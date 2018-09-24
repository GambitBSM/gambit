! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:27 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module Wrapper_OneLoopDecay_Glu_NMSSM
Use Model_Data_NMSSM 
Use Kinematics 
Use OneLoopDecay_Glu_NMSSM 
Use Control 
Use Settings 

 
Contains

 
Subroutine OneLoopDecay_Glu(MSdOS,MSd2OS,MSvOS,MSv2OS,MSuOS,MSu2OS,MSeOS,             & 
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
& ZfVPVZ,ZfVZVP,cplAhSdcSd,cplAhSucSu,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChiSdL,          & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,               & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplChaFucSdL,            & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplhhSdcSd,           & 
& cplhhSucSu,cplHpmSucSd,cplSdcHpmcSu,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,     & 
& cplSucSdVWm,cplSucSuVG,cplSucSuVP,cplSucSuVZ,cplVGVGVG,ctcplGluFdcSdL,ctcplGluFdcSdR,  & 
& ctcplGluFucSuL,ctcplGluFucSuR,ctcplGluGluVGL,ctcplGluGluVGR,ZcplAhSdcSd,               & 
& ZcplAhSucSu,ZcplcFdChiSdL,ZcplcFdChiSdR,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFdFdhhL,        & 
& ZcplcFdFdhhR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplcFdFdVPL,ZcplcFdFdVPR,ZcplcFdFdVZL,         & 
& ZcplcFdFdVZR,ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuChiSuL,ZcplcFuChiSuR,ZcplcFuFuAhL,     & 
& ZcplcFuFuAhR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFuFuVPL,         & 
& ZcplcFuFuVPR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplChiFdcSdL,      & 
& ZcplChiFdcSdR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplGluFucSuL,   & 
& ZcplGluFucSuR,ZcplGluGluVGL,ZcplGluGluVGR,ZcplhhSdcSd,ZcplhhSucSu,ZcplSdcSdVG,         & 
& ZcplSdcSdVP,ZcplSdcSdVZ,ZcplSucSuVG,ZcplSucSuVP,ZcplSucSuVZ,ZcplVGVGVG,ZRUZD,          & 
& ZRUZV,ZRUZU,ZRUZE,ZRUZH,ZRUZA,ZRUZP,ZRUZN,ZRUUM,ZRUUP,ZRUZEL,ZRUZER,ZRUZDL,            & 
& ZRUZDR,ZRUZUL,ZRUZUR,MLambda,em,gs,deltaM,kont,gP1LGlu)

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

Complex(dp),Intent(in) :: cplAhSdcSd(3,6,6),cplAhSucSu(3,6,6),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),        & 
& cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),         & 
& cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),               & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),& 
& cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),             & 
& cplcFdGluSdR(3,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplcFuFdcHpmL(3,3,2),        & 
& cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,3),         & 
& cplcFuFuAhR(3,3,3),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),           & 
& cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6),               & 
& cplGluGluVGL,cplGluGluVGR,cplhhSdcSd(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),      & 
& cplSdcHpmcSu(6,2,6),cplSdcSdVG(6,6),cplSdcSdVP(6,6),cplSdcSdVZ(6,6),cplSdcSucVWm(6,6), & 
& cplSucSdVWm(6,6),cplSucSuVG(6,6),cplSucSuVP(6,6),cplSucSuVZ(6,6),cplVGVGVG,            & 
& ctcplGluFdcSdL(3,6),ctcplGluFdcSdR(3,6),ctcplGluFucSuL(3,6),ctcplGluFucSuR(3,6),       & 
& ctcplGluGluVGL,ctcplGluGluVGR,ZcplAhSdcSd(3,6,6),ZcplAhSucSu(3,6,6),ZcplcFdChiSdL(3,5,6),& 
& ZcplcFdChiSdR(3,5,6),ZcplcFdFdAhL(3,3,3),ZcplcFdFdAhR(3,3,3),ZcplcFdFdhhL(3,3,3),      & 
& ZcplcFdFdhhR(3,3,3),ZcplcFdFdVGL(3,3),ZcplcFdFdVGR(3,3),ZcplcFdFdVPL(3,3),             & 
& ZcplcFdFdVPR(3,3),ZcplcFdFdVZL(3,3),ZcplcFdFdVZR(3,3),ZcplcFdGluSdL(3,6),              & 
& ZcplcFdGluSdR(3,6),ZcplcFuChiSuL(3,5,6),ZcplcFuChiSuR(3,5,6),ZcplcFuFuAhL(3,3,3),      & 
& ZcplcFuFuAhR(3,3,3),ZcplcFuFuhhL(3,3,3),ZcplcFuFuhhR(3,3,3),ZcplcFuFuVGL(3,3),         & 
& ZcplcFuFuVGR(3,3),ZcplcFuFuVPL(3,3),ZcplcFuFuVPR(3,3),ZcplcFuFuVZL(3,3),               & 
& ZcplcFuFuVZR(3,3),ZcplcFuGluSuL(3,6),ZcplcFuGluSuR(3,6),ZcplChiFdcSdL(5,3,6),          & 
& ZcplChiFdcSdR(5,3,6),ZcplChiFucSuL(5,3,6),ZcplChiFucSuR(5,3,6),ZcplGluFdcSdL(3,6),     & 
& ZcplGluFdcSdR(3,6),ZcplGluFucSuL(3,6),ZcplGluFucSuR(3,6),ZcplGluGluVGL,ZcplGluGluVGR,  & 
& ZcplhhSdcSd(3,6,6),ZcplhhSucSu(3,6,6),ZcplSdcSdVG(6,6),ZcplSdcSdVP(6,6),               & 
& ZcplSdcSdVZ(6,6),ZcplSucSuVG(6,6),ZcplSucSuVP(6,6),ZcplSucSuVZ(6,6),ZcplVGVGVG

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
Real(dp), Intent(out) :: gP1LGlu(1,49) 
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
Real(dp) :: MRPGluToFdcSd(3,6),MRGGluToFdcSd(3,6), MRPZGluToFdcSd(3,6),MRGZGluToFdcSd(3,6) 
Real(dp) :: MVPGluToFdcSd(3,6) 
Real(dp) :: RMsqTreeGluToFdcSd(3,6),RMsqWaveGluToFdcSd(3,6),RMsqVertexGluToFdcSd(3,6) 
Complex(dp) :: AmpTreeGluToFdcSd(2,3,6),AmpWaveGluToFdcSd(2,3,6)=(0._dp,0._dp),AmpVertexGluToFdcSd(2,3,6)& 
 & ,AmpVertexIRosGluToFdcSd(2,3,6),AmpVertexIRdrGluToFdcSd(2,3,6), AmpSumGluToFdcSd(2,3,6), AmpSum2GluToFdcSd(2,3,6) 
Complex(dp) :: AmpTreeZGluToFdcSd(2,3,6),AmpWaveZGluToFdcSd(2,3,6),AmpVertexZGluToFdcSd(2,3,6) 
Real(dp) :: AmpSqGluToFdcSd(3,6),  AmpSqTreeGluToFdcSd(3,6) 
Real(dp) :: MRPGluToFucSu(3,6),MRGGluToFucSu(3,6), MRPZGluToFucSu(3,6),MRGZGluToFucSu(3,6) 
Real(dp) :: MVPGluToFucSu(3,6) 
Real(dp) :: RMsqTreeGluToFucSu(3,6),RMsqWaveGluToFucSu(3,6),RMsqVertexGluToFucSu(3,6) 
Complex(dp) :: AmpTreeGluToFucSu(2,3,6),AmpWaveGluToFucSu(2,3,6)=(0._dp,0._dp),AmpVertexGluToFucSu(2,3,6)& 
 & ,AmpVertexIRosGluToFucSu(2,3,6),AmpVertexIRdrGluToFucSu(2,3,6), AmpSumGluToFucSu(2,3,6), AmpSum2GluToFucSu(2,3,6) 
Complex(dp) :: AmpTreeZGluToFucSu(2,3,6),AmpWaveZGluToFucSu(2,3,6),AmpVertexZGluToFucSu(2,3,6) 
Real(dp) :: AmpSqGluToFucSu(3,6),  AmpSqTreeGluToFucSu(3,6) 
Real(dp) :: MRPGluToChiVG(5),MRGGluToChiVG(5), MRPZGluToChiVG(5),MRGZGluToChiVG(5) 
Real(dp) :: MVPGluToChiVG(5) 
Real(dp) :: RMsqTreeGluToChiVG(5),RMsqWaveGluToChiVG(5),RMsqVertexGluToChiVG(5) 
Complex(dp) :: AmpTreeGluToChiVG(4,5),AmpWaveGluToChiVG(4,5)=(0._dp,0._dp),AmpVertexGluToChiVG(4,5)& 
 & ,AmpVertexIRosGluToChiVG(4,5),AmpVertexIRdrGluToChiVG(4,5), AmpSumGluToChiVG(4,5), AmpSum2GluToChiVG(4,5) 
Complex(dp) :: AmpTreeZGluToChiVG(4,5),AmpWaveZGluToChiVG(4,5),AmpVertexZGluToChiVG(4,5) 
Real(dp) :: AmpSqGluToChiVG(5),  AmpSqTreeGluToChiVG(5) 
Real(dp) :: MRPGluToGluAh(3),MRGGluToGluAh(3), MRPZGluToGluAh(3),MRGZGluToGluAh(3) 
Real(dp) :: MVPGluToGluAh(3) 
Real(dp) :: RMsqTreeGluToGluAh(3),RMsqWaveGluToGluAh(3),RMsqVertexGluToGluAh(3) 
Complex(dp) :: AmpTreeGluToGluAh(2,3),AmpWaveGluToGluAh(2,3)=(0._dp,0._dp),AmpVertexGluToGluAh(2,3)& 
 & ,AmpVertexIRosGluToGluAh(2,3),AmpVertexIRdrGluToGluAh(2,3), AmpSumGluToGluAh(2,3), AmpSum2GluToGluAh(2,3) 
Complex(dp) :: AmpTreeZGluToGluAh(2,3),AmpWaveZGluToGluAh(2,3),AmpVertexZGluToGluAh(2,3) 
Real(dp) :: AmpSqGluToGluAh(3),  AmpSqTreeGluToGluAh(3) 
Real(dp) :: MRPGluToGluhh(3),MRGGluToGluhh(3), MRPZGluToGluhh(3),MRGZGluToGluhh(3) 
Real(dp) :: MVPGluToGluhh(3) 
Real(dp) :: RMsqTreeGluToGluhh(3),RMsqWaveGluToGluhh(3),RMsqVertexGluToGluhh(3) 
Complex(dp) :: AmpTreeGluToGluhh(2,3),AmpWaveGluToGluhh(2,3)=(0._dp,0._dp),AmpVertexGluToGluhh(2,3)& 
 & ,AmpVertexIRosGluToGluhh(2,3),AmpVertexIRdrGluToGluhh(2,3), AmpSumGluToGluhh(2,3), AmpSum2GluToGluhh(2,3) 
Complex(dp) :: AmpTreeZGluToGluhh(2,3),AmpWaveZGluToGluhh(2,3),AmpVertexZGluToGluhh(2,3) 
Real(dp) :: AmpSqGluToGluhh(3),  AmpSqTreeGluToGluhh(3) 
Real(dp) :: MRPGluToGluVG,MRGGluToGluVG, MRPZGluToGluVG,MRGZGluToGluVG 
Real(dp) :: MVPGluToGluVG 
Real(dp) :: RMsqTreeGluToGluVG,RMsqWaveGluToGluVG,RMsqVertexGluToGluVG 
Complex(dp) :: AmpTreeGluToGluVG(4),AmpWaveGluToGluVG(4)=(0._dp,0._dp),AmpVertexGluToGluVG(4)& 
 & ,AmpVertexIRosGluToGluVG(4),AmpVertexIRdrGluToGluVG(4), AmpSumGluToGluVG(4), AmpSum2GluToGluVG(4) 
Complex(dp) :: AmpTreeZGluToGluVG(4),AmpWaveZGluToGluVG(4),AmpVertexZGluToGluVG(4) 
Real(dp) :: AmpSqGluToGluVG,  AmpSqTreeGluToGluVG 
Real(dp) :: MRPGluToGluVP,MRGGluToGluVP, MRPZGluToGluVP,MRGZGluToGluVP 
Real(dp) :: MVPGluToGluVP 
Real(dp) :: RMsqTreeGluToGluVP,RMsqWaveGluToGluVP,RMsqVertexGluToGluVP 
Complex(dp) :: AmpTreeGluToGluVP(4),AmpWaveGluToGluVP(4)=(0._dp,0._dp),AmpVertexGluToGluVP(4)& 
 & ,AmpVertexIRosGluToGluVP(4),AmpVertexIRdrGluToGluVP(4), AmpSumGluToGluVP(4), AmpSum2GluToGluVP(4) 
Complex(dp) :: AmpTreeZGluToGluVP(4),AmpWaveZGluToGluVP(4),AmpVertexZGluToGluVP(4) 
Real(dp) :: AmpSqGluToGluVP,  AmpSqTreeGluToGluVP 
Real(dp) :: MRPGluToGluVZ,MRGGluToGluVZ, MRPZGluToGluVZ,MRGZGluToGluVZ 
Real(dp) :: MVPGluToGluVZ 
Real(dp) :: RMsqTreeGluToGluVZ,RMsqWaveGluToGluVZ,RMsqVertexGluToGluVZ 
Complex(dp) :: AmpTreeGluToGluVZ(4),AmpWaveGluToGluVZ(4)=(0._dp,0._dp),AmpVertexGluToGluVZ(4)& 
 & ,AmpVertexIRosGluToGluVZ(4),AmpVertexIRdrGluToGluVZ(4), AmpSumGluToGluVZ(4), AmpSum2GluToGluVZ(4) 
Complex(dp) :: AmpTreeZGluToGluVZ(4),AmpWaveZGluToGluVZ(4),AmpVertexZGluToGluVZ(4) 
Real(dp) :: AmpSqGluToGluVZ,  AmpSqTreeGluToGluVZ 
Write(*,*) "Calculating one-loop decays of Glu " 
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
! Fd Conjg(Sd)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_GluToFdcSd(cplGluFdcSdL,cplGluFdcSdR,MFd,MGlu,              & 
& MSd,MFd2,MGlu2,MSd2,AmpTreeGluToFdcSd)

  Else 
Call Amplitude_Tree_NMSSM_GluToFdcSd(ZcplGluFdcSdL,ZcplGluFdcSdR,MFd,MGlu,            & 
& MSd,MFd2,MGlu2,MSd2,AmpTreeGluToFdcSd)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_GluToFdcSd(MLambda,em,gs,cplGluFdcSdL,cplGluFdcSdR,             & 
& MFdOS,MGluOS,MSdOS,MRPGluToFdcSd,MRGGluToFdcSd)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_GluToFdcSd(MLambda,em,gs,ZcplGluFdcSdL,ZcplGluFdcSdR,           & 
& MFdOS,MGluOS,MSdOS,MRPGluToFdcSd,MRGGluToFdcSd)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_GluToFdcSd(MLambda,em,gs,cplGluFdcSdL,cplGluFdcSdR,             & 
& MFd,MGlu,MSd,MRPGluToFdcSd,MRGGluToFdcSd)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_GluToFdcSd(MLambda,em,gs,ZcplGluFdcSdL,ZcplGluFdcSdR,           & 
& MFd,MGlu,MSd,MRPGluToFdcSd,MRGGluToFdcSd)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_GluToFdcSd(cplGluFdcSdL,cplGluFdcSdR,ctcplGluFdcSdL,        & 
& ctcplGluFdcSdR,MFd,MFd2,MGlu,MGlu2,MSd,MSd2,ZfFDL,ZfFDR,ZffG,ZfSd,AmpWaveGluToFdcSd)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToFdcSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,             & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexGluToFdcSd)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_GluToFdcSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRdrGluToFdcSd)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFdcSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,             & 
& cplChiFdcSdR,ZcplGluFdcSdL,ZcplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,          & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,    & 
& cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,      & 
& AmpVertexIRosGluToFdcSd)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFdcSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,ZcplGluFdcSdL,ZcplGluFdcSdR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosGluToFdcSd)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFdcSd(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,cplChaFucSdR,cplChiFdcSdL,             & 
& cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcChaFdcSuL,             & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplGluFucSuL,    & 
& cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,      & 
& AmpVertexIRosGluToFdcSd)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFdcSd(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplAhSdcSd,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,     & 
& cplcFuFdcVWmR,cplGluFucSuL,cplGluFucSuR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,        & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplHpmSucSd,cplSdcSdVG,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSucSdVWm,AmpVertexIRosGluToFdcSd)

 End if 
 End if 
AmpVertexGluToFdcSd = AmpVertexGluToFdcSd -  AmpVertexIRdrGluToFdcSd! +  AmpVertexIRosGluToFdcSd ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZGluToFdcSd=0._dp 
AmpVertexZGluToFdcSd=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZGluToFdcSd(1,gt2,:) = AmpWaveZGluToFdcSd(1,gt2,:)+ZRUZDL(gt2,gt1)*AmpWaveGluToFdcSd(1,gt1,:) 
AmpVertexZGluToFdcSd(1,gt2,:)= AmpVertexZGluToFdcSd(1,gt2,:)+ZRUZDL(gt2,gt1)*AmpVertexGluToFdcSd(1,gt1,:) 
AmpWaveZGluToFdcSd(2,gt2,:) = AmpWaveZGluToFdcSd(2,gt2,:)+ZRUZDRc(gt2,gt1)*AmpWaveGluToFdcSd(2,gt1,:) 
AmpVertexZGluToFdcSd(2,gt2,:)= AmpVertexZGluToFdcSd(2,gt2,:)+ZRUZDRc(gt2,gt1)*AmpVertexGluToFdcSd(2,gt1,:) 
 End Do 
End Do 
AmpWaveGluToFdcSd=AmpWaveZGluToFdcSd 
AmpVertexGluToFdcSd= AmpVertexZGluToFdcSd
! Final State 2 
AmpWaveZGluToFdcSd=0._dp 
AmpVertexZGluToFdcSd=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZGluToFdcSd(:,:,gt2) = AmpWaveZGluToFdcSd(:,:,gt2)+ZRUZDc(gt2,gt1)*AmpWaveGluToFdcSd(:,:,gt1) 
AmpVertexZGluToFdcSd(:,:,gt2)= AmpVertexZGluToFdcSd(:,:,gt2)+ZRUZDc(gt2,gt1)*AmpVertexGluToFdcSd(:,:,gt1) 
 End Do 
End Do 
AmpWaveGluToFdcSd=AmpWaveZGluToFdcSd 
AmpVertexGluToFdcSd= AmpVertexZGluToFdcSd
End if
If (ShiftIRdiv) Then 
AmpVertexGluToFdcSd = AmpVertexGluToFdcSd  +  AmpVertexIRosGluToFdcSd
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Fd conj[Sd] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumGluToFdcSd = AmpTreeGluToFdcSd 
 AmpSum2GluToFdcSd = AmpTreeGluToFdcSd + 2._dp*AmpWaveGluToFdcSd + 2._dp*AmpVertexGluToFdcSd  
Else 
 AmpSumGluToFdcSd = AmpTreeGluToFdcSd + AmpWaveGluToFdcSd + AmpVertexGluToFdcSd
 AmpSum2GluToFdcSd = AmpTreeGluToFdcSd + AmpWaveGluToFdcSd + AmpVertexGluToFdcSd 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToFdcSd = AmpTreeGluToFdcSd
 AmpSum2GluToFdcSd = AmpTreeGluToFdcSd 
End if 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MFdOS(gt2))+Abs(MSdOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MFd(gt2))+Abs(MSd(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2GluToFdcSd = AmpTreeGluToFdcSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFdOS(gt2),MSdOS(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFd(gt2),MSd(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqGluToFdcSd(gt2, gt3) 
  AmpSum2GluToFdcSd = 2._dp*AmpWaveGluToFdcSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFdOS(gt2),MSdOS(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFd(gt2),MSd(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqGluToFdcSd(gt2, gt3) 
  AmpSum2GluToFdcSd = 2._dp*AmpVertexGluToFdcSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFdOS(gt2),MSdOS(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFd(gt2),MSd(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqGluToFdcSd(gt2, gt3) 
  AmpSum2GluToFdcSd = AmpTreeGluToFdcSd + 2._dp*AmpWaveGluToFdcSd + 2._dp*AmpVertexGluToFdcSd
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFdOS(gt2),MSdOS(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFd(gt2),MSd(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqGluToFdcSd(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2GluToFdcSd = AmpTreeGluToFdcSd
  Call SquareAmp_FtoFS(MGluOS,MFdOS(gt2),MSdOS(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
  AmpSqTreeGluToFdcSd(gt2, gt3) = AmpSqGluToFdcSd(gt2, gt3)  
  AmpSum2GluToFdcSd = + 2._dp*AmpWaveGluToFdcSd + 2._dp*AmpVertexGluToFdcSd
  Call SquareAmp_FtoFS(MGluOS,MFdOS(gt2),MSdOS(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
  AmpSqGluToFdcSd(gt2, gt3) = AmpSqGluToFdcSd(gt2, gt3) + AmpSqTreeGluToFdcSd(gt2, gt3)  
Else  
  AmpSum2GluToFdcSd = AmpTreeGluToFdcSd
  Call SquareAmp_FtoFS(MGlu,MFd(gt2),MSd(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
  AmpSqTreeGluToFdcSd(gt2, gt3) = AmpSqGluToFdcSd(gt2, gt3)  
  AmpSum2GluToFdcSd = + 2._dp*AmpWaveGluToFdcSd + 2._dp*AmpVertexGluToFdcSd
  Call SquareAmp_FtoFS(MGlu,MFd(gt2),MSd(gt3),AmpSumGluToFdcSd(:,gt2, gt3),AmpSum2GluToFdcSd(:,gt2, gt3),AmpSqGluToFdcSd(gt2, gt3)) 
  AmpSqGluToFdcSd(gt2, gt3) = AmpSqGluToFdcSd(gt2, gt3) + AmpSqTreeGluToFdcSd(gt2, gt3)  
End if  
Else  
  AmpSqGluToFdcSd(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToFdcSd(gt2, gt3).eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 1._dp*GammaTPS(MGluOS,MFdOS(gt2),MSdOS(gt3),helfactor*AmpSqGluToFdcSd(gt2, gt3))
Else 
  gP1LGlu(gt1,i4) = 1._dp*GammaTPS(MGlu,MFd(gt2),MSd(gt3),helfactor*AmpSqGluToFdcSd(gt2, gt3))
End if 
If ((Abs(MRPGluToFdcSd(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGGluToFdcSd(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPGluToFdcSd(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGGluToFdcSd(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPGluToFdcSd(gt2, gt3) + MRGGluToFdcSd(gt2, gt3)) 
  gP1LGlu(gt1,i4) = gP1LGlu(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPGluToFdcSd(gt2, gt3) + MRGGluToFdcSd(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LGlu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
If (.not.CalcLoopDecay_LoopInducedOnly) Then 
!---------------- 
! Fu Conjg(Su)
!---------------- 

!Tree Level 
  If (.not.ExternalZfactors) Then 
Call Amplitude_Tree_NMSSM_GluToFucSu(cplGluFucSuL,cplGluFucSuR,MFu,MGlu,              & 
& MSu,MFu2,MGlu2,MSu2,AmpTreeGluToFucSu)

  Else 
Call Amplitude_Tree_NMSSM_GluToFucSu(ZcplGluFucSuL,ZcplGluFucSuR,MFu,MGlu,            & 
& MSu,MFu2,MGlu2,MSu2,AmpTreeGluToFucSu)

  End if 


!Real Corrections 
If (OSkinematics) Then 
  If (.not.ExternalZfactors) Then 
 ! OS and no Z-factors 
Call Gamma_Real_NMSSM_GluToFucSu(MLambda,em,gs,cplGluFucSuL,cplGluFucSuR,             & 
& MFuOS,MGluOS,MSuOS,MRPGluToFucSu,MRGGluToFucSu)

  Else 
 ! OS and Z-factors 
Call Gamma_Real_NMSSM_GluToFucSu(MLambda,em,gs,ZcplGluFucSuL,ZcplGluFucSuR,           & 
& MFuOS,MGluOS,MSuOS,MRPGluToFucSu,MRGGluToFucSu)

  End if 
Else 
 ! DR and no Z-factors 
  If (.not.ExternalZfactors) Then 
Call Gamma_Real_NMSSM_GluToFucSu(MLambda,em,gs,cplGluFucSuL,cplGluFucSuR,             & 
& MFu,MGlu,MSu,MRPGluToFucSu,MRGGluToFucSu)

  Else 
 ! DR and Z-factors 
Call Gamma_Real_NMSSM_GluToFucSu(MLambda,em,gs,ZcplGluFucSuL,ZcplGluFucSuR,           & 
& MFu,MGlu,MSu,MRPGluToFucSu,MRGGluToFucSu)

  End if 
End if 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_GluToFucSu(cplGluFucSuL,cplGluFucSuR,ctcplGluFucSuL,        & 
& ctcplGluFucSuR,MFu,MFu2,MGlu,MGlu2,MSu,MSu2,ZffG,ZfFUL,ZfFUR,ZfSu,AmpWaveGluToFucSu)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToFucSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,MHpm,           & 
& MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,MSd2,             & 
& MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,             & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexGluToFucSu)

If (ShiftIRdiv) Then 
Call Amplitude_IR_VERTEX_NMSSM_GluToFucSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRdrGluToFucSu)

 If (ExternalZfactors) Then 
  If (OSkinematics) Then 
 ! OS and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFucSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,             & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,cplcChaFdcSuR,ZcplGluFucSuL,      & 
& ZcplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,           & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,               & 
& cplSucSuVZ,AmpVertexIRosGluToFucSu)

   Else 
 ! DR and Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFucSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,ZcplGluFucSuL,ZcplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,        & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosGluToFucSu)

 End if 
 Else 
  If (OSkinematics) Then 
 ! OS and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFucSu(MAhOS,MChaOS,MChiOS,MFdOS,MFuOS,            & 
& MGluOS,MhhOS,MHpmOS,MSdOS,MSuOS,MVG,MVP,MVWmOS,MVZOS,MAh2OS,MCha2OS,MChi2OS,           & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MHpm2OS,MSd2OS,MSu2OS,MVG2,MVP2,MVWm2OS,MVZ2OS,           & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,cplChaFucSdR,cplChiFucSuL,             & 
& cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,       & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFuFuVGL,            & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,          & 
& cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVG,cplSucSuVP,               & 
& cplSucSuVZ,AmpVertexIRosGluToFucSu)

   Else 
 ! DR and no Z-factors 
Call Amplitude_IR_VERTEX_NMSSM_GluToFucSu(MAh,MCha,MChi,MFd,MFu,MGlu,Mhh,             & 
& MHpm,MSd,MSu,MVG,MVP,MVWm,MVZ,MAh2,MCha2,MChi2,MFd2,MFu2,MGlu2,Mhh2,MHpm2,             & 
& MSd2,MSu2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,cplAhSucSu,cplChaFucSdL,        & 
& cplChaFucSdR,cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplcChaFdcSuL,        & 
& cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,             & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,           & 
& cplSucSuVG,cplSucSuVP,cplSucSuVZ,AmpVertexIRosGluToFucSu)

 End if 
 End if 
AmpVertexGluToFucSu = AmpVertexGluToFucSu -  AmpVertexIRdrGluToFucSu! +  AmpVertexIRosGluToFucSu ! Shift added later
End if 


 ! Add Z-factors to have external fields on-shell 
 If (ExternalZfactors) Then 
! Final State 1 
AmpWaveZGluToFucSu=0._dp 
AmpVertexZGluToFucSu=0._dp 
Do gt1=1,3
  Do gt2=1,3
AmpWaveZGluToFucSu(1,gt2,:) = AmpWaveZGluToFucSu(1,gt2,:)+ZRUZUL(gt2,gt1)*AmpWaveGluToFucSu(1,gt1,:) 
AmpVertexZGluToFucSu(1,gt2,:)= AmpVertexZGluToFucSu(1,gt2,:)+ZRUZUL(gt2,gt1)*AmpVertexGluToFucSu(1,gt1,:) 
AmpWaveZGluToFucSu(2,gt2,:) = AmpWaveZGluToFucSu(2,gt2,:)+ZRUZURc(gt2,gt1)*AmpWaveGluToFucSu(2,gt1,:) 
AmpVertexZGluToFucSu(2,gt2,:)= AmpVertexZGluToFucSu(2,gt2,:)+ZRUZURc(gt2,gt1)*AmpVertexGluToFucSu(2,gt1,:) 
 End Do 
End Do 
AmpWaveGluToFucSu=AmpWaveZGluToFucSu 
AmpVertexGluToFucSu= AmpVertexZGluToFucSu
! Final State 2 
AmpWaveZGluToFucSu=0._dp 
AmpVertexZGluToFucSu=0._dp 
Do gt1=1,6
  Do gt2=1,6
AmpWaveZGluToFucSu(:,:,gt2) = AmpWaveZGluToFucSu(:,:,gt2)+ZRUZUc(gt2,gt1)*AmpWaveGluToFucSu(:,:,gt1) 
AmpVertexZGluToFucSu(:,:,gt2)= AmpVertexZGluToFucSu(:,:,gt2)+ZRUZUc(gt2,gt1)*AmpVertexGluToFucSu(:,:,gt1) 
 End Do 
End Do 
AmpWaveGluToFucSu=AmpWaveZGluToFucSu 
AmpVertexGluToFucSu= AmpVertexZGluToFucSu
End if
If (ShiftIRdiv) Then 
AmpVertexGluToFucSu = AmpVertexGluToFucSu  +  AmpVertexIRosGluToFucSu
End if
 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Fu conj[Su] -----------------------" 
End if 
If (.not.SquareFullAmplitudeDecays) Then 
 AmpSumGluToFucSu = AmpTreeGluToFucSu 
 AmpSum2GluToFucSu = AmpTreeGluToFucSu + 2._dp*AmpWaveGluToFucSu + 2._dp*AmpVertexGluToFucSu  
Else 
 AmpSumGluToFucSu = AmpTreeGluToFucSu + AmpWaveGluToFucSu + AmpVertexGluToFucSu
 AmpSum2GluToFucSu = AmpTreeGluToFucSu + AmpWaveGluToFucSu + AmpVertexGluToFucSu 
End If 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToFucSu = AmpTreeGluToFucSu
 AmpSum2GluToFucSu = AmpTreeGluToFucSu 
End if 
gt1=1 
i4 = isave 
  Do gt2=1,3
    Do gt3=1,6
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MFuOS(gt2))+Abs(MSuOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MFu(gt2))+Abs(MSu(gt3)))))) Then 
 If (DebugLoopDecays) Then 
  Write(*,*) gt2, gt3 
  AmpSum2GluToFucSu = AmpTreeGluToFucSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFuOS(gt2),MSuOS(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFu(gt2),MSu(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x TREE: ",AmpSqGluToFucSu(gt2, gt3) 
  AmpSum2GluToFucSu = 2._dp*AmpWaveGluToFucSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFuOS(gt2),MSuOS(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFu(gt2),MSu(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x WAVE: ",AmpSqGluToFucSu(gt2, gt3) 
  AmpSum2GluToFucSu = 2._dp*AmpVertexGluToFucSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFuOS(gt2),MSuOS(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFu(gt2),MSu(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x VERTEX: ",AmpSqGluToFucSu(gt2, gt3) 
  AmpSum2GluToFucSu = AmpTreeGluToFucSu + 2._dp*AmpWaveGluToFucSu + 2._dp*AmpVertexGluToFucSu
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MFuOS(gt2),MSuOS(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MFu(gt2),MSu(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
End if  
  Write(*,*) "TREE x (TREE+WAVE+VERTEX): ",AmpSqGluToFucSu(gt2, gt3) 
 End if 
If (OSkinematics) Then 
  AmpSum2GluToFucSu = AmpTreeGluToFucSu
  Call SquareAmp_FtoFS(MGluOS,MFuOS(gt2),MSuOS(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
  AmpSqTreeGluToFucSu(gt2, gt3) = AmpSqGluToFucSu(gt2, gt3)  
  AmpSum2GluToFucSu = + 2._dp*AmpWaveGluToFucSu + 2._dp*AmpVertexGluToFucSu
  Call SquareAmp_FtoFS(MGluOS,MFuOS(gt2),MSuOS(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
  AmpSqGluToFucSu(gt2, gt3) = AmpSqGluToFucSu(gt2, gt3) + AmpSqTreeGluToFucSu(gt2, gt3)  
Else  
  AmpSum2GluToFucSu = AmpTreeGluToFucSu
  Call SquareAmp_FtoFS(MGlu,MFu(gt2),MSu(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
  AmpSqTreeGluToFucSu(gt2, gt3) = AmpSqGluToFucSu(gt2, gt3)  
  AmpSum2GluToFucSu = + 2._dp*AmpWaveGluToFucSu + 2._dp*AmpVertexGluToFucSu
  Call SquareAmp_FtoFS(MGlu,MFu(gt2),MSu(gt3),AmpSumGluToFucSu(:,gt2, gt3),AmpSum2GluToFucSu(:,gt2, gt3),AmpSqGluToFucSu(gt2, gt3)) 
  AmpSqGluToFucSu(gt2, gt3) = AmpSqGluToFucSu(gt2, gt3) + AmpSqTreeGluToFucSu(gt2, gt3)  
End if  
Else  
  AmpSqGluToFucSu(gt2, gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToFucSu(gt2, gt3).eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 1._dp*GammaTPS(MGluOS,MFuOS(gt2),MSuOS(gt3),helfactor*AmpSqGluToFucSu(gt2, gt3))
Else 
  gP1LGlu(gt1,i4) = 1._dp*GammaTPS(MGlu,MFu(gt2),MSu(gt3),helfactor*AmpSqGluToFucSu(gt2, gt3))
End if 
If ((Abs(MRPGluToFucSu(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGGluToFucSu(gt2, gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
 ! Adding real corrections 
If ((Abs(MRPGluToFucSu(gt2, gt3)).gt.1.0E-20_dp).or.(Abs(MRGGluToFucSu(gt2, gt3)).gt.1.0E-20_dp)) Then 
 If (.not.OnlyTreeLevelContributions) Then 
   If (DebugLoopDecays) Write(*,*) "real", phasespacefactor*1._dp*helfactor*(MRPGluToFucSu(gt2, gt3) + MRGGluToFucSu(gt2, gt3)) 
  gP1LGlu(gt1,i4) = gP1LGlu(gt1,i4) + phasespacefactor*1._dp*helfactor*(MRPGluToFucSu(gt2, gt3) + MRGGluToFucSu(gt2, gt3))
   If (DebugLoopDecays) Write(*,*) "sum",  gP1LGlu(gt1,i4) 
  End if 
End if 
End if 
i4=i4+1

    End do
  End do
isave = i4 
End If 
!---------------- 
! Chi VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_GluToChiVG(MChiOS,MFdOS,MFuOS,MGluOS,MSdOS,               & 
& MSuOS,MVG,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVG2,ZcplChiFdcSdL,              & 
& ZcplChiFdcSdR,ZcplChiFucSuL,ZcplChiFucSuR,ZcplcFdChiSdL,ZcplcFdChiSdR,ZcplcFuChiSuL,   & 
& ZcplcFuChiSuR,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdVGL,ZcplcFdFdVGR,ZcplGluFucSuL,     & 
& ZcplGluFucSuR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuGluSuL,     & 
& ZcplcFuGluSuR,ZcplSdcSdVG,ZcplSucSuVG,AmpVertexGluToChiVG)

 Else 
Call Amplitude_VERTEX_NMSSM_GluToChiVG(MChiOS,MFdOS,MFuOS,MGluOS,MSdOS,               & 
& MSuOS,MVG,MChi2OS,MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVG2,cplChiFdcSdL,               & 
& cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,         & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVGL,cplcFdFdVGR,cplGluFucSuL,           & 
& cplGluFucSuR,cplcFuFuVGL,cplcFuFuVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,           & 
& cplcFuGluSuR,cplSdcSdVG,cplSucSuVG,AmpVertexGluToChiVG)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToChiVG(MChi,MFd,MFu,MGlu,MSd,MSu,MVG,MChi2,           & 
& MFd2,MFu2,MGlu2,MSd2,MSu2,MVG2,cplChiFdcSdL,cplChiFdcSdR,cplChiFucSuL,cplChiFucSuR,    & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdVGL,cplcFdFdVGR,cplGluFucSuL,cplGluFucSuR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplSdcSdVG,cplSucSuVG,             & 
& AmpVertexGluToChiVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Chi VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToChiVG = 0._dp 
 AmpSum2GluToChiVG = 0._dp  
Else 
 AmpSumGluToChiVG = AmpVertexGluToChiVG + AmpWaveGluToChiVG
 AmpSum2GluToChiVG = AmpVertexGluToChiVG + AmpWaveGluToChiVG 
End If 
gt1=1 
i4 = isave 
  Do gt2=1,5
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MChiOS(gt2))+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MChi(gt2))+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MGluOS,MChiOS(gt2),0._dp,AmpSumGluToChiVG(:,gt2),AmpSum2GluToChiVG(:,gt2),AmpSqGluToChiVG(gt2)) 
Else  
  Call SquareAmp_FtoFV(MGlu,MChi(gt2),MVG,AmpSumGluToChiVG(:,gt2),AmpSum2GluToChiVG(:,gt2),AmpSqGluToChiVG(gt2)) 
End if  
Else  
  AmpSqGluToChiVG(gt2) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToChiVG(gt2).eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGluOS,MChiOS(gt2),0._dp,helfactor*AmpSqGluToChiVG(gt2))
Else 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGlu,MChi(gt2),MVG,helfactor*AmpSqGluToChiVG(gt2))
End if 
If ((Abs(MRPGluToChiVG(gt2)).gt.1.0E-20_dp).or.(Abs(MRGGluToChiVG(gt2)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
End if 
i4=i4+1

  End do
isave = i4 
!---------------- 
! Glu Ah
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_GluToGluAh(MAhOS,MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,          & 
& MAh2OS,MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,ZcplcFdFdAhL,ZcplcFdFdAhR,ZcplcFuFuAhL,     & 
& ZcplcFuFuAhR,ZcplAhSdcSd,ZcplAhSucSu,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplGluFucSuL,        & 
& ZcplGluFucSuR,ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,AmpVertexGluToGluAh)

 Else 
Call Amplitude_VERTEX_NMSSM_GluToGluAh(MAhOS,MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,          & 
& MAh2OS,MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,        & 
& cplcFuFuAhR,cplAhSdcSd,cplAhSucSu,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,              & 
& cplGluFucSuR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,AmpVertexGluToGluAh)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToGluAh(MAh,MFd,MFu,MGlu,MSd,MSu,MAh2,MFd2,            & 
& MFu2,MGlu2,MSd2,MSu2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhSdcSd,       & 
& cplAhSucSu,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,AmpVertexGluToGluAh)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Glu Ah -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToGluAh = 0._dp 
 AmpSum2GluToGluAh = 0._dp  
Else 
 AmpSumGluToGluAh = AmpVertexGluToGluAh + AmpWaveGluToGluAh
 AmpSum2GluToGluAh = AmpVertexGluToGluAh + AmpWaveGluToGluAh 
End If 
gt1=1 
i4 = isave 
    Do gt3=2,3
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MGluOS)+Abs(MAhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MGlu)+Abs(MAh(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MGluOS,MAhOS(gt3),AmpSumGluToGluAh(:,gt3),AmpSum2GluToGluAh(:,gt3),AmpSqGluToGluAh(gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MGlu,MAh(gt3),AmpSumGluToGluAh(:,gt3),AmpSum2GluToGluAh(:,gt3),AmpSqGluToGluAh(gt3)) 
End if  
Else  
  AmpSqGluToGluAh(gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToGluAh(gt3).eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGluOS,MGluOS,MAhOS(gt3),helfactor*AmpSqGluToGluAh(gt3))
Else 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGlu,MGlu,MAh(gt3),helfactor*AmpSqGluToGluAh(gt3))
End if 
If ((Abs(MRPGluToGluAh(gt3)).gt.1.0E-20_dp).or.(Abs(MRGGluToGluAh(gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
End if 
i4=i4+1

    End do
isave = i4 
!---------------- 
! Glu hh
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_GluToGluhh(MFdOS,MFuOS,MGluOS,MhhOS,MSdOS,MSuOS,          & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MSd2OS,MSu2OS,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdhhL,   & 
& ZcplcFdFdhhR,ZcplGluFucSuL,ZcplGluFucSuR,ZcplcFuFuhhL,ZcplcFuFuhhR,ZcplcFdGluSdL,      & 
& ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplhhSdcSd,ZcplhhSucSu,AmpVertexGluToGluhh)

 Else 
Call Amplitude_VERTEX_NMSSM_GluToGluhh(MFdOS,MFuOS,MGluOS,MhhOS,MSdOS,MSuOS,          & 
& MFd2OS,MFu2OS,MGlu2OS,Mhh2OS,MSd2OS,MSu2OS,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,      & 
& cplcFdFdhhR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,            & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,AmpVertexGluToGluhh)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToGluhh(MFd,MFu,MGlu,Mhh,MSd,MSu,MFd2,MFu2,            & 
& MGlu2,Mhh2,MSd2,MSu2,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplGluFucSuL,   & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,           & 
& cplcFuGluSuR,cplhhSdcSd,cplhhSucSu,AmpVertexGluToGluhh)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Glu hh -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToGluhh = 0._dp 
 AmpSum2GluToGluhh = 0._dp  
Else 
 AmpSumGluToGluhh = AmpVertexGluToGluhh + AmpWaveGluToGluhh
 AmpSum2GluToGluhh = AmpVertexGluToGluhh + AmpWaveGluToGluhh 
End If 
gt1=1 
i4 = isave 
    Do gt3=1,3
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MGluOS)+Abs(MhhOS(gt3))))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MGlu)+Abs(Mhh(gt3)))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFS(MGluOS,MGluOS,MhhOS(gt3),AmpSumGluToGluhh(:,gt3),AmpSum2GluToGluhh(:,gt3),AmpSqGluToGluhh(gt3)) 
Else  
  Call SquareAmp_FtoFS(MGlu,MGlu,Mhh(gt3),AmpSumGluToGluhh(:,gt3),AmpSum2GluToGluhh(:,gt3),AmpSqGluToGluhh(gt3)) 
End if  
Else  
  AmpSqGluToGluhh(gt3) = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToGluhh(gt3).eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGluOS,MGluOS,MhhOS(gt3),helfactor*AmpSqGluToGluhh(gt3))
Else 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGlu,MGlu,Mhh(gt3),helfactor*AmpSqGluToGluhh(gt3))
End if 
If ((Abs(MRPGluToGluhh(gt3)).gt.1.0E-20_dp).or.(Abs(MRGGluToGluhh(gt3)).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
End if 
i4=i4+1

    End do
isave = i4 
!---------------- 
! Glu VG
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_WAVE_NMSSM_GluToGluVG(ZcplGluGluVGL,ZcplGluGluVGR,ctcplGluGluVGL,      & 
& ctcplGluGluVGR,MGluOS,MGlu2OS,MVG,MVG2,ZffG,ZfVG,AmpWaveGluToGluVG)

 Else 
Call Amplitude_WAVE_NMSSM_GluToGluVG(cplGluGluVGL,cplGluGluVGR,ctcplGluGluVGL,        & 
& ctcplGluGluVGR,MGluOS,MGlu2OS,MVG,MVG2,ZffG,ZfVG,AmpWaveGluToGluVG)

 End if 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_GluToGluVG(MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,MVG,            & 
& MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVG2,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdVGL,     & 
& ZcplcFdFdVGR,ZcplGluFucSuL,ZcplGluFucSuR,ZcplcFuFuVGL,ZcplcFuFuVGR,ZcplGluGluVGL,      & 
& ZcplGluGluVGR,ZcplcFdGluSdL,ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplSdcSdVG,     & 
& ZcplSucSuVG,ZcplVGVGVG,AmpVertexGluToGluVG)

 Else 
Call Amplitude_VERTEX_NMSSM_GluToGluVG(MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,MVG,            & 
& MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVG2,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVGL,        & 
& cplcFdFdVGR,cplGluFucSuL,cplGluFucSuR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,            & 
& cplGluGluVGR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplSdcSdVG,           & 
& cplSucSuVG,cplVGVGVG,AmpVertexGluToGluVG)

 End if 
Else 


!Self-energy Corrections 
Call Amplitude_WAVE_NMSSM_GluToGluVG(cplGluGluVGL,cplGluGluVGR,ctcplGluGluVGL,        & 
& ctcplGluGluVGR,MGlu,MGlu2,MVG,MVG2,ZffG,ZfVG,AmpWaveGluToGluVG)



!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToGluVG(MFd,MFu,MGlu,MSd,MSu,MVG,MFd2,MFu2,            & 
& MGlu2,MSd2,MSu2,MVG2,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVGL,cplcFdFdVGR,cplGluFucSuL,   & 
& cplGluFucSuR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplcFdGluSdL,           & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplSdcSdVG,cplSucSuVG,cplVGVGVG,AmpVertexGluToGluVG)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Glu VG -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToGluVG = 0._dp 
 AmpSum2GluToGluVG = 0._dp  
Else 
 AmpSumGluToGluVG = AmpVertexGluToGluVG + AmpWaveGluToGluVG
 AmpSum2GluToGluVG = AmpVertexGluToGluVG + AmpWaveGluToGluVG 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MGluOS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MGlu)+Abs(MVG))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MGluOS,MGluOS,0._dp,AmpSumGluToGluVG(:),AmpSum2GluToGluVG(:),AmpSqGluToGluVG) 
Else  
  Call SquareAmp_FtoFV(MGlu,MGlu,MVG,AmpSumGluToGluVG(:),AmpSum2GluToGluVG(:),AmpSqGluToGluVG) 
End if  
Else  
  AmpSqGluToGluVG = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToGluVG.eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 6._dp*GammaTPS(MGluOS,MGluOS,0._dp,helfactor*AmpSqGluToGluVG)
Else 
  gP1LGlu(gt1,i4) = 6._dp*GammaTPS(MGlu,MGlu,MVG,helfactor*AmpSqGluToGluVG)
End if 
If ((Abs(MRPGluToGluVG).gt.1.0E-20_dp).or.(Abs(MRGGluToGluVG).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! Glu VP
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_GluToGluVP(MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,MVP,            & 
& MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVP2,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdVPL,     & 
& ZcplcFdFdVPR,ZcplGluFucSuL,ZcplGluFucSuR,ZcplcFuFuVPL,ZcplcFuFuVPR,ZcplcFdGluSdL,      & 
& ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplSdcSdVP,ZcplSucSuVP,AmpVertexGluToGluVP)

 Else 
Call Amplitude_VERTEX_NMSSM_GluToGluVP(MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,MVP,            & 
& MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVP2,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplGluFucSuL,cplGluFucSuR,cplcFuFuVPL,cplcFuFuVPR,cplcFdGluSdL,            & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplSdcSdVP,cplSucSuVP,AmpVertexGluToGluVP)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToGluVP(MFd,MFu,MGlu,MSd,MSu,MVP,MFd2,MFu2,            & 
& MGlu2,MSd2,MSu2,MVP2,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVPL,cplcFdFdVPR,cplGluFucSuL,   & 
& cplGluFucSuR,cplcFuFuVPL,cplcFuFuVPR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,           & 
& cplcFuGluSuR,cplSdcSdVP,cplSucSuVP,AmpVertexGluToGluVP)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Glu VP -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToGluVP = 0._dp 
 AmpSum2GluToGluVP = 0._dp  
Else 
 AmpSumGluToGluVP = AmpVertexGluToGluVP + AmpWaveGluToGluVP
 AmpSum2GluToGluVP = AmpVertexGluToGluVP + AmpWaveGluToGluVP 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MGluOS)+Abs(0.)))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MGlu)+Abs(MVP))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MGluOS,MGluOS,0._dp,AmpSumGluToGluVP(:),AmpSum2GluToGluVP(:),AmpSqGluToGluVP) 
Else  
  Call SquareAmp_FtoFV(MGlu,MGlu,MVP,AmpSumGluToGluVP(:),AmpSum2GluToGluVP(:),AmpSqGluToGluVP) 
End if  
Else  
  AmpSqGluToGluVP = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToGluVP.eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGluOS,MGluOS,0._dp,helfactor*AmpSqGluToGluVP)
Else 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGlu,MGlu,MVP,helfactor*AmpSqGluToGluVP)
End if 
If ((Abs(MRPGluToGluVP).gt.1.0E-20_dp).or.(Abs(MRGGluToGluVP).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
End if 
i4=i4+1

isave = i4 
!---------------- 
! Glu VZ
!---------------- 

If (LoopInducedDecaysOS) Then 


!Self-energy Corrections 


!Vertex Corrections 
 If (ExternalZfactors) Then 
Call Amplitude_VERTEX_NMSSM_GluToGluVZ(MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,MVZOS,          & 
& MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVZ2OS,ZcplGluFdcSdL,ZcplGluFdcSdR,ZcplcFdFdVZL,   & 
& ZcplcFdFdVZR,ZcplGluFucSuL,ZcplGluFucSuR,ZcplcFuFuVZL,ZcplcFuFuVZR,ZcplcFdGluSdL,      & 
& ZcplcFdGluSdR,ZcplcFuGluSuL,ZcplcFuGluSuR,ZcplSdcSdVZ,ZcplSucSuVZ,AmpVertexGluToGluVZ)

 Else 
Call Amplitude_VERTEX_NMSSM_GluToGluVZ(MFdOS,MFuOS,MGluOS,MSdOS,MSuOS,MVZOS,          & 
& MFd2OS,MFu2OS,MGlu2OS,MSd2OS,MSu2OS,MVZ2OS,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,      & 
& cplcFdFdVZR,cplGluFucSuL,cplGluFucSuR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,            & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplSdcSdVZ,cplSucSuVZ,AmpVertexGluToGluVZ)

 End if 
Else 


!Self-energy Corrections 


!Vertex Corrections 
Call Amplitude_VERTEX_NMSSM_GluToGluVZ(MFd,MFu,MGlu,MSd,MSu,MVZ,MFd2,MFu2,            & 
& MGlu2,MSd2,MSu2,MVZ2,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdVZL,cplcFdFdVZR,cplGluFucSuL,   & 
& cplGluFucSuR,cplcFuFuVZL,cplcFuFuVZR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,           & 
& cplcFuGluSuR,cplSdcSdVZ,cplSucSuVZ,AmpVertexGluToGluVZ)

End if 


 !Square the amplitude 
If (DebugLoopDecays) Then 
Write(*,*) "------------------ Glu->Glu VZ -----------------------" 
End if 
If (OnlyTreeLevelContributions) Then 
 AmpSumGluToGluVZ = 0._dp 
 AmpSum2GluToGluVZ = 0._dp  
Else 
 AmpSumGluToGluVZ = AmpVertexGluToGluVZ + AmpWaveGluToGluVZ
 AmpSum2GluToGluVZ = AmpVertexGluToGluVZ + AmpWaveGluToGluVZ 
End If 
gt1=1 
i4 = isave 
If (((OSkinematics).and.(Abs(MGluOS).gt.(Abs(MGluOS)+Abs(MVZOS)))).or.((.not.OSkinematics).and.(Abs(MGlu).gt.(Abs(MGlu)+Abs(MVZ))))) Then 
If (OSkinematics) Then 
  Call SquareAmp_FtoFV(MGluOS,MGluOS,MVZOS,AmpSumGluToGluVZ(:),AmpSum2GluToGluVZ(:),AmpSqGluToGluVZ) 
Else  
  Call SquareAmp_FtoFV(MGlu,MGlu,MVZ,AmpSumGluToGluVZ(:),AmpSum2GluToGluVZ(:),AmpSqGluToGluVZ) 
End if  
Else  
  AmpSqGluToGluVZ = 0._dp 
End if  

! Calculate Partial widths 
helfactor = 2._dp 
If (AmpSqGluToGluVZ.eq.0._dp) Then 
  gP1LGlu(gt1,i4) = 0._dp 
Else 
If (OSkinematics) Then 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGluOS,MGluOS,MVZOS,helfactor*AmpSqGluToGluVZ)
Else 
  gP1LGlu(gt1,i4) = 2._dp*GammaTPS(MGlu,MGlu,MVZ,helfactor*AmpSqGluToGluVZ)
End if 
If ((Abs(MRPGluToGluVZ).gt.1.0E-20_dp).or.(Abs(MRGGluToGluVZ).gt.1.0E-20_dp)) Then 
  phasespacefactor = 1._dp 
End if 
 If (DebugLoopDecays) Write(*,*) "virtual", gP1LGlu(gt1,i4) 
End if 
i4=i4+1

isave = i4 
End Subroutine OneLoopDecay_Glu

End Module Wrapper_OneLoopDecay_Glu_NMSSM
