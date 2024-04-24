! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Fd_Inert2
Use Model_Data_Inert2 
Use Kinematics 
Use OneLoopDecay_Fd_Inert2 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Fd(MHpOS,MHp2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MFeOS,              & 
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
& cplHpcVWpVZ(2),cplVGVGVG,ctcplcFdFdG0L(3,3),ctcplcFdFdG0R(3,3),ctcplcFdFdhhL(3,3),     & 
& ctcplcFdFdhhR(3,3),ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),ctcplcFdFdVPL(3,3),           & 
& ctcplcFdFdVPR(3,3),ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3),ctcplcFdFucHpL(3,3,2),        & 
& ctcplcFdFucHpR(3,3,2),ctcplcFdFucVWpL(3,3),ctcplcFdFucVWpR(3,3),GcplcFdFucHpL(3,3,2),  & 
& GcplcFdFucHpR(3,3,2),GcplcHpVPVWp(2),GcplHpcVWpVP(2),GosZcplcFdFucHpL(3,3,2),          & 
& GosZcplcFdFucHpR(3,3,2),GosZcplcHpVPVWp(2),GosZcplHpcVWpVP(2),GZcplcFdFucHpL(3,3,2),   & 
& GZcplcFdFucHpR(3,3,2),GZcplcHpVPVWp(2),GZcplHpcVWpVP(2),ZcplA0cHpVWp(2),               & 
& ZcplA0HpcHp(2,2),ZcplA0HpcVWp(2),ZcplcFdFdG0L(3,3),ZcplcFdFdG0R(3,3),ZcplcFdFdhhL(3,3),& 
& ZcplcFdFdhhR(3,3),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),ZcplcFdFdVPL(3,3),               & 
& ZcplcFdFdVPR(3,3),ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),ZcplcFdFucHpL(3,3,2),            & 
& ZcplcFdFucHpR(3,3,2),ZcplcFdFucVWpL(3,3),ZcplcFdFucVWpR(3,3),ZcplcFuFdHpL(3,3,2),      & 
& ZcplcFuFdHpR(3,3,2),ZcplcFuFdVWpL(3,3),ZcplcFuFdVWpR(3,3),ZcplcFuFuVGL(3,3),           & 
& ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),ZcplcHpVPVWp(2),ZcplcVWpVPVWp,   & 
& ZcplH0cHpVWp(2),ZcplH0HpcHp(2,2),ZcplH0HpcVWp(2),ZcplHpcHpVP(2,2),ZcplHpcVWpVP(2),     & 
& ZcplVGVGVG

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
Real(dp), Intent(out) :: gP1LFd(3,24) 
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
Real(dp) :: MRPFdToFdhh(3,3),MRGFdToFdhh(3,3), MRPZFdToFdhh(3,3),MRGZFdToFdhh(3,3) 
Real(dp) :: MVPFdToFdhh(3,3) 
Real(dp) :: RMsqTreeFdToFdhh(3,3),RMsqWaveFdToFdhh(3,3),RMsqVertexFdToFdhh(3,3) 
Complex(dp) :: AmpTreeFdToFdhh(2,3,3),AmpWaveFdToFdhh(2,3,3)=(0._dp,0._dp),AmpVertexFdToFdhh(2,3,3)& 
 & ,AmpVertexIRosFdToFdhh(2,3,3),AmpVertexIRdrFdToFdhh(2,3,3), AmpSumFdToFdhh(2,3,3), AmpSum2FdToFdhh(2,3,3) 
Complex(dp) :: AmpTreeZFdToFdhh(2,3,3),AmpWaveZFdToFdhh(2,3,3),AmpVertexZFdToFdhh(2,3,3) 
Real(dp) :: AmpSqFdToFdhh(3,3),  AmpSqTreeFdToFdhh(3,3) 
Real(dp) :: MRPFdToFdVZ(3,3),MRGFdToFdVZ(3,3), MRPZFdToFdVZ(3,3),MRGZFdToFdVZ(3,3) 
Real(dp) :: MVPFdToFdVZ(3,3) 
Real(dp) :: RMsqTreeFdToFdVZ(3,3),RMsqWaveFdToFdVZ(3,3),RMsqVertexFdToFdVZ(3,3) 
Complex(dp) :: AmpTreeFdToFdVZ(4,3,3),AmpWaveFdToFdVZ(4,3,3)=(0._dp,0._dp),AmpVertexFdToFdVZ(4,3,3)& 
 & ,AmpVertexIRosFdToFdVZ(4,3,3),AmpVertexIRdrFdToFdVZ(4,3,3), AmpSumFdToFdVZ(4,3,3), AmpSum2FdToFdVZ(4,3,3) 
Complex(dp) :: AmpTreeZFdToFdVZ(4,3,3),AmpWaveZFdToFdVZ(4,3,3),AmpVertexZFdToFdVZ(4,3,3) 
Real(dp) :: AmpSqFdToFdVZ(3,3),  AmpSqTreeFdToFdVZ(3,3) 
Real(dp) :: MRPFdToFucHp(3,3,2),MRGFdToFucHp(3,3,2), MRPZFdToFucHp(3,3,2),MRGZFdToFucHp(3,3,2) 
Real(dp) :: MVPFdToFucHp(3,3,2) 
Real(dp) :: RMsqTreeFdToFucHp(3,3,2),RMsqWaveFdToFucHp(3,3,2),RMsqVertexFdToFucHp(3,3,2) 
Complex(dp) :: AmpTreeFdToFucHp(2,3,3,2),AmpWaveFdToFucHp(2,3,3,2)=(0._dp,0._dp),AmpVertexFdToFucHp(2,3,3,2)& 
 & ,AmpVertexIRosFdToFucHp(2,3,3,2),AmpVertexIRdrFdToFucHp(2,3,3,2), AmpSumFdToFucHp(2,3,3,2), AmpSum2FdToFucHp(2,3,3,2) 
Complex(dp) :: AmpTreeZFdToFucHp(2,3,3,2),AmpWaveZFdToFucHp(2,3,3,2),AmpVertexZFdToFucHp(2,3,3,2) 
Real(dp) :: AmpSqFdToFucHp(3,3,2),  AmpSqTreeFdToFucHp(3,3,2) 
Real(dp) :: MRPFdToFucVWp(3,3),MRGFdToFucVWp(3,3), MRPZFdToFucVWp(3,3),MRGZFdToFucVWp(3,3) 
Real(dp) :: MVPFdToFucVWp(3,3) 
Real(dp) :: RMsqTreeFdToFucVWp(3,3),RMsqWaveFdToFucVWp(3,3),RMsqVertexFdToFucVWp(3,3) 
Complex(dp) :: AmpTreeFdToFucVWp(4,3,3),AmpWaveFdToFucVWp(4,3,3)=(0._dp,0._dp),AmpVertexFdToFucVWp(4,3,3)& 
 & ,AmpVertexIRosFdToFucVWp(4,3,3),AmpVertexIRdrFdToFucVWp(4,3,3), AmpSumFdToFucVWp(4,3,3), AmpSum2FdToFucVWp(4,3,3) 
Complex(dp) :: AmpTreeZFdToFucVWp(4,3,3),AmpWaveZFdToFucVWp(4,3,3),AmpVertexZFdToFucVWp(4,3,3) 
Real(dp) :: AmpSqFdToFucVWp(3,3),  AmpSqTreeFdToFucVWp(3,3) 
Real(dp) :: MRPFdToFdA0(3,3),MRGFdToFdA0(3,3), MRPZFdToFdA0(3,3),MRGZFdToFdA0(3,3) 
Real(dp) :: MVPFdToFdA0(3,3) 
Real(dp) :: RMsqTreeFdToFdA0(3,3),RMsqWaveFdToFdA0(3,3),RMsqVertexFdToFdA0(3,3) 
Complex(dp) :: AmpTreeFdToFdA0(2,3,3),AmpWaveFdToFdA0(2,3,3)=(0._dp,0._dp),AmpVertexFdToFdA0(2,3,3)& 
 & ,AmpVertexIRosFdToFdA0(2,3,3),AmpVertexIRdrFdToFdA0(2,3,3), AmpSumFdToFdA0(2,3,3), AmpSum2FdToFdA0(2,3,3) 
Complex(dp) :: AmpTreeZFdToFdA0(2,3,3),AmpWaveZFdToFdA0(2,3,3),AmpVertexZFdToFdA0(2,3,3) 
Real(dp) :: AmpSqFdToFdA0(3,3),  AmpSqTreeFdToFdA0(3,3) 
Real(dp) :: MRPFdToFdH0(3,3),MRGFdToFdH0(3,3), MRPZFdToFdH0(3,3),MRGZFdToFdH0(3,3) 
Real(dp) :: MVPFdToFdH0(3,3) 
Real(dp) :: RMsqTreeFdToFdH0(3,3),RMsqWaveFdToFdH0(3,3),RMsqVertexFdToFdH0(3,3) 
Complex(dp) :: AmpTreeFdToFdH0(2,3,3),AmpWaveFdToFdH0(2,3,3)=(0._dp,0._dp),AmpVertexFdToFdH0(2,3,3)& 
 & ,AmpVertexIRosFdToFdH0(2,3,3),AmpVertexIRdrFdToFdH0(2,3,3), AmpSumFdToFdH0(2,3,3), AmpSum2FdToFdH0(2,3,3) 
Complex(dp) :: AmpTreeZFdToFdH0(2,3,3),AmpWaveZFdToFdH0(2,3,3),AmpVertexZFdToFdH0(2,3,3) 
Real(dp) :: AmpSqFdToFdH0(3,3),  AmpSqTreeFdToFdH0(3,3) 
Real(dp) :: MRPFdToFdVG(3,3),MRGFdToFdVG(3,3), MRPZFdToFdVG(3,3),MRGZFdToFdVG(3,3) 
Real(dp) :: MVPFdToFdVG(3,3) 
Real(dp) :: RMsqTreeFdToFdVG(3,3),RMsqWaveFdToFdVG(3,3),RMsqVertexFdToFdVG(3,3) 
Complex(dp) :: AmpTreeFdToFdVG(4,3,3),AmpWaveFdToFdVG(4,3,3)=(0._dp,0._dp),AmpVertexFdToFdVG(4,3,3)& 
 & ,AmpVertexIRosFdToFdVG(4,3,3),AmpVertexIRdrFdToFdVG(4,3,3), AmpSumFdToFdVG(4,3,3), AmpSum2FdToFdVG(4,3,3) 
Complex(dp) :: AmpTreeZFdToFdVG(4,3,3),AmpWaveZFdToFdVG(4,3,3),AmpVertexZFdToFdVG(4,3,3) 
Real(dp) :: AmpSqFdToFdVG(3,3),  AmpSqTreeFdToFdVG(3,3) 
Real(dp) :: MRPFdToFdVP(3,3),MRGFdToFdVP(3,3), MRPZFdToFdVP(3,3),MRGZFdToFdVP(3,3) 
Real(dp) :: MVPFdToFdVP(3,3) 
Real(dp) :: RMsqTreeFdToFdVP(3,3),RMsqWaveFdToFdVP(3,3),RMsqVertexFdToFdVP(3,3) 
Complex(dp) :: AmpTreeFdToFdVP(4,3,3),AmpWaveFdToFdVP(4,3,3)=(0._dp,0._dp),AmpVertexFdToFdVP(4,3,3)& 
 & ,AmpVertexIRosFdToFdVP(4,3,3),AmpVertexIRdrFdToFdVP(4,3,3), AmpSumFdToFdVP(4,3,3), AmpSum2FdToFdVP(4,3,3) 
Complex(dp) :: AmpTreeZFdToFdVP(4,3,3),AmpWaveZFdToFdVP(4,3,3),AmpVertexZFdToFdVP(4,3,3) 
Real(dp) :: AmpSqFdToFdVP(3,3),  AmpSqTreeFdToFdVP(3,3) 
Write(*,*) "Calculating one-loop decays of Fd " 
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
! Fd hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FdToFdhh(cplcFdFdhhL,cplcFdFdhhR,MFd,Mhh,MFd2,             & 
& Mhh2,AmpTreeFdToFdhh)

  Else 
Call Amplitude_Tree_Inert2_FdToFdhh(ZcplcFdFdhhL,ZcplcFdFdhhR,MFd,Mhh,MFd2,           & 
& Mhh2,AmpTreeFdToFdhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FdToFdhh(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,MFdOS,          & 
& MhhOS,MRPFdToFdhh,MRGFdToFdhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FdToFdhh(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,              & 
& MFdOS,MhhOS,MRPFdToFdhh,MRGFdToFdhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FdToFdhh(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,MFd,            & 
& Mhh,MRPFdToFdhh,MRGFdToFdhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FdToFdhh(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,              & 
& MFd,Mhh,MRPFdToFdhh,MRGFdToFdhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FdToFdhh(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,            & 
& ctcplcFdFdhhR,MFd,MFd2,Mhh,Mhh2,ZfDL,ZfDR,Zfhh,AmpWaveFdToFdhh)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFdhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexFdToFdhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FdToFdhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRdrFdToFdhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdhh(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRosFdToFdhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRosFdToFdhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdhh(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,      & 
& cplhhcHpVWp,cplhhcVWpVWp,cplhhVZVZ,AmpVertexIRosFdToFdhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,AmpVertexIRosFdToFdhh)

 End if 
 End if 
AmpVertexFdToFdhh = AmpVertexFdToFdhh -  AmpVertexIRdrFdToFdhh! +  AmpVertexIRosFdToFdhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFdhh=0._dp 
AmpVertexZFdToFdhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdhh(1,gt2,:) = AmpWaveZFdToFdhh(1,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveFdToFdhh(1,gt1,:) 
AmpVertexZFdToFdhh(1,gt2,:)= AmpVertexZFdToFdhh(1,gt2,:) + ZRUZDR(gt2,gt1)*AmpVertexFdToFdhh(1,gt1,:) 
AmpWaveZFdToFdhh(2,gt2,:) = AmpWaveZFdToFdhh(2,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveFdToFdhh(2,gt1,:) 
AmpVertexZFdToFdhh(2,gt2,:)= AmpVertexZFdToFdhh(2,gt2,:) + ZRUZDLc(gt2,gt1)*AmpVertexFdToFdhh(2,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFdhh=AmpWaveZFdToFdhh 
AmpVertexFdToFdhh= AmpVertexZFdToFdhh
! Final State 1 
AmpWaveZFdToFdhh=0._dp 
AmpVertexZFdToFdhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdhh(1,:,gt2) = AmpWaveZFdToFdhh(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFdToFdhh(1,:,gt1) 
AmpVertexZFdToFdhh(1,:,gt2)= AmpVertexZFdToFdhh(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFdToFdhh(1,:,gt1) 
AmpWaveZFdToFdhh(2,:,gt2) = AmpWaveZFdToFdhh(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFdToFdhh(2,:,gt1) 
AmpVertexZFdToFdhh(2,:,gt2)= AmpVertexZFdToFdhh(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFdToFdhh(2,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFdhh=AmpWaveZFdToFdhh 
AmpVertexFdToFdhh= AmpVertexZFdToFdhh
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFdhh = AmpVertexFdToFdhh  +  AmpVertexIRosFdToFdhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFdhh = AmpTreeFdToFdhh 
 AmpSum2FdToFdhh = AmpTreeFdToFdhh + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh  
Else 
 AmpSumFdToFdhh = AmpTreeFdToFdhh + AmpWaveFdToFdhh + AmpVertexFdToFdhh
 AmpSum2FdToFdhh = AmpTreeFdToFdhh + AmpWaveFdToFdhh + AmpVertexFdToFdhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdhh = AmpTreeFdToFdhh
 AmpSum2FdToFdhh = AmpTreeFdToFdhh 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MhhOS)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(Mhh))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FdToFdhh = AmpTreeFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFdhh(gt1, gt2) 
  AmpSum2FdToFdhh = 2._dp*AmpWaveFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFdhh(gt1, gt2) 
  AmpSum2FdToFdhh = 2._dp*AmpVertexFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFdhh(gt1, gt2) 
  AmpSum2FdToFdhh = AmpTreeFdToFdhh + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFdhh(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFdhh = AmpTreeFdToFdhh
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
  AmpSqTreeFdToFdhh(gt1, gt2) = AmpSqFdToFdhh(gt1, gt2)  
  AmpSum2FdToFdhh = + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
  AmpSqFdToFdhh(gt1, gt2) = AmpSqFdToFdhh(gt1, gt2) + AmpSqTreeFdToFdhh(gt1, gt2)  
Else  
  AmpSum2FdToFdhh = AmpTreeFdToFdhh
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
  AmpSqTreeFdToFdhh(gt1, gt2) = AmpSqFdToFdhh(gt1, gt2)  
  AmpSum2FdToFdhh = + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh,AmpSumFdToFdhh(:,gt1, gt2),AmpSum2FdToFdhh(:,gt1, gt2),AmpSqFdToFdhh(gt1, gt2)) 
  AmpSqFdToFdhh(gt1, gt2) = AmpSqFdToFdhh(gt1, gt2) + AmpSqTreeFdToFdhh(gt1, gt2)  
End if  
Else  
  AmpSqFdToFdhh(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdhh(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),MhhOS,helfactor*AmpSqFdToFdhh(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),Mhh,helfactor*AmpSqFdToFdhh(gt1, gt2))
End if 
If ((Abs(MRPFdToFdhh(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdhh(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFdhh(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdhh(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFdhh(gt1, gt2) + MRGFdToFdhh(gt1, gt2)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFdhh(gt1, gt2) + MRGFdToFdhh(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFd(gt1,i4) 
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
! Fd VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FdToFdVZ(cplcFdFdVZL,cplcFdFdVZR,MFd,MVZ,MFd2,             & 
& MVZ2,AmpTreeFdToFdVZ)

  Else 
Call Amplitude_Tree_Inert2_FdToFdVZ(ZcplcFdFdVZL,ZcplcFdFdVZR,MFd,MVZ,MFd2,           & 
& MVZ2,AmpTreeFdToFdVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FdToFdVZ(MLambda,em,gs,cplcFdFdVZL,cplcFdFdVZR,MFdOS,          & 
& MVZOS,MRPFdToFdVZ,MRGFdToFdVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FdToFdVZ(MLambda,em,gs,ZcplcFdFdVZL,ZcplcFdFdVZR,              & 
& MFdOS,MVZOS,MRPFdToFdVZ,MRGFdToFdVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FdToFdVZ(MLambda,em,gs,cplcFdFdVZL,cplcFdFdVZR,MFd,            & 
& MVZ,MRPFdToFdVZ,MRGFdToFdVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FdToFdVZ(MLambda,em,gs,ZcplcFdFdVZL,ZcplcFdFdVZR,              & 
& MFd,MVZ,MRPFdToFdVZ,MRGFdToFdVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FdToFdVZ(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,              & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFd,               & 
& MFd2,MVP,MVP2,MVZ,MVZ2,ZfDL,ZfDR,ZfVPVZ,ZfVZ,AmpWaveFdToFdVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFdVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexFdToFdVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FdToFdVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRdrFdToFdVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdVZ(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,           & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,    & 
& cplcVWpVWpVZ,AmpVertexIRosFdToFdVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,ZcplcFdFdVZL,ZcplcFdFdVZR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRosFdToFdVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdVZ(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,               & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,    & 
& cplcVWpVWpVZ,AmpVertexIRosFdToFdVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFdVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,            & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,AmpVertexIRosFdToFdVZ)

 End if 
 End if 
AmpVertexFdToFdVZ = AmpVertexFdToFdVZ -  AmpVertexIRdrFdToFdVZ! +  AmpVertexIRosFdToFdVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFdVZ=0._dp 
AmpVertexZFdToFdVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdVZ(1,gt2,:) = AmpWaveZFdToFdVZ(1,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveFdToFdVZ(1,gt1,:) 
AmpVertexZFdToFdVZ(1,gt2,:)= AmpVertexZFdToFdVZ(1,gt2,:) + ZRUZDLc(gt2,gt1)*AmpVertexFdToFdVZ(1,gt1,:) 
AmpWaveZFdToFdVZ(2,gt2,:) = AmpWaveZFdToFdVZ(2,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveFdToFdVZ(2,gt1,:) 
AmpVertexZFdToFdVZ(2,gt2,:)= AmpVertexZFdToFdVZ(2,gt2,:) + ZRUZDR(gt2,gt1)*AmpVertexFdToFdVZ(2,gt1,:) 
AmpWaveZFdToFdVZ(3,gt2,:) = AmpWaveZFdToFdVZ(3,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveFdToFdVZ(3,gt1,:) 
AmpVertexZFdToFdVZ(3,gt2,:)= AmpVertexZFdToFdVZ(3,gt2,:) + ZRUZDLc(gt2,gt1)*AmpVertexFdToFdVZ(3,gt1,:) 
AmpWaveZFdToFdVZ(4,gt2,:) = AmpWaveZFdToFdVZ(4,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveFdToFdVZ(4,gt1,:) 
AmpVertexZFdToFdVZ(4,gt2,:)= AmpVertexZFdToFdVZ(4,gt2,:) + ZRUZDR(gt2,gt1)*AmpVertexFdToFdVZ(4,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFdVZ=AmpWaveZFdToFdVZ 
AmpVertexFdToFdVZ= AmpVertexZFdToFdVZ
! Final State 1 
AmpWaveZFdToFdVZ=0._dp 
AmpVertexZFdToFdVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdVZ(1,:,gt2) = AmpWaveZFdToFdVZ(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFdToFdVZ(1,:,gt1) 
AmpVertexZFdToFdVZ(1,:,gt2)= AmpVertexZFdToFdVZ(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFdToFdVZ(1,:,gt1) 
AmpWaveZFdToFdVZ(2,:,gt2) = AmpWaveZFdToFdVZ(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFdToFdVZ(2,:,gt1) 
AmpVertexZFdToFdVZ(2,:,gt2)= AmpVertexZFdToFdVZ(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFdToFdVZ(2,:,gt1) 
AmpWaveZFdToFdVZ(3,:,gt2) = AmpWaveZFdToFdVZ(3,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFdToFdVZ(3,:,gt1) 
AmpVertexZFdToFdVZ(3,:,gt2)= AmpVertexZFdToFdVZ(3,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFdToFdVZ(3,:,gt1) 
AmpWaveZFdToFdVZ(4,:,gt2) = AmpWaveZFdToFdVZ(4,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFdToFdVZ(4,:,gt1) 
AmpVertexZFdToFdVZ(4,:,gt2)= AmpVertexZFdToFdVZ(4,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFdToFdVZ(4,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFdVZ=AmpWaveZFdToFdVZ 
AmpVertexFdToFdVZ= AmpVertexZFdToFdVZ
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFdVZ = AmpVertexFdToFdVZ  +  AmpVertexIRosFdToFdVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFdVZ = AmpTreeFdToFdVZ 
 AmpSum2FdToFdVZ = AmpTreeFdToFdVZ + 2._dp*AmpWaveFdToFdVZ + 2._dp*AmpVertexFdToFdVZ  
Else 
 AmpSumFdToFdVZ = AmpTreeFdToFdVZ + AmpWaveFdToFdVZ + AmpVertexFdToFdVZ
 AmpSum2FdToFdVZ = AmpTreeFdToFdVZ + AmpWaveFdToFdVZ + AmpVertexFdToFdVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdVZ = AmpTreeFdToFdVZ
 AmpSum2FdToFdVZ = AmpTreeFdToFdVZ 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FdToFdVZ = AmpTreeFdToFdVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),MVZOS,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVZ,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFdVZ(gt1, gt2) 
  AmpSum2FdToFdVZ = 2._dp*AmpWaveFdToFdVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),MVZOS,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVZ,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFdVZ(gt1, gt2) 
  AmpSum2FdToFdVZ = 2._dp*AmpVertexFdToFdVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),MVZOS,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVZ,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFdVZ(gt1, gt2) 
  AmpSum2FdToFdVZ = AmpTreeFdToFdVZ + 2._dp*AmpWaveFdToFdVZ + 2._dp*AmpVertexFdToFdVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),MVZOS,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVZ,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFdVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFdVZ = AmpTreeFdToFdVZ
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),MVZOS,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
  AmpSqTreeFdToFdVZ(gt1, gt2) = AmpSqFdToFdVZ(gt1, gt2)  
  AmpSum2FdToFdVZ = + 2._dp*AmpWaveFdToFdVZ + 2._dp*AmpVertexFdToFdVZ
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),MVZOS,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
  AmpSqFdToFdVZ(gt1, gt2) = AmpSqFdToFdVZ(gt1, gt2) + AmpSqTreeFdToFdVZ(gt1, gt2)  
Else  
  AmpSum2FdToFdVZ = AmpTreeFdToFdVZ
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVZ,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
  AmpSqTreeFdToFdVZ(gt1, gt2) = AmpSqFdToFdVZ(gt1, gt2)  
  AmpSum2FdToFdVZ = + 2._dp*AmpWaveFdToFdVZ + 2._dp*AmpVertexFdToFdVZ
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVZ,AmpSumFdToFdVZ(:,gt1, gt2),AmpSum2FdToFdVZ(:,gt1, gt2),AmpSqFdToFdVZ(gt1, gt2)) 
  AmpSqFdToFdVZ(gt1, gt2) = AmpSqFdToFdVZ(gt1, gt2) + AmpSqTreeFdToFdVZ(gt1, gt2)  
End if  
Else  
  AmpSqFdToFdVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdVZ(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),MVZOS,helfactor*AmpSqFdToFdVZ(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),MVZ,helfactor*AmpSqFdToFdVZ(gt1, gt2))
End if 
If ((Abs(MRPFdToFdVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFdVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFdVZ(gt1, gt2) + MRGFdToFdVZ(gt1, gt2)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFdVZ(gt1, gt2) + MRGFdToFdVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFd(gt1,i4) 
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
! Fu Conjg(Hp)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FdToFucHp(cplcFdFucHpL,cplcFdFucHpR,MFd,MFu,               & 
& MHp,MFd2,MFu2,MHp2,AmpTreeFdToFucHp)

  Else 
Call Amplitude_Tree_Inert2_FdToFucHp(ZcplcFdFucHpL,ZcplcFdFucHpR,MFd,MFu,             & 
& MHp,MFd2,MFu2,MHp2,AmpTreeFdToFucHp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FdToFucHp(MLambda,em,gs,cplcFdFucHpL,cplcFdFucHpR,             & 
& MFdOS,MFuOS,MHpOS,MRPFdToFucHp,MRGFdToFucHp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FdToFucHp(MLambda,em,gs,ZcplcFdFucHpL,ZcplcFdFucHpR,           & 
& MFdOS,MFuOS,MHpOS,MRPFdToFucHp,MRGFdToFucHp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FdToFucHp(MLambda,em,gs,cplcFdFucHpL,cplcFdFucHpR,             & 
& MFd,MFu,MHp,MRPFdToFucHp,MRGFdToFucHp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FdToFucHp(MLambda,em,gs,ZcplcFdFucHpL,ZcplcFdFucHpR,           & 
& MFd,MFu,MHp,MRPFdToFucHp,MRGFdToFucHp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FdToFucHp(cplcFdFucHpL,cplcFdFucHpR,ctcplcFdFucHpL,        & 
& ctcplcFdFucHpR,MFd,MFd2,MFu,MFu2,MHp,MHp2,ZfDL,ZfDR,ZfHp,ZfUL,ZfUR,AmpWaveFdToFucHp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFucHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,              & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexFdToFucHp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FdToFucHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRdrFdToFucHp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucHp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,ZcplcFdFucHpL,ZcplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,       & 
& cplG0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& AmpVertexIRosFdToFucHp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& ZcplcFdFucHpL,ZcplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,        & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRosFdToFucHp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucHp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,              & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,      & 
& AmpVertexIRosFdToFucHp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,           & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,AmpVertexIRosFdToFucHp)

 End if 
 End if 
AmpVertexFdToFucHp = AmpVertexFdToFucHp -  AmpVertexIRdrFdToFucHp! +  AmpVertexIRosFdToFucHp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFucHp=0._dp 
AmpVertexZFdToFucHp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFucHp(1,gt2,:,:) = AmpWaveZFdToFucHp(1,gt2,:,:)+ZRUZDR(gt2,gt1)*AmpWaveFdToFucHp(1,gt1,:,:) 
AmpVertexZFdToFucHp(1,gt2,:,:)= AmpVertexZFdToFucHp(1,gt2,:,:) + ZRUZDR(gt2,gt1)*AmpVertexFdToFucHp(1,gt1,:,:) 
AmpWaveZFdToFucHp(2,gt2,:,:) = AmpWaveZFdToFucHp(2,gt2,:,:)+ZRUZDLc(gt2,gt1)*AmpWaveFdToFucHp(2,gt1,:,:) 
AmpVertexZFdToFucHp(2,gt2,:,:)= AmpVertexZFdToFucHp(2,gt2,:,:) + ZRUZDLc(gt2,gt1)*AmpVertexFdToFucHp(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFdToFucHp=AmpWaveZFdToFucHp 
AmpVertexFdToFucHp= AmpVertexZFdToFucHp
! Final State 1 
AmpWaveZFdToFucHp=0._dp 
AmpVertexZFdToFucHp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFucHp(1,:,gt2,:) = AmpWaveZFdToFucHp(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpWaveFdToFucHp(1,:,gt1,:) 
AmpVertexZFdToFucHp(1,:,gt2,:)= AmpVertexZFdToFucHp(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpVertexFdToFucHp(1,:,gt1,:) 
AmpWaveZFdToFucHp(2,:,gt2,:) = AmpWaveZFdToFucHp(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpWaveFdToFucHp(2,:,gt1,:) 
AmpVertexZFdToFucHp(2,:,gt2,:)= AmpVertexZFdToFucHp(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpVertexFdToFucHp(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFucHp=AmpWaveZFdToFucHp 
AmpVertexFdToFucHp= AmpVertexZFdToFucHp
! Final State 2 
AmpWaveZFdToFucHp=0._dp 
AmpVertexZFdToFucHp=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFdToFucHp(:,:,:,gt2) = AmpWaveZFdToFucHp(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveFdToFucHp(:,:,:,gt1) 
AmpVertexZFdToFucHp(:,:,:,gt2)= AmpVertexZFdToFucHp(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexFdToFucHp(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFucHp=AmpWaveZFdToFucHp 
AmpVertexFdToFucHp= AmpVertexZFdToFucHp
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFucHp = AmpVertexFdToFucHp  +  AmpVertexIRosFdToFucHp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fu conj[Hp] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFucHp = AmpTreeFdToFucHp 
 AmpSum2FdToFucHp = AmpTreeFdToFucHp + 2._dp*AmpWaveFdToFucHp + 2._dp*AmpVertexFdToFucHp  
Else 
 AmpSumFdToFucHp = AmpTreeFdToFucHp + AmpWaveFdToFucHp + AmpVertexFdToFucHp
 AmpSum2FdToFucHp = AmpTreeFdToFucHp + AmpWaveFdToFucHp + AmpVertexFdToFucHp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFucHp = AmpTreeFdToFucHp
 AmpSum2FdToFucHp = AmpTreeFdToFucHp 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MHpOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFu(gt2))+Abs(MHp(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FdToFucHp = AmpTreeFdToFucHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHp(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFucHp(gt1, gt2, gt3) 
  AmpSum2FdToFucHp = 2._dp*AmpWaveFdToFucHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHp(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFucHp(gt1, gt2, gt3) 
  AmpSum2FdToFucHp = 2._dp*AmpVertexFdToFucHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHp(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFucHp(gt1, gt2, gt3) 
  AmpSum2FdToFucHp = AmpTreeFdToFucHp + 2._dp*AmpWaveFdToFucHp + 2._dp*AmpVertexFdToFucHp
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHp(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFucHp(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFucHp = AmpTreeFdToFucHp
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
  AmpSqTreeFdToFucHp(gt1, gt2, gt3) = AmpSqFdToFucHp(gt1, gt2, gt3)  
  AmpSum2FdToFucHp = + 2._dp*AmpWaveFdToFucHp + 2._dp*AmpVertexFdToFucHp
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
  AmpSqFdToFucHp(gt1, gt2, gt3) = AmpSqFdToFucHp(gt1, gt2, gt3) + AmpSqTreeFdToFucHp(gt1, gt2, gt3)  
Else  
  AmpSum2FdToFucHp = AmpTreeFdToFucHp
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHp(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
  AmpSqTreeFdToFucHp(gt1, gt2, gt3) = AmpSqFdToFucHp(gt1, gt2, gt3)  
  AmpSum2FdToFucHp = + 2._dp*AmpWaveFdToFucHp + 2._dp*AmpVertexFdToFucHp
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHp(gt3),AmpSumFdToFucHp(:,gt1, gt2, gt3),AmpSum2FdToFucHp(:,gt1, gt2, gt3),AmpSqFdToFucHp(gt1, gt2, gt3)) 
  AmpSqFdToFucHp(gt1, gt2, gt3) = AmpSqFdToFucHp(gt1, gt2, gt3) + AmpSqTreeFdToFucHp(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFdToFucHp(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFucHp(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFuOS(gt2),MHpOS(gt3),helfactor*AmpSqFdToFucHp(gt1, gt2, gt3))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFu(gt2),MHp(gt3),helfactor*AmpSqFdToFucHp(gt1, gt2, gt3))
End if 
If ((Abs(MRPFdToFucHp(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFucHp(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFucHp(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFucHp(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFucHp(gt1, gt2, gt3) + MRGFdToFucHp(gt1, gt2, gt3)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFucHp(gt1, gt2, gt3) + MRGFdToFucHp(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFd(gt1,i4) 
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
! Fu Conjg(VWp)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_Inert2_FdToFucVWp(cplcFdFucVWpL,cplcFdFucVWpR,MFd,MFu,            & 
& MVWp,MFd2,MFu2,MVWp2,AmpTreeFdToFucVWp)

  Else 
Call Amplitude_Tree_Inert2_FdToFucVWp(ZcplcFdFucVWpL,ZcplcFdFucVWpR,MFd,              & 
& MFu,MVWp,MFd2,MFu2,MVWp2,AmpTreeFdToFucVWp)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_Inert2_FdToFucVWp(MLambda,em,gs,cplcFdFucVWpL,cplcFdFucVWpR,          & 
& MFdOS,MFuOS,MVWpOS,MRPFdToFucVWp,MRGFdToFucVWp)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_Inert2_FdToFucVWp(MLambda,em,gs,ZcplcFdFucVWpL,ZcplcFdFucVWpR,        & 
& MFdOS,MFuOS,MVWpOS,MRPFdToFucVWp,MRGFdToFucVWp)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_Inert2_FdToFucVWp(MLambda,em,gs,cplcFdFucVWpL,cplcFdFucVWpR,          & 
& MFd,MFu,MVWp,MRPFdToFucVWp,MRGFdToFucVWp)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_Inert2_FdToFucVWp(MLambda,em,gs,ZcplcFdFucVWpL,ZcplcFdFucVWpR,        & 
& MFd,MFu,MVWp,MRPFdToFucVWp,MRGFdToFucVWp)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FdToFucVWp(cplcFdFucVWpL,cplcFdFucVWpR,ctcplcFdFucVWpL,    & 
& ctcplcFdFucVWpR,MFd,MFd2,MFu,MFu2,MVWp,MVWp2,ZfDL,ZfDR,ZfUL,ZfUR,ZfVWp,AmpWaveFdToFucVWp)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFucVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,             & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0HpcVWp,cplhhHpcVWp,         & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,AmpVertexFdToFucVWp)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_Inert2_FdToFucVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,               & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0HpcVWp,cplhhHpcVWp,         & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,AmpVertexIRdrFdToFucVWp)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucVWp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,             & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,GosZcplcFdFucHpL,GosZcplcFdFucHpR,ZcplcFdFucVWpL,              & 
& ZcplcFdFucVWpR,cplG0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,GosZcplHpcVWpVP,cplHpcVWpVZ,       & 
& cplcVWpVPVWp,cplcVWpVWpVZ,AmpVertexIRosFdToFucVWp)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,               & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& GZcplcFdFucHpL,GZcplcFdFucHpR,ZcplcFdFucVWpL,ZcplcFdFucVWpR,cplG0HpcVWp,               & 
& cplhhHpcVWp,cplhhcVWpVWp,GZcplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,          & 
& AmpVertexIRosFdToFucVWp)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucVWp(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,             & 
& MVG,MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,             & 
& MVZ2OS,cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,GcplcFdFucHpL,GcplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,       & 
& cplG0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,GcplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,            & 
& cplcVWpVWpVZ,AmpVertexIRosFdToFucVWp)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_Inert2_FdToFucVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,               & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0HpcVWp,cplhhHpcVWp,         & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,AmpVertexIRosFdToFucVWp)

 End if 
 End if 
AmpVertexFdToFucVWp = AmpVertexFdToFucVWp -  AmpVertexIRdrFdToFucVWp! +  AmpVertexIRosFdToFucVWp ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFucVWp=0._dp 
AmpVertexZFdToFucVWp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFucVWp(1,gt2,:) = AmpWaveZFdToFucVWp(1,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveFdToFucVWp(1,gt1,:) 
AmpVertexZFdToFucVWp(1,gt2,:)= AmpVertexZFdToFucVWp(1,gt2,:) + ZRUZDLc(gt2,gt1)*AmpVertexFdToFucVWp(1,gt1,:) 
AmpWaveZFdToFucVWp(2,gt2,:) = AmpWaveZFdToFucVWp(2,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveFdToFucVWp(2,gt1,:) 
AmpVertexZFdToFucVWp(2,gt2,:)= AmpVertexZFdToFucVWp(2,gt2,:) + ZRUZDR(gt2,gt1)*AmpVertexFdToFucVWp(2,gt1,:) 
AmpWaveZFdToFucVWp(3,gt2,:) = AmpWaveZFdToFucVWp(3,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveFdToFucVWp(3,gt1,:) 
AmpVertexZFdToFucVWp(3,gt2,:)= AmpVertexZFdToFucVWp(3,gt2,:) + ZRUZDLc(gt2,gt1)*AmpVertexFdToFucVWp(3,gt1,:) 
AmpWaveZFdToFucVWp(4,gt2,:) = AmpWaveZFdToFucVWp(4,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveFdToFucVWp(4,gt1,:) 
AmpVertexZFdToFucVWp(4,gt2,:)= AmpVertexZFdToFucVWp(4,gt2,:) + ZRUZDR(gt2,gt1)*AmpVertexFdToFucVWp(4,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFucVWp=AmpWaveZFdToFucVWp 
AmpVertexFdToFucVWp= AmpVertexZFdToFucVWp
! Final State 1 
AmpWaveZFdToFucVWp=0._dp 
AmpVertexZFdToFucVWp=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFucVWp(1,:,gt2) = AmpWaveZFdToFucVWp(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveFdToFucVWp(1,:,gt1) 
AmpVertexZFdToFucVWp(1,:,gt2)= AmpVertexZFdToFucVWp(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexFdToFucVWp(1,:,gt1) 
AmpWaveZFdToFucVWp(2,:,gt2) = AmpWaveZFdToFucVWp(2,:,gt2)+ZRUZURc(gt2,gt1)*AmpWaveFdToFucVWp(2,:,gt1) 
AmpVertexZFdToFucVWp(2,:,gt2)= AmpVertexZFdToFucVWp(2,:,gt2)+ZRUZURc(gt2,gt1)*AmpVertexFdToFucVWp(2,:,gt1) 
AmpWaveZFdToFucVWp(3,:,gt2) = AmpWaveZFdToFucVWp(3,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveFdToFucVWp(3,:,gt1) 
AmpVertexZFdToFucVWp(3,:,gt2)= AmpVertexZFdToFucVWp(3,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexFdToFucVWp(3,:,gt1) 
AmpWaveZFdToFucVWp(4,:,gt2) = AmpWaveZFdToFucVWp(4,:,gt2)+ZRUZURc(gt2,gt1)*AmpWaveFdToFucVWp(4,:,gt1) 
AmpVertexZFdToFucVWp(4,:,gt2)= AmpVertexZFdToFucVWp(4,:,gt2)+ZRUZURc(gt2,gt1)*AmpVertexFdToFucVWp(4,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFucVWp=AmpWaveZFdToFucVWp 
AmpVertexFdToFucVWp= AmpVertexZFdToFucVWp
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFucVWp = AmpVertexFdToFucVWp  +  AmpVertexIRosFdToFucVWp
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fu conj[VWp] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFucVWp = AmpTreeFdToFucVWp 
 AmpSum2FdToFucVWp = AmpTreeFdToFucVWp + 2._dp*AmpWaveFdToFucVWp + 2._dp*AmpVertexFdToFucVWp  
Else 
 AmpSumFdToFucVWp = AmpTreeFdToFucVWp + AmpWaveFdToFucVWp + AmpVertexFdToFucVWp
 AmpSum2FdToFucVWp = AmpTreeFdToFucVWp + AmpWaveFdToFucVWp + AmpVertexFdToFucVWp 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFucVWp = AmpTreeFdToFucVWp
 AmpSum2FdToFucVWp = AmpTreeFdToFucVWp 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MVWpOS)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFu(gt2))+Abs(MVWp))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FdToFucVWp = AmpTreeFdToFucVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWpOS,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWp,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFucVWp(gt1, gt2) 
  AmpSum2FdToFucVWp = 2._dp*AmpWaveFdToFucVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWpOS,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWp,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFucVWp(gt1, gt2) 
  AmpSum2FdToFucVWp = 2._dp*AmpVertexFdToFucVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWpOS,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWp,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFucVWp(gt1, gt2) 
  AmpSum2FdToFucVWp = AmpTreeFdToFucVWp + 2._dp*AmpWaveFdToFucVWp + 2._dp*AmpVertexFdToFucVWp
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWpOS,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWp,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFucVWp(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFucVWp = AmpTreeFdToFucVWp
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWpOS,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
  AmpSqTreeFdToFucVWp(gt1, gt2) = AmpSqFdToFucVWp(gt1, gt2)  
  AmpSum2FdToFucVWp = + 2._dp*AmpWaveFdToFucVWp + 2._dp*AmpVertexFdToFucVWp
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWpOS,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
  AmpSqFdToFucVWp(gt1, gt2) = AmpSqFdToFucVWp(gt1, gt2) + AmpSqTreeFdToFucVWp(gt1, gt2)  
Else  
  AmpSum2FdToFucVWp = AmpTreeFdToFucVWp
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWp,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
  AmpSqTreeFdToFucVWp(gt1, gt2) = AmpSqFdToFucVWp(gt1, gt2)  
  AmpSum2FdToFucVWp = + 2._dp*AmpWaveFdToFucVWp + 2._dp*AmpVertexFdToFucVWp
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWp,AmpSumFdToFucVWp(:,gt1, gt2),AmpSum2FdToFucVWp(:,gt1, gt2),AmpSqFdToFucVWp(gt1, gt2)) 
  AmpSqFdToFucVWp(gt1, gt2) = AmpSqFdToFucVWp(gt1, gt2) + AmpSqTreeFdToFucVWp(gt1, gt2)  
End if  
Else  
  AmpSqFdToFucVWp(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFucVWp(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFuOS(gt2),MVWpOS,helfactor*AmpSqFdToFucVWp(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFu(gt2),MVWp,helfactor*AmpSqFdToFucVWp(gt1, gt2))
End if 
If ((Abs(MRPFdToFucVWp(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFucVWp(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFucVWp(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFucVWp(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFucVWp(gt1, gt2) + MRGFdToFucVWp(gt1, gt2)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFucVWp(gt1, gt2) + MRGFdToFucVWp(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LFd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End If 
!---------------- 
! Fd A0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FdToFdA0(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,          & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,ZcplA0HpcHp,ZcplA0HpcVWp,ZcplA0cHpVWp,ZcplcFuFdHpL,       & 
& ZcplcFuFdHpR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFdFucVWpL,   & 
& ZcplcFdFucVWpR,AmpVertexFdToFdA0)

 Else 
Call Amplitude_VERTEX_Inert2_FdToFdA0(MA0OS,MFdOS,MFuOS,MHpOS,MVWpOS,MA02OS,          & 
& MFd2OS,MFu2OS,MHp2OS,MVWp2OS,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,           & 
& cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,         & 
& cplcFdFucVWpR,AmpVertexFdToFdA0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFdA0(MA0,MFd,MFu,MHp,MVWp,MA02,MFd2,MFu2,            & 
& MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,    & 
& cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,AmpVertexFdToFdA0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd A0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdA0 = 0._dp 
 AmpSum2FdToFdA0 = 0._dp  
Else 
 AmpSumFdToFdA0 = AmpVertexFdToFdA0 + AmpWaveFdToFdA0
 AmpSum2FdToFdA0 = AmpVertexFdToFdA0 + AmpWaveFdToFdA0 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MA0OS)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(MA0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MA0OS,AmpSumFdToFdA0(:,gt1, gt2),AmpSum2FdToFdA0(:,gt1, gt2),AmpSqFdToFdA0(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MA0,AmpSumFdToFdA0(:,gt1, gt2),AmpSum2FdToFdA0(:,gt1, gt2),AmpSqFdToFdA0(gt1, gt2)) 
End if  
Else  
  AmpSqFdToFdA0(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdA0(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),MA0OS,helfactor*AmpSqFdToFdA0(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),MA0,helfactor*AmpSqFdToFdA0(gt1, gt2))
End if 
If ((Abs(MRPFdToFdA0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdA0(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fd H0
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FdToFdH0(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,          & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,ZcplcFuFdHpL,ZcplcFuFdHpR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,    & 
& ZcplcFdFucHpL,ZcplcFdFucHpR,ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplH0HpcHp,ZcplH0HpcVWp,    & 
& ZcplH0cHpVWp,AmpVertexFdToFdH0)

 Else 
Call Amplitude_VERTEX_Inert2_FdToFdH0(MFdOS,MFuOS,MH0OS,MHpOS,MVWpOS,MFd2OS,          & 
& MFu2OS,MH02OS,MHp2OS,MVWp2OS,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,        & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,          & 
& cplH0cHpVWp,AmpVertexFdToFdH0)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFdH0(MFd,MFu,MH0,MHp,MVWp,MFd2,MFu2,MH02,            & 
& MHp2,MVWp2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,             & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,           & 
& AmpVertexFdToFdH0)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd H0 -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdH0 = 0._dp 
 AmpSum2FdToFdH0 = 0._dp  
Else 
 AmpSumFdToFdH0 = AmpVertexFdToFdH0 + AmpWaveFdToFdH0
 AmpSum2FdToFdH0 = AmpVertexFdToFdH0 + AmpWaveFdToFdH0 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MH0OS)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(MH0))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MH0OS,AmpSumFdToFdH0(:,gt1, gt2),AmpSum2FdToFdH0(:,gt1, gt2),AmpSqFdToFdH0(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MH0,AmpSumFdToFdH0(:,gt1, gt2),AmpSum2FdToFdH0(:,gt1, gt2),AmpSqFdToFdH0(gt1, gt2)) 
End if  
Else  
  AmpSqFdToFdH0(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdH0(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),MH0OS,helfactor*AmpSqFdToFdH0(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),MH0,helfactor*AmpSqFdToFdH0(gt1, gt2))
End if 
If ((Abs(MRPFdToFdH0(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdH0(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fd VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_FdToFdVG(ZcplcFdFdVGL,ZcplcFdFdVGR,ctcplcFdFdVGL,          & 
& ctcplcFdFdVGR,MFdOS,MFd2OS,MVG,MVG2,ZfDL,ZfDR,ZfVG,AmpWaveFdToFdVG)

 Else 
Call Amplitude_WAVE_Inert2_FdToFdVG(cplcFdFdVGL,cplcFdFdVGR,ctcplcFdFdVGL,            & 
& ctcplcFdFdVGR,MFdOS,MFd2OS,MVG,MVG2,ZfDL,ZfDR,ZfVG,AmpWaveFdToFdVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FdToFdVG(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& ZcplcFdFdG0L,ZcplcFdFdG0R,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFuFdHpL,ZcplcFuFdHpR,         & 
& ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,       & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFdFucHpL,ZcplcFdFucHpR,       & 
& ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplVGVGVG,AmpVertexFdToFdVG)

 Else 
Call Amplitude_VERTEX_Inert2_FdToFdVG(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,               & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuVGL,cplcFuFuVGR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplVGVGVG,AmpVertexFdToFdVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FdToFdVG(cplcFdFdVGL,cplcFdFdVGR,ctcplcFdFdVGL,            & 
& ctcplcFdFdVGR,MFd,MFd2,MVG,MVG2,ZfDL,ZfDR,ZfVG,AmpWaveFdToFdVG)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFdVG(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplVGVGVG,AmpVertexFdToFdVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdVG = 0._dp 
 AmpSum2FdToFdVG = 0._dp  
Else 
 AmpSumFdToFdVG = AmpVertexFdToFdVG + AmpWaveFdToFdVG
 AmpSum2FdToFdVG = AmpVertexFdToFdVG + AmpWaveFdToFdVG 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),0._dp,AmpSumFdToFdVG(:,gt1, gt2),AmpSum2FdToFdVG(:,gt1, gt2),AmpSqFdToFdVG(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVG,AmpSumFdToFdVG(:,gt1, gt2),AmpSum2FdToFdVG(:,gt1, gt2),AmpSqFdToFdVG(gt1, gt2)) 
End if  
Else  
  AmpSqFdToFdVG(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdVG(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 4._dp/3._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),0._dp,helfactor*AmpSqFdToFdVG(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 4._dp/3._dp*GammaTPS(MFd(gt1),MFd(gt2),MVG,helfactor*AmpSqFdToFdVG(gt1, gt2))
End if 
If ((Abs(MRPFdToFdVG(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdVG(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fd VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_Inert2_FdToFdVP(ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,           & 
& ZcplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFdOS,            & 
& MFd2OS,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,AmpWaveFdToFdVP)

 Else 
Call Amplitude_WAVE_Inert2_FdToFdVP(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,              & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFdOS,             & 
& MFd2OS,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,AmpWaveFdToFdVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_Inert2_FdToFdVP(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& ZcplcFdFdG0L,ZcplcFdFdG0R,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFuFdHpL,ZcplcFuFdHpR,         & 
& ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdVWpL,ZcplcFuFdVWpR,       & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFucHpL,ZcplcFdFucHpR,       & 
& ZcplcFdFucVWpL,ZcplcFdFucVWpR,ZcplHpcHpVP,ZcplHpcVWpVP,ZcplcHpVPVWp,ZcplcVWpVPVWp,     & 
& AmpVertexFdToFdVP)

 Else 
Call Amplitude_VERTEX_Inert2_FdToFdVP(MFdOS,MFuOS,MG0OS,MhhOS,MHpOS,MVG,              & 
& MVP,MVWpOS,MVZOS,MFd2OS,MFu2OS,MG02OS,Mhh2OS,MHp2OS,MVG2,MVP2,MVWp2OS,MVZ2OS,          & 
& cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,               & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,           & 
& AmpVertexFdToFdVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_Inert2_FdToFdVP(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,              & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFd,               & 
& MFd2,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,AmpWaveFdToFdVP)



!Vertex Corrections 
Call Amplitude_VERTEX_Inert2_FdToFdVP(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,MVWp,               & 
& MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,AmpVertexFdToFdVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdVP = 0._dp 
 AmpSum2FdToFdVP = 0._dp  
Else 
 AmpSumFdToFdVP = AmpVertexFdToFdVP + AmpWaveFdToFdVP
 AmpSum2FdToFdVP = AmpVertexFdToFdVP + AmpWaveFdToFdVP 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFdOS(gt2),0._dp,AmpSumFdToFdVP(:,gt1, gt2),AmpSum2FdToFdVP(:,gt1, gt2),AmpSqFdToFdVP(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFd(gt2),MVP,AmpSumFdToFdVP(:,gt1, gt2),AmpSum2FdToFdVP(:,gt1, gt2),AmpSqFdToFdVP(gt1, gt2)) 
End if  
Else  
  AmpSqFdToFdVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdVP(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),0._dp,helfactor*AmpSqFdToFdVP(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),MVP,helfactor*AmpSqFdToFdVP(gt1, gt2))
End if 
If ((Abs(MRPFdToFdVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.3) isave = i4 
End do
End Subroutine OneLoopDecay_Fd

End Module Wrapper_OneLoopDecay_Fd_Inert2
