! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:47 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module LoopMasses_Inert2 
 
Use Control 
Use Settings 
Use Couplings_Inert2 
Use LoopFunctions 
Use AddLoopFunctions 
Use Mathematics 
Use MathematicsQP 
Use Model_Data_Inert2 
Use StandardModel 
Use Tadpoles_Inert2 
 Use Pole2L_Inert2 
 Use TreeLevelMasses_Inert2 
 
Real(dp), Private :: MHp_1L(2), MHp2_1L(2)  
Complex(dp), Private :: ZP_1L(2,2)  
Real(dp), Private :: MFd_1L(3), MFd2_1L(3)  
Complex(dp), Private :: ZDL_1L(3,3),ZDR_1L(3,3)
Real(dp), Private :: MFu_1L(3), MFu2_1L(3)  
Complex(dp), Private :: ZUL_1L(3,3),ZUR_1L(3,3)
Real(dp), Private :: MFe_1L(3), MFe2_1L(3)  
Complex(dp), Private :: ZEL_1L(3,3),ZER_1L(3,3)
Real(dp), Private :: MG0_1L, MG02_1L  
Real(dp), Private :: Mhh_1L, Mhh2_1L  
Real(dp), Private :: MA0_1L, MA02_1L  
Real(dp), Private :: MH0_1L, MH02_1L  
Real(dp), Private :: MVZ_1L, MVZ2_1L  
Real(dp), Private :: MVWp_1L, MVWp2_1L  
Real(dp) :: pi2A0  
Real(dp) :: ti_ep2L(1)  
Real(dp) :: pi_ep2L(1,1)
Real(dp) :: Pi2S_EffPot(1,1)
Real(dp) :: PiP2S_EffPot(1,1)
Contains 
 
Subroutine OneLoopMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,kont)

Implicit None 
Real(dp),Intent(inout) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(inout) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(inout) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(inout) :: v

Complex(dp) :: cplA0A0A0A0,cplA0A0cVWpVWp,cplA0A0G0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hh,               & 
& cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0A0UHpcUHp(2,2),cplA0A0VZVZ,cplA0cUHpVWp(2),         & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcUHp(2,2),cplA0HpcVWp(2),         & 
& cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),  & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFdFucUHpL(3,3,2),cplcFdFucUHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),       & 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3),  & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcUHpL(3,3,2),               & 
& cplcFeFvcUHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFuG0L(3,3),           & 
& cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
& cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgGgGVG,cplcgWCgAcVWp,cplcgWCgWCG0,cplcgWCgWChh,     & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcUHp(2),cplcgWCgZcVWp,cplcgWpgWpG0,cplcgWpgWphh,    & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWpgZUHp(2),cplcgZgWCUHp(2),cplcgZgWpcUHp(2),            & 
& cplcgZgWpcVWp,cplcgZgZhh,cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcUFdFdG0L(3,3),              & 
& cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),cplcUFdFdVGL(3,3),               & 
& cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),               & 
& cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),cplcUFdFucHpR(3,3,2),cplcUFdFucVWpL(3,3),       & 
& cplcUFdFucVWpR(3,3),cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),             & 
& cplcUFeFehhR(3,3),cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),               & 
& cplcUFeFeVZR(3,3),cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),       & 
& cplcUFeFvcVWpR(3,3),cplcUFuFdHpL(3,3,2),cplcUFuFdHpR(3,3,2),cplcUFuFdVWpL(3,3),        & 
& cplcUFuFdVWpR(3,3),cplcUFuFuG0L(3,3),cplcUFuFuG0R(3,3),cplcUFuFuhhL(3,3),              & 
& cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),               & 
& cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3),cplcUFvFeHpL(3,3,2),             & 
& cplcUFvFeHpR(3,3,2),cplcUFvFeVWpL(3,3),cplcUFvFeVWpR(3,3),cplcUFvFvVZL(3,3),           & 
& cplcUFvFvVZR(3,3),cplcUHpVPVWp(2),cplcUHpVWpVZ(2),cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,& 
& cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWp,       & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplG0cUHpVWp(2),cplG0G0cVWpVWp,cplG0G0G0G0,            & 
& cplG0G0H0H0,cplG0G0hh,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0G0UHpcUHp(2,2),               & 
& cplG0G0VZVZ,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplH0cUHpVWp(2),cplH0H0cVWpVWp,         & 
& cplH0H0H0H0,cplH0H0hh,cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0H0UHpcUHp(2,2),               & 
& cplH0H0VZVZ,cplH0HpcHp(2,2),cplH0HpcUHp(2,2),cplH0HpcVWp(2),cplhhcUHpVWp(2),           & 
& cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhhh,cplhhhhhhhh,cplhhhhHpcHp(2,2),cplhhhhUHpcUHp(2,2),& 
& cplhhhhVZVZ,cplhhHpcHp(2,2),cplhhHpcUHp(2,2),cplhhHpcVWp(2),cplhhVZVZ,cplHpcHpcVWpVWp(2,2),& 
& cplHpcHpVP(2,2),cplHpcHpVPVP(2,2),cplHpcHpVPVZ(2,2),cplHpcHpVZ(2,2),cplHpcHpVZVZ(2,2)

Complex(dp) :: cplHpcUHpVP(2,2),cplHpcUHpVZ(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2),cplUHpcUHpcVWpVWp(2,2),& 
& cplUHpcUHpVPVP(2,2),cplUHpcUHpVZVZ(2,2),cplUHpHpcUHpcHp(2,2,2,2),cplVGVGVG,            & 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1, j2, j3, j4, il, i_count, ierr 
Integer :: i2L, iFin 
Logical :: Convergence2L 
Real(dp) :: Pi2S_EffPot_save(1,1), diff(1,1)
Complex(dp) :: Tad1Loop(2), dmz2  
Real(dp) :: comp(1), tanbQ, vev2, vSM
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopMasses' 
 
kont = 0 
 
! Set Gauge fixing parameters 
RXi= RXiNew 
RXiG = RXi 
RXiP = RXi 
RXiWp = RXi 
RXiZ = RXi 

 ! Running angles 

 
Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,GenerationMixing,kont)

MHD2Tree  = MHD2

 
 If (CalculateOneLoopMasses) Then 
 
If ((DecoupleAtRenScale).and.(Abs(1._dp-RXiNew).lt.0.01_dp)) Then 
vSM=vSM_Q 
v=vSM 
Else 
Call CouplingsForVectorBosons(g1,g2,TW,ZP,v,ZDL,ZUL,ZEL,cplG0hhVZ,cplG0HpcVWp,        & 
& cplG0G0cVWpVWp,cplG0G0VZVZ,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplhhhhcVWpVWp,          & 
& cplhhhhVZVZ,cplA0H0VZ,cplA0HpcVWp,cplA0A0cVWpVWp,cplA0A0VZVZ,cplH0HpcVWp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,            & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,              & 
& cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcVWpVWpVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,   & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplHpcHpcVWpVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,     & 
& cplcVWpcVWpVWpVWp3,cplcHpVWpVZ,cplcHpVPVWp,cplHpcHpVPVZ,cplcVWpVPVWpVZ1,               & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)

Call Pi1LoopVZ(mZ2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,             & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,dmZ2)

vev2=4._dp*Real(mZ2+dmz2,dp)/(g1**2+g2**2) -0 
vSM=sqrt(vev2) 
v=vSM 
End if 
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,v,(/ ZeroC, ZeroC /))

Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,GenerationMixing,kont)

Call CouplingsForLoopMasses(lam5,lam4,v,ZP,g2,Yd,Yu,ZDL,ZDR,ZUL,ZUR,Ye,               & 
& ZER,g1,TW,lam1,lam3,lam2,g3,ZEL,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,cplcFdFucUHpR,  & 
& cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,cplcgWCgZcUHp,     & 
& cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,cplHpcUHpVP,            & 
& cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,cplH0H0UHpcUHp,    & 
& cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,cplUHpcUHpVZVZ,        & 
& cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,cplcUFdFdVGR,         & 
& cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,cplcUFdFucHpR,       & 
& cplcUFdFucVWpL,cplcUFdFucVWpR,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,   & 
& cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,         & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeG0L,cplcUFeFeG0R,         & 
& cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,         & 
& cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,cplcUFvFeHpL,cplcUFvFeHpR,   & 
& cplcUFvFeVWpL,cplcUFvFeVWpR,cplcUFvFvVZL,cplcUFvFvVZR,cplA0A0G0,cplA0G0H0,             & 
& cplcFdFdG0L,cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,       & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,           & 
& cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,       & 
& cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,   & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0A0A0A0,               & 
& cplA0A0H0H0,cplA0A0HpcHp,cplA0A0cVWpVWp,cplA0A0VZVZ,cplH0HpcHp,cplH0HpcVWp,            & 
& cplH0H0H0H0,cplH0H0HpcHp,cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVGL,cplcFdFdVGR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,   & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,            & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplHpcHpVZVZ,            & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcFdFucVWpL,cplcFdFucVWpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,   & 
& cplHpcHpcVWpVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcHpVWpVZ,cplcHpVPVWp,cplHpcHpVPVZ,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)

Call OneLoopTadpoleshh(v,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0A0hh,cplcFdFdhhL,cplcFdFdhhR,          & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplcgWpgWphh,cplcgWCgWChh,   & 
& cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhcVWpVWp,cplhhVZVZ,Tad1Loop(1:1))

MHD2Tree  = MHD2
If (CalculateTwoLoopHiggsMasses) Then 
    If(GaugelessLimit) Then 
  vFix = 0._dp 
   g1_saveEP =g1
   g1 = 0._dp 
   g2_saveEP =g2
   g2 = 0._dp 
     Else 
  vFix = v 
     End if 

SELECT CASE (TwoLoopMethod) 
CASE ( 1 , 2 ) 


 CASE ( 3 ) ! Diagrammatic method 
  ! Make sure that there are no exactly degenerated masses! 
   Ye_saveEP =Ye
   where (aint(Abs(Ye)).eq.Ye) Ye=Ye*(1 + 1*1.0E-12_dp)
   Yd_saveEP =Yd
   where (aint(Abs(Yd)).eq.Yd) Yd=Yd*(1 + 2*1.0E-12_dp)
   Yu_saveEP =Yu
   where (aint(Abs(Yu)).eq.Yu) Yu=Yu*(1 + 3*1.0E-12_dp)

If (NewGBC) Then 
Call CalculatePi2S(125._dp**2,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,              & 
& Yu,MHD2,MHU2,kont,ti_ep2L,Pi2S_EffPot,PiP2S_EffPot)

Else 
Call CalculatePi2S(0._dp,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,kont,ti_ep2L,Pi2S_EffPot,PiP2S_EffPot)

End if 
   Ye =Ye_saveEP 
   Yd =Yd_saveEP 
   Yu =Yu_saveEP 


 CASE ( 8 , 9 ) ! Hard-coded routines 
  
 END SELECT
 
   If(GaugelessLimit) Then 
   g1 =g1_saveEP 
   g2 =g2_saveEP 
   End if 

Else ! Two loop turned off 
Pi2S_EffPot = 0._dp 

Pi2A0 = 0._dp 

ti_ep2L = 0._dp 

End if 
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,v,Tad1Loop)

MHD21L = MHD2
Tad1Loop(1:1) = Tad1Loop(1:1) - ti_ep2L 
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,v,Tad1Loop)

MHD22L = MHD2
Call OneLoopHp(g2,MHD21L,MHU2,lam1,lam4,lam3,v,MHp,MHp2,MA0,MA02,MVWp,MVWp2,          & 
& MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,            & 
& cplA0cUHpVWp,cplcFdFucUHpL,cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,     & 
& cplcgZgWpcUHp,cplcgWpgZUHp,cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,        & 
& cplhhHpcUHp,cplhhcUHpVWp,cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,            & 
& cplA0A0UHpcUHp,cplG0G0UHpcUHp,cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,           & 
& cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,cplUHpcUHpVZVZ,0.1_dp*delta_mass,MHp_1L,              & 
& MHp2_1L,ZP_1L,kont)

Call OneLoopFd(Yd,v,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,MFu2,            & 
& MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,           & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,0.1_dp*delta_mass,MFd_1L,MFd2_1L,          & 
& ZDL_1L,ZDR_1L,kont)

Call OneLoopFu(Yu,v,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,Mhh,               & 
& Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,cplcUFuFuG0L,      & 
& cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,         & 
& cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,0.1_dp*delta_mass,MFu_1L,MFu2_1L,               & 
& ZUL_1L,ZUR_1L,kont)

Call OneLoopFe(Ye,v,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,          & 
& cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,         & 
& cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,   & 
& 0.1_dp*delta_mass,MFe_1L,MFe2_1L,ZEL_1L,ZER_1L,kont)

Call OneLoopG0(g1,g2,MHD22L,lam1,v,TW,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,           & 
& cplcFdFdG0L,cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,       & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,           & 
& 0.1_dp*delta_mass,MG0_1L,MG02_1L,kont)

Call OneLoophh(MHD22L,lam1,v,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,       & 
& cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,       & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,   & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,0.1_dp*delta_mass,Mhh_1L,Mhh2_1L,kont)

Call OneLoopA0(lam5,MHU2,lam3,v,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,              & 
& MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,   & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,0.1_dp*delta_mass,MA0_1L,MA02_1L,kont)

Call OneLoopH0(lam5,MHU2,lam3,v,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,              & 
& MH02,MHp,MHp2,MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,   & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,0.1_dp*delta_mass,MH0_1L,MH02_1L,kont)

MHp = MHp_1L 
MHp2 = MHp2_1L 
ZP = ZP_1L 
MG0 = MG0_1L 
MG02 = MG02_1L 
Mhh = Mhh_1L 
Mhh2 = Mhh2_1L 
MA0 = MA0_1L 
MA02 = MA02_1L 
MH0 = MH0_1L 
MH02 = MH02_1L 
End If 
 
Call SortGoldstones(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,            & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,             & 
& betaH,kont)

! Set pole masses 
MVWp = mW 
MVWp2 = mW2 
MVZ = mZ 
MVZ2 = mZ2 
MFe(1:3) = mf_l 
MFe2(1:3) = mf_l**2 
MFu(1:3) = mf_u 
MFu2(1:3) = mf_u**2 
MFd(1:3) = mf_d 
MFd2(1:3) = mf_d**2 
! Shift Everything to t'Hooft Gauge
RXi=  1._dp 
RXiG = 1._dp 
RXiP = 1._dp 
RXiWp = 1._dp 
RXiZ = 1._dp 
MG0=MVZ
MG02=MVZ2
MHp(1)=MVWp
MHp2(1)=MVWp2
mf_u2 = mf_u**2 
mf_d2 = mf_d**2 
mf_l2 = mf_l**2 
 

 If (WriteTreeLevelTadpoleSolutions) Then 
! Saving tree-level parameters for output
MHD2  = MHD2Tree 
End if 


Iname = Iname -1 
End Subroutine OneLoopMasses 
 
Subroutine OneLoopTadpoleshh(v,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,               & 
& MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0A0hh,cplcFdFdhhL,             & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplcgWpgWphh,    & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhcVWpVWp,cplhhVZVZ,tadpoles)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0A0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),        & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplG0G0hh,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,      & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhcVWpVWp,cplhhVZVZ

Real(dp), Intent(in) :: v

Integer :: i1,i2, gO1, gO2 
Complex(dp) :: coupL, coupR, coup, temp, res, A0m, sumI(1)  
Real(dp) :: m1 
Complex(dp), Intent(out) :: tadpoles(1) 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopTadpoleshh'
 
tadpoles = 0._dp 
 
!------------------------ 
! A0 
!------------------------ 
A0m = SA_A0(MA02) 
  Do gO1 = 1, 1
   coup = cplA0A0hh
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
!------------------------ 
! bar[Fd] 
!------------------------ 
Do i1 = 1, 3
 A0m = 2._dp*MFd(i1)*SA_A0(MFd2(i1)) 
  Do gO1 = 1, 1
   coupL = cplcFdFdhhL(i1,i1)
   coupR = cplcFdFdhhR(i1,i1)
   sumI(gO1) = (coupL+coupR)*A0m 
  End Do 
 
tadpoles =  tadpoles + 3._dp*sumI 
End Do 
 !------------------------ 
! bar[Fe] 
!------------------------ 
Do i1 = 1, 3
 A0m = 2._dp*MFe(i1)*SA_A0(MFe2(i1)) 
  Do gO1 = 1, 1
   coupL = cplcFeFehhL(i1,i1)
   coupR = cplcFeFehhR(i1,i1)
   sumI(gO1) = (coupL+coupR)*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
End Do 
 !------------------------ 
! bar[Fu] 
!------------------------ 
Do i1 = 1, 3
 A0m = 2._dp*MFu(i1)*SA_A0(MFu2(i1)) 
  Do gO1 = 1, 1
   coupL = cplcFuFuhhL(i1,i1)
   coupR = cplcFuFuhhR(i1,i1)
   sumI(gO1) = (coupL+coupR)*A0m 
  End Do 
 
tadpoles =  tadpoles + 3._dp*sumI 
End Do 
 !------------------------ 
! G0 
!------------------------ 
A0m = SA_A0(MG02) 
  Do gO1 = 1, 1
   coup = cplG0G0hh
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
!------------------------ 
! bar[gWp] 
!------------------------ 
A0m = 1._dp*SA_A0(MVWp2*RXi) 
  Do gO1 = 1, 1
    coup = cplcgWpgWphh
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
!------------------------ 
! bar[gWpC] 
!------------------------ 
A0m = 1._dp*SA_A0(MVWp2*RXi) 
  Do gO1 = 1, 1
    coup = cplcgWCgWChh
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
!------------------------ 
! bar[gZ] 
!------------------------ 
A0m = 1._dp*SA_A0(MVZ2*RXi) 
  Do gO1 = 1, 1
    coup = cplcgZgZhh
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
!------------------------ 
! H0 
!------------------------ 
A0m = SA_A0(MH02) 
  Do gO1 = 1, 1
   coup = cplH0H0hh
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
!------------------------ 
! hh 
!------------------------ 
A0m = SA_A0(Mhh2) 
  Do gO1 = 1, 1
   coup = cplhhhhhh
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 
!------------------------ 
! conj[Hp] 
!------------------------ 
Do i1 = 1, 2
 A0m = SA_A0(MHp2(i1)) 
  Do gO1 = 1, 1
   coup = cplhhHpcHp(i1,i1)
   sumI(gO1) = -coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
A0m = 3._dp*SA_A0(MVWp2)+RXi*SA_A0(MVWp2*RXi) - 2._dp*MVWp2*rMS 
  Do gO1 = 1, 1
    coup = cplhhcVWpVWp
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp*sumI 
!------------------------ 
! VZ 
!------------------------ 
A0m = 3._dp*SA_A0(MVZ2)+RXi*SA_A0(MVZ2*RXi) - 2._dp*MVZ2*rMS 
  Do gO1 = 1, 1
    coup = cplhhVZVZ
    sumI(gO1) = coup*A0m 
  End Do 
 
tadpoles =  tadpoles + 1._dp/2._dp*sumI 



tadpoles = oo16pi2*tadpoles 
Iname = Iname - 1 
End Subroutine OneLoopTadpoleshh 
 
Subroutine OneLoopHp(g2,MHD2,MHU2,lam1,lam4,lam3,v,MHp,MHp2,MA0,MA02,MVWp,            & 
& MVWp2,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,      & 
& cplA0cUHpVWp,cplcFdFucUHpL,cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,     & 
& cplcgZgWpcUHp,cplcgWpgZUHp,cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,        & 
& cplhhHpcUHp,cplhhcUHpVWp,cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,            & 
& cplA0A0UHpcUHp,cplG0G0UHpcUHp,cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,           & 
& cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,cplUHpcUHpVZVZ,delta,mass,mass2,RS,kont)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MA0,MA02,MVWp,MVWp2,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),              & 
& MFe2(3),MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2

Real(dp), Intent(in) :: g2,MHD2,MHU2,v

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(in) :: cplA0HpcUHp(2,2),cplA0cUHpVWp(2),cplcFdFucUHpL(3,3,2),cplcFdFucUHpR(3,3,2),           & 
& cplcFeFvcUHpL(3,3,2),cplcFeFvcUHpR(3,3,2),cplG0cUHpVWp(2),cplcgZgWpcUHp(2),            & 
& cplcgWpgZUHp(2),cplcgWCgZcUHp(2),cplcgZgWCUHp(2),cplH0HpcUHp(2,2),cplH0cUHpVWp(2),     & 
& cplhhHpcUHp(2,2),cplhhcUHpVWp(2),cplHpcUHpVP(2,2),cplHpcUHpVZ(2,2),cplcUHpVPVWp(2),    & 
& cplcUHpVWpVZ(2),cplA0A0UHpcUHp(2,2),cplG0G0UHpcUHp(2,2),cplH0H0UHpcUHp(2,2),           & 
& cplhhhhUHpcUHp(2,2),cplUHpHpcUHpcHp(2,2,2,2),cplUHpcUHpVPVP(2,2),cplUHpcUHpcVWpVWp(2,2),& 
& cplUHpcUHpVZVZ(2,2)

Complex(dp) :: mat2a(2,2), mat2(2,2),  PiSf(2,2,2)
Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi2(2), test_m2(2),p2, test(2) 
Real(dp), Intent(out) :: mass(2), mass2(2) 
Complex(dp), Intent(out) ::  RS(2,2) 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopHp'
 
mat2a(1,1) = 0._dp 
mat2a(1,1) = mat2a(1,1)+MHU2
mat2a(1,1) = mat2a(1,1)+(lam3*v**2)/2._dp
mat2a(1,1) = mat2a(1,1)+(lam4*v**2)/2._dp
mat2a(1,2) = 0._dp 
mat2a(2,2) = 0._dp 
mat2a(2,2) = mat2a(2,2)+MHD2
mat2a(2,2) = mat2a(2,2)+(lam1*v**2)/2._dp
mat2a(2,2) = mat2a(2,2)+(g2**2*v**2*RXiWp)/4._dp

 
 Do i1=2,2
  Do i2 = 1, i1-1 
  mat2a(i1,i2) = Conjg(mat2a(i2,i1)) 
  End do 
End do 

 
! Rotation matrix for p2=0 
PiSf(1,:,:) = ZeroC 
p2 = 0._dp 
If (i1.eq.1) p2 = 0._dp 
Call Pi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,MFe,MFe2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,            & 
& cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,     & 
& cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,          & 
& cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,       & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,        & 
& cplUHpcUHpVZVZ,kont,PiSf(1,:,:))

mat2 = mat2a - Real(PiSf(1,:,:),dp) 
Call Chop(mat2) 
Call Eigensystem(mat2,mi2,RS,kont,test) 
ZPOS_0 = RS 
 
 
! Now with momenta 
Do i1=1,2
PiSf(i1,:,:) = ZeroC 
p2 = MHp2(i1)
If (i1.eq.1) p2 = 0._dp 
Call Pi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,MFe,MFe2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,            & 
& cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,     & 
& cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,          & 
& cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,       & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,        & 
& cplUHpcUHpVZVZ,kont,PiSf(i1,:,:))

End Do 
Do i1=2,1,-1 
mat2 = mat2a - Real(PiSf(i1,:,:),dp) 
Call Chop(mat2) 
Call Eigensystem(mat2,mi2,RS,kont,test) 
If ((kont.Eq.-8).Or.(kont.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  kont = 0 
End If 
If ((kont.Ne.0).And.(ErrorLevel.Ge.0)) Then 
  Write(ErrCan,*) "Diagonalization did not work in routine "//NameOfUnit(Iname) 
  Write(*,*) "Diagonalization did not work in routine "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
End If 
mass2(i1) = mi2(i1) 
End do 
 
Do i1=1,2
  If (Abs(mass2(i1)).Le.MaxMassNumericalZero**2) mass2(i1) = 0._dp 
  If (mass2(i1).Ge.0._dp) Then 
    mass(i1) = Sqrt(mass2(i1)) 
  Else 
   If (ErrorLevel.Ge.0) Then 
   If ((i1.Gt.1).or.(Abs(mass2(i1)).gt.MaxVal(Abs(mass2)))) Then 
     Write(*,*) 'Warning from routine '//NameOfUnit(Iname) 
     Write(*,*) 'in the calculation of the masses' 
     Write(*,*) 'occurred a negative mass squared!' 
   Call TerminateProgram 
   End If 
   End If 
   kont = -301 
   mass(i1) = 0._dp 
  End If 
End Do 
 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
Do i1=1,2
PiSf(i1,:,:) = ZeroC 
p2 =  mass2(i1) 
If (i1.eq.1) p2 = 0._dp 
Call Pi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,MFe,MFe2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,            & 
& cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,     & 
& cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,          & 
& cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,       & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,        & 
& cplUHpcUHpVZVZ,kont,PiSf(i1,:,:))

End Do 
Do i1=2,1,-1 
mat2 = mat2a - Real(PiSf(i1,:,:),dp) 
Call Chop(mat2) 
Call Eigensystem(mat2,mi2,RS,kont,test) 
ZPOS_p2(i1,:) = RS(i1,:) 
 If ((kont.Eq.-8).Or.(kont.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  kont = 0 
End If 
If ((kont.Ne.0).And.(ErrorLevel.Ge.0)) Then 
  Write(ErrCan,*) "Diagonalization did not work in routine "//NameOfUnit(Iname) 
  Write(*,*) "Diagonalization did not work in routine "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
End If 
mass2(i1) = mi2(i1) 
End do 
Do i1=1,2
 If (Abs(mass2(i1)).Le.MaxMassNumericalZero**2) mass2(i1) = 0._dp 
 If (test_m2(i1).Ne.0._dp) Then 
    test_m2(i1) = Abs(test_m2(i1) - mass2(i1)) / test_m2(i1) 
 Else 
    test_m2(i1) = Abs(mass2(i1)) 
 End If 
 If (Abs(mass2(i1)).lt.1.0E-30_dp) test_m2(i1) = 0._dp 
 If (mass2(i1).Ge.0._dp) Then 
    mass(i1) = sqrt(mass2(i1)) 
  Else 
     Write(*,*) 'Warning from routine '//NameOfUnit(Iname) 
     Write(*,*) 'in the calculation of the masses occurred a negative mass squared!' 
     Write(*,*) 'generation: ',i1 
     Write(*,*) 'mass: ',mass2(i1) 
   SignOfMassChanged = .True. 
   mass(i1) = 0._dp 
  End If 
End Do 
 
If (Maxval(test_m2).LT.0.1_dp*delta) Exit 
If (i_count.Gt.30) Then 
  Write(*,*) "Problem in "//NameOfUnit(Iname), test_m2, mass2 
  kont = -510 
  Call AddError(510) 
 Exit 
End If 
End Do 
 
 
Iname = Iname -1 
End Subroutine OneLoopHp
 
 
Subroutine Pi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,               & 
& MFe,MFe2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,   & 
& cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,     & 
& cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,          & 
& cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,       & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,        & 
& cplUHpcUHpVZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MA0,MA02,MVWp,MVWp2,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),              & 
& MFe2(3),MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0HpcUHp(2,2),cplA0cUHpVWp(2),cplcFdFucUHpL(3,3,2),cplcFdFucUHpR(3,3,2),           & 
& cplcFeFvcUHpL(3,3,2),cplcFeFvcUHpR(3,3,2),cplG0cUHpVWp(2),cplcgZgWpcUHp(2),            & 
& cplcgWpgZUHp(2),cplcgWCgZcUHp(2),cplcgZgWCUHp(2),cplH0HpcUHp(2,2),cplH0cUHpVWp(2),     & 
& cplhhHpcUHp(2,2),cplhhcUHpVWp(2),cplHpcUHpVP(2,2),cplHpcUHpVZ(2,2),cplcUHpVPVWp(2),    & 
& cplcUHpVWpVZ(2),cplA0A0UHpcUHp(2,2),cplG0G0UHpcUHp(2,2),cplH0H0UHpcUHp(2,2),           & 
& cplhhhhUHpcUHp(2,2),cplUHpHpcUHpcHp(2,2,2,2),cplUHpcUHpVPVP(2,2),cplUHpcUHpcVWpVWp(2,2),& 
& cplUHpcUHpVZVZ(2,2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res(2,2) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI(2,2) 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! Hp, A0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(SA_B0(p2,MHp2(i1),MA02),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplA0HpcUHp(i1,gO1)
coup2 = Conjg(cplA0HpcUHp(i1,gO2))
    SumI(gO1,gO2) = coup1*coup2*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, A0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = FloopRXi(p2,MA02,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplA0cUHpVWp(gO1)
coup2 =  Conjg(cplA0cUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = Real(SA_Gloop(p2,MFd2(i1),MFu2(i2)),dp) 
B0m2 = -2._dp*MFd(i1)*MFu(i2)*Real(SA_B0(p2,MFd2(i1),MFu2(i2)),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coupL1 = cplcFdFucUHpL(i1,i2,gO1)
coupR1 = cplcFdFucUHpR(i1,i2,gO1)
coupL2 =  Conjg(cplcFdFucUHpL(i1,i2,gO2))
coupR2 =  Conjg(cplcFdFucUHpR(i1,i2,gO2))
    SumI(gO1,gO2) = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
   End Do 
End Do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fv 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = Real(SA_Gloop(p2,MFe2(i1),0._dp),dp) 
B0m2 = -2._dp*MFe(i1)*0._dp*Real(SA_B0(p2,MFe2(i1),0._dp),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coupL1 = cplcFeFvcUHpL(i1,i2,gO1)
coupR1 = cplcFeFvcUHpR(i1,i2,gO1)
coupL2 =  Conjg(cplcFeFvcUHpL(i1,i2,gO2))
coupR2 =  Conjg(cplcFeFvcUHpR(i1,i2,gO2))
    SumI(gO1,gO2) = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! VWp, G0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = FloopRXi(p2,MG02,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplG0cUHpVWp(gO1)
coup2 =  Conjg(cplG0cUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 = -Real(SA_B0(p2,MVWp2*RXi,MVZ2*RXi),dp) 
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcgZgWpcUHp(gO1)
coup2 =  cplcgWpgZUHp(gO2) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gZ 
!------------------------ 
sumI = 0._dp 
 
F0m2 = -Real(SA_B0(p2,MVZ2*RXi,MVWp2*RXi),dp) 
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcgWCgZcUHp(gO1)
coup2 =  cplcgZgWCUHp(gO2) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! Hp, H0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(SA_B0(p2,MHp2(i1),MH02),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplH0HpcUHp(i1,gO1)
coup2 = Conjg(cplH0HpcUHp(i1,gO2))
    SumI(gO1,gO2) = coup1*coup2*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, H0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = FloopRXi(p2,MH02,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplH0cUHpVWp(gO1)
coup2 =  Conjg(cplH0cUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! Hp, hh 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(SA_B0(p2,MHp2(i1),Mhh2),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplhhHpcUHp(i1,gO1)
coup2 = Conjg(cplhhHpcUHp(i1,gO2))
    SumI(gO1,gO2) = coup1*coup2*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, hh 
!------------------------ 
sumI = 0._dp 
 
F0m2 = FloopRXi(p2,Mhh2,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplhhcUHpVWp(gO1)
coup2 =  Conjg(cplhhcUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! VP, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = FloopRXi(p2,MHp2(i2),0._dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplHpcUHpVP(i2,gO1)
coup2 =  Conjg(cplHpcUHpVP(i2,gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VZ, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = FloopRXi(p2,MHp2(i2),MVZ2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplHpcUHpVZ(i2,gO1)
coup2 =  Conjg(cplHpcUHpVZ(i2,gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VWp, VP 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(SVVloop(p2,0._dp,MVWp2),dp)   
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcUHpVPVWp(gO1)
coup2 =  Conjg(cplcUHpVPVWp(gO2)) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! VZ, VWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(SVVloop(p2,MVWp2,MVZ2),dp)   
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcUHpVWpVZ(gO1)
coup2 =  Conjg(cplcUHpVWpVZ(gO2)) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MA02) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplA0A0UHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MG02) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplG0G0UHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MH02) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplH0H0UHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(Mhh2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplhhhhUHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_A0(MHp2(i1)) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpHpcUHpcHp(gO2,i1,gO1,i1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VP, VP 
!------------------------ 
sumI = 0._dp 
 
!------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 = 0.75_dp*SA_A0(MVWp2) + 0.25_dp*RXi*SA_A0(MVWp2*RXi) - 0.5_dp*MVWp2*rMS 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpcUHpcVWpVWp(gO2,gO1)
    SumI(gO1,gO2) = coup1*A0m2 
   End Do 
End Do 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 = 0.75_dp*SA_A0(MVZ2) + 0.25_dp*RXi*SA_A0(MVZ2*RXi) - 0.5_dp*MVZ2*rMS 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpcUHpVZVZ(gO2,gO1)
    SumI(gO1,gO2) = coup1*A0m2 
   End Do 
End Do 
res = res +2._dp* SumI  


Do gO2 = 1, 2
  Do gO1 = gO2+1, 2
     res(gO1,gO2) = Conjg(res(gO2,gO1))  
   End Do 
End Do 
 
res = oo16pi2*res 
 
End Subroutine Pi1LoopHp 
 
Subroutine DerPi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,            & 
& MFe,MFe2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,   & 
& cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,     & 
& cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,          & 
& cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,       & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,        & 
& cplUHpcUHpVZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MA0,MA02,MVWp,MVWp2,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),              & 
& MFe2(3),MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0HpcUHp(2,2),cplA0cUHpVWp(2),cplcFdFucUHpL(3,3,2),cplcFdFucUHpR(3,3,2),           & 
& cplcFeFvcUHpL(3,3,2),cplcFeFvcUHpR(3,3,2),cplG0cUHpVWp(2),cplcgZgWpcUHp(2),            & 
& cplcgWpgZUHp(2),cplcgWCgZcUHp(2),cplcgZgWCUHp(2),cplH0HpcUHp(2,2),cplH0cUHpVWp(2),     & 
& cplhhHpcUHp(2,2),cplhhcUHpVWp(2),cplHpcUHpVP(2,2),cplHpcUHpVZ(2,2),cplcUHpVPVWp(2),    & 
& cplcUHpVWpVZ(2),cplA0A0UHpcUHp(2,2),cplG0G0UHpcUHp(2,2),cplH0H0UHpcUHp(2,2),           & 
& cplhhhhUHpcUHp(2,2),cplUHpHpcUHpcHp(2,2,2,2),cplUHpcUHpVPVP(2,2),cplUHpcUHpcVWpVWp(2,2),& 
& cplUHpcUHpVZVZ(2,2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res(2,2) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI(2,2) 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! Hp, A0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(SA_DerB0(p2,MHp2(i1),MA02),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplA0HpcUHp(i1,gO1)
coup2 = Conjg(cplA0HpcUHp(i1,gO2))
    SumI(gO1,gO2) = coup1*coup2*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, A0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = DerFloopRXi(p2,MA02,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplA0cUHpVWp(gO1)
coup2 =  Conjg(cplA0cUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = Real(SA_DerGloop(p2,MFd2(i1),MFu2(i2)),dp) 
B0m2 = -2._dp*MFd(i1)*MFu(i2)*Real(SA_DerB0(p2,MFd2(i1),MFu2(i2)),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coupL1 = cplcFdFucUHpL(i1,i2,gO1)
coupR1 = cplcFdFucUHpR(i1,i2,gO1)
coupL2 =  Conjg(cplcFdFucUHpL(i1,i2,gO2))
coupR2 =  Conjg(cplcFdFucUHpR(i1,i2,gO2))
    SumI(gO1,gO2) = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
   End Do 
End Do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fv 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = Real(SA_DerGloop(p2,MFe2(i1),0._dp),dp) 
B0m2 = -2._dp*MFe(i1)*0._dp*Real(SA_DerB0(p2,MFe2(i1),0._dp),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coupL1 = cplcFeFvcUHpL(i1,i2,gO1)
coupR1 = cplcFeFvcUHpR(i1,i2,gO1)
coupL2 =  Conjg(cplcFeFvcUHpL(i1,i2,gO2))
coupR2 =  Conjg(cplcFeFvcUHpR(i1,i2,gO2))
    SumI(gO1,gO2) = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! VWp, G0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = DerFloopRXi(p2,MG02,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplG0cUHpVWp(gO1)
coup2 =  Conjg(cplG0cUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 = -Real(SA_DerB0(p2,MVWp2*RXi,MVZ2*RXi),dp) 
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcgZgWpcUHp(gO1)
coup2 =  cplcgWpgZUHp(gO2) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gZ 
!------------------------ 
sumI = 0._dp 
 
F0m2 = -Real(SA_DerB0(p2,MVZ2*RXi,MVWp2*RXi),dp) 
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcgWCgZcUHp(gO1)
coup2 =  cplcgZgWCUHp(gO2) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! Hp, H0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(SA_DerB0(p2,MHp2(i1),MH02),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplH0HpcUHp(i1,gO1)
coup2 = Conjg(cplH0HpcUHp(i1,gO2))
    SumI(gO1,gO2) = coup1*coup2*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, H0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = DerFloopRXi(p2,MH02,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplH0cUHpVWp(gO1)
coup2 =  Conjg(cplH0cUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! Hp, hh 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(SA_DerB0(p2,MHp2(i1),Mhh2),dp) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplhhHpcUHp(i1,gO1)
coup2 = Conjg(cplhhHpcUHp(i1,gO2))
    SumI(gO1,gO2) = coup1*coup2*B0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, hh 
!------------------------ 
sumI = 0._dp 
 
F0m2 = DerFloopRXi(p2,Mhh2,MVWp2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplhhcUHpVWp(gO1)
coup2 =  Conjg(cplhhcUHpVWp(gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! VP, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = DerFloopRXi(p2,MHp2(i2),MVP2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplHpcUHpVP(i2,gO1)
coup2 =  Conjg(cplHpcUHpVP(i2,gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VZ, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = DerFloopRXi(p2,MHp2(i2),MVZ2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplHpcUHpVZ(i2,gO1)
coup2 =  Conjg(cplHpcUHpVZ(i2,gO2))
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VWp, VP 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerSVVloop(p2,MVP2,MVWp2),dp)   
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcUHpVPVWp(gO1)
coup2 =  Conjg(cplcUHpVPVWp(gO2)) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! VZ, VWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerSVVloop(p2,MVWp2,MVZ2),dp)   
 Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplcUHpVWpVZ(gO1)
coup2 =  Conjg(cplcUHpVWpVZ(gO2)) 
    SumI(gO1,gO2) = coup1*coup2*F0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MA02) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplA0A0UHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MG02) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplG0G0UHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MH02) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplH0H0UHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(Mhh2) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplhhhhUHpcUHp(gO2,gO1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_DerA0(MHp2(i1)) 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpHpcUHpcHp(gO2,i1,gO1,i1)
    SumI(gO1,gO2) = -coup1*A0m2 
   End Do 
End Do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VP, VP 
!------------------------ 
sumI = 0._dp 
 
A0m2 = 0.75_dp*SA_DerA0(MVP2) + 0.25_dp*RXi*SA_DerA0(MVP2*RXi) - 0.5_dp*MVP2*DerrMS 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpcUHpVPVP(gO2,gO1)
    SumI(gO1,gO2) = coup1*A0m2 
   End Do 
End Do 
res = res +2._dp* SumI  
!------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 = 0.75_dp*SA_DerA0(MVWp2) + 0.25_dp*RXi*SA_DerA0(MVWp2*RXi) - 0.5_dp*MVWp2*DerrMS 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpcUHpcVWpVWp(gO2,gO1)
    SumI(gO1,gO2) = coup1*A0m2 
   End Do 
End Do 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 = 0.75_dp*SA_DerA0(MVZ2) + 0.25_dp*RXi*SA_DerA0(MVZ2*RXi) - 0.5_dp*MVZ2*DerrMS 
Do gO1 = 1, 2
  Do gO2 = gO1, 2
coup1 = cplUHpcUHpVZVZ(gO2,gO1)
    SumI(gO1,gO2) = coup1*A0m2 
   End Do 
End Do 
res = res +2._dp* SumI  


Do gO2 = 1, 2
  Do gO1 = gO2+1, 2
     res(gO1,gO2) = Conjg(res(gO2,gO1))  
   End Do 
End Do 
 
res = oo16pi2*res 
 
End Subroutine DerPi1LoopHp 
 
Subroutine OneLoopFd(Yd,v,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,               & 
& MFu,MFu2,MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,               & 
& cplcUFdFdVGL,cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,         & 
& cplcUFdFucHpL,cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,delta,MFd_1L,MFd2_1L,        & 
& ZDL_1L,ZDR_1L,ierr)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFd(3),MFd2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MFu(3),MFu2(3),              & 
& MVWp,MVWp2

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: Yd(3,3)

Complex(dp), Intent(in) :: cplcUFdFdG0L(3,3),cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),              & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),cplcUFdFucHpR(3,3,2),         & 
& cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3)

Complex(dp) :: mat1a(3,3), mat1(3,3) 
Integer , Intent(inout):: ierr 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi2(3), test_m2(3), p2 
Real(dp), Intent(out) :: MFd_1L(3),MFd2_1L(3) 
 Complex(dp), Intent(out) :: ZDL_1L(3,3), ZDR_1L(3,3) 
 
 Real(dp) :: MFd_t(3),MFd2_t(3) 
 Complex(dp) :: ZDL_t(3,3), ZDR_t(3,3), sigL(3,3), sigR(3,3), sigSL(3,3), sigSR(3,3) 
 
 Complex(dp) :: mat(3,3)=0._dp, mat2(3,3)=0._dp, phaseM 

Complex(dp) :: ZDL2(3,3), ZDR2(3,3) 
 
 Real(dp) :: ZDL1(3,3), ZDR1(3,3), test(2) 
 
 Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopMFd'
 
mat1a(1,1) = 0._dp 
mat1a(1,1) = mat1a(1,1)+(v*Yd(1,1))/sqrt(2._dp)
mat1a(1,2) = 0._dp 
mat1a(1,2) = mat1a(1,2)+(v*Yd(1,2))/sqrt(2._dp)
mat1a(1,3) = 0._dp 
mat1a(1,3) = mat1a(1,3)+(v*Yd(1,3))/sqrt(2._dp)
mat1a(2,1) = 0._dp 
mat1a(2,1) = mat1a(2,1)+(v*Yd(2,1))/sqrt(2._dp)
mat1a(2,2) = 0._dp 
mat1a(2,2) = mat1a(2,2)+(v*Yd(2,2))/sqrt(2._dp)
mat1a(2,3) = 0._dp 
mat1a(2,3) = mat1a(2,3)+(v*Yd(2,3))/sqrt(2._dp)
mat1a(3,1) = 0._dp 
mat1a(3,1) = mat1a(3,1)+(v*Yd(3,1))/sqrt(2._dp)
mat1a(3,2) = 0._dp 
mat1a(3,2) = mat1a(3,2)+(v*Yd(3,2))/sqrt(2._dp)
mat1a(3,3) = 0._dp 
mat1a(3,3) = mat1a(3,3)+(v*Yd(3,3))/sqrt(2._dp)

 
 !---------------------------------------- 
! Rotation matrix for p2=0 
!----------------------------------------- 
 
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = 0._dp 
Call Sigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,MFu2,           & 
& MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,           & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFd2_t,ZDR1,ierr,test) 
ZDR2 = ZDR1 
Else 
Call EigenSystem(mat2,MFd2_t,ZDR2,ierr,test) 
 End If 
 
ZDROS_0 = ZDR2 
 mat2 = Matmul(mat1,Transpose(Conjg(mat1))) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFd2_t,ZDL1,ierr,test) 
 
 
ZDL2 = ZDL1 
Else 
Call EigenSystem(mat2,MFd2_t,ZDL2,ierr,test) 
 
 
End If 
ZDL2 = Conjg(ZDL2) 
ZDLOS_0 = ZDL2 
 
!---------------------------------------- 
! Now, with momenta
!----------------------------------------- 
 
Do il=3,1,-1
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = MFd2(il) 
Call Sigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,MFu2,           & 
& MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,           & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFd2_t,ZDR1,ierr,test) 
ZDR2 = ZDR1 
Else 
Call EigenSystem(mat2,MFd2_t,ZDR2,ierr,test) 
 End If 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
!---------------------------------------- 
! Redoing Calculation using redefined p2 
!----------------------------------------- 
 
i_count = 0 
p2_loop: Do  
i_count = i_count + 1 
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = MFd2_t(iL)
Call Sigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,MFu2,           & 
& MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,           & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFd2_t,ZDR1,ierr,test) 
ZDR2 = ZDR1 
Else 
Call EigenSystem(mat2,MFd2_t,ZDR2,ierr,test) 
 End If 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
MFd2_1L(il) = MFd2_t(il) 
MFd_1L(il) = Sqrt(MFd2_1L(il)) 
 
If (p2.Ne.0._dp) Then 
  test(1) = Abs(MFd2_1L(il)-p2)/p2
Else 
  test(2) = Abs(MFd2_1L(il))
End If 
If (Abs(MFd2_1L(il)).lt.1.0E-30_dp) Exit p2_loop 
If (test(1).lt.0.1_dp*delta) Exit p2_loop 
If(i_count.gt.30) then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Exit p2_loop 
End if
End Do p2_loop 
mat2 = Matmul(mat1,Transpose(Conjg(mat1))) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFd2_t,ZDL1,ierr,test) 
 
 
ZDL2 = ZDL1 
Else 
Call EigenSystem(mat2,MFd2_t,ZDL2,ierr,test) 
 
 
End If 
ZDL2 = Conjg(ZDL2) 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
mat2 = Matmul(Matmul( Conjg(ZDL2),mat1),Transpose( Conjg(ZDR2))) 
Do i1=1,3
If (Abs(mat2(i1,i1)).gt.0._dp) Then 
phaseM = mat2(i1,i1) / Abs(mat2(i1,i1)) 
ZDR2(i1,:) = phaseM *ZDR2(i1,:) 
 End if 
End Do 
 
ZDLOS_p2(il,:) = ZDL2(il,:) 
 ZDROS_p2(il,:) = ZDR2(il,:) 
 ZDL_1L = ZDL2 
 ZDR_1L = ZDR2 
 End Do  
 
Iname = Iname -1 
End Subroutine OneLoopFd
 
 
Subroutine Sigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,              & 
& MFu,MFu2,MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,               & 
& cplcUFdFdVGL,cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,         & 
& cplcUFdFucHpL,cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFd(3),MFd2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MFu(3),MFu2(3),              & 
& MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFdFdG0L(3,3),cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),              & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),cplcUFdFucHpR(3,3,2),         & 
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
! G0, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFd2(i2),MG02),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),MG02),dp) 
coupL1 = cplcUFdFdG0L(gO1,i2)
coupR1 = cplcUFdFdG0R(gO1,i2)
coupL2 =  Conjg(cplcUFdFdG0L(gO2,i2))
coupR2 =  Conjg(cplcUFdFdG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFd2(i2),Mhh2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),Mhh2),dp) 
coupL1 = cplcUFdFdhhL(gO1,i2)
coupR1 = cplcUFdFdhhR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdhhL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdhhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VG, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFd2(i2),0._dp)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),0._dp)-0.5_dp*rMS,dp) 
coupL1 = cplcUFdFdVGL(gO1,i2)
coupR1 = cplcUFdFdVGR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVGL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVGR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +4._dp/3._dp* sumL
SigR = SigR +4._dp/3._dp* sumR 
SigSL = SigSL +4._dp/3._dp* sumSL 
SigSR = SigSR +4._dp/3._dp* sumSR 
    End Do 
 !------------------------ 
! VP, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFd2(i2),0._dp)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),0._dp)-0.5_dp*rMS,dp) 
coupL1 = cplcUFdFdVPL(gO1,i2)
coupR1 = cplcUFdFdVPR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVPL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVPR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFd2(i2),MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),MVZ2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFdFdVZL(gO1,i2)
coupR1 = cplcUFdFdVZR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVZL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! conj[Hp], Fu 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFu2(i2),MHp2(i1)),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),MHp2(i1)),dp) 
coupL1 = cplcUFdFucHpL(gO1,i2,i1)
coupR1 = cplcUFdFucHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFdFucHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFdFucHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFu2(i2),MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),MVWp2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFdFucVWpL(gO1,i2)
coupR1 = cplcUFdFucVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFdFucVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFdFucVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFd 
 
Subroutine DerSigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,           & 
& MFu,MFu2,MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,               & 
& cplcUFdFdVGL,cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,         & 
& cplcUFdFucHpL,cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFd(3),MFd2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MFu(3),MFu2(3),              & 
& MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFdFdG0L(3,3),cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),              & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),cplcUFdFucHpR(3,3,2),         & 
& cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! G0, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFd2(i2),MG02),dp) 
B0m2 = MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),MG02),dp) 
coupL1 = cplcUFdFdG0L(gO1,i2)
coupR1 = cplcUFdFdG0R(gO1,i2)
coupL2 =  Conjg(cplcUFdFdG0L(gO2,i2))
coupR2 =  Conjg(cplcUFdFdG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFd2(i2),Mhh2),dp) 
B0m2 = MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),Mhh2),dp) 
coupL1 = cplcUFdFdhhL(gO1,i2)
coupR1 = cplcUFdFdhhR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdhhL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdhhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VG, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFd2(i2),MVG2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),MVG2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFdFdVGL(gO1,i2)
coupR1 = cplcUFdFdVGR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVGL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVGR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +4._dp/3._dp* sumL
SigR = SigR +4._dp/3._dp* sumR 
SigSL = SigSL +4._dp/3._dp* sumSL 
SigSR = SigSR +4._dp/3._dp* sumSR 
    End Do 
 !------------------------ 
! VP, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFd2(i2),MVP2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),MVP2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFdFdVPL(gO1,i2)
coupR1 = cplcUFdFdVPR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVPL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVPR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFd2(i2),MVZ2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),MVZ2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFdFdVZL(gO1,i2)
coupR1 = cplcUFdFdVZR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVZL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! conj[Hp], Fu 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFu2(i2),MHp2(i1)),dp) 
B0m2 = MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),MHp2(i1)),dp) 
coupL1 = cplcUFdFucHpL(gO1,i2,i1)
coupR1 = cplcUFdFucHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFdFucHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFdFucHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFu2(i2),MVWp2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),MVWp2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFdFucVWpL(gO1,i2)
coupR1 = cplcUFdFucVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFdFucVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFdFucVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine DerSigma1LoopFd 
 
Subroutine OneLoopFu(Yu,v,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,             & 
& Mhh,Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,               & 
& cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,         & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,delta,MFu_1L,MFu2_1L,              & 
& ZUL_1L,ZUR_1L,ierr)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MFd(3),MFd2(3),MVWp,MVWp2,MG0,MG02,MFu(3),MFu2(3),Mhh,Mhh2,MVZ,MVZ2

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: Yu(3,3)

Complex(dp), Intent(in) :: cplcUFuFdHpL(3,3,2),cplcUFuFdHpR(3,3,2),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),        & 
& cplcUFuFuG0L(3,3),cplcUFuFuG0R(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),               & 
& cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),               & 
& cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3)

Complex(dp) :: mat1a(3,3), mat1(3,3) 
Integer , Intent(inout):: ierr 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi2(3), test_m2(3), p2 
Real(dp), Intent(out) :: MFu_1L(3),MFu2_1L(3) 
 Complex(dp), Intent(out) :: ZUL_1L(3,3), ZUR_1L(3,3) 
 
 Real(dp) :: MFu_t(3),MFu2_t(3) 
 Complex(dp) :: ZUL_t(3,3), ZUR_t(3,3), sigL(3,3), sigR(3,3), sigSL(3,3), sigSR(3,3) 
 
 Complex(dp) :: mat(3,3)=0._dp, mat2(3,3)=0._dp, phaseM 

Complex(dp) :: ZUL2(3,3), ZUR2(3,3) 
 
 Real(dp) :: ZUL1(3,3), ZUR1(3,3), test(2) 
 
 Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopMFu'
 
mat1a(1,1) = 0._dp 
mat1a(1,1) = mat1a(1,1)-((v*Yu(1,1))/sqrt(2._dp))
mat1a(1,2) = 0._dp 
mat1a(1,2) = mat1a(1,2)-((v*Yu(1,2))/sqrt(2._dp))
mat1a(1,3) = 0._dp 
mat1a(1,3) = mat1a(1,3)-((v*Yu(1,3))/sqrt(2._dp))
mat1a(2,1) = 0._dp 
mat1a(2,1) = mat1a(2,1)-((v*Yu(2,1))/sqrt(2._dp))
mat1a(2,2) = 0._dp 
mat1a(2,2) = mat1a(2,2)-((v*Yu(2,2))/sqrt(2._dp))
mat1a(2,3) = 0._dp 
mat1a(2,3) = mat1a(2,3)-((v*Yu(2,3))/sqrt(2._dp))
mat1a(3,1) = 0._dp 
mat1a(3,1) = mat1a(3,1)-((v*Yu(3,1))/sqrt(2._dp))
mat1a(3,2) = 0._dp 
mat1a(3,2) = mat1a(3,2)-((v*Yu(3,2))/sqrt(2._dp))
mat1a(3,3) = 0._dp 
mat1a(3,3) = mat1a(3,3)-((v*Yu(3,3))/sqrt(2._dp))

 
 !---------------------------------------- 
! Rotation matrix for p2=0 
!----------------------------------------- 
 
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = 0._dp 
Call Sigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,Mhh,              & 
& Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,cplcUFuFuG0L,      & 
& cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,         & 
& cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFu2_t,ZUR1,ierr,test) 
ZUR2 = ZUR1 
Else 
Call EigenSystem(mat2,MFu2_t,ZUR2,ierr,test) 
 End If 
 
ZUROS_0 = ZUR2 
 mat2 = Matmul(mat1,Transpose(Conjg(mat1))) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFu2_t,ZUL1,ierr,test) 
 
 
ZUL2 = ZUL1 
Else 
Call EigenSystem(mat2,MFu2_t,ZUL2,ierr,test) 
 
 
End If 
ZUL2 = Conjg(ZUL2) 
ZULOS_0 = ZUL2 
 
!---------------------------------------- 
! Now, with momenta
!----------------------------------------- 
 
Do il=3,1,-1
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = MFu2(il) 
Call Sigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,Mhh,              & 
& Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,cplcUFuFuG0L,      & 
& cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,         & 
& cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFu2_t,ZUR1,ierr,test) 
ZUR2 = ZUR1 
Else 
Call EigenSystem(mat2,MFu2_t,ZUR2,ierr,test) 
 End If 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
!---------------------------------------- 
! Redoing Calculation using redefined p2 
!----------------------------------------- 
 
i_count = 0 
p2_loop: Do  
i_count = i_count + 1 
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = MFu2_t(iL)
Call Sigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,Mhh,              & 
& Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,cplcUFuFuG0L,      & 
& cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,         & 
& cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFu2_t,ZUR1,ierr,test) 
ZUR2 = ZUR1 
Else 
Call EigenSystem(mat2,MFu2_t,ZUR2,ierr,test) 
 End If 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
MFu2_1L(il) = MFu2_t(il) 
MFu_1L(il) = Sqrt(MFu2_1L(il)) 
 
If (p2.Ne.0._dp) Then 
  test(1) = Abs(MFu2_1L(il)-p2)/p2
Else 
  test(2) = Abs(MFu2_1L(il))
End If 
If (Abs(MFu2_1L(il)).lt.1.0E-30_dp) Exit p2_loop 
If (test(1).lt.0.1_dp*delta) Exit p2_loop 
If(i_count.gt.30) then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Exit p2_loop 
End if
End Do p2_loop 
mat2 = Matmul(mat1,Transpose(Conjg(mat1))) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFu2_t,ZUL1,ierr,test) 
 
 
ZUL2 = ZUL1 
Else 
Call EigenSystem(mat2,MFu2_t,ZUL2,ierr,test) 
 
 
End If 
ZUL2 = Conjg(ZUL2) 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
mat2 = Matmul(Matmul( Conjg(ZUL2),mat1),Transpose( Conjg(ZUR2))) 
Do i1=1,3
If (Abs(mat2(i1,i1)).gt.0._dp) Then 
phaseM = mat2(i1,i1) / Abs(mat2(i1,i1)) 
ZUR2(i1,:) = phaseM *ZUR2(i1,:) 
 End if 
End Do 
 
ZULOS_p2(il,:) = ZUL2(il,:) 
 ZUROS_p2(il,:) = ZUR2(il,:) 
 ZUL_1L = ZUL2 
 ZUR_1L = ZUR2 
 End Do  
 
Iname = Iname -1 
End Subroutine OneLoopFu
 
 
Subroutine Sigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,            & 
& Mhh,Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,               & 
& cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,         & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MFd(3),MFd2(3),MVWp,MVWp2,MG0,MG02,MFu(3),MFu2(3),Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcUFuFdHpL(3,3,2),cplcUFuFdHpR(3,3,2),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),        & 
& cplcUFuFuG0L(3,3),cplcUFuFuG0R(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),               & 
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
! Hp, Fd 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFd2(i2),MHp2(i1)),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),MHp2(i1)),dp) 
coupL1 = cplcUFuFdHpL(gO1,i2,i1)
coupR1 = cplcUFuFdHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFuFdHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFuFdHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! VWp, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFd2(i2),MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),MVWp2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFuFdVWpL(gO1,i2)
coupR1 = cplcUFuFdVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFuFdVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFuFdVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! G0, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFu2(i2),MG02),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),MG02),dp) 
coupL1 = cplcUFuFuG0L(gO1,i2)
coupR1 = cplcUFuFuG0R(gO1,i2)
coupL2 =  Conjg(cplcUFuFuG0L(gO2,i2))
coupR2 =  Conjg(cplcUFuFuG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFu2(i2),Mhh2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),Mhh2),dp) 
coupL1 = cplcUFuFuhhL(gO1,i2)
coupR1 = cplcUFuFuhhR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuhhL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuhhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VG, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFu2(i2),0._dp)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),0._dp)-0.5_dp*rMS,dp) 
coupL1 = cplcUFuFuVGL(gO1,i2)
coupR1 = cplcUFuFuVGR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVGL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVGR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +4._dp/3._dp* sumL
SigR = SigR +4._dp/3._dp* sumR 
SigSL = SigSL +4._dp/3._dp* sumSL 
SigSR = SigSR +4._dp/3._dp* sumSR 
    End Do 
 !------------------------ 
! VP, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFu2(i2),0._dp)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),0._dp)-0.5_dp*rMS,dp) 
coupL1 = cplcUFuFuVPL(gO1,i2)
coupR1 = cplcUFuFuVPR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVPL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVPR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFu2(i2),MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),MVZ2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFuFuVZL(gO1,i2)
coupR1 = cplcUFuFuVZR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVZL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFu 
 
Subroutine DerSigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,              & 
& MFu2,Mhh,Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,          & 
& cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,         & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MFd(3),MFd2(3),MVWp,MVWp2,MG0,MG02,MFu(3),MFu2(3),Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcUFuFdHpL(3,3,2),cplcUFuFdHpR(3,3,2),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),        & 
& cplcUFuFuG0L(3,3),cplcUFuFuG0R(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),               & 
& cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),               & 
& cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! Hp, Fd 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFd2(i2),MHp2(i1)),dp) 
B0m2 = MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),MHp2(i1)),dp) 
coupL1 = cplcUFuFdHpL(gO1,i2,i1)
coupR1 = cplcUFuFdHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFuFdHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFuFdHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! VWp, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFd2(i2),MVWp2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_DerB0(p2,MFd2(i2),MVWp2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFuFdVWpL(gO1,i2)
coupR1 = cplcUFuFdVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFuFdVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFuFdVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! G0, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFu2(i2),MG02),dp) 
B0m2 = MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),MG02),dp) 
coupL1 = cplcUFuFuG0L(gO1,i2)
coupR1 = cplcUFuFuG0R(gO1,i2)
coupL2 =  Conjg(cplcUFuFuG0L(gO2,i2))
coupR2 =  Conjg(cplcUFuFuG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFu2(i2),Mhh2),dp) 
B0m2 = MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),Mhh2),dp) 
coupL1 = cplcUFuFuhhL(gO1,i2)
coupR1 = cplcUFuFuhhR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuhhL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuhhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VG, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFu2(i2),MVG2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),MVG2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFuFuVGL(gO1,i2)
coupR1 = cplcUFuFuVGR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVGL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVGR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +4._dp/3._dp* sumL
SigR = SigR +4._dp/3._dp* sumR 
SigSL = SigSL +4._dp/3._dp* sumSL 
SigSR = SigSR +4._dp/3._dp* sumSR 
    End Do 
 !------------------------ 
! VP, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFu2(i2),MVP2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),MVP2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFuFuVPL(gO1,i2)
coupR1 = cplcUFuFuVPR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVPL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVPR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFu2(i2),MVZ2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_DerB0(p2,MFu2(i2),MVZ2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFuFuVZL(gO1,i2)
coupR1 = cplcUFuFuVZR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVZL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine DerSigma1LoopFu 
 
Subroutine OneLoopFe(Ye,v,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,               & 
& MVWp,MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,           & 
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,     & 
& cplcUFeFvcVWpR,delta,MFe_1L,MFe2_1L,ZEL_1L,ZER_1L,ierr)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFe(3),MFe2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: Ye(3,3)

Complex(dp), Intent(in) :: cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),              & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3)

Complex(dp) :: mat1a(3,3), mat1(3,3) 
Integer , Intent(inout):: ierr 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi2(3), test_m2(3), p2 
Real(dp), Intent(out) :: MFe_1L(3),MFe2_1L(3) 
 Complex(dp), Intent(out) :: ZEL_1L(3,3), ZER_1L(3,3) 
 
 Real(dp) :: MFe_t(3),MFe2_t(3) 
 Complex(dp) :: ZEL_t(3,3), ZER_t(3,3), sigL(3,3), sigR(3,3), sigSL(3,3), sigSR(3,3) 
 
 Complex(dp) :: mat(3,3)=0._dp, mat2(3,3)=0._dp, phaseM 

Complex(dp) :: ZEL2(3,3), ZER2(3,3) 
 
 Real(dp) :: ZEL1(3,3), ZER1(3,3), test(2) 
 
 Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopMFe'
 
mat1a(1,1) = 0._dp 
mat1a(1,1) = mat1a(1,1)+(v*Ye(1,1))/sqrt(2._dp)
mat1a(1,2) = 0._dp 
mat1a(1,2) = mat1a(1,2)+(v*Ye(1,2))/sqrt(2._dp)
mat1a(1,3) = 0._dp 
mat1a(1,3) = mat1a(1,3)+(v*Ye(1,3))/sqrt(2._dp)
mat1a(2,1) = 0._dp 
mat1a(2,1) = mat1a(2,1)+(v*Ye(2,1))/sqrt(2._dp)
mat1a(2,2) = 0._dp 
mat1a(2,2) = mat1a(2,2)+(v*Ye(2,2))/sqrt(2._dp)
mat1a(2,3) = 0._dp 
mat1a(2,3) = mat1a(2,3)+(v*Ye(2,3))/sqrt(2._dp)
mat1a(3,1) = 0._dp 
mat1a(3,1) = mat1a(3,1)+(v*Ye(3,1))/sqrt(2._dp)
mat1a(3,2) = 0._dp 
mat1a(3,2) = mat1a(3,2)+(v*Ye(3,2))/sqrt(2._dp)
mat1a(3,3) = 0._dp 
mat1a(3,3) = mat1a(3,3)+(v*Ye(3,3))/sqrt(2._dp)

 
 !---------------------------------------- 
! Rotation matrix for p2=0 
!----------------------------------------- 
 
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = 0._dp 
Call Sigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,               & 
& MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,   & 
& cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,   & 
& sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFe2_t,ZER1,ierr,test) 
ZER2 = ZER1 
Else 
Call EigenSystem(mat2,MFe2_t,ZER2,ierr,test) 
 End If 
 
ZEROS_0 = ZER2 
 mat2 = Matmul(mat1,Transpose(Conjg(mat1))) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFe2_t,ZEL1,ierr,test) 
 
 
ZEL2 = ZEL1 
Else 
Call EigenSystem(mat2,MFe2_t,ZEL2,ierr,test) 
 
 
End If 
ZEL2 = Conjg(ZEL2) 
ZELOS_0 = ZEL2 
 
!---------------------------------------- 
! Now, with momenta
!----------------------------------------- 
 
Do il=3,1,-1
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = MFe2(il) 
Call Sigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,               & 
& MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,   & 
& cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,   & 
& sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFe2_t,ZER1,ierr,test) 
ZER2 = ZER1 
Else 
Call EigenSystem(mat2,MFe2_t,ZER2,ierr,test) 
 End If 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
!---------------------------------------- 
! Redoing Calculation using redefined p2 
!----------------------------------------- 
 
i_count = 0 
p2_loop: Do  
i_count = i_count + 1 
sigL=0._dp 
sigR=0._dp 
sigSL=0._dp 
sigSR=0._dp 
p2 = MFe2_t(iL)
Call Sigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,               & 
& MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,   & 
& cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,   & 
& sigL,sigR,sigSL,sigSR)

mat1 = mat1a - SigSL - 0.5_dp*(MatMul(SigR,mat1a) + MatMul(mat1a,SigL)) 
 
mat2 = Matmul(Transpose(Conjg(mat1)),mat1) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFe2_t,ZER1,ierr,test) 
ZER2 = ZER1 
Else 
Call EigenSystem(mat2,MFe2_t,ZER2,ierr,test) 
 End If 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
MFe2_1L(il) = MFe2_t(il) 
MFe_1L(il) = Sqrt(MFe2_1L(il)) 
 
If (p2.Ne.0._dp) Then 
  test(1) = Abs(MFe2_1L(il)-p2)/p2
Else 
  test(2) = Abs(MFe2_1L(il))
End If 
If (Abs(MFe2_1L(il)).lt.1.0E-30_dp) Exit p2_loop 
If (test(1).lt.0.1_dp*delta) Exit p2_loop 
If(i_count.gt.30) then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Exit p2_loop 
End if
End Do p2_loop 
mat2 = Matmul(mat1,Transpose(Conjg(mat1))) 
If (ForceRealMatrices) mat2 = Real(mat2,dp) 
If (Maxval(Abs(Aimag(mat2))).Eq.0._dp) Then 
Call EigenSystem(Real(mat2,dp),MFe2_t,ZEL1,ierr,test) 
 
 
ZEL2 = ZEL1 
Else 
Call EigenSystem(mat2,MFe2_t,ZEL2,ierr,test) 
 
 
End If 
ZEL2 = Conjg(ZEL2) 
 
If ((ierr.Eq.-8).Or.(ierr.Eq.-9)) Then 
  Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  Write(*,*) "Possible numerical problem in "//NameOfUnit(Iname) 
  If (ErrorLevel.Eq.2) Call TerminateProgram 
  ierr = 0 
End If 
 
mat2 = Matmul(Matmul( Conjg(ZEL2),mat1),Transpose( Conjg(ZER2))) 
Do i1=1,3
If (Abs(mat2(i1,i1)).gt.0._dp) Then 
phaseM = mat2(i1,i1) / Abs(mat2(i1,i1)) 
ZER2(i1,:) = phaseM *ZER2(i1,:) 
 End if 
End Do 
 
ZELOS_p2(il,:) = ZEL2(il,:) 
 ZEROS_p2(il,:) = ZER2(il,:) 
 ZEL_1L = ZEL2 
 ZER_1L = ZER2 
 End Do  
 
Iname = Iname -1 
End Subroutine OneLoopFe
 
 
Subroutine Sigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,              & 
& MVWp,MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,           & 
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,     & 
& cplcUFeFvcVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFe(3),MFe2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),              & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3)

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
! G0, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFe2(i2),MG02),dp) 
B0m2 = MFe(i2)*Real(SA_B0(p2,MFe2(i2),MG02),dp) 
coupL1 = cplcUFeFeG0L(gO1,i2)
coupR1 = cplcUFeFeG0R(gO1,i2)
coupL2 =  Conjg(cplcUFeFeG0L(gO2,i2))
coupR2 =  Conjg(cplcUFeFeG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFe2(i2),Mhh2),dp) 
B0m2 = MFe(i2)*Real(SA_B0(p2,MFe2(i2),Mhh2),dp) 
coupL1 = cplcUFeFehhL(gO1,i2)
coupR1 = cplcUFeFehhR(gO1,i2)
coupL2 =  Conjg(cplcUFeFehhL(gO2,i2))
coupR2 =  Conjg(cplcUFeFehhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VP, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFe2(i2),0._dp)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(p2,MFe2(i2),0._dp)-0.5_dp*rMS,dp) 
coupL1 = cplcUFeFeVPL(gO1,i2)
coupR1 = cplcUFeFeVPR(gO1,i2)
coupL2 =  Conjg(cplcUFeFeVPL(gO2,i2))
coupR2 =  Conjg(cplcUFeFeVPR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFe2(i2),MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(p2,MFe2(i2),MVZ2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFeFeVZL(gO1,i2)
coupR1 = cplcUFeFeVZR(gO1,i2)
coupL2 =  Conjg(cplcUFeFeVZL(gO2,i2))
coupR2 =  Conjg(cplcUFeFeVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! conj[Hp], Fv 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,0._dp,MHp2(i1)),dp) 
B0m2 = 0._dp*Real(SA_B0(p2,0._dp,MHp2(i1)),dp) 
coupL1 = cplcUFeFvcHpL(gO1,i2,i1)
coupR1 = cplcUFeFvcHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFeFvcHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFeFvcHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Fv 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,0._dp,MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*0._dp*Real(SA_B0(p2,0._dp,MVWp2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFeFvcVWpL(gO1,i2)
coupR1 = cplcUFeFvcVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFeFvcVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFeFvcVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFe 
 
Subroutine DerSigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,           & 
& MVWp,MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,           & 
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,     & 
& cplcUFeFvcVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFe(3),MFe2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),              & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! G0, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFe2(i2),MG02),dp) 
B0m2 = MFe(i2)*Real(SA_DerB0(p2,MFe2(i2),MG02),dp) 
coupL1 = cplcUFeFeG0L(gO1,i2)
coupR1 = cplcUFeFeG0R(gO1,i2)
coupL2 =  Conjg(cplcUFeFeG0L(gO2,i2))
coupR2 =  Conjg(cplcUFeFeG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFe2(i2),Mhh2),dp) 
B0m2 = MFe(i2)*Real(SA_DerB0(p2,MFe2(i2),Mhh2),dp) 
coupL1 = cplcUFeFehhL(gO1,i2)
coupR1 = cplcUFeFehhR(gO1,i2)
coupL2 =  Conjg(cplcUFeFehhL(gO2,i2))
coupR2 =  Conjg(cplcUFeFehhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VP, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFe2(i2),MVP2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_DerB0(p2,MFe2(i2),MVP2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFeFeVPL(gO1,i2)
coupR1 = cplcUFeFeVPR(gO1,i2)
coupL2 =  Conjg(cplcUFeFeVPL(gO2,i2))
coupR2 =  Conjg(cplcUFeFeVPR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFe2(i2),MVZ2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_DerB0(p2,MFe2(i2),MVZ2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFeFeVZL(gO1,i2)
coupR1 = cplcUFeFeVZR(gO1,i2)
coupL2 =  Conjg(cplcUFeFeVZL(gO2,i2))
coupR2 =  Conjg(cplcUFeFeVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! conj[Hp], Fv 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,0._dp,MHp2(i1)),dp) 
B0m2 = 0._dp*Real(SA_DerB0(p2,0._dp,MHp2(i1)),dp) 
coupL1 = cplcUFeFvcHpL(gO1,i2,i1)
coupR1 = cplcUFeFvcHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFeFvcHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFeFvcHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Fv 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,0._dp,MVWp2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*0._dp*Real(SA_DerB0(p2,0._dp,MVWp2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFeFvcVWpL(gO1,i2)
coupR1 = cplcUFeFvcVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFeFvcVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFeFvcVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine DerSigma1LoopFe 
 
Subroutine Sigma1LoopFv(p2,MHp,MHp2,MFe,MFe2,MVWp,MVWp2,MVZ,MVZ2,cplcUFvFeHpL,        & 
& cplcUFvFeHpR,cplcUFvFeVWpL,cplcUFvFeVWpR,cplcUFvFvVZL,cplcUFvFvVZR,sigL,               & 
& sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MFe(3),MFe2(3),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcUFvFeHpL(3,3,2),cplcUFvFeHpR(3,3,2),cplcUFvFeVWpL(3,3),cplcUFvFeVWpR(3,3),        & 
& cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3)

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
! Hp, Fe 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_B1(p2,MFe2(i2),MHp2(i1)),dp) 
B0m2 = MFe(i2)*Real(SA_B0(p2,MFe2(i2),MHp2(i1)),dp) 
coupL1 = cplcUFvFeHpL(gO1,i2,i1)
coupR1 = cplcUFvFeHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFvFeHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFvFeHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! VWp, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,MFe2(i2),MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(p2,MFe2(i2),MVWp2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFvFeVWpL(gO1,i2)
coupR1 = cplcUFvFeVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFvFeVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFvFeVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fv 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_B1(p2,0._dp,MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*0._dp*Real(SA_B0(p2,0._dp,MVZ2)-0.5_dp*rMS,dp) 
coupL1 = cplcUFvFvVZL(gO1,i2)
coupR1 = cplcUFvFvVZR(gO1,i2)
coupL2 =  Conjg(cplcUFvFvVZL(gO2,i2))
coupR2 =  Conjg(cplcUFvFvVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFv 
 
Subroutine DerSigma1LoopFv(p2,MHp,MHp2,MFe,MFe2,MVWp,MVWp2,MVZ,MVZ2,cplcUFvFeHpL,     & 
& cplcUFvFeHpR,cplcUFvFeVWpL,cplcUFvFeVWpR,cplcUFvFvVZL,cplcUFvFvVZR,sigL,               & 
& sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MFe(3),MFe2(3),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcUFvFeHpL(3,3,2),cplcUFvFeHpR(3,3,2),cplcUFvFeVWpL(3,3),cplcUFvFeVWpR(3,3),        & 
& cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3)

Complex(dp), Intent(out) :: SigL(3,3),SigR(3,3), SigSL(3,3), SigSR(3,3) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumL(3,3), sumR(3,3), sumSL(3,3), sumSR(3,3) 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

SigL = Cmplx(0._dp,0._dp,dp) 
SigR = Cmplx(0._dp,0._dp,dp) 
SigSL = Cmplx(0._dp,0._dp,dp) 
 SigSR = Cmplx(0._dp,0._dp,dp) 
 
!------------------------ 
! Hp, Fe 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -Real(SA_DerB1(p2,MFe2(i2),MHp2(i1)),dp) 
B0m2 = MFe(i2)*Real(SA_DerB0(p2,MFe2(i2),MHp2(i1)),dp) 
coupL1 = cplcUFvFeHpL(gO1,i2,i1)
coupR1 = cplcUFvFeHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFvFeHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFvFeHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! VWp, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,MFe2(i2),MVWp2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_DerB0(p2,MFe2(i2),MVWp2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFvFeVWpL(gO1,i2)
coupR1 = cplcUFvFeVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFvFeVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFvFeVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fv 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
B1m2 = -2._dp*Real(SA_DerB1(p2,0._dp,MVZ2)+ 0.5_dp*DerrMS,dp) 
B0m2 = -4._dp*0._dp*Real(SA_DerB0(p2,0._dp,MVZ2)-0.5_dp*DerrMS,dp) 
coupL1 = cplcUFvFvVZL(gO1,i2)
coupR1 = cplcUFvFvVZR(gO1,i2)
coupL2 =  Conjg(cplcUFvFvVZL(gO2,i2))
coupR2 =  Conjg(cplcUFvFvVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine DerSigma1LoopFv 
 
Subroutine OneLoopG0(g1,g2,MHD2,lam1,v,TW,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,             & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,      & 
& cplcFdFdG0L,cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,       & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,           & 
& delta,mass,mass2,kont)

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp(2),MHp2(2)

Real(dp), Intent(in) :: g1,g2,MHD2,v,TW

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFeFeG0L(3,3),               & 
& cplcFeFeG0R(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplG0G0hh,cplcgWpgWpG0,             & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplA0A0G0G0,cplG0G0G0G0,               & 
& cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0G0cVWpVWp,cplG0G0VZVZ

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopG0'
 
mi2 = (2*(2._dp*(MHD2) + lam1*v**2) + v**2*RXiZ*(g2*Cos(TW) + g1*Sin(TW))**2)/4._dp 

 
p2 = 0._dp 
PiSf = ZeroC 
Call Pi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,   & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,       & 
& cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,PiSf)

PiSf=PiSf- real(pip2s_effpot(1,1),dp)
mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,   & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,       & 
& cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,PiSf)

PiSf=PiSf- real(pip2s_effpot(1,1),dp)
mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
   If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
   End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
   SignOfMassChanged = .True. 
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
End Subroutine OneLoopG0
 
 
Subroutine Pi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,             & 
& Mhh2,MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,            & 
& cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,    & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,      & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFeFeG0L(3,3),               & 
& cplcFeFeG0R(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplG0G0hh,cplcgWpgWpG0,             & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplA0A0G0G0,cplG0G0G0G0,               & 
& cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0G0cVWpVWp,cplG0G0VZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
res = 0._dp 
 
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MA02,MA02),dp) 
coup1 = cplA0A0G0
coup2 = Conjg(cplA0A0G0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MH02,MA02),dp) 
coup1 = cplA0G0H0
coup2 = Conjg(cplA0G0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_Gloop(p2,MFd2(i1),MFd2(i2)) 
B0m2 = -2._dp*MFd(i1)*MFd(i2)*SA_B0(p2,MFd2(i1),MFd2(i2)) 
coupL1 = cplcFdFdG0L(i1,i2)
coupR1 = cplcFdFdG0R(i1,i2)
coupL2 =  Conjg(cplcFdFdG0L(i1,i2))
coupR2 =  Conjg(cplcFdFdG0R(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_Gloop(p2,MFe2(i1),MFe2(i2)) 
B0m2 = -2._dp*MFe(i1)*MFe(i2)*SA_B0(p2,MFe2(i1),MFe2(i2)) 
coupL1 = cplcFeFeG0L(i1,i2)
coupR1 = cplcFeFeG0R(i1,i2)
coupL2 =  Conjg(cplcFeFeG0L(i1,i2))
coupR2 =  Conjg(cplcFeFeG0R(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_Gloop(p2,MFu2(i1),MFu2(i2)) 
B0m2 = -2._dp*MFu(i1)*MFu(i2)*SA_B0(p2,MFu2(i1),MFu2(i2)) 
coupL1 = cplcFuFuG0L(i1,i2)
coupR1 = cplcFuFuG0R(i1,i2)
coupL2 =  Conjg(cplcFuFuG0L(i1,i2))
coupR2 =  Conjg(cplcFuFuG0R(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! hh, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,Mhh2,MG02),dp) 
coup1 = cplG0G0hh
coup2 = Conjg(cplG0G0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_B0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWpgWpG0
coup2 =  cplcgWpgWpG0 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_B0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWCgWCG0
coup2 =  cplcgWCgWCG0 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MH02,MH02),dp) 
coup1 = cplG0H0H0
coup2 = Conjg(cplG0H0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! VZ, hh 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(FloopRXi(p2,Mhh2,MVZ2),dp) 
coup1 = cplG0hhVZ
coup2 =  Conjg(cplG0hhVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(FloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplG0HpcVWp(i2)
coup2 =  Conjg(cplG0HpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MA02) 
coup1 = cplA0A0G0G0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MG02) 
coup1 = cplG0G0G0G0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MH02) 
coup1 = cplG0G0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(Mhh2) 
coup1 = cplG0G0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_A0(MHp2(i1)) 
coup1 = cplG0G0HpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVWp2) + 0.25_dp*RXi*SA_A0(MVWp2*RXi) - 0.5_dp*MVWp2*rMS 
coup1 = cplG0G0cVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVZ2) + 0.25_dp*RXi*SA_A0(MVZ2*RXi) - 0.5_dp*MVZ2*rMS 
coup1 = cplG0G0VZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine Pi1LoopG0 
 
Subroutine DerPi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,              & 
& Mhh,Mhh2,MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,        & 
& cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,    & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,      & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplA0A0G0,cplA0G0H0,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFeFeG0L(3,3),               & 
& cplcFeFeG0R(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplG0G0hh,cplcgWpgWpG0,             & 
& cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp(2),cplA0A0G0G0,cplG0G0G0G0,               & 
& cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0G0cVWpVWp,cplG0G0VZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MA02,MA02),dp) 
coup1 = cplA0A0G0
coup2 = Conjg(cplA0A0G0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MH02,MA02),dp) 
coup1 = cplA0G0H0
coup2 = Conjg(cplA0G0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_DerGloop(p2,MFd2(i1),MFd2(i2)) 
B0m2 = -2._dp*MFd(i1)*MFd(i2)*SA_DerB0(p2,MFd2(i1),MFd2(i2)) 
coupL1 = cplcFdFdG0L(i1,i2)
coupR1 = cplcFdFdG0R(i1,i2)
coupL2 =  Conjg(cplcFdFdG0L(i1,i2))
coupR2 =  Conjg(cplcFdFdG0R(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_DerGloop(p2,MFe2(i1),MFe2(i2)) 
B0m2 = -2._dp*MFe(i1)*MFe(i2)*SA_DerB0(p2,MFe2(i1),MFe2(i2)) 
coupL1 = cplcFeFeG0L(i1,i2)
coupR1 = cplcFeFeG0R(i1,i2)
coupL2 =  Conjg(cplcFeFeG0L(i1,i2))
coupR2 =  Conjg(cplcFeFeG0R(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_DerGloop(p2,MFu2(i1),MFu2(i2)) 
B0m2 = -2._dp*MFu(i1)*MFu(i2)*SA_DerB0(p2,MFu2(i1),MFu2(i2)) 
coupL1 = cplcFuFuG0L(i1,i2)
coupR1 = cplcFuFuG0R(i1,i2)
coupL2 =  Conjg(cplcFuFuG0L(i1,i2))
coupR2 =  Conjg(cplcFuFuG0R(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! hh, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,Mhh2,MG02),dp) 
coup1 = cplG0G0hh
coup2 = Conjg(cplG0G0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_DerB0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWpgWpG0
coup2 =  cplcgWpgWpG0 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_DerB0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWCgWCG0
coup2 =  cplcgWCgWCG0 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MH02,MH02),dp) 
coup1 = cplG0H0H0
coup2 = Conjg(cplG0H0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! VZ, hh 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerFloopRXi(p2,Mhh2,MVZ2),dp) 
coup1 = cplG0hhVZ
coup2 =  Conjg(cplG0hhVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(DerFloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplG0HpcVWp(i2)
coup2 =  Conjg(cplG0HpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MA02) 
coup1 = cplA0A0G0G0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MG02) 
coup1 = cplG0G0G0G0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MH02) 
coup1 = cplG0G0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(Mhh2) 
coup1 = cplG0G0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_DerA0(MHp2(i1)) 
coup1 = cplG0G0HpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVWp2) + 0.25_dp*RXi*SA_DerA0(MVWp2*RXi) - 0.5_dp*MVWp2*DerrMS 
coup1 = cplG0G0cVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVZ2) + 0.25_dp*RXi*SA_DerA0(MVZ2*RXi) - 0.5_dp*MVZ2*DerrMS 
coup1 = cplG0G0VZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine DerPi1LoopG0 
 
Subroutine OneLoophh(MHD2,lam1,v,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,             & 
& MFu2,MG0,MG02,MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,          & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,     & 
& cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,delta,mass,mass2,kont)

Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,              & 
& MVZ,MVZ2,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2

Real(dp), Intent(in) :: MHD2,v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,   & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp(2,2),& 
& cplhhhhcVWpVWp,cplhhhhVZVZ

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoophh'
 
mi2 = MHD2 + (3*lam1*v**2)/2._dp 

 
p2 = Mhh2
PiSf = ZeroC 
Call Pi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,              & 
& MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,       & 
& cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp, & 
& cplhhhhVZVZ,kont,PiSf)

PiSf=PiSf- real(pi2s_effpot(1,1),dp)
mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,              & 
& MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,       & 
& cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp, & 
& cplhhhhVZVZ,kont,PiSf)

PiSf=PiSf- real(pi2s_effpot(1,1),dp)
mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
   If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
   End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
   SignOfMassChanged = .True. 
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
End Subroutine OneLoophh
 
 
Subroutine Pi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,             & 
& MG02,MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,       & 
& cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,       & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,   & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,              & 
& MVZ,MVZ2,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,   & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp(2,2),& 
& cplhhhhcVWpVWp,cplhhhhVZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
res = 0._dp 
 
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MA02,MA02),dp) 
coup1 = cplA0A0hh
coup2 = Conjg(cplA0A0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MH02,MA02),dp) 
coup1 = cplA0H0hh
coup2 = Conjg(cplA0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
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
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
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
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
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
 !------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MG02,MG02),dp) 
coup1 = cplG0G0hh
coup2 = Conjg(cplG0G0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! VZ, G0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(FloopRXi(p2,MG02,MVZ2),dp) 
coup1 = cplG0hhVZ
coup2 =  Conjg(cplG0hhVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_B0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWpgWphh
coup2 =  cplcgWpgWphh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_B0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWCgWChh
coup2 =  cplcgWCgWChh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gZ 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_B0(p2,MVZ2*RXi,MVZ2*RXi),dp) 
 coup1 = cplcgZgZhh
coup2 =  cplcgZgZhh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MH02,MH02),dp) 
coup1 = cplH0H0hh
coup2 = Conjg(cplH0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,Mhh2,Mhh2),dp) 
coup1 = cplhhhhhh
coup2 = Conjg(cplhhhhhh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B0m2 = Real(SA_B0(p2,MHp2(i1),MHp2(i2)),dp) 
coup1 = cplhhHpcHp(i2,i1)
coup2 = Conjg(cplhhHpcHp(i2,i1))
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(FloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplhhHpcVWp(i2)
coup2 =  Conjg(cplhhHpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(SVVloop(p2,MVWp2,MVWp2),dp) 
coup1 = cplhhcVWpVWp
coup2 =  Conjg(cplhhcVWpVWp)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(SVVloop(p2,MVZ2,MVZ2),dp) 
coup1 = cplhhVZVZ
coup2 =  Conjg(cplhhVZVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MA02) 
coup1 = cplA0A0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MG02) 
coup1 = cplG0G0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MH02) 
coup1 = cplH0H0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(Mhh2) 
coup1 = cplhhhhhhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_A0(MHp2(i1)) 
coup1 = cplhhhhHpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVWp2) + 0.25_dp*RXi*SA_A0(MVWp2*RXi) - 0.5_dp*MVWp2*rMS 
coup1 = cplhhhhcVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVZ2) + 0.25_dp*RXi*SA_A0(MVZ2*RXi) - 0.5_dp*MVZ2*rMS 
coup1 = cplhhhhVZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine Pi1Loophh 
 
Subroutine DerPi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,              & 
& MG0,MG02,MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,       & 
& cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,       & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,   & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MH0,MH02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,              & 
& MVZ,MVZ2,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),               & 
& cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,   & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp(2,2),& 
& cplhhhhcVWpVWp,cplhhhhVZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MA02,MA02),dp) 
coup1 = cplA0A0hh
coup2 = Conjg(cplA0A0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MH02,MA02),dp) 
coup1 = cplA0H0hh
coup2 = Conjg(cplA0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_DerGloop(p2,MFd2(i1),MFd2(i2)) 
B0m2 = -2._dp*MFd(i1)*MFd(i2)*SA_DerB0(p2,MFd2(i1),MFd2(i2)) 
coupL1 = cplcFdFdhhL(i1,i2)
coupR1 = cplcFdFdhhR(i1,i2)
coupL2 =  Conjg(cplcFdFdhhL(i1,i2))
coupR2 =  Conjg(cplcFdFdhhR(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_DerGloop(p2,MFe2(i1),MFe2(i2)) 
B0m2 = -2._dp*MFe(i1)*MFe(i2)*SA_DerB0(p2,MFe2(i1),MFe2(i2)) 
coupL1 = cplcFeFehhL(i1,i2)
coupR1 = cplcFeFehhR(i1,i2)
coupL2 =  Conjg(cplcFeFehhL(i1,i2))
coupR2 =  Conjg(cplcFeFehhR(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 G0m2 = SA_DerGloop(p2,MFu2(i1),MFu2(i2)) 
B0m2 = -2._dp*MFu(i1)*MFu(i2)*SA_DerB0(p2,MFu2(i1),MFu2(i2)) 
coupL1 = cplcFuFuhhL(i1,i2)
coupR1 = cplcFuFuhhR(i1,i2)
coupL2 =  Conjg(cplcFuFuhhL(i1,i2))
coupR2 =  Conjg(cplcFuFuhhR(i1,i2))
    SumI = (coupL1*coupL2+coupR1*coupR2)*G0m2 & 
                & + (coupL1*coupR2+coupR1*coupL2)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MG02,MG02),dp) 
coup1 = cplG0G0hh
coup2 = Conjg(cplG0G0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! VZ, G0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerFloopRXi(p2,MG02,MVZ2),dp) 
coup1 = cplG0hhVZ
coup2 =  Conjg(cplG0hhVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_DerB0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWpgWphh
coup2 =  cplcgWpgWphh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_DerB0(p2,MVWp2*RXi,MVWp2*RXi),dp) 
 coup1 = cplcgWCgWChh
coup2 =  cplcgWCgWChh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gZ 
!------------------------ 
sumI = 0._dp 
 
F0m2 =  -Real(SA_DerB0(p2,MVZ2*RXi,MVZ2*RXi),dp) 
 coup1 = cplcgZgZhh
coup2 =  cplcgZgZhh 
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MH02,MH02),dp) 
coup1 = cplH0H0hh
coup2 = Conjg(cplH0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,Mhh2,Mhh2),dp) 
coup1 = cplhhhhhh
coup2 = Conjg(cplhhhhhh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B0m2 = Real(SA_DerB0(p2,MHp2(i1),MHp2(i2)),dp) 
coup1 = cplhhHpcHp(i2,i1)
coup2 = Conjg(cplhhHpcHp(i2,i1))
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(DerFloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplhhHpcVWp(i2)
coup2 =  Conjg(cplhhHpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerSVVloop(p2,MVWp2,MVWp2),dp) 
coup1 = cplhhcVWpVWp
coup2 =  Conjg(cplhhcVWpVWp)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerSVVloop(p2,MVZ2,MVZ2),dp) 
coup1 = cplhhVZVZ
coup2 =  Conjg(cplhhVZVZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MA02) 
coup1 = cplA0A0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MG02) 
coup1 = cplG0G0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MH02) 
coup1 = cplH0H0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(Mhh2) 
coup1 = cplhhhhhhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_DerA0(MHp2(i1)) 
coup1 = cplhhhhHpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVWp2) + 0.25_dp*RXi*SA_DerA0(MVWp2*RXi) - 0.5_dp*MVWp2*DerrMS 
coup1 = cplhhhhcVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVZ2) + 0.25_dp*RXi*SA_DerA0(MVZ2*RXi) - 0.5_dp*MVZ2*DerrMS 
coup1 = cplhhhhVZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine DerPi1Loophh 
 
Subroutine OneLoopA0(lam5,MHU2,lam3,v,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,            & 
& MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,   & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,delta,mass,mass2,kont)

Real(dp), Intent(in) :: MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Real(dp), Intent(in) :: MHU2,v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0A0cVWpVWp,      & 
& cplA0A0VZVZ

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopA0'
 
mi2 = (4._dp*(MHU2) - (-2._dp*(lam3) + lam5)*v**2 - v**2*Conjg(lam5))/4._dp 

 
p2 = MA02
PiSf = ZeroC 
Call Pi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp,MHp2,              & 
& MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,               & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,PiSf)

mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp,MHp2,              & 
& MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,               & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,PiSf)

mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
   If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
   End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
   SignOfMassChanged = .True. 
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
End Subroutine OneLoopA0
 
 
Subroutine Pi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp,             & 
& MHp2,MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,          & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0A0cVWpVWp,      & 
& cplA0A0VZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
res = 0._dp 
 
!------------------------ 
! G0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MG02,MA02),dp) 
coup1 = cplA0A0G0
coup2 = Conjg(cplA0A0G0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,Mhh2,MA02),dp) 
coup1 = cplA0A0hh
coup2 = Conjg(cplA0A0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MH02,MG02),dp) 
coup1 = cplA0G0H0
coup2 = Conjg(cplA0G0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,Mhh2,MH02),dp) 
coup1 = cplA0H0hh
coup2 = Conjg(cplA0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, H0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(FloopRXi(p2,MH02,MVZ2),dp) 
coup1 = cplA0H0VZ
coup2 =  Conjg(cplA0H0VZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B0m2 = Real(SA_B0(p2,MHp2(i1),MHp2(i2)),dp) 
coup1 = cplA0HpcHp(i2,i1)
coup2 = Conjg(cplA0HpcHp(i2,i1))
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(FloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplA0HpcVWp(i2)
coup2 =  Conjg(cplA0HpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MA02) 
coup1 = cplA0A0A0A0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MG02) 
coup1 = cplA0A0G0G0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MH02) 
coup1 = cplA0A0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(Mhh2) 
coup1 = cplA0A0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_A0(MHp2(i1)) 
coup1 = cplA0A0HpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVWp2) + 0.25_dp*RXi*SA_A0(MVWp2*RXi) - 0.5_dp*MVWp2*rMS 
coup1 = cplA0A0cVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVZ2) + 0.25_dp*RXi*SA_A0(MVZ2*RXi) - 0.5_dp*MVZ2*rMS 
coup1 = cplA0A0VZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine Pi1LoopA0 
 
Subroutine DerPi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,              & 
& MHp,MHp2,MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,      & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),     & 
& cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0A0cVWpVWp,      & 
& cplA0A0VZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! G0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MG02,MA02),dp) 
coup1 = cplA0A0G0
coup2 = Conjg(cplA0A0G0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,Mhh2,MA02),dp) 
coup1 = cplA0A0hh
coup2 = Conjg(cplA0A0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MH02,MG02),dp) 
coup1 = cplA0G0H0
coup2 = Conjg(cplA0G0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,Mhh2,MH02),dp) 
coup1 = cplA0H0hh
coup2 = Conjg(cplA0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, H0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerFloopRXi(p2,MH02,MVZ2),dp) 
coup1 = cplA0H0VZ
coup2 =  Conjg(cplA0H0VZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B0m2 = Real(SA_DerB0(p2,MHp2(i1),MHp2(i2)),dp) 
coup1 = cplA0HpcHp(i2,i1)
coup2 = Conjg(cplA0HpcHp(i2,i1))
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(DerFloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplA0HpcVWp(i2)
coup2 =  Conjg(cplA0HpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MA02) 
coup1 = cplA0A0A0A0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MG02) 
coup1 = cplA0A0G0G0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MH02) 
coup1 = cplA0A0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(Mhh2) 
coup1 = cplA0A0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_DerA0(MHp2(i1)) 
coup1 = cplA0A0HpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVWp2) + 0.25_dp*RXi*SA_DerA0(MVWp2*RXi) - 0.5_dp*MVWp2*DerrMS 
coup1 = cplA0A0cVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVZ2) + 0.25_dp*RXi*SA_DerA0(MVZ2*RXi) - 0.5_dp*MVZ2*DerrMS 
coup1 = cplA0A0VZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine DerPi1LoopA0 
 
Subroutine OneLoopH0(lam5,MHU2,lam3,v,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,            & 
& MH0,MH02,MHp,MHp2,MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,        & 
& cplH0HpcHp,cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,   & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,delta,mass,mass2,kont)

Real(dp), Intent(in) :: MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp(2),MHp2(2),MVWp,MVWp2

Real(dp), Intent(in) :: MHU2,v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),     & 
& cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0H0cVWpVWp,      & 
& cplH0H0VZVZ

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopH0'
 
mi2 = (4._dp*(MHU2) + (2._dp*(lam3) + lam5)*v**2 + v**2*Conjg(lam5))/4._dp 

 
p2 = MH02
PiSf = ZeroC 
Call Pi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp,MHp2,              & 
& MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,               & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,PiSf)

mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp,MHp2,              & 
& MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,               & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,PiSf)

mass2 = mi2 - Real(PiSf,dp) 
mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
   If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
   End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
   SignOfMassChanged = .True. 
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
End Subroutine OneLoopH0
 
 
Subroutine Pi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp,             & 
& MHp2,MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,          & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),     & 
& cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0H0cVWpVWp,      & 
& cplH0H0VZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
res = 0._dp 
 
!------------------------ 
! G0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MG02,MA02),dp) 
coup1 = cplA0G0H0
coup2 = Conjg(cplA0G0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,Mhh2,MA02),dp) 
coup1 = cplA0H0hh
coup2 = Conjg(cplA0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, A0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(FloopRXi(p2,MA02,MVZ2),dp) 
coup1 = cplA0H0VZ
coup2 =  Conjg(cplA0H0VZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,MH02,MG02),dp) 
coup1 = cplG0H0H0
coup2 = Conjg(cplG0H0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_B0(p2,Mhh2,MH02),dp) 
coup1 = cplH0H0hh
coup2 = Conjg(cplH0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B0m2 = Real(SA_B0(p2,MHp2(i1),MHp2(i2)),dp) 
coup1 = cplH0HpcHp(i2,i1)
coup2 = Conjg(cplH0HpcHp(i2,i1))
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(FloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplH0HpcVWp(i2)
coup2 =  Conjg(cplH0HpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MA02) 
coup1 = cplA0A0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MG02) 
coup1 = cplG0G0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(MH02) 
coup1 = cplH0H0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_A0(Mhh2) 
coup1 = cplH0H0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_A0(MHp2(i1)) 
coup1 = cplH0H0HpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVWp2) + 0.25_dp*RXi*SA_A0(MVWp2*RXi) - 0.5_dp*MVWp2*rMS 
coup1 = cplH0H0cVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_A0(MVZ2) + 0.25_dp*RXi*SA_A0(MVZ2*RXi) - 0.5_dp*MVZ2*rMS 
coup1 = cplH0H0VZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine Pi1LoopH0 
 
Subroutine DerPi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,              & 
& MHp,MHp2,MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,      & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2),     & 
& cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0H0cVWpVWp,      & 
& cplH0H0VZVZ

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2,B1m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2,temp, sumI 
Integer :: i1,i2,i3,i4,ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! G0, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MG02,MA02),dp) 
coup1 = cplA0G0H0
coup2 = Conjg(cplA0G0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, A0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,Mhh2,MA02),dp) 
coup1 = cplA0H0hh
coup2 = Conjg(cplA0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, A0 
!------------------------ 
sumI = 0._dp 
 
F0m2 = Real(DerFloopRXi(p2,MA02,MVZ2),dp) 
coup1 = cplA0H0VZ
coup2 =  Conjg(cplA0H0VZ)
    SumI = coup1*coup2*F0m2 
res = res +1._dp* SumI  
!------------------------ 
! H0, G0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,MH02,MG02),dp) 
coup1 = cplG0H0H0
coup2 = Conjg(cplG0H0H0)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! hh, H0 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(SA_DerB0(p2,Mhh2,MH02),dp) 
coup1 = cplH0H0hh
coup2 = Conjg(cplH0H0hh)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B0m2 = Real(SA_DerB0(p2,MHp2(i1),MHp2(i2)),dp) 
coup1 = cplH0HpcHp(i2,i1)
coup2 = Conjg(cplH0HpcHp(i2,i1))
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 F0m2 = Real(DerFloopRXi(p2,MHp2(i2),MVWp2),dp) 
coup1 = cplH0HpcVWp(i2)
coup2 =  Conjg(cplH0HpcVWp(i2))
    SumI = coup1*coup2*F0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! A0, A0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MA02) 
coup1 = cplA0A0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0, G0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MG02) 
coup1 = cplG0G0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0, H0 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(MH02) 
coup1 = cplH0H0H0H0
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh, hh 
!------------------------ 
sumI = 0._dp 
 
A0m2 = SA_DerA0(Mhh2) 
coup1 = cplH0H0hhhh
    SumI = -coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 A0m2 = SA_DerA0(MHp2(i1)) 
coup1 = cplH0H0HpcHp(i1,i1)
    SumI = -coup1*A0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVWp2) + 0.25_dp*RXi*SA_DerA0(MVWp2*RXi) - 0.5_dp*MVWp2*DerrMS 
coup1 = cplH0H0cVWpVWp
    SumI = coup1*A0m2 
res = res +4._dp* SumI  
!------------------------ 
! VZ, VZ 
!------------------------ 
sumI = 0._dp 
 
A0m2 =  0.75_dp*SA_DerA0(MVZ2) + 0.25_dp*RXi*SA_DerA0(MVZ2*RXi) - 0.5_dp*MVZ2*DerrMS 
coup1 = cplH0H0VZVZ
    SumI = coup1*A0m2 
res = res +2._dp* SumI  


res = oo16pi2*res 
 
End Subroutine DerPi1LoopH0 
 
Subroutine Pi1LoopVG(p2,MFd,MFd2,MFu,MFu2,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,        & 
& cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3)

Complex(dp), Intent(in) :: cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcgGgGVG,       & 
& cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

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
coupL1 = cplcFdFdVGL(i1,i2)
coupR1 = cplcFdFdVGR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +0.5_dp* SumI  
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
coupL1 = cplcFuFuVGL(i1,i2)
coupR1 = cplcFuFuVGR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +0.5_dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gG], gG 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,0._dp,0._dp),dp)
coup1 = cplcgGgGVG
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +3._dp* SumI  
!------------------------ 
! VG, VG 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplVGVGVG
coup2 = Conjg(coup1) 
    SumI = -VVVloop(p2,0._dp,0._dp)*coup1*coup2 
res = res +1.5_dp* SumI  
!------------------------ 
! VG 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(0._dp) +RXi/4._dp*SA_A0(0._dp*RXi) 
coup1 = cplVGVGVGVG1
coup2 = cplVGVGVGVG2
coup3 = cplVGVGVGVG3
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*0._dp-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVG 
 
Subroutine DerPi1LoopVG(p2,MFd,MFd2,MFu,MFu2,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,     & 
& cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3)

Complex(dp), Intent(in) :: cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcgGgGVG,       & 
& cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_DerB0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVGL(i1,i2)
coupR1 = cplcFdFdVGR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +0.5_dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*Real(SA_DerB0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVGL(i1,i2)
coupR1 = cplcFuFuVGR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +0.5_dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gG], gG 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVG2,MVG2),dp)
coup1 = cplcgGgGVG
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +3._dp* SumI  
!------------------------ 
! VG, VG 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplVGVGVG
coup2 = Conjg(coup1) 
    SumI = -DerVVVloop(p2,MVG2,MVG2)*coup1*coup2 
res = res +1.5_dp* SumI  
!------------------------ 
! VG 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVG2) +RXi/4._dp*SA_DerA0(MVG2*RXi) 
coup1 = cplVGVGVGVG1
coup2 = cplVGVGVGVG2
coup3 = cplVGVGVGVG3
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVG2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVG 
 
Subroutine Pi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,            & 
& cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3), & 
& cplcFuFuVPR(3,3),cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP(2,2),cplHpcVWpVP(2),             & 
& cplcVWpVPVWp,cplHpcHpVPVP(2,2),cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2

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
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MFd2(i1).gt.50._dp**2).and.(MFd2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MFd2(i1).lt.50._dp**2).and.(MFd2(i2).lt.50._dp**2)) )   Then 
H0m2 = Real(SA_Hloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_B0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVPL(i1,i2)
coupR1 = cplcFdFdVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MFe2(i1).gt.50._dp**2).and.(MFe2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MFe2(i1).lt.50._dp**2).and.(MFe2(i2).lt.50._dp**2)) )   Then 
H0m2 = Real(SA_Hloop(p2,MFe2(i1),MFe2(i2)),dp) 
B0m2 = 4._dp*MFe(i1)*MFe(i2)*Real(SA_B0(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVPL(i1,i2)
coupR1 = cplcFeFeVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MFu2(i1).gt.50._dp**2).and.(MFu2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MFu2(i1).lt.50._dp**2).and.(MFu2(i2).lt.50._dp**2)) )   Then 
H0m2 = Real(SA_Hloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*Real(SA_B0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVPL(i1,i2)
coupR1 = cplcFuFuVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MVWp2.lt.50._dp**2)) )   Then 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVP
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
End If 
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MVWp2.lt.50._dp**2)) )   Then 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVP
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
End If 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MHp2(i2).gt.50._dp**2).and.(MHp2(i1).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MHp2(i2).lt.50._dp**2).and.(MHp2(i1).lt.50._dp**2)) )   Then 
B22m2 = Real(VSSloop(p2,MHp2(i2),MHp2(i1)),dp)  
coup1 = cplHpcHpVP(i2,i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MHp2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MHp2(i2).lt.50._dp**2)) )   Then 
B0m2 = Real(VVSloop(p2,MVWp2,MHp2(i2)),dp)
coup1 = cplHpcVWpVP(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +2._dp* SumI  
End If 
    End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MVWp2.lt.50._dp**2)) )   Then 
coup1 = cplcVWpVPVWp
coup2 = Conjg(coup1) 
    SumI = -VVVloop(p2,MVWp2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
End If 
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MHp2(i1).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MHp2(i1).lt.50._dp**2)) )   Then 
SumI = 0._dp 
 A0m2 = SA_A0(MHp2(i1))
 coup1 = cplHpcHpVPVP(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
End If 
      End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2)) )   Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2*RXi) 
coup1 = cplcVWpVPVPVWp3
coup2 = cplcVWpVPVPVWp1
coup3 = cplcVWpVPVPVWp2
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
End If 
res = oo16pi2*res 
 
End Subroutine Pi1LoopVP 
 
Subroutine DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,            & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,            & 
& cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3), & 
& cplcFuFuVPR(3,3),cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP(2,2),cplHpcVWpVP(2),             & 
& cplcVWpVPVWp,cplHpcHpVPVP(2,2),cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MFd2(i1).gt.50._dp**2).and.(MFd2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MFd2(i1).lt.50._dp**2).and.(MFd2(i2).lt.50._dp**2)) )   Then 
H0m2 = Real(SA_DerHloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_DerB0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVPL(i1,i2)
coupR1 = cplcFdFdVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MFe2(i1).gt.50._dp**2).and.(MFe2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MFe2(i1).lt.50._dp**2).and.(MFe2(i2).lt.50._dp**2)) )   Then 
H0m2 = Real(SA_DerHloop(p2,MFe2(i1),MFe2(i2)),dp) 
B0m2 = 4._dp*MFe(i1)*MFe(i2)*Real(SA_DerB0(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVPL(i1,i2)
coupR1 = cplcFeFeVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MFu2(i1).gt.50._dp**2).and.(MFu2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MFu2(i1).lt.50._dp**2).and.(MFu2(i2).lt.50._dp**2)) )   Then 
H0m2 = Real(SA_DerHloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*Real(SA_DerB0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVPL(i1,i2)
coupR1 = cplcFuFuVPR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MVWp2.lt.50._dp**2)) )   Then 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVP
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
End If 
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MVWp2.lt.50._dp**2)) )   Then 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVP
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
End If 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MHp2(i2).gt.50._dp**2).and.(MHp2(i1).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MHp2(i2).lt.50._dp**2).and.(MHp2(i1).lt.50._dp**2)) )   Then 
B22m2 = Real(DerVSSloop(p2,MHp2(i2),MHp2(i1)),dp)  
coup1 = cplHpcHpVP(i2,i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
End If 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MHp2(i2).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MHp2(i2).lt.50._dp**2)) )   Then 
B0m2 = Real(DerVVSloop(p2,MVWp2,MHp2(i2)),dp)
coup1 = cplHpcVWpVP(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +2._dp* SumI  
End If 
    End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2).and.(MVWp2.lt.50._dp**2)) )   Then 
coup1 = cplcVWpVPVWp
coup2 = Conjg(coup1) 
    SumI = -DerVVVloop(p2,MVWp2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
End If 
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MHp2(i1).gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MHp2(i1).lt.50._dp**2)) )   Then 
SumI = 0._dp 
 A0m2 = SA_DerA0(MHp2(i1))
 coup1 = cplHpcHpVPVP(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
End If 
      End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
If (((.not.OnlyHeavyStates).and.(.not.OnlyLightStates)) & 
  & .or.((OnlyHeavyStates).and.(MVWp2.gt.50._dp**2))   & 
  & .or.((OnlyLightStates).and.(MVWp2.lt.50._dp**2)) )   Then 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVWp2) +RXi/4._dp*SA_DerA0(MVWp2*RXi) 
coup1 = cplcVWpVPVPVWp3
coup2 = cplcVWpVPVPVWp1
coup3 = cplcVWpVPVPVWp2
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
End If 
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVP 
 
Subroutine OneLoopVZ(g1,g2,v,TW,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,              & 
& MFu2,Mhh,Mhh2,MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,             & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,      & 
& cplcVWpVWpVZ,cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,             & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,delta,mass,mass2,kont)

Real(dp), Intent(in) :: MH0,MH02,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(in) :: cplA0H0VZ,cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),        & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplG0hhVZ,         & 
& cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcVWpVWpVZ,       & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ(2,2),cplcVWpVWpVZVZ1,     & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopVZ'
 
mi2 = MVZ2 

 
p2 = MVZ2
PiSf = ZeroC 
Call Pi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiSf)

mass2 = mi2 + Real(PiSf,dp) 
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiSf)

mass2 = mi2 + Real(PiSf,dp) 
mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
   If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
   End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
   SignOfMassChanged = .True. 
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
End Subroutine OneLoopVZ
 
 
Subroutine Pi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,             & 
& Mhh2,MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,          & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MH0,MH02,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0H0VZ,cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),        & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplG0hhVZ,         & 
& cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcVWpVWpVZ,       & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ(2,2),cplcVWpVWpVZVZ1,     & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
B22m2 = Real(VSSloop(p2,MA02,MH02),dp)  
coup1 = cplA0H0VZ
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_B0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
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
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
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
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fv], Fv 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,0._dp,0._dp),dp) 
B0m2 = 4._dp*0._dp*0._dp*Real(SA_B0(p2,0._dp,0._dp),dp) 
coupL1 = cplcFvFvVZL(i1,i2)
coupR1 = cplcFvFvVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! hh, G0 
!------------------------ 
sumI = 0._dp 
 
B22m2 = Real(VSSloop(p2,MG02,Mhh2),dp)  
coup1 = cplG0hhVZ
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVZ
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVZ
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, hh 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(VVSloop(p2,MVZ2,Mhh2),dp)
coup1 = cplhhVZVZ
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B22m2 = Real(VSSloop(p2,MHp2(i2),MHp2(i1)),dp)  
coup1 = cplHpcHpVZ(i2,i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(VVSloop(p2,MVWp2,MHp2(i2)),dp)
coup1 = cplHpcVWpVZ(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVWpVZ
coup2 = Conjg(coup1) 
    SumI = -VVVloop(p2,MVWp2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! A0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MA02)
 coup1 = cplA0A0VZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MG02)
 coup1 = cplG0G0VZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MH02)
 coup1 = cplH0H0VZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(Mhh2)
 coup1 = cplhhhhVZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 SumI = 0._dp 
 A0m2 = SA_A0(MHp2(i1))
 coup1 = cplHpcHpVZVZ(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
      End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2*RXi) 
coup1 = cplcVWpVWpVZVZ1
coup2 = cplcVWpVWpVZVZ2
coup3 = cplcVWpVWpVZVZ3
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVZ 
 
Subroutine DerPi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,              & 
& Mhh,Mhh2,MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,      & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MH0,MH02,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0H0VZ,cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),        & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplG0hhVZ,         & 
& cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcVWpVWpVZ,       & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ(2,2),cplcVWpVWpVZVZ1,     & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
B22m2 = Real(DerVSSloop(p2,MA02,MH02),dp)  
coup1 = cplA0H0VZ
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFd(i2)*Real(SA_DerB0(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
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
 H0m2 = Real(SA_DerHloop(p2,MFe2(i1),MFe2(i2)),dp) 
B0m2 = 4._dp*MFe(i1)*MFe(i2)*Real(SA_DerB0(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
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
 H0m2 = Real(SA_DerHloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFu(i1)*MFu(i2)*Real(SA_DerB0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fv], Fv 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,0._dp,0._dp),dp) 
B0m2 = 4._dp*0._dp*0._dp*Real(SA_DerB0(p2,0._dp,0._dp),dp) 
coupL1 = cplcFvFvVZL(i1,i2)
coupR1 = cplcFvFvVZR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! hh, G0 
!------------------------ 
sumI = 0._dp 
 
B22m2 = Real(DerVSSloop(p2,MG02,Mhh2),dp)  
coup1 = cplG0hhVZ
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVZ
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVZ
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, hh 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(DerVVSloop(p2,MVZ2,Mhh2),dp)
coup1 = cplhhVZVZ
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B22m2 = Real(DerVSSloop(p2,MHp2(i2),MHp2(i1)),dp)  
coup1 = cplHpcHpVZ(i2,i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(DerVVSloop(p2,MVWp2,MHp2(i2)),dp)
coup1 = cplHpcVWpVZ(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +2._dp* SumI  
    End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVWpVZ
coup2 = Conjg(coup1) 
    SumI = -DerVVVloop(p2,MVWp2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! A0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(MA02)
 coup1 = cplA0A0VZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(MG02)
 coup1 = cplG0G0VZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(MH02)
 coup1 = cplH0H0VZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(Mhh2)
 coup1 = cplhhhhVZVZ
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 SumI = 0._dp 
 A0m2 = SA_DerA0(MHp2(i1))
 coup1 = cplHpcHpVZVZ(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
      End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVWp2) +RXi/4._dp*SA_DerA0(MVWp2*RXi) 
coup1 = cplcVWpVWpVZVZ1
coup2 = cplcVWpVWpVZVZ2
coup3 = cplcVWpVWpVZVZ3
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVZ 
 
Subroutine OneLoopVWp(g2,v,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,              & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,              & 
& cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,     & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,          & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,    & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,delta,mass,mass2,kont)

Real(dp), Intent(in) :: MHp(2),MHp2(2),MA0,MA02,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),MFe2(3),MG0,             & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(in) :: cplA0HpcVWp(2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),              & 
& cplcFeFvcVWpR(3,3),cplG0HpcVWp(2),cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgZcVWp,cplH0HpcVWp(2),cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),               & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp, & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp(2,2),cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,   & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer , Intent(inout):: kont 
Integer :: i1,i2,i3,i4,j1,j2,j3,j4,il,i_count, ierr 
Real(dp), Intent(in) :: delta 
Real(dp) :: mi, mi2, p2, test_m2 
Complex(dp) :: PiSf, SigL, SigR, SigSL, SigSR 
Real(dp), Intent(out) :: mass, mass2 
Iname = Iname + 1 
NameOfUnit(Iname) = 'OneLoopVWp'
 
mi2 = MVWp2 

 
p2 = MVWp2
PiSf = ZeroC 
Call Pi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,MG02,             & 
& MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,PiSf)

mass2 = mi2 + Real(PiSf,dp) 
mass = sqrt(mass2) 
i_count = 0 
Do  
i_count = i_count + 1 
test_m2 = mass2 
p2 =  mass2 
PiSf = ZeroC 
Call Pi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,MG02,             & 
& MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,PiSf)

mass2 = mi2 + Real(PiSf,dp) 
mass = sqrt(mass2) 
 If (test_m2.Ne.0._dp) Then 
    test_m2 = Abs(test_m2 - mass2) / test_m2 
 Else 
    test_m2 = Abs(mass2) 
 End If 
 If (mass2.Ge.0._dp) Then 
   If (RotateNegativeFermionMasses) Then 
    mass = sqrt(mass2) 
   End if 
  Else 
 If (Abs(mass2).lt.1.0E-30_dp) test_m2 = 0._dp 
     Write(ErrCan,*) 'Warning from routine'//NameOfUnit(Iname) 
     Write(ErrCan,*) 'in the calculation of the masses' 
     Write(ErrCan,*) 'occurred a negative mass squared!' 
   SignOfMassChanged = .True. 
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
End Subroutine OneLoopVWp
 
 
Subroutine Pi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,            & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MA0,MA02,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),MFe2(3),MG0,             & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0HpcVWp(2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),              & 
& cplcFeFvcVWpR(3,3),cplG0HpcVWp(2),cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgZcVWp,cplH0HpcVWp(2),cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),               & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp, & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp(2,2),cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,   & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! Hp, A0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(VSSloop(p2,MA02,MHp2(i1)),dp)  
coup1 = cplA0HpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! bar[Fd], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,MFd2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFu(i2)*Real(SA_B0(p2,MFd2(i1),MFu2(i2)),dp) 
coupL1 = cplcFdFucVWpL(i1,i2)
coupR1 = cplcFdFucVWpR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fv 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_Hloop(p2,MFe2(i1),0._dp),dp) 
B0m2 = 4._dp*MFe(i1)*0._dp*Real(SA_B0(p2,MFe2(i1),0._dp),dp) 
coupL1 = cplcFeFvcVWpL(i1,i2)
coupR1 = cplcFeFvcVWpR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! Hp, G0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(VSSloop(p2,MG02,MHp2(i1)),dp)  
coup1 = cplG0HpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! bar[gWpC], gP 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,0._dp,MVWp2),dp)
coup1 = cplcgWCgAcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gP], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,0._dp),dp)
coup1 = cplcgAgWpcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVWp2,MVZ2),dp)
coup1 = cplcgZgWpcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gZ 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(VGGloop(p2,MVZ2,MVWp2),dp)
coup1 = cplcgWCgZcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! Hp, H0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(VSSloop(p2,MH02,MHp2(i1)),dp)  
coup1 = cplH0HpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! Hp, hh 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(VSSloop(p2,Mhh2,MHp2(i1)),dp)  
coup1 = cplhhHpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, hh 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(VVSloop(p2,MVWp2,Mhh2),dp)
coup1 = cplhhcVWpVWp
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VP, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(VVSloop(p2,0._dp,MHp2(i2)),dp)
coup1 = cplHpcVWpVP(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VZ, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(VVSloop(p2,MVZ2,MHp2(i2)),dp)
coup1 = cplHpcVWpVZ(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VWp, VP 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVPVWp
coup2 = Conjg(coup1) 
    SumI = -VVVloop(p2,MVWp2,0._dp)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, VWp 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVWpVZ
coup2 = Conjg(coup1) 
    SumI = -VVVloop(p2,MVZ2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! A0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MA02)
 coup1 = cplA0A0cVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MG02)
 coup1 = cplG0G0cVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(MH02)
 coup1 = cplH0H0cVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_A0(Mhh2)
 coup1 = cplhhhhcVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 SumI = 0._dp 
 A0m2 = SA_A0(MHp2(i1))
 coup1 = cplHpcHpcVWpVWp(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
      End Do 
 !------------------------ 
! VP 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(0._dp) +RXi/4._dp*SA_A0(0._dp*RXi) 
coup1 = cplcVWpVPVPVWp3
coup2 = cplcVWpVPVPVWp1
coup3 = cplcVWpVPVPVWp2
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*0._dp-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2*RXi) 
coup1 = cplcVWpcVWpVWpVWp2
coup2 = cplcVWpcVWpVWpVWp3
coup3 = cplcVWpcVWpVWpVWp1
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
!------------------------ 
! VZ 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVZ2) +RXi/4._dp*SA_A0(MVZ2*RXi) 
coup1 = cplcVWpVWpVZVZ1
coup2 = cplcVWpVWpVZVZ2
coup3 = cplcVWpVWpVZVZ3
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVZ2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVWp 
 
Subroutine DerPi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,             & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,              & 
& cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,     & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,          & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,    & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,        & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MA0,MA02,MFd(3),MFd2(3),MFu(3),MFu2(3),MFe(3),MFe2(3),MG0,             & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0HpcVWp(2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),              & 
& cplcFeFvcVWpR(3,3),cplG0HpcVWp(2),cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgZcVWp,cplH0HpcVWp(2),cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),               & 
& cplHpcVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp, & 
& cplhhhhcVWpVWp,cplHpcHpcVWpVWp(2,2),cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,   & 
& cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,              & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2, A0m12, A0m22 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! Hp, A0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(DerVSSloop(p2,MA02,MHp2(i1)),dp)  
coup1 = cplA0HpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! bar[Fd], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFd2(i1),MFu2(i2)),dp) 
B0m2 = 4._dp*MFd(i1)*MFu(i2)*Real(SA_DerB0(p2,MFd2(i1),MFu2(i2)),dp) 
coupL1 = cplcFdFucVWpL(i1,i2)
coupR1 = cplcFdFucVWpR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fv 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFe2(i1),0._dp),dp) 
B0m2 = 4._dp*MFe(i1)*0._dp*Real(SA_DerB0(p2,MFe2(i1),0._dp),dp) 
coupL1 = cplcFeFvcVWpL(i1,i2)
coupR1 = cplcFeFvcVWpR(i1,i2)
    SumI = (Abs(coupL1)**2+Abs(coupR1)**2)*H0m2 & 
                & + (Real(Conjg(coupL1)*coupR1,dp))*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! Hp, G0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(DerVSSloop(p2,MG02,MHp2(i1)),dp)  
coup1 = cplG0HpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! bar[gWpC], gP 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVP2,MVWp2),dp)
coup1 = cplcgWCgAcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gP], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVP2),dp)
coup1 = cplcgAgWpcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gWp 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVZ2),dp)
coup1 = cplcgZgWpcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gZ 
!------------------------ 
sumI = 0._dp 
 
SumI = 0._dp 
B0m2 = Real(DerVGGloop(p2,MVZ2,MVWp2),dp)
coup1 = cplcgWCgZcVWp
coup2 = Conjg(coup1) 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! Hp, H0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(DerVSSloop(p2,MH02,MHp2(i1)),dp)  
coup1 = cplH0HpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! Hp, hh 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B22m2 = Real(DerVSSloop(p2,Mhh2,MHp2(i1)),dp)  
coup1 = cplhhHpcVWp(i1)
    SumI = Abs(coup1)**2*B22m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! VWp, hh 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(DerVVSloop(p2,MVWp2,Mhh2),dp)
coup1 = cplhhcVWpVWp
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! VP, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(DerVVSloop(p2,MVP2,MHp2(i2)),dp)
coup1 = cplHpcVWpVP(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VZ, Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(DerVVSloop(p2,MVZ2,MHp2(i2)),dp)
coup1 = cplHpcVWpVZ(i2)
    SumI = Abs(coup1)**2*B0m2 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! VWp, VP 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVPVWp
coup2 = Conjg(coup1) 
    SumI = -DerVVVloop(p2,MVWp2,MVP2)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! VZ, VWp 
!------------------------ 
sumI = 0._dp 
 
coup1 = cplcVWpVWpVZ
coup2 = Conjg(coup1) 
    SumI = -DerVVVloop(p2,MVZ2,MVWp2)*coup1*coup2 
res = res +1._dp* SumI  
!------------------------ 
! A0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(MA02)
 coup1 = cplA0A0cVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! G0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(MG02)
 coup1 = cplG0G0cVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! H0 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(MH02)
 coup1 = cplH0H0cVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! hh 
!------------------------ 
SumI = 0._dp 
 A0m2 = SA_DerA0(Mhh2)
 coup1 = cplhhhhcVWpVWp
 SumI = coup1*A0m2 
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 SumI = 0._dp 
 A0m2 = SA_DerA0(MHp2(i1))
 coup1 = cplHpcHpcVWpVWp(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
      End Do 
 !------------------------ 
! VP 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVP2) +RXi/4._dp*SA_DerA0(MVP2*RXi) 
coup1 = cplcVWpVPVPVWp3
coup2 = cplcVWpVPVPVWp1
coup3 = cplcVWpVPVPVWp2
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVP2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
!------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVWp2) +RXi/4._dp*SA_DerA0(MVWp2*RXi) 
coup1 = cplcVWpcVWpVWpVWp2
coup2 = cplcVWpcVWpVWpVWp3
coup3 = cplcVWpcVWpVWpVWp1
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
!------------------------ 
! VZ 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVZ2) +RXi/4._dp*SA_DerA0(MVZ2*RXi) 
coup1 = cplcVWpVWpVZVZ1
coup2 = cplcVWpVWpVZVZ2
coup3 = cplcVWpVWpVZVZ3
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVZ2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1._dp/2._dp* SumI  
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVWp 
 
Subroutine Sigma1LoopFeMZ(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,            & 
& MVWp,MVWp2,cplcUFeFeG0L,cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,           & 
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,     & 
& cplcUFeFvcVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFe(3),MFe2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),              & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3)

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
! G0, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFe2(gO1),MFe2(i2),MG02),dp) 
B0m2 = MFe(i2)*Real(SA_B0(MFe2(gO1),MFe2(i2),MG02),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFe2(i2),MG02),dp) 
B0m2 = MFe(i2)*Real(SA_B0(p2,MFe2(i2),MG02),dp) 
End If 
coupL1 = cplcUFeFeG0L(gO1,i2)
coupR1 = cplcUFeFeG0R(gO1,i2)
coupL2 =  Conjg(cplcUFeFeG0L(gO2,i2))
coupR2 =  Conjg(cplcUFeFeG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFe2(gO1),MFe2(i2),Mhh2),dp) 
B0m2 = MFe(i2)*Real(SA_B0(MFe2(gO1),MFe2(i2),Mhh2),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFe2(i2),Mhh2),dp) 
B0m2 = MFe(i2)*Real(SA_B0(p2,MFe2(i2),Mhh2),dp) 
End If 
coupL1 = cplcUFeFehhL(gO1,i2)
coupR1 = cplcUFeFehhR(gO1,i2)
coupL2 =  Conjg(cplcUFeFehhL(gO2,i2))
coupR2 =  Conjg(cplcUFeFehhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fe 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -2._dp*Real(SA_B1(MFe2(gO1),MFe2(i2),MVZ2),dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(MFe2(gO1),MFe2(i2),MVZ2)-0.5_dp*rMS,dp) 
Else 
B1m2 = -2._dp*Real(SA_B1(p2,MFe2(i2),MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFe(i2)*Real(SA_B0(p2,MFe2(i2),MVZ2)-0.5_dp*rMS,dp) 
End If 
coupL1 = cplcUFeFeVZL(gO1,i2)
coupR1 = cplcUFeFeVZR(gO1,i2)
coupL2 =  Conjg(cplcUFeFeVZL(gO2,i2))
coupR2 =  Conjg(cplcUFeFeVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! conj[Hp], Fv 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFe2(gO1),0._dp,MHp2(i1)),dp) 
B0m2 = 0._dp*Real(SA_B0(MFe2(gO1),0._dp,MHp2(i1)),dp) 
Else 
B1m2 = -Real(SA_B1(p2,0._dp,MHp2(i1)),dp) 
B0m2 = 0._dp*Real(SA_B0(p2,0._dp,MHp2(i1)),dp) 
End If 
coupL1 = cplcUFeFvcHpL(gO1,i2,i1)
coupR1 = cplcUFeFvcHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFeFvcHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFeFvcHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Fv 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -2._dp*Real(SA_B1(MFe2(gO1),0._dp,MVWp2),dp) 
B0m2 = -4._dp*0._dp*Real(SA_B0(MFe2(gO1),0._dp,MVWp2)-0.5_dp*rMS,dp) 
Else 
B1m2 = -2._dp*Real(SA_B1(p2,0._dp,MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*0._dp*Real(SA_B0(p2,0._dp,MVWp2)-0.5_dp*rMS,dp) 
End If 
coupL1 = cplcUFeFvcVWpL(gO1,i2)
coupR1 = cplcUFeFvcVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFeFvcVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFeFvcVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFeMZ 
 
Subroutine Sigma1LoopFdMZ(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,            & 
& MFu,MFu2,MVWp,MVWp2,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,               & 
& cplcUFdFdVGL,cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,         & 
& cplcUFdFucHpL,cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MG0,MG02,MFd(3),MFd2(3),Mhh,Mhh2,MVZ,MVZ2,MHp(2),MHp2(2),MFu(3),MFu2(3),              & 
& MVWp,MVWp2

Complex(dp), Intent(in) :: cplcUFdFdG0L(3,3),cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),              & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),cplcUFdFucHpR(3,3,2),         & 
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
! G0, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFd2(gO1),MFd2(i2),MG02),dp) 
B0m2 = MFd(i2)*Real(SA_B0(MFd2(gO1),MFd2(i2),MG02),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFd2(i2),MG02),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),MG02),dp) 
End If 
coupL1 = cplcUFdFdG0L(gO1,i2)
coupR1 = cplcUFdFdG0R(gO1,i2)
coupL2 =  Conjg(cplcUFdFdG0L(gO2,i2))
coupR2 =  Conjg(cplcUFdFdG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFd2(gO1),MFd2(i2),Mhh2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(MFd2(gO1),MFd2(i2),Mhh2),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFd2(i2),Mhh2),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),Mhh2),dp) 
End If 
coupL1 = cplcUFdFdhhL(gO1,i2)
coupR1 = cplcUFdFdhhR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdhhL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdhhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -2._dp*Real(SA_B1(MFd2(gO1),MFd2(i2),MVZ2),dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(MFd2(gO1),MFd2(i2),MVZ2)-0.5_dp*rMS,dp) 
Else 
B1m2 = -2._dp*Real(SA_B1(p2,MFd2(i2),MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),MVZ2)-0.5_dp*rMS,dp) 
End If 
coupL1 = cplcUFdFdVZL(gO1,i2)
coupR1 = cplcUFdFdVZR(gO1,i2)
coupL2 =  Conjg(cplcUFdFdVZL(gO2,i2))
coupR2 =  Conjg(cplcUFdFdVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! conj[Hp], Fu 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFd2(gO1),MFu2(i2),MHp2(i1)),dp) 
B0m2 = MFu(i2)*Real(SA_B0(MFd2(gO1),MFu2(i2),MHp2(i1)),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFu2(i2),MHp2(i1)),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),MHp2(i1)),dp) 
End If 
coupL1 = cplcUFdFucHpL(gO1,i2,i1)
coupR1 = cplcUFdFucHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFdFucHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFdFucHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -2._dp*Real(SA_B1(MFd2(gO1),MFu2(i2),MVWp2),dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(MFd2(gO1),MFu2(i2),MVWp2)-0.5_dp*rMS,dp) 
Else 
B1m2 = -2._dp*Real(SA_B1(p2,MFu2(i2),MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),MVWp2)-0.5_dp*rMS,dp) 
End If 
coupL1 = cplcUFdFucVWpL(gO1,i2)
coupR1 = cplcUFdFucVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFdFucVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFdFucVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFdMZ 
 
Subroutine Sigma1LoopFuMZ(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,               & 
& MFu2,Mhh,Mhh2,MVZ,MVZ2,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,cplcUFuFdVWpR,          & 
& cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,         & 
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigL,sigR,sigSL,sigSR)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MFd(3),MFd2(3),MVWp,MVWp2,MG0,MG02,MFu(3),MFu2(3),Mhh,Mhh2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcUFuFdHpL(3,3,2),cplcUFuFdHpR(3,3,2),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),        & 
& cplcUFuFuG0L(3,3),cplcUFuFuG0R(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),               & 
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
! Hp, Fd 
!------------------------ 
    Do i1 = 1, 2
       Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFu2(gO1),MFd2(i2),MHp2(i1)),dp) 
B0m2 = MFd(i2)*Real(SA_B0(MFu2(gO1),MFd2(i2),MHp2(i1)),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFd2(i2),MHp2(i1)),dp) 
B0m2 = MFd(i2)*Real(SA_B0(p2,MFd2(i2),MHp2(i1)),dp) 
End If 
coupL1 = cplcUFuFdHpL(gO1,i2,i1)
coupR1 = cplcUFuFdHpR(gO1,i2,i1)
coupL2 =  Conjg(cplcUFuFdHpL(gO2,i2,i1))
coupR2 =  Conjg(cplcUFuFdHpR(gO2,i2,i1))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
      End Do 
     End Do 
 !------------------------ 
! VWp, Fd 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -2._dp*Real(SA_B1(MFu2(gO1),MFd2(i2),MVWp2),dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(MFu2(gO1),MFd2(i2),MVWp2)-0.5_dp*rMS,dp) 
Else 
B1m2 = -2._dp*Real(SA_B1(p2,MFd2(i2),MVWp2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFd(i2)*Real(SA_B0(p2,MFd2(i2),MVWp2)-0.5_dp*rMS,dp) 
End If 
coupL1 = cplcUFuFdVWpL(gO1,i2)
coupR1 = cplcUFuFdVWpR(gO1,i2)
coupL2 =  Conjg(cplcUFuFdVWpL(gO2,i2))
coupR2 =  Conjg(cplcUFuFdVWpR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! G0, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFu2(gO1),MFu2(i2),MG02),dp) 
B0m2 = MFu(i2)*Real(SA_B0(MFu2(gO1),MFu2(i2),MG02),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFu2(i2),MG02),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),MG02),dp) 
End If 
coupL1 = cplcUFuFuG0L(gO1,i2)
coupR1 = cplcUFuFuG0R(gO1,i2)
coupL2 =  Conjg(cplcUFuFuG0L(gO2,i2))
coupR2 =  Conjg(cplcUFuFuG0R(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! hh, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -Real(SA_B1(MFu2(gO1),MFu2(i2),Mhh2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(MFu2(gO1),MFu2(i2),Mhh2),dp) 
Else 
B1m2 = -Real(SA_B1(p2,MFu2(i2),Mhh2),dp) 
B0m2 = MFu(i2)*Real(SA_B0(p2,MFu2(i2),Mhh2),dp) 
End If 
coupL1 = cplcUFuFuhhL(gO1,i2)
coupR1 = cplcUFuFuhhR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuhhL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuhhR(gO2,i2))
SumSL(gO1,gO2) = coupR1*coupL2*B0m2 
SumSR(gO1,gO2) = coupL1*coupR2*B0m2 
sumR(gO1,gO2) = coupR1*coupR2*B1m2 
sumL(gO1,gO2) = coupL1*coupL2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 !------------------------ 
! VZ, Fu 
!------------------------ 
      Do i2 = 1, 3
 SumSL = 0._dp 
SumSR = 0._dp 
sumR = 0._dp 
sumL = 0._dp 
Do gO1 = 1, 3
  Do gO2 = 1, 3
If(gO1.eq.gO2) Then 
B1m2 = -2._dp*Real(SA_B1(MFu2(gO1),MFu2(i2),MVZ2),dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(MFu2(gO1),MFu2(i2),MVZ2)-0.5_dp*rMS,dp) 
Else 
B1m2 = -2._dp*Real(SA_B1(p2,MFu2(i2),MVZ2)+ 0.5_dp*rMS,dp) 
B0m2 = -4._dp*MFu(i2)*Real(SA_B0(p2,MFu2(i2),MVZ2)-0.5_dp*rMS,dp) 
End If 
coupL1 = cplcUFuFuVZL(gO1,i2)
coupR1 = cplcUFuFuVZR(gO1,i2)
coupL2 =  Conjg(cplcUFuFuVZL(gO2,i2))
coupR2 =  Conjg(cplcUFuFuVZR(gO2,i2))
SumSL(gO1,gO2) = coupL1*coupR2*B0m2 
SumSR(gO1,gO2) = coupR1*coupL2*B0m2 
sumR(gO1,gO2) = coupL1*coupL2*B1m2 
sumL(gO1,gO2) = coupR1*coupR2*B1m2 
   End Do 
End Do 
SigL = SigL +1._dp* sumL
SigR = SigR +1._dp* sumR 
SigSL = SigSL +1._dp* sumSL 
SigSR = SigSR +1._dp* sumSR 
    End Do 
 SigL = oo16pi2*SigL 
SigR = oo16pi2*SigR 
SigSL = oo16pi2*SigSL 
SigSR = oo16pi2*SigSR 
 
End Subroutine Sigma1LoopFuMZ 
 
Subroutine Pi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,           & 
& cplcVWpVPVWp,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,             & 
& cplHpcHpVP,cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3), & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,              & 
& cplcgWpgWpVZ,cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVWp,cplcVWpVPVWpVZ1,               & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP(2,2),cplHpcHpVPVZ(2,2),        & 
& cplHpcHpVZ(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2)

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
coupL2 = cplcFuFuVZL(i2,i1)
coupR2 = cplcFuFuVZR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*H0m2 & 
                & + 0.5_dp*(coupL1*coupR2 + coupL2*coupR1)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVP
coup2 = cplcgWpgWpVZ 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(VGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVP
coup2 = cplcgWCgWCVZ 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B22m2 = Real(VSSloop(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVP(i2,i1)
coup2 = cplHpcHpVZ(i1,i2)
    SumI = coup1*coup2*B22m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(VVSloop(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVP(i2)
coup2 = cplcHpVWpVZ(i2)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(VVSloop(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVPVWp(i1)
coup2 = cplHpcVWpVZ(i1)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(VVVloop(p2,MVWp2,MVWp2),dp) 
coup1 = cplcVWpVPVWp
coup2 = cplcVWpVWpVZ
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 SumI = 0._dp 
 A0m2 = SA_A0(MHp2(i1))
 coup1 = cplHpcHpVPVZ(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
      End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_A0(MVWp2) +RXi/4._dp*SA_A0(MVWp2*RXi) 
coup1 = cplcVWpVPVWpVZ2
coup2 = cplcVWpVPVWpVZ1
coup3 = cplcVWpVPVWpVZ3
SumI = ((2._dp*rMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVPVZ 
 
Subroutine DerPi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,          & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,           & 
& cplcVWpVPVWp,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,             & 
& cplHpcHpVP,cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3), & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,              & 
& cplcgWpgWpVZ,cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVWp,cplcVWpVPVWpVZ1,               & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP(2,2),cplHpcHpVPVZ(2,2),        & 
& cplHpcHpVZ(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFd2(i1),MFd2(i2)),dp) 
B0m2 = 2._dp*MFd(i1)*MFd(i2)*Real(SA_DerB0(p2,MFd2(i1),MFd2(i2)),dp) 
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
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFe2(i1),MFe2(i2)),dp) 
B0m2 = 2._dp*MFe(i1)*MFe(i2)*Real(SA_DerB0(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVPL(i1,i2)
coupR1 = cplcFeFeVPR(i1,i2)
coupL2 = cplcFeFeVZL(i2,i1)
coupR2 = cplcFeFeVZR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*H0m2 & 
                & + 0.5_dp*(coupL1*coupR2 + coupL2*coupR1)*B0m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 H0m2 = Real(SA_DerHloop(p2,MFu2(i1),MFu2(i2)),dp) 
B0m2 = 2._dp*MFu(i1)*MFu(i2)*Real(SA_DerB0(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVPL(i1,i2)
coupR1 = cplcFuFuVPR(i1,i2)
coupL2 = cplcFuFuVZL(i2,i1)
coupR2 = cplcFuFuVZR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*H0m2 & 
                & + 0.5_dp*(coupL1*coupR2 + coupL2*coupR1)*B0m2 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWpgWpVP
coup2 = cplcgWpgWpVZ 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(DerVGGloop(p2,MVWp2,MVWp2),dp)
coup1 = cplcgWCgWCVP
coup2 = cplcgWCgWCVZ 
   SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 B22m2 = Real(DerVSSloop(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVP(i2,i1)
coup2 = cplHpcHpVZ(i1,i2)
    SumI = coup1*coup2*B22m2 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 B0m2 = Real(DerVVSloop(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVP(i2)
coup2 = cplcHpVWpVZ(i2)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 B0m2 = Real(DerVVSloop(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVPVWp(i1)
coup2 = cplHpcVWpVZ(i1)
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
B0m2 = Real(DerVVVloop(p2,MVWp2,MVWp2),dp) 
coup1 = cplcVWpVPVWp
coup2 = cplcVWpVWpVZ
    SumI = coup1*coup2*B0m2 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp] 
!------------------------ 
    Do i1 = 1, 2
 SumI = 0._dp 
 A0m2 = SA_DerA0(MHp2(i1))
 coup1 = cplHpcHpVPVZ(i1,i1)
 SumI = coup1*A0m2 
res = res +1* SumI  
      End Do 
 !------------------------ 
! conj[VWp] 
!------------------------ 
SumI = 0._dp 
A0m2 = 3._dp/4._dp*SA_DerA0(MVWp2) +RXi/4._dp*SA_DerA0(MVWp2*RXi) 
coup1 = cplcVWpVPVWpVZ2
coup2 = cplcVWpVPVWpVZ1
coup3 = cplcVWpVPVWpVZ3
SumI = ((2._dp*DerrMS*coup1+(1-RXi**2)/8._dp*(coup2+coup3))*MVWp2-(4._dp*coup1+coup2+coup3)*A0m2)
res = res +1* SumI  
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVPVZ 
 
Subroutine Pi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,               & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,        & 
& cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,              & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,              & 
& cplG0hhVZ,cplG0HpcVWp,cplhhVZVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0VZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWCG0,      & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ(2),cplG0cHpVWp(2),cplG0G0hh,        & 
& cplG0hhVZ,cplG0HpcVWp(2),cplhhVZVZ,cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MA02,MH02),dp) 
B1m2 = Real(SA_B1(p2,MA02,MH02),dp) 
coup1 = cplA0H0VZ
coup2 = cplA0G0H0
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MFd2(i1),MFd2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
coupL2 = cplcFdFdG0L(i2,i1)
coupR2 = cplcFdFdG0R(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFd(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFd(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MFe2(i1),MFe2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
coupL2 = cplcFeFeG0L(i2,i1)
coupR2 = cplcFeFeG0R(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFe(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFe(i2)*B1m2  
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MFu2(i1),MFu2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
coupL2 = cplcFuFuG0L(i2,i1)
coupR2 = cplcFuFuG0R(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFu(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFu(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! hh, G0 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MG02,Mhh2),dp) 
B1m2 = Real(SA_B1(p2,MG02,Mhh2),dp) 
coup1 = cplG0hhVZ
coup2 = cplG0G0hh
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWpgWpVZ
coup2 = cplcgWpgWpG0 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWCgWCVZ
coup2 = cplcgWCgWCG0 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! VZ, hh 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVZ2,Mhh2),dp) 
B1m2 = Real(SA_B1(p2,MVZ2,Mhh2),dp) 
coup1 = cplhhVZVZ
coup2 = cplG0hhVZ
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +0.5_dp* SumI  
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplG0cHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplG0HpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 res = oo16pi2*res 
 
End Subroutine Pi1LoopVZG0 
 
Subroutine DerPi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,            & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,        & 
& cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,              & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,              & 
& cplG0hhVZ,cplG0HpcVWp,cplhhVZVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0G0H0,cplA0H0VZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWCG0,      & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ(2),cplG0cHpVWp(2),cplG0G0hh,        & 
& cplG0hhVZ,cplG0HpcVWp(2),cplhhVZVZ,cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MA02,MH02),dp) 
B1m2 = Real(SA_DerB1(p2,MA02,MH02),dp) 
coup1 = cplA0H0VZ
coup2 = cplA0G0H0
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MFd2(i1),MFd2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
coupL2 = cplcFdFdG0L(i2,i1)
coupR2 = cplcFdFdG0R(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFd(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFd(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MFe2(i1),MFe2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
coupL2 = cplcFeFeG0L(i2,i1)
coupR2 = cplcFeFeG0R(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFe(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFe(i2)*B1m2  
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MFu2(i1),MFu2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
coupL2 = cplcFuFuG0L(i2,i1)
coupR2 = cplcFuFuG0R(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFu(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFu(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! hh, G0 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MG02,Mhh2),dp) 
B1m2 = Real(SA_DerB1(p2,MG02,Mhh2),dp) 
coup1 = cplG0hhVZ
coup2 = cplG0G0hh
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWpgWpVZ
coup2 = cplcgWpgWpG0 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWCgWCVZ
coup2 = cplcgWCgWCG0 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! VZ, hh 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVZ2,Mhh2),dp) 
B1m2 = Real(SA_DerB1(p2,MVZ2,Mhh2),dp) 
coup1 = cplhhVZVZ
coup2 = cplG0hhVZ
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +0.5_dp* SumI  
!------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplG0cHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplG0HpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 res = oo16pi2*res 
 
End Subroutine DerPi1LoopVZG0 
 
Subroutine Pi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,               & 
& MHp,MHp2,MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,           & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,            & 
& cplcgWpgWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,             & 
& cplhhHpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MH0,MH02,MHp(2),MHp2(2),        & 
& MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0H0hh,cplA0H0VZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWChh,      & 
& cplcgWCgWCVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplhhcHpVWp(2),     & 
& cplhhcVWpVWp,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MA02,MH02),dp) 
B1m2 = Real(SA_B1(p2,MA02,MH02),dp) 
coup1 = cplA0H0VZ
coup2 = cplA0H0hh
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MFd2(i1),MFd2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
coupL2 = cplcFdFdhhL(i2,i1)
coupR2 = cplcFdFdhhR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFd(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFd(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MFe2(i1),MFe2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
coupL2 = cplcFeFehhL(i2,i1)
coupR2 = cplcFeFehhR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFe(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFe(i2)*B1m2  
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MFu2(i1),MFu2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
coupL2 = cplcFuFuhhL(i2,i1)
coupR2 = cplcFuFuhhR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFu(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFu(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWpgWpVZ
coup2 = cplcgWpgWphh 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWCgWCVZ
coup2 = cplcgWCgWChh 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MHp2(i2),MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVZ(i2,i1)
coup2 = cplhhHpcHp(i1,i2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplhhcHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplhhHpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MVWp2),dp)
B1m2 = Real(SA_B1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcVWpVWpVZ
coup2 = cplhhcVWpVWp
    SumI = coup1*coup2*(3._dp/2._dp*B0m2+3._dp*B1m2) 
End do 
res = res +1._dp* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVZhh 
 
Subroutine DerPi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,            & 
& MHp,MHp2,MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,           & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,            & 
& cplcgWpgWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,             & 
& cplhhHpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MH0,MH02,MHp(2),MHp2(2),        & 
& MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0H0hh,cplA0H0VZ,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWCgWChh,      & 
& cplcgWCgWCVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcHpVWpVZ(2),cplcVWpVWpVZ,cplhhcHpVWp(2),     & 
& cplhhcVWpVWp,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplHpcHpVZ(2,2),cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! H0, A0 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MA02,MH02),dp) 
B1m2 = Real(SA_DerB1(p2,MA02,MH02),dp) 
coup1 = cplA0H0VZ
coup2 = cplA0H0hh
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[Fd], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MFd2(i1),MFd2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFd2(i1),MFd2(i2)),dp) 
coupL1 = cplcFdFdVZL(i1,i2)
coupR1 = cplcFdFdVZR(i1,i2)
coupL2 = cplcFdFdhhL(i2,i1)
coupR2 = cplcFdFdhhR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFd(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFd(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fe], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MFe2(i1),MFe2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFe2(i1),MFe2(i2)),dp) 
coupL1 = cplcFeFeVZL(i1,i2)
coupR1 = cplcFeFeVZR(i1,i2)
coupL2 = cplcFeFehhL(i2,i1)
coupR2 = cplcFeFehhR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFe(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFe(i2)*B1m2  
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fu], Fu 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MFu2(i1),MFu2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFu2(i1),MFu2(i2)),dp) 
coupL1 = cplcFuFuVZL(i1,i2)
coupR1 = cplcFuFuVZR(i1,i2)
coupL2 = cplcFuFuhhL(i2,i1)
coupR2 = cplcFuFuhhR(i2,i1)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFu(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFu(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gWp], gWp 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWpgWpVZ
coup2 = cplcgWpgWphh 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWpC], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVWp2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcgWCgWCVZ
coup2 = cplcgWCgWChh 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MHp2(i2),MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVZ(i2,i1)
coup2 = cplhhHpcHp(i1,i2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplhhcHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplhhHpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VWp 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVWp2),dp)
B1m2 = Real(SA_DerB1(p2,MVWp2,MVWp2),dp) 
coup1 = cplcVWpVWpVZ
coup2 = cplhhcVWpVWp
    SumI = coup1*coup2*(3._dp/2._dp*B0m2+3._dp*B1m2) 
End do 
res = res +1._dp* SumI  
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVZhh 
 
Subroutine Pi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,     & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0cHpVWp(2),cplA0HpcHp(2,2),cplA0HpcVWp(2),cplcHpVWpVZ(2),cplHpcHpVZ(2,2),         & 
& cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MHp2(i2),MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVZ(i2,i1)
coup2 = cplA0HpcHp(i1,i2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplA0cHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplA0HpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 res = oo16pi2*res 
 
End Subroutine Pi1LoopVZA0 
 
Subroutine DerPi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,              & 
& cplA0HpcVWp,cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplA0cHpVWp(2),cplA0HpcHp(2,2),cplA0HpcVWp(2),cplcHpVWpVZ(2),cplHpcHpVZ(2,2),         & 
& cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MHp2(i2),MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVZ(i2,i1)
coup2 = cplA0HpcHp(i1,i2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplA0cHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplA0HpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 res = oo16pi2*res 
 
End Subroutine DerPi1LoopVZA0 
 
Subroutine Pi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,     & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcHpVWpVZ(2),cplH0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplHpcHpVZ(2,2),         & 
& cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MHp2(i2),MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVZ(i2,i1)
coup2 = cplH0HpcHp(i1,i2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplH0cHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_B0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplH0HpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 res = oo16pi2*res 
 
End Subroutine Pi1LoopVZH0 
 
Subroutine DerPi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,             & 
& cplH0HpcHp,cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MHp(2),MHp2(2),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcHpVWpVZ(2),cplH0cHpVWp(2),cplH0HpcHp(2,2),cplH0HpcVWp(2),cplHpcHpVZ(2,2),         & 
& cplHpcVWpVZ(2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! conj[Hp], Hp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
       Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MHp2(i2),MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MHp2(i2),MHp2(i1)),dp) 
coup1 = cplHpcHpVZ(i2,i1)
coup2 = cplH0HpcHp(i1,i2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! conj[VWp], Hp 
!------------------------ 
sumI = 0._dp 
 
      Do i2 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i2)),dp) 
coup1 = cplHpcVWpVZ(i2)
coup2 = cplH0cHpVWp(i2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
    End Do 
 !------------------------ 
! conj[Hp], VWp 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,1 
B0m2 = Real(SA_DerB0(p2,MVWp2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplH0HpcVWp(i1)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 res = oo16pi2*res 
 
End Subroutine DerPi1LoopVZH0 
 
Subroutine Pi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,              & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,             & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,         & 
& cplcFvFeVWpR,cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,         & 
& cplcgZgWpcHp,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,            & 
& cplH0HpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MH0,MH02,Mhh,Mhh2,              & 
& MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0cHpVWp(2),cplA0HpcHp(2,2),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),               & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),           & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcgAgWCVWp,cplcgWCgAcHp(2),cplcgWCgZcHp(2),      & 
& cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),               & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp(2),cplH0HpcHp(2,2),cplhhcHpVWp(2),               & 
& cplhhcVWpVWp,cplhhHpcHp(2,2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res(2) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
res = 0._dp 
 
!------------------------ 
! conj[Hp], A0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MA02,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MA02,MHp2(i1)),dp) 
coup1 = cplA0cHpVWp(i1)
coup2 = cplA0HpcHp(i1,gO2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! bar[Fu], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MFu2(i1),MFd2(i2)),dp) 
B1m2 = Real(SA_B1(p2,MFu2(i1),MFd2(i2)),dp) 
coupL1 = cplcFuFdVWpL(i1,i2)
coupR1 = cplcFuFdVWpR(i1,i2)
coupL2 = cplcFdFucHpL(i2,i1,gO2)
coupR2 = cplcFdFucHpR(i2,i1,gO2)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFu(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFd(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fv], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,0._dp,MFe2(i2)),dp) 
B1m2 = Real(SA_B1(p2,0._dp,MFe2(i2)),dp) 
coupL1 = cplcFvFeVWpL(i1,i2)
coupR1 = cplcFvFeVWpR(i1,i2)
coupL2 = cplcFeFvcHpL(i2,i1,gO2)
coupR2 = cplcFeFvcHpR(i2,i1,gO2)
    SumI = (coupL1*coupL2+coupR1*coupR2)*0._dp*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFe(i2)*B1m2  
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gP], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVWp2,0._dp),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,0._dp),dp) 
coup1 = cplcgAgWCVWp
coup2 = cplcgWCgAcHp(gO2) 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVWp2,MVZ2),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,MVZ2),dp) 
coup1 = cplcgZgWCVWp
coup2 = cplcgWCgZcHp(gO2) 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gZ 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVZ2,MVWp2),dp) 
B1m2 = Real(SA_B1(p2,MVZ2,MVWp2),dp) 
coup1 = cplcgWpgZVWp
coup2 = cplcgZgWpcHp(gO2) 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], H0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MH02,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MH02,MHp2(i1)),dp) 
coup1 = cplH0cHpVWp(i1)
coup2 = cplH0HpcHp(i1,gO2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[Hp], hh 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,Mhh2,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,Mhh2,MHp2(i1)),dp) 
coup1 = cplhhcHpVWp(i1)
coup2 = cplhhHpcHp(i1,gO2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], hh 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVWp2,Mhh2),dp) 
B1m2 = Real(SA_B1(p2,MVWp2,Mhh2),dp) 
coup1 = cplhhcVWpVWp
coup2 = cplhhcHpVWp(gO2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], VP 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,0._dp,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,0._dp,MHp2(i1)),dp) 
coup1 = cplcHpVPVWp(i1)
coup2 = cplHpcHpVP(i1,gO2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VP 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVWp2,0._dp),dp)
B1m2 = Real(SA_B1(p2,MVWp2,0._dp),dp) 
coup1 = cplcVWpVPVWp
coup2 = cplcHpVPVWp(gO2)
    SumI = coup1*coup2*(3._dp/2._dp*B0m2+3._dp*B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], VZ 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVZ2,MHp2(i1)),dp) 
B1m2 = Real(SA_B1(p2,MVZ2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplHpcHpVZ(i1,gO2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VZ 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_B0(p2,MVWp2,MVZ2),dp)
B1m2 = Real(SA_B1(p2,MVWp2,MVZ2),dp) 
coup1 = cplcVWpVWpVZ
coup2 = cplcHpVWpVZ(gO2)
    SumI = coup1*coup2*(3._dp/2._dp*B0m2+3._dp*B1m2) 
End do 
res = res +1._dp* SumI  
res = oo16pi2*res 
 
End Subroutine Pi1LoopVWpHp 
 
Subroutine DerPi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,           & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,             & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,         & 
& cplcFvFeVWpR,cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,         & 
& cplcgZgWpcHp,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,            & 
& cplH0HpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,res)

Implicit None 
Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MH0,MH02,Mhh,Mhh2,              & 
& MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplA0cHpVWp(2),cplA0HpcHp(2,2),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),               & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),           & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcgAgWCVWp,cplcgWCgAcHp(2),cplcgWCgZcHp(2),      & 
& cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),               & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp(2),cplH0HpcHp(2,2),cplhhcHpVWp(2),               & 
& cplhhcVWpVWp,cplhhHpcHp(2,2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2)

Integer, Intent(inout) :: kont 
Real(dp) :: B0m2, F0m2, G0m2, B1m2, H0m2, B22m2, m1, m2 
Real(dp), Intent(in) :: p2 
Complex(dp) :: A0m2 
Complex(dp), Intent(inout) :: res(2) 
Complex(dp) :: coupL1, coupR1, coupL2,coupR2, coup1,coup2, coup3, temp, sumI 
Integer :: i1,i2,i3,i4, gO1, gO2, ierr 
 
 
Real(dp) ::MVG,MVP,MVG2,MVP2
MVG = Mass_Regulator_PhotonGluon 
MVP = Mass_Regulator_PhotonGluon 
MVG2 = Mass_Regulator_PhotonGluon**2 
MVP2 = Mass_Regulator_PhotonGluon**2 

res = 0._dp 
 
!------------------------ 
! conj[Hp], A0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MA02,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MA02,MHp2(i1)),dp) 
coup1 = cplA0cHpVWp(i1)
coup2 = cplA0HpcHp(i1,gO2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! bar[Fu], Fd 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MFu2(i1),MFd2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,MFu2(i1),MFd2(i2)),dp) 
coupL1 = cplcFuFdVWpL(i1,i2)
coupR1 = cplcFuFdVWpR(i1,i2)
coupL2 = cplcFdFucHpL(i2,i1,gO2)
coupR2 = cplcFdFucHpR(i2,i1,gO2)
    SumI = (coupL1*coupL2+coupR1*coupR2)*MFu(i1)*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFd(i2)*B1m2  
End do 
res = res +3._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[Fv], Fe 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 3
       Do i2 = 1, 3
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,0._dp,MFe2(i2)),dp) 
B1m2 = Real(SA_DerB1(p2,0._dp,MFe2(i2)),dp) 
coupL1 = cplcFvFeVWpL(i1,i2)
coupR1 = cplcFvFeVWpR(i1,i2)
coupL2 = cplcFeFvcHpL(i2,i1,gO2)
coupR2 = cplcFeFvcHpR(i2,i1,gO2)
    SumI = (coupL1*coupL2+coupR1*coupR2)*0._dp*(B0m2+B1m2) & 
  & + (coupL1*coupR2+coupR1*coupL2)*MFe(i2)*B1m2  
End do 
res = res +1._dp* SumI  
      End Do 
     End Do 
 !------------------------ 
! bar[gP], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVP2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MVP2),dp) 
coup1 = cplcgAgWCVWp
coup2 = cplcgWCgAcHp(gO2) 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gZ], gWpC 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVZ2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,MVZ2),dp) 
coup1 = cplcgZgWCVWp
coup2 = cplcgWCgZcHp(gO2) 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! bar[gWp], gZ 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVZ2,MVWp2),dp) 
B1m2 = Real(SA_DerB1(p2,MVZ2,MVWp2),dp) 
coup1 = cplcgWpgZVWp
coup2 = cplcgZgWpcHp(gO2) 
   SumI = -0.5_dp*coup1*coup2*(B0m2+B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], H0 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MH02,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MH02,MHp2(i1)),dp) 
coup1 = cplH0cHpVWp(i1)
coup2 = cplH0HpcHp(i1,gO2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[Hp], hh 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,Mhh2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,Mhh2,MHp2(i1)),dp) 
coup1 = cplhhcHpVWp(i1)
coup2 = cplhhHpcHp(i1,gO2)
    SumI = -coup1*coup2*(B1m2+0.5_dp*B0m2)
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], hh 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVWp2,Mhh2),dp) 
B1m2 = Real(SA_DerB1(p2,MVWp2,Mhh2),dp) 
coup1 = cplhhcVWpVWp
coup2 = cplhhcHpVWp(gO2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], VP 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVP2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MVP2,MHp2(i1)),dp) 
coup1 = cplcHpVPVWp(i1)
coup2 = cplHpcHpVP(i1,gO2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VP 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVP2),dp)
B1m2 = Real(SA_DerB1(p2,MVWp2,MVP2),dp) 
coup1 = cplcVWpVPVWp
coup2 = cplcHpVPVWp(gO2)
    SumI = coup1*coup2*(3._dp/2._dp*B0m2+3._dp*B1m2) 
End do 
res = res +1._dp* SumI  
!------------------------ 
! conj[Hp], VZ 
!------------------------ 
sumI = 0._dp 
 
    Do i1 = 1, 2
 Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVZ2,MHp2(i1)),dp) 
B1m2 = Real(SA_DerB1(p2,MVZ2,MHp2(i1)),dp) 
coup1 = cplcHpVWpVZ(i1)
coup2 = cplHpcHpVZ(i1,gO2)
    SumI = coup1*coup2*(B1m2-B0m2) 
End do 
res = res +1._dp* SumI  
      End Do 
 !------------------------ 
! conj[VWp], VZ 
!------------------------ 
sumI = 0._dp 
 
Do gO2=1,2 
B0m2 = Real(SA_DerB0(p2,MVWp2,MVZ2),dp)
B1m2 = Real(SA_DerB1(p2,MVWp2,MVZ2),dp) 
coup1 = cplcVWpVWpVZ
coup2 = cplcHpVWpVZ(gO2)
    SumI = coup1*coup2*(3._dp/2._dp*B0m2+3._dp*B1m2) 
End do 
res = res +1._dp* SumI  
res = oo16pi2*res 
 
End Subroutine DerPi1LoopVWpHp 
 
End Module LoopMasses_Inert2 
