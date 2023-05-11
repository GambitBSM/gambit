! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Fu_gumTHDMII
Use Model_Data_gumTHDMII 
Use Kinematics 
Use OneLoopDecay_Fu_gumTHDMII 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Fu(MhhOS,Mhh2OS,MAhOS,MAh2OS,MHmOS,MHm2OS,MFdOS,              & 
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
& ctcplcFuFdcHmL,ctcplcFuFdcHmR,ctcplcFuFdcVWmL,ctcplcFuFdcVWmR,ctcplcFuFuAhL,           & 
& ctcplcFuFuAhR,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,   & 
& ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,GcplcFuFdcHmL,GcplcFuFdcHmR,GcplcHmVPVWm,    & 
& GcplHmcVWmVP,GosZcplcFuFdcHmL,GosZcplcFuFdcHmR,GosZcplcHmVPVWm,GosZcplHmcVWmVP,        & 
& GZcplcFuFdcHmL,GZcplcFuFdcHmR,GZcplcHmVPVWm,GZcplHmcVWmVP,ZcplcFdFdVGL,ZcplcFdFdVGR,   & 
& ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFuHmL,ZcplcFdFuHmR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,       & 
& ZcplcFuFdcHmL,ZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFuFuAhL,ZcplcFuFuAhR,   & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,         & 
& ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcHmVPVWm,ZcplcVWmVPVWm,ZcplHmcHmVP,ZcplHmcVWmVP,         & 
& ZcplVGVGVG,ZRUZH,ZRUZA,ZRUZP,ZRUVd,ZRUUd,ZRUVu,ZRUUu,ZRUVe,ZRUUe,MLambda,              & 
& em,gs,deltaM,kont,gP1LFu)

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
& ctcplcFuFdcHmL(3,3,2),ctcplcFuFdcHmR(3,3,2),ctcplcFuFdcVWmL(3,3),ctcplcFuFdcVWmR(3,3), & 
& ctcplcFuFuAhL(3,3,2),ctcplcFuFuAhR(3,3,2),ctcplcFuFuhhL(3,3,2),ctcplcFuFuhhR(3,3,2),   & 
& ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),           & 
& ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3),GcplcFuFdcHmL(3,3,2),GcplcFuFdcHmR(3,3,2),       & 
& GcplcHmVPVWm(2),GcplHmcVWmVP(2),GosZcplcFuFdcHmL(3,3,2),GosZcplcFuFdcHmR(3,3,2),       & 
& GosZcplcHmVPVWm(2),GosZcplHmcVWmVP(2),GZcplcFuFdcHmL(3,3,2),GZcplcFuFdcHmR(3,3,2),     & 
& GZcplcHmVPVWm(2),GZcplHmcVWmVP(2),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),ZcplcFdFdVPL(3,3),& 
& ZcplcFdFdVPR(3,3),ZcplcFdFuHmL(3,3,2),ZcplcFdFuHmR(3,3,2),ZcplcFdFuVWmL(3,3),          & 
& ZcplcFdFuVWmR(3,3),ZcplcFuFdcHmL(3,3,2),ZcplcFuFdcHmR(3,3,2),ZcplcFuFdcVWmL(3,3),      & 
& ZcplcFuFdcVWmR(3,3),ZcplcFuFuAhL(3,3,2),ZcplcFuFuAhR(3,3,2),ZcplcFuFuhhL(3,3,2),       & 
& ZcplcFuFuhhR(3,3,2),ZcplcFuFuVGL(3,3),ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),             & 
& ZcplcFuFuVPR(3,3),ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcHmVPVWm(2),ZcplcVWmVPVWm,   & 
& ZcplHmcHmVP(2,2),ZcplHmcVWmVP(2),ZcplVGVGVG

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
Real(dp), Intent(out) :: gP1LFu(3,24) 
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
Real(dp) :: MRPFuToFuAh(3,3,2),MRGFuToFuAh(3,3,2), MRPZFuToFuAh(3,3,2),MRGZFuToFuAh(3,3,2) 
Real(dp) :: MVPFuToFuAh(3,3,2) 
Real(dp) :: RMsqTreeFuToFuAh(3,3,2),RMsqWaveFuToFuAh(3,3,2),RMsqVertexFuToFuAh(3,3,2) 
Complex(dp) :: AmpTreeFuToFuAh(2,3,3,2),AmpWaveFuToFuAh(2,3,3,2)=(0._dp,0._dp),AmpVertexFuToFuAh(2,3,3,2)& 
 & ,AmpVertexIRosFuToFuAh(2,3,3,2),AmpVertexIRdrFuToFuAh(2,3,3,2), AmpSumFuToFuAh(2,3,3,2), AmpSum2FuToFuAh(2,3,3,2) 
Complex(dp) :: AmpTreeZFuToFuAh(2,3,3,2),AmpWaveZFuToFuAh(2,3,3,2),AmpVertexZFuToFuAh(2,3,3,2) 
Real(dp) :: AmpSqFuToFuAh(3,3,2),  AmpSqTreeFuToFuAh(3,3,2) 
Real(dp) :: MRPFuToFdcHm(3,3,2),MRGFuToFdcHm(3,3,2), MRPZFuToFdcHm(3,3,2),MRGZFuToFdcHm(3,3,2) 
Real(dp) :: MVPFuToFdcHm(3,3,2) 
Real(dp) :: RMsqTreeFuToFdcHm(3,3,2),RMsqWaveFuToFdcHm(3,3,2),RMsqVertexFuToFdcHm(3,3,2) 
Complex(dp) :: AmpTreeFuToFdcHm(2,3,3,2),AmpWaveFuToFdcHm(2,3,3,2)=(0._dp,0._dp),AmpVertexFuToFdcHm(2,3,3,2)& 
 & ,AmpVertexIRosFuToFdcHm(2,3,3,2),AmpVertexIRdrFuToFdcHm(2,3,3,2), AmpSumFuToFdcHm(2,3,3,2), AmpSum2FuToFdcHm(2,3,3,2) 
Complex(dp) :: AmpTreeZFuToFdcHm(2,3,3,2),AmpWaveZFuToFdcHm(2,3,3,2),AmpVertexZFuToFdcHm(2,3,3,2) 
Real(dp) :: AmpSqFuToFdcHm(3,3,2),  AmpSqTreeFuToFdcHm(3,3,2) 
Real(dp) :: MRPFuToFdcVWm(3,3),MRGFuToFdcVWm(3,3), MRPZFuToFdcVWm(3,3),MRGZFuToFdcVWm(3,3) 
Real(dp) :: MVPFuToFdcVWm(3,3) 
Real(dp) :: RMsqTreeFuToFdcVWm(3,3),RMsqWaveFuToFdcVWm(3,3),RMsqVertexFuToFdcVWm(3,3) 
Complex(dp) :: AmpTreeFuToFdcVWm(4,3,3),AmpWaveFuToFdcVWm(4,3,3)=(0._dp,0._dp),AmpVertexFuToFdcVWm(4,3,3)& 
 & ,AmpVertexIRosFuToFdcVWm(4,3,3),AmpVertexIRdrFuToFdcVWm(4,3,3), AmpSumFuToFdcVWm(4,3,3), AmpSum2FuToFdcVWm(4,3,3) 
Complex(dp) :: AmpTreeZFuToFdcVWm(4,3,3),AmpWaveZFuToFdcVWm(4,3,3),AmpVertexZFuToFdcVWm(4,3,3) 
Real(dp) :: AmpSqFuToFdcVWm(3,3),  AmpSqTreeFuToFdcVWm(3,3) 
Real(dp) :: MRPFuToFuhh(3,3,2),MRGFuToFuhh(3,3,2), MRPZFuToFuhh(3,3,2),MRGZFuToFuhh(3,3,2) 
Real(dp) :: MVPFuToFuhh(3,3,2) 
Real(dp) :: RMsqTreeFuToFuhh(3,3,2),RMsqWaveFuToFuhh(3,3,2),RMsqVertexFuToFuhh(3,3,2) 
Complex(dp) :: AmpTreeFuToFuhh(2,3,3,2),AmpWaveFuToFuhh(2,3,3,2)=(0._dp,0._dp),AmpVertexFuToFuhh(2,3,3,2)& 
 & ,AmpVertexIRosFuToFuhh(2,3,3,2),AmpVertexIRdrFuToFuhh(2,3,3,2), AmpSumFuToFuhh(2,3,3,2), AmpSum2FuToFuhh(2,3,3,2) 
Complex(dp) :: AmpTreeZFuToFuhh(2,3,3,2),AmpWaveZFuToFuhh(2,3,3,2),AmpVertexZFuToFuhh(2,3,3,2) 
Real(dp) :: AmpSqFuToFuhh(3,3,2),  AmpSqTreeFuToFuhh(3,3,2) 
Real(dp) :: MRPFuToFuVZ(3,3),MRGFuToFuVZ(3,3), MRPZFuToFuVZ(3,3),MRGZFuToFuVZ(3,3) 
Real(dp) :: MVPFuToFuVZ(3,3) 
Real(dp) :: RMsqTreeFuToFuVZ(3,3),RMsqWaveFuToFuVZ(3,3),RMsqVertexFuToFuVZ(3,3) 
Complex(dp) :: AmpTreeFuToFuVZ(4,3,3),AmpWaveFuToFuVZ(4,3,3)=(0._dp,0._dp),AmpVertexFuToFuVZ(4,3,3)& 
 & ,AmpVertexIRosFuToFuVZ(4,3,3),AmpVertexIRdrFuToFuVZ(4,3,3), AmpSumFuToFuVZ(4,3,3), AmpSum2FuToFuVZ(4,3,3) 
Complex(dp) :: AmpTreeZFuToFuVZ(4,3,3),AmpWaveZFuToFuVZ(4,3,3),AmpVertexZFuToFuVZ(4,3,3) 
Real(dp) :: AmpSqFuToFuVZ(3,3),  AmpSqTreeFuToFuVZ(3,3) 
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
! Fu Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FuToFuAh(cplcFuFuAhL,cplcFuFuAhR,MAh,MFu,               & 
& MAh2,MFu2,AmpTreeFuToFuAh)

  Else 
Call Amplitude_Tree_gumTHDMII_FuToFuAh(ZcplcFuFuAhL,ZcplcFuFuAhR,MAh,MFu,             & 
& MAh2,MFu2,AmpTreeFuToFuAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuAh(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,             & 
& MAhOS,MFuOS,MRPFuToFuAh,MRGFuToFuAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuAh(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,           & 
& MAhOS,MFuOS,MRPFuToFuAh,MRGFuToFuAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FuToFuAh(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,             & 
& MAh,MFu,MRPFuToFuAh,MRGFuToFuAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuAh(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,           & 
& MAh,MFu,MRPFuToFuAh,MRGFuToFuAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFuAh(cplcFuFuAhL,cplcFuFuAhR,ctcplcFuFuAhL,         & 
& ctcplcFuFuAhR,MAh,MAh2,MFu,MFu2,ZfAh,ZfUL,ZfUR,AmpWaveFuToFuAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFuAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,        & 
& cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,AmpVertexFuToFuAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& AmpVertexIRdrFuToFuAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,          & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,      & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,AmpVertexIRosFuToFuAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,      & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& AmpVertexIRosFuToFuAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,      & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,AmpVertexIRosFuToFuAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& AmpVertexIRosFuToFuAh)

 End if 
 End if 
AmpVertexFuToFuAh = AmpVertexFuToFuAh -  AmpVertexIRdrFuToFuAh! +  AmpVertexIRosFuToFuAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFuAh=0._dp 
AmpVertexZFuToFuAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuAh(1,gt2,:,:) = AmpWaveZFuToFuAh(1,gt2,:,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFuAh(1,gt1,:,:) 
AmpVertexZFuToFuAh(1,gt2,:,:)= AmpVertexZFuToFuAh(1,gt2,:,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFuAh(1,gt1,:,:) 
AmpWaveZFuToFuAh(2,gt2,:,:) = AmpWaveZFuToFuAh(2,gt2,:,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFuAh(2,gt1,:,:) 
AmpVertexZFuToFuAh(2,gt2,:,:)= AmpVertexZFuToFuAh(2,gt2,:,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFuAh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFuAh=AmpWaveZFuToFuAh 
AmpVertexFuToFuAh= AmpVertexZFuToFuAh
! Final State 1 
AmpWaveZFuToFuAh=0._dp 
AmpVertexZFuToFuAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuAh(1,:,gt2,:) = AmpWaveZFuToFuAh(1,:,gt2,:)+ZRUVu(gt2,gt1)*AmpWaveFuToFuAh(1,:,gt1,:) 
AmpVertexZFuToFuAh(1,:,gt2,:)= AmpVertexZFuToFuAh(1,:,gt2,:)+ZRUVu(gt2,gt1)*AmpVertexFuToFuAh(1,:,gt1,:) 
AmpWaveZFuToFuAh(2,:,gt2,:) = AmpWaveZFuToFuAh(2,:,gt2,:)+ZRUUuc(gt2,gt1)*AmpWaveFuToFuAh(2,:,gt1,:) 
AmpVertexZFuToFuAh(2,:,gt2,:)= AmpVertexZFuToFuAh(2,:,gt2,:)+ZRUUuc(gt2,gt1)*AmpVertexFuToFuAh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuAh=AmpWaveZFuToFuAh 
AmpVertexFuToFuAh= AmpVertexZFuToFuAh
! Final State 2 
AmpWaveZFuToFuAh=0._dp 
AmpVertexZFuToFuAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFuToFuAh(:,:,:,gt2) = AmpWaveZFuToFuAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveFuToFuAh(:,:,:,gt1) 
AmpVertexZFuToFuAh(:,:,:,gt2)= AmpVertexZFuToFuAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexFuToFuAh(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFuAh=AmpWaveZFuToFuAh 
AmpVertexFuToFuAh= AmpVertexZFuToFuAh
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFuAh = AmpVertexFuToFuAh  +  AmpVertexIRosFuToFuAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fu Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFuAh = AmpTreeFuToFuAh 
 AmpSum2FuToFuAh = AmpTreeFuToFuAh + 2._dp*AmpWaveFuToFuAh + 2._dp*AmpVertexFuToFuAh  
Else 
 AmpSumFuToFuAh = AmpTreeFuToFuAh + AmpWaveFuToFuAh + AmpVertexFuToFuAh
 AmpSum2FuToFuAh = AmpTreeFuToFuAh + AmpWaveFuToFuAh + AmpVertexFuToFuAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFuAh = AmpTreeFuToFuAh
 AmpSum2FuToFuAh = AmpTreeFuToFuAh 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuToFuAh = AmpTreeFuToFuAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MAh(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFuAh(gt1, gt2, gt3) 
  AmpSum2FuToFuAh = 2._dp*AmpWaveFuToFuAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MAh(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFuAh(gt1, gt2, gt3) 
  AmpSum2FuToFuAh = 2._dp*AmpVertexFuToFuAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MAh(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFuAh(gt1, gt2, gt3) 
  AmpSum2FuToFuAh = AmpTreeFuToFuAh + 2._dp*AmpWaveFuToFuAh + 2._dp*AmpVertexFuToFuAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MAh(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFuAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFuAh = AmpTreeFuToFuAh
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
  AmpSqTreeFuToFuAh(gt1, gt2, gt3) = AmpSqFuToFuAh(gt1, gt2, gt3)  
  AmpSum2FuToFuAh = + 2._dp*AmpWaveFuToFuAh + 2._dp*AmpVertexFuToFuAh
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
  AmpSqFuToFuAh(gt1, gt2, gt3) = AmpSqFuToFuAh(gt1, gt2, gt3) + AmpSqTreeFuToFuAh(gt1, gt2, gt3)  
Else  
  AmpSum2FuToFuAh = AmpTreeFuToFuAh
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MAh(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
  AmpSqTreeFuToFuAh(gt1, gt2, gt3) = AmpSqFuToFuAh(gt1, gt2, gt3)  
  AmpSum2FuToFuAh = + 2._dp*AmpWaveFuToFuAh + 2._dp*AmpVertexFuToFuAh
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),MAh(gt3),AmpSumFuToFuAh(:,gt1, gt2, gt3),AmpSum2FuToFuAh(:,gt1, gt2, gt3),AmpSqFuToFuAh(gt1, gt2, gt3)) 
  AmpSqFuToFuAh(gt1, gt2, gt3) = AmpSqFuToFuAh(gt1, gt2, gt3) + AmpSqTreeFuToFuAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuToFuAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),MAhOS(gt3),helfactor*AmpSqFuToFuAh(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),MAh(gt3),helfactor*AmpSqFuToFuAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuToFuAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFuAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFuAh(gt1, gt2, gt3) + MRGFuToFuAh(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFuAh(gt1, gt2, gt3) + MRGFuToFuAh(gt1, gt2, gt3))
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
! Fd Conjg(Hm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FuToFdcHm(cplcFuFdcHmL,cplcFuFdcHmR,MFd,MFu,            & 
& MHm,MFd2,MFu2,MHm2,AmpTreeFuToFdcHm)

  Else 
Call Amplitude_Tree_gumTHDMII_FuToFdcHm(ZcplcFuFdcHmL,ZcplcFuFdcHmR,MFd,              & 
& MFu,MHm,MFd2,MFu2,MHm2,AmpTreeFuToFdcHm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FuToFdcHm(MLambda,em,gs,cplcFuFdcHmL,cplcFuFdcHmR,          & 
& MFdOS,MFuOS,MHmOS,MRPFuToFdcHm,MRGFuToFdcHm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFdcHm(MLambda,em,gs,ZcplcFuFdcHmL,ZcplcFuFdcHmR,        & 
& MFdOS,MFuOS,MHmOS,MRPFuToFdcHm,MRGFuToFdcHm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FuToFdcHm(MLambda,em,gs,cplcFuFdcHmL,cplcFuFdcHmR,          & 
& MFd,MFu,MHm,MRPFuToFdcHm,MRGFuToFdcHm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFdcHm(MLambda,em,gs,ZcplcFuFdcHmL,ZcplcFuFdcHmR,        & 
& MFd,MFu,MHm,MRPFuToFdcHm,MRGFuToFdcHm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFdcHm(cplcFuFdcHmL,cplcFuFdcHmR,ctcplcFuFdcHmL,     & 
& ctcplcFuFdcHmR,MFd,MFd2,MFu,MFu2,MHm,MHm2,ZfDL,ZfDR,ZfHm,ZfUL,ZfUR,AmpWaveFuToFdcHm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFdcHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexFuToFdcHm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRdrFuToFdcHm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,ZcplcFuFdcHmL,ZcplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,AmpVertexIRosFuToFdcHm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,ZcplcFuFdcHmL,             & 
& ZcplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRosFuToFdcHm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,AmpVertexIRosFuToFdcHm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRosFuToFdcHm)

 End if 
 End if 
AmpVertexFuToFdcHm = AmpVertexFuToFdcHm -  AmpVertexIRdrFuToFdcHm! +  AmpVertexIRosFuToFdcHm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFdcHm=0._dp 
AmpVertexZFuToFdcHm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcHm(1,gt2,:,:) = AmpWaveZFuToFdcHm(1,gt2,:,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFdcHm(1,gt1,:,:) 
AmpVertexZFuToFdcHm(1,gt2,:,:)= AmpVertexZFuToFdcHm(1,gt2,:,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFdcHm(1,gt1,:,:) 
AmpWaveZFuToFdcHm(2,gt2,:,:) = AmpWaveZFuToFdcHm(2,gt2,:,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFdcHm(2,gt1,:,:) 
AmpVertexZFuToFdcHm(2,gt2,:,:)= AmpVertexZFuToFdcHm(2,gt2,:,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFdcHm(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFdcHm=AmpWaveZFuToFdcHm 
AmpVertexFuToFdcHm= AmpVertexZFuToFdcHm
! Final State 1 
AmpWaveZFuToFdcHm=0._dp 
AmpVertexZFuToFdcHm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcHm(1,:,gt2,:) = AmpWaveZFuToFdcHm(1,:,gt2,:)+ZRUVd(gt2,gt1)*AmpWaveFuToFdcHm(1,:,gt1,:) 
AmpVertexZFuToFdcHm(1,:,gt2,:)= AmpVertexZFuToFdcHm(1,:,gt2,:)+ZRUVd(gt2,gt1)*AmpVertexFuToFdcHm(1,:,gt1,:) 
AmpWaveZFuToFdcHm(2,:,gt2,:) = AmpWaveZFuToFdcHm(2,:,gt2,:)+ZRUUdc(gt2,gt1)*AmpWaveFuToFdcHm(2,:,gt1,:) 
AmpVertexZFuToFdcHm(2,:,gt2,:)= AmpVertexZFuToFdcHm(2,:,gt2,:)+ZRUUdc(gt2,gt1)*AmpVertexFuToFdcHm(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFdcHm=AmpWaveZFuToFdcHm 
AmpVertexFuToFdcHm= AmpVertexZFuToFdcHm
! Final State 2 
AmpWaveZFuToFdcHm=0._dp 
AmpVertexZFuToFdcHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFuToFdcHm(:,:,:,gt2) = AmpWaveZFuToFdcHm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveFuToFdcHm(:,:,:,gt1) 
AmpVertexZFuToFdcHm(:,:,:,gt2)= AmpVertexZFuToFdcHm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexFuToFdcHm(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFdcHm=AmpWaveZFuToFdcHm 
AmpVertexFuToFdcHm= AmpVertexZFuToFdcHm
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFdcHm = AmpVertexFuToFdcHm  +  AmpVertexIRosFuToFdcHm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fd conj[Hm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFdcHm = AmpTreeFuToFdcHm 
 AmpSum2FuToFdcHm = AmpTreeFuToFdcHm + 2._dp*AmpWaveFuToFdcHm + 2._dp*AmpVertexFuToFdcHm  
Else 
 AmpSumFuToFdcHm = AmpTreeFuToFdcHm + AmpWaveFuToFdcHm + AmpVertexFuToFdcHm
 AmpSum2FuToFdcHm = AmpTreeFuToFdcHm + AmpWaveFuToFdcHm + AmpVertexFuToFdcHm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFdcHm = AmpTreeFuToFdcHm
 AmpSum2FuToFdcHm = AmpTreeFuToFdcHm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MHmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFd(gt2))+Abs(MHm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuToFdcHm = AmpTreeFuToFdcHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHm(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFdcHm(gt1, gt2, gt3) 
  AmpSum2FuToFdcHm = 2._dp*AmpWaveFuToFdcHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHm(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFdcHm(gt1, gt2, gt3) 
  AmpSum2FuToFdcHm = 2._dp*AmpVertexFuToFdcHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHm(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFdcHm(gt1, gt2, gt3) 
  AmpSum2FuToFdcHm = AmpTreeFuToFdcHm + 2._dp*AmpWaveFuToFdcHm + 2._dp*AmpVertexFuToFdcHm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHm(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFdcHm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFdcHm = AmpTreeFuToFdcHm
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
  AmpSqTreeFuToFdcHm(gt1, gt2, gt3) = AmpSqFuToFdcHm(gt1, gt2, gt3)  
  AmpSum2FuToFdcHm = + 2._dp*AmpWaveFuToFdcHm + 2._dp*AmpVertexFuToFdcHm
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
  AmpSqFuToFdcHm(gt1, gt2, gt3) = AmpSqFuToFdcHm(gt1, gt2, gt3) + AmpSqTreeFuToFdcHm(gt1, gt2, gt3)  
Else  
  AmpSum2FuToFdcHm = AmpTreeFuToFdcHm
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHm(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
  AmpSqTreeFuToFdcHm(gt1, gt2, gt3) = AmpSqFuToFdcHm(gt1, gt2, gt3)  
  AmpSum2FuToFdcHm = + 2._dp*AmpWaveFuToFdcHm + 2._dp*AmpVertexFuToFdcHm
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHm(gt3),AmpSumFuToFdcHm(:,gt1, gt2, gt3),AmpSum2FuToFdcHm(:,gt1, gt2, gt3),AmpSqFuToFdcHm(gt1, gt2, gt3)) 
  AmpSqFuToFdcHm(gt1, gt2, gt3) = AmpSqFuToFdcHm(gt1, gt2, gt3) + AmpSqTreeFuToFdcHm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuToFdcHm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFdcHm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFdOS(gt2),MHmOS(gt3),helfactor*AmpSqFuToFdcHm(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFd(gt2),MHm(gt3),helfactor*AmpSqFuToFdcHm(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuToFdcHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdcHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFdcHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdcHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFdcHm(gt1, gt2, gt3) + MRGFuToFdcHm(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFdcHm(gt1, gt2, gt3) + MRGFuToFdcHm(gt1, gt2, gt3))
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
! Fd Conjg(VWm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FuToFdcVWm(cplcFuFdcVWmL,cplcFuFdcVWmR,MFd,             & 
& MFu,MVWm,MFd2,MFu2,MVWm2,AmpTreeFuToFdcVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_FuToFdcVWm(ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,               & 
& MFd,MFu,MVWm,MFd2,MFu2,MVWm2,AmpTreeFuToFdcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FuToFdcVWm(MLambda,em,gs,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& MFdOS,MFuOS,MVWmOS,MRPFuToFdcVWm,MRGFuToFdcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFdcVWm(MLambda,em,gs,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,     & 
& MFdOS,MFuOS,MVWmOS,MRPFuToFdcVWm,MRGFuToFdcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FuToFdcVWm(MLambda,em,gs,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& MFd,MFu,MVWm,MRPFuToFdcVWm,MRGFuToFdcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFdcVWm(MLambda,em,gs,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,     & 
& MFd,MFu,MVWm,MRPFuToFdcVWm,MRGFuToFdcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFdcVWm(cplcFuFdcVWmL,cplcFuFdcVWmR,ctcplcFuFdcVWmL, & 
& ctcplcFuFdcVWmR,MFd,MFd2,MFu,MFu2,MVWm,MVWm2,ZfDL,ZfDR,ZfUL,ZfUR,ZfVWm,AmpWaveFuToFdcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFdcVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,               & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcVWm,               & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexFuToFdcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcVWm,               & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRdrFuToFdcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,          & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,GosZcplcFuFdcHmL,GosZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcVWm,cplhhcVWmVWm,GosZcplHmcVWmVP,cplHmcVWmVZ,          & 
& cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,GZcplcFuFdcHmL,            & 
& GZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,      & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcVWm,               & 
& cplhhcVWmVWm,GZcplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,          & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,GcplcFuFdcHmL,GcplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplhhHmcVWm,cplhhcVWmVWm,GcplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcVWm,               & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

 End if 
 End if 
AmpVertexFuToFdcVWm = AmpVertexFuToFdcVWm -  AmpVertexIRdrFuToFdcVWm! +  AmpVertexIRosFuToFdcVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFdcVWm=0._dp 
AmpVertexZFuToFdcVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcVWm(1,gt2,:) = AmpWaveZFuToFdcVWm(1,gt2,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFdcVWm(1,gt1,:) 
AmpVertexZFuToFdcVWm(1,gt2,:)= AmpVertexZFuToFdcVWm(1,gt2,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFdcVWm(1,gt1,:) 
AmpWaveZFuToFdcVWm(2,gt2,:) = AmpWaveZFuToFdcVWm(2,gt2,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFdcVWm(2,gt1,:) 
AmpVertexZFuToFdcVWm(2,gt2,:)= AmpVertexZFuToFdcVWm(2,gt2,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFdcVWm(2,gt1,:) 
AmpWaveZFuToFdcVWm(3,gt2,:) = AmpWaveZFuToFdcVWm(3,gt2,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFdcVWm(3,gt1,:) 
AmpVertexZFuToFdcVWm(3,gt2,:)= AmpVertexZFuToFdcVWm(3,gt2,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFdcVWm(3,gt1,:) 
AmpWaveZFuToFdcVWm(4,gt2,:) = AmpWaveZFuToFdcVWm(4,gt2,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFdcVWm(4,gt1,:) 
AmpVertexZFuToFdcVWm(4,gt2,:)= AmpVertexZFuToFdcVWm(4,gt2,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFdcVWm(4,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFdcVWm=AmpWaveZFuToFdcVWm 
AmpVertexFuToFdcVWm= AmpVertexZFuToFdcVWm
! Final State 1 
AmpWaveZFuToFdcVWm=0._dp 
AmpVertexZFuToFdcVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcVWm(1,:,gt2) = AmpWaveZFuToFdcVWm(1,:,gt2)+ZRUVd(gt2,gt1)*AmpWaveFuToFdcVWm(1,:,gt1) 
AmpVertexZFuToFdcVWm(1,:,gt2)= AmpVertexZFuToFdcVWm(1,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexFuToFdcVWm(1,:,gt1) 
AmpWaveZFuToFdcVWm(2,:,gt2) = AmpWaveZFuToFdcVWm(2,:,gt2)+ZRUUdc(gt2,gt1)*AmpWaveFuToFdcVWm(2,:,gt1) 
AmpVertexZFuToFdcVWm(2,:,gt2)= AmpVertexZFuToFdcVWm(2,:,gt2)+ZRUUdc(gt2,gt1)*AmpVertexFuToFdcVWm(2,:,gt1) 
AmpWaveZFuToFdcVWm(3,:,gt2) = AmpWaveZFuToFdcVWm(3,:,gt2)+ZRUVd(gt2,gt1)*AmpWaveFuToFdcVWm(3,:,gt1) 
AmpVertexZFuToFdcVWm(3,:,gt2)= AmpVertexZFuToFdcVWm(3,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexFuToFdcVWm(3,:,gt1) 
AmpWaveZFuToFdcVWm(4,:,gt2) = AmpWaveZFuToFdcVWm(4,:,gt2)+ZRUUdc(gt2,gt1)*AmpWaveFuToFdcVWm(4,:,gt1) 
AmpVertexZFuToFdcVWm(4,:,gt2)= AmpVertexZFuToFdcVWm(4,:,gt2)+ZRUUdc(gt2,gt1)*AmpVertexFuToFdcVWm(4,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFdcVWm=AmpWaveZFuToFdcVWm 
AmpVertexFuToFdcVWm= AmpVertexZFuToFdcVWm
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFdcVWm = AmpVertexFuToFdcVWm  +  AmpVertexIRosFuToFdcVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fd conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFdcVWm = AmpTreeFuToFdcVWm 
 AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm + 2._dp*AmpWaveFuToFdcVWm + 2._dp*AmpVertexFuToFdcVWm  
Else 
 AmpSumFuToFdcVWm = AmpTreeFuToFdcVWm + AmpWaveFuToFdcVWm + AmpVertexFuToFdcVWm
 AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm + AmpWaveFuToFdcVWm + AmpVertexFuToFdcVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFdcVWm = AmpTreeFuToFdcVWm
 AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFd(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWmOS,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWm,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFdcVWm(gt1, gt2) 
  AmpSum2FuToFdcVWm = 2._dp*AmpWaveFuToFdcVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWmOS,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWm,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFdcVWm(gt1, gt2) 
  AmpSum2FuToFdcVWm = 2._dp*AmpVertexFuToFdcVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWmOS,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWm,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFdcVWm(gt1, gt2) 
  AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm + 2._dp*AmpWaveFuToFdcVWm + 2._dp*AmpVertexFuToFdcVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWmOS,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWm,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFdcVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWmOS,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
  AmpSqTreeFuToFdcVWm(gt1, gt2) = AmpSqFuToFdcVWm(gt1, gt2)  
  AmpSum2FuToFdcVWm = + 2._dp*AmpWaveFuToFdcVWm + 2._dp*AmpVertexFuToFdcVWm
  Call SquareAmp_FtoFV(MFuOS(gt1),MFdOS(gt2),MVWmOS,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
  AmpSqFuToFdcVWm(gt1, gt2) = AmpSqFuToFdcVWm(gt1, gt2) + AmpSqTreeFuToFdcVWm(gt1, gt2)  
Else  
  AmpSum2FuToFdcVWm = AmpTreeFuToFdcVWm
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWm,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
  AmpSqTreeFuToFdcVWm(gt1, gt2) = AmpSqFuToFdcVWm(gt1, gt2)  
  AmpSum2FuToFdcVWm = + 2._dp*AmpWaveFuToFdcVWm + 2._dp*AmpVertexFuToFdcVWm
  Call SquareAmp_FtoFV(MFu(gt1),MFd(gt2),MVWm,AmpSumFuToFdcVWm(:,gt1, gt2),AmpSum2FuToFdcVWm(:,gt1, gt2),AmpSqFuToFdcVWm(gt1, gt2)) 
  AmpSqFuToFdcVWm(gt1, gt2) = AmpSqFuToFdcVWm(gt1, gt2) + AmpSqTreeFuToFdcVWm(gt1, gt2)  
End if  
Else  
  AmpSqFuToFdcVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFdcVWm(gt1, gt2).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFdOS(gt2),MVWmOS,helfactor*AmpSqFuToFdcVWm(gt1, gt2))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFd(gt2),MVWm,helfactor*AmpSqFuToFdcVWm(gt1, gt2))
End if 
If ((Abs(MRPFuToFdcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFdcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFdcVWm(gt1, gt2) + MRGFuToFdcVWm(gt1, gt2)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFdcVWm(gt1, gt2) + MRGFuToFdcVWm(gt1, gt2))
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
Call Amplitude_Tree_gumTHDMII_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,MFu,Mhh,               & 
& MFu2,Mhh2,AmpTreeFuToFuhh)

  Else 
Call Amplitude_Tree_gumTHDMII_FuToFuhh(ZcplcFuFuhhL,ZcplcFuFuhhR,MFu,Mhh,             & 
& MFu2,Mhh2,AmpTreeFuToFuhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,             & 
& MFuOS,MhhOS,MRPFuToFuhh,MRGFuToFuhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuhh(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,           & 
& MFuOS,MhhOS,MRPFuToFuhh,MRGFuToFuhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,             & 
& MFu,Mhh,MRPFuToFuhh,MRGFuToFuhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuhh(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,           & 
& MFu,Mhh,MRPFuToFuhh,MRGFuToFuhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,         & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,Zfhh,ZfUL,ZfUR,AmpWaveFuToFuhh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFuhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,               & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexFuToFuhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexIRdrFuToFuhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,ZcplcFuFuhhL,        & 
& ZcplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFuToFuhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexIRosFuToFuhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosFuToFuhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
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
AmpWaveZFuToFuhh(1,gt2,:,:) = AmpWaveZFuToFuhh(1,gt2,:,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFuhh(1,gt1,:,:) 
AmpVertexZFuToFuhh(1,gt2,:,:)= AmpVertexZFuToFuhh(1,gt2,:,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFuhh(1,gt1,:,:) 
AmpWaveZFuToFuhh(2,gt2,:,:) = AmpWaveZFuToFuhh(2,gt2,:,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFuhh(2,gt1,:,:) 
AmpVertexZFuToFuhh(2,gt2,:,:)= AmpVertexZFuToFuhh(2,gt2,:,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFuhh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFuhh=AmpWaveZFuToFuhh 
AmpVertexFuToFuhh= AmpVertexZFuToFuhh
! Final State 1 
AmpWaveZFuToFuhh=0._dp 
AmpVertexZFuToFuhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuhh(1,:,gt2,:) = AmpWaveZFuToFuhh(1,:,gt2,:)+ZRUVu(gt2,gt1)*AmpWaveFuToFuhh(1,:,gt1,:) 
AmpVertexZFuToFuhh(1,:,gt2,:)= AmpVertexZFuToFuhh(1,:,gt2,:)+ZRUVu(gt2,gt1)*AmpVertexFuToFuhh(1,:,gt1,:) 
AmpWaveZFuToFuhh(2,:,gt2,:) = AmpWaveZFuToFuhh(2,:,gt2,:)+ZRUUuc(gt2,gt1)*AmpWaveFuToFuhh(2,:,gt1,:) 
AmpVertexZFuToFuhh(2,:,gt2,:)= AmpVertexZFuToFuhh(2,:,gt2,:)+ZRUUuc(gt2,gt1)*AmpVertexFuToFuhh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuhh=AmpWaveZFuToFuhh 
AmpVertexFuToFuhh= AmpVertexZFuToFuhh
! Final State 2 
AmpWaveZFuToFuhh=0._dp 
AmpVertexZFuToFuhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFuToFuhh(:,:,:,gt2) = AmpWaveZFuToFuhh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveFuToFuhh(:,:,:,gt1) 
AmpVertexZFuToFuhh(:,:,:,gt2)= AmpVertexZFuToFuhh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexFuToFuhh(:,:,:,gt1) 
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
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFu(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuToFuhh = AmpTreeFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFuhh(gt1, gt2, gt3) 
  AmpSum2FuToFuhh = 2._dp*AmpWaveFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFuhh(gt1, gt2, gt3) 
  AmpSum2FuToFuhh = 2._dp*AmpVertexFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFuhh(gt1, gt2, gt3) 
  AmpSum2FuToFuhh = AmpTreeFuToFuhh + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFuhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFuhh = AmpTreeFuToFuhh
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
  AmpSqTreeFuToFuhh(gt1, gt2, gt3) = AmpSqFuToFuhh(gt1, gt2, gt3)  
  AmpSum2FuToFuhh = + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh
  Call SquareAmp_FtoFS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
  AmpSqFuToFuhh(gt1, gt2, gt3) = AmpSqFuToFuhh(gt1, gt2, gt3) + AmpSqTreeFuToFuhh(gt1, gt2, gt3)  
Else  
  AmpSum2FuToFuhh = AmpTreeFuToFuhh
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
  AmpSqTreeFuToFuhh(gt1, gt2, gt3) = AmpSqFuToFuhh(gt1, gt2, gt3)  
  AmpSum2FuToFuhh = + 2._dp*AmpWaveFuToFuhh + 2._dp*AmpVertexFuToFuhh
  Call SquareAmp_FtoFS(MFu(gt1),MFu(gt2),Mhh(gt3),AmpSumFuToFuhh(:,gt1, gt2, gt3),AmpSum2FuToFuhh(:,gt1, gt2, gt3),AmpSqFuToFuhh(gt1, gt2, gt3)) 
  AmpSqFuToFuhh(gt1, gt2, gt3) = AmpSqFuToFuhh(gt1, gt2, gt3) + AmpSqTreeFuToFuhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuToFuhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFuhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFuOS(gt2),MhhOS(gt3),helfactor*AmpSqFuToFuhh(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFu(gt2),Mhh(gt3),helfactor*AmpSqFuToFuhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuToFuhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFuhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFuhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFuhh(gt1, gt2, gt3) + MRGFuToFuhh(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFuhh(gt1, gt2, gt3) + MRGFuToFuhh(gt1, gt2, gt3))
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
! Fu VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_FuToFuVZ(cplcFuFuVZL,cplcFuFuVZR,MFu,MVZ,               & 
& MFu2,MVZ2,AmpTreeFuToFuVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_FuToFuVZ(ZcplcFuFuVZL,ZcplcFuFuVZR,MFu,MVZ,             & 
& MFu2,MVZ2,AmpTreeFuToFuVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,             & 
& MFuOS,MVZOS,MRPFuToFuVZ,MRGFuToFuVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuVZ(MLambda,em,gs,ZcplcFuFuVZL,ZcplcFuFuVZR,           & 
& MFuOS,MVZOS,MRPFuToFuVZ,MRGFuToFuVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,             & 
& MFu,MVZ,MRPFuToFuVZ,MRGFuToFuVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_FuToFuVZ(MLambda,em,gs,ZcplcFuFuVZL,ZcplcFuFuVZR,           & 
& MFu,MVZ,MRPFuToFuVZ,MRGFuToFuVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFuVZ(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,           & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,MVZ,MVZ2,ZfUL,ZfUR,ZfVPVZ,ZfVZ,AmpWaveFuToFuVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexFuToFuVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRdrFuToFuVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,         & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,          & 
& cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,              & 
& cplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,               & 
& cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,ZcplcFuFuVZL,            & 
& ZcplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,            & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,         & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,          & 
& cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,              & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

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
AmpWaveZFuToFuVZ(1,gt2,:) = AmpWaveZFuToFuVZ(1,gt2,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFuVZ(1,gt1,:) 
AmpVertexZFuToFuVZ(1,gt2,:)= AmpVertexZFuToFuVZ(1,gt2,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFuVZ(1,gt1,:) 
AmpWaveZFuToFuVZ(2,gt2,:) = AmpWaveZFuToFuVZ(2,gt2,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFuVZ(2,gt1,:) 
AmpVertexZFuToFuVZ(2,gt2,:)= AmpVertexZFuToFuVZ(2,gt2,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFuVZ(2,gt1,:) 
AmpWaveZFuToFuVZ(3,gt2,:) = AmpWaveZFuToFuVZ(3,gt2,:)+ZRUVuc(gt2,gt1)*AmpWaveFuToFuVZ(3,gt1,:) 
AmpVertexZFuToFuVZ(3,gt2,:)= AmpVertexZFuToFuVZ(3,gt2,:) + ZRUVuc(gt2,gt1)*AmpVertexFuToFuVZ(3,gt1,:) 
AmpWaveZFuToFuVZ(4,gt2,:) = AmpWaveZFuToFuVZ(4,gt2,:)+ZRUUu(gt2,gt1)*AmpWaveFuToFuVZ(4,gt1,:) 
AmpVertexZFuToFuVZ(4,gt2,:)= AmpVertexZFuToFuVZ(4,gt2,:) + ZRUUu(gt2,gt1)*AmpVertexFuToFuVZ(4,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuVZ=AmpWaveZFuToFuVZ 
AmpVertexFuToFuVZ= AmpVertexZFuToFuVZ
! Final State 1 
AmpWaveZFuToFuVZ=0._dp 
AmpVertexZFuToFuVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuVZ(1,:,gt2) = AmpWaveZFuToFuVZ(1,:,gt2)+ZRUVu(gt2,gt1)*AmpWaveFuToFuVZ(1,:,gt1) 
AmpVertexZFuToFuVZ(1,:,gt2)= AmpVertexZFuToFuVZ(1,:,gt2)+ZRUVu(gt2,gt1)*AmpVertexFuToFuVZ(1,:,gt1) 
AmpWaveZFuToFuVZ(2,:,gt2) = AmpWaveZFuToFuVZ(2,:,gt2)+ZRUUuc(gt2,gt1)*AmpWaveFuToFuVZ(2,:,gt1) 
AmpVertexZFuToFuVZ(2,:,gt2)= AmpVertexZFuToFuVZ(2,:,gt2)+ZRUUuc(gt2,gt1)*AmpVertexFuToFuVZ(2,:,gt1) 
AmpWaveZFuToFuVZ(3,:,gt2) = AmpWaveZFuToFuVZ(3,:,gt2)+ZRUVu(gt2,gt1)*AmpWaveFuToFuVZ(3,:,gt1) 
AmpVertexZFuToFuVZ(3,:,gt2)= AmpVertexZFuToFuVZ(3,:,gt2)+ZRUVu(gt2,gt1)*AmpVertexFuToFuVZ(3,:,gt1) 
AmpWaveZFuToFuVZ(4,:,gt2) = AmpWaveZFuToFuVZ(4,:,gt2)+ZRUUuc(gt2,gt1)*AmpWaveFuToFuVZ(4,:,gt1) 
AmpVertexZFuToFuVZ(4,:,gt2)= AmpVertexZFuToFuVZ(4,:,gt2)+ZRUUuc(gt2,gt1)*AmpVertexFuToFuVZ(4,:,gt1) 
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
! Fu VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_FuToFuVG(ZcplcFuFuVGL,ZcplcFuFuVGR,ctcplcFuFuVGL,       & 
& ctcplcFuFuVGR,MFuOS,MFu2OS,MVG,MVG2,ZfUL,ZfUR,ZfVG,AmpWaveFuToFuVG)

 Else 
Call Amplitude_WAVE_gumTHDMII_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,         & 
& ctcplcFuFuVGR,MFuOS,MFu2OS,MVG,MVG2,ZfUL,ZfUR,ZfVG,AmpWaveFuToFuVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVG(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFuFdcHmL,              & 
& ZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFuHmL,    & 
& ZcplcFdFuHmR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFuVWmL,        & 
& ZcplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplVGVGVG,AmpVertexFuToFuVG)

 Else 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVG(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFdcHmL,cplcFuFdcHmR,      & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplVGVGVG,AmpVertexFuToFuVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,         & 
& ctcplcFuFuVGR,MFu,MFu2,MVG,MVG2,ZfUL,ZfUR,ZfVG,AmpWaveFuToFuVG)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVG(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
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
Call Amplitude_WAVE_gumTHDMII_FuToFuVP(ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,        & 
& ZcplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFuOS,            & 
& MFu2OS,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)

 Else 
Call Amplitude_WAVE_gumTHDMII_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,           & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFuOS,             & 
& MFu2OS,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVP(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdcHmL,              & 
& ZcplcFuFdcHmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFuHmL,    & 
& ZcplcFdFuHmR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFuVWmL,        & 
& ZcplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplHmcHmVP,ZcplHmcVWmVP,ZcplcHmVPVWm,         & 
& ZcplcVWmVPVWm,AmpVertexFuToFuVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVP(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,               & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,      & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,               & 
& AmpVertexFuToFuVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,           & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_FuToFuVP(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,AmpVertexFuToFuVP)

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

End Module Wrapper_OneLoopDecay_Fu_gumTHDMII
