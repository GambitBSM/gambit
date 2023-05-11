! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Fd_gumTHDMII
Use Model_Data_gumTHDMII 
Use Kinematics 
Use OneLoopDecay_Fd_gumTHDMII 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Fd(MhhOS,Mhh2OS,MAhOS,MAh2OS,MHmOS,MHm2OS,MFdOS,              & 
& MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS,ZAOS,ZPOS,           & 
& ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,               & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,              & 
& ZP,ZW,ZZ,alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,            & 
& m222,vd,vu,dg1,dg2,dg3,dm122,dYu,dYd,dYe,dlam5,dm112,dm222,dlam1,dlam4,dlam3,          & 
& dlam2,dvd,dvu,dZH,dZA,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,          & 
& ZfVG,ZfvL,ZfVP,ZfVZ,ZfVWm,Zfhh,ZfAh,ZfHm,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,ZfVPVZ,         & 
& ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcHmVPVWm,cplcHmVWmVZ,               & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,               & 
& cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,cplHmcVWmVZ,cplVGVGVG,         & 
& ctcplcFdFdAhL,ctcplcFdFdAhR,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFdFdVGL,ctcplcFdFdVGR,   & 
& ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,ctcplcFdFuHmL,ctcplcFdFuHmR,   & 
& ctcplcFdFuVWmL,ctcplcFdFuVWmR,GcplcFdFuHmL,GcplcFdFuHmR,GcplcHmVPVWm,GcplHmcVWmVP,     & 
& GosZcplcFdFuHmL,GosZcplcFdFuHmR,GosZcplcHmVPVWm,GosZcplHmcVWmVP,GZcplcFdFuHmL,         & 
& GZcplcFdFuHmR,GZcplcHmVPVWm,GZcplHmcVWmVP,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFdFdhhL,      & 
& ZcplcFdFdhhR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,         & 
& ZcplcFdFdVZR,ZcplcFdFuHmL,ZcplcFdFuHmR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplcFuFdcHmL,      & 
& ZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,    & 
& ZcplcFuFuVPR,ZcplcHmVPVWm,ZcplcVWmVPVWm,ZcplHmcHmVP,ZcplHmcVWmVP,ZcplVGVGVG,           & 
& ZRUZH,ZRUZA,ZRUZP,ZRUVd,ZRUUd,ZRUVu,ZRUUu,ZRUVe,ZRUUe,MLambda,em,gs,deltaM,            & 
& kont,gP1LFd)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Real(dp),Intent(in) :: vd,vu

Real(dp),Intent(in) :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),               & 
& alphaH,betaH

Complex(dp),Intent(in) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Real(dp),Intent(in) :: dg1,dg2,dg3,dvd,dvu,dZH(2,2),dZA(2,2),dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp),Intent(in) :: dm122,dYu(3,3),dYd(3,3),dYe(3,3),dlam5,dm112,dm222,dlam1,dlam4,dlam3,dlam2,           & 
& dZDL(3,3),dZDR(3,3),dZUL(3,3),dZUR(3,3),dZEL(3,3),dZER(3,3)

Complex(dp),Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhcHmVWm(2,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),   & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),               & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHmL(3,3,2),& 
& cplcFdFuHmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFdcHmL(3,3,2),            & 
& cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),          & 
& cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcHmVPVWm(2),cplcHmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm(2,2),              & 
& cplhhcVWmVWm(2),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhVZVZ(2),      & 
& cplHmcHmVP(2,2),cplHmcHmVZ(2,2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplVGVGVG,               & 
& ctcplcFdFdAhL(3,3,2),ctcplcFdFdAhR(3,3,2),ctcplcFdFdhhL(3,3,2),ctcplcFdFdhhR(3,3,2),   & 
& ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),ctcplcFdFdVPL(3,3),ctcplcFdFdVPR(3,3),           & 
& ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3),ctcplcFdFuHmL(3,3,2),ctcplcFdFuHmR(3,3,2),       & 
& ctcplcFdFuVWmL(3,3),ctcplcFdFuVWmR(3,3),GcplcFdFuHmL(3,3,2),GcplcFdFuHmR(3,3,2),       & 
& GcplcHmVPVWm(2),GcplHmcVWmVP(2),GosZcplcFdFuHmL(3,3,2),GosZcplcFdFuHmR(3,3,2),         & 
& GosZcplcHmVPVWm(2),GosZcplHmcVWmVP(2),GZcplcFdFuHmL(3,3,2),GZcplcFdFuHmR(3,3,2),       & 
& GZcplcHmVPVWm(2),GZcplHmcVWmVP(2),ZcplcFdFdAhL(3,3,2),ZcplcFdFdAhR(3,3,2),             & 
& ZcplcFdFdhhL(3,3,2),ZcplcFdFdhhR(3,3,2),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),           & 
& ZcplcFdFdVPL(3,3),ZcplcFdFdVPR(3,3),ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),               & 
& ZcplcFdFuHmL(3,3,2),ZcplcFdFuHmR(3,3,2),ZcplcFdFuVWmL(3,3),ZcplcFdFuVWmR(3,3),         & 
& ZcplcFuFdcHmL(3,3,2),ZcplcFuFdcHmR(3,3,2),ZcplcFuFdcVWmL(3,3),ZcplcFuFdcVWmR(3,3),     & 
& ZcplcFuFuVGL(3,3),ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),               & 
& ZcplcHmVPVWm(2),ZcplcVWmVPVWm,ZcplHmcHmVP(2,2),ZcplHmcVWmVP(2),ZcplVGVGVG

Real(dp), Intent(in) :: em, gs 
Complex(dp),Intent(in) :: ZfVG,ZfvL(3,3),ZfVP,ZfVZ,ZfVWm,Zfhh(2,2),ZfAh(2,2),ZfHm(2,2),ZfDL(3,3),               & 
& ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfEL(3,3),ZfER(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MhhOS(2),Mhh2OS(2),MAhOS(2),MAh2OS(2),MHmOS(2),MHm2OS(2),MFdOS(3),MFd2OS(3),          & 
& MFuOS(3),MFu2OS(3),MFeOS(3),MFe2OS(3),MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(2,2),           & 
& ZAOS(2,2),ZPOS(2,2)

Complex(dp),Intent(in) :: ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3),ZELOS(3,3),ZEROS(3,3)

Complex(dp),Intent(in) :: ZRUZH(2,2),ZRUZA(2,2),ZRUZP(2,2),ZRUVd(3,3),ZRUUd(3,3),ZRUVu(3,3),ZRUUu(3,3),         & 
& ZRUVe(3,3),ZRUUe(3,3)

Real(dp), Intent(in) :: MLambda, deltaM 
Real(dp), Intent(out) :: gP1LFd(3,24) 
Integer, Intent(out) :: kont 
Real(dp) :: MVG,MVP,MVG2,MVP2, helfactor, phasespacefactor 
Integer :: i1,i2,i3,i4, isave, gt1, gt2, gt3 

Complex(dp) :: ZRUZHc(2, 2) 
Complex(dp) :: ZRUZAc(2, 2) 
Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUVdc(3, 3) 
Complex(dp) :: ZRUUdc(3, 3) 
Complex(dp) :: ZRUVuc(3, 3) 
Complex(dp) :: ZRUUuc(3, 3) 
Complex(dp) :: ZRUVec(3, 3) 
Complex(dp) :: ZRUUec(3, 3) 
Real(dp) :: MRPFdToFdAh(3,3,2),MRGFdToFdAh(3,3,2), MRPZFdToFdAh(3,3,2),MRGZFdToFdAh(3,3,2) 
Real(dp) :: MVPFdToFdAh(3,3,2) 
Real(dp) :: RMsqTreeFdToFdAh(3,3,2),RMsqWaveFdToFdAh(3,3,2),RMsqVertexFdToFdAh(3,3,2) 
Complex(dp) :: AmpTreeFdToFdAh(2,3,3,2),AmpWaveFdToFdAh(2,3,3,2)=(0._dp,0._dp),AmpVertexFdToFdAh(2,3,3,2)& 
 & ,AmpVertexIRosFdToFdAh(2,3,3,2),AmpVertexIRdrFdToFdAh(2,3,3,2), AmpSumFdToFdAh(2,3,3,2), AmpSum2FdToFdAh(2,3,3,2) 
Complex(dp) :: AmpTreeZFdToFdAh(2,3,3,2),AmpWaveZFdToFdAh(2,3,3,2),AmpVertexZFdToFdAh(2,3,3,2) 
Real(dp) :: AmpSqFdToFdAh(3,3,2),  AmpSqTreeFdToFdAh(3,3,2) 
Real(dp) :: MRPFdToFdhh(3,3,2),MRGFdToFdhh(3,3,2), MRPZFdToFdhh(3,3,2),MRGZFdToFdhh(3,3,2) 
Real(dp) :: MVPFdToFdhh(3,3,2) 
Real(dp) :: RMsqTreeFdToFdhh(3,3,2),RMsqWaveFdToFdhh(3,3,2),RMsqVertexFdToFdhh(3,3,2) 
Complex(dp) :: AmpTreeFdToFdhh(2,3,3,2),AmpWaveFdToFdhh(2,3,3,2)=(0._dp,0._dp),AmpVertexFdToFdhh(2,3,3,2)& 
 & ,AmpVertexIRosFdToFdhh(2,3,3,2),AmpVertexIRdrFdToFdhh(2,3,3,2), AmpSumFdToFdhh(2,3,3,2), AmpSum2FdToFdhh(2,3,3,2) 
Complex(dp) :: AmpTreeZFdToFdhh(2,3,3,2),AmpWaveZFdToFdhh(2,3,3,2),AmpVertexZFdToFdhh(2,3,3,2) 
Real(dp) :: AmpSqFdToFdhh(3,3,2),  AmpSqTreeFdToFdhh(3,3,2) 
Real(dp) :: MRPFdToFdVZ(3,3),MRGFdToFdVZ(3,3), MRPZFdToFdVZ(3,3),MRGZFdToFdVZ(3,3) 
Real(dp) :: MVPFdToFdVZ(3,3) 
Real(dp) :: RMsqTreeFdToFdVZ(3,3),RMsqWaveFdToFdVZ(3,3),RMsqVertexFdToFdVZ(3,3) 
Complex(dp) :: AmpTreeFdToFdVZ(4,3,3),AmpWaveFdToFdVZ(4,3,3)=(0._dp,0._dp),AmpVertexFdToFdVZ(4,3,3)& 
 & ,AmpVertexIRosFdToFdVZ(4,3,3),AmpVertexIRdrFdToFdVZ(4,3,3), AmpSumFdToFdVZ(4,3,3), AmpSum2FdToFdVZ(4,3,3) 
Complex(dp) :: AmpTreeZFdToFdVZ(4,3,3),AmpWaveZFdToFdVZ(4,3,3),AmpVertexZFdToFdVZ(4,3,3) 
Real(dp) :: AmpSqFdToFdVZ(3,3),  AmpSqTreeFdToFdVZ(3,3) 
Real(dp) :: MRPFdToFuHm(3,3,2),MRGFdToFuHm(3,3,2), MRPZFdToFuHm(3,3,2),MRGZFdToFuHm(3,3,2) 
Real(dp) :: MVPFdToFuHm(3,3,2) 
Real(dp) :: RMsqTreeFdToFuHm(3,3,2),RMsqWaveFdToFuHm(3,3,2),RMsqVertexFdToFuHm(3,3,2) 
Complex(dp) :: AmpTreeFdToFuHm(2,3,3,2),AmpWaveFdToFuHm(2,3,3,2)=(0._dp,0._dp),AmpVertexFdToFuHm(2,3,3,2)& 
 & ,AmpVertexIRosFdToFuHm(2,3,3,2),AmpVertexIRdrFdToFuHm(2,3,3,2), AmpSumFdToFuHm(2,3,3,2), AmpSum2FdToFuHm(2,3,3,2) 
Complex(dp) :: AmpTreeZFdToFuHm(2,3,3,2),AmpWaveZFdToFuHm(2,3,3,2),AmpVertexZFdToFuHm(2,3,3,2) 
Real(dp) :: AmpSqFdToFuHm(3,3,2),  AmpSqTreeFdToFuHm(3,3,2) 
Real(dp) :: MRPFdToFuVWm(3,3),MRGFdToFuVWm(3,3), MRPZFdToFuVWm(3,3),MRGZFdToFuVWm(3,3) 
Real(dp) :: MVPFdToFuVWm(3,3) 
Real(dp) :: RMsqTreeFdToFuVWm(3,3),RMsqWaveFdToFuVWm(3,3),RMsqVertexFdToFuVWm(3,3) 
Complex(dp) :: AmpTreeFdToFuVWm(4,3,3),AmpWaveFdToFuVWm(4,3,3)=(0._dp,0._dp),AmpVertexFdToFuVWm(4,3,3)& 
 & ,AmpVertexIRosFdToFuVWm(4,3,3),AmpVertexIRdrFdToFuVWm(4,3,3), AmpSumFdToFuVWm(4,3,3), AmpSum2FdToFuVWm(4,3,3) 
Complex(dp) :: AmpTreeZFdToFuVWm(4,3,3),AmpWaveZFdToFuVWm(4,3,3),AmpVertexZFdToFuVWm(4,3,3) 
Real(dp) :: AmpSqFdToFuVWm(3,3),  AmpSqTreeFdToFuVWm(3,3) 
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

ZRUZHc = Conjg(ZRUZH)
ZRUZAc = Conjg(ZRUZA)
ZRUZPc = Conjg(ZRUZP)
ZRUVdc = Conjg(ZRUVd)
ZRUUdc = Conjg(ZRUUd)
ZRUVuc = Conjg(ZRUVu)
ZRUUuc = Conjg(ZRUUu)
ZRUVec = Conjg(ZRUVe)
ZRUUec = Conjg(ZRUUe)

 ! Counter 
isave = 1 

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fd Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FdToFdAh(cplcFdFdAhL,cplcFdFdAhR,MAh,MFd,               & 
& MAh2,MFd2,AmpTreeFdToFdAh)

  Else 
Call Amplitude_Tree_gumTHDMII_FdToFdAh(ZcplcFdFdAhL,ZcplcFdFdAhR,MAh,MFd,             & 
& MAh2,MFd2,AmpTreeFdToFdAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdAh(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,             & 
& MAhOS,MFdOS,MRPFdToFdAh,MRGFdToFdAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdAh(MLambda,em,gs,ZcplcFdFdAhL,ZcplcFdFdAhR,           & 
& MAhOS,MFdOS,MRPFdToFdAh,MRGFdToFdAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FdToFdAh(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,             & 
& MAh,MFd,MRPFdToFdAh,MRGFdToFdAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdAh(MLambda,em,gs,ZcplcFdFdAhL,ZcplcFdFdAhR,           & 
& MAh,MFd,MRPFdToFdAh,MRGFdToFdAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFdAh(cplcFdFdAhL,cplcFdFdAhR,ctcplcFdFdAhL,         & 
& ctcplcFdFdAhR,MAh,MAh2,MFd,MFd2,ZfAh,ZfDL,ZfDR,AmpWaveFdToFdAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFdAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,        & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,               & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,           & 
& cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,AmpVertexFdToFdAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& AmpVertexIRdrFdToFdAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdAh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,ZcplcFdFdAhL,ZcplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,          & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,AmpVertexIRosFdToFdAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& ZcplcFdFdAhL,ZcplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,      & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& AmpVertexIRosFdToFdAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdAh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,AmpVertexIRosFdToFdAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& AmpVertexIRosFdToFdAh)

 End if 
 End if 
AmpVertexFdToFdAh = AmpVertexFdToFdAh -  AmpVertexIRdrFdToFdAh! +  AmpVertexIRosFdToFdAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFdAh=0._dp 
AmpVertexZFdToFdAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdAh(1,gt2,:,:) = AmpWaveZFdToFdAh(1,gt2,:,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFdAh(1,gt1,:,:) 
AmpVertexZFdToFdAh(1,gt2,:,:)= AmpVertexZFdToFdAh(1,gt2,:,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFdAh(1,gt1,:,:) 
AmpWaveZFdToFdAh(2,gt2,:,:) = AmpWaveZFdToFdAh(2,gt2,:,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFdAh(2,gt1,:,:) 
AmpVertexZFdToFdAh(2,gt2,:,:)= AmpVertexZFdToFdAh(2,gt2,:,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFdAh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFdToFdAh=AmpWaveZFdToFdAh 
AmpVertexFdToFdAh= AmpVertexZFdToFdAh
! Final State 1 
AmpWaveZFdToFdAh=0._dp 
AmpVertexZFdToFdAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdAh(1,:,gt2,:) = AmpWaveZFdToFdAh(1,:,gt2,:)+ZRUVd(gt2,gt1)*AmpWaveFdToFdAh(1,:,gt1,:) 
AmpVertexZFdToFdAh(1,:,gt2,:)= AmpVertexZFdToFdAh(1,:,gt2,:)+ZRUVd(gt2,gt1)*AmpVertexFdToFdAh(1,:,gt1,:) 
AmpWaveZFdToFdAh(2,:,gt2,:) = AmpWaveZFdToFdAh(2,:,gt2,:)+ZRUUdc(gt2,gt1)*AmpWaveFdToFdAh(2,:,gt1,:) 
AmpVertexZFdToFdAh(2,:,gt2,:)= AmpVertexZFdToFdAh(2,:,gt2,:)+ZRUUdc(gt2,gt1)*AmpVertexFdToFdAh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFdAh=AmpWaveZFdToFdAh 
AmpVertexFdToFdAh= AmpVertexZFdToFdAh
! Final State 2 
AmpWaveZFdToFdAh=0._dp 
AmpVertexZFdToFdAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFdToFdAh(:,:,:,gt2) = AmpWaveZFdToFdAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveFdToFdAh(:,:,:,gt1) 
AmpVertexZFdToFdAh(:,:,:,gt2)= AmpVertexZFdToFdAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexFdToFdAh(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFdAh=AmpWaveZFdToFdAh 
AmpVertexFdToFdAh= AmpVertexZFdToFdAh
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFdAh = AmpVertexFdToFdAh  +  AmpVertexIRosFdToFdAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fd Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFdAh = AmpTreeFdToFdAh 
 AmpSum2FdToFdAh = AmpTreeFdToFdAh + 2._dp*AmpWaveFdToFdAh + 2._dp*AmpVertexFdToFdAh  
Else 
 AmpSumFdToFdAh = AmpTreeFdToFdAh + AmpWaveFdToFdAh + AmpVertexFdToFdAh
 AmpSum2FdToFdAh = AmpTreeFdToFdAh + AmpWaveFdToFdAh + AmpVertexFdToFdAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFdAh = AmpTreeFdToFdAh
 AmpSum2FdToFdAh = AmpTreeFdToFdAh 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FdToFdAh = AmpTreeFdToFdAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MAh(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFdAh(gt1, gt2, gt3) 
  AmpSum2FdToFdAh = 2._dp*AmpWaveFdToFdAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MAh(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFdAh(gt1, gt2, gt3) 
  AmpSum2FdToFdAh = 2._dp*AmpVertexFdToFdAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MAh(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFdAh(gt1, gt2, gt3) 
  AmpSum2FdToFdAh = AmpTreeFdToFdAh + 2._dp*AmpWaveFdToFdAh + 2._dp*AmpVertexFdToFdAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MAh(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFdAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFdAh = AmpTreeFdToFdAh
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
  AmpSqTreeFdToFdAh(gt1, gt2, gt3) = AmpSqFdToFdAh(gt1, gt2, gt3)  
  AmpSum2FdToFdAh = + 2._dp*AmpWaveFdToFdAh + 2._dp*AmpVertexFdToFdAh
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
  AmpSqFdToFdAh(gt1, gt2, gt3) = AmpSqFdToFdAh(gt1, gt2, gt3) + AmpSqTreeFdToFdAh(gt1, gt2, gt3)  
Else  
  AmpSum2FdToFdAh = AmpTreeFdToFdAh
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MAh(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
  AmpSqTreeFdToFdAh(gt1, gt2, gt3) = AmpSqFdToFdAh(gt1, gt2, gt3)  
  AmpSum2FdToFdAh = + 2._dp*AmpWaveFdToFdAh + 2._dp*AmpVertexFdToFdAh
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),MAh(gt3),AmpSumFdToFdAh(:,gt1, gt2, gt3),AmpSum2FdToFdAh(:,gt1, gt2, gt3),AmpSqFdToFdAh(gt1, gt2, gt3)) 
  AmpSqFdToFdAh(gt1, gt2, gt3) = AmpSqFdToFdAh(gt1, gt2, gt3) + AmpSqTreeFdToFdAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFdToFdAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),MAhOS(gt3),helfactor*AmpSqFdToFdAh(gt1, gt2, gt3))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),MAh(gt3),helfactor*AmpSqFdToFdAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPFdToFdAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFdAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFdAh(gt1, gt2, gt3) + MRGFdToFdAh(gt1, gt2, gt3)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFdAh(gt1, gt2, gt3) + MRGFdToFdAh(gt1, gt2, gt3))
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
! Fd hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FdToFdhh(cplcFdFdhhL,cplcFdFdhhR,MFd,Mhh,               & 
& MFd2,Mhh2,AmpTreeFdToFdhh)

  Else 
Call Amplitude_Tree_gumTHDMII_FdToFdhh(ZcplcFdFdhhL,ZcplcFdFdhhR,MFd,Mhh,             & 
& MFd2,Mhh2,AmpTreeFdToFdhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdhh(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,             & 
& MFdOS,MhhOS,MRPFdToFdhh,MRGFdToFdhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdhh(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,           & 
& MFdOS,MhhOS,MRPFdToFdhh,MRGFdToFdhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FdToFdhh(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,             & 
& MFd,Mhh,MRPFdToFdhh,MRGFdToFdhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdhh(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,           & 
& MFd,Mhh,MRPFdToFdhh,MRGFdToFdhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFdhh(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,         & 
& ctcplcFdFdhhR,MFd,MFd2,Mhh,Mhh2,ZfDL,ZfDR,Zfhh,AmpWaveFdToFdhh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFdhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,               & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexFdToFdhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRdrFdToFdhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdhh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,ZcplcFdFdhhL,             & 
& ZcplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,              & 
& cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFdToFdhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,     & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRosFdToFdhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdhh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFdToFdhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
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
AmpWaveZFdToFdhh(1,gt2,:,:) = AmpWaveZFdToFdhh(1,gt2,:,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFdhh(1,gt1,:,:) 
AmpVertexZFdToFdhh(1,gt2,:,:)= AmpVertexZFdToFdhh(1,gt2,:,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFdhh(1,gt1,:,:) 
AmpWaveZFdToFdhh(2,gt2,:,:) = AmpWaveZFdToFdhh(2,gt2,:,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFdhh(2,gt1,:,:) 
AmpVertexZFdToFdhh(2,gt2,:,:)= AmpVertexZFdToFdhh(2,gt2,:,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFdhh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFdToFdhh=AmpWaveZFdToFdhh 
AmpVertexFdToFdhh= AmpVertexZFdToFdhh
! Final State 1 
AmpWaveZFdToFdhh=0._dp 
AmpVertexZFdToFdhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdhh(1,:,gt2,:) = AmpWaveZFdToFdhh(1,:,gt2,:)+ZRUVd(gt2,gt1)*AmpWaveFdToFdhh(1,:,gt1,:) 
AmpVertexZFdToFdhh(1,:,gt2,:)= AmpVertexZFdToFdhh(1,:,gt2,:)+ZRUVd(gt2,gt1)*AmpVertexFdToFdhh(1,:,gt1,:) 
AmpWaveZFdToFdhh(2,:,gt2,:) = AmpWaveZFdToFdhh(2,:,gt2,:)+ZRUUdc(gt2,gt1)*AmpWaveFdToFdhh(2,:,gt1,:) 
AmpVertexZFdToFdhh(2,:,gt2,:)= AmpVertexZFdToFdhh(2,:,gt2,:)+ZRUUdc(gt2,gt1)*AmpVertexFdToFdhh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFdhh=AmpWaveZFdToFdhh 
AmpVertexFdToFdhh= AmpVertexZFdToFdhh
! Final State 2 
AmpWaveZFdToFdhh=0._dp 
AmpVertexZFdToFdhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFdToFdhh(:,:,:,gt2) = AmpWaveZFdToFdhh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveFdToFdhh(:,:,:,gt1) 
AmpVertexZFdToFdhh(:,:,:,gt2)= AmpVertexZFdToFdhh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexFdToFdhh(:,:,:,gt1) 
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
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFd(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FdToFdhh = AmpTreeFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFdhh(gt1, gt2, gt3) 
  AmpSum2FdToFdhh = 2._dp*AmpWaveFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFdhh(gt1, gt2, gt3) 
  AmpSum2FdToFdhh = 2._dp*AmpVertexFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFdhh(gt1, gt2, gt3) 
  AmpSum2FdToFdhh = AmpTreeFdToFdhh + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFdhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFdhh = AmpTreeFdToFdhh
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
  AmpSqTreeFdToFdhh(gt1, gt2, gt3) = AmpSqFdToFdhh(gt1, gt2, gt3)  
  AmpSum2FdToFdhh = + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh
  Call SquareAmp_FtoFS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
  AmpSqFdToFdhh(gt1, gt2, gt3) = AmpSqFdToFdhh(gt1, gt2, gt3) + AmpSqTreeFdToFdhh(gt1, gt2, gt3)  
Else  
  AmpSum2FdToFdhh = AmpTreeFdToFdhh
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
  AmpSqTreeFdToFdhh(gt1, gt2, gt3) = AmpSqFdToFdhh(gt1, gt2, gt3)  
  AmpSum2FdToFdhh = + 2._dp*AmpWaveFdToFdhh + 2._dp*AmpVertexFdToFdhh
  Call SquareAmp_FtoFS(MFd(gt1),MFd(gt2),Mhh(gt3),AmpSumFdToFdhh(:,gt1, gt2, gt3),AmpSum2FdToFdhh(:,gt1, gt2, gt3),AmpSqFdToFdhh(gt1, gt2, gt3)) 
  AmpSqFdToFdhh(gt1, gt2, gt3) = AmpSqFdToFdhh(gt1, gt2, gt3) + AmpSqTreeFdToFdhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFdToFdhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFdhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFdOS(gt2),MhhOS(gt3),helfactor*AmpSqFdToFdhh(gt1, gt2, gt3))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFd(gt2),Mhh(gt3),helfactor*AmpSqFdToFdhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPFdToFdhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFdhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFdhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFdhh(gt1, gt2, gt3) + MRGFdToFdhh(gt1, gt2, gt3)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFdhh(gt1, gt2, gt3) + MRGFdToFdhh(gt1, gt2, gt3))
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
! Fd VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FdToFdVZ(cplcFdFdVZL,cplcFdFdVZR,MFd,MVZ,               & 
& MFd2,MVZ2,AmpTreeFdToFdVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_FdToFdVZ(ZcplcFdFdVZL,ZcplcFdFdVZR,MFd,MVZ,             & 
& MFd2,MVZ2,AmpTreeFdToFdVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdVZ(MLambda,em,gs,cplcFdFdVZL,cplcFdFdVZR,             & 
& MFdOS,MVZOS,MRPFdToFdVZ,MRGFdToFdVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdVZ(MLambda,em,gs,ZcplcFdFdVZL,ZcplcFdFdVZR,           & 
& MFdOS,MVZOS,MRPFdToFdVZ,MRGFdToFdVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FdToFdVZ(MLambda,em,gs,cplcFdFdVZL,cplcFdFdVZR,             & 
& MFd,MVZ,MRPFdToFdVZ,MRGFdToFdVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFdVZ(MLambda,em,gs,ZcplcFdFdVZL,ZcplcFdFdVZR,           & 
& MFd,MVZ,MRPFdToFdVZ,MRGFdToFdVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFdVZ(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,           & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFd,               & 
& MFd2,MVP,MVP2,MVZ,MVZ2,ZfDL,ZfDR,ZfVPVZ,ZfVZ,AmpWaveFdToFdVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,     & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexFdToFdVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,     & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRdrFdToFdVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdVZ(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,ZcplcFdFdVZL,ZcplcFdFdVZR,cplcFuFdcHmL,            & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexIRosFdToFdVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,     & 
& ZcplcFdFdVZL,ZcplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFdToFdVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdVZ(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexIRosFdToFdVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFdVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,     & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFdToFdVZ)

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
AmpWaveZFdToFdVZ(1,gt2,:) = AmpWaveZFdToFdVZ(1,gt2,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFdVZ(1,gt1,:) 
AmpVertexZFdToFdVZ(1,gt2,:)= AmpVertexZFdToFdVZ(1,gt2,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFdVZ(1,gt1,:) 
AmpWaveZFdToFdVZ(2,gt2,:) = AmpWaveZFdToFdVZ(2,gt2,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFdVZ(2,gt1,:) 
AmpVertexZFdToFdVZ(2,gt2,:)= AmpVertexZFdToFdVZ(2,gt2,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFdVZ(2,gt1,:) 
AmpWaveZFdToFdVZ(3,gt2,:) = AmpWaveZFdToFdVZ(3,gt2,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFdVZ(3,gt1,:) 
AmpVertexZFdToFdVZ(3,gt2,:)= AmpVertexZFdToFdVZ(3,gt2,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFdVZ(3,gt1,:) 
AmpWaveZFdToFdVZ(4,gt2,:) = AmpWaveZFdToFdVZ(4,gt2,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFdVZ(4,gt1,:) 
AmpVertexZFdToFdVZ(4,gt2,:)= AmpVertexZFdToFdVZ(4,gt2,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFdVZ(4,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFdVZ=AmpWaveZFdToFdVZ 
AmpVertexFdToFdVZ= AmpVertexZFdToFdVZ
! Final State 1 
AmpWaveZFdToFdVZ=0._dp 
AmpVertexZFdToFdVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFdVZ(1,:,gt2) = AmpWaveZFdToFdVZ(1,:,gt2)+ZRUVd(gt2,gt1)*AmpWaveFdToFdVZ(1,:,gt1) 
AmpVertexZFdToFdVZ(1,:,gt2)= AmpVertexZFdToFdVZ(1,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexFdToFdVZ(1,:,gt1) 
AmpWaveZFdToFdVZ(2,:,gt2) = AmpWaveZFdToFdVZ(2,:,gt2)+ZRUUdc(gt2,gt1)*AmpWaveFdToFdVZ(2,:,gt1) 
AmpVertexZFdToFdVZ(2,:,gt2)= AmpVertexZFdToFdVZ(2,:,gt2)+ZRUUdc(gt2,gt1)*AmpVertexFdToFdVZ(2,:,gt1) 
AmpWaveZFdToFdVZ(3,:,gt2) = AmpWaveZFdToFdVZ(3,:,gt2)+ZRUVd(gt2,gt1)*AmpWaveFdToFdVZ(3,:,gt1) 
AmpVertexZFdToFdVZ(3,:,gt2)= AmpVertexZFdToFdVZ(3,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexFdToFdVZ(3,:,gt1) 
AmpWaveZFdToFdVZ(4,:,gt2) = AmpWaveZFdToFdVZ(4,:,gt2)+ZRUUdc(gt2,gt1)*AmpWaveFdToFdVZ(4,:,gt1) 
AmpVertexZFdToFdVZ(4,:,gt2)= AmpVertexZFdToFdVZ(4,:,gt2)+ZRUUdc(gt2,gt1)*AmpVertexFdToFdVZ(4,:,gt1) 
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
! Fu Hm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FdToFuHm(cplcFdFuHmL,cplcFdFuHmR,MFd,MFu,               & 
& MHm,MFd2,MFu2,MHm2,AmpTreeFdToFuHm)

  Else 
Call Amplitude_Tree_gumTHDMII_FdToFuHm(ZcplcFdFuHmL,ZcplcFdFuHmR,MFd,MFu,             & 
& MHm,MFd2,MFu2,MHm2,AmpTreeFdToFuHm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FdToFuHm(MLambda,em,gs,cplcFdFuHmL,cplcFdFuHmR,             & 
& MFdOS,MFuOS,MHmOS,MRPFdToFuHm,MRGFdToFuHm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFuHm(MLambda,em,gs,ZcplcFdFuHmL,ZcplcFdFuHmR,           & 
& MFdOS,MFuOS,MHmOS,MRPFdToFuHm,MRGFdToFuHm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FdToFuHm(MLambda,em,gs,cplcFdFuHmL,cplcFdFuHmR,             & 
& MFd,MFu,MHm,MRPFdToFuHm,MRGFdToFuHm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFuHm(MLambda,em,gs,ZcplcFdFuHmL,ZcplcFdFuHmR,           & 
& MFd,MFu,MHm,MRPFdToFuHm,MRGFdToFuHm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFuHm(cplcFdFuHmL,cplcFdFuHmR,ctcplcFdFuHmL,         & 
& ctcplcFdFuHmR,MFd,MFd2,MFu,MFu2,MHm,MHm2,ZfDL,ZfDR,ZfHm,ZfUL,ZfUR,AmpWaveFdToFuHm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFuHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,              & 
& cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexFdToFuHm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,              & 
& cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexIRdrFdToFuHm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuHm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhHmcVWm,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,ZcplcFdFuHmL,ZcplcFdFuHmR,             & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,      & 
& cplHmcVWmVZ,AmpVertexIRosFdToFuHm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,ZcplcFdFuHmL,ZcplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,              & 
& cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexIRosFdToFuHm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuHm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhHmcVWm,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,      & 
& cplHmcVWmVZ,AmpVertexIRosFdToFuHm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,              & 
& cplhhHmcVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,AmpVertexIRosFdToFuHm)

 End if 
 End if 
AmpVertexFdToFuHm = AmpVertexFdToFuHm -  AmpVertexIRdrFdToFuHm! +  AmpVertexIRosFdToFuHm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFuHm=0._dp 
AmpVertexZFdToFuHm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFuHm(1,gt2,:,:) = AmpWaveZFdToFuHm(1,gt2,:,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFuHm(1,gt1,:,:) 
AmpVertexZFdToFuHm(1,gt2,:,:)= AmpVertexZFdToFuHm(1,gt2,:,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFuHm(1,gt1,:,:) 
AmpWaveZFdToFuHm(2,gt2,:,:) = AmpWaveZFdToFuHm(2,gt2,:,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFuHm(2,gt1,:,:) 
AmpVertexZFdToFuHm(2,gt2,:,:)= AmpVertexZFdToFuHm(2,gt2,:,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFuHm(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFdToFuHm=AmpWaveZFdToFuHm 
AmpVertexFdToFuHm= AmpVertexZFdToFuHm
! Final State 1 
AmpWaveZFdToFuHm=0._dp 
AmpVertexZFdToFuHm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFuHm(1,:,gt2,:) = AmpWaveZFdToFuHm(1,:,gt2,:)+ZRUVu(gt2,gt1)*AmpWaveFdToFuHm(1,:,gt1,:) 
AmpVertexZFdToFuHm(1,:,gt2,:)= AmpVertexZFdToFuHm(1,:,gt2,:)+ZRUVu(gt2,gt1)*AmpVertexFdToFuHm(1,:,gt1,:) 
AmpWaveZFdToFuHm(2,:,gt2,:) = AmpWaveZFdToFuHm(2,:,gt2,:)+ZRUUuc(gt2,gt1)*AmpWaveFdToFuHm(2,:,gt1,:) 
AmpVertexZFdToFuHm(2,:,gt2,:)= AmpVertexZFdToFuHm(2,:,gt2,:)+ZRUUuc(gt2,gt1)*AmpVertexFdToFuHm(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFuHm=AmpWaveZFdToFuHm 
AmpVertexFdToFuHm= AmpVertexZFdToFuHm
! Final State 2 
AmpWaveZFdToFuHm=0._dp 
AmpVertexZFdToFuHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFdToFuHm(:,:,:,gt2) = AmpWaveZFdToFuHm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveFdToFuHm(:,:,:,gt1) 
AmpVertexZFdToFuHm(:,:,:,gt2)= AmpVertexZFdToFuHm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexFdToFuHm(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFuHm=AmpWaveZFdToFuHm 
AmpVertexFdToFuHm= AmpVertexZFdToFuHm
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFuHm = AmpVertexFdToFuHm  +  AmpVertexIRosFdToFuHm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fu Hm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFuHm = AmpTreeFdToFuHm 
 AmpSum2FdToFuHm = AmpTreeFdToFuHm + 2._dp*AmpWaveFdToFuHm + 2._dp*AmpVertexFdToFuHm  
Else 
 AmpSumFdToFuHm = AmpTreeFdToFuHm + AmpWaveFdToFuHm + AmpVertexFdToFuHm
 AmpSum2FdToFuHm = AmpTreeFdToFuHm + AmpWaveFdToFuHm + AmpVertexFdToFuHm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFuHm = AmpTreeFdToFuHm
 AmpSum2FdToFuHm = AmpTreeFdToFuHm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MHmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFu(gt2))+Abs(MHm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FdToFuHm = AmpTreeFdToFuHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHm(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFuHm(gt1, gt2, gt3) 
  AmpSum2FdToFuHm = 2._dp*AmpWaveFdToFuHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHm(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFuHm(gt1, gt2, gt3) 
  AmpSum2FdToFuHm = 2._dp*AmpVertexFdToFuHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHm(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFuHm(gt1, gt2, gt3) 
  AmpSum2FdToFuHm = AmpTreeFdToFuHm + 2._dp*AmpWaveFdToFuHm + 2._dp*AmpVertexFdToFuHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHm(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFuHm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFuHm = AmpTreeFdToFuHm
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
  AmpSqTreeFdToFuHm(gt1, gt2, gt3) = AmpSqFdToFuHm(gt1, gt2, gt3)  
  AmpSum2FdToFuHm = + 2._dp*AmpWaveFdToFuHm + 2._dp*AmpVertexFdToFuHm
  Call SquareAmp_FtoFS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
  AmpSqFdToFuHm(gt1, gt2, gt3) = AmpSqFdToFuHm(gt1, gt2, gt3) + AmpSqTreeFdToFuHm(gt1, gt2, gt3)  
Else  
  AmpSum2FdToFuHm = AmpTreeFdToFuHm
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHm(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
  AmpSqTreeFdToFuHm(gt1, gt2, gt3) = AmpSqFdToFuHm(gt1, gt2, gt3)  
  AmpSum2FdToFuHm = + 2._dp*AmpWaveFdToFuHm + 2._dp*AmpVertexFdToFuHm
  Call SquareAmp_FtoFS(MFd(gt1),MFu(gt2),MHm(gt3),AmpSumFdToFuHm(:,gt1, gt2, gt3),AmpSum2FdToFuHm(:,gt1, gt2, gt3),AmpSqFdToFuHm(gt1, gt2, gt3)) 
  AmpSqFdToFuHm(gt1, gt2, gt3) = AmpSqFdToFuHm(gt1, gt2, gt3) + AmpSqTreeFdToFuHm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFdToFuHm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFuHm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFuOS(gt2),MHmOS(gt3),helfactor*AmpSqFdToFuHm(gt1, gt2, gt3))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFu(gt2),MHm(gt3),helfactor*AmpSqFdToFuHm(gt1, gt2, gt3))
End if 
If ((Abs(MRPFdToFuHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFuHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFuHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFdToFuHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFuHm(gt1, gt2, gt3) + MRGFdToFuHm(gt1, gt2, gt3)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFuHm(gt1, gt2, gt3) + MRGFdToFuHm(gt1, gt2, gt3))
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
! Fu VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FdToFuVWm(cplcFdFuVWmL,cplcFdFuVWmR,MFd,MFu,            & 
& MVWm,MFd2,MFu2,MVWm2,AmpTreeFdToFuVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_FdToFuVWm(ZcplcFdFuVWmL,ZcplcFdFuVWmR,MFd,              & 
& MFu,MVWm,MFd2,MFu2,MVWm2,AmpTreeFdToFuVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FdToFuVWm(MLambda,em,gs,cplcFdFuVWmL,cplcFdFuVWmR,          & 
& MFdOS,MFuOS,MVWmOS,MRPFdToFuVWm,MRGFdToFuVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFuVWm(MLambda,em,gs,ZcplcFdFuVWmL,ZcplcFdFuVWmR,        & 
& MFdOS,MFuOS,MVWmOS,MRPFdToFuVWm,MRGFdToFuVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FdToFuVWm(MLambda,em,gs,cplcFdFuVWmL,cplcFdFuVWmR,          & 
& MFd,MFu,MVWm,MRPFdToFuVWm,MRGFdToFuVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FdToFuVWm(MLambda,em,gs,ZcplcFdFuVWmL,ZcplcFdFuVWmR,        & 
& MFd,MFu,MVWm,MRPFdToFuVWm,MRGFdToFuVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFuVWm(cplcFdFuVWmL,cplcFdFuVWmR,ctcplcFdFuVWmL,     & 
& ctcplcFdFuVWmR,MFd,MFd2,MFu,MFu2,MVWm,MVWm2,ZfDL,ZfDR,ZfUL,ZfUR,ZfVWm,AmpWaveFdToFuVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFuVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhcHmVWm,             & 
& cplhhcVWmVWm,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexFdToFuVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhcHmVWm,             & 
& cplhhcVWmVWm,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRdrFdToFuVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuVWm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhcHmVWm,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,GosZcplcFdFuHmL,GosZcplcFdFuHmR,cplcFuFuVGL,       & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplhhcHmVWm,cplhhcVWmVWm,GosZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,         & 
& cplcVWmVWmVZ,AmpVertexIRosFdToFuVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,GZcplcFdFuHmL,GZcplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,           & 
& cplcFuFuVPR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhcHmVWm,           & 
& cplhhcVWmVWm,GZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFdToFuVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuVWm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhcHmVWm,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFuFuhhL,cplcFuFuhhR,GcplcFdFuHmL,GcplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhcHmVWm,cplhhcVWmVWm,GcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,            & 
& cplcVWmVWmVZ,AmpVertexIRosFdToFuVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FdToFuVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhcHmVWm,             & 
& cplhhcVWmVWm,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFdToFuVWm)

 End if 
 End if 
AmpVertexFdToFuVWm = AmpVertexFdToFuVWm -  AmpVertexIRdrFdToFuVWm! +  AmpVertexIRosFdToFuVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFdToFuVWm=0._dp 
AmpVertexZFdToFuVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFuVWm(1,gt2,:) = AmpWaveZFdToFuVWm(1,gt2,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFuVWm(1,gt1,:) 
AmpVertexZFdToFuVWm(1,gt2,:)= AmpVertexZFdToFuVWm(1,gt2,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFuVWm(1,gt1,:) 
AmpWaveZFdToFuVWm(2,gt2,:) = AmpWaveZFdToFuVWm(2,gt2,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFuVWm(2,gt1,:) 
AmpVertexZFdToFuVWm(2,gt2,:)= AmpVertexZFdToFuVWm(2,gt2,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFuVWm(2,gt1,:) 
AmpWaveZFdToFuVWm(3,gt2,:) = AmpWaveZFdToFuVWm(3,gt2,:)+ZRUVdc(gt2,gt1)*AmpWaveFdToFuVWm(3,gt1,:) 
AmpVertexZFdToFuVWm(3,gt2,:)= AmpVertexZFdToFuVWm(3,gt2,:) + ZRUVdc(gt2,gt1)*AmpVertexFdToFuVWm(3,gt1,:) 
AmpWaveZFdToFuVWm(4,gt2,:) = AmpWaveZFdToFuVWm(4,gt2,:)+ZRUUd(gt2,gt1)*AmpWaveFdToFuVWm(4,gt1,:) 
AmpVertexZFdToFuVWm(4,gt2,:)= AmpVertexZFdToFuVWm(4,gt2,:) + ZRUUd(gt2,gt1)*AmpVertexFdToFuVWm(4,gt1,:) 
 End Do 
End Do 
AmpWaveFdToFuVWm=AmpWaveZFdToFuVWm 
AmpVertexFdToFuVWm= AmpVertexZFdToFuVWm
! Final State 1 
AmpWaveZFdToFuVWm=0._dp 
AmpVertexZFdToFuVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFdToFuVWm(1,:,gt2) = AmpWaveZFdToFuVWm(1,:,gt2)+ZRUVu(gt2,gt1)*AmpWaveFdToFuVWm(1,:,gt1) 
AmpVertexZFdToFuVWm(1,:,gt2)= AmpVertexZFdToFuVWm(1,:,gt2)+ZRUVu(gt2,gt1)*AmpVertexFdToFuVWm(1,:,gt1) 
AmpWaveZFdToFuVWm(2,:,gt2) = AmpWaveZFdToFuVWm(2,:,gt2)+ZRUUuc(gt2,gt1)*AmpWaveFdToFuVWm(2,:,gt1) 
AmpVertexZFdToFuVWm(2,:,gt2)= AmpVertexZFdToFuVWm(2,:,gt2)+ZRUUuc(gt2,gt1)*AmpVertexFdToFuVWm(2,:,gt1) 
AmpWaveZFdToFuVWm(3,:,gt2) = AmpWaveZFdToFuVWm(3,:,gt2)+ZRUVu(gt2,gt1)*AmpWaveFdToFuVWm(3,:,gt1) 
AmpVertexZFdToFuVWm(3,:,gt2)= AmpVertexZFdToFuVWm(3,:,gt2)+ZRUVu(gt2,gt1)*AmpVertexFdToFuVWm(3,:,gt1) 
AmpWaveZFdToFuVWm(4,:,gt2) = AmpWaveZFdToFuVWm(4,:,gt2)+ZRUUuc(gt2,gt1)*AmpWaveFdToFuVWm(4,:,gt1) 
AmpVertexZFdToFuVWm(4,:,gt2)= AmpVertexZFdToFuVWm(4,:,gt2)+ZRUUuc(gt2,gt1)*AmpVertexFdToFuVWm(4,:,gt1) 
 End Do 
End Do 
AmpWaveFdToFuVWm=AmpWaveZFdToFuVWm 
AmpVertexFdToFuVWm= AmpVertexZFdToFuVWm
End if
If (ShiftIRdiv) Then 
AmpVertexFdToFuVWm = AmpVertexFdToFuVWm  +  AmpVertexIRosFdToFuVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fd->Fu VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFdToFuVWm = AmpTreeFdToFuVWm 
 AmpSum2FdToFuVWm = AmpTreeFdToFuVWm + 2._dp*AmpWaveFdToFuVWm + 2._dp*AmpVertexFdToFuVWm  
Else 
 AmpSumFdToFuVWm = AmpTreeFdToFuVWm + AmpWaveFdToFuVWm + AmpVertexFdToFuVWm
 AmpSum2FdToFuVWm = AmpTreeFdToFuVWm + AmpWaveFdToFuVWm + AmpVertexFdToFuVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFdToFuVWm = AmpTreeFdToFuVWm
 AmpSum2FdToFuVWm = AmpTreeFdToFuVWm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFdOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MFd(gt1)).gt.(Abs(MFu(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FdToFuVWm = AmpTreeFdToFuVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWmOS,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWm,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFdToFuVWm(gt1, gt2) 
  AmpSum2FdToFuVWm = 2._dp*AmpWaveFdToFuVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWmOS,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWm,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFdToFuVWm(gt1, gt2) 
  AmpSum2FdToFuVWm = 2._dp*AmpVertexFdToFuVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWmOS,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWm,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFdToFuVWm(gt1, gt2) 
  AmpSum2FdToFuVWm = AmpTreeFdToFuVWm + 2._dp*AmpWaveFdToFuVWm + 2._dp*AmpVertexFdToFuVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWmOS,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWm,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFdToFuVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FdToFuVWm = AmpTreeFdToFuVWm
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWmOS,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
  AmpSqTreeFdToFuVWm(gt1, gt2) = AmpSqFdToFuVWm(gt1, gt2)  
  AmpSum2FdToFuVWm = + 2._dp*AmpWaveFdToFuVWm + 2._dp*AmpVertexFdToFuVWm
  Call SquareAmp_FtoFV(MFdOS(gt1),MFuOS(gt2),MVWmOS,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
  AmpSqFdToFuVWm(gt1, gt2) = AmpSqFdToFuVWm(gt1, gt2) + AmpSqTreeFdToFuVWm(gt1, gt2)  
Else  
  AmpSum2FdToFuVWm = AmpTreeFdToFuVWm
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWm,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
  AmpSqTreeFdToFuVWm(gt1, gt2) = AmpSqFdToFuVWm(gt1, gt2)  
  AmpSum2FdToFuVWm = + 2._dp*AmpWaveFdToFuVWm + 2._dp*AmpVertexFdToFuVWm
  Call SquareAmp_FtoFV(MFd(gt1),MFu(gt2),MVWm,AmpSumFdToFuVWm(:,gt1, gt2),AmpSum2FdToFuVWm(:,gt1, gt2),AmpSqFdToFuVWm(gt1, gt2)) 
  AmpSqFdToFuVWm(gt1, gt2) = AmpSqFdToFuVWm(gt1, gt2) + AmpSqTreeFdToFuVWm(gt1, gt2)  
End if  
Else  
  AmpSqFdToFuVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFdToFuVWm(gt1, gt2).eq.0._dp) Then 
  gP1LFd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFdOS(gt1),MFuOS(gt2),MVWmOS,helfactor*AmpSqFdToFuVWm(gt1, gt2))
Else 
  gP1LFd(gt1,i4) = 1._dp*GammaTPS(MFd(gt1),MFu(gt2),MVWm,helfactor*AmpSqFdToFuVWm(gt1, gt2))
End if 
If ((Abs(MRPFdToFuVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFuVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFdToFuVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFdToFuVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFdToFuVWm(gt1, gt2) + MRGFdToFuVWm(gt1, gt2)) 
  gP1LFd(gt1,i4) = gP1LFd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFdToFuVWm(gt1, gt2) + MRGFdToFuVWm(gt1, gt2))
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
! Fd VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_FdToFdVG(ZcplcFdFdVGL,ZcplcFdFdVGR,ctcplcFdFdVGL,       & 
& ctcplcFdFdVGR,MFdOS,MFd2OS,MVG,MVG2,ZfDL,ZfDR,ZfVG,AmpWaveFdToFdVG)

 Else 
Call Amplitude_WAVE_gumTHDMII_FdToFdVG(cplcFdFdVGL,cplcFdFdVGR,ctcplcFdFdVGL,         & 
& ctcplcFdFdVGR,MFdOS,MFd2OS,MVG,MVG2,ZfDL,ZfDR,ZfVG,AmpWaveFdToFdVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVG(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFdFdVGL,               & 
& ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFuFdcHmL,        & 
& ZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFdFuHmL,ZcplcFdFuHmR,ZcplcFuFuVGL,    & 
& ZcplcFuFuVGR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplVGVGVG,AmpVertexFdToFdVG)

 Else 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVG(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplVGVGVG,AmpVertexFdToFdVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFdVG(cplcFdFdVGL,cplcFdFdVGR,ctcplcFdFdVGL,         & 
& ctcplcFdFdVGR,MFd,MFd2,MVG,MVG2,ZfDL,ZfDR,ZfVG,AmpWaveFdToFdVG)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVG(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
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
Call Amplitude_WAVE_gumTHDMII_FdToFdVP(ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,        & 
& ZcplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFdOS,            & 
& MFd2OS,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,AmpWaveFdToFdVP)

 Else 
Call Amplitude_WAVE_gumTHDMII_FdToFdVP(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,           & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFdOS,             & 
& MFd2OS,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,AmpWaveFdToFdVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVP(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFdFdVGL,               & 
& ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,ZcplcFdFdVZR,ZcplcFuFdcHmL,        & 
& ZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFdFuHmL,ZcplcFdFuHmR,ZcplcFuFuVPL,    & 
& ZcplcFuFuVPR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplHmcHmVP,ZcplHmcVWmVP,ZcplcHmVPVWm,        & 
& ZcplcVWmVPVWm,AmpVertexFdToFdVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVP(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,        & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVPL,cplcFuFuVPR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,             & 
& AmpVertexFdToFdVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FdToFdVP(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,           & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFd,               & 
& MFd2,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,AmpWaveFdToFdVP)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FdToFdVP(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,AmpVertexFdToFdVP)

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

End Module Wrapper_OneLoopDecay_Fd_gumTHDMII
