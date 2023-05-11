! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:54 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Tadpoles_Inert2 
 
Use Model_Data_Inert2 
Use TreeLevelMasses_Inert2 
Use RGEs_Inert2 
Use Control 
Use Settings 
Use Mathematics 

Contains 


Subroutine SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,             & 
& Yu,MHD2,MHU2,v,Tad1Loop)

Implicit None
Real(dp),Intent(inout) :: g1,g2,g3,MHD2,MHU2,v

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Complex(dp), Intent(in) :: Tad1Loop(2)

! For numerical routines 
Real(dp) :: gC(70)
logical :: broycheck 
Real(dp) :: broyx(1)

If (HighScaleModel.Eq."LOW") Then 
MHD2 = -(lam1*v**2)/2._dp + Tad1Loop(1)/v

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (MHD2.ne.MHD2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for MHD2" 
   Call TerminateProgram  
 End If 
 Else 
MHD2 = -(lam1*v**2)/2._dp + Tad1Loop(1)/v

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (MHD2.ne.MHD2) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for MHD2" 
   Call TerminateProgram  
 End If 
 End if 
End Subroutine SolveTadpoleEquations

Subroutine CalculateTadpoles(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,              & 
& MHD2,MHU2,v,Tad1Loop,TadpoleValues)

Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Complex(dp), Intent(in) :: Tad1Loop(1)

Real(dp), Intent(out) :: TadpoleValues(1)

TadpoleValues(1) = Real(MHD2*v + (lam1*v**3)/2._dp - Tad1Loop(1),dp) 
End Subroutine CalculateTadpoles 

End Module Tadpoles_Inert2 
 
