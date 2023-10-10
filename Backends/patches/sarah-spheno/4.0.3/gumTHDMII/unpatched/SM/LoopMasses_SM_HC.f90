! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version SARAHVERSION 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:23 on 7.1.2017   
! ----------------------------------------------------------------------  
 
 
Module LoopMasses_SM_HC
 
Use Control 
Use Settings 
Use Couplings_SM_HC
Use LoopFunctions 
Use AddLoopFunctions 
Use Mathematics 
Use MathematicsQP 
Use StandardModel 
Use RGEs_SM_HC
! Use EffectivePotential_SM_HC 
! Use Pole2L_SM_HC
Use TreeLevelMasses_SM_HC 
 
Real(dp), Private :: MHp_1L, MHp2_1L  
Real(dp), Private :: MAh_1L, MAh2_1L  
Real(dp), Private :: Mhh_1L, Mhh2_1L  
Real(dp), Private :: MVZ_1L, MVZ2_1L  
Real(dp), Private :: MVWp_1L, MVWp2_1L  
Real(dp) :: pi2A0  
Real(dp) :: ti_ep2L_SM(1)  
Real(dp) :: pi_ep2L(1,1)
Real(dp) :: Pi2S_EffPot_SM(1,1)
Real(dp) :: PiP2S_EffPot_SM(1,1)
Contains 


Subroutine Pi1Loop_Mh_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,mh_pole,pi_SM,kont)

Implicit None 
Real(dp),Intent(inout) :: g1,g2,g3
Real(dp), Intent(in) :: mh_pole
Real(dp), Intent(out) :: pi_SM
Complex(dp),Intent(inout) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3)
Complex(dp) :: Mu

Real(dp) :: MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,MHp,MHp2,              & 
& MVWp,MVWp2,MVZ,MVZ2,TW,ZZ(2,2)

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Real(dp),Intent(inout) :: v

Complex(dp) :: cplAhAhAhAh,cplAhAhcVWpVWp,cplAhAhhh,cplAhAhhhhh,cplAhAhHpcHp,cplAhAhVZVZ,            & 
& cplAhcHpVWp,cplAhhhVZ,cplAhHpcVWp,cplcFdFdAhL(3,3),cplcFdFdAhR(3,3),cplcFdFdhhL(3,3),  & 
& cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),  & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3),cplcFdFucHpR(3,3),cplcFdFucVWpL(3,3),& 
& cplcFdFucVWpR(3,3),cplcFeFeAhL(3,3),cplcFeFeAhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),& 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3), & 
& cplcFeFvcHpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFuAhL(3,3),              & 
& cplcFuFuAhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
& cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgGgGVG,cplcgWCgAcVWp,cplcgWCgWCAh,cplcgWCgWChh,     & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp,cplcgWCgZcVWp,cplcgWpgWpAh,cplcgWpgWphh,        & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWpgZHp,cplcgZgWCHp,cplcgZgWpcHp,cplcgZgWpcVWp,          & 
& cplcgZgZhh,cplcHpVPVWp,cplcHpVWpVZ,cplcUFdFdAhL(3,3),cplcUFdFdAhR(3,3),cplcUFdFdhhL(3,3),& 
& cplcUFdFdhhR(3,3),cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),               & 
& cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3),              & 
& cplcUFdFucHpR(3,3),cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3),cplcUFeFeAhL(3,3),          & 
& cplcUFeFeAhR(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),cplcUFeFeVPL(3,3),               & 
& cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),cplcUFeFvcHpL(3,3),              & 
& cplcUFeFvcHpR(3,3),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3),cplcUFuFdHpL(3,3),          & 
& cplcUFuFdHpR(3,3),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuAhL(3,3),             & 
& cplcUFuFuAhR(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),               & 
& cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),               & 
& cplcUFuFuVZR(3,3),cplcUFvFeHpL(3,3),cplcUFvFeHpR(3,3),cplcUFvFeVWpL(3,3),              & 
& cplcUFvFeVWpR(3,3),cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3),cplcVWpcVWpVWpVWp1,             & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3, & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhhh,cplhhhhhhhh,cplhhhhHpcHp,            & 
& cplhhhhVZVZ,cplhhHpcHp,cplhhHpcVWp,cplhhVZVZ,cplHpcHpcVWpVWp,cplHpcHpVP,               & 
& cplHpcHpVPVP,cplHpcHpVZ,cplHpcHpVZVZ,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp,            & 
& cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1, j2, j3, j4, il, i_count, ierr 
Integer :: i2L, iFin 
Logical :: Convergence2L 
Real(dp) :: Pi2S_EffPot_save(1,1), diff(1,1)
Complex(dp) :: Tad1Loop(1), dmz2, MuTree, Mu1L, Mu2L, PiSf
Real(dp) :: comp(1), tanbQ, vev2, vSM
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopMasses' 
 
kont = 0 


Mu = 0.5_dp*Lam*v**2 
 
Call TreeMasses_SM(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,MHp2,MVWp,           & 
& MVWp2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,ZDL,ZEL,ZUL,ZW,ZZ,v,g1,g2,g3,Lam,Yu,Yd,Ye,               & 
& Mu,GenerationMixing,kont)

! mh_SM = Mhh

! MuTree  = Mu


! pi_SM = 0._dp

 
!  If (CalculateOneLoopMasses) Then 
 
! Call CouplingsForVectorBosons_SM(g2,g1,TW,v,ZDL,ZUL,ZEL,cplAhcHpVWp,cplhhcHpVWp,         & 
! & cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplHpcHpcVWpVWp,cplHpcHpVZVZ,cplAhhhVZ,             & 
! & cplAhHpcVWp,cplAhAhcVWpVWp,cplAhAhVZVZ,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,             & 
! & cplhhhhcVWpVWp,cplhhhhVZVZ,cplHpcVWpVP,cplcVWpVPVWp,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,   & 
! & cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,           & 
! & cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcVWpVZ,             & 
! & cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcFdFucVWpL,            & 
! & cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,   & 
! & cplcgWCgZcVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)
! 
! Call Pi1LoopVZ_SM(mZ2,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,             & 
! & MHp,MHp2,MVWp,MVWp2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
! & cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,             & 
! & cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,    & 
! & cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,dmZ2)
! 
! ! vev2=4._dp*Real(mZ2+dmz2,dp)/(g1**2+g2**2) -0 
! ! vSM=sqrt(vev2) 
! ! v=vSM 
! Call SolveTadpoleEquations_SM(g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v,(/ ZeroC /))

! Call TreeMasses_SM(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,MHp2,MVWp,           & 
! & MVWp2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,ZDL,ZEL,ZUL,ZW,ZZ,v,g1,g2,g3,Lam,Yu,Yd,Ye,               & 
! & Mu,GenerationMixing,kont)

Call CouplingsForLoopMasses_SM(Yd,ZDL,ZDR,g3,g1,g2,TW,Yu,ZUL,ZUR,Ye,ZEL,ZER,             & 
& v,Lam,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,cplcUFdFdVGR,   & 
& cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,cplcUFdFucHpR,       & 
& cplcUFdFucVWpL,cplcUFdFucVWpR,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdHpL,cplcUFuFdHpR,     & 
& cplcUFuFdVWpL,cplcUFuFdVWpR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,       & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeAhL,cplcUFeFeAhR,         & 
& cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,         & 
& cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,cplcUFvFeHpL,cplcUFvFeHpR,   & 
& cplcUFvFeVWpL,cplcUFvFeVWpR,cplcUFvFvVZL,cplcUFvFvVZR,cplAhcHpVWp,cplcFdFucHpL,        & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcgZgWpcHp,cplcgWpgZHp,cplcgWCgZcHp,          & 
& cplcgZgWCHp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& cplAhAhHpcHp,cplhhhhHpcHp,cplHpHpcHpcHp,cplHpcHpVPVP,cplHpcHpcVWpVWp,cplHpcHpVZVZ,     & 
& cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,     & 
& cplcgWpgWpAh,cplcgWCgWCAh,cplAhhhVZ,cplAhHpcVWp,cplAhAhAhAh,cplAhAhhhhh,               & 
& cplAhAhcVWpVWp,cplAhAhVZVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,            & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplhhhhhh,cplhhHpcVWp,    & 
& cplhhcVWpVWp,cplhhVZVZ,cplhhhhhhhh,cplhhhhcVWpVWp,cplhhhhVZVZ,cplcFdFdVGL,             & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,    & 
& cplVGVGVGVG3,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcgWpgWpVP,cplcgWCgWCVP,cplHpcVWpVP,cplcVWpVPVWp,cplcVWpVPVPVWp1,        & 
& cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,             & 
& cplHpcVWpVZ,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,              & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,   & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)

Call OneLoopTadpoleshh_SM(v,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,            & 
& MHp2,MVWp,MVWp2,MVZ,MVZ2,cplAhAhhh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,    & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplhhhhhh,cplhhHpcHp,     & 
& cplhhcVWpVWp,cplhhVZVZ,Tad1Loop(1:1))
! 
! MuTree  = Mu
! If (CalculateTwoLoopHiggsMasses) Then 
! Call CalculatePi2S_SM(0._dp,v,0._dp*g1,0._dp*g2,g3,Lam,Yu,Yd,Ye,Mu,kont,ti_ep2L_SM,Pi2S_EffPot_SM,         & 
! & PiP2S_EffPot_SM)
! Else ! Two loop turned off 
! Pi2S_EffPot_SM = 0._dp 
! ti_ep2L_SM = 0._dp 
! End if 
! 
! 
! 
! Call SolveTadpoleEquations_SM(g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v,Tad1Loop)
! 
! Mu1L = Mu
! Tad1Loop(1:1) = Tad1Loop(1:1) - ti_ep2L_SM 
! Call SolveTadpoleEquations_SM(g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v,Tad1Loop)
! 
! Mu2L = Mu


Call Pi1Loophh_SM(mh_pole,MAh,MAh2,MVZ,MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MHp,MHp2,MVWp,MVWp2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,              & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,cplhhhhhhhh,       & 
& cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,kont,PiSf)

! mh_SM = Mhh_1L

pi_SM = Real(PiSf,dp) - Pi2S_EffPot_SM(1,1) - Tad1Loop(1)/v

! End If 


Iname = Iname -1 
End Subroutine Pi1Loop_Mh_SM


Subroutine SolveTadpoleEquations_SM(g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v,Tad1Loop)

Implicit None
Real(dp),Intent(inout) :: g1,g2,g3,v

Complex(dp),Intent(inout) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3),Mu

Complex(dp), Intent(in) :: Tad1Loop(1)

! For numerical routines 
Real(dp) :: gC(62)
logical :: broycheck 
Real(dp) :: broyx(1)

! If (HighScaleModel.Eq."LOW") Then 
Mu = (v**2*Lam)/2._dp - Tad1Loop(1)/v

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (Real(Mu,dp).ne.Real(Mu,dp)) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for Mu" 
   Call TerminateProgram  
 End If 
 If (Abs(AImag(Mu)).gt.1.0E-04_dp) Then 
   Write(*,*) "No real solution of tadpole equations for Mu" 
   !Call TerminateProgram  
   Mu = Real(Mu,dp) 
!   SignOfMuChanged= .True. 
End If 
End Subroutine SolveTadpoleEquations_SM

 
Subroutine OneLoop_Z_W_SM(v,g1,g2,g3,Lam, Yu,Yd,Ye,kont,dmZ2,dmW2,dmW2_0)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3
Complex(dp),Intent(in) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3)
Complex(dp) :: Mu
Real(dp),Intent(inout) :: v
Complex(dp), Intent(out) :: dmW2, dmZ2, dmW2_0

Real(dp) :: MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,MHp,MHp2,              & 
& MVWp,MVWp2,MVZ,MVZ2,TW,ZZ(2,2)

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)


Complex(dp) :: cplAhAhAhAh,cplAhAhcVWpVWp,cplAhAhhh,cplAhAhhhhh,cplAhAhHpcHp,cplAhAhVZVZ,            & 
& cplAhcHpVWp,cplAhhhVZ,cplAhHpcVWp,cplcFdFdAhL(3,3),cplcFdFdAhR(3,3),cplcFdFdhhL(3,3),  & 
& cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),  & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3),cplcFdFucHpR(3,3),cplcFdFucVWpL(3,3),& 
& cplcFdFucVWpR(3,3),cplcFeFeAhL(3,3),cplcFeFeAhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),& 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3), & 
& cplcFeFvcHpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFuAhL(3,3),              & 
& cplcFuFuAhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
& cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgGgGVG,cplcgWCgAcVWp,cplcgWCgWCAh,cplcgWCgWChh,     & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp,cplcgWCgZcVWp,cplcgWpgWpAh,cplcgWpgWphh,        & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWpgZHp,cplcgZgWCHp,cplcgZgWpcHp,cplcgZgWpcVWp,          & 
& cplcgZgZhh,cplcHpVPVWp,cplcHpVWpVZ,cplcUFdFdAhL(3,3),cplcUFdFdAhR(3,3),cplcUFdFdhhL(3,3),& 
& cplcUFdFdhhR(3,3),cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),               & 
& cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3),              & 
& cplcUFdFucHpR(3,3),cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3),cplcUFeFeAhL(3,3),          & 
& cplcUFeFeAhR(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),cplcUFeFeVPL(3,3),               & 
& cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),cplcUFeFvcHpL(3,3),              & 
& cplcUFeFvcHpR(3,3),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3),cplcUFuFdHpL(3,3),          & 
& cplcUFuFdHpR(3,3),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuAhL(3,3),             & 
& cplcUFuFuAhR(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),               & 
& cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),               & 
& cplcUFuFuVZR(3,3),cplcUFvFeHpL(3,3),cplcUFvFeHpR(3,3),cplcUFvFeVWpL(3,3),              & 
& cplcUFvFeVWpR(3,3),cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3),cplcVWpcVWpVWpVWp1,             & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3, & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhhh,cplhhhhhhhh,cplhhhhHpcHp,            & 
& cplhhhhVZVZ,cplhhHpcHp,cplhhHpcVWp,cplhhVZVZ,cplHpcHpcVWpVWp,cplHpcHpVP,               & 
& cplHpcHpVPVP,cplHpcHpVZ,cplHpcHpVZVZ,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp,            & 
& cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1, j2, j3, j4, il, i_count, ierr 
Integer :: i2L, iFin 
Logical :: Convergence2L 
Real(dp) :: Pi2S_EffPot_save(1,1), diff(1,1)
Complex(dp) :: Tad1Loop(1)  
Real(dp) :: comp(1), tanbQ, vev2, vSM, p2
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoop_Z_W_SM ' 
 
kont = 0 

! Running angles 

 
Call TreeMasses_SM(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,MHp2,MVWp,           & 
& MVWp2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,ZDL,ZEL,ZUL,ZW,ZZ,v,g1,g2,g3,Lam,Yu,Yd,Ye,               & 
& Mu,GenerationMixing,kont)
 
Call CouplingsForVectorBosons_SM(g2,g1,TW,v,ZDL,ZUL,ZEL,cplAhcHpVWp,cplhhcHpVWp,         & 
& cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplHpcHpcVWpVWp,cplHpcHpVZVZ,cplAhhhVZ,             & 
& cplAhHpcVWp,cplAhAhcVWpVWp,cplAhAhVZVZ,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,             & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,cplHpcVWpVP,cplcVWpVPVWp,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,   & 
& cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcVWpVZ,             & 
& cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcFdFucVWpL,            & 
& cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,   & 
& cplcgWCgZcVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)

Call Pi1LoopVZ_SM(mZ2,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,             & 
& MHp,MHp2,MVWp,MVWp2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,             & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,    & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,dmZ2)

Call Pi1LoopVWp_SM(mw2,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,            & 
& Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,        & 
& cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,dmW2)

Call Pi1LoopVWp_SM(0._dp,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,            & 
& Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,        & 
& cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,dmW2_0)


Iname = Iname -1 
End Subroutine OneLoop_Z_W_SM 


Subroutine OneLoop_Z_W_Gamma_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,kont,PiZZ,PiZZ_mz2,PiWW,PiWW_mw2,PiZg_mz2,Pigg_mz2)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3
Complex(dp),Intent(in) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3)
Complex(dp) :: Mu
Real(dp),Intent(in) :: v
Complex(dp), Intent(out) :: PiZZ, PiZZ_mz2, PiWW,PiWW_mw2,PiZg_mz2, Pigg_mz2

Real(dp) :: MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,MHp,MHp2,              & 
& MVWp,MVWp2,MVZ,MVZ2,TW,ZZ(2,2)

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)


! Complex(dp) :: cplAhAhAhAh,cplAhAhcVWpVWp,cplAhAhhh,cplAhAhhhhh,cplAhAhHpcHp,cplAhAhVZVZ,            & 
! & cplAhcHpVWp,cplAhhhVZ,cplAhHpcVWp,cplcFdFdAhL(3,3),cplcFdFdAhR(3,3),cplcFdFdhhL(3,3),  & 
! & cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),  & 
! & cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3),cplcFdFucHpR(3,3),cplcFdFucVWpL(3,3),& 
! & cplcFdFucVWpR(3,3),cplcFeFeAhL(3,3),cplcFeFeAhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),& 
! & cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3), & 
! & cplcFeFvcHpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFuAhL(3,3),              & 
! & cplcFuFuAhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),  & 
! & cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
! & cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgGgGVG,cplcgWCgAcVWp,cplcgWCgWCAh,cplcgWCgWChh,     & 
! & cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp,cplcgWCgZcVWp,cplcgWpgWpAh,cplcgWpgWphh,        & 
! & cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWpgZHp,cplcgZgWCHp,cplcgZgWpcHp,cplcgZgWpcVWp,          & 
! & cplcgZgZhh,cplcHpVPVWp,cplcHpVWpVZ,cplcUFdFdAhL(3,3),cplcUFdFdAhR(3,3),cplcUFdFdhhL(3,3),& 
! & cplcUFdFdhhR(3,3),cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),               & 
! & cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3),              & 
! & cplcUFdFucHpR(3,3),cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3),cplcUFeFeAhL(3,3),          & 
! & cplcUFeFeAhR(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),cplcUFeFeVPL(3,3),               & 
! & cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),cplcUFeFvcHpL(3,3),              & 
! & cplcUFeFvcHpR(3,3),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3),cplcUFuFdHpL(3,3),          & 
! & cplcUFuFdHpR(3,3),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuAhL(3,3),             & 
! & cplcUFuFuAhR(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),               & 
! & cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),               & 
! & cplcUFuFuVZR(3,3),cplcUFvFeHpL(3,3),cplcUFvFeHpR(3,3),cplcUFvFeVWpL(3,3),              & 
! & cplcUFvFeVWpR(3,3),cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3),cplcVWpcVWpVWpVWp1,             & 
! & cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3, & 
! & cplcVWpVPVWp,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
! & cplhhcHpVWp,cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhhh,cplhhhhhhhh,cplhhhhHpcHp,            & 
! & cplhhhhVZVZ,cplhhHpcHp,cplhhHpcVWp,cplhhVZVZ,cplHpcHpcVWpVWp,cplHpcHpVP,               & 
! & cplHpcHpVPVP,cplHpcHpVZ,cplHpcHpVZVZ,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp,            & 
! & cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

Complex(dp) :: cplAhAhhh,cplhhhhhh,cplhhHpcHp,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpcHp,cplhhhhhhhh,      & 
& cplhhhhHpcHp,cplHpHpcHpcHp,cplAhhhVZ,cplAhHpcVWp,cplAhcHpVWp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,cplHpcVWpVZ,      & 
& cplcHpVPVWp,cplcHpVWpVZ,cplAhAhcVWpVWp,cplAhAhVZVZ,cplAhHpcVWpVP,cplAhHpcVWpVZ,        & 
& cplAhcHpVPVWp,cplAhcHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP,cplhhHpcVWpVZ,    & 
& cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,cplHpcHpcVWpVWp,cplHpcHpVZVZ,    & 
& cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdAhL(3,3),cplcFdFdAhR(3,3),cplcFeFeAhL(3,3),& 
& cplcFeFeAhR(3,3),cplcFuFuAhL(3,3),cplcFuFuAhR(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),  & 
& cplcFuFdHpL(3,3),cplcFuFdHpR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3),  & 
& cplcFvFeHpR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucHpL(3,3),cplcFdFucHpR(3,3),& 
& cplcFeFvcHpL(3,3),cplcFeFvcHpR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),& 
& cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),& 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),& 
& cplcFeFeVZR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),               & 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),               & 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,& 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2, & 
& cplcVWpcVWpVWpVWp3,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,         & 
& cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,      & 
& cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,        & 
& cplcgWpgWpAh,cplcgWCgWCAh,cplcgZgAhh,cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,            & 
& cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1, j2, j3, j4, il, i_count, ierr 
Integer :: i2L, iFin 
Logical :: Convergence2L 
Real(dp) :: Pi2S_EffPot_save(1,1), diff(1,1)
Complex(dp) :: Tad1Loop(1)  
Real(dp) :: comp(1), tanbQ, vev2, vSM, p2
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoop_Z_W_SM ' 
 
kont = 0 

! Running angles 

 
Call TreeMasses_SM(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,MHp2,MVWp,           & 
& MVWp2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,ZDL,ZEL,ZUL,ZW,ZZ,v,g1,g2,g3,Lam,Yu,Yd,Ye,               & 
& Mu,GenerationMixing,kont)

 
! Call CouplingsForVectorBosons_SM(g2,g1,TW,v,ZDL,ZUL,ZEL,cplAhcHpVWp,cplhhcHpVWp,         & 
! & cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplHpcHpcVWpVWp,cplHpcHpVZVZ,cplAhhhVZ,             & 
! & cplAhHpcVWp,cplAhAhcVWpVWp,cplAhAhVZVZ,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,             & 
! & cplhhhhcVWpVWp,cplhhhhVZVZ,cplHpcVWpVP,cplcVWpVPVWp,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,   & 
! & cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,           & 
! & cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcVWpVZ,             & 
! & cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcFdFucVWpL,            & 
! & cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,   & 
! & cplcgWCgZcVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)


Call AllCouplingsReallyAll_SM(Lam,v,g1,g2,TW,g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,             & 
& Yu,ZUL,ZUR,cplAhAhhh,cplhhhhhh,cplhhHpcHp,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpcHp,        & 
& cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,cplAhhhVZ,cplAhHpcVWp,cplAhcHpVWp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplAhAhcVWpVWp,cplAhAhVZVZ,cplAhHpcVWpVP,          & 
& cplAhHpcVWpVZ,cplAhcHpVPVWp,cplAhcHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP,    & 
& cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,cplHpcHpcVWpVWp,   & 
& cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdAhL,cplcFdFdAhR,              & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,               & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFvFvVZL,cplcFvFvVZR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWpVPVPVWp1,    & 
& cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,       & 
& cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWpVP,    & 
& cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,       & 
& cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpAh,cplcgWCgWCAh,cplcgZgAhh,          & 
& cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,           & 
& cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp)

Call Pi1LoopVZ_SM(0._dp,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,           & 
& MHp,MHp2,MVWp,MVWp2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,             & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,    & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiZZ)


Call Pi1LoopVZ_SM(MVZ2,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,             & 
& MHp,MHp2,MVWp,MVWp2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,             & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,    & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiZZ_mz2)

Call Pi1LoopVWp_SM(0._dp,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,               & 
& Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,        & 
& cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiWW)

Call Pi1LoopVWp_SM(MVWp2,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,Mhh2,            & 
& MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,             & 
& cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiWW_mw2)

Call Pi1LoopVPVZ_SM(MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,PiZg_mz2)

Call Pi1LoopVP_SM(MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,Pigg_mz2)


Iname = Iname -1 
End Subroutine OneLoop_Z_W_Gamma_SM


Subroutine OneLoop_d_u_e_SM(v,g1,g2,g3,Lam, Yu,Yd,Ye, SigR_d, SigL_d, SigSR_d, sigSL_d, &
& SigR_u, SigL_u, SigSR_u, SigSL_u, SigR_e, SigL_e, SigSR_e, SigSL_e, &
& kont)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3
Complex(dp),Intent(in) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3)
Complex(dp) :: Mu
Real(dp),Intent(inout) :: v
Complex(dp), Intent(out) :: SigL_d(3,3), SigR_d(3,3), SigSL_d(3,3), SigSR_d(3,3)
Complex(dp), Intent(out) :: SigL_u(3,3), SigR_u(3,3), SigSL_u(3,3), SigSR_u(3,3)
Complex(dp), Intent(out) :: SigL_e(3,3), SigR_e(3,3), SigSL_e(3,3), SigSR_e(3,3)

Real(dp) :: MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,MHp,MHp2,              & 
& MVWp,MVWp2,MVZ,MVZ2,TW,ZZ(2,2)

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)


Complex(dp) :: cplAhAhAhAh,cplAhAhcVWpVWp,cplAhAhhh,cplAhAhhhhh,cplAhAhHpcHp,cplAhAhVZVZ,            & 
& cplAhcHpVWp,cplAhhhVZ,cplAhHpcVWp,cplcFdFdAhL(3,3),cplcFdFdAhR(3,3),cplcFdFdhhL(3,3),  & 
& cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),  & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3),cplcFdFucHpR(3,3),cplcFdFucVWpL(3,3),& 
& cplcFdFucVWpR(3,3),cplcFeFeAhL(3,3),cplcFeFeAhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),& 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3), & 
& cplcFeFvcHpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFuAhL(3,3),              & 
& cplcFuFuAhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
& cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgGgGVG,cplcgWCgAcVWp,cplcgWCgWCAh,cplcgWCgWChh,     & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp,cplcgWCgZcVWp,cplcgWpgWpAh,cplcgWpgWphh,        & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWpgZHp,cplcgZgWCHp,cplcgZgWpcHp,cplcgZgWpcVWp,          & 
& cplcgZgZhh,cplcHpVPVWp,cplcHpVWpVZ,cplcUFdFdAhL(3,3),cplcUFdFdAhR(3,3),cplcUFdFdhhL(3,3),& 
& cplcUFdFdhhR(3,3),cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),               & 
& cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3),              & 
& cplcUFdFucHpR(3,3),cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3),cplcUFeFeAhL(3,3),          & 
& cplcUFeFeAhR(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),cplcUFeFeVPL(3,3),               & 
& cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),cplcUFeFvcHpL(3,3),              & 
& cplcUFeFvcHpR(3,3),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3),cplcUFuFdHpL(3,3),          & 
& cplcUFuFdHpR(3,3),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuAhL(3,3),             & 
& cplcUFuFuAhR(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),               & 
& cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),               & 
& cplcUFuFuVZR(3,3),cplcUFvFeHpL(3,3),cplcUFvFeHpR(3,3),cplcUFvFeVWpL(3,3),              & 
& cplcUFvFeVWpR(3,3),cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3),cplcVWpcVWpVWpVWp1,             & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3, & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhhh,cplhhhhhhhh,cplhhhhHpcHp,            & 
& cplhhhhVZVZ,cplhhHpcHp,cplhhHpcVWp,cplhhVZVZ,cplHpcHpcVWpVWp,cplHpcHpVP,               & 
& cplHpcHpVPVP,cplHpcHpVZ,cplHpcHpVZVZ,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp,            & 
& cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1, j2, j3, j4, il, i_count, ierr 
Integer :: i2L, iFin 
Logical :: Convergence2L 
Real(dp) :: Pi2S_EffPot_save(1,1), diff(1,1)
Complex(dp) :: Tad1Loop(1), dmz2  
Real(dp) :: comp(1), tanbQ, vev2, vSM, p2
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoop_Z_W_SM ' 
 
kont = 0 

! Running angles 

 
Call TreeMasses_SM(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,MHp2,MVWp,           & 
& MVWp2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,ZDL,ZEL,ZUL,ZW,ZZ,v,g1,g2,g3,Lam,Yu,Yd,Ye,               & 
& Mu,GenerationMixing,kont)

! If (UsePoleMass) Then
! MFu = mf_u
! MFu2 = mf_u2
! End if
! Full one-loop corrections
Call CouplingsForSMfermions_SM(Yd,ZDL,ZDR,g3,g1,g2,TW,Yu,ZUL,ZUR,Ye,ZEL,ZER,             & 
& cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,cplcUFdFdVGR,         & 
& cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,cplcUFdFucHpR,       & 
& cplcUFdFucVWpL,cplcUFdFucVWpR,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdHpL,cplcUFuFdHpR,     & 
& cplcUFuFdVWpL,cplcUFuFdVWpR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,       & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeAhL,cplcUFeFeAhR,         & 
& cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,         & 
& cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR)

p2=0._dp

Call Sigma1LoopFeMZ_SM(p2,MFe,MFe2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,             & 
& MVWp2,cplcUFeFeAhL,cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,   & 
& cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,   & 
& sigR_e,sigL_e,sigSR_e,sigSL_e)

Call Sigma1LoopFdMZ_SM(p2,MFd,MFd2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,              & 
& MFu2,MVWp,MVWp2,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,      & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigR_d,sigL_d,sigSR_d,sigSL_d)

Call Sigma1LoopFuMZ_SM(p2,MFu,MFu2,MAh,MAh2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,Mhh,            & 
& Mhh2,MVZ,MVZ2,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,       & 
& cplcUFuFdVWpR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,        & 
& cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigR_u,sigL_u,sigSR_u,sigSL_u)


! sigR_u=0.
! sigL_u=0.
! sigSR_u=0.
! sigSL_u=0.

! sigR_d=0.
! sigL_d=0.
! sigSR_d=0.
! sigSL_d=0.


Iname = Iname -1 
End Subroutine OneLoop_d_u_e_SM 

!  
Subroutine OneLoopTadpoleshh_SM(v,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,               & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplAhAhhh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,              & 
& cplhhhhhh,cplhhHpcHp,cplhhcVWpVWp,cplhhVZVZ,tadpoles)

Implicit None 
Real(dp), Intent(in) :: MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,MHp,MHp2,              & 
& MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplAhAhhh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),        & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplhhhhhh,      & 
& cplhhHpcHp,cplhhcVWpVWp,cplhhVZVZ

Real(dp), Intent(in) :: v

Integer :: i1,i2, gO1, gO2 
Complex(dp) :: coupL, coupR, coup, temp, res, A0m, sumI(1)  
Real(dp) :: m1 
Complex(dp), Intent(out) :: tadpoles(1) 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopTadpoleshh'
 
tadpoles = 0._dp 
 
!------------------------ 
! Ah 
!------------------------ 
! If (Include_in_loopAh) Then 
A0m = SA_A0(MAh2) 
  Do gO1 = 1, 1
   coup = cplAhAhhh
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
! End if 
!------------------------ 
! bar[Fd] 
!------------------------ 
! If (Include_in_loopFd) Then 
Do i1 = 1, 3
 A0m = 2._dp*MFd(i1)*SA_A0(MFd2(i1)) 
  Do gO1 = 1, 1
   coupL = cplcFdFdhhL(i1,i1)
   coupR = cplcFdFdhhR(i1,i1)
   sumI(gO1) = (coupL+coupR)*A0m 
  End Do 
 
tadpoles =  tadpoles + 3._dp*sumI 
End Do 
!  End if 
!------------------------ 
! bar[Fe] 
!------------------------ 
! If (Include_in_loopFe) Then 
Do i1 = 1, 3
 A0m = 2._dp*MFe(i1)*SA_A0(MFe2(i1)) 
  Do gO1 = 1, 1
   coupL = cplcFeFehhL(i1,i1)
   coupR = cplcFeFehhR(i1,i1)
   sumI(gO1) = (coupL+coupR)*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
End Do 
!  End if 
!------------------------ 
! bar[Fu] 
!------------------------ 
! If (Include_in_loopFu) Then 
Do i1 = 1, 3
 A0m = 2._dp*MFu(i1)*SA_A0(MFu2(i1)) 
  Do gO1 = 1, 1
   coupL = cplcFuFuhhL(i1,i1)
   coupR = cplcFuFuhhR(i1,i1)
   sumI(gO1) = (coupL+coupR)*A0m 
  End Do 
 
tadpoles =  tadpoles + 3._dp*sumI 
End Do 
!  End if 
!------------------------ 
! bar[gWp] 
!------------------------ 
! If (Include_in_loopgWp) Then 
A0m = 1._dp*SA_A0(MVWp2) 
  Do gO1 = 1, 1
    coup = cplcgWpgWphh
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
! End if 
!------------------------ 
! bar[gWpC] 
!------------------------ 
! If (Include_in_loopgWC) Then 
A0m = 1._dp*SA_A0(MVWp2) 
  Do gO1 = 1, 1
    coup = cplcgWCgWChh
    sumI(gO1) = coup*A0m 
  End Do 
!  
tadpoles =  tadpoles + 1._dp*sumI 
! End if 
!------------------------ 
! bar[gZ] 
!------------------------ 
! If (Include_in_loopgZ) Then 
A0m = 1._dp*SA_A0(MVZ2) 
  Do gO1 = 1, 1
    coup = cplcgZgZhh
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
! End if 
!------------------------ 
! hh 
!------------------------ 
! If (Include_in_loophh) Then 
A0m = SA_A0(Mhh2) 
  Do gO1 = 1, 1
   coup = cplhhhhhh
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
! End if 
!------------------------ 
! conj[Hp] 
!------------------------ 
! If (Include_in_loopHp) Then 
A0m = SA_A0(MHp2) 
  Do gO1 = 1, 1
   coup = cplhhHpcHp
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
! End if 
!------------------------ 
! conj[VWp] 
!------------------------ 
! If (Include_in_loopVWp) Then 
A0m = 3._dp*SA_A0(MVWp2)+RXi*SA_A0(MVWp2) - 2._dp*MVWp2*1._dp 
  Do gO1 = 1, 1
    coup = cplhhcVWpVWp
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
! End if 
!------------------------ 
! VZ 
!------------------------ 
! If (Include_in_loopVZ) Then 
A0m = 3._dp*SA_A0(MVZ2)+RXi*SA_A0(MVZ2) - 2._dp*MVZ2*1._dp 
  Do gO1 = 1, 1
    coup = cplhhVZVZ
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
! End if 



tadpoles = oo16pi2*tadpoles 
Iname = Iname - 1 
End Subroutine OneLoopTadpoleshh_SM
!  
Subroutine OneLoophh_SM(Mu,Lam,v,MAh,MAh2,MVZ,MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,             & 
& cplcgZgZhh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,        & 
& cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,delta,mass,mass2,tad,kont)

Real(dp), Intent(in) :: MAh,MAh2,MVZ,MVZ2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MHp,MHp2,MVWp,MVWp2

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: Mu,Lam, tad

Complex(dp), Intent(in) :: cplAhAhhh,cplAhhhVZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcgWpgWphh,cplcgWCgWChh,          & 
& cplcgZgZhh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,        & 
& cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoophh'
 
mi2 = -1._dp*(Mu) + (3*v**2*Lam)/2._dp 

Write(*,*) sqrt(getrenormalizationscale())



 
p2 = Mhh2
PiSf = ZeroC 


Call Pi1Loophh_SM(p2,MAh,MAh2,MVZ,MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MHp,MHp2,MVWp,MVWp2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,              & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,cplhhhhhhhh,       & 
& cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,kont,PiSf)

mass2 = mi2 - Real(PiSf,dp) + Pi2S_EffPot_SM(1,1)
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1Loophh_SM(p2,MAh,MAh2,MVZ,MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MHp,MHp2,MVWp,MVWp2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,              & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,cplhhhhhhhh,       & 
& cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,kont,PiSf)

mass2 = mi2 - Real(PiSf,dp) + Pi2S_EffPot_SM(1,1)


mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
!    If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
!    End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
!    SignOfMassChanged = .True. 
   mass = 0._dp 
  End If 
If (test_m2.LT.0.1_dp*delta) Exit 
If (i_count.Gt.30) Then 
  Write(*,*) "Problem in "//NameOfUnit(Iname), test_m2, mass2 
  kont = -510 
  Call AddError(510) 
 Exit 
End If 
End Do 
 
 
Iname = Iname -1 
End Subroutine OneLoophh_SM
 
 
Subroutine Pi1Loophh_SM(p2,MAh,MAh2,MVZ,MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,             & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,      & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,              & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,cplhhhhhhhh,       & 
& cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MAh,MAh2,MVZ,MVZ2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MHp,MHp2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplAhAhhh,cplAhhhVZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcgWpgWphh,cplcgWCgWChh,          & 
& cplcgZgZhh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplAhAhhhhh,        & 
& cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
res = 0._dp 
 
 
!------------------------ 
! Ah, Ah 
!------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopAh).and.(Include_in_loopAh)) Then 
B0m2 = SA_B0(p2,MAh2,MAh2) 
coup1 = cplAhAhhh
coup2 = Conjg(cplAhAhhh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
! End If 
!------------------------ 
! VZ, Ah 
!------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopVZ).and.(Include_in_loopAh)) Then 
F0m2 = FloopRXi(p2,MAh2,MVZ2) 
coup1 = cplAhhhVZ
coup2 =  Conjg(cplAhhhVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
! End If 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopFd).and.(Include_in_loopFd)) Then 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_Gloop(p2,MFd2(i1),MFd2(i2)) 
B0m2 = -2._dp*MFd(i1)*MFd(i2)*SA_B0(p2,MFd2(i1),MFd2(i2)) 
coupL1 = cplcFdFdhhL(i1,i2)
coupR1 = cplcFdFdhhR(i1,i2)
coupL2 =  Conjg(cplcFdFdhhL(i1,i2))
coupR2 =  Conjg(cplcFdFdhhR(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 ! End If 
!------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopFe).and.(Include_in_loopFe)) Then 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_Gloop(p2,MFe2(i1),MFe2(i2)) 
B0m2 = -2._dp*MFe(i1)*MFe(i2)*SA_B0(p2,MFe2(i1),MFe2(i2)) 
coupL1 = cplcFeFehhL(i1,i2)
coupR1 = cplcFeFehhR(i1,i2)
coupL2 =  Conjg(cplcFeFehhL(i1,i2))
coupR2 =  Conjg(cplcFeFehhR(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 ! End If 
 
!------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopFu).and.(Include_in_loopFu)) Then 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_Gloop(p2,MFu2(i1),MFu2(i2)) 
B0m2 = -2._dp*MFu(i1)*MFu(i2)*SA_B0(p2,MFu2(i1),MFu2(i2)) 
coupL1 = cplcFuFuhhL(i1,i2)
coupR1 = cplcFuFuhhR(i1,i2)
coupL2 =  Conjg(cplcFuFuhhL(i1,i2))
coupR2 =  Conjg(cplcFuFuhhR(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 ! End ! If 
! !------------------------ 
! ! bar[gWp], gWp 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopgWp).and.(Include_in_loopgWp)) Then 
F0m2 =  -Real(SA_B0(p2,MVWp2,MVWp2),dp) 
 coup1 = cplcgWpgWphh
coup2 =  cplcgWpgWphh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! bar[gWpC], gWpC 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopgWC).and.(Include_in_loopgWC)) Then 
F0m2 =  -Real(SA_B0(p2,MVWp2,MVWp2),dp) 
 coup1 = cplcgWCgWChh
coup2 =  cplcgWCgWChh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! bar[gZ], gZ 
! !------------------------ 
! sumI = 0._dp 
!  
! ! If ((Include_in_loopgZ).and.(Include_in_loopgZ)) Then 
F0m2 =  -Real(SA_B0(p2,MVZ2,MVZ2),dp) 
 coup1 = cplcgZgZhh
coup2 =  cplcgZgZhh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! hh, hh 
! !------------------------ 
! sumI = 0._dp 
!  
! ! If ((Include_in_loophh).and.(Include_in_loophh)) Then 
B0m2 = SA_B0(p2,Mhh2,Mhh2) 
coup1 = cplhhhhhh
coup2 = Conjg(cplhhhhhh)
    SumI = coup1*coup2*B0m2 

res = res +1._dp/2._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! conj[Hp], Hp 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopHp).and.(Include_in_loopHp)) Then 
B0m2 = SA_B0(p2,MHp2,MHp2) 
coup1 = cplhhHpcHp
coup2 = Conjg(cplhhHpcHp)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! conj[VWp], Hp 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopVWp).and.(Include_in_loopHp)) Then 
F0m2 = FloopRXi(p2,MHp2,MVWp2) 
coup1 = cplhhHpcVWp
coup2 =  Conjg(cplhhHpcVWp)
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! conj[VWp], VWp 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopVWp).and.(Include_in_loopVWp)) Then 
F0m2 = SVVloop(p2,MVWp2,MVWp2) 
coup1 = cplhhcVWpVWp
coup2 =  Conjg(cplhhcVWpVWp)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! VZ, VZ 
! !------------------------ 
! sumI = 0._dp 
!  
! ! If ((Include_in_loopVZ).and.(Include_in_loopVZ)) Then 
F0m2 = SVVloop(p2,MVZ2,MVZ2) 
coup1 = cplhhVZVZ
coup2 =  Conjg(cplhhVZVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp/2._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! Ah, Ah 
! !------------------------ 
! sumI = 0._dp 
!  
! ! If ((Include_in_loopAh).and.(Include_in_loopAh)) Then 
A0m2 = SA_A0(MAh2) 
coup1 = cplAhAhhhhh
    SumI = -coup1*A0m2 
res = res + 1._dp/2._dp* SumI   
! ! End ! If 
! !------------------------ 
! ! hh, hh 
! !------------------------ 
! sumI = 0._dp 
!  
! ! If ((Include_in_loophh).and.(Include_in_loophh)) Then 
A0m2 = SA_A0(Mhh2) 
coup1 = cplhhhhhhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! conj[Hp], Hp 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopHp).and.(Include_in_loopHp)) Then 
A0m2 = SA_A0(MHp2) 
coup1 = cplhhhhHpcHp
    SumI = -coup1*A0m2 
res = res +1._dp* SumI 
! ! End ! If 
! !------------------------ 
! ! conj[VWp], VWp 
! !------------------------ 
sumI = 0._dp 
 
! If ((Include_in_loopVWp).and.(Include_in_loopVWp)) Then 
A0m2 =  0.75_dp*SA_A0(MVWp2) + 0.25_dp*SA_A0(MVWp2) - 0.5_dp*MVWp2
coup1 = cplhhhhcVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
! ! End ! If 
! !------------------------ 
! ! VZ, VZ 
! !------------------------ 
! sumI = 0._dp 
!  
! ! If ((Include_in_loopVZ).and.(Include_in_loopVZ)) Then 
A0m2 =  0.75_dp*SA_A0(MVZ2) + 0.25_dp*SA_A0(MVZ2) - 0.5_dp*MVZ2
coup1 = cplhhhhVZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  
! ! End ! If 

res = oo16pi2*res 
 
End Subroutine Pi1Loophh_SM 
!  



Subroutine Pi1LoopVP_SM(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,            & 
& cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MHp,MHp2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3), & 
& cplcFuFuVPR(3,3),cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,        & 
& cplHpcHpVPVP,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3

H0m2 = Real(SA_Hloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_B0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVPL(i1,i2)
coupR1 = cplcFdFdVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
H0m2 = Real(SA_Hloop(p2,MFe2(i1),MFe2(i2)),dp) 
B0m2 = 4._dp*MFe(i1)*MFe(i2)*Real(SA_B0(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVPL(i1,i2)
coupR1 = cplcFeFeVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
!------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
H0m2 = Real(SA_Hloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*Real(SA_B0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVPL(i1,i2)
coupR1 = cplcFuFuVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVP
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVP
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
B22m2 = Real(VSSloop(p2,MHp2,MHp2),dp)  
coup1 = cplHpcHpVP
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(VVSloop(p2,MVWp2,MHp2),dp)
coup1 = cplHpcVWpVP
    SumI = Abs(coup1)**2*B0m2 
res = res +2._dp* SumI  
!------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVPVWp
coup2 = Conjg(coup1) 
    SumI = -VVVloop(p2,MVWp2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MHp2)
 coup1 = cplHpcHpVPVP
 SumI = coup1*A0m2 
res = res +1* SumI  
!------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2*RXi) 
coup1 = cplcVWpVPVPVWp3
coup2 = cplcVWpVPVPVWp1
coup3 = cplcVWpVPVPVWp2
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVP_SM
!  

Subroutine Pi1LoopVPVZ_SM(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,           & 
& cplcVWpVPVWp,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,             & 
& cplHpcHpVP,cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MHp,MHp2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3), & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,              & 
& cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,     & 
& cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,           & 
& cplHpcVWpVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_B0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVPL(i1,i2)
coupR1 = cplcFdFdVPR(i1,i2)
coupL2 = cplcFdFdVZL(i2,i1)
coupR2 = cplcFdFdVZR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*H0m2 & 
                & + 0.5_dp*(coupL1*coupR2 + coupL2*coupR1)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!------------------------ 
! bar[Fe], Fe 
!------------------------ 
! If ((Include_in_loopFe).and.(Include_in_loopFe)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,MFe2(i1),MFe2(i2)),dp) 
B0m2 = 4._dp*MFe(i1)*MFe(i2)*Real(SA_B0(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVPL(i1,i2)
coupR1 = cplcFeFeVPR(i1,i2)
coupL2 = cplcFeFeVZL(i2,i1)
coupR2 = cplcFeFeVZR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*H0m2 & 
                & + 0.5_dp*(coupL1*coupR2 + coupL2*coupR1)*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[Fu], Fu 
!------------------------ 
! If ((Include_in_loopFu).and.(Include_in_loopFu)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*Real(SA_B0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVPL(i1,i2)
coupR1 = cplcFuFuVPR(i1,i2)
coupL2 = cplcFuFuVZL(i2,i1)
coupR2 = cplcFuFuVZR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*H0m2 & 
                & + 0.5_dp*(coupL1*coupR2 + coupL2*coupR1)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
! If ((Include_in_loopgWp).and.(Include_in_loopgWp)) Then 
sumI = 0._dp 
 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVP
coup2 = cplcgWpgWpVZ 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
! If ((Include_in_loopgWC).and.(Include_in_loopgWC)) Then 
sumI = 0._dp 
 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVP
coup2 = cplcgWCgWCVZ 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopHp)) Then 
sumI = 0._dp 
 
B22m2 = Real(VSSloop(p2,MHp2,MHp2),dp) 
coup1 = cplHpcHpVP
coup2 = cplHpcHpVZ
    SumI = coup1*coup2*B22m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopHp)) Then 
sumI = 0._dp 
 
B0m2 = Real(VVSloop(p2,MVWp2,MHp2),dp) 
coup1 = cplHpcVWpVP
coup2 = cplcHpVWpVZ
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[Hp], VWp 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopVWp)) Then 
sumI = 0._dp 
 
B0m2 = Real(VVSloop(p2,MVWp2,MHp2),dp) 
coup1 = cplcHpVPVWp
coup2 = cplHpcVWpVZ
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[VWp], VWp 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopVWp)) Then 
sumI = 0._dp 
 
B0m2 = Real(VVVloop(p2,MVWp2,MVWp2),dp) 
coup1 = cplcVWpVPVWp
coup2 = cplcVWpVWpVZ
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[Hp] 
!------------------------ 
! If (Include_in_loopHp) Then 
SumI = 0._dp 
 A0m2 = SA_A0(MHp2)
 coup1 = cplHpcHpVPVZ
 SumI = coup1*A0m2 
res = res +1* SumI  
! End if 
!------------------------ 
! conj[VWp] 
!------------------------ 
! If (Include_in_loopVWp) Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2*RXi) 
coup1 = cplcVWpVPVWpVZ2
coup2 = cplcVWpVPVWpVZ1
coup3 = cplcVWpVPVWpVZ3
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
! End if 
res = oo16pi2*res 
 
End Subroutine Pi1LoopVPVZ_SM
 
Subroutine Pi1LoopVZ_SM(p2,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,             & 
& MVZ2,MHp,MHp2,MVWp,MVWp2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,    & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,             & 
& cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,    & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,res)

Implicit None 
Real(dp), Intent(in) :: Mhh,Mhh2,MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MVZ,MVZ2,              & 
& MHp,MHp2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplAhhhVZ,cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),        & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgWpgWpVZ,      & 
& cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplAhAhVZVZ,cplhhhhVZVZ,    & 
& cplHpcHpVZVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! hh, Ah 
!------------------------ 
! If ((Include_in_loophh).and.(Include_in_loopAh)) Then 
sumI = 0._dp 
 
B22m2 = VSSloop(p2,MAh2,Mhh2)  
coup1 = cplAhhhVZ
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
! If ((Include_in_loopFd).and.(Include_in_loopFd)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = SA_Hloop(p2,MFd2(i1),MFd2(i2)) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*SA_B0(p2,MFd2(i1),MFd2(i2)) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[Fe], Fe 
!------------------------ 
! If ((Include_in_loopFe).and.(Include_in_loopFe)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = SA_Hloop(p2,MFe2(i1),MFe2(i2)) 
B0m2 = 4._dp*MFe(i1)*MFe(i2)*SA_B0(p2,MFe2(i1),MFe2(i2)) 
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[Fu], Fu 
!------------------------ 
! If ((Include_in_loopFu).and.(Include_in_loopFu)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = SA_Hloop(p2,MFu2(i1),MFu2(i2)) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*SA_B0(p2,MFu2(i1),MFu2(i2)) 
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[Fv], Fv 
!------------------------ 
! If ((Include_in_loopFv).and.(Include_in_loopFv)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = SA_Hloop(p2,0._dp,0._dp) 
B0m2 = 4._dp*0.*0.*SA_B0(p2,0._dp,0._dp) 
coupL1 = cplcFvFvVZL(i1,i2)
coupR1 = cplcFvFvVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
! If ((Include_in_loopgWp).and.(Include_in_loopgWp)) Then 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = VGGloop(p2,MVWp2,MVWp2)
coup1 = cplcgWpgWpVZ
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
! If ((Include_in_loopgWC).and.(Include_in_loopgWC)) Then 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = VGGloop(p2,MVWp2,MVWp2)
coup1 = cplcgWCgWCVZ
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! VZ, hh 
!------------------------ 
! If ((Include_in_loopVZ).and.(Include_in_loophh)) Then 
sumI = 0._dp 
 
B0m2 = VVSloop(p2,MVZ2,Mhh2) 
coup1 = cplhhVZVZ
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopHp)) Then 
sumI = 0._dp 
 
B22m2 = VSSloop(p2,MHp2,MHp2)  
coup1 = cplHpcHpVZ
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopHp)) Then 
sumI = 0._dp 
 
B0m2 = VVSloop(p2,MVWp2,MHp2) 
coup1 = cplHpcVWpVZ
    SumI = Abs(coup1)**2*B0m2 
res = res +2._dp* SumI  
! End if 
!------------------------ 
! conj[VWp], VWp 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopVWp)) Then 
sumI = 0._dp 
 
coup1 = cplcVWpVWpVZ
coup2 = Conjg(coup1) 
    SumI = -VVVloopSM(p2,MVWp2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! Ah 
!------------------------ 
! If (Include_in_loopAh) Then 
SumI = 0._dp 
 A0m2 = SA_A0(MAh2)
 coup1 = cplAhAhVZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
! End if 
!------------------------ 
! hh 
!------------------------ 
! If (Include_in_loophh) Then 
SumI = 0._dp 
 A0m2 = SA_A0(Mhh2)
 coup1 = cplhhhhVZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
! End if 
!------------------------ 
! conj[Hp] 
!------------------------ 
! If (Include_in_loopHp) Then 
SumI = 0._dp 
 A0m2 = SA_A0(MHp2)
 coup1 = cplHpcHpVZVZ
 SumI = coup1*A0m2 
res = res +1* SumI  
! End if 
!------------------------ 
! conj[VWp] 
!------------------------ 
! If (Include_in_loopVWp) Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2) 
coup1 = cplcVWpVWpVZVZ1
coup2 = cplcVWpVWpVZVZ2
coup3 = cplcVWpVWpVZVZ3
SumI = ((2._dp*rMS_SM*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
! End if 
res = oo16pi2*res 
 
End Subroutine Pi1LoopVZ_SM

 
! Subroutine OneLoopVWp(g2,v,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,              & 
! & Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,    & 
! & cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
! & cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
! & cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
! & cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
! & cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,delta,mass,mass2,kont)
! 
! Real(dp), Intent(in) :: MHp,MHp2,MAh,MAh2,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),MFe2(3),Mhh,Mhh2,              & 
! & MVWp,MVWp2,MVZ,MVZ2
! 
! Real(dp), Intent(in) :: g2,v
! 
! Complex(dp), Intent(in) :: cplAhHpcVWp,cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),& 
! & cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,cplhhcVWpVWp,      & 
! & cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,cplhhhhcVWpVWp,       & 
! & cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
! & cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3
! 
! Integer , Intent(inout):: kont 
! Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
! Real(dp), Intent(in) :: delta 
! Real(dp) :: mi, mi2, p2, test_m2 
! Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
! Real(dp), Intent(out) :: mass, mass2 
! Iname = Iname + 1 
! NameOfUnit(Iname) = 'OneLoopVWp'
!  
! mi2 = MVWp2 
! 
!  
! p2 = MVWp2
! PiSf = ZeroC 
! Call Pi1LoopVWp(p2,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,Mhh2,             & 
! & MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,             & 
! & cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
! & cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
! & cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
! & cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
! & cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiSf)
! 
! mass2 = mi2 + Real(PiSf,dp) 
! mass = sqrt(mass2) 
! i_count = 0 
! Do  
! i_count = i_count + 1 
! test_m2 = mass2 
! p2 =  mass2 
! PiSf = ZeroC 
! Call Pi1LoopVWp(p2,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,Mhh2,             & 
! & MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,             & 
! & cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
! & cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
! & cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
! & cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
! & cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiSf)
! 
! mass2 = mi2 + Real(PiSf,dp) 
! mass = sqrt(mass2) 
!  If (test_m2.Ne.0._dp) Then 
!     test_m2 = Abs(test_m2 - mass2) / test_m2 
!  Else 
!     test_m2 = Abs(mass2) 
!  End If 
!  If (mass2.Ge.0._dp) Then 
!    If (RotateNegativeFermionMasses) Then 
!     mass = sqrt(mass2) 
!    End if 
!   Else 
!  If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
!      Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
!      Write(ErrCan,*) 'in the calculation of the masses' 
!      Write(ErrCan,*) 'occurred a negative mass squared!' 
!    SignOfMassChanged = .True. 
!    mass = 0._dp 
!   End If 
! If (test_m2.LT.0.1_dp*delta) Exit 
! If (i_count.Gt.30) Then 
!   Write(*,*) "Problem in "//NameOfUnit(Iname), test_m2, mass2 
!   kont = -510 
!   Call AddError(510) 
!  Exit 
! End If 
! End Do 
!  
!  
! Iname = Iname -1 
! End Subroutine OneLoopVWp
 
 
Subroutine Pi1LoopVWp_SM(p2,MHp,MHp2,MAh,MAh2,MFd,MFd2,MFu,MFu2,MFe,MFe2,Mhh,            & 
& Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplAhHpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,        & 
& cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,     & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,         & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp,MHp2,MAh,MAh2,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),MFe2(3),Mhh,Mhh2,              & 
& MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplAhHpcVWp,cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),& 
& cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplhhHpcVWp,cplhhcVWpVWp,      & 
& cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplAhAhcVWpVWp,cplhhhhcVWpVWp,       & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! Hp, Ah 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopAh)) Then 
sumI = 0._dp 
 
B22m2 = VSSloop(p2,MAh2,MHp2)  
coup1 = cplAhHpcVWp
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[Fd], Fu 
!------------------------ 
! If ((Include_in_loopFd).and.(Include_in_loopFu)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = SA_Hloop(p2,MFd2(i1),MFu2(i2)) 
B0m2 = 4._dp*MFd(i1)*MFu(i2)*SA_B0(p2,MFd2(i1),MFu2(i2)) 
coupL1 = cplcFdFucVWpL(i1,i2)
coupR1 = cplcFdFucVWpR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[Fe], Fv 
!------------------------ 
! If ((Include_in_loopFe).and.(Include_in_loopFv)) Then 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = SA_Hloop(p2,MFe2(i1),0._dp) 
B0m2 = 4._dp*MFe(i1)*0.*SA_B0(p2,MFe2(i1),0._dp) 
coupL1 = cplcFeFvcVWpL(i1,i2)
coupR1 = cplcFeFvcVWpR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
!  End if 
!------------------------ 
! bar[gWpC], gP 
!------------------------ 
! If ((Include_in_loopgWC).and.(Include_in_loopgA)) Then 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = VGGloop(p2,0._dp,MVWp2)
coup1 = cplcgWCgAcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[gP], gWp 
!------------------------ 
! If ((Include_in_loopgA).and.(Include_in_loopgWp)) Then 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = VGGloop(p2,MVWp2,0._dp)
coup1 = cplcgAgWpcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[gZ], gWp 
!------------------------ 
! If ((Include_in_loopgZ).and.(Include_in_loopgWp)) Then 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = VGGloop(p2,MVWp2,MVZ2)
coup1 = cplcgZgWpcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! bar[gWpC], gZ 
!------------------------ 
! If ((Include_in_loopgWC).and.(Include_in_loopgZ)) Then 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = VGGloop(p2,MVZ2,MVWp2)
coup1 = cplcgWCgZcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! Hp, hh 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loophh)) Then 
sumI = 0._dp 
 
B22m2 = VSSloop(p2,Mhh2,MHp2)  
coup1 = cplhhHpcVWp
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! VWp, hh 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loophh)) Then 
sumI = 0._dp 
 
B0m2 = VVSloop(p2,MVWp2,Mhh2) 
coup1 = cplhhcVWpVWp
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! VP, Hp 
!------------------------ 
! If ((Include_in_loopVP).and.(Include_in_loopHp)) Then 
sumI = 0._dp 
 
B0m2 = VVSloop(p2,0._dp,MHp2) 
coup1 = cplHpcVWpVP
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! VZ, Hp 
!------------------------ 
! If ((Include_in_loopVZ).and.(Include_in_loopHp)) Then 
sumI = 0._dp 
 
B0m2 = VVSloop(p2,MVZ2,MHp2) 
coup1 = cplHpcVWpVZ
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! VWp, VP 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopVP)) Then 
sumI = 0._dp 
 
coup1 = cplcVWpVPVWp
coup2 = Conjg(coup1) 
    SumI = -VVVloopSM(p2,MVWp2,0._dp)*coup1*coup2 
res = res +1._dp* SumI  
! End if 
! !------------------------ 
! VZ, VWp 
!------------------------ 
! If ((Include_in_loopVZ).and.(Include_in_loopVWp)) Then 
sumI = 0._dp 
 
coup1 = cplcVWpVWpVZ
coup2 = Conjg(coup1) 
    SumI = -VVVloopSM(p2,MVZ2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
! End if 
!------------------------ 
! Ah 
!------------------------ 
! If (Include_in_loopAh) Then 
SumI = 0._dp 
 A0m2 = SA_A0(MAh2)
 coup1 = cplAhAhcVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
! End if 
!------------------------ 
! hh 
!------------------------ 
! If (Include_in_loophh) Then 
SumI = 0._dp 
 A0m2 = SA_A0(Mhh2)
 coup1 = cplhhhhcVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
! End if 
!------------------------ 
! conj[Hp] 
!------------------------ 
! If (Include_in_loopHp) Then 
SumI = 0._dp 
 A0m2 = SA_A0(MHp2)
 coup1 = cplHpcHpcVWpVWp
 SumI = coup1*A0m2 
res = res +1* SumI  
! End if 
!------------------------ 
! VP 
!------------------------ 
! If (Include_in_loopVP) Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(0._dp) +RXi/4._dp*SA_A0(0._dp) 
coup1 = cplcVWpVPVPVWp3
coup2 = cplcVWpVPVPVWp1
coup3 = cplcVWpVPVPVWp2
SumI = ((2._dp*1._dp*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*0._dp-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
! End if 
!------------------------ 
! conj[VWp] 
!------------------------ 
! If (Include_in_loopVWp) Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2) 
coup1 = cplcVWpcVWpVWpVWp2
coup2 = cplcVWpcVWpVWpVWp3
coup3 = cplcVWpcVWpVWpVWp1
SumI = ((2._dp*rMS_SM*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
! End if 
!------------------------ 
! VZ 
!------------------------ 
! If (Include_in_loopVZ) Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVZ2) +RXi/4._dp*SA_A0(MVZ2) 
coup1 = cplcVWpVWpVZVZ1
coup2 = cplcVWpVWpVZVZ2
coup3 = cplcVWpVWpVZVZ3
SumI = ((2._dp*rMS_SM*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVZ2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
! End if 
res = oo16pi2*res 
 
End Subroutine Pi1LoopVWp_SM 
 
Subroutine Sigma1LoopFeMZ_SM(p2,MFe,MFe2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,            & 
& MVWp,MVWp2,cplcUFeFeAhL,cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,           & 
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,     & 
& cplcUFeFvcVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MFe(3),MFe2(3),MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFeFeAhL(3,3),cplcUFeFeAhR(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),              & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvcHpL(3,3),cplcUFeFvcHpR(3,3),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! Fe, Ah 
!------------------------ 
! If ((Include_in_loopFe).and.(Include_in_loopAh)) Then 
    Do i1 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFe2(gO1),MFe2(i1),MAh2),dp) 
B0m2 = MFe(i1)*Real(SA_B0(MFe2(gO1),MFe2(i1),MAh2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFe2(i1),MAh2),dp) 
B0m2 = MFe(i1)*Real(SA_B0(p2,MFe2(i1),MAh2),dp) 
End If 
coupL1 = cplcUFeFeAhL(gO1,i1)
coupR1 = cplcUFeFeAhR(gO1,i1)
coupL2 =  Conjg(cplcUFeFeAhL(gO2,i1))
coupR2 =  Conjg(cplcUFeFeAhR(gO2,i1))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
!  End if 
!------------------------ 
! hh, Fe 
!------------------------ 
! If ((Include_in_loophh).and.(Include_in_loopFe)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFe2(gO1),MFe2(i2),Mhh2),dp) 
B0m2 = MFe(i2)*Real(SA_B0(MFe2(gO1),MFe2(i2),Mhh2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFe2(i2),Mhh2),dp) 
B0m2 = MFe(i2)*Real(SA_B0(p2,MFe2(i2),Mhh2),dp) 
End If 
coupL1 = cplcUFeFehhL(gO1,i2)
coupR1 = cplcUFeFehhR(gO1,i2)
coupL2 =  Conjg(cplcUFeFehhL(gO2,i2))
coupR2 =  Conjg(cplcUFeFehhR(gO2,i2))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! VZ, Fe 
!------------------------ 
! If ((Include_in_loopVZ).and.(Include_in_loopFe)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = - Real(SA_B1(MFe2(gO1),MFe2(i2),MVZ2),dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(MFe2(gO1),MFe2(i2),MVZ2)-0.5_dp*rMS_SM,dp) 
Else 
B1m2 = - Real(SA_B1(p2,MFe2(i2),MVZ2)+ 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(p2,MFe2(i2),MVZ2)-0.5_dp*rMS_SM,dp) 
End If 
coupL1 = cplcUFeFeVZL(gO1,i2)
coupR1 = cplcUFeFeVZR(gO1,i2)
coupL2 =  Conjg(cplcUFeFeVZL(gO2,i2))
coupR2 =  Conjg(cplcUFeFeVZR(gO2,i2))
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! conj[Hp], Fv 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopFv)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFe2(gO1),0._dp,MHp2),dp) 
B0m2 = 0.*Real(SA_B0(MFe2(gO1),0._dp,MHp2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,0._dp,MHp2),dp) 
B0m2 = 0.*Real(SA_B0(p2,0._dp,MHp2),dp) 
End If 
coupL1 = cplcUFeFvcHpL(gO1,i2)
coupR1 = cplcUFeFvcHpR(gO1,i2)
coupL2 =  Conjg(cplcUFeFvcHpL(gO2,i2))
coupR2 =  Conjg(cplcUFeFvcHpR(gO2,i2))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! conj[VWp], Fv 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopFv)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = - Real(SA_B1(MFe2(gO1),0._dp,MVWp2),dp) 
B0m2 = -4._dp*0.*Real(SA_B0(MFe2(gO1),0._dp,MVWp2)-0.5_dp*rMS_SM,dp) 
Else 
B1m2 = - Real(SA_B1(p2,0._dp,MVWp2)+ 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*0.*Real(SA_B0(p2,0._dp,MVWp2)-0.5_dp*rMS_SM,dp) 
End If 
coupL1 = cplcUFeFvcVWpL(gO1,i2)
coupR1 = cplcUFeFvcVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFeFvcVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFeFvcVWpR(gO2,i2))
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFeMZ_SM 
 
Subroutine Sigma1LoopFdMZ_SM(p2,MFd,MFd2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,            & 
& MFu,MFu2,MVWp,MVWp2,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,               & 
& cplcUFdFdVGL,cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,         & 
& cplcUFdFucHpL,cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu(3),MFu2(3),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFdFdAhL(3,3),cplcUFdFdAhR(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),              & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3),cplcUFdFucHpR(3,3),             & 
& cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! Fd, Ah 
!------------------------ 
! If ((Include_in_loopFd).and.(Include_in_loopAh)) Then 
    Do i1 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFd2(gO1),MFd2(i1),MAh2),dp) 
B0m2 = MFd(i1)*Real(SA_B0(MFd2(gO1),MFd2(i1),MAh2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFd2(i1),MAh2),dp) 
B0m2 = MFd(i1)*Real(SA_B0(p2,MFd2(i1),MAh2),dp) 
End If 
coupL1 = cplcUFdFdAhL(gO1,i1)
coupR1 = cplcUFdFdAhR(gO1,i1)
coupL2 =  Conjg(cplcUFdFdAhL(gO2,i1))
coupR2 =  Conjg(cplcUFdFdAhR(gO2,i1))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
!  End if 
!------------------------ 
! hh, Fd 
!------------------------ 
! If ((Include_in_loophh).and.(Include_in_loopFd)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFd2(gO1),MFd2(i2),Mhh2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(MFd2(gO1),MFd2(i2),Mhh2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFd2(i2),Mhh2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),Mhh2),dp) 
End If 
coupL1 = cplcUFdFdhhL(gO1,i2)
coupR1 = cplcUFdFdhhR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdhhL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdhhR(gO2,i2))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! VZ, Fd 
!------------------------ 
! If ((Include_in_loopVZ).and.(Include_in_loopFd)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = - Real(SA_B1(MFd2(gO1),MFd2(i2),MVZ2),dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(MFd2(gO1),MFd2(i2),MVZ2)-0.5_dp*rMS_SM,dp) 
Else 
B1m2 = - Real(SA_B1(p2,MFd2(i2),MVZ2)+ 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),MVZ2)-0.5_dp*rMS_SM,dp) 
End If 
coupL1 = cplcUFdFdVZL(gO1,i2)
coupR1 = cplcUFdFdVZR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVZL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVZR(gO2,i2))
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! conj[Hp], Fu 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopFu)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFd2(gO1),MFu2(i2),MHp2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(MFd2(gO1),MFu2(i2),MHp2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFu2(i2),MHp2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),MHp2),dp) 
End If 
coupL1 = cplcUFdFucHpL(gO1,i2)
coupR1 = cplcUFdFucHpR(gO1,i2)
coupL2 =  Conjg(cplcUFdFucHpL(gO2,i2))
coupR2 =  Conjg(cplcUFdFucHpR(gO2,i2))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! conj[VWp], Fu 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopFu)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = - Real(SA_B1(MFd2(gO1),MFu2(i2),MVWp2)  + 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(MFd2(gO1),MFu2(i2),MVWp2)-0.5_dp*rMS_SM,dp) 
Else 
B1m2 = - Real(SA_B1(p2,MFu2(i2),MVWp2)+ 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),MVWp2)-0.5_dp*rMS_SM,dp) 
End If 
coupL1 = cplcUFdFucVWpL(gO1,i2)
coupR1 = cplcUFdFucVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFdFucVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFdFucVWpR(gO2,i2))
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFdMZ_SM
 
Subroutine Sigma1LoopFuMZ_SM(p2,MFu,MFu2,MAh,MAh2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,          & 
& Mhh,Mhh2,MVZ,MVZ2,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,   & 
& cplcUFuFdVWpR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,        & 
& cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MFu(3),MFu2(3),MAh,MAh2,MHp,MHp2,MFd(3),MFd2(3),MVWp,MVWp2,Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcUFuFuAhL(3,3),cplcUFuFuAhR(3,3),cplcUFuFdHpL(3,3),cplcUFuFdHpR(3,3),              & 
& cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),             & 
& cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),               & 
& cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! Fu, Ah 
!------------------------ 
! If ((Include_in_loopFu).and.(Include_in_loopAh)) Then 
    Do i1 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFu2(gO1),MFu2(i1),MAh2),dp) 
B0m2 = MFu(i1)*Real(SA_B0(MFu2(gO1),MFu2(i1),MAh2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFu2(i1),MAh2),dp) 
B0m2 = MFu(i1)*Real(SA_B0(p2,MFu2(i1),MAh2),dp) 
End If 
coupL1 = cplcUFuFuAhL(gO1,i1)
coupR1 = cplcUFuFuAhR(gO1,i1)
coupL2 =  Conjg(cplcUFuFuAhL(gO2,i1))
coupR2 =  Conjg(cplcUFuFuAhR(gO2,i1))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
!  End if 
!------------------------ 
! Hp, Fd 
!------------------------ 
! If ((Include_in_loopHp).and.(Include_in_loopFd)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFu2(gO1),MFd2(i2),MHp2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(MFu2(gO1),MFd2(i2),MHp2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFd2(i2),MHp2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),MHp2),dp) 
End If 
coupL1 = cplcUFuFdHpL(gO1,i2)
coupR1 = cplcUFuFdHpR(gO1,i2)
coupL2 =  Conjg(cplcUFuFdHpL(gO2,i2))
coupR2 =  Conjg(cplcUFuFdHpR(gO2,i2))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! VWp, Fd 
!------------------------ 
! If ((Include_in_loopVWp).and.(Include_in_loopFd)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = - Real(SA_B1(MFu2(gO1),MFd2(i2),MVWp2) + 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(MFu2(gO1),MFd2(i2),MVWp2)-0.5_dp*rMS_SM,dp) 
Else 
B1m2 = - Real(SA_B1(p2,MFd2(i2),MVWp2)+ 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),MVWp2)-0.5_dp*rMS_SM,dp) 
End If 
coupL1 = cplcUFuFdVWpL(gO1,i2)
coupR1 = cplcUFuFdVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFuFdVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFuFdVWpR(gO2,i2))
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! hh, Fu 
!------------------------ 
! If ((Include_in_loophh).and.(Include_in_loopFu)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -0.5_dp*Real(SA_B1(MFu2(gO1),MFu2(i2),Mhh2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(MFu2(gO1),MFu2(i2),Mhh2),dp) 
Else 
B1m2 = -0.5_dp*Real(SA_B1(p2,MFu2(i2),Mhh2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),Mhh2),dp) 
End If 
coupL1 = cplcUFuFuhhL(gO1,i2)
coupR1 = cplcUFuFuhhR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuhhL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuhhR(gO2,i2))
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
!------------------------ 
! VZ, Fu 
!------------------------ 
! If ((Include_in_loopVZ).and.(Include_in_loopFu)) Then 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = - Real(SA_B1(MFu2(gO1),MFu2(i2),MVZ2),dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(MFu2(gO1),MFu2(i2),MVZ2)-0.5_dp*rMS_SM,dp) 
Else 
B1m2 = - Real(SA_B1(p2,MFu2(i2),MVZ2)+ 0.5_dp*rMS_SM,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),MVZ2)-0.5_dp*rMS_SM,dp) 
End If 


coupL1 = cplcUFuFuVZL(gO1,i2)
coupR1 = cplcUFuFuVZR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVZL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVZR(gO2,i2))
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 



   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
!  End if 
SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFuMZ_SM 


Subroutine DeltaVB_SM(sinW2,sinW2_dr,g2,rho,res)

Implicit None 
Real(dp), Intent(in) :: sinW2,sinW2_Dr, rho,g2 
Real(dp), Intent(out) :: res 
 
Complex(dp) :: sumI, coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,coup3, coup4L,coup4R, teil 
Complex(dp) :: D27m2, D0m2, vertex, phase 
Real(dp) :: cosW2, cosW2_Dr, chargefactor 
Iname = Iname+1
NameOfUnit(Iname) = "DeltaVB_SM" 


!-------------------------- 
!SM Contributions 
!-------------------------- 
cosW2 = 1._dp - sinW2 
cosW2_DR = 1._dp - sinW2_DR 
sumI = 6._dp & 
  & + Log(cosW2)*(3.5_dp - 2.5_dp *sinW2   & 
  & - sinW2_DR*(5._dp - 1.5_dp*cosW2/cosW2_DR))/sinW2   
res = sumI*g2**2*rho 
 

res = res*oo16pi2 
Iname = Iname-1
End subroutine DeltaVB_SM


Real(dp) Function AlphaEW_MS_SM(Q,MFd,MFu,MFe) 
 
Real(dp),Intent(in)::Q,MFd(3),MFu(3),MFe(3)
Integer::i1 
Real(dp)::DeltaAlpha 
DeltaAlpha=1._dp-Alpha/Alpha_MZ_MS! MSbar value^=mW+light fermions 
! DeltaAlpha=DeltaAlpha+alpha/(6._dp*Pi)*(1._dp-1._dp)! conversion to DRbar if necessary 
DeltaAlpha=DeltaAlpha-16._dp/9._dp*Log(MFu(3)/ Q)*Alpha/(2._dp*pi)  
AlphaEW_MS_SM=Alpha/(1._dp-DeltaAlpha) 
 
End Function AlphaEW_MS_SM
 
 
Real(dp) Function AlphaS_MS_SM(Q,MFd,MFu) 
Real(dp),Intent(in)::Q,MFd(3),MFu(3) 
Integer::i1 
Real(dp)::DeltaAlpha 
! DeltaAlpha = 0.5_dp !- 2._dp*Log(sqrt(mf_u2(3))/Q)/3._dp 
! DeltaAlpha=DeltaAlpha-2._dp/3._dp*Log(MFu(3)/ Q)
DeltaAlpha=-2._dp/3._dp*Log(MFu(3)/ Q) 
DeltaAlpha=AlphaS_mZ*DeltaAlpha/(2._dp*Pi) 
AlphaS_MS_SM=AlphaS_mZ/(1._dp-DeltaAlpha)
 
! Conversion to MS bar if necessary 
! If (1._dp.gt.0.5_dp) Then 
! AlphaS_MS_SM = AlphaS_MS_SM*(1._dp - oo4pi*AlphaS_MS_SM-5._dp/4._dp*(AlphaS_MS_SM/Pi)**2) 
! End if 
End Function AlphaS_MS_SM 


Subroutine GetLambdaSM(g_SM,mudim,mh2,lambda)
Implicit None
Complex(dp),Intent(out) :: lambda
Real(dp),Intent(in):: g_SM(62), mudim, mh2
Integer :: i1, kont
Real(dp) :: g1,g2,g3,v
Complex(dp) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3),Mu
Real(dp) ::  mh_SM, pi_SM, pi2_SM


Call GToParameters62_SM(g_SM,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v)

Yu = - Yu

 lambda=(mh2)/v**2
!  

If (CalculateOneLoopMasses) Then

Do i1=1,100

! Call Pih_SM(mh2, Real(Yu(3,3),dp), g1, g2, g3, Real(lambda,dp), v, pi_SM)

! mh_SM = sqrt(lambda*v**2 + pi_SM)

Call Pi1Loop_Mh_SM(v,g1,g2,g3,lambda,Yu,Yd,Ye,Mu,mh2,pi_SM,kont)
Call Pih_2L_SM(mh2,  Real(Yu(3,3),dp), g1, g2, g3, Real(lambda,dp), v, pi2_SM )

mh_SM = sqrt(lambda*v**2 - pi_SM + pi2_SM)



If ((Abs(mh_SM-sqrt(mh2))/sqrt(mh2)).lt.1.0E-6_dp) Then
 Exit
Else 
 lambda = lambda - 0.5_dp*(mh_SM**2-mh2)/v**2
End if

End do

End if


End Subroutine GetLambdaSM

Subroutine Get_mh_pole_SM(g_SM,mudim,delta0,mh2,mh_SM)
Implicit None
Real(dp),Intent(inout):: g_SM(62)
Real(dp), Intent(in) :: mudim, mh2, delta0
Integer :: i1, kont
Real(dp) :: g1,g2,g3,v
Complex(dp) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3),Mu
Real(dp), Intent(out) ::  mh_SM
Real(dp) :: tz, dt, q2, mh_SM_old, pi_SM, pi2_SM, rMS_save, mh2_tree
Logical :: CalculateTwoLoopHiggsMasses_save

Call GToParameters62_SM(g_SM,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v)

Call ParametersToG62_SM(g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v,g_SM)
! 

! Get eff lambda at ren-scale
Call GetLambdaSM(g_SM,mudim,mh2,Lam)


! Run to m_top~160 GeV

tz=0.5_dp*Log(mf_u2(3)/mudim)
dt=tz/100._dp 
g_SM(1)=g_SM(1)*sqrt(5._dp/3._dp) 
g_SM(4)=Real(Lam,dp)
! 
! CalculateOneLoopMasses=.false.
! Call OneLoop_Mh_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,mh_SM,kont)
! Write(*,*) "mh_SM no run", mh_SM, sqrt(mh2)
! 
! CalculateOneLoopMasses=.true.
! Call OneLoop_Mh_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,mh_SM,kont)
! Write(*,*) "mh_SM no run", mh_SM, sqrt(mh2)


Call odeint(g_SM,62,0._dp,tz,delta0,dt,0._dp,rge62_SM,kont) 
g_SM(1)=g_SM(1)/sqrt(5._dp/3._dp) 

Call GToParameters62_SM(g_SM,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v)


Yu = - Yu

CalculateTwoLoopHiggsMasses_save=CalculateTwoLoopHiggsMasses
CalculateTwoLoopHiggsMasses=.true.


q2 = SetRenormalizationScale(mf_u2(3))

! CalculateOneLoopMasses=.false.
! Call OneLoop_Mh_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,mh_SM,kont)
! 
! CalculateOneLoopMasses=.true.
! Call OneLoop_Mh_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,mh_SM,kont)

mh_SM_old=sqrt(mh2)
mh2_tree = Real(Lam*v**2,dp)

rMS_save = rMS
rMS = 1._dp

Do i1=1,100
! 
! Call Pih_SM(mh_SM_old**2, Real(Yu(3,3),dp), g1, g2, g3, Real(Lam,dp), v, pi_SM)
! mh_SM = sqrt(Lam*v**2  + pi_SM)

Call Pi1Loop_Mh_SM(v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,mh2_tree,pi_SM,kont)
Call Pih_2L_SM(mh_SM,  Real(Yu(3,3),dp), g1, g2, g3, Real(Lam,dp), v, pi2_SM )
! 
mh_SM = sqrt(Lam*v**2  - pi_SM + pi2_SM)


If ((Abs(mh_SM-mh_SM_old)/sqrt(mh2)).lt.1.0E-6_dp) Then
 Exit
Else 
 mh_SM_old=mH_SM
End if

End do

CalculateTwoLoopHiggsMasses=CalculateTwoLoopHiggsMasses_save

rMS = rMS_save

q2 = SetRenormalizationScale(mudim)


End Subroutine Get_mh_pole_SM


Subroutine Pih_2L_SM(mh2, Yu, g1, g2, g3, Lam, v, pi_SM )
Implicit None 
Real(dp), Intent(in) :: Yu, g1, g2,g3, v, Lam, mh2
Real(dp), Intent(out) :: pi_SM
Real(dp) :: yt2, mt2, lambda,lambda2,v2,g22,g24,gp2,G2_s,G4_s,mW2_run,mZ2_run, &
& mH2_run,logW,logZ,logH,q2, p2, LogT, LogT2, g32


   yt2 = Yu**2
   mt2 = yt2/2._dp*v**2;
   q2 = getrenormalizationscale()
 
 
!  Write(*,*) "q2", q2
 
   v2 = v**2
   g32 = g3**2
 
    LogT = Log(mt2 / Q2);
   LogT2 = LogT**2;
 
 pi_SM = 0._dp
 
If (CalculateTwoLoopHiggsMasses) Then 
pi_SM= pi_SM + oo16pi2**2*(2._dp*mt2 * 16._dp*g32*yt2*(3._dp*LogT2 + LogT) + &
 & 2._dp*mt2*(-3._dp*yt2**2*(3._dp*LogT2 - 7._dp*LogT + 2._dp + pi**2/3._dp)))
End if


End Subroutine Pih_2L_SM

Subroutine Pih_SM(mh2, Yu, g1, g2, g3, Lam, v, pi_SM )
Implicit None 
Real(dp), Intent(in) :: Yu, g1, g2,g3, v, Lam, mh2
Real(dp), Intent(out) :: pi_SM
Real(dp) :: yt2, mt2, lambda,lambda2,v2,g22,g24,gp2,G2_s,G4_s,mW2_run,mZ2_run, &
& mH2_run,logW,logZ,logH,q2, p2, LogT, LogT2, g32


yt2 = Yu**2
   mt2 = yt2/2._dp*v**2;
   p2 = mh2
   q2 = getrenormalizationscale()
   lambda = Lam/2._dp   
   lambda2 = Lambda**2;

   v2 = v**2
   g22 = g2**2
   g24 = g2**4
   gp2  = g1**2
   g32 = g3**2
   G2_s = g22 + gp2;
   G4_s = G2_S**2
   mW2_run = g22 * v2/4.;
   mZ2_run = G2_s * v2/4.;
   mH2_run = 2*lambda*v2;
   LogW = Log(mW2_run / Q2);
   LogZ = Log(mZ2_run / Q2);
   LogH = Log(mH2_run / Q2);

pi_SM = oo16pi2*(+3*yt2*((4*mt2 - p2)*B0(p2,mt2,mt2)) &
! &       +6*lambda2*v2*(3*LogH-6+Pi*Sqrt(3._dp)) &
!   & - (4.5_dp*v2*Lam**2*B0(p2,mH2_run,mH2_run)) &
&       -v2/4._dp*(3._dp*g24-8._dp*lambda*g22+16._dp*lambda2)*B0(mW2_run,mW2_run,p2) &
&       -v2/8._dp*(3._dp*G4_s-8._dp*lambda*G2+16._dp*lambda2)*B0(mZ2_run,mZ2_run,p2) &
&       +2._dp*mW2*(g22-2*lambda*(LogW-1._dp)) &
&       +mZ2_run*(G2_s-2._dp*lambda*(LogZ-1._dp)) &
& )
   LogT = Log(mt2 / Q2);
   LogT2 = LogT**2;


If (CalculateTwoLoopHiggsMasses) Then 
pi_SM= pi_SM + 0*oo16pi2**2*(2*mt2 * 16*g32*yt2*(3*LogT2 + LogT) + &
 & 2*mt2*(-3*yt2**2*(3*LogT2 - 7*LogT + 2 + pi**2/3.)))
End if


End Subroutine Pih_SM


Complex(dp) Function VVVloopSM(p2,m12,m22) 
Implicit None 
Real(dp),Intent(in)::p2,m12,m22 
Real(dp) :: b001


  VVVloopSM=   -2._dp*rMS_SM*(m12 + m22 - p2/3._dp) + 10._dp*SA_B00(p2,m12,m22) &
     & + (m12+m22+4._dp*p2)*SA_B0(p2,m12,m22)+  SA_A0(m12) + SA_A0(m22)

     End Function VVVloopSM
 
End Module LoopMasses_SM_HC
