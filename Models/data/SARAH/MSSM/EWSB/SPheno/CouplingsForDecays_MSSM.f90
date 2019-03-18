! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:03 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module CouplingsForDecays_MSSM
 
Use Control 
Use Model_Data_MSSM 
Use RGEs_MSSM 
Use Couplings_MSSM 
Use LoopCouplings_MSSM 
Use Tadpoles_MSSM 
 Use SusyMasses_MSSM 
Use Mathematics, Only: CompareMatrices, Adjungate 
 
Use StandardModel 
Contains 
 
 
 
Subroutine CouplingsFor_Sd_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhSdcSd,cplChaFucSdL,              & 
& cplChaFucSdR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplhhSdcSd,           & 
& cplHpmSucSd,cplSdcSdVZ,cplSucSdVWm,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhSdcSd(2,6,6),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChiFdcSdL(4,3,6),        & 
& cplChiFdcSdR(4,3,6),cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplhhSdcSd(2,6,6),             & 
& cplHpmSucSd(2,6,6),cplSdcSdVZ(6,6),cplSucSdVWm(6,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Sd_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSdcSdT(gt1,gt2,gt3,Mu,Yd,Td,ZD,ZA,cplAhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSdcSdT(gt1,gt2,gt3,g1,g2,Mu,Yd,Td,vd,vu,ZD,ZH,cplhhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplHpmSucSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingHpmSucSdT(gt1,gt2,gt3,g2,Mu,Yd,Td,Yu,Tu,vd,vu,ZD,ZU,ZP,cplHpmSucSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcSdVZ = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSdcSdVZT(gt1,gt2,g1,g2,ZD,TW,cplSdcSdVZ(gt1,gt2))

 End Do 
End Do 


cplSucSdVWm = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSucSdVWmT(gt1,gt2,g2,ZD,ZU,cplSucSdVWm(gt1,gt2))

 End Do 
End Do 


cplChaFucSdL = 0._dp 
cplChaFucSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFucSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplChaFucSdL(gt1,gt2,gt3)& 
& ,cplChaFucSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Sd_decays_2B
 
Subroutine CouplingsFor_Su_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhSucSu,cplChiFucSuL,              & 
& cplChiFucSuR,cplcChaFdcSuL,cplcChaFdcSuR,cplGluFucSuL,cplGluFucSuR,cplhhSucSu,         & 
& cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVZ,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhSucSu(2,6,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplcChaFdcSuL(2,3,6),       & 
& cplcChaFdcSuR(2,3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplhhSucSu(2,6,6),            & 
& cplSdcHpmcSu(6,2,6),cplSdcSucVWm(6,6),cplSucSuVZ(6,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Su_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSucSuT(gt1,gt2,gt3,Mu,Yu,Tu,ZU,ZA,cplAhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSucSuT(gt1,gt2,gt3,g1,g2,Mu,Yu,Tu,vd,vu,ZU,ZH,cplhhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcHpmcSu = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingSdcHpmcSuT(gt1,gt2,gt3,g2,Mu,Yd,Td,Yu,Tu,vd,vu,ZD,ZU,ZP,cplSdcHpmcSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcSucVWm = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSdcSucVWmT(gt1,gt2,g2,ZD,ZU,cplSdcSucVWm(gt1,gt2))

 End Do 
End Do 


cplSucSuVZ = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSucSuVZT(gt1,gt2,g1,g2,ZU,TW,cplSucSuVZ(gt1,gt2))

 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFucSuL = 0._dp 
cplGluFucSuR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFucSuT(gt2,gt3,g3,pG,ZU,ZUL,ZUR,cplGluFucSuL(gt2,gt3),cplGluFucSuR(gt2,gt3))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Su_decays_2B
 
Subroutine CouplingsFor_Se_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhSecSe,cplChaFvcSeL,              & 
& cplChaFvcSeR,cplChiFecSeL,cplChiFecSeR,cplhhSecSe,cplHpmSvcSe,cplSecSeVZ,              & 
& cplSvcSeVWm,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhSecSe(2,6,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplChiFecSeL(4,3,6),        & 
& cplChiFecSeR(4,3,6),cplhhSecSe(2,6,6),cplHpmSvcSe(2,3,6),cplSecSeVZ(6,6),              & 
& cplSvcSeVWm(3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Se_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSecSeT(gt1,gt2,gt3,Mu,Ye,Te,ZE,ZA,cplAhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSecSeT(gt1,gt2,gt3,g1,g2,Mu,Ye,Te,vd,vu,ZE,ZH,cplhhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplHpmSvcSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingHpmSvcSeT(gt1,gt2,gt3,g2,Mu,Ye,Te,vd,vu,ZV,ZE,ZP,cplHpmSvcSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecSeVZ = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSecSeVZT(gt1,gt2,g1,g2,ZE,TW,cplSecSeVZ(gt1,gt2))

 End Do 
End Do 


cplSvcSeVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 6
Call CouplingSvcSeVWmT(gt1,gt2,g2,ZV,ZE,cplSvcSeVWm(gt1,gt2))

 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Se_decays_2B
 
Subroutine CouplingsFor_Sv_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplChiFvcSvL,cplChiFvcSvR,            & 
& cplcChaFecSvL,cplcChaFecSvR,cplhhSvcSv,cplSecHpmcSv,cplSecSvcVWm,cplSvcSvVZ,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),    & 
& cplhhSvcSv(2,3,3),cplSecHpmcSv(6,2,3),cplSecSvcVWm(6,3),cplSvcSvVZ(3,3)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Sv_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplhhSvcSv = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplinghhSvcSvT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,cplhhSvcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecHpmcSv = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingSecHpmcSvT(gt1,gt2,gt3,g2,Mu,Ye,Te,vd,vu,ZV,ZE,ZP,cplSecHpmcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecSvcVWm = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 3
Call CouplingSecSvcVWmT(gt1,gt2,g2,ZV,ZE,cplSecSvcVWm(gt1,gt2))

 End Do 
End Do 


cplSvcSvVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingSvcSvVZT(gt1,gt2,g1,g2,TW,cplSvcSvVZ(gt1,gt2))

 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Sv_decays_2B
 
Subroutine CouplingsFor_hh_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplHiggsPP,cplHiggsGG,cplHiggsZZvirt, & 
& cplHiggsWWvirt,cplAhAhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,           & 
& cplChiChihhR,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,              & 
& cplcFuFuhhR,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,      & 
& cplhhSvcSv,cplhhcVWmVWm,cplhhVZVZ,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplHiggsPP(2),cplHiggsGG(2),cplHiggsZZvirt(2),cplHiggsWWvirt(2),cplAhAhhh(2,2,2),     & 
& cplAhhhVZ(2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),cplChiChihhL(4,4,2),          & 
& cplChiChihhR(4,4,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFeFehhL(3,3,2),          & 
& cplcFeFehhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplhhhhhh(2,2,2),             & 
& cplhhHpmcHpm(2,2,2),cplhhHpmcVWm(2,2),cplhhSdcSd(2,6,6),cplhhSecSe(2,6,6),             & 
& cplhhSucSu(2,6,6),cplhhSvcSv(2,3,3),cplhhcVWmVWm(2),cplhhVZVZ(2)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp) :: ratCha(2),ratFd(3),ratFe(3),ratFu(3),ratHpm(2),ratSd(6),ratSe(6),ratSu(6),ratVWm

Complex(dp) :: ratPCha(2),ratPFd(3),ratPFe(3),ratPFu(3),ratPHpm(2),ratPSd(6),ratPSe(6),              & 
& ratPSu(6),ratPVWm

Complex(dp) :: coup 
Real(dp) :: vev, gNLO, NLOqcd, NNLOqcd, NNNLOqcd, AlphaSQ, AlphaSQhlf 
Real(dp) :: g1SM,g2SM,g3SM,vSM
Complex(dp) ::YuSM(3,3),YdSM(3,3),YeSM(3,3)
Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_hh_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
If (m_in.le.Qin) Then 
  If (m_in.le.mz) Then 
    Call RunSM(mz,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  Else 
    Call RunSM(m_in,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  End if 
End if 
! Run always SM gauge couplings if present 
! alphaS(mH/2) for NLO corrections to diphoton rate 
Call RunSMgauge(m_in/2._dp,deltaM, g1,g2,g3) 
AlphaSQhlf=g3**2/(4._dp*Pi) 
! alphaS(mH) for digluon rate 
Call RunSMgauge(m_in,deltaM, g1,g2,g3) 
AlphaSQ=g3**2/(4._dp*Pi) 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhhhhhT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpmT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSdcSdT(gt1,gt2,gt3,g1,g2,Mu,Yd,Td,vd,vu,ZD,ZH,cplhhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSecSeT(gt1,gt2,gt3,g1,g2,Mu,Ye,Te,vd,vu,ZE,ZH,cplhhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSucSuT(gt1,gt2,gt3,g1,g2,Mu,Yu,Tu,vd,vu,ZU,ZH,cplhhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSvcSv = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplinghhSvcSvT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,cplhhSvcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmT(gt1,gt2,g2,ZH,ZP,cplhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


vev = Sqrt(vd**2 + vu**2)
cplHiggsWWvirt = cplhhcVWmVWm/vev 
cplHiggsZZvirt = cplhhVZVZ*Sqrt(7._dp/12._dp-10._dp/9._dp*Sin(TW)**2+40._dp/27._dp*Sin(TW)**4)/vev 
 

!----------------------------------------------------
! Scalar Higgs coupling ratios 
!----------------------------------------------------
 
Do i2=1, 2
ratCha(i2) = cplcChaChahhL(i2,i2,i1)*1._dp*vev/MCha(i2) 
End Do 
Do i2=1, 3
ratFd(i2) = cplcFdFdhhL(i2,i2,i1)*1._dp*vev/MFd(i2) 
End Do 
Do i2=1, 3
ratFe(i2) = cplcFeFehhL(i2,i2,i1)*1._dp*vev/MFe(i2) 
End Do 
Do i2=1, 3
ratFu(i2) = cplcFuFuhhL(i2,i2,i1)*1._dp*vev/MFu(i2) 
End Do 
Do i2=1, 2
ratHpm(i2) = 0.5_dp*cplhhHpmcHpm(i1,i2,i2)*vev/MHpm2(i2) 
End Do 
Do i2=1, 6
ratSd(i2) = 0.5_dp*cplhhSdcSd(i1,i2,i2)*vev/MSd2(i2) 
End Do 
Do i2=1, 6
ratSe(i2) = 0.5_dp*cplhhSecSe(i1,i2,i2)*vev/MSe2(i2) 
End Do 
Do i2=1, 6
ratSu(i2) = 0.5_dp*cplhhSucSu(i1,i2,i2)*vev/MSu2(i2) 
End Do 
ratVWm = -0.5_dp*cplhhcVWmVWm(i1)*vev/MVWm2 
If (HigherOrderDiboson) Then 
  gNLO = Sqrt(AlphaSQhlf*4._dp*Pi) 
Else  
  gNLO = -1._dp 
End if 
Call CoupHiggsToPhoton(m_in,i1,ratCha,ratFd,ratFe,ratFu,ratHpm,ratSd,ratSe,           & 
& ratSu,ratVWm,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,MSu,gNLO,coup)

cplHiggsPP(i1) = coup*Alpha 
CoupHPP(i1) = coup 
Call CoupHiggsToPhotonSM(m_in,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,MSu,gNLO,coup)

ratioPP(i1) = Abs(cplHiggsPP(i1)/(coup*Alpha))**2 
  gNLO = -1._dp 
Call CoupHiggsToGluon(m_in,i1,ratFd,ratFu,ratSd,ratSu,MFd,MFu,MSd,MSu,gNLO,coup)

cplHiggsGG(i1) = coup*AlphaSQ 
CoupHGG(i1) = coup 
Call CoupHiggsToGluonSM(m_in,MFd,MFu,MSd,MSu,gNLO,coup)

If (HigherOrderDiboson) Then 
  NLOqcd = 12._dp*oo48pi2*(95._dp/4._dp - 7._dp/6._dp*NFlav(m_in))*g3**2 
  NNLOqcd = 0.0005785973353112832_dp*(410.52103034222284_dp - 52.326413200014684_dp*NFlav(m_in)+NFlav(m_in)**2 & 
 & +(2.6337085360233763_dp +0.7392866066030529_dp *NFlav(m_in))*Log(m_in**2/mf_u(3)**2))*g3**4 
  NNNLOqcd = 0.00017781840290519607_dp*(42.74607514668917_dp + 11.191050460173795_dp*Log(m_in**2/mf_u(3)**2) + Log(m_in**2/mf_u(3)**2)**2)*g3**6 
Else 
  NLOqcd = 0._dp 
  NNLOqcd = 0._dp 
  NNNLOqcd = 0._dp 
End if 
coup = coup*Sqrt(1._dp + NLOqcd+NNLOqcd+NNNLOqcd) 
cplHiggsGG(i1) = cplHiggsGG(i1)*Sqrt(1._dp + NLOqcd+NNLOqcd+NNNLOqcd) 
CoupHGG(i1)=cplHiggsGG(i1) 
ratioGG(i1) = Abs(cplHiggsGG(i1)/(coup*AlphaSQ))**2 
!----------------------------------------------------
! Coupling ratios for HiggsBounds 
!----------------------------------------------------
 
Do i2=1, 3
rHB_S_S_Fe(i1,i2) = Abs((cplcFeFehhL(i2,i2,i1)+cplcFeFehhR(i2,i2,i1))*vev/(2._dp*MFe(i2)))**2 
rHB_S_P_Fe(i1,i2) = Abs((cplcFeFehhL(i2,i2,i1)-cplcFeFehhR(i2,i2,i1))*vev/(2._dp*MFe(i2)))**2 
End Do 
Do i2=1, 3
rHB_S_S_Fu(i1,i2) = Abs((cplcFuFuhhL(i2,i2,i1)+cplcFuFuhhR(i2,i2,i1))*vev/(2._dp*MFu(i2)))**2 
rHB_S_P_Fu(i1,i2) = Abs((cplcFuFuhhL(i2,i2,i1)-cplcFuFuhhR(i2,i2,i1))*vev/(2._dp*MFu(i2)))**2 
End Do 
Do i2=1, 3
rHB_S_S_Fd(i1,i2) = Abs((cplcFdFdhhL(i2,i2,i1)+cplcFdFdhhR(i2,i2,i1))*vev/(2._dp*MFd(i2)))**2 
rHB_S_P_Fd(i1,i2) = Abs((cplcFdFdhhL(i2,i2,i1)-cplcFdFdhhR(i2,i2,i1))*vev/(2._dp*MFd(i2)))**2 
End Do 
rHB_S_VZ(i1) = Abs(-0.5_dp*cplhhVZVZ(i1)*vev/MVZ2)**2 
rHB_S_VWm(i1) = Abs(-0.5_dp*cplhhcVWmVWm(i1)*vev/MVWm2)**2 
If (i1.eq.1) Then 
CPL_A_H_Z = Abs(cplAhhhVZ**2/(g2**2/(cos(TW)*4._dp)))
CPL_H_H_Z = 0._dp 
End if 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhhhhhT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpmT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSdcSdT(gt1,gt2,gt3,g1,g2,Mu,Yd,Td,vd,vu,ZD,ZH,cplhhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSecSeT(gt1,gt2,gt3,g1,g2,Mu,Ye,Te,vd,vu,ZE,ZH,cplhhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSucSuT(gt1,gt2,gt3,g1,g2,Mu,Yu,Tu,vd,vu,ZU,ZH,cplhhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSvcSv = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplinghhSvcSvT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,cplhhSvcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmT(gt1,gt2,g2,ZH,ZP,cplhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_hh_decays_2B
 
Subroutine CouplingsFor_Ah_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplPseudoHiggsPP,cplPseudoHiggsGG,    & 
& cplAhAhhh,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhVZ,cplAhHpmcHpm,    & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplPseudoHiggsPP(2),cplPseudoHiggsGG(2),cplAhAhhh(2,2,2),cplcChaChaAhL(2,2,2),        & 
& cplcChaChaAhR(2,2,2),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),cplcFdFdAhL(3,3,2),       & 
& cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),           & 
& cplcFuFuAhR(3,3,2),cplAhhhVZ(2,2),cplAhHpmcHpm(2,2,2),cplAhHpmcVWm(2,2),               & 
& cplAhSdcSd(2,6,6),cplAhSecSe(2,6,6),cplAhSucSu(2,6,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp) :: ratCha(2),ratFd(3),ratFe(3),ratFu(3),ratHpm(2),ratSd(6),ratSe(6),ratSu(6),ratVWm

Complex(dp) :: ratPCha(2),ratPFd(3),ratPFe(3),ratPFu(3),ratPHpm(2),ratPSd(6),ratPSe(6),              & 
& ratPSu(6),ratPVWm

Complex(dp) :: coup 
Real(dp) :: vev, gNLO, NLOqcd, NNLOqcd, NNNLOqcd, AlphaSQ, AlphaSQhlf 
Real(dp) :: g1SM,g2SM,g3SM,vSM
Complex(dp) ::YuSM(3,3),YdSM(3,3),YeSM(3,3)
Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Ah_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
If (m_in.le.Qin) Then 
  If (m_in.le.mz) Then 
    Call RunSM(mz,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  Else 
    Call RunSM(m_in,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  End if 
End if 
! Run always SM gauge couplings if present 
! alphaS(mH/2) for NLO corrections to diphoton rate 
Call RunSMgauge(m_in/2._dp,deltaM, g1,g2,g3) 
AlphaSQhlf=g3**2/(4._dp*Pi) 
! alphaS(mH) for digluon rate 
Call RunSMgauge(m_in,deltaM, g1,g2,g3) 
AlphaSQ=g3**2/(4._dp*Pi) 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpmT(gt1,gt2,gt3,g2,vd,vu,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSdcSdT(gt1,gt2,gt3,Mu,Yd,Td,ZD,ZA,cplAhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSecSeT(gt1,gt2,gt3,Mu,Ye,Te,ZE,ZA,cplAhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSucSuT(gt1,gt2,gt3,Mu,Yu,Tu,ZU,ZA,cplAhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmT(gt1,gt2,g2,ZA,ZP,cplAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


vev = Sqrt(vd**2 + vu**2)
!----------------------------------------------------
! Pseudo Scalar Higgs coupling ratios 
!----------------------------------------------------
 
Do i2=1, 2
ratPCha(i2) = cplcChaChaAhL(i2,i2,i1)*1._dp*vev/MCha(i2) 
End Do 
Do i2=1, 3
ratPFd(i2) = cplcFdFdAhL(i2,i2,i1)*1._dp*vev/MFd(i2) 
End Do 
Do i2=1, 3
ratPFe(i2) = cplcFeFeAhL(i2,i2,i1)*1._dp*vev/MFe(i2) 
End Do 
Do i2=1, 3
ratPFu(i2) = cplcFuFuAhL(i2,i2,i1)*1._dp*vev/MFu(i2) 
End Do 
Do i2=1, 2
ratPHpm(i2) = 0.5_dp*cplAhHpmcHpm(i1,i2,i2)*vev/MHpm2(i2) 
End Do 
Do i2=1, 6
ratPSd(i2) = 0.5_dp*cplAhSdcSd(i1,i2,i2)*vev/MSd2(i2) 
End Do 
Do i2=1, 6
ratPSe(i2) = 0.5_dp*cplAhSecSe(i1,i2,i2)*vev/MSe2(i2) 
End Do 
Do i2=1, 6
ratPSu(i2) = 0.5_dp*cplAhSucSu(i1,i2,i2)*vev/MSu2(i2) 
End Do 
ratPVWm = 0._dp 
If (HigherOrderDiboson) Then 
  gNLO = g3 
Else  
  gNLO = -1._dp 
End if 
Call CoupPseudoHiggsToPhoton(m_in,i1,ratPCha,ratPFd,ratPFe,ratPFu,ratPHpm,            & 
& ratPSd,ratPSe,ratPSu,ratPVWm,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,MSu,gNLO,coup)

cplPseudoHiggsPP(i1) = 2._dp*coup*Alpha 
CoupAPP(i1) = 2._dp*coup 
Call CoupPseudoHiggsToPhotonSM(m_in,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,               & 
& MSu,gNLO,coup)

ratioPPP(i1) = Abs(cplPseudoHiggsPP(i1)/(2._dp*coup*oo4pi*(1._dp-mW2/mZ2)*g2**2))**2 
  gNLO = -1._dp 
Call CoupPseudoHiggsToGluon(Mhh(i1),i1,ratPFd,ratPFu,ratPSd,ratPSu,MFd,               & 
& MFu,MSd,MSu,gNLO,coup)

If (HigherOrderDiboson) Then 
  NLOqcd = 12._dp*oo48pi2*(97._dp/4._dp - 7._dp/6._dp*NFlav(m_in))*g3**2 
  NNLOqcd = (171.544_dp +  5._dp*Log(m_in**2/mf_u(3)**2))*g3**4/(4._dp*Pi**2)**2 
  NNNLOqcd = 0._dp 
Else 
  NLOqcd = 0._dp 
  NNLOqcd = 0._dp 
  NNNLOqcd = 0._dp 
End if 
cplPseudoHiggsGG(i1) = 2._dp*coup*AlphaSQ*Sqrt(1._dp + NLOqcd+NNLOqcd+NNNLOqcd) 
CoupAGG(i1) = 2._dp*coup*AlphaSQ*Sqrt(1._dp + NLOqcd+NNLOqcd+NNNLOqcd) 
Call CoupPseudoHiggsToGluonSM(m_in,MFd,MFu,MSd,MSu,gNLO,coup)

coup = coup*Sqrt(1._dp + NLOqcd+NNLOqcd+NNNLOqcd) 
ratioPGG(i1) = Abs(cplPseudoHiggsGG(i1)/(2._dp*coup*AlphaSQ))**2 

!----------------------------------------------------
! Coupling ratios for HiggsBounds 
!----------------------------------------------------
 
Do i2=1, 3
rHB_P_S_Fe(i1,i2) = 1._dp*Abs((cplcFeFeAhL(i2,i2,i1)+cplcFeFeAhR(i2,i2,i1))*vev/(2._dp*MFe(i2)))**2 
rHB_P_P_Fe(i1,i2) = 1._dp*Abs((cplcFeFeAhL(i2,i2,i1)-cplcFeFeAhR(i2,i2,i1))*vev/(2._dp*MFe(i2)))**2 
End Do 
Do i2=1, 3
rHB_P_S_Fu(i1,i2) = 1._dp*Abs((cplcFuFuAhL(i2,i2,i1)+cplcFuFuAhR(i2,i2,i1))*vev/(2._dp*MFu(i2)))**2 
rHB_P_P_Fu(i1,i2) = 1._dp*Abs((cplcFuFuAhL(i2,i2,i1)-cplcFuFuAhR(i2,i2,i1))*vev/(2._dp*MFu(i2)))**2 
End Do 
Do i2=1, 3
rHB_P_S_Fd(i1,i2) = 1._dp*Abs((cplcFdFdAhL(i2,i2,i1)+cplcFdFdAhR(i2,i2,i1))*vev/(2._dp*MFd(i2)))**2 
rHB_P_P_Fd(i1,i2) = 1._dp*Abs((cplcFdFdAhL(i2,i2,i1)-cplcFdFdAhR(i2,i2,i1))*vev/(2._dp*MFd(i2)))**2 
End Do 
If (i1.eq.2) Then 
CPL_A_A_Z = 0._dp 
End if 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpmT(gt1,gt2,gt3,g2,vd,vu,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSdcSdT(gt1,gt2,gt3,Mu,Yd,Td,ZD,ZA,cplAhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSecSeT(gt1,gt2,gt3,Mu,Ye,Te,ZE,ZA,cplAhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSucSuT(gt1,gt2,gt3,Mu,Yu,Tu,ZU,ZA,cplAhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmT(gt1,gt2,g2,ZA,ZP,cplAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Ah_decays_2B
 
Subroutine CouplingsFor_Hpm_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhHpmcHpm,cplAhcHpmVWm,            & 
& cplChiChacHpmL,cplChiChacHpmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFvFecHpmL,               & 
& cplcFvFecHpmR,cplhhHpmcHpm,cplhhcHpmVWm,cplHpmcHpmVZ,cplSdcHpmcSu,cplSecHpmcSv,        & 
& cplcHpmVWmVZ,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhHpmcHpm(2,2,2),cplAhcHpmVWm(2,2),cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),    & 
& cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),   & 
& cplhhHpmcHpm(2,2,2),cplhhcHpmVWm(2,2),cplHpmcHpmVZ(2,2),cplSdcHpmcSu(6,2,6),           & 
& cplSecHpmcSv(6,2,3),cplcHpmVWmVZ(2)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Hpm_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
If (m_in.le.Qin) Then 
  If (m_in.le.mz) Then 
    Call RunSM(mz,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  Else 
    Call RunSM(m_in,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  End if 
End if 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpmT(gt1,gt2,gt3,g2,vd,vu,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpmT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcHpmcSu = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingSdcHpmcSuT(gt1,gt2,gt3,g2,Mu,Yd,Td,Yu,Tu,vd,vu,ZD,ZU,ZP,cplSdcHpmcSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecHpmcSv = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingSecHpmcSvT(gt1,gt2,gt3,g2,Mu,Ye,Te,vd,vu,ZV,ZE,ZP,cplSecHpmcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhcHpmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHpmVWmT(gt1,gt2,g2,ZA,ZP,cplAhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHpmVWmT(gt1,gt2,g2,ZH,ZP,cplhhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZ(gt1,gt2))

 End Do 
End Do 


cplcHpmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVWmVZ(gt1))

End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Hpm_decays_2B
 
Subroutine CouplingsFor_Glu_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplGluFdcSdL,cplGluFdcSdR,            & 
& cplGluFucSuL,cplGluFucSuR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Glu_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


cplGluFucSuL = 0._dp 
cplGluFucSuR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFucSuT(gt2,gt3,g3,pG,ZU,ZUL,ZUR,cplGluFucSuL(gt2,gt3),cplGluFucSuR(gt2,gt3))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Glu_decays_2B
 
Subroutine CouplingsFor_Chi_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplChiChiAhL,cplChiChiAhR,            & 
& cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChihhL,              & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),  & 
& cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),       & 
& cplChiChiVZL(4,4),cplChiChiVZR(4,4),cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),           & 
& cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),       & 
& cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Chi_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Chi_decays_2B
 
Subroutine CouplingsFor_Cha_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplcChaChaAhL,cplcChaChaAhR,          & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR, & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,               & 
& cplcChaFecSvR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),  & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),     & 
& cplcChaChiVWmL(2,4),cplcChaChiVWmR(2,4),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),     & 
& cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),   & 
& cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Cha_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFvSeL = 0._dp 
cplcChacFvSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFvSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplcChacFvSeL(gt1,gt2,gt3)            & 
& ,cplcChacFvSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Cha_decays_2B
 
Subroutine CouplingsFor_Fu_decays_2B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplcFuFuAhL,cplcFuFuAhR,              & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,             & 
& cplcChacFuSdL,cplcChacFuSdR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),        & 
& cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),       & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),               & 
& cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Fu_2B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
If (m_in.le.Qin) Then 
  If (m_in.le.mz) Then 
    Call RunSM(mz,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  Else 
    Call RunSM(m_in,deltaM,vu/vd,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
  End if 
End if 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuGluSuL = 0._dp 
cplcFuGluSuR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFuGluSuT(gt1,gt3,g3,pG,ZU,ZUL,ZUR,cplcFuGluSuL(gt1,gt3),cplcFuGluSuR(gt1,gt3))

 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Fu_decays_2B
 
Subroutine CouplingsFor_Glu_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplcChacFuSdL,cplcChacFuSdR,          & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdGluSdL,cplcFdGluSdR,       & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuGluSuL,cplcFuGluSuR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFucSuL,cplChiFucSuR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),  & 
& cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),           & 
& cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),           & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Glu_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChiSdL = 0._dp 
cplcFdChiSdR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFdChiSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplcFdChiSdL(gt1,gt2,gt3)   & 
& ,cplcFdChiSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFucSuL = 0._dp 
cplGluFucSuR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFucSuT(gt2,gt3,g3,pG,ZU,ZUL,ZUR,cplGluFucSuL(gt2,gt3),cplGluFucSuR(gt2,gt3))

 End Do 
End Do 


cplcFdGluSdL = 0._dp 
cplcFdGluSdR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFdGluSdT(gt1,gt3,g3,pG,ZD,ZDL,ZDR,cplcFdGluSdL(gt1,gt3),cplcFdGluSdR(gt1,gt3))

 End Do 
End Do 


cplcFuGluSuL = 0._dp 
cplcFuGluSuR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFuGluSuT(gt1,gt3,g3,pG,ZU,ZUL,ZUR,cplcFuGluSuL(gt1,gt3),cplcFuGluSuR(gt1,gt3))

 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Glu_decays_3B
 
Subroutine CouplingsFor_Chi_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplcChaChaAhL,cplcChaChaAhR,          & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR, & 
& cplcChaChiVWmL,cplcChaChiVWmR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFuAhL,cplcFuFuAhR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,             & 
& cplcFvChiSvL,cplcFvChiSvR,cplcFvFvVZL,cplcFvFvVZR,cplChaFucSdL,cplChaFucSdR,           & 
& cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,         & 
& cplChiFvcSvL,cplChiFvcSvR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),  & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),     & 
& cplcChaChiVWmL(2,4),cplcChaChiVWmR(2,4),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),       & 
& cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),         & 
& cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),               & 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),           & 
& cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),           & 
& cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),         & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),               & 
& cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),           & 
& cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),               & 
& cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),           & 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),             & 
& cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),   & 
& cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),       & 
& cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),cplChiChiVZR(4,4),           & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),       & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Chi_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFucSdL = 0._dp 
cplChaFucSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFucSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplChaFucSdL(gt1,gt2,gt3)& 
& ,cplChaFucSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChaSuL = 0._dp 
cplcFdChaSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingcFdChaSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcFdChaSuL(gt1,gt2,gt3)& 
& ,cplcFdChaSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChaSvL = 0._dp 
cplcFeChaSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcFeChaSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcFeChaSvL(gt1,gt2,gt3)   & 
& ,cplcFeChaSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChiSdL = 0._dp 
cplcFdChiSdR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFdChiSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplcFdChiSdL(gt1,gt2,gt3)   & 
& ,cplcFdChiSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChiSeL = 0._dp 
cplcFeChiSeR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFeChiSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplcFeChiSeL(gt1,gt2,gt3)   & 
& ,cplcFeChiSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFucSuL = 0._dp 
cplGluFucSuR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFucSuT(gt2,gt3,g3,pG,ZU,ZUL,ZUR,cplGluFucSuL(gt2,gt3),cplGluFucSuR(gt2,gt3))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3) & 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3),               & 
& cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdGluSdL = 0._dp 
cplcFdGluSdR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFdGluSdT(gt1,gt3,g3,pG,ZD,ZDL,ZDR,cplcFdGluSdL(gt1,gt3),cplcFdGluSdR(gt1,gt3))

 End Do 
End Do 


cplcFuGluSuL = 0._dp 
cplcFuGluSuR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFuGluSuT(gt1,gt3,g3,pG,ZU,ZUL,ZUR,cplcFuGluSuL(gt1,gt3),cplcFuGluSuR(gt1,gt3))

 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFuVWmL = 0._dp 
cplcFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFuVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFdFuVWmL(gt1,gt2),cplcFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvVWmL = 0._dp 
cplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,cplcFeFvVWmL(gt1,gt2),cplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Chi_decays_3B
 
Subroutine CouplingsFor_Cha_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,           & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplcChacFuSdL,cplcChacFuSdR,          & 
& cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,   & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,              & 
& cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,              & 
& cplcFdFdVZR,cplcFeChaSvL,cplcFeChaSvR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,           & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,            & 
& cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,      & 
& cplcFvFvVZR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,        & 
& cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,   & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplGluFdcSdL,cplGluFdcSdR,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),  & 
& cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),   & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),     & 
& cplcChaChiVWmL(2,4),cplcChaChiVWmR(2,4),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),     & 
& cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),     & 
& cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),           & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),             & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),           & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),             & 
& cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),       & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcFvChiSvL(3,4,3),& 
& cplcFvChiSvR(3,4,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFvFecVWmL(3,3),      & 
& cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplChaFucSdL(2,3,6),              & 
& cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplChiChacHpmL(4,2,2),     & 
& cplChiChacHpmR(4,2,2),cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChiAhL(4,4,2),     & 
& cplChiChiAhR(4,4,2),cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),         & 
& cplChiChiVZR(4,4),cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),         & 
& cplChiFecSeR(4,3,6),cplGluFdcSdL(3,6),cplGluFdcSdR(3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Cha_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFucSdL = 0._dp 
cplChaFucSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFucSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplChaFucSdL(gt1,gt2,gt3)& 
& ,cplChaFucSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChaSuL = 0._dp 
cplcFdChaSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingcFdChaSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcFdChaSuL(gt1,gt2,gt3)& 
& ,cplcFdChaSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChaSvL = 0._dp 
cplcFeChaSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcFeChaSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcFeChaSvL(gt1,gt2,gt3)   & 
& ,cplcFeChaSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuGluSuL = 0._dp 
cplcFuGluSuR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFuGluSuT(gt1,gt3,g3,pG,ZU,ZUL,ZUR,cplcFuGluSuL(gt1,gt3),cplcFuGluSuR(gt1,gt3))

 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFvSeL = 0._dp 
cplcChacFvSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFvSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplcChacFvSeL(gt1,gt2,gt3)            & 
& ,cplcChacFvSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmT(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Cha_decays_3B
 
Subroutine CouplingsFor_Sd_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhSdcSd,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,   & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdGluSdL,cplcFdGluSdR,           & 
& cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,         & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,           & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplChaFucSdL,cplChaFucSdR,cplChiChacHpmL,cplChiChacHpmR,cplChiChacVWmL,cplChiChacVWmR, & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,         & 
& cplChiFvcSvL,cplChiFvcSvR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,         & 
& cplhhSdcSd,cplHpmSucSd,cplSdcSdVZ,cplSucSdVWm,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhSdcSd(2,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),     & 
& cplcChacFvSeR(2,3,6),cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),   & 
& cplcChaChahhR(2,2,2),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),      & 
& cplcChaChiHpmR(2,4,2),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcChaFecSvL(2,3,3),  & 
& cplcChaFecSvR(2,3,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFdChiSdL(3,4,6),      & 
& cplcFdChiSdR(3,4,6),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),          & 
& cplcFdFdhhR(3,3,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),              & 
& cplcFdFuHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFeChiSeL(3,4,6),           & 
& cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),          & 
& cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuChiSuL(3,4,6),              & 
& cplcFuChiSuR(3,4,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),      & 
& cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),           & 
& cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),& 
& cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),     & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),   & 
& cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),       & 
& cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),cplChiChiVZR(4,4),           & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),       & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6),               & 
& cplhhSdcSd(2,6,6),cplHpmSucSd(2,6,6),cplSdcSdVZ(6,6),cplSucSdVWm(6,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Sd_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSdcSdT(gt1,gt2,gt3,Mu,Yd,Td,ZD,ZA,cplAhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSdcSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSdcSdT(gt1,gt2,gt3,g1,g2,Mu,Yd,Td,vd,vu,ZD,ZH,cplhhSdcSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplHpmSucSd = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingHpmSucSdT(gt1,gt2,gt3,g2,Mu,Yd,Td,Yu,Tu,vd,vu,ZD,ZU,ZP,cplHpmSucSd(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcSdVZ = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSdcSdVZT(gt1,gt2,g1,g2,ZD,TW,cplSdcSdVZ(gt1,gt2))

 End Do 
End Do 


cplSucSdVWm = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSucSdVWmT(gt1,gt2,g2,ZD,ZU,cplSucSdVWm(gt1,gt2))

 End Do 
End Do 


cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFucSdL = 0._dp 
cplChaFucSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFucSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplChaFucSdL(gt1,gt2,gt3)& 
& ,cplChaFucSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChaSuL = 0._dp 
cplcFdChaSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingcFdChaSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcFdChaSuL(gt1,gt2,gt3)& 
& ,cplcFdChaSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChiSdL = 0._dp 
cplcFdChiSdR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFdChiSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplcFdChiSdL(gt1,gt2,gt3)   & 
& ,cplcFdChiSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChiSeL = 0._dp 
cplcFeChiSeR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFeChiSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplcFeChiSeL(gt1,gt2,gt3)   & 
& ,cplcFeChiSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFucSuL = 0._dp 
cplGluFucSuR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFucSuT(gt2,gt3,g3,pG,ZU,ZUL,ZUR,cplGluFucSuL(gt2,gt3),cplGluFucSuR(gt2,gt3))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3) & 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdGluSdL = 0._dp 
cplcFdGluSdR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFdGluSdT(gt1,gt3,g3,pG,ZD,ZDL,ZDR,cplcFdGluSdL(gt1,gt3),cplcFdGluSdR(gt1,gt3))

 End Do 
End Do 


cplcFuGluSuL = 0._dp 
cplcFuGluSuR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFuGluSuT(gt1,gt3,g3,pG,ZU,ZUL,ZUR,cplcFuGluSuL(gt1,gt3),cplcFuGluSuR(gt1,gt3))

 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFvSeL = 0._dp 
cplcChacFvSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFvSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplcChacFvSeL(gt1,gt2,gt3)            & 
& ,cplcChacFvSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmT(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Sd_decays_3B
 
Subroutine CouplingsFor_Su_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhSucSu,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,             & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,         & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFvVZL,cplcFvFvVZR,           & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,         & 
& cplChiFvcSvL,cplChiFvcSvR,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,         & 
& cplhhSucSu,cplSdcHpmcSu,cplSdcSucVWm,cplSucSuVZ,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhSucSu(2,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChaChaAhL(2,2,2),     & 
& cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),cplcChaChaVZL(2,2),     & 
& cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),cplcChaChiVWmL(2,4),    & 
& cplcChaChiVWmR(2,4),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFdFdAhL(3,3,2),        & 
& cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVZL(3,3),             & 
& cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFdFuVWmL(3,3),            & 
& cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFeChaSvL(3,2,3),             & 
& cplcFeChaSvR(3,2,3),cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),        & 
& cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),             & 
& cplcFeFeVZR(3,3),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),            & 
& cplcFeFvVWmR(3,3),cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuFdcHpmL(3,3,2),        & 
& cplcFuFdcHpmR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),         & 
& cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),& 
& cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),             & 
& cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),       & 
& cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),   & 
& cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),cplChiChiVZR(4,4),           & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),       & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3),       & 
& cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6),               & 
& cplhhSucSu(2,6,6),cplSdcHpmcSu(6,2,6),cplSdcSucVWm(6,6),cplSucSuVZ(6,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Su_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSucSuT(gt1,gt2,gt3,Mu,Yu,Tu,ZU,ZA,cplAhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSucSu = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSucSuT(gt1,gt2,gt3,g1,g2,Mu,Yu,Tu,vd,vu,ZU,ZH,cplhhSucSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcHpmcSu = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingSdcHpmcSuT(gt1,gt2,gt3,g2,Mu,Yd,Td,Yu,Tu,vd,vu,ZD,ZU,ZP,cplSdcHpmcSu(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSdcSucVWm = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSdcSucVWmT(gt1,gt2,g2,ZD,ZU,cplSdcSucVWm(gt1,gt2))

 End Do 
End Do 


cplSucSuVZ = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSucSuVZT(gt1,gt2,g1,g2,ZU,TW,cplSucSuVZ(gt1,gt2))

 End Do 
End Do 


cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFucSdL = 0._dp 
cplChaFucSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFucSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplChaFucSdL(gt1,gt2,gt3)& 
& ,cplChaFucSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChaSuL = 0._dp 
cplcFdChaSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingcFdChaSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcFdChaSuL(gt1,gt2,gt3)& 
& ,cplcFdChaSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChaSvL = 0._dp 
cplcFeChaSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcFeChaSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcFeChaSvL(gt1,gt2,gt3)   & 
& ,cplcFeChaSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChiSdL = 0._dp 
cplcFdChiSdR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFdChiSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplcFdChiSdL(gt1,gt2,gt3)   & 
& ,cplcFdChiSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChiSeL = 0._dp 
cplcFeChiSeR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFeChiSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplcFeChiSeL(gt1,gt2,gt3)   & 
& ,cplcFeChiSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFdcSdL = 0._dp 
cplGluFdcSdR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFdcSdT(gt2,gt3,g3,pG,ZD,ZDL,ZDR,cplGluFdcSdL(gt2,gt3),cplGluFdcSdR(gt2,gt3))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplGluFucSuL = 0._dp 
cplGluFucSuR = 0._dp 
Do gt2 = 1, 3
 Do gt3 = 1, 6
Call CouplingGluFucSuT(gt2,gt3,g3,pG,ZU,ZUL,ZUR,cplGluFucSuL(gt2,gt3),cplGluFucSuR(gt2,gt3))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3) & 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3),               & 
& cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdGluSdL = 0._dp 
cplcFdGluSdR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFdGluSdT(gt1,gt3,g3,pG,ZD,ZDL,ZDR,cplcFdGluSdL(gt1,gt3),cplcFdGluSdR(gt1,gt3))

 End Do 
End Do 


cplcFuGluSuL = 0._dp 
cplcFuGluSuR = 0._dp 
Do gt1 = 1, 3
 Do gt3 = 1, 6
Call CouplingcFuGluSuT(gt1,gt3,g3,pG,ZU,ZUL,ZUR,cplcFuGluSuL(gt1,gt3),cplcFuGluSuR(gt1,gt3))

 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFuVWmL = 0._dp 
cplcFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFuVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFdFuVWmL(gt1,gt2),cplcFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvVWmL = 0._dp 
cplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,cplcFeFvVWmL(gt1,gt2),cplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Su_decays_3B
 
Subroutine CouplingsFor_Se_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplAhSecSe,cplcChacFuSdL,             & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,   & 
& cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,cplcChaChiHpmL,cplcChaChiHpmR,               & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChiSdL,cplcFdChiSdR,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,     & 
& cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,       & 
& cplChiChacVWmL,cplChiChacVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,     & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,         & 
& cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplhhSecSe,cplHpmSvcSe,            & 
& cplSecSeVZ,cplSvcSeVWm,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplAhSecSe(2,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),     & 
& cplcChacFvSeR(2,3,6),cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),   & 
& cplcChaChahhR(2,2,2),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),      & 
& cplcChaChiHpmR(2,4,2),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcChaFecSvL(2,3,3),  & 
& cplcChaFecSvR(2,3,3),cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFdFdAhL(3,3,2),       & 
& cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVZL(3,3),             & 
& cplcFdFdVZR(3,3),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplcFeChiSeL(3,4,6),          & 
& cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),          & 
& cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHpmL(3,3,2),              & 
& cplcFeFvHpmR(3,3,2),cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuFdcHpmL(3,3,2),      & 
& cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),         & 
& cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),             & 
& cplcFuFuVZR(3,3),cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),cplcFvFecHpmL(3,3,2),         & 
& cplcFvFecHpmR(3,3,2),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),           & 
& cplcFvFvVZR(3,3),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplChiChacHpmL(4,2,2),        & 
& cplChiChacHpmR(4,2,2),cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChiAhL(4,4,2),     & 
& cplChiChiAhR(4,4,2),cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),         & 
& cplChiChiVZR(4,4),cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),         & 
& cplChiFecSeR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),       & 
& cplChiFvcSvR(4,3,3),cplhhSecSe(2,6,6),cplHpmSvcSe(2,3,6),cplSecSeVZ(6,6),              & 
& cplSvcSeVWm(3,6)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Se_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplAhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplingAhSecSeT(gt1,gt2,gt3,Mu,Ye,Te,ZE,ZA,cplAhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhSecSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 6
  Do gt3 = 1, 6
Call CouplinghhSecSeT(gt1,gt2,gt3,g1,g2,Mu,Ye,Te,vd,vu,ZE,ZH,cplhhSecSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplHpmSvcSe = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingHpmSvcSeT(gt1,gt2,gt3,g2,Mu,Ye,Te,vd,vu,ZV,ZE,ZP,cplHpmSvcSe(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecSeVZ = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 6
Call CouplingSecSeVZT(gt1,gt2,g1,g2,ZE,TW,cplSecSeVZ(gt1,gt2))

 End Do 
End Do 


cplSvcSeVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 6
Call CouplingSvcSeVWmT(gt1,gt2,g2,ZV,ZE,cplSvcSeVWm(gt1,gt2))

 End Do 
End Do 


cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChaSvL = 0._dp 
cplcFeChaSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcFeChaSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcFeChaSvL(gt1,gt2,gt3)   & 
& ,cplcFeChaSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChiSdL = 0._dp 
cplcFdChiSdR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFdChiSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplcFdChiSdL(gt1,gt2,gt3)   & 
& ,cplcFdChiSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChiSeL = 0._dp 
cplcFeChiSeR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFeChiSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplcFeChiSeL(gt1,gt2,gt3)   & 
& ,cplcFeChiSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFdcSuL = 0._dp 
cplcChaFdcSuR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChaFdcSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcChaFdcSuL(gt1,gt2,gt3)& 
& ,cplcChaFdcSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3),               & 
& cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFuSdL = 0._dp 
cplcChacFuSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFuSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplcChacFuSdL(gt1,gt2,gt3)& 
& ,cplcChacFuSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFvSeL = 0._dp 
cplcChacFvSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFvSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplcChacFvSeL(gt1,gt2,gt3)            & 
& ,cplcChacFvSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmT(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Se_decays_3B
 
Subroutine CouplingsFor_Sv_decays_3B(m_in,i1,MAhinput,MAh2input,MChainput,            & 
& MCha2input,MChiinput,MChi2input,MFdinput,MFd2input,MFeinput,MFe2input,MFuinput,        & 
& MFu2input,MGluinput,MGlu2input,Mhhinput,Mhh2input,MHpminput,MHpm2input,MSdinput,       & 
& MSd2input,MSeinput,MSe2input,MSuinput,MSu2input,MSvinput,MSv2input,MVWminput,          & 
& MVWm2input,MVZinput,MVZ2input,pGinput,TWinput,UMinput,UPinput,vinput,ZAinput,          & 
& ZDinput,ZDLinput,ZDRinput,ZEinput,ZELinput,ZERinput,ZHinput,ZNinput,ZPinput,           & 
& ZUinput,ZULinput,ZURinput,ZVinput,ZWinput,ZZinput,alphaHinput,betaHinput,              & 
& g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,Tdinput,Teinput,               & 
& Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,              & 
& me2input,M1input,M2input,M3input,vdinput,vuinput,cplcChacFvSeL,cplcChacFvSeR,          & 
& cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplcChaChiHpmL,cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFecSvL,             & 
& cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdhhL,         & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,            & 
& cplcFdFuVWmR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFuhhL,          & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,           & 
& cplcFvFecHpmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,          & 
& cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,     & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplhhSvcSv,           & 
& cplSecHpmcSv,cplSecSvcVWm,cplSvcSvVZ,deltaM)

Implicit None 

Real(dp), Intent(in) :: m_in 
Real(dp), Intent(in) :: deltaM 
Integer, Intent(in) :: i1 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MChainput(2),MCha2input(2),MChiinput(4),MChi2input(4),       & 
& MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),MFu2input(3),            & 
& MGluinput,MGlu2input,Mhhinput(2),Mhh2input(2),MHpminput(2),MHpm2input(2),              & 
& MSdinput(6),MSd2input(6),MSeinput(6),MSe2input(6),MSuinput(6),MSu2input(6),            & 
& MSvinput(3),MSv2input(3),MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,              & 
& vinput,ZAinput(2,2),ZHinput(2,2),ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: pGinput,UMinput(2,2),UPinput(2,2),ZDinput(6,6),ZDLinput(3,3),ZDRinput(3,3),           & 
& ZEinput(6,6),ZELinput(3,3),ZERinput(3,3),ZNinput(4,4),ZUinput(6,6),ZULinput(3,3),      & 
& ZURinput(3,3),ZVinput(3,3),ZWinput(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp),Intent(out) :: cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),  & 
& cplcChaChahhL(2,2,2),cplcChaChahhR(2,2,2),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),       & 
& cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),cplcChaChiVWmL(2,4),cplcChaChiVWmR(2,4),   & 
& cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),     & 
& cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),         & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),             & 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),           & 
& cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),         & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),               & 
& cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),           & 
& cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),         & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvChiSvL(3,4,3),cplcFvChiSvR(3,4,3),             & 
& cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),           & 
& cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),       & 
& cplChiChacHpmL(4,2,2),cplChiChacHpmR(4,2,2),cplChiChiAhL(4,4,2),cplChiChiAhR(4,4,2),   & 
& cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),cplChiChiVZR(4,4),           & 
& cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),       & 
& cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),cplChiFvcSvR(4,3,3),       & 
& cplhhSvcSv(2,3,3),cplSecHpmcSv(6,2,3),cplSecSvcVWm(6,3),cplSvcSvVZ(3,3)

Real(dp) ::  g1D(215) 
Integer :: i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: gSM(11), sinW2, dt, tz, Qin 
Iname = Iname + 1 
NameOfUnit(Iname) = 'Couplings_Sv_3B'
 
sinW2=1._dp-mW2/mZ2 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
Yu = Yuinput 
Mu = Muinput 
Td = Tdinput 
Te = Teinput 
Tu = Tuinput 
Bmu = Bmuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
Qin=sqrt(getRenormalizationScale()) 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,g1D)

If ((m_in.le.Qin).and.(RunningCouplingsDecays)) Then 
  tz=Log(m_in/Qin) 
  If (m_in.le.mz) tz=Log(mz/Qin)  
  dt=tz/50._dp 
  Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 
Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

! --- Calculate running tree-level masses for loop induced couplings and Quark mixing matrices --- 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

ZH = ZHinput 
ZA = ZAinput 
! --- Use the 1-loop mixing matrices calculated at M_SUSY in the vertices --- 
UM = UMinput 
UP = UPinput 
ZA = ZAinput 
ZD = ZDinput 
ZE = ZEinput 
ZH = ZHinput 
ZN = ZNinput 
ZP = ZPinput 
ZU = ZUinput 
ZV = ZVinput 
ZW = ZWinput 
ZZ = ZZinput 
cplhhSvcSv = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplinghhSvcSvT(gt1,gt2,gt3,g1,g2,vd,vu,ZH,cplhhSvcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecHpmcSv = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingSecHpmcSvT(gt1,gt2,gt3,g2,Mu,Ye,Te,vd,vu,ZV,ZE,ZP,cplSecHpmcSv(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSecSvcVWm = 0._dp 
Do gt1 = 1, 6
 Do gt2 = 1, 3
Call CouplingSecSvcVWmT(gt1,gt2,g2,ZV,ZE,cplSecSvcVWm(gt1,gt2))

 End Do 
End Do 


cplSvcSvVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingSvcSvVZT(gt1,gt2,g1,g2,TW,cplSvcSvVZ(gt1,gt2))

 End Do 
End Do 


cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)            & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)              & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFucSdL = 0._dp 
cplChaFucSdR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFucSdT(gt1,gt2,gt3,g2,Yd,Yu,ZD,UM,UP,ZUL,ZUR,cplChaFucSdL(gt1,gt2,gt3)& 
& ,cplChaFucSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)            & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChaSuL = 0._dp 
cplcFdChaSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 6
Call CouplingcFdChaSuT(gt1,gt2,gt3,g2,Yd,Yu,ZU,UM,UP,ZDL,ZDR,cplcFdChaSuL(gt1,gt2,gt3)& 
& ,cplcFdChaSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChaSvL = 0._dp 
cplcFeChaSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcFeChaSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcFeChaSvL(gt1,gt2,gt3)   & 
& ,cplcFeChaSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)              & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFdcSdL = 0._dp 
cplChiFdcSdR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFdcSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplChiFdcSdL(gt1,gt2,gt3)   & 
& ,cplChiFdcSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFucSuL = 0._dp 
cplChiFucSuR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFucSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplChiFucSuL(gt1,gt2,gt3)   & 
& ,cplChiFucSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdChiSdL = 0._dp 
cplcFdChiSdR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFdChiSdT(gt1,gt2,gt3,g1,g2,Yd,ZD,ZN,ZDL,ZDR,cplcFdChiSdL(gt1,gt2,gt3)   & 
& ,cplcFdChiSdR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChiSeL = 0._dp 
cplcFeChiSeR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFeChiSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplcFeChiSeL(gt1,gt2,gt3)   & 
& ,cplcFeChiSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuChiSuL = 0._dp 
cplcFuChiSuR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFuChiSuT(gt1,gt2,gt3,g1,g2,Yu,ZU,ZN,ZUL,ZUR,cplcFuChiSuL(gt1,gt2,gt3)   & 
& ,cplcFuChiSuR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3) & 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3),               & 
& cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChacFvSeL = 0._dp 
cplcChacFvSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFvSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplcChacFvSeL(gt1,gt2,gt3)            & 
& ,cplcChacFvSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 4
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFuVWmL = 0._dp 
cplcFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFuVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFdFuVWmL(gt1,gt2),cplcFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvVWmL = 0._dp 
cplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,cplcFeFvVWmL(gt1,gt2),cplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
 
End subroutine CouplingsFor_Sv_decays_3B
 
Function NFlav(m_in) 
Implicit None 
Real(dp), Intent(in) :: m_in 
Real(dp) :: NFlav 
If (m_in.lt.mf_d(3)) Then 
  NFlav = 4._dp 
Else If (m_in.lt.mf_u(3)) Then 
  NFlav = 5._dp 
Else 
  NFlav = 6._dp 
End if 
End Function

Subroutine RunSM(scale_out,deltaM,tb,g1,g2,g3,Yu, Yd, Ye, vd, vu) 
Implicit None
Real(dp), Intent(in) :: scale_out,deltaM, tb
Real(dp), Intent(out) :: g1, g2, g3, vd, vu
Complex(dp), Intent(out) :: Yu(3,3), Yd(3,3), Ye(3,3)
Real(dp) :: dt, gSM(14), gSM2(2), gSM3(3), mtopMS,  sinw2, vev, tz, alphaStop 
Integer :: kont

Yd = 0._dp
Ye = 0._dp
Yu = 0._dp

If (.not.RunningTopMZ) Then

! Calculating alpha_S(m_top)
gSM2(1)=sqrt(Alpha_mZ*4*Pi) 
gSM2(2)=sqrt(AlphaS_mZ*4*Pi) 


tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM2,2,tz,0._dp,deltaM,dt,0._dp,RGEAlphaS,kont)



alphaStop = gSM2(2)**2/4._dp/Pi



! m_top^pole to m_top^MS(m_top) 

mtopMS = mf_u(3)*(1._dp - 4._dp/3._dp*alphaStop/Pi)


! Running m_top^MS(m_top) to M_Z 

gSM3(1)=gSM2(1) 
gSM3(2)=gSM2(2)
gSM3(3)=mtopMS

tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM3,3,0._dp,tz,deltaM,dt,0._dp,RGEtop,kont)


mf_u_mz_running = gSM3(3)


RunningTopMZ = .True.

End if

! Starting values at MZ

gSM(1)=sqrt(Alpha_mZ*4*Pi) 
gSM(2)=sqrt(AlphaS_mZ*4*Pi) 
gSM(3)= 0.486E-03_dp ! mf_l_mz(1) 
gSM(4)= 0.10272 !mf_l_mz(2) 
gSM(5)= 1.74624 !mf_l_mz(3) 
gSM(6)= 1.27E-03_dp ! mf_u_mz(1) 
gSM(7)= 0.619  ! mf_u_mz(2) 
gSM(8)= mf_u_mz_running ! m_top 
gSM(9)= 2.9E-03_dp !mf_d_mz(1) 
gSM(10)= 0.055 !mf_d_mz(2) 
gSM(11)= 2.85 ! mf_d_mz(3) 
 

! To get the running sin(w2) 
SinW2 = 0.22290_dp
gSM(12) = 5._dp/3._dp*Alpha_MZ/(1-sinW2)
gSM(13) = Alpha_MZ/Sinw2
gSM(14) = AlphaS_mZ

  nUp =2._dp 
  nDown =3._dp 
  nLep =3._dp 
 

If (scale_out.gt.sqrt(mz2)) Then

 ! From M_Z to Min(M_top,scale_out) 
 If (scale_out.gt.mf_u(3)) Then 
  tz=Log(sqrt(mz2)/mf_u(3)) 
  dt=tz/50._dp 
 Else 
  tz=Log(sqrt(mz2)/scale_out) 
  dt=tz/50._dp 
 End if 

  Call odeint(gSM,14,tz,0._dp,deltaM,dt,0._dp,rge11,kont)


 ! From M_top to M_SUSY if M_top < M_SUSY 
 If (scale_out.gt.mf_u(3)) Then 
  tz=Log(mf_u(3)/scale_out) 
  dt=tz/50._dp 
  nUp =3._dp 
  Call odeint(gSM,14,tz,0._dp,deltaM,dt,0._dp,rge11,kont)
 End if 
Else

 ! From M_Z down to scale_out
  tz=Log(scale_out/sqrt(mz2)) 
  dt=tz/50._dp 
  Call odeint(gSM,14,0._dp,tz,deltaM,dt,0._dp,rge11_SMa,kont)

End if

! Calculating Couplings 

 sinW2=1._dp-mW2/mZ2 
 vev=Sqrt(mZ2*(1._dp-sinW2)*SinW2/(gSM(1)**2/4._dp))
 vd=vev/Sqrt(1._dp+tb**2)
 vu=tb*vd
 
Yd(1,1) =gSM(9)*sqrt(2._dp)/vd 
Yd(2,2) =gSM(10)*sqrt(2._dp)/vd 
Yd(3,3) =gSM(11)*sqrt(2._dp)/vd 
Ye(1,1) =gSM(3)*sqrt(2._dp)/vd 
Ye(2,2)=gSM(4)*sqrt(2._dp)/vd 
Ye(3,3)=gSM(5)*sqrt(2._dp)/vd 
Yu(1,1)=gSM(6)*sqrt(2._dp)/vu 
Yu(2,2)=gSM(7)*sqrt(2._dp)/vu 
Yu(3,3)=gSM(8)*sqrt(2._dp)/vu 


g3 =gSM(2) 
g3running=gSM(2) 

g1 = sqrt(gSM(12)*4._dp*Pi*3._dp/5._dp)
g2 = sqrt(gSM(13)*4._dp*Pi)
! g3 = sqrt(gSM(3)*4._dp*Pi)

sinw2 = g1**2/(g1**2 + g2**2)

!g2=gSM(1)/sqrt(sinW2) 
!g1 = g2*Sqrt(sinW2/(1._dp-sinW2)) 

If (GenerationMixing) Then 
If (TransposedYukawa) Then ! check, if superpotential is Yu Hu u q  or Yu Hu q u
 Yu= Matmul(Transpose(CKM),Transpose(Yu))
Else 
 Yu=Transpose(Matmul(Transpose(CKM),Transpose(Yu)))
End if 
End If


End Subroutine RunSM


Subroutine RunSMohdm(scale_out,deltaM,g1,g2,g3,Yu, Yd, Ye, v) 
Implicit None
Real(dp), Intent(in) :: scale_out,deltaM
Real(dp), Intent(out) :: g1, g2, g3, v
Complex(dp), Intent(out) :: Yu(3,3), Yd(3,3), Ye(3,3)
Real(dp) :: dt, gSM(14), gSM2(2), gSM3(3), mtopMS,  sinw2, vev, tz, alphaStop 
Integer :: kont

Yd = 0._dp
Ye = 0._dp
Yu = 0._dp

If (.not.RunningTopMZ) Then

! Calculating alpha_S(m_top)
gSM2(1)=sqrt(Alpha_mZ*4*Pi) 
gSM2(2)=sqrt(AlphaS_mZ*4*Pi) 


tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM2,2,tz,0._dp,deltaM,dt,0._dp,RGEAlphaS,kont)



alphaStop = gSM2(2)**2/4._dp/Pi



! m_top^pole to m_top^MS(m_top) 

mtopMS = mf_u(3)*(1._dp - 4._dp/3._dp*alphaStop/Pi)


! Running m_top^MS(m_top) to M_Z 

gSM3(1)=gSM2(1) 
gSM3(2)=gSM2(2)
gSM3(3)=mtopMS

tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM3,3,0._dp,tz,deltaM,dt,0._dp,RGEtop,kont)


mf_u_mz_running = gSM3(3)


RunningTopMZ = .True.

End if

! Starting values at MZ

gSM(1)=sqrt(Alpha_mZ*4*Pi) 
gSM(2)=sqrt(AlphaS_mZ*4*Pi) 
gSM(3)= 0.486E-03_dp ! mf_l_mz(1) 
gSM(4)= 0.10272 !mf_l_mz(2) 
gSM(5)= 1.74624 !mf_l_mz(3) 
gSM(6)= 1.27E-03_dp ! mf_u_mz(1) 
gSM(7)= 0.619  ! mf_u_mz(2) 
gSM(8)= mf_u_mz_running ! m_top 
gSM(9)= 2.9E-03_dp !mf_d_mz(1) 
gSM(10)= 0.055 !mf_d_mz(2) 
gSM(11)= 2.85 ! mf_d_mz(3) 
 

! To get the running sin(w2) 
SinW2 = 0.22290_dp
gSM(12) = 5._dp/3._dp*Alpha_MZ/(1-sinW2)
gSM(13) = Alpha_MZ/Sinw2
gSM(14) = AlphaS_mZ

  nUp =2._dp 
  nDown =3._dp 
  nLep =3._dp 
 

If (scale_out.gt.sqrt(mz2)) Then

 ! From M_Z to Min(M_top,scale_out) 
 If (scale_out.gt.mf_u(3)) Then 
  tz=Log(sqrt(mz2)/mf_u(3)) 
  dt=tz/50._dp 
 Else 
  tz=Log(sqrt(mz2)/scale_out) 
  dt=tz/50._dp 
 End if 

  Call odeint(gSM,14,tz,0._dp,deltaM,dt,0._dp,rge11,kont)


 ! From M_top to M_SUSY if M_top < M_SUSY 
 If (scale_out.gt.mf_u(3)) Then 
  tz=Log(mf_u(3)/scale_out) 
  dt=tz/50._dp 
  nUp =3._dp 
  Call odeint(gSM,14,tz,0._dp,deltaM,dt,0._dp,rge11,kont)
 End if 
Else

 ! From M_Z down to scale_out
  tz=Log(scale_out/sqrt(mz2)) 
  dt=tz/50._dp 
  Call odeint(gSM,14,0._dp,tz,deltaM,dt,0._dp,rge11_SMa,kont)

End if

! Calculating Couplings 

 sinW2=1._dp-mW2/mZ2 
 vev=Sqrt(mZ2*(1._dp-sinW2)*SinW2/(gSM(1)**2/4._dp))
 v = vev
 
Yd(1,1) =gSM(9)*sqrt(2._dp)/v 
Yd(2,2) =gSM(10)*sqrt(2._dp)/v 
Yd(3,3) =gSM(11)*sqrt(2._dp)/v 
Ye(1,1) =gSM(3)*sqrt(2._dp)/v 
Ye(2,2)=gSM(4)*sqrt(2._dp)/v 
Ye(3,3)=gSM(5)*sqrt(2._dp)/v 
Yu(1,1)=gSM(6)*sqrt(2._dp)/v 
Yu(2,2)=gSM(7)*sqrt(2._dp)/v 
Yu(3,3)=gSM(8)*sqrt(2._dp)/v 


g3 =gSM(2) 
g3running=gSM(2) 

g1 = sqrt(gSM(12)*4._dp*Pi*3._dp/5._dp)
g2 = sqrt(gSM(13)*4._dp*Pi)
! g3 = sqrt(gSM(3)*4._dp*Pi)

sinw2 = g1**2/(g1**2 + g2**2)

g2=gSM(1)/sqrt(sinW2) 
g1 = g2*Sqrt(sinW2/(1._dp-sinW2)) 

If (GenerationMixing) Then 
If (TransposedYukawa) Then ! check, if superpotential is Yu Hu u q  or Yu Hu q u
 Yu= Matmul(Transpose(CKM),Transpose(Yu))
Else 
 Yu=Transpose(Matmul(Transpose(CKM),Transpose(Yu)))
End if 
End If


End Subroutine RunSMohdm

Subroutine RunSMgauge(scale_out,deltaM,g1,g2,g3) 
Implicit None
Real(dp), Intent(in) :: scale_out,deltaM
Real(dp), Intent(out) :: g1, g2, g3
Complex(dp) :: Yu(3,3), Yd(3,3), Ye(3,3)
Real(dp) :: v, dt, gSM(14), gSM2(2), gSM3(3), mtopMS,  sinw2, vev, tz, alphaStop 
Integer :: kont

Yd = 0._dp
Ye = 0._dp
Yu = 0._dp

If (.not.RunningTopMZ) Then

! Calculating alpha_S(m_top)
gSM2(1)=sqrt(Alpha_mZ*4*Pi) 
gSM2(2)=sqrt(AlphaS_mZ*4*Pi) 


tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM2,2,tz,0._dp,deltaM,dt,0._dp,RGEAlphaS,kont)



alphaStop = gSM2(2)**2/4._dp/Pi



! m_top^pole to m_top^MS(m_top) 

mtopMS = mf_u(3)*(1._dp - 4._dp/3._dp*alphaStop/Pi)


! Running m_top^MS(m_top) to M_Z 

gSM3(1)=gSM2(1) 
gSM3(2)=gSM2(2)
gSM3(3)=mtopMS

tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM3,3,0._dp,tz,deltaM,dt,0._dp,RGEtop,kont)


mf_u_mz_running = gSM3(3)


RunningTopMZ = .True.

End if

! Starting values at MZ

gSM(1)=sqrt(Alpha_mZ*4*Pi) 
gSM(2)=sqrt(AlphaS_mZ*4*Pi) 
gSM(3)= 0.486E-03_dp ! mf_l_mz(1) 
gSM(4)= 0.10272 !mf_l_mz(2) 
gSM(5)= 1.74624 !mf_l_mz(3) 
gSM(6)= 1.27E-03_dp ! mf_u_mz(1) 
gSM(7)= 0.619  ! mf_u_mz(2) 
gSM(8)= mf_u_mz_running ! m_top 
gSM(9)= 2.9E-03_dp !mf_d_mz(1) 
gSM(10)= 0.055 !mf_d_mz(2) 
gSM(11)= 2.85 ! mf_d_mz(3) 
 

! To get the running sin(w2) 
SinW2 = 0.22290_dp
gSM(12) = 5._dp/3._dp*Alpha_MZ/(1-sinW2)
gSM(13) = Alpha_MZ/Sinw2
gSM(14) = AlphaS_mZ

  nUp =2._dp 
  nDown =3._dp 
  nLep =3._dp 
 

If (scale_out.gt.sqrt(mz2)) Then

 ! From M_Z to Min(M_top,scale_out) 
 If (scale_out.gt.mf_u(3)) Then 
  tz=Log(sqrt(mz2)/mf_u(3)) 
  dt=tz/50._dp 
 Else 
  tz=Log(sqrt(mz2)/scale_out) 
  dt=tz/50._dp 
 End if 

  Call odeint(gSM,14,tz,0._dp,deltaM,dt,0._dp,rge11,kont)


 ! From M_top to M_SUSY if M_top < M_SUSY 
 If (scale_out.gt.mf_u(3)) Then 
  tz=Log(mf_u(3)/scale_out) 
  dt=tz/50._dp 
  nUp =3._dp 
  Call odeint(gSM,14,tz,0._dp,deltaM,dt,0._dp,rge11,kont)
 End if 
Else

 ! From M_Z down to scale_out
  tz=Log(scale_out/sqrt(mz2)) 
  dt=tz/50._dp 
  Call odeint(gSM,14,0._dp,tz,deltaM,dt,0._dp,rge11_SMa,kont)

End if

! Calculating Couplings 

 sinW2=1._dp-mW2/mZ2 
 vev=Sqrt(mZ2*(1._dp-sinW2)*SinW2/(gSM(1)**2/4._dp))
 v = vev
 
Yd(1,1) =gSM(9)*sqrt(2._dp)/v 
Yd(2,2) =gSM(10)*sqrt(2._dp)/v 
Yd(3,3) =gSM(11)*sqrt(2._dp)/v 
Ye(1,1) =gSM(3)*sqrt(2._dp)/v 
Ye(2,2)=gSM(4)*sqrt(2._dp)/v 
Ye(3,3)=gSM(5)*sqrt(2._dp)/v 
Yu(1,1)=gSM(6)*sqrt(2._dp)/v 
Yu(2,2)=gSM(7)*sqrt(2._dp)/v 
Yu(3,3)=gSM(8)*sqrt(2._dp)/v 


g3 =gSM(2) 
g3running=gSM(2) 

g1 = sqrt(gSM(12)*4._dp*Pi*3._dp/5._dp)
g2 = sqrt(gSM(13)*4._dp*Pi)
! g3 = sqrt(gSM(3)*4._dp*Pi)

sinw2 = g1**2/(g1**2 + g2**2)

g2=gSM(1)/sqrt(sinW2) 
g1 = g2*Sqrt(sinW2/(1._dp-sinW2)) 

If (GenerationMixing) Then 
If (TransposedYukawa) Then ! check, if superpotential is Yu Hu u q  or Yu Hu q u
 Yu= Matmul(Transpose(CKM),Transpose(Yu))
Else 
 Yu=Transpose(Matmul(Transpose(CKM),Transpose(Yu)))
End if 
End If


End Subroutine RunSMgauge
End Module CouplingsForDecays_MSSM
