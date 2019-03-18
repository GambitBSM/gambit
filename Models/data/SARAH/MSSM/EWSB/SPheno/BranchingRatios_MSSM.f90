! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:00 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module BranchingRatios_MSSM 
 
Use Control 
Use Couplings_MSSM 
Use Model_Data_MSSM 
Use LoopCouplings_MSSM 
Use Glu3Decays_MSSM 
Use Chi3Decays_MSSM 
Use Cha3Decays_MSSM 
Use Sd3Decays_MSSM 
Use Su3Decays_MSSM 
Use Se3Decays_MSSM 
Use Sv3Decays_MSSM 
Use SUSYDecays_MSSM 
 
Contains 
 
Subroutine CalculateBR(CTBD,fac3,epsI,deltaM,kont,MAh,MAh2,MCha,MCha2,MChi,           & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,            & 
& ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,             & 
& Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,gPSd,gTSd,BRSd,              & 
& gPSu,gTSu,BRSu,gPSe,gTSe,BRSe,gPSv,gTSv,BRSv,gPhh,gThh,BRhh,gPAh,gTAh,BRAh,            & 
& gPHpm,gTHpm,BRHpm,gPGlu,gTGlu,BRGlu,gPChi,gTChi,BRChi,gPCha,gTCha,BRCha,               & 
& gPFu,gTFu,BRFu)

Real(dp), Intent(in) :: epsI, deltaM, fac3 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: CTBD 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp),Intent(in) :: vd,vu

Real(dp),Intent(inout) :: gPSd(6,1080),gTSd(6),BRSd(6,1080),gPSu(6,1080),gTSu(6),BRSu(6,1080),gPSe(6,987),      & 
& gTSe(6),BRSe(6,987),gPSv(3,888),gTSv(3),BRSv(3,888),gPhh(2,171),gThh(2),               & 
& BRhh(2,171),gPAh(2,157),gTAh(2),BRAh(2,157),gPHpm(2,88),gTHpm(2),BRHpm(2,88),          & 
& gPGlu(1,126),gTGlu,BRGlu(1,126),gPChi(4,361),gTChi(4),BRChi(4,361),gPCha(2,272),       & 
& gTCha(2),BRCha(2,272),gPFu(3,60),gTFu(3),BRFu(3,60)

Complex(dp) :: cplHiggsPP(2),cplHiggsGG(2),cplPseudoHiggsPP(2),cplPseudoHiggsGG(2),cplHiggsZZvirt(2),& 
& cplHiggsWWvirt(2)

Real(dp) :: gGluFdcFdChi(1,3,3,4),gGluFdcFucCha(1,3,3,2),gGluFucFuChi(1,3,3,4),gChiChicChaCha(4,4,2,2),& 
& gChiChiChiChi(4,4,4,4),gChiChicFdFd(4,4,3,3),gChiChicFeFe(4,4,3,3),gChiChicFuFu(4,4,3,3),& 
& gChiChacFdFu(4,2,3,3),gChiChacFeFv(4,2,3,3),gChiChicFvFv(4,4,3,3),gChiFdcFdGlu(4,3,3,1),& 
& gChiFucFuGlu(4,3,3,1),gChaChacChaCha(2,2,2,2),gChaChaChiChi(2,2,4,4),gChaChacFdFd(2,2,3,3),& 
& gChaChacFeFe(2,2,3,3),gChaChacFuFu(2,2,3,3),gChaChacFvFv(2,2,3,3),gChaChicFuFd(2,4,3,3),& 
& gChaChicFvFe(2,4,3,3),gChaFdcFuGlu(2,3,3,1),gSdAhChaFu(6,2,2,3),gSdAhChiFd(6,2,4,3),   & 
& gSdAhFdGlu(6,2,3,1),gSdSuChaChi(6,6,2,4),gSdChaFdcHpm(6,2,3,2),gSdhhChaFu(6,2,2,3),    & 
& gSdChaGluSu(6,2,1,6),gSdSdChacCha(6,6,2,2),gSdSdChiChi(6,6,4,4),gSdhhChiFd(6,2,4,3),   & 
& gSdHpmChiFu(6,2,4,3),gSdChiGluSd(6,4,1,6),gSdFdFdcSd(6,3,3,6),gSdFdFecSe(6,3,3,6),     & 
& gSdFuFdcSu(6,3,3,6),gSdFdFvcSv(6,3,3,3),gSdHpmFdcCha(6,2,3,2),gSdSdFdcFd(6,6,3,3),     & 
& gSdFdSecFe(6,3,6,3),gSdSuFdcFu(6,6,3,3),gSdFdSvcFv(6,3,3,3),gSdFuFecSv(6,3,3,3),       & 
& gSdSdFucFu(6,6,3,3),gSdFuSecFv(6,3,6,3),gSdhhFdGlu(6,2,3,1),gSdHpmFuGlu(6,2,3,1),      & 
& gSdGluGluSd(6,1,1,6),gSdSdFecFe(6,6,3,3),gSdSdFvcFv(6,6,3,3),gSdSuFecFv(6,6,3,3),      & 
& gSuAhChiFu(6,2,4,3),gSuAhFdcCha(6,2,3,2),gSuAhFuGlu(6,2,3,1),gSuSuChiChi(6,6,4,4),     & 
& gSucHpmChiFd(6,2,4,3),gSuhhChiFu(6,2,4,3),gSuChiGluSu(6,4,1,6),gSuSdChicCha(6,6,4,2),  & 
& gSuFdFucSd(6,3,3,6),gSuFdFvcSe(6,3,3,6),gSuhhFdcCha(6,2,3,2),gSuSuFdcFd(6,6,3,3),      & 
& gSuFdSvcFe(6,3,3,3),gSucHpmChaFu(6,2,2,3),gSuFuFecSe(6,3,3,6),gSuFuFucSu(6,3,3,6),     & 
& gSuFuFvcSv(6,3,3,3),gSucChaFuHpm(6,2,3,2),gSuSdFucFd(6,6,3,3),gSuFuSecFe(6,3,6,3),     & 
& gSuSuFucFu(6,6,3,3),gSuFuSvcFv(6,3,3,3),gSucHpmFdGlu(6,2,3,1),gSuhhFuGlu(6,2,3,1),     & 
& gSuGluGluSu(6,1,1,6),gSuGluSdcCha(6,1,6,2),gSuSdFvcFe(6,6,3,3),gSuSuChacCha(6,6,2,2),  & 
& gSuSuFecFe(6,6,3,3),gSuSuFvcFv(6,6,3,3),gSeAhChaFv(6,2,2,3),gSeAhChiFe(6,2,4,3),       & 
& gSeSvChaChi(6,3,2,4),gSeChaFecHpm(6,2,3,2),gSeSeChacCha(6,6,2,2),gSeSeChiChi(6,6,4,4), & 
& gSehhChiFe(6,2,4,3),gSeHpmChiFv(6,2,4,3),gSeFeFdcSd(6,3,3,6),gSeFeFecSe(6,3,3,6),      & 
& gSeFeFucSu(6,3,3,6),gSeFvFecSv(6,3,3,3),gSeHpmFecCha(6,2,3,2),gSeFeSdcFd(6,3,6,3),     & 
& gSeSeFecFe(6,6,3,3),gSeFeSucFu(6,3,6,3),gSeSvFecFv(6,3,3,3),gSehhChaFv(6,2,2,3),       & 
& gSeFvFdcSu(6,3,3,6),gSeFvSdcFu(6,3,6,3),gSeSeFvcFv(6,6,3,3),gSeSeFdcFd(6,6,3,3),       & 
& gSeSeFucFu(6,6,3,3),gSeSvFdcFu(6,3,3,3),gSvSvChiChi(3,3,4,4),gSvcHpmChiFe(3,2,4,3),    & 
& gSvSeChicCha(3,6,4,2),gSvFeAhcCha(3,3,2,2),gSvFeFucSd(3,3,3,6),gSvFeFvcSe(3,3,3,6),    & 
& gSvhhFecCha(3,2,3,2),gSvFeSucFd(3,3,6,3),gSvSvFecFe(3,3,3,3),gSvFvAhChi(3,3,2,4),      & 
& gSvcHpmChaFv(3,2,2,3),gSvhhChiFv(3,2,4,3),gSvFvFdcSd(3,3,3,6),gSvFvFucSu(3,3,3,6),     & 
& gSvFvFvcSv(3,3,3,3),gSvcChaFvHpm(3,2,3,2),gSvFvSdcFd(3,3,6,3),gSvSeFvcFe(3,6,3,3),     & 
& gSvFvSucFu(3,3,6,3),gSvSvFvcFv(3,3,3,3),gSvSeFucFd(3,6,3,3),gSvSvChacCha(3,3,2,2),     & 
& gSvSvFdcFd(3,3,3,3),gSvSvFucFu(3,3,3,3)

Complex(dp) :: coup 
Real(dp) :: vev 
Real(dp) :: gTVZ,gTVWm

Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateBR'
 
Write(*,*) "Calculating branching ratios and decay widths" 
gTVWm = gamW 
gTVZ = gamZ 
gPSd = 0._dp 
gTSd = 0._dp 
BRSd = 0._dp 
Call SdTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPSd(:,1:57),gTSd,BRSd(:,1:57))

Do i1=1,6
gTSd(i1) =Sum(gPSd(i1,:)) 
If (gTSd(i1).Gt.0._dp) BRSd(i1,: ) =gPSd(i1,:)/gTSd(i1) 
End Do 
 

gPSu = 0._dp 
gTSu = 0._dp 
BRSu = 0._dp 
Call SuTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPSu(:,1:57),gTSu,BRSu(:,1:57))

Do i1=1,6
gTSu(i1) =Sum(gPSu(i1,:)) 
If (gTSu(i1).Gt.0._dp) BRSu(i1,: ) =gPSu(i1,:)/gTSu(i1) 
End Do 
 

gPSe = 0._dp 
gTSe = 0._dp 
BRSe = 0._dp 
Call SeTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPSe(:,1:48),gTSe,BRSe(:,1:48))

Do i1=1,6
gTSe(i1) =Sum(gPSe(i1,:)) 
If (gTSe(i1).Gt.0._dp) BRSe(i1,: ) =gPSe(i1,:)/gTSe(i1) 
End Do 
 

gPSv = 0._dp 
gTSv = 0._dp 
BRSv = 0._dp 
Call SvTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPSv(:,1:39),gTSv,BRSv(:,1:39))

Do i1=1,3
gTSv(i1) =Sum(gPSv(i1,:)) 
If (gTSv(i1).Gt.0._dp) BRSv(i1,: ) =gPSv(i1,:)/gTSv(i1) 
End Do 
 

gPhh = 0._dp 
gThh = 0._dp 
BRhh = 0._dp 
Call hhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPhh,gThh,BRhh)

gPAh = 0._dp 
gTAh = 0._dp 
BRAh = 0._dp 
Call AhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPAh,gTAh,BRAh)

! Set Goldstone Widhts 
gTAh(1)=gTVZ


gPHpm = 0._dp 
gTHpm = 0._dp 
BRHpm = 0._dp 
Call HpmTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPHpm,gTHpm,BRHpm)

! Set Goldstone Widhts 
gTHpm(1)=gTVWm


gPGlu = 0._dp 
gTGlu = 0._dp 
BRGlu = 0._dp 
Call GluTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPGlu(:,1:36),gTGlu,BRGlu(:,1:36))

Do i1=1,1
gTGlu =Sum(gPGlu(i1,:)) 
If (gTGlu.Gt.0._dp) BRGlu(i1,: ) =gPGlu(i1,:)/gTGlu 
End Do 
 

gPChi = 0._dp 
gTChi = 0._dp 
BRChi = 0._dp 
Call ChiTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPChi(:,1:83),gTChi,BRChi(:,1:83))

Do i1=1,4
gTChi(i1) =Sum(gPChi(i1,:)) 
If (gTChi(i1).Gt.0._dp) BRChi(i1,: ) =gPChi(i1,:)/gTChi(i1) 
End Do 
 

gPCha = 0._dp 
gTCha = 0._dp 
BRCha = 0._dp 
Call ChaTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPCha(:,1:79),gTCha,BRCha(:,1:79))

Do i1=1,2
gTCha(i1) =Sum(gPCha(i1,:)) 
If (gTCha(i1).Gt.0._dp) BRCha(i1,: ) =gPCha(i1,:)/gTCha(i1) 
End Do 
 

gPFu = 0._dp 
gTFu = 0._dp 
BRFu = 0._dp 
Call FuTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gPFu,gTFu,BRFu)

If (.Not.CTBD) Then 
If (Enable3BDecaysS) Then 
If (MaxVal(gTSd).Lt.MaxVal(fac3*Abs(MSd))) Then 
Call SdThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSdAhChaFu,gSdAhChiFd,gSdAhFdGlu,gSdSuChaChi,          & 
& gSdChaFdcHpm,gSdhhChaFu,gSdChaGluSu,gSdSdChacCha,gSdSdChiChi,gSdhhChiFd,               & 
& gSdHpmChiFu,gSdChiGluSd,gSdFdFdcSd,gSdFdFecSe,gSdFuFdcSu,gSdFdFvcSv,gSdHpmFdcCha,      & 
& gSdSdFdcFd,gSdFdSecFe,gSdSuFdcFu,gSdFdSvcFv,gSdFuFecSv,gSdSdFucFu,gSdFuSecFv,          & 
& gSdhhFdGlu,gSdHpmFuGlu,gSdGluGluSd,gSdSdFecFe,gSdSdFvcFv,gSdSuFecFv,epsI,              & 
& deltaM,.False.,gTSd,gPSd(:,58:1080),BRSd(:,58:1080))

Else 
Call SdThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSdAhChaFu,gSdAhChiFd,gSdAhFdGlu,gSdSuChaChi,          & 
& gSdChaFdcHpm,gSdhhChaFu,gSdChaGluSu,gSdSdChacCha,gSdSdChiChi,gSdhhChiFd,               & 
& gSdHpmChiFu,gSdChiGluSd,gSdFdFdcSd,gSdFdFecSe,gSdFuFdcSu,gSdFdFvcSv,gSdHpmFdcCha,      & 
& gSdSdFdcFd,gSdFdSecFe,gSdSuFdcFu,gSdFdSvcFv,gSdFuFecSv,gSdSdFucFu,gSdFuSecFv,          & 
& gSdhhFdGlu,gSdHpmFuGlu,gSdGluGluSd,gSdSdFecFe,gSdSdFvcFv,gSdSuFecFv,epsI,              & 
& deltaM,.True.,gTSd,gPSd(:,58:1080),BRSd(:,58:1080))

End If 
 
End If 
Else 
Call SdThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSdAhChaFu,gSdAhChiFd,gSdAhFdGlu,gSdSuChaChi,          & 
& gSdChaFdcHpm,gSdhhChaFu,gSdChaGluSu,gSdSdChacCha,gSdSdChiChi,gSdhhChiFd,               & 
& gSdHpmChiFu,gSdChiGluSd,gSdFdFdcSd,gSdFdFecSe,gSdFuFdcSu,gSdFdFvcSv,gSdHpmFdcCha,      & 
& gSdSdFdcFd,gSdFdSecFe,gSdSuFdcFu,gSdFdSvcFv,gSdFuFecSv,gSdSdFucFu,gSdFuSecFv,          & 
& gSdhhFdGlu,gSdHpmFuGlu,gSdGluGluSd,gSdSdFecFe,gSdSdFvcFv,gSdSuFecFv,epsI,              & 
& deltaM,.False.,gTSd,gPSd(:,58:1080),BRSd(:,58:1080))

End If 
Do i1=1,6
gTSd(i1) =Sum(gPSd(i1,:)) 
If (gTSd(i1).Gt.0._dp) BRSd(i1,: ) =gPSd(i1,:)/gTSd(i1) 
End Do 
 

If (.Not.CTBD) Then 
If (Enable3BDecaysS) Then 
If (MaxVal(gTSu).Lt.MaxVal(fac3*Abs(MSu))) Then 
Call SuThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,gSuSuChiChi,         & 
& gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,gSuFdFvcSe,gSuhhFdcCha,    & 
& gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,gSuFuFvcSv,gSucChaFuHpm,      & 
& gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,gSuhhFuGlu,gSuGluGluSu,       & 
& gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,epsI,deltaM,.False.,        & 
& gTSu,gPSu(:,58:1080),BRSu(:,58:1080))

Else 
Call SuThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,gSuSuChiChi,         & 
& gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,gSuFdFvcSe,gSuhhFdcCha,    & 
& gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,gSuFuFvcSv,gSucChaFuHpm,      & 
& gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,gSuhhFuGlu,gSuGluGluSu,       & 
& gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,epsI,deltaM,.True.,         & 
& gTSu,gPSu(:,58:1080),BRSu(:,58:1080))

End If 
 
End If 
Else 
Call SuThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,gSuSuChiChi,         & 
& gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,gSuFdFvcSe,gSuhhFdcCha,    & 
& gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,gSuFuFvcSv,gSucChaFuHpm,      & 
& gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,gSuhhFuGlu,gSuGluGluSu,       & 
& gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,epsI,deltaM,.False.,        & 
& gTSu,gPSu(:,58:1080),BRSu(:,58:1080))

End If 
Do i1=1,6
gTSu(i1) =Sum(gPSu(i1,:)) 
If (gTSu(i1).Gt.0._dp) BRSu(i1,: ) =gPSu(i1,:)/gTSu(i1) 
End Do 
 

If (.Not.CTBD) Then 
If (Enable3BDecaysS) Then 
If (MaxVal(gTSe).Lt.MaxVal(fac3*Abs(MSe))) Then 
Call SeThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSeAhChaFv,gSeAhChiFe,gSeSvChaChi,gSeChaFecHpm,        & 
& gSeSeChacCha,gSeSeChiChi,gSehhChiFe,gSeHpmChiFv,gSeFeFdcSd,gSeFeFecSe,gSeFeFucSu,      & 
& gSeFvFecSv,gSeHpmFecCha,gSeFeSdcFd,gSeSeFecFe,gSeFeSucFu,gSeSvFecFv,gSehhChaFv,        & 
& gSeFvFdcSu,gSeFvSdcFu,gSeSeFvcFv,gSeSeFdcFd,gSeSeFucFu,gSeSvFdcFu,epsI,deltaM,         & 
& .False.,gTSe,gPSe(:,49:987),BRSe(:,49:987))

Else 
Call SeThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSeAhChaFv,gSeAhChiFe,gSeSvChaChi,gSeChaFecHpm,        & 
& gSeSeChacCha,gSeSeChiChi,gSehhChiFe,gSeHpmChiFv,gSeFeFdcSd,gSeFeFecSe,gSeFeFucSu,      & 
& gSeFvFecSv,gSeHpmFecCha,gSeFeSdcFd,gSeSeFecFe,gSeFeSucFu,gSeSvFecFv,gSehhChaFv,        & 
& gSeFvFdcSu,gSeFvSdcFu,gSeSeFvcFv,gSeSeFdcFd,gSeSeFucFu,gSeSvFdcFu,epsI,deltaM,         & 
& .True.,gTSe,gPSe(:,49:987),BRSe(:,49:987))

End If 
 
End If 
Else 
Call SeThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSeAhChaFv,gSeAhChiFe,gSeSvChaChi,gSeChaFecHpm,        & 
& gSeSeChacCha,gSeSeChiChi,gSehhChiFe,gSeHpmChiFv,gSeFeFdcSd,gSeFeFecSe,gSeFeFucSu,      & 
& gSeFvFecSv,gSeHpmFecCha,gSeFeSdcFd,gSeSeFecFe,gSeFeSucFu,gSeSvFecFv,gSehhChaFv,        & 
& gSeFvFdcSu,gSeFvSdcFu,gSeSeFvcFv,gSeSeFdcFd,gSeSeFucFu,gSeSvFdcFu,epsI,deltaM,         & 
& .False.,gTSe,gPSe(:,49:987),BRSe(:,49:987))

End If 
Do i1=1,6
gTSe(i1) =Sum(gPSe(i1,:)) 
If (gTSe(i1).Gt.0._dp) BRSe(i1,: ) =gPSe(i1,:)/gTSe(i1) 
End Do 
 

If (.Not.CTBD) Then 
If (Enable3BDecaysS) Then 
If (MaxVal(gTSv).Lt.MaxVal(fac3*Abs(MSv))) Then 
Call SvThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSvSvChiChi,gSvcHpmChiFe,gSvSeChicCha,gSvFeAhcCha,     & 
& gSvFeFucSd,gSvFeFvcSe,gSvhhFecCha,gSvFeSucFd,gSvSvFecFe,gSvFvAhChi,gSvcHpmChaFv,       & 
& gSvhhChiFv,gSvFvFdcSd,gSvFvFucSu,gSvFvFvcSv,gSvcChaFvHpm,gSvFvSdcFd,gSvSeFvcFe,        & 
& gSvFvSucFu,gSvSvFvcFv,gSvSeFucFd,gSvSvChacCha,gSvSvFdcFd,gSvSvFucFu,epsI,              & 
& deltaM,.False.,gTSv,gPSv(:,40:888),BRSv(:,40:888))

Else 
Call SvThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSvSvChiChi,gSvcHpmChiFe,gSvSeChicCha,gSvFeAhcCha,     & 
& gSvFeFucSd,gSvFeFvcSe,gSvhhFecCha,gSvFeSucFd,gSvSvFecFe,gSvFvAhChi,gSvcHpmChaFv,       & 
& gSvhhChiFv,gSvFvFdcSd,gSvFvFucSu,gSvFvFvcSv,gSvcChaFvHpm,gSvFvSdcFd,gSvSeFvcFe,        & 
& gSvFvSucFu,gSvSvFvcFv,gSvSeFucFd,gSvSvChacCha,gSvSvFdcFd,gSvSvFucFu,epsI,              & 
& deltaM,.True.,gTSv,gPSv(:,40:888),BRSv(:,40:888))

End If 
 
End If 
Else 
Call SvThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gSvSvChiChi,gSvcHpmChiFe,gSvSeChicCha,gSvFeAhcCha,     & 
& gSvFeFucSd,gSvFeFvcSe,gSvhhFecCha,gSvFeSucFd,gSvSvFecFe,gSvFvAhChi,gSvcHpmChaFv,       & 
& gSvhhChiFv,gSvFvFdcSd,gSvFvFucSu,gSvFvFvcSv,gSvcChaFvHpm,gSvFvSdcFd,gSvSeFvcFe,        & 
& gSvFvSucFu,gSvSvFvcFv,gSvSeFucFd,gSvSvChacCha,gSvSvFdcFd,gSvSvFucFu,epsI,              & 
& deltaM,.False.,gTSv,gPSv(:,40:888),BRSv(:,40:888))

End If 
Do i1=1,3
gTSv(i1) =Sum(gPSv(i1,:)) 
If (gTSv(i1).Gt.0._dp) BRSv(i1,: ) =gPSv(i1,:)/gTSv(i1) 
End Do 
 

! No 3-body decays for hh  
! No 3-body decays for Ah  
! No 3-body decays for Hpm  
If (.Not.CTBD) Then 
If (Enable3BDecaysF) Then 
If (gTGlu.Lt.fac3*Abs(MGlu)) Then 
Call GluThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTSd,gTSu,gGluFdcFdChi,gGluFdcFucCha,gGluFucFuChi,     & 
& epsI,deltaM,.False.,gTGlu,gPGlu(:,37:126),BRGlu(:,37:126))

Else 
Call GluThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTSd,gTSu,gGluFdcFdChi,gGluFdcFucCha,gGluFucFuChi,     & 
& epsI,deltaM,.True.,gTGlu,gPGlu(:,37:126),BRGlu(:,37:126))

End If 
 
End If 
Else 
Call GluThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTSd,gTSu,gGluFdcFdChi,gGluFdcFucCha,gGluFucFuChi,     & 
& epsI,deltaM,.False.,gTGlu,gPGlu(:,37:126),BRGlu(:,37:126))

End If 
Do i1=1,1
gTGlu =Sum(gPGlu(i1,:)) 
If (gTGlu.Gt.0._dp) BRGlu(i1,: ) =gPGlu(i1,:)/gTGlu 
End Do 
 

If (.Not.CTBD) Then 
If (Enable3BDecaysF) Then 
If (MaxVal(gTChi).Lt.MaxVal(fac3*Abs(MChi))) Then 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,gTVWm,             & 
& gTVZ,gChiChicChaCha,gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,              & 
& gChiChacFdFu,gChiChacFeFv,gChiChicFvFv,gChiFdcFdGlu,gChiFucFuGlu,epsI,deltaM,          & 
& .False.,gTChi,gPChi(:,84:361),BRChi(:,84:361))

Else 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,gTVWm,             & 
& gTVZ,gChiChicChaCha,gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,              & 
& gChiChacFdFu,gChiChacFeFv,gChiChicFvFv,gChiFdcFdGlu,gChiFucFuGlu,epsI,deltaM,          & 
& .True.,gTChi,gPChi(:,84:361),BRChi(:,84:361))

End If 
 
End If 
Else 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,gTVWm,             & 
& gTVZ,gChiChicChaCha,gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,              & 
& gChiChacFdFu,gChiChacFeFv,gChiChicFvFv,gChiFdcFdGlu,gChiFucFuGlu,epsI,deltaM,          & 
& .False.,gTChi,gPChi(:,84:361),BRChi(:,84:361))

End If 
Do i1=1,4
gTChi(i1) =Sum(gPChi(i1,:)) 
If (gTChi(i1).Gt.0._dp) BRChi(i1,: ) =gPChi(i1,:)/gTChi(i1) 
End Do 
 

If (.Not.CTBD) Then 
If (Enable3BDecaysF) Then 
If (MaxVal(gTCha).Lt.MaxVal(fac3*Abs(MCha))) Then 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,gTVWm,             & 
& gTVZ,gChaChacChaCha,gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,              & 
& gChaChacFvFv,gChaChicFuFd,gChaChicFvFe,gChaFdcFuGlu,epsI,deltaM,.False.,               & 
& gTCha,gPCha(:,80:272),BRCha(:,80:272))

Else 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,gTVWm,             & 
& gTVZ,gChaChacChaCha,gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,              & 
& gChaChacFvFv,gChaChicFuFd,gChaChicFvFe,gChaFdcFuGlu,epsI,deltaM,.True.,gTCha,          & 
& gPCha(:,80:272),BRCha(:,80:272))

End If 
 
End If 
Else 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,gTVWm,             & 
& gTVZ,gChaChacChaCha,gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,              & 
& gChaChacFvFv,gChaChicFuFd,gChaChicFvFe,gChaFdcFuGlu,epsI,deltaM,.False.,               & 
& gTCha,gPCha(:,80:272),BRCha(:,80:272))

End If 
Do i1=1,2
gTCha(i1) =Sum(gPCha(i1,:)) 
If (gTCha(i1).Gt.0._dp) BRCha(i1,: ) =gPCha(i1,:)/gTCha(i1) 
End Do 
 

! No 3-body decays for Fu  
Iname = Iname - 1 
 
End Subroutine CalculateBR 
End Module BranchingRatios_MSSM 
 