! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:33 on 18.2.2026   
! ----------------------------------------------------------------------  
 
 
Module Tadpoles_Inert 
 
Use Model_Data_Inert 
Use TreeLevelMasses_Inert 
Use RGEs_Inert 
Use Control 
Use Settings 
Use Mathematics 

Contains 


Subroutine SolveTadpoleEquations(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,             & 
& Yu,mHd2,mHu2,v,Tad1Loop)

Implicit None
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,v

Complex(dp),Intent(inout) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Complex(dp), Intent(in) :: Tad1Loop(2)

! For numerical routines 
Real(dp) :: gC(70)
logical :: broycheck 
Real(dp) :: broyx(2)

If (HighScaleModel.Eq."LOW") Then 
mHd2 = (-(Lam1*v**3) + Tad1Loop(1))/v

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (mHd2.ne.mHd2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for mHd2" 
   Call TerminateProgram  
 End If 
 Else 
mHd2 = (-(Lam1*v**3) + Tad1Loop(1))/v

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (mHd2.ne.mHd2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for mHd2" 
   Call TerminateProgram  
 End If 
 End if 
End Subroutine SolveTadpoleEquations

Subroutine CalculateTadpoles(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,              & 
& mHd2,mHu2,v,Tad1Loop,TadpoleValues)

Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,v

Complex(dp),Intent(in) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Complex(dp), Intent(in) :: Tad1Loop(1)

Real(dp), Intent(out) :: TadpoleValues(1)

TadpoleValues(1) = Real(v*(mHd2 + Lam1*v**2) - Tad1Loop(1),dp) 
End Subroutine CalculateTadpoles 

End Module Tadpoles_Inert 
 
