! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:50 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecay_Hp_Inert2
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

Subroutine Amplitude_Tree_Inert2_HpToHpA0(cplA0HpcHp,MA0,MHp,MA02,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MA02,MHp2(2)

Complex(dp), Intent(in) :: cplA0HpcHp(2,2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MA0 
! Tree-Level Vertex 
coupT1 = cplA0HpcHp(gt2,gt1)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_HpToHpA0


Subroutine Gamma_Real_Inert2_HpToHpA0(MLambda,em,gs,cplA0HpcHp,MA0,MHp,               & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0HpcHp(2,2)

Real(dp), Intent(in) :: MA0,MHp(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2), GammarealGluon(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
Coup = cplA0HpcHp(i2,i1)
Mex1 = MHp(i1)
Mex2 = MHp(i2)
Mex3 = MA0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSS(Mex1,Mex2,Mex3,MLambda,em,1._dp,1._dp,0._dp,1._dp,0._dp,0._dp,Coup,Gammarealphoton(i1,i2),kont)
  GammarealGluon(i1,i2) = 0._dp 
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_HpToHpA0


Subroutine Amplitude_WAVE_Inert2_HpToHpA0(cplA0HpcHp,ctcplA0HpcHp,MA0,MA02,           & 
& MHp,MHp2,ZfA0,ZfHp,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplA0HpcHp(2,2)

Complex(dp), Intent(in) :: ctcplA0HpcHp(2,2)

Complex(dp), Intent(in) :: ZfA0,ZfHp(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MA0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0HpcHp(gt2,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplA0HpcHp(gt2,i1)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplA0HpcHp(i1,gt1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0HpcHp(gt2,gt1)


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToHpA0


Subroutine Amplitude_VERTEX_Inert2_HpToHpA0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,             & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,              & 
& cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,              & 
& cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),           & 
& cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),          & 
& cplHpcVWpVP(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),           & 
& cplA0A0HpcHp1(2,2),cplA0G0HpcHp1(2,2),cplA0hhHpcHp1(2,2),cplA0HpcVWpVP1(2),            & 
& cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),cplG0H0HpcHp1(2,2),              & 
& cplH0hhHpcHp1(2,2),cplHpHpcHpcHp1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(gt1, gt2) = 0._dp 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MA0 


! {A0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {A0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {H0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, hh, A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, hh, H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MH0 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, A0, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, H0, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, H0, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MVZ 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = -cplHpcHpVZ(gt2,i1)
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, G0, A0}
ML1 = MVWp 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, A0}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, G0}
ML1 = MVWp 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, G0}
ML1 = MVWp 
ML2 = MH0 
ML3 = MG0 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, G0, H0}
ML1 = MVWp 
ML2 = MG0 
ML3 = MH0 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, H0}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ, H0}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MH0 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, hh}
ML1 = MVWp 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, hh}
ML1 = MVWp 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, VZ}
ML1 = MVWp 
ML2 = MH0 
ML3 = MVZ 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = -cplHpcHpVZ(gt2,i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplHpcHpVZ(gt2,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0A0HpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplA0hhHpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplA0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplA0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0A0HpcHp1(i2,gt1)
coup2 = cplA0HpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i2,gt1)
coup2 = cplhhHpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplA0cHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplA0cHpVWpVZ1(gt1)
coup2 = cplHpcVWpVZ(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0G0HpcHp1(gt2,gt1)
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0hhHpcHp1(gt2,gt1)
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplG0H0HpcHp1(gt2,gt1)
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplH0hhHpcHp1(gt2,gt1)
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplHpHpcHpcHp1(gt2,i1,gt1,i2)
coup2 = cplA0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToHpA0


Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpA0(MA0,MG0,MH0,Mhh,MHp,MVP,               & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,       & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,              & 
& cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,              & 
& cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),           & 
& cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),          & 
& cplHpcVWpVP(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),           & 
& cplA0A0HpcHp1(2,2),cplA0G0HpcHp1(2,2),cplA0hhHpcHp1(2,2),cplA0HpcVWpVP1(2),            & 
& cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),cplG0H0HpcHp1(2,2),              & 
& cplH0hhHpcHp1(2,2),cplHpHpcHpcHp1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MA0 


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplA0HpcHp(i3,i2)
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplA0HpcVWp(i3)
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplA0cHpVWp(i2)
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplA0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplA0cHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt2)
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpA0


Subroutine Amplitude_Tree_Inert2_HpToA0VWp(cplA0cHpVWp,MA0,MHp,MVWp,MA02,             & 
& MHp2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVWp,MA02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0cHpVWp(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MA0 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = -cplA0cHpVWp(gt1)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_Tree_Inert2_HpToA0VWp


Subroutine Gamma_Real_Inert2_HpToA0VWp(MLambda,em,gs,cplA0cHpVWp,MA0,MHp,             & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0cHpVWp(2)

Real(dp), Intent(in) :: MA0,MHp(2),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
Coup = cplA0cHpVWp(i1)
Mex1 = MHp(i1)
Mex2 = MA0
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,1._dp,0._dp,1._dp,Coup,Gammarealphoton(i1),kont)
 GammarealGluon(i1) = 0._dp 
Else 
  GammarealGluon(i1) = 0._dp 
  GammarealPhoton(i1) = 0._dp 

End if 
End Do
End Subroutine Gamma_Real_Inert2_HpToA0VWp


Subroutine Amplitude_WAVE_Inert2_HpToA0VWp(cplA0cHpVWp,ctcplA0cHpVWp,MA0,             & 
& MA02,MHp,MHp2,MVWp,MVWp2,ZfA0,ZfHp,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0cHpVWp(2)

Complex(dp), Intent(in) :: ctcplA0cHpVWp(2)

Complex(dp), Intent(in) :: ZfA0,ZfHp(2,2),ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MA0 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0cHpVWp(gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplA0cHpVWp(i1)
End Do


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0cHpVWp(gt1)


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplA0cHpVWp(gt1)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToA0VWp


Subroutine Amplitude_VERTEX_Inert2_HpToA0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,            & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0cHpVWp(2),cplH0HpcHp(2,2),cplH0cHpVWp(2),cplhhHpcHp(2,2),          & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),            & 
& cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1(2),            & 
& cplA0cHpVWpVZ1(2),cplH0cHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MA0 
Mex3 = MVWp 


! {A0, conj[Hp], G0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0A0G0
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[Hp], hh}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0A0hh
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], hh}
ML1 = MA0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0A0hh
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], G0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplA0G0H0
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp], hh}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplA0H0hh
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], hh}
ML1 = MH0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplA0H0hh
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], VZ}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplA0H0VZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], VZ}
ML1 = MH0 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplA0H0VZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {hh, conj[Hp], A0}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplA0A0hh
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], H0}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplA0H0hh
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, A0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, H0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VZ, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplA0cHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplA0cHpVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplA0cHpVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], H0}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplA0H0VZ
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
coup1 = -cplA0cHpVWp(gt1)
coup2 = cplA0A0cVWpVWp1
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplA0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplA0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {H0, VZ}
ML1 = MH0 
ML2 = MVZ 
coup1 = cplH0cHpVWpVZ1(gt1)
coup2 = cplA0H0VZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(i1,gt1)
coup2 = cplA0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToA0VWp


Subroutine Amplitude_IR_VERTEX_Inert2_HpToA0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,              & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,       & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0cHpVWp(2),cplH0HpcHp(2,2),cplH0cHpVWp(2),cplhhHpcHp(2,2),          & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),            & 
& cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1(2),            & 
& cplA0cHpVWpVZ1(2),cplH0cHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MA0 
Mex3 = MVWp 


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplA0cHpVWp(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplA0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplA0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToA0VWp


Subroutine Amplitude_Tree_Inert2_HpTocFdFu(cplcFdFucHpL,cplcFdFucHpR,MFd,             & 
& MFu,MHp,MFd2,MFu2,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MHp(2),MFd2(3),MFu2(3),MHp2(2)

Complex(dp), Intent(in) :: cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2)

Complex(dp) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFu(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFdFucHpL(gt2,gt3,gt1)
coupT1R = cplcFdFucHpR(gt2,gt3,gt1)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_HpTocFdFu


Subroutine Gamma_Real_Inert2_HpTocFdFu(MLambda,em,gs,cplcFdFucHpL,cplcFdFucHpR,       & 
& MFd,MFu,MHp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2)

Real(dp), Intent(in) :: MFd(3),MFu(3),MHp(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,3,3), GammarealGluon(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=2,2
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFdFucHpL(i2,i3,i1)
CoupR = cplcFdFucHpR(i2,i3,i1)
Mex1 = MHp(i1)
Mex2 = MFd(i2)
Mex3 = MFu(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,3._dp,1._dp,2._dp,1._dp/3._dp,2._dp/3._dp,4._dp/3._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,gs,0._dp,0._dp,0._dp,4._dp,-4._dp,4._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_Inert2_HpTocFdFu


Subroutine Amplitude_WAVE_Inert2_HpTocFdFu(cplcFdFucHpL,cplcFdFucHpR,ctcplcFdFucHpL,  & 
& ctcplcFdFucHpR,MFd,MFd2,MFu,MFu2,MHp,MHp2,ZfDL,ZfDR,ZfHp,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3),MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFdFucHpL(3,3,2),ctcplcFdFucHpR(3,3,2)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfHp(2,2),ZfUL(3,3),ZfUR(3,3)

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
Mex1 = MHp(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFu(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFucHpL(gt2,gt3,gt1) 
ZcoupT1R = ctcplcFdFucHpR(gt2,gt3,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplcFdFucHpL(gt2,gt3,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplcFdFucHpR(gt2,gt3,i1)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDR(i1,gt2)*cplcFdFucHpL(i1,gt3,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDL(i1,gt2))*cplcFdFucHpR(i1,gt3,gt1)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt3)*cplcFdFucHpL(gt2,i1,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt3))*cplcFdFucHpR(gt2,i1,gt1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpTocFdFu


Subroutine Amplitude_VERTEX_Inert2_HpTocFdFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,             & 
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
Mex1 = MHp(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFu(gt3) 


! {G0, conj[VWp], Fd}
    Do i3=1,3
ML1 = MG0 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = -cplG0cHpVWp(gt1)
coup2L = cplcFdFdG0L(gt2,i3)
coup2R = cplcFdFdG0R(gt2,i3)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2L = cplcFdFdhhL(gt2,i3)
coup2R = cplcFdFdhhR(gt2,i3)
coup3L = cplcFdFucHpL(i3,gt3,i2)
coup3R = cplcFdFucHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], Fd}
    Do i3=1,3
ML1 = Mhh 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = -cplhhcHpVWp(gt1)
coup2L = cplcFdFdhhL(gt2,i3)
coup2R = cplcFdFdhhR(gt2,i3)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, hh, Fu}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MFu(i3) 
coup1 = cplhhHpcHp(i1,gt1)
coup2L = cplcFdFucHpL(gt2,i3,i1)
coup2R = cplcFdFucHpR(gt2,i3,i1)
coup3L = cplcFuFuhhL(i3,gt3)
coup3R = cplcFuFuhhR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, Fu}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MFu(i3) 
coup1 = -cplHpcHpVP(i1,gt1)
coup2L = cplcFdFucHpL(gt2,i3,i1)
coup2R = cplcFdFucHpR(gt2,i3,i1)
coup3L = cplcFuFuVPL(i3,gt3)
coup3R = cplcFuFuVPR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VZ, Fu}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MFu(i3) 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2L = cplcFdFucHpL(gt2,i3,i1)
coup2R = cplcFdFucHpR(gt2,i3,i1)
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


! {VP, conj[Hp], Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = -cplHpcHpVP(i2,gt1)
coup2L = cplcFdFdVPL(gt2,i3)
coup2R = cplcFdFdVPR(gt2,i3)
coup3L = cplcFdFucHpL(i3,gt3,i2)
coup3R = cplcFdFucHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], Fd}
    Do i3=1,3
ML1 = MVP 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2L = cplcFdFdVPL(gt2,i3)
coup2R = cplcFdFdVPR(gt2,i3)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Fu}
    Do i3=1,3
ML1 = MVWp 
ML2 = MG0 
ML3 = MFu(i3) 
coup1 = -cplG0cHpVWp(gt1)
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFuG0L(i3,gt3)
coup3R = cplcFuFuG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Fu}
    Do i3=1,3
ML1 = MVWp 
ML2 = Mhh 
ML3 = MFu(i3) 
coup1 = -cplhhcHpVWp(gt1)
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFuhhL(i3,gt3)
coup3R = cplcFuFuhhR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Fu}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVP 
ML3 = MFu(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFuVPL(i3,gt3)
coup3R = cplcFuFuVPR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Fu}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVZ 
ML3 = MFu(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFuVZL(i3,gt3)
coup3R = cplcFuFuVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = -cplHpcHpVZ(i2,gt1)
coup2L = cplcFdFdVZL(gt2,i3)
coup2R = cplcFdFdVZR(gt2,i3)
coup3L = cplcFdFucHpL(i3,gt3,i2)
coup3R = cplcFdFucHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], Fd}
    Do i3=1,3
ML1 = MVZ 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2L = cplcFdFdVZL(gt2,i3)
coup2R = cplcFdFdVZR(gt2,i3)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {bar[Fd], bar[Fu], G0}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MG0 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdG0L(gt2,i1)
coup2R = cplcFdFdG0R(gt2,i1)
coup3L = cplcFuFuG0L(i2,gt3)
coup3R = cplcFuFuG0R(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fu], hh}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = Mhh 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdhhL(gt2,i1)
coup2R = cplcFdFdhhR(gt2,i1)
coup3L = cplcFuFuhhL(i2,gt3)
coup3R = cplcFuFuhhR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fu], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MVG 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVGL(gt2,i1)
coup2R = cplcFdFdVGR(gt2,i1)
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


! {bar[Fd], bar[Fu], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MVP 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVPL(gt2,i1)
coup2R = cplcFdFdVPR(gt2,i1)
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


! {bar[Fd], bar[Fu], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MVZ 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVZL(gt2,i1)
coup2R = cplcFdFdVZR(gt2,i1)
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
End Subroutine Amplitude_VERTEX_Inert2_HpTocFdFu


Subroutine Amplitude_IR_VERTEX_Inert2_HpTocFdFu(MFd,MFu,MG0,Mhh,MHp,MVG,              & 
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
Mex1 = MHp(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFu(gt3) 


! {Hp, VP, Fu}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MFu(i3) 
coup1 = -cplHpcHpVP(i1,gt1)
coup2L = cplcFdFucHpL(gt2,i3,i1)
coup2R = cplcFdFucHpR(gt2,i3,i1)
coup3L = cplcFuFuVPL(i3,gt3)
coup3R = cplcFuFuVPR(i3,gt3)
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VP, conj[Hp], Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = -cplHpcHpVP(i2,gt1)
coup2L = cplcFdFdVPL(gt2,i3)
coup2R = cplcFdFdVPR(gt2,i3)
coup3L = cplcFdFucHpL(i3,gt3,i2)
coup3R = cplcFdFucHpR(i3,gt3,i2)
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], Fd}
    Do i3=1,3
ML1 = MVP 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2L = cplcFdFdVPL(gt2,i3)
coup2R = cplcFdFdVPR(gt2,i3)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Fu}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVP 
ML3 = MFu(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFuVPL(i3,gt3)
coup3R = cplcFuFuVPR(i3,gt3)
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {bar[Fd], bar[Fu], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MVG 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVGL(gt2,i1)
coup2R = cplcFdFdVGR(gt2,i1)
coup3L = cplcFuFuVGL(i2,gt3)
coup3R = cplcFuFuVGR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fu], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MVP 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVPL(gt2,i1)
coup2R = cplcFdFdVPR(gt2,i1)
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
End Subroutine Amplitude_IR_VERTEX_Inert2_HpTocFdFu


Subroutine Amplitude_Tree_Inert2_HpTocFeFv(cplcFeFvcHpL,cplcFeFvcHpR,MFe,             & 
& MHp,MFe2,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MHp(2),MFe2(3),MHp2(2)

Complex(dp), Intent(in) :: cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2)

Complex(dp) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MFe(gt2) 
Mex3 = 0._dp 
! Tree-Level Vertex 
coupT1L = cplcFeFvcHpL(gt2,gt3,gt1)
coupT1R = cplcFeFvcHpR(gt2,gt3,gt1)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_HpTocFeFv


Subroutine Gamma_Real_Inert2_HpTocFeFv(MLambda,em,gs,cplcFeFvcHpL,cplcFeFvcHpR,       & 
& MFe,MHp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2)

Real(dp), Intent(in) :: MFe(3),MHp(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,3,3), GammarealGluon(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=2,2
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFeFvcHpL(i2,i3,i1)
CoupR = cplcFeFvcHpR(i2,i3,i1)
Mex1 = MHp(i1)
Mex2 = MFe(i2)
Mex3 = 0._dp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,1._dp,1._dp,0._dp,1._dp,0._dp,0._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
  GammarealGluon(i1,i2,i3) = 0._dp 
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_Inert2_HpTocFeFv


Subroutine Amplitude_WAVE_Inert2_HpTocFeFv(cplcFeFvcHpL,cplcFeFvcHpR,ctcplcFeFvcHpL,  & 
& ctcplcFeFvcHpR,MFe,MFe2,MHp,MHp2,ZfEL,ZfER,ZfHp,ZfvL,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MFe2(3),MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFeFvcHpL(3,3,2),ctcplcFeFvcHpR(3,3,2)

Complex(dp), Intent(in) :: ZfEL(3,3),ZfER(3,3),ZfHp(2,2),ZfvL(3,3)

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
Mex1 = MHp(gt1) 
Mex2 = MFe(gt2) 
Mex3 = 0._dp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFeFvcHpL(gt2,gt3,gt1) 
ZcoupT1R = ctcplcFeFvcHpR(gt2,gt3,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplcFeFvcHpL(gt2,gt3,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplcFeFvcHpR(gt2,gt3,i1)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfER(i1,gt2)*cplcFeFvcHpL(i1,gt3,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfEL(i1,gt2))*cplcFeFvcHpR(i1,gt3,gt1)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfvL(i1,gt3)*cplcFeFvcHpL(gt2,i1,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*0*cplcFeFvcHpR(gt2,i1,gt1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpTocFeFv


Subroutine Amplitude_VERTEX_Inert2_HpTocFeFv(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0cHpVWp,         & 
& cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MG0,Mhh,MHp(2),MVP,MVWp,MVZ,MFe2(3),MG02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3), & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),  & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),         & 
& cplG0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),         & 
& cplcHpVPVWp(2),cplcHpVWpVZ(2)

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
Mex1 = MHp(gt1) 
Mex2 = MFe(gt2) 
Mex3 = 0._dp 


! {G0, conj[VWp], Fe}
    Do i3=1,3
ML1 = MG0 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = -cplG0cHpVWp(gt1)
coup2L = cplcFeFeG0L(gt2,i3)
coup2R = cplcFeFeG0R(gt2,i3)
coup3L = cplcFeFvcVWpL(i3,gt3)
coup3R = cplcFeFvcVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], Fe}
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2L = cplcFeFehhL(gt2,i3)
coup2R = cplcFeFehhR(gt2,i3)
coup3L = cplcFeFvcHpL(i3,gt3,i2)
coup3R = cplcFeFvcHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], Fe}
    Do i3=1,3
ML1 = Mhh 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = -cplhhcHpVWp(gt1)
coup2L = cplcFeFehhL(gt2,i3)
coup2R = cplcFeFehhR(gt2,i3)
coup3L = cplcFeFvcVWpL(i3,gt3)
coup3R = cplcFeFvcVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VZ, Fv}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = 0._dp 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2L = cplcFeFvcHpL(gt2,i3,i1)
coup2R = cplcFeFvcHpR(gt2,i3,i1)
coup3L = cplcFvFvVZL(i3,gt3)
coup3R = cplcFvFvVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VP, conj[Hp], Fe}
  Do i2=1,2
    Do i3=1,3
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = -cplHpcHpVP(i2,gt1)
coup2L = cplcFeFeVPL(gt2,i3)
coup2R = cplcFeFeVPR(gt2,i3)
coup3L = cplcFeFvcHpL(i3,gt3,i2)
coup3R = cplcFeFvcHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], Fe}
    Do i3=1,3
ML1 = MVP 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2L = cplcFeFeVPL(gt2,i3)
coup2R = cplcFeFeVPR(gt2,i3)
coup3L = cplcFeFvcVWpL(i3,gt3)
coup3R = cplcFeFvcVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Fv}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVZ 
ML3 = 0._dp 
coup1 = cplcHpVWpVZ(gt1)
coup2L = cplcFeFvcVWpL(gt2,i3)
coup2R = cplcFeFvcVWpR(gt2,i3)
coup3L = cplcFvFvVZL(i3,gt3)
coup3R = cplcFvFvVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], Fe}
  Do i2=1,2
    Do i3=1,3
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = -cplHpcHpVZ(i2,gt1)
coup2L = cplcFeFeVZL(gt2,i3)
coup2R = cplcFeFeVZR(gt2,i3)
coup3L = cplcFeFvcHpL(i3,gt3,i2)
coup3R = cplcFeFvcHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], Fe}
    Do i3=1,3
ML1 = MVZ 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2L = cplcFeFeVZL(gt2,i3)
coup2R = cplcFeFeVZR(gt2,i3)
coup3L = cplcFeFvcVWpL(i3,gt3)
coup3R = cplcFeFvcVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {bar[Fe], bar[Fv], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = MVZ 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFeFeVZL(gt2,i1)
coup2R = cplcFeFeVZR(gt2,i1)
coup3L = cplcFvFvVZL(i2,gt3)
coup3R = cplcFvFvVZR(i2,gt3)
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
End Subroutine Amplitude_VERTEX_Inert2_HpTocFeFv


Subroutine Amplitude_IR_VERTEX_Inert2_HpTocFeFv(MFe,MG0,Mhh,MHp,MVP,MVWp,             & 
& MVZ,MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0cHpVWp,         & 
& cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MG0,Mhh,MHp(2),MVP,MVWp,MVZ,MFe2(3),MG02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3), & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),  & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),         & 
& cplG0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),         & 
& cplcHpVPVWp(2),cplcHpVWpVZ(2)

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
Mex1 = MHp(gt1) 
Mex2 = MFe(gt2) 
Mex3 = 0._dp 


! {VP, conj[Hp], Fe}
  Do i2=1,2
    Do i3=1,3
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = -cplHpcHpVP(i2,gt1)
coup2L = cplcFeFeVPL(gt2,i3)
coup2R = cplcFeFeVPR(gt2,i3)
coup3L = cplcFeFvcHpL(i3,gt3,i2)
coup3R = cplcFeFvcHpR(i3,gt3,i2)
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], Fe}
    Do i3=1,3
ML1 = MVP 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2L = cplcFeFeVPL(gt2,i3)
coup2R = cplcFeFeVPR(gt2,i3)
coup3L = cplcFeFvcVWpL(i3,gt3)
coup3R = cplcFeFvcVWpR(i3,gt3)
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpTocFeFv


Subroutine Amplitude_Tree_Inert2_HpToG0VWp(cplG0cHpVWp,MG0,MHp,MVWp,MG02,             & 
& MHp2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MHp(2),MVWp,MG02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplG0cHpVWp(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = -cplG0cHpVWp(gt1)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_Tree_Inert2_HpToG0VWp


Subroutine Gamma_Real_Inert2_HpToG0VWp(MLambda,em,gs,cplG0cHpVWp,MG0,MHp,             & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplG0cHpVWp(2)

Real(dp), Intent(in) :: MG0,MHp(2),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
Coup = cplG0cHpVWp(i1)
Mex1 = MHp(i1)
Mex2 = MG0
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,1._dp,0._dp,1._dp,Coup,Gammarealphoton(i1),kont)
 GammarealGluon(i1) = 0._dp 
Else 
  GammarealGluon(i1) = 0._dp 
  GammarealPhoton(i1) = 0._dp 

End if 
End Do
End Subroutine Gamma_Real_Inert2_HpToG0VWp


Subroutine Amplitude_WAVE_Inert2_HpToG0VWp(cplG0cHpVWp,ctcplG0cHpVWp,MG0,             & 
& MG02,MHp,MHp2,MVWp,MVWp2,ZfG0,ZfHp,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplG0cHpVWp(2)

Complex(dp), Intent(in) :: ctcplG0cHpVWp(2)

Complex(dp), Intent(in) :: ZfG0,ZfHp(2,2),ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplG0cHpVWp(gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplG0cHpVWp(i1)
End Do


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfG0*cplG0cHpVWp(gt1)


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplG0cHpVWp(gt1)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToG0VWp


Subroutine Amplitude_VERTEX_Inert2_HpToG0VWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,             & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0G0,cplA0G0H0,cplA0HpcHp,cplA0cHpVWp,cplcFdFdG0L,cplcFdFdG0R,cplcFuFdVWpL,       & 
& cplcFuFdVWpR,cplcFeFeG0L,cplcFeFeG0R,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuG0L,            & 
& cplcFuFuG0R,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,             & 
& cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWCgAcHp,    & 
& cplcgZgWpcHp,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,           & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0G0cVWpVWp1,cplG0cHpVPVWp1,cplG0cHpVWpVZ1,   & 
& cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFdG0L(3,3),cplcFdFdG0R(3,3), & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFvFeVWpL(3,3),& 
& cplcFvFeVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFdFucHpL(3,3,2),               & 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0G0hh,cplcgWpgWpG0,    & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWCgAcHp(2),        & 
& cplcgZgWpcHp(2),cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp(2),cplH0HpcHp(2,2),& 
& cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),            & 
& cplHpcHpVZ(2,2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,               & 
& cplG0G0cVWpVWp1,cplG0cHpVPVWp1(2),cplG0cHpVWpVZ1(2),cplhhcHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MVWp 


! {A0, conj[Hp], A0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0A0G0
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[Hp], H0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0G0H0
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Fu, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = -cplcFuFdVWpR(i3,i2)
coup3R = -cplcFuFdVWpL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {G0, conj[VWp], hh}
ML1 = MG0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplG0G0hh
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {gWp, gZ, gWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgWpG0
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], A0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplA0G0H0
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp], H0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplG0H0H0
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], G0}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplG0G0hh
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], VZ}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplG0hhVZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], VZ}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplG0hhVZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplG0cHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplG0cHpVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplG0cHpVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], hh}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplG0hhVZ
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], hh}
ML1 = MVZ 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplG0hhVZ
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdG0L(i3,i1)
coup2R = cplcFdFdG0R(i3,i1)
coup3L = cplcFuFdVWpL(i2,i3)
coup3R = cplcFuFdVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[Fe], bar[Fv], bar[Fe]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFeFeG0L(i3,i1)
coup2R = cplcFeFeG0R(i3,i1)
coup3L = cplcFvFeVWpL(i2,i3)
coup3R = cplcFvFeVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[gWpC], bar[gP], bar[gWpC]}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcgWCgAcHp(gt1)
coup2 = cplcgWCgWCG0
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[gWpC], bar[gZ], bar[gWpC]}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgWCgWCG0
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {G0, conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
coup1 = -cplG0cHpVWp(gt1)
coup2 = cplG0G0cVWpVWp1
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplG0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplG0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {hh, VZ}
ML1 = Mhh 
ML2 = MVZ 
coup1 = cplhhcHpVWpVZ1(gt1)
coup2 = cplG0hhVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(i1,gt1)
coup2 = cplG0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToG0VWp


Subroutine Amplitude_IR_VERTEX_Inert2_HpToG0VWp(MA0,MFd,MFe,MFu,MG0,MH0,              & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0G0,cplA0G0H0,cplA0HpcHp,cplA0cHpVWp,cplcFdFdG0L,cplcFdFdG0R,               & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFeG0L,cplcFeFeG0R,cplcFvFeVWpL,cplcFvFeVWpR,           & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,       & 
& cplcgWCgAcHp,cplcgZgWpcHp,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp,         & 
& cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,      & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0G0cVWpVWp1,cplG0cHpVPVWp1,      & 
& cplG0cHpVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFdG0L(3,3),cplcFdFdG0R(3,3), & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFvFeVWpL(3,3),& 
& cplcFvFeVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFdFucHpL(3,3,2),               & 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0G0hh,cplcgWpgWpG0,    & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWCgAcHp(2),        & 
& cplcgZgWpcHp(2),cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp(2),cplH0HpcHp(2,2),& 
& cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),            & 
& cplHpcHpVZ(2,2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,               & 
& cplG0G0cVWpVWp1,cplG0cHpVPVWp1(2),cplG0cHpVWpVZ1(2),cplhhcHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MVWp 


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplG0cHpVWp(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplG0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplG0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToG0VWp


Subroutine Amplitude_Tree_Inert2_HpToHpH0(cplH0HpcHp,MH0,MHp,MH02,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MHp(2),MH02,MHp2(2)

Complex(dp), Intent(in) :: cplH0HpcHp(2,2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MH0 
! Tree-Level Vertex 
coupT1 = cplH0HpcHp(gt2,gt1)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_HpToHpH0


Subroutine Gamma_Real_Inert2_HpToHpH0(MLambda,em,gs,cplH0HpcHp,MH0,MHp,               & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplH0HpcHp(2,2)

Real(dp), Intent(in) :: MH0,MHp(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2), GammarealGluon(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
Coup = cplH0HpcHp(i2,i1)
Mex1 = MHp(i1)
Mex2 = MHp(i2)
Mex3 = MH0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSS(Mex1,Mex2,Mex3,MLambda,em,1._dp,1._dp,0._dp,1._dp,0._dp,0._dp,Coup,Gammarealphoton(i1,i2),kont)
  GammarealGluon(i1,i2) = 0._dp 
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_HpToHpH0


Subroutine Amplitude_WAVE_Inert2_HpToHpH0(cplH0HpcHp,ctcplH0HpcHp,MH0,MH02,           & 
& MHp,MHp2,ZfH0,ZfHp,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MH02,MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplH0HpcHp(2,2)

Complex(dp), Intent(in) :: ctcplH0HpcHp(2,2)

Complex(dp), Intent(in) :: ZfH0,ZfHp(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MH0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplH0HpcHp(gt2,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplH0HpcHp(gt2,i1)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplH0HpcHp(i1,gt1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplH0HpcHp(gt2,gt1)


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToHpH0


Subroutine Amplitude_VERTEX_Inert2_HpToHpH0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,             & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,              & 
& cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1, & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),          & 
& cplG0H0H0,cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),      & 
& cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),          & 
& cplHpcVWpVP(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),           & 
& cplA0G0HpcHp1(2,2),cplA0hhHpcHp1(2,2),cplG0H0HpcHp1(2,2),cplH0H0HpcHp1(2,2),           & 
& cplH0hhHpcHp1(2,2),cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2),cplH0cHpVPVWp1(2),              & 
& cplH0cHpVWpVZ1(2),cplHpHpcHpcHp1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(gt1, gt2) = 0._dp 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MH0 


! {A0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {A0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {H0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, hh, A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MA0 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, hh, H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, A0, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, H0, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, A0, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MVZ 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = -cplHpcHpVZ(gt2,i1)
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, G0, A0}
ML1 = MVWp 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, A0}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ, A0}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MA0 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, G0}
ML1 = MVWp 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, G0}
ML1 = MVWp 
ML2 = MH0 
ML3 = MG0 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, G0, H0}
ML1 = MVWp 
ML2 = MG0 
ML3 = MH0 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, H0}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, hh}
ML1 = MVWp 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, hh}
ML1 = MVWp 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, VZ}
ML1 = MVWp 
ML2 = MA0 
ML3 = MVZ 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = -cplHpcHpVZ(gt2,i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplHpcHpVZ(gt2,i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0H0HpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplH0hhHpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplH0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplH0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0H0HpcHp1(i2,gt1)
coup2 = cplH0HpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i2,gt1)
coup2 = cplhhHpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplH0cHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplH0cHpVWpVZ1(gt1)
coup2 = cplHpcVWpVZ(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0G0HpcHp1(gt2,gt1)
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0hhHpcHp1(gt2,gt1)
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplG0H0HpcHp1(gt2,gt1)
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplH0hhHpcHp1(gt2,gt1)
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplHpHpcHpcHp1(gt2,i1,gt1,i2)
coup2 = cplH0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToHpH0


Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpH0(MA0,MG0,MH0,Mhh,MHp,MVP,               & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,       & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,              & 
& cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1, & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),          & 
& cplG0H0H0,cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),      & 
& cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),          & 
& cplHpcVWpVP(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),           & 
& cplA0G0HpcHp1(2,2),cplA0hhHpcHp1(2,2),cplG0H0HpcHp1(2,2),cplH0H0HpcHp1(2,2),           & 
& cplH0hhHpcHp1(2,2),cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2),cplH0cHpVPVWp1(2),              & 
& cplH0cHpVWpVZ1(2),cplHpHpcHpcHp1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MH0 


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplH0HpcHp(i3,i2)
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplH0HpcVWp(i3)
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplH0cHpVWp(i2)
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplH0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplH0cHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt2)
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpH0


Subroutine Amplitude_Tree_Inert2_HpToH0VWp(cplH0cHpVWp,MH0,MHp,MVWp,MH02,             & 
& MHp2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MHp(2),MVWp,MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplH0cHpVWp(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MH0 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = -cplH0cHpVWp(gt1)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_Tree_Inert2_HpToH0VWp


Subroutine Gamma_Real_Inert2_HpToH0VWp(MLambda,em,gs,cplH0cHpVWp,MH0,MHp,             & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplH0cHpVWp(2)

Real(dp), Intent(in) :: MH0,MHp(2),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
Coup = cplH0cHpVWp(i1)
Mex1 = MHp(i1)
Mex2 = MH0
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,1._dp,0._dp,1._dp,Coup,Gammarealphoton(i1),kont)
 GammarealGluon(i1) = 0._dp 
Else 
  GammarealGluon(i1) = 0._dp 
  GammarealPhoton(i1) = 0._dp 

End if 
End Do
End Subroutine Gamma_Real_Inert2_HpToH0VWp


Subroutine Amplitude_WAVE_Inert2_HpToH0VWp(cplH0cHpVWp,ctcplH0cHpVWp,MH0,             & 
& MH02,MHp,MHp2,MVWp,MVWp2,ZfH0,ZfHp,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MH02,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplH0cHpVWp(2)

Complex(dp), Intent(in) :: ctcplH0cHpVWp(2)

Complex(dp), Intent(in) :: ZfH0,ZfHp(2,2),ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MH0 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplH0cHpVWp(gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplH0cHpVWp(i1)
End Do


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplH0cHpVWp(gt1)


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplH0cHpVWp(gt1)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToH0VWp


Subroutine Amplitude_VERTEX_Inert2_HpToH0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,            & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplG0H0H0,               & 
& cplG0cHpVWp(2),cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),& 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),            & 
& cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0cHpVWpVZ1(2),cplH0H0cVWpVWp1,            & 
& cplH0cHpVPVWp1(2),cplH0cHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MH0 
Mex3 = MVWp 


! {A0, conj[Hp], G0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0G0H0
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[Hp], hh}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0H0hh
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], hh}
ML1 = MA0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0H0hh
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp], VZ}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = -cplA0H0VZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], VZ}
ML1 = MA0 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplA0cHpVWp(gt1)
coup2 = -cplA0H0VZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], G0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplG0H0H0
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp], hh}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0H0hh
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], hh}
ML1 = MH0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0H0hh
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {hh, conj[Hp], A0}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplA0H0hh
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], H0}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplH0H0hh
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, A0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, H0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VZ, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplH0cHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplH0cHpVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplH0cHpVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], A0}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = -cplA0H0VZ
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
coup1 = -cplH0cHpVWp(gt1)
coup2 = cplH0H0cVWpVWp1
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplH0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplH0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {A0, VZ}
ML1 = MA0 
ML2 = MVZ 
coup1 = cplA0cHpVWpVZ1(gt1)
coup2 = -cplA0H0VZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(i1,gt1)
coup2 = cplH0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToH0VWp


Subroutine Amplitude_IR_VERTEX_Inert2_HpToH0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,              & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,       & 
& cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplG0H0H0,               & 
& cplG0cHpVWp(2),cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),& 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),            & 
& cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0cHpVWpVZ1(2),cplH0H0cVWpVWp1,            & 
& cplH0cHpVPVWp1(2),cplH0cHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MH0 
Mex3 = MVWp 


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplH0cHpVWp(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplH0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplH0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToH0VWp


Subroutine Amplitude_Tree_Inert2_HpToHphh(cplhhHpcHp,Mhh,MHp,Mhh2,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,MHp(2),Mhh2,MHp2(2)

Complex(dp), Intent(in) :: cplhhHpcHp(2,2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = Mhh 
! Tree-Level Vertex 
coupT1 = cplhhHpcHp(gt2,gt1)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_HpToHphh


Subroutine Gamma_Real_Inert2_HpToHphh(MLambda,em,gs,cplhhHpcHp,Mhh,MHp,               & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplhhHpcHp(2,2)

Real(dp), Intent(in) :: Mhh,MHp(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2), GammarealGluon(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
Coup = cplhhHpcHp(i2,i1)
Mex1 = MHp(i1)
Mex2 = MHp(i2)
Mex3 = Mhh
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSS(Mex1,Mex2,Mex3,MLambda,em,1._dp,1._dp,0._dp,1._dp,0._dp,0._dp,Coup,Gammarealphoton(i1,i2),kont)
  GammarealGluon(i1,i2) = 0._dp 
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_HpToHphh


Subroutine Amplitude_WAVE_Inert2_HpToHphh(cplhhHpcHp,ctcplhhHpcHp,Mhh,Mhh2,           & 
& MHp,MHp2,Zfhh,ZfHp,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplhhHpcHp(2,2)

Complex(dp), Intent(in) :: ctcplhhHpcHp(2,2)

Complex(dp), Intent(in) :: Zfhh,ZfHp(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = Mhh 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhHpcHp(gt2,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplhhHpcHp(gt2,i1)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplhhHpcHp(i1,gt1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhHpcHp(gt2,gt1)


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToHphh


Subroutine Amplitude_VERTEX_Inert2_HpToHphh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,    & 
& cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,       & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,   & 
& cplA0hhHpcHp1,cplG0G0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,  & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,          & 
& cplHpcHpVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFdFdhhL(3,3),   & 
& cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFuFuhhL(3,3),               & 
& cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),          & 
& cplcFeFvcHpR(3,3,2),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,    & 
& cplcgZgWpcHp(2),cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcHp(2), & 
& cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),     & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP(2,2),cplHpcVWpVP(2),   & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0HpcHp1(2,2),       & 
& cplA0hhHpcHp1(2,2),cplG0G0HpcHp1(2,2),cplH0H0HpcHp1(2,2),cplH0hhHpcHp1(2,2),           & 
& cplhhhhHpcHp1(2,2),cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),cplhhcHpVPVWp1(2),              & 
& cplhhcHpVWpVZ1(2),cplHpHpcHpcHp1(2,2,2,2),cplHpcHpcVWpVWp1(2,2),cplHpcHpVZVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(gt1, gt2) = 0._dp 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = Mhh 


! {A0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {A0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {Fu, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = cplcFuFdHpL(i1,i3,gt2)
coup2R = cplcFuFdHpR(i1,i3,gt2)
coup3L = cplcFdFdhhL(i3,i2)
coup3R = cplcFdFdhhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {Fv, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = 0._dp 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i2,i1,gt1)
coup1R = cplcFeFvcHpR(i2,i1,gt1)
coup2L = cplcFvFeHpL(i1,i3,gt2)
coup2R = cplcFvFeHpR(i1,i3,gt2)
coup3L = cplcFeFehhL(i3,i2)
coup3R = cplcFeFehhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {G0, conj[VWp], conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {gWp, gZ, gZ}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgZgZhh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {gZ, gWpC, gWpC}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgZgWCHp(gt2)
coup3 = cplcgWCgWChh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {H0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {Hp, A0, A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, H0, A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, A0, H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, H0, H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MH0 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, hh, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = Mhh 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplhhhhhh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = -cplHpcHpVZ(gt2,i1)
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp], conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, A0}
ML1 = MVWp 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, A0}
ML1 = MVWp 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplA0HpcVWp(gt2)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, G0, G0}
ML1 = MVWp 
ML2 = MG0 
ML3 = MG0 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ, G0}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MG0 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplG0HpcVWp(gt2)
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, H0}
ML1 = MVWp 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, H0}
ML1 = MVWp 
ML2 = MH0 
ML3 = MH0 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcVWp(gt2)
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, hh}
ML1 = MVWp 
ML2 = Mhh 
ML3 = Mhh 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcVWp(gt2)
coup3 = cplhhhhhh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, G0, VZ}
ML1 = MVWp 
ML2 = MG0 
ML3 = MVZ 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ, VZ}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = -cplHpcHpVZ(gt2,i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplHpcHpVZ(gt2,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], conj[VWp]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fu]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFuFdHpL(i3,i1,gt2)
coup2R = cplcFuFdHpR(i3,i1,gt2)
coup3L = cplcFuFuhhL(i2,i3)
coup3R = cplcFuFuhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[gWpC], bar[gZ], bar[gZ]}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgZgWCHp(gt2)
coup3 = cplcgZgZhh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gWp], bar[gWp]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgWpgWphh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0hhHpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0hhHpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhhhHpcHp1(gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplhhHpcVWpVP1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplhhHpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i2,gt1)
coup2 = cplA0HpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i2,gt1)
coup2 = cplH0HpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(i2,gt1)
coup2 = cplhhHpcHp(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplhhcHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplhhcHpVWpVZ1(gt1)
coup2 = cplHpcVWpVZ(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0HpcHp1(gt2,gt1)
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1._dp/2._dp)*AmpC 



! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0HpcHp1(gt2,gt1)
coup2 = cplG0G0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1._dp/2._dp)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0HpcHp1(gt2,gt1)
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1._dp/2._dp)*AmpC 



! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhHpcHp1(gt2,gt1)
coup2 = cplhhhhhh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1._dp/2._dp)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplHpHpcHpcHp1(gt2,i1,gt1,i2)
coup2 = cplhhHpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(gt2,gt1)
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 



! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplHpcHpVZVZ1(gt2,gt1)
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToHphh


Subroutine Amplitude_IR_VERTEX_Inert2_HpToHphh(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,               & 
& cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,               & 
& cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgZgWpcHp,    & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,     & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,     & 
& cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,       & 
& cplA0A0HpcHp1,cplA0hhHpcHp1,cplG0G0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,   & 
& cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,            & 
& cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFdFdhhL(3,3),   & 
& cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFuFuhhL(3,3),               & 
& cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),          & 
& cplcFeFvcHpR(3,3,2),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,    & 
& cplcgZgWpcHp(2),cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcHp(2), & 
& cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),     & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP(2,2),cplHpcVWpVP(2),   & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0HpcHp1(2,2),       & 
& cplA0hhHpcHp1(2,2),cplG0G0HpcHp1(2,2),cplH0H0HpcHp1(2,2),cplH0hhHpcHp1(2,2),           & 
& cplhhhhHpcHp1(2,2),cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),cplhhcHpVPVWp1(2),              & 
& cplhhcHpVWpVZ1(2),cplHpHpcHpcHp1(2,2,2,2),cplHpcHpcVWpVWp1(2,2),cplHpcHpVZVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = Mhh 


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplhhHpcHp(i3,i2)
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplHpcHpVP(gt2,i3)
coup3 = cplhhHpcVWp(i3)
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplhhcHpVWp(i2)
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp], conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplhhcVWpVWp
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplhhHpcVWpVP1(gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplhhcHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt2)
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2) = Amp(gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToHphh


Subroutine Amplitude_Tree_Inert2_HpTohhVWp(cplhhcHpVWp,Mhh,MHp,MVWp,Mhh2,             & 
& MHp2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,MHp(2),MVWp,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplhhcHpVWp(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = Mhh 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = -cplhhcHpVWp(gt1)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_Tree_Inert2_HpTohhVWp


Subroutine Gamma_Real_Inert2_HpTohhVWp(MLambda,em,gs,cplhhcHpVWp,Mhh,MHp,             & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplhhcHpVWp(2)

Real(dp), Intent(in) :: Mhh,MHp(2),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
Coup = cplhhcHpVWp(i1)
Mex1 = MHp(i1)
Mex2 = Mhh
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,1._dp,0._dp,1._dp,Coup,Gammarealphoton(i1),kont)
 GammarealGluon(i1) = 0._dp 
Else 
  GammarealGluon(i1) = 0._dp 
  GammarealPhoton(i1) = 0._dp 

End if 
End Do
End Subroutine Gamma_Real_Inert2_HpTohhVWp


Subroutine Amplitude_WAVE_Inert2_HpTohhVWp(cplhhcHpVWp,ctcplhhcHpVWp,Mhh,             & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,Zfhh,ZfHp,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplhhcHpVWp(2)

Complex(dp), Intent(in) :: ctcplhhcHpVWp(2)

Complex(dp), Intent(in) :: Zfhh,ZfHp(2,2),ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = Mhh 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhcHpVWp(gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplhhcHpVWp(i1)
End Do


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhcHpVWp(gt1)


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplhhcHpVWp(gt1)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_WAVE_Inert2_HpTohhVWp


Subroutine Amplitude_VERTEX_Inert2_HpTohhVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,             & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,       & 
& cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,             & 
& cplG0cHpVWp,cplcgZgAhh,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,            & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,              & 
& cplH0HpcHp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,      & 
& cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,     & 
& cplG0cHpVWpVZ1,cplhhhhcVWpVWp1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3), & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeVWpL(3,3),& 
& cplcFvFeVWpR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),               & 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0hhVZ,cplG0cHpVWp(2),  & 
& cplcgZgAhh,cplcgWCgAcHp(2),cplcgWpgWphh,cplcgZgWpcHp(2),cplcgWCgWChh,cplcgAgWCVWp,     & 
& cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp(2),cplH0H0hh,cplH0HpcHp(2,2),        & 
& cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,   & 
& cplhhVZVZ,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),  & 
& cplcVWpVWpVZ,cplG0cHpVWpVZ1(2),cplhhhhcVWpVWp1,cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),    & 
& cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = Mhh 
Mex3 = MVWp 


! {A0, conj[Hp], A0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0A0hh
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[Hp], H0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0H0hh
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Fu, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = -cplcFuFdVWpR(i3,i2)
coup3R = -cplcFuFdVWpL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {G0, conj[VWp], VZ}
ML1 = MG0 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplG0cHpVWp(gt1)
coup2 = -cplG0hhVZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {gWp, gZ, gWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgWphh
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {gZ, gWpC, gP}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgZgAhh
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {gZ, gWpC, gZ}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgZgZhh
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], A0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplA0H0hh
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp], H0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0H0hh
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], hh}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhhhhh
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], hh}
ML1 = Mhh 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhhhhh
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, A0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, H0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VZ, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplhhcHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplhhcHpVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplhhcHpVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, VWp}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhcVWpVWp
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VP, VWp}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplhhcVWpVWp
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VZ, VWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplhhcVWpVWp
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], G0}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = -cplG0hhVZ
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[Hp], VZ}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplhhVZVZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], VZ}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplhhVZVZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdhhL(i3,i1)
coup2R = cplcFdFdhhR(i3,i1)
coup3L = cplcFuFdVWpL(i2,i3)
coup3R = cplcFuFdVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[Fe], bar[Fv], bar[Fe]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFeFehhL(i3,i1)
coup2R = cplcFeFehhR(i3,i1)
coup3L = cplcFvFeVWpL(i2,i3)
coup3R = cplcFvFeVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[gWpC], bar[gP], bar[gWpC]}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcgWCgAcHp(gt1)
coup2 = cplcgWCgWChh
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[gWpC], bar[gZ], bar[gWpC]}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgWCgWChh
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gWp], bar[gZ]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgZgZhh
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplhhhhcVWpVWp1
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplhhcHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplhhcHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {G0, VZ}
ML1 = MG0 
ML2 = MVZ 
coup1 = cplG0cHpVWpVZ1(gt1)
coup2 = -cplG0hhVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(i1,gt1)
coup2 = cplhhcHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpTohhVWp


Subroutine Amplitude_IR_VERTEX_Inert2_HpTohhVWp(MA0,MFd,MFe,MFu,MG0,MH0,              & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,               & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0cHpVWp,cplcgZgAhh,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,               & 
& cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp,           & 
& cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,         & 
& cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,     & 
& cplcVWpVWpVZ,cplG0cHpVWpVZ1,cplhhhhcVWpVWp1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,             & 
& cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3), & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeVWpL(3,3),& 
& cplcFvFeVWpR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),               & 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0hhVZ,cplG0cHpVWp(2),  & 
& cplcgZgAhh,cplcgWCgAcHp(2),cplcgWpgWphh,cplcgZgWpcHp(2),cplcgWCgWChh,cplcgAgWCVWp,     & 
& cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp(2),cplH0H0hh,cplH0HpcHp(2,2),        & 
& cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,   & 
& cplhhVZVZ,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),  & 
& cplcVWpVWpVZ,cplG0cHpVWpVZ1(2),cplhhhhcVWpVWp1,cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),    & 
& cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = Mhh 
Mex3 = MVWp 


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = cplhhcHpVWp(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplhhHpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, VWp}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplhhcVWpVWp
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplhhcHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpTohhVWp


Subroutine Amplitude_Tree_Inert2_HpToHpVZ(cplHpcHpVZ,MHp,MVZ,MHp2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MHp(2),MVZ,MHp2(2),MVZ2

Complex(dp), Intent(in) :: cplHpcHpVZ(2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1 = -cplHpcHpVZ(gt2,gt1)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_HpToHpVZ


Subroutine Gamma_Real_Inert2_HpToHpVZ(MLambda,em,gs,cplHpcHpVZ,MHp,MVZ,               & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplHpcHpVZ(2,2)

Real(dp), Intent(in) :: MHp(2),MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2), GammarealGluon(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
Coup = cplHpcHpVZ(i2,i1)
Mex1 = MHp(i1)
Mex2 = MHp(i2)
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,1._dp,1._dp,0._dp,Coup,Gammarealphoton(i1,i2),kont)
 GammarealGluon(i1,i2) = 0._dp 
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_HpToHpVZ


Subroutine Amplitude_WAVE_Inert2_HpToHpVZ(cplHpcHpVP,cplHpcHpVZ,ctcplHpcHpVP,         & 
& ctcplHpcHpVZ,MHp,MHp2,MVP,MVP2,MVZ,MVZ2,ZfHp,ZfVPVZ,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MHp(2),MHp2(2),MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplHpcHpVP(2,2),cplHpcHpVZ(2,2)

Complex(dp), Intent(in) :: ctcplHpcHpVP(2,2),ctcplHpcHpVZ(2,2)

Complex(dp), Intent(in) :: ZfHp(2,2),ZfVPVZ,ZfVZ

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
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplHpcHpVZ(gt2,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplHpcHpVZ(gt2,i1)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplHpcHpVZ(i1,gt1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVPVZ*cplHpcHpVP(gt2,gt1)
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplHpcHpVZ(gt2,gt1)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToHpVZ


Subroutine Amplitude_VERTEX_Inert2_HpToHpVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,      & 
& cplcFdFdVZR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,              & 
& cplcgZgWCHp,cplcgWCgWCVZ,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,       & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,            & 
& cplA0cHpVWpVZ1,cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,            & 
& cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFuFdHpL(3,3,2),           & 
& cplcFuFdHpR(3,3,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFvFeHpL(3,3,2),               & 
& cplcFvFeHpR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),             & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),       & 
& cplcgWpgWpVZ,cplcgZgWpcHp(2),cplcgZgWCHp(2),cplcgWCgWCVZ,cplcgWpgZHp(2),               & 
& cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),         & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhVZVZ,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),& 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),           & 
& cplA0cHpVWpVZ1(2),cplG0HpcVWpVZ1(2),cplG0cHpVWpVZ1(2),cplH0HpcVWpVZ1(2),               & 
& cplH0cHpVWpVZ1(2),cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVZ1(2,2),              & 
& cplHpcHpVZVZ1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVZ 


! {A0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {A0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = -cplA0HpcVWp(gt2)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplA0cHpVWp(gt1)
coup2 = -cplA0HpcVWp(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Fu, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = cplcFuFdHpL(i1,i3,gt2)
coup2R = cplcFuFdHpR(i1,i3,gt2)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
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


! {Fv, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = 0._dp 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i2,i1,gt1)
coup1R = cplcFeFvcHpR(i2,i1,gt1)
coup2L = cplcFvFeHpL(i1,i3,gt2)
coup2R = cplcFvFeHpR(i1,i3,gt2)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
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


! {G0, conj[VWp], conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplG0cHpVWp(gt1)
coup2 = -cplG0HpcVWp(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {gZ, gWpC, gWpC}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgZgWCHp(gt2)
coup3 = cplcgWCgWCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {H0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = -cplH0HpcVWp(gt2)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplH0cHpVWp(gt1)
coup2 = -cplH0HpcVWp(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcHpVWp(gt1)
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Hp, H0, A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, A0, H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, hh, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplHpcHpVZ(gt2,i1)
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp], conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, H0, A0}
ML1 = MVWp 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0cHpVWp(gt1)
coup2 = -cplA0HpcVWp(gt2)
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, G0}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplhhcHpVWp(gt1)
coup2 = -cplG0HpcVWp(gt2)
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, A0, H0}
ML1 = MVWp 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0cHpVWp(gt1)
coup2 = -cplH0HpcVWp(gt2)
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, G0, hh}
ML1 = MVWp 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplG0cHpVWp(gt1)
coup2 = -cplhhHpcVWp(gt2)
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, VZ, hh}
ML1 = MVWp 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VWp, hh, VZ}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], conj[VWp]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fu]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFuFdHpL(i3,i1,gt2)
coup2R = cplcFuFdHpR(i3,i1,gt2)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
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


! {bar[Fe], bar[Fv], bar[Fv]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = 0._dp 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFvFeHpL(i3,i1,gt2)
coup2R = cplcFvFeHpR(i3,i1,gt2)
coup3L = cplcFvFvVZL(i2,i3)
coup3R = cplcFvFvVZR(i2,i3)
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


! {bar[gZ], bar[gWp], bar[gWp]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgWpgWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {A0, conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
coup1 = -cplA0cHpVWp(gt1)
coup2 = cplA0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {G0, conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
coup1 = -cplG0cHpVWp(gt1)
coup2 = cplG0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {H0, conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
coup1 = -cplH0cHpVWp(gt1)
coup2 = cplH0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplhhHpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplHpcHpVPVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplHpcHpVZVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {A0, conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
coup1 = cplA0cHpVWpVZ1(gt1)
coup2 = -cplA0HpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {G0, conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
coup1 = cplG0cHpVWpVZ1(gt1)
coup2 = -cplG0HpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {H0, conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
coup1 = cplH0cHpVWpVZ1(gt1)
coup2 = -cplH0HpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhcHpVWpVZ1(gt1)
coup2 = -cplhhHpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVZ1(i1,gt1)
coup2 = cplHpcHpVP(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = cplHpcHpVZVZ1(i1,gt1)
coup2 = cplHpcHpVZ(gt2,i1)
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
End Subroutine Amplitude_VERTEX_Inert2_HpToHpVZ


Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpVZ(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,             & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVZ,              & 
& cplcgZgWpcHp,cplcgZgWCHp,cplcgWCgWCVZ,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,             & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhVZVZ,cplHpcHpVP,       & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,               & 
& cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,cplH0HpcVWpVZ1,            & 
& cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFuFdHpL(3,3,2),           & 
& cplcFuFdHpR(3,3,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFvFeHpL(3,3,2),               & 
& cplcFvFeHpR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),             & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),       & 
& cplcgWpgWpVZ,cplcgZgWpcHp(2),cplcgZgWCHp(2),cplcgWCgWCVZ,cplcgWpgZHp(2),               & 
& cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),         & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhVZVZ,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),& 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),           & 
& cplA0cHpVWpVZ1(2),cplG0HpcVWpVZ1(2),cplG0cHpVWpVZ1(2),cplH0HpcVWpVZ1(2),               & 
& cplH0cHpVWpVZ1(2),cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVZ1(2,2),              & 
& cplHpcHpVZVZ1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVZ 


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcHpVZ(i3,i2)
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplcHpVWpVZ(i2)
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp], conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplcVWpVWpVZ
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplHpcHpVPVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVZ1(i1,gt1)
coup2 = cplHpcHpVP(gt2,i1)
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpVZ


Subroutine Amplitude_Tree_Inert2_HpToVZVWp(cplcHpVWpVZ,MHp,MVWp,MVZ,MHp2,             & 
& MVWp2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MHp(2),MVWp,MVZ,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcHpVWpVZ(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MVZ 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = cplcHpVWpVZ(gt1)
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_Tree_Inert2_HpToVZVWp


Subroutine Gamma_Real_Inert2_HpToVZVWp(MLambda,em,gs,cplcHpVWpVZ,MHp,MVWp,            & 
& MVZ,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcHpVWpVZ(2)

Real(dp), Intent(in) :: MHp(2),MVWp,MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
Coup = cplcHpVWpVZ(i1)
Mex1 = MHp(i1)
Mex2 = MVZ
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  GammarealGluon(i1) = 0._dp 
 Call hardphotonSVV(Mex1,Mex2,Mex3,MLambda,em,1._dp,0._dp,1._dp,Coup,Gammarealphoton(i1),kont)
Else 
  GammarealGluon(i1) = 0._dp 
  GammarealPhoton(i1) = 0._dp 

End if 
End Do
End Subroutine Gamma_Real_Inert2_HpToVZVWp


Subroutine Amplitude_WAVE_Inert2_HpToVZVWp(cplcHpVPVWp,cplcHpVWpVZ,ctcplcHpVPVWp,     & 
& ctcplcHpVWpVZ,MHp,MHp2,MVP,MVP2,MVWp,MVWp2,MVZ,MVZ2,ZfHp,ZfVWp,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MHp(2),MHp2(2),MVP,MVP2,MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcHpVPVWp(2),cplcHpVWpVZ(2)

Complex(dp), Intent(in) :: ctcplcHpVPVWp(2),ctcplcHpVWpVZ(2)

Complex(dp), Intent(in) :: ZfHp(2,2),ZfVWp,ZfVZ

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MVZ 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplcHpVWpVZ(gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplcHpVWpVZ(i1)
End Do


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplcHpVWpVZ(gt1)


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplcHpVWpVZ(gt1)


! Getting the amplitude 
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToVZVWp


Subroutine Amplitude_VERTEX_Inert2_HpToVZVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,             & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0H0VZ,cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,             & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,            & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplHpcVWpVZ,       & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,       & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,          & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),         & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),& 
& cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),& 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),             & 
& cplG0hhVZ,cplG0cHpVWp(2),cplcgWCgAcHp(2),cplcgWpgWpVZ,cplcgZgWpcHp(2),cplcgAgWCVWp,    & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0cHpVWp(2), & 
& cplhhHpcHp(2,2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP(2,2),cplHpcHpVZ(2,2), & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0cHpVWpVZ1(2),& 
& cplH0cHpVWpVZ1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVZ1(2,2),cplHpcHpcVWpVWp1(2,2),          & 
& cplHpcHpVZVZ1(2,2),cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q

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
Mex1 = MHp(gt1) 
Mex2 = MVZ 
Mex3 = MVWp 


! {A0, conj[Hp], H0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0H0VZ
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Fu, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = -cplcFuFuVZR(i1,i3)
coup2R = -cplcFuFuVZL(i1,i3)
coup3L = -cplcFuFdVWpR(i3,i2)
coup3R = -cplcFuFdVWpL(i3,i2)
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


! {Fv, Fe, Fv}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = 0._dp 
ML2 = MFe(i2) 
ML3 = 0._dp 
coup1L = cplcFeFvcHpL(i2,i1,gt1)
coup1R = cplcFeFvcHpR(i2,i1,gt1)
coup2L = -cplcFvFvVZR(i1,i3)
coup2R = -cplcFvFvVZL(i1,i3)
coup3L = -cplcFvFeVWpR(i3,i2)
coup3R = -cplcFvFeVWpL(i3,i2)
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


! {G0, conj[VWp], hh}
ML1 = MG0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = -cplG0cHpVWp(gt1)
coup2 = cplG0hhVZ
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {gWp, gZ, gWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgWpVZ
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], A0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = -cplA0H0VZ
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], G0}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = -cplG0hhVZ
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp], VZ}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhVZVZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], VZ}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MVZ 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplhhVZVZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, A0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, H0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VZ, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = -cplG0cHpVWp(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = -cplH0cHpVWp(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, VWp}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(gt1)
coup2 = -cplcVWpVWpVZ
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VP, VWp}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplcVWpVWpVZ
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VZ, VWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplcVWpVWpVZ
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], hh}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = -cplHpcHpVZ(i2,gt1)
coup2 = cplhhVZVZ
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], hh}
ML1 = MVZ 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplhhVZVZ
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVZL(i3,i1)
coup2R = cplcFdFdVZR(i3,i1)
coup3L = cplcFuFdVWpL(i2,i3)
coup3R = cplcFuFdVWpR(i2,i3)
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


! {bar[Fe], bar[Fv], bar[Fe]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFeFeVZL(i3,i1)
coup2R = cplcFeFeVZR(i3,i1)
coup3L = cplcFvFeVWpL(i2,i3)
coup3R = cplcFvFeVWpR(i2,i3)
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


! {bar[gWpC], bar[gP], bar[gWpC]}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcgWCgAcHp(gt1)
coup2 = cplcgWCgWCVZ
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[gWpC], bar[gZ], bar[gWpC]}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgWCgWCVZ
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0cHpVWpVZ1(i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0cHpVWpVZ1(i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhcHpVWpVZ1(i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplcVWpVPVWpVZ1Q
coup2a = coup2 
coup2 = cplcVWpVPVWpVZ2Q
coup2b = coup2 
coup2 = cplcVWpVPVWpVZ3Q
coup2c = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplcVWpVWpVZVZ1Q
coup2c = coup2 
coup2 = cplcVWpVWpVZVZ2Q
coup2b = coup2 
coup2 = cplcVWpVWpVZVZ3Q
coup2a = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {hh, VZ}
ML1 = Mhh 
ML2 = MVZ 
coup1 = cplhhcHpVWpVZ1(gt1)
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhcHpVWpVZ1(gt1)
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVZ1(i1,gt1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = cplHpcHpVZVZ1(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToVZVWp


Subroutine Amplitude_IR_VERTEX_Inert2_HpToVZVWp(MA0,MFd,MFe,MFu,MG0,MH0,              & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0H0VZ,cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,           & 
& cplcFdFdVZR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVZ,cplcgZgWpcHp,             & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,           & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,          & 
& cplH0cHpVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,            & 
& cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,  & 
& cplcVWpVWpVZVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ,cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),         & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),& 
& cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),& 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),             & 
& cplG0hhVZ,cplG0cHpVWp(2),cplcgWCgAcHp(2),cplcgWpgWpVZ,cplcgZgWpcHp(2),cplcgAgWCVWp,    & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0cHpVWp(2), & 
& cplhhHpcHp(2,2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP(2,2),cplHpcHpVZ(2,2), & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0cHpVWpVZ1(2),& 
& cplH0cHpVWpVZ1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVZ1(2,2),cplHpcHpcVWpVWp1(2,2),          & 
& cplHpcHpVZVZ1(2,2),cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q

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
Mex1 = MHp(gt1) 
Mex2 = MVZ 
Mex3 = MVWp 


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVZ(i3)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, VWp}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplcVWpVWpVZ
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplcVWpVPVWpVZ1Q
coup2a = coup2 
coup2 = cplcVWpVPVWpVZ2Q
coup2b = coup2 
coup2 = cplcVWpVPVWpVZ3Q
coup2c = coup2 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVZ1(i1,gt1)
coup2 = cplcHpVPVWp(i1)
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToVZVWp


Subroutine Amplitude_WAVE_Inert2_HpToG0Hp(MG0,MG02,MHp,MHp2,ZfG0,ZfHp,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,MHp(2),MHp2(2)

Complex(dp), Intent(in) :: ZfG0,ZfHp(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
    Do gt3=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MHp(gt3) 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
! Vanishing 
Amp(gt1, gt3) = 0._dp
    End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToG0Hp


Subroutine Amplitude_VERTEX_Inert2_HpToG0Hp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0G0,cplA0G0H0,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,cplcFeFeG0R,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,       & 
& cplcgZgWpcHp,cplcgZgWCHp,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,              & 
& cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,cplG0H0HpcHp1,         & 
& cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplG0cHpVPVWp1,cplG0cHpVWpVZ1,cplH0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFdFdG0L(3,3),   & 
& cplcFdFdG0R(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFeG0L(3,3),               & 
& cplcFeFeG0R(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),               & 
& cplcFuFuG0R(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),          & 
& cplcFeFvcHpR(3,3,2),cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,           & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgZgWpcHp(2),cplcgZgWCHp(2),cplcgWpgZHp(2),           & 
& cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),         & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),          & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0HpcHp1(2,2),cplA0G0HpcHp1(2,2),    & 
& cplG0H0HpcHp1(2,2),cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplG0cHpVPVWp1(2),              & 
& cplG0cHpVWpVZ1(2),cplH0H0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
    Do gt3=1,2
Amp(gt1, gt3) = 0._dp 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MHp(gt3) 


! {A0, conj[Hp], A0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0A0G0
coup3 = cplA0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], A0}
ML1 = MA0 
ML2 = MVWp 
ML3 = MA0 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0A0G0
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp], H0}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0G0H0
coup3 = cplH0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], H0}
ML1 = MA0 
ML2 = MVWp 
ML3 = MH0 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0G0H0
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {Fu, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFdHpL(i3,i2,gt3)
coup3R = cplcFuFdHpR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {G0, conj[VWp], hh}
ML1 = MG0 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplG0cHpVWp(gt1)
coup2 = cplG0G0hh
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {gWp, gZ, gWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgWpG0
coup3 = cplcgWpgZHp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], A0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplA0G0H0
coup3 = cplA0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], A0}
ML1 = MH0 
ML2 = MVWp 
ML3 = MA0 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplA0G0H0
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], H0}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplG0H0H0
coup3 = cplH0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], H0}
ML1 = MH0 
ML2 = MVWp 
ML3 = MH0 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplG0H0H0
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {hh, conj[VWp], G0}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MG0 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplG0G0hh
coup3 = -cplG0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {hh, conj[Hp], VZ}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = -cplG0hhVZ
coup3 = cplHpcHpVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], VZ}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplhhcHpVWp(gt1)
coup2 = -cplG0hhVZ
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {Hp, A0, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MVWp 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = -cplG0cHpVWp(i1)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Hp, H0, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MVWp 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = -cplG0cHpVWp(i1)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = -cplG0cHpVWp(i1)
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplHpcVWpVP(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i1,gt1)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplA0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplH0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplhhHpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplHpcHpVP(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplHpcHpVZ(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], hh}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = -cplG0hhVZ
coup3 = cplhhHpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], hh}
ML1 = MVZ 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplcHpVWpVZ(gt1)
coup2 = -cplG0hhVZ
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdG0L(i3,i1)
coup2R = cplcFdFdG0R(i3,i1)
coup3L = cplcFuFdHpL(i2,i3,gt3)
coup3R = cplcFuFdHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[Fe], bar[Fv], bar[Fe]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFeFeG0L(i3,i1)
coup2R = cplcFeFeG0R(i3,i1)
coup3L = cplcFvFeHpL(i2,i3,gt3)
coup3R = cplcFvFeHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[gWpC], bar[gZ], bar[gWpC]}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgWCgWCG0
coup3 = cplcgZgWCHp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0G0HpcHp1(gt3,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplG0H0HpcHp1(gt3,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplG0HpcVWpVP1(gt3)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplG0HpcVWpVZ1(gt3)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0HpcHp1(gt3,gt1)
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0HpcHp1(gt3,gt1)
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0G0HpcHp1(i2,gt1)
coup2 = cplA0HpcHp(gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplG0H0HpcHp1(i2,gt1)
coup2 = cplH0HpcHp(gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplG0cHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 



! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplG0cHpVWpVZ1(gt1)
coup2 = cplHpcVWpVZ(gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 

    End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToG0Hp


Subroutine Amplitude_IR_VERTEX_Inert2_HpToG0Hp(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0G0,cplA0G0H0,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdG0L,               & 
& cplcFdFdG0R,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,cplcFeFeG0R,cplcFvFeHpL,               & 
& cplcFvFeHpR,cplcFuFuG0L,cplcFuFuG0R,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,      & 
& cplG0cHpVWp,cplcgZgWpcHp,cplcgZgWCHp,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,              & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,            & 
& cplG0H0HpcHp1,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplG0cHpVPVWp1,cplG0cHpVWpVZ1,             & 
& cplH0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFdFdG0L(3,3),   & 
& cplcFdFdG0R(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFeG0L(3,3),               & 
& cplcFeFeG0R(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),               & 
& cplcFuFuG0R(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),          & 
& cplcFeFvcHpR(3,3,2),cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,           & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgZgWpcHp(2),cplcgZgWCHp(2),cplcgWpgZHp(2),           & 
& cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),         & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),          & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0HpcHp1(2,2),cplA0G0HpcHp1(2,2),    & 
& cplG0H0HpcHp1(2,2),cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplG0cHpVPVWp1(2),              & 
& cplG0cHpVWpVZ1(2),cplH0H0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
    Do gt3=1,2
Amp(gt1, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MG0 
Mex3 = MHp(gt3) 


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplHpcHpVP(i1,gt1)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplHpcVWpVP(gt3)
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplHpcHpVP(gt3,i3)
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplG0HpcVWpVP1(gt3)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplG0cHpVPVWp1(gt1)
coup2 = cplHpcVWpVP(gt3)
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt3) = Amp(gt1, gt3) + oo16pi2*(1)*AmpC 

    End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToG0Hp


Subroutine Amplitude_WAVE_Inert2_HpToHpVP(cplHpcHpVP,cplHpcHpVZ,ctcplHpcHpVP,         & 
& ctcplHpcHpVZ,MHp,MHp2,MVP,MVP2,ZfHp,ZfVP,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: MHp(2),MHp2(2),MVP,MVP2

Complex(dp), Intent(in) :: cplHpcHpVP(2,2),cplHpcHpVZ(2,2)

Complex(dp), Intent(in) :: ctcplHpcHpVP(2,2),ctcplHpcHpVZ(2,2)

Complex(dp), Intent(in) :: ZfHp(2,2),ZfVP,ZfVZVP

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
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVP 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplHpcHpVP(gt2,i1)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplHpcHpVP(i1,gt1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZVP*cplHpcHpVZ(gt2,gt1)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToHpVP


Subroutine Amplitude_VERTEX_Inert2_HpToHpVP(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVPL,cplcFdFdVPR,    & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0HpcVWp,cplG0cHpVWp,           & 
& cplcgWpgWpVP,cplcgZgWpcHp,cplcgZgWCHp,cplcgWCgWCVP,cplcgWpgZHp,cplcgWCgZcHp,           & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,               & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplG0HpcVWpVP1,cplG0cHpVPVWp1,cplH0HpcVWpVP1,            & 
& cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplHpcHpVPVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),  & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFucHpL(3,3,2),& 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0HpcVWp(2),            & 
& cplG0cHpVWp(2),cplcgWpgWpVP,cplcgZgWpcHp(2),cplcgZgWCHp(2),cplcgWCgWCVP,               & 
& cplcgWpgZHp(2),cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),          & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),          & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),             & 
& cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplG0HpcVWpVP1(2),cplG0cHpVPVWp1(2),               & 
& cplH0HpcVWpVP1(2),cplH0cHpVPVWp1(2),cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2),               & 
& cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVP 


! {A0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {A0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(gt1)
coup2 = cplA0HpcHp(gt2,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = -cplA0HpcVWp(gt2)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {A0, conj[VWp], conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplA0cHpVWp(gt1)
coup2 = -cplA0HpcVWp(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Fu, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = cplcFuFdHpL(i1,i3,gt2)
coup2R = cplcFuFdHpR(i1,i3,gt2)
coup3L = -cplcFdFdVPR(i3,i2)
coup3R = -cplcFdFdVPL(i3,i2)
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


! {Fv, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = 0._dp 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i2,i1,gt1)
coup1R = cplcFeFvcHpR(i2,i1,gt1)
coup2L = cplcFvFeHpL(i1,i3,gt2)
coup2R = cplcFvFeHpR(i1,i3,gt2)
coup3L = -cplcFeFeVPR(i3,i2)
coup3R = -cplcFeFeVPL(i3,i2)
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


! {G0, conj[VWp], conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplG0cHpVWp(gt1)
coup2 = -cplG0HpcVWp(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {gZ, gWpC, gWpC}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgZgWCHp(gt2)
coup3 = cplcgWCgWCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {H0, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {H0, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplH0cHpVWp(gt1)
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = -cplH0HpcVWp(gt2)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[VWp], conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplH0cHpVWp(gt1)
coup2 = -cplH0HpcVWp(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(gt1)
coup2 = cplhhHpcHp(gt2,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[VWp], conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcHpVWp(gt1)
coup2 = -cplhhHpcVWp(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp], conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {VZ, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVZ(i2,gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, conj[VWp], conj[VWp]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcVWpVZ(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fu]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFuFdHpL(i3,i1,gt2)
coup2R = cplcFuFdHpR(i3,i1,gt2)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
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


! {bar[gZ], bar[gWp], bar[gWp]}
ML1 = MVZ 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgWpgWpVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {A0, conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
coup1 = -cplA0cHpVWp(gt1)
coup2 = cplA0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {G0, conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
coup1 = -cplG0cHpVWp(gt1)
coup2 = cplG0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {H0, conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
coup1 = -cplH0cHpVWp(gt1)
coup2 = cplH0HpcVWpVP1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplhhHpcVWpVP1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplHpcHpVPVP1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplHpcHpVPVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {A0, conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
coup1 = cplA0cHpVPVWp1(gt1)
coup2 = -cplA0HpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {G0, conj[VWp]}
ML1 = MG0 
ML2 = MVWp 
coup1 = cplG0cHpVPVWp1(gt1)
coup2 = -cplG0HpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {H0, conj[VWp]}
ML1 = MH0 
ML2 = MVWp 
coup1 = cplH0cHpVPVWp1(gt1)
coup2 = -cplH0HpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhcHpVPVWp1(gt1)
coup2 = -cplhhHpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 



! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVP1(i1,gt1)
coup2 = cplHpcHpVP(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = cplHpcHpVPVZ1(i1,gt1)
coup2 = cplHpcHpVZ(gt2,i1)
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
End Subroutine Amplitude_VERTEX_Inert2_HpToHpVP


Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpVP(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVPL,           & 
& cplcFdFdVPR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0HpcVWp,           & 
& cplG0cHpVWp,cplcgWpgWpVP,cplcgZgWpcHp,cplcgZgWCHp,cplcgWCgWCVP,cplcgWpgZHp,            & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,    & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,    & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplG0HpcVWpVP1,cplG0cHpVPVWp1,cplH0HpcVWpVP1,            & 
& cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplHpcHpVPVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),  & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFucHpL(3,3,2),& 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0HpcVWp(2),            & 
& cplG0cHpVWp(2),cplcgWpgWpVP,cplcgZgWpcHp(2),cplcgZgWCHp(2),cplcgWCgWCVP,               & 
& cplcgWpgZHp(2),cplcgWCgZcHp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),          & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),          & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),             & 
& cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplG0HpcVWpVP1(2),cplG0cHpVPVWp1(2),               & 
& cplH0HpcVWpVP1(2),cplH0cHpVPVWp1(2),cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2),               & 
& cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2)

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
Mex1 = MHp(gt1) 
Mex2 = MHp(gt2) 
Mex3 = MVP 


! {VP, conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcHpVP(i3,i2)
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VP, conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVP 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcHpVP(gt2,i3)
coup3 = cplHpcVWpVP(i3)
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VP, conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplHpcHpVP(i2,gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplcHpVPVWp(i2)
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp], conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(gt2)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplHpcHpVPVP1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVP1(i1,gt1)
coup2 = cplHpcHpVP(gt2,i1)
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToHpVP


Subroutine Amplitude_WAVE_Inert2_HpToVPVWp(cplcHpVPVWp,cplcHpVWpVZ,ctcplcHpVPVWp,     & 
& ctcplcHpVWpVZ,MHp,MHp2,MVP,MVP2,MVWp,MVWp2,ZfHp,ZfVP,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MHp(2),MHp2(2),MVP,MVP2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplcHpVPVWp(2),cplcHpVWpVZ(2)

Complex(dp), Intent(in) :: ctcplcHpVPVWp(2),ctcplcHpVWpVZ(2)

Complex(dp), Intent(in) :: ZfHp(2,2),ZfVP,ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MHp(gt1) 
Mex2 = MVP 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplcHpVPVWp(gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt1))*cplcHpVPVWp(i1)
End Do


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVP*cplcHpVPVWp(gt1)


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplcHpVPVWp(gt1)


! Getting the amplitude 
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt1) = AmpC 
End Do
End Subroutine Amplitude_WAVE_Inert2_HpToVPVWp


Subroutine Amplitude_VERTEX_Inert2_HpToVPVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,             & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0HpcHp,cplA0cHpVWp,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,              & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0cHpVWp,cplcgWCgAcHp,          & 
& cplcgWpgWpVP,cplcgZgWpcHp,cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,         & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,               & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,   & 
& cplA0cHpVPVWp1,cplH0cHpVPVWp1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplHpcHpVPVZ1,              & 
& cplHpcHpcVWpVWp1,cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVWpVZ3Q,  & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3),   & 
& cplcFuFdVWpR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),& 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),             & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0cHpVWp(2),cplcgWCgAcHp(2),cplcgWpgWpVP,   & 
& cplcgZgWpcHp(2),cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp(2),   & 
& cplH0HpcHp(2,2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplhhcVWpVWp,            & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),cplcVWpVPVWp,            & 
& cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0cHpVPVWp1(2),cplH0cHpVPVWp1(2),cplhhcHpVPVWp1(2),     & 
& cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2),cplHpcHpcVWpVWp1(2,2),cplcVWpVPVPVWp3Q,          & 
& cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q

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
Mex1 = MHp(gt1) 
Mex2 = MVP 
Mex3 = MVWp 


! {Fu, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(i2,i1,gt1)
coup1R = cplcFdFucHpR(i2,i1,gt1)
coup2L = -cplcFuFuVPR(i1,i3)
coup2R = -cplcFuFuVPL(i1,i3)
coup3L = -cplcFuFdVWpR(i3,i2)
coup3R = -cplcFuFdVWpL(i3,i2)
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


! {gWp, gZ, gWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgWpcHp(gt1)
coup2 = cplcgWpgWpVP
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, A0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,gt1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, H0, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0HpcHp(i1,gt1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VZ, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, hh, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,gt1)
coup2 = cplcHpVPVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplcHpVPVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hp, VZ, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1 = -cplHpcHpVZ(i1,gt1)
coup2 = cplcHpVPVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, A0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, G0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = -cplG0cHpVWp(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, H0, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = -cplH0cHpVWp(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VZ, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, hh, VWp}
ML1 = MVWp 
ML2 = Mhh 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(gt1)
coup2 = cplcVWpVPVWp
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VP, VWp}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplcVWpVPVWp
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VZ, VWp}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplcVWpVPVWp
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFucHpL(i1,i2,gt1)
coup1R = cplcFdFucHpR(i1,i2,gt1)
coup2L = cplcFdFdVPL(i3,i1)
coup2R = cplcFdFdVPR(i3,i1)
coup3L = cplcFuFdVWpL(i2,i3)
coup3R = cplcFuFdVWpR(i2,i3)
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


! {bar[Fe], bar[Fv], bar[Fe]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = 0._dp 
ML3 = MFe(i3) 
coup1L = cplcFeFvcHpL(i1,i2,gt1)
coup1R = cplcFeFvcHpR(i1,i2,gt1)
coup2L = cplcFeFeVPL(i3,i1)
coup2R = cplcFeFeVPR(i3,i1)
coup3L = cplcFvFeVWpL(i2,i3)
coup3R = cplcFvFeVWpR(i2,i3)
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


! {bar[gWpC], bar[gP], bar[gWpC]}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcgWCgAcHp(gt1)
coup2 = cplcgWCgWCVP
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[gWpC], bar[gZ], bar[gWpC]}
ML1 = MVWp 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgWCgZcHp(gt1)
coup2 = cplcgWCgWCVP
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i2,gt1)
coup2 = cplA0cHpVPVWp1(i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0HpcHp(i2,gt1)
coup2 = cplH0cHpVPVWp1(i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i2,gt1)
coup2 = cplhhcHpVPVWp1(i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplcVWpVPVPVWp1Q
coup2c = coup2 
coup2 = cplcVWpVPVPVWp2Q
coup2a = coup2 
coup2 = cplcVWpVPVPVWp3Q
coup2b = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplcHpVWpVZ(gt1)
coup2 = cplcVWpVPVWpVZ1Q
coup2b = coup2 
coup2 = cplcVWpVPVWpVZ2Q
coup2c = coup2 
coup2 = cplcVWpVPVWpVZ3Q
coup2a = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplHpcHpcVWpVWp1(i1,gt1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhcHpVPVWp1(gt1)
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 



! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVP1(i1,gt1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = cplHpcHpVPVZ1(i1,gt1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_HpToVPVWp


Subroutine Amplitude_IR_VERTEX_Inert2_HpToVPVWp(MA0,MFd,MFe,MFu,MG0,MH0,              & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0HpcHp,cplA0cHpVWp,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,         & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0cHpVWp,cplcgWCgAcHp,          & 
& cplcgWpgWpVP,cplcgZgWpcHp,cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,         & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,               & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,   & 
& cplA0cHpVPVWp1,cplH0cHpVPVWp1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplHpcHpVPVZ1,              & 
& cplHpcHpcVWpVWp1,cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVWpVZ3Q,  & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3),   & 
& cplcFuFdVWpR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),& 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),             & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplG0cHpVWp(2),cplcgWCgAcHp(2),cplcgWpgWpVP,   & 
& cplcgZgWpcHp(2),cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp(2),   & 
& cplH0HpcHp(2,2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplhhcVWpVWp,            & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),cplcHpVPVWp(2),cplcVWpVPVWp,            & 
& cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0cHpVPVWp1(2),cplH0cHpVPVWp1(2),cplhhcHpVPVWp1(2),     & 
& cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2),cplHpcHpcVWpVWp1(2,2),cplcVWpVPVPVWp3Q,          & 
& cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q

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
Mex1 = MHp(gt1) 
Mex2 = MVP 
Mex3 = MVWp 


! {Hp, VP, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, VP, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1 = -cplHpcHpVP(i1,gt1)
coup2 = cplcHpVPVWp(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWp, VP, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVP 
ML3 = MHp(i3) 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplHpcVWpVP(i3)
coup3 = cplcHpVPVWp(i3)
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, VP, VWp}
ML1 = MVWp 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplcVWpVPVWp
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplcHpVPVWp(gt1)
coup2 = cplcVWpVPVPVWp1Q
coup2c = coup2 
coup2 = cplcVWpVPVPVWp2Q
coup2a = coup2 
coup2 = cplcVWpVPVPVWp3Q
coup2b = coup2 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplHpcHpVPVP1(i1,gt1)
coup2 = cplcHpVPVWp(i1)
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_HpToVPVWp



End Module OneLoopDecay_Hp_Inert2
