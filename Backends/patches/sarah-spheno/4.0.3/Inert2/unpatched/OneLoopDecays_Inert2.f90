! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecays_Inert2 
Use Couplings_Inert2 
Use CouplingsCT_Inert2 
Use Model_Data_Inert2 
Use LoopCouplings_Inert2 
Use LoopMasses_Inert2 
Use RGEs_Inert2 
Use Tadpoles_Inert2 
Use Kinematics 
Use CouplingsForDecays_Inert2 
 
Use Wrapper_OneLoopDecay_Fu_Inert2 
Use Wrapper_OneLoopDecay_Fe_Inert2 
Use Wrapper_OneLoopDecay_Fd_Inert2 
Use Wrapper_OneLoopDecay_hh_Inert2 
Use Wrapper_OneLoopDecay_H0_Inert2 
Use Wrapper_OneLoopDecay_A0_Inert2 
Use Wrapper_OneLoopDecay_Hp_Inert2 

 
Contains 
 
Subroutine getZCouplings(lam5,v,lam3,lam4,ZP,lam1,lam2,g1,g2,TW,g3,Yd,ZDL,            & 
& ZDR,Yu,ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,          & 
& cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0A0A0A0,             & 
& cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplA0G0G0H0,              & 
& cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,cplG0G0H0H0,             & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,cplH0H0hhhh,             & 
& cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,cplA0H0VZ,            & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0HpcVWpVP,          & 
& cplA0HpcVWpVZ,cplA0cHpVPVWp,cplA0cHpVWpVZ,cplG0G0cVWpVWp,cplG0G0VZVZ,cplG0HpcVWpVP,    & 
& cplG0HpcVWpVZ,cplG0cHpVPVWp,cplG0cHpVWpVZ,cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP,    & 
& cplH0HpcVWpVZ,cplH0cHpVPVWp,cplH0cHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP,    & 
& cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,cplHpcHpcVWpVWp,   & 
& cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,cplcFdFdG0R,              & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,cplcFeFeG0R,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,cplcFuFuG0R,               & 
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
& cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,cplcgWCgWCG0,cplcgZgAhh,          & 
& cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,           & 
& cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,          & 
& ZRUZER,ZcplA0A0G0,ZcplA0A0hh,ZcplA0G0H0,ZcplA0H0hh,ZcplA0HpcHp,ZcplG0G0hh,             & 
& ZcplG0H0H0,ZcplH0H0hh,ZcplH0HpcHp,Zcplhhhhhh,ZcplhhHpcHp,ZcplA0A0A0A0,ZcplA0A0G0G0,    & 
& ZcplA0A0G0hh,ZcplA0A0H0H0,ZcplA0A0hhhh,ZcplA0A0HpcHp,ZcplA0G0G0H0,ZcplA0G0H0hh,        & 
& ZcplA0G0HpcHp,ZcplA0H0hhhh,ZcplA0hhHpcHp,ZcplG0G0G0G0,ZcplG0G0H0H0,ZcplG0G0hhhh,       & 
& ZcplG0G0HpcHp,ZcplG0H0H0hh,ZcplG0H0HpcHp,ZcplH0H0H0H0,ZcplH0H0hhhh,ZcplH0H0HpcHp,      & 
& ZcplH0hhHpcHp,Zcplhhhhhhhh,ZcplhhhhHpcHp,ZcplHpHpcHpcHp,ZcplA0H0VZ,ZcplA0HpcVWp,       & 
& ZcplA0cHpVWp,ZcplG0hhVZ,ZcplG0HpcVWp,ZcplG0cHpVWp,ZcplH0HpcVWp,ZcplH0cHpVWp,           & 
& ZcplhhHpcVWp,ZcplhhcHpVWp,ZcplHpcHpVP,ZcplHpcHpVZ,ZcplhhcVWpVWp,ZcplhhVZVZ,            & 
& ZcplHpcVWpVP,ZcplHpcVWpVZ,ZcplcHpVPVWp,ZcplcHpVWpVZ,ZcplA0A0cVWpVWp,ZcplA0A0VZVZ,      & 
& ZcplA0HpcVWpVP,ZcplA0HpcVWpVZ,ZcplA0cHpVPVWp,ZcplA0cHpVWpVZ,ZcplG0G0cVWpVWp,           & 
& ZcplG0G0VZVZ,ZcplG0HpcVWpVP,ZcplG0HpcVWpVZ,ZcplG0cHpVPVWp,ZcplG0cHpVWpVZ,              & 
& ZcplH0H0cVWpVWp,ZcplH0H0VZVZ,ZcplH0HpcVWpVP,ZcplH0HpcVWpVZ,ZcplH0cHpVPVWp,             & 
& ZcplH0cHpVWpVZ,ZcplhhhhcVWpVWp,ZcplhhhhVZVZ,ZcplhhHpcVWpVP,ZcplhhHpcVWpVZ,             & 
& ZcplhhcHpVPVWp,ZcplhhcHpVWpVZ,ZcplHpcHpVPVP,ZcplHpcHpVPVZ,ZcplHpcHpcVWpVWp,            & 
& ZcplHpcHpVZVZ,ZcplVGVGVG,ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplcFdFdG0L,ZcplcFdFdG0R,        & 
& ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFeFeG0L,ZcplcFeFeG0R,         & 
& ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFvFeHpL,ZcplcFvFeHpR,ZcplcFuFuG0L,ZcplcFuFuG0R,         & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFeFvcHpL,ZcplcFeFvcHpR,     & 
& ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,       & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFvFeVWpL,ZcplcFvFeVWpR,       & 
& ZcplcFeFeVZL,ZcplcFeFeVZR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,         & 
& ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplcFvFvVZL,ZcplcFvFvVZR,     & 
& ZcplcFeFvcVWpL,ZcplcFeFvcVWpR,ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,               & 
& ZcplcVWpVPVPVWp1,ZcplcVWpVPVPVWp2,ZcplcVWpVPVPVWp3,ZcplcVWpVPVWpVZ1,ZcplcVWpVPVWpVZ2,  & 
& ZcplcVWpVPVWpVZ3,ZcplcVWpcVWpVWpVWp1,ZcplcVWpcVWpVWpVWp2,ZcplcVWpcVWpVWpVWp3,          & 
& ZcplcVWpVWpVZVZ1,ZcplcVWpVWpVZVZ2,ZcplcVWpVWpVZVZ3,ZcplcgGgGVG,ZcplcgWpgAVWp,          & 
& ZcplcgWCgAcVWp,ZcplcgWpgWpVP,ZcplcgWpgWpVZ,ZcplcgAgWpcVWp,ZcplcgZgWpcVWp,              & 
& ZcplcgWCgWCVP,ZcplcgAgWCVWp,ZcplcgZgWCVWp,ZcplcgWCgWCVZ,ZcplcgWpgZVWp,ZcplcgWCgZcVWp,  & 
& ZcplcgWpgWpG0,ZcplcgWCgWCG0,ZcplcgZgAhh,ZcplcgWpgAHp,ZcplcgWCgAcHp,ZcplcgWpgWphh,      & 
& ZcplcgZgWpcHp,ZcplcgWCgWChh,ZcplcgZgWCHp,ZcplcgZgZhh,ZcplcgWpgZHp,ZcplcgWCgZcHp)

Implicit None

Real(dp), Intent(in) :: v,ZP(2,2),g1,g2,TW,g3

Complex(dp), Intent(in) :: lam5,lam3,lam4,lam1,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),         & 
& Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplA0A0A0A0,cplA0A0G0G0,           & 
& cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0G0G0H0,cplA0G0H0hh,         & 
& cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),cplG0G0G0G0,cplG0G0H0H0,               & 
& cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),cplH0H0H0H0,               & 
& cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,cplhhhhHpcHp(2,2),         & 
& cplHpHpcHpcHp(2,2,2,2),cplA0H0VZ,cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcVWp(2),            & 
& cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP(2),  & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0cVWpVWp,cplA0A0VZVZ,               & 
& cplA0HpcVWpVP(2),cplA0HpcVWpVZ(2),cplA0cHpVPVWp(2),cplA0cHpVWpVZ(2),cplG0G0cVWpVWp,    & 
& cplG0G0VZVZ,cplG0HpcVWpVP(2),cplG0HpcVWpVZ(2),cplG0cHpVPVWp(2),cplG0cHpVWpVZ(2),       & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP(2),cplH0HpcVWpVZ(2),cplH0cHpVPVWp(2),         & 
& cplH0cHpVWpVZ(2),cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP(2),cplhhHpcVWpVZ(2),         & 
& cplhhcHpVPVWp(2),cplhhcHpVWpVZ(2),cplHpcHpVPVP(2,2),cplHpcHpVPVZ(2,2),cplHpcHpcVWpVWp(2,2),& 
& cplHpcHpVZVZ(2,2),cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),& 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),               & 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3), & 
& cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3), & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVGL(3,3),& 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,          & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,       & 
& cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,               & 
& cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,      & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,        & 
& cplcgWCgWCG0,cplcgZgAhh,cplcgWpgAHp(2),cplcgWCgAcHp(2),cplcgWpgWphh,cplcgZgWpcHp(2),   & 
& cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcHp(2)

Complex(dp), Intent(in) :: ZRUZP(2,2),ZRUZDL(3,3),ZRUZDR(3,3),ZRUZUL(3,3),ZRUZUR(3,3),ZRUZEL(3,3),               & 
& ZRUZER(3,3)

Integer :: gt1, gt2
Complex(dp) :: TempcplA0A0G0,TempcplA0A0hh,TempcplA0G0H0,TempcplA0H0hh,TempcplA0HpcHp(2,2),          & 
& TempcplG0G0hh,TempcplG0H0H0,TempcplH0H0hh,TempcplH0HpcHp(2,2),Tempcplhhhhhh,           & 
& TempcplhhHpcHp(2,2),TempcplA0A0A0A0,TempcplA0A0G0G0,TempcplA0A0G0hh,TempcplA0A0H0H0,   & 
& TempcplA0A0hhhh,TempcplA0A0HpcHp(2,2),TempcplA0G0G0H0,TempcplA0G0H0hh,TempcplA0G0HpcHp(2,2),& 
& TempcplA0H0hhhh,TempcplA0hhHpcHp(2,2),TempcplG0G0G0G0,TempcplG0G0H0H0,TempcplG0G0hhhh, & 
& TempcplG0G0HpcHp(2,2),TempcplG0H0H0hh,TempcplG0H0HpcHp(2,2),TempcplH0H0H0H0,           & 
& TempcplH0H0hhhh,TempcplH0H0HpcHp(2,2),TempcplH0hhHpcHp(2,2),Tempcplhhhhhhhh,           & 
& TempcplhhhhHpcHp(2,2),TempcplHpHpcHpcHp(2,2,2,2),TempcplA0H0VZ,TempcplA0HpcVWp(2),     & 
& TempcplA0cHpVWp(2),TempcplG0hhVZ,TempcplG0HpcVWp(2),TempcplG0cHpVWp(2),TempcplH0HpcVWp(2),& 
& TempcplH0cHpVWp(2),TempcplhhHpcVWp(2),TempcplhhcHpVWp(2),TempcplHpcHpVP(2,2),          & 
& TempcplHpcHpVZ(2,2),TempcplhhcVWpVWp,TempcplhhVZVZ,TempcplHpcVWpVP(2),TempcplHpcVWpVZ(2),& 
& TempcplcHpVPVWp(2),TempcplcHpVWpVZ(2),TempcplA0A0cVWpVWp,TempcplA0A0VZVZ,              & 
& TempcplA0HpcVWpVP(2),TempcplA0HpcVWpVZ(2),TempcplA0cHpVPVWp(2),TempcplA0cHpVWpVZ(2),   & 
& TempcplG0G0cVWpVWp,TempcplG0G0VZVZ,TempcplG0HpcVWpVP(2),TempcplG0HpcVWpVZ(2),          & 
& TempcplG0cHpVPVWp(2),TempcplG0cHpVWpVZ(2),TempcplH0H0cVWpVWp,TempcplH0H0VZVZ,          & 
& TempcplH0HpcVWpVP(2),TempcplH0HpcVWpVZ(2),TempcplH0cHpVPVWp(2),TempcplH0cHpVWpVZ(2),   & 
& TempcplhhhhcVWpVWp,TempcplhhhhVZVZ,TempcplhhHpcVWpVP(2),TempcplhhHpcVWpVZ(2),          & 
& TempcplhhcHpVPVWp(2),TempcplhhcHpVWpVZ(2),TempcplHpcHpVPVP(2,2),TempcplHpcHpVPVZ(2,2), & 
& TempcplHpcHpcVWpVWp(2,2),TempcplHpcHpVZVZ(2,2),TempcplVGVGVG,TempcplcVWpVPVWp,         & 
& TempcplcVWpVWpVZ,TempcplcFdFdG0L(3,3),TempcplcFdFdG0R(3,3),TempcplcFdFdhhL(3,3),       & 
& TempcplcFdFdhhR(3,3),TempcplcFuFdHpL(3,3,2),TempcplcFuFdHpR(3,3,2),TempcplcFeFeG0L(3,3),& 
& TempcplcFeFeG0R(3,3),TempcplcFeFehhL(3,3),TempcplcFeFehhR(3,3),TempcplcFvFeHpL(3,3,2), & 
& TempcplcFvFeHpR(3,3,2),TempcplcFuFuG0L(3,3),TempcplcFuFuG0R(3,3),TempcplcFuFuhhL(3,3), & 
& TempcplcFuFuhhR(3,3),TempcplcFdFucHpL(3,3,2),TempcplcFdFucHpR(3,3,2),TempcplcFeFvcHpL(3,3,2),& 
& TempcplcFeFvcHpR(3,3,2),TempcplcFdFdVGL(3,3),TempcplcFdFdVGR(3,3),TempcplcFdFdVPL(3,3),& 
& TempcplcFdFdVPR(3,3),TempcplcFuFdVWpL(3,3),TempcplcFuFdVWpR(3,3),TempcplcFdFdVZL(3,3), & 
& TempcplcFdFdVZR(3,3),TempcplcFeFeVPL(3,3),TempcplcFeFeVPR(3,3),TempcplcFvFeVWpL(3,3),  & 
& TempcplcFvFeVWpR(3,3),TempcplcFeFeVZL(3,3),TempcplcFeFeVZR(3,3),TempcplcFuFuVGL(3,3),  & 
& TempcplcFuFuVGR(3,3),TempcplcFuFuVPL(3,3),TempcplcFuFuVPR(3,3),TempcplcFuFuVZL(3,3),   & 
& TempcplcFuFuVZR(3,3),TempcplcFdFucVWpL(3,3),TempcplcFdFucVWpR(3,3),TempcplcFvFvVZL(3,3),& 
& TempcplcFvFvVZR(3,3),TempcplcFeFvcVWpL(3,3),TempcplcFeFvcVWpR(3,3),TempcplVGVGVGVG1,   & 
& TempcplVGVGVGVG2,TempcplVGVGVGVG3,TempcplcVWpVPVPVWp1,TempcplcVWpVPVPVWp2,             & 
& TempcplcVWpVPVPVWp3,TempcplcVWpVPVWpVZ1,TempcplcVWpVPVWpVZ2,TempcplcVWpVPVWpVZ3,       & 
& TempcplcVWpcVWpVWpVWp1,TempcplcVWpcVWpVWpVWp2,TempcplcVWpcVWpVWpVWp3,TempcplcVWpVWpVZVZ1,& 
& TempcplcVWpVWpVZVZ2,TempcplcVWpVWpVZVZ3,TempcplcgGgGVG,TempcplcgWpgAVWp,               & 
& TempcplcgWCgAcVWp,TempcplcgWpgWpVP,TempcplcgWpgWpVZ,TempcplcgAgWpcVWp,TempcplcgZgWpcVWp,& 
& TempcplcgWCgWCVP,TempcplcgAgWCVWp,TempcplcgZgWCVWp,TempcplcgWCgWCVZ,TempcplcgWpgZVWp

Complex(dp) :: TempcplcgWCgZcVWp,TempcplcgWpgWpG0,TempcplcgWCgWCG0,TempcplcgZgAhh,TempcplcgWpgAHp(2), & 
& TempcplcgWCgAcHp(2),TempcplcgWpgWphh,TempcplcgZgWpcHp(2),TempcplcgWCgWChh,             & 
& TempcplcgZgWCHp(2),TempcplcgZgZhh,TempcplcgWpgZHp(2),TempcplcgWCgZcHp(2)

Complex(dp), Intent(out) :: ZcplA0A0G0,ZcplA0A0hh,ZcplA0G0H0,ZcplA0H0hh,ZcplA0HpcHp(2,2),ZcplG0G0hh,              & 
& ZcplG0H0H0,ZcplH0H0hh,ZcplH0HpcHp(2,2),Zcplhhhhhh,ZcplhhHpcHp(2,2),ZcplA0A0A0A0,       & 
& ZcplA0A0G0G0,ZcplA0A0G0hh,ZcplA0A0H0H0,ZcplA0A0hhhh,ZcplA0A0HpcHp(2,2),ZcplA0G0G0H0,   & 
& ZcplA0G0H0hh,ZcplA0G0HpcHp(2,2),ZcplA0H0hhhh,ZcplA0hhHpcHp(2,2),ZcplG0G0G0G0,          & 
& ZcplG0G0H0H0,ZcplG0G0hhhh,ZcplG0G0HpcHp(2,2),ZcplG0H0H0hh,ZcplG0H0HpcHp(2,2),          & 
& ZcplH0H0H0H0,ZcplH0H0hhhh,ZcplH0H0HpcHp(2,2),ZcplH0hhHpcHp(2,2),Zcplhhhhhhhh,          & 
& ZcplhhhhHpcHp(2,2),ZcplHpHpcHpcHp(2,2,2,2),ZcplA0H0VZ,ZcplA0HpcVWp(2),ZcplA0cHpVWp(2), & 
& ZcplG0hhVZ,ZcplG0HpcVWp(2),ZcplG0cHpVWp(2),ZcplH0HpcVWp(2),ZcplH0cHpVWp(2),            & 
& ZcplhhHpcVWp(2),ZcplhhcHpVWp(2),ZcplHpcHpVP(2,2),ZcplHpcHpVZ(2,2),ZcplhhcVWpVWp,       & 
& ZcplhhVZVZ,ZcplHpcVWpVP(2),ZcplHpcVWpVZ(2),ZcplcHpVPVWp(2),ZcplcHpVWpVZ(2),            & 
& ZcplA0A0cVWpVWp,ZcplA0A0VZVZ,ZcplA0HpcVWpVP(2),ZcplA0HpcVWpVZ(2),ZcplA0cHpVPVWp(2),    & 
& ZcplA0cHpVWpVZ(2),ZcplG0G0cVWpVWp,ZcplG0G0VZVZ,ZcplG0HpcVWpVP(2),ZcplG0HpcVWpVZ(2),    & 
& ZcplG0cHpVPVWp(2),ZcplG0cHpVWpVZ(2),ZcplH0H0cVWpVWp,ZcplH0H0VZVZ,ZcplH0HpcVWpVP(2),    & 
& ZcplH0HpcVWpVZ(2),ZcplH0cHpVPVWp(2),ZcplH0cHpVWpVZ(2),ZcplhhhhcVWpVWp,ZcplhhhhVZVZ,    & 
& ZcplhhHpcVWpVP(2),ZcplhhHpcVWpVZ(2),ZcplhhcHpVPVWp(2),ZcplhhcHpVWpVZ(2),               & 
& ZcplHpcHpVPVP(2,2),ZcplHpcHpVPVZ(2,2),ZcplHpcHpcVWpVWp(2,2),ZcplHpcHpVZVZ(2,2),        & 
& ZcplVGVGVG,ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplcFdFdG0L(3,3),ZcplcFdFdG0R(3,3),            & 
& ZcplcFdFdhhL(3,3),ZcplcFdFdhhR(3,3),ZcplcFuFdHpL(3,3,2),ZcplcFuFdHpR(3,3,2),           & 
& ZcplcFeFeG0L(3,3),ZcplcFeFeG0R(3,3),ZcplcFeFehhL(3,3),ZcplcFeFehhR(3,3),               & 
& ZcplcFvFeHpL(3,3,2),ZcplcFvFeHpR(3,3,2),ZcplcFuFuG0L(3,3),ZcplcFuFuG0R(3,3),           & 
& ZcplcFuFuhhL(3,3),ZcplcFuFuhhR(3,3),ZcplcFdFucHpL(3,3,2),ZcplcFdFucHpR(3,3,2),         & 
& ZcplcFeFvcHpL(3,3,2),ZcplcFeFvcHpR(3,3,2),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),         & 
& ZcplcFdFdVPL(3,3),ZcplcFdFdVPR(3,3),ZcplcFuFdVWpL(3,3),ZcplcFuFdVWpR(3,3),             & 
& ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),ZcplcFeFeVPL(3,3),ZcplcFeFeVPR(3,3),               & 
& ZcplcFvFeVWpL(3,3),ZcplcFvFeVWpR(3,3),ZcplcFeFeVZL(3,3),ZcplcFeFeVZR(3,3),             & 
& ZcplcFuFuVGL(3,3),ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),               & 
& ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcFdFucVWpL(3,3),ZcplcFdFucVWpR(3,3),           & 
& ZcplcFvFvVZL(3,3),ZcplcFvFvVZR(3,3),ZcplcFeFvcVWpL(3,3),ZcplcFeFvcVWpR(3,3),           & 
& ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,ZcplcVWpVPVPVWp1,ZcplcVWpVPVPVWp2,           & 
& ZcplcVWpVPVPVWp3,ZcplcVWpVPVWpVZ1,ZcplcVWpVPVWpVZ2,ZcplcVWpVPVWpVZ3,ZcplcVWpcVWpVWpVWp1,& 
& ZcplcVWpcVWpVWpVWp2,ZcplcVWpcVWpVWpVWp3,ZcplcVWpVWpVZVZ1,ZcplcVWpVWpVZVZ2,             & 
& ZcplcVWpVWpVZVZ3,ZcplcgGgGVG,ZcplcgWpgAVWp,ZcplcgWCgAcVWp,ZcplcgWpgWpVP,               & 
& ZcplcgWpgWpVZ,ZcplcgAgWpcVWp,ZcplcgZgWpcVWp,ZcplcgWCgWCVP,ZcplcgAgWCVWp,               & 
& ZcplcgZgWCVWp,ZcplcgWCgWCVZ,ZcplcgWpgZVWp,ZcplcgWCgZcVWp,ZcplcgWpgWpG0,ZcplcgWCgWCG0,  & 
& ZcplcgZgAhh,ZcplcgWpgAHp(2),ZcplcgWCgAcHp(2),ZcplcgWpgWphh,ZcplcgZgWpcHp(2),           & 
& ZcplcgWCgWChh,ZcplcgZgWCHp(2),ZcplcgZgZhh,ZcplcgWpgZHp(2),ZcplcgWCgZcHp(2)

Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUZDLc(3, 3) 
Complex(dp) :: ZRUZDRc(3, 3) 
Complex(dp) :: ZRUZULc(3, 3) 
Complex(dp) :: ZRUZURc(3, 3) 
Complex(dp) :: ZRUZELc(3, 3) 
Complex(dp) :: ZRUZERc(3, 3) 
ZRUZPc = Conjg(ZRUZP)
ZRUZDLc = Conjg(ZRUZDL)
ZRUZDRc = Conjg(ZRUZDR)
ZRUZULc = Conjg(ZRUZUL)
ZRUZURc = Conjg(ZRUZUR)
ZRUZELc = Conjg(ZRUZEL)
ZRUZERc = Conjg(ZRUZER)


 ! ## ZcplA0A0G0 ## 
ZcplA0A0G0 = 0._dp 
TempcplA0A0G0 = cplA0A0G0 
ZcplA0A0G0 = TempcplA0A0G0 


 ! ## ZcplA0A0hh ## 
ZcplA0A0hh = 0._dp 
TempcplA0A0hh = cplA0A0hh 
ZcplA0A0hh = TempcplA0A0hh 


 ! ## ZcplA0G0H0 ## 
ZcplA0G0H0 = 0._dp 
TempcplA0G0H0 = cplA0G0H0 
ZcplA0G0H0 = TempcplA0G0H0 


 ! ## ZcplA0H0hh ## 
ZcplA0H0hh = 0._dp 
TempcplA0H0hh = cplA0H0hh 
ZcplA0H0hh = TempcplA0H0hh 


 ! ## ZcplA0HpcHp ## 
ZcplA0HpcHp = 0._dp 
TempcplA0HpcHp = cplA0HpcHp 
ZcplA0HpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplA0HpcHp(gt2,:) = ZcplA0HpcHp(gt2,:) + ZRUZP(gt2,gt1)*TempcplA0HpcHp(gt1,:) 
 End Do 
End Do 
TempcplA0HpcHp = ZcplA0HpcHp 
ZcplA0HpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplA0HpcHp(:,gt2) = ZcplA0HpcHp(:,gt2) + ZRUZP(gt2,gt1)*TempcplA0HpcHp(:,gt1) 
 End Do 
End Do 


 ! ## ZcplG0G0hh ## 
ZcplG0G0hh = 0._dp 
TempcplG0G0hh = cplG0G0hh 
ZcplG0G0hh = TempcplG0G0hh 


 ! ## ZcplG0H0H0 ## 
ZcplG0H0H0 = 0._dp 
TempcplG0H0H0 = cplG0H0H0 
ZcplG0H0H0 = TempcplG0H0H0 


 ! ## ZcplH0H0hh ## 
ZcplH0H0hh = 0._dp 
TempcplH0H0hh = cplH0H0hh 
ZcplH0H0hh = TempcplH0H0hh 


 ! ## ZcplH0HpcHp ## 
ZcplH0HpcHp = 0._dp 
TempcplH0HpcHp = cplH0HpcHp 
ZcplH0HpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplH0HpcHp(gt2,:) = ZcplH0HpcHp(gt2,:) + ZRUZP(gt2,gt1)*TempcplH0HpcHp(gt1,:) 
 End Do 
End Do 
TempcplH0HpcHp = ZcplH0HpcHp 
ZcplH0HpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplH0HpcHp(:,gt2) = ZcplH0HpcHp(:,gt2) + ZRUZP(gt2,gt1)*TempcplH0HpcHp(:,gt1) 
 End Do 
End Do 


 ! ## Zcplhhhhhh ## 
Zcplhhhhhh = 0._dp 
Tempcplhhhhhh = cplhhhhhh 
Zcplhhhhhh = Tempcplhhhhhh 


 ! ## ZcplhhHpcHp ## 
ZcplhhHpcHp = 0._dp 
TempcplhhHpcHp = cplhhHpcHp 
ZcplhhHpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhHpcHp(gt2,:) = ZcplhhHpcHp(gt2,:) + ZRUZP(gt2,gt1)*TempcplhhHpcHp(gt1,:) 
 End Do 
End Do 
TempcplhhHpcHp = ZcplhhHpcHp 
ZcplhhHpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhHpcHp(:,gt2) = ZcplhhHpcHp(:,gt2) + ZRUZP(gt2,gt1)*TempcplhhHpcHp(:,gt1) 
 End Do 
End Do 


 ! ## ZcplA0A0A0A0 ## 
ZcplA0A0A0A0 = 0._dp 


 ! ## ZcplA0A0G0G0 ## 
ZcplA0A0G0G0 = 0._dp 


 ! ## ZcplA0A0G0hh ## 
ZcplA0A0G0hh = 0._dp 


 ! ## ZcplA0A0H0H0 ## 
ZcplA0A0H0H0 = 0._dp 


 ! ## ZcplA0A0hhhh ## 
ZcplA0A0hhhh = 0._dp 


 ! ## ZcplA0A0HpcHp ## 
ZcplA0A0HpcHp = 0._dp 


 ! ## ZcplA0G0G0H0 ## 
ZcplA0G0G0H0 = 0._dp 


 ! ## ZcplA0G0H0hh ## 
ZcplA0G0H0hh = 0._dp 


 ! ## ZcplA0G0HpcHp ## 
ZcplA0G0HpcHp = 0._dp 


 ! ## ZcplA0H0hhhh ## 
ZcplA0H0hhhh = 0._dp 


 ! ## ZcplA0hhHpcHp ## 
ZcplA0hhHpcHp = 0._dp 


 ! ## ZcplG0G0G0G0 ## 
ZcplG0G0G0G0 = 0._dp 


 ! ## ZcplG0G0H0H0 ## 
ZcplG0G0H0H0 = 0._dp 


 ! ## ZcplG0G0hhhh ## 
ZcplG0G0hhhh = 0._dp 


 ! ## ZcplG0G0HpcHp ## 
ZcplG0G0HpcHp = 0._dp 


 ! ## ZcplG0H0H0hh ## 
ZcplG0H0H0hh = 0._dp 


 ! ## ZcplG0H0HpcHp ## 
ZcplG0H0HpcHp = 0._dp 


 ! ## ZcplH0H0H0H0 ## 
ZcplH0H0H0H0 = 0._dp 


 ! ## ZcplH0H0hhhh ## 
ZcplH0H0hhhh = 0._dp 


 ! ## ZcplH0H0HpcHp ## 
ZcplH0H0HpcHp = 0._dp 


 ! ## ZcplH0hhHpcHp ## 
ZcplH0hhHpcHp = 0._dp 


 ! ## Zcplhhhhhhhh ## 
Zcplhhhhhhhh = 0._dp 


 ! ## ZcplhhhhHpcHp ## 
ZcplhhhhHpcHp = 0._dp 


 ! ## ZcplHpHpcHpcHp ## 
ZcplHpHpcHpcHp = 0._dp 


 ! ## ZcplA0H0VZ ## 
ZcplA0H0VZ = 0._dp 
TempcplA0H0VZ = cplA0H0VZ 
ZcplA0H0VZ = TempcplA0H0VZ 


 ! ## ZcplA0HpcVWp ## 
ZcplA0HpcVWp = 0._dp 
TempcplA0HpcVWp = cplA0HpcVWp 
ZcplA0HpcVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplA0HpcVWp(gt2) = ZcplA0HpcVWp(gt2) + ZRUZP(gt2,gt1)*TempcplA0HpcVWp(gt1) 
 End Do 
End Do 
TempcplA0HpcVWp = ZcplA0HpcVWp 


 ! ## ZcplA0cHpVWp ## 
ZcplA0cHpVWp = 0._dp 
TempcplA0cHpVWp = cplA0cHpVWp 
ZcplA0cHpVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplA0cHpVWp(gt2) = ZcplA0cHpVWp(gt2) + ZRUZP(gt2,gt1)*TempcplA0cHpVWp(gt1) 
 End Do 
End Do 
TempcplA0cHpVWp = ZcplA0cHpVWp 


 ! ## ZcplG0hhVZ ## 
ZcplG0hhVZ = 0._dp 
TempcplG0hhVZ = cplG0hhVZ 
ZcplG0hhVZ = TempcplG0hhVZ 


 ! ## ZcplG0HpcVWp ## 
ZcplG0HpcVWp = 0._dp 
TempcplG0HpcVWp = cplG0HpcVWp 
ZcplG0HpcVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplG0HpcVWp(gt2) = ZcplG0HpcVWp(gt2) + ZRUZP(gt2,gt1)*TempcplG0HpcVWp(gt1) 
 End Do 
End Do 
TempcplG0HpcVWp = ZcplG0HpcVWp 


 ! ## ZcplG0cHpVWp ## 
ZcplG0cHpVWp = 0._dp 
TempcplG0cHpVWp = cplG0cHpVWp 
ZcplG0cHpVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplG0cHpVWp(gt2) = ZcplG0cHpVWp(gt2) + ZRUZP(gt2,gt1)*TempcplG0cHpVWp(gt1) 
 End Do 
End Do 
TempcplG0cHpVWp = ZcplG0cHpVWp 


 ! ## ZcplH0HpcVWp ## 
ZcplH0HpcVWp = 0._dp 
TempcplH0HpcVWp = cplH0HpcVWp 
ZcplH0HpcVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplH0HpcVWp(gt2) = ZcplH0HpcVWp(gt2) + ZRUZP(gt2,gt1)*TempcplH0HpcVWp(gt1) 
 End Do 
End Do 
TempcplH0HpcVWp = ZcplH0HpcVWp 


 ! ## ZcplH0cHpVWp ## 
ZcplH0cHpVWp = 0._dp 
TempcplH0cHpVWp = cplH0cHpVWp 
ZcplH0cHpVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplH0cHpVWp(gt2) = ZcplH0cHpVWp(gt2) + ZRUZP(gt2,gt1)*TempcplH0cHpVWp(gt1) 
 End Do 
End Do 
TempcplH0cHpVWp = ZcplH0cHpVWp 


 ! ## ZcplhhHpcVWp ## 
ZcplhhHpcVWp = 0._dp 
TempcplhhHpcVWp = cplhhHpcVWp 
ZcplhhHpcVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhHpcVWp(gt2) = ZcplhhHpcVWp(gt2) + ZRUZP(gt2,gt1)*TempcplhhHpcVWp(gt1) 
 End Do 
End Do 
TempcplhhHpcVWp = ZcplhhHpcVWp 


 ! ## ZcplhhcHpVWp ## 
ZcplhhcHpVWp = 0._dp 
TempcplhhcHpVWp = cplhhcHpVWp 
ZcplhhcHpVWp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplhhcHpVWp(gt2) = ZcplhhcHpVWp(gt2) + ZRUZP(gt2,gt1)*TempcplhhcHpVWp(gt1) 
 End Do 
End Do 
TempcplhhcHpVWp = ZcplhhcHpVWp 


 ! ## ZcplHpcHpVP ## 
ZcplHpcHpVP = 0._dp 
TempcplHpcHpVP = cplHpcHpVP 
Do gt1=1,2
  Do gt2=1,2
ZcplHpcHpVP(gt2,:) = ZcplHpcHpVP(gt2,:) + ZRUZP(gt2,gt1)*TempcplHpcHpVP(gt1,:) 
 End Do 
End Do 
TempcplHpcHpVP = ZcplHpcHpVP 
ZcplHpcHpVP = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplHpcHpVP(:,gt2) = ZcplHpcHpVP(:,gt2) + ZRUZP(gt2,gt1)*TempcplHpcHpVP(:,gt1) 
 End Do 
End Do 
TempcplHpcHpVP = ZcplHpcHpVP 


 ! ## ZcplHpcHpVZ ## 
ZcplHpcHpVZ = 0._dp 
TempcplHpcHpVZ = cplHpcHpVZ 
Do gt1=1,2
  Do gt2=1,2
ZcplHpcHpVZ(gt2,:) = ZcplHpcHpVZ(gt2,:) + ZRUZP(gt2,gt1)*TempcplHpcHpVZ(gt1,:) 
 End Do 
End Do 
TempcplHpcHpVZ = ZcplHpcHpVZ 
ZcplHpcHpVZ = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplHpcHpVZ(:,gt2) = ZcplHpcHpVZ(:,gt2) + ZRUZP(gt2,gt1)*TempcplHpcHpVZ(:,gt1) 
 End Do 
End Do 
TempcplHpcHpVZ = ZcplHpcHpVZ 


 ! ## ZcplhhcVWpVWp ## 
ZcplhhcVWpVWp = 0._dp 
TempcplhhcVWpVWp = cplhhcVWpVWp 
ZcplhhcVWpVWp = TempcplhhcVWpVWp 


 ! ## ZcplhhVZVZ ## 
ZcplhhVZVZ = 0._dp 
TempcplhhVZVZ = cplhhVZVZ 
ZcplhhVZVZ = TempcplhhVZVZ 


 ! ## ZcplHpcVWpVP ## 
ZcplHpcVWpVP = 0._dp 
TempcplHpcVWpVP = cplHpcVWpVP 
Do gt1=1,2
  Do gt2=1,2
ZcplHpcVWpVP(gt2) = ZcplHpcVWpVP(gt2) + ZRUZP(gt2,gt1)*TempcplHpcVWpVP(gt1) 
 End Do 
End Do 
TempcplHpcVWpVP = ZcplHpcVWpVP 


 ! ## ZcplHpcVWpVZ ## 
ZcplHpcVWpVZ = 0._dp 
TempcplHpcVWpVZ = cplHpcVWpVZ 
Do gt1=1,2
  Do gt2=1,2
ZcplHpcVWpVZ(gt2) = ZcplHpcVWpVZ(gt2) + ZRUZP(gt2,gt1)*TempcplHpcVWpVZ(gt1) 
 End Do 
End Do 
TempcplHpcVWpVZ = ZcplHpcVWpVZ 


 ! ## ZcplcHpVPVWp ## 
ZcplcHpVPVWp = 0._dp 
TempcplcHpVPVWp = cplcHpVPVWp 
Do gt1=1,2
  Do gt2=1,2
ZcplcHpVPVWp(gt2) = ZcplcHpVPVWp(gt2) + ZRUZP(gt2,gt1)*TempcplcHpVPVWp(gt1) 
 End Do 
End Do 
TempcplcHpVPVWp = ZcplcHpVPVWp 


 ! ## ZcplcHpVWpVZ ## 
ZcplcHpVWpVZ = 0._dp 
TempcplcHpVWpVZ = cplcHpVWpVZ 
Do gt1=1,2
  Do gt2=1,2
ZcplcHpVWpVZ(gt2) = ZcplcHpVWpVZ(gt2) + ZRUZP(gt2,gt1)*TempcplcHpVWpVZ(gt1) 
 End Do 
End Do 
TempcplcHpVWpVZ = ZcplcHpVWpVZ 


 ! ## ZcplA0A0cVWpVWp ## 
ZcplA0A0cVWpVWp = 0._dp 


 ! ## ZcplA0A0VZVZ ## 
ZcplA0A0VZVZ = 0._dp 


 ! ## ZcplA0HpcVWpVP ## 
ZcplA0HpcVWpVP = 0._dp 


 ! ## ZcplA0HpcVWpVZ ## 
ZcplA0HpcVWpVZ = 0._dp 


 ! ## ZcplA0cHpVPVWp ## 
ZcplA0cHpVPVWp = 0._dp 


 ! ## ZcplA0cHpVWpVZ ## 
ZcplA0cHpVWpVZ = 0._dp 


 ! ## ZcplG0G0cVWpVWp ## 
ZcplG0G0cVWpVWp = 0._dp 


 ! ## ZcplG0G0VZVZ ## 
ZcplG0G0VZVZ = 0._dp 


 ! ## ZcplG0HpcVWpVP ## 
ZcplG0HpcVWpVP = 0._dp 


 ! ## ZcplG0HpcVWpVZ ## 
ZcplG0HpcVWpVZ = 0._dp 


 ! ## ZcplG0cHpVPVWp ## 
ZcplG0cHpVPVWp = 0._dp 


 ! ## ZcplG0cHpVWpVZ ## 
ZcplG0cHpVWpVZ = 0._dp 


 ! ## ZcplH0H0cVWpVWp ## 
ZcplH0H0cVWpVWp = 0._dp 


 ! ## ZcplH0H0VZVZ ## 
ZcplH0H0VZVZ = 0._dp 


 ! ## ZcplH0HpcVWpVP ## 
ZcplH0HpcVWpVP = 0._dp 


 ! ## ZcplH0HpcVWpVZ ## 
ZcplH0HpcVWpVZ = 0._dp 


 ! ## ZcplH0cHpVPVWp ## 
ZcplH0cHpVPVWp = 0._dp 


 ! ## ZcplH0cHpVWpVZ ## 
ZcplH0cHpVWpVZ = 0._dp 


 ! ## ZcplhhhhcVWpVWp ## 
ZcplhhhhcVWpVWp = 0._dp 


 ! ## ZcplhhhhVZVZ ## 
ZcplhhhhVZVZ = 0._dp 


 ! ## ZcplhhHpcVWpVP ## 
ZcplhhHpcVWpVP = 0._dp 


 ! ## ZcplhhHpcVWpVZ ## 
ZcplhhHpcVWpVZ = 0._dp 


 ! ## ZcplhhcHpVPVWp ## 
ZcplhhcHpVPVWp = 0._dp 


 ! ## ZcplhhcHpVWpVZ ## 
ZcplhhcHpVWpVZ = 0._dp 


 ! ## ZcplHpcHpVPVP ## 
ZcplHpcHpVPVP = 0._dp 


 ! ## ZcplHpcHpVPVZ ## 
ZcplHpcHpVPVZ = 0._dp 


 ! ## ZcplHpcHpcVWpVWp ## 
ZcplHpcHpcVWpVWp = 0._dp 


 ! ## ZcplHpcHpVZVZ ## 
ZcplHpcHpVZVZ = 0._dp 


 ! ## ZcplVGVGVG ## 
ZcplVGVGVG = 0._dp 
TempcplVGVGVG = cplVGVGVG 
ZcplVGVGVG = TempcplVGVGVG 


 ! ## ZcplcVWpVPVWp ## 
ZcplcVWpVPVWp = 0._dp 
TempcplcVWpVPVWp = cplcVWpVPVWp 
ZcplcVWpVPVWp = TempcplcVWpVPVWp 


 ! ## ZcplcVWpVWpVZ ## 
ZcplcVWpVWpVZ = 0._dp 
TempcplcVWpVWpVZ = cplcVWpVWpVZ 
ZcplcVWpVWpVZ = TempcplcVWpVWpVZ 


 ! ## ZcplcFdFdG0L ## 
ZcplcFdFdG0L = 0._dp 
TempcplcFdFdG0L = cplcFdFdG0L 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdG0L(gt2,:) = ZcplcFdFdG0L(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdG0L(gt1,:) 
 End Do 
End Do 
TempcplcFdFdG0L = ZcplcFdFdG0L 
ZcplcFdFdG0L = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdG0L(:,gt2) = ZcplcFdFdG0L(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdG0L(:,gt1) 
 End Do 
End Do 
TempcplcFdFdG0L = ZcplcFdFdG0L 


 ! ## ZcplcFdFdG0R ## 
ZcplcFdFdG0R = 0._dp 
TempcplcFdFdG0R = cplcFdFdG0R 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdG0R(gt2,:) = ZcplcFdFdG0R(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdG0R(gt1,:) 
 End Do 
End Do 
TempcplcFdFdG0R = ZcplcFdFdG0R 
ZcplcFdFdG0R = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdG0R(:,gt2) = ZcplcFdFdG0R(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdG0R(:,gt1) 
 End Do 
End Do 
TempcplcFdFdG0R = ZcplcFdFdG0R 


 ! ## ZcplcFdFdhhL ## 
ZcplcFdFdhhL = 0._dp 
TempcplcFdFdhhL = cplcFdFdhhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhL(gt2,:) = ZcplcFdFdhhL(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdhhL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdhhL = ZcplcFdFdhhL 
ZcplcFdFdhhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhL(:,gt2) = ZcplcFdFdhhL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdhhL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdhhL = ZcplcFdFdhhL 


 ! ## ZcplcFdFdhhR ## 
ZcplcFdFdhhR = 0._dp 
TempcplcFdFdhhR = cplcFdFdhhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhR(gt2,:) = ZcplcFdFdhhR(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdhhR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdhhR = ZcplcFdFdhhR 
ZcplcFdFdhhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdhhR(:,gt2) = ZcplcFdFdhhR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdhhR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdhhR = ZcplcFdFdhhR 


 ! ## ZcplcFuFdHpL ## 
ZcplcFuFdHpL = 0._dp 
TempcplcFuFdHpL = cplcFuFdHpL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdHpL(gt2,:,:) = ZcplcFuFdHpL(gt2,:,:) + ZRUZUR(gt2,gt1)*TempcplcFuFdHpL(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFdHpL = ZcplcFuFdHpL 
ZcplcFuFdHpL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdHpL(:,gt2,:) = ZcplcFuFdHpL(:,gt2,:) + ZRUZDL(gt2,gt1)*TempcplcFuFdHpL(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFdHpL = ZcplcFuFdHpL 
ZcplcFuFdHpL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFuFdHpL(:,:,gt2) = ZcplcFuFdHpL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFuFdHpL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFdHpR ## 
ZcplcFuFdHpR = 0._dp 
TempcplcFuFdHpR = cplcFuFdHpR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdHpR(gt2,:,:) = ZcplcFuFdHpR(gt2,:,:) + ZRUZULc(gt2,gt1)*TempcplcFuFdHpR(gt1,:,:) 
 End Do 
End Do 
TempcplcFuFdHpR = ZcplcFuFdHpR 
ZcplcFuFdHpR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdHpR(:,gt2,:) = ZcplcFuFdHpR(:,gt2,:) + ZRUZDRc(gt2,gt1)*TempcplcFuFdHpR(:,gt1,:) 
 End Do 
End Do 
TempcplcFuFdHpR = ZcplcFuFdHpR 
ZcplcFuFdHpR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFuFdHpR(:,:,gt2) = ZcplcFuFdHpR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFuFdHpR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFeG0L ## 
ZcplcFeFeG0L = 0._dp 
TempcplcFeFeG0L = cplcFeFeG0L 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeG0L(gt2,:) = ZcplcFeFeG0L(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFeG0L(gt1,:) 
 End Do 
End Do 
TempcplcFeFeG0L = ZcplcFeFeG0L 
ZcplcFeFeG0L = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeG0L(:,gt2) = ZcplcFeFeG0L(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFeFeG0L(:,gt1) 
 End Do 
End Do 
TempcplcFeFeG0L = ZcplcFeFeG0L 


 ! ## ZcplcFeFeG0R ## 
ZcplcFeFeG0R = 0._dp 
TempcplcFeFeG0R = cplcFeFeG0R 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeG0R(gt2,:) = ZcplcFeFeG0R(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFeG0R(gt1,:) 
 End Do 
End Do 
TempcplcFeFeG0R = ZcplcFeFeG0R 
ZcplcFeFeG0R = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeG0R(:,gt2) = ZcplcFeFeG0R(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFeFeG0R(:,gt1) 
 End Do 
End Do 
TempcplcFeFeG0R = ZcplcFeFeG0R 


 ! ## ZcplcFeFehhL ## 
ZcplcFeFehhL = 0._dp 
TempcplcFeFehhL = cplcFeFehhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhL(gt2,:) = ZcplcFeFehhL(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFehhL(gt1,:) 
 End Do 
End Do 
TempcplcFeFehhL = ZcplcFeFehhL 
ZcplcFeFehhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhL(:,gt2) = ZcplcFeFehhL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFeFehhL(:,gt1) 
 End Do 
End Do 
TempcplcFeFehhL = ZcplcFeFehhL 


 ! ## ZcplcFeFehhR ## 
ZcplcFeFehhR = 0._dp 
TempcplcFeFehhR = cplcFeFehhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhR(gt2,:) = ZcplcFeFehhR(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFehhR(gt1,:) 
 End Do 
End Do 
TempcplcFeFehhR = ZcplcFeFehhR 
ZcplcFeFehhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFehhR(:,gt2) = ZcplcFeFehhR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFeFehhR(:,gt1) 
 End Do 
End Do 
TempcplcFeFehhR = ZcplcFeFehhR 


 ! ## ZcplcFvFeHpL ## 
ZcplcFvFeHpL = 0._dp 
TempcplcFvFeHpL = cplcFvFeHpL 
ZcplcFvFeHpL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFeHpL(:,gt2,:) = ZcplcFvFeHpL(:,gt2,:) + ZRUZEL(gt2,gt1)*TempcplcFvFeHpL(:,gt1,:) 
 End Do 
End Do 
TempcplcFvFeHpL = ZcplcFvFeHpL 
ZcplcFvFeHpL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFvFeHpL(:,:,gt2) = ZcplcFvFeHpL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFvFeHpL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFvFeHpR ## 
ZcplcFvFeHpR = 0._dp 
TempcplcFvFeHpR = cplcFvFeHpR 
ZcplcFvFeHpR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFeHpR(:,gt2,:) = ZcplcFvFeHpR(:,gt2,:) + ZRUZERc(gt2,gt1)*TempcplcFvFeHpR(:,gt1,:) 
 End Do 
End Do 
TempcplcFvFeHpR = ZcplcFvFeHpR 
ZcplcFvFeHpR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFvFeHpR(:,:,gt2) = ZcplcFvFeHpR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFvFeHpR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFuFuG0L ## 
ZcplcFuFuG0L = 0._dp 
TempcplcFuFuG0L = cplcFuFuG0L 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuG0L(gt2,:) = ZcplcFuFuG0L(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuG0L(gt1,:) 
 End Do 
End Do 
TempcplcFuFuG0L = ZcplcFuFuG0L 
ZcplcFuFuG0L = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuG0L(:,gt2) = ZcplcFuFuG0L(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuG0L(:,gt1) 
 End Do 
End Do 
TempcplcFuFuG0L = ZcplcFuFuG0L 


 ! ## ZcplcFuFuG0R ## 
ZcplcFuFuG0R = 0._dp 
TempcplcFuFuG0R = cplcFuFuG0R 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuG0R(gt2,:) = ZcplcFuFuG0R(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuG0R(gt1,:) 
 End Do 
End Do 
TempcplcFuFuG0R = ZcplcFuFuG0R 
ZcplcFuFuG0R = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuG0R(:,gt2) = ZcplcFuFuG0R(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuG0R(:,gt1) 
 End Do 
End Do 
TempcplcFuFuG0R = ZcplcFuFuG0R 


 ! ## ZcplcFuFuhhL ## 
ZcplcFuFuhhL = 0._dp 
TempcplcFuFuhhL = cplcFuFuhhL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhL(gt2,:) = ZcplcFuFuhhL(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuhhL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuhhL = ZcplcFuFuhhL 
ZcplcFuFuhhL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhL(:,gt2) = ZcplcFuFuhhL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuhhL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuhhL = ZcplcFuFuhhL 


 ! ## ZcplcFuFuhhR ## 
ZcplcFuFuhhR = 0._dp 
TempcplcFuFuhhR = cplcFuFuhhR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhR(gt2,:) = ZcplcFuFuhhR(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuhhR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuhhR = ZcplcFuFuhhR 
ZcplcFuFuhhR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuhhR(:,gt2) = ZcplcFuFuhhR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuhhR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuhhR = ZcplcFuFuhhR 


 ! ## ZcplcFdFucHpL ## 
ZcplcFdFucHpL = 0._dp 
TempcplcFdFucHpL = cplcFdFucHpL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucHpL(gt2,:,:) = ZcplcFdFucHpL(gt2,:,:) + ZRUZDR(gt2,gt1)*TempcplcFdFucHpL(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFucHpL = ZcplcFdFucHpL 
ZcplcFdFucHpL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucHpL(:,gt2,:) = ZcplcFdFucHpL(:,gt2,:) + ZRUZUL(gt2,gt1)*TempcplcFdFucHpL(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFucHpL = ZcplcFdFucHpL 
ZcplcFdFucHpL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFdFucHpL(:,:,gt2) = ZcplcFdFucHpL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFdFucHpL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFucHpR ## 
ZcplcFdFucHpR = 0._dp 
TempcplcFdFucHpR = cplcFdFucHpR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucHpR(gt2,:,:) = ZcplcFdFucHpR(gt2,:,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFucHpR(gt1,:,:) 
 End Do 
End Do 
TempcplcFdFucHpR = ZcplcFdFucHpR 
ZcplcFdFucHpR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucHpR(:,gt2,:) = ZcplcFdFucHpR(:,gt2,:) + ZRUZURc(gt2,gt1)*TempcplcFdFucHpR(:,gt1,:) 
 End Do 
End Do 
TempcplcFdFucHpR = ZcplcFdFucHpR 
ZcplcFdFucHpR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFdFucHpR(:,:,gt2) = ZcplcFdFucHpR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFdFucHpR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFvcHpL ## 
ZcplcFeFvcHpL = 0._dp 
TempcplcFeFvcHpL = cplcFeFvcHpL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvcHpL(gt2,:,:) = ZcplcFeFvcHpL(gt2,:,:) + ZRUZER(gt2,gt1)*TempcplcFeFvcHpL(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFvcHpL = ZcplcFeFvcHpL 
ZcplcFeFvcHpL = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFeFvcHpL(:,:,gt2) = ZcplcFeFvcHpL(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFeFvcHpL(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFeFvcHpR ## 
ZcplcFeFvcHpR = 0._dp 
TempcplcFeFvcHpR = cplcFeFvcHpR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvcHpR(gt2,:,:) = ZcplcFeFvcHpR(gt2,:,:) + ZRUZELc(gt2,gt1)*TempcplcFeFvcHpR(gt1,:,:) 
 End Do 
End Do 
TempcplcFeFvcHpR = ZcplcFeFvcHpR 
ZcplcFeFvcHpR = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcFeFvcHpR(:,:,gt2) = ZcplcFeFvcHpR(:,:,gt2) + ZRUZP(gt2,gt1)*TempcplcFeFvcHpR(:,:,gt1) 
 End Do 
End Do 


 ! ## ZcplcFdFdVGL ## 
ZcplcFdFdVGL = 0._dp 
TempcplcFdFdVGL = cplcFdFdVGL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGL(gt2,:) = ZcplcFdFdVGL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdVGL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVGL = ZcplcFdFdVGL 
ZcplcFdFdVGL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGL(:,gt2) = ZcplcFdFdVGL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdVGL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVGL = ZcplcFdFdVGL 


 ! ## ZcplcFdFdVGR ## 
ZcplcFdFdVGR = 0._dp 
TempcplcFdFdVGR = cplcFdFdVGR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGR(gt2,:) = ZcplcFdFdVGR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdVGR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVGR = ZcplcFdFdVGR 
ZcplcFdFdVGR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVGR(:,gt2) = ZcplcFdFdVGR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdVGR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVGR = ZcplcFdFdVGR 


 ! ## ZcplcFdFdVPL ## 
ZcplcFdFdVPL = 0._dp 
TempcplcFdFdVPL = cplcFdFdVPL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPL(gt2,:) = ZcplcFdFdVPL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdVPL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVPL = ZcplcFdFdVPL 
ZcplcFdFdVPL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPL(:,gt2) = ZcplcFdFdVPL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdVPL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVPL = ZcplcFdFdVPL 


 ! ## ZcplcFdFdVPR ## 
ZcplcFdFdVPR = 0._dp 
TempcplcFdFdVPR = cplcFdFdVPR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPR(gt2,:) = ZcplcFdFdVPR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdVPR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVPR = ZcplcFdFdVPR 
ZcplcFdFdVPR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVPR(:,gt2) = ZcplcFdFdVPR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdVPR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVPR = ZcplcFdFdVPR 


 ! ## ZcplcFuFdVWpL ## 
ZcplcFuFdVWpL = 0._dp 
TempcplcFuFdVWpL = cplcFuFdVWpL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdVWpL(gt2,:) = ZcplcFuFdVWpL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFdVWpL(gt1,:) 
 End Do 
End Do 
TempcplcFuFdVWpL = ZcplcFuFdVWpL 
ZcplcFuFdVWpL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdVWpL(:,gt2) = ZcplcFuFdVWpL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFuFdVWpL(:,gt1) 
 End Do 
End Do 
TempcplcFuFdVWpL = ZcplcFuFdVWpL 


 ! ## ZcplcFuFdVWpR ## 
ZcplcFuFdVWpR = 0._dp 
TempcplcFuFdVWpR = cplcFuFdVWpR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdVWpR(gt2,:) = ZcplcFuFdVWpR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFdVWpR(gt1,:) 
 End Do 
End Do 
TempcplcFuFdVWpR = ZcplcFuFdVWpR 
ZcplcFuFdVWpR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFdVWpR(:,gt2) = ZcplcFuFdVWpR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFuFdVWpR(:,gt1) 
 End Do 
End Do 
TempcplcFuFdVWpR = ZcplcFuFdVWpR 


 ! ## ZcplcFdFdVZL ## 
ZcplcFdFdVZL = 0._dp 
TempcplcFdFdVZL = cplcFdFdVZL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZL(gt2,:) = ZcplcFdFdVZL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFdVZL(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVZL = ZcplcFdFdVZL 
ZcplcFdFdVZL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZL(:,gt2) = ZcplcFdFdVZL(:,gt2) + ZRUZDL(gt2,gt1)*TempcplcFdFdVZL(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVZL = ZcplcFdFdVZL 


 ! ## ZcplcFdFdVZR ## 
ZcplcFdFdVZR = 0._dp 
TempcplcFdFdVZR = cplcFdFdVZR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZR(gt2,:) = ZcplcFdFdVZR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFdVZR(gt1,:) 
 End Do 
End Do 
TempcplcFdFdVZR = ZcplcFdFdVZR 
ZcplcFdFdVZR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFdVZR(:,gt2) = ZcplcFdFdVZR(:,gt2) + ZRUZDRc(gt2,gt1)*TempcplcFdFdVZR(:,gt1) 
 End Do 
End Do 
TempcplcFdFdVZR = ZcplcFdFdVZR 


 ! ## ZcplcFeFeVPL ## 
ZcplcFeFeVPL = 0._dp 
TempcplcFeFeVPL = cplcFeFeVPL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPL(gt2,:) = ZcplcFeFeVPL(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFeVPL(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVPL = ZcplcFeFeVPL 
ZcplcFeFeVPL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPL(:,gt2) = ZcplcFeFeVPL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFeFeVPL(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVPL = ZcplcFeFeVPL 


 ! ## ZcplcFeFeVPR ## 
ZcplcFeFeVPR = 0._dp 
TempcplcFeFeVPR = cplcFeFeVPR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPR(gt2,:) = ZcplcFeFeVPR(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFeVPR(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVPR = ZcplcFeFeVPR 
ZcplcFeFeVPR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVPR(:,gt2) = ZcplcFeFeVPR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFeFeVPR(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVPR = ZcplcFeFeVPR 


 ! ## ZcplcFvFeVWpL ## 
ZcplcFvFeVWpL = 0._dp 
TempcplcFvFeVWpL = cplcFvFeVWpL 
ZcplcFvFeVWpL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFeVWpL(:,gt2) = ZcplcFvFeVWpL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFvFeVWpL(:,gt1) 
 End Do 
End Do 
TempcplcFvFeVWpL = ZcplcFvFeVWpL 


 ! ## ZcplcFvFeVWpR ## 
ZcplcFvFeVWpR = 0._dp 
TempcplcFvFeVWpR = cplcFvFeVWpR 
ZcplcFvFeVWpR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFvFeVWpR(:,gt2) = ZcplcFvFeVWpR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFvFeVWpR(:,gt1) 
 End Do 
End Do 
TempcplcFvFeVWpR = ZcplcFvFeVWpR 


 ! ## ZcplcFeFeVZL ## 
ZcplcFeFeVZL = 0._dp 
TempcplcFeFeVZL = cplcFeFeVZL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZL(gt2,:) = ZcplcFeFeVZL(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFeVZL(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVZL = ZcplcFeFeVZL 
ZcplcFeFeVZL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZL(:,gt2) = ZcplcFeFeVZL(:,gt2) + ZRUZEL(gt2,gt1)*TempcplcFeFeVZL(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVZL = ZcplcFeFeVZL 


 ! ## ZcplcFeFeVZR ## 
ZcplcFeFeVZR = 0._dp 
TempcplcFeFeVZR = cplcFeFeVZR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZR(gt2,:) = ZcplcFeFeVZR(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFeVZR(gt1,:) 
 End Do 
End Do 
TempcplcFeFeVZR = ZcplcFeFeVZR 
ZcplcFeFeVZR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFeVZR(:,gt2) = ZcplcFeFeVZR(:,gt2) + ZRUZERc(gt2,gt1)*TempcplcFeFeVZR(:,gt1) 
 End Do 
End Do 
TempcplcFeFeVZR = ZcplcFeFeVZR 


 ! ## ZcplcFuFuVGL ## 
ZcplcFuFuVGL = 0._dp 
TempcplcFuFuVGL = cplcFuFuVGL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGL(gt2,:) = ZcplcFuFuVGL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuVGL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVGL = ZcplcFuFuVGL 
ZcplcFuFuVGL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGL(:,gt2) = ZcplcFuFuVGL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuVGL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVGL = ZcplcFuFuVGL 


 ! ## ZcplcFuFuVGR ## 
ZcplcFuFuVGR = 0._dp 
TempcplcFuFuVGR = cplcFuFuVGR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGR(gt2,:) = ZcplcFuFuVGR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuVGR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVGR = ZcplcFuFuVGR 
ZcplcFuFuVGR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVGR(:,gt2) = ZcplcFuFuVGR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuVGR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVGR = ZcplcFuFuVGR 


 ! ## ZcplcFuFuVPL ## 
ZcplcFuFuVPL = 0._dp 
TempcplcFuFuVPL = cplcFuFuVPL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPL(gt2,:) = ZcplcFuFuVPL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuVPL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVPL = ZcplcFuFuVPL 
ZcplcFuFuVPL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPL(:,gt2) = ZcplcFuFuVPL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuVPL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVPL = ZcplcFuFuVPL 


 ! ## ZcplcFuFuVPR ## 
ZcplcFuFuVPR = 0._dp 
TempcplcFuFuVPR = cplcFuFuVPR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPR(gt2,:) = ZcplcFuFuVPR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuVPR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVPR = ZcplcFuFuVPR 
ZcplcFuFuVPR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVPR(:,gt2) = ZcplcFuFuVPR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuVPR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVPR = ZcplcFuFuVPR 


 ! ## ZcplcFuFuVZL ## 
ZcplcFuFuVZL = 0._dp 
TempcplcFuFuVZL = cplcFuFuVZL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZL(gt2,:) = ZcplcFuFuVZL(gt2,:) + ZRUZULc(gt2,gt1)*TempcplcFuFuVZL(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVZL = ZcplcFuFuVZL 
ZcplcFuFuVZL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZL(:,gt2) = ZcplcFuFuVZL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFuFuVZL(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVZL = ZcplcFuFuVZL 


 ! ## ZcplcFuFuVZR ## 
ZcplcFuFuVZR = 0._dp 
TempcplcFuFuVZR = cplcFuFuVZR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZR(gt2,:) = ZcplcFuFuVZR(gt2,:) + ZRUZUR(gt2,gt1)*TempcplcFuFuVZR(gt1,:) 
 End Do 
End Do 
TempcplcFuFuVZR = ZcplcFuFuVZR 
ZcplcFuFuVZR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFuFuVZR(:,gt2) = ZcplcFuFuVZR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFuFuVZR(:,gt1) 
 End Do 
End Do 
TempcplcFuFuVZR = ZcplcFuFuVZR 


 ! ## ZcplcFdFucVWpL ## 
ZcplcFdFucVWpL = 0._dp 
TempcplcFdFucVWpL = cplcFdFucVWpL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucVWpL(gt2,:) = ZcplcFdFucVWpL(gt2,:) + ZRUZDLc(gt2,gt1)*TempcplcFdFucVWpL(gt1,:) 
 End Do 
End Do 
TempcplcFdFucVWpL = ZcplcFdFucVWpL 
ZcplcFdFucVWpL = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucVWpL(:,gt2) = ZcplcFdFucVWpL(:,gt2) + ZRUZUL(gt2,gt1)*TempcplcFdFucVWpL(:,gt1) 
 End Do 
End Do 
TempcplcFdFucVWpL = ZcplcFdFucVWpL 


 ! ## ZcplcFdFucVWpR ## 
ZcplcFdFucVWpR = 0._dp 
TempcplcFdFucVWpR = cplcFdFucVWpR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucVWpR(gt2,:) = ZcplcFdFucVWpR(gt2,:) + ZRUZDR(gt2,gt1)*TempcplcFdFucVWpR(gt1,:) 
 End Do 
End Do 
TempcplcFdFucVWpR = ZcplcFdFucVWpR 
ZcplcFdFucVWpR = 0._dp 
Do gt1=1,3
  Do gt2=1,3
ZcplcFdFucVWpR(:,gt2) = ZcplcFdFucVWpR(:,gt2) + ZRUZURc(gt2,gt1)*TempcplcFdFucVWpR(:,gt1) 
 End Do 
End Do 
TempcplcFdFucVWpR = ZcplcFdFucVWpR 


 ! ## ZcplcFvFvVZL ## 
ZcplcFvFvVZL = 0._dp 
TempcplcFvFvVZL = cplcFvFvVZL 


 ! ## ZcplcFvFvVZR ## 
ZcplcFvFvVZR = 0._dp 
TempcplcFvFvVZR = cplcFvFvVZR 


 ! ## ZcplcFeFvcVWpL ## 
ZcplcFeFvcVWpL = 0._dp 
TempcplcFeFvcVWpL = cplcFeFvcVWpL 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvcVWpL(gt2,:) = ZcplcFeFvcVWpL(gt2,:) + ZRUZELc(gt2,gt1)*TempcplcFeFvcVWpL(gt1,:) 
 End Do 
End Do 
TempcplcFeFvcVWpL = ZcplcFeFvcVWpL 


 ! ## ZcplcFeFvcVWpR ## 
ZcplcFeFvcVWpR = 0._dp 
TempcplcFeFvcVWpR = cplcFeFvcVWpR 
Do gt1=1,3
  Do gt2=1,3
ZcplcFeFvcVWpR(gt2,:) = ZcplcFeFvcVWpR(gt2,:) + ZRUZER(gt2,gt1)*TempcplcFeFvcVWpR(gt1,:) 
 End Do 
End Do 
TempcplcFeFvcVWpR = ZcplcFeFvcVWpR 


 ! ## ZcplVGVGVGVG1 ## 
ZcplVGVGVGVG1 = 0._dp 


 ! ## ZcplVGVGVGVG2 ## 
ZcplVGVGVGVG2 = 0._dp 


 ! ## ZcplVGVGVGVG3 ## 
ZcplVGVGVGVG3 = 0._dp 


 ! ## ZcplcVWpVPVPVWp1 ## 
ZcplcVWpVPVPVWp1 = 0._dp 


 ! ## ZcplcVWpVPVPVWp2 ## 
ZcplcVWpVPVPVWp2 = 0._dp 


 ! ## ZcplcVWpVPVPVWp3 ## 
ZcplcVWpVPVPVWp3 = 0._dp 


 ! ## ZcplcVWpVPVWpVZ1 ## 
ZcplcVWpVPVWpVZ1 = 0._dp 


 ! ## ZcplcVWpVPVWpVZ2 ## 
ZcplcVWpVPVWpVZ2 = 0._dp 


 ! ## ZcplcVWpVPVWpVZ3 ## 
ZcplcVWpVPVWpVZ3 = 0._dp 


 ! ## ZcplcVWpcVWpVWpVWp1 ## 
ZcplcVWpcVWpVWpVWp1 = 0._dp 


 ! ## ZcplcVWpcVWpVWpVWp2 ## 
ZcplcVWpcVWpVWpVWp2 = 0._dp 


 ! ## ZcplcVWpcVWpVWpVWp3 ## 
ZcplcVWpcVWpVWpVWp3 = 0._dp 


 ! ## ZcplcVWpVWpVZVZ1 ## 
ZcplcVWpVWpVZVZ1 = 0._dp 


 ! ## ZcplcVWpVWpVZVZ2 ## 
ZcplcVWpVWpVZVZ2 = 0._dp 


 ! ## ZcplcVWpVWpVZVZ3 ## 
ZcplcVWpVWpVZVZ3 = 0._dp 


 ! ## ZcplcgGgGVG ## 
ZcplcgGgGVG = 0._dp 
TempcplcgGgGVG = cplcgGgGVG 
ZcplcgGgGVG = TempcplcgGgGVG 


 ! ## ZcplcgWpgAVWp ## 
ZcplcgWpgAVWp = 0._dp 
TempcplcgWpgAVWp = cplcgWpgAVWp 
ZcplcgWpgAVWp = TempcplcgWpgAVWp 


 ! ## ZcplcgWCgAcVWp ## 
ZcplcgWCgAcVWp = 0._dp 
TempcplcgWCgAcVWp = cplcgWCgAcVWp 
ZcplcgWCgAcVWp = TempcplcgWCgAcVWp 


 ! ## ZcplcgWpgWpVP ## 
ZcplcgWpgWpVP = 0._dp 
TempcplcgWpgWpVP = cplcgWpgWpVP 
ZcplcgWpgWpVP = TempcplcgWpgWpVP 


 ! ## ZcplcgWpgWpVZ ## 
ZcplcgWpgWpVZ = 0._dp 
TempcplcgWpgWpVZ = cplcgWpgWpVZ 
ZcplcgWpgWpVZ = TempcplcgWpgWpVZ 


 ! ## ZcplcgAgWpcVWp ## 
ZcplcgAgWpcVWp = 0._dp 
TempcplcgAgWpcVWp = cplcgAgWpcVWp 
ZcplcgAgWpcVWp = TempcplcgAgWpcVWp 


 ! ## ZcplcgZgWpcVWp ## 
ZcplcgZgWpcVWp = 0._dp 
TempcplcgZgWpcVWp = cplcgZgWpcVWp 
ZcplcgZgWpcVWp = TempcplcgZgWpcVWp 


 ! ## ZcplcgWCgWCVP ## 
ZcplcgWCgWCVP = 0._dp 
TempcplcgWCgWCVP = cplcgWCgWCVP 
ZcplcgWCgWCVP = TempcplcgWCgWCVP 


 ! ## ZcplcgAgWCVWp ## 
ZcplcgAgWCVWp = 0._dp 
TempcplcgAgWCVWp = cplcgAgWCVWp 
ZcplcgAgWCVWp = TempcplcgAgWCVWp 


 ! ## ZcplcgZgWCVWp ## 
ZcplcgZgWCVWp = 0._dp 
TempcplcgZgWCVWp = cplcgZgWCVWp 
ZcplcgZgWCVWp = TempcplcgZgWCVWp 


 ! ## ZcplcgWCgWCVZ ## 
ZcplcgWCgWCVZ = 0._dp 
TempcplcgWCgWCVZ = cplcgWCgWCVZ 
ZcplcgWCgWCVZ = TempcplcgWCgWCVZ 


 ! ## ZcplcgWpgZVWp ## 
ZcplcgWpgZVWp = 0._dp 
TempcplcgWpgZVWp = cplcgWpgZVWp 
ZcplcgWpgZVWp = TempcplcgWpgZVWp 


 ! ## ZcplcgWCgZcVWp ## 
ZcplcgWCgZcVWp = 0._dp 
TempcplcgWCgZcVWp = cplcgWCgZcVWp 
ZcplcgWCgZcVWp = TempcplcgWCgZcVWp 


 ! ## ZcplcgWpgWpG0 ## 
ZcplcgWpgWpG0 = 0._dp 
TempcplcgWpgWpG0 = cplcgWpgWpG0 
ZcplcgWpgWpG0 = TempcplcgWpgWpG0 


 ! ## ZcplcgWCgWCG0 ## 
ZcplcgWCgWCG0 = 0._dp 
TempcplcgWCgWCG0 = cplcgWCgWCG0 
ZcplcgWCgWCG0 = TempcplcgWCgWCG0 


 ! ## ZcplcgZgAhh ## 
ZcplcgZgAhh = 0._dp 
TempcplcgZgAhh = cplcgZgAhh 
ZcplcgZgAhh = TempcplcgZgAhh 


 ! ## ZcplcgWpgAHp ## 
ZcplcgWpgAHp = 0._dp 
TempcplcgWpgAHp = cplcgWpgAHp 
ZcplcgWpgAHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWpgAHp(gt2) = ZcplcgWpgAHp(gt2) + ZRUZP(gt2,gt1)*TempcplcgWpgAHp(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWCgAcHp ## 
ZcplcgWCgAcHp = 0._dp 
TempcplcgWCgAcHp = cplcgWCgAcHp 
ZcplcgWCgAcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWCgAcHp(gt2) = ZcplcgWCgAcHp(gt2) + ZRUZP(gt2,gt1)*TempcplcgWCgAcHp(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWpgWphh ## 
ZcplcgWpgWphh = 0._dp 
TempcplcgWpgWphh = cplcgWpgWphh 
ZcplcgWpgWphh = TempcplcgWpgWphh 


 ! ## ZcplcgZgWpcHp ## 
ZcplcgZgWpcHp = 0._dp 
TempcplcgZgWpcHp = cplcgZgWpcHp 
ZcplcgZgWpcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgZgWpcHp(gt2) = ZcplcgZgWpcHp(gt2) + ZRUZP(gt2,gt1)*TempcplcgZgWpcHp(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWCgWChh ## 
ZcplcgWCgWChh = 0._dp 
TempcplcgWCgWChh = cplcgWCgWChh 
ZcplcgWCgWChh = TempcplcgWCgWChh 


 ! ## ZcplcgZgWCHp ## 
ZcplcgZgWCHp = 0._dp 
TempcplcgZgWCHp = cplcgZgWCHp 
ZcplcgZgWCHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgZgWCHp(gt2) = ZcplcgZgWCHp(gt2) + ZRUZP(gt2,gt1)*TempcplcgZgWCHp(gt1) 
 End Do 
End Do 


 ! ## ZcplcgZgZhh ## 
ZcplcgZgZhh = 0._dp 
TempcplcgZgZhh = cplcgZgZhh 
ZcplcgZgZhh = TempcplcgZgZhh 


 ! ## ZcplcgWpgZHp ## 
ZcplcgWpgZHp = 0._dp 
TempcplcgWpgZHp = cplcgWpgZHp 
ZcplcgWpgZHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWpgZHp(gt2) = ZcplcgWpgZHp(gt2) + ZRUZP(gt2,gt1)*TempcplcgWpgZHp(gt1) 
 End Do 
End Do 


 ! ## ZcplcgWCgZcHp ## 
ZcplcgWCgZcHp = 0._dp 
TempcplcgWCgZcHp = cplcgWCgZcHp 
ZcplcgWCgZcHp = 0._dp 
Do gt1=1,2
  Do gt2=1,2
ZcplcgWCgZcHp(gt2) = ZcplcgWCgZcHp(gt2) + ZRUZP(gt2,gt1)*TempcplcgWCgZcHp(gt1) 
 End Do 
End Do 
End Subroutine  getZCouplings 

Subroutine getGBCouplings(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,               & 
& MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,               & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,cplA0cHpVWp,cplcFdFucVWpL,cplcFdFucVWpR,     & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,       & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplhhcHpVWp,             & 
& cplhhcVWpVWp,ZcplA0cHpVWp,ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplcFeFvcVWpL,ZcplcFeFvcVWpR, & 
& ZcplcFuFdVWpL,ZcplcFuFdVWpR,ZcplcFvFeVWpL,ZcplcFvFeVWpR,ZcplcHpVPVWp,ZcplcHpVWpVZ,     & 
& ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplH0cHpVWp,ZcplhhcHpVWp,ZcplhhcVWpVWp,GcplA0HpcHp,       & 
& GcplH0HpcHp,GcplhhHpcHp,GcplA0HpcVWp,GcplA0cHpVWp,GcplG0HpcVWp,GcplG0cHpVWp,           & 
& GcplH0HpcVWp,GcplH0cHpVWp,GcplhhHpcVWp,GcplhhcHpVWp,GcplHpcHpVP,GcplHpcHpVZ,           & 
& GcplHpcVWpVP,GcplHpcVWpVZ,GcplcHpVPVWp,GcplcHpVWpVZ,GcplcFuFdHpL,GcplcFuFdHpR,         & 
& GcplcFvFeHpL,GcplcFvFeHpR,GcplcFdFucHpL,GcplcFdFucHpR,GcplcFeFvcHpL,GcplcFeFvcHpR,     & 
& GZcplA0HpcHp,GZcplH0HpcHp,GZcplhhHpcHp,GZcplA0HpcVWp,GZcplA0cHpVWp,GZcplG0HpcVWp,      & 
& GZcplG0cHpVWp,GZcplH0HpcVWp,GZcplH0cHpVWp,GZcplhhHpcVWp,GZcplhhcHpVWp,GZcplHpcHpVP,    & 
& GZcplHpcHpVZ,GZcplHpcVWpVP,GZcplHpcVWpVZ,GZcplcHpVPVWp,GZcplcHpVWpVZ,GZcplcFuFdHpL,    & 
& GZcplcFuFdHpR,GZcplcFvFeHpL,GZcplcFvFeHpR,GZcplcFdFucHpL,GZcplcFdFucHpR,               & 
& GZcplcFeFvcHpL,GZcplcFeFvcHpR,GosZcplA0HpcHp,GosZcplH0HpcHp,GosZcplhhHpcHp,            & 
& GosZcplA0HpcVWp,GosZcplA0cHpVWp,GosZcplG0HpcVWp,GosZcplG0cHpVWp,GosZcplH0HpcVWp,       & 
& GosZcplH0cHpVWp,GosZcplhhHpcVWp,GosZcplhhcHpVWp,GosZcplHpcHpVP,GosZcplHpcHpVZ,         & 
& GosZcplHpcVWpVP,GosZcplHpcVWpVZ,GosZcplcHpVPVWp,GosZcplcHpVWpVZ,GosZcplcFuFdHpL,       & 
& GosZcplcFuFdHpR,GosZcplcFvFeHpL,GosZcplcFvFeHpR,GosZcplcFdFucHpL,GosZcplcFdFucHpR,     & 
& GosZcplcFeFvcHpL,GosZcplcFeFvcHpR)

Implicit None

Real(dp), Intent(in) :: MHpOS(2),MHp2OS(2),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),          & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS(2,2)

Complex(dp), Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp), Intent(in) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp), Intent(in) :: cplA0cHpVWp(2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),              & 
& cplcFeFvcVWpR(3,3),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFvFeVWpL(3,3),              & 
& cplcFvFeVWpR(3,3),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVWp,cplcVWpVWpVZ,             & 
& cplH0cHpVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,ZcplA0cHpVWp(2),ZcplcFdFucVWpL(3,3),        & 
& ZcplcFdFucVWpR(3,3),ZcplcFeFvcVWpL(3,3),ZcplcFeFvcVWpR(3,3),ZcplcFuFdVWpL(3,3),        & 
& ZcplcFuFdVWpR(3,3),ZcplcFvFeVWpL(3,3),ZcplcFvFeVWpR(3,3),ZcplcHpVPVWp(2),              & 
& ZcplcHpVWpVZ(2),ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplH0cHpVWp(2),ZcplhhcHpVWp(2),           & 
& ZcplhhcVWpVWp

Integer :: gt1, gt2, gt3, i1, i2
Complex(dp), Intent(out) :: GcplA0HpcHp(2,2),GcplH0HpcHp(2,2),GcplhhHpcHp(2,2),GcplA0HpcVWp(2),GcplA0cHpVWp(2),   & 
& GcplG0HpcVWp(2),GcplG0cHpVWp(2),GcplH0HpcVWp(2),GcplH0cHpVWp(2),GcplhhHpcVWp(2),       & 
& GcplhhcHpVWp(2),GcplHpcHpVP(2,2),GcplHpcHpVZ(2,2),GcplHpcVWpVP(2),GcplHpcVWpVZ(2),     & 
& GcplcHpVPVWp(2),GcplcHpVWpVZ(2),GcplcFuFdHpL(3,3,2),GcplcFuFdHpR(3,3,2),               & 
& GcplcFvFeHpL(3,3,2),GcplcFvFeHpR(3,3,2),GcplcFdFucHpL(3,3,2),GcplcFdFucHpR(3,3,2),     & 
& GcplcFeFvcHpL(3,3,2),GcplcFeFvcHpR(3,3,2)

Complex(dp), Intent(out) :: GZcplA0HpcHp(2,2),GZcplH0HpcHp(2,2),GZcplhhHpcHp(2,2),GZcplA0HpcVWp(2),               & 
& GZcplA0cHpVWp(2),GZcplG0HpcVWp(2),GZcplG0cHpVWp(2),GZcplH0HpcVWp(2),GZcplH0cHpVWp(2),  & 
& GZcplhhHpcVWp(2),GZcplhhcHpVWp(2),GZcplHpcHpVP(2,2),GZcplHpcHpVZ(2,2),GZcplHpcVWpVP(2),& 
& GZcplHpcVWpVZ(2),GZcplcHpVPVWp(2),GZcplcHpVWpVZ(2),GZcplcFuFdHpL(3,3,2),               & 
& GZcplcFuFdHpR(3,3,2),GZcplcFvFeHpL(3,3,2),GZcplcFvFeHpR(3,3,2),GZcplcFdFucHpL(3,3,2),  & 
& GZcplcFdFucHpR(3,3,2),GZcplcFeFvcHpL(3,3,2),GZcplcFeFvcHpR(3,3,2)

Complex(dp), Intent(out) :: GosZcplA0HpcHp(2,2),GosZcplH0HpcHp(2,2),GosZcplhhHpcHp(2,2),GosZcplA0HpcVWp(2),       & 
& GosZcplA0cHpVWp(2),GosZcplG0HpcVWp(2),GosZcplG0cHpVWp(2),GosZcplH0HpcVWp(2),           & 
& GosZcplH0cHpVWp(2),GosZcplhhHpcVWp(2),GosZcplhhcHpVWp(2),GosZcplHpcHpVP(2,2),          & 
& GosZcplHpcHpVZ(2,2),GosZcplHpcVWpVP(2),GosZcplHpcVWpVZ(2),GosZcplcHpVPVWp(2),          & 
& GosZcplcHpVWpVZ(2),GosZcplcFuFdHpL(3,3,2),GosZcplcFuFdHpR(3,3,2),GosZcplcFvFeHpL(3,3,2),& 
& GosZcplcFvFeHpR(3,3,2),GosZcplcFdFucHpL(3,3,2),GosZcplcFdFucHpR(3,3,2),GosZcplcFeFvcHpL(3,3,2),& 
& GosZcplcFeFvcHpR(3,3,2)

 Do i2=1,2
GcplA0HpcHp(1,i2) = (1)*(MA02OS - MHp2OS(i2))/MVWpOS*cplA0cHpVWp(i2)
GosZcplA0HpcHp(1,i2) = (1)*(MA02OS - MHp2OS(i2))/MVWpOS*ZcplA0cHpVWp(i2)
GZcplA0HpcHp(1,i2) = (1)*(MA02 - MHp2(i2))/MVWp*ZcplA0cHpVWp(i2)
 End Do
 Do i2=1,2
GcplH0HpcHp(1,i2) = (1)*(MH02OS - MHp2OS(i2))/MVWpOS*cplH0cHpVWp(i2)
GosZcplH0HpcHp(1,i2) = (1)*(MH02OS - MHp2OS(i2))/MVWpOS*ZcplH0cHpVWp(i2)
GZcplH0HpcHp(1,i2) = (1)*(MH02 - MHp2(i2))/MVWp*ZcplH0cHpVWp(i2)
 End Do
 Do i2=1,2
GcplhhHpcHp(1,i2) = (1)*(Mhh2OS - MHp2OS(i2))/MVWpOS*cplhhcHpVWp(i2)
GosZcplhhHpcHp(1,i2) = (1)*(Mhh2OS - MHp2OS(i2))/MVWpOS*ZcplhhcHpVWp(i2)
GZcplhhHpcHp(1,i2) = (1)*(Mhh2 - MHp2(i2))/MVWp*ZcplhhcHpVWp(i2)
 End Do
GcplA0HpcVWp(1) = 0._dp 
GosZcplA0HpcVWp(1) = 0._dp
GZcplA0HpcVWp(1) = 0._dp
GcplA0cHpVWp(1) = 0._dp 
GosZcplA0cHpVWp(1) = 0._dp
GZcplA0cHpVWp(1) = 0._dp
GcplG0HpcVWp(1) = 0._dp 
GosZcplG0HpcVWp(1) = 0._dp
GZcplG0HpcVWp(1) = 0._dp
GcplG0cHpVWp(1) = 0._dp 
GosZcplG0cHpVWp(1) = 0._dp
GZcplG0cHpVWp(1) = 0._dp
GcplH0HpcVWp(1) = 0._dp 
GosZcplH0HpcVWp(1) = 0._dp
GZcplH0HpcVWp(1) = 0._dp
GcplH0cHpVWp(1) = 0._dp 
GosZcplH0cHpVWp(1) = 0._dp
GZcplH0cHpVWp(1) = 0._dp
GcplhhHpcVWp(1) = 0.5_dp*(1)/MVWpOS*cplhhcVWpVWp
GosZcplhhHpcVWp(1) = 0.5_dp*(1)/MVWpOS*ZcplhhcVWpVWp
GZcplhhHpcVWp(1) = 0.5_dp*(1)/MVWp*ZcplhhcVWpVWp
GcplhhcHpVWp(1) = 0.5_dp*(1)/MVWpOS*cplhhcVWpVWp
GosZcplhhcHpVWp(1) = 0.5_dp*(1)/MVWpOS*ZcplhhcVWpVWp
GZcplhhcHpVWp(1) = 0.5_dp*(1)/MVWp*ZcplhhcVWpVWp
Do i1=1,2
GcplHpcHpVP(1,i1) = 0.5_dp*(1)/MVWpOS*cplcHpVPVWp(i1)
GosZcplHpcHpVP(1,i1) = 0.5_dp*(1)/MVWpOS*ZcplcHpVPVWp(i1)
GZcplHpcHpVP(1,i1) = 0.5_dp*(1)/MVWp*ZcplcHpVPVWp(i1)
End Do 
Do i1=1,2
GcplHpcHpVZ(1,i1) = 0.5_dp*(1)/MVWpOS*cplcHpVWpVZ(i1)
GosZcplHpcHpVZ(1,i1) = 0.5_dp*(1)/MVWpOS*ZcplcHpVWpVZ(i1)
GZcplHpcHpVZ(1,i1) = 0.5_dp*(1)/MVWp*ZcplcHpVWpVZ(i1)
End Do 
GcplHpcVWpVP(1) = (-1)*(MVWp2OS - 0._dp)/MVWpOS*cplcVWpVPVWp
GosZcplHpcVWpVP(1) = (-1)*(MVWp2OS - 0._dp)/MVWpOS*ZcplcVWpVPVWp
GZcplHpcVWpVP(1) = (-1)*(MVWp2 - 0._dp)/MVWpOS*ZcplcVWpVPVWp 
GcplHpcVWpVZ(1) = (1)*(MVWp2OS - MVZ2OS)/MVWpOS*cplcVWpVWpVZ
GosZcplHpcVWpVZ(1) = (1)*(MVWp2OS - MVZ2OS)/MVWpOS*ZcplcVWpVWpVZ
GZcplHpcVWpVZ(1) = (1)*(MVWp2 - MVZ2)/MVWpOS*ZcplcVWpVWpVZ 
GcplcHpVPVWp(1) = (-1)*(0._dp - MVWp2OS)/MVWpOS*cplcVWpVPVWp
GosZcplcHpVPVWp(1) = (-1)*(0._dp - MVWp2OS)/MVWpOS*ZcplcVWpVPVWp
GZcplcHpVPVWp(1) = (-1)*(0._dp - MVWp2)/MVWpOS*ZcplcVWpVPVWp 
GcplcHpVWpVZ(1) = (-1)*(MVWp2OS - MVZ2OS)/MVWpOS*cplcVWpVWpVZ
GosZcplcHpVWpVZ(1) = (-1)*(MVWp2OS - MVZ2OS)/MVWpOS*ZcplcVWpVWpVZ
GZcplcHpVWpVZ(1) = (-1)*(MVWp2 - MVZ2)/MVWpOS*ZcplcVWpVWpVZ 
Do i1=1,3
 Do i2=1,3
GcplcFuFdHpL(i1,i2,1) = (MFuOS(i1)*cplcFuFdVWpL(i1,i2) - MFdOS(i2)*cplcFuFdVWpR(i1,i2))/MVWpOS
GcplcFuFdHpR(i1,i2,1) = -(MFdOS(i2)*cplcFuFdVWpL(i1,i2) - MFuOS(i1)*cplcFuFdVWpR(i1,i2))/MVWpOS
GosZcplcFuFdHpL(i1,i2,1) = (MFuOS(i1)*ZcplcFuFdVWpL(i1,i2) - MFdOS(i2)*ZcplcFuFdVWpR(i1,i2))/MVWpOS
GosZcplcFuFdHpR(i1,i2,1) = -(MFdOS(i2)*ZcplcFuFdVWpL(i1,i2) - MFuOS(i1)*ZcplcFuFdVWpR(i1,i2))/MVWpOS
GZcplcFuFdHpL(i1,i2,1) = (MFu(i1)*ZcplcFuFdVWpL(i1,i2) - MFd(i2)*ZcplcFuFdVWpR(i1,i2))/MVWp
GZcplcFuFdHpR(i1,i2,1) = -(MFd(i2)*ZcplcFuFdVWpL(i1,i2) - MFu(i1)*ZcplcFuFdVWpR(i1,i2))/MVWp
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFvFeHpL(i1,i2,1) = (0.*cplcFvFeVWpL(i1,i2) - MFeOS(i2)*cplcFvFeVWpR(i1,i2))/MVWpOS
GcplcFvFeHpR(i1,i2,1) = -(MFeOS(i2)*cplcFvFeVWpL(i1,i2) - 0.*cplcFvFeVWpR(i1,i2))/MVWpOS
GosZcplcFvFeHpL(i1,i2,1) = (0.*ZcplcFvFeVWpL(i1,i2) - MFeOS(i2)*ZcplcFvFeVWpR(i1,i2))/MVWpOS
GosZcplcFvFeHpR(i1,i2,1) = -(MFeOS(i2)*ZcplcFvFeVWpL(i1,i2) - 0.*ZcplcFvFeVWpR(i1,i2))/MVWpOS
GZcplcFvFeHpL(i1,i2,1) = (0._dp*ZcplcFvFeVWpL(i1,i2) - MFe(i2)*ZcplcFvFeVWpR(i1,i2))/MVWp
GZcplcFvFeHpR(i1,i2,1) = -(MFe(i2)*ZcplcFvFeVWpL(i1,i2) - 0._dp*ZcplcFvFeVWpR(i1,i2))/MVWp
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFdFucHpL(i1,i2,1) = (MFdOS(i1)*cplcFdFucVWpL(i1,i2) - MFuOS(i2)*cplcFdFucVWpR(i1,i2))/MVWpOS
GcplcFdFucHpR(i1,i2,1) = -(MFuOS(i2)*cplcFdFucVWpL(i1,i2) - MFdOS(i1)*cplcFdFucVWpR(i1,i2))/MVWpOS
GosZcplcFdFucHpL(i1,i2,1) = (MFdOS(i1)*ZcplcFdFucVWpL(i1,i2) - MFuOS(i2)*ZcplcFdFucVWpR(i1,i2))/MVWpOS
GosZcplcFdFucHpR(i1,i2,1) = -(MFuOS(i2)*ZcplcFdFucVWpL(i1,i2) - MFdOS(i1)*ZcplcFdFucVWpR(i1,i2))/MVWpOS
GZcplcFdFucHpL(i1,i2,1) = (MFd(i1)*ZcplcFdFucVWpL(i1,i2) - MFu(i2)*ZcplcFdFucVWpR(i1,i2))/MVWp
GZcplcFdFucHpR(i1,i2,1) = -(MFu(i2)*ZcplcFdFucVWpL(i1,i2) - MFd(i1)*ZcplcFdFucVWpR(i1,i2))/MVWp
 End Do
End Do 
Do i1=1,3
 Do i2=1,3
GcplcFeFvcHpL(i1,i2,1) = (MFeOS(i1)*cplcFeFvcVWpL(i1,i2) - 0.*cplcFeFvcVWpR(i1,i2))/MVWpOS
GcplcFeFvcHpR(i1,i2,1) = -(0.*cplcFeFvcVWpL(i1,i2) - MFeOS(i1)*cplcFeFvcVWpR(i1,i2))/MVWpOS
GosZcplcFeFvcHpL(i1,i2,1) = (MFeOS(i1)*ZcplcFeFvcVWpL(i1,i2) - 0.*ZcplcFeFvcVWpR(i1,i2))/MVWpOS
GosZcplcFeFvcHpR(i1,i2,1) = -(0.*ZcplcFeFvcVWpL(i1,i2) - MFeOS(i1)*ZcplcFeFvcVWpR(i1,i2))/MVWpOS
GZcplcFeFvcHpL(i1,i2,1) = (MFe(i1)*ZcplcFeFvcVWpL(i1,i2) - 0._dp*ZcplcFeFvcVWpR(i1,i2))/MVWp
GZcplcFeFvcHpR(i1,i2,1) = -(0._dp*ZcplcFeFvcVWpL(i1,i2) - MFe(i1)*ZcplcFeFvcVWpR(i1,i2))/MVWp
 End Do
End Do 
End Subroutine  getGBCouplings 

Subroutine WaveFunctionRenormalisation(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,               & 
& MFu2OS,MFeOS,MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,               & 
& MVZOS,MVZ2OS,MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,              & 
& MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,              & 
& MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,           & 
& lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0HpcHp,cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,              & 
& cplA0A0A0A0,cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0G0G0H0,cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,             & 
& cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,             & 
& cplH0H0hhhh,cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,          & 
& cplA0H0VZ,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,       & 
& cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,      & 
& cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0cVWpVWp,cplA0A0VZVZ,            & 
& cplA0HpcVWpVP,cplA0HpcVWpVZ,cplA0cHpVPVWp,cplA0cHpVWpVZ,cplG0G0cVWpVWp,cplG0G0VZVZ,    & 
& cplG0HpcVWpVP,cplG0HpcVWpVZ,cplG0cHpVPVWp,cplG0cHpVWpVZ,cplH0H0cVWpVWp,cplH0H0VZVZ,    & 
& cplH0HpcVWpVP,cplH0HpcVWpVZ,cplH0cHpVPVWp,cplH0cHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,    & 
& cplhhHpcVWpVP,cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,     & 
& cplHpcHpcVWpVWp,cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,          & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,             & 
& cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,             & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFvFvVZL,           & 
& cplcFvFvVZR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,        & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,       & 
& cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,               & 
& cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,      & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,        & 
& cplcgWCgWCG0,cplcgZgAhh,cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,            & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,GcplA0HpcHp,              & 
& GcplH0HpcHp,GcplhhHpcHp,GcplA0HpcVWp,GcplA0cHpVWp,GcplG0HpcVWp,GcplG0cHpVWp,           & 
& GcplH0HpcVWp,GcplH0cHpVWp,GcplhhHpcVWp,GcplhhcHpVWp,GcplHpcHpVP,GcplHpcHpVZ,           & 
& GcplHpcVWpVP,GcplHpcVWpVZ,GcplcHpVPVWp,GcplcHpVWpVZ,GcplcFuFdHpL,GcplcFuFdHpR,         & 
& GcplcFvFeHpL,GcplcFvFeHpR,GcplcFdFucHpL,GcplcFdFucHpR,GcplcFeFvcHpL,GcplcFeFvcHpR,     & 
& dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,dlam3,dlam2,dv,dZP,              & 
& dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,ZfvL,ZfG0,Zfhh,ZfA0,           & 
& ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,ZfVPVZ,ZfVZVP,ctcplA0A0G0,     & 
& ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp,ctcplG0G0hh,ctcplG0H0H0,              & 
& ctcplH0H0hh,ctcplH0HpcHp,ctcplhhhhhh,ctcplhhHpcHp,ctcplA0H0VZ,ctcplA0HpcVWp,           & 
& ctcplA0cHpVWp,ctcplG0hhVZ,ctcplG0HpcVWp,ctcplG0cHpVWp,ctcplH0HpcVWp,ctcplH0cHpVWp,     & 
& ctcplhhHpcVWp,ctcplhhcHpVWp,ctcplHpcHpVP,ctcplHpcHpVZ,ctcplhhcVWpVWp,ctcplhhVZVZ,      & 
& ctcplHpcVWpVP,ctcplHpcVWpVZ,ctcplcHpVPVWp,ctcplcHpVWpVZ,ctcplVGVGVG,ctcplcVWpVPVWp,    & 
& ctcplcVWpVWpVZ,ctcplcFdFdG0L,ctcplcFdFdG0R,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFuFdHpL,  & 
& ctcplcFuFdHpR,ctcplcFeFeG0L,ctcplcFeFeG0R,ctcplcFeFehhL,ctcplcFeFehhR,ctcplcFvFeHpL,   & 
& ctcplcFvFeHpR,ctcplcFuFuG0L,ctcplcFuFuG0R,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFucHpL,  & 
& ctcplcFdFucHpR,ctcplcFeFvcHpL,ctcplcFeFvcHpR,ctcplcFdFdVGL,ctcplcFdFdVGR,              & 
& ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFuFdVWpL,ctcplcFuFdVWpR,ctcplcFdFdVZL,               & 
& ctcplcFdFdVZR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFvFeVWpL,ctcplcFvFeVWpR,               & 
& ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,   & 
& ctcplcFuFuVZL,ctcplcFuFuVZR,ctcplcFdFucVWpL,ctcplcFdFucVWpR,ctcplcFvFvVZL,             & 
& ctcplcFvFvVZR,ctcplcFeFvcVWpL,ctcplcFeFvcVWpR,MLambda,deltaM,kont)

Implicit None 
Real(dp),Intent(inout) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(inout) :: v

Complex(dp),Intent(in) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplA0A0A0A0,cplA0A0G0G0,           & 
& cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0G0G0H0,cplA0G0H0hh,         & 
& cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),cplG0G0G0G0,cplG0G0H0H0,               & 
& cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),cplH0H0H0H0,               & 
& cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,cplhhhhHpcHp(2,2),         & 
& cplHpHpcHpcHp(2,2,2,2),cplA0H0VZ,cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcVWp(2),            & 
& cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP(2),  & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0cVWpVWp,cplA0A0VZVZ,               & 
& cplA0HpcVWpVP(2),cplA0HpcVWpVZ(2),cplA0cHpVPVWp(2),cplA0cHpVWpVZ(2),cplG0G0cVWpVWp,    & 
& cplG0G0VZVZ,cplG0HpcVWpVP(2),cplG0HpcVWpVZ(2),cplG0cHpVPVWp(2),cplG0cHpVWpVZ(2),       & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP(2),cplH0HpcVWpVZ(2),cplH0cHpVPVWp(2),         & 
& cplH0cHpVWpVZ(2),cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP(2),cplhhHpcVWpVZ(2),         & 
& cplhhcHpVPVWp(2),cplhhcHpVWpVZ(2),cplHpcHpVPVP(2,2),cplHpcHpVPVZ(2,2),cplHpcHpcVWpVWp(2,2),& 
& cplHpcHpVZVZ(2,2),cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),& 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),               & 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3), & 
& cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3), & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVGL(3,3),& 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,          & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,       & 
& cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,               & 
& cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,      & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,        & 
& cplcgWCgWCG0,cplcgZgAhh,cplcgWpgAHp(2),cplcgWCgAcHp(2),cplcgWpgWphh,cplcgZgWpcHp(2),   & 
& cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcHp(2)

Real(dp),Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(in) :: MHpOS(2),MHp2OS(2),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),          & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS(2,2)

Complex(dp),Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Complex(dp) :: PiHp(2,2,2),DerPiHp(2,2,2),SigmaLFd(3,3,3),SigmaSLFd(3,3,3),SigmaSRFd(3,3,3),         & 
& SigmaRFd(3,3,3),DerSigmaLFd(3,3,3),DerSigmaSLFd(3,3,3),DerSigmaSRFd(3,3,3),            & 
& DerSigmaRFd(3,3,3),DerSigmaLirFd(3,3,3),DerSigmaSLirFd(3,3,3),DerSigmaSRirFd(3,3,3),   & 
& DerSigmaRirFd(3,3,3),SigmaLFu(3,3,3),SigmaSLFu(3,3,3),SigmaSRFu(3,3,3),SigmaRFu(3,3,3),& 
& DerSigmaLFu(3,3,3),DerSigmaSLFu(3,3,3),DerSigmaSRFu(3,3,3),DerSigmaRFu(3,3,3),         & 
& DerSigmaLirFu(3,3,3),DerSigmaSLirFu(3,3,3),DerSigmaSRirFu(3,3,3),DerSigmaRirFu(3,3,3), & 
& SigmaLFe(3,3,3),SigmaSLFe(3,3,3),SigmaSRFe(3,3,3),SigmaRFe(3,3,3),DerSigmaLFe(3,3,3),  & 
& DerSigmaSLFe(3,3,3),DerSigmaSRFe(3,3,3),DerSigmaRFe(3,3,3),DerSigmaLirFe(3,3,3),       & 
& DerSigmaSLirFe(3,3,3),DerSigmaSRirFe(3,3,3),DerSigmaRirFe(3,3,3),SigmaLFv(3,3,3),      & 
& SigmaSLFv(3,3,3),SigmaSRFv(3,3,3),SigmaRFv(3,3,3),DerSigmaLFv(3,3,3),DerSigmaSLFv(3,3,3),& 
& DerSigmaSRFv(3,3,3),DerSigmaRFv(3,3,3),DerSigmaLirFv(3,3,3),DerSigmaSLirFv(3,3,3),     & 
& DerSigmaSRirFv(3,3,3),DerSigmaRirFv(3,3,3),PiG0,DerPiG0,Pihh,DerPihh,PiA0,             & 
& DerPiA0,PiH0,DerPiH0,PiVG,DerPiVG,PiVP,DerPiVP,PiVZ,DerPiVZ,PiVWp,DerPiVWp,            & 
& PiVPlight0,DerPiVPlight0,PiVPheavy0,DerPiVPheavy0,PiVPlightMZ,DerPiVPlightMZ,          & 
& PiVPheavyMZ,DerPiVPheavyMZ,PiVPVZ,DerPiVPVZ,PiVZVP,DerPiVZVP,PiVZG0,DerPiVZG0,         & 
& PiG0VZ,DerPiG0VZ,PiVZhh,DerPiVZhh,PihhVZ,DerPihhVZ,PiVZA0,DerPiVZA0,PiA0VZ,            & 
& DerPiA0VZ,PiVZH0,DerPiVZH0,PiH0VZ,DerPiH0VZ,PiVWpHp(2,2,2),DerPiVWpHp(2,2,2),          & 
& PiHpVWp(2,2,2),DerPiHpVWp(2,2,2)

Complex(dp) :: PiHpDR(2,2,2),DerPiHpDR(2,2,2),SigmaLFdDR(3,3,3),SigmaSLFdDR(3,3,3),SigmaSRFdDR(3,3,3),& 
& SigmaRFdDR(3,3,3),DerSigmaLFdDR(3,3,3),DerSigmaSLFdDR(3,3,3),DerSigmaSRFdDR(3,3,3),    & 
& DerSigmaRFdDR(3,3,3),DerSigmaLirFdDR(3,3,3),DerSigmaSLirFdDR(3,3,3),DerSigmaSRirFdDR(3,3,3),& 
& DerSigmaRirFdDR(3,3,3),SigmaLFuDR(3,3,3),SigmaSLFuDR(3,3,3),SigmaSRFuDR(3,3,3),        & 
& SigmaRFuDR(3,3,3),DerSigmaLFuDR(3,3,3),DerSigmaSLFuDR(3,3,3),DerSigmaSRFuDR(3,3,3),    & 
& DerSigmaRFuDR(3,3,3),DerSigmaLirFuDR(3,3,3),DerSigmaSLirFuDR(3,3,3),DerSigmaSRirFuDR(3,3,3),& 
& DerSigmaRirFuDR(3,3,3),SigmaLFeDR(3,3,3),SigmaSLFeDR(3,3,3),SigmaSRFeDR(3,3,3),        & 
& SigmaRFeDR(3,3,3),DerSigmaLFeDR(3,3,3),DerSigmaSLFeDR(3,3,3),DerSigmaSRFeDR(3,3,3),    & 
& DerSigmaRFeDR(3,3,3),DerSigmaLirFeDR(3,3,3),DerSigmaSLirFeDR(3,3,3),DerSigmaSRirFeDR(3,3,3),& 
& DerSigmaRirFeDR(3,3,3),SigmaLFvDR(3,3,3),SigmaSLFvDR(3,3,3),SigmaSRFvDR(3,3,3),        & 
& SigmaRFvDR(3,3,3),DerSigmaLFvDR(3,3,3),DerSigmaSLFvDR(3,3,3),DerSigmaSRFvDR(3,3,3),    & 
& DerSigmaRFvDR(3,3,3),DerSigmaLirFvDR(3,3,3),DerSigmaSLirFvDR(3,3,3),DerSigmaSRirFvDR(3,3,3),& 
& DerSigmaRirFvDR(3,3,3),PiG0DR,DerPiG0DR,PihhDR,DerPihhDR,PiA0DR,DerPiA0DR,             & 
& PiH0DR,DerPiH0DR,PiVGDR,DerPiVGDR,PiVPDR,DerPiVPDR,PiVZDR,DerPiVZDR,PiVWpDR,           & 
& DerPiVWpDR,PiVPlight0DR,DerPiVPlight0DR,PiVPheavy0DR,DerPiVPheavy0DR,PiVPlightMZDR,    & 
& DerPiVPlightMZDR,PiVPheavyMZDR,DerPiVPheavyMZDR,PiVPVZDR,DerPiVPVZDR,PiVZVPDR,         & 
& DerPiVZVPDR,PiVZG0DR,DerPiVZG0DR,PiG0VZDR,DerPiG0VZDR,PiVZhhDR,DerPiVZhhDR,            & 
& PihhVZDR,DerPihhVZDR,PiVZA0DR,DerPiVZA0DR,PiA0VZDR,DerPiA0VZDR,PiVZH0DR,               & 
& DerPiVZH0DR,PiH0VZDR,DerPiH0VZDR,PiVWpHpDR(2,2,2),DerPiVWpHpDR(2,2,2),PiHpVWpDR(2,2,2),& 
& DerPiHpVWpDR(2,2,2)

Complex(dp) :: PiHpOS(2,2,2),DerPiHpOS(2,2,2),SigmaLFdOS(3,3,3),SigmaSLFdOS(3,3,3),SigmaSRFdOS(3,3,3),& 
& SigmaRFdOS(3,3,3),DerSigmaLFdOS(3,3,3),DerSigmaSLFdOS(3,3,3),DerSigmaSRFdOS(3,3,3),    & 
& DerSigmaRFdOS(3,3,3),DerSigmaLirFdOS(3,3,3),DerSigmaSLirFdOS(3,3,3),DerSigmaSRirFdOS(3,3,3),& 
& DerSigmaRirFdOS(3,3,3),SigmaLFuOS(3,3,3),SigmaSLFuOS(3,3,3),SigmaSRFuOS(3,3,3),        & 
& SigmaRFuOS(3,3,3),DerSigmaLFuOS(3,3,3),DerSigmaSLFuOS(3,3,3),DerSigmaSRFuOS(3,3,3),    & 
& DerSigmaRFuOS(3,3,3),DerSigmaLirFuOS(3,3,3),DerSigmaSLirFuOS(3,3,3),DerSigmaSRirFuOS(3,3,3),& 
& DerSigmaRirFuOS(3,3,3),SigmaLFeOS(3,3,3),SigmaSLFeOS(3,3,3),SigmaSRFeOS(3,3,3),        & 
& SigmaRFeOS(3,3,3),DerSigmaLFeOS(3,3,3),DerSigmaSLFeOS(3,3,3),DerSigmaSRFeOS(3,3,3),    & 
& DerSigmaRFeOS(3,3,3),DerSigmaLirFeOS(3,3,3),DerSigmaSLirFeOS(3,3,3),DerSigmaSRirFeOS(3,3,3),& 
& DerSigmaRirFeOS(3,3,3),SigmaLFvOS(3,3,3),SigmaSLFvOS(3,3,3),SigmaSRFvOS(3,3,3),        & 
& SigmaRFvOS(3,3,3),DerSigmaLFvOS(3,3,3),DerSigmaSLFvOS(3,3,3),DerSigmaSRFvOS(3,3,3),    & 
& DerSigmaRFvOS(3,3,3),DerSigmaLirFvOS(3,3,3),DerSigmaSLirFvOS(3,3,3),DerSigmaSRirFvOS(3,3,3),& 
& DerSigmaRirFvOS(3,3,3),PiG0OS,DerPiG0OS,PihhOS,DerPihhOS,PiA0OS,DerPiA0OS,             & 
& PiH0OS,DerPiH0OS,PiVGOS,DerPiVGOS,PiVPOS,DerPiVPOS,PiVZOS,DerPiVZOS,PiVWpOS,           & 
& DerPiVWpOS,PiVPlight0OS,DerPiVPlight0OS,PiVPheavy0OS,DerPiVPheavy0OS,PiVPlightMZOS,    & 
& DerPiVPlightMZOS,PiVPheavyMZOS,DerPiVPheavyMZOS,PiVPVZOS,DerPiVPVZOS,PiVZVPOS,         & 
& DerPiVZVPOS,PiVZG0OS,DerPiVZG0OS,PiG0VZOS,DerPiG0VZOS,PiVZhhOS,DerPiVZhhOS,            & 
& PihhVZOS,DerPihhVZOS,PiVZA0OS,DerPiVZA0OS,PiA0VZOS,DerPiA0VZOS,PiVZH0OS,               & 
& DerPiVZH0OS,PiH0VZOS,DerPiH0VZOS,PiVWpHpOS(2,2,2),DerPiVWpHpOS(2,2,2),PiHpVWpOS(2,2,2),& 
& DerPiHpVWpOS(2,2,2)

Real(dp), Intent(in) :: MLambda, deltaM 

Integer, Intent(out) :: kont 
Real(dp),Intent(out) :: dg1,dg2,dg3,dMHD2,dMHU2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp),Intent(out) :: dYe(3,3),dYd(3,3),dYu(3,3),dlam5,dlam1,dlam4,dlam3,dlam2,dZDL(3,3),dZDR(3,3),         & 
& dZUL(3,3),dZUR(3,3),dZEL(3,3),dZER(3,3)

Complex(dp),Intent(out) :: ZfVG,ZfvL(3,3),ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp(2,2),ZfDL(3,3),               & 
& ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfEL(3,3),ZfER(3,3),ZfVPVZ,ZfVZVP

Complex(dp),Intent(out) :: ctcplA0A0G0,ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp(2,2),ctcplG0G0hh,        & 
& ctcplG0H0H0,ctcplH0H0hh,ctcplH0HpcHp(2,2),ctcplhhhhhh,ctcplhhHpcHp(2,2),               & 
& ctcplA0H0VZ,ctcplA0HpcVWp(2),ctcplA0cHpVWp(2),ctcplG0hhVZ,ctcplG0HpcVWp(2),            & 
& ctcplG0cHpVWp(2),ctcplH0HpcVWp(2),ctcplH0cHpVWp(2),ctcplhhHpcVWp(2),ctcplhhcHpVWp(2),  & 
& ctcplHpcHpVP(2,2),ctcplHpcHpVZ(2,2),ctcplhhcVWpVWp,ctcplhhVZVZ,ctcplHpcVWpVP(2),       & 
& ctcplHpcVWpVZ(2),ctcplcHpVPVWp(2),ctcplcHpVWpVZ(2),ctcplVGVGVG,ctcplcVWpVPVWp,         & 
& ctcplcVWpVWpVZ,ctcplcFdFdG0L(3,3),ctcplcFdFdG0R(3,3),ctcplcFdFdhhL(3,3),               & 
& ctcplcFdFdhhR(3,3),ctcplcFuFdHpL(3,3,2),ctcplcFuFdHpR(3,3,2),ctcplcFeFeG0L(3,3),       & 
& ctcplcFeFeG0R(3,3),ctcplcFeFehhL(3,3),ctcplcFeFehhR(3,3),ctcplcFvFeHpL(3,3,2),         & 
& ctcplcFvFeHpR(3,3,2),ctcplcFuFuG0L(3,3),ctcplcFuFuG0R(3,3),ctcplcFuFuhhL(3,3),         & 
& ctcplcFuFuhhR(3,3),ctcplcFdFucHpL(3,3,2),ctcplcFdFucHpR(3,3,2),ctcplcFeFvcHpL(3,3,2),  & 
& ctcplcFeFvcHpR(3,3,2),ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),ctcplcFdFdVPL(3,3),        & 
& ctcplcFdFdVPR(3,3),ctcplcFuFdVWpL(3,3),ctcplcFuFdVWpR(3,3),ctcplcFdFdVZL(3,3),         & 
& ctcplcFdFdVZR(3,3),ctcplcFeFeVPL(3,3),ctcplcFeFeVPR(3,3),ctcplcFvFeVWpL(3,3),          & 
& ctcplcFvFeVWpR(3,3),ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),ctcplcFuFuVGL(3,3),          & 
& ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),           & 
& ctcplcFuFuVZR(3,3),ctcplcFdFucVWpL(3,3),ctcplcFdFucVWpR(3,3),ctcplcFvFvVZL(3,3),       & 
& ctcplcFvFvVZR(3,3),ctcplcFeFvcVWpL(3,3),ctcplcFeFvcVWpR(3,3)

Complex(dp),Intent(in) :: GcplA0HpcHp(2,2),GcplH0HpcHp(2,2),GcplhhHpcHp(2,2),GcplA0HpcVWp(2),GcplA0cHpVWp(2),   & 
& GcplG0HpcVWp(2),GcplG0cHpVWp(2),GcplH0HpcVWp(2),GcplH0cHpVWp(2),GcplhhHpcVWp(2),       & 
& GcplhhcHpVWp(2),GcplHpcHpVP(2,2),GcplHpcHpVZ(2,2),GcplHpcVWpVP(2),GcplHpcVWpVZ(2),     & 
& GcplcHpVPVWp(2),GcplcHpVWpVZ(2),GcplcFuFdHpL(3,3,2),GcplcFuFdHpR(3,3,2),               & 
& GcplcFvFeHpL(3,3,2),GcplcFvFeHpR(3,3,2),GcplcFdFucHpL(3,3,2),GcplcFdFucHpR(3,3,2),     & 
& GcplcFeFvcHpL(3,3,2),GcplcFeFvcHpR(3,3,2)

Real(dp) ::  g1D(70) 
Real(dp) :: p2 
Logical :: TwoLoopRGEsave 
Real(dp) ::MVG,MVP,MVG2,MVP2
Complex(dp) ::  Tad1Loop(2)
Complex(dp) :: MatTad_hh(1,1)=0._dp 
Integer :: i1,i2,i3 

MVG = MLambda 
MVP = MLambda 
MVG2 = MLambda**2 
MVP2 = MLambda**2 

Call OneLoopTadpoleshh(v,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0A0hh,cplcFdFdhhL,cplcFdFdhhR,          & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplcgWpgWphh,cplcgWCgWChh,   & 
& cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhcVWpVWp,cplhhVZVZ,Tad1Loop(1:1))

MatTad_hh(1,1) = Tad1Loop(1) 
! Not working!! 
MatTad_hh= 0._dp
!--------------------------
!Hp
!--------------------------
Do i1=1,2
p2 = MHp2(i1)
Call Pi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,MFe,MFe2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcHp,cplA0cHpVWp,cplcFdFucHpL,               & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0cHpVWp,cplcgZgWpcHp,cplcgWpgZHp,           & 
& cplcgWCgZcHp,cplcgZgWCHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,     & 
& cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp,cplG0G0HpcHp,cplH0H0HpcHp,             & 
& cplhhhhHpcHp,cplHpHpcHpcHp,cplHpcHpVPVP,cplHpcHpcVWpVWp,cplHpcHpVZVZ,kont,             & 
& PiHp(i1,:,:))

Call DerPi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,MFe,              & 
& MFe2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcHp,cplA0cHpVWp,cplcFdFucHpL,          & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0cHpVWp,cplcgZgWpcHp,cplcgWpgZHp,           & 
& cplcgWCgZcHp,cplcgZgWCHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,     & 
& cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp,cplG0G0HpcHp,cplH0H0HpcHp,             & 
& cplhhhhHpcHp,cplHpHpcHpcHp,cplHpcHpVPVP,cplHpcHpcVWpVWp,cplHpcHpVZVZ,kont,             & 
& DerPiHp(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopHp(p2,MHp,MHp2,MA0,MA02,MVWp,MVWp2,MFd,MFd2,MFu,MFu2,MFe,              & 
& MFe2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MVZ,MVZ2,cplA0HpcHp,cplA0cHpVWp,cplcFdFucHpL,          & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0cHpVWp,cplcgZgWpcHp,cplcgWpgZHp,           & 
& cplcgWCgZcHp,cplcgZgWCHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,     & 
& cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp,cplG0G0HpcHp,cplH0H0HpcHp,             & 
& cplhhhhHpcHp,cplHpHpcHpcHp,cplHpcHpVPVP,cplHpcHpcVWpVWp,cplHpcHpVZVZ,kont,             & 
& DerPiHpDR(i1,:,:))

p2 =MHp2OS(i1)
Call DerPi1LoopHp(p2,MHpOS,MHp2OS,MA0OS,MA02OS,MVWpOS,MVWp2OS,MFdOS,MFd2OS,           & 
& MFuOS,MFu2OS,MFeOS,MFe2OS,MG0OS,MG02OS,MH0OS,MH02OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,         & 
& cplA0HpcHp,cplA0cHpVWp,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,            & 
& cplG0cHpVWp,cplcgZgWpcHp,cplcgWpgZHp,cplcgWCgZcHp,cplcgZgWCHp,cplH0HpcHp,              & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& cplA0A0HpcHp,cplG0G0HpcHp,cplH0H0HpcHp,cplhhhhHpcHp,cplHpHpcHpcHp,cplHpcHpVPVP,        & 
& cplHpcHpcVWpVWp,cplHpcHpVZVZ,kont,DerPiHpOS(i1,:,:))

DerPiHp(i1,:,:) = DerPiHp(i1,:,:)- DerPiHpDR(i1,:,:) + DerPiHpOS(i1,:,:)
IRdivonly=.False. 
End if
End do


!--------------------------
!Fd
!--------------------------
Do i1=1,3
p2 =MFd2(i1)
Call Sigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,MFu2,           & 
& MVWp,MVWp2,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,SigmaLFd(i1,:,:),SigmaRFd(i1,:,:),SigmaSLFd(i1,:,:)        & 
& ,SigmaSRFd(i1,:,:))

Call DerSigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,             & 
& MFu2,MVWp,MVWp2,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,           & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,              & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,DerSigmaLFd(i1,:,:),DerSigmaRFd(i1,:,:)       & 
& ,DerSigmaSLFd(i1,:,:),DerSigmaSRFd(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFd(p2,MG0,MG02,MFd,MFd2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MFu,             & 
& MFu2,MVWp,MVWp2,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,           & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,              & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,DerSigmaLFdDR(i1,:,:),DerSigmaRFdDR(i1,:,:)   & 
& ,DerSigmaSLFdDR(i1,:,:),DerSigmaSRFdDR(i1,:,:))

p2 =MFd2OS(i1)
Call DerSigma1LoopFd(p2,MG0OS,MG02OS,MFdOS,MFd2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,          & 
& MHpOS,MHp2OS,MFuOS,MFu2OS,MVWpOS,MVWp2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,DerSigmaLFdOS(i1,:,:)& 
& ,DerSigmaRFdOS(i1,:,:),DerSigmaSLFdOS(i1,:,:),DerSigmaSRFdOS(i1,:,:))

DerSigmaLFd(i1,:,:) = DerSigmaLFd(i1,:,:) - DerSigmaLFdDR(i1,:,:)! + DerSigmaLFdOS(i1,:,:)
DerSigmaRFd(i1,:,:) = DerSigmaRFd(i1,:,:) - DerSigmaRFdDR(i1,:,:)! + DerSigmaRFdOS(i1,:,:)
DerSigmaSLFd(i1,:,:) = DerSigmaSLFd(i1,:,:) - DerSigmaSLFdDR(i1,:,:)! + DerSigmaSLFdOS(i1,:,:)
DerSigmaSRFd(i1,:,:) = DerSigmaSRFd(i1,:,:) - DerSigmaSRFdDR(i1,:,:)! + DerSigmaSRFdOS(i1,:,:)
DerSigmaLirFd(i1,:,:) = + DerSigmaLFdOS(i1,:,:)
DerSigmaRirFd(i1,:,:) = + DerSigmaRFdOS(i1,:,:)
DerSigmaSLirFd(i1,:,:) = + DerSigmaSLFdOS(i1,:,:)
DerSigmaSRirFd(i1,:,:) = + DerSigmaSRFdOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFd(i1,:,:) = 0._dp
DerSigmaRirFd(i1,:,:) = 0._dp
DerSigmaSLirFd(i1,:,:) = 0._dp
DerSigmaSRirFd(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Fu
!--------------------------
Do i1=1,3
p2 =MFu2(i1)
Call Sigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,Mhh,              & 
& Mhh2,MVZ,MVZ2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,           & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,SigmaLFu(i1,:,:),SigmaRFu(i1,:,:),SigmaSLFu(i1,:,:)& 
& ,SigmaSRFu(i1,:,:))

Call DerSigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,               & 
& Mhh,Mhh2,MVZ,MVZ2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,       & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,DerSigmaLFu(i1,:,:),DerSigmaRFu(i1,:,:)            & 
& ,DerSigmaSLFu(i1,:,:),DerSigmaSRFu(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFu(p2,MHp,MHp2,MFd,MFd2,MVWp,MVWp2,MG0,MG02,MFu,MFu2,               & 
& Mhh,Mhh2,MVZ,MVZ2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,       & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,DerSigmaLFuDR(i1,:,:),DerSigmaRFuDR(i1,:,:)        & 
& ,DerSigmaSLFuDR(i1,:,:),DerSigmaSRFuDR(i1,:,:))

p2 =MFu2OS(i1)
Call DerSigma1LoopFu(p2,MHpOS,MHp2OS,MFdOS,MFd2OS,MVWpOS,MVWp2OS,MG0OS,               & 
& MG02OS,MFuOS,MFu2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,    & 
& cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,              & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,DerSigmaLFuOS(i1,:,:)      & 
& ,DerSigmaRFuOS(i1,:,:),DerSigmaSLFuOS(i1,:,:),DerSigmaSRFuOS(i1,:,:))

DerSigmaLFu(i1,:,:) = DerSigmaLFu(i1,:,:) - DerSigmaLFuDR(i1,:,:)! + DerSigmaLFuOS(i1,:,:)
DerSigmaRFu(i1,:,:) = DerSigmaRFu(i1,:,:) - DerSigmaRFuDR(i1,:,:)! + DerSigmaRFuOS(i1,:,:)
DerSigmaSLFu(i1,:,:) = DerSigmaSLFu(i1,:,:) - DerSigmaSLFuDR(i1,:,:)! + DerSigmaSLFuOS(i1,:,:)
DerSigmaSRFu(i1,:,:) = DerSigmaSRFu(i1,:,:) - DerSigmaSRFuDR(i1,:,:)! + DerSigmaSRFuOS(i1,:,:)
DerSigmaLirFu(i1,:,:) = + DerSigmaLFuOS(i1,:,:)
DerSigmaRirFu(i1,:,:) = + DerSigmaRFuOS(i1,:,:)
DerSigmaSLirFu(i1,:,:) = + DerSigmaSLFuOS(i1,:,:)
DerSigmaSRirFu(i1,:,:) = + DerSigmaSRFuOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFu(i1,:,:) = 0._dp
DerSigmaRirFu(i1,:,:) = 0._dp
DerSigmaSLirFu(i1,:,:) = 0._dp
DerSigmaSRirFu(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Fe
!--------------------------
Do i1=1,3
p2 =MFe2(i1)
Call Sigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,               & 
& MVWp2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,         & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,         & 
& SigmaLFe(i1,:,:),SigmaRFe(i1,:,:),SigmaSLFe(i1,:,:),SigmaSRFe(i1,:,:))

Call DerSigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,            & 
& MVWp2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,         & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,         & 
& DerSigmaLFe(i1,:,:),DerSigmaRFe(i1,:,:),DerSigmaSLFe(i1,:,:),DerSigmaSRFe(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFe(p2,MG0,MG02,MFe,MFe2,Mhh,Mhh2,MVZ,MVZ2,MHp,MHp2,MVWp,            & 
& MVWp2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,         & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,         & 
& DerSigmaLFeDR(i1,:,:),DerSigmaRFeDR(i1,:,:),DerSigmaSLFeDR(i1,:,:),DerSigmaSRFeDR(i1,:,:))

p2 =MFe2OS(i1)
Call DerSigma1LoopFe(p2,MG0OS,MG02OS,MFeOS,MFe2OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,          & 
& MHpOS,MHp2OS,MVWpOS,MVWp2OS,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,           & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,             & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,DerSigmaLFeOS(i1,:,:),DerSigmaRFeOS(i1,:,:),               & 
& DerSigmaSLFeOS(i1,:,:),DerSigmaSRFeOS(i1,:,:))

DerSigmaLFe(i1,:,:) = DerSigmaLFe(i1,:,:) - DerSigmaLFeDR(i1,:,:)! + DerSigmaLFeOS(i1,:,:)
DerSigmaRFe(i1,:,:) = DerSigmaRFe(i1,:,:) - DerSigmaRFeDR(i1,:,:)! + DerSigmaRFeOS(i1,:,:)
DerSigmaSLFe(i1,:,:) = DerSigmaSLFe(i1,:,:) - DerSigmaSLFeDR(i1,:,:)! + DerSigmaSLFeOS(i1,:,:)
DerSigmaSRFe(i1,:,:) = DerSigmaSRFe(i1,:,:) - DerSigmaSRFeDR(i1,:,:)! + DerSigmaSRFeOS(i1,:,:)
DerSigmaLirFe(i1,:,:) = + DerSigmaLFeOS(i1,:,:)
DerSigmaRirFe(i1,:,:) = + DerSigmaRFeOS(i1,:,:)
DerSigmaSLirFe(i1,:,:) = + DerSigmaSLFeOS(i1,:,:)
DerSigmaSRirFe(i1,:,:) = + DerSigmaSRFeOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFe(i1,:,:) = 0._dp
DerSigmaRirFe(i1,:,:) = 0._dp
DerSigmaSLirFe(i1,:,:) = 0._dp
DerSigmaSRirFe(i1,:,:) = 0._dp
End if
End do


!--------------------------
!Fv
!--------------------------
Do i1=1,3
p2 =0._dp
Call Sigma1LoopFv(p2,MHp,MHp2,MFe,MFe2,MVWp,MVWp2,MVZ,MVZ2,cplcFvFeHpL,               & 
& cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,SigmaLFv(i1,:,:)         & 
& ,SigmaRFv(i1,:,:),SigmaSLFv(i1,:,:),SigmaSRFv(i1,:,:))

Call DerSigma1LoopFv(p2,MHp,MHp2,MFe,MFe2,MVWp,MVWp2,MVZ,MVZ2,cplcFvFeHpL,            & 
& cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,DerSigmaLFv(i1,:,:)      & 
& ,DerSigmaRFv(i1,:,:),DerSigmaSLFv(i1,:,:),DerSigmaSRFv(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerSigma1LoopFv(p2,MHp,MHp2,MFe,MFe2,MVWp,MVWp2,MVZ,MVZ2,cplcFvFeHpL,            & 
& cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,DerSigmaLFvDR(i1,:,:)    & 
& ,DerSigmaRFvDR(i1,:,:),DerSigmaSLFvDR(i1,:,:),DerSigmaSRFvDR(i1,:,:))

p2 =0._dp
Call DerSigma1LoopFv(p2,MHpOS,MHp2OS,MFeOS,MFe2OS,MVWpOS,MVWp2OS,MVZOS,               & 
& MVZ2OS,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,      & 
& DerSigmaLFvOS(i1,:,:),DerSigmaRFvOS(i1,:,:),DerSigmaSLFvOS(i1,:,:),DerSigmaSRFvOS(i1,:,:))

DerSigmaLFv(i1,:,:) = DerSigmaLFv(i1,:,:) - DerSigmaLFvDR(i1,:,:)! + DerSigmaLFvOS(i1,:,:)
DerSigmaRFv(i1,:,:) = DerSigmaRFv(i1,:,:) - DerSigmaRFvDR(i1,:,:)! + DerSigmaRFvOS(i1,:,:)
DerSigmaSLFv(i1,:,:) = DerSigmaSLFv(i1,:,:) - DerSigmaSLFvDR(i1,:,:)! + DerSigmaSLFvOS(i1,:,:)
DerSigmaSRFv(i1,:,:) = DerSigmaSRFv(i1,:,:) - DerSigmaSRFvDR(i1,:,:)! + DerSigmaSRFvOS(i1,:,:)
DerSigmaLirFv(i1,:,:) = + DerSigmaLFvOS(i1,:,:)
DerSigmaRirFv(i1,:,:) = + DerSigmaRFvOS(i1,:,:)
DerSigmaSLirFv(i1,:,:) = + DerSigmaSLFvOS(i1,:,:)
DerSigmaSRirFv(i1,:,:) = + DerSigmaSRFvOS(i1,:,:)
IRdivonly=.False. 
Else
DerSigmaLirFv(i1,:,:) = 0._dp
DerSigmaRirFv(i1,:,:) = 0._dp
DerSigmaSLirFv(i1,:,:) = 0._dp
DerSigmaSRirFv(i1,:,:) = 0._dp
End if
End do


!--------------------------
!G0
!--------------------------
p2 = MG02
Call Pi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,   & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,       & 
& cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,PiG0)

Call DerPi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,   & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,       & 
& cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,DerPiG0)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopG0(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MG0,MG02,MVZ,MVZ2,MVWp,MVWp2,MHp,MHp2,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,   & 
& cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,       & 
& cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,kont,DerPiG0DR)

p2 = MG02OS
Call DerPi1LoopG0(p2,MA0OS,MA02OS,MH0OS,MH02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,             & 
& MFuOS,MFu2OS,MhhOS,Mhh2OS,MG0OS,MG02OS,MVZOS,MVZ2OS,MVWpOS,MVWp2OS,MHpOS,              & 
& MHp2OS,cplA0A0G0,cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,            & 
& cplcFuFuG0L,cplcFuFuG0R,cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,       & 
& GcplG0HpcVWp,cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,             & 
& cplG0G0cVWpVWp,cplG0G0VZVZ,kont,DerPiG0OS)

DerPiG0 = DerPiG0-DerPiG0DR + DerPiG0OS
IRdivonly=.False. 
End if 
!--------------------------
!hh
!--------------------------
p2 = Mhh2
Call Pi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,              & 
& MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,       & 
& cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp, & 
& cplhhhhVZVZ,kont,Pihh)

Call DerPi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,       & 
& cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp, & 
& cplhhhhVZVZ,kont,DerPihh)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1Loophh(p2,MA0,MA02,MH0,MH02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MVZ,MVZ2,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,       & 
& cplhhVZVZ,cplA0A0hhhh,cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp, & 
& cplhhhhVZVZ,kont,DerPihhDR)

p2 = Mhh2OS
Call DerPi1Loophh(p2,MA0OS,MA02OS,MH0OS,MH02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,             & 
& MFuOS,MFu2OS,MG0OS,MG02OS,MVZOS,MVZ2OS,MhhOS,Mhh2OS,MHpOS,MHp2OS,MVWpOS,               & 
& MVWp2OS,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,      & 
& cplH0H0hh,cplhhhhhh,GcplhhHpcHp,GcplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,       & 
& cplG0G0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,           & 
& kont,DerPihhOS)

DerPihh = DerPihh-DerPihhDR + DerPihhOS
IRdivonly=.False. 
End if 
!--------------------------
!A0
!--------------------------
p2 = MA02
Call Pi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp,MHp2,              & 
& MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,               & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,PiA0)

Call DerPi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp,MHp2,           & 
& MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,               & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,DerPiA0)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopA0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MH0,MH02,MVZ,MVZ2,MHp,MHp2,           & 
& MVWp,MVWp2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,               & 
& cplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0A0cVWpVWp,cplA0A0VZVZ,kont,DerPiA0DR)

p2 = MA02OS
Call DerPi1LoopA0(p2,MG0OS,MG02OS,MA0OS,MA02OS,MhhOS,Mhh2OS,MH0OS,MH02OS,             & 
& MVZOS,MVZ2OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,GcplA0HpcHp,GcplA0HpcVWp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,    & 
& cplA0A0HpcHp,cplA0A0cVWpVWp,cplA0A0VZVZ,kont,DerPiA0OS)

DerPiA0 = DerPiA0-DerPiA0DR + DerPiA0OS
IRdivonly=.False. 
End if 
!--------------------------
!H0
!--------------------------
p2 = MH02
Call Pi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp,MHp2,              & 
& MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,               & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,PiH0)

Call DerPi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp,MHp2,           & 
& MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,               & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,DerPiH0)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopH0(p2,MG0,MG02,MA0,MA02,Mhh,Mhh2,MVZ,MVZ2,MH0,MH02,MHp,MHp2,           & 
& MVWp,MVWp2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,cplH0H0hh,cplH0HpcHp,               & 
& cplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,kont,DerPiH0DR)

p2 = MH02OS
Call DerPi1LoopH0(p2,MG0OS,MG02OS,MA0OS,MA02OS,MhhOS,Mhh2OS,MVZOS,MVZ2OS,             & 
& MH0OS,MH02OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0H0H0,      & 
& cplH0H0hh,GcplH0HpcHp,GcplH0HpcVWp,cplA0A0H0H0,cplG0G0H0H0,cplH0H0H0H0,cplH0H0hhhh,    & 
& cplH0H0HpcHp,cplH0H0cVWpVWp,cplH0H0VZVZ,kont,DerPiH0OS)

DerPiH0 = DerPiH0-DerPiH0DR + DerPiH0OS
IRdivonly=.False. 
End if 
!--------------------------
!VG
!--------------------------
p2 = MVG2
Call Pi1LoopVG(p2,MFd,MFd2,MFu,MFu2,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,              & 
& cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,               & 
& kont,PiVG)

Call DerPi1LoopVG(p2,MFd,MFd2,MFu,MFu2,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,               & 
& kont,DerPiVG)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVG(p2,MFd,MFd2,MFu,MFu2,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,               & 
& kont,DerPiVGDR)

p2 = 0.
Call DerPi1LoopVG(p2,MFdOS,MFd2OS,MFuOS,MFu2OS,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,   & 
& kont,DerPiVGOS)

DerPiVG = DerPiVG-DerPiVGDR + DerPiVGOS
IRdivonly=.False. 
End if 
!--------------------------
!VP
!--------------------------
p2 = MVP2
Call Pi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,PiVP)

Call DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVP)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVPDR)

p2 = 0.
Call DerPi1LoopVP(p2,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MHpOS,MHp2OS,             & 
& MVWpOS,MVWp2OS,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,            & 
& cplcFuFuVPR,cplcgWpgWpVP,cplcgWCgWCVP,GcplHpcHpVP,GcplHpcVWpVP,cplcVWpVPVWp,           & 
& cplHpcHpVPVP,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVPOS)

DerPiVP = DerPiVP-DerPiVPDR + DerPiVPOS
IRdivonly=.False. 
End if 
!--------------------------
!VZ
!--------------------------
p2 = MVZ2
Call Pi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiVZ)

Call DerPi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,DerPiVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZ(p2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,DerPiVZDR)

p2 = MVZ2OS
Call DerPi1LoopVZ(p2,MH0OS,MH02OS,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,             & 
& MFuOS,MFu2OS,MhhOS,Mhh2OS,MG0OS,MG02OS,MVZOS,MVZ2OS,MHpOS,MHp2OS,MVWpOS,               & 
& MVWp2OS,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,         & 
& cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,               & 
& cplhhVZVZ,GcplHpcHpVZ,GcplHpcVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ,cplG0G0VZVZ,               & 
& cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,  & 
& kont,DerPiVZOS)

DerPiVZ = DerPiVZ-DerPiVZDR + DerPiVZOS
IRdivonly=.False. 
End if 
!--------------------------
!VWp
!--------------------------
p2 = MVWp2
Call Pi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,MG02,             & 
& MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,PiVWp)

Call DerPi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,               & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,DerPiVWp)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVWp(p2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,               & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,DerPiVWpDR)

p2 = MVWp2OS
Call DerPi1LoopVWp(p2,MHpOS,MHp2OS,MA0OS,MA02OS,MFdOS,MFd2OS,MFuOS,MFu2OS,            & 
& MFeOS,MFe2OS,MG0OS,MG02OS,MH0OS,MH02OS,MhhOS,Mhh2OS,MVWpOS,MVWp2OS,MVZOS,              & 
& MVZ2OS,GcplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,           & 
& GcplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,GcplH0HpcVWp,     & 
& GcplhhHpcVWp,cplhhcVWpVWp,GcplHpcVWpVP,GcplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,         & 
& cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp,cplHpcHpcVWpVWp,           & 
& cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3, & 
& cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,               & 
& DerPiVWpOS)

DerPiVWp = DerPiVWp-DerPiVWpDR + DerPiVWpOS
IRdivonly=.False. 
End if 
!--------------------------
! Additional Self-Energies for Photon
!--------------------------
p2 = 0._dp
OnlyLightStates = .True. 
Call Pi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,PiVPlight0)

Call DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVPlight0)

OnlyLightStates = .False. 
p2 = 0._dp
OnlyHeavyStates = .True. 
Call Pi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,PiVPheavy0)

Call DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVPheavy0)

OnlyHeavyStates = .False. 
p2 = MVZ2
OnlyLightStates = .True. 
Call Pi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,PiVPlightMZ)

Call DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVPlightMZ)

OnlyLightStates = .False. 
p2 = MVZ2
OnlyHeavyStates = .True. 
Call Pi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,PiVPheavyMZ)

Call DerPi1LoopVP(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,DerPiVPheavyMZ)

OnlyHeavyStates = .False. 
!--------------------------
!VP
!--------------------------
p2 = MVZ2
Call Pi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,       & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,PiVPVZ)

Call DerPi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,    & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,DerPiVPVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,    & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,DerPiVPVZDR)

p2 =MVZ2OS
Call DerPi1LoopVPVZ(p2,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MHpOS,MHp2OS,           & 
& MVWpOS,MVWp2OS,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,            & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,GcplcHpVPVWp,          & 
& GcplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,             & 
& cplcVWpVWpVZ,GcplHpcHpVP,cplHpcHpVPVZ,GcplHpcHpVZ,GcplHpcVWpVP,GcplHpcVWpVZ,           & 
& kont,DerPiVPVZOS)

DerPiVPVZ = DerPiVPVZ- DerPiVPVZDR + DerPiVPVZOS
IRdivonly=.False. 
End if
p2 = 0._dp 
Call Pi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,       & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,PiVZVP)

Call DerPi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,    & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,DerPiVZVP)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVPVZ(p2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,    & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,DerPiVPVZDR)

p2 = 0._dp 
Call DerPi1LoopVPVZ(p2,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,MHpOS,MHp2OS,           & 
& MVWpOS,MVWp2OS,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,            & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,GcplcHpVPVWp,          & 
& GcplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,             & 
& cplcVWpVWpVZ,GcplHpcHpVP,cplHpcHpVPVZ,GcplHpcHpVZ,GcplHpcVWpVP,GcplHpcVWpVZ,           & 
& kont,DerPiVPVZOS)

DerPiVPVZ = DerPiVPVZ- DerPiVPVZDR + DerPiVPVZOS
IRdivonly=.False. 
End if
!--------------------------
!VZ
!--------------------------
p2 = MG02
Call Pi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,            & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,cplcgWCgWCVZ,             & 
& cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,     & 
& cplhhVZVZ,cplHpcVWpVZ,kont,PiVZG0)

Call DerPi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,              & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,            & 
& cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,              & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,              & 
& cplG0hhVZ,cplG0HpcVWp,cplhhVZVZ,cplHpcVWpVZ,kont,DerPiVZG0)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,              & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,            & 
& cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,              & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,              & 
& cplG0hhVZ,cplG0HpcVWp,cplhhVZVZ,cplHpcVWpVZ,kont,DerPiVZG0DR)

p2 =MG02OS
Call DerPi1LoopVZG0(p2,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,           & 
& MG0OS,MG02OS,MH0OS,MH02OS,MhhOS,Mhh2OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,MVZOS,              & 
& MVZ2OS,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,            & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,           & 
& GcplcHpVWpVZ,GcplG0cHpVWp,cplG0G0hh,cplG0hhVZ,GcplG0HpcVWp,cplhhVZVZ,GcplHpcVWpVZ,     & 
& kont,DerPiVZG0OS)

DerPiVZG0 = DerPiVZG0- DerPiVZG0DR + DerPiVZG0OS
IRdivonly=.False. 
End if
p2 = MVZ2
Call Pi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,            & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,cplcFdFdG0R,     & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,cplcgWCgWCVZ,             & 
& cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,     & 
& cplhhVZVZ,cplHpcVWpVZ,kont,PiG0VZ)

Call DerPi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,              & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,            & 
& cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,              & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,              & 
& cplG0hhVZ,cplG0HpcVWp,cplhhVZVZ,cplHpcVWpVZ,kont,DerPiG0VZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZG0(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,              & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,            & 
& cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,              & 
& cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,cplcHpVWpVZ,cplG0cHpVWp,cplG0G0hh,              & 
& cplG0hhVZ,cplG0HpcVWp,cplhhVZVZ,cplHpcVWpVZ,kont,DerPiVZG0DR)

p2 =MVZ2OS
Call DerPi1LoopVZG0(p2,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,           & 
& MG0OS,MG02OS,MH0OS,MH02OS,MhhOS,Mhh2OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,MVZOS,              & 
& MVZ2OS,cplA0G0H0,cplA0H0VZ,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdVZL,cplcFdFdVZR,            & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCG0,cplcgWCgWCVZ,cplcgWpgWpG0,cplcgWpgWpVZ,           & 
& GcplcHpVWpVZ,GcplG0cHpVWp,cplG0G0hh,cplG0hhVZ,GcplG0HpcVWp,cplhhVZVZ,GcplHpcVWpVZ,     & 
& kont,DerPiVZG0OS)

DerPiVZG0 = DerPiVZG0- DerPiVZG0DR + DerPiVZG0OS
IRdivonly=.False. 
End if
!--------------------------
!VZ
!--------------------------
p2 = Mhh2
Call Pi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,MHp,MHp2,            & 
& MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,cplcgWpgWpVZ,           & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplHpcHpVZ,cplHpcVWpVZ,kont,PiVZhh)

Call DerPi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,MHp,              & 
& MHp2,MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,            & 
& cplcgWpgWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,             & 
& cplhhHpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZhh)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,MHp,              & 
& MHp2,MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,            & 
& cplcgWpgWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,             & 
& cplhhHpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZhhDR)

p2 =Mhh2OS
Call DerPi1LoopVZhh(p2,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,           & 
& MH0OS,MH02OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,              & 
& cplcgWCgWCVZ,cplcgWpgWphh,cplcgWpgWpVZ,GcplcHpVWpVZ,cplcVWpVWpVZ,GcplhhcHpVWp,         & 
& cplhhcVWpVWp,GcplhhHpcHp,GcplhhHpcVWp,GcplHpcHpVZ,GcplHpcVWpVZ,kont,DerPiVZhhOS)

DerPiVZhh = DerPiVZhh- DerPiVZhhDR + DerPiVZhhOS
IRdivonly=.False. 
End if
p2 = MVZ2
Call Pi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,MHp,MHp2,            & 
& MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,cplcgWpgWpVZ,           & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplHpcHpVZ,cplHpcVWpVZ,kont,PihhVZ)

Call DerPi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,MHp,              & 
& MHp2,MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,            & 
& cplcgWpgWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,             & 
& cplhhHpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPihhVZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZhh(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,MHp,              & 
& MHp2,MVWp,MVWp2,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,cplcgWCgWCVZ,cplcgWpgWphh,            & 
& cplcgWpgWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,             & 
& cplhhHpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZhhDR)

p2 =MVZ2OS
Call DerPi1LoopVZhh(p2,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,           & 
& MH0OS,MH02OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWChh,              & 
& cplcgWCgWCVZ,cplcgWpgWphh,cplcgWpgWpVZ,GcplcHpVWpVZ,cplcVWpVWpVZ,GcplhhcHpVWp,         & 
& cplhhcVWpVWp,GcplhhHpcHp,GcplhhHpcVWp,GcplHpcHpVZ,GcplHpcVWpVZ,kont,DerPiVZhhOS)

DerPiVZhh = DerPiVZhh- DerPiVZhhDR + DerPiVZhhOS
IRdivonly=.False. 
End if
!--------------------------
!VZ
!--------------------------
p2 = MA02
Call Pi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,           & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,PiVZA0)

Call DerPi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,        & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZA0)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,        & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZA0DR)

p2 =MA02OS
Call DerPi1LoopVZA0(p2,MHpOS,MHp2OS,MVWpOS,MVWp2OS,GcplA0cHpVWp,GcplA0HpcHp,          & 
& GcplA0HpcVWp,GcplcHpVWpVZ,GcplHpcHpVZ,GcplHpcVWpVZ,kont,DerPiVZA0OS)

DerPiVZA0 = DerPiVZA0- DerPiVZA0DR + DerPiVZA0OS
IRdivonly=.False. 
End if
p2 = MVZ2
Call Pi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,           & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,PiA0VZ)

Call DerPi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,        & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiA0VZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZA0(p2,MHp,MHp2,MVWp,MVWp2,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,        & 
& cplcHpVWpVZ,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZA0DR)

p2 =MVZ2OS
Call DerPi1LoopVZA0(p2,MHpOS,MHp2OS,MVWpOS,MVWp2OS,GcplA0cHpVWp,GcplA0HpcHp,          & 
& GcplA0HpcVWp,GcplcHpVWpVZ,GcplHpcHpVZ,GcplHpcVWpVZ,kont,DerPiVZA0OS)

DerPiVZA0 = DerPiVZA0- DerPiVZA0DR + DerPiVZA0OS
IRdivonly=.False. 
End if
!--------------------------
!VZ
!--------------------------
p2 = MH02
Call Pi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,           & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,PiVZH0)

Call DerPi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,        & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZH0)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,        & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZH0DR)

p2 =MH02OS
Call DerPi1LoopVZH0(p2,MHpOS,MHp2OS,MVWpOS,MVWp2OS,GcplcHpVWpVZ,GcplH0cHpVWp,         & 
& GcplH0HpcHp,GcplH0HpcVWp,GcplHpcHpVZ,GcplHpcVWpVZ,kont,DerPiVZH0OS)

DerPiVZH0 = DerPiVZH0- DerPiVZH0DR + DerPiVZH0OS
IRdivonly=.False. 
End if
p2 = MVZ2
Call Pi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,           & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,PiH0VZ)

Call DerPi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,        & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiH0VZ)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVZH0(p2,MHp,MHp2,MVWp,MVWp2,cplcHpVWpVZ,cplH0cHpVWp,cplH0HpcHp,        & 
& cplH0HpcVWp,cplHpcHpVZ,cplHpcVWpVZ,kont,DerPiVZH0DR)

p2 =MVZ2OS
Call DerPi1LoopVZH0(p2,MHpOS,MHp2OS,MVWpOS,MVWp2OS,GcplcHpVWpVZ,GcplH0cHpVWp,         & 
& GcplH0HpcHp,GcplH0HpcVWp,GcplHpcHpVZ,GcplHpcVWpVZ,kont,DerPiVZH0OS)

DerPiVZH0 = DerPiVZH0- DerPiVZH0DR + DerPiVZH0OS
IRdivonly=.False. 
End if
!--------------------------
!VWp
!--------------------------
Do i1=1,2
p2 = MHp2(i1)
Call Pi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,Mhh,Mhh2,           & 
& MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,cplcFdFucHpR,         & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,         & 
& cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,         & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplH0HpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,PiVWpHp(i1,:,:))

Call DerPi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,Mhh,             & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,cplcFdFucHpR,    & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,         & 
& cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,         & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplH0HpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,DerPiVWpHp(i1,:,:))

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,Mhh,             & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,cplcFdFucHpR,    & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,         & 
& cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,         & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplH0HpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,DerPiVWpHpDR(i1,:,:))

p2 =MHp2OS(i1)
Call DerPi1LoopVWpHp(p2,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,          & 
& MH0OS,MH02OS,MhhOS,Mhh2OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,MVZOS,MVZ2OS,GcplA0cHpVWp,       & 
& GcplA0HpcHp,GcplcFdFucHpL,GcplcFdFucHpR,GcplcFeFvcHpL,GcplcFeFvcHpR,cplcFuFdVWpL,      & 
& cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,         & 
& cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,GcplcHpVPVWp,GcplcHpVWpVZ,cplcVWpVPVWp,         & 
& cplcVWpVWpVZ,GcplH0cHpVWp,GcplH0HpcHp,GcplhhcHpVWp,cplhhcVWpVWp,GcplhhHpcHp,           & 
& GcplHpcHpVP,GcplHpcHpVZ,kont,DerPiVWpHpOS(i1,:,:))

DerPiVWpHp(i1,:,:) = DerPiVWpHp(i1,:,:)- DerPiVWpHpDR(i1,:,:) + DerPiVWpHpOS(i1,:,:)
IRdivonly=.False. 
End if
End do
p2 = MVWp2
Call Pi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,Mhh,Mhh2,           & 
& MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,cplcFdFucHpR,         & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,         & 
& cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,         & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplH0HpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,PiHpVWp)

Call DerPi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,Mhh,             & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,cplcFdFucHpR,    & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,         & 
& cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,         & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplH0HpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,DerPiHpVWp)

If ((ShiftIRdiv).and.(OSkinematics)) Then 
IRdivonly=.True. 
Call DerPi1LoopVWpHp(p2,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MH0,MH02,Mhh,             & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0cHpVWp,cplA0HpcHp,cplcFdFucHpL,cplcFdFucHpR,    & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,         & 
& cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,         & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplH0HpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhHpcHp,cplHpcHpVP,cplHpcHpVZ,kont,DerPiVWpHpDR)

p2 =MVWp2OS
Call DerPi1LoopVWpHp(p2,MA0OS,MA02OS,MFdOS,MFd2OS,MFeOS,MFe2OS,MFuOS,MFu2OS,          & 
& MH0OS,MH02OS,MhhOS,Mhh2OS,MHpOS,MHp2OS,MVWpOS,MVWp2OS,MVZOS,MVZ2OS,GcplA0cHpVWp,       & 
& GcplA0HpcHp,GcplcFdFucHpL,GcplcFdFucHpR,GcplcFeFvcHpL,GcplcFeFvcHpR,cplcFuFdVWpL,      & 
& cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgZcHp,         & 
& cplcgWpgZVWp,cplcgZgWCVWp,cplcgZgWpcHp,GcplcHpVPVWp,GcplcHpVWpVZ,cplcVWpVPVWp,         & 
& cplcVWpVWpVZ,GcplH0cHpVWp,GcplH0HpcHp,GcplhhcHpVWp,cplhhcVWpVWp,GcplhhHpcHp,           & 
& GcplHpcHpVP,GcplHpcHpVZ,kont,DerPiVWpHpOS)

DerPiVWpHp = DerPiVWpHp- DerPiVWpHpDR + DerPiVWpHpOS
IRdivonly=.False. 
End if
! -----------------------------------------------------------
! Calculate now all wave-function renormalisation constants 
! -----------------------------------------------------------


!  ######    VG    ###### 
ZfVG = -DerPiVG


!  ######    vL    ###### 
Do i1=1,3
  Do i2=1,3
   If (i1.eq.i2) Then 
     ZfvL(i1,i2) = -SigmaRFv(i2,i1,i2) 
   Else 
     ZfvL(i1,i2) = 0._dp 
   End if 
  End Do 
End Do 


!  ######    G0    ###### 
ZfG0 = -DerPiG0


!  ######    hh    ###### 
Zfhh = -DerPihh


!  ######    A0    ###### 
ZfA0 = -DerPiA0


!  ######    H0    ###### 
ZfH0 = -DerPiH0


!  ######    VP    ###### 
ZfVP = -DerPiVP


!  ######    VZ    ###### 
ZfVZ = -DerPiVZ


!  ######    VWp    ###### 
ZfVWp = -DerPiVWp


!  ######    Hp    ###### 
Do i1=1,2
  Do i2=1,2
   If ((i1.eq.i2).or.(MHp(i1).eq.MHp(i2))) Then 
       ZfHp(i1,i2) = -DerPiHp(i1,i1,i2)
   Else 
       ZfHp(i1,i2) = 2._dp/(MHp2(i1)-MHp2(i2))*PiHp(i2,i1,i2)
   End if 
  End Do 
End Do 


!  ######    DL    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFd(i1).eq.MFd(i2))) Then 
     ZfDL(i1,i2) = -SigmaRFd(i2,i1,i2) &
      & -MFd2(i1)*(DerSigmaRFd(i2,i1,i2) + DerSigmaLFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSRFd(i2,i1,i2)+DerSigmaSLFd(i2,i1,i2))
     If (OSkinematics) Then 
     ZfDL(i1,i2) = ZfDL(i1,i2) &
      & -MFd2OS(i1)*(DerSigmaRirFd(i2,i1,i2) + DerSigmaLirFd(i2,i1,i2))&
      & -MFdOS(i1)*(DerSigmaSRirFd(i2,i1,i2)+DerSigmaSLirFd(i2,i1,i2))
     Else 
     ZfDL(i1,i2) = ZfDL(i1,i2) &
      & -MFd2(i1)*(DerSigmaRirFd(i2,i1,i2) + DerSigmaLirFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSRirFd(i2,i1,i2)+DerSigmaSLirFd(i2,i1,i2))
     End if 
   Else 
     ZfDL(i1,i2) = 2._dp/(MFd2(i1) - MFd2(i2))* &
      & (MFd2(i2)*SigmaRFd(i2,i1,i2) + MFd(i1)*MFd(i2)*SigmaLFd(i2,i1,i2) + MFd(i1)*SigmaSRFd(i2,i1,i2) + MFd(i2)*SigmaSLFd(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    DR    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFd(i1).eq.MFd(i2))) Then 
     ZfDR(i1,i2) = -SigmaLFd(i2,i1,i2) &
      & -MFd2(i1)*(DerSigmaLFd(i2,i1,i2) + DerSigmaRFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSLFd(i2,i1,i2)+DerSigmaSRFd(i2,i1,i2))
     If (OSkinematics) Then 
     ZfDR(i1,i2) = ZfDR(i1,i2) &
      & -MFd2OS(i1)*(DerSigmaLirFd(i2,i1,i2) + DerSigmaRirFd(i2,i1,i2))&
      & -MFdOS(i1)*(DerSigmaSLirFd(i2,i1,i2)+DerSigmaSRirFd(i2,i1,i2))
     Else 
     ZfDR(i1,i2) = ZfDR(i1,i2) &
      & -MFd2(i1)*(DerSigmaLirFd(i2,i1,i2) + DerSigmaRirFd(i2,i1,i2))&
      & -MFd(i1)*(DerSigmaSLirFd(i2,i1,i2)+DerSigmaSRirFd(i2,i1,i2))
     End if 
   Else 
     ZfDR(i1,i2) = 2._dp/(MFd2(i1) - MFd2(i2))* &
      & (MFd2(i2)*SigmaLFd(i2,i1,i2) + MFd(i1)*MFd(i2)*SigmaRFd(i2,i1,i2) + MFd(i1)*SigmaSLFd(i2,i1,i2) + MFd(i2)*SigmaSRFd(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    UL    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFu(i1).eq.MFu(i2))) Then 
     ZfUL(i1,i2) = -SigmaRFu(i2,i1,i2) &
      & -MFu2(i1)*(DerSigmaRFu(i2,i1,i2) + DerSigmaLFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSRFu(i2,i1,i2)+DerSigmaSLFu(i2,i1,i2))
     If (OSkinematics) Then 
     ZfUL(i1,i2) = ZfUL(i1,i2) &
      & -MFu2OS(i1)*(DerSigmaRirFu(i2,i1,i2) + DerSigmaLirFu(i2,i1,i2))&
      & -MFuOS(i1)*(DerSigmaSRirFu(i2,i1,i2)+DerSigmaSLirFu(i2,i1,i2))
     Else 
     ZfUL(i1,i2) = ZfUL(i1,i2) &
      & -MFu2(i1)*(DerSigmaRirFu(i2,i1,i2) + DerSigmaLirFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSRirFu(i2,i1,i2)+DerSigmaSLirFu(i2,i1,i2))
     End if 
   Else 
     ZfUL(i1,i2) = 2._dp/(MFu2(i1) - MFu2(i2))* &
      & (MFu2(i2)*SigmaRFu(i2,i1,i2) + MFu(i1)*MFu(i2)*SigmaLFu(i2,i1,i2) + MFu(i1)*SigmaSRFu(i2,i1,i2) + MFu(i2)*SigmaSLFu(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    UR    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFu(i1).eq.MFu(i2))) Then 
     ZfUR(i1,i2) = -SigmaLFu(i2,i1,i2) &
      & -MFu2(i1)*(DerSigmaLFu(i2,i1,i2) + DerSigmaRFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSLFu(i2,i1,i2)+DerSigmaSRFu(i2,i1,i2))
     If (OSkinematics) Then 
     ZfUR(i1,i2) = ZfUR(i1,i2) &
      & -MFu2OS(i1)*(DerSigmaLirFu(i2,i1,i2) + DerSigmaRirFu(i2,i1,i2))&
      & -MFuOS(i1)*(DerSigmaSLirFu(i2,i1,i2)+DerSigmaSRirFu(i2,i1,i2))
     Else 
     ZfUR(i1,i2) = ZfUR(i1,i2) &
      & -MFu2(i1)*(DerSigmaLirFu(i2,i1,i2) + DerSigmaRirFu(i2,i1,i2))&
      & -MFu(i1)*(DerSigmaSLirFu(i2,i1,i2)+DerSigmaSRirFu(i2,i1,i2))
     End if 
   Else 
     ZfUR(i1,i2) = 2._dp/(MFu2(i1) - MFu2(i2))* &
      & (MFu2(i2)*SigmaLFu(i2,i1,i2) + MFu(i1)*MFu(i2)*SigmaRFu(i2,i1,i2) + MFu(i1)*SigmaSLFu(i2,i1,i2) + MFu(i2)*SigmaSRFu(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    EL    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFe(i1).eq.MFe(i2))) Then 
     ZfEL(i1,i2) = -SigmaRFe(i2,i1,i2) &
      & -MFe2(i1)*(DerSigmaRFe(i2,i1,i2) + DerSigmaLFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSRFe(i2,i1,i2)+DerSigmaSLFe(i2,i1,i2))
     If (OSkinematics) Then 
     ZfEL(i1,i2) = ZfEL(i1,i2) &
      & -MFe2OS(i1)*(DerSigmaRirFe(i2,i1,i2) + DerSigmaLirFe(i2,i1,i2))&
      & -MFeOS(i1)*(DerSigmaSRirFe(i2,i1,i2)+DerSigmaSLirFe(i2,i1,i2))
     Else 
     ZfEL(i1,i2) = ZfEL(i1,i2) &
      & -MFe2(i1)*(DerSigmaRirFe(i2,i1,i2) + DerSigmaLirFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSRirFe(i2,i1,i2)+DerSigmaSLirFe(i2,i1,i2))
     End if 
   Else 
     ZfEL(i1,i2) = 2._dp/(MFe2(i1) - MFe2(i2))* &
      & (MFe2(i2)*SigmaRFe(i2,i1,i2) + MFe(i1)*MFe(i2)*SigmaLFe(i2,i1,i2) + MFe(i1)*SigmaSRFe(i2,i1,i2) + MFe(i2)*SigmaSLFe(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    ER    ###### 
Do i1=1,3
  Do i2=1,3
   If ((i1.eq.i2).or.(MFe(i1).eq.MFe(i2))) Then 
     ZfER(i1,i2) = -SigmaLFe(i2,i1,i2) &
      & -MFe2(i1)*(DerSigmaLFe(i2,i1,i2) + DerSigmaRFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSLFe(i2,i1,i2)+DerSigmaSRFe(i2,i1,i2))
     If (OSkinematics) Then 
     ZfER(i1,i2) = ZfER(i1,i2) &
      & -MFe2OS(i1)*(DerSigmaLirFe(i2,i1,i2) + DerSigmaRirFe(i2,i1,i2))&
      & -MFeOS(i1)*(DerSigmaSLirFe(i2,i1,i2)+DerSigmaSRirFe(i2,i1,i2))
     Else 
     ZfER(i1,i2) = ZfER(i1,i2) &
      & -MFe2(i1)*(DerSigmaLirFe(i2,i1,i2) + DerSigmaRirFe(i2,i1,i2))&
      & -MFe(i1)*(DerSigmaSLirFe(i2,i1,i2)+DerSigmaSRirFe(i2,i1,i2))
     End if 
   Else 
     ZfER(i1,i2) = 2._dp/(MFe2(i1) - MFe2(i2))* &
      & (MFe2(i2)*SigmaLFe(i2,i1,i2) + MFe(i1)*MFe(i2)*SigmaRFe(i2,i1,i2) + MFe(i1)*SigmaSLFe(i2,i1,i2) + MFe(i2)*SigmaSRFe(i2,i1,i2))
   End if 
  End Do 
End Do 


!  ######    VPVZ    ###### 
ZfVPVZ = 2._dp*PiVPVZ/(MVP2-MVZ2 )
ZfVZVP = 2._dp*PiVZVP/(MVZ2-MVP2 )
! -----------------------------------------------------------
! Setting the Counter-Terms 
! -----------------------------------------------------------
! ----------- getting the divergent pieces ---------

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG70(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,g1D)

TwoLoopRGEsave=TwoLoopRGE 
TwoLoopRGE=.False. 
Call rge70(70,0._dp,g1D,g1D) 
TwoLoopRGE=TwoLoopRGEsave 
Call GToParameters70(g1D,dg1,dg2,dg3,dlam5,dlam1,dlam4,dlam3,dlam2,dYe,               & 
& dYd,dYu,dMHD2,dMHU2,dv)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
dg1 = Sqrt(3._dp/5._dp)*dg1 
! ----------------------- 
 

 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
dg1 = 0.5_dp*divergence*dg1 
dg2 = 0.5_dp*divergence*dg2 
dg3 = 0.5_dp*divergence*dg3 
dYe = 0.5_dp*divergence*dYe 
dYd = 0.5_dp*divergence*dYd 
dYu = 0.5_dp*divergence*dYu 
dlam5 = 0.5_dp*divergence*dlam5 
dMHD2 = 0.5_dp*divergence*dMHD2 
dMHU2 = 0.5_dp*divergence*dMHU2 
dlam1 = 0.5_dp*divergence*dlam1 
dlam4 = 0.5_dp*divergence*dlam4 
dlam3 = 0.5_dp*divergence*dlam3 
dlam2 = 0.5_dp*divergence*dlam2 
dv = 0.5_dp*divergence*dv 
dZP = 0._dp 
dZDL = 0._dp 
dZDR = 0._dp 
dZUL = 0._dp 
dZUR = 0._dp 
dZEL = 0._dp 
dZER = 0._dp 
dSinTW = 0._dp 
dCosTW = 0._dp 
dTanTW = 0._dp 
If (CTinLoopDecays) Then 
dCosTW = ((PiVWp/MVWp**2 - PiVZ/mVZ**2)*Cos(TW))/2._dp 
dSinTW = -(dCosTW*1/Tan(TW)) 
dg2 = (g2*(derPiVPheavy0 + PiVPlightMZ/MVZ**2 - (-(PiVWp/MVWp**2) + PiVZ/MVZ**2)*1/Tan(TW)**2 + (2*PiVZVP*Tan(TW))/MVZ**2))/2._dp 
dg1 = dSinTW*g2*1/Cos(TW) + dg2*Tan(TW) - dCosTW*g2*1/Cos(TW)*Tan(TW) 
End if 
 
dZDL = 0.25_dp*MatMul(ZfDL- Conjg(Transpose(ZfDL)),ZDL)
dZDR = 0.25_dp*MatMul(ZfDR- Conjg(Transpose(ZfDR)),ZDR)
dZEL = 0.25_dp*MatMul(ZfEL- Conjg(Transpose(ZfEL)),ZEL)
dZER = 0.25_dp*MatMul(ZfER- Conjg(Transpose(ZfER)),ZER)
dZP = 0.25_dp*MatMul(ZfHp- Conjg(Transpose(ZfHp)),ZP)
dZUL = 0.25_dp*MatMul(ZfUL- Conjg(Transpose(ZfUL)),ZUL)
dZUR = 0.25_dp*MatMul(ZfUR- Conjg(Transpose(ZfUR)),ZUR)


! -----------------------------------------------------------
! Calculating the CT vertices 
! -----------------------------------------------------------
Call CalculateCouplingCT(lam5,v,lam3,lam4,ZP,lam1,g1,g2,TW,g3,Yd,ZDL,ZDR,             & 
& Yu,ZUL,ZUR,Ye,ZEL,ZER,dlam5,dv,dlam3,dlam4,dZP,dlam1,dg1,dg2,dSinTW,dCosTW,            & 
& dTanTW,dg3,dYd,dZDL,dZDR,dYu,dZUL,dZUR,dYe,dZEL,dZER,ctcplA0A0G0,ctcplA0A0hh,          & 
& ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp,ctcplG0G0hh,ctcplG0H0H0,ctcplH0H0hh,              & 
& ctcplH0HpcHp,ctcplhhhhhh,ctcplhhHpcHp,ctcplA0H0VZ,ctcplA0HpcVWp,ctcplA0cHpVWp,         & 
& ctcplG0hhVZ,ctcplG0HpcVWp,ctcplG0cHpVWp,ctcplH0HpcVWp,ctcplH0cHpVWp,ctcplhhHpcVWp,     & 
& ctcplhhcHpVWp,ctcplHpcHpVP,ctcplHpcHpVZ,ctcplhhcVWpVWp,ctcplhhVZVZ,ctcplHpcVWpVP,      & 
& ctcplHpcVWpVZ,ctcplcHpVPVWp,ctcplcHpVWpVZ,ctcplVGVGVG,ctcplcVWpVPVWp,ctcplcVWpVWpVZ,   & 
& ctcplcFdFdG0L,ctcplcFdFdG0R,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFuFdHpL,ctcplcFuFdHpR,   & 
& ctcplcFeFeG0L,ctcplcFeFeG0R,ctcplcFeFehhL,ctcplcFeFehhR,ctcplcFvFeHpL,ctcplcFvFeHpR,   & 
& ctcplcFuFuG0L,ctcplcFuFuG0R,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFucHpL,ctcplcFdFucHpR, & 
& ctcplcFeFvcHpL,ctcplcFeFvcHpR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,               & 
& ctcplcFdFdVPR,ctcplcFuFdVWpL,ctcplcFuFdVWpR,ctcplcFdFdVZL,ctcplcFdFdVZR,               & 
& ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFvFeVWpL,ctcplcFvFeVWpR,ctcplcFeFeVZL,               & 
& ctcplcFeFeVZR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,   & 
& ctcplcFuFuVZR,ctcplcFdFucVWpL,ctcplcFdFucVWpR,ctcplcFvFvVZL,ctcplcFvFvVZR,             & 
& ctcplcFeFvcVWpL,ctcplcFeFvcVWpR)

End Subroutine WaveFunctionRenormalisation 
Subroutine CalculateOneLoopDecays(gP1LFu,gP1LFe,gP1LFd,gP1Lhh,gP1LH0,gP1LA0,          & 
& gP1LHp,MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,MG0OS,MG02OS,               & 
& MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,MVWp2OS,ZPOS,               & 
& ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,               & 
& Ye,Yd,Yu,MHD2,MHU2,epsI,deltaM,kont)

Implicit None 
Real(dp), Intent(in) :: epsI, deltaM 
Integer, Intent(inout) :: kont 
Real(dp) :: MLambda, em, gs, vSM, sinW2, g1SM, g2SM 
Integer :: divset, i1 
Complex(dp) :: divvalue, YuSM(3,3), YdSM(3,3), YeSM(3,3) 
Real(dp),Intent(inout) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(inout) :: v

Real(dp) :: dg1,dg2,dg3,dMHD2,dMHU2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp) :: dYe(3,3),dYd(3,3),dYu(3,3),dlam5,dlam1,dlam4,dlam3,dlam2,dZDL(3,3),dZDR(3,3),         & 
& dZUL(3,3),dZUR(3,3),dZEL(3,3),dZER(3,3)

Complex(dp) :: ZfVG,ZfvL(3,3),ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp(2,2),ZfDL(3,3),               & 
& ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfEL(3,3),ZfER(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MHpOS(2),MHp2OS(2),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),          & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS(2,2)

Complex(dp),Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Real(dp) :: p2, q2, q2_save 
Real(dp) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1(2,2),  & 
& cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),cplA0H0hhhh1,cplA0hhHpcHp1(2,2),          & 
& cplG0G0G0G01,cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1(2,2),cplG0H0H0hh1,cplG0H0HpcHp1(2,2),& 
& cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),cplH0hhHpcHp1(2,2),cplhhhhhhhh1,          & 
& cplhhhhHpcHp1(2,2),cplHpHpcHpcHp1(2,2,2,2),cplA0A0cVWpVWp1,cplA0A0VZVZ1,               & 
& cplA0HpcVWpVP1(2),cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),               & 
& cplG0G0cVWpVWp1,cplG0G0VZVZ1,cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplG0cHpVPVWp1(2),    & 
& cplG0cHpVWpVZ1(2),cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2),    & 
& cplH0cHpVPVWp1(2),cplH0cHpVWpVZ1(2),cplhhhhcVWpVWp1,cplhhhhVZVZ1,cplhhHpcVWpVP1(2),    & 
& cplhhHpcVWpVZ1(2),cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVP1(2,2),              & 
& cplHpcHpVPVZ1(2,2),cplHpcHpcVWpVWp1(2,2),cplHpcHpVZVZ1(2,2),cplVGVGVGVG1Q,             & 
& cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q,        & 
& cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ3Q,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,& 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q

Complex(dp) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplA0A0A0A0,cplA0A0G0G0,           & 
& cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0G0G0H0,cplA0G0H0hh,         & 
& cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),cplG0G0G0G0,cplG0G0H0H0,               & 
& cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),cplH0H0H0H0,               & 
& cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,cplhhhhHpcHp(2,2),         & 
& cplHpHpcHpcHp(2,2,2,2),cplA0H0VZ,cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcVWp(2),            & 
& cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP(2),  & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0cVWpVWp,cplA0A0VZVZ,               & 
& cplA0HpcVWpVP(2),cplA0HpcVWpVZ(2),cplA0cHpVPVWp(2),cplA0cHpVWpVZ(2),cplG0G0cVWpVWp,    & 
& cplG0G0VZVZ,cplG0HpcVWpVP(2),cplG0HpcVWpVZ(2),cplG0cHpVPVWp(2),cplG0cHpVWpVZ(2),       & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP(2),cplH0HpcVWpVZ(2),cplH0cHpVPVWp(2),         & 
& cplH0cHpVWpVZ(2),cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP(2),cplhhHpcVWpVZ(2),         & 
& cplhhcHpVPVWp(2),cplhhcHpVWpVZ(2),cplHpcHpVPVP(2,2),cplHpcHpVPVZ(2,2),cplHpcHpcVWpVWp(2,2),& 
& cplHpcHpVZVZ(2,2),cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),& 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),               & 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3), & 
& cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3), & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVGL(3,3),& 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,          & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,       & 
& cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,               & 
& cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,      & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,        & 
& cplcgWCgWCG0,cplcgZgAhh,cplcgWpgAHp(2),cplcgWCgAcHp(2),cplcgWpgWphh,cplcgZgWpcHp(2),   & 
& cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcHp(2)

Complex(dp) :: ctcplA0A0G0,ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp(2,2),ctcplG0G0hh,        & 
& ctcplG0H0H0,ctcplH0H0hh,ctcplH0HpcHp(2,2),ctcplhhhhhh,ctcplhhHpcHp(2,2),               & 
& ctcplA0H0VZ,ctcplA0HpcVWp(2),ctcplA0cHpVWp(2),ctcplG0hhVZ,ctcplG0HpcVWp(2),            & 
& ctcplG0cHpVWp(2),ctcplH0HpcVWp(2),ctcplH0cHpVWp(2),ctcplhhHpcVWp(2),ctcplhhcHpVWp(2),  & 
& ctcplHpcHpVP(2,2),ctcplHpcHpVZ(2,2),ctcplhhcVWpVWp,ctcplhhVZVZ,ctcplHpcVWpVP(2),       & 
& ctcplHpcVWpVZ(2),ctcplcHpVPVWp(2),ctcplcHpVWpVZ(2),ctcplVGVGVG,ctcplcVWpVPVWp,         & 
& ctcplcVWpVWpVZ,ctcplcFdFdG0L(3,3),ctcplcFdFdG0R(3,3),ctcplcFdFdhhL(3,3),               & 
& ctcplcFdFdhhR(3,3),ctcplcFuFdHpL(3,3,2),ctcplcFuFdHpR(3,3,2),ctcplcFeFeG0L(3,3),       & 
& ctcplcFeFeG0R(3,3),ctcplcFeFehhL(3,3),ctcplcFeFehhR(3,3),ctcplcFvFeHpL(3,3,2),         & 
& ctcplcFvFeHpR(3,3,2),ctcplcFuFuG0L(3,3),ctcplcFuFuG0R(3,3),ctcplcFuFuhhL(3,3),         & 
& ctcplcFuFuhhR(3,3),ctcplcFdFucHpL(3,3,2),ctcplcFdFucHpR(3,3,2),ctcplcFeFvcHpL(3,3,2),  & 
& ctcplcFeFvcHpR(3,3,2),ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),ctcplcFdFdVPL(3,3),        & 
& ctcplcFdFdVPR(3,3),ctcplcFuFdVWpL(3,3),ctcplcFuFdVWpR(3,3),ctcplcFdFdVZL(3,3),         & 
& ctcplcFdFdVZR(3,3),ctcplcFeFeVPL(3,3),ctcplcFeFeVPR(3,3),ctcplcFvFeVWpL(3,3),          & 
& ctcplcFvFeVWpR(3,3),ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),ctcplcFuFuVGL(3,3),          & 
& ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),           & 
& ctcplcFuFuVZR(3,3),ctcplcFdFucVWpL(3,3),ctcplcFdFucVWpR(3,3),ctcplcFvFvVZL(3,3),       & 
& ctcplcFvFvVZR(3,3),ctcplcFeFvcVWpL(3,3),ctcplcFeFvcVWpR(3,3)

Complex(dp) :: ZRUZP(2,2),ZRUZDL(3,3),ZRUZDR(3,3),ZRUZUL(3,3),ZRUZUR(3,3),ZRUZEL(3,3),               & 
& ZRUZER(3,3)

Complex(dp) :: ZcplA0A0G0,ZcplA0A0hh,ZcplA0G0H0,ZcplA0H0hh,ZcplA0HpcHp(2,2),ZcplG0G0hh,              & 
& ZcplG0H0H0,ZcplH0H0hh,ZcplH0HpcHp(2,2),Zcplhhhhhh,ZcplhhHpcHp(2,2),ZcplA0A0A0A0,       & 
& ZcplA0A0G0G0,ZcplA0A0G0hh,ZcplA0A0H0H0,ZcplA0A0hhhh,ZcplA0A0HpcHp(2,2),ZcplA0G0G0H0,   & 
& ZcplA0G0H0hh,ZcplA0G0HpcHp(2,2),ZcplA0H0hhhh,ZcplA0hhHpcHp(2,2),ZcplG0G0G0G0,          & 
& ZcplG0G0H0H0,ZcplG0G0hhhh,ZcplG0G0HpcHp(2,2),ZcplG0H0H0hh,ZcplG0H0HpcHp(2,2),          & 
& ZcplH0H0H0H0,ZcplH0H0hhhh,ZcplH0H0HpcHp(2,2),ZcplH0hhHpcHp(2,2),Zcplhhhhhhhh,          & 
& ZcplhhhhHpcHp(2,2),ZcplHpHpcHpcHp(2,2,2,2),ZcplA0H0VZ,ZcplA0HpcVWp(2),ZcplA0cHpVWp(2), & 
& ZcplG0hhVZ,ZcplG0HpcVWp(2),ZcplG0cHpVWp(2),ZcplH0HpcVWp(2),ZcplH0cHpVWp(2),            & 
& ZcplhhHpcVWp(2),ZcplhhcHpVWp(2),ZcplHpcHpVP(2,2),ZcplHpcHpVZ(2,2),ZcplhhcVWpVWp,       & 
& ZcplhhVZVZ,ZcplHpcVWpVP(2),ZcplHpcVWpVZ(2),ZcplcHpVPVWp(2),ZcplcHpVWpVZ(2),            & 
& ZcplA0A0cVWpVWp,ZcplA0A0VZVZ,ZcplA0HpcVWpVP(2),ZcplA0HpcVWpVZ(2),ZcplA0cHpVPVWp(2),    & 
& ZcplA0cHpVWpVZ(2),ZcplG0G0cVWpVWp,ZcplG0G0VZVZ,ZcplG0HpcVWpVP(2),ZcplG0HpcVWpVZ(2),    & 
& ZcplG0cHpVPVWp(2),ZcplG0cHpVWpVZ(2),ZcplH0H0cVWpVWp,ZcplH0H0VZVZ,ZcplH0HpcVWpVP(2),    & 
& ZcplH0HpcVWpVZ(2),ZcplH0cHpVPVWp(2),ZcplH0cHpVWpVZ(2),ZcplhhhhcVWpVWp,ZcplhhhhVZVZ,    & 
& ZcplhhHpcVWpVP(2),ZcplhhHpcVWpVZ(2),ZcplhhcHpVPVWp(2),ZcplhhcHpVWpVZ(2),               & 
& ZcplHpcHpVPVP(2,2),ZcplHpcHpVPVZ(2,2),ZcplHpcHpcVWpVWp(2,2),ZcplHpcHpVZVZ(2,2),        & 
& ZcplVGVGVG,ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplcFdFdG0L(3,3),ZcplcFdFdG0R(3,3),            & 
& ZcplcFdFdhhL(3,3),ZcplcFdFdhhR(3,3),ZcplcFuFdHpL(3,3,2),ZcplcFuFdHpR(3,3,2),           & 
& ZcplcFeFeG0L(3,3),ZcplcFeFeG0R(3,3),ZcplcFeFehhL(3,3),ZcplcFeFehhR(3,3),               & 
& ZcplcFvFeHpL(3,3,2),ZcplcFvFeHpR(3,3,2),ZcplcFuFuG0L(3,3),ZcplcFuFuG0R(3,3),           & 
& ZcplcFuFuhhL(3,3),ZcplcFuFuhhR(3,3),ZcplcFdFucHpL(3,3,2),ZcplcFdFucHpR(3,3,2),         & 
& ZcplcFeFvcHpL(3,3,2),ZcplcFeFvcHpR(3,3,2),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),         & 
& ZcplcFdFdVPL(3,3),ZcplcFdFdVPR(3,3),ZcplcFuFdVWpL(3,3),ZcplcFuFdVWpR(3,3),             & 
& ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),ZcplcFeFeVPL(3,3),ZcplcFeFeVPR(3,3),               & 
& ZcplcFvFeVWpL(3,3),ZcplcFvFeVWpR(3,3),ZcplcFeFeVZL(3,3),ZcplcFeFeVZR(3,3),             & 
& ZcplcFuFuVGL(3,3),ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),               & 
& ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcFdFucVWpL(3,3),ZcplcFdFucVWpR(3,3),           & 
& ZcplcFvFvVZL(3,3),ZcplcFvFvVZR(3,3),ZcplcFeFvcVWpL(3,3),ZcplcFeFvcVWpR(3,3),           & 
& ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,ZcplcVWpVPVPVWp1,ZcplcVWpVPVPVWp2,           & 
& ZcplcVWpVPVPVWp3,ZcplcVWpVPVWpVZ1,ZcplcVWpVPVWpVZ2,ZcplcVWpVPVWpVZ3,ZcplcVWpcVWpVWpVWp1,& 
& ZcplcVWpcVWpVWpVWp2,ZcplcVWpcVWpVWpVWp3,ZcplcVWpVWpVZVZ1,ZcplcVWpVWpVZVZ2,             & 
& ZcplcVWpVWpVZVZ3,ZcplcgGgGVG,ZcplcgWpgAVWp,ZcplcgWCgAcVWp,ZcplcgWpgWpVP,               & 
& ZcplcgWpgWpVZ,ZcplcgAgWpcVWp,ZcplcgZgWpcVWp,ZcplcgWCgWCVP,ZcplcgAgWCVWp,               & 
& ZcplcgZgWCVWp,ZcplcgWCgWCVZ,ZcplcgWpgZVWp,ZcplcgWCgZcVWp,ZcplcgWpgWpG0,ZcplcgWCgWCG0,  & 
& ZcplcgZgAhh,ZcplcgWpgAHp(2),ZcplcgWCgAcHp(2),ZcplcgWpgWphh,ZcplcgZgWpcHp(2),           & 
& ZcplcgWCgWChh,ZcplcgZgWCHp(2),ZcplcgZgZhh,ZcplcgWpgZHp(2),ZcplcgWCgZcHp(2)

Complex(dp) :: GcplA0HpcHp(2,2),GcplH0HpcHp(2,2),GcplhhHpcHp(2,2),GcplA0HpcVWp(2),GcplA0cHpVWp(2),   & 
& GcplG0HpcVWp(2),GcplG0cHpVWp(2),GcplH0HpcVWp(2),GcplH0cHpVWp(2),GcplhhHpcVWp(2),       & 
& GcplhhcHpVWp(2),GcplHpcHpVP(2,2),GcplHpcHpVZ(2,2),GcplHpcVWpVP(2),GcplHpcVWpVZ(2),     & 
& GcplcHpVPVWp(2),GcplcHpVWpVZ(2),GcplcFuFdHpL(3,3,2),GcplcFuFdHpR(3,3,2),               & 
& GcplcFvFeHpL(3,3,2),GcplcFvFeHpR(3,3,2),GcplcFdFucHpL(3,3,2),GcplcFdFucHpR(3,3,2),     & 
& GcplcFeFvcHpL(3,3,2),GcplcFeFvcHpR(3,3,2)

Complex(dp) :: GZcplA0HpcHp(2,2),GZcplH0HpcHp(2,2),GZcplhhHpcHp(2,2),GZcplA0HpcVWp(2),               & 
& GZcplA0cHpVWp(2),GZcplG0HpcVWp(2),GZcplG0cHpVWp(2),GZcplH0HpcVWp(2),GZcplH0cHpVWp(2),  & 
& GZcplhhHpcVWp(2),GZcplhhcHpVWp(2),GZcplHpcHpVP(2,2),GZcplHpcHpVZ(2,2),GZcplHpcVWpVP(2),& 
& GZcplHpcVWpVZ(2),GZcplcHpVPVWp(2),GZcplcHpVWpVZ(2),GZcplcFuFdHpL(3,3,2),               & 
& GZcplcFuFdHpR(3,3,2),GZcplcFvFeHpL(3,3,2),GZcplcFvFeHpR(3,3,2),GZcplcFdFucHpL(3,3,2),  & 
& GZcplcFdFucHpR(3,3,2),GZcplcFeFvcHpL(3,3,2),GZcplcFeFvcHpR(3,3,2)

Complex(dp) :: GosZcplA0HpcHp(2,2),GosZcplH0HpcHp(2,2),GosZcplhhHpcHp(2,2),GosZcplA0HpcVWp(2),       & 
& GosZcplA0cHpVWp(2),GosZcplG0HpcVWp(2),GosZcplG0cHpVWp(2),GosZcplH0HpcVWp(2),           & 
& GosZcplH0cHpVWp(2),GosZcplhhHpcVWp(2),GosZcplhhcHpVWp(2),GosZcplHpcHpVP(2,2),          & 
& GosZcplHpcHpVZ(2,2),GosZcplHpcVWpVP(2),GosZcplHpcVWpVZ(2),GosZcplcHpVPVWp(2),          & 
& GosZcplcHpVWpVZ(2),GosZcplcFuFdHpL(3,3,2),GosZcplcFuFdHpR(3,3,2),GosZcplcFvFeHpL(3,3,2),& 
& GosZcplcFvFeHpR(3,3,2),GosZcplcFdFucHpL(3,3,2),GosZcplcFdFucHpR(3,3,2),GosZcplcFeFvcHpL(3,3,2),& 
& GosZcplcFeFvcHpR(3,3,2)

Real(dp), Intent(out) :: gP1LFu(3,24) 
Real(dp), Intent(out) :: gP1LFe(3,21) 
Real(dp), Intent(out) :: gP1LFd(3,24) 
Real(dp), Intent(out) :: gP1Lhh(1,59) 
Real(dp), Intent(out) :: gP1LH0(1,54) 
Real(dp), Intent(out) :: gP1LA0(1,54) 
Real(dp), Intent(out) :: gP1LHp(2,28) 
Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateOneLoopDecays'
 
Write(*,*) "Calculating one loop decays" 
! Regulator mass for gluon/photon 
MLambda = Mass_Regulator_PhotonGluon 
divset=SetDivonlyAdd(INT(divonly_save)) 
divvalue=SetDivergenceAdd(divergence_save) 
If (.not.CalculateOneLoopMasses) Then 
 If (OSkinematics) Then 
  Write(*,*) "Loop masses not calculated: tree-level masses used for kinematics" 
  OSkinematics = .false. 
 End if
 If (ExternalZfactors) Then 
  Write(*,*) "Loop masses not calculated: no U-factors are applied" 
  ExternalZfactors = .false. 
 End if
End if

If (Extra_scale_loopDecays) Then 
q2_save = GetRenormalizationScale() 
q2 = SetRenormalizationScale(scale_loopdecays **2) 
End if 
If ((OSkinematics).or.(ExternalZfactors)) ShiftIRdiv = .true. 
If (ewOSinDecays) Then 
sinW2=1._dp-mW2/mZ2 
g1SM=sqrt(4*Pi*Alpha_MZ/(1-sinW2)) 
g2SM=sqrt(4*Pi*Alpha_MZ/Sinw2) 
vSM=sqrt(mz2*4._dp/(g1SM**2+g2SM**2)) 
v=vSM 
g1=g1SM 
g2=g2SM 
 If (yukOSinDecays) Then !! Allow OS Yukawas only together with vSM 
    YuSM = 0._dp 
    YdSM = 0._dp 
    YuSM = 0._dp 
   Do i1=1,3 
      YuSM(i1,i1)=sqrt(2._dp)*mf_u(i1)/vSM 
      YeSM(i1,i1)=sqrt(2._dp)*mf_l(i1)/vSM 
      YdSM(i1,i1)=sqrt(2._dp)*mf_d(i1)/vSM 
    End Do 
   If(GenerationMixing) Then 
    YuSM = Transpose(Matmul(Transpose(CKM),Transpose(YuSM))) 
   End if 
Ye=YeSM 
Yd=YdSM 
Yu=YuSM 
 End if 
End if 
! -------------------------------------------- 
! General information needed in the following 
! -------------------------------------------- 

! DR parameters 
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,v,(/ ZeroC, ZeroC /))

Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,GenerationMixing,kont)

! Stabilize numerics 
If (Abs(MG0).lt.1.0E-15_dp) MG0=0._dp
If (Abs(MG02).lt.1.0E-30_dp) MG02=0._dp
If (Abs(Mhh).lt.1.0E-15_dp) Mhh=0._dp
If (Abs(Mhh2).lt.1.0E-30_dp) Mhh2=0._dp
If (Abs(MA0).lt.1.0E-15_dp) MA0=0._dp
If (Abs(MA02).lt.1.0E-30_dp) MA02=0._dp
If (Abs(MH0).lt.1.0E-15_dp) MH0=0._dp
If (Abs(MH02).lt.1.0E-30_dp) MH02=0._dp
Where (Abs(MHp).lt.1.0E-15_dp) MHp=0._dp
Where (Abs(MHp2).lt.1.0E-30_dp) MHp2=0._dp
Where (Abs(MFd).lt.1.0E-15_dp) MFd=0._dp
Where (Abs(MFd2).lt.1.0E-30_dp) MFd2=0._dp
Where (Abs(MFu).lt.1.0E-15_dp) MFu=0._dp
Where (Abs(MFu2).lt.1.0E-30_dp) MFu2=0._dp
Where (Abs(MFe).lt.1.0E-15_dp) MFe=0._dp
Where (Abs(MFe2).lt.1.0E-30_dp) MFe2=0._dp
If (UseZeroRotationMatrices) Then  ! Rotation matrices calculated for p2=0
ZRUZP = MatMul(ZPOS_0, Transpose(ZP))
ZRUZDL = MatMul(ZDLOS_0, Conjg(Transpose(ZDL)))
ZRUZDR = MatMul(ZDROS_0, Conjg(Transpose(ZDR)))
ZRUZUL = MatMul(ZULOS_0, Conjg(Transpose(ZUL)))
ZRUZUR = MatMul(ZUROS_0, Conjg(Transpose(ZUR)))
ZRUZEL = MatMul(ZELOS_0, Conjg(Transpose(ZEL)))
ZRUZER = MatMul(ZEROS_0, Conjg(Transpose(ZER)))
Else If (UseP2Matrices) Then   ! p2 dependent matrix 
ZRUZP = MatMul(ZPOS_p2, Transpose(ZP))
ZRUZDL = MatMul(ZDLOS_p2, Conjg(Transpose(ZDL)))
ZRUZDR = MatMul(ZDROS_p2, Conjg(Transpose(ZDR)))
ZRUZUL = MatMul(ZULOS_p2, Conjg(Transpose(ZUL)))
ZRUZUR = MatMul(ZUROS_p2, Conjg(Transpose(ZUR)))
ZRUZEL = MatMul(ZELOS_p2, Conjg(Transpose(ZEL)))
ZRUZER = MatMul(ZEROS_p2, Conjg(Transpose(ZER)))
Else  ! Rotation matrix for lightest state
ZRUZP = MatMul(ZPOS, Transpose(ZP))
ZRUZDL = MatMul(ZDLOS, Conjg(Transpose(ZDL)))
ZRUZDR = MatMul(ZDROS, Conjg(Transpose(ZDR)))
ZRUZUL = MatMul(ZULOS, Conjg(Transpose(ZUL)))
ZRUZUR = MatMul(ZUROS, Conjg(Transpose(ZUR)))
ZRUZEL = MatMul(ZELOS, Conjg(Transpose(ZEL)))
ZRUZER = MatMul(ZEROS, Conjg(Transpose(ZER)))
End if 
! Couplings 
Call AllCouplingsReallyAll(lam5,v,lam3,lam4,ZP,lam1,lam2,g1,g2,TW,g3,Yd,              & 
& ZDL,ZDR,Yu,ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,      & 
& cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0A0A0A0,             & 
& cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplA0G0G0H0,              & 
& cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,cplG0G0H0H0,             & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,cplH0H0hhhh,             & 
& cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,cplA0H0VZ,            & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0HpcVWpVP,          & 
& cplA0HpcVWpVZ,cplA0cHpVPVWp,cplA0cHpVWpVZ,cplG0G0cVWpVWp,cplG0G0VZVZ,cplG0HpcVWpVP,    & 
& cplG0HpcVWpVZ,cplG0cHpVPVWp,cplG0cHpVWpVZ,cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP,    & 
& cplH0HpcVWpVZ,cplH0cHpVPVWp,cplH0cHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP,    & 
& cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,cplHpcHpcVWpVWp,   & 
& cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,cplcFdFdG0R,              & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,cplcFeFeG0R,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,cplcFuFuG0R,               & 
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
& cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,cplcgWCgWCG0,cplcgZgAhh,          & 
& cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,           & 
& cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp)

em = cplcVWpVPVWp 
gs = cplcFdFdVGL(1,1) 
Call CouplingsColoredQuartics(lam2,lam5,lam3,lam4,ZP,lam1,g2,g1,TW,g3,cplA0A0A0A01,   & 
& cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0G0G0H01,        & 
& cplA0G0H0hh1,cplA0G0HpcHp1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0G0G0G01,cplG0G0H0H01,       & 
& cplG0G0hhhh1,cplG0G0HpcHp1,cplG0H0H0hh1,cplG0H0HpcHp1,cplH0H0H0H01,cplH0H0hhhh1,       & 
& cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhhhhh1,cplhhhhHpcHp1,cplHpHpcHpcHp1,cplA0A0cVWpVWp1, & 
& cplA0A0VZVZ1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,              & 
& cplG0G0cVWpVWp1,cplG0G0VZVZ1,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplG0cHpVPVWp1,             & 
& cplG0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,             & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,cplhhHpcVWpVP1,             & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpVPVP1,cplHpcHpVPVZ1,              & 
& cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q,              & 
& cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q,cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,  & 
& cplcVWpVPVWpVZ3Q,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,          & 
& cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q)

If (externalZfactors) Then 
Call getZCouplings(lam5,v,lam3,lam4,ZP,lam1,lam2,g1,g2,TW,g3,Yd,ZDL,ZDR,              & 
& Yu,ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,              & 
& cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0A0A0A0,             & 
& cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplA0G0G0H0,              & 
& cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,cplG0G0H0H0,             & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,cplH0H0hhhh,             & 
& cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,cplA0H0VZ,            & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0HpcVWpVP,          & 
& cplA0HpcVWpVZ,cplA0cHpVPVWp,cplA0cHpVWpVZ,cplG0G0cVWpVWp,cplG0G0VZVZ,cplG0HpcVWpVP,    & 
& cplG0HpcVWpVZ,cplG0cHpVPVWp,cplG0cHpVWpVZ,cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP,    & 
& cplH0HpcVWpVZ,cplH0cHpVPVWp,cplH0cHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP,    & 
& cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,cplHpcHpcVWpVWp,   & 
& cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,cplcFdFdG0R,              & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,cplcFeFeG0R,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,cplcFuFuG0R,               & 
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
& cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,cplcgWCgWCG0,cplcgZgAhh,          & 
& cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,           & 
& cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,          & 
& ZRUZER,ZcplA0A0G0,ZcplA0A0hh,ZcplA0G0H0,ZcplA0H0hh,ZcplA0HpcHp,ZcplG0G0hh,             & 
& ZcplG0H0H0,ZcplH0H0hh,ZcplH0HpcHp,Zcplhhhhhh,ZcplhhHpcHp,ZcplA0A0A0A0,ZcplA0A0G0G0,    & 
& ZcplA0A0G0hh,ZcplA0A0H0H0,ZcplA0A0hhhh,ZcplA0A0HpcHp,ZcplA0G0G0H0,ZcplA0G0H0hh,        & 
& ZcplA0G0HpcHp,ZcplA0H0hhhh,ZcplA0hhHpcHp,ZcplG0G0G0G0,ZcplG0G0H0H0,ZcplG0G0hhhh,       & 
& ZcplG0G0HpcHp,ZcplG0H0H0hh,ZcplG0H0HpcHp,ZcplH0H0H0H0,ZcplH0H0hhhh,ZcplH0H0HpcHp,      & 
& ZcplH0hhHpcHp,Zcplhhhhhhhh,ZcplhhhhHpcHp,ZcplHpHpcHpcHp,ZcplA0H0VZ,ZcplA0HpcVWp,       & 
& ZcplA0cHpVWp,ZcplG0hhVZ,ZcplG0HpcVWp,ZcplG0cHpVWp,ZcplH0HpcVWp,ZcplH0cHpVWp,           & 
& ZcplhhHpcVWp,ZcplhhcHpVWp,ZcplHpcHpVP,ZcplHpcHpVZ,ZcplhhcVWpVWp,ZcplhhVZVZ,            & 
& ZcplHpcVWpVP,ZcplHpcVWpVZ,ZcplcHpVPVWp,ZcplcHpVWpVZ,ZcplA0A0cVWpVWp,ZcplA0A0VZVZ,      & 
& ZcplA0HpcVWpVP,ZcplA0HpcVWpVZ,ZcplA0cHpVPVWp,ZcplA0cHpVWpVZ,ZcplG0G0cVWpVWp,           & 
& ZcplG0G0VZVZ,ZcplG0HpcVWpVP,ZcplG0HpcVWpVZ,ZcplG0cHpVPVWp,ZcplG0cHpVWpVZ,              & 
& ZcplH0H0cVWpVWp,ZcplH0H0VZVZ,ZcplH0HpcVWpVP,ZcplH0HpcVWpVZ,ZcplH0cHpVPVWp,             & 
& ZcplH0cHpVWpVZ,ZcplhhhhcVWpVWp,ZcplhhhhVZVZ,ZcplhhHpcVWpVP,ZcplhhHpcVWpVZ,             & 
& ZcplhhcHpVPVWp,ZcplhhcHpVWpVZ,ZcplHpcHpVPVP,ZcplHpcHpVPVZ,ZcplHpcHpcVWpVWp,            & 
& ZcplHpcHpVZVZ,ZcplVGVGVG,ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplcFdFdG0L,ZcplcFdFdG0R,        & 
& ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFeFeG0L,ZcplcFeFeG0R,         & 
& ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFvFeHpL,ZcplcFvFeHpR,ZcplcFuFuG0L,ZcplcFuFuG0R,         & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFeFvcHpL,ZcplcFeFvcHpR,     & 
& ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,       & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFvFeVWpL,ZcplcFvFeVWpR,       & 
& ZcplcFeFeVZL,ZcplcFeFeVZR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,         & 
& ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplcFvFvVZL,ZcplcFvFvVZR,     & 
& ZcplcFeFvcVWpL,ZcplcFeFvcVWpR,ZcplVGVGVGVG1,ZcplVGVGVGVG2,ZcplVGVGVGVG3,               & 
& ZcplcVWpVPVPVWp1,ZcplcVWpVPVPVWp2,ZcplcVWpVPVPVWp3,ZcplcVWpVPVWpVZ1,ZcplcVWpVPVWpVZ2,  & 
& ZcplcVWpVPVWpVZ3,ZcplcVWpcVWpVWpVWp1,ZcplcVWpcVWpVWpVWp2,ZcplcVWpcVWpVWpVWp3,          & 
& ZcplcVWpVWpVZVZ1,ZcplcVWpVWpVZVZ2,ZcplcVWpVWpVZVZ3,ZcplcgGgGVG,ZcplcgWpgAVWp,          & 
& ZcplcgWCgAcVWp,ZcplcgWpgWpVP,ZcplcgWpgWpVZ,ZcplcgAgWpcVWp,ZcplcgZgWpcVWp,              & 
& ZcplcgWCgWCVP,ZcplcgAgWCVWp,ZcplcgZgWCVWp,ZcplcgWCgWCVZ,ZcplcgWpgZVWp,ZcplcgWCgZcVWp,  & 
& ZcplcgWpgWpG0,ZcplcgWCgWCG0,ZcplcgZgAhh,ZcplcgWpgAHp,ZcplcgWCgAcHp,ZcplcgWpgWphh,      & 
& ZcplcgZgWpcHp,ZcplcgWCgWChh,ZcplcgZgWCHp,ZcplcgZgZhh,ZcplcgWpgZHp,ZcplcgWCgZcHp)

End if 
Call getGBCouplings(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,              & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,cplA0cHpVWp,cplcFdFucVWpL,cplcFdFucVWpR,            & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFvFeVWpL,cplcFvFeVWpR,       & 
& cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplH0cHpVWp,cplhhcHpVWp,             & 
& cplhhcVWpVWp,ZcplA0cHpVWp,ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplcFeFvcVWpL,ZcplcFeFvcVWpR, & 
& ZcplcFuFdVWpL,ZcplcFuFdVWpR,ZcplcFvFeVWpL,ZcplcFvFeVWpR,ZcplcHpVPVWp,ZcplcHpVWpVZ,     & 
& ZcplcVWpVPVWp,ZcplcVWpVWpVZ,ZcplH0cHpVWp,ZcplhhcHpVWp,ZcplhhcVWpVWp,GcplA0HpcHp,       & 
& GcplH0HpcHp,GcplhhHpcHp,GcplA0HpcVWp,GcplA0cHpVWp,GcplG0HpcVWp,GcplG0cHpVWp,           & 
& GcplH0HpcVWp,GcplH0cHpVWp,GcplhhHpcVWp,GcplhhcHpVWp,GcplHpcHpVP,GcplHpcHpVZ,           & 
& GcplHpcVWpVP,GcplHpcVWpVZ,GcplcHpVPVWp,GcplcHpVWpVZ,GcplcFuFdHpL,GcplcFuFdHpR,         & 
& GcplcFvFeHpL,GcplcFvFeHpR,GcplcFdFucHpL,GcplcFdFucHpR,GcplcFeFvcHpL,GcplcFeFvcHpR,     & 
& GZcplA0HpcHp,GZcplH0HpcHp,GZcplhhHpcHp,GZcplA0HpcVWp,GZcplA0cHpVWp,GZcplG0HpcVWp,      & 
& GZcplG0cHpVWp,GZcplH0HpcVWp,GZcplH0cHpVWp,GZcplhhHpcVWp,GZcplhhcHpVWp,GZcplHpcHpVP,    & 
& GZcplHpcHpVZ,GZcplHpcVWpVP,GZcplHpcVWpVZ,GZcplcHpVPVWp,GZcplcHpVWpVZ,GZcplcFuFdHpL,    & 
& GZcplcFuFdHpR,GZcplcFvFeHpL,GZcplcFvFeHpR,GZcplcFdFucHpL,GZcplcFdFucHpR,               & 
& GZcplcFeFvcHpL,GZcplcFeFvcHpR,GosZcplA0HpcHp,GosZcplH0HpcHp,GosZcplhhHpcHp,            & 
& GosZcplA0HpcVWp,GosZcplA0cHpVWp,GosZcplG0HpcVWp,GosZcplG0cHpVWp,GosZcplH0HpcVWp,       & 
& GosZcplH0cHpVWp,GosZcplhhHpcVWp,GosZcplhhcHpVWp,GosZcplHpcHpVP,GosZcplHpcHpVZ,         & 
& GosZcplHpcVWpVP,GosZcplHpcVWpVZ,GosZcplcHpVPVWp,GosZcplcHpVWpVZ,GosZcplcFuFdHpL,       & 
& GosZcplcFuFdHpR,GosZcplcFvFeHpL,GosZcplcFvFeHpR,GosZcplcFdFucHpL,GosZcplcFdFucHpR,     & 
& GosZcplcFeFvcHpL,GosZcplcFeFvcHpR)

! Write intilization of all counter terms 
Call WaveFunctionRenormalisation(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,              & 
& MFeOS,MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,         & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Ye,Yd,Yu,MHD2,MHU2,v,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,               & 
& cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0A0A0A0,             & 
& cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplA0G0G0H0,              & 
& cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,cplG0G0H0H0,             & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,cplH0H0hhhh,             & 
& cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,cplA0H0VZ,            & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0HpcVWpVP,          & 
& cplA0HpcVWpVZ,cplA0cHpVPVWp,cplA0cHpVWpVZ,cplG0G0cVWpVWp,cplG0G0VZVZ,cplG0HpcVWpVP,    & 
& cplG0HpcVWpVZ,cplG0cHpVPVWp,cplG0cHpVWpVZ,cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP,    & 
& cplH0HpcVWpVZ,cplH0cHpVPVWp,cplH0cHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP,    & 
& cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,cplHpcHpcVWpVWp,   & 
& cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,cplcFdFdG0R,              & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,cplcFeFeG0R,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,cplcFuFuG0R,               & 
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
& cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,cplcgWCgWCG0,cplcgZgAhh,          & 
& cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,           & 
& cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,GcplA0HpcHp,GcplH0HpcHp,GcplhhHpcHp,               & 
& GcplA0HpcVWp,GcplA0cHpVWp,GcplG0HpcVWp,GcplG0cHpVWp,GcplH0HpcVWp,GcplH0cHpVWp,         & 
& GcplhhHpcVWp,GcplhhcHpVWp,GcplHpcHpVP,GcplHpcHpVZ,GcplHpcVWpVP,GcplHpcVWpVZ,           & 
& GcplcHpVPVWp,GcplcHpVWpVZ,GcplcFuFdHpL,GcplcFuFdHpR,GcplcFvFeHpL,GcplcFvFeHpR,         & 
& GcplcFdFucHpL,GcplcFdFucHpR,GcplcFeFvcHpL,GcplcFeFvcHpR,dg1,dg2,dg3,dYe,               & 
& dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,               & 
& dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,           & 
& ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,ZfVPVZ,ZfVZVP,ctcplA0A0G0,ctcplA0A0hh,        & 
& ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp,ctcplG0G0hh,ctcplG0H0H0,ctcplH0H0hh,              & 
& ctcplH0HpcHp,ctcplhhhhhh,ctcplhhHpcHp,ctcplA0H0VZ,ctcplA0HpcVWp,ctcplA0cHpVWp,         & 
& ctcplG0hhVZ,ctcplG0HpcVWp,ctcplG0cHpVWp,ctcplH0HpcVWp,ctcplH0cHpVWp,ctcplhhHpcVWp,     & 
& ctcplhhcHpVWp,ctcplHpcHpVP,ctcplHpcHpVZ,ctcplhhcVWpVWp,ctcplhhVZVZ,ctcplHpcVWpVP,      & 
& ctcplHpcVWpVZ,ctcplcHpVPVWp,ctcplcHpVWpVZ,ctcplVGVGVG,ctcplcVWpVPVWp,ctcplcVWpVWpVZ,   & 
& ctcplcFdFdG0L,ctcplcFdFdG0R,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFuFdHpL,ctcplcFuFdHpR,   & 
& ctcplcFeFeG0L,ctcplcFeFeG0R,ctcplcFeFehhL,ctcplcFeFehhR,ctcplcFvFeHpL,ctcplcFvFeHpR,   & 
& ctcplcFuFuG0L,ctcplcFuFuG0R,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFucHpL,ctcplcFdFucHpR, & 
& ctcplcFeFvcHpL,ctcplcFeFvcHpR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,               & 
& ctcplcFdFdVPR,ctcplcFuFdVWpL,ctcplcFuFdVWpR,ctcplcFdFdVZL,ctcplcFdFdVZR,               & 
& ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFvFeVWpL,ctcplcFvFeVWpR,ctcplcFeFeVZL,               & 
& ctcplcFeFeVZR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,   & 
& ctcplcFuFuVZR,ctcplcFdFucVWpL,ctcplcFdFucVWpR,ctcplcFvFvVZL,ctcplcFvFvVZR,             & 
& ctcplcFeFvcVWpL,ctcplcFeFvcVWpR,MLambda,deltaM,kont)

! -------------------------------------------- 
! The decays at one-loop 
! -------------------------------------------- 

! Fu
If (CalcLoopDecay_Fu) Then 
Call OneLoopDecay_Fu(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,cplcFdFdG0L,cplcFdFdG0R,              & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,             & 
& cplG0cHpVWp,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplH0cHpVWp,cplH0HpcHp,cplH0HpcVWp,        & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhVZVZ,cplHpcHpVP,        & 
& cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,cplVGVGVG,ctcplcFuFdHpL,ctcplcFuFdHpR,              & 
& ctcplcFuFdVWpL,ctcplcFuFdVWpR,ctcplcFuFuG0L,ctcplcFuFuG0R,ctcplcFuFuhhL,               & 
& ctcplcFuFuhhR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,   & 
& ctcplcFuFuVZR,GcplcFuFdHpL,GcplcFuFdHpR,GcplcHpVPVWp,GcplHpcVWpVP,GosZcplcFuFdHpL,     & 
& GosZcplcFuFdHpR,GosZcplcHpVPVWp,GosZcplHpcVWpVP,GZcplcFuFdHpL,GZcplcFuFdHpR,           & 
& GZcplcHpVPVWp,GZcplHpcVWpVP,ZcplA0cHpVWp,ZcplA0HpcHp,ZcplA0HpcVWp,ZcplcFdFdVGL,        & 
& ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFdFucVWpL,     & 
& ZcplcFdFucVWpR,ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,ZcplcFuFuG0L,     & 
& ZcplcFuFuG0R,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,         & 
& ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcHpVPVWp,ZcplcVWpVPVWp,ZcplH0cHpVWp,        & 
& ZcplH0HpcHp,ZcplH0HpcVWp,ZcplHpcHpVP,ZcplHpcVWpVP,ZcplVGVGVG,ZRUZP,ZRUZDL,             & 
& ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LFu)

End if 
! Fe
If (CalcLoopDecay_Fe) Then 
Call OneLoopDecay_Fe(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,cplcFeFeG0L,cplcFeFeG0R,              & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFvFeHpL,cplcFvFeHpR,         & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcHpVPVWp,cplcHpVWpVZ,             & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplG0cHpVWp,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplH0cHpVWp,     & 
& cplH0HpcHp,cplH0HpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,ctcplcFeFeG0L,ctcplcFeFeG0R,   & 
& ctcplcFeFehhL,ctcplcFeFehhR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,   & 
& ctcplcFeFvcHpL,ctcplcFeFvcHpR,ctcplcFeFvcVWpL,ctcplcFeFvcVWpR,GcplcFeFvcHpL,           & 
& GcplcFeFvcHpR,GcplcHpVPVWp,GcplHpcVWpVP,GosZcplcFeFvcHpL,GosZcplcFeFvcHpR,             & 
& GosZcplcHpVPVWp,GosZcplHpcVWpVP,GZcplcFeFvcHpL,GZcplcFeFvcHpR,GZcplcHpVPVWp,           & 
& GZcplHpcVWpVP,ZcplA0cHpVWp,ZcplA0HpcHp,ZcplA0HpcVWp,ZcplcFeFeG0L,ZcplcFeFeG0R,         & 
& ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFeFeVPL,ZcplcFeFeVPR,ZcplcFeFeVZL,ZcplcFeFeVZR,         & 
& ZcplcFeFvcHpL,ZcplcFeFvcHpR,ZcplcFeFvcVWpL,ZcplcFeFvcVWpR,ZcplcFvFeHpL,ZcplcFvFeHpR,   & 
& ZcplcFvFeVWpL,ZcplcFvFeVWpR,ZcplcHpVPVWp,ZcplcVWpVPVWp,ZcplH0cHpVWp,ZcplH0HpcHp,       & 
& ZcplH0HpcVWp,ZcplHpcHpVP,ZcplHpcVWpVP,ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,               & 
& ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LFe)

End if 
! Fd
If (CalcLoopDecay_Fd) Then 
Call OneLoopDecay_Fd(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0cHpVWp,cplA0HpcHp,cplA0HpcVWp,cplcFdFdG0L,cplcFdFdG0R,              & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,             & 
& cplG0cHpVWp,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplH0cHpVWp,cplH0HpcHp,cplH0HpcVWp,        & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhVZVZ,cplHpcHpVP,        & 
& cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,cplVGVGVG,ctcplcFdFdG0L,ctcplcFdFdG0R,              & 
& ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,ctcplcFdFdVPR,   & 
& ctcplcFdFdVZL,ctcplcFdFdVZR,ctcplcFdFucHpL,ctcplcFdFucHpR,ctcplcFdFucVWpL,             & 
& ctcplcFdFucVWpR,GcplcFdFucHpL,GcplcFdFucHpR,GcplcHpVPVWp,GcplHpcVWpVP,GosZcplcFdFucHpL,& 
& GosZcplcFdFucHpR,GosZcplcHpVPVWp,GosZcplHpcVWpVP,GZcplcFdFucHpL,GZcplcFdFucHpR,        & 
& GZcplcHpVPVWp,GZcplHpcVWpVP,ZcplA0cHpVWp,ZcplA0HpcHp,ZcplA0HpcVWp,ZcplcFdFdG0L,        & 
& ZcplcFdFdG0R,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,         & 
& ZcplcFdFdVPR,ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFdFucVWpL,     & 
& ZcplcFdFucVWpR,ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,ZcplcFuFuVGL,     & 
& ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcHpVPVWp,ZcplcVWpVPVWp,ZcplH0cHpVWp,        & 
& ZcplH0HpcHp,ZcplH0HpcVWp,ZcplHpcHpVP,ZcplHpcVWpVP,ZcplVGVGVG,ZRUZP,ZRUZDL,             & 
& ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LFd)

End if 
! hh
If (CalcLoopDecay_hh) Then 
Call OneLoopDecay_hh(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0A0A0A01,cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,        & 
& cplA0A0H0H01,cplA0A0hh,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0VZVZ1,cplA0cHpVPVWp1,         & 
& cplA0cHpVWp,cplA0cHpVWpVZ1,cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1,          & 
& cplA0H0hh,cplA0H0hhhh1,cplA0H0VZ,cplA0hhHpcHp1,cplA0HpcHp,cplA0HpcVWp,cplA0HpcVWpVP1,  & 
& cplA0HpcVWpVZ1,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,              & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,          & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,              & 
& cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,         & 
& cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,              & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFeHpL,               & 
& cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcgAgWCVWp,            & 
& cplcgAgWpcVWp,cplcgWCgAcVWp,cplcgWCgWCG0,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,       & 
& cplcgWCgZcHp,cplcgWCgZcVWp,cplcgWpgAHp,cplcgWpgAVWp,cplcgWpgWpG0,cplcgWpgWphh,         & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWpgZHp,cplcgWpgZVWp,cplcgZgAhh,cplcgZgWCHp,             & 
& cplcgZgWCVWp,cplcgZgWpcHp,cplcgZgWpcVWp,cplcgZgZhh,cplcHpVPVWp,cplcHpVWpVZ,            & 
& cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,cplcVWpVPVPVWp1Q,          & 
& cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q,cplcVWpVPVWp,cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,      & 
& cplcVWpVPVWpVZ3Q,cplcVWpVWpVZ,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,      & 
& cplG0cHpVPVWp1,cplG0cHpVWp,cplG0cHpVWpVZ1,cplG0G0cVWpVWp1,cplG0G0G0G01,cplG0G0H0H01,   & 
& cplG0G0hh,cplG0G0hhhh1,cplG0G0HpcHp1,cplG0G0VZVZ1,cplG0H0H0,cplG0H0H0hh1,              & 
& cplG0H0HpcHp1,cplG0hhVZ,cplG0HpcVWp,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplH0cHpVPVWp1,      & 
& cplH0cHpVWp,cplH0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0H0H0H01,cplH0H0hh,cplH0H0hhhh1,        & 
& cplH0H0HpcHp1,cplH0H0VZVZ1,cplH0hhHpcHp1,cplH0HpcHp,cplH0HpcVWp,cplH0HpcVWpVP1,        & 
& cplH0HpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWp,cplhhcHpVWpVZ1,cplhhcVWpVWp,cplhhhhcVWpVWp1, & 
& cplhhhhhh,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhVZVZ1,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhVZVZ,cplHpcHpcVWpVWp1,cplHpcHpVP,cplHpcHpVPVP1,     & 
& cplHpcHpVPVZ1,cplHpcHpVZ,cplHpcHpVZVZ1,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp1,         & 
& ctcplA0A0hh,ctcplA0H0hh,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFeFehhL,ctcplcFeFehhR,       & 
& ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplG0G0hh,ctcplG0hhVZ,ctcplH0H0hh,ctcplhhcVWpVWp,        & 
& ctcplhhhhhh,ctcplhhHpcHp,ctcplhhHpcVWp,ctcplhhVZVZ,GcplcHpVPVWp,GcplhhcHpVWp,          & 
& GcplhhHpcHp,GcplHpcVWpVP,GosZcplcHpVPVWp,GosZcplhhcHpVWp,GosZcplhhHpcHp,               & 
& GosZcplHpcVWpVP,GZcplcHpVPVWp,GZcplhhcHpVWp,GZcplhhHpcHp,GZcplHpcVWpVP,ZcplA0A0hh,     & 
& ZcplA0H0hh,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFuFuhhL,           & 
& ZcplcFuFuhhR,ZcplG0G0hh,ZcplG0hhVZ,ZcplH0H0hh,ZcplhhcVWpVWp,Zcplhhhhhh,ZcplhhHpcHp,    & 
& ZcplhhHpcVWp,ZcplhhVZVZ,ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,               & 
& MLambda,em,gs,deltaM,kont,gP1Lhh)

End if 
! H0
If (CalcLoopDecay_H0) Then 
Call OneLoopDecay_H0(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hh,              & 
& cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0VZVZ1,cplA0cHpVPVWp1,cplA0cHpVWp,cplA0cHpVWpVZ1,     & 
& cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1,cplA0H0hh,cplA0H0hhhh1,              & 
& cplA0H0VZ,cplA0hhHpcHp1,cplA0HpcHp,cplA0HpcVWp,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,          & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcHpL,cplcFeFvcHpR,       & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,         & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcHpVPVWp,cplcHpVWpVZ,             & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplG0cHpVPVWp1,cplG0cHpVWp,cplG0cHpVWpVZ1,cplG0G0H0H01,      & 
& cplG0G0hh,cplG0G0HpcHp1,cplG0H0H0,cplG0H0H0hh1,cplG0H0HpcHp1,cplG0hhVZ,cplG0HpcVWp,    & 
& cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWp,cplH0cHpVWpVZ1,               & 
& cplH0H0cVWpVWp1,cplH0H0H0H01,cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0VZVZ1,        & 
& cplH0hhHpcHp1,cplH0HpcHp,cplH0HpcVWp,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplhhcHpVPVWp1,     & 
& cplhhcHpVWp,cplhhcHpVWpVZ1,cplhhcVWpVWp,cplhhhhhh,cplhhhhHpcHp1,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhVZVZ,cplHpcHpcVWpVWp1,cplHpcHpVP,       & 
& cplHpcHpVPVP1,cplHpcHpVPVZ1,cplHpcHpVZ,cplHpcHpVZVZ1,cplHpcVWpVP,cplHpcVWpVZ,          & 
& cplHpHpcHpcHp1,ctcplA0G0H0,ctcplA0H0hh,ctcplA0H0VZ,ctcplG0H0H0,ctcplH0H0hh,            & 
& ctcplH0HpcHp,ctcplH0HpcVWp,GcplcHpVPVWp,GcplH0HpcHp,GcplHpcVWpVP,GosZcplcHpVPVWp,      & 
& GosZcplH0HpcHp,GosZcplHpcVWpVP,GZcplcHpVPVWp,GZcplH0HpcHp,GZcplHpcVWpVP,               & 
& ZcplA0G0H0,ZcplA0H0hh,ZcplA0H0VZ,ZcplG0H0H0,ZcplH0H0hh,ZcplH0HpcHp,ZcplH0HpcVWp,       & 
& ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LH0)

End if 
! A0
If (CalcLoopDecay_A0) Then 
Call OneLoopDecay_A0(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0A0A0A01,cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,        & 
& cplA0A0H0H01,cplA0A0hh,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0VZVZ1,cplA0cHpVPVWp1,         & 
& cplA0cHpVWp,cplA0cHpVWpVZ1,cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1,          & 
& cplA0H0hh,cplA0H0hhhh1,cplA0H0VZ,cplA0hhHpcHp1,cplA0HpcHp,cplA0HpcVWp,cplA0HpcVWpVP1,  & 
& cplA0HpcVWpVZ1,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcHpL,     & 
& cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,         & 
& cplcFuFdVWpR,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,cplcHpVPVWp,            & 
& cplcHpVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplG0cHpVPVWp1,cplG0cHpVWp,cplG0cHpVWpVZ1,       & 
& cplG0G0H0H01,cplG0G0hh,cplG0G0HpcHp1,cplG0H0H0,cplG0H0H0hh1,cplG0H0HpcHp1,             & 
& cplG0hhVZ,cplG0HpcVWp,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWp,        & 
& cplH0cHpVWpVZ1,cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0VZVZ1,cplH0hhHpcHp1,        & 
& cplH0HpcHp,cplH0HpcVWp,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWp,       & 
& cplhhcHpVWpVZ1,cplhhcVWpVWp,cplhhhhhh,cplhhhhHpcHp1,cplhhHpcHp,cplhhHpcVWp,            & 
& cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhVZVZ,cplHpcHpcVWpVWp1,cplHpcHpVP,cplHpcHpVPVP1,     & 
& cplHpcHpVPVZ1,cplHpcHpVZ,cplHpcHpVZVZ1,cplHpcVWpVP,cplHpcVWpVZ,cplHpHpcHpcHp1,         & 
& ctcplA0A0G0,ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0H0VZ,ctcplA0HpcHp,              & 
& ctcplA0HpcVWp,GcplA0HpcHp,GcplcHpVPVWp,GcplHpcVWpVP,GosZcplA0HpcHp,GosZcplcHpVPVWp,    & 
& GosZcplHpcVWpVP,GZcplA0HpcHp,GZcplcHpVPVWp,GZcplHpcVWpVP,ZcplA0A0G0,ZcplA0A0hh,        & 
& ZcplA0G0H0,ZcplA0H0hh,ZcplA0H0VZ,ZcplA0HpcHp,ZcplA0HpcVWp,ZRUZP,ZRUZDL,ZRUZDR,         & 
& ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,MLambda,em,gs,deltaM,kont,gP1LA0)

End if 
! Hp
If (CalcLoopDecay_Hp) Then 
Call OneLoopDecay_Hp(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,             & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,               & 
& ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,               & 
& Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,               & 
& dlam3,dlam2,dv,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,ZfVG,            & 
& ZfvL,ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,           & 
& ZfVPVZ,ZfVZVP,cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0hh,cplA0A0HpcHp1,cplA0cHpVPVWp1,        & 
& cplA0cHpVWp,cplA0cHpVWpVZ1,cplA0G0H0,cplA0G0HpcHp1,cplA0H0hh,cplA0H0VZ,cplA0hhHpcHp1,  & 
& cplA0HpcHp,cplA0HpcVWp,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplcFdFdG0L,cplcFdFdG0R,          & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,         & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,cplcFvFeVWpR,             & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgAgWCVWp,cplcgWCgAcHp,cplcgWCgWCG0,cplcgWCgWChh,           & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp,cplcgWpgWpG0,cplcgWpgWphh,cplcgWpgWpVP,         & 
& cplcgWpgWpVZ,cplcgWpgZHp,cplcgWpgZVWp,cplcgZgAhh,cplcgZgWCHp,cplcgZgWCVWp,             & 
& cplcgZgWpcHp,cplcgZgZhh,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,     & 
& cplcVWpVPVPVWp3Q,cplcVWpVPVWp,cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ3Q,      & 
& cplcVWpVWpVZ,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplG0cHpVPVWp1,        & 
& cplG0cHpVWp,cplG0cHpVWpVZ1,cplG0G0cVWpVWp1,cplG0G0hh,cplG0G0HpcHp1,cplG0H0H0,          & 
& cplG0H0HpcHp1,cplG0hhVZ,cplG0HpcVWp,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,cplH0cHpVPVWp1,      & 
& cplH0cHpVWp,cplH0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0H0hh,cplH0H0HpcHp1,cplH0hhHpcHp1,      & 
& cplH0HpcHp,cplH0HpcVWp,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWp,       & 
& cplhhcHpVWpVZ1,cplhhcVWpVWp,cplhhhhcVWpVWp1,cplhhhhhh,cplhhhhHpcHp1,cplhhHpcHp,        & 
& cplhhHpcVWp,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhVZVZ,cplHpcHpcVWpVWp1,cplHpcHpVP,       & 
& cplHpcHpVPVP1,cplHpcHpVPVZ1,cplHpcHpVZ,cplHpcHpVZVZ1,cplHpcVWpVP,cplHpcVWpVZ,          & 
& cplHpHpcHpcHp1,ctcplA0cHpVWp,ctcplA0HpcHp,ctcplcFdFucHpL,ctcplcFdFucHpR,               & 
& ctcplcFeFvcHpL,ctcplcFeFvcHpR,ctcplcHpVPVWp,ctcplcHpVWpVZ,ctcplG0cHpVWp,               & 
& ctcplH0cHpVWp,ctcplH0HpcHp,ctcplhhcHpVWp,ctcplhhHpcHp,ctcplHpcHpVP,ctcplHpcHpVZ,       & 
& GcplA0HpcHp,GcplcHpVPVWp,GcplH0HpcHp,GcplhhHpcHp,GcplHpcHpVZ,GcplHpcVWpVP,             & 
& GosZcplA0HpcHp,GosZcplcHpVPVWp,GosZcplH0HpcHp,GosZcplhhHpcHp,GosZcplHpcHpVZ,           & 
& GosZcplHpcVWpVP,GZcplA0HpcHp,GZcplcHpVPVWp,GZcplH0HpcHp,GZcplhhHpcHp,GZcplHpcHpVZ,     & 
& GZcplHpcVWpVP,ZcplA0cHpVWp,ZcplA0HpcHp,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFeFvcHpL,      & 
& ZcplcFeFvcHpR,ZcplcHpVWpVZ,ZcplG0cHpVWp,ZcplH0cHpVWp,ZcplH0HpcHp,ZcplhhcHpVWp,         & 
& ZcplhhHpcHp,ZcplHpcHpVZ,ZRUZP,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,ZRUZEL,ZRUZER,               & 
& MLambda,em,gs,deltaM,kont,gP1LHp)

End if 
If (Extra_scale_loopDecays) Then 
q2 = SetRenormalizationScale(q2_save) 
End if 
Iname = Iname - 1 
 
End Subroutine CalculateOneLoopDecays  
 
 
End Module OneLoopDecays_Inert2 
 