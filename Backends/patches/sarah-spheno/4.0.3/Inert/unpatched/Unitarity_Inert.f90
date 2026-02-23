! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:33 on 18.2.2026   
! ----------------------------------------------------------------------  
 
 
Module Unitarity_Inert 
 
Use Control 
Use Settings 
Use LoopFunctions 
Use Mathematics 
Use Model_Data_Inert 
Use RGEs_Inert 
Use LoopMasses_Inert 
Use TreeLevelMasses_Inert 
Use Couplings_Inert 
Use Tadpoles_Inert 
 Use StandardModel 
 
Logical :: IncludeGoldstoneContributions=.true. 
Logical :: IncludeGoldstoneExternal=.true. 
Logical :: AddR=.true. 
Real(dp) :: cut_elements = 0.0001_dp 
Real(dp) :: cut_amplitudes = 0.01_dp 
Logical :: Ignore_poles=.false. 
 
Contains 

Subroutine ScatteringEigenvalues(vinput,g1input,g2input,g3input,Lam5input,            & 
& Lam1input,Lam4input,Lam3input,Lam2input,Yeinput,Ydinput,Yuinput,mHd2input,             & 
& mHu2input,delta0,kont)

Implicit None 
Integer, Intent(inout) :: kont 
Integer :: ierr 
Real(dp) :: g1,g2,g3,mHd2,mHu2

Complex(dp) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp) :: v

Real(dp) :: gD(70) 
Real(dp) :: tz,dt,q,q2,mudim 
Real(dp), Intent(in) :: delta0 
Integer :: iter 
Complex(dp) :: scatter_matrix(36,36) 
Complex(dp) :: rot_matrix(36,36) 
Real(dp) :: eigenvalues_matrix(36), test(2), unitarity_s, scattering_eigenvalue, step_size
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vinput

Complex(dp),Intent(in) :: Lam5input,Lam1input,Lam4input,Lam3input,Lam2input,Yeinput(3,3),Ydinput(3,3),          & 
& Yuinput(3,3)

max_scattering_eigenvalue = 0._dp 

g1 = g1input 
g2 = g2input 
g3 = g3input 
Lam5 = Lam5input 
Lam1 = Lam1input 
Lam4 = Lam4input 
Lam3 = Lam3input 
Lam2 = Lam2input 
Ye = Yeinput 
Yd = Ydinput 
Yu = Yuinput 
mHd2 = mHd2input 
mHu2 = mHu2input 
v = vinput 
scatter_matrix=0._dp 
scatter_matrix(1,16) =-1._dp*(Lam5)
scatter_matrix(1,27) =-2._dp*(Lam1)
scatter_matrix(2,17) =Lam5
scatter_matrix(2,28) =-2._dp*(Lam1)
scatter_matrix(3,3) =-2._dp*(Lam5)
scatter_matrix(3,11) =Lam5
scatter_matrix(3,29) =-1._dp*(Lam3)
scatter_matrix(3,33) =-1._dp*(Lam4)
scatter_matrix(4,10) =Lam5
scatter_matrix(4,30) =-1._dp*(Lam3) - Lam4
scatter_matrix(5,5) =-4._dp*(Lam1)
scatter_matrix(5,13) =-2._dp*(Lam1)
scatter_matrix(5,20) =-1._dp*(Lam3)
scatter_matrix(5,26) =-1._dp*(Lam3) - Lam4
scatter_matrix(6,12) =-2._dp*(Lam1)
scatter_matrix(6,21) =-1._dp*(Lam4)
scatter_matrix(7,18) =-1._dp*(Lam3)
scatter_matrix(8,19) =-1._dp*(Lam4)
scatter_matrix(8,23) =-1._dp*(Lam3) - Lam4
scatter_matrix(9,22) =-1._dp*(Lam5)
scatter_matrix(9,31) =-2._dp*(Lam1)
scatter_matrix(10,4) =Lam5
scatter_matrix(10,32) =-1._dp*(Lam3) - Lam4
scatter_matrix(11,3) =Lam5
scatter_matrix(11,11) =-2._dp*(Lam5)
scatter_matrix(11,29) =-1._dp*(Lam4)
scatter_matrix(11,33) =-1._dp*(Lam3)
scatter_matrix(12,6) =-2._dp*(Lam1)
scatter_matrix(12,25) =-1._dp*(Lam4)
scatter_matrix(13,5) =-2._dp*(Lam1)
scatter_matrix(13,13) =-4._dp*(Lam1)
scatter_matrix(13,20) =-1._dp*(Lam3) - Lam4
scatter_matrix(13,26) =-1._dp*(Lam3)
scatter_matrix(14,19) =-1._dp*(Lam3) - Lam4
scatter_matrix(14,23) =-1._dp*(Lam4)
scatter_matrix(15,24) =-1._dp*(Lam3)
scatter_matrix(16,1) =-1._dp*(Lam5)
scatter_matrix(16,34) =-2._dp*(Lam2)
scatter_matrix(17,2) =Lam5
scatter_matrix(17,35) =-2._dp*(Lam2)
scatter_matrix(18,7) =-1._dp*(Lam3)
scatter_matrix(19,8) =-1._dp*(Lam4)
scatter_matrix(19,14) =-1._dp*(Lam3) - Lam4
scatter_matrix(20,5) =-1._dp*(Lam3)
scatter_matrix(20,13) =-1._dp*(Lam3) - Lam4
scatter_matrix(20,20) =-4._dp*(Lam2)
scatter_matrix(20,26) =-2._dp*(Lam2)
scatter_matrix(21,6) =-1._dp*(Lam4)
scatter_matrix(21,25) =-2._dp*(Lam2)
scatter_matrix(22,9) =-1._dp*(Lam5)
scatter_matrix(22,36) =-2._dp*(Lam2)
scatter_matrix(23,8) =-1._dp*(Lam3) - Lam4
scatter_matrix(23,14) =-1._dp*(Lam4)
scatter_matrix(24,15) =-1._dp*(Lam3)
scatter_matrix(25,12) =-1._dp*(Lam4)
scatter_matrix(25,21) =-2._dp*(Lam2)
scatter_matrix(26,5) =-1._dp*(Lam3) - Lam4
scatter_matrix(26,13) =-1._dp*(Lam3)
scatter_matrix(26,20) =-2._dp*(Lam2)
scatter_matrix(26,26) =-4._dp*(Lam2)
scatter_matrix(27,1) =-2._dp*(Lam1)
scatter_matrix(27,34) =-Conjg(Lam5)
scatter_matrix(28,2) =-2._dp*(Lam1)
scatter_matrix(28,35) =Conjg(Lam5)
scatter_matrix(29,3) =-1._dp*(Lam3)
scatter_matrix(29,11) =-1._dp*(Lam4)
scatter_matrix(29,29) =-2*Conjg(Lam5)
scatter_matrix(29,33) =Conjg(Lam5)
scatter_matrix(30,4) =-1._dp*(Lam3) - Lam4
scatter_matrix(30,32) =Conjg(Lam5)
scatter_matrix(31,9) =-2._dp*(Lam1)
scatter_matrix(31,36) =-Conjg(Lam5)
scatter_matrix(32,10) =-1._dp*(Lam3) - Lam4
scatter_matrix(32,30) =Conjg(Lam5)
scatter_matrix(33,3) =-1._dp*(Lam4)
scatter_matrix(33,11) =-1._dp*(Lam3)
scatter_matrix(33,29) =Conjg(Lam5)
scatter_matrix(33,33) =-2*Conjg(Lam5)
scatter_matrix(34,16) =-2._dp*(Lam2)
scatter_matrix(34,27) =-Conjg(Lam5)
scatter_matrix(35,17) =-2._dp*(Lam2)
scatter_matrix(35,28) =Conjg(Lam5)
scatter_matrix(36,22) =-2._dp*(Lam2)
scatter_matrix(36,31) =-Conjg(Lam5)
Call EigenSystem( oo16pi*scatter_matrix,eigenvalues_matrix,rot_matrix,ierr,test) 

scattering_eigenvalue=MaxVal(Abs(eigenvalues_matrix)) 
max_scattering_eigenvalue=scattering_eigenvalue 
If (max_scattering_eigenvalue.gt.0.5_dp) TreeUnitarity=0._dp 
End Subroutine ScatteringEigenvalues

Subroutine ScatteringEigenvaluesWithTrilinears(MA0input,MA02input,MFdinput,           & 
& MFd2input,MFeinput,MFe2input,MFuinput,MFu2input,MG0input,MG02input,MH0input,           & 
& MH02input,Mhhinput,Mhh2input,MHpinput,MHp2input,MVWpinput,MVWp2input,MVZinput,         & 
& MVZ2input,TWinput,ZDLinput,ZDRinput,ZELinput,ZERinput,ZPinput,ZULinput,ZURinput,       & 
& ZWinput,ZZinput,betaHinput,vinput,g1input,g2input,g3input,Lam5input,Lam1input,         & 
& Lam4input,Lam3input,Lam2input,Yeinput,Ydinput,Yuinput,mHd2input,mHu2input,             & 
& delta0,kont)

Implicit None 
Integer, Intent(inout) :: kont 
Integer :: ierr 
Logical :: Pole_Present, SPole_Present, TPole_Present, UPole_Present 
Integer :: RemoveTUpoles(99) 
Real(dp) :: g1,g2,g3,mHd2,mHu2

Complex(dp) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp) :: v

Complex(dp) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplA0A0A0A0,cplA0A0G0G0,           & 
& cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0G0G0H0,cplA0G0H0hh,         & 
& cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),cplG0G0G0G0,cplG0G0H0H0,               & 
& cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),cplH0H0H0H0,               & 
& cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,cplhhhhHpcHp(2,2),         & 
& cplHpHpcHpcHp(2,2,2,2)

Real(dp) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vinput

Complex(dp),Intent(in) :: Lam5input,Lam1input,Lam4input,Lam3input,Lam2input,Yeinput(3,3),Ydinput(3,3),          & 
& Yuinput(3,3)

Real(dp),Intent(in) :: MA0input,MA02input,MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),     & 
& MFu2input(3),MG0input,MG02input,MH0input,MH02input,Mhhinput,Mhh2input,MHpinput(2),     & 
& MHp2input(2),MVWpinput,MVWp2input,MVZinput,MVZ2input,TWinput,ZPinput(2,2),             & 
& ZZinput(2,2),betaHinput

Complex(dp),Intent(in) :: ZDLinput(3,3),ZDRinput(3,3),ZELinput(3,3),ZERinput(3,3),ZULinput(3,3),ZURinput(3,3),  & 
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
Real(dp) :: gD(70) 
Real(dp) :: tz,dt,q,q2,mudim, max_element_removed  
Real(dp), Intent(in) :: delta0 
Integer :: iter, i, il,ir, count 
g1 = g1input 
g2 = g2input 
g3 = g3input 
Lam5 = Lam5input 
Lam1 = Lam1input 
Lam4 = Lam4input 
Lam3 = Lam3input 
Lam2 = Lam2input 
Ye = Yeinput 
Yd = Ydinput 
Yu = Yuinput 
mHd2 = mHd2input 
mHu2 = mHu2input 
v = vinput 
Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,.True.,kont)

Call CouplingsColourStructures(Lam5,v,Lam3,Lam4,ZP,Lam1,Lam2,cplA0A0G0,               & 
& cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,     & 
& cplhhhhhh,cplhhHpcHp,cplA0A0A0A0,cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,      & 
& cplA0A0HpcHp,cplA0G0G0H0,cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,            & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,             & 
& cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,            & 
& cplHpHpcHpcHp)

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
scatter_matrix1(1,1) = a0_A0A0_A0A0_00(unitarity_s,1,1,1,1,1,1) 
scatter_matrix1(1,2) = a0_A0A0_A0G0_00(unitarity_s,1,1,1,1,1,2) 
scatter_matrix1(1,3) = a0_A0A0_A0H0_00(unitarity_s,1,1,1,1,1,3) 
scatter_matrix1(1,4) = a0_A0A0_A0hh_00(unitarity_s,1,1,1,1,1,4) 
scatter_matrix1(1,5) = a0_A0A0_G0G0_00(unitarity_s,1,1,1,1,1,5) 
scatter_matrix1(1,6) = a0_A0A0_G0H0_00(unitarity_s,1,1,1,1,1,6) 
scatter_matrix1(1,7) = a0_A0A0_G0hh_00(unitarity_s,1,1,1,1,1,7) 
scatter_matrix1(1,8) = a0_A0A0_H0H0_00(unitarity_s,1,1,1,1,1,8) 
scatter_matrix1(1,9) = a0_A0A0_H0hh_00(unitarity_s,1,1,1,1,1,9) 
scatter_matrix1(1,10) = a0_A0A0_hhhh_00(unitarity_s,1,1,1,1,1,10) 
scatter_matrix1(1,11) = a0_A0A0_HpHpc_00(unitarity_s,1,1,1,1,1,11) 
scatter_matrix1(1,12) = a0_A0A0_HpHpc_00(unitarity_s,1,1,1,2,1,12) 
scatter_matrix1(1,13) = a0_A0A0_HpHpc_00(unitarity_s,1,1,2,1,1,13) 
scatter_matrix1(1,14) = a0_A0A0_HpHpc_00(unitarity_s,1,1,2,2,1,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,1) = a0_A0G0_A0A0_00(unitarity_s,1,1,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,2) = a0_A0G0_A0G0_00(unitarity_s,1,1,1,1,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,3) = a0_A0G0_A0H0_00(unitarity_s,1,1,1,1,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,4) = a0_A0G0_A0hh_00(unitarity_s,1,1,1,1,2,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,5) = a0_A0G0_G0G0_00(unitarity_s,1,1,1,1,2,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,6) = a0_A0G0_G0H0_00(unitarity_s,1,1,1,1,2,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,7) = a0_A0G0_G0hh_00(unitarity_s,1,1,1,1,2,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,8) = a0_A0G0_H0H0_00(unitarity_s,1,1,1,1,2,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,9) = a0_A0G0_H0hh_00(unitarity_s,1,1,1,1,2,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,10) = a0_A0G0_hhhh_00(unitarity_s,1,1,1,1,2,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,11) = a0_A0G0_HpHpc_00(unitarity_s,1,1,1,1,2,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,12) = a0_A0G0_HpHpc_00(unitarity_s,1,1,1,2,2,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,13) = a0_A0G0_HpHpc_00(unitarity_s,1,1,2,1,2,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(2,14) = a0_A0G0_HpHpc_00(unitarity_s,1,1,2,2,2,14) 
scatter_matrix1(3,1) = a0_A0H0_A0A0_00(unitarity_s,1,1,1,1,3,1) 
scatter_matrix1(3,2) = a0_A0H0_A0G0_00(unitarity_s,1,1,1,1,3,2) 
scatter_matrix1(3,3) = a0_A0H0_A0H0_00(unitarity_s,1,1,1,1,3,3) 
scatter_matrix1(3,4) = a0_A0H0_A0hh_00(unitarity_s,1,1,1,1,3,4) 
scatter_matrix1(3,5) = a0_A0H0_G0G0_00(unitarity_s,1,1,1,1,3,5) 
scatter_matrix1(3,6) = a0_A0H0_G0H0_00(unitarity_s,1,1,1,1,3,6) 
scatter_matrix1(3,7) = a0_A0H0_G0hh_00(unitarity_s,1,1,1,1,3,7) 
scatter_matrix1(3,8) = a0_A0H0_H0H0_00(unitarity_s,1,1,1,1,3,8) 
scatter_matrix1(3,9) = a0_A0H0_H0hh_00(unitarity_s,1,1,1,1,3,9) 
scatter_matrix1(3,10) = a0_A0H0_hhhh_00(unitarity_s,1,1,1,1,3,10) 
scatter_matrix1(3,11) = a0_A0H0_HpHpc_00(unitarity_s,1,1,1,1,3,11) 
scatter_matrix1(3,12) = a0_A0H0_HpHpc_00(unitarity_s,1,1,1,2,3,12) 
scatter_matrix1(3,13) = a0_A0H0_HpHpc_00(unitarity_s,1,1,2,1,3,13) 
scatter_matrix1(3,14) = a0_A0H0_HpHpc_00(unitarity_s,1,1,2,2,3,14) 
scatter_matrix1(4,1) = a0_A0hh_A0A0_00(unitarity_s,1,1,1,1,4,1) 
scatter_matrix1(4,2) = a0_A0hh_A0G0_00(unitarity_s,1,1,1,1,4,2) 
scatter_matrix1(4,3) = a0_A0hh_A0H0_00(unitarity_s,1,1,1,1,4,3) 
scatter_matrix1(4,4) = a0_A0hh_A0hh_00(unitarity_s,1,1,1,1,4,4) 
scatter_matrix1(4,5) = a0_A0hh_G0G0_00(unitarity_s,1,1,1,1,4,5) 
scatter_matrix1(4,6) = a0_A0hh_G0H0_00(unitarity_s,1,1,1,1,4,6) 
scatter_matrix1(4,7) = a0_A0hh_G0hh_00(unitarity_s,1,1,1,1,4,7) 
scatter_matrix1(4,8) = a0_A0hh_H0H0_00(unitarity_s,1,1,1,1,4,8) 
scatter_matrix1(4,9) = a0_A0hh_H0hh_00(unitarity_s,1,1,1,1,4,9) 
scatter_matrix1(4,10) = a0_A0hh_hhhh_00(unitarity_s,1,1,1,1,4,10) 
scatter_matrix1(4,11) = a0_A0hh_HpHpc_00(unitarity_s,1,1,1,1,4,11) 
scatter_matrix1(4,12) = a0_A0hh_HpHpc_00(unitarity_s,1,1,1,2,4,12) 
scatter_matrix1(4,13) = a0_A0hh_HpHpc_00(unitarity_s,1,1,2,1,4,13) 
scatter_matrix1(4,14) = a0_A0hh_HpHpc_00(unitarity_s,1,1,2,2,4,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,1) = a0_G0G0_A0A0_00(unitarity_s,1,1,1,1,5,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,2) = a0_G0G0_A0G0_00(unitarity_s,1,1,1,1,5,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,3) = a0_G0G0_A0H0_00(unitarity_s,1,1,1,1,5,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,4) = a0_G0G0_A0hh_00(unitarity_s,1,1,1,1,5,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,5) = a0_G0G0_G0G0_00(unitarity_s,1,1,1,1,5,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,6) = a0_G0G0_G0H0_00(unitarity_s,1,1,1,1,5,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,7) = a0_G0G0_G0hh_00(unitarity_s,1,1,1,1,5,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,8) = a0_G0G0_H0H0_00(unitarity_s,1,1,1,1,5,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,9) = a0_G0G0_H0hh_00(unitarity_s,1,1,1,1,5,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,10) = a0_G0G0_hhhh_00(unitarity_s,1,1,1,1,5,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,11) = a0_G0G0_HpHpc_00(unitarity_s,1,1,1,1,5,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,12) = a0_G0G0_HpHpc_00(unitarity_s,1,1,1,2,5,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,13) = a0_G0G0_HpHpc_00(unitarity_s,1,1,2,1,5,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(5,14) = a0_G0G0_HpHpc_00(unitarity_s,1,1,2,2,5,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,1) = a0_G0H0_A0A0_00(unitarity_s,1,1,1,1,6,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,2) = a0_G0H0_A0G0_00(unitarity_s,1,1,1,1,6,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,3) = a0_G0H0_A0H0_00(unitarity_s,1,1,1,1,6,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,4) = a0_G0H0_A0hh_00(unitarity_s,1,1,1,1,6,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,5) = a0_G0H0_G0G0_00(unitarity_s,1,1,1,1,6,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,6) = a0_G0H0_G0H0_00(unitarity_s,1,1,1,1,6,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,7) = a0_G0H0_G0hh_00(unitarity_s,1,1,1,1,6,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,8) = a0_G0H0_H0H0_00(unitarity_s,1,1,1,1,6,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,9) = a0_G0H0_H0hh_00(unitarity_s,1,1,1,1,6,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,10) = a0_G0H0_hhhh_00(unitarity_s,1,1,1,1,6,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,11) = a0_G0H0_HpHpc_00(unitarity_s,1,1,1,1,6,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,12) = a0_G0H0_HpHpc_00(unitarity_s,1,1,1,2,6,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,13) = a0_G0H0_HpHpc_00(unitarity_s,1,1,2,1,6,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(6,14) = a0_G0H0_HpHpc_00(unitarity_s,1,1,2,2,6,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,1) = a0_G0hh_A0A0_00(unitarity_s,1,1,1,1,7,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,2) = a0_G0hh_A0G0_00(unitarity_s,1,1,1,1,7,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,3) = a0_G0hh_A0H0_00(unitarity_s,1,1,1,1,7,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,4) = a0_G0hh_A0hh_00(unitarity_s,1,1,1,1,7,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,5) = a0_G0hh_G0G0_00(unitarity_s,1,1,1,1,7,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,6) = a0_G0hh_G0H0_00(unitarity_s,1,1,1,1,7,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,7) = a0_G0hh_G0hh_00(unitarity_s,1,1,1,1,7,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,8) = a0_G0hh_H0H0_00(unitarity_s,1,1,1,1,7,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,9) = a0_G0hh_H0hh_00(unitarity_s,1,1,1,1,7,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,10) = a0_G0hh_hhhh_00(unitarity_s,1,1,1,1,7,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,11) = a0_G0hh_HpHpc_00(unitarity_s,1,1,1,1,7,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,12) = a0_G0hh_HpHpc_00(unitarity_s,1,1,1,2,7,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,13) = a0_G0hh_HpHpc_00(unitarity_s,1,1,2,1,7,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(7,14) = a0_G0hh_HpHpc_00(unitarity_s,1,1,2,2,7,14) 
scatter_matrix1(8,1) = a0_H0H0_A0A0_00(unitarity_s,1,1,1,1,8,1) 
scatter_matrix1(8,2) = a0_H0H0_A0G0_00(unitarity_s,1,1,1,1,8,2) 
scatter_matrix1(8,3) = a0_H0H0_A0H0_00(unitarity_s,1,1,1,1,8,3) 
scatter_matrix1(8,4) = a0_H0H0_A0hh_00(unitarity_s,1,1,1,1,8,4) 
scatter_matrix1(8,5) = a0_H0H0_G0G0_00(unitarity_s,1,1,1,1,8,5) 
scatter_matrix1(8,6) = a0_H0H0_G0H0_00(unitarity_s,1,1,1,1,8,6) 
scatter_matrix1(8,7) = a0_H0H0_G0hh_00(unitarity_s,1,1,1,1,8,7) 
scatter_matrix1(8,8) = a0_H0H0_H0H0_00(unitarity_s,1,1,1,1,8,8) 
scatter_matrix1(8,9) = a0_H0H0_H0hh_00(unitarity_s,1,1,1,1,8,9) 
scatter_matrix1(8,10) = a0_H0H0_hhhh_00(unitarity_s,1,1,1,1,8,10) 
scatter_matrix1(8,11) = a0_H0H0_HpHpc_00(unitarity_s,1,1,1,1,8,11) 
scatter_matrix1(8,12) = a0_H0H0_HpHpc_00(unitarity_s,1,1,1,2,8,12) 
scatter_matrix1(8,13) = a0_H0H0_HpHpc_00(unitarity_s,1,1,2,1,8,13) 
scatter_matrix1(8,14) = a0_H0H0_HpHpc_00(unitarity_s,1,1,2,2,8,14) 
scatter_matrix1(9,1) = a0_H0hh_A0A0_00(unitarity_s,1,1,1,1,9,1) 
scatter_matrix1(9,2) = a0_H0hh_A0G0_00(unitarity_s,1,1,1,1,9,2) 
scatter_matrix1(9,3) = a0_H0hh_A0H0_00(unitarity_s,1,1,1,1,9,3) 
scatter_matrix1(9,4) = a0_H0hh_A0hh_00(unitarity_s,1,1,1,1,9,4) 
scatter_matrix1(9,5) = a0_H0hh_G0G0_00(unitarity_s,1,1,1,1,9,5) 
scatter_matrix1(9,6) = a0_H0hh_G0H0_00(unitarity_s,1,1,1,1,9,6) 
scatter_matrix1(9,7) = a0_H0hh_G0hh_00(unitarity_s,1,1,1,1,9,7) 
scatter_matrix1(9,8) = a0_H0hh_H0H0_00(unitarity_s,1,1,1,1,9,8) 
scatter_matrix1(9,9) = a0_H0hh_H0hh_00(unitarity_s,1,1,1,1,9,9) 
scatter_matrix1(9,10) = a0_H0hh_hhhh_00(unitarity_s,1,1,1,1,9,10) 
scatter_matrix1(9,11) = a0_H0hh_HpHpc_00(unitarity_s,1,1,1,1,9,11) 
scatter_matrix1(9,12) = a0_H0hh_HpHpc_00(unitarity_s,1,1,1,2,9,12) 
scatter_matrix1(9,13) = a0_H0hh_HpHpc_00(unitarity_s,1,1,2,1,9,13) 
scatter_matrix1(9,14) = a0_H0hh_HpHpc_00(unitarity_s,1,1,2,2,9,14) 
scatter_matrix1(10,1) = a0_hhhh_A0A0_00(unitarity_s,1,1,1,1,10,1) 
scatter_matrix1(10,2) = a0_hhhh_A0G0_00(unitarity_s,1,1,1,1,10,2) 
scatter_matrix1(10,3) = a0_hhhh_A0H0_00(unitarity_s,1,1,1,1,10,3) 
scatter_matrix1(10,4) = a0_hhhh_A0hh_00(unitarity_s,1,1,1,1,10,4) 
scatter_matrix1(10,5) = a0_hhhh_G0G0_00(unitarity_s,1,1,1,1,10,5) 
scatter_matrix1(10,6) = a0_hhhh_G0H0_00(unitarity_s,1,1,1,1,10,6) 
scatter_matrix1(10,7) = a0_hhhh_G0hh_00(unitarity_s,1,1,1,1,10,7) 
scatter_matrix1(10,8) = a0_hhhh_H0H0_00(unitarity_s,1,1,1,1,10,8) 
scatter_matrix1(10,9) = a0_hhhh_H0hh_00(unitarity_s,1,1,1,1,10,9) 
scatter_matrix1(10,10) = a0_hhhh_hhhh_00(unitarity_s,1,1,1,1,10,10) 
scatter_matrix1(10,11) = a0_hhhh_HpHpc_00(unitarity_s,1,1,1,1,10,11) 
scatter_matrix1(10,12) = a0_hhhh_HpHpc_00(unitarity_s,1,1,1,2,10,12) 
scatter_matrix1(10,13) = a0_hhhh_HpHpc_00(unitarity_s,1,1,2,1,10,13) 
scatter_matrix1(10,14) = a0_hhhh_HpHpc_00(unitarity_s,1,1,2,2,10,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,1) = a0_HpHpc_A0A0_00(unitarity_s,1,1,1,1,11,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,2) = a0_HpHpc_A0G0_00(unitarity_s,1,1,1,1,11,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,3) = a0_HpHpc_A0H0_00(unitarity_s,1,1,1,1,11,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,4) = a0_HpHpc_A0hh_00(unitarity_s,1,1,1,1,11,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,5) = a0_HpHpc_G0G0_00(unitarity_s,1,1,1,1,11,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,6) = a0_HpHpc_G0H0_00(unitarity_s,1,1,1,1,11,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,7) = a0_HpHpc_G0hh_00(unitarity_s,1,1,1,1,11,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,8) = a0_HpHpc_H0H0_00(unitarity_s,1,1,1,1,11,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,9) = a0_HpHpc_H0hh_00(unitarity_s,1,1,1,1,11,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,10) = a0_HpHpc_hhhh_00(unitarity_s,1,1,1,1,11,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,11) = a0_HpHpc_HpHpc_00(unitarity_s,1,1,1,1,11,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,12) = a0_HpHpc_HpHpc_00(unitarity_s,1,1,1,2,11,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,13) = a0_HpHpc_HpHpc_00(unitarity_s,1,1,2,1,11,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(11,14) = a0_HpHpc_HpHpc_00(unitarity_s,1,1,2,2,11,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,1) = a0_HpHpc_A0A0_00(unitarity_s,1,2,1,1,12,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,2) = a0_HpHpc_A0G0_00(unitarity_s,1,2,1,1,12,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,3) = a0_HpHpc_A0H0_00(unitarity_s,1,2,1,1,12,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,4) = a0_HpHpc_A0hh_00(unitarity_s,1,2,1,1,12,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,5) = a0_HpHpc_G0G0_00(unitarity_s,1,2,1,1,12,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,6) = a0_HpHpc_G0H0_00(unitarity_s,1,2,1,1,12,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,7) = a0_HpHpc_G0hh_00(unitarity_s,1,2,1,1,12,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,8) = a0_HpHpc_H0H0_00(unitarity_s,1,2,1,1,12,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,9) = a0_HpHpc_H0hh_00(unitarity_s,1,2,1,1,12,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,10) = a0_HpHpc_hhhh_00(unitarity_s,1,2,1,1,12,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,11) = a0_HpHpc_HpHpc_00(unitarity_s,1,2,1,1,12,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,12) = a0_HpHpc_HpHpc_00(unitarity_s,1,2,1,2,12,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,13) = a0_HpHpc_HpHpc_00(unitarity_s,1,2,2,1,12,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(12,14) = a0_HpHpc_HpHpc_00(unitarity_s,1,2,2,2,12,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,1) = a0_HpHpc_A0A0_00(unitarity_s,2,1,1,1,13,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,2) = a0_HpHpc_A0G0_00(unitarity_s,2,1,1,1,13,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,3) = a0_HpHpc_A0H0_00(unitarity_s,2,1,1,1,13,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,4) = a0_HpHpc_A0hh_00(unitarity_s,2,1,1,1,13,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,5) = a0_HpHpc_G0G0_00(unitarity_s,2,1,1,1,13,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,6) = a0_HpHpc_G0H0_00(unitarity_s,2,1,1,1,13,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,7) = a0_HpHpc_G0hh_00(unitarity_s,2,1,1,1,13,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,8) = a0_HpHpc_H0H0_00(unitarity_s,2,1,1,1,13,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,9) = a0_HpHpc_H0hh_00(unitarity_s,2,1,1,1,13,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,10) = a0_HpHpc_hhhh_00(unitarity_s,2,1,1,1,13,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,11) = a0_HpHpc_HpHpc_00(unitarity_s,2,1,1,1,13,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,12) = a0_HpHpc_HpHpc_00(unitarity_s,2,1,1,2,13,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,13) = a0_HpHpc_HpHpc_00(unitarity_s,2,1,2,1,13,13) 
If (IncludeGoldstoneExternal) scatter_matrix1(13,14) = a0_HpHpc_HpHpc_00(unitarity_s,2,1,2,2,13,14) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,1) = a0_HpHpc_A0A0_00(unitarity_s,2,2,1,1,14,1) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,2) = a0_HpHpc_A0G0_00(unitarity_s,2,2,1,1,14,2) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,3) = a0_HpHpc_A0H0_00(unitarity_s,2,2,1,1,14,3) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,4) = a0_HpHpc_A0hh_00(unitarity_s,2,2,1,1,14,4) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,5) = a0_HpHpc_G0G0_00(unitarity_s,2,2,1,1,14,5) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,6) = a0_HpHpc_G0H0_00(unitarity_s,2,2,1,1,14,6) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,7) = a0_HpHpc_G0hh_00(unitarity_s,2,2,1,1,14,7) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,8) = a0_HpHpc_H0H0_00(unitarity_s,2,2,1,1,14,8) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,9) = a0_HpHpc_H0hh_00(unitarity_s,2,2,1,1,14,9) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,10) = a0_HpHpc_hhhh_00(unitarity_s,2,2,1,1,14,10) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,11) = a0_HpHpc_HpHpc_00(unitarity_s,2,2,1,1,14,11) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,12) = a0_HpHpc_HpHpc_00(unitarity_s,2,2,1,2,14,12) 
If (IncludeGoldstoneExternal) scatter_matrix1(14,13) = a0_HpHpc_HpHpc_00(unitarity_s,2,2,2,1,14,13) 
scatter_matrix1(14,14) = a0_HpHpc_HpHpc_00(unitarity_s,2,2,2,2,14,14) 


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
If (IncludeGoldstoneExternal) scatter_matrix2(1,1) = a0_A0Hp_A0Hpc_00(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,2) = a0_A0Hp_A0Hpc_00(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,3) = a0_A0Hp_G0Hpc_00(unitarity_s,1,1,1,1,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,4) = a0_A0Hp_G0Hpc_00(unitarity_s,1,1,1,2,1,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,5) = a0_A0Hp_H0Hpc_00(unitarity_s,1,1,1,1,1,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,6) = a0_A0Hp_H0Hpc_00(unitarity_s,1,1,1,2,1,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,7) = a0_A0Hp_hhHpc_00(unitarity_s,1,1,1,1,1,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(1,8) = a0_A0Hp_hhHpc_00(unitarity_s,1,1,1,2,1,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,1) = a0_A0Hp_A0Hpc_00(unitarity_s,1,2,1,1,2,1) 
scatter_matrix2(2,2) = a0_A0Hp_A0Hpc_00(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,3) = a0_A0Hp_G0Hpc_00(unitarity_s,1,2,1,1,2,3) 
scatter_matrix2(2,4) = a0_A0Hp_G0Hpc_00(unitarity_s,1,2,1,2,2,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,5) = a0_A0Hp_H0Hpc_00(unitarity_s,1,2,1,1,2,5) 
scatter_matrix2(2,6) = a0_A0Hp_H0Hpc_00(unitarity_s,1,2,1,2,2,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(2,7) = a0_A0Hp_hhHpc_00(unitarity_s,1,2,1,1,2,7) 
scatter_matrix2(2,8) = a0_A0Hp_hhHpc_00(unitarity_s,1,2,1,2,2,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,1) = a0_G0Hp_A0Hpc_00(unitarity_s,1,1,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,2) = a0_G0Hp_A0Hpc_00(unitarity_s,1,1,1,2,3,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,3) = a0_G0Hp_G0Hpc_00(unitarity_s,1,1,1,1,3,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,4) = a0_G0Hp_G0Hpc_00(unitarity_s,1,1,1,2,3,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,5) = a0_G0Hp_H0Hpc_00(unitarity_s,1,1,1,1,3,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,6) = a0_G0Hp_H0Hpc_00(unitarity_s,1,1,1,2,3,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,7) = a0_G0Hp_hhHpc_00(unitarity_s,1,1,1,1,3,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(3,8) = a0_G0Hp_hhHpc_00(unitarity_s,1,1,1,2,3,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,1) = a0_G0Hp_A0Hpc_00(unitarity_s,1,2,1,1,4,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,2) = a0_G0Hp_A0Hpc_00(unitarity_s,1,2,1,2,4,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,3) = a0_G0Hp_G0Hpc_00(unitarity_s,1,2,1,1,4,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,4) = a0_G0Hp_G0Hpc_00(unitarity_s,1,2,1,2,4,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,5) = a0_G0Hp_H0Hpc_00(unitarity_s,1,2,1,1,4,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,6) = a0_G0Hp_H0Hpc_00(unitarity_s,1,2,1,2,4,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,7) = a0_G0Hp_hhHpc_00(unitarity_s,1,2,1,1,4,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(4,8) = a0_G0Hp_hhHpc_00(unitarity_s,1,2,1,2,4,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,1) = a0_H0Hp_A0Hpc_00(unitarity_s,1,1,1,1,5,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,2) = a0_H0Hp_A0Hpc_00(unitarity_s,1,1,1,2,5,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,3) = a0_H0Hp_G0Hpc_00(unitarity_s,1,1,1,1,5,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,4) = a0_H0Hp_G0Hpc_00(unitarity_s,1,1,1,2,5,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,5) = a0_H0Hp_H0Hpc_00(unitarity_s,1,1,1,1,5,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,6) = a0_H0Hp_H0Hpc_00(unitarity_s,1,1,1,2,5,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,7) = a0_H0Hp_hhHpc_00(unitarity_s,1,1,1,1,5,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(5,8) = a0_H0Hp_hhHpc_00(unitarity_s,1,1,1,2,5,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,1) = a0_H0Hp_A0Hpc_00(unitarity_s,1,2,1,1,6,1) 
scatter_matrix2(6,2) = a0_H0Hp_A0Hpc_00(unitarity_s,1,2,1,2,6,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,3) = a0_H0Hp_G0Hpc_00(unitarity_s,1,2,1,1,6,3) 
scatter_matrix2(6,4) = a0_H0Hp_G0Hpc_00(unitarity_s,1,2,1,2,6,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,5) = a0_H0Hp_H0Hpc_00(unitarity_s,1,2,1,1,6,5) 
scatter_matrix2(6,6) = a0_H0Hp_H0Hpc_00(unitarity_s,1,2,1,2,6,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(6,7) = a0_H0Hp_hhHpc_00(unitarity_s,1,2,1,1,6,7) 
scatter_matrix2(6,8) = a0_H0Hp_hhHpc_00(unitarity_s,1,2,1,2,6,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,1) = a0_hhHp_A0Hpc_00(unitarity_s,1,1,1,1,7,1) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,2) = a0_hhHp_A0Hpc_00(unitarity_s,1,1,1,2,7,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,3) = a0_hhHp_G0Hpc_00(unitarity_s,1,1,1,1,7,3) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,4) = a0_hhHp_G0Hpc_00(unitarity_s,1,1,1,2,7,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,5) = a0_hhHp_H0Hpc_00(unitarity_s,1,1,1,1,7,5) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,6) = a0_hhHp_H0Hpc_00(unitarity_s,1,1,1,2,7,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,7) = a0_hhHp_hhHpc_00(unitarity_s,1,1,1,1,7,7) 
If (IncludeGoldstoneExternal) scatter_matrix2(7,8) = a0_hhHp_hhHpc_00(unitarity_s,1,1,1,2,7,8) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,1) = a0_hhHp_A0Hpc_00(unitarity_s,1,2,1,1,8,1) 
scatter_matrix2(8,2) = a0_hhHp_A0Hpc_00(unitarity_s,1,2,1,2,8,2) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,3) = a0_hhHp_G0Hpc_00(unitarity_s,1,2,1,1,8,3) 
scatter_matrix2(8,4) = a0_hhHp_G0Hpc_00(unitarity_s,1,2,1,2,8,4) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,5) = a0_hhHp_H0Hpc_00(unitarity_s,1,2,1,1,8,5) 
scatter_matrix2(8,6) = a0_hhHp_H0Hpc_00(unitarity_s,1,2,1,2,8,6) 
If (IncludeGoldstoneExternal) scatter_matrix2(8,7) = a0_hhHp_hhHpc_00(unitarity_s,1,2,1,1,8,7) 
scatter_matrix2(8,8) = a0_hhHp_hhHpc_00(unitarity_s,1,2,1,2,8,8) 


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
If (IncludeGoldstoneExternal) scatter_matrix3(1,1) = a0_HpHp_HpcHpc_00(unitarity_s,1,1,1,1,1,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(1,2) = a0_HpHp_HpcHpc_00(unitarity_s,1,1,1,2,1,2) 
If (IncludeGoldstoneExternal) scatter_matrix3(1,3) = a0_HpHp_HpcHpc_00(unitarity_s,1,1,2,2,1,3) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,1) = a0_HpHp_HpcHpc_00(unitarity_s,1,2,1,1,2,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,2) = a0_HpHp_HpcHpc_00(unitarity_s,1,2,1,2,2,2) 
If (IncludeGoldstoneExternal) scatter_matrix3(2,3) = a0_HpHp_HpcHpc_00(unitarity_s,1,2,2,2,2,3) 
If (IncludeGoldstoneExternal) scatter_matrix3(3,1) = a0_HpHp_HpcHpc_00(unitarity_s,2,2,1,1,3,1) 
If (IncludeGoldstoneExternal) scatter_matrix3(3,2) = a0_HpHp_HpcHpc_00(unitarity_s,2,2,1,2,3,2) 
scatter_matrix3(3,3) = a0_HpHp_HpcHpc_00(unitarity_s,2,2,2,2,3,3) 


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

Complex(dp) Function a0_A0A0_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0A0A0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0A0_A0A0_00

Complex(dp) Function a0_A0A0_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0A0_A0G0_00

Complex(dp) Function a0_A0A0_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0A0_A0H0_00

Complex(dp) Function a0_A0A0_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0A0_A0hh_00

Complex(dp) Function a0_A0A0_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0G0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0A0_G0G0_00

Complex(dp) Function a0_A0A0_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0A0_G0H0_00

Complex(dp) Function a0_A0A0_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0A0_G0hh_00

Complex(dp) Function a0_A0A0_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0A0_H0H0_00

Complex(dp) Function a0_A0A0_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0A0_H0hh_00

Complex(dp) Function a0_A0A0_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0A0_hhhh_00

Complex(dp) Function a0_A0A0_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MA0
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0HpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplhhHpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i3,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplA0HpcHp(iprop,i4)
unicpl2(1)=cplA0HpcHp(i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0A0_HpHpc_00

Complex(dp) Function a0_A0G0_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_A0A0_00

Complex(dp) Function a0_A0G0_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0G0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0G0_A0G0_00

Complex(dp) Function a0_A0G0_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_A0H0_00

Complex(dp) Function a0_A0G0_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0G0_A0hh_00

Complex(dp) Function a0_A0G0_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_G0G0_00

Complex(dp) Function a0_A0G0_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0G0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0G0_G0H0_00

Complex(dp) Function a0_A0G0_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_G0hh_00

Complex(dp) Function a0_A0G0_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_H0H0_00

Complex(dp) Function a0_A0G0_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0G0_H0hh_00

Complex(dp) Function a0_A0G0_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_hhhh_00

Complex(dp) Function a0_A0G0_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MG0
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0HpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
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
End Function a0_A0G0_HpHpc_00

Complex(dp) Function a0_A0H0_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0H0_A0A0_00

Complex(dp) Function a0_A0H0_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0H0_A0G0_00

Complex(dp) Function a0_A0H0_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0H0_A0H0_00

Complex(dp) Function a0_A0H0_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0H0_A0hh_00

Complex(dp) Function a0_A0H0_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0G0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0H0_G0G0_00

Complex(dp) Function a0_A0H0_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0H0_G0H0_00

Complex(dp) Function a0_A0H0_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0H0_G0hh_00

Complex(dp) Function a0_A0H0_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_A0H0_H0H0_00

Complex(dp) Function a0_A0H0_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0H0_H0hh_00

Complex(dp) Function a0_A0H0_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0H0_hhhh_00

Complex(dp) Function a0_A0H0_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MH0
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhHpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i3,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplA0HpcHp(iprop,i4)
unicpl2(1)=cplH0HpcHp(i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0H0_HpHpc_00

Complex(dp) Function a0_A0hh_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0hh_A0A0_00

Complex(dp) Function a0_A0hh_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0hh_A0G0_00

Complex(dp) Function a0_A0hh_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0hh_A0H0_00

Complex(dp) Function a0_A0hh_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0hh_A0hh_00

Complex(dp) Function a0_A0hh_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0hh_G0G0_00

Complex(dp) Function a0_A0hh_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_A0hh_G0H0_00

Complex(dp) Function a0_A0hh_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0hh_G0hh_00

Complex(dp) Function a0_A0hh_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0hh_H0H0_00

Complex(dp) Function a0_A0hh_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_A0hh_H0hh_00

Complex(dp) Function a0_A0hh_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_A0hh_hhhh_00

Complex(dp) Function a0_A0hh_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = Mhh
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0hhHpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i3,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplA0HpcHp(iprop,i4)
unicpl2(1)=cplhhHpcHp(i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0hh_HpHpc_00

Complex(dp) Function a0_A0Hp_A0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i2,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplA0HpcHp(iprop,i4)
unicpl2(1)=cplA0HpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0Hp_A0Hpc_00

Complex(dp) Function a0_A0Hp_G0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_A0Hp_G0Hpc_00

Complex(dp) Function a0_A0Hp_H0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i2,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplA0HpcHp(iprop,i4)
unicpl2(1)=cplH0HpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0Hp_H0Hpc_00

Complex(dp) Function a0_A0Hp_hhHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0hhHpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i2,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplA0HpcHp(iprop,i4)
unicpl2(1)=cplhhHpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0Hp_hhHpc_00

Complex(dp) Function a0_A0Hpc_A0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(iprop,i2)
unicpl2(1)=cplA0HpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplA0HpcHp(i4,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0Hpc_A0Hp_00

Complex(dp) Function a0_A0Hpc_G0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_A0Hpc_G0Hp_00

Complex(dp) Function a0_A0Hpc_H0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(iprop,i2)
unicpl2(1)=cplH0HpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplA0HpcHp(i4,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0Hpc_H0Hp_00

Complex(dp) Function a0_A0Hpc_hhHp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MA0
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0hhHpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(iprop,i2)
unicpl2(1)=cplhhHpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplA0HpcHp(i4,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_A0Hpc_hhHp_00

Complex(dp) Function a0_G0G0_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0G0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0G0_A0A0_00

Complex(dp) Function a0_G0G0_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0G0_A0G0_00

Complex(dp) Function a0_G0G0_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0G0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0G0_A0H0_00

Complex(dp) Function a0_G0G0_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0G0_A0hh_00

Complex(dp) Function a0_G0G0_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0G0G0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_G0G0_G0G0_00

Complex(dp) Function a0_G0G0_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0G0_G0H0_00

Complex(dp) Function a0_G0G0_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0G0_G0hh_00

Complex(dp) Function a0_G0G0_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0G0_H0H0_00

Complex(dp) Function a0_G0G0_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0G0_H0hh_00

Complex(dp) Function a0_G0G0_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_G0G0_hhhh_00

Complex(dp) Function a0_G0G0_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MG0
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0HpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplhhHpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
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
End Function a0_G0G0_HpHpc_00

Complex(dp) Function a0_G0H0_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_A0A0_00

Complex(dp) Function a0_G0H0_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0G0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_G0H0_A0G0_00

Complex(dp) Function a0_G0H0_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_A0H0_00

Complex(dp) Function a0_G0H0_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_G0H0_A0hh_00

Complex(dp) Function a0_G0H0_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_G0G0_00

Complex(dp) Function a0_G0H0_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0H0_G0H0_00

Complex(dp) Function a0_G0H0_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_G0hh_00

Complex(dp) Function a0_G0H0_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_H0H0_00

Complex(dp) Function a0_G0H0_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_G0H0_H0hh_00

Complex(dp) Function a0_G0H0_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_hhhh_00

Complex(dp) Function a0_G0H0_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MH0
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0HpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
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
End Function a0_G0H0_HpHpc_00

Complex(dp) Function a0_G0hh_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0G0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0hh_A0A0_00

Complex(dp) Function a0_G0hh_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_A0G0_00

Complex(dp) Function a0_G0hh_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0hh_A0H0_00

Complex(dp) Function a0_G0hh_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_A0hh_00

Complex(dp) Function a0_G0hh_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_G0G0_00

Complex(dp) Function a0_G0hh_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_G0H0_00

Complex(dp) Function a0_G0hh_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_G0hh_G0hh_00

Complex(dp) Function a0_G0hh_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_G0hh_H0H0_00

Complex(dp) Function a0_G0hh_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_H0hh_00

Complex(dp) Function a0_G0hh_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_hhhh_00

Complex(dp) Function a0_G0hh_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = Mhh
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0hh_HpHpc_00

Complex(dp) Function a0_G0Hp_A0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_G0Hp_A0Hpc_00

Complex(dp) Function a0_G0Hp_G0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
End Function a0_G0Hp_G0Hpc_00

Complex(dp) Function a0_G0Hp_H0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_G0Hp_H0Hpc_00

Complex(dp) Function a0_G0Hp_hhHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0Hp_hhHpc_00

Complex(dp) Function a0_G0Hpc_A0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0G0
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_G0Hpc_A0Hp_00

Complex(dp) Function a0_G0Hpc_G0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
End Function a0_G0Hpc_G0Hp_00

Complex(dp) Function a0_G0Hpc_H0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_G0Hpc_H0Hp_00

Complex(dp) Function a0_G0Hpc_hhHp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MG0
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_G0Hpc_hhHp_00

Complex(dp) Function a0_H0H0_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_H0H0_A0A0_00

Complex(dp) Function a0_H0H0_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0H0_A0G0_00

Complex(dp) Function a0_H0H0_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_H0H0_A0H0_00

Complex(dp) Function a0_H0H0_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0H0_A0hh_00

Complex(dp) Function a0_H0H0_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_H0H0_G0G0_00

Complex(dp) Function a0_H0H0_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0H0_G0H0_00

Complex(dp) Function a0_H0H0_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_H0H0_G0hh_00

Complex(dp) Function a0_H0H0_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0H0H0
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MG0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_H0H0_H0H0_00

Complex(dp) Function a0_H0H0_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0H0_H0hh_00

Complex(dp) Function a0_H0H0_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_H0H0_hhhh_00

Complex(dp) Function a0_H0H0_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MH0
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0HpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplhhHpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i3,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplH0HpcHp(iprop,i4)
unicpl2(1)=cplH0HpcHp(i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0H0_HpHpc_00

Complex(dp) Function a0_H0hh_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0hh_A0A0_00

Complex(dp) Function a0_H0hh_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_H0hh_A0G0_00

Complex(dp) Function a0_H0hh_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0hh_A0H0_00

Complex(dp) Function a0_H0hh_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_H0hh_A0hh_00

Complex(dp) Function a0_H0hh_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0hh_G0G0_00

Complex(dp) Function a0_H0hh_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0H0hh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_H0hh_G0H0_00

Complex(dp) Function a0_H0hh_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0hh_G0hh_00

Complex(dp) Function a0_H0hh_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0hh_H0H0_00

Complex(dp) Function a0_H0hh_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_H0hh_H0hh_00

Complex(dp) Function a0_H0hh_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_H0hh_hhhh_00

Complex(dp) Function a0_H0hh_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = Mhh
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0hhHpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i3,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplH0HpcHp(iprop,i4)
unicpl2(1)=cplhhHpcHp(i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0hh_HpHpc_00

Complex(dp) Function a0_H0Hp_A0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i2,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplH0HpcHp(iprop,i4)
unicpl2(1)=cplA0HpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0Hp_A0Hpc_00

Complex(dp) Function a0_H0Hp_G0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_H0Hp_G0Hpc_00

Complex(dp) Function a0_H0Hp_H0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0HpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i2,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplH0HpcHp(iprop,i4)
unicpl2(1)=cplH0HpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0Hp_H0Hpc_00

Complex(dp) Function a0_H0Hp_hhHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0hhHpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i2,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplH0HpcHp(iprop,i4)
unicpl2(1)=cplhhHpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0Hp_hhHpc_00

Complex(dp) Function a0_H0Hpc_A0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(iprop,i2)
unicpl2(1)=cplA0HpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplH0HpcHp(i4,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0Hpc_A0Hp_00

Complex(dp) Function a0_H0Hpc_G0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0G0H0
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplG0H0H0
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
End Function a0_H0Hpc_G0Hp_00

Complex(dp) Function a0_H0Hpc_H0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0HpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(iprop,i2)
unicpl2(1)=cplH0HpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplH0HpcHp(i4,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0Hpc_H0Hp_00

Complex(dp) Function a0_H0Hpc_hhHp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MH0
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0hhHpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(iprop,i2)
unicpl2(1)=cplhhHpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplH0HpcHp(i4,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_H0Hpc_hhHp_00

Complex(dp) Function a0_hhhh_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_hhhh_A0A0_00

Complex(dp) Function a0_hhhh_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhhh_A0G0_00

Complex(dp) Function a0_hhhh_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_hhhh_A0H0_00

Complex(dp) Function a0_hhhh_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhhh_A0hh_00

Complex(dp) Function a0_hhhh_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MG0  
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
Do iprop=istart,1
unicpl1(1)=cplG0G0hh
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MG0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MG0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MG0  
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
End Function a0_hhhh_G0G0_00

Complex(dp) Function a0_hhhh_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhhh_G0H0_00

Complex(dp) Function a0_hhhh_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhhh_G0hh_00

Complex(dp) Function a0_hhhh_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0hhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
End Function a0_hhhh_H0H0_00

Complex(dp) Function a0_hhhh_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhhh_H0hh_00

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
m1 = Mhh
m2 = Mhh
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhhhhh
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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

Complex(dp) Function a0_hhhh_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = Mhh
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHpcHp(i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplhhHpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(i3,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplhhHpcHp(iprop,i4)
unicpl2(1)=cplhhHpcHp(i3,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhhh_HpHpc_00

Complex(dp) Function a0_hhHp_A0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0hhHpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(i2,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplhhHpcHp(iprop,i4)
unicpl2(1)=cplA0HpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhHp_A0Hpc_00

Complex(dp) Function a0_hhHp_G0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhHp_G0Hpc_00

Complex(dp) Function a0_hhHp_H0Hpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0hhHpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(i2,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplhhHpcHp(iprop,i4)
unicpl2(1)=cplH0HpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhHp_H0Hpc_00

Complex(dp) Function a0_hhHp_hhHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHpcHp(i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(i2,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplhhHpcHp(iprop,i4)
unicpl2(1)=cplhhHpcHp(i2,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhHp_hhHpc_00

Complex(dp) Function a0_hhHpc_A0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = MA0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0hhHpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(iprop,i2)
unicpl2(1)=cplA0HpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0A0hh
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplhhHpcHp(i4,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhHpc_A0Hp_00

Complex(dp) Function a0_hhHpc_G0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = MG0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_hhHpc_G0Hp_00

Complex(dp) Function a0_hhHpc_H0Hp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = MH0
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0hhHpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(iprop,i2)
unicpl2(1)=cplH0HpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0H0hh
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0H0hh
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
unicpl1(1)=cplhhHpcHp(i4,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhHpc_H0Hp_00

Complex(dp) Function a0_hhHpc_hhHp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = Mhh
m2 = MHp(i2)
m3 = Mhh
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHpcHp(i4,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(iprop,i2)
unicpl2(1)=cplhhHpcHp(i4,iprop)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MHp(iProp)**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhhhhh
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
unicpl1(1)=cplhhHpcHp(i4,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_hhHpc_hhHp_00

Complex(dp) Function a0_HpHp_HpcHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplHpHpcHpcHp(i1,i2,i3,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i3)
unicpl2(1)=cplA0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i3)
unicpl2(1)=cplH0HpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i3)
unicpl2(1)=cplhhHpcHp(i2,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i4)
unicpl2(1)=cplA0HpcHp(i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i4)
unicpl2(1)=cplH0HpcHp(i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i4)
unicpl2(1)=cplhhHpcHp(i2,i3)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_HpHp_HpcHpc_00

Complex(dp) Function a0_HpHpc_A0A0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MA0
m4 = MA0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0A0HpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i2)
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i1,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplA0HpcHp(i1,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_HpHpc_A0A0_00

Complex(dp) Function a0_HpHpc_A0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MA0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0G0HpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i2)
unicpl2(1)=cplA0A0G0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i2)
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
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
End Function a0_HpHpc_A0G0_00

Complex(dp) Function a0_HpHpc_A0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MA0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i2)
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i1,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplH0HpcHp(i1,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_HpHpc_A0H0_00

Complex(dp) Function a0_HpHpc_A0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MA0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplA0hhHpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i2)
unicpl2(1)=cplA0A0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i2)
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplA0HpcHp(i1,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplhhHpcHp(i1,iprop)
unicpl2(1)=cplA0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_HpHpc_A0hh_00

Complex(dp) Function a0_HpHpc_G0G0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MG0
m4 = MG0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0G0HpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i2)
unicpl2(1)=cplG0G0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
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
End Function a0_HpHpc_G0G0_00

Complex(dp) Function a0_HpHpc_G0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MG0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplG0H0HpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i2)
unicpl2(1)=cplA0G0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i2)
unicpl2(1)=cplG0H0H0
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
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
End Function a0_HpHpc_G0H0_00

Complex(dp) Function a0_HpHpc_G0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MG0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 


! S-Channel 


! T-Channel 


! U-Channel 
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
End Function a0_HpHpc_G0hh_00

Complex(dp) Function a0_HpHpc_H0H0_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MH0
m4 = MH0
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0H0HpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i2)
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i1,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplH0HpcHp(i1,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_HpHpc_H0H0_00

Complex(dp) Function a0_HpHpc_H0hh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MH0
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplH0hhHpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i2)
unicpl2(1)=cplA0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i2)
unicpl2(1)=cplH0H0hh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplH0HpcHp(i1,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplhhHpcHp(i1,iprop)
unicpl2(1)=cplH0HpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_HpHpc_H0hh_00

Complex(dp) Function a0_HpHpc_hhhh_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = Mhh
m4 = Mhh
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplhhhhHpcHp(i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i2)
unicpl2(1)=cplhhhhhh
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 
istart=1
If (.not.IncludeGoldstoneContributions) istart=2
Do iprop=istart,2
unicpl1(1)=cplhhHpcHp(i1,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MHp(iProp)  
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
unicpl1(1)=cplhhHpcHp(i1,iprop)
unicpl2(1)=cplhhHpcHp(iprop,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MHp(iProp),s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MHp(iProp)**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MHp(iProp)  
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
End Function a0_HpHpc_hhhh_00

Complex(dp) Function a0_HpHpc_HpHpc_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplHpHpcHpcHp(i1,i3,i2,i4)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i2)
unicpl2(1)=cplA0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MA0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i2)
unicpl2(1)=cplH0HpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/MH0**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 
istart=1
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i2)
unicpl2(1)=cplhhHpcHp(i3,i4)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Schannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If (Abs(1-s/Mhh**2).lt.CutSpole) Then 
 Pole_Present = .true. 
Else 
  amp = amp + tempamp2(1,1)
End if 
End Do 


! T-Channel 


! U-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i1,i4)
unicpl2(1)=cplA0HpcHp(i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i1,i4)
unicpl2(1)=cplH0HpcHp(i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i1,i4)
unicpl2(1)=cplhhHpcHp(i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_HpHpc_HpHpc_00

Complex(dp) Function a0_HpcHpc_HpHp_00(s,i1,i2,i3,i4,ind1,ind2)  Result(amp)
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
m1 = MHp(i1)
m2 = MHp(i2)
m3 = MHp(i3)
m4 = MHp(i4)
If ((s.gt.1.01_dp*(m3+m4)**2).and.(s.gt.1.01_dp*(m1+m2)**2)) Then 


! Quartic 
unicpl1(1)=cplHpHpcHpcHp(i3,i4,i1,i2)
amp = amp +(-2._dp)*(unicpl1(1))


! S-Channel 


! T-Channel 
istart=1
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i3,i1)
unicpl2(1)=cplA0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i3,i1)
unicpl2(1)=cplH0HpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i3,i1)
unicpl2(1)=cplhhHpcHp(i4,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Tchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckTpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "T",m1,m2,m3,m4,Mhh  
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
Do iprop=istart,1
unicpl1(1)=cplA0HpcHp(i4,i1)
unicpl2(1)=cplA0HpcHp(i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MA0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MA0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MA0  
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
Do iprop=istart,1
unicpl1(1)=cplH0HpcHp(i4,i1)
unicpl2(1)=cplH0HpcHp(i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,MH0,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,MH0**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,MH0  
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
Do iprop=istart,1
unicpl1(1)=cplhhHpcHp(i4,i1)
unicpl2(1)=cplhhHpcHp(i3,i2)
tempamp2(1,1)= unicpl1(1)*unicpl2(1)*Uchannel(m1,m2,m3,m4,Mhh,s,(1._dp,0._dp),(1._dp,0._dp)) 
If  (((s.lt.(CheckUpole(m1**2,m2**2,m3**2,m4**2,Mhh**2)))).and.(maxval(Abs(tempamp2)).gt.1.0E-10_dp)) Then 
! Write(*,*) "U",m1,m2,m3,m4,Mhh  
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
End Function a0_HpcHpc_HpHp_00

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
  
End Module Unitarity_Inert 
