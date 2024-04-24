! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_hh_gumTHDMII
Use Model_Data_gumTHDMII 
Use Kinematics 
Use OneLoopDecay_hh_gumTHDMII 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_hh(MhhOS,Mhh2OS,MAhOS,MAh2OS,MHmOS,MHm2OS,MFdOS,              & 
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
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgAgWmcVWm,        & 
& cplcgAgWpCVWm,cplcgWmgAHm,cplcgWmgAVWm,cplcgWmgWmAh,cplcgWmgWmhh,cplcgWmgWmVP,         & 
& cplcgWmgWmVZ,cplcgWmgZHm,cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh,cplcgWpCgWpChh,    & 
& cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcgWpCgZcHm,cplcgWpCgZcVWm,cplcgZgAhh,cplcgZgWmcHm,    & 
& cplcgZgWmcVWm,cplcgZgWpCHm,cplcgZgWpCVWm,cplcgZgZhh,cplcHmVPVWm,cplcHmVWmVZ,           & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVPVPVWm1Q,          & 
& cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,      & 
& cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,      & 
& cplhhcHmVPVWm1,cplhhcHmVWm,cplhhcHmVWmVZ1,cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,      & 
& cplhhhhhhhh1,cplhhhhHmcHm1,cplhhhhVZVZ1,cplhhHmcHm,cplhhHmcVWm,cplhhHmcVWmVP1,         & 
& cplhhHmcVWmVZ1,cplhhVZVZ,cplHmcHmcVWmVWm1,cplHmcHmVP,cplHmcHmVPVP1,cplHmcHmVPVZ1,      & 
& cplHmcHmVZ,cplHmcHmVZVZ1,cplHmcVWmVP,cplHmcVWmVZ,cplHmHmcHmcHm1,ctcplAhAhhh,           & 
& ctcplAhhhhh,ctcplAhhhVZ,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFeFehhL,ctcplcFeFehhR,       & 
& ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplhhcVWmVWm,ctcplhhhhhh,ctcplhhHmcHm,ctcplhhHmcVWm,     & 
& ctcplhhVZVZ,GcplcHmVPVWm,GcplhhcHmVWm,GcplhhHmcHm,GcplHmcVWmVP,GosZcplcHmVPVWm,        & 
& GosZcplhhcHmVWm,GosZcplhhHmcHm,GosZcplHmcVWmVP,GZcplcHmVPVWm,GZcplhhcHmVWm,            & 
& GZcplhhHmcHm,GZcplHmcVWmVP,ZcplAhAhhh,ZcplAhhhhh,ZcplAhhhVZ,ZcplcFdFdhhL,              & 
& ZcplcFdFdhhR,ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplhhcVWmVWm,        & 
& Zcplhhhhhh,ZcplhhHmcHm,ZcplhhHmcVWm,ZcplhhVZVZ,ZRUZH,ZRUZA,ZRUZP,ZRUVd,ZRUUd,          & 
& ZRUVu,ZRUUu,ZRUVe,ZRUUe,MLambda,em,gs,deltaM,kont,gP1Lhh)

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
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHm(2),          & 
& cplcgWmgAVWm,cplcgWmgWmAh(2),cplcgWmgWmhh(2),cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHm(2), & 
& cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh(2),cplcgWpCgWpChh(2),cplcgWpCgWpCVP,        & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHm(2),cplcgWpCgZcVWm,cplcgZgAhh(2),cplcgZgWmcHm(2),          & 
& cplcgZgWmcVWm,cplcgZgWpCHm(2),cplcgZgWpCVWm,cplcgZgZhh(2),cplcHmVPVWm(2),              & 
& cplcHmVWmVZ(2),cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,            & 
& cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,cplcVWmVPVWmVZ1Q,      & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,      & 
& cplcVWmVWmVZVZ3Q,cplhhcHmVPVWm1(2,2),cplhhcHmVWm(2,2),cplhhcHmVWmVZ1(2,2),             & 
& cplhhcVWmVWm(2),cplhhhhcVWmVWm1(2,2),cplhhhhhh(2,2,2),cplhhhhhhhh1(2,2,2,2),           & 
& cplhhhhHmcHm1(2,2,2,2),cplhhhhVZVZ1(2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),           & 
& cplhhHmcVWmVP1(2,2),cplhhHmcVWmVZ1(2,2),cplhhVZVZ(2),cplHmcHmcVWmVWm1(2,2),            & 
& cplHmcHmVP(2,2),cplHmcHmVPVP1(2,2),cplHmcHmVPVZ1(2,2),cplHmcHmVZ(2,2),cplHmcHmVZVZ1(2,2),& 
& cplHmcVWmVP(2),cplHmcVWmVZ(2),cplHmHmcHmcHm1(2,2,2,2),ctcplAhAhhh(2,2,2),              & 
& ctcplAhhhhh(2,2,2),ctcplAhhhVZ(2,2),ctcplcFdFdhhL(3,3,2),ctcplcFdFdhhR(3,3,2),         & 
& ctcplcFeFehhL(3,3,2),ctcplcFeFehhR(3,3,2),ctcplcFuFuhhL(3,3,2),ctcplcFuFuhhR(3,3,2),   & 
& ctcplhhcVWmVWm(2),ctcplhhhhhh(2,2,2),ctcplhhHmcHm(2,2,2),ctcplhhHmcVWm(2,2),           & 
& ctcplhhVZVZ(2),GcplcHmVPVWm(2),GcplhhcHmVWm(2,2),GcplhhHmcHm(2,2,2),GcplHmcVWmVP(2),   & 
& GosZcplcHmVPVWm(2),GosZcplhhcHmVWm(2,2),GosZcplhhHmcHm(2,2,2),GosZcplHmcVWmVP(2),      & 
& GZcplcHmVPVWm(2),GZcplhhcHmVWm(2,2),GZcplhhHmcHm(2,2,2),GZcplHmcVWmVP(2),              & 
& ZcplAhAhhh(2,2,2),ZcplAhhhhh(2,2,2),ZcplAhhhVZ(2,2),ZcplcFdFdhhL(3,3,2),               & 
& ZcplcFdFdhhR(3,3,2),ZcplcFeFehhL(3,3,2),ZcplcFeFehhR(3,3,2),ZcplcFuFuhhL(3,3,2)

Complex(dp),Intent(in) :: ZcplcFuFuhhR(3,3,2),ZcplhhcVWmVWm(2),Zcplhhhhhh(2,2,2),ZcplhhHmcHm(2,2,2),             & 
& ZcplhhHmcVWm(2,2),ZcplhhVZVZ(2)

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
Real(dp), Intent(out) :: gP1Lhh(2,59) 
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
Real(dp) :: MRPhhToAhAh(2,2,2),MRGhhToAhAh(2,2,2), MRPZhhToAhAh(2,2,2),MRGZhhToAhAh(2,2,2) 
Real(dp) :: MVPhhToAhAh(2,2,2) 
Real(dp) :: RMsqTreehhToAhAh(2,2,2),RMsqWavehhToAhAh(2,2,2),RMsqVertexhhToAhAh(2,2,2) 
Complex(dp) :: AmpTreehhToAhAh(2,2,2),AmpWavehhToAhAh(2,2,2)=(0._dp,0._dp),AmpVertexhhToAhAh(2,2,2)& 
 & ,AmpVertexIRoshhToAhAh(2,2,2),AmpVertexIRdrhhToAhAh(2,2,2), AmpSumhhToAhAh(2,2,2), AmpSum2hhToAhAh(2,2,2) 
Complex(dp) :: AmpTreeZhhToAhAh(2,2,2),AmpWaveZhhToAhAh(2,2,2),AmpVertexZhhToAhAh(2,2,2) 
Real(dp) :: AmpSqhhToAhAh(2,2,2),  AmpSqTreehhToAhAh(2,2,2) 
Real(dp) :: MRPhhTohhAh(2,2,2),MRGhhTohhAh(2,2,2), MRPZhhTohhAh(2,2,2),MRGZhhTohhAh(2,2,2) 
Real(dp) :: MVPhhTohhAh(2,2,2) 
Real(dp) :: RMsqTreehhTohhAh(2,2,2),RMsqWavehhTohhAh(2,2,2),RMsqVertexhhTohhAh(2,2,2) 
Complex(dp) :: AmpTreehhTohhAh(2,2,2),AmpWavehhTohhAh(2,2,2)=(0._dp,0._dp),AmpVertexhhTohhAh(2,2,2)& 
 & ,AmpVertexIRoshhTohhAh(2,2,2),AmpVertexIRdrhhTohhAh(2,2,2), AmpSumhhTohhAh(2,2,2), AmpSum2hhTohhAh(2,2,2) 
Complex(dp) :: AmpTreeZhhTohhAh(2,2,2),AmpWaveZhhTohhAh(2,2,2),AmpVertexZhhTohhAh(2,2,2) 
Real(dp) :: AmpSqhhTohhAh(2,2,2),  AmpSqTreehhTohhAh(2,2,2) 
Real(dp) :: MRPhhToAhVZ(2,2),MRGhhToAhVZ(2,2), MRPZhhToAhVZ(2,2),MRGZhhToAhVZ(2,2) 
Real(dp) :: MVPhhToAhVZ(2,2) 
Real(dp) :: RMsqTreehhToAhVZ(2,2),RMsqWavehhToAhVZ(2,2),RMsqVertexhhToAhVZ(2,2) 
Complex(dp) :: AmpTreehhToAhVZ(2,2,2),AmpWavehhToAhVZ(2,2,2)=(0._dp,0._dp),AmpVertexhhToAhVZ(2,2,2)& 
 & ,AmpVertexIRoshhToAhVZ(2,2,2),AmpVertexIRdrhhToAhVZ(2,2,2), AmpSumhhToAhVZ(2,2,2), AmpSum2hhToAhVZ(2,2,2) 
Complex(dp) :: AmpTreeZhhToAhVZ(2,2,2),AmpWaveZhhToAhVZ(2,2,2),AmpVertexZhhToAhVZ(2,2,2) 
Real(dp) :: AmpSqhhToAhVZ(2,2),  AmpSqTreehhToAhVZ(2,2) 
Real(dp) :: MRPhhTocFdFd(2,3,3),MRGhhTocFdFd(2,3,3), MRPZhhTocFdFd(2,3,3),MRGZhhTocFdFd(2,3,3) 
Real(dp) :: MVPhhTocFdFd(2,3,3) 
Real(dp) :: RMsqTreehhTocFdFd(2,3,3),RMsqWavehhTocFdFd(2,3,3),RMsqVertexhhTocFdFd(2,3,3) 
Complex(dp) :: AmpTreehhTocFdFd(2,2,3,3),AmpWavehhTocFdFd(2,2,3,3)=(0._dp,0._dp),AmpVertexhhTocFdFd(2,2,3,3)& 
 & ,AmpVertexIRoshhTocFdFd(2,2,3,3),AmpVertexIRdrhhTocFdFd(2,2,3,3), AmpSumhhTocFdFd(2,2,3,3), AmpSum2hhTocFdFd(2,2,3,3) 
Complex(dp) :: AmpTreeZhhTocFdFd(2,2,3,3),AmpWaveZhhTocFdFd(2,2,3,3),AmpVertexZhhTocFdFd(2,2,3,3) 
Real(dp) :: AmpSqhhTocFdFd(2,3,3),  AmpSqTreehhTocFdFd(2,3,3) 
Real(dp) :: MRPhhTocFeFe(2,3,3),MRGhhTocFeFe(2,3,3), MRPZhhTocFeFe(2,3,3),MRGZhhTocFeFe(2,3,3) 
Real(dp) :: MVPhhTocFeFe(2,3,3) 
Real(dp) :: RMsqTreehhTocFeFe(2,3,3),RMsqWavehhTocFeFe(2,3,3),RMsqVertexhhTocFeFe(2,3,3) 
Complex(dp) :: AmpTreehhTocFeFe(2,2,3,3),AmpWavehhTocFeFe(2,2,3,3)=(0._dp,0._dp),AmpVertexhhTocFeFe(2,2,3,3)& 
 & ,AmpVertexIRoshhTocFeFe(2,2,3,3),AmpVertexIRdrhhTocFeFe(2,2,3,3), AmpSumhhTocFeFe(2,2,3,3), AmpSum2hhTocFeFe(2,2,3,3) 
Complex(dp) :: AmpTreeZhhTocFeFe(2,2,3,3),AmpWaveZhhTocFeFe(2,2,3,3),AmpVertexZhhTocFeFe(2,2,3,3) 
Real(dp) :: AmpSqhhTocFeFe(2,3,3),  AmpSqTreehhTocFeFe(2,3,3) 
Real(dp) :: MRPhhTocFuFu(2,3,3),MRGhhTocFuFu(2,3,3), MRPZhhTocFuFu(2,3,3),MRGZhhTocFuFu(2,3,3) 
Real(dp) :: MVPhhTocFuFu(2,3,3) 
Real(dp) :: RMsqTreehhTocFuFu(2,3,3),RMsqWavehhTocFuFu(2,3,3),RMsqVertexhhTocFuFu(2,3,3) 
Complex(dp) :: AmpTreehhTocFuFu(2,2,3,3),AmpWavehhTocFuFu(2,2,3,3)=(0._dp,0._dp),AmpVertexhhTocFuFu(2,2,3,3)& 
 & ,AmpVertexIRoshhTocFuFu(2,2,3,3),AmpVertexIRdrhhTocFuFu(2,2,3,3), AmpSumhhTocFuFu(2,2,3,3), AmpSum2hhTocFuFu(2,2,3,3) 
Complex(dp) :: AmpTreeZhhTocFuFu(2,2,3,3),AmpWaveZhhTocFuFu(2,2,3,3),AmpVertexZhhTocFuFu(2,2,3,3) 
Real(dp) :: AmpSqhhTocFuFu(2,3,3),  AmpSqTreehhTocFuFu(2,3,3) 
Real(dp) :: MRPhhTohhhh(2,2,2),MRGhhTohhhh(2,2,2), MRPZhhTohhhh(2,2,2),MRGZhhTohhhh(2,2,2) 
Real(dp) :: MVPhhTohhhh(2,2,2) 
Real(dp) :: RMsqTreehhTohhhh(2,2,2),RMsqWavehhTohhhh(2,2,2),RMsqVertexhhTohhhh(2,2,2) 
Complex(dp) :: AmpTreehhTohhhh(2,2,2),AmpWavehhTohhhh(2,2,2)=(0._dp,0._dp),AmpVertexhhTohhhh(2,2,2)& 
 & ,AmpVertexIRoshhTohhhh(2,2,2),AmpVertexIRdrhhTohhhh(2,2,2), AmpSumhhTohhhh(2,2,2), AmpSum2hhTohhhh(2,2,2) 
Complex(dp) :: AmpTreeZhhTohhhh(2,2,2),AmpWaveZhhTohhhh(2,2,2),AmpVertexZhhTohhhh(2,2,2) 
Real(dp) :: AmpSqhhTohhhh(2,2,2),  AmpSqTreehhTohhhh(2,2,2) 
Real(dp) :: MRPhhTocHmHm(2,2,2),MRGhhTocHmHm(2,2,2), MRPZhhTocHmHm(2,2,2),MRGZhhTocHmHm(2,2,2) 
Real(dp) :: MVPhhTocHmHm(2,2,2) 
Real(dp) :: RMsqTreehhTocHmHm(2,2,2),RMsqWavehhTocHmHm(2,2,2),RMsqVertexhhTocHmHm(2,2,2) 
Complex(dp) :: AmpTreehhTocHmHm(2,2,2),AmpWavehhTocHmHm(2,2,2)=(0._dp,0._dp),AmpVertexhhTocHmHm(2,2,2)& 
 & ,AmpVertexIRoshhTocHmHm(2,2,2),AmpVertexIRdrhhTocHmHm(2,2,2), AmpSumhhTocHmHm(2,2,2), AmpSum2hhTocHmHm(2,2,2) 
Complex(dp) :: AmpTreeZhhTocHmHm(2,2,2),AmpWaveZhhTocHmHm(2,2,2),AmpVertexZhhTocHmHm(2,2,2) 
Real(dp) :: AmpSqhhTocHmHm(2,2,2),  AmpSqTreehhTocHmHm(2,2,2) 
Real(dp) :: MRPhhToHmcVWm(2,2),MRGhhToHmcVWm(2,2), MRPZhhToHmcVWm(2,2),MRGZhhToHmcVWm(2,2) 
Real(dp) :: MVPhhToHmcVWm(2,2) 
Real(dp) :: RMsqTreehhToHmcVWm(2,2),RMsqWavehhToHmcVWm(2,2),RMsqVertexhhToHmcVWm(2,2) 
Complex(dp) :: AmpTreehhToHmcVWm(2,2,2),AmpWavehhToHmcVWm(2,2,2)=(0._dp,0._dp),AmpVertexhhToHmcVWm(2,2,2)& 
 & ,AmpVertexIRoshhToHmcVWm(2,2,2),AmpVertexIRdrhhToHmcVWm(2,2,2), AmpSumhhToHmcVWm(2,2,2), AmpSum2hhToHmcVWm(2,2,2) 
Complex(dp) :: AmpTreeZhhToHmcVWm(2,2,2),AmpWaveZhhToHmcVWm(2,2,2),AmpVertexZhhToHmcVWm(2,2,2) 
Real(dp) :: AmpSqhhToHmcVWm(2,2),  AmpSqTreehhToHmcVWm(2,2) 
Real(dp) :: MRPhhTocVWmVWm(2),MRGhhTocVWmVWm(2), MRPZhhTocVWmVWm(2),MRGZhhTocVWmVWm(2) 
Real(dp) :: MVPhhTocVWmVWm(2) 
Real(dp) :: RMsqTreehhTocVWmVWm(2),RMsqWavehhTocVWmVWm(2),RMsqVertexhhTocVWmVWm(2) 
Complex(dp) :: AmpTreehhTocVWmVWm(2,2),AmpWavehhTocVWmVWm(2,2)=(0._dp,0._dp),AmpVertexhhTocVWmVWm(2,2)& 
 & ,AmpVertexIRoshhTocVWmVWm(2,2),AmpVertexIRdrhhTocVWmVWm(2,2), AmpSumhhTocVWmVWm(2,2), AmpSum2hhTocVWmVWm(2,2) 
Complex(dp) :: AmpTreeZhhTocVWmVWm(2,2),AmpWaveZhhTocVWmVWm(2,2),AmpVertexZhhTocVWmVWm(2,2) 
Real(dp) :: AmpSqhhTocVWmVWm(2),  AmpSqTreehhTocVWmVWm(2) 
Real(dp) :: MRPhhToVZVZ(2),MRGhhToVZVZ(2), MRPZhhToVZVZ(2),MRGZhhToVZVZ(2) 
Real(dp) :: MVPhhToVZVZ(2) 
Real(dp) :: RMsqTreehhToVZVZ(2),RMsqWavehhToVZVZ(2),RMsqVertexhhToVZVZ(2) 
Complex(dp) :: AmpTreehhToVZVZ(2,2),AmpWavehhToVZVZ(2,2)=(0._dp,0._dp),AmpVertexhhToVZVZ(2,2)& 
 & ,AmpVertexIRoshhToVZVZ(2,2),AmpVertexIRdrhhToVZVZ(2,2), AmpSumhhToVZVZ(2,2), AmpSum2hhToVZVZ(2,2) 
Complex(dp) :: AmpTreeZhhToVZVZ(2,2),AmpWaveZhhToVZVZ(2,2),AmpVertexZhhToVZVZ(2,2) 
Real(dp) :: AmpSqhhToVZVZ(2),  AmpSqTreehhToVZVZ(2) 
Real(dp) :: MRPhhToAhVP(2,2),MRGhhToAhVP(2,2), MRPZhhToAhVP(2,2),MRGZhhToAhVP(2,2) 
Real(dp) :: MVPhhToAhVP(2,2) 
Real(dp) :: RMsqTreehhToAhVP(2,2),RMsqWavehhToAhVP(2,2),RMsqVertexhhToAhVP(2,2) 
Complex(dp) :: AmpTreehhToAhVP(2,2,2),AmpWavehhToAhVP(2,2,2)=(0._dp,0._dp),AmpVertexhhToAhVP(2,2,2)& 
 & ,AmpVertexIRoshhToAhVP(2,2,2),AmpVertexIRdrhhToAhVP(2,2,2), AmpSumhhToAhVP(2,2,2), AmpSum2hhToAhVP(2,2,2) 
Complex(dp) :: AmpTreeZhhToAhVP(2,2,2),AmpWaveZhhToAhVP(2,2,2),AmpVertexZhhToAhVP(2,2,2) 
Real(dp) :: AmpSqhhToAhVP(2,2),  AmpSqTreehhToAhVP(2,2) 
Real(dp) :: MRPhhToFvcFv(2,3,3),MRGhhToFvcFv(2,3,3), MRPZhhToFvcFv(2,3,3),MRGZhhToFvcFv(2,3,3) 
Real(dp) :: MVPhhToFvcFv(2,3,3) 
Real(dp) :: RMsqTreehhToFvcFv(2,3,3),RMsqWavehhToFvcFv(2,3,3),RMsqVertexhhToFvcFv(2,3,3) 
Complex(dp) :: AmpTreehhToFvcFv(2,2,3,3),AmpWavehhToFvcFv(2,2,3,3)=(0._dp,0._dp),AmpVertexhhToFvcFv(2,2,3,3)& 
 & ,AmpVertexIRoshhToFvcFv(2,2,3,3),AmpVertexIRdrhhToFvcFv(2,2,3,3), AmpSumhhToFvcFv(2,2,3,3), AmpSum2hhToFvcFv(2,2,3,3) 
Complex(dp) :: AmpTreeZhhToFvcFv(2,2,3,3),AmpWaveZhhToFvcFv(2,2,3,3),AmpVertexZhhToFvcFv(2,2,3,3) 
Real(dp) :: AmpSqhhToFvcFv(2,3,3),  AmpSqTreehhToFvcFv(2,3,3) 
Real(dp) :: MRPhhTohhVP(2,2),MRGhhTohhVP(2,2), MRPZhhTohhVP(2,2),MRGZhhTohhVP(2,2) 
Real(dp) :: MVPhhTohhVP(2,2) 
Real(dp) :: RMsqTreehhTohhVP(2,2),RMsqWavehhTohhVP(2,2),RMsqVertexhhTohhVP(2,2) 
Complex(dp) :: AmpTreehhTohhVP(2,2,2),AmpWavehhTohhVP(2,2,2)=(0._dp,0._dp),AmpVertexhhTohhVP(2,2,2)& 
 & ,AmpVertexIRoshhTohhVP(2,2,2),AmpVertexIRdrhhTohhVP(2,2,2), AmpSumhhTohhVP(2,2,2), AmpSum2hhTohhVP(2,2,2) 
Complex(dp) :: AmpTreeZhhTohhVP(2,2,2),AmpWaveZhhTohhVP(2,2,2),AmpVertexZhhTohhVP(2,2,2) 
Real(dp) :: AmpSqhhTohhVP(2,2),  AmpSqTreehhTohhVP(2,2) 
Real(dp) :: MRPhhTohhVZ(2,2),MRGhhTohhVZ(2,2), MRPZhhTohhVZ(2,2),MRGZhhTohhVZ(2,2) 
Real(dp) :: MVPhhTohhVZ(2,2) 
Real(dp) :: RMsqTreehhTohhVZ(2,2),RMsqWavehhTohhVZ(2,2),RMsqVertexhhTohhVZ(2,2) 
Complex(dp) :: AmpTreehhTohhVZ(2,2,2),AmpWavehhTohhVZ(2,2,2)=(0._dp,0._dp),AmpVertexhhTohhVZ(2,2,2)& 
 & ,AmpVertexIRoshhTohhVZ(2,2,2),AmpVertexIRdrhhTohhVZ(2,2,2), AmpSumhhTohhVZ(2,2,2), AmpSum2hhTohhVZ(2,2,2) 
Complex(dp) :: AmpTreeZhhTohhVZ(2,2,2),AmpWaveZhhTohhVZ(2,2,2),AmpVertexZhhTohhVZ(2,2,2) 
Real(dp) :: AmpSqhhTohhVZ(2,2),  AmpSqTreehhTohhVZ(2,2) 
Real(dp) :: MRPhhToVGVG(2),MRGhhToVGVG(2), MRPZhhToVGVG(2),MRGZhhToVGVG(2) 
Real(dp) :: MVPhhToVGVG(2) 
Real(dp) :: RMsqTreehhToVGVG(2),RMsqWavehhToVGVG(2),RMsqVertexhhToVGVG(2) 
Complex(dp) :: AmpTreehhToVGVG(2,2),AmpWavehhToVGVG(2,2)=(0._dp,0._dp),AmpVertexhhToVGVG(2,2)& 
 & ,AmpVertexIRoshhToVGVG(2,2),AmpVertexIRdrhhToVGVG(2,2), AmpSumhhToVGVG(2,2), AmpSum2hhToVGVG(2,2) 
Complex(dp) :: AmpTreeZhhToVGVG(2,2),AmpWaveZhhToVGVG(2,2),AmpVertexZhhToVGVG(2,2) 
Real(dp) :: AmpSqhhToVGVG(2),  AmpSqTreehhToVGVG(2) 
Real(dp) :: MRPhhToVPVP(2),MRGhhToVPVP(2), MRPZhhToVPVP(2),MRGZhhToVPVP(2) 
Real(dp) :: MVPhhToVPVP(2) 
Real(dp) :: RMsqTreehhToVPVP(2),RMsqWavehhToVPVP(2),RMsqVertexhhToVPVP(2) 
Complex(dp) :: AmpTreehhToVPVP(2,2),AmpWavehhToVPVP(2,2)=(0._dp,0._dp),AmpVertexhhToVPVP(2,2)& 
 & ,AmpVertexIRoshhToVPVP(2,2),AmpVertexIRdrhhToVPVP(2,2), AmpSumhhToVPVP(2,2), AmpSum2hhToVPVP(2,2) 
Complex(dp) :: AmpTreeZhhToVPVP(2,2),AmpWaveZhhToVPVP(2,2),AmpVertexZhhToVPVP(2,2) 
Real(dp) :: AmpSqhhToVPVP(2),  AmpSqTreehhToVPVP(2) 
Real(dp) :: MRPhhToVPVZ(2),MRGhhToVPVZ(2), MRPZhhToVPVZ(2),MRGZhhToVPVZ(2) 
Real(dp) :: MVPhhToVPVZ(2) 
Real(dp) :: RMsqTreehhToVPVZ(2),RMsqWavehhToVPVZ(2),RMsqVertexhhToVPVZ(2) 
Complex(dp) :: AmpTreehhToVPVZ(2,2),AmpWavehhToVPVZ(2,2)=(0._dp,0._dp),AmpVertexhhToVPVZ(2,2)& 
 & ,AmpVertexIRoshhToVPVZ(2,2),AmpVertexIRdrhhToVPVZ(2,2), AmpSumhhToVPVZ(2,2), AmpSum2hhToVPVZ(2,2) 
Complex(dp) :: AmpTreeZhhToVPVZ(2,2),AmpWaveZhhToVPVZ(2,2),AmpVertexZhhToVPVZ(2,2) 
Real(dp) :: AmpSqhhToVPVZ(2),  AmpSqTreehhToVPVZ(2) 
Write(*,*) "Calculating one-loop decays of hh " 
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
isave = 5

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Ah Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_hhToAhAh(cplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhToAhAh)

  Else 
Call Amplitude_Tree_gumTHDMII_hhToAhAh(ZcplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhToAhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhToAhAh(MLambda,em,gs,cplAhAhhh,MAhOS,MhhOS,               & 
& MRPhhToAhAh,MRGhhToAhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhToAhAh(MLambda,em,gs,ZcplAhAhhh,MAhOS,MhhOS,              & 
& MRPhhToAhAh,MRGhhToAhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhToAhAh(MLambda,em,gs,cplAhAhhh,MAh,Mhh,MRPhhToAhAh,       & 
& MRGhhToAhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhToAhAh(MLambda,em,gs,ZcplAhAhhh,MAh,Mhh,MRPhhToAhAh,      & 
& MRGhhToAhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhToAhAh(cplAhAhhh,ctcplAhAhhh,MAh,MAh2,Mhh,            & 
& Mhh2,ZfAh,Zfhh,AmpWavehhToAhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexhhToAhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRdrhhToAhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,ZcplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,             & 
& cplAhAhHmcHm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRoshhToAhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,ZcplAhAhhh,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRoshhToAhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,             & 
& cplAhAhHmcHm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRoshhToAhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,AmpVertexIRoshhToAhAh)

 End if 
 End if 
AmpVertexhhToAhAh = AmpVertexhhToAhAh -  AmpVertexIRdrhhToAhAh! +  AmpVertexIRoshhToAhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToAhAh=0._dp 
AmpVertexZhhToAhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToAhAh(gt2,:,:) = AmpWaveZhhToAhAh(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhToAhAh(gt1,:,:) 
AmpVertexZhhToAhAh(gt2,:,:)= AmpVertexZhhToAhAh(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhToAhAh(gt1,:,:) 
 End Do 
End Do 
AmpWavehhToAhAh=AmpWaveZhhToAhAh 
AmpVertexhhToAhAh= AmpVertexZhhToAhAh
! Final State 1 
AmpWaveZhhToAhAh=0._dp 
AmpVertexZhhToAhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToAhAh(:,gt2,:) = AmpWaveZhhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWavehhToAhAh(:,gt1,:) 
AmpVertexZhhToAhAh(:,gt2,:)= AmpVertexZhhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpVertexhhToAhAh(:,gt1,:) 
 End Do 
End Do 
AmpWavehhToAhAh=AmpWaveZhhToAhAh 
AmpVertexhhToAhAh= AmpVertexZhhToAhAh
! Final State 2 
AmpWaveZhhToAhAh=0._dp 
AmpVertexZhhToAhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToAhAh(:,:,gt2) = AmpWaveZhhToAhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWavehhToAhAh(:,:,gt1) 
AmpVertexZhhToAhAh(:,:,gt2)= AmpVertexZhhToAhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexhhToAhAh(:,:,gt1) 
 End Do 
End Do 
AmpWavehhToAhAh=AmpWaveZhhToAhAh 
AmpVertexhhToAhAh= AmpVertexZhhToAhAh
End if
If (ShiftIRdiv) Then 
AmpVertexhhToAhAh = AmpVertexhhToAhAh  +  AmpVertexIRoshhToAhAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Ah Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToAhAh = AmpTreehhToAhAh 
 AmpSum2hhToAhAh = AmpTreehhToAhAh + 2._dp*AmpWavehhToAhAh + 2._dp*AmpVertexhhToAhAh  
Else 
 AmpSumhhToAhAh = AmpTreehhToAhAh + AmpWavehhToAhAh + AmpVertexhhToAhAh
 AmpSum2hhToAhAh = AmpTreehhToAhAh + AmpWavehhToAhAh + AmpVertexhhToAhAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToAhAh = AmpTreehhToAhAh
 AmpSum2hhToAhAh = AmpTreehhToAhAh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
    Do gt3=gt2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MAh(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhToAhAh = AmpTreehhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MAh(gt2),MAh(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToAhAh(gt1, gt2, gt3) 
  AmpSum2hhToAhAh = 2._dp*AmpWavehhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MAh(gt2),MAh(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToAhAh(gt1, gt2, gt3) 
  AmpSum2hhToAhAh = 2._dp*AmpVertexhhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MAh(gt2),MAh(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToAhAh(gt1, gt2, gt3) 
  AmpSum2hhToAhAh = AmpTreehhToAhAh + 2._dp*AmpWavehhToAhAh + 2._dp*AmpVertexhhToAhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MAh(gt2),MAh(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToAhAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToAhAh = AmpTreehhToAhAh
  Call SquareAmp_StoSS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
  AmpSqTreehhToAhAh(gt1, gt2, gt3) = AmpSqhhToAhAh(gt1, gt2, gt3)  
  AmpSum2hhToAhAh = + 2._dp*AmpWavehhToAhAh + 2._dp*AmpVertexhhToAhAh
  Call SquareAmp_StoSS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
  AmpSqhhToAhAh(gt1, gt2, gt3) = AmpSqhhToAhAh(gt1, gt2, gt3) + AmpSqTreehhToAhAh(gt1, gt2, gt3)  
Else  
  AmpSum2hhToAhAh = AmpTreehhToAhAh
  Call SquareAmp_StoSS(Mhh(gt1),MAh(gt2),MAh(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
  AmpSqTreehhToAhAh(gt1, gt2, gt3) = AmpSqhhToAhAh(gt1, gt2, gt3)  
  AmpSum2hhToAhAh = + 2._dp*AmpWavehhToAhAh + 2._dp*AmpVertexhhToAhAh
  Call SquareAmp_StoSS(Mhh(gt1),MAh(gt2),MAh(gt3),AmpSumhhToAhAh(gt1, gt2, gt3),AmpSum2hhToAhAh(gt1, gt2, gt3),AmpSqhhToAhAh(gt1, gt2, gt3)) 
  AmpSqhhToAhAh(gt1, gt2, gt3) = AmpSqhhToAhAh(gt1, gt2, gt3) + AmpSqTreehhToAhAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhToAhAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (gt2.ne.gt3) helfactor = 2._dp*helfactor 
If (AmpSqhhToAhAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(MhhOS(gt1),MAhOS(gt2),MAhOS(gt3),helfactor*AmpSqhhToAhAh(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(Mhh(gt1),MAh(gt2),MAh(gt3),helfactor*AmpSqhhToAhAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhToAhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToAhAh(gt1, gt2, gt3) + MRGhhToAhAh(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToAhAh(gt1, gt2, gt3) + MRGhhToAhAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
Call Amplitude_Tree_gumTHDMII_hhTohhAh(cplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhTohhAh)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTohhAh(ZcplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhTohhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTohhAh(MLambda,em,gs,cplAhhhhh,MAhOS,MhhOS,               & 
& MRPhhTohhAh,MRGhhTohhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTohhAh(MLambda,em,gs,ZcplAhhhhh,MAhOS,MhhOS,              & 
& MRPhhTohhAh,MRGhhTohhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTohhAh(MLambda,em,gs,cplAhhhhh,MAh,Mhh,MRPhhTohhAh,       & 
& MRGhhTohhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTohhAh(MLambda,em,gs,ZcplAhhhhh,MAh,Mhh,MRPhhTohhAh,      & 
& MRGhhTohhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTohhAh(cplAhhhhh,ctcplAhhhhh,MAh,MAh2,Mhh,            & 
& Mhh2,ZfAh,Zfhh,AmpWavehhTohhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexhhTohhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexIRdrhhTohhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHmcHm,               & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,              & 
& cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,           & 
& cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,AmpVertexIRoshhTohhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexIRoshhTohhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhAh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,         & 
& cplhhhhhhhh1,cplhhhhHmcHm1,AmpVertexIRoshhTohhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,       & 
& AmpVertexIRoshhTohhAh)

 End if 
 End if 
AmpVertexhhTohhAh = AmpVertexhhTohhAh -  AmpVertexIRdrhhTohhAh! +  AmpVertexIRoshhTohhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTohhAh=0._dp 
AmpVertexZhhTohhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTohhAh(gt2,:,:) = AmpWaveZhhTohhAh(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhAh(gt1,:,:) 
AmpVertexZhhTohhAh(gt2,:,:)= AmpVertexZhhTohhAh(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTohhAh(gt1,:,:) 
 End Do 
End Do 
AmpWavehhTohhAh=AmpWaveZhhTohhAh 
AmpVertexhhTohhAh= AmpVertexZhhTohhAh
! Final State 1 
AmpWaveZhhTohhAh=0._dp 
AmpVertexZhhTohhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTohhAh(:,gt2,:) = AmpWaveZhhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhAh(:,gt1,:) 
AmpVertexZhhTohhAh(:,gt2,:)= AmpVertexZhhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexhhTohhAh(:,gt1,:) 
 End Do 
End Do 
AmpWavehhTohhAh=AmpWaveZhhTohhAh 
AmpVertexhhTohhAh= AmpVertexZhhTohhAh
! Final State 2 
AmpWaveZhhTohhAh=0._dp 
AmpVertexZhhTohhAh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTohhAh(:,:,gt2) = AmpWaveZhhTohhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWavehhTohhAh(:,:,gt1) 
AmpVertexZhhTohhAh(:,:,gt2)= AmpVertexZhhTohhAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexhhTohhAh(:,:,gt1) 
 End Do 
End Do 
AmpWavehhTohhAh=AmpWaveZhhTohhAh 
AmpVertexhhTohhAh= AmpVertexZhhTohhAh
End if
If (ShiftIRdiv) Then 
AmpVertexhhTohhAh = AmpVertexhhTohhAh  +  AmpVertexIRoshhTohhAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->hh Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTohhAh = AmpTreehhTohhAh 
 AmpSum2hhTohhAh = AmpTreehhTohhAh + 2._dp*AmpWavehhTohhAh + 2._dp*AmpVertexhhTohhAh  
Else 
 AmpSumhhTohhAh = AmpTreehhTohhAh + AmpWavehhTohhAh + AmpVertexhhTohhAh
 AmpSum2hhTohhAh = AmpTreehhTohhAh + AmpWavehhTohhAh + AmpVertexhhTohhAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTohhAh = AmpTreehhTohhAh
 AmpSum2hhTohhAh = AmpTreehhTohhAh 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(Mhh(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTohhAh = AmpTreehhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),MAh(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTohhAh(gt1, gt2, gt3) 
  AmpSum2hhTohhAh = 2._dp*AmpWavehhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),MAh(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTohhAh(gt1, gt2, gt3) 
  AmpSum2hhTohhAh = 2._dp*AmpVertexhhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),MAh(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTohhAh(gt1, gt2, gt3) 
  AmpSum2hhTohhAh = AmpTreehhTohhAh + 2._dp*AmpWavehhTohhAh + 2._dp*AmpVertexhhTohhAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),MAh(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTohhAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTohhAh = AmpTreehhTohhAh
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
  AmpSqTreehhTohhAh(gt1, gt2, gt3) = AmpSqhhTohhAh(gt1, gt2, gt3)  
  AmpSum2hhTohhAh = + 2._dp*AmpWavehhTohhAh + 2._dp*AmpVertexhhTohhAh
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
  AmpSqhhTohhAh(gt1, gt2, gt3) = AmpSqhhTohhAh(gt1, gt2, gt3) + AmpSqTreehhTohhAh(gt1, gt2, gt3)  
Else  
  AmpSum2hhTohhAh = AmpTreehhTohhAh
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),MAh(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
  AmpSqTreehhTohhAh(gt1, gt2, gt3) = AmpSqhhTohhAh(gt1, gt2, gt3)  
  AmpSum2hhTohhAh = + 2._dp*AmpWavehhTohhAh + 2._dp*AmpVertexhhTohhAh
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),MAh(gt3),AmpSumhhTohhAh(gt1, gt2, gt3),AmpSum2hhTohhAh(gt1, gt2, gt3),AmpSqhhTohhAh(gt1, gt2, gt3)) 
  AmpSqhhTohhAh(gt1, gt2, gt3) = AmpSqhhTohhAh(gt1, gt2, gt3) + AmpSqTreehhTohhAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTohhAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTohhAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MhhOS(gt2),MAhOS(gt3),helfactor*AmpSqhhTohhAh(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),Mhh(gt2),MAh(gt3),helfactor*AmpSqhhTohhAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTohhAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTohhAh(gt1, gt2, gt3) + MRGhhTohhAh(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTohhAh(gt1, gt2, gt3) + MRGhhTohhAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! Ah VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_hhToAhVZ(cplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,               & 
& MVZ2,AmpTreehhToAhVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_hhToAhVZ(ZcplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,              & 
& MVZ2,AmpTreehhToAhVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhToAhVZ(MLambda,em,gs,cplAhhhVZ,MAhOS,MhhOS,               & 
& MVZOS,MRPhhToAhVZ,MRGhhToAhVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhToAhVZ(MLambda,em,gs,ZcplAhhhVZ,MAhOS,MhhOS,              & 
& MVZOS,MRPhhToAhVZ,MRGhhToAhVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhToAhVZ(MLambda,em,gs,cplAhhhVZ,MAh,Mhh,MVZ,               & 
& MRPhhToAhVZ,MRGhhToAhVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhToAhVZ(MLambda,em,gs,ZcplAhhhVZ,MAh,Mhh,MVZ,              & 
& MRPhhToAhVZ,MRGhhToAhVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhToAhVZ(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,            & 
& Mhh2,MVZ,MVZ2,ZfAh,Zfhh,ZfVZ,AmpWavehhToAhVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexhhToAhVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexIRdrhhToAhVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHmcHm,               & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,        & 
& cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,       & 
& cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexIRoshhToAhVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexIRoshhToAhVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,       & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,    & 
& cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,               & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,      & 
& cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexIRoshhToAhVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1, & 
& AmpVertexIRoshhToAhVZ)

 End if 
 End if 
AmpVertexhhToAhVZ = AmpVertexhhToAhVZ -  AmpVertexIRdrhhToAhVZ! +  AmpVertexIRoshhToAhVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToAhVZ=0._dp 
AmpVertexZhhToAhVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToAhVZ(:,gt2,:) = AmpWaveZhhToAhVZ(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhToAhVZ(:,gt1,:) 
AmpVertexZhhToAhVZ(:,gt2,:)= AmpVertexZhhToAhVZ(:,gt2,:) + ZRUZH(gt2,gt1)*AmpVertexhhToAhVZ(:,gt1,:) 
 End Do 
End Do 
AmpWavehhToAhVZ=AmpWaveZhhToAhVZ 
AmpVertexhhToAhVZ= AmpVertexZhhToAhVZ
! Final State 1 
AmpWaveZhhToAhVZ=0._dp 
AmpVertexZhhToAhVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToAhVZ(:,:,gt2) = AmpWaveZhhToAhVZ(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWavehhToAhVZ(:,:,gt1) 
AmpVertexZhhToAhVZ(:,:,gt2)= AmpVertexZhhToAhVZ(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexhhToAhVZ(:,:,gt1) 
 End Do 
End Do 
AmpWavehhToAhVZ=AmpWaveZhhToAhVZ 
AmpVertexhhToAhVZ= AmpVertexZhhToAhVZ
End if
If (ShiftIRdiv) Then 
AmpVertexhhToAhVZ = AmpVertexhhToAhVZ  +  AmpVertexIRoshhToAhVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Ah VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToAhVZ = AmpTreehhToAhVZ 
 AmpSum2hhToAhVZ = AmpTreehhToAhVZ + 2._dp*AmpWavehhToAhVZ + 2._dp*AmpVertexhhToAhVZ  
Else 
 AmpSumhhToAhVZ = AmpTreehhToAhVZ + AmpWavehhToAhVZ + AmpVertexhhToAhVZ
 AmpSum2hhToAhVZ = AmpTreehhToAhVZ + AmpWavehhToAhVZ + AmpVertexhhToAhVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToAhVZ = AmpTreehhToAhVZ
 AmpSum2hhToAhVZ = AmpTreehhToAhVZ 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MAh(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2hhToAhVZ = AmpTreehhToAhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),MVZOS,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVZ,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToAhVZ(gt1, gt2) 
  AmpSum2hhToAhVZ = 2._dp*AmpWavehhToAhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),MVZOS,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVZ,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToAhVZ(gt1, gt2) 
  AmpSum2hhToAhVZ = 2._dp*AmpVertexhhToAhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),MVZOS,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVZ,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToAhVZ(gt1, gt2) 
  AmpSum2hhToAhVZ = AmpTreehhToAhVZ + 2._dp*AmpWavehhToAhVZ + 2._dp*AmpVertexhhToAhVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),MVZOS,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVZ,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToAhVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToAhVZ = AmpTreehhToAhVZ
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),MVZOS,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
  AmpSqTreehhToAhVZ(gt1, gt2) = AmpSqhhToAhVZ(gt1, gt2)  
  AmpSum2hhToAhVZ = + 2._dp*AmpWavehhToAhVZ + 2._dp*AmpVertexhhToAhVZ
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),MVZOS,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
  AmpSqhhToAhVZ(gt1, gt2) = AmpSqhhToAhVZ(gt1, gt2) + AmpSqTreehhToAhVZ(gt1, gt2)  
Else  
  AmpSum2hhToAhVZ = AmpTreehhToAhVZ
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVZ,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
  AmpSqTreehhToAhVZ(gt1, gt2) = AmpSqhhToAhVZ(gt1, gt2)  
  AmpSum2hhToAhVZ = + 2._dp*AmpWavehhToAhVZ + 2._dp*AmpVertexhhToAhVZ
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVZ,AmpSumhhToAhVZ(:,gt1, gt2),AmpSum2hhToAhVZ(:,gt1, gt2),AmpSqhhToAhVZ(gt1, gt2)) 
  AmpSqhhToAhVZ(gt1, gt2) = AmpSqhhToAhVZ(gt1, gt2) + AmpSqTreehhToAhVZ(gt1, gt2)  
End if  
Else  
  AmpSqhhToAhVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToAhVZ(gt1, gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MAhOS(gt2),MVZOS,helfactor*AmpSqhhToAhVZ(gt1, gt2))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MAh(gt2),MVZ,helfactor*AmpSqhhToAhVZ(gt1, gt2))
End if 
If ((Abs(MRPhhToAhVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToAhVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToAhVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToAhVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPhhToAhVZ(gt1, gt2) + MRGhhToAhVZ(gt1, gt2)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPhhToAhVZ(gt1, gt2) + MRGhhToAhVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! bar(Fd) Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,MFd,Mhh,              & 
& MFd2,Mhh2,AmpTreehhTocFdFd)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTocFdFd(ZcplcFdFdhhL,ZcplcFdFdhhR,MFd,Mhh,            & 
& MFd2,Mhh2,AmpTreehhTocFdFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,            & 
& MFdOS,MhhOS,MRPhhTocFdFd,MRGhhTocFdFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFdFd(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,          & 
& MFdOS,MhhOS,MRPhhTocFdFd,MRGhhTocFdFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,            & 
& MFd,Mhh,MRPhhTocFdFd,MRGhhTocFdFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFdFd(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,          & 
& MFd,Mhh,MRPhhTocFdFd,MRGhhTocFdFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,        & 
& ctcplcFdFdhhR,MFd,MFd2,Mhh,Mhh2,ZfDL,ZfDR,Zfhh,AmpWavehhTocFdFd)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,               & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexhhTocFdFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRdrhhTocFdFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFdFd(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,ZcplcFdFdhhL,             & 
& ZcplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,              & 
& cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,     & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRoshhTocFdFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFdFd(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRoshhTocFdFd)

 End if 
 End if 
AmpVertexhhTocFdFd = AmpVertexhhTocFdFd -  AmpVertexIRdrhhTocFdFd! +  AmpVertexIRoshhTocFdFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocFdFd(:,gt2,:,:) = AmpWaveZhhTocFdFd(:,gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTocFdFd(:,gt1,:,:) 
AmpVertexZhhTocFdFd(:,gt2,:,:)= AmpVertexZhhTocFdFd(:,gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTocFdFd(:,gt1,:,:) 
 End Do 
End Do 
AmpWavehhTocFdFd=AmpWaveZhhTocFdFd 
AmpVertexhhTocFdFd= AmpVertexZhhTocFdFd
! Final State 1 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFdFd(1,:,gt2,:) = AmpWaveZhhTocFdFd(1,:,gt2,:)+ZRUUd(gt2,gt1)*AmpWavehhTocFdFd(1,:,gt1,:) 
AmpVertexZhhTocFdFd(1,:,gt2,:)= AmpVertexZhhTocFdFd(1,:,gt2,:)+ZRUUd(gt2,gt1)*AmpVertexhhTocFdFd(1,:,gt1,:) 
AmpWaveZhhTocFdFd(2,:,gt2,:) = AmpWaveZhhTocFdFd(2,:,gt2,:)+ZRUVdc(gt2,gt1)*AmpWavehhTocFdFd(2,:,gt1,:) 
AmpVertexZhhTocFdFd(2,:,gt2,:)= AmpVertexZhhTocFdFd(2,:,gt2,:)+ZRUVdc(gt2,gt1)*AmpVertexhhTocFdFd(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFdFd=AmpWaveZhhTocFdFd 
AmpVertexhhTocFdFd= AmpVertexZhhTocFdFd
! Final State 2 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFdFd(1,:,:,gt2) = AmpWaveZhhTocFdFd(1,:,:,gt2)+ZRUVd(gt2,gt1)*AmpWavehhTocFdFd(1,:,:,gt1) 
AmpVertexZhhTocFdFd(1,:,:,gt2)= AmpVertexZhhTocFdFd(1,:,:,gt2)+ZRUVd(gt2,gt1)*AmpVertexhhTocFdFd(1,:,:,gt1) 
AmpWaveZhhTocFdFd(2,:,:,gt2) = AmpWaveZhhTocFdFd(2,:,:,gt2)+ZRUUd(gt2,gt1)*AmpWavehhTocFdFd(2,:,:,gt1) 
AmpVertexZhhTocFdFd(2,:,:,gt2)= AmpVertexZhhTocFdFd(2,:,:,gt2)+ZRUUd(gt2,gt1)*AmpVertexhhTocFdFd(2,:,:,gt1) 
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
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MFd(gt2))+Abs(MFd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocFdFd(gt1, gt2, gt3) 
  AmpSum2hhTocFdFd = 2._dp*AmpWavehhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocFdFd(gt1, gt2, gt3) 
  AmpSum2hhTocFdFd = 2._dp*AmpVertexhhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocFdFd(gt1, gt2, gt3) 
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocFdFd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd
  Call SquareAmp_StoFF(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
  AmpSqTreehhTocFdFd(gt1, gt2, gt3) = AmpSqhhTocFdFd(gt1, gt2, gt3)  
  AmpSum2hhTocFdFd = + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd
  Call SquareAmp_StoFF(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
  AmpSqhhTocFdFd(gt1, gt2, gt3) = AmpSqhhTocFdFd(gt1, gt2, gt3) + AmpSqTreehhTocFdFd(gt1, gt2, gt3)  
Else  
  AmpSum2hhTocFdFd = AmpTreehhTocFdFd
  Call SquareAmp_StoFF(Mhh(gt1),MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
  AmpSqTreehhTocFdFd(gt1, gt2, gt3) = AmpSqhhTocFdFd(gt1, gt2, gt3)  
  AmpSum2hhTocFdFd = + 2._dp*AmpWavehhTocFdFd + 2._dp*AmpVertexhhTocFdFd
  Call SquareAmp_StoFF(Mhh(gt1),MFd(gt2),MFd(gt3),AmpSumhhTocFdFd(:,gt1, gt2, gt3),AmpSum2hhTocFdFd(:,gt1, gt2, gt3),AmpSqhhTocFdFd(gt1, gt2, gt3)) 
  AmpSqhhTocFdFd(gt1, gt2, gt3) = AmpSqhhTocFdFd(gt1, gt2, gt3) + AmpSqTreehhTocFdFd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTocFdFd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocFdFd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(MhhOS(gt1),MFdOS(gt2),MFdOS(gt3),helfactor*AmpSqhhTocFdFd(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(Mhh(gt1),MFd(gt2),MFd(gt3),helfactor*AmpSqhhTocFdFd(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFdFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocFdFd(gt1, gt2, gt3) + MRGhhTocFdFd(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocFdFd(gt1, gt2, gt3) + MRGhhTocFdFd(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
Call Amplitude_Tree_gumTHDMII_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,MFe,Mhh,              & 
& MFe2,Mhh2,AmpTreehhTocFeFe)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTocFeFe(ZcplcFeFehhL,ZcplcFeFehhR,MFe,Mhh,            & 
& MFe2,Mhh2,AmpTreehhTocFeFe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,            & 
& MFeOS,MhhOS,MRPhhTocFeFe,MRGhhTocFeFe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFeFe(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,          & 
& MFeOS,MhhOS,MRPhhTocFeFe,MRGhhTocFeFe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,            & 
& MFe,Mhh,MRPhhTocFeFe,MRGhhTocFeFe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFeFe(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,          & 
& MFe,Mhh,MRPhhTocFeFe,MRGhhTocFeFe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,ctcplcFeFehhL,        & 
& ctcplcFeFehhR,MFe,MFe2,Mhh,Mhh2,ZfEL,ZfER,Zfhh,AmpWavehhTocFeFe)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,               & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexhhTocFeFe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRdrhhTocFeFe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFeFe(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplcFeFeAhL,    & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,ZcplcFeFehhL,ZcplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,    & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,ZcplcFeFehhL,ZcplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,         & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,    & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFeFe(MAhOS,MFeOS,MhhOS,MHmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplcFeFeAhL,    & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,       & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,    & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,       & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,AmpVertexIRoshhTocFeFe)

 End if 
 End if 
AmpVertexhhTocFeFe = AmpVertexhhTocFeFe -  AmpVertexIRdrhhTocFeFe! +  AmpVertexIRoshhTocFeFe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocFeFe(:,gt2,:,:) = AmpWaveZhhTocFeFe(:,gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTocFeFe(:,gt1,:,:) 
AmpVertexZhhTocFeFe(:,gt2,:,:)= AmpVertexZhhTocFeFe(:,gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTocFeFe(:,gt1,:,:) 
 End Do 
End Do 
AmpWavehhTocFeFe=AmpWaveZhhTocFeFe 
AmpVertexhhTocFeFe= AmpVertexZhhTocFeFe
! Final State 1 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFeFe(1,:,gt2,:) = AmpWaveZhhTocFeFe(1,:,gt2,:)+ZRUUe(gt2,gt1)*AmpWavehhTocFeFe(1,:,gt1,:) 
AmpVertexZhhTocFeFe(1,:,gt2,:)= AmpVertexZhhTocFeFe(1,:,gt2,:)+ZRUUe(gt2,gt1)*AmpVertexhhTocFeFe(1,:,gt1,:) 
AmpWaveZhhTocFeFe(2,:,gt2,:) = AmpWaveZhhTocFeFe(2,:,gt2,:)+ZRUVec(gt2,gt1)*AmpWavehhTocFeFe(2,:,gt1,:) 
AmpVertexZhhTocFeFe(2,:,gt2,:)= AmpVertexZhhTocFeFe(2,:,gt2,:)+ZRUVec(gt2,gt1)*AmpVertexhhTocFeFe(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFeFe=AmpWaveZhhTocFeFe 
AmpVertexhhTocFeFe= AmpVertexZhhTocFeFe
! Final State 2 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFeFe(1,:,:,gt2) = AmpWaveZhhTocFeFe(1,:,:,gt2)+ZRUVe(gt2,gt1)*AmpWavehhTocFeFe(1,:,:,gt1) 
AmpVertexZhhTocFeFe(1,:,:,gt2)= AmpVertexZhhTocFeFe(1,:,:,gt2)+ZRUVe(gt2,gt1)*AmpVertexhhTocFeFe(1,:,:,gt1) 
AmpWaveZhhTocFeFe(2,:,:,gt2) = AmpWaveZhhTocFeFe(2,:,:,gt2)+ZRUUe(gt2,gt1)*AmpWavehhTocFeFe(2,:,:,gt1) 
AmpVertexZhhTocFeFe(2,:,:,gt2)= AmpVertexZhhTocFeFe(2,:,:,gt2)+ZRUUe(gt2,gt1)*AmpVertexhhTocFeFe(2,:,:,gt1) 
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
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MFeOS(gt2))+Abs(MFeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MFe(gt2))+Abs(MFe(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocFeFe(gt1, gt2, gt3) 
  AmpSum2hhTocFeFe = 2._dp*AmpWavehhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocFeFe(gt1, gt2, gt3) 
  AmpSum2hhTocFeFe = 2._dp*AmpVertexhhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocFeFe(gt1, gt2, gt3) 
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocFeFe(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe
  Call SquareAmp_StoFF(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
  AmpSqTreehhTocFeFe(gt1, gt2, gt3) = AmpSqhhTocFeFe(gt1, gt2, gt3)  
  AmpSum2hhTocFeFe = + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe
  Call SquareAmp_StoFF(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
  AmpSqhhTocFeFe(gt1, gt2, gt3) = AmpSqhhTocFeFe(gt1, gt2, gt3) + AmpSqTreehhTocFeFe(gt1, gt2, gt3)  
Else  
  AmpSum2hhTocFeFe = AmpTreehhTocFeFe
  Call SquareAmp_StoFF(Mhh(gt1),MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
  AmpSqTreehhTocFeFe(gt1, gt2, gt3) = AmpSqhhTocFeFe(gt1, gt2, gt3)  
  AmpSum2hhTocFeFe = + 2._dp*AmpWavehhTocFeFe + 2._dp*AmpVertexhhTocFeFe
  Call SquareAmp_StoFF(Mhh(gt1),MFe(gt2),MFe(gt3),AmpSumhhTocFeFe(:,gt1, gt2, gt3),AmpSum2hhTocFeFe(:,gt1, gt2, gt3),AmpSqhhTocFeFe(gt1, gt2, gt3)) 
  AmpSqhhTocFeFe(gt1, gt2, gt3) = AmpSqhhTocFeFe(gt1, gt2, gt3) + AmpSqTreehhTocFeFe(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTocFeFe(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocFeFe(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MFeOS(gt2),MFeOS(gt3),helfactor*AmpSqhhTocFeFe(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MFe(gt2),MFe(gt3),helfactor*AmpSqhhTocFeFe(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFeFe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocFeFe(gt1, gt2, gt3) + MRGhhTocFeFe(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocFeFe(gt1, gt2, gt3) + MRGhhTocFeFe(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
Call Amplitude_Tree_gumTHDMII_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,MFu,Mhh,              & 
& MFu2,Mhh2,AmpTreehhTocFuFu)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTocFuFu(ZcplcFuFuhhL,ZcplcFuFuhhR,MFu,Mhh,            & 
& MFu2,Mhh2,AmpTreehhTocFuFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,            & 
& MFuOS,MhhOS,MRPhhTocFuFu,MRGhhTocFuFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFuFu(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,          & 
& MFuOS,MhhOS,MRPhhTocFuFu,MRGhhTocFuFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,            & 
& MFu,Mhh,MRPhhTocFuFu,MRGhhTocFuFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocFuFu(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,          & 
& MFu,Mhh,MRPhhTocFuFu,MRGhhTocFuFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,        & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,Zfhh,ZfUL,ZfUR,AmpWavehhTocFuFu)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,               & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexhhTocFuFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexIRdrhhTocFuFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFuFu(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,ZcplcFuFuhhL,        & 
& ZcplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexIRoshhTocFuFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFuFu(MAhOS,MFdOS,MFuOS,MhhOS,MHmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHm2OS,MVG2,MVP2,MVWm2OS,             & 
& MVZ2OS,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,               & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,          & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,AmpVertexIRoshhTocFuFu)

 End if 
 End if 
AmpVertexhhTocFuFu = AmpVertexhhTocFuFu -  AmpVertexIRdrhhTocFuFu! +  AmpVertexIRoshhTocFuFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocFuFu(:,gt2,:,:) = AmpWaveZhhTocFuFu(:,gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTocFuFu(:,gt1,:,:) 
AmpVertexZhhTocFuFu(:,gt2,:,:)= AmpVertexZhhTocFuFu(:,gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTocFuFu(:,gt1,:,:) 
 End Do 
End Do 
AmpWavehhTocFuFu=AmpWaveZhhTocFuFu 
AmpVertexhhTocFuFu= AmpVertexZhhTocFuFu
! Final State 1 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFuFu(1,:,gt2,:) = AmpWaveZhhTocFuFu(1,:,gt2,:)+ZRUUu(gt2,gt1)*AmpWavehhTocFuFu(1,:,gt1,:) 
AmpVertexZhhTocFuFu(1,:,gt2,:)= AmpVertexZhhTocFuFu(1,:,gt2,:)+ZRUUu(gt2,gt1)*AmpVertexhhTocFuFu(1,:,gt1,:) 
AmpWaveZhhTocFuFu(2,:,gt2,:) = AmpWaveZhhTocFuFu(2,:,gt2,:)+ZRUVuc(gt2,gt1)*AmpWavehhTocFuFu(2,:,gt1,:) 
AmpVertexZhhTocFuFu(2,:,gt2,:)= AmpVertexZhhTocFuFu(2,:,gt2,:)+ZRUVuc(gt2,gt1)*AmpVertexhhTocFuFu(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFuFu=AmpWaveZhhTocFuFu 
AmpVertexhhTocFuFu= AmpVertexZhhTocFuFu
! Final State 2 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFuFu(1,:,:,gt2) = AmpWaveZhhTocFuFu(1,:,:,gt2)+ZRUVu(gt2,gt1)*AmpWavehhTocFuFu(1,:,:,gt1) 
AmpVertexZhhTocFuFu(1,:,:,gt2)= AmpVertexZhhTocFuFu(1,:,:,gt2)+ZRUVu(gt2,gt1)*AmpVertexhhTocFuFu(1,:,:,gt1) 
AmpWaveZhhTocFuFu(2,:,:,gt2) = AmpWaveZhhTocFuFu(2,:,:,gt2)+ZRUUu(gt2,gt1)*AmpWavehhTocFuFu(2,:,:,gt1) 
AmpVertexZhhTocFuFu(2,:,:,gt2)= AmpVertexZhhTocFuFu(2,:,:,gt2)+ZRUUu(gt2,gt1)*AmpVertexhhTocFuFu(2,:,:,gt1) 
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
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MFu(gt2))+Abs(MFu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocFuFu(gt1, gt2, gt3) 
  AmpSum2hhTocFuFu = 2._dp*AmpWavehhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocFuFu(gt1, gt2, gt3) 
  AmpSum2hhTocFuFu = 2._dp*AmpVertexhhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocFuFu(gt1, gt2, gt3) 
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocFuFu(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu
  Call SquareAmp_StoFF(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
  AmpSqTreehhTocFuFu(gt1, gt2, gt3) = AmpSqhhTocFuFu(gt1, gt2, gt3)  
  AmpSum2hhTocFuFu = + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu
  Call SquareAmp_StoFF(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
  AmpSqhhTocFuFu(gt1, gt2, gt3) = AmpSqhhTocFuFu(gt1, gt2, gt3) + AmpSqTreehhTocFuFu(gt1, gt2, gt3)  
Else  
  AmpSum2hhTocFuFu = AmpTreehhTocFuFu
  Call SquareAmp_StoFF(Mhh(gt1),MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
  AmpSqTreehhTocFuFu(gt1, gt2, gt3) = AmpSqhhTocFuFu(gt1, gt2, gt3)  
  AmpSum2hhTocFuFu = + 2._dp*AmpWavehhTocFuFu + 2._dp*AmpVertexhhTocFuFu
  Call SquareAmp_StoFF(Mhh(gt1),MFu(gt2),MFu(gt3),AmpSumhhTocFuFu(:,gt1, gt2, gt3),AmpSum2hhTocFuFu(:,gt1, gt2, gt3),AmpSqhhTocFuFu(gt1, gt2, gt3)) 
  AmpSqhhTocFuFu(gt1, gt2, gt3) = AmpSqhhTocFuFu(gt1, gt2, gt3) + AmpSqTreehhTocFuFu(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTocFuFu(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocFuFu(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(MhhOS(gt1),MFuOS(gt2),MFuOS(gt3),helfactor*AmpSqhhTocFuFu(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 3._dp*GammaTPS(Mhh(gt1),MFu(gt2),MFu(gt3),helfactor*AmpSqhhTocFuFu(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocFuFu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocFuFu(gt1, gt2, gt3) + MRGhhTocFuFu(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocFuFu(gt1, gt2, gt3) + MRGhhTocFuFu(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
Call Amplitude_Tree_gumTHDMII_hhTohhhh(cplhhhhhh,Mhh,Mhh2,AmpTreehhTohhhh)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTohhhh(Zcplhhhhhh,Mhh,Mhh2,AmpTreehhTohhhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTohhhh(MLambda,em,gs,cplhhhhhh,MhhOS,MRPhhTohhhh,         & 
& MRGhhTohhhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTohhhh(MLambda,em,gs,Zcplhhhhhh,MhhOS,MRPhhTohhhh,        & 
& MRGhhTohhhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTohhhh(MLambda,em,gs,cplhhhhhh,Mhh,MRPhhTohhhh,           & 
& MRGhhTohhhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTohhhh(MLambda,em,gs,Zcplhhhhhh,Mhh,MRPhhTohhhh,          & 
& MRGhhTohhhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTohhhh(cplhhhhhh,ctcplhhhhhh,Mhh,Mhh2,Zfhh,           & 
& AmpWavehhTohhhh)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,cplhhhhHmcHm1,cplhhhhcVWmVWm1,        & 
& cplhhhhVZVZ1,AmpVertexhhTohhhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,            & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,               & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,             & 
& cplhhhhHmcHm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRdrhhTohhhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhhh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,Zcplhhhhhh,             & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,   & 
& cplhhhhhhhh1,cplhhhhHmcHm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,            & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,Zcplhhhhhh,cplhhHmcHm,cplhhHmcVWm,              & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,             & 
& cplhhhhHmcHm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhhh(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,              & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,   & 
& cplhhhhhhhh1,cplhhhhHmcHm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,            & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,               & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,             & 
& cplhhhhHmcHm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

 End if 
 End if 
AmpVertexhhTohhhh = AmpVertexhhTohhhh -  AmpVertexIRdrhhTohhhh! +  AmpVertexIRoshhTohhhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTohhhh=0._dp 
AmpVertexZhhTohhhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTohhhh(gt2,:,:) = AmpWaveZhhTohhhh(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhhh(gt1,:,:) 
AmpVertexZhhTohhhh(gt2,:,:)= AmpVertexZhhTohhhh(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTohhhh(gt1,:,:) 
 End Do 
End Do 
AmpWavehhTohhhh=AmpWaveZhhTohhhh 
AmpVertexhhTohhhh= AmpVertexZhhTohhhh
! Final State 1 
AmpWaveZhhTohhhh=0._dp 
AmpVertexZhhTohhhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTohhhh(:,gt2,:) = AmpWaveZhhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhhh(:,gt1,:) 
AmpVertexZhhTohhhh(:,gt2,:)= AmpVertexZhhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexhhTohhhh(:,gt1,:) 
 End Do 
End Do 
AmpWavehhTohhhh=AmpWaveZhhTohhhh 
AmpVertexhhTohhhh= AmpVertexZhhTohhhh
! Final State 2 
AmpWaveZhhTohhhh=0._dp 
AmpVertexZhhTohhhh=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTohhhh(:,:,gt2) = AmpWaveZhhTohhhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWavehhTohhhh(:,:,gt1) 
AmpVertexZhhTohhhh(:,:,gt2)= AmpVertexZhhTohhhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexhhTohhhh(:,:,gt1) 
 End Do 
End Do 
AmpWavehhTohhhh=AmpWaveZhhTohhhh 
AmpVertexhhTohhhh= AmpVertexZhhTohhhh
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
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
    Do gt3=gt2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(Mhh(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTohhhh = AmpTreehhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),Mhh(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTohhhh(gt1, gt2, gt3) 
  AmpSum2hhTohhhh = 2._dp*AmpWavehhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),Mhh(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTohhhh(gt1, gt2, gt3) 
  AmpSum2hhTohhhh = 2._dp*AmpVertexhhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),Mhh(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTohhhh(gt1, gt2, gt3) 
  AmpSum2hhTohhhh = AmpTreehhTohhhh + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),Mhh(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTohhhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTohhhh = AmpTreehhTohhhh
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
  AmpSqTreehhTohhhh(gt1, gt2, gt3) = AmpSqhhTohhhh(gt1, gt2, gt3)  
  AmpSum2hhTohhhh = + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh
  Call SquareAmp_StoSS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
  AmpSqhhTohhhh(gt1, gt2, gt3) = AmpSqhhTohhhh(gt1, gt2, gt3) + AmpSqTreehhTohhhh(gt1, gt2, gt3)  
Else  
  AmpSum2hhTohhhh = AmpTreehhTohhhh
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),Mhh(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
  AmpSqTreehhTohhhh(gt1, gt2, gt3) = AmpSqhhTohhhh(gt1, gt2, gt3)  
  AmpSum2hhTohhhh = + 2._dp*AmpWavehhTohhhh + 2._dp*AmpVertexhhTohhhh
  Call SquareAmp_StoSS(Mhh(gt1),Mhh(gt2),Mhh(gt3),AmpSumhhTohhhh(gt1, gt2, gt3),AmpSum2hhTohhhh(gt1, gt2, gt3),AmpSqhhTohhhh(gt1, gt2, gt3)) 
  AmpSqhhTohhhh(gt1, gt2, gt3) = AmpSqhhTohhhh(gt1, gt2, gt3) + AmpSqTreehhTohhhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTohhhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (gt2.ne.gt3) helfactor = 2._dp*helfactor 
If (AmpSqhhTohhhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(MhhOS(gt1),MhhOS(gt2),MhhOS(gt3),helfactor*AmpSqhhTohhhh(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(Mhh(gt1),Mhh(gt2),Mhh(gt3),helfactor*AmpSqhhTohhhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTohhhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPhhTohhhh(gt1, gt2, gt3) + MRGhhTohhhh(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPhhTohhhh(gt1, gt2, gt3) + MRGhhTohhhh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! Conjg(Hm) Hm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_hhTocHmHm(cplhhHmcHm,Mhh,MHm,Mhh2,MHm2,AmpTreehhTocHmHm)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTocHmHm(ZcplhhHmcHm,Mhh,MHm,Mhh2,MHm2,AmpTreehhTocHmHm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTocHmHm(MLambda,em,gs,cplhhHmcHm,MhhOS,MHmOS,             & 
& MRPhhTocHmHm,MRGhhTocHmHm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocHmHm(MLambda,em,gs,ZcplhhHmcHm,MhhOS,MHmOS,            & 
& MRPhhTocHmHm,MRGhhTocHmHm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTocHmHm(MLambda,em,gs,cplhhHmcHm,Mhh,MHm,MRPhhTocHmHm,    & 
& MRGhhTocHmHm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocHmHm(MLambda,em,gs,ZcplhhHmcHm,Mhh,MHm,MRPhhTocHmHm,   & 
& MRGhhTocHmHm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTocHmHm(cplhhHmcHm,ctcplhhHmcHm,Mhh,Mhh2,             & 
& MHm,MHm2,Zfhh,ZfHm,AmpWavehhTocHmHm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,       & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,               & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,        & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexhhTocHmHm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,     & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,        & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexIRdrhhTocHmHm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocHmHm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,         & 
& cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,cplhhhhhh,ZcplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,    & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,   & 
& cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,           & 
& AmpVertexIRoshhTocHmHm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,     & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,ZcplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,       & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexIRoshhTocHmHm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocHmHm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,           & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,         & 
& cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,     & 
& cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,   & 
& cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,           & 
& AmpVertexIRoshhTocHmHm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,     & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgWmgWmhh,              & 
& cplcgZgWmcHm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm,         & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,        & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,              & 
& cplAhhhHmcHm1,cplhhhhHmcHm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,              & 
& cplhhcHmVWmVZ1,cplHmHmcHmcHm1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,AmpVertexIRoshhTocHmHm)

 End if 
 End if 
AmpVertexhhTocHmHm = AmpVertexhhTocHmHm -  AmpVertexIRdrhhTocHmHm! +  AmpVertexIRoshhTocHmHm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocHmHm=0._dp 
AmpVertexZhhTocHmHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHmHm(gt2,:,:) = AmpWaveZhhTocHmHm(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTocHmHm(gt1,:,:) 
AmpVertexZhhTocHmHm(gt2,:,:)= AmpVertexZhhTocHmHm(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTocHmHm(gt1,:,:) 
 End Do 
End Do 
AmpWavehhTocHmHm=AmpWaveZhhTocHmHm 
AmpVertexhhTocHmHm= AmpVertexZhhTocHmHm
! Final State 1 
AmpWaveZhhTocHmHm=0._dp 
AmpVertexZhhTocHmHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHmHm(:,gt2,:) = AmpWaveZhhTocHmHm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWavehhTocHmHm(:,gt1,:) 
AmpVertexZhhTocHmHm(:,gt2,:)= AmpVertexZhhTocHmHm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexhhTocHmHm(:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocHmHm=AmpWaveZhhTocHmHm 
AmpVertexhhTocHmHm= AmpVertexZhhTocHmHm
! Final State 2 
AmpWaveZhhTocHmHm=0._dp 
AmpVertexZhhTocHmHm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHmHm(:,:,gt2) = AmpWaveZhhTocHmHm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWavehhTocHmHm(:,:,gt1) 
AmpVertexZhhTocHmHm(:,:,gt2)= AmpVertexZhhTocHmHm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexhhTocHmHm(:,:,gt1) 
 End Do 
End Do 
AmpWavehhTocHmHm=AmpWaveZhhTocHmHm 
AmpVertexhhTocHmHm= AmpVertexZhhTocHmHm
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocHmHm = AmpVertexhhTocHmHm  +  AmpVertexIRoshhTocHmHm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->conj[Hm] Hm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocHmHm = AmpTreehhTocHmHm 
 AmpSum2hhTocHmHm = AmpTreehhTocHmHm + 2._dp*AmpWavehhTocHmHm + 2._dp*AmpVertexhhTocHmHm  
Else 
 AmpSumhhTocHmHm = AmpTreehhTocHmHm + AmpWavehhTocHmHm + AmpVertexhhTocHmHm
 AmpSum2hhTocHmHm = AmpTreehhTocHmHm + AmpWavehhTocHmHm + AmpVertexhhTocHmHm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocHmHm = AmpTreehhTocHmHm
 AmpSum2hhTocHmHm = AmpTreehhTocHmHm 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MHmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MHm(gt2))+Abs(MHm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTocHmHm = AmpTreehhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHm(gt2),MHm(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocHmHm(gt1, gt2, gt3) 
  AmpSum2hhTocHmHm = 2._dp*AmpWavehhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHm(gt2),MHm(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocHmHm(gt1, gt2, gt3) 
  AmpSum2hhTocHmHm = 2._dp*AmpVertexhhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHm(gt2),MHm(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocHmHm(gt1, gt2, gt3) 
  AmpSum2hhTocHmHm = AmpTreehhTocHmHm + 2._dp*AmpWavehhTocHmHm + 2._dp*AmpVertexhhTocHmHm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHm(gt2),MHm(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocHmHm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocHmHm = AmpTreehhTocHmHm
  Call SquareAmp_StoSS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
  AmpSqTreehhTocHmHm(gt1, gt2, gt3) = AmpSqhhTocHmHm(gt1, gt2, gt3)  
  AmpSum2hhTocHmHm = + 2._dp*AmpWavehhTocHmHm + 2._dp*AmpVertexhhTocHmHm
  Call SquareAmp_StoSS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
  AmpSqhhTocHmHm(gt1, gt2, gt3) = AmpSqhhTocHmHm(gt1, gt2, gt3) + AmpSqTreehhTocHmHm(gt1, gt2, gt3)  
Else  
  AmpSum2hhTocHmHm = AmpTreehhTocHmHm
  Call SquareAmp_StoSS(Mhh(gt1),MHm(gt2),MHm(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
  AmpSqTreehhTocHmHm(gt1, gt2, gt3) = AmpSqhhTocHmHm(gt1, gt2, gt3)  
  AmpSum2hhTocHmHm = + 2._dp*AmpWavehhTocHmHm + 2._dp*AmpVertexhhTocHmHm
  Call SquareAmp_StoSS(Mhh(gt1),MHm(gt2),MHm(gt3),AmpSumhhTocHmHm(gt1, gt2, gt3),AmpSum2hhTocHmHm(gt1, gt2, gt3),AmpSqhhTocHmHm(gt1, gt2, gt3)) 
  AmpSqhhTocHmHm(gt1, gt2, gt3) = AmpSqhhTocHmHm(gt1, gt2, gt3) + AmpSqTreehhTocHmHm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTocHmHm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTocHmHm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MHmOS(gt2),MHmOS(gt3),helfactor*AmpSqhhTocHmHm(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MHm(gt2),MHm(gt3),helfactor*AmpSqhhTocHmHm(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocHmHm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocHmHm(gt1, gt2, gt3) + MRGhhTocHmHm(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocHmHm(gt1, gt2, gt3) + MRGhhTocHmHm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
Call Amplitude_Tree_gumTHDMII_hhToHmcVWm(cplhhHmcVWm,Mhh,MHm,MVWm,Mhh2,               & 
& MHm2,MVWm2,AmpTreehhToHmcVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_hhToHmcVWm(ZcplhhHmcVWm,Mhh,MHm,MVWm,Mhh2,              & 
& MHm2,MVWm2,AmpTreehhToHmcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhToHmcVWm(MLambda,em,gs,cplhhHmcVWm,MhhOS,MHmOS,           & 
& MVWmOS,MRPhhToHmcVWm,MRGhhToHmcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhToHmcVWm(MLambda,em,gs,ZcplhhHmcVWm,MhhOS,MHmOS,          & 
& MVWmOS,MRPhhToHmcVWm,MRGhhToHmcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhToHmcVWm(MLambda,em,gs,cplhhHmcVWm,Mhh,MHm,               & 
& MVWm,MRPhhToHmcVWm,MRGhhToHmcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhToHmcVWm(MLambda,em,gs,ZcplhhHmcVWm,Mhh,MHm,              & 
& MVWm,MRPhhToHmcVWm,MRGhhToHmcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhToHmcVWm(cplhhHmcVWm,ctcplhhHmcVWm,Mhh,               & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,Zfhh,ZfHm,ZfVWm,AmpWavehhToHmcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,  & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgAhh,cplcgWmgAHm,cplcgWmgWmhh,   & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,        & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,     & 
& cplAhHmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,         & 
& AmpVertexhhToHmcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,  & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgAhh,cplcgWmgAHm,cplcgWmgWmhh,   & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,        & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,     & 
& cplAhHmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,         & 
& AmpVertexIRdrhhToHmcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToHmcVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,          & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,               & 
& cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,             & 
& cplcFeFvHmR,cplcgZgAhh,cplcgWmgAHm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,           & 
& cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcVWm,cplhhhhhh,           & 
& GosZcplhhHmcHm,ZcplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,             & 
& GosZcplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhHmcVWmVZ1,       & 
& cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRoshhToHmcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,  & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgAhh,cplcgWmgAHm,cplcgWmgWmhh,   & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,        & 
& cplcgWpCgZcVWm,cplhhhhhh,GZcplhhHmcHm,ZcplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,           & 
& cplhhVZVZ,cplHmcHmVP,GZcplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,   & 
& cplAhHmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,         & 
& AmpVertexIRoshhToHmcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToHmcVWm(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,          & 
& MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,         & 
& MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,               & 
& cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,             & 
& cplcFeFvHmR,cplcgZgAhh,cplcgWmgAHm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,           & 
& cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcVWm,cplhhhhhh,           & 
& GcplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVP,GcplHmcVWmVP,    & 
& cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhHmcVWmVZ1,cplhhhhcVWmVWm1,       & 
& cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,AmpVertexIRoshhToHmcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,  & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcgZgAhh,cplcgWmgAHm,cplcgWmgWmhh,   & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,        & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,     & 
& cplAhHmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,         & 
& AmpVertexIRoshhToHmcVWm)

 End if 
 End if 
AmpVertexhhToHmcVWm = AmpVertexhhToHmcVWm -  AmpVertexIRdrhhToHmcVWm! +  AmpVertexIRoshhToHmcVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToHmcVWm=0._dp 
AmpVertexZhhToHmcVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToHmcVWm(:,gt2,:) = AmpWaveZhhToHmcVWm(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhToHmcVWm(:,gt1,:) 
AmpVertexZhhToHmcVWm(:,gt2,:)= AmpVertexZhhToHmcVWm(:,gt2,:) + ZRUZH(gt2,gt1)*AmpVertexhhToHmcVWm(:,gt1,:) 
 End Do 
End Do 
AmpWavehhToHmcVWm=AmpWaveZhhToHmcVWm 
AmpVertexhhToHmcVWm= AmpVertexZhhToHmcVWm
! Final State 1 
AmpWaveZhhToHmcVWm=0._dp 
AmpVertexZhhToHmcVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToHmcVWm(:,:,gt2) = AmpWaveZhhToHmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWavehhToHmcVWm(:,:,gt1) 
AmpVertexZhhToHmcVWm(:,:,gt2)= AmpVertexZhhToHmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexhhToHmcVWm(:,:,gt1) 
 End Do 
End Do 
AmpWavehhToHmcVWm=AmpWaveZhhToHmcVWm 
AmpVertexhhToHmcVWm= AmpVertexZhhToHmcVWm
End if
If (ShiftIRdiv) Then 
AmpVertexhhToHmcVWm = AmpVertexhhToHmcVWm  +  AmpVertexIRoshhToHmcVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Hm conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToHmcVWm = AmpTreehhToHmcVWm 
 AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm + 2._dp*AmpWavehhToHmcVWm + 2._dp*AmpVertexhhToHmcVWm  
Else 
 AmpSumhhToHmcVWm = AmpTreehhToHmcVWm + AmpWavehhToHmcVWm + AmpVertexhhToHmcVWm
 AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm + AmpWavehhToHmcVWm + AmpVertexhhToHmcVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToHmcVWm = AmpTreehhToHmcVWm
 AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm 
End if 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MHmOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MHm(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHm(gt2),MVWm,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToHmcVWm(gt1, gt2) 
  AmpSum2hhToHmcVWm = 2._dp*AmpWavehhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHm(gt2),MVWm,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToHmcVWm(gt1, gt2) 
  AmpSum2hhToHmcVWm = 2._dp*AmpVertexhhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHm(gt2),MVWm,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToHmcVWm(gt1, gt2) 
  AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm + 2._dp*AmpWavehhToHmcVWm + 2._dp*AmpVertexhhToHmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHm(gt2),MVWm,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToHmcVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm
  Call SquareAmp_StoSV(MhhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
  AmpSqTreehhToHmcVWm(gt1, gt2) = AmpSqhhToHmcVWm(gt1, gt2)  
  AmpSum2hhToHmcVWm = + 2._dp*AmpWavehhToHmcVWm + 2._dp*AmpVertexhhToHmcVWm
  Call SquareAmp_StoSV(MhhOS(gt1),MHmOS(gt2),MVWmOS,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
  AmpSqhhToHmcVWm(gt1, gt2) = AmpSqhhToHmcVWm(gt1, gt2) + AmpSqTreehhToHmcVWm(gt1, gt2)  
Else  
  AmpSum2hhToHmcVWm = AmpTreehhToHmcVWm
  Call SquareAmp_StoSV(Mhh(gt1),MHm(gt2),MVWm,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
  AmpSqTreehhToHmcVWm(gt1, gt2) = AmpSqhhToHmcVWm(gt1, gt2)  
  AmpSum2hhToHmcVWm = + 2._dp*AmpWavehhToHmcVWm + 2._dp*AmpVertexhhToHmcVWm
  Call SquareAmp_StoSV(Mhh(gt1),MHm(gt2),MVWm,AmpSumhhToHmcVWm(:,gt1, gt2),AmpSum2hhToHmcVWm(:,gt1, gt2),AmpSqhhToHmcVWm(gt1, gt2)) 
  AmpSqhhToHmcVWm(gt1, gt2) = AmpSqhhToHmcVWm(gt1, gt2) + AmpSqTreehhToHmcVWm(gt1, gt2)  
End if  
Else  
  AmpSqhhToHmcVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToHmcVWm(gt1, gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS(gt1),MHmOS(gt2),MVWmOS,helfactor*AmpSqhhToHmcVWm(gt1, gt2))
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh(gt1),MHm(gt2),MVWm,helfactor*AmpSqhhToHmcVWm(gt1, gt2))
End if 
If ((Abs(MRPhhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToHmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPhhToHmcVWm(gt1, gt2) + MRGhhToHmcVWm(gt1, gt2)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPhhToHmcVWm(gt1, gt2) + MRGhhToHmcVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! Conjg(VWm) VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_hhTocVWmVWm(cplhhcVWmVWm,Mhh,MVWm,Mhh2,MVWm2,           & 
& AmpTreehhTocVWmVWm)

  Else 
Call Amplitude_Tree_gumTHDMII_hhTocVWmVWm(ZcplhhcVWmVWm,Mhh,MVWm,Mhh2,MVWm2,          & 
& AmpTreehhTocVWmVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhTocVWmVWm(MLambda,em,gs,cplhhcVWmVWm,MhhOS,               & 
& MVWmOS,MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocVWmVWm(MLambda,em,gs,ZcplhhcVWmVWm,MhhOS,              & 
& MVWmOS,MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhTocVWmVWm(MLambda,em,gs,cplhhcVWmVWm,Mhh,MVWm,            & 
& MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhTocVWmVWm(MLambda,em,gs,ZcplhhcVWmVWm,Mhh,MVWm,           & 
& MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhTocVWmVWm(cplhhcVWmVWm,ctcplhhcVWmVWm,Mhh,            & 
& Mhh2,MVWm,MVWm2,Zfhh,ZfVWm,AmpWavehhTocVWmVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTocVWmVWm(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,              & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,            & 
& cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,               & 
& cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,            & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,   & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,          & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,     & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,     & 
& cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,          & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,          & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexhhTocVWmVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocVWmVWm(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,        & 
& cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,               & 
& cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,            & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,   & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,          & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,     & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,     & 
& cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,          & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,          & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRdrhhTocVWmVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocVWmVWm(MAhOS,MFdOS,MFeOS,MFuOS,               & 
& MhhOS,MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,           & 
& MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,      & 
& cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,          & 
& cplcFeFvVWmR,cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,      & 
& cplcgWpCgZcVWm,cplhhhhhh,GosZcplhhHmcHm,cplhhHmcVWm,GosZcplhhcHmVWm,ZcplhhcVWmVWm,     & 
& cplhhVZVZ,GosZcplHmcVWmVP,cplHmcVWmVZ,GosZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,        & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,            & 
& cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,& 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocVWmVWm(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,        & 
& cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,               & 
& cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,            & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,   & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,          & 
& GZcplhhHmcHm,cplhhHmcVWm,GZcplhhcHmVWm,ZcplhhcVWmVWm,cplhhVZVZ,GZcplHmcVWmVP,          & 
& cplHmcVWmVZ,GZcplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,       & 
& cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,           & 
& cplHmcHmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,          & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocVWmVWm(MAhOS,MFdOS,MFeOS,MFuOS,               & 
& MhhOS,MHmOS,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,           & 
& MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,      & 
& cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,          & 
& cplcFeFvVWmR,cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,      & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,GcplhhcHmVWm,cplhhcVWmVWm,             & 
& cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,   & 
& cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,          & 
& cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,               & 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhTocVWmVWm(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,        & 
& cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,               & 
& cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,            & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,   & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,          & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,     & 
& cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,     & 
& cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmcVWmVWm1,          & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,          & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

 End if 
 End if 
AmpVertexhhTocVWmVWm = AmpVertexhhTocVWmVWm -  AmpVertexIRdrhhTocVWmVWm! +  AmpVertexIRoshhTocVWmVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocVWmVWm=0._dp 
AmpVertexZhhTocVWmVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocVWmVWm(:,gt2) = AmpWaveZhhTocVWmVWm(:,gt2)+ZRUZH(gt2,gt1)*AmpWavehhTocVWmVWm(:,gt1) 
AmpVertexZhhTocVWmVWm(:,gt2)= AmpVertexZhhTocVWmVWm(:,gt2) + ZRUZH(gt2,gt1)*AmpVertexhhTocVWmVWm(:,gt1) 
 End Do 
End Do 
AmpWavehhTocVWmVWm=AmpWaveZhhTocVWmVWm 
AmpVertexhhTocVWmVWm= AmpVertexZhhTocVWmVWm
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocVWmVWm = AmpVertexhhTocVWmVWm  +  AmpVertexIRoshhTocVWmVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->conj[VWm] VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocVWmVWm = AmpTreehhTocVWmVWm 
 AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm + 2._dp*AmpWavehhTocVWmVWm + 2._dp*AmpVertexhhTocVWmVWm  
Else 
 AmpSumhhTocVWmVWm = AmpTreehhTocVWmVWm + AmpWavehhTocVWmVWm + AmpVertexhhTocVWmVWm
 AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm + AmpWavehhTocVWmVWm + AmpVertexhhTocVWmVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocVWmVWm = AmpTreehhTocVWmVWm
 AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm 
End if 
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MVWmOS)+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MVWm)+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVWmOS,MVWmOS,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVWm,MVWm,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocVWmVWm(gt1) 
  AmpSum2hhTocVWmVWm = 2._dp*AmpWavehhTocVWmVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVWmOS,MVWmOS,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVWm,MVWm,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocVWmVWm(gt1) 
  AmpSum2hhTocVWmVWm = 2._dp*AmpVertexhhTocVWmVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVWmOS,MVWmOS,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVWm,MVWm,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocVWmVWm(gt1) 
  AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm + 2._dp*AmpWavehhTocVWmVWm + 2._dp*AmpVertexhhTocVWmVWm
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVWmOS,MVWmOS,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVWm,MVWm,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocVWmVWm(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm
  Call SquareAmp_StoVV(MhhOS(gt1),MVWmOS,MVWmOS,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
  AmpSqTreehhTocVWmVWm(gt1) = AmpSqhhTocVWmVWm(gt1)  
  AmpSum2hhTocVWmVWm = + 2._dp*AmpWavehhTocVWmVWm + 2._dp*AmpVertexhhTocVWmVWm
  Call SquareAmp_StoVV(MhhOS(gt1),MVWmOS,MVWmOS,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
  AmpSqhhTocVWmVWm(gt1) = AmpSqhhTocVWmVWm(gt1) + AmpSqTreehhTocVWmVWm(gt1)  
Else  
  AmpSum2hhTocVWmVWm = AmpTreehhTocVWmVWm
  Call SquareAmp_StoVV(Mhh(gt1),MVWm,MVWm,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
  AmpSqTreehhTocVWmVWm(gt1) = AmpSqhhTocVWmVWm(gt1)  
  AmpSum2hhTocVWmVWm = + 2._dp*AmpWavehhTocVWmVWm + 2._dp*AmpVertexhhTocVWmVWm
  Call SquareAmp_StoVV(Mhh(gt1),MVWm,MVWm,AmpSumhhTocVWmVWm(:,gt1),AmpSum2hhTocVWmVWm(:,gt1),AmpSqhhTocVWmVWm(gt1)) 
  AmpSqhhTocVWmVWm(gt1) = AmpSqhhTocVWmVWm(gt1) + AmpSqTreehhTocVWmVWm(gt1)  
End if  
Else  
  AmpSqhhTocVWmVWm(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTocVWmVWm(gt1).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS(gt1),MVWmOS,MVWmOS,helfactor*AmpSqhhTocVWmVWm(gt1))
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh(gt1),MVWm,MVWm,helfactor*AmpSqhhTocVWmVWm(gt1))
End if 
If ((Abs(MRPhhTocVWmVWm(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhTocVWmVWm(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocVWmVWm(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhTocVWmVWm(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPhhTocVWmVWm(gt1) + MRGhhTocVWmVWm(gt1)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPhhTocVWmVWm(gt1) + MRGhhTocVWmVWm(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! VZ VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_gumTHDMII_hhToVZVZ(cplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,AmpTreehhToVZVZ)

  Else 
Call Amplitude_Tree_gumTHDMII_hhToVZVZ(ZcplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,AmpTreehhToVZVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_gumTHDMII_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,MhhOS,MVZOS,               & 
& MRPhhToVZVZ,MRGhhToVZVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_gumTHDMII_hhToVZVZ(MLambda,em,gs,ZcplhhVZVZ,MhhOS,MVZOS,              & 
& MRPhhToVZVZ,MRGhhToVZVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_gumTHDMII_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,Mhh,MVZ,MRPhhToVZVZ,       & 
& MRGhhToVZVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_gumTHDMII_hhToVZVZ(MLambda,em,gs,ZcplhhVZVZ,Mhh,MVZ,MRPhhToVZVZ,      & 
& MRGhhToVZVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhToVZVZ(cplhhVZVZ,ctcplhhVZVZ,Mhh,Mhh2,MVZ,            & 
& MVZ2,Zfhh,ZfVZ,AmpWavehhToVZVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVZVZ1,cplcVWmVWmVZVZ2Q,& 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexhhToVZVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVZVZ1,cplcVWmVWmVZVZ2Q,& 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRdrhhToVZVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToVZVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,ZcplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,      & 
& cplHmcHmVZVZ1,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,ZcplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,   & 
& cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVZVZ1,cplcVWmVWmVZVZ2Q,& 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToVZVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,      & 
& cplHmcHmVZVZ1,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_gumTHDMII_hhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,             & 
& MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhVZ,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,cplHmcHmVZVZ1,cplcVWmVWmVZVZ2Q,& 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

 End if 
 End if 
AmpVertexhhToVZVZ = AmpVertexhhToVZVZ -  AmpVertexIRdrhhToVZVZ! +  AmpVertexIRoshhToVZVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToVZVZ=0._dp 
AmpVertexZhhToVZVZ=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToVZVZ(:,gt2) = AmpWaveZhhToVZVZ(:,gt2)+ZRUZH(gt2,gt1)*AmpWavehhToVZVZ(:,gt1) 
AmpVertexZhhToVZVZ(:,gt2)= AmpVertexZhhToVZVZ(:,gt2) + ZRUZH(gt2,gt1)*AmpVertexhhToVZVZ(:,gt1) 
 End Do 
End Do 
AmpWavehhToVZVZ=AmpWaveZhhToVZVZ 
AmpVertexhhToVZVZ= AmpVertexZhhToVZVZ
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
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MVZOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MVZ)+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1 
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVZOS,MVZOS,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVZ,MVZ,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToVZVZ(gt1) 
  AmpSum2hhToVZVZ = 2._dp*AmpWavehhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVZOS,MVZOS,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVZ,MVZ,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToVZVZ(gt1) 
  AmpSum2hhToVZVZ = 2._dp*AmpVertexhhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVZOS,MVZOS,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVZ,MVZ,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToVZVZ(gt1) 
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),MVZOS,MVZOS,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVZ,MVZ,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToVZVZ(gt1) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ
  Call SquareAmp_StoVV(MhhOS(gt1),MVZOS,MVZOS,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
  AmpSqTreehhToVZVZ(gt1) = AmpSqhhToVZVZ(gt1)  
  AmpSum2hhToVZVZ = + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ
  Call SquareAmp_StoVV(MhhOS(gt1),MVZOS,MVZOS,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
  AmpSqhhToVZVZ(gt1) = AmpSqhhToVZVZ(gt1) + AmpSqTreehhToVZVZ(gt1)  
Else  
  AmpSum2hhToVZVZ = AmpTreehhToVZVZ
  Call SquareAmp_StoVV(Mhh(gt1),MVZ,MVZ,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
  AmpSqTreehhToVZVZ(gt1) = AmpSqhhToVZVZ(gt1)  
  AmpSum2hhToVZVZ = + 2._dp*AmpWavehhToVZVZ + 2._dp*AmpVertexhhToVZVZ
  Call SquareAmp_StoVV(Mhh(gt1),MVZ,MVZ,AmpSumhhToVZVZ(:,gt1),AmpSum2hhToVZVZ(:,gt1),AmpSqhhToVZVZ(gt1)) 
  AmpSqhhToVZVZ(gt1) = AmpSqhhToVZVZ(gt1) + AmpSqTreehhToVZVZ(gt1)  
End if  
Else  
  AmpSqhhToVZVZ(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVZVZ(gt1).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MVZOS,MVZOS,helfactor*AmpSqhhToVZVZ(gt1))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MVZ,MVZ,helfactor*AmpSqhhToVZVZ(gt1))
End if 
If ((Abs(MRPhhToVZVZ(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhToVZVZ(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToVZVZ(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhToVZVZ(gt1)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPhhToVZVZ(gt1) + MRGhhToVZVZ(gt1)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPhhToVZVZ(gt1) + MRGhhToVZVZ(gt1))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End If 
!---------------- 
! Ah VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_gumTHDMII_hhToAhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,            & 
& MhhOS,Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWavehhToAhVP)

 Else 
Call Amplitude_WAVE_gumTHDMII_hhToAhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,            & 
& MhhOS,Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWavehhToAhVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_hhToAhVP(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,               & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,              & 
& cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,         & 
& cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,           & 
& cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,AmpVertexhhToAhVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhToAhVP(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVP,MVWmOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,               & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,              & 
& cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,         & 
& cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,           & 
& cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,AmpVertexhhToAhVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_gumTHDMII_hhToAhVP(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,            & 
& Mhh2,MVP,MVP2,MVZ,MVZ2,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWavehhToAhVP)



!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToAhVP(MAh,MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,    & 
& cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,              & 
& AmpVertexhhToAhVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Ah VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToAhVP = 0._dp 
 AmpSum2hhToAhVP = 0._dp  
Else 
 AmpSumhhToAhVP = AmpVertexhhToAhVP + AmpWavehhToAhVP
 AmpSum2hhToAhVP = AmpVertexhhToAhVP + AmpWavehhToAhVP 
End If 
Do gt1=1,2
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MAhOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MAh(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MAhOS(gt2),0._dp,AmpSumhhToAhVP(:,gt1, gt2),AmpSum2hhToAhVP(:,gt1, gt2),AmpSqhhToAhVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MAh(gt2),MVP,AmpSumhhToAhVP(:,gt1, gt2),AmpSum2hhToAhVP(:,gt1, gt2),AmpSqhhToAhVP(gt1, gt2)) 
End if  
Else  
  AmpSqhhToAhVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToAhVP(gt1, gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MAhOS(gt2),0._dp,helfactor*AmpSqhhToAhVP(gt1, gt2))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MAh(gt2),MVP,helfactor*AmpSqhhToAhVP(gt1, gt2))
End if 
If ((Abs(MRPhhToAhVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToAhVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
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
Call Amplitude_VERTEX_gumTHDMII_hhToFvcFv(MFeOS,MhhOS,MHmOS,MVWmOS,MVZOS,             & 
& MFe2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhToFvcFv)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhToFvcFv(MFeOS,MhhOS,MHmOS,MVWmOS,MVZOS,             & 
& MFe2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToFvcFv(MFe,Mhh,MHm,MVWm,MVZ,MFe2,Mhh2,             & 
& MHm2,MVWm2,MVZ2,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,       & 
& cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,           & 
& cplcFvFvVZR,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhToFvcFv)

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
Do gt1=1,2
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(0._dp)+Abs(0._dp))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),0._dp,0._dp,AmpSumhhToFvcFv(:,gt1, gt2, gt3),AmpSum2hhToFvcFv(:,gt1, gt2, gt3),AmpSqhhToFvcFv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),0._dp,0._dp,AmpSumhhToFvcFv(:,gt1, gt2, gt3),AmpSum2hhToFvcFv(:,gt1, gt2, gt3),AmpSqhhToFvcFv(gt1, gt2, gt3)) 
End if  
Else  
  AmpSqhhToFvcFv(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhToFvcFv(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),0._dp,0._dp,helfactor*AmpSqhhToFvcFv(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),0._dp,0._dp,helfactor*AmpSqhhToFvcFv(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhToFvcFv(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhToFvcFv(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
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


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_hhTohhVP(MFdOS,MFeOS,MFuOS,MhhOS,MHmOS,               & 
& MVP,MVWmOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdhhL,cplcFdFdhhR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,         & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplhhHmcVWmVP1,cplhhcHmVPVWm1,         & 
& AmpVertexhhTohhVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhTohhVP(MFdOS,MFeOS,MFuOS,MhhOS,MHmOS,               & 
& MVP,MVWmOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdhhL,cplcFdFdhhR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,         & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplhhHmcVWmVP1,cplhhcHmVPVWm1,         & 
& AmpVertexhhTohhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTohhVP(MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,MFd2,           & 
& MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,    & 
& cplcVWmVPVWm,cplhhHmcVWmVP1,cplhhcHmVPVWm1,AmpVertexhhTohhVP)

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
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(Mhh(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MhhOS(gt2),0._dp,AmpSumhhTohhVP(:,gt1, gt2),AmpSum2hhTohhVP(:,gt1, gt2),AmpSqhhTohhVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),Mhh(gt2),MVP,AmpSumhhTohhVP(:,gt1, gt2),AmpSum2hhTohhVP(:,gt1, gt2),AmpSqhhTohhVP(gt1, gt2)) 
End if  
Else  
  AmpSqhhTohhVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTohhVP(gt1, gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MhhOS(gt2),0._dp,helfactor*AmpSqhhTohhVP(gt1, gt2))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),Mhh(gt2),MVP,helfactor*AmpSqhhTohhVP(gt1, gt2))
End if 
If ((Abs(MRPhhTohhVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhTohhVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.2) isave = i4 
End do
!---------------- 
! hh VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_gumTHDMII_hhTohhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,        & 
& cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexhhTohhVZ)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhTohhVZ(MAhOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHmOS,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,        & 
& cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexhhTohhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,MVWm,MVZ,            & 
& MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,AmpVertexhhTohhVZ)

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
Do gt1=1,2
i4 = isave 
  Do gt2=1,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MhhOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(Mhh(gt2))+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MhhOS(gt2),MVZOS,AmpSumhhTohhVZ(:,gt1, gt2),AmpSum2hhTohhVZ(:,gt1, gt2),AmpSqhhTohhVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),Mhh(gt2),MVZ,AmpSumhhTohhVZ(:,gt1, gt2),AmpSum2hhTohhVZ(:,gt1, gt2),AmpSqhhTohhVZ(gt1, gt2)) 
End if  
Else  
  AmpSqhhTohhVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTohhVZ(gt1, gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MhhOS(gt2),MVZOS,helfactor*AmpSqhhTohhVZ(gt1, gt2))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),Mhh(gt2),MVZ,helfactor*AmpSqhhTohhVZ(gt1, gt2))
End if 
If ((Abs(MRPhhTohhVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhTohhVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
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
Call Amplitude_VERTEX_gumTHDMII_hhToVGVG(MFdOS,MFuOS,MhhOS,MVG,MFd2OS,MFu2OS,         & 
& Mhh2OS,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhToVGVG(MFdOS,MFuOS,MhhOS,MVG,MFd2OS,MFu2OS,         & 
& Mhh2OS,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToVGVG(MFd,MFu,Mhh,MVG,MFd2,MFu2,Mhh2,              & 
& MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,cplcFuFuhhR,          & 
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
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MVG)+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),0._dp,0._dp,AmpSumhhToVGVG(:,gt1),AmpSum2hhToVGVG(:,gt1),AmpSqhhToVGVG(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVG,MVG,AmpSumhhToVGVG(:,gt1),AmpSum2hhToVGVG(:,gt1),AmpSqhhToVGVG(gt1)) 
End if  
Else  
  AmpSqhhToVGVG(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVGVG(gt1).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 8._dp*GammaTPS(MhhOS(gt1),0._dp,0._dp,helfactor*AmpSqhhToVGVG(gt1))
Else 
  gP1Lhh(gt1,i4) = 8._dp*GammaTPS(Mhh(gt1),MVG,MVG,helfactor*AmpSqhhToVGVG(gt1))
End if 
If ((Abs(MRPhhToVGVG(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhToVGVG(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
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
Call Amplitude_VERTEX_gumTHDMII_hhToVPVP(MFdOS,MFeOS,MFuOS,MhhOS,MHmOS,               & 
& MVP,MVWmOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdhhL,cplcFdFdhhR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,         & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplhhHmcVWmVP1,cplhhcHmVPVWm1,         & 
& cplHmcHmVPVP1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,AmpVertexhhToVPVP)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhToVPVP(MFdOS,MFeOS,MFuOS,MhhOS,MHmOS,               & 
& MVP,MVWmOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,cplcFdFdhhL,cplcFdFdhhR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,         & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,cplhhHmcVWmVP1,cplhhcHmVPVWm1,         & 
& cplHmcHmVPVP1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,AmpVertexhhToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToVPVP(MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,MFd2,           & 
& MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,        & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,    & 
& cplcVWmVPVWm,cplhhHmcVWmVP1,cplhhcHmVPVWm1,cplHmcHmVPVP1,cplcVWmVPVPVWm3Q,             & 
& cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,AmpVertexhhToVPVP)

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
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MVP)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),0._dp,0._dp,AmpSumhhToVPVP(:,gt1),AmpSum2hhToVPVP(:,gt1),AmpSqhhToVPVP(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVP,MVP,AmpSumhhToVPVP(:,gt1),AmpSum2hhToVPVP(:,gt1),AmpSqhhToVPVP(gt1)) 
End if  
Else  
  AmpSqhhToVPVP(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVPVP(gt1).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),0._dp,0._dp,helfactor*AmpSqhhToVPVP(gt1))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MVP,MVP,helfactor*AmpSqhhToVPVP(gt1))
End if 
If ((Abs(MRPhhToVPVP(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhToVPVP(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
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
Call Amplitude_VERTEX_gumTHDMII_hhToVPVZ(MFdOS,MFeOS,MFuOS,MhhOS,MHmOS,               & 
& MVP,MVWmOS,MVZOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,   & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,     & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhHmcVWmVP1,          & 
& cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplcVWmVPVWmVZ3Q,           & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexhhToVPVZ)

 Else 
Call Amplitude_VERTEX_gumTHDMII_hhToVPVZ(MFdOS,MFeOS,MFuOS,MhhOS,MHmOS,               & 
& MVP,MVWmOS,MVZOS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHm2OS,MVP2,MVWm2OS,MVZ2OS,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,   & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,     & 
& cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhHmcVWmVP1,          & 
& cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,cplHmcHmVPVZ1,cplcVWmVPVWmVZ3Q,           & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexhhToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_gumTHDMII_hhToVPVZ(MFd,MFe,MFu,Mhh,MHm,MVP,MVWm,MVZ,            & 
& MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,          & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,            & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,       & 
& cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,   & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,cplhhcHmVWmVZ1,  & 
& cplHmcHmVPVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexhhToVPVZ)

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
Do gt1=1,2
i4 = isave 
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(0.)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MVP)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoVV(MhhOS(gt1),0._dp,MVZOS,AmpSumhhToVPVZ(:,gt1),AmpSum2hhToVPVZ(:,gt1),AmpSqhhToVPVZ(gt1)) 
Else  
  Call SquareAmp_StoVV(Mhh(gt1),MVP,MVZ,AmpSumhhToVPVZ(:,gt1),AmpSum2hhToVPVZ(:,gt1),AmpSqhhToVPVZ(gt1)) 
End if  
Else  
  AmpSqhhToVPVZ(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToVPVZ(gt1).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS(gt1),0._dp,MVZOS,helfactor*AmpSqhhToVPVZ(gt1))
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh(gt1),MVP,MVZ,helfactor*AmpSqhhToVPVZ(gt1))
End if 
If ((Abs(MRPhhToVPVZ(gt1)).gt.1.0E-20_dp).or.(Abs(MRGhhToVPVZ(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.2) isave = i4 
End do
End Subroutine OneLoopDecay_hh

End Module Wrapper_OneLoopDecay_hh_gumTHDMII
