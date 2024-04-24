! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module BranchingRatios_gumTHDMII 
 
Use Control 
Use Settings 
Use Couplings_gumTHDMII 
Use Model_Data_gumTHDMII 
Use LoopCouplings_gumTHDMII 
Use Fu3Decays_gumTHDMII 
Use Fe3Decays_gumTHDMII 
Use Fd3Decays_gumTHDMII 
Use TreeLevelDecays_gumTHDMII 
Use OneLoopDecays_gumTHDMII


 Contains 
 
Subroutine CalculateBR(CTBD,fac3,epsI,deltaM,kont,MAh,MAh2,MFd,MFd2,MFe,              & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,              & 
& ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,           & 
& Yu,Yd,Ye,m122,m112,m222,gPFu,gTFu,BRFu,gPFe,gTFe,BRFe,gPFd,gTFd,BRFd,gPhh,             & 
& gThh,BRhh,gPAh,gTAh,BRAh,gPHm,gTHm,BRHm)

Real(dp), Intent(in) :: epsI, deltaM, fac3 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: CTBD 
Real(dp),Intent(inout) :: g1,g2,g3

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Real(dp),Intent(in) :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),               & 
& alphaH,betaH

Complex(dp),Intent(in) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Real(dp),Intent(inout) :: vd,vu

Real(dp),Intent(inout) :: gPFu(3,159),gTFu(3),BRFu(3,159),gPFe(3,156),gTFe(3),BRFe(3,156),gPFd(3,159),          & 
& gTFd(3),BRFd(3,159),gPhh(2,59),gThh(2),BRhh(2,59),gPAh(2,57),gTAh(2),BRAh(2,57),       & 
& gPHm(2,28),gTHm(2),BRHm(2,28)

Complex(dp) :: cplHiggsPP(2),cplHiggsGG(2),cplPseudoHiggsPP(2),cplPseudoHiggsGG(2),cplHiggsZZvirt(2),& 
& cplHiggsWWvirt(2)

Real(dp) :: gFuFucFdFd(3,3,3,3),gFuFucFeFe(3,3,3,3),gFuFucFuFu(3,3,3,3),gFuFdcFeFv(3,3,3,3),      & 
& gFuFucFvFv(3,3,3,3),gFeFecFdFd(3,3,3,3),gFeFecFeFe(3,3,3,3),gFeFecFuFu(3,3,3,3),       & 
& gFeFecFvFv(3,3,3,3),gFeFvcFuFd(3,3,3,3),gFdFdcFdFd(3,3,3,3),gFdFdcFeFe(3,3,3,3),       & 
& gFdFdcFuFu(3,3,3,3),gFdFdcFvFv(3,3,3,3),gFdFucFvFe(3,3,3,3)

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
Call CalculateOneLoopDecays(gP1LFu,gP1LFe,gP1LFd,gP1Lhh,gP1LAh,gP1LHm,Mhh,            & 
& Mhh2,MAh,MAh2,MHm,MHm2,MFd,MFd2,MFu,MFu2,MFe,MFe2,MVZ,MVZ2,MVWm,MVWm2,ZH,              & 
& ZA,ZP,ZDL,ZDR,ZUL,ZUR,ZEL,ZER,vd,vu,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,              & 
& Yd,Ye,m122,m112,m222,epsI,deltaM,kont)

End if 


gPFu = 0._dp 
gTFu = 0._dp 
BRFu = 0._dp 
Call FuTwoBodyDecay(-1,DeltaM,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,              & 
& alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,             & 
& vu,gPFu(:,1:24),gTFu,BRFu(:,1:24))

Do i1=1,3
gTFu(i1) =Sum(gPFu(i1,:)) 
If (gTFu(i1).Gt.0._dp) BRFu(i1,: ) =gPFu(i1,:)/gTFu(i1) 
If (OneLoopDecays) Then 
gT1LFu(i1) =Sum(gP1LFu(i1,:)) 
If (gT1LFu(i1).Gt.0._dp) BR1LFu(i1,: ) =gP1LFu(i1,:)/gT1LFu(i1) 
End if
End Do 
 

gPFe = 0._dp 
gTFe = 0._dp 
BRFe = 0._dp 
Call FeTwoBodyDecay(-1,DeltaM,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,              & 
& alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,             & 
& vu,gPFe(:,1:21),gTFe,BRFe(:,1:21))

Do i1=1,3
gTFe(i1) =Sum(gPFe(i1,:)) 
If (gTFe(i1).Gt.0._dp) BRFe(i1,: ) =gPFe(i1,:)/gTFe(i1) 
If (OneLoopDecays) Then 
gT1LFe(i1) =Sum(gP1LFe(i1,:)) 
If (gT1LFe(i1).Gt.0._dp) BR1LFe(i1,: ) =gP1LFe(i1,:)/gT1LFe(i1) 
End if
End Do 
 

gPFd = 0._dp 
gTFd = 0._dp 
BRFd = 0._dp 
Call FdTwoBodyDecay(-1,DeltaM,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,              & 
& alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,             & 
& vu,gPFd(:,1:24),gTFd,BRFd(:,1:24))

Do i1=1,3
gTFd(i1) =Sum(gPFd(i1,:)) 
If (gTFd(i1).Gt.0._dp) BRFd(i1,: ) =gPFd(i1,:)/gTFd(i1) 
If (OneLoopDecays) Then 
gT1LFd(i1) =Sum(gP1LFd(i1,:)) 
If (gT1LFd(i1).Gt.0._dp) BR1LFd(i1,: ) =gP1LFd(i1,:)/gT1LFd(i1) 
End if
End Do 
 

gPhh = 0._dp 
gThh = 0._dp 
BRhh = 0._dp 
Call hhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,              & 
& alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,             & 
& vu,gPhh,gThh,BRhh)

Do i1=1,2
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
Call AhTwoBodyDecay(-1,DeltaM,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,              & 
& alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,             & 
& vu,gPAh,gTAh,BRAh)

Do i1=1,2
gTAh(i1) =Sum(gPAh(i1,:)) 
If (gTAh(i1).Gt.0._dp) BRAh(i1,: ) =gPAh(i1,:)/gTAh(i1) 
If (OneLoopDecays) Then 
gT1LAh(i1) =Sum(gP1LAh(i1,:)) 
If (gT1LAh(i1).Gt.0._dp) BR1LAh(i1,: ) =gP1LAh(i1,:)/gT1LAh(i1) 
End if
End Do 
 

! Set Goldstone Widhts 
gTAh(1)=gTVZ


gPHm = 0._dp 
gTHm = 0._dp 
BRHm = 0._dp 
Call HmTwoBodyDecay(-1,DeltaM,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,              & 
& alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,             & 
& vu,gPHm,gTHm,BRHm)

Do i1=1,2
gTHm(i1) =Sum(gPHm(i1,:)) 
If (gTHm(i1).Gt.0._dp) BRHm(i1,: ) =gPHm(i1,:)/gTHm(i1) 
If (OneLoopDecays) Then 
gT1LHm(i1) =Sum(gP1LHm(i1,:)) 
If (gT1LHm(i1).Gt.0._dp) BR1LHm(i1,: ) =gP1LHm(i1,:)/gT1LHm(i1) 
End if
End Do 
 

! Set Goldstone Widhts 
gTHm(1)=gTVWm


If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Fu)) Then 
If (MaxVal(gTFu).Lt.MaxVal(fac3*Abs(MFu))) Then 
Call FuThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFuFucFdFd,gFuFucFeFe,gFuFucFuFu,gFuFdcFeFv,gFuFucFvFv,           & 
& epsI,deltaM,.False.,gTFu,gPFu(:,25:159),BRFu(:,25:159))

Else 
Call FuThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFuFucFdFd,gFuFucFeFe,gFuFucFuFu,gFuFdcFeFv,gFuFucFvFv,           & 
& epsI,deltaM,.True.,gTFu,gPFu(:,25:159),BRFu(:,25:159))

End If 
 
End If 
Else 
Call FuThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFuFucFdFd,gFuFucFeFe,gFuFucFuFu,gFuFdcFeFv,gFuFucFvFv,           & 
& epsI,deltaM,.False.,gTFu,gPFu(:,25:159),BRFu(:,25:159))

End If 
Do i1=1,3
gTFu(i1) =Sum(gPFu(i1,:)) 
If (gTFu(i1).Gt.0._dp) BRFu(i1,: ) =gPFu(i1,:)/gTFu(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Fe)) Then 
If (MaxVal(gTFe).Lt.MaxVal(fac3*Abs(MFe))) Then 
Call FeThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFeFecFdFd,gFeFecFeFe,gFeFecFuFu,gFeFecFvFv,gFeFvcFuFd,           & 
& epsI,deltaM,.False.,gTFe,gPFe(:,22:156),BRFe(:,22:156))

Else 
Call FeThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFeFecFdFd,gFeFecFeFe,gFeFecFuFu,gFeFecFvFv,gFeFvcFuFd,           & 
& epsI,deltaM,.True.,gTFe,gPFe(:,22:156),BRFe(:,22:156))

End If 
 
End If 
Else 
Call FeThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFeFecFdFd,gFeFecFeFe,gFeFecFuFu,gFeFecFvFv,gFeFvcFuFd,           & 
& epsI,deltaM,.False.,gTFe,gPFe(:,22:156),BRFe(:,22:156))

End If 
Do i1=1,3
gTFe(i1) =Sum(gPFe(i1,:)) 
If (gTFe(i1).Gt.0._dp) BRFe(i1,: ) =gPFe(i1,:)/gTFe(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Fd)) Then 
If (MaxVal(gTFd).Lt.MaxVal(fac3*Abs(MFd))) Then 
Call FdThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFdFdcFdFd,gFdFdcFeFe,gFdFdcFuFu,gFdFdcFvFv,gFdFucFvFe,           & 
& epsI,deltaM,.False.,gTFd,gPFd(:,25:159),BRFd(:,25:159))

Else 
Call FdThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFdFdcFdFd,gFdFdcFeFe,gFdFdcFuFu,gFdFdcFvFv,gFdFucFvFe,           & 
& epsI,deltaM,.True.,gTFd,gPFd(:,25:159),BRFd(:,25:159))

End If 
 
End If 
Else 
Call FdThreeBodyDecay(-1,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,            & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,           & 
& betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,vd,vu,gTAh,            & 
& gThh,gTHm,gTVWm,gTVZ,gFdFdcFdFd,gFdFdcFeFe,gFdFdcFuFu,gFdFdcFvFv,gFdFucFvFe,           & 
& epsI,deltaM,.False.,gTFd,gPFd(:,25:159),BRFd(:,25:159))

End If 
Do i1=1,3
gTFd(i1) =Sum(gPFd(i1,:)) 
If (gTFd(i1).Gt.0._dp) BRFd(i1,: ) =gPFd(i1,:)/gTFd(i1) 
End Do 
 

! No 3-body decays for hh  
! No 3-body decays for Ah  
! No 3-body decays for Hm  
Iname = Iname - 1 
 
End Subroutine CalculateBR 
End Module BranchingRatios_gumTHDMII 
 