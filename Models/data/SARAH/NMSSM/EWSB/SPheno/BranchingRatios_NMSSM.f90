! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:27 on 24.9.2018   
! ----------------------------------------------------------------------  
 
 
Module BranchingRatios_NMSSM 
 
Use Control 
Use Settings 
Use Couplings_NMSSM 
Use Model_Data_NMSSM 
Use LoopCouplings_NMSSM 
Use Glu3Decays_NMSSM 
Use Chi3Decays_NMSSM 
Use Cha3Decays_NMSSM 
Use Sd3Decays_NMSSM 
Use Su3Decays_NMSSM 
Use Se3Decays_NMSSM 
Use Sv3Decays_NMSSM 
Use TreeLevelDecays_NMSSM 
Use OneLoopDecays_NMSSM


 Contains 
 
Subroutine CalculateBR(CTBD,fac3,epsI,deltaM,kont,MAh,MAh2,MCha,MCha2,MChi,           & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,            & 
& ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,             & 
& kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gPSd,               & 
& gTSd,BRSd,gPSu,gTSu,BRSu,gPSe,gTSe,BRSe,gPSv,gTSv,BRSv,gPhh,gThh,BRhh,gPAh,            & 
& gTAh,BRAh,gPHpm,gTHpm,BRHpm,gPGlu,gTGlu,BRGlu,gPChi,gTChi,BRChi,gPCha,gTCha,           & 
& BRCha,gPFu,gTFu,BRFu)

Real(dp), Intent(in) :: epsI, deltaM, fac3 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: CTBD 
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp),Intent(inout) :: vd,vu,vS

Real(dp),Intent(inout) :: gPSd(6,1245),gTSd(6),BRSd(6,1245),gPSu(6,1245),gTSu(6),BRSu(6,1245),gPSe(6,1128),     & 
& gTSe(6),BRSe(6,1128),gPSv(3,1002),gTSv(3),BRSv(3,1002),gPhh(3,209),gThh(3),            & 
& BRhh(3,209),gPAh(3,207),gTAh(3),BRAh(3,207),gPHpm(2,96),gTHpm(2),BRHpm(2,96),          & 
& gPGlu(1,157),gTGlu,BRGlu(1,157),gPChi(5,482),gTChi(5),BRChi(5,482),gPCha(2,316),       & 
& gTCha(2),BRCha(2,316),gPFu(3,78),gTFu(3),BRFu(3,78)

Complex(dp) :: cplHiggsPP(3),cplHiggsGG(3),cplPseudoHiggsPP(3),cplPseudoHiggsGG(3),cplHiggsZZvirt(3),& 
& cplHiggsWWvirt(3)

Real(dp) :: gGluFdcFdChi(1,3,3,5),gGluFdcFucCha(1,3,3,2),gGluFucFuChi(1,3,3,5),gChiChicChaCha(5,5,2,2),& 
& gChiChiChiChi(5,5,5,5),gChiChicFdFd(5,5,3,3),gChiChicFeFe(5,5,3,3),gChiChicFuFu(5,5,3,3),& 
& gChiChacFdFu(5,2,3,3),gChiChacFeFv(5,2,3,3),gChiChicFvFv(5,5,3,3),gChiFdcFdGlu(5,3,3,1),& 
& gChiFucFuGlu(5,3,3,1),gChaChacChaCha(2,2,2,2),gChaChaChiChi(2,2,5,5),gChaChacFdFd(2,2,3,3),& 
& gChaChacFeFe(2,2,3,3),gChaChacFuFu(2,2,3,3),gChaChacFvFv(2,2,3,3),gChaChicFuFd(2,5,3,3),& 
& gChaChicFvFe(2,5,3,3),gChaFdcFuGlu(2,3,3,1),gSdAhChaFu(6,3,2,3),gSdAhChiFd(6,3,5,3),   & 
& gSdAhFdGlu(6,3,3,1),gSdSuChaChi(6,6,2,5),gSdChaFdcHpm(6,2,3,2),gSdhhChaFu(6,3,2,3),    & 
& gSdChaGluSu(6,2,1,6),gSdSdChacCha(6,6,2,2),gSdSdChiChi(6,6,5,5),gSdhhChiFd(6,3,5,3),   & 
& gSdHpmChiFu(6,2,5,3),gSdChiGluSd(6,5,1,6),gSdFdFdcSd(6,3,3,6),gSdFdFecSe(6,3,3,6),     & 
& gSdFuFdcSu(6,3,3,6),gSdFdFvcSv(6,3,3,3),gSdHpmFdcCha(6,2,3,2),gSdSdFdcFd(6,6,3,3),     & 
& gSdFdSecFe(6,3,6,3),gSdSuFdcFu(6,6,3,3),gSdFdSvcFv(6,3,3,3),gSdFuFecSv(6,3,3,3),       & 
& gSdSdFucFu(6,6,3,3),gSdFuSecFv(6,3,6,3),gSdhhFdGlu(6,3,3,1),gSdHpmFuGlu(6,2,3,1),      & 
& gSdGluGluSd(6,1,1,6),gSdSdFecFe(6,6,3,3),gSdSdFvcFv(6,6,3,3),gSdSuFecFv(6,6,3,3),      & 
& gSuAhChiFu(6,3,5,3),gSuAhFdcCha(6,3,3,2),gSuAhFuGlu(6,3,3,1),gSuSuChiChi(6,6,5,5),     & 
& gSucHpmChiFd(6,2,5,3),gSuhhChiFu(6,3,5,3),gSuChiGluSu(6,5,1,6),gSuSdChicCha(6,6,5,2),  & 
& gSuFdFucSd(6,3,3,6),gSuFdFvcSe(6,3,3,6),gSuhhFdcCha(6,3,3,2),gSuSuFdcFd(6,6,3,3),      & 
& gSuFdSvcFe(6,3,3,3),gSucHpmChaFu(6,2,2,3),gSuFuFecSe(6,3,3,6),gSuFuFucSu(6,3,3,6),     & 
& gSuFuFvcSv(6,3,3,3),gSucChaFuHpm(6,2,3,2),gSuSdFucFd(6,6,3,3),gSuFuSecFe(6,3,6,3),     & 
& gSuSuFucFu(6,6,3,3),gSuFuSvcFv(6,3,3,3),gSucHpmFdGlu(6,2,3,1),gSuhhFuGlu(6,3,3,1),     & 
& gSuGluGluSu(6,1,1,6),gSuGluSdcCha(6,1,6,2),gSuSdFvcFe(6,6,3,3),gSuSuChacCha(6,6,2,2),  & 
& gSuSuFecFe(6,6,3,3),gSuSuFvcFv(6,6,3,3),gSeAhChaFv(6,3,2,3),gSeAhChiFe(6,3,5,3),       & 
& gSeSvChaChi(6,3,2,5),gSeChaFecHpm(6,2,3,2),gSeSeChacCha(6,6,2,2),gSeSeChiChi(6,6,5,5), & 
& gSehhChiFe(6,3,5,3),gSeHpmChiFv(6,2,5,3),gSeFeFdcSd(6,3,3,6),gSeFeFecSe(6,3,3,6),      & 
& gSeFeFucSu(6,3,3,6),gSeFvFecSv(6,3,3,3),gSeHpmFecCha(6,2,3,2),gSeFeSdcFd(6,3,6,3),     & 
& gSeSeFecFe(6,6,3,3),gSeFeSucFu(6,3,6,3),gSeSvFecFv(6,3,3,3),gSehhChaFv(6,3,2,3),       & 
& gSeFvFdcSu(6,3,3,6),gSeFvSdcFu(6,3,6,3),gSeSeFvcFv(6,6,3,3),gSeSeFdcFd(6,6,3,3),       & 
& gSeSeFucFu(6,6,3,3),gSeSvFdcFu(6,3,3,3),gSvSvChiChi(3,3,5,5),gSvcHpmChiFe(3,2,5,3),    & 
& gSvSeChicCha(3,6,5,2),gSvFeAhcCha(3,3,3,2),gSvFeFucSd(3,3,3,6),gSvFeFvcSe(3,3,3,6),    & 
& gSvhhFecCha(3,3,3,2),gSvFeSucFd(3,3,6,3),gSvSvFecFe(3,3,3,3),gSvFvAhChi(3,3,3,5),      & 
& gSvcHpmChaFv(3,2,2,3),gSvhhChiFv(3,3,5,3),gSvFvFdcSd(3,3,3,6),gSvFvFucSu(3,3,3,6),     & 
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
! One-Loop Decays 
If (OneLoopDecays) Then 
Call CalculateOneLoopDecays(gP1LSd,gP1LSu,gP1LSe,gP1LSv,gP1Lhh,gP1LAh,gP1LHpm,        & 
& gP1LGlu,gP1LChi,gP1LCha,gP1LFu,MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,           & 
& MAh,MAh2,MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,             & 
& MGlu2,MVZ,MVZ2,MVWm,MVWm2,ZD,ZV,ZU,ZE,ZH,ZA,ZP,ZN,UM,UP,ZEL,ZER,ZDL,ZDR,               & 
& ZUL,ZUR,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,epsI,deltaM,kont)

End if 


gPSd = 0._dp 
gTSd = 0._dp 
BRSd = 0._dp 
Call SdTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPSd(:,1:84),gTSd,BRSd(:,1:84))

Do i1=1,6
gTSd(i1) =Sum(gPSd(i1,:)) 
If (gTSd(i1).Gt.0._dp) BRSd(i1,: ) =gPSd(i1,:)/gTSd(i1) 
If (OneLoopDecays) Then 
gT1LSd(i1) =Sum(gP1LSd(i1,:)) 
If (gT1LSd(i1).Gt.0._dp) BR1LSd(i1,: ) =gP1LSd(i1,:)/gT1LSd(i1) 
End if
End Do 
 

gPSu = 0._dp 
gTSu = 0._dp 
BRSu = 0._dp 
Call SuTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPSu(:,1:84),gTSu,BRSu(:,1:84))

Do i1=1,6
gTSu(i1) =Sum(gPSu(i1,:)) 
If (gTSu(i1).Gt.0._dp) BRSu(i1,: ) =gPSu(i1,:)/gTSu(i1) 
If (OneLoopDecays) Then 
gT1LSu(i1) =Sum(gP1LSu(i1,:)) 
If (gT1LSu(i1).Gt.0._dp) BR1LSu(i1,: ) =gP1LSu(i1,:)/gT1LSu(i1) 
End if
End Do 
 

gPSe = 0._dp 
gTSe = 0._dp 
BRSe = 0._dp 
Call SeTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPSe(:,1:69),gTSe,BRSe(:,1:69))

Do i1=1,6
gTSe(i1) =Sum(gPSe(i1,:)) 
If (gTSe(i1).Gt.0._dp) BRSe(i1,: ) =gPSe(i1,:)/gTSe(i1) 
If (OneLoopDecays) Then 
gT1LSe(i1) =Sum(gP1LSe(i1,:)) 
If (gT1LSe(i1).Gt.0._dp) BR1LSe(i1,: ) =gP1LSe(i1,:)/gT1LSe(i1) 
End if
End Do 
 

gPSv = 0._dp 
gTSv = 0._dp 
BRSv = 0._dp 
Call SvTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPSv(:,1:54),gTSv,BRSv(:,1:54))

Do i1=1,3
gTSv(i1) =Sum(gPSv(i1,:)) 
If (gTSv(i1).Gt.0._dp) BRSv(i1,: ) =gPSv(i1,:)/gTSv(i1) 
If (OneLoopDecays) Then 
gT1LSv(i1) =Sum(gP1LSv(i1,:)) 
If (gT1LSv(i1).Gt.0._dp) BR1LSv(i1,: ) =gP1LSv(i1,:)/gT1LSv(i1) 
End if
End Do 
 

gPhh = 0._dp 
gThh = 0._dp 
BRhh = 0._dp 
Call hhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPhh,gThh,BRhh)

Do i1=1,3
gThh(i1) =Sum(gPhh(i1,:)) 
If (gThh(i1).Gt.0._dp) BRhh(i1,: ) =gPhh(i1,:)/gThh(i1) 
If (OneLoopDecays) Then 
gT1Lhh(i1) =Sum(gP1Lhh(i1,:)) 
If (gT1Lhh(i1).Gt.0._dp) BR1Lhh(i1,: ) =gP1Lhh(i1,:)/gT1Lhh(i1) 
End if
End Do 
 

gPAh = 0._dp 
gTAh = 0._dp 
BRAh = 0._dp 
Call AhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPAh,gTAh,BRAh)

Do i1=1,3
gTAh(i1) =Sum(gPAh(i1,:)) 
If (gTAh(i1).Gt.0._dp) BRAh(i1,: ) =gPAh(i1,:)/gTAh(i1) 
If (OneLoopDecays) Then 
gT1LAh(i1) =Sum(gP1LAh(i1,:)) 
If (gT1LAh(i1).Gt.0._dp) BR1LAh(i1,: ) =gP1LAh(i1,:)/gT1LAh(i1) 
End if
End Do 
 

! Set Goldstone Widhts 
gTAh(1)=gTVZ


gPHpm = 0._dp 
gTHpm = 0._dp 
BRHpm = 0._dp 
Call HpmTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPHpm,gTHpm,BRHpm)

Do i1=1,2
gTHpm(i1) =Sum(gPHpm(i1,:)) 
If (gTHpm(i1).Gt.0._dp) BRHpm(i1,: ) =gPHpm(i1,:)/gTHpm(i1) 
If (OneLoopDecays) Then 
gT1LHpm(i1) =Sum(gP1LHpm(i1,:)) 
If (gT1LHpm(i1).Gt.0._dp) BR1LHpm(i1,: ) =gP1LHpm(i1,:)/gT1LHpm(i1) 
End if
End Do 
 

! Set Goldstone Widhts 
gTHpm(1)=gTVWm


gPGlu = 0._dp 
gTGlu = 0._dp 
BRGlu = 0._dp 
Call GluTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPGlu(:,1:49),gTGlu,               & 
& BRGlu(:,1:49))

Do i1=1,1
gTGlu =Sum(gPGlu(i1,:)) 
If (gTGlu.Gt.0._dp) BRGlu(i1,: ) =gPGlu(i1,:)/gTGlu 
If (OneLoopDecays) Then 
gT1LGlu =Sum(gP1LGlu(i1,:)) 
If (gT1LGlu.Gt.0._dp) BR1LGlu(i1,: ) =gP1LGlu(i1,:)/gT1LGlu 
End if
End Do 
 

gPChi = 0._dp 
gTChi = 0._dp 
BRChi = 0._dp 
Call ChiTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPChi(:,1:103),gTChi,              & 
& BRChi(:,1:103))

Do i1=1,5
gTChi(i1) =Sum(gPChi(i1,:)) 
If (gTChi(i1).Gt.0._dp) BRChi(i1,: ) =gPChi(i1,:)/gTChi(i1) 
If (OneLoopDecays) Then 
gT1LChi(i1) =Sum(gP1LChi(i1,:)) 
If (gT1LChi(i1).Gt.0._dp) BR1LChi(i1,: ) =gP1LChi(i1,:)/gT1LChi(i1) 
End if
End Do 
 

gPCha = 0._dp 
gTCha = 0._dp 
BRCha = 0._dp 
Call ChaTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPCha(:,1:87),gTCha,               & 
& BRCha(:,1:87))

Do i1=1,2
gTCha(i1) =Sum(gPCha(i1,:)) 
If (gTCha(i1).Gt.0._dp) BRCha(i1,: ) =gPCha(i1,:)/gTCha(i1) 
If (OneLoopDecays) Then 
gT1LCha(i1) =Sum(gP1LCha(i1,:)) 
If (gT1LCha(i1).Gt.0._dp) BR1LCha(i1,: ) =gP1LCha(i1,:)/gT1LCha(i1) 
End if
End Do 
 

gPFu = 0._dp 
gTFu = 0._dp 
BRFu = 0._dp 
Call FuTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,               & 
& MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,             & 
& ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,               & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPFu,gTFu,BRFu)

Do i1=1,3
gTFu(i1) =Sum(gPFu(i1,:)) 
If (gTFu(i1).Gt.0._dp) BRFu(i1,: ) =gPFu(i1,:)/gTFu(i1) 
If (OneLoopDecays) Then 
gT1LFu(i1) =Sum(gP1LFu(i1,:)) 
If (gT1LFu(i1).Gt.0._dp) BR1LFu(i1,: ) =gP1LFu(i1,:)/gT1LFu(i1) 
End if
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysS).and.(Calc3BodyDecay_Sd)) Then 
If (MaxVal(gTSd).Lt.MaxVal(fac3*Abs(MSd))) Then 
Call SdThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSdAhChaFu,gSdAhChiFd,gSdAhFdGlu,               & 
& gSdSuChaChi,gSdChaFdcHpm,gSdhhChaFu,gSdChaGluSu,gSdSdChacCha,gSdSdChiChi,              & 
& gSdhhChiFd,gSdHpmChiFu,gSdChiGluSd,gSdFdFdcSd,gSdFdFecSe,gSdFuFdcSu,gSdFdFvcSv,        & 
& gSdHpmFdcCha,gSdSdFdcFd,gSdFdSecFe,gSdSuFdcFu,gSdFdSvcFv,gSdFuFecSv,gSdSdFucFu,        & 
& gSdFuSecFv,gSdhhFdGlu,gSdHpmFuGlu,gSdGluGluSd,gSdSdFecFe,gSdSdFvcFv,gSdSuFecFv,        & 
& epsI,deltaM,.False.,gTSd,gPSd(:,85:1245),BRSd(:,85:1245))

Else 
Call SdThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSdAhChaFu,gSdAhChiFd,gSdAhFdGlu,               & 
& gSdSuChaChi,gSdChaFdcHpm,gSdhhChaFu,gSdChaGluSu,gSdSdChacCha,gSdSdChiChi,              & 
& gSdhhChiFd,gSdHpmChiFu,gSdChiGluSd,gSdFdFdcSd,gSdFdFecSe,gSdFuFdcSu,gSdFdFvcSv,        & 
& gSdHpmFdcCha,gSdSdFdcFd,gSdFdSecFe,gSdSuFdcFu,gSdFdSvcFv,gSdFuFecSv,gSdSdFucFu,        & 
& gSdFuSecFv,gSdhhFdGlu,gSdHpmFuGlu,gSdGluGluSd,gSdSdFecFe,gSdSdFvcFv,gSdSuFecFv,        & 
& epsI,deltaM,.True.,gTSd,gPSd(:,85:1245),BRSd(:,85:1245))

End If 
 
End If 
Else 
Call SdThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSdAhChaFu,gSdAhChiFd,gSdAhFdGlu,               & 
& gSdSuChaChi,gSdChaFdcHpm,gSdhhChaFu,gSdChaGluSu,gSdSdChacCha,gSdSdChiChi,              & 
& gSdhhChiFd,gSdHpmChiFu,gSdChiGluSd,gSdFdFdcSd,gSdFdFecSe,gSdFuFdcSu,gSdFdFvcSv,        & 
& gSdHpmFdcCha,gSdSdFdcFd,gSdFdSecFe,gSdSuFdcFu,gSdFdSvcFv,gSdFuFecSv,gSdSdFucFu,        & 
& gSdFuSecFv,gSdhhFdGlu,gSdHpmFuGlu,gSdGluGluSd,gSdSdFecFe,gSdSdFvcFv,gSdSuFecFv,        & 
& epsI,deltaM,.False.,gTSd,gPSd(:,85:1245),BRSd(:,85:1245))

End If 
Do i1=1,6
gTSd(i1) =Sum(gPSd(i1,:)) 
If (gTSd(i1).Gt.0._dp) BRSd(i1,: ) =gPSd(i1,:)/gTSd(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysS).and.(Calc3BodyDecay_Su)) Then 
If (MaxVal(gTSu).Lt.MaxVal(fac3*Abs(MSu))) Then 
Call SuThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,              & 
& gSuSuChiChi,gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,               & 
& gSuFdFvcSe,gSuhhFdcCha,gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,       & 
& gSuFuFvcSv,gSucChaFuHpm,gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,      & 
& gSuhhFuGlu,gSuGluGluSu,gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,     & 
& epsI,deltaM,.False.,gTSu,gPSu(:,85:1245),BRSu(:,85:1245))

Else 
Call SuThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,              & 
& gSuSuChiChi,gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,               & 
& gSuFdFvcSe,gSuhhFdcCha,gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,       & 
& gSuFuFvcSv,gSucChaFuHpm,gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,      & 
& gSuhhFuGlu,gSuGluGluSu,gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,     & 
& epsI,deltaM,.True.,gTSu,gPSu(:,85:1245),BRSu(:,85:1245))

End If 
 
End If 
Else 
Call SuThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSuAhChiFu,gSuAhFdcCha,gSuAhFuGlu,              & 
& gSuSuChiChi,gSucHpmChiFd,gSuhhChiFu,gSuChiGluSu,gSuSdChicCha,gSuFdFucSd,               & 
& gSuFdFvcSe,gSuhhFdcCha,gSuSuFdcFd,gSuFdSvcFe,gSucHpmChaFu,gSuFuFecSe,gSuFuFucSu,       & 
& gSuFuFvcSv,gSucChaFuHpm,gSuSdFucFd,gSuFuSecFe,gSuSuFucFu,gSuFuSvcFv,gSucHpmFdGlu,      & 
& gSuhhFuGlu,gSuGluGluSu,gSuGluSdcCha,gSuSdFvcFe,gSuSuChacCha,gSuSuFecFe,gSuSuFvcFv,     & 
& epsI,deltaM,.False.,gTSu,gPSu(:,85:1245),BRSu(:,85:1245))

End If 
Do i1=1,6
gTSu(i1) =Sum(gPSu(i1,:)) 
If (gTSu(i1).Gt.0._dp) BRSu(i1,: ) =gPSu(i1,:)/gTSu(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysS).and.(Calc3BodyDecay_Se)) Then 
If (MaxVal(gTSe).Lt.MaxVal(fac3*Abs(MSe))) Then 
Call SeThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSeAhChaFv,gSeAhChiFe,gSeSvChaChi,              & 
& gSeChaFecHpm,gSeSeChacCha,gSeSeChiChi,gSehhChiFe,gSeHpmChiFv,gSeFeFdcSd,               & 
& gSeFeFecSe,gSeFeFucSu,gSeFvFecSv,gSeHpmFecCha,gSeFeSdcFd,gSeSeFecFe,gSeFeSucFu,        & 
& gSeSvFecFv,gSehhChaFv,gSeFvFdcSu,gSeFvSdcFu,gSeSeFvcFv,gSeSeFdcFd,gSeSeFucFu,          & 
& gSeSvFdcFu,epsI,deltaM,.False.,gTSe,gPSe(:,70:1128),BRSe(:,70:1128))

Else 
Call SeThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSeAhChaFv,gSeAhChiFe,gSeSvChaChi,              & 
& gSeChaFecHpm,gSeSeChacCha,gSeSeChiChi,gSehhChiFe,gSeHpmChiFv,gSeFeFdcSd,               & 
& gSeFeFecSe,gSeFeFucSu,gSeFvFecSv,gSeHpmFecCha,gSeFeSdcFd,gSeSeFecFe,gSeFeSucFu,        & 
& gSeSvFecFv,gSehhChaFv,gSeFvFdcSu,gSeFvSdcFu,gSeSeFvcFv,gSeSeFdcFd,gSeSeFucFu,          & 
& gSeSvFdcFu,epsI,deltaM,.True.,gTSe,gPSe(:,70:1128),BRSe(:,70:1128))

End If 
 
End If 
Else 
Call SeThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSeAhChaFv,gSeAhChiFe,gSeSvChaChi,              & 
& gSeChaFecHpm,gSeSeChacCha,gSeSeChiChi,gSehhChiFe,gSeHpmChiFv,gSeFeFdcSd,               & 
& gSeFeFecSe,gSeFeFucSu,gSeFvFecSv,gSeHpmFecCha,gSeFeSdcFd,gSeSeFecFe,gSeFeSucFu,        & 
& gSeSvFecFv,gSehhChaFv,gSeFvFdcSu,gSeFvSdcFu,gSeSeFvcFv,gSeSeFdcFd,gSeSeFucFu,          & 
& gSeSvFdcFu,epsI,deltaM,.False.,gTSe,gPSe(:,70:1128),BRSe(:,70:1128))

End If 
Do i1=1,6
gTSe(i1) =Sum(gPSe(i1,:)) 
If (gTSe(i1).Gt.0._dp) BRSe(i1,: ) =gPSe(i1,:)/gTSe(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysS).and.(Calc3BodyDecay_Sv)) Then 
If (MaxVal(gTSv).Lt.MaxVal(fac3*Abs(MSv))) Then 
Call SvThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSvSvChiChi,gSvcHpmChiFe,gSvSeChicCha,          & 
& gSvFeAhcCha,gSvFeFucSd,gSvFeFvcSe,gSvhhFecCha,gSvFeSucFd,gSvSvFecFe,gSvFvAhChi,        & 
& gSvcHpmChaFv,gSvhhChiFv,gSvFvFdcSd,gSvFvFucSu,gSvFvFvcSv,gSvcChaFvHpm,gSvFvSdcFd,      & 
& gSvSeFvcFe,gSvFvSucFu,gSvSvFvcFv,gSvSeFucFd,gSvSvChacCha,gSvSvFdcFd,gSvSvFucFu,        & 
& epsI,deltaM,.False.,gTSv,gPSv(:,55:1002),BRSv(:,55:1002))

Else 
Call SvThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSvSvChiChi,gSvcHpmChiFe,gSvSeChicCha,          & 
& gSvFeAhcCha,gSvFeFucSd,gSvFeFvcSe,gSvhhFecCha,gSvFeSucFd,gSvSvFecFe,gSvFvAhChi,        & 
& gSvcHpmChaFv,gSvhhChiFv,gSvFvFdcSd,gSvFvFucSu,gSvFvFvcSv,gSvcChaFvHpm,gSvFvSdcFd,      & 
& gSvSeFvcFe,gSvFvSucFu,gSvSvFvcFv,gSvSeFucFd,gSvSvChacCha,gSvSvFdcFd,gSvSvFucFu,        & 
& epsI,deltaM,.True.,gTSv,gPSv(:,55:1002),BRSv(:,55:1002))

End If 
 
End If 
Else 
Call SvThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gSvSvChiChi,gSvcHpmChiFe,gSvSeChicCha,          & 
& gSvFeAhcCha,gSvFeFucSd,gSvFeFvcSe,gSvhhFecCha,gSvFeSucFd,gSvSvFecFe,gSvFvAhChi,        & 
& gSvcHpmChaFv,gSvhhChiFv,gSvFvFdcSd,gSvFvFucSu,gSvFvFvcSv,gSvcChaFvHpm,gSvFvSdcFd,      & 
& gSvSeFvcFe,gSvFvSucFu,gSvSvFvcFv,gSvSeFucFd,gSvSvChacCha,gSvSvFdcFd,gSvSvFucFu,        & 
& epsI,deltaM,.False.,gTSv,gPSv(:,55:1002),BRSv(:,55:1002))

End If 
Do i1=1,3
gTSv(i1) =Sum(gPSv(i1,:)) 
If (gTSv(i1).Gt.0._dp) BRSv(i1,: ) =gPSv(i1,:)/gTSv(i1) 
End Do 
 

! No 3-body decays for hh  
! No 3-body decays for Ah  
! No 3-body decays for Hpm  
If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Glu)) Then 
If (gTGlu.Lt.fac3*Abs(MGlu)) Then 
Call GluThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTSd,gTSu,gGluFdcFdChi,gGluFdcFucCha,           & 
& gGluFucFuChi,epsI,deltaM,.False.,gTGlu,gPGlu(:,50:157),BRGlu(:,50:157))

Else 
Call GluThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTSd,gTSu,gGluFdcFdChi,gGluFdcFucCha,           & 
& gGluFucFuChi,epsI,deltaM,.True.,gTGlu,gPGlu(:,50:157),BRGlu(:,50:157))

End If 
 
End If 
Else 
Call GluThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTSd,gTSu,gGluFdcFdChi,gGluFdcFucCha,           & 
& gGluFucFuChi,epsI,deltaM,.False.,gTGlu,gPGlu(:,50:157),BRGlu(:,50:157))

End If 
Do i1=1,1
gTGlu =Sum(gPGlu(i1,:)) 
If (gTGlu.Gt.0._dp) BRGlu(i1,: ) =gPGlu(i1,:)/gTGlu 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Chi)) Then 
If (MaxVal(gTChi).Lt.MaxVal(fac3*Abs(MChi))) Then 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,            & 
& gTVWm,gTVZ,gChiChicChaCha,gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,        & 
& gChiChacFdFu,gChiChacFeFv,gChiChicFvFv,gChiFdcFdGlu,gChiFucFuGlu,epsI,deltaM,          & 
& .False.,gTChi,gPChi(:,104:482),BRChi(:,104:482))

Else 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,            & 
& gTVWm,gTVZ,gChiChicChaCha,gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,        & 
& gChiChacFdFu,gChiChacFeFv,gChiChicFvFv,gChiFdcFdGlu,gChiFucFuGlu,epsI,deltaM,          & 
& .True.,gTChi,gPChi(:,104:482),BRChi(:,104:482))

End If 
 
End If 
Else 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,            & 
& gTVWm,gTVZ,gChiChicChaCha,gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,        & 
& gChiChacFdFu,gChiChacFeFv,gChiChicFvFv,gChiFdcFdGlu,gChiFucFuGlu,epsI,deltaM,          & 
& .False.,gTChi,gPChi(:,104:482),BRChi(:,104:482))

End If 
Do i1=1,5
gTChi(i1) =Sum(gPChi(i1,:)) 
If (gTChi(i1).Gt.0._dp) BRChi(i1,: ) =gPChi(i1,:)/gTChi(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Cha)) Then 
If (MaxVal(gTCha).Lt.MaxVal(fac3*Abs(MCha))) Then 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,            & 
& gTVWm,gTVZ,gChaChacChaCha,gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,        & 
& gChaChacFvFv,gChaChicFuFd,gChaChicFvFe,gChaFdcFuGlu,epsI,deltaM,.False.,               & 
& gTCha,gPCha(:,88:316),BRCha(:,88:316))

Else 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,            & 
& gTVWm,gTVZ,gChaChacChaCha,gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,        & 
& gChaChacFvFv,gChaChicFuFd,gChaChicFvFe,gChaFdcFuGlu,epsI,deltaM,.True.,gTCha,          & 
& gPCha(:,88:316),BRCha(:,88:316))

End If 
 
End If 
Else 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTSd,gTSe,gTSu,gTSv,            & 
& gTVWm,gTVZ,gChaChacChaCha,gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,        & 
& gChaChacFvFv,gChaChicFuFd,gChaChicFvFe,gChaFdcFuGlu,epsI,deltaM,.False.,               & 
& gTCha,gPCha(:,88:316),BRCha(:,88:316))

End If 
Do i1=1,2
gTCha(i1) =Sum(gPCha(i1,:)) 
If (gTCha(i1).Gt.0._dp) BRCha(i1,: ) =gPCha(i1,:)/gTCha(i1) 
End Do 
 

! No 3-body decays for Fu  
Iname = Iname - 1 
 
End Subroutine CalculateBR 
End Module BranchingRatios_NMSSM 
 