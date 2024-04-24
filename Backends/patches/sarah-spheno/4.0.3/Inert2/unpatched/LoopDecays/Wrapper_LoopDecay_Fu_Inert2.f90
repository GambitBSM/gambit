! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Fu_Inert2
Use Model_Data_Inert2 
Use Kinematics 
Use OneLoopDecay_Fu_Inert2 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Fu(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,              & 
& MFe2OS,MG0OS,MG02OS,MhhOS,Mhh2OS,MA0OS,MA02OS,MH0OS,MH02OS,MVZOS,MVZ2OS,               & 
& MVWpOS,MVWp2OS,ZPOS,ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Ye,Yd,Yu,MHD2,MHU2,v,dg1,dg2,dg3,dYe,dYd,dYu,dlam5,dMHD2,dMHU2,dlam1,dlam4,            & 
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

Complex(dp),Intent(in) :: cplA0cHpVWp(2),cplA0HpcHp(2,2),cplA0HpcVWp(2),cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),      & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),  & 
& cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),& 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),           & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),& 
& cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpVPVWp,          & 
& cplcVWpVWpVZ,cplG0cHpVWp(2),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),cplH0cHpVWp(2),         & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhhhhh,cplhhHpcHp(2,2),  & 
& cplhhHpcVWp(2),cplhhVZVZ,cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplHpcVWpVP(2),               & 
& cplHpcVWpVZ(2),cplVGVGVG,ctcplcFuFdHpL(3,3,2),ctcplcFuFdHpR(3,3,2),ctcplcFuFdVWpL(3,3),& 
& ctcplcFuFdVWpR(3,3),ctcplcFuFuG0L(3,3),ctcplcFuFuG0R(3,3),ctcplcFuFuhhL(3,3),          & 
& ctcplcFuFuhhR(3,3),ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),           & 
& ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3),GcplcFuFdHpL(3,3,2),          & 
& GcplcFuFdHpR(3,3,2),GcplcHpVPVWp(2),GcplHpcVWpVP(2),GosZcplcFuFdHpL(3,3,2),            & 
& GosZcplcFuFdHpR(3,3,2),GosZcplcHpVPVWp(2),GosZcplHpcVWpVP(2),GZcplcFuFdHpL(3,3,2),     & 
& GZcplcFuFdHpR(3,3,2),GZcplcHpVPVWp(2),GZcplHpcVWpVP(2),ZcplA0cHpVWp(2),ZcplA0HpcHp(2,2),& 
& ZcplA0HpcVWp(2),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),ZcplcFdFdVPL(3,3),ZcplcFdFdVPR(3,3),& 
& ZcplcFdFucHpL(3,3,2),ZcplcFdFucHpR(3,3,2),ZcplcFdFucVWpL(3,3),ZcplcFdFucVWpR(3,3),     & 
& ZcplcFuFdHpL(3,3,2),ZcplcFuFdHpR(3,3,2),ZcplcFuFdVWpL(3,3),ZcplcFuFdVWpR(3,3),         & 
& ZcplcFuFuG0L(3,3),ZcplcFuFuG0R(3,3),ZcplcFuFuhhL(3,3),ZcplcFuFuhhR(3,3),               & 
& ZcplcFuFuVGL(3,3),ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),               & 
& ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcHpVPVWp(2),ZcplcVWpVPVWp,ZcplH0cHpVWp(2),     & 
& ZcplH0HpcHp(2,2),ZcplH0HpcVWp(2),ZcplHpcHpVP(2,2),ZcplHpcVWpVP(2),ZcplVGVGVG

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
Real(dp), Intent(out) :: gP1LFu(3,24) 
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
Real(dp) :: MRPFuToFdHp(3,3,2),MRGFuToFdHp(3,3,2), MRPZFuToFdHp(3,3,2),MRGZFuToFdHp(3,3,2) 
Real(dp) :: MVPFuToFdHp(3,3,2) 
Real(dp) :: RMsqTreeFuToFdHp(3,3,2),RMsqWaveFuToFdHp(3,3,2),RMsqVertexFuToFdHp(3,3,2) 
Complex(dp) :: AmpTreeFuToFdHp(2,3,3,2),AmpWaveFuToFdHp(2,3,3,2)=(0._dp,0._dp),AmpVertexFuToFdHp(2,3,3,2)& 
 & ,AmpVertexIRosFuToFdHp(2,3,3,2),AmpVertexIRdrFuToFdHp(2,3,3,2), AmpSumFuToFdHp(2,3,3,2), AmpSum2FuToFdHp(2,3,3,2) 
Complex(dp) :: AmpTreeZFuToFdHp(2,3,3,2),AmpWaveZFuToFdHp(2,3,3,2),AmpVertexZFuToFdHp(2,3,3,2) 
Real(dp) :: AmpSqFuToFdHp(3,3,2),  AmpSqTreeFuToFdHp(3,3,2) 
Real(dp) :: MRPFuToFdVWp(3,3),MRGFuToFdVWp(3,3), MRPZFuToFdVWp(3,3),MRGZFuToFdVWp(3,3) 
Real(dp) :: MVPFuToFdVWp(3,3) 
Real(dp) :: RMsqTreeFuToFdVWp(3,3),RMsqWaveFuToFdVWp(3,3),RMsqVertexFuToFdVWp(3,3) 
Complex(dp) :: AmpTreeFuToFdVWp(4,3,3),AmpWaveFuToFdVWp(4,3,3)=(0._dp,0._dp),AmpVertexFuToFdVWp(4,3,3)& 
 & ,AmpVertexIRosFuToFdVWp(4,3,3),AmpVertexIRdrFuToFdVWp(4,3,3), AmpSumFuToFdVWp(4,3,3), AmpSum2FuToFdVWp(4,3,3) 
Complex(dp) :: AmpTreeZFuToFdVWp(4,3,3),AmpWaveZFuToFdVWp(4,3,3),AmpVertexZFuToFdVWp(4,3,3) 
Real(dp) :: AmpSqFuToFdVWp(3,3),  AmpSqTreeFuToFdVWp(3,3) 
Real(dp) :: MRPFuToFuhh(3,3),MRGFuToFuhh(3,3), MRPZFuToFuhh(3,3),MRGZFuToFuhh(3,3) 
Real(dp) :: MVPFuToFuhh(3,3) 
Real(dp) :: RMsqTreeFuToFuhh(3,3),RMsqWaveFuToFuhh(3,3),RMsqVertexFuToFuhh(3,3) 
Complex(dp) :: AmpTreeFuToFuhh(2,3,3),AmpWaveFuToFuhh(2,3,3)=(0._dp,0._dp),AmpVertexFuToFuhh(2,3,3)& 
 & ,AmpVertexIRosFuToFuhh(2,3,3),AmpVertexIRdrFuToFuhh(2,3,3), AmpSumFuToFuhh(2,3,3), AmpSum2FuToFuhh(2,3,3) 
Complex(dp) :: AmpTreeZFuToFuhh(2,3,3),AmpWaveZFuToFuhh(2,3,3),AmpVertexZFuToFuhh(2,3,3) 
Real(dp) :: AmpSqFuToFuhh(3,3),  AmpSqTreeFuToFuhh(3,3) 
Real(dp) :: MRPFuToFuVZ(3,3),MRGFuToFuVZ(3,3), MRPZFuToFuVZ(3,3),MRGZFuToFuVZ(3,3) 
Real(dp) :: MVPFuToFuVZ(3,3) 
Real(dp) :: RMsqTreeFuToFuVZ(3,3),RMsqWaveFuToFuVZ(3,3),RMsqVertexFuToFuVZ(3,3) 
Complex(dp) :: AmpTreeFuToFuVZ(4,3,3),AmpWaveFuToFuVZ(4,3,3)=(0._dp,0._dp),AmpVertexFuToFuVZ(4,3,3)& 
 & ,AmpVertexIRosFuToFuVZ(4,3,3),AmpVertexIRdrFuToFuVZ(4,3,3), AmpSumFuToFuVZ(4,3,3), AmpSum2FuToFuVZ(4,3,3) 
Complex(dp) :: AmpTreeZFuToFuVZ(4,3,3),AmpWaveZFuToFuVZ(4,3,3),AmpVertexZFuToFuVZ(4,3,3) 
Real(dp) :: AmpSqFuToFuVZ(3,3),  AmpSqTreeFuToFuVZ(3,3) 
Real(dp) :: MRPFuToFuA0(3,3),MRGFuToFuA0(3,3), MRPZFuToFuA0(3,3),MRGZFuToFuA0(3,3) 
Real(dp) :: MVPFuToFuA0(3,3) 
Real(dp) :: RMsqTreeFuToFuA0(3,3),RMsqWaveFuToFuA0(3,3),RMsqVertexFuToFuA0(3,3) 
Complex(dp) :: AmpTreeFuToFuA0(2,3,3),AmpWaveFuToFuA0(2,3,3)=(0._dp,0._dp),AmpVertexFuToFuA0(2,3,3)& 
 & ,AmpVertexIRosFuToFuA0(2,3,3),AmpVertexIRdrFuToFuA0(2,3,3), AmpSumFuToFuA0(2,3,3), AmpSum2FuToFuA0(2,3,3) 
Complex(dp) :: AmpTreeZFuToFuA0(2,3,3),AmpWaveZFuToFuA0(2,3,3),AmpVertexZFuToFuA0(2,3,3) 
Real(dp) :: AmpSqFuToFuA0(3,3),  AmpSqTreeFuToFuA0(3,3) 
Real(dp) :: MRPFuToFuH0(3,3),MRGFuToFuH0(3,3), MRPZFuToFuH0(3,3),MRGZFuToFuH0(3,3) 
Real(dp) :: MVPFuToFuH0(3,3) 
Real(dp) :: RMsqTreeFuToFuH0(3,3),RMsqWaveFuToFuH0(3,3),RMsqVertexFuToFuH0(3,3) 
Complex(dp) :: AmpTreeFuToFuH0(2,3,3),AmpWaveFuToFuH0(2,3,3)=(0._dp,0._dp),AmpVertexFuToFuH0(2,3,3)& 
 & ,AmpVertexIRosFuToFuH0(2,3,3),AmpVertexIRdrFuToFuH0(2,3,3), AmpSumFuToFuH0(2,3,3), AmpSum2FuToFuH0(2,3,3) 
Complex(dp) :: AmpTreeZFuToFuH0(2,3,3),AmpWaveZFuToFuH0(2,3,3),AmpVertexZFuToFuH0(2,3,3) 
Real(dp) :: AmpSqFuToFuH0(3,3),  AmpSqTreeFuToFuH0(3,3) 
Real(dp) :: MRPFuToFuVG(3,3),MRGFuToFuVG(3,3), MRPZFuToFuVG(3,3),MRGZFuToFuVG(3,3) 
Real(dp) :: MVPFuToFuVG(3,3) 
Real(dp) :: RMsqTreeFuToFuVG(3,3),RMsqWaveFuToFuVG(3,3),RMsqVertexFuToFuVG(3,3) 
Complex(dp) :: AmpTreeFuToFuVG(4,3,3),AmpWaveFuToFuVG(4,3,3)=(0._dp,0._dp),AmpVertexFuToFuVG(4,3,3)& 
 & ,AmpVertexIRosFuToFuVG(4,3,3),AmpVertexIRdrFuToFuVG(4,3,3), AmpSumFuToFuVG(4,3,3), AmpSum2FuToFuVG(4,3,3) 
Complex(dp) :: AmpTreeZFuToFuVG(4,3,3),AmpWaveZFuToFuVG(4,3,3),AmpVertexZFuToFuVG(4,3,3) 
Real(dp) :: AmpSqFuToFuVG(3,3),  AmpSqTreeFuToFuVG(3,3) 
Real(dp) :: MRPFuToFuVP(3,3),MRGFuToFuVP(3,3), MRPZFuToFuVP(3,3),MRGZFuToFuVP(3,3) 
Real(dp) :: MVPFuToFuVP(3,3) 
Real(dp) :: RMsqTreeFuToFuVP(3,3),RMsqWaveFuToFuVP(3,3),RMsqVertexFuToFuVP(3,3) 
Complex(dp) :: AmpTreeFuToFuVP(4,3,3),AmpWaveFuToFuVP(4,3,3)=(0._dp,0._dp),AmpVertexFuToFuVP(4,3,3)& 
 & ,AmpVertexIRosFuToFuVP(4,3,3),AmpVertexIRdrFuToFuVP(4,3,3), AmpSumFuToFuVP(4,3,3), AmpSum2FuToFuVP(4,3,3) 
Complex(dp) :: AmpTreeZFuToFuVP(4,3,3),AmpWaveZFuToFuVP(4,3,3),AmpVertexZFuToFuVP(4,3,3) 
Real(dp) :: AmpSqFuToFuVP(3,3),  AmpSqTreeFuToFuVP(3,3) 
Write(*,*) "Calculating one-loop decays of Fu " 
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
! Fd Hp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FuToFdHp(cplcFuFdHpL,cplcFuFdHpR,MFd,MFu,MHp,              & 
& MFd2,MFu2,MHp2,AmpTreeFuToFdHp)

  Else 
Call Amplitude_Tree_Inert2_FuToFdHp(ZcplcFuFdHpL,ZcplcFuFdHpR,MFd,MFu,MHp,            & 
& MFd2,MFu2,MHp2,AmpTreeFuToFdHp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FuToFdHp(MLambda,em,gs,cplcFuFdHpL,cplcFuFdHpR,MFdOS,          & 
& MFuOS,MHpOS,MRPFuToFdHp,MRGFuToFdHp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FuToFdHp(MLambda,em,gs,ZcplcFuFdHpL,ZcplcFuFdHpR,              & 
& MFdOS,MFuOS,MHpOS,MRPFuToFdHp,MRGFuToFdHp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FuToFdHp(MLambda,em,gs,cplcFuFdHpL,cplcFuFdHpR,MFd,            & 
& MFu,MHp,MRPFuToFdHp,MRGFuToFdHp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FuToFdHp(MLambda,em,gs,ZcplcFuFdHpL,ZcplcFuFdHpR,              & 
& MFd,MFu,MHp,MRPFuToFdHp,MRGFuToFdHp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FuToFdHp(cplcFuFdHpL,cplcFuFdHpR,ctcplcFuFdHpL,            & 
& ctcplcFuFdHpR,MFd,MFd2,MFu,MFu2,MHp,MHp2,ZfDL,ZfDR,ZfHp,ZfUL,ZfUR,AmpWaveFuToFdHp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFdHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0HpcVWp,cplhhHpcHp,cplhhHpcVWp,    & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,AmpVertexFuToFdHp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FuToFdHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0HpcVWp,cplhhHpcHp,cplhhHpcVWp,    & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,AmpVertexIRdrFuToFdHp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdHp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,ZcplcFuFdHpL,ZcplcFuFdHpR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,      & 
& AmpVertexIRosFuToFdHp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,ZcplcFuFdHpL,ZcplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0HpcVWp,cplhhHpcHp,cplhhHpcVWp,    & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,AmpVertexIRosFuToFdHp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdHp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0HpcVWp,cplhhHpcHp,cplhhHpcVWp,cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,      & 
& AmpVertexIRosFuToFdHp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0HpcVWp,cplhhHpcHp,cplhhHpcVWp,    & 
& cplHpcHpVP,cplHpcVWpVP,cplHpcHpVZ,cplHpcVWpVZ,AmpVertexIRosFuToFdHp)

 End if 
 End if 
AmpVertexFuToFdHp = AmpVertexFuToFdHp -  AmpVertexIRdrFuToFdHp! +  AmpVertexIRosFuToFdHp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFdHp=0._dp 
AmpVertexZFuToFdHp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdHp(1,gt2,:,:) = AmpWaveZFuToFdHp(1,gt2,:,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFdHp(1,gt1,:,:) 
AmpVertexZFuToFdHp(1,gt2,:,:)= AmpVertexZFuToFdHp(1,gt2,:,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFdHp(1,gt1,:,:) 
AmpWaveZFuToFdHp(2,gt2,:,:) = AmpWaveZFuToFdHp(2,gt2,:,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFdHp(2,gt1,:,:) 
AmpVertexZFuToFdHp(2,gt2,:,:)= AmpVertexZFuToFdHp(2,gt2,:,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFdHp(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFdHp=AmpWaveZFuToFdHp 
AmpVertexFuToFdHp= AmpVertexZFuToFdHp
! Final State 1 
AmpWaveZFuToFdHp=0._dp 
AmpVertexZFuToFdHp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdHp(1,:,gt2,:) = AmpWaveZFuToFdHp(1,:,gt2,:)+ZRUZDL(gt2,gt1)*AmpWaveFuToFdHp(1,:,gt1,:) 
AmpVertexZFuToFdHp(1,:,gt2,:)= AmpVertexZFuToFdHp(1,:,gt2,:)+ZRUZDL(gt2,gt1)*AmpVertexFuToFdHp(1,:,gt1,:) 
AmpWaveZFuToFdHp(2,:,gt2,:) = AmpWaveZFuToFdHp(2,:,gt2,:)+ZRUZDRc(gt2,gt1)*AmpWaveFuToFdHp(2,:,gt1,:) 
AmpVertexZFuToFdHp(2,:,gt2,:)= AmpVertexZFuToFdHp(2,:,gt2,:)+ZRUZDRc(gt2,gt1)*AmpVertexFuToFdHp(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFdHp=AmpWaveZFuToFdHp 
AmpVertexFuToFdHp= AmpVertexZFuToFdHp
! Final State 2 
AmpWaveZFuToFdHp=0._dp 
AmpVertexZFuToFdHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFuToFdHp(:,:,:,gt2) = AmpWaveZFuToFdHp(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveFuToFdHp(:,:,:,gt1) 
AmpVertexZFuToFdHp(:,:,:,gt2)= AmpVertexZFuToFdHp(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexFuToFdHp(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFdHp=AmpWaveZFuToFdHp 
AmpVertexFuToFdHp= AmpVertexZFuToFdHp
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFdHp = AmpVertexFuToFdHp  +  AmpVertexIRosFuToFdHp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fd Hp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFdHp = AmpTreeFuToFdHp 
 AmpSum2FuToFdHp = AmpTreeFuToFdHp + 2._dp*AmpWaveFuToFdHp + 2._dp*AmpVertexFuToFdHp  
Else 
 AmpSumFuToFdHp = AmpTreeFuToFdHp + AmpWaveFuToFdHp + AmpVertexFuToFdHp
 AmpSum2FuToFdHp = AmpTreeFuToFdHp + AmpWaveFuToFdHp + AmpVertexFuToFdHp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFdHp = AmpTreeFuToFdHp
 AmpSum2FuToFdHp = AmpTreeFuToFdHp 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MHpOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFd(gt2))+Abs(MHp(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuToFdHp = AmpTreeFuToFdHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHp(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFdHp(gt1, gt2, gt3) 
  AmpSum2FuToFdHp = 2._dp*AmpWaveFuToFdHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHp(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFdHp(gt1, gt2, gt3) 
  AmpSum2FuToFdHp = 2._dp*AmpVertexFuToFdHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHp(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFdHp(gt1, gt2, gt3) 
  AmpSum2FuToFdHp = AmpTreeFuToFdHp + 2._dp*AmpWaveFuToFdHp + 2._dp*AmpVertexFuToFdHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHp(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFdHp(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFdHp = AmpTreeFuToFdHp
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
  AmpSqTreeFuToFdHp(gt1, gt2, gt3) = AmpSqFuToFdHp(gt1, gt2, gt3)  
  AmpSum2FuToFdHp = + 2._dp*AmpWaveFuToFdHp + 2._dp*AmpVertexFuToFdHp
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
  AmpSqFuToFdHp(gt1, gt2, gt3) = AmpSqFuToFdHp(gt1, gt2, gt3) + AmpSqTreeFuToFdHp(gt1, gt2, gt3)  
Else  
  AmpSum2FuToFdHp = AmpTreeFuToFdHp
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHp(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
  AmpSqTreeFuToFdHp(gt1, gt2, gt3) = AmpSqFuToFdHp(gt1, gt2, gt3)  
  AmpSum2FuToFdHp = + 2._dp*AmpWaveFuToFdHp + 2._dp*AmpVertexFuToFdHp
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHp(gt3),AmpSumFuToFdHp(:,gt1, gt2, gt3),AmpSum2FuToFdHp(:,gt1, gt2, gt3),AmpSqFuToFdHp(gt1, gt2, gt3)) 
  AmpSqFuToFdHp(gt1, gt2, gt3) = AmpSqFuToFdHp(gt1, gt2, gt3) + AmpSqTreeFuToFdHp(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuToFdHp(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFdHp(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFdOS(gt2),MHpOS(gt3),helfactor*AmpSqFuToFdHp(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFd(gt2),MHp(gt3),helfactor*AmpSqFuToFdHp(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuToFdHp(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdHp(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFdHp(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdHp(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFdHp(gt1, gt2, gt3) + MRGFuToFdHp(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFdHp(gt1, gt2, gt3) + MRGFuToFdHp(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fd VWp
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FuToFdVWp(cplcFuFdVWpL,cplcFuFdVWpR,MFd,MFu,               & 
& MVWp,MFd2,MFu2,MVWp2,AmpTreeFuToFdVWp)

  Else 
Call Amplitude_Tree_Inert2_FuToFdVWp(ZcplcFuFdVWpL,ZcplcFuFdVWpR,MFd,MFu,             & 
& MVWp,MFd2,MFu2,MVWp2,AmpTreeFuToFdVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FuToFdVWp(MLambda,em,gs,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& MFdOS,MFuOS,MVWpOS,MRPFuToFdVWp,MRGFuToFdVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FuToFdVWp(MLambda,em,gs,ZcplcFuFdVWpL,ZcplcFuFdVWpR,           & 
& MFdOS,MFuOS,MVWpOS,MRPFuToFdVWp,MRGFuToFdVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FuToFdVWp(MLambda,em,gs,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& MFd,MFu,MVWp,MRPFuToFdVWp,MRGFuToFdVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FuToFdVWp(MLambda,em,gs,ZcplcFuFdVWpL,ZcplcFuFdVWpR,           & 
& MFd,MFu,MVWp,MRPFuToFdVWp,MRGFuToFdVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FuToFdVWp(cplcFuFdVWpL,cplcFuFdVWpR,ctcplcFuFdVWpL,        & 
& ctcplcFuFdVWpR,MFd,MFd2,MFu,MFu2,MVWp,MVWp2,ZfDL,ZfDR,ZfUL,ZfUR,ZfVWp,AmpWaveFuToFdVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFdVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,              & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0cHpVWp,cplhhcHpVWp,               & 
& cplhhcVWpVWp,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexFuToFdVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FuToFdVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0cHpVWp,cplhhcHpVWp,               & 
& cplhhcVWpVWp,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRdrFuToFdVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdVWp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,GosZcplcFuFdHpL,GosZcplcFuFdHpR,& 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,           & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0cHpVWp,cplhhcHpVWp,cplhhcVWpVWp,GosZcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,         & 
& cplcVWpVWpVZ,AmpVertexIRosFuToFdVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,GZcplcFuFdHpL,GZcplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,           & 
& cplcFdFdVPL,cplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0cHpVWp,cplhhcHpVWp,               & 
& cplhhcVWpVWp,GZcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRosFuToFdVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdVWp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,GcplcFuFdHpL,GcplcFuFdHpR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplG0cHpVWp,cplhhcHpVWp,cplhhcVWpVWp,GcplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,            & 
& cplcVWpVWpVZ,AmpVertexIRosFuToFdVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFdVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplG0cHpVWp,cplhhcHpVWp,               & 
& cplhhcVWpVWp,cplcHpVPVWp,cplcVWpVPVWp,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRosFuToFdVWp)

 End if 
 End if 
AmpVertexFuToFdVWp = AmpVertexFuToFdVWp -  AmpVertexIRdrFuToFdVWp! +  AmpVertexIRosFuToFdVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFdVWp=0._dp 
AmpVertexZFuToFdVWp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdVWp(1,gt2,:) = AmpWaveZFuToFdVWp(1,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFdVWp(1,gt1,:) 
AmpVertexZFuToFdVWp(1,gt2,:)= AmpVertexZFuToFdVWp(1,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFdVWp(1,gt1,:) 
AmpWaveZFuToFdVWp(2,gt2,:) = AmpWaveZFuToFdVWp(2,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFdVWp(2,gt1,:) 
AmpVertexZFuToFdVWp(2,gt2,:)= AmpVertexZFuToFdVWp(2,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFdVWp(2,gt1,:) 
AmpWaveZFuToFdVWp(3,gt2,:) = AmpWaveZFuToFdVWp(3,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFdVWp(3,gt1,:) 
AmpVertexZFuToFdVWp(3,gt2,:)= AmpVertexZFuToFdVWp(3,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFdVWp(3,gt1,:) 
AmpWaveZFuToFdVWp(4,gt2,:) = AmpWaveZFuToFdVWp(4,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFdVWp(4,gt1,:) 
AmpVertexZFuToFdVWp(4,gt2,:)= AmpVertexZFuToFdVWp(4,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFdVWp(4,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFdVWp=AmpWaveZFuToFdVWp 
AmpVertexFuToFdVWp= AmpVertexZFuToFdVWp
! Final State 1 
AmpWaveZFuToFdVWp=0._dp 
AmpVertexZFuToFdVWp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdVWp(1,:,gt2) = AmpWaveZFuToFdVWp(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFuToFdVWp(1,:,gt1) 
AmpVertexZFuToFdVWp(1,:,gt2)= AmpVertexZFuToFdVWp(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFuToFdVWp(1,:,gt1) 
AmpWaveZFuToFdVWp(2,:,gt2) = AmpWaveZFuToFdVWp(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFuToFdVWp(2,:,gt1) 
AmpVertexZFuToFdVWp(2,:,gt2)= AmpVertexZFuToFdVWp(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFuToFdVWp(2,:,gt1) 
AmpWaveZFuToFdVWp(3,:,gt2) = AmpWaveZFuToFdVWp(3,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFuToFdVWp(3,:,gt1) 
AmpVertexZFuToFdVWp(3,:,gt2)= AmpVertexZFuToFdVWp(3,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFuToFdVWp(3,:,gt1) 
AmpWaveZFuToFdVWp(4,:,gt2) = AmpWaveZFuToFdVWp(4,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFuToFdVWp(4,:,gt1) 
AmpVertexZFuToFdVWp(4,:,gt2)= AmpVertexZFuToFdVWp(4,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFuToFdVWp(4,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFdVWp=AmpWaveZFuToFdVWp 
AmpVertexFuToFdVWp= AmpVertexZFuToFdVWp
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFdVWp = AmpVertexFuToFdVWp  +  AmpVertexIRosFuToFdVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fd VWp -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFdVWp = AmpTreeFuToFdVWp 
 AmpSum2FuToFdVWp = AmpTreeFuToFdVWp + 2._dp*AmpWaveFuToFdVWp + 2._dp*AmpVertexFuToFdVWp  
Else 
 AmpSumFuToFdVWp = AmpTreeFuToFdVWp + AmpWaveFuToFdVWp + AmpVertexFuToFdVWp
 AmpSum2FuToFdVWp = AmpTreeFuToFdVWp + AmpWaveFuToFdVWp + AmpVertexFuToFdVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFdVWp = AmpTreeFuToFdVWp
 AmpSum2FuToFdVWp = AmpTreeFuToFdVWp 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFd(gt2))+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FuToFdVWp = AmpTreeFuToFdVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWpOS,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWp,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFdVWp(gt1, gt2) 
  AmpSum2FuToFdVWp = 2._dp*AmpWaveFuToFdVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWpOS,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWp,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFdVWp(gt1, gt2) 
  AmpSum2FuToFdVWp = 2._dp*AmpVertexFuToFdVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWpOS,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWp,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFdVWp(gt1, gt2) 
  AmpSum2FuToFdVWp = AmpTreeFuToFdVWp + 2._dp*AmpWaveFuToFdVWp + 2._dp*AmpVertexFuToFdVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWpOS,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWp,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFdVWp(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFdVWp = AmpTreeFuToFdVWp
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWpOS,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
  AmpSqTreeFuToFdVWp(gt1, gt2) = AmpSqFuToFdVWp(gt1, gt2)  
  AmpSum2FuToFdVWp = + 2._dp*AmpWaveFuToFdVWp + 2._dp*AmpVertexFuToFdVWp
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWpOS,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
  AmpSqFuToFdVWp(gt1, gt2) = AmpSqFuToFdVWp(gt1, gt2) + AmpSqTreeFuToFdVWp(gt1, gt2)  
Else  
  AmpSum2FuToFdVWp = AmpTreeFuToFdVWp
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWp,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
  AmpSqTreeFuToFdVWp(gt1, gt2) = AmpSqFuToFdVWp(gt1, gt2)  
  AmpSum2FuToFdVWp = + 2._dp*AmpWaveFuToFdVWp + 2._dp*AmpVertexFuToFdVWp
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWp,AmpSumFuToFdVWp(:,gt1, gt2),AmpSum2FuToFdVWp(:,gt1, gt2),AmpSqFuToFdVWp(gt1, gt2)) 
  AmpSqFuToFdVWp(gt1, gt2) = AmpSqFuToFdVWp(gt1, gt2) + AmpSqTreeFuToFdVWp(gt1, gt2)  
End if  
Else  
  AmpSqFuToFdVWp(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFdVWp(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFdOS(gt2),MVWpOS,helfactor*AmpSqFuToFdVWp(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFd(gt2),MVWp,helfactor*AmpSqFuToFdVWp(gt1, gt2))
End if 
If ((Abs(MRPFuToFdVWp(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdVWp(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFdVWp(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdVWp(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFdVWp(gt1, gt2) + MRGFuToFdVWp(gt1, gt2)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFdVWp(gt1, gt2) + MRGFuToFdVWp(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fu hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,MFu,Mhh,MFu2,             & 
& Mhh2,AmpTreeFuToFuhh)

  Else 
Call Amplitude_Tree_Inert2_FuToFuhh(ZcplcFuFuhhL,ZcplcFuFuhhR,MFu,Mhh,MFu2,           & 
& Mhh2,AmpTreeFuToFuhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,MFuOS,          & 
& MhhOS,MRPFuToFuhh,MRGFuToFuhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FuToFuhh(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,              & 
& MFuOS,MhhOS,MRPFuToFuhh,MRGFuToFuhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,MFu,            & 
& Mhh,MRPFuToFuhh,MRGFuToFuhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FuToFuhh(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,              & 
& MFu,Mhh,MRPFuToFuhh,MRGFuToFuhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,            & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,Zfhh,ZfUL,ZfUR,AmpWaveFuToFuhh)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFuhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexFuToFuhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FuToFuhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRdrFuToFuhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuhh(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,      & 
& cplcFuFuG0L,cplcFuFuG0R,ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRosFuToFuhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRosFuToFuhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuhh(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,      & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRosFuToFuhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRosFuToFuhh)

 End if 
 End if 
AmpVertexFuToFuhh = AmpVertexFuToFuhh -  AmpVertexIRdrFuToFuhh! +  AmpVertexIRosFuToFuhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFuhh=0._dp 
AmpVertexZFuToFuhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuhh(1,gt2,:) = AmpWaveZFuToFuhh(1,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFuhh(1,gt1,:) 
AmpVertexZFuToFuhh(1,gt2,:)= AmpVertexZFuToFuhh(1,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFuhh(1,gt1,:) 
AmpWaveZFuToFuhh(2,gt2,:) = AmpWaveZFuToFuhh(2,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFuhh(2,gt1,:) 
AmpVertexZFuToFuhh(2,gt2,:)= AmpVertexZFuToFuhh(2,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFuhh(2,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuhh=AmpWaveZFuToFuhh 
AmpVertexFuToFuhh= AmpVertexZFuToFuhh
! Final State 1 
AmpWaveZFuToFuhh=0._dp 
AmpVertexZFuToFuhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuhh(1,:,gt2) = AmpWaveZFuToFuhh(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveFuToFuhh(1,:,gt1) 
AmpVertexZFuToFuhh(1,:,gt2)= AmpVertexZFuToFuhh(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexFuToFuhh(1,:,gt1) 
AmpWaveZFuToFuhh(2,:,gt2) = AmpWaveZFuToFuhh(2,:,gt2)+ZRUZURc(gt2,gt1)*AmpWaveFuToFuhh(2,:,gt1) 
AmpVertexZFuToFuhh(2,:,gt2)= AmpVertexZFuToFuhh(2,:,gt2)+ZRUZURc(gt2,gt1)*AmpVertexFuToFuhh(2,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFuhh=AmpWaveZFuToFuhh 
AmpVertexFuToFuhh= AmpVertexZFuToFuhh
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFuhh = AmpVertexFuToFuhh  +  AmpVertexIRosFuToFuhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFuhh = AmpTreeFuToFuhh 
 AmpSum2FuToFuhh = AmpTreeFuToFuhh + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh  
Else 
 AmpSumFuToFuhh = AmpTreeFuToFuhh + AmpWaveFuToFuhh + AmpVertexFuToFuhh
 AmpSum2FuToFuhh = AmpTreeFuToFuhh + AmpWaveFuToFuhh + AmpVertexFuToFuhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuhh = AmpTreeFuToFuhh
 AmpSum2FuToFuhh = AmpTreeFuToFuhh 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(Mhh))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FuToFuhh = AmpTreeFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFuhh(gt1, gt2) 
  AmpSum2FuToFuhh = 2._dp*AmpWaveFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFuhh(gt1, gt2) 
  AmpSum2FuToFuhh = 2._dp*AmpVertexFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFuhh(gt1, gt2) 
  AmpSum2FuToFuhh = AmpTreeFuToFuhh + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFuhh(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFuhh = AmpTreeFuToFuhh
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
  AmpSqTreeFuToFuhh(gt1, gt2) = AmpSqFuToFuhh(gt1, gt2)  
  AmpSum2FuToFuhh = + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
  AmpSqFuToFuhh(gt1, gt2) = AmpSqFuToFuhh(gt1, gt2) + AmpSqTreeFuToFuhh(gt1, gt2)  
Else  
  AmpSum2FuToFuhh = AmpTreeFuToFuhh
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
  AmpSqTreeFuToFuhh(gt1, gt2) = AmpSqFuToFuhh(gt1, gt2)  
  AmpSum2FuToFuhh = + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh,AmpSumFuToFuhh(:,gt1, gt2),AmpSum2FuToFuhh(:,gt1, gt2),AmpSqFuToFuhh(gt1, gt2)) 
  AmpSqFuToFuhh(gt1, gt2) = AmpSqFuToFuhh(gt1, gt2) + AmpSqTreeFuToFuhh(gt1, gt2)  
End if  
Else  
  AmpSqFuToFuhh(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuhh(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),MhhOS,helfactor*AmpSqFuToFuhh(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),Mhh,helfactor*AmpSqFuToFuhh(gt1, gt2))
End if 
If ((Abs(MRPFuToFuhh(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuhh(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFuhh(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuhh(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFuhh(gt1, gt2) + MRGFuToFuhh(gt1, gt2)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFuhh(gt1, gt2) + MRGFuToFuhh(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fu VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FuToFuVZ(cplcFuFuVZL,cplcFuFuVZR,MFu,MVZ,MFu2,             & 
& MVZ2,AmpTreeFuToFuVZ)

  Else 
Call Amplitude_Tree_Inert2_FuToFuVZ(ZcplcFuFuVZL,ZcplcFuFuVZR,MFu,MVZ,MFu2,           & 
& MVZ2,AmpTreeFuToFuVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,MFuOS,          & 
& MVZOS,MRPFuToFuVZ,MRGFuToFuVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FuToFuVZ(MLambda,em,gs,ZcplcFuFuVZL,ZcplcFuFuVZR,              & 
& MFuOS,MVZOS,MRPFuToFuVZ,MRGFuToFuVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,MFu,            & 
& MVZ,MRPFuToFuVZ,MRGFuToFuVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FuToFuVZ(MLambda,em,gs,ZcplcFuFuVZL,ZcplcFuFuVZR,              & 
& MFu,MVZ,MRPFuToFuVZ,MRGFuToFuVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FuToFuVZ(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,              & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,MVZ,MVZ2,ZfUL,ZfUR,ZfVPVZ,ZfVZ,AmpWaveFuToFuVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFuVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexFuToFuVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FuToFuVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRdrFuToFuVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuVZ(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,      & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,           & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,    & 
& cplcVWpVWpVZ,AmpVertexIRosFuToFuVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& ZcplcFuFuVZL,ZcplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,       & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRosFuToFuVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuVZ(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,      & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,    & 
& cplcVWpVWpVZ,AmpVertexIRosFuToFuVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FuToFuVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRosFuToFuVZ)

 End if 
 End if 
AmpVertexFuToFuVZ = AmpVertexFuToFuVZ -  AmpVertexIRdrFuToFuVZ! +  AmpVertexIRosFuToFuVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFuVZ=0._dp 
AmpVertexZFuToFuVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuVZ(1,gt2,:) = AmpWaveZFuToFuVZ(1,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFuVZ(1,gt1,:) 
AmpVertexZFuToFuVZ(1,gt2,:)= AmpVertexZFuToFuVZ(1,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFuVZ(1,gt1,:) 
AmpWaveZFuToFuVZ(2,gt2,:) = AmpWaveZFuToFuVZ(2,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFuVZ(2,gt1,:) 
AmpVertexZFuToFuVZ(2,gt2,:)= AmpVertexZFuToFuVZ(2,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFuVZ(2,gt1,:) 
AmpWaveZFuToFuVZ(3,gt2,:) = AmpWaveZFuToFuVZ(3,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFuVZ(3,gt1,:) 
AmpVertexZFuToFuVZ(3,gt2,:)= AmpVertexZFuToFuVZ(3,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFuVZ(3,gt1,:) 
AmpWaveZFuToFuVZ(4,gt2,:) = AmpWaveZFuToFuVZ(4,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFuVZ(4,gt1,:) 
AmpVertexZFuToFuVZ(4,gt2,:)= AmpVertexZFuToFuVZ(4,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFuVZ(4,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuVZ=AmpWaveZFuToFuVZ 
AmpVertexFuToFuVZ= AmpVertexZFuToFuVZ
! Final State 1 
AmpWaveZFuToFuVZ=0._dp 
AmpVertexZFuToFuVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuVZ(1,:,gt2) = AmpWaveZFuToFuVZ(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveFuToFuVZ(1,:,gt1) 
AmpVertexZFuToFuVZ(1,:,gt2)= AmpVertexZFuToFuVZ(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexFuToFuVZ(1,:,gt1) 
AmpWaveZFuToFuVZ(2,:,gt2) = AmpWaveZFuToFuVZ(2,:,gt2)+ZRUZURc(gt2,gt1)*AmpWaveFuToFuVZ(2,:,gt1) 
AmpVertexZFuToFuVZ(2,:,gt2)= AmpVertexZFuToFuVZ(2,:,gt2)+ZRUZURc(gt2,gt1)*AmpVertexFuToFuVZ(2,:,gt1) 
AmpWaveZFuToFuVZ(3,:,gt2) = AmpWaveZFuToFuVZ(3,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveFuToFuVZ(3,:,gt1) 
AmpVertexZFuToFuVZ(3,:,gt2)= AmpVertexZFuToFuVZ(3,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexFuToFuVZ(3,:,gt1) 
AmpWaveZFuToFuVZ(4,:,gt2) = AmpWaveZFuToFuVZ(4,:,gt2)+ZRUZURc(gt2,gt1)*AmpWaveFuToFuVZ(4,:,gt1) 
AmpVertexZFuToFuVZ(4,:,gt2)= AmpVertexZFuToFuVZ(4,:,gt2)+ZRUZURc(gt2,gt1)*AmpVertexFuToFuVZ(4,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFuVZ=AmpWaveZFuToFuVZ 
AmpVertexFuToFuVZ= AmpVertexZFuToFuVZ
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFuVZ = AmpVertexFuToFuVZ  +  AmpVertexIRosFuToFuVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFuVZ = AmpTreeFuToFuVZ 
 AmpSum2FuToFuVZ = AmpTreeFuToFuVZ + 2._dp*AmpWaveFuToFuVZ + 2._dp*AmpVertexFuToFuVZ  
Else 
 AmpSumFuToFuVZ = AmpTreeFuToFuVZ + AmpWaveFuToFuVZ + AmpVertexFuToFuVZ
 AmpSum2FuToFuVZ = AmpTreeFuToFuVZ + AmpWaveFuToFuVZ + AmpVertexFuToFuVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuVZ = AmpTreeFuToFuVZ
 AmpSum2FuToFuVZ = AmpTreeFuToFuVZ 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FuToFuVZ = AmpTreeFuToFuVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),MVZOS,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVZ,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFuVZ(gt1, gt2) 
  AmpSum2FuToFuVZ = 2._dp*AmpWaveFuToFuVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),MVZOS,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVZ,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFuVZ(gt1, gt2) 
  AmpSum2FuToFuVZ = 2._dp*AmpVertexFuToFuVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),MVZOS,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVZ,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFuVZ(gt1, gt2) 
  AmpSum2FuToFuVZ = AmpTreeFuToFuVZ + 2._dp*AmpWaveFuToFuVZ + 2._dp*AmpVertexFuToFuVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),MVZOS,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVZ,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFuVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFuVZ = AmpTreeFuToFuVZ
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),MVZOS,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
  AmpSqTreeFuToFuVZ(gt1, gt2) = AmpSqFuToFuVZ(gt1, gt2)  
  AmpSum2FuToFuVZ = + 2._dp*AmpWaveFuToFuVZ + 2._dp*AmpVertexFuToFuVZ
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),MVZOS,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
  AmpSqFuToFuVZ(gt1, gt2) = AmpSqFuToFuVZ(gt1, gt2) + AmpSqTreeFuToFuVZ(gt1, gt2)  
Else  
  AmpSum2FuToFuVZ = AmpTreeFuToFuVZ
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVZ,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
  AmpSqTreeFuToFuVZ(gt1, gt2) = AmpSqFuToFuVZ(gt1, gt2)  
  AmpSum2FuToFuVZ = + 2._dp*AmpWaveFuToFuVZ + 2._dp*AmpVertexFuToFuVZ
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVZ,AmpSumFuToFuVZ(:,gt1, gt2),AmpSum2FuToFuVZ(:,gt1, gt2),AmpSqFuToFuVZ(gt1, gt2)) 
  AmpSqFuToFuVZ(gt1, gt2) = AmpSqFuToFuVZ(gt1, gt2) + AmpSqTreeFuToFuVZ(gt1, gt2)  
End if  
Else  
  AmpSqFuToFuVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuVZ(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),MVZOS,helfactor*AmpSqFuToFuVZ(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),MVZ,helfactor*AmpSqFuToFuVZ(gt1, gt2))
End if 
If ((Abs(MRPFuToFuVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFuVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFuVZ(gt1, gt2) + MRGFuToFuVZ(gt1, gt2)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFuVZ(gt1, gt2) + MRGFuToFuVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End If 
!---------------- 
! Fu A0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FuToFuA0(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,          & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,ZcplA0HpcHp,ZcplA0HpcVWp,ZcplA0cHpVWp,ZcplcFuFdHpL,       & 
& ZcplcFuFdHpR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFdFucVWpL,   & 
& ZcplcFdFucVWpR,AmpVertexFuToFuA0)

 Else 
Call Amplitude_VERTEX_Inert2_FuToFuA0(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,          & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,           & 
& cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,         & 
& cplcFdFucVWpR,AmpVertexFuToFuA0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFuA0(MA0,MFd,MFu,MHp,MVWp,MA02,MFd2,MFu2,            & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,    & 
& cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,AmpVertexFuToFuA0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu A0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuA0 = 0._dp 
 AmpSum2FuToFuA0 = 0._dp  
Else 
 AmpSumFuToFuA0 = AmpVertexFuToFuA0 + AmpWaveFuToFuA0
 AmpSum2FuToFuA0 = AmpVertexFuToFuA0 + AmpWaveFuToFuA0 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(MA0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MA0OS,AmpSumFuToFuA0(:,gt1, gt2),AmpSum2FuToFuA0(:,gt1, gt2),AmpSqFuToFuA0(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MA0,AmpSumFuToFuA0(:,gt1, gt2),AmpSum2FuToFuA0(:,gt1, gt2),AmpSqFuToFuA0(gt1, gt2)) 
End if  
Else  
  AmpSqFuToFuA0(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuA0(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),MA0OS,helfactor*AmpSqFuToFuA0(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),MA0,helfactor*AmpSqFuToFuA0(gt1, gt2))
End if 
If ((Abs(MRPFuToFuA0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuA0(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fu H0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FuToFuH0(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,          & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,    & 
& ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplH0HpcHp,ZcplH0HpcVWp,    & 
& ZcplH0cHpVWp,AmpVertexFuToFuH0)

 Else 
Call Amplitude_VERTEX_Inert2_FuToFuH0(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,          & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,        & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexFuToFuH0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFuH0(MFd,MFu,MH0,MHp,MVWp,MFd2,MFu2,MH02,            & 
& MHp2,MVWp2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,             & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,           & 
& AmpVertexFuToFuH0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu H0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuH0 = 0._dp 
 AmpSum2FuToFuH0 = 0._dp  
Else 
 AmpSumFuToFuH0 = AmpVertexFuToFuH0 + AmpWaveFuToFuH0
 AmpSum2FuToFuH0 = AmpVertexFuToFuH0 + AmpWaveFuToFuH0 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(MH0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MH0OS,AmpSumFuToFuH0(:,gt1, gt2),AmpSum2FuToFuH0(:,gt1, gt2),AmpSqFuToFuH0(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MH0,AmpSumFuToFuH0(:,gt1, gt2),AmpSum2FuToFuH0(:,gt1, gt2),AmpSqFuToFuH0(gt1, gt2)) 
End if  
Else  
  AmpSqFuToFuH0(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuH0(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),MH0OS,helfactor*AmpSqFuToFuH0(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),MH0,helfactor*AmpSqFuToFuH0(gt1, gt2))
End if 
If ((Abs(MRPFuToFuH0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuH0(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fu VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_FuToFuVG(ZcplcFuFuVGL,ZcplcFuFuVGR,ctcplcFuFuVGL,          & 
& ctcplcFuFuVGR,MFuOS,MFu2OS,MVG,MVG2,ZfUL,ZfUR,ZfVG,AmpWaveFuToFuVG)

 Else 
Call Amplitude_WAVE_Inert2_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,            & 
& ctcplcFuFuVGR,MFuOS,MFu2OS,MVG,MVG2,ZfUL,ZfUR,ZfVG,AmpWaveFuToFuVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FuToFuVG(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,       & 
& ZcplcFuFuG0L,ZcplcFuFuG0R,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,         & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFdFucHpL,ZcplcFdFucHpR,       & 
& ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplVGVGVG,AmpVertexFuToFuVG)

 Else 
Call Amplitude_VERTEX_Inert2_FuToFuVG(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplVGVGVG,AmpVertexFuToFuVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,            & 
& ctcplcFuFuVGR,MFu,MFu2,MVG,MVG2,ZfUL,ZfUR,ZfVG,AmpWaveFuToFuVG)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFuVG(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplVGVGVG,AmpVertexFuToFuVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuVG = 0._dp 
 AmpSum2FuToFuVG = 0._dp  
Else 
 AmpSumFuToFuVG = AmpVertexFuToFuVG + AmpWaveFuToFuVG
 AmpSum2FuToFuVG = AmpVertexFuToFuVG + AmpWaveFuToFuVG 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),0._dp,AmpSumFuToFuVG(:,gt1, gt2),AmpSum2FuToFuVG(:,gt1, gt2),AmpSqFuToFuVG(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVG,AmpSumFuToFuVG(:,gt1, gt2),AmpSum2FuToFuVG(:,gt1, gt2),AmpSqFuToFuVG(gt1, gt2)) 
End if  
Else  
  AmpSqFuToFuVG(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuVG(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 4._dp/3._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),0._dp,helfactor*AmpSqFuToFuVG(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 4._dp/3._dp*GammaTPS(MFu(gt1),MFu(gt2),MVG,helfactor*AmpSqFuToFuVG(gt1, gt2))
End if 
If ((Abs(MRPFuToFuVG(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuVG(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fu VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_FuToFuVP(ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,           & 
& ZcplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFuOS,            & 
& MFu2OS,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)

 Else 
Call Amplitude_WAVE_Inert2_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,              & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFuOS,             & 
& MFu2OS,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FuToFuVP(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,       & 
& ZcplcFuFuG0L,ZcplcFuFuG0R,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,         & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFdFucHpL,ZcplcFdFucHpR,       & 
& ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplHpcHpVP,ZcplHpcVWpVP,ZcplcHpVPVWp,ZcplcVWpVPVWp,     & 
& AmpVertexFuToFuVP)

 Else 
Call Amplitude_VERTEX_Inert2_FuToFuVP(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,           & 
& AmpVertexFuToFuVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,              & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FuToFuVP(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFuFdHpL,cplcFuFdHpR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuG0L,cplcFuFuG0R,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,AmpVertexFuToFuVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuVP = 0._dp 
 AmpSum2FuToFuVP = 0._dp  
Else 
 AmpSumFuToFuVP = AmpVertexFuToFuVP + AmpWaveFuToFuVP
 AmpSum2FuToFuVP = AmpVertexFuToFuVP + AmpWaveFuToFuVP 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFuOS(gt2),0._dp,AmpSumFuToFuVP(:,gt1, gt2),AmpSum2FuToFuVP(:,gt1, gt2),AmpSqFuToFuVP(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFu(gt2),MVP,AmpSumFuToFuVP(:,gt1, gt2),AmpSum2FuToFuVP(:,gt1, gt2),AmpSqFuToFuVP(gt1, gt2)) 
End if  
Else  
  AmpSqFuToFuVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuVP(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),0._dp,helfactor*AmpSqFuToFuVP(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),MVP,helfactor*AmpSqFuToFuVP(gt1, gt2))
End if 
If ((Abs(MRPFuToFuVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End Subroutine OneLoopDecay_Fu

End Module Wrapper_OneLoopDecay_Fu_Inert2
