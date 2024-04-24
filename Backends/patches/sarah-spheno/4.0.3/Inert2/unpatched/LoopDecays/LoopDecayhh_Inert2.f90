! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:48 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecay_hh_Inert2
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

Subroutine Amplitude_Tree_Inert2_hhToA0A0(cplA0A0hh,MA0,Mhh,MA02,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MA02,Mhh2

Complex(dp), Intent(in) :: cplA0A0hh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MA0 
! Tree-Level Vertex 
coupT1 = cplA0A0hh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhToA0A0


Subroutine Gamma_Real_Inert2_hhToA0A0(MLambda,em,gs,cplA0A0hh,MA0,Mhh,GammarealPhoton,& 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0A0hh

Real(dp), Intent(in) :: MA0,Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplA0A0hh
Mex1 = Mhh
Mex2 = MA0
Mex3 = MA0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhToA0A0


Subroutine Amplitude_WAVE_Inert2_hhToA0A0(cplA0A0hh,ctcplA0A0hh,MA0,MA02,             & 
& Mhh,Mhh2,ZfA0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,Mhh,Mhh2

Complex(dp), Intent(in) :: cplA0A0hh

Complex(dp), Intent(in) :: ctcplA0A0hh

Complex(dp), Intent(in) :: ZfA0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MA0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0A0hh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplA0A0hh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0A0hh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0A0hh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToA0A0


Subroutine Amplitude_VERTEX_Inert2_hhToA0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,      & 
& cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,     & 
& cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2), & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,          & 
& cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1(2,2),cplA0A0cVWpVWp1,cplA0A0VZVZ1,             & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MA0 


! {A0, A0, G0}
ML1 = MA0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, G0}
ML1 = MA0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplA0A0G0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, hh}
ML1 = MA0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, hh}
ML1 = MA0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplA0A0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, A0}
ML1 = MG0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0G0hh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, H0}
ML1 = MG0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplG0G0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, VZ, H0}
ML1 = MG0 
ML2 = MVZ 
ML3 = MH0 
coup1 = cplG0hhVZ
coup2 = cplA0G0H0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, G0}
ML1 = MH0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, G0}
ML1 = MH0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplH0H0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, hh}
ML1 = MH0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, hh}
ML1 = MH0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, VZ}
ML1 = MH0 
ML2 = MH0 
ML3 = MVZ 
coup1 = cplH0H0hh
coup2 = -cplA0H0VZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, A0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhhhhh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, H0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhhhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplA0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplA0cHpVWp(i1)
coup3 = cplA0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplA0HpcVWp(i3)
coup3 = cplA0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplA0HpcVWp(i3)
coup3 = cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, H0}
ML1 = MVZ 
ML2 = MG0 
ML3 = MH0 
coup1 = cplG0hhVZ
coup2 = -cplA0H0VZ
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ, H0}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MH0 
coup1 = cplhhVZVZ
coup2 = -cplA0H0VZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcHp(i1,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplA0HpcVWp(i1)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplA0cHpVWp(i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplA0cHpVWp(i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0A0A01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplA0A0G0G01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplA0A0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplA0A0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0A0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplA0A0cVWpVWp1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplA0A0VZVZ1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0hh1
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hhhh1
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i1,i2)
coup2 = cplA0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0hh1
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hhhh1
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i1,i2)
coup2 = cplA0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToA0A0


Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,       & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,      & 
& cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,     & 
& cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2), & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,          & 
& cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1(2,2),cplA0A0cVWpVWp1,cplA0A0VZVZ1,             & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MA0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0A0


Subroutine Amplitude_Tree_Inert2_hhToH0A0(cplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,Mhh,MA02,MH02,Mhh2

Complex(dp), Intent(in) :: cplA0H0hh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MA0 
! Tree-Level Vertex 
coupT1 = cplA0H0hh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhToH0A0


Subroutine Gamma_Real_Inert2_hhToH0A0(MLambda,em,gs,cplA0H0hh,MA0,MH0,Mhh,            & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0H0hh

Real(dp), Intent(in) :: MA0,MH0,Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplA0H0hh
Mex1 = Mhh
Mex2 = MH0
Mex3 = MA0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhToH0A0


Subroutine Amplitude_WAVE_Inert2_hhToH0A0(cplA0H0hh,ctcplA0H0hh,MA0,MA02,             & 
& MH0,MH02,Mhh,Mhh2,ZfA0,ZfH0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,Mhh,Mhh2

Complex(dp), Intent(in) :: cplA0H0hh

Complex(dp), Intent(in) :: ctcplA0H0hh

Complex(dp), Intent(in) :: ZfA0,ZfH0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MA0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0H0hh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplA0H0hh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplA0H0hh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0H0hh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToH0A0


Subroutine Amplitude_VERTEX_Inert2_hhToH0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,         & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,          & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2), & 
& cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,         & 
& cplA0hhHpcHp1(2,2),cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MA0 


! {A0, A0, G0}
ML1 = MA0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, G0}
ML1 = MA0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, hh}
ML1 = MA0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, hh}
ML1 = MA0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, VZ}
ML1 = MA0 
ML2 = MH0 
ML3 = MVZ 
coup1 = cplA0H0hh
coup2 = cplA0H0VZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, A0}
ML1 = MG0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0G0hh
coup2 = cplA0G0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, H0}
ML1 = MG0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplG0G0hh
coup2 = cplG0H0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, VZ, H0}
ML1 = MG0 
ML2 = MVZ 
ML3 = MH0 
coup1 = cplG0hhVZ
coup2 = cplG0H0H0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, G0}
ML1 = MH0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, G0}
ML1 = MH0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplH0H0hh
coup2 = cplG0H0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, hh}
ML1 = MH0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, hh}
ML1 = MH0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, A0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhhhhh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, H0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhhhhh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplA0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplH0cHpVWp(i1)
coup3 = cplA0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplH0HpcVWp(i3)
coup3 = cplA0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplH0HpcVWp(i3)
coup3 = cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, A0}
ML1 = MVZ 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0hhVZ
coup2 = cplA0H0VZ
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcHp(i1,i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplH0HpcVWp(i1)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplH0cHpVWp(i3)
coup3 = cplA0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplH0cHpVWp(i3)
coup3 = cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0A0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplA0G0G0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplA0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0hh1
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hhhh1
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i1,i2)
coup2 = cplH0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0G0H0hh1
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0H0hhhh1
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplG0H0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplH0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i1,i2)
coup2 = cplA0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToH0A0


Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,       & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,         & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,          & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2), & 
& cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,         & 
& cplA0hhHpcHp1(2,2),cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MA0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0A0


Subroutine Amplitude_Tree_Inert2_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,MFd,               & 
& Mhh,MFd2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),Mhh,MFd2(3),Mhh2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3)

Complex(dp) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFdFdhhL(gt2,gt3)
coupT1R = cplcFdFdhhR(gt2,gt3)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_Tree_Inert2_hhTocFdFd


Subroutine Gamma_Real_Inert2_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,         & 
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
 
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFdFdhhL(i2,i3)
CoupR = cplcFdFdhhR(i2,i3)
Mex1 = Mhh
Mex2 = MFd(i2)
Mex3 = MFd(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,1._dp/3._dp,-1._dp/3._dp,1._dp/3._dp,CoupL,CoupR,Gammarealphoton(i2,i3),kont)
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,gs,0._dp,0._dp,0._dp,4._dp,-4._dp,4._dp,CoupL,CoupR,Gammarealgluon(i2,i3),kont)
Else 
  GammarealGluon(i2,i3) = 0._dp 
  GammarealPhoton(i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Subroutine Gamma_Real_Inert2_hhTocFdFd


Subroutine Amplitude_WAVE_Inert2_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,     & 
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

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFdhhL(gt2,gt3) 
ZcoupT1R = ctcplcFdFdhhR(gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1L = ZcoupT1L + 0.5_dp*Zfhh*cplcFdFdhhL(gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Zfhh*cplcFdFdhhR(gt2,gt3)


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDR(i1,gt2)*cplcFdFdhhL(i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDL(i1,gt2))*cplcFdFdhhR(i1,gt3)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt3)*cplcFdFdhhL(gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt3))*cplcFdFdhhR(gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_WAVE_Inert2_hhTocFdFd


Subroutine Amplitude_VERTEX_Inert2_hhTocFdFd(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,             & 
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
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 


! {G0, G0, Fd}
    Do i3=1,3
ML1 = MG0 
ML2 = MG0 
ML3 = MFd(i3) 
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(gt2,i3)
coup2R = cplcFdFdG0R(gt2,i3)
coup3L = cplcFdFdG0L(i3,gt3)
coup3R = cplcFdFdG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {G0, VZ, Fd}
    Do i3=1,3
ML1 = MG0 
ML2 = MVZ 
ML3 = MFd(i3) 
coup1 = -cplG0hhVZ
coup2L = cplcFdFdG0L(gt2,i3)
coup2R = cplcFdFdG0R(gt2,i3)
coup3L = cplcFdFdVZL(i3,gt3)
coup3R = cplcFdFdVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, Fd}
    Do i3=1,3
ML1 = Mhh 
ML2 = Mhh 
ML3 = MFd(i3) 
coup1 = cplhhhhhh
coup2L = cplcFdFdhhL(gt2,i3)
coup2R = cplcFdFdhhR(gt2,i3)
coup3L = cplcFdFdhhL(i3,gt3)
coup3R = cplcFdFdhhR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp, Fu}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MFu(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFdFucHpL(gt2,i3,i1)
coup2R = cplcFdFucHpR(gt2,i3,i1)
coup3L = cplcFuFdHpL(i3,gt3,i2)
coup3R = cplcFuFdHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Fu}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MFu(i3) 
coup1 = cplhhHpcVWp(i1)
coup2L = cplcFdFucHpL(gt2,i3,i1)
coup2R = cplcFdFucHpR(gt2,i3,i1)
coup3L = cplcFuFdVWpL(i3,gt3)
coup3R = cplcFuFdVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VWp, Hp, Fu}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MFu(i3) 
coup1 = cplhhcHpVWp(i2)
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFdHpL(i3,gt3,i2)
coup3R = cplcFuFdHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Fu}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVWp 
ML3 = MFu(i3) 
coup1 = cplhhcVWpVWp
coup2L = cplcFdFucVWpL(gt2,i3)
coup2R = cplcFdFucVWpR(gt2,i3)
coup3L = cplcFuFdVWpL(i3,gt3)
coup3R = cplcFuFdVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, Fd}
    Do i3=1,3
ML1 = MVZ 
ML2 = MG0 
ML3 = MFd(i3) 
coup1 = -cplG0hhVZ
coup2L = cplcFdFdVZL(gt2,i3)
coup2R = cplcFdFdVZR(gt2,i3)
coup3L = cplcFdFdG0L(i3,gt3)
coup3R = cplcFdFdG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, Fd}
    Do i3=1,3
ML1 = MVZ 
ML2 = MVZ 
ML3 = MFd(i3) 
coup1 = cplhhVZVZ
coup2L = cplcFdFdVZL(gt2,i3)
coup2R = cplcFdFdVZR(gt2,i3)
coup3L = cplcFdFdVZL(i3,gt3)
coup3R = cplcFdFdVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {bar[Fd], bar[Fd], G0}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MG0 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFdFdG0L(gt2,i1)
coup2R = cplcFdFdG0R(gt2,i1)
coup3L = cplcFdFdG0L(i2,gt3)
coup3R = cplcFdFdG0R(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], hh}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = Mhh 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFdFdhhL(gt2,i1)
coup2R = cplcFdFdhhR(gt2,i1)
coup3L = cplcFdFdhhL(i2,gt3)
coup3R = cplcFdFdhhR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVG 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVP 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVZ 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], conj[Hp]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MHp(i3) 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFdFucHpL(gt2,i1,i3)
coup2R = cplcFdFucHpR(gt2,i1,i3)
coup3L = cplcFuFdHpL(i2,gt3,i3)
coup3R = cplcFuFdHpR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fu], bar[Fu], conj[VWp]}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVWp 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFdFucVWpL(gt2,i1)
coup2R = cplcFdFucVWpR(gt2,i1)
coup3L = cplcFuFdVWpL(i2,gt3)
coup3R = cplcFuFdVWpR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTocFdFd


Subroutine Amplitude_IR_VERTEX_Inert2_hhTocFdFd(MFd,MFu,MG0,Mhh,MHp,MVG,              & 
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
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 


! {bar[Fd], bar[Fd], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVG 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFdFdVGL(gt2,i1)
coup2R = cplcFdFdVGR(gt2,i1)
coup3L = cplcFdFdVGL(i2,gt3)
coup3R = cplcFdFdVGR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVP 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFdFdVPL(gt2,i1)
coup2R = cplcFdFdVPR(gt2,i1)
coup3L = cplcFdFdVPL(i2,gt3)
coup3R = cplcFdFdVPR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTocFdFd


Subroutine Amplitude_Tree_Inert2_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,MFe,               & 
& Mhh,MFe2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),Mhh,MFe2(3),Mhh2

Complex(dp), Intent(in) :: cplcFeFehhL(3,3),cplcFeFehhR(3,3)

Complex(dp) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFeFehhL(gt2,gt3)
coupT1R = cplcFeFehhR(gt2,gt3)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_Tree_Inert2_hhTocFeFe


Subroutine Gamma_Real_Inert2_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,         & 
& MFe,Mhh,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFeFehhL(3,3),cplcFeFehhR(3,3)

Real(dp), Intent(in) :: MFe(3),Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFeFehhL(i2,i3)
CoupR = cplcFeFehhR(i2,i3)
Mex1 = Mhh
Mex2 = MFe(i2)
Mex3 = MFe(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,1._dp,-1._dp,1._dp,CoupL,CoupR,Gammarealphoton(i2,i3),kont)
  GammarealGluon(i2,i3) = 0._dp 
Else 
  GammarealGluon(i2,i3) = 0._dp 
  GammarealPhoton(i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Subroutine Gamma_Real_Inert2_hhTocFeFe


Subroutine Amplitude_WAVE_Inert2_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,ctcplcFeFehhL,     & 
& ctcplcFeFehhR,MFe,MFe2,Mhh,Mhh2,ZfEL,ZfER,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MFe2(3),Mhh,Mhh2

Complex(dp), Intent(in) :: cplcFeFehhL(3,3),cplcFeFehhR(3,3)

Complex(dp), Intent(in) :: ctcplcFeFehhL(3,3),ctcplcFeFehhR(3,3)

Complex(dp), Intent(in) :: ZfEL(3,3),ZfER(3,3),Zfhh

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFeFehhL(gt2,gt3) 
ZcoupT1R = ctcplcFeFehhR(gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1L = ZcoupT1L + 0.5_dp*Zfhh*cplcFeFehhL(gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Zfhh*cplcFeFehhR(gt2,gt3)


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfER(i1,gt2)*cplcFeFehhL(i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfEL(i1,gt2))*cplcFeFehhR(i1,gt3)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfEL(i1,gt3)*cplcFeFehhL(gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfER(i1,gt3))*cplcFeFehhR(gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_WAVE_Inert2_hhTocFeFe


Subroutine Amplitude_VERTEX_Inert2_hhTocFeFe(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,              & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,        & 
& cplhhcVWpVWp,cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MG0,Mhh,MHp(2),MVP,MVWp,MVZ,MFe2(3),MG02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),& 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),             & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp(2,2),   & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 


! {G0, G0, Fe}
    Do i3=1,3
ML1 = MG0 
ML2 = MG0 
ML3 = MFe(i3) 
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(gt2,i3)
coup2R = cplcFeFeG0R(gt2,i3)
coup3L = cplcFeFeG0L(i3,gt3)
coup3R = cplcFeFeG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {G0, VZ, Fe}
    Do i3=1,3
ML1 = MG0 
ML2 = MVZ 
ML3 = MFe(i3) 
coup1 = -cplG0hhVZ
coup2L = cplcFeFeG0L(gt2,i3)
coup2R = cplcFeFeG0R(gt2,i3)
coup3L = cplcFeFeVZL(i3,gt3)
coup3R = cplcFeFeVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, Fe}
    Do i3=1,3
ML1 = Mhh 
ML2 = Mhh 
ML3 = MFe(i3) 
coup1 = cplhhhhhh
coup2L = cplcFeFehhL(gt2,i3)
coup2R = cplcFeFehhR(gt2,i3)
coup3L = cplcFeFehhL(i3,gt3)
coup3R = cplcFeFehhR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp, Fv}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = 0._dp 
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFeFvcHpL(gt2,i3,i1)
coup2R = cplcFeFvcHpR(gt2,i3,i1)
coup3L = cplcFvFeHpL(i3,gt3,i2)
coup3R = cplcFvFeHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Fv}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = 0._dp 
coup1 = cplhhHpcVWp(i1)
coup2L = cplcFeFvcHpL(gt2,i3,i1)
coup2R = cplcFeFvcHpR(gt2,i3,i1)
coup3L = cplcFvFeVWpL(i3,gt3)
coup3R = cplcFvFeVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VWp, Hp, Fv}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = 0._dp 
coup1 = cplhhcHpVWp(i2)
coup2L = cplcFeFvcVWpL(gt2,i3)
coup2R = cplcFeFvcVWpR(gt2,i3)
coup3L = cplcFvFeHpL(i3,gt3,i2)
coup3R = cplcFvFeHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Fv}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVWp 
ML3 = 0._dp 
coup1 = cplhhcVWpVWp
coup2L = cplcFeFvcVWpL(gt2,i3)
coup2R = cplcFeFvcVWpR(gt2,i3)
coup3L = cplcFvFeVWpL(i3,gt3)
coup3R = cplcFvFeVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, Fe}
    Do i3=1,3
ML1 = MVZ 
ML2 = MG0 
ML3 = MFe(i3) 
coup1 = -cplG0hhVZ
coup2L = cplcFeFeVZL(gt2,i3)
coup2R = cplcFeFeVZR(gt2,i3)
coup3L = cplcFeFeG0L(i3,gt3)
coup3R = cplcFeFeG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, Fe}
    Do i3=1,3
ML1 = MVZ 
ML2 = MVZ 
ML3 = MFe(i3) 
coup1 = cplhhVZVZ
coup2L = cplcFeFeVZL(gt2,i3)
coup2R = cplcFeFeVZR(gt2,i3)
coup3L = cplcFeFeVZL(i3,gt3)
coup3R = cplcFeFeVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {bar[Fe], bar[Fe], G0}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MG0 
coup1L = cplcFeFehhL(i1,i2)
coup1R = cplcFeFehhR(i1,i2)
coup2L = cplcFeFeG0L(gt2,i1)
coup2R = cplcFeFeG0R(gt2,i1)
coup3L = cplcFeFeG0L(i2,gt3)
coup3R = cplcFeFeG0R(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fe], bar[Fe], hh}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = Mhh 
coup1L = cplcFeFehhL(i1,i2)
coup1R = cplcFeFehhR(i1,i2)
coup2L = cplcFeFehhL(gt2,i1)
coup2R = cplcFeFehhR(gt2,i1)
coup3L = cplcFeFehhL(i2,gt3)
coup3R = cplcFeFehhR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fe], bar[Fe], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVP 
coup1L = cplcFeFehhL(i1,i2)
coup1R = cplcFeFehhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fe], bar[Fe], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVZ 
coup1L = cplcFeFehhL(i1,i2)
coup1R = cplcFeFehhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTocFeFe


Subroutine Amplitude_IR_VERTEX_Inert2_hhTocFeFe(MFe,MG0,Mhh,MHp,MVP,MVWp,             & 
& MVZ,MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,              & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,        & 
& cplhhcVWpVWp,cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),MG0,Mhh,MHp(2),MVP,MVWp,MVZ,MFe2(3),MG02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),& 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),             & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp(2,2),   & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 


! {bar[Fe], bar[Fe], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVP 
coup1L = cplcFeFehhL(i1,i2)
coup1R = cplcFeFehhR(i1,i2)
coup2L = cplcFeFeVPL(gt2,i1)
coup2R = cplcFeFeVPR(gt2,i1)
coup3L = cplcFeFeVPL(i2,gt3)
coup3R = cplcFeFeVPR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTocFeFe


Subroutine Amplitude_Tree_Inert2_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,MFu,               & 
& Mhh,MFu2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),Mhh,MFu2(3),Mhh2

Complex(dp), Intent(in) :: cplcFuFuhhL(3,3),cplcFuFuhhR(3,3)

Complex(dp) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFuFuhhL(gt2,gt3)
coupT1R = cplcFuFuhhR(gt2,gt3)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_Tree_Inert2_hhTocFuFu


Subroutine Gamma_Real_Inert2_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,         & 
& MFu,Mhh,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFuhhL(3,3),cplcFuFuhhR(3,3)

Real(dp), Intent(in) :: MFu(3),Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFuFuhhL(i2,i3)
CoupR = cplcFuFuhhR(i2,i3)
Mex1 = Mhh
Mex2 = MFu(i2)
Mex3 = MFu(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,4._dp/3._dp,-4._dp/3._dp,4._dp/3._dp,CoupL,CoupR,Gammarealphoton(i2,i3),kont)
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,gs,0._dp,0._dp,0._dp,4._dp,-4._dp,4._dp,CoupL,CoupR,Gammarealgluon(i2,i3),kont)
Else 
  GammarealGluon(i2,i3) = 0._dp 
  GammarealPhoton(i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Subroutine Gamma_Real_Inert2_hhTocFuFu


Subroutine Amplitude_WAVE_Inert2_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,     & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,Zfhh,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),MFu2(3),Mhh,Mhh2

Complex(dp), Intent(in) :: cplcFuFuhhL(3,3),cplcFuFuhhR(3,3)

Complex(dp), Intent(in) :: ctcplcFuFuhhL(3,3),ctcplcFuFuhhR(3,3)

Complex(dp), Intent(in) :: Zfhh,ZfUL(3,3),ZfUR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFuhhL(gt2,gt3) 
ZcoupT1R = ctcplcFuFuhhR(gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1L = ZcoupT1L + 0.5_dp*Zfhh*cplcFuFuhhL(gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Zfhh*cplcFuFuhhR(gt2,gt3)


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUR(i1,gt2)*cplcFuFuhhL(i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUL(i1,gt2))*cplcFuFuhhR(i1,gt3)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt3)*cplcFuFuhhL(gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt3))*cplcFuFuhhR(gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_WAVE_Inert2_hhTocFuFu


Subroutine Amplitude_VERTEX_Inert2_hhTocFuFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,             & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),              & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),& 
& cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),             & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp(2,2),   & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 


! {G0, G0, Fu}
    Do i3=1,3
ML1 = MG0 
ML2 = MG0 
ML3 = MFu(i3) 
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(gt2,i3)
coup2R = cplcFuFuG0R(gt2,i3)
coup3L = cplcFuFuG0L(i3,gt3)
coup3R = cplcFuFuG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {G0, VZ, Fu}
    Do i3=1,3
ML1 = MG0 
ML2 = MVZ 
ML3 = MFu(i3) 
coup1 = -cplG0hhVZ
coup2L = cplcFuFuG0L(gt2,i3)
coup2R = cplcFuFuG0R(gt2,i3)
coup3L = cplcFuFuVZL(i3,gt3)
coup3R = cplcFuFuVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, Fu}
    Do i3=1,3
ML1 = Mhh 
ML2 = Mhh 
ML3 = MFu(i3) 
coup1 = cplhhhhhh
coup2L = cplcFuFuhhL(gt2,i3)
coup2R = cplcFuFuhhR(gt2,i3)
coup3L = cplcFuFuhhL(i3,gt3)
coup3R = cplcFuFuhhR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, Fu}
    Do i3=1,3
ML1 = MVZ 
ML2 = MG0 
ML3 = MFu(i3) 
coup1 = -cplG0hhVZ
coup2L = cplcFuFuVZL(gt2,i3)
coup2R = cplcFuFuVZR(gt2,i3)
coup3L = cplcFuFuG0L(i3,gt3)
coup3R = cplcFuFuG0R(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, Fu}
    Do i3=1,3
ML1 = MVZ 
ML2 = MVZ 
ML3 = MFu(i3) 
coup1 = cplhhVZVZ
coup2L = cplcFuFuVZL(gt2,i3)
coup2R = cplcFuFuVZR(gt2,i3)
coup3L = cplcFuFuVZL(i3,gt3)
coup3R = cplcFuFuVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {bar[Fd], bar[Fd], Hp}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MHp(i3) 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFuFdHpL(gt2,i1,i3)
coup2R = cplcFuFdHpR(gt2,i1,i3)
coup3L = cplcFdFucHpL(i2,gt3,i3)
coup3R = cplcFdFucHpR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fd], bar[Fd], VWp}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVWp 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFuFdVWpL(gt2,i1)
coup2R = cplcFuFdVWpR(gt2,i1)
coup3L = cplcFdFucVWpL(i2,gt3)
coup3R = cplcFdFucVWpR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], G0}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MG0 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFuFuG0L(gt2,i1)
coup2R = cplcFuFuG0R(gt2,i1)
coup3L = cplcFuFuG0L(i2,gt3)
coup3R = cplcFuFuG0R(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], hh}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = Mhh 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFuFuhhL(gt2,i1)
coup2R = cplcFuFuhhR(gt2,i1)
coup3L = cplcFuFuhhL(i2,gt3)
coup3R = cplcFuFuhhR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVG 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVP 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVZ 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
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
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[Hp], Fd}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = cplhhHpcHp(i2,i1)
coup2L = cplcFuFdHpL(gt2,i3,i1)
coup2R = cplcFuFdHpR(gt2,i3,i1)
coup3L = cplcFdFucHpL(i3,gt3,i2)
coup3R = cplcFdFucHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[Hp], conj[VWp], Fd}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = cplhhcHpVWp(i1)
coup2L = cplcFuFdHpL(gt2,i3,i1)
coup2R = cplcFuFdHpR(gt2,i3,i1)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[VWp], conj[Hp], Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = cplhhHpcVWp(i2)
coup2L = cplcFuFdVWpL(gt2,i3)
coup2R = cplcFuFdVWpR(gt2,i3)
coup3L = cplcFdFucHpL(i3,gt3,i2)
coup3R = cplcFdFucHpR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], Fd}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = cplhhcVWpVWp
coup2L = cplcFuFdVWpL(gt2,i3)
coup2R = cplcFuFdVWpR(gt2,i3)
coup3L = cplcFdFucVWpL(i3,gt3)
coup3R = cplcFdFucVWpR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTocFuFu


Subroutine Amplitude_IR_VERTEX_Inert2_hhTocFuFu(MFd,MFu,MG0,Mhh,MHp,MVG,              & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,    & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),              & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),& 
& cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),             & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp(2,2),   & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 


! {bar[Fu], bar[Fu], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVG 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFuFuVGL(gt2,i1)
coup2R = cplcFuFuVGR(gt2,i1)
coup3L = cplcFuFuVGL(i2,gt3)
coup3R = cplcFuFuVGR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVP 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFuFuVPL(gt2,i1)
coup2R = cplcFuFuVPR(gt2,i1)
coup3L = cplcFuFuVPL(i2,gt3)
coup3R = cplcFuFuVPR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTocFuFu


Subroutine Amplitude_Tree_Inert2_hhToG0G0(cplG0G0hh,MG0,Mhh,MG02,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,Mhh,MG02,Mhh2

Complex(dp), Intent(in) :: cplG0G0hh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MG0 
! Tree-Level Vertex 
coupT1 = cplG0G0hh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhToG0G0


Subroutine Gamma_Real_Inert2_hhToG0G0(MLambda,em,gs,cplG0G0hh,MG0,Mhh,GammarealPhoton,& 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplG0G0hh

Real(dp), Intent(in) :: MG0,Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplG0G0hh
Mex1 = Mhh
Mex2 = MG0
Mex3 = MG0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhToG0G0


Subroutine Amplitude_WAVE_Inert2_hhToG0G0(cplG0G0hh,ctcplG0G0hh,MG0,MG02,             & 
& Mhh,Mhh2,ZfG0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,Mhh,Mhh2

Complex(dp), Intent(in) :: cplG0G0hh

Complex(dp), Intent(in) :: ctcplG0G0hh

Complex(dp), Intent(in) :: ZfG0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MG0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplG0G0hh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplG0G0hh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfG0*cplG0G0hh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfG0*cplG0G0hh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToG0G0


Subroutine Amplitude_VERTEX_Inert2_hhToG0G0(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,             & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,       & 
& cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgWCgWChh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,      & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0G0G01,cplA0A0G0hh1,cplA0G0G0H01,cplA0G0H0hh1,            & 
& cplG0G0G0G01,cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1,cplG0G0cVWpVWp1,cplG0G0VZVZ1,     & 
& cplG0H0H0hh1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),            & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),  & 
& cplcFeFehhR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2), & 
& cplcgWpgWphh,cplcgWCgWChh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhcVWpVWp,            & 
& cplhhVZVZ,cplA0A0G0G01,cplA0A0G0hh1,cplA0G0G0H01,cplA0G0H0hh1,cplG0G0G0G01,            & 
& cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1(2,2),cplG0G0cVWpVWp1,cplG0G0VZVZ1,             & 
& cplG0H0H0hh1

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MG0 


! {A0, A0, A0}
ML1 = MA0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, A0}
ML1 = MA0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0A0G0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, H0}
ML1 = MA0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, H0}
ML1 = MA0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i3,i2)
coup3R = cplcFdFdG0R(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i3,i2)
coup3R = cplcFeFeG0R(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i3,i2)
coup3R = cplcFuFuG0R(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {G0, G0, hh}
ML1 = MG0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, VZ, hh}
ML1 = MG0 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplG0hhVZ
coup2 = cplG0G0hh
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpG0
coup3 = cplcgWpgWpG0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCG0
coup3 = cplcgWCgWCG0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {H0, A0, A0}
ML1 = MH0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, A0}
ML1 = MH0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0H0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, H0}
ML1 = MH0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, H0}
ML1 = MH0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplH0H0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, G0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplhhhhhh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, VZ}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplhhhhhh
coup2 = -cplG0hhVZ
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplG0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplG0HpcVWp(i3)
coup3 = cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, hh}
ML1 = MVZ 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplG0hhVZ
coup2 = -cplG0hhVZ
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ, hh}
ML1 = MVZ 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplhhVZVZ
coup2 = -cplG0hhVZ
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplG0HpcVWp(i1)
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplG0cHpVWp(i3)
coup3 = cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0G0G01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0G0G0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0G0G01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplG0G0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplG0G0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplG0G0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplG0G0cVWpVWp1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplG0G0VZVZ1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0G0hh1
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0G0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, hh}
ML1 = MG0 
ML2 = Mhh 
coup1 = cplG0G0hhhh1
coup2 = cplG0G0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplG0H0H0hh1
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0G0hh1
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0G0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, hh}
ML1 = MG0 
ML2 = Mhh 
coup1 = cplG0G0hhhh1
coup2 = cplG0G0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplG0H0H0hh1
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 

End Subroutine Amplitude_VERTEX_Inert2_hhToG0G0


Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0G0(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,         & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,       & 
& cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgWCgWChh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,      & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0G0G01,cplA0A0G0hh1,cplA0G0G0H01,cplA0G0H0hh1,            & 
& cplG0G0G0G01,cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1,cplG0G0cVWpVWp1,cplG0G0VZVZ1,     & 
& cplG0H0H0hh1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),            & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),  & 
& cplcFeFehhR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2), & 
& cplcgWpgWphh,cplcgWCgWChh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhcVWpVWp,            & 
& cplhhVZVZ,cplA0A0G0G01,cplA0A0G0hh1,cplA0G0G0H01,cplA0G0H0hh1,cplG0G0G0G01,            & 
& cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1(2,2),cplG0G0cVWpVWp1,cplG0G0VZVZ1,             & 
& cplG0H0H0hh1

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MG0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0G0


Subroutine Amplitude_Tree_Inert2_hhToG0VZ(cplG0hhVZ,MG0,Mhh,MVZ,MG02,Mhh2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,Mhh,MVZ,MG02,Mhh2,MVZ2

Complex(dp), Intent(in) :: cplG0hhVZ

Complex(dp) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1 = -cplG0hhVZ
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:) = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhToG0VZ


Subroutine Gamma_Real_Inert2_hhToG0VZ(MLambda,em,gs,cplG0hhVZ,MG0,Mhh,MVZ,            & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplG0hhVZ

Real(dp), Intent(in) :: MG0,Mhh,MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplG0hhVZ
Mex1 = Mhh
Mex2 = MG0
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
 GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhToG0VZ


Subroutine Amplitude_WAVE_Inert2_hhToG0VZ(cplG0hhVZ,ctcplG0hhVZ,MG0,MG02,             & 
& Mhh,Mhh2,MVZ,MVZ2,ZfG0,Zfhh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplG0hhVZ

Complex(dp), Intent(in) :: ctcplG0hhVZ

Complex(dp), Intent(in) :: ZfG0,Zfhh,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplG0hhVZ 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplG0hhVZ


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfG0*cplG0hhVZ


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplG0hhVZ


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,-ZcoupT1,AmpC) 
Amp(:) = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToG0VZ


Subroutine Amplitude_VERTEX_Inert2_hhToG0VZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,             & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,           & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,               & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,    & 
& cplcgWCgWCVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,      & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0G0VZVZ1,cplG0HpcVWpVZ1, & 
& cplG0cHpVWpVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),  & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeG0L(3,3),  & 
& cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,     & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,        & 
& cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplG0G0VZVZ1,     & 
& cplG0HpcVWpVZ1(2),cplG0cHpVWpVZ1(2),cplhhhhVZVZ1,cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MVZ 


! {A0, H0, A0}
ML1 = MA0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0A0G0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {A0, A0, H0}
ML1 = MA0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = -cplcFuFuVZR(i3,i2)
coup3R = -cplcFuFuVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {G0, G0, hh}
ML1 = MG0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {G0, VZ, hh}
ML1 = MG0 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplG0hhVZ
coup2 = cplG0G0hh
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpG0
coup3 = cplcgWpgWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCG0
coup3 = cplcgWCgWCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {H0, H0, A0}
ML1 = MH0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0H0hh
coup2 = cplA0G0H0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, A0, H0}
ML1 = MH0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, hh, G0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplhhhhhh
coup2 = cplG0G0hh
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, hh, VZ}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplhhhhhh
coup2 = cplG0hhVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplG0cHpVWp(i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplG0cHpVWp(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplG0HpcVWp(i3)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplG0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, hh}
ML1 = MVZ 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplG0hhVZ
coup2 = cplG0hhVZ
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {VZ, VZ, hh}
ML1 = MVZ 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplhhVZVZ
coup2 = cplG0hhVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplG0HpcVWp(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplG0HpcVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplG0cHpVWp(i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplG0cHpVWp(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {G0, VZ}
ML1 = MG0 
ML2 = MVZ 
coup1 = -cplG0hhVZ
coup2 = cplG0G0VZVZ1
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplG0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplG0HpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {hh, VZ}
ML1 = Mhh 
ML2 = MVZ 
coup1 = cplhhhhVZVZ1
coup2 = cplG0hhVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplG0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplG0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToG0VZ


Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0VZ(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,         & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,           & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,               & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,    & 
& cplcgWCgWCVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,      & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0G0VZVZ1,cplG0HpcVWpVZ1, & 
& cplG0cHpVWpVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),  & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeG0L(3,3),  & 
& cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,     & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,        & 
& cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplG0G0VZVZ1,     & 
& cplG0HpcVWpVZ1(2),cplG0cHpVWpVZ1(2),cplhhhhVZVZ1,cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0VZ


Subroutine Amplitude_Tree_Inert2_hhToH0H0(cplH0H0hh,MH0,Mhh,MH02,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MH02,Mhh2

Complex(dp), Intent(in) :: cplH0H0hh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MH0 
! Tree-Level Vertex 
coupT1 = cplH0H0hh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhToH0H0


Subroutine Gamma_Real_Inert2_hhToH0H0(MLambda,em,gs,cplH0H0hh,MH0,Mhh,GammarealPhoton,& 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplH0H0hh

Real(dp), Intent(in) :: MH0,Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplH0H0hh
Mex1 = Mhh
Mex2 = MH0
Mex3 = MH0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhToH0H0


Subroutine Amplitude_WAVE_Inert2_hhToH0H0(cplH0H0hh,ctcplH0H0hh,MH0,MH02,             & 
& Mhh,Mhh2,ZfH0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MH02,Mhh,Mhh2

Complex(dp), Intent(in) :: cplH0H0hh

Complex(dp), Intent(in) :: ctcplH0H0hh

Complex(dp), Intent(in) :: ZfH0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MH0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplH0H0hh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplH0H0hh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplH0H0hh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplH0H0hh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToH0H0


Subroutine Amplitude_VERTEX_Inert2_hhToH0H0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,           & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,      & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,         & 
& cplH0H0HpcHp1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,      & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),               & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,        & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),   & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MH0 


! {A0, A0, G0}
ML1 = MA0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, G0}
ML1 = MA0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, hh}
ML1 = MA0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, hh}
ML1 = MA0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, VZ}
ML1 = MA0 
ML2 = MA0 
ML3 = MVZ 
coup1 = cplA0A0hh
coup2 = cplA0H0VZ
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, A0}
ML1 = MG0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0G0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, VZ, A0}
ML1 = MG0 
ML2 = MVZ 
ML3 = MA0 
coup1 = cplG0hhVZ
coup2 = cplA0G0H0
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, H0}
ML1 = MG0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplG0G0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, G0}
ML1 = MH0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, G0}
ML1 = MH0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplH0H0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, hh}
ML1 = MH0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, hh}
ML1 = MH0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, A0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplhhhhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, H0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplhhhhhh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplH0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplH0cHpVWp(i1)
coup3 = cplH0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplH0HpcVWp(i3)
coup3 = cplH0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplH0HpcVWp(i3)
coup3 = cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, A0}
ML1 = MVZ 
ML2 = MG0 
ML3 = MA0 
coup1 = cplG0hhVZ
coup2 = cplA0H0VZ
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ, A0}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MA0 
coup1 = cplhhVZVZ
coup2 = cplA0H0VZ
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcHp(i1,i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplH0HpcVWp(i1)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplH0cHpVWp(i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplH0cHpVWp(i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplH0H0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplH0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0H0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplH0H0cVWpVWp1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplH0H0VZVZ1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0G0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplG0H0H0hh1
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplH0H0hhhh1
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i1,i2)
coup2 = cplH0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0G0H0hh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplG0H0H0hh1
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplH0H0hhhh1
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i1,i2)
coup2 = cplH0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToH0H0


Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0H0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,       & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,      & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,         & 
& cplH0H0HpcHp1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,      & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),               & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,        & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),   & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MH0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0H0


Subroutine Amplitude_Tree_Inert2_hhTohhhh(cplhhhhhh,Mhh,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2

Complex(dp), Intent(in) :: cplhhhhhh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = Mhh 
! Tree-Level Vertex 
coupT1 = cplhhhhhh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhTohhhh


Subroutine Gamma_Real_Inert2_hhTohhhh(MLambda,em,gs,cplhhhhhh,Mhh,GammarealPhoton,    & 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplhhhhhh

Real(dp), Intent(in) :: Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplhhhhhh
Mex1 = Mhh
Mex2 = Mhh
Mex3 = Mhh
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhTohhhh


Subroutine Amplitude_WAVE_Inert2_hhTohhhh(cplhhhhhh,ctcplhhhhhh,Mhh,Mhh2,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2

Complex(dp), Intent(in) :: cplhhhhhh

Complex(dp), Intent(in) :: ctcplhhhhhh

Complex(dp), Intent(in) :: Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = Mhh 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhhhhh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhhhhh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhhhhh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhhhhh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhTohhhh


Subroutine Amplitude_VERTEX_Inert2_hhTohhhh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,             & 
& cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,     & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,          & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,   & 
& cplG0G0hhhh1,cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,   & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),            & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,cplG0G0hhhh1,          & 
& cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1(2,2),cplhhhhcVWpVWp1,cplhhhhVZVZ1

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = Mhh 


! {A0, A0, A0}
ML1 = MA0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, A0}
ML1 = MA0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0A0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, H0}
ML1 = MA0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, H0}
ML1 = MA0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i3,i2)
coup3R = cplcFdFdhhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i3,i2)
coup3R = cplcFeFehhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i3,i2)
coup3R = cplcFuFuhhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {G0, G0, G0}
ML1 = MG0 
ML2 = MG0 
ML3 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, VZ, G0}
ML1 = MG0 
ML2 = MVZ 
ML3 = MG0 
coup1 = cplG0hhVZ
coup2 = cplG0G0hh
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0, VZ}
ML1 = MG0 
ML2 = MG0 
ML3 = MVZ 
coup1 = cplG0G0hh
coup2 = cplG0hhVZ
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, VZ, VZ}
ML1 = MG0 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplG0hhVZ
coup2 = cplG0hhVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWphh
coup3 = cplcgWpgWphh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWChh
coup3 = cplcgWCgWChh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {gZ, gZ, gZ}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplcgZgZhh
coup2 = cplcgZgZhh
coup3 = cplcgZgZhh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {H0, A0, A0}
ML1 = MH0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, A0}
ML1 = MH0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, H0}
ML1 = MH0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, H0}
ML1 = MH0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, hh, hh}
ML1 = Mhh 
ML2 = Mhh 
ML3 = Mhh 
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplhhcHpVWp(i1)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = -cplhhcHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplhhHpcVWp(i3)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplhhHpcVWp(i3)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplhhcVWpVWp
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {VZ, G0, G0}
ML1 = MVZ 
ML2 = MG0 
ML3 = MG0 
coup1 = cplG0hhVZ
coup2 = cplG0hhVZ
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ, G0}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MG0 
coup1 = cplhhVZVZ
coup2 = cplG0hhVZ
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, G0, VZ}
ML1 = MVZ 
ML2 = MG0 
ML3 = MVZ 
coup1 = cplG0hhVZ
coup2 = cplhhVZVZ
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplhhVZVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplhhHpcHp(i1,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplhhHpcVWp(i1)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = -cplhhHpcVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplhhcHpVWp(i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplhhcHpVWp(i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplH0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplhhhhhhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhhhHpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplhhhhcVWpVWp1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplhhhhVZVZ1
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hhhh1
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hhhh1
coup2 = cplG0G0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hhhh1
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhhhh1
coup2 = cplhhhhhh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(i1,i2)
coup2 = cplhhHpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhhhcVWpVWp1
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhhhVZVZ1
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hhhh1
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hhhh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hhhh1
coup2 = cplG0G0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hhhh1
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhhhh1
coup2 = cplhhhhhh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(i1,i2)
coup2 = cplhhHpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhhhcVWpVWp1
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhhhVZVZ1
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 

End Subroutine Amplitude_VERTEX_Inert2_hhTohhhh


Subroutine Amplitude_IR_VERTEX_Inert2_hhTohhhh(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,         & 
& cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,     & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,          & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,   & 
& cplG0G0hhhh1,cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,   & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),            & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,cplG0G0hhhh1,          & 
& cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1(2,2),cplhhhhcVWpVWp1,cplhhhhVZVZ1

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = Mhh 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTohhhh


Subroutine Amplitude_Tree_Inert2_hhTocHpHp(cplhhHpcHp,Mhh,MHp,Mhh2,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,MHp(2),Mhh2,MHp2(2)

Complex(dp), Intent(in) :: cplhhHpcHp(2,2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 
! Tree-Level Vertex 
coupT1 = cplhhHpcHp(gt3,gt2)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_Tree_Inert2_hhTocHpHp


Subroutine Gamma_Real_Inert2_hhTocHpHp(MLambda,em,gs,cplhhHpcHp,Mhh,MHp,              & 
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
 
  Do i2=2,2
    Do i3=2,2
Coup = cplhhHpcHp(i3,i2)
Mex1 = Mhh
Mex2 = MHp(i2)
Mex3 = MHp(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSS(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,1._dp,-1._dp,1._dp,Coup,Gammarealphoton(i2,i3),kont)
  GammarealGluon(i2,i3) = 0._dp 
Else 
  GammarealGluon(i2,i3) = 0._dp 
  GammarealPhoton(i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Subroutine Gamma_Real_Inert2_hhTocHpHp


Subroutine Amplitude_WAVE_Inert2_hhTocHpHp(cplhhHpcHp,ctcplhhHpcHp,Mhh,               & 
& Mhh2,MHp,MHp2,Zfhh,ZfHp,Amp)

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

  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhHpcHp(gt3,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhHpcHp(gt3,gt2)


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt2))*cplhhHpcHp(gt3,i1)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt3)*cplhhHpcHp(i1,gt2)
End Do


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_WAVE_Inert2_hhTocHpHp


Subroutine Amplitude_VERTEX_Inert2_hhTocHpHp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,             & 
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
  Do gt2=1,2
    Do gt3=1,2
Amp(gt2, gt3) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 


! {A0, A0, Hp}
    Do i3=1,2
ML1 = MA0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplA0HpcHp(i3,gt2)
coup3 = cplA0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {A0, H0, Hp}
    Do i3=1,2
ML1 = MA0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplA0HpcHp(i3,gt2)
coup3 = cplH0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {A0, A0, VWp}
ML1 = MA0 
ML2 = MA0 
ML3 = MVWp 
coup1 = cplA0A0hh
coup2 = cplA0cHpVWp(gt2)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {A0, H0, VWp}
ML1 = MA0 
ML2 = MH0 
ML3 = MVWp 
coup1 = cplA0H0hh
coup2 = cplA0cHpVWp(gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3,gt2)
coup2R = cplcFdFucHpR(i1,i3,gt2)
coup3L = cplcFuFdHpL(i3,i2,gt3)
coup3R = cplcFuFdHpR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(3)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFvcHpL(i1,i3,gt2)
coup2R = cplcFeFvcHpR(i1,i3,gt2)
coup3L = cplcFvFeHpL(i3,i2,gt3)
coup3R = cplcFvFeHpR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {G0, G0, VWp}
ML1 = MG0 
ML2 = MG0 
ML3 = MVWp 
coup1 = cplG0G0hh
coup2 = cplG0cHpVWp(gt2)
coup3 = -cplG0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {G0, VZ, VWp}
ML1 = MG0 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplG0hhVZ
coup2 = cplG0cHpVWp(gt2)
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {gWpC, gWpC, gZ}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgZcHp(gt2)
coup3 = cplcgZgWCHp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {gZ, gZ, gWp}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgZhh
coup2 = cplcgZgWpcHp(gt2)
coup3 = cplcgWpgZHp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {H0, A0, Hp}
    Do i3=1,2
ML1 = MH0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplH0HpcHp(i3,gt2)
coup3 = cplA0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {H0, H0, Hp}
    Do i3=1,2
ML1 = MH0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0H0hh
coup2 = cplH0HpcHp(i3,gt2)
coup3 = cplH0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {H0, A0, VWp}
ML1 = MH0 
ML2 = MA0 
ML3 = MVWp 
coup1 = cplA0H0hh
coup2 = cplH0cHpVWp(gt2)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {H0, H0, VWp}
ML1 = MH0 
ML2 = MH0 
ML3 = MVWp 
coup1 = cplH0H0hh
coup2 = cplH0cHpVWp(gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {hh, hh, Hp}
    Do i3=1,2
ML1 = Mhh 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhhhhh
coup2 = cplhhHpcHp(i3,gt2)
coup3 = cplhhHpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, VWp}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhhhhh
coup2 = cplhhcHpVWp(gt2)
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {VZ, VZ, Hp}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplhhVZVZ
coup2 = cplHpcHpVZ(i3,gt2)
coup3 = cplHpcHpVZ(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, G0, VWp}
ML1 = MVZ 
ML2 = MG0 
ML3 = MVWp 
coup1 = cplG0hhVZ
coup2 = cplcHpVWpVZ(gt2)
coup3 = -cplG0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {VZ, VZ, VWp}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplhhVZVZ
coup2 = cplcHpVWpVZ(gt2)
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {bar[Fu], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFdFucHpL(i3,i1,gt2)
coup2R = cplcFdFucHpR(i3,i1,gt2)
coup3L = cplcFuFdHpL(i2,i3,gt3)
coup3R = cplcFuFdHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[gWp], bar[gWp], bar[gZ]}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWpgWphh
coup2 = cplcgZgWpcHp(gt2)
coup3 = cplcgWpgZHp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gZ], bar[gWpC]}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgZhh
coup2 = cplcgWCgZcHp(gt2)
coup3 = cplcgZgWCHp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[Hp], A0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplA0HpcHp(i1,gt2)
coup3 = cplA0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], A0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MA0 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcHp(i1,gt2)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hp], conj[Hp], H0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplH0HpcHp(i1,gt2)
coup3 = cplH0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], H0}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MH0 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcHp(i1,gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hp], conj[Hp], hh}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplhhHpcHp(i1,gt2)
coup3 = cplhhHpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = Mhh 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplhhHpcHp(i1,gt2)
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hp], conj[Hp], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcHpVP(i1,gt2)
coup3 = cplHpcHpVP(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplHpcHpVP(i1,gt2)
coup3 = cplHpcVWpVP(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hp], conj[Hp], VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcHpVZ(i1,gt2)
coup3 = cplHpcHpVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVZ 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplHpcHpVZ(i1,gt2)
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], A0}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplA0cHpVWp(gt2)
coup3 = cplA0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], A0}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MA0 
coup1 = cplhhcVWpVWp
coup2 = cplA0cHpVWp(gt2)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[VWp], G0}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MG0 
coup1 = cplhhcVWpVWp
coup2 = cplG0cHpVWp(gt2)
coup3 = -cplG0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[Hp], H0}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplH0cHpVWp(gt2)
coup3 = cplH0HpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], H0}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MH0 
coup1 = cplhhcVWpVWp
coup2 = cplH0cHpVWp(gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[Hp], hh}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplhhcHpVWp(gt2)
coup3 = cplhhHpcHp(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], hh}
ML1 = MVWp 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplhhcVWpVWp
coup2 = cplhhcHpVWp(gt2)
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[Hp], VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplcHpVPVWp(gt2)
coup3 = cplHpcHpVP(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], VP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcVWpVWp
coup2 = cplcHpVPVWp(gt2)
coup3 = cplHpcVWpVP(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[Hp], VZ}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplcHpVWpVZ(gt2)
coup3 = cplHpcHpVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], VZ}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplhhcVWpVWp
coup2 = cplcHpVWpVZ(gt2)
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0HpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0HpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplH0H0HpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplhhhhHpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpHpcHpcHp1(gt3,i2,gt2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplHpcHpcVWpVWp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplHpcHpVZVZ1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, Hp}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(gt3,i2)
coup2 = cplA0HpcHp(i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {H0, Hp}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(gt3,i2)
coup2 = cplH0HpcHp(i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {hh, Hp}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(gt3,i2)
coup2 = cplhhHpcHp(i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {VP, VWp}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(gt3)
coup2 = cplcHpVPVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 



! {VZ, VWp}
ML1 = MVZ 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(gt3)
coup2 = cplcHpVWpVZ(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 



! {A0, conj[Hp]}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i2,gt2)
coup2 = cplA0HpcHp(gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {H0, conj[Hp]}
  Do i2=1,2
ML1 = MH0 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i2,gt2)
coup2 = cplH0HpcHp(gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {hh, conj[Hp]}
  Do i2=1,2
ML1 = Mhh 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(i2,gt2)
coup2 = cplhhHpcHp(gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do


! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplhhcHpVPVWp1(gt2)
coup2 = cplHpcVWpVP(gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 



! {VWp, VZ}
ML1 = MVWp 
ML2 = MVZ 
coup1 = cplhhcHpVWpVZ1(gt2)
coup2 = cplHpcVWpVZ(gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTocHpHp


Subroutine Amplitude_IR_VERTEX_Inert2_hhTocHpHp(MA0,MFd,MFe,MFu,MG0,MH0,              & 
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
  Do gt2=1,2
    Do gt3=1,2
Amp(gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 


! {conj[Hp], conj[Hp], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcHpVP(i1,gt2)
coup3 = cplHpcHpVP(gt3,i2)
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplHpcHpVP(i1,gt2)
coup3 = cplHpcVWpVP(gt3)
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplcHpVPVWp(gt2)
coup3 = cplHpcHpVP(gt3,i2)
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], VP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcVWpVWp
coup2 = cplcHpVPVWp(gt2)
coup3 = cplHpcVWpVP(gt3)
Call Amp_VERTEX_StoSS_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {VP, VWp}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(gt3)
coup2 = cplcHpVPVWp(gt2)
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 



! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplhhcHpVPVWp1(gt2)
coup2 = cplHpcVWpVP(gt3)
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTocHpHp


Subroutine Amplitude_Tree_Inert2_hhToHpcVWp(cplhhHpcVWp,Mhh,MHp,MVWp,Mhh2,            & 
& MHp2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,MHp(2),MVWp,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplhhHpcVWp(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,2
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = cplhhHpcVWp(gt2)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt2) = AmpC 
  End Do
End Subroutine Amplitude_Tree_Inert2_hhToHpcVWp


Subroutine Gamma_Real_Inert2_hhToHpcVWp(MLambda,em,gs,cplhhHpcVWp,Mhh,MHp,            & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplhhHpcVWp(2)

Real(dp), Intent(in) :: Mhh,MHp(2),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
  Do i2=2,2
Coup = cplhhHpcVWp(i2)
Mex1 = Mhh
Mex2 = MHp(i2)
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,0._dp,1._dp,-1._dp,Coup,Gammarealphoton(i2),kont)
 GammarealGluon(i2) = 0._dp 
Else 
  GammarealGluon(i2) = 0._dp 
  GammarealPhoton(i2) = 0._dp 

End if 
  End Do
End Subroutine Gamma_Real_Inert2_hhToHpcVWp


Subroutine Amplitude_WAVE_Inert2_hhToHpcVWp(cplhhHpcVWp,ctcplhhHpcVWp,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,Zfhh,ZfHp,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplhhHpcVWp(2)

Complex(dp), Intent(in) :: ctcplhhHpcVWp(2)

Complex(dp), Intent(in) :: Zfhh,ZfHp(2,2),ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

  Do gt2=1,2
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhHpcVWp(gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhHpcVWp(gt2)


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplhhHpcVWp(i1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplhhHpcVWp(gt2)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt2) = AmpC 
  End Do
End Subroutine Amplitude_WAVE_Inert2_hhToHpcVWp


Subroutine Amplitude_VERTEX_Inert2_hhToHpcVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,            & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,        & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,         & 
& cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,               & 
& cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,      & 
& cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,     & 
& cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3), & 
& cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFehhL(3,3),cplcFeFehhR(3,3),               & 
& cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),               & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),           & 
& cplG0hhVZ,cplG0HpcVWp(2),cplcgZgAhh,cplcgWpgAHp(2),cplcgWpgWphh,cplcgAgWpcVWp,         & 
& cplcgZgWpcVWp,cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcVWp,     & 
& cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),     & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),  & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplG0HpcVWpVZ1(2),cplhhhhcVWpVWp1,            & 
& cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,2
Amp(:,gt2) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MVWp 


! {A0, A0, conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplA0HpcHp(gt2,i3)
coup3 = -cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, H0, conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplA0HpcHp(gt2,i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {Fu, Fu, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3,gt2)
coup2R = cplcFuFdHpR(i1,i3,gt2)
coup3L = -cplcFdFucVWpR(i3,i2)
coup3R = -cplcFdFucVWpL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {G0, VZ, conj[VWp]}
ML1 = MG0 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplG0hhVZ
coup2 = -cplG0HpcVWp(gt2)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {gWp, gWp, gP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgAHp(gt2)
coup3 = cplcgAgWpcVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {gWp, gWp, gZ}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgZgWpcVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {gZ, gZ, gWpC}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgZhh
coup2 = cplcgZgWCHp(gt2)
coup3 = cplcgWCgZcVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {H0, A0, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplH0HpcHp(gt2,i3)
coup3 = -cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, H0, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0H0hh
coup2 = cplH0HpcHp(gt2,i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhhhhh
coup2 = cplhhHpcHp(gt2,i3)
coup3 = -cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, conj[VWp]}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhhhhh
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {Hp, Hp, A0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(gt2,i1)
coup3 = cplA0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp, H0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(gt2,i1)
coup3 = cplH0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = Mhh 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplhhHpcHp(gt2,i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, Hp, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpVP(gt2,i1)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplHpcHpVP(gt2,i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hp, Hp, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpVZ(gt2,i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVZ 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplHpcHpVZ(gt2,i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, A0}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplA0HpcVWp(gt2)
coup3 = cplA0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, Hp, G0}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplG0HpcVWp(gt2)
coup3 = cplG0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, Hp, H0}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplH0HpcVWp(gt2)
coup3 = cplH0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, Hp, hh}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, hh}
ML1 = MVWp 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplhhcVWpVWp
coup2 = -cplhhHpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {VWp, Hp, VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcVWpVWp
coup2 = cplHpcVWpVP(gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {VWp, Hp, VZ}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VZ}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplhhcVWpVWp
coup2 = cplHpcVWpVZ(gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {VZ, G0, conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplG0hhVZ
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = -cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplhhVZVZ
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, conj[VWp]}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplhhVZVZ
coup2 = cplHpcVWpVZ(gt2)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {bar[Fd], bar[Fd], bar[Fu]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdhhL(i1,i2)
coup1R = cplcFdFdhhR(i1,i2)
coup2L = cplcFuFdHpL(i3,i1,gt2)
coup2R = cplcFuFdHpR(i3,i1,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(3)*AmpC 
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
coup1L = cplcFeFehhL(i1,i2)
coup1R = cplcFeFehhR(i1,i2)
coup2L = cplcFvFeHpL(i3,i1,gt2)
coup2R = cplcFvFeHpR(i3,i1,gt2)
coup3L = cplcFeFvcVWpL(i2,i3)
coup3R = cplcFeFvcVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[gWpC], bar[gWpC], bar[gZ]}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWCgWChh
coup2 = cplcgZgWCHp(gt2)
coup3 = cplcgWCgZcVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gP], bar[gWp]}
ML1 = MVZ 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcgZgAhh
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgAgWpcVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gZ], bar[gWp]}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgZhh
coup2 = cplcgWpgZHp(gt2)
coup3 = cplcgZgWpcVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {G0, VZ}
ML1 = MG0 
ML2 = MVZ 
coup1 = -cplG0hhVZ
coup2 = cplG0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplHpcHpcVWpVWp1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
End Do


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhhhcVWpVWp1
coup2 = -cplhhHpcVWp(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 



! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplHpcHpVP(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 

End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplHpcHpVZ(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToHpcVWp


Subroutine Amplitude_IR_VERTEX_Inert2_hhToHpcVWp(MA0,MFd,MFe,MFu,MG0,MH0,             & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplcFdFdhhL,cplcFdFdhhR,               & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& cplG0hhVZ,cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,cplcgWpgWphh,cplcgAgWpcVWp,               & 
& cplcgZgWpcVWp,cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcVWp,           & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,         & 
& cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,     & 
& cplcVWpVWpVZ,cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,             & 
& cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3), & 
& cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFehhL(3,3),cplcFeFehhR(3,3),               & 
& cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),               & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),           & 
& cplG0hhVZ,cplG0HpcVWp(2),cplcgZgAhh,cplcgWpgAHp(2),cplcgWpgWphh,cplcgAgWpcVWp,         & 
& cplcgZgWpcVWp,cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcVWp,     & 
& cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),     & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),  & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplG0HpcVWpVZ1(2),cplhhhhcVWpVWp1,            & 
& cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,2
Amp(:,gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MHp(gt2) 
Mex3 = MVWp 


! {Hp, Hp, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpVP(gt2,i1)
coup3 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplHpcHpVP(gt2,i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcVWpVWp
coup2 = cplHpcVWpVP(gt2)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplHpcHpVP(gt2,i1)
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToHpcVWp


Subroutine Amplitude_Tree_Inert2_hhTocVWpVWp(cplhhcVWpVWp,Mhh,MVWp,Mhh2,              & 
& MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,MVWp,Mhh2,MVWp2

Complex(dp), Intent(in) :: cplhhcVWpVWp

Complex(dp) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MVWp 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = cplhhcVWpVWp
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:) = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhTocVWpVWp


Subroutine Gamma_Real_Inert2_hhTocVWpVWp(MLambda,em,gs,cplhhcVWpVWp,Mhh,              & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplhhcVWpVWp

Real(dp), Intent(in) :: Mhh,MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplhhcVWpVWp
Mex1 = Mhh
Mex2 = MVWp
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  GammarealGluon = 0._dp 
 Call hardphotonSVV(Mex1,Mex2,Mex3,MLambda,em,0._dp,-1._dp,1._dp,Coup,Gammarealphoton,kont)
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhTocVWpVWp


Subroutine Amplitude_WAVE_Inert2_hhTocVWpVWp(cplhhcVWpVWp,ctcplhhcVWpVWp,             & 
& Mhh,Mhh2,MVWp,MVWp2,Zfhh,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplhhcVWpVWp

Complex(dp), Intent(in) :: ctcplhhcVWpVWp

Complex(dp), Intent(in) :: Zfhh,ZfVWp

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MVWp 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhcVWpVWp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhcVWpVWp


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfVWp)*cplhhcVWpVWp


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplhhcVWpVWp


! Getting the amplitude 
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:) = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhTocVWpVWp


Subroutine Amplitude_VERTEX_Inert2_hhTocVWpVWp(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,     & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,       & 
& cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,               & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,         & 
& cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,         & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,& 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),  & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeVWpL(3,3),& 
& cplcFvFeVWpR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),& 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),              & 
& cplG0cHpVWp(2),cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWphh,cplcgAgWpcVWp,       & 
& cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,          & 
& cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),       & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP(2),cplHpcVWpVZ(2),    & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0A0cVWpVWp1,               & 
& cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),   & 
& cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2),cplcVWpcVWpVWpVWp1Q,         & 
& cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,             & 
& cplcVWpVWpVZVZ1Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MVWp 
Mex3 = MVWp 


! {A0, A0, Hp}
    Do i3=1,2
ML1 = MA0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplA0HpcVWp(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {A0, H0, Hp}
    Do i3=1,2
ML1 = MA0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplA0HpcVWp(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Fd, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = -cplcFdFucVWpR(i1,i3)
coup2R = -cplcFdFucVWpL(i1,i3)
coup3L = -cplcFuFdVWpR(i3,i2)
coup3R = -cplcFuFdVWpL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(3)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = -cplcFeFvcVWpR(i1,i3)
coup2R = -cplcFeFvcVWpL(i1,i3)
coup3L = -cplcFvFeVWpR(i3,i2)
coup3R = -cplcFvFeVWpL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {G0, G0, Hp}
    Do i3=1,2
ML1 = MG0 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplG0G0hh
coup2 = cplG0HpcVWp(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {G0, VZ, Hp}
    Do i3=1,2
ML1 = MG0 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = -cplG0hhVZ
coup2 = cplG0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {gP, gZ, gWp}
ML1 = MVP 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgAhh
coup2 = cplcgAgWpcVWp
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {gWpC, gWpC, gP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgAcVWp
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {gWpC, gWpC, gZ}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgZcVWp
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {gZ, gZ, gWp}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgZhh
coup2 = cplcgZgWpcVWp
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, A0, Hp}
    Do i3=1,2
ML1 = MH0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplH0HpcVWp(i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {H0, H0, Hp}
    Do i3=1,2
ML1 = MH0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplH0H0hh
coup2 = cplH0HpcVWp(i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, Hp}
    Do i3=1,2
ML1 = Mhh 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplhhhhhh
coup2 = cplhhHpcVWp(i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {hh, hh, VWp}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplhhhhhh
coup2 = cplhhcVWpVWp
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {VZ, G0, Hp}
    Do i3=1,2
ML1 = MVZ 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = -cplG0hhVZ
coup2 = cplHpcVWpVZ(i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, Hp}
    Do i3=1,2
ML1 = MVZ 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplhhVZVZ
coup2 = cplHpcVWpVZ(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, VWp}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplhhVZVZ
coup2 = cplcVWpVWpVZ
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {bar[Fu], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuhhL(i1,i2)
coup1R = cplcFuFuhhR(i1,i2)
coup2L = cplcFdFucVWpL(i3,i1)
coup2R = cplcFdFucVWpR(i3,i1)
coup3L = cplcFuFdVWpL(i2,i3)
coup3R = cplcFuFdVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[gWp], bar[gWp], bar[gP]}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplcgWpgWphh
coup2 = cplcgAgWpcVWp
coup3 = cplcgWpgAVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {bar[gWp], bar[gWp], bar[gZ]}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplcgWpgWphh
coup2 = cplcgZgWpcVWp
coup3 = cplcgWpgZVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gP], bar[gWpC]}
ML1 = MVZ 
ML2 = MVP 
ML3 = MVWp 
coup1 = cplcgZgAhh
coup2 = cplcgWCgZcVWp
coup3 = cplcgAgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {bar[gZ], bar[gZ], bar[gWpC]}
ML1 = MVZ 
ML2 = MVZ 
ML3 = MVWp 
coup1 = cplcgZgZhh
coup2 = cplcgWCgZcVWp
coup3 = cplcgZgWCVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[Hp], A0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplA0HpcVWp(i1)
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[Hp], G0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplG0HpcVWp(i1)
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[Hp], H0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplH0HpcVWp(i1)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[Hp], hh}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplhhHpcVWp(i1)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplhhcHpVWp(i1)
coup2 = -cplhhHpcVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hp], conj[Hp], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hp], conj[Hp], VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcVWpVZ(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcVWpVZ(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], hh}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplhhHpcVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], hh}
ML1 = MVWp 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplhhcVWpVWp
coup2 = cplhhcVWpVWp
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[Hp], VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcVWp(i2)
coup2 = cplcVWpVPVWp
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], VP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVPVWp
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {conj[VWp], conj[Hp], VZ}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplhhHpcVWp(i2)
coup2 = -cplcVWpVWpVZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], VZ}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplhhcVWpVWp
coup2 = -cplcVWpVWpVZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0cVWpVWp1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0cVWpVWp1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplH0H0cVWpVWp1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplhhhhcVWpVWp1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpcVWpVWp1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpcVWpVWpVWp1Q
coup2b = coup2 
coup2 = cplcVWpcVWpVWpVWp2Q
coup2a = coup2 
coup2 = cplcVWpcVWpVWpVWp3Q
coup2c = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplhhVZVZ
coup2 = cplcVWpVWpVZVZ1Q
coup2a = coup2 
coup2 = cplcVWpVWpVZVZ2Q
coup2b = coup2 
coup2 = cplcVWpVWpVZVZ3Q
coup2c = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, VWp}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhhhcVWpVWp1
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 



! {VP, Hp}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do


! {VZ, Hp}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do


! {hh, conj[VWp]}
ML1 = Mhh 
ML2 = MVWp 
coup1 = cplhhhhcVWpVWp1
coup2 = cplhhcVWpVWp
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 



! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {Hp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVZ 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTocVWpVWp


Subroutine Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp(MA0,MFd,MFe,MFu,MG0,MH0,            & 
& Mhh,MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,               & 
& MVZ2,cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,     & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,       & 
& cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,               & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,         & 
& cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,         & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,& 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MFd2(3),MFe2(3),        & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),  & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeVWpL(3,3),& 
& cplcFvFeVWpR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),& 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),              & 
& cplG0cHpVWp(2),cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWphh,cplcgAgWpcVWp,       & 
& cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,          & 
& cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhhhhh,cplhhHpcHp(2,2),       & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP(2),cplHpcVWpVZ(2),    & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0A0cVWpVWp1,               & 
& cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),   & 
& cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2),cplcVWpcVWpVWpVWp1Q,         & 
& cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,             & 
& cplcVWpVWpVZVZ1Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MVWp 
Mex3 = MVWp 


! {conj[Hp], conj[Hp], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcHpVPVWp(i2)
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplhhHpcVWp(i2)
coup2 = cplcVWpVPVWp
coup3 = cplcHpVPVWp(i2)
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWp], conj[VWp], VP}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVPVWp
coup3 = cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {VP, Hp}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplcHpVPVWp(i1)
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp


Subroutine Amplitude_Tree_Inert2_hhToVZVZ(cplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,MVZ,Mhh2,MVZ2

Complex(dp), Intent(in) :: cplhhVZVZ

Complex(dp) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MVZ 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1 = cplhhVZVZ
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:) = AmpC 
End Subroutine Amplitude_Tree_Inert2_hhToVZVZ


Subroutine Gamma_Real_Inert2_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,Mhh,MVZ,GammarealPhoton,& 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplhhVZVZ

Real(dp), Intent(in) :: Mhh,MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplhhVZVZ
Mex1 = Mhh
Mex2 = MVZ
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  GammarealGluon = 0._dp 
 Gammarealphoton = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_hhToVZVZ


Subroutine Amplitude_WAVE_Inert2_hhToVZVZ(cplhhVZVZ,ctcplhhVZVZ,Mhh,Mhh2,             & 
& MVZ,MVZ2,Zfhh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplhhVZVZ

Complex(dp), Intent(in) :: ctcplhhVZVZ

Complex(dp), Intent(in) :: Zfhh,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MVZ 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplhhVZVZ 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplhhVZVZ


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplhhVZVZ


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplhhVZVZ


! Getting the amplitude 
Call TreeAmp_StoVV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:) = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToVZVZ


Subroutine Amplitude_VERTEX_Inert2_hhToVZVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,             & 
& cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,         & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplG0G0VZVZ1,             & 
& cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0VZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplG0G0hh,         & 
& cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,               & 
& cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,        & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0A0VZVZ1,               & 
& cplG0G0VZVZ1,cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2),            & 
& cplHpcHpVZVZ1(2,2),cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MVZ 
Mex3 = MVZ 


! {A0, A0, H0}
ML1 = MA0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0H0VZ
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {G0, G0, hh}
ML1 = MG0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplG0G0hh
coup2 = cplG0hhVZ
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {G0, VZ, hh}
ML1 = MG0 
ML2 = MVZ 
ML3 = Mhh 
coup1 = -cplG0hhVZ
coup2 = cplG0hhVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpVZ
coup3 = cplcgWpgWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCVZ
coup3 = cplcgWCgWCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {H0, H0, A0}
ML1 = MH0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0H0hh
coup2 = -cplA0H0VZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, hh, G0}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplhhhhhh
coup2 = -cplG0hhVZ
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, hh, VZ}
ML1 = Mhh 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplhhhhhh
coup2 = cplhhVZVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhHpcVWp(i1)
coup2 = -cplHpcHpVZ(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplcHpVWpVZ(i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplcHpVWpVZ(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplHpcVWpVZ(i3)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplHpcVWpVZ(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhcHpVWp(i2)
coup2 = -cplcVWpVWpVZ
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = -cplcVWpVWpVZ
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {VZ, G0, hh}
ML1 = MVZ 
ML2 = MG0 
ML3 = Mhh 
coup1 = -cplG0hhVZ
coup2 = cplhhVZVZ
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {VZ, VZ, hh}
ML1 = MVZ 
ML2 = MVZ 
ML3 = Mhh 
coup1 = cplhhVZVZ
coup2 = cplhhVZVZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcHpVZ(i1,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcVWpVZ(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcVWpVZ(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcVWp(i2)
coup2 = cplcHpVWpVZ(i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplcHpVWpVZ(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcVWp(i2)
coup2 = cplcVWpVWpVZ
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0VZVZ1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplG0G0hh
coup2 = cplG0G0VZVZ1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplH0H0VZVZ1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {hh, hh}
ML1 = Mhh 
ML2 = Mhh 
coup1 = cplhhhhhh
coup2 = cplhhhhVZVZ1
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1._dp/2._dp)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpVZVZ1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVWpVZVZ1Q
coup2a = coup2 
coup2 = cplcVWpVWpVZVZ2Q
coup2b = coup2 
coup2 = cplcVWpVWpVZVZ3Q
coup2c = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, VZ}
ML1 = Mhh 
ML2 = MVZ 
coup1 = cplhhhhVZVZ1
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do


! {hh, VZ}
ML1 = Mhh 
ML2 = MVZ 
coup1 = cplhhhhVZVZ1
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 



! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToVZVZ


Subroutine Amplitude_IR_VERTEX_Inert2_hhToVZVZ(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,         & 
& cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,         & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplG0G0VZVZ1,             & 
& cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),            & 
& MFu2(3),MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0VZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplG0G0hh,         & 
& cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,               & 
& cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ,        & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0A0VZVZ1,               & 
& cplG0G0VZVZ1,cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2),            & 
& cplHpcHpVZVZ1(2,2),cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MVZ 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToVZVZ


Subroutine Amplitude_WAVE_Inert2_hhToA0G0(MA0,MA02,MG0,MG02,Mhh,Mhh2,ZfA0,            & 
& ZfG0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MG0,MG02,Mhh,Mhh2

Complex(dp), Intent(in) :: ZfA0,ZfG0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MG0 
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
Amp = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToA0G0


Subroutine Amplitude_VERTEX_Inert2_hhToA0G0(MA0,MG0,Mhh,MHp,MVWp,MA02,MG02,           & 
& Mhh2,MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0G0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,Mhh,MHp(2),MVWp,MA02,MG02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),          & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplA0G0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MG0 


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplA0cHpVWp(i1)
coup3 = cplG0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplA0HpcVWp(i3)
coup3 = cplG0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcHp(i1,i3)
coup3 = cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplA0HpcVWp(i1)
coup3 = cplG0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplA0cHpVWp(i3)
coup3 = cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0G0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToA0G0


Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0G0(MA0,MG0,Mhh,MHp,MVWp,MA02,             & 
& MG02,Mhh2,MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,       & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0G0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,Mhh,MHp(2),MVWp,MA02,MG02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),          & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplA0G0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MG0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0G0


Subroutine Amplitude_WAVE_Inert2_hhToA0hh(MA0,MA02,Mhh,Mhh2,ZfA0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,Mhh,Mhh2

Complex(dp), Intent(in) :: ZfA0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = Mhh 
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
Amp = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToA0hh


Subroutine Amplitude_VERTEX_Inert2_hhToA0hh(MA0,Mhh,MHp,MVWp,MA02,Mhh2,               & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplA0hhHpcHp1,cplhhhhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MHp(2),MVWp,MA02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplA0hhHpcHp1(2,2),cplhhhhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = Mhh 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplA0cHpVWp(i1)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = -cplA0cHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplA0HpcVWp(i3)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplA0HpcVWp(i3)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcHp(i1,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplA0HpcVWp(i1)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = -cplA0HpcVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplA0cHpVWp(i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplA0cHpVWp(i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0hhHpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(i1,i2)
coup2 = cplA0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0hhHpcHp1(i1,i2)
coup2 = cplhhHpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToA0hh


Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0hh(MA0,Mhh,MHp,MVWp,MA02,Mhh2,            & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplA0hhHpcHp1,cplhhhhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MHp(2),MVWp,MA02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplA0hhHpcHp1(2,2),cplhhhhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = Mhh 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0hh


Subroutine Amplitude_WAVE_Inert2_hhToA0VP(MA0,MA02,Mhh,Mhh2,MVP,MVP2,ZfA0,            & 
& Zfhh,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,Mhh,Mhh2,MVP,MVP2

Complex(dp), Intent(in) :: ZfA0,Zfhh,ZfVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MA0 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToA0VP


Subroutine Amplitude_VERTEX_Inert2_hhToA0VP(MA0,Mhh,MHp,MVP,MVWp,MA02,Mhh2,           & 
& MHp2,MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,              & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MHp(2),MVP,MVWp,MA02,Mhh2,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),             & 
& cplcVWpVPVWp,cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MVP 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(i3,i1)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0cHpVWp(i1)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0cHpVWp(i1)
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplA0HpcVWp(i3)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplA0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcHp(i1,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplA0HpcVWp(i1)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplA0cHpVWp(i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplA0cHpVWp(i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplA0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplA0HpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplA0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplA0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToA0VP


Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0VP(MA0,Mhh,MHp,MVP,MVWp,MA02,             & 
& Mhh2,MHp2,MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,        & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,              & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MHp(2),MVP,MVWp,MA02,Mhh2,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),             & 
& cplcVWpVPVWp,cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0VP


Subroutine Amplitude_WAVE_Inert2_hhToA0VZ(MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,ZfA0,            & 
& Zfhh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfA0,Zfhh,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MA0 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToA0VZ


Subroutine Amplitude_VERTEX_Inert2_hhToA0VZ(MA0,Mhh,MHp,MVWp,MVZ,MA02,Mhh2,           & 
& MHp2,MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MHp(2),MVWp,MVZ,MA02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2),cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MVZ 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(i3,i1)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0HpcHp(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0cHpVWp(i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplA0cHpVWp(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplA0HpcVWp(i3)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplA0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcHp(i1,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplA0HpcVWp(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplA0HpcVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplA0cHpVWp(i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplA0cHpVWp(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplA0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplA0HpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplA0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplA0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToA0VZ


Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0VZ(MA0,Mhh,MHp,MVWp,MVZ,MA02,             & 
& Mhh2,MHp2,MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,        & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MHp(2),MVWp,MVZ,MA02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2),cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MA0 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToA0VZ


Subroutine Amplitude_WAVE_Inert2_hhToFvcFv(Mhh,Mhh2,Zfhh,ZfvL,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2

Complex(dp), Intent(in) :: Zfhh,ZfvL(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = Mhh 
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
Amp(:,gt2, gt3) = 0._dp
    End Do
  End Do
End Subroutine Amplitude_WAVE_Inert2_hhToFvcFv


Subroutine Amplitude_VERTEX_Inert2_hhToFvcFv(MFe,Mhh,MHp,MVWp,MVZ,MFe2,               & 
& Mhh2,MHp2,MVWp2,MVZ2,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,     & 
& cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),Mhh,MHp(2),MVWp,MVZ,MFe2(3),Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),              & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcFeFvcHpL(3,3,2),& 
& cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplhhHpcHp(2,2),             & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = 0._dp 
Mex3 = 0._dp 


! {Fe, Fe, conj[Hp]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MHp(i3) 
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFvcHpL(i1,gt2,i3)
coup2R = cplcFeFvcHpR(i1,gt2,i3)
coup3L = cplcFvFeHpL(gt3,i2,i3)
coup3R = cplcFvFeHpR(gt3,i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, conj[VWp]}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVWp 
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = -cplcFeFvcVWpR(i1,gt2)
coup2R = -cplcFeFvcVWpL(i1,gt2)
coup3L = -cplcFvFeVWpR(gt3,i2)
coup3R = -cplcFvFeVWpL(gt3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp, bar[Fe]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i3,gt2,i1)
coup2R = cplcFeFvcHpR(i3,gt2,i1)
coup3L = cplcFvFeHpL(gt3,i3,i2)
coup3R = cplcFvFeHpR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, bar[Fe]}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = cplhhHpcVWp(i1)
coup2L = cplcFeFvcHpL(i3,gt2,i1)
coup2R = cplcFeFvcHpR(i3,gt2,i1)
coup3L = -cplcFvFeVWpR(gt3,i3)
coup3R = -cplcFvFeVWpL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VWp, Hp, bar[Fe]}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = cplhhcHpVWp(i2)
coup2L = -cplcFeFvcVWpR(i3,gt2)
coup2R = -cplcFeFvcVWpL(i3,gt2)
coup3L = cplcFvFeHpL(gt3,i3,i2)
coup3R = cplcFvFeHpR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, bar[Fe]}
    Do i3=1,3
ML1 = MVWp 
ML2 = MVWp 
ML3 = MFe(i3) 
coup1 = cplhhcVWpVWp
coup2L = -cplcFeFvcVWpR(i3,gt2)
coup2R = -cplcFeFvcVWpL(i3,gt2)
coup3L = -cplcFvFeVWpR(gt3,i3)
coup3R = -cplcFvFeVWpL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, VZ, bar[Fv]}
    Do i3=1,3
ML1 = MVZ 
ML2 = MVZ 
ML3 = 0._dp 
coup1 = cplhhVZVZ
coup2L = -cplcFvFvVZR(i3,gt2)
coup2R = -cplcFvFvVZL(i3,gt2)
coup3L = -cplcFvFvVZR(gt3,i3)
coup3R = -cplcFvFvVZL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToFvcFv


Subroutine Amplitude_IR_VERTEX_Inert2_hhToFvcFv(MFe,Mhh,MHp,MVWp,MVZ,MFe2,            & 
& Mhh2,MHp2,MVWp2,MVZ2,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,     & 
& cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFe(3),Mhh,MHp(2),MVWp,MVZ,MFe2(3),Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),              & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcFeFvcHpL(3,3,2),& 
& cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplhhHpcHp(2,2),             & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = 0._dp 
Mex3 = 0._dp 
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToFvcFv


Subroutine Amplitude_WAVE_Inert2_hhToG0H0(MG0,MG02,MH0,MH02,Mhh,Mhh2,ZfG0,            & 
& ZfH0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,MH0,MH02,Mhh,Mhh2

Complex(dp), Intent(in) :: ZfG0,ZfH0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MH0 
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
Amp = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToG0H0


Subroutine Amplitude_VERTEX_Inert2_hhToG0H0(MG0,MH0,Mhh,MHp,MVWp,MG02,MH02,           & 
& Mhh2,MHp2,MVWp2,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplG0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MH0,Mhh,MHp(2),MVWp,MG02,MH02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),          & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplG0H0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MH0 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplH0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplH0HpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplG0HpcVWp(i3)
coup3 = cplH0cHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplG0HpcVWp(i1)
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplG0cHpVWp(i3)
coup3 = cplH0HpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplG0cHpVWp(i3)
coup3 = cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplG0H0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToG0H0


Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0H0(MG0,MH0,Mhh,MHp,MVWp,MG02,             & 
& MH02,Mhh2,MHp2,MVWp2,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,       & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplG0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MH0,Mhh,MHp(2),MVWp,MG02,MH02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),          & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplG0H0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MH0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0H0


Subroutine Amplitude_WAVE_Inert2_hhToG0hh(MG0,MG02,Mhh,Mhh2,ZfG0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,Mhh,Mhh2

Complex(dp), Intent(in) :: ZfG0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = Mhh 
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
Amp = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToG0hh


Subroutine Amplitude_VERTEX_Inert2_hhToG0hh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVWp,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,cplA0A0G0,cplA0A0hh,            & 
& cplA0G0H0,cplA0H0hh,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFeFeG0L,       & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,               & 
& cplcgWpgWphh,cplcgWCgWChh,cplH0H0hh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,   & 
& cplA0A0G0hh1,cplA0A0hhhh1,cplA0G0H0hh1,cplA0H0hhhh1,cplG0H0H0hh1,cplH0H0hhhh1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MA02,MFd2(3),MFe2(3),MFu2(3),        & 
& MG02,MH02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),            & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),  & 
& cplcFeFehhR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,        & 
& cplcgWCgWChh,cplH0H0hh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,     & 
& cplA0A0G0hh1,cplA0A0hhhh1,cplA0G0H0hh1,cplA0H0hhhh1,cplG0H0H0hh1,cplH0H0hhhh1

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = Mhh 


! {A0, A0, A0}
ML1 = MA0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0G0
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, A0}
ML1 = MA0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0A0G0
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, A0, H0}
ML1 = MA0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, H0, H0}
ML1 = MA0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i3,i2)
coup3R = cplcFdFdhhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i3,i2)
coup3R = cplcFeFehhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i3,i2)
coup3R = cplcFuFuhhR(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpG0
coup3 = cplcgWpgWphh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCG0
coup3 = cplcgWCgWChh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 


! {H0, A0, A0}
ML1 = MH0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, A0}
ML1 = MH0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0H0hh
coup2 = cplA0G0H0
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, A0, H0}
ML1 = MH0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0, H0}
ML1 = MH0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplH0H0hh
coup2 = cplG0H0H0
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplG0HpcVWp(i3)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplG0HpcVWp(i3)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplG0HpcVWp(i1)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = -cplG0HpcVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplG0cHpVWp(i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplG0cHpVWp(i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0G0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hh
coup2 = cplG0H0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0hhhh1
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0H0hhhh1
coup2 = cplA0G0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplH0H0hhhh1
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0G0hh1
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0G0H0hh1
coup2 = cplA0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 



! {H0, H0}
ML1 = MH0 
ML2 = MH0 
coup1 = cplG0H0H0hh1
coup2 = cplH0H0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 

End Subroutine Amplitude_VERTEX_Inert2_hhToG0hh


Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0hh(MA0,MFd,MFe,MFu,MG0,MH0,               & 
& Mhh,MHp,MVWp,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,cplA0A0G0,cplA0A0hh,        & 
& cplA0G0H0,cplA0H0hh,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFeFeG0L,       & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,               & 
& cplcgWpgWphh,cplcgWCgWChh,cplH0H0hh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,   & 
& cplA0A0G0hh1,cplA0A0hhhh1,cplA0G0H0hh1,cplA0H0hhhh1,cplG0H0H0hh1,cplH0H0hhhh1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MG0,MH0,Mhh,MHp(2),MVWp,MA02,MFd2(3),MFe2(3),MFu2(3),        & 
& MG02,MH02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),            & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),  & 
& cplcFeFehhR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,        & 
& cplcgWCgWChh,cplH0H0hh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,     & 
& cplA0A0G0hh1,cplA0A0hhhh1,cplA0G0H0hh1,cplA0H0hhhh1,cplG0H0H0hh1,cplH0H0hhhh1

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = Mhh 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0hh


Subroutine Amplitude_WAVE_Inert2_hhToG0VP(cplG0hhVZ,ctcplG0hhVZ,MG0,MG02,             & 
& Mhh,Mhh2,MVP,MVP2,MVZ,MVZ2,ZfG0,Zfhh,ZfVP,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: MG0,MG02,Mhh,Mhh2,MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplG0hhVZ

Complex(dp), Intent(in) :: ctcplG0hhVZ

Complex(dp), Intent(in) :: ZfG0,Zfhh,ZfVP,ZfVZVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MG0 
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
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZVP*cplG0hhVZ


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:) = AmpC 
End Subroutine Amplitude_WAVE_Inert2_hhToG0VP


Subroutine Amplitude_VERTEX_Inert2_hhToG0VP(MFd,MFe,MFu,MG0,Mhh,MHp,MVP,              & 
& MVWp,MFd2,MFe2,MFu2,MG02,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpG0,cplcgWCgWCG0,cplG0HpcVWp,             & 
& cplG0cHpVWp,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,cplcgWCgWCVP,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplG0HpcVWpVP1,cplG0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),MG0,Mhh,MHp(2),MVP,MVWp,MFd2(3),MFe2(3),MFu2(3),MG02,            & 
& Mhh2,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3), & 
& cplcFdFdVPR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),  & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),  & 
& cplcFuFuhhR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWpG0,cplcgWCgWCG0,          & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,cplcgWCgWCVP,     & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),            & 
& cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplG0HpcVWpVP1(2),cplG0cHpVPVWp1(2),        & 
& cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MVP 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = -cplcFdFdVPR(i3,i2)
coup3R = -cplcFdFdVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = -cplcFeFeVPR(i3,i2)
coup3R = -cplcFeFeVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = -cplcFuFuVPR(i3,i2)
coup3R = -cplcFuFuVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpG0
coup3 = cplcgWpgWpVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCG0
coup3 = cplcgWCgWCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplG0cHpVWp(i1)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplG0cHpVWp(i1)
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplG0HpcVWp(i3)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplG0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplG0HpcVWp(i1)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplG0HpcVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplG0cHpVWp(i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplG0cHpVWp(i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplG0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplG0HpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplG0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplG0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToG0VP


Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0VP(MFd,MFe,MFu,MG0,Mhh,MHp,               & 
& MVP,MVWp,MFd2,MFe2,MFu2,MG02,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeG0L,cplcFeFeG0R,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpG0,cplcgWCgWCG0,             & 
& cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,cplcgWCgWCVP,           & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplG0HpcVWpVP1,cplG0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),MG0,Mhh,MHp(2),MVP,MVWp,MFd2(3),MFe2(3),MFu2(3),MG02,            & 
& Mhh2,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3), & 
& cplcFdFdVPR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),  & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),  & 
& cplcFuFuhhR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWpG0,cplcgWCgWCG0,          & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,cplcgWCgWCVP,     & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),            & 
& cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplG0HpcVWpVP1(2),cplG0cHpVPVWp1(2),        & 
& cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MG0 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToG0VP


Subroutine Amplitude_WAVE_Inert2_hhToH0hh(MH0,MH02,Mhh,Mhh2,ZfH0,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MH02,Mhh,Mhh2

Complex(dp), Intent(in) :: ZfH0,Zfhh

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = Mhh 
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
Amp = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToH0hh


Subroutine Amplitude_VERTEX_Inert2_hhToH0hh(MH0,Mhh,MHp,MVWp,MH02,Mhh2,               & 
& MHp2,MVWp2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplH0hhHpcHp1,cplhhhhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MHp(2),MVWp,MH02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplH0hhHpcHp1(2,2),cplhhhhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = Mhh 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplH0cHpVWp(i1)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = -cplH0cHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = -cplH0HpcVWp(i3)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplH0HpcVWp(i3)
coup3 = cplhhcHpVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcHp(i1,i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = -cplH0HpcVWp(i1)
coup3 = cplhhcHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = -cplH0HpcVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = -cplH0cHpVWp(i3)
coup3 = cplhhHpcHp(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = -cplH0cHpVWp(i3)
coup3 = cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0hhHpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhhhHpcHp1(i1,i2)
coup2 = cplH0HpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplH0hhHpcHp1(i1,i2)
coup2 = cplhhHpcHp(i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToH0hh


Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0hh(MH0,Mhh,MHp,MVWp,MH02,Mhh2,            & 
& MHp2,MVWp2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplH0hhHpcHp1,cplhhhhHpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MHp(2),MVWp,MH02,Mhh2,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplH0hhHpcHp1(2,2),cplhhhhHpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = Mhh 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0hh


Subroutine Amplitude_WAVE_Inert2_hhToH0VP(MH0,MH02,Mhh,Mhh2,MVP,MVP2,ZfH0,            & 
& Zfhh,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MH02,Mhh,Mhh2,MVP,MVP2

Complex(dp), Intent(in) :: ZfH0,Zfhh,ZfVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToH0VP


Subroutine Amplitude_VERTEX_Inert2_hhToH0VP(MH0,Mhh,MHp,MVP,MVWp,MH02,Mhh2,           & 
& MHp2,MVP2,MVWp2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,              & 
& cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MHp(2),MVP,MVWp,MH02,Mhh2,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),             & 
& cplcVWpVPVWp,cplH0HpcVWpVP1(2),cplH0cHpVPVWp1(2),cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MVP 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i3,i1)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0cHpVWp(i1)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0cHpVWp(i1)
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplH0HpcVWp(i3)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplH0HpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcHp(i1,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplH0HpcVWp(i1)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplH0cHpVWp(i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplH0cHpVWp(i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplH0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplH0HpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplH0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplH0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToH0VP


Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0VP(MH0,Mhh,MHp,MVP,MVWp,MH02,             & 
& Mhh2,MHp2,MVP2,MVWp2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,        & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,              & 
& cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MHp(2),MVP,MVWp,MH02,Mhh2,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),             & 
& cplcVWpVPVWp,cplH0HpcVWpVP1(2),cplH0cHpVPVWp1(2),cplhhHpcVWpVP1(2),cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0VP


Subroutine Amplitude_WAVE_Inert2_hhToH0VZ(MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,ZfH0,            & 
& Zfhh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,MH02,Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfH0,Zfhh,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = MH0 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToH0VZ


Subroutine Amplitude_VERTEX_Inert2_hhToH0VZ(MH0,Mhh,MHp,MVWp,MVZ,MH02,Mhh2,           & 
& MHp2,MVWp2,MVZ2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MHp(2),MVWp,MVZ,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1(2),cplH0cHpVWpVZ1(2),cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MVZ 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i3,i1)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0HpcHp(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0cHpVWp(i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplH0cHpVWp(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplH0HpcVWp(i3)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplH0HpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcHp(i1,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplH0HpcVWp(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplH0HpcVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplH0cHpVWp(i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplH0cHpVWp(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplH0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplH0HpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplH0cHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplH0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToH0VZ


Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0VZ(MH0,Mhh,MHp,MVWp,MVZ,MH02,             & 
& Mhh2,MHp2,MVWp2,MVZ2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,        & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MH0,Mhh,MHp(2),MVWp,MVZ,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcHp(2,2),cplhhHpcVWp(2),         & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1(2),cplH0cHpVWpVZ1(2),cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MH0 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToH0VZ


Subroutine Amplitude_WAVE_Inert2_hhTohhVP(Mhh,Mhh2,MVP,MVP2,Zfhh,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVP,MVP2

Complex(dp), Intent(in) :: Zfhh,ZfVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhTohhVP


Subroutine Amplitude_VERTEX_Inert2_hhTohhVP(MFd,MFe,MFu,Mhh,MHp,MVP,MVWp,             & 
& MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,               & 
& cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,            & 
& cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,               & 
& cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),Mhh,MHp(2),MVP,MVWp,MFd2(3),MFe2(3),MFu2(3),Mhh2,MHp2(2),        & 
& MVP2,MVWp2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFehhL(3,3), & 
& cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,              & 
& cplcgWCgWCVP,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,               & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplhhHpcVWpVP1(2),          & 
& cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = MVP 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = -cplcFdFdVPR(i3,i2)
coup3R = -cplcFdFdVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = -cplcFeFeVPR(i3,i2)
coup3R = -cplcFeFeVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = -cplcFuFuVPR(i3,i2)
coup3R = -cplcFuFuVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWphh
coup3 = cplcgWpgWpVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWChh
coup3 = cplcgWCgWCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhcHpVWp(i1)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplhhcHpVWp(i1)
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplhhHpcVWp(i3)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplhhHpcVWp(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplhhcVWpVWp
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplhhHpcHp(i1,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplhhHpcVWp(i1)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplhhHpcVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplhhcHpVWp(i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplhhcHpVWp(i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplhhcHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplhhHpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplhhcHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplhhHpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTohhVP


Subroutine Amplitude_IR_VERTEX_Inert2_hhTohhVP(MFd,MFe,MFu,Mhh,MHp,MVP,               & 
& MVWp,MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,          & 
& cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,            & 
& cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,               & 
& cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),Mhh,MHp(2),MVP,MVWp,MFd2(3),MFe2(3),MFu2(3),Mhh2,MHp2(2),        & 
& MVP2,MVWp2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFehhL(3,3), & 
& cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,              & 
& cplcgWCgWCVP,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,               & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplhhHpcVWpVP1(2),          & 
& cplhhcHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTohhVP


Subroutine Amplitude_WAVE_Inert2_hhTohhVZ(Mhh,Mhh2,MVZ,MVZ2,Zfhh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: Zfhh,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhTohhVZ


Subroutine Amplitude_VERTEX_Inert2_hhTohhVZ(MA0,MFd,MFe,MFu,MH0,Mhh,MHp,              & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,            & 
& cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),MFu2(3),        & 
& MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),     & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWpgWphh,      & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp(2,2),cplhhHpcVWp(2),       & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = MVZ 


! {A0, H0, A0}
ML1 = MA0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0A0hh
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {A0, A0, H0}
ML1 = MA0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = -cplcFuFuVZR(i3,i2)
coup3R = -cplcFuFuVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWphh
coup3 = cplcgWpgWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWChh
coup3 = cplcgWCgWCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {H0, H0, A0}
ML1 = MH0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplH0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, A0, H0}
ML1 = MH0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhcHpVWp(i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i1)
coup2 = cplhhcHpVWp(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplhhHpcVWp(i3)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplhhHpcVWp(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplhhcVWpVWp
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplhhHpcHp(i1,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplhhHpcVWp(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = -cplhhcHpVWp(i1)
coup2 = cplhhHpcVWp(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplhhcHpVWp(i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplhhcHpVWp(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplhhHpcVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplhhcHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplhhHpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplhhcHpVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplhhHpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhTohhVZ


Subroutine Amplitude_IR_VERTEX_Inert2_hhTohhVZ(MA0,MFd,MFe,MFu,MH0,Mhh,               & 
& MHp,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,        & 
& cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFe(3),MFu(3),MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MFd2(3),MFe2(3),MFu2(3),        & 
& MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),     & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWpgWphh,      & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp(2,2),cplhhHpcVWp(2),       & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplhhHpcVWpVZ1(2),cplhhcHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = Mhh 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhTohhVZ


Subroutine Amplitude_WAVE_Inert2_hhToVGVG(Mhh,Mhh2,MVG,MVG2,Zfhh,ZfVG,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVG,MVG2

Complex(dp), Intent(in) :: Zfhh,ZfVG

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToVGVG


Subroutine Amplitude_VERTEX_Inert2_hhToVGVG(MFd,MFu,Mhh,MVG,MFd2,MFu2,Mhh2,           & 
& MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,cplcFuFuhhR,          & 
& cplcFuFuVGL,cplcFuFuVGR,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),Mhh,MVG,MFd2(3),MFu2(3),Mhh2,MVG2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuhhL(3,3), & 
& cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MVG 
Mex3 = MVG 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToVGVG


Subroutine Amplitude_IR_VERTEX_Inert2_hhToVGVG(MFd,MFu,Mhh,MVG,MFd2,MFu2,             & 
& Mhh2,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,cplcFuFuhhR,     & 
& cplcFuFuVGL,cplcFuFuVGR,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),Mhh,MVG,MFd2(3),MFu2(3),Mhh2,MVG2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuhhL(3,3), & 
& cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MVG 
Mex3 = MVG 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToVGVG


Subroutine Amplitude_WAVE_Inert2_hhToVPVP(cplhhVZVZ,ctcplhhVZVZ,Mhh,Mhh2,             & 
& MVP,MVP2,MVZ,MVZ2,Zfhh,ZfVP,ZfVPVZ,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplhhVZVZ

Complex(dp), Intent(in) :: ctcplhhVZVZ

Complex(dp), Intent(in) :: Zfhh,ZfVP,ZfVPVZ,ZfVZVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToVPVP


Subroutine Amplitude_VERTEX_Inert2_hhToVPVP(MFd,MFe,MFu,Mhh,MHp,MVP,MVWp,             & 
& MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,               & 
& cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,            & 
& cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,               & 
& cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,cplHpcHpVPVP1,      & 
& cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),Mhh,MHp(2),MVP,MVWp,MFd2(3),MFe2(3),MFu2(3),Mhh2,MHp2(2),        & 
& MVP2,MVWp2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFehhL(3,3), & 
& cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,              & 
& cplcgWCgWCVP,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,               & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplhhHpcVWpVP1(2),          & 
& cplhhcHpVPVWp1(2),cplHpcHpVPVP1(2,2),cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MVP 
Mex3 = MVP 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpVP
coup3 = cplcgWpgWpVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCVP
coup3 = cplcgWCgWCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhHpcVWp(i1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplcHpVPVWp(i1)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplcHpVPVWp(i1)
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplHpcVWpVP(i3)
coup3 = -cplHpcHpVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplHpcVWpVP(i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhcHpVWp(i2)
coup2 = cplcVWpVPVWp
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVPVWp
coup3 = cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcHpVP(i1,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcVWpVP(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcVWp(i2)
coup2 = cplcHpVPVWp(i3)
coup3 = cplHpcHpVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplcHpVPVWp(i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcVWp(i2)
coup2 = -cplcVWpVPVWp
coup3 = cplcHpVPVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpVPVP1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVPVPVWp1Q
coup2b = coup2 
coup2 = cplcVWpVPVPVWp2Q
coup2c = coup2 
coup2 = cplcVWpVPVPVWp3Q
coup2a = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToVPVP


Subroutine Amplitude_IR_VERTEX_Inert2_hhToVPVP(MFd,MFe,MFu,Mhh,MHp,MVP,               & 
& MVWp,MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,          & 
& cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,            & 
& cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,               & 
& cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,cplHpcHpVPVP1,      & 
& cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),Mhh,MHp(2),MVP,MVWp,MFd2(3),MFe2(3),MFu2(3),Mhh2,MHp2(2),        & 
& MVP2,MVWp2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFehhL(3,3), & 
& cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,              & 
& cplcgWCgWCVP,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,               & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplhhHpcVWpVP1(2),          & 
& cplhhcHpVPVWp1(2),cplHpcHpVPVP1(2,2),cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MVP 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToVPVP


Subroutine Amplitude_WAVE_Inert2_hhToVPVZ(cplhhVZVZ,ctcplhhVZVZ,Mhh,Mhh2,             & 
& MVP,MVP2,MVZ,MVZ2,Zfhh,ZfVP,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: Mhh,Mhh2,MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplhhVZVZ

Complex(dp), Intent(in) :: ctcplhhVZVZ

Complex(dp), Intent(in) :: Zfhh,ZfVP,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = Mhh 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_hhToVPVZ


Subroutine Amplitude_VERTEX_Inert2_hhToVPVZ(MFd,MFe,MFu,Mhh,MHp,MVP,MVWp,             & 
& MVZ,MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWpgWpVZ,            & 
& cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,             & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,   & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,  & 
& cplHpcHpVPVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),Mhh,MHp(2),MVP,MVWp,MVZ,MFd2(3),MFe2(3),MFu2(3),Mhh2,            & 
& MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3), & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),  & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVPL(3,3),  & 
& cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWpgWphh,cplcgWpgWpVP,          & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp(2,2),cplhhHpcVWp(2),    & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),            & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplhhHpcVWpVP1(2),& 
& cplhhHpcVWpVZ1(2),cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVZ1(2,2),              & 
& cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = Mhh 
Mex2 = MVP 
Mex3 = MVZ 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
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
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
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
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
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
Amp(:) = Amp(:) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWp, gWp, gWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWpgWphh
coup2 = cplcgWpgWpVP
coup3 = cplcgWpgWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {gWpC, gWpC, gWpC}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplcgWCgWChh
coup2 = cplcgWCgWCVP
coup3 = cplcgWCgWCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhHpcVWp(i1)
coup2 = -cplHpcHpVP(i3,i1)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplcHpVPVWp(i1)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhHpcVWp(i1)
coup2 = cplcHpVPVWp(i1)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, Hp}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(i2)
coup2 = cplHpcVWpVP(i3)
coup3 = -cplHpcHpVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWp, VWp, Hp}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplHpcVWpVP(i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhcHpVWp(i2)
coup2 = cplcVWpVPVWp
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVPVWp
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(2)*AmpC 


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcHpVP(i1,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcHp(i2,i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hp], conj[VWp], conj[VWp]}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1 = cplhhcHpVWp(i1)
coup2 = cplHpcVWpVP(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWp], conj[Hp], conj[Hp]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplhhHpcVWp(i2)
coup2 = cplcHpVPVWp(i3)
coup3 = cplHpcHpVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWp], conj[VWp], conj[Hp]}
    Do i3=1,2
ML1 = MVWp 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplhhcVWpVWp
coup2 = cplcHpVPVWp(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplhhHpcVWp(i2)
coup2 = -cplcVWpVPVWp
coup3 = cplcHpVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpcHpVPVZ1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWp, VWp}
ML1 = MVWp 
ML2 = MVWp 
coup1 = cplhhcVWpVWp
coup2 = cplcVWpVPVWpVZ1Q
coup2b = coup2 
coup2 = cplcVWpVPVWpVZ2Q
coup2a = coup2 
coup2 = cplcVWpVPVWpVZ3Q
coup2c = coup2 
If (Abs(coup1)*(Abs(coup2a)+Abs(coup2b)+Abs(coup2c)) .gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology2_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2a,coup2b,coup2c,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVZ1(i1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVWpVZ1(i2)
coup2 = cplHpcVWpVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplhhHpcVWpVP1(i1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplhhcHpVPVWp1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_hhToVPVZ


Subroutine Amplitude_IR_VERTEX_Inert2_hhToVPVZ(MFd,MFe,MFu,Mhh,MHp,MVP,               & 
& MVWp,MVZ,MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,cplcgWpgWpVP,             & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp,cplhhHpcVWp,            & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,    & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFe(3),MFu(3),Mhh,MHp(2),MVP,MVWp,MVZ,MFd2(3),MFe2(3),MFu2(3),Mhh2,            & 
& MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3), & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),  & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVPL(3,3),  & 
& cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWpgWphh,cplcgWpgWpVP,          & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp(2,2),cplhhHpcVWp(2),    & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),            & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplhhHpcVWpVP1(2),& 
& cplhhHpcVWpVZ1(2),cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVZ1(2,2),              & 
& cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = Mhh 
Mex2 = MVP 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_hhToVPVZ



End Module OneLoopDecay_hh_Inert2
