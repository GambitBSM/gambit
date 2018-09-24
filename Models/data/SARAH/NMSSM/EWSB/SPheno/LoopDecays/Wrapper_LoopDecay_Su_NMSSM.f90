! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:27 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Su_NMSSM
Use Model_Data_NMSSM 
Use Kinematics 
Use OneLoopDecay_Su_NMSSM 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Su(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,              & 
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
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhAhSucSuaa,cplAhcHpmVWm,cplAhhhhh,               & 
& cplAhhhSucSuaa,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,   & 
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
& cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhhhSucSuaa,cplhhHpmcHpm,          & 
& cplhhHpmcVWm,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplhhSdcSd,cplhhSecSe,cplhhSucSu,        & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplHpmSucSd,cplSdcHpmcSu,cplSdcSdcVWmVWmaa,        & 
& cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSdcSucVWmVGLamct4ct2ct1,              & 
& cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSecSuaa, & 
& cplSecHpmcSv,cplSeSucSecSuaa,cplSucSdVGVWmLamct3ct2ct1,cplSucSdVPVWmaa,cplSucSdVWm,    & 
& cplSucSdVWmVZaa,cplSucSucVWmVWmaa,cplSucSuVG,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSucSuVGVPLamct3ct2ct1,cplSucSuVGVZLamct3ct2ct1,& 
& cplSucSuVP,cplSucSuVPVPaa,cplSucSuVPVZaa,cplSucSuVZ,cplSucSuVZVZaa,cplSuSucSucSuabab,  & 
& cplSuSucSucSuabba,cplSuSvcSucSvaa,cplVGVGVG,ctcplAhSucSu,ctcplcChaFdcSuL,              & 
& ctcplcChaFdcSuR,ctcplChiFucSuL,ctcplChiFucSuR,ctcplGluFucSuL,ctcplGluFucSuR,           & 
& ctcplhhSucSu,ctcplSdcHpmcSu,ctcplSdcSucVWm,ctcplSucSuVG,ctcplSucSuVP,ctcplSucSuVZ,     & 
& GcplcHpmVPVWm,GcplHpmcVWmVP,GcplSdcHpmcSu,GosZcplcHpmVPVWm,GosZcplHpmcVWmVP,           & 
& GosZcplSdcHpmcSu,GZcplcHpmVPVWm,GZcplHpmcVWmVP,GZcplSdcHpmcSu,ZcplAhSucSu,             & 
& ZcplcChaFdcSuL,ZcplcChaFdcSuR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplGluFucSuL,               & 
& ZcplGluFucSuR,ZcplhhSucSu,ZcplSdcHpmcSu,ZcplSdcSucVWm,ZcplSucSuVZ,ZRUZD,               & 
& ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,            & 
& ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LSu)

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

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhAhSucSuaa(3,3,6,6),cplAhcHpmVWm(3,2),          & 
& cplAhhhhh(3,3,3),cplAhhhSucSuaa(3,3,6,6),cplAhhhVZ(3,3),cplAhHpmcHpm(3,2,2),           & 
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
& cplhhhhhh(3,3,3),cplhhhhSucSuaa(3,3,6,6),cplhhHpmcHpm(3,2,2),cplhhHpmcVWm(3,2),        & 
& cplhhHpmSucSdaa(3,2,6,6),cplhhSdcHpmcSuaa(3,6,2,6),cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),& 
& cplhhSucSu(3,6,6),cplhhSvcSv(3,3,3),cplhhVZVZ(3),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),  & 
& cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplHpmSdcHpmcSdaa(2,6,2,6),cplHpmSucHpmcSuaa(2,6,2,6), & 
& cplHpmSucSd(2,6,6),cplSdcHpmcSu(6,2,6),cplSdcSdcVWmVWmaa(6,6),cplSdcSdVG(6,6),         & 
& cplSdcSdVP(6,6),cplSdcSdVZ(6,6),cplSdcSucVWm(6,6),cplSdcSucVWmVGLamct4ct2ct1(6,6),     & 
& cplSdcSucVWmVPaa(6,6),cplSdcSucVWmVZaa(6,6),cplSdSucSdcSuabab(6,6,6,6),cplSdSucSdcSuabba(6,6,6,6),& 
& cplSdSvcSecSuaa(6,3,6,6),cplSecHpmcSv(6,2,3),cplSeSucSecSuaa(6,6,6,6),cplSucSdVGVWmLamct3ct2ct1(6,6),& 
& cplSucSdVPVWmaa(6,6),cplSucSdVWm(6,6),cplSucSdVWmVZaa(6,6),cplSucSucVWmVWmaa(6,6),     & 
& cplSucSuVG(6,6),cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1(6,6),cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1(6,6),& 
& cplSucSuVGVPLamct3ct2ct1(6,6),cplSucSuVGVZLamct3ct2ct1(6,6),cplSucSuVP(6,6),           & 
& cplSucSuVPVPaa(6,6),cplSucSuVPVZaa(6,6),cplSucSuVZ(6,6),cplSucSuVZVZaa(6,6),           & 
& cplSuSucSucSuabab(6,6,6,6),cplSuSucSucSuabba(6,6,6,6),cplSuSvcSucSvaa(6,3,6,3),        & 
& cplVGVGVG,ctcplAhSucSu(3,6,6),ctcplcChaFdcSuL(2,3,6),ctcplcChaFdcSuR(2,3,6)

Complex(dp),Intent(in) :: ctcplChiFucSuL(5,3,6),ctcplChiFucSuR(5,3,6),ctcplGluFucSuL(3,6),ctcplGluFucSuR(3,6),   & 
& ctcplhhSucSu(3,6,6),ctcplSdcHpmcSu(6,2,6),ctcplSdcSucVWm(6,6),ctcplSucSuVG(6,6),       & 
& ctcplSucSuVP(6,6),ctcplSucSuVZ(6,6),GcplcHpmVPVWm(2),GcplHpmcVWmVP(2),GcplSdcHpmcSu(6,2,6),& 
& GosZcplcHpmVPVWm(2),GosZcplHpmcVWmVP(2),GosZcplSdcHpmcSu(6,2,6),GZcplcHpmVPVWm(2),     & 
& GZcplHpmcVWmVP(2),GZcplSdcHpmcSu(6,2,6),ZcplAhSucSu(3,6,6),ZcplcChaFdcSuL(2,3,6),      & 
& ZcplcChaFdcSuR(2,3,6),ZcplChiFucSuL(5,3,6),ZcplChiFucSuR(5,3,6),ZcplGluFucSuL(3,6),    & 
& ZcplGluFucSuR(3,6),ZcplhhSucSu(3,6,6),ZcplSdcHpmcSu(6,2,6),ZcplSdcSucVWm(6,6),         & 
& ZcplSucSuVZ(6,6)

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
Real(dp), Intent(out) :: gP1LSu(6,84) 
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
Real(dp) :: MRPSuToSuAh(6,6,3),MRGSuToSuAh(6,6,3), MRPZSuToSuAh(6,6,3),MRGZSuToSuAh(6,6,3) 
Real(dp) :: MVPSuToSuAh(6,6,3) 
Real(dp) :: RMsqTreeSuToSuAh(6,6,3),RMsqWaveSuToSuAh(6,6,3),RMsqVertexSuToSuAh(6,6,3) 
Complex(dp) :: AmpTreeSuToSuAh(6,6,3),AmpWaveSuToSuAh(6,6,3)=(0._dp,0._dp),AmpVertexSuToSuAh(6,6,3)& 
 & ,AmpVertexIRosSuToSuAh(6,6,3),AmpVertexIRdrSuToSuAh(6,6,3), AmpSumSuToSuAh(6,6,3), AmpSum2SuToSuAh(6,6,3) 
Complex(dp) :: AmpTreeZSuToSuAh(6,6,3),AmpWaveZSuToSuAh(6,6,3),AmpVertexZSuToSuAh(6,6,3) 
Real(dp) :: AmpSqSuToSuAh(6,6,3),  AmpSqTreeSuToSuAh(6,6,3) 
Real(dp) :: MRPSuToFuChi(6,3,5),MRGSuToFuChi(6,3,5), MRPZSuToFuChi(6,3,5),MRGZSuToFuChi(6,3,5) 
Real(dp) :: MVPSuToFuChi(6,3,5) 
Real(dp) :: RMsqTreeSuToFuChi(6,3,5),RMsqWaveSuToFuChi(6,3,5),RMsqVertexSuToFuChi(6,3,5) 
Complex(dp) :: AmpTreeSuToFuChi(2,6,3,5),AmpWaveSuToFuChi(2,6,3,5)=(0._dp,0._dp),AmpVertexSuToFuChi(2,6,3,5)& 
 & ,AmpVertexIRosSuToFuChi(2,6,3,5),AmpVertexIRdrSuToFuChi(2,6,3,5), AmpSumSuToFuChi(2,6,3,5), AmpSum2SuToFuChi(2,6,3,5) 
Complex(dp) :: AmpTreeZSuToFuChi(2,6,3,5),AmpWaveZSuToFuChi(2,6,3,5),AmpVertexZSuToFuChi(2,6,3,5) 
Real(dp) :: AmpSqSuToFuChi(6,3,5),  AmpSqTreeSuToFuChi(6,3,5) 
Real(dp) :: MRPSuTocChaFd(6,2,3),MRGSuTocChaFd(6,2,3), MRPZSuTocChaFd(6,2,3),MRGZSuTocChaFd(6,2,3) 
Real(dp) :: MVPSuTocChaFd(6,2,3) 
Real(dp) :: RMsqTreeSuTocChaFd(6,2,3),RMsqWaveSuTocChaFd(6,2,3),RMsqVertexSuTocChaFd(6,2,3) 
Complex(dp) :: AmpTreeSuTocChaFd(2,6,2,3),AmpWaveSuTocChaFd(2,6,2,3)=(0._dp,0._dp),AmpVertexSuTocChaFd(2,6,2,3)& 
 & ,AmpVertexIRosSuTocChaFd(2,6,2,3),AmpVertexIRdrSuTocChaFd(2,6,2,3), AmpSumSuTocChaFd(2,6,2,3), AmpSum2SuTocChaFd(2,6,2,3) 
Complex(dp) :: AmpTreeZSuTocChaFd(2,6,2,3),AmpWaveZSuTocChaFd(2,6,2,3),AmpVertexZSuTocChaFd(2,6,2,3) 
Real(dp) :: AmpSqSuTocChaFd(6,2,3),  AmpSqTreeSuTocChaFd(6,2,3) 
Real(dp) :: MRPSuToGluFu(6,3),MRGSuToGluFu(6,3), MRPZSuToGluFu(6,3),MRGZSuToGluFu(6,3) 
Real(dp) :: MVPSuToGluFu(6,3) 
Real(dp) :: RMsqTreeSuToGluFu(6,3),RMsqWaveSuToGluFu(6,3),RMsqVertexSuToGluFu(6,3) 
Complex(dp) :: AmpTreeSuToGluFu(2,6,3),AmpWaveSuToGluFu(2,6,3)=(0._dp,0._dp),AmpVertexSuToGluFu(2,6,3)& 
 & ,AmpVertexIRosSuToGluFu(2,6,3),AmpVertexIRdrSuToGluFu(2,6,3), AmpSumSuToGluFu(2,6,3), AmpSum2SuToGluFu(2,6,3) 
Complex(dp) :: AmpTreeZSuToGluFu(2,6,3),AmpWaveZSuToGluFu(2,6,3),AmpVertexZSuToGluFu(2,6,3) 
Real(dp) :: AmpSqSuToGluFu(6,3),  AmpSqTreeSuToGluFu(6,3) 
Real(dp) :: MRPSuToSuhh(6,6,3),MRGSuToSuhh(6,6,3), MRPZSuToSuhh(6,6,3),MRGZSuToSuhh(6,6,3) 
Real(dp) :: MVPSuToSuhh(6,6,3) 
Real(dp) :: RMsqTreeSuToSuhh(6,6,3),RMsqWaveSuToSuhh(6,6,3),RMsqVertexSuToSuhh(6,6,3) 
Complex(dp) :: AmpTreeSuToSuhh(6,6,3),AmpWaveSuToSuhh(6,6,3)=(0._dp,0._dp),AmpVertexSuToSuhh(6,6,3)& 
 & ,AmpVertexIRosSuToSuhh(6,6,3),AmpVertexIRdrSuToSuhh(6,6,3), AmpSumSuToSuhh(6,6,3), AmpSum2SuToSuhh(6,6,3) 
Complex(dp) :: AmpTreeZSuToSuhh(6,6,3),AmpWaveZSuToSuhh(6,6,3),AmpVertexZSuToSuhh(6,6,3) 
Real(dp) :: AmpSqSuToSuhh(6,6,3),  AmpSqTreeSuToSuhh(6,6,3) 
Real(dp) :: MRPSuTocHpmSd(6,2,6),MRGSuTocHpmSd(6,2,6), MRPZSuTocHpmSd(6,2,6),MRGZSuTocHpmSd(6,2,6) 
Real(dp) :: MVPSuTocHpmSd(6,2,6) 
Real(dp) :: RMsqTreeSuTocHpmSd(6,2,6),RMsqWaveSuTocHpmSd(6,2,6),RMsqVertexSuTocHpmSd(6,2,6) 
Complex(dp) :: AmpTreeSuTocHpmSd(6,2,6),AmpWaveSuTocHpmSd(6,2,6)=(0._dp,0._dp),AmpVertexSuTocHpmSd(6,2,6)& 
 & ,AmpVertexIRosSuTocHpmSd(6,2,6),AmpVertexIRdrSuTocHpmSd(6,2,6), AmpSumSuTocHpmSd(6,2,6), AmpSum2SuTocHpmSd(6,2,6) 
Complex(dp) :: AmpTreeZSuTocHpmSd(6,2,6),AmpWaveZSuTocHpmSd(6,2,6),AmpVertexZSuTocHpmSd(6,2,6) 
Real(dp) :: AmpSqSuTocHpmSd(6,2,6),  AmpSqTreeSuTocHpmSd(6,2,6) 
Real(dp) :: MRPSuToSdcVWm(6,6),MRGSuToSdcVWm(6,6), MRPZSuToSdcVWm(6,6),MRGZSuToSdcVWm(6,6) 
Real(dp) :: MVPSuToSdcVWm(6,6) 
Real(dp) :: RMsqTreeSuToSdcVWm(6,6),RMsqWaveSuToSdcVWm(6,6),RMsqVertexSuToSdcVWm(6,6) 
Complex(dp) :: AmpTreeSuToSdcVWm(2,6,6),AmpWaveSuToSdcVWm(2,6,6)=(0._dp,0._dp),AmpVertexSuToSdcVWm(2,6,6)& 
 & ,AmpVertexIRosSuToSdcVWm(2,6,6),AmpVertexIRdrSuToSdcVWm(2,6,6), AmpSumSuToSdcVWm(2,6,6), AmpSum2SuToSdcVWm(2,6,6) 
Complex(dp) :: AmpTreeZSuToSdcVWm(2,6,6),AmpWaveZSuToSdcVWm(2,6,6),AmpVertexZSuToSdcVWm(2,6,6) 
Real(dp) :: AmpSqSuToSdcVWm(6,6),  AmpSqTreeSuToSdcVWm(6,6) 
Real(dp) :: MRPSuToSuVZ(6,6),MRGSuToSuVZ(6,6), MRPZSuToSuVZ(6,6),MRGZSuToSuVZ(6,6) 
Real(dp) :: MVPSuToSuVZ(6,6) 
Real(dp) :: RMsqTreeSuToSuVZ(6,6),RMsqWaveSuToSuVZ(6,6),RMsqVertexSuToSuVZ(6,6) 
Complex(dp) :: AmpTreeSuToSuVZ(2,6,6),AmpWaveSuToSuVZ(2,6,6)=(0._dp,0._dp),AmpVertexSuToSuVZ(2,6,6)& 
 & ,AmpVertexIRosSuToSuVZ(2,6,6),AmpVertexIRdrSuToSuVZ(2,6,6), AmpSumSuToSuVZ(2,6,6), AmpSum2SuToSuVZ(2,6,6) 
Complex(dp) :: AmpTreeZSuToSuVZ(2,6,6),AmpWaveZSuToSuVZ(2,6,6),AmpVertexZSuToSuVZ(2,6,6) 
Real(dp) :: AmpSqSuToSuVZ(6,6),  AmpSqTreeSuToSuVZ(6,6) 
Real(dp) :: MRPSuToSuVG(6,6),MRGSuToSuVG(6,6), MRPZSuToSuVG(6,6),MRGZSuToSuVG(6,6) 
Real(dp) :: MVPSuToSuVG(6,6) 
Real(dp) :: RMsqTreeSuToSuVG(6,6),RMsqWaveSuToSuVG(6,6),RMsqVertexSuToSuVG(6,6) 
Complex(dp) :: AmpTreeSuToSuVG(2,6,6),AmpWaveSuToSuVG(2,6,6)=(0._dp,0._dp),AmpVertexSuToSuVG(2,6,6)& 
 & ,AmpVertexIRosSuToSuVG(2,6,6),AmpVertexIRdrSuToSuVG(2,6,6), AmpSumSuToSuVG(2,6,6), AmpSum2SuToSuVG(2,6,6) 
Complex(dp) :: AmpTreeZSuToSuVG(2,6,6),AmpWaveZSuToSuVG(2,6,6),AmpVertexZSuToSuVG(2,6,6) 
Real(dp) :: AmpSqSuToSuVG(6,6),  AmpSqTreeSuToSuVG(6,6) 
Real(dp) :: MRPSuToSuVP(6,6),MRGSuToSuVP(6,6), MRPZSuToSuVP(6,6),MRGZSuToSuVP(6,6) 
Real(dp) :: MVPSuToSuVP(6,6) 
Real(dp) :: RMsqTreeSuToSuVP(6,6),RMsqWaveSuToSuVP(6,6),RMsqVertexSuToSuVP(6,6) 
Complex(dp) :: AmpTreeSuToSuVP(2,6,6),AmpWaveSuToSuVP(2,6,6)=(0._dp,0._dp),AmpVertexSuToSuVP(2,6,6)& 
 & ,AmpVertexIRosSuToSuVP(2,6,6),AmpVertexIRdrSuToSuVP(2,6,6), AmpSumSuToSuVP(2,6,6), AmpSum2SuToSuVP(2,6,6) 
Complex(dp) :: AmpTreeZSuToSuVP(2,6,6),AmpWaveZSuToSuVP(2,6,6),AmpVertexZSuToSuVP(2,6,6) 
Real(dp) :: AmpSqSuToSuVP(6,6),  AmpSqTreeSuToSuVP(6,6) 
Write(*,*) "Calculating one-loop decays of Su " 
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
! Su Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuToSuAh(cplAhSucSu,MAh,MSu,MAh2,MSu2,AmpTreeSuToSuAh)

  Else 
Call Amplitude_Tree_NMSSM_SuToSuAh(ZcplAhSucSu,MAh,MSu,MAh2,MSu2,AmpTreeSuToSuAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuToSuAh(MLambda,em,gs,cplAhSucSu,MAhOS,MSuOS,MRPSuToSuAh,      & 
& MRGSuToSuAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuToSuAh(MLambda,em,gs,ZcplAhSucSu,MAhOS,MSuOS,MRPSuToSuAh,     & 
& MRGSuToSuAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuToSuAh(MLambda,em,gs,cplAhSucSu,MAh,MSu,MRPSuToSuAh,          & 
& MRGSuToSuAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuToSuAh(MLambda,em,gs,ZcplAhSucSu,MAh,MSu,MRPSuToSuAh,         & 
& MRGSuToSuAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToSuAh(cplAhSucSu,ctcplAhSucSu,MAh,MAh2,MSu,              & 
& MSu2,ZfAh,ZfSu,AmpWaveSuToSuAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToSuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,              & 
& MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuGluSuL,       & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,              & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplAhHpmSucSdaa,       & 
& cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab, & 
& cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexSuToSuAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,            & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,            & 
& cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,   & 
& cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRdrSuToSuAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuAh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,             & 
& MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVG2,MVP2,           & 
& MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,           & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,ZcplAhSucSu,cplAhcHpmVWm,              & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuGluSuL,cplcFuGluSuR,       & 
& cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,    & 
& cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,             & 
& cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,  & 
& cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosSuToSuAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& ZcplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,          & 
& cplcFuChiSuL,cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,            & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,            & 
& cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,   & 
& cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosSuToSuAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuAh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,             & 
& MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVG2,MVP2,           & 
& MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,           & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuGluSuL,cplcFuGluSuR,       & 
& cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,    & 
& cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,             & 
& cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,  & 
& cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosSuToSuAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuAh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,            & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,            & 
& cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,   & 
& cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosSuToSuAh)

 End if 
 End if 
AmpVertexSuToSuAh = AmpVertexSuToSuAh -  AmpVertexIRdrSuToSuAh! +  AmpVertexIRosSuToSuAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuToSuAh=0._dp 
AmpVertexZSuToSuAh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSuAh(gt2,:,:) = AmpWaveZSuToSuAh(gt2,:,:)+ZRUZUc(gt2,gt1)*AmpWaveSuToSuAh(gt1,:,:) 
AmpVertexZSuToSuAh(gt2,:,:)= AmpVertexZSuToSuAh(gt2,:,:) + ZRUZUc(gt2,gt1)*AmpVertexSuToSuAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveSuToSuAh=AmpWaveZSuToSuAh 
AmpVertexSuToSuAh= AmpVertexZSuToSuAh
! Final State 1 
AmpWaveZSuToSuAh=0._dp 
AmpVertexZSuToSuAh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSuAh(:,gt2,:) = AmpWaveZSuToSuAh(:,gt2,:)+ZRUZU(gt2,gt1)*AmpWaveSuToSuAh(:,gt1,:) 
AmpVertexZSuToSuAh(:,gt2,:)= AmpVertexZSuToSuAh(:,gt2,:)+ZRUZU(gt2,gt1)*AmpVertexSuToSuAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveSuToSuAh=AmpWaveZSuToSuAh 
AmpVertexSuToSuAh= AmpVertexZSuToSuAh
! Final State 2 
AmpWaveZSuToSuAh=0._dp 
AmpVertexZSuToSuAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSuToSuAh(:,:,gt2) = AmpWaveZSuToSuAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveSuToSuAh(:,:,gt1) 
AmpVertexZSuToSuAh(:,:,gt2)= AmpVertexZSuToSuAh(:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexSuToSuAh(:,:,gt1) 
 End Do 
End Do 
AmpWaveSuToSuAh=AmpWaveZSuToSuAh 
AmpVertexSuToSuAh= AmpVertexZSuToSuAh
End if
If (ShiftIRdiv) Then 
AmpVertexSuToSuAh = AmpVertexSuToSuAh  +  AmpVertexIRosSuToSuAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Su Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuToSuAh = AmpTreeSuToSuAh 
 AmpSum2SuToSuAh = AmpTreeSuToSuAh + 2._dp*AmpWaveSuToSuAh + 2._dp*AmpVertexSuToSuAh  
Else 
 AmpSumSuToSuAh = AmpTreeSuToSuAh + AmpWaveSuToSuAh + AmpVertexSuToSuAh
 AmpSum2SuToSuAh = AmpTreeSuToSuAh + AmpWaveSuToSuAh + AmpVertexSuToSuAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToSuAh = AmpTreeSuToSuAh
 AmpSum2SuToSuAh = AmpTreeSuToSuAh 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
    Do gt3=2,3
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MSu(gt2))+Abs(MAh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SuToSuAh = AmpTreeSuToSuAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),MAh(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuToSuAh(gt1, gt2, gt3) 
  AmpSum2SuToSuAh = 2._dp*AmpWaveSuToSuAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),MAh(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuToSuAh(gt1, gt2, gt3) 
  AmpSum2SuToSuAh = 2._dp*AmpVertexSuToSuAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),MAh(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuToSuAh(gt1, gt2, gt3) 
  AmpSum2SuToSuAh = AmpTreeSuToSuAh + 2._dp*AmpWaveSuToSuAh + 2._dp*AmpVertexSuToSuAh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),MAh(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuToSuAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuToSuAh = AmpTreeSuToSuAh
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
  AmpSqTreeSuToSuAh(gt1, gt2, gt3) = AmpSqSuToSuAh(gt1, gt2, gt3)  
  AmpSum2SuToSuAh = + 2._dp*AmpWaveSuToSuAh + 2._dp*AmpVertexSuToSuAh
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
  AmpSqSuToSuAh(gt1, gt2, gt3) = AmpSqSuToSuAh(gt1, gt2, gt3) + AmpSqTreeSuToSuAh(gt1, gt2, gt3)  
Else  
  AmpSum2SuToSuAh = AmpTreeSuToSuAh
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),MAh(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
  AmpSqTreeSuToSuAh(gt1, gt2, gt3) = AmpSqSuToSuAh(gt1, gt2, gt3)  
  AmpSum2SuToSuAh = + 2._dp*AmpWaveSuToSuAh + 2._dp*AmpVertexSuToSuAh
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),MAh(gt3),AmpSumSuToSuAh(gt1, gt2, gt3),AmpSum2SuToSuAh(gt1, gt2, gt3),AmpSqSuToSuAh(gt1, gt2, gt3)) 
  AmpSqSuToSuAh(gt1, gt2, gt3) = AmpSqSuToSuAh(gt1, gt2, gt3) + AmpSqTreeSuToSuAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSuToSuAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuToSuAh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MSuOS(gt2),MAhOS(gt3),helfactor*AmpSqSuToSuAh(gt1, gt2, gt3))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MSu(gt2),MAh(gt3),helfactor*AmpSqSuToSuAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPSuToSuAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuToSuAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSuToSuAh(gt1, gt2, gt3) + MRGSuToSuAh(gt1, gt2, gt3)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSuToSuAh(gt1, gt2, gt3) + MRGSuToSuAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! Fu Chi
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuToFuChi(cplChiFucSuL,cplChiFucSuR,MChi,MFu,               & 
& MSu,MChi2,MFu2,MSu2,AmpTreeSuToFuChi)

  Else 
Call Amplitude_Tree_NMSSM_SuToFuChi(ZcplChiFucSuL,ZcplChiFucSuR,MChi,MFu,             & 
& MSu,MChi2,MFu2,MSu2,AmpTreeSuToFuChi)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuToFuChi(MLambda,em,gs,cplChiFucSuL,cplChiFucSuR,              & 
& MChiOS,MFuOS,MSuOS,MRPSuToFuChi,MRGSuToFuChi)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuToFuChi(MLambda,em,gs,ZcplChiFucSuL,ZcplChiFucSuR,            & 
& MChiOS,MFuOS,MSuOS,MRPSuToFuChi,MRGSuToFuChi)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuToFuChi(MLambda,em,gs,cplChiFucSuL,cplChiFucSuR,              & 
& MChi,MFu,MSu,MRPSuToFuChi,MRGSuToFuChi)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuToFuChi(MLambda,em,gs,ZcplChiFucSuL,ZcplChiFucSuR,            & 
& MChi,MFu,MSu,MRPSuToFuChi,MRGSuToFuChi)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToFuChi(cplChiFucSuL,cplChiFucSuR,ctcplChiFucSuL,         & 
& ctcplChiFucSuR,MChi,MChi2,MFu,MFu2,MSu,MSu2,ZfFUL,ZfFUR,ZfL0,ZfSu,AmpWaveSuToFuChi)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToFuChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,           & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,    & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,             & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexSuToFuChi)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuToFuChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,      & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,    & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,             & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRdrSuToFuChi)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToFuChi(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChiChacHpmL,           & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,ZcplChiFucSuL,        & 
& ZcplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,    & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,   & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,            & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,     & 
& AmpVertexIRosSuToFuChi)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToFuChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,      & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,ZcplChiFucSuL,ZcplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,   & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,    & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,             & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuToFuChi)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToFuChi(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChiChacHpmL,           & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,     & 
& cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,   & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,            & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,     & 
& AmpVertexIRosSuToFuChi)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToFuChi(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplcFuFuAhL,cplcFuFuAhR,      & 
& cplAhSucSu,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChaFucSdL,   & 
& cplChaFucSdR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,    & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,             & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuToFuChi)

 End if 
 End if 
AmpVertexSuToFuChi = AmpVertexSuToFuChi -  AmpVertexIRdrSuToFuChi! +  AmpVertexIRosSuToFuChi ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuToFuChi=0._dp 
AmpVertexZSuToFuChi=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToFuChi(:,gt2,:,:) = AmpWaveZSuToFuChi(:,gt2,:,:)+ZRUZUc(gt2,gt1)*AmpWaveSuToFuChi(:,gt1,:,:) 
AmpVertexZSuToFuChi(:,gt2,:,:)= AmpVertexZSuToFuChi(:,gt2,:,:) + ZRUZUc(gt2,gt1)*AmpVertexSuToFuChi(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveSuToFuChi=AmpWaveZSuToFuChi 
AmpVertexSuToFuChi= AmpVertexZSuToFuChi
! Final State 1 
AmpWaveZSuToFuChi=0._dp 
AmpVertexZSuToFuChi=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSuToFuChi(1,:,gt2,:) = AmpWaveZSuToFuChi(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpWaveSuToFuChi(1,:,gt1,:) 
AmpVertexZSuToFuChi(1,:,gt2,:)= AmpVertexZSuToFuChi(1,:,gt2,:)+ZRUZUL(gt2,gt1)*AmpVertexSuToFuChi(1,:,gt1,:) 
AmpWaveZSuToFuChi(2,:,gt2,:) = AmpWaveZSuToFuChi(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpWaveSuToFuChi(2,:,gt1,:) 
AmpVertexZSuToFuChi(2,:,gt2,:)= AmpVertexZSuToFuChi(2,:,gt2,:)+ZRUZURc(gt2,gt1)*AmpVertexSuToFuChi(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveSuToFuChi=AmpWaveZSuToFuChi 
AmpVertexSuToFuChi= AmpVertexZSuToFuChi
! Final State 2 
AmpWaveZSuToFuChi=0._dp 
AmpVertexZSuToFuChi=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZSuToFuChi(1,:,:,gt2) = AmpWaveZSuToFuChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveSuToFuChi(1,:,:,gt1) 
AmpVertexZSuToFuChi(1,:,:,gt2)= AmpVertexZSuToFuChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexSuToFuChi(1,:,:,gt1) 
AmpWaveZSuToFuChi(2,:,:,gt2) = AmpWaveZSuToFuChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveSuToFuChi(2,:,:,gt1) 
AmpVertexZSuToFuChi(2,:,:,gt2)= AmpVertexZSuToFuChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexSuToFuChi(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveSuToFuChi=AmpWaveZSuToFuChi 
AmpVertexSuToFuChi= AmpVertexZSuToFuChi
End if
If (ShiftIRdiv) Then 
AmpVertexSuToFuChi = AmpVertexSuToFuChi  +  AmpVertexIRosSuToFuChi
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Fu Chi -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuToFuChi = AmpTreeSuToFuChi 
 AmpSum2SuToFuChi = AmpTreeSuToFuChi + 2._dp*AmpWaveSuToFuChi + 2._dp*AmpVertexSuToFuChi  
Else 
 AmpSumSuToFuChi = AmpTreeSuToFuChi + AmpWaveSuToFuChi + AmpVertexSuToFuChi
 AmpSum2SuToFuChi = AmpTreeSuToFuChi + AmpWaveSuToFuChi + AmpVertexSuToFuChi 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToFuChi = AmpTreeSuToFuChi
 AmpSum2SuToFuChi = AmpTreeSuToFuChi 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,3
    Do gt3=1,5
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MFuOS(gt2))+Abs(MChiOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MFu(gt2))+Abs(MChi(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SuToFuChi = AmpTreeSuToFuChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MFu(gt2),MChi(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuToFuChi(gt1, gt2, gt3) 
  AmpSum2SuToFuChi = 2._dp*AmpWaveSuToFuChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MFu(gt2),MChi(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuToFuChi(gt1, gt2, gt3) 
  AmpSum2SuToFuChi = 2._dp*AmpVertexSuToFuChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MFu(gt2),MChi(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuToFuChi(gt1, gt2, gt3) 
  AmpSum2SuToFuChi = AmpTreeSuToFuChi + 2._dp*AmpWaveSuToFuChi + 2._dp*AmpVertexSuToFuChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MFu(gt2),MChi(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuToFuChi(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuToFuChi = AmpTreeSuToFuChi
  Call SquareAmp_StoFF(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
  AmpSqTreeSuToFuChi(gt1, gt2, gt3) = AmpSqSuToFuChi(gt1, gt2, gt3)  
  AmpSum2SuToFuChi = + 2._dp*AmpWaveSuToFuChi + 2._dp*AmpVertexSuToFuChi
  Call SquareAmp_StoFF(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
  AmpSqSuToFuChi(gt1, gt2, gt3) = AmpSqSuToFuChi(gt1, gt2, gt3) + AmpSqTreeSuToFuChi(gt1, gt2, gt3)  
Else  
  AmpSum2SuToFuChi = AmpTreeSuToFuChi
  Call SquareAmp_StoFF(MSu(gt1),MFu(gt2),MChi(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
  AmpSqTreeSuToFuChi(gt1, gt2, gt3) = AmpSqSuToFuChi(gt1, gt2, gt3)  
  AmpSum2SuToFuChi = + 2._dp*AmpWaveSuToFuChi + 2._dp*AmpVertexSuToFuChi
  Call SquareAmp_StoFF(MSu(gt1),MFu(gt2),MChi(gt3),AmpSumSuToFuChi(:,gt1, gt2, gt3),AmpSum2SuToFuChi(:,gt1, gt2, gt3),AmpSqSuToFuChi(gt1, gt2, gt3)) 
  AmpSqSuToFuChi(gt1, gt2, gt3) = AmpSqSuToFuChi(gt1, gt2, gt3) + AmpSqTreeSuToFuChi(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSuToFuChi(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqSuToFuChi(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MFuOS(gt2),MChiOS(gt3),helfactor*AmpSqSuToFuChi(gt1, gt2, gt3))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MFu(gt2),MChi(gt3),helfactor*AmpSqSuToFuChi(gt1, gt2, gt3))
End if 
If ((Abs(MRPSuToFuChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToFuChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuToFuChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToFuChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSuToFuChi(gt1, gt2, gt3) + MRGSuToFuChi(gt1, gt2, gt3)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSuToFuChi(gt1, gt2, gt3) + MRGSuToFuChi(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! bar(Cha) Fd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuTocChaFd(cplcChaFdcSuL,cplcChaFdcSuR,MCha,MFd,            & 
& MSu,MCha2,MFd2,MSu2,AmpTreeSuTocChaFd)

  Else 
Call Amplitude_Tree_NMSSM_SuTocChaFd(ZcplcChaFdcSuL,ZcplcChaFdcSuR,MCha,              & 
& MFd,MSu,MCha2,MFd2,MSu2,AmpTreeSuTocChaFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuTocChaFd(MLambda,em,gs,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& MChaOS,MFdOS,MSuOS,MRPSuTocChaFd,MRGSuTocChaFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuTocChaFd(MLambda,em,gs,ZcplcChaFdcSuL,ZcplcChaFdcSuR,         & 
& MChaOS,MFdOS,MSuOS,MRPSuTocChaFd,MRGSuTocChaFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuTocChaFd(MLambda,em,gs,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& MCha,MFd,MSu,MRPSuTocChaFd,MRGSuTocChaFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuTocChaFd(MLambda,em,gs,ZcplcChaFdcSuL,ZcplcChaFdcSuR,         & 
& MCha,MFd,MSu,MRPSuTocChaFd,MRGSuTocChaFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuTocChaFd(cplcChaFdcSuL,cplcChaFdcSuR,ctcplcChaFdcSuL,     & 
& ctcplcChaFdcSuR,MCha,MCha2,MFd,MFd2,MSu,MSu2,ZfFDL,ZfFDR,ZfLm,ZfLp,ZfSu,               & 
& AmpWaveSuTocChaFd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuTocChaFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,         & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplcChacFuSdL,cplcChacFuSdR,        & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexSuTocChaFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuTocChaFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplcChacFuSdL,cplcChacFuSdR,        & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRdrSuTocChaFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocChaFd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplAhSucSu,cplcChaChahhL,          & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,    & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,ZcplcChaFdcSuL,            & 
& ZcplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,   & 
& cplGluFucSuR,cplhhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,         & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuTocChaFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocChaFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,ZcplcChaFdcSuL,ZcplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,   & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplcChacFuSdL,cplcChacFuSdR,        & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuTocChaFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocChaFd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplAhSucSu,cplcChaChahhL,          & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiFdcSdL,    & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,    & 
& cplGluFucSuR,cplhhSucSu,cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,         & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuTocChaFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocChaFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,      & 
& cplcChaChaVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,    & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplhhSucSu,cplcChacFuSdL,cplcChacFuSdR,        & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuTocChaFd)

 End if 
 End if 
AmpVertexSuTocChaFd = AmpVertexSuTocChaFd -  AmpVertexIRdrSuTocChaFd! +  AmpVertexIRosSuTocChaFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuTocChaFd=0._dp 
AmpVertexZSuTocChaFd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuTocChaFd(:,gt2,:,:) = AmpWaveZSuTocChaFd(:,gt2,:,:)+ZRUZUc(gt2,gt1)*AmpWaveSuTocChaFd(:,gt1,:,:) 
AmpVertexZSuTocChaFd(:,gt2,:,:)= AmpVertexZSuTocChaFd(:,gt2,:,:) + ZRUZUc(gt2,gt1)*AmpVertexSuTocChaFd(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveSuTocChaFd=AmpWaveZSuTocChaFd 
AmpVertexSuTocChaFd= AmpVertexZSuTocChaFd
! Final State 1 
AmpWaveZSuTocChaFd=0._dp 
AmpVertexZSuTocChaFd=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZSuTocChaFd(1,:,gt2,:) = AmpWaveZSuTocChaFd(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpWaveSuTocChaFd(1,:,gt1,:) 
AmpVertexZSuTocChaFd(1,:,gt2,:)= AmpVertexZSuTocChaFd(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpVertexSuTocChaFd(1,:,gt1,:) 
AmpWaveZSuTocChaFd(2,:,gt2,:) = AmpWaveZSuTocChaFd(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpWaveSuTocChaFd(2,:,gt1,:) 
AmpVertexZSuTocChaFd(2,:,gt2,:)= AmpVertexZSuTocChaFd(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpVertexSuTocChaFd(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveSuTocChaFd=AmpWaveZSuTocChaFd 
AmpVertexSuTocChaFd= AmpVertexZSuTocChaFd
! Final State 2 
AmpWaveZSuTocChaFd=0._dp 
AmpVertexZSuTocChaFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSuTocChaFd(1,:,:,gt2) = AmpWaveZSuTocChaFd(1,:,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveSuTocChaFd(1,:,:,gt1) 
AmpVertexZSuTocChaFd(1,:,:,gt2)= AmpVertexZSuTocChaFd(1,:,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexSuTocChaFd(1,:,:,gt1) 
AmpWaveZSuTocChaFd(2,:,:,gt2) = AmpWaveZSuTocChaFd(2,:,:,gt2)+ZRUZDR(gt2,gt1)*AmpWaveSuTocChaFd(2,:,:,gt1) 
AmpVertexZSuTocChaFd(2,:,:,gt2)= AmpVertexZSuTocChaFd(2,:,:,gt2)+ZRUZDR(gt2,gt1)*AmpVertexSuTocChaFd(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveSuTocChaFd=AmpWaveZSuTocChaFd 
AmpVertexSuTocChaFd= AmpVertexZSuTocChaFd
End if
If (ShiftIRdiv) Then 
AmpVertexSuTocChaFd = AmpVertexSuTocChaFd  +  AmpVertexIRosSuTocChaFd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->bar[Cha] Fd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuTocChaFd = AmpTreeSuTocChaFd 
 AmpSum2SuTocChaFd = AmpTreeSuTocChaFd + 2._dp*AmpWaveSuTocChaFd + 2._dp*AmpVertexSuTocChaFd  
Else 
 AmpSumSuTocChaFd = AmpTreeSuTocChaFd + AmpWaveSuTocChaFd + AmpVertexSuTocChaFd
 AmpSum2SuTocChaFd = AmpTreeSuTocChaFd + AmpWaveSuTocChaFd + AmpVertexSuTocChaFd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuTocChaFd = AmpTreeSuTocChaFd
 AmpSum2SuTocChaFd = AmpTreeSuTocChaFd 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,2
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MChaOS(gt2))+Abs(MFdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MCha(gt2))+Abs(MFd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SuTocChaFd = AmpTreeSuTocChaFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MCha(gt2),MFd(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuTocChaFd(gt1, gt2, gt3) 
  AmpSum2SuTocChaFd = 2._dp*AmpWaveSuTocChaFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MCha(gt2),MFd(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuTocChaFd(gt1, gt2, gt3) 
  AmpSum2SuTocChaFd = 2._dp*AmpVertexSuTocChaFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MCha(gt2),MFd(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuTocChaFd(gt1, gt2, gt3) 
  AmpSum2SuTocChaFd = AmpTreeSuTocChaFd + 2._dp*AmpWaveSuTocChaFd + 2._dp*AmpVertexSuTocChaFd
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MCha(gt2),MFd(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuTocChaFd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuTocChaFd = AmpTreeSuTocChaFd
  Call SquareAmp_StoFF(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
  AmpSqTreeSuTocChaFd(gt1, gt2, gt3) = AmpSqSuTocChaFd(gt1, gt2, gt3)  
  AmpSum2SuTocChaFd = + 2._dp*AmpWaveSuTocChaFd + 2._dp*AmpVertexSuTocChaFd
  Call SquareAmp_StoFF(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
  AmpSqSuTocChaFd(gt1, gt2, gt3) = AmpSqSuTocChaFd(gt1, gt2, gt3) + AmpSqTreeSuTocChaFd(gt1, gt2, gt3)  
Else  
  AmpSum2SuTocChaFd = AmpTreeSuTocChaFd
  Call SquareAmp_StoFF(MSu(gt1),MCha(gt2),MFd(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
  AmpSqTreeSuTocChaFd(gt1, gt2, gt3) = AmpSqSuTocChaFd(gt1, gt2, gt3)  
  AmpSum2SuTocChaFd = + 2._dp*AmpWaveSuTocChaFd + 2._dp*AmpVertexSuTocChaFd
  Call SquareAmp_StoFF(MSu(gt1),MCha(gt2),MFd(gt3),AmpSumSuTocChaFd(:,gt1, gt2, gt3),AmpSum2SuTocChaFd(:,gt1, gt2, gt3),AmpSqSuTocChaFd(gt1, gt2, gt3)) 
  AmpSqSuTocChaFd(gt1, gt2, gt3) = AmpSqSuTocChaFd(gt1, gt2, gt3) + AmpSqTreeSuTocChaFd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSuTocChaFd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqSuTocChaFd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MChaOS(gt2),MFdOS(gt3),helfactor*AmpSqSuTocChaFd(gt1, gt2, gt3))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MCha(gt2),MFd(gt3),helfactor*AmpSqSuTocChaFd(gt1, gt2, gt3))
End if 
If ((Abs(MRPSuTocChaFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuTocChaFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuTocChaFd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuTocChaFd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSuTocChaFd(gt1, gt2, gt3) + MRGSuTocChaFd(gt1, gt2, gt3)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSuTocChaFd(gt1, gt2, gt3) + MRGSuTocChaFd(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! Glu Fu
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuToGluFu(cplGluFucSuL,cplGluFucSuR,MFu,MGlu,               & 
& MSu,MFu2,MGlu2,MSu2,AmpTreeSuToGluFu)

  Else 
Call Amplitude_Tree_NMSSM_SuToGluFu(ZcplGluFucSuL,ZcplGluFucSuR,MFu,MGlu,             & 
& MSu,MFu2,MGlu2,MSu2,AmpTreeSuToGluFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuToGluFu(MLambda,em,gs,cplGluFucSuL,cplGluFucSuR,              & 
& MFuOS,MGluOS,MSuOS,MRPSuToGluFu,MRGSuToGluFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuToGluFu(MLambda,em,gs,ZcplGluFucSuL,ZcplGluFucSuR,            & 
& MFuOS,MGluOS,MSuOS,MRPSuToGluFu,MRGSuToGluFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuToGluFu(MLambda,em,gs,cplGluFucSuL,cplGluFucSuR,              & 
& MFu,MGlu,MSu,MRPSuToGluFu,MRGSuToGluFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuToGluFu(MLambda,em,gs,ZcplGluFucSuL,ZcplGluFucSuR,            & 
& MFu,MGlu,MSu,MRPSuToGluFu,MRGSuToGluFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToGluFu(cplGluFucSuL,cplGluFucSuR,ctcplGluFucSuL,         & 
& ctcplGluFucSuR,MFu,MFu2,MGlu,MGlu2,MSu,MSu2,ZffG,ZfFUL,ZfFUR,ZfSu,AmpWaveSuToGluFu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToGluFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,             & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexSuToGluFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuToGluFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRdrSuToGluFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToGluFu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,             & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,cplcChaFdcSuR,ZcplGluFucSuL,      & 
& ZcplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,               & 
& cplSucSuVZ,AmpVertexIRosSuToGluFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToGluFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,ZcplGluFucSuL,ZcplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,        & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuToGluFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToGluFu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,             & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,       & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,            & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,               & 
& cplSucSuVZ,AmpVertexIRosSuToGluFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToGluFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosSuToGluFu)

 End if 
 End if 
AmpVertexSuToGluFu = AmpVertexSuToGluFu -  AmpVertexIRdrSuToGluFu! +  AmpVertexIRosSuToGluFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuToGluFu=0._dp 
AmpVertexZSuToGluFu=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToGluFu(:,gt2,:) = AmpWaveZSuToGluFu(:,gt2,:)+ZRUZUc(gt2,gt1)*AmpWaveSuToGluFu(:,gt1,:) 
AmpVertexZSuToGluFu(:,gt2,:)= AmpVertexZSuToGluFu(:,gt2,:) + ZRUZUc(gt2,gt1)*AmpVertexSuToGluFu(:,gt1,:) 
 End Do 
End Do 
AmpWaveSuToGluFu=AmpWaveZSuToGluFu 
AmpVertexSuToGluFu= AmpVertexZSuToGluFu
! Final State 2 
AmpWaveZSuToGluFu=0._dp 
AmpVertexZSuToGluFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSuToGluFu(1,:,gt2) = AmpWaveZSuToGluFu(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveSuToGluFu(1,:,gt1) 
AmpVertexZSuToGluFu(1,:,gt2)= AmpVertexZSuToGluFu(1,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexSuToGluFu(1,:,gt1) 
AmpWaveZSuToGluFu(2,:,gt2) = AmpWaveZSuToGluFu(2,:,gt2)+ZRUZUR(gt2,gt1)*AmpWaveSuToGluFu(2,:,gt1) 
AmpVertexZSuToGluFu(2,:,gt2)= AmpVertexZSuToGluFu(2,:,gt2)+ZRUZUR(gt2,gt1)*AmpVertexSuToGluFu(2,:,gt1) 
 End Do 
End Do 
AmpWaveSuToGluFu=AmpWaveZSuToGluFu 
AmpVertexSuToGluFu= AmpVertexZSuToGluFu
End if
If (ShiftIRdiv) Then 
AmpVertexSuToGluFu = AmpVertexSuToGluFu  +  AmpVertexIRosSuToGluFu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Glu Fu -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuToGluFu = AmpTreeSuToGluFu 
 AmpSum2SuToGluFu = AmpTreeSuToGluFu + 2._dp*AmpWaveSuToGluFu + 2._dp*AmpVertexSuToGluFu  
Else 
 AmpSumSuToGluFu = AmpTreeSuToGluFu + AmpWaveSuToGluFu + AmpVertexSuToGluFu
 AmpSum2SuToGluFu = AmpTreeSuToGluFu + AmpWaveSuToGluFu + AmpVertexSuToGluFu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToGluFu = AmpTreeSuToGluFu
 AmpSum2SuToGluFu = AmpTreeSuToGluFu 
End if 
Do gt1=1,6
i4 = isave 
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MGluOS)+Abs(MFuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MGlu)+Abs(MFu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt3 
  AmpSum2SuToGluFu = AmpTreeSuToGluFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MGluOS,MFuOS(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MGlu,MFu(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuToGluFu(gt1, gt3) 
  AmpSum2SuToGluFu = 2._dp*AmpWaveSuToGluFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MGluOS,MFuOS(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MGlu,MFu(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuToGluFu(gt1, gt3) 
  AmpSum2SuToGluFu = 2._dp*AmpVertexSuToGluFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MGluOS,MFuOS(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MGlu,MFu(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuToGluFu(gt1, gt3) 
  AmpSum2SuToGluFu = AmpTreeSuToGluFu + 2._dp*AmpWaveSuToGluFu + 2._dp*AmpVertexSuToGluFu
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MSuOS(gt1),MGluOS,MFuOS(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
Else  
  Call SquareAmp_StoFF(MSu(gt1),MGlu,MFu(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuToGluFu(gt1, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuToGluFu = AmpTreeSuToGluFu
  Call SquareAmp_StoFF(MSuOS(gt1),MGluOS,MFuOS(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
  AmpSqTreeSuToGluFu(gt1, gt3) = AmpSqSuToGluFu(gt1, gt3)  
  AmpSum2SuToGluFu = + 2._dp*AmpWaveSuToGluFu + 2._dp*AmpVertexSuToGluFu
  Call SquareAmp_StoFF(MSuOS(gt1),MGluOS,MFuOS(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
  AmpSqSuToGluFu(gt1, gt3) = AmpSqSuToGluFu(gt1, gt3) + AmpSqTreeSuToGluFu(gt1, gt3)  
Else  
  AmpSum2SuToGluFu = AmpTreeSuToGluFu
  Call SquareAmp_StoFF(MSu(gt1),MGlu,MFu(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
  AmpSqTreeSuToGluFu(gt1, gt3) = AmpSqSuToGluFu(gt1, gt3)  
  AmpSum2SuToGluFu = + 2._dp*AmpWaveSuToGluFu + 2._dp*AmpVertexSuToGluFu
  Call SquareAmp_StoFF(MSu(gt1),MGlu,MFu(gt3),AmpSumSuToGluFu(:,gt1, gt3),AmpSum2SuToGluFu(:,gt1, gt3),AmpSqSuToGluFu(gt1, gt3)) 
  AmpSqSuToGluFu(gt1, gt3) = AmpSqSuToGluFu(gt1, gt3) + AmpSqTreeSuToGluFu(gt1, gt3)  
End if  
Else  
  AmpSqSuToGluFu(gt1, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqSuToGluFu(gt1, gt3).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 4._dp/3._dp*GammaTPS(MSuOS(gt1),MGluOS,MFuOS(gt3),helfactor*AmpSqSuToGluFu(gt1, gt3))
Else 
  gP1LSu(gt1,i4) = 4._dp/3._dp*GammaTPS(MSu(gt1),MGlu,MFu(gt3),helfactor*AmpSqSuToGluFu(gt1, gt3))
End if 
If ((Abs(MRPSuToGluFu(gt1, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToGluFu(gt1, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuToGluFu(gt1, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToGluFu(gt1, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSuToGluFu(gt1, gt3) + MRGSuToGluFu(gt1, gt3)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSuToGluFu(gt1, gt3) + MRGSuToGluFu(gt1, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! Su hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuToSuhh(cplhhSucSu,Mhh,MSu,Mhh2,MSu2,AmpTreeSuToSuhh)

  Else 
Call Amplitude_Tree_NMSSM_SuToSuhh(ZcplhhSucSu,Mhh,MSu,Mhh2,MSu2,AmpTreeSuToSuhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuToSuhh(MLambda,em,gs,cplhhSucSu,MhhOS,MSuOS,MRPSuToSuhh,      & 
& MRGSuToSuhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuToSuhh(MLambda,em,gs,ZcplhhSucSu,MhhOS,MSuOS,MRPSuToSuhh,     & 
& MRGSuToSuhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuToSuhh(MLambda,em,gs,cplhhSucSu,Mhh,MSu,MRPSuToSuhh,          & 
& MRGSuToSuhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuToSuhh(MLambda,em,gs,ZcplhhSucSu,Mhh,MSu,MRPSuToSuhh,         & 
& MRGSuToSuhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToSuhh(cplhhSucSu,ctcplhhSucSu,Mhh,Mhh2,MSu,              & 
& MSu2,Zfhh,ZfSu,AmpWaveSuToSuhh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToSuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhSucSu,     & 
& cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,              & 
& cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,      & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa, & 
& cplAhhhSucSuaa,cplhhhhSucSuaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplHpmSucHpmcSuaa,      & 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,& 
& cplSuSvcSucSvaa,cplSucSucVWmVWmaa,cplSucSuVZVZaa,AmpVertexSuToSuhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,          & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,         & 
& cplChiChihhR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,             & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,               & 
& cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplhhhhSucSuaa,cplhhHpmSucSdaa,               & 
& cplhhSdcHpmcSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,& 
& cplSuSucSucSuabba,cplSuSucSucSuabab,cplSuSvcSucSvaa,cplSucSucVWmVWmaa,cplSucSuVZVZaa,  & 
& AmpVertexIRdrSuToSuhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuhh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhSucSu,              & 
& cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,              & 
& cplhhSecSe,ZcplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,     & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa, & 
& cplAhhhSucSuaa,cplhhhhSucSuaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplHpmSucHpmcSuaa,      & 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,& 
& cplSuSvcSucSvaa,cplSucSucVWmVWmaa,cplSucSuVZVZaa,AmpVertexIRosSuToSuhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,          & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,         & 
& cplChiChihhR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,             & 
& cplhhSdcSd,cplhhSecSe,ZcplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,      & 
& cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,               & 
& cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplhhhhSucSuaa,cplhhHpmSucSdaa,               & 
& cplhhSdcHpmcSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,& 
& cplSuSucSucSuabba,cplSuSucSucSuabab,cplSuSvcSucSvaa,cplSucSucVWmVWmaa,cplSucSuVZVZaa,  & 
& AmpVertexIRosSuToSuhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuhh(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplAhSucSu,              & 
& cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,cplChiChihhR,       & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,cplcFdFdhhR,           & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,              & 
& cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHpmSucSd,      & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa, & 
& cplAhhhSucSuaa,cplhhhhSucSuaa,cplhhHpmSucSdaa,cplhhSdcHpmcSuaa,cplHpmSucHpmcSuaa,      & 
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,& 
& cplSuSvcSucSvaa,cplSucSucVWmVWmaa,cplSucSuVZVZaa,AmpVertexIRosSuToSuhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuhh(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,          & 
& cplAhSucSu,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplChiChihhL,         & 
& cplChiChihhR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuGluSuL,cplcFuGluSuR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,             & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,               & 
& cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplhhhhSucSuaa,cplhhHpmSucSdaa,               & 
& cplhhSdcHpmcSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSeSucSecSuaa,& 
& cplSuSucSucSuabba,cplSuSucSucSuabab,cplSuSvcSucSvaa,cplSucSucVWmVWmaa,cplSucSuVZVZaa,  & 
& AmpVertexIRosSuToSuhh)

 End if 
 End if 
AmpVertexSuToSuhh = AmpVertexSuToSuhh -  AmpVertexIRdrSuToSuhh! +  AmpVertexIRosSuToSuhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuToSuhh=0._dp 
AmpVertexZSuToSuhh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSuhh(gt2,:,:) = AmpWaveZSuToSuhh(gt2,:,:)+ZRUZUc(gt2,gt1)*AmpWaveSuToSuhh(gt1,:,:) 
AmpVertexZSuToSuhh(gt2,:,:)= AmpVertexZSuToSuhh(gt2,:,:) + ZRUZUc(gt2,gt1)*AmpVertexSuToSuhh(gt1,:,:) 
 End Do 
End Do 
AmpWaveSuToSuhh=AmpWaveZSuToSuhh 
AmpVertexSuToSuhh= AmpVertexZSuToSuhh
! Final State 1 
AmpWaveZSuToSuhh=0._dp 
AmpVertexZSuToSuhh=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSuhh(:,gt2,:) = AmpWaveZSuToSuhh(:,gt2,:)+ZRUZU(gt2,gt1)*AmpWaveSuToSuhh(:,gt1,:) 
AmpVertexZSuToSuhh(:,gt2,:)= AmpVertexZSuToSuhh(:,gt2,:)+ZRUZU(gt2,gt1)*AmpVertexSuToSuhh(:,gt1,:) 
 End Do 
End Do 
AmpWaveSuToSuhh=AmpWaveZSuToSuhh 
AmpVertexSuToSuhh= AmpVertexZSuToSuhh
! Final State 2 
AmpWaveZSuToSuhh=0._dp 
AmpVertexZSuToSuhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZSuToSuhh(:,:,gt2) = AmpWaveZSuToSuhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveSuToSuhh(:,:,gt1) 
AmpVertexZSuToSuhh(:,:,gt2)= AmpVertexZSuToSuhh(:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexSuToSuhh(:,:,gt1) 
 End Do 
End Do 
AmpWaveSuToSuhh=AmpWaveZSuToSuhh 
AmpVertexSuToSuhh= AmpVertexZSuToSuhh
End if
If (ShiftIRdiv) Then 
AmpVertexSuToSuhh = AmpVertexSuToSuhh  +  AmpVertexIRosSuToSuhh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Su hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuToSuhh = AmpTreeSuToSuhh 
 AmpSum2SuToSuhh = AmpTreeSuToSuhh + 2._dp*AmpWaveSuToSuhh + 2._dp*AmpVertexSuToSuhh  
Else 
 AmpSumSuToSuhh = AmpTreeSuToSuhh + AmpWaveSuToSuhh + AmpVertexSuToSuhh
 AmpSum2SuToSuhh = AmpTreeSuToSuhh + AmpWaveSuToSuhh + AmpVertexSuToSuhh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToSuhh = AmpTreeSuToSuhh
 AmpSum2SuToSuhh = AmpTreeSuToSuhh 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MSu(gt2))+Abs(Mhh(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SuToSuhh = AmpTreeSuToSuhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),Mhh(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuToSuhh(gt1, gt2, gt3) 
  AmpSum2SuToSuhh = 2._dp*AmpWaveSuToSuhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),Mhh(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuToSuhh(gt1, gt2, gt3) 
  AmpSum2SuToSuhh = 2._dp*AmpVertexSuToSuhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),Mhh(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuToSuhh(gt1, gt2, gt3) 
  AmpSum2SuToSuhh = AmpTreeSuToSuhh + 2._dp*AmpWaveSuToSuhh + 2._dp*AmpVertexSuToSuhh
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),Mhh(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuToSuhh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuToSuhh = AmpTreeSuToSuhh
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
  AmpSqTreeSuToSuhh(gt1, gt2, gt3) = AmpSqSuToSuhh(gt1, gt2, gt3)  
  AmpSum2SuToSuhh = + 2._dp*AmpWaveSuToSuhh + 2._dp*AmpVertexSuToSuhh
  Call SquareAmp_StoSS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
  AmpSqSuToSuhh(gt1, gt2, gt3) = AmpSqSuToSuhh(gt1, gt2, gt3) + AmpSqTreeSuToSuhh(gt1, gt2, gt3)  
Else  
  AmpSum2SuToSuhh = AmpTreeSuToSuhh
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),Mhh(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
  AmpSqTreeSuToSuhh(gt1, gt2, gt3) = AmpSqSuToSuhh(gt1, gt2, gt3)  
  AmpSum2SuToSuhh = + 2._dp*AmpWaveSuToSuhh + 2._dp*AmpVertexSuToSuhh
  Call SquareAmp_StoSS(MSu(gt1),MSu(gt2),Mhh(gt3),AmpSumSuToSuhh(gt1, gt2, gt3),AmpSum2SuToSuhh(gt1, gt2, gt3),AmpSqSuToSuhh(gt1, gt2, gt3)) 
  AmpSqSuToSuhh(gt1, gt2, gt3) = AmpSqSuToSuhh(gt1, gt2, gt3) + AmpSqTreeSuToSuhh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSuToSuhh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuToSuhh(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MSuOS(gt2),MhhOS(gt3),helfactor*AmpSqSuToSuhh(gt1, gt2, gt3))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MSu(gt2),Mhh(gt3),helfactor*AmpSqSuToSuhh(gt1, gt2, gt3))
End if 
If ((Abs(MRPSuToSuhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuToSuhh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuhh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSuToSuhh(gt1, gt2, gt3) + MRGSuToSuhh(gt1, gt2, gt3)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSuToSuhh(gt1, gt2, gt3) + MRGSuToSuhh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! Conjg(Hpm) Sd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuTocHpmSd(cplSdcHpmcSu,MHpm,MSd,MSu,MHpm2,MSd2,            & 
& MSu2,AmpTreeSuTocHpmSd)

  Else 
Call Amplitude_Tree_NMSSM_SuTocHpmSd(ZcplSdcHpmcSu,MHpm,MSd,MSu,MHpm2,MSd2,           & 
& MSu2,AmpTreeSuTocHpmSd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuTocHpmSd(MLambda,em,gs,cplSdcHpmcSu,MHpmOS,MSdOS,             & 
& MSuOS,MRPSuTocHpmSd,MRGSuTocHpmSd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuTocHpmSd(MLambda,em,gs,ZcplSdcHpmcSu,MHpmOS,MSdOS,            & 
& MSuOS,MRPSuTocHpmSd,MRGSuTocHpmSd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuTocHpmSd(MLambda,em,gs,cplSdcHpmcSu,MHpm,MSd,MSu,             & 
& MRPSuTocHpmSd,MRGSuTocHpmSd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuTocHpmSd(MLambda,em,gs,ZcplSdcHpmcSu,MHpm,MSd,MSu,            & 
& MRPSuTocHpmSd,MRGSuTocHpmSd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuTocHpmSd(cplSdcHpmcSu,ctcplSdcHpmcSu,MHpm,MHpm2,          & 
& MSd,MSd2,MSu,MSu2,ZfHpm,ZfSd,ZfSu,AmpWaveSuTocHpmSd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuTocHpmSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhSdcSd,cplAhSucSu,           & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplGluFucSuL,     & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcHpm,cplhhSdcSd,cplhhSucSu,             & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,               & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSecHpmcSv,cplSucSuVG,         & 
& cplSucSuVP,cplSucSuVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhSdcHpmcSuaa,cplhhSdcHpmcSuaa,     & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,               & 
& cplSdSvcSecSuaa,cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,AmpVertexSuTocHpmSd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuTocHpmSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhSdcSd,cplAhSucSu,     & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplGluFucSuL,     & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcHpm,cplhhSdcSd,cplhhSucSu,             & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,               & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSecHpmcSv,cplSucSuVG,         & 
& cplSucSuVP,cplSucSuVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhSdcHpmcSuaa,cplhhSdcHpmcSuaa,     & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,               & 
& cplSdSvcSecSuaa,cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,AmpVertexIRdrSuTocHpmSd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocHpmSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhHpmcHpm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,       & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,     & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcHpm,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,             & 
& cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,ZcplSdcHpmcSu,cplSdcSucVWm,cplSecHpmcSv,cplSucSuVG,cplSucSuVP,           & 
& cplSucSuVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhSdcHpmcSuaa,cplhhSdcHpmcSuaa,cplHpmSdcHpmcSdaa,& 
& cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSdSvcSecSuaa,cplSdcSucVWmVPaa,& 
& cplSdcSucVWmVZaa,AmpVertexIRosSuTocHpmSd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocHpmSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhSdcSd,cplAhSucSu,     & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplGluFucSuL,     & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcHpm,cplhhSdcSd,cplhhSucSu,             & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,               & 
& cplcChacFuSdL,cplcChacFuSdR,ZcplSdcHpmcSu,cplSdcSucVWm,cplSecHpmcSv,cplSucSuVG,        & 
& cplSucSuVP,cplSucSuVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhSdcHpmcSuaa,cplhhSdcHpmcSuaa,     & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,               & 
& cplSdSvcSecSuaa,cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,AmpVertexIRosSuTocHpmSd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocHpmSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,               & 
& MCha2OS,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,             & 
& MSv2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhHpmcHpm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,       & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,     & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcHpm,cplhhSdcSd,cplhhSucSu,cplhhcHpmVWm,             & 
& cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSecHpmcSv,cplSucSuVG,cplSucSuVP,            & 
& cplSucSuVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhSdcHpmcSuaa,cplhhSdcHpmcSuaa,cplHpmSdcHpmcSdaa,& 
& cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,cplSdSvcSecSuaa,cplSdcSucVWmVPaa,& 
& cplSdcSucVWmVZaa,AmpVertexIRosSuTocHpmSd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuTocHpmSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,           & 
& MHpm2,MSd2,MSe2,MSu2,MSv2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcHpm,cplAhSdcSd,cplAhSucSu,     & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplGluFucSuL,     & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcHpm,cplhhSdcSd,cplhhSucSu,             & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,               & 
& cplcChacFuSdL,cplcChacFuSdR,cplSdcHpmcSu,cplSdcSucVWm,cplSecHpmcSv,cplSucSuVG,         & 
& cplSucSuVP,cplSucSuVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhSdcHpmcSuaa,cplhhSdcHpmcSuaa,     & 
& cplHpmSdcHpmcSdaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,               & 
& cplSdSvcSecSuaa,cplSdcSucVWmVPaa,cplSdcSucVWmVZaa,AmpVertexIRosSuTocHpmSd)

 End if 
 End if 
AmpVertexSuTocHpmSd = AmpVertexSuTocHpmSd -  AmpVertexIRdrSuTocHpmSd! +  AmpVertexIRosSuTocHpmSd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuTocHpmSd=0._dp 
AmpVertexZSuTocHpmSd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuTocHpmSd(gt2,:,:) = AmpWaveZSuTocHpmSd(gt2,:,:)+ZRUZUc(gt2,gt1)*AmpWaveSuTocHpmSd(gt1,:,:) 
AmpVertexZSuTocHpmSd(gt2,:,:)= AmpVertexZSuTocHpmSd(gt2,:,:) + ZRUZUc(gt2,gt1)*AmpVertexSuTocHpmSd(gt1,:,:) 
 End Do 
End Do 
AmpWaveSuTocHpmSd=AmpWaveZSuTocHpmSd 
AmpVertexSuTocHpmSd= AmpVertexZSuTocHpmSd
! Final State 1 
AmpWaveZSuTocHpmSd=0._dp 
AmpVertexZSuTocHpmSd=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZSuTocHpmSd(:,gt2,:) = AmpWaveZSuTocHpmSd(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveSuTocHpmSd(:,gt1,:) 
AmpVertexZSuTocHpmSd(:,gt2,:)= AmpVertexZSuTocHpmSd(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexSuTocHpmSd(:,gt1,:) 
 End Do 
End Do 
AmpWaveSuTocHpmSd=AmpWaveZSuTocHpmSd 
AmpVertexSuTocHpmSd= AmpVertexZSuTocHpmSd
! Final State 2 
AmpWaveZSuTocHpmSd=0._dp 
AmpVertexZSuTocHpmSd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuTocHpmSd(:,:,gt2) = AmpWaveZSuTocHpmSd(:,:,gt2)+ZRUZD(gt2,gt1)*AmpWaveSuTocHpmSd(:,:,gt1) 
AmpVertexZSuTocHpmSd(:,:,gt2)= AmpVertexZSuTocHpmSd(:,:,gt2)+ZRUZD(gt2,gt1)*AmpVertexSuTocHpmSd(:,:,gt1) 
 End Do 
End Do 
AmpWaveSuTocHpmSd=AmpWaveZSuTocHpmSd 
AmpVertexSuTocHpmSd= AmpVertexZSuTocHpmSd
End if
If (ShiftIRdiv) Then 
AmpVertexSuTocHpmSd = AmpVertexSuTocHpmSd  +  AmpVertexIRosSuTocHpmSd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->conj[Hpm] Sd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuTocHpmSd = AmpTreeSuTocHpmSd 
 AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd + 2._dp*AmpWaveSuTocHpmSd + 2._dp*AmpVertexSuTocHpmSd  
Else 
 AmpSumSuTocHpmSd = AmpTreeSuTocHpmSd + AmpWaveSuTocHpmSd + AmpVertexSuTocHpmSd
 AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd + AmpWaveSuTocHpmSd + AmpVertexSuTocHpmSd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuTocHpmSd = AmpTreeSuTocHpmSd
 AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=2,2
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MHpmOS(gt2))+Abs(MSdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MHpm(gt2))+Abs(MSd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MHpm(gt2),MSd(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuTocHpmSd(gt1, gt2, gt3) 
  AmpSum2SuTocHpmSd = 2._dp*AmpWaveSuTocHpmSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MHpm(gt2),MSd(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuTocHpmSd(gt1, gt2, gt3) 
  AmpSum2SuTocHpmSd = 2._dp*AmpVertexSuTocHpmSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MHpm(gt2),MSd(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuTocHpmSd(gt1, gt2, gt3) 
  AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd + 2._dp*AmpWaveSuTocHpmSd + 2._dp*AmpVertexSuTocHpmSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MSu(gt1),MHpm(gt2),MSd(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuTocHpmSd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd
  Call SquareAmp_StoSS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
  AmpSqTreeSuTocHpmSd(gt1, gt2, gt3) = AmpSqSuTocHpmSd(gt1, gt2, gt3)  
  AmpSum2SuTocHpmSd = + 2._dp*AmpWaveSuTocHpmSd + 2._dp*AmpVertexSuTocHpmSd
  Call SquareAmp_StoSS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
  AmpSqSuTocHpmSd(gt1, gt2, gt3) = AmpSqSuTocHpmSd(gt1, gt2, gt3) + AmpSqTreeSuTocHpmSd(gt1, gt2, gt3)  
Else  
  AmpSum2SuTocHpmSd = AmpTreeSuTocHpmSd
  Call SquareAmp_StoSS(MSu(gt1),MHpm(gt2),MSd(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
  AmpSqTreeSuTocHpmSd(gt1, gt2, gt3) = AmpSqSuTocHpmSd(gt1, gt2, gt3)  
  AmpSum2SuTocHpmSd = + 2._dp*AmpWaveSuTocHpmSd + 2._dp*AmpVertexSuTocHpmSd
  Call SquareAmp_StoSS(MSu(gt1),MHpm(gt2),MSd(gt3),AmpSumSuTocHpmSd(gt1, gt2, gt3),AmpSum2SuTocHpmSd(gt1, gt2, gt3),AmpSqSuTocHpmSd(gt1, gt2, gt3)) 
  AmpSqSuTocHpmSd(gt1, gt2, gt3) = AmpSqSuTocHpmSd(gt1, gt2, gt3) + AmpSqTreeSuTocHpmSd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqSuTocHpmSd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuTocHpmSd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MHpmOS(gt2),MSdOS(gt3),helfactor*AmpSqSuTocHpmSd(gt1, gt2, gt3))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MHpm(gt2),MSd(gt3),helfactor*AmpSqSuTocHpmSd(gt1, gt2, gt3))
End if 
If ((Abs(MRPSuTocHpmSd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuTocHpmSd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuTocHpmSd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGSuTocHpmSd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPSuTocHpmSd(gt1, gt2, gt3) + MRGSuTocHpmSd(gt1, gt2, gt3)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPSuTocHpmSd(gt1, gt2, gt3) + MRGSuTocHpmSd(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! Sd Conjg(VWm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuToSdcVWm(cplSdcSucVWm,MSd,MSu,MVWm,MSd2,MSu2,             & 
& MVWm2,AmpTreeSuToSdcVWm)

  Else 
Call Amplitude_Tree_NMSSM_SuToSdcVWm(ZcplSdcSucVWm,MSd,MSu,MVWm,MSd2,MSu2,            & 
& MVWm2,AmpTreeSuToSdcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuToSdcVWm(MLambda,em,gs,cplSdcSucVWm,MSdOS,MSuOS,              & 
& MVWmOS,MRPSuToSdcVWm,MRGSuToSdcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuToSdcVWm(MLambda,em,gs,ZcplSdcSucVWm,MSdOS,MSuOS,             & 
& MVWmOS,MRPSuToSdcVWm,MRGSuToSdcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuToSdcVWm(MLambda,em,gs,cplSdcSucVWm,MSd,MSu,MVWm,             & 
& MRPSuToSdcVWm,MRGSuToSdcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuToSdcVWm(MLambda,em,gs,ZcplSdcSucVWm,MSd,MSu,MVWm,            & 
& MRPSuToSdcVWm,MRGSuToSdcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToSdcVWm(cplSdcSucVWm,ctcplSdcSucVWm,MSd,MSd2,            & 
& MSu,MSu2,MVWm,MVWm2,ZfSd,ZfSu,ZfVWm,AmpWaveSuToSdcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToSdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcChaFdcSuL,      & 
& cplcChaFdcSuR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,      & 
& cplcFdGluSdR,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhcVWmVWm,cplHpmcVWmVP,             & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,             & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplcVWmVPVWm,               & 
& cplcVWmVWmVZ,cplSdcSucVWmVGLamct4ct2ct1,cplSdcSucVWmVPaa,cplSdcSdcVWmVWmaa,            & 
& cplSdcSucVWmVZaa,cplSucSucVWmVWmaa,AmpVertexSuToSdcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuToSdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplChiChacVWmL,      & 
& cplChiChacVWmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcChaFdcSuL,      & 
& cplcChaFdcSuR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,      & 
& cplcFdGluSdR,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhcVWmVWm,cplHpmcVWmVP,             & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,             & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplcVWmVPVWm,               & 
& cplcVWmVWmVZ,cplSdcSucVWmVGLamct4ct2ct1,cplSdcSucVWmVPaa,cplSdcSdcVWmVWmaa,            & 
& cplSdcSucVWmVZaa,cplSucSucVWmVWmaa,AmpVertexIRdrSuToSdcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSdcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplChiChacVWmL,cplChiChacVWmR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcVWm,        & 
& cplhhSdcSd,cplhhSucSu,cplhhcVWmVWm,GosZcplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,GosZcplSdcHpmcSu,ZcplSdcSucVWm,      & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplSdcSucVWmVGLamct4ct2ct1, & 
& cplSdcSucVWmVPaa,cplSdcSdcVWmVWmaa,cplSdcSucVWmVZaa,cplSucSucVWmVWmaa,AmpVertexIRosSuToSdcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplChiChacVWmL,      & 
& cplChiChacVWmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcChaFdcSuL,      & 
& cplcChaFdcSuR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,      & 
& cplcFdGluSdR,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhcVWmVWm,GZcplHpmcVWmVP,           & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,             & 
& GZcplSdcHpmcSu,ZcplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,cplSdcSucVWmVGLamct4ct2ct1,cplSdcSucVWmVPaa,cplSdcSdcVWmVWmaa,            & 
& cplSdcSucVWmVZaa,cplSucSucVWmVWmaa,AmpVertexIRosSuToSdcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSdcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplChiChacVWmL,cplChiChacVWmR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplhhHpmcVWm,        & 
& cplhhSdcSd,cplhhSucSu,cplhhcVWmVWm,GcplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,GcplSdcHpmcSu,cplSdcSucVWm,          & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplSdcSucVWmVGLamct4ct2ct1, & 
& cplSdcSucVWmVPaa,cplSdcSdcVWmVWmaa,cplSdcSucVWmVZaa,cplSucSucVWmVWmaa,AmpVertexIRosSuToSdcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSdcVWm(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplChiChacVWmL,      & 
& cplChiChacVWmR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcChaFdcSuL,      & 
& cplcChaFdcSuR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,      & 
& cplcFdGluSdR,cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhcVWmVWm,cplHpmcVWmVP,             & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,             & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplcVWmVPVWm,               & 
& cplcVWmVWmVZ,cplSdcSucVWmVGLamct4ct2ct1,cplSdcSucVWmVPaa,cplSdcSdcVWmVWmaa,            & 
& cplSdcSucVWmVZaa,cplSucSucVWmVWmaa,AmpVertexIRosSuToSdcVWm)

 End if 
 End if 
AmpVertexSuToSdcVWm = AmpVertexSuToSdcVWm -  AmpVertexIRdrSuToSdcVWm! +  AmpVertexIRosSuToSdcVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuToSdcVWm=0._dp 
AmpVertexZSuToSdcVWm=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSdcVWm(:,gt2,:) = AmpWaveZSuToSdcVWm(:,gt2,:)+ZRUZUc(gt2,gt1)*AmpWaveSuToSdcVWm(:,gt1,:) 
AmpVertexZSuToSdcVWm(:,gt2,:)= AmpVertexZSuToSdcVWm(:,gt2,:) + ZRUZUc(gt2,gt1)*AmpVertexSuToSdcVWm(:,gt1,:) 
 End Do 
End Do 
AmpWaveSuToSdcVWm=AmpWaveZSuToSdcVWm 
AmpVertexSuToSdcVWm= AmpVertexZSuToSdcVWm
! Final State 1 
AmpWaveZSuToSdcVWm=0._dp 
AmpVertexZSuToSdcVWm=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSdcVWm(:,:,gt2) = AmpWaveZSuToSdcVWm(:,:,gt2)+ZRUZD(gt2,gt1)*AmpWaveSuToSdcVWm(:,:,gt1) 
AmpVertexZSuToSdcVWm(:,:,gt2)= AmpVertexZSuToSdcVWm(:,:,gt2)+ZRUZD(gt2,gt1)*AmpVertexSuToSdcVWm(:,:,gt1) 
 End Do 
End Do 
AmpWaveSuToSdcVWm=AmpWaveZSuToSdcVWm 
AmpVertexSuToSdcVWm= AmpVertexZSuToSdcVWm
End if
If (ShiftIRdiv) Then 
AmpVertexSuToSdcVWm = AmpVertexSuToSdcVWm  +  AmpVertexIRosSuToSdcVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Sd conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuToSdcVWm = AmpTreeSuToSdcVWm 
 AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm + 2._dp*AmpWaveSuToSdcVWm + 2._dp*AmpVertexSuToSdcVWm  
Else 
 AmpSumSuToSdcVWm = AmpTreeSuToSdcVWm + AmpWaveSuToSdcVWm + AmpVertexSuToSdcVWm
 AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm + AmpWaveSuToSdcVWm + AmpVertexSuToSdcVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToSdcVWm = AmpTreeSuToSdcVWm
 AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MSd(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSdOS(gt2),MVWmOS,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSd(gt2),MVWm,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuToSdcVWm(gt1, gt2) 
  AmpSum2SuToSdcVWm = 2._dp*AmpWaveSuToSdcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSdOS(gt2),MVWmOS,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSd(gt2),MVWm,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuToSdcVWm(gt1, gt2) 
  AmpSum2SuToSdcVWm = 2._dp*AmpVertexSuToSdcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSdOS(gt2),MVWmOS,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSd(gt2),MVWm,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuToSdcVWm(gt1, gt2) 
  AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm + 2._dp*AmpWaveSuToSdcVWm + 2._dp*AmpVertexSuToSdcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSdOS(gt2),MVWmOS,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSd(gt2),MVWm,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuToSdcVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm
  Call SquareAmp_StoSV(MSuOS(gt1),MSdOS(gt2),MVWmOS,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
  AmpSqTreeSuToSdcVWm(gt1, gt2) = AmpSqSuToSdcVWm(gt1, gt2)  
  AmpSum2SuToSdcVWm = + 2._dp*AmpWaveSuToSdcVWm + 2._dp*AmpVertexSuToSdcVWm
  Call SquareAmp_StoSV(MSuOS(gt1),MSdOS(gt2),MVWmOS,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
  AmpSqSuToSdcVWm(gt1, gt2) = AmpSqSuToSdcVWm(gt1, gt2) + AmpSqTreeSuToSdcVWm(gt1, gt2)  
Else  
  AmpSum2SuToSdcVWm = AmpTreeSuToSdcVWm
  Call SquareAmp_StoSV(MSu(gt1),MSd(gt2),MVWm,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
  AmpSqTreeSuToSdcVWm(gt1, gt2) = AmpSqSuToSdcVWm(gt1, gt2)  
  AmpSum2SuToSdcVWm = + 2._dp*AmpWaveSuToSdcVWm + 2._dp*AmpVertexSuToSdcVWm
  Call SquareAmp_StoSV(MSu(gt1),MSd(gt2),MVWm,AmpSumSuToSdcVWm(:,gt1, gt2),AmpSum2SuToSdcVWm(:,gt1, gt2),AmpSqSuToSdcVWm(gt1, gt2)) 
  AmpSqSuToSdcVWm(gt1, gt2) = AmpSqSuToSdcVWm(gt1, gt2) + AmpSqTreeSuToSdcVWm(gt1, gt2)  
End if  
Else  
  AmpSqSuToSdcVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuToSdcVWm(gt1, gt2).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MSdOS(gt2),MVWmOS,helfactor*AmpSqSuToSdcVWm(gt1, gt2))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MSd(gt2),MVWm,helfactor*AmpSqSuToSdcVWm(gt1, gt2))
End if 
If ((Abs(MRPSuToSdcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSuToSdcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuToSdcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSuToSdcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPSuToSdcVWm(gt1, gt2) + MRGSuToSdcVWm(gt1, gt2)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPSuToSdcVWm(gt1, gt2) + MRGSuToSdcVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
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
! Su VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_SuToSuVZ(cplSucSuVZ,MSu,MVZ,MSu2,MVZ2,AmpTreeSuToSuVZ)

  Else 
Call Amplitude_Tree_NMSSM_SuToSuVZ(ZcplSucSuVZ,MSu,MVZ,MSu2,MVZ2,AmpTreeSuToSuVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_SuToSuVZ(MLambda,em,gs,cplSucSuVZ,MSuOS,MVZOS,MRPSuToSuVZ,      & 
& MRGSuToSuVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_SuToSuVZ(MLambda,em,gs,ZcplSucSuVZ,MSuOS,MVZOS,MRPSuToSuVZ,     & 
& MRGSuToSuVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_SuToSuVZ(MLambda,em,gs,cplSucSuVZ,MSu,MVZ,MRPSuToSuVZ,          & 
& MRGSuToSuVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_SuToSuVZ(MLambda,em,gs,ZcplSucSuVZ,MSu,MVZ,MRPSuToSuVZ,         & 
& MRGSuToSuVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToSuVZ(cplSucSuVP,cplSucSuVZ,ctcplSucSuVP,ctcplSucSuVZ,   & 
& MSu,MSu2,MVP,MVP2,MVZ,MVZ2,ZfSu,ZfVPVZ,ZfVZ,AmpWaveSuToSuVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToSuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,              & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,         & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplhhVZVZ,cplHpmSucSd,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSdcHpmcSu,    & 
& cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,   & 
& cplSdcSucVWmVZaa,cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVZaa,cplSucSdVWmVZaa,              & 
& cplSucSuVZVZaa,AmpVertexSuToSuVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,         & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplhhVZVZ,cplHpmSucSd,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSdcHpmcSu,    & 
& cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,   & 
& cplSdcSucVWmVZaa,cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVZaa,cplSucSdVWmVZaa,              & 
& cplSucSuVZVZaa,AmpVertexIRdrSuToSuVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhhhVZ,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVZL,cplcChaChaVZR,            & 
& cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplhhVZVZ,cplHpmSucSd,    & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,             & 
& cplSucSuVP,cplSucSdVWm,ZcplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplSdcSucVWmVZaa,         & 
& cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVZaa,cplSucSdVWmVZaa,cplSucSuVZVZaa,AmpVertexIRosSuToSuVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,         & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplhhVZVZ,cplHpmSucSd,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSdcHpmcSu,    & 
& cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,ZcplSucSuVZ,cplcHpmVWmVZ,               & 
& cplcVWmVWmVZ,cplSdcSucVWmVZaa,cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVZaa,cplSucSdVWmVZaa, & 
& cplSucSuVZVZaa,AmpVertexIRosSuToSuVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,              & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhhhVZ,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVZL,cplcChaChaVZR,            & 
& cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplhhVZVZ,cplHpmSucSd,    & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,             & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplSdcSucVWmVZaa,          & 
& cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVZaa,cplSucSdVWmVZaa,cplSucSuVZVZaa,AmpVertexIRosSuToSuVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_SuToSuVZ(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,               & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhhhVZ,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,         & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,         & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplhhVZVZ,cplHpmSucSd,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSdcHpmcSu,    & 
& cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,   & 
& cplSdcSucVWmVZaa,cplSucSuVGVZLamct3ct2ct1,cplSucSuVPVZaa,cplSucSdVWmVZaa,              & 
& cplSucSuVZVZaa,AmpVertexIRosSuToSuVZ)

 End if 
 End if 
AmpVertexSuToSuVZ = AmpVertexSuToSuVZ -  AmpVertexIRdrSuToSuVZ! +  AmpVertexIRosSuToSuVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZSuToSuVZ=0._dp 
AmpVertexZSuToSuVZ=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSuVZ(:,gt2,:) = AmpWaveZSuToSuVZ(:,gt2,:)+ZRUZUc(gt2,gt1)*AmpWaveSuToSuVZ(:,gt1,:) 
AmpVertexZSuToSuVZ(:,gt2,:)= AmpVertexZSuToSuVZ(:,gt2,:) + ZRUZUc(gt2,gt1)*AmpVertexSuToSuVZ(:,gt1,:) 
 End Do 
End Do 
AmpWaveSuToSuVZ=AmpWaveZSuToSuVZ 
AmpVertexSuToSuVZ= AmpVertexZSuToSuVZ
! Final State 1 
AmpWaveZSuToSuVZ=0._dp 
AmpVertexZSuToSuVZ=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZSuToSuVZ(:,:,gt2) = AmpWaveZSuToSuVZ(:,:,gt2)+ZRUZU(gt2,gt1)*AmpWaveSuToSuVZ(:,:,gt1) 
AmpVertexZSuToSuVZ(:,:,gt2)= AmpVertexZSuToSuVZ(:,:,gt2)+ZRUZU(gt2,gt1)*AmpVertexSuToSuVZ(:,:,gt1) 
 End Do 
End Do 
AmpWaveSuToSuVZ=AmpWaveZSuToSuVZ 
AmpVertexSuToSuVZ= AmpVertexZSuToSuVZ
End if
If (ShiftIRdiv) Then 
AmpVertexSuToSuVZ = AmpVertexSuToSuVZ  +  AmpVertexIRosSuToSuVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Su VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumSuToSuVZ = AmpTreeSuToSuVZ 
 AmpSum2SuToSuVZ = AmpTreeSuToSuVZ + 2._dp*AmpWaveSuToSuVZ + 2._dp*AmpVertexSuToSuVZ  
Else 
 AmpSumSuToSuVZ = AmpTreeSuToSuVZ + AmpWaveSuToSuVZ + AmpVertexSuToSuVZ
 AmpSum2SuToSuVZ = AmpTreeSuToSuVZ + AmpWaveSuToSuVZ + AmpVertexSuToSuVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToSuVZ = AmpTreeSuToSuVZ
 AmpSum2SuToSuVZ = AmpTreeSuToSuVZ 
End if 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MSu(gt2))+Abs(MVZ))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2SuToSuVZ = AmpTreeSuToSuVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),MVZOS,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVZ,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqSuToSuVZ(gt1, gt2) 
  AmpSum2SuToSuVZ = 2._dp*AmpWaveSuToSuVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),MVZOS,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVZ,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqSuToSuVZ(gt1, gt2) 
  AmpSum2SuToSuVZ = 2._dp*AmpVertexSuToSuVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),MVZOS,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVZ,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqSuToSuVZ(gt1, gt2) 
  AmpSum2SuToSuVZ = AmpTreeSuToSuVZ + 2._dp*AmpWaveSuToSuVZ + 2._dp*AmpVertexSuToSuVZ
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),MVZOS,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVZ,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqSuToSuVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2SuToSuVZ = AmpTreeSuToSuVZ
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),MVZOS,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
  AmpSqTreeSuToSuVZ(gt1, gt2) = AmpSqSuToSuVZ(gt1, gt2)  
  AmpSum2SuToSuVZ = + 2._dp*AmpWaveSuToSuVZ + 2._dp*AmpVertexSuToSuVZ
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),MVZOS,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
  AmpSqSuToSuVZ(gt1, gt2) = AmpSqSuToSuVZ(gt1, gt2) + AmpSqTreeSuToSuVZ(gt1, gt2)  
Else  
  AmpSum2SuToSuVZ = AmpTreeSuToSuVZ
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVZ,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
  AmpSqTreeSuToSuVZ(gt1, gt2) = AmpSqSuToSuVZ(gt1, gt2)  
  AmpSum2SuToSuVZ = + 2._dp*AmpWaveSuToSuVZ + 2._dp*AmpVertexSuToSuVZ
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVZ,AmpSumSuToSuVZ(:,gt1, gt2),AmpSum2SuToSuVZ(:,gt1, gt2),AmpSqSuToSuVZ(gt1, gt2)) 
  AmpSqSuToSuVZ(gt1, gt2) = AmpSqSuToSuVZ(gt1, gt2) + AmpSqTreeSuToSuVZ(gt1, gt2)  
End if  
Else  
  AmpSqSuToSuVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuToSuVZ(gt1, gt2).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MSuOS(gt2),MVZOS,helfactor*AmpSqSuToSuVZ(gt1, gt2))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MSu(gt2),MVZ,helfactor*AmpSqSuToSuVZ(gt1, gt2))
End if 
If ((Abs(MRPSuToSuVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPSuToSuVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPSuToSuVZ(gt1, gt2) + MRGSuToSuVZ(gt1, gt2)) 
  gP1LSu(gt1,i4) = gP1LSu(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPSuToSuVZ(gt1, gt2) + MRGSuToSuVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LSu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
End If 
!---------------- 
! Su VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_SuToSuVG(cplSucSuVG,ctcplSucSuVG,MSuOS,MSu2OS,              & 
& MVG,MVG2,ZfSu,ZfVG,AmpWaveSuToSuVG)

 Else 
Call Amplitude_WAVE_NMSSM_SuToSuVG(cplSucSuVG,ctcplSucSuVG,MSuOS,MSu2OS,              & 
& MVG,MVG2,ZfSu,ZfVG,AmpWaveSuToSuVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_SuToSuVG(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSucSu,       & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFdFdVGL,cplcFdFdVGR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplHpmSucSd,cplSdcSdVG,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,     & 
& cplSucSdVWm,cplSucSuVZ,cplVGVGVG,cplSdcSucVWmVGLamct4ct2ct1,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSucSuVGVPLamct3ct2ct1,cplSucSdVGVWmLamct3ct2ct1,& 
& cplSucSuVGVZLamct3ct2ct1,AmpVertexSuToSuVG)

 Else 
Call Amplitude_VERTEX_NMSSM_SuToSuVG(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSucSu,       & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFdFdVGL,cplcFdFdVGR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplHpmSucSd,cplSdcSdVG,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,     & 
& cplSucSdVWm,cplSucSuVZ,cplVGVGVG,cplSdcSucVWmVGLamct4ct2ct1,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSucSuVGVPLamct3ct2ct1,cplSucSdVGVWmLamct3ct2ct1,& 
& cplSucSuVGVZLamct3ct2ct1,AmpVertexSuToSuVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToSuVG(cplSucSuVG,ctcplSucSuVG,MSu,MSu2,MVG,              & 
& MVG2,ZfSu,ZfVG,AmpWaveSuToSuVG)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToSuVG(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,           & 
& cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVGL,cplcFdFdVGR,cplcChaFdcSuL,          & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,          & 
& cplGluGluVGR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplVGVGVG,      & 
& cplSdcSucVWmVGLamct4ct2ct1,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSucSuVGVPLamct3ct2ct1,cplSucSdVGVWmLamct3ct2ct1,cplSucSuVGVZLamct3ct2ct1,           & 
& AmpVertexSuToSuVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Su VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToSuVG = 0._dp 
 AmpSum2SuToSuVG = 0._dp  
Else 
 AmpSumSuToSuVG = AmpVertexSuToSuVG + AmpWaveSuToSuVG
 AmpSum2SuToSuVG = AmpVertexSuToSuVG + AmpWaveSuToSuVG 
End If 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MSu(gt2))+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),0._dp,AmpSumSuToSuVG(:,gt1, gt2),AmpSum2SuToSuVG(:,gt1, gt2),AmpSqSuToSuVG(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVG,AmpSumSuToSuVG(:,gt1, gt2),AmpSum2SuToSuVG(:,gt1, gt2),AmpSqSuToSuVG(gt1, gt2)) 
End if  
Else  
  AmpSqSuToSuVG(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuToSuVG(gt1, gt2).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 4._dp/3._dp*GammaTPS(MSuOS(gt1),MSuOS(gt2),0._dp,helfactor*AmpSqSuToSuVG(gt1, gt2))
Else 
  gP1LSu(gt1,i4) = 4._dp/3._dp*GammaTPS(MSu(gt1),MSu(gt2),MVG,helfactor*AmpSqSuToSuVG(gt1, gt2))
End if 
If ((Abs(MRPSuToSuVG(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuVG(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
!---------------- 
! Su VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_SuToSuVP(cplSucSuVP,cplSucSuVZ,ctcplSucSuVP,ctcplSucSuVZ,   & 
& MSuOS,MSu2OS,MVP,MVP2,ZfSu,ZfVP,ZfVZVP,AmpWaveSuToSuVP)

 Else 
Call Amplitude_WAVE_NMSSM_SuToSuVP(cplSucSuVP,cplSucSuVZ,ctcplSucSuVP,ctcplSucSuVZ,   & 
& MSuOS,MSu2OS,MVP,MVP2,ZfSu,ZfVP,ZfVZVP,AmpWaveSuToSuVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_SuToSuVP(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSucSu,       & 
& cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,cplcChaChaVPR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVPL,cplcFdFdVPR,cplcChaFdcSuL,cplcChaFdcSuR,         & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuVPL,cplcFuFuVPR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplHpmSucSd,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSdcHpmcSu,              & 
& cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,   & 
& cplSdcSucVWmVPaa,cplSucSuVGVPLamct3ct2ct1,cplSucSuVPVPaa,cplSucSdVPVWmaa,              & 
& cplSucSuVPVZaa,AmpVertexSuToSuVP)

 Else 
Call Amplitude_VERTEX_NMSSM_SuToSuVP(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,MGluOS,          & 
& MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,           & 
& MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,cplAhSucSu,       & 
& cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,cplcChaChaVPR,cplChiFucSuL,cplChiFucSuR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVPL,cplcFdFdVPR,cplcChaFdcSuL,cplcChaFdcSuR,         & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuVPL,cplcFuFuVPR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplhhSucSu,cplHpmSucSd,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSdcHpmcSu,              & 
& cplSdcSucVWm,cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,   & 
& cplSdcSucVWmVPaa,cplSucSuVGVPLamct3ct2ct1,cplSucSuVPVPaa,cplSucSdVPVWmaa,              & 
& cplSucSuVPVZaa,AmpVertexSuToSuVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_SuToSuVP(cplSucSuVP,cplSucSuVZ,ctcplSucSuVP,ctcplSucSuVZ,   & 
& MSu,MSu2,MVP,MVP2,ZfSu,ZfVP,ZfVZVP,AmpWaveSuToSuVP)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_SuToSuVP(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,             & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhSucSu,cplcFdChaSuL,cplcFdChaSuR,cplcChaChaVPL,          & 
& cplcChaChaVPR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFdFdVPL,         & 
& cplcFdFdVPR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuVPL,         & 
& cplcFuFuVPR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplHpmcHpmVP,             & 
& cplHpmcVWmVP,cplSdcSdVP,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,               & 
& cplSucSdVWm,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplSdcSucVWmVPaa,cplSucSuVGVPLamct3ct2ct1,& 
& cplSucSuVPVPaa,cplSucSdVPVWmaa,cplSucSuVPVZaa,AmpVertexSuToSuVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Su->Su VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumSuToSuVP = 0._dp 
 AmpSum2SuToSuVP = 0._dp  
Else 
 AmpSumSuToSuVP = AmpVertexSuToSuVP + AmpWaveSuToSuVP
 AmpSum2SuToSuVP = AmpVertexSuToSuVP + AmpWaveSuToSuVP 
End If 
Do gt1=1,6
i4 = isave 
  Do gt2=1,6
If (((OSkinematics).and.(Abs(MSuOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MSu(gt1)).gt.(Abs(MSu(gt2))+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MSuOS(gt1),MSuOS(gt2),0._dp,AmpSumSuToSuVP(:,gt1, gt2),AmpSum2SuToSuVP(:,gt1, gt2),AmpSqSuToSuVP(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MSu(gt1),MSu(gt2),MVP,AmpSumSuToSuVP(:,gt1, gt2),AmpSum2SuToSuVP(:,gt1, gt2),AmpSqSuToSuVP(gt1, gt2)) 
End if  
Else  
  AmpSqSuToSuVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqSuToSuVP(gt1, gt2).eq.0._dp) Then 
  gP1LSu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSuOS(gt1),MSuOS(gt2),0._dp,helfactor*AmpSqSuToSuVP(gt1, gt2))
Else 
  gP1LSu(gt1,i4) = 1._dp*GammaTPS(MSu(gt1),MSu(gt2),MVP,helfactor*AmpSqSuToSuVP(gt1, gt2))
End if 
If ((Abs(MRPSuToSuVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGSuToSuVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LSu(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.6) isave = i4 
End do
End Subroutine OneLoopDecay_Su

End Module Wrapper_OneLoopDecay_Su_NMSSM
