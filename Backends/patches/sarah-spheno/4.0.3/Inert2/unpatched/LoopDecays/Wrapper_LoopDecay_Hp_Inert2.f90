! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Hp_Inert2
Use Model_Data_Inert2 
Use Kinematics 
Use OneLoopDecay_Hp_Inert2 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Hp(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,              & 
& MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,               & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Ye,Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,            & 
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

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(in) :: v

Real(dp),Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(in) :: dg1,dg2,dg3,dMHD2,dMHU2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp),Intent(in) :: dYe(3,3),dYd(3,3),dYu(3,3),dlam5,dlam1,dlam4,dlam3,dlam2,dZDL(3,3),dZDR(3,3),         & 
& dZUL(3,3),dZUR(3,3),dZEL(3,3),dZER(3,3)

Complex(dp),Intent(in) :: cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0hh,cplA0A0HpcHp1(2,2),cplA0cHpVPVWp1(2),             & 
& cplA0cHpVWp(2),cplA0cHpVWpVZ1(2),cplA0G0H0,cplA0G0HpcHp1(2,2),cplA0H0hh,               & 
& cplA0H0VZ,cplA0hhHpcHp1(2,2),cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0HpcVWpVP1(2),         & 
& cplA0HpcVWpVZ1(2),cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3), & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),& 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),& 
& cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFdHpL(3,3,2),          & 
& cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFuFuG0L(3,3),               & 
& cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),  & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFvFvVZL(3,3),               & 
& cplcFvFvVZR(3,3),cplcgAgWCVWp,cplcgWCgAcHp(2),cplcgWCgWCG0,cplcgWCgWChh,               & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp(2),cplcgWpgWpG0,cplcgWpgWphh,cplcgWpgWpVP,      & 
& cplcgWpgWpVZ,cplcgWpgZHp(2),cplcgWpgZVWp,cplcgZgAhh,cplcgZgWCHp(2),cplcgZgWCVWp,       & 
& cplcgZgWpcHp(2),cplcgZgZhh,cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVPVWp1Q,             & 
& cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q,cplcVWpVPVWp,cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,      & 
& cplcVWpVPVWpVZ3Q,cplcVWpVWpVZ,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,      & 
& cplG0cHpVPVWp1(2),cplG0cHpVWp(2),cplG0cHpVWpVZ1(2),cplG0G0cVWpVWp1,cplG0G0hh,          & 
& cplG0G0HpcHp1(2,2),cplG0H0H0,cplG0H0HpcHp1(2,2),cplG0hhVZ,cplG0HpcVWp(2),              & 
& cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplH0cHpVPVWp1(2),cplH0cHpVWp(2),cplH0cHpVWpVZ1(2),& 
& cplH0H0cVWpVWp1,cplH0H0hh,cplH0H0HpcHp1(2,2),cplH0hhHpcHp1(2,2),cplH0HpcHp(2,2),       & 
& cplH0HpcVWp(2),cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2),cplhhcHpVPVWp1(2),cplhhcHpVWp(2),   & 
& cplhhcHpVWpVZ1(2),cplhhcVWpVWp,cplhhhhcVWpVWp1,cplhhhhhh,cplhhhhHpcHp1(2,2),           & 
& cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),cplhhVZVZ,          & 
& cplHpcHpcVWpVWp1(2,2),cplHpcHpVP(2,2),cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2),           & 
& cplHpcHpVZ(2,2),cplHpcHpVZVZ1(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2),cplHpHpcHpcHp1(2,2,2,2),& 
& ctcplA0cHpVWp(2),ctcplA0HpcHp(2,2),ctcplcFdFucHpL(3,3,2),ctcplcFdFucHpR(3,3,2),        & 
& ctcplcFeFvcHpL(3,3,2),ctcplcFeFvcHpR(3,3,2),ctcplcHpVPVWp(2),ctcplcHpVWpVZ(2),         & 
& ctcplG0cHpVWp(2),ctcplH0cHpVWp(2),ctcplH0HpcHp(2,2),ctcplhhcHpVWp(2),ctcplhhHpcHp(2,2),& 
& ctcplHpcHpVP(2,2),ctcplHpcHpVZ(2,2),GcplA0HpcHp(2,2),GcplcHpVPVWp(2),GcplH0HpcHp(2,2), & 
& GcplhhHpcHp(2,2),GcplHpcHpVZ(2,2),GcplHpcVWpVP(2),GosZcplA0HpcHp(2,2),GosZcplcHpVPVWp(2),& 
& GosZcplH0HpcHp(2,2),GosZcplhhHpcHp(2,2),GosZcplHpcHpVZ(2,2),GosZcplHpcVWpVP(2),        & 
& GZcplA0HpcHp(2,2),GZcplcHpVPVWp(2),GZcplH0HpcHp(2,2),GZcplhhHpcHp(2,2),GZcplHpcHpVZ(2,2),& 
& GZcplHpcVWpVP(2),ZcplA0cHpVWp(2),ZcplA0HpcHp(2,2),ZcplcFdFucHpL(3,3,2),ZcplcFdFucHpR(3,3,2),& 
& ZcplcFeFvcHpL(3,3,2),ZcplcFeFvcHpR(3,3,2),ZcplcHpVWpVZ(2),ZcplG0cHpVWp(2)

Complex(dp),Intent(in) :: ZcplH0cHpVWp(2),ZcplH0HpcHp(2,2),ZcplhhcHpVWp(2),ZcplhhHpcHp(2,2),ZcplHpcHpVZ(2,2)

Real(dp), Intent(in) :: em, gs 
Complex(dp),Intent(in) :: ZfVG,ZfvL(3,3),ZfG0,Zfhh,ZfA0,ZfH0,ZfVP,ZfVZ,ZfVWp,ZfHp(2,2),ZfDL(3,3),               & 
& ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfEL(3,3),ZfER(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MHpOS(2),MHp2OS(2),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),          & 
& MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,MVWpOS,               & 
& MVWp2OS,ZPOS(2,2)

Complex(dp),Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Complex(dp),Intent(in) :: ZRUZP(2,2),ZRUZDL(3,3),ZRUZDR(3,3),ZRUZUL(3,3),ZRUZUR(3,3),ZRUZEL(3,3),               & 
& ZRUZER(3,3)

Real(dp), Intent(in) :: MLambda, deltaM 
Real(dp), Intent(out) :: gP1LHp(2,28) 
Integer, Intent(out) :: kont 
Real(dp) :: MVG,MVP,MVG2,MVP2, helfactor, phasespacefactor 
Integer :: i1,i2,i3,i4, isave, gt1, gt2, gt3 

Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUZDLc(3, 3) 
Complex(dp) :: ZRUZDRc(3, 3) 
Complex(dp) :: ZRUZULc(3, 3) 
Complex(dp) :: ZRUZURc(3, 3) 
Complex(dp) :: ZRUZELc(3, 3) 
Complex(dp) :: ZRUZERc(3, 3) 
Real(dp) :: MRPHpToHpA0(2,2),MRGHpToHpA0(2,2), MRPZHpToHpA0(2,2),MRGZHpToHpA0(2,2) 
Real(dp) :: MVPHpToHpA0(2,2) 
Real(dp) :: RMsqTreeHpToHpA0(2,2),RMsqWaveHpToHpA0(2,2),RMsqVertexHpToHpA0(2,2) 
Complex(dp) :: AmpTreeHpToHpA0(2,2),AmpWaveHpToHpA0(2,2)=(0._dp,0._dp),AmpVertexHpToHpA0(2,2)& 
 & ,AmpVertexIRosHpToHpA0(2,2),AmpVertexIRdrHpToHpA0(2,2), AmpSumHpToHpA0(2,2), AmpSum2HpToHpA0(2,2) 
Complex(dp) :: AmpTreeZHpToHpA0(2,2),AmpWaveZHpToHpA0(2,2),AmpVertexZHpToHpA0(2,2) 
Real(dp) :: AmpSqHpToHpA0(2,2),  AmpSqTreeHpToHpA0(2,2) 
Real(dp) :: MRPHpToA0VWp(2),MRGHpToA0VWp(2), MRPZHpToA0VWp(2),MRGZHpToA0VWp(2) 
Real(dp) :: MVPHpToA0VWp(2) 
Real(dp) :: RMsqTreeHpToA0VWp(2),RMsqWaveHpToA0VWp(2),RMsqVertexHpToA0VWp(2) 
Complex(dp) :: AmpTreeHpToA0VWp(2,2),AmpWaveHpToA0VWp(2,2)=(0._dp,0._dp),AmpVertexHpToA0VWp(2,2)& 
 & ,AmpVertexIRosHpToA0VWp(2,2),AmpVertexIRdrHpToA0VWp(2,2), AmpSumHpToA0VWp(2,2), AmpSum2HpToA0VWp(2,2) 
Complex(dp) :: AmpTreeZHpToA0VWp(2,2),AmpWaveZHpToA0VWp(2,2),AmpVertexZHpToA0VWp(2,2) 
Real(dp) :: AmpSqHpToA0VWp(2),  AmpSqTreeHpToA0VWp(2) 
Real(dp) :: MRPHpTocFdFu(2,3,3),MRGHpTocFdFu(2,3,3), MRPZHpTocFdFu(2,3,3),MRGZHpTocFdFu(2,3,3) 
Real(dp) :: MVPHpTocFdFu(2,3,3) 
Real(dp) :: RMsqTreeHpTocFdFu(2,3,3),RMsqWaveHpTocFdFu(2,3,3),RMsqVertexHpTocFdFu(2,3,3) 
Complex(dp) :: AmpTreeHpTocFdFu(2,2,3,3),AmpWaveHpTocFdFu(2,2,3,3)=(0._dp,0._dp),AmpVertexHpTocFdFu(2,2,3,3)& 
 & ,AmpVertexIRosHpTocFdFu(2,2,3,3),AmpVertexIRdrHpTocFdFu(2,2,3,3), AmpSumHpTocFdFu(2,2,3,3), AmpSum2HpTocFdFu(2,2,3,3) 
Complex(dp) :: AmpTreeZHpTocFdFu(2,2,3,3),AmpWaveZHpTocFdFu(2,2,3,3),AmpVertexZHpTocFdFu(2,2,3,3) 
Real(dp) :: AmpSqHpTocFdFu(2,3,3),  AmpSqTreeHpTocFdFu(2,3,3) 
Real(dp) :: MRPHpTocFeFv(2,3,3),MRGHpTocFeFv(2,3,3), MRPZHpTocFeFv(2,3,3),MRGZHpTocFeFv(2,3,3) 
Real(dp) :: MVPHpTocFeFv(2,3,3) 
Real(dp) :: RMsqTreeHpTocFeFv(2,3,3),RMsqWaveHpTocFeFv(2,3,3),RMsqVertexHpTocFeFv(2,3,3) 
Complex(dp) :: AmpTreeHpTocFeFv(2,2,3,3),AmpWaveHpTocFeFv(2,2,3,3)=(0._dp,0._dp),AmpVertexHpTocFeFv(2,2,3,3)& 
 & ,AmpVertexIRosHpTocFeFv(2,2,3,3),AmpVertexIRdrHpTocFeFv(2,2,3,3), AmpSumHpTocFeFv(2,2,3,3), AmpSum2HpTocFeFv(2,2,3,3) 
Complex(dp) :: AmpTreeZHpTocFeFv(2,2,3,3),AmpWaveZHpTocFeFv(2,2,3,3),AmpVertexZHpTocFeFv(2,2,3,3) 
Real(dp) :: AmpSqHpTocFeFv(2,3,3),  AmpSqTreeHpTocFeFv(2,3,3) 
Real(dp) :: MRPHpToHpH0(2,2),MRGHpToHpH0(2,2), MRPZHpToHpH0(2,2),MRGZHpToHpH0(2,2) 
Real(dp) :: MVPHpToHpH0(2,2) 
Real(dp) :: RMsqTreeHpToHpH0(2,2),RMsqWaveHpToHpH0(2,2),RMsqVertexHpToHpH0(2,2) 
Complex(dp) :: AmpTreeHpToHpH0(2,2),AmpWaveHpToHpH0(2,2)=(0._dp,0._dp),AmpVertexHpToHpH0(2,2)& 
 & ,AmpVertexIRosHpToHpH0(2,2),AmpVertexIRdrHpToHpH0(2,2), AmpSumHpToHpH0(2,2), AmpSum2HpToHpH0(2,2) 
Complex(dp) :: AmpTreeZHpToHpH0(2,2),AmpWaveZHpToHpH0(2,2),AmpVertexZHpToHpH0(2,2) 
Real(dp) :: AmpSqHpToHpH0(2,2),  AmpSqTreeHpToHpH0(2,2) 
Real(dp) :: MRPHpToH0VWp(2),MRGHpToH0VWp(2), MRPZHpToH0VWp(2),MRGZHpToH0VWp(2) 
Real(dp) :: MVPHpToH0VWp(2) 
Real(dp) :: RMsqTreeHpToH0VWp(2),RMsqWaveHpToH0VWp(2),RMsqVertexHpToH0VWp(2) 
Complex(dp) :: AmpTreeHpToH0VWp(2,2),AmpWaveHpToH0VWp(2,2)=(0._dp,0._dp),AmpVertexHpToH0VWp(2,2)& 
 & ,AmpVertexIRosHpToH0VWp(2,2),AmpVertexIRdrHpToH0VWp(2,2), AmpSumHpToH0VWp(2,2), AmpSum2HpToH0VWp(2,2) 
Complex(dp) :: AmpTreeZHpToH0VWp(2,2),AmpWaveZHpToH0VWp(2,2),AmpVertexZHpToH0VWp(2,2) 
Real(dp) :: AmpSqHpToH0VWp(2),  AmpSqTreeHpToH0VWp(2) 
Real(dp) :: MRPHpToHphh(2,2),MRGHpToHphh(2,2), MRPZHpToHphh(2,2),MRGZHpToHphh(2,2) 
Real(dp) :: MVPHpToHphh(2,2) 
Real(dp) :: RMsqTreeHpToHphh(2,2),RMsqWaveHpToHphh(2,2),RMsqVertexHpToHphh(2,2) 
Complex(dp) :: AmpTreeHpToHphh(2,2),AmpWaveHpToHphh(2,2)=(0._dp,0._dp),AmpVertexHpToHphh(2,2)& 
 & ,AmpVertexIRosHpToHphh(2,2),AmpVertexIRdrHpToHphh(2,2), AmpSumHpToHphh(2,2), AmpSum2HpToHphh(2,2) 
Complex(dp) :: AmpTreeZHpToHphh(2,2),AmpWaveZHpToHphh(2,2),AmpVertexZHpToHphh(2,2) 
Real(dp) :: AmpSqHpToHphh(2,2),  AmpSqTreeHpToHphh(2,2) 
Real(dp) :: MRPHpTohhVWp(2),MRGHpTohhVWp(2), MRPZHpTohhVWp(2),MRGZHpTohhVWp(2) 
Real(dp) :: MVPHpTohhVWp(2) 
Real(dp) :: RMsqTreeHpTohhVWp(2),RMsqWaveHpTohhVWp(2),RMsqVertexHpTohhVWp(2) 
Complex(dp) :: AmpTreeHpTohhVWp(2,2),AmpWaveHpTohhVWp(2,2)=(0._dp,0._dp),AmpVertexHpTohhVWp(2,2)& 
 & ,AmpVertexIRosHpTohhVWp(2,2),AmpVertexIRdrHpTohhVWp(2,2), AmpSumHpTohhVWp(2,2), AmpSum2HpTohhVWp(2,2) 
Complex(dp) :: AmpTreeZHpTohhVWp(2,2),AmpWaveZHpTohhVWp(2,2),AmpVertexZHpTohhVWp(2,2) 
Real(dp) :: AmpSqHpTohhVWp(2),  AmpSqTreeHpTohhVWp(2) 
Real(dp) :: MRPHpToHpVZ(2,2),MRGHpToHpVZ(2,2), MRPZHpToHpVZ(2,2),MRGZHpToHpVZ(2,2) 
Real(dp) :: MVPHpToHpVZ(2,2) 
Real(dp) :: RMsqTreeHpToHpVZ(2,2),RMsqWaveHpToHpVZ(2,2),RMsqVertexHpToHpVZ(2,2) 
Complex(dp) :: AmpTreeHpToHpVZ(2,2,2),AmpWaveHpToHpVZ(2,2,2)=(0._dp,0._dp),AmpVertexHpToHpVZ(2,2,2)& 
 & ,AmpVertexIRosHpToHpVZ(2,2,2),AmpVertexIRdrHpToHpVZ(2,2,2), AmpSumHpToHpVZ(2,2,2), AmpSum2HpToHpVZ(2,2,2) 
Complex(dp) :: AmpTreeZHpToHpVZ(2,2,2),AmpWaveZHpToHpVZ(2,2,2),AmpVertexZHpToHpVZ(2,2,2) 
Real(dp) :: AmpSqHpToHpVZ(2,2),  AmpSqTreeHpToHpVZ(2,2) 
Real(dp) :: MRPHpToVZVWp(2),MRGHpToVZVWp(2), MRPZHpToVZVWp(2),MRGZHpToVZVWp(2) 
Real(dp) :: MVPHpToVZVWp(2) 
Real(dp) :: RMsqTreeHpToVZVWp(2),RMsqWaveHpToVZVWp(2),RMsqVertexHpToVZVWp(2) 
Complex(dp) :: AmpTreeHpToVZVWp(2,2),AmpWaveHpToVZVWp(2,2)=(0._dp,0._dp),AmpVertexHpToVZVWp(2,2)& 
 & ,AmpVertexIRosHpToVZVWp(2,2),AmpVertexIRdrHpToVZVWp(2,2), AmpSumHpToVZVWp(2,2), AmpSum2HpToVZVWp(2,2) 
Complex(dp) :: AmpTreeZHpToVZVWp(2,2),AmpWaveZHpToVZVWp(2,2),AmpVertexZHpToVZVWp(2,2) 
Real(dp) :: AmpSqHpToVZVWp(2),  AmpSqTreeHpToVZVWp(2) 
Real(dp) :: MRPHpToHpVP(2,2),MRGHpToHpVP(2,2), MRPZHpToHpVP(2,2),MRGZHpToHpVP(2,2) 
Real(dp) :: MVPHpToHpVP(2,2) 
Real(dp) :: RMsqTreeHpToHpVP(2,2),RMsqWaveHpToHpVP(2,2),RMsqVertexHpToHpVP(2,2) 
Complex(dp) :: AmpTreeHpToHpVP(2,2,2),AmpWaveHpToHpVP(2,2,2)=(0._dp,0._dp),AmpVertexHpToHpVP(2,2,2)& 
 & ,AmpVertexIRosHpToHpVP(2,2,2),AmpVertexIRdrHpToHpVP(2,2,2), AmpSumHpToHpVP(2,2,2), AmpSum2HpToHpVP(2,2,2) 
Complex(dp) :: AmpTreeZHpToHpVP(2,2,2),AmpWaveZHpToHpVP(2,2,2),AmpVertexZHpToHpVP(2,2,2) 
Real(dp) :: AmpSqHpToHpVP(2,2),  AmpSqTreeHpToHpVP(2,2) 
Real(dp) :: MRPHpToVPVWp(2),MRGHpToVPVWp(2), MRPZHpToVPVWp(2),MRGZHpToVPVWp(2) 
Real(dp) :: MVPHpToVPVWp(2) 
Real(dp) :: RMsqTreeHpToVPVWp(2),RMsqWaveHpToVPVWp(2),RMsqVertexHpToVPVWp(2) 
Complex(dp) :: AmpTreeHpToVPVWp(2,2),AmpWaveHpToVPVWp(2,2)=(0._dp,0._dp),AmpVertexHpToVPVWp(2,2)& 
 & ,AmpVertexIRosHpToVPVWp(2,2),AmpVertexIRdrHpToVPVWp(2,2), AmpSumHpToVPVWp(2,2), AmpSum2HpToVPVWp(2,2) 
Complex(dp) :: AmpTreeZHpToVPVWp(2,2),AmpWaveZHpToVPVWp(2,2),AmpVertexZHpToVPVWp(2,2) 
Real(dp) :: AmpSqHpToVPVWp(2),  AmpSqTreeHpToVPVWp(2) 
Write(*,*) "Calculating one-loop decays of Hp " 
kont = 0 
MVG = MLambda 
MVP = MLambda 
MVG2 = MLambda**2 
MVP2 = MLambda**2 

ZRUZPc = Conjg(ZRUZP)
ZRUZDLc = Conjg(ZRUZDL)
ZRUZDRc = Conjg(ZRUZDR)
ZRUZULc = Conjg(ZRUZUL)
ZRUZURc = Conjg(ZRUZUR)
ZRUZELc = Conjg(ZRUZEL)
ZRUZERc = Conjg(ZRUZER)

 ! Counter 
isave = 1 

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Hp A0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToHpA0(cplA0HpcHp,MA0,MHp,MA02,MHp2,AmpTreeHpToHpA0)

  Else 
Call Amplitude_Tree_Inert2_HpToHpA0(ZcplA0HpcHp,MA0,MHp,MA02,MHp2,AmpTreeHpToHpA0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToHpA0(MLambda,em,gs,cplA0HpcHp,MA0OS,MHpOS,MRPHpToHpA0,     & 
& MRGHpToHpA0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToHpA0(MLambda,em,gs,ZcplA0HpcHp,MA0OS,MHpOS,MRPHpToHpA0,    & 
& MRGHpToHpA0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToHpA0(MLambda,em,gs,cplA0HpcHp,MA0,MHp,MRPHpToHpA0,         & 
& MRGHpToHpA0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToHpA0(MLambda,em,gs,ZcplA0HpcHp,MA0,MHp,MRPHpToHpA0,        & 
& MRGHpToHpA0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToHpA0(cplA0HpcHp,ctcplA0HpcHp,MA0,MA02,MHp,             & 
& MHp2,ZfA0,ZfHp,AmpWaveHpToHpA0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToHpA0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,       & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,            & 
& cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,             & 
& cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexHpToHpA0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToHpA0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,       & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,            & 
& cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,             & 
& cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexIRdrHpToHpA0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpA0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,ZcplA0HpcHp,cplA0HpcVWp,             & 
& cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,              & 
& AmpVertexIRosHpToHpA0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpA0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,ZcplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,      & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,            & 
& cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,             & 
& cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexIRosHpToHpA0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpA0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,              & 
& cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,   & 
& cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,              & 
& AmpVertexIRosHpToHpA0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpA0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcHp,       & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0G0HpcHp1,            & 
& cplA0hhHpcHp1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,             & 
& cplG0H0HpcHp1,cplH0hhHpcHp1,cplHpHpcHpcHp1,AmpVertexIRosHpToHpA0)

 End if 
 End if 
AmpVertexHpToHpA0 = AmpVertexHpToHpA0 -  AmpVertexIRdrHpToHpA0! +  AmpVertexIRosHpToHpA0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToHpA0=0._dp 
AmpVertexZHpToHpA0=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHpA0(gt2,:) = AmpWaveZHpToHpA0(gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHpToHpA0(gt1,:) 
AmpVertexZHpToHpA0(gt2,:)= AmpVertexZHpToHpA0(gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHpToHpA0(gt1,:) 
 End Do 
End Do 
AmpWaveHpToHpA0=AmpWaveZHpToHpA0 
AmpVertexHpToHpA0= AmpVertexZHpToHpA0
! Final State 1 
AmpWaveZHpToHpA0=0._dp 
AmpVertexZHpToHpA0=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHpA0(:,gt2) = AmpWaveZHpToHpA0(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToHpA0(:,gt1) 
AmpVertexZHpToHpA0(:,gt2)= AmpVertexZHpToHpA0(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexHpToHpA0(:,gt1) 
 End Do 
End Do 
AmpWaveHpToHpA0=AmpWaveZHpToHpA0 
AmpVertexHpToHpA0= AmpVertexZHpToHpA0
End if
If (ShiftIRdiv) Then 
AmpVertexHpToHpA0 = AmpVertexHpToHpA0  +  AmpVertexIRosHpToHpA0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->Hp A0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToHpA0 = AmpTreeHpToHpA0 
 AmpSum2HpToHpA0 = AmpTreeHpToHpA0 + 2._dp*AmpWaveHpToHpA0 + 2._dp*AmpVertexHpToHpA0  
Else 
 AmpSumHpToHpA0 = AmpTreeHpToHpA0 + AmpWaveHpToHpA0 + AmpVertexHpToHpA0
 AmpSum2HpToHpA0 = AmpTreeHpToHpA0 + AmpWaveHpToHpA0 + AmpVertexHpToHpA0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToHpA0 = AmpTreeHpToHpA0
 AmpSum2HpToHpA0 = AmpTreeHpToHpA0 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MHpOS(gt2))+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MHp(gt2))+Abs(MA0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HpToHpA0 = AmpTreeHpToHpA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MA0OS,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MA0,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToHpA0(gt1, gt2) 
  AmpSum2HpToHpA0 = 2._dp*AmpWaveHpToHpA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MA0OS,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MA0,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToHpA0(gt1, gt2) 
  AmpSum2HpToHpA0 = 2._dp*AmpVertexHpToHpA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MA0OS,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MA0,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToHpA0(gt1, gt2) 
  AmpSum2HpToHpA0 = AmpTreeHpToHpA0 + 2._dp*AmpWaveHpToHpA0 + 2._dp*AmpVertexHpToHpA0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MA0OS,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MA0,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToHpA0(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToHpA0 = AmpTreeHpToHpA0
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MA0OS,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
  AmpSqTreeHpToHpA0(gt1, gt2) = AmpSqHpToHpA0(gt1, gt2)  
  AmpSum2HpToHpA0 = + 2._dp*AmpWaveHpToHpA0 + 2._dp*AmpVertexHpToHpA0
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MA0OS,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
  AmpSqHpToHpA0(gt1, gt2) = AmpSqHpToHpA0(gt1, gt2) + AmpSqTreeHpToHpA0(gt1, gt2)  
Else  
  AmpSum2HpToHpA0 = AmpTreeHpToHpA0
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MA0,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
  AmpSqTreeHpToHpA0(gt1, gt2) = AmpSqHpToHpA0(gt1, gt2)  
  AmpSum2HpToHpA0 = + 2._dp*AmpWaveHpToHpA0 + 2._dp*AmpVertexHpToHpA0
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MA0,AmpSumHpToHpA0(gt1, gt2),AmpSum2HpToHpA0(gt1, gt2),AmpSqHpToHpA0(gt1, gt2)) 
  AmpSqHpToHpA0(gt1, gt2) = AmpSqHpToHpA0(gt1, gt2) + AmpSqTreeHpToHpA0(gt1, gt2)  
End if  
Else  
  AmpSqHpToHpA0(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToHpA0(gt1, gt2).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MHpOS(gt2),MA0OS,helfactor*AmpSqHpToHpA0(gt1, gt2))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MHp(gt2),MA0,helfactor*AmpSqHpToHpA0(gt1, gt2))
End if 
If ((Abs(MRPHpToHpA0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpA0(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToHpA0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpA0(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHpToHpA0(gt1, gt2) + MRGHpToHpA0(gt1, gt2)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHpToHpA0(gt1, gt2) + MRGHpToHpA0(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! A0 VWp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToA0VWp(cplA0cHpVWp,MA0,MHp,MVWp,MA02,MHp2,              & 
& MVWp2,AmpTreeHpToA0VWp)

  Else 
Call Amplitude_Tree_Inert2_HpToA0VWp(ZcplA0cHpVWp,MA0,MHp,MVWp,MA02,MHp2,             & 
& MVWp2,AmpTreeHpToA0VWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToA0VWp(MLambda,em,gs,cplA0cHpVWp,MA0OS,MHpOS,               & 
& MVWpOS,MRPHpToA0VWp,MRGHpToA0VWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToA0VWp(MLambda,em,gs,ZcplA0cHpVWp,MA0OS,MHpOS,              & 
& MVWpOS,MRPHpToA0VWp,MRGHpToA0VWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToA0VWp(MLambda,em,gs,cplA0cHpVWp,MA0,MHp,MVWp,              & 
& MRPHpToA0VWp,MRGHpToA0VWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToA0VWp(MLambda,em,gs,ZcplA0cHpVWp,MA0,MHp,MVWp,             & 
& MRPHpToA0VWp,MRGHpToA0VWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToA0VWp(cplA0cHpVWp,ctcplA0cHpVWp,MA0,MA02,              & 
& MHp,MHp2,MVWp,MVWp2,ZfA0,ZfHp,ZfVWp,AmpWaveHpToA0VWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToA0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,              & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,      & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,cplH0cHpVWp,       & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,    & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1, & 
& cplHpcHpcVWpVWp1,AmpVertexHpToA0VWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToA0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRdrHpToA0VWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToA0VWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,GosZcplA0HpcHp,cplA0HpcVWp,          & 
& ZcplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,   & 
& cplHpcHpVP,cplHpcHpVZ,GosZcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,           & 
& cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRosHpToA0VWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToA0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,GZcplA0HpcHp,cplA0HpcVWp,ZcplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,      & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,GZcplcHpVPVWp,   & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpToA0VWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToA0VWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,GcplA0HpcHp,cplA0HpcVWp,             & 
& cplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,    & 
& cplHpcHpVP,cplHpcHpVZ,GcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRosHpToA0VWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToA0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,            & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0cHpVWp,cplH0HpcHp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplA0cHpVPVWp1,cplA0cHpVWpVZ1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpToA0VWp)

 End if 
 End if 
AmpVertexHpToA0VWp = AmpVertexHpToA0VWp -  AmpVertexIRdrHpToA0VWp! +  AmpVertexIRosHpToA0VWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToA0VWp=0._dp 
AmpVertexZHpToA0VWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToA0VWp(:,gt2) = AmpWaveZHpToA0VWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToA0VWp(:,gt1) 
AmpVertexZHpToA0VWp(:,gt2)= AmpVertexZHpToA0VWp(:,gt2) + ZRUZP(gt2,gt1)*AmpVertexHpToA0VWp(:,gt1) 
 End Do 
End Do 
AmpWaveHpToA0VWp=AmpWaveZHpToA0VWp 
AmpVertexHpToA0VWp= AmpVertexZHpToA0VWp
End if
If (ShiftIRdiv) Then 
AmpVertexHpToA0VWp = AmpVertexHpToA0VWp  +  AmpVertexIRosHpToA0VWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->A0 VWp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToA0VWp = AmpTreeHpToA0VWp 
 AmpSum2HpToA0VWp = AmpTreeHpToA0VWp + 2._dp*AmpWaveHpToA0VWp + 2._dp*AmpVertexHpToA0VWp  
Else 
 AmpSumHpToA0VWp = AmpTreeHpToA0VWp + AmpWaveHpToA0VWp + AmpVertexHpToA0VWp
 AmpSum2HpToA0VWp = AmpTreeHpToA0VWp + AmpWaveHpToA0VWp + AmpVertexHpToA0VWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToA0VWp = AmpTreeHpToA0VWp
 AmpSum2HpToA0VWp = AmpTreeHpToA0VWp 
End if 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MA0OS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MA0)+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2HpToA0VWp = AmpTreeHpToA0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MA0OS,MVWpOS,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MA0,MVWp,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToA0VWp(gt1) 
  AmpSum2HpToA0VWp = 2._dp*AmpWaveHpToA0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MA0OS,MVWpOS,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MA0,MVWp,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToA0VWp(gt1) 
  AmpSum2HpToA0VWp = 2._dp*AmpVertexHpToA0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MA0OS,MVWpOS,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MA0,MVWp,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToA0VWp(gt1) 
  AmpSum2HpToA0VWp = AmpTreeHpToA0VWp + 2._dp*AmpWaveHpToA0VWp + 2._dp*AmpVertexHpToA0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MA0OS,MVWpOS,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MA0,MVWp,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToA0VWp(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToA0VWp = AmpTreeHpToA0VWp
  Call SquareAmp_StoSV(MHpOS(gt1),MA0OS,MVWpOS,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
  AmpSqTreeHpToA0VWp(gt1) = AmpSqHpToA0VWp(gt1)  
  AmpSum2HpToA0VWp = + 2._dp*AmpWaveHpToA0VWp + 2._dp*AmpVertexHpToA0VWp
  Call SquareAmp_StoSV(MHpOS(gt1),MA0OS,MVWpOS,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
  AmpSqHpToA0VWp(gt1) = AmpSqHpToA0VWp(gt1) + AmpSqTreeHpToA0VWp(gt1)  
Else  
  AmpSum2HpToA0VWp = AmpTreeHpToA0VWp
  Call SquareAmp_StoSV(MHp(gt1),MA0,MVWp,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
  AmpSqTreeHpToA0VWp(gt1) = AmpSqHpToA0VWp(gt1)  
  AmpSum2HpToA0VWp = + 2._dp*AmpWaveHpToA0VWp + 2._dp*AmpVertexHpToA0VWp
  Call SquareAmp_StoSV(MHp(gt1),MA0,MVWp,AmpSumHpToA0VWp(:,gt1),AmpSum2HpToA0VWp(:,gt1),AmpSqHpToA0VWp(gt1)) 
  AmpSqHpToA0VWp(gt1) = AmpSqHpToA0VWp(gt1) + AmpSqTreeHpToA0VWp(gt1)  
End if  
Else  
  AmpSqHpToA0VWp(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToA0VWp(gt1).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MA0OS,MVWpOS,helfactor*AmpSqHpToA0VWp(gt1))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MA0,MVWp,helfactor*AmpSqHpToA0VWp(gt1))
End if 
If ((Abs(MRPHpToA0VWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToA0VWp(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToA0VWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToA0VWp(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHpToA0VWp(gt1) + MRGHpToA0VWp(gt1)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHpToA0VWp(gt1) + MRGHpToA0VWp(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fd) Fu
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpTocFdFu(cplcFdFucHpL,cplcFdFucHpR,MFd,MFu,               & 
& MHp,MFd2,MFu2,MHp2,AmpTreeHpTocFdFu)

  Else 
Call Amplitude_Tree_Inert2_HpTocFdFu(ZcplcFdFucHpL,ZcplcFdFucHpR,MFd,MFu,             & 
& MHp,MFd2,MFu2,MHp2,AmpTreeHpTocFdFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpTocFdFu(MLambda,em,gs,cplcFdFucHpL,cplcFdFucHpR,             & 
& MFdOS,MFuOS,MHpOS,MRPHpTocFdFu,MRGHpTocFdFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpTocFdFu(MLambda,em,gs,ZcplcFdFucHpL,ZcplcFdFucHpR,           & 
& MFdOS,MFuOS,MHpOS,MRPHpTocFdFu,MRGHpTocFdFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpTocFdFu(MLambda,em,gs,cplcFdFucHpL,cplcFdFucHpR,             & 
& MFd,MFu,MHp,MRPHpTocFdFu,MRGHpTocFdFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpTocFdFu(MLambda,em,gs,ZcplcFdFucHpL,ZcplcFdFucHpR,           & 
& MFd,MFu,MHp,MRPHpTocFdFu,MRGHpTocFdFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpTocFdFu(cplcFdFucHpL,cplcFdFucHpR,ctcplcFdFucHpL,        & 
& ctcplcFdFucHpR,MFd,MFd2,MFu,MFu2,MHp,MHp2,ZfDL,ZfDR,ZfHp,ZfUL,ZfUR,AmpWaveHpTocFdFu)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpTocFdFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,              & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexHpTocFdFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpTocFdFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRdrHpTocFdFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFdFu(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,ZcplcFdFucHpL,ZcplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,       & 
& cplG0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& AmpVertexIRosHpTocFdFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFdFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& ZcplcFdFucHpL,ZcplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,        & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRosHpTocFdFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFdFu(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& AmpVertexIRosHpTocFdFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFdFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRosHpTocFdFu)

 End if 
 End if 
AmpVertexHpTocFdFu = AmpVertexHpTocFdFu -  AmpVertexIRdrHpTocFdFu! +  AmpVertexIRosHpTocFdFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpTocFdFu=0._dp 
AmpVertexZHpTocFdFu=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpTocFdFu(:,gt2,:,:) = AmpWaveZHpTocFdFu(:,gt2,:,:)+ZRUZP(gt2,gt1)*AmpWaveHpTocFdFu(:,gt1,:,:) 
AmpVertexZHpTocFdFu(:,gt2,:,:)= AmpVertexZHpTocFdFu(:,gt2,:,:) + ZRUZP(gt2,gt1)*AmpVertexHpTocFdFu(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveHpTocFdFu=AmpWaveZHpTocFdFu 
AmpVertexHpTocFdFu= AmpVertexZHpTocFdFu
! Final State 1 
AmpWaveZHpTocFdFu=0._dp 
AmpVertexZHpTocFdFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZHpTocFdFu(1,:,gt2,:) = AmpWaveZHpTocFdFu(1,:,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveHpTocFdFu(1,:,gt1,:) 
AmpVertexZHpTocFdFu(1,:,gt2,:)= AmpVertexZHpTocFdFu(1,:,gt2,:)+ZRUZDR(gt2,gt1)*AmpVertexHpTocFdFu(1,:,gt1,:) 
AmpWaveZHpTocFdFu(2,:,gt2,:) = AmpWaveZHpTocFdFu(2,:,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveHpTocFdFu(2,:,gt1,:) 
AmpVertexZHpTocFdFu(2,:,gt2,:)= AmpVertexZHpTocFdFu(2,:,gt2,:)+ZRUZDLc(gt2,gt1)*AmpVertexHpTocFdFu(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveHpTocFdFu=AmpWaveZHpTocFdFu 
AmpVertexHpTocFdFu= AmpVertexZHpTocFdFu
! Final State 2 
AmpWaveZHpTocFdFu=0._dp 
AmpVertexZHpTocFdFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZHpTocFdFu(1,:,:,gt2) = AmpWaveZHpTocFdFu(1,:,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveHpTocFdFu(1,:,:,gt1) 
AmpVertexZHpTocFdFu(1,:,:,gt2)= AmpVertexZHpTocFdFu(1,:,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexHpTocFdFu(1,:,:,gt1) 
AmpWaveZHpTocFdFu(2,:,:,gt2) = AmpWaveZHpTocFdFu(2,:,:,gt2)+ZRUZUR(gt2,gt1)*AmpWaveHpTocFdFu(2,:,:,gt1) 
AmpVertexZHpTocFdFu(2,:,:,gt2)= AmpVertexZHpTocFdFu(2,:,:,gt2)+ZRUZUR(gt2,gt1)*AmpVertexHpTocFdFu(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveHpTocFdFu=AmpWaveZHpTocFdFu 
AmpVertexHpTocFdFu= AmpVertexZHpTocFdFu
End if
If (ShiftIRdiv) Then 
AmpVertexHpTocFdFu = AmpVertexHpTocFdFu  +  AmpVertexIRosHpTocFdFu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->bar[Fd] Fu -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpTocFdFu = AmpTreeHpTocFdFu 
 AmpSum2HpTocFdFu = AmpTreeHpTocFdFu + 2._dp*AmpWaveHpTocFdFu + 2._dp*AmpVertexHpTocFdFu  
Else 
 AmpSumHpTocFdFu = AmpTreeHpTocFdFu + AmpWaveHpTocFdFu + AmpVertexHpTocFdFu
 AmpSum2HpTocFdFu = AmpTreeHpTocFdFu + AmpWaveHpTocFdFu + AmpVertexHpTocFdFu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpTocFdFu = AmpTreeHpTocFdFu
 AmpSum2HpTocFdFu = AmpTreeHpTocFdFu 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MFd(gt2))+Abs(MFu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2HpTocFdFu = AmpTreeHpTocFdFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFd(gt2),MFu(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpTocFdFu(gt1, gt2, gt3) 
  AmpSum2HpTocFdFu = 2._dp*AmpWaveHpTocFdFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFd(gt2),MFu(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpTocFdFu(gt1, gt2, gt3) 
  AmpSum2HpTocFdFu = 2._dp*AmpVertexHpTocFdFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFd(gt2),MFu(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpTocFdFu(gt1, gt2, gt3) 
  AmpSum2HpTocFdFu = AmpTreeHpTocFdFu + 2._dp*AmpWaveHpTocFdFu + 2._dp*AmpVertexHpTocFdFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFd(gt2),MFu(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpTocFdFu(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpTocFdFu = AmpTreeHpTocFdFu
  Call SquareAmp_StoFF(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
  AmpSqTreeHpTocFdFu(gt1, gt2, gt3) = AmpSqHpTocFdFu(gt1, gt2, gt3)  
  AmpSum2HpTocFdFu = + 2._dp*AmpWaveHpTocFdFu + 2._dp*AmpVertexHpTocFdFu
  Call SquareAmp_StoFF(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
  AmpSqHpTocFdFu(gt1, gt2, gt3) = AmpSqHpTocFdFu(gt1, gt2, gt3) + AmpSqTreeHpTocFdFu(gt1, gt2, gt3)  
Else  
  AmpSum2HpTocFdFu = AmpTreeHpTocFdFu
  Call SquareAmp_StoFF(MHp(gt1),MFd(gt2),MFu(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
  AmpSqTreeHpTocFdFu(gt1, gt2, gt3) = AmpSqHpTocFdFu(gt1, gt2, gt3)  
  AmpSum2HpTocFdFu = + 2._dp*AmpWaveHpTocFdFu + 2._dp*AmpVertexHpTocFdFu
  Call SquareAmp_StoFF(MHp(gt1),MFd(gt2),MFu(gt3),AmpSumHpTocFdFu(:,gt1, gt2, gt3),AmpSum2HpTocFdFu(:,gt1, gt2, gt3),AmpSqHpTocFdFu(gt1, gt2, gt3)) 
  AmpSqHpTocFdFu(gt1, gt2, gt3) = AmpSqHpTocFdFu(gt1, gt2, gt3) + AmpSqTreeHpTocFdFu(gt1, gt2, gt3)  
End if  
Else  
  AmpSqHpTocFdFu(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqHpTocFdFu(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 3._dp*GammaTPS(MHpOS(gt1),MFdOS(gt2),MFuOS(gt3),helfactor*AmpSqHpTocFdFu(gt1, gt2, gt3))
Else 
  gP1LHp(gt1,i4) = 3._dp*GammaTPS(MHp(gt1),MFd(gt2),MFu(gt3),helfactor*AmpSqHpTocFdFu(gt1, gt2, gt3))
End if 
If ((Abs(MRPHpTocFdFu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHpTocFdFu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpTocFdFu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHpTocFdFu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHpTocFdFu(gt1, gt2, gt3) + MRGHpTocFdFu(gt1, gt2, gt3)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHpTocFdFu(gt1, gt2, gt3) + MRGHpTocFdFu(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fe) Fv
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpTocFeFv(cplcFeFvcHpL,cplcFeFvcHpR,MFe,MHp,               & 
& MFe2,MHp2,AmpTreeHpTocFeFv)

  Else 
Call Amplitude_Tree_Inert2_HpTocFeFv(ZcplcFeFvcHpL,ZcplcFeFvcHpR,MFe,MHp,             & 
& MFe2,MHp2,AmpTreeHpTocFeFv)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpTocFeFv(MLambda,em,gs,cplcFeFvcHpL,cplcFeFvcHpR,             & 
& MFeOS,MHpOS,MRPHpTocFeFv,MRGHpTocFeFv)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpTocFeFv(MLambda,em,gs,ZcplcFeFvcHpL,ZcplcFeFvcHpR,           & 
& MFeOS,MHpOS,MRPHpTocFeFv,MRGHpTocFeFv)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpTocFeFv(MLambda,em,gs,cplcFeFvcHpL,cplcFeFvcHpR,             & 
& MFe,MHp,MRPHpTocFeFv,MRGHpTocFeFv)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpTocFeFv(MLambda,em,gs,ZcplcFeFvcHpL,ZcplcFeFvcHpR,           & 
& MFe,MHp,MRPHpTocFeFv,MRGHpTocFeFv)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpTocFeFv(cplcFeFvcHpL,cplcFeFvcHpR,ctcplcFeFvcHpL,        & 
& ctcplcFeFvcHpR,MFe,MFe2,MHp,MHp2,ZfEL,ZfER,ZfHp,ZfvL,AmpWaveHpTocFeFv)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpTocFeFv(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,MFe2,             & 
& MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexHpTocFeFv)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpTocFeFv(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0cHpVWp,         & 
& cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRdrHpTocFeFv)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFeFv(MFeOS,MG0OS,MhhOS,MHpOS,MVP,MVWpOS,         & 
& MVZOS,MFe2OS,MG02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplcFeFeG0L,cplcFeFeG0R,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,ZcplcFeFvcHpL,ZcplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,       & 
& cplG0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& AmpVertexIRosHpTocFeFv)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFeFv(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,ZcplcFeFvcHpL,ZcplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0cHpVWp,       & 
& cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRosHpTocFeFv)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFeFv(MFeOS,MG0OS,MhhOS,MHpOS,MVP,MVWpOS,         & 
& MVZOS,MFe2OS,MG02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplcFeFeG0L,cplcFeFeG0R,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,         & 
& cplG0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& AmpVertexIRosHpTocFeFv)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTocFeFv(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0cHpVWp,         & 
& cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRosHpTocFeFv)

 End if 
 End if 
AmpVertexHpTocFeFv = AmpVertexHpTocFeFv -  AmpVertexIRdrHpTocFeFv! +  AmpVertexIRosHpTocFeFv ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpTocFeFv=0._dp 
AmpVertexZHpTocFeFv=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpTocFeFv(:,gt2,:,:) = AmpWaveZHpTocFeFv(:,gt2,:,:)+ZRUZP(gt2,gt1)*AmpWaveHpTocFeFv(:,gt1,:,:) 
AmpVertexZHpTocFeFv(:,gt2,:,:)= AmpVertexZHpTocFeFv(:,gt2,:,:) + ZRUZP(gt2,gt1)*AmpVertexHpTocFeFv(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveHpTocFeFv=AmpWaveZHpTocFeFv 
AmpVertexHpTocFeFv= AmpVertexZHpTocFeFv
! Final State 1 
AmpWaveZHpTocFeFv=0._dp 
AmpVertexZHpTocFeFv=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZHpTocFeFv(1,:,gt2,:) = AmpWaveZHpTocFeFv(1,:,gt2,:)+ZRUZER(gt2,gt1)*AmpWaveHpTocFeFv(1,:,gt1,:) 
AmpVertexZHpTocFeFv(1,:,gt2,:)= AmpVertexZHpTocFeFv(1,:,gt2,:)+ZRUZER(gt2,gt1)*AmpVertexHpTocFeFv(1,:,gt1,:) 
AmpWaveZHpTocFeFv(2,:,gt2,:) = AmpWaveZHpTocFeFv(2,:,gt2,:)+ZRUZELc(gt2,gt1)*AmpWaveHpTocFeFv(2,:,gt1,:) 
AmpVertexZHpTocFeFv(2,:,gt2,:)= AmpVertexZHpTocFeFv(2,:,gt2,:)+ZRUZELc(gt2,gt1)*AmpVertexHpTocFeFv(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveHpTocFeFv=AmpWaveZHpTocFeFv 
AmpVertexHpTocFeFv= AmpVertexZHpTocFeFv
End if
If (ShiftIRdiv) Then 
AmpVertexHpTocFeFv = AmpVertexHpTocFeFv  +  AmpVertexIRosHpTocFeFv
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->bar[Fe] Fv -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpTocFeFv = AmpTreeHpTocFeFv 
 AmpSum2HpTocFeFv = AmpTreeHpTocFeFv + 2._dp*AmpWaveHpTocFeFv + 2._dp*AmpVertexHpTocFeFv  
Else 
 AmpSumHpTocFeFv = AmpTreeHpTocFeFv + AmpWaveHpTocFeFv + AmpVertexHpTocFeFv
 AmpSum2HpTocFeFv = AmpTreeHpTocFeFv + AmpWaveHpTocFeFv + AmpVertexHpTocFeFv 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpTocFeFv = AmpTreeHpTocFeFv
 AmpSum2HpTocFeFv = AmpTreeHpTocFeFv 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MFe(gt2))+Abs(0._dp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2HpTocFeFv = AmpTreeHpTocFeFv
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFeOS(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFe(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpTocFeFv(gt1, gt2, gt3) 
  AmpSum2HpTocFeFv = 2._dp*AmpWaveHpTocFeFv
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFeOS(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFe(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpTocFeFv(gt1, gt2, gt3) 
  AmpSum2HpTocFeFv = 2._dp*AmpVertexHpTocFeFv
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFeOS(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFe(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpTocFeFv(gt1, gt2, gt3) 
  AmpSum2HpTocFeFv = AmpTreeHpTocFeFv + 2._dp*AmpWaveHpTocFeFv + 2._dp*AmpVertexHpTocFeFv
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHpOS(gt1),MFeOS(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHp(gt1),MFe(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpTocFeFv(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpTocFeFv = AmpTreeHpTocFeFv
  Call SquareAmp_StoFF(MHpOS(gt1),MFeOS(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
  AmpSqTreeHpTocFeFv(gt1, gt2, gt3) = AmpSqHpTocFeFv(gt1, gt2, gt3)  
  AmpSum2HpTocFeFv = + 2._dp*AmpWaveHpTocFeFv + 2._dp*AmpVertexHpTocFeFv
  Call SquareAmp_StoFF(MHpOS(gt1),MFeOS(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
  AmpSqHpTocFeFv(gt1, gt2, gt3) = AmpSqHpTocFeFv(gt1, gt2, gt3) + AmpSqTreeHpTocFeFv(gt1, gt2, gt3)  
Else  
  AmpSum2HpTocFeFv = AmpTreeHpTocFeFv
  Call SquareAmp_StoFF(MHp(gt1),MFe(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
  AmpSqTreeHpTocFeFv(gt1, gt2, gt3) = AmpSqHpTocFeFv(gt1, gt2, gt3)  
  AmpSum2HpTocFeFv = + 2._dp*AmpWaveHpTocFeFv + 2._dp*AmpVertexHpTocFeFv
  Call SquareAmp_StoFF(MHp(gt1),MFe(gt2),0._dp,AmpSumHpTocFeFv(:,gt1, gt2, gt3),AmpSum2HpTocFeFv(:,gt1, gt2, gt3),AmpSqHpTocFeFv(gt1, gt2, gt3)) 
  AmpSqHpTocFeFv(gt1, gt2, gt3) = AmpSqHpTocFeFv(gt1, gt2, gt3) + AmpSqTreeHpTocFeFv(gt1, gt2, gt3)  
End if  
Else  
  AmpSqHpTocFeFv(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqHpTocFeFv(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MFeOS(gt2),0._dp,helfactor*AmpSqHpTocFeFv(gt1, gt2, gt3))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MFe(gt2),0._dp,helfactor*AmpSqHpTocFeFv(gt1, gt2, gt3))
End if 
If ((Abs(MRPHpTocFeFv(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHpTocFeFv(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpTocFeFv(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHpTocFeFv(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHpTocFeFv(gt1, gt2, gt3) + MRGHpTocFeFv(gt1, gt2, gt3)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHpTocFeFv(gt1, gt2, gt3) + MRGHpTocFeFv(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Hp H0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToHpH0(cplH0HpcHp,MH0,MHp,MH02,MHp2,AmpTreeHpToHpH0)

  Else 
Call Amplitude_Tree_Inert2_HpToHpH0(ZcplH0HpcHp,MH0,MHp,MH02,MHp2,AmpTreeHpToHpH0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToHpH0(MLambda,em,gs,cplH0HpcHp,MH0OS,MHpOS,MRPHpToHpH0,     & 
& MRGHpToHpH0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToHpH0(MLambda,em,gs,ZcplH0HpcHp,MH0OS,MHpOS,MRPHpToHpH0,    & 
& MRGHpToHpH0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToHpH0(MLambda,em,gs,cplH0HpcHp,MH0,MHp,MRPHpToHpH0,         & 
& MRGHpToHpH0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToHpH0(MLambda,em,gs,ZcplH0HpcHp,MH0,MHp,MRPHpToHpH0,        & 
& MRGHpToHpH0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToHpH0(cplH0HpcHp,ctcplH0HpcHp,MH0,MH02,MHp,             & 
& MHp2,ZfH0,ZfHp,AmpWaveHpToHpH0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToHpH0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,            & 
& cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,               & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexHpToHpH0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToHpH0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,            & 
& cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,               & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexIRdrHpToHpH0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpH0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,ZcplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,      & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,     & 
& cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,            & 
& AmpVertexIRosHpToHpH0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpH0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,ZcplH0HpcHp,       & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,            & 
& cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,               & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexIRosHpToHpH0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpH0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,            & 
& cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,       & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,     & 
& cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,     & 
& cplH0HpcVWpVP1,cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,            & 
& AmpVertexIRosHpToHpH0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpH0(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,            & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0H0H0,cplG0HpcVWp,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,        & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0G0HpcHp1,cplA0hhHpcHp1,            & 
& cplG0H0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplH0HpcVWpVP1,cplH0HpcVWpVZ1,               & 
& cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpHpcHpcHp1,AmpVertexIRosHpToHpH0)

 End if 
 End if 
AmpVertexHpToHpH0 = AmpVertexHpToHpH0 -  AmpVertexIRdrHpToHpH0! +  AmpVertexIRosHpToHpH0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToHpH0=0._dp 
AmpVertexZHpToHpH0=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHpH0(gt2,:) = AmpWaveZHpToHpH0(gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHpToHpH0(gt1,:) 
AmpVertexZHpToHpH0(gt2,:)= AmpVertexZHpToHpH0(gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHpToHpH0(gt1,:) 
 End Do 
End Do 
AmpWaveHpToHpH0=AmpWaveZHpToHpH0 
AmpVertexHpToHpH0= AmpVertexZHpToHpH0
! Final State 1 
AmpWaveZHpToHpH0=0._dp 
AmpVertexZHpToHpH0=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHpH0(:,gt2) = AmpWaveZHpToHpH0(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToHpH0(:,gt1) 
AmpVertexZHpToHpH0(:,gt2)= AmpVertexZHpToHpH0(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexHpToHpH0(:,gt1) 
 End Do 
End Do 
AmpWaveHpToHpH0=AmpWaveZHpToHpH0 
AmpVertexHpToHpH0= AmpVertexZHpToHpH0
End if
If (ShiftIRdiv) Then 
AmpVertexHpToHpH0 = AmpVertexHpToHpH0  +  AmpVertexIRosHpToHpH0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->Hp H0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToHpH0 = AmpTreeHpToHpH0 
 AmpSum2HpToHpH0 = AmpTreeHpToHpH0 + 2._dp*AmpWaveHpToHpH0 + 2._dp*AmpVertexHpToHpH0  
Else 
 AmpSumHpToHpH0 = AmpTreeHpToHpH0 + AmpWaveHpToHpH0 + AmpVertexHpToHpH0
 AmpSum2HpToHpH0 = AmpTreeHpToHpH0 + AmpWaveHpToHpH0 + AmpVertexHpToHpH0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToHpH0 = AmpTreeHpToHpH0
 AmpSum2HpToHpH0 = AmpTreeHpToHpH0 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MHpOS(gt2))+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MHp(gt2))+Abs(MH0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HpToHpH0 = AmpTreeHpToHpH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MH0OS,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MH0,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToHpH0(gt1, gt2) 
  AmpSum2HpToHpH0 = 2._dp*AmpWaveHpToHpH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MH0OS,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MH0,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToHpH0(gt1, gt2) 
  AmpSum2HpToHpH0 = 2._dp*AmpVertexHpToHpH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MH0OS,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MH0,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToHpH0(gt1, gt2) 
  AmpSum2HpToHpH0 = AmpTreeHpToHpH0 + 2._dp*AmpWaveHpToHpH0 + 2._dp*AmpVertexHpToHpH0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MH0OS,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MH0,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToHpH0(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToHpH0 = AmpTreeHpToHpH0
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MH0OS,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
  AmpSqTreeHpToHpH0(gt1, gt2) = AmpSqHpToHpH0(gt1, gt2)  
  AmpSum2HpToHpH0 = + 2._dp*AmpWaveHpToHpH0 + 2._dp*AmpVertexHpToHpH0
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MH0OS,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
  AmpSqHpToHpH0(gt1, gt2) = AmpSqHpToHpH0(gt1, gt2) + AmpSqTreeHpToHpH0(gt1, gt2)  
Else  
  AmpSum2HpToHpH0 = AmpTreeHpToHpH0
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MH0,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
  AmpSqTreeHpToHpH0(gt1, gt2) = AmpSqHpToHpH0(gt1, gt2)  
  AmpSum2HpToHpH0 = + 2._dp*AmpWaveHpToHpH0 + 2._dp*AmpVertexHpToHpH0
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),MH0,AmpSumHpToHpH0(gt1, gt2),AmpSum2HpToHpH0(gt1, gt2),AmpSqHpToHpH0(gt1, gt2)) 
  AmpSqHpToHpH0(gt1, gt2) = AmpSqHpToHpH0(gt1, gt2) + AmpSqTreeHpToHpH0(gt1, gt2)  
End if  
Else  
  AmpSqHpToHpH0(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToHpH0(gt1, gt2).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MHpOS(gt2),MH0OS,helfactor*AmpSqHpToHpH0(gt1, gt2))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MHp(gt2),MH0,helfactor*AmpSqHpToHpH0(gt1, gt2))
End if 
If ((Abs(MRPHpToHpH0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpH0(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToHpH0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpH0(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHpToHpH0(gt1, gt2) + MRGHpToHpH0(gt1, gt2)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHpToHpH0(gt1, gt2) + MRGHpToHpH0(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! H0 VWp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToH0VWp(cplH0cHpVWp,MH0,MHp,MVWp,MH02,MHp2,              & 
& MVWp2,AmpTreeHpToH0VWp)

  Else 
Call Amplitude_Tree_Inert2_HpToH0VWp(ZcplH0cHpVWp,MH0,MHp,MVWp,MH02,MHp2,             & 
& MVWp2,AmpTreeHpToH0VWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToH0VWp(MLambda,em,gs,cplH0cHpVWp,MH0OS,MHpOS,               & 
& MVWpOS,MRPHpToH0VWp,MRGHpToH0VWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToH0VWp(MLambda,em,gs,ZcplH0cHpVWp,MH0OS,MHpOS,              & 
& MVWpOS,MRPHpToH0VWp,MRGHpToH0VWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToH0VWp(MLambda,em,gs,cplH0cHpVWp,MH0,MHp,MVWp,              & 
& MRPHpToH0VWp,MRGHpToH0VWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToH0VWp(MLambda,em,gs,ZcplH0cHpVWp,MH0,MHp,MVWp,             & 
& MRPHpToH0VWp,MRGHpToH0VWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToH0VWp(cplH0cHpVWp,ctcplH0cHpVWp,MH0,MH02,              & 
& MHp,MHp2,MVWp,MVWp2,ZfH0,ZfHp,ZfVWp,AmpWaveHpToH0VWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToH0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,MVZ,              & 
& MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,     & 
& cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,        & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,    & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1, & 
& cplHpcHpcVWpVWp1,AmpVertexHpToH0VWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToH0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRdrHpToH0VWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToH0VWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,            & 
& cplH0H0hh,GosZcplH0HpcHp,cplH0HpcVWp,ZcplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,              & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,GosZcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,           & 
& cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,             & 
& cplHpcHpcVWpVWp1,AmpVertexIRosHpToH0VWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToH0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,cplH0H0hh,GZcplH0HpcHp,cplH0HpcVWp,       & 
& ZcplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,GZcplcHpVPVWp,  & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpToH0VWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToH0VWp(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,              & 
& MVP,MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,               & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,            & 
& cplH0H0hh,GcplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,     & 
& cplHpcHpVP,cplHpcHpVZ,GcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,              & 
& cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRosHpToH0VWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToH0VWp(MA0,MG0,MH0,Mhh,MHp,MVP,MVWp,               & 
& MVZ,MA02,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0G0H0,cplA0H0hh,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0cHpVWp,cplG0H0H0,cplG0cHpVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,         & 
& cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0cHpVPVWp1,   & 
& cplH0cHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpToH0VWp)

 End if 
 End if 
AmpVertexHpToH0VWp = AmpVertexHpToH0VWp -  AmpVertexIRdrHpToH0VWp! +  AmpVertexIRosHpToH0VWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToH0VWp=0._dp 
AmpVertexZHpToH0VWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToH0VWp(:,gt2) = AmpWaveZHpToH0VWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToH0VWp(:,gt1) 
AmpVertexZHpToH0VWp(:,gt2)= AmpVertexZHpToH0VWp(:,gt2) + ZRUZP(gt2,gt1)*AmpVertexHpToH0VWp(:,gt1) 
 End Do 
End Do 
AmpWaveHpToH0VWp=AmpWaveZHpToH0VWp 
AmpVertexHpToH0VWp= AmpVertexZHpToH0VWp
End if
If (ShiftIRdiv) Then 
AmpVertexHpToH0VWp = AmpVertexHpToH0VWp  +  AmpVertexIRosHpToH0VWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->H0 VWp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToH0VWp = AmpTreeHpToH0VWp 
 AmpSum2HpToH0VWp = AmpTreeHpToH0VWp + 2._dp*AmpWaveHpToH0VWp + 2._dp*AmpVertexHpToH0VWp  
Else 
 AmpSumHpToH0VWp = AmpTreeHpToH0VWp + AmpWaveHpToH0VWp + AmpVertexHpToH0VWp
 AmpSum2HpToH0VWp = AmpTreeHpToH0VWp + AmpWaveHpToH0VWp + AmpVertexHpToH0VWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToH0VWp = AmpTreeHpToH0VWp
 AmpSum2HpToH0VWp = AmpTreeHpToH0VWp 
End if 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MH0OS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MH0)+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2HpToH0VWp = AmpTreeHpToH0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MH0OS,MVWpOS,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MH0,MVWp,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToH0VWp(gt1) 
  AmpSum2HpToH0VWp = 2._dp*AmpWaveHpToH0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MH0OS,MVWpOS,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MH0,MVWp,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToH0VWp(gt1) 
  AmpSum2HpToH0VWp = 2._dp*AmpVertexHpToH0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MH0OS,MVWpOS,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MH0,MVWp,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToH0VWp(gt1) 
  AmpSum2HpToH0VWp = AmpTreeHpToH0VWp + 2._dp*AmpWaveHpToH0VWp + 2._dp*AmpVertexHpToH0VWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MH0OS,MVWpOS,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MH0,MVWp,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToH0VWp(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToH0VWp = AmpTreeHpToH0VWp
  Call SquareAmp_StoSV(MHpOS(gt1),MH0OS,MVWpOS,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
  AmpSqTreeHpToH0VWp(gt1) = AmpSqHpToH0VWp(gt1)  
  AmpSum2HpToH0VWp = + 2._dp*AmpWaveHpToH0VWp + 2._dp*AmpVertexHpToH0VWp
  Call SquareAmp_StoSV(MHpOS(gt1),MH0OS,MVWpOS,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
  AmpSqHpToH0VWp(gt1) = AmpSqHpToH0VWp(gt1) + AmpSqTreeHpToH0VWp(gt1)  
Else  
  AmpSum2HpToH0VWp = AmpTreeHpToH0VWp
  Call SquareAmp_StoSV(MHp(gt1),MH0,MVWp,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
  AmpSqTreeHpToH0VWp(gt1) = AmpSqHpToH0VWp(gt1)  
  AmpSum2HpToH0VWp = + 2._dp*AmpWaveHpToH0VWp + 2._dp*AmpVertexHpToH0VWp
  Call SquareAmp_StoSV(MHp(gt1),MH0,MVWp,AmpSumHpToH0VWp(:,gt1),AmpSum2HpToH0VWp(:,gt1),AmpSqHpToH0VWp(gt1)) 
  AmpSqHpToH0VWp(gt1) = AmpSqHpToH0VWp(gt1) + AmpSqTreeHpToH0VWp(gt1)  
End if  
Else  
  AmpSqHpToH0VWp(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToH0VWp(gt1).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MH0OS,MVWpOS,helfactor*AmpSqHpToH0VWp(gt1))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MH0,MVWp,helfactor*AmpSqHpToH0VWp(gt1))
End if 
If ((Abs(MRPHpToH0VWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToH0VWp(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToH0VWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToH0VWp(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHpToH0VWp(gt1) + MRGHpToH0VWp(gt1)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHpToH0VWp(gt1) + MRGHpToH0VWp(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Hp hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToHphh(cplhhHpcHp,Mhh,MHp,Mhh2,MHp2,AmpTreeHpToHphh)

  Else 
Call Amplitude_Tree_Inert2_HpToHphh(ZcplhhHpcHp,Mhh,MHp,Mhh2,MHp2,AmpTreeHpToHphh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToHphh(MLambda,em,gs,cplhhHpcHp,MhhOS,MHpOS,MRPHpToHphh,     & 
& MRGHpToHphh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToHphh(MLambda,em,gs,ZcplhhHpcHp,MhhOS,MHpOS,MRPHpToHphh,    & 
& MRGHpToHphh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToHphh(MLambda,em,gs,cplhhHpcHp,Mhh,MHp,MRPHpToHphh,         & 
& MRGHpToHphh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToHphh(MLambda,em,gs,ZcplhhHpcHp,Mhh,MHp,MRPHpToHphh,        & 
& MRGHpToHphh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToHphh(cplhhHpcHp,ctcplhhHpcHp,Mhh,Mhh2,MHp,             & 
& MHp2,Zfhh,ZfHp,AmpWaveHpToHphh)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToHphh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,MVP,            & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,            & 
& cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,      & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,             & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,              & 
& cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,       & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,   & 
& cplA0hhHpcHp1,cplG0G0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,  & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,          & 
& cplHpcHpVZVZ1,AmpVertexHpToHphh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToHphh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,      & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,             & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,              & 
& cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,       & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,   & 
& cplA0hhHpcHp1,cplG0G0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,  & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,          & 
& cplHpcHpVZVZ1,AmpVertexIRdrHpToHphh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHphh(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,          & 
& cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,              & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,    & 
& cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,             & 
& cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,ZcplhhHpcHp,       & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0hhHpcHp1,cplG0G0HpcHp1,         & 
& cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,               & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,           & 
& AmpVertexIRosHpToHphh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHphh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,      & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,             & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,              & 
& cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhhhhh,ZcplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,      & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,   & 
& cplA0hhHpcHp1,cplG0G0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,  & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,          & 
& cplHpcHpVZVZ1,AmpVertexIRosHpToHphh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHphh(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,          & 
& cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,              & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,    & 
& cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,             & 
& cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,        & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,cplA0hhHpcHp1,cplG0G0HpcHp1,         & 
& cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,               & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,           & 
& AmpVertexIRosHpToHphh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHphh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,      & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0G0hh,             & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,              & 
& cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,      & 
& cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,       & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0HpcHp1,   & 
& cplA0hhHpcHp1,cplG0G0HpcHp1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhHpcHp1,cplhhHpcVWpVP1,  & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpHpcHpcHp1,cplHpcHpcVWpVWp1,          & 
& cplHpcHpVZVZ1,AmpVertexIRosHpToHphh)

 End if 
 End if 
AmpVertexHpToHphh = AmpVertexHpToHphh -  AmpVertexIRdrHpToHphh! +  AmpVertexIRosHpToHphh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToHphh=0._dp 
AmpVertexZHpToHphh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHphh(gt2,:) = AmpWaveZHpToHphh(gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHpToHphh(gt1,:) 
AmpVertexZHpToHphh(gt2,:)= AmpVertexZHpToHphh(gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHpToHphh(gt1,:) 
 End Do 
End Do 
AmpWaveHpToHphh=AmpWaveZHpToHphh 
AmpVertexHpToHphh= AmpVertexZHpToHphh
! Final State 1 
AmpWaveZHpToHphh=0._dp 
AmpVertexZHpToHphh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHphh(:,gt2) = AmpWaveZHpToHphh(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToHphh(:,gt1) 
AmpVertexZHpToHphh(:,gt2)= AmpVertexZHpToHphh(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexHpToHphh(:,gt1) 
 End Do 
End Do 
AmpWaveHpToHphh=AmpWaveZHpToHphh 
AmpVertexHpToHphh= AmpVertexZHpToHphh
End if
If (ShiftIRdiv) Then 
AmpVertexHpToHphh = AmpVertexHpToHphh  +  AmpVertexIRosHpToHphh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->Hp hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToHphh = AmpTreeHpToHphh 
 AmpSum2HpToHphh = AmpTreeHpToHphh + 2._dp*AmpWaveHpToHphh + 2._dp*AmpVertexHpToHphh  
Else 
 AmpSumHpToHphh = AmpTreeHpToHphh + AmpWaveHpToHphh + AmpVertexHpToHphh
 AmpSum2HpToHphh = AmpTreeHpToHphh + AmpWaveHpToHphh + AmpVertexHpToHphh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToHphh = AmpTreeHpToHphh
 AmpSum2HpToHphh = AmpTreeHpToHphh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MHpOS(gt2))+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MHp(gt2))+Abs(Mhh))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HpToHphh = AmpTreeHpToHphh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MhhOS,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),Mhh,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToHphh(gt1, gt2) 
  AmpSum2HpToHphh = 2._dp*AmpWaveHpToHphh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MhhOS,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),Mhh,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToHphh(gt1, gt2) 
  AmpSum2HpToHphh = 2._dp*AmpVertexHpToHphh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MhhOS,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),Mhh,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToHphh(gt1, gt2) 
  AmpSum2HpToHphh = AmpTreeHpToHphh + 2._dp*AmpWaveHpToHphh + 2._dp*AmpVertexHpToHphh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MhhOS,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
Else  
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),Mhh,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToHphh(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToHphh = AmpTreeHpToHphh
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MhhOS,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
  AmpSqTreeHpToHphh(gt1, gt2) = AmpSqHpToHphh(gt1, gt2)  
  AmpSum2HpToHphh = + 2._dp*AmpWaveHpToHphh + 2._dp*AmpVertexHpToHphh
  Call SquareAmp_StoSS(MHpOS(gt1),MHpOS(gt2),MhhOS,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
  AmpSqHpToHphh(gt1, gt2) = AmpSqHpToHphh(gt1, gt2) + AmpSqTreeHpToHphh(gt1, gt2)  
Else  
  AmpSum2HpToHphh = AmpTreeHpToHphh
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),Mhh,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
  AmpSqTreeHpToHphh(gt1, gt2) = AmpSqHpToHphh(gt1, gt2)  
  AmpSum2HpToHphh = + 2._dp*AmpWaveHpToHphh + 2._dp*AmpVertexHpToHphh
  Call SquareAmp_StoSS(MHp(gt1),MHp(gt2),Mhh,AmpSumHpToHphh(gt1, gt2),AmpSum2HpToHphh(gt1, gt2),AmpSqHpToHphh(gt1, gt2)) 
  AmpSqHpToHphh(gt1, gt2) = AmpSqHpToHphh(gt1, gt2) + AmpSqTreeHpToHphh(gt1, gt2)  
End if  
Else  
  AmpSqHpToHphh(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToHphh(gt1, gt2).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MHpOS(gt2),MhhOS,helfactor*AmpSqHpToHphh(gt1, gt2))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MHp(gt2),Mhh,helfactor*AmpSqHpToHphh(gt1, gt2))
End if 
If ((Abs(MRPHpToHphh(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHphh(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToHphh(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHphh(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHpToHphh(gt1, gt2) + MRGHpToHphh(gt1, gt2)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHpToHphh(gt1, gt2) + MRGHpToHphh(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh VWp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpTohhVWp(cplhhcHpVWp,Mhh,MHp,MVWp,Mhh2,MHp2,              & 
& MVWp2,AmpTreeHpTohhVWp)

  Else 
Call Amplitude_Tree_Inert2_HpTohhVWp(ZcplhhcHpVWp,Mhh,MHp,MVWp,Mhh2,MHp2,             & 
& MVWp2,AmpTreeHpTohhVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpTohhVWp(MLambda,em,gs,cplhhcHpVWp,MhhOS,MHpOS,               & 
& MVWpOS,MRPHpTohhVWp,MRGHpTohhVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpTohhVWp(MLambda,em,gs,ZcplhhcHpVWp,MhhOS,MHpOS,              & 
& MVWpOS,MRPHpTohhVWp,MRGHpTohhVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpTohhVWp(MLambda,em,gs,cplhhcHpVWp,Mhh,MHp,MVWp,              & 
& MRPHpTohhVWp,MRGHpTohhVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpTohhVWp(MLambda,em,gs,ZcplhhcHpVWp,Mhh,MHp,MVWp,             & 
& MRPHpTohhVWp,MRGHpTohhVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpTohhVWp(cplhhcHpVWp,ctcplhhcHpVWp,Mhh,Mhh2,              & 
& MHp,MHp2,MVWp,MVWp2,Zfhh,ZfHp,ZfVWp,AmpWaveHpTohhVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpTohhVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,               & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,             & 
& cplcgZgAhh,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgAgWCVWp,           & 
& cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,    & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,        & 
& cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0cHpVWpVZ1,           & 
& cplhhhhcVWpVWp1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexHpTohhVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpTohhVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,             & 
& cplcgZgAhh,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgAgWCVWp,           & 
& cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,    & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,        & 
& cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0cHpVWpVZ1,           & 
& cplhhhhcVWpVWp1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRdrHpTohhVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTohhVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,              & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,          & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,           & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,cplcgZgAhh,cplcgWCgAcHp,               & 
& cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,           & 
& cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,cplhhhhhh,GosZcplhhHpcHp,   & 
& cplhhHpcVWp,ZcplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,GosZcplcHpVPVWp, & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0cHpVWpVZ1,cplhhhhcVWpVWp1,cplhhcHpVPVWp1,   & 
& cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpTohhVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTohhVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,             & 
& cplcgZgAhh,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgAgWCVWp,           & 
& cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,    & 
& cplhhhhhh,GZcplhhHpcHp,cplhhHpcVWp,ZcplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,     & 
& cplHpcHpVZ,GZcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0cHpVWpVZ1,         & 
& cplhhhhcVWpVWp1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpTohhVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTohhVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,              & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,          & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,           & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,cplcgZgAhh,cplcgWCgAcHp,               & 
& cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,           & 
& cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,cplhhhhhh,GcplhhHpcHp,      & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,GcplcHpVPVWp,     & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0cHpVWpVZ1,cplhhhhcVWpVWp1,cplhhcHpVPVWp1,   & 
& cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpTohhVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpTohhVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,             & 
& cplcgZgAhh,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,cplcgWCgWChh,cplcgAgWCVWp,           & 
& cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcHp,cplH0H0hh,cplH0HpcHp,cplH0cHpVWp,    & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,        & 
& cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplG0cHpVWpVZ1,           & 
& cplhhhhcVWpVWp1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRosHpTohhVWp)

 End if 
 End if 
AmpVertexHpTohhVWp = AmpVertexHpTohhVWp -  AmpVertexIRdrHpTohhVWp! +  AmpVertexIRosHpTohhVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpTohhVWp=0._dp 
AmpVertexZHpTohhVWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpTohhVWp(:,gt2) = AmpWaveZHpTohhVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpTohhVWp(:,gt1) 
AmpVertexZHpTohhVWp(:,gt2)= AmpVertexZHpTohhVWp(:,gt2) + ZRUZP(gt2,gt1)*AmpVertexHpTohhVWp(:,gt1) 
 End Do 
End Do 
AmpWaveHpTohhVWp=AmpWaveZHpTohhVWp 
AmpVertexHpTohhVWp= AmpVertexZHpTohhVWp
End if
If (ShiftIRdiv) Then 
AmpVertexHpTohhVWp = AmpVertexHpTohhVWp  +  AmpVertexIRosHpTohhVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->hh VWp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpTohhVWp = AmpTreeHpTohhVWp 
 AmpSum2HpTohhVWp = AmpTreeHpTohhVWp + 2._dp*AmpWaveHpTohhVWp + 2._dp*AmpVertexHpTohhVWp  
Else 
 AmpSumHpTohhVWp = AmpTreeHpTohhVWp + AmpWaveHpTohhVWp + AmpVertexHpTohhVWp
 AmpSum2HpTohhVWp = AmpTreeHpTohhVWp + AmpWaveHpTohhVWp + AmpVertexHpTohhVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpTohhVWp = AmpTreeHpTohhVWp
 AmpSum2HpTohhVWp = AmpTreeHpTohhVWp 
End if 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MhhOS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(Mhh)+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2HpTohhVWp = AmpTreeHpTohhVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MhhOS,MVWpOS,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),Mhh,MVWp,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpTohhVWp(gt1) 
  AmpSum2HpTohhVWp = 2._dp*AmpWaveHpTohhVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MhhOS,MVWpOS,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),Mhh,MVWp,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpTohhVWp(gt1) 
  AmpSum2HpTohhVWp = 2._dp*AmpVertexHpTohhVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MhhOS,MVWpOS,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),Mhh,MVWp,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpTohhVWp(gt1) 
  AmpSum2HpTohhVWp = AmpTreeHpTohhVWp + 2._dp*AmpWaveHpTohhVWp + 2._dp*AmpVertexHpTohhVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MhhOS,MVWpOS,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),Mhh,MVWp,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpTohhVWp(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpTohhVWp = AmpTreeHpTohhVWp
  Call SquareAmp_StoSV(MHpOS(gt1),MhhOS,MVWpOS,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
  AmpSqTreeHpTohhVWp(gt1) = AmpSqHpTohhVWp(gt1)  
  AmpSum2HpTohhVWp = + 2._dp*AmpWaveHpTohhVWp + 2._dp*AmpVertexHpTohhVWp
  Call SquareAmp_StoSV(MHpOS(gt1),MhhOS,MVWpOS,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
  AmpSqHpTohhVWp(gt1) = AmpSqHpTohhVWp(gt1) + AmpSqTreeHpTohhVWp(gt1)  
Else  
  AmpSum2HpTohhVWp = AmpTreeHpTohhVWp
  Call SquareAmp_StoSV(MHp(gt1),Mhh,MVWp,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
  AmpSqTreeHpTohhVWp(gt1) = AmpSqHpTohhVWp(gt1)  
  AmpSum2HpTohhVWp = + 2._dp*AmpWaveHpTohhVWp + 2._dp*AmpVertexHpTohhVWp
  Call SquareAmp_StoSV(MHp(gt1),Mhh,MVWp,AmpSumHpTohhVWp(:,gt1),AmpSum2HpTohhVWp(:,gt1),AmpSqHpTohhVWp(gt1)) 
  AmpSqHpTohhVWp(gt1) = AmpSqHpTohhVWp(gt1) + AmpSqTreeHpTohhVWp(gt1)  
End if  
Else  
  AmpSqHpTohhVWp(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpTohhVWp(gt1).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MhhOS,MVWpOS,helfactor*AmpSqHpTohhVWp(gt1))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),Mhh,MVWp,helfactor*AmpSqHpTohhVWp(gt1))
End if 
If ((Abs(MRPHpTohhVWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpTohhVWp(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpTohhVWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpTohhVWp(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHpTohhVWp(gt1) + MRGHpTohhVWp(gt1)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHpTohhVWp(gt1) + MRGHpTohhVWp(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Hp VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToHpVZ(cplHpcHpVZ,MHp,MVZ,MHp2,MVZ2,AmpTreeHpToHpVZ)

  Else 
Call Amplitude_Tree_Inert2_HpToHpVZ(ZcplHpcHpVZ,MHp,MVZ,MHp2,MVZ2,AmpTreeHpToHpVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToHpVZ(MLambda,em,gs,cplHpcHpVZ,MHpOS,MVZOS,MRPHpToHpVZ,     & 
& MRGHpToHpVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToHpVZ(MLambda,em,gs,ZcplHpcHpVZ,MHpOS,MVZOS,MRPHpToHpVZ,    & 
& MRGHpToHpVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToHpVZ(MLambda,em,gs,cplHpcHpVZ,MHp,MVZ,MRPHpToHpVZ,         & 
& MRGHpToHpVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToHpVZ(MLambda,em,gs,ZcplHpcHpVZ,MHp,MVZ,MRPHpToHpVZ,        & 
& MRGHpToHpVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToHpVZ(cplHpcHpVP,cplHpcHpVZ,ctcplHpcHpVP,               & 
& ctcplHpcHpVZ,MHp,MHp2,MVP,MVP2,MVZ,MVZ2,ZfHp,ZfVPVZ,ZfVZ,AmpWaveHpToHpVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToHpVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,MVP,            & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,            & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgZgWCHp,               & 
& cplcgWCgWCVZ,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,              & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,        & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,        & 
& cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,            & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpVZVZ1,AmpVertexHpToHpVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToHpVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgZgWCHp,               & 
& cplcgWCgWCVZ,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,              & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,        & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,        & 
& cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,            & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpVZVZ1,AmpVertexIRdrHpToHpVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpVZ(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,        & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,cplcFdFdVZR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0HpcVWp,               & 
& cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgZgWCHp,cplcgWCgWCVZ,cplcgWpgZHp,            & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,    & 
& cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,ZcplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,              & 
& cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,             & 
& cplHpcHpVZVZ1,AmpVertexIRosHpToHpVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgZgWCHp,               & 
& cplcgWCgWCVZ,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,              & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,ZcplHpcHpVZ,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,        & 
& cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,            & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpVZVZ1,AmpVertexIRosHpToHpVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpVZ(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,        & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,cplcFdFdVZR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0HpcVWp,               & 
& cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgZgWCHp,cplcgWCgWCVZ,cplcgWpgZHp,            & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,    & 
& cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,       & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,              & 
& cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,             & 
& cplHpcHpVZVZ1,AmpVertexIRosHpToHpVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToHpVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgZgWCHp,               & 
& cplcgWCgWCVZ,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,              & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,        & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,        & 
& cplG0HpcVWpVZ1,cplG0cHpVWpVZ1,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,            & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpVZVZ1,AmpVertexIRosHpToHpVZ)

 End if 
 End if 
AmpVertexHpToHpVZ = AmpVertexHpToHpVZ -  AmpVertexIRdrHpToHpVZ! +  AmpVertexIRosHpToHpVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToHpVZ=0._dp 
AmpVertexZHpToHpVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHpVZ(:,gt2,:) = AmpWaveZHpToHpVZ(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHpToHpVZ(:,gt1,:) 
AmpVertexZHpToHpVZ(:,gt2,:)= AmpVertexZHpToHpVZ(:,gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHpToHpVZ(:,gt1,:) 
 End Do 
End Do 
AmpWaveHpToHpVZ=AmpWaveZHpToHpVZ 
AmpVertexHpToHpVZ= AmpVertexZHpToHpVZ
! Final State 1 
AmpWaveZHpToHpVZ=0._dp 
AmpVertexZHpToHpVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToHpVZ(:,:,gt2) = AmpWaveZHpToHpVZ(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToHpVZ(:,:,gt1) 
AmpVertexZHpToHpVZ(:,:,gt2)= AmpVertexZHpToHpVZ(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexHpToHpVZ(:,:,gt1) 
 End Do 
End Do 
AmpWaveHpToHpVZ=AmpWaveZHpToHpVZ 
AmpVertexHpToHpVZ= AmpVertexZHpToHpVZ
End if
If (ShiftIRdiv) Then 
AmpVertexHpToHpVZ = AmpVertexHpToHpVZ  +  AmpVertexIRosHpToHpVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->Hp VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToHpVZ = AmpTreeHpToHpVZ 
 AmpSum2HpToHpVZ = AmpTreeHpToHpVZ + 2._dp*AmpWaveHpToHpVZ + 2._dp*AmpVertexHpToHpVZ  
Else 
 AmpSumHpToHpVZ = AmpTreeHpToHpVZ + AmpWaveHpToHpVZ + AmpVertexHpToHpVZ
 AmpSum2HpToHpVZ = AmpTreeHpToHpVZ + AmpWaveHpToHpVZ + AmpVertexHpToHpVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToHpVZ = AmpTreeHpToHpVZ
 AmpSum2HpToHpVZ = AmpTreeHpToHpVZ 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MHpOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MHp(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HpToHpVZ = AmpTreeHpToHpVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),MVZOS,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVZ,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToHpVZ(gt1, gt2) 
  AmpSum2HpToHpVZ = 2._dp*AmpWaveHpToHpVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),MVZOS,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVZ,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToHpVZ(gt1, gt2) 
  AmpSum2HpToHpVZ = 2._dp*AmpVertexHpToHpVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),MVZOS,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVZ,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToHpVZ(gt1, gt2) 
  AmpSum2HpToHpVZ = AmpTreeHpToHpVZ + 2._dp*AmpWaveHpToHpVZ + 2._dp*AmpVertexHpToHpVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),MVZOS,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVZ,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToHpVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToHpVZ = AmpTreeHpToHpVZ
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),MVZOS,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
  AmpSqTreeHpToHpVZ(gt1, gt2) = AmpSqHpToHpVZ(gt1, gt2)  
  AmpSum2HpToHpVZ = + 2._dp*AmpWaveHpToHpVZ + 2._dp*AmpVertexHpToHpVZ
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),MVZOS,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
  AmpSqHpToHpVZ(gt1, gt2) = AmpSqHpToHpVZ(gt1, gt2) + AmpSqTreeHpToHpVZ(gt1, gt2)  
Else  
  AmpSum2HpToHpVZ = AmpTreeHpToHpVZ
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVZ,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
  AmpSqTreeHpToHpVZ(gt1, gt2) = AmpSqHpToHpVZ(gt1, gt2)  
  AmpSum2HpToHpVZ = + 2._dp*AmpWaveHpToHpVZ + 2._dp*AmpVertexHpToHpVZ
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVZ,AmpSumHpToHpVZ(:,gt1, gt2),AmpSum2HpToHpVZ(:,gt1, gt2),AmpSqHpToHpVZ(gt1, gt2)) 
  AmpSqHpToHpVZ(gt1, gt2) = AmpSqHpToHpVZ(gt1, gt2) + AmpSqTreeHpToHpVZ(gt1, gt2)  
End if  
Else  
  AmpSqHpToHpVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToHpVZ(gt1, gt2).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MHpOS(gt2),MVZOS,helfactor*AmpSqHpToHpVZ(gt1, gt2))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MHp(gt2),MVZ,helfactor*AmpSqHpToHpVZ(gt1, gt2))
End if 
If ((Abs(MRPHpToHpVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToHpVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHpToHpVZ(gt1, gt2) + MRGHpToHpVZ(gt1, gt2)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHpToHpVZ(gt1, gt2) + MRGHpToHpVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! VZ VWp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_HpToVZVWp(cplcHpVWpVZ,MHp,MVWp,MVZ,MHp2,MVWp2,             & 
& MVZ2,AmpTreeHpToVZVWp)

  Else 
Call Amplitude_Tree_Inert2_HpToVZVWp(ZcplcHpVWpVZ,MHp,MVWp,MVZ,MHp2,MVWp2,            & 
& MVZ2,AmpTreeHpToVZVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_HpToVZVWp(MLambda,em,gs,cplcHpVWpVZ,MHpOS,MVWpOS,              & 
& MVZOS,MRPHpToVZVWp,MRGHpToVZVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_HpToVZVWp(MLambda,em,gs,ZcplcHpVWpVZ,MHpOS,MVWpOS,             & 
& MVZOS,MRPHpToVZVWp,MRGHpToVZVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_HpToVZVWp(MLambda,em,gs,cplcHpVWpVZ,MHp,MVWp,MVZ,              & 
& MRPHpToVZVWp,MRGHpToVZVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_HpToVZVWp(MLambda,em,gs,ZcplcHpVWpVZ,MHp,MVWp,MVZ,             & 
& MRPHpToVZVWp,MRGHpToVZVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToVZVWp(cplcHpVPVWp,cplcHpVWpVZ,ctcplcHpVPVWp,           & 
& ctcplcHpVWpVZ,MHp,MHp2,MVP,MVP2,MVWp,MVWp2,MVZ,MVZ2,ZfHp,ZfVWp,ZfVZ,AmpWaveHpToVZVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToVZVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,               & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,              & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,             & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,            & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplHpcVWpVZ,       & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,       & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,          & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,  & 
& AmpVertexHpToVZVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_HpToVZVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,              & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,             & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,            & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplHpcVWpVZ,       & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,       & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,          & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,  & 
& AmpVertexIRdrHpToVZVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToVZVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,              & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0H0VZ,cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,       & 
& cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,            & 
& cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,             & 
& cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,              & 
& cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,         & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,               & 
& cplhhVZVZ,cplHpcHpVP,GosZcplHpcHpVZ,cplHpcVWpVZ,GosZcplcHpVPVWp,cplcVWpVPVWp,          & 
& ZcplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,  & 
& cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,     & 
& cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRosHpToVZVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToVZVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,              & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,             & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,            & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,GZcplHpcHpVZ,cplHpcVWpVZ,     & 
& GZcplcHpVPVWp,cplcVWpVPVWp,ZcplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,    & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,          & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,  & 
& AmpVertexIRosHpToVZVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToVZVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,              & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0H0VZ,cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,       & 
& cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,            & 
& cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,             & 
& cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,              & 
& cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,         & 
& cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,               & 
& cplhhVZVZ,cplHpcHpVP,GcplHpcHpVZ,cplHpcVWpVZ,GcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,    & 
& cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,               & 
& cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,     & 
& cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRosHpToVZVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_HpToVZVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0H0VZ,        & 
& cplA0HpcHp,cplA0cHpVWp,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,              & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0hhVZ,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVZ,cplcgZgWpcHp,cplcgAgWCVWp,             & 
& cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,            & 
& cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,cplHpcHpVZ,cplHpcVWpVZ,       & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVWpVZ1,cplH0cHpVWpVZ1,       & 
& cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplcVWpVPVWpVZ3Q,          & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,  & 
& AmpVertexIRosHpToVZVWp)

 End if 
 End if 
AmpVertexHpToVZVWp = AmpVertexHpToVZVWp -  AmpVertexIRdrHpToVZVWp! +  AmpVertexIRosHpToVZVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHpToVZVWp=0._dp 
AmpVertexZHpToVZVWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHpToVZVWp(:,gt2) = AmpWaveZHpToVZVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHpToVZVWp(:,gt1) 
AmpVertexZHpToVZVWp(:,gt2)= AmpVertexZHpToVZVWp(:,gt2) + ZRUZP(gt2,gt1)*AmpVertexHpToVZVWp(:,gt1) 
 End Do 
End Do 
AmpWaveHpToVZVWp=AmpWaveZHpToVZVWp 
AmpVertexHpToVZVWp= AmpVertexZHpToVZVWp
End if
If (ShiftIRdiv) Then 
AmpVertexHpToVZVWp = AmpVertexHpToVZVWp  +  AmpVertexIRosHpToVZVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->VZ VWp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHpToVZVWp = AmpTreeHpToVZVWp 
 AmpSum2HpToVZVWp = AmpTreeHpToVZVWp + 2._dp*AmpWaveHpToVZVWp + 2._dp*AmpVertexHpToVZVWp  
Else 
 AmpSumHpToVZVWp = AmpTreeHpToVZVWp + AmpWaveHpToVZVWp + AmpVertexHpToVZVWp
 AmpSum2HpToVZVWp = AmpTreeHpToVZVWp + AmpWaveHpToVZVWp + AmpVertexHpToVZVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToVZVWp = AmpTreeHpToVZVWp
 AmpSum2HpToVZVWp = AmpTreeHpToVZVWp 
End if 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MVZOS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MVZ)+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2HpToVZVWp = AmpTreeHpToVZVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHpOS(gt1),MVZOS,MVWpOS,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
Else  
  Call SquareAmp_StoVV(MHp(gt1),MVZ,MVWp,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHpToVZVWp(gt1) 
  AmpSum2HpToVZVWp = 2._dp*AmpWaveHpToVZVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHpOS(gt1),MVZOS,MVWpOS,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
Else  
  Call SquareAmp_StoVV(MHp(gt1),MVZ,MVWp,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHpToVZVWp(gt1) 
  AmpSum2HpToVZVWp = 2._dp*AmpVertexHpToVZVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHpOS(gt1),MVZOS,MVWpOS,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
Else  
  Call SquareAmp_StoVV(MHp(gt1),MVZ,MVWp,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHpToVZVWp(gt1) 
  AmpSum2HpToVZVWp = AmpTreeHpToVZVWp + 2._dp*AmpWaveHpToVZVWp + 2._dp*AmpVertexHpToVZVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHpOS(gt1),MVZOS,MVWpOS,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
Else  
  Call SquareAmp_StoVV(MHp(gt1),MVZ,MVWp,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHpToVZVWp(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2HpToVZVWp = AmpTreeHpToVZVWp
  Call SquareAmp_StoVV(MHpOS(gt1),MVZOS,MVWpOS,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
  AmpSqTreeHpToVZVWp(gt1) = AmpSqHpToVZVWp(gt1)  
  AmpSum2HpToVZVWp = + 2._dp*AmpWaveHpToVZVWp + 2._dp*AmpVertexHpToVZVWp
  Call SquareAmp_StoVV(MHpOS(gt1),MVZOS,MVWpOS,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
  AmpSqHpToVZVWp(gt1) = AmpSqHpToVZVWp(gt1) + AmpSqTreeHpToVZVWp(gt1)  
Else  
  AmpSum2HpToVZVWp = AmpTreeHpToVZVWp
  Call SquareAmp_StoVV(MHp(gt1),MVZ,MVWp,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
  AmpSqTreeHpToVZVWp(gt1) = AmpSqHpToVZVWp(gt1)  
  AmpSum2HpToVZVWp = + 2._dp*AmpWaveHpToVZVWp + 2._dp*AmpVertexHpToVZVWp
  Call SquareAmp_StoVV(MHp(gt1),MVZ,MVWp,AmpSumHpToVZVWp(:,gt1),AmpSum2HpToVZVWp(:,gt1),AmpSqHpToVZVWp(gt1)) 
  AmpSqHpToVZVWp(gt1) = AmpSqHpToVZVWp(gt1) + AmpSqTreeHpToVZVWp(gt1)  
End if  
Else  
  AmpSqHpToVZVWp(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToVZVWp(gt1).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 2._dp*GammaTPS(MHpOS(gt1),MVZOS,MVWpOS,helfactor*AmpSqHpToVZVWp(gt1))
Else 
  gP1LHp(gt1,i4) = 2._dp*GammaTPS(MHp(gt1),MVZ,MVWp,helfactor*AmpSqHpToVZVWp(gt1))
End if 
If ((Abs(MRPHpToVZVWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToVZVWp(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHpToVZVWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToVZVWp(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPHpToVZVWp(gt1) + MRGHpToVZVWp(gt1)) 
  gP1LHp(gt1,i4) = gP1LHp(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPHpToVZVWp(gt1) + MRGHpToVZVWp(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHp(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
!---------------- 
! Hp VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_HpToHpVP(cplHpcHpVP,cplHpcHpVZ,ctcplHpcHpVP,               & 
& ctcplHpcHpVZ,MHpOS,MHp2OS,MVP,MVP2,ZfHp,ZfVP,ZfVZVP,AmpWaveHpToHpVP)

 Else 
Call Amplitude_WAVE_Inert2_HpToHpVP(cplHpcHpVP,cplHpcHpVZ,ctcplHpcHpVP,               & 
& ctcplHpcHpVZ,MHpOS,MHp2OS,MVP,MVP2,ZfHp,ZfVP,ZfVZVP,AmpWaveHpToHpVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_HpToHpVP(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,MH0OS,            & 
& MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,             & 
& cplcFuFdHpR,cplcFdFdVPL,cplcFdFdVPR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVP,cplcgZgWpcHp,cplcgZgWCHp,            & 
& cplcgWCgWCVP,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,              & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,      & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplG0HpcVWpVP1,     & 
& cplG0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,            & 
& cplHpcHpVPVP1,cplHpcHpVPVZ1,AmpVertexHpToHpVP)

 Else 
Call Amplitude_VERTEX_Inert2_HpToHpVP(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,MH0OS,            & 
& MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,             & 
& cplcFuFdHpR,cplcFdFdVPL,cplcFdFdVPR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplG0HpcVWp,cplG0cHpVWp,cplcgWpgWpVP,cplcgZgWpcHp,cplcgZgWCHp,            & 
& cplcgWCgWCVP,cplcgWpgZHp,cplcgWCgZcHp,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,              & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,      & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplG0HpcVWpVP1,     & 
& cplG0cHpVPVWp1,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,            & 
& cplHpcHpVPVP1,cplHpcHpVPVZ1,AmpVertexHpToHpVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToHpVP(cplHpcHpVP,cplHpcHpVZ,ctcplHpcHpVP,               & 
& ctcplHpcHpVZ,MHp,MHp2,MVP,MVP2,ZfHp,ZfVP,ZfVZVP,AmpWaveHpToHpVP)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToHpVP(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,MVP,            & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0HpcHp,           & 
& cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0HpcVWp,cplG0cHpVWp,           & 
& cplcgWpgWpVP,cplcgZgWpcHp,cplcgZgWCHp,cplcgWCgWCVP,cplcgWpgZHp,cplcgWCgZcHp,           & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,      & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,               & 
& cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplG0HpcVWpVP1,cplG0cHpVPVWp1,cplH0HpcVWpVP1,            & 
& cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplHpcHpVPVZ1,              & 
& AmpVertexHpToHpVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->Hp VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToHpVP = 0._dp 
 AmpSum2HpToHpVP = 0._dp  
Else 
 AmpSumHpToHpVP = AmpVertexHpToHpVP + AmpWaveHpToHpVP
 AmpSum2HpToHpVP = AmpVertexHpToHpVP + AmpWaveHpToHpVP 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(MHpOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MHp(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHpOS(gt1),MHpOS(gt2),0._dp,AmpSumHpToHpVP(:,gt1, gt2),AmpSum2HpToHpVP(:,gt1, gt2),AmpSqHpToHpVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHp(gt1),MHp(gt2),MVP,AmpSumHpToHpVP(:,gt1, gt2),AmpSum2HpToHpVP(:,gt1, gt2),AmpSqHpToHpVP(gt1, gt2)) 
End if  
Else  
  AmpSqHpToHpVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToHpVP(gt1, gt2).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHpOS(gt1),MHpOS(gt2),0._dp,helfactor*AmpSqHpToHpVP(gt1, gt2))
Else 
  gP1LHp(gt1,i4) = 1._dp*GammaTPS(MHp(gt1),MHp(gt2),MVP,helfactor*AmpSqHpToHpVP(gt1, gt2))
End if 
If ((Abs(MRPHpToHpVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHpToHpVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VP VWp
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_HpToVPVWp(cplcHpVPVWp,cplcHpVWpVZ,ctcplcHpVPVWp,           & 
& ctcplcHpVWpVZ,MHpOS,MHp2OS,MVP,MVP2,MVWpOS,MVWp2OS,ZfHp,ZfVP,ZfVWp,AmpWaveHpToVPVWp)

 Else 
Call Amplitude_WAVE_Inert2_HpToVPVWp(cplcHpVPVWp,cplcHpVWpVZ,ctcplcHpVPVWp,           & 
& ctcplcHpVWpVZ,MHpOS,MHp2OS,MVP,MVP2,MVWpOS,MVWp2OS,ZfHp,ZfVP,ZfVWp,AmpWaveHpToVPVWp)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_HpToVPVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,MH0OS,           & 
& MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0cHpVWp,cplcFdFdVPL,cplcFdFdVPR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,           & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVP,cplcgZgWpcHp,cplcgWCgWCVP,cplcgAgWCVWp,          & 
& cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,   & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVPVWp1,cplH0cHpVPVWp1,cplhhcHpVPVWp1,cplHpcHpVPVP1,   & 
& cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,     & 
& cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,AmpVertexHpToVPVWp)

 Else 
Call Amplitude_VERTEX_Inert2_HpToVPVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,MH0OS,           & 
& MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0cHpVWp,cplcFdFdVPL,cplcFdFdVPR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,           & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVP,cplcgZgWpcHp,cplcgWCgWCVP,cplcgAgWCVWp,          & 
& cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp,cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,   & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVPVWp1,cplH0cHpVPVWp1,cplhhcHpVPVWp1,cplHpcHpVPVP1,   & 
& cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,     & 
& cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,AmpVertexHpToVPVWp)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_HpToVPVWp(cplcHpVPVWp,cplcHpVWpVZ,ctcplcHpVPVWp,           & 
& ctcplcHpVWpVZ,MHp,MHp2,MVP,MVP2,MVWp,MVWp2,ZfHp,ZfVP,ZfVWp,AmpWaveHpToVPVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_HpToVPVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,               & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0HpcHp,       & 
& cplA0cHpVWp,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,            & 
& cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplG0cHpVWp,cplcgWCgAcHp,cplcgWpgWpVP,          & 
& cplcgZgWpcHp,cplcgWCgWCVP,cplcgAgWCVWp,cplcgZgWCVWp,cplcgWpgZVWp,cplcgWCgZcHp,         & 
& cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,     & 
& cplHpcHpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0cHpVPVWp1,           & 
& cplH0cHpVPVWp1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,            & 
& cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,  & 
& cplcVWpVPVWpVZ1Q,AmpVertexHpToVPVWp)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hp->VP VWp -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumHpToVPVWp = 0._dp 
 AmpSum2HpToVPVWp = 0._dp  
Else 
 AmpSumHpToVPVWp = AmpVertexHpToVPVWp + AmpWaveHpToVPVWp
 AmpSum2HpToVPVWp = AmpVertexHpToVPVWp + AmpWaveHpToVPVWp 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHpOS(gt1)).gt.(Abs(0.)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MHp(gt1)).gt.(Abs(MVP)+Abs(MVWp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHpOS(gt1),0._dp,MVWpOS,AmpSumHpToVPVWp(:,gt1),AmpSum2HpToVPVWp(:,gt1),AmpSqHpToVPVWp(gt1)) 
Else  
  Call SquareAmp_StoVV(MHp(gt1),MVP,MVWp,AmpSumHpToVPVWp(:,gt1),AmpSum2HpToVPVWp(:,gt1),AmpSqHpToVPVWp(gt1)) 
End if  
Else  
  AmpSqHpToVPVWp(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHpToVPVWp(gt1).eq.0._dp) Then 
  gP1LHp(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHp(gt1,i4) = 2._dp*GammaTPS(MHpOS(gt1),0._dp,MVWpOS,helfactor*AmpSqHpToVPVWp(gt1))
Else 
  gP1LHp(gt1,i4) = 2._dp*GammaTPS(MHp(gt1),MVP,MVWp,helfactor*AmpSqHpToVPVWp(gt1))
End if 
If ((Abs(MRPHpToVPVWp(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHpToVPVWp(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHp(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End Subroutine OneLoopDecay_Hp

End Module Wrapper_OneLoopDecay_Hp_Inert2
