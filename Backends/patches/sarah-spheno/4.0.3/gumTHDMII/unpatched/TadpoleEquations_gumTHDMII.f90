! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:28 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Tadpoles_gumTHDMII 
 
Use Model_Data_gumTHDMII 
Use TreeLevelMasses_gumTHDMII 
Use RGEs_gumTHDMII 
Use Control 
Use Settings 
Use Mathematics 

Contains 


Subroutine SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,             & 
& Ye,m122,m112,m222,vd,vu,Tad1Loop)

Implicit None
Real(dp),Intent(inout) :: g1,g2,g3,vd,vu

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Complex(dp), Intent(in) :: Tad1Loop(2)

! For numerical routines 
Real(dp) :: gC(75)
logical :: broycheck 
Real(dp) :: broyx(2)

If (HighScaleModel.Eq."LOW") Then 
m112 = -(2*lam1*vd**3 - 2*m122*vu + 2*lam3*vd*vu**2 + 2*lam4*vd*vu**2 + lam5*vd*vu**2 +      & 
&  vd*vu**2*Conjg(lam5) - 2*vu*Conjg(m122) - 4*Tad1Loop(1))/(4._dp*vd)
m222 = -(-2*m122*vd + 2*lam3*vd**2*vu + 2*lam4*vd**2*vu + lam5*vd**2*vu + 2*lam2*vu**3 +     & 
&  vd**2*vu*Conjg(lam5) - 2*vd*Conjg(m122) - 4*Tad1Loop(2))/(4._dp*vu)

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (Real(m112,dp).ne.Real(m112,dp)) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for m112" 
   Call TerminateProgram  
 End If 
 If (Abs(AImag(m112)).gt.1.0E-04_dp) Then 
   Write(*,*) "No real solution of tadpole equations for m112" 
   !Call TerminateProgram  
   m112 = Real(m112,dp) 
  SignOfMuChanged= .True. 
End If 
 If (Real(m222,dp).ne.Real(m222,dp)) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for m222" 
   Call TerminateProgram  
 End If 
 If (Abs(AImag(m222)).gt.1.0E-04_dp) Then 
   Write(*,*) "No real solution of tadpole equations for m222" 
   !Call TerminateProgram  
   m222 = Real(m222,dp) 
  SignOfMuChanged= .True. 
End If 
 Else 
m112 = -(2*lam1*vd**3 - 2*m122*vu + 2*lam3*vd*vu**2 + 2*lam4*vd*vu**2 + lam5*vd*vu**2 +      & 
&  vd*vu**2*Conjg(lam5) - 2*vu*Conjg(m122) - 4*Tad1Loop(1))/(4._dp*vd)
m222 = -(-2*m122*vd + 2*lam3*vd**2*vu + 2*lam4*vd**2*vu + lam5*vd**2*vu + 2*lam2*vu**3 +     & 
&  vd**2*vu*Conjg(lam5) - 2*vd*Conjg(m122) - 4*Tad1Loop(2))/(4._dp*vu)

 ! ----------- Check solutions for consistency  -------- 

 ! Check for NaNs 
If (Real(m112,dp).ne.Real(m112,dp)) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for m112" 
   Call TerminateProgram  
 End If 
 If (Abs(AImag(m112)).gt.1.0E-04_dp) Then 
   Write(*,*) "No real solution of tadpole equations for m112" 
   !Call TerminateProgram  
   m112 = Real(m112,dp) 
  SignOfMuChanged= .True. 
End If 
 If (Real(m222,dp).ne.Real(m222,dp)) Then 
   Write(*,*) "NaN appearing in solution of tadpole equations for m222" 
   Call TerminateProgram  
 End If 
 If (Abs(AImag(m222)).gt.1.0E-04_dp) Then 
   Write(*,*) "No real solution of tadpole equations for m222" 
   !Call TerminateProgram  
   m222 = Real(m222,dp) 
  SignOfMuChanged= .True. 
End If 
 End if 
End Subroutine SolveTadpoleEquations

Subroutine CalculateTadpoles(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,              & 
& m122,m112,m222,vd,vu,Tad1Loop,TadpoleValues)

Real(dp),Intent(in) :: g1,g2,g3,vd,vu

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Complex(dp), Intent(in) :: Tad1Loop(2)

Real(dp), Intent(out) :: TadpoleValues(2)

TadpoleValues(1) = Real((2*lam1*vd**3 + vd*(4._dp*(m112) + vu**2*(2._dp*(lam3)        & 
&  + 2._dp*(lam4) + lam5 + Conjg(lam5))) - 2*vu*(m122 + Conjg(m122)))/4._dp - Tad1Loop(1),dp) 
TadpoleValues(2) = Real((4*m222*vu + 2*lam2*vu**3 + vd**2*vu*(2._dp*(lam3)            & 
&  + 2._dp*(lam4) + lam5 + Conjg(lam5)) - 2*vd*(m122 + Conjg(m122)))/4._dp - Tad1Loop(2),dp) 
End Subroutine CalculateTadpoles 

End Module Tadpoles_gumTHDMII 
 
