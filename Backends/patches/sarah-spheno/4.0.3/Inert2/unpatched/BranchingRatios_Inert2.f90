! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module BranchingRatios_Inert2 
 
Use Control 
Use Settings 
Use Couplings_Inert2 
Use Model_Data_Inert2 
Use LoopCouplings_Inert2 
Use Fu3Decays_Inert2 
Use Fe3Decays_Inert2 
Use Fd3Decays_Inert2 
Use TreeLevelDecays_Inert2 
Use OneLoopDecays_Inert2


 Contains 
 
Subroutine CalculateBR(CTBD,fac3,epsI,deltaM,kont,MA0,MA02,MFd,MFd2,MFe,              & 
& MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,              & 
& ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,            & 
& Ye,Yd,Yu,MHD2,MHU2,gPFu,gTFu,BRFu,gPFe,gTFe,BRFe,gPFd,gTFd,BRFd,gPhh,gThh,             & 
& BRhh,gPH0,gTH0,BRH0,gPA0,gTA0,BRA0,gPHp,gTHp,BRHp)

Real(dp), Intent(in) :: epsI, deltaM, fac3 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: CTBD 
Real(dp),Intent(inout) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(in) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(in) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(inout) :: v

Real(dp),Intent(inout) :: gPFu(3,159),gTFu(3),BRFu(3,159),gPFe(3,156),gTFe(3),BRFe(3,156),gPFd(3,159),          & 
& gTFd(3),BRFd(3,159),gPhh(1,59),gThh,BRhh(1,59),gPH0(1,54),gTH0,BRH0(1,54),             & 
& gPA0(1,54),gTA0,BRA0(1,54),gPHp(2,28),gTHp(2),BRHp(2,28)

Complex(dp) :: cplHiggsPP,cplHiggsGG,cplPseudoHiggsPP,cplPseudoHiggsGG,cplHiggsZZvirt,               & 
& cplHiggsWWvirt

Real(dp) :: gTG0 
Real(dp) :: gFuFucFdFd(3,3,3,3),gFuFdcFeFv(3,3,3,3),gFuFucFeFe(3,3,3,3),gFuFucFuFu(3,3,3,3),      & 
& gFuFucFvFv(3,3,3,3),gFeFecFdFd(3,3,3,3),gFeFecFeFe(3,3,3,3),gFeFecFuFu(3,3,3,3),       & 
& gFeFecFvFv(3,3,3,3),gFeFvcFuFd(3,3,3,3),gFdFdcFdFd(3,3,3,3),gFdFdcFeFe(3,3,3,3),       & 
& gFdFdcFuFu(3,3,3,3),gFdFdcFvFv(3,3,3,3),gFdFucFvFe(3,3,3,3)

Complex(dp) :: coup 
Real(dp) :: vev 
Real(dp) :: gTVZ,gTVWp

Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateBR'
 
Write(*,*) "Calculating branching ratios and decay widths" 
gTVWp = gamW 
gTVZ = gamZ 
! One-Loop Decays 
If (OneLoopDecays) Then 
Call CalculateOneLoopDecays(gP1LFu,gP1LFe,gP1LFd,gP1Lhh,gP1LH0,gP1LA0,gP1LHp,         & 
& MHp,MHp2,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MA0,MA02,MH0,MH02,               & 
& MVZ,MVZ2,MVWp,MVWp2,ZP,ZDL,ZDR,ZUL,ZUR,ZEL,ZER,v,g1,g2,g3,lam5,lam1,lam4,              & 
& lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,epsI,deltaM,kont)

End if 


gPFu = 0._dp 
gTFu = 0._dp 
BRFu = 0._dp 
Call FuTwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPFu(:,1:24)    & 
& ,gTFu,BRFu(:,1:24))

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
Call FeTwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPFe(:,1:21)    & 
& ,gTFe,BRFe(:,1:21))

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
Call FdTwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPFd(:,1:24)    & 
& ,gTFd,BRFd(:,1:24))

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
Call hhTwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPhh,           & 
& gThh,BRhh)

Do i1=1,1
gThh =Sum(gPhh(i1,:)) 
If (gThh.Gt.0._dp) BRhh(i1,: ) =gPhh(i1,:)/gThh 
If (OneLoopDecays) Then 
gT1Lhh =Sum(gP1Lhh(i1,:)) 
If (gT1Lhh.Gt.0._dp) BR1Lhh(i1,: ) =gP1Lhh(i1,:)/gT1Lhh 
End if
End Do 
 

gPH0 = 0._dp 
gTH0 = 0._dp 
BRH0 = 0._dp 
Call H0TwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPH0,           & 
& gTH0,BRH0)

Do i1=1,1
gTH0 =Sum(gPH0(i1,:)) 
If (gTH0.Gt.0._dp) BRH0(i1,: ) =gPH0(i1,:)/gTH0 
If (OneLoopDecays) Then 
gT1LH0 =Sum(gP1LH0(i1,:)) 
If (gT1LH0.Gt.0._dp) BR1LH0(i1,: ) =gP1LH0(i1,:)/gT1LH0 
End if
End Do 
 

gPA0 = 0._dp 
gTA0 = 0._dp 
BRA0 = 0._dp 
Call A0TwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPA0,           & 
& gTA0,BRA0)

Do i1=1,1
gTA0 =Sum(gPA0(i1,:)) 
If (gTA0.Gt.0._dp) BRA0(i1,: ) =gPA0(i1,:)/gTA0 
If (OneLoopDecays) Then 
gT1LA0 =Sum(gP1LA0(i1,:)) 
If (gT1LA0.Gt.0._dp) BR1LA0(i1,: ) =gP1LA0(i1,:)/gT1LA0 
End if
End Do 
 

gPHp = 0._dp 
gTHp = 0._dp 
BRHp = 0._dp 
Call HpTwoBodyDecay(-1,DeltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,           & 
& MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,              & 
& ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gPHp,           & 
& gTHp,BRHp)

Do i1=1,2
gTHp(i1) =Sum(gPHp(i1,:)) 
If (gTHp(i1).Gt.0._dp) BRHp(i1,: ) =gPHp(i1,:)/gTHp(i1) 
If (OneLoopDecays) Then 
gT1LHp(i1) =Sum(gP1LHp(i1,:)) 
If (gT1LHp(i1).Gt.0._dp) BR1LHp(i1,: ) =gP1LHp(i1,:)/gT1LHp(i1) 
End if
End Do 
 

! Set Goldstone Widhts 
gTHp(1)=gTVWp


If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Fu)) Then 
If (MaxVal(gTFu).Lt.MaxVal(fac3*Abs(MFu))) Then 
Call FuThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFuFucFdFd,gFuFdcFeFv,gFuFucFeFe,gFuFucFuFu,gFuFucFvFv,epsI,           & 
& deltaM,.False.,gTFu,gPFu(:,25:159),BRFu(:,25:159))

Else 
Call FuThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFuFucFdFd,gFuFdcFeFv,gFuFucFeFe,gFuFucFuFu,gFuFucFvFv,epsI,           & 
& deltaM,.True.,gTFu,gPFu(:,25:159),BRFu(:,25:159))

End If 
 
End If 
Else 
Call FuThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFuFucFdFd,gFuFdcFeFv,gFuFucFeFe,gFuFucFuFu,gFuFucFvFv,epsI,           & 
& deltaM,.False.,gTFu,gPFu(:,25:159),BRFu(:,25:159))

End If 
Do i1=1,3
gTFu(i1) =Sum(gPFu(i1,:)) 
If (gTFu(i1).Gt.0._dp) BRFu(i1,: ) =gPFu(i1,:)/gTFu(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Fe)) Then 
If (MaxVal(gTFe).Lt.MaxVal(fac3*Abs(MFe))) Then 
Call FeThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFeFecFdFd,gFeFecFeFe,gFeFecFuFu,gFeFecFvFv,gFeFvcFuFd,epsI,           & 
& deltaM,.False.,gTFe,gPFe(:,22:156),BRFe(:,22:156))

Else 
Call FeThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFeFecFdFd,gFeFecFeFe,gFeFecFuFu,gFeFecFvFv,gFeFvcFuFd,epsI,           & 
& deltaM,.True.,gTFe,gPFe(:,22:156),BRFe(:,22:156))

End If 
 
End If 
Else 
Call FeThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFeFecFdFd,gFeFecFeFe,gFeFecFuFu,gFeFecFvFv,gFeFvcFuFd,epsI,           & 
& deltaM,.False.,gTFe,gPFe(:,22:156),BRFe(:,22:156))

End If 
Do i1=1,3
gTFe(i1) =Sum(gPFe(i1,:)) 
If (gTFe(i1).Gt.0._dp) BRFe(i1,: ) =gPFe(i1,:)/gTFe(i1) 
End Do 
 

If (.Not.CTBD) Then 
If ((Enable3BDecaysF).and.(Calc3BodyDecay_Fd)) Then 
If (MaxVal(gTFd).Lt.MaxVal(fac3*Abs(MFd))) Then 
Call FdThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFdFdcFdFd,gFdFdcFeFe,gFdFdcFuFu,gFdFdcFvFv,gFdFucFvFe,epsI,           & 
& deltaM,.False.,gTFd,gPFd(:,25:159),BRFd(:,25:159))

Else 
Call FdThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFdFdcFdFd,gFdFdcFeFe,gFdFdcFuFu,gFdFdcFvFv,gFdFucFvFe,epsI,           & 
& deltaM,.True.,gTFd,gPFd(:,25:159),BRFd(:,25:159))

End If 
 
End If 
Else 
Call FdThreeBodyDecay(-1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gThh,               & 
& gTHp,gTVWp,gTVZ,gFdFdcFdFd,gFdFdcFeFe,gFdFdcFuFu,gFdFdcFvFv,gFdFucFvFe,epsI,           & 
& deltaM,.False.,gTFd,gPFd(:,25:159),BRFd(:,25:159))

End If 
Do i1=1,3
gTFd(i1) =Sum(gPFd(i1,:)) 
If (gTFd(i1).Gt.0._dp) BRFd(i1,: ) =gPFd(i1,:)/gTFd(i1) 
End Do 
 

! No 3-body decays for hh  
! No 3-body decays for H0  
! No 3-body decays for A0  
! No 3-body decays for Hp  
Iname = Iname - 1 
 
End Subroutine CalculateBR 
End Module BranchingRatios_Inert2 
 