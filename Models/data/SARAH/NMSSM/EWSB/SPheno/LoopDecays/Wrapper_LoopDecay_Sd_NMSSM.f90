! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:26 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Sd_NMSSM
Use Model_Data_NMSSM 
Use Kinematics 
Use OneLoopDecay_Sd_NMSSM 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Sd(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,              & 
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
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhAhSdcSdaa,cplAhcHpmVWm,cplAhhhhh,               & 
& cplAhhhSdcSdaa,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,   & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplcChaChaAhL,            & 
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
& cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhhhSdcSdaa,cplhhHpmcHpm,          & 
& cplhhHpmcVWm,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplhhSdcSd,cplhhSecSe,cplhhSucSu,        & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,              & 
& cplSdcSdcVWmVWmaa,cplSdcSdVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVP,cplSdcSdVPVPaa,           & 
& cplSdcSdVPVZaa,cplSdcSdVZ,cplSdcSdVZVZaa,cplSdcSucVWm,cplSdcSucVWmVGLamct4ct2ct1,      & 
& cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,cplSdSdcSdcSdabab,cplSdSdcSdcSdabba,cplSdSecSdcSeaa, & 
& cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSdcSvaa,cplSeSucSdcSvaa,cplSucSdVGVWmLamct3ct2ct1,& 
& cplSucSdVPVWmaa,cplSucSdVWm,cplSucSdVWmVZaa,cplSucSucVWmVWmaa,cplSucSuVG,              & 
& cplSucSuVP,cplSucSuVZ,cplVGVGVG,ctcplAhSdcSd,ctcplChaFucSdL,ctcplChaFucSdR,            & 
& ctcplChiFdcSdL,ctcplChiFdcSdR,ctcplGluFdcSdL,ctcplGluFdcSdR,ctcplhhSdcSd,              & 
& ctcplHpmSucSd,ctcplSdcSdVG,ctcplSdcSdVP,ctcplSdcSdVZ,ctcplSucSdVWm,GcplcHpmVPVWm,      & 
& GcplHpmcVWmVP,GcplHpmSucSd,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,GosZcplHpmSucSd,          & 
& GZcplcHpmVPVWm,GZcplHpmcVWmVP,GZcplHpmSucSd,ZcplAhSdcSd,ZcplChaFucSdL,ZcplChaFucSdR,   & 
& ZcplChiFdcSdL,ZcplChiFdcSdR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplhhSdcSd,ZcplHpmSucSd,      & 
& ZcplSdcSdVZ,ZcplSucSdVWm,ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,              & 
& ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,            & 
& kont,gP1LSd)

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

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhAhSdcSdaa(3,3,6,6),cplAhcHpmVWm(3,2),          & 
& cplAhhhhh(3,3,3),cplAhhhSdcSdaa(3,3,6,6),cplAhhhVZ(3,3),cplAhHpmcHpm(3,2,2),           & 
& cplAhHpmcVWm(3,2),cplAhHpmSucSdaa(3,2,6,6),cplAhSdcHpmcSuaa(3,6,2,6),cplAhSdcSd(3,6,6),& 
& cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),         & 
& cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),   & 
& cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),           & 
& cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),   & 
& cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),     & 
& cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),         & 
& cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),               & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),& 
& cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),             & 
& cplcFdGluSdR(3,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplcFuFdcHpmL(3,3,2),        & 
& cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,3),         & 
& cplcFuFuAhR(3,3,3),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),           & 
& cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),   & 
& cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),       & 
& cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),           & 
& cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),               & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),       & 
& cplGluFucSuR(3,6),cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm(3,2),cplhhcVWmVWm(3),         & 
& cplhhhhhh(3,3,3),cplhhhhSdcSdaa(3,3,6,6),cplhhHpmcHpm(3,2,2),cplhhHpmcVWm(3,2),        & 
& cplhhHpmSucSdaa(3,2,6,6),cplhhSdcHpmcSuaa(3,6,2,6),cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),& 
& cplhhSucSu(3,6,6),cplhhSvcSv(3,3,3),cplhhVZVZ(3),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),  & 
& cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplHpmSdcHpmcSdaa(2,6,2,6),cplHpmSucHpmcSuaa(2,6,2,6), & 
& cplHpmSucSd(2,6,6),cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSdcSdcVWmVWmaa(6,6),      & 
& cplSdcSdVG(6,6),cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1(6,6),cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1(6,6),& 
& cplSdcSdVGVPLamct3ct2ct1(6,6),cplSdcSdVGVZLamct3ct2ct1(6,6),cplSdcSdVP(6,6),           & 
& cplSdcSdVPVPaa(6,6),cplSdcSdVPVZaa(6,6),cplSdcSdVZ(6,6),cplSdcSdVZVZaa(6,6),           & 
& cplSdcSucVWm(6,6),cplSdcSucVWmVGLamct4ct2ct1(6,6),cplSdcSucVWmVPaa(6,6),               & 
& cplSdcSucVWmVZaa(6,6),cplSdSdcSdcSdabab(6,6,6,6),cplSdSdcSdcSdabba(6,6,6,6),           & 
& cplSdSecSdcSeaa(6,6,6,6),cplSdSucSdcSuabab(6,6,6,6),cplSdSucSdcSuabba(6,6,6,6),        & 
& cplSdSvcSdcSvaa(6,3,6,3),cplSeSucSdcSvaa(6,6,6,3),cplSucSdVGVWmLamct3ct2ct1(6,6),      & 
& cplSucSdVPVWmaa(6,6),cplSucSdVWm(6,6),cplSucSdVWmVZaa(6,6),cplSucSucVWmVWmaa(6,6),     & 
& cplSucSuVG(6,6),cplSucSuVP(6,6),cplSucSuVZ(6,6),cplVGVGVG,ctcplAhSdcSd(3,6,6)

Complex(dp),Intent(in) :: ctcplChaFucSdL(2,3,6),ctcplChaFucSdR(2,3,6),ctcplChiFdcSdL(5,3,6),ctcplChiFdcSdR(5,3,6),& 
& ctcplGluFdcSdL(3,6),ctcplGluFdcSdR(3,6),ctcplhhSdcSd(3,6,6),ctcplHpmSucSd(2,6,6),      & 
& ctcplSdcSdVG(6,6),ctcplSdcSdVP(6,6),ctcplSdcSdVZ(6,6),ctcplSucSdVWm(6,6),              & 
& GcplcHpmVPVWm(2),GcplHpmcVWmVP(2),GcplHpmSucSd(2,6,6),GosZcplcHpmVPVWm(2),             & 
& GosZcplHpmcVWmVP(2),GosZcplHpmSucSd(2,6,6),GZcplcHpmVPVWm(2),GZcplHpmcVWmVP(2),        & 
& GZcplHpmSucSd(2,6,6),ZcplAhSdcSd(3,6,6),ZcplChaFucSdL(2,3,6),ZcplChaFucSdR(2,3,6),     & 
& ZcplChiFdcSdL(5,3,6),ZcplChiFdcSdR(5,3,6),ZcplGluFdcSdL(3,6),ZcplGluFdcSdR(3,6),       & 
& ZcplhhSdcSd(3,6,6),ZcplHpmSucSd(2,6,6),ZcplSdcSdVZ(6,6),ZcplSucSdVWm(6,6)

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
Real(dp), Intent(out) :: gP1LSd(6,84) 
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
Real(dp) :: MRPSdToSdAh(6,6,3),MRGSdToSdAh(6,6,3), MRPZSdToSdAh(6,6,3),MRGZSdToSdAh(6,6,3) 
Real(dp) :: MVPSdToSdAh(6,6,3) 
Real(dp) :: RMsqTreeSdToSdAh(6,6,3),RMsqWaveSdToSdAh(6,6,3),RMsqVertexSdToSdAh(6,6,3) 
Complex(dp) :: AmpTreeSdToSdAh(6,6,3),AmpWaveSdToSdAh(6,6,3)=(0._dp,0._dp),AmpVertexSdToSdAh(6,6,3)& 
 & ,AmpVertexIRosSdToSdAh(6,6,3),AmpVertexIRdrSdToSdAh(6,6,3), AmpSumSdToSdAh(6,6,3), AmpSum2SdToSdAh(6,6,3) 
Complex(dp) :: AmpTreeZSdToSdAh(6,6,3),AmpWaveZSdToSdAh(6,6,3),AmpVertexZSdToSdAh(6,6,3) 
Real(dp) :: AmpSqSdToSdAh(6,6,3),  AmpSqTreeSdToSdAh(6,6,3) 
Real(dp) :: MRPSdToFuCha(6,3,2),MRGSdToFuCha(6,3,2), MRPZSdToFuCha(6,3,2),MRGZSdToFuCha(6,3,2) 
Real(dp) :: MVPSdToFuCha(6,3,2) 
Real(dp) :: RMsqTreeSdToFuCha(6,3,2),RMsqWaveSdToFuCha(6,3,2),RMsqVertexSdToFuCha(6,3,2) 
Complex(dp) :: AmpTreeSdToFuCha(2,6,3,2),AmpWaveSdToFuCha(2,6,3,2)=(0._dp,0._dp),AmpVertexSdToFuCha(2,6,3,2)& 
 & ,AmpVertexIRosSdToFuCha(2,6,3,2),AmpVertexIRdrSdToFuCha(2,6,3,2), AmpSumSdToFuCha(2,6,3,2), AmpSum2SdToFuCha(2,6,3,2) 
Complex(dp) :: AmpTreeZSdToFuCha(2,6,3,2),AmpWaveZSdToFuCha(2,6,3,2),AmpVertexZSdToFuCha(2,6,3,2) 
Real(dp) :: AmpSqSdToFuCha(6,3,2),  AmpSqTreeSdToFuCha(6,3,2) 
Real(dp) :: MRPSdToFdChi(6,3,5),MRGSdToFdChi(6,3,5), MRPZSdToFdChi(6,3,5),MRGZSdToFdChi(6,3,5) 
Real(dp) :: MVPSdToFdChi(6,3,5) 
Real(dp) :: RMsqTreeSdToFdChi(6,3,5),RMsqWaveSdToFdChi(6,3,5),RMsqVertexSdToFdChi(6,3,5) 
Complex(dp) :: AmpTreeSdToFdChi(2,6,3,5),AmpWaveSdToFdChi(2,6,3,5)=(0._dp,0._dp),AmpVertexSdToFdChi(2,6,3,5)& 
 & ,AmpVertexIRosSdToFdChi(2,6,3,5),AmpVertexIRdrSdToFdChi(2,6,3,5), AmpSumSdToFdChi(2,6,3,5), AmpSum2SdToFdChi(2,6,3,5) 
Complex(dp) :: AmpTreeZSdToFdChi(2,6,3,5),AmpWaveZSdToFdChi(2,6,3,5),AmpVertexZSdToFdChi(2,6,3,5) 
Real(dp) :: AmpSqSdToFdChi(6,3,5),  AmpSqTreeSdToFdChi(6,3,5) 
Real(dp) :: MRPSdToGluFd(6,3),MRGSdToGluFd(6,3), MRPZSdToGluFd(6,3),MRGZSdToGluFd(6,3) 
Real(dp) :: MVPSdToGluFd(6,3) 
Real(dp) :: RMsqTreeSdToGluFd(6,3),RMsqWaveSdToGluFd(6,3),RMsqVertexSdToGluFd(6,3) 
Complex(dp) :: AmpTreeSdToGluFd(2,6,3),AmpWaveSdToGluFd(2,6,3)=(0._dp,0._dp),AmpVertexSdToGluFd(2,6,3)& 
 & ,AmpVertexIRosSdToGluFd(2,6,3),AmpVertexIRdrSdToGluFd(2,6,3), AmpSumSdToGluFd(2,6,3), AmpSum2SdToGluFd(2,6,3) 
Complex(dp) :: AmpTreeZSdToGluFd(2,6,3),AmpWaveZSdToGluFd(2,6,3),AmpVertexZSdToGluFd(2,6,3) 
Real(dp) :: AmpSqSdToGluFd(6,3),  AmpSqTreeSdToGluFd(6,3) 
Real(dp) :: MRPSdToSdhh(6,6,3),MRGSdToSdhh(6,6,3), MRPZSdToSdhh(6,6,3),MRGZSdToSdhh(6,6,3) 
Real(dp) :: MVPSdToSdhh(6,6,3) 
Real(dp) :: RMsqTreeSdToSdhh(6,6,3),RMsqWaveSdToSdhh(6,6,3),RMsqVertexSdToSdhh(6,6,3) 
Complex(dp) :: AmpTreeSdToSdhh(6,6,3),AmpWaveSdToSdhh(6,6,3)=(0._dp,0._dp),AmpVertexSdToSdhh(6,6,3)& 
 & ,AmpVertexIRosSdToSdhh(6,6,3),AmpVertexIRdrSdToSdhh(6,6,3), AmpSumSdToSdhh(6,6,3), AmpSum2SdToSdhh(6,6,3) 
Complex(dp) :: AmpTreeZSdToSdhh(6,6,3),AmpWaveZSdToSdhh(6,6,3),AmpVertexZSdToSdhh(6,6,3) 
Real(dp) :: AmpSqSdToSdhh(6,6,3),  AmpSqTreeSdToSdhh(6,6,3) 
Real(dp) :: MRPSdToSuHpm(6,6,2),MRGSdToSuHpm(6,6,2), MRPZSdToSuHpm(6,6,2),MRGZSdToSuHpm(6,6,2) 
Real(dp) :: MVPSdToSuHpm(6,6,2) 
Real(dp) :: RMsqTreeSdToSuHpm(6,6,2),RMsqWaveSdToSuHpm(6,6,2),RMsqVertexSdToSuHpm(6,6,2) 
Complex(dp) :: AmpTreeSdToSuHpm(6,6,2),AmpWaveSdToSuHpm(6,6,2)=(0._dp,0._dp),AmpVertexSdToSuHpm(6,6,2)& 
 & ,AmpVertexIRosSdToSuHpm(6,6,2),AmpVertexIRdrSdToSuHpm(6,6,2), AmpSumSdToSuHpm(6,6,2), AmpSum2SdToSuHpm(6,6,2) 
Complex(dp) :: AmpTreeZSdToSuHpm(6,6,2),AmpWaveZSdToSuHpm(6,6,2),AmpVertexZSdToSuHpm(6,6,2) 
Real(dp) :: AmpSqSdToSuHpm(6,6,2),  AmpSqTreeSdToSuHpm(6,6,2) 
Real(dp) :: MRPSdToSdVZ(6,6),MRGSdToSdVZ(6,6), MRPZSdToSdVZ(6,6),MRGZSdToSdVZ(6,6) 
Real(dp) :: MVPSdToSdVZ(6,6) 
Real(dp) :: RMsqTreeSdToSdVZ(6,6),RMsqWaveSdToSdVZ(6,6),RMsqVertexSdToSdVZ(6,6) 
Complex(dp) :: AmpTreeSdToSdVZ(2,6,6),AmpWaveSdToSdVZ(2,6,6)=(0._dp,0._dp),AmpVertexSdToSdVZ(2,6,6)& 
 & ,AmpVertexIRosSdToSdVZ(2,6,6),AmpVertexIRdrSdToSdVZ(2,6,6), AmpSumSdToSdVZ(2,6,6), AmpSum2SdToSdVZ(2,6,6) 
Complex(dp) :: AmpTreeZSdToSdVZ(2,6,6),AmpWaveZSdToSdVZ(2,6,6),AmpVertexZSdToSdVZ(2,6,6) 
Real(dp) :: AmpSqSdToSdVZ(6,6),  AmpSqTreeSdToSdVZ(6,6) 
Real(dp) :: MRPSdToSuVWm(6,6),MRGSdToSuVWm(6,6), MRPZSdToSuVWm(6,6),MRGZSdToSuVWm(6,6) 
Real(dp) :: MVPSdToSuVWm(6,6) 
Real(dp) :: RMsqTreeSdToSuVWm(6,6),RMsqWaveSdToSuVWm(6,6),RMsqVertexSdToSuVWm(6,6) 
Complex(dp) :: AmpTreeSdToSuVWm(2,6,6),AmpWaveSdToSuVWm(2,6,6)=(0._dp,0._dp),AmpVertexSdToSuVWm(2,6,6)& 
 & ,AmpVertexIRosSdToSuVWm(2,6,6),AmpVertexIRdrSdToSuVWm(2,6,6), AmpSumSdToSuVWm(2,6,6), AmpSum2SdToSuVWm(2,6,6) 
Complex(dp) :: AmpTreeZSdToSuVWm(2,6,6),AmpWaveZSdToSuVWm(2,6,6),AmpVertexZSdToSuVWm(2,6,6) 
Real(dp) :: AmpSqSdToSuVWm(6,6),  AmpSqTreeSdToSuVWm(6,6) 
Real(dp) :: MRPSdToSdVG(6,6),MRGSdToSdVG(6,6), MRPZSdToSdVG(6,6),MRGZSdToSdVG(6,6) 
Real(dp) :: MVPSdToSdVG(6,6) 
Real(dp) :: RMsqTreeSdToSdVG(6,6),RMsqWaveSdToSdVG(6,6),RMsqVertexSdToSdVG(6,6) 
Complex(dp) :: AmpTreeSdToSdVG(2,6,6),AmpWaveSdToSdVG(2,6,6)=(0._dp,0._dp),AmpVertexSdToSdVG(2,6,6)& 
 & ,AmpVertexIRosSdToSdVG(2,6,6),AmpVertexIRdrSdToSdVG(2,6,6), AmpSumSdToSdVG(2,6,6), AmpSum2SdToSdVG(2,6,6) 
Complex(dp) :: AmpTreeZSdToSdVG(2,6,6),AmpWaveZSdToSdVG(2,6,6),AmpVertexZSdToSdVG(2,6,6) 
Real(dp) :: AmpSqSdToSdVG(6,6),  AmpSqTreeSdToSdVG(6,6) 
Real(dp) :: MRPSdToSdVP(6,6),MRGSdToSdVP(6,6), MRPZSdToSdVP(6,6),MRGZSdToSdVP(6,6) 
Real(dp) :: MVPSdToSdVP(6,6) 
Real(dp) :: RMsqTreeSdToSdVP(6,6),RMsqWaveSdToSdVP(6,6),RMsqVertexSdToSdVP(6,6) 
Complex(dp) :: AmpTreeSdToSdVP(2,6,6),AmpWaveSdToSdVP(2,6,6)=(0._dp,0._dp),AmpVertexSdToSdVP(2,6,6)& 
 & ,AmpVertexIRosSdToSdVP(2,6,6),AmpVertexIRdrSdToSdVP(2,6,6), AmpSumSdToSdVP(2,6,6), AmpSum2SdToSdVP(2,6,6) 
Complex(dp) :: AmpTreeZSdToSdVP(2,6,6),AmpWaveZSdToSdVP(2,6,6),AmpVertexZSdToSdVP(2,6,6) 
Real(dp) :: AmpSqSdToSdVP(6,6),  AmpSqTreeSdToSdVP(6,6) 
Write(*,*) "Calculating one-loop decays of Sd " 
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
! Sd Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToSdAh(cplAhSdcSd,MAh,MSd,MAh2,MSd2,AmpTreeSdToSdAh)

  Else 
Call Amplitude_Tree_NMSSM_SdToSdAh(ZcplAhSdcSd,MAh,MSd,MAh2,MSd2,AmpTreeSdToSdAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToSdAh(MLambda,em,gs,cplAhSdcSd,MAhOS,MSdOS,MRPSdToSdAh,      & 
& MRGSdToSdAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToSdAh(MLambda,em,gs,ZcplAhSdcSd,MAhOS,MSdOS,MRPSdToSdAh,     & 
& MRGSdToSdAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToSdAh(MLambda,em,gs,cplAhSdcSd,MAh,MSd,MRPSdToSdAh,          & 
& MRGSdToSdAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToSdAh(MLambda,em,gs,ZcplAhSdcSd,MAh,MSd,MRPSdToSdAh,         & 
& MRGSdToSdAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSdAh(cplAhSdcSd,ctcplAhSdcSd,MAh,MAh2,MSd,              & 
& MSd2,ZfAh,ZfSd,AmpWaveSdToSdAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSdAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,              & 
& MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,         & 
& cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,           & 
& cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,              & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexSdToSdAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRdrSdToSdAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdAh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,             & 
& MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVG2,MVP2,           & 
& MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,           & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHpmcHpm,cplAhHpmcVWm,ZcplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,              & 
& cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,            & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,             & 
& cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,& 
& cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,  & 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosSdToSdAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,ZcplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosSdToSdAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdAh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,             & 
& MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVG2,MVP2,           & 
& MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,           & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,            & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,             & 
& cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,& 
& cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,  & 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosSdToSdAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosSdToSdAh)

 End if 
 End if 
AmpVertexSdToSdAh = AmpVertexSdToSdAh -  AmpVertexIRdrSdToSdAh! +  AmpVertexIRosSdToSdAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToSdAh=0._dp 
AmpVertexZSdToSdAh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSdAh(gt2,:,:) = AmpWaveZSdToSdAh(gt2,:,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToSdAh(gt1,:,:) 
AmpVertexZSdToSdAh(gt2,:,:)= AmpVertexZSdToSdAh(gt2,:,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToSdAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveSdToSdAh=AmpWaveZSdToSdAh 
AmpVertexSdToSdAh= AmpVertexZSdToSdAh
! Final State 1 
AmpWaveZSdToSdAh=0._dp 
AmpVertexZSdToSdAh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSdAh(:,gt2,:) = AmpWaveZSdToSdAh(:,gt2,:)+ZRUZD(gt2,gt1)*AmpWaveSdToSdAh(:,gt1,:) 
AmpVertexZSdToSdAh(:,gt2,:)= AmpVertexZSdToSdAh(:,gt2,:)+ZRUZD(gt2,gt1)*AmpVertexSdToSdAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToSdAh=AmpWaveZSdToSdAh 
AmpVertexSdToSdAh= AmpVertexZSdToSdAh
! Final State 2 
AmpWaveZSdToSdAh=0._dp 
AmpVertexZSdToSdAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSdToSdAh(:,:,gt2) = AmpWaveZSdToSdAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveSdToSdAh(:,:,gt1) 
AmpVertexZSdToSdAh(:,:,gt2)= AmpVertexZSdToSdAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexSdToSdAh(:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToSdAh=AmpWaveZSdToSdAh 
AmpVertexSdToSdAh= AmpVertexZSdToSdAh
End if
If (ShiftIRdiv) Then 
AmpVertexSdToSdAh = AmpVertexSdToSdAh  +  AmpVertexIRosSdToSdAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Sd Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToSdAh = AmpTreeSdToSdAh 
 AmpSum2SdToSdAh = AmpTreeSdToSdAh + 2._dp*AmpWaveSdToSdAh + 2._dp*AmpVertexSdToSdAh  
Else 
 AmpSumSdToSdAh = AmpTreeSdToSdAh + AmpWaveSdToSdAh + AmpVertexSdToSdAh
 AmpSum2SdToSdAh = AmpTreeSdToSdAh + AmpWaveSdToSdAh + AmpVertexSdToSdAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSdAh = AmpTreeSdToSdAh
 AmpSum2SdToSdAh = AmpTreeSdToSdAh 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
    Do gt3=2,3
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSd(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SdToSdAh = AmpTreeSdToSdAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),MAh(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToSdAh(gt1, gt2, gt3) 
  AmpSum2SdToSdAh = 2._dp*AmpWaveSdToSdAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),MAh(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToSdAh(gt1, gt2, gt3) 
  AmpSum2SdToSdAh = 2._dp*AmpVertexSdToSdAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),MAh(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToSdAh(gt1, gt2, gt3) 
  AmpSum2SdToSdAh = AmpTreeSdToSdAh + 2._dp*AmpWaveSdToSdAh + 2._dp*AmpVertexSdToSdAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),MAh(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToSdAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToSdAh = AmpTreeSdToSdAh
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
  AmpSqTreeSdToSdAh(gt1, gt2, gt3) = AmpSqSdToSdAh(gt1, gt2, gt3)  
  AmpSum2SdToSdAh = + 2._dp*AmpWaveSdToSdAh + 2._dp*AmpVertexSdToSdAh
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
  AmpSqSdToSdAh(gt1, gt2, gt3) = AmpSqSdToSdAh(gt1, gt2, gt3) + AmpSqTreeSdToSdAh(gt1, gt2, gt3)  
Else  
  AmpSum2SdToSdAh = AmpTreeSdToSdAh
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),MAh(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
  AmpSqTreeSdToSdAh(gt1, gt2, gt3) = AmpSqSdToSdAh(gt1, gt2, gt3)  
  AmpSum2SdToSdAh = + 2._dp*AmpWaveSdToSdAh + 2._dp*AmpVertexSdToSdAh
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),MAh(gt3),AmpSumSdToSdAh(gt1, gt2, gt3),AmpSum2SdToSdAh(gt1, gt2, gt3),AmpSqSdToSdAh(gt1, gt2, gt3)) 
  AmpSqSdToSdAh(gt1, gt2, gt3) = AmpSqSdToSdAh(gt1, gt2, gt3) + AmpSqTreeSdToSdAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSdToSdAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSdAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MSdOS(gt2),MAhOS(gt3),helfactor*AmpSqSdToSdAh(gt1, gt2, gt3))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MSd(gt2),MAh(gt3),helfactor*AmpSqSdToSdAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPSdToSdAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToSdAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSdToSdAh(gt1, gt2, gt3) + MRGSdToSdAh(gt1, gt2, gt3)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSdToSdAh(gt1, gt2, gt3) + MRGSdToSdAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fu Cha
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToFuCha(cplChaFucSdL,cplChaFucSdR,MCha,MFu,               & 
& MSd,MCha2,MFu2,MSd2,AmpTreeSdToFuCha)

  Else 
Call Amplitude_Tree_NMSSM_SdToFuCha(ZcplChaFucSdL,ZcplChaFucSdR,MCha,MFu,             & 
& MSd,MCha2,MFu2,MSd2,AmpTreeSdToFuCha)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToFuCha(MLambda,em,gs,cplChaFucSdL,cplChaFucSdR,              & 
& MChaOS,MFuOS,MSdOS,MRPSdToFuCha,MRGSdToFuCha)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToFuCha(MLambda,em,gs,ZcplChaFucSdL,ZcplChaFucSdR,            & 
& MChaOS,MFuOS,MSdOS,MRPSdToFuCha,MRGSdToFuCha)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToFuCha(MLambda,em,gs,cplChaFucSdL,cplChaFucSdR,              & 
& MCha,MFu,MSd,MRPSdToFuCha,MRGSdToFuCha)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToFuCha(MLambda,em,gs,ZcplChaFucSdL,ZcplChaFucSdR,            & 
& MCha,MFu,MSd,MRPSdToFuCha,MRGSdToFuCha)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToFuCha(cplChaFucSdL,cplChaFucSdR,ctcplChaFucSdL,         & 
& ctcplChaFucSdR,MCha,MCha2,MFu,MFu2,MSd,MSd2,ZfFUL,ZfFUR,ZfLm,ZfLp,ZfSd,AmpWaveSdToFuCha)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToFuCha(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,         & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,      & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,      & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,          & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSdcSd,              & 
& cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexSdToFuCha)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToFuCha(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,      & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,      & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,          & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSdcSd,              & 
& cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRdrSdToFuCha)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFuCha(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,cplChiChacHpmL,         & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,ZcplChaFucSdL,ZcplChaFucSdR,              & 
& cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,cplcChaChaVPR,     & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,       & 
& cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSdcSd,cplHpmSucSd,              & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToFuCha)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFuCha(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,ZcplChaFucSdL,  & 
& ZcplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,     & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,      & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,          & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSdcSd,              & 
& cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToFuCha)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFuCha(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,cplChiChacHpmL,         & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,  & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,     & 
& cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,        & 
& cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,           & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,     & 
& cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToFuCha)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFuCha(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,      & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,      & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,          & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSdcSd,              & 
& cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToFuCha)

 End if 
 End if 
AmpVertexSdToFuCha = AmpVertexSdToFuCha -  AmpVertexIRdrSdToFuCha! +  AmpVertexIRosSdToFuCha ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToFuCha=0._dp 
AmpVertexZSdToFuCha=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToFuCha(:,gt2,:,:) = AmpWaveZSdToFuCha(:,gt2,:,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToFuCha(:,gt1,:,:) 
AmpVertexZSdToFuCha(:,gt2,:,:)= AmpVertexZSdToFuCha(:,gt2,:,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToFuCha(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveSdToFuCha=AmpWaveZSdToFuCha 
AmpVertexSdToFuCha= AmpVertexZSdToFuCha
! Final State 1 
AmpWaveZSdToFuCha=0._dp 
AmpVertexZSdToFuCha=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSdToFuCha(1,:,gt2,:) = AmpWaveZSdToFuCha(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpWaveSdToFuCha(1,:,gt1,:) 
AmpVertexZSdToFuCha(1,:,gt2,:)= AmpVertexZSdToFuCha(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpVertexSdToFuCha(1,:,gt1,:) 
AmpWaveZSdToFuCha(2,:,gt2,:) = AmpWaveZSdToFuCha(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpWaveSdToFuCha(2,:,gt1,:) 
AmpVertexZSdToFuCha(2,:,gt2,:)= AmpVertexZSdToFuCha(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpVertexSdToFuCha(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToFuCha=AmpWaveZSdToFuCha 
AmpVertexSdToFuCha= AmpVertexZSdToFuCha
! Final State 2 
AmpWaveZSdToFuCha=0._dp 
AmpVertexZSdToFuCha=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZSdToFuCha(1,:,:,gt2) = AmpWaveZSdToFuCha(1,:,:,gt2)+ZRUUM(gt2,gt1)*AmpWaveSdToFuCha(1,:,:,gt1) 
AmpVertexZSdToFuCha(1,:,:,gt2)= AmpVertexZSdToFuCha(1,:,:,gt2)+ZRUUM(gt2,gt1)*AmpVertexSdToFuCha(1,:,:,gt1) 
AmpWaveZSdToFuCha(2,:,:,gt2) = AmpWaveZSdToFuCha(2,:,:,gt2)+ZRUUP(gt2,gt1)*AmpWaveSdToFuCha(2,:,:,gt1) 
AmpVertexZSdToFuCha(2,:,:,gt2)= AmpVertexZSdToFuCha(2,:,:,gt2)+ZRUUP(gt2,gt1)*AmpVertexSdToFuCha(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToFuCha=AmpWaveZSdToFuCha 
AmpVertexSdToFuCha= AmpVertexZSdToFuCha
End if
If (ShiftIRdiv) Then 
AmpVertexSdToFuCha = AmpVertexSdToFuCha  +  AmpVertexIRosSdToFuCha
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Fu Cha -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToFuCha = AmpTreeSdToFuCha 
 AmpSum2SdToFuCha = AmpTreeSdToFuCha + 2._dp*AmpWaveSdToFuCha + 2._dp*AmpVertexSdToFuCha  
Else 
 AmpSumSdToFuCha = AmpTreeSdToFuCha + AmpWaveSdToFuCha + AmpVertexSdToFuCha
 AmpSum2SdToFuCha = AmpTreeSdToFuCha + AmpWaveSdToFuCha + AmpVertexSdToFuCha 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToFuCha = AmpTreeSdToFuCha
 AmpSum2SdToFuCha = AmpTreeSdToFuCha 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,3
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MChaOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MFu(gt2))+Abs(MCha(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SdToFuCha = AmpTreeSdToFuCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFu(gt2),MCha(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToFuCha(gt1, gt2, gt3) 
  AmpSum2SdToFuCha = 2._dp*AmpWaveSdToFuCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFu(gt2),MCha(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToFuCha(gt1, gt2, gt3) 
  AmpSum2SdToFuCha = 2._dp*AmpVertexSdToFuCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFu(gt2),MCha(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToFuCha(gt1, gt2, gt3) 
  AmpSum2SdToFuCha = AmpTreeSdToFuCha + 2._dp*AmpWaveSdToFuCha + 2._dp*AmpVertexSdToFuCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFu(gt2),MCha(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToFuCha(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToFuCha = AmpTreeSdToFuCha
  Call SquareAmp_StoFF(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
  AmpSqTreeSdToFuCha(gt1, gt2, gt3) = AmpSqSdToFuCha(gt1, gt2, gt3)  
  AmpSum2SdToFuCha = + 2._dp*AmpWaveSdToFuCha + 2._dp*AmpVertexSdToFuCha
  Call SquareAmp_StoFF(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
  AmpSqSdToFuCha(gt1, gt2, gt3) = AmpSqSdToFuCha(gt1, gt2, gt3) + AmpSqTreeSdToFuCha(gt1, gt2, gt3)  
Else  
  AmpSum2SdToFuCha = AmpTreeSdToFuCha
  Call SquareAmp_StoFF(MSd(gt1),MFu(gt2),MCha(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
  AmpSqTreeSdToFuCha(gt1, gt2, gt3) = AmpSqSdToFuCha(gt1, gt2, gt3)  
  AmpSum2SdToFuCha = + 2._dp*AmpWaveSdToFuCha + 2._dp*AmpVertexSdToFuCha
  Call SquareAmp_StoFF(MSd(gt1),MFu(gt2),MCha(gt3),AmpSumSdToFuCha(:,gt1, gt2, gt3),AmpSum2SdToFuCha(:,gt1, gt2, gt3),AmpSqSdToFuCha(gt1, gt2, gt3)) 
  AmpSqSdToFuCha(gt1, gt2, gt3) = AmpSqSdToFuCha(gt1, gt2, gt3) + AmpSqTreeSdToFuCha(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSdToFuCha(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqSdToFuCha(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MFuOS(gt2),MChaOS(gt3),helfactor*AmpSqSdToFuCha(gt1, gt2, gt3))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MFu(gt2),MCha(gt3),helfactor*AmpSqSdToFuCha(gt1, gt2, gt3))
End if 
If ((Abs(MRPSdToFuCha(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToFuCha(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToFuCha(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToFuCha(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSdToFuCha(gt1, gt2, gt3) + MRGSdToFuCha(gt1, gt2, gt3)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSdToFuCha(gt1, gt2, gt3) + MRGSdToFuCha(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fd Chi
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToFdChi(cplChiFdcSdL,cplChiFdcSdR,MChi,MFd,               & 
& MSd,MChi2,MFd2,MSd2,AmpTreeSdToFdChi)

  Else 
Call Amplitude_Tree_NMSSM_SdToFdChi(ZcplChiFdcSdL,ZcplChiFdcSdR,MChi,MFd,             & 
& MSd,MChi2,MFd2,MSd2,AmpTreeSdToFdChi)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToFdChi(MLambda,em,gs,cplChiFdcSdL,cplChiFdcSdR,              & 
& MChiOS,MFdOS,MSdOS,MRPSdToFdChi,MRGSdToFdChi)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToFdChi(MLambda,em,gs,ZcplChiFdcSdL,ZcplChiFdcSdR,            & 
& MChiOS,MFdOS,MSdOS,MRPSdToFdChi,MRGSdToFdChi)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToFdChi(MLambda,em,gs,cplChiFdcSdL,cplChiFdcSdR,              & 
& MChi,MFd,MSd,MRPSdToFdChi,MRGSdToFdChi)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToFdChi(MLambda,em,gs,ZcplChiFdcSdL,ZcplChiFdcSdR,            & 
& MChi,MFd,MSd,MRPSdToFdChi,MRGSdToFdChi)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToFdChi(cplChiFdcSdL,cplChiFdcSdR,ctcplChiFdcSdL,         & 
& ctcplChiFdcSdR,MChi,MChi2,MFd,MFd2,MSd,MSd2,ZfFDL,ZfFDR,ZfL0,ZfSd,AmpWaveSdToFdChi)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToFdChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,     & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,         & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexSdToFdChi)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToFdChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,     & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,         & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRdrSdToFdChi)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFdChi(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChiChacHpmL,           & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,ZcplChiFdcSdL,ZcplChiFdcSdR,cplChiFucSuL,       & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,      & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,     & 
& AmpVertexIRosSdToFdChi)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFdChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,ZcplChiFdcSdL,        & 
& ZcplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,    & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,     & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,         & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToFdChi)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFdChi(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChiChacHpmL,           & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,      & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,     & 
& AmpVertexIRosSdToFdChi)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToFdChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplAhSdcSd,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,     & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,         & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToFdChi)

 End if 
 End if 
AmpVertexSdToFdChi = AmpVertexSdToFdChi -  AmpVertexIRdrSdToFdChi! +  AmpVertexIRosSdToFdChi ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToFdChi=0._dp 
AmpVertexZSdToFdChi=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToFdChi(:,gt2,:,:) = AmpWaveZSdToFdChi(:,gt2,:,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToFdChi(:,gt1,:,:) 
AmpVertexZSdToFdChi(:,gt2,:,:)= AmpVertexZSdToFdChi(:,gt2,:,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToFdChi(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveSdToFdChi=AmpWaveZSdToFdChi 
AmpVertexSdToFdChi= AmpVertexZSdToFdChi
! Final State 1 
AmpWaveZSdToFdChi=0._dp 
AmpVertexZSdToFdChi=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSdToFdChi(1,:,gt2,:) = AmpWaveZSdToFdChi(1,:,gt2,:)+ZRUZDL(gt2,gt1)*AmpWaveSdToFdChi(1,:,gt1,:) 
AmpVertexZSdToFdChi(1,:,gt2,:)= AmpVertexZSdToFdChi(1,:,gt2,:)+ZRUZDL(gt2,gt1)*AmpVertexSdToFdChi(1,:,gt1,:) 
AmpWaveZSdToFdChi(2,:,gt2,:) = AmpWaveZSdToFdChi(2,:,gt2,:)+ZRUZDRc(gt2,gt1)*AmpWaveSdToFdChi(2,:,gt1,:) 
AmpVertexZSdToFdChi(2,:,gt2,:)= AmpVertexZSdToFdChi(2,:,gt2,:)+ZRUZDRc(gt2,gt1)*AmpVertexSdToFdChi(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToFdChi=AmpWaveZSdToFdChi 
AmpVertexSdToFdChi= AmpVertexZSdToFdChi
! Final State 2 
AmpWaveZSdToFdChi=0._dp 
AmpVertexZSdToFdChi=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZSdToFdChi(1,:,:,gt2) = AmpWaveZSdToFdChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveSdToFdChi(1,:,:,gt1) 
AmpVertexZSdToFdChi(1,:,:,gt2)= AmpVertexZSdToFdChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexSdToFdChi(1,:,:,gt1) 
AmpWaveZSdToFdChi(2,:,:,gt2) = AmpWaveZSdToFdChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveSdToFdChi(2,:,:,gt1) 
AmpVertexZSdToFdChi(2,:,:,gt2)= AmpVertexZSdToFdChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexSdToFdChi(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToFdChi=AmpWaveZSdToFdChi 
AmpVertexSdToFdChi= AmpVertexZSdToFdChi
End if
If (ShiftIRdiv) Then 
AmpVertexSdToFdChi = AmpVertexSdToFdChi  +  AmpVertexIRosSdToFdChi
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Fd Chi -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToFdChi = AmpTreeSdToFdChi 
 AmpSum2SdToFdChi = AmpTreeSdToFdChi + 2._dp*AmpWaveSdToFdChi + 2._dp*AmpVertexSdToFdChi  
Else 
 AmpSumSdToFdChi = AmpTreeSdToFdChi + AmpWaveSdToFdChi + AmpVertexSdToFdChi
 AmpSum2SdToFdChi = AmpTreeSdToFdChi + AmpWaveSdToFdChi + AmpVertexSdToFdChi 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToFdChi = AmpTreeSdToFdChi
 AmpSum2SdToFdChi = AmpTreeSdToFdChi 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,3
    Do gt3=1,5
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MFdOS(gt2))+Abs(MChiOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MFd(gt2))+Abs(MChi(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SdToFdChi = AmpTreeSdToFdChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFd(gt2),MChi(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToFdChi(gt1, gt2, gt3) 
  AmpSum2SdToFdChi = 2._dp*AmpWaveSdToFdChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFd(gt2),MChi(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToFdChi(gt1, gt2, gt3) 
  AmpSum2SdToFdChi = 2._dp*AmpVertexSdToFdChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFd(gt2),MChi(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToFdChi(gt1, gt2, gt3) 
  AmpSum2SdToFdChi = AmpTreeSdToFdChi + 2._dp*AmpWaveSdToFdChi + 2._dp*AmpVertexSdToFdChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MFd(gt2),MChi(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToFdChi(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToFdChi = AmpTreeSdToFdChi
  Call SquareAmp_StoFF(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
  AmpSqTreeSdToFdChi(gt1, gt2, gt3) = AmpSqSdToFdChi(gt1, gt2, gt3)  
  AmpSum2SdToFdChi = + 2._dp*AmpWaveSdToFdChi + 2._dp*AmpVertexSdToFdChi
  Call SquareAmp_StoFF(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
  AmpSqSdToFdChi(gt1, gt2, gt3) = AmpSqSdToFdChi(gt1, gt2, gt3) + AmpSqTreeSdToFdChi(gt1, gt2, gt3)  
Else  
  AmpSum2SdToFdChi = AmpTreeSdToFdChi
  Call SquareAmp_StoFF(MSd(gt1),MFd(gt2),MChi(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
  AmpSqTreeSdToFdChi(gt1, gt2, gt3) = AmpSqSdToFdChi(gt1, gt2, gt3)  
  AmpSum2SdToFdChi = + 2._dp*AmpWaveSdToFdChi + 2._dp*AmpVertexSdToFdChi
  Call SquareAmp_StoFF(MSd(gt1),MFd(gt2),MChi(gt3),AmpSumSdToFdChi(:,gt1, gt2, gt3),AmpSum2SdToFdChi(:,gt1, gt2, gt3),AmpSqSdToFdChi(gt1, gt2, gt3)) 
  AmpSqSdToFdChi(gt1, gt2, gt3) = AmpSqSdToFdChi(gt1, gt2, gt3) + AmpSqTreeSdToFdChi(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSdToFdChi(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqSdToFdChi(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MFdOS(gt2),MChiOS(gt3),helfactor*AmpSqSdToFdChi(gt1, gt2, gt3))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MFd(gt2),MChi(gt3),helfactor*AmpSqSdToFdChi(gt1, gt2, gt3))
End if 
If ((Abs(MRPSdToFdChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToFdChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToFdChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToFdChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSdToFdChi(gt1, gt2, gt3) + MRGSdToFdChi(gt1, gt2, gt3)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSdToFdChi(gt1, gt2, gt3) + MRGSdToFdChi(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Glu Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToGluFd(cplGluFdcSdL,cplGluFdcSdR,MFd,MGlu,               & 
& MSd,MFd2,MGlu2,MSd2,AmpTreeSdToGluFd)

  Else 
Call Amplitude_Tree_NMSSM_SdToGluFd(ZcplGluFdcSdL,ZcplGluFdcSdR,MFd,MGlu,             & 
& MSd,MFd2,MGlu2,MSd2,AmpTreeSdToGluFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToGluFd(MLambda,em,gs,cplGluFdcSdL,cplGluFdcSdR,              & 
& MFdOS,MGluOS,MSdOS,MRPSdToGluFd,MRGSdToGluFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToGluFd(MLambda,em,gs,ZcplGluFdcSdL,ZcplGluFdcSdR,            & 
& MFdOS,MGluOS,MSdOS,MRPSdToGluFd,MRGSdToGluFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToGluFd(MLambda,em,gs,cplGluFdcSdL,cplGluFdcSdR,              & 
& MFd,MGlu,MSd,MRPSdToGluFd,MRGSdToGluFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToGluFd(MLambda,em,gs,ZcplGluFdcSdL,ZcplGluFdcSdR,            & 
& MFd,MGlu,MSd,MRPSdToGluFd,MRGSdToGluFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToGluFd(cplGluFdcSdL,cplGluFdcSdR,ctcplGluFdcSdL,         & 
& ctcplGluFdcSdR,MFd,MFd2,MGlu,MGlu2,MSd,MSd2,ZfFDL,ZfFDR,ZffG,ZfSd,AmpWaveSdToGluFd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToGluFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,             & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexSdToGluFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToGluFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRdrSdToGluFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToGluFd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,             & 
& cplChiFdcSdR,ZcplGluFdcSdL,ZcplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,    & 
& cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,      & 
& AmpVertexIRosSdToGluFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToGluFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,ZcplGluFdcSdL,ZcplGluFdcSdR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToGluFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToGluFd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,             & 
& cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,    & 
& cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,      & 
& AmpVertexIRosSdToGluFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToGluFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosSdToGluFd)

 End if 
 End if 
AmpVertexSdToGluFd = AmpVertexSdToGluFd -  AmpVertexIRdrSdToGluFd! +  AmpVertexIRosSdToGluFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToGluFd=0._dp 
AmpVertexZSdToGluFd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToGluFd(:,gt2,:) = AmpWaveZSdToGluFd(:,gt2,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToGluFd(:,gt1,:) 
AmpVertexZSdToGluFd(:,gt2,:)= AmpVertexZSdToGluFd(:,gt2,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToGluFd(:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToGluFd=AmpWaveZSdToGluFd 
AmpVertexSdToGluFd= AmpVertexZSdToGluFd
! Final State 2 
AmpWaveZSdToGluFd=0._dp 
AmpVertexZSdToGluFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSdToGluFd(1,:,gt2) = AmpWaveZSdToGluFd(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveSdToGluFd(1,:,gt1) 
AmpVertexZSdToGluFd(1,:,gt2)= AmpVertexZSdToGluFd(1,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexSdToGluFd(1,:,gt1) 
AmpWaveZSdToGluFd(2,:,gt2) = AmpWaveZSdToGluFd(2,:,gt2)+ZRUZDR(gt2,gt1)*AmpWaveSdToGluFd(2,:,gt1) 
AmpVertexZSdToGluFd(2,:,gt2)= AmpVertexZSdToGluFd(2,:,gt2)+ZRUZDR(gt2,gt1)*AmpVertexSdToGluFd(2,:,gt1) 
 End Do 
End Do 
AmpWaveSdToGluFd=AmpWaveZSdToGluFd 
AmpVertexSdToGluFd= AmpVertexZSdToGluFd
End if
If (ShiftIRdiv) Then 
AmpVertexSdToGluFd = AmpVertexSdToGluFd  +  AmpVertexIRosSdToGluFd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Glu Fd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToGluFd = AmpTreeSdToGluFd 
 AmpSum2SdToGluFd = AmpTreeSdToGluFd + 2._dp*AmpWaveSdToGluFd + 2._dp*AmpVertexSdToGluFd  
Else 
 AmpSumSdToGluFd = AmpTreeSdToGluFd + AmpWaveSdToGluFd + AmpVertexSdToGluFd
 AmpSum2SdToGluFd = AmpTreeSdToGluFd + AmpWaveSdToGluFd + AmpVertexSdToGluFd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToGluFd = AmpTreeSdToGluFd
 AmpSum2SdToGluFd = AmpTreeSdToGluFd 
End if 
Do gt1=1,6
i4 = isave 
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MGluOS)+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MGlu)+Abs(MFd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt3 
  AmpSum2SdToGluFd = AmpTreeSdToGluFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MGluOS,MFdOS(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MGlu,MFd(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToGluFd(gt1, gt3) 
  AmpSum2SdToGluFd = 2._dp*AmpWaveSdToGluFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MGluOS,MFdOS(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MGlu,MFd(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToGluFd(gt1, gt3) 
  AmpSum2SdToGluFd = 2._dp*AmpVertexSdToGluFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MGluOS,MFdOS(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MGlu,MFd(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToGluFd(gt1, gt3) 
  AmpSum2SdToGluFd = AmpTreeSdToGluFd + 2._dp*AmpWaveSdToGluFd + 2._dp*AmpVertexSdToGluFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSdOS(gt1),MGluOS,MFdOS(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSd(gt1),MGlu,MFd(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToGluFd(gt1, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToGluFd = AmpTreeSdToGluFd
  Call SquareAmp_StoFF(MSdOS(gt1),MGluOS,MFdOS(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
  AmpSqTreeSdToGluFd(gt1, gt3) = AmpSqSdToGluFd(gt1, gt3)  
  AmpSum2SdToGluFd = + 2._dp*AmpWaveSdToGluFd + 2._dp*AmpVertexSdToGluFd
  Call SquareAmp_StoFF(MSdOS(gt1),MGluOS,MFdOS(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
  AmpSqSdToGluFd(gt1, gt3) = AmpSqSdToGluFd(gt1, gt3) + AmpSqTreeSdToGluFd(gt1, gt3)  
Else  
  AmpSum2SdToGluFd = AmpTreeSdToGluFd
  Call SquareAmp_StoFF(MSd(gt1),MGlu,MFd(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
  AmpSqTreeSdToGluFd(gt1, gt3) = AmpSqSdToGluFd(gt1, gt3)  
  AmpSum2SdToGluFd = + 2._dp*AmpWaveSdToGluFd + 2._dp*AmpVertexSdToGluFd
  Call SquareAmp_StoFF(MSd(gt1),MGlu,MFd(gt3),AmpSumSdToGluFd(:,gt1, gt3),AmpSum2SdToGluFd(:,gt1, gt3),AmpSqSdToGluFd(gt1, gt3)) 
  AmpSqSdToGluFd(gt1, gt3) = AmpSqSdToGluFd(gt1, gt3) + AmpSqTreeSdToGluFd(gt1, gt3)  
End if  
Else  
  AmpSqSdToGluFd(gt1, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqSdToGluFd(gt1, gt3).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 4._dp/3._dp*GammaTPS(MSdOS(gt1),MGluOS,MFdOS(gt3),helfactor*AmpSqSdToGluFd(gt1, gt3))
Else 
  gP1LSd(gt1,i4) = 4._dp/3._dp*GammaTPS(MSd(gt1),MGlu,MFd(gt3),helfactor*AmpSqSdToGluFd(gt1, gt3))
End if 
If ((Abs(MRPSdToGluFd(gt1, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToGluFd(gt1, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToGluFd(gt1, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToGluFd(gt1, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSdToGluFd(gt1, gt3) + MRGSdToGluFd(gt1, gt3)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSdToGluFd(gt1, gt3) + MRGSdToGluFd(gt1, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Sd hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToSdhh(cplhhSdcSd,Mhh,MSd,Mhh2,MSd2,AmpTreeSdToSdhh)

  Else 
Call Amplitude_Tree_NMSSM_SdToSdhh(ZcplhhSdcSd,Mhh,MSd,Mhh2,MSd2,AmpTreeSdToSdhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToSdhh(MLambda,em,gs,cplhhSdcSd,MhhOS,MSdOS,MRPSdToSdhh,      & 
& MRGSdToSdhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToSdhh(MLambda,em,gs,ZcplhhSdcSd,MhhOS,MSdOS,MRPSdToSdhh,     & 
& MRGSdToSdhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToSdhh(MLambda,em,gs,cplhhSdcSd,Mhh,MSd,MRPSdToSdhh,          & 
& MRGSdToSdhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToSdhh(MLambda,em,gs,ZcplhhSdcSd,Mhh,MSd,MRPSdToSdhh,         & 
& MRGSdToSdhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSdhh(cplhhSdcSd,ctcplhhSdcSd,Mhh,Mhh2,MSd,              & 
& MSd2,Zfhh,ZfSd,AmpWaveSdToSdhh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSdhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhSdcSd,     & 
& cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,cplcFdGluSdR,             & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,      & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,      & 
& cplAhhhSdcSdaa,cplhhhhSdcSdaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplHpmSdcHpmcSdaa,      & 
& cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,& 
& cplSdSvcSdcSvaa,cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,AmpVertexSdToSdhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,          & 
& cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,         & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,             & 
& cplcFdGluSdR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,      & 
& cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,          & 
& cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplhhhhSdcSdaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,         & 
& cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,cplSdSucSdcSuabba,& 
& cplSdSucSdcSuabab,cplSdSvcSdcSvaa,cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,AmpVertexIRdrSdToSdhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdhh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhSdcSd,              & 
& cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,cplcFdGluSdR,             & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,ZcplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,      & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,      & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,      & 
& cplAhhhSdcSdaa,cplhhhhSdcSdaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplHpmSdcHpmcSdaa,      & 
& cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,& 
& cplSdSvcSdcSvaa,cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,AmpVertexIRosSdToSdhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,          & 
& cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,         & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,             & 
& cplcFdGluSdR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,ZcplhhSdcSd,cplhhSecSe,               & 
& cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,cplSdcSdVG,      & 
& cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplhhhhSdcSdaa,cplhhHpmSucSdaa,              & 
& cplhhSdcHpmcSuaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,& 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSdSvcSdcSvaa,cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,  & 
& AmpVertexIRosSdToSdhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdhh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhSdcSd,              & 
& cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,cplcFdGluSdR,             & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,      & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,      & 
& cplAhhhSdcSdaa,cplhhhhSdcSdaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplHpmSdcHpmcSdaa,      & 
& cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,& 
& cplSdSvcSdcSvaa,cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,AmpVertexIRosSdToSdhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,          & 
& cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,         & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,             & 
& cplcFdGluSdR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,      & 
& cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,          & 
& cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplhhhhSdcSdaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,         & 
& cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab,cplSdSecSdcSeaa,cplSdSucSdcSuabba,& 
& cplSdSucSdcSuabab,cplSdSvcSdcSvaa,cplSdcSdcVWmVWmaa,cplSdcSdVZVZaa,AmpVertexIRosSdToSdhh)

 End if 
 End if 
AmpVertexSdToSdhh = AmpVertexSdToSdhh -  AmpVertexIRdrSdToSdhh! +  AmpVertexIRosSdToSdhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToSdhh=0._dp 
AmpVertexZSdToSdhh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSdhh(gt2,:,:) = AmpWaveZSdToSdhh(gt2,:,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToSdhh(gt1,:,:) 
AmpVertexZSdToSdhh(gt2,:,:)= AmpVertexZSdToSdhh(gt2,:,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToSdhh(gt1,:,:) 
 End Do 
End Do 
AmpWaveSdToSdhh=AmpWaveZSdToSdhh 
AmpVertexSdToSdhh= AmpVertexZSdToSdhh
! Final State 1 
AmpWaveZSdToSdhh=0._dp 
AmpVertexZSdToSdhh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSdhh(:,gt2,:) = AmpWaveZSdToSdhh(:,gt2,:)+ZRUZD(gt2,gt1)*AmpWaveSdToSdhh(:,gt1,:) 
AmpVertexZSdToSdhh(:,gt2,:)= AmpVertexZSdToSdhh(:,gt2,:)+ZRUZD(gt2,gt1)*AmpVertexSdToSdhh(:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToSdhh=AmpWaveZSdToSdhh 
AmpVertexSdToSdhh= AmpVertexZSdToSdhh
! Final State 2 
AmpWaveZSdToSdhh=0._dp 
AmpVertexZSdToSdhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSdToSdhh(:,:,gt2) = AmpWaveZSdToSdhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveSdToSdhh(:,:,gt1) 
AmpVertexZSdToSdhh(:,:,gt2)= AmpVertexZSdToSdhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexSdToSdhh(:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToSdhh=AmpWaveZSdToSdhh 
AmpVertexSdToSdhh= AmpVertexZSdToSdhh
End if
If (ShiftIRdiv) Then 
AmpVertexSdToSdhh = AmpVertexSdToSdhh  +  AmpVertexIRosSdToSdhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Sd hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToSdhh = AmpTreeSdToSdhh 
 AmpSum2SdToSdhh = AmpTreeSdToSdhh + 2._dp*AmpWaveSdToSdhh + 2._dp*AmpVertexSdToSdhh  
Else 
 AmpSumSdToSdhh = AmpTreeSdToSdhh + AmpWaveSdToSdhh + AmpVertexSdToSdhh
 AmpSum2SdToSdhh = AmpTreeSdToSdhh + AmpWaveSdToSdhh + AmpVertexSdToSdhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSdhh = AmpTreeSdToSdhh
 AmpSum2SdToSdhh = AmpTreeSdToSdhh 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSd(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SdToSdhh = AmpTreeSdToSdhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),Mhh(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToSdhh(gt1, gt2, gt3) 
  AmpSum2SdToSdhh = 2._dp*AmpWaveSdToSdhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),Mhh(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToSdhh(gt1, gt2, gt3) 
  AmpSum2SdToSdhh = 2._dp*AmpVertexSdToSdhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),Mhh(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToSdhh(gt1, gt2, gt3) 
  AmpSum2SdToSdhh = AmpTreeSdToSdhh + 2._dp*AmpWaveSdToSdhh + 2._dp*AmpVertexSdToSdhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),Mhh(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToSdhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToSdhh = AmpTreeSdToSdhh
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
  AmpSqTreeSdToSdhh(gt1, gt2, gt3) = AmpSqSdToSdhh(gt1, gt2, gt3)  
  AmpSum2SdToSdhh = + 2._dp*AmpWaveSdToSdhh + 2._dp*AmpVertexSdToSdhh
  Call SquareAmp_StoSS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
  AmpSqSdToSdhh(gt1, gt2, gt3) = AmpSqSdToSdhh(gt1, gt2, gt3) + AmpSqTreeSdToSdhh(gt1, gt2, gt3)  
Else  
  AmpSum2SdToSdhh = AmpTreeSdToSdhh
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),Mhh(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
  AmpSqTreeSdToSdhh(gt1, gt2, gt3) = AmpSqSdToSdhh(gt1, gt2, gt3)  
  AmpSum2SdToSdhh = + 2._dp*AmpWaveSdToSdhh + 2._dp*AmpVertexSdToSdhh
  Call SquareAmp_StoSS(MSd(gt1),MSd(gt2),Mhh(gt3),AmpSumSdToSdhh(gt1, gt2, gt3),AmpSum2SdToSdhh(gt1, gt2, gt3),AmpSqSdToSdhh(gt1, gt2, gt3)) 
  AmpSqSdToSdhh(gt1, gt2, gt3) = AmpSqSdToSdhh(gt1, gt2, gt3) + AmpSqTreeSdToSdhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSdToSdhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSdhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MSdOS(gt2),MhhOS(gt3),helfactor*AmpSqSdToSdhh(gt1, gt2, gt3))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MSd(gt2),Mhh(gt3),helfactor*AmpSqSdToSdhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPSdToSdhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToSdhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSdToSdhh(gt1, gt2, gt3) + MRGSdToSdhh(gt1, gt2, gt3)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSdToSdhh(gt1, gt2, gt3) + MRGSdToSdhh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Su Hpm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToSuHpm(cplHpmSucSd,MHpm,MSd,MSu,MHpm2,MSd2,              & 
& MSu2,AmpTreeSdToSuHpm)

  Else 
Call Amplitude_Tree_NMSSM_SdToSuHpm(ZcplHpmSucSd,MHpm,MSd,MSu,MHpm2,MSd2,             & 
& MSu2,AmpTreeSdToSuHpm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToSuHpm(MLambda,em,gs,cplHpmSucSd,MHpmOS,MSdOS,               & 
& MSuOS,MRPSdToSuHpm,MRGSdToSuHpm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToSuHpm(MLambda,em,gs,ZcplHpmSucSd,MHpmOS,MSdOS,              & 
& MSuOS,MRPSdToSuHpm,MRGSdToSuHpm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToSuHpm(MLambda,em,gs,cplHpmSucSd,MHpm,MSd,MSu,               & 
& MRPSdToSuHpm,MRGSdToSuHpm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToSuHpm(MLambda,em,gs,ZcplHpmSucSd,MHpm,MSd,MSu,              & 
& MRPSdToSuHpm,MRGSdToSuHpm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSuHpm(cplHpmSucSd,ctcplHpmSucSd,MHpm,MHpm2,             & 
& MSd,MSd2,MSu,MSu2,ZfHpm,ZfSd,ZfSu,AmpWaveSdToSuHpm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSuHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,         & 
& cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,           & 
& cplChiFdcSdR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,     & 
& cplGluFdcSdR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,         & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,               & 
& cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,               & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhHpmSucSdaa,cplhhHpmSucSdaa,          & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,               & 
& cplSeSucSdcSvaa,cplSucSdVPVWmaa,cplSucSdVWmVZaa,AmpVertexSdToSuHpm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhHpmcVWm,              & 
& cplAhSdcSd,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,             & 
& cplChiFdcSdL,cplChiFdcSdR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuChiSuL,cplcFuChiSuR,     & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuGluSuL,cplcFuGluSuR,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,               & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,             & 
& cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhHpmSucSdaa,               & 
& cplhhHpmSucSdaa,cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,& 
& cplSeSucSdcSvaa,cplSucSdVPVWmaa,cplSucSdVWmVZaa,AmpVertexIRdrSdToSuHpm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuHpm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,       & 
& cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,     & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhHpmcVWm,         & 
& cplhhSdcSd,cplhhSucSu,ZcplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,              & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,      & 
& cplSucSdVWm,cplSucSuVZ,cplAhHpmSucSdaa,cplhhHpmSucSdaa,cplHpmSdcHpmcSdaa,              & 
& cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSdcSvaa,cplSucSdVPVWmaa, & 
& cplSucSdVWmVZaa,AmpVertexIRosSdToSuHpm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhHpmcVWm,              & 
& cplAhSdcSd,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,             & 
& cplChiFdcSdL,cplChiFdcSdR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuChiSuL,cplcFuChiSuR,     & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuGluSuL,cplcFuGluSuR,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,ZcplHpmSucSd,cplHpmSvcSe,              & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,             & 
& cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhHpmSucSdaa,               & 
& cplhhHpmSucSdaa,cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,& 
& cplSeSucSdcSvaa,cplSucSdVPVWmaa,cplSucSdVWmVZaa,AmpVertexIRosSdToSuHpm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuHpm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,       & 
& cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,     & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuGluSuL,cplcFuGluSuR,cplhhHpmcHpm,cplhhHpmcVWm,         & 
& cplhhSdcSd,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,               & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,      & 
& cplSucSdVWm,cplSucSuVZ,cplAhHpmSucSdaa,cplhhHpmSucSdaa,cplHpmSdcHpmcSdaa,              & 
& cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSdcSvaa,cplSucSdVPVWmaa, & 
& cplSucSdVWmVZaa,AmpVertexIRosSdToSuHpm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuHpm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhHpmcVWm,              & 
& cplAhSdcSd,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,             & 
& cplChiFdcSdL,cplChiFdcSdR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuChiSuL,cplcFuChiSuR,     & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuGluSuL,cplcFuGluSuR,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,               & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,             & 
& cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhHpmSucSdaa,               & 
& cplhhHpmSucSdaa,cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,& 
& cplSeSucSdcSvaa,cplSucSdVPVWmaa,cplSucSdVWmVZaa,AmpVertexIRosSdToSuHpm)

 End if 
 End if 
AmpVertexSdToSuHpm = AmpVertexSdToSuHpm -  AmpVertexIRdrSdToSuHpm! +  AmpVertexIRosSdToSuHpm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToSuHpm=0._dp 
AmpVertexZSdToSuHpm=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSuHpm(gt2,:,:) = AmpWaveZSdToSuHpm(gt2,:,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToSuHpm(gt1,:,:) 
AmpVertexZSdToSuHpm(gt2,:,:)= AmpVertexZSdToSuHpm(gt2,:,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToSuHpm(gt1,:,:) 
 End Do 
End Do 
AmpWaveSdToSuHpm=AmpWaveZSdToSuHpm 
AmpVertexSdToSuHpm= AmpVertexZSdToSuHpm
! Final State 1 
AmpWaveZSdToSuHpm=0._dp 
AmpVertexZSdToSuHpm=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSuHpm(:,gt2,:) = AmpWaveZSdToSuHpm(:,gt2,:)+ZRUZU(gt2,gt1)*AmpWaveSdToSuHpm(:,gt1,:) 
AmpVertexZSdToSuHpm(:,gt2,:)= AmpVertexZSdToSuHpm(:,gt2,:)+ZRUZU(gt2,gt1)*AmpVertexSdToSuHpm(:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToSuHpm=AmpWaveZSdToSuHpm 
AmpVertexSdToSuHpm= AmpVertexZSdToSuHpm
! Final State 2 
AmpWaveZSdToSuHpm=0._dp 
AmpVertexZSdToSuHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZSdToSuHpm(:,:,gt2) = AmpWaveZSdToSuHpm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveSdToSuHpm(:,:,gt1) 
AmpVertexZSdToSuHpm(:,:,gt2)= AmpVertexZSdToSuHpm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexSdToSuHpm(:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToSuHpm=AmpWaveZSdToSuHpm 
AmpVertexSdToSuHpm= AmpVertexZSdToSuHpm
End if
If (ShiftIRdiv) Then 
AmpVertexSdToSuHpm = AmpVertexSdToSuHpm  +  AmpVertexIRosSdToSuHpm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Su Hpm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToSuHpm = AmpTreeSdToSuHpm 
 AmpSum2SdToSuHpm = AmpTreeSdToSuHpm + 2._dp*AmpWaveSdToSuHpm + 2._dp*AmpVertexSdToSuHpm  
Else 
 AmpSumSdToSuHpm = AmpTreeSdToSuHpm + AmpWaveSdToSuHpm + AmpVertexSdToSuHpm
 AmpSum2SdToSuHpm = AmpTreeSdToSuHpm + AmpWaveSdToSuHpm + AmpVertexSdToSuHpm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSuHpm = AmpTreeSdToSuHpm
 AmpSum2SdToSuHpm = AmpTreeSdToSuHpm 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(MHpmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSu(gt2))+Abs(MHpm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SdToSuHpm = AmpTreeSdToSuHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSu(gt2),MHpm(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToSuHpm(gt1, gt2, gt3) 
  AmpSum2SdToSuHpm = 2._dp*AmpWaveSdToSuHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSu(gt2),MHpm(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToSuHpm(gt1, gt2, gt3) 
  AmpSum2SdToSuHpm = 2._dp*AmpVertexSdToSuHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSu(gt2),MHpm(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToSuHpm(gt1, gt2, gt3) 
  AmpSum2SdToSuHpm = AmpTreeSdToSuHpm + 2._dp*AmpWaveSdToSuHpm + 2._dp*AmpVertexSdToSuHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSd(gt1),MSu(gt2),MHpm(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToSuHpm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToSuHpm = AmpTreeSdToSuHpm
  Call SquareAmp_StoSS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
  AmpSqTreeSdToSuHpm(gt1, gt2, gt3) = AmpSqSdToSuHpm(gt1, gt2, gt3)  
  AmpSum2SdToSuHpm = + 2._dp*AmpWaveSdToSuHpm + 2._dp*AmpVertexSdToSuHpm
  Call SquareAmp_StoSS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
  AmpSqSdToSuHpm(gt1, gt2, gt3) = AmpSqSdToSuHpm(gt1, gt2, gt3) + AmpSqTreeSdToSuHpm(gt1, gt2, gt3)  
Else  
  AmpSum2SdToSuHpm = AmpTreeSdToSuHpm
  Call SquareAmp_StoSS(MSd(gt1),MSu(gt2),MHpm(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
  AmpSqTreeSdToSuHpm(gt1, gt2, gt3) = AmpSqSdToSuHpm(gt1, gt2, gt3)  
  AmpSum2SdToSuHpm = + 2._dp*AmpWaveSdToSuHpm + 2._dp*AmpVertexSdToSuHpm
  Call SquareAmp_StoSS(MSd(gt1),MSu(gt2),MHpm(gt3),AmpSumSdToSuHpm(gt1, gt2, gt3),AmpSum2SdToSuHpm(gt1, gt2, gt3),AmpSqSdToSuHpm(gt1, gt2, gt3)) 
  AmpSqSdToSuHpm(gt1, gt2, gt3) = AmpSqSdToSuHpm(gt1, gt2, gt3) + AmpSqTreeSdToSuHpm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSdToSuHpm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSuHpm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MSuOS(gt2),MHpmOS(gt3),helfactor*AmpSqSdToSuHpm(gt1, gt2, gt3))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MSu(gt2),MHpm(gt3),helfactor*AmpSqSdToSuHpm(gt1, gt2, gt3))
End if 
If ((Abs(MRPSdToSuHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToSuHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToSuHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSdToSuHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSdToSuHpm(gt1, gt2, gt3) + MRGSdToSuHpm(gt1, gt2, gt3)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSdToSuHpm(gt1, gt2, gt3) + MRGSdToSuHpm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Sd VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToSdVZ(cplSdcSdVZ,MSd,MVZ,MSd2,MVZ2,AmpTreeSdToSdVZ)

  Else 
Call Amplitude_Tree_NMSSM_SdToSdVZ(ZcplSdcSdVZ,MSd,MVZ,MSd2,MVZ2,AmpTreeSdToSdVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToSdVZ(MLambda,em,gs,cplSdcSdVZ,MSdOS,MVZOS,MRPSdToSdVZ,      & 
& MRGSdToSdVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToSdVZ(MLambda,em,gs,ZcplSdcSdVZ,MSdOS,MVZOS,MRPSdToSdVZ,     & 
& MRGSdToSdVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToSdVZ(MLambda,em,gs,cplSdcSdVZ,MSd,MVZ,MRPSdToSdVZ,          & 
& MRGSdToSdVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToSdVZ(MLambda,em,gs,ZcplSdcSdVZ,MSd,MVZ,MRPSdToSdVZ,         & 
& MRGSdToSdVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSdVZ(cplSdcSdVP,cplSdcSdVZ,ctcplSdcSdVP,ctcplSdcSdVZ,   & 
& MSd,MSd2,MVP,MVP2,MVZ,MVZ2,ZfSd,ZfVPVZ,ZfVZ,AmpWaveSdToSdVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSdVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,              & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,       & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplhhVZVZ,cplHpmSucSd,    & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,           & 
& cplcVWmVWmVZ,cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVPVZaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,  & 
& cplSucSdVWmVZaa,AmpVertexSdToSdVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,       & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplhhVZVZ,cplHpmSucSd,    & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,           & 
& cplcVWmVWmVZ,cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVPVZaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,  & 
& cplSucSdVWmVZaa,AmpVertexIRdrSdToSdVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhhhVZ,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplcChaChaVZL,cplcChaChaVZR,            & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplhhVZVZ,cplHpmSucSd,cplHpmcHpmVZ,               & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,ZcplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,            & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,            & 
& cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVPVZaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,               & 
& cplSucSdVWmVZaa,AmpVertexIRosSdToSdVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,       & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplhhVZVZ,cplHpmSucSd,    & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,ZcplSdcSdVZ,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,           & 
& cplcVWmVWmVZ,cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVPVZaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,  & 
& cplSucSdVWmVZaa,AmpVertexIRosSdToSdVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhhhVZ,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplcChaChaVZL,cplcChaChaVZR,            & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplhhVZVZ,cplHpmSucSd,cplHpmcHpmVZ,               & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,             & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,            & 
& cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVPVZaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,               & 
& cplSucSdVWmVZaa,AmpVertexIRosSdToSdVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSdVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,       & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplhhVZVZ,cplHpmSucSd,    & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,           & 
& cplcVWmVWmVZ,cplSdcSdVGVZLamct3ct2ct1,cplSdcSdVPVZaa,cplSdcSdVZVZaa,cplSdcSucVWmVZaa,  & 
& cplSucSdVWmVZaa,AmpVertexIRosSdToSdVZ)

 End if 
 End if 
AmpVertexSdToSdVZ = AmpVertexSdToSdVZ -  AmpVertexIRdrSdToSdVZ! +  AmpVertexIRosSdToSdVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToSdVZ=0._dp 
AmpVertexZSdToSdVZ=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSdVZ(:,gt2,:) = AmpWaveZSdToSdVZ(:,gt2,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToSdVZ(:,gt1,:) 
AmpVertexZSdToSdVZ(:,gt2,:)= AmpVertexZSdToSdVZ(:,gt2,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToSdVZ(:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToSdVZ=AmpWaveZSdToSdVZ 
AmpVertexSdToSdVZ= AmpVertexZSdToSdVZ
! Final State 1 
AmpWaveZSdToSdVZ=0._dp 
AmpVertexZSdToSdVZ=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSdVZ(:,:,gt2) = AmpWaveZSdToSdVZ(:,:,gt2)+ZRUZD(gt2,gt1)*AmpWaveSdToSdVZ(:,:,gt1) 
AmpVertexZSdToSdVZ(:,:,gt2)= AmpVertexZSdToSdVZ(:,:,gt2)+ZRUZD(gt2,gt1)*AmpVertexSdToSdVZ(:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToSdVZ=AmpWaveZSdToSdVZ 
AmpVertexSdToSdVZ= AmpVertexZSdToSdVZ
End if
If (ShiftIRdiv) Then 
AmpVertexSdToSdVZ = AmpVertexSdToSdVZ  +  AmpVertexIRosSdToSdVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Sd VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToSdVZ = AmpTreeSdToSdVZ 
 AmpSum2SdToSdVZ = AmpTreeSdToSdVZ + 2._dp*AmpWaveSdToSdVZ + 2._dp*AmpVertexSdToSdVZ  
Else 
 AmpSumSdToSdVZ = AmpTreeSdToSdVZ + AmpWaveSdToSdVZ + AmpVertexSdToSdVZ
 AmpSum2SdToSdVZ = AmpTreeSdToSdVZ + AmpWaveSdToSdVZ + AmpVertexSdToSdVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSdVZ = AmpTreeSdToSdVZ
 AmpSum2SdToSdVZ = AmpTreeSdToSdVZ 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSd(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2SdToSdVZ = AmpTreeSdToSdVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),MVZOS,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVZ,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToSdVZ(gt1, gt2) 
  AmpSum2SdToSdVZ = 2._dp*AmpWaveSdToSdVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),MVZOS,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVZ,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToSdVZ(gt1, gt2) 
  AmpSum2SdToSdVZ = 2._dp*AmpVertexSdToSdVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),MVZOS,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVZ,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToSdVZ(gt1, gt2) 
  AmpSum2SdToSdVZ = AmpTreeSdToSdVZ + 2._dp*AmpWaveSdToSdVZ + 2._dp*AmpVertexSdToSdVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),MVZOS,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVZ,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToSdVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToSdVZ = AmpTreeSdToSdVZ
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),MVZOS,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
  AmpSqTreeSdToSdVZ(gt1, gt2) = AmpSqSdToSdVZ(gt1, gt2)  
  AmpSum2SdToSdVZ = + 2._dp*AmpWaveSdToSdVZ + 2._dp*AmpVertexSdToSdVZ
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),MVZOS,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
  AmpSqSdToSdVZ(gt1, gt2) = AmpSqSdToSdVZ(gt1, gt2) + AmpSqTreeSdToSdVZ(gt1, gt2)  
Else  
  AmpSum2SdToSdVZ = AmpTreeSdToSdVZ
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVZ,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
  AmpSqTreeSdToSdVZ(gt1, gt2) = AmpSqSdToSdVZ(gt1, gt2)  
  AmpSum2SdToSdVZ = + 2._dp*AmpWaveSdToSdVZ + 2._dp*AmpVertexSdToSdVZ
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVZ,AmpSumSdToSdVZ(:,gt1, gt2),AmpSum2SdToSdVZ(:,gt1, gt2),AmpSqSdToSdVZ(gt1, gt2)) 
  AmpSqSdToSdVZ(gt1, gt2) = AmpSqSdToSdVZ(gt1, gt2) + AmpSqTreeSdToSdVZ(gt1, gt2)  
End if  
Else  
  AmpSqSdToSdVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSdVZ(gt1, gt2).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MSdOS(gt2),MVZOS,helfactor*AmpSqSdToSdVZ(gt1, gt2))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MSd(gt2),MVZ,helfactor*AmpSqSdToSdVZ(gt1, gt2))
End if 
If ((Abs(MRPSdToSdVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToSdVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPSdToSdVZ(gt1, gt2) + MRGSdToSdVZ(gt1, gt2)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPSdToSdVZ(gt1, gt2) + MRGSdToSdVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Su VWm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SdToSuVWm(cplSucSdVWm,MSd,MSu,MVWm,MSd2,MSu2,               & 
& MVWm2,AmpTreeSdToSuVWm)

  Else 
Call Amplitude_Tree_NMSSM_SdToSuVWm(ZcplSucSdVWm,MSd,MSu,MVWm,MSd2,MSu2,              & 
& MVWm2,AmpTreeSdToSuVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SdToSuVWm(MLambda,em,gs,cplSucSdVWm,MSdOS,MSuOS,MVWmOS,         & 
& MRPSdToSuVWm,MRGSdToSuVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SdToSuVWm(MLambda,em,gs,ZcplSucSdVWm,MSdOS,MSuOS,               & 
& MVWmOS,MRPSdToSuVWm,MRGSdToSuVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SdToSuVWm(MLambda,em,gs,cplSucSdVWm,MSd,MSu,MVWm,               & 
& MRPSdToSuVWm,MRGSdToSuVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SdToSuVWm(MLambda,em,gs,ZcplSucSdVWm,MSd,MSu,MVWm,              & 
& MRPSdToSuVWm,MRGSdToSuVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSuVWm(cplSucSdVWm,ctcplSucSdVWm,MSd,MSd2,               & 
& MSu,MSu2,MVWm,MVWm2,ZfSd,ZfSu,ZfVWm,AmpWaveSdToSuVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSuVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,             & 
& cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFuVWmL,     & 
& cplcFdFuVWmR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,             & 
& cplhhcVWmVWm,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,       & 
& cplSucSdVWm,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,            & 
& cplSdcSdcVWmVWmaa,cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWmVZaa,           & 
& cplSucSucVWmVWmaa,AmpVertexSdToSuVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,        & 
& cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFuVWmL,     & 
& cplcFdFuVWmR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,             & 
& cplhhcVWmVWm,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,       & 
& cplSucSdVWm,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,            & 
& cplSdcSdcVWmVWmaa,cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWmVZaa,           & 
& cplSucSucVWmVWmaa,AmpVertexIRdrSdToSuVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,             & 
& cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,       & 
& cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuGluSuL,       & 
& cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,GosZcplHpmSucSd,          & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,ZcplSucSdVWm,cplSucSuVZ,        & 
& GosZcplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplSdcSdcVWmVWmaa,             & 
& cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWmVZaa,cplSucSucVWmVWmaa,           & 
& AmpVertexIRosSdToSuVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,        & 
& cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFuVWmL,     & 
& cplcFdFuVWmR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,             & 
& cplhhcVWmVWm,GZcplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,     & 
& ZcplSucSdVWm,cplSucSuVZ,GZcplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,         & 
& cplSdcSdcVWmVWmaa,cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWmVZaa,           & 
& cplSucSucVWmVWmaa,AmpVertexIRosSdToSuVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplcFdChaSuL,             & 
& cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,       & 
& cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuGluSuL,       & 
& cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,GcplHpmSucSd,             & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,         & 
& GcplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplSdcSdcVWmVWmaa,cplSucSdVGVWmLamct3ct2ct1,& 
& cplSucSdVPVWmaa,cplSucSdVWmVZaa,cplSucSucVWmVWmaa,AmpVertexIRosSdToSuVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SdToSuVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,        & 
& cplChaFucSdR,cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFuVWmL,     & 
& cplcFdFuVWmR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,             & 
& cplhhcVWmVWm,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,       & 
& cplSucSdVWm,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,            & 
& cplSdcSdcVWmVWmaa,cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWmVZaa,           & 
& cplSucSucVWmVWmaa,AmpVertexIRosSdToSuVWm)

 End if 
 End if 
AmpVertexSdToSuVWm = AmpVertexSdToSuVWm -  AmpVertexIRdrSdToSuVWm! +  AmpVertexIRosSdToSuVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSdToSuVWm=0._dp 
AmpVertexZSdToSuVWm=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSuVWm(:,gt2,:) = AmpWaveZSdToSuVWm(:,gt2,:)+ZRUZDc(gt2,gt1)*AmpWaveSdToSuVWm(:,gt1,:) 
AmpVertexZSdToSuVWm(:,gt2,:)= AmpVertexZSdToSuVWm(:,gt2,:) + ZRUZDc(gt2,gt1)*AmpVertexSdToSuVWm(:,gt1,:) 
 End Do 
End Do 
AmpWaveSdToSuVWm=AmpWaveZSdToSuVWm 
AmpVertexSdToSuVWm= AmpVertexZSdToSuVWm
! Final State 1 
AmpWaveZSdToSuVWm=0._dp 
AmpVertexZSdToSuVWm=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSdToSuVWm(:,:,gt2) = AmpWaveZSdToSuVWm(:,:,gt2)+ZRUZU(gt2,gt1)*AmpWaveSdToSuVWm(:,:,gt1) 
AmpVertexZSdToSuVWm(:,:,gt2)= AmpVertexZSdToSuVWm(:,:,gt2)+ZRUZU(gt2,gt1)*AmpVertexSdToSuVWm(:,:,gt1) 
 End Do 
End Do 
AmpWaveSdToSuVWm=AmpWaveZSdToSuVWm 
AmpVertexSdToSuVWm= AmpVertexZSdToSuVWm
End if
If (ShiftIRdiv) Then 
AmpVertexSdToSuVWm = AmpVertexSdToSuVWm  +  AmpVertexIRosSdToSuVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Su VWm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSdToSuVWm = AmpTreeSdToSuVWm 
 AmpSum2SdToSuVWm = AmpTreeSdToSuVWm + 2._dp*AmpWaveSdToSuVWm + 2._dp*AmpVertexSdToSuVWm  
Else 
 AmpSumSdToSuVWm = AmpTreeSdToSuVWm + AmpWaveSdToSuVWm + AmpVertexSdToSuVWm
 AmpSum2SdToSuVWm = AmpTreeSdToSuVWm + AmpWaveSdToSuVWm + AmpVertexSdToSuVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSuVWm = AmpTreeSdToSuVWm
 AmpSum2SdToSuVWm = AmpTreeSdToSuVWm 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSu(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2SdToSuVWm = AmpTreeSdToSuVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSuOS(gt2),MVWmOS,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSu(gt2),MVWm,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSdToSuVWm(gt1, gt2) 
  AmpSum2SdToSuVWm = 2._dp*AmpWaveSdToSuVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSuOS(gt2),MVWmOS,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSu(gt2),MVWm,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSdToSuVWm(gt1, gt2) 
  AmpSum2SdToSuVWm = 2._dp*AmpVertexSdToSuVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSuOS(gt2),MVWmOS,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSu(gt2),MVWm,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSdToSuVWm(gt1, gt2) 
  AmpSum2SdToSuVWm = AmpTreeSdToSuVWm + 2._dp*AmpWaveSdToSuVWm + 2._dp*AmpVertexSdToSuVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSuOS(gt2),MVWmOS,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSu(gt2),MVWm,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSdToSuVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2SdToSuVWm = AmpTreeSdToSuVWm
  Call SquareAmp_StoSV(MSdOS(gt1),MSuOS(gt2),MVWmOS,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
  AmpSqTreeSdToSuVWm(gt1, gt2) = AmpSqSdToSuVWm(gt1, gt2)  
  AmpSum2SdToSuVWm = + 2._dp*AmpWaveSdToSuVWm + 2._dp*AmpVertexSdToSuVWm
  Call SquareAmp_StoSV(MSdOS(gt1),MSuOS(gt2),MVWmOS,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
  AmpSqSdToSuVWm(gt1, gt2) = AmpSqSdToSuVWm(gt1, gt2) + AmpSqTreeSdToSuVWm(gt1, gt2)  
Else  
  AmpSum2SdToSuVWm = AmpTreeSdToSuVWm
  Call SquareAmp_StoSV(MSd(gt1),MSu(gt2),MVWm,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
  AmpSqTreeSdToSuVWm(gt1, gt2) = AmpSqSdToSuVWm(gt1, gt2)  
  AmpSum2SdToSuVWm = + 2._dp*AmpWaveSdToSuVWm + 2._dp*AmpVertexSdToSuVWm
  Call SquareAmp_StoSV(MSd(gt1),MSu(gt2),MVWm,AmpSumSdToSuVWm(:,gt1, gt2),AmpSum2SdToSuVWm(:,gt1, gt2),AmpSqSdToSuVWm(gt1, gt2)) 
  AmpSqSdToSuVWm(gt1, gt2) = AmpSqSdToSuVWm(gt1, gt2) + AmpSqTreeSdToSuVWm(gt1, gt2)  
End if  
Else  
  AmpSqSdToSuVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSuVWm(gt1, gt2).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MSuOS(gt2),MVWmOS,helfactor*AmpSqSdToSuVWm(gt1, gt2))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MSu(gt2),MVWm,helfactor*AmpSqSdToSuVWm(gt1, gt2))
End if 
If ((Abs(MRPSdToSuVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSdToSuVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSdToSuVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSdToSuVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPSdToSuVWm(gt1, gt2) + MRGSdToSuVWm(gt1, gt2)) 
  gP1LSd(gt1,i4) = gP1LSd(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPSdToSuVWm(gt1, gt2) + MRGSdToSuVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSd(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
End If 
!---------------- 
! Sd VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_SdToSdVG(cplSdcSdVG,ctcplSdcSdVG,MSdOS,MSd2OS,              & 
& MVG,MVG2,ZfSd,ZfVG,AmpWaveSdToSdVG)

 Else 
Call Amplitude_WAVE_NMSSM_SdToSdVG(cplSdcSdVG,ctcplSdcSdVG,MSdOS,MSd2OS,              & 
& MVG,MVG2,ZfSd,ZfVG,AmpWaveSdToSdVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_SdToSdVG(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSdcSd,       & 
& cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,            & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,             & 
& cplSdcSucVWm,cplSucSuVG,cplSucSdVWm,cplVGVGVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVGVZLamct3ct2ct1,& 
& cplSdcSucVWmVGLamct4ct2ct1,cplSucSdVGVWmLamct3ct2ct1,AmpVertexSdToSdVG)

 Else 
Call Amplitude_VERTEX_NMSSM_SdToSdVG(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSdcSd,       & 
& cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,            & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,             & 
& cplSdcSucVWm,cplSucSuVG,cplSucSdVWm,cplVGVGVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVGVZLamct3ct2ct1,& 
& cplSdcSucVWmVGLamct4ct2ct1,cplSucSdVGVWmLamct3ct2ct1,AmpVertexSdToSdVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSdVG(cplSdcSdVG,ctcplSdcSdVG,MSd,MSd2,MVG,              & 
& MVG2,ZfSd,ZfVG,AmpWaveSdToSdVG)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSdVG(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,           & 
& cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,            & 
& cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,    & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSdVWm,cplVGVGVG,              & 
& cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,   & 
& cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVGVZLamct3ct2ct1,cplSdcSucVWmVGLamct4ct2ct1,          & 
& cplSucSdVGVWmLamct3ct2ct1,AmpVertexSdToSdVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Sd VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSdVG = 0._dp 
 AmpSum2SdToSdVG = 0._dp  
Else 
 AmpSumSdToSdVG = AmpVertexSdToSdVG + AmpWaveSdToSdVG
 AmpSum2SdToSdVG = AmpVertexSdToSdVG + AmpWaveSdToSdVG 
End If 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSd(gt2))+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),0._dp,AmpSumSdToSdVG(:,gt1, gt2),AmpSum2SdToSdVG(:,gt1, gt2),AmpSqSdToSdVG(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVG,AmpSumSdToSdVG(:,gt1, gt2),AmpSum2SdToSdVG(:,gt1, gt2),AmpSqSdToSdVG(gt1, gt2)) 
End if  
Else  
  AmpSqSdToSdVG(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSdVG(gt1, gt2).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 4._dp/3._dp*GammaTPS(MSdOS(gt1),MSdOS(gt2),0._dp,helfactor*AmpSqSdToSdVG(gt1, gt2))
Else 
  gP1LSd(gt1,i4) = 4._dp/3._dp*GammaTPS(MSd(gt1),MSd(gt2),MVG,helfactor*AmpSqSdToSdVG(gt1, gt2))
End if 
If ((Abs(MRPSdToSdVG(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdVG(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
!---------------- 
! Sd VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_SdToSdVP(cplSdcSdVP,cplSdcSdVZ,ctcplSdcSdVP,ctcplSdcSdVZ,   & 
& MSdOS,MSd2OS,MVP,MVP2,ZfSd,ZfVP,ZfVZVP,AmpWaveSdToSdVP)

 Else 
Call Amplitude_WAVE_NMSSM_SdToSdVP(cplSdcSdVP,cplSdcSdVZ,ctcplSdcSdVP,ctcplSdcSdVZ,   & 
& MSdOS,MSd2OS,MVP,MVP2,ZfSd,ZfVP,ZfVZVP,AmpWaveSdToSdVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_SdToSdVP(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSdcSd,       & 
& cplChaFucSdL,cplChaFucSdR,cplcChaChaVPL,cplcChaChaVPR,cplChiFdcSdL,cplChiFdcSdR,       & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVPL,cplcFdFdVPR,           & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,              & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVP,cplSucSdVWm,cplcHpmVPVWm,           & 
& cplcVWmVPVWm,cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVPVPaa,cplSdcSdVPVZaa,cplSdcSucVWmVPaa,  & 
& cplSucSdVPVWmaa,AmpVertexSdToSdVP)

 Else 
Call Amplitude_VERTEX_NMSSM_SdToSdVP(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSdcSd,       & 
& cplChaFucSdL,cplChaFucSdR,cplcChaChaVPL,cplcChaChaVPR,cplChiFdcSdL,cplChiFdcSdR,       & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVPL,cplcFdFdVPR,           & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,              & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVP,cplSucSdVWm,cplcHpmVPVWm,           & 
& cplcVWmVPVWm,cplSdcSdVGVPLamct3ct2ct1,cplSdcSdVPVPaa,cplSdcSdVPVZaa,cplSdcSucVWmVPaa,  & 
& cplSucSdVPVWmaa,AmpVertexSdToSdVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SdToSdVP(cplSdcSdVP,cplSdcSdVZ,ctcplSdcSdVP,ctcplSdcSdVZ,   & 
& MSd,MSd2,MVP,MVP2,ZfSd,ZfVP,ZfVZVP,AmpWaveSdToSdVP)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SdToSdVP(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplcChaChaVPL,          & 
& cplcChaChaVPR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,        & 
& cplGluFdcSdR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFuVPL,cplcFuFuVPR,cplcFdGluSdL,             & 
& cplcFdGluSdR,cplhhSdcSd,cplHpmSucSd,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVP,cplSucSdVWm,cplcHpmVPVWm,cplcVWmVPVWm,cplSdcSdVGVPLamct3ct2ct1,             & 
& cplSdcSdVPVPaa,cplSdcSdVPVZaa,cplSdcSucVWmVPaa,cplSucSdVPVWmaa,AmpVertexSdToSdVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Sd->Sd VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumSdToSdVP = 0._dp 
 AmpSum2SdToSdVP = 0._dp  
Else 
 AmpSumSdToSdVP = AmpVertexSdToSdVP + AmpWaveSdToSdVP
 AmpSum2SdToSdVP = AmpVertexSdToSdVP + AmpWaveSdToSdVP 
End If 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSdOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MSd(gt1)).gt.(Abs(MSd(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSdOS(gt1),MSdOS(gt2),0._dp,AmpSumSdToSdVP(:,gt1, gt2),AmpSum2SdToSdVP(:,gt1, gt2),AmpSqSdToSdVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSd(gt1),MSd(gt2),MVP,AmpSumSdToSdVP(:,gt1, gt2),AmpSum2SdToSdVP(:,gt1, gt2),AmpSqSdToSdVP(gt1, gt2)) 
End if  
Else  
  AmpSqSdToSdVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSdToSdVP(gt1, gt2).eq.0._dp) Then 
  gP1LSd(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSdOS(gt1),MSdOS(gt2),0._dp,helfactor*AmpSqSdToSdVP(gt1, gt2))
Else 
  gP1LSd(gt1,i4) = 1._dp*GammaTPS(MSd(gt1),MSd(gt2),MVP,helfactor*AmpSqSdToSdVP(gt1, gt2))
End if 
If ((Abs(MRPSdToSdVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSdToSdVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSd(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
End Subroutine OneLoopDecay_Sd

End Module Wrapper_OneLoopDecay_Sd_NMSSM
