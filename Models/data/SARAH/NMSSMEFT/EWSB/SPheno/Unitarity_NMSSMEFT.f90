! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 14:02 on 29.10.2018   
! ----------------------------------------------------------------------  
 
 
Module Unitarity_NMSSMEFT 
 
Use Control 
Use Settings 
Use LoopFunctions 
Use Mathematics 
Use Model_Data_NMSSMEFT 
Use RGEs_NMSSMEFT 
Use LoopMasses_NMSSMEFT 
Use TreeLevelMasses_NMSSMEFT 
Use Couplings_NMSSMEFT 
Use Tadpoles_NMSSMEFT 
 Use StandardModel 
 
Logical :: IncludeGoldstoneContributions=.true. 
Logical :: IncludeGoldstoneExternal=.true. 
Logical :: AddR=.true. 
Real(dp) :: cut_elements = 0.0001_dp 
Real(dp) :: cut_amplitudes = 0.01_dp 
Logical :: Ignore_poles=.false. 
 
Contains 

Subroutine ScatteringEigenvalues(vdinput,vuinput,vSinput,g1input,g2input,             & 
& g3input,Ydinput,Yeinput,laminput,kapinput,Yuinput,Tdinput,Teinput,Tlaminput,           & 
& Tkinput,Tuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,mu2input,               & 
& me2input,ms2input,M1input,M2input,M3input,delta0,kont)

Implicit None 
Integer, Intent(inout) :: kont 
Integer :: ierr 
Real(dp) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp) :: vd,vu,vS

Real(dp) :: gD(221) 
Real(dp) :: tz,dt,q,q2,mudim 
Real(dp), Intent(in) :: delta0 
Integer :: iter 
Complex(dp) :: scatter_matrix(55,55) 
Complex(dp) :: rot_matrix(55,55) 
Real(dp) :: eigenvalues_matrix(55), test(2), unitarity_s, scattering_eigenvalue, step_size
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,ms2input,vdinput,vuinput,vSinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),laminput,kapinput,Yuinput(3,3),Tdinput(3,3),Teinput(3,3),   & 
& Tlaminput,Tkinput,Tuinput(3,3),mq2input(3,3),ml2input(3,3),md2input(3,3),              & 
& mu2input(3,3),me2input(3,3),M1input,M2input,M3input

max_scattering_eigenvalue = 0._dp 

g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
lam = laminput 
kap = kapinput 
Yu = Yuinput 
Td = Tdinput 
Te = Teinput 
Tlam = Tlaminput 
Tk = Tkinput 
Tu = Tuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
ms2 = ms2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
vS = vSinput 
If (unitarity_steps.eq.1) Then  
  step_size = 0._dp
Else  
 If (unitarity_steps.gt.0) Then 
  step_size = ((Abs(unitarity_s_max)) -(abs(unitarity_s_min)))/(1._dp*(Abs(unitarity_steps)-1)) 
 Else 
  step_size = (log(Abs(unitarity_s_max)) -log(abs(unitarity_s_min)))/(1._dp*(Abs(unitarity_steps)-1)) 
 End if 
End if 
Do iter=0,Abs(unitarity_steps)-1 
If (unitarity_steps.lt.0) Then 
  unitarity_s=exp(log(unitarity_s_min) + iter*step_size)**2 
Else 
  unitarity_s=(unitarity_s_min + iter*step_size)**2 
End if 
If (RunRGEs_unitarity) Then  
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
lam = laminput 
kap = kapinput 
Yu = Yuinput 
Td = Tdinput 
Te = Teinput 
Tlam = Tlaminput 
Tk = Tkinput 
Tu = Tuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
ms2 = ms2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
vS = vSinput 

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG221(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gD)

mudim=GetRenormalizationScale() 
tz=0.5_dp*Log(mudim/unitarity_s)
dt=-tz/50._dp
Call odeint(gD,221,tz,0._dp,0.1_dp*delta0,dt,0._dp,rge221,kont)
Call GToParameters221(gD,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

End if 
scatter_matrix=0._dp 
scatter_matrix(1,41) =(-g1**2 - g2**2)/4._dp
scatter_matrix(2,42) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(3,43) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(3,48) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(3,55) =sqrt(2._dp)*lam*Conjg(kap)
scatter_matrix(4,44) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(5,45) =-(lam*Conjg(lam))
scatter_matrix(6,6) =(-g1**2 - g2**2)/2._dp
scatter_matrix(6,16) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(6,25) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(6,33) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(6,40) =-(lam*Conjg(lam))
scatter_matrix(7,15) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(7,26) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(8,23) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(9,24) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(9,30) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(10,27) =2*lam*Conjg(kap)
scatter_matrix(10,36) =-(lam*Conjg(lam))
scatter_matrix(11,46) =(-g1**2 - g2**2)/4._dp
scatter_matrix(12,47) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(13,43) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(13,48) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(13,55) =-(sqrt(2._dp)*lam*Conjg(kap))
scatter_matrix(14,49) =-(lam*Conjg(lam))
scatter_matrix(15,7) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(15,32) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(16,6) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(16,16) =(-g1**2 - g2**2)/2._dp
scatter_matrix(16,25) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(16,33) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(16,40) =-(lam*Conjg(lam))
scatter_matrix(17,24) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(17,30) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(18,31) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(19,34) =-2*lam*Conjg(kap)
scatter_matrix(19,37) =-(lam*Conjg(lam))
scatter_matrix(20,50) =(-g1**2 - g2**2)/4._dp
scatter_matrix(21,51) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(22,52) =-(lam*Conjg(lam))
scatter_matrix(23,8) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(24,9) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(24,17) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(25,6) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(25,16) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(25,25) =(-g1**2 - g2**2)/2._dp
scatter_matrix(25,33) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(25,40) =-(lam*Conjg(lam))
scatter_matrix(26,7) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(26,32) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(27,10) =2*lam*Conjg(kap)
scatter_matrix(27,38) =-(lam*Conjg(lam))
scatter_matrix(28,53) =(-g1**2 - g2**2)/4._dp
scatter_matrix(29,54) =-(lam*Conjg(lam))
scatter_matrix(30,9) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(30,17) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(31,18) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(32,15) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(32,26) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(33,6) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(33,16) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(33,25) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(33,33) =(-g1**2 - g2**2)/2._dp
scatter_matrix(33,40) =-(lam*Conjg(lam))
scatter_matrix(34,19) =-2*lam*Conjg(kap)
scatter_matrix(34,39) =-(lam*Conjg(lam))
scatter_matrix(35,43) =sqrt(2._dp)*kap*Conjg(lam)
scatter_matrix(35,48) =-(sqrt(2._dp)*kap*Conjg(lam))
scatter_matrix(35,55) =-2*kap*Conjg(kap)
scatter_matrix(36,10) =-(lam*Conjg(lam))
scatter_matrix(36,38) =2*kap*Conjg(lam)
scatter_matrix(37,19) =-(lam*Conjg(lam))
scatter_matrix(37,39) =-2*kap*Conjg(lam)
scatter_matrix(38,27) =-(lam*Conjg(lam))
scatter_matrix(38,36) =2*kap*Conjg(lam)
scatter_matrix(39,34) =-(lam*Conjg(lam))
scatter_matrix(39,37) =-2*kap*Conjg(lam)
scatter_matrix(40,6) =-(lam*Conjg(lam))
scatter_matrix(40,16) =-(lam*Conjg(lam))
scatter_matrix(40,25) =-(lam*Conjg(lam))
scatter_matrix(40,33) =-(lam*Conjg(lam))
scatter_matrix(40,40) =-4*kap*Conjg(kap)
scatter_matrix(41,1) =(-g1**2 - g2**2)/4._dp
scatter_matrix(42,2) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(43,3) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(43,13) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(43,35) =sqrt(2._dp)*kap*Conjg(lam)
scatter_matrix(44,4) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(45,5) =-(lam*Conjg(lam))
scatter_matrix(46,11) =(-g1**2 - g2**2)/4._dp
scatter_matrix(47,12) =(g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(48,3) =-g2**2/2._dp + lam*Conjg(lam)
scatter_matrix(48,13) =(g1**2/2._dp + g2**2/2._dp)/2._dp - lam*Conjg(lam)
scatter_matrix(48,35) =-(sqrt(2._dp)*kap*Conjg(lam))
scatter_matrix(49,14) =-(lam*Conjg(lam))
scatter_matrix(50,20) =(-g1**2 - g2**2)/4._dp
scatter_matrix(51,21) =(-g1**2/2._dp - g2**2/2._dp)/2._dp
scatter_matrix(52,22) =-(lam*Conjg(lam))
scatter_matrix(53,28) =(-g1**2 - g2**2)/4._dp
scatter_matrix(54,29) =-(lam*Conjg(lam))
scatter_matrix(55,3) =sqrt(2._dp)*lam*Conjg(kap)
scatter_matrix(55,13) =-(sqrt(2._dp)*lam*Conjg(kap))
scatter_matrix(55,35) =-2*kap*Conjg(kap)
Call EigenSystem( oo16pi*scatter_matrix,eigenvalues_matrix,rot_matrix,ierr,test) 

scattering_eigenvalue=MaxVal(Abs(eigenvalues_matrix)) 
 If (scattering_eigenvalue.gt.max_scattering_eigenvalue) Then 
   max_scattering_eigenvalue=scattering_eigenvalue 
 End if 

End Do 
If (max_scattering_eigenvalue.gt.0.5_dp) TreeUnitarity=0._dp 
End Subroutine ScatteringEigenvalues

Subroutine ScatteringEigenvaluesWithTrilinears(vdinput,vuinput,vSinput,               & 
& g1input,g2input,g3input,Ydinput,Yeinput,laminput,kapinput,Yuinput,Tdinput,             & 
& Teinput,Tlaminput,Tkinput,Tuinput,mq2input,ml2input,mHd2input,mHu2input,               & 
& md2input,mu2input,me2input,ms2input,M1input,M2input,M3input,delta0,kont)

Implicit None 
Integer, Intent(inout) :: kont 
Integer :: ierr 
Logical :: Pole_Present, SPole_Present, TPole_Present, UPole_Present 
Integer :: RemoveTUpoles(99) 
Real(dp) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp) :: vd,vu,vS

Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplAhAhAhAh(3,3,3,3),cplAhAhAhhh(3,3,3,3),        & 
& cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhhhhhhh(3,3,3,3),cplAhhhHpmcHpm(3,3,2,2),& 
& cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),cplHpmHpmcHpmcHpm(2,2,2,2),               & 
& cplAhhhVZ(3,3),cplAhHpmcVWm(3,2),cplAhcHpmVWm(3,2),cplhhHpmcVWm(3,2),cplhhcHpmVWm(3,2),& 
& cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),cplhhcVWmVWm(3),cplhhVZVZ(3),cplHpmcVWmVP(2),      & 
& cplHpmcVWmVZ(2),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplAhAhcVWmVWm(3,3),cplAhAhVZVZ(3,3),  & 
& cplAhHpmcVWmVP(3,2),cplAhHpmcVWmVZ(3,2),cplAhcHpmVPVWm(3,2),cplAhcHpmVWmVZ(3,2),       & 
& cplhhhhcVWmVWm(3,3),cplhhhhVZVZ(3,3),cplhhHpmcVWmVP(3,2),cplhhHpmcVWmVZ(3,2),          & 
& cplhhcHpmVPVWm(3,2),cplhhcHpmVWmVZ(3,2),cplHpmcHpmVPVP(2,2),cplHpmcHpmVPVZ(2,2),       & 
& cplHpmcHpmcVWmVWm(2,2),cplHpmcHpmVZVZ(2,2),cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,        & 
& cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),     & 
& cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),           & 
& cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),     & 
& cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),     & 
& cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),     & 
& cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),       & 
& cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),       & 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),       & 
& cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),         & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),             & 
& cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),             & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),& 
& cplcFuFdcVWmR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),& 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),& 
& cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),& 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,& 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2, & 
& cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,         & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm, & 
& cplcgWmgWmAh(3),cplcgWpCgWpCAh(3),cplcgZgAhh(3),cplcgWmgAHpm(2),cplcgWpCgAcHpm(2),     & 
& cplcgWmgWmhh(3),cplcgZgWmcHpm(2),cplcgWpCgWpChh(3),cplcgZgWpCHpm(2),cplcgZgZhh(3),     & 
& cplcgWmgZHpm(2),cplcgWpCgZcHpm(2)

Real(dp) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(0),MSd2(0),MSe(0),          & 
& MSe2(0),MSu(0),MSu2(0),MSv(0),MSv2(0),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(3,3),ZH(3,3),        & 
& ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(0,0),ZDL(3,3),ZDR(3,3),ZE(0,0),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(0,0),ZUL(3,3),ZUR(3,3),ZV(0,0),ZW(2,2)

Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,ms2input,vdinput,vuinput,vSinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),laminput,kapinput,Yuinput(3,3),Tdinput(3,3),Teinput(3,3),   & 
& Tlaminput,Tkinput,Tuinput(3,3),mq2input(3,3),ml2input(3,3),md2input(3,3),              & 
& mu2input(3,3),me2input(3,3),M1input,M2input,M3input

Complex(dp) :: scatter_matrix1(25,25) 
Complex(dp) :: scatter_matrix1B(25,25) 
Complex(dp) :: rot_matrix1(25,25) 
Real(dp) :: eigenvalues_matrix1(25)
Complex(dp) :: scatter_matrix2(12,12) 
Complex(dp) :: scatter_matrix2B(12,12) 
Complex(dp) :: rot_matrix2(12,12) 
Real(dp) :: eigenvalues_matrix2(12)
Complex(dp) :: scatter_matrix3(3,3) 
Complex(dp) :: scatter_matrix3B(3,3) 
Complex(dp) :: rot_matrix3(3,3) 
Real(dp) :: eigenvalues_matrix3(3)
Real(dp) :: step_size,scattering_eigenvalue_trilinears, unitarity_s, test(2) 
Real(dp) :: gD(221) 
Real(dp) :: tz,dt,q,q2,mudim, max_element_removed  
Real(dp), Intent(in) :: delta0 
Integer :: iter, i, count 
max_scattering_eigenvalue_trilinears = 0._dp 
If (unitarity_steps.eq.1) Then  
  step_size = 0._dp
Else  
 If (unitarity_steps.gt.0) Then 
  step_size = ((Abs(unitarity_s_max)) -(abs(unitarity_s_min)))/(1._dp*(Abs(unitarity_steps)-1)) 
 Else 
  step_size = (log(Abs(unitarity_s_max)) -log(abs(unitarity_s_min)))/(1._dp*(Abs(unitarity_steps)-1)) 
 End if 
End if 
Do iter=0,Abs(unitarity_steps)-1 
If (unitarity_steps.lt.0) Then 
  unitarity_s=exp(log(unitarity_s_min) + iter*step_size)**2 
Else 
  unitarity_s=(unitarity_s_min + iter*step_size)**2 
End if 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Yd = Ydinput 
Ye = Yeinput 
lam = laminput 
kap = kapinput 
Yu = Yuinput 
Td = Tdinput 
Te = Teinput 
Tlam = Tlaminput 
Tk = Tkinput 
Tu = Tuinput 
mq2 = mq2input 
ml2 = ml2input 
mHd2 = mHd2input 
mHu2 = mHu2input 
md2 = md2input 
mu2 = mu2input 
me2 = me2input 
ms2 = ms2input 
M1 = M1input 
M2 = M2input 
M3 = M3input 
vd = vdinput 
vu = vuinput 
vS = vSinput 
If (RunRGEs_unitarity) Then  

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG221(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gD)

mudim=GetRenormalizationScale() 
tz=0.5_dp*Log(mudim/unitarity_s)
dt=-tz/50._dp
Call odeint(gD,221,tz,0._dp,0.1_dp*delta0,dt,0._dp,rge221,kont)
Call GToParameters221(gD,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

End if 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,           & 
& pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,             & 
& vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             & 
& mu2,me2,ms2,M1,M2,M3,.True.,kont)

Call AllCouplingsReallyAll(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,TW,g3,             & 
& UM,UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,               & 
& cplAhHpmcHpm,cplhhhhhh,cplhhHpmcHpm,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,               & 
& cplAhAhHpmcHpm,cplAhhhhhhh,cplAhhhHpmcHpm,cplhhhhhhhh,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm,& 
& cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,            & 
& cplHpmcHpmVZ,cplhhcVWmVWm,cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,            & 
& cplcHpmVWmVZ,cplAhAhcVWmVWm,cplAhAhVZVZ,cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,  & 
& cplAhcHpmVWmVZ,cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,               & 
& cplhhcHpmVPVWm,cplhhcHpmVWmVZ,cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,         & 
& cplHpmcHpmVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,     & 
& cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,               & 
& cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdVGL,     & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,            & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,            & 
& cplcFvFvVZR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,    & 
& cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,    & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3, & 
& cplcgGgGVG,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,               & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,       & 
& cplcgWpCgAcHpm,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,     & 
& cplcgWmgZHpm,cplcgWpCgZcHpm)

!! 1. sub-matrix  
Pole_Present = .false. 
max_element_removed = 0._dp 
RemoveTUpoles = 0 
scatter_matrix1=0._dp 
If (IncludeGoldstoneExternal) scatter_matrix1(1,1) = a0_AhAh_AhAh(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,2) = a0_AhAh_AhAh(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,3) = a0_AhAh_AhAh(unitarity_s,1,1,1,3,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,4) = a0_AhAh_AhAh(unitarity_s,1,1,2,2,1,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,5) = a0_AhAh_AhAh(unitarity_s,1,1,2,3,1,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,6) = a0_AhAh_AhAh(unitarity_s,1,1,3,3,1,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,7) = a0_AhAh_Ahhh(unitarity_s,1,1,1,1,1,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,8) = a0_AhAh_Ahhh(unitarity_s,1,1,1,2,1,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,9) = a0_AhAh_Ahhh(unitarity_s,1,1,1,3,1,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,10) = a0_AhAh_Ahhh(unitarity_s,1,1,2,1,1,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,11) = a0_AhAh_Ahhh(unitarity_s,1,1,2,2,1,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,12) = a0_AhAh_Ahhh(unitarity_s,1,1,2,3,1,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,13) = a0_AhAh_Ahhh(unitarity_s,1,1,3,1,1,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,14) = a0_AhAh_Ahhh(unitarity_s,1,1,3,2,1,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,15) = a0_AhAh_Ahhh(unitarity_s,1,1,3,3,1,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,16) = a0_AhAh_hhhh(unitarity_s,1,1,1,1,1,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,17) = a0_AhAh_hhhh(unitarity_s,1,1,1,2,1,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,18) = a0_AhAh_hhhh(unitarity_s,1,1,1,3,1,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,19) = a0_AhAh_hhhh(unitarity_s,1,1,2,2,1,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,20) = a0_AhAh_hhhh(unitarity_s,1,1,2,3,1,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,21) = a0_AhAh_hhhh(unitarity_s,1,1,3,3,1,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,22) = a0_AhAh_HpmHpmc(unitarity_s,1,1,1,1,1,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,23) = a0_AhAh_HpmHpmc(unitarity_s,1,1,1,2,1,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,24) = a0_AhAh_HpmHpmc(unitarity_s,1,1,2,1,1,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,25) = a0_AhAh_HpmHpmc(unitarity_s,1,1,2,2,1,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,1) = a0_AhAh_AhAh(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,2) = a0_AhAh_AhAh(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,3) = a0_AhAh_AhAh(unitarity_s,1,2,1,3,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,4) = a0_AhAh_AhAh(unitarity_s,1,2,2,2,2,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,5) = a0_AhAh_AhAh(unitarity_s,1,2,2,3,2,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,6) = a0_AhAh_AhAh(unitarity_s,1,2,3,3,2,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,7) = a0_AhAh_Ahhh(unitarity_s,1,2,1,1,2,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,8) = a0_AhAh_Ahhh(unitarity_s,1,2,1,2,2,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,9) = a0_AhAh_Ahhh(unitarity_s,1,2,1,3,2,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,10) = a0_AhAh_Ahhh(unitarity_s,1,2,2,1,2,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,11) = a0_AhAh_Ahhh(unitarity_s,1,2,2,2,2,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,12) = a0_AhAh_Ahhh(unitarity_s,1,2,2,3,2,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,13) = a0_AhAh_Ahhh(unitarity_s,1,2,3,1,2,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,14) = a0_AhAh_Ahhh(unitarity_s,1,2,3,2,2,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,15) = a0_AhAh_Ahhh(unitarity_s,1,2,3,3,2,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,16) = a0_AhAh_hhhh(unitarity_s,1,2,1,1,2,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,17) = a0_AhAh_hhhh(unitarity_s,1,2,1,2,2,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,18) = a0_AhAh_hhhh(unitarity_s,1,2,1,3,2,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,19) = a0_AhAh_hhhh(unitarity_s,1,2,2,2,2,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,20) = a0_AhAh_hhhh(unitarity_s,1,2,2,3,2,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,21) = a0_AhAh_hhhh(unitarity_s,1,2,3,3,2,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,22) = a0_AhAh_HpmHpmc(unitarity_s,1,2,1,1,2,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,23) = a0_AhAh_HpmHpmc(unitarity_s,1,2,1,2,2,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,24) = a0_AhAh_HpmHpmc(unitarity_s,1,2,2,1,2,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,25) = a0_AhAh_HpmHpmc(unitarity_s,1,2,2,2,2,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,1) = a0_AhAh_AhAh(unitarity_s,1,3,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,2) = a0_AhAh_AhAh(unitarity_s,1,3,1,2,3,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,3) = a0_AhAh_AhAh(unitarity_s,1,3,1,3,3,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,4) = a0_AhAh_AhAh(unitarity_s,1,3,2,2,3,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,5) = a0_AhAh_AhAh(unitarity_s,1,3,2,3,3,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,6) = a0_AhAh_AhAh(unitarity_s,1,3,3,3,3,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,7) = a0_AhAh_Ahhh(unitarity_s,1,3,1,1,3,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,8) = a0_AhAh_Ahhh(unitarity_s,1,3,1,2,3,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,9) = a0_AhAh_Ahhh(unitarity_s,1,3,1,3,3,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,10) = a0_AhAh_Ahhh(unitarity_s,1,3,2,1,3,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,11) = a0_AhAh_Ahhh(unitarity_s,1,3,2,2,3,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,12) = a0_AhAh_Ahhh(unitarity_s,1,3,2,3,3,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,13) = a0_AhAh_Ahhh(unitarity_s,1,3,3,1,3,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,14) = a0_AhAh_Ahhh(unitarity_s,1,3,3,2,3,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,15) = a0_AhAh_Ahhh(unitarity_s,1,3,3,3,3,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,16) = a0_AhAh_hhhh(unitarity_s,1,3,1,1,3,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,17) = a0_AhAh_hhhh(unitarity_s,1,3,1,2,3,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,18) = a0_AhAh_hhhh(unitarity_s,1,3,1,3,3,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,19) = a0_AhAh_hhhh(unitarity_s,1,3,2,2,3,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,20) = a0_AhAh_hhhh(unitarity_s,1,3,2,3,3,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,21) = a0_AhAh_hhhh(unitarity_s,1,3,3,3,3,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,22) = a0_AhAh_HpmHpmc(unitarity_s,1,3,1,1,3,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,23) = a0_AhAh_HpmHpmc(unitarity_s,1,3,1,2,3,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,24) = a0_AhAh_HpmHpmc(unitarity_s,1,3,2,1,3,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,25) = a0_AhAh_HpmHpmc(unitarity_s,1,3,2,2,3,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,1) = a0_AhAh_AhAh(unitarity_s,2,2,1,1,4,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,2) = a0_AhAh_AhAh(unitarity_s,2,2,1,2,4,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,3) = a0_AhAh_AhAh(unitarity_s,2,2,1,3,4,3) 
scatter_matrix1(4,4) = a0_AhAh_AhAh(unitarity_s,2,2,2,2,4,4) 
scatter_matrix1(4,5) = a0_AhAh_AhAh(unitarity_s,2,2,2,3,4,5) 
scatter_matrix1(4,6) = a0_AhAh_AhAh(unitarity_s,2,2,3,3,4,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,7) = a0_AhAh_Ahhh(unitarity_s,2,2,1,1,4,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,8) = a0_AhAh_Ahhh(unitarity_s,2,2,1,2,4,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,9) = a0_AhAh_Ahhh(unitarity_s,2,2,1,3,4,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,10) = a0_AhAh_Ahhh(unitarity_s,2,2,2,1,4,10) 
scatter_matrix1(4,11) = a0_AhAh_Ahhh(unitarity_s,2,2,2,2,4,11) 
scatter_matrix1(4,12) = a0_AhAh_Ahhh(unitarity_s,2,2,2,3,4,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,13) = a0_AhAh_Ahhh(unitarity_s,2,2,3,1,4,13) 
scatter_matrix1(4,14) = a0_AhAh_Ahhh(unitarity_s,2,2,3,2,4,14) 
scatter_matrix1(4,15) = a0_AhAh_Ahhh(unitarity_s,2,2,3,3,4,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,16) = a0_AhAh_hhhh(unitarity_s,2,2,1,1,4,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,17) = a0_AhAh_hhhh(unitarity_s,2,2,1,2,4,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,18) = a0_AhAh_hhhh(unitarity_s,2,2,1,3,4,18) 
scatter_matrix1(4,19) = a0_AhAh_hhhh(unitarity_s,2,2,2,2,4,19) 
scatter_matrix1(4,20) = a0_AhAh_hhhh(unitarity_s,2,2,2,3,4,20) 
scatter_matrix1(4,21) = a0_AhAh_hhhh(unitarity_s,2,2,3,3,4,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,22) = a0_AhAh_HpmHpmc(unitarity_s,2,2,1,1,4,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,23) = a0_AhAh_HpmHpmc(unitarity_s,2,2,1,2,4,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,24) = a0_AhAh_HpmHpmc(unitarity_s,2,2,2,1,4,24) 
scatter_matrix1(4,25) = a0_AhAh_HpmHpmc(unitarity_s,2,2,2,2,4,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,1) = a0_AhAh_AhAh(unitarity_s,2,3,1,1,5,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,2) = a0_AhAh_AhAh(unitarity_s,2,3,1,2,5,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,3) = a0_AhAh_AhAh(unitarity_s,2,3,1,3,5,3) 
scatter_matrix1(5,4) = a0_AhAh_AhAh(unitarity_s,2,3,2,2,5,4) 
scatter_matrix1(5,5) = a0_AhAh_AhAh(unitarity_s,2,3,2,3,5,5) 
scatter_matrix1(5,6) = a0_AhAh_AhAh(unitarity_s,2,3,3,3,5,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,7) = a0_AhAh_Ahhh(unitarity_s,2,3,1,1,5,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,8) = a0_AhAh_Ahhh(unitarity_s,2,3,1,2,5,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,9) = a0_AhAh_Ahhh(unitarity_s,2,3,1,3,5,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,10) = a0_AhAh_Ahhh(unitarity_s,2,3,2,1,5,10) 
scatter_matrix1(5,11) = a0_AhAh_Ahhh(unitarity_s,2,3,2,2,5,11) 
scatter_matrix1(5,12) = a0_AhAh_Ahhh(unitarity_s,2,3,2,3,5,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,13) = a0_AhAh_Ahhh(unitarity_s,2,3,3,1,5,13) 
scatter_matrix1(5,14) = a0_AhAh_Ahhh(unitarity_s,2,3,3,2,5,14) 
scatter_matrix1(5,15) = a0_AhAh_Ahhh(unitarity_s,2,3,3,3,5,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,16) = a0_AhAh_hhhh(unitarity_s,2,3,1,1,5,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,17) = a0_AhAh_hhhh(unitarity_s,2,3,1,2,5,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,18) = a0_AhAh_hhhh(unitarity_s,2,3,1,3,5,18) 
scatter_matrix1(5,19) = a0_AhAh_hhhh(unitarity_s,2,3,2,2,5,19) 
scatter_matrix1(5,20) = a0_AhAh_hhhh(unitarity_s,2,3,2,3,5,20) 
scatter_matrix1(5,21) = a0_AhAh_hhhh(unitarity_s,2,3,3,3,5,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,22) = a0_AhAh_HpmHpmc(unitarity_s,2,3,1,1,5,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,23) = a0_AhAh_HpmHpmc(unitarity_s,2,3,1,2,5,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,24) = a0_AhAh_HpmHpmc(unitarity_s,2,3,2,1,5,24) 
scatter_matrix1(5,25) = a0_AhAh_HpmHpmc(unitarity_s,2,3,2,2,5,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,1) = a0_AhAh_AhAh(unitarity_s,3,3,1,1,6,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,2) = a0_AhAh_AhAh(unitarity_s,3,3,1,2,6,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,3) = a0_AhAh_AhAh(unitarity_s,3,3,1,3,6,3) 
scatter_matrix1(6,4) = a0_AhAh_AhAh(unitarity_s,3,3,2,2,6,4) 
scatter_matrix1(6,5) = a0_AhAh_AhAh(unitarity_s,3,3,2,3,6,5) 
scatter_matrix1(6,6) = a0_AhAh_AhAh(unitarity_s,3,3,3,3,6,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,7) = a0_AhAh_Ahhh(unitarity_s,3,3,1,1,6,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,8) = a0_AhAh_Ahhh(unitarity_s,3,3,1,2,6,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,9) = a0_AhAh_Ahhh(unitarity_s,3,3,1,3,6,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,10) = a0_AhAh_Ahhh(unitarity_s,3,3,2,1,6,10) 
scatter_matrix1(6,11) = a0_AhAh_Ahhh(unitarity_s,3,3,2,2,6,11) 
scatter_matrix1(6,12) = a0_AhAh_Ahhh(unitarity_s,3,3,2,3,6,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,13) = a0_AhAh_Ahhh(unitarity_s,3,3,3,1,6,13) 
scatter_matrix1(6,14) = a0_AhAh_Ahhh(unitarity_s,3,3,3,2,6,14) 
scatter_matrix1(6,15) = a0_AhAh_Ahhh(unitarity_s,3,3,3,3,6,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,16) = a0_AhAh_hhhh(unitarity_s,3,3,1,1,6,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,17) = a0_AhAh_hhhh(unitarity_s,3,3,1,2,6,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,18) = a0_AhAh_hhhh(unitarity_s,3,3,1,3,6,18) 
scatter_matrix1(6,19) = a0_AhAh_hhhh(unitarity_s,3,3,2,2,6,19) 
scatter_matrix1(6,20) = a0_AhAh_hhhh(unitarity_s,3,3,2,3,6,20) 
scatter_matrix1(6,21) = a0_AhAh_hhhh(unitarity_s,3,3,3,3,6,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,22) = a0_AhAh_HpmHpmc(unitarity_s,3,3,1,1,6,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,23) = a0_AhAh_HpmHpmc(unitarity_s,3,3,1,2,6,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,24) = a0_AhAh_HpmHpmc(unitarity_s,3,3,2,1,6,24) 
scatter_matrix1(6,25) = a0_AhAh_HpmHpmc(unitarity_s,3,3,2,2,6,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,1) = a0_Ahhh_AhAh(unitarity_s,1,1,1,1,7,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,2) = a0_Ahhh_AhAh(unitarity_s,1,1,1,2,7,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,3) = a0_Ahhh_AhAh(unitarity_s,1,1,1,3,7,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,4) = a0_Ahhh_AhAh(unitarity_s,1,1,2,2,7,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,5) = a0_Ahhh_AhAh(unitarity_s,1,1,2,3,7,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,6) = a0_Ahhh_AhAh(unitarity_s,1,1,3,3,7,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,7) = a0_Ahhh_Ahhh(unitarity_s,1,1,1,1,7,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,8) = a0_Ahhh_Ahhh(unitarity_s,1,1,1,2,7,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,9) = a0_Ahhh_Ahhh(unitarity_s,1,1,1,3,7,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,10) = a0_Ahhh_Ahhh(unitarity_s,1,1,2,1,7,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,11) = a0_Ahhh_Ahhh(unitarity_s,1,1,2,2,7,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,12) = a0_Ahhh_Ahhh(unitarity_s,1,1,2,3,7,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,13) = a0_Ahhh_Ahhh(unitarity_s,1,1,3,1,7,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,14) = a0_Ahhh_Ahhh(unitarity_s,1,1,3,2,7,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,15) = a0_Ahhh_Ahhh(unitarity_s,1,1,3,3,7,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,16) = a0_Ahhh_hhhh(unitarity_s,1,1,1,1,7,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,17) = a0_Ahhh_hhhh(unitarity_s,1,1,1,2,7,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,18) = a0_Ahhh_hhhh(unitarity_s,1,1,1,3,7,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,19) = a0_Ahhh_hhhh(unitarity_s,1,1,2,2,7,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,20) = a0_Ahhh_hhhh(unitarity_s,1,1,2,3,7,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,21) = a0_Ahhh_hhhh(unitarity_s,1,1,3,3,7,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,22) = a0_Ahhh_HpmHpmc(unitarity_s,1,1,1,1,7,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,23) = a0_Ahhh_HpmHpmc(unitarity_s,1,1,1,2,7,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,24) = a0_Ahhh_HpmHpmc(unitarity_s,1,1,2,1,7,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,25) = a0_Ahhh_HpmHpmc(unitarity_s,1,1,2,2,7,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,1) = a0_Ahhh_AhAh(unitarity_s,1,2,1,1,8,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,2) = a0_Ahhh_AhAh(unitarity_s,1,2,1,2,8,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,3) = a0_Ahhh_AhAh(unitarity_s,1,2,1,3,8,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,4) = a0_Ahhh_AhAh(unitarity_s,1,2,2,2,8,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,5) = a0_Ahhh_AhAh(unitarity_s,1,2,2,3,8,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,6) = a0_Ahhh_AhAh(unitarity_s,1,2,3,3,8,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,7) = a0_Ahhh_Ahhh(unitarity_s,1,2,1,1,8,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,8) = a0_Ahhh_Ahhh(unitarity_s,1,2,1,2,8,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,9) = a0_Ahhh_Ahhh(unitarity_s,1,2,1,3,8,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,10) = a0_Ahhh_Ahhh(unitarity_s,1,2,2,1,8,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,11) = a0_Ahhh_Ahhh(unitarity_s,1,2,2,2,8,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,12) = a0_Ahhh_Ahhh(unitarity_s,1,2,2,3,8,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,13) = a0_Ahhh_Ahhh(unitarity_s,1,2,3,1,8,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,14) = a0_Ahhh_Ahhh(unitarity_s,1,2,3,2,8,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,15) = a0_Ahhh_Ahhh(unitarity_s,1,2,3,3,8,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,16) = a0_Ahhh_hhhh(unitarity_s,1,2,1,1,8,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,17) = a0_Ahhh_hhhh(unitarity_s,1,2,1,2,8,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,18) = a0_Ahhh_hhhh(unitarity_s,1,2,1,3,8,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,19) = a0_Ahhh_hhhh(unitarity_s,1,2,2,2,8,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,20) = a0_Ahhh_hhhh(unitarity_s,1,2,2,3,8,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,21) = a0_Ahhh_hhhh(unitarity_s,1,2,3,3,8,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,22) = a0_Ahhh_HpmHpmc(unitarity_s,1,2,1,1,8,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,23) = a0_Ahhh_HpmHpmc(unitarity_s,1,2,1,2,8,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,24) = a0_Ahhh_HpmHpmc(unitarity_s,1,2,2,1,8,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(8,25) = a0_Ahhh_HpmHpmc(unitarity_s,1,2,2,2,8,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,1) = a0_Ahhh_AhAh(unitarity_s,1,3,1,1,9,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,2) = a0_Ahhh_AhAh(unitarity_s,1,3,1,2,9,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,3) = a0_Ahhh_AhAh(unitarity_s,1,3,1,3,9,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,4) = a0_Ahhh_AhAh(unitarity_s,1,3,2,2,9,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,5) = a0_Ahhh_AhAh(unitarity_s,1,3,2,3,9,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,6) = a0_Ahhh_AhAh(unitarity_s,1,3,3,3,9,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,7) = a0_Ahhh_Ahhh(unitarity_s,1,3,1,1,9,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,8) = a0_Ahhh_Ahhh(unitarity_s,1,3,1,2,9,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,9) = a0_Ahhh_Ahhh(unitarity_s,1,3,1,3,9,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,10) = a0_Ahhh_Ahhh(unitarity_s,1,3,2,1,9,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,11) = a0_Ahhh_Ahhh(unitarity_s,1,3,2,2,9,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,12) = a0_Ahhh_Ahhh(unitarity_s,1,3,2,3,9,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,13) = a0_Ahhh_Ahhh(unitarity_s,1,3,3,1,9,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,14) = a0_Ahhh_Ahhh(unitarity_s,1,3,3,2,9,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,15) = a0_Ahhh_Ahhh(unitarity_s,1,3,3,3,9,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,16) = a0_Ahhh_hhhh(unitarity_s,1,3,1,1,9,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,17) = a0_Ahhh_hhhh(unitarity_s,1,3,1,2,9,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,18) = a0_Ahhh_hhhh(unitarity_s,1,3,1,3,9,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,19) = a0_Ahhh_hhhh(unitarity_s,1,3,2,2,9,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,20) = a0_Ahhh_hhhh(unitarity_s,1,3,2,3,9,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,21) = a0_Ahhh_hhhh(unitarity_s,1,3,3,3,9,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,22) = a0_Ahhh_HpmHpmc(unitarity_s,1,3,1,1,9,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,23) = a0_Ahhh_HpmHpmc(unitarity_s,1,3,1,2,9,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,24) = a0_Ahhh_HpmHpmc(unitarity_s,1,3,2,1,9,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(9,25) = a0_Ahhh_HpmHpmc(unitarity_s,1,3,2,2,9,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,1) = a0_Ahhh_AhAh(unitarity_s,2,1,1,1,10,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,2) = a0_Ahhh_AhAh(unitarity_s,2,1,1,2,10,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,3) = a0_Ahhh_AhAh(unitarity_s,2,1,1,3,10,3) 
scatter_matrix1(10,4) = a0_Ahhh_AhAh(unitarity_s,2,1,2,2,10,4) 
scatter_matrix1(10,5) = a0_Ahhh_AhAh(unitarity_s,2,1,2,3,10,5) 
scatter_matrix1(10,6) = a0_Ahhh_AhAh(unitarity_s,2,1,3,3,10,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,7) = a0_Ahhh_Ahhh(unitarity_s,2,1,1,1,10,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,8) = a0_Ahhh_Ahhh(unitarity_s,2,1,1,2,10,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,9) = a0_Ahhh_Ahhh(unitarity_s,2,1,1,3,10,9) 
scatter_matrix1(10,10) = a0_Ahhh_Ahhh(unitarity_s,2,1,2,1,10,10) 
scatter_matrix1(10,11) = a0_Ahhh_Ahhh(unitarity_s,2,1,2,2,10,11) 
scatter_matrix1(10,12) = a0_Ahhh_Ahhh(unitarity_s,2,1,2,3,10,12) 
scatter_matrix1(10,13) = a0_Ahhh_Ahhh(unitarity_s,2,1,3,1,10,13) 
scatter_matrix1(10,14) = a0_Ahhh_Ahhh(unitarity_s,2,1,3,2,10,14) 
scatter_matrix1(10,15) = a0_Ahhh_Ahhh(unitarity_s,2,1,3,3,10,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,16) = a0_Ahhh_hhhh(unitarity_s,2,1,1,1,10,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,17) = a0_Ahhh_hhhh(unitarity_s,2,1,1,2,10,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,18) = a0_Ahhh_hhhh(unitarity_s,2,1,1,3,10,18) 
scatter_matrix1(10,19) = a0_Ahhh_hhhh(unitarity_s,2,1,2,2,10,19) 
scatter_matrix1(10,20) = a0_Ahhh_hhhh(unitarity_s,2,1,2,3,10,20) 
scatter_matrix1(10,21) = a0_Ahhh_hhhh(unitarity_s,2,1,3,3,10,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,22) = a0_Ahhh_HpmHpmc(unitarity_s,2,1,1,1,10,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(10,23) = a0_Ahhh_HpmHpmc(unitarity_s,2,1,1,2,10,23) 
scatter_matrix1(10,24) = a0_Ahhh_HpmHpmc(unitarity_s,2,1,2,1,10,24) 
scatter_matrix1(10,25) = a0_Ahhh_HpmHpmc(unitarity_s,2,1,2,2,10,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,1) = a0_Ahhh_AhAh(unitarity_s,2,2,1,1,11,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,2) = a0_Ahhh_AhAh(unitarity_s,2,2,1,2,11,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,3) = a0_Ahhh_AhAh(unitarity_s,2,2,1,3,11,3) 
scatter_matrix1(11,4) = a0_Ahhh_AhAh(unitarity_s,2,2,2,2,11,4) 
scatter_matrix1(11,5) = a0_Ahhh_AhAh(unitarity_s,2,2,2,3,11,5) 
scatter_matrix1(11,6) = a0_Ahhh_AhAh(unitarity_s,2,2,3,3,11,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,7) = a0_Ahhh_Ahhh(unitarity_s,2,2,1,1,11,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,8) = a0_Ahhh_Ahhh(unitarity_s,2,2,1,2,11,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,9) = a0_Ahhh_Ahhh(unitarity_s,2,2,1,3,11,9) 
scatter_matrix1(11,10) = a0_Ahhh_Ahhh(unitarity_s,2,2,2,1,11,10) 
scatter_matrix1(11,11) = a0_Ahhh_Ahhh(unitarity_s,2,2,2,2,11,11) 
scatter_matrix1(11,12) = a0_Ahhh_Ahhh(unitarity_s,2,2,2,3,11,12) 
scatter_matrix1(11,13) = a0_Ahhh_Ahhh(unitarity_s,2,2,3,1,11,13) 
scatter_matrix1(11,14) = a0_Ahhh_Ahhh(unitarity_s,2,2,3,2,11,14) 
scatter_matrix1(11,15) = a0_Ahhh_Ahhh(unitarity_s,2,2,3,3,11,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,16) = a0_Ahhh_hhhh(unitarity_s,2,2,1,1,11,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,17) = a0_Ahhh_hhhh(unitarity_s,2,2,1,2,11,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,18) = a0_Ahhh_hhhh(unitarity_s,2,2,1,3,11,18) 
scatter_matrix1(11,19) = a0_Ahhh_hhhh(unitarity_s,2,2,2,2,11,19) 
scatter_matrix1(11,20) = a0_Ahhh_hhhh(unitarity_s,2,2,2,3,11,20) 
scatter_matrix1(11,21) = a0_Ahhh_hhhh(unitarity_s,2,2,3,3,11,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,22) = a0_Ahhh_HpmHpmc(unitarity_s,2,2,1,1,11,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,23) = a0_Ahhh_HpmHpmc(unitarity_s,2,2,1,2,11,23) 
scatter_matrix1(11,24) = a0_Ahhh_HpmHpmc(unitarity_s,2,2,2,1,11,24) 
scatter_matrix1(11,25) = a0_Ahhh_HpmHpmc(unitarity_s,2,2,2,2,11,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,1) = a0_Ahhh_AhAh(unitarity_s,2,3,1,1,12,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,2) = a0_Ahhh_AhAh(unitarity_s,2,3,1,2,12,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,3) = a0_Ahhh_AhAh(unitarity_s,2,3,1,3,12,3) 
scatter_matrix1(12,4) = a0_Ahhh_AhAh(unitarity_s,2,3,2,2,12,4) 
scatter_matrix1(12,5) = a0_Ahhh_AhAh(unitarity_s,2,3,2,3,12,5) 
scatter_matrix1(12,6) = a0_Ahhh_AhAh(unitarity_s,2,3,3,3,12,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,7) = a0_Ahhh_Ahhh(unitarity_s,2,3,1,1,12,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,8) = a0_Ahhh_Ahhh(unitarity_s,2,3,1,2,12,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,9) = a0_Ahhh_Ahhh(unitarity_s,2,3,1,3,12,9) 
scatter_matrix1(12,10) = a0_Ahhh_Ahhh(unitarity_s,2,3,2,1,12,10) 
scatter_matrix1(12,11) = a0_Ahhh_Ahhh(unitarity_s,2,3,2,2,12,11) 
scatter_matrix1(12,12) = a0_Ahhh_Ahhh(unitarity_s,2,3,2,3,12,12) 
scatter_matrix1(12,13) = a0_Ahhh_Ahhh(unitarity_s,2,3,3,1,12,13) 
scatter_matrix1(12,14) = a0_Ahhh_Ahhh(unitarity_s,2,3,3,2,12,14) 
scatter_matrix1(12,15) = a0_Ahhh_Ahhh(unitarity_s,2,3,3,3,12,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,16) = a0_Ahhh_hhhh(unitarity_s,2,3,1,1,12,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,17) = a0_Ahhh_hhhh(unitarity_s,2,3,1,2,12,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,18) = a0_Ahhh_hhhh(unitarity_s,2,3,1,3,12,18) 
scatter_matrix1(12,19) = a0_Ahhh_hhhh(unitarity_s,2,3,2,2,12,19) 
scatter_matrix1(12,20) = a0_Ahhh_hhhh(unitarity_s,2,3,2,3,12,20) 
scatter_matrix1(12,21) = a0_Ahhh_hhhh(unitarity_s,2,3,3,3,12,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,22) = a0_Ahhh_HpmHpmc(unitarity_s,2,3,1,1,12,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,23) = a0_Ahhh_HpmHpmc(unitarity_s,2,3,1,2,12,23) 
scatter_matrix1(12,24) = a0_Ahhh_HpmHpmc(unitarity_s,2,3,2,1,12,24) 
scatter_matrix1(12,25) = a0_Ahhh_HpmHpmc(unitarity_s,2,3,2,2,12,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,1) = a0_Ahhh_AhAh(unitarity_s,3,1,1,1,13,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,2) = a0_Ahhh_AhAh(unitarity_s,3,1,1,2,13,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,3) = a0_Ahhh_AhAh(unitarity_s,3,1,1,3,13,3) 
scatter_matrix1(13,4) = a0_Ahhh_AhAh(unitarity_s,3,1,2,2,13,4) 
scatter_matrix1(13,5) = a0_Ahhh_AhAh(unitarity_s,3,1,2,3,13,5) 
scatter_matrix1(13,6) = a0_Ahhh_AhAh(unitarity_s,3,1,3,3,13,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,7) = a0_Ahhh_Ahhh(unitarity_s,3,1,1,1,13,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,8) = a0_Ahhh_Ahhh(unitarity_s,3,1,1,2,13,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,9) = a0_Ahhh_Ahhh(unitarity_s,3,1,1,3,13,9) 
scatter_matrix1(13,10) = a0_Ahhh_Ahhh(unitarity_s,3,1,2,1,13,10) 
scatter_matrix1(13,11) = a0_Ahhh_Ahhh(unitarity_s,3,1,2,2,13,11) 
scatter_matrix1(13,12) = a0_Ahhh_Ahhh(unitarity_s,3,1,2,3,13,12) 
scatter_matrix1(13,13) = a0_Ahhh_Ahhh(unitarity_s,3,1,3,1,13,13) 
scatter_matrix1(13,14) = a0_Ahhh_Ahhh(unitarity_s,3,1,3,2,13,14) 
scatter_matrix1(13,15) = a0_Ahhh_Ahhh(unitarity_s,3,1,3,3,13,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,16) = a0_Ahhh_hhhh(unitarity_s,3,1,1,1,13,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,17) = a0_Ahhh_hhhh(unitarity_s,3,1,1,2,13,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,18) = a0_Ahhh_hhhh(unitarity_s,3,1,1,3,13,18) 
scatter_matrix1(13,19) = a0_Ahhh_hhhh(unitarity_s,3,1,2,2,13,19) 
scatter_matrix1(13,20) = a0_Ahhh_hhhh(unitarity_s,3,1,2,3,13,20) 
scatter_matrix1(13,21) = a0_Ahhh_hhhh(unitarity_s,3,1,3,3,13,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,22) = a0_Ahhh_HpmHpmc(unitarity_s,3,1,1,1,13,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,23) = a0_Ahhh_HpmHpmc(unitarity_s,3,1,1,2,13,23) 
scatter_matrix1(13,24) = a0_Ahhh_HpmHpmc(unitarity_s,3,1,2,1,13,24) 
scatter_matrix1(13,25) = a0_Ahhh_HpmHpmc(unitarity_s,3,1,2,2,13,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,1) = a0_Ahhh_AhAh(unitarity_s,3,2,1,1,14,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,2) = a0_Ahhh_AhAh(unitarity_s,3,2,1,2,14,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,3) = a0_Ahhh_AhAh(unitarity_s,3,2,1,3,14,3) 
scatter_matrix1(14,4) = a0_Ahhh_AhAh(unitarity_s,3,2,2,2,14,4) 
scatter_matrix1(14,5) = a0_Ahhh_AhAh(unitarity_s,3,2,2,3,14,5) 
scatter_matrix1(14,6) = a0_Ahhh_AhAh(unitarity_s,3,2,3,3,14,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,7) = a0_Ahhh_Ahhh(unitarity_s,3,2,1,1,14,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,8) = a0_Ahhh_Ahhh(unitarity_s,3,2,1,2,14,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,9) = a0_Ahhh_Ahhh(unitarity_s,3,2,1,3,14,9) 
scatter_matrix1(14,10) = a0_Ahhh_Ahhh(unitarity_s,3,2,2,1,14,10) 
scatter_matrix1(14,11) = a0_Ahhh_Ahhh(unitarity_s,3,2,2,2,14,11) 
scatter_matrix1(14,12) = a0_Ahhh_Ahhh(unitarity_s,3,2,2,3,14,12) 
scatter_matrix1(14,13) = a0_Ahhh_Ahhh(unitarity_s,3,2,3,1,14,13) 
scatter_matrix1(14,14) = a0_Ahhh_Ahhh(unitarity_s,3,2,3,2,14,14) 
scatter_matrix1(14,15) = a0_Ahhh_Ahhh(unitarity_s,3,2,3,3,14,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,16) = a0_Ahhh_hhhh(unitarity_s,3,2,1,1,14,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,17) = a0_Ahhh_hhhh(unitarity_s,3,2,1,2,14,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,18) = a0_Ahhh_hhhh(unitarity_s,3,2,1,3,14,18) 
scatter_matrix1(14,19) = a0_Ahhh_hhhh(unitarity_s,3,2,2,2,14,19) 
scatter_matrix1(14,20) = a0_Ahhh_hhhh(unitarity_s,3,2,2,3,14,20) 
scatter_matrix1(14,21) = a0_Ahhh_hhhh(unitarity_s,3,2,3,3,14,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,22) = a0_Ahhh_HpmHpmc(unitarity_s,3,2,1,1,14,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,23) = a0_Ahhh_HpmHpmc(unitarity_s,3,2,1,2,14,23) 
scatter_matrix1(14,24) = a0_Ahhh_HpmHpmc(unitarity_s,3,2,2,1,14,24) 
scatter_matrix1(14,25) = a0_Ahhh_HpmHpmc(unitarity_s,3,2,2,2,14,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,1) = a0_Ahhh_AhAh(unitarity_s,3,3,1,1,15,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,2) = a0_Ahhh_AhAh(unitarity_s,3,3,1,2,15,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,3) = a0_Ahhh_AhAh(unitarity_s,3,3,1,3,15,3) 
scatter_matrix1(15,4) = a0_Ahhh_AhAh(unitarity_s,3,3,2,2,15,4) 
scatter_matrix1(15,5) = a0_Ahhh_AhAh(unitarity_s,3,3,2,3,15,5) 
scatter_matrix1(15,6) = a0_Ahhh_AhAh(unitarity_s,3,3,3,3,15,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,7) = a0_Ahhh_Ahhh(unitarity_s,3,3,1,1,15,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,8) = a0_Ahhh_Ahhh(unitarity_s,3,3,1,2,15,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,9) = a0_Ahhh_Ahhh(unitarity_s,3,3,1,3,15,9) 
scatter_matrix1(15,10) = a0_Ahhh_Ahhh(unitarity_s,3,3,2,1,15,10) 
scatter_matrix1(15,11) = a0_Ahhh_Ahhh(unitarity_s,3,3,2,2,15,11) 
scatter_matrix1(15,12) = a0_Ahhh_Ahhh(unitarity_s,3,3,2,3,15,12) 
scatter_matrix1(15,13) = a0_Ahhh_Ahhh(unitarity_s,3,3,3,1,15,13) 
scatter_matrix1(15,14) = a0_Ahhh_Ahhh(unitarity_s,3,3,3,2,15,14) 
scatter_matrix1(15,15) = a0_Ahhh_Ahhh(unitarity_s,3,3,3,3,15,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,16) = a0_Ahhh_hhhh(unitarity_s,3,3,1,1,15,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,17) = a0_Ahhh_hhhh(unitarity_s,3,3,1,2,15,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,18) = a0_Ahhh_hhhh(unitarity_s,3,3,1,3,15,18) 
scatter_matrix1(15,19) = a0_Ahhh_hhhh(unitarity_s,3,3,2,2,15,19) 
scatter_matrix1(15,20) = a0_Ahhh_hhhh(unitarity_s,3,3,2,3,15,20) 
scatter_matrix1(15,21) = a0_Ahhh_hhhh(unitarity_s,3,3,3,3,15,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,22) = a0_Ahhh_HpmHpmc(unitarity_s,3,3,1,1,15,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(15,23) = a0_Ahhh_HpmHpmc(unitarity_s,3,3,1,2,15,23) 
scatter_matrix1(15,24) = a0_Ahhh_HpmHpmc(unitarity_s,3,3,2,1,15,24) 
scatter_matrix1(15,25) = a0_Ahhh_HpmHpmc(unitarity_s,3,3,2,2,15,25) 
scatter_matrix1(16,1) = a0_hhhh_AhAh(unitarity_s,1,1,1,1,16,1) 
scatter_matrix1(16,2) = a0_hhhh_AhAh(unitarity_s,1,1,1,2,16,2) 
scatter_matrix1(16,3) = a0_hhhh_AhAh(unitarity_s,1,1,1,3,16,3) 
scatter_matrix1(16,4) = a0_hhhh_AhAh(unitarity_s,1,1,2,2,16,4) 
scatter_matrix1(16,5) = a0_hhhh_AhAh(unitarity_s,1,1,2,3,16,5) 
scatter_matrix1(16,6) = a0_hhhh_AhAh(unitarity_s,1,1,3,3,16,6) 
scatter_matrix1(16,7) = a0_hhhh_Ahhh(unitarity_s,1,1,1,1,16,7) 
scatter_matrix1(16,8) = a0_hhhh_Ahhh(unitarity_s,1,1,1,2,16,8) 
scatter_matrix1(16,9) = a0_hhhh_Ahhh(unitarity_s,1,1,1,3,16,9) 
scatter_matrix1(16,10) = a0_hhhh_Ahhh(unitarity_s,1,1,2,1,16,10) 
scatter_matrix1(16,11) = a0_hhhh_Ahhh(unitarity_s,1,1,2,2,16,11) 
scatter_matrix1(16,12) = a0_hhhh_Ahhh(unitarity_s,1,1,2,3,16,12) 
scatter_matrix1(16,13) = a0_hhhh_Ahhh(unitarity_s,1,1,3,1,16,13) 
scatter_matrix1(16,14) = a0_hhhh_Ahhh(unitarity_s,1,1,3,2,16,14) 
scatter_matrix1(16,15) = a0_hhhh_Ahhh(unitarity_s,1,1,3,3,16,15) 
scatter_matrix1(16,16) = a0_hhhh_hhhh(unitarity_s,1,1,1,1,16,16) 
scatter_matrix1(16,17) = a0_hhhh_hhhh(unitarity_s,1,1,1,2,16,17) 
scatter_matrix1(16,18) = a0_hhhh_hhhh(unitarity_s,1,1,1,3,16,18) 
scatter_matrix1(16,19) = a0_hhhh_hhhh(unitarity_s,1,1,2,2,16,19) 
scatter_matrix1(16,20) = a0_hhhh_hhhh(unitarity_s,1,1,2,3,16,20) 
scatter_matrix1(16,21) = a0_hhhh_hhhh(unitarity_s,1,1,3,3,16,21) 
scatter_matrix1(16,22) = a0_hhhh_HpmHpmc(unitarity_s,1,1,1,1,16,22) 
scatter_matrix1(16,23) = a0_hhhh_HpmHpmc(unitarity_s,1,1,1,2,16,23) 
scatter_matrix1(16,24) = a0_hhhh_HpmHpmc(unitarity_s,1,1,2,1,16,24) 
scatter_matrix1(16,25) = a0_hhhh_HpmHpmc(unitarity_s,1,1,2,2,16,25) 
scatter_matrix1(17,1) = a0_hhhh_AhAh(unitarity_s,1,2,1,1,17,1) 
scatter_matrix1(17,2) = a0_hhhh_AhAh(unitarity_s,1,2,1,2,17,2) 
scatter_matrix1(17,3) = a0_hhhh_AhAh(unitarity_s,1,2,1,3,17,3) 
scatter_matrix1(17,4) = a0_hhhh_AhAh(unitarity_s,1,2,2,2,17,4) 
scatter_matrix1(17,5) = a0_hhhh_AhAh(unitarity_s,1,2,2,3,17,5) 
scatter_matrix1(17,6) = a0_hhhh_AhAh(unitarity_s,1,2,3,3,17,6) 
scatter_matrix1(17,7) = a0_hhhh_Ahhh(unitarity_s,1,2,1,1,17,7) 
scatter_matrix1(17,8) = a0_hhhh_Ahhh(unitarity_s,1,2,1,2,17,8) 
scatter_matrix1(17,9) = a0_hhhh_Ahhh(unitarity_s,1,2,1,3,17,9) 
scatter_matrix1(17,10) = a0_hhhh_Ahhh(unitarity_s,1,2,2,1,17,10) 
scatter_matrix1(17,11) = a0_hhhh_Ahhh(unitarity_s,1,2,2,2,17,11) 
scatter_matrix1(17,12) = a0_hhhh_Ahhh(unitarity_s,1,2,2,3,17,12) 
scatter_matrix1(17,13) = a0_hhhh_Ahhh(unitarity_s,1,2,3,1,17,13) 
scatter_matrix1(17,14) = a0_hhhh_Ahhh(unitarity_s,1,2,3,2,17,14) 
scatter_matrix1(17,15) = a0_hhhh_Ahhh(unitarity_s,1,2,3,3,17,15) 
scatter_matrix1(17,16) = a0_hhhh_hhhh(unitarity_s,1,2,1,1,17,16) 
scatter_matrix1(17,17) = a0_hhhh_hhhh(unitarity_s,1,2,1,2,17,17) 
scatter_matrix1(17,18) = a0_hhhh_hhhh(unitarity_s,1,2,1,3,17,18) 
scatter_matrix1(17,19) = a0_hhhh_hhhh(unitarity_s,1,2,2,2,17,19) 
scatter_matrix1(17,20) = a0_hhhh_hhhh(unitarity_s,1,2,2,3,17,20) 
scatter_matrix1(17,21) = a0_hhhh_hhhh(unitarity_s,1,2,3,3,17,21) 
scatter_matrix1(17,22) = a0_hhhh_HpmHpmc(unitarity_s,1,2,1,1,17,22) 
scatter_matrix1(17,23) = a0_hhhh_HpmHpmc(unitarity_s,1,2,1,2,17,23) 
scatter_matrix1(17,24) = a0_hhhh_HpmHpmc(unitarity_s,1,2,2,1,17,24) 
scatter_matrix1(17,25) = a0_hhhh_HpmHpmc(unitarity_s,1,2,2,2,17,25) 
scatter_matrix1(18,1) = a0_hhhh_AhAh(unitarity_s,1,3,1,1,18,1) 
scatter_matrix1(18,2) = a0_hhhh_AhAh(unitarity_s,1,3,1,2,18,2) 
scatter_matrix1(18,3) = a0_hhhh_AhAh(unitarity_s,1,3,1,3,18,3) 
scatter_matrix1(18,4) = a0_hhhh_AhAh(unitarity_s,1,3,2,2,18,4) 
scatter_matrix1(18,5) = a0_hhhh_AhAh(unitarity_s,1,3,2,3,18,5) 
scatter_matrix1(18,6) = a0_hhhh_AhAh(unitarity_s,1,3,3,3,18,6) 
scatter_matrix1(18,7) = a0_hhhh_Ahhh(unitarity_s,1,3,1,1,18,7) 
scatter_matrix1(18,8) = a0_hhhh_Ahhh(unitarity_s,1,3,1,2,18,8) 
scatter_matrix1(18,9) = a0_hhhh_Ahhh(unitarity_s,1,3,1,3,18,9) 
scatter_matrix1(18,10) = a0_hhhh_Ahhh(unitarity_s,1,3,2,1,18,10) 
scatter_matrix1(18,11) = a0_hhhh_Ahhh(unitarity_s,1,3,2,2,18,11) 
scatter_matrix1(18,12) = a0_hhhh_Ahhh(unitarity_s,1,3,2,3,18,12) 
scatter_matrix1(18,13) = a0_hhhh_Ahhh(unitarity_s,1,3,3,1,18,13) 
scatter_matrix1(18,14) = a0_hhhh_Ahhh(unitarity_s,1,3,3,2,18,14) 
scatter_matrix1(18,15) = a0_hhhh_Ahhh(unitarity_s,1,3,3,3,18,15) 
scatter_matrix1(18,16) = a0_hhhh_hhhh(unitarity_s,1,3,1,1,18,16) 
scatter_matrix1(18,17) = a0_hhhh_hhhh(unitarity_s,1,3,1,2,18,17) 
scatter_matrix1(18,18) = a0_hhhh_hhhh(unitarity_s,1,3,1,3,18,18) 
scatter_matrix1(18,19) = a0_hhhh_hhhh(unitarity_s,1,3,2,2,18,19) 
scatter_matrix1(18,20) = a0_hhhh_hhhh(unitarity_s,1,3,2,3,18,20) 
scatter_matrix1(18,21) = a0_hhhh_hhhh(unitarity_s,1,3,3,3,18,21) 
scatter_matrix1(18,22) = a0_hhhh_HpmHpmc(unitarity_s,1,3,1,1,18,22) 
scatter_matrix1(18,23) = a0_hhhh_HpmHpmc(unitarity_s,1,3,1,2,18,23) 
scatter_matrix1(18,24) = a0_hhhh_HpmHpmc(unitarity_s,1,3,2,1,18,24) 
scatter_matrix1(18,25) = a0_hhhh_HpmHpmc(unitarity_s,1,3,2,2,18,25) 
scatter_matrix1(19,1) = a0_hhhh_AhAh(unitarity_s,2,2,1,1,19,1) 
scatter_matrix1(19,2) = a0_hhhh_AhAh(unitarity_s,2,2,1,2,19,2) 
scatter_matrix1(19,3) = a0_hhhh_AhAh(unitarity_s,2,2,1,3,19,3) 
scatter_matrix1(19,4) = a0_hhhh_AhAh(unitarity_s,2,2,2,2,19,4) 
scatter_matrix1(19,5) = a0_hhhh_AhAh(unitarity_s,2,2,2,3,19,5) 
scatter_matrix1(19,6) = a0_hhhh_AhAh(unitarity_s,2,2,3,3,19,6) 
scatter_matrix1(19,7) = a0_hhhh_Ahhh(unitarity_s,2,2,1,1,19,7) 
scatter_matrix1(19,8) = a0_hhhh_Ahhh(unitarity_s,2,2,1,2,19,8) 
scatter_matrix1(19,9) = a0_hhhh_Ahhh(unitarity_s,2,2,1,3,19,9) 
scatter_matrix1(19,10) = a0_hhhh_Ahhh(unitarity_s,2,2,2,1,19,10) 
scatter_matrix1(19,11) = a0_hhhh_Ahhh(unitarity_s,2,2,2,2,19,11) 
scatter_matrix1(19,12) = a0_hhhh_Ahhh(unitarity_s,2,2,2,3,19,12) 
scatter_matrix1(19,13) = a0_hhhh_Ahhh(unitarity_s,2,2,3,1,19,13) 
scatter_matrix1(19,14) = a0_hhhh_Ahhh(unitarity_s,2,2,3,2,19,14) 
scatter_matrix1(19,15) = a0_hhhh_Ahhh(unitarity_s,2,2,3,3,19,15) 
scatter_matrix1(19,16) = a0_hhhh_hhhh(unitarity_s,2,2,1,1,19,16) 
scatter_matrix1(19,17) = a0_hhhh_hhhh(unitarity_s,2,2,1,2,19,17) 
scatter_matrix1(19,18) = a0_hhhh_hhhh(unitarity_s,2,2,1,3,19,18) 
scatter_matrix1(19,19) = a0_hhhh_hhhh(unitarity_s,2,2,2,2,19,19) 
scatter_matrix1(19,20) = a0_hhhh_hhhh(unitarity_s,2,2,2,3,19,20) 
scatter_matrix1(19,21) = a0_hhhh_hhhh(unitarity_s,2,2,3,3,19,21) 
scatter_matrix1(19,22) = a0_hhhh_HpmHpmc(unitarity_s,2,2,1,1,19,22) 
scatter_matrix1(19,23) = a0_hhhh_HpmHpmc(unitarity_s,2,2,1,2,19,23) 
scatter_matrix1(19,24) = a0_hhhh_HpmHpmc(unitarity_s,2,2,2,1,19,24) 
scatter_matrix1(19,25) = a0_hhhh_HpmHpmc(unitarity_s,2,2,2,2,19,25) 
scatter_matrix1(20,1) = a0_hhhh_AhAh(unitarity_s,2,3,1,1,20,1) 
scatter_matrix1(20,2) = a0_hhhh_AhAh(unitarity_s,2,3,1,2,20,2) 
scatter_matrix1(20,3) = a0_hhhh_AhAh(unitarity_s,2,3,1,3,20,3) 
scatter_matrix1(20,4) = a0_hhhh_AhAh(unitarity_s,2,3,2,2,20,4) 
scatter_matrix1(20,5) = a0_hhhh_AhAh(unitarity_s,2,3,2,3,20,5) 
scatter_matrix1(20,6) = a0_hhhh_AhAh(unitarity_s,2,3,3,3,20,6) 
scatter_matrix1(20,7) = a0_hhhh_Ahhh(unitarity_s,2,3,1,1,20,7) 
scatter_matrix1(20,8) = a0_hhhh_Ahhh(unitarity_s,2,3,1,2,20,8) 
scatter_matrix1(20,9) = a0_hhhh_Ahhh(unitarity_s,2,3,1,3,20,9) 
scatter_matrix1(20,10) = a0_hhhh_Ahhh(unitarity_s,2,3,2,1,20,10) 
scatter_matrix1(20,11) = a0_hhhh_Ahhh(unitarity_s,2,3,2,2,20,11) 
scatter_matrix1(20,12) = a0_hhhh_Ahhh(unitarity_s,2,3,2,3,20,12) 
scatter_matrix1(20,13) = a0_hhhh_Ahhh(unitarity_s,2,3,3,1,20,13) 
scatter_matrix1(20,14) = a0_hhhh_Ahhh(unitarity_s,2,3,3,2,20,14) 
scatter_matrix1(20,15) = a0_hhhh_Ahhh(unitarity_s,2,3,3,3,20,15) 
scatter_matrix1(20,16) = a0_hhhh_hhhh(unitarity_s,2,3,1,1,20,16) 
scatter_matrix1(20,17) = a0_hhhh_hhhh(unitarity_s,2,3,1,2,20,17) 
scatter_matrix1(20,18) = a0_hhhh_hhhh(unitarity_s,2,3,1,3,20,18) 
scatter_matrix1(20,19) = a0_hhhh_hhhh(unitarity_s,2,3,2,2,20,19) 
scatter_matrix1(20,20) = a0_hhhh_hhhh(unitarity_s,2,3,2,3,20,20) 
scatter_matrix1(20,21) = a0_hhhh_hhhh(unitarity_s,2,3,3,3,20,21) 
scatter_matrix1(20,22) = a0_hhhh_HpmHpmc(unitarity_s,2,3,1,1,20,22) 
scatter_matrix1(20,23) = a0_hhhh_HpmHpmc(unitarity_s,2,3,1,2,20,23) 
scatter_matrix1(20,24) = a0_hhhh_HpmHpmc(unitarity_s,2,3,2,1,20,24) 
scatter_matrix1(20,25) = a0_hhhh_HpmHpmc(unitarity_s,2,3,2,2,20,25) 
scatter_matrix1(21,1) = a0_hhhh_AhAh(unitarity_s,3,3,1,1,21,1) 
scatter_matrix1(21,2) = a0_hhhh_AhAh(unitarity_s,3,3,1,2,21,2) 
scatter_matrix1(21,3) = a0_hhhh_AhAh(unitarity_s,3,3,1,3,21,3) 
scatter_matrix1(21,4) = a0_hhhh_AhAh(unitarity_s,3,3,2,2,21,4) 
scatter_matrix1(21,5) = a0_hhhh_AhAh(unitarity_s,3,3,2,3,21,5) 
scatter_matrix1(21,6) = a0_hhhh_AhAh(unitarity_s,3,3,3,3,21,6) 
scatter_matrix1(21,7) = a0_hhhh_Ahhh(unitarity_s,3,3,1,1,21,7) 
scatter_matrix1(21,8) = a0_hhhh_Ahhh(unitarity_s,3,3,1,2,21,8) 
scatter_matrix1(21,9) = a0_hhhh_Ahhh(unitarity_s,3,3,1,3,21,9) 
scatter_matrix1(21,10) = a0_hhhh_Ahhh(unitarity_s,3,3,2,1,21,10) 
scatter_matrix1(21,11) = a0_hhhh_Ahhh(unitarity_s,3,3,2,2,21,11) 
scatter_matrix1(21,12) = a0_hhhh_Ahhh(unitarity_s,3,3,2,3,21,12) 
scatter_matrix1(21,13) = a0_hhhh_Ahhh(unitarity_s,3,3,3,1,21,13) 
scatter_matrix1(21,14) = a0_hhhh_Ahhh(unitarity_s,3,3,3,2,21,14) 
scatter_matrix1(21,15) = a0_hhhh_Ahhh(unitarity_s,3,3,3,3,21,15) 
scatter_matrix1(21,16) = a0_hhhh_hhhh(unitarity_s,3,3,1,1,21,16) 
scatter_matrix1(21,17) = a0_hhhh_hhhh(unitarity_s,3,3,1,2,21,17) 
scatter_matrix1(21,18) = a0_hhhh_hhhh(unitarity_s,3,3,1,3,21,18) 
scatter_matrix1(21,19) = a0_hhhh_hhhh(unitarity_s,3,3,2,2,21,19) 
scatter_matrix1(21,20) = a0_hhhh_hhhh(unitarity_s,3,3,2,3,21,20) 
scatter_matrix1(21,21) = a0_hhhh_hhhh(unitarity_s,3,3,3,3,21,21) 
scatter_matrix1(21,22) = a0_hhhh_HpmHpmc(unitarity_s,3,3,1,1,21,22) 
scatter_matrix1(21,23) = a0_hhhh_HpmHpmc(unitarity_s,3,3,1,2,21,23) 
scatter_matrix1(21,24) = a0_hhhh_HpmHpmc(unitarity_s,3,3,2,1,21,24) 
scatter_matrix1(21,25) = a0_hhhh_HpmHpmc(unitarity_s,3,3,2,2,21,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,1) = a0_HpmHpmc_AhAh(unitarity_s,1,1,1,1,22,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,2) = a0_HpmHpmc_AhAh(unitarity_s,1,1,1,2,22,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,3) = a0_HpmHpmc_AhAh(unitarity_s,1,1,1,3,22,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,4) = a0_HpmHpmc_AhAh(unitarity_s,1,1,2,2,22,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,5) = a0_HpmHpmc_AhAh(unitarity_s,1,1,2,3,22,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,6) = a0_HpmHpmc_AhAh(unitarity_s,1,1,3,3,22,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,7) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,1,1,22,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,8) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,1,2,22,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,9) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,1,3,22,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,10) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,2,1,22,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,11) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,2,2,22,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,12) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,2,3,22,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,13) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,3,1,22,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,14) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,3,2,22,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,15) = a0_HpmHpmc_Ahhh(unitarity_s,1,1,3,3,22,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,16) = a0_HpmHpmc_hhhh(unitarity_s,1,1,1,1,22,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,17) = a0_HpmHpmc_hhhh(unitarity_s,1,1,1,2,22,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,18) = a0_HpmHpmc_hhhh(unitarity_s,1,1,1,3,22,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,19) = a0_HpmHpmc_hhhh(unitarity_s,1,1,2,2,22,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,20) = a0_HpmHpmc_hhhh(unitarity_s,1,1,2,3,22,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,21) = a0_HpmHpmc_hhhh(unitarity_s,1,1,3,3,22,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,22) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,1,1,1,22,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,23) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,1,1,2,22,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,24) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,1,2,1,22,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(22,25) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,1,2,2,22,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,1) = a0_HpmHpmc_AhAh(unitarity_s,1,2,1,1,23,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,2) = a0_HpmHpmc_AhAh(unitarity_s,1,2,1,2,23,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,3) = a0_HpmHpmc_AhAh(unitarity_s,1,2,1,3,23,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,4) = a0_HpmHpmc_AhAh(unitarity_s,1,2,2,2,23,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,5) = a0_HpmHpmc_AhAh(unitarity_s,1,2,2,3,23,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,6) = a0_HpmHpmc_AhAh(unitarity_s,1,2,3,3,23,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,7) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,1,1,23,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,8) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,1,2,23,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,9) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,1,3,23,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,10) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,2,1,23,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,11) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,2,2,23,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,12) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,2,3,23,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,13) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,3,1,23,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,14) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,3,2,23,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,15) = a0_HpmHpmc_Ahhh(unitarity_s,1,2,3,3,23,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,16) = a0_HpmHpmc_hhhh(unitarity_s,1,2,1,1,23,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,17) = a0_HpmHpmc_hhhh(unitarity_s,1,2,1,2,23,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,18) = a0_HpmHpmc_hhhh(unitarity_s,1,2,1,3,23,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,19) = a0_HpmHpmc_hhhh(unitarity_s,1,2,2,2,23,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,20) = a0_HpmHpmc_hhhh(unitarity_s,1,2,2,3,23,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,21) = a0_HpmHpmc_hhhh(unitarity_s,1,2,3,3,23,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,22) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,2,1,1,23,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,23) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,2,1,2,23,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,24) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,2,2,1,23,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(23,25) = a0_HpmHpmc_HpmHpmc(unitarity_s,1,2,2,2,23,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,1) = a0_HpmHpmc_AhAh(unitarity_s,2,1,1,1,24,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,2) = a0_HpmHpmc_AhAh(unitarity_s,2,1,1,2,24,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,3) = a0_HpmHpmc_AhAh(unitarity_s,2,1,1,3,24,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,4) = a0_HpmHpmc_AhAh(unitarity_s,2,1,2,2,24,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,5) = a0_HpmHpmc_AhAh(unitarity_s,2,1,2,3,24,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,6) = a0_HpmHpmc_AhAh(unitarity_s,2,1,3,3,24,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,7) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,1,1,24,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,8) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,1,2,24,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,9) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,1,3,24,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,10) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,2,1,24,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,11) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,2,2,24,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,12) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,2,3,24,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,13) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,3,1,24,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,14) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,3,2,24,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,15) = a0_HpmHpmc_Ahhh(unitarity_s,2,1,3,3,24,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,16) = a0_HpmHpmc_hhhh(unitarity_s,2,1,1,1,24,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,17) = a0_HpmHpmc_hhhh(unitarity_s,2,1,1,2,24,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,18) = a0_HpmHpmc_hhhh(unitarity_s,2,1,1,3,24,18) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,19) = a0_HpmHpmc_hhhh(unitarity_s,2,1,2,2,24,19) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,20) = a0_HpmHpmc_hhhh(unitarity_s,2,1,2,3,24,20) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,21) = a0_HpmHpmc_hhhh(unitarity_s,2,1,3,3,24,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,22) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,1,1,1,24,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,23) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,1,1,2,24,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,24) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,1,2,1,24,24) 
If (IncludeGoldstoneExternal) scatter_matrix1(24,25) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,1,2,2,24,25) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,1) = a0_HpmHpmc_AhAh(unitarity_s,2,2,1,1,25,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,2) = a0_HpmHpmc_AhAh(unitarity_s,2,2,1,2,25,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,3) = a0_HpmHpmc_AhAh(unitarity_s,2,2,1,3,25,3) 
scatter_matrix1(25,4) = a0_HpmHpmc_AhAh(unitarity_s,2,2,2,2,25,4) 
scatter_matrix1(25,5) = a0_HpmHpmc_AhAh(unitarity_s,2,2,2,3,25,5) 
scatter_matrix1(25,6) = a0_HpmHpmc_AhAh(unitarity_s,2,2,3,3,25,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,7) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,1,1,25,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,8) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,1,2,25,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,9) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,1,3,25,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,10) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,2,1,25,10) 
scatter_matrix1(25,11) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,2,2,25,11) 
scatter_matrix1(25,12) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,2,3,25,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,13) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,3,1,25,13) 
scatter_matrix1(25,14) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,3,2,25,14) 
scatter_matrix1(25,15) = a0_HpmHpmc_Ahhh(unitarity_s,2,2,3,3,25,15) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,16) = a0_HpmHpmc_hhhh(unitarity_s,2,2,1,1,25,16) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,17) = a0_HpmHpmc_hhhh(unitarity_s,2,2,1,2,25,17) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,18) = a0_HpmHpmc_hhhh(unitarity_s,2,2,1,3,25,18) 
scatter_matrix1(25,19) = a0_HpmHpmc_hhhh(unitarity_s,2,2,2,2,25,19) 
scatter_matrix1(25,20) = a0_HpmHpmc_hhhh(unitarity_s,2,2,2,3,25,20) 
scatter_matrix1(25,21) = a0_HpmHpmc_hhhh(unitarity_s,2,2,3,3,25,21) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,22) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,2,1,1,25,22) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,23) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,2,1,2,25,23) 
If (IncludeGoldstoneExternal) scatter_matrix1(25,24) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,2,2,1,25,24) 
scatter_matrix1(25,25) = a0_HpmHpmc_HpmHpmc(unitarity_s,2,2,2,2,25,25) 


Select CASE (TUcutLevel)  
CASE (2) 
  scatter_matrix1B = scatter_matrix1
Do i=1,25 
  If (RemoveTUpoles(i).eq.1) Then
   scatter_matrix1(i,:) = 0._dp 
   scatter_matrix1(:,i) = 0._dp 
    If (AddR) scatter_matrix1(i,i) = -1111._dp ! to get a fixed order of the eigenvalues 
   scatter_matrix1B(:,i) = 0._dp 
  Else 
   scatter_matrix1B(i,:) = 0._dp 
  End If 
End Do 
CASE (1) 
If ((Abs(max_element_removed)/MaxVal(Abs(scatter_matrix1))).gt.cut_elements) Then 
 ! Write(*,*)  (Abs(max_element_removed)/MaxVal(Abs(scatter_matrix1)))  
End if 
End Select 
If (.not.pole_present) Then 
Call EigenSystem(scatter_matrix1,eigenvalues_matrix1,rot_matrix1,ierr,test)
 If ((TUcutLevel.eq.2).and.(AddR)) Then ! Calculate 'R' 
  scatter_matrix1B = MatMul(scatter_matrix1B,Conjg(Transpose(rot_matrix1))) 
   Do i=1,25 
    If (eigenvalues_matrix1 (i).lt.-1000._dp) Then
     eigenvalues_matrix1(i) = 0._dp 
    Else 
     eigenvalues_matrix1(i) = sqrt(eigenvalues_matrix1(i)**2+  sum(scatter_matrix1B(i,:)**2) )
    End If
   End Do 
 End If 
scattering_eigenvalue_trilinears=MaxVal(Abs(eigenvalues_matrix1)) 
Else 
  scattering_eigenvalue_trilinears = 0._dp 
End if 
If (scattering_eigenvalue_trilinears.gt.max_scattering_eigenvalue_trilinears) Then 
   max_scattering_eigenvalue_trilinears=scattering_eigenvalue_trilinears 
   unitarity_s_best=sqrt(unitarity_s)
End if 
 
!! 2. sub-matrix  
Pole_Present = .false. 
max_element_removed = 0._dp 
RemoveTUpoles = 0 
scatter_matrix2=0._dp 
If (IncludeGoldstoneExternal) scatter_matrix2(1,1) = a0_AhHpmc_AhHpm(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,2) = a0_AhHpmc_AhHpm(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,3) = a0_AhHpmc_AhHpm(unitarity_s,1,1,2,1,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,4) = a0_AhHpmc_AhHpm(unitarity_s,1,1,2,2,1,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,5) = a0_AhHpmc_AhHpm(unitarity_s,1,1,3,1,1,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,6) = a0_AhHpmc_AhHpm(unitarity_s,1,1,3,2,1,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,7) = a0_AhHpmc_hhHpm(unitarity_s,1,1,1,1,1,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,8) = a0_AhHpmc_hhHpm(unitarity_s,1,1,1,2,1,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,9) = a0_AhHpmc_hhHpm(unitarity_s,1,1,2,1,1,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,10) = a0_AhHpmc_hhHpm(unitarity_s,1,1,2,2,1,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,11) = a0_AhHpmc_hhHpm(unitarity_s,1,1,3,1,1,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,12) = a0_AhHpmc_hhHpm(unitarity_s,1,1,3,2,1,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,1) = a0_AhHpmc_AhHpm(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,2) = a0_AhHpmc_AhHpm(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,3) = a0_AhHpmc_AhHpm(unitarity_s,1,2,2,1,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,4) = a0_AhHpmc_AhHpm(unitarity_s,1,2,2,2,2,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,5) = a0_AhHpmc_AhHpm(unitarity_s,1,2,3,1,2,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,6) = a0_AhHpmc_AhHpm(unitarity_s,1,2,3,2,2,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,7) = a0_AhHpmc_hhHpm(unitarity_s,1,2,1,1,2,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,8) = a0_AhHpmc_hhHpm(unitarity_s,1,2,1,2,2,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,9) = a0_AhHpmc_hhHpm(unitarity_s,1,2,2,1,2,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,10) = a0_AhHpmc_hhHpm(unitarity_s,1,2,2,2,2,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,11) = a0_AhHpmc_hhHpm(unitarity_s,1,2,3,1,2,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,12) = a0_AhHpmc_hhHpm(unitarity_s,1,2,3,2,2,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,1) = a0_AhHpmc_AhHpm(unitarity_s,2,1,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,2) = a0_AhHpmc_AhHpm(unitarity_s,2,1,1,2,3,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,3) = a0_AhHpmc_AhHpm(unitarity_s,2,1,2,1,3,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,4) = a0_AhHpmc_AhHpm(unitarity_s,2,1,2,2,3,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,5) = a0_AhHpmc_AhHpm(unitarity_s,2,1,3,1,3,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,6) = a0_AhHpmc_AhHpm(unitarity_s,2,1,3,2,3,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,7) = a0_AhHpmc_hhHpm(unitarity_s,2,1,1,1,3,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,8) = a0_AhHpmc_hhHpm(unitarity_s,2,1,1,2,3,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,9) = a0_AhHpmc_hhHpm(unitarity_s,2,1,2,1,3,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,10) = a0_AhHpmc_hhHpm(unitarity_s,2,1,2,2,3,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,11) = a0_AhHpmc_hhHpm(unitarity_s,2,1,3,1,3,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,12) = a0_AhHpmc_hhHpm(unitarity_s,2,1,3,2,3,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,1) = a0_AhHpmc_AhHpm(unitarity_s,2,2,1,1,4,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,2) = a0_AhHpmc_AhHpm(unitarity_s,2,2,1,2,4,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,3) = a0_AhHpmc_AhHpm(unitarity_s,2,2,2,1,4,3) 
scatter_matrix2(4,4) = a0_AhHpmc_AhHpm(unitarity_s,2,2,2,2,4,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,5) = a0_AhHpmc_AhHpm(unitarity_s,2,2,3,1,4,5) 
scatter_matrix2(4,6) = a0_AhHpmc_AhHpm(unitarity_s,2,2,3,2,4,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,7) = a0_AhHpmc_hhHpm(unitarity_s,2,2,1,1,4,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,8) = a0_AhHpmc_hhHpm(unitarity_s,2,2,1,2,4,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,9) = a0_AhHpmc_hhHpm(unitarity_s,2,2,2,1,4,9) 
scatter_matrix2(4,10) = a0_AhHpmc_hhHpm(unitarity_s,2,2,2,2,4,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,11) = a0_AhHpmc_hhHpm(unitarity_s,2,2,3,1,4,11) 
scatter_matrix2(4,12) = a0_AhHpmc_hhHpm(unitarity_s,2,2,3,2,4,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,1) = a0_AhHpmc_AhHpm(unitarity_s,3,1,1,1,5,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,2) = a0_AhHpmc_AhHpm(unitarity_s,3,1,1,2,5,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,3) = a0_AhHpmc_AhHpm(unitarity_s,3,1,2,1,5,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,4) = a0_AhHpmc_AhHpm(unitarity_s,3,1,2,2,5,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,5) = a0_AhHpmc_AhHpm(unitarity_s,3,1,3,1,5,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,6) = a0_AhHpmc_AhHpm(unitarity_s,3,1,3,2,5,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,7) = a0_AhHpmc_hhHpm(unitarity_s,3,1,1,1,5,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,8) = a0_AhHpmc_hhHpm(unitarity_s,3,1,1,2,5,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,9) = a0_AhHpmc_hhHpm(unitarity_s,3,1,2,1,5,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,10) = a0_AhHpmc_hhHpm(unitarity_s,3,1,2,2,5,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,11) = a0_AhHpmc_hhHpm(unitarity_s,3,1,3,1,5,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,12) = a0_AhHpmc_hhHpm(unitarity_s,3,1,3,2,5,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,1) = a0_AhHpmc_AhHpm(unitarity_s,3,2,1,1,6,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,2) = a0_AhHpmc_AhHpm(unitarity_s,3,2,1,2,6,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,3) = a0_AhHpmc_AhHpm(unitarity_s,3,2,2,1,6,3) 
scatter_matrix2(6,4) = a0_AhHpmc_AhHpm(unitarity_s,3,2,2,2,6,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,5) = a0_AhHpmc_AhHpm(unitarity_s,3,2,3,1,6,5) 
scatter_matrix2(6,6) = a0_AhHpmc_AhHpm(unitarity_s,3,2,3,2,6,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,7) = a0_AhHpmc_hhHpm(unitarity_s,3,2,1,1,6,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,8) = a0_AhHpmc_hhHpm(unitarity_s,3,2,1,2,6,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,9) = a0_AhHpmc_hhHpm(unitarity_s,3,2,2,1,6,9) 
scatter_matrix2(6,10) = a0_AhHpmc_hhHpm(unitarity_s,3,2,2,2,6,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,11) = a0_AhHpmc_hhHpm(unitarity_s,3,2,3,1,6,11) 
scatter_matrix2(6,12) = a0_AhHpmc_hhHpm(unitarity_s,3,2,3,2,6,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,1) = a0_hhHpmc_AhHpm(unitarity_s,1,1,1,1,7,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,2) = a0_hhHpmc_AhHpm(unitarity_s,1,1,1,2,7,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,3) = a0_hhHpmc_AhHpm(unitarity_s,1,1,2,1,7,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,4) = a0_hhHpmc_AhHpm(unitarity_s,1,1,2,2,7,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,5) = a0_hhHpmc_AhHpm(unitarity_s,1,1,3,1,7,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,6) = a0_hhHpmc_AhHpm(unitarity_s,1,1,3,2,7,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,7) = a0_hhHpmc_hhHpm(unitarity_s,1,1,1,1,7,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,8) = a0_hhHpmc_hhHpm(unitarity_s,1,1,1,2,7,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,9) = a0_hhHpmc_hhHpm(unitarity_s,1,1,2,1,7,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,10) = a0_hhHpmc_hhHpm(unitarity_s,1,1,2,2,7,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,11) = a0_hhHpmc_hhHpm(unitarity_s,1,1,3,1,7,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,12) = a0_hhHpmc_hhHpm(unitarity_s,1,1,3,2,7,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,1) = a0_hhHpmc_AhHpm(unitarity_s,1,2,1,1,8,1) 
scatter_matrix2(8,2) = a0_hhHpmc_AhHpm(unitarity_s,1,2,1,2,8,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,3) = a0_hhHpmc_AhHpm(unitarity_s,1,2,2,1,8,3) 
scatter_matrix2(8,4) = a0_hhHpmc_AhHpm(unitarity_s,1,2,2,2,8,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,5) = a0_hhHpmc_AhHpm(unitarity_s,1,2,3,1,8,5) 
scatter_matrix2(8,6) = a0_hhHpmc_AhHpm(unitarity_s,1,2,3,2,8,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,7) = a0_hhHpmc_hhHpm(unitarity_s,1,2,1,1,8,7) 
scatter_matrix2(8,8) = a0_hhHpmc_hhHpm(unitarity_s,1,2,1,2,8,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,9) = a0_hhHpmc_hhHpm(unitarity_s,1,2,2,1,8,9) 
scatter_matrix2(8,10) = a0_hhHpmc_hhHpm(unitarity_s,1,2,2,2,8,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,11) = a0_hhHpmc_hhHpm(unitarity_s,1,2,3,1,8,11) 
scatter_matrix2(8,12) = a0_hhHpmc_hhHpm(unitarity_s,1,2,3,2,8,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,1) = a0_hhHpmc_AhHpm(unitarity_s,2,1,1,1,9,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,2) = a0_hhHpmc_AhHpm(unitarity_s,2,1,1,2,9,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,3) = a0_hhHpmc_AhHpm(unitarity_s,2,1,2,1,9,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,4) = a0_hhHpmc_AhHpm(unitarity_s,2,1,2,2,9,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,5) = a0_hhHpmc_AhHpm(unitarity_s,2,1,3,1,9,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,6) = a0_hhHpmc_AhHpm(unitarity_s,2,1,3,2,9,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,7) = a0_hhHpmc_hhHpm(unitarity_s,2,1,1,1,9,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,8) = a0_hhHpmc_hhHpm(unitarity_s,2,1,1,2,9,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,9) = a0_hhHpmc_hhHpm(unitarity_s,2,1,2,1,9,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,10) = a0_hhHpmc_hhHpm(unitarity_s,2,1,2,2,9,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,11) = a0_hhHpmc_hhHpm(unitarity_s,2,1,3,1,9,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(9,12) = a0_hhHpmc_hhHpm(unitarity_s,2,1,3,2,9,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(10,1) = a0_hhHpmc_AhHpm(unitarity_s,2,2,1,1,10,1) 
scatter_matrix2(10,2) = a0_hhHpmc_AhHpm(unitarity_s,2,2,1,2,10,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(10,3) = a0_hhHpmc_AhHpm(unitarity_s,2,2,2,1,10,3) 
scatter_matrix2(10,4) = a0_hhHpmc_AhHpm(unitarity_s,2,2,2,2,10,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(10,5) = a0_hhHpmc_AhHpm(unitarity_s,2,2,3,1,10,5) 
scatter_matrix2(10,6) = a0_hhHpmc_AhHpm(unitarity_s,2,2,3,2,10,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(10,7) = a0_hhHpmc_hhHpm(unitarity_s,2,2,1,1,10,7) 
scatter_matrix2(10,8) = a0_hhHpmc_hhHpm(unitarity_s,2,2,1,2,10,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(10,9) = a0_hhHpmc_hhHpm(unitarity_s,2,2,2,1,10,9) 
scatter_matrix2(10,10) = a0_hhHpmc_hhHpm(unitarity_s,2,2,2,2,10,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(10,11) = a0_hhHpmc_hhHpm(unitarity_s,2,2,3,1,10,11) 
scatter_matrix2(10,12) = a0_hhHpmc_hhHpm(unitarity_s,2,2,3,2,10,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,1) = a0_hhHpmc_AhHpm(unitarity_s,3,1,1,1,11,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,2) = a0_hhHpmc_AhHpm(unitarity_s,3,1,1,2,11,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,3) = a0_hhHpmc_AhHpm(unitarity_s,3,1,2,1,11,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,4) = a0_hhHpmc_AhHpm(unitarity_s,3,1,2,2,11,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,5) = a0_hhHpmc_AhHpm(unitarity_s,3,1,3,1,11,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,6) = a0_hhHpmc_AhHpm(unitarity_s,3,1,3,2,11,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,7) = a0_hhHpmc_hhHpm(unitarity_s,3,1,1,1,11,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,8) = a0_hhHpmc_hhHpm(unitarity_s,3,1,1,2,11,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,9) = a0_hhHpmc_hhHpm(unitarity_s,3,1,2,1,11,9) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,10) = a0_hhHpmc_hhHpm(unitarity_s,3,1,2,2,11,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,11) = a0_hhHpmc_hhHpm(unitarity_s,3,1,3,1,11,11) 
If (IncludeGoldstoneExternal) scatter_matrix2(11,12) = a0_hhHpmc_hhHpm(unitarity_s,3,1,3,2,11,12) 
If (IncludeGoldstoneExternal) scatter_matrix2(12,1) = a0_hhHpmc_AhHpm(unitarity_s,3,2,1,1,12,1) 
scatter_matrix2(12,2) = a0_hhHpmc_AhHpm(unitarity_s,3,2,1,2,12,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(12,3) = a0_hhHpmc_AhHpm(unitarity_s,3,2,2,1,12,3) 
scatter_matrix2(12,4) = a0_hhHpmc_AhHpm(unitarity_s,3,2,2,2,12,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(12,5) = a0_hhHpmc_AhHpm(unitarity_s,3,2,3,1,12,5) 
scatter_matrix2(12,6) = a0_hhHpmc_AhHpm(unitarity_s,3,2,3,2,12,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(12,7) = a0_hhHpmc_hhHpm(unitarity_s,3,2,1,1,12,7) 
scatter_matrix2(12,8) = a0_hhHpmc_hhHpm(unitarity_s,3,2,1,2,12,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(12,9) = a0_hhHpmc_hhHpm(unitarity_s,3,2,2,1,12,9) 
scatter_matrix2(12,10) = a0_hhHpmc_hhHpm(unitarity_s,3,2,2,2,12,10) 
If (IncludeGoldstoneExternal) scatter_matrix2(12,11) = a0_hhHpmc_hhHpm(unitarity_s,3,2,3,1,12,11) 
scatter_matrix2(12,12) = a0_hhHpmc_hhHpm(unitarity_s,3,2,3,2,12,12) 


Select CASE (TUcutLevel)  
CASE (2) 
  scatter_matrix2B = scatter_matrix2
Do i=1,12 
  If (RemoveTUpoles(i).eq.1) Then
   scatter_matrix2(i,:) = 0._dp 
   scatter_matrix2(:,i) = 0._dp 
    If (AddR) scatter_matrix2(i,i) = -1111._dp ! to get a fixed order of the eigenvalues 
   scatter_matrix2B(:,i) = 0._dp 
  Else 
   scatter_matrix2B(i,:) = 0._dp 
  End If 
End Do 
CASE (1) 
If ((Abs(max_element_removed)/MaxVal(Abs(scatter_matrix2))).gt.cut_elements) Then 
 ! Write(*,*)  (Abs(max_element_removed)/MaxVal(Abs(scatter_matrix2)))  
End if 
End Select 
If (.not.pole_present) Then 
Call EigenSystem(scatter_matrix2,eigenvalues_matrix2,rot_matrix2,ierr,test)
 If ((TUcutLevel.eq.2).and.(AddR)) Then ! Calculate 'R' 
  scatter_matrix2B = MatMul(scatter_matrix2B,Conjg(Transpose(rot_matrix2))) 
   Do i=1,12 
    If (eigenvalues_matrix2 (i).lt.-1000._dp) Then
     eigenvalues_matrix2(i) = 0._dp 
    Else 
     eigenvalues_matrix2(i) = sqrt(eigenvalues_matrix2(i)**2+  sum(scatter_matrix2B(i,:)**2) )
    End If
   End Do 
 End If 
scattering_eigenvalue_trilinears=MaxVal(Abs(eigenvalues_matrix2)) 
Else 
  scattering_eigenvalue_trilinears = 0._dp 
End if 
If (scattering_eigenvalue_trilinears.gt.max_scattering_eigenvalue_trilinears) Then 
   max_scattering_eigenvalue_trilinears=scattering_eigenvalue_trilinears 
   unitarity_s_best=sqrt(unitarity_s)
End if 
 
!! 3. sub-matrix  
Pole_Present = .false. 
max_element_removed = 0._dp 
RemoveTUpoles = 0 
scatter_matrix3=0._dp 
If (IncludeGoldstoneExternal) scatter_matrix3(1,1) = a0_HpmcHpmc_HpmHpm(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(1,2) = a0_HpmcHpmc_HpmHpm(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix3(1,3) = a0_HpmcHpmc_HpmHpm(unitarity_s,1,1,2,2,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,1) = a0_HpmcHpmc_HpmHpm(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,2) = a0_HpmcHpmc_HpmHpm(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,3) = a0_HpmcHpmc_HpmHpm(unitarity_s,1,2,2,2,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix3(3,1) = a0_HpmcHpmc_HpmHpm(unitarity_s,2,2,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(3,2) = a0_HpmcHpmc_HpmHpm(unitarity_s,2,2,1,2,3,2) 
scatter_matrix3(3,3) = a0_HpmcHpmc_HpmHpm(unitarity_s,2,2,2,2,3,3) 


Select CASE (TUcutLevel)  
CASE (2) 
  scatter_matrix3B = scatter_matrix3
Do i=1,3 
  If (RemoveTUpoles(i).eq.1) Then
   scatter_matrix3(i,:) = 0._dp 
   scatter_matrix3(:,i) = 0._dp 
    If (AddR) scatter_matrix3(i,i) = -1111._dp ! to get a fixed order of the eigenvalues 
   scatter_matrix3B(:,i) = 0._dp 
  Else 
   scatter_matrix3B(i,:) = 0._dp 
  End If 
End Do 
CASE (1) 
If ((Abs(max_element_removed)/MaxVal(Abs(scatter_matrix3))).gt.cut_elements) Then 
 ! Write(*,*)  (Abs(max_element_removed)/MaxVal(Abs(scatter_matrix3)))  
End if 
End Select 
If (.not.pole_present) Then 
Call EigenSystem(scatter_matrix3,eigenvalues_matrix3,rot_matrix3,ierr,test)
 If ((TUcutLevel.eq.2).and.(AddR)) Then ! Calculate 'R' 
  scatter_matrix3B = MatMul(scatter_matrix3B,Conjg(Transpose(rot_matrix3))) 
   Do i=1,3 
    If (eigenvalues_matrix3 (i).lt.-1000._dp) Then
     eigenvalues_matrix3(i) = 0._dp 
    Else 
     eigenvalues_matrix3(i) = sqrt(eigenvalues_matrix3(i)**2+  sum(scatter_matrix3B(i,:)**2) )
    End If
   End Do 
 End If 
scattering_eigenvalue_trilinears=MaxVal(Abs(eigenvalues_matrix3)) 
Else 
  scattering_eigenvalue_trilinears = 0._dp 
End if 
If (scattering_eigenvalue_trilinears.gt.max_scattering_eigenvalue_trilinears) Then 
   max_scattering_eigenvalue_trilinears=scattering_eigenvalue_trilinears 
   unitarity_s_best=sqrt(unitarity_s)
End if 
 
End do 

If (max_scattering_eigenvalue_trilinears.gt.0.5_dp) TreeUnitarityTrilinear=0._dp 
 
! Write(*,*) (max_scattering_eigenvalue_trilinears) 
 


 Contains 

Complex(dp) Function a0_AhAh_AhAh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = MAh(i3)
m4 = MAh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhAhAh(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i2,iprop),cplAhAhAh(i3,i4,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i2,iprop),cplAhAhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhAh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhAh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhAh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhAh(i2,i4,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhAhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhAhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhAhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhAhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhAh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhAh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhAh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhAh(i2,i3,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_AhAh

Complex(dp) Function a0_AhAh_Ahhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhAhhh(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i2,iprop),cplAhAhhh(i3,iprop,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i2,iprop),cplAhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i2,iprop,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i2,iprop,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i2,iprop,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i2,iprop,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhAh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhAh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhAh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhAh(i2,i3,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhAhhh(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_Ahhh

Complex(dp) Function a0_AhAh_hhhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhhhhh(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i2,iprop),cplAhhhhh(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i2,iprop),cplhhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhAhhh(i2,iprop,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhAhhh(i2,iprop,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhAhhh(i2,iprop,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhAhhh(i2,iprop,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplAhhhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i2,iprop,i3))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i2,iprop,i3))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i2,iprop,i3)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i2,iprop,i3)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_hhhh

Complex(dp) Function a0_AhAh_HpmHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = MHpm(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhHpmcHpm(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i2,iprop),cplAhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i2,iprop),cplhhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplAhHpmcHpm(i2,iprop,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplAhHpmcHpm(i2,iprop,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplAhHpmcHpm(i2,iprop,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplAhHpmcHpm(i2,iprop,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_HpmHpmc

Complex(dp) Function a0_Ahhh_AhAh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = MAh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhAhhh(i1,i3,i4,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i2),cplAhAhAh(i3,i4,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i2,iprop),cplAhAhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i4,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i4,iprop,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i4,iprop,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhAhhh(i4,iprop,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i4,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i4,i2,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i4,i2,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplAhhhhh(i4,i2,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhhh(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhhh(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhhh(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i4,iprop),cplAhAhhh(i3,iprop,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_AhAh

Complex(dp) Function a0_Ahhh_Ahhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhhhhh(i1,i3,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i2),cplAhAhhh(i3,iprop,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i2,iprop),cplAhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhhhhh(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhhhhh(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhhhhh(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhhhhh(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhAhhh(i3,iprop,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_Ahhh

Complex(dp) Function a0_Ahhh_hhhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhhhhh(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i2),cplAhhhhh(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i2,iprop),cplhhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhhhhh(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhhhhh(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhhhhh(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhhhhh(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhhhhh(iprop,i2,i3))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhhhhh(iprop,i2,i3))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhhhhh(iprop,i2,i3)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i4),cplAhhhhh(iprop,i2,i3)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_hhhh

Complex(dp) Function a0_Ahhh_HpmHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = MHpm(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhHpmcHpm(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i2),cplAhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i2,iprop),cplhhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_HpmHpmc

Complex(dp) Function a0_AhHpm_AhHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MHpm(i2)
m3 = MAh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhHpmcHpm(i1,i3,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i2,iprop),cplAhHpmcHpm(i3,iprop,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHpm_AhHpmc

Complex(dp) Function a0_AhHpm_hhHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MHpm(i2)
m3 = Mhh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhHpmcHpm(i1,i3,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i2,iprop),cplhhHpmcHpm(i3,iprop,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHpm_hhHpmc

Complex(dp) Function a0_AhHpmc_AhHpm(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MHpm(i2)
m3 = MAh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhHpmcHpm(i1,i3,i4,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i2),cplAhHpmcHpm(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhAh(i1,i3,iprop),cplAhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhAhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHpmc_AhHpm

Complex(dp) Function a0_AhHpmc_hhHpm(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MAh(i1)
m2 = MHpm(i2)
m3 = Mhh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhHpmcHpm(i1,i3,i4,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,iprop,i2),cplhhHpmcHpm(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i1,iprop,i3),cplAhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHpmc_hhHpm

Complex(dp) Function a0_hhhh_AhAh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = MAh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhhhhh(i3,i4,i1,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i2),cplAhAhAh(i3,i4,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i2,iprop),cplAhAhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhAhhh(i4,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhAhhh(i4,iprop,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhAhhh(i4,iprop,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhAhhh(i4,iprop,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplAhhhhh(i4,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplAhhhhh(i4,i2,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplAhhhhh(i4,i2,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplAhhhhh(i4,i2,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i4,iprop,i1),cplAhAhhh(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i4,iprop,i1),cplAhAhhh(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i4,iprop,i1),cplAhAhhh(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i4,iprop,i1),cplAhAhhh(i3,iprop,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i4,i1,iprop),cplAhhhhh(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i4,i1,iprop),cplAhhhhh(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i4,i1,iprop),cplAhhhhh(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i4,i1,iprop),cplAhhhhh(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_AhAh

Complex(dp) Function a0_hhhh_Ahhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhhhhh(i3,i1,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i2),cplAhAhhh(i3,iprop,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i2,iprop),cplAhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhhhhh(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhhhhh(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhhhhh(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhhhhh(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhhhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhhhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhhhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhhhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhAhhh(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhAhhh(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhAhhh(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhAhhh(i3,iprop,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplAhhhhh(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_Ahhh

Complex(dp) Function a0_hhhh_hhhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplhhhhhhhh(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i2),cplAhhhhh(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i2,iprop),cplhhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhhhhh(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhhhhh(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhhhhh(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhhhhh(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhhhhh(i2,i4,iprop)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhhhhh(iprop,i2,i3))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhhhhh(iprop,i2,i3))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhhhhh(iprop,i2,i3)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i4),cplAhhhhh(iprop,i2,i3)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i4,iprop),cplhhhhhh(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_hhhh

Complex(dp) Function a0_hhhh_HpmHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = MHpm(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplhhhhHpmcHpm(i1,i2,i3,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i2),cplAhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i2,iprop),cplhhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i3,iprop),cplhhHpmcHpm(i2,iprop,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i2,i3,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_HpmHpmc

Complex(dp) Function a0_hhHpm_AhHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = MHpm(i2)
m3 = MAh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhHpmcHpm(i3,i1,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i2,iprop),cplAhHpmcHpm(i3,iprop,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplAhHpmcHpm(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHpm_AhHpmc

Complex(dp) Function a0_hhHpm_hhHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = MHpm(i2)
m3 = Mhh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplhhhhHpmcHpm(i1,i3,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i2,iprop),cplhhHpmcHpm(i3,iprop,i4)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i4),cplhhHpmcHpm(i3,i2,iprop)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHpm_hhHpmc

Complex(dp) Function a0_hhHpmc_AhHpm(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = MHpm(i2)
m3 = MAh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhHpmcHpm(i3,i1,i4,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i2),cplAhHpmcHpm(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhAhhh(i3,iprop,i1),cplAhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplAhhhhh(i3,i1,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHpmc_AhHpm

Complex(dp) Function a0_hhHpmc_hhHpm(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = Mhh(i1)
m2 = MHpm(i2)
m3 = Mhh(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplhhhhHpmcHpm(i1,i3,i4,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If (Abs(1-s/MHpm(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,iprop,i2),cplhhHpmcHpm(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhhhhh(iprop,i1,i3),cplAhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhhhhh(i1,i3,iprop),cplhhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i1,i4,iprop),cplhhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHpmc_hhHpm

Complex(dp) Function a0_HpmHpm_HpmcHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MHpm(i1)
m2 = MHpm(i2)
m3 = MHpm(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplHpmHpmcHpmcHpm(i1,i2,i3,i4)


! S-Channel 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i3),cplAhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i3),cplhhHpmcHpm(iprop,i2,i4))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i3),cplhhHpmcHpm(iprop,i2,i4))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i3),cplhhHpmcHpm(iprop,i2,i4)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i3),cplhhHpmcHpm(iprop,i2,i4)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i2,i3))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i2,i3))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i2,i3)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i2,i3)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i2,i3))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i2,i3))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i2,i3)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i2,i3)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HpmHpm_HpmcHpmc

Complex(dp) Function a0_HpmHpmc_AhAh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MHpm(i1)
m2 = MHpm(i2)
m3 = MAh(i3)
m4 = MAh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhAhHpmcHpm(i3,i4,i1,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i2),cplAhAhAh(i3,i4,iprop)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i2),cplAhAhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplAhHpmcHpm(i4,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplAhHpmcHpm(i4,iprop,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplAhHpmcHpm(i4,iprop,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplAhHpmcHpm(i4,iprop,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HpmHpmc_AhAh

Complex(dp) Function a0_HpmHpmc_Ahhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MHpm(i1)
m2 = MHpm(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplAhhhHpmcHpm(i3,i4,i1,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i2),cplAhAhhh(i3,iprop,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i2),cplAhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplAhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplAhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HpmHpmc_Ahhh

Complex(dp) Function a0_HpmHpmc_hhhh(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MHpm(i1)
m2 = MHpm(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplhhhhHpmcHpm(i3,i4,i1,i2)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i2),cplAhhhhh(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i2),cplhhhhhh(i3,i4,iprop)) 
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i3,i1,iprop),cplhhHpmcHpm(i4,iprop,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHpm(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplhhHpmcHpm(i3,iprop,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHpm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplhhHpmcHpm(i3,iprop,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplhhHpmcHpm(i3,iprop,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MHpm(iProp),s,cplhhHpmcHpm(i4,i1,iprop),cplhhHpmcHpm(i3,iprop,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HpmHpmc_hhhh

Complex(dp) Function a0_HpmHpmc_HpmHpmc(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MHpm(i1)
m2 = MHpm(i2)
m3 = MHpm(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplHpmHpmcHpmcHpm(i1,i3,i2,i4)


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If (Abs(1-s/MAh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i2),cplAhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If (Abs(1-s/Mhh(iProp)**2).lt.0.25_dp) Then 
 Pole_Present = .true. 
Else 
  amp = amp + Schannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i2),cplhhHpmcHpm(iprop,i3,i4)) 
End if 
End Do 


! T-Channel 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i3,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i3,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i3,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i1,i4),cplAhHpmcHpm(iprop,i3,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i3,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i3,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i3,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i1,i4),cplhhHpmcHpm(iprop,i3,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HpmHpmc_HpmHpmc

Complex(dp) Function a0_HpmcHpmc_HpmHpm(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: amp_poles 
m1 = MHpm(i1)
m2 = MHpm(i2)
m3 = MHpm(i3)
m4 = MHpm(i4)
amp = 0._dp 
amp_poles = 0._dp 
If ((s.gt.1.25_dp*(m3+m4)**2).and.(s.gt.1.25_dp*(m1+m2)**2)) Then 


! Quartic 
amp = amp -2._dp*cplHpmHpmcHpmcHpm(i3,i4,i1,i2)


! S-Channel 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i3,i1),cplAhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i3,i1),cplAhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i3,i1),cplAhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i3,i1),cplAhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i3,i1),cplhhHpmcHpm(iprop,i4,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i3,i1),cplhhHpmcHpm(iprop,i4,i2))) 
 Case (0) 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i3,i1),cplhhHpmcHpm(iprop,i4,i2)) 
End Select 
Else 
  amp = amp + Tchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i3,i1),cplhhHpmcHpm(iprop,i4,i2)) 
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i4,i1),cplAhHpmcHpm(iprop,i3,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i4,i1),cplAhHpmcHpm(iprop,i3,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i4,i1),cplAhHpmcHpm(iprop,i3,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,MAh(iProp),s,cplAhHpmcHpm(iprop,i4,i1),cplAhHpmcHpm(iprop,i3,i2)) 
End if 
End Do 
istart=1
Do iprop=istart,3
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i4,i1),cplhhHpmcHpm(iprop,i3,i2))).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles = amp_poles + Abs(Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i4,i1),cplhhHpmcHpm(iprop,i3,i2))) 
 Case (0) 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i4,i1),cplhhHpmcHpm(iprop,i3,i2)) 
End Select 
Else 
  amp = amp + Uchannel(m1,m2,m3,m4,Mhh(iProp),s,cplhhHpmcHpm(iprop,i4,i1),cplhhHpmcHpm(iprop,i3,i2)) 
End if 
End Do 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
End if 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If ((Abs(amp)).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HpmcHpmc_HpmHpm

End Subroutine ScatteringEigenvaluesWithTrilinears

Complex(dp) Function Kaehler(a,b,c) 
Implicit None 
Real(dp),Intent(in)::a,b,c
Kaehler = a**2-2._dp*a*(b+c)+(b-c)**2 
End Function Kaehler 
  
Real(dp) Function CheckTpole(m1,m2,m3,m4,mP) 
Implicit None 
Real(dp),Intent(in)::m1,m2,m3,m4,mP
Complex(dp):: res
res = (m2*m3 - m3*m4 + m2*mP + m3*mP + m4*mP - mP**2 + m1*(-m2 + m4 + mP) + Sqrt(m1**2 + (m3 - mP)**2 &
  &  - 2*m1*(m3 + mP))*Sqrt(m2**2 + (m4 - mP)**2 - 2*m2*(m4 + mP)))/(2.*mP)
If (Aimag(res).gt.1._dp) Then 
 CheckTpole = 0._dp 
Else 
 CheckTpole = Real(res,dp) 
End If 
End Function CheckTpole 
 
Real(dp) Function CheckUpole(m1,m2,m3,m4,mP) 
Implicit None 
Real(dp),Intent(in)::m1,m2,m3,m4,mP
Complex(dp) :: res
res =(m2*m4-m3*m4+m2*mP+m3*mP+m4*mP-mP**2+m1*(-m2+m3+mP)+Sqrt(m2**2+(m3-mP)**2 &
  &-2*m2*(m3+mP))*Sqrt(m1**2+(m4-mP)**2-2*m1*(m4+mP)))/(2.*mP)
If (Aimag(res).gt.1._dp) Then 
 CheckUpole = 0._dp 
Else 
 CheckUpole = Real(res,dp) 
End If 
End Function CheckUpole 
 
Complex(dp) Function Schannel(m1,m2,m3,m4,mP,s,c1,c2) 
Implicit None 
Real(dp),Intent(in)::m1,m2,m3,m4,mP,s
Complex(dp),Intent(in)::c1,c2
Schannel = 2._dp/(-mP**2+s) 
Schannel = c1*c2*Schannel 
End Function Schannel 
 
Complex(dp) Function Uchannel(m1r,m2r,m3r,m4r,mPr,s,c1,c2) 
Implicit None 
Real(dp),Intent(in)::m1r,m2r,m3r,m4r,mPr,s
Complex(dp),Intent(in)::c1,c2
Complex(dp)::m1,m2,m3,m4,mP 
m1=Cmplx(m1r,0._dp)
m2=Cmplx(m2r,0._dp)
m3=Cmplx(m3r,0._dp)
m4=Cmplx(m4r,0._dp)
mP=Cmplx(mPr,0._dp)
Uchannel = (2*s*Log(-(((m1 - m2)*(m1 + m2)*(m3 - m4)*(m3 + m4) + (m1**2 + m2**2 + m3**2 + m4**2 - 2*mP**2)*s & 
  & - s**2 + Sqrt((m1**4 + (m2**2 - s)**2 - 2*m1**2*(m2**2 + s))*(m3**4 + (m4**2 - s)**2 - 2*m3**2*(m4**2 + s))))/& 
  &((-m1 + m2)*(m1 + m2)*(m3 - m4)*(m3 + m4) - (m1**2 + m2**2 + m3**2 + m4**2 - 2*mP**2)*s + s**2 + & 
  & Sqrt((m1**4 + (m2**2 - s)**2 - 2*m1**2*(m2**2 + s))*(m3**4 + (m4**2 - s)**2 - 2*m3**2*(m4**2 + s)))))))/& 
 &Sqrt((m1**4 + (m2**2 - s)**2 - 2*m1**2*(m2**2 + s))*(m3**4 + (m4**2 - s)**2 - 2*m3**2*(m4**2 + s))) 
Uchannel = c1*c2*Uchannel 
End Function Uchannel 
  
Complex(dp) Function Tchannel(m1r,m2r,m3r,m4r,mPr,s,c1,c2) 
Implicit None 
Real(dp),Intent(in)::m1r,m2r,m3r,m4r,mPr,s
Complex(dp),Intent(in)::c1,c2
Complex(dp)::m1,m2,m3,m4,mP 
m1=Cmplx(m1r,0._dp)
m2=Cmplx(m2r,0._dp)
m3=Cmplx(m3r,0._dp)
m4=Cmplx(m4r,0._dp)
mP=Cmplx(mPr,0._dp)
Tchannel =(2*s*Log(((m1-m2)*(m1+m2)*(m3-m4)*(m3+m4)-(m1**2+m2**2+m3**2+m4**2-2*mP**2)*s+s**2& 
  & -Sqrt((m1**4+(m2**2-s)**2-2*m1**2*(m2**2+s))*(m3**4+(m4**2-s)**2-2*m3**2*(m4**2+s))))/& 
  & ((m1-m2)*(m1+m2)*(m3-m4)*(m3+m4)-(m1**2+m2**2+m3**2+m4**2-2*mP**2)*s+s**2+Sqrt((m1**4+(m2**2-s)**2& 
  & -2*m1**2*(m2**2+s))*(m3**4+(m4**2-s)**2-2*m3**2*(m4**2+s))))))/& 
  & Sqrt((m1**4+(m2**2-s)**2-2*m1**2*(m2**2+s))*(m3**4+(m4**2-s)**2-2*m3**2*(m4**2+s))) 
Tchannel = c1*c2*Tchannel 
End Function Tchannel 
  
End Module Unitarity_NMSSMEFT 
