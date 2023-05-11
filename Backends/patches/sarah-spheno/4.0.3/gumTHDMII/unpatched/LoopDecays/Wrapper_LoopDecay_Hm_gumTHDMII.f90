! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Hm_gumTHDMII
Use Model_Data_gumTHDMII 
Use Kinematics 
Use OneLoopDecay_Hm_gumTHDMII 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Hm(MhhOS,Mhh2OS,MAhOS,MAh2OS,MHmOS,MHm2OS,MFdOS,              & 
& MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS,ZAOS,ZPOS,           & 
& ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,               & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,              & 
& ZP,ZW,ZZ,alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,            & 
& m222,vd,vu,dg1,dg2,dg3,dm122,dYu,dYd,dYe,dlam5,dm112,dm222,dlam1,dlam4,dlam3,          & 
& dlam2,dvd,dvu,dZH,dZA,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,          & 
& ZfVG,ZfvL,ZfVP,ZfVZ,ZfVWm,Zfhh,ZfAh,ZfHm,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,ZfVPVZ,         & 
& ZfVZVP,cplAhAhAh,cplAhAhcVWmVWm1,cplAhAhhh,cplAhAhHmcHm1,cplAhcHmVPVWm1,               & 
& cplAhcHmVWm,cplAhcHmVWmVZ1,cplAhhhhh,cplAhhhHmcHm1,cplAhhhVZ,cplAhHmcHm,               & 
& cplAhHmcVWm,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,         & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,             & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,            & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,          & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,         & 
& cplcFvFvVZR,cplcgAgWpCVWm,cplcgWmgWmAh,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,         & 
& cplcgWmgZHm,cplcgWmgZVWm,cplcgWpCgAcHm,cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP,   & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHm,cplcgZgAhh,cplcgZgWmcHm,cplcgZgWpCHm,cplcgZgWpCVWm,       & 
& cplcgZgZhh,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q, & 
& cplcVWmVPVWm,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,          & 
& cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplhhcHmVPVWm1,cplhhcHmVWm,         & 
& cplhhcHmVWmVZ1,cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhHmcHm1,cplhhHmcHm,        & 
& cplhhHmcVWm,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhVZVZ,cplHmcHmcVWmVWm1,cplHmcHmVP,       & 
& cplHmcHmVPVP1,cplHmcHmVPVZ1,cplHmcHmVZ,cplHmcHmVZVZ1,cplHmcVWmVP,cplHmcVWmVZ,          & 
& cplHmHmcHmcHm1,ctcplAhcHmVWm,ctcplAhHmcHm,ctcplcFuFdcHmL,ctcplcFuFdcHmR,               & 
& ctcplcFvFecHmL,ctcplcFvFecHmR,ctcplcHmVPVWm,ctcplcHmVWmVZ,ctcplhhcHmVWm,               & 
& ctcplhhHmcHm,ctcplHmcHmVP,ctcplHmcHmVZ,GcplAhHmcHm,GcplcHmVPVWm,GcplhhHmcHm,           & 
& GcplHmcHmVZ,GcplHmcVWmVP,GosZcplAhHmcHm,GosZcplcHmVPVWm,GosZcplhhHmcHm,GosZcplHmcHmVZ, & 
& GosZcplHmcVWmVP,GZcplAhHmcHm,GZcplcHmVPVWm,GZcplhhHmcHm,GZcplHmcHmVZ,GZcplHmcVWmVP,    & 
& ZcplAhcHmVWm,ZcplAhHmcHm,ZcplcFuFdcHmL,ZcplcFuFdcHmR,ZcplcFvFecHmL,ZcplcFvFecHmR,      & 
& ZcplcHmVWmVZ,ZcplhhcHmVWm,ZcplhhHmcHm,ZcplHmcHmVZ,ZRUZH,ZRUZA,ZRUZP,ZRUVd,             & 
& ZRUUd,ZRUVu,ZRUUu,ZRUVe,ZRUUe,MLambda,em,gs,deltaM,kont,gP1LHm)

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

Complex(dp),Intent(in) :: cplAhAhAh(2,2,2),cplAhAhcVWmVWm1(2,2),cplAhAhhh(2,2,2),cplAhAhHmcHm1(2,2,2,2),        & 
& cplAhcHmVPVWm1(2,2),cplAhcHmVWm(2,2),cplAhcHmVWmVZ1(2,2),cplAhhhhh(2,2,2),             & 
& cplAhhhHmcHm1(2,2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),              & 
& cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),         & 
& cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),               & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHmL(3,3,2),& 
& cplcFdFuHmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFeFeAhL(3,3,2),             & 
& cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVPL(3,3),             & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),& 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),           & 
& cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFecHmL(3,3,2),& 
& cplcFvFecHmR(3,3,2),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),            & 
& cplcFvFvVZR(3,3),cplcgAgWpCVWm,cplcgWmgWmAh(2),cplcgWmgWmhh(2),cplcgWmgWmVP,           & 
& cplcgWmgWmVZ,cplcgWmgZHm(2),cplcgWmgZVWm,cplcgWpCgAcHm(2),cplcgWpCgWpCAh(2),           & 
& cplcgWpCgWpChh(2),cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcgWpCgZcHm(2),cplcgZgAhh(2),        & 
& cplcgZgWmcHm(2),cplcgZgWpCHm(2),cplcgZgWpCVWm,cplcgZgZhh(2),cplcHmVPVWm(2),            & 
& cplcHmVWmVZ(2),cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,        & 
& cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,      & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplhhcHmVPVWm1(2,2),cplhhcHmVWm(2,2),cplhhcHmVWmVZ1(2,2),& 
& cplhhcVWmVWm(2),cplhhhhcVWmVWm1(2,2),cplhhhhhh(2,2,2),cplhhhhHmcHm1(2,2,2,2),          & 
& cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhHmcVWmVP1(2,2),cplhhHmcVWmVZ1(2,2),            & 
& cplhhVZVZ(2),cplHmcHmcVWmVWm1(2,2),cplHmcHmVP(2,2),cplHmcHmVPVP1(2,2),cplHmcHmVPVZ1(2,2),& 
& cplHmcHmVZ(2,2),cplHmcHmVZVZ1(2,2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplHmHmcHmcHm1(2,2,2,2),& 
& ctcplAhcHmVWm(2,2),ctcplAhHmcHm(2,2,2),ctcplcFuFdcHmL(3,3,2),ctcplcFuFdcHmR(3,3,2),    & 
& ctcplcFvFecHmL(3,3,2),ctcplcFvFecHmR(3,3,2),ctcplcHmVPVWm(2),ctcplcHmVWmVZ(2),         & 
& ctcplhhcHmVWm(2,2),ctcplhhHmcHm(2,2,2),ctcplHmcHmVP(2,2),ctcplHmcHmVZ(2,2),            & 
& GcplAhHmcHm(2,2,2),GcplcHmVPVWm(2),GcplhhHmcHm(2,2,2),GcplHmcHmVZ(2,2),GcplHmcVWmVP(2),& 
& GosZcplAhHmcHm(2,2,2),GosZcplcHmVPVWm(2),GosZcplhhHmcHm(2,2,2),GosZcplHmcHmVZ(2,2),    & 
& GosZcplHmcVWmVP(2),GZcplAhHmcHm(2,2,2),GZcplcHmVPVWm(2),GZcplhhHmcHm(2,2,2),           & 
& GZcplHmcHmVZ(2,2),GZcplHmcVWmVP(2),ZcplAhcHmVWm(2,2),ZcplAhHmcHm(2,2,2),               & 
& ZcplcFuFdcHmL(3,3,2),ZcplcFuFdcHmR(3,3,2),ZcplcFvFecHmL(3,3,2),ZcplcFvFecHmR(3,3,2),   & 
& ZcplcHmVWmVZ(2),ZcplhhcHmVWm(2,2),ZcplhhHmcHm(2,2,2),ZcplHmcHmVZ(2,2)

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
Real(dp), Intent(out) :: gP1LHm(2,28) 
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
Real(dp) :: MRPHmToHmAh(2,2,2),MRGHmToHmAh(2,2,2), MRPZHmToHmAh(2,2,2),MRGZHmToHmAh(2,2,2) 
Real(dp) :: MVPHmToHmAh(2,2,2) 
Real(dp) :: RMsqTreeHmToHmAh(2,2,2),RMsqWaveHmToHmAh(2,2,2),RMsqVertexHmToHmAh(2,2,2) 
Complex(dp) :: AmpTreeHmToHmAh(2,2,2),AmpWaveHmToHmAh(2,2,2)=(0._dp,0._dp),AmpVertexHmToHmAh(2,2,2)& 
 & ,AmpVertexIRosHmToHmAh(2,2,2),AmpVertexIRdrHmToHmAh(2,2,2), AmpSumHmToHmAh(2,2,2), AmpSum2HmToHmAh(2,2,2) 
Complex(dp) :: AmpTreeZHmToHmAh(2,2,2),AmpWaveZHmToHmAh(2,2,2),AmpVertexZHmToHmAh(2,2,2) 
Real(dp) :: AmpSqHmToHmAh(2,2,2),  AmpSqTreeHmToHmAh(2,2,2) 
Real(dp) :: MRPHmToAhVWm(2,2),MRGHmToAhVWm(2,2), MRPZHmToAhVWm(2,2),MRGZHmToAhVWm(2,2) 
Real(dp) :: MVPHmToAhVWm(2,2) 
Real(dp) :: RMsqTreeHmToAhVWm(2,2),RMsqWaveHmToAhVWm(2,2),RMsqVertexHmToAhVWm(2,2) 
Complex(dp) :: AmpTreeHmToAhVWm(2,2,2),AmpWaveHmToAhVWm(2,2,2)=(0._dp,0._dp),AmpVertexHmToAhVWm(2,2,2)& 
 & ,AmpVertexIRosHmToAhVWm(2,2,2),AmpVertexIRdrHmToAhVWm(2,2,2), AmpSumHmToAhVWm(2,2,2), AmpSum2HmToAhVWm(2,2,2) 
Complex(dp) :: AmpTreeZHmToAhVWm(2,2,2),AmpWaveZHmToAhVWm(2,2,2),AmpVertexZHmToAhVWm(2,2,2) 
Real(dp) :: AmpSqHmToAhVWm(2,2),  AmpSqTreeHmToAhVWm(2,2) 
Real(dp) :: MRPHmTocFuFd(2,3,3),MRGHmTocFuFd(2,3,3), MRPZHmTocFuFd(2,3,3),MRGZHmTocFuFd(2,3,3) 
Real(dp) :: MVPHmTocFuFd(2,3,3) 
Real(dp) :: RMsqTreeHmTocFuFd(2,3,3),RMsqWaveHmTocFuFd(2,3,3),RMsqVertexHmTocFuFd(2,3,3) 
Complex(dp) :: AmpTreeHmTocFuFd(2,2,3,3),AmpWaveHmTocFuFd(2,2,3,3)=(0._dp,0._dp),AmpVertexHmTocFuFd(2,2,3,3)& 
 & ,AmpVertexIRosHmTocFuFd(2,2,3,3),AmpVertexIRdrHmTocFuFd(2,2,3,3), AmpSumHmTocFuFd(2,2,3,3), AmpSum2HmTocFuFd(2,2,3,3) 
Complex(dp) :: AmpTreeZHmTocFuFd(2,2,3,3),AmpWaveZHmTocFuFd(2,2,3,3),AmpVertexZHmTocFuFd(2,2,3,3) 
Real(dp) :: AmpSqHmTocFuFd(2,3,3),  AmpSqTreeHmTocFuFd(2,3,3) 
Real(dp) :: MRPHmTocFvFe(2,3,3),MRGHmTocFvFe(2,3,3), MRPZHmTocFvFe(2,3,3),MRGZHmTocFvFe(2,3,3) 
Real(dp) :: MVPHmTocFvFe(2,3,3) 
Real(dp) :: RMsqTreeHmTocFvFe(2,3,3),RMsqWaveHmTocFvFe(2,3,3),RMsqVertexHmTocFvFe(2,3,3) 
Complex(dp) :: AmpTreeHmTocFvFe(2,2,3,3),AmpWaveHmTocFvFe(2,2,3,3)=(0._dp,0._dp),AmpVertexHmTocFvFe(2,2,3,3)& 
 & ,AmpVertexIRosHmTocFvFe(2,2,3,3),AmpVertexIRdrHmTocFvFe(2,2,3,3), AmpSumHmTocFvFe(2,2,3,3), AmpSum2HmTocFvFe(2,2,3,3) 
Complex(dp) :: AmpTreeZHmTocFvFe(2,2,3,3),AmpWaveZHmTocFvFe(2,2,3,3),AmpVertexZHmTocFvFe(2,2,3,3) 
Real(dp) :: AmpSqHmTocFvFe(2,3,3),  AmpSqTreeHmTocFvFe(2,3,3) 
Real(dp) :: MRPHmToHmhh(2,2,2),MRGHmToHmhh(2,2,2), MRPZHmToHmhh(2,2,2),MRGZHmToHmhh(2,2,2) 
Real(dp) :: MVPHmToHmhh(2,2,2) 
Real(dp) :: RMsqTreeHmToHmhh(2,2,2),RMsqWaveHmToHmhh(2,2,2),RMsqVertexHmToHmhh(2,2,2) 
Complex(dp) :: AmpTreeHmToHmhh(2,2,2),AmpWaveHmToHmhh(2,2,2)=(0._dp,0._dp),AmpVertexHmToHmhh(2,2,2)& 
 & ,AmpVertexIRosHmToHmhh(2,2,2),AmpVertexIRdrHmToHmhh(2,2,2), AmpSumHmToHmhh(2,2,2), AmpSum2HmToHmhh(2,2,2) 
Complex(dp) :: AmpTreeZHmToHmhh(2,2,2),AmpWaveZHmToHmhh(2,2,2),AmpVertexZHmToHmhh(2,2,2) 
Real(dp) :: AmpSqHmToHmhh(2,2,2),  AmpSqTreeHmToHmhh(2,2,2) 
Real(dp) :: MRPHmTohhVWm(2,2),MRGHmTohhVWm(2,2), MRPZHmTohhVWm(2,2),MRGZHmTohhVWm(2,2) 
Real(dp) :: MVPHmTohhVWm(2,2) 
Real(dp) :: RMsqTreeHmTohhVWm(2,2),RMsqWaveHmTohhVWm(2,2),RMsqVertexHmTohhVWm(2,2) 
Complex(dp) :: AmpTreeHmTohhVWm(2,2,2),AmpWaveHmTohhVWm(2,2,2)=(0._dp,0._dp),AmpVertexHmTohhVWm(2,2,2)& 
 & ,AmpVertexIRosHmTohhVWm(2,2,2),AmpVertexIRdrHmTohhVWm(2,2,2), AmpSumHmTohhVWm(2,2,2), AmpSum2HmTohhVWm(2,2,2) 
Complex(dp) :: AmpTreeZHmTohhVWm(2,2,2),AmpWaveZHmTohhVWm(2,2,2),AmpVertexZHmTohhVWm(2,2,2) 
Real(dp) :: AmpSqHmTohhVWm(2,2),  AmpSqTreeHmTohhVWm(2,2) 
Real(dp) :: MRPHmToHmVZ(2,2),MRGHmToHmVZ(2,2), MRPZHmToHmVZ(2,2),MRGZHmToHmVZ(2,2) 
Real(dp) :: MVPHmToHmVZ(2,2) 
Real(dp) :: RMsqTreeHmToHmVZ(2,2),RMsqWaveHmToHmVZ(2,2),RMsqVertexHmToHmVZ(2,2) 
Complex(dp) :: AmpTreeHmToHmVZ(2,2,2),AmpWaveHmToHmVZ(2,2,2)=(0._dp,0._dp),AmpVertexHmToHmVZ(2,2,2)& 
 & ,AmpVertexIRosHmToHmVZ(2,2,2),AmpVertexIRdrHmToHmVZ(2,2,2), AmpSumHmToHmVZ(2,2,2), AmpSum2HmToHmVZ(2,2,2) 
Complex(dp) :: AmpTreeZHmToHmVZ(2,2,2),AmpWaveZHmToHmVZ(2,2,2),AmpVertexZHmToHmVZ(2,2,2) 
Real(dp) :: AmpSqHmToHmVZ(2,2),  AmpSqTreeHmToHmVZ(2,2) 
Real(dp) :: MRPHmToVZVWm(2),MRGHmToVZVWm(2), MRPZHmToVZVWm(2),MRGZHmToVZVWm(2) 
Real(dp) :: MVPHmToVZVWm(2) 
Real(dp) :: RMsqTreeHmToVZVWm(2),RMsqWaveHmToVZVWm(2),RMsqVertexHmToVZVWm(2) 
Complex(dp) :: AmpTreeHmToVZVWm(2,2),AmpWaveHmToVZVWm(2,2)=(0._dp,0._dp),AmpVertexHmToVZVWm(2,2)& 
 & ,AmpVertexIRosHmToVZVWm(2,2),AmpVertexIRdrHmToVZVWm(2,2), AmpSumHmToVZVWm(2,2), AmpSum2HmToVZVWm(2,2) 
Complex(dp) :: AmpTreeZHmToVZVWm(2,2),AmpWaveZHmToVZVWm(2,2),AmpVertexZHmToVZVWm(2,2) 
Real(dp) :: AmpSqHmToVZVWm(2),  AmpSqTreeHmToVZVWm(2) 
Real(dp) :: MRPHmToHmVP(2,2),MRGHmToHmVP(2,2), MRPZHmToHmVP(2,2),MRGZHmToHmVP(2,2) 
Real(dp) :: MVPHmToHmVP(2,2) 
Real(dp) :: RMsqTreeHmToHmVP(2,2),RMsqWaveHmToHmVP(2,2),RMsqVertexHmToHmVP(2,2) 
Complex(dp) :: AmpTreeHmToHmVP(2,2,2),AmpWaveHmToHmVP(2,2,2)=(0._dp,0._dp),AmpVertexHmToHmVP(2,2,2)& 
 & ,AmpVertexIRosHmToHmVP(2,2,2),AmpVertexIRdrHmToHmVP(2,2,2), AmpSumHmToHmVP(2,2,2), AmpSum2HmToHmVP(2,2,2) 
Complex(dp) :: AmpTreeZHmToHmVP(2,2,2),AmpWaveZHmToHmVP(2,2,2),AmpVertexZHmToHmVP(2,2,2) 
Real(dp) :: AmpSqHmToHmVP(2,2),  AmpSqTreeHmToHmVP(2,2) 
Real(dp) :: MRPHmToVPVWm(2),MRGHmToVPVWm(2), MRPZHmToVPVWm(2),MRGZHmToVPVWm(2) 
Real(dp) :: MVPHmToVPVWm(2) 
Real(dp) :: RMsqTreeHmToVPVWm(2),RMsqWaveHmToVPVWm(2),RMsqVertexHmToVPVWm(2) 
Complex(dp) :: AmpTreeHmToVPVWm(2,2),AmpWaveHmToVPVWm(2,2)=(0._dp,0._dp),AmpVertexHmToVPVWm(2,2)& 
 & ,AmpVertexIRosHmToVPVWm(2,2),AmpVertexIRdrHmToVPVWm(2,2), AmpSumHmToVPVWm(2,2), AmpSum2HmToVPVWm(2,2) 
Complex(dp) :: AmpTreeZHmToVPVWm(2,2),AmpWaveZHmToVPVWm(2,2),AmpVertexZHmToVPVWm(2,2) 
Real(dp) :: AmpSqHmToVPVWm(2),  AmpSqTreeHmToVPVWm(2) 
Write(*,*) "Calculating one-loop decays of Hm " 
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
! Hm Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmToHmAh(cplAhHmcHm,MAh,MHm,MAh2,MHm2,AmpTreeHmToHmAh)

  Else 
Call Amplitude_Tree_gumTHDMII_HmToHmAh(ZcplAhHmcHm,MAh,MHm,MAh2,MHm2,AmpTreeHmToHmAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmAh(MLambda,em,gs,cplAhHmcHm,MAhOS,MHmOS,              & 
& MRPHmToHmAh,MRGHmToHmAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmAh(MLambda,em,gs,ZcplAhHmcHm,MAhOS,MHmOS,             & 
& MRPHmToHmAh,MRGHmToHmAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmToHmAh(MLambda,em,gs,cplAhHmcHm,MAh,MHm,MRPHmToHmAh,      & 
& MRGHmToHmAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmAh(MLambda,em,gs,ZcplAhHmcHm,MAh,MHm,MRPHmToHmAh,     & 
& MRGHmToHmAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToHmAh(cplAhHmcHm,ctcplAhHmcHm,MAh,MAh2,              & 
& MHm,MHm2,ZfAh,ZfHm,AmpWaveHmToHmAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToHmAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,    & 
& cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,            & 
& cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,            & 
& cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,     & 
& cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,  & 
& cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexHmToHmAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,           & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,     & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRdrHmToHmAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& ZcplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,             & 
& cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,             & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,   & 
& cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,             & 
& cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRosHmToHmAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,ZcplAhHmcHm,cplAhHmcVWm,               & 
& cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,           & 
& cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,             & 
& cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,               & 
& cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,            & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,             & 
& cplHmHmcHmcHm1,AmpVertexIRosHmToHmAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,             & 
& cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,             & 
& cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,             & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,   & 
& cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,             & 
& cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRosHmToHmAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,           & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,     & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRosHmToHmAh)

 End if 
 End if 
AmpVertexHmToHmAh = AmpVertexHmToHmAh -  AmpVertexIRdrHmToHmAh! +  AmpVertexIRosHmToHmAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmToHmAh=0._dp 
AmpVertexZHmToHmAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmAh(gt2,:,:) = AmpWaveZHmToHmAh(gt2,:,:)+ZRUZP(gt2,gt1)*AmpWaveHmToHmAh(gt1,:,:) 
AmpVertexZHmToHmAh(gt2,:,:)= AmpVertexZHmToHmAh(gt2,:,:) + ZRUZP(gt2,gt1)*AmpVertexHmToHmAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveHmToHmAh=AmpWaveZHmToHmAh 
AmpVertexHmToHmAh= AmpVertexZHmToHmAh
! Final State 1 
AmpWaveZHmToHmAh=0._dp 
AmpVertexZHmToHmAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmAh(:,gt2,:) = AmpWaveZHmToHmAh(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHmToHmAh(:,gt1,:) 
AmpVertexZHmToHmAh(:,gt2,:)= AmpVertexZHmToHmAh(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexHmToHmAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveHmToHmAh=AmpWaveZHmToHmAh 
AmpVertexHmToHmAh= AmpVertexZHmToHmAh
! Final State 2 
AmpWaveZHmToHmAh=0._dp 
AmpVertexZHmToHmAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmAh(:,:,gt2) = AmpWaveZHmToHmAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveHmToHmAh(:,:,gt1) 
AmpVertexZHmToHmAh(:,:,gt2)= AmpVertexZHmToHmAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexHmToHmAh(:,:,gt1) 
 End Do 
End Do 
AmpWaveHmToHmAh=AmpWaveZHmToHmAh 
AmpVertexHmToHmAh= AmpVertexZHmToHmAh
End if
If (ShiftIRdiv) Then 
AmpVertexHmToHmAh = AmpVertexHmToHmAh  +  AmpVertexIRosHmToHmAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->Hm Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmToHmAh = AmpTreeHmToHmAh 
 AmpSum2HmToHmAh = AmpTreeHmToHmAh + 2._dp*AmpWaveHmToHmAh + 2._dp*AmpVertexHmToHmAh  
Else 
 AmpSumHmToHmAh = AmpTreeHmToHmAh + AmpWaveHmToHmAh + AmpVertexHmToHmAh
 AmpSum2HmToHmAh = AmpTreeHmToHmAh + AmpWaveHmToHmAh + AmpVertexHmToHmAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToHmAh = AmpTreeHmToHmAh
 AmpSum2HmToHmAh = AmpTreeHmToHmAh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MHm(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2HmToHmAh = AmpTreeHmToHmAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),MAh(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmToHmAh(gt1, gt2, gt3) 
  AmpSum2HmToHmAh = 2._dp*AmpWaveHmToHmAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),MAh(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmToHmAh(gt1, gt2, gt3) 
  AmpSum2HmToHmAh = 2._dp*AmpVertexHmToHmAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),MAh(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmToHmAh(gt1, gt2, gt3) 
  AmpSum2HmToHmAh = AmpTreeHmToHmAh + 2._dp*AmpWaveHmToHmAh + 2._dp*AmpVertexHmToHmAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),MAh(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmToHmAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmToHmAh = AmpTreeHmToHmAh
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
  AmpSqTreeHmToHmAh(gt1, gt2, gt3) = AmpSqHmToHmAh(gt1, gt2, gt3)  
  AmpSum2HmToHmAh = + 2._dp*AmpWaveHmToHmAh + 2._dp*AmpVertexHmToHmAh
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
  AmpSqHmToHmAh(gt1, gt2, gt3) = AmpSqHmToHmAh(gt1, gt2, gt3) + AmpSqTreeHmToHmAh(gt1, gt2, gt3)  
Else  
  AmpSum2HmToHmAh = AmpTreeHmToHmAh
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),MAh(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
  AmpSqTreeHmToHmAh(gt1, gt2, gt3) = AmpSqHmToHmAh(gt1, gt2, gt3)  
  AmpSum2HmToHmAh = + 2._dp*AmpWaveHmToHmAh + 2._dp*AmpVertexHmToHmAh
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),MAh(gt3),AmpSumHmToHmAh(gt1, gt2, gt3),AmpSum2HmToHmAh(gt1, gt2, gt3),AmpSqHmToHmAh(gt1, gt2, gt3)) 
  AmpSqHmToHmAh(gt1, gt2, gt3) = AmpSqHmToHmAh(gt1, gt2, gt3) + AmpSqTreeHmToHmAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqHmToHmAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToHmAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),MHmOS(gt2),MAhOS(gt3),helfactor*AmpSqHmToHmAh(gt1, gt2, gt3))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),MHm(gt2),MAh(gt3),helfactor*AmpSqHmToHmAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPHmToHmAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmToHmAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHmToHmAh(gt1, gt2, gt3) + MRGHmToHmAh(gt1, gt2, gt3)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHmToHmAh(gt1, gt2, gt3) + MRGHmToHmAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! Ah VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmToAhVWm(cplAhcHmVWm,MAh,MHm,MVWm,MAh2,MHm2,           & 
& MVWm2,AmpTreeHmToAhVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_HmToAhVWm(ZcplAhcHmVWm,MAh,MHm,MVWm,MAh2,               & 
& MHm2,MVWm2,AmpTreeHmToAhVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmToAhVWm(MLambda,em,gs,cplAhcHmVWm,MAhOS,MHmOS,            & 
& MVWmOS,MRPHmToAhVWm,MRGHmToAhVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmToAhVWm(MLambda,em,gs,ZcplAhcHmVWm,MAhOS,MHmOS,           & 
& MVWmOS,MRPHmToAhVWm,MRGHmToAhVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmToAhVWm(MLambda,em,gs,cplAhcHmVWm,MAh,MHm,MVWm,           & 
& MRPHmToAhVWm,MRGHmToAhVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmToAhVWm(MLambda,em,gs,ZcplAhcHmVWm,MAh,MHm,               & 
& MVWm,MRPHmToAhVWm,MRGHmToAhVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToAhVWm(cplAhcHmVWm,ctcplAhcHmVWm,MAh,MAh2,           & 
& MHm,MHm2,MVWm,MVWm2,ZfAh,ZfHm,ZfVWm,AmpWaveHmToAhVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToAhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,    & 
& cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcgWpCgAcHm,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,      & 
& cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcHmVZ,               & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhcHmVPVWm1,      & 
& cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexHmToAhVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToAhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,      & 
& cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcHmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRdrHmToAhVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToAhVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& GosZcplAhHmcHm,cplAhHmcVWm,ZcplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,        & 
& cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,        & 
& cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,        & 
& cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcHmVZ,GosZcplcHmVPVWm,cplcVWmVPVWm,           & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1, & 
& cplHmcHmcVWmVWm1,AmpVertexIRosHmToAhVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToAhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,GZcplAhHmcHm,cplAhHmcVWm,              & 
& ZcplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,         & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,cplcgZgWmcHm,cplcgAgWpCVWm,       & 
& cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,          & 
& cplHmcHmVP,cplHmcHmVZ,GZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,             & 
& cplAhAhcVWmVWm1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,         & 
& AmpVertexIRosHmToAhVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToAhVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& GcplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,        & 
& cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,        & 
& cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcHmVZ,GcplcHmVPVWm,cplcVWmVPVWm,              & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1, & 
& cplHmcHmcVWmVWm1,AmpVertexIRosHmToAhVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToAhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,      & 
& cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcHmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRosHmToAhVWm)

 End if 
 End if 
AmpVertexHmToAhVWm = AmpVertexHmToAhVWm -  AmpVertexIRdrHmToAhVWm! +  AmpVertexIRosHmToAhVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmToAhVWm=0._dp 
AmpVertexZHmToAhVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToAhVWm(:,gt2,:) = AmpWaveZHmToAhVWm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHmToAhVWm(:,gt1,:) 
AmpVertexZHmToAhVWm(:,gt2,:)= AmpVertexZHmToAhVWm(:,gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHmToAhVWm(:,gt1,:) 
 End Do 
End Do 
AmpWaveHmToAhVWm=AmpWaveZHmToAhVWm 
AmpVertexHmToAhVWm= AmpVertexZHmToAhVWm
! Final State 1 
AmpWaveZHmToAhVWm=0._dp 
AmpVertexZHmToAhVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToAhVWm(:,:,gt2) = AmpWaveZHmToAhVWm(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveHmToAhVWm(:,:,gt1) 
AmpVertexZHmToAhVWm(:,:,gt2)= AmpVertexZHmToAhVWm(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexHmToAhVWm(:,:,gt1) 
 End Do 
End Do 
AmpWaveHmToAhVWm=AmpWaveZHmToAhVWm 
AmpVertexHmToAhVWm= AmpVertexZHmToAhVWm
End if
If (ShiftIRdiv) Then 
AmpVertexHmToAhVWm = AmpVertexHmToAhVWm  +  AmpVertexIRosHmToAhVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->Ah VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmToAhVWm = AmpTreeHmToAhVWm 
 AmpSum2HmToAhVWm = AmpTreeHmToAhVWm + 2._dp*AmpWaveHmToAhVWm + 2._dp*AmpVertexHmToAhVWm  
Else 
 AmpSumHmToAhVWm = AmpTreeHmToAhVWm + AmpWaveHmToAhVWm + AmpVertexHmToAhVWm
 AmpSum2HmToAhVWm = AmpTreeHmToAhVWm + AmpWaveHmToAhVWm + AmpVertexHmToAhVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToAhVWm = AmpTreeHmToAhVWm
 AmpSum2HmToAhVWm = AmpTreeHmToAhVWm 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MAh(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HmToAhVWm = AmpTreeHmToAhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MAhOS(gt2),MVWmOS,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MAh(gt2),MVWm,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmToAhVWm(gt1, gt2) 
  AmpSum2HmToAhVWm = 2._dp*AmpWaveHmToAhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MAhOS(gt2),MVWmOS,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MAh(gt2),MVWm,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmToAhVWm(gt1, gt2) 
  AmpSum2HmToAhVWm = 2._dp*AmpVertexHmToAhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MAhOS(gt2),MVWmOS,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MAh(gt2),MVWm,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmToAhVWm(gt1, gt2) 
  AmpSum2HmToAhVWm = AmpTreeHmToAhVWm + 2._dp*AmpWaveHmToAhVWm + 2._dp*AmpVertexHmToAhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MAhOS(gt2),MVWmOS,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MAh(gt2),MVWm,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmToAhVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmToAhVWm = AmpTreeHmToAhVWm
  Call SquareAmp_StoSV(MHmOS(gt1),MAhOS(gt2),MVWmOS,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
  AmpSqTreeHmToAhVWm(gt1, gt2) = AmpSqHmToAhVWm(gt1, gt2)  
  AmpSum2HmToAhVWm = + 2._dp*AmpWaveHmToAhVWm + 2._dp*AmpVertexHmToAhVWm
  Call SquareAmp_StoSV(MHmOS(gt1),MAhOS(gt2),MVWmOS,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
  AmpSqHmToAhVWm(gt1, gt2) = AmpSqHmToAhVWm(gt1, gt2) + AmpSqTreeHmToAhVWm(gt1, gt2)  
Else  
  AmpSum2HmToAhVWm = AmpTreeHmToAhVWm
  Call SquareAmp_StoSV(MHm(gt1),MAh(gt2),MVWm,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
  AmpSqTreeHmToAhVWm(gt1, gt2) = AmpSqHmToAhVWm(gt1, gt2)  
  AmpSum2HmToAhVWm = + 2._dp*AmpWaveHmToAhVWm + 2._dp*AmpVertexHmToAhVWm
  Call SquareAmp_StoSV(MHm(gt1),MAh(gt2),MVWm,AmpSumHmToAhVWm(:,gt1, gt2),AmpSum2HmToAhVWm(:,gt1, gt2),AmpSqHmToAhVWm(gt1, gt2)) 
  AmpSqHmToAhVWm(gt1, gt2) = AmpSqHmToAhVWm(gt1, gt2) + AmpSqTreeHmToAhVWm(gt1, gt2)  
End if  
Else  
  AmpSqHmToAhVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToAhVWm(gt1, gt2).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),MAhOS(gt2),MVWmOS,helfactor*AmpSqHmToAhVWm(gt1, gt2))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),MAh(gt2),MVWm,helfactor*AmpSqHmToAhVWm(gt1, gt2))
End if 
If ((Abs(MRPHmToAhVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmToAhVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmToAhVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmToAhVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHmToAhVWm(gt1, gt2) + MRGHmToAhVWm(gt1, gt2)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHmToAhVWm(gt1, gt2) + MRGHmToAhVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! bar(Fu) Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmTocFuFd(cplcFuFdcHmL,cplcFuFdcHmR,MFd,MFu,            & 
& MHm,MFd2,MFu2,MHm2,AmpTreeHmTocFuFd)

  Else 
Call Amplitude_Tree_gumTHDMII_HmTocFuFd(ZcplcFuFdcHmL,ZcplcFuFdcHmR,MFd,              & 
& MFu,MHm,MFd2,MFu2,MHm2,AmpTreeHmTocFuFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmTocFuFd(MLambda,em,gs,cplcFuFdcHmL,cplcFuFdcHmR,          & 
& MFdOS,MFuOS,MHmOS,MRPHmTocFuFd,MRGHmTocFuFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmTocFuFd(MLambda,em,gs,ZcplcFuFdcHmL,ZcplcFuFdcHmR,        & 
& MFdOS,MFuOS,MHmOS,MRPHmTocFuFd,MRGHmTocFuFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmTocFuFd(MLambda,em,gs,cplcFuFdcHmL,cplcFuFdcHmR,          & 
& MFd,MFu,MHm,MRPHmTocFuFd,MRGHmTocFuFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmTocFuFd(MLambda,em,gs,ZcplcFuFdcHmL,ZcplcFuFdcHmR,        & 
& MFd,MFu,MHm,MRPHmTocFuFd,MRGHmTocFuFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmTocFuFd(cplcFuFdcHmL,cplcFuFdcHmR,ctcplcFuFdcHmL,     & 
& ctcplcFuFdcHmR,MFd,MFd2,MFu,MFu2,MHm,MHm2,ZfDL,ZfDR,ZfHm,ZfUL,ZfUR,AmpWaveHmTocFuFd)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmTocFuFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexHmTocFuFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFuFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRdrHmTocFuFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFuFd(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,ZcplcFuFdcHmL,ZcplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,AmpVertexIRosHmTocFuFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFuFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,ZcplcFuFdcHmL,             & 
& ZcplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRosHmTocFuFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFuFd(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,AmpVertexIRosHmTocFuFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFuFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRosHmTocFuFd)

 End if 
 End if 
AmpVertexHmTocFuFd = AmpVertexHmTocFuFd -  AmpVertexIRdrHmTocFuFd! +  AmpVertexIRosHmTocFuFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmTocFuFd=0._dp 
AmpVertexZHmTocFuFd=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmTocFuFd(:,gt2,:,:) = AmpWaveZHmTocFuFd(:,gt2,:,:)+ZRUZP(gt2,gt1)*AmpWaveHmTocFuFd(:,gt1,:,:) 
AmpVertexZHmTocFuFd(:,gt2,:,:)= AmpVertexZHmTocFuFd(:,gt2,:,:) + ZRUZP(gt2,gt1)*AmpVertexHmTocFuFd(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveHmTocFuFd=AmpWaveZHmTocFuFd 
AmpVertexHmTocFuFd= AmpVertexZHmTocFuFd
! Final State 1 
AmpWaveZHmTocFuFd=0._dp 
AmpVertexZHmTocFuFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZHmTocFuFd(1,:,gt2,:) = AmpWaveZHmTocFuFd(1,:,gt2,:)+ZRUUu(gt2,gt1)*AmpWaveHmTocFuFd(1,:,gt1,:) 
AmpVertexZHmTocFuFd(1,:,gt2,:)= AmpVertexZHmTocFuFd(1,:,gt2,:)+ZRUUu(gt2,gt1)*AmpVertexHmTocFuFd(1,:,gt1,:) 
AmpWaveZHmTocFuFd(2,:,gt2,:) = AmpWaveZHmTocFuFd(2,:,gt2,:)+ZRUVuc(gt2,gt1)*AmpWaveHmTocFuFd(2,:,gt1,:) 
AmpVertexZHmTocFuFd(2,:,gt2,:)= AmpVertexZHmTocFuFd(2,:,gt2,:)+ZRUVuc(gt2,gt1)*AmpVertexHmTocFuFd(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveHmTocFuFd=AmpWaveZHmTocFuFd 
AmpVertexHmTocFuFd= AmpVertexZHmTocFuFd
! Final State 2 
AmpWaveZHmTocFuFd=0._dp 
AmpVertexZHmTocFuFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZHmTocFuFd(1,:,:,gt2) = AmpWaveZHmTocFuFd(1,:,:,gt2)+ZRUVd(gt2,gt1)*AmpWaveHmTocFuFd(1,:,:,gt1) 
AmpVertexZHmTocFuFd(1,:,:,gt2)= AmpVertexZHmTocFuFd(1,:,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexHmTocFuFd(1,:,:,gt1) 
AmpWaveZHmTocFuFd(2,:,:,gt2) = AmpWaveZHmTocFuFd(2,:,:,gt2)+ZRUUd(gt2,gt1)*AmpWaveHmTocFuFd(2,:,:,gt1) 
AmpVertexZHmTocFuFd(2,:,:,gt2)= AmpVertexZHmTocFuFd(2,:,:,gt2)+ZRUUd(gt2,gt1)*AmpVertexHmTocFuFd(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveHmTocFuFd=AmpWaveZHmTocFuFd 
AmpVertexHmTocFuFd= AmpVertexZHmTocFuFd
End if
If (ShiftIRdiv) Then 
AmpVertexHmTocFuFd = AmpVertexHmTocFuFd  +  AmpVertexIRosHmTocFuFd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->bar[Fu] Fd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmTocFuFd = AmpTreeHmTocFuFd 
 AmpSum2HmTocFuFd = AmpTreeHmTocFuFd + 2._dp*AmpWaveHmTocFuFd + 2._dp*AmpVertexHmTocFuFd  
Else 
 AmpSumHmTocFuFd = AmpTreeHmTocFuFd + AmpWaveHmTocFuFd + AmpVertexHmTocFuFd
 AmpSum2HmTocFuFd = AmpTreeHmTocFuFd + AmpWaveHmTocFuFd + AmpVertexHmTocFuFd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmTocFuFd = AmpTreeHmTocFuFd
 AmpSum2HmTocFuFd = AmpTreeHmTocFuFd 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MFu(gt2))+Abs(MFd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2HmTocFuFd = AmpTreeHmTocFuFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),MFu(gt2),MFd(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmTocFuFd(gt1, gt2, gt3) 
  AmpSum2HmTocFuFd = 2._dp*AmpWaveHmTocFuFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),MFu(gt2),MFd(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmTocFuFd(gt1, gt2, gt3) 
  AmpSum2HmTocFuFd = 2._dp*AmpVertexHmTocFuFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),MFu(gt2),MFd(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmTocFuFd(gt1, gt2, gt3) 
  AmpSum2HmTocFuFd = AmpTreeHmTocFuFd + 2._dp*AmpWaveHmTocFuFd + 2._dp*AmpVertexHmTocFuFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),MFu(gt2),MFd(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmTocFuFd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmTocFuFd = AmpTreeHmTocFuFd
  Call SquareAmp_StoFF(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
  AmpSqTreeHmTocFuFd(gt1, gt2, gt3) = AmpSqHmTocFuFd(gt1, gt2, gt3)  
  AmpSum2HmTocFuFd = + 2._dp*AmpWaveHmTocFuFd + 2._dp*AmpVertexHmTocFuFd
  Call SquareAmp_StoFF(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
  AmpSqHmTocFuFd(gt1, gt2, gt3) = AmpSqHmTocFuFd(gt1, gt2, gt3) + AmpSqTreeHmTocFuFd(gt1, gt2, gt3)  
Else  
  AmpSum2HmTocFuFd = AmpTreeHmTocFuFd
  Call SquareAmp_StoFF(MHm(gt1),MFu(gt2),MFd(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
  AmpSqTreeHmTocFuFd(gt1, gt2, gt3) = AmpSqHmTocFuFd(gt1, gt2, gt3)  
  AmpSum2HmTocFuFd = + 2._dp*AmpWaveHmTocFuFd + 2._dp*AmpVertexHmTocFuFd
  Call SquareAmp_StoFF(MHm(gt1),MFu(gt2),MFd(gt3),AmpSumHmTocFuFd(:,gt1, gt2, gt3),AmpSum2HmTocFuFd(:,gt1, gt2, gt3),AmpSqHmTocFuFd(gt1, gt2, gt3)) 
  AmpSqHmTocFuFd(gt1, gt2, gt3) = AmpSqHmTocFuFd(gt1, gt2, gt3) + AmpSqTreeHmTocFuFd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqHmTocFuFd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqHmTocFuFd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 3._dp*GammaTPS(MHmOS(gt1),MFuOS(gt2),MFdOS(gt3),helfactor*AmpSqHmTocFuFd(gt1, gt2, gt3))
Else 
  gP1LHm(gt1,i4) = 3._dp*GammaTPS(MHm(gt1),MFu(gt2),MFd(gt3),helfactor*AmpSqHmTocFuFd(gt1, gt2, gt3))
End if 
If ((Abs(MRPHmTocFuFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmTocFuFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmTocFuFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmTocFuFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHmTocFuFd(gt1, gt2, gt3) + MRGHmTocFuFd(gt1, gt2, gt3)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHmTocFuFd(gt1, gt2, gt3) + MRGHmTocFuFd(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! bar(Fv) Fe
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmTocFvFe(cplcFvFecHmL,cplcFvFecHmR,MFe,MHm,            & 
& MFe2,MHm2,AmpTreeHmTocFvFe)

  Else 
Call Amplitude_Tree_gumTHDMII_HmTocFvFe(ZcplcFvFecHmL,ZcplcFvFecHmR,MFe,              & 
& MHm,MFe2,MHm2,AmpTreeHmTocFvFe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmTocFvFe(MLambda,em,gs,cplcFvFecHmL,cplcFvFecHmR,          & 
& MFeOS,MHmOS,MRPHmTocFvFe,MRGHmTocFvFe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmTocFvFe(MLambda,em,gs,ZcplcFvFecHmL,ZcplcFvFecHmR,        & 
& MFeOS,MHmOS,MRPHmTocFvFe,MRGHmTocFvFe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmTocFvFe(MLambda,em,gs,cplcFvFecHmL,cplcFvFecHmR,          & 
& MFe,MHm,MRPHmTocFvFe,MRGHmTocFvFe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmTocFvFe(MLambda,em,gs,ZcplcFvFecHmL,ZcplcFvFecHmR,        & 
& MFe,MHm,MRPHmTocFvFe,MRGHmTocFvFe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmTocFvFe(cplcFvFecHmL,cplcFvFecHmR,ctcplcFvFecHmL,     & 
& ctcplcFvFecHmR,MFe,MFe2,MHm,MHm2,ZfEL,ZfER,ZfHm,ZfvL,AmpWaveHmTocFvFe)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmTocFvFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,               & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhcHmVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexHmTocFvFe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFvFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhcHmVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRdrHmTocFvFe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFvFe(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhHmcHm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFeFeVZL,cplcFeFeVZR,ZcplcFvFecHmL,ZcplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplcFvFvVZL,cplcFvFvVZR,cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,AmpVertexIRosHmTocFvFe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFvFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhcHmVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& ZcplcFvFecHmL,ZcplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRosHmTocFvFe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFvFe(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplcFeFeAhL,              & 
& cplcFeFeAhR,cplAhHmcHm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,AmpVertexIRosHmTocFvFe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTocFvFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhcHmVWm,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,AmpVertexIRosHmTocFvFe)

 End if 
 End if 
AmpVertexHmTocFvFe = AmpVertexHmTocFvFe -  AmpVertexIRdrHmTocFvFe! +  AmpVertexIRosHmTocFvFe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmTocFvFe=0._dp 
AmpVertexZHmTocFvFe=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmTocFvFe(:,gt2,:,:) = AmpWaveZHmTocFvFe(:,gt2,:,:)+ZRUZP(gt2,gt1)*AmpWaveHmTocFvFe(:,gt1,:,:) 
AmpVertexZHmTocFvFe(:,gt2,:,:)= AmpVertexZHmTocFvFe(:,gt2,:,:) + ZRUZP(gt2,gt1)*AmpVertexHmTocFvFe(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveHmTocFvFe=AmpWaveZHmTocFvFe 
AmpVertexHmTocFvFe= AmpVertexZHmTocFvFe
! Final State 2 
AmpWaveZHmTocFvFe=0._dp 
AmpVertexZHmTocFvFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZHmTocFvFe(1,:,:,gt2) = AmpWaveZHmTocFvFe(1,:,:,gt2)+ZRUVe(gt2,gt1)*AmpWaveHmTocFvFe(1,:,:,gt1) 
AmpVertexZHmTocFvFe(1,:,:,gt2)= AmpVertexZHmTocFvFe(1,:,:,gt2)+ZRUVe(gt2,gt1)*AmpVertexHmTocFvFe(1,:,:,gt1) 
AmpWaveZHmTocFvFe(2,:,:,gt2) = AmpWaveZHmTocFvFe(2,:,:,gt2)+ZRUUe(gt2,gt1)*AmpWaveHmTocFvFe(2,:,:,gt1) 
AmpVertexZHmTocFvFe(2,:,:,gt2)= AmpVertexZHmTocFvFe(2,:,:,gt2)+ZRUUe(gt2,gt1)*AmpVertexHmTocFvFe(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveHmTocFvFe=AmpWaveZHmTocFvFe 
AmpVertexHmTocFvFe= AmpVertexZHmTocFvFe
End if
If (ShiftIRdiv) Then 
AmpVertexHmTocFvFe = AmpVertexHmTocFvFe  +  AmpVertexIRosHmTocFvFe
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->bar[Fv] Fe -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmTocFvFe = AmpTreeHmTocFvFe 
 AmpSum2HmTocFvFe = AmpTreeHmTocFvFe + 2._dp*AmpWaveHmTocFvFe + 2._dp*AmpVertexHmTocFvFe  
Else 
 AmpSumHmTocFvFe = AmpTreeHmTocFvFe + AmpWaveHmTocFvFe + AmpVertexHmTocFvFe
 AmpSum2HmTocFvFe = AmpTreeHmTocFvFe + AmpWaveHmTocFvFe + AmpVertexHmTocFvFe 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmTocFvFe = AmpTreeHmTocFvFe
 AmpSum2HmTocFvFe = AmpTreeHmTocFvFe 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(0.)+Abs(MFeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(0._dp)+Abs(MFe(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2HmTocFvFe = AmpTreeHmTocFvFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),0._dp,MFeOS(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),0._dp,MFe(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmTocFvFe(gt1, gt2, gt3) 
  AmpSum2HmTocFvFe = 2._dp*AmpWaveHmTocFvFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),0._dp,MFeOS(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),0._dp,MFe(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmTocFvFe(gt1, gt2, gt3) 
  AmpSum2HmTocFvFe = 2._dp*AmpVertexHmTocFvFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),0._dp,MFeOS(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),0._dp,MFe(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmTocFvFe(gt1, gt2, gt3) 
  AmpSum2HmTocFvFe = AmpTreeHmTocFvFe + 2._dp*AmpWaveHmTocFvFe + 2._dp*AmpVertexHmTocFvFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MHmOS(gt1),0._dp,MFeOS(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MHm(gt1),0._dp,MFe(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmTocFvFe(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmTocFvFe = AmpTreeHmTocFvFe
  Call SquareAmp_StoFF(MHmOS(gt1),0._dp,MFeOS(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
  AmpSqTreeHmTocFvFe(gt1, gt2, gt3) = AmpSqHmTocFvFe(gt1, gt2, gt3)  
  AmpSum2HmTocFvFe = + 2._dp*AmpWaveHmTocFvFe + 2._dp*AmpVertexHmTocFvFe
  Call SquareAmp_StoFF(MHmOS(gt1),0._dp,MFeOS(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
  AmpSqHmTocFvFe(gt1, gt2, gt3) = AmpSqHmTocFvFe(gt1, gt2, gt3) + AmpSqTreeHmTocFvFe(gt1, gt2, gt3)  
Else  
  AmpSum2HmTocFvFe = AmpTreeHmTocFvFe
  Call SquareAmp_StoFF(MHm(gt1),0._dp,MFe(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
  AmpSqTreeHmTocFvFe(gt1, gt2, gt3) = AmpSqHmTocFvFe(gt1, gt2, gt3)  
  AmpSum2HmTocFvFe = + 2._dp*AmpWaveHmTocFvFe + 2._dp*AmpVertexHmTocFvFe
  Call SquareAmp_StoFF(MHm(gt1),0._dp,MFe(gt3),AmpSumHmTocFvFe(:,gt1, gt2, gt3),AmpSum2HmTocFvFe(:,gt1, gt2, gt3),AmpSqHmTocFvFe(gt1, gt2, gt3)) 
  AmpSqHmTocFvFe(gt1, gt2, gt3) = AmpSqHmTocFvFe(gt1, gt2, gt3) + AmpSqTreeHmTocFvFe(gt1, gt2, gt3)  
End if  
Else  
  AmpSqHmTocFvFe(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqHmTocFvFe(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),0._dp,MFeOS(gt3),helfactor*AmpSqHmTocFvFe(gt1, gt2, gt3))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),0._dp,MFe(gt3),helfactor*AmpSqHmTocFvFe(gt1, gt2, gt3))
End if 
If ((Abs(MRPHmTocFvFe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmTocFvFe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmTocFvFe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmTocFvFe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHmTocFvFe(gt1, gt2, gt3) + MRGHmTocFvFe(gt1, gt2, gt3)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHmTocFvFe(gt1, gt2, gt3) + MRGHmTocFvFe(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! Hm hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmToHmhh(cplhhHmcHm,Mhh,MHm,Mhh2,MHm2,AmpTreeHmToHmhh)

  Else 
Call Amplitude_Tree_gumTHDMII_HmToHmhh(ZcplhhHmcHm,Mhh,MHm,Mhh2,MHm2,AmpTreeHmToHmhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmhh(MLambda,em,gs,cplhhHmcHm,MhhOS,MHmOS,              & 
& MRPHmToHmhh,MRGHmToHmhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmhh(MLambda,em,gs,ZcplhhHmcHm,MhhOS,MHmOS,             & 
& MRPHmToHmhh,MRGHmToHmhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmToHmhh(MLambda,em,gs,cplhhHmcHm,Mhh,MHm,MRPHmToHmhh,      & 
& MRGHmToHmhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmhh(MLambda,em,gs,ZcplhhHmcHm,Mhh,MHm,MRPHmToHmhh,     & 
& MRGHmToHmhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToHmhh(cplhhHmcHm,ctcplhhHmcHm,Mhh,Mhh2,              & 
& MHm,MHm2,Zfhh,ZfHm,AmpWaveHmToHmhh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToHmhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,       & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,               & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,        & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexHmToHmhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,     & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,        & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexIRdrHmToHmhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmhh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,         & 
& cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,cplhhhhhh,ZcplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,    & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,   & 
& cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,           & 
& AmpVertexIRosHmToHmhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,     & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,ZcplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,       & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexIRosHmToHmhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmhh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,         & 
& cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,     & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,   & 
& cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,           & 
& AmpVertexIRosHmToHmhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,     & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,        & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexIRosHmToHmhh)

 End if 
 End if 
AmpVertexHmToHmhh = AmpVertexHmToHmhh -  AmpVertexIRdrHmToHmhh! +  AmpVertexIRosHmToHmhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmToHmhh=0._dp 
AmpVertexZHmToHmhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmhh(gt2,:,:) = AmpWaveZHmToHmhh(gt2,:,:)+ZRUZP(gt2,gt1)*AmpWaveHmToHmhh(gt1,:,:) 
AmpVertexZHmToHmhh(gt2,:,:)= AmpVertexZHmToHmhh(gt2,:,:) + ZRUZP(gt2,gt1)*AmpVertexHmToHmhh(gt1,:,:) 
 End Do 
End Do 
AmpWaveHmToHmhh=AmpWaveZHmToHmhh 
AmpVertexHmToHmhh= AmpVertexZHmToHmhh
! Final State 1 
AmpWaveZHmToHmhh=0._dp 
AmpVertexZHmToHmhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmhh(:,gt2,:) = AmpWaveZHmToHmhh(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHmToHmhh(:,gt1,:) 
AmpVertexZHmToHmhh(:,gt2,:)= AmpVertexZHmToHmhh(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexHmToHmhh(:,gt1,:) 
 End Do 
End Do 
AmpWaveHmToHmhh=AmpWaveZHmToHmhh 
AmpVertexHmToHmhh= AmpVertexZHmToHmhh
! Final State 2 
AmpWaveZHmToHmhh=0._dp 
AmpVertexZHmToHmhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmhh(:,:,gt2) = AmpWaveZHmToHmhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveHmToHmhh(:,:,gt1) 
AmpVertexZHmToHmhh(:,:,gt2)= AmpVertexZHmToHmhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexHmToHmhh(:,:,gt1) 
 End Do 
End Do 
AmpWaveHmToHmhh=AmpWaveZHmToHmhh 
AmpVertexHmToHmhh= AmpVertexZHmToHmhh
End if
If (ShiftIRdiv) Then 
AmpVertexHmToHmhh = AmpVertexHmToHmhh  +  AmpVertexIRosHmToHmhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->Hm hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmToHmhh = AmpTreeHmToHmhh 
 AmpSum2HmToHmhh = AmpTreeHmToHmhh + 2._dp*AmpWaveHmToHmhh + 2._dp*AmpVertexHmToHmhh  
Else 
 AmpSumHmToHmhh = AmpTreeHmToHmhh + AmpWaveHmToHmhh + AmpVertexHmToHmhh
 AmpSum2HmToHmhh = AmpTreeHmToHmhh + AmpWaveHmToHmhh + AmpVertexHmToHmhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToHmhh = AmpTreeHmToHmhh
 AmpSum2HmToHmhh = AmpTreeHmToHmhh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MHm(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2HmToHmhh = AmpTreeHmToHmhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),Mhh(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmToHmhh(gt1, gt2, gt3) 
  AmpSum2HmToHmhh = 2._dp*AmpWaveHmToHmhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),Mhh(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmToHmhh(gt1, gt2, gt3) 
  AmpSum2HmToHmhh = 2._dp*AmpVertexHmToHmhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),Mhh(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmToHmhh(gt1, gt2, gt3) 
  AmpSum2HmToHmhh = AmpTreeHmToHmhh + 2._dp*AmpWaveHmToHmhh + 2._dp*AmpVertexHmToHmhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),Mhh(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmToHmhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmToHmhh = AmpTreeHmToHmhh
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
  AmpSqTreeHmToHmhh(gt1, gt2, gt3) = AmpSqHmToHmhh(gt1, gt2, gt3)  
  AmpSum2HmToHmhh = + 2._dp*AmpWaveHmToHmhh + 2._dp*AmpVertexHmToHmhh
  Call SquareAmp_StoSS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
  AmpSqHmToHmhh(gt1, gt2, gt3) = AmpSqHmToHmhh(gt1, gt2, gt3) + AmpSqTreeHmToHmhh(gt1, gt2, gt3)  
Else  
  AmpSum2HmToHmhh = AmpTreeHmToHmhh
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),Mhh(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
  AmpSqTreeHmToHmhh(gt1, gt2, gt3) = AmpSqHmToHmhh(gt1, gt2, gt3)  
  AmpSum2HmToHmhh = + 2._dp*AmpWaveHmToHmhh + 2._dp*AmpVertexHmToHmhh
  Call SquareAmp_StoSS(MHm(gt1),MHm(gt2),Mhh(gt3),AmpSumHmToHmhh(gt1, gt2, gt3),AmpSum2HmToHmhh(gt1, gt2, gt3),AmpSqHmToHmhh(gt1, gt2, gt3)) 
  AmpSqHmToHmhh(gt1, gt2, gt3) = AmpSqHmToHmhh(gt1, gt2, gt3) + AmpSqTreeHmToHmhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqHmToHmhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToHmhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),MHmOS(gt2),MhhOS(gt3),helfactor*AmpSqHmToHmhh(gt1, gt2, gt3))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),MHm(gt2),Mhh(gt3),helfactor*AmpSqHmToHmhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPHmToHmhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmToHmhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPHmToHmhh(gt1, gt2, gt3) + MRGHmToHmhh(gt1, gt2, gt3)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPHmToHmhh(gt1, gt2, gt3) + MRGHmToHmhh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! hh VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmTohhVWm(cplhhcHmVWm,Mhh,MHm,MVWm,Mhh2,MHm2,           & 
& MVWm2,AmpTreeHmTohhVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_HmTohhVWm(ZcplhhcHmVWm,Mhh,MHm,MVWm,Mhh2,               & 
& MHm2,MVWm2,AmpTreeHmTohhVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmTohhVWm(MLambda,em,gs,cplhhcHmVWm,MhhOS,MHmOS,            & 
& MVWmOS,MRPHmTohhVWm,MRGHmTohhVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmTohhVWm(MLambda,em,gs,ZcplhhcHmVWm,MhhOS,MHmOS,           & 
& MVWmOS,MRPHmTohhVWm,MRGHmTohhVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmTohhVWm(MLambda,em,gs,cplhhcHmVWm,Mhh,MHm,MVWm,           & 
& MRPHmTohhVWm,MRGHmTohhVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmTohhVWm(MLambda,em,gs,ZcplhhcHmVWm,Mhh,MHm,               & 
& MVWm,MRPHmTohhVWm,MRGHmTohhVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmTohhVWm(cplhhcHmVWm,ctcplhhcHmVWm,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,Zfhh,ZfHm,ZfVWm,AmpWaveHmTohhVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmTohhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,       & 
& cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,              & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWpCgAcHm,          & 
& cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,       & 
& cplcgWmgZVWm,cplcgWpCgZcHm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,             & 
& cplHmcHmcVWmVWm1,AmpVertexHmTohhVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTohhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWpCgAcHm,          & 
& cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,       & 
& cplcgWmgZVWm,cplcgWpCgZcHm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,             & 
& cplHmcHmcVWmVWm1,AmpVertexIRdrHmTohhVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTohhVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,               & 
& cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,           & 
& cplcFeFvVWmR,cplcgZgAhh,cplcgWpCgAcHm,cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,        & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhhhhh,           & 
& GosZcplhhHmcHm,cplhhHmcVWm,ZcplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,             & 
& cplHmcHmVZ,GosZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,       & 
& cplhhhhcVWmVWm1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRosHmTohhVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTohhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWpCgAcHm,          & 
& cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,       & 
& cplcgWmgZVWm,cplcgWpCgZcHm,cplhhhhhh,GZcplhhHmcHm,cplhhHmcVWm,ZcplhhcHmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,GZcplcHmVPVWm,cplcVWmVPVWm,               & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1, & 
& cplHmcHmcVWmVWm1,AmpVertexIRosHmTohhVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTohhVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,               & 
& cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,           & 
& cplcFeFvVWmR,cplcgZgAhh,cplcgWpCgAcHm,cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,        & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhhhhh,           & 
& GcplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,      & 
& GcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,     & 
& cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRosHmTohhVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmTohhVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWpCgAcHm,          & 
& cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,       & 
& cplcgWmgZVWm,cplcgWpCgZcHm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,     & 
& cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,             & 
& cplHmcHmcVWmVWm1,AmpVertexIRosHmTohhVWm)

 End if 
 End if 
AmpVertexHmTohhVWm = AmpVertexHmTohhVWm -  AmpVertexIRdrHmTohhVWm! +  AmpVertexIRosHmTohhVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmTohhVWm=0._dp 
AmpVertexZHmTohhVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmTohhVWm(:,gt2,:) = AmpWaveZHmTohhVWm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHmTohhVWm(:,gt1,:) 
AmpVertexZHmTohhVWm(:,gt2,:)= AmpVertexZHmTohhVWm(:,gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHmTohhVWm(:,gt1,:) 
 End Do 
End Do 
AmpWaveHmTohhVWm=AmpWaveZHmTohhVWm 
AmpVertexHmTohhVWm= AmpVertexZHmTohhVWm
! Final State 1 
AmpWaveZHmTohhVWm=0._dp 
AmpVertexZHmTohhVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmTohhVWm(:,:,gt2) = AmpWaveZHmTohhVWm(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveHmTohhVWm(:,:,gt1) 
AmpVertexZHmTohhVWm(:,:,gt2)= AmpVertexZHmTohhVWm(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexHmTohhVWm(:,:,gt1) 
 End Do 
End Do 
AmpWaveHmTohhVWm=AmpWaveZHmTohhVWm 
AmpVertexHmTohhVWm= AmpVertexZHmTohhVWm
End if
If (ShiftIRdiv) Then 
AmpVertexHmTohhVWm = AmpVertexHmTohhVWm  +  AmpVertexIRosHmTohhVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->hh VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmTohhVWm = AmpTreeHmTohhVWm 
 AmpSum2HmTohhVWm = AmpTreeHmTohhVWm + 2._dp*AmpWaveHmTohhVWm + 2._dp*AmpVertexHmTohhVWm  
Else 
 AmpSumHmTohhVWm = AmpTreeHmTohhVWm + AmpWaveHmTohhVWm + AmpVertexHmTohhVWm
 AmpSum2HmTohhVWm = AmpTreeHmTohhVWm + AmpWaveHmTohhVWm + AmpVertexHmTohhVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmTohhVWm = AmpTreeHmTohhVWm
 AmpSum2HmTohhVWm = AmpTreeHmTohhVWm 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(Mhh(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HmTohhVWm = AmpTreeHmTohhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MhhOS(gt2),MVWmOS,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),Mhh(gt2),MVWm,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmTohhVWm(gt1, gt2) 
  AmpSum2HmTohhVWm = 2._dp*AmpWaveHmTohhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MhhOS(gt2),MVWmOS,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),Mhh(gt2),MVWm,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmTohhVWm(gt1, gt2) 
  AmpSum2HmTohhVWm = 2._dp*AmpVertexHmTohhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MhhOS(gt2),MVWmOS,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),Mhh(gt2),MVWm,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmTohhVWm(gt1, gt2) 
  AmpSum2HmTohhVWm = AmpTreeHmTohhVWm + 2._dp*AmpWaveHmTohhVWm + 2._dp*AmpVertexHmTohhVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MhhOS(gt2),MVWmOS,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),Mhh(gt2),MVWm,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmTohhVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmTohhVWm = AmpTreeHmTohhVWm
  Call SquareAmp_StoSV(MHmOS(gt1),MhhOS(gt2),MVWmOS,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
  AmpSqTreeHmTohhVWm(gt1, gt2) = AmpSqHmTohhVWm(gt1, gt2)  
  AmpSum2HmTohhVWm = + 2._dp*AmpWaveHmTohhVWm + 2._dp*AmpVertexHmTohhVWm
  Call SquareAmp_StoSV(MHmOS(gt1),MhhOS(gt2),MVWmOS,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
  AmpSqHmTohhVWm(gt1, gt2) = AmpSqHmTohhVWm(gt1, gt2) + AmpSqTreeHmTohhVWm(gt1, gt2)  
Else  
  AmpSum2HmTohhVWm = AmpTreeHmTohhVWm
  Call SquareAmp_StoSV(MHm(gt1),Mhh(gt2),MVWm,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
  AmpSqTreeHmTohhVWm(gt1, gt2) = AmpSqHmTohhVWm(gt1, gt2)  
  AmpSum2HmTohhVWm = + 2._dp*AmpWaveHmTohhVWm + 2._dp*AmpVertexHmTohhVWm
  Call SquareAmp_StoSV(MHm(gt1),Mhh(gt2),MVWm,AmpSumHmTohhVWm(:,gt1, gt2),AmpSum2HmTohhVWm(:,gt1, gt2),AmpSqHmTohhVWm(gt1, gt2)) 
  AmpSqHmTohhVWm(gt1, gt2) = AmpSqHmTohhVWm(gt1, gt2) + AmpSqTreeHmTohhVWm(gt1, gt2)  
End if  
Else  
  AmpSqHmTohhVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmTohhVWm(gt1, gt2).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),MhhOS(gt2),MVWmOS,helfactor*AmpSqHmTohhVWm(gt1, gt2))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),Mhh(gt2),MVWm,helfactor*AmpSqHmTohhVWm(gt1, gt2))
End if 
If ((Abs(MRPHmTohhVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmTohhVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmTohhVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmTohhVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHmTohhVWm(gt1, gt2) + MRGHmTohhVWm(gt1, gt2)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHmTohhVWm(gt1, gt2) + MRGHmTohhVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! Hm VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmToHmVZ(cplHmcHmVZ,MHm,MVZ,MHm2,MVZ2,AmpTreeHmToHmVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_HmToHmVZ(ZcplHmcHmVZ,MHm,MVZ,MHm2,MVZ2,AmpTreeHmToHmVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmVZ(MLambda,em,gs,cplHmcHmVZ,MHmOS,MVZOS,              & 
& MRPHmToHmVZ,MRGHmToHmVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmVZ(MLambda,em,gs,ZcplHmcHmVZ,MHmOS,MVZOS,             & 
& MRPHmToHmVZ,MRGHmToHmVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmToHmVZ(MLambda,em,gs,cplHmcHmVZ,MHm,MVZ,MRPHmToHmVZ,      & 
& MRGHmToHmVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmToHmVZ(MLambda,em,gs,ZcplHmcHmVZ,MHm,MVZ,MRPHmToHmVZ,     & 
& MRGHmToHmVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToHmVZ(cplHmcHmVP,cplHmcHmVZ,ctcplHmcHmVP,            & 
& ctcplHmcHmVZ,MHm,MHm2,MVP,MVP2,MVZ,MVZ2,ZfHm,ZfVPVZ,ZfVZ,AmpWaveHmToHmVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToHmVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,             & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,              & 
& cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVZ,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,         & 
& cplhhHmcVWm,cplhhcHmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,       & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhHmcVWmVZ1,     & 
& cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmVZVZ1,AmpVertexHmToHmVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,           & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWmgWmVZ,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVZ,cplcgWmgZHm,cplcgWpCgZcHm,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,        & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,        & 
& cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmVZVZ1,AmpVertexIRdrHmToHmVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,           & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVZ,         & 
& cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhVZVZ,cplHmcHmVP,     & 
& cplHmcVWmVP,ZcplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,              & 
& cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,             & 
& cplHmcHmVZVZ1,AmpVertexIRosHmToHmVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,           & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWmgWmVZ,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVZ,cplcgWmgZHm,cplcgWpCgZcHm,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,ZcplHmcHmVZ,       & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,        & 
& cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmVZVZ1,AmpVertexIRosHmToHmVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,           & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVZ,         & 
& cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhVZVZ,cplHmcHmVP,     & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,               & 
& cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,             & 
& cplHmcHmVZVZ1,AmpVertexIRosHmToHmVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToHmVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,           & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWmgWmVZ,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVZ,cplcgWmgZHm,cplcgWpCgZcHm,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,        & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,        & 
& cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmVZVZ1,AmpVertexIRosHmToHmVZ)

 End if 
 End if 
AmpVertexHmToHmVZ = AmpVertexHmToHmVZ -  AmpVertexIRdrHmToHmVZ! +  AmpVertexIRosHmToHmVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmToHmVZ=0._dp 
AmpVertexZHmToHmVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmVZ(:,gt2,:) = AmpWaveZHmToHmVZ(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveHmToHmVZ(:,gt1,:) 
AmpVertexZHmToHmVZ(:,gt2,:)= AmpVertexZHmToHmVZ(:,gt2,:) + ZRUZP(gt2,gt1)*AmpVertexHmToHmVZ(:,gt1,:) 
 End Do 
End Do 
AmpWaveHmToHmVZ=AmpWaveZHmToHmVZ 
AmpVertexHmToHmVZ= AmpVertexZHmToHmVZ
! Final State 1 
AmpWaveZHmToHmVZ=0._dp 
AmpVertexZHmToHmVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToHmVZ(:,:,gt2) = AmpWaveZHmToHmVZ(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHmToHmVZ(:,:,gt1) 
AmpVertexZHmToHmVZ(:,:,gt2)= AmpVertexZHmToHmVZ(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexHmToHmVZ(:,:,gt1) 
 End Do 
End Do 
AmpWaveHmToHmVZ=AmpWaveZHmToHmVZ 
AmpVertexHmToHmVZ= AmpVertexZHmToHmVZ
End if
If (ShiftIRdiv) Then 
AmpVertexHmToHmVZ = AmpVertexHmToHmVZ  +  AmpVertexIRosHmToHmVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->Hm VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmToHmVZ = AmpTreeHmToHmVZ 
 AmpSum2HmToHmVZ = AmpTreeHmToHmVZ + 2._dp*AmpWaveHmToHmVZ + 2._dp*AmpVertexHmToHmVZ  
Else 
 AmpSumHmToHmVZ = AmpTreeHmToHmVZ + AmpWaveHmToHmVZ + AmpVertexHmToHmVZ
 AmpSum2HmToHmVZ = AmpTreeHmToHmVZ + AmpWaveHmToHmVZ + AmpVertexHmToHmVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToHmVZ = AmpTreeHmToHmVZ
 AmpSum2HmToHmVZ = AmpTreeHmToHmVZ 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MHm(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2HmToHmVZ = AmpTreeHmToHmVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),MVZOS,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVZ,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmToHmVZ(gt1, gt2) 
  AmpSum2HmToHmVZ = 2._dp*AmpWaveHmToHmVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),MVZOS,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVZ,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmToHmVZ(gt1, gt2) 
  AmpSum2HmToHmVZ = 2._dp*AmpVertexHmToHmVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),MVZOS,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVZ,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmToHmVZ(gt1, gt2) 
  AmpSum2HmToHmVZ = AmpTreeHmToHmVZ + 2._dp*AmpWaveHmToHmVZ + 2._dp*AmpVertexHmToHmVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),MVZOS,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVZ,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmToHmVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmToHmVZ = AmpTreeHmToHmVZ
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),MVZOS,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
  AmpSqTreeHmToHmVZ(gt1, gt2) = AmpSqHmToHmVZ(gt1, gt2)  
  AmpSum2HmToHmVZ = + 2._dp*AmpWaveHmToHmVZ + 2._dp*AmpVertexHmToHmVZ
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),MVZOS,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
  AmpSqHmToHmVZ(gt1, gt2) = AmpSqHmToHmVZ(gt1, gt2) + AmpSqTreeHmToHmVZ(gt1, gt2)  
Else  
  AmpSum2HmToHmVZ = AmpTreeHmToHmVZ
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVZ,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
  AmpSqTreeHmToHmVZ(gt1, gt2) = AmpSqHmToHmVZ(gt1, gt2)  
  AmpSum2HmToHmVZ = + 2._dp*AmpWaveHmToHmVZ + 2._dp*AmpVertexHmToHmVZ
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVZ,AmpSumHmToHmVZ(:,gt1, gt2),AmpSum2HmToHmVZ(:,gt1, gt2),AmpSqHmToHmVZ(gt1, gt2)) 
  AmpSqHmToHmVZ(gt1, gt2) = AmpSqHmToHmVZ(gt1, gt2) + AmpSqTreeHmToHmVZ(gt1, gt2)  
End if  
Else  
  AmpSqHmToHmVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToHmVZ(gt1, gt2).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),MHmOS(gt2),MVZOS,helfactor*AmpSqHmToHmVZ(gt1, gt2))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),MHm(gt2),MVZ,helfactor*AmpSqHmToHmVZ(gt1, gt2))
End if 
If ((Abs(MRPHmToHmVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmToHmVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPHmToHmVZ(gt1, gt2) + MRGHmToHmVZ(gt1, gt2)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPHmToHmVZ(gt1, gt2) + MRGHmToHmVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
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
! VZ VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_HmToVZVWm(cplcHmVWmVZ,MHm,MVWm,MVZ,MHm2,MVWm2,          & 
& MVZ2,AmpTreeHmToVZVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_HmToVZVWm(ZcplcHmVWmVZ,MHm,MVWm,MVZ,MHm2,               & 
& MVWm2,MVZ2,AmpTreeHmToVZVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_HmToVZVWm(MLambda,em,gs,cplcHmVWmVZ,MHmOS,MVWmOS,           & 
& MVZOS,MRPHmToVZVWm,MRGHmToVZVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_HmToVZVWm(MLambda,em,gs,ZcplcHmVWmVZ,MHmOS,MVWmOS,          & 
& MVZOS,MRPHmToVZVWm,MRGHmToVZVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_HmToVZVWm(MLambda,em,gs,cplcHmVWmVZ,MHm,MVWm,               & 
& MVZ,MRPHmToVZVWm,MRGHmToVZVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_HmToVZVWm(MLambda,em,gs,ZcplcHmVWmVZ,MHm,MVWm,              & 
& MVZ,MRPHmToVZVWm,MRGHmToVZVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToVZVWm(cplcHmVPVWm,cplcHmVWmVZ,ctcplcHmVPVWm,        & 
& ctcplcHmVWmVZ,MHm,MHm2,MVP,MVP2,MVWm,MVWm2,MVZ,MVZ2,ZfHm,ZfVWm,ZfVZ,AmpWaveHmToVZVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToVZVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,    & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,cplcFeFeVZR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpCgAcHm,cplcgWmgWmVZ,          & 
& cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcHm,    & 
& cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVZ,       & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,       & 
& cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,        & 
& cplcVWmVPVWmVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexHmToVZVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToVZVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,           & 
& cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,             & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpCgAcHm,           & 
& cplcgWmgWmVZ,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,     & 
& cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,     & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,          & 
& cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,cplcVWmVPVWmVZ3Q,          & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,  & 
& AmpVertexIRdrHmToVZVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToVZVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,          & 
& cplcFuFdcHmR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,           & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,            & 
& cplcFvFvVZR,cplcgWpCgAcHm,cplcgWmgWmVZ,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,       & 
& cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,         & 
& cplhhVZVZ,cplHmcHmVP,GosZcplHmcHmVZ,cplHmcVWmVZ,GosZcplcHmVPVWm,cplcVWmVPVWm,          & 
& ZcplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,& 
& cplHmcHmVZVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,cplcVWmVWmVZVZ2Q,     & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRosHmToVZVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToVZVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,           & 
& cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,             & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpCgAcHm,           & 
& cplcgWmgWmVZ,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,     & 
& cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,GZcplHmcHmVZ,   & 
& cplHmcVWmVZ,GZcplcHmVPVWm,cplcVWmVPVWm,ZcplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,       & 
& cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,cplcVWmVPVWmVZ3Q,          & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,  & 
& AmpVertexIRosHmToVZVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToVZVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhhhVZ,cplAhHmcHm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,          & 
& cplcFuFdcHmR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,           & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,            & 
& cplcFvFvVZR,cplcgWpCgAcHm,cplcgWmgWmVZ,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,       & 
& cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,         & 
& cplhhVZVZ,cplHmcHmVP,GcplHmcHmVZ,cplHmcVWmVZ,GcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,    & 
& cplcVWmVWmVZ,cplAhcHmVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,             & 
& cplHmcHmVZVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,cplcVWmVWmVZVZ2Q,     & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRosHmToVZVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_HmToVZVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhHmcHm,           & 
& cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVZL,             & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpCgAcHm,           & 
& cplcgWmgWmVZ,cplcgZgWmcHm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,     & 
& cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,     & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVWmVZ1,          & 
& cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,cplcVWmVPVWmVZ3Q,          & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,  & 
& AmpVertexIRosHmToVZVWm)

 End if 
 End if 
AmpVertexHmToVZVWm = AmpVertexHmToVZVWm -  AmpVertexIRdrHmToVZVWm! +  AmpVertexIRosHmToVZVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZHmToVZVWm=0._dp 
AmpVertexZHmToVZVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZHmToVZVWm(:,gt2) = AmpWaveZHmToVZVWm(:,gt2)+ZRUZP(gt2,gt1)*AmpWaveHmToVZVWm(:,gt1) 
AmpVertexZHmToVZVWm(:,gt2)= AmpVertexZHmToVZVWm(:,gt2) + ZRUZP(gt2,gt1)*AmpVertexHmToVZVWm(:,gt1) 
 End Do 
End Do 
AmpWaveHmToVZVWm=AmpWaveZHmToVZVWm 
AmpVertexHmToVZVWm= AmpVertexZHmToVZVWm
End if
If (ShiftIRdiv) Then 
AmpVertexHmToVZVWm = AmpVertexHmToVZVWm  +  AmpVertexIRosHmToVZVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->VZ VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumHmToVZVWm = AmpTreeHmToVZVWm 
 AmpSum2HmToVZVWm = AmpTreeHmToVZVWm + 2._dp*AmpWaveHmToVZVWm + 2._dp*AmpVertexHmToVZVWm  
Else 
 AmpSumHmToVZVWm = AmpTreeHmToVZVWm + AmpWaveHmToVZVWm + AmpVertexHmToVZVWm
 AmpSum2HmToVZVWm = AmpTreeHmToVZVWm + AmpWaveHmToVZVWm + AmpVertexHmToVZVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToVZVWm = AmpTreeHmToVZVWm
 AmpSum2HmToVZVWm = AmpTreeHmToVZVWm 
End if 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MVZOS)+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MVZ)+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2HmToVZVWm = AmpTreeHmToVZVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHmOS(gt1),MVZOS,MVWmOS,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(MHm(gt1),MVZ,MVWm,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqHmToVZVWm(gt1) 
  AmpSum2HmToVZVWm = 2._dp*AmpWaveHmToVZVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHmOS(gt1),MVZOS,MVWmOS,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(MHm(gt1),MVZ,MVWm,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqHmToVZVWm(gt1) 
  AmpSum2HmToVZVWm = 2._dp*AmpVertexHmToVZVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHmOS(gt1),MVZOS,MVWmOS,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(MHm(gt1),MVZ,MVWm,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqHmToVZVWm(gt1) 
  AmpSum2HmToVZVWm = AmpTreeHmToVZVWm + 2._dp*AmpWaveHmToVZVWm + 2._dp*AmpVertexHmToVZVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHmOS(gt1),MVZOS,MVWmOS,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(MHm(gt1),MVZ,MVWm,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqHmToVZVWm(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2HmToVZVWm = AmpTreeHmToVZVWm
  Call SquareAmp_StoVV(MHmOS(gt1),MVZOS,MVWmOS,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
  AmpSqTreeHmToVZVWm(gt1) = AmpSqHmToVZVWm(gt1)  
  AmpSum2HmToVZVWm = + 2._dp*AmpWaveHmToVZVWm + 2._dp*AmpVertexHmToVZVWm
  Call SquareAmp_StoVV(MHmOS(gt1),MVZOS,MVWmOS,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
  AmpSqHmToVZVWm(gt1) = AmpSqHmToVZVWm(gt1) + AmpSqTreeHmToVZVWm(gt1)  
Else  
  AmpSum2HmToVZVWm = AmpTreeHmToVZVWm
  Call SquareAmp_StoVV(MHm(gt1),MVZ,MVWm,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
  AmpSqTreeHmToVZVWm(gt1) = AmpSqHmToVZVWm(gt1)  
  AmpSum2HmToVZVWm = + 2._dp*AmpWaveHmToVZVWm + 2._dp*AmpVertexHmToVZVWm
  Call SquareAmp_StoVV(MHm(gt1),MVZ,MVWm,AmpSumHmToVZVWm(:,gt1),AmpSum2HmToVZVWm(:,gt1),AmpSqHmToVZVWm(gt1)) 
  AmpSqHmToVZVWm(gt1) = AmpSqHmToVZVWm(gt1) + AmpSqTreeHmToVZVWm(gt1)  
End if  
Else  
  AmpSqHmToVZVWm(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToVZVWm(gt1).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 2._dp*GammaTPS(MHmOS(gt1),MVZOS,MVWmOS,helfactor*AmpSqHmToVZVWm(gt1))
Else 
  gP1LHm(gt1,i4) = 2._dp*GammaTPS(MHm(gt1),MVZ,MVWm,helfactor*AmpSqHmToVZVWm(gt1))
End if 
If ((Abs(MRPHmToVZVWm(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHmToVZVWm(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPHmToVZVWm(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHmToVZVWm(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPHmToVZVWm(gt1) + MRGHmToVZVWm(gt1)) 
  gP1LHm(gt1,i4) = gP1LHm(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPHmToVZVWm(gt1) + MRGHmToVZVWm(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LHm(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
!---------------- 
! Hm VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_HmToHmVP(cplHmcHmVP,cplHmcHmVZ,ctcplHmcHmVP,            & 
& ctcplHmcHmVZ,MHmOS,MHm2OS,MVP,MVP2,ZfHm,ZfVP,ZfVZVP,AmpWaveHmToHmVP)

 Else 
Call Amplitude_WAVE_gumTHDMII_HmToHmVP(cplHmcHmVP,cplHmcHmVZ,ctcplHmcHmVP,            & 
& ctcplHmcHmVZ,MHmOS,MHm2OS,MVP,MVP2,ZfHm,ZfVP,ZfVZVP,AmpWaveHmToHmVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_HmToHmVP(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,        & 
& cplcFuFdcHmR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,            & 
& cplcFdFuHmR,cplcFuFuVPL,cplcFuFuVPR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmVP,              & 
& cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVP,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,         & 
& cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,     & 
& cplcVWmVPVWm,cplcHmVWmVZ,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,  & 
& cplHmcHmVPVP1,cplHmcHmVPVZ1,AmpVertexHmToHmVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_HmToHmVP(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,        & 
& cplcFuFdcHmR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,            & 
& cplcFdFuHmR,cplcFuFuVPL,cplcFuFuVPR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmVP,              & 
& cplcgZgWmcHm,cplcgZgWpCHm,cplcgWpCgWpCVP,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,         & 
& cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,     & 
& cplcVWmVPVWm,cplcHmVWmVZ,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,  & 
& cplHmcHmVPVP1,cplHmcHmVPVZ1,AmpVertexHmToHmVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToHmVP(cplHmcHmVP,cplHmcHmVZ,ctcplHmcHmVP,            & 
& ctcplHmcHmVZ,MHm,MHm2,MVP,MVP2,ZfHm,ZfVP,ZfVZVP,AmpWaveHmToHmVP)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToHmVP(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,            & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhHmcHm,cplAhHmcVWm,              & 
& cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVPL,             & 
& cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmVP,cplcgZgWmcHm,cplcgZgWpCHm,            & 
& cplcgWpCgWpCVP,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,           & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,    & 
& cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,cplHmcHmVPVP1,             & 
& cplHmcHmVPVZ1,AmpVertexHmToHmVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->Hm VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToHmVP = 0._dp 
 AmpSum2HmToHmVP = 0._dp  
Else 
 AmpSumHmToHmVP = AmpVertexHmToHmVP + AmpWaveHmToHmVP
 AmpSum2HmToHmVP = AmpVertexHmToHmVP + AmpWaveHmToHmVP 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MHm(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MHmOS(gt1),MHmOS(gt2),0._dp,AmpSumHmToHmVP(:,gt1, gt2),AmpSum2HmToHmVP(:,gt1, gt2),AmpSqHmToHmVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MHm(gt1),MHm(gt2),MVP,AmpSumHmToHmVP(:,gt1, gt2),AmpSum2HmToHmVP(:,gt1, gt2),AmpSqHmToHmVP(gt1, gt2)) 
End if  
Else  
  AmpSqHmToHmVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToHmVP(gt1, gt2).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHmOS(gt1),MHmOS(gt2),0._dp,helfactor*AmpSqHmToHmVP(gt1, gt2))
Else 
  gP1LHm(gt1,i4) = 1._dp*GammaTPS(MHm(gt1),MHm(gt2),MVP,helfactor*AmpSqHmToHmVP(gt1, gt2))
End if 
If ((Abs(MRPHmToHmVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGHmToHmVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VP VWm
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_HmToVPVWm(cplcHmVPVWm,cplcHmVWmVZ,ctcplcHmVPVWm,        & 
& ctcplcHmVWmVZ,MHmOS,MHm2OS,MVP,MVP2,MVWmOS,MVWm2OS,ZfHm,ZfVP,ZfVWm,AmpWaveHmToVPVWm)

 Else 
Call Amplitude_WAVE_gumTHDMII_HmToVPVWm(cplcHmVPVWm,cplcHmVWmVZ,ctcplcHmVPVWm,        & 
& ctcplcHmVWmVZ,MHmOS,MHm2OS,MVP,MVP2,MVWmOS,MVWm2OS,ZfHm,ZfVP,ZfVWm,AmpWaveHmToVPVWm)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_HmToVPVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,              & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhHmcHm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,       & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,cplcgWmgWmVP,        & 
& cplcgZgWmcHm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcHm,    & 
& cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplcHmVPVWm,     & 
& cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVPVWm1,cplhhcHmVPVWm1,cplHmcHmVPVP1,     & 
& cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,     & 
& cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexHmToVPVWm)

 Else 
Call Amplitude_VERTEX_gumTHDMII_HmToVPVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,              & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhHmcHm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,       & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,cplcgWmgWmVP,        & 
& cplcgZgWmcHm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcHm,    & 
& cplhhHmcHm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplcHmVPVWm,     & 
& cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVPVWm1,cplhhcHmVPVWm1,cplHmcHmVPVP1,     & 
& cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,     & 
& cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexHmToVPVWm)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_HmToVPVWm(cplcHmVPVWm,cplcHmVWmVZ,ctcplcHmVPVWm,        & 
& ctcplcHmVWmVZ,MHm,MHm2,MVP,MVP2,MVWm,MVWm2,ZfHm,ZfVP,ZfVWm,AmpWaveHmToVPVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_HmToVPVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhHmcHm,cplAhcHmVWm,              & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFeVPL,cplcFeFeVPR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcgWpCgAcHm,cplcgWmgWmVP,cplcgZgWmcHm,cplcgWpCgWpCVP,      & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcHm,cplhhHmcHm,cplhhcHmVWm,         & 
& cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplcHmVPVWm,cplcVWmVPVWm,               & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhcHmVPVWm1,cplhhcHmVPVWm1,cplHmcHmVPVP1,cplHmcHmVPVZ1,    & 
& cplHmcHmcVWmVWm1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVWmVZ3Q,  & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexHmToVPVWm)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Hm->VP VWm -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumHmToVPVWm = 0._dp 
 AmpSum2HmToVPVWm = 0._dp  
Else 
 AmpSumHmToVPVWm = AmpVertexHmToVPVWm + AmpWaveHmToVPVWm
 AmpSum2HmToVPVWm = AmpVertexHmToVPVWm + AmpWaveHmToVPVWm 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MHmOS(gt1)).gt.(Abs(0.)+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MHm(gt1)).gt.(Abs(MVP)+Abs(MVWm))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MHmOS(gt1),0._dp,MVWmOS,AmpSumHmToVPVWm(:,gt1),AmpSum2HmToVPVWm(:,gt1),AmpSqHmToVPVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(MHm(gt1),MVP,MVWm,AmpSumHmToVPVWm(:,gt1),AmpSum2HmToVPVWm(:,gt1),AmpSqHmToVPVWm(gt1)) 
End if  
Else  
  AmpSqHmToVPVWm(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqHmToVPVWm(gt1).eq.0._dp) Then 
  gP1LHm(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LHm(gt1,i4) = 2._dp*GammaTPS(MHmOS(gt1),0._dp,MVWmOS,helfactor*AmpSqHmToVPVWm(gt1))
Else 
  gP1LHm(gt1,i4) = 2._dp*GammaTPS(MHm(gt1),MVP,MVWm,helfactor*AmpSqHmToVPVWm(gt1))
End if 
If ((Abs(MRPHmToVPVWm(gt1)).gt.1.0E-20_dp).or.(Abs(MRGHmToVPVWm(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LHm(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End Subroutine OneLoopDecay_Hm

End Module Wrapper_OneLoopDecay_Hm_gumTHDMII
