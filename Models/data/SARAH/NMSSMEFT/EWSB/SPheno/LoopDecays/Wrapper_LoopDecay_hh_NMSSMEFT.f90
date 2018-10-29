! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:59 on 29.10.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_hh_NMSSMEFT
Use Model_Data_NMSSMEFT 
Use Kinematics 
Use OneLoopDecay_hh_NMSSMEFT 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_hh(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,              & 
& MSe2OS,MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,         & 
& MFeOS,MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZDOS,               & 
& ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,ZDROS,ZULOS,            & 
& ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,              & 
& MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,              & 
& UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,             & 
& g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,             & 
& M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,dkap,dTk,dYu,dTu,dmq2,           & 
& dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,dvu,dvS,dZD,dZV,dZU,              & 
& dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,dZUL,dZUR,dSinTW,dCosTW,               & 
& dTanTW,ZfVG,ZfFvL,ZfVP,ZfVZ,ZfVWm,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,          & 
& ZfFDL,ZfFDR,ZfFUL,ZfFUR,ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhAhAh1,cplAhAhAhhh1,             & 
& cplAhAhcVWmVWm1,cplAhAhhh,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhVZVZ1,cplAhcHpmVPVWm1,   & 
& cplAhcHpmVWm,cplAhcHpmVWmVZ1,cplAhhhhh,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhVZ,         & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplcChaChaAhL,               & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,           & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgAgWmcVWm,cplcgAgWpCVWm,       & 
& cplcgWmgAHpm,cplcgWmgAVWm,cplcgWmgWmAh,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,         & 
& cplcgWmgZHpm,cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP, & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHpm,cplcgWpCgZcVWm,cplcgZgAhh,cplcgZgWmcHpm,cplcgZgWmcVWm,   & 
& cplcgZgWpCHpm,cplcgZgWpCVWm,cplcgZgZhh,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,       & 
& cplChiChiVZR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,        & 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,   & 
& cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,      & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplhhcHpmVPVWm1,cplhhcHpmVWm,cplhhcHpmVWmVZ1,        & 
& cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhVZVZ1,      & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhVZVZ,cplHpmcHpmcVWmVWm1,& 
& cplHpmcHpmVP,cplHpmcHpmVPVP1,cplHpmcHpmVPVZ1,cplHpmcHpmVZ,cplHpmcHpmVZVZ1,             & 
& cplHpmcVWmVP,cplHpmcVWmVZ,cplHpmHpmcHpmcHpm1,ctcplAhAhhh,ctcplAhhhhh,ctcplAhhhVZ,      & 
& ctcplcChaChahhL,ctcplcChaChahhR,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFeFehhL,             & 
& ctcplcFeFehhR,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplChiChihhL,ctcplChiChihhR,               & 
& ctcplhhcVWmVWm,ctcplhhhhhh,ctcplhhHpmcHpm,ctcplhhHpmcVWm,ctcplhhVZVZ,GcplcHpmVPVWm,    & 
& GcplhhcHpmVWm,GcplhhHpmcHpm,GcplHpmcVWmVP,GosZcplcHpmVPVWm,GosZcplhhcHpmVWm,           & 
& GosZcplhhHpmcHpm,GosZcplHpmcVWmVP,GZcplcHpmVPVWm,GZcplhhcHpmVWm,GZcplhhHpmcHpm,        & 
& GZcplHpmcVWmVP,ZcplAhAhhh,ZcplAhhhhh,ZcplAhhhVZ,ZcplcChaChahhL,ZcplcChaChahhR,         & 
& ZcplcFdFdhhL,ZcplcFdFdhhR,ZcplcFeFehhL,ZcplcFeFehhR,ZcplcFuFuhhL,ZcplcFuFuhhR,         & 
& ZcplChiChihhL,ZcplChiChihhR,ZcplhhcVWmVWm,Zcplhhhhhh,ZcplhhHpmcHpm,ZcplhhHpmcVWm,      & 
& ZcplhhVZVZ,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,         & 
& ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1Lhh)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp),Intent(in) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(0),MSd2(0),MSe(0),          & 
& MSe2(0),MSu(0),MSu2(0),MSv(0),MSv2(0),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(3,3),ZH(3,3),        & 
& ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(0,0),ZDL(3,3),ZDR(3,3),ZE(0,0),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(0,0),ZUL(3,3),ZUR(3,3),ZV(0,0),ZW(2,2)

Real(dp),Intent(in) :: dg1,dg2,dg3,dmHd2,dmHu2,dms2,dvd,dvu,dvS,dZH(3,3),dZA(3,3),dZP(2,2),dSinTW,           & 
& dCosTW,dTanTW

Complex(dp),Intent(in) :: dYd(3,3),dTd(3,3),dYe(3,3),dTe(3,3),dlam,dTlam,dkap,dTk,dYu(3,3),dTu(3,3),            & 
& dmq2(3,3),dml2(3,3),dmd2(3,3),dmu2(3,3),dme2(3,3),dM1,dM2,dM3,dZD(0,0),dZV(0,0),       & 
& dZU(0,0),dZE(0,0),dZN(5,5),dUM(2,2),dUP(2,2),dZEL(3,3),dZER(3,3),dZDL(3,3),            & 
& dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhAhAh1(3,3,3,3),cplAhAhAhhh1(3,3,3,3),cplAhAhcVWmVWm1(3,3),    & 
& cplAhAhhh(3,3,3),cplAhAhhhhh1(3,3,3,3),cplAhAhHpmcHpm1(3,3,2,2),cplAhAhVZVZ1(3,3),     & 
& cplAhcHpmVPVWm1(3,2),cplAhcHpmVWm(3,2),cplAhcHpmVWmVZ1(3,2),cplAhhhhh(3,3,3),          & 
& cplAhhhhhhh1(3,3,3,3),cplAhhhHpmcHpm1(3,3,2,2),cplAhhhVZ(3,3),cplAhHpmcHpm(3,2,2),     & 
& cplAhHpmcVWm(3,2),cplAhHpmcVWmVP1(3,2),cplAhHpmcVWmVZ1(3,2),cplcChaChaAhL(2,2,3),      & 
& cplcChaChaAhR(2,2,3),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcChaChaVPL(2,2),     & 
& cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,5,2),        & 
& cplcChaChiHpmR(2,5,2),cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),cplcFdFdAhL(3,3,3),      & 
& cplcFdFdAhR(3,3,3),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcFdFdVGL(3,3),             & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),           & 
& cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),           & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHpmL(3,3,2),& 
& cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFuFdcHpmL(3,3,2),          & 
& cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,3),         & 
& cplcFuFuAhR(3,3,3),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),       & 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHpm(2),         & 
& cplcgWmgAVWm,cplcgWmgWmAh(3),cplcgWmgWmhh(3),cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHpm(2),& 
& cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh(3),cplcgWpCgWpChh(3),cplcgWpCgWpCVP,        & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHpm(2),cplcgWpCgZcVWm,cplcgZgAhh(3),cplcgZgWmcHpm(2),        & 
& cplcgZgWmcVWm,cplcgZgWpCHpm(2),cplcgZgWpCVWm,cplcgZgZhh(3),cplChiChacHpmL(5,2,2),      & 
& cplChiChacHpmR(5,2,2),cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),cplChiChiAhL(5,5,3),     & 
& cplChiChiAhR(5,5,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplChiChiVZL(5,5),         & 
& cplChiChiVZR(5,5),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,& 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWm,   & 
& cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmVWmVZ,cplcVWmVWmVZVZ1Q,      & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplhhcHpmVPVWm1(3,2),cplhhcHpmVWm(3,2),              & 
& cplhhcHpmVWmVZ1(3,2),cplhhcVWmVWm(3),cplhhhhcVWmVWm1(3,3),cplhhhhhh(3,3,3),            & 
& cplhhhhhhhh1(3,3,3,3),cplhhhhHpmcHpm1(3,3,2,2),cplhhhhVZVZ1(3,3),cplhhHpmcHpm(3,2,2),  & 
& cplhhHpmcVWm(3,2),cplhhHpmcVWmVP1(3,2),cplhhHpmcVWmVZ1(3,2),cplhhVZVZ(3),              & 
& cplHpmcHpmcVWmVWm1(2,2),cplHpmcHpmVP(2,2),cplHpmcHpmVPVP1(2,2),cplHpmcHpmVPVZ1(2,2),   & 
& cplHpmcHpmVZ(2,2),cplHpmcHpmVZVZ1(2,2),cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplHpmHpmcHpmcHpm1(2,2,2,2),& 
& ctcplAhAhhh(3,3,3),ctcplAhhhhh(3,3,3),ctcplAhhhVZ(3,3),ctcplcChaChahhL(2,2,3),         & 
& ctcplcChaChahhR(2,2,3),ctcplcFdFdhhL(3,3,3),ctcplcFdFdhhR(3,3,3),ctcplcFeFehhL(3,3,3), & 
& ctcplcFeFehhR(3,3,3),ctcplcFuFuhhL(3,3,3),ctcplcFuFuhhR(3,3,3),ctcplChiChihhL(5,5,3)

Complex(dp),Intent(in) :: ctcplChiChihhR(5,5,3),ctcplhhcVWmVWm(3),ctcplhhhhhh(3,3,3),ctcplhhHpmcHpm(3,2,2),      & 
& ctcplhhHpmcVWm(3,2),ctcplhhVZVZ(3),GcplcHpmVPVWm(2),GcplhhcHpmVWm(3,2),GcplhhHpmcHpm(3,2,2),& 
& GcplHpmcVWmVP(2),GosZcplcHpmVPVWm(2),GosZcplhhcHpmVWm(3,2),GosZcplhhHpmcHpm(3,2,2),    & 
& GosZcplHpmcVWmVP(2),GZcplcHpmVPVWm(2),GZcplhhcHpmVWm(3,2),GZcplhhHpmcHpm(3,2,2),       & 
& GZcplHpmcVWmVP(2),ZcplAhAhhh(3,3,3),ZcplAhhhhh(3,3,3),ZcplAhhhVZ(3,3),ZcplcChaChahhL(2,2,3),& 
& ZcplcChaChahhR(2,2,3),ZcplcFdFdhhL(3,3,3),ZcplcFdFdhhR(3,3,3),ZcplcFeFehhL(3,3,3),     & 
& ZcplcFeFehhR(3,3,3),ZcplcFuFuhhL(3,3,3),ZcplcFuFuhhR(3,3,3),ZcplChiChihhL(5,5,3),      & 
& ZcplChiChihhR(5,5,3),ZcplhhcVWmVWm(3),Zcplhhhhhh(3,3,3),ZcplhhHpmcHpm(3,2,2),          & 
& ZcplhhHpmcVWm(3,2),ZcplhhVZVZ(3)

Real(dp), Intent(in) :: em, gs 
Complex(dp),Intent(in) :: ZfVG,ZfFvL(3,3),ZfVP,ZfVZ,ZfVWm,Zfhh(3,3),ZfAh(3,3),ZfHpm(2,2),ZfL0(5,5),             & 
& ZfLm(2,2),ZfLp(2,2),ZfFEL(3,3),ZfFER(3,3),ZfFDL(3,3),ZfFDR(3,3),ZfFUL(3,3),            & 
& ZfFUR(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MSdOS(0),MSd2OS(0),MSvOS(0),MSv2OS(0),MSuOS(0),MSu2OS(0),MSeOS(0),MSe2OS(0),          & 
& MhhOS(3),Mhh2OS(3),MAhOS(3),MAh2OS(3),MHpmOS(2),MHpm2OS(2),MChiOS(5),MChi2OS(5),       & 
& MChaOS(2),MCha2OS(2),MFeOS(3),MFe2OS(3),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),         & 
& MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(3,3),ZAOS(3,3),ZPOS(2,2)

Complex(dp),Intent(in) :: ZDOS(0,0),ZVOS(0,0),ZUOS(0,0),ZEOS(0,0),ZNOS(5,5),UMOS(2,2),UPOS(2,2),ZELOS(3,3),     & 
& ZEROS(3,3),ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3)

Complex(dp),Intent(in) :: ZRUZD(0,0),ZRUZV(0,0),ZRUZU(0,0),ZRUZE(0,0),ZRUZH(3,3),ZRUZA(3,3),ZRUZP(2,2),         & 
& ZRUZN(5,5),ZRUUM(2,2),ZRUUP(2,2),ZRUZEL(3,3),ZRUZER(3,3),ZRUZDL(3,3),ZRUZDR(3,3),      & 
& ZRUZUL(3,3),ZRUZUR(3,3)

Real(dp), Intent(in) :: MLambda, deltaM 
Real(dp), Intent(out) :: gP1Lhh(3,91) 
Integer, Intent(out) :: kont 
Real(dp) :: MVG,MVP,MVG2,MVP2, helfactor, phasespacefactor 
Integer :: i1,i2,i3,i4, isave, gt1, gt2, gt3 

Complex(dp) :: ZRUZDc(0, 0) 
Complex(dp) :: ZRUZVc(0, 0) 
Complex(dp) :: ZRUZUc(0, 0) 
Complex(dp) :: ZRUZEc(0, 0) 
Complex(dp) :: ZRUZHc(3, 3) 
Complex(dp) :: ZRUZAc(3, 3) 
Complex(dp) :: ZRUZPc(2, 2) 
Complex(dp) :: ZRUZNc(5, 5) 
Complex(dp) :: ZRUUMc(2, 2) 
Complex(dp) :: ZRUUPc(2, 2) 
Complex(dp) :: ZRUZELc(3, 3) 
Complex(dp) :: ZRUZERc(3, 3) 
Complex(dp) :: ZRUZDLc(3, 3) 
Complex(dp) :: ZRUZDRc(3, 3) 
Complex(dp) :: ZRUZULc(3, 3) 
Complex(dp) :: ZRUZURc(3, 3) 
Real(dp) :: MRPhhToAhAh(3,3,3),MRGhhToAhAh(3,3,3), MRPZhhToAhAh(3,3,3),MRGZhhToAhAh(3,3,3) 
Real(dp) :: MVPhhToAhAh(3,3,3) 
Real(dp) :: RMsqTreehhToAhAh(3,3,3),RMsqWavehhToAhAh(3,3,3),RMsqVertexhhToAhAh(3,3,3) 
Complex(dp) :: AmpTreehhToAhAh(3,3,3),AmpWavehhToAhAh(3,3,3)=(0._dp,0._dp),AmpVertexhhToAhAh(3,3,3)& 
 & ,AmpVertexIRoshhToAhAh(3,3,3),AmpVertexIRdrhhToAhAh(3,3,3), AmpSumhhToAhAh(3,3,3), AmpSum2hhToAhAh(3,3,3) 
Complex(dp) :: AmpTreeZhhToAhAh(3,3,3),AmpWaveZhhToAhAh(3,3,3),AmpVertexZhhToAhAh(3,3,3) 
Real(dp) :: AmpSqhhToAhAh(3,3,3),  AmpSqTreehhToAhAh(3,3,3) 
Real(dp) :: MRPhhTohhAh(3,3,3),MRGhhTohhAh(3,3,3), MRPZhhTohhAh(3,3,3),MRGZhhTohhAh(3,3,3) 
Real(dp) :: MVPhhTohhAh(3,3,3) 
Real(dp) :: RMsqTreehhTohhAh(3,3,3),RMsqWavehhTohhAh(3,3,3),RMsqVertexhhTohhAh(3,3,3) 
Complex(dp) :: AmpTreehhTohhAh(3,3,3),AmpWavehhTohhAh(3,3,3)=(0._dp,0._dp),AmpVertexhhTohhAh(3,3,3)& 
 & ,AmpVertexIRoshhTohhAh(3,3,3),AmpVertexIRdrhhTohhAh(3,3,3), AmpSumhhTohhAh(3,3,3), AmpSum2hhTohhAh(3,3,3) 
Complex(dp) :: AmpTreeZhhTohhAh(3,3,3),AmpWaveZhhTohhAh(3,3,3),AmpVertexZhhTohhAh(3,3,3) 
Real(dp) :: AmpSqhhTohhAh(3,3,3),  AmpSqTreehhTohhAh(3,3,3) 
Real(dp) :: MRPhhToAhVZ(3,3),MRGhhToAhVZ(3,3), MRPZhhToAhVZ(3,3),MRGZhhToAhVZ(3,3) 
Real(dp) :: MVPhhToAhVZ(3,3) 
Real(dp) :: RMsqTreehhToAhVZ(3,3),RMsqWavehhToAhVZ(3,3),RMsqVertexhhToAhVZ(3,3) 
Complex(dp) :: AmpTreehhToAhVZ(2,3,3),AmpWavehhToAhVZ(2,3,3)=(0._dp,0._dp),AmpVertexhhToAhVZ(2,3,3)& 
 & ,AmpVertexIRoshhToAhVZ(2,3,3),AmpVertexIRdrhhToAhVZ(2,3,3), AmpSumhhToAhVZ(2,3,3), AmpSum2hhToAhVZ(2,3,3) 
Complex(dp) :: AmpTreeZhhToAhVZ(2,3,3),AmpWaveZhhToAhVZ(2,3,3),AmpVertexZhhToAhVZ(2,3,3) 
Real(dp) :: AmpSqhhToAhVZ(3,3),  AmpSqTreehhToAhVZ(3,3) 
Real(dp) :: MRPhhTocChaCha(3,2,2),MRGhhTocChaCha(3,2,2), MRPZhhTocChaCha(3,2,2),MRGZhhTocChaCha(3,2,2) 
Real(dp) :: MVPhhTocChaCha(3,2,2) 
Real(dp) :: RMsqTreehhTocChaCha(3,2,2),RMsqWavehhTocChaCha(3,2,2),RMsqVertexhhTocChaCha(3,2,2) 
Complex(dp) :: AmpTreehhTocChaCha(2,3,2,2),AmpWavehhTocChaCha(2,3,2,2)=(0._dp,0._dp),AmpVertexhhTocChaCha(2,3,2,2)& 
 & ,AmpVertexIRoshhTocChaCha(2,3,2,2),AmpVertexIRdrhhTocChaCha(2,3,2,2), AmpSumhhTocChaCha(2,3,2,2), AmpSum2hhTocChaCha(2,3,2,2) 
Complex(dp) :: AmpTreeZhhTocChaCha(2,3,2,2),AmpWaveZhhTocChaCha(2,3,2,2),AmpVertexZhhTocChaCha(2,3,2,2) 
Real(dp) :: AmpSqhhTocChaCha(3,2,2),  AmpSqTreehhTocChaCha(3,2,2) 
Real(dp) :: MRPhhToChiChi(3,5,5),MRGhhToChiChi(3,5,5), MRPZhhToChiChi(3,5,5),MRGZhhToChiChi(3,5,5) 
Real(dp) :: MVPhhToChiChi(3,5,5) 
Real(dp) :: RMsqTreehhToChiChi(3,5,5),RMsqWavehhToChiChi(3,5,5),RMsqVertexhhToChiChi(3,5,5) 
Complex(dp) :: AmpTreehhToChiChi(2,3,5,5),AmpWavehhToChiChi(2,3,5,5)=(0._dp,0._dp),AmpVertexhhToChiChi(2,3,5,5)& 
 & ,AmpVertexIRoshhToChiChi(2,3,5,5),AmpVertexIRdrhhToChiChi(2,3,5,5), AmpSumhhToChiChi(2,3,5,5), AmpSum2hhToChiChi(2,3,5,5) 
Complex(dp) :: AmpTreeZhhToChiChi(2,3,5,5),AmpWaveZhhToChiChi(2,3,5,5),AmpVertexZhhToChiChi(2,3,5,5) 
Real(dp) :: AmpSqhhToChiChi(3,5,5),  AmpSqTreehhToChiChi(3,5,5) 
Real(dp) :: MRPhhTocFdFd(3,3,3),MRGhhTocFdFd(3,3,3), MRPZhhTocFdFd(3,3,3),MRGZhhTocFdFd(3,3,3) 
Real(dp) :: MVPhhTocFdFd(3,3,3) 
Real(dp) :: RMsqTreehhTocFdFd(3,3,3),RMsqWavehhTocFdFd(3,3,3),RMsqVertexhhTocFdFd(3,3,3) 
Complex(dp) :: AmpTreehhTocFdFd(2,3,3,3),AmpWavehhTocFdFd(2,3,3,3)=(0._dp,0._dp),AmpVertexhhTocFdFd(2,3,3,3)& 
 & ,AmpVertexIRoshhTocFdFd(2,3,3,3),AmpVertexIRdrhhTocFdFd(2,3,3,3), AmpSumhhTocFdFd(2,3,3,3), AmpSum2hhTocFdFd(2,3,3,3) 
Complex(dp) :: AmpTreeZhhTocFdFd(2,3,3,3),AmpWaveZhhTocFdFd(2,3,3,3),AmpVertexZhhTocFdFd(2,3,3,3) 
Real(dp) :: AmpSqhhTocFdFd(3,3,3),  AmpSqTreehhTocFdFd(3,3,3) 
Real(dp) :: MRPhhTocFeFe(3,3,3),MRGhhTocFeFe(3,3,3), MRPZhhTocFeFe(3,3,3),MRGZhhTocFeFe(3,3,3) 
Real(dp) :: MVPhhTocFeFe(3,3,3) 
Real(dp) :: RMsqTreehhTocFeFe(3,3,3),RMsqWavehhTocFeFe(3,3,3),RMsqVertexhhTocFeFe(3,3,3) 
Complex(dp) :: AmpTreehhTocFeFe(2,3,3,3),AmpWavehhTocFeFe(2,3,3,3)=(0._dp,0._dp),AmpVertexhhTocFeFe(2,3,3,3)& 
 & ,AmpVertexIRoshhTocFeFe(2,3,3,3),AmpVertexIRdrhhTocFeFe(2,3,3,3), AmpSumhhTocFeFe(2,3,3,3), AmpSum2hhTocFeFe(2,3,3,3) 
Complex(dp) :: AmpTreeZhhTocFeFe(2,3,3,3),AmpWaveZhhTocFeFe(2,3,3,3),AmpVertexZhhTocFeFe(2,3,3,3) 
Real(dp) :: AmpSqhhTocFeFe(3,3,3),  AmpSqTreehhTocFeFe(3,3,3) 
Real(dp) :: MRPhhTocFuFu(3,3,3),MRGhhTocFuFu(3,3,3), MRPZhhTocFuFu(3,3,3),MRGZhhTocFuFu(3,3,3) 
Real(dp) :: MVPhhTocFuFu(3,3,3) 
Real(dp) :: RMsqTreehhTocFuFu(3,3,3),RMsqWavehhTocFuFu(3,3,3),RMsqVertexhhTocFuFu(3,3,3) 
Complex(dp) :: AmpTreehhTocFuFu(2,3,3,3),AmpWavehhTocFuFu(2,3,3,3)=(0._dp,0._dp),AmpVertexhhTocFuFu(2,3,3,3)& 
 & ,AmpVertexIRoshhTocFuFu(2,3,3,3),AmpVertexIRdrhhTocFuFu(2,3,3,3), AmpSumhhTocFuFu(2,3,3,3), AmpSum2hhTocFuFu(2,3,3,3) 
Complex(dp) :: AmpTreeZhhTocFuFu(2,3,3,3),AmpWaveZhhTocFuFu(2,3,3,3),AmpVertexZhhTocFuFu(2,3,3,3) 
Real(dp) :: AmpSqhhTocFuFu(3,3,3),  AmpSqTreehhTocFuFu(3,3,3) 
Real(dp) :: MRPhhTohhhh(3,3,3),MRGhhTohhhh(3,3,3), MRPZhhTohhhh(3,3,3),MRGZhhTohhhh(3,3,3) 
Real(dp) :: MVPhhTohhhh(3,3,3) 
Real(dp) :: RMsqTreehhTohhhh(3,3,3),RMsqWavehhTohhhh(3,3,3),RMsqVertexhhTohhhh(3,3,3) 
Complex(dp) :: AmpTreehhTohhhh(3,3,3),AmpWavehhTohhhh(3,3,3)=(0._dp,0._dp),AmpVertexhhTohhhh(3,3,3)& 
 & ,AmpVertexIRoshhTohhhh(3,3,3),AmpVertexIRdrhhTohhhh(3,3,3), AmpSumhhTohhhh(3,3,3), AmpSum2hhTohhhh(3,3,3) 
Complex(dp) :: AmpTreeZhhTohhhh(3,3,3),AmpWaveZhhTohhhh(3,3,3),AmpVertexZhhTohhhh(3,3,3) 
Real(dp) :: AmpSqhhTohhhh(3,3,3),  AmpSqTreehhTohhhh(3,3,3) 
Real(dp) :: MRPhhTocHpmHpm(3,2,2),MRGhhTocHpmHpm(3,2,2), MRPZhhTocHpmHpm(3,2,2),MRGZhhTocHpmHpm(3,2,2) 
Real(dp) :: MVPhhTocHpmHpm(3,2,2) 
Real(dp) :: RMsqTreehhTocHpmHpm(3,2,2),RMsqWavehhTocHpmHpm(3,2,2),RMsqVertexhhTocHpmHpm(3,2,2) 
Complex(dp) :: AmpTreehhTocHpmHpm(3,2,2),AmpWavehhTocHpmHpm(3,2,2)=(0._dp,0._dp),AmpVertexhhTocHpmHpm(3,2,2)& 
 & ,AmpVertexIRoshhTocHpmHpm(3,2,2),AmpVertexIRdrhhTocHpmHpm(3,2,2), AmpSumhhTocHpmHpm(3,2,2), AmpSum2hhTocHpmHpm(3,2,2) 
Complex(dp) :: AmpTreeZhhTocHpmHpm(3,2,2),AmpWaveZhhTocHpmHpm(3,2,2),AmpVertexZhhTocHpmHpm(3,2,2) 
Real(dp) :: AmpSqhhTocHpmHpm(3,2,2),  AmpSqTreehhTocHpmHpm(3,2,2) 
Real(dp) :: MRPhhToHpmcVWm(3,2),MRGhhToHpmcVWm(3,2), MRPZhhToHpmcVWm(3,2),MRGZhhToHpmcVWm(3,2) 
Real(dp) :: MVPhhToHpmcVWm(3,2) 
Real(dp) :: RMsqTreehhToHpmcVWm(3,2),RMsqWavehhToHpmcVWm(3,2),RMsqVertexhhToHpmcVWm(3,2) 
Complex(dp) :: AmpTreehhToHpmcVWm(2,3,2),AmpWavehhToHpmcVWm(2,3,2)=(0._dp,0._dp),AmpVertexhhToHpmcVWm(2,3,2)& 
 & ,AmpVertexIRoshhToHpmcVWm(2,3,2),AmpVertexIRdrhhToHpmcVWm(2,3,2), AmpSumhhToHpmcVWm(2,3,2), AmpSum2hhToHpmcVWm(2,3,2) 
Complex(dp) :: AmpTreeZhhToHpmcVWm(2,3,2),AmpWaveZhhToHpmcVWm(2,3,2),AmpVertexZhhToHpmcVWm(2,3,2) 
Real(dp) :: AmpSqhhToHpmcVWm(3,2),  AmpSqTreehhToHpmcVWm(3,2) 
Real(dp) :: MRPhhTocVWmVWm(3),MRGhhTocVWmVWm(3), MRPZhhTocVWmVWm(3),MRGZhhTocVWmVWm(3) 
Real(dp) :: MVPhhTocVWmVWm(3) 
Real(dp) :: RMsqTreehhTocVWmVWm(3),RMsqWavehhTocVWmVWm(3),RMsqVertexhhTocVWmVWm(3) 
Complex(dp) :: AmpTreehhTocVWmVWm(2,3),AmpWavehhTocVWmVWm(2,3)=(0._dp,0._dp),AmpVertexhhTocVWmVWm(2,3)& 
 & ,AmpVertexIRoshhTocVWmVWm(2,3),AmpVertexIRdrhhTocVWmVWm(2,3), AmpSumhhTocVWmVWm(2,3), AmpSum2hhTocVWmVWm(2,3) 
Complex(dp) :: AmpTreeZhhTocVWmVWm(2,3),AmpWaveZhhTocVWmVWm(2,3),AmpVertexZhhTocVWmVWm(2,3) 
Real(dp) :: AmpSqhhTocVWmVWm(3),  AmpSqTreehhTocVWmVWm(3) 
Real(dp) :: MRPhhToVZVZ(3),MRGhhToVZVZ(3), MRPZhhToVZVZ(3),MRGZhhToVZVZ(3) 
Real(dp) :: MVPhhToVZVZ(3) 
Real(dp) :: RMsqTreehhToVZVZ(3),RMsqWavehhToVZVZ(3),RMsqVertexhhToVZVZ(3) 
Complex(dp) :: AmpTreehhToVZVZ(2,3),AmpWavehhToVZVZ(2,3)=(0._dp,0._dp),AmpVertexhhToVZVZ(2,3)& 
 & ,AmpVertexIRoshhToVZVZ(2,3),AmpVertexIRdrhhToVZVZ(2,3), AmpSumhhToVZVZ(2,3), AmpSum2hhToVZVZ(2,3) 
Complex(dp) :: AmpTreeZhhToVZVZ(2,3),AmpWaveZhhToVZVZ(2,3),AmpVertexZhhToVZVZ(2,3) 
Real(dp) :: AmpSqhhToVZVZ(3),  AmpSqTreehhToVZVZ(3) 
Real(dp) :: MRPhhToAhVP(3,3),MRGhhToAhVP(3,3), MRPZhhToAhVP(3,3),MRGZhhToAhVP(3,3) 
Real(dp) :: MVPhhToAhVP(3,3) 
Real(dp) :: RMsqTreehhToAhVP(3,3),RMsqWavehhToAhVP(3,3),RMsqVertexhhToAhVP(3,3) 
Complex(dp) :: AmpTreehhToAhVP(2,3,3),AmpWavehhToAhVP(2,3,3)=(0._dp,0._dp),AmpVertexhhToAhVP(2,3,3)& 
 & ,AmpVertexIRoshhToAhVP(2,3,3),AmpVertexIRdrhhToAhVP(2,3,3), AmpSumhhToAhVP(2,3,3), AmpSum2hhToAhVP(2,3,3) 
Complex(dp) :: AmpTreeZhhToAhVP(2,3,3),AmpWaveZhhToAhVP(2,3,3),AmpVertexZhhToAhVP(2,3,3) 
Real(dp) :: AmpSqhhToAhVP(3,3),  AmpSqTreehhToAhVP(3,3) 
Real(dp) :: MRPhhToFvcFv(3,3,3),MRGhhToFvcFv(3,3,3), MRPZhhToFvcFv(3,3,3),MRGZhhToFvcFv(3,3,3) 
Real(dp) :: MVPhhToFvcFv(3,3,3) 
Real(dp) :: RMsqTreehhToFvcFv(3,3,3),RMsqWavehhToFvcFv(3,3,3),RMsqVertexhhToFvcFv(3,3,3) 
Complex(dp) :: AmpTreehhToFvcFv(2,3,3,3),AmpWavehhToFvcFv(2,3,3,3)=(0._dp,0._dp),AmpVertexhhToFvcFv(2,3,3,3)& 
 & ,AmpVertexIRoshhToFvcFv(2,3,3,3),AmpVertexIRdrhhToFvcFv(2,3,3,3), AmpSumhhToFvcFv(2,3,3,3), AmpSum2hhToFvcFv(2,3,3,3) 
Complex(dp) :: AmpTreeZhhToFvcFv(2,3,3,3),AmpWaveZhhToFvcFv(2,3,3,3),AmpVertexZhhToFvcFv(2,3,3,3) 
Real(dp) :: AmpSqhhToFvcFv(3,3,3),  AmpSqTreehhToFvcFv(3,3,3) 
Real(dp) :: MRPhhTohhVP(3,3),MRGhhTohhVP(3,3), MRPZhhTohhVP(3,3),MRGZhhTohhVP(3,3) 
Real(dp) :: MVPhhTohhVP(3,3) 
Real(dp) :: RMsqTreehhTohhVP(3,3),RMsqWavehhTohhVP(3,3),RMsqVertexhhTohhVP(3,3) 
Complex(dp) :: AmpTreehhTohhVP(2,3,3),AmpWavehhTohhVP(2,3,3)=(0._dp,0._dp),AmpVertexhhTohhVP(2,3,3)& 
 & ,AmpVertexIRoshhTohhVP(2,3,3),AmpVertexIRdrhhTohhVP(2,3,3), AmpSumhhTohhVP(2,3,3), AmpSum2hhTohhVP(2,3,3) 
Complex(dp) :: AmpTreeZhhTohhVP(2,3,3),AmpWaveZhhTohhVP(2,3,3),AmpVertexZhhTohhVP(2,3,3) 
Real(dp) :: AmpSqhhTohhVP(3,3),  AmpSqTreehhTohhVP(3,3) 
Real(dp) :: MRPhhTohhVZ(3,3),MRGhhTohhVZ(3,3), MRPZhhTohhVZ(3,3),MRGZhhTohhVZ(3,3) 
Real(dp) :: MVPhhTohhVZ(3,3) 
Real(dp) :: RMsqTreehhTohhVZ(3,3),RMsqWavehhTohhVZ(3,3),RMsqVertexhhTohhVZ(3,3) 
Complex(dp) :: AmpTreehhTohhVZ(2,3,3),AmpWavehhTohhVZ(2,3,3)=(0._dp,0._dp),AmpVertexhhTohhVZ(2,3,3)& 
 & ,AmpVertexIRoshhTohhVZ(2,3,3),AmpVertexIRdrhhTohhVZ(2,3,3), AmpSumhhTohhVZ(2,3,3), AmpSum2hhTohhVZ(2,3,3) 
Complex(dp) :: AmpTreeZhhTohhVZ(2,3,3),AmpWaveZhhTohhVZ(2,3,3),AmpVertexZhhTohhVZ(2,3,3) 
Real(dp) :: AmpSqhhTohhVZ(3,3),  AmpSqTreehhTohhVZ(3,3) 
Real(dp) :: MRPhhToVGVG(3),MRGhhToVGVG(3), MRPZhhToVGVG(3),MRGZhhToVGVG(3) 
Real(dp) :: MVPhhToVGVG(3) 
Real(dp) :: RMsqTreehhToVGVG(3),RMsqWavehhToVGVG(3),RMsqVertexhhToVGVG(3) 
Complex(dp) :: AmpTreehhToVGVG(2,3),AmpWavehhToVGVG(2,3)=(0._dp,0._dp),AmpVertexhhToVGVG(2,3)& 
 & ,AmpVertexIRoshhToVGVG(2,3),AmpVertexIRdrhhToVGVG(2,3), AmpSumhhToVGVG(2,3), AmpSum2hhToVGVG(2,3) 
Complex(dp) :: AmpTreeZhhToVGVG(2,3),AmpWaveZhhToVGVG(2,3),AmpVertexZhhToVGVG(2,3) 
Real(dp) :: AmpSqhhToVGVG(3),  AmpSqTreehhToVGVG(3) 
Real(dp) :: MRPhhToVPVP(3),MRGhhToVPVP(3), MRPZhhToVPVP(3),MRGZhhToVPVP(3) 
Real(dp) :: MVPhhToVPVP(3) 
Real(dp) :: RMsqTreehhToVPVP(3),RMsqWavehhToVPVP(3),RMsqVertexhhToVPVP(3) 
Complex(dp) :: AmpTreehhToVPVP(2,3),AmpWavehhToVPVP(2,3)=(0._dp,0._dp),AmpVertexhhToVPVP(2,3)& 
 & ,AmpVertexIRoshhToVPVP(2,3),AmpVertexIRdrhhToVPVP(2,3), AmpSumhhToVPVP(2,3), AmpSum2hhToVPVP(2,3) 
Complex(dp) :: AmpTreeZhhToVPVP(2,3),AmpWaveZhhToVPVP(2,3),AmpVertexZhhToVPVP(2,3) 
Real(dp) :: AmpSqhhToVPVP(3),  AmpSqTreehhToVPVP(3) 
Real(dp) :: MRPhhToVPVZ(3),MRGhhToVPVZ(3), MRPZhhToVPVZ(3),MRGZhhToVPVZ(3) 
Real(dp) :: MVPhhToVPVZ(3) 
Real(dp) :: RMsqTreehhToVPVZ(3),RMsqWavehhToVPVZ(3),RMsqVertexhhToVPVZ(3) 
Complex(dp) :: AmpTreehhToVPVZ(2,3),AmpWavehhToVPVZ(2,3)=(0._dp,0._dp),AmpVertexhhToVPVZ(2,3)& 
 & ,AmpVertexIRoshhToVPVZ(2,3),AmpVertexIRdrhhToVPVZ(2,3), AmpSumhhToVPVZ(2,3), AmpSum2hhToVPVZ(2,3) 
Complex(dp) :: AmpTreeZhhToVPVZ(2,3),AmpWaveZhhToVPVZ(2,3),AmpVertexZhhToVPVZ(2,3) 
Real(dp) :: AmpSqhhToVPVZ(3),  AmpSqTreehhToVPVZ(3) 
Write(*,*) "Calculating one-loop decays of hh " 
kont = 0 
MVG = MLambda 
MVP = MLambda 
MVG2 = MLambda**2 
MVP2 = MLambda**2 

ZRUZDc = Conjg(ZRUZD)
ZRUZVc = Conjg(ZRUZV)
ZRUZUc = Conjg(ZRUZU)
ZRUZEc = Conjg(ZRUZE)
ZRUZHc = Conjg(ZRUZH)
ZRUZAc = Conjg(ZRUZA)
ZRUZPc = Conjg(ZRUZP)
ZRUZNc = Conjg(ZRUZN)
ZRUUMc = Conjg(ZRUUM)
ZRUUPc = Conjg(ZRUUP)
ZRUZELc = Conjg(ZRUZEL)
ZRUZERc = Conjg(ZRUZER)
ZRUZDLc = Conjg(ZRUZDL)
ZRUZDRc = Conjg(ZRUZDR)
ZRUZULc = Conjg(ZRUZUL)
ZRUZURc = Conjg(ZRUZUR)

 ! Counter 
isave = 5

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Ah Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhToAhAh(cplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhToAhAh)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhToAhAh(ZcplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhToAhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhToAhAh(MLambda,em,gs,cplAhAhhh,MAhOS,MhhOS,MRPhhToAhAh,    & 
& MRGhhToAhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToAhAh(MLambda,em,gs,ZcplAhAhhh,MAhOS,MhhOS,               & 
& MRPhhToAhAh,MRGhhToAhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhToAhAh(MLambda,em,gs,cplAhAhhh,MAh,Mhh,MRPhhToAhAh,        & 
& MRGhhToAhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToAhAh(MLambda,em,gs,ZcplAhAhhh,MAh,Mhh,MRPhhToAhAh,       & 
& MRGhhToAhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhToAhAh(cplAhAhhh,ctcplAhAhhh,MAh,MAh2,Mhh,             & 
& Mhh2,ZfAh,Zfhh,AmpWavehhToAhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,   & 
& cplAhhhhhhh1,cplAhhhHpmcHpm1,AmpVertexhhToAhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,   & 
& cplAhhhhhhh1,cplAhhhHpmcHpm1,AmpVertexIRdrhhToAhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhAh,ZcplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,           & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,            & 
& cplAhAhHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHpmcHpm1,             & 
& AmpVertexIRoshhToAhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& ZcplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,          & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,   & 
& cplAhhhhhhh1,cplAhhhHpmcHpm1,AmpVertexIRoshhToAhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,         & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,           & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,            & 
& cplAhAhHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHpmcHpm1,             & 
& AmpVertexIRoshhToAhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,   & 
& cplAhhhhhhh1,cplAhhhHpmcHpm1,AmpVertexIRoshhToAhAh)

 End if 
 End if 
AmpVertexhhToAhAh = AmpVertexhhToAhAh -  AmpVertexIRdrhhToAhAh! +  AmpVertexIRoshhToAhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToAhAh=0._dp 
AmpVertexZhhToAhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhToAhAh(gt2,:,:) = AmpWaveZhhToAhAh(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhToAhAh(gt1,:,:) 
AmpVertexZhhToAhAh(gt2,:,:)= AmpVertexZhhToAhAh(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhToAhAh(gt1,:,:) 
 End Do 
End Do 
AmpWavehhToAhAh=AmpWaveZhhToAhAh 
AmpVertexhhToAhAh= AmpVertexZhhToAhAh
! Final State 1 
AmpWaveZhhToAhAh=0._dp 
AmpVertexZhhToAhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhToAhAh(:,gt2,:) = AmpWaveZhhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWavehhToAhAh(:,gt1,:) 
AmpVertexZhhToAhAh(:,gt2,:)= AmpVertexZhhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpVertexhhToAhAh(:,gt1,:) 
 End Do 
End Do 
AmpWavehhToAhAh=AmpWaveZhhToAhAh 
AmpVertexhhToAhAh= AmpVertexZhhToAhAh
! Final State 2 
AmpWaveZhhToAhAh=0._dp 
AmpVertexZhhToAhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=2,3
    Do gt3=gt2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTohhAh(cplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhTohhAh)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTohhAh(ZcplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreehhTohhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTohhAh(MLambda,em,gs,cplAhhhhh,MAhOS,MhhOS,MRPhhTohhAh,    & 
& MRGhhTohhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTohhAh(MLambda,em,gs,ZcplAhhhhh,MAhOS,MhhOS,               & 
& MRPhhTohhAh,MRGhhTohhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTohhAh(MLambda,em,gs,cplAhhhhh,MAh,Mhh,MRPhhTohhAh,        & 
& MRGhhTohhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTohhAh(MLambda,em,gs,ZcplAhhhhh,MAh,Mhh,MRPhhTohhAh,       & 
& MRGhhTohhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTohhAh(cplAhhhhh,ctcplAhhhhh,MAh,MAh2,Mhh,             & 
& Mhh2,ZfAh,Zfhh,AmpWavehhTohhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplAhAhAhhh1,            & 
& cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplhhhhhhhh1,cplhhhhHpmcHpm1,AmpVertexhhTohhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplAhAhAhhh1,            & 
& cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplhhhhhhhh1,cplhhhhHpmcHpm1,AmpVertexIRdrhhTohhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,         & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,              & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,           & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,      & 
& cplhhhhhhhh1,cplhhhhHpmcHpm1,AmpVertexIRoshhTohhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,            & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplAhAhAhhh1,            & 
& cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplhhhhhhhh1,cplhhhhHpmcHpm1,AmpVertexIRoshhTohhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,         & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,       & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,           & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,      & 
& cplhhhhhhhh1,cplhhhhHpmcHpm1,AmpVertexIRoshhTohhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplAhAhAhhh1,            & 
& cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplhhhhhhhh1,cplhhhhHpmcHpm1,AmpVertexIRoshhTohhAh)

 End if 
 End if 
AmpVertexhhTohhAh = AmpVertexhhTohhAh -  AmpVertexIRdrhhTohhAh! +  AmpVertexIRoshhTohhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTohhAh=0._dp 
AmpVertexZhhTohhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTohhAh(gt2,:,:) = AmpWaveZhhTohhAh(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhAh(gt1,:,:) 
AmpVertexZhhTohhAh(gt2,:,:)= AmpVertexZhhTohhAh(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTohhAh(gt1,:,:) 
 End Do 
End Do 
AmpWavehhTohhAh=AmpWaveZhhTohhAh 
AmpVertexhhTohhAh= AmpVertexZhhTohhAh
! Final State 1 
AmpWaveZhhTohhAh=0._dp 
AmpVertexZhhTohhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTohhAh(:,gt2,:) = AmpWaveZhhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhAh(:,gt1,:) 
AmpVertexZhhTohhAh(:,gt2,:)= AmpVertexZhhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexhhTohhAh(:,gt1,:) 
 End Do 
End Do 
AmpWavehhTohhAh=AmpWaveZhhTohhAh 
AmpVertexhhTohhAh= AmpVertexZhhTohhAh
! Final State 2 
AmpWaveZhhTohhAh=0._dp 
AmpVertexZhhTohhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Ah VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhToAhVZ(cplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,MVZ2,           & 
& AmpTreehhToAhVZ)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhToAhVZ(ZcplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,               & 
& MVZ2,AmpTreehhToAhVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhToAhVZ(MLambda,em,gs,cplAhhhVZ,MAhOS,MhhOS,MVZOS,          & 
& MRPhhToAhVZ,MRGhhToAhVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToAhVZ(MLambda,em,gs,ZcplAhhhVZ,MAhOS,MhhOS,               & 
& MVZOS,MRPhhToAhVZ,MRGhhToAhVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhToAhVZ(MLambda,em,gs,cplAhhhVZ,MAh,Mhh,MVZ,MRPhhToAhVZ,    & 
& MRGhhToAhVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToAhVZ(MLambda,em,gs,ZcplAhhhVZ,MAh,Mhh,MVZ,               & 
& MRPhhToAhVZ,MRGhhToAhVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhToAhVZ(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,             & 
& Mhh2,MVZ,MVZ2,ZfAh,Zfhh,ZfVZ,AmpWavehhToAhVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToAhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,      & 
& cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexhhToAhVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,      & 
& cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexIRdrhhToAhVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,         & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,              & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,         & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,        & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,            & 
& cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,& 
& cplhhcHpmVWmVZ1,AmpVertexIRoshhToAhVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,            & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,      & 
& cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexIRoshhToAhVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,         & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,         & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,        & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,            & 
& cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,& 
& cplhhcHpmVWmVZ1,AmpVertexIRoshhToAhVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToAhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,         & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,       & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,      & 
& cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexIRoshhToAhVZ)

 End if 
 End if 
AmpVertexhhToAhVZ = AmpVertexhhToAhVZ -  AmpVertexIRdrhhToAhVZ! +  AmpVertexIRoshhToAhVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToAhVZ=0._dp 
AmpVertexZhhToAhVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhToAhVZ(:,gt2,:) = AmpWaveZhhToAhVZ(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhToAhVZ(:,gt1,:) 
AmpVertexZhhToAhVZ(:,gt2,:)= AmpVertexZhhToAhVZ(:,gt2,:) + ZRUZH(gt2,gt1)*AmpVertexhhToAhVZ(:,gt1,:) 
 End Do 
End Do 
AmpWavehhToAhVZ=AmpWaveZhhToAhVZ 
AmpVertexhhToAhVZ= AmpVertexZhhToAhVZ
! Final State 1 
AmpWaveZhhToAhVZ=0._dp 
AmpVertexZhhToAhVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Cha) Cha
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTocChaCha(cplcChaChahhL,cplcChaChahhR,MCha,            & 
& Mhh,MCha2,Mhh2,AmpTreehhTocChaCha)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTocChaCha(ZcplcChaChahhL,ZcplcChaChahhR,               & 
& MCha,Mhh,MCha2,Mhh2,AmpTreehhTocChaCha)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocChaCha(MLambda,em,gs,cplcChaChahhL,cplcChaChahhR,       & 
& MChaOS,MhhOS,MRPhhTocChaCha,MRGhhTocChaCha)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocChaCha(MLambda,em,gs,ZcplcChaChahhL,ZcplcChaChahhR,     & 
& MChaOS,MhhOS,MRPhhTocChaCha,MRGhhTocChaCha)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTocChaCha(MLambda,em,gs,cplcChaChahhL,cplcChaChahhR,       & 
& MCha,Mhh,MRPhhTocChaCha,MRGhhTocChaCha)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocChaCha(MLambda,em,gs,ZcplcChaChahhL,ZcplcChaChahhR,     & 
& MCha,Mhh,MRPhhTocChaCha,MRGhhTocChaCha)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTocChaCha(cplcChaChahhL,cplcChaChahhR,ctcplcChaChahhL, & 
& ctcplcChaChahhR,MCha,MCha2,Mhh,Mhh2,Zfhh,ZfLm,ZfLp,AmpWavehhTocChaCha)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTocChaCha(MAh,MCha,MChi,Mhh,MHpm,MVP,MVWm,           & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcChaChaAhL,               & 
& cplcChaChaAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,        & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,  & 
& cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,AmpVertexhhTocChaCha)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocChaCha(MAh,MCha,MChi,Mhh,MHpm,MVP,             & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,        & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,  & 
& cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,AmpVertexIRdrhhTocChaCha)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocChaCha(MAhOS,MChaOS,MChiOS,MhhOS,              & 
& MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& MVZ2OS,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,       & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,ZcplcChaChahhL,ZcplcChaChahhR,            & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,     & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocChaCha)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocChaCha(MAh,MCha,MChi,Mhh,MHpm,MVP,             & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,        & 
& cplChiChacVWmR,ZcplcChaChahhL,ZcplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,              & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,   & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,        & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocChaCha)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocChaCha(MAhOS,MChaOS,MChiOS,MhhOS,              & 
& MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& MVZ2OS,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,       & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,              & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,     & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocChaCha)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocChaCha(MAh,MCha,MChi,Mhh,MHpm,MVP,             & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,        & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,  & 
& cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,AmpVertexIRoshhTocChaCha)

 End if 
 End if 
AmpVertexhhTocChaCha = AmpVertexhhTocChaCha -  AmpVertexIRdrhhTocChaCha! +  AmpVertexIRoshhTocChaCha ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocChaCha=0._dp 
AmpVertexZhhTocChaCha=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocChaCha(:,gt2,:,:) = AmpWaveZhhTocChaCha(:,gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTocChaCha(:,gt1,:,:) 
AmpVertexZhhTocChaCha(:,gt2,:,:)= AmpVertexZhhTocChaCha(:,gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTocChaCha(:,gt1,:,:) 
 End Do 
End Do 
AmpWavehhTocChaCha=AmpWaveZhhTocChaCha 
AmpVertexhhTocChaCha= AmpVertexZhhTocChaCha
! Final State 1 
AmpWaveZhhTocChaCha=0._dp 
AmpVertexZhhTocChaCha=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocChaCha(1,:,gt2,:) = AmpWaveZhhTocChaCha(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpWavehhTocChaCha(1,:,gt1,:) 
AmpVertexZhhTocChaCha(1,:,gt2,:)= AmpVertexZhhTocChaCha(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpVertexhhTocChaCha(1,:,gt1,:) 
AmpWaveZhhTocChaCha(2,:,gt2,:) = AmpWaveZhhTocChaCha(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpWavehhTocChaCha(2,:,gt1,:) 
AmpVertexZhhTocChaCha(2,:,gt2,:)= AmpVertexZhhTocChaCha(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpVertexhhTocChaCha(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocChaCha=AmpWaveZhhTocChaCha 
AmpVertexhhTocChaCha= AmpVertexZhhTocChaCha
! Final State 2 
AmpWaveZhhTocChaCha=0._dp 
AmpVertexZhhTocChaCha=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocChaCha(1,:,:,gt2) = AmpWaveZhhTocChaCha(1,:,:,gt2)+ZRUUM(gt2,gt1)*AmpWavehhTocChaCha(1,:,:,gt1) 
AmpVertexZhhTocChaCha(1,:,:,gt2)= AmpVertexZhhTocChaCha(1,:,:,gt2)+ZRUUM(gt2,gt1)*AmpVertexhhTocChaCha(1,:,:,gt1) 
AmpWaveZhhTocChaCha(2,:,:,gt2) = AmpWaveZhhTocChaCha(2,:,:,gt2)+ZRUUP(gt2,gt1)*AmpWavehhTocChaCha(2,:,:,gt1) 
AmpVertexZhhTocChaCha(2,:,:,gt2)= AmpVertexZhhTocChaCha(2,:,:,gt2)+ZRUUP(gt2,gt1)*AmpVertexhhTocChaCha(2,:,:,gt1) 
 End Do 
End Do 
AmpWavehhTocChaCha=AmpWaveZhhTocChaCha 
AmpVertexhhTocChaCha= AmpVertexZhhTocChaCha
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocChaCha = AmpVertexhhTocChaCha  +  AmpVertexIRoshhTocChaCha
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->bar[Cha] Cha -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocChaCha = AmpTreehhTocChaCha 
 AmpSum2hhTocChaCha = AmpTreehhTocChaCha + 2._dp*AmpWavehhTocChaCha + 2._dp*AmpVertexhhTocChaCha  
Else 
 AmpSumhhTocChaCha = AmpTreehhTocChaCha + AmpWavehhTocChaCha + AmpVertexhhTocChaCha
 AmpSum2hhTocChaCha = AmpTreehhTocChaCha + AmpWavehhTocChaCha + AmpVertexhhTocChaCha 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocChaCha = AmpTreehhTocChaCha
 AmpSum2hhTocChaCha = AmpTreehhTocChaCha 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,2
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MChaOS(gt2))+Abs(MChaOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MCha(gt2))+Abs(MCha(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTocChaCha = AmpTreehhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MCha(gt2),MCha(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocChaCha(gt1, gt2, gt3) 
  AmpSum2hhTocChaCha = 2._dp*AmpWavehhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MCha(gt2),MCha(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocChaCha(gt1, gt2, gt3) 
  AmpSum2hhTocChaCha = 2._dp*AmpVertexhhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MCha(gt2),MCha(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocChaCha(gt1, gt2, gt3) 
  AmpSum2hhTocChaCha = AmpTreehhTocChaCha + 2._dp*AmpWavehhTocChaCha + 2._dp*AmpVertexhhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MCha(gt2),MCha(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocChaCha(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocChaCha = AmpTreehhTocChaCha
  Call SquareAmp_StoFF(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
  AmpSqTreehhTocChaCha(gt1, gt2, gt3) = AmpSqhhTocChaCha(gt1, gt2, gt3)  
  AmpSum2hhTocChaCha = + 2._dp*AmpWavehhTocChaCha + 2._dp*AmpVertexhhTocChaCha
  Call SquareAmp_StoFF(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
  AmpSqhhTocChaCha(gt1, gt2, gt3) = AmpSqhhTocChaCha(gt1, gt2, gt3) + AmpSqTreehhTocChaCha(gt1, gt2, gt3)  
Else  
  AmpSum2hhTocChaCha = AmpTreehhTocChaCha
  Call SquareAmp_StoFF(Mhh(gt1),MCha(gt2),MCha(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
  AmpSqTreehhTocChaCha(gt1, gt2, gt3) = AmpSqhhTocChaCha(gt1, gt2, gt3)  
  AmpSum2hhTocChaCha = + 2._dp*AmpWavehhTocChaCha + 2._dp*AmpVertexhhTocChaCha
  Call SquareAmp_StoFF(Mhh(gt1),MCha(gt2),MCha(gt3),AmpSumhhTocChaCha(:,gt1, gt2, gt3),AmpSum2hhTocChaCha(:,gt1, gt2, gt3),AmpSqhhTocChaCha(gt1, gt2, gt3)) 
  AmpSqhhTocChaCha(gt1, gt2, gt3) = AmpSqhhTocChaCha(gt1, gt2, gt3) + AmpSqTreehhTocChaCha(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTocChaCha(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqhhTocChaCha(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MChaOS(gt2),MChaOS(gt3),helfactor*AmpSqhhTocChaCha(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MCha(gt2),MCha(gt3),helfactor*AmpSqhhTocChaCha(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocChaCha(gt1, gt2, gt3) + MRGhhTocChaCha(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocChaCha(gt1, gt2, gt3) + MRGhhTocChaCha(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! Chi Chi
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhToChiChi(cplChiChihhL,cplChiChihhR,MChi,               & 
& Mhh,MChi2,Mhh2,AmpTreehhToChiChi)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhToChiChi(ZcplChiChihhL,ZcplChiChihhR,MChi,             & 
& Mhh,MChi2,Mhh2,AmpTreehhToChiChi)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhToChiChi(MLambda,em,gs,cplChiChihhL,cplChiChihhR,          & 
& MChiOS,MhhOS,MRPhhToChiChi,MRGhhToChiChi)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToChiChi(MLambda,em,gs,ZcplChiChihhL,ZcplChiChihhR,        & 
& MChiOS,MhhOS,MRPhhToChiChi,MRGhhToChiChi)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhToChiChi(MLambda,em,gs,cplChiChihhL,cplChiChihhR,          & 
& MChi,Mhh,MRPhhToChiChi,MRGhhToChiChi)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToChiChi(MLambda,em,gs,ZcplChiChihhL,ZcplChiChihhR,        & 
& MChi,Mhh,MRPhhToChiChi,MRGhhToChiChi)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhToChiChi(cplChiChihhL,cplChiChihhR,ctcplChiChihhL,     & 
& ctcplChiChihhR,MChi,MChi2,Mhh,Mhh2,Zfhh,ZfL0,AmpWavehhToChiChi)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToChiChi(MAh,MCha,MChi,Mhh,MHpm,MVWm,MVZ,            & 
& MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhToChiChi)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToChiChi(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,        & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRdrhhToChiChi)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToChiChi(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplAhAhhh,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR, & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,ZcplChiChihhL,               & 
& ZcplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,  & 
& cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,AmpVertexIRoshhToChiChi)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToChiChi(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,        & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,ZcplChiChihhL,ZcplChiChihhR,cplChiChiVZL,cplChiChiVZR,     & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhToChiChi)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToChiChi(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplAhAhhh,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR, & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR, & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& AmpVertexIRoshhToChiChi)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToChiChi(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,        & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhToChiChi)

 End if 
 End if 
AmpVertexhhToChiChi = AmpVertexhhToChiChi -  AmpVertexIRdrhhToChiChi! +  AmpVertexIRoshhToChiChi ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToChiChi=0._dp 
AmpVertexZhhToChiChi=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhToChiChi(:,gt2,:,:) = AmpWaveZhhToChiChi(:,gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhToChiChi(:,gt1,:,:) 
AmpVertexZhhToChiChi(:,gt2,:,:)= AmpVertexZhhToChiChi(:,gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhToChiChi(:,gt1,:,:) 
 End Do 
End Do 
AmpWavehhToChiChi=AmpWaveZhhToChiChi 
AmpVertexhhToChiChi= AmpVertexZhhToChiChi
! Final State 1 
AmpWaveZhhToChiChi=0._dp 
AmpVertexZhhToChiChi=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZhhToChiChi(1,:,gt2,:) = AmpWaveZhhToChiChi(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpWavehhToChiChi(1,:,gt1,:) 
AmpVertexZhhToChiChi(1,:,gt2,:)= AmpVertexZhhToChiChi(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpVertexhhToChiChi(1,:,gt1,:) 
AmpWaveZhhToChiChi(2,:,gt2,:) = AmpWaveZhhToChiChi(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpWavehhToChiChi(2,:,gt1,:) 
AmpVertexZhhToChiChi(2,:,gt2,:)= AmpVertexZhhToChiChi(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpVertexhhToChiChi(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhToChiChi=AmpWaveZhhToChiChi 
AmpVertexhhToChiChi= AmpVertexZhhToChiChi
! Final State 2 
AmpWaveZhhToChiChi=0._dp 
AmpVertexZhhToChiChi=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZhhToChiChi(1,:,:,gt2) = AmpWaveZhhToChiChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWavehhToChiChi(1,:,:,gt1) 
AmpVertexZhhToChiChi(1,:,:,gt2)= AmpVertexZhhToChiChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexhhToChiChi(1,:,:,gt1) 
AmpWaveZhhToChiChi(2,:,:,gt2) = AmpWaveZhhToChiChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWavehhToChiChi(2,:,:,gt1) 
AmpVertexZhhToChiChi(2,:,:,gt2)= AmpVertexZhhToChiChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexhhToChiChi(2,:,:,gt1) 
 End Do 
End Do 
AmpWavehhToChiChi=AmpWaveZhhToChiChi 
AmpVertexhhToChiChi= AmpVertexZhhToChiChi
End if
If (ShiftIRdiv) Then 
AmpVertexhhToChiChi = AmpVertexhhToChiChi  +  AmpVertexIRoshhToChiChi
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Chi Chi -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToChiChi = AmpTreehhToChiChi 
 AmpSum2hhToChiChi = AmpTreehhToChiChi + 2._dp*AmpWavehhToChiChi + 2._dp*AmpVertexhhToChiChi  
Else 
 AmpSumhhToChiChi = AmpTreehhToChiChi + AmpWavehhToChiChi + AmpVertexhhToChiChi
 AmpSum2hhToChiChi = AmpTreehhToChiChi + AmpWavehhToChiChi + AmpVertexhhToChiChi 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToChiChi = AmpTreehhToChiChi
 AmpSum2hhToChiChi = AmpTreehhToChiChi 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,5
    Do gt3=gt2,5
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MChiOS(gt2))+Abs(MChiOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MChi(gt2))+Abs(MChi(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhToChiChi = AmpTreehhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MChi(gt2),MChi(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToChiChi(gt1, gt2, gt3) 
  AmpSum2hhToChiChi = 2._dp*AmpWavehhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MChi(gt2),MChi(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToChiChi(gt1, gt2, gt3) 
  AmpSum2hhToChiChi = 2._dp*AmpVertexhhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MChi(gt2),MChi(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToChiChi(gt1, gt2, gt3) 
  AmpSum2hhToChiChi = AmpTreehhToChiChi + 2._dp*AmpWavehhToChiChi + 2._dp*AmpVertexhhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(Mhh(gt1),MChi(gt2),MChi(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToChiChi(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToChiChi = AmpTreehhToChiChi
  Call SquareAmp_StoFF(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
  AmpSqTreehhToChiChi(gt1, gt2, gt3) = AmpSqhhToChiChi(gt1, gt2, gt3)  
  AmpSum2hhToChiChi = + 2._dp*AmpWavehhToChiChi + 2._dp*AmpVertexhhToChiChi
  Call SquareAmp_StoFF(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
  AmpSqhhToChiChi(gt1, gt2, gt3) = AmpSqhhToChiChi(gt1, gt2, gt3) + AmpSqTreehhToChiChi(gt1, gt2, gt3)  
Else  
  AmpSum2hhToChiChi = AmpTreehhToChiChi
  Call SquareAmp_StoFF(Mhh(gt1),MChi(gt2),MChi(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
  AmpSqTreehhToChiChi(gt1, gt2, gt3) = AmpSqhhToChiChi(gt1, gt2, gt3)  
  AmpSum2hhToChiChi = + 2._dp*AmpWavehhToChiChi + 2._dp*AmpVertexhhToChiChi
  Call SquareAmp_StoFF(Mhh(gt1),MChi(gt2),MChi(gt3),AmpSumhhToChiChi(:,gt1, gt2, gt3),AmpSum2hhToChiChi(:,gt1, gt2, gt3),AmpSqhhToChiChi(gt1, gt2, gt3)) 
  AmpSqhhToChiChi(gt1, gt2, gt3) = AmpSqhhToChiChi(gt1, gt2, gt3) + AmpSqTreehhToChiChi(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhToChiChi(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (gt2.ne.gt3) helfactor = 2._dp*helfactor 
If (AmpSqhhToChiChi(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(MhhOS(gt1),MChiOS(gt2),MChiOS(gt3),helfactor*AmpSqhhToChiChi(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp/2._dp*GammaTPS(Mhh(gt1),MChi(gt2),MChi(gt3),helfactor*AmpSqhhToChiChi(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToChiChi(gt1, gt2, gt3) + MRGhhToChiChi(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPhhToChiChi(gt1, gt2, gt3) + MRGhhToChiChi(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! bar(Fd) Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,MFd,Mhh,               & 
& MFd2,Mhh2,AmpTreehhTocFdFd)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTocFdFd(ZcplcFdFdhhL,ZcplcFdFdhhR,MFd,Mhh,             & 
& MFd2,Mhh2,AmpTreehhTocFdFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,             & 
& MFdOS,MhhOS,MRPhhTocFdFd,MRGhhTocFdFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFdFd(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,           & 
& MFdOS,MhhOS,MRPhhTocFdFd,MRGhhTocFdFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTocFdFd(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,             & 
& MFd,Mhh,MRPhhTocFdFd,MRGhhTocFdFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFdFd(MLambda,em,gs,ZcplcFdFdhhL,ZcplcFdFdhhR,           & 
& MFd,Mhh,MRPhhTocFdFd,MRGhhTocFdFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTocFdFd(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,         & 
& ctcplcFdFdhhR,MFd,MFd2,Mhh,Mhh2,ZfFDL,ZfFDR,Zfhh,AmpWavehhTocFdFd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTocFdFd(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,              & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhTocFdFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFdFd(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRdrhhTocFdFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFdFd(MAhOS,MFdOS,MFuOS,MhhOS,MHpmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHpm2OS,MVG2,MVP2,MVWm2OS,            & 
& MVZ2OS,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,ZcplcFdFdhhL,             & 
& ZcplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,              & 
& cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,             & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFdFd(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,ZcplcFdFdhhL,ZcplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,     & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFdFd(MAhOS,MFdOS,MFuOS,MhhOS,MHpmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHpm2OS,MVG2,MVP2,MVWm2OS,            & 
& MVZ2OS,cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,             & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFdFd(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFdFdAhL,         & 
& cplcFdFdAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFdFd)

 End if 
 End if 
AmpVertexhhTocFdFd = AmpVertexhhTocFdFd -  AmpVertexIRdrhhTocFdFd! +  AmpVertexIRoshhTocFdFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
AmpWaveZhhTocFdFd(1,:,gt2,:) = AmpWaveZhhTocFdFd(1,:,gt2,:)+ZRUZDR(gt2,gt1)*AmpWavehhTocFdFd(1,:,gt1,:) 
AmpVertexZhhTocFdFd(1,:,gt2,:)= AmpVertexZhhTocFdFd(1,:,gt2,:)+ZRUZDR(gt2,gt1)*AmpVertexhhTocFdFd(1,:,gt1,:) 
AmpWaveZhhTocFdFd(2,:,gt2,:) = AmpWaveZhhTocFdFd(2,:,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWavehhTocFdFd(2,:,gt1,:) 
AmpVertexZhhTocFdFd(2,:,gt2,:)= AmpVertexZhhTocFdFd(2,:,gt2,:)+ZRUZDLc(gt2,gt1)*AmpVertexhhTocFdFd(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFdFd=AmpWaveZhhTocFdFd 
AmpVertexhhTocFdFd= AmpVertexZhhTocFdFd
! Final State 2 
AmpWaveZhhTocFdFd=0._dp 
AmpVertexZhhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFdFd(1,:,:,gt2) = AmpWaveZhhTocFdFd(1,:,:,gt2)+ZRUZDL(gt2,gt1)*AmpWavehhTocFdFd(1,:,:,gt1) 
AmpVertexZhhTocFdFd(1,:,:,gt2)= AmpVertexZhhTocFdFd(1,:,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexhhTocFdFd(1,:,:,gt1) 
AmpWaveZhhTocFdFd(2,:,:,gt2) = AmpWaveZhhTocFdFd(2,:,:,gt2)+ZRUZDR(gt2,gt1)*AmpWavehhTocFdFd(2,:,:,gt1) 
AmpVertexZhhTocFdFd(2,:,:,gt2)= AmpVertexZhhTocFdFd(2,:,:,gt2)+ZRUZDR(gt2,gt1)*AmpVertexhhTocFdFd(2,:,:,gt1) 
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
Do gt1=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fe) Fe
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,MFe,Mhh,               & 
& MFe2,Mhh2,AmpTreehhTocFeFe)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTocFeFe(ZcplcFeFehhL,ZcplcFeFehhR,MFe,Mhh,             & 
& MFe2,Mhh2,AmpTreehhTocFeFe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,             & 
& MFeOS,MhhOS,MRPhhTocFeFe,MRGhhTocFeFe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFeFe(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,           & 
& MFeOS,MhhOS,MRPhhTocFeFe,MRGhhTocFeFe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTocFeFe(MLambda,em,gs,cplcFeFehhL,cplcFeFehhR,             & 
& MFe,Mhh,MRPhhTocFeFe,MRGhhTocFeFe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFeFe(MLambda,em,gs,ZcplcFeFehhL,ZcplcFeFehhR,           & 
& MFe,Mhh,MRPhhTocFeFe,MRGhhTocFeFe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTocFeFe(cplcFeFehhL,cplcFeFehhR,ctcplcFeFehhL,         & 
& ctcplcFeFehhR,MFe,MFe2,Mhh,Mhh2,ZfFEL,ZfFER,Zfhh,AmpWavehhTocFeFe)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTocFeFe(MAh,MFe,Mhh,MHpm,MVP,MVWm,MVZ,               & 
& MAh2,MFe2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,      & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,     & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhTocFeFe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFeFe(MAh,MFe,Mhh,MHpm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,      & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,     & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRdrhhTocFeFe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFeFe(MAhOS,MFeOS,MhhOS,MHpmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,               & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,ZcplcFeFehhL,ZcplcFeFehhR,cplcFeFeVPL,     & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,           & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFeFe(MAh,MFe,Mhh,MHpm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,      & 
& cplAhhhVZ,ZcplcFeFehhL,ZcplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFeFe(MAhOS,MFeOS,MhhOS,MHpmOS,MVP,             & 
& MVWmOS,MVZOS,MAh2OS,MFe2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,               & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,       & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,           & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFeFe(MAh,MFe,Mhh,MHpm,MVP,MVWm,MVZ,            & 
& MAh2,MFe2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,      & 
& cplAhhhVZ,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,     & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,     & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,            & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFeFe)

 End if 
 End if 
AmpVertexhhTocFeFe = AmpVertexhhTocFeFe -  AmpVertexIRdrhhTocFeFe! +  AmpVertexIRoshhTocFeFe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
AmpWaveZhhTocFeFe(1,:,gt2,:) = AmpWaveZhhTocFeFe(1,:,gt2,:)+ZRUZER(gt2,gt1)*AmpWavehhTocFeFe(1,:,gt1,:) 
AmpVertexZhhTocFeFe(1,:,gt2,:)= AmpVertexZhhTocFeFe(1,:,gt2,:)+ZRUZER(gt2,gt1)*AmpVertexhhTocFeFe(1,:,gt1,:) 
AmpWaveZhhTocFeFe(2,:,gt2,:) = AmpWaveZhhTocFeFe(2,:,gt2,:)+ZRUZELc(gt2,gt1)*AmpWavehhTocFeFe(2,:,gt1,:) 
AmpVertexZhhTocFeFe(2,:,gt2,:)= AmpVertexZhhTocFeFe(2,:,gt2,:)+ZRUZELc(gt2,gt1)*AmpVertexhhTocFeFe(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFeFe=AmpWaveZhhTocFeFe 
AmpVertexhhTocFeFe= AmpVertexZhhTocFeFe
! Final State 2 
AmpWaveZhhTocFeFe=0._dp 
AmpVertexZhhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFeFe(1,:,:,gt2) = AmpWaveZhhTocFeFe(1,:,:,gt2)+ZRUZEL(gt2,gt1)*AmpWavehhTocFeFe(1,:,:,gt1) 
AmpVertexZhhTocFeFe(1,:,:,gt2)= AmpVertexZhhTocFeFe(1,:,:,gt2)+ZRUZEL(gt2,gt1)*AmpVertexhhTocFeFe(1,:,:,gt1) 
AmpWaveZhhTocFeFe(2,:,:,gt2) = AmpWaveZhhTocFeFe(2,:,:,gt2)+ZRUZER(gt2,gt1)*AmpWavehhTocFeFe(2,:,:,gt1) 
AmpVertexZhhTocFeFe(2,:,:,gt2)= AmpVertexZhhTocFeFe(2,:,:,gt2)+ZRUZER(gt2,gt1)*AmpVertexhhTocFeFe(2,:,:,gt1) 
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
Do gt1=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fu) Fu
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,MFu,Mhh,               & 
& MFu2,Mhh2,AmpTreehhTocFuFu)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTocFuFu(ZcplcFuFuhhL,ZcplcFuFuhhR,MFu,Mhh,             & 
& MFu2,Mhh2,AmpTreehhTocFuFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,             & 
& MFuOS,MhhOS,MRPhhTocFuFu,MRGhhTocFuFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFuFu(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,           & 
& MFuOS,MhhOS,MRPhhTocFuFu,MRGhhTocFuFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTocFuFu(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,             & 
& MFu,Mhh,MRPhhTocFuFu,MRGhhTocFuFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocFuFu(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,           & 
& MFu,Mhh,MRPhhTocFuFu,MRGhhTocFuFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTocFuFu(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,         & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,ZfFUL,ZfFUR,Zfhh,AmpWavehhTocFuFu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTocFuFu(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,MVWm,           & 
& MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,   & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,              & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhTocFuFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFuFu(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,         & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,   & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,              & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRdrhhTocFuFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFuFu(MAhOS,MFdOS,MFuOS,MhhOS,MHpmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHpm2OS,MVG2,MVP2,MVWm2OS,            & 
& MVZ2OS,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,ZcplcFuFuhhL,      & 
& ZcplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,            & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,               & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFuFu(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,         & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,   & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,       & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,              & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFuFu(MAhOS,MFdOS,MFuOS,MhhOS,MHpmOS,           & 
& MVG,MVP,MVWmOS,MVZOS,MAh2OS,MFd2OS,MFu2OS,Mhh2OS,MHpm2OS,MVG2,MVP2,MVWm2OS,            & 
& MVZ2OS,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,              & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,               & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocFuFu(MAh,MFd,MFu,Mhh,MHpm,MVG,MVP,             & 
& MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHpm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,         & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,   & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,              & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRoshhTocFuFu)

 End if 
 End if 
AmpVertexhhTocFuFu = AmpVertexhhTocFuFu -  AmpVertexIRdrhhTocFuFu! +  AmpVertexIRoshhTocFuFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
AmpWaveZhhTocFuFu(1,:,gt2,:) = AmpWaveZhhTocFuFu(1,:,gt2,:)+ZRUZUR(gt2,gt1)*AmpWavehhTocFuFu(1,:,gt1,:) 
AmpVertexZhhTocFuFu(1,:,gt2,:)= AmpVertexZhhTocFuFu(1,:,gt2,:)+ZRUZUR(gt2,gt1)*AmpVertexhhTocFuFu(1,:,gt1,:) 
AmpWaveZhhTocFuFu(2,:,gt2,:) = AmpWaveZhhTocFuFu(2,:,gt2,:)+ZRUZULc(gt2,gt1)*AmpWavehhTocFuFu(2,:,gt1,:) 
AmpVertexZhhTocFuFu(2,:,gt2,:)= AmpVertexZhhTocFuFu(2,:,gt2,:)+ZRUZULc(gt2,gt1)*AmpVertexhhTocFuFu(2,:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocFuFu=AmpWaveZhhTocFuFu 
AmpVertexhhTocFuFu= AmpVertexZhhTocFuFu
! Final State 2 
AmpWaveZhhTocFuFu=0._dp 
AmpVertexZhhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocFuFu(1,:,:,gt2) = AmpWaveZhhTocFuFu(1,:,:,gt2)+ZRUZUL(gt2,gt1)*AmpWavehhTocFuFu(1,:,:,gt1) 
AmpVertexZhhTocFuFu(1,:,:,gt2)= AmpVertexZhhTocFuFu(1,:,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexhhTocFuFu(1,:,:,gt1) 
AmpWaveZhhTocFuFu(2,:,:,gt2) = AmpWaveZhhTocFuFu(2,:,:,gt2)+ZRUZUR(gt2,gt1)*AmpWavehhTocFuFu(2,:,:,gt1) 
AmpVertexZhhTocFuFu(2,:,:,gt2)= AmpVertexZhhTocFuFu(2,:,:,gt2)+ZRUZUR(gt2,gt1)*AmpVertexhhTocFuFu(2,:,:,gt1) 
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
Do gt1=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTohhhh(cplhhhhhh,Mhh,Mhh2,AmpTreehhTohhhh)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTohhhh(Zcplhhhhhh,Mhh,Mhh2,AmpTreehhTohhhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTohhhh(MLambda,em,gs,cplhhhhhh,MhhOS,MRPhhTohhhh,          & 
& MRGhhTohhhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTohhhh(MLambda,em,gs,Zcplhhhhhh,MhhOS,MRPhhTohhhh,         & 
& MRGhhTohhhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTohhhh(MLambda,em,gs,cplhhhhhh,Mhh,MRPhhTohhhh,            & 
& MRGhhTohhhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTohhhh(MLambda,em,gs,Zcplhhhhhh,Mhh,MRPhhTohhhh,           & 
& MRGhhTohhhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTohhhh(cplhhhhhh,ctcplhhhhhh,Mhh,Mhh2,Zfhh,            & 
& AmpWavehhTohhhh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,              & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,            & 
& cplhhhhHpmcHpm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexhhTohhhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,         & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,            & 
& cplhhhhHpmcHpm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRdrhhTohhhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhhh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,             & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,            & 
& Zcplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,              & 
& cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,   & 
& AmpVertexIRoshhTohhhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,         & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,Zcplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,           & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,            & 
& cplhhhhHpmcHpm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhhh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,             & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,            & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,   & 
& AmpVertexIRoshhTohhhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,         & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcgWmgWmhh,cplcgWpCgWpChh,cplcgZgZhh,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhhhhh1,cplAhhhhhhh1,cplhhhhhhhh1,            & 
& cplhhhhHpmcHpm1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,AmpVertexIRoshhTohhhh)

 End if 
 End if 
AmpVertexhhTohhhh = AmpVertexhhTohhhh -  AmpVertexIRdrhhTohhhh! +  AmpVertexIRoshhTohhhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTohhhh=0._dp 
AmpVertexZhhTohhhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTohhhh(gt2,:,:) = AmpWaveZhhTohhhh(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhhh(gt1,:,:) 
AmpVertexZhhTohhhh(gt2,:,:)= AmpVertexZhhTohhhh(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTohhhh(gt1,:,:) 
 End Do 
End Do 
AmpWavehhTohhhh=AmpWaveZhhTohhhh 
AmpVertexhhTohhhh= AmpVertexZhhTohhhh
! Final State 1 
AmpWaveZhhTohhhh=0._dp 
AmpVertexZhhTohhhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTohhhh(:,gt2,:) = AmpWaveZhhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhTohhhh(:,gt1,:) 
AmpVertexZhhTohhhh(:,gt2,:)= AmpVertexZhhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexhhTohhhh(:,gt1,:) 
 End Do 
End Do 
AmpWavehhTohhhh=AmpWaveZhhTohhhh 
AmpVertexhhTohhhh= AmpVertexZhhTohhhh
! Final State 2 
AmpWaveZhhTohhhh=0._dp 
AmpVertexZhhTohhhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=gt2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Conjg(Hpm) Hpm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTocHpmHpm(cplhhHpmcHpm,Mhh,MHpm,Mhh2,MHpm2,            & 
& AmpTreehhTocHpmHpm)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTocHpmHpm(ZcplhhHpmcHpm,Mhh,MHpm,Mhh2,MHpm2,           & 
& AmpTreehhTocHpmHpm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocHpmHpm(MLambda,em,gs,cplhhHpmcHpm,MhhOS,MHpmOS,         & 
& MRPhhTocHpmHpm,MRGhhTocHpmHpm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocHpmHpm(MLambda,em,gs,ZcplhhHpmcHpm,MhhOS,               & 
& MHpmOS,MRPhhTocHpmHpm,MRGhhTocHpmHpm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTocHpmHpm(MLambda,em,gs,cplhhHpmcHpm,Mhh,MHpm,             & 
& MRPhhTocHpmHpm,MRGhhTocHpmHpm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocHpmHpm(MLambda,em,gs,ZcplhhHpmcHpm,Mhh,MHpm,            & 
& MRPhhTocHpmHpm,MRGhhTocHpmHpm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTocHpmHpm(cplhhHpmcHpm,ctcplhhHpmcHpm,Mhh,             & 
& Mhh2,MHpm,MHpm2,Zfhh,ZfHpm,AmpWavehhTocHpmHpm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,               & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgWmgWmhh,cplcgZgWmcHpm,        & 
& cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,            & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,      & 
& cplAhhhHpmcHpm1,cplhhhhHpmcHpm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,       & 
& cplhhcHpmVWmVZ1,cplHpmHpmcHpmcHpm1,cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,AmpVertexhhTocHpmHpm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgWmgWmhh,cplcgZgWmcHpm,        & 
& cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,            & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,      & 
& cplAhhhHpmcHpm1,cplhhhhHpmcHpm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,       & 
& cplhhcHpmVWmVZ1,cplHpmHpmcHpmcHpm1,cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,AmpVertexIRdrhhTocHpmHpm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocHpmHpm(MAhOS,MChaOS,MChiOS,MFdOS,              & 
& MFeOS,MFuOS,MhhOS,MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,               & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,        & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,    & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,          & 
& cplcFeFvHpmR,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,       & 
& cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhhhhh,ZcplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,            & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,cplAhhhHpmcHpm1,cplhhhhHpmcHpm1,             & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmHpmcHpmcHpm1,    & 
& cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,AmpVertexIRoshhTocHpmHpm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgWmgWmhh,cplcgZgWmcHpm,        & 
& cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhhhhh,         & 
& ZcplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,           & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,      & 
& cplAhhhHpmcHpm1,cplhhhhHpmcHpm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,       & 
& cplhhcHpmVWmVZ1,cplHpmHpmcHpmcHpm1,cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,AmpVertexIRoshhTocHpmHpm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocHpmHpm(MAhOS,MChaOS,MChiOS,MFdOS,              & 
& MFeOS,MFuOS,MhhOS,MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,               & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,        & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,    & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,          & 
& cplcFeFvHpmR,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,       & 
& cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,          & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,            & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,cplAhhhHpmcHpm1,cplhhhhHpmcHpm1,             & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmHpmcHpmcHpm1,    & 
& cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,AmpVertexIRoshhTocHpmHpm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,             & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,     & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgWmgWmhh,cplcgZgWmcHpm,        & 
& cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,            & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,      & 
& cplAhhhHpmcHpm1,cplhhhhHpmcHpm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,       & 
& cplhhcHpmVWmVZ1,cplHpmHpmcHpmcHpm1,cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,AmpVertexIRoshhTocHpmHpm)

 End if 
 End if 
AmpVertexhhTocHpmHpm = AmpVertexhhTocHpmHpm -  AmpVertexIRdrhhTocHpmHpm! +  AmpVertexIRoshhTocHpmHpm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocHpmHpm=0._dp 
AmpVertexZhhTocHpmHpm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhTocHpmHpm(gt2,:,:) = AmpWaveZhhTocHpmHpm(gt2,:,:)+ZRUZH(gt2,gt1)*AmpWavehhTocHpmHpm(gt1,:,:) 
AmpVertexZhhTocHpmHpm(gt2,:,:)= AmpVertexZhhTocHpmHpm(gt2,:,:) + ZRUZH(gt2,gt1)*AmpVertexhhTocHpmHpm(gt1,:,:) 
 End Do 
End Do 
AmpWavehhTocHpmHpm=AmpWaveZhhTocHpmHpm 
AmpVertexhhTocHpmHpm= AmpVertexZhhTocHpmHpm
! Final State 1 
AmpWaveZhhTocHpmHpm=0._dp 
AmpVertexZhhTocHpmHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHpmHpm(:,gt2,:) = AmpWaveZhhTocHpmHpm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWavehhTocHpmHpm(:,gt1,:) 
AmpVertexZhhTocHpmHpm(:,gt2,:)= AmpVertexZhhTocHpmHpm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexhhTocHpmHpm(:,gt1,:) 
 End Do 
End Do 
AmpWavehhTocHpmHpm=AmpWaveZhhTocHpmHpm 
AmpVertexhhTocHpmHpm= AmpVertexZhhTocHpmHpm
! Final State 2 
AmpWaveZhhTocHpmHpm=0._dp 
AmpVertexZhhTocHpmHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhTocHpmHpm(:,:,gt2) = AmpWaveZhhTocHpmHpm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWavehhTocHpmHpm(:,:,gt1) 
AmpVertexZhhTocHpmHpm(:,:,gt2)= AmpVertexZhhTocHpmHpm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexhhTocHpmHpm(:,:,gt1) 
 End Do 
End Do 
AmpWavehhTocHpmHpm=AmpWaveZhhTocHpmHpm 
AmpVertexhhTocHpmHpm= AmpVertexZhhTocHpmHpm
End if
If (ShiftIRdiv) Then 
AmpVertexhhTocHpmHpm = AmpVertexhhTocHpmHpm  +  AmpVertexIRoshhTocHpmHpm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->conj[Hpm] Hpm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhTocHpmHpm = AmpTreehhTocHpmHpm 
 AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm + 2._dp*AmpWavehhTocHpmHpm + 2._dp*AmpVertexhhTocHpmHpm  
Else 
 AmpSumhhTocHpmHpm = AmpTreehhTocHpmHpm + AmpWavehhTocHpmHpm + AmpVertexhhTocHpmHpm
 AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm + AmpWavehhTocHpmHpm + AmpVertexhhTocHpmHpm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhTocHpmHpm = AmpTreehhTocHpmHpm
 AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MHpmOS(gt2))+Abs(MHpmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MHpm(gt2))+Abs(MHpm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHpm(gt2),MHpm(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhTocHpmHpm(gt1, gt2, gt3) 
  AmpSum2hhTocHpmHpm = 2._dp*AmpWavehhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHpm(gt2),MHpm(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhTocHpmHpm(gt1, gt2, gt3) 
  AmpSum2hhTocHpmHpm = 2._dp*AmpVertexhhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHpm(gt2),MHpm(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhTocHpmHpm(gt1, gt2, gt3) 
  AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm + 2._dp*AmpWavehhTocHpmHpm + 2._dp*AmpVertexhhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(Mhh(gt1),MHpm(gt2),MHpm(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhTocHpmHpm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm
  Call SquareAmp_StoSS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqTreehhTocHpmHpm(gt1, gt2, gt3) = AmpSqhhTocHpmHpm(gt1, gt2, gt3)  
  AmpSum2hhTocHpmHpm = + 2._dp*AmpWavehhTocHpmHpm + 2._dp*AmpVertexhhTocHpmHpm
  Call SquareAmp_StoSS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqhhTocHpmHpm(gt1, gt2, gt3) = AmpSqhhTocHpmHpm(gt1, gt2, gt3) + AmpSqTreehhTocHpmHpm(gt1, gt2, gt3)  
Else  
  AmpSum2hhTocHpmHpm = AmpTreehhTocHpmHpm
  Call SquareAmp_StoSS(Mhh(gt1),MHpm(gt2),MHpm(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqTreehhTocHpmHpm(gt1, gt2, gt3) = AmpSqhhTocHpmHpm(gt1, gt2, gt3)  
  AmpSum2hhTocHpmHpm = + 2._dp*AmpWavehhTocHpmHpm + 2._dp*AmpVertexhhTocHpmHpm
  Call SquareAmp_StoSS(Mhh(gt1),MHpm(gt2),MHpm(gt3),AmpSumhhTocHpmHpm(gt1, gt2, gt3),AmpSum2hhTocHpmHpm(gt1, gt2, gt3),AmpSqhhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqhhTocHpmHpm(gt1, gt2, gt3) = AmpSqhhTocHpmHpm(gt1, gt2, gt3) + AmpSqTreehhTocHpmHpm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqhhTocHpmHpm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhTocHpmHpm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(MhhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),helfactor*AmpSqhhTocHpmHpm(gt1, gt2, gt3))
Else 
  gP1Lhh(gt1,i4) = 1._dp*GammaTPS(Mhh(gt1),MHpm(gt2),MHpm(gt3),helfactor*AmpSqhhTocHpmHpm(gt1, gt2, gt3))
End if 
If ((Abs(MRPhhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGhhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPhhTocHpmHpm(gt1, gt2, gt3) + MRGhhTocHpmHpm(gt1, gt2, gt3)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPhhTocHpmHpm(gt1, gt2, gt3) + MRGhhTocHpmHpm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! Hpm Conjg(VWm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhToHpmcVWm(cplhhHpmcVWm,Mhh,MHpm,MVWm,Mhh2,             & 
& MHpm2,MVWm2,AmpTreehhToHpmcVWm)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhToHpmcVWm(ZcplhhHpmcVWm,Mhh,MHpm,MVWm,Mhh2,            & 
& MHpm2,MVWm2,AmpTreehhToHpmcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhToHpmcVWm(MLambda,em,gs,cplhhHpmcVWm,MhhOS,MHpmOS,         & 
& MVWmOS,MRPhhToHpmcVWm,MRGhhToHpmcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToHpmcVWm(MLambda,em,gs,ZcplhhHpmcVWm,MhhOS,               & 
& MHpmOS,MVWmOS,MRPhhToHpmcVWm,MRGhhToHpmcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhToHpmcVWm(MLambda,em,gs,cplhhHpmcVWm,Mhh,MHpm,             & 
& MVWm,MRPhhToHpmcVWm,MRGhhToHpmcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToHpmcVWm(MLambda,em,gs,ZcplhhHpmcVWm,Mhh,MHpm,            & 
& MVWm,MRPhhToHpmcVWm,MRGhhToHpmcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhToHpmcVWm(cplhhHpmcVWm,ctcplhhHpmcVWm,Mhh,             & 
& Mhh2,MHpm,MHpm2,MVWm,MVWm2,Zfhh,ZfHpm,ZfVWm,AmpWavehhToHpmcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,               & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgZgAhh,cplcgWmgAHpm,cplcgWmgWmhh,           & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,          & 
& cplHpmcHpmcVWmVWm1,AmpVertexhhToHpmcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgZgAhh,cplcgWmgAHpm,cplcgWmgWmhh,           & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,          & 
& cplHpmcHpmcVWmVWm1,AmpVertexIRdrhhToHpmcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToHpmcVWm(MAhOS,MChaOS,MChiOS,MFdOS,              & 
& MFeOS,MFuOS,MhhOS,MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,               & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,        & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,   & 
& cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcgZgAhh,cplcgWmgAHpm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,       & 
& cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcVWm,cplhhhhhh,GosZcplhhHpmcHpm,       & 
& ZcplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,GosZcplHpmcVWmVP,       & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplhhhhcVWmVWm1,   & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplHpmcHpmcVWmVWm1,AmpVertexIRoshhToHpmcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgZgAhh,cplcgWmgAHpm,cplcgWmgWmhh,           & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhhhhh,GZcplhhHpmcHpm,ZcplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,       & 
& cplhhVZVZ,cplHpmcHpmVP,GZcplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVPVWm,          & 
& cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,          & 
& cplHpmcHpmcVWmVWm1,AmpVertexIRoshhToHpmcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToHpmcVWm(MAhOS,MChaOS,MChiOS,MFdOS,              & 
& MFeOS,MFuOS,MhhOS,MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,               & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,        & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,   & 
& cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcgZgAhh,cplcgWmgAHpm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,       & 
& cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,cplcgWpCgZcVWm,cplhhhhhh,GcplhhHpmcHpm,          & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVP,GcplHpmcVWmVP,           & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplhhhhcVWmVWm1,   & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplHpmcHpmcVWmVWm1,AmpVertexIRoshhToHpmcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcgZgAhh,cplcgWmgAHpm,cplcgWmgWmhh,           & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,          & 
& cplHpmcHpmcVWmVWm1,AmpVertexIRoshhToHpmcVWm)

 End if 
 End if 
AmpVertexhhToHpmcVWm = AmpVertexhhToHpmcVWm -  AmpVertexIRdrhhToHpmcVWm! +  AmpVertexIRoshhToHpmcVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhToHpmcVWm=0._dp 
AmpVertexZhhToHpmcVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZhhToHpmcVWm(:,gt2,:) = AmpWaveZhhToHpmcVWm(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWavehhToHpmcVWm(:,gt1,:) 
AmpVertexZhhToHpmcVWm(:,gt2,:)= AmpVertexZhhToHpmcVWm(:,gt2,:) + ZRUZH(gt2,gt1)*AmpVertexhhToHpmcVWm(:,gt1,:) 
 End Do 
End Do 
AmpWavehhToHpmcVWm=AmpWaveZhhToHpmcVWm 
AmpVertexhhToHpmcVWm= AmpVertexZhhToHpmcVWm
! Final State 1 
AmpWaveZhhToHpmcVWm=0._dp 
AmpVertexZhhToHpmcVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZhhToHpmcVWm(:,:,gt2) = AmpWaveZhhToHpmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWavehhToHpmcVWm(:,:,gt1) 
AmpVertexZhhToHpmcVWm(:,:,gt2)= AmpVertexZhhToHpmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexhhToHpmcVWm(:,:,gt1) 
 End Do 
End Do 
AmpWavehhToHpmcVWm=AmpWaveZhhToHpmcVWm 
AmpVertexhhToHpmcVWm= AmpVertexZhhToHpmcVWm
End if
If (ShiftIRdiv) Then 
AmpVertexhhToHpmcVWm = AmpVertexhhToHpmcVWm  +  AmpVertexIRoshhToHpmcVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ hh->Hpm conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumhhToHpmcVWm = AmpTreehhToHpmcVWm 
 AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm + 2._dp*AmpWavehhToHpmcVWm + 2._dp*AmpVertexhhToHpmcVWm  
Else 
 AmpSumhhToHpmcVWm = AmpTreehhToHpmcVWm + AmpWavehhToHpmcVWm + AmpVertexhhToHpmcVWm
 AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm + AmpWavehhToHpmcVWm + AmpVertexhhToHpmcVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumhhToHpmcVWm = AmpTreehhToHpmcVWm
 AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(MHpmOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(MHpm(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHpm(gt2),MVWm,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqhhToHpmcVWm(gt1, gt2) 
  AmpSum2hhToHpmcVWm = 2._dp*AmpWavehhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHpm(gt2),MVWm,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqhhToHpmcVWm(gt1, gt2) 
  AmpSum2hhToHpmcVWm = 2._dp*AmpVertexhhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHpm(gt2),MVWm,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqhhToHpmcVWm(gt1, gt2) 
  AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm + 2._dp*AmpWavehhToHpmcVWm + 2._dp*AmpVertexhhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MhhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(Mhh(gt1),MHpm(gt2),MVWm,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqhhToHpmcVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm
  Call SquareAmp_StoSV(MhhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
  AmpSqTreehhToHpmcVWm(gt1, gt2) = AmpSqhhToHpmcVWm(gt1, gt2)  
  AmpSum2hhToHpmcVWm = + 2._dp*AmpWavehhToHpmcVWm + 2._dp*AmpVertexhhToHpmcVWm
  Call SquareAmp_StoSV(MhhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
  AmpSqhhToHpmcVWm(gt1, gt2) = AmpSqhhToHpmcVWm(gt1, gt2) + AmpSqTreehhToHpmcVWm(gt1, gt2)  
Else  
  AmpSum2hhToHpmcVWm = AmpTreehhToHpmcVWm
  Call SquareAmp_StoSV(Mhh(gt1),MHpm(gt2),MVWm,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
  AmpSqTreehhToHpmcVWm(gt1, gt2) = AmpSqhhToHpmcVWm(gt1, gt2)  
  AmpSum2hhToHpmcVWm = + 2._dp*AmpWavehhToHpmcVWm + 2._dp*AmpVertexhhToHpmcVWm
  Call SquareAmp_StoSV(Mhh(gt1),MHpm(gt2),MVWm,AmpSumhhToHpmcVWm(:,gt1, gt2),AmpSum2hhToHpmcVWm(:,gt1, gt2),AmpSqhhToHpmcVWm(gt1, gt2)) 
  AmpSqhhToHpmcVWm(gt1, gt2) = AmpSqhhToHpmcVWm(gt1, gt2) + AmpSqTreehhToHpmcVWm(gt1, gt2)  
End if  
Else  
  AmpSqhhToHpmcVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqhhToHpmcVWm(gt1, gt2).eq.0._dp) Then 
  gP1Lhh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(MhhOS(gt1),MHpmOS(gt2),MVWmOS,helfactor*AmpSqhhToHpmcVWm(gt1, gt2))
Else 
  gP1Lhh(gt1,i4) = 2._dp*GammaTPS(Mhh(gt1),MHpm(gt2),MVWm,helfactor*AmpSqhhToHpmcVWm(gt1, gt2))
End if 
If ((Abs(MRPhhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1Lhh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPhhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGhhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPhhToHpmcVWm(gt1, gt2) + MRGhhToHpmcVWm(gt1, gt2)) 
  gP1Lhh(gt1,i4) = gP1Lhh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPhhToHpmcVWm(gt1, gt2) + MRGhhToHpmcVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1Lhh(gt1,i4) 
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
! Conjg(VWm) VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhTocVWmVWm(cplhhcVWmVWm,Mhh,MVWm,Mhh2,MVWm2,            & 
& AmpTreehhTocVWmVWm)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhTocVWmVWm(ZcplhhcVWmVWm,Mhh,MVWm,Mhh2,MVWm2,           & 
& AmpTreehhTocVWmVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocVWmVWm(MLambda,em,gs,cplhhcVWmVWm,MhhOS,MVWmOS,         & 
& MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocVWmVWm(MLambda,em,gs,ZcplhhcVWmVWm,MhhOS,               & 
& MVWmOS,MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhTocVWmVWm(MLambda,em,gs,cplhhcVWmVWm,Mhh,MVWm,             & 
& MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhTocVWmVWm(MLambda,em,gs,ZcplhhcVWmVWm,Mhh,MVWm,            & 
& MRPhhTocVWmVWm,MRGhhTocVWmVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhTocVWmVWm(cplhhcVWmVWm,ctcplhhcVWmVWm,Mhh,             & 
& Mhh2,MVWm,MVWm2,Zfhh,ZfVWm,AmpWavehhTocVWmVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTocVWmVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,               & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,          & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,         & 
& cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,   & 
& cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,            & 
& cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,& 
& cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,& 
& cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,             & 
& cplcVWmVWmVZVZ1Q,AmpVertexhhTocVWmVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocVWmVWm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,          & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,         & 
& cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,   & 
& cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,            & 
& cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,& 
& cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,& 
& cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,             & 
& cplcVWmVWmVZVZ1Q,AmpVertexIRdrhhTocVWmVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocVWmVWm(MAhOS,MChaOS,MChiOS,MFdOS,              & 
& MFeOS,MFuOS,MhhOS,MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,               & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,        & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,   & 
& cplChiChihhL,cplChiChihhR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,       & 
& cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,     & 
& cplhhhhhh,GosZcplhhHpmcHpm,cplhhHpmcVWm,GosZcplhhcHpmVWm,ZcplhhcVWmVWm,cplhhVZVZ,      & 
& GosZcplHpmcVWmVP,cplHpmcVWmVZ,GosZcplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,              & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,          & 
& cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,& 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocVWmVWm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,          & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,         & 
& cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,   & 
& cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,GZcplhhHpmcHpm,cplhhHpmcVWm,          & 
& GZcplhhcHpmVWm,ZcplhhcVWmVWm,cplhhVZVZ,GZcplHpmcVWmVP,cplHpmcVWmVZ,GZcplcHpmVPVWm,     & 
& cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,& 
& cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,& 
& cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,             & 
& cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocVWmVWm(MAhOS,MChaOS,MChiOS,MFdOS,              & 
& MFeOS,MFuOS,MhhOS,MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,               & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,        & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,   & 
& cplChiChihhL,cplChiChihhR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,       & 
& cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,     & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,GcplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,              & 
& cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,         & 
& cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,       & 
& cplhhcHpmVWmVZ1,cplHpmcHpmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,            & 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhTocVWmVWm(MAh,MCha,MChi,MFd,MFe,MFu,              & 
& Mhh,MHpm,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,           & 
& MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuVWmL,          & 
& cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcgZgAhh,cplcgWmgAVWm,cplcgWpCgAcVWm,         & 
& cplcgWmgWmhh,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpChh,cplcgAgWpCVWm,cplcgZgWpCVWm,   & 
& cplcgZgZhh,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,            & 
& cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplhhhhcVWmVWm1,cplhhHpmcVWmVP1,& 
& cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmcVWmVWm1,cplcVWmcVWmVWmVWm1Q,& 
& cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,             & 
& cplcVWmVWmVZVZ1Q,AmpVertexIRoshhTocVWmVWm)

 End if 
 End if 
AmpVertexhhTocVWmVWm = AmpVertexhhTocVWmVWm -  AmpVertexIRdrhhTocVWmVWm! +  AmpVertexIRoshhTocVWmVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZhhTocVWmVWm=0._dp 
AmpVertexZhhTocVWmVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! VZ VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_hhToVZVZ(cplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,AmpTreehhToVZVZ)

  Else 
Call Amplitude_Tree_NMSSMEFT_hhToVZVZ(ZcplhhVZVZ,Mhh,MVZ,Mhh2,MVZ2,AmpTreehhToVZVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,MhhOS,MVZOS,MRPhhToVZVZ,    & 
& MRGhhToVZVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToVZVZ(MLambda,em,gs,ZcplhhVZVZ,MhhOS,MVZOS,               & 
& MRPhhToVZVZ,MRGhhToVZVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_hhToVZVZ(MLambda,em,gs,cplhhVZVZ,Mhh,MVZ,MRPhhToVZVZ,        & 
& MRGhhToVZVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_hhToVZVZ(MLambda,em,gs,ZcplhhVZVZ,Mhh,MVZ,MRPhhToVZVZ,       & 
& MRGhhToVZVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhToVZVZ(cplhhVZVZ,ctcplhhVZVZ,Mhh,Mhh2,MVZ,             & 
& MVZ2,Zfhh,ZfVZ,AmpWavehhToVZVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToVZVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,              & 
& cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,        & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,            & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,          & 
& cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,            & 
& cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,cplHpmcHpmVZVZ1,cplcVWmVWmVZVZ2Q,         & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexhhToVZVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToVZVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,         & 
& cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,        & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,            & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,          & 
& cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,            & 
& cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,cplHpmcHpmVZVZ1,cplcVWmVWmVZVZ2Q,         & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRdrhhToVZVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToVZVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,ZcplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,           & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,   & 
& cplHpmcHpmVZVZ1,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToVZVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,         & 
& cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,        & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,            & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,          & 
& cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& ZcplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,           & 
& cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,cplHpmcHpmVZVZ1,cplcVWmVWmVZVZ2Q,         & 
& cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToVZVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,            & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,   & 
& cplHpmcHpmVZVZ1,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q,cplcVWmVWmVZVZ1Q,AmpVertexIRoshhToVZVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_hhToVZVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,         & 
& cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,        & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,            & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,          & 
& cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,            & 
& cplhhhhVZVZ1,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,cplHpmcHpmVZVZ1,cplcVWmVWmVZVZ2Q,         & 
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
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
End If 
!---------------- 
! Ah VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSMEFT_hhToAhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,             & 
& MhhOS,Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWavehhToAhVP)

 Else 
Call Amplitude_WAVE_NMSSMEFT_hhToAhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,             & 
& MhhOS,Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWavehhToAhVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhToAhVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,               & 
& MhhOS,MHpmOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,            & 
& MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,          & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,     & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,         & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,AmpVertexhhToAhVP)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhToAhVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,               & 
& MhhOS,MHpmOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,            & 
& MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,          & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,     & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,         & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,AmpVertexhhToAhVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_hhToAhVP(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,             & 
& Mhh2,MVP,MVP2,MVZ,MVZ2,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWavehhToAhVP)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToAhVP(MAh,MCha,MFd,MFe,MFu,Mhh,MHpm,MVP,            & 
& MVWm,MAh2,MCha2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplcChaChahhL,      & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,          & 
& cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,       & 
& cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplhhHpmcVWmVP1,& 
& cplhhcHpmVPVWm1,AmpVertexhhToAhVP)

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
Do gt1=1,3
i4 = isave 
  Do gt2=2,3
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fv bar(Fv)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhToFvcFv(MFeOS,MhhOS,MHpmOS,MVWmOS,MVZOS,             & 
& MFe2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,            & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,      & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,           & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhToFvcFv)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhToFvcFv(MFeOS,MhhOS,MHpmOS,MVWmOS,MVZOS,             & 
& MFe2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,            & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,      & 
& cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,           & 
& cplhhcVWmVWm,cplhhVZVZ,AmpVertexhhToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToFvcFv(MFe,Mhh,MHpm,MVWm,MVZ,MFe2,Mhh2,             & 
& MHpm2,MVWm2,MVZ2,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,    & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,         & 
& cplcFvFvVZR,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,             & 
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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MhhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(Mhh(gt1)).gt.(Abs(0.)+Abs(0.))))) Then 
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! hh VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhVP(MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHpmOS,MVP,MVWmOS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,     & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,   & 
& AmpVertexhhTohhVP)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhVP(MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHpmOS,MVP,MVWmOS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,     & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,   & 
& AmpVertexhhTohhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhVP(MCha,MFd,MFe,MFu,Mhh,MHpm,MVP,MVWm,           & 
& MCha2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,  & 
& cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,      & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,         & 
& cplcVWmVPVWm,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,AmpVertexhhTohhVP)

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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! hh VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,             & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,              & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexhhTohhVZ)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,MFe2OS,MFu2OS,           & 
& Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcChaChahhL,             & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,              & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexhhTohhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhTohhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,              & 
& cplAhhhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,           & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,        & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,            & 
& cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexhhTohhVZ)

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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VG VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhToVGVG(MFdOS,MFuOS,MhhOS,MVG,MFd2OS,MFu2OS,          & 
& Mhh2OS,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhToVGVG(MFdOS,MFuOS,MhhOS,MVG,MFd2OS,MFu2OS,          & 
& Mhh2OS,MVG2,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,AmpVertexhhToVGVG)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToVGVG(MFd,MFu,Mhh,MVG,MFd2,MFu2,Mhh2,               & 
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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VP VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhToVPVP(MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHpmOS,MVP,MVWmOS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,     & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,   & 
& cplHpmcHpmVPVP1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,AmpVertexhhToVPVP)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhToVPVP(MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHpmOS,MVP,MVWmOS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,     & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,   & 
& cplHpmcHpmVPVP1,cplcVWmVPVPVWm3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,AmpVertexhhToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToVPVP(MCha,MFd,MFe,MFu,Mhh,MHpm,MVP,MVWm,           & 
& MCha2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,  & 
& cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,      & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,         & 
& cplcVWmVPVWm,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,cplHpmcHpmVPVP1,cplcVWmVPVPVWm3Q,         & 
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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VP VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_hhToVPVZ(MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHpmOS,MVP,MVWmOS,MVZOS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,              & 
& MVWm2OS,MVZ2OS,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,             & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVP,      & 
& cplcgWpCgWpCVZ,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,       & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVWmVZ,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,          & 
& cplHpmcHpmVPVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexhhToVPVZ)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_hhToVPVZ(MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,               & 
& MHpmOS,MVP,MVWmOS,MVZOS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MVP2,              & 
& MVWm2OS,MVZ2OS,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,             & 
& cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVP,      & 
& cplcgWpCgWpCVZ,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,       & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVWmVZ,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,          & 
& cplHpmcHpmVPVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ1Q,AmpVertexhhToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_hhToVPVZ(MCha,MFd,MFe,MFu,Mhh,MHpm,MVP,MVWm,           & 
& MVZ,MCha2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChahhL,cplcChaChahhR,       & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVP,             & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplhhHpmcHpm,cplhhHpmcVWm,   & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,         & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,   & 
& cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmVPVZ1,cplcVWmVPVWmVZ3Q,cplcVWmVPVWmVZ2Q,     & 
& cplcVWmVPVWmVZ1Q,AmpVertexhhToVPVZ)

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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
End Subroutine OneLoopDecay_hh

End Module Wrapper_OneLoopDecay_hh_NMSSMEFT
