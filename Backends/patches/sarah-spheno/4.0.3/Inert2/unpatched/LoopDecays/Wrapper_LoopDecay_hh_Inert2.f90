! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_hh_Inert2
Use Model_Data_Inert2 
Use Kinematics 
Use OneLoopDecay_hh_Inert2 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_hh(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,              & 
& MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,               & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Ye,Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,            & 
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

Complex(dp),Intent(in) :: cplA0A0A0A01,cplA0A0cVWpVWp1,cplA0A0G0,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,        & 
& cplA0A0hh,cplA0A0hhhh1,cplA0A0HpcHp1(2,2),cplA0A0VZVZ1,cplA0cHpVPVWp1(2),              & 
& cplA0cHpVWp(2),cplA0cHpVWpVZ1(2),cplA0G0G0H01,cplA0G0H0,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),& 
& cplA0H0hh,cplA0H0hhhh1,cplA0H0VZ,cplA0hhHpcHp1(2,2),cplA0HpcHp(2,2),cplA0HpcVWp(2),    & 
& cplA0HpcVWpVP1(2),cplA0HpcVWpVZ1(2),cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),& 
& cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),  & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),             & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),               & 
& cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),  & 
& cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),           & 
& cplcFeFvcVWpR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),            & 
& cplcFuFdVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3), & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFvFeVWpL(3,3),              & 
& cplcFvFeVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWCVWp,cplcgAgWpcVWp,        & 
& cplcgWCgAcVWp,cplcgWCgWCG0,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcHp(2),     & 
& cplcgWCgZcVWp,cplcgWpgAHp(2),cplcgWpgAVWp,cplcgWpgWpG0,cplcgWpgWphh,cplcgWpgWpVP,      & 
& cplcgWpgWpVZ,cplcgWpgZHp(2),cplcgWpgZVWp,cplcgZgAhh,cplcgZgWCHp(2),cplcgZgWCVWp,       & 
& cplcgZgWpcHp(2),cplcgZgWpcVWp,cplcgZgZhh,cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpcVWpVWpVWp1Q,& 
& cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,             & 
& cplcVWpVPVPVWp3Q,cplcVWpVPVWp,cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ3Q,      & 
& cplcVWpVWpVZ,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplG0cHpVPVWp1(2),     & 
& cplG0cHpVWp(2),cplG0cHpVWpVZ1(2),cplG0G0cVWpVWp1,cplG0G0G0G01,cplG0G0H0H01,            & 
& cplG0G0hh,cplG0G0hhhh1,cplG0G0HpcHp1(2,2),cplG0G0VZVZ1,cplG0H0H0,cplG0H0H0hh1,         & 
& cplG0H0HpcHp1(2,2),cplG0hhVZ,cplG0HpcVWp(2),cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),       & 
& cplH0cHpVPVWp1(2),cplH0cHpVWp(2),cplH0cHpVWpVZ1(2),cplH0H0cVWpVWp1,cplH0H0H0H01,       & 
& cplH0H0hh,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),cplH0H0VZVZ1,cplH0hhHpcHp1(2,2),             & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2),cplhhcHpVPVWp1(2),  & 
& cplhhcHpVWp(2),cplhhcHpVWpVZ1(2),cplhhcVWpVWp,cplhhhhcVWpVWp1,cplhhhhhh,               & 
& cplhhhhhhhh1,cplhhhhHpcHp1(2,2),cplhhhhVZVZ1,cplhhHpcHp(2,2),cplhhHpcVWp(2),           & 
& cplhhHpcVWpVP1(2),cplhhHpcVWpVZ1(2),cplhhVZVZ,cplHpcHpcVWpVWp1(2,2),cplHpcHpVP(2,2),   & 
& cplHpcHpVPVP1(2,2),cplHpcHpVPVZ1(2,2),cplHpcHpVZ(2,2),cplHpcHpVZVZ1(2,2),              & 
& cplHpcVWpVP(2),cplHpcVWpVZ(2),cplHpHpcHpcHp1(2,2,2,2),ctcplA0A0hh,ctcplA0H0hh,         & 
& ctcplcFdFdhhL(3,3),ctcplcFdFdhhR(3,3),ctcplcFeFehhL(3,3),ctcplcFeFehhR(3,3),           & 
& ctcplcFuFuhhL(3,3),ctcplcFuFuhhR(3,3),ctcplG0G0hh,ctcplG0hhVZ,ctcplH0H0hh,             & 
& ctcplhhcVWpVWp,ctcplhhhhhh,ctcplhhHpcHp(2,2),ctcplhhHpcVWp(2),ctcplhhVZVZ,             & 
& GcplcHpVPVWp(2),GcplhhcHpVWp(2),GcplhhHpcHp(2,2),GcplHpcVWpVP(2),GosZcplcHpVPVWp(2)

Complex(dp),Intent(in) :: GosZcplhhcHpVWp(2),GosZcplhhHpcHp(2,2),GosZcplHpcVWpVP(2),GZcplcHpVPVWp(2),            & 
& GZcplhhcHpVWp(2),GZcplhhHpcHp(2,2),GZcplHpcVWpVP(2),ZcplA0A0hh,ZcplA0H0hh,             & 
& ZcplcFdFdhhL(3,3),ZcplcFdFdhhR(3,3),ZcplcFeFehhL(3,3),ZcplcFeFehhR(3,3),               & 
& ZcplcFuFuhhL(3,3),ZcplcFuFuhhR(3,3),ZcplG0G0hh,ZcplG0hhVZ,ZcplH0H0hh,ZcplhhcVWpVWp,    & 
& Zcplhhhhhh,ZcplhhHpcHp(2,2),ZcplhhHpcVWp(2),ZcplhhVZVZ

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
Real(dp), Intent(out) :: gP1Lhh(1,59) 
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
Real(dp) :: MRPhhToA0A0,MRGhhToA0A0, MRPZhhToA0A0,MRGZhhToA0A0 
Real(dp) :: MVPhhToA0A0 
Real(dp) :: RMsqTreehhToA0A0,RMsqWavehhToA0A0,RMsqVertexhhToA0A0 
Complex(dp) :: AmpTreehhToA0A0,AmpWavehhToA0A0=(0._dp,0._dp),AmpVertexhhToA0A0& 
 & ,AmpVertexIRoshhToA0A0,AmpVertexIRdrhhToA0A0, AmpSumhhToA0A0, AmpSum2hhToA0A0 
Complex(dp) :: AmpTreeZhhToA0A0,AmpWaveZhhToA0A0,AmpVertexZhhToA0A0 
Real(dp) :: AmpSqhhToA0A0,  AmpSqTreehhToA0A0 
Real(dp) :: MRPhhToH0A0,MRGhhToH0A0, MRPZhhToH0A0,MRGZhhToH0A0 
Real(dp) :: MVPhhToH0A0 
Real(dp) :: RMsqTreehhToH0A0,RMsqWavehhToH0A0,RMsqVertexhhToH0A0 
Complex(dp) :: AmpTreehhToH0A0,AmpWavehhToH0A0=(0._dp,0._dp),AmpVertexhhToH0A0& 
 & ,AmpVertexIRoshhToH0A0,AmpVertexIRdrhhToH0A0, AmpSumhhToH0A0, AmpSum2hhToH0A0 
Complex(dp) :: AmpTreeZhhToH0A0,AmpWaveZhhToH0A0,AmpVertexZhhToH0A0 
Real(dp) :: AmpSqhhToH0A0,  AmpSqTreehhToH0A0 
Real(dp) :: MRPhhTocFdFd(3,3),MRGhhTocFdFd(3,3), MRPZhhTocFdFd(3,3),MRGZhhTocFdFd(3,3) 
Real(dp) :: MVPhhTocFdFd(3,3) 
Real(dp) :: RMsqTreehhTocFdFd(3,3),RMsqWavehhTocFdFd(3,3),RMsqVertexhhTocFdFd(3,3) 
Complex(dp) :: AmpTreehhTocFdFd(2,3,3),AmpWavehhTocFdFd(2,3,3)=(0._dp,0._dp),AmpVertexhhTocFdFd(2,3,3)& 
 & ,AmpVertexIRoshhTocFdFd(2,3,3),AmpVertexIRdrhhTocFdFd(2,3,3), AmpSumhhTocFdFd(2,3,3), AmpSum2hhTocFdFd(2,3,3) 
Complex(dp) :: AmpTreeZhhTocFdFd(2,3,3),AmpWaveZhhTocFdFd(2,3,3),AmpVertexZhhTocFdFd(2,3,3) 
Real(dp) :: AmpSqhhTocFdFd(3,3),  AmpSqTreehhTocFdFd(3,3) 
Real(dp) :: MRPhhTocFeFe(3,3),MRGhhTocFeFe(3,3), MRPZhhTocFeFe(3,3),MRGZhhTocFeFe(3,3) 
Real(dp) :: MVPhhTocFeFe(3,3) 
Real(dp) :: RMsqTreehhTocFeFe(3,3),RMsqWavehhTocFeFe(3,3),RMsqVertexhhTocFeFe(3,3) 
Complex(dp) :: AmpTreehhTocFeFe(2,3,3),AmpWavehhTocFeFe(2,3,3)=(0._dp,0._dp),AmpVertexhhTocFeFe(2,3,3)& 
 & ,AmpVertexIRoshhTocFeFe(2,3,3),AmpVertexIRdrhhTocFeFe(2,3,3), AmpSumhhTocFeFe(2,3,3), AmpSum2hhTocFeFe(2,3,3) 
Complex(dp) :: AmpTreeZhhTocFeFe(2,3,3),AmpWaveZhhTocFeFe(2,3,3),AmpVertexZhhTocFeFe(2,3,3) 
Real(dp) :: AmpSqhhTocFeFe(3,3),  AmpSqTreehhTocFeFe(3,3) 
Real(dp) :: MRPhhTocFuFu(3,3),MRGhhTocFuFu(3,3), MRPZhhTocFuFu(3,3),MRGZhhTocFuFu(3,3) 
Real(dp) :: MVPhhTocFuFu(3,3) 
Real(dp) :: RMsqTreehhTocFuFu(3,3),RMsqWavehhTocFuFu(3,3),RMsqVertexhhTocFuFu(3,3) 
Complex(dp) :: AmpTreehhTocFuFu(2,3,3),AmpWavehhTocFuFu(2,3,3)=(0._dp,0._dp),AmpVertexhhTocFuFu(2,3,3)& 
 & ,AmpVertexIRoshhTocFuFu(2,3,3),AmpVertexIRdrhhTocFuFu(2,3,3), AmpSumhhTocFuFu(2,3,3), AmpSum2hhTocFuFu(2,3,3) 
Complex(dp) :: AmpTreeZhhTocFuFu(2,3,3),AmpWaveZhhTocFuFu(2,3,3),AmpVertexZhhTocFuFu(2,3,3) 
Real(dp) :: AmpSqhhTocFuFu(3,3),  AmpSqTreehhTocFuFu(3,3) 
Real(dp) :: MRPhhToH0H0,MRGhhToH0H0, MRPZhhToH0H0,MRGZhhToH0H0 
Real(dp) :: MVPhhToH0H0 
Real(dp) :: RMsqTreehhToH0H0,RMsqWavehhToH0H0,RMsqVertexhhToH0H0 
Complex(dp) :: AmpTreehhToH0H0,AmpWavehhToH0H0=(0._dp,0._dp),AmpVertexhhToH0H0& 
 & ,AmpVertexIRoshhToH0H0,AmpVertexIRdrhhToH0H0, AmpSumhhToH0H0, AmpSum2hhToH0H0 
Complex(dp) :: AmpTreeZhhToH0H0,AmpWaveZhhToH0H0,AmpVertexZhhToH0H0 
Real(dp) :: AmpSqhhToH0H0,  AmpSqTreehhToH0H0 
Real(dp) :: MRPhhTohhhh,MRGhhTohhhh, MRPZhhTohhhh,MRGZhhTohhhh 
Real(dp) :: MVPhhTohhhh 
Real(dp) :: RMsqTreehhTohhhh,RMsqWavehhTohhhh,RMsqVertexhhTohhhh 
Complex(dp) :: AmpTreehhTohhhh,AmpWavehhTohhhh=(0._dp,0._dp),AmpVertexhhTohhhh& 
 & ,AmpVertexIRoshhTohhhh,AmpVertexIRdrhhTohhhh, AmpSumhhTohhhh, AmpSum2hhTohhhh 
Complex(dp) :: AmpTreeZhhTohhhh,AmpWaveZhhTohhhh,AmpVertexZhhTohhhh 
Real(dp) :: AmpSqhhTohhhh,  AmpSqTreehhTohhhh 
Real(dp) :: MRPhhTocHpHp(2,2),MRGhhTocHpHp(2,2), MRPZhhTocHpHp(2,2),MRGZhhTocHpHp(2,2) 
Real(dp) :: MVPhhTocHpHp(2,2) 
Real(dp) :: RMsqTreehhTocHpHp(2,2),RMsqWavehhTocHpHp(2,2),RMsqVertexhhTocHpHp(2,2) 
Complex(dp) :: AmpTreehhTocHpHp(2,2),AmpWavehhTocHpHp(2,2)=(0._dp,0._dp),AmpVertexhhTocHpHp(2,2)& 
 & ,AmpVertexIRoshhTocHpHp(2,2),AmpVertexIRdrhhTocHpHp(2,2), AmpSumhhTocHpHp(2,2), AmpSum2hhTocHpHp(2,2) 
Complex(dp) :: AmpTreeZhhTocHpHp(2,2),AmpWaveZhhTocHpHp(2,2),AmpVertexZhhTocHpHp(2,2) 
Real(dp) :: AmpSqhhTocHpHp(2,2),  AmpSqTreehhTocHpHp(2,2) 
Real(dp) :: MRPhhToHpcVWp(2),MRGhhToHpcVWp(2), MRPZhhToHpcVWp(2),MRGZhhToHpcVWp(2) 
Real(dp) :: MVPhhToHpcVWp(2) 
Real(dp) :: RMsqTreehhToHpcVWp(2),RMsqWavehhToHpcVWp(2),RMsqVertexhhToHpcVWp(2) 
Complex(dp) :: AmpTreehhToHpcVWp(2,2),AmpWavehhToHpcVWp(2,2)=(0._dp,0._dp),AmpVertexhhToHpcVWp(2,2)& 
 & ,AmpVertexIRoshhToHpcVWp(2,2),AmpVertexIRdrhhToHpcVWp(2,2), AmpSumhhToHpcVWp(2,2), AmpSum2hhToHpcVWp(2,2) 
Complex(dp) :: AmpTreeZhhToHpcVWp(2,2),AmpWaveZhhToHpcVWp(2,2),AmpVertexZhhToHpcVWp(2,2) 
Real(dp) :: AmpSqhhToHpcVWp(2),  AmpSqTreehhToHpcVWp(2) 
Real(dp) :: MRPhhTocVWpVWp,MRGhhTocVWpVWp, MRPZhhTocVWpVWp,MRGZhhTocVWpVWp 
Real(dp) :: MVPhhTocVWpVWp 
Real(dp) :: RMsqTreehhTocVWpVWp,RMsqWavehhTocVWpVWp,RMsqVertexhhTocVWpVWp 
Complex(dp) :: AmpTreehhTocVWpVWp(2),AmpWavehhTocVWpVWp(2)=(0._dp,0._dp),AmpVertexhhTocVWpVWp(2)& 
 & ,AmpVertexIRoshhTocVWpVWp(2),AmpVertexIRdrhhTocVWpVWp(2), AmpSumhhTocVWpVWp(2), AmpSum2hhTocVWpVWp(2) 
Complex(dp) :: AmpTreeZhhTocVWpVWp(2),AmpWaveZhhTocVWpVWp(2),AmpVertexZhhTocVWpVWp(2) 
Real(dp) :: AmpSqhhTocVWpVWp,  AmpSqTreehhTocVWpVWp 
Real(dp) :: MRPhhToVZVZ,MRGhhToVZVZ, MRPZhhToVZVZ,MRGZhhToVZVZ 
Real(dp) :: MVPhhToVZVZ 
Real(dp) :: RMsqTreehhToVZVZ,RMsqWavehhToVZVZ,RMsqVertexhhToVZVZ 
Complex(dp) :: AmpTreehhToVZVZ(2),AmpWavehhToVZVZ(2)=(0._dp,0._dp),AmpVertexhhToVZVZ(2)& 
 & ,AmpVertexIRoshhToVZVZ(2),AmpVertexIRdrhhToVZVZ(2), AmpSumhhToVZVZ(2), AmpSum2hhToVZVZ(2) 
Complex(dp) :: AmpTreeZhhToVZVZ(2),AmpWaveZhhToVZVZ(2),AmpVertexZhhToVZVZ(2) 
Real(dp) :: AmpSqhhToVZVZ,  AmpSqTreehhToVZVZ 
Real(dp) :: MRPhhToA0hh,MRGhhToA0hh, MRPZhhToA0hh,MRGZhhToA0hh 
Real(dp) :: MVPhhToA0hh 
Real(dp) :: RMsqTreehhToA0hh,RMsqWavehhToA0hh,RMsqVertexhhToA0hh 
Complex(dp) :: AmpTreehhToA0hh,AmpWavehhToA0hh=(0._dp,0._dp),AmpVertexhhToA0hh& 
 & ,AmpVertexIRoshhToA0hh,AmpVertexIRdrhhToA0hh, AmpSumhhToA0hh, AmpSum2hhToA0hh 
Complex(dp) :: AmpTreeZhhToA0hh,AmpWaveZhhToA0hh,AmpVertexZhhToA0hh 
Real(dp) :: AmpSqhhToA0hh,  AmpSqTreehhToA0hh 
Real(dp) :: MRPhhToA0VP,MRGhhToA0VP, MRPZhhToA0VP,MRGZhhToA0VP 
Real(dp) :: MVPhhToA0VP 
Real(dp) :: RMsqTreehhToA0VP,RMsqWavehhToA0VP,RMsqVertexhhToA0VP 
Complex(dp) :: AmpTreehhToA0VP(2),AmpWavehhToA0VP(2)=(0._dp,0._dp),AmpVertexhhToA0VP(2)& 
 & ,AmpVertexIRoshhToA0VP(2),AmpVertexIRdrhhToA0VP(2), AmpSumhhToA0VP(2), AmpSum2hhToA0VP(2) 
Complex(dp) :: AmpTreeZhhToA0VP(2),AmpWaveZhhToA0VP(2),AmpVertexZhhToA0VP(2) 
Real(dp) :: AmpSqhhToA0VP,  AmpSqTreehhToA0VP 
Real(dp) :: MRPhhToA0VZ,MRGhhToA0VZ, MRPZhhToA0VZ,MRGZhhToA0VZ 
Real(dp) :: MVPhhToA0VZ 
Real(dp) :: RMsqTreehhToA0VZ,RMsqWavehhToA0VZ,RMsqVertexhhToA0VZ 
Complex(dp) :: AmpTreehhToA0VZ(2),AmpWavehhToA0VZ(2)=(0._dp,0._dp),AmpVertexhhToA0VZ(2)& 
 & ,AmpVertexIRoshhToA0VZ(2),AmpVertexIRdrhhToA0VZ(2), AmpSumhhToA0VZ(2), AmpSum2hhToA0VZ(2) 
Complex(dp) :: AmpTreeZhhToA0VZ(2),AmpWaveZhhToA0VZ(2),AmpVertexZhhToA0VZ(2) 
Real(dp) :: AmpSqhhToA0VZ,  AmpSqTreehhToA0VZ 
Real(dp) :: MRPhhToFvcFv(3,3),MRGhhToFvcFv(3,3), MRPZhhToFvcFv(3,3),MRGZhhToFvcFv(3,3) 
Real(dp) :: MVPhhToFvcFv(3,3) 
Real(dp) :: RMsqTreehhToFvcFv(3,3),RMsqWavehhToFvcFv(3,3),RMsqVertexhhToFvcFv(3,3) 
Complex(dp) :: AmpTreehhToFvcFv(2,3,3),AmpWavehhToFvcFv(2,3,3)=(0._dp,0._dp),AmpVertexhhToFvcFv(2,3,3)& 
 & ,AmpVertexIRoshhToFvcFv(2,3,3),AmpVertexIRdrhhToFvcFv(2,3,3), AmpSumhhToFvcFv(2,3,3), AmpSum2hhToFvcFv(2,3,3) 
Complex(dp) :: AmpTreeZhhToFvcFv(2,3,3),AmpWaveZhhToFvcFv(2,3,3),AmpVertexZhhToFvcFv(2,3,3) 
Real(dp) :: AmpSqhhToFvcFv(3,3),  AmpSqTreehhToFvcFv(3,3) 
Real(dp) :: MRPhhToH0hh,MRGhhToH0hh, MRPZhhToH0hh,MRGZhhToH0hh 
Real(dp) :: MVPhhToH0hh 
Real(dp) :: RMsqTreehhToH0hh,RMsqWavehhToH0hh,RMsqVertexhhToH0hh 
Complex(dp) :: AmpTreehhToH0hh,AmpWavehhToH0hh=(0._dp,0._dp),AmpVertexhhToH0hh& 
 & ,AmpVertexIRoshhToH0hh,AmpVertexIRdrhhToH0hh, AmpSumhhToH0hh, AmpSum2hhToH0hh 
Complex(dp) :: AmpTreeZhhToH0hh,AmpWaveZhhToH0hh,AmpVertexZhhToH0hh 
Real(dp) :: AmpSqhhToH0hh,  AmpSqTreehhToH0hh 
Real(dp) :: MRPhhToH0VP,MRGhhToH0VP, MRPZhhToH0VP,MRGZhhToH0VP 
Real(dp) :: MVPhhToH0VP 
Real(dp) :: RMsqTreehhToH0VP,RMsqWavehhToH0VP,RMsqVertexhhToH0VP 
Complex(dp) :: AmpTreehhToH0VP(2),AmpWavehhToH0VP(2)=(0._dp,0._dp),AmpVertexhhToH0VP(2)& 
 & ,AmpVertexIRoshhToH0VP(2),AmpVertexIRdrhhToH0VP(2), AmpSumhhToH0VP(2), AmpSum2hhToH0VP(2) 
Complex(dp) :: AmpTreeZhhToH0VP(2),AmpWaveZhhToH0VP(2),AmpVertexZhhToH0VP(2) 
Real(dp) :: AmpSqhhToH0VP,  AmpSqTreehhToH0VP 
Real(dp) :: MRPhhToH0VZ,MRGhhToH0VZ, MRPZhhToH0VZ,MRGZhhToH0VZ 
Real(dp) :: MVPhhToH0VZ 
Real(dp) :: RMsqTreehhToH0VZ,RMsqWavehhToH0VZ,RMsqVertexhhToH0VZ 
Complex(dp) :: AmpTreehhToH0VZ(2),AmpWavehhToH0VZ(2)=(0._dp,0._dp),AmpVertexhhToH0VZ(2)& 
 & ,AmpVertexIRoshhToH0VZ(2),AmpVertexIRdrhhToH0VZ(2), AmpSumhhToH0VZ(2), AmpSum2hhToH0VZ(2) 
Complex(dp) :: AmpTreeZhhToH0VZ(2),AmpWaveZhhToH0VZ(2),AmpVertexZhhToH0VZ(2) 
Real(dp) :: AmpSqhhToH0VZ,  AmpSqTreehhToH0VZ 
Real(dp) :: MRPhhTohhVP,MRGhhTohhVP, MRPZhhTohhVP,MRGZhhTohhVP 
Real(dp) :: MVPhhTohhVP 
Real(dp) :: RMsqTreehhTohhVP,RMsqWavehhTohhVP,RMsqVertexhhTohhVP 
Complex(dp) :: AmpTreehhTohhVP(2),AmpWavehhTohhVP(2)=(0._dp,0._dp),AmpVertexhhTohhVP(2)& 
 & ,AmpVertexIRoshhTohhVP(2),AmpVertexIRdrhhTohhVP(2), AmpSumhhTohhVP(2), AmpSum2hhTohhVP(2) 
Complex(dp) :: AmpTreeZhhTohhVP(2),AmpWaveZhhTohhVP(2),AmpVertexZhhTohhVP(2) 
Real(dp) :: AmpSqhhTohhVP,  AmpSqTreehhTohhVP 
Real(dp) :: MRPhhTohhVZ,MRGhhTohhVZ, MRPZhhTohhVZ,MRGZhhTohhVZ 
Real(dp) :: MVPhhTohhVZ 
Real(dp) :: RMsqTreehhTohhVZ,RMsqWavehhTohhVZ,RMsqVertexhhTohhVZ 
Complex(dp) :: AmpTreehhTohhVZ(2),AmpWavehhTohhVZ(2)=(0._dp,0._dp),AmpVertexhhTohhVZ(2)& 
 & ,AmpVertexIRoshhTohhVZ(2),AmpVertexIRdrhhTohhVZ(2), AmpSumhhTohhVZ(2), AmpSum2hhTohhVZ(2) 
Complex(dp) :: AmpTreeZhhTohhVZ(2),AmpWaveZhhTohhVZ(2),AmpVertexZhhTohhVZ(2) 
Real(dp) :: AmpSqhhTohhVZ,  AmpSqTreehhTohhVZ 
Real(dp) :: MRPhhToVGVG,MRGhhToVGVG, MRPZhhToVGVG,MRGZhhToVGVG 
Real(dp) :: MVPhhToVGVG 
Real(dp) :: RMsqTreehhToVGVG,RMsqWavehhToVGVG,RMsqVertexhhToVGVG 
Complex(dp) :: AmpTreehhToVGVG(2),AmpWavehhToVGVG(2)=(0._dp,0._dp),AmpVertexhhToVGVG(2)& 
 & ,AmpVertexIRoshhToVGVG(2),AmpVertexIRdrhhToVGVG(2), AmpSumhhToVGVG(2), AmpSum2hhToVGVG(2) 
Complex(dp) :: AmpTreeZhhToVGVG(2),AmpWaveZhhToVGVG(2),AmpVertexZhhToVGVG(2) 
Real(dp) :: AmpSqhhToVGVG,  AmpSqTreehhToVGVG 
Real(dp) :: MRPhhToVPVP,MRGhhToVPVP, MRPZhhToVPVP,MRGZhhToVPVP 
Real(dp) :: MVPhhToVPVP 
Real(dp) :: RMsqTreehhToVPVP,RMsqWavehhToVPVP,RMsqVertexhhToVPVP 
Complex(dp) :: AmpTreehhToVPVP(2),AmpWavehhToVPVP(2)=(0._dp,0._dp),AmpVertexhhToVPVP(2)& 
 & ,AmpVertexIRoshhToVPVP(2),AmpVertexIRdrhhToVPVP(2), AmpSumhhToVPVP(2), AmpSum2hhToVPVP(2) 
Complex(dp) :: AmpTreeZhhToVPVP(2),AmpWaveZhhToVPVP(2),AmpVertexZhhToVPVP(2) 
Real(dp) :: AmpSqhhToVPVP,  AmpSqTreehhToVPVP 
Real(dp) :: MRPhhToVPVZ,MRGhhToVPVZ, MRPZhhToVPVZ,MRGZhhToVPVZ 
Real(dp) :: MVPhhToVPVZ 
Real(dp) :: RMsqTreehhToVPVZ,RMsqWavehhToVPVZ,RMsqVertexhhToVPVZ 
Complex(dp) :: AmpTreehhToVPVZ(2),AmpWavehhToVPVZ(2)=(0._dp,0._dp),AmpVertexhhToVPVZ(2)& 
 & ,AmpVertexIRoshhToVPVZ(2),AmpVertexIRdrhhToVPVZ(2), AmpSumhhToVPVZ(2), AmpSum2hhToVPVZ(2) 
Complex(dp) :: AmpTreeZhhToVPVZ(2),AmpWaveZhhToVPVZ(2),AmpVertexZhhToVPVZ(2) 
Real(dp) :: AmpSqhhToVPVZ,  AmpSqTreehhToVPVZ 
Write(*,*) "Calculating one-loop decays of hh " 
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
isave = 5

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! A0 A0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhToA0A0(cplA0A0hh,MA0,Mhh,MA02,Mhh2,AmpTreehhToA0A0)

  Else 
Call Amplitude_Tree_Inert2_hhToA0A0(ZcplA0A0hh,MA0,Mhh,MA02,Mhh2,AmpTreehhToA0A0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhToA0A0(MLambda,em,gs,cplA0A0hh,MA0OS,MhhOS,MRPhhToA0A0,      & 
& MRGhhToA0A0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhToA0A0(MLambda,em,gs,ZcplA0A0hh,MA0OS,MhhOS,MRPhhToA0A0,     & 
& MRGhhToA0A0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhToA0A0(MLambda,em,gs,cplA0A0hh,MA0,Mhh,MRPhhToA0A0,          & 
& MRGhhToA0A0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhToA0A0(MLambda,em,gs,ZcplA0A0hh,MA0,Mhh,MRPhhToA0A0,         & 
& MRGhhToA0A0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhToA0A0(cplA0A0hh,ctcplA0A0hh,MA0,MA02,Mhh,               & 
& Mhh2,ZfA0,Zfhh,AmpWavehhToA0A0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToA0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,     & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexhhToA0A0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhToA0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,     & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexIRdrhhToA0A0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToA0A0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& ZcplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,            & 
& cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,     & 
& cplA0hhHpcHp1,AmpVertexIRoshhToA0A0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToA0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,ZcplA0A0hh,cplA0G0H0,cplA0H0hh,               & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,      & 
& cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,     & 
& cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexIRoshhToA0A0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToA0A0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,            & 
& cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,cplA0G0H0hh1,cplA0H0hhhh1,     & 
& cplA0hhHpcHp1,AmpVertexIRoshhToA0A0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToA0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0hhVZ,cplH0H0hh,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0A0A01,cplA0A0G0G01,   & 
& cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,cplA0A0cVWpVWp1,cplA0A0VZVZ1,     & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,AmpVertexIRoshhToA0A0)

 End if 
 End if 
AmpVertexhhToA0A0 = AmpVertexhhToA0A0 -  AmpVertexIRdrhhToA0A0! +  AmpVertexIRoshhToA0A0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexhhToA0A0 = AmpVertexhhToA0A0  +  AmpVertexIRoshhToA0A0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->A0 A0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToA0A0 = AmpTreehhToA0A0 
 AmpSum2hhToA0A0 = AmpTreehhToA0A0 + 2._dp*AmpWavehhToA0A0 + 2._dp*AmpVertexhhToA0A0  
Else 
 AmpSumhhToA0A0 = AmpTreehhToA0A0 + AmpWavehhToA0A0 + AmpVertexhhToA0A0
 AmpSum2hhToA0A0 = AmpTreehhToA0A0 + AmpWavehhToA0A0 + AmpVertexhhToA0A0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToA0A0 = AmpTreehhToA0A0
 AmpSum2hhToA0A0 = AmpTreehhToA0A0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MA0OS)+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MA0)+Abs(MA0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2hhToA0A0 = AmpTreehhToA0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MA0OS,MA0OS,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MA0,MA0,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToA0A0 
  AmpSum2hhToA0A0 = 2._dp*AmpWavehhToA0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MA0OS,MA0OS,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MA0,MA0,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToA0A0 
  AmpSum2hhToA0A0 = 2._dp*AmpVertexhhToA0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MA0OS,MA0OS,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MA0,MA0,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToA0A0 
  AmpSum2hhToA0A0 = AmpTreehhToA0A0 + 2._dp*AmpWavehhToA0A0 + 2._dp*AmpVertexhhToA0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MA0OS,MA0OS,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MA0,MA0,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToA0A0 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToA0A0 = AmpTreehhToA0A0
  Call SquareAmp_StoSS(MhhOS,MA0OS,MA0OS,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
  AmpSqTreehhToA0A0 = AmpSqhhToA0A0  
  AmpSum2hhToA0A0 = + 2._dp*AmpWavehhToA0A0 + 2._dp*AmpVertexhhToA0A0
  Call SquareAmp_StoSS(MhhOS,MA0OS,MA0OS,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
  AmpSqhhToA0A0 = AmpSqhhToA0A0 + AmpSqTreehhToA0A0  
Else  
  AmpSum2hhToA0A0 = AmpTreehhToA0A0
  Call SquareAmp_StoSS(Mhh,MA0,MA0,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
  AmpSqTreehhToA0A0 = AmpSqhhToA0A0  
  AmpSum2hhToA0A0 = + 2._dp*AmpWavehhToA0A0 + 2._dp*AmpVertexhhToA0A0
  Call SquareAmp_StoSS(Mhh,MA0,MA0,AmpSumhhToA0A0,AmpSum2hhToA0A0,AmpSqhhToA0A0) 
  AmpSqhhToA0A0 = AmpSqhhToA0A0 + AmpSqTreehhToA0A0  
End if  
Else  
  AmpSqhhToA0A0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToA0A0.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(MhhOS,MA0OS,MA0OS,helfactor*AmpSqhhToA0A0)
Else 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(Mhh,MA0,MA0,helfactor*AmpSqhhToA0A0)
End if 
If ((Abs(MRPhhToA0A0).gt.1.0E-20_dp).or.(Abs(MRGhhToA0A0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToA0A0).gt.1.0E-20_dp).or.(Abs(MRGhhToA0A0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToA0A0 + MRGhhToA0A0) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToA0A0 + MRGhhToA0A0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! H0 A0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhToH0A0(cplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,             & 
& AmpTreehhToH0A0)

  Else 
Call Amplitude_Tree_Inert2_hhToH0A0(ZcplA0H0hh,MA0,MH0,Mhh,MA02,MH02,Mhh2,            & 
& AmpTreehhToH0A0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhToH0A0(MLambda,em,gs,cplA0H0hh,MA0OS,MH0OS,MhhOS,            & 
& MRPhhToH0A0,MRGhhToH0A0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhToH0A0(MLambda,em,gs,ZcplA0H0hh,MA0OS,MH0OS,MhhOS,           & 
& MRPhhToH0A0,MRGhhToH0A0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhToH0A0(MLambda,em,gs,cplA0H0hh,MA0,MH0,Mhh,MRPhhToH0A0,      & 
& MRGhhToH0A0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhToH0A0(MLambda,em,gs,ZcplA0H0hh,MA0,MH0,Mhh,MRPhhToH0A0,     & 
& MRGhhToH0A0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhToH0A0(cplA0H0hh,ctcplA0H0hh,MA0,MA02,MH0,               & 
& MH02,Mhh,Mhh2,ZfA0,ZfH0,Zfhh,AmpWavehhToH0A0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToH0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexhhToH0A0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhToH0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRdrhhToH0A0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0A0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,ZcplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,           & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,   & 
& cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,        & 
& cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRoshhToH0A0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,ZcplA0H0hh,               & 
& cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,            & 
& cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,         & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,          & 
& cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,       & 
& AmpVertexIRoshhToH0A0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0A0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0G0,              & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,            & 
& cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,            & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,   & 
& cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,        & 
& cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRoshhToH0A0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0A0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,      & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,            & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0G0G0H01,cplA0G0H0hh1,         & 
& cplA0H0hhhh1,cplA0hhHpcHp1,cplG0H0H0hh1,cplH0H0hhhh1,cplH0hhHpcHp1,AmpVertexIRoshhToH0A0)

 End if 
 End if 
AmpVertexhhToH0A0 = AmpVertexhhToH0A0 -  AmpVertexIRdrhhToH0A0! +  AmpVertexIRoshhToH0A0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexhhToH0A0 = AmpVertexhhToH0A0  +  AmpVertexIRoshhToH0A0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->H0 A0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToH0A0 = AmpTreehhToH0A0 
 AmpSum2hhToH0A0 = AmpTreehhToH0A0 + 2._dp*AmpWavehhToH0A0 + 2._dp*AmpVertexhhToH0A0  
Else 
 AmpSumhhToH0A0 = AmpTreehhToH0A0 + AmpWavehhToH0A0 + AmpVertexhhToH0A0
 AmpSum2hhToH0A0 = AmpTreehhToH0A0 + AmpWavehhToH0A0 + AmpVertexhhToH0A0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToH0A0 = AmpTreehhToH0A0
 AmpSum2hhToH0A0 = AmpTreehhToH0A0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MH0OS)+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MH0)+Abs(MA0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2hhToH0A0 = AmpTreehhToH0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MA0OS,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MA0,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToH0A0 
  AmpSum2hhToH0A0 = 2._dp*AmpWavehhToH0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MA0OS,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MA0,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToH0A0 
  AmpSum2hhToH0A0 = 2._dp*AmpVertexhhToH0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MA0OS,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MA0,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToH0A0 
  AmpSum2hhToH0A0 = AmpTreehhToH0A0 + 2._dp*AmpWavehhToH0A0 + 2._dp*AmpVertexhhToH0A0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MA0OS,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MA0,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToH0A0 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToH0A0 = AmpTreehhToH0A0
  Call SquareAmp_StoSS(MhhOS,MH0OS,MA0OS,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
  AmpSqTreehhToH0A0 = AmpSqhhToH0A0  
  AmpSum2hhToH0A0 = + 2._dp*AmpWavehhToH0A0 + 2._dp*AmpVertexhhToH0A0
  Call SquareAmp_StoSS(MhhOS,MH0OS,MA0OS,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
  AmpSqhhToH0A0 = AmpSqhhToH0A0 + AmpSqTreehhToH0A0  
Else  
  AmpSum2hhToH0A0 = AmpTreehhToH0A0
  Call SquareAmp_StoSS(Mhh,MH0,MA0,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
  AmpSqTreehhToH0A0 = AmpSqhhToH0A0  
  AmpSum2hhToH0A0 = + 2._dp*AmpWavehhToH0A0 + 2._dp*AmpVertexhhToH0A0
  Call SquareAmp_StoSS(Mhh,MH0,MA0,AmpSumhhToH0A0,AmpSum2hhToH0A0,AmpSqhhToH0A0) 
  AmpSqhhToH0A0 = AmpSqhhToH0A0 + AmpSqTreehhToH0A0  
End if  
Else  
  AmpSqhhToH0A0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToH0A0.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MH0OS,MA0OS,helfactor*AmpSqhhToH0A0)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MH0,MA0,helfactor*AmpSqhhToH0A0)
End if 
If ((Abs(MRPhhToH0A0).gt.1.0E-20_dp).or.(Abs(MRGhhToH0A0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToH0A0).gt.1.0E-20_dp).or.(Abs(MRGhhToH0A0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhToH0A0 + MRGhhToH0A0) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhToH0A0 + MRGhhToH0A0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fd) Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,MFd,Mhh,MFd2,            & 
& Mhh2,AmpTreehhTocFdFd)

  Else 
Call Amplitude_Tree_Inert2_hhTocFdFd(ZcplcFdFdhhL,ZcplcFdFdhhR,MFd,Mhh,               & 
& MFd2,Mhh2,AmpTreehhTocFdFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,               & 
& MFdOS,MhhOS,MRPhhTocFdFd,MRGhhTocFdFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhTocFdFd(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,             & 
& MFdOS,MhhOS,MRPhhTocFdFd,MRGhhTocFdFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,               & 
& MFd,Mhh,MRPhhTocFdFd,MRGhhTocFdFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhTocFdFd(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,             & 
& MFd,Mhh,MRPhhTocFdFd,MRGhhTocFdFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,           & 
& ctcplcFdFdhhR,MFd,MFd2,Mhh,Mhh2,ZfDL,ZfDR,Zfhh,AmpWavehhTocFdFd)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTocFdFd(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,              & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexhhTocFdFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhTocFdFd(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRdrhhTocFdFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFdFd(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFdFd(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRoshhTocFdFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFdFd(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFdFd(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRoshhTocFdFd)

 End if 
 End if 
AmpVertexhhTocFdFd = AmpVertexhhTocFdFd -  AmpVertexIRdrhhTocFdFd! +  AmpVertexIRoshhTocFdFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFdFd(1,gt2,:) = AmpWaveZhhTocFdFd(1,gt2,:)+ZRUZDR(gt2,gt1)*AmpWavehhTocFdFd(1,gt1,:) 
AmpVertexZhhTocFdFd(1,gt2,:)= AmpVertexZhhTocFdFd(1,gt2,:)+ZRUZDR(gt2,gt1)*AmpVertexhhTocFdFd(1,gt1,:) 
AmpWaveZhhTocFdFd(2,gt2,:) = AmpWaveZhhTocFdFd(2,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWavehhTocFdFd(2,gt1,:) 
AmpVertexZhhTocFdFd(2,gt2,:)= AmpVertexZhhTocFdFd(2,gt2,:)+ZRUZDLc(gt2,gt1)*AmpVertexhhTocFdFd(2,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFdFd=AmpWaveZhhTocFdFd 
AmpVertexhhTocFdFd= AmpVertexZhhTocFdFd
! Final State 2 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFdFd(1,:,gt2) = AmpWaveZhhTocFdFd(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpWavehhTocFdFd(1,:,gt1) 
AmpVertexZhhTocFdFd(1,:,gt2)= AmpVertexZhhTocFdFd(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexhhTocFdFd(1,:,gt1) 
AmpWaveZhhTocFdFd(2,:,gt2) = AmpWaveZhhTocFdFd(2,:,gt2)+ZRUZDR(gt2,gt1)*AmpWavehhTocFdFd(2,:,gt1) 
AmpVertexZhhTocFdFd(2,:,gt2)= AmpVertexZhhTocFdFd(2,:,gt2)+ZRUZDR(gt2,gt1)*AmpVertexhhTocFdFd(2,:,gt1) 
 End Do 
End Do 
AmpWavehhTocFdFd=AmpWaveZhhTocFdFd 
AmpVertexhhTocFdFd= AmpVertexZhhTocFdFd
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocFdFd = AmpVertexhhTocFdFd  +  AmpVertexIRoshhTocFdFd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->bar[Fd] Fd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocFdFd = AmpTreehhTocFdFd 
 AmpSum2hhTocFdFd = AmpTreehhTocFdFd + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd  
Else 
 AmpSumhhTocFdFd = AmpTreehhTocFdFd + AmpWavehhTocFdFd + AmpVertexhhTocFdFd
 AmpSum2hhTocFdFd = AmpTreehhTocFdFd + AmpWavehhTocFdFd + AmpVertexhhTocFdFd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocFdFd = AmpTreehhTocFdFd
 AmpSum2hhTocFdFd = AmpTreehhTocFdFd 
End if 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MFdOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MFd(gt2))+Abs(MFd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocFdFd(gt2, gt3) 
  AmpSum2hhTocFdFd = 2._dp*AmpWavehhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocFdFd(gt2, gt3) 
  AmpSum2hhTocFdFd = 2._dp*AmpVertexhhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocFdFd(gt2, gt3) 
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocFdFd(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd
  Call SquareAmp_StoFF(MhhOS,MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
  AmpSqTreehhTocFdFd(gt2, gt3) = AmpSqhhTocFdFd(gt2, gt3)  
  AmpSum2hhTocFdFd = + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd
  Call SquareAmp_StoFF(MhhOS,MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
  AmpSqhhTocFdFd(gt2, gt3) = AmpSqhhTocFdFd(gt2, gt3) + AmpSqTreehhTocFdFd(gt2, gt3)  
Else  
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd
  Call SquareAmp_StoFF(Mhh,MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
  AmpSqTreehhTocFdFd(gt2, gt3) = AmpSqhhTocFdFd(gt2, gt3)  
  AmpSum2hhTocFdFd = + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd
  Call SquareAmp_StoFF(Mhh,MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt2, gt3),AmpSum2hhTocFdFd(:,gt2, gt3),AmpSqhhTocFdFd(gt2, gt3)) 
  AmpSqhhTocFdFd(gt2, gt3) = AmpSqhhTocFdFd(gt2, gt3) + AmpSqTreehhTocFdFd(gt2, gt3)  
End if  
Else  
  AmpSqhhTocFdFd(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocFdFd(gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(MhhOS,MFdOS(gt2),MFdOS(gt3),helfactor*AmpSqhhTocFdFd(gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(Mhh,MFd(gt2),MFd(gt3),helfactor*AmpSqhhTocFdFd(gt2, gt3))
End if 
If ((Abs(MRPhhTocFdFd(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFdFd(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocFdFd(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFdFd(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocFdFd(gt2, gt3) + MRGhhTocFdFd(gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocFdFd(gt2, gt3) + MRGhhTocFdFd(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fe) Fe
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,MFe,Mhh,MFe2,            & 
& Mhh2,AmpTreehhTocFeFe)

  Else 
Call Amplitude_Tree_Inert2_hhTocFeFe(ZcplcFeFehhL,ZcplcFeFehhR,MFe,Mhh,               & 
& MFe2,Mhh2,AmpTreehhTocFeFe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,               & 
& MFeOS,MhhOS,MRPhhTocFeFe,MRGhhTocFeFe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhTocFeFe(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,             & 
& MFeOS,MhhOS,MRPhhTocFeFe,MRGhhTocFeFe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,               & 
& MFe,Mhh,MRPhhTocFeFe,MRGhhTocFeFe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhTocFeFe(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,             & 
& MFe,Mhh,MRPhhTocFeFe,MRGhhTocFeFe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,ctcplcFeFehhL,           & 
& ctcplcFeFehhR,MFe,MFe2,Mhh,Mhh2,ZfEL,ZfER,Zfhh,AmpWavehhTocFeFe)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTocFeFe(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,MFe2,             & 
& MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexhhTocFeFe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhTocFeFe(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,              & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,        & 
& cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRdrhhTocFeFe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFeFe(MFeOS,MG0OS,MhhOS,MHpOS,MVP,MVWpOS,         & 
& MVZOS,MFe2OS,MG02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplcFeFeG0L,cplcFeFeG0R,         & 
& ZcplcFeFehhL,ZcplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,             & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFeFe(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,ZcplcFeFehhL,              & 
& ZcplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,             & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,        & 
& cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFeFe(MFeOS,MG0OS,MhhOS,MHpOS,MVP,MVWpOS,         & 
& MVZOS,MFe2OS,MG02OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplcFeFeG0L,cplcFeFeG0R,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFeFe(MFe,MG0,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFe2,MG02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,              & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,        & 
& cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

 End if 
 End if 
AmpVertexhhTocFeFe = AmpVertexhhTocFeFe -  AmpVertexIRdrhhTocFeFe! +  AmpVertexIRoshhTocFeFe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFeFe(1,gt2,:) = AmpWaveZhhTocFeFe(1,gt2,:)+ZRUZER(gt2,gt1)*AmpWavehhTocFeFe(1,gt1,:) 
AmpVertexZhhTocFeFe(1,gt2,:)= AmpVertexZhhTocFeFe(1,gt2,:)+ZRUZER(gt2,gt1)*AmpVertexhhTocFeFe(1,gt1,:) 
AmpWaveZhhTocFeFe(2,gt2,:) = AmpWaveZhhTocFeFe(2,gt2,:)+ZRUZELc(gt2,gt1)*AmpWavehhTocFeFe(2,gt1,:) 
AmpVertexZhhTocFeFe(2,gt2,:)= AmpVertexZhhTocFeFe(2,gt2,:)+ZRUZELc(gt2,gt1)*AmpVertexhhTocFeFe(2,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFeFe=AmpWaveZhhTocFeFe 
AmpVertexhhTocFeFe= AmpVertexZhhTocFeFe
! Final State 2 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFeFe(1,:,gt2) = AmpWaveZhhTocFeFe(1,:,gt2)+ZRUZEL(gt2,gt1)*AmpWavehhTocFeFe(1,:,gt1) 
AmpVertexZhhTocFeFe(1,:,gt2)= AmpVertexZhhTocFeFe(1,:,gt2)+ZRUZEL(gt2,gt1)*AmpVertexhhTocFeFe(1,:,gt1) 
AmpWaveZhhTocFeFe(2,:,gt2) = AmpWaveZhhTocFeFe(2,:,gt2)+ZRUZER(gt2,gt1)*AmpWavehhTocFeFe(2,:,gt1) 
AmpVertexZhhTocFeFe(2,:,gt2)= AmpVertexZhhTocFeFe(2,:,gt2)+ZRUZER(gt2,gt1)*AmpVertexhhTocFeFe(2,:,gt1) 
 End Do 
End Do 
AmpWavehhTocFeFe=AmpWaveZhhTocFeFe 
AmpVertexhhTocFeFe= AmpVertexZhhTocFeFe
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocFeFe = AmpVertexhhTocFeFe  +  AmpVertexIRoshhTocFeFe
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->bar[Fe] Fe -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocFeFe = AmpTreehhTocFeFe 
 AmpSum2hhTocFeFe = AmpTreehhTocFeFe + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe  
Else 
 AmpSumhhTocFeFe = AmpTreehhTocFeFe + AmpWavehhTocFeFe + AmpVertexhhTocFeFe
 AmpSum2hhTocFeFe = AmpTreehhTocFeFe + AmpWavehhTocFeFe + AmpVertexhhTocFeFe 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocFeFe = AmpTreehhTocFeFe
 AmpSum2hhTocFeFe = AmpTreehhTocFeFe 
End if 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MFeOS(gt2))+Abs(MFeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MFe(gt2))+Abs(MFe(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocFeFe(gt2, gt3) 
  AmpSum2hhTocFeFe = 2._dp*AmpWavehhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocFeFe(gt2, gt3) 
  AmpSum2hhTocFeFe = 2._dp*AmpVertexhhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocFeFe(gt2, gt3) 
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocFeFe(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe
  Call SquareAmp_StoFF(MhhOS,MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
  AmpSqTreehhTocFeFe(gt2, gt3) = AmpSqhhTocFeFe(gt2, gt3)  
  AmpSum2hhTocFeFe = + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe
  Call SquareAmp_StoFF(MhhOS,MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
  AmpSqhhTocFeFe(gt2, gt3) = AmpSqhhTocFeFe(gt2, gt3) + AmpSqTreehhTocFeFe(gt2, gt3)  
Else  
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe
  Call SquareAmp_StoFF(Mhh,MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
  AmpSqTreehhTocFeFe(gt2, gt3) = AmpSqhhTocFeFe(gt2, gt3)  
  AmpSum2hhTocFeFe = + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe
  Call SquareAmp_StoFF(Mhh,MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt2, gt3),AmpSum2hhTocFeFe(:,gt2, gt3),AmpSqhhTocFeFe(gt2, gt3)) 
  AmpSqhhTocFeFe(gt2, gt3) = AmpSqhhTocFeFe(gt2, gt3) + AmpSqTreehhTocFeFe(gt2, gt3)  
End if  
Else  
  AmpSqhhTocFeFe(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocFeFe(gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MFeOS(gt2),MFeOS(gt3),helfactor*AmpSqhhTocFeFe(gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MFe(gt2),MFe(gt3),helfactor*AmpSqhhTocFeFe(gt2, gt3))
End if 
If ((Abs(MRPhhTocFeFe(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFeFe(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocFeFe(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFeFe(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocFeFe(gt2, gt3) + MRGhhTocFeFe(gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocFeFe(gt2, gt3) + MRGhhTocFeFe(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fu) Fu
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,MFu,Mhh,MFu2,            & 
& Mhh2,AmpTreehhTocFuFu)

  Else 
Call Amplitude_Tree_Inert2_hhTocFuFu(ZcplcFuFuhhL,ZcplcFuFuhhR,MFu,Mhh,               & 
& MFu2,Mhh2,AmpTreehhTocFuFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,               & 
& MFuOS,MhhOS,MRPhhTocFuFu,MRGhhTocFuFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhTocFuFu(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,             & 
& MFuOS,MhhOS,MRPhhTocFuFu,MRGhhTocFuFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,               & 
& MFu,Mhh,MRPhhTocFuFu,MRGhhTocFuFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhTocFuFu(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,             & 
& MFu,Mhh,MRPhhTocFuFu,MRGhhTocFuFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,           & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,Zfhh,ZfUL,ZfUR,AmpWavehhTocFuFu)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTocFuFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,              & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexhhTocFuFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhTocFuFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRdrhhTocFuFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFuFu(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,      & 
& cplcFuFuG0L,cplcFuFuG0R,ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFuFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRoshhTocFuFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFuFu(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,      & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocFuFu(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRoshhTocFuFu)

 End if 
 End if 
AmpVertexhhTocFuFu = AmpVertexhhTocFuFu -  AmpVertexIRdrhhTocFuFu! +  AmpVertexIRoshhTocFuFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFuFu(1,gt2,:) = AmpWaveZhhTocFuFu(1,gt2,:)+ZRUZUR(gt2,gt1)*AmpWavehhTocFuFu(1,gt1,:) 
AmpVertexZhhTocFuFu(1,gt2,:)= AmpVertexZhhTocFuFu(1,gt2,:)+ZRUZUR(gt2,gt1)*AmpVertexhhTocFuFu(1,gt1,:) 
AmpWaveZhhTocFuFu(2,gt2,:) = AmpWaveZhhTocFuFu(2,gt2,:)+ZRUZULc(gt2,gt1)*AmpWavehhTocFuFu(2,gt1,:) 
AmpVertexZhhTocFuFu(2,gt2,:)= AmpVertexZhhTocFuFu(2,gt2,:)+ZRUZULc(gt2,gt1)*AmpVertexhhTocFuFu(2,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFuFu=AmpWaveZhhTocFuFu 
AmpVertexhhTocFuFu= AmpVertexZhhTocFuFu
! Final State 2 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFuFu(1,:,gt2) = AmpWaveZhhTocFuFu(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpWavehhTocFuFu(1,:,gt1) 
AmpVertexZhhTocFuFu(1,:,gt2)= AmpVertexZhhTocFuFu(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexhhTocFuFu(1,:,gt1) 
AmpWaveZhhTocFuFu(2,:,gt2) = AmpWaveZhhTocFuFu(2,:,gt2)+ZRUZUR(gt2,gt1)*AmpWavehhTocFuFu(2,:,gt1) 
AmpVertexZhhTocFuFu(2,:,gt2)= AmpVertexZhhTocFuFu(2,:,gt2)+ZRUZUR(gt2,gt1)*AmpVertexhhTocFuFu(2,:,gt1) 
 End Do 
End Do 
AmpWavehhTocFuFu=AmpWaveZhhTocFuFu 
AmpVertexhhTocFuFu= AmpVertexZhhTocFuFu
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocFuFu = AmpVertexhhTocFuFu  +  AmpVertexIRoshhTocFuFu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->bar[Fu] Fu -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocFuFu = AmpTreehhTocFuFu 
 AmpSum2hhTocFuFu = AmpTreehhTocFuFu + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu  
Else 
 AmpSumhhTocFuFu = AmpTreehhTocFuFu + AmpWavehhTocFuFu + AmpVertexhhTocFuFu
 AmpSum2hhTocFuFu = AmpTreehhTocFuFu + AmpWavehhTocFuFu + AmpVertexhhTocFuFu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocFuFu = AmpTreehhTocFuFu
 AmpSum2hhTocFuFu = AmpTreehhTocFuFu 
End if 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MFuOS(gt2))+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MFu(gt2))+Abs(MFu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocFuFu(gt2, gt3) 
  AmpSum2hhTocFuFu = 2._dp*AmpWavehhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocFuFu(gt2, gt3) 
  AmpSum2hhTocFuFu = 2._dp*AmpVertexhhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocFuFu(gt2, gt3) 
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocFuFu(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu
  Call SquareAmp_StoFF(MhhOS,MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
  AmpSqTreehhTocFuFu(gt2, gt3) = AmpSqhhTocFuFu(gt2, gt3)  
  AmpSum2hhTocFuFu = + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu
  Call SquareAmp_StoFF(MhhOS,MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
  AmpSqhhTocFuFu(gt2, gt3) = AmpSqhhTocFuFu(gt2, gt3) + AmpSqTreehhTocFuFu(gt2, gt3)  
Else  
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu
  Call SquareAmp_StoFF(Mhh,MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
  AmpSqTreehhTocFuFu(gt2, gt3) = AmpSqhhTocFuFu(gt2, gt3)  
  AmpSum2hhTocFuFu = + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu
  Call SquareAmp_StoFF(Mhh,MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt2, gt3),AmpSum2hhTocFuFu(:,gt2, gt3),AmpSqhhTocFuFu(gt2, gt3)) 
  AmpSqhhTocFuFu(gt2, gt3) = AmpSqhhTocFuFu(gt2, gt3) + AmpSqTreehhTocFuFu(gt2, gt3)  
End if  
Else  
  AmpSqhhTocFuFu(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocFuFu(gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(MhhOS,MFuOS(gt2),MFuOS(gt3),helfactor*AmpSqhhTocFuFu(gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(Mhh,MFu(gt2),MFu(gt3),helfactor*AmpSqhhTocFuFu(gt2, gt3))
End if 
If ((Abs(MRPhhTocFuFu(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFuFu(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocFuFu(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFuFu(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocFuFu(gt2, gt3) + MRGhhTocFuFu(gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocFuFu(gt2, gt3) + MRGhhTocFuFu(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! H0 H0
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhToH0H0(cplH0H0hh,MH0,Mhh,MH02,Mhh2,AmpTreehhToH0H0)

  Else 
Call Amplitude_Tree_Inert2_hhToH0H0(ZcplH0H0hh,MH0,Mhh,MH02,Mhh2,AmpTreehhToH0H0)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhToH0H0(MLambda,em,gs,cplH0H0hh,MH0OS,MhhOS,MRPhhToH0H0,      & 
& MRGhhToH0H0)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhToH0H0(MLambda,em,gs,ZcplH0H0hh,MH0OS,MhhOS,MRPhhToH0H0,     & 
& MRGhhToH0H0)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhToH0H0(MLambda,em,gs,cplH0H0hh,MH0,Mhh,MRPhhToH0H0,          & 
& MRGhhToH0H0)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhToH0H0(MLambda,em,gs,ZcplH0H0hh,MH0,Mhh,MRPhhToH0H0,         & 
& MRGhhToH0H0)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhToH0H0(cplH0H0hh,ctcplH0H0hh,MH0,MH02,Mhh,               & 
& Mhh2,ZfH0,Zfhh,AmpWavehhToH0H0)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToH0H0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,              & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexhhToH0H0)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhToH0H0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexIRdrhhToH0H0)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0H0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,              & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,cplG0H0H0,cplG0hhVZ,ZcplH0H0hh,cplH0HpcHp,     & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,     & 
& cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,            & 
& cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,    & 
& AmpVertexIRoshhToH0H0)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0H0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,ZcplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,           & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexIRoshhToH0H0)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0H0(MA0OS,MG0OS,MH0OS,MhhOS,MHpOS,               & 
& MVWpOS,MVZOS,MA02OS,MG02OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,              & 
& cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,      & 
& cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,     & 
& cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,            & 
& cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,    & 
& AmpVertexIRoshhToH0H0)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToH0H0(MA0,MG0,MH0,Mhh,MHp,MVWp,MVZ,MA02,           & 
& MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0H0VZ,cplG0G0hh,      & 
& cplG0H0H0,cplG0hhVZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,            & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0H0H01,cplA0G0H0hh1,   & 
& cplA0H0hhhh1,cplG0G0H0H01,cplG0H0H0hh1,cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1,        & 
& cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0hhHpcHp1,AmpVertexIRoshhToH0H0)

 End if 
 End if 
AmpVertexhhToH0H0 = AmpVertexhhToH0H0 -  AmpVertexIRdrhhToH0H0! +  AmpVertexIRoshhToH0H0 ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexhhToH0H0 = AmpVertexhhToH0H0  +  AmpVertexIRoshhToH0H0
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->H0 H0 -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToH0H0 = AmpTreehhToH0H0 
 AmpSum2hhToH0H0 = AmpTreehhToH0H0 + 2._dp*AmpWavehhToH0H0 + 2._dp*AmpVertexhhToH0H0  
Else 
 AmpSumhhToH0H0 = AmpTreehhToH0H0 + AmpWavehhToH0H0 + AmpVertexhhToH0H0
 AmpSum2hhToH0H0 = AmpTreehhToH0H0 + AmpWavehhToH0H0 + AmpVertexhhToH0H0 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToH0H0 = AmpTreehhToH0H0
 AmpSum2hhToH0H0 = AmpTreehhToH0H0 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MH0OS)+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MH0)+Abs(MH0))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2hhToH0H0 = AmpTreehhToH0H0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MH0OS,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MH0,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToH0H0 
  AmpSum2hhToH0H0 = 2._dp*AmpWavehhToH0H0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MH0OS,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MH0,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToH0H0 
  AmpSum2hhToH0H0 = 2._dp*AmpVertexhhToH0H0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MH0OS,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MH0,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToH0H0 
  AmpSum2hhToH0H0 = AmpTreehhToH0H0 + 2._dp*AmpWavehhToH0H0 + 2._dp*AmpVertexhhToH0H0
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MH0OS,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,MH0,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToH0H0 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToH0H0 = AmpTreehhToH0H0
  Call SquareAmp_StoSS(MhhOS,MH0OS,MH0OS,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
  AmpSqTreehhToH0H0 = AmpSqhhToH0H0  
  AmpSum2hhToH0H0 = + 2._dp*AmpWavehhToH0H0 + 2._dp*AmpVertexhhToH0H0
  Call SquareAmp_StoSS(MhhOS,MH0OS,MH0OS,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
  AmpSqhhToH0H0 = AmpSqhhToH0H0 + AmpSqTreehhToH0H0  
Else  
  AmpSum2hhToH0H0 = AmpTreehhToH0H0
  Call SquareAmp_StoSS(Mhh,MH0,MH0,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
  AmpSqTreehhToH0H0 = AmpSqhhToH0H0  
  AmpSum2hhToH0H0 = + 2._dp*AmpWavehhToH0H0 + 2._dp*AmpVertexhhToH0H0
  Call SquareAmp_StoSS(Mhh,MH0,MH0,AmpSumhhToH0H0,AmpSum2hhToH0H0,AmpSqhhToH0H0) 
  AmpSqhhToH0H0 = AmpSqhhToH0H0 + AmpSqTreehhToH0H0  
End if  
Else  
  AmpSqhhToH0H0 = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToH0H0.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(MhhOS,MH0OS,MH0OS,helfactor*AmpSqhhToH0H0)
Else 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(Mhh,MH0,MH0,helfactor*AmpSqhhToH0H0)
End if 
If ((Abs(MRPhhToH0H0).gt.1.0E-20_dp).or.(Abs(MRGhhToH0H0).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToH0H0).gt.1.0E-20_dp).or.(Abs(MRGhhToH0H0).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToH0H0 + MRGhhToH0H0) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToH0H0 + MRGhhToH0H0)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhTohhhh(cplhhhhhh,Mhh,Mhh2,AmpTreehhTohhhh)

  Else 
Call Amplitude_Tree_Inert2_hhTohhhh(Zcplhhhhhh,Mhh,Mhh2,AmpTreehhTohhhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhTohhhh(MLambda,em,gs,cplhhhhhh,MhhOS,MRPhhTohhhh,            & 
& MRGhhTohhhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhTohhhh(MLambda,em,gs,Zcplhhhhhh,MhhOS,MRPhhTohhhh,           & 
& MRGhhTohhhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhTohhhh(MLambda,em,gs,cplhhhhhh,Mhh,MRPhhTohhhh,              & 
& MRGhhTohhhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhTohhhh(MLambda,em,gs,Zcplhhhhhh,Mhh,MRPhhTohhhh,             & 
& MRGhhTohhhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhTohhhh(cplhhhhhh,ctcplhhhhhh,Mhh,Mhh2,Zfhh,              & 
& AmpWavehhTohhhh)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTohhhh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,MVWp,           & 
& MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,            & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,          & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,   & 
& cplG0G0hhhh1,cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,     & 
& AmpVertexhhTohhhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhTohhhh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,          & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,   & 
& cplG0G0hhhh1,cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,     & 
& AmpVertexIRdrhhTohhhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTohhhh(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,              & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,Zcplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,       & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,cplG0G0hhhh1,cplH0H0hhhh1,            & 
& cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTohhhh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,Zcplhhhhhh,         & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,   & 
& cplG0G0hhhh1,cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,     & 
& AmpVertexIRoshhTohhhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTohhhh(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,              & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,        & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,cplG0G0hhhh1,cplH0H0hhhh1,            & 
& cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTohhhh(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,          & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh1,cplA0H0hhhh1,   & 
& cplG0G0hhhh1,cplH0H0hhhh1,cplhhhhhhhh1,cplhhhhHpcHp1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,     & 
& AmpVertexIRoshhTohhhh)

 End if 
 End if 
AmpVertexhhTohhhh = AmpVertexhhTohhhh -  AmpVertexIRdrhhTohhhh! +  AmpVertexIRoshhTohhhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexhhTohhhh = AmpVertexhhTohhhh  +  AmpVertexIRoshhTohhhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->hh hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTohhhh = AmpTreehhTohhhh 
 AmpSum2hhTohhhh = AmpTreehhTohhhh + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh  
Else 
 AmpSumhhTohhhh = AmpTreehhTohhhh + AmpWavehhTohhhh + AmpVertexhhTohhhh
 AmpSum2hhTohhhh = AmpTreehhTohhhh + AmpWavehhTohhhh + AmpVertexhhTohhhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTohhhh = AmpTreehhTohhhh
 AmpSum2hhTohhhh = AmpTreehhTohhhh 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MhhOS)+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(Mhh)+Abs(Mhh))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2hhTohhhh = AmpTreehhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MhhOS,MhhOS,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
Else  
  Call SquareAmp_StoSS(Mhh,Mhh,Mhh,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTohhhh 
  AmpSum2hhTohhhh = 2._dp*AmpWavehhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MhhOS,MhhOS,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
Else  
  Call SquareAmp_StoSS(Mhh,Mhh,Mhh,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTohhhh 
  AmpSum2hhTohhhh = 2._dp*AmpVertexhhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MhhOS,MhhOS,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
Else  
  Call SquareAmp_StoSS(Mhh,Mhh,Mhh,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTohhhh 
  AmpSum2hhTohhhh = AmpTreehhTohhhh + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MhhOS,MhhOS,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
Else  
  Call SquareAmp_StoSS(Mhh,Mhh,Mhh,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTohhhh 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTohhhh = AmpTreehhTohhhh
  Call SquareAmp_StoSS(MhhOS,MhhOS,MhhOS,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
  AmpSqTreehhTohhhh = AmpSqhhTohhhh  
  AmpSum2hhTohhhh = + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh
  Call SquareAmp_StoSS(MhhOS,MhhOS,MhhOS,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
  AmpSqhhTohhhh = AmpSqhhTohhhh + AmpSqTreehhTohhhh  
Else  
  AmpSum2hhTohhhh = AmpTreehhTohhhh
  Call SquareAmp_StoSS(Mhh,Mhh,Mhh,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
  AmpSqTreehhTohhhh = AmpSqhhTohhhh  
  AmpSum2hhTohhhh = + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh
  Call SquareAmp_StoSS(Mhh,Mhh,Mhh,AmpSumhhTohhhh,AmpSum2hhTohhhh,AmpSqhhTohhhh) 
  AmpSqhhTohhhh = AmpSqhhTohhhh + AmpSqTreehhTohhhh  
End if  
Else  
  AmpSqhhTohhhh = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTohhhh.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(MhhOS,MhhOS,MhhOS,helfactor*AmpSqhhTohhhh)
Else 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(Mhh,Mhh,Mhh,helfactor*AmpSqhhTohhhh)
End if 
If ((Abs(MRPhhTohhhh).gt.1.0E-20_dp).or.(Abs(MRGhhTohhhh).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTohhhh).gt.1.0E-20_dp).or.(Abs(MRGhhTohhhh).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPhhTohhhh + MRGhhTohhhh) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPhhTohhhh + MRGhhTohhhh)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Conjg(Hp) Hp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhTocHpHp(cplhhHpcHp,Mhh,MHp,Mhh2,MHp2,AmpTreehhTocHpHp)

  Else 
Call Amplitude_Tree_Inert2_hhTocHpHp(ZcplhhHpcHp,Mhh,MHp,Mhh2,MHp2,AmpTreehhTocHpHp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhTocHpHp(MLambda,em,gs,cplhhHpcHp,MhhOS,MHpOS,MRPhhTocHpHp,   & 
& MRGhhTocHpHp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhTocHpHp(MLambda,em,gs,ZcplhhHpcHp,MhhOS,MHpOS,               & 
& MRPhhTocHpHp,MRGhhTocHpHp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhTocHpHp(MLambda,em,gs,cplhhHpcHp,Mhh,MHp,MRPhhTocHpHp,       & 
& MRGhhTocHpHp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhTocHpHp(MLambda,em,gs,ZcplhhHpcHp,Mhh,MHp,MRPhhTocHpHp,      & 
& MRGhhTocHpHp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhTocHpHp(cplhhHpcHp,ctcplhhHpcHp,Mhh,Mhh2,MHp,            & 
& MHp2,Zfhh,ZfHp,AmpWavehhTocHpHp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTocHpHp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,               & 
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
& cplHpcHpVZVZ1,AmpVertexhhTocHpHp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhTocHpHp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
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
& cplHpcHpVZVZ1,AmpVertexIRdrhhTocHpHp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocHpHp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,              & 
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
& AmpVertexIRoshhTocHpHp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocHpHp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
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
& cplHpcHpVZVZ1,AmpVertexIRoshhTocHpHp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocHpHp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,              & 
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
& AmpVertexIRoshhTocHpHp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocHpHp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,            & 
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
& cplHpcHpVZVZ1,AmpVertexIRoshhTocHpHp)

 End if 
 End if 
AmpVertexhhTocHpHp = AmpVertexhhTocHpHp -  AmpVertexIRdrhhTocHpHp! +  AmpVertexIRoshhTocHpHp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZhhTocHpHp=0._dp 
AmpVertexZhhTocHpHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHpHp(gt2,:) = AmpWaveZhhTocHpHp(gt2,:)+ZRUZP(gt2,gt1)*AmpWavehhTocHpHp(gt1,:) 
AmpVertexZhhTocHpHp(gt2,:)= AmpVertexZhhTocHpHp(gt2,:)+ZRUZP(gt2,gt1)*AmpVertexhhTocHpHp(gt1,:) 
 End Do 
End Do 
AmpWavehhTocHpHp=AmpWaveZhhTocHpHp 
AmpVertexhhTocHpHp= AmpVertexZhhTocHpHp
! Final State 2 
AmpWaveZhhTocHpHp=0._dp 
AmpVertexZhhTocHpHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHpHp(:,gt2) = AmpWaveZhhTocHpHp(:,gt2)+ZRUZP(gt2,gt1)*AmpWavehhTocHpHp(:,gt1) 
AmpVertexZhhTocHpHp(:,gt2)= AmpVertexZhhTocHpHp(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexhhTocHpHp(:,gt1) 
 End Do 
End Do 
AmpWavehhTocHpHp=AmpWaveZhhTocHpHp 
AmpVertexhhTocHpHp= AmpVertexZhhTocHpHp
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocHpHp = AmpVertexhhTocHpHp  +  AmpVertexIRoshhTocHpHp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->conj[Hp] Hp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocHpHp = AmpTreehhTocHpHp 
 AmpSum2hhTocHpHp = AmpTreehhTocHpHp + 2._dp*AmpWavehhTocHpHp + 2._dp*AmpVertexhhTocHpHp  
Else 
 AmpSumhhTocHpHp = AmpTreehhTocHpHp + AmpWavehhTocHpHp + AmpVertexhhTocHpHp
 AmpSum2hhTocHpHp = AmpTreehhTocHpHp + AmpWavehhTocHpHp + AmpVertexhhTocHpHp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocHpHp = AmpTreehhTocHpHp
 AmpSum2hhTocHpHp = AmpTreehhTocHpHp 
End if 
gt1=1 
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MHpOS(gt2))+Abs(MHpOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MHp(gt2))+Abs(MHp(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2hhTocHpHp = AmpTreehhTocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MHpOS(gt2),MHpOS(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh,MHp(gt2),MHp(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocHpHp(gt2, gt3) 
  AmpSum2hhTocHpHp = 2._dp*AmpWavehhTocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MHpOS(gt2),MHpOS(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh,MHp(gt2),MHp(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocHpHp(gt2, gt3) 
  AmpSum2hhTocHpHp = 2._dp*AmpVertexhhTocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MHpOS(gt2),MHpOS(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh,MHp(gt2),MHp(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocHpHp(gt2, gt3) 
  AmpSum2hhTocHpHp = AmpTreehhTocHpHp + 2._dp*AmpWavehhTocHpHp + 2._dp*AmpVertexhhTocHpHp
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MHpOS(gt2),MHpOS(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh,MHp(gt2),MHp(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocHpHp(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocHpHp = AmpTreehhTocHpHp
  Call SquareAmp_StoSS(MhhOS,MHpOS(gt2),MHpOS(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
  AmpSqTreehhTocHpHp(gt2, gt3) = AmpSqhhTocHpHp(gt2, gt3)  
  AmpSum2hhTocHpHp = + 2._dp*AmpWavehhTocHpHp + 2._dp*AmpVertexhhTocHpHp
  Call SquareAmp_StoSS(MhhOS,MHpOS(gt2),MHpOS(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
  AmpSqhhTocHpHp(gt2, gt3) = AmpSqhhTocHpHp(gt2, gt3) + AmpSqTreehhTocHpHp(gt2, gt3)  
Else  
  AmpSum2hhTocHpHp = AmpTreehhTocHpHp
  Call SquareAmp_StoSS(Mhh,MHp(gt2),MHp(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
  AmpSqTreehhTocHpHp(gt2, gt3) = AmpSqhhTocHpHp(gt2, gt3)  
  AmpSum2hhTocHpHp = + 2._dp*AmpWavehhTocHpHp + 2._dp*AmpVertexhhTocHpHp
  Call SquareAmp_StoSS(Mhh,MHp(gt2),MHp(gt3),AmpSumhhTocHpHp(gt2, gt3),AmpSum2hhTocHpHp(gt2, gt3),AmpSqhhTocHpHp(gt2, gt3)) 
  AmpSqhhTocHpHp(gt2, gt3) = AmpSqhhTocHpHp(gt2, gt3) + AmpSqTreehhTocHpHp(gt2, gt3)  
End if  
Else  
  AmpSqhhTocHpHp(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTocHpHp(gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MHpOS(gt2),MHpOS(gt3),helfactor*AmpSqhhTocHpHp(gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MHp(gt2),MHp(gt3),helfactor*AmpSqhhTocHpHp(gt2, gt3))
End if 
If ((Abs(MRPhhTocHpHp(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocHpHp(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocHpHp(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocHpHp(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocHpHp(gt2, gt3) + MRGhhTocHpHp(gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocHpHp(gt2, gt3) + MRGhhTocHpHp(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Hp Conjg(VWp)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhToHpcVWp(cplhhHpcVWp,Mhh,MHp,MVWp,Mhh2,MHp2,             & 
& MVWp2,AmpTreehhToHpcVWp)

  Else 
Call Amplitude_Tree_Inert2_hhToHpcVWp(ZcplhhHpcVWp,Mhh,MHp,MVWp,Mhh2,MHp2,            & 
& MVWp2,AmpTreehhToHpcVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhToHpcVWp(MLambda,em,gs,cplhhHpcVWp,MhhOS,MHpOS,              & 
& MVWpOS,MRPhhToHpcVWp,MRGhhToHpcVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhToHpcVWp(MLambda,em,gs,ZcplhhHpcVWp,MhhOS,MHpOS,             & 
& MVWpOS,MRPhhToHpcVWp,MRGhhToHpcVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhToHpcVWp(MLambda,em,gs,cplhhHpcVWp,Mhh,MHp,MVWp,             & 
& MRPhhToHpcVWp,MRGhhToHpcVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhToHpcVWp(MLambda,em,gs,ZcplhhHpcVWp,Mhh,MHp,MVWp,            & 
& MRPhhToHpcVWp,MRGhhToHpcVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhToHpcVWp(cplhhHpcVWp,ctcplhhHpcVWp,Mhh,Mhh2,             & 
& MHp,MHp2,MVWp,MVWp2,Zfhh,ZfHp,ZfVWp,AmpWavehhToHpcVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToHpcVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,              & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,      & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,cplG0HpcVWp,         & 
& cplcgZgAhh,cplcgWpgAHp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,          & 
& cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,     & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,        & 
& cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplG0HpcVWpVZ1,           & 
& cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexhhToHpcVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhToHpcVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,               & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,        & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,         & 
& cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,               & 
& cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,      & 
& cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,     & 
& cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRdrhhToHpcVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToHpcVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,             & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,          & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,              & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,          & 
& cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,GosZcplhhHpcHp,   & 
& ZcplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,GosZcplHpcVWpVP,            & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,       & 
& cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRoshhToHpcVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToHpcVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,               & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,        & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,         & 
& cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,               & 
& cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,GZcplhhHpcHp,ZcplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,   & 
& cplhhVZVZ,cplHpcHpVP,GZcplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,   & 
& cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRoshhToHpcVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToHpcVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,             & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,          & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,              & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,          & 
& cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,GcplhhHpcHp,      & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVP,GcplHpcVWpVP,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,   & 
& cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,AmpVertexIRoshhToHpcVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToHpcVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,               & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcHp,cplA0HpcVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,        & 
& cplcFuFdHpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0hhVZ,         & 
& cplG0HpcVWp,cplcgZgAhh,cplcgWpgAHp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,           & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcVWp,cplH0H0hh,               & 
& cplH0HpcHp,cplH0HpcVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,      & 
& cplhhVZVZ,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,     & 
& cplG0HpcVWpVZ1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplHpcHpcVWpVWp1,         & 
& AmpVertexIRoshhToHpcVWp)

 End if 
 End if 
AmpVertexhhToHpcVWp = AmpVertexhhToHpcVWp -  AmpVertexIRdrhhToHpcVWp! +  AmpVertexIRoshhToHpcVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZhhToHpcVWp=0._dp 
AmpVertexZhhToHpcVWp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToHpcVWp(:,gt2) = AmpWaveZhhToHpcVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpWavehhToHpcVWp(:,gt1) 
AmpVertexZhhToHpcVWp(:,gt2)= AmpVertexZhhToHpcVWp(:,gt2)+ZRUZP(gt2,gt1)*AmpVertexhhToHpcVWp(:,gt1) 
 End Do 
End Do 
AmpWavehhToHpcVWp=AmpWaveZhhToHpcVWp 
AmpVertexhhToHpcVWp= AmpVertexZhhToHpcVWp
End if
If (ShiftIRdiv) Then 
AmpVertexhhToHpcVWp = AmpVertexhhToHpcVWp  +  AmpVertexIRoshhToHpcVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Hp conj[VWp] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToHpcVWp = AmpTreehhToHpcVWp 
 AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp + 2._dp*AmpWavehhToHpcVWp + 2._dp*AmpVertexhhToHpcVWp  
Else 
 AmpSumhhToHpcVWp = AmpTreehhToHpcVWp + AmpWavehhToHpcVWp + AmpVertexhhToHpcVWp
 AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp + AmpWavehhToHpcVWp + AmpVertexhhToHpcVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToHpcVWp = AmpTreehhToHpcVWp
 AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp 
End if 
gt1=1 
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MHpOS(gt2))+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MHp(gt2))+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2 
  AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MHpOS(gt2),MVWpOS,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh,MHp(gt2),MVWp,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToHpcVWp(gt2) 
  AmpSum2hhToHpcVWp = 2._dp*AmpWavehhToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MHpOS(gt2),MVWpOS,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh,MHp(gt2),MVWp,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToHpcVWp(gt2) 
  AmpSum2hhToHpcVWp = 2._dp*AmpVertexhhToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MHpOS(gt2),MVWpOS,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh,MHp(gt2),MVWp,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToHpcVWp(gt2) 
  AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp + 2._dp*AmpWavehhToHpcVWp + 2._dp*AmpVertexhhToHpcVWp
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MHpOS(gt2),MVWpOS,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh,MHp(gt2),MVWp,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToHpcVWp(gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp
  Call SquareAmp_StoSV(MhhOS,MHpOS(gt2),MVWpOS,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
  AmpSqTreehhToHpcVWp(gt2) = AmpSqhhToHpcVWp(gt2)  
  AmpSum2hhToHpcVWp = + 2._dp*AmpWavehhToHpcVWp + 2._dp*AmpVertexhhToHpcVWp
  Call SquareAmp_StoSV(MhhOS,MHpOS(gt2),MVWpOS,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
  AmpSqhhToHpcVWp(gt2) = AmpSqhhToHpcVWp(gt2) + AmpSqTreehhToHpcVWp(gt2)  
Else  
  AmpSum2hhToHpcVWp = AmpTreehhToHpcVWp
  Call SquareAmp_StoSV(Mhh,MHp(gt2),MVWp,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
  AmpSqTreehhToHpcVWp(gt2) = AmpSqhhToHpcVWp(gt2)  
  AmpSum2hhToHpcVWp = + 2._dp*AmpWavehhToHpcVWp + 2._dp*AmpVertexhhToHpcVWp
  Call SquareAmp_StoSV(Mhh,MHp(gt2),MVWp,AmpSumhhToHpcVWp(:,gt2),AmpSum2hhToHpcVWp(:,gt2),AmpSqhhToHpcVWp(gt2)) 
  AmpSqhhToHpcVWp(gt2) = AmpSqhhToHpcVWp(gt2) + AmpSqTreehhToHpcVWp(gt2)  
End if  
Else  
  AmpSqhhToHpcVWp(gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToHpcVWp(gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS,MHpOS(gt2),MVWpOS,helfactor*AmpSqhhToHpcVWp(gt2))
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh,MHp(gt2),MVWp,helfactor*AmpSqhhToHpcVWp(gt2))
End if 
If ((Abs(MRPhhToHpcVWp(gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToHpcVWp(gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToHpcVWp(gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToHpcVWp(gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPhhToHpcVWp(gt2) + MRGhhToHpcVWp(gt2)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPhhToHpcVWp(gt2) + MRGhhToHpcVWp(gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Conjg(VWp) VWp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhTocVWpVWp(cplhhcVWpVWp,Mhh,MVWp,Mhh2,MVWp2,              & 
& AmpTreehhTocVWpVWp)

  Else 
Call Amplitude_Tree_Inert2_hhTocVWpVWp(ZcplhhcVWpVWp,Mhh,MVWp,Mhh2,MVWp2,             & 
& AmpTreehhTocVWpVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhTocVWpVWp(MLambda,em,gs,cplhhcVWpVWp,MhhOS,MVWpOS,           & 
& MRPhhTocVWpVWp,MRGhhTocVWpVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhTocVWpVWp(MLambda,em,gs,ZcplhhcVWpVWp,MhhOS,MVWpOS,          & 
& MRPhhTocVWpVWp,MRGhhTocVWpVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhTocVWpVWp(MLambda,em,gs,cplhhcVWpVWp,Mhh,MVWp,               & 
& MRPhhTocVWpVWp,MRGhhTocVWpVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhTocVWpVWp(MLambda,em,gs,ZcplhhcVWpVWp,Mhh,MVWp,              & 
& MRPhhTocVWpVWp,MRGhhTocVWpVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhTocVWpVWp(cplhhcVWpVWp,ctcplhhcVWpVWp,Mhh,               & 
& Mhh2,MVWp,MVWp2,Zfhh,ZfVWp,AmpWavehhTocVWpVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTocVWpVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplA0A0hh,        & 
& cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,   & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,           & 
& cplG0HpcVWp,cplG0cHpVWp,cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWphh,            & 
& cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,         & 
& cplcgWpgZVWp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplG0G0cVWpVWp1,cplH0H0cVWpVWp1, & 
& cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,           & 
& cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,          & 
& cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexhhTocVWpVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,      & 
& cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,         & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,               & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,       & 
& cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,               & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,         & 
& cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,         & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,& 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRdrhhTocVWpVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,            & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,               & 
& cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,        & 
& cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,          & 
& cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,GosZcplhhHpcHp,cplhhHpcVWp,GosZcplhhcHpVWp,& 
& ZcplhhcVWpVWp,cplhhVZVZ,GosZcplHpcVWpVP,cplHpcVWpVZ,GosZcplcHpVPVWp,cplcVWpVPVWp,      & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,              & 
& cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,           & 
& cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,          & 
& cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhTocVWpVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,      & 
& cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,         & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,               & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,       & 
& cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,               & 
& cplhhhhhh,GZcplhhHpcHp,cplhhHpcVWp,GZcplhhcHpVWp,ZcplhhcVWpVWp,cplhhVZVZ,              & 
& GZcplHpcVWpVP,cplHpcVWpVZ,GZcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,         & 
& cplA0A0cVWpVWp1,cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,        & 
& cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,     & 
& cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,             & 
& cplcVWpVWpVZVZ1Q,AmpVertexIRoshhTocVWpVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,            & 
& MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,               & 
& cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,        & 
& cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,          & 
& cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,GcplhhcHpVWp,       & 
& cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,               & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,              & 
& cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,           & 
& cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,cplcVWpcVWpVWpVWp3Q,          & 
& cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhTocVWpVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhTocVWpVWp(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,              & 
& MHp,MVP,MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVP2,MVWp2,MVZ2,              & 
& cplA0A0hh,cplA0H0hh,cplA0HpcVWp,cplA0cHpVWp,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdVWpL,      & 
& cplcFuFdVWpR,cplcFeFehhL,cplcFeFehhR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0G0hh,         & 
& cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplcgZgAhh,cplcgWpgAVWp,cplcgWCgAcVWp,               & 
& cplcgWpgWphh,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWChh,cplcgAgWCVWp,cplcgZgWCVWp,       & 
& cplcgZgZhh,cplcgWpgZVWp,cplcgWCgZcVWp,cplH0H0hh,cplH0HpcVWp,cplH0cHpVWp,               & 
& cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,       & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0cVWpVWp1,         & 
& cplG0G0cVWpVWp1,cplH0H0cVWpVWp1,cplhhhhcVWpVWp1,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,         & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpcVWpVWp1,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,& 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhTocVWpVWp)

 End if 
 End if 
AmpVertexhhTocVWpVWp = AmpVertexhhTocVWpVWp -  AmpVertexIRdrhhTocVWpVWp! +  AmpVertexIRoshhTocVWpVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocVWpVWp = AmpVertexhhTocVWpVWp  +  AmpVertexIRoshhTocVWpVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->conj[VWp] VWp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocVWpVWp = AmpTreehhTocVWpVWp 
 AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp + 2._dp*AmpWavehhTocVWpVWp + 2._dp*AmpVertexhhTocVWpVWp  
Else 
 AmpSumhhTocVWpVWp = AmpTreehhTocVWpVWp + AmpWavehhTocVWpVWp + AmpVertexhhTocVWpVWp
 AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp + AmpWavehhTocVWpVWp + AmpVertexhhTocVWpVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocVWpVWp = AmpTreehhTocVWpVWp
 AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MVWpOS)+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MVWp)+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVWpOS,MVWpOS,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
Else  
  Call SquareAmp_StoVV(Mhh,MVWp,MVWp,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocVWpVWp 
  AmpSum2hhTocVWpVWp = 2._dp*AmpWavehhTocVWpVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVWpOS,MVWpOS,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
Else  
  Call SquareAmp_StoVV(Mhh,MVWp,MVWp,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocVWpVWp 
  AmpSum2hhTocVWpVWp = 2._dp*AmpVertexhhTocVWpVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVWpOS,MVWpOS,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
Else  
  Call SquareAmp_StoVV(Mhh,MVWp,MVWp,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocVWpVWp 
  AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp + 2._dp*AmpWavehhTocVWpVWp + 2._dp*AmpVertexhhTocVWpVWp
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVWpOS,MVWpOS,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
Else  
  Call SquareAmp_StoVV(Mhh,MVWp,MVWp,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocVWpVWp 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp
  Call SquareAmp_StoVV(MhhOS,MVWpOS,MVWpOS,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
  AmpSqTreehhTocVWpVWp = AmpSqhhTocVWpVWp  
  AmpSum2hhTocVWpVWp = + 2._dp*AmpWavehhTocVWpVWp + 2._dp*AmpVertexhhTocVWpVWp
  Call SquareAmp_StoVV(MhhOS,MVWpOS,MVWpOS,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
  AmpSqhhTocVWpVWp = AmpSqhhTocVWpVWp + AmpSqTreehhTocVWpVWp  
Else  
  AmpSum2hhTocVWpVWp = AmpTreehhTocVWpVWp
  Call SquareAmp_StoVV(Mhh,MVWp,MVWp,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
  AmpSqTreehhTocVWpVWp = AmpSqhhTocVWpVWp  
  AmpSum2hhTocVWpVWp = + 2._dp*AmpWavehhTocVWpVWp + 2._dp*AmpVertexhhTocVWpVWp
  Call SquareAmp_StoVV(Mhh,MVWp,MVWp,AmpSumhhTocVWpVWp(:),AmpSum2hhTocVWpVWp(:),AmpSqhhTocVWpVWp) 
  AmpSqhhTocVWpVWp = AmpSqhhTocVWpVWp + AmpSqTreehhTocVWpVWp  
End if  
Else  
  AmpSqhhTocVWpVWp = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTocVWpVWp.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS,MVWpOS,MVWpOS,helfactor*AmpSqhhTocVWpVWp)
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh,MVWp,MVWp,helfactor*AmpSqhhTocVWpVWp)
End if 
If ((Abs(MRPhhTocVWpVWp).gt.1.0E-20_dp).or.(Abs(MRGhhTocVWpVWp).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocVWpVWp).gt.1.0E-20_dp).or.(Abs(MRGhhTocVWpVWp).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPhhTocVWpVWp + MRGhhTocVWpVWp) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPhhTocVWpVWp + MRGhhTocVWpVWp)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! VZ VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_hhToVZVZ(cplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,AmpTreehhToVZVZ)

  Else 
Call Amplitude_Tree_Inert2_hhToVZVZ(ZcplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,AmpTreehhToVZVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,MhhOS,MVZOS,MRPhhToVZVZ,      & 
& MRGhhToVZVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_hhToVZVZ(MLambda,em,gs,ZcplhhVZVZ,MhhOS,MVZOS,MRPhhToVZVZ,     & 
& MRGhhToVZVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,Mhh,MVZ,MRPhhToVZVZ,          & 
& MRGhhToVZVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_hhToVZVZ(MLambda,em,gs,ZcplhhVZVZ,Mhh,MVZ,MRPhhToVZVZ,         & 
& MRGhhToVZVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_hhToVZVZ(cplhhVZVZ,ctcplhhVZVZ,Mhh,Mhh2,MVZ,               & 
& MVZ2,Zfhh,ZfVZ,AmpWavehhToVZVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToVZVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,MVWp,           & 
& MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0VZ,            & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,         & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplG0G0VZVZ1,             & 
& cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexhhToVZVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_hhToVZVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0VZ,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,         & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplG0G0VZVZ1,             & 
& cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRdrhhToVZVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToVZVZ(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,              & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,     & 
& cplhhcHpVWp,cplhhcVWpVWp,ZcplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,   & 
& cplA0A0VZVZ1,cplG0G0VZVZ1,cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,     & 
& cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhToVZVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToVZVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0VZ,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,ZcplhhVZVZ,        & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplG0G0VZVZ1,             & 
& cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhToVZVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToVZVZ(MA0OS,MFdOS,MFeOS,MFuOS,MG0OS,               & 
& MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MG02OS,MH02OS,              & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0A0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,      & 
& cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,     & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,    & 
& cplA0A0VZVZ1,cplG0G0VZVZ1,cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,     & 
& cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhToVZVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_hhToVZVZ(MA0,MFd,MFe,MFu,MG0,MH0,Mhh,MHp,             & 
& MVWp,MVZ,MA02,MFd2,MFe2,MFu2,MG02,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0VZ,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0G0hh,cplG0hhVZ,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,         & 
& cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0A0VZVZ1,cplG0G0VZVZ1,             & 
& cplH0H0VZVZ1,cplhhhhVZVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,cplHpcHpVZVZ1,cplcVWpVWpVZVZ2Q,& 
& cplcVWpVWpVZVZ3Q,cplcVWpVWpVZVZ1Q,AmpVertexIRoshhToVZVZ)

 End if 
 End if 
AmpVertexhhToVZVZ = AmpVertexhhToVZVZ -  AmpVertexIRdrhhToVZVZ! +  AmpVertexIRoshhToVZVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
End if
If (ShiftIRdiv) Then 
AmpVertexhhToVZVZ = AmpVertexhhToVZVZ  +  AmpVertexIRoshhToVZVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->VZ VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToVZVZ = AmpTreehhToVZVZ 
 AmpSum2hhToVZVZ = AmpTreehhToVZVZ + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ  
Else 
 AmpSumhhToVZVZ = AmpTreehhToVZVZ + AmpWavehhToVZVZ + AmpVertexhhToVZVZ
 AmpSum2hhToVZVZ = AmpTreehhToVZVZ + AmpWavehhToVZVZ + AmpVertexhhToVZVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToVZVZ = AmpTreehhToVZVZ
 AmpSum2hhToVZVZ = AmpTreehhToVZVZ 
End if 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MVZOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MVZ)+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*)  
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVZOS,MVZOS,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
Else  
  Call SquareAmp_StoVV(Mhh,MVZ,MVZ,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToVZVZ 
  AmpSum2hhToVZVZ = 2._dp*AmpWavehhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVZOS,MVZOS,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
Else  
  Call SquareAmp_StoVV(Mhh,MVZ,MVZ,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToVZVZ 
  AmpSum2hhToVZVZ = 2._dp*AmpVertexhhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVZOS,MVZOS,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
Else  
  Call SquareAmp_StoVV(Mhh,MVZ,MVZ,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToVZVZ 
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,MVZOS,MVZOS,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
Else  
  Call SquareAmp_StoVV(Mhh,MVZ,MVZ,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToVZVZ 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ
  Call SquareAmp_StoVV(MhhOS,MVZOS,MVZOS,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
  AmpSqTreehhToVZVZ = AmpSqhhToVZVZ  
  AmpSum2hhToVZVZ = + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ
  Call SquareAmp_StoVV(MhhOS,MVZOS,MVZOS,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
  AmpSqhhToVZVZ = AmpSqhhToVZVZ + AmpSqTreehhToVZVZ  
Else  
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ
  Call SquareAmp_StoVV(Mhh,MVZ,MVZ,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
  AmpSqTreehhToVZVZ = AmpSqhhToVZVZ  
  AmpSum2hhToVZVZ = + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ
  Call SquareAmp_StoVV(Mhh,MVZ,MVZ,AmpSumhhToVZVZ(:),AmpSum2hhToVZVZ(:),AmpSqhhToVZVZ) 
  AmpSqhhToVZVZ = AmpSqhhToVZVZ + AmpSqTreehhToVZVZ  
End if  
Else  
  AmpSqhhToVZVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVZVZ.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MVZOS,MVZOS,helfactor*AmpSqhhToVZVZ)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MVZ,MVZ,helfactor*AmpSqhhToVZVZ)
End if 
If ((Abs(MRPhhToVZVZ).gt.1.0E-20_dp).or.(Abs(MRGhhToVZVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToVZVZ).gt.1.0E-20_dp).or.(Abs(MRGhhToVZVZ).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPhhToVZVZ + MRGhhToVZVZ) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPhhToVZVZ + MRGhhToVZVZ)
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

isave = i4 
End If 
!---------------- 
! A0 hh
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToA0hh(MA0OS,MhhOS,MHpOS,MVWpOS,MA02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0hhHpcHp1,cplhhhhHpcHp1,AmpVertexhhToA0hh)

 Else 
Call Amplitude_VERTEX_Inert2_hhToA0hh(MA0OS,MhhOS,MHpOS,MVWpOS,MA02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplA0hhHpcHp1,cplhhhhHpcHp1,AmpVertexhhToA0hh)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToA0hh(MA0,Mhh,MHp,MVWp,MA02,Mhh2,MHp2,MVWp2,          & 
& cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,    & 
& cplA0hhHpcHp1,cplhhhhHpcHp1,AmpVertexhhToA0hh)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->A0 hh -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToA0hh = 0._dp 
 AmpSum2hhToA0hh = 0._dp  
Else 
 AmpSumhhToA0hh = AmpVertexhhToA0hh + AmpWavehhToA0hh
 AmpSum2hhToA0hh = AmpVertexhhToA0hh + AmpWavehhToA0hh 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MA0OS)+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MA0)+Abs(Mhh))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MA0OS,MhhOS,AmpSumhhToA0hh,AmpSum2hhToA0hh,AmpSqhhToA0hh) 
Else  
  Call SquareAmp_StoSS(Mhh,MA0,Mhh,AmpSumhhToA0hh,AmpSum2hhToA0hh,AmpSqhhToA0hh) 
End if  
Else  
  AmpSqhhToA0hh = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToA0hh.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MA0OS,MhhOS,helfactor*AmpSqhhToA0hh)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MA0,Mhh,helfactor*AmpSqhhToA0hh)
End if 
If ((Abs(MRPhhToA0hh).gt.1.0E-20_dp).or.(Abs(MRGhhToA0hh).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! A0 VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToA0VP(MA0OS,MhhOS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexhhToA0VP)

 Else 
Call Amplitude_VERTEX_Inert2_hhToA0VP(MA0OS,MhhOS,MHpOS,MVP,MVWpOS,MA02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplA0HpcVWpVP1,cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexhhToA0VP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToA0VP(MA0,Mhh,MHp,MVP,MVWp,MA02,Mhh2,MHp2,            & 
& MVP2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplA0HpcVWpVP1,           & 
& cplA0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,AmpVertexhhToA0VP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->A0 VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToA0VP = 0._dp 
 AmpSum2hhToA0VP = 0._dp  
Else 
 AmpSumhhToA0VP = AmpVertexhhToA0VP + AmpWavehhToA0VP
 AmpSum2hhToA0VP = AmpVertexhhToA0VP + AmpWavehhToA0VP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MA0OS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MA0)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MA0OS,0._dp,AmpSumhhToA0VP(:),AmpSum2hhToA0VP(:),AmpSqhhToA0VP) 
Else  
  Call SquareAmp_StoSV(Mhh,MA0,MVP,AmpSumhhToA0VP(:),AmpSum2hhToA0VP(:),AmpSqhhToA0VP) 
End if  
Else  
  AmpSqhhToA0VP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToA0VP.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MA0OS,0._dp,helfactor*AmpSqhhToA0VP)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MA0,MVP,helfactor*AmpSqhhToA0VP)
End if 
If ((Abs(MRPhhToA0VP).gt.1.0E-20_dp).or.(Abs(MRGhhToA0VP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! A0 VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToA0VZ(MA0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexhhToA0VZ)

 Else 
Call Amplitude_VERTEX_Inert2_hhToA0VZ(MA0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MA02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplA0HpcVWpVZ1,cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexhhToA0VZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToA0VZ(MA0,Mhh,MHp,MVWp,MVZ,MA02,Mhh2,MHp2,            & 
& MVWp2,MVZ2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplA0HpcVWpVZ1,           & 
& cplA0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexhhToA0VZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->A0 VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToA0VZ = 0._dp 
 AmpSum2hhToA0VZ = 0._dp  
Else 
 AmpSumhhToA0VZ = AmpVertexhhToA0VZ + AmpWavehhToA0VZ
 AmpSum2hhToA0VZ = AmpVertexhhToA0VZ + AmpWavehhToA0VZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MA0OS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MA0)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MA0OS,MVZOS,AmpSumhhToA0VZ(:),AmpSum2hhToA0VZ(:),AmpSqhhToA0VZ) 
Else  
  Call SquareAmp_StoSV(Mhh,MA0,MVZ,AmpSumhhToA0VZ(:),AmpSum2hhToA0VZ(:),AmpSqhhToA0VZ) 
End if  
Else  
  AmpSqhhToA0VZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToA0VZ.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MA0OS,MVZOS,helfactor*AmpSqhhToA0VZ)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MA0,MVZ,helfactor*AmpSqhhToA0VZ)
End if 
If ((Abs(MRPhhToA0VZ).gt.1.0E-20_dp).or.(Abs(MRGhhToA0VZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! Fv bar(Fv)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToFvcFv(MFeOS,MhhOS,MHpOS,MVWpOS,MVZOS,MFe2OS,         & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,          & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,           & 
& cplhhVZVZ,AmpVertexhhToFvcFv)

 Else 
Call Amplitude_VERTEX_Inert2_hhToFvcFv(MFeOS,MhhOS,MHpOS,MVWpOS,MVZOS,MFe2OS,         & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,          & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,           & 
& cplhhVZVZ,AmpVertexhhToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToFvcFv(MFe,Mhh,MHp,MVWp,MVZ,MFe2,Mhh2,MHp2,           & 
& MVWp2,MVZ2,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFvFeVWpL,               & 
& cplcFvFeVWpR,cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,          & 
& cplcFeFvcVWpR,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,               & 
& AmpVertexhhToFvcFv)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Fv bar[Fv] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToFvcFv = 0._dp 
 AmpSum2hhToFvcFv = 0._dp  
Else 
 AmpSumhhToFvcFv = AmpVertexhhToFvcFv + AmpWavehhToFvcFv
 AmpSum2hhToFvcFv = AmpVertexhhToFvcFv + AmpWavehhToFvcFv 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(0._dp)+Abs(0._dp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS,0._dp,0._dp,AmpSumhhToFvcFv(:,gt2, gt3),AmpSum2hhToFvcFv(:,gt2, gt3),AmpSqhhToFvcFv(gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh,0._dp,0._dp,AmpSumhhToFvcFv(:,gt2, gt3),AmpSum2hhToFvcFv(:,gt2, gt3),AmpSqhhToFvcFv(gt2, gt3)) 
End if  
Else  
  AmpSqhhToFvcFv(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhToFvcFv(gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,0._dp,0._dp,helfactor*AmpSqhhToFvcFv(gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,0._dp,0._dp,helfactor*AmpSqhhToFvcFv(gt2, gt3))
End if 
If ((Abs(MRPhhToFvcFv(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhToFvcFv(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

    End do
  End do
isave = i4 
!---------------- 
! H0 hh
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToH0hh(MH0OS,MhhOS,MHpOS,MVWpOS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplH0hhHpcHp1,cplhhhhHpcHp1,AmpVertexhhToH0hh)

 Else 
Call Amplitude_VERTEX_Inert2_hhToH0hh(MH0OS,MhhOS,MHpOS,MVWpOS,MH02OS,Mhh2OS,         & 
& MHp2OS,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,              & 
& cplhhcHpVWp,cplhhcVWpVWp,cplH0hhHpcHp1,cplhhhhHpcHp1,AmpVertexhhToH0hh)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToH0hh(MH0,Mhh,MHp,MVWp,MH02,Mhh2,MHp2,MVWp2,          & 
& cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,    & 
& cplH0hhHpcHp1,cplhhhhHpcHp1,AmpVertexhhToH0hh)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->H0 hh -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToH0hh = 0._dp 
 AmpSum2hhToH0hh = 0._dp  
Else 
 AmpSumhhToH0hh = AmpVertexhhToH0hh + AmpWavehhToH0hh
 AmpSum2hhToH0hh = AmpVertexhhToH0hh + AmpWavehhToH0hh 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MH0OS)+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MH0)+Abs(Mhh))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS,MH0OS,MhhOS,AmpSumhhToH0hh,AmpSum2hhToH0hh,AmpSqhhToH0hh) 
Else  
  Call SquareAmp_StoSS(Mhh,MH0,Mhh,AmpSumhhToH0hh,AmpSum2hhToH0hh,AmpSqhhToH0hh) 
End if  
Else  
  AmpSqhhToH0hh = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToH0hh.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MH0OS,MhhOS,helfactor*AmpSqhhToH0hh)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MH0,Mhh,helfactor*AmpSqhhToH0hh)
End if 
If ((Abs(MRPhhToH0hh).gt.1.0E-20_dp).or.(Abs(MRGhhToH0hh).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! H0 VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToH0VP(MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MH02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexhhToH0VP)

 Else 
Call Amplitude_VERTEX_Inert2_hhToH0VP(MH0OS,MhhOS,MHpOS,MVP,MVWpOS,MH02OS,            & 
& Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,               & 
& cplcVWpVPVWp,cplH0HpcVWpVP1,cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,              & 
& AmpVertexhhToH0VP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToH0VP(MH0,Mhh,MHp,MVP,MVWp,MH02,Mhh2,MHp2,            & 
& MVP2,MVWp2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplH0HpcVWpVP1,           & 
& cplH0cHpVPVWp1,cplhhHpcVWpVP1,cplhhcHpVPVWp1,AmpVertexhhToH0VP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->H0 VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToH0VP = 0._dp 
 AmpSum2hhToH0VP = 0._dp  
Else 
 AmpSumhhToH0VP = AmpVertexhhToH0VP + AmpWavehhToH0VP
 AmpSum2hhToH0VP = AmpVertexhhToH0VP + AmpWavehhToH0VP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MH0OS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MH0)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MH0OS,0._dp,AmpSumhhToH0VP(:),AmpSum2hhToH0VP(:),AmpSqhhToH0VP) 
Else  
  Call SquareAmp_StoSV(Mhh,MH0,MVP,AmpSumhhToH0VP(:),AmpSum2hhToH0VP(:),AmpSqhhToH0VP) 
End if  
Else  
  AmpSqhhToH0VP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToH0VP.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MH0OS,0._dp,helfactor*AmpSqhhToH0VP)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MH0,MVP,helfactor*AmpSqhhToH0VP)
End if 
If ((Abs(MRPhhToH0VP).gt.1.0E-20_dp).or.(Abs(MRGhhToH0VP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! H0 VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToH0VZ(MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexhhToH0VZ)

 Else 
Call Amplitude_VERTEX_Inert2_hhToH0VZ(MH0OS,MhhOS,MHpOS,MVWpOS,MVZOS,MH02OS,          & 
& Mhh2OS,MHp2OS,MVWp2OS,MVZ2OS,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,            & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplH0HpcVWpVZ1,cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,              & 
& AmpVertexhhToH0VZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToH0VZ(MH0,Mhh,MHp,MVWp,MVZ,MH02,Mhh2,MHp2,            & 
& MVWp2,MVZ2,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,      & 
& cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplH0HpcVWpVZ1,           & 
& cplH0cHpVWpVZ1,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexhhToH0VZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->H0 VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToH0VZ = 0._dp 
 AmpSum2hhToH0VZ = 0._dp  
Else 
 AmpSumhhToH0VZ = AmpVertexhhToH0VZ + AmpWavehhToH0VZ
 AmpSum2hhToH0VZ = AmpVertexhhToH0VZ + AmpWavehhToH0VZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MH0OS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MH0)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MH0OS,MVZOS,AmpSumhhToH0VZ(:),AmpSum2hhToH0VZ(:),AmpSqhhToH0VZ) 
Else  
  Call SquareAmp_StoSV(Mhh,MH0,MVZ,AmpSumhhToH0VZ(:),AmpSum2hhToH0VZ(:),AmpSqhhToH0VZ) 
End if  
Else  
  AmpSqhhToH0VZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToH0VZ.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MH0OS,MVZOS,helfactor*AmpSqhhToH0VZ)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MH0,MVZ,helfactor*AmpSqhhToH0VZ)
End if 
If ((Abs(MRPhhToH0VZ).gt.1.0E-20_dp).or.(Abs(MRGhhToH0VZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! hh VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhTohhVP(MFdOS,MFeOS,MFuOS,MhhOS,MHpOS,MVP,              & 
& MVWpOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,             & 
& cplcgWCgWChh,cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,             & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,         & 
& AmpVertexhhTohhVP)

 Else 
Call Amplitude_VERTEX_Inert2_hhTohhVP(MFdOS,MFeOS,MFuOS,MhhOS,MHpOS,MVP,              & 
& MVWpOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,             & 
& cplcgWCgWChh,cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,             & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,         & 
& AmpVertexhhTohhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTohhVP(MFd,MFe,MFu,Mhh,MHp,MVP,MVWp,MFd2,              & 
& MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,cplcgWCgWCVP,           & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,AmpVertexhhTohhVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->hh VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTohhVP = 0._dp 
 AmpSum2hhTohhVP = 0._dp  
Else 
 AmpSumhhTohhVP = AmpVertexhhTohhVP + AmpWavehhTohhVP
 AmpSum2hhTohhVP = AmpVertexhhTohhVP + AmpWavehhTohhVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MhhOS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(Mhh)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MhhOS,0._dp,AmpSumhhTohhVP(:),AmpSum2hhTohhVP(:),AmpSqhhTohhVP) 
Else  
  Call SquareAmp_StoSV(Mhh,Mhh,MVP,AmpSumhhTohhVP(:),AmpSum2hhTohhVP(:),AmpSqhhTohhVP) 
End if  
Else  
  AmpSqhhTohhVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTohhVP.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MhhOS,0._dp,helfactor*AmpSqhhTohhVP)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,Mhh,MVP,helfactor*AmpSqhhTohhVP)
End if 
If ((Abs(MRPhhTohhVP).gt.1.0E-20_dp).or.(Abs(MRGhhTohhVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! hh VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhTohhVZ(MA0OS,MFdOS,MFeOS,MFuOS,MH0OS,MhhOS,            & 
& MHpOS,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,           & 
& MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,              & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,            & 
& cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexhhTohhVZ)

 Else 
Call Amplitude_VERTEX_Inert2_hhTohhVZ(MA0OS,MFdOS,MFeOS,MFuOS,MH0OS,MhhOS,            & 
& MHpOS,MVWpOS,MVZOS,MA02OS,MFd2OS,MFe2OS,MFu2OS,MH02OS,Mhh2OS,MHp2OS,MVWp2OS,           & 
& MVZ2OS,cplA0A0hh,cplA0H0hh,cplA0H0VZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,              & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,            & 
& cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,     & 
& cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexhhTohhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhTohhVZ(MA0,MFd,MFe,MFu,MH0,Mhh,MHp,MVWp,               & 
& MVZ,MA02,MFd2,MFe2,MFu2,MH02,Mhh2,MHp2,MVWp2,MVZ2,cplA0A0hh,cplA0H0hh,cplA0H0VZ,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWpgWphh,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVZ,cplH0H0hh,cplhhHpcHp,              & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,               & 
& cplcVWpVWpVZ,cplhhHpcVWpVZ1,cplhhcHpVWpVZ1,AmpVertexhhTohhVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->hh VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTohhVZ = 0._dp 
 AmpSum2hhTohhVZ = 0._dp  
Else 
 AmpSumhhTohhVZ = AmpVertexhhTohhVZ + AmpWavehhTohhVZ
 AmpSum2hhTohhVZ = AmpVertexhhTohhVZ + AmpWavehhTohhVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(MhhOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(Mhh)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS,MhhOS,MVZOS,AmpSumhhTohhVZ(:),AmpSum2hhTohhVZ(:),AmpSqhhTohhVZ) 
Else  
  Call SquareAmp_StoSV(Mhh,Mhh,MVZ,AmpSumhhTohhVZ(:),AmpSum2hhTohhVZ(:),AmpSqhhTohhVZ) 
End if  
Else  
  AmpSqhhTohhVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTohhVZ.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,MhhOS,MVZOS,helfactor*AmpSqhhTohhVZ)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,Mhh,MVZ,helfactor*AmpSqhhTohhVZ)
End if 
If ((Abs(MRPhhTohhVZ).gt.1.0E-20_dp).or.(Abs(MRGhhTohhVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VG VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToVGVG(MFdOS,MFuOS,MhhOS,MVG,MFd2OS,MFu2OS,            & 
& Mhh2OS,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

 Else 
Call Amplitude_VERTEX_Inert2_hhToVGVG(MFdOS,MFuOS,MhhOS,MVG,MFd2OS,MFu2OS,            & 
& Mhh2OS,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToVGVG(MFd,MFu,Mhh,MVG,MFd2,MFu2,Mhh2,MVG2,            & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->VG VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToVGVG = 0._dp 
 AmpSum2hhToVGVG = 0._dp  
Else 
 AmpSumhhToVGVG = AmpVertexhhToVGVG + AmpWavehhToVGVG
 AmpSum2hhToVGVG = AmpVertexhhToVGVG + AmpWavehhToVGVG 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MVG)+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,0._dp,0._dp,AmpSumhhToVGVG(:),AmpSum2hhToVGVG(:),AmpSqhhToVGVG) 
Else  
  Call SquareAmp_StoVV(Mhh,MVG,MVG,AmpSumhhToVGVG(:),AmpSum2hhToVGVG(:),AmpSqhhToVGVG) 
End if  
Else  
  AmpSqhhToVGVG = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVGVG.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 8._dp*GammaTPS(MhhOS,0._dp,0._dp,helfactor*AmpSqhhToVGVG)
Else 
  gP1Lhh(gt1,i4) = 8._dp*GammaTPS(Mhh,MVG,MVG,helfactor*AmpSqhhToVGVG)
End if 
If ((Abs(MRPhhToVGVG).gt.1.0E-20_dp).or.(Abs(MRGhhToVGVG).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VP VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToVPVP(MFdOS,MFeOS,MFuOS,MhhOS,MHpOS,MVP,              & 
& MVWpOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,             & 
& cplcgWCgWChh,cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,             & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,         & 
& cplHpcHpVPVP1,cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,AmpVertexhhToVPVP)

 Else 
Call Amplitude_VERTEX_Inert2_hhToVPVP(MFdOS,MFeOS,MFuOS,MhhOS,MHpOS,MVP,              & 
& MVWpOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,             & 
& cplcgWCgWChh,cplcgWCgWCVP,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,             & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,         & 
& cplHpcHpVPVP1,cplcVWpVPVPVWp3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,AmpVertexhhToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToVPVP(MFd,MFe,MFu,Mhh,MHp,MVP,MVWp,MFd2,              & 
& MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWCgWChh,cplcgWCgWCVP,           & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,    & 
& cplcVWpVPVWp,cplhhHpcVWpVP1,cplhhcHpVPVWp1,cplHpcHpVPVP1,cplcVWpVPVPVWp3Q,             & 
& cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,AmpVertexhhToVPVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->VP VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToVPVP = 0._dp 
 AmpSum2hhToVPVP = 0._dp  
Else 
 AmpSumhhToVPVP = AmpVertexhhToVPVP + AmpWavehhToVPVP
 AmpSum2hhToVPVP = AmpVertexhhToVPVP + AmpWavehhToVPVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MVP)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,0._dp,0._dp,AmpSumhhToVPVP(:),AmpSum2hhToVPVP(:),AmpSqhhToVPVP) 
Else  
  Call SquareAmp_StoVV(Mhh,MVP,MVP,AmpSumhhToVPVP(:),AmpSum2hhToVPVP(:),AmpSqhhToVPVP) 
End if  
Else  
  AmpSqhhToVPVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVPVP.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS,0._dp,0._dp,helfactor*AmpSqhhToVPVP)
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh,MVP,MVP,helfactor*AmpSqhhToVPVP)
End if 
If ((Abs(MRPhhToVPVP).gt.1.0E-20_dp).or.(Abs(MRGhhToVPVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! VP VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_hhToVPVZ(MFdOS,MFeOS,MFuOS,MhhOS,MHpOS,MVP,              & 
& MVWpOS,MVZOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplcFdFdhhL,       & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,              & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp,           & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,    & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,       & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,         & 
& cplcVWpVPVWpVZ1Q,AmpVertexhhToVPVZ)

 Else 
Call Amplitude_VERTEX_Inert2_hhToVPVZ(MFdOS,MFeOS,MFuOS,MhhOS,MHpOS,MVP,              & 
& MVWpOS,MVZOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHp2OS,MVP2,MVWp2OS,MVZ2OS,cplcFdFdhhL,       & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,              & 
& cplcgWpgWpVP,cplcgWpgWpVZ,cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp,           & 
& cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,    & 
& cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,       & 
& cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpVPVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,         & 
& cplcVWpVPVWpVZ1Q,AmpVertexhhToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_hhToVPVZ(MFd,MFe,MFu,Mhh,MHp,MVP,MVWp,MVZ,               & 
& MFd2,MFe2,MFu2,Mhh2,MHp2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,          & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWpgWphh,cplcgWpgWpVP,cplcgWpgWpVZ,            & 
& cplcgWCgWChh,cplcgWCgWCVP,cplcgWCgWCVZ,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,             & 
& cplhhcVWpVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVPVWp,cplcVWpVPVWp,   & 
& cplcHpVWpVZ,cplcVWpVWpVZ,cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,  & 
& cplHpcHpVPVZ1,cplcVWpVPVWpVZ3Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ1Q,AmpVertexhhToVPVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->VP VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToVPVZ = 0._dp 
 AmpSum2hhToVPVZ = 0._dp  
Else 
 AmpSumhhToVPVZ = AmpVertexhhToVPVZ + AmpWavehhToVPVZ
 AmpSum2hhToVPVZ = AmpVertexhhToVPVZ + AmpWavehhToVPVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS).gt.(Abs(0.)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh).gt.(Abs(MVP)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS,0._dp,MVZOS,AmpSumhhToVPVZ(:),AmpSum2hhToVPVZ(:),AmpSqhhToVPVZ) 
Else  
  Call SquareAmp_StoVV(Mhh,MVP,MVZ,AmpSumhhToVPVZ(:),AmpSum2hhToVPVZ(:),AmpSqhhToVPVZ) 
End if  
Else  
  AmpSqhhToVPVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVPVZ.eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS,0._dp,MVZOS,helfactor*AmpSqhhToVPVZ)
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh,MVP,MVZ,helfactor*AmpSqhhToVPVZ)
End if 
If ((Abs(MRPhhToVPVZ).gt.1.0E-20_dp).or.(Abs(MRGhhToVPVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

isave = i4 
End Subroutine OneLoopDecay_hh

End Module Wrapper_OneLoopDecay_hh_Inert2
