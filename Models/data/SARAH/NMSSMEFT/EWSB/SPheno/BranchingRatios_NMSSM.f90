! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.9.3 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 14:16 on 19.10.2018   
! ----------------------------------------------------------------------  
 
 
Module BranchingRatios_NMSSM 
 
Use Control 
Use Couplings_NMSSM 
Use Model_Data_NMSSM 
Use LoopCouplings_NMSSM 
Use Chi3Decays_NMSSM 
Use Cha3Decays_NMSSM 
Use TreeLevelDecays_NMSSM 


 Contains 
 
Subroutine CalculateBR(CTBD,fac3,epsI,deltaM,kont,MAh,MAh2,MCha,MCha2,MChi,           & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,            & 
& MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,              & 
& ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,              & 
& Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gPhh,gThh,BRhh,               & 
& gPAh,gTAh,BRAh,gPHpm,gTHpm,BRHpm,gPChi,gTChi,BRChi,gPCha,gTCha,BRCha,gPFu,             & 
& gTFu,BRFu)

Real(dp), Intent(in) :: epsI, deltaM, fac3 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: CTBD 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(1),MSd2(1),MSe(1),          & 
& MSe2(1),MSu(1),MSu2(1),MSv(1),MSv2(1),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(3,3),ZH(3,3),        & 
& ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: pG,UM(2,2),UP(2,2),ZD(1,1),ZDL(3,3),ZDR(3,3),ZE(1,1),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(1,1),ZUL(3,3),ZUR(3,3),ZV(1,1),ZW(2,2)

Real(dp),Intent(in) :: vd,vu,vS

Real(dp),Intent(inout) :: gPhh(3,71),gThh(3),BRhh(3,71),gPAh(3,68),gTAh(3),BRAh(3,68),gPHpm(2,40),              & 
& gTHpm(2),BRHpm(2,40),gPChi(5,395),gTChi(5),BRChi(5,395),gPCha(2,242),gTCha(2),         & 
& BRCha(2,242),gPFu(3,24),gTFu(3),BRFu(3,24)

Complex(dp) :: cplHiggsPP(3),cplHiggsGG(3),cplPseudoHiggsPP(3),cplPseudoHiggsGG(3),cplHiggsZZvirt(3),& 
& cplHiggsWWvirt(3)

Real(dp) :: gChiChicChaCha(5,5,2,2),gChiChiChiChi(5,5,5,5),gChiChicFdFd(5,5,3,3),gChiChicFeFe(5,5,3,3),& 
& gChiChicFuFu(5,5,3,3),gChiChacFdFu(5,2,3,3),gChiChacFeFv(5,2,3,3),gChiChicFvFv(5,5,3,3),& 
& gChaChacChaCha(2,2,2,2),gChaChaChiChi(2,2,5,5),gChaChacFdFd(2,2,3,3),gChaChacFeFe(2,2,3,3),& 
& gChaChacFuFu(2,2,3,3),gChaChacFvFv(2,2,3,3),gChaChicFuFd(2,5,3,3),gChaChicFvFe(2,5,3,3)

Complex(dp) :: coup 
Real(dp) :: vev 
Real(dp) :: gTVZ,gTVWm

Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateBR'
 
Write(*,*) "Calculating branching ratios and decay widths" 
gTVWm = gamW 
gTVZ = gamZ 
gPhh = 0._dp 
gThh = 0._dp 
BRhh = 0._dp 
Call hhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,            & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,           & 
& md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPhh,gThh,BRhh)

gPAh = 0._dp 
gTAh = 0._dp 
BRAh = 0._dp 
Call AhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,            & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,           & 
& md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPAh,gTAh,BRAh)

! Set Goldstone Widhts 
gTAh(1)=gTVZ


gPHpm = 0._dp 
gTHpm = 0._dp 
BRHpm = 0._dp 
Call HpmTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,             & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPHpm,gTHpm,BRHpm)

! Set Goldstone Widhts 
gTHpm(1)=gTVWm


gPChi = 0._dp 
gTChi = 0._dp 
BRChi = 0._dp 
Call ChiTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,             & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPChi(:,1:34),gTChi,BRChi(:,1:34))

Do i1=1,5
gTChi(i1) =Sum(gPChi(i1,:)) 
If (gTChi(i1).Gt.0._dp) BRChi(i1,: ) =gPChi(i1,:)/gTChi(i1) 
End Do 
 

gPCha = 0._dp 
gTCha = 0._dp 
BRCha = 0._dp 
Call ChaTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,             & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPCha(:,1:22),gTCha,BRCha(:,1:22))

Do i1=1,2
gTCha(i1) =Sum(gPCha(i1,:)) 
If (gTCha(i1).Gt.0._dp) BRCha(i1,: ) =gPCha(i1,:)/gTCha(i1) 
End Do 
 

gPFu = 0._dp 
gTFu = 0._dp 
BRFu = 0._dp 
Call FuTwoBodyDecay(-1,DeltaM,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,            & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,           & 
& md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gPFu,gTFu,BRFu)

! No 3-body decays for hh  
! No 3-body decays for Ah  
! No 3-body decays for Hpm  
If (.Not.CTBD) Then 
If (Enable3BDecaysF) Then 
If (MaxVal(gTChi).Lt.MaxVal(fac3*Abs(MChi))) Then 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTVWm,gTVZ,gChiChicChaCha,               & 
& gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,gChiChacFdFu,gChiChacFeFv,        & 
& gChiChicFvFv,epsI,deltaM,.False.,gTChi,gPChi(:,35:395),BRChi(:,35:395))

Else 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTVWm,gTVZ,gChiChicChaCha,               & 
& gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,gChiChacFdFu,gChiChacFeFv,        & 
& gChiChicFvFv,epsI,deltaM,.True.,gTChi,gPChi(:,35:395),BRChi(:,35:395))

End If 
 
End If 
Else 
Call ChiThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTVWm,gTVZ,gChiChicChaCha,               & 
& gChiChiChiChi,gChiChicFdFd,gChiChicFeFe,gChiChicFuFu,gChiChacFdFu,gChiChacFeFv,        & 
& gChiChicFvFv,epsI,deltaM,.False.,gTChi,gPChi(:,35:395),BRChi(:,35:395))

End If 
Do i1=1,5
gTChi(i1) =Sum(gPChi(i1,:)) 
If (gTChi(i1).Gt.0._dp) BRChi(i1,: ) =gPChi(i1,:)/gTChi(i1) 
End Do 
 

If (.Not.CTBD) Then 
If (Enable3BDecaysF) Then 
If (MaxVal(gTCha).Lt.MaxVal(fac3*Abs(MCha))) Then 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTVWm,gTVZ,gChaChacChaCha,               & 
& gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,gChaChacFvFv,gChaChicFuFd,        & 
& gChaChicFvFe,epsI,deltaM,.False.,gTCha,gPCha(:,23:242),BRCha(:,23:242))

Else 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTVWm,gTVZ,gChaChacChaCha,               & 
& gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,gChaChacFvFv,gChaChicFuFd,        & 
& gChaChicFvFe,epsI,deltaM,.True.,gTCha,gPCha(:,23:242),BRCha(:,23:242))

End If 
 
End If 
Else 
Call ChaThreeBodyDecay(-1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           & 
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             & 
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gTAh,gThh,gTHpm,gTVWm,gTVZ,gChaChacChaCha,               & 
& gChaChaChiChi,gChaChacFdFd,gChaChacFeFe,gChaChacFuFu,gChaChacFvFv,gChaChicFuFd,        & 
& gChaChicFvFe,epsI,deltaM,.False.,gTCha,gPCha(:,23:242),BRCha(:,23:242))

End If 
Do i1=1,2
gTCha(i1) =Sum(gPCha(i1,:)) 
If (gTCha(i1).Gt.0._dp) BRCha(i1,: ) =gPCha(i1,:)/gTCha(i1) 
End Do 
 

! No 3-body decays for Fu  
Iname = Iname - 1 
 
End Subroutine CalculateBR 
End Module BranchingRatios_NMSSM 
 