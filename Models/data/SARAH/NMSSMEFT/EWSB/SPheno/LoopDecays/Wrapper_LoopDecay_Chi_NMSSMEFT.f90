! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.12.3 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 17:31 on 22.10.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Chi_NMSSMEFT
Use Model_Data_NMSSMEFT 
Use Kinematics 
Use OneLoopDecay_Chi_NMSSMEFT 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Chi(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,             & 
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
& ZfFDL,ZfFDR,ZfFUL,ZfFUR,ZfVPVZ,ZfVZVP,cplAhAhAh,cplAhAhhh,cplAhcHpmVWm,cplAhhhhh,      & 
& cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,         & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,  & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplChiChacHpmL,cplChiChacHpmR,            & 
& cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,         & 
& cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhVZVZ,               & 
& cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,ctcplChiChacHpmL,ctcplChiChacHpmR, & 
& ctcplChiChacVWmL,ctcplChiChacVWmR,ctcplChiChiAhL,ctcplChiChiAhR,ctcplChiChihhL,        & 
& ctcplChiChihhR,ctcplChiChiVZL,ctcplChiChiVZR,GcplChiChacHpmL,GcplChiChacHpmR,          & 
& GcplcHpmVPVWm,GcplHpmcVWmVP,GosZcplChiChacHpmL,GosZcplChiChacHpmR,GosZcplcHpmVPVWm,    & 
& GosZcplHpmcVWmVP,GZcplChiChacHpmL,GZcplChiChacHpmR,GZcplcHpmVPVWm,GZcplHpmcVWmVP,      & 
& ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplcChaChiHpmL,ZcplcChaChiHpmR,ZcplcChaChiVWmL,         & 
& ZcplcChaChiVWmR,ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplChiChacVWmL,ZcplChiChacVWmR,       & 
& ZcplChiChiAhL,ZcplChiChiAhR,ZcplChiChihhL,ZcplChiChihhR,ZcplChiChiVZL,ZcplChiChiVZR,   & 
& ZcplcHpmVPVWm,ZcplcVWmVPVWm,ZcplHpmcHpmVP,ZcplHpmcVWmVP,ZRUZD,ZRUZV,ZRUZU,             & 
& ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,ZRUZDR,ZRUZUL,          & 
& ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LChi)

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

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhcHpmVWm(3,2),cplAhhhhh(3,3,3),cplAhhhVZ(3,3),  & 
& cplAhHpmcHpm(3,2,2),cplAhHpmcVWm(3,2),cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),       & 
& cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),       & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),     & 
& cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),   & 
& cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),       & 
& cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplChiChiVZL(5,5),cplChiChiVZR(5,5),           & 
& cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHpmVWm(3,2),           & 
& cplhhcVWmVWm(3),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplhhHpmcVWm(3,2),cplhhVZVZ(3),   & 
& cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),cplHpmcVWmVP(2),cplHpmcVWmVZ(2),ctcplChiChacHpmL(5,2,2),& 
& ctcplChiChacHpmR(5,2,2),ctcplChiChacVWmL(5,2),ctcplChiChacVWmR(5,2),ctcplChiChiAhL(5,5,3),& 
& ctcplChiChiAhR(5,5,3),ctcplChiChihhL(5,5,3),ctcplChiChihhR(5,5,3),ctcplChiChiVZL(5,5), & 
& ctcplChiChiVZR(5,5),GcplChiChacHpmL(5,2,2),GcplChiChacHpmR(5,2,2),GcplcHpmVPVWm(2),    & 
& GcplHpmcVWmVP(2),GosZcplChiChacHpmL(5,2,2),GosZcplChiChacHpmR(5,2,2),GosZcplcHpmVPVWm(2),& 
& GosZcplHpmcVWmVP(2),GZcplChiChacHpmL(5,2,2),GZcplChiChacHpmR(5,2,2),GZcplcHpmVPVWm(2), & 
& GZcplHpmcVWmVP(2),ZcplcChaChaVPL(2,2),ZcplcChaChaVPR(2,2),ZcplcChaChiHpmL(2,5,2),      & 
& ZcplcChaChiHpmR(2,5,2),ZcplcChaChiVWmL(2,5),ZcplcChaChiVWmR(2,5),ZcplChiChacHpmL(5,2,2),& 
& ZcplChiChacHpmR(5,2,2),ZcplChiChacVWmL(5,2),ZcplChiChacVWmR(5,2),ZcplChiChiAhL(5,5,3), & 
& ZcplChiChiAhR(5,5,3),ZcplChiChihhL(5,5,3),ZcplChiChihhR(5,5,3),ZcplChiChiVZL(5,5),     & 
& ZcplChiChiVZR(5,5),ZcplcHpmVPVWm(2),ZcplcVWmVPVWm,ZcplHpmcHpmVP(2,2),ZcplHpmcVWmVP(2)

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
Real(dp), Intent(out) :: gP1LChi(5,39) 
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
Real(dp) :: MRPChiToChiAh(5,5,3),MRGChiToChiAh(5,5,3), MRPZChiToChiAh(5,5,3),MRGZChiToChiAh(5,5,3) 
Real(dp) :: MVPChiToChiAh(5,5,3) 
Real(dp) :: RMsqTreeChiToChiAh(5,5,3),RMsqWaveChiToChiAh(5,5,3),RMsqVertexChiToChiAh(5,5,3) 
Complex(dp) :: AmpTreeChiToChiAh(2,5,5,3),AmpWaveChiToChiAh(2,5,5,3)=(0._dp,0._dp),AmpVertexChiToChiAh(2,5,5,3)& 
 & ,AmpVertexIRosChiToChiAh(2,5,5,3),AmpVertexIRdrChiToChiAh(2,5,5,3), AmpSumChiToChiAh(2,5,5,3), AmpSum2ChiToChiAh(2,5,5,3) 
Complex(dp) :: AmpTreeZChiToChiAh(2,5,5,3),AmpWaveZChiToChiAh(2,5,5,3),AmpVertexZChiToChiAh(2,5,5,3) 
Real(dp) :: AmpSqChiToChiAh(5,5,3),  AmpSqTreeChiToChiAh(5,5,3) 
Real(dp) :: MRPChiToChacHpm(5,2,2),MRGChiToChacHpm(5,2,2), MRPZChiToChacHpm(5,2,2),MRGZChiToChacHpm(5,2,2) 
Real(dp) :: MVPChiToChacHpm(5,2,2) 
Real(dp) :: RMsqTreeChiToChacHpm(5,2,2),RMsqWaveChiToChacHpm(5,2,2),RMsqVertexChiToChacHpm(5,2,2) 
Complex(dp) :: AmpTreeChiToChacHpm(2,5,2,2),AmpWaveChiToChacHpm(2,5,2,2)=(0._dp,0._dp),AmpVertexChiToChacHpm(2,5,2,2)& 
 & ,AmpVertexIRosChiToChacHpm(2,5,2,2),AmpVertexIRdrChiToChacHpm(2,5,2,2), AmpSumChiToChacHpm(2,5,2,2), AmpSum2ChiToChacHpm(2,5,2,2) 
Complex(dp) :: AmpTreeZChiToChacHpm(2,5,2,2),AmpWaveZChiToChacHpm(2,5,2,2),AmpVertexZChiToChacHpm(2,5,2,2) 
Real(dp) :: AmpSqChiToChacHpm(5,2,2),  AmpSqTreeChiToChacHpm(5,2,2) 
Real(dp) :: MRPChiToChacVWm(5,2),MRGChiToChacVWm(5,2), MRPZChiToChacVWm(5,2),MRGZChiToChacVWm(5,2) 
Real(dp) :: MVPChiToChacVWm(5,2) 
Real(dp) :: RMsqTreeChiToChacVWm(5,2),RMsqWaveChiToChacVWm(5,2),RMsqVertexChiToChacVWm(5,2) 
Complex(dp) :: AmpTreeChiToChacVWm(4,5,2),AmpWaveChiToChacVWm(4,5,2)=(0._dp,0._dp),AmpVertexChiToChacVWm(4,5,2)& 
 & ,AmpVertexIRosChiToChacVWm(4,5,2),AmpVertexIRdrChiToChacVWm(4,5,2), AmpSumChiToChacVWm(4,5,2), AmpSum2ChiToChacVWm(4,5,2) 
Complex(dp) :: AmpTreeZChiToChacVWm(4,5,2),AmpWaveZChiToChacVWm(4,5,2),AmpVertexZChiToChacVWm(4,5,2) 
Real(dp) :: AmpSqChiToChacVWm(5,2),  AmpSqTreeChiToChacVWm(5,2) 
Real(dp) :: MRPChiToChihh(5,5,3),MRGChiToChihh(5,5,3), MRPZChiToChihh(5,5,3),MRGZChiToChihh(5,5,3) 
Real(dp) :: MVPChiToChihh(5,5,3) 
Real(dp) :: RMsqTreeChiToChihh(5,5,3),RMsqWaveChiToChihh(5,5,3),RMsqVertexChiToChihh(5,5,3) 
Complex(dp) :: AmpTreeChiToChihh(2,5,5,3),AmpWaveChiToChihh(2,5,5,3)=(0._dp,0._dp),AmpVertexChiToChihh(2,5,5,3)& 
 & ,AmpVertexIRosChiToChihh(2,5,5,3),AmpVertexIRdrChiToChihh(2,5,5,3), AmpSumChiToChihh(2,5,5,3), AmpSum2ChiToChihh(2,5,5,3) 
Complex(dp) :: AmpTreeZChiToChihh(2,5,5,3),AmpWaveZChiToChihh(2,5,5,3),AmpVertexZChiToChihh(2,5,5,3) 
Real(dp) :: AmpSqChiToChihh(5,5,3),  AmpSqTreeChiToChihh(5,5,3) 
Real(dp) :: MRPChiToChiVZ(5,5),MRGChiToChiVZ(5,5), MRPZChiToChiVZ(5,5),MRGZChiToChiVZ(5,5) 
Real(dp) :: MVPChiToChiVZ(5,5) 
Real(dp) :: RMsqTreeChiToChiVZ(5,5),RMsqWaveChiToChiVZ(5,5),RMsqVertexChiToChiVZ(5,5) 
Complex(dp) :: AmpTreeChiToChiVZ(4,5,5),AmpWaveChiToChiVZ(4,5,5)=(0._dp,0._dp),AmpVertexChiToChiVZ(4,5,5)& 
 & ,AmpVertexIRosChiToChiVZ(4,5,5),AmpVertexIRdrChiToChiVZ(4,5,5), AmpSumChiToChiVZ(4,5,5), AmpSum2ChiToChiVZ(4,5,5) 
Complex(dp) :: AmpTreeZChiToChiVZ(4,5,5),AmpWaveZChiToChiVZ(4,5,5),AmpVertexZChiToChiVZ(4,5,5) 
Real(dp) :: AmpSqChiToChiVZ(5,5),  AmpSqTreeChiToChiVZ(5,5) 
Real(dp) :: MRPChiToChiVP(5,5),MRGChiToChiVP(5,5), MRPZChiToChiVP(5,5),MRGZChiToChiVP(5,5) 
Real(dp) :: MVPChiToChiVP(5,5) 
Real(dp) :: RMsqTreeChiToChiVP(5,5),RMsqWaveChiToChiVP(5,5),RMsqVertexChiToChiVP(5,5) 
Complex(dp) :: AmpTreeChiToChiVP(4,5,5),AmpWaveChiToChiVP(4,5,5)=(0._dp,0._dp),AmpVertexChiToChiVP(4,5,5)& 
 & ,AmpVertexIRosChiToChiVP(4,5,5),AmpVertexIRdrChiToChiVP(4,5,5), AmpSumChiToChiVP(4,5,5), AmpSum2ChiToChiVP(4,5,5) 
Complex(dp) :: AmpTreeZChiToChiVP(4,5,5),AmpWaveZChiToChiVP(4,5,5),AmpVertexZChiToChiVP(4,5,5) 
Real(dp) :: AmpSqChiToChiVP(5,5),  AmpSqTreeChiToChiVP(5,5) 
Write(*,*) "Calculating one-loop decays of Chi " 
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
! Chi Ah
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_ChiToChiAh(cplChiChiAhL,cplChiChiAhR,MAh,MChi,           & 
& MAh2,MChi2,AmpTreeChiToChiAh)

  Else 
Call Amplitude_Tree_NMSSMEFT_ChiToChiAh(ZcplChiChiAhL,ZcplChiChiAhR,MAh,              & 
& MChi,MAh2,MChi2,AmpTreeChiToChiAh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChiAh(MLambda,em,gs,cplChiChiAhL,cplChiChiAhR,          & 
& MAhOS,MChiOS,MRPChiToChiAh,MRGChiToChiAh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChiAh(MLambda,em,gs,ZcplChiChiAhL,ZcplChiChiAhR,        & 
& MAhOS,MChiOS,MRPChiToChiAh,MRGChiToChiAh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_ChiToChiAh(MLambda,em,gs,cplChiChiAhL,cplChiChiAhR,          & 
& MAh,MChi,MRPChiToChiAh,MRGChiToChiAh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChiAh(MLambda,em,gs,ZcplChiChiAhL,ZcplChiChiAhR,        & 
& MAh,MChi,MRPChiToChiAh,MRGChiToChiAh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_ChiToChiAh(cplChiChiAhL,cplChiChiAhR,ctcplChiChiAhL,     & 
& ctcplChiChiAhR,MAh,MAh2,MChi,MChi2,ZfAh,ZfL0,AmpWaveChiToChiAh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChiAh(MAh,MCha,MChi,Mhh,MHpm,MVWm,MVZ,            & 
& MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexChiToChiAh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiAh(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRdrChiToChiAh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiAh(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,ZcplChiChiAhL,ZcplChiChiAhR,           & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,             & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,   & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& AmpVertexIRosChiToChiAh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiAh(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,          & 
& cplcChaChaAhR,ZcplChiChiAhL,ZcplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,            & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRosChiToChiAh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiAh(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplAhAhAh,cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,             & 
& cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,             & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,   & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& AmpVertexIRosChiToChiAh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiAh(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcChaChaAhL,          & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcChaChiVWmL,cplcChaChiVWmR,AmpVertexIRosChiToChiAh)

 End if 
 End if 
AmpVertexChiToChiAh = AmpVertexChiToChiAh -  AmpVertexIRdrChiToChiAh! +  AmpVertexIRosChiToChiAh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZChiToChiAh=0._dp 
AmpVertexZChiToChiAh=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChiAh(1,gt2,:,:) = AmpWaveZChiToChiAh(1,gt2,:,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChiAh(1,gt1,:,:) 
AmpVertexZChiToChiAh(1,gt2,:,:)= AmpVertexZChiToChiAh(1,gt2,:,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChiAh(1,gt1,:,:) 
AmpWaveZChiToChiAh(2,gt2,:,:) = AmpWaveZChiToChiAh(2,gt2,:,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChiAh(2,gt1,:,:) 
AmpVertexZChiToChiAh(2,gt2,:,:)= AmpVertexZChiToChiAh(2,gt2,:,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChiAh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveChiToChiAh=AmpWaveZChiToChiAh 
AmpVertexChiToChiAh= AmpVertexZChiToChiAh
! Final State 1 
AmpWaveZChiToChiAh=0._dp 
AmpVertexZChiToChiAh=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChiAh(1,:,gt2,:) = AmpWaveZChiToChiAh(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChiAh(1,:,gt1,:) 
AmpVertexZChiToChiAh(1,:,gt2,:)= AmpVertexZChiToChiAh(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpVertexChiToChiAh(1,:,gt1,:) 
AmpWaveZChiToChiAh(2,:,gt2,:) = AmpWaveZChiToChiAh(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChiAh(2,:,gt1,:) 
AmpVertexZChiToChiAh(2,:,gt2,:)= AmpVertexZChiToChiAh(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpVertexChiToChiAh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveChiToChiAh=AmpWaveZChiToChiAh 
AmpVertexChiToChiAh= AmpVertexZChiToChiAh
! Final State 2 
AmpWaveZChiToChiAh=0._dp 
AmpVertexZChiToChiAh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZChiToChiAh(:,:,:,gt2) = AmpWaveZChiToChiAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpWaveChiToChiAh(:,:,:,gt1) 
AmpVertexZChiToChiAh(:,:,:,gt2)= AmpVertexZChiToChiAh(:,:,:,gt2)+ZRUZA(gt2,gt1)*AmpVertexChiToChiAh(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveChiToChiAh=AmpWaveZChiToChiAh 
AmpVertexChiToChiAh= AmpVertexZChiToChiAh
End if
If (ShiftIRdiv) Then 
AmpVertexChiToChiAh = AmpVertexChiToChiAh  +  AmpVertexIRosChiToChiAh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Chi->Chi Ah -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumChiToChiAh = AmpTreeChiToChiAh 
 AmpSum2ChiToChiAh = AmpTreeChiToChiAh + 2._dp*AmpWaveChiToChiAh + 2._dp*AmpVertexChiToChiAh  
Else 
 AmpSumChiToChiAh = AmpTreeChiToChiAh + AmpWaveChiToChiAh + AmpVertexChiToChiAh
 AmpSum2ChiToChiAh = AmpTreeChiToChiAh + AmpWaveChiToChiAh + AmpVertexChiToChiAh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumChiToChiAh = AmpTreeChiToChiAh
 AmpSum2ChiToChiAh = AmpTreeChiToChiAh 
End if 
Do gt1=1,5
i4 = isave 
  Do gt2=1,5
    Do gt3=2,3
If (((OSkinematics).and.(MChiOS(gt1).gt.(MChiOS(gt2)+MAhOS(gt3)))).or.((.not.OSkinematics).and.(MChi(gt1).gt.(MChi(gt2)+MAh(gt3))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2ChiToChiAh = AmpTreeChiToChiAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),MAh(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqChiToChiAh(gt1, gt2, gt3) 
  AmpSum2ChiToChiAh = 2._dp*AmpWaveChiToChiAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),MAh(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqChiToChiAh(gt1, gt2, gt3) 
  AmpSum2ChiToChiAh = 2._dp*AmpVertexChiToChiAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),MAh(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqChiToChiAh(gt1, gt2, gt3) 
  AmpSum2ChiToChiAh = AmpTreeChiToChiAh + 2._dp*AmpWaveChiToChiAh + 2._dp*AmpVertexChiToChiAh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),MAh(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqChiToChiAh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2ChiToChiAh = AmpTreeChiToChiAh
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
  AmpSqTreeChiToChiAh(gt1, gt2, gt3) = AmpSqChiToChiAh(gt1, gt2, gt3)  
  AmpSum2ChiToChiAh = + 2._dp*AmpWaveChiToChiAh + 2._dp*AmpVertexChiToChiAh
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
  AmpSqChiToChiAh(gt1, gt2, gt3) = AmpSqChiToChiAh(gt1, gt2, gt3) + AmpSqTreeChiToChiAh(gt1, gt2, gt3)  
Else  
  AmpSum2ChiToChiAh = AmpTreeChiToChiAh
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),MAh(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
  AmpSqTreeChiToChiAh(gt1, gt2, gt3) = AmpSqChiToChiAh(gt1, gt2, gt3)  
  AmpSum2ChiToChiAh = + 2._dp*AmpWaveChiToChiAh + 2._dp*AmpVertexChiToChiAh
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),MAh(gt3),AmpSumChiToChiAh(:,gt1, gt2, gt3),AmpSum2ChiToChiAh(:,gt1, gt2, gt3),AmpSqChiToChiAh(gt1, gt2, gt3)) 
  AmpSqChiToChiAh(gt1, gt2, gt3) = AmpSqChiToChiAh(gt1, gt2, gt3) + AmpSqTreeChiToChiAh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqChiToChiAh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqChiToChiAh(gt1, gt2, gt3).le.0._dp) Then 
  gP1LChi(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChiOS(gt1),MChiOS(gt2),MAhOS(gt3),helfactor*AmpSqChiToChiAh(gt1, gt2, gt3))
Else 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChi(gt1),MChi(gt2),MAh(gt3),helfactor*AmpSqChiToChiAh(gt1, gt2, gt3))
End if 
If ((Abs(MRPChiToChiAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGChiToChiAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LChi(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPChiToChiAh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGChiToChiAh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPChiToChiAh(gt1, gt2, gt3) + MRGChiToChiAh(gt1, gt2, gt3)) 
  gP1LChi(gt1,i4) = gP1LChi(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPChiToChiAh(gt1, gt2, gt3) + MRGChiToChiAh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LChi(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.5) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Cha Conjg(Hpm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_ChiToChacHpm(cplChiChacHpmL,cplChiChacHpmR,              & 
& MCha,MChi,MHpm,MCha2,MChi2,MHpm2,AmpTreeChiToChacHpm)

  Else 
Call Amplitude_Tree_NMSSMEFT_ChiToChacHpm(ZcplChiChacHpmL,ZcplChiChacHpmR,            & 
& MCha,MChi,MHpm,MCha2,MChi2,MHpm2,AmpTreeChiToChacHpm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChacHpm(MLambda,em,gs,cplChiChacHpmL,cplChiChacHpmR,    & 
& MChaOS,MChiOS,MHpmOS,MRPChiToChacHpm,MRGChiToChacHpm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChacHpm(MLambda,em,gs,ZcplChiChacHpmL,ZcplChiChacHpmR,  & 
& MChaOS,MChiOS,MHpmOS,MRPChiToChacHpm,MRGChiToChacHpm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_ChiToChacHpm(MLambda,em,gs,cplChiChacHpmL,cplChiChacHpmR,    & 
& MCha,MChi,MHpm,MRPChiToChacHpm,MRGChiToChacHpm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChacHpm(MLambda,em,gs,ZcplChiChacHpmL,ZcplChiChacHpmR,  & 
& MCha,MChi,MHpm,MRPChiToChacHpm,MRGChiToChacHpm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_ChiToChacHpm(cplChiChacHpmL,cplChiChacHpmR,              & 
& ctcplChiChacHpmL,ctcplChiChacHpmR,MCha,MCha2,MChi,MChi2,MHpm,MHpm2,ZfHpm,              & 
& ZfL0,ZfLm,ZfLp,AmpWaveChiToChacHpm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChacHpm(MAh,MCha,MChi,Mhh,MHpm,MVP,               & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,               & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& AmpVertexChiToChacHpm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacHpm(MAh,MCha,MChi,Mhh,MHpm,MVP,            & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,               & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& AmpVertexIRdrChiToChacHpm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacHpm(MAhOS,MChaOS,MChiOS,MhhOS,             & 
& MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& MVZ2OS,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhHpmcHpm,             & 
& cplAhcHpmVWm,ZcplChiChacHpmL,ZcplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,            & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,     & 
& cplcHpmVPVWm,cplcHpmVWmVZ,AmpVertexIRosChiToChacHpm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacHpm(MAh,MCha,MChi,Mhh,MHpm,MVP,            & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcHpm,cplAhcHpmVWm,ZcplChiChacHpmL,ZcplChiChacHpmR,   & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,               & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& AmpVertexIRosChiToChacHpm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacHpm(MAhOS,MChaOS,MChiOS,MhhOS,             & 
& MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& MVZ2OS,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhHpmcHpm,             & 
& cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,              & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,     & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,     & 
& cplcHpmVPVWm,cplcHpmVWmVZ,AmpVertexIRosChiToChacHpm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacHpm(MAh,MCha,MChi,Mhh,MHpm,MVP,            & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcHpm,cplAhcHpmVWm,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,               & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& AmpVertexIRosChiToChacHpm)

 End if 
 End if 
AmpVertexChiToChacHpm = AmpVertexChiToChacHpm -  AmpVertexIRdrChiToChacHpm! +  AmpVertexIRosChiToChacHpm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZChiToChacHpm=0._dp 
AmpVertexZChiToChacHpm=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChacHpm(1,gt2,:,:) = AmpWaveZChiToChacHpm(1,gt2,:,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChacHpm(1,gt1,:,:) 
AmpVertexZChiToChacHpm(1,gt2,:,:)= AmpVertexZChiToChacHpm(1,gt2,:,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChacHpm(1,gt1,:,:) 
AmpWaveZChiToChacHpm(2,gt2,:,:) = AmpWaveZChiToChacHpm(2,gt2,:,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChacHpm(2,gt1,:,:) 
AmpVertexZChiToChacHpm(2,gt2,:,:)= AmpVertexZChiToChacHpm(2,gt2,:,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChacHpm(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveChiToChacHpm=AmpWaveZChiToChacHpm 
AmpVertexChiToChacHpm= AmpVertexZChiToChacHpm
! Final State 1 
AmpWaveZChiToChacHpm=0._dp 
AmpVertexZChiToChacHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZChiToChacHpm(1,:,gt2,:) = AmpWaveZChiToChacHpm(1,:,gt2,:)+ZRUUM(gt2,gt1)*AmpWaveChiToChacHpm(1,:,gt1,:) 
AmpVertexZChiToChacHpm(1,:,gt2,:)= AmpVertexZChiToChacHpm(1,:,gt2,:)+ZRUUM(gt2,gt1)*AmpVertexChiToChacHpm(1,:,gt1,:) 
AmpWaveZChiToChacHpm(2,:,gt2,:) = AmpWaveZChiToChacHpm(2,:,gt2,:)+ZRUUPc(gt2,gt1)*AmpWaveChiToChacHpm(2,:,gt1,:) 
AmpVertexZChiToChacHpm(2,:,gt2,:)= AmpVertexZChiToChacHpm(2,:,gt2,:)+ZRUUPc(gt2,gt1)*AmpVertexChiToChacHpm(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveChiToChacHpm=AmpWaveZChiToChacHpm 
AmpVertexChiToChacHpm= AmpVertexZChiToChacHpm
! Final State 2 
AmpWaveZChiToChacHpm=0._dp 
AmpVertexZChiToChacHpm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZChiToChacHpm(:,:,:,gt2) = AmpWaveZChiToChacHpm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpWaveChiToChacHpm(:,:,:,gt1) 
AmpVertexZChiToChacHpm(:,:,:,gt2)= AmpVertexZChiToChacHpm(:,:,:,gt2)+ZRUZP(gt2,gt1)*AmpVertexChiToChacHpm(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveChiToChacHpm=AmpWaveZChiToChacHpm 
AmpVertexChiToChacHpm= AmpVertexZChiToChacHpm
End if
If (ShiftIRdiv) Then 
AmpVertexChiToChacHpm = AmpVertexChiToChacHpm  +  AmpVertexIRosChiToChacHpm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Chi->Cha conj[Hpm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumChiToChacHpm = AmpTreeChiToChacHpm 
 AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm + 2._dp*AmpWaveChiToChacHpm + 2._dp*AmpVertexChiToChacHpm  
Else 
 AmpSumChiToChacHpm = AmpTreeChiToChacHpm + AmpWaveChiToChacHpm + AmpVertexChiToChacHpm
 AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm + AmpWaveChiToChacHpm + AmpVertexChiToChacHpm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumChiToChacHpm = AmpTreeChiToChacHpm
 AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm 
End if 
Do gt1=1,5
i4 = isave 
  Do gt2=1,2
    Do gt3=2,2
If (((OSkinematics).and.(MChiOS(gt1).gt.(MChaOS(gt2)+MHpmOS(gt3)))).or.((.not.OSkinematics).and.(MChi(gt1).gt.(MCha(gt2)+MHpm(gt3))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MCha(gt2),MHpm(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqChiToChacHpm(gt1, gt2, gt3) 
  AmpSum2ChiToChacHpm = 2._dp*AmpWaveChiToChacHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MCha(gt2),MHpm(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqChiToChacHpm(gt1, gt2, gt3) 
  AmpSum2ChiToChacHpm = 2._dp*AmpVertexChiToChacHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MCha(gt2),MHpm(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqChiToChacHpm(gt1, gt2, gt3) 
  AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm + 2._dp*AmpWaveChiToChacHpm + 2._dp*AmpVertexChiToChacHpm
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MCha(gt2),MHpm(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqChiToChacHpm(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm
  Call SquareAmp_FtoFS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
  AmpSqTreeChiToChacHpm(gt1, gt2, gt3) = AmpSqChiToChacHpm(gt1, gt2, gt3)  
  AmpSum2ChiToChacHpm = + 2._dp*AmpWaveChiToChacHpm + 2._dp*AmpVertexChiToChacHpm
  Call SquareAmp_FtoFS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
  AmpSqChiToChacHpm(gt1, gt2, gt3) = AmpSqChiToChacHpm(gt1, gt2, gt3) + AmpSqTreeChiToChacHpm(gt1, gt2, gt3)  
Else  
  AmpSum2ChiToChacHpm = AmpTreeChiToChacHpm
  Call SquareAmp_FtoFS(MChi(gt1),MCha(gt2),MHpm(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
  AmpSqTreeChiToChacHpm(gt1, gt2, gt3) = AmpSqChiToChacHpm(gt1, gt2, gt3)  
  AmpSum2ChiToChacHpm = + 2._dp*AmpWaveChiToChacHpm + 2._dp*AmpVertexChiToChacHpm
  Call SquareAmp_FtoFS(MChi(gt1),MCha(gt2),MHpm(gt3),AmpSumChiToChacHpm(:,gt1, gt2, gt3),AmpSum2ChiToChacHpm(:,gt1, gt2, gt3),AmpSqChiToChacHpm(gt1, gt2, gt3)) 
  AmpSqChiToChacHpm(gt1, gt2, gt3) = AmpSqChiToChacHpm(gt1, gt2, gt3) + AmpSqTreeChiToChacHpm(gt1, gt2, gt3)  
End if  
Else  
  AmpSqChiToChacHpm(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqChiToChacHpm(gt1, gt2, gt3).le.0._dp) Then 
  gP1LChi(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LChi(gt1,i4) = 2._dp*GammaTPS(MChiOS(gt1),MChaOS(gt2),MHpmOS(gt3),helfactor*AmpSqChiToChacHpm(gt1, gt2, gt3))
Else 
  gP1LChi(gt1,i4) = 2._dp*GammaTPS(MChi(gt1),MCha(gt2),MHpm(gt3),helfactor*AmpSqChiToChacHpm(gt1, gt2, gt3))
End if 
If ((Abs(MRPChiToChacHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGChiToChacHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LChi(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPChiToChacHpm(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGChiToChacHpm(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPChiToChacHpm(gt1, gt2, gt3) + MRGChiToChacHpm(gt1, gt2, gt3)) 
  gP1LChi(gt1,i4) = gP1LChi(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPChiToChacHpm(gt1, gt2, gt3) + MRGChiToChacHpm(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LChi(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.5) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Cha Conjg(VWm)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_ChiToChacVWm(cplChiChacVWmL,cplChiChacVWmR,              & 
& MCha,MChi,MVWm,MCha2,MChi2,MVWm2,AmpTreeChiToChacVWm)

  Else 
Call Amplitude_Tree_NMSSMEFT_ChiToChacVWm(ZcplChiChacVWmL,ZcplChiChacVWmR,            & 
& MCha,MChi,MVWm,MCha2,MChi2,MVWm2,AmpTreeChiToChacVWm)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChacVWm(MLambda,em,gs,cplChiChacVWmL,cplChiChacVWmR,    & 
& MChaOS,MChiOS,MVWmOS,MRPChiToChacVWm,MRGChiToChacVWm)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChacVWm(MLambda,em,gs,ZcplChiChacVWmL,ZcplChiChacVWmR,  & 
& MChaOS,MChiOS,MVWmOS,MRPChiToChacVWm,MRGChiToChacVWm)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_ChiToChacVWm(MLambda,em,gs,cplChiChacVWmL,cplChiChacVWmR,    & 
& MCha,MChi,MVWm,MRPChiToChacVWm,MRGChiToChacVWm)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChacVWm(MLambda,em,gs,ZcplChiChacVWmL,ZcplChiChacVWmR,  & 
& MCha,MChi,MVWm,MRPChiToChacVWm,MRGChiToChacVWm)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_ChiToChacVWm(cplChiChacVWmL,cplChiChacVWmR,              & 
& ctcplChiChacVWmL,ctcplChiChacVWmR,MCha,MCha2,MChi,MChi2,MVWm,MVWm2,ZfL0,               & 
& ZfLm,ZfLp,ZfVWm,AmpWaveChiToChacVWm)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChacVWm(MAh,MCha,MChi,Mhh,MHpm,MVP,               & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexChiToChacVWm)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacVWm(MAh,MCha,MChi,Mhh,MHpm,MVP,            & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRdrChiToChacVWm)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacVWm(MAhOS,MChaOS,MChiOS,MhhOS,             & 
& MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& MVZ2OS,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhHpmcVWm,             & 
& GosZcplChiChacHpmL,GosZcplChiChacHpmR,ZcplChiChacVWmL,ZcplChiChacVWmR,cplcChaChahhL,   & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,    & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplhhHpmcVWm,cplhhcVWmVWm,GosZcplHpmcVWmVP,cplHpmcVWmVZ,cplcVWmVPVWm,   & 
& cplcVWmVWmVZ,AmpVertexIRosChiToChacVWm)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacVWm(MAh,MCha,MChi,Mhh,MHpm,MVP,            & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcVWm,GZcplChiChacHpmL,GZcplChiChacHpmR,              & 
& ZcplChiChacVWmL,ZcplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,             & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,      & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& cplhhHpmcVWm,cplhhcVWmVWm,GZcplHpmcVWmVP,cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,       & 
& AmpVertexIRosChiToChacVWm)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacVWm(MAhOS,MChaOS,MChiOS,MhhOS,             & 
& MHpmOS,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVP2,MVWm2OS,            & 
& MVZ2OS,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplAhHpmcVWm,             & 
& GcplChiChacHpmL,GcplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,           & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,    & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,   & 
& cplcChaChiVWmR,cplhhHpmcVWm,cplhhcVWmVWm,GcplHpmcVWmVP,cplHpmcVWmVZ,cplcVWmVPVWm,      & 
& cplcVWmVWmVZ,AmpVertexIRosChiToChacVWm)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChacVWm(MAh,MCha,MChi,Mhh,MHpm,MVP,            & 
& MVWm,MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVP2,MVWm2,MVZ2,cplcChaChaAhL,cplcChaChaAhR,      & 
& cplChiChiAhL,cplChiChiAhR,cplAhHpmcVWm,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,   & 
& cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,  & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,AmpVertexIRosChiToChacVWm)

 End if 
 End if 
AmpVertexChiToChacVWm = AmpVertexChiToChacVWm -  AmpVertexIRdrChiToChacVWm! +  AmpVertexIRosChiToChacVWm ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZChiToChacVWm=0._dp 
AmpVertexZChiToChacVWm=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChacVWm(1,gt2,:) = AmpWaveZChiToChacVWm(1,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChacVWm(1,gt1,:) 
AmpVertexZChiToChacVWm(1,gt2,:)= AmpVertexZChiToChacVWm(1,gt2,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChacVWm(1,gt1,:) 
AmpWaveZChiToChacVWm(2,gt2,:) = AmpWaveZChiToChacVWm(2,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChacVWm(2,gt1,:) 
AmpVertexZChiToChacVWm(2,gt2,:)= AmpVertexZChiToChacVWm(2,gt2,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChacVWm(2,gt1,:) 
AmpWaveZChiToChacVWm(3,gt2,:) = AmpWaveZChiToChacVWm(3,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChacVWm(3,gt1,:) 
AmpVertexZChiToChacVWm(3,gt2,:)= AmpVertexZChiToChacVWm(3,gt2,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChacVWm(3,gt1,:) 
AmpWaveZChiToChacVWm(4,gt2,:) = AmpWaveZChiToChacVWm(4,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChacVWm(4,gt1,:) 
AmpVertexZChiToChacVWm(4,gt2,:)= AmpVertexZChiToChacVWm(4,gt2,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChacVWm(4,gt1,:) 
 End Do 
End Do 
AmpWaveChiToChacVWm=AmpWaveZChiToChacVWm 
AmpVertexChiToChacVWm= AmpVertexZChiToChacVWm
! Final State 1 
AmpWaveZChiToChacVWm=0._dp 
AmpVertexZChiToChacVWm=0._dp 
Do gt1=1,2
  Do gt2=1,2
AmpWaveZChiToChacVWm(1,:,gt2) = AmpWaveZChiToChacVWm(1,:,gt2)+ZRUUM(gt2,gt1)*AmpWaveChiToChacVWm(1,:,gt1) 
AmpVertexZChiToChacVWm(1,:,gt2)= AmpVertexZChiToChacVWm(1,:,gt2)+ZRUUM(gt2,gt1)*AmpVertexChiToChacVWm(1,:,gt1) 
AmpWaveZChiToChacVWm(2,:,gt2) = AmpWaveZChiToChacVWm(2,:,gt2)+ZRUUPc(gt2,gt1)*AmpWaveChiToChacVWm(2,:,gt1) 
AmpVertexZChiToChacVWm(2,:,gt2)= AmpVertexZChiToChacVWm(2,:,gt2)+ZRUUPc(gt2,gt1)*AmpVertexChiToChacVWm(2,:,gt1) 
AmpWaveZChiToChacVWm(3,:,gt2) = AmpWaveZChiToChacVWm(3,:,gt2)+ZRUUM(gt2,gt1)*AmpWaveChiToChacVWm(3,:,gt1) 
AmpVertexZChiToChacVWm(3,:,gt2)= AmpVertexZChiToChacVWm(3,:,gt2)+ZRUUM(gt2,gt1)*AmpVertexChiToChacVWm(3,:,gt1) 
AmpWaveZChiToChacVWm(4,:,gt2) = AmpWaveZChiToChacVWm(4,:,gt2)+ZRUUPc(gt2,gt1)*AmpWaveChiToChacVWm(4,:,gt1) 
AmpVertexZChiToChacVWm(4,:,gt2)= AmpVertexZChiToChacVWm(4,:,gt2)+ZRUUPc(gt2,gt1)*AmpVertexChiToChacVWm(4,:,gt1) 
 End Do 
End Do 
AmpWaveChiToChacVWm=AmpWaveZChiToChacVWm 
AmpVertexChiToChacVWm= AmpVertexZChiToChacVWm
End if
If (ShiftIRdiv) Then 
AmpVertexChiToChacVWm = AmpVertexChiToChacVWm  +  AmpVertexIRosChiToChacVWm
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Chi->Cha conj[VWm] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumChiToChacVWm = AmpTreeChiToChacVWm 
 AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm + 2._dp*AmpWaveChiToChacVWm + 2._dp*AmpVertexChiToChacVWm  
Else 
 AmpSumChiToChacVWm = AmpTreeChiToChacVWm + AmpWaveChiToChacVWm + AmpVertexChiToChacVWm
 AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm + AmpWaveChiToChacVWm + AmpVertexChiToChacVWm 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumChiToChacVWm = AmpTreeChiToChacVWm
 AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm 
End if 
Do gt1=1,5
i4 = isave 
  Do gt2=1,2
If (((OSkinematics).and.(MChiOS(gt1).gt.(MChaOS(gt2)+MVWmOS))).or.((.not.OSkinematics).and.(MChi(gt1).gt.(MCha(gt2)+MVWm)))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChaOS(gt2),MVWmOS,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MCha(gt2),MVWm,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqChiToChacVWm(gt1, gt2) 
  AmpSum2ChiToChacVWm = 2._dp*AmpWaveChiToChacVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChaOS(gt2),MVWmOS,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MCha(gt2),MVWm,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqChiToChacVWm(gt1, gt2) 
  AmpSum2ChiToChacVWm = 2._dp*AmpVertexChiToChacVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChaOS(gt2),MVWmOS,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MCha(gt2),MVWm,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqChiToChacVWm(gt1, gt2) 
  AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm + 2._dp*AmpWaveChiToChacVWm + 2._dp*AmpVertexChiToChacVWm
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChaOS(gt2),MVWmOS,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MCha(gt2),MVWm,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqChiToChacVWm(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm
  Call SquareAmp_FtoFV(MChiOS(gt1),MChaOS(gt2),MVWmOS,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
  AmpSqTreeChiToChacVWm(gt1, gt2) = AmpSqChiToChacVWm(gt1, gt2)  
  AmpSum2ChiToChacVWm = + 2._dp*AmpWaveChiToChacVWm + 2._dp*AmpVertexChiToChacVWm
  Call SquareAmp_FtoFV(MChiOS(gt1),MChaOS(gt2),MVWmOS,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
  AmpSqChiToChacVWm(gt1, gt2) = AmpSqChiToChacVWm(gt1, gt2) + AmpSqTreeChiToChacVWm(gt1, gt2)  
Else  
  AmpSum2ChiToChacVWm = AmpTreeChiToChacVWm
  Call SquareAmp_FtoFV(MChi(gt1),MCha(gt2),MVWm,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
  AmpSqTreeChiToChacVWm(gt1, gt2) = AmpSqChiToChacVWm(gt1, gt2)  
  AmpSum2ChiToChacVWm = + 2._dp*AmpWaveChiToChacVWm + 2._dp*AmpVertexChiToChacVWm
  Call SquareAmp_FtoFV(MChi(gt1),MCha(gt2),MVWm,AmpSumChiToChacVWm(:,gt1, gt2),AmpSum2ChiToChacVWm(:,gt1, gt2),AmpSqChiToChacVWm(gt1, gt2)) 
  AmpSqChiToChacVWm(gt1, gt2) = AmpSqChiToChacVWm(gt1, gt2) + AmpSqTreeChiToChacVWm(gt1, gt2)  
End if  
Else  
  AmpSqChiToChacVWm(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqChiToChacVWm(gt1, gt2).le.0._dp) Then 
  gP1LChi(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LChi(gt1,i4) = 2._dp*GammaTPS(MChiOS(gt1),MChaOS(gt2),MVWmOS,helfactor*AmpSqChiToChacVWm(gt1, gt2))
Else 
  gP1LChi(gt1,i4) = 2._dp*GammaTPS(MChi(gt1),MCha(gt2),MVWm,helfactor*AmpSqChiToChacVWm(gt1, gt2))
End if 
If ((Abs(MRPChiToChacVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGChiToChacVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LChi(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPChiToChacVWm(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGChiToChacVWm(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPChiToChacVWm(gt1, gt2) + MRGChiToChacVWm(gt1, gt2)) 
  gP1LChi(gt1,i4) = gP1LChi(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPChiToChacVWm(gt1, gt2) + MRGChiToChacVWm(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LChi(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.5) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Chi hh
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_ChiToChihh(cplChiChihhL,cplChiChihhR,MChi,               & 
& Mhh,MChi2,Mhh2,AmpTreeChiToChihh)

  Else 
Call Amplitude_Tree_NMSSMEFT_ChiToChihh(ZcplChiChihhL,ZcplChiChihhR,MChi,             & 
& Mhh,MChi2,Mhh2,AmpTreeChiToChihh)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChihh(MLambda,em,gs,cplChiChihhL,cplChiChihhR,          & 
& MChiOS,MhhOS,MRPChiToChihh,MRGChiToChihh)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChihh(MLambda,em,gs,ZcplChiChihhL,ZcplChiChihhR,        & 
& MChiOS,MhhOS,MRPChiToChihh,MRGChiToChihh)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_ChiToChihh(MLambda,em,gs,cplChiChihhL,cplChiChihhR,          & 
& MChi,Mhh,MRPChiToChihh,MRGChiToChihh)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChihh(MLambda,em,gs,ZcplChiChihhL,ZcplChiChihhR,        & 
& MChi,Mhh,MRPChiToChihh,MRGChiToChihh)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_ChiToChihh(cplChiChihhL,cplChiChihhR,ctcplChiChihhL,     & 
& ctcplChiChihhR,MChi,MChi2,Mhh,Mhh2,Zfhh,ZfL0,AmpWaveChiToChihh)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChihh(MAh,MCha,MChi,Mhh,MHpm,MVWm,MVZ,            & 
& MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,            & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexChiToChihh)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChihh(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,        & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRdrChiToChihh)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChihh(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplAhAhhh,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR, & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,ZcplChiChihhL,               & 
& ZcplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,  & 
& cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,          & 
& cplhhVZVZ,AmpVertexIRosChiToChihh)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChihh(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,        & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,ZcplChiChihhL,ZcplChiChihhR,cplChiChiVZL,cplChiChiVZR,     & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosChiToChihh)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChihh(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplAhAhhh,cplChiChiAhL,cplChiChiAhR,cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR, & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,   & 
& cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR, & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,               & 
& AmpVertexIRosChiToChihh)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChihh(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplAhAhhh,cplChiChiAhL,cplChiChiAhR,        & 
& cplAhhhhh,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,       & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhhhhh,cplhhHpmcHpm,    & 
& cplhhHpmcVWm,cplhhcHpmVWm,cplhhcVWmVWm,cplhhVZVZ,AmpVertexIRosChiToChihh)

 End if 
 End if 
AmpVertexChiToChihh = AmpVertexChiToChihh -  AmpVertexIRdrChiToChihh! +  AmpVertexIRosChiToChihh ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZChiToChihh=0._dp 
AmpVertexZChiToChihh=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChihh(1,gt2,:,:) = AmpWaveZChiToChihh(1,gt2,:,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChihh(1,gt1,:,:) 
AmpVertexZChiToChihh(1,gt2,:,:)= AmpVertexZChiToChihh(1,gt2,:,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChihh(1,gt1,:,:) 
AmpWaveZChiToChihh(2,gt2,:,:) = AmpWaveZChiToChihh(2,gt2,:,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChihh(2,gt1,:,:) 
AmpVertexZChiToChihh(2,gt2,:,:)= AmpVertexZChiToChihh(2,gt2,:,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChihh(2,gt1,:,:) 
 End Do 
End Do 
AmpWaveChiToChihh=AmpWaveZChiToChihh 
AmpVertexChiToChihh= AmpVertexZChiToChihh
! Final State 1 
AmpWaveZChiToChihh=0._dp 
AmpVertexZChiToChihh=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChihh(1,:,gt2,:) = AmpWaveZChiToChihh(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChihh(1,:,gt1,:) 
AmpVertexZChiToChihh(1,:,gt2,:)= AmpVertexZChiToChihh(1,:,gt2,:)+ZRUZN(gt2,gt1)*AmpVertexChiToChihh(1,:,gt1,:) 
AmpWaveZChiToChihh(2,:,gt2,:) = AmpWaveZChiToChihh(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChihh(2,:,gt1,:) 
AmpVertexZChiToChihh(2,:,gt2,:)= AmpVertexZChiToChihh(2,:,gt2,:)+ZRUZNc(gt2,gt1)*AmpVertexChiToChihh(2,:,gt1,:) 
 End Do 
End Do 
AmpWaveChiToChihh=AmpWaveZChiToChihh 
AmpVertexChiToChihh= AmpVertexZChiToChihh
! Final State 2 
AmpWaveZChiToChihh=0._dp 
AmpVertexZChiToChihh=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZChiToChihh(:,:,:,gt2) = AmpWaveZChiToChihh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpWaveChiToChihh(:,:,:,gt1) 
AmpVertexZChiToChihh(:,:,:,gt2)= AmpVertexZChiToChihh(:,:,:,gt2)+ZRUZH(gt2,gt1)*AmpVertexChiToChihh(:,:,:,gt1) 
 End Do 
End Do 
AmpWaveChiToChihh=AmpWaveZChiToChihh 
AmpVertexChiToChihh= AmpVertexZChiToChihh
End if
If (ShiftIRdiv) Then 
AmpVertexChiToChihh = AmpVertexChiToChihh  +  AmpVertexIRosChiToChihh
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Chi->Chi hh -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumChiToChihh = AmpTreeChiToChihh 
 AmpSum2ChiToChihh = AmpTreeChiToChihh + 2._dp*AmpWaveChiToChihh + 2._dp*AmpVertexChiToChihh  
Else 
 AmpSumChiToChihh = AmpTreeChiToChihh + AmpWaveChiToChihh + AmpVertexChiToChihh
 AmpSum2ChiToChihh = AmpTreeChiToChihh + AmpWaveChiToChihh + AmpVertexChiToChihh 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumChiToChihh = AmpTreeChiToChihh
 AmpSum2ChiToChihh = AmpTreeChiToChihh 
End if 
Do gt1=1,5
i4 = isave 
  Do gt2=1,5
    Do gt3=1,3
If (((OSkinematics).and.(MChiOS(gt1).gt.(MChiOS(gt2)+MhhOS(gt3)))).or.((.not.OSkinematics).and.(MChi(gt1).gt.(MChi(gt2)+Mhh(gt3))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2, gt3 
  AmpSum2ChiToChihh = AmpTreeChiToChihh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),Mhh(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqChiToChihh(gt1, gt2, gt3) 
  AmpSum2ChiToChihh = 2._dp*AmpWaveChiToChihh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),Mhh(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqChiToChihh(gt1, gt2, gt3) 
  AmpSum2ChiToChihh = 2._dp*AmpVertexChiToChihh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),Mhh(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqChiToChihh(gt1, gt2, gt3) 
  AmpSum2ChiToChihh = AmpTreeChiToChihh + 2._dp*AmpWaveChiToChihh + 2._dp*AmpVertexChiToChihh
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),Mhh(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqChiToChihh(gt1, gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2ChiToChihh = AmpTreeChiToChihh
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
  AmpSqTreeChiToChihh(gt1, gt2, gt3) = AmpSqChiToChihh(gt1, gt2, gt3)  
  AmpSum2ChiToChihh = + 2._dp*AmpWaveChiToChihh + 2._dp*AmpVertexChiToChihh
  Call SquareAmp_FtoFS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
  AmpSqChiToChihh(gt1, gt2, gt3) = AmpSqChiToChihh(gt1, gt2, gt3) + AmpSqTreeChiToChihh(gt1, gt2, gt3)  
Else  
  AmpSum2ChiToChihh = AmpTreeChiToChihh
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),Mhh(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
  AmpSqTreeChiToChihh(gt1, gt2, gt3) = AmpSqChiToChihh(gt1, gt2, gt3)  
  AmpSum2ChiToChihh = + 2._dp*AmpWaveChiToChihh + 2._dp*AmpVertexChiToChihh
  Call SquareAmp_FtoFS(MChi(gt1),MChi(gt2),Mhh(gt3),AmpSumChiToChihh(:,gt1, gt2, gt3),AmpSum2ChiToChihh(:,gt1, gt2, gt3),AmpSqChiToChihh(gt1, gt2, gt3)) 
  AmpSqChiToChihh(gt1, gt2, gt3) = AmpSqChiToChihh(gt1, gt2, gt3) + AmpSqTreeChiToChihh(gt1, gt2, gt3)  
End if  
Else  
  AmpSqChiToChihh(gt1, gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqChiToChihh(gt1, gt2, gt3).le.0._dp) Then 
  gP1LChi(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChiOS(gt1),MChiOS(gt2),MhhOS(gt3),helfactor*AmpSqChiToChihh(gt1, gt2, gt3))
Else 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChi(gt1),MChi(gt2),Mhh(gt3),helfactor*AmpSqChiToChihh(gt1, gt2, gt3))
End if 
If ((Abs(MRPChiToChihh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGChiToChihh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LChi(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPChiToChihh(gt1, gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGChiToChihh(gt1, gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPChiToChihh(gt1, gt2, gt3) + MRGChiToChihh(gt1, gt2, gt3)) 
  gP1LChi(gt1,i4) = gP1LChi(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPChiToChihh(gt1, gt2, gt3) + MRGChiToChihh(gt1, gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LChi(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
If (gt1.eq.5) isave = i4 
End do
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Chi VZ
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSMEFT_ChiToChiVZ(cplChiChiVZL,cplChiChiVZR,MChi,               & 
& MVZ,MChi2,MVZ2,AmpTreeChiToChiVZ)

  Else 
Call Amplitude_Tree_NMSSMEFT_ChiToChiVZ(ZcplChiChiVZL,ZcplChiChiVZR,MChi,             & 
& MVZ,MChi2,MVZ2,AmpTreeChiToChiVZ)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChiVZ(MLambda,em,gs,cplChiChiVZL,cplChiChiVZR,          & 
& MChiOS,MVZOS,MRPChiToChiVZ,MRGChiToChiVZ)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChiVZ(MLambda,em,gs,ZcplChiChiVZL,ZcplChiChiVZR,        & 
& MChiOS,MVZOS,MRPChiToChiVZ,MRGChiToChiVZ)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSMEFT_ChiToChiVZ(MLambda,em,gs,cplChiChiVZL,cplChiChiVZR,          & 
& MChi,MVZ,MRPChiToChiVZ,MRGChiToChiVZ)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSMEFT_ChiToChiVZ(MLambda,em,gs,ZcplChiChiVZL,ZcplChiChiVZR,        & 
& MChi,MVZ,MRPChiToChiVZ,MRGChiToChiVZ)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_ChiToChiVZ(cplChiChiVZL,cplChiChiVZR,ctcplChiChiVZL,     & 
& ctcplChiChiVZR,MChi,MChi2,MVZ,MVZ2,ZfL0,ZfVZ,AmpWaveChiToChiVZ)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChiVZ(MAh,MCha,MChi,Mhh,MHpm,MVWm,MVZ,            & 
& MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplAhhhVZ,            & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVZL,             & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,      & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexChiToChiVZ)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiVZ(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplAhhhVZ,        & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVZL,             & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,      & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRdrChiToChiVZ)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiVZ(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplChiChiAhL,cplChiChiAhR,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,      & 
& cplChiChacVWmR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,ZcplChiChiVZL,    & 
& ZcplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosChiToChiVZ)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiVZ(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplAhhhVZ,        & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVZL,             & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,ZcplChiChiVZL,ZcplChiChiVZR,cplcChaChiHpmL,    & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,      & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosChiToChiVZ)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiVZ(MAhOS,MChaOS,MChiOS,MhhOS,               & 
& MHpmOS,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,Mhh2OS,MHpm2OS,MVWm2OS,MVZ2OS,              & 
& cplChiChiAhL,cplChiChiAhR,cplAhhhVZ,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,      & 
& cplChiChacVWmR,cplcChaChaVZL,cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,     & 
& cplChiChiVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,              & 
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosChiToChiVZ)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSMEFT_ChiToChiVZ(MAh,MCha,MChi,Mhh,MHpm,MVWm,             & 
& MVZ,MAh2,MCha2,MChi2,Mhh2,MHpm2,MVWm2,MVZ2,cplChiChiAhL,cplChiChiAhR,cplAhhhVZ,        & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVZL,             & 
& cplcChaChaVZR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplcChaChiHpmL,      & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,      & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,AmpVertexIRosChiToChiVZ)

 End if 
 End if 
AmpVertexChiToChiVZ = AmpVertexChiToChiVZ -  AmpVertexIRdrChiToChiVZ! +  AmpVertexIRosChiToChiVZ ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Decaying particle 
AmpWaveZChiToChiVZ=0._dp 
AmpVertexZChiToChiVZ=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChiVZ(1,gt2,:) = AmpWaveZChiToChiVZ(1,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChiVZ(1,gt1,:) 
AmpVertexZChiToChiVZ(1,gt2,:)= AmpVertexZChiToChiVZ(1,gt2,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChiVZ(1,gt1,:) 
AmpWaveZChiToChiVZ(2,gt2,:) = AmpWaveZChiToChiVZ(2,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChiVZ(2,gt1,:) 
AmpVertexZChiToChiVZ(2,gt2,:)= AmpVertexZChiToChiVZ(2,gt2,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChiVZ(2,gt1,:) 
AmpWaveZChiToChiVZ(3,gt2,:) = AmpWaveZChiToChiVZ(3,gt2,:)+ZRUZNc(gt2,gt1)*AmpWaveChiToChiVZ(3,gt1,:) 
AmpVertexZChiToChiVZ(3,gt2,:)= AmpVertexZChiToChiVZ(3,gt2,:) + ZRUZNc(gt2,gt1)*AmpVertexChiToChiVZ(3,gt1,:) 
AmpWaveZChiToChiVZ(4,gt2,:) = AmpWaveZChiToChiVZ(4,gt2,:)+ZRUZN(gt2,gt1)*AmpWaveChiToChiVZ(4,gt1,:) 
AmpVertexZChiToChiVZ(4,gt2,:)= AmpVertexZChiToChiVZ(4,gt2,:) + ZRUZN(gt2,gt1)*AmpVertexChiToChiVZ(4,gt1,:) 
 End Do 
End Do 
AmpWaveChiToChiVZ=AmpWaveZChiToChiVZ 
AmpVertexChiToChiVZ= AmpVertexZChiToChiVZ
! Final State 1 
AmpWaveZChiToChiVZ=0._dp 
AmpVertexZChiToChiVZ=0._dp 
Do gt1=1,5
  Do gt2=1,5
AmpWaveZChiToChiVZ(1,:,gt2) = AmpWaveZChiToChiVZ(1,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveChiToChiVZ(1,:,gt1) 
AmpVertexZChiToChiVZ(1,:,gt2)= AmpVertexZChiToChiVZ(1,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexChiToChiVZ(1,:,gt1) 
AmpWaveZChiToChiVZ(2,:,gt2) = AmpWaveZChiToChiVZ(2,:,gt2)+ZRUZNc(gt2,gt1)*AmpWaveChiToChiVZ(2,:,gt1) 
AmpVertexZChiToChiVZ(2,:,gt2)= AmpVertexZChiToChiVZ(2,:,gt2)+ZRUZNc(gt2,gt1)*AmpVertexChiToChiVZ(2,:,gt1) 
AmpWaveZChiToChiVZ(3,:,gt2) = AmpWaveZChiToChiVZ(3,:,gt2)+ZRUZN(gt2,gt1)*AmpWaveChiToChiVZ(3,:,gt1) 
AmpVertexZChiToChiVZ(3,:,gt2)= AmpVertexZChiToChiVZ(3,:,gt2)+ZRUZN(gt2,gt1)*AmpVertexChiToChiVZ(3,:,gt1) 
AmpWaveZChiToChiVZ(4,:,gt2) = AmpWaveZChiToChiVZ(4,:,gt2)+ZRUZNc(gt2,gt1)*AmpWaveChiToChiVZ(4,:,gt1) 
AmpVertexZChiToChiVZ(4,:,gt2)= AmpVertexZChiToChiVZ(4,:,gt2)+ZRUZNc(gt2,gt1)*AmpVertexChiToChiVZ(4,:,gt1) 
 End Do 
End Do 
AmpWaveChiToChiVZ=AmpWaveZChiToChiVZ 
AmpVertexChiToChiVZ= AmpVertexZChiToChiVZ
End if
If (ShiftIRdiv) Then 
AmpVertexChiToChiVZ = AmpVertexChiToChiVZ  +  AmpVertexIRosChiToChiVZ
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Chi->Chi VZ -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumChiToChiVZ = AmpTreeChiToChiVZ 
 AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ + 2._dp*AmpWaveChiToChiVZ + 2._dp*AmpVertexChiToChiVZ  
Else 
 AmpSumChiToChiVZ = AmpTreeChiToChiVZ + AmpWaveChiToChiVZ + AmpVertexChiToChiVZ
 AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ + AmpWaveChiToChiVZ + AmpVertexChiToChiVZ 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumChiToChiVZ = AmpTreeChiToChiVZ
 AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ 
End if 
Do gt1=1,5
i4 = isave 
  Do gt2=1,5
If (((OSkinematics).and.(MChiOS(gt1).gt.(MChiOS(gt2)+MVZOS))).or.((.not.OSkinematics).and.(MChi(gt1).gt.(MChi(gt2)+MVZ)))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt1, gt2 
  AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),MVZOS,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVZ,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqChiToChiVZ(gt1, gt2) 
  AmpSum2ChiToChiVZ = 2._dp*AmpWaveChiToChiVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),MVZOS,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVZ,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqChiToChiVZ(gt1, gt2) 
  AmpSum2ChiToChiVZ = 2._dp*AmpVertexChiToChiVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),MVZOS,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVZ,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqChiToChiVZ(gt1, gt2) 
  AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ + 2._dp*AmpWaveChiToChiVZ + 2._dp*AmpVertexChiToChiVZ
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),MVZOS,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVZ,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqChiToChiVZ(gt1, gt2) 
 End if 
If (OSkinematics) Then 
  AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),MVZOS,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
  AmpSqTreeChiToChiVZ(gt1, gt2) = AmpSqChiToChiVZ(gt1, gt2)  
  AmpSum2ChiToChiVZ = + 2._dp*AmpWaveChiToChiVZ + 2._dp*AmpVertexChiToChiVZ
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),MVZOS,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
  AmpSqChiToChiVZ(gt1, gt2) = AmpSqChiToChiVZ(gt1, gt2) + AmpSqTreeChiToChiVZ(gt1, gt2)  
Else  
  AmpSum2ChiToChiVZ = AmpTreeChiToChiVZ
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVZ,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
  AmpSqTreeChiToChiVZ(gt1, gt2) = AmpSqChiToChiVZ(gt1, gt2)  
  AmpSum2ChiToChiVZ = + 2._dp*AmpWaveChiToChiVZ + 2._dp*AmpVertexChiToChiVZ
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVZ,AmpSumChiToChiVZ(:,gt1, gt2),AmpSum2ChiToChiVZ(:,gt1, gt2),AmpSqChiToChiVZ(gt1, gt2)) 
  AmpSqChiToChiVZ(gt1, gt2) = AmpSqChiToChiVZ(gt1, gt2) + AmpSqTreeChiToChiVZ(gt1, gt2)  
End if  
Else  
  AmpSqChiToChiVZ(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqChiToChiVZ(gt1, gt2).le.0._dp) Then 
  gP1LChi(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChiOS(gt1),MChiOS(gt2),MVZOS,helfactor*AmpSqChiToChiVZ(gt1, gt2))
Else 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChi(gt1),MChi(gt2),MVZ,helfactor*AmpSqChiToChiVZ(gt1, gt2))
End if 
If ((Abs(MRPChiToChiVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGChiToChiVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LChi(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPChiToChiVZ(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGChiToChiVZ(gt1, gt2)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*0.5_dp*helfactor*(MRPChiToChiVZ(gt1, gt2) + MRGChiToChiVZ(gt1, gt2)) 
  gP1LChi(gt1,i4) = gP1LChi(gt1,i4) + phasespacefactor*0.5_dp*helfactor*(MRPChiToChiVZ(gt1, gt2) + MRGChiToChiVZ(gt1, gt2))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LChi(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

  End do
If (gt1.eq.5) isave = i4 
End do
End If 
!---------------- 
! Chi VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSMEFT_ChiToChiVP(ZcplChiChiVZL,ZcplChiChiVZR,ctcplChiChiVZL,   & 
& ctcplChiChiVZR,MChiOS,MChi2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfL0,ZfVP,ZfVZVP,AmpWaveChiToChiVP)

 Else 
Call Amplitude_WAVE_NMSSMEFT_ChiToChiVP(cplChiChiVZL,cplChiChiVZR,ctcplChiChiVZL,     & 
& ctcplChiChiVZR,MChiOS,MChi2OS,MVP,MVP2,MVZOS,MVZ2OS,ZfL0,ZfVP,ZfVZVP,AmpWaveChiToChiVP)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChiVP(MChaOS,MChiOS,MHpmOS,MVP,MVWmOS,            & 
& MCha2OS,MChi2OS,MHpm2OS,MVP2,MVWm2OS,ZcplChiChacHpmL,ZcplChiChacHpmR,ZcplChiChacVWmL,  & 
& ZcplChiChacVWmR,ZcplcChaChaVPL,ZcplcChaChaVPR,ZcplcChaChiHpmL,ZcplcChaChiHpmR,         & 
& ZcplcChaChiVWmL,ZcplcChaChiVWmR,ZcplHpmcHpmVP,ZcplHpmcVWmVP,ZcplcHpmVPVWm,             & 
& ZcplcVWmVPVWm,AmpVertexChiToChiVP)

 Else 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChiVP(MChaOS,MChiOS,MHpmOS,MVP,MVWmOS,            & 
& MCha2OS,MChi2OS,MHpm2OS,MVP2,MVWm2OS,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,     & 
& cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChiHpmL,cplcChaChiHpmR,              & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,     & 
& AmpVertexChiToChiVP)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSMEFT_ChiToChiVP(cplChiChiVZL,cplChiChiVZR,ctcplChiChiVZL,     & 
& ctcplChiChiVZR,MChi,MChi2,MVP,MVP2,MVZ,MVZ2,ZfL0,ZfVP,ZfVZVP,AmpWaveChiToChiVP)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSMEFT_ChiToChiVP(MCha,MChi,MHpm,MVP,MVWm,MCha2,              & 
& MChi2,MHpm2,MVP2,MVWm2,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,    & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,              & 
& cplcChaChiVWmR,cplHpmcHpmVP,cplHpmcVWmVP,cplcHpmVPVWm,cplcVWmVPVWm,AmpVertexChiToChiVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Chi->Chi VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumChiToChiVP = 0._dp 
 AmpSum2ChiToChiVP = 0._dp  
Else 
 AmpSumChiToChiVP = AmpVertexChiToChiVP + AmpWaveChiToChiVP
 AmpSum2ChiToChiVP = AmpVertexChiToChiVP + AmpWaveChiToChiVP 
End If 
Do gt1=1,5
i4 = isave 
  Do gt2=1,5
If (((OSkinematics).and.(MChiOS(gt1).gt.(MChiOS(gt2)+0.))).or.((.not.OSkinematics).and.(MChi(gt1).gt.(MChi(gt2)+MVP)))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MChiOS(gt1),MChiOS(gt2),0._dp,AmpSumChiToChiVP(:,gt1, gt2),AmpSum2ChiToChiVP(:,gt1, gt2),AmpSqChiToChiVP(gt1, gt2)) 
Else  
  Call SquareAmp_FtoFV(MChi(gt1),MChi(gt2),MVP,AmpSumChiToChiVP(:,gt1, gt2),AmpSum2ChiToChiVP(:,gt1, gt2),AmpSqChiToChiVP(gt1, gt2)) 
End if  
Else  
  AmpSqChiToChiVP(gt1, gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqChiToChiVP(gt1, gt2).le.0._dp) Then 
  gP1LChi(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChiOS(gt1),MChiOS(gt2),0._dp,helfactor*AmpSqChiToChiVP(gt1, gt2))
Else 
  gP1LChi(gt1,i4) = 1._dp*GammaTPS(MChi(gt1),MChi(gt2),MVP,helfactor*AmpSqChiToChiVP(gt1, gt2))
End if 
If ((Abs(MRPChiToChiVP(gt1, gt2)).gt.1.0E-20_dp).or.(Abs(MRGChiToChiVP(gt1, gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LChi(gt1,i4) 
End if 
i4=i4+1

  End do
If (gt1.eq.5) isave = i4 
End do
End Subroutine OneLoopDecay_Chi

End Module Wrapper_OneLoopDecay_Chi_NMSSMEFT
