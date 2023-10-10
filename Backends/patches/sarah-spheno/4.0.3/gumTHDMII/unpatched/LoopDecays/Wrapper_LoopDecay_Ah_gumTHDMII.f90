! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Ah_gumTHDMII
Use Model_Data_gumTHDMII 
Use Kinematics 
Use OneLoopDecay_Ah_gumTHDMII 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Ah(MhhOS,Mhh2OS,MAhOS,MAh2OS,MHmOS,MHm2OS,MFdOS,              & 
& MFd2OS,MFuOS,MFu2OS,MFeOS,MFe2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS,ZAOS,ZPOS,           & 
& ZDLOS,ZDROS,ZULOS,ZUROS,ZELOS,ZEROS,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,               & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,              & 
& ZP,ZW,ZZ,alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,            & 
& m222,vd,vu,dg1,dg2,dg3,dm122,dYu,dYd,dYe,dlam5,dm112,dm222,dlam1,dlam4,dlam3,          & 
& dlam2,dvd,dvu,dZH,dZA,dZP,dZDL,dZDR,dZUL,dZUR,dZEL,dZER,dSinTW,dCosTW,dTanTW,          & 
& ZfVG,ZfvL,ZfVP,ZfVZ,ZfVWm,Zfhh,ZfAh,ZfHm,ZfDL,ZfDR,ZfUL,ZfUR,ZfEL,ZfER,ZfVPVZ,         & 
& ZfVZVP,cplAhAhAh,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhcVWmVWm1,cplAhAhhh,cplAhAhhhhh1,     & 
& cplAhAhHmcHm1,cplAhAhVZVZ1,cplAhcHmVPVWm1,cplAhcHmVWm,cplAhcHmVWmVZ1,cplAhhhhh,        & 
& cplAhhhhhhh1,cplAhhhHmcHm1,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhHmcVWmVP1,            & 
& cplAhHmcVWmVZ1,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHm,      & 
& cplcgWmgAVWm,cplcgWmgWmAh,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHm,          & 
& cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP,              & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHm,cplcgWpCgZcVWm,cplcgZgWmcHm,cplcgZgWmcVWm,cplcgZgWpCHm,   & 
& cplcgZgWpCVWm,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVPVWm1,        & 
& cplhhcHmVWm,cplhhcHmVWmVZ1,cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhhhhh1,        & 
& cplhhhhHmcHm1,cplhhhhVZVZ1,cplhhHmcHm,cplhhHmcVWm,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,       & 
& cplhhVZVZ,cplHmcHmcVWmVWm1,cplHmcHmVP,cplHmcHmVPVP1,cplHmcHmVPVZ1,cplHmcHmVZ,          & 
& cplHmcHmVZVZ1,cplHmcVWmVP,cplHmcVWmVZ,cplHmHmcHmcHm1,ctcplAhAhAh,ctcplAhAhhh,          & 
& ctcplAhhhhh,ctcplAhhhVZ,ctcplAhHmcHm,ctcplAhHmcVWm,ctcplcFdFdAhL,ctcplcFdFdAhR,        & 
& ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,GcplAhHmcHm,GcplcHmVPVWm,      & 
& GcplHmcVWmVP,GosZcplAhHmcHm,GosZcplcHmVPVWm,GosZcplHmcVWmVP,GZcplAhHmcHm,              & 
& GZcplcHmVPVWm,GZcplHmcVWmVP,ZcplAhAhAh,ZcplAhAhhh,ZcplAhhhhh,ZcplAhhhVZ,               & 
& ZcplAhHmcHm,ZcplAhHmcVWm,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFeFeAhL,ZcplcFeFeAhR,          & 
& ZcplcFuFuAhL,ZcplcFuFuAhR,ZRUZH,ZRUZA,ZRUZP,ZRUVd,ZRUUd,ZRUVu,ZRUUu,ZRUVe,             & 
& ZRUUe,MLambda,em,gs,deltaM,kont,gP1LAh)

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

Complex(dp),Intent(in) :: cplAhAhAh(2,2,2),cplAhAhAhAh1(2,2,2,2),cplAhAhAhhh1(2,2,2,2),cplAhAhcVWmVWm1(2,2),    & 
& cplAhAhhh(2,2,2),cplAhAhhhhh1(2,2,2,2),cplAhAhHmcHm1(2,2,2,2),cplAhAhVZVZ1(2,2),       & 
& cplAhcHmVPVWm1(2,2),cplAhcHmVWm(2,2),cplAhcHmVWmVZ1(2,2),cplAhhhhh(2,2,2),             & 
& cplAhhhhhhh1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),         & 
& cplAhHmcVWm(2,2),cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2),cplcFdFdAhL(3,3,2),           & 
& cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVGL(3,3),             & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),             & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),           & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHmL(3,3,2),& 
& cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFuFdcHmL(3,3,2),            & 
& cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),          & 
& cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),         & 
& cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHm(2),cplcgWmgAVWm,cplcgWmgWmAh(2),               & 
& cplcgWmgWmhh(2),cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHm(2),cplcgWmgZVWm,cplcgWpCgAcVWm,  & 
& cplcgWpCgWpCAh(2),cplcgWpCgWpChh(2),cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcgWpCgZcHm(2),    & 
& cplcgWpCgZcVWm,cplcgZgWmcHm(2),cplcgZgWmcVWm,cplcgZgWpCHm(2),cplcgZgWpCVWm,            & 
& cplcHmVPVWm(2),cplcHmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVPVWm1(2,2),           & 
& cplhhcHmVWm(2,2),cplhhcHmVWmVZ1(2,2),cplhhcVWmVWm(2),cplhhhhcVWmVWm1(2,2),             & 
& cplhhhhhh(2,2,2),cplhhhhhhhh1(2,2,2,2),cplhhhhHmcHm1(2,2,2,2),cplhhhhVZVZ1(2,2),       & 
& cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhHmcVWmVP1(2,2),cplhhHmcVWmVZ1(2,2),            & 
& cplhhVZVZ(2),cplHmcHmcVWmVWm1(2,2),cplHmcHmVP(2,2),cplHmcHmVPVP1(2,2),cplHmcHmVPVZ1(2,2),& 
& cplHmcHmVZ(2,2),cplHmcHmVZVZ1(2,2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplHmHmcHmcHm1(2,2,2,2),& 
& ctcplAhAhAh(2,2,2),ctcplAhAhhh(2,2,2),ctcplAhhhhh(2,2,2),ctcplAhhhVZ(2,2),             & 
& ctcplAhHmcHm(2,2,2),ctcplAhHmcVWm(2,2),ctcplcFdFdAhL(3,3,2),ctcplcFdFdAhR(3,3,2),      & 
& ctcplcFeFeAhL(3,3,2),ctcplcFeFeAhR(3,3,2),ctcplcFuFuAhL(3,3,2),ctcplcFuFuAhR(3,3,2),   & 
& GcplAhHmcHm(2,2,2),GcplcHmVPVWm(2),GcplHmcVWmVP(2),GosZcplAhHmcHm(2,2,2),              & 
& GosZcplcHmVPVWm(2),GosZcplHmcVWmVP(2),GZcplAhHmcHm(2,2,2),GZcplcHmVPVWm(2),            & 
& GZcplHmcVWmVP(2),ZcplAhAhAh(2,2,2),ZcplAhAhhh(2,2,2),ZcplAhhhhh(2,2,2),ZcplAhhhVZ(2,2),& 
& ZcplAhHmcHm(2,2,2),ZcplAhHmcVWm(2,2),ZcplcFdFdAhL(3,3,2),ZcplcFdFdAhR(3,3,2),          & 
& ZcplcFeFeAhL(3,3,2),ZcplcFeFeAhR(3,3,2),ZcplcFuFuAhL(3,3,2),ZcplcFuFuAhR(3,3,2)

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
Real(dp), Intent(out) :: gP1LAh(2,57) 
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
Real(dp) :: MRPAhToAhAh(2,2,2),MRGAhToAhAh(2,2,2), MRPZAhToAhAh(2,2,2),MRGZAhToAhAh(2,2,2) 
Real(dp) :: MVPAhToAhAh(2,2,2) 
Real(dp) :: RMsqTreeAhToAhAh(2,2,2),RMsqWaveAhToAhAh(2,2,2),RMsqVertexAhToAhAh(2,2,2) 
Complex(dp) :: AmpTreeAhToAhAh(2,2,2),AmpWaveAhToAhAh(2,2,2)=(0._dp,0._dp),AmpVertexAhToAhAh(2,2,2)& 
 & ,AmpVertexIRosAhToAhAh(2,2,2),AmpVertexIRdrAhToAhAh(2,2,2), AmpSumAhToAhAh(2,2,2), AmpSum2AhToAhAh(2,2,2) 
Complex(dp) :: AmpTreeZAhToAhAh(2,2,2),AmpWaveZAhToAhAh(2,2,2),AmpVertexZAhToAhAh(2,2,2) 
Real(dp) :: AmpSqAhToAhAh(2,2,2),  AmpSqTreeAhToAhAh(2,2,2) 
Real(dp) :: MRPAhTohhAh(2,2,2),MRGAhTohhAh(2,2,2), MRPZAhTohhAh(2,2,2),MRGZAhTohhAh(2,2,2) 
Real(dp) :: MVPAhTohhAh(2,2,2) 
Real(dp) :: RMsqTreeAhTohhAh(2,2,2),RMsqWaveAhTohhAh(2,2,2),RMsqVertexAhTohhAh(2,2,2) 
Complex(dp) :: AmpTreeAhTohhAh(2,2,2),AmpWaveAhTohhAh(2,2,2)=(0._dp,0._dp),AmpVertexAhTohhAh(2,2,2)& 
 & ,AmpVertexIRosAhTohhAh(2,2,2),AmpVertexIRdrAhTohhAh(2,2,2), AmpSumAhTohhAh(2,2,2), AmpSum2AhTohhAh(2,2,2) 
Complex(dp) :: AmpTreeZAhTohhAh(2,2,2),AmpWaveZAhTohhAh(2,2,2),AmpVertexZAhTohhAh(2,2,2) 
Real(dp) :: AmpSqAhTohhAh(2,2,2),  AmpSqTreeAhTohhAh(2,2,2) 
Real(dp) :: MRPAhTocFdFd(2,3,3),MRGAhTocFdFd(2,3,3), MRPZAhTocFdFd(2,3,3),MRGZAhTocFdFd(2,3,3) 
Real(dp) :: MVPAhTocFdFd(2,3,3) 
Real(dp) :: RMsqTreeAhTocFdFd(2,3,3),RMsqWaveAhTocFdFd(2,3,3),RMsqVertexAhTocFdFd(2,3,3) 
Complex(dp) :: AmpTreeAhTocFdFd(2,2,3,3),AmpWaveAhTocFdFd(2,2,3,3)=(0._dp,0._dp),AmpVertexAhTocFdFd(2,2,3,3)& 
 & ,AmpVertexIRosAhTocFdFd(2,2,3,3),AmpVertexIRdrAhTocFdFd(2,2,3,3), AmpSumAhTocFdFd(2,2,3,3), AmpSum2AhTocFdFd(2,2,3,3) 
Complex(dp) :: AmpTreeZAhTocFdFd(2,2,3,3),AmpWaveZAhTocFdFd(2,2,3,3),AmpVertexZAhTocFdFd(2,2,3,3) 
Real(dp) :: AmpSqAhTocFdFd(2,3,3),  AmpSqTreeAhTocFdFd(2,3,3) 
Real(dp) :: MRPAhTocFeFe(2,3,3),MRGAhTocFeFe(2,3,3), MRPZAhTocFeFe(2,3,3),MRGZAhTocFeFe(2,3,3) 
Real(dp) :: MVPAhTocFeFe(2,3,3) 
Real(dp) :: RMsqTreeAhTocFeFe(2,3,3),RMsqWaveAhTocFeFe(2,3,3),RMsqVertexAhTocFeFe(2,3,3) 
Complex(dp) :: AmpTreeAhTocFeFe(2,2,3,3),AmpWaveAhTocFeFe(2,2,3,3)=(0._dp,0._dp),AmpVertexAhTocFeFe(2,2,3,3)& 
 & ,AmpVertexIRosAhTocFeFe(2,2,3,3),AmpVertexIRdrAhTocFeFe(2,2,3,3), AmpSumAhTocFeFe(2,2,3,3), AmpSum2AhTocFeFe(2,2,3,3) 
Complex(dp) :: AmpTreeZAhTocFeFe(2,2,3,3),AmpWaveZAhTocFeFe(2,2,3,3),AmpVertexZAhTocFeFe(2,2,3,3) 
Real(dp) :: AmpSqAhTocFeFe(2,3,3),  AmpSqTreeAhTocFeFe(2,3,3) 
Real(dp) :: MRPAhTocFuFu(2,3,3),MRGAhTocFuFu(2,3,3), MRPZAhTocFuFu(2,3,3),MRGZAhTocFuFu(2,3,3) 
Real(dp) :: MVPAhTocFuFu(2,3,3) 
Real(dp) :: RMsqTreeAhTocFuFu(2,3,3),RMsqWaveAhTocFuFu(2,3,3),RMsqVertexAhTocFuFu(2,3,3) 
Complex(dp) :: AmpTreeAhTocFuFu(2,2,3,3),AmpWaveAhTocFuFu(2,2,3,3)=(0._dp,0._dp),AmpVertexAhTocFuFu(2,2,3,3)& 
 & ,AmpVertexIRosAhTocFuFu(2,2,3,3),AmpVertexIRdrAhTocFuFu(2,2,3,3), AmpSumAhTocFuFu(2,2,3,3), AmpSum2AhTocFuFu(2,2,3,3) 
Complex(dp) :: AmpTreeZAhTocFuFu(2,2,3,3),AmpWaveZAhTocFuFu(2,2,3,3),AmpVertexZAhTocFuFu(2,2,3,3) 
Real(dp) :: AmpSqAhTocFuFu(2,3,3),  AmpSqTreeAhTocFuFu(2,3,3) 
Real(dp) :: MRPAhTohhhh(2,2,2),MRGAhTohhhh(2,2,2), MRPZAhTohhhh(2,2,2),MRGZAhTohhhh(2,2,2) 
Real(dp) :: MVPAhTohhhh(2,2,2) 
Real(dp) :: RMsqTreeAhTohhhh(2,2,2),RMsqWaveAhTohhhh(2,2,2),RMsqVertexAhTohhhh(2,2,2) 
Complex(dp) :: AmpTreeAhTohhhh(2,2,2),AmpWaveAhTohhhh(2,2,2)=(0._dp,0._dp),AmpVertexAhTohhhh(2,2,2)& 
 & ,AmpVertexIRosAhTohhhh(2,2,2),AmpVertexIRdrAhTohhhh(2,2,2), AmpSumAhTohhhh(2,2,2), AmpSum2AhTohhhh(2,2,2) 
Complex(dp) :: AmpTreeZAhTohhhh(2,2,2),AmpWaveZAhTohhhh(2,2,2),AmpVertexZAhTohhhh(2,2,2) 
Real(dp) :: AmpSqAhTohhhh(2,2,2),  AmpSqTreeAhTohhhh(2,2,2) 
Real(dp) :: MRPAhTohhVZ(2,2),MRGAhTohhVZ(2,2), MRPZAhTohhVZ(2,2),MRGZAhTohhVZ(2,2) 
Real(dp) :: MVPAhTohhVZ(2,2) 
Real(dp) :: RMsqTreeAhTohhVZ(2,2),RMsqWaveAhTohhVZ(2,2),RMsqVertexAhTohhVZ(2,2) 
Complex(dp) :: AmpTreeAhTohhVZ(2,2,2),AmpWaveAhTohhVZ(2,2,2)=(0._dp,0._dp),AmpVertexAhTohhVZ(2,2,2)& 
 & ,AmpVertexIRosAhTohhVZ(2,2,2),AmpVertexIRdrAhTohhVZ(2,2,2), AmpSumAhTohhVZ(2,2,2), AmpSum2AhTohhVZ(2,2,2) 
Complex(dp) :: AmpTreeZAhTohhVZ(2,2,2),AmpWaveZAhTohhVZ(2,2,2),AmpVertexZAhTohhVZ(2,2,2) 
Real(dp) :: AmpSqAhTohhVZ(2,2),  AmpSqTreeAhTohhVZ(2,2) 
Real(dp) :: MRPAhTocHmHm(2,2,2),MRGAhTocHmHm(2,2,2), MRPZAhTocHmHm(2,2,2),MRGZAhTocHmHm(2,2,2) 
Real(dp) :: MVPAhTocHmHm(2,2,2) 
Real(dp) :: RMsqTreeAhTocHmHm(2,2,2),RMsqWaveAhTocHmHm(2,2,2),RMsqVertexAhTocHmHm(2,2,2) 
Complex(dp) :: AmpTreeAhTocHmHm(2,2,2),AmpWaveAhTocHmHm(2,2,2)=(0._dp,0._dp),AmpVertexAhTocHmHm(2,2,2)& 
 & ,AmpVertexIRosAhTocHmHm(2,2,2),AmpVertexIRdrAhTocHmHm(2,2,2), AmpSumAhTocHmHm(2,2,2), AmpSum2AhTocHmHm(2,2,2) 
Complex(dp) :: AmpTreeZAhTocHmHm(2,2,2),AmpWaveZAhTocHmHm(2,2,2),AmpVertexZAhTocHmHm(2,2,2) 
Real(dp) :: AmpSqAhTocHmHm(2,2,2),  AmpSqTreeAhTocHmHm(2,2,2) 
Real(dp) :: MRPAhToHmcVWm(2,2),MRGAhToHmcVWm(2,2), MRPZAhToHmcVWm(2,2),MRGZAhToHmcVWm(2,2) 
Real(dp) :: MVPAhToHmcVWm(2,2) 
Real(dp) :: RMsqTreeAhToHmcVWm(2,2),RMsqWaveAhToHmcVWm(2,2),RMsqVertexAhToHmcVWm(2,2) 
Complex(dp) :: AmpTreeAhToHmcVWm(2,2,2),AmpWaveAhToHmcVWm(2,2,2)=(0._dp,0._dp),AmpVertexAhToHmcVWm(2,2,2)& 
 & ,AmpVertexIRosAhToHmcVWm(2,2,2),AmpVertexIRdrAhToHmcVWm(2,2,2), AmpSumAhToHmcVWm(2,2,2), AmpSum2AhToHmcVWm(2,2,2) 
Complex(dp) :: AmpTreeZAhToHmcVWm(2,2,2),AmpWaveZAhToHmcVWm(2,2,2),AmpVertexZAhToHmcVWm(2,2,2) 
Real(dp) :: AmpSqAhToHmcVWm(2,2),  AmpSqTreeAhToHmcVWm(2,2) 
Real(dp) :: MRPAhToAhVP(2,2),MRGAhToAhVP(2,2), MRPZAhToAhVP(2,2),MRGZAhToAhVP(2,2) 
Real(dp) :: MVPAhToAhVP(2,2) 
Real(dp) :: RMsqTreeAhToAhVP(2,2),RMsqWaveAhToAhVP(2,2),RMsqVertexAhToAhVP(2,2) 
Complex(dp) :: AmpTreeAhToAhVP(2,2,2),AmpWaveAhToAhVP(2,2,2)=(0._dp,0._dp),AmpVertexAhToAhVP(2,2,2)& 
 & ,AmpVertexIRosAhToAhVP(2,2,2),AmpVertexIRdrAhToAhVP(2,2,2), AmpSumAhToAhVP(2,2,2), AmpSum2AhToAhVP(2,2,2) 
Complex(dp) :: AmpTreeZAhToAhVP(2,2,2),AmpWaveZAhToAhVP(2,2,2),AmpVertexZAhToAhVP(2,2,2) 
Real(dp) :: AmpSqAhToAhVP(2,2),  AmpSqTreeAhToAhVP(2,2) 
Real(dp) :: MRPAhToAhVZ(2,2),MRGAhToAhVZ(2,2), MRPZAhToAhVZ(2,2),MRGZAhToAhVZ(2,2) 
Real(dp) :: MVPAhToAhVZ(2,2) 
Real(dp) :: RMsqTreeAhToAhVZ(2,2),RMsqWaveAhToAhVZ(2,2),RMsqVertexAhToAhVZ(2,2) 
Complex(dp) :: AmpTreeAhToAhVZ(2,2,2),AmpWaveAhToAhVZ(2,2,2)=(0._dp,0._dp),AmpVertexAhToAhVZ(2,2,2)& 
 & ,AmpVertexIRosAhToAhVZ(2,2,2),AmpVertexIRdrAhToAhVZ(2,2,2), AmpSumAhToAhVZ(2,2,2), AmpSum2AhToAhVZ(2,2,2) 
Complex(dp) :: AmpTreeZAhToAhVZ(2,2,2),AmpWaveZAhToAhVZ(2,2,2),AmpVertexZAhToAhVZ(2,2,2) 
Real(dp) :: AmpSqAhToAhVZ(2,2),  AmpSqTreeAhToAhVZ(2,2) 
Real(dp) :: MRPAhToFvcFv(2,3,3),MRGAhToFvcFv(2,3,3), MRPZAhToFvcFv(2,3,3),MRGZAhToFvcFv(2,3,3) 
Real(dp) :: MVPAhToFvcFv(2,3,3) 
Real(dp) :: RMsqTreeAhToFvcFv(2,3,3),RMsqWaveAhToFvcFv(2,3,3),RMsqVertexAhToFvcFv(2,3,3) 
Complex(dp) :: AmpTreeAhToFvcFv(2,2,3,3),AmpWaveAhToFvcFv(2,2,3,3)=(0._dp,0._dp),AmpVertexAhToFvcFv(2,2,3,3)& 
 & ,AmpVertexIRosAhToFvcFv(2,2,3,3),AmpVertexIRdrAhToFvcFv(2,2,3,3), AmpSumAhToFvcFv(2,2,3,3), AmpSum2AhToFvcFv(2,2,3,3) 
Complex(dp) :: AmpTreeZAhToFvcFv(2,2,3,3),AmpWaveZAhToFvcFv(2,2,3,3),AmpVertexZAhToFvcFv(2,2,3,3) 
Real(dp) :: AmpSqAhToFvcFv(2,3,3),  AmpSqTreeAhToFvcFv(2,3,3) 
Real(dp) :: MRPAhTohhVP(2,2),MRGAhTohhVP(2,2), MRPZAhTohhVP(2,2),MRGZAhTohhVP(2,2) 
Real(dp) :: MVPAhTohhVP(2,2) 
Real(dp) :: RMsqTreeAhTohhVP(2,2),RMsqWaveAhTohhVP(2,2),RMsqVertexAhTohhVP(2,2) 
Complex(dp) :: AmpTreeAhTohhVP(2,2,2),AmpWaveAhTohhVP(2,2,2)=(0._dp,0._dp),AmpVertexAhTohhVP(2,2,2)& 
 & ,AmpVertexIRosAhTohhVP(2,2,2),AmpVertexIRdrAhTohhVP(2,2,2), AmpSumAhTohhVP(2,2,2), AmpSum2AhTohhVP(2,2,2) 
Complex(dp) :: AmpTreeZAhTohhVP(2,2,2),AmpWaveZAhTohhVP(2,2,2),AmpVertexZAhTohhVP(2,2,2) 
Real(dp) :: AmpSqAhTohhVP(2,2),  AmpSqTreeAhTohhVP(2,2) 
Real(dp) :: MRPAhToVGVG(2),MRGAhToVGVG(2), MRPZAhToVGVG(2),MRGZAhToVGVG(2) 
Real(dp) :: MVPAhToVGVG(2) 
Real(dp) :: RMsqTreeAhToVGVG(2),RMsqWaveAhToVGVG(2),RMsqVertexAhToVGVG(2) 
Complex(dp) :: AmpTreeAhToVGVG(2,2),AmpWaveAhToVGVG(2,2)=(0._dp,0._dp),AmpVertexAhToVGVG(2,2)& 
 & ,AmpVertexIRosAhToVGVG(2,2),AmpVertexIRdrAhToVGVG(2,2), AmpSumAhToVGVG(2,2), AmpSum2AhToVGVG(2,2) 
Complex(dp) :: AmpTreeZAhToVGVG(2,2),AmpWaveZAhToVGVG(2,2),AmpVertexZAhToVGVG(2,2) 
Real(dp) :: AmpSqAhToVGVG(2),  AmpSqTreeAhToVGVG(2) 
Real(dp) :: MRPAhToVPVP(2),MRGAhToVPVP(2), MRPZAhToVPVP(2),MRGZAhToVPVP(2) 
Real(dp) :: MVPAhToVPVP(2) 
Real(dp) :: RMsqTreeAhToVPVP(2),RMsqWaveAhToVPVP(2),RMsqVertexAhToVPVP(2) 
Complex(dp) :: AmpTreeAhToVPVP(2,2),AmpWaveAhToVPVP(2,2)=(0._dp,0._dp),AmpVertexAhToVPVP(2,2)& 
 & ,AmpVertexIRosAhToVPVP(2,2),AmpVertexIRdrAhToVPVP(2,2), AmpSumAhToVPVP(2,2), AmpSum2AhToVPVP(2,2) 
Complex(dp) :: AmpTreeZAhToVPVP(2,2),AmpWaveZAhToVPVP(2,2),AmpVertexZAhToVPVP(2,2) 
Real(dp) :: AmpSqAhToVPVP(2),  AmpSqTreeAhToVPVP(2) 
Real(dp) :: MRPAhToVPVZ(2),MRGAhToVPVZ(2), MRPZAhToVPVZ(2),MRGZAhToVPVZ(2) 
Real(dp) :: MVPAhToVPVZ(2) 
Real(dp) :: RMsqTreeAhToVPVZ(2),RMsqWaveAhToVPVZ(2),RMsqVertexAhToVPVZ(2) 
Complex(dp) :: AmpTreeAhToVPVZ(2,2),AmpWaveAhToVPVZ(2,2)=(0._dp,0._dp),AmpVertexAhToVPVZ(2,2)& 
 & ,AmpVertexIRosAhToVPVZ(2,2),AmpVertexIRdrAhToVPVZ(2,2), AmpSumAhToVPVZ(2,2), AmpSum2AhToVPVZ(2,2) 
Complex(dp) :: AmpTreeZAhToVPVZ(2,2),AmpWaveZAhToVPVZ(2,2),AmpVertexZAhToVPVZ(2,2) 
Real(dp) :: AmpSqAhToVPVZ(2),  AmpSqTreeAhToVPVZ(2) 
Real(dp) :: MRPAhToVWmcVWm(2),MRGAhToVWmcVWm(2), MRPZAhToVWmcVWm(2),MRGZAhToVWmcVWm(2) 
Real(dp) :: MVPAhToVWmcVWm(2) 
Real(dp) :: RMsqTreeAhToVWmcVWm(2),RMsqWaveAhToVWmcVWm(2),RMsqVertexAhToVWmcVWm(2) 
Complex(dp) :: AmpTreeAhToVWmcVWm(2,2),AmpWaveAhToVWmcVWm(2,2)=(0._dp,0._dp),AmpVertexAhToVWmcVWm(2,2)& 
 & ,AmpVertexIRosAhToVWmcVWm(2,2),AmpVertexIRdrAhToVWmcVWm(2,2), AmpSumAhToVWmcVWm(2,2), AmpSum2AhToVWmcVWm(2,2) 
Complex(dp) :: AmpTreeZAhToVWmcVWm(2,2),AmpWaveZAhToVWmcVWm(2,2),AmpVertexZAhToVWmcVWm(2,2) 
Real(dp) :: AmpSqAhToVWmcVWm(2),  AmpSqTreeAhToVWmcVWm(2) 
Real(dp) :: MRPAhToVZVZ(2),MRGAhToVZVZ(2), MRPZAhToVZVZ(2),MRGZAhToVZVZ(2) 
Real(dp) :: MVPAhToVZVZ(2) 
Real(dp) :: RMsqTreeAhToVZVZ(2),RMsqWaveAhToVZVZ(2),RMsqVertexAhToVZVZ(2) 
Complex(dp) :: AmpTreeAhToVZVZ(2,2),AmpWaveAhToVZVZ(2,2)=(0._dp,0._dp),AmpVertexAhToVZVZ(2,2)& 
 & ,AmpVertexIRosAhToVZVZ(2,2),AmpVertexIRdrAhToVZVZ(2,2), AmpSumAhToVZVZ(2,2), AmpSum2AhToVZVZ(2,2) 
Complex(dp) :: AmpTreeZAhToVZVZ(2,2),AmpWaveZAhToVZVZ(2,2),AmpVertexZAhToVZVZ(2,2) 
Real(dp) :: AmpSqAhToVZVZ(2),  AmpSqTreeAhToVZVZ(2) 
Write(*,*) "Calculating one-loop decays of Ah " 
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
isave = 3

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Ah Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhToAhAh(cplAhAhAh,MAh,MAh2,AmpTreeAhToAhAh)

  Else 
Call Amplitude_Tree_gumTHDMII_AhToAhAh(ZcplAhAhAh,MAh,MAh2,AmpTreeAhToAhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhToAhAh(MLambda,em,gs,cplAhAhAh,MAhOS,MRPAhToAhAh,         & 
& MRGAhToAhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhToAhAh(MLambda,em,gs,ZcplAhAhAh,MAhOS,MRPAhToAhAh,        & 
& MRGAhToAhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhToAhAh(MLambda,em,gs,cplAhAhAh,MAh,MRPAhToAhAh,           & 
& MRGAhToAhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhToAhAh(MLambda,em,gs,ZcplAhAhAh,MAh,MRPAhToAhAh,          & 
& MRGAhToAhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhToAhAh(cplAhAhAh,ctcplAhAhAh,MAh,MAh2,ZfAh,           & 
& AmpWaveAhToAhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplAhAhAhAh1,    & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,AmpVertexAhToAhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplAhAhAhAh1,    & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,AmpVertexIRdrAhToAhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& ZcplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,AmpVertexIRosAhToAhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,ZcplAhAhAh,cplAhAhhh,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplAhAhAhAh1,    & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,AmpVertexIRosAhToAhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,AmpVertexIRosAhToAhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplAhAhAhAh1,    & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,AmpVertexIRosAhToAhAh)

 End if 
 End if 
AmpVertexAhToAhAh = AmpVertexAhToAhAh -  AmpVertexIRdrAhToAhAh! +  AmpVertexIRosAhToAhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhToAhAh=0._dp 
AmpVertexZAhToAhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhToAhAh(gt2,:,:) = AmpWaveZAhToAhAh(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhToAhAh(gt1,:,:) 
AmpVertexZAhToAhAh(gt2,:,:)= AmpVertexZAhToAhAh(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhToAhAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhToAhAh=AmpWaveZAhToAhAh 
AmpVertexAhToAhAh= AmpVertexZAhToAhAh
! Final State 1 
AmpWaveZAhToAhAh=0._dp 
AmpVertexZAhToAhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhToAhAh(:,gt2,:) = AmpWaveZAhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWaveAhToAhAh(:,gt1,:) 
AmpVertexZAhToAhAh(:,gt2,:)= AmpVertexZAhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpVertexAhToAhAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhToAhAh=AmpWaveZAhToAhAh 
AmpVertexAhToAhAh= AmpVertexZAhToAhAh
! Final State 2 
AmpWaveZAhToAhAh=0._dp 
AmpVertexZAhToAhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhToAhAh(:,:,gt2) = AmpWaveZAhToAhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveAhToAhAh(:,:,gt1) 
AmpVertexZAhToAhAh(:,:,gt2)= AmpVertexZAhToAhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexAhToAhAh(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhToAhAh=AmpWaveZAhToAhAh 
AmpVertexAhToAhAh= AmpVertexZAhToAhAh
End if
If (ShiftIRdiv) Then 
AmpVertexAhToAhAh = AmpVertexAhToAhAh  +  AmpVertexIRosAhToAhAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Ah Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhToAhAh = AmpTreeAhToAhAh 
 AmpSum2AhToAhAh = AmpTreeAhToAhAh + 2._dp*AmpWaveAhToAhAh + 2._dp*AmpVertexAhToAhAh  
Else 
 AmpSumAhToAhAh = AmpTreeAhToAhAh + AmpWaveAhToAhAh + AmpVertexAhToAhAh
 AmpSum2AhToAhAh = AmpTreeAhToAhAh + AmpWaveAhToAhAh + AmpVertexAhToAhAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToAhAh = AmpTreeAhToAhAh
 AmpSum2AhToAhAh = AmpTreeAhToAhAh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
    Do gt3=gt2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MAh(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhToAhAh = AmpTreeAhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MAh(gt2),MAh(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhToAhAh(gt1, gt2, gt3) 
  AmpSum2AhToAhAh = 2._dp*AmpWaveAhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MAh(gt2),MAh(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhToAhAh(gt1, gt2, gt3) 
  AmpSum2AhToAhAh = 2._dp*AmpVertexAhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MAh(gt2),MAh(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhToAhAh(gt1, gt2, gt3) 
  AmpSum2AhToAhAh = AmpTreeAhToAhAh + 2._dp*AmpWaveAhToAhAh + 2._dp*AmpVertexAhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MAh(gt2),MAh(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhToAhAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhToAhAh = AmpTreeAhToAhAh
  Call SquareAmp_StoSS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
  AmpSqTreeAhToAhAh(gt1, gt2, gt3) = AmpSqAhToAhAh(gt1, gt2, gt3)  
  AmpSum2AhToAhAh = + 2._dp*AmpWaveAhToAhAh + 2._dp*AmpVertexAhToAhAh
  Call SquareAmp_StoSS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
  AmpSqAhToAhAh(gt1, gt2, gt3) = AmpSqAhToAhAh(gt1, gt2, gt3) + AmpSqTreeAhToAhAh(gt1, gt2, gt3)  
Else  
  AmpSum2AhToAhAh = AmpTreeAhToAhAh
  Call SquareAmp_StoSS(MAh(gt1),MAh(gt2),MAh(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
  AmpSqTreeAhToAhAh(gt1, gt2, gt3) = AmpSqAhToAhAh(gt1, gt2, gt3)  
  AmpSum2AhToAhAh = + 2._dp*AmpWaveAhToAhAh + 2._dp*AmpVertexAhToAhAh
  Call SquareAmp_StoSS(MAh(gt1),MAh(gt2),MAh(gt3),AmpSumAhToAhAh(gt1, gt2, gt3),AmpSum2AhToAhAh(gt1, gt2, gt3),AmpSqAhToAhAh(gt1, gt2, gt3)) 
  AmpSqAhToAhAh(gt1, gt2, gt3) = AmpSqAhToAhAh(gt1, gt2, gt3) + AmpSqTreeAhToAhAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhToAhAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (gt2.ne.gt3) helfactor = 2._dp*helfactor 
If (AmpSqAhToAhAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp/2._dp*GammaTPS(MAhOS(gt1),MAhOS(gt2),MAhOS(gt3),helfactor*AmpSqAhToAhAh(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp/2._dp*GammaTPS(MAh(gt1),MAh(gt2),MAh(gt3),helfactor*AmpSqAhToAhAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPAhToAhAh(gt1, gt2, gt3) + MRGAhToAhAh(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPAhToAhAh(gt1, gt2, gt3) + MRGAhToAhAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! hh Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTohhAh(cplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhAh)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTohhAh(ZcplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhAh(MLambda,em,gs,cplAhAhhh,MAhOS,MhhOS,               & 
& MRPAhTohhAh,MRGAhTohhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhAh(MLambda,em,gs,ZcplAhAhhh,MAhOS,MhhOS,              & 
& MRPAhTohhAh,MRGAhTohhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTohhAh(MLambda,em,gs,cplAhAhhh,MAh,Mhh,MRPAhTohhAh,       & 
& MRGAhTohhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhAh(MLambda,em,gs,ZcplAhAhhh,MAh,Mhh,MRPAhTohhAh,      & 
& MRGAhTohhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTohhAh(cplAhAhhh,ctcplAhAhhh,MAh,MAh2,Mhh,            & 
& Mhh2,ZfAh,Zfhh,AmpWaveAhTohhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexAhTohhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRdrAhTohhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,ZcplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,             & 
& cplAhAhHmcHm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRosAhTohhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,ZcplAhAhhh,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRosAhTohhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,             & 
& cplAhAhHmcHm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRosAhTohhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRosAhTohhAh)

 End if 
 End if 
AmpVertexAhTohhAh = AmpVertexAhTohhAh -  AmpVertexIRdrAhTohhAh! +  AmpVertexIRosAhTohhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTohhAh=0._dp 
AmpVertexZAhTohhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhAh(gt2,:,:) = AmpWaveZAhTohhAh(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTohhAh(gt1,:,:) 
AmpVertexZAhTohhAh(gt2,:,:)= AmpVertexZAhTohhAh(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTohhAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTohhAh=AmpWaveZAhTohhAh 
AmpVertexAhTohhAh= AmpVertexZAhTohhAh
! Final State 1 
AmpWaveZAhTohhAh=0._dp 
AmpVertexZAhTohhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhAh(:,gt2,:) = AmpWaveZAhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWaveAhTohhAh(:,gt1,:) 
AmpVertexZAhTohhAh(:,gt2,:)= AmpVertexZAhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexAhTohhAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTohhAh=AmpWaveZAhTohhAh 
AmpVertexAhTohhAh= AmpVertexZAhTohhAh
! Final State 2 
AmpWaveZAhTohhAh=0._dp 
AmpVertexZAhTohhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhAh(:,:,gt2) = AmpWaveZAhTohhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveAhTohhAh(:,:,gt1) 
AmpVertexZAhTohhAh(:,:,gt2)= AmpVertexZAhTohhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexAhTohhAh(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTohhAh=AmpWaveZAhTohhAh 
AmpVertexAhTohhAh= AmpVertexZAhTohhAh
End if
If (ShiftIRdiv) Then 
AmpVertexAhTohhAh = AmpVertexAhTohhAh  +  AmpVertexIRosAhTohhAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->hh Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTohhAh = AmpTreeAhTohhAh 
 AmpSum2AhTohhAh = AmpTreeAhTohhAh + 2._dp*AmpWaveAhTohhAh + 2._dp*AmpVertexAhTohhAh  
Else 
 AmpSumAhTohhAh = AmpTreeAhTohhAh + AmpWaveAhTohhAh + AmpVertexAhTohhAh
 AmpSum2AhTohhAh = AmpTreeAhTohhAh + AmpWaveAhTohhAh + AmpVertexAhTohhAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTohhAh = AmpTreeAhTohhAh
 AmpSum2AhTohhAh = AmpTreeAhTohhAh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(Mhh(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTohhAh = AmpTreeAhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),MAh(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTohhAh(gt1, gt2, gt3) 
  AmpSum2AhTohhAh = 2._dp*AmpWaveAhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),MAh(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTohhAh(gt1, gt2, gt3) 
  AmpSum2AhTohhAh = 2._dp*AmpVertexAhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),MAh(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTohhAh(gt1, gt2, gt3) 
  AmpSum2AhTohhAh = AmpTreeAhTohhAh + 2._dp*AmpWaveAhTohhAh + 2._dp*AmpVertexAhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),MAh(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTohhAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTohhAh = AmpTreeAhTohhAh
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
  AmpSqTreeAhTohhAh(gt1, gt2, gt3) = AmpSqAhTohhAh(gt1, gt2, gt3)  
  AmpSum2AhTohhAh = + 2._dp*AmpWaveAhTohhAh + 2._dp*AmpVertexAhTohhAh
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
  AmpSqAhTohhAh(gt1, gt2, gt3) = AmpSqAhTohhAh(gt1, gt2, gt3) + AmpSqTreeAhTohhAh(gt1, gt2, gt3)  
Else  
  AmpSum2AhTohhAh = AmpTreeAhTohhAh
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),MAh(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
  AmpSqTreeAhTohhAh(gt1, gt2, gt3) = AmpSqAhTohhAh(gt1, gt2, gt3)  
  AmpSum2AhTohhAh = + 2._dp*AmpWaveAhTohhAh + 2._dp*AmpVertexAhTohhAh
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),MAh(gt3),AmpSumAhTohhAh(gt1, gt2, gt3),AmpSum2AhTohhAh(gt1, gt2, gt3),AmpSqAhTohhAh(gt1, gt2, gt3)) 
  AmpSqAhTohhAh(gt1, gt2, gt3) = AmpSqAhTohhAh(gt1, gt2, gt3) + AmpSqTreeAhTohhAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTohhAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTohhAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MhhOS(gt2),MAhOS(gt3),helfactor*AmpSqAhTohhAh(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),Mhh(gt2),MAh(gt3),helfactor*AmpSqAhTohhAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTohhAh(gt1, gt2, gt3) + MRGAhTohhAh(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTohhAh(gt1, gt2, gt3) + MRGAhTohhAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! bar(Fd) Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTocFdFd(cplcFdFdAhL,cplcFdFdAhR,MAh,MFd,              & 
& MAh2,MFd2,AmpTreeAhTocFdFd)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTocFdFd(ZcplcFdFdAhL,ZcplcFdFdAhR,MAh,MFd,            & 
& MAh2,MFd2,AmpTreeAhTocFdFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFdFd(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,            & 
& MAhOS,MFdOS,MRPAhTocFdFd,MRGAhTocFdFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFdFd(MLambda,em,gs,ZcplcFdFdAhL,ZcplcFdFdAhR,          & 
& MAhOS,MFdOS,MRPAhTocFdFd,MRGAhTocFdFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTocFdFd(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,            & 
& MAh,MFd,MRPAhTocFdFd,MRGAhTocFdFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFdFd(MLambda,em,gs,ZcplcFdFdAhL,ZcplcFdFdAhR,          & 
& MAh,MFd,MRPAhTocFdFd,MRGAhTocFdFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTocFdFd(cplcFdFdAhL,cplcFdFdAhR,ctcplcFdFdAhL,        & 
& ctcplcFdFdAhR,MAh,MAh2,MFd,MFd2,ZfAh,ZfDL,ZfDR,AmpWaveAhTocFdFd)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,        & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,               & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,           & 
& cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,AmpVertexAhTocFdFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& AmpVertexIRdrAhTocFdFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,ZcplcFdFdAhL,ZcplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,          & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,AmpVertexIRosAhTocFdFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& ZcplcFdFdAhL,ZcplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,      & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& AmpVertexIRosAhTocFdFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,        & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,AmpVertexIRosAhTocFdFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,         & 
& AmpVertexIRosAhTocFdFd)

 End if 
 End if 
AmpVertexAhTocFdFd = AmpVertexAhTocFdFd -  AmpVertexIRdrAhTocFdFd! +  AmpVertexIRosAhTocFdFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocFdFd=0._dp 
AmpVertexZAhTocFdFd=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocFdFd(:,gt2,:,:) = AmpWaveZAhTocFdFd(:,gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocFdFd(:,gt1,:,:) 
AmpVertexZAhTocFdFd(:,gt2,:,:)= AmpVertexZAhTocFdFd(:,gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocFdFd(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocFdFd=AmpWaveZAhTocFdFd 
AmpVertexAhTocFdFd= AmpVertexZAhTocFdFd
! Final State 1 
AmpWaveZAhTocFdFd=0._dp 
AmpVertexZAhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFdFd(1,:,gt2,:) = AmpWaveZAhTocFdFd(1,:,gt2,:)+ZRUUd(gt2,gt1)*AmpWaveAhTocFdFd(1,:,gt1,:) 
AmpVertexZAhTocFdFd(1,:,gt2,:)= AmpVertexZAhTocFdFd(1,:,gt2,:)+ZRUUd(gt2,gt1)*AmpVertexAhTocFdFd(1,:,gt1,:) 
AmpWaveZAhTocFdFd(2,:,gt2,:) = AmpWaveZAhTocFdFd(2,:,gt2,:)+ZRUVdc(gt2,gt1)*AmpWaveAhTocFdFd(2,:,gt1,:) 
AmpVertexZAhTocFdFd(2,:,gt2,:)= AmpVertexZAhTocFdFd(2,:,gt2,:)+ZRUVdc(gt2,gt1)*AmpVertexAhTocFdFd(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocFdFd=AmpWaveZAhTocFdFd 
AmpVertexAhTocFdFd= AmpVertexZAhTocFdFd
! Final State 2 
AmpWaveZAhTocFdFd=0._dp 
AmpVertexZAhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFdFd(1,:,:,gt2) = AmpWaveZAhTocFdFd(1,:,:,gt2)+ZRUVd(gt2,gt1)*AmpWaveAhTocFdFd(1,:,:,gt1) 
AmpVertexZAhTocFdFd(1,:,:,gt2)= AmpVertexZAhTocFdFd(1,:,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexAhTocFdFd(1,:,:,gt1) 
AmpWaveZAhTocFdFd(2,:,:,gt2) = AmpWaveZAhTocFdFd(2,:,:,gt2)+ZRUUd(gt2,gt1)*AmpWaveAhTocFdFd(2,:,:,gt1) 
AmpVertexZAhTocFdFd(2,:,:,gt2)= AmpVertexZAhTocFdFd(2,:,:,gt2)+ZRUUd(gt2,gt1)*AmpVertexAhTocFdFd(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocFdFd=AmpWaveZAhTocFdFd 
AmpVertexAhTocFdFd= AmpVertexZAhTocFdFd
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocFdFd = AmpVertexAhTocFdFd  +  AmpVertexIRosAhTocFdFd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->bar[Fd] Fd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocFdFd = AmpTreeAhTocFdFd 
 AmpSum2AhTocFdFd = AmpTreeAhTocFdFd + 2._dp*AmpWaveAhTocFdFd + 2._dp*AmpVertexAhTocFdFd  
Else 
 AmpSumAhTocFdFd = AmpTreeAhTocFdFd + AmpWaveAhTocFdFd + AmpVertexAhTocFdFd
 AmpSum2AhTocFdFd = AmpTreeAhTocFdFd + AmpWaveAhTocFdFd + AmpVertexAhTocFdFd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocFdFd = AmpTreeAhTocFdFd
 AmpSum2AhTocFdFd = AmpTreeAhTocFdFd 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MFd(gt2))+Abs(MFd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocFdFd = AmpTreeAhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFd(gt2),MFd(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocFdFd(gt1, gt2, gt3) 
  AmpSum2AhTocFdFd = 2._dp*AmpWaveAhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFd(gt2),MFd(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocFdFd(gt1, gt2, gt3) 
  AmpSum2AhTocFdFd = 2._dp*AmpVertexAhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFd(gt2),MFd(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocFdFd(gt1, gt2, gt3) 
  AmpSum2AhTocFdFd = AmpTreeAhTocFdFd + 2._dp*AmpWaveAhTocFdFd + 2._dp*AmpVertexAhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFd(gt2),MFd(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocFdFd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocFdFd = AmpTreeAhTocFdFd
  Call SquareAmp_StoFF(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
  AmpSqTreeAhTocFdFd(gt1, gt2, gt3) = AmpSqAhTocFdFd(gt1, gt2, gt3)  
  AmpSum2AhTocFdFd = + 2._dp*AmpWaveAhTocFdFd + 2._dp*AmpVertexAhTocFdFd
  Call SquareAmp_StoFF(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
  AmpSqAhTocFdFd(gt1, gt2, gt3) = AmpSqAhTocFdFd(gt1, gt2, gt3) + AmpSqTreeAhTocFdFd(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocFdFd = AmpTreeAhTocFdFd
  Call SquareAmp_StoFF(MAh(gt1),MFd(gt2),MFd(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
  AmpSqTreeAhTocFdFd(gt1, gt2, gt3) = AmpSqAhTocFdFd(gt1, gt2, gt3)  
  AmpSum2AhTocFdFd = + 2._dp*AmpWaveAhTocFdFd + 2._dp*AmpVertexAhTocFdFd
  Call SquareAmp_StoFF(MAh(gt1),MFd(gt2),MFd(gt3),AmpSumAhTocFdFd(:,gt1, gt2, gt3),AmpSum2AhTocFdFd(:,gt1, gt2, gt3),AmpSqAhTocFdFd(gt1, gt2, gt3)) 
  AmpSqAhTocFdFd(gt1, gt2, gt3) = AmpSqAhTocFdFd(gt1, gt2, gt3) + AmpSqTreeAhTocFdFd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocFdFd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqAhTocFdFd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAhOS(gt1),MFdOS(gt2),MFdOS(gt3),helfactor*AmpSqAhTocFdFd(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAh(gt1),MFd(gt2),MFd(gt3),helfactor*AmpSqAhTocFdFd(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocFdFd(gt1, gt2, gt3) + MRGAhTocFdFd(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocFdFd(gt1, gt2, gt3) + MRGAhTocFdFd(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! bar(Fe) Fe
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTocFeFe(cplcFeFeAhL,cplcFeFeAhR,MAh,MFe,              & 
& MAh2,MFe2,AmpTreeAhTocFeFe)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTocFeFe(ZcplcFeFeAhL,ZcplcFeFeAhR,MAh,MFe,            & 
& MAh2,MFe2,AmpTreeAhTocFeFe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFeFe(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,            & 
& MAhOS,MFeOS,MRPAhTocFeFe,MRGAhTocFeFe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFeFe(MLambda,em,gs,ZcplcFeFeAhL,ZcplcFeFeAhR,          & 
& MAhOS,MFeOS,MRPAhTocFeFe,MRGAhTocFeFe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTocFeFe(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,            & 
& MAh,MFe,MRPAhTocFeFe,MRGAhTocFeFe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFeFe(MLambda,em,gs,ZcplcFeFeAhL,ZcplcFeFeAhR,          & 
& MAh,MFe,MRPAhTocFeFe,MRGAhTocFeFe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTocFeFe(cplcFeFeAhL,cplcFeFeAhR,ctcplcFeFeAhL,        & 
& ctcplcFeFeAhR,MAh,MAh2,MFe,MFe2,ZfAh,ZfEL,ZfER,AmpWaveAhTocFeFe)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,               & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,       & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexAhTocFeFe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,       & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexIRdrAhTocFeFe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,      & 
& ZcplcFeFeAhL,ZcplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,      & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosAhTocFeFe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,ZcplcFeFeAhL,ZcplcFeFeAhR,     & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexIRosAhTocFeFe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,      & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosAhTocFeFe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,       & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,cplcFeFehhR,        & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,         & 
& AmpVertexIRosAhTocFeFe)

 End if 
 End if 
AmpVertexAhTocFeFe = AmpVertexAhTocFeFe -  AmpVertexIRdrAhTocFeFe! +  AmpVertexIRosAhTocFeFe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocFeFe=0._dp 
AmpVertexZAhTocFeFe=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocFeFe(:,gt2,:,:) = AmpWaveZAhTocFeFe(:,gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocFeFe(:,gt1,:,:) 
AmpVertexZAhTocFeFe(:,gt2,:,:)= AmpVertexZAhTocFeFe(:,gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocFeFe(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocFeFe=AmpWaveZAhTocFeFe 
AmpVertexAhTocFeFe= AmpVertexZAhTocFeFe
! Final State 1 
AmpWaveZAhTocFeFe=0._dp 
AmpVertexZAhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFeFe(1,:,gt2,:) = AmpWaveZAhTocFeFe(1,:,gt2,:)+ZRUUe(gt2,gt1)*AmpWaveAhTocFeFe(1,:,gt1,:) 
AmpVertexZAhTocFeFe(1,:,gt2,:)= AmpVertexZAhTocFeFe(1,:,gt2,:)+ZRUUe(gt2,gt1)*AmpVertexAhTocFeFe(1,:,gt1,:) 
AmpWaveZAhTocFeFe(2,:,gt2,:) = AmpWaveZAhTocFeFe(2,:,gt2,:)+ZRUVec(gt2,gt1)*AmpWaveAhTocFeFe(2,:,gt1,:) 
AmpVertexZAhTocFeFe(2,:,gt2,:)= AmpVertexZAhTocFeFe(2,:,gt2,:)+ZRUVec(gt2,gt1)*AmpVertexAhTocFeFe(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocFeFe=AmpWaveZAhTocFeFe 
AmpVertexAhTocFeFe= AmpVertexZAhTocFeFe
! Final State 2 
AmpWaveZAhTocFeFe=0._dp 
AmpVertexZAhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFeFe(1,:,:,gt2) = AmpWaveZAhTocFeFe(1,:,:,gt2)+ZRUVe(gt2,gt1)*AmpWaveAhTocFeFe(1,:,:,gt1) 
AmpVertexZAhTocFeFe(1,:,:,gt2)= AmpVertexZAhTocFeFe(1,:,:,gt2)+ZRUVe(gt2,gt1)*AmpVertexAhTocFeFe(1,:,:,gt1) 
AmpWaveZAhTocFeFe(2,:,:,gt2) = AmpWaveZAhTocFeFe(2,:,:,gt2)+ZRUUe(gt2,gt1)*AmpWaveAhTocFeFe(2,:,:,gt1) 
AmpVertexZAhTocFeFe(2,:,:,gt2)= AmpVertexZAhTocFeFe(2,:,:,gt2)+ZRUUe(gt2,gt1)*AmpVertexAhTocFeFe(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocFeFe=AmpWaveZAhTocFeFe 
AmpVertexAhTocFeFe= AmpVertexZAhTocFeFe
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocFeFe = AmpVertexAhTocFeFe  +  AmpVertexIRosAhTocFeFe
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->bar[Fe] Fe -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocFeFe = AmpTreeAhTocFeFe 
 AmpSum2AhTocFeFe = AmpTreeAhTocFeFe + 2._dp*AmpWaveAhTocFeFe + 2._dp*AmpVertexAhTocFeFe  
Else 
 AmpSumAhTocFeFe = AmpTreeAhTocFeFe + AmpWaveAhTocFeFe + AmpVertexAhTocFeFe
 AmpSum2AhTocFeFe = AmpTreeAhTocFeFe + AmpWaveAhTocFeFe + AmpVertexAhTocFeFe 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocFeFe = AmpTreeAhTocFeFe
 AmpSum2AhTocFeFe = AmpTreeAhTocFeFe 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(MFeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MFe(gt2))+Abs(MFe(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocFeFe = AmpTreeAhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFe(gt2),MFe(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocFeFe(gt1, gt2, gt3) 
  AmpSum2AhTocFeFe = 2._dp*AmpWaveAhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFe(gt2),MFe(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocFeFe(gt1, gt2, gt3) 
  AmpSum2AhTocFeFe = 2._dp*AmpVertexAhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFe(gt2),MFe(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocFeFe(gt1, gt2, gt3) 
  AmpSum2AhTocFeFe = AmpTreeAhTocFeFe + 2._dp*AmpWaveAhTocFeFe + 2._dp*AmpVertexAhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFe(gt2),MFe(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocFeFe(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocFeFe = AmpTreeAhTocFeFe
  Call SquareAmp_StoFF(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
  AmpSqTreeAhTocFeFe(gt1, gt2, gt3) = AmpSqAhTocFeFe(gt1, gt2, gt3)  
  AmpSum2AhTocFeFe = + 2._dp*AmpWaveAhTocFeFe + 2._dp*AmpVertexAhTocFeFe
  Call SquareAmp_StoFF(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
  AmpSqAhTocFeFe(gt1, gt2, gt3) = AmpSqAhTocFeFe(gt1, gt2, gt3) + AmpSqTreeAhTocFeFe(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocFeFe = AmpTreeAhTocFeFe
  Call SquareAmp_StoFF(MAh(gt1),MFe(gt2),MFe(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
  AmpSqTreeAhTocFeFe(gt1, gt2, gt3) = AmpSqAhTocFeFe(gt1, gt2, gt3)  
  AmpSum2AhTocFeFe = + 2._dp*AmpWaveAhTocFeFe + 2._dp*AmpVertexAhTocFeFe
  Call SquareAmp_StoFF(MAh(gt1),MFe(gt2),MFe(gt3),AmpSumAhTocFeFe(:,gt1, gt2, gt3),AmpSum2AhTocFeFe(:,gt1, gt2, gt3),AmpSqAhTocFeFe(gt1, gt2, gt3)) 
  AmpSqAhTocFeFe(gt1, gt2, gt3) = AmpSqAhTocFeFe(gt1, gt2, gt3) + AmpSqTreeAhTocFeFe(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocFeFe(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqAhTocFeFe(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MFeOS(gt2),MFeOS(gt3),helfactor*AmpSqAhTocFeFe(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MFe(gt2),MFe(gt3),helfactor*AmpSqAhTocFeFe(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocFeFe(gt1, gt2, gt3) + MRGAhTocFeFe(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocFeFe(gt1, gt2, gt3) + MRGAhTocFeFe(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! bar(Fu) Fu
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTocFuFu(cplcFuFuAhL,cplcFuFuAhR,MAh,MFu,              & 
& MAh2,MFu2,AmpTreeAhTocFuFu)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTocFuFu(ZcplcFuFuAhL,ZcplcFuFuAhR,MAh,MFu,            & 
& MAh2,MFu2,AmpTreeAhTocFuFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFuFu(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,            & 
& MAhOS,MFuOS,MRPAhTocFuFu,MRGAhTocFuFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFuFu(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,          & 
& MAhOS,MFuOS,MRPAhTocFuFu,MRGAhTocFuFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTocFuFu(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,            & 
& MAh,MFu,MRPAhTocFuFu,MRGAhTocFuFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocFuFu(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,          & 
& MAh,MFu,MRPAhTocFuFu,MRGAhTocFuFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTocFuFu(cplcFuFuAhL,cplcFuFuAhR,ctcplcFuFuAhL,        & 
& ctcplcFuFuAhR,MAh,MAh2,MFu,MFu2,ZfAh,ZfUL,ZfUR,AmpWaveAhTocFuFu)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,        & 
& cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,AmpVertexAhTocFuFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& AmpVertexIRdrAhTocFuFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,          & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,      & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,AmpVertexIRosAhTocFuFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,      & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& AmpVertexIRosAhTocFuFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,      & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,AmpVertexIRosAhTocFuFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& AmpVertexIRosAhTocFuFu)

 End if 
 End if 
AmpVertexAhTocFuFu = AmpVertexAhTocFuFu -  AmpVertexIRdrAhTocFuFu! +  AmpVertexIRosAhTocFuFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocFuFu=0._dp 
AmpVertexZAhTocFuFu=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocFuFu(:,gt2,:,:) = AmpWaveZAhTocFuFu(:,gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocFuFu(:,gt1,:,:) 
AmpVertexZAhTocFuFu(:,gt2,:,:)= AmpVertexZAhTocFuFu(:,gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocFuFu(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocFuFu=AmpWaveZAhTocFuFu 
AmpVertexAhTocFuFu= AmpVertexZAhTocFuFu
! Final State 1 
AmpWaveZAhTocFuFu=0._dp 
AmpVertexZAhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFuFu(1,:,gt2,:) = AmpWaveZAhTocFuFu(1,:,gt2,:)+ZRUUu(gt2,gt1)*AmpWaveAhTocFuFu(1,:,gt1,:) 
AmpVertexZAhTocFuFu(1,:,gt2,:)= AmpVertexZAhTocFuFu(1,:,gt2,:)+ZRUUu(gt2,gt1)*AmpVertexAhTocFuFu(1,:,gt1,:) 
AmpWaveZAhTocFuFu(2,:,gt2,:) = AmpWaveZAhTocFuFu(2,:,gt2,:)+ZRUVuc(gt2,gt1)*AmpWaveAhTocFuFu(2,:,gt1,:) 
AmpVertexZAhTocFuFu(2,:,gt2,:)= AmpVertexZAhTocFuFu(2,:,gt2,:)+ZRUVuc(gt2,gt1)*AmpVertexAhTocFuFu(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocFuFu=AmpWaveZAhTocFuFu 
AmpVertexAhTocFuFu= AmpVertexZAhTocFuFu
! Final State 2 
AmpWaveZAhTocFuFu=0._dp 
AmpVertexZAhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFuFu(1,:,:,gt2) = AmpWaveZAhTocFuFu(1,:,:,gt2)+ZRUVu(gt2,gt1)*AmpWaveAhTocFuFu(1,:,:,gt1) 
AmpVertexZAhTocFuFu(1,:,:,gt2)= AmpVertexZAhTocFuFu(1,:,:,gt2)+ZRUVu(gt2,gt1)*AmpVertexAhTocFuFu(1,:,:,gt1) 
AmpWaveZAhTocFuFu(2,:,:,gt2) = AmpWaveZAhTocFuFu(2,:,:,gt2)+ZRUUu(gt2,gt1)*AmpWaveAhTocFuFu(2,:,:,gt1) 
AmpVertexZAhTocFuFu(2,:,:,gt2)= AmpVertexZAhTocFuFu(2,:,:,gt2)+ZRUUu(gt2,gt1)*AmpVertexAhTocFuFu(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocFuFu=AmpWaveZAhTocFuFu 
AmpVertexAhTocFuFu= AmpVertexZAhTocFuFu
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocFuFu = AmpVertexAhTocFuFu  +  AmpVertexIRosAhTocFuFu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->bar[Fu] Fu -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocFuFu = AmpTreeAhTocFuFu 
 AmpSum2AhTocFuFu = AmpTreeAhTocFuFu + 2._dp*AmpWaveAhTocFuFu + 2._dp*AmpVertexAhTocFuFu  
Else 
 AmpSumAhTocFuFu = AmpTreeAhTocFuFu + AmpWaveAhTocFuFu + AmpVertexAhTocFuFu
 AmpSum2AhTocFuFu = AmpTreeAhTocFuFu + AmpWaveAhTocFuFu + AmpVertexAhTocFuFu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocFuFu = AmpTreeAhTocFuFu
 AmpSum2AhTocFuFu = AmpTreeAhTocFuFu 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MFu(gt2))+Abs(MFu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocFuFu = AmpTreeAhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFu(gt2),MFu(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocFuFu(gt1, gt2, gt3) 
  AmpSum2AhTocFuFu = 2._dp*AmpWaveAhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFu(gt2),MFu(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocFuFu(gt1, gt2, gt3) 
  AmpSum2AhTocFuFu = 2._dp*AmpVertexAhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFu(gt2),MFu(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocFuFu(gt1, gt2, gt3) 
  AmpSum2AhTocFuFu = AmpTreeAhTocFuFu + 2._dp*AmpWaveAhTocFuFu + 2._dp*AmpVertexAhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MFu(gt2),MFu(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocFuFu(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocFuFu = AmpTreeAhTocFuFu
  Call SquareAmp_StoFF(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
  AmpSqTreeAhTocFuFu(gt1, gt2, gt3) = AmpSqAhTocFuFu(gt1, gt2, gt3)  
  AmpSum2AhTocFuFu = + 2._dp*AmpWaveAhTocFuFu + 2._dp*AmpVertexAhTocFuFu
  Call SquareAmp_StoFF(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
  AmpSqAhTocFuFu(gt1, gt2, gt3) = AmpSqAhTocFuFu(gt1, gt2, gt3) + AmpSqTreeAhTocFuFu(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocFuFu = AmpTreeAhTocFuFu
  Call SquareAmp_StoFF(MAh(gt1),MFu(gt2),MFu(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
  AmpSqTreeAhTocFuFu(gt1, gt2, gt3) = AmpSqAhTocFuFu(gt1, gt2, gt3)  
  AmpSum2AhTocFuFu = + 2._dp*AmpWaveAhTocFuFu + 2._dp*AmpVertexAhTocFuFu
  Call SquareAmp_StoFF(MAh(gt1),MFu(gt2),MFu(gt3),AmpSumAhTocFuFu(:,gt1, gt2, gt3),AmpSum2AhTocFuFu(:,gt1, gt2, gt3),AmpSqAhTocFuFu(gt1, gt2, gt3)) 
  AmpSqAhTocFuFu(gt1, gt2, gt3) = AmpSqAhTocFuFu(gt1, gt2, gt3) + AmpSqTreeAhTocFuFu(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocFuFu(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqAhTocFuFu(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAhOS(gt1),MFuOS(gt2),MFuOS(gt3),helfactor*AmpSqAhTocFuFu(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAh(gt1),MFu(gt2),MFu(gt3),helfactor*AmpSqAhTocFuFu(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocFuFu(gt1, gt2, gt3) + MRGAhTocFuFu(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocFuFu(gt1, gt2, gt3) + MRGAhTocFuFu(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! hh hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTohhhh(cplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhhh)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTohhhh(ZcplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhhh(MLambda,em,gs,cplAhhhhh,MAhOS,MhhOS,               & 
& MRPAhTohhhh,MRGAhTohhhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhhh(MLambda,em,gs,ZcplAhhhhh,MAhOS,MhhOS,              & 
& MRPAhTohhhh,MRGAhTohhhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTohhhh(MLambda,em,gs,cplAhhhhh,MAh,Mhh,MRPAhTohhhh,       & 
& MRGAhTohhhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhhh(MLambda,em,gs,ZcplAhhhhh,MAh,Mhh,MRPAhTohhhh,      & 
& MRGAhTohhhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTohhhh(cplAhhhhh,ctcplAhhhhh,MAh,MAh2,Mhh,            & 
& Mhh2,ZfAh,Zfhh,AmpWaveAhTohhhh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexAhTohhhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexIRdrAhTohhhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHmcHm,               & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,              & 
& cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,           & 
& cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,AmpVertexIRosAhTohhhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexIRosAhTohhhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,         & 
& cplhhhhhhhh1,cplhhhhHmcHm1,AmpVertexIRosAhTohhhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexIRosAhTohhhh)

 End if 
 End if 
AmpVertexAhTohhhh = AmpVertexAhTohhhh -  AmpVertexIRdrAhTohhhh! +  AmpVertexIRosAhTohhhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTohhhh=0._dp 
AmpVertexZAhTohhhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhhh(gt2,:,:) = AmpWaveZAhTohhhh(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTohhhh(gt1,:,:) 
AmpVertexZAhTohhhh(gt2,:,:)= AmpVertexZAhTohhhh(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTohhhh(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTohhhh=AmpWaveZAhTohhhh 
AmpVertexAhTohhhh= AmpVertexZAhTohhhh
! Final State 1 
AmpWaveZAhTohhhh=0._dp 
AmpVertexZAhTohhhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhhh(:,gt2,:) = AmpWaveZAhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWaveAhTohhhh(:,gt1,:) 
AmpVertexZAhTohhhh(:,gt2,:)= AmpVertexZAhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexAhTohhhh(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTohhhh=AmpWaveZAhTohhhh 
AmpVertexAhTohhhh= AmpVertexZAhTohhhh
! Final State 2 
AmpWaveZAhTohhhh=0._dp 
AmpVertexZAhTohhhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhhh(:,:,gt2) = AmpWaveZAhTohhhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveAhTohhhh(:,:,gt1) 
AmpVertexZAhTohhhh(:,:,gt2)= AmpVertexZAhTohhhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexAhTohhhh(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTohhhh=AmpWaveZAhTohhhh 
AmpVertexAhTohhhh= AmpVertexZAhTohhhh
End if
If (ShiftIRdiv) Then 
AmpVertexAhTohhhh = AmpVertexAhTohhhh  +  AmpVertexIRosAhTohhhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->hh hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTohhhh = AmpTreeAhTohhhh 
 AmpSum2AhTohhhh = AmpTreeAhTohhhh + 2._dp*AmpWaveAhTohhhh + 2._dp*AmpVertexAhTohhhh  
Else 
 AmpSumAhTohhhh = AmpTreeAhTohhhh + AmpWaveAhTohhhh + AmpVertexAhTohhhh
 AmpSum2AhTohhhh = AmpTreeAhTohhhh + AmpWaveAhTohhhh + AmpVertexAhTohhhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTohhhh = AmpTreeAhTohhhh
 AmpSum2AhTohhhh = AmpTreeAhTohhhh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
    Do gt3=gt2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(Mhh(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTohhhh = AmpTreeAhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),Mhh(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTohhhh(gt1, gt2, gt3) 
  AmpSum2AhTohhhh = 2._dp*AmpWaveAhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),Mhh(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTohhhh(gt1, gt2, gt3) 
  AmpSum2AhTohhhh = 2._dp*AmpVertexAhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),Mhh(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTohhhh(gt1, gt2, gt3) 
  AmpSum2AhTohhhh = AmpTreeAhTohhhh + 2._dp*AmpWaveAhTohhhh + 2._dp*AmpVertexAhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),Mhh(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTohhhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTohhhh = AmpTreeAhTohhhh
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
  AmpSqTreeAhTohhhh(gt1, gt2, gt3) = AmpSqAhTohhhh(gt1, gt2, gt3)  
  AmpSum2AhTohhhh = + 2._dp*AmpWaveAhTohhhh + 2._dp*AmpVertexAhTohhhh
  Call SquareAmp_StoSS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
  AmpSqAhTohhhh(gt1, gt2, gt3) = AmpSqAhTohhhh(gt1, gt2, gt3) + AmpSqTreeAhTohhhh(gt1, gt2, gt3)  
Else  
  AmpSum2AhTohhhh = AmpTreeAhTohhhh
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),Mhh(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
  AmpSqTreeAhTohhhh(gt1, gt2, gt3) = AmpSqAhTohhhh(gt1, gt2, gt3)  
  AmpSum2AhTohhhh = + 2._dp*AmpWaveAhTohhhh + 2._dp*AmpVertexAhTohhhh
  Call SquareAmp_StoSS(MAh(gt1),Mhh(gt2),Mhh(gt3),AmpSumAhTohhhh(gt1, gt2, gt3),AmpSum2AhTohhhh(gt1, gt2, gt3),AmpSqAhTohhhh(gt1, gt2, gt3)) 
  AmpSqAhTohhhh(gt1, gt2, gt3) = AmpSqAhTohhhh(gt1, gt2, gt3) + AmpSqTreeAhTohhhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTohhhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (gt2.ne.gt3) helfactor = 2._dp*helfactor 
If (AmpSqAhTohhhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp/2._dp*GammaTPS(MAhOS(gt1),MhhOS(gt2),MhhOS(gt3),helfactor*AmpSqAhTohhhh(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp/2._dp*GammaTPS(MAh(gt1),Mhh(gt2),Mhh(gt3),helfactor*AmpSqAhTohhhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPAhTohhhh(gt1, gt2, gt3) + MRGAhTohhhh(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPAhTohhhh(gt1, gt2, gt3) + MRGAhTohhhh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! hh VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTohhVZ(cplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,               & 
& MVZ2,AmpTreeAhTohhVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTohhVZ(ZcplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,              & 
& MVZ2,AmpTreeAhTohhVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhVZ(MLambda,em,gs,cplAhhhVZ,MAhOS,MhhOS,               & 
& MVZOS,MRPAhTohhVZ,MRGAhTohhVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhVZ(MLambda,em,gs,ZcplAhhhVZ,MAhOS,MhhOS,              & 
& MVZOS,MRPAhTohhVZ,MRGAhTohhVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTohhVZ(MLambda,em,gs,cplAhhhVZ,MAh,Mhh,MVZ,               & 
& MRPAhTohhVZ,MRGAhTohhVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTohhVZ(MLambda,em,gs,ZcplAhhhVZ,MAh,Mhh,MVZ,              & 
& MRPAhTohhVZ,MRGAhTohhVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTohhVZ(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,            & 
& Mhh2,MVZ,MVZ2,ZfAh,Zfhh,ZfVZ,AmpWaveAhTohhVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexAhTohhVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexIRdrAhTohhVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHmcHm,               & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,        & 
& cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,       & 
& cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexIRosAhTohhVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexIRosAhTohhVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,      & 
& cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexIRosAhTohhVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexIRosAhTohhVZ)

 End if 
 End if 
AmpVertexAhTohhVZ = AmpVertexAhTohhVZ -  AmpVertexIRdrAhTohhVZ! +  AmpVertexIRosAhTohhVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTohhVZ=0._dp 
AmpVertexZAhTohhVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhVZ(:,gt2,:) = AmpWaveZAhTohhVZ(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWaveAhTohhVZ(:,gt1,:) 
AmpVertexZAhTohhVZ(:,gt2,:)= AmpVertexZAhTohhVZ(:,gt2,:) + ZRUZA(gt2,gt1)*AmpVertexAhTohhVZ(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTohhVZ=AmpWaveZAhTohhVZ 
AmpVertexAhTohhVZ= AmpVertexZAhTohhVZ
! Final State 1 
AmpWaveZAhTohhVZ=0._dp 
AmpVertexZAhTohhVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTohhVZ(:,:,gt2) = AmpWaveZAhTohhVZ(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveAhTohhVZ(:,:,gt1) 
AmpVertexZAhTohhVZ(:,:,gt2)= AmpVertexZAhTohhVZ(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexAhTohhVZ(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTohhVZ=AmpWaveZAhTohhVZ 
AmpVertexAhTohhVZ= AmpVertexZAhTohhVZ
End if
If (ShiftIRdiv) Then 
AmpVertexAhTohhVZ = AmpVertexAhTohhVZ  +  AmpVertexIRosAhTohhVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->hh VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTohhVZ = AmpTreeAhTohhVZ 
 AmpSum2AhTohhVZ = AmpTreeAhTohhVZ + 2._dp*AmpWaveAhTohhVZ + 2._dp*AmpVertexAhTohhVZ  
Else 
 AmpSumAhTohhVZ = AmpTreeAhTohhVZ + AmpWaveAhTohhVZ + AmpVertexAhTohhVZ
 AmpSum2AhTohhVZ = AmpTreeAhTohhVZ + AmpWaveAhTohhVZ + AmpVertexAhTohhVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTohhVZ = AmpTreeAhTohhVZ
 AmpSum2AhTohhVZ = AmpTreeAhTohhVZ 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(Mhh(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2AhTohhVZ = AmpTreeAhTohhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),MVZOS,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVZ,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTohhVZ(gt1, gt2) 
  AmpSum2AhTohhVZ = 2._dp*AmpWaveAhTohhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),MVZOS,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVZ,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTohhVZ(gt1, gt2) 
  AmpSum2AhTohhVZ = 2._dp*AmpVertexAhTohhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),MVZOS,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVZ,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTohhVZ(gt1, gt2) 
  AmpSum2AhTohhVZ = AmpTreeAhTohhVZ + 2._dp*AmpWaveAhTohhVZ + 2._dp*AmpVertexAhTohhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),MVZOS,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVZ,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTohhVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTohhVZ = AmpTreeAhTohhVZ
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),MVZOS,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
  AmpSqTreeAhTohhVZ(gt1, gt2) = AmpSqAhTohhVZ(gt1, gt2)  
  AmpSum2AhTohhVZ = + 2._dp*AmpWaveAhTohhVZ + 2._dp*AmpVertexAhTohhVZ
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),MVZOS,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
  AmpSqAhTohhVZ(gt1, gt2) = AmpSqAhTohhVZ(gt1, gt2) + AmpSqTreeAhTohhVZ(gt1, gt2)  
Else  
  AmpSum2AhTohhVZ = AmpTreeAhTohhVZ
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVZ,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
  AmpSqTreeAhTohhVZ(gt1, gt2) = AmpSqAhTohhVZ(gt1, gt2)  
  AmpSum2AhTohhVZ = + 2._dp*AmpWaveAhTohhVZ + 2._dp*AmpVertexAhTohhVZ
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVZ,AmpSumAhTohhVZ(:,gt1, gt2),AmpSum2AhTohhVZ(:,gt1, gt2),AmpSqAhTohhVZ(gt1, gt2)) 
  AmpSqAhTohhVZ(gt1, gt2) = AmpSqAhTohhVZ(gt1, gt2) + AmpSqTreeAhTohhVZ(gt1, gt2)  
End if  
Else  
  AmpSqAhTohhVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTohhVZ(gt1, gt2).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MhhOS(gt2),MVZOS,helfactor*AmpSqAhTohhVZ(gt1, gt2))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),Mhh(gt2),MVZ,helfactor*AmpSqAhTohhVZ(gt1, gt2))
End if 
If ((Abs(MRPAhTohhVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTohhVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPAhTohhVZ(gt1, gt2) + MRGAhTohhVZ(gt1, gt2)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPAhTohhVZ(gt1, gt2) + MRGAhTohhVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! Conjg(Hm) Hm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhTocHmHm(cplAhHmcHm,MAh,MHm,MAh2,MHm2,AmpTreeAhTocHmHm)

  Else 
Call Amplitude_Tree_gumTHDMII_AhTocHmHm(ZcplAhHmcHm,MAh,MHm,MAh2,MHm2,AmpTreeAhTocHmHm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhTocHmHm(MLambda,em,gs,cplAhHmcHm,MAhOS,MHmOS,             & 
& MRPAhTocHmHm,MRGAhTocHmHm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocHmHm(MLambda,em,gs,ZcplAhHmcHm,MAhOS,MHmOS,            & 
& MRPAhTocHmHm,MRGAhTocHmHm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhTocHmHm(MLambda,em,gs,cplAhHmcHm,MAh,MHm,MRPAhTocHmHm,    & 
& MRGAhTocHmHm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhTocHmHm(MLambda,em,gs,ZcplAhHmcHm,MAh,MHm,MRPAhTocHmHm,   & 
& MRGAhTocHmHm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTocHmHm(cplAhHmcHm,ctcplAhHmcHm,MAh,MAh2,             & 
& MHm,MHm2,ZfAh,ZfHm,AmpWaveAhTocHmHm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,    & 
& cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,            & 
& cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,            & 
& cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,     & 
& cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,  & 
& cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexAhTocHmHm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,           & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,     & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRdrAhTocHmHm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& ZcplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,             & 
& cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,             & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,   & 
& cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,             & 
& cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRosAhTocHmHm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,ZcplAhHmcHm,cplAhHmcVWm,               & 
& cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,           & 
& cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,             & 
& cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,               & 
& cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,            & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,             & 
& cplHmHmcHmcHm1,AmpVertexIRosAhTocHmHm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,             & 
& cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,             & 
& cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,             & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,   & 
& cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,             & 
& cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRosAhTocHmHm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,           & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,     & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,AmpVertexIRosAhTocHmHm)

 End if 
 End if 
AmpVertexAhTocHmHm = AmpVertexAhTocHmHm -  AmpVertexIRdrAhTocHmHm! +  AmpVertexIRosAhTocHmHm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocHmHm=0._dp 
AmpVertexZAhTocHmHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocHmHm(gt2,:,:) = AmpWaveZAhTocHmHm(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocHmHm(gt1,:,:) 
AmpVertexZAhTocHmHm(gt2,:,:)= AmpVertexZAhTocHmHm(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocHmHm(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocHmHm=AmpWaveZAhTocHmHm 
AmpVertexAhTocHmHm= AmpVertexZAhTocHmHm
! Final State 1 
AmpWaveZAhTocHmHm=0._dp 
AmpVertexZAhTocHmHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocHmHm(:,gt2,:) = AmpWaveZAhTocHmHm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveAhTocHmHm(:,gt1,:) 
AmpVertexZAhTocHmHm(:,gt2,:)= AmpVertexZAhTocHmHm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexAhTocHmHm(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocHmHm=AmpWaveZAhTocHmHm 
AmpVertexAhTocHmHm= AmpVertexZAhTocHmHm
! Final State 2 
AmpWaveZAhTocHmHm=0._dp 
AmpVertexZAhTocHmHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocHmHm(:,:,gt2) = AmpWaveZAhTocHmHm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveAhTocHmHm(:,:,gt1) 
AmpVertexZAhTocHmHm(:,:,gt2)= AmpVertexZAhTocHmHm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexAhTocHmHm(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocHmHm=AmpWaveZAhTocHmHm 
AmpVertexAhTocHmHm= AmpVertexZAhTocHmHm
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocHmHm = AmpVertexAhTocHmHm  +  AmpVertexIRosAhTocHmHm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->conj[Hm] Hm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocHmHm = AmpTreeAhTocHmHm 
 AmpSum2AhTocHmHm = AmpTreeAhTocHmHm + 2._dp*AmpWaveAhTocHmHm + 2._dp*AmpVertexAhTocHmHm  
Else 
 AmpSumAhTocHmHm = AmpTreeAhTocHmHm + AmpWaveAhTocHmHm + AmpVertexAhTocHmHm
 AmpSum2AhTocHmHm = AmpTreeAhTocHmHm + AmpWaveAhTocHmHm + AmpVertexAhTocHmHm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocHmHm = AmpTreeAhTocHmHm
 AmpSum2AhTocHmHm = AmpTreeAhTocHmHm 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MHmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MHm(gt2))+Abs(MHm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocHmHm = AmpTreeAhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHm(gt2),MHm(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocHmHm(gt1, gt2, gt3) 
  AmpSum2AhTocHmHm = 2._dp*AmpWaveAhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHm(gt2),MHm(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocHmHm(gt1, gt2, gt3) 
  AmpSum2AhTocHmHm = 2._dp*AmpVertexAhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHm(gt2),MHm(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocHmHm(gt1, gt2, gt3) 
  AmpSum2AhTocHmHm = AmpTreeAhTocHmHm + 2._dp*AmpWaveAhTocHmHm + 2._dp*AmpVertexAhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHm(gt2),MHm(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocHmHm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocHmHm = AmpTreeAhTocHmHm
  Call SquareAmp_StoSS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
  AmpSqTreeAhTocHmHm(gt1, gt2, gt3) = AmpSqAhTocHmHm(gt1, gt2, gt3)  
  AmpSum2AhTocHmHm = + 2._dp*AmpWaveAhTocHmHm + 2._dp*AmpVertexAhTocHmHm
  Call SquareAmp_StoSS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
  AmpSqAhTocHmHm(gt1, gt2, gt3) = AmpSqAhTocHmHm(gt1, gt2, gt3) + AmpSqTreeAhTocHmHm(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocHmHm = AmpTreeAhTocHmHm
  Call SquareAmp_StoSS(MAh(gt1),MHm(gt2),MHm(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
  AmpSqTreeAhTocHmHm(gt1, gt2, gt3) = AmpSqAhTocHmHm(gt1, gt2, gt3)  
  AmpSum2AhTocHmHm = + 2._dp*AmpWaveAhTocHmHm + 2._dp*AmpVertexAhTocHmHm
  Call SquareAmp_StoSS(MAh(gt1),MHm(gt2),MHm(gt3),AmpSumAhTocHmHm(gt1, gt2, gt3),AmpSum2AhTocHmHm(gt1, gt2, gt3),AmpSqAhTocHmHm(gt1, gt2, gt3)) 
  AmpSqAhTocHmHm(gt1, gt2, gt3) = AmpSqAhTocHmHm(gt1, gt2, gt3) + AmpSqTreeAhTocHmHm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocHmHm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTocHmHm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MHmOS(gt2),MHmOS(gt3),helfactor*AmpSqAhTocHmHm(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MHm(gt2),MHm(gt3),helfactor*AmpSqAhTocHmHm(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocHmHm(gt1, gt2, gt3) + MRGAhTocHmHm(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocHmHm(gt1, gt2, gt3) + MRGAhTocHmHm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! Hm Conjg(VWm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_AhToHmcVWm(cplAhHmcVWm,MAh,MHm,MVWm,MAh2,               & 
& MHm2,MVWm2,AmpTreeAhToHmcVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_AhToHmcVWm(ZcplAhHmcVWm,MAh,MHm,MVWm,MAh2,              & 
& MHm2,MVWm2,AmpTreeAhToHmcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_AhToHmcVWm(MLambda,em,gs,cplAhHmcVWm,MAhOS,MHmOS,           & 
& MVWmOS,MRPAhToHmcVWm,MRGAhToHmcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_AhToHmcVWm(MLambda,em,gs,ZcplAhHmcVWm,MAhOS,MHmOS,          & 
& MVWmOS,MRPAhToHmcVWm,MRGAhToHmcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_AhToHmcVWm(MLambda,em,gs,cplAhHmcVWm,MAh,MHm,               & 
& MVWm,MRPAhToHmcVWm,MRGAhToHmcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_AhToHmcVWm(MLambda,em,gs,ZcplAhHmcVWm,MAh,MHm,              & 
& MVWm,MRPAhToHmcVWm,MRGAhToHmcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhToHmcVWm(cplAhHmcVWm,ctcplAhHmcVWm,MAh,               & 
& MAh2,MHm,MHm2,MVWm,MVWm2,ZfAh,ZfHm,ZfVWm,AmpWaveAhToHmcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,       & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,          & 
& cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexAhToHmcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,       & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,          & 
& cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRdrAhToHmcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,          & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& GosZcplAhHmcHm,ZcplAhHmcVWm,cplAhcHmVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,             & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,        & 
& cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,GosZcplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,            & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,               & 
& cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRosAhToHmcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,GZcplAhHmcHm,ZcplAhHmcVWm,             & 
& cplAhcHmVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHmL,       & 
& cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,cplcgAgWmcVWm,cplcgZgWmcVWm,           & 
& cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,cplhhHmcVWm,cplhhcVWmVWm,           & 
& cplHmcHmVP,GZcplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,             & 
& cplAhAhcVWmVWm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,         & 
& AmpVertexIRosAhToHmcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,          & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& GcplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,             & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,        & 
& cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,GcplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,               & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,               & 
& cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRosAhToHmcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,       & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,          & 
& cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRosAhToHmcVWm)

 End if 
 End if 
AmpVertexAhToHmcVWm = AmpVertexAhToHmcVWm -  AmpVertexIRdrAhToHmcVWm! +  AmpVertexIRosAhToHmcVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhToHmcVWm=0._dp 
AmpVertexZAhToHmcVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhToHmcVWm(:,gt2,:) = AmpWaveZAhToHmcVWm(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWaveAhToHmcVWm(:,gt1,:) 
AmpVertexZAhToHmcVWm(:,gt2,:)= AmpVertexZAhToHmcVWm(:,gt2,:) + ZRUZA(gt2,gt1)*AmpVertexAhToHmcVWm(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhToHmcVWm=AmpWaveZAhToHmcVWm 
AmpVertexAhToHmcVWm= AmpVertexZAhToHmcVWm
! Final State 1 
AmpWaveZAhToHmcVWm=0._dp 
AmpVertexZAhToHmcVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhToHmcVWm(:,:,gt2) = AmpWaveZAhToHmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveAhToHmcVWm(:,:,gt1) 
AmpVertexZAhToHmcVWm(:,:,gt2)= AmpVertexZAhToHmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexAhToHmcVWm(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhToHmcVWm=AmpWaveZAhToHmcVWm 
AmpVertexAhToHmcVWm= AmpVertexZAhToHmcVWm
End if
If (ShiftIRdiv) Then 
AmpVertexAhToHmcVWm = AmpVertexAhToHmcVWm  +  AmpVertexIRosAhToHmcVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Hm conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhToHmcVWm = AmpTreeAhToHmcVWm 
 AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm + 2._dp*AmpWaveAhToHmcVWm + 2._dp*AmpVertexAhToHmcVWm  
Else 
 AmpSumAhToHmcVWm = AmpTreeAhToHmcVWm + AmpWaveAhToHmcVWm + AmpVertexAhToHmcVWm
 AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm + AmpWaveAhToHmcVWm + AmpVertexAhToHmcVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToHmcVWm = AmpTreeAhToHmcVWm
 AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MHm(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHm(gt2),MVWm,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhToHmcVWm(gt1, gt2) 
  AmpSum2AhToHmcVWm = 2._dp*AmpWaveAhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHm(gt2),MVWm,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhToHmcVWm(gt1, gt2) 
  AmpSum2AhToHmcVWm = 2._dp*AmpVertexAhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHm(gt2),MVWm,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhToHmcVWm(gt1, gt2) 
  AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm + 2._dp*AmpWaveAhToHmcVWm + 2._dp*AmpVertexAhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHm(gt2),MVWm,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhToHmcVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm
  Call SquareAmp_StoSV(MAhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
  AmpSqTreeAhToHmcVWm(gt1, gt2) = AmpSqAhToHmcVWm(gt1, gt2)  
  AmpSum2AhToHmcVWm = + 2._dp*AmpWaveAhToHmcVWm + 2._dp*AmpVertexAhToHmcVWm
  Call SquareAmp_StoSV(MAhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
  AmpSqAhToHmcVWm(gt1, gt2) = AmpSqAhToHmcVWm(gt1, gt2) + AmpSqTreeAhToHmcVWm(gt1, gt2)  
Else  
  AmpSum2AhToHmcVWm = AmpTreeAhToHmcVWm
  Call SquareAmp_StoSV(MAh(gt1),MHm(gt2),MVWm,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
  AmpSqTreeAhToHmcVWm(gt1, gt2) = AmpSqAhToHmcVWm(gt1, gt2)  
  AmpSum2AhToHmcVWm = + 2._dp*AmpWaveAhToHmcVWm + 2._dp*AmpVertexAhToHmcVWm
  Call SquareAmp_StoSV(MAh(gt1),MHm(gt2),MVWm,AmpSumAhToHmcVWm(:,gt1, gt2),AmpSum2AhToHmcVWm(:,gt1, gt2),AmpSqAhToHmcVWm(gt1, gt2)) 
  AmpSqAhToHmcVWm(gt1, gt2) = AmpSqAhToHmcVWm(gt1, gt2) + AmpSqTreeAhToHmcVWm(gt1, gt2)  
End if  
Else  
  AmpSqAhToHmcVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToHmcVWm(gt1, gt2).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAhOS(gt1),MHmOS(gt2),MVWmOS,helfactor*AmpSqAhToHmcVWm(gt1, gt2))
Else 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAh(gt1),MHm(gt2),MVWm,helfactor*AmpSqAhToHmcVWm(gt1, gt2))
End if 
If ((Abs(MRPAhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPAhToHmcVWm(gt1, gt2) + MRGAhToHmcVWm(gt1, gt2)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPAhToHmcVWm(gt1, gt2) + MRGAhToHmcVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
End If 
!---------------- 
! Ah VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToAhVP(MAhOS,MFdOS,MFeOS,MFuOS,MHmOS,               & 
& MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,AmpVertexAhToAhVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToAhVP(MAhOS,MFdOS,MFeOS,MFuOS,MHmOS,               & 
& MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,AmpVertexAhToAhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToAhVP(MAh,MFd,MFe,MFu,MHm,MVP,MVWm,MAh2,           & 
& MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,            & 
& cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,            & 
& cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,AmpVertexAhToAhVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Ah VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToAhVP = 0._dp 
 AmpSum2AhToAhVP = 0._dp  
Else 
 AmpSumAhToAhVP = AmpVertexAhToAhVP + AmpWaveAhToAhVP
 AmpSum2AhToAhVP = AmpVertexAhToAhVP + AmpWaveAhToAhVP 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MAh(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MAhOS(gt2),0._dp,AmpSumAhToAhVP(:,gt1, gt2),AmpSum2AhToAhVP(:,gt1, gt2),AmpSqAhToAhVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MAh(gt2),MVP,AmpSumAhToAhVP(:,gt1, gt2),AmpSum2AhToAhVP(:,gt1, gt2),AmpSqAhToAhVP(gt1, gt2)) 
End if  
Else  
  AmpSqAhToAhVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToAhVP(gt1, gt2).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MAhOS(gt2),0._dp,helfactor*AmpSqAhToAhVP(gt1, gt2))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MAh(gt2),MVP,helfactor*AmpSqAhToAhVP(gt1, gt2))
End if 
If ((Abs(MRPAhToAhVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhToAhVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! Ah VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToAhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,              & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,AmpVertexAhToAhVZ)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToAhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,              & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,AmpVertexAhToAhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,     & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,              & 
& cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,AmpVertexAhToAhVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Ah VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToAhVZ = 0._dp 
 AmpSum2AhToAhVZ = 0._dp  
Else 
 AmpSumAhToAhVZ = AmpVertexAhToAhVZ + AmpWaveAhToAhVZ
 AmpSum2AhToAhVZ = AmpVertexAhToAhVZ + AmpWaveAhToAhVZ 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MAh(gt2))+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MAhOS(gt2),MVZOS,AmpSumAhToAhVZ(:,gt1, gt2),AmpSum2AhToAhVZ(:,gt1, gt2),AmpSqAhToAhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MAh(gt2),MVZ,AmpSumAhToAhVZ(:,gt1, gt2),AmpSum2AhToAhVZ(:,gt1, gt2),AmpSqAhToAhVZ(gt1, gt2)) 
End if  
Else  
  AmpSqAhToAhVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToAhVZ(gt1, gt2).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MAhOS(gt2),MVZOS,helfactor*AmpSqAhToAhVZ(gt1, gt2))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MAh(gt2),MVZ,helfactor*AmpSqAhToAhVZ(gt1, gt2))
End if 
If ((Abs(MRPAhToAhVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhToAhVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! Fv bar(Fv)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToFvcFv(MAhOS,MFeOS,MHmOS,MVWmOS,MAh2OS,            & 
& MFe2OS,MHm2OS,MVWm2OS,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,      & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexAhToFvcFv)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToFvcFv(MAhOS,MFeOS,MHmOS,MVWmOS,MAh2OS,            & 
& MFe2OS,MHm2OS,MVWm2OS,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,      & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexAhToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToFvcFv(MAh,MFe,MHm,MVWm,MAh2,MFe2,MHm2,            & 
& MVWm2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFvFecHmL,         & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,AmpVertexAhToFvcFv)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Fv bar[Fv] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToFvcFv = 0._dp 
 AmpSum2AhToFvcFv = 0._dp  
Else 
 AmpSumAhToFvcFv = AmpVertexAhToFvcFv + AmpWaveAhToFvcFv
 AmpSum2AhToFvcFv = AmpVertexAhToFvcFv + AmpWaveAhToFvcFv 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(0._dp)+Abs(0._dp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),0._dp,0._dp,AmpSumAhToFvcFv(:,gt1, gt2, gt3),AmpSum2AhToFvcFv(:,gt1, gt2, gt3),AmpSqAhToFvcFv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),0._dp,0._dp,AmpSumAhToFvcFv(:,gt1, gt2, gt3),AmpSum2AhToFvcFv(:,gt1, gt2, gt3),AmpSqAhToFvcFv(gt1, gt2, gt3)) 
End if  
Else  
  AmpSqAhToFvcFv(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqAhToFvcFv(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),0._dp,0._dp,helfactor*AmpSqAhToFvcFv(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),0._dp,0._dp,helfactor*AmpSqAhToFvcFv(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhToFvcFv(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhToFvcFv(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! hh VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,            & 
& MhhOS,Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWaveAhTohhVP)

 Else 
Call Amplitude_WAVE_gumTHDMII_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,            & 
& MhhOS,Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWaveAhTohhVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhTohhVP(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,               & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,              & 
& cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,         & 
& cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,           & 
& cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,AmpVertexAhTohhVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhTohhVP(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,               & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,              & 
& cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,         & 
& cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,           & 
& cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,AmpVertexAhTohhVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,            & 
& Mhh2,MVP,MVP2,MVZ,MVZ2,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWaveAhTohhVP)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhTohhVP(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,    & 
& cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,              & 
& AmpVertexAhTohhVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->hh VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTohhVP = 0._dp 
 AmpSum2AhTohhVP = 0._dp  
Else 
 AmpSumAhTohhVP = AmpVertexAhTohhVP + AmpWaveAhTohhVP
 AmpSum2AhTohhVP = AmpVertexAhTohhVP + AmpWaveAhTohhVP 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(Mhh(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MhhOS(gt2),0._dp,AmpSumAhTohhVP(:,gt1, gt2),AmpSum2AhTohhVP(:,gt1, gt2),AmpSqAhTohhVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),Mhh(gt2),MVP,AmpSumAhTohhVP(:,gt1, gt2),AmpSum2AhTohhVP(:,gt1, gt2),AmpSqAhTohhVP(gt1, gt2)) 
End if  
Else  
  AmpSqAhTohhVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTohhVP(gt1, gt2).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MhhOS(gt2),0._dp,helfactor*AmpSqAhTohhVP(gt1, gt2))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),Mhh(gt2),MVP,helfactor*AmpSqAhTohhVP(gt1, gt2))
End if 
If ((Abs(MRPAhTohhVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhTohhVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VG VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToVGVG(MAhOS,MFdOS,MFuOS,MVG,MAh2OS,MFd2OS,         & 
& MFu2OS,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexAhToVGVG)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToVGVG(MAhOS,MFdOS,MFuOS,MVG,MAh2OS,MFd2OS,         & 
& MFu2OS,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexAhToVGVG)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToVGVG(MAh,MFd,MFu,MVG,MAh2,MFd2,MFu2,              & 
& MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVGL,cplcFdFdVGR,          & 
& cplcFuFuVGL,cplcFuFuVGR,AmpVertexAhToVGVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->VG VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToVGVG = 0._dp 
 AmpSum2AhToVGVG = 0._dp  
Else 
 AmpSumAhToVGVG = AmpVertexAhToVGVG + AmpWaveAhToVGVG
 AmpSum2AhToVGVG = AmpVertexAhToVGVG + AmpWaveAhToVGVG 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MVG)+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MAhOS(gt1),0._dp,0._dp,AmpSumAhToVGVG(:,gt1),AmpSum2AhToVGVG(:,gt1),AmpSqAhToVGVG(gt1)) 
Else  
  Call SquareAmp_StoVV(MAh(gt1),MVG,MVG,AmpSumAhToVGVG(:,gt1),AmpSum2AhToVGVG(:,gt1),AmpSqAhToVGVG(gt1)) 
End if  
Else  
  AmpSqAhToVGVG(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToVGVG(gt1).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 8._dp*GammaTPS(MAhOS(gt1),0._dp,0._dp,helfactor*AmpSqAhToVGVG(gt1))
Else 
  gP1LAh(gt1,i4) = 8._dp*GammaTPS(MAh(gt1),MVG,MVG,helfactor*AmpSqAhToVGVG(gt1))
End if 
If ((Abs(MRPAhToVGVG(gt1)).gt.1.0E-20_dp).or.(Abs(MRGAhToVGVG(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VP VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToVPVP(MAhOS,MFdOS,MFeOS,MFuOS,MHmOS,               & 
& MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplHmcHmVPVP1,AmpVertexAhToVPVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToVPVP(MAhOS,MFdOS,MFeOS,MFuOS,MHmOS,               & 
& MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,    & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplHmcHmVPVP1,AmpVertexAhToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToVPVP(MAh,MFd,MFe,MFu,MHm,MVP,MVWm,MAh2,           & 
& MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,            & 
& cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,            & 
& cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplHmcHmVPVP1,AmpVertexAhToVPVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->VP VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToVPVP = 0._dp 
 AmpSum2AhToVPVP = 0._dp  
Else 
 AmpSumAhToVPVP = AmpVertexAhToVPVP + AmpWaveAhToVPVP
 AmpSum2AhToVPVP = AmpVertexAhToVPVP + AmpWaveAhToVPVP 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MVP)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MAhOS(gt1),0._dp,0._dp,AmpSumAhToVPVP(:,gt1),AmpSum2AhToVPVP(:,gt1),AmpSqAhToVPVP(gt1)) 
Else  
  Call SquareAmp_StoVV(MAh(gt1),MVP,MVP,AmpSumAhToVPVP(:,gt1),AmpSum2AhToVPVP(:,gt1),AmpSqAhToVPVP(gt1)) 
End if  
Else  
  AmpSqAhToVPVP(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToVPVP(gt1).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),0._dp,0._dp,helfactor*AmpSqAhToVPVP(gt1))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MVP,MVP,helfactor*AmpSqAhToVPVP(gt1))
End if 
If ((Abs(MRPAhToVPVP(gt1)).gt.1.0E-20_dp).or.(Abs(MRGAhToVPVP(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VP VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToVPVZ(MAhOS,MFdOS,MFeOS,MFuOS,MHmOS,               & 
& MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,               & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,            & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,          & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVP1,          & 
& cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplHmcHmVPVZ1,AmpVertexAhToVPVZ)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToVPVZ(MAhOS,MFdOS,MFeOS,MFuOS,MHmOS,               & 
& MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,               & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,            & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,          & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhHmcVWmVP1,          & 
& cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplHmcHmVPVZ1,AmpVertexAhToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToVPVZ(MAh,MFd,MFe,MFu,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,       & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,    & 
& cplcVWmVWmVZ,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,              & 
& cplHmcHmVPVZ1,AmpVertexAhToVPVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->VP VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToVPVZ = 0._dp 
 AmpSum2AhToVPVZ = 0._dp  
Else 
 AmpSumAhToVPVZ = AmpVertexAhToVPVZ + AmpWaveAhToVPVZ
 AmpSum2AhToVPVZ = AmpVertexAhToVPVZ + AmpWaveAhToVPVZ 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(0.)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MVP)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MAhOS(gt1),0._dp,MVZOS,AmpSumAhToVPVZ(:,gt1),AmpSum2AhToVPVZ(:,gt1),AmpSqAhToVPVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(MAh(gt1),MVP,MVZ,AmpSumAhToVPVZ(:,gt1),AmpSum2AhToVPVZ(:,gt1),AmpSqAhToVPVZ(gt1)) 
End if  
Else  
  AmpSqAhToVPVZ(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToVPVZ(gt1).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAhOS(gt1),0._dp,MVZOS,helfactor*AmpSqAhToVPVZ(gt1))
Else 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAh(gt1),MVP,MVZ,helfactor*AmpSqAhToVPVZ(gt1))
End if 
If ((Abs(MRPAhToVPVZ(gt1)).gt.1.0E-20_dp).or.(Abs(MRGAhToVPVZ(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VWm Conjg(VWm)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToVWmcVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,          & 
& cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWmgAVWm,        & 
& cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,   & 
& cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,           & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,      & 
& cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplHmcHmcVWmVWm1,         & 
& AmpVertexAhToVWmcVWm)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToVWmcVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,            & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,          & 
& cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgWmgAVWm,        & 
& cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,   & 
& cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,           & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,      & 
& cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplHmcHmcVWmVWm1,         & 
& AmpVertexAhToVWmcVWm)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToVWmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,     & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcHmVWm,       & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,             & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,             & 
& cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplHmcHmcVWmVWm1,AmpVertexAhToVWmcVWm)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->VWm conj[VWm] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToVWmcVWm = 0._dp 
 AmpSum2AhToVWmcVWm = 0._dp  
Else 
 AmpSumAhToVWmcVWm = AmpVertexAhToVWmcVWm + AmpWaveAhToVWmcVWm
 AmpSum2AhToVWmcVWm = AmpVertexAhToVWmcVWm + AmpWaveAhToVWmcVWm 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MVWmOS)+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MVWm)+Abs(MVWm))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MAhOS(gt1),MVWmOS,MVWmOS,AmpSumAhToVWmcVWm(:,gt1),AmpSum2AhToVWmcVWm(:,gt1),AmpSqAhToVWmcVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(MAh(gt1),MVWm,MVWm,AmpSumAhToVWmcVWm(:,gt1),AmpSum2AhToVWmcVWm(:,gt1),AmpSqAhToVWmcVWm(gt1)) 
End if  
Else  
  AmpSqAhToVWmcVWm(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToVWmcVWm(gt1).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAhOS(gt1),MVWmOS,MVWmOS,helfactor*AmpSqAhToVWmcVWm(gt1))
Else 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAh(gt1),MVWm,MVWm,helfactor*AmpSqAhToVWmcVWm(gt1))
End if 
If ((Abs(MRPAhToVWmcVWm(gt1)).gt.1.0E-20_dp).or.(Abs(MRGAhToVWmcVWm(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
!---------------- 
! VZ VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_AhToVZVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,     & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,              & 
& cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplHmcHmVZVZ1,    & 
& AmpVertexAhToVZVZ)

 Else 
Call Amplitude_VERTEX_gumTHDMII_AhToVZVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,     & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,              & 
& cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplHmcHmVZVZ1,    & 
& AmpVertexAhToVZVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_AhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplcFdFdAhL,cplcFdFdAhR,            & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,cplcFdFdVZR,        & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1, & 
& cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplHmcHmVZVZ1,AmpVertexAhToVZVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->VZ VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToVZVZ = 0._dp 
 AmpSum2AhToVZVZ = 0._dp  
Else 
 AmpSumAhToVZVZ = AmpVertexAhToVZVZ + AmpWaveAhToVZVZ
 AmpSum2AhToVZVZ = AmpVertexAhToVZVZ + AmpWaveAhToVZVZ 
End If 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MVZOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MVZ)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MAhOS(gt1),MVZOS,MVZOS,AmpSumAhToVZVZ(:,gt1),AmpSum2AhToVZVZ(:,gt1),AmpSqAhToVZVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(MAh(gt1),MVZ,MVZ,AmpSumAhToVZVZ(:,gt1),AmpSum2AhToVZVZ(:,gt1),AmpSqAhToVZVZ(gt1)) 
End if  
Else  
  AmpSqAhToVZVZ(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToVZVZ(gt1).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MVZOS,MVZOS,helfactor*AmpSqAhToVZVZ(gt1))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MVZ,MVZ,helfactor*AmpSqAhToVZVZ(gt1))
End if 
If ((Abs(MRPAhToVZVZ(gt1)).gt.1.0E-20_dp).or.(Abs(MRGAhToVZVZ(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End Subroutine OneLoopDecay_Ah

End Module Wrapper_OneLoopDecay_Ah_gumTHDMII
