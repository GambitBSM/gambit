! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:03 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module FineTuning_MSSM 
 
Use Control 
Use LoopFunctions 
Use Mathematics 
Use Model_Data_MSSM 
Use RGEs_MSSM 
Use LoopMasses_MSSM 
Use SusyMasses_MSSM 
Use Couplings_MSSM 
Use Tadpoles_MSSM 
 Use StandardModel 
 
Contains 

Subroutine FineTuning(g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,        & 
& Tdinput,Teinput,Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,       & 
& mu2input,me2input,M1input,M2input,M3input,vdinput,vuinput,mGut,kont)

Implicit None 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp), Intent(in) :: mGUT 
Integer, Intent(inout) :: kont 
Integer :: i1, Fpar 
Real(dp) :: delta0,gA(213), gB(213), gC(215), gRef(213), gDiff(213)
Real(dp) :: MZ2ref, MZ2current, variation, stepsize, dt, tz, factor 
Real(dp) :: vdref, vuref, maxdiff 
Real(dp) :: m_lo, m_hi 
Logical :: NumericalProblem, GenerationMixingSave 
Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp) :: Tad1Loop(2), dmz2, mudim 

Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp) :: cplAhAhcVWmVWm(2,2),cplAhAhVZVZ(2,2),cplAhhhVZ(2,2),cplAhHpmcVWm(2,2),cplcChaChaVZL(2,2),& 
& cplcChaChaVZR(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),& 
& cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),               & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplcgAgWmcVWm,cplcgWmgWmVZ,cplcgWpCgAcVWm,cplcgWpCgWpCVZ,cplcgWpCgZcVWm,               & 
& cplcgZgWmcVWm,cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChiVZL(4,4),               & 
& cplChiChiVZR(4,4),cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,            & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWm,cplcVWmVWmVZ,             & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),   & 
& cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplGluGluVGL,cplGluGluVGR,cplhhcVWmVWm(2),         & 
& cplhhhhcVWmVWm(2,2),cplhhhhVZVZ(2,2),cplhhHpmcVWm(2,2),cplhhVZVZ(2),cplHpmcHpmcVWmVWm(2,2),& 
& cplHpmcHpmVZ(2,2),cplHpmcHpmVZVZ(2,2),cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplSdcSdcVWmVWm(6,6),& 
& cplSdcSdVZ(6,6),cplSdcSdVZVZ(6,6),cplSdcSucVWm(6,6),cplSecSecVWmVWm(6,6),              & 
& cplSecSeVZ(6,6),cplSecSeVZVZ(6,6),cplSecSvcVWm(6,3),cplSucSucVWmVWm(6,6),              & 
& cplSucSuVZ(6,6),cplSucSuVZVZ(6,6),cplSvcSvcVWmVWm(3,3),cplSvcSvVZ(3,3),cplSvcSvVZVZ(3,3)

Write(*,*) "Calculate FineTuning" 
NumericalProblem = .False. 
GenerationMixingSave=GenerationMixing 
GenerationMixing= .false. 
Tad1Loop = 0._dp 
stepsize = 1.0E-5_dp 
 
delta0 = stepsize/1000._dp
 
variation = 1._dp + stepsize 
 
mudim = GetRenormalizationScale() 
 
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
! ------------------------- 
! Initialization 
! ----------------------- 
 
Fpar = 0 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,vd,vu,gC)

Call GToParameters215(gC,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,Tad1Loop)

! First Run to GUT scale and back to get reference 
Do i1=1,100 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG213(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,gA)

tz=Log(sqrt(mudim)/mGUT)
dt=-tz/50._dp
Call odeint(gA,213,tz,0._dp,0.001_dp*delta0,dt,0._dp,rge213,kont)
Call BoundaryFT(gA,gB,0,variation)
tz=Log(sqrt(mudim)/mGUT)
dt=tz/50._dp
Call odeint(gB,213,0._dp,tz,0.001_dp*delta0,dt,0._dp,rge213,kont)
Call GToParameters213(gB,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
gDiff=Abs(gB-gRef) 
Where (Abs(gDiff).lt.1E-12_dp) gDiff=0._dp 
Where (Abs(gRef).Gt.0._dp) gDiff=gDiff/Abs(gRef) 
maxdiff=Maxval(gDiff) 
If (Abs(maxdiff).gt.delta0) Then 
gRef = gB 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,Tad1Loop)

Else 
Exit 
End if 
End Do 

 ! Calculate VEVs 
Call SolveTadpoleEquationsVEVs(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,Tad1Loop)



 ! Calculate reference value for MZ  
MZ2ref = 1._dp/4._dp*(g1**2 + g2**2)*( vd**2 + vu**2) 
vdref = vd
vuref = vu
If (OneLoopFT) Then 

 ! One-Loop correction 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.False.,kont)

Call CouplingsForVectorBosons(g1,g2,ZH,ZA,TW,UM,UP,ZN,vd,vu,ZP,ZD,ZE,ZU,              & 
& ZDL,ZUL,ZEL,ZV,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,        & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm, & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,     & 
& cplSdcSucVWm,cplSecSvcVWm,cplcVWmVPVWm,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,& 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm1,       & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)

Call Pi1LoopVZ(MZ2ref,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,               & 
& MFe,MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmZ2)

MZ2ref = MZ2ref+Real(dmz2,dp) 
End if 
If (i1.gt.99) Then 
 NumericalProblem = .true. 
Write(*,*) "RGEs haven't converged with needed precission" 
End if 
If (MZ2ref.lt.1000._dp) Then 
 NumericalProblem = .true. 
Write(*,*) "Numerical problem in solving tadpole equations with respect to VEVs." 
End if 


! ----------------------------- 
! Calculate Fine-Tuning 
! -------------------------- 
 
Do i1=1,5 
 
! RGE running 
Fpar = i1 
vd = vdMZ 
vu = vuMZ 
Call BoundaryFT(gA,gB,i1,variation)
tz=Log(sqrt(mudim)/mGUT)
dt=tz/50._dp
Call odeint(gB,213,0._dp,tz,0.001_dp*delta0,dt,0._dp,rge213,kont)
Call GToParameters213(gB,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Select Case(i1) 
  Case(1) 
    factor = 1._dp/2._dp 
  Case(2) 
    factor = 1 
  Case(3) 
    factor = 1 
  Case(4) 
    factor = 1 
  Case(5) 
    factor = 1 
End Select 


 ! Calculate VEVs 
Call SolveTadpoleEquationsVEVs(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,Tad1Loop)



 ! Calculate FineTuning 
MZ2current = 1._dp/4._dp*(g1**2 + g2**2)*( vd**2 + vu**2) 
If (OneLoopFT) Then 

 ! One-Loop correction 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,.False.,kont)

Call CouplingsForVectorBosons(g1,g2,ZH,ZA,TW,UM,UP,ZN,vd,vu,ZP,ZD,ZE,ZU,              & 
& ZDL,ZUL,ZEL,ZV,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,        & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm, & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,     & 
& cplSdcSucVWm,cplSecSvcVWm,cplcVWmVPVWm,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,& 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm1,       & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)

Call Pi1LoopVZ(MZ2current,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,           & 
& MFe,MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,           & 
& MSv,MSv2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,              & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmZ2)

MZ2current = MZ2current + Real(dmz2,dp) 
End if 
If ((MZ2Current.lt.500._dp).or.(MZ2Current.gt.100000._dp)) Then 
Write(*,*) " Large deviation in Z mass in fine-tuning routine: ", sqrt(MZ2Current) 
Write(*,*) " That's most likely a numerical problem! " 
 NumericalProblem = .true. 
End If 
If (NumericalProblem) Then 
 FineTuningResultsAllVEVs(i1) = -1._dp 
Else 
 FineTuningResultsAllVEVs(i1) = 0.5_dp*Abs((MZ2current-MZ2ref)/(MZ2ref))/stepsize*factor 
End If 
! Write(*,*) sqrt((Real(vu-vuref,dp)**2+Real(vd-vdref,dp)**2)/(vdref**2+vuref**2))/stepsize*factor 
End Do 
GenerationMixing = GenerationMixingSave 
End Subroutine FineTuning 
Subroutine BoundaryFT(gA,gB,FTpar,variation) 
Implicit None 
Real(dp),Intent(in)::gA(:)
Real(dp),Intent(out)::gB(:)
Integer, Intent(in) :: FTpar
Real(dp), Intent(in) :: variation 
Complex(dp) :: savePar 
Integer::i1,i2
Real(dp) :: g1,g2,g3

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3)

Real(dp) :: mHd2,mHu2

Complex(dp) :: Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Iname=Iname+1
NameOfUnit(Iname)='BoundaryFT'
Call GToParameters213(gA,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3)

Select Case(FTpar) 
Case (1) 
   savePar = m0 
   m0 = variation*m0 
Case (2) 
   savePar = m12 
   m12 = variation*m12 
Case (3) 
   savePar = Azero 
   Azero = variation*Azero 
End Select 
Select Case(BoundaryCondition) 
Case (1) 
If (InputValueforTe) Then 
Te = TeIN 
Else 
Te = Azero*Ye
End If 
If (InputValueforTd) Then 
Td = TdIN 
Else 
Td = Azero*Yd
End If 
If (InputValueforTu) Then 
Tu = TuIN 
Else 
Tu = Azero*Yu
End If 
If (InputValueformq2) Then 
mq2 = mq2IN 
Else 
mq2 = 0._dp 
Do i1=1,3
mq2(i1,i1) = m0**2
End Do
End If 
If (InputValueforml2) Then 
ml2 = ml2IN 
Else 
ml2 = 0._dp 
Do i1=1,3
ml2(i1,i1) = m0**2
End Do
End If 
If (InputValueformd2) Then 
md2 = md2IN 
Else 
md2 = 0._dp 
Do i1=1,3
md2(i1,i1) = m0**2
End Do
End If 
If (InputValueformu2) Then 
mu2 = mu2IN 
Else 
mu2 = 0._dp 
Do i1=1,3
mu2(i1,i1) = m0**2
End Do
End If 
If (InputValueforme2) Then 
me2 = me2IN 
Else 
me2 = 0._dp 
Do i1=1,3
me2(i1,i1) = m0**2
End Do
End If 
If (InputValueformHd2) Then 
mHd2 = mHd2IN 
Else 
mHd2 = m0**2
End If 
If (InputValueformHu2) Then 
mHu2 = mHu2IN 
Else 
mHu2 = m0**2
End If 
If (InputValueforM1) Then 
M1 = M1IN 
Else 
M1 = m12
End If 
If (InputValueforM2) Then 
M2 = M2IN 
Else 
M2 = m12
End If 
If (InputValueforM3) Then 
M3 = M3IN 
Else 
M3 = m12
End If 
If (InputValueforMu) Then 
Mu = MuIN 
Else 
End If 
If (InputValueforBmu) Then 
Bmu = BmuIN 
Else 
End If 
Case (2) 
If (InputValueforTe) Then 
Te = TeIN 
Else 
Te = 0
End If 
If (InputValueforTd) Then 
Td = TdIN 
Else 
Td = 0
End If 
If (InputValueforTu) Then 
Tu = TuIN 
Else 
Tu = 0
End If 
If (InputValueformHd2) Then 
mHd2 = mHd2IN 
Else 
mHd2 = ((0.3_dp*g1**4 + 1.5_dp*g2**4)*LambdaInput**2*(3._dp*(n10plets) + n5plets)*fGMSB(LambdaInput/MessengerScale))/(256._dp*Pi**4)
End If 
If (InputValueformHu2) Then 
mHu2 = mHu2IN 
Else 
mHu2 = mHd2
End If 
If (InputValueformq2) Then 
mq2 = mq2IN 
Else 
mq2 = 0._dp 
Do i1=1,3
mq2(i1,i1) = ((0.0333333_dp*g1**4 + 1.5_dp*g2**4 + 2.66667_dp*g3**4)*LambdaInput**2*(3._dp*(n10plets) + n5plets)*fGMSB(LambdaInput/MessengerScale))/(256._dp*Pi**4)
End Do
End If 
If (InputValueforml2) Then 
ml2 = ml2IN 
Else 
ml2 = 0._dp 
Do i1=1,3
ml2(i1,i1) = mHd2
End Do
End If 
If (InputValueformd2) Then 
md2 = md2IN 
Else 
md2 = 0._dp 
Do i1=1,3
md2(i1,i1) = ((0.133333_dp*g1**4 + 2.66667_dp*g3**4)*LambdaInput**2*(3._dp*(n10plets) + n5plets)*fGMSB(LambdaInput/MessengerScale))/(256._dp*Pi**4)
End Do
End If 
If (InputValueformu2) Then 
mu2 = mu2IN 
Else 
mu2 = 0._dp 
Do i1=1,3
mu2(i1,i1) = ((0.533333_dp*g1**4 + 2.66667_dp*g3**4)*LambdaInput**2*(3._dp*(n10plets) + n5plets)*fGMSB(LambdaInput/MessengerScale))/(256._dp*Pi**4)
End Do
End If 
If (InputValueforme2) Then 
me2 = me2IN 
Else 
me2 = 0._dp 
Do i1=1,3
me2(i1,i1) = 0.0000481218_dp*g1**4*LambdaInput**2*(3._dp*(n10plets) + n5plets)*fGMSB(LambdaInput/MessengerScale)
End Do
End If 
If (InputValueforM1) Then 
M1 = M1IN 
Else 
M1 = (g1**2*LambdaInput*(3._dp*(n10plets) + n5plets)*gGMSB(LambdaInput/MessengerScale))/(16._dp*Pi**2)
End If 
If (InputValueforM2) Then 
M2 = M2IN 
Else 
M2 = (g2**2*LambdaInput*(3._dp*(n10plets) + n5plets)*gGMSB(LambdaInput/MessengerScale))/(16._dp*Pi**2)
End If 
If (InputValueforM3) Then 
M3 = M3IN 
Else 
M3 = (g3**2*LambdaInput*(3._dp*(n10plets) + n5plets)*gGMSB(LambdaInput/MessengerScale))/(16._dp*Pi**2)
End If 
If (InputValueforMu) Then 
Mu = MuIN 
Else 
End If 
If (InputValueforBmu) Then 
Bmu = BmuIN 
Else 
End If 
End Select 
Select Case(FTpar) 
Case (1) 
   m0 = savePar 
Case (2) 
   m12 = savePar 
Case (3) 
   Azero = savePar 
Case (4) 
   Mu = variation*Mu 
Case (5) 
   Bmu = variation*Bmu 
End Select 
Call ParametersToG213(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,            & 
& md2,mu2,me2,M1,M2,M3,gB)

Iname=Iname-1
End Subroutine BoundaryFT 
 
End Module FineTuning_MSSM 
