! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:50 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecay_A0_Inert2
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

Subroutine Amplitude_Tree_Inert2_A0ToG0A0(cplA0A0G0,MA0,MG0,MA02,MG02,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MA02,MG02

Complex(dp), Intent(in) :: cplA0A0G0

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MA0 
! Tree-Level Vertex 
coupT1 = cplA0A0G0
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_A0ToG0A0


Subroutine Gamma_Real_Inert2_A0ToG0A0(MLambda,em,gs,cplA0A0G0,MA0,MG0,GammarealPhoton,& 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0A0G0

Real(dp), Intent(in) :: MA0,MG0

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplA0A0G0
Mex1 = MA0
Mex2 = MG0
Mex3 = MA0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_A0ToG0A0


Subroutine Amplitude_WAVE_Inert2_A0ToG0A0(cplA0A0G0,ctcplA0A0G0,MA0,MA02,             & 
& MG0,MG02,ZfA0,ZfG0,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MG0,MG02

Complex(dp), Intent(in) :: cplA0A0G0

Complex(dp), Intent(in) :: ctcplA0A0G0

Complex(dp), Intent(in) :: ZfA0,ZfG0

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MA0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0A0G0 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0A0G0


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfG0*cplA0A0G0


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0A0G0


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_A0ToG0A0


Subroutine Amplitude_VERTEX_Inert2_A0ToG0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,           & 
& cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),            & 
& cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0G0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MA0 


! {A0, G0, A0}
ML1 = MA0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, A0}
ML1 = MA0 
ML2 = Mhh 
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


! {A0, G0, H0}
ML1 = MA0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, H0}
ML1 = MA0 
ML2 = Mhh 
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


! {G0, A0, hh}
ML1 = MG0 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0A0G0
coup2 = cplG0G0hh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0, hh}
ML1 = MG0 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, G0, A0}
ML1 = MH0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, A0}
ML1 = MH0 
ML2 = Mhh 
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


! {H0, G0, H0}
ML1 = MH0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, H0}
ML1 = MH0 
ML2 = Mhh 
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


! {H0, VZ, H0}
ML1 = MH0 
ML2 = MVZ 
ML3 = MH0 
coup1 = -cplA0H0VZ
coup2 = cplG0H0H0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, A0, G0}
ML1 = Mhh 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, H0, G0}
ML1 = Mhh 
ML2 = MH0 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplG0G0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, H0, VZ}
ML1 = Mhh 
ML2 = MH0 
ML3 = MVZ 
coup1 = cplA0H0hh
coup2 = -cplG0hhVZ
coup3 = cplA0H0VZ
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplG0cHpVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
coup2 = -cplG0HpcVWp(i3)
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


! {VZ, H0, hh}
ML1 = MVZ 
ML2 = MH0 
ML3 = Mhh 
coup1 = -cplA0H0VZ
coup2 = -cplG0hhVZ
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
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
coup1 = cplA0HpcHp(i2,i1)
coup2 = -cplG0HpcVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
coup2 = -cplG0cHpVWp(i3)
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


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0
coup2 = cplA0A0G0G01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0A0G0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0
coup2 = cplA0G0G0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hh
coup2 = cplA0G0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplA0G0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0A0A01
coup2 = cplA0A0G0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {G0, hh}
ML1 = MG0 
ML2 = Mhh 
coup1 = cplA0A0G0hh1
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
coup1 = cplA0A0H0H01
coup2 = cplG0H0H0
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0G01
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
coup1 = cplA0A0G0hh1
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
coup1 = cplA0G0G0H01
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
coup1 = cplA0G0H0hh1
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
coup1 = cplA0G0HpcHp1(i1,i2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0ToG0A0


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,       & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,           & 
& cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),            & 
& cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0G0HpcHp1(2,2)

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
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MA0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0A0


Subroutine Amplitude_Tree_Inert2_A0TohhA0(cplA0A0hh,MA0,Mhh,MA02,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,Mhh,MA02,Mhh2

Complex(dp), Intent(in) :: cplA0A0hh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MA0 
! Tree-Level Vertex 
coupT1 = cplA0A0hh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_A0TohhA0


Subroutine Gamma_Real_Inert2_A0TohhA0(MLambda,em,gs,cplA0A0hh,MA0,Mhh,GammarealPhoton,& 
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
Mex1 = MA0
Mex2 = Mhh
Mex3 = MA0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_A0TohhA0


Subroutine Amplitude_WAVE_Inert2_A0TohhA0(cplA0A0hh,ctcplA0A0hh,MA0,MA02,             & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MA0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0A0hh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0A0hh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplA0A0hh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0A0hh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_A0TohhA0


Subroutine Amplitude_VERTEX_Inert2_A0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MA0 


! {A0, G0, A0}
ML1 = MA0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplA0A0G0
coup2 = cplA0A0hh
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, A0}
ML1 = MA0 
ML2 = Mhh 
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


! {A0, G0, H0}
ML1 = MA0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplA0A0G0
coup2 = cplA0H0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, H0}
ML1 = MA0 
ML2 = Mhh 
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


! {G0, A0, G0}
ML1 = MG0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0A0G0
coup2 = cplG0G0hh
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0, G0}
ML1 = MG0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0, VZ}
ML1 = MG0 
ML2 = MH0 
ML3 = MVZ 
coup1 = cplA0G0H0
coup2 = cplG0hhVZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, G0, A0}
ML1 = MH0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplA0G0H0
coup2 = cplA0H0hh
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, A0}
ML1 = MH0 
ML2 = Mhh 
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


! {H0, G0, H0}
ML1 = MH0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplA0G0H0
coup2 = cplH0H0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, H0}
ML1 = MH0 
ML2 = Mhh 
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


! {H0, VZ, H0}
ML1 = MH0 
ML2 = MVZ 
ML3 = MH0 
coup1 = -cplA0H0VZ
coup2 = cplH0H0hh
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, A0, hh}
ML1 = Mhh 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0A0hh
coup2 = cplhhhhhh
coup3 = cplA0A0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, H0, hh}
ML1 = Mhh 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplhhhhhh
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
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
coup1 = -cplA0HpcVWp(i1)
coup2 = cplhhHpcHp(i3,i1)
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplhhcHpVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
coup2 = -cplhhHpcVWp(i3)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0cHpVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplA0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do


! {VZ, H0, G0}
ML1 = MVZ 
ML2 = MH0 
ML3 = MG0 
coup1 = -cplA0H0VZ
coup2 = cplG0hhVZ
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {VZ, H0, VZ}
ML1 = MVZ 
ML2 = MH0 
ML3 = MVZ 
coup1 = -cplA0H0VZ
coup2 = cplhhVZVZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
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
coup1 = -cplA0cHpVWp(i1)
coup2 = cplhhHpcHp(i1,i3)
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
coup1 = cplA0HpcHp(i2,i1)
coup2 = -cplhhHpcVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
coup2 = -cplhhcHpVWp(i3)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0HpcVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplA0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0
coup2 = cplA0A0G0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0A0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0
coup2 = cplA0G0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hh
coup2 = cplA0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplA0hhHpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {A0, A0}
ML1 = MA0 
ML2 = MA0 
coup1 = cplA0A0A0A01
coup2 = cplA0A0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {G0, G0}
ML1 = MG0 
ML2 = MG0 
coup1 = cplA0A0G0G01
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
coup1 = cplA0A0H0H01
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
coup1 = cplA0A0hhhh1
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
coup1 = cplA0A0HpcHp1(i1,i2)
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
coup1 = cplA0A0cVWpVWp1
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
coup1 = cplA0A0VZVZ1
coup2 = cplhhVZVZ
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



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
End Subroutine Amplitude_VERTEX_Inert2_A0TohhA0


Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhA0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MA0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhA0


Subroutine Amplitude_Tree_Inert2_A0ToH0G0(cplA0G0H0,MA0,MG0,MH0,MA02,MG02,MH02,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,MA02,MG02,MH02

Complex(dp), Intent(in) :: cplA0G0H0

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MG0 
! Tree-Level Vertex 
coupT1 = cplA0G0H0
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_A0ToH0G0


Subroutine Gamma_Real_Inert2_A0ToH0G0(MLambda,em,gs,cplA0G0H0,MA0,MG0,MH0,            & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0G0H0

Real(dp), Intent(in) :: MA0,MG0,MH0

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplA0G0H0
Mex1 = MA0
Mex2 = MH0
Mex3 = MG0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_A0ToH0G0


Subroutine Amplitude_WAVE_Inert2_A0ToH0G0(cplA0G0H0,ctcplA0G0H0,MA0,MA02,             & 
& MG0,MG02,MH0,MH02,ZfA0,ZfG0,ZfH0,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MG0,MG02,MH0,MH02

Complex(dp), Intent(in) :: cplA0G0H0

Complex(dp), Intent(in) :: ctcplA0G0H0

Complex(dp), Intent(in) :: ZfA0,ZfG0,ZfH0

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MG0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0G0H0 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0G0H0


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplA0G0H0


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfG0*cplA0G0H0


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_A0ToH0G0


Subroutine Amplitude_VERTEX_Inert2_A0ToH0G0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplA0A0G0G01,     & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1,cplG0G0H0H01,        & 
& cplG0H0H0hh1,cplG0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),            & 
& cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplA0A0G0G01,cplA0A0G0hh1,     & 
& cplA0A0H0H01,cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),cplG0G0H0H01,cplG0H0H0hh1,   & 
& cplG0H0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MG0 


! {A0, hh, G0}
ML1 = MA0 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, G0, hh}
ML1 = MA0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplA0A0G0
coup2 = cplA0H0hh
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, VZ}
ML1 = MA0 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplA0A0hh
coup2 = cplA0H0VZ
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, A0, A0}
ML1 = MG0 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0, A0}
ML1 = MG0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, A0, H0}
ML1 = MG0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0G0
coup2 = cplG0H0H0
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0, H0}
ML1 = MG0 
ML2 = MH0 
ML3 = MH0 
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, G0}
ML1 = MH0 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, G0, hh}
ML1 = MH0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplA0G0H0
coup2 = cplH0H0hh
coup3 = cplG0G0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, VZ, hh}
ML1 = MH0 
ML2 = MVZ 
ML3 = Mhh 
coup1 = -cplA0H0VZ
coup2 = cplH0H0hh
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, A0, A0}
ML1 = Mhh 
ML2 = MA0 
ML3 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0A0G0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, H0, A0}
ML1 = Mhh 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, A0, H0}
ML1 = Mhh 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplH0H0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, H0, H0}
ML1 = Mhh 
ML2 = MH0 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, VWp, Hp}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0HpcVWp(i1)
coup2 = cplH0HpcHp(i3,i1)
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplH0cHpVWp(i1)
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


! {VZ, H0, A0}
ML1 = MVZ 
ML2 = MH0 
ML3 = MA0 
coup1 = -cplA0H0VZ
coup2 = cplA0H0VZ
coup3 = cplA0G0H0
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
coup1 = -cplA0cHpVWp(i1)
coup2 = cplH0HpcHp(i1,i3)
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
coup1 = cplA0HpcHp(i2,i1)
coup2 = -cplH0HpcVWp(i1)
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


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0
coup2 = cplA0G0G0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0G0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0
coup2 = cplG0G0H0H01
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hh
coup2 = cplG0H0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplG0H0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0G01
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
coup1 = cplA0A0G0hh1
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
coup1 = cplA0G0G0H01
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
coup1 = cplA0G0H0hh1
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
coup1 = cplA0G0HpcHp1(i1,i2)
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


! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0A0H0H01
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
coup1 = cplA0G0H0hh1
coup2 = cplG0G0hh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 

End Subroutine Amplitude_VERTEX_Inert2_A0ToH0G0


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0G0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,       & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplA0A0G0G01,     & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1,cplG0G0H0H01,        & 
& cplG0H0H0hh1,cplG0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),            & 
& cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplA0A0G0G01,cplA0A0G0hh1,     & 
& cplA0A0H0H01,cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),cplG0G0H0H01,cplG0H0H0hh1,   & 
& cplG0H0HpcHp1(2,2)

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
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MG0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0G0


Subroutine Amplitude_Tree_Inert2_A0TohhH0(cplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,Mhh,MA02,MH02,Mhh2

Complex(dp), Intent(in) :: cplA0H0hh

Complex(dp) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MH0 
! Tree-Level Vertex 
coupT1 = cplA0H0hh
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp = AmpC 
End Subroutine Amplitude_Tree_Inert2_A0TohhH0


Subroutine Gamma_Real_Inert2_A0TohhH0(MLambda,em,gs,cplA0H0hh,MA0,MH0,Mhh,            & 
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
Mex1 = MA0
Mex2 = Mhh
Mex3 = MH0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
  GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_A0TohhH0


Subroutine Amplitude_WAVE_Inert2_A0TohhH0(cplA0H0hh,ctcplA0H0hh,MA0,MA02,             & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MH0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0H0hh 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0H0hh


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh*cplA0H0hh


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplA0H0hh


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp = AmpC 
End Subroutine Amplitude_WAVE_Inert2_A0TohhH0


Subroutine Amplitude_VERTEX_Inert2_A0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MH0 


! {A0, G0, A0}
ML1 = MA0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplA0A0G0
coup2 = cplA0A0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, A0}
ML1 = MA0 
ML2 = Mhh 
ML3 = MA0 
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, G0, H0}
ML1 = MA0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplA0A0G0
coup2 = cplA0H0hh
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh, H0}
ML1 = MA0 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, A0, G0}
ML1 = MG0 
ML2 = MA0 
ML3 = MG0 
coup1 = cplA0A0G0
coup2 = cplG0G0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0, G0}
ML1 = MG0 
ML2 = MH0 
ML3 = MG0 
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, A0, VZ}
ML1 = MG0 
ML2 = MA0 
ML3 = MVZ 
coup1 = cplA0A0G0
coup2 = cplG0hhVZ
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, G0, A0}
ML1 = MH0 
ML2 = MG0 
ML3 = MA0 
coup1 = cplA0G0H0
coup2 = cplA0H0hh
coup3 = cplA0G0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, A0}
ML1 = MH0 
ML2 = Mhh 
ML3 = MA0 
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


! {H0, VZ, A0}
ML1 = MH0 
ML2 = MVZ 
ML3 = MA0 
coup1 = -cplA0H0VZ
coup2 = cplA0H0hh
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, G0, H0}
ML1 = MH0 
ML2 = MG0 
ML3 = MH0 
coup1 = cplA0G0H0
coup2 = cplH0H0hh
coup3 = cplG0H0H0
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh, H0}
ML1 = MH0 
ML2 = Mhh 
ML3 = MH0 
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, A0, hh}
ML1 = Mhh 
ML2 = MA0 
ML3 = Mhh 
coup1 = cplA0A0hh
coup2 = cplhhhhhh
coup3 = cplA0H0hh
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {hh, H0, hh}
ML1 = Mhh 
ML2 = MH0 
ML3 = Mhh 
coup1 = cplA0H0hh
coup2 = cplhhhhhh
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
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
coup1 = -cplA0HpcVWp(i1)
coup2 = cplhhHpcHp(i3,i1)
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplhhcHpVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
coup2 = -cplhhHpcVWp(i3)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0cHpVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplH0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do


! {VZ, H0, G0}
ML1 = MVZ 
ML2 = MH0 
ML3 = MG0 
coup1 = -cplA0H0VZ
coup2 = cplG0hhVZ
coup3 = cplG0H0H0
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
coup1 = -cplA0cHpVWp(i1)
coup2 = cplhhHpcHp(i1,i3)
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
coup1 = cplA0HpcHp(i2,i1)
coup2 = -cplhhHpcVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
coup2 = -cplhhcHpVWp(i3)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0HpcVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplH0cHpVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0
coup2 = cplA0G0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0
coup2 = cplG0H0H0hh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hh
coup2 = cplH0H0hhhh1
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplH0hhHpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do


! {A0, H0}
ML1 = MA0 
ML2 = MH0 
coup1 = cplA0A0H0H01
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
coup1 = cplA0G0G0H01
coup2 = cplG0G0hh
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
coup1 = cplA0H0hhhh1
coup2 = cplhhhhhh
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1._dp/2._dp)*AmpC 



! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0hh1
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
coup1 = cplA0A0hhhh1
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
coup1 = cplA0G0H0hh1
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
coup1 = cplA0H0hhhh1
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
coup1 = cplA0hhHpcHp1(i1,i2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0TohhH0


Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhH0(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MH0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhH0


Subroutine Amplitude_Tree_Inert2_A0ToH0VZ(cplA0H0VZ,MA0,MH0,MVZ,MA02,MH02,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MVZ,MA02,MH02,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ

Complex(dp) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1 = cplA0H0VZ
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:) = AmpC 
End Subroutine Amplitude_Tree_Inert2_A0ToH0VZ


Subroutine Gamma_Real_Inert2_A0ToH0VZ(MLambda,em,gs,cplA0H0VZ,MA0,MH0,MVZ,            & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0H0VZ

Real(dp), Intent(in) :: MA0,MH0,MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton, GammarealGluon 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Coup = cplA0H0VZ
Mex1 = MA0
Mex2 = MH0
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton = 0._dp 
 GammarealGluon = 0._dp 
Else 
  GammarealGluon = 0._dp 
  GammarealPhoton = 0._dp 

End if 
End Subroutine Gamma_Real_Inert2_A0ToH0VZ


Subroutine Amplitude_WAVE_Inert2_A0ToH0VZ(cplA0H0VZ,ctcplA0H0VZ,MA0,MA02,             & 
& MH0,MH02,MVZ,MVZ2,ZfA0,ZfH0,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ

Complex(dp), Intent(in) :: ctcplA0H0VZ

Complex(dp), Intent(in) :: ZfA0,ZfH0,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0H0VZ 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0H0VZ


! External Field 2 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfH0*cplA0H0VZ


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplA0H0VZ


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:) = AmpC 
End Subroutine Amplitude_WAVE_Inert2_A0ToH0VZ


Subroutine Amplitude_VERTEX_Inert2_A0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,       & 
& cplcVWpVWpVZ,cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,   & 
& cplH0cHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),           & 
& cplH0cHpVWp(2),cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,   & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2),cplH0H0VZVZ1,cplH0HpcVWpVZ1(2),       & 
& cplH0cHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MVZ 


! {A0, hh, G0}
ML1 = MA0 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {A0, G0, hh}
ML1 = MA0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplA0A0G0
coup2 = cplA0H0hh
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {A0, hh, VZ}
ML1 = MA0 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplA0A0hh
coup2 = -cplA0H0VZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {G0, H0, A0}
ML1 = MG0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {G0, A0, H0}
ML1 = MG0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0G0
coup2 = cplG0H0H0
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, hh, G0}
ML1 = MH0 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplG0H0H0
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, G0, hh}
ML1 = MH0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplA0G0H0
coup2 = cplH0H0hh
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, VZ, hh}
ML1 = MH0 
ML2 = MVZ 
ML3 = Mhh 
coup1 = -cplA0H0VZ
coup2 = cplH0H0hh
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, H0, A0}
ML1 = Mhh 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, A0, H0}
ML1 = Mhh 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0hh
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {VZ, H0, A0}
ML1 = MVZ 
ML2 = MH0 
ML3 = MA0 
coup1 = -cplA0H0VZ
coup2 = -cplA0H0VZ
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {H0, VZ}
ML1 = MH0 
ML2 = MVZ 
coup1 = cplA0H0VZ
coup2 = cplH0H0VZVZ1
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplH0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplH0HpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {A0, VZ}
ML1 = MA0 
ML2 = MVZ 
coup1 = cplA0A0VZVZ1
coup2 = -cplA0H0VZ
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
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplH0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToH0VZ


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,       & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,       & 
& cplcVWpVWpVZ,cplA0A0VZVZ1,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplH0H0VZVZ1,cplH0HpcVWpVZ1,   & 
& cplH0cHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),           & 
& cplH0cHpVWp(2),cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,   & 
& cplA0A0VZVZ1,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2),cplH0H0VZVZ1,cplH0HpcVWpVZ1(2),       & 
& cplH0cHpVWpVZ1(2)

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
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0VZ


Subroutine Amplitude_Tree_Inert2_A0TocHpHp(cplA0HpcHp,MA0,MHp,MA02,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MA02,MHp2(2)

Complex(dp), Intent(in) :: cplA0HpcHp(2,2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 
! Tree-Level Vertex 
coupT1 = cplA0HpcHp(gt3,gt2)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_Tree_Inert2_A0TocHpHp


Subroutine Gamma_Real_Inert2_A0TocHpHp(MLambda,em,gs,cplA0HpcHp,MA0,MHp,              & 
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
 
  Do i2=2,2
    Do i3=2,2
Coup = cplA0HpcHp(i3,i2)
Mex1 = MA0
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
End Subroutine Gamma_Real_Inert2_A0TocHpHp


Subroutine Amplitude_WAVE_Inert2_A0TocHpHp(cplA0HpcHp,ctcplA0HpcHp,MA0,               & 
& MA02,MHp,MHp2,ZfA0,ZfHp,Amp)

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

  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0HpcHp(gt3,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0HpcHp(gt3,gt2)


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHp(i1,gt2))*cplA0HpcHp(gt3,i1)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt3)*cplA0HpcHp(i1,gt2)
End Do


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt2, gt3) = AmpC 
    End Do
  End Do
End Subroutine Amplitude_WAVE_Inert2_A0TocHpHp


Subroutine Amplitude_VERTEX_Inert2_A0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,            & 
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
  Do gt2=1,2
    Do gt3=1,2
Amp(gt2, gt3) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 


! {A0, hh, Hp}
    Do i3=1,2
ML1 = MA0 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplA0HpcHp(i3,gt2)
coup3 = cplhhHpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {A0, G0, VWp}
ML1 = MA0 
ML2 = MG0 
ML3 = MVWp 
coup1 = cplA0A0G0
coup2 = cplA0cHpVWp(gt2)
coup3 = -cplG0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {A0, hh, VWp}
ML1 = MA0 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplA0A0hh
coup2 = cplA0cHpVWp(gt2)
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {G0, A0, VWp}
ML1 = MG0 
ML2 = MA0 
ML3 = MVWp 
coup1 = cplA0A0G0
coup2 = cplG0cHpVWp(gt2)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {G0, H0, VWp}
ML1 = MG0 
ML2 = MH0 
ML3 = MVWp 
coup1 = cplA0G0H0
coup2 = cplG0cHpVWp(gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {H0, hh, Hp}
    Do i3=1,2
ML1 = MH0 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplH0HpcHp(i3,gt2)
coup3 = cplhhHpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {H0, VZ, Hp}
    Do i3=1,2
ML1 = MH0 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = -cplA0H0VZ
coup2 = cplH0HpcHp(i3,gt2)
coup3 = cplHpcHpVZ(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {H0, G0, VWp}
ML1 = MH0 
ML2 = MG0 
ML3 = MVWp 
coup1 = cplA0G0H0
coup2 = cplH0cHpVWp(gt2)
coup3 = -cplG0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {H0, hh, VWp}
ML1 = MH0 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplA0H0hh
coup2 = cplH0cHpVWp(gt2)
coup3 = -cplhhHpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {H0, VZ, VWp}
ML1 = MH0 
ML2 = MVZ 
ML3 = MVWp 
coup1 = -cplA0H0VZ
coup2 = cplH0cHpVWp(gt2)
coup3 = cplHpcVWpVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {hh, A0, Hp}
    Do i3=1,2
ML1 = Mhh 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplhhHpcHp(i3,gt2)
coup3 = cplA0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, H0, Hp}
    Do i3=1,2
ML1 = Mhh 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplhhHpcHp(i3,gt2)
coup3 = cplH0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {hh, A0, VWp}
ML1 = Mhh 
ML2 = MA0 
ML3 = MVWp 
coup1 = cplA0A0hh
coup2 = cplhhcHpVWp(gt2)
coup3 = -cplA0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {hh, H0, VWp}
ML1 = Mhh 
ML2 = MH0 
ML3 = MVWp 
coup1 = cplA0H0hh
coup2 = cplhhcHpVWp(gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {VZ, H0, Hp}
    Do i3=1,2
ML1 = MVZ 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = -cplA0H0VZ
coup2 = cplHpcHpVZ(i3,gt2)
coup3 = cplH0HpcHp(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do


! {VZ, H0, VWp}
ML1 = MVZ 
ML2 = MH0 
ML3 = MVWp 
coup1 = -cplA0H0VZ
coup2 = cplcHpVWpVZ(gt2)
coup3 = -cplH0HpcVWp(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], H0}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], hh}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], VZ}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = -cplA0HpcVWp(i2)
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


! {A0, G0}
ML1 = MA0 
ML2 = MG0 
coup1 = cplA0A0G0
coup2 = cplA0G0HpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {A0, hh}
ML1 = MA0 
ML2 = Mhh 
coup1 = cplA0A0hh
coup2 = cplA0hhHpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {G0, H0}
ML1 = MG0 
ML2 = MH0 
coup1 = cplA0G0H0
coup2 = cplG0H0HpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {H0, hh}
ML1 = MH0 
ML2 = Mhh 
coup1 = cplA0H0hh
coup2 = cplH0hhHpcHp1(gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplHpHpcHpcHp1(gt3,i2,gt2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {A0, Hp}
  Do i2=1,2
ML1 = MA0 
ML2 = MHp(i2) 
coup1 = cplA0A0HpcHp1(gt3,i2)
coup2 = cplA0HpcHp(i2,gt2)
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
coup1 = cplA0hhHpcHp1(gt3,i2)
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
coup1 = cplA0HpcVWpVP1(gt3)
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
coup1 = cplA0HpcVWpVZ1(gt3)
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
coup1 = cplA0A0HpcHp1(i2,gt2)
coup2 = cplA0HpcHp(gt3,i2)
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
coup1 = cplA0hhHpcHp1(i2,gt2)
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
coup1 = cplA0cHpVPVWp1(gt2)
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
coup1 = cplA0cHpVWpVZ1(gt2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0TocHpHp


Subroutine Amplitude_IR_VERTEX_Inert2_A0TocHpHp(MA0,MG0,MH0,Mhh,MHp,MVP,              & 
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
  Do gt2=1,2
    Do gt3=1,2
Amp(gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MHp(gt3) 


! {conj[Hp], conj[Hp], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
coup2 = cplcHpVPVWp(gt2)
coup3 = cplHpcHpVP(gt3,i2)
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {VP, VWp}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplA0HpcVWpVP1(gt3)
coup2 = cplcHpVPVWp(gt2)
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 



! {VP, conj[VWp]}
ML1 = MVP 
ML2 = MVWp 
coup1 = cplA0cHpVPVWp1(gt2)
coup2 = cplHpcVWpVP(gt3)
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt2, gt3) = Amp(gt2, gt3) + oo16pi2*(1)*AmpC 

    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0TocHpHp


Subroutine Amplitude_Tree_Inert2_A0ToHpcVWp(cplA0HpcVWp,MA0,MHp,MVWp,MA02,            & 
& MHp2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVWp,MA02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcVWp(2)

Complex(dp) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

  Do gt2=1,2
! External masses 
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1 = cplA0HpcVWp(gt2)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt2) = AmpC 
  End Do
End Subroutine Amplitude_Tree_Inert2_A0ToHpcVWp


Subroutine Gamma_Real_Inert2_A0ToHpcVWp(MLambda,em,gs,cplA0HpcVWp,MA0,MHp,            & 
& MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplA0HpcVWp(2)

Real(dp), Intent(in) :: MA0,MHp(2),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2), GammarealGluon(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
  Do i2=2,2
Coup = cplA0HpcVWp(i2)
Mex1 = MA0
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
End Subroutine Gamma_Real_Inert2_A0ToHpcVWp


Subroutine Amplitude_WAVE_Inert2_A0ToHpcVWp(cplA0HpcVWp,ctcplA0HpcVWp,MA0,            & 
& MA02,MHp,MHp2,MVWp,MVWp2,ZfA0,ZfHp,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0HpcVWp(2)

Complex(dp), Intent(in) :: ctcplA0HpcVWp(2)

Complex(dp), Intent(in) :: ZfA0,ZfHp(2,2),ZfVWp

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

  Do gt2=1,2
! External masses 
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplA0HpcVWp(gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfA0*cplA0HpcVWp(gt2)


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHp(i1,gt2)*cplA0HpcVWp(i1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWp*cplA0HpcVWp(gt2)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt2) = AmpC 
  End Do
End Subroutine Amplitude_WAVE_Inert2_A0ToHpcVWp


Subroutine Amplitude_VERTEX_Inert2_A0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,           & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,         & 
& cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0HpcVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplhhHpcHp(2,2),          & 
& cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),            & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1(2),            & 
& cplA0HpcVWpVZ1(2),cplH0HpcVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MVWp 


! {A0, G0, conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplA0A0G0
coup2 = cplA0HpcHp(gt2,i3)
coup3 = -cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, hh, conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplA0HpcHp(gt2,i3)
coup3 = -cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {A0, hh, conj[VWp]}
ML1 = MA0 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplA0A0hh
coup2 = -cplA0HpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {H0, G0, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplA0G0H0
coup2 = cplH0HpcHp(gt2,i3)
coup3 = -cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, hh, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplH0HpcHp(gt2,i3)
coup3 = -cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, VZ, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = -cplA0H0VZ
coup2 = cplH0HpcHp(gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, hh, conj[VWp]}
ML1 = MH0 
ML2 = Mhh 
ML3 = MVWp 
coup1 = cplA0H0hh
coup2 = -cplH0HpcVWp(gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {H0, VZ, conj[VWp]}
ML1 = MH0 
ML2 = MVZ 
ML3 = MVWp 
coup1 = -cplA0H0VZ
coup2 = -cplH0HpcVWp(gt2)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {hh, A0, conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplhhHpcHp(gt2,i3)
coup3 = -cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {hh, H0, conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplhhHpcHp(gt2,i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp, A0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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
coup1 = -cplA0cHpVWp(i2)
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
coup1 = -cplA0cHpVWp(i2)
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
coup1 = -cplA0cHpVWp(i2)
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


! {VWp, Hp, VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = -cplA0cHpVWp(i2)
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


! {VWp, Hp, VZ}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = -cplA0cHpVWp(i2)
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


! {VZ, H0, conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = -cplA0H0VZ
coup2 = cplHpcHpVZ(gt2,i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
    End Do


! {H0, VZ}
ML1 = MH0 
ML2 = MVZ 
coup1 = cplA0H0VZ
coup2 = cplH0HpcVWpVZ1(gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplHpcHpcVWpVWp1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
End Do


! {A0, conj[VWp]}
ML1 = MA0 
ML2 = MVWp 
coup1 = cplA0A0cVWpVWp1
coup2 = -cplA0HpcVWp(gt2)
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
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0HpcVWpVZ1(i1)
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
End Subroutine Amplitude_VERTEX_Inert2_A0ToHpcVWp


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,             & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,       & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplH0HpcHp,         & 
& cplH0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplH0HpcVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0HpcVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplhhHpcHp(2,2),          & 
& cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplHpcHpVZ(2,2),            & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0HpcVWpVP1(2),            & 
& cplA0HpcVWpVZ1(2),cplH0HpcVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MA0 
Mex2 = MHp(gt2) 
Mex3 = MVWp 


! {Hp, Hp, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
coup2 = cplHpcVWpVP(gt2)
coup3 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplA0HpcVWpVP1(i1)
coup2 = cplHpcHpVP(gt2,i1)
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt2) = Amp(:,gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToHpcVWp


Subroutine Amplitude_WAVE_Inert2_A0ToA0A0(MA0,MA02,ZfA0,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02

Complex(dp), Intent(in) :: ZfA0

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToA0A0


Subroutine Amplitude_VERTEX_Inert2_A0ToA0A0(MA0,MHp,MVWp,MA02,MHp2,MVWp2,             & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplA0A0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVWp,MA02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplA0A0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MA0 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplA0A0HpcHp1(i2,i1)
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
coup1 = cplA0A0HpcHp1(i1,i2)
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
coup1 = cplA0A0HpcHp1(i1,i2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0ToA0A0


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0A0(MA0,MHp,MVWp,MA02,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplA0A0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVWp,MA02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplA0A0HpcHp1(2,2)

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
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MA0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0A0


Subroutine Amplitude_WAVE_Inert2_A0ToA0H0(MA0,MA02,MH0,MH02,ZfA0,ZfH0,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02

Complex(dp), Intent(in) :: ZfA0,ZfH0

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToA0H0


Subroutine Amplitude_VERTEX_Inert2_A0ToA0H0(MA0,MH0,MHp,MVWp,MA02,MH02,               & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,      & 
& cplA0A0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MHp(2),MVWp,MA02,MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),         & 
& cplH0cHpVWp(2),cplA0A0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MH0 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplA0HpcHp(i3,i1)
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
coup1 = -cplA0HpcVWp(i1)
coup2 = cplA0HpcHp(i3,i1)
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
coup2 = -cplA0HpcVWp(i3)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
coup2 = cplA0HpcHp(i1,i3)
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
coup1 = cplA0HpcHp(i2,i1)
coup2 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
coup2 = -cplA0cHpVWp(i3)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0A0HpcHp1(i1,i2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0ToA0H0


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0H0(MA0,MH0,MHp,MVWp,MA02,MH02,            & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,      & 
& cplA0A0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MHp(2),MVWp,MA02,MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),         & 
& cplH0cHpVWp(2),cplA0A0HpcHp1(2,2)

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
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MH0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0H0


Subroutine Amplitude_WAVE_Inert2_A0ToA0VP(MA0,MA02,MVP,MVP2,ZfA0,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MVP,MVP2

Complex(dp), Intent(in) :: ZfA0,ZfVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToA0VP


Subroutine Amplitude_VERTEX_Inert2_A0ToA0VP(MA0,MHp,MVP,MVWp,MA02,MHp2,               & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,      & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVP,MVWp,MA02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),         & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MVP 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplA0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplA0HpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplA0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToA0VP


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0VP(MA0,MHp,MVP,MVWp,MA02,MHp2,            & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,      & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVP,MVWp,MA02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),         & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2)

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
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0VP


Subroutine Amplitude_WAVE_Inert2_A0ToA0VZ(MA0,MA02,MVZ,MVZ2,ZfA0,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfA0,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToA0VZ


Subroutine Amplitude_VERTEX_Inert2_A0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,             & 
& MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,           & 
& cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),      & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MVZ 


! {A0, hh, G0}
ML1 = MA0 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplA0A0hh
coup2 = cplA0A0G0
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {A0, G0, hh}
ML1 = MA0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplA0A0G0
coup2 = cplA0A0hh
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {G0, H0, A0}
ML1 = MG0 
ML2 = MH0 
ML3 = MA0 
coup1 = cplA0G0H0
coup2 = cplA0A0G0
coup3 = cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {G0, A0, H0}
ML1 = MG0 
ML2 = MA0 
ML3 = MH0 
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = -cplA0H0VZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, hh, G0}
ML1 = MH0 
ML2 = Mhh 
ML3 = MG0 
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, G0, hh}
ML1 = MH0 
ML2 = MG0 
ML3 = Mhh 
coup1 = cplA0G0H0
coup2 = cplA0H0hh
coup3 = -cplG0hhVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, VZ, hh}
ML1 = MH0 
ML2 = MVZ 
ML3 = Mhh 
coup1 = -cplA0H0VZ
coup2 = cplA0H0hh
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {H0, hh, VZ}
ML1 = MH0 
ML2 = Mhh 
ML3 = MVZ 
coup1 = cplA0H0hh
coup2 = cplA0H0VZ
coup3 = cplhhVZVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 


! {hh, H0, A0}
ML1 = Mhh 
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


! {hh, A0, H0}
ML1 = Mhh 
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


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplA0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplA0HpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplA0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToA0VZ


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0VZ(MA0,MG0,MH0,Mhh,MHp,MVWp,              & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,       & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,           & 
& cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),      & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2)

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
Mex1 = MA0 
Mex2 = MA0 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToA0VZ


Subroutine Amplitude_WAVE_Inert2_A0ToFdcFd(MA0,MA02,MFd,MFd2,ZfA0,ZfDL,ZfDR,Amp)

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

  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MA0 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToFdcFd


Subroutine Amplitude_VERTEX_Inert2_A0ToFdcFd(MA0,MFd,MFu,MHp,MVWp,MA02,               & 
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
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 


! {conj[Hp], conj[Hp], bar[Fu]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MFu(i3) 
coup1 = cplA0HpcHp(i2,i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
coup3L = cplcFdFucHpL(gt3,i3,i2)
coup3R = cplcFdFucHpR(gt3,i3,i2)
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


! {conj[Hp], conj[VWp], bar[Fu]}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MFu(i3) 
coup1 = cplA0cHpVWp(i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
coup3L = -cplcFdFucVWpR(gt3,i3)
coup3R = -cplcFdFucVWpL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[VWp], conj[Hp], bar[Fu]}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MFu(i3) 
coup1 = cplA0HpcVWp(i2)
coup2L = -cplcFuFdVWpR(i3,gt2)
coup2R = -cplcFuFdVWpL(i3,gt2)
coup3L = cplcFdFucHpL(gt3,i3,i2)
coup3R = cplcFdFucHpR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToFdcFd


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFdcFd(MA0,MFd,MFu,MHp,MVWp,MA02,            & 
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
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MA0 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFdcFd


Subroutine Amplitude_WAVE_Inert2_A0ToFecFe(MA0,MA02,MFe,MFe2,ZfA0,ZfEL,ZfER,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MFe(3),MFe2(3)

Complex(dp), Intent(in) :: ZfA0,ZfEL(3,3),ZfER(3,3)

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
Mex1 = MA0 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToFecFe


Subroutine Amplitude_VERTEX_Inert2_A0ToFecFe(MA0,MFe,MHp,MVWp,MA02,MFe2,              & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,    & 
& cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFe(3),MHp(2),MVWp,MA02,MFe2(3),MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),  & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),           & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3)

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
Mex1 = MA0 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 


! {conj[Hp], conj[Hp], bar[Fv]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = 0._dp 
coup1 = cplA0HpcHp(i2,i1)
coup2L = cplcFvFeHpL(i3,gt2,i1)
coup2R = cplcFvFeHpR(i3,gt2,i1)
coup3L = cplcFeFvcHpL(gt3,i3,i2)
coup3R = cplcFeFvcHpR(gt3,i3,i2)
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


! {conj[Hp], conj[VWp], bar[Fv]}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = 0._dp 
coup1 = cplA0cHpVWp(i1)
coup2L = cplcFvFeHpL(i3,gt2,i1)
coup2R = cplcFvFeHpR(i3,gt2,i1)
coup3L = -cplcFeFvcVWpR(gt3,i3)
coup3R = -cplcFeFvcVWpL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[VWp], conj[Hp], bar[Fv]}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = 0._dp 
coup1 = cplA0HpcVWp(i2)
coup2L = -cplcFvFeVWpR(i3,gt2)
coup2R = -cplcFvFeVWpL(i3,gt2)
coup3L = cplcFeFvcHpL(gt3,i3,i2)
coup3R = cplcFeFvcHpR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToFecFe


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFecFe(MA0,MFe,MHp,MVWp,MA02,MFe2,           & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,    & 
& cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFe(3),MHp(2),MVWp,MA02,MFe2(3),MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),  & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),           & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3)

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
Mex1 = MA0 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFecFe


Subroutine Amplitude_WAVE_Inert2_A0ToFucFu(MA0,MA02,MFu,MFu2,ZfA0,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MFu(3),MFu2(3)

Complex(dp), Intent(in) :: ZfA0,ZfUL(3,3),ZfUR(3,3)

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
Mex1 = MA0 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToFucFu


Subroutine Amplitude_VERTEX_Inert2_A0ToFucFu(MA0,MFd,MFu,MHp,MVWp,MA02,               & 
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
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 


! {Hp, Hp, bar[Fd]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = cplA0HpcHp(i1,i2)
coup2L = cplcFdFucHpL(i3,gt2,i1)
coup2R = cplcFdFucHpR(i3,gt2,i1)
coup3L = cplcFuFdHpL(gt3,i3,i2)
coup3R = cplcFuFdHpR(gt3,i3,i2)
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


! {Hp, VWp, bar[Fd]}
Do i1=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MFd(i3) 
coup1 = cplA0HpcVWp(i1)
coup2L = cplcFdFucHpL(i3,gt2,i1)
coup2R = cplcFdFucHpR(i3,gt2,i1)
coup3L = -cplcFuFdVWpR(gt3,i3)
coup3R = -cplcFuFdVWpL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VWp, Hp, bar[Fd]}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MFd(i3) 
coup1 = cplA0cHpVWp(i2)
coup2L = -cplcFdFucVWpR(i3,gt2)
coup2R = -cplcFdFucVWpL(i3,gt2)
coup3L = cplcFuFdHpL(gt3,i3,i2)
coup3R = cplcFuFdHpR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt2, gt3) = Amp(:,gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToFucFu


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFucFu(MA0,MFd,MFu,MHp,MVWp,MA02,            & 
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
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MA0 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFucFu


Subroutine Amplitude_WAVE_Inert2_A0ToFvcFv(MA0,MA02,ZfA0,ZfvL,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02

Complex(dp), Intent(in) :: ZfA0,ZfvL(3,3)

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
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToFvcFv


Subroutine Amplitude_VERTEX_Inert2_A0ToFvcFv(MA0,MFe,MHp,MVWp,MA02,MFe2,              & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,    & 
& cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFe(3),MHp(2),MVWp,MA02,MFe2(3),MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),  & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),           & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3)

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
Mex1 = MA0 
Mex2 = 0._dp 
Mex3 = 0._dp 


! {Hp, Hp, bar[Fe]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MFe(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0cHpVWp(i2)
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
    End Do
  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToFvcFv


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFvcFv(MA0,MFe,MHp,MVWp,MA02,MFe2,           & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,    & 
& cplcFvFeVWpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFe(3),MHp(2),MVWp,MA02,MFe2(3),MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),  & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),           & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3)

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
Mex1 = MA0 
Mex2 = 0._dp 
Mex3 = 0._dp 
    End Do
  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToFvcFv


Subroutine Amplitude_WAVE_Inert2_A0ToG0G0(MA0,MA02,MG0,MG02,ZfA0,ZfG0,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MG0,MG02

Complex(dp), Intent(in) :: ZfA0,ZfG0

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MG0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToG0G0


Subroutine Amplitude_VERTEX_Inert2_A0ToG0G0(MA0,MG0,MHp,MVWp,MA02,MG02,               & 
& MHp2,MVWp2,cplA0HpcHp,cplG0HpcVWp,cplG0cHpVWp,cplG0G0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MHp(2),MVWp,MA02,MG02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplG0HpcVWp(2),cplG0cHpVWp(2),cplG0G0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MG0 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i1,i2)
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


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,i1)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplG0G0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToG0G0


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0G0(MA0,MG0,MHp,MVWp,MA02,MG02,            & 
& MHp2,MVWp2,cplA0HpcHp,cplG0HpcVWp,cplG0cHpVWp,cplG0G0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MHp(2),MVWp,MA02,MG02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplG0HpcVWp(2),cplG0cHpVWp(2),cplG0G0HpcHp1(2,2)

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
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MG0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0G0


Subroutine Amplitude_WAVE_Inert2_A0ToG0hh(MA0,MA02,MG0,MG02,Mhh,Mhh2,ZfA0,            & 
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
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToG0hh


Subroutine Amplitude_VERTEX_Inert2_A0ToG0hh(MA0,MG0,Mhh,MHp,MVWp,MA02,MG02,           & 
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
Mex1 = MA0 
Mex2 = MG0 
Mex3 = Mhh 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0G0HpcHp1(i1,i2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0ToG0hh


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0hh(MA0,MG0,Mhh,MHp,MVWp,MA02,             & 
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
Mex1 = MA0 
Mex2 = MG0 
Mex3 = Mhh 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0hh


Subroutine Amplitude_WAVE_Inert2_A0ToG0VP(MA0,MA02,MG0,MG02,MVP,MVP2,ZfA0,            & 
& ZfG0,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MG0,MG02,MVP,MVP2

Complex(dp), Intent(in) :: ZfA0,ZfG0,ZfVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_A0ToG0VP


Subroutine Amplitude_VERTEX_Inert2_A0ToG0VP(MA0,MG0,MHp,MVP,MVWp,MA02,MG02,           & 
& MHp2,MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,            & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,         & 
& cplG0HpcVWpVP1,cplG0cHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MHp(2),MVP,MVWp,MA02,MG02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),          & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplA0HpcVWpVP1(2),          & 
& cplA0cHpVPVWp1(2),cplG0HpcVWpVP1(2),cplG0cHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MVP 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplG0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplG0HpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplG0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToG0VP


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0VP(MA0,MG0,MHp,MVP,MVWp,MA02,             & 
& MG02,MHp2,MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,       & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,         & 
& cplG0HpcVWpVP1,cplG0cHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MHp(2),MVP,MVWp,MA02,MG02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),          & 
& cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplA0HpcVWpVP1(2),          & 
& cplA0cHpVPVWp1(2),cplG0HpcVWpVP1(2),cplG0cHpVPVWp1(2)

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
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0VP


Subroutine Amplitude_WAVE_Inert2_A0ToG0VZ(MA0,MA02,MG0,MG02,MVZ,MVZ2,ZfA0,            & 
& ZfG0,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MG0,MG02,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfA0,ZfG0,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MG0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToG0VZ


Subroutine Amplitude_VERTEX_Inert2_A0ToG0VZ(MA0,MG0,MHp,MVWp,MVZ,MA02,MG02,           & 
& MHp2,MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,            & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,         & 
& cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MHp(2),MVWp,MVZ,MA02,MG02,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),          & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),          & 
& cplA0cHpVWpVZ1(2),cplG0HpcVWpVZ1(2),cplG0cHpVWpVZ1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MVZ 


! {Hp, Hp, VWp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[Hp], conj[VWp]}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplG0cHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplG0HpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplG0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToG0VZ


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0VZ(MA0,MG0,MHp,MVWp,MVZ,MA02,             & 
& MG02,MHp2,MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,       & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,         & 
& cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MHp(2),MVWp,MVZ,MA02,MG02,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),          & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),          & 
& cplA0cHpVWpVZ1(2),cplG0HpcVWpVZ1(2),cplG0cHpVWpVZ1(2)

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
Mex1 = MA0 
Mex2 = MG0 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToG0VZ


Subroutine Amplitude_WAVE_Inert2_A0ToH0H0(MA0,MA02,MH0,MH02,ZfA0,ZfH0,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02

Complex(dp), Intent(in) :: ZfA0,ZfH0

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MH0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToH0H0


Subroutine Amplitude_VERTEX_Inert2_A0ToH0H0(MA0,MH0,MHp,MVWp,MA02,MH02,               & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,      & 
& cplH0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MHp(2),MVWp,MA02,MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),         & 
& cplH0cHpVWp(2),cplH0H0HpcHp1(2,2)

Complex(dp), Intent(out) :: Amp 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MH0 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplH0H0HpcHp1(i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp = Amp + oo16pi2*(1)*AmpC 
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToH0H0


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0H0(MA0,MH0,MHp,MVWp,MA02,MH02,            & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,      & 
& cplH0H0HpcHp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MHp(2),MVWp,MA02,MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),         & 
& cplH0cHpVWp(2),cplH0H0HpcHp1(2,2)

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
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MH0 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0H0


Subroutine Amplitude_WAVE_Inert2_A0ToH0VP(cplA0H0VZ,ctcplA0H0VZ,MA0,MA02,             & 
& MH0,MH02,MVP,MVP2,MVZ,MVZ2,ZfA0,ZfH0,ZfVP,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0H0VZ

Complex(dp), Intent(in) :: ctcplA0H0VZ

Complex(dp), Intent(in) :: ZfA0,ZfH0,ZfVP,ZfVZVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZVP*cplA0H0VZ


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:) = AmpC 
End Subroutine Amplitude_WAVE_Inert2_A0ToH0VP


Subroutine Amplitude_VERTEX_Inert2_A0ToH0VP(MA0,MH0,MHp,MVP,MVWp,MA02,MH02,           & 
& MHp2,MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,             & 
& cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,            & 
& cplA0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MHp(2),MVP,MVWp,MA02,MH02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),         & 
& cplH0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,             & 
& cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplH0HpcVWpVP1(2),cplH0cHpVPVWp1(2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MVP 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWp(i1)
coup2 = cplH0cHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplH0HpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplH0HpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToH0VP


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0VP(MA0,MH0,MHp,MVP,MVWp,MA02,             & 
& MH02,MHp2,MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplH0HpcHp,cplH0HpcVWp,        & 
& cplH0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,            & 
& cplA0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MH0,MHp(2),MVP,MVWp,MA02,MH02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),         & 
& cplH0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp,             & 
& cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplH0HpcVWpVP1(2),cplH0cHpVPVWp1(2)

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
Mex1 = MA0 
Mex2 = MH0 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToH0VP


Subroutine Amplitude_WAVE_Inert2_A0Tohhhh(MA0,MA02,Mhh,Mhh2,ZfA0,Zfhh,Amp)

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
Mex1 = MA0 
Mex2 = Mhh 
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
End Subroutine Amplitude_WAVE_Inert2_A0Tohhhh


Subroutine Amplitude_VERTEX_Inert2_A0Tohhhh(MA0,Mhh,MHp,MVWp,MA02,Mhh2,               & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = Mhh 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0HpcVWp(i2)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplhhhhHpcHp1(i2,i1)
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
coup1 = cplA0hhHpcHp1(i1,i2)
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
End Subroutine Amplitude_VERTEX_Inert2_A0Tohhhh


Subroutine Amplitude_IR_VERTEX_Inert2_A0Tohhhh(MA0,Mhh,MHp,MVWp,MA02,Mhh2,            & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = Mhh 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0Tohhhh


Subroutine Amplitude_WAVE_Inert2_A0TohhVP(MA0,MA02,Mhh,Mhh2,MVP,MVP2,ZfA0,            & 
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
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0TohhVP


Subroutine Amplitude_VERTEX_Inert2_A0TohhVP(MA0,Mhh,MHp,MVP,MVWp,MA02,Mhh2,           & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MVP 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0HpcVWp(i2)
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
coup1 = cplA0HpcVWp(i1)
coup2 = cplhhcHpVPVWp1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplhhHpcVWpVP1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplhhHpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0TohhVP


Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhVP(MA0,Mhh,MHp,MVP,MVWp,MA02,             & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhVP


Subroutine Amplitude_WAVE_Inert2_A0TohhVZ(MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,ZfA0,            & 
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
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0TohhVZ


Subroutine Amplitude_VERTEX_Inert2_A0TohhVZ(MA0,Mhh,MHp,MVWp,MVZ,MA02,Mhh2,           & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MVZ 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = -cplA0HpcVWp(i1)
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
coup1 = -cplA0cHpVWp(i2)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = -cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = -cplA0cHpVWp(i1)
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
coup1 = -cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = -cplA0HpcVWp(i2)
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
coup1 = cplA0HpcVWp(i1)
coup2 = cplhhcHpVWpVZ1(i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
coup1 = cplA0cHpVWp(i2)
coup2 = cplhhHpcVWpVZ1(i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplhhHpcVWp(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0TohhVZ


Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhVZ(MA0,Mhh,MHp,MVWp,MVZ,MA02,             & 
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
Mex1 = MA0 
Mex2 = Mhh 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0TohhVZ


Subroutine Amplitude_WAVE_Inert2_A0ToVPVP(MA0,MA02,MVP,MVP2,ZfA0,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MVP,MVP2

Complex(dp), Intent(in) :: ZfA0,ZfVP

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToVPVP


Subroutine Amplitude_VERTEX_Inert2_A0ToVPVP(MA0,MHp,MVP,MVWp,MA02,MHp2,               & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,      & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplHpcHpVPVP1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVP,MVWp,MA02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),         & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplHpcHpVPVP1(2,2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MVP 
Mex3 = MVP 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0cHpVWp(i2)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = cplA0cHpVWp(i1)
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
coup1 = cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcVWp(i2)
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplHpcHpVPVP1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
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
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToVPVP


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVPVP(MA0,MHp,MVP,MVWp,MA02,MHp2,            & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,      & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplHpcHpVPVP1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVP,MVWp,MA02,MHp2(2),MVP2,MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),         & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplA0HpcVWpVP1(2),cplA0cHpVPVWp1(2),cplHpcHpVPVP1(2,2)

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
Mex1 = MA0 
Mex2 = MVP 
Mex3 = MVP 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVPVP


Subroutine Amplitude_WAVE_Inert2_A0ToVPVZ(MA0,MA02,MVP,MVP2,MVZ,MVZ2,ZfA0,            & 
& ZfVP,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfA0,ZfVP,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToVPVZ


Subroutine Amplitude_VERTEX_Inert2_A0ToVPVZ(MA0,MHp,MVP,MVWp,MVZ,MA02,MHp2,           & 
& MVP2,MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,             & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplHpcHpVPVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVP,MVWp,MVZ,MA02,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),         & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplA0HpcVWpVP1(2),cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),  & 
& cplHpcHpVPVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MVP 
Mex3 = MVZ 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0cHpVWp(i2)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = cplA0cHpVWp(i1)
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
coup1 = cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcVWp(i2)
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplHpcHpVPVZ1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
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
coup1 = cplA0HpcVWpVP1(i1)
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
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToVPVZ


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVPVZ(MA0,MHp,MVP,MVWp,MVZ,MA02,             & 
& MHp2,MVP2,MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVP,cplHpcVWpVP,        & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplHpcHpVPVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVP,MVWp,MVZ,MA02,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVP(2,2),cplHpcVWpVP(2),         & 
& cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),             & 
& cplcVWpVWpVZ,cplA0HpcVWpVP1(2),cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),  & 
& cplHpcHpVPVZ1(2,2)

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
Mex1 = MA0 
Mex2 = MVP 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVPVZ


Subroutine Amplitude_WAVE_Inert2_A0ToVWpcVWp(MA0,MA02,MVWp,MVWp2,ZfA0,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MVWp,MVWp2

Complex(dp), Intent(in) :: ZfA0,ZfVWp

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
Mex2 = MVWp 
Mex3 = MVWp 
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
End Subroutine Amplitude_WAVE_Inert2_A0ToVWpcVWp


Subroutine Amplitude_VERTEX_Inert2_A0ToVWpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,               & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,       & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcVWpVP,              & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVP1,          & 
& cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),            & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),cplHpcVWpVZ(2),              & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVP1(2),             & 
& cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MVWp 
Mex3 = MVWp 


! {A0, G0, conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplA0A0G0
coup2 = cplA0cHpVWp(i3)
coup3 = -cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {A0, hh, conj[Hp]}
    Do i3=1,2
ML1 = MA0 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplA0cHpVWp(i3)
coup3 = -cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {G0, A0, conj[Hp]}
    Do i3=1,2
ML1 = MG0 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0G0
coup2 = cplG0cHpVWp(i3)
coup3 = -cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {G0, H0, conj[Hp]}
    Do i3=1,2
ML1 = MG0 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0G0H0
coup2 = cplG0cHpVWp(i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {H0, G0, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MG0 
ML3 = MHp(i3) 
coup1 = cplA0G0H0
coup2 = cplH0cHpVWp(i3)
coup3 = -cplG0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {H0, hh, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplH0cHpVWp(i3)
coup3 = -cplhhHpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {H0, VZ, conj[Hp]}
    Do i3=1,2
ML1 = MH0 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1 = cplA0H0VZ
coup2 = cplH0cHpVWp(i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {hh, A0, conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MA0 
ML3 = MHp(i3) 
coup1 = cplA0A0hh
coup2 = cplhhcHpVWp(i3)
coup3 = -cplA0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {hh, H0, conj[Hp]}
    Do i3=1,2
ML1 = Mhh 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0hh
coup2 = cplhhcHpVWp(i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
    End Do


! {Hp, Hp, A0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MA0 
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplA0cHpVWp(i1)
coup3 = cplA0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp, G0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MG0 
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplG0cHpVWp(i1)
coup3 = cplG0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp, H0}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MH0 
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplH0cHpVWp(i1)
coup3 = cplH0HpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, Hp, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplA0HpcHp(i1,i2)
coup2 = -cplhhcHpVWp(i1)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, hh}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = Mhh 
coup1 = cplA0HpcVWp(i1)
coup2 = -cplhhcHpVWp(i1)
coup3 = cplhhcVWpVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {Hp, Hp, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplA0HpcHp(i1,i2)
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


! {Hp, VWp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplA0HpcVWp(i1)
coup2 = cplcHpVPVWp(i1)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {Hp, Hp, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplA0HpcHp(i1,i2)
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


! {Hp, VWp, VZ}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVZ 
coup1 = cplA0HpcVWp(i1)
coup2 = cplcHpVWpVZ(i1)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, hh}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1 = cplA0cHpVWp(i2)
coup2 = cplhhcVWpVWp
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, Hp, VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplA0cHpVWp(i2)
coup2 = -cplcVWpVPVWp
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VWp, Hp, VZ}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1 = cplA0cHpVWp(i2)
coup2 = cplcVWpVWpVZ
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, H0, conj[Hp]}
    Do i3=1,2
ML1 = MVZ 
ML2 = MH0 
ML3 = MHp(i3) 
coup1 = cplA0H0VZ
coup2 = cplcHpVWpVZ(i3)
coup3 = -cplH0HpcVWp(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
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
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplHpcHpcVWpVWp1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplA0HpcVWpVP1(i1)
coup2 = cplcHpVPVWp(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
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
coup1 = cplA0HpcVWpVZ1(i1)
coup2 = cplcHpVWpVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VP, Hp}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToVWpcVWp


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVWpcVWp(MA0,MG0,MH0,Mhh,MHp,MVP,            & 
& MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,       & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcVWpVP,              & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVP1,          & 
& cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplHpcHpcVWpVWp1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MG0,MH0,Mhh,MHp(2),MVP,MVWp,MVZ,MA02,MG02,MH02,Mhh2,MHp2(2),MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0cHpVWp(2),cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),            & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),cplHpcVWpVZ(2),              & 
& cplcHpVPVWp(2),cplcVWpVPVWp,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVP1(2),             & 
& cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),cplHpcHpcVWpVWp1(2,2)

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
Mex1 = MA0 
Mex2 = MVWp 
Mex3 = MVWp 


! {Hp, Hp, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplcHpVPVWp(i1)
coup3 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1 = cplA0HpcVWp(i1)
coup2 = cplcHpVPVWp(i1)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
End Do


! {VWp, Hp, VP}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVP 
coup1 = cplA0cHpVWp(i2)
coup2 = -cplcVWpVPVWp
coup3 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do


! {Hp, VP}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVP 
coup1 = cplA0HpcVWpVP1(i1)
coup2 = cplcHpVPVWp(i1)
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

End Do


! {VP, Hp}
  Do i2=1,2
ML1 = MVP 
ML2 = MHp(i2) 
coup1 = cplA0cHpVPVWp1(i2)
coup2 = cplHpcVWpVP(i2)
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVWpcVWp


Subroutine Amplitude_WAVE_Inert2_A0ToVZVZ(MA0,MA02,MVZ,MVZ2,ZfA0,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfA0,ZfVZ

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

! External masses 
Mex1 = MA0 
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
Amp(:) = 0._dp
End Subroutine Amplitude_WAVE_Inert2_A0ToVZVZ


Subroutine Amplitude_VERTEX_Inert2_A0ToVZVZ(MA0,MHp,MVWp,MVZ,MA02,MHp2,               & 
& MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,      & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplHpcHpVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVWp,MVZ,MA02,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2),         & 
& cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2),cplHpcHpVZVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Amp(:) = 0._dp 
! External masses 
Mex1 = MA0 
Mex2 = MVZ 
Mex3 = MVZ 


! {Hp, Hp, Hp}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0HpcHp(i1,i2)
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
coup1 = cplA0HpcVWp(i1)
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
coup1 = cplA0cHpVWp(i2)
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


! {VWp, Hp, VWp}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0cHpVWp(i2)
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


! {conj[Hp], conj[VWp], conj[Hp]}
Do i1=1,2
    Do i3=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1 = cplA0cHpVWp(i1)
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
coup1 = cplA0HpcHp(i2,i1)
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
coup1 = cplA0cHpVWp(i1)
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
coup1 = cplA0HpcVWp(i2)
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


! {conj[VWp], conj[Hp], conj[VWp]}
  Do i2=1,2
ML1 = MVWp 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1 = cplA0HpcVWp(i2)
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


! {Hp, Hp}
Do i1=1,2
  Do i2=1,2
ML1 = MHp(i1) 
ML2 = MHp(i2) 
coup1 = cplA0HpcHp(i1,i2)
coup2 = cplHpcHpVZVZ1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hp, VWp}
Do i1=1,2
ML1 = MHp(i1) 
ML2 = MVWp 
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplHpcVWpVZ(i2)
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
coup1 = cplA0HpcVWpVZ1(i1)
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
coup1 = cplA0cHpVWpVZ1(i2)
coup2 = cplHpcVWpVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:) = Amp(:) + oo16pi2*(1)*AmpC 

  End Do
End Subroutine Amplitude_VERTEX_Inert2_A0ToVZVZ


Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVZVZ(MA0,MHp,MVWp,MVZ,MA02,MHp2,            & 
& MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,      & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplHpcHpVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MHp(2),MVWp,MVZ,MA02,MHp2(2),MVWp2,MVZ2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2),         & 
& cplcHpVWpVZ(2),cplcVWpVWpVZ,cplA0HpcVWpVZ1(2),cplA0cHpVWpVZ1(2),cplHpcHpVZVZ1(2,2)

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
Mex1 = MA0 
Mex2 = MVZ 
Mex3 = MVZ 

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_A0ToVZVZ



End Module OneLoopDecay_A0_Inert2
