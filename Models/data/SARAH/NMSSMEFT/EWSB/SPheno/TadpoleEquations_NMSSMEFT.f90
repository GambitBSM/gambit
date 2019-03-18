! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.13.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 14:02 on 29.10.2018   
! ----------------------------------------------------------------------  
 
 
Module Tadpoles_NMSSMEFT 
 
Use Model_Data_NMSSMEFT 
Use TreeLevelMasses_NMSSMEFT 
Use RGEs_NMSSMEFT 
Use Control 
Use Settings 
Use Mathematics 

Contains 


Subroutine SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,             & 
& Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,Tad1Loop)

Implicit None
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,ms2,vd,vu,vS

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp), Intent(in) :: Tad1Loop(3)

! For numerical routines 
Real(dp) :: gC(221)
logical :: broycheck 
Real(dp) :: broyx(3)

If (HighScaleModel.Eq."LOW") Then 
mHd2 = (-(g1**2*vd**3) - g2**2*vd**3 + g1**2*vd*vu**2 + g2**2*vd*vu**2 + 2*vS**2*vu*lam*Conjg(kap) +& 
&  2*(-2*vd*vu**2*lam + vS**2*(vu*kap - 2*vd*lam))*Conjg(lam) + 2*sqrt(2._dp)*vS*vu*Conjg(Tlam) +& 
&  2*sqrt(2._dp)*vS*vu*Tlam + 8*Tad1Loop(1))/(8._dp*vd)
mHu2 = (g1**2*vd**2*vu + g2**2*vd**2*vu - g1**2*vu**3 - g2**2*vu**3 + 2*vd*vS**2*lam*Conjg(kap) +& 
&  (2*vd*vS**2*kap - 4*vd**2*vu*lam - 4*vS**2*vu*lam)*Conjg(lam) + 2*sqrt(2._dp)*vd*vS*Conjg(Tlam) +& 
&  2*sqrt(2._dp)*vd*vS*Tlam + 8*Tad1Loop(2))/(8._dp*vu)
ms2 = ((-4*vS**3*kap + 2*vd*vS*vu*lam)*Conjg(kap) - 2*vS*(-(vd*vu*kap) + vd**2*lam +        & 
&  vu**2*lam)*Conjg(lam) - sqrt(2._dp)*vS**2*Conjg(Tk) + sqrt(2._dp)*vd*vu*Conjg(Tlam) - & 
&  sqrt(2._dp)*vS**2*Tk + sqrt(2._dp)*vd*vu*Tlam + 4*Tad1Loop(3))/(4._dp*vS)

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (mHd2.ne.mHd2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for mHd2" 
   Call TerminateProgram  
 End If 
 If (mHu2.ne.mHu2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for mHu2" 
   Call TerminateProgram  
 End If 
 If (ms2.ne.ms2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for ms2" 
   Call TerminateProgram  
 End If 
 Else 
mHd2 = (-(g1**2*vd**3) - g2**2*vd**3 + g1**2*vd*vu**2 + g2**2*vd*vu**2 + 2*vS**2*vu*lam*Conjg(kap) +& 
&  2*(-2*vd*vu**2*lam + vS**2*(vu*kap - 2*vd*lam))*Conjg(lam) + 2*sqrt(2._dp)*vS*vu*Conjg(Tlam) +& 
&  2*sqrt(2._dp)*vS*vu*Tlam + 8*Tad1Loop(1))/(8._dp*vd)
mHu2 = (g1**2*vd**2*vu + g2**2*vd**2*vu - g1**2*vu**3 - g2**2*vu**3 + 2*vd*vS**2*lam*Conjg(kap) +& 
&  (2*vd*vS**2*kap - 4*vd**2*vu*lam - 4*vS**2*vu*lam)*Conjg(lam) + 2*sqrt(2._dp)*vd*vS*Conjg(Tlam) +& 
&  2*sqrt(2._dp)*vd*vS*Tlam + 8*Tad1Loop(2))/(8._dp*vu)
ms2 = ((-4*vS**3*kap + 2*vd*vS*vu*lam)*Conjg(kap) - 2*vS*(-(vd*vu*kap) + vd**2*lam +        & 
&  vu**2*lam)*Conjg(lam) - sqrt(2._dp)*vS**2*Conjg(Tk) + sqrt(2._dp)*vd*vu*Conjg(Tlam) - & 
&  sqrt(2._dp)*vS**2*Tk + sqrt(2._dp)*vd*vu*Tlam + 4*Tad1Loop(3))/(4._dp*vS)

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (mHd2.ne.mHd2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for mHd2" 
   Call TerminateProgram  
 End If 
 If (mHu2.ne.mHu2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for mHu2" 
   Call TerminateProgram  
 End If 
 If (ms2.ne.ms2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for ms2" 
   Call TerminateProgram  
 End If 
 End if 
End Subroutine SolveTadpoleEquations

Subroutine CalculateTadpoles(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,              & 
& mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,Tad1Loop,TadpoleValues)

Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2,vd,vu,vS

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp), Intent(in) :: Tad1Loop(3)

Real(dp), Intent(out) :: TadpoleValues(3)

TadpoleValues(1) = Real(((g1**2 + g2**2)*vd**3 + vd*(8._dp*(mHd2) - (g1**2 + g2**2)   & 
& *vu**2 + 4*(vS**2 + vu**2)*lam*Conjg(lam)) - 2*vS*vu*(vS*(lam*Conjg(kap)               & 
&  + kap*Conjg(lam)) + sqrt(2._dp)*Conjg(Tlam) + sqrt(2._dp)*Tlam))/8._dp - Tad1Loop(1),dp) 
TadpoleValues(2) = Real((8*mHu2*vu - g1**2*vd**2*vu - g2**2*vd**2*vu + g1**2*vu**3 + g2**2*vu**3 - 2*vd*vS**2*lam*Conjg(kap)& 
&  - 2*vd*vS**2*kap*Conjg(lam) + 4*vd**2*vu*lam*Conjg(lam) + 4*vS**2*vu*lam*Conjg(lam)   & 
&  - 2*sqrt(2._dp)*vd*vS*Conjg(Tlam) - 2*sqrt(2._dp)*vd*vS*Tlam)/8._dp - Tad1Loop(2),dp) 
TadpoleValues(3) = Real((4*vS**3*kap*Conjg(kap) + 2*vS*(2._dp*(ms2) - vd*vu*lam*Conjg(kap)& 
&  + (-(vd*vu*kap) + vd**2*lam + vu**2*lam)*Conjg(lam)) + sqrt(2._dp)*vS**2*(Conjg(Tk)   & 
&  + Tk) - sqrt(2._dp)*vd*vu*(Conjg(Tlam) + Tlam))/4._dp - Tad1Loop(3),dp) 
End Subroutine CalculateTadpoles 

End Module Tadpoles_NMSSMEFT 
 
