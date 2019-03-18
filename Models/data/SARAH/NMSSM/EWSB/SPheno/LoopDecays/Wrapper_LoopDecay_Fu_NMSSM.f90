! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:27 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Fu_NMSSM
Use Model_Data_NMSSM 
Use Kinematics 
Use OneLoopDecay_Fu_NMSSM 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Fu(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,              & 
& MSe2OS,MhhOS,Mhh2OS,MAhOS,MAh2OS,MHpmOS,MHpm2OS,MChiOS,MChi2OS,MChaOS,MCha2OS,         & 
& MFeOS,MFe2OS,MFdOS,MFd2OS,MFuOS,MFu2OS,MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,             & 
& MVWm2OS,ZDOS,ZVOS,ZUOS,ZEOS,ZHOS,ZAOS,ZPOS,ZNOS,UMOS,UPOS,ZELOS,ZEROS,ZDLOS,           & 
& ZDROS,ZULOS,ZUROS,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,           & 
& md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,dg1,dg2,dg3,dYd,dTd,dYe,dTe,dlam,dTlam,              & 
& dkap,dTk,dYu,dTu,dmq2,dml2,dmHd2,dmHu2,dmd2,dmu2,dme2,dms2,dM1,dM2,dM3,dvd,            & 
& dvu,dvS,dpG,dZD,dZV,dZU,dZE,dZH,dZA,dZP,dZN,dUM,dUP,dZEL,dZER,dZDL,dZDR,               & 
& dZUL,dZUR,dSinTW,dCosTW,dTanTW,ZfVG,ZffG,ZfFvL,ZfVP,ZfVZ,ZfVWm,ZfSd,ZfSv,              & 
& ZfSu,ZfSe,Zfhh,ZfAh,ZfHpm,ZfL0,ZfLm,ZfLp,ZfFEL,ZfFER,ZfFDL,ZfFDR,ZfFUL,ZfFUR,          & 
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHpmVWm,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,       & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChaFucSdL,cplChaFucSdR,           & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,              & 
& cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,         & 
& cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,            & 
& cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,   & 
& cplHpmSucSd,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSucSdVWm,    & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplVGVGVG,ctcplcChacFuSdL,ctcplcChacFuSdR,            & 
& ctcplcFuChiSuL,ctcplcFuChiSuR,ctcplcFuFdcHpmL,ctcplcFuFdcHpmR,ctcplcFuFdcVWmL,         & 
& ctcplcFuFdcVWmR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplcFuFuhhL,ctcplcFuFuhhR,               & 
& ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,   & 
& ctcplcFuGluSuL,ctcplcFuGluSuR,GcplcFuFdcHpmL,GcplcFuFdcHpmR,GcplcHpmVPVWm,             & 
& GcplHpmcVWmVP,GosZcplcFuFdcHpmL,GosZcplcFuFdcHpmR,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,   & 
& GZcplcFuFdcHpmL,GZcplcFuFdcHpmR,GZcplcHpmVPVWm,GZcplHpmcVWmVP,ZcplcChacFuSdL,          & 
& ZcplcChacFuSdR,ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,   & 
& ZcplcFdFdVPR,ZcplcFdFuHpmL,ZcplcFdFuHpmR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplcFuChiSuL,    & 
& ZcplcFuChiSuR,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,             & 
& ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,         & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFuGluSuL,ZcplcFuGluSuR,       & 
& ZcplChaFucSdL,ZcplChaFucSdR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplcHpmVPVWm,ZcplcVWmVPVWm,   & 
& ZcplGluFucSuL,ZcplGluFucSuR,ZcplGluGluVGL,ZcplGluGluVGR,ZcplHpmcHpmVP,ZcplHpmcVWmVP,   & 
& ZcplSdcSdVG,ZcplSdcSdVP,ZcplSucSuVG,ZcplSucSuVP,ZcplVGVGVG,ZRUZD,ZRUZV,ZRUZU,          & 
& ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,          & 
& ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LFu)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp),Intent(in) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp),Intent(in) :: dg1,dg2,dg3,dmHd2,dmHu2,dms2,dvd,dvu,dvS,dZH(3,3),dZA(3,3),dZP(2,2),dSinTW,           & 
& dCosTW,dTanTW

Complex(dp),Intent(in) :: dYd(3,3),dTd(3,3),dYe(3,3),dTe(3,3),dlam,dTlam,dkap,dTk,dYu(3,3),dTu(3,3),            & 
& dmq2(3,3),dml2(3,3),dmd2(3,3),dmu2(3,3),dme2(3,3),dM1,dM2,dM3,dpG,dZD(6,6),            & 
& dZV(3,3),dZU(6,6),dZE(6,6),dZN(5,5),dUM(2,2),dUP(2,2),dZEL(3,3),dZER(3,3),             & 
& dZDL(3,3),dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhcHpmVWm(3,2),cplAhhhhh(3,3,3),cplAhhhVZ(3,3),  & 
& cplAhHpmcHpm(3,2,2),cplAhHpmcVWm(3,2),cplAhSdcSd(3,6,6),cplAhSucSu(3,6,6),             & 
& cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),   & 
& cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),       & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),     & 
& cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),     & 
& cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),       & 
& cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),           & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),            & 
& cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuChiSuL(3,5,6),             & 
& cplcFuChiSuR(3,5,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),      & 
& cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplChaFucSdL(2,3,6),& 
& cplChaFucSdR(2,3,6),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplChiChacVWmL(5,2),   & 
& cplChiChacVWmR(5,2),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplChiFdcSdL(5,3,6),           & 
& cplChiFdcSdR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcHpmVPVWm(2),           & 
& cplcHpmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),         & 
& cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm(3,2),       & 
& cplhhcVWmVWm(3),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplhhHpmcVWm(3,2),cplhhSdcSd(3,6,6),& 
& cplhhSucSu(3,6,6),cplhhVZVZ(3),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),cplHpmcVWmVP(2),    & 
& cplHpmcVWmVZ(2),cplHpmSucSd(2,6,6),cplSdcHpmcSu(6,2,6),cplSdcSdVG(6,6),cplSdcSdVP(6,6),& 
& cplSdcSdVZ(6,6),cplSdcSucVWm(6,6),cplSucSdVWm(6,6),cplSucSuVG(6,6),cplSucSuVP(6,6),    & 
& cplSucSuVZ(6,6),cplVGVGVG,ctcplcChacFuSdL(2,3,6),ctcplcChacFuSdR(2,3,6),               & 
& ctcplcFuChiSuL(3,5,6),ctcplcFuChiSuR(3,5,6),ctcplcFuFdcHpmL(3,3,2),ctcplcFuFdcHpmR(3,3,2),& 
& ctcplcFuFdcVWmL(3,3),ctcplcFuFdcVWmR(3,3),ctcplcFuFuAhL(3,3,3),ctcplcFuFuAhR(3,3,3),   & 
& ctcplcFuFuhhL(3,3,3),ctcplcFuFuhhR(3,3,3),ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3),       & 
& ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3),           & 
& ctcplcFuGluSuL(3,6),ctcplcFuGluSuR(3,6),GcplcFuFdcHpmL(3,3,2),GcplcFuFdcHpmR(3,3,2),   & 
& GcplcHpmVPVWm(2),GcplHpmcVWmVP(2),GosZcplcFuFdcHpmL(3,3,2),GosZcplcFuFdcHpmR(3,3,2),   & 
& GosZcplcHpmVPVWm(2),GosZcplHpmcVWmVP(2),GZcplcFuFdcHpmL(3,3,2),GZcplcFuFdcHpmR(3,3,2), & 
& GZcplcHpmVPVWm(2),GZcplHpmcVWmVP(2),ZcplcChacFuSdL(2,3,6),ZcplcChacFuSdR(2,3,6),       & 
& ZcplcChaChaVPL(2,2),ZcplcChaChaVPR(2,2),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),           & 
& ZcplcFdFdVPL(3,3),ZcplcFdFdVPR(3,3),ZcplcFdFuHpmL(3,3,2),ZcplcFdFuHpmR(3,3,2),         & 
& ZcplcFdFuVWmL(3,3),ZcplcFdFuVWmR(3,3),ZcplcFuChiSuL(3,5,6),ZcplcFuChiSuR(3,5,6)

Complex(dp),Intent(in) :: ZcplcFuFdcHpmL(3,3,2),ZcplcFuFdcHpmR(3,3,2),ZcplcFuFdcVWmL(3,3),ZcplcFuFdcVWmR(3,3),   & 
& ZcplcFuFuAhL(3,3,3),ZcplcFuFuAhR(3,3,3),ZcplcFuFuhhL(3,3,3),ZcplcFuFuhhR(3,3,3),       & 
& ZcplcFuFuVGL(3,3),ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),               & 
& ZcplcFuFuVZL(3,3),ZcplcFuFuVZR(3,3),ZcplcFuGluSuL(3,6),ZcplcFuGluSuR(3,6),             & 
& ZcplChaFucSdL(2,3,6),ZcplChaFucSdR(2,3,6),ZcplChiFucSuL(5,3,6),ZcplChiFucSuR(5,3,6),   & 
& ZcplcHpmVPVWm(2),ZcplcVWmVPVWm,ZcplGluFucSuL(3,6),ZcplGluFucSuR(3,6),ZcplGluGluVGL,    & 
& ZcplGluGluVGR,ZcplHpmcHpmVP(2,2),ZcplHpmcVWmVP(2),ZcplSdcSdVG(6,6),ZcplSdcSdVP(6,6),   & 
& ZcplSucSuVG(6,6),ZcplSucSuVP(6,6),ZcplVGVGVG

Real(dp), Intent(in) :: em, gs 
Complex(dp),Intent(in) :: ZfVG,ZffG,ZfFvL(3,3),ZfVP,ZfVZ,ZfVWm,ZfSd(6,6),ZfSv(3,3),ZfSu(6,6),ZfSe(6,6),         & 
& Zfhh(3,3),ZfAh(3,3),ZfHpm(2,2),ZfL0(5,5),ZfLm(2,2),ZfLp(2,2),ZfFEL(3,3),               & 
& ZfFER(3,3),ZfFDL(3,3),ZfFDR(3,3),ZfFUL(3,3),ZfFUR(3,3),ZfVPVZ,ZfVZVP

Real(dp),Intent(in) :: MSdOS(6),MSd2OS(6),MSvOS(3),MSv2OS(3),MSuOS(6),MSu2OS(6),MSeOS(6),MSe2OS(6),          & 
& MhhOS(3),Mhh2OS(3),MAhOS(3),MAh2OS(3),MHpmOS(2),MHpm2OS(2),MChiOS(5),MChi2OS(5),       & 
& MChaOS(2),MCha2OS(2),MFeOS(3),MFe2OS(3),MFdOS(3),MFd2OS(3),MFuOS(3),MFu2OS(3),         & 
& MGluOS,MGlu2OS,MVZOS,MVZ2OS,MVWmOS,MVWm2OS,ZHOS(3,3),ZAOS(3,3),ZPOS(2,2)

Complex(dp),Intent(in) :: ZDOS(6,6),ZVOS(3,3),ZUOS(6,6),ZEOS(6,6),ZNOS(5,5),UMOS(2,2),UPOS(2,2),ZELOS(3,3),     & 
& ZEROS(3,3),ZDLOS(3,3),ZDROS(3,3),ZULOS(3,3),ZUROS(3,3)

Complex(dp),Intent(in) :: ZRUZD(6,6),ZRUZV(3,3),ZRUZU(6,6),ZRUZE(6,6),ZRUZH(3,3),ZRUZA(3,3),ZRUZP(2,2),         & 
& ZRUZN(5,5),ZRUUM(2,2),ZRUUP(2,2),ZRUZEL(3,3),ZRUZER(3,3),ZRUZDL(3,3),ZRUZDR(3,3),      & 
& ZRUZUL(3,3),ZRUZUR(3,3)

Real(dp), Intent(in) :: MLambda, deltaM 
Real(dp), Intent(out) :: gP1LFu(3,78) 
Integer, Intent(out) :: kont 
Real(dp) :: MVG,MVP,MVG2,MVP2, helfactor, phasespacefactor 
Integer :: i1,i2,i3,i4, isave, gt1, gt2, gt3 

Complex(dp) :: ZRUZDc(6, 6) 
Complex(dp) :: ZRUZVc(3, 3) 
Complex(dp) :: ZRUZUc(6, 6) 
Complex(dp) :: ZRUZEc(6, 6) 
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
Real(dp) :: MRPFuToFuAh(3,3,3),MRGFuToFuAh(3,3,3), MRPZFuToFuAh(3,3,3),MRGZFuToFuAh(3,3,3) 
Real(dp) :: MVPFuToFuAh(3,3,3) 
Real(dp) :: RMsqTreeFuToFuAh(3,3,3),RMsqWaveFuToFuAh(3,3,3),RMsqVertexFuToFuAh(3,3,3) 
Complex(dp) :: AmpTreeFuToFuAh(2,3,3,3),AmpWaveFuToFuAh(2,3,3,3)=(0._dp,0._dp),AmpVertexFuToFuAh(2,3,3,3)& 
 & ,AmpVertexIRosFuToFuAh(2,3,3,3),AmpVertexIRdrFuToFuAh(2,3,3,3), AmpSumFuToFuAh(2,3,3,3), AmpSum2FuToFuAh(2,3,3,3) 
Complex(dp) :: AmpTreeZFuToFuAh(2,3,3,3),AmpWaveZFuToFuAh(2,3,3,3),AmpVertexZFuToFuAh(2,3,3,3) 
Real(dp) :: AmpSqFuToFuAh(3,3,3),  AmpSqTreeFuToFuAh(3,3,3) 
Real(dp) :: MRPFuToChiSu(3,5,6),MRGFuToChiSu(3,5,6), MRPZFuToChiSu(3,5,6),MRGZFuToChiSu(3,5,6) 
Real(dp) :: MVPFuToChiSu(3,5,6) 
Real(dp) :: RMsqTreeFuToChiSu(3,5,6),RMsqWaveFuToChiSu(3,5,6),RMsqVertexFuToChiSu(3,5,6) 
Complex(dp) :: AmpTreeFuToChiSu(2,3,5,6),AmpWaveFuToChiSu(2,3,5,6)=(0._dp,0._dp),AmpVertexFuToChiSu(2,3,5,6)& 
 & ,AmpVertexIRosFuToChiSu(2,3,5,6),AmpVertexIRdrFuToChiSu(2,3,5,6), AmpSumFuToChiSu(2,3,5,6), AmpSum2FuToChiSu(2,3,5,6) 
Complex(dp) :: AmpTreeZFuToChiSu(2,3,5,6),AmpWaveZFuToChiSu(2,3,5,6),AmpVertexZFuToChiSu(2,3,5,6) 
Real(dp) :: AmpSqFuToChiSu(3,5,6),  AmpSqTreeFuToChiSu(3,5,6) 
Real(dp) :: MRPFuToFdcHpm(3,3,2),MRGFuToFdcHpm(3,3,2), MRPZFuToFdcHpm(3,3,2),MRGZFuToFdcHpm(3,3,2) 
Real(dp) :: MVPFuToFdcHpm(3,3,2) 
Real(dp) :: RMsqTreeFuToFdcHpm(3,3,2),RMsqWaveFuToFdcHpm(3,3,2),RMsqVertexFuToFdcHpm(3,3,2) 
Complex(dp) :: AmpTreeFuToFdcHpm(2,3,3,2),AmpWaveFuToFdcHpm(2,3,3,2)=(0._dp,0._dp),AmpVertexFuToFdcHpm(2,3,3,2)& 
 & ,AmpVertexIRosFuToFdcHpm(2,3,3,2),AmpVertexIRdrFuToFdcHpm(2,3,3,2), AmpSumFuToFdcHpm(2,3,3,2), AmpSum2FuToFdcHpm(2,3,3,2) 
Complex(dp) :: AmpTreeZFuToFdcHpm(2,3,3,2),AmpWaveZFuToFdcHpm(2,3,3,2),AmpVertexZFuToFdcHpm(2,3,3,2) 
Real(dp) :: AmpSqFuToFdcHpm(3,3,2),  AmpSqTreeFuToFdcHpm(3,3,2) 
Real(dp) :: MRPFuToFdcVWm(3,3),MRGFuToFdcVWm(3,3), MRPZFuToFdcVWm(3,3),MRGZFuToFdcVWm(3,3) 
Real(dp) :: MVPFuToFdcVWm(3,3) 
Real(dp) :: RMsqTreeFuToFdcVWm(3,3),RMsqWaveFuToFdcVWm(3,3),RMsqVertexFuToFdcVWm(3,3) 
Complex(dp) :: AmpTreeFuToFdcVWm(4,3,3),AmpWaveFuToFdcVWm(4,3,3)=(0._dp,0._dp),AmpVertexFuToFdcVWm(4,3,3)& 
 & ,AmpVertexIRosFuToFdcVWm(4,3,3),AmpVertexIRdrFuToFdcVWm(4,3,3), AmpSumFuToFdcVWm(4,3,3), AmpSum2FuToFdcVWm(4,3,3) 
Complex(dp) :: AmpTreeZFuToFdcVWm(4,3,3),AmpWaveZFuToFdcVWm(4,3,3),AmpVertexZFuToFdcVWm(4,3,3) 
Real(dp) :: AmpSqFuToFdcVWm(3,3),  AmpSqTreeFuToFdcVWm(3,3) 
Real(dp) :: MRPFuToFuhh(3,3,3),MRGFuToFuhh(3,3,3), MRPZFuToFuhh(3,3,3),MRGZFuToFuhh(3,3,3) 
Real(dp) :: MVPFuToFuhh(3,3,3) 
Real(dp) :: RMsqTreeFuToFuhh(3,3,3),RMsqWaveFuToFuhh(3,3,3),RMsqVertexFuToFuhh(3,3,3) 
Complex(dp) :: AmpTreeFuToFuhh(2,3,3,3),AmpWaveFuToFuhh(2,3,3,3)=(0._dp,0._dp),AmpVertexFuToFuhh(2,3,3,3)& 
 & ,AmpVertexIRosFuToFuhh(2,3,3,3),AmpVertexIRdrFuToFuhh(2,3,3,3), AmpSumFuToFuhh(2,3,3,3), AmpSum2FuToFuhh(2,3,3,3) 
Complex(dp) :: AmpTreeZFuToFuhh(2,3,3,3),AmpWaveZFuToFuhh(2,3,3,3),AmpVertexZFuToFuhh(2,3,3,3) 
Real(dp) :: AmpSqFuToFuhh(3,3,3),  AmpSqTreeFuToFuhh(3,3,3) 
Real(dp) :: MRPFuToFuVZ(3,3),MRGFuToFuVZ(3,3), MRPZFuToFuVZ(3,3),MRGZFuToFuVZ(3,3) 
Real(dp) :: MVPFuToFuVZ(3,3) 
Real(dp) :: RMsqTreeFuToFuVZ(3,3),RMsqWaveFuToFuVZ(3,3),RMsqVertexFuToFuVZ(3,3) 
Complex(dp) :: AmpTreeFuToFuVZ(4,3,3),AmpWaveFuToFuVZ(4,3,3)=(0._dp,0._dp),AmpVertexFuToFuVZ(4,3,3)& 
 & ,AmpVertexIRosFuToFuVZ(4,3,3),AmpVertexIRdrFuToFuVZ(4,3,3), AmpSumFuToFuVZ(4,3,3), AmpSum2FuToFuVZ(4,3,3) 
Complex(dp) :: AmpTreeZFuToFuVZ(4,3,3),AmpWaveZFuToFuVZ(4,3,3),AmpVertexZFuToFuVZ(4,3,3) 
Real(dp) :: AmpSqFuToFuVZ(3,3),  AmpSqTreeFuToFuVZ(3,3) 
Real(dp) :: MRPFuToGluSu(3,6),MRGFuToGluSu(3,6), MRPZFuToGluSu(3,6),MRGZFuToGluSu(3,6) 
Real(dp) :: MVPFuToGluSu(3,6) 
Real(dp) :: RMsqTreeFuToGluSu(3,6),RMsqWaveFuToGluSu(3,6),RMsqVertexFuToGluSu(3,6) 
Complex(dp) :: AmpTreeFuToGluSu(2,3,6),AmpWaveFuToGluSu(2,3,6)=(0._dp,0._dp),AmpVertexFuToGluSu(2,3,6)& 
 & ,AmpVertexIRosFuToGluSu(2,3,6),AmpVertexIRdrFuToGluSu(2,3,6), AmpSumFuToGluSu(2,3,6), AmpSum2FuToGluSu(2,3,6) 
Complex(dp) :: AmpTreeZFuToGluSu(2,3,6),AmpWaveZFuToGluSu(2,3,6),AmpVertexZFuToGluSu(2,3,6) 
Real(dp) :: AmpSqFuToGluSu(3,6),  AmpSqTreeFuToGluSu(3,6) 
Real(dp) :: MRPFuTocChaSd(3,2,6),MRGFuTocChaSd(3,2,6), MRPZFuTocChaSd(3,2,6),MRGZFuTocChaSd(3,2,6) 
Real(dp) :: MVPFuTocChaSd(3,2,6) 
Real(dp) :: RMsqTreeFuTocChaSd(3,2,6),RMsqWaveFuTocChaSd(3,2,6),RMsqVertexFuTocChaSd(3,2,6) 
Complex(dp) :: AmpTreeFuTocChaSd(2,3,2,6),AmpWaveFuTocChaSd(2,3,2,6)=(0._dp,0._dp),AmpVertexFuTocChaSd(2,3,2,6)& 
 & ,AmpVertexIRosFuTocChaSd(2,3,2,6),AmpVertexIRdrFuTocChaSd(2,3,2,6), AmpSumFuTocChaSd(2,3,2,6), AmpSum2FuTocChaSd(2,3,2,6) 
Complex(dp) :: AmpTreeZFuTocChaSd(2,3,2,6),AmpWaveZFuTocChaSd(2,3,2,6),AmpVertexZFuTocChaSd(2,3,2,6) 
Real(dp) :: AmpSqFuTocChaSd(3,2,6),  AmpSqTreeFuTocChaSd(3,2,6) 
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
isave = 1 

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fu Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_FuToFuAh(cplcFuFuAhL,cplcFuFuAhR,MAh,MFu,MAh2,              & 
& MFu2,AmpTreeFuToFuAh)

  Else 
Call Amplitude_Tree_NMSSM_FuToFuAh(ZcplcFuFuAhL,ZcplcFuFuAhR,MAh,MFu,MAh2,            & 
& MFu2,AmpTreeFuToFuAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToFuAh(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,MAhOS,           & 
& MFuOS,MRPFuToFuAh,MRGFuToFuAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToFuAh(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,               & 
& MAhOS,MFuOS,MRPFuToFuAh,MRGFuToFuAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToFuAh(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,MAh,             & 
& MFu,MRPFuToFuAh,MRGFuToFuAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToFuAh(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,               & 
& MAh,MFu,MRPFuToFuAh,MRGFuToFuAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFuAh(cplcFuFuAhL,cplcFuFuAhR,ctcplcFuFuAhL,             & 
& ctcplcFuFuAhR,MAh,MAh2,MFu,MFu2,ZfAh,ZfFUL,ZfFUR,AmpWaveFuToFuAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexFuToFuAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRdrFuToFuAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuAh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,    & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,             & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosFuToFuAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosFuToFuAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuAh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,      & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,             & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosFuToFuAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosFuToFuAh)

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
AmpWaveZFuToFuAh(1,gt2,:,:) = AmpWaveZFuToFuAh(1,gt2,:,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFuAh(1,gt1,:,:) 
AmpVertexZFuToFuAh(1,gt2,:,:)= AmpVertexZFuToFuAh(1,gt2,:,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFuAh(1,gt1,:,:) 
AmpWaveZFuToFuAh(2,gt2,:,:) = AmpWaveZFuToFuAh(2,gt2,:,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFuAh(2,gt1,:,:) 
AmpVertexZFuToFuAh(2,gt2,:,:)= AmpVertexZFuToFuAh(2,gt2,:,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFuAh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFuAh=AmpWaveZFuToFuAh 
AmpVertexFuToFuAh= AmpVertexZFuToFuAh
! Final State 1 
AmpWaveZFuToFuAh=0._dp 
AmpVertexZFuToFuAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuAh(1,:,gt2,:) = AmpWaveZFuToFuAh(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpWaveFuToFuAh(1,:,gt1,:) 
AmpVertexZFuToFuAh(1,:,gt2,:)= AmpVertexZFuToFuAh(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpVertexFuToFuAh(1,:,gt1,:) 
AmpWaveZFuToFuAh(2,:,gt2,:) = AmpWaveZFuToFuAh(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpWaveFuToFuAh(2,:,gt1,:) 
AmpVertexZFuToFuAh(2,:,gt2,:)= AmpVertexZFuToFuAh(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpVertexFuToFuAh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuAh=AmpWaveZFuToFuAh 
AmpVertexFuToFuAh= AmpVertexZFuToFuAh
! Final State 2 
AmpWaveZFuToFuAh=0._dp 
AmpVertexZFuToFuAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
    Do gt3=2,3
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
! Chi Su
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_FuToChiSu(cplcFuChiSuL,cplcFuChiSuR,MChi,MFu,               & 
& MSu,MChi2,MFu2,MSu2,AmpTreeFuToChiSu)

  Else 
Call Amplitude_Tree_NMSSM_FuToChiSu(ZcplcFuChiSuL,ZcplcFuChiSuR,MChi,MFu,             & 
& MSu,MChi2,MFu2,MSu2,AmpTreeFuToChiSu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToChiSu(MLambda,em,gs,cplcFuChiSuL,cplcFuChiSuR,              & 
& MChiOS,MFuOS,MSuOS,MRPFuToChiSu,MRGFuToChiSu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToChiSu(MLambda,em,gs,ZcplcFuChiSuL,ZcplcFuChiSuR,            & 
& MChiOS,MFuOS,MSuOS,MRPFuToChiSu,MRGFuToChiSu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToChiSu(MLambda,em,gs,cplcFuChiSuL,cplcFuChiSuR,              & 
& MChi,MFu,MSu,MRPFuToChiSu,MRGFuToChiSu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToChiSu(MLambda,em,gs,ZcplcFuChiSuL,ZcplcFuChiSuR,            & 
& MChi,MFu,MSu,MRPFuToChiSu,MRGFuToChiSu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToChiSu(cplcFuChiSuL,cplcFuChiSuR,ctcplcFuChiSuL,         & 
& ctcplcFuChiSuR,MChi,MChi2,MFu,MFu2,MSu,MSu2,ZfFUL,ZfFUR,ZfL0,ZfSu,AmpWaveFuToChiSu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToChiSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,           & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcHpmL,    & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexFuToChiSu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToChiSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,      & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcHpmL,    & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexIRdrFuToChiSu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToChiSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChiChacHpmL,           & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,ZcplcFuChiSuL,    & 
& ZcplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,               & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,           & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,             & 
& cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,cplSucSuVP,              & 
& cplSucSdVWm,cplSucSuVZ,AmpVertexIRosFuToChiSu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToChiSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,      & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,ZcplcFuChiSuL,ZcplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcHpmL,  & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexIRosFuToChiSu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToChiSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChiChacHpmL,           & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,  & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,              & 
& cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,cplSucSuVP,cplSucSdVWm,             & 
& cplSucSuVZ,AmpVertexIRosFuToChiSu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToChiSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,      & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcHpmL,    & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexIRosFuToChiSu)

 End if 
 End if 
AmpVertexFuToChiSu = AmpVertexFuToChiSu -  AmpVertexIRdrFuToChiSu! +  AmpVertexIRosFuToChiSu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToChiSu=0._dp 
AmpVertexZFuToChiSu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToChiSu(1,gt2,:,:) = AmpWaveZFuToChiSu(1,gt2,:,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToChiSu(1,gt1,:,:) 
AmpVertexZFuToChiSu(1,gt2,:,:)= AmpVertexZFuToChiSu(1,gt2,:,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToChiSu(1,gt1,:,:) 
AmpWaveZFuToChiSu(2,gt2,:,:) = AmpWaveZFuToChiSu(2,gt2,:,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToChiSu(2,gt1,:,:) 
AmpVertexZFuToChiSu(2,gt2,:,:)= AmpVertexZFuToChiSu(2,gt2,:,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToChiSu(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToChiSu=AmpWaveZFuToChiSu 
AmpVertexFuToChiSu= AmpVertexZFuToChiSu
! Final State 1 
AmpWaveZFuToChiSu=0._dp 
AmpVertexZFuToChiSu=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZFuToChiSu(1,:,gt2,:) = AmpWaveZFuToChiSu(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveFuToChiSu(1,:,gt1,:) 
AmpVertexZFuToChiSu(1,:,gt2,:)= AmpVertexZFuToChiSu(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpVertexFuToChiSu(1,:,gt1,:) 
AmpWaveZFuToChiSu(2,:,gt2,:) = AmpWaveZFuToChiSu(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveFuToChiSu(2,:,gt1,:) 
AmpVertexZFuToChiSu(2,:,gt2,:)= AmpVertexZFuToChiSu(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpVertexFuToChiSu(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToChiSu=AmpWaveZFuToChiSu 
AmpVertexFuToChiSu= AmpVertexZFuToChiSu
! Final State 2 
AmpWaveZFuToChiSu=0._dp 
AmpVertexZFuToChiSu=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZFuToChiSu(:,:,:,gt2) = AmpWaveZFuToChiSu(:,:,:,gt2)+ZRUZU(gt2,gt1)*AmpWaveFuToChiSu(:,:,:,gt1) 
AmpVertexZFuToChiSu(:,:,:,gt2)= AmpVertexZFuToChiSu(:,:,:,gt2)+ZRUZU(gt2,gt1)*AmpVertexFuToChiSu(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFuToChiSu=AmpWaveZFuToChiSu 
AmpVertexFuToChiSu= AmpVertexZFuToChiSu
End if
If (ShiftIRdiv) Then 
AmpVertexFuToChiSu = AmpVertexFuToChiSu  +  AmpVertexIRosFuToChiSu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Chi Su -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToChiSu = AmpTreeFuToChiSu 
 AmpSum2FuToChiSu = AmpTreeFuToChiSu + 2._dp*AmpWaveFuToChiSu + 2._dp*AmpVertexFuToChiSu  
Else 
 AmpSumFuToChiSu = AmpTreeFuToChiSu + AmpWaveFuToChiSu + AmpVertexFuToChiSu
 AmpSum2FuToChiSu = AmpTreeFuToChiSu + AmpWaveFuToChiSu + AmpVertexFuToChiSu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToChiSu = AmpTreeFuToChiSu
 AmpSum2FuToChiSu = AmpTreeFuToChiSu 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,5
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MChiOS(gt2))+Abs(MSuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MChi(gt2))+Abs(MSu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuToChiSu = AmpTreeFuToChiSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MChi(gt2),MSu(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToChiSu(gt1, gt2, gt3) 
  AmpSum2FuToChiSu = 2._dp*AmpWaveFuToChiSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MChi(gt2),MSu(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToChiSu(gt1, gt2, gt3) 
  AmpSum2FuToChiSu = 2._dp*AmpVertexFuToChiSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MChi(gt2),MSu(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToChiSu(gt1, gt2, gt3) 
  AmpSum2FuToChiSu = AmpTreeFuToChiSu + 2._dp*AmpWaveFuToChiSu + 2._dp*AmpVertexFuToChiSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MChi(gt2),MSu(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToChiSu(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToChiSu = AmpTreeFuToChiSu
  Call SquareAmp_FtoFS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
  AmpSqTreeFuToChiSu(gt1, gt2, gt3) = AmpSqFuToChiSu(gt1, gt2, gt3)  
  AmpSum2FuToChiSu = + 2._dp*AmpWaveFuToChiSu + 2._dp*AmpVertexFuToChiSu
  Call SquareAmp_FtoFS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
  AmpSqFuToChiSu(gt1, gt2, gt3) = AmpSqFuToChiSu(gt1, gt2, gt3) + AmpSqTreeFuToChiSu(gt1, gt2, gt3)  
Else  
  AmpSum2FuToChiSu = AmpTreeFuToChiSu
  Call SquareAmp_FtoFS(MFu(gt1),MChi(gt2),MSu(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
  AmpSqTreeFuToChiSu(gt1, gt2, gt3) = AmpSqFuToChiSu(gt1, gt2, gt3)  
  AmpSum2FuToChiSu = + 2._dp*AmpWaveFuToChiSu + 2._dp*AmpVertexFuToChiSu
  Call SquareAmp_FtoFS(MFu(gt1),MChi(gt2),MSu(gt3),AmpSumFuToChiSu(:,gt1, gt2, gt3),AmpSum2FuToChiSu(:,gt1, gt2, gt3),AmpSqFuToChiSu(gt1, gt2, gt3)) 
  AmpSqFuToChiSu(gt1, gt2, gt3) = AmpSqFuToChiSu(gt1, gt2, gt3) + AmpSqTreeFuToChiSu(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuToChiSu(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToChiSu(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MChiOS(gt2),MSuOS(gt3),helfactor*AmpSqFuToChiSu(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MChi(gt2),MSu(gt3),helfactor*AmpSqFuToChiSu(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuToChiSu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToChiSu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToChiSu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToChiSu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToChiSu(gt1, gt2, gt3) + MRGFuToChiSu(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToChiSu(gt1, gt2, gt3) + MRGFuToChiSu(gt1, gt2, gt3))
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
! Fd Conjg(Hpm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_FuToFdcHpm(cplcFuFdcHpmL,cplcFuFdcHpmR,MFd,MFu,             & 
& MHpm,MFd2,MFu2,MHpm2,AmpTreeFuToFdcHpm)

  Else 
Call Amplitude_Tree_NMSSM_FuToFdcHpm(ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,MFd,               & 
& MFu,MHpm,MFd2,MFu2,MHpm2,AmpTreeFuToFdcHpm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToFdcHpm(MLambda,em,gs,cplcFuFdcHpmL,cplcFuFdcHpmR,           & 
& MFdOS,MFuOS,MHpmOS,MRPFuToFdcHpm,MRGFuToFdcHpm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToFdcHpm(MLambda,em,gs,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,         & 
& MFdOS,MFuOS,MHpmOS,MRPFuToFdcHpm,MRGFuToFdcHpm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToFdcHpm(MLambda,em,gs,cplcFuFdcHpmL,cplcFuFdcHpmR,           & 
& MFd,MFu,MHpm,MRPFuToFdcHpm,MRGFuToFdcHpm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToFdcHpm(MLambda,em,gs,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,         & 
& MFd,MFu,MHpm,MRPFuToFdcHpm,MRGFuToFdcHpm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFdcHpm(cplcFuFdcHpmL,cplcFuFdcHpmR,ctcplcFuFdcHpmL,     & 
& ctcplcFuFdcHpmR,MFd,MFd2,MFu,MFu2,MHpm,MHpm2,ZfFDL,ZfFDR,ZfFUL,ZfFUR,ZfHpm,            & 
& AmpWaveFuToFdcHpm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFdcHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFdcSdL,cplChiFdcSdR,     & 
& cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,   & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhcHpmVWm,           & 
& cplHpmcHpmVP,cplHpmcHpmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplcHpmVPVWm,       & 
& cplcHpmVWmVZ,AmpVertexFuToFdcHpm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFdcSdL,cplChiFdcSdR,     & 
& cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,   & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhcHpmVWm,           & 
& cplHpmcHpmVP,cplHpmcHpmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplcHpmVPVWm,       & 
& cplcHpmVWmVZ,AmpVertexIRdrFuToFdcHpm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcHpm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHpmcHpm,cplAhcHpmVWm,             & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,cplcFuChiSuR,     & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,     & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplcHpmVPVWm,cplcHpmVWmVZ,AmpVertexIRosFuToFdcHpm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFdcSdL,cplChiFdcSdR,     & 
& cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcChaFdcSuL,cplcChaFdcSuR,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,cplcFuFdcVWmL,               & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,            & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,       & 
& cplcHpmVPVWm,cplcHpmVWmVZ,AmpVertexIRosFuToFdcHpm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcHpm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHpmcHpm,cplAhcHpmVWm,             & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,cplcFuChiSuR,     & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,       & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,         & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplcHpmVPVWm,cplcHpmVWmVZ,AmpVertexIRosFuToFdcHpm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFdcSdL,cplChiFdcSdR,     & 
& cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,   & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhcHpmVWm,           & 
& cplHpmcHpmVP,cplHpmcHpmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplcHpmVPVWm,       & 
& cplcHpmVWmVZ,AmpVertexIRosFuToFdcHpm)

 End if 
 End if 
AmpVertexFuToFdcHpm = AmpVertexFuToFdcHpm -  AmpVertexIRdrFuToFdcHpm! +  AmpVertexIRosFuToFdcHpm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToFdcHpm=0._dp 
AmpVertexZFuToFdcHpm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcHpm(1,gt2,:,:) = AmpWaveZFuToFdcHpm(1,gt2,:,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFdcHpm(1,gt1,:,:) 
AmpVertexZFuToFdcHpm(1,gt2,:,:)= AmpVertexZFuToFdcHpm(1,gt2,:,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFdcHpm(1,gt1,:,:) 
AmpWaveZFuToFdcHpm(2,gt2,:,:) = AmpWaveZFuToFdcHpm(2,gt2,:,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFdcHpm(2,gt1,:,:) 
AmpVertexZFuToFdcHpm(2,gt2,:,:)= AmpVertexZFuToFdcHpm(2,gt2,:,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFdcHpm(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFdcHpm=AmpWaveZFuToFdcHpm 
AmpVertexFuToFdcHpm= AmpVertexZFuToFdcHpm
! Final State 1 
AmpWaveZFuToFdcHpm=0._dp 
AmpVertexZFuToFdcHpm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcHpm(1,:,gt2,:) = AmpWaveZFuToFdcHpm(1,:,gt2,:)+ZRUZDL(gt2,gt1)*AmpWaveFuToFdcHpm(1,:,gt1,:) 
AmpVertexZFuToFdcHpm(1,:,gt2,:)= AmpVertexZFuToFdcHpm(1,:,gt2,:)+ZRUZDL(gt2,gt1)*AmpVertexFuToFdcHpm(1,:,gt1,:) 
AmpWaveZFuToFdcHpm(2,:,gt2,:) = AmpWaveZFuToFdcHpm(2,:,gt2,:)+ZRUZDRc(gt2,gt1)*AmpWaveFuToFdcHpm(2,:,gt1,:) 
AmpVertexZFuToFdcHpm(2,:,gt2,:)= AmpVertexZFuToFdcHpm(2,:,gt2,:)+ZRUZDRc(gt2,gt1)*AmpVertexFuToFdcHpm(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFdcHpm=AmpWaveZFuToFdcHpm 
AmpVertexFuToFdcHpm= AmpVertexZFuToFdcHpm
! Final State 2 
AmpWaveZFuToFdcHpm=0._dp 
AmpVertexZFuToFdcHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFuToFdcHpm(:,:,:,gt2) = AmpWaveZFuToFdcHpm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveFuToFdcHpm(:,:,:,gt1) 
AmpVertexZFuToFdcHpm(:,:,:,gt2)= AmpVertexZFuToFdcHpm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexFuToFdcHpm(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFuToFdcHpm=AmpWaveZFuToFdcHpm 
AmpVertexFuToFdcHpm= AmpVertexZFuToFdcHpm
End if
If (ShiftIRdiv) Then 
AmpVertexFuToFdcHpm = AmpVertexFuToFdcHpm  +  AmpVertexIRosFuToFdcHpm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Fd conj[Hpm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToFdcHpm = AmpTreeFuToFdcHpm 
 AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm + 2._dp*AmpWaveFuToFdcHpm + 2._dp*AmpVertexFuToFdcHpm  
Else 
 AmpSumFuToFdcHpm = AmpTreeFuToFdcHpm + AmpWaveFuToFdcHpm + AmpVertexFuToFdcHpm
 AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm + AmpWaveFuToFdcHpm + AmpVertexFuToFdcHpm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToFdcHpm = AmpTreeFuToFdcHpm
 AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MHpmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MFd(gt2))+Abs(MHpm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHpm(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToFdcHpm(gt1, gt2, gt3) 
  AmpSum2FuToFdcHpm = 2._dp*AmpWaveFuToFdcHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHpm(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToFdcHpm(gt1, gt2, gt3) 
  AmpSum2FuToFdcHpm = 2._dp*AmpVertexFuToFdcHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHpm(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToFdcHpm(gt1, gt2, gt3) 
  AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm + 2._dp*AmpWaveFuToFdcHpm + 2._dp*AmpVertexFuToFdcHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHpm(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToFdcHpm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
  AmpSqTreeFuToFdcHpm(gt1, gt2, gt3) = AmpSqFuToFdcHpm(gt1, gt2, gt3)  
  AmpSum2FuToFdcHpm = + 2._dp*AmpWaveFuToFdcHpm + 2._dp*AmpVertexFuToFdcHpm
  Call SquareAmp_FtoFS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
  AmpSqFuToFdcHpm(gt1, gt2, gt3) = AmpSqFuToFdcHpm(gt1, gt2, gt3) + AmpSqTreeFuToFdcHpm(gt1, gt2, gt3)  
Else  
  AmpSum2FuToFdcHpm = AmpTreeFuToFdcHpm
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHpm(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
  AmpSqTreeFuToFdcHpm(gt1, gt2, gt3) = AmpSqFuToFdcHpm(gt1, gt2, gt3)  
  AmpSum2FuToFdcHpm = + 2._dp*AmpWaveFuToFdcHpm + 2._dp*AmpVertexFuToFdcHpm
  Call SquareAmp_FtoFS(MFu(gt1),MFd(gt2),MHpm(gt3),AmpSumFuToFdcHpm(:,gt1, gt2, gt3),AmpSum2FuToFdcHpm(:,gt1, gt2, gt3),AmpSqFuToFdcHpm(gt1, gt2, gt3)) 
  AmpSqFuToFdcHpm(gt1, gt2, gt3) = AmpSqFuToFdcHpm(gt1, gt2, gt3) + AmpSqTreeFuToFdcHpm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuToFdcHpm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToFdcHpm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MFdOS(gt2),MHpmOS(gt3),helfactor*AmpSqFuToFdcHpm(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MFd(gt2),MHpm(gt3),helfactor*AmpSqFuToFdcHpm(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuToFdcHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdcHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToFdcHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToFdcHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToFdcHpm(gt1, gt2, gt3) + MRGFuToFdcHpm(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToFdcHpm(gt1, gt2, gt3) + MRGFuToFdcHpm(gt1, gt2, gt3))
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
Call Amplitude_Tree_NMSSM_FuToFdcVWm(cplcFuFdcVWmL,cplcFuFdcVWmR,MFd,MFu,             & 
& MVWm,MFd2,MFu2,MVWm2,AmpTreeFuToFdcVWm)

  Else 
Call Amplitude_Tree_NMSSM_FuToFdcVWm(ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,MFd,               & 
& MFu,MVWm,MFd2,MFu2,MVWm2,AmpTreeFuToFdcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToFdcVWm(MLambda,em,gs,cplcFuFdcVWmL,cplcFuFdcVWmR,           & 
& MFdOS,MFuOS,MVWmOS,MRPFuToFdcVWm,MRGFuToFdcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToFdcVWm(MLambda,em,gs,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,         & 
& MFdOS,MFuOS,MVWmOS,MRPFuToFdcVWm,MRGFuToFdcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToFdcVWm(MLambda,em,gs,cplcFuFdcVWmL,cplcFuFdcVWmR,           & 
& MFd,MFu,MVWm,MRPFuToFdcVWm,MRGFuToFdcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToFdcVWm(MLambda,em,gs,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,         & 
& MFd,MFu,MVWm,MRPFuToFdcVWm,MRGFuToFdcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFdcVWm(cplcFuFdcVWmL,cplcFuFdcVWmR,ctcplcFuFdcVWmL,     & 
& ctcplcFuFdcVWmR,MFd,MFd2,MFu,MFu2,MVWm,MVWm2,ZfFDL,ZfFDR,ZfFUL,ZfFUR,ZfVWm,            & 
& AmpWaveFuToFdcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,     & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,          & 
& cplHpmcVWmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcSucVWm,cplcVWmVPVWm,cplcVWmVWmVZ,       & 
& AmpVertexFuToFdcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,     & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,          & 
& cplHpmcVWmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcSucVWm,cplcVWmVPVWm,cplcVWmVWmVZ,       & 
& AmpVertexIRdrFuToFdcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,       & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,GosZcplcFuFdcHpmL,     & 
& GosZcplcFuFdcHpmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcVWm,cplhhcVWmVWm,GosZcplHpmcVWmVP,cplHpmcVWmVZ,     & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcSucVWm,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,GZcplcFuFdcHpmL,GZcplcFuFdcHpmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcVWm,cplhhcVWmVWm,           & 
& GZcplHpmcVWmVP,cplHpmcVWmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcSucVWm,cplcVWmVPVWm,     & 
& cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,       & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,GcplcFuFdcHpmL,        & 
& GcplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,        & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplhhHpmcVWm,cplhhcVWmVWm,GcplHpmcVWmVP,cplHpmcVWmVZ,cplcChacFuSdL,       & 
& cplcChacFuSdR,cplSdcSucVWm,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRosFuToFdcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,        & 
& cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,     & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,          & 
& cplHpmcVWmVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcSucVWm,cplcVWmVPVWm,cplcVWmVWmVZ,       & 
& AmpVertexIRosFuToFdcVWm)

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
AmpWaveZFuToFdcVWm(1,gt2,:) = AmpWaveZFuToFdcVWm(1,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFdcVWm(1,gt1,:) 
AmpVertexZFuToFdcVWm(1,gt2,:)= AmpVertexZFuToFdcVWm(1,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFdcVWm(1,gt1,:) 
AmpWaveZFuToFdcVWm(2,gt2,:) = AmpWaveZFuToFdcVWm(2,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFdcVWm(2,gt1,:) 
AmpVertexZFuToFdcVWm(2,gt2,:)= AmpVertexZFuToFdcVWm(2,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFdcVWm(2,gt1,:) 
AmpWaveZFuToFdcVWm(3,gt2,:) = AmpWaveZFuToFdcVWm(3,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFdcVWm(3,gt1,:) 
AmpVertexZFuToFdcVWm(3,gt2,:)= AmpVertexZFuToFdcVWm(3,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFdcVWm(3,gt1,:) 
AmpWaveZFuToFdcVWm(4,gt2,:) = AmpWaveZFuToFdcVWm(4,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFdcVWm(4,gt1,:) 
AmpVertexZFuToFdcVWm(4,gt2,:)= AmpVertexZFuToFdcVWm(4,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFdcVWm(4,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFdcVWm=AmpWaveZFuToFdcVWm 
AmpVertexFuToFdcVWm= AmpVertexZFuToFdcVWm
! Final State 1 
AmpWaveZFuToFdcVWm=0._dp 
AmpVertexZFuToFdcVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFdcVWm(1,:,gt2) = AmpWaveZFuToFdcVWm(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFuToFdcVWm(1,:,gt1) 
AmpVertexZFuToFdcVWm(1,:,gt2)= AmpVertexZFuToFdcVWm(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFuToFdcVWm(1,:,gt1) 
AmpWaveZFuToFdcVWm(2,:,gt2) = AmpWaveZFuToFdcVWm(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFuToFdcVWm(2,:,gt1) 
AmpVertexZFuToFdcVWm(2,:,gt2)= AmpVertexZFuToFdcVWm(2,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFuToFdcVWm(2,:,gt1) 
AmpWaveZFuToFdcVWm(3,:,gt2) = AmpWaveZFuToFdcVWm(3,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveFuToFdcVWm(3,:,gt1) 
AmpVertexZFuToFdcVWm(3,:,gt2)= AmpVertexZFuToFdcVWm(3,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexFuToFdcVWm(3,:,gt1) 
AmpWaveZFuToFdcVWm(4,:,gt2) = AmpWaveZFuToFdcVWm(4,:,gt2)+ZRUZDRc(gt2,gt1)*AmpWaveFuToFdcVWm(4,:,gt1) 
AmpVertexZFuToFdcVWm(4,:,gt2)= AmpVertexZFuToFdcVWm(4,:,gt2)+ZRUZDRc(gt2,gt1)*AmpVertexFuToFdcVWm(4,:,gt1) 
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
Call Amplitude_Tree_NMSSM_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,MFu,Mhh,MFu2,              & 
& Mhh2,AmpTreeFuToFuhh)

  Else 
Call Amplitude_Tree_NMSSM_FuToFuhh(ZcplcFuFuhhL,ZcplcFuFuhhR,MFu,Mhh,MFu2,            & 
& Mhh2,AmpTreeFuToFuhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,MFuOS,           & 
& MhhOS,MRPFuToFuhh,MRGFuToFuhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToFuhh(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,               & 
& MFuOS,MhhOS,MRPFuToFuhh,MRGFuToFuhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,MFu,             & 
& Mhh,MRPFuToFuhh,MRGFuToFuhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToFuhh(MLambda,em,gs,ZcplcFuFuhhL,ZcplcFuFuhhR,               & 
& MFu,Mhh,MRPFuToFuhh,MRGFuToFuhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,             & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,ZfFUL,ZfFUR,Zfhh,AmpWaveFuToFuhh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,       & 
& cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,              & 
& cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplcChacFuSdL,cplcChacFuSdR,            & 
& AmpVertexFuToFuhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,            & 
& cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,          & 
& cplChiChihhR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,            & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,             & 
& cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplcChacFuSdL,               & 
& cplcChacFuSdR,AmpVertexIRdrFuToFuhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuhh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,         & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,ZcplcFuFuhhL,ZcplcFuFuhhR,       & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosFuToFuhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,            & 
& cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,          & 
& cplChiChihhR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,      & 
& cplGluFucSuR,ZcplcFuFuhhL,ZcplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,             & 
& cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplcChacFuSdL,               & 
& cplcChacFuSdR,AmpVertexIRosFuToFuhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuhh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,         & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,   & 
& cplhhVZVZ,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosFuToFuhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,            & 
& cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,          & 
& cplChiChihhR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,            & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,             & 
& cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplcChacFuSdL,               & 
& cplcChacFuSdR,AmpVertexIRosFuToFuhh)

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
AmpWaveZFuToFuhh(1,gt2,:,:) = AmpWaveZFuToFuhh(1,gt2,:,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToFuhh(1,gt1,:,:) 
AmpVertexZFuToFuhh(1,gt2,:,:)= AmpVertexZFuToFuhh(1,gt2,:,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToFuhh(1,gt1,:,:) 
AmpWaveZFuToFuhh(2,gt2,:,:) = AmpWaveZFuToFuhh(2,gt2,:,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToFuhh(2,gt1,:,:) 
AmpVertexZFuToFuhh(2,gt2,:,:)= AmpVertexZFuToFuhh(2,gt2,:,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToFuhh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuToFuhh=AmpWaveZFuToFuhh 
AmpVertexFuToFuhh= AmpVertexZFuToFuhh
! Final State 1 
AmpWaveZFuToFuhh=0._dp 
AmpVertexZFuToFuhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToFuhh(1,:,gt2,:) = AmpWaveZFuToFuhh(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpWaveFuToFuhh(1,:,gt1,:) 
AmpVertexZFuToFuhh(1,:,gt2,:)= AmpVertexZFuToFuhh(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpVertexFuToFuhh(1,:,gt1,:) 
AmpWaveZFuToFuhh(2,:,gt2,:) = AmpWaveZFuToFuhh(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpWaveFuToFuhh(2,:,gt1,:) 
AmpVertexZFuToFuhh(2,:,gt2,:)= AmpVertexZFuToFuhh(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpVertexFuToFuhh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuToFuhh=AmpWaveZFuToFuhh 
AmpVertexFuToFuhh= AmpVertexZFuToFuhh
! Final State 2 
AmpWaveZFuToFuhh=0._dp 
AmpVertexZFuToFuhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
    Do gt3=1,3
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
Call Amplitude_Tree_NMSSM_FuToFuVZ(cplcFuFuVZL,cplcFuFuVZR,MFu,MVZ,MFu2,              & 
& MVZ2,AmpTreeFuToFuVZ)

  Else 
Call Amplitude_Tree_NMSSM_FuToFuVZ(ZcplcFuFuVZL,ZcplcFuFuVZR,MFu,MVZ,MFu2,            & 
& MVZ2,AmpTreeFuToFuVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,MFuOS,           & 
& MVZOS,MRPFuToFuVZ,MRGFuToFuVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToFuVZ(MLambda,em,gs,ZcplcFuFuVZL,ZcplcFuFuVZR,               & 
& MFuOS,MVZOS,MRPFuToFuVZ,MRGFuToFuVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,MFu,             & 
& MVZ,MRPFuToFuVZ,MRGFuToFuVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToFuVZ(MLambda,em,gs,ZcplcFuFuVZL,ZcplcFuFuVZR,               & 
& MFu,MVZ,MRPFuToFuVZ,MRGFuToFuVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFuVZ(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,MVZ,MVZ2,ZfFUL,ZfFUR,ZfVPVZ,ZfVZ,AmpWaveFuToFuVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplChaFucSdL,              & 
& cplChaFucSdR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,       & 
& cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,          & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,            & 
& cplcFuGluSuR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexFuToFuVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplChaFucSdL,         & 
& cplChaFucSdR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,       & 
& cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,          & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,            & 
& cplcFuGluSuR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRdrFuToFuVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,cplcChaChaVZL,             & 
& cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,        & 
& cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,        & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhVZVZ,            & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVZ,           & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplChaFucSdL,         & 
& cplChaFucSdR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,       & 
& cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,          & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplChaFucSdL,cplChaFucSdR,cplcChaChaVZL,             & 
& cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,        & 
& cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,        & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhVZVZ,              & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVZ,           & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToFuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplChaFucSdL,         & 
& cplChaFucSdR,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,       & 
& cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHpmL,          & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,            & 
& cplcFuGluSuR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosFuToFuVZ)

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
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Glu Su
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_FuToGluSu(cplcFuGluSuL,cplcFuGluSuR,MFu,MGlu,               & 
& MSu,MFu2,MGlu2,MSu2,AmpTreeFuToGluSu)

  Else 
Call Amplitude_Tree_NMSSM_FuToGluSu(ZcplcFuGluSuL,ZcplcFuGluSuR,MFu,MGlu,             & 
& MSu,MFu2,MGlu2,MSu2,AmpTreeFuToGluSu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuToGluSu(MLambda,em,gs,cplcFuGluSuL,cplcFuGluSuR,              & 
& MFuOS,MGluOS,MSuOS,MRPFuToGluSu,MRGFuToGluSu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuToGluSu(MLambda,em,gs,ZcplcFuGluSuL,ZcplcFuGluSuR,            & 
& MFuOS,MGluOS,MSuOS,MRPFuToGluSu,MRGFuToGluSu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuToGluSu(MLambda,em,gs,cplcFuGluSuL,cplcFuGluSuR,              & 
& MFu,MGlu,MSu,MRPFuToGluSu,MRGFuToGluSu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuToGluSu(MLambda,em,gs,ZcplcFuGluSuL,ZcplcFuGluSuR,            & 
& MFu,MGlu,MSu,MRPFuToGluSu,MRGFuToGluSu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToGluSu(cplcFuGluSuL,cplcFuGluSuR,ctcplcFuGluSuL,         & 
& ctcplcFuGluSuR,MFu,MFu2,MGlu,MGlu2,MSu,MSu2,ZffG,ZfFUL,ZfFUR,ZfSu,AmpWaveFuToGluSu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToGluSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplcFdChaSuL,             & 
& cplcFdChaSuR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexFuToGluSu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuToGluSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplcFdChaSuL,        & 
& cplcFdChaSuR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexIRdrFuToGluSu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToGluSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,cplcFuChiSuL,             & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,              & 
& cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,cplhhSucSu,         & 
& cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,cplSucSuVP,cplSucSdVWm,             & 
& cplSucSuVZ,AmpVertexIRosFuToGluSu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToGluSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplcFdChaSuL,        & 
& cplcFdChaSuR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,ZcplcFuGluSuL,         & 
& ZcplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,           & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexIRosFuToGluSu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToGluSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,cplcFuChiSuL,             & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,              & 
& cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,           & 
& cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,cplSucSuVP,cplSucSdVWm,             & 
& cplSucSuVZ,AmpVertexIRosFuToGluSu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuToGluSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplcFdChaSuL,        & 
& cplcFdChaSuR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,            & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,AmpVertexIRosFuToGluSu)

 End if 
 End if 
AmpVertexFuToGluSu = AmpVertexFuToGluSu -  AmpVertexIRdrFuToGluSu! +  AmpVertexIRosFuToGluSu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuToGluSu=0._dp 
AmpVertexZFuToGluSu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuToGluSu(1,gt2,:) = AmpWaveZFuToGluSu(1,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveFuToGluSu(1,gt1,:) 
AmpVertexZFuToGluSu(1,gt2,:)= AmpVertexZFuToGluSu(1,gt2,:) + ZRUZUR(gt2,gt1)*AmpVertexFuToGluSu(1,gt1,:) 
AmpWaveZFuToGluSu(2,gt2,:) = AmpWaveZFuToGluSu(2,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveFuToGluSu(2,gt1,:) 
AmpVertexZFuToGluSu(2,gt2,:)= AmpVertexZFuToGluSu(2,gt2,:) + ZRUZULc(gt2,gt1)*AmpVertexFuToGluSu(2,gt1,:) 
 End Do 
End Do 
AmpWaveFuToGluSu=AmpWaveZFuToGluSu 
AmpVertexFuToGluSu= AmpVertexZFuToGluSu
! Final State 2 
AmpWaveZFuToGluSu=0._dp 
AmpVertexZFuToGluSu=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZFuToGluSu(:,:,gt2) = AmpWaveZFuToGluSu(:,:,gt2)+ZRUZU(gt2,gt1)*AmpWaveFuToGluSu(:,:,gt1) 
AmpVertexZFuToGluSu(:,:,gt2)= AmpVertexZFuToGluSu(:,:,gt2)+ZRUZU(gt2,gt1)*AmpVertexFuToGluSu(:,:,gt1) 
 End Do 
End Do 
AmpWaveFuToGluSu=AmpWaveZFuToGluSu 
AmpVertexFuToGluSu= AmpVertexZFuToGluSu
End if
If (ShiftIRdiv) Then 
AmpVertexFuToGluSu = AmpVertexFuToGluSu  +  AmpVertexIRosFuToGluSu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->Glu Su -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuToGluSu = AmpTreeFuToGluSu 
 AmpSum2FuToGluSu = AmpTreeFuToGluSu + 2._dp*AmpWaveFuToGluSu + 2._dp*AmpVertexFuToGluSu  
Else 
 AmpSumFuToGluSu = AmpTreeFuToGluSu + AmpWaveFuToGluSu + AmpVertexFuToGluSu
 AmpSum2FuToGluSu = AmpTreeFuToGluSu + AmpWaveFuToGluSu + AmpVertexFuToGluSu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuToGluSu = AmpTreeFuToGluSu
 AmpSum2FuToGluSu = AmpTreeFuToGluSu 
End if 
Do gt1=1,3
i4 = isave 
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MGluOS)+Abs(MSuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MGlu)+Abs(MSu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt3 
  AmpSum2FuToGluSu = AmpTreeFuToGluSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MGluOS,MSuOS(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MGlu,MSu(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuToGluSu(gt1, gt3) 
  AmpSum2FuToGluSu = 2._dp*AmpWaveFuToGluSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MGluOS,MSuOS(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MGlu,MSu(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuToGluSu(gt1, gt3) 
  AmpSum2FuToGluSu = 2._dp*AmpVertexFuToGluSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MGluOS,MSuOS(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MGlu,MSu(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuToGluSu(gt1, gt3) 
  AmpSum2FuToGluSu = AmpTreeFuToGluSu + 2._dp*AmpWaveFuToGluSu + 2._dp*AmpVertexFuToGluSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MGluOS,MSuOS(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MGlu,MSu(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuToGluSu(gt1, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuToGluSu = AmpTreeFuToGluSu
  Call SquareAmp_FtoFS(MFuOS(gt1),MGluOS,MSuOS(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
  AmpSqTreeFuToGluSu(gt1, gt3) = AmpSqFuToGluSu(gt1, gt3)  
  AmpSum2FuToGluSu = + 2._dp*AmpWaveFuToGluSu + 2._dp*AmpVertexFuToGluSu
  Call SquareAmp_FtoFS(MFuOS(gt1),MGluOS,MSuOS(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
  AmpSqFuToGluSu(gt1, gt3) = AmpSqFuToGluSu(gt1, gt3) + AmpSqTreeFuToGluSu(gt1, gt3)  
Else  
  AmpSum2FuToGluSu = AmpTreeFuToGluSu
  Call SquareAmp_FtoFS(MFu(gt1),MGlu,MSu(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
  AmpSqTreeFuToGluSu(gt1, gt3) = AmpSqFuToGluSu(gt1, gt3)  
  AmpSum2FuToGluSu = + 2._dp*AmpWaveFuToGluSu + 2._dp*AmpVertexFuToGluSu
  Call SquareAmp_FtoFS(MFu(gt1),MGlu,MSu(gt3),AmpSumFuToGluSu(:,gt1, gt3),AmpSum2FuToGluSu(:,gt1, gt3),AmpSqFuToGluSu(gt1, gt3)) 
  AmpSqFuToGluSu(gt1, gt3) = AmpSqFuToGluSu(gt1, gt3) + AmpSqTreeFuToGluSu(gt1, gt3)  
End if  
Else  
  AmpSqFuToGluSu(gt1, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuToGluSu(gt1, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 4._dp/3._dp*GammaTPS(MFuOS(gt1),MGluOS,MSuOS(gt3),helfactor*AmpSqFuToGluSu(gt1, gt3))
Else 
  gP1LFu(gt1,i4) = 4._dp/3._dp*GammaTPS(MFu(gt1),MGlu,MSu(gt3),helfactor*AmpSqFuToGluSu(gt1, gt3))
End if 
If ((Abs(MRPFuToGluSu(gt1, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToGluSu(gt1, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuToGluSu(gt1, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuToGluSu(gt1, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuToGluSu(gt1, gt3) + MRGFuToGluSu(gt1, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuToGluSu(gt1, gt3) + MRGFuToGluSu(gt1, gt3))
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
! bar(Cha) Sd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_FuTocChaSd(cplcChacFuSdL,cplcChacFuSdR,MCha,MFu,            & 
& MSd,MCha2,MFu2,MSd2,AmpTreeFuTocChaSd)

  Else 
Call Amplitude_Tree_NMSSM_FuTocChaSd(ZcplcChacFuSdL,ZcplcChacFuSdR,MCha,              & 
& MFu,MSd,MCha2,MFu2,MSd2,AmpTreeFuTocChaSd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_FuTocChaSd(MLambda,em,gs,cplcChacFuSdL,cplcChacFuSdR,           & 
& MChaOS,MFuOS,MSdOS,MRPFuTocChaSd,MRGFuTocChaSd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_FuTocChaSd(MLambda,em,gs,ZcplcChacFuSdL,ZcplcChacFuSdR,         & 
& MChaOS,MFuOS,MSdOS,MRPFuTocChaSd,MRGFuTocChaSd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_FuTocChaSd(MLambda,em,gs,cplcChacFuSdL,cplcChacFuSdR,           & 
& MCha,MFu,MSd,MRPFuTocChaSd,MRGFuTocChaSd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_FuTocChaSd(MLambda,em,gs,ZcplcChacFuSdL,ZcplcChacFuSdR,         & 
& MCha,MFu,MSd,MRPFuTocChaSd,MRGFuTocChaSd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuTocChaSd(cplcChacFuSdL,cplcChacFuSdR,ctcplcChacFuSdL,     & 
& ctcplcChacFuSdR,MCha,MCha2,MFu,MFu2,MSd,MSd2,ZfFUL,ZfFUR,ZfLm,ZfLp,ZfSd,               & 
& AmpWaveFuTocChaSd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuTocChaSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,         & 
& cplAhSdcSd,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,    & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,  & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,              & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplSdcSdVG,cplSdcSdVP,               & 
& cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,AmpVertexFuTocChaSd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_FuTocChaSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhSdcSd,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,    & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,  & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,              & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplSdcSdVG,cplSdcSdVP,               & 
& cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,AmpVertexIRdrFuTocChaSd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuTocChaSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,cplcChaChahhL,          & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,  & 
& cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,     & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,  & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,            & 
& cplcFuGluSuR,cplhhSdcSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,ZcplcChacFuSdL,               & 
& ZcplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,AmpVertexIRosFuTocChaSd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuTocChaSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhSdcSd,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,    & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,  & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,              & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplSdcSdVG,cplSdcSdVP,               & 
& cplSdcSdVZ,ZcplcChacFuSdL,ZcplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,AmpVertexIRosFuTocChaSd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuTocChaSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,cplcChaChahhL,          & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,  & 
& cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,     & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,  & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,            & 
& cplcFuGluSuR,cplhhSdcSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,  & 
& cplSdcHpmcSu,cplSdcSucVWm,AmpVertexIRosFuTocChaSd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_FuTocChaSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhSdcSd,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,    & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,  & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,              & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplSdcSdVG,cplSdcSdVP,               & 
& cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,AmpVertexIRosFuTocChaSd)

 End if 
 End if 
AmpVertexFuTocChaSd = AmpVertexFuTocChaSd -  AmpVertexIRdrFuTocChaSd! +  AmpVertexIRosFuTocChaSd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZFuTocChaSd=0._dp 
AmpVertexZFuTocChaSd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZFuTocChaSd(1,gt2,:,:) = AmpWaveZFuTocChaSd(1,gt2,:,:)+ZRUZUR(gt2,gt1)*AmpWaveFuTocChaSd(1,gt1,:,:) 
AmpVertexZFuTocChaSd(1,gt2,:,:)= AmpVertexZFuTocChaSd(1,gt2,:,:) + ZRUZUR(gt2,gt1)*AmpVertexFuTocChaSd(1,gt1,:,:) 
AmpWaveZFuTocChaSd(2,gt2,:,:) = AmpWaveZFuTocChaSd(2,gt2,:,:)+ZRUZULc(gt2,gt1)*AmpWaveFuTocChaSd(2,gt1,:,:) 
AmpVertexZFuTocChaSd(2,gt2,:,:)= AmpVertexZFuTocChaSd(2,gt2,:,:) + ZRUZULc(gt2,gt1)*AmpVertexFuTocChaSd(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveFuTocChaSd=AmpWaveZFuTocChaSd 
AmpVertexFuTocChaSd= AmpVertexZFuTocChaSd
! Final State 1 
AmpWaveZFuTocChaSd=0._dp 
AmpVertexZFuTocChaSd=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZFuTocChaSd(1,:,gt2,:) = AmpWaveZFuTocChaSd(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpWaveFuTocChaSd(1,:,gt1,:) 
AmpVertexZFuTocChaSd(1,:,gt2,:)= AmpVertexZFuTocChaSd(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpVertexFuTocChaSd(1,:,gt1,:) 
AmpWaveZFuTocChaSd(2,:,gt2,:) = AmpWaveZFuTocChaSd(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpWaveFuTocChaSd(2,:,gt1,:) 
AmpVertexZFuTocChaSd(2,:,gt2,:)= AmpVertexZFuTocChaSd(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpVertexFuTocChaSd(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveFuTocChaSd=AmpWaveZFuTocChaSd 
AmpVertexFuTocChaSd= AmpVertexZFuTocChaSd
! Final State 2 
AmpWaveZFuTocChaSd=0._dp 
AmpVertexZFuTocChaSd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZFuTocChaSd(:,:,:,gt2) = AmpWaveZFuTocChaSd(:,:,:,gt2)+ZRUZD(gt2,gt1)*AmpWaveFuTocChaSd(:,:,:,gt1) 
AmpVertexZFuTocChaSd(:,:,:,gt2)= AmpVertexZFuTocChaSd(:,:,:,gt2)+ZRUZD(gt2,gt1)*AmpVertexFuTocChaSd(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveFuTocChaSd=AmpWaveZFuTocChaSd 
AmpVertexFuTocChaSd= AmpVertexZFuTocChaSd
End if
If (ShiftIRdiv) Then 
AmpVertexFuTocChaSd = AmpVertexFuTocChaSd  +  AmpVertexIRosFuTocChaSd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Fu->bar[Cha] Sd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumFuTocChaSd = AmpTreeFuTocChaSd 
 AmpSum2FuTocChaSd = AmpTreeFuTocChaSd + 2._dp*AmpWaveFuTocChaSd + 2._dp*AmpVertexFuTocChaSd  
Else 
 AmpSumFuTocChaSd = AmpTreeFuTocChaSd + AmpWaveFuTocChaSd + AmpVertexFuTocChaSd
 AmpSum2FuTocChaSd = AmpTreeFuTocChaSd + AmpWaveFuTocChaSd + AmpVertexFuTocChaSd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumFuTocChaSd = AmpTreeFuTocChaSd
 AmpSum2FuTocChaSd = AmpTreeFuTocChaSd 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,2
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MFuOS(gt1)).gt.(Abs(MChaOS(gt2))+Abs(MSdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MFu(gt1)).gt.(Abs(MCha(gt2))+Abs(MSd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2FuTocChaSd = AmpTreeFuTocChaSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MCha(gt2),MSd(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqFuTocChaSd(gt1, gt2, gt3) 
  AmpSum2FuTocChaSd = 2._dp*AmpWaveFuTocChaSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MCha(gt2),MSd(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqFuTocChaSd(gt1, gt2, gt3) 
  AmpSum2FuTocChaSd = 2._dp*AmpVertexFuTocChaSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MCha(gt2),MSd(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqFuTocChaSd(gt1, gt2, gt3) 
  AmpSum2FuTocChaSd = AmpTreeFuTocChaSd + 2._dp*AmpWaveFuTocChaSd + 2._dp*AmpVertexFuTocChaSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MFu(gt1),MCha(gt2),MSd(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqFuTocChaSd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2FuTocChaSd = AmpTreeFuTocChaSd
  Call SquareAmp_FtoFS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
  AmpSqTreeFuTocChaSd(gt1, gt2, gt3) = AmpSqFuTocChaSd(gt1, gt2, gt3)  
  AmpSum2FuTocChaSd = + 2._dp*AmpWaveFuTocChaSd + 2._dp*AmpVertexFuTocChaSd
  Call SquareAmp_FtoFS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
  AmpSqFuTocChaSd(gt1, gt2, gt3) = AmpSqFuTocChaSd(gt1, gt2, gt3) + AmpSqTreeFuTocChaSd(gt1, gt2, gt3)  
Else  
  AmpSum2FuTocChaSd = AmpTreeFuTocChaSd
  Call SquareAmp_FtoFS(MFu(gt1),MCha(gt2),MSd(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
  AmpSqTreeFuTocChaSd(gt1, gt2, gt3) = AmpSqFuTocChaSd(gt1, gt2, gt3)  
  AmpSum2FuTocChaSd = + 2._dp*AmpWaveFuTocChaSd + 2._dp*AmpVertexFuTocChaSd
  Call SquareAmp_FtoFS(MFu(gt1),MCha(gt2),MSd(gt3),AmpSumFuTocChaSd(:,gt1, gt2, gt3),AmpSum2FuTocChaSd(:,gt1, gt2, gt3),AmpSqFuTocChaSd(gt1, gt2, gt3)) 
  AmpSqFuTocChaSd(gt1, gt2, gt3) = AmpSqFuTocChaSd(gt1, gt2, gt3) + AmpSqTreeFuTocChaSd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqFuTocChaSd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqFuTocChaSd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LFu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFuOS(gt1),MChaOS(gt2),MSdOS(gt3),helfactor*AmpSqFuTocChaSd(gt1, gt2, gt3))
Else 
  gP1LFu(gt1,i4) = 1._dp*GammaTPS(MFu(gt1),MCha(gt2),MSd(gt3),helfactor*AmpSqFuTocChaSd(gt1, gt2, gt3))
End if 
If ((Abs(MRPFuTocChaSd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuTocChaSd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LFu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPFuTocChaSd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGFuTocChaSd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPFuTocChaSd(gt1, gt2, gt3) + MRGFuTocChaSd(gt1, gt2, gt3)) 
  gP1LFu(gt1,i4) = gP1LFu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPFuTocChaSd(gt1, gt2, gt3) + MRGFuTocChaSd(gt1, gt2, gt3))
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
!---------------- 
! Fu VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_FuToFuVG(ZcplcFuFuVGL,ZcplcFuFuVGR,ctcplcFuFuVGL,           & 
& ctcplcFuFuVGR,MFuOS,MFu2OS,MVG,MVG2,ZfFUL,ZfFUR,ZfVG,AmpWaveFuToFuVG)

 Else 
Call Amplitude_WAVE_NMSSM_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,             & 
& ctcplcFuFuVGR,MFuOS,MFu2OS,MVG,MVG2,ZfFUL,ZfFUR,ZfVG,AmpWaveFuToFuVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_FuToFuVG(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,ZcplcFuFuAhL,     & 
& ZcplcFuFuAhR,ZcplChaFucSdL,ZcplChaFucSdR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplcFuChiSuL,    & 
& ZcplcFuChiSuR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFuFdcHpmL,ZcplcFuFdcHpmR,ZcplcFuFdcVWmL,  & 
& ZcplcFuFdcVWmR,ZcplGluFucSuL,ZcplGluFucSuR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFuHpmL,    & 
& ZcplcFdFuHpmR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFuVWmL,       & 
& ZcplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplGluGluVGL,ZcplGluGluVGR,ZcplcFuGluSuL,     & 
& ZcplcFuGluSuR,ZcplSdcSdVG,ZcplcChacFuSdL,ZcplcChacFuSdR,ZcplSucSuVG,ZcplVGVGVG,        & 
& AmpVertexFuToFuVG)

 Else 
Call Amplitude_VERTEX_NMSSM_FuToFuVG(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,          & 
& cplcFuChiSuR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,        & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFuGluSuL,           & 
& cplcFuGluSuR,cplSdcSdVG,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVG,cplVGVGVG,              & 
& AmpVertexFuToFuVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,             & 
& ctcplcFuFuVGR,MFu,MFu2,MVG,MVG2,ZfFUL,ZfFUR,ZfVG,AmpWaveFuToFuVG)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFuVG(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplChaFucSdL,cplChaFucSdR,           & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVGL,cplcFdFdVGR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplGluGluVGL,cplGluGluVGR,cplcFuGluSuL,cplcFuGluSuR,cplSdcSdVG,cplcChacFuSdL,          & 
& cplcChacFuSdR,cplSucSuVG,cplVGVGVG,AmpVertexFuToFuVG)

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
Call Amplitude_WAVE_NMSSM_FuToFuVP(ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFuFuVZL,            & 
& ZcplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFuOS,            & 
& MFu2OS,MVP,MVP2,ZfFUL,ZfFUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)

 Else 
Call Amplitude_WAVE_NMSSM_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFuOS,             & 
& MFu2OS,MVP,MVP2,ZfFUL,ZfFUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_FuToFuVP(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,ZcplcFuFuAhL,     & 
& ZcplcFuFuAhR,ZcplChaFucSdL,ZcplChaFucSdR,ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplChiFucSuL,  & 
& ZcplChiFucSuR,ZcplcFuChiSuL,ZcplcFuChiSuR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFuFdcHpmL,    & 
& ZcplcFuFdcHpmR,ZcplcFuFdcVWmL,ZcplcFuFdcVWmR,ZcplGluFucSuL,ZcplGluFucSuR,              & 
& ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdFuHpmL,ZcplcFdFuHpmR,ZcplcFuFuVGL,ZcplcFuFuVGR,       & 
& ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdFuVWmL,ZcplcFdFuVWmR,ZcplcFuFuVZL,ZcplcFuFuVZR,       & 
& ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplHpmcHpmVP,ZcplHpmcVWmVP,ZcplSdcSdVP,ZcplcChacFuSdL,    & 
& ZcplcChacFuSdR,ZcplSucSuVP,ZcplcHpmVPVWm,ZcplcVWmVPVWm,AmpVertexFuToFuVP)

 Else 
Call Amplitude_VERTEX_NMSSM_FuToFuVP(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplChaFucSdL,cplChaFucSdR,cplcChaChaVPL,cplcChaChaVPR,cplChiFucSuL,        & 
& cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHpmL,          & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,            & 
& cplcFuGluSuR,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplcChacFuSdL,cplcChacFuSdR,         & 
& cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,AmpVertexFuToFuVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,ZfFUL,ZfFUR,ZfVP,ZfVZVP,AmpWaveFuToFuVP)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_FuToFuVP(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplChaFucSdL,cplChaFucSdR,           & 
& cplcChaChaVPL,cplcChaChaVPR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,       & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplHpmcHpmVP,cplHpmcVWmVP,           & 
& cplSdcSdVP,cplcChacFuSdL,cplcChacFuSdR,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,           & 
& AmpVertexFuToFuVP)

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

End Module Wrapper_OneLoopDecay_Fu_NMSSM
