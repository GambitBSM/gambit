! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:27 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Ah_NMSSM
Use Model_Data_NMSSM 
Use Kinematics 
Use OneLoopDecay_Ah_NMSSM 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Ah(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,              & 
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
& ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhcVWmVWm1,cplAhAhhh,           & 
& cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,              & 
& cplAhAhSvcSv1,cplAhAhVZVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWm,cplAhcHpmVWmVZ1,               & 
& cplAhhhhh,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,cplAhhhSucSuaa,    & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplAhHpmSucSdaa,   & 
& cplAhHpmSvcSe1,cplAhSdcHpmcSuaa,cplAhSdcSd,cplAhSecHpmcSv1,cplAhSecSe,cplAhSucSu,      & 
& cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,      & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHpm,    & 
& cplcgWmgAVWm,cplcgWmgWmAh,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHpm,         & 
& cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh,cplcgWpCgWpChh,cplcgWpCgWpCVP,              & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHpm,cplcgWpCgZcVWm,cplcgZgWmcHpm,cplcgZgWmcVWm,              & 
& cplcgZgWpCHpm,cplcgZgWpCVWm,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,       & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,              & 
& cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,         & 
& cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVPVWm1,cplhhcHpmVWm,cplhhcHpmVWmVZ1,   & 
& cplhhcVWmVWm,cplhhhhcVWmVWm1,cplhhhhhh,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,    & 
& cplhhhhSecSe1,cplhhhhSucSuaa,cplhhhhSvcSv1,cplhhhhVZVZ1,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,           & 
& cplhhVZVZ,cplHpmcHpmcVWmVWm1,cplHpmcHpmVP,cplHpmcHpmVPVP1,cplHpmcHpmVPVZ1,             & 
& cplHpmcHpmVZ,cplHpmcHpmVZVZ1,cplHpmcVWmVP,cplHpmcVWmVZ,cplHpmHpmcHpmcHpm1,             & 
& cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,cplHpmSucSd,cplHpmSvcHpmcSv1,     & 
& cplHpmSvcSe,cplSdcHpmcSu,cplSdcSdcVWmVWmaa,cplSdcSdVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,& 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,cplSdcSdVP,cplSdcSdVPVPaa,cplSdcSdVPVZaa,    & 
& cplSdcSdVZ,cplSdcSdVZVZaa,cplSdcSucVWm,cplSdSdcSdcSdabab,cplSdSdcSdcSdabba,            & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabab,cplSdSucSdcSuabba,cplSdSvcSdcSvaa,cplSecHpmcSv,      & 
& cplSecSecVWmVWm1,cplSecSeVP,cplSecSeVPVP1,cplSecSeVPVZ1,cplSecSeVZ,cplSecSeVZVZ1,      & 
& cplSecSvcVWm,cplSeSecSecSe1,cplSeSucSecSuaa,cplSeSvcSecSv1,cplSucSdVWm,cplSucSucVWmVWmaa,& 
& cplSucSuVG,cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSucSuVP,cplSucSuVPVPaa,cplSucSuVPVZaa,cplSucSuVZ,cplSucSuVZVZaa,cplSuSucSucSuabab,  & 
& cplSuSucSucSuabba,cplSuSvcSucSvaa,cplSvcSeVWm,cplSvcSvVZ,ctcplAhAhAh,ctcplAhAhhh,      & 
& ctcplAhhhhh,ctcplAhhhVZ,ctcplAhHpmcHpm,ctcplAhHpmcVWm,ctcplAhSdcSd,ctcplAhSecSe,       & 
& ctcplAhSucSu,ctcplcChaChaAhL,ctcplcChaChaAhR,ctcplcFdFdAhL,ctcplcFdFdAhR,              & 
& ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplChiChiAhL,ctcplChiChiAhR, & 
& GcplAhHpmcHpm,GcplcHpmVPVWm,GcplHpmcVWmVP,GosZcplAhHpmcHpm,GosZcplcHpmVPVWm,           & 
& GosZcplHpmcVWmVP,GZcplAhHpmcHpm,GZcplcHpmVPVWm,GZcplHpmcVWmVP,ZcplAhAhAh,              & 
& ZcplAhAhhh,ZcplAhhhhh,ZcplAhhhVZ,ZcplAhHpmcHpm,ZcplAhHpmcVWm,ZcplAhSdcSd,              & 
& ZcplAhSecSe,ZcplAhSucSu,ZcplcChaChaAhL,ZcplcChaChaAhR,ZcplcFdFdAhL,ZcplcFdFdAhR,       & 
& ZcplcFeFeAhL,ZcplcFeFeAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,ZcplChiChiAhL,ZcplChiChiAhR,       & 
& ZRUZD,ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,             & 
& ZRUZDL,ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LAh)

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

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhAhAh1(3,3,3,3),cplAhAhAhhh1(3,3,3,3),cplAhAhcVWmVWm1(3,3),    & 
& cplAhAhhh(3,3,3),cplAhAhhhhh1(3,3,3,3),cplAhAhHpmcHpm1(3,3,2,2),cplAhAhSdcSdaa(3,3,6,6),& 
& cplAhAhSecSe1(3,3,6,6),cplAhAhSucSuaa(3,3,6,6),cplAhAhSvcSv1(3,3,3,3),cplAhAhVZVZ1(3,3),& 
& cplAhcHpmVPVWm1(3,2),cplAhcHpmVWm(3,2),cplAhcHpmVWmVZ1(3,2),cplAhhhhh(3,3,3),          & 
& cplAhhhhhhh1(3,3,3,3),cplAhhhHpmcHpm1(3,3,2,2),cplAhhhSdcSdaa(3,3,6,6),cplAhhhSecSe1(3,3,6,6),& 
& cplAhhhSucSuaa(3,3,6,6),cplAhhhVZ(3,3),cplAhHpmcHpm(3,2,2),cplAhHpmcVWm(3,2),          & 
& cplAhHpmcVWmVP1(3,2),cplAhHpmcVWmVZ1(3,2),cplAhHpmSucSdaa(3,2,6,6),cplAhHpmSvcSe1(3,2,3,6),& 
& cplAhSdcHpmcSuaa(3,6,2,6),cplAhSdcSd(3,6,6),cplAhSecHpmcSv1(3,6,2,3),cplAhSecSe(3,6,6),& 
& cplAhSucSu(3,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplcChaChahhL(2,2,3),   & 
& cplcChaChahhR(2,2,3),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),         & 
& cplcChaChaVZR(2,2),cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),cplcChaChiVWmL(2,5),    & 
& cplcChaChiVWmR(2,5),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcChaFecSvL(2,3,3),    & 
& cplcChaFecSvR(2,3,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFdChiSdL(3,5,6),      & 
& cplcFdChiSdR(3,5,6),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFdFdhhL(3,3,3),          & 
& cplcFdFdhhR(3,3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),             & 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),               & 
& cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplcFeChiSeL(3,5,6),cplcFeChiSeR(3,5,6),       & 
& cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),           & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHpmL(3,3,2),& 
& cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFuChiSuL(3,5,6),           & 
& cplcFuChiSuR(3,5,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),      & 
& cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcFvChiSvL(3,5,3),& 
& cplcFvChiSvR(3,5,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFvFecVWmL(3,3),      & 
& cplcFvFecVWmR(3,3),cplcgAgWmcVWm,cplcgAgWpCVWm,cplcgWmgAHpm(2),cplcgWmgAVWm,           & 
& cplcgWmgWmAh(3),cplcgWmgWmhh(3),cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWmgZHpm(2),             & 
& cplcgWmgZVWm,cplcgWpCgAcVWm,cplcgWpCgWpCAh(3),cplcgWpCgWpChh(3),cplcgWpCgWpCVP,        & 
& cplcgWpCgWpCVZ,cplcgWpCgZcHpm(2),cplcgWpCgZcVWm,cplcgZgWmcHpm(2),cplcgZgWmcVWm,        & 
& cplcgZgWpCHpm(2),cplcgZgWpCVWm,cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),& 
& cplChaFvcSeR(2,3,6),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplChiChacVWmL(5,2),   & 
& cplChiChacVWmR(5,2),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplChiFdcSdL(5,3,6),           & 
& cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),       & 
& cplChiFucSuR(5,3,6),cplChiFvcSvL(5,3,3),cplChiFvcSvR(5,3,3),cplcHpmVPVWm(2)

Complex(dp),Intent(in) :: cplcHpmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),         & 
& cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplhhcHpmVPVWm1(3,2),cplhhcHpmVWm(3,2),            & 
& cplhhcHpmVWmVZ1(3,2),cplhhcVWmVWm(3),cplhhhhcVWmVWm1(3,3),cplhhhhhh(3,3,3),            & 
& cplhhhhhhhh1(3,3,3,3),cplhhhhHpmcHpm1(3,3,2,2),cplhhhhSdcSdaa(3,3,6,6),cplhhhhSecSe1(3,3,6,6),& 
& cplhhhhSucSuaa(3,3,6,6),cplhhhhSvcSv1(3,3,3,3),cplhhhhVZVZ1(3,3),cplhhHpmcHpm(3,2,2),  & 
& cplhhHpmcVWm(3,2),cplhhHpmcVWmVP1(3,2),cplhhHpmcVWmVZ1(3,2),cplhhSdcSd(3,6,6),         & 
& cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplhhSvcSv(3,3,3),cplhhVZVZ(3),cplHpmcHpmcVWmVWm1(2,2),& 
& cplHpmcHpmVP(2,2),cplHpmcHpmVPVP1(2,2),cplHpmcHpmVPVZ1(2,2),cplHpmcHpmVZ(2,2),         & 
& cplHpmcHpmVZVZ1(2,2),cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplHpmHpmcHpmcHpm1(2,2,2,2),      & 
& cplHpmSdcHpmcSdaa(2,6,2,6),cplHpmSecHpmcSe1(2,6,2,6),cplHpmSucHpmcSuaa(2,6,2,6),       & 
& cplHpmSucSd(2,6,6),cplHpmSvcHpmcSv1(2,3,2,3),cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),   & 
& cplSdcSdcVWmVWmaa(6,6),cplSdcSdVG(6,6),cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1(6,6), & 
& cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1(6,6),cplSdcSdVP(6,6),cplSdcSdVPVPaa(6,6),    & 
& cplSdcSdVPVZaa(6,6),cplSdcSdVZ(6,6),cplSdcSdVZVZaa(6,6),cplSdcSucVWm(6,6),             & 
& cplSdSdcSdcSdabab(6,6,6,6),cplSdSdcSdcSdabba(6,6,6,6),cplSdSecSdcSeaa(6,6,6,6),        & 
& cplSdSucSdcSuabab(6,6,6,6),cplSdSucSdcSuabba(6,6,6,6),cplSdSvcSdcSvaa(6,3,6,3),        & 
& cplSecHpmcSv(6,2,3),cplSecSecVWmVWm1(6,6),cplSecSeVP(6,6),cplSecSeVPVP1(6,6),          & 
& cplSecSeVPVZ1(6,6),cplSecSeVZ(6,6),cplSecSeVZVZ1(6,6),cplSecSvcVWm(6,3),               & 
& cplSeSecSecSe1(6,6,6,6),cplSeSucSecSuaa(6,6,6,6),cplSeSvcSecSv1(6,3,6,3),              & 
& cplSucSdVWm(6,6),cplSucSucVWmVWmaa(6,6),cplSucSuVG(6,6),cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1(6,6),& 
& cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1(6,6),cplSucSuVP(6,6),cplSucSuVPVPaa(6,6),    & 
& cplSucSuVPVZaa(6,6),cplSucSuVZ(6,6),cplSucSuVZVZaa(6,6),cplSuSucSucSuabab(6,6,6,6),    & 
& cplSuSucSucSuabba(6,6,6,6),cplSuSvcSucSvaa(6,3,6,3),cplSvcSeVWm(3,6),cplSvcSvVZ(3,3),  & 
& ctcplAhAhAh(3,3,3),ctcplAhAhhh(3,3,3),ctcplAhhhhh(3,3,3),ctcplAhhhVZ(3,3),             & 
& ctcplAhHpmcHpm(3,2,2),ctcplAhHpmcVWm(3,2),ctcplAhSdcSd(3,6,6),ctcplAhSecSe(3,6,6),     & 
& ctcplAhSucSu(3,6,6),ctcplcChaChaAhL(2,2,3),ctcplcChaChaAhR(2,2,3),ctcplcFdFdAhL(3,3,3),& 
& ctcplcFdFdAhR(3,3,3),ctcplcFeFeAhL(3,3,3),ctcplcFeFeAhR(3,3,3),ctcplcFuFuAhL(3,3,3),   & 
& ctcplcFuFuAhR(3,3,3),ctcplChiChiAhL(5,5,3),ctcplChiChiAhR(5,5,3),GcplAhHpmcHpm(3,2,2), & 
& GcplcHpmVPVWm(2),GcplHpmcVWmVP(2),GosZcplAhHpmcHpm(3,2,2),GosZcplcHpmVPVWm(2),         & 
& GosZcplHpmcVWmVP(2),GZcplAhHpmcHpm(3,2,2),GZcplcHpmVPVWm(2),GZcplHpmcVWmVP(2),         & 
& ZcplAhAhAh(3,3,3),ZcplAhAhhh(3,3,3),ZcplAhhhhh(3,3,3),ZcplAhhhVZ(3,3),ZcplAhHpmcHpm(3,2,2),& 
& ZcplAhHpmcVWm(3,2),ZcplAhSdcSd(3,6,6),ZcplAhSecSe(3,6,6),ZcplAhSucSu(3,6,6),           & 
& ZcplcChaChaAhL(2,2,3),ZcplcChaChaAhR(2,2,3),ZcplcFdFdAhL(3,3,3),ZcplcFdFdAhR(3,3,3),   & 
& ZcplcFeFeAhL(3,3,3),ZcplcFeFeAhR(3,3,3),ZcplcFuFuAhL(3,3,3),ZcplcFuFuAhR(3,3,3),       & 
& ZcplChiChiAhL(5,5,3),ZcplChiChiAhR(5,5,3)

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
Real(dp), Intent(out) :: gP1LAh(3,207) 
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
Real(dp) :: MRPAhToAhAh(3,3,3),MRGAhToAhAh(3,3,3), MRPZAhToAhAh(3,3,3),MRGZAhToAhAh(3,3,3) 
Real(dp) :: MVPAhToAhAh(3,3,3) 
Real(dp) :: RMsqTreeAhToAhAh(3,3,3),RMsqWaveAhToAhAh(3,3,3),RMsqVertexAhToAhAh(3,3,3) 
Complex(dp) :: AmpTreeAhToAhAh(3,3,3),AmpWaveAhToAhAh(3,3,3)=(0._dp,0._dp),AmpVertexAhToAhAh(3,3,3)& 
 & ,AmpVertexIRosAhToAhAh(3,3,3),AmpVertexIRdrAhToAhAh(3,3,3), AmpSumAhToAhAh(3,3,3), AmpSum2AhToAhAh(3,3,3) 
Complex(dp) :: AmpTreeZAhToAhAh(3,3,3),AmpWaveZAhToAhAh(3,3,3),AmpVertexZAhToAhAh(3,3,3) 
Real(dp) :: AmpSqAhToAhAh(3,3,3),  AmpSqTreeAhToAhAh(3,3,3) 
Real(dp) :: MRPAhTohhAh(3,3,3),MRGAhTohhAh(3,3,3), MRPZAhTohhAh(3,3,3),MRGZAhTohhAh(3,3,3) 
Real(dp) :: MVPAhTohhAh(3,3,3) 
Real(dp) :: RMsqTreeAhTohhAh(3,3,3),RMsqWaveAhTohhAh(3,3,3),RMsqVertexAhTohhAh(3,3,3) 
Complex(dp) :: AmpTreeAhTohhAh(3,3,3),AmpWaveAhTohhAh(3,3,3)=(0._dp,0._dp),AmpVertexAhTohhAh(3,3,3)& 
 & ,AmpVertexIRosAhTohhAh(3,3,3),AmpVertexIRdrAhTohhAh(3,3,3), AmpSumAhTohhAh(3,3,3), AmpSum2AhTohhAh(3,3,3) 
Complex(dp) :: AmpTreeZAhTohhAh(3,3,3),AmpWaveZAhTohhAh(3,3,3),AmpVertexZAhTohhAh(3,3,3) 
Real(dp) :: AmpSqAhTohhAh(3,3,3),  AmpSqTreeAhTohhAh(3,3,3) 
Real(dp) :: MRPAhTocChaCha(3,2,2),MRGAhTocChaCha(3,2,2), MRPZAhTocChaCha(3,2,2),MRGZAhTocChaCha(3,2,2) 
Real(dp) :: MVPAhTocChaCha(3,2,2) 
Real(dp) :: RMsqTreeAhTocChaCha(3,2,2),RMsqWaveAhTocChaCha(3,2,2),RMsqVertexAhTocChaCha(3,2,2) 
Complex(dp) :: AmpTreeAhTocChaCha(2,3,2,2),AmpWaveAhTocChaCha(2,3,2,2)=(0._dp,0._dp),AmpVertexAhTocChaCha(2,3,2,2)& 
 & ,AmpVertexIRosAhTocChaCha(2,3,2,2),AmpVertexIRdrAhTocChaCha(2,3,2,2), AmpSumAhTocChaCha(2,3,2,2), AmpSum2AhTocChaCha(2,3,2,2) 
Complex(dp) :: AmpTreeZAhTocChaCha(2,3,2,2),AmpWaveZAhTocChaCha(2,3,2,2),AmpVertexZAhTocChaCha(2,3,2,2) 
Real(dp) :: AmpSqAhTocChaCha(3,2,2),  AmpSqTreeAhTocChaCha(3,2,2) 
Real(dp) :: MRPAhToChiChi(3,5,5),MRGAhToChiChi(3,5,5), MRPZAhToChiChi(3,5,5),MRGZAhToChiChi(3,5,5) 
Real(dp) :: MVPAhToChiChi(3,5,5) 
Real(dp) :: RMsqTreeAhToChiChi(3,5,5),RMsqWaveAhToChiChi(3,5,5),RMsqVertexAhToChiChi(3,5,5) 
Complex(dp) :: AmpTreeAhToChiChi(2,3,5,5),AmpWaveAhToChiChi(2,3,5,5)=(0._dp,0._dp),AmpVertexAhToChiChi(2,3,5,5)& 
 & ,AmpVertexIRosAhToChiChi(2,3,5,5),AmpVertexIRdrAhToChiChi(2,3,5,5), AmpSumAhToChiChi(2,3,5,5), AmpSum2AhToChiChi(2,3,5,5) 
Complex(dp) :: AmpTreeZAhToChiChi(2,3,5,5),AmpWaveZAhToChiChi(2,3,5,5),AmpVertexZAhToChiChi(2,3,5,5) 
Real(dp) :: AmpSqAhToChiChi(3,5,5),  AmpSqTreeAhToChiChi(3,5,5) 
Real(dp) :: MRPAhTocFdFd(3,3,3),MRGAhTocFdFd(3,3,3), MRPZAhTocFdFd(3,3,3),MRGZAhTocFdFd(3,3,3) 
Real(dp) :: MVPAhTocFdFd(3,3,3) 
Real(dp) :: RMsqTreeAhTocFdFd(3,3,3),RMsqWaveAhTocFdFd(3,3,3),RMsqVertexAhTocFdFd(3,3,3) 
Complex(dp) :: AmpTreeAhTocFdFd(2,3,3,3),AmpWaveAhTocFdFd(2,3,3,3)=(0._dp,0._dp),AmpVertexAhTocFdFd(2,3,3,3)& 
 & ,AmpVertexIRosAhTocFdFd(2,3,3,3),AmpVertexIRdrAhTocFdFd(2,3,3,3), AmpSumAhTocFdFd(2,3,3,3), AmpSum2AhTocFdFd(2,3,3,3) 
Complex(dp) :: AmpTreeZAhTocFdFd(2,3,3,3),AmpWaveZAhTocFdFd(2,3,3,3),AmpVertexZAhTocFdFd(2,3,3,3) 
Real(dp) :: AmpSqAhTocFdFd(3,3,3),  AmpSqTreeAhTocFdFd(3,3,3) 
Real(dp) :: MRPAhTocFeFe(3,3,3),MRGAhTocFeFe(3,3,3), MRPZAhTocFeFe(3,3,3),MRGZAhTocFeFe(3,3,3) 
Real(dp) :: MVPAhTocFeFe(3,3,3) 
Real(dp) :: RMsqTreeAhTocFeFe(3,3,3),RMsqWaveAhTocFeFe(3,3,3),RMsqVertexAhTocFeFe(3,3,3) 
Complex(dp) :: AmpTreeAhTocFeFe(2,3,3,3),AmpWaveAhTocFeFe(2,3,3,3)=(0._dp,0._dp),AmpVertexAhTocFeFe(2,3,3,3)& 
 & ,AmpVertexIRosAhTocFeFe(2,3,3,3),AmpVertexIRdrAhTocFeFe(2,3,3,3), AmpSumAhTocFeFe(2,3,3,3), AmpSum2AhTocFeFe(2,3,3,3) 
Complex(dp) :: AmpTreeZAhTocFeFe(2,3,3,3),AmpWaveZAhTocFeFe(2,3,3,3),AmpVertexZAhTocFeFe(2,3,3,3) 
Real(dp) :: AmpSqAhTocFeFe(3,3,3),  AmpSqTreeAhTocFeFe(3,3,3) 
Real(dp) :: MRPAhTocFuFu(3,3,3),MRGAhTocFuFu(3,3,3), MRPZAhTocFuFu(3,3,3),MRGZAhTocFuFu(3,3,3) 
Real(dp) :: MVPAhTocFuFu(3,3,3) 
Real(dp) :: RMsqTreeAhTocFuFu(3,3,3),RMsqWaveAhTocFuFu(3,3,3),RMsqVertexAhTocFuFu(3,3,3) 
Complex(dp) :: AmpTreeAhTocFuFu(2,3,3,3),AmpWaveAhTocFuFu(2,3,3,3)=(0._dp,0._dp),AmpVertexAhTocFuFu(2,3,3,3)& 
 & ,AmpVertexIRosAhTocFuFu(2,3,3,3),AmpVertexIRdrAhTocFuFu(2,3,3,3), AmpSumAhTocFuFu(2,3,3,3), AmpSum2AhTocFuFu(2,3,3,3) 
Complex(dp) :: AmpTreeZAhTocFuFu(2,3,3,3),AmpWaveZAhTocFuFu(2,3,3,3),AmpVertexZAhTocFuFu(2,3,3,3) 
Real(dp) :: AmpSqAhTocFuFu(3,3,3),  AmpSqTreeAhTocFuFu(3,3,3) 
Real(dp) :: MRPAhTohhhh(3,3,3),MRGAhTohhhh(3,3,3), MRPZAhTohhhh(3,3,3),MRGZAhTohhhh(3,3,3) 
Real(dp) :: MVPAhTohhhh(3,3,3) 
Real(dp) :: RMsqTreeAhTohhhh(3,3,3),RMsqWaveAhTohhhh(3,3,3),RMsqVertexAhTohhhh(3,3,3) 
Complex(dp) :: AmpTreeAhTohhhh(3,3,3),AmpWaveAhTohhhh(3,3,3)=(0._dp,0._dp),AmpVertexAhTohhhh(3,3,3)& 
 & ,AmpVertexIRosAhTohhhh(3,3,3),AmpVertexIRdrAhTohhhh(3,3,3), AmpSumAhTohhhh(3,3,3), AmpSum2AhTohhhh(3,3,3) 
Complex(dp) :: AmpTreeZAhTohhhh(3,3,3),AmpWaveZAhTohhhh(3,3,3),AmpVertexZAhTohhhh(3,3,3) 
Real(dp) :: AmpSqAhTohhhh(3,3,3),  AmpSqTreeAhTohhhh(3,3,3) 
Real(dp) :: MRPAhTohhVZ(3,3),MRGAhTohhVZ(3,3), MRPZAhTohhVZ(3,3),MRGZAhTohhVZ(3,3) 
Real(dp) :: MVPAhTohhVZ(3,3) 
Real(dp) :: RMsqTreeAhTohhVZ(3,3),RMsqWaveAhTohhVZ(3,3),RMsqVertexAhTohhVZ(3,3) 
Complex(dp) :: AmpTreeAhTohhVZ(2,3,3),AmpWaveAhTohhVZ(2,3,3)=(0._dp,0._dp),AmpVertexAhTohhVZ(2,3,3)& 
 & ,AmpVertexIRosAhTohhVZ(2,3,3),AmpVertexIRdrAhTohhVZ(2,3,3), AmpSumAhTohhVZ(2,3,3), AmpSum2AhTohhVZ(2,3,3) 
Complex(dp) :: AmpTreeZAhTohhVZ(2,3,3),AmpWaveZAhTohhVZ(2,3,3),AmpVertexZAhTohhVZ(2,3,3) 
Real(dp) :: AmpSqAhTohhVZ(3,3),  AmpSqTreeAhTohhVZ(3,3) 
Real(dp) :: MRPAhTocHpmHpm(3,2,2),MRGAhTocHpmHpm(3,2,2), MRPZAhTocHpmHpm(3,2,2),MRGZAhTocHpmHpm(3,2,2) 
Real(dp) :: MVPAhTocHpmHpm(3,2,2) 
Real(dp) :: RMsqTreeAhTocHpmHpm(3,2,2),RMsqWaveAhTocHpmHpm(3,2,2),RMsqVertexAhTocHpmHpm(3,2,2) 
Complex(dp) :: AmpTreeAhTocHpmHpm(3,2,2),AmpWaveAhTocHpmHpm(3,2,2)=(0._dp,0._dp),AmpVertexAhTocHpmHpm(3,2,2)& 
 & ,AmpVertexIRosAhTocHpmHpm(3,2,2),AmpVertexIRdrAhTocHpmHpm(3,2,2), AmpSumAhTocHpmHpm(3,2,2), AmpSum2AhTocHpmHpm(3,2,2) 
Complex(dp) :: AmpTreeZAhTocHpmHpm(3,2,2),AmpWaveZAhTocHpmHpm(3,2,2),AmpVertexZAhTocHpmHpm(3,2,2) 
Real(dp) :: AmpSqAhTocHpmHpm(3,2,2),  AmpSqTreeAhTocHpmHpm(3,2,2) 
Real(dp) :: MRPAhToHpmcVWm(3,2),MRGAhToHpmcVWm(3,2), MRPZAhToHpmcVWm(3,2),MRGZAhToHpmcVWm(3,2) 
Real(dp) :: MVPAhToHpmcVWm(3,2) 
Real(dp) :: RMsqTreeAhToHpmcVWm(3,2),RMsqWaveAhToHpmcVWm(3,2),RMsqVertexAhToHpmcVWm(3,2) 
Complex(dp) :: AmpTreeAhToHpmcVWm(2,3,2),AmpWaveAhToHpmcVWm(2,3,2)=(0._dp,0._dp),AmpVertexAhToHpmcVWm(2,3,2)& 
 & ,AmpVertexIRosAhToHpmcVWm(2,3,2),AmpVertexIRdrAhToHpmcVWm(2,3,2), AmpSumAhToHpmcVWm(2,3,2), AmpSum2AhToHpmcVWm(2,3,2) 
Complex(dp) :: AmpTreeZAhToHpmcVWm(2,3,2),AmpWaveZAhToHpmcVWm(2,3,2),AmpVertexZAhToHpmcVWm(2,3,2) 
Real(dp) :: AmpSqAhToHpmcVWm(3,2),  AmpSqTreeAhToHpmcVWm(3,2) 
Real(dp) :: MRPAhTocSdSd(3,6,6),MRGAhTocSdSd(3,6,6), MRPZAhTocSdSd(3,6,6),MRGZAhTocSdSd(3,6,6) 
Real(dp) :: MVPAhTocSdSd(3,6,6) 
Real(dp) :: RMsqTreeAhTocSdSd(3,6,6),RMsqWaveAhTocSdSd(3,6,6),RMsqVertexAhTocSdSd(3,6,6) 
Complex(dp) :: AmpTreeAhTocSdSd(3,6,6),AmpWaveAhTocSdSd(3,6,6)=(0._dp,0._dp),AmpVertexAhTocSdSd(3,6,6)& 
 & ,AmpVertexIRosAhTocSdSd(3,6,6),AmpVertexIRdrAhTocSdSd(3,6,6), AmpSumAhTocSdSd(3,6,6), AmpSum2AhTocSdSd(3,6,6) 
Complex(dp) :: AmpTreeZAhTocSdSd(3,6,6),AmpWaveZAhTocSdSd(3,6,6),AmpVertexZAhTocSdSd(3,6,6) 
Real(dp) :: AmpSqAhTocSdSd(3,6,6),  AmpSqTreeAhTocSdSd(3,6,6) 
Real(dp) :: MRPAhTocSeSe(3,6,6),MRGAhTocSeSe(3,6,6), MRPZAhTocSeSe(3,6,6),MRGZAhTocSeSe(3,6,6) 
Real(dp) :: MVPAhTocSeSe(3,6,6) 
Real(dp) :: RMsqTreeAhTocSeSe(3,6,6),RMsqWaveAhTocSeSe(3,6,6),RMsqVertexAhTocSeSe(3,6,6) 
Complex(dp) :: AmpTreeAhTocSeSe(3,6,6),AmpWaveAhTocSeSe(3,6,6)=(0._dp,0._dp),AmpVertexAhTocSeSe(3,6,6)& 
 & ,AmpVertexIRosAhTocSeSe(3,6,6),AmpVertexIRdrAhTocSeSe(3,6,6), AmpSumAhTocSeSe(3,6,6), AmpSum2AhTocSeSe(3,6,6) 
Complex(dp) :: AmpTreeZAhTocSeSe(3,6,6),AmpWaveZAhTocSeSe(3,6,6),AmpVertexZAhTocSeSe(3,6,6) 
Real(dp) :: AmpSqAhTocSeSe(3,6,6),  AmpSqTreeAhTocSeSe(3,6,6) 
Real(dp) :: MRPAhTocSuSu(3,6,6),MRGAhTocSuSu(3,6,6), MRPZAhTocSuSu(3,6,6),MRGZAhTocSuSu(3,6,6) 
Real(dp) :: MVPAhTocSuSu(3,6,6) 
Real(dp) :: RMsqTreeAhTocSuSu(3,6,6),RMsqWaveAhTocSuSu(3,6,6),RMsqVertexAhTocSuSu(3,6,6) 
Complex(dp) :: AmpTreeAhTocSuSu(3,6,6),AmpWaveAhTocSuSu(3,6,6)=(0._dp,0._dp),AmpVertexAhTocSuSu(3,6,6)& 
 & ,AmpVertexIRosAhTocSuSu(3,6,6),AmpVertexIRdrAhTocSuSu(3,6,6), AmpSumAhTocSuSu(3,6,6), AmpSum2AhTocSuSu(3,6,6) 
Complex(dp) :: AmpTreeZAhTocSuSu(3,6,6),AmpWaveZAhTocSuSu(3,6,6),AmpVertexZAhTocSuSu(3,6,6) 
Real(dp) :: AmpSqAhTocSuSu(3,6,6),  AmpSqTreeAhTocSuSu(3,6,6) 
Real(dp) :: MRPAhToAhVP(3,3),MRGAhToAhVP(3,3), MRPZAhToAhVP(3,3),MRGZAhToAhVP(3,3) 
Real(dp) :: MVPAhToAhVP(3,3) 
Real(dp) :: RMsqTreeAhToAhVP(3,3),RMsqWaveAhToAhVP(3,3),RMsqVertexAhToAhVP(3,3) 
Complex(dp) :: AmpTreeAhToAhVP(2,3,3),AmpWaveAhToAhVP(2,3,3)=(0._dp,0._dp),AmpVertexAhToAhVP(2,3,3)& 
 & ,AmpVertexIRosAhToAhVP(2,3,3),AmpVertexIRdrAhToAhVP(2,3,3), AmpSumAhToAhVP(2,3,3), AmpSum2AhToAhVP(2,3,3) 
Complex(dp) :: AmpTreeZAhToAhVP(2,3,3),AmpWaveZAhToAhVP(2,3,3),AmpVertexZAhToAhVP(2,3,3) 
Real(dp) :: AmpSqAhToAhVP(3,3),  AmpSqTreeAhToAhVP(3,3) 
Real(dp) :: MRPAhToAhVZ(3,3),MRGAhToAhVZ(3,3), MRPZAhToAhVZ(3,3),MRGZAhToAhVZ(3,3) 
Real(dp) :: MVPAhToAhVZ(3,3) 
Real(dp) :: RMsqTreeAhToAhVZ(3,3),RMsqWaveAhToAhVZ(3,3),RMsqVertexAhToAhVZ(3,3) 
Complex(dp) :: AmpTreeAhToAhVZ(2,3,3),AmpWaveAhToAhVZ(2,3,3)=(0._dp,0._dp),AmpVertexAhToAhVZ(2,3,3)& 
 & ,AmpVertexIRosAhToAhVZ(2,3,3),AmpVertexIRdrAhToAhVZ(2,3,3), AmpSumAhToAhVZ(2,3,3), AmpSum2AhToAhVZ(2,3,3) 
Complex(dp) :: AmpTreeZAhToAhVZ(2,3,3),AmpWaveZAhToAhVZ(2,3,3),AmpVertexZAhToAhVZ(2,3,3) 
Real(dp) :: AmpSqAhToAhVZ(3,3),  AmpSqTreeAhToAhVZ(3,3) 
Real(dp) :: MRPAhToFvcFv(3,3,3),MRGAhToFvcFv(3,3,3), MRPZAhToFvcFv(3,3,3),MRGZAhToFvcFv(3,3,3) 
Real(dp) :: MVPAhToFvcFv(3,3,3) 
Real(dp) :: RMsqTreeAhToFvcFv(3,3,3),RMsqWaveAhToFvcFv(3,3,3),RMsqVertexAhToFvcFv(3,3,3) 
Complex(dp) :: AmpTreeAhToFvcFv(2,3,3,3),AmpWaveAhToFvcFv(2,3,3,3)=(0._dp,0._dp),AmpVertexAhToFvcFv(2,3,3,3)& 
 & ,AmpVertexIRosAhToFvcFv(2,3,3,3),AmpVertexIRdrAhToFvcFv(2,3,3,3), AmpSumAhToFvcFv(2,3,3,3), AmpSum2AhToFvcFv(2,3,3,3) 
Complex(dp) :: AmpTreeZAhToFvcFv(2,3,3,3),AmpWaveZAhToFvcFv(2,3,3,3),AmpVertexZAhToFvcFv(2,3,3,3) 
Real(dp) :: AmpSqAhToFvcFv(3,3,3),  AmpSqTreeAhToFvcFv(3,3,3) 
Real(dp) :: MRPAhToGluGlu(3),MRGAhToGluGlu(3), MRPZAhToGluGlu(3),MRGZAhToGluGlu(3) 
Real(dp) :: MVPAhToGluGlu(3) 
Real(dp) :: RMsqTreeAhToGluGlu(3),RMsqWaveAhToGluGlu(3),RMsqVertexAhToGluGlu(3) 
Complex(dp) :: AmpTreeAhToGluGlu(2,3),AmpWaveAhToGluGlu(2,3)=(0._dp,0._dp),AmpVertexAhToGluGlu(2,3)& 
 & ,AmpVertexIRosAhToGluGlu(2,3),AmpVertexIRdrAhToGluGlu(2,3), AmpSumAhToGluGlu(2,3), AmpSum2AhToGluGlu(2,3) 
Complex(dp) :: AmpTreeZAhToGluGlu(2,3),AmpWaveZAhToGluGlu(2,3),AmpVertexZAhToGluGlu(2,3) 
Real(dp) :: AmpSqAhToGluGlu(3),  AmpSqTreeAhToGluGlu(3) 
Real(dp) :: MRPAhTohhVP(3,3),MRGAhTohhVP(3,3), MRPZAhTohhVP(3,3),MRGZAhTohhVP(3,3) 
Real(dp) :: MVPAhTohhVP(3,3) 
Real(dp) :: RMsqTreeAhTohhVP(3,3),RMsqWaveAhTohhVP(3,3),RMsqVertexAhTohhVP(3,3) 
Complex(dp) :: AmpTreeAhTohhVP(2,3,3),AmpWaveAhTohhVP(2,3,3)=(0._dp,0._dp),AmpVertexAhTohhVP(2,3,3)& 
 & ,AmpVertexIRosAhTohhVP(2,3,3),AmpVertexIRdrAhTohhVP(2,3,3), AmpSumAhTohhVP(2,3,3), AmpSum2AhTohhVP(2,3,3) 
Complex(dp) :: AmpTreeZAhTohhVP(2,3,3),AmpWaveZAhTohhVP(2,3,3),AmpVertexZAhTohhVP(2,3,3) 
Real(dp) :: AmpSqAhTohhVP(3,3),  AmpSqTreeAhTohhVP(3,3) 
Real(dp) :: MRPAhToSvcSv(3,3,3),MRGAhToSvcSv(3,3,3), MRPZAhToSvcSv(3,3,3),MRGZAhToSvcSv(3,3,3) 
Real(dp) :: MVPAhToSvcSv(3,3,3) 
Real(dp) :: RMsqTreeAhToSvcSv(3,3,3),RMsqWaveAhToSvcSv(3,3,3),RMsqVertexAhToSvcSv(3,3,3) 
Complex(dp) :: AmpTreeAhToSvcSv(3,3,3),AmpWaveAhToSvcSv(3,3,3)=(0._dp,0._dp),AmpVertexAhToSvcSv(3,3,3)& 
 & ,AmpVertexIRosAhToSvcSv(3,3,3),AmpVertexIRdrAhToSvcSv(3,3,3), AmpSumAhToSvcSv(3,3,3), AmpSum2AhToSvcSv(3,3,3) 
Complex(dp) :: AmpTreeZAhToSvcSv(3,3,3),AmpWaveZAhToSvcSv(3,3,3),AmpVertexZAhToSvcSv(3,3,3) 
Real(dp) :: AmpSqAhToSvcSv(3,3,3),  AmpSqTreeAhToSvcSv(3,3,3) 
Real(dp) :: MRPAhToVGVG(3),MRGAhToVGVG(3), MRPZAhToVGVG(3),MRGZAhToVGVG(3) 
Real(dp) :: MVPAhToVGVG(3) 
Real(dp) :: RMsqTreeAhToVGVG(3),RMsqWaveAhToVGVG(3),RMsqVertexAhToVGVG(3) 
Complex(dp) :: AmpTreeAhToVGVG(2,3),AmpWaveAhToVGVG(2,3)=(0._dp,0._dp),AmpVertexAhToVGVG(2,3)& 
 & ,AmpVertexIRosAhToVGVG(2,3),AmpVertexIRdrAhToVGVG(2,3), AmpSumAhToVGVG(2,3), AmpSum2AhToVGVG(2,3) 
Complex(dp) :: AmpTreeZAhToVGVG(2,3),AmpWaveZAhToVGVG(2,3),AmpVertexZAhToVGVG(2,3) 
Real(dp) :: AmpSqAhToVGVG(3),  AmpSqTreeAhToVGVG(3) 
Real(dp) :: MRPAhToVPVP(3),MRGAhToVPVP(3), MRPZAhToVPVP(3),MRGZAhToVPVP(3) 
Real(dp) :: MVPAhToVPVP(3) 
Real(dp) :: RMsqTreeAhToVPVP(3),RMsqWaveAhToVPVP(3),RMsqVertexAhToVPVP(3) 
Complex(dp) :: AmpTreeAhToVPVP(2,3),AmpWaveAhToVPVP(2,3)=(0._dp,0._dp),AmpVertexAhToVPVP(2,3)& 
 & ,AmpVertexIRosAhToVPVP(2,3),AmpVertexIRdrAhToVPVP(2,3), AmpSumAhToVPVP(2,3), AmpSum2AhToVPVP(2,3) 
Complex(dp) :: AmpTreeZAhToVPVP(2,3),AmpWaveZAhToVPVP(2,3),AmpVertexZAhToVPVP(2,3) 
Real(dp) :: AmpSqAhToVPVP(3),  AmpSqTreeAhToVPVP(3) 
Real(dp) :: MRPAhToVPVZ(3),MRGAhToVPVZ(3), MRPZAhToVPVZ(3),MRGZAhToVPVZ(3) 
Real(dp) :: MVPAhToVPVZ(3) 
Real(dp) :: RMsqTreeAhToVPVZ(3),RMsqWaveAhToVPVZ(3),RMsqVertexAhToVPVZ(3) 
Complex(dp) :: AmpTreeAhToVPVZ(2,3),AmpWaveAhToVPVZ(2,3)=(0._dp,0._dp),AmpVertexAhToVPVZ(2,3)& 
 & ,AmpVertexIRosAhToVPVZ(2,3),AmpVertexIRdrAhToVPVZ(2,3), AmpSumAhToVPVZ(2,3), AmpSum2AhToVPVZ(2,3) 
Complex(dp) :: AmpTreeZAhToVPVZ(2,3),AmpWaveZAhToVPVZ(2,3),AmpVertexZAhToVPVZ(2,3) 
Real(dp) :: AmpSqAhToVPVZ(3),  AmpSqTreeAhToVPVZ(3) 
Real(dp) :: MRPAhToVWmcVWm(3),MRGAhToVWmcVWm(3), MRPZAhToVWmcVWm(3),MRGZAhToVWmcVWm(3) 
Real(dp) :: MVPAhToVWmcVWm(3) 
Real(dp) :: RMsqTreeAhToVWmcVWm(3),RMsqWaveAhToVWmcVWm(3),RMsqVertexAhToVWmcVWm(3) 
Complex(dp) :: AmpTreeAhToVWmcVWm(2,3),AmpWaveAhToVWmcVWm(2,3)=(0._dp,0._dp),AmpVertexAhToVWmcVWm(2,3)& 
 & ,AmpVertexIRosAhToVWmcVWm(2,3),AmpVertexIRdrAhToVWmcVWm(2,3), AmpSumAhToVWmcVWm(2,3), AmpSum2AhToVWmcVWm(2,3) 
Complex(dp) :: AmpTreeZAhToVWmcVWm(2,3),AmpWaveZAhToVWmcVWm(2,3),AmpVertexZAhToVWmcVWm(2,3) 
Real(dp) :: AmpSqAhToVWmcVWm(3),  AmpSqTreeAhToVWmcVWm(3) 
Real(dp) :: MRPAhToVZVZ(3),MRGAhToVZVZ(3), MRPZAhToVZVZ(3),MRGZAhToVZVZ(3) 
Real(dp) :: MVPAhToVZVZ(3) 
Real(dp) :: RMsqTreeAhToVZVZ(3),RMsqWaveAhToVZVZ(3),RMsqVertexAhToVZVZ(3) 
Complex(dp) :: AmpTreeAhToVZVZ(2,3),AmpWaveAhToVZVZ(2,3)=(0._dp,0._dp),AmpVertexAhToVZVZ(2,3)& 
 & ,AmpVertexIRosAhToVZVZ(2,3),AmpVertexIRdrAhToVZVZ(2,3), AmpSumAhToVZVZ(2,3), AmpSum2AhToVZVZ(2,3) 
Complex(dp) :: AmpTreeZAhToVZVZ(2,3),AmpWaveZAhToVZVZ(2,3),AmpVertexZAhToVZVZ(2,3) 
Real(dp) :: AmpSqAhToVZVZ(3),  AmpSqTreeAhToVZVZ(3) 
Write(*,*) "Calculating one-loop decays of Ah " 
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
isave = 3

If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Ah Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhToAhAh(cplAhAhAh,MAh,MAh2,AmpTreeAhToAhAh)

  Else 
Call Amplitude_Tree_NMSSM_AhToAhAh(ZcplAhAhAh,MAh,MAh2,AmpTreeAhToAhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhToAhAh(MLambda,em,gs,cplAhAhAh,MAhOS,MRPAhToAhAh,             & 
& MRGAhToAhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhToAhAh(MLambda,em,gs,ZcplAhAhAh,MAhOS,MRPAhToAhAh,            & 
& MRGAhToAhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhToAhAh(MLambda,em,gs,cplAhAhAh,MAh,MRPAhToAhAh,               & 
& MRGAhToAhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhToAhAh(MLambda,em,gs,ZcplAhAhAh,MAh,MRPAhToAhAh,              & 
& MRGAhToAhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhToAhAh(cplAhAhAh,ctcplAhAhAh,MAh,MAh2,ZfAh,               & 
& AmpWaveAhToAhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,              & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplAhAhAhAh1,               & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa, & 
& AmpVertexAhToAhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplAhAhAhAh1,               & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa, & 
& AmpVertexIRdrAhToAhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToAhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& ZcplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,            & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplAhAhAhAh1,cplAhAhAhhh1,               & 
& cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,              & 
& AmpVertexIRosAhToAhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,ZcplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,         & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplAhAhAhAh1,               & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa, & 
& AmpVertexIRosAhToAhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToAhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplAhAhAhAh1,cplAhAhAhhh1,               & 
& cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,              & 
& AmpVertexIRosAhToAhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToAhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplAhAhAhAh1,               & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa, & 
& AmpVertexIRosAhToAhAh)

 End if 
 End if 
AmpVertexAhToAhAh = AmpVertexAhToAhAh -  AmpVertexIRdrAhToAhAh! +  AmpVertexIRosAhToAhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhToAhAh=0._dp 
AmpVertexZAhToAhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhToAhAh(gt2,:,:) = AmpWaveZAhToAhAh(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhToAhAh(gt1,:,:) 
AmpVertexZAhToAhAh(gt2,:,:)= AmpVertexZAhToAhAh(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhToAhAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhToAhAh=AmpWaveZAhToAhAh 
AmpVertexAhToAhAh= AmpVertexZAhToAhAh
! Final State 1 
AmpWaveZAhToAhAh=0._dp 
AmpVertexZAhToAhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhToAhAh(:,gt2,:) = AmpWaveZAhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWaveAhToAhAh(:,gt1,:) 
AmpVertexZAhToAhAh(:,gt2,:)= AmpVertexZAhToAhAh(:,gt2,:)+ZRUZA(gt2,gt1)*AmpVertexAhToAhAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhToAhAh=AmpWaveZAhToAhAh 
AmpVertexAhToAhAh= AmpVertexZAhToAhAh
! Final State 2 
AmpWaveZAhToAhAh=0._dp 
AmpVertexZAhToAhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=2,3
    Do gt3=gt2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTohhAh(cplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhAh)

  Else 
Call Amplitude_Tree_NMSSM_AhTohhAh(ZcplAhAhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTohhAh(MLambda,em,gs,cplAhAhhh,MAhOS,MhhOS,MRPAhTohhAh,       & 
& MRGAhTohhAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTohhAh(MLambda,em,gs,ZcplAhAhhh,MAhOS,MhhOS,MRPAhTohhAh,      & 
& MRGAhTohhAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTohhAh(MLambda,em,gs,cplAhAhhh,MAh,Mhh,MRPAhTohhAh,           & 
& MRGAhTohhAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTohhAh(MLambda,em,gs,ZcplAhAhhh,MAh,Mhh,MRPAhTohhAh,          & 
& MRGAhTohhAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTohhAh(cplAhAhhh,ctcplAhAhhh,MAh,MAh2,Mhh,Mhh2,           & 
& ZfAh,Zfhh,AmpWaveAhTohhAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,              & 
& MSd,MSe,MSu,MSv,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,              & 
& MSe2,MSu2,MSv2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,            & 
& cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,             & 
& cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,              & 
& cplAhhhSecSe1,cplAhhhSucSuaa,AmpVertexAhTohhAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,              & 
& MSe2,MSu2,MSv2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,            & 
& cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,             & 
& cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,              & 
& cplAhhhSecSe1,cplAhhhSucSuaa,AmpVertexIRdrAhTohhAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,        & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,MVWm2OS,               & 
& MVZ2OS,cplAhAhAh,ZcplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,    & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,       & 
& cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,               & 
& cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,cplAhhhSucSuaa,              & 
& AmpVertexIRosAhTohhAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,              & 
& MSe2,MSu2,MSv2,MVWm2,MVZ2,cplAhAhAh,ZcplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,            & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,            & 
& cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,             & 
& cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,              & 
& cplAhhhSecSe1,cplAhhhSucSuaa,AmpVertexIRosAhTohhAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhAh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,        & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,MVWm2OS,               & 
& MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,      & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,cplhhcHpmVWm,cplhhcVWmVWm,    & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhAhSdcSdaa,       & 
& cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,               & 
& cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,cplAhhhSucSuaa,              & 
& AmpVertexIRosAhTohhAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhAh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,              & 
& MSe2,MSu2,MSv2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,         & 
& cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,           & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,            & 
& cplAhAhHpmcHpm1,cplAhAhSdcSdaa,cplAhAhSecSe1,cplAhAhSucSuaa,cplAhAhSvcSv1,             & 
& cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,              & 
& cplAhhhSecSe1,cplAhhhSucSuaa,AmpVertexIRosAhTohhAh)

 End if 
 End if 
AmpVertexAhTohhAh = AmpVertexAhTohhAh -  AmpVertexIRdrAhTohhAh! +  AmpVertexIRosAhTohhAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTohhAh=0._dp 
AmpVertexZAhTohhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTohhAh(gt2,:,:) = AmpWaveZAhTohhAh(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTohhAh(gt1,:,:) 
AmpVertexZAhTohhAh(gt2,:,:)= AmpVertexZAhTohhAh(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTohhAh(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTohhAh=AmpWaveZAhTohhAh 
AmpVertexAhTohhAh= AmpVertexZAhTohhAh
! Final State 1 
AmpWaveZAhTohhAh=0._dp 
AmpVertexZAhTohhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTohhAh(:,gt2,:) = AmpWaveZAhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWaveAhTohhAh(:,gt1,:) 
AmpVertexZAhTohhAh(:,gt2,:)= AmpVertexZAhTohhAh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexAhTohhAh(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTohhAh=AmpWaveZAhTohhAh 
AmpVertexAhTohhAh= AmpVertexZAhTohhAh
! Final State 2 
AmpWaveZAhTohhAh=0._dp 
AmpVertexZAhTohhAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Cha) Cha
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocChaCha(cplcChaChaAhL,cplcChaChaAhR,MAh,MCha,           & 
& MAh2,MCha2,AmpTreeAhTocChaCha)

  Else 
Call Amplitude_Tree_NMSSM_AhTocChaCha(ZcplcChaChaAhL,ZcplcChaChaAhR,MAh,              & 
& MCha,MAh2,MCha2,AmpTreeAhTocChaCha)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocChaCha(MLambda,em,gs,cplcChaChaAhL,cplcChaChaAhR,          & 
& MAhOS,MChaOS,MRPAhTocChaCha,MRGAhTocChaCha)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocChaCha(MLambda,em,gs,ZcplcChaChaAhL,ZcplcChaChaAhR,        & 
& MAhOS,MChaOS,MRPAhTocChaCha,MRGAhTocChaCha)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocChaCha(MLambda,em,gs,cplcChaChaAhL,cplcChaChaAhR,          & 
& MAh,MCha,MRPAhTocChaCha,MRGAhTocChaCha)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocChaCha(MLambda,em,gs,ZcplcChaChaAhL,ZcplcChaChaAhR,        & 
& MAh,MCha,MRPAhTocChaCha,MRGAhTocChaCha)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocChaCha(cplcChaChaAhL,cplcChaChaAhR,ctcplcChaChaAhL,    & 
& ctcplcChaChaAhR,MAh,MAh2,MCha,MCha2,ZfAh,ZfLm,ZfLp,AmpWaveAhTocChaCha)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocChaCha(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,               & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,      & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,       & 
& cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,       & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,AmpVertexAhTocChaCha)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocChaCha(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,      & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,       & 
& cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,       & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,AmpVertexIRdrAhTocChaCha)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocChaCha(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,ZcplcChaChaAhL,ZcplcChaChaAhR,cplChiChiAhL,    & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,   & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,       & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,cplcChaChaVPR,       & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,              & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcChacFuSdL,  & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,AmpVertexIRosAhTocChaCha)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocChaCha(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,ZcplcChaChaAhL,ZcplcChaChaAhR, & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,      & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,       & 
& cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,       & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,AmpVertexIRosAhTocChaCha)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocChaCha(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,   & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,       & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,cplcChaChaVPR,       & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,              & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcChacFuSdL,  & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,AmpVertexIRosAhTocChaCha)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocChaCha(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,      & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,       & 
& cplChiChacVWmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,       & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,AmpVertexIRosAhTocChaCha)

 End if 
 End if 
AmpVertexAhTocChaCha = AmpVertexAhTocChaCha -  AmpVertexIRdrAhTocChaCha! +  AmpVertexIRosAhTocChaCha ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocChaCha=0._dp 
AmpVertexZAhTocChaCha=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocChaCha(:,gt2,:,:) = AmpWaveZAhTocChaCha(:,gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocChaCha(:,gt1,:,:) 
AmpVertexZAhTocChaCha(:,gt2,:,:)= AmpVertexZAhTocChaCha(:,gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocChaCha(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocChaCha=AmpWaveZAhTocChaCha 
AmpVertexAhTocChaCha= AmpVertexZAhTocChaCha
! Final State 1 
AmpWaveZAhTocChaCha=0._dp 
AmpVertexZAhTocChaCha=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocChaCha(1,:,gt2,:) = AmpWaveZAhTocChaCha(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpWaveAhTocChaCha(1,:,gt1,:) 
AmpVertexZAhTocChaCha(1,:,gt2,:)= AmpVertexZAhTocChaCha(1,:,gt2,:)+ZRUUP(gt2,gt1)*AmpVertexAhTocChaCha(1,:,gt1,:) 
AmpWaveZAhTocChaCha(2,:,gt2,:) = AmpWaveZAhTocChaCha(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpWaveAhTocChaCha(2,:,gt1,:) 
AmpVertexZAhTocChaCha(2,:,gt2,:)= AmpVertexZAhTocChaCha(2,:,gt2,:)+ZRUUMc(gt2,gt1)*AmpVertexAhTocChaCha(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocChaCha=AmpWaveZAhTocChaCha 
AmpVertexAhTocChaCha= AmpVertexZAhTocChaCha
! Final State 2 
AmpWaveZAhTocChaCha=0._dp 
AmpVertexZAhTocChaCha=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocChaCha(1,:,:,gt2) = AmpWaveZAhTocChaCha(1,:,:,gt2)+ZRUUM(gt2,gt1)*AmpWaveAhTocChaCha(1,:,:,gt1) 
AmpVertexZAhTocChaCha(1,:,:,gt2)= AmpVertexZAhTocChaCha(1,:,:,gt2)+ZRUUM(gt2,gt1)*AmpVertexAhTocChaCha(1,:,:,gt1) 
AmpWaveZAhTocChaCha(2,:,:,gt2) = AmpWaveZAhTocChaCha(2,:,:,gt2)+ZRUUP(gt2,gt1)*AmpWaveAhTocChaCha(2,:,:,gt1) 
AmpVertexZAhTocChaCha(2,:,:,gt2)= AmpVertexZAhTocChaCha(2,:,:,gt2)+ZRUUP(gt2,gt1)*AmpVertexAhTocChaCha(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocChaCha=AmpWaveZAhTocChaCha 
AmpVertexAhTocChaCha= AmpVertexZAhTocChaCha
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocChaCha = AmpVertexAhTocChaCha  +  AmpVertexIRosAhTocChaCha
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->bar[Cha] Cha -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocChaCha = AmpTreeAhTocChaCha 
 AmpSum2AhTocChaCha = AmpTreeAhTocChaCha + 2._dp*AmpWaveAhTocChaCha + 2._dp*AmpVertexAhTocChaCha  
Else 
 AmpSumAhTocChaCha = AmpTreeAhTocChaCha + AmpWaveAhTocChaCha + AmpVertexAhTocChaCha
 AmpSum2AhTocChaCha = AmpTreeAhTocChaCha + AmpWaveAhTocChaCha + AmpVertexAhTocChaCha 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocChaCha = AmpTreeAhTocChaCha
 AmpSum2AhTocChaCha = AmpTreeAhTocChaCha 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,2
    Do gt3=1,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MChaOS(gt2))+Abs(MChaOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MCha(gt2))+Abs(MCha(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocChaCha = AmpTreeAhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MCha(gt2),MCha(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocChaCha(gt1, gt2, gt3) 
  AmpSum2AhTocChaCha = 2._dp*AmpWaveAhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MCha(gt2),MCha(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocChaCha(gt1, gt2, gt3) 
  AmpSum2AhTocChaCha = 2._dp*AmpVertexAhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MCha(gt2),MCha(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocChaCha(gt1, gt2, gt3) 
  AmpSum2AhTocChaCha = AmpTreeAhTocChaCha + 2._dp*AmpWaveAhTocChaCha + 2._dp*AmpVertexAhTocChaCha
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MCha(gt2),MCha(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocChaCha(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocChaCha = AmpTreeAhTocChaCha
  Call SquareAmp_StoFF(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
  AmpSqTreeAhTocChaCha(gt1, gt2, gt3) = AmpSqAhTocChaCha(gt1, gt2, gt3)  
  AmpSum2AhTocChaCha = + 2._dp*AmpWaveAhTocChaCha + 2._dp*AmpVertexAhTocChaCha
  Call SquareAmp_StoFF(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
  AmpSqAhTocChaCha(gt1, gt2, gt3) = AmpSqAhTocChaCha(gt1, gt2, gt3) + AmpSqTreeAhTocChaCha(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocChaCha = AmpTreeAhTocChaCha
  Call SquareAmp_StoFF(MAh(gt1),MCha(gt2),MCha(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
  AmpSqTreeAhTocChaCha(gt1, gt2, gt3) = AmpSqAhTocChaCha(gt1, gt2, gt3)  
  AmpSum2AhTocChaCha = + 2._dp*AmpWaveAhTocChaCha + 2._dp*AmpVertexAhTocChaCha
  Call SquareAmp_StoFF(MAh(gt1),MCha(gt2),MCha(gt3),AmpSumAhTocChaCha(:,gt1, gt2, gt3),AmpSum2AhTocChaCha(:,gt1, gt2, gt3),AmpSqAhTocChaCha(gt1, gt2, gt3)) 
  AmpSqAhTocChaCha(gt1, gt2, gt3) = AmpSqAhTocChaCha(gt1, gt2, gt3) + AmpSqTreeAhTocChaCha(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocChaCha(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqAhTocChaCha(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MChaOS(gt2),MChaOS(gt3),helfactor*AmpSqAhTocChaCha(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MCha(gt2),MCha(gt3),helfactor*AmpSqAhTocChaCha(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocChaCha(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocChaCha(gt1, gt2, gt3) + MRGAhTocChaCha(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocChaCha(gt1, gt2, gt3) + MRGAhTocChaCha(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
Call Amplitude_Tree_NMSSM_AhToChiChi(cplChiChiAhL,cplChiChiAhR,MAh,MChi,              & 
& MAh2,MChi2,AmpTreeAhToChiChi)

  Else 
Call Amplitude_Tree_NMSSM_AhToChiChi(ZcplChiChiAhL,ZcplChiChiAhR,MAh,MChi,            & 
& MAh2,MChi2,AmpTreeAhToChiChi)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhToChiChi(MLambda,em,gs,cplChiChiAhL,cplChiChiAhR,             & 
& MAhOS,MChiOS,MRPAhToChiChi,MRGAhToChiChi)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhToChiChi(MLambda,em,gs,ZcplChiChiAhL,ZcplChiChiAhR,           & 
& MAhOS,MChiOS,MRPAhToChiChi,MRGAhToChiChi)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhToChiChi(MLambda,em,gs,cplChiChiAhL,cplChiChiAhR,             & 
& MAh,MChi,MRPAhToChiChi,MRGAhToChiChi)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhToChiChi(MLambda,em,gs,ZcplChiChiAhL,ZcplChiChiAhR,           & 
& MAh,MChi,MRPAhToChiChi,MRGAhToChiChi)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhToChiChi(cplChiChiAhL,cplChiChiAhR,ctcplChiChiAhL,        & 
& ctcplChiChiAhR,MAh,MAh2,MChi,MChi2,ZfAh,ZfL0,AmpWaveAhToChiChi)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToChiChi(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,            & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,   & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexAhToChiChi)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhToChiChi(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,             & 
& MSe2,MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,     & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,   & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRdrAhToChiChi)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToChiChi(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,            & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,ZcplChiChiAhL,ZcplChiChiAhR,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,              & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRosAhToChiChi)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToChiChi(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,             & 
& MSe2,MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,ZcplChiChiAhL,    & 
& ZcplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,             & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,   & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRosAhToChiChi)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToChiChi(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,            & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,              & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRosAhToChiChi)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToChiChi(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,             & 
& MSe2,MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,     & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,   & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRosAhToChiChi)

 End if 
 End if 
AmpVertexAhToChiChi = AmpVertexAhToChiChi -  AmpVertexIRdrAhToChiChi! +  AmpVertexIRosAhToChiChi ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhToChiChi=0._dp 
AmpVertexZAhToChiChi=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhToChiChi(:,gt2,:,:) = AmpWaveZAhToChiChi(:,gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhToChiChi(:,gt1,:,:) 
AmpVertexZAhToChiChi(:,gt2,:,:)= AmpVertexZAhToChiChi(:,gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhToChiChi(:,gt1,:,:) 
 End Do 
End Do 
AmpWaveAhToChiChi=AmpWaveZAhToChiChi 
AmpVertexAhToChiChi= AmpVertexZAhToChiChi
! Final State 1 
AmpWaveZAhToChiChi=0._dp 
AmpVertexZAhToChiChi=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZAhToChiChi(1,:,gt2,:) = AmpWaveZAhToChiChi(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveAhToChiChi(1,:,gt1,:) 
AmpVertexZAhToChiChi(1,:,gt2,:)= AmpVertexZAhToChiChi(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpVertexAhToChiChi(1,:,gt1,:) 
AmpWaveZAhToChiChi(2,:,gt2,:) = AmpWaveZAhToChiChi(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveAhToChiChi(2,:,gt1,:) 
AmpVertexZAhToChiChi(2,:,gt2,:)= AmpVertexZAhToChiChi(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpVertexAhToChiChi(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhToChiChi=AmpWaveZAhToChiChi 
AmpVertexAhToChiChi= AmpVertexZAhToChiChi
! Final State 2 
AmpWaveZAhToChiChi=0._dp 
AmpVertexZAhToChiChi=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZAhToChiChi(1,:,:,gt2) = AmpWaveZAhToChiChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveAhToChiChi(1,:,:,gt1) 
AmpVertexZAhToChiChi(1,:,:,gt2)= AmpVertexZAhToChiChi(1,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexAhToChiChi(1,:,:,gt1) 
AmpWaveZAhToChiChi(2,:,:,gt2) = AmpWaveZAhToChiChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveAhToChiChi(2,:,:,gt1) 
AmpVertexZAhToChiChi(2,:,:,gt2)= AmpVertexZAhToChiChi(2,:,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexAhToChiChi(2,:,:,gt1) 
 End Do 
End Do 
AmpWaveAhToChiChi=AmpWaveZAhToChiChi 
AmpVertexAhToChiChi= AmpVertexZAhToChiChi
End if
If (ShiftIRdiv) Then 
AmpVertexAhToChiChi = AmpVertexAhToChiChi  +  AmpVertexIRosAhToChiChi
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Chi Chi -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhToChiChi = AmpTreeAhToChiChi 
 AmpSum2AhToChiChi = AmpTreeAhToChiChi + 2._dp*AmpWaveAhToChiChi + 2._dp*AmpVertexAhToChiChi  
Else 
 AmpSumAhToChiChi = AmpTreeAhToChiChi + AmpWaveAhToChiChi + AmpVertexAhToChiChi
 AmpSum2AhToChiChi = AmpTreeAhToChiChi + AmpWaveAhToChiChi + AmpVertexAhToChiChi 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToChiChi = AmpTreeAhToChiChi
 AmpSum2AhToChiChi = AmpTreeAhToChiChi 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,5
    Do gt3=gt2,5
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MChiOS(gt2))+Abs(MChiOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MChi(gt2))+Abs(MChi(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhToChiChi = AmpTreeAhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MChi(gt2),MChi(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhToChiChi(gt1, gt2, gt3) 
  AmpSum2AhToChiChi = 2._dp*AmpWaveAhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MChi(gt2),MChi(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhToChiChi(gt1, gt2, gt3) 
  AmpSum2AhToChiChi = 2._dp*AmpVertexAhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MChi(gt2),MChi(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhToChiChi(gt1, gt2, gt3) 
  AmpSum2AhToChiChi = AmpTreeAhToChiChi + 2._dp*AmpWaveAhToChiChi + 2._dp*AmpVertexAhToChiChi
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MChi(gt2),MChi(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhToChiChi(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhToChiChi = AmpTreeAhToChiChi
  Call SquareAmp_StoFF(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
  AmpSqTreeAhToChiChi(gt1, gt2, gt3) = AmpSqAhToChiChi(gt1, gt2, gt3)  
  AmpSum2AhToChiChi = + 2._dp*AmpWaveAhToChiChi + 2._dp*AmpVertexAhToChiChi
  Call SquareAmp_StoFF(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
  AmpSqAhToChiChi(gt1, gt2, gt3) = AmpSqAhToChiChi(gt1, gt2, gt3) + AmpSqTreeAhToChiChi(gt1, gt2, gt3)  
Else  
  AmpSum2AhToChiChi = AmpTreeAhToChiChi
  Call SquareAmp_StoFF(MAh(gt1),MChi(gt2),MChi(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
  AmpSqTreeAhToChiChi(gt1, gt2, gt3) = AmpSqAhToChiChi(gt1, gt2, gt3)  
  AmpSum2AhToChiChi = + 2._dp*AmpWaveAhToChiChi + 2._dp*AmpVertexAhToChiChi
  Call SquareAmp_StoFF(MAh(gt1),MChi(gt2),MChi(gt3),AmpSumAhToChiChi(:,gt1, gt2, gt3),AmpSum2AhToChiChi(:,gt1, gt2, gt3),AmpSqAhToChiChi(gt1, gt2, gt3)) 
  AmpSqAhToChiChi(gt1, gt2, gt3) = AmpSqAhToChiChi(gt1, gt2, gt3) + AmpSqTreeAhToChiChi(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhToChiChi(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (gt2.ne.gt3) helfactor = 2._dp*helfactor 
If (AmpSqAhToChiChi(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp/2._dp*GammaTPS(MAhOS(gt1),MChiOS(gt2),MChiOS(gt3),helfactor*AmpSqAhToChiChi(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp/2._dp*GammaTPS(MAh(gt1),MChi(gt2),MChi(gt3),helfactor*AmpSqAhToChiChi(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhToChiChi(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp/4._dp*helfactor*(MRPAhToChiChi(gt1, gt2, gt3) + MRGAhToChiChi(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*1._dp/4._dp*helfactor*(MRPAhToChiChi(gt1, gt2, gt3) + MRGAhToChiChi(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
Call Amplitude_Tree_NMSSM_AhTocFdFd(cplcFdFdAhL,cplcFdFdAhR,MAh,MFd,MAh2,             & 
& MFd2,AmpTreeAhTocFdFd)

  Else 
Call Amplitude_Tree_NMSSM_AhTocFdFd(ZcplcFdFdAhL,ZcplcFdFdAhR,MAh,MFd,MAh2,           & 
& MFd2,AmpTreeAhTocFdFd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocFdFd(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,MAhOS,          & 
& MFdOS,MRPAhTocFdFd,MRGAhTocFdFd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocFdFd(MLambda,em,gs,ZcplcFdFdAhL,ZcplcFdFdAhR,              & 
& MAhOS,MFdOS,MRPAhTocFdFd,MRGAhTocFdFd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocFdFd(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,MAh,            & 
& MFd,MRPAhTocFdFd,MRGAhTocFdFd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocFdFd(MLambda,em,gs,ZcplcFdFdAhL,ZcplcFdFdAhR,              & 
& MAh,MFd,MRPAhTocFdFd,MRGAhTocFdFd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocFdFd(cplcFdFdAhL,cplcFdFdAhR,ctcplcFdFdAhL,            & 
& ctcplcFdFdAhR,MAh,MAh2,MFd,MFd2,ZfAh,ZfFDL,ZfFDR,AmpWaveAhTocFdFd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocFdFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHpmL,cplcFdFuHpmR,     & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,AmpVertexAhTocFdFd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFdFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHpmL,cplcFdFuHpmR,     & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,AmpVertexIRdrAhTocFdFd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFdFd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& ZcplcFdFdAhL,ZcplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,    & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,             & 
& cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,       & 
& cplcFdGluSdL,cplcFdGluSdR,AmpVertexIRosAhTocFdFd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFdFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,ZcplcFdFdAhL,ZcplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHpmL,cplcFdFuHpmR,     & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,AmpVertexIRosAhTocFdFd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFdFd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,      & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,             & 
& cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,       & 
& cplcFdGluSdL,cplcFdGluSdR,AmpVertexIRosAhTocFdFd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFdFd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplcFdChaSuL,cplcFdChaSuR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,           & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHpmL,cplcFdFuHpmR,     & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,AmpVertexIRosAhTocFdFd)

 End if 
 End if 
AmpVertexAhTocFdFd = AmpVertexAhTocFdFd -  AmpVertexIRdrAhTocFdFd! +  AmpVertexIRosAhTocFdFd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocFdFd=0._dp 
AmpVertexZAhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
AmpWaveZAhTocFdFd(1,:,gt2,:) = AmpWaveZAhTocFdFd(1,:,gt2,:)+ZRUZDR(gt2,gt1)*AmpWaveAhTocFdFd(1,:,gt1,:) 
AmpVertexZAhTocFdFd(1,:,gt2,:)= AmpVertexZAhTocFdFd(1,:,gt2,:)+ZRUZDR(gt2,gt1)*AmpVertexAhTocFdFd(1,:,gt1,:) 
AmpWaveZAhTocFdFd(2,:,gt2,:) = AmpWaveZAhTocFdFd(2,:,gt2,:)+ZRUZDLc(gt2,gt1)*AmpWaveAhTocFdFd(2,:,gt1,:) 
AmpVertexZAhTocFdFd(2,:,gt2,:)= AmpVertexZAhTocFdFd(2,:,gt2,:)+ZRUZDLc(gt2,gt1)*AmpVertexAhTocFdFd(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocFdFd=AmpWaveZAhTocFdFd 
AmpVertexAhTocFdFd= AmpVertexZAhTocFdFd
! Final State 2 
AmpWaveZAhTocFdFd=0._dp 
AmpVertexZAhTocFdFd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFdFd(1,:,:,gt2) = AmpWaveZAhTocFdFd(1,:,:,gt2)+ZRUZDL(gt2,gt1)*AmpWaveAhTocFdFd(1,:,:,gt1) 
AmpVertexZAhTocFdFd(1,:,:,gt2)= AmpVertexZAhTocFdFd(1,:,:,gt2)+ZRUZDL(gt2,gt1)*AmpVertexAhTocFdFd(1,:,:,gt1) 
AmpWaveZAhTocFdFd(2,:,:,gt2) = AmpWaveZAhTocFdFd(2,:,:,gt2)+ZRUZDR(gt2,gt1)*AmpWaveAhTocFdFd(2,:,:,gt1) 
AmpVertexZAhTocFdFd(2,:,:,gt2)= AmpVertexZAhTocFdFd(2,:,:,gt2)+ZRUZDR(gt2,gt1)*AmpVertexAhTocFdFd(2,:,:,gt1) 
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
Do gt1=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fe) Fe
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocFeFe(cplcFeFeAhL,cplcFeFeAhR,MAh,MFe,MAh2,             & 
& MFe2,AmpTreeAhTocFeFe)

  Else 
Call Amplitude_Tree_NMSSM_AhTocFeFe(ZcplcFeFeAhL,ZcplcFeFeAhR,MAh,MFe,MAh2,           & 
& MFe2,AmpTreeAhTocFeFe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocFeFe(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,MAhOS,          & 
& MFeOS,MRPAhTocFeFe,MRGAhTocFeFe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocFeFe(MLambda,em,gs,ZcplcFeFeAhL,ZcplcFeFeAhR,              & 
& MAhOS,MFeOS,MRPAhTocFeFe,MRGAhTocFeFe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocFeFe(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,MAh,            & 
& MFe,MRPAhTocFeFe,MRGAhTocFeFe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocFeFe(MLambda,em,gs,ZcplcFeFeAhL,ZcplcFeFeAhR,              & 
& MAh,MFe,MRPAhTocFeFe,MRGAhTocFeFe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocFeFe(cplcFeFeAhL,cplcFeFeAhR,ctcplcFeFeAhL,            & 
& ctcplcFeFeAhR,MAh,MAh2,MFe,MFe2,ZfAh,ZfFEL,ZfFER,AmpWaveAhTocFeFe)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocFeFe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSe,MSv,             & 
& MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSe2,MSv2,MVP2,MVWm2,MVZ2,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,      & 
& cplAhcHpmVWm,cplcFeChaSvL,cplcFeChaSvR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,         & 
& cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,              & 
& cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexAhTocFeFe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFeFe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSe,              & 
& MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSe2,MSv2,MVP2,MVWm2,MVZ2,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,      & 
& cplAhcHpmVWm,cplcFeChaSvL,cplcFeChaSvR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,         & 
& cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,              & 
& cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRdrAhTocFeFe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFeFe(MAhOS,MChaOS,MChiOS,MFeOS,MhhOS,             & 
& MHpmOS,MSeOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,Mhh2OS,              & 
& MHpm2OS,MSe2OS,MSv2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,ZcplcFeFeAhL,ZcplcFeFeAhR,cplAhhhhh,           & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,cplAhcHpmVWm,cplcFeChaSvL,              & 
& cplcFeChaSvR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,          & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcChaFecSvL,             & 
& cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,    & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosAhTocFeFe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFeFe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSe,              & 
& MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSe2,MSv2,MVP2,MVWm2,MVZ2,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& ZcplcFeFeAhL,ZcplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,               & 
& cplAhSecSe,cplAhcHpmVWm,cplcFeChaSvL,cplcFeChaSvR,cplChiFecSeL,cplChiFecSeR,           & 
& cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,       & 
& AmpVertexIRosAhTocFeFe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFeFe(MAhOS,MChaOS,MChiOS,MFeOS,MhhOS,             & 
& MHpmOS,MSeOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,Mhh2OS,              & 
& MHpm2OS,MSe2OS,MSv2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,             & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,cplAhcHpmVWm,cplcFeChaSvL,              & 
& cplcFeChaSvR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,          & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcChaFecSvL,             & 
& cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,    & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosAhTocFeFe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFeFe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSe,              & 
& MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSe2,MSv2,MVP2,MVWm2,MVZ2,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,      & 
& cplAhcHpmVWm,cplcFeChaSvL,cplcFeChaSvR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,         & 
& cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,              & 
& cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,AmpVertexIRosAhTocFeFe)

 End if 
 End if 
AmpVertexAhTocFeFe = AmpVertexAhTocFeFe -  AmpVertexIRdrAhTocFeFe! +  AmpVertexIRosAhTocFeFe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocFeFe=0._dp 
AmpVertexZAhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
AmpWaveZAhTocFeFe(1,:,gt2,:) = AmpWaveZAhTocFeFe(1,:,gt2,:)+ZRUZER(gt2,gt1)*AmpWaveAhTocFeFe(1,:,gt1,:) 
AmpVertexZAhTocFeFe(1,:,gt2,:)= AmpVertexZAhTocFeFe(1,:,gt2,:)+ZRUZER(gt2,gt1)*AmpVertexAhTocFeFe(1,:,gt1,:) 
AmpWaveZAhTocFeFe(2,:,gt2,:) = AmpWaveZAhTocFeFe(2,:,gt2,:)+ZRUZELc(gt2,gt1)*AmpWaveAhTocFeFe(2,:,gt1,:) 
AmpVertexZAhTocFeFe(2,:,gt2,:)= AmpVertexZAhTocFeFe(2,:,gt2,:)+ZRUZELc(gt2,gt1)*AmpVertexAhTocFeFe(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocFeFe=AmpWaveZAhTocFeFe 
AmpVertexAhTocFeFe= AmpVertexZAhTocFeFe
! Final State 2 
AmpWaveZAhTocFeFe=0._dp 
AmpVertexZAhTocFeFe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFeFe(1,:,:,gt2) = AmpWaveZAhTocFeFe(1,:,:,gt2)+ZRUZEL(gt2,gt1)*AmpWaveAhTocFeFe(1,:,:,gt1) 
AmpVertexZAhTocFeFe(1,:,:,gt2)= AmpVertexZAhTocFeFe(1,:,:,gt2)+ZRUZEL(gt2,gt1)*AmpVertexAhTocFeFe(1,:,:,gt1) 
AmpWaveZAhTocFeFe(2,:,:,gt2) = AmpWaveZAhTocFeFe(2,:,:,gt2)+ZRUZER(gt2,gt1)*AmpWaveAhTocFeFe(2,:,:,gt1) 
AmpVertexZAhTocFeFe(2,:,:,gt2)= AmpVertexZAhTocFeFe(2,:,:,gt2)+ZRUZER(gt2,gt1)*AmpVertexAhTocFeFe(2,:,:,gt1) 
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
Do gt1=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! bar(Fu) Fu
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocFuFu(cplcFuFuAhL,cplcFuFuAhR,MAh,MFu,MAh2,             & 
& MFu2,AmpTreeAhTocFuFu)

  Else 
Call Amplitude_Tree_NMSSM_AhTocFuFu(ZcplcFuFuAhL,ZcplcFuFuAhR,MAh,MFu,MAh2,           & 
& MFu2,AmpTreeAhTocFuFu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocFuFu(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,MAhOS,          & 
& MFuOS,MRPAhTocFuFu,MRGAhTocFuFu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocFuFu(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,              & 
& MAhOS,MFuOS,MRPAhTocFuFu,MRGAhTocFuFu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocFuFu(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,MAh,            & 
& MFu,MRPAhTocFuFu,MRGAhTocFuFu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocFuFu(MLambda,em,gs,ZcplcFuFuAhL,ZcplcFuFuAhR,              & 
& MAh,MFu,MRPAhTocFuFu,MRGAhTocFuFu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocFuFu(cplcFuFuAhL,cplcFuFuAhR,ctcplcFuFuAhL,            & 
& ctcplcFuFuAhR,MAh,MAh2,MFu,MFu2,ZfAh,ZfFUL,ZfFUR,AmpWaveAhTocFuFu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocFuFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexAhTocFuFu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFuFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRdrAhTocFuFu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFuFu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,    & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,             & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosAhTocFuFu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFuFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,ZcplcFuFuAhL,ZcplcFuFuAhR,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosAhTocFuFu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFuFu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,      & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,             & 
& cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,           & 
& cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosAhTocFuFu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocFuFu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSucSu,cplAhcHpmVWm,      & 
& cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,cplcFuChiSuR,         & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,AmpVertexIRosAhTocFuFu)

 End if 
 End if 
AmpVertexAhTocFuFu = AmpVertexAhTocFuFu -  AmpVertexIRdrAhTocFuFu! +  AmpVertexIRosAhTocFuFu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocFuFu=0._dp 
AmpVertexZAhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
AmpWaveZAhTocFuFu(1,:,gt2,:) = AmpWaveZAhTocFuFu(1,:,gt2,:)+ZRUZUR(gt2,gt1)*AmpWaveAhTocFuFu(1,:,gt1,:) 
AmpVertexZAhTocFuFu(1,:,gt2,:)= AmpVertexZAhTocFuFu(1,:,gt2,:)+ZRUZUR(gt2,gt1)*AmpVertexAhTocFuFu(1,:,gt1,:) 
AmpWaveZAhTocFuFu(2,:,gt2,:) = AmpWaveZAhTocFuFu(2,:,gt2,:)+ZRUZULc(gt2,gt1)*AmpWaveAhTocFuFu(2,:,gt1,:) 
AmpVertexZAhTocFuFu(2,:,gt2,:)= AmpVertexZAhTocFuFu(2,:,gt2,:)+ZRUZULc(gt2,gt1)*AmpVertexAhTocFuFu(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocFuFu=AmpWaveZAhTocFuFu 
AmpVertexAhTocFuFu= AmpVertexZAhTocFuFu
! Final State 2 
AmpWaveZAhTocFuFu=0._dp 
AmpVertexZAhTocFuFu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocFuFu(1,:,:,gt2) = AmpWaveZAhTocFuFu(1,:,:,gt2)+ZRUZUL(gt2,gt1)*AmpWaveAhTocFuFu(1,:,:,gt1) 
AmpVertexZAhTocFuFu(1,:,:,gt2)= AmpVertexZAhTocFuFu(1,:,:,gt2)+ZRUZUL(gt2,gt1)*AmpVertexAhTocFuFu(1,:,:,gt1) 
AmpWaveZAhTocFuFu(2,:,:,gt2) = AmpWaveZAhTocFuFu(2,:,:,gt2)+ZRUZUR(gt2,gt1)*AmpWaveAhTocFuFu(2,:,:,gt1) 
AmpVertexZAhTocFuFu(2,:,:,gt2)= AmpVertexZAhTocFuFu(2,:,:,gt2)+ZRUZUR(gt2,gt1)*AmpVertexAhTocFuFu(2,:,:,gt1) 
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
Do gt1=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTohhhh(cplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhhh)

  Else 
Call Amplitude_Tree_NMSSM_AhTohhhh(ZcplAhhhhh,MAh,Mhh,MAh2,Mhh2,AmpTreeAhTohhhh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTohhhh(MLambda,em,gs,cplAhhhhh,MAhOS,MhhOS,MRPAhTohhhh,       & 
& MRGAhTohhhh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTohhhh(MLambda,em,gs,ZcplAhhhhh,MAhOS,MhhOS,MRPAhTohhhh,      & 
& MRGAhTohhhh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTohhhh(MLambda,em,gs,cplAhhhhh,MAh,Mhh,MRPAhTohhhh,           & 
& MRGAhTohhhh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTohhhh(MLambda,em,gs,ZcplAhhhhh,MAh,Mhh,MRPAhTohhhh,          & 
& MRGAhTohhhh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTohhhh(cplAhhhhh,ctcplAhhhhh,MAh,MAh2,Mhh,Mhh2,           & 
& ZfAh,Zfhh,AmpWaveAhTohhhh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,              & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,             & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,    & 
& cplAhhhSecSe1,cplAhhhSucSuaa,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,              & 
& cplhhhhSecSe1,cplhhhhSucSuaa,AmpVertexAhTohhhh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,             & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,    & 
& cplAhhhSecSe1,cplAhhhSucSuaa,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,              & 
& cplhhhhSecSe1,cplhhhhSucSuaa,AmpVertexIRdrAhTohhhh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhhh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,            & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,               & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,   & 
& cplAhhhSucSuaa,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,cplhhhhSecSe1,              & 
& cplhhhhSucSuaa,AmpVertexIRosAhTohhhh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,ZcplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,             & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,             & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,    & 
& cplAhhhSecSe1,cplAhhhSucSuaa,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,              & 
& cplhhhhSecSe1,cplhhhhSucSuaa,AmpVertexIRosAhTohhhh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhhh(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,               & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,cplAhhhSecSe1,   & 
& cplAhhhSucSuaa,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,cplhhhhSecSe1,              & 
& cplhhhhSucSuaa,AmpVertexIRosAhTohhhh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhhh(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,           & 
& cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,cplcgWpCgWpChh,cplhhhhhh,             & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplAhhhSdcSdaa,    & 
& cplAhhhSecSe1,cplAhhhSucSuaa,cplhhhhhhhh1,cplhhhhHpmcHpm1,cplhhhhSdcSdaa,              & 
& cplhhhhSecSe1,cplhhhhSucSuaa,AmpVertexIRosAhTohhhh)

 End if 
 End if 
AmpVertexAhTohhhh = AmpVertexAhTohhhh -  AmpVertexIRdrAhTohhhh! +  AmpVertexIRosAhTohhhh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTohhhh=0._dp 
AmpVertexZAhTohhhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTohhhh(gt2,:,:) = AmpWaveZAhTohhhh(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTohhhh(gt1,:,:) 
AmpVertexZAhTohhhh(gt2,:,:)= AmpVertexZAhTohhhh(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTohhhh(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTohhhh=AmpWaveZAhTohhhh 
AmpVertexAhTohhhh= AmpVertexZAhTohhhh
! Final State 1 
AmpWaveZAhTohhhh=0._dp 
AmpVertexZAhTohhhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTohhhh(:,gt2,:) = AmpWaveZAhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpWaveAhTohhhh(:,gt1,:) 
AmpVertexZAhTohhhh(:,gt2,:)= AmpVertexZAhTohhhh(:,gt2,:)+ZRUZH(gt2,gt1)*AmpVertexAhTohhhh(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTohhhh=AmpWaveZAhTohhhh 
AmpVertexAhTohhhh= AmpVertexZAhTohhhh
! Final State 2 
AmpWaveZAhTohhhh=0._dp 
AmpVertexZAhTohhhh=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=gt2,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! hh VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTohhVZ(cplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,MVZ2,              & 
& AmpTreeAhTohhVZ)

  Else 
Call Amplitude_Tree_NMSSM_AhTohhVZ(ZcplAhhhVZ,MAh,Mhh,MVZ,MAh2,Mhh2,MVZ2,             & 
& AmpTreeAhTohhVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTohhVZ(MLambda,em,gs,cplAhhhVZ,MAhOS,MhhOS,MVZOS,             & 
& MRPAhTohhVZ,MRGAhTohhVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTohhVZ(MLambda,em,gs,ZcplAhhhVZ,MAhOS,MhhOS,MVZOS,            & 
& MRPAhTohhVZ,MRGAhTohhVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTohhVZ(MLambda,em,gs,cplAhhhVZ,MAh,Mhh,MVZ,MRPAhTohhVZ,       & 
& MRGAhTohhVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTohhVZ(MLambda,em,gs,ZcplAhhhVZ,MAh,Mhh,MVZ,MRPAhTohhVZ,      & 
& MRGAhTohhVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTohhVZ(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,Mhh2,           & 
& MVZ,MVZ2,ZfAh,Zfhh,ZfVZ,AmpWaveAhTohhVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTohhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,              & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,              & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,     & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,   & 
& cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexAhTohhVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,              & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,     & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,   & 
& cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexIRdrAhTohhVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,            & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,               & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplcHpmVWmVZ,     & 
& cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,& 
& cplhhcHpmVWmVZ1,AmpVertexIRosAhTohhVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,ZcplAhhhVZ,cplAhHpmcHpm,             & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,              & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,     & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,   & 
& cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexIRosAhTohhVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,              & 
& MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,               & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,               & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplcHpmVWmVZ,     & 
& cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplhhHpmcVWmVZ1,& 
& cplhhcHpmVWmVZ1,AmpVertexIRosAhTohhVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTohhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,              & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,               & 
& cplcFuFuVZR,cplcgWmgWmhh,cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,         & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,     & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,   & 
& cplhhHpmcVWmVZ1,cplhhcHpmVWmVZ1,AmpVertexIRosAhTohhVZ)

 End if 
 End if 
AmpVertexAhTohhVZ = AmpVertexAhTohhVZ -  AmpVertexIRdrAhTohhVZ! +  AmpVertexIRosAhTohhVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTohhVZ=0._dp 
AmpVertexZAhTohhVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTohhVZ(:,gt2,:) = AmpWaveZAhTohhVZ(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWaveAhTohhVZ(:,gt1,:) 
AmpVertexZAhTohhVZ(:,gt2,:)= AmpVertexZAhTohhVZ(:,gt2,:) + ZRUZA(gt2,gt1)*AmpVertexAhTohhVZ(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTohhVZ=AmpWaveZAhTohhVZ 
AmpVertexAhTohhVZ= AmpVertexZAhTohhVZ
! Final State 1 
AmpWaveZAhTohhVZ=0._dp 
AmpVertexZAhTohhVZ=0._dp 
Do gt1=1,3
  Do gt2=1,3
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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
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
If (gt1.eq.3) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Conjg(Hpm) Hpm
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocHpmHpm(cplAhHpmcHpm,MAh,MHpm,MAh2,MHpm2,               & 
& AmpTreeAhTocHpmHpm)

  Else 
Call Amplitude_Tree_NMSSM_AhTocHpmHpm(ZcplAhHpmcHpm,MAh,MHpm,MAh2,MHpm2,              & 
& AmpTreeAhTocHpmHpm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocHpmHpm(MLambda,em,gs,cplAhHpmcHpm,MAhOS,MHpmOS,            & 
& MRPAhTocHpmHpm,MRGAhTocHpmHpm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocHpmHpm(MLambda,em,gs,ZcplAhHpmcHpm,MAhOS,MHpmOS,           & 
& MRPAhTocHpmHpm,MRGAhTocHpmHpm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocHpmHpm(MLambda,em,gs,cplAhHpmcHpm,MAh,MHpm,MRPAhTocHpmHpm, & 
& MRGAhTocHpmHpm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocHpmHpm(MLambda,em,gs,ZcplAhHpmcHpm,MAh,MHpm,               & 
& MRPAhTocHpmHpm,MRGAhTocHpmHpm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocHpmHpm(cplAhHpmcHpm,ctcplAhHpmcHpm,MAh,MAh2,           & 
& MHpm,MHpm2,ZfAh,ZfHpm,AmpWaveAhTocHpmHpm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,               & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcHpmL,             & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhHpmcHpm,     & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,           & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplAhAhHpmcHpm1,cplAhhhHpmcHpm1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,cplAhHpmcVWmVP1,        & 
& cplAhHpmcVWmVZ1,cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,      & 
& cplhhhhHpmcHpm1,cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,& 
& AmpVertexAhTocHpmHpm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcHpmL,             & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhHpmcHpm,     & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,           & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplAhAhHpmcHpm1,cplAhhhHpmcHpm1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,cplAhHpmcVWmVP1,        & 
& cplAhHpmcVWmVZ1,cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,      & 
& cplhhhhHpmcHpm1,cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,& 
& AmpVertexIRdrAhTocHpmHpm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocHpmHpm(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,ZcplAhHpmcHpm,             & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,             & 
& cplChiChacHpmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcHpmL,cplcFuFdcHpmR,              & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,       & 
& cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhcHpmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,           & 
& cplHpmcVWmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,      & 
& cplAhhhHpmcHpm1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,        & 
& cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhHpmcHpm1,      & 
& cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,               & 
& AmpVertexIRosAhTocHpmHpm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& ZcplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,              & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcHpmL,             & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhHpmcHpm,     & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,           & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplAhAhHpmcHpm1,cplAhhhHpmcHpm1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,cplAhHpmcVWmVP1,        & 
& cplAhHpmcVWmVZ1,cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,      & 
& cplhhhhHpmcHpm1,cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,& 
& AmpVertexIRosAhTocHpmHpm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocHpmHpm(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacHpmL,             & 
& cplChiChacHpmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcHpmL,cplcFuFdcHpmR,              & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,       & 
& cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhcHpmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,           & 
& cplHpmcVWmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,cplAhAhHpmcHpm1,      & 
& cplAhhhHpmcHpm1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,        & 
& cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhHpmcHpm1,      & 
& cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,               & 
& AmpVertexIRosAhTocHpmHpm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocHpmHpm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacHpmL,cplChiChacHpmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcHpmL,             & 
& cplcFuFdcHpmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgZgWmcHpm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcHpm,cplhhHpmcHpm,     & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,cplHpmcVWmVP,           & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcHpmcSu,cplSecHpmcSv,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplAhAhHpmcHpm1,cplAhhhHpmcHpm1,cplAhHpmSucSdaa,cplAhHpmSvcSe1,cplAhHpmcVWmVP1,        & 
& cplAhHpmcVWmVZ1,cplAhSdcHpmcSuaa,cplAhSecHpmcSv1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,      & 
& cplhhhhHpmcHpm1,cplHpmHpmcHpmcHpm1,cplHpmSdcHpmcSdaa,cplHpmSecHpmcSe1,cplHpmSucHpmcSuaa,& 
& AmpVertexIRosAhTocHpmHpm)

 End if 
 End if 
AmpVertexAhTocHpmHpm = AmpVertexAhTocHpmHpm -  AmpVertexIRdrAhTocHpmHpm! +  AmpVertexIRosAhTocHpmHpm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocHpmHpm=0._dp 
AmpVertexZAhTocHpmHpm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocHpmHpm(gt2,:,:) = AmpWaveZAhTocHpmHpm(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocHpmHpm(gt1,:,:) 
AmpVertexZAhTocHpmHpm(gt2,:,:)= AmpVertexZAhTocHpmHpm(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocHpmHpm(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocHpmHpm=AmpWaveZAhTocHpmHpm 
AmpVertexAhTocHpmHpm= AmpVertexZAhTocHpmHpm
! Final State 1 
AmpWaveZAhTocHpmHpm=0._dp 
AmpVertexZAhTocHpmHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocHpmHpm(:,gt2,:) = AmpWaveZAhTocHpmHpm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpWaveAhTocHpmHpm(:,gt1,:) 
AmpVertexZAhTocHpmHpm(:,gt2,:)= AmpVertexZAhTocHpmHpm(:,gt2,:)+ZRUZP(gt2,gt1)*AmpVertexAhTocHpmHpm(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocHpmHpm=AmpWaveZAhTocHpmHpm 
AmpVertexAhTocHpmHpm= AmpVertexZAhTocHpmHpm
! Final State 2 
AmpWaveZAhTocHpmHpm=0._dp 
AmpVertexZAhTocHpmHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhTocHpmHpm(:,:,gt2) = AmpWaveZAhTocHpmHpm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveAhTocHpmHpm(:,:,gt1) 
AmpVertexZAhTocHpmHpm(:,:,gt2)= AmpVertexZAhTocHpmHpm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexAhTocHpmHpm(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocHpmHpm=AmpWaveZAhTocHpmHpm 
AmpVertexAhTocHpmHpm= AmpVertexZAhTocHpmHpm
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocHpmHpm = AmpVertexAhTocHpmHpm  +  AmpVertexIRosAhTocHpmHpm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->conj[Hpm] Hpm -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocHpmHpm = AmpTreeAhTocHpmHpm 
 AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm + 2._dp*AmpWaveAhTocHpmHpm + 2._dp*AmpVertexAhTocHpmHpm  
Else 
 AmpSumAhTocHpmHpm = AmpTreeAhTocHpmHpm + AmpWaveAhTocHpmHpm + AmpVertexAhTocHpmHpm
 AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm + AmpWaveAhTocHpmHpm + AmpVertexAhTocHpmHpm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocHpmHpm = AmpTreeAhTocHpmHpm
 AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=2,2
    Do gt3=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MHpmOS(gt2))+Abs(MHpmOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MHpm(gt2))+Abs(MHpm(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHpm(gt2),MHpm(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocHpmHpm(gt1, gt2, gt3) 
  AmpSum2AhTocHpmHpm = 2._dp*AmpWaveAhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHpm(gt2),MHpm(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocHpmHpm(gt1, gt2, gt3) 
  AmpSum2AhTocHpmHpm = 2._dp*AmpVertexAhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHpm(gt2),MHpm(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocHpmHpm(gt1, gt2, gt3) 
  AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm + 2._dp*AmpWaveAhTocHpmHpm + 2._dp*AmpVertexAhTocHpmHpm
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MHpm(gt2),MHpm(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocHpmHpm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm
  Call SquareAmp_StoSS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqTreeAhTocHpmHpm(gt1, gt2, gt3) = AmpSqAhTocHpmHpm(gt1, gt2, gt3)  
  AmpSum2AhTocHpmHpm = + 2._dp*AmpWaveAhTocHpmHpm + 2._dp*AmpVertexAhTocHpmHpm
  Call SquareAmp_StoSS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqAhTocHpmHpm(gt1, gt2, gt3) = AmpSqAhTocHpmHpm(gt1, gt2, gt3) + AmpSqTreeAhTocHpmHpm(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocHpmHpm = AmpTreeAhTocHpmHpm
  Call SquareAmp_StoSS(MAh(gt1),MHpm(gt2),MHpm(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqTreeAhTocHpmHpm(gt1, gt2, gt3) = AmpSqAhTocHpmHpm(gt1, gt2, gt3)  
  AmpSum2AhTocHpmHpm = + 2._dp*AmpWaveAhTocHpmHpm + 2._dp*AmpVertexAhTocHpmHpm
  Call SquareAmp_StoSS(MAh(gt1),MHpm(gt2),MHpm(gt3),AmpSumAhTocHpmHpm(gt1, gt2, gt3),AmpSum2AhTocHpmHpm(gt1, gt2, gt3),AmpSqAhTocHpmHpm(gt1, gt2, gt3)) 
  AmpSqAhTocHpmHpm(gt1, gt2, gt3) = AmpSqAhTocHpmHpm(gt1, gt2, gt3) + AmpSqTreeAhTocHpmHpm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocHpmHpm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTocHpmHpm(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MHpmOS(gt2),MHpmOS(gt3),helfactor*AmpSqAhTocHpmHpm(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MHpm(gt2),MHpm(gt3),helfactor*AmpSqAhTocHpmHpm(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocHpmHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocHpmHpm(gt1, gt2, gt3) + MRGAhTocHpmHpm(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocHpmHpm(gt1, gt2, gt3) + MRGAhTocHpmHpm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
Call Amplitude_Tree_NMSSM_AhToHpmcVWm(cplAhHpmcVWm,MAh,MHpm,MVWm,MAh2,MHpm2,          & 
& MVWm2,AmpTreeAhToHpmcVWm)

  Else 
Call Amplitude_Tree_NMSSM_AhToHpmcVWm(ZcplAhHpmcVWm,MAh,MHpm,MVWm,MAh2,               & 
& MHpm2,MVWm2,AmpTreeAhToHpmcVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhToHpmcVWm(MLambda,em,gs,cplAhHpmcVWm,MAhOS,MHpmOS,            & 
& MVWmOS,MRPAhToHpmcVWm,MRGAhToHpmcVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhToHpmcVWm(MLambda,em,gs,ZcplAhHpmcVWm,MAhOS,MHpmOS,           & 
& MVWmOS,MRPAhToHpmcVWm,MRGAhToHpmcVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhToHpmcVWm(MLambda,em,gs,cplAhHpmcVWm,MAh,MHpm,MVWm,           & 
& MRPAhToHpmcVWm,MRGAhToHpmcVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhToHpmcVWm(MLambda,em,gs,ZcplAhHpmcVWm,MAh,MHpm,               & 
& MVWm,MRPAhToHpmcVWm,MRGAhToHpmcVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhToHpmcVWm(cplAhHpmcVWm,ctcplAhHpmcVWm,MAh,MAh2,           & 
& MHpm,MHpm2,MVWm,MVWm2,ZfAh,ZfHpm,ZfVWm,AmpWaveAhToHpmcVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,               & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgWmgAHpm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmSucSd,cplHpmSvcSe,         & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,             & 
& cplhhHpmcVWmVZ1,cplHpmcHpmcVWmVWm1,AmpVertexAhToHpmcVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgWmgAHpm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmSucSd,cplHpmSvcSe,         & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,             & 
& cplhhHpmcVWmVZ1,cplHpmcHpmcVWmVWm1,AmpVertexIRdrAhToHpmcVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToHpmcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,GosZcplAhHpmcHpm,          & 
& ZcplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacVWmL,            & 
& cplChiChacVWmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,              & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,       & 
& cplcgWmgAHpm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcVWm,    & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,           & 
& GosZcplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,cplcVWmVPVWm,     & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplhhHpmcVWmVZ1,          & 
& cplHpmcHpmcVWmVWm1,AmpVertexIRosAhToHpmcVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& GZcplAhHpmcHpm,ZcplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,            & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgWmgAHpm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmSucSd,cplHpmSvcSe,         & 
& cplHpmcHpmVP,GZcplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,       & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,             & 
& cplhhHpmcVWmVZ1,cplHpmcHpmcVWmVWm1,AmpVertexIRosAhToHpmcVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToHpmcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,           & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,GcplAhHpmcHpm,             & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacVWmL,             & 
& cplChiChacVWmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,              & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,       & 
& cplcgWmgAHpm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgWmgZHpm,cplcgWpCgZcVWm,    & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmSucSd,cplHpmSvcSe,cplHpmcHpmVP,           & 
& GcplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,cplcVWmVPVWm,        & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplhhHpmcVWmVZ1,          & 
& cplHpmcHpmcVWmVWm1,AmpVertexIRosAhToHpmcVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhToHpmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,             & 
& MHpm,MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,          & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,      & 
& cplcFeFvHpmR,cplcgWmgAHpm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHpm,cplcgWmgZHpm,      & 
& cplcgWpCgZcVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmSucSd,cplHpmSvcSe,         & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,             & 
& cplhhHpmcVWmVZ1,cplHpmcHpmcVWmVWm1,AmpVertexIRosAhToHpmcVWm)

 End if 
 End if 
AmpVertexAhToHpmcVWm = AmpVertexAhToHpmcVWm -  AmpVertexIRdrAhToHpmcVWm! +  AmpVertexIRosAhToHpmcVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhToHpmcVWm=0._dp 
AmpVertexZAhToHpmcVWm=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhToHpmcVWm(:,gt2,:) = AmpWaveZAhToHpmcVWm(:,gt2,:)+ZRUZA(gt2,gt1)*AmpWaveAhToHpmcVWm(:,gt1,:) 
AmpVertexZAhToHpmcVWm(:,gt2,:)= AmpVertexZAhToHpmcVWm(:,gt2,:) + ZRUZA(gt2,gt1)*AmpVertexAhToHpmcVWm(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhToHpmcVWm=AmpWaveZAhToHpmcVWm 
AmpVertexAhToHpmcVWm= AmpVertexZAhToHpmcVWm
! Final State 1 
AmpWaveZAhToHpmcVWm=0._dp 
AmpVertexZAhToHpmcVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZAhToHpmcVWm(:,:,gt2) = AmpWaveZAhToHpmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveAhToHpmcVWm(:,:,gt1) 
AmpVertexZAhToHpmcVWm(:,:,gt2)= AmpVertexZAhToHpmcVWm(:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexAhToHpmcVWm(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhToHpmcVWm=AmpWaveZAhToHpmcVWm 
AmpVertexAhToHpmcVWm= AmpVertexZAhToHpmcVWm
End if
If (ShiftIRdiv) Then 
AmpVertexAhToHpmcVWm = AmpVertexAhToHpmcVWm  +  AmpVertexIRosAhToHpmcVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Hpm conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhToHpmcVWm = AmpTreeAhToHpmcVWm 
 AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm + 2._dp*AmpWaveAhToHpmcVWm + 2._dp*AmpVertexAhToHpmcVWm  
Else 
 AmpSumAhToHpmcVWm = AmpTreeAhToHpmcVWm + AmpWaveAhToHpmcVWm + AmpVertexAhToHpmcVWm
 AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm + AmpWaveAhToHpmcVWm + AmpVertexAhToHpmcVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToHpmcVWm = AmpTreeAhToHpmcVWm
 AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=2,2
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MHpmOS(gt2))+Abs(MVWmOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MHpm(gt2))+Abs(MVWm))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHpm(gt2),MVWm,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhToHpmcVWm(gt1, gt2) 
  AmpSum2AhToHpmcVWm = 2._dp*AmpWaveAhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHpm(gt2),MVWm,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhToHpmcVWm(gt1, gt2) 
  AmpSum2AhToHpmcVWm = 2._dp*AmpVertexAhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHpm(gt2),MVWm,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhToHpmcVWm(gt1, gt2) 
  AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm + 2._dp*AmpWaveAhToHpmcVWm + 2._dp*AmpVertexAhToHpmcVWm
If (OSkinematics) Then 
  Call SquareAmp_StoSV(MAhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
Else  
  Call SquareAmp_StoSV(MAh(gt1),MHpm(gt2),MVWm,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhToHpmcVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm
  Call SquareAmp_StoSV(MAhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
  AmpSqTreeAhToHpmcVWm(gt1, gt2) = AmpSqAhToHpmcVWm(gt1, gt2)  
  AmpSum2AhToHpmcVWm = + 2._dp*AmpWaveAhToHpmcVWm + 2._dp*AmpVertexAhToHpmcVWm
  Call SquareAmp_StoSV(MAhOS(gt1),MHpmOS(gt2),MVWmOS,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
  AmpSqAhToHpmcVWm(gt1, gt2) = AmpSqAhToHpmcVWm(gt1, gt2) + AmpSqTreeAhToHpmcVWm(gt1, gt2)  
Else  
  AmpSum2AhToHpmcVWm = AmpTreeAhToHpmcVWm
  Call SquareAmp_StoSV(MAh(gt1),MHpm(gt2),MVWm,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
  AmpSqTreeAhToHpmcVWm(gt1, gt2) = AmpSqAhToHpmcVWm(gt1, gt2)  
  AmpSum2AhToHpmcVWm = + 2._dp*AmpWaveAhToHpmcVWm + 2._dp*AmpVertexAhToHpmcVWm
  Call SquareAmp_StoSV(MAh(gt1),MHpm(gt2),MVWm,AmpSumAhToHpmcVWm(:,gt1, gt2),AmpSum2AhToHpmcVWm(:,gt1, gt2),AmpSqAhToHpmcVWm(gt1, gt2)) 
  AmpSqAhToHpmcVWm(gt1, gt2) = AmpSqAhToHpmcVWm(gt1, gt2) + AmpSqTreeAhToHpmcVWm(gt1, gt2)  
End if  
Else  
  AmpSqAhToHpmcVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToHpmcVWm(gt1, gt2).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAhOS(gt1),MHpmOS(gt2),MVWmOS,helfactor*AmpSqAhToHpmcVWm(gt1, gt2))
Else 
  gP1LAh(gt1,i4) = 2._dp*GammaTPS(MAh(gt1),MHpm(gt2),MVWm,helfactor*AmpSqAhToHpmcVWm(gt1, gt2))
End if 
If ((Abs(MRPAhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGAhToHpmcVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*2._dp*helfactor*(MRPAhToHpmcVWm(gt1, gt2) + MRGAhToHpmcVWm(gt1, gt2)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*2._dp*helfactor*(MRPAhToHpmcVWm(gt1, gt2) + MRGAhToHpmcVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! Conjg(Sd) Sd
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocSdSd(cplAhSdcSd,MAh,MSd,MAh2,MSd2,AmpTreeAhTocSdSd)

  Else 
Call Amplitude_Tree_NMSSM_AhTocSdSd(ZcplAhSdcSd,MAh,MSd,MAh2,MSd2,AmpTreeAhTocSdSd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocSdSd(MLambda,em,gs,cplAhSdcSd,MAhOS,MSdOS,MRPAhTocSdSd,    & 
& MRGAhTocSdSd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocSdSd(MLambda,em,gs,ZcplAhSdcSd,MAhOS,MSdOS,MRPAhTocSdSd,   & 
& MRGAhTocSdSd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocSdSd(MLambda,em,gs,cplAhSdcSd,MAh,MSd,MRPAhTocSdSd,        & 
& MRGAhTocSdSd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocSdSd(MLambda,em,gs,ZcplAhSdcSd,MAh,MSd,MRPAhTocSdSd,       & 
& MRGAhTocSdSd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocSdSd(cplAhSdcSd,ctcplAhSdcSd,MAh,MAh2,MSd,             & 
& MSd2,ZfAh,ZfSd,AmpWaveAhTocSdSd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocSdSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,              & 
& MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplcFdChiSdL,         & 
& cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,cplhhSdcSd,           & 
& cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,              & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexAhTocSdSd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSdSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRdrAhTocSdSd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSdSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
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
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosAhTocSdSd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSdSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,ZcplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosAhTocSdSd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSdSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
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
& cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosAhTocSdSd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSdSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplcFdChiSdL,cplcFdChiSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplcChacFuSdL,cplcChacFuSdR,   & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSdVWm,cplAhAhSdcSdaa,cplAhhhSdcSdaa,cplAhHpmSucSdaa,   & 
& cplAhSdcHpmcSuaa,cplhhhhSdcSdaa,cplHpmSdcHpmcSdaa,cplSdSdcSdcSdabba,cplSdSdcSdcSdabab, & 
& cplSdSecSdcSeaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab,AmpVertexIRosAhTocSdSd)

 End if 
 End if 
AmpVertexAhTocSdSd = AmpVertexAhTocSdSd -  AmpVertexIRdrAhTocSdSd! +  AmpVertexIRosAhTocSdSd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocSdSd=0._dp 
AmpVertexZAhTocSdSd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocSdSd(gt2,:,:) = AmpWaveZAhTocSdSd(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocSdSd(gt1,:,:) 
AmpVertexZAhTocSdSd(gt2,:,:)= AmpVertexZAhTocSdSd(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocSdSd(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocSdSd=AmpWaveZAhTocSdSd 
AmpVertexAhTocSdSd= AmpVertexZAhTocSdSd
! Final State 1 
AmpWaveZAhTocSdSd=0._dp 
AmpVertexZAhTocSdSd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZAhTocSdSd(:,gt2,:) = AmpWaveZAhTocSdSd(:,gt2,:)+ZRUZDc(gt2,gt1)*AmpWaveAhTocSdSd(:,gt1,:) 
AmpVertexZAhTocSdSd(:,gt2,:)= AmpVertexZAhTocSdSd(:,gt2,:)+ZRUZDc(gt2,gt1)*AmpVertexAhTocSdSd(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocSdSd=AmpWaveZAhTocSdSd 
AmpVertexAhTocSdSd= AmpVertexZAhTocSdSd
! Final State 2 
AmpWaveZAhTocSdSd=0._dp 
AmpVertexZAhTocSdSd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZAhTocSdSd(:,:,gt2) = AmpWaveZAhTocSdSd(:,:,gt2)+ZRUZD(gt2,gt1)*AmpWaveAhTocSdSd(:,:,gt1) 
AmpVertexZAhTocSdSd(:,:,gt2)= AmpVertexZAhTocSdSd(:,:,gt2)+ZRUZD(gt2,gt1)*AmpVertexAhTocSdSd(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocSdSd=AmpWaveZAhTocSdSd 
AmpVertexAhTocSdSd= AmpVertexZAhTocSdSd
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocSdSd = AmpVertexAhTocSdSd  +  AmpVertexIRosAhTocSdSd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->conj[Sd] Sd -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocSdSd = AmpTreeAhTocSdSd 
 AmpSum2AhTocSdSd = AmpTreeAhTocSdSd + 2._dp*AmpWaveAhTocSdSd + 2._dp*AmpVertexAhTocSdSd  
Else 
 AmpSumAhTocSdSd = AmpTreeAhTocSdSd + AmpWaveAhTocSdSd + AmpVertexAhTocSdSd
 AmpSum2AhTocSdSd = AmpTreeAhTocSdSd + AmpWaveAhTocSdSd + AmpVertexAhTocSdSd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocSdSd = AmpTreeAhTocSdSd
 AmpSum2AhTocSdSd = AmpTreeAhTocSdSd 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,6
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MSdOS(gt2))+Abs(MSdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MSd(gt2))+Abs(MSd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocSdSd = AmpTreeAhTocSdSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSd(gt2),MSd(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocSdSd(gt1, gt2, gt3) 
  AmpSum2AhTocSdSd = 2._dp*AmpWaveAhTocSdSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSd(gt2),MSd(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocSdSd(gt1, gt2, gt3) 
  AmpSum2AhTocSdSd = 2._dp*AmpVertexAhTocSdSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSd(gt2),MSd(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocSdSd(gt1, gt2, gt3) 
  AmpSum2AhTocSdSd = AmpTreeAhTocSdSd + 2._dp*AmpWaveAhTocSdSd + 2._dp*AmpVertexAhTocSdSd
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSd(gt2),MSd(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocSdSd(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocSdSd = AmpTreeAhTocSdSd
  Call SquareAmp_StoSS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
  AmpSqTreeAhTocSdSd(gt1, gt2, gt3) = AmpSqAhTocSdSd(gt1, gt2, gt3)  
  AmpSum2AhTocSdSd = + 2._dp*AmpWaveAhTocSdSd + 2._dp*AmpVertexAhTocSdSd
  Call SquareAmp_StoSS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
  AmpSqAhTocSdSd(gt1, gt2, gt3) = AmpSqAhTocSdSd(gt1, gt2, gt3) + AmpSqTreeAhTocSdSd(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocSdSd = AmpTreeAhTocSdSd
  Call SquareAmp_StoSS(MAh(gt1),MSd(gt2),MSd(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
  AmpSqTreeAhTocSdSd(gt1, gt2, gt3) = AmpSqAhTocSdSd(gt1, gt2, gt3)  
  AmpSum2AhTocSdSd = + 2._dp*AmpWaveAhTocSdSd + 2._dp*AmpVertexAhTocSdSd
  Call SquareAmp_StoSS(MAh(gt1),MSd(gt2),MSd(gt3),AmpSumAhTocSdSd(gt1, gt2, gt3),AmpSum2AhTocSdSd(gt1, gt2, gt3),AmpSqAhTocSdSd(gt1, gt2, gt3)) 
  AmpSqAhTocSdSd(gt1, gt2, gt3) = AmpSqAhTocSdSd(gt1, gt2, gt3) + AmpSqTreeAhTocSdSd(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocSdSd(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTocSdSd(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAhOS(gt1),MSdOS(gt2),MSdOS(gt3),helfactor*AmpSqAhTocSdSd(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAh(gt1),MSd(gt2),MSd(gt3),helfactor*AmpSqAhTocSdSd(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocSdSd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocSdSd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocSdSd(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocSdSd(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocSdSd(gt1, gt2, gt3) + MRGAhTocSdSd(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocSdSd(gt1, gt2, gt3) + MRGAhTocSdSd(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! Conjg(Se) Se
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocSeSe(cplAhSecSe,MAh,MSe,MAh2,MSe2,AmpTreeAhTocSeSe)

  Else 
Call Amplitude_Tree_NMSSM_AhTocSeSe(ZcplAhSecSe,MAh,MSe,MAh2,MSe2,AmpTreeAhTocSeSe)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocSeSe(MLambda,em,gs,cplAhSecSe,MAhOS,MSeOS,MRPAhTocSeSe,    & 
& MRGAhTocSeSe)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocSeSe(MLambda,em,gs,ZcplAhSecSe,MAhOS,MSeOS,MRPAhTocSeSe,   & 
& MRGAhTocSeSe)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocSeSe(MLambda,em,gs,cplAhSecSe,MAh,MSe,MRPAhTocSeSe,        & 
& MRGAhTocSeSe)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocSeSe(MLambda,em,gs,ZcplAhSecSe,MAh,MSe,MRPAhTocSeSe,       & 
& MRGAhTocSeSe)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocSeSe(cplAhSecSe,ctcplAhSecSe,MAh,MAh2,MSe,             & 
& MSe2,ZfAh,ZfSe,AmpWaveAhTocSeSe)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocSeSe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSd,MSe,             & 
& MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSd2,MSe2,MSu2,MSv2,             & 
& MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,    & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,               & 
& cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplcChacFvSeL,cplcChacFvSeR,cplSecHpmcSv,cplSecSvcVWm,           & 
& cplSvcSeVWm,cplAhAhSecSe1,cplAhhhSecSe1,cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSecSe1,  & 
& cplHpmSecHpmcSe1,cplSdSecSdcSeaa,cplSeSecSecSe1,cplSeSucSecSuaa,AmpVertexAhTocSeSe)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSeSe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSd,              & 
& MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSd2,MSe2,MSu2,              & 
& MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,     & 
& cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,    & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,               & 
& cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplcChacFvSeL,cplcChacFvSeR,cplSecHpmcSv,cplSecSvcVWm,           & 
& cplSvcSeVWm,cplAhAhSecSe1,cplAhhhSecSe1,cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSecSe1,  & 
& cplHpmSecHpmcSe1,cplSdSecSdcSeaa,cplSeSecSecSe1,cplSeSucSecSuaa,AmpVertexIRdrAhTocSeSe)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSeSe(MAhOS,MChaOS,MChiOS,MFeOS,MhhOS,             & 
& MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,         & 
& Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,              & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,ZcplAhSecSe,      & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,cplChiFecSeL,cplChiFecSeR,           & 
& cplcFeChiSeL,cplcFeChiSeR,cplhhSecSe,cplHpmSvcSe,cplSecSeVP,cplSecSeVZ,cplcChacFvSeL,  & 
& cplcChacFvSeR,cplSecHpmcSv,cplSecSvcVWm,cplSvcSeVWm,cplAhAhSecSe1,cplAhhhSecSe1,       & 
& cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSecSe1,cplHpmSecHpmcSe1,cplSdSecSdcSeaa,         & 
& cplSeSecSecSe1,cplSeSucSecSuaa,AmpVertexIRosAhTocSeSe)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSeSe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSd,              & 
& MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSd2,MSe2,MSu2,              & 
& MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,     & 
& cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,    & 
& cplAhSdcSd,ZcplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,              & 
& cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplcChacFvSeL,cplcChacFvSeR,cplSecHpmcSv,cplSecSvcVWm,           & 
& cplSvcSeVWm,cplAhAhSecSe1,cplAhhhSecSe1,cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSecSe1,  & 
& cplHpmSecHpmcSe1,cplSdSecSdcSeaa,cplSeSecSecSe1,cplSeSucSecSuaa,AmpVertexIRosAhTocSeSe)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSeSe(MAhOS,MChaOS,MChiOS,MFeOS,MhhOS,             & 
& MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,         & 
& Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,              & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,cplChiFecSeL,cplChiFecSeR,           & 
& cplcFeChiSeL,cplcFeChiSeR,cplhhSecSe,cplHpmSvcSe,cplSecSeVP,cplSecSeVZ,cplcChacFvSeL,  & 
& cplcChacFvSeR,cplSecHpmcSv,cplSecSvcVWm,cplSvcSeVWm,cplAhAhSecSe1,cplAhhhSecSe1,       & 
& cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSecSe1,cplHpmSecHpmcSe1,cplSdSecSdcSeaa,         & 
& cplSeSecSecSe1,cplSeSucSecSuaa,AmpVertexIRosAhTocSeSe)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSeSe(MAh,MCha,MChi,MFe,Mhh,MHpm,MSd,              & 
& MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSd2,MSe2,MSu2,              & 
& MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,     & 
& cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,    & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,               & 
& cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVP,cplSecSeVZ,cplcChacFvSeL,cplcChacFvSeR,cplSecHpmcSv,cplSecSvcVWm,           & 
& cplSvcSeVWm,cplAhAhSecSe1,cplAhhhSecSe1,cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSecSe1,  & 
& cplHpmSecHpmcSe1,cplSdSecSdcSeaa,cplSeSecSecSe1,cplSeSucSecSuaa,AmpVertexIRosAhTocSeSe)

 End if 
 End if 
AmpVertexAhTocSeSe = AmpVertexAhTocSeSe -  AmpVertexIRdrAhTocSeSe! +  AmpVertexIRosAhTocSeSe ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocSeSe=0._dp 
AmpVertexZAhTocSeSe=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocSeSe(gt2,:,:) = AmpWaveZAhTocSeSe(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocSeSe(gt1,:,:) 
AmpVertexZAhTocSeSe(gt2,:,:)= AmpVertexZAhTocSeSe(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocSeSe(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocSeSe=AmpWaveZAhTocSeSe 
AmpVertexAhTocSeSe= AmpVertexZAhTocSeSe
! Final State 1 
AmpWaveZAhTocSeSe=0._dp 
AmpVertexZAhTocSeSe=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZAhTocSeSe(:,gt2,:) = AmpWaveZAhTocSeSe(:,gt2,:)+ZRUZEc(gt2,gt1)*AmpWaveAhTocSeSe(:,gt1,:) 
AmpVertexZAhTocSeSe(:,gt2,:)= AmpVertexZAhTocSeSe(:,gt2,:)+ZRUZEc(gt2,gt1)*AmpVertexAhTocSeSe(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocSeSe=AmpWaveZAhTocSeSe 
AmpVertexAhTocSeSe= AmpVertexZAhTocSeSe
! Final State 2 
AmpWaveZAhTocSeSe=0._dp 
AmpVertexZAhTocSeSe=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZAhTocSeSe(:,:,gt2) = AmpWaveZAhTocSeSe(:,:,gt2)+ZRUZE(gt2,gt1)*AmpWaveAhTocSeSe(:,:,gt1) 
AmpVertexZAhTocSeSe(:,:,gt2)= AmpVertexZAhTocSeSe(:,:,gt2)+ZRUZE(gt2,gt1)*AmpVertexAhTocSeSe(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocSeSe=AmpWaveZAhTocSeSe 
AmpVertexAhTocSeSe= AmpVertexZAhTocSeSe
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocSeSe = AmpVertexAhTocSeSe  +  AmpVertexIRosAhTocSeSe
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->conj[Se] Se -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocSeSe = AmpTreeAhTocSeSe 
 AmpSum2AhTocSeSe = AmpTreeAhTocSeSe + 2._dp*AmpWaveAhTocSeSe + 2._dp*AmpVertexAhTocSeSe  
Else 
 AmpSumAhTocSeSe = AmpTreeAhTocSeSe + AmpWaveAhTocSeSe + AmpVertexAhTocSeSe
 AmpSum2AhTocSeSe = AmpTreeAhTocSeSe + AmpWaveAhTocSeSe + AmpVertexAhTocSeSe 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocSeSe = AmpTreeAhTocSeSe
 AmpSum2AhTocSeSe = AmpTreeAhTocSeSe 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,6
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MSeOS(gt2))+Abs(MSeOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MSe(gt2))+Abs(MSe(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocSeSe = AmpTreeAhTocSeSe
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSe(gt2),MSe(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocSeSe(gt1, gt2, gt3) 
  AmpSum2AhTocSeSe = 2._dp*AmpWaveAhTocSeSe
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSe(gt2),MSe(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocSeSe(gt1, gt2, gt3) 
  AmpSum2AhTocSeSe = 2._dp*AmpVertexAhTocSeSe
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSe(gt2),MSe(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocSeSe(gt1, gt2, gt3) 
  AmpSum2AhTocSeSe = AmpTreeAhTocSeSe + 2._dp*AmpWaveAhTocSeSe + 2._dp*AmpVertexAhTocSeSe
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSe(gt2),MSe(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocSeSe(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocSeSe = AmpTreeAhTocSeSe
  Call SquareAmp_StoSS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
  AmpSqTreeAhTocSeSe(gt1, gt2, gt3) = AmpSqAhTocSeSe(gt1, gt2, gt3)  
  AmpSum2AhTocSeSe = + 2._dp*AmpWaveAhTocSeSe + 2._dp*AmpVertexAhTocSeSe
  Call SquareAmp_StoSS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
  AmpSqAhTocSeSe(gt1, gt2, gt3) = AmpSqAhTocSeSe(gt1, gt2, gt3) + AmpSqTreeAhTocSeSe(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocSeSe = AmpTreeAhTocSeSe
  Call SquareAmp_StoSS(MAh(gt1),MSe(gt2),MSe(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
  AmpSqTreeAhTocSeSe(gt1, gt2, gt3) = AmpSqAhTocSeSe(gt1, gt2, gt3)  
  AmpSum2AhTocSeSe = + 2._dp*AmpWaveAhTocSeSe + 2._dp*AmpVertexAhTocSeSe
  Call SquareAmp_StoSS(MAh(gt1),MSe(gt2),MSe(gt3),AmpSumAhTocSeSe(gt1, gt2, gt3),AmpSum2AhTocSeSe(gt1, gt2, gt3),AmpSqAhTocSeSe(gt1, gt2, gt3)) 
  AmpSqAhTocSeSe(gt1, gt2, gt3) = AmpSqAhTocSeSe(gt1, gt2, gt3) + AmpSqTreeAhTocSeSe(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocSeSe(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTocSeSe(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MSeOS(gt2),MSeOS(gt3),helfactor*AmpSqAhTocSeSe(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MSe(gt2),MSe(gt3),helfactor*AmpSqAhTocSeSe(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocSeSe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocSeSe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocSeSe(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocSeSe(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocSeSe(gt1, gt2, gt3) + MRGAhTocSeSe(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocSeSe(gt1, gt2, gt3) + MRGAhTocSeSe(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! Conjg(Su) Su
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_AhTocSuSu(cplAhSucSu,MAh,MSu,MAh2,MSu2,AmpTreeAhTocSuSu)

  Else 
Call Amplitude_Tree_NMSSM_AhTocSuSu(ZcplAhSucSu,MAh,MSu,MAh2,MSu2,AmpTreeAhTocSuSu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_AhTocSuSu(MLambda,em,gs,cplAhSucSu,MAhOS,MSuOS,MRPAhTocSuSu,    & 
& MRGAhTocSuSu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_AhTocSuSu(MLambda,em,gs,ZcplAhSucSu,MAhOS,MSuOS,MRPAhTocSuSu,   & 
& MRGAhTocSuSu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_AhTocSuSu(MLambda,em,gs,cplAhSucSu,MAh,MSu,MRPAhTocSuSu,        & 
& MRGAhTocSuSu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_AhTocSuSu(MLambda,em,gs,ZcplAhSucSu,MAh,MSu,MRPAhTocSuSu,       & 
& MRGAhTocSuSu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTocSuSu(cplAhSucSu,ctcplAhSucSu,MAh,MAh2,MSu,             & 
& MSu2,ZfAh,ZfSu,AmpWaveAhTocSuSu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTocSuSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,            & 
& MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,              & 
& MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuGluSuL,       & 
& cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,              & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,cplAhHpmSucSdaa,       & 
& cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,cplSdSucSdcSuabab, & 
& cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexAhTocSuSu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSuSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,            & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,            & 
& cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,   & 
& cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRdrAhTocSuSu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSuSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
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
& cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosAhTocSuSu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSuSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& ZcplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,          & 
& cplcFuChiSuL,cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,            & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,            & 
& cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,   & 
& cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosAhTocSuSu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSuSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,             & 
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
& cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosAhTocSuSu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_AhTocSuSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,              & 
& MHpm,MSd,MSe,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,               & 
& MHpm2,MSd2,MSe2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,           & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplcFdChaSuL,cplcFdChaSuR,cplChiFucSuL,cplChiFucSuR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,       & 
& cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSucVWm,            & 
& cplSucSuVG,cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplAhAhSucSuaa,cplAhhhSucSuaa,            & 
& cplAhHpmSucSdaa,cplAhSdcHpmcSuaa,cplhhhhSucSuaa,cplHpmSucHpmcSuaa,cplSdSucSdcSuabba,   & 
& cplSdSucSdcSuabab,cplSeSucSecSuaa,cplSuSucSucSuabba,cplSuSucSucSuabab,AmpVertexIRosAhTocSuSu)

 End if 
 End if 
AmpVertexAhTocSuSu = AmpVertexAhTocSuSu -  AmpVertexIRdrAhTocSuSu! +  AmpVertexIRosAhTocSuSu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZAhTocSuSu=0._dp 
AmpVertexZAhTocSuSu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZAhTocSuSu(gt2,:,:) = AmpWaveZAhTocSuSu(gt2,:,:)+ZRUZA(gt2,gt1)*AmpWaveAhTocSuSu(gt1,:,:) 
AmpVertexZAhTocSuSu(gt2,:,:)= AmpVertexZAhTocSuSu(gt2,:,:) + ZRUZA(gt2,gt1)*AmpVertexAhTocSuSu(gt1,:,:) 
 End Do 
End Do 
AmpWaveAhTocSuSu=AmpWaveZAhTocSuSu 
AmpVertexAhTocSuSu= AmpVertexZAhTocSuSu
! Final State 1 
AmpWaveZAhTocSuSu=0._dp 
AmpVertexZAhTocSuSu=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZAhTocSuSu(:,gt2,:) = AmpWaveZAhTocSuSu(:,gt2,:)+ZRUZUc(gt2,gt1)*AmpWaveAhTocSuSu(:,gt1,:) 
AmpVertexZAhTocSuSu(:,gt2,:)= AmpVertexZAhTocSuSu(:,gt2,:)+ZRUZUc(gt2,gt1)*AmpVertexAhTocSuSu(:,gt1,:) 
 End Do 
End Do 
AmpWaveAhTocSuSu=AmpWaveZAhTocSuSu 
AmpVertexAhTocSuSu= AmpVertexZAhTocSuSu
! Final State 2 
AmpWaveZAhTocSuSu=0._dp 
AmpVertexZAhTocSuSu=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZAhTocSuSu(:,:,gt2) = AmpWaveZAhTocSuSu(:,:,gt2)+ZRUZU(gt2,gt1)*AmpWaveAhTocSuSu(:,:,gt1) 
AmpVertexZAhTocSuSu(:,:,gt2)= AmpVertexZAhTocSuSu(:,:,gt2)+ZRUZU(gt2,gt1)*AmpVertexAhTocSuSu(:,:,gt1) 
 End Do 
End Do 
AmpWaveAhTocSuSu=AmpWaveZAhTocSuSu 
AmpVertexAhTocSuSu= AmpVertexZAhTocSuSu
End if
If (ShiftIRdiv) Then 
AmpVertexAhTocSuSu = AmpVertexAhTocSuSu  +  AmpVertexIRosAhTocSuSu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->conj[Su] Su -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumAhTocSuSu = AmpTreeAhTocSuSu 
 AmpSum2AhTocSuSu = AmpTreeAhTocSuSu + 2._dp*AmpWaveAhTocSuSu + 2._dp*AmpVertexAhTocSuSu  
Else 
 AmpSumAhTocSuSu = AmpTreeAhTocSuSu + AmpWaveAhTocSuSu + AmpVertexAhTocSuSu
 AmpSum2AhTocSuSu = AmpTreeAhTocSuSu + AmpWaveAhTocSuSu + AmpVertexAhTocSuSu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhTocSuSu = AmpTreeAhTocSuSu
 AmpSum2AhTocSuSu = AmpTreeAhTocSuSu 
End if 
Do gt1=1,3
i4 = isave 
  Do gt2=1,6
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MSuOS(gt2))+Abs(MSuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MSu(gt2))+Abs(MSu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2AhTocSuSu = AmpTreeAhTocSuSu
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSu(gt2),MSu(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqAhTocSuSu(gt1, gt2, gt3) 
  AmpSum2AhTocSuSu = 2._dp*AmpWaveAhTocSuSu
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSu(gt2),MSu(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqAhTocSuSu(gt1, gt2, gt3) 
  AmpSum2AhTocSuSu = 2._dp*AmpVertexAhTocSuSu
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSu(gt2),MSu(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqAhTocSuSu(gt1, gt2, gt3) 
  AmpSum2AhTocSuSu = AmpTreeAhTocSuSu + 2._dp*AmpWaveAhTocSuSu + 2._dp*AmpVertexAhTocSuSu
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSu(gt2),MSu(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqAhTocSuSu(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2AhTocSuSu = AmpTreeAhTocSuSu
  Call SquareAmp_StoSS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
  AmpSqTreeAhTocSuSu(gt1, gt2, gt3) = AmpSqAhTocSuSu(gt1, gt2, gt3)  
  AmpSum2AhTocSuSu = + 2._dp*AmpWaveAhTocSuSu + 2._dp*AmpVertexAhTocSuSu
  Call SquareAmp_StoSS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
  AmpSqAhTocSuSu(gt1, gt2, gt3) = AmpSqAhTocSuSu(gt1, gt2, gt3) + AmpSqTreeAhTocSuSu(gt1, gt2, gt3)  
Else  
  AmpSum2AhTocSuSu = AmpTreeAhTocSuSu
  Call SquareAmp_StoSS(MAh(gt1),MSu(gt2),MSu(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
  AmpSqTreeAhTocSuSu(gt1, gt2, gt3) = AmpSqAhTocSuSu(gt1, gt2, gt3)  
  AmpSum2AhTocSuSu = + 2._dp*AmpWaveAhTocSuSu + 2._dp*AmpVertexAhTocSuSu
  Call SquareAmp_StoSS(MAh(gt1),MSu(gt2),MSu(gt3),AmpSumAhTocSuSu(gt1, gt2, gt3),AmpSum2AhTocSuSu(gt1, gt2, gt3),AmpSqAhTocSuSu(gt1, gt2, gt3)) 
  AmpSqAhTocSuSu(gt1, gt2, gt3) = AmpSqAhTocSuSu(gt1, gt2, gt3) + AmpSqTreeAhTocSuSu(gt1, gt2, gt3)  
End if  
Else  
  AmpSqAhTocSuSu(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhTocSuSu(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAhOS(gt1),MSuOS(gt2),MSuOS(gt3),helfactor*AmpSqAhTocSuSu(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 3._dp*GammaTPS(MAh(gt1),MSu(gt2),MSu(gt3),helfactor*AmpSqAhTocSuSu(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhTocSuSu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocSuSu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPAhTocSuSu(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhTocSuSu(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPAhTocSuSu(gt1, gt2, gt3) + MRGAhTocSuSu(gt1, gt2, gt3)) 
  gP1LAh(gt1,i4) = gP1LAh(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPAhTocSuSu(gt1, gt2, gt3) + MRGAhTocSuSu(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LAh(gt1,i4) 
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
! Ah VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToAhVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MHpmOS,           & 
& MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,MHpm2OS,              & 
& MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,             & 
& cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,          & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP,          & 
& cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,               & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,AmpVertexAhToAhVP)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToAhVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MHpmOS,           & 
& MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,MHpm2OS,              & 
& MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,             & 
& cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,          & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP,          & 
& cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,               & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,AmpVertexAhToAhVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToAhVP(MAh,MCha,MFd,MFe,MFu,MHpm,MSd,MSe,               & 
& MSu,MVP,MVWm,MAh2,MCha2,MFd2,MFe2,MFu2,MHpm2,MSd2,MSe2,MSu2,MVP2,MVWm2,cplcChaChaAhL,  & 
& cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,             & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,          & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,            & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,AmpVertexAhToAhVP)

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
Do gt1=1,3
i4 = isave 
  Do gt2=2,3
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Ah VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToAhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,MFuOS,           & 
& MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,             & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,cplAhAhAh,            & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,               & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,           & 
& cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,              & 
& cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,           & 
& cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhHpmcVWmVZ1,            & 
& cplAhcHpmVWmVZ1,AmpVertexAhToAhVZ)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToAhVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,MFuOS,           & 
& MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,             & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,cplAhAhAh,            & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,               & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,           & 
& cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,              & 
& cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,           & 
& cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhHpmcVWmVZ1,            & 
& cplAhcHpmVWmVZ1,AmpVertexAhToAhVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToAhVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,              & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,          & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVZL,              & 
& cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,           & 
& cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,             & 
& cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplcHpmVWmVZ,               & 
& cplcVWmVWmVZ,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,AmpVertexAhToAhVZ)

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
Do gt1=1,3
i4 = isave 
  Do gt2=2,3
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Fv bar(Fv)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToFvcFv(MAhOS,MChaOS,MChiOS,MFeOS,MHpmOS,               & 
& MSeOS,MSvOS,MVWmOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,MHpm2OS,MSe2OS,MSv2OS,MVWm2OS,        & 
& cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,         & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,           & 
& cplChiFvcSvL,cplChiFvcSvR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,       & 
& cplcChacFvSeL,cplcChacFvSeR,AmpVertexAhToFvcFv)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToFvcFv(MAhOS,MChaOS,MChiOS,MFeOS,MHpmOS,               & 
& MSeOS,MSvOS,MVWmOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,MHpm2OS,MSe2OS,MSv2OS,MVWm2OS,        & 
& cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,         & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSecSe,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,           & 
& cplChiFvcSvL,cplChiFvcSvR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,       & 
& cplcChacFvSeL,cplcChacFvSeR,AmpVertexAhToFvcFv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToFvcFv(MAh,MCha,MChi,MFe,MHpm,MSe,MSv,MVWm,            & 
& MAh2,MCha2,MChi2,MFe2,MHpm2,MSe2,MSv2,MVWm2,cplcChaChaAhL,cplcChaChaAhR,               & 
& cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhHpmcHpm,cplAhHpmcVWm,           & 
& cplAhSecSe,cplAhcHpmVWm,cplChaFvcSeL,cplChaFvcSeR,cplChiFvcSvL,cplChiFvcSvR,           & 
& cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,     & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcChacFvSeL,cplcChacFvSeR,       & 
& AmpVertexAhToFvcFv)

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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(0.)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(0.)+Abs(0.))))) Then 
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Glu Glu
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToGluGlu(MAhOS,MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,          & 
& MAh2OS,MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,        & 
& cplcFuFuAhR,cplAhSdcSd,cplAhSucSu,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,              & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,AmpVertexAhToGluGlu)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToGluGlu(MAhOS,MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,          & 
& MAh2OS,MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,        & 
& cplcFuFuAhR,cplAhSdcSd,cplAhSucSu,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,              & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,AmpVertexAhToGluGlu)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToGluGlu(MAh,MFd,MFu,MGlu,MSd,MSu,MAh2,MFd2,            & 
& MFu2,MGlu2,MSd2,MSu2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,       & 
& cplAhSucSu,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,AmpVertexAhToGluGlu)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Glu Glu -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToGluGlu = 0._dp 
 AmpSum2AhToGluGlu = 0._dp  
Else 
 AmpSumAhToGluGlu = AmpVertexAhToGluGlu + AmpWaveAhToGluGlu
 AmpSum2AhToGluGlu = AmpVertexAhToGluGlu + AmpWaveAhToGluGlu 
End If 
Do gt1=1,3
i4 = isave 
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MGluOS)+Abs(MGluOS)))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MGlu)+Abs(MGlu))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoFF(MAhOS(gt1),MGluOS,MGluOS,AmpSumAhToGluGlu(:,gt1),AmpSum2AhToGluGlu(:,gt1),AmpSqAhToGluGlu(gt1)) 
Else  
  Call SquareAmp_StoFF(MAh(gt1),MGlu,MGlu,AmpSumAhToGluGlu(:,gt1),AmpSum2AhToGluGlu(:,gt1),AmpSqAhToGluGlu(gt1)) 
End if  
Else  
  AmpSqAhToGluGlu(gt1) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 4._dp 
If (AmpSqAhToGluGlu(gt1).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 4._dp*GammaTPS(MAhOS(gt1),MGluOS,MGluOS,helfactor*AmpSqAhToGluGlu(gt1))
Else 
  gP1LAh(gt1,i4) = 4._dp*GammaTPS(MAh(gt1),MGlu,MGlu,helfactor*AmpSqAhToGluGlu(gt1))
End if 
If ((Abs(MRPAhToGluGlu(gt1)).gt.1.0E-20_dp).or.(Abs(MRGAhToGluGlu(gt1)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! hh VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,MhhOS,          & 
& Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWaveAhTohhVP)

 Else 
Call Amplitude_WAVE_NMSSM_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAhOS,MAh2OS,MhhOS,          & 
& Mhh2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWaveAhTohhVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhTohhVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHpmOS,MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,               & 
& Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,          & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,           & 
& cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,               & 
& cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,               & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,AmpVertexAhTohhVP)

 Else 
Call Amplitude_VERTEX_NMSSM_AhTohhVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MhhOS,            & 
& MHpmOS,MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,               & 
& Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,          & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,           & 
& cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,       & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFehhL,cplcFeFehhR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,cplhhHpmcHpm,cplhhHpmcVWm,     & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcHpmVP,               & 
& cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,               & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplhhHpmcVWmVP1,cplhhcHpmVPVWm1,AmpVertexAhTohhVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAh,MAh2,Mhh,Mhh2,           & 
& MVP,MVP2,MVZ,MVZ2,ZfAh,Zfhh,ZfVP,ZfVZVP,AmpWaveAhTohhVP)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhTohhVP(MAh,MCha,MFd,MFe,MFu,Mhh,MHpm,MSd,               & 
& MSe,MSu,MVP,MVWm,MAh2,MCha2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,MSu2,MVP2,             & 
& MVWm2,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,         & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChahhL,cplcChaChahhR,             & 
& cplcChaChaVPL,cplcChaChaVPR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhcHpmVWm,               & 
& cplhhcVWmVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,               & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplhhHpmcVWmVP1,             & 
& cplhhcHpmVPVWm1,AmpVertexAhTohhVP)

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
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
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
If (gt1.eq.3) isave = i4 
End do
!---------------- 
! Sv Conjg(Sv)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToSvcSv(MAhOS,MChaOS,MChiOS,MFeOS,MhhOS,MHpmOS,         & 
& MSdOS,MSeOS,MSuOS,MSvOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,Mhh2OS,             & 
& MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplcChaChaAhL,            & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,             & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,     & 
& cplcFeChaSvL,cplcFeChaSvR,cplChiFvcSvL,cplChiFvcSvR,cplcFvChiSvL,cplcFvChiSvR,         & 
& cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplHpmSvcSe,cplSecHpmcSv,cplSecSvcVWm,          & 
& cplSvcSeVWm,cplSvcSvVZ,cplAhAhSvcSv1,cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSvcSv1,     & 
& cplHpmSvcHpmcSv1,cplSdSvcSdcSvaa,cplSeSvcSecSv1,cplSuSvcSucSvaa,AmpVertexAhToSvcSv)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToSvcSv(MAhOS,MChaOS,MChiOS,MFeOS,MhhOS,MHpmOS,         & 
& MSdOS,MSeOS,MSuOS,MSvOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFe2OS,Mhh2OS,             & 
& MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,MVWm2OS,MVZ2OS,cplAhAhAh,cplcChaChaAhL,            & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,cplcFeFeAhR,cplAhhhhh,             & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,     & 
& cplcFeChaSvL,cplcFeChaSvR,cplChiFvcSvL,cplChiFvcSvR,cplcFvChiSvL,cplcFvChiSvR,         & 
& cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplHpmSvcSe,cplSecHpmcSv,cplSecSvcVWm,          & 
& cplSvcSeVWm,cplSvcSvVZ,cplAhAhSvcSv1,cplAhHpmSvcSe1,cplAhSecHpmcSv1,cplhhhhSvcSv1,     & 
& cplHpmSvcHpmcSv1,cplSdSvcSdcSvaa,cplSeSvcSecSv1,cplSuSvcSucSvaa,AmpVertexAhToSvcSv)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToSvcSv(MAh,MCha,MChi,MFe,Mhh,MHpm,MSd,MSe,             & 
& MSu,MSv,MVWm,MVZ,MAh2,MCha2,MChi2,MFe2,Mhh2,MHpm2,MSd2,MSe2,MSu2,MSv2,MVWm2,           & 
& MVZ2,cplAhAhAh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFeFeAhL,      & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,       & 
& cplAhSucSu,cplAhcHpmVWm,cplcFeChaSvL,cplcFeChaSvR,cplChiFvcSvL,cplChiFvcSvR,           & 
& cplcFvChiSvL,cplcFvChiSvR,cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplHpmSvcSe,          & 
& cplSecHpmcSv,cplSecSvcVWm,cplSvcSeVWm,cplSvcSvVZ,cplAhAhSvcSv1,cplAhHpmSvcSe1,         & 
& cplAhSecHpmcSv1,cplhhhhSvcSv1,cplHpmSvcHpmcSv1,cplSdSvcSdcSvaa,cplSeSvcSecSv1,         & 
& cplSuSvcSucSvaa,AmpVertexAhToSvcSv)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Ah->Sv conj[Sv] -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumAhToSvcSv = 0._dp 
 AmpSum2AhToSvcSv = 0._dp  
Else 
 AmpSumAhToSvcSv = AmpVertexAhToSvcSv + AmpWaveAhToSvcSv
 AmpSum2AhToSvcSv = AmpVertexAhToSvcSv + AmpWaveAhToSvcSv 
End If 
Do gt1=1,3
i4 = isave 
  Do gt2=1,3
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MAhOS(gt1)).gt.(Abs(MSvOS(gt2))+Abs(MSvOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MAh(gt1)).gt.(Abs(MSv(gt2))+Abs(MSv(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_StoSS(MAhOS(gt1),MSvOS(gt2),MSvOS(gt3),AmpSumAhToSvcSv(gt1, gt2, gt3),AmpSum2AhToSvcSv(gt1, gt2, gt3),AmpSqAhToSvcSv(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_StoSS(MAh(gt1),MSv(gt2),MSv(gt3),AmpSumAhToSvcSv(gt1, gt2, gt3),AmpSum2AhToSvcSv(gt1, gt2, gt3),AmpSqAhToSvcSv(gt1, gt2, gt3)) 
End if  
Else  
  AmpSqAhToSvcSv(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 1._dp 
If (AmpSqAhToSvcSv(gt1, gt2, gt3).eq.0._dp) Then 
  gP1LAh(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAhOS(gt1),MSvOS(gt2),MSvOS(gt3),helfactor*AmpSqAhToSvcSv(gt1, gt2, gt3))
Else 
  gP1LAh(gt1,i4) = 1._dp*GammaTPS(MAh(gt1),MSv(gt2),MSv(gt3),helfactor*AmpSqAhToSvcSv(gt1, gt2, gt3))
End if 
If ((Abs(MRPAhToSvcSv(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGAhToSvcSv(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LAh(gt1,i4) 
End if 
i4=i4+1

    End do
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
Call Amplitude_VERTEX_NMSSM_AhToVGVG(MAhOS,MFdOS,MFuOS,MSdOS,MSuOS,MVG,               & 
& MAh2OS,MFd2OS,MFu2OS,MSd2OS,MSu2OS,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhSdcSd,cplAhSucSu,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,     & 
& cplSdcSdVG,cplSucSuVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,   & 
& AmpVertexAhToVGVG)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToVGVG(MAhOS,MFdOS,MFuOS,MSdOS,MSuOS,MVG,               & 
& MAh2OS,MFd2OS,MFu2OS,MSd2OS,MSu2OS,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,           & 
& cplcFuFuAhR,cplAhSdcSd,cplAhSucSu,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,     & 
& cplSdcSdVG,cplSucSuVG,cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,& 
& cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,   & 
& AmpVertexAhToVGVG)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToVGVG(MAh,MFd,MFu,MSd,MSu,MVG,MAh2,MFd2,               & 
& MFu2,MSd2,MSu2,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,        & 
& cplAhSucSu,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplSdcSdVG,cplSucSuVG,      & 
& cplSdcSdVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSdcSdVGVGsumj113Lamct3j1ct1Lamct4ct2j1,   & 
& cplSucSuVGVGsumj113Lamct3ct2j1Lamct4j1ct1,cplSucSuVGVGsumj113Lamct3j1ct1Lamct4ct2j1,   & 
& AmpVertexAhToVGVG)

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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VP VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToVPVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MHpmOS,           & 
& MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,MHpm2OS,              & 
& MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,             & 
& cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,          & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP,          & 
& cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,               & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplHpmcHpmVPVP1,cplSdcSdVPVPaa,cplSecSeVPVP1,          & 
& cplSucSuVPVPaa,AmpVertexAhToVPVP)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToVPVP(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MHpmOS,           & 
& MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,MHpm2OS,              & 
& MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,             & 
& cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,          & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP,          & 
& cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,cplcHpmVPVWm,cplcVWmVPVWm,               & 
& cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplHpmcHpmVPVP1,cplSdcSdVPVPaa,cplSecSeVPVP1,          & 
& cplSucSuVPVPaa,AmpVertexAhToVPVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToVPVP(MAh,MCha,MFd,MFe,MFu,MHpm,MSd,MSe,               & 
& MSu,MVP,MVWm,MAh2,MCha2,MFd2,MFe2,MFu2,MHpm2,MSd2,MSe2,MSu2,MVP2,MVWm2,cplcChaChaAhL,  & 
& cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,             & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,          & 
& cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,            & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSecSeVP,cplSucSuVP,             & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplAhHpmcVWmVP1,cplAhcHpmVPVWm1,cplHpmcHpmVPVP1,             & 
& cplSdcSdVPVPaa,cplSecSeVPVP1,cplSucSuVPVPaa,AmpVertexAhToVPVP)

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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VP VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToVPVZ(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MHpmOS,           & 
& MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,MHpm2OS,        & 
& MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,MVZ2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,      & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,             & 
& cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,     & 
& cplHpmcVWmVZ,cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,        & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,   & 
& cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplHpmcHpmVPVZ1,cplSdcSdVPVZaa,cplSecSeVPVZ1,          & 
& cplSucSuVPVZaa,AmpVertexAhToVPVZ)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToVPVZ(MAhOS,MChaOS,MFdOS,MFeOS,MFuOS,MHpmOS,           & 
& MSdOS,MSeOS,MSuOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MFd2OS,MFe2OS,MFu2OS,MHpm2OS,        & 
& MSd2OS,MSe2OS,MSu2OS,MVP2,MVWm2OS,MVZ2OS,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,      & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,             & 
& cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcFdFdVPL,      & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,     & 
& cplHpmcVWmVZ,cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,        & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,   & 
& cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplHpmcHpmVPVZ1,cplSdcSdVPVZaa,cplSecSeVPVZ1,          & 
& cplSucSuVPVZaa,AmpVertexAhToVPVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToVPVZ(MAh,MCha,MFd,MFe,MFu,MHpm,MSd,MSe,               & 
& MSu,MVP,MVWm,MVZ,MAh2,MCha2,MFd2,MFe2,MFu2,MHpm2,MSd2,MSe2,MSu2,MVP2,MVWm2,            & 
& MVZ2,cplcChaChaAhL,cplcChaChaAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,      & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHpmcHpm,cplAhHpmcVWm,         & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVPL,cplcChaChaVPR,             & 
& cplcChaChaVZL,cplcChaChaVZR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,           & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,       & 
& cplHpmcHpmVP,cplHpmcVWmVP,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVP,cplSdcSdVZ,             & 
& cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,    & 
& cplcVWmVWmVZ,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,          & 
& cplHpmcHpmVPVZ1,cplSdcSdVPVZaa,cplSecSeVPVZ1,cplSucSuVPVZaa,AmpVertexAhToVPVZ)

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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VWm Conjg(VWm)
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToVWmcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacVWmL,             & 
& cplChiChacVWmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,              & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,       & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgAgWpCVWm,cplcgZgWpCVWm,   & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcVWmVP,       & 
& cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,cplSucSdVWm,cplSvcSeVWm,cplcHpmVPVWm,           & 
& cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,& 
& cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhcVWmVWm1,cplHpmcHpmcVWmVWm1,cplSdcSdcVWmVWmaa,  & 
& cplSecSecVWmVWm1,cplSucSucVWmVWmaa,AmpVertexAhToVWmcVWm)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToVWmcVWm(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,              & 
& MFuOS,MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MSvOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,            & 
& MChi2OS,MFd2OS,MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MSv2OS,               & 
& MVP2,MVWm2OS,MVZ2OS,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,      & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplChiChacVWmL,             & 
& cplChiChacVWmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,              & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,cplcFeFvVWmR,       & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgAgWpCVWm,cplcgZgWpCVWm,   & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplHpmcVWmVP,       & 
& cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,cplSucSdVWm,cplSvcSeVWm,cplcHpmVPVWm,           & 
& cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,cplAhHpmcVWmVZ1,& 
& cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhcVWmVWm1,cplHpmcHpmcVWmVWm1,cplSdcSdcVWmVWmaa,  & 
& cplSecSecVWmVWm1,cplSucSucVWmVWmaa,AmpVertexAhToVWmcVWm)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToVWmcVWm(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,           & 
& MSd,MSe,MSu,MSv,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,               & 
& MSd2,MSe2,MSu2,MSv2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,   & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,               & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,               & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFvVWmL,      & 
& cplcFeFvVWmR,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgAgWpCVWm,    & 
& cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,      & 
& cplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSucVWm,cplSecSvcVWm,cplSucSdVWm,cplSvcSeVWm,           & 
& cplcHpmVPVWm,cplcVWmVPVWm,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHpmcVWmVP1,   & 
& cplAhHpmcVWmVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhcVWmVWm1,cplHpmcHpmcVWmVWm1,    & 
& cplSdcSdcVWmVWmaa,cplSecSecVWmVWm1,cplSucSucVWmVWmaa,AmpVertexAhToVWmcVWm)

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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
!---------------- 
! VZ VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_AhToVZVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,MFuOS,           & 
& MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,             & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,cplAhAhAh,            & 
& cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,        & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,              & 
& cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,     & 
& cplhhhhVZVZ1,cplHpmcHpmVZVZ1,cplSdcSdVZVZaa,cplSecSeVZVZ1,cplSucSuVZVZaa,              & 
& AmpVertexAhToVZVZ)

 Else 
Call Amplitude_VERTEX_NMSSM_AhToVZVZ(MAhOS,MChaOS,MChiOS,MFdOS,MFeOS,MFuOS,           & 
& MhhOS,MHpmOS,MSdOS,MSeOS,MSuOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,MFd2OS,             & 
& MFe2OS,MFu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSe2OS,MSu2OS,MVWm2OS,MVZ2OS,cplAhAhAh,            & 
& cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,        & 
& cplAhcHpmVWm,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,        & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,              & 
& cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,     & 
& cplhhhhVZVZ1,cplHpmcHpmVZVZ1,cplSdcSdVZVZaa,cplSecSeVZVZ1,cplSucSuVZVZaa,              & 
& AmpVertexAhToVZVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_AhToVZVZ(MAh,MCha,MChi,MFd,MFe,MFu,Mhh,MHpm,              & 
& MSd,MSe,MSu,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFe2,MFu2,Mhh2,MHpm2,MSd2,MSe2,             & 
& MSu2,MVWm2,MVZ2,cplAhAhAh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplAhcHpmVWm,cplcChaChaVZL,cplcChaChaVZR,             & 
& cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,               & 
& cplAhAhVZVZ1,cplAhHpmcVWmVZ1,cplAhcHpmVWmVZ1,cplhhhhVZVZ1,cplHpmcHpmVZVZ1,             & 
& cplSdcSdVZVZaa,cplSecSeVZVZ1,cplSucSuVZVZaa,AmpVertexAhToVZVZ)

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
Do gt1=1,3
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

If (gt1.eq.3) isave = i4 
End do
End Subroutine OneLoopDecay_Ah

End Module Wrapper_OneLoopDecay_Ah_NMSSM
