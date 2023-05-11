! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:28 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Unitarity_gumTHDMII 
 
Use Control 
Use Settings 
Use LoopFunctions 
Use Mathematics 
Use Model_Data_gumTHDMII 
Use RGEs_gumTHDMII 
Use LoopMasses_gumTHDMII 
Use TreeLevelMasses_gumTHDMII 
Use Couplings_gumTHDMII 
Use Tadpoles_gumTHDMII 
 Use StandardModel 
 
Logical :: IncludeGoldstoneContributions=.true. 
Logical :: IncludeGoldstoneExternal=.true. 
Logical :: AddR=.true. 
Real(dp) :: cut_elements = 0.0001_dp 
Real(dp) :: cut_amplitudes = 0.01_dp 
Logical :: Ignore_poles=.false. 
 
Contains 

Subroutine ScatteringEigenvalues(vdinput,vuinput,g1input,g2input,g3input,             & 
& lam5input,lam1input,lam4input,lam3input,lam2input,Yuinput,Ydinput,Yeinput,             & 
& m122input,m112input,m222input,delta0,kont)

Implicit None 
Integer, Intent(inout) :: kont 
Integer :: ierr 
Real(dp) :: g1,g2,g3

Complex(dp) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Real(dp) :: vd,vu

Real(dp) :: gD(75) 
Real(dp) :: tz,dt,q,q2,mudim 
Real(dp), Intent(in) :: delta0 
Integer :: iter 
Complex(dp) :: scatter_matrix(36,36) 
Complex(dp) :: rot_matrix(36,36) 
Real(dp) :: eigenvalues_matrix(36), test(2), unitarity_s, scattering_eigenvalue, step_size
Real(dp),Intent(in) :: g1input,g2input,g3input,vdinput,vuinput

Complex(dp),Intent(in) :: lam5input,lam1input,lam4input,lam3input,lam2input,Yuinput(3,3),Ydinput(3,3),          & 
& Yeinput(3,3),m122input,m112input,m222input

max_scattering_eigenvalue = 0._dp 

g1 = g1input 
g2 = g2input 
g3 = g3input 
lam5 = lam5input 
lam1 = lam1input 
lam4 = lam4input 
lam3 = lam3input 
lam2 = lam2input 
Yu = Yuinput 
Yd = Ydinput 
Ye = Yeinput 
m122 = m122input 
m112 = m112input 
m222 = m222input 
vd = vdinput 
vu = vuinput 
scatter_matrix=0._dp 
scatter_matrix(1,27) =-1._dp*(lam1)
scatter_matrix(1,34) =-1._dp*(lam5)
scatter_matrix(2,28) =-1._dp*(lam1)
scatter_matrix(2,35) =-1._dp*(lam5)
scatter_matrix(3,29) =-1._dp*(lam3) - lam4
scatter_matrix(4,30) =-1._dp*(lam3)
scatter_matrix(4,32) =-1._dp*(lam4)
scatter_matrix(5,5) =-2._dp*(lam1)
scatter_matrix(5,13) =-1._dp*(lam1)
scatter_matrix(5,20) =-1._dp*(lam3) - lam4
scatter_matrix(5,26) =-1._dp*(lam3)
scatter_matrix(6,12) =-1._dp*(lam1)
scatter_matrix(6,25) =-1._dp*(lam4)
scatter_matrix(7,7) =-2._dp*(lam5)
scatter_matrix(7,15) =-1._dp*(lam5)
scatter_matrix(7,18) =-1._dp*(lam3) - lam4
scatter_matrix(7,24) =-1._dp*(lam4)
scatter_matrix(8,14) =-1._dp*(lam5)
scatter_matrix(8,23) =-1._dp*(lam3)
scatter_matrix(9,31) =-1._dp*(lam1)
scatter_matrix(9,36) =-1._dp*(lam5)
scatter_matrix(10,30) =-1._dp*(lam4)
scatter_matrix(10,32) =-1._dp*(lam3)
scatter_matrix(11,33) =-1._dp*(lam3) - lam4
scatter_matrix(12,6) =-1._dp*(lam1)
scatter_matrix(12,21) =-1._dp*(lam4)
scatter_matrix(13,5) =-1._dp*(lam1)
scatter_matrix(13,13) =-2._dp*(lam1)
scatter_matrix(13,20) =-1._dp*(lam3)
scatter_matrix(13,26) =-1._dp*(lam3) - lam4
scatter_matrix(14,8) =-1._dp*(lam5)
scatter_matrix(14,19) =-1._dp*(lam3)
scatter_matrix(15,7) =-1._dp*(lam5)
scatter_matrix(15,15) =-2._dp*(lam5)
scatter_matrix(15,18) =-1._dp*(lam4)
scatter_matrix(15,24) =-1._dp*(lam3) - lam4
scatter_matrix(16,27) =-Conjg(lam5)
scatter_matrix(16,34) =-1._dp*(lam2)
scatter_matrix(17,28) =-Conjg(lam5)
scatter_matrix(17,35) =-1._dp*(lam2)
scatter_matrix(18,7) =-1._dp*(lam3) - lam4
scatter_matrix(18,15) =-1._dp*(lam4)
scatter_matrix(18,18) =-2*Conjg(lam5)
scatter_matrix(18,24) =-Conjg(lam5)
scatter_matrix(19,14) =-1._dp*(lam3)
scatter_matrix(19,23) =-Conjg(lam5)
scatter_matrix(20,5) =-1._dp*(lam3) - lam4
scatter_matrix(20,13) =-1._dp*(lam3)
scatter_matrix(20,20) =-2._dp*(lam2)
scatter_matrix(20,26) =-1._dp*(lam2)
scatter_matrix(21,12) =-1._dp*(lam4)
scatter_matrix(21,25) =-1._dp*(lam2)
scatter_matrix(22,31) =-Conjg(lam5)
scatter_matrix(22,36) =-1._dp*(lam2)
scatter_matrix(23,8) =-1._dp*(lam3)
scatter_matrix(23,19) =-Conjg(lam5)
scatter_matrix(24,7) =-1._dp*(lam4)
scatter_matrix(24,15) =-1._dp*(lam3) - lam4
scatter_matrix(24,18) =-Conjg(lam5)
scatter_matrix(24,24) =-2*Conjg(lam5)
scatter_matrix(25,6) =-1._dp*(lam4)
scatter_matrix(25,21) =-1._dp*(lam2)
scatter_matrix(26,5) =-1._dp*(lam3)
scatter_matrix(26,13) =-1._dp*(lam3) - lam4
scatter_matrix(26,20) =-1._dp*(lam2)
scatter_matrix(26,26) =-2._dp*(lam2)
scatter_matrix(27,1) =-1._dp*(lam1)
scatter_matrix(27,16) =-Conjg(lam5)
scatter_matrix(28,2) =-1._dp*(lam1)
scatter_matrix(28,17) =-Conjg(lam5)
scatter_matrix(29,3) =-1._dp*(lam3) - lam4
scatter_matrix(30,4) =-1._dp*(lam3)
scatter_matrix(30,10) =-1._dp*(lam4)
scatter_matrix(31,9) =-1._dp*(lam1)
scatter_matrix(31,22) =-Conjg(lam5)
scatter_matrix(32,4) =-1._dp*(lam4)
scatter_matrix(32,10) =-1._dp*(lam3)
scatter_matrix(33,11) =-1._dp*(lam3) - lam4
scatter_matrix(34,1) =-1._dp*(lam5)
scatter_matrix(34,16) =-1._dp*(lam2)
scatter_matrix(35,2) =-1._dp*(lam5)
scatter_matrix(35,17) =-1._dp*(lam2)
scatter_matrix(36,9) =-1._dp*(lam5)
scatter_matrix(36,22) =-1._dp*(lam2)
Call EigenSystem( oo16pi*scatter_matrix,eigenvalues_matrix,rot_matrix,ierr,test) 

scattering_eigenvalue=MaxVal(Abs(eigenvalues_matrix)) 
max_scattering_eigenvalue=scattering_eigenvalue 
If (max_scattering_eigenvalue.gt.0.5_dp) TreeUnitarity=0._dp 
End Subroutine ScatteringEigenvalues

Subroutine ScatteringEigenvaluesWithTrilinears(MAhinput,MAh2input,MFdinput,           & 
& MFd2input,MFeinput,MFe2input,MFuinput,MFu2input,Mhhinput,Mhh2input,MHminput,           & 
& MHm2input,MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,ZDRinput,ZERinput,           & 
& ZURinput,vinput,ZDLinput,ZELinput,ZULinput,ZAinput,ZHinput,ZPinput,ZWinput,            & 
& ZZinput,alphaHinput,betaHinput,vdinput,vuinput,g1input,g2input,g3input,lam5input,      & 
& lam1input,lam4input,lam3input,lam2input,Yuinput,Ydinput,Yeinput,m122input,             & 
& m112input,m222input,delta0,kont)

Implicit None 
Integer, Intent(inout) :: kont 
Integer :: ierr 
Logical :: Pole_Present, SPole_Present, TPole_Present, UPole_Present 
Integer :: RemoveTUpoles(99) 
Real(dp) :: g1,g2,g3

Complex(dp) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Real(dp) :: vd,vu

Complex(dp) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhhhhh(2,2,2),cplAhHmcHm(2,2,2),cplhhhhhh(2,2,2),& 
& cplhhHmcHm(2,2,2),cplAhAhAhAh(2,2,2,2),cplAhAhAhhh(2,2,2,2),cplAhAhhhhh(2,2,2,2),      & 
& cplAhAhHmcHm(2,2,2,2),cplAhhhhhhh(2,2,2,2),cplAhhhHmcHm(2,2,2,2),cplhhhhhhhh(2,2,2,2), & 
& cplhhhhHmcHm(2,2,2,2),cplHmHmcHmcHm(2,2,2,2)

Real(dp) :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),               & 
& alphaH,betaH

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Real(dp),Intent(in) :: g1input,g2input,g3input,vdinput,vuinput

Complex(dp),Intent(in) :: lam5input,lam1input,lam4input,lam3input,lam2input,Yuinput(3,3),Ydinput(3,3),          & 
& Yeinput(3,3),m122input,m112input,m222input

Real(dp),Intent(in) :: MAhinput(2),MAh2input(2),MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),           & 
& MFuinput(3),MFu2input(3),Mhhinput(2),Mhh2input(2),MHminput(2),MHm2input(2),            & 
& MVWminput,MVWm2input,MVZinput,MVZ2input,TWinput,vinput,ZAinput(2,2),ZHinput(2,2),      & 
& ZPinput(2,2),ZZinput(2,2),alphaHinput,betaHinput

Complex(dp),Intent(in) :: ZDRinput(3,3),ZERinput(3,3),ZURinput(3,3),ZDLinput(3,3),ZELinput(3,3),ZULinput(3,3),  & 
& ZWinput(2,2)

Complex(dp) :: scatter_matrix1(14,14) 
Complex(dp) :: scatter_matrix1B(14,14) 
Complex(dp) :: rot_matrix1(14,14) 
Real(dp) :: eigenvalues_matrix1(14)
Complex(dp) :: scatter_matrix2(8,8) 
Complex(dp) :: scatter_matrix2B(8,8) 
Complex(dp) :: rot_matrix2(8,8) 
Real(dp) :: eigenvalues_matrix2(8)
Complex(dp) :: scatter_matrix3(3,3) 
Complex(dp) :: scatter_matrix3B(3,3) 
Complex(dp) :: rot_matrix3(3,3) 
Real(dp) :: eigenvalues_matrix3(3)
Real(dp) :: step_size,scattering_eigenvalue_trilinears, unitarity_s, test(2) 
Real(dp) :: gD(75) 
Real(dp) :: tz,dt,q,q2,mudim, max_element_removed  
Real(dp), Intent(in) :: delta0 
Integer :: iter, i, il,ir, count 
g1 = g1input 
g2 = g2input 
g3 = g3input 
lam5 = lam5input 
lam1 = lam1input 
lam4 = lam4input 
lam3 = lam3input 
lam2 = lam2input 
Yu = Yuinput 
Yd = Ydinput 
Ye = Yeinput 
m122 = m122input 
m112 = m112input 
m222 = m222input 
vd = vdinput 
vu = vuinput 
Call TreeMasses(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,           & 
& MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,betaH,               & 
& vd,vu,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,.True.,kont)

Call CouplingsColourStructures(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,               & 
& cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,cplhhhhhh,cplhhHmcHm,cplAhAhAhAh,             & 
& cplAhAhAhhh,cplAhAhhhhh,cplAhAhHmcHm,cplAhhhhhhh,cplAhhhHmcHm,cplhhhhhhhh,             & 
& cplhhhhHmcHm,cplHmHmcHmcHm)

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
!! 1. sub-matrix  
Pole_Present = .false. 
max_element_removed = 0._dp 
RemoveTUpoles = 0 
scatter_matrix1=0._dp 
If (IncludeGoldstoneExternal) scatter_matrix1(1,1) = a0_AhAh_AhAh_00(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,2) = a0_AhAh_AhAh_00(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,3) = a0_AhAh_AhAh_00(unitarity_s,1,1,2,2,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,4) = a0_AhAh_Ahhh_00(unitarity_s,1,1,1,1,1,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,5) = a0_AhAh_Ahhh_00(unitarity_s,1,1,1,2,1,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,6) = a0_AhAh_Ahhh_00(unitarity_s,1,1,2,1,1,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,7) = a0_AhAh_Ahhh_00(unitarity_s,1,1,2,2,1,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,8) = a0_AhAh_hhhh_00(unitarity_s,1,1,1,1,1,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,9) = a0_AhAh_hhhh_00(unitarity_s,1,1,1,2,1,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,10) = a0_AhAh_hhhh_00(unitarity_s,1,1,2,2,1,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,11) = a0_AhAh_HmHmc_00(unitarity_s,1,1,1,1,1,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,12) = a0_AhAh_HmHmc_00(unitarity_s,1,1,1,2,1,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,13) = a0_AhAh_HmHmc_00(unitarity_s,1,1,2,1,1,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(1,14) = a0_AhAh_HmHmc_00(unitarity_s,1,1,2,2,1,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,1) = a0_AhAh_AhAh_00(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,2) = a0_AhAh_AhAh_00(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,3) = a0_AhAh_AhAh_00(unitarity_s,1,2,2,2,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,4) = a0_AhAh_Ahhh_00(unitarity_s,1,2,1,1,2,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,5) = a0_AhAh_Ahhh_00(unitarity_s,1,2,1,2,2,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,6) = a0_AhAh_Ahhh_00(unitarity_s,1,2,2,1,2,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,7) = a0_AhAh_Ahhh_00(unitarity_s,1,2,2,2,2,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,8) = a0_AhAh_hhhh_00(unitarity_s,1,2,1,1,2,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,9) = a0_AhAh_hhhh_00(unitarity_s,1,2,1,2,2,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,10) = a0_AhAh_hhhh_00(unitarity_s,1,2,2,2,2,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,11) = a0_AhAh_HmHmc_00(unitarity_s,1,2,1,1,2,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,12) = a0_AhAh_HmHmc_00(unitarity_s,1,2,1,2,2,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,13) = a0_AhAh_HmHmc_00(unitarity_s,1,2,2,1,2,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,14) = a0_AhAh_HmHmc_00(unitarity_s,1,2,2,2,2,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,1) = a0_AhAh_AhAh_00(unitarity_s,2,2,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,2) = a0_AhAh_AhAh_00(unitarity_s,2,2,1,2,3,2) 
scatter_matrix1(3,3) = a0_AhAh_AhAh_00(unitarity_s,2,2,2,2,3,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,4) = a0_AhAh_Ahhh_00(unitarity_s,2,2,1,1,3,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,5) = a0_AhAh_Ahhh_00(unitarity_s,2,2,1,2,3,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,6) = a0_AhAh_Ahhh_00(unitarity_s,2,2,2,1,3,6) 
scatter_matrix1(3,7) = a0_AhAh_Ahhh_00(unitarity_s,2,2,2,2,3,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,8) = a0_AhAh_hhhh_00(unitarity_s,2,2,1,1,3,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,9) = a0_AhAh_hhhh_00(unitarity_s,2,2,1,2,3,9) 
scatter_matrix1(3,10) = a0_AhAh_hhhh_00(unitarity_s,2,2,2,2,3,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,11) = a0_AhAh_HmHmc_00(unitarity_s,2,2,1,1,3,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,12) = a0_AhAh_HmHmc_00(unitarity_s,2,2,1,2,3,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(3,13) = a0_AhAh_HmHmc_00(unitarity_s,2,2,2,1,3,13) 
scatter_matrix1(3,14) = a0_AhAh_HmHmc_00(unitarity_s,2,2,2,2,3,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,1) = a0_Ahhh_AhAh_00(unitarity_s,1,1,1,1,4,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,2) = a0_Ahhh_AhAh_00(unitarity_s,1,1,1,2,4,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,3) = a0_Ahhh_AhAh_00(unitarity_s,1,1,2,2,4,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,4) = a0_Ahhh_Ahhh_00(unitarity_s,1,1,1,1,4,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,5) = a0_Ahhh_Ahhh_00(unitarity_s,1,1,1,2,4,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,6) = a0_Ahhh_Ahhh_00(unitarity_s,1,1,2,1,4,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,7) = a0_Ahhh_Ahhh_00(unitarity_s,1,1,2,2,4,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,8) = a0_Ahhh_hhhh_00(unitarity_s,1,1,1,1,4,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,9) = a0_Ahhh_hhhh_00(unitarity_s,1,1,1,2,4,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,10) = a0_Ahhh_hhhh_00(unitarity_s,1,1,2,2,4,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,11) = a0_Ahhh_HmHmc_00(unitarity_s,1,1,1,1,4,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,12) = a0_Ahhh_HmHmc_00(unitarity_s,1,1,1,2,4,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,13) = a0_Ahhh_HmHmc_00(unitarity_s,1,1,2,1,4,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(4,14) = a0_Ahhh_HmHmc_00(unitarity_s,1,1,2,2,4,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,1) = a0_Ahhh_AhAh_00(unitarity_s,1,2,1,1,5,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,2) = a0_Ahhh_AhAh_00(unitarity_s,1,2,1,2,5,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,3) = a0_Ahhh_AhAh_00(unitarity_s,1,2,2,2,5,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,4) = a0_Ahhh_Ahhh_00(unitarity_s,1,2,1,1,5,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,5) = a0_Ahhh_Ahhh_00(unitarity_s,1,2,1,2,5,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,6) = a0_Ahhh_Ahhh_00(unitarity_s,1,2,2,1,5,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,7) = a0_Ahhh_Ahhh_00(unitarity_s,1,2,2,2,5,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,8) = a0_Ahhh_hhhh_00(unitarity_s,1,2,1,1,5,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,9) = a0_Ahhh_hhhh_00(unitarity_s,1,2,1,2,5,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,10) = a0_Ahhh_hhhh_00(unitarity_s,1,2,2,2,5,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,11) = a0_Ahhh_HmHmc_00(unitarity_s,1,2,1,1,5,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,12) = a0_Ahhh_HmHmc_00(unitarity_s,1,2,1,2,5,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,13) = a0_Ahhh_HmHmc_00(unitarity_s,1,2,2,1,5,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,14) = a0_Ahhh_HmHmc_00(unitarity_s,1,2,2,2,5,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,1) = a0_Ahhh_AhAh_00(unitarity_s,2,1,1,1,6,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,2) = a0_Ahhh_AhAh_00(unitarity_s,2,1,1,2,6,2) 
scatter_matrix1(6,3) = a0_Ahhh_AhAh_00(unitarity_s,2,1,2,2,6,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,4) = a0_Ahhh_Ahhh_00(unitarity_s,2,1,1,1,6,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,5) = a0_Ahhh_Ahhh_00(unitarity_s,2,1,1,2,6,5) 
scatter_matrix1(6,6) = a0_Ahhh_Ahhh_00(unitarity_s,2,1,2,1,6,6) 
scatter_matrix1(6,7) = a0_Ahhh_Ahhh_00(unitarity_s,2,1,2,2,6,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,8) = a0_Ahhh_hhhh_00(unitarity_s,2,1,1,1,6,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,9) = a0_Ahhh_hhhh_00(unitarity_s,2,1,1,2,6,9) 
scatter_matrix1(6,10) = a0_Ahhh_hhhh_00(unitarity_s,2,1,2,2,6,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,11) = a0_Ahhh_HmHmc_00(unitarity_s,2,1,1,1,6,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,12) = a0_Ahhh_HmHmc_00(unitarity_s,2,1,1,2,6,12) 
scatter_matrix1(6,13) = a0_Ahhh_HmHmc_00(unitarity_s,2,1,2,1,6,13) 
scatter_matrix1(6,14) = a0_Ahhh_HmHmc_00(unitarity_s,2,1,2,2,6,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,1) = a0_Ahhh_AhAh_00(unitarity_s,2,2,1,1,7,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,2) = a0_Ahhh_AhAh_00(unitarity_s,2,2,1,2,7,2) 
scatter_matrix1(7,3) = a0_Ahhh_AhAh_00(unitarity_s,2,2,2,2,7,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,4) = a0_Ahhh_Ahhh_00(unitarity_s,2,2,1,1,7,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,5) = a0_Ahhh_Ahhh_00(unitarity_s,2,2,1,2,7,5) 
scatter_matrix1(7,6) = a0_Ahhh_Ahhh_00(unitarity_s,2,2,2,1,7,6) 
scatter_matrix1(7,7) = a0_Ahhh_Ahhh_00(unitarity_s,2,2,2,2,7,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,8) = a0_Ahhh_hhhh_00(unitarity_s,2,2,1,1,7,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,9) = a0_Ahhh_hhhh_00(unitarity_s,2,2,1,2,7,9) 
scatter_matrix1(7,10) = a0_Ahhh_hhhh_00(unitarity_s,2,2,2,2,7,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,11) = a0_Ahhh_HmHmc_00(unitarity_s,2,2,1,1,7,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,12) = a0_Ahhh_HmHmc_00(unitarity_s,2,2,1,2,7,12) 
scatter_matrix1(7,13) = a0_Ahhh_HmHmc_00(unitarity_s,2,2,2,1,7,13) 
scatter_matrix1(7,14) = a0_Ahhh_HmHmc_00(unitarity_s,2,2,2,2,7,14) 
scatter_matrix1(8,1) = a0_hhhh_AhAh_00(unitarity_s,1,1,1,1,8,1) 
scatter_matrix1(8,2) = a0_hhhh_AhAh_00(unitarity_s,1,1,1,2,8,2) 
scatter_matrix1(8,3) = a0_hhhh_AhAh_00(unitarity_s,1,1,2,2,8,3) 
scatter_matrix1(8,4) = a0_hhhh_Ahhh_00(unitarity_s,1,1,1,1,8,4) 
scatter_matrix1(8,5) = a0_hhhh_Ahhh_00(unitarity_s,1,1,1,2,8,5) 
scatter_matrix1(8,6) = a0_hhhh_Ahhh_00(unitarity_s,1,1,2,1,8,6) 
scatter_matrix1(8,7) = a0_hhhh_Ahhh_00(unitarity_s,1,1,2,2,8,7) 
scatter_matrix1(8,8) = a0_hhhh_hhhh_00(unitarity_s,1,1,1,1,8,8) 
scatter_matrix1(8,9) = a0_hhhh_hhhh_00(unitarity_s,1,1,1,2,8,9) 
scatter_matrix1(8,10) = a0_hhhh_hhhh_00(unitarity_s,1,1,2,2,8,10) 
scatter_matrix1(8,11) = a0_hhhh_HmHmc_00(unitarity_s,1,1,1,1,8,11) 
scatter_matrix1(8,12) = a0_hhhh_HmHmc_00(unitarity_s,1,1,1,2,8,12) 
scatter_matrix1(8,13) = a0_hhhh_HmHmc_00(unitarity_s,1,1,2,1,8,13) 
scatter_matrix1(8,14) = a0_hhhh_HmHmc_00(unitarity_s,1,1,2,2,8,14) 
scatter_matrix1(9,1) = a0_hhhh_AhAh_00(unitarity_s,1,2,1,1,9,1) 
scatter_matrix1(9,2) = a0_hhhh_AhAh_00(unitarity_s,1,2,1,2,9,2) 
scatter_matrix1(9,3) = a0_hhhh_AhAh_00(unitarity_s,1,2,2,2,9,3) 
scatter_matrix1(9,4) = a0_hhhh_Ahhh_00(unitarity_s,1,2,1,1,9,4) 
scatter_matrix1(9,5) = a0_hhhh_Ahhh_00(unitarity_s,1,2,1,2,9,5) 
scatter_matrix1(9,6) = a0_hhhh_Ahhh_00(unitarity_s,1,2,2,1,9,6) 
scatter_matrix1(9,7) = a0_hhhh_Ahhh_00(unitarity_s,1,2,2,2,9,7) 
scatter_matrix1(9,8) = a0_hhhh_hhhh_00(unitarity_s,1,2,1,1,9,8) 
scatter_matrix1(9,9) = a0_hhhh_hhhh_00(unitarity_s,1,2,1,2,9,9) 
scatter_matrix1(9,10) = a0_hhhh_hhhh_00(unitarity_s,1,2,2,2,9,10) 
scatter_matrix1(9,11) = a0_hhhh_HmHmc_00(unitarity_s,1,2,1,1,9,11) 
scatter_matrix1(9,12) = a0_hhhh_HmHmc_00(unitarity_s,1,2,1,2,9,12) 
scatter_matrix1(9,13) = a0_hhhh_HmHmc_00(unitarity_s,1,2,2,1,9,13) 
scatter_matrix1(9,14) = a0_hhhh_HmHmc_00(unitarity_s,1,2,2,2,9,14) 
scatter_matrix1(10,1) = a0_hhhh_AhAh_00(unitarity_s,2,2,1,1,10,1) 
scatter_matrix1(10,2) = a0_hhhh_AhAh_00(unitarity_s,2,2,1,2,10,2) 
scatter_matrix1(10,3) = a0_hhhh_AhAh_00(unitarity_s,2,2,2,2,10,3) 
scatter_matrix1(10,4) = a0_hhhh_Ahhh_00(unitarity_s,2,2,1,1,10,4) 
scatter_matrix1(10,5) = a0_hhhh_Ahhh_00(unitarity_s,2,2,1,2,10,5) 
scatter_matrix1(10,6) = a0_hhhh_Ahhh_00(unitarity_s,2,2,2,1,10,6) 
scatter_matrix1(10,7) = a0_hhhh_Ahhh_00(unitarity_s,2,2,2,2,10,7) 
scatter_matrix1(10,8) = a0_hhhh_hhhh_00(unitarity_s,2,2,1,1,10,8) 
scatter_matrix1(10,9) = a0_hhhh_hhhh_00(unitarity_s,2,2,1,2,10,9) 
scatter_matrix1(10,10) = a0_hhhh_hhhh_00(unitarity_s,2,2,2,2,10,10) 
scatter_matrix1(10,11) = a0_hhhh_HmHmc_00(unitarity_s,2,2,1,1,10,11) 
scatter_matrix1(10,12) = a0_hhhh_HmHmc_00(unitarity_s,2,2,1,2,10,12) 
scatter_matrix1(10,13) = a0_hhhh_HmHmc_00(unitarity_s,2,2,2,1,10,13) 
scatter_matrix1(10,14) = a0_hhhh_HmHmc_00(unitarity_s,2,2,2,2,10,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,1) = a0_HmHmc_AhAh_00(unitarity_s,1,1,1,1,11,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,2) = a0_HmHmc_AhAh_00(unitarity_s,1,1,1,2,11,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,3) = a0_HmHmc_AhAh_00(unitarity_s,1,1,2,2,11,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,4) = a0_HmHmc_Ahhh_00(unitarity_s,1,1,1,1,11,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,5) = a0_HmHmc_Ahhh_00(unitarity_s,1,1,1,2,11,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,6) = a0_HmHmc_Ahhh_00(unitarity_s,1,1,2,1,11,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,7) = a0_HmHmc_Ahhh_00(unitarity_s,1,1,2,2,11,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,8) = a0_HmHmc_hhhh_00(unitarity_s,1,1,1,1,11,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,9) = a0_HmHmc_hhhh_00(unitarity_s,1,1,1,2,11,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,10) = a0_HmHmc_hhhh_00(unitarity_s,1,1,2,2,11,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,11) = a0_HmHmc_HmHmc_00(unitarity_s,1,1,1,1,11,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,12) = a0_HmHmc_HmHmc_00(unitarity_s,1,1,1,2,11,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,13) = a0_HmHmc_HmHmc_00(unitarity_s,1,1,2,1,11,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,14) = a0_HmHmc_HmHmc_00(unitarity_s,1,1,2,2,11,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,1) = a0_HmHmc_AhAh_00(unitarity_s,1,2,1,1,12,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,2) = a0_HmHmc_AhAh_00(unitarity_s,1,2,1,2,12,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,3) = a0_HmHmc_AhAh_00(unitarity_s,1,2,2,2,12,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,4) = a0_HmHmc_Ahhh_00(unitarity_s,1,2,1,1,12,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,5) = a0_HmHmc_Ahhh_00(unitarity_s,1,2,1,2,12,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,6) = a0_HmHmc_Ahhh_00(unitarity_s,1,2,2,1,12,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,7) = a0_HmHmc_Ahhh_00(unitarity_s,1,2,2,2,12,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,8) = a0_HmHmc_hhhh_00(unitarity_s,1,2,1,1,12,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,9) = a0_HmHmc_hhhh_00(unitarity_s,1,2,1,2,12,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,10) = a0_HmHmc_hhhh_00(unitarity_s,1,2,2,2,12,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,11) = a0_HmHmc_HmHmc_00(unitarity_s,1,2,1,1,12,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,12) = a0_HmHmc_HmHmc_00(unitarity_s,1,2,1,2,12,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,13) = a0_HmHmc_HmHmc_00(unitarity_s,1,2,2,1,12,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,14) = a0_HmHmc_HmHmc_00(unitarity_s,1,2,2,2,12,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,1) = a0_HmHmc_AhAh_00(unitarity_s,2,1,1,1,13,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,2) = a0_HmHmc_AhAh_00(unitarity_s,2,1,1,2,13,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,3) = a0_HmHmc_AhAh_00(unitarity_s,2,1,2,2,13,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,4) = a0_HmHmc_Ahhh_00(unitarity_s,2,1,1,1,13,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,5) = a0_HmHmc_Ahhh_00(unitarity_s,2,1,1,2,13,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,6) = a0_HmHmc_Ahhh_00(unitarity_s,2,1,2,1,13,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,7) = a0_HmHmc_Ahhh_00(unitarity_s,2,1,2,2,13,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,8) = a0_HmHmc_hhhh_00(unitarity_s,2,1,1,1,13,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,9) = a0_HmHmc_hhhh_00(unitarity_s,2,1,1,2,13,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,10) = a0_HmHmc_hhhh_00(unitarity_s,2,1,2,2,13,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,11) = a0_HmHmc_HmHmc_00(unitarity_s,2,1,1,1,13,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,12) = a0_HmHmc_HmHmc_00(unitarity_s,2,1,1,2,13,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,13) = a0_HmHmc_HmHmc_00(unitarity_s,2,1,2,1,13,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,14) = a0_HmHmc_HmHmc_00(unitarity_s,2,1,2,2,13,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,1) = a0_HmHmc_AhAh_00(unitarity_s,2,2,1,1,14,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,2) = a0_HmHmc_AhAh_00(unitarity_s,2,2,1,2,14,2) 
scatter_matrix1(14,3) = a0_HmHmc_AhAh_00(unitarity_s,2,2,2,2,14,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,4) = a0_HmHmc_Ahhh_00(unitarity_s,2,2,1,1,14,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,5) = a0_HmHmc_Ahhh_00(unitarity_s,2,2,1,2,14,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,6) = a0_HmHmc_Ahhh_00(unitarity_s,2,2,2,1,14,6) 
scatter_matrix1(14,7) = a0_HmHmc_Ahhh_00(unitarity_s,2,2,2,2,14,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,8) = a0_HmHmc_hhhh_00(unitarity_s,2,2,1,1,14,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,9) = a0_HmHmc_hhhh_00(unitarity_s,2,2,1,2,14,9) 
scatter_matrix1(14,10) = a0_HmHmc_hhhh_00(unitarity_s,2,2,2,2,14,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,11) = a0_HmHmc_HmHmc_00(unitarity_s,2,2,1,1,14,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,12) = a0_HmHmc_HmHmc_00(unitarity_s,2,2,1,2,14,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,13) = a0_HmHmc_HmHmc_00(unitarity_s,2,2,2,1,14,13) 
scatter_matrix1(14,14) = a0_HmHmc_HmHmc_00(unitarity_s,2,2,2,2,14,14) 


Select CASE (TUcutLevel)  
CASE (2) 
  scatter_matrix1B = scatter_matrix1
Do i=1,14 
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
   Do i=1,14 
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
If (IncludeGoldstoneExternal) scatter_matrix2(1,1) = a0_AhHmc_AhHm_00(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,2) = a0_AhHmc_AhHm_00(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,3) = a0_AhHmc_AhHm_00(unitarity_s,1,1,2,1,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,4) = a0_AhHmc_AhHm_00(unitarity_s,1,1,2,2,1,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,5) = a0_AhHmc_hhHm_00(unitarity_s,1,1,1,1,1,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,6) = a0_AhHmc_hhHm_00(unitarity_s,1,1,1,2,1,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,7) = a0_AhHmc_hhHm_00(unitarity_s,1,1,2,1,1,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,8) = a0_AhHmc_hhHm_00(unitarity_s,1,1,2,2,1,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,1) = a0_AhHmc_AhHm_00(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,2) = a0_AhHmc_AhHm_00(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,3) = a0_AhHmc_AhHm_00(unitarity_s,1,2,2,1,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,4) = a0_AhHmc_AhHm_00(unitarity_s,1,2,2,2,2,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,5) = a0_AhHmc_hhHm_00(unitarity_s,1,2,1,1,2,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,6) = a0_AhHmc_hhHm_00(unitarity_s,1,2,1,2,2,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,7) = a0_AhHmc_hhHm_00(unitarity_s,1,2,2,1,2,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,8) = a0_AhHmc_hhHm_00(unitarity_s,1,2,2,2,2,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,1) = a0_AhHmc_AhHm_00(unitarity_s,2,1,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,2) = a0_AhHmc_AhHm_00(unitarity_s,2,1,1,2,3,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,3) = a0_AhHmc_AhHm_00(unitarity_s,2,1,2,1,3,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,4) = a0_AhHmc_AhHm_00(unitarity_s,2,1,2,2,3,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,5) = a0_AhHmc_hhHm_00(unitarity_s,2,1,1,1,3,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,6) = a0_AhHmc_hhHm_00(unitarity_s,2,1,1,2,3,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,7) = a0_AhHmc_hhHm_00(unitarity_s,2,1,2,1,3,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,8) = a0_AhHmc_hhHm_00(unitarity_s,2,1,2,2,3,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,1) = a0_AhHmc_AhHm_00(unitarity_s,2,2,1,1,4,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,2) = a0_AhHmc_AhHm_00(unitarity_s,2,2,1,2,4,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,3) = a0_AhHmc_AhHm_00(unitarity_s,2,2,2,1,4,3) 
scatter_matrix2(4,4) = a0_AhHmc_AhHm_00(unitarity_s,2,2,2,2,4,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,5) = a0_AhHmc_hhHm_00(unitarity_s,2,2,1,1,4,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,6) = a0_AhHmc_hhHm_00(unitarity_s,2,2,1,2,4,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,7) = a0_AhHmc_hhHm_00(unitarity_s,2,2,2,1,4,7) 
scatter_matrix2(4,8) = a0_AhHmc_hhHm_00(unitarity_s,2,2,2,2,4,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,1) = a0_hhHmc_AhHm_00(unitarity_s,1,1,1,1,5,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,2) = a0_hhHmc_AhHm_00(unitarity_s,1,1,1,2,5,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,3) = a0_hhHmc_AhHm_00(unitarity_s,1,1,2,1,5,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,4) = a0_hhHmc_AhHm_00(unitarity_s,1,1,2,2,5,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,5) = a0_hhHmc_hhHm_00(unitarity_s,1,1,1,1,5,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,6) = a0_hhHmc_hhHm_00(unitarity_s,1,1,1,2,5,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,7) = a0_hhHmc_hhHm_00(unitarity_s,1,1,2,1,5,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,8) = a0_hhHmc_hhHm_00(unitarity_s,1,1,2,2,5,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,1) = a0_hhHmc_AhHm_00(unitarity_s,1,2,1,1,6,1) 
scatter_matrix2(6,2) = a0_hhHmc_AhHm_00(unitarity_s,1,2,1,2,6,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,3) = a0_hhHmc_AhHm_00(unitarity_s,1,2,2,1,6,3) 
scatter_matrix2(6,4) = a0_hhHmc_AhHm_00(unitarity_s,1,2,2,2,6,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,5) = a0_hhHmc_hhHm_00(unitarity_s,1,2,1,1,6,5) 
scatter_matrix2(6,6) = a0_hhHmc_hhHm_00(unitarity_s,1,2,1,2,6,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,7) = a0_hhHmc_hhHm_00(unitarity_s,1,2,2,1,6,7) 
scatter_matrix2(6,8) = a0_hhHmc_hhHm_00(unitarity_s,1,2,2,2,6,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,1) = a0_hhHmc_AhHm_00(unitarity_s,2,1,1,1,7,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,2) = a0_hhHmc_AhHm_00(unitarity_s,2,1,1,2,7,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,3) = a0_hhHmc_AhHm_00(unitarity_s,2,1,2,1,7,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,4) = a0_hhHmc_AhHm_00(unitarity_s,2,1,2,2,7,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,5) = a0_hhHmc_hhHm_00(unitarity_s,2,1,1,1,7,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,6) = a0_hhHmc_hhHm_00(unitarity_s,2,1,1,2,7,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,7) = a0_hhHmc_hhHm_00(unitarity_s,2,1,2,1,7,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,8) = a0_hhHmc_hhHm_00(unitarity_s,2,1,2,2,7,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,1) = a0_hhHmc_AhHm_00(unitarity_s,2,2,1,1,8,1) 
scatter_matrix2(8,2) = a0_hhHmc_AhHm_00(unitarity_s,2,2,1,2,8,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,3) = a0_hhHmc_AhHm_00(unitarity_s,2,2,2,1,8,3) 
scatter_matrix2(8,4) = a0_hhHmc_AhHm_00(unitarity_s,2,2,2,2,8,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,5) = a0_hhHmc_hhHm_00(unitarity_s,2,2,1,1,8,5) 
scatter_matrix2(8,6) = a0_hhHmc_hhHm_00(unitarity_s,2,2,1,2,8,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,7) = a0_hhHmc_hhHm_00(unitarity_s,2,2,2,1,8,7) 
scatter_matrix2(8,8) = a0_hhHmc_hhHm_00(unitarity_s,2,2,2,2,8,8) 


Select CASE (TUcutLevel)  
CASE (2) 
  scatter_matrix2B = scatter_matrix2
Do i=1,8 
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
   Do i=1,8 
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
If (IncludeGoldstoneExternal) scatter_matrix3(1,1) = a0_HmcHmc_HmHm_00(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(1,2) = a0_HmcHmc_HmHm_00(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix3(1,3) = a0_HmcHmc_HmHm_00(unitarity_s,1,1,2,2,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,1) = a0_HmcHmc_HmHm_00(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,2) = a0_HmcHmc_HmHm_00(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,3) = a0_HmcHmc_HmHm_00(unitarity_s,1,2,2,2,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix3(3,1) = a0_HmcHmc_HmHm_00(unitarity_s,2,2,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(3,2) = a0_HmcHmc_HmHm_00(unitarity_s,2,2,1,2,3,2) 
scatter_matrix3(3,3) = a0_HmcHmc_HmHm_00(unitarity_s,2,2,2,2,3,3) 


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

Complex(dp) Function a0_AhAh_AhAh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = MAh(i3)
m4 = MAh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhAhAh(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i2,iprop)
unicpl2(1)=cplAhAhAh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i2,iprop)
unicpl2(1)=cplAhAhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i3,iprop)
unicpl2(1)=cplAhAhAh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i3,iprop)
unicpl2(1)=cplAhAhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i4,iprop)
unicpl2(1)=cplAhAhAh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i4,iprop)
unicpl2(1)=cplAhAhhh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_AhAh_00

Complex(dp) Function a0_AhAh_Ahhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhAhhh(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i2,iprop)
unicpl2(1)=cplAhAhhh(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i2,iprop)
unicpl2(1)=cplAhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i3,iprop)
unicpl2(1)=cplAhAhhh(i2,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i3,iprop)
unicpl2(1)=cplAhhhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i4)
unicpl2(1)=cplAhAhAh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i4,iprop)
unicpl2(1)=cplAhAhhh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_Ahhh_00

Complex(dp) Function a0_AhAh_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhhhhh(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i2,iprop)
unicpl2(1)=cplAhhhhh(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i2,iprop)
unicpl2(1)=cplhhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i3)
unicpl2(1)=cplAhAhhh(i2,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i3,iprop)
unicpl2(1)=cplAhhhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i4)
unicpl2(1)=cplAhAhhh(i2,iprop,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i4,iprop)
unicpl2(1)=cplAhhhhh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_hhhh_00

Complex(dp) Function a0_AhAh_HmHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MAh(i2)
m3 = MHm(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhHmcHm(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i2,iprop)
unicpl2(1)=cplAhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i2,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,i3,iprop)
unicpl2(1)=cplAhHmcHm(i2,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,iprop,i4)
unicpl2(1)=cplAhHmcHm(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhAh_HmHmc_00

Complex(dp) Function a0_Ahhh_AhAh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = MAh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhAhhh(i1,i3,i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i2)
unicpl2(1)=cplAhAhAh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i2,iprop)
unicpl2(1)=cplAhAhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i3,iprop)
unicpl2(1)=cplAhAhhh(i4,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i3,iprop)
unicpl2(1)=cplAhhhhh(i4,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i4,iprop)
unicpl2(1)=cplAhAhhh(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i4,iprop)
unicpl2(1)=cplAhhhhh(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_AhAh_00

Complex(dp) Function a0_Ahhh_Ahhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhhhhh(i1,i3,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i2)
unicpl2(1)=cplAhAhhh(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i2,iprop)
unicpl2(1)=cplAhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i3,iprop)
unicpl2(1)=cplAhhhhh(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i3,iprop)
unicpl2(1)=cplhhhhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i4)
unicpl2(1)=cplAhAhhh(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i4,iprop)
unicpl2(1)=cplAhhhhh(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_Ahhh_00

Complex(dp) Function a0_Ahhh_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhhhhh(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i2)
unicpl2(1)=cplAhhhhh(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i2,iprop)
unicpl2(1)=cplhhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i3)
unicpl2(1)=cplAhhhhh(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i3,iprop)
unicpl2(1)=cplhhhhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i4)
unicpl2(1)=cplAhhhhh(iprop,i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i4,iprop)
unicpl2(1)=cplhhhhhh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_hhhh_00

Complex(dp) Function a0_Ahhh_HmHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = Mhh(i2)
m3 = MHm(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhHmcHm(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i2)
unicpl2(1)=cplAhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i2,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(i2,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,iprop,i4)
unicpl2(1)=cplhhHmcHm(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_Ahhh_HmHmc_00

Complex(dp) Function a0_AhHm_AhHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MHm(i2)
m3 = MAh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhHmcHm(i1,i3,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,i2,iprop)
unicpl2(1)=cplAhHmcHm(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i3,iprop)
unicpl2(1)=cplAhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,iprop,i4)
unicpl2(1)=cplAhHmcHm(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHm_AhHmc_00

Complex(dp) Function a0_AhHm_hhHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MHm(i2)
m3 = Mhh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhHmcHm(i1,i3,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,i2,iprop)
unicpl2(1)=cplhhHmcHm(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i3)
unicpl2(1)=cplAhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,iprop,i4)
unicpl2(1)=cplhhHmcHm(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHm_hhHmc_00

Complex(dp) Function a0_AhHmc_AhHm_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MHm(i2)
m3 = MAh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhHmcHm(i1,i3,i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,iprop,i2)
unicpl2(1)=cplAhHmcHm(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhAh(i1,i3,iprop)
unicpl2(1)=cplAhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,i4,iprop)
unicpl2(1)=cplAhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHmc_AhHm_00

Complex(dp) Function a0_AhHmc_hhHm_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MAh(i1)
m2 = MHm(i2)
m3 = Mhh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhHmcHm(i1,i3,i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,iprop,i2)
unicpl2(1)=cplhhHmcHm(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i1,iprop,i3)
unicpl2(1)=cplAhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i1,i4,iprop)
unicpl2(1)=cplhhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_AhHmc_hhHm_00

Complex(dp) Function a0_hhhh_AhAh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = MAh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhhhhh(i3,i4,i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i2)
unicpl2(1)=cplAhAhAh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i2,iprop)
unicpl2(1)=cplAhAhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i3,iprop,i1)
unicpl2(1)=cplAhAhhh(i4,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i3,i1,iprop)
unicpl2(1)=cplAhhhhh(i4,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i4,iprop,i1)
unicpl2(1)=cplAhAhhh(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i4,i1,iprop)
unicpl2(1)=cplAhhhhh(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_AhAh_00

Complex(dp) Function a0_hhhh_Ahhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhhhhh(i3,i1,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i2)
unicpl2(1)=cplAhAhhh(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i2,iprop)
unicpl2(1)=cplAhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i3,iprop,i1)
unicpl2(1)=cplAhhhhh(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i3,i1,iprop)
unicpl2(1)=cplhhhhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i4)
unicpl2(1)=cplAhAhhh(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i4,iprop)
unicpl2(1)=cplAhhhhh(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_Ahhh_00

Complex(dp) Function a0_hhhh_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhhhhh(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i2)
unicpl2(1)=cplAhhhhh(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i2,iprop)
unicpl2(1)=cplhhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i3)
unicpl2(1)=cplAhhhhh(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i3,iprop)
unicpl2(1)=cplhhhhhh(i2,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i4)
unicpl2(1)=cplAhhhhh(iprop,i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i4,iprop)
unicpl2(1)=cplhhhhhh(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_hhhh_00

Complex(dp) Function a0_hhhh_HmHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = Mhh(i2)
m3 = MHm(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHmcHm(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i2)
unicpl2(1)=cplAhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i2,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(i2,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,iprop,i4)
unicpl2(1)=cplhhHmcHm(i2,i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhhh_HmHmc_00

Complex(dp) Function a0_hhHm_AhHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = MHm(i2)
m3 = MAh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhHmcHm(i3,i1,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,i2,iprop)
unicpl2(1)=cplAhHmcHm(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i3,iprop,i1)
unicpl2(1)=cplAhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i3,i1,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,iprop,i4)
unicpl2(1)=cplAhHmcHm(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHm_AhHmc_00

Complex(dp) Function a0_hhHm_hhHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = MHm(i2)
m3 = Mhh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHmcHm(i1,i3,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,i2,iprop)
unicpl2(1)=cplhhHmcHm(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i3)
unicpl2(1)=cplAhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,iprop,i4)
unicpl2(1)=cplhhHmcHm(i3,i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHm_hhHmc_00

Complex(dp) Function a0_hhHmc_AhHm_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = MHm(i2)
m3 = MAh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhHmcHm(i3,i1,i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,iprop,i2)
unicpl2(1)=cplAhHmcHm(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhAhhh(i3,iprop,i1)
unicpl2(1)=cplAhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(i3,i1,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,i4,iprop)
unicpl2(1)=cplAhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHmc_AhHm_00

Complex(dp) Function a0_hhHmc_hhHm_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = Mhh(i1)
m2 = MHm(i2)
m3 = Mhh(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHmcHm(i1,i3,i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,iprop,i2)
unicpl2(1)=cplhhHmcHm(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHm(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhhhhh(iprop,i1,i3)
unicpl2(1)=cplAhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhhhhh(i1,i3,iprop)
unicpl2(1)=cplhhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i1,i4,iprop)
unicpl2(1)=cplhhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_hhHmc_hhHm_00

Complex(dp) Function a0_HmHm_HmcHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MHm(i1)
m2 = MHm(i2)
m3 = MHm(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplHmHmcHmcHm(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i3)
unicpl2(1)=cplAhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i3)
unicpl2(1)=cplhhHmcHm(iprop,i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i4)
unicpl2(1)=cplAhHmcHm(iprop,i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i4)
unicpl2(1)=cplhhHmcHm(iprop,i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HmHm_HmcHmc_00

Complex(dp) Function a0_HmHmc_AhAh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MHm(i1)
m2 = MHm(i2)
m3 = MAh(i3)
m4 = MAh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhAhHmcHm(i3,i4,i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i2)
unicpl2(1)=cplAhAhAh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i2)
unicpl2(1)=cplAhAhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i3,i1,iprop)
unicpl2(1)=cplAhHmcHm(i4,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i4,i1,iprop)
unicpl2(1)=cplAhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HmHmc_AhAh_00

Complex(dp) Function a0_HmHmc_Ahhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MHm(i1)
m2 = MHm(i2)
m3 = MAh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplAhhhHmcHm(i3,i4,i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i2)
unicpl2(1)=cplAhAhhh(i3,iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i2)
unicpl2(1)=cplAhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(i3,i1,iprop)
unicpl2(1)=cplhhHmcHm(i4,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i4,i1,iprop)
unicpl2(1)=cplAhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HmHmc_Ahhh_00

Complex(dp) Function a0_HmHmc_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MHm(i1)
m2 = MHm(i2)
m3 = Mhh(i3)
m4 = Mhh(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHmcHm(i3,i4,i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i2)
unicpl2(1)=cplAhhhhh(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i2)
unicpl2(1)=cplhhhhhh(i3,i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i3,i1,iprop)
unicpl2(1)=cplhhHmcHm(i4,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(i4,i1,iprop)
unicpl2(1)=cplhhHmcHm(i3,iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHm(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHm(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHm(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HmHmc_hhhh_00

Complex(dp) Function a0_HmHmc_HmHmc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MHm(i1)
m2 = MHm(i2)
m3 = MHm(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplHmHmcHmcHm(i1,i3,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i2)
unicpl2(1)=cplAhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MAh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i2)
unicpl2(1)=cplhhHmcHm(iprop,i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i1,i4)
unicpl2(1)=cplAhHmcHm(iprop,i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i1,i4)
unicpl2(1)=cplhhHmcHm(iprop,i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HmHmc_HmHmc_00

Complex(dp) Function a0_HmcHmc_HmHm_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
Implicit None 
Integer, Intent(in) :: i1,i2,i3,i4,ind1,ind2 
Real(dp), Intent(in) :: s 
Integer :: iprop, istart,c1,c2,c2end 
Logical :: pole_s_channel=.False. 
Real(dp) :: m1,m2,m3,m4 
Complex(dp) :: tempamp2(1,1) 
Complex(dp) :: amp_poles 
Complex(dp) :: unicpl1(8),unicpl2(8) 
amp = 0._dp 
amp_poles = 0._dp 
m1 = MHm(i1)
m2 = MHm(i2)
m3 = MHm(i3)
m4 = MHm(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplHmHmcHmcHm(i3,i4,i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i3,i1)
unicpl2(1)=cplAhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i3,i1)
unicpl2(1)=cplhhHmcHm(iprop,i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! U-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplAhHmcHm(iprop,i4,i1)
unicpl2(1)=cplAhHmcHm(iprop,i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MAh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MAh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MAh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,2
unicpl1(1)=cplhhHmcHm(iprop,i4,i1)
unicpl2(1)=cplhhHmcHm(iprop,i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh(iProp)  
Select Case (TUcutLevel) 
 Case (3) 
   Pole_Present = .True. 
 Case (2) 
  RemoveTUpoles(ind1) = 1 
  RemoveTUpoles(ind2) = 1 
 Case (1) 
  amp_poles  = 0._dp
 Case (0) 
  amp = amp + tempamp2(1,1)
End Select 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
End if 
amp = 0.5_dp*oo16pi*amp*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp=amp/sqrt(2._dp) 
If (i3.eq.i4) amp=amp/sqrt(2._dp) 
If (TUcutLevel.eq.1) Then 
 amp_poles = 0.5_dp*oo16pi*amp_poles*sqrt(sqrt(Kaehler(s,m1**2,m2**2)*Kaehler(s,m3**2,m4**2)))/s 
If (i1.eq.i2) amp_poles=amp_poles/sqrt(2._dp) 
If (i3.eq.i4) amp_poles=amp_poles/sqrt(2._dp) 
  If ((Abs(amp_poles)/Abs(amp)).gt.cut_amplitudes) Then 
   ! Write(*,*) "TU ratio", (Abs(amp_poles)/Abs(amp))  
   If (Abs(amp).gt.max_element_removed) max_element_removed = Abs(amp) 
   amp = 0._dp 
  End if 
End if 
End Function a0_HmcHmc_HmHm_00

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
If (res.ne.res) res=0._dp 
If (Aimag(res).gt.1._dp) Then 
 CheckTpole = 0._dp 
Else 
 CheckTpole = Real(1.05_dp*res,dp) 
End If 
End Function CheckTpole 
 
Real(dp) Function CheckUpole(m1,m2,m3,m4,mP) 
Implicit None 
Real(dp),Intent(in)::m1,m2,m3,m4,mP
Complex(dp) :: res
res =(m2*m4-m3*m4+m2*mP+m3*mP+m4*mP-mP**2+m1*(-m2+m3+mP)+Sqrt(m2**2+(m3-mP)**2 &
  &-2*m2*(m3+mP))*Sqrt(m1**2+(m4-mP)**2-2*m1*(m4+mP)))/(2.*mP)
If (res.ne.res) res=0._dp 
If (Aimag(res).gt.1._dp) Then 
 CheckUpole = 0._dp 
Else 
 CheckUpole = Real(1.05_dp*res,dp) 
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
  
End Module Unitarity_gumTHDMII 
