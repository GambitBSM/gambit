Module AddLoopFunctions
Use Control
Use Settings
!Use Mathematics, Only: Li2, CLi2, Delt
!Use LoopFunctions
Use LoopFunctions !, Only: DB0, A0, B0, B1, B00, B11, Cget, Log1minusX, GetRenormalizationScale

! private variables
Real(dp), Private :: mudim2 = 0._dp !, divergence = 0._dp
Real(dp), Private :: xloss = 0.125_dp
! Integer, Private :: divonly = 0 !when set to 1, only UV divergent parts are taken
                                !not for special C routines
Real(dp), Private :: controlmdiff = 1.0e-15_dp !controls the mass difference
                                               !when comparing two masses
Real(dp) :: CCut = 10.e-15_dp

! taken parts from Stefan Liebler

Contains

Logical Function EqualMasses(x,y) 
Implicit None
Real(dp), Intent(in) :: x,y
Real(dp) :: epsD
epsD = 1.0E-20_dp
If ((Max(Abs(x),Abs(y)).lt.epsD)) Then
 EqualMasses = .True.
Else 
 If ((Abs(x-y)/Max(Abs(x),Abs(y))).le.epsD) Then
  EqualMasses = .True.
!   Write(*,*) x,y
 Else
  EqualMasses = .False.
 End if
End if
End Function EqualMasses


Complex(dp) Function C0_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 

! Write(*,*) pp1,pp2,pp3
 
! If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.rp1).and.(m3.eq.rp2)) Then 
If ((EqualMasses(m2,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m1,rp1)).and.(EqualMasses(m3,rp2))) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m3))
! C0_IR = zLog((pp1 + pp2 - pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp1*pp2)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))
C0_IR = getC_IR(pp3,pp1,pp2,Mass_Regulator_PhotonGluon)
Else If ((EqualMasses(m1,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m2,rp1)).and.(EqualMasses(m3,rp3))) Then
! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.rp1).and.(m3.eq.rp3)) Then 
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m2*m3))
! C0_IR = zLog((pp1 - pp2 + pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp1*pp3)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))
C0_IR = getC_IR(pp2,pp1,pp3,Mass_Regulator_PhotonGluon)
! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.rp2).and.(m1.eq.rp3)) Then 
Else If ((EqualMasses(m3,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m1,rp3)).and.(EqualMasses(m2,rp2))) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m2))
! C0_IR = zLog((-pp1 + pp2 + pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp2*pp3)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))
C0_IR = getC_IR(pp1,pp2,pp3,Mass_Regulator_PhotonGluon)
Else  
C0_IR = 0._dp 
End if 

If (Abs(C0_IR).ne.Abs(C0_IR)) Then
Write(*,*) "NaN in C0_IR", rp1,rp2,rp3,m1,m2,m3
C0_IR= 0._dp
End if


End Function C0_IR 

Complex(dp) Function getC_IR(pp1,pp2,pp3,reg)
Complex(dp), Intent(in) :: pp1, pp2, pp3
Real(dp), Intent(in) :: reg
Real(dp) :: epsIR
Complex(dp) :: Creg



If ((Abs((pp2/pp1)).lt.1E-8_dp).and.(Abs((pp3/pp1)).lt.1E-8_dp)) Then
  Creg=cmplx(reg,0._dp,dp) 
!  getC_IR = ((pp1*(pp2 + pp1) + pp3*(4*pp2 + pp1))*zLog(Creg**2)*zLog(-1._dp/pp1))/pp1**3
 epsIR = zlog(Creg**2/(-pp1))
 getC_IR = epsIR/pp1*zlog(zSqrt(pp2*pp3)/(-pp1)) 
!  Write(*,*) "A", pp1, pp2, pp3, getC_IR
else if (Abs((pp2/pp1)).lt.1E-8_dp) Then 
 Creg=cmplx(reg,0._dp,dp) 
 epsIR = zlog(zSqrt(pp2)*(pp3-pp1)/(Creg**2*zSqrt(pp3)))
 getC_IR = 1._dp/(pp1-pp3)*epsIR*zLog((pp3-pp1)/zSqrt(pp2*pp3))
!  Write(*,*) "B", pp1, pp2, pp3, getC_IR
else if (Abs((pp3/pp1)).lt.1E-8_dp) Then 
 Creg=cmplx(reg,0._dp,dp) 
 epsIR = zlog(zSqrt(pp3)*(pp2-pp1)/(Creg**2*zSqrt(pp2)))
 getC_IR = 1._dp/(pp1-pp2)*epsIR*zLog((pp2-pp1)/zSqrt(pp2*pp3))
!  Write(*,*) "C", pp1, pp2, pp3, getC_IR
else 
 epsIR = 1._dp/log(reg**2/sqrt(pp2*pp3))
 getC_IR = zLog((-pp1 + pp2 + pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp2*pp3)))/ &
  & (epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))
!   Write(*,*) "D", pp1, pp2, pp3,getC_IR
end if

If (Abs(getC_IR).ne.Abs(getC_IR)) Then
 getC_IR = ((pp1*(pp2 + pp3) + pp3*(4*pp2 + pp1))*zLog(Creg**2)*zLog(-1._dp/pp1))/pp1**3
End if 

! Write(*,*) pp1,pp2,pp3,reg, getC_IR

End Function getC_IR


Complex(dp) Function C1_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 
 
! If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.rp1).and.(m3.eq.rp2)) Then 
If ((EqualMasses(m2,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m1,rp1)).and.(EqualMasses(m3,rp2))) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m3))
! C1_IR = -(zLog((pp1 + pp2 - pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp1*pp2)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3))))
C1_IR = -getC_IR(pp3,pp1,pp2,Mass_Regulator_PhotonGluon)
Else  
C1_IR = 0._dp 
End if 

If (Abs(C1_IR).ne.Abs(C1_IR)) Then
! Write(*,*) "NaN in C1_IR", rp1,rp2,rp3,m1,m2,m3
C1_IR=0._dp
End if


End Function C1_IR 


Complex(dp) Function C2_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 
 
! If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.rp2).and.(m1.eq.rp3)) Then 
If ((EqualMasses(m3,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m1,rp3)).and.(EqualMasses(m2,rp2))) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m2))
! C2_IR = -(zLog((-pp1 + pp2 + pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp2*pp3)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3))))
C2_IR = -getC_IR(pp1,pp2,pp3,Mass_Regulator_PhotonGluon)
Else  
C2_IR = 0._dp 
End if 

If (Abs(C2_IR).ne.Abs(C2_IR)) Then
! Write(*,*) "NaN in C2_IR", rp1,rp2,rp3,m1,m2,m3
C2_IR=0._dp
End if


End Function C2_IR 


Complex(dp) Function C00_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 
 

C00_IR = 0._dp 

If (Abs(C00_IR).ne.Abs(C00_IR)) Then
! Write(*,*) "NaN in C00_IR", rp1,rp2,rp3,m1,m2,m3
End if


End Function C00_IR 


Complex(dp) Function C11_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 
 
! If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.rp1).and.(m3.eq.rp2)) Then 
If ((EqualMasses(m2,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m1,rp1)).and.(EqualMasses(m3,rp2))) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m3))
! C11_IR = zLog((pp1 + pp2 - pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp1*pp2)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))
C11_IR = getC_IR(pp3,pp1,pp2,Mass_Regulator_PhotonGluon)
Else  
C11_IR = 0._dp 
End if 

If (Abs(C11_IR).ne.Abs(C11_IR)) Then
! Write(*,*) "NaN in C11_IR", rp1,rp2,rp3,m1,m2,m3
C11_IR=0._dp
End if


End Function C11_IR 


Complex(dp) Function C12_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 
 

C12_IR = 0._dp 

If (Abs(C12_IR).ne.Abs(C12_IR)) Then
! Write(*,*) "NaN in C12_IR", rp1,rp2,rp3,m1,m2,m3
C12_IR=0._dp
End if


End Function C12_IR 


Complex(dp) Function C22_IR(rp1,rp2,rp3,m1,m2,m3) 
Implicit None 
Real(dp), Intent(in) :: rp1, rp2, rp3, m1, m2, m3 
Complex(dp) :: pp1, pp2, pp3 
Real(dp) :: epsIR
pp1=cmplx(rp1,0._dp,dp) 
pp2=cmplx(rp2,0._dp,dp) 
pp3=cmplx(rp3,0._dp,dp) 

! If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.rp2).and.(m1.eq.rp3)) Then 
If ((EqualMasses(m3,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(m1,rp3)).and.(EqualMasses(m2,rp2))) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m2))
! C22_IR = zLog((-pp1 + pp2 + pp3 + zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))/(2.*zSqrt(pp2*pp3)))/(epsIR*zSqrt(pp1**2 + (pp2 - pp3)**2 - 2*pp1*(pp2 + pp3)))
C22_IR = getC_IR(pp1,pp2,pp3,Mass_Regulator_PhotonGluon)
Else  
C22_IR = 0._dp 
End if 

If (Abs(C22_IR).ne.Abs(C22_IR)) Then
! Write(*,*) "NaN in C22_IR", rp1,rp2,rp3,m1,m2,m3
C22_IR=0._dp
End if

End Function C22_IR 





! 
! 
! Complex(dp) Function C0_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C0_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C0_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C0_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C0_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C0_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then
! If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m2)) 
!  C0_IR = zLog((-p1 + p2 + p3 + zSqrt(Cmplx(p1**2 + (p2 - p3)**2 - 2._dp*p1*(p2 + p3),0._dp,dp)))/(2._dp*zSqrt(Cmplx(p2*p3,0._dp,dp))))/ &
!  & (epsIR*zSqrt(Cmplx(p1**2 + (p2 - p3)**2 - 2._dp*p1*(p2 + p3),0._dp,dp)))
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C0_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C0_IR = 0
! Else  
! C0_IR = 0._dp 
! End if
! 
! 
! ! if ((Abs(C0_IR)).ne.(Abs(C0_IR)))  Then
! ! Write(*,*) "NaN in C0"
! ! Write(*,*) "input:", p1,p2,p3,m1,m2,m3,epsIR
! ! End if
! 
! ! Write(*,*) "C0", C0_IR
! 
! End Function C0_IR


! 
! 
! Complex(dp) Function C1_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2) 
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C1_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C1_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C1_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C1_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C1_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C1_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C1_IR = 0
! ! Else  
! C1_IR = 0._dp 
! ! End if
! End Function C1_IR 
! 
! 
! Complex(dp) Function C2_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! Complex(dp) :: arg
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2) 
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C2_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C2_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C2_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C2_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C2_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then
! If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m2)) 
!  arg = (-p1 + p2 + p3 + zSqrt(CMPLX(p1**2 + (p2 - p3)**2 - 2._dp*p1*(p2 + p3),0._dp,dp)))/(2._dp*zSqrt(CMPLX(p2*p3,0._dp,dp)))
!  C2_IR = -(zLog(arg)/(epsIR*zSqrt(CMPLX(p1**2 + (p2 - p3)**2 - 2._dp*p1*(p2 + p3),0._dp,dp))))
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C2_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C2_IR = 0
! Else  
! C2_IR = 0._dp 
! End if
! 
! ! if ((Abs(C2_IR)).ne.(Abs(C2_IR)))  Then
! ! Write(*,*) "NaN in C2"
! ! Write(*,*) "input:", p1,p2,p3,m1,m2,m3,epsIR
! ! Write(*,*) "arg, Log(arg)", arg, zLog(arg)
! ! Write(*,*) "part I, II", (-p1 + p2 + p3 + zSqrt(CMPLX(p1**2 + (p2 - p3)**2 - 2._dp*p1*(p2 + p3),0._dp,dp))), (2._dp*zSqrt(CMPLX(p2*p3,0._dp,dp)))
! ! End if
! 
! End Function C2_IR 
! 
! 
! Complex(dp) Function C00_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2) 
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C00_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C00_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C00_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C00_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C00_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C00_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C00_IR = 0
! ! Else  
! C00_IR = 0._dp 
! ! End if
! End Function C00_IR 
! 
! 
! Complex(dp) Function C11_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2) 
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C11_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C11_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C11_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C11_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C11_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C11_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C11_IR = 0
! ! Else  
! C11_IR = 0._dp 
! ! End if
! End Function C11_IR 
! 
! 
! Complex(dp) Function C12_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2) 
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C12_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C12_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C12_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C12_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C12_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C12_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C12_IR = 0
! ! Else  
! C12_IR = 0._dp 
! ! End if
! End Function C12_IR 
! 
! 
! Complex(dp) Function C22_IR(p1,p2,p3,m1,m2,m3) 
! Implicit None 
! Real(dp), Intent(in) :: p1, p2, p3, m1, m2, m3 
! Real(dp) :: epsIR
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2) 
! ! If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m3.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p2)) Then 
! ! C22_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m2.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m2.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p1).and.(m3.eq.p2)) Then 
! ! C22_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m3.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p2)) Then 
! ! C22_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m1.eq.p2).and.(m2.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p2)) Then 
! ! C22_IR = 0
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p2).and.(m1.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m1.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p1).and.(m3.eq.p2)) Then 
! ! C22_IR = 0
! ! Else If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then 
! If ((m3.eq.Mass_Regulator_PhotonGluon**2).and.(m2.eq.p2).and.(m1.eq.p3)) Then
! epsIR = 1._dp/log(Mass_Regulator_PhotonGluon**2/sqrt(m1*m2)) 
!  C22_IR = zLog(((-p1 + p2 + p3 + zSqrt(Cmplx(p1**2 + (p2 - p3)**2 - 2*p1*(p2 + p3),0._dp,dp)))/ &
!  & (2._dp*zSqrt(Cmplx(p2*p3,0._dp,dp)))))/(epsIR*zSqrt(Cmplx(p1**2 + (p2 - p3)**2 - 2*p1*(p2 + p3),0._dp,dp)))
! ! Else If ((m2.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m1.eq.p3)) Then 
! ! C22_IR = 0
! ! Else If ((m1.eq.Mass_Regulator_PhotonGluon**2).and.(m3.eq.p1).and.(m2.eq.p2)) Then 
! ! C22_IR = 0
! Else  
! C22_IR = 0._dp 
! End if
! 
! 
! ! if ((Abs(C22_IR)).ne.(Abs(C22_IR))) Then
! ! Write(*,*) "NaN in C22"
! ! Write(*,*) "input:", p1,p2,p3,m1,m2,m3,epsIR
! ! End if
! 
! End Function C22_IR 




Complex(dp) Function SA_B0(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2

! FS: changed 15/07/2017
    If ((xm1.eq.0._dp).and.(xm2.eq.0._dp).and.(xp.eq.0._dp)) Then 
      SA_B0=0._dp ! to prevent numerical problems.
      Return
    End if
!    

  
  If (divonly.Eq.1) Then
   If (IRdivonly) Then 
    SA_B0 = 0._dp
   Else
    SA_B0 = divergence
   End if 
   Return 
  End If
  
  If (IRdivonly) Then 
   SA_B0 = 0._dp
   Return
  End if
 

  SA_B0 = B0(xp,xm1,xm2)

End Function SA_B0

Complex(dp) Function SA_A0(m)
 Implicit None
  Real(dp), Intent(in) :: m

  If (divonly.Eq.1) Then
   If (IRdivonly) Then 
    SA_A0 = 0._dp
   Else
    SA_A0 = m*divergence
   End if
   Return
  End If
  
  If (IRdivonly) Then 
   SA_A0 = 0._dp
   Return
  End if  

  SA_A0 = A0(m)

End Function SA_A0

Complex(dp) Function SA_B1(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  
  If ((xm1.eq.0._dp).and.(xm2.eq.0._dp)) Then 
    SA_B1=0._dp
    Return
  End if

  If (divonly.Eq.1) Then
   If (IRdivonly) Then 
    SA_B1 = 0._dp
   Else
    SA_B1 = - 0.5_dp * divergence
   End if
   Return 
  End If
  
  If (IRdivonly) Then 
   SA_B1 = 0._dp
   Return
  End if
  
  
  SA_B1 = B1(xp,xm1,xm2)

End Function SA_B1

Complex(dp) Function SA_B00(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2

  If (divonly.Eq.1) Then
   If (IRdivonly) Then 
    SA_B00 = 0._dp
   Else
    SA_B00 = divergence * (3._dp * xm1 + 3._dp * xm2 - xp)/12._dp
   End if
   Return 
  End If

  SA_B00 = B00(xp,xm1,xm2)

End Function SA_B00


Complex(dp) Function SA_Cget(name, p1, p2, p1p2, m1, m2, m3)
 Implicit None
  Real(dp), Intent(in) :: p1, p2, p1p2, m1, m2, m3
  Character(len=4), Intent(in) :: name

  Complex(dp) :: C_0, C1, C2, C00, C11, C12, C22, C001, C002, C111, C112  &
    & , C122, C222

  Iname = Iname + 1
  NameOfUnit(Iname) = "Cget"
  
  
 If (divonly.Eq.1) Then
  if (IRdivonly) Then 
    SA_Cget = 0._dp
  Else
   If ((name.Eq."C0").Or.(name.Eq."C1").Or.(name.Eq."C2")) Then
    SA_Cget = ZeroC
   Else If (name.Eq."C00") Then
    SA_Cget = 0.25_dp * divergence
   Else If ((name.Eq."C11").Or.(name.Eq."C12").Or.(name.Eq."C22")) Then
    SA_Cget = ZeroC
   Else If ((name.Eq."C001").Or.(name.Eq."C002")) Then
    SA_Cget = - divergence / 12._dp
   Else If ((name.Eq."C111").Or.(name.Eq."C112").Or.(name.Eq."C122").Or.(name.Eq."C222")) Then
    SA_Cget = ZeroC
   Else
    Write (ErrCan,*) "Problem in function Cget, function "//name
    Write (ErrCan,*) "is not defined"
    If (Errorlevel.Ge.0) Call TerminateProgram
   End If
  End if
!   Return

 Else if (IRdivonly) Then 
 
  If (name.Eq."C0") Then
   SA_Cget = C0_IR(p1,p2,p1p2, m1, m2, m3)
  Else If (name.Eq."C1") Then
   SA_Cget = C1_IR(p1,p2,p1p2, m1, m2, m3)
  Else If (name.Eq."C2") Then
   SA_Cget = C2_IR(p1,p2,p1p2, m1, m2, m3)
  Else If (name.Eq."C11") Then
   SA_Cget = C11_IR(p1,p2,p1p2, m1, m2, m3)
  Else If (name.Eq."C12") Then
   SA_Cget = C12_IR(p1,p2,p1p2, m1, m2, m3)
  Else If (name.Eq."C22") Then
   SA_Cget = C22_IR(p1,p2,p1p2, m1, m2, m3)
  Else If (name.Eq."C00") Then
   SA_Cget = C00_IR(p1,p2,p1p2, m1, m2, m3)
  Else
   Write(*,*) "unknown IR divergence: ", name 
  End If


 Else
 
  SA_Cget = Cget(name, p1, p2, p1p2, m1, m2, m3)

 End if
Iname = Iname - 1
  


End Function SA_Cget


Complex(dp) Function FloopRXi(p2,m12,m22) 
   Implicit None 
   Real(dp),Intent(in)::p2,m12,m22 
    
   
    If (RXi.eq.1._dp) Then
!        FloopRXi=Floop(p2,m12,m22)
!             Write(*,*) "frxi A",FloopRXi
     FloopRXi = SA_A0(m12) - 2._dp * SA_A0(m22) &
       & -  (2._dp * p2 + 2._dp * m12 - m22) * SA_B0(p2,m12,m22)
!             Write(*,*) "frxi B",FloopRXi
    Else
       If ((m12.gt.1.0E-10_dp).and.(m22.gt.1.0E-10_dp)) Then
          FloopRXi=A0(m12)-A0(m22)+((m12-p2)*A0(m22))/m22-&
               & ((m12-p2+m22*RXi)*A0(m22*RXi))/m22+(-m12+m22+p2)*b0(p2,m12,m22)-&
               & (m12-(m12-p2)**2/m22+3._dp*p2)*b0(p2,m12,m22)-((m12-p2)**2*b0(p2,m12,m22*RXi))/m22
       Else
          If (m12.gt.1.0E-10_dp) Then
              FloopRXi=A0(m12)-2._dp*(m12+p2)*B0(p2,0._dp,m12)
          Else If (m22.gt.1.0E-10_dp) Then
              FloopRXi=(-((m22+p2)*A0(m22))+(p2-m22*RXi)*A0(m22*RXi)+(m22-p2)**2*B0(p2,0._dp,m22)-p2**2*B0(p2,0._dp,m22*RXi))/m22
          Else
              FloopRXi=0._dp
          End if
       End if
    End if
     If (Real(FloopRXi,dp).ne.Real(FloopRXi,dp)) Write(*,*) "NaN in FloopRXi", p2,m12,m22

End Function FloopRXi


  
Complex(dp) Function SVVloop(p2,m12,m22)
    Implicit None

    Real(dp),Intent(in)::p2,m12,m22
    
    If ((m12.eq.0._dp).and.(m22.eq.0._dp)) Then
      SVVloop = 0._dp
      Return
    End if
 
    If (RXi.eq.1._dp) Then
	   
        SVVloop = 4._dp*Real(SA_B0(p2,m12,m22)-0.5_dp*rMS,dp)
    Else If (RXi.lt.0.1_dp) Then
	If (m12.gt.1.0E-10_dp) Then
	    If (p2.gt.0.1_dp) Then
		SVVloop = -2._dp*(rMS-A0(m12)/(8._dp*m12)+(RXi*A0(m12))/(8._dp*m12)-A0(m22)/(8._dp*m22)+(RXi*A0(m22))/(8._dp*m22)+A0(m12*RXi)/(8._dp*m12)&
               &-(RXi*A0(m12*RXi))/(8._dp*m12)+A0(m22*RXi)/(8._dp*m22)-&
               &(RXi*A0(m22*RXi))/(8._dp*m22)-(5._dp*B0(p2,m12,m22))/4._dp-(m12*B0(p2,m12,m22))/(8._dp*m22)&
               &-(m22*B0(p2,m12,m22))/(8._dp*m12)+(p2*B0(p2,m12,m22))/(4._dp*m12)+(p2*B0(p2,m12,m22))/(4._dp*m22)-&
               &(p2**2*B0(p2,m12,m22))/(8._dp*m12*m22)+(m12*B0(p2,m12,m22*RXi))/(8._dp*m22)-(p2*B0(p2,m12,m22*RXi))/(4._dp*m22)&
               &+(p2**2*B0(p2,m12,m22*RXi))/(8._dp*m12*m22)-(RXi*B0(p2,m12,m22*RXi))/4._dp-&
               &(p2*RXi*B0(p2,m12,m22*RXi))/(4._dp*m12)+(m22*RXi**2*B0(p2,m12,m22*RXi))/(8._dp*m12)&
               &+(m22*B0(p2,m22,m12*RXi))/(8._dp*m12)-(p2*B0(p2,m22,m12*RXi))/(4._dp*m12)+&
               &(p2**2*B0(p2,m22,m12*RXi))/(8._dp*m12*m22)-(RXi*B0(p2,m22,m12*RXi))/4._dp-(p2*RXi*B0(p2,m22,m12*RXi))/(4._dp*m22)&
               &+(m12*RXi**2*B0(p2,m22,m12*RXi))/(8._dp*m22)-&
               &(p2**2*B0(p2,m12*RXi,m22*RXi))/(8._dp*m12*m22)+(p2*RXi*B0(p2,m12*RXi,m22*RXi))/(4._dp*m12)&
               &+(p2*RXi*B0(p2,m12*RXi,m22*RXi))/(4._dp*m22)-(RXi**2*B0(p2,m12*RXi,m22*RXi))/4._dp-&
               &(m12*RXi**2*B0(p2,m12*RXi,m22*RXi))/(8._dp*m22)-(m22*RXi**2*B0(p2,m12*RXi,m22*RXi))/(8._dp*m12))
!                Write(*,*) SVVloop
	    Else
	     If (m12.eq.m22) Then 
	        SVVloop = 0._dp
	     Else 
		SVVloop = (2._dp*rMS*(-m12+m22)+3._dp*A0(m12)-3._dp*A0(m22))/(m12-m22)
             End if
	    End if
        Else
	     If (p2.gt.0.1) Then
		SVVloop = (-8._dp*rMS*m22+A0(m22)+2._dp*p2*B0(p2,0._dp,0._dp)+2._dp*(5._dp*m22-p2)*B0(p2,0._dp,m22))/(4._dp*m22)
	    Else
		SVVloop = -2._dp*rMS + 3._dp*B0(0._dp,0._dp,m22)
	    End if
	End if
    Else
    
       If ((m12.gt.1.0E-10_dp).and.(m22.gt.1.0E-10_dp)) Then
	  If (p2.lt.0.1) Then
	      SVVloop = (-2._dp*rMS*m12+2._dp*rMS*m22+3._dp*A0(m12)-3._dp*A0(m22)+RXi*A0(m12*RXi)-RXi*A0(m22*RXi))/(m12-m22)
	  Else
	  
	   If (m12-m22.lt.1_dp) Then 
	     SVVloop=  (p2**2*(B0(p2,m12,m12) - 2*B0(p2,m12,m12*RXi) + B0(p2,m12*RXi,m12*RXi)) + &
     &  4*m12*p2*(-B0(p2,m12,m12) + (1 + RXi)*B0(p2,m12,m12*RXi) - RXi*B0(p2,m12*RXi,m12*RXi)) + &
     &  2*m12*((1 - RXi)*A0(m12) + (-1 + RXi)*A0(m12*RXi) - m12*(4*rMS - 6*B0(p2,m12,m12) + (-1 + RXi)**2*B0(p2,m12,m12*RXi) - 2*RXi**2*B0(p2,m12*RXi,m12*RXi))))/(4*m12**2)
	   Else 
	      SVVloop = -2._dp*(rMS-A0(m12)/(8._dp*m12)+(RXi*A0(m12))/(8._dp*m12)-A0(m22)/(8._dp*m22)+(RXi*A0(m22))/(8._dp*m22)+A0(m12*RXi)/(8._dp*m12)&
               &-(RXi*A0(m12*RXi))/(8._dp*m12)+A0(m22*RXi)/(8._dp*m22)-&
               &(RXi*A0(m22*RXi))/(8._dp*m22)-(5._dp*B0(p2,m12,m22))/4._dp-(m12*B0(p2,m12,m22))/(8._dp*m22)&
               &-(m22*B0(p2,m12,m22))/(8._dp*m12)+(p2*B0(p2,m12,m22))/(4._dp*m12)+(p2*B0(p2,m12,m22))/(4._dp*m22)-&
               &(p2**2*B0(p2,m12,m22))/(8._dp*m12*m22)+(m12*B0(p2,m12,m22*RXi))/(8._dp*m22)-(p2*B0(p2,m12,m22*RXi))/(4._dp*m22)&
               &+(p2**2*B0(p2,m12,m22*RXi))/(8._dp*m12*m22)-(RXi*B0(p2,m12,m22*RXi))/4._dp-&
               &(p2*RXi*B0(p2,m12,m22*RXi))/(4._dp*m12)+(m22*RXi**2*B0(p2,m12,m22*RXi))/(8._dp*m12)&
               &+(m22*B0(p2,m22,m12*RXi))/(8._dp*m12)-(p2*B0(p2,m22,m12*RXi))/(4._dp*m12)+&
               &(p2**2*B0(p2,m22,m12*RXi))/(8._dp*m12*m22)-(RXi*B0(p2,m22,m12*RXi))/4._dp-(p2*RXi*B0(p2,m22,m12*RXi))/(4._dp*m22)&
               &+(m12*RXi**2*B0(p2,m22,m12*RXi))/(8._dp*m22)-&
               &(p2**2*B0(p2,m12*RXi,m22*RXi))/(8._dp*m12*m22)+(p2*RXi*B0(p2,m12*RXi,m22*RXi))/(4._dp*m12)&
               &+(p2*RXi*B0(p2,m12*RXi,m22*RXi))/(4._dp*m22)-(RXi**2*B0(p2,m12*RXi,m22*RXi))/4._dp-&
               &(m12*RXi**2*B0(p2,m12*RXi,m22*RXi))/(8._dp*m22)-(m22*RXi**2*B0(p2,m12*RXi,m22*RXi))/(8._dp*m12))
!                Write(*,*) SVVloop
          End if
          End if 
       Else If ((m12.gt.1.0E-10_dp).and.(m22.lt.1.0E-10_dp)) Then
	  If (p2.lt.0.1) Then
	      SVVloop = (-8._dp*rMS*m22+(11._dp+RXi)*A0(m22)+(1._dp+3._dp*RXi)*A0(m22*RXi))/(4._dp*m22)
	  Else
	      SVVloop =  -2._dp*rMS+A0(m12)/(4._dp*m12)-(RXi*A0(m12))/(4._dp*m12)-A0(m12*RXi)/(4._dp*m12)+(RXi*A0(m12*RXi))/(4._dp*m12)&
              &+(5._dp*B0(p2,0._dp,m12))/2._dp-(p2*B0(p2,0._dp,m12))/(2._dp*m12)+(RXi*B0(p2,0._dp,m12))/2._dp+(p2*RXi*B0(p2,0._dp,m12))/(2._dp*m12)& 
              &+(p2*B0(p2,0._dp,m12*RXi))/(2._dp*m12)+(RXi*B0(p2,0._dp,m12*RXi))/2._dp-(p2*RXi*B0(p2,0._dp,m12*RXi))/(2._dp*m12) + (RXi**2*B0(p2,0._dp,m12*RXi))/2._dp
          End if 
          
       Else If ((m22.gt.1.0E-10_dp).and.(m12.lt.1.0E-10_dp)) Then
	  If (p2.lt.0.1) Then
	      SVVloop = -2._dp*rMS + (1.0_dp*RXi)*B0(0._dp,0._dp,m22*RXi) + (3._dp)*B0(0._dp,0._dp,m22) !+ A0(m22)/m22
	  Else
	       SVVloop =  -2._dp*rMS+A0(m22)/(4._dp*m22)-(RXi*A0(m22))/(4._dp*m22)-A0(m22*RXi)/(4._dp*m22)+(RXi*A0(m22*RXi))/(4._dp*m22)&
              &+(5._dp*B0(p2,0._dp,m22))/2._dp-(p2*B0(p2,0._dp,m22))/(2._dp*m22)+(RXi*B0(p2,0._dp,m22))/2._dp+(p2*RXi*B0(p2,0._dp,m22))/(2._dp*m22)& 
              &+(p2*B0(p2,0._dp,m22*RXi))/(2._dp*m22)+(RXi*B0(p2,0._dp,m22*RXi))/2._dp-(p2*RXi*B0(p2,0._dp,m22*RXi))/(2._dp*m22) + (RXi**2*B0(p2,0._dp,m22*RXi))/2._dp
          End if 
          
       End if
    End if
         If (Real(SVVloop,dp).ne.Real(SVVloop,dp)) Write(*,*) "NaN in SVVloop", p2,m12,m22
  End Function SVVloop

Complex(dp) Function VSSloop(p2,m12,m22) 
Implicit None 
Real(dp),Intent(in)::p2,m12,m22 

VSSloop=  -4._dp*SA_B00(p2,m12,m22) 

End Function VSSloop

Complex(dp) Function VVSloop(p2,m12,m22) 
Implicit None 
Real(dp),Intent(in)::p2,m12,m22 


If (RXi.eq.1._dp) Then 
  VVSloop=  SA_B0(p2,m12,m22) 
Else
   VVSloop = B0(p2,m12,m22) + (-B00(p2,m12,m22) + B00(p2,m22,rxi*m12))/m12 !! FeynArts
End if

End Function VVSloop


Complex(dp) Function VVVloop(p2,m12,m22) 
Implicit None 
Real(dp),Intent(in)::p2,m12,m22 
Real(dp) :: b001


If (RXi.eq.1._dp) Then 
  VVVloop=   -2._dp*rMS*(m12 + m22 - p2/3._dp) + 10._dp*SA_B00(p2,m12,m22) &
     & + (m12+m22+4._dp*p2)*SA_B0(p2,m12,m22)+  SA_A0(m12) + SA_A0(m22)
Else
  If ((p2.gt.0).and.(m12.gt.0_dp).and.(m22.gt.0._dp)) Then 
      VVVloop= ((m12*m22*p2*(-3*m12 - 3*m22 - 40*p2 - 12*(m12 + m22 - 4*p2)*RXi - 9*(m12 + m22)*RXi**2) +  &
     &      6*m22*(-m22**2 - 9*m22*p2 + m12*(-9*m22 + p2*(13 - 2*RXi)) + m12**2*(9 + RXi) + p2**2*(9 + RXi))*A0(m12) -  &
     &      6*m12*(m12**2 + 9*m12*(m22 + p2) - m22**2*(9 + RXi) - p2**2*(9 + RXi) + m22*p2*(-13 + 2*RXi))*A0(m22) +  &
     &      6*(m22*(m22**2 + m22*(9*p2 - m12*RXi) - p2*(-11*m12*RXi + p2*(9 + RXi)))*A0(m12*RXi) + m12*(m12**2 + 9*m12*p2 - 9*p2**2 - (m12*m22 - 11*m22*p2 + p2**2)*RXi)*A0(m22*RXi) -  &
     &         m12**4*B0(p2,m12,m22) - 8*m12**3*m22*B0(p2,m12,m22) + 18*m12**2*m22**2*B0(p2,m12,m22) - 8*m12*m22**3*B0(p2,m12,m22) - m22**4*B0(p2,m12,m22) - 8*m12**3*p2*B0(p2,m12,m22) + &  
     &         32*m12**2*m22*p2*B0(p2,m12,m22) + 32*m12*m22**2*p2*B0(p2,m12,m22) - 8*m22**3*p2*B0(p2,m12,m22) + 18*m12**2*p2**2*B0(p2,m12,m22) + 32*m12*m22*p2**2*B0(p2,m12,m22) +  &
     &         18*m22**2*p2**2*B0(p2,m12,m22) - 8*m12*p2**3*B0(p2,m12,m22) - 8*m22*p2**3*B0(p2,m12,m22) - p2**4*B0(p2,m12,m22) + m12**4*B0(p2,m12,m22*RXi) + 8*m12**3*p2*B0(p2,m12,m22*RXi) -  &
     &         18*m12**2*p2**2*B0(p2,m12,m22*RXi) + 8*m12*p2**3*B0(p2,m12,m22*RXi) + p2**4*B0(p2,m12,m22*RXi) - 2*m12**3*m22*RXi*B0(p2,m12,m22*RXi) + 2*m12**2*m22*p2*RXi*B0(p2,m12,m22*RXi) +  &
     &         2*m12*m22*p2**2*RXi*B0(p2,m12,m22*RXi) - 2*m22*p2**3*RXi*B0(p2,m12,m22*RXi) + m12**2*m22**2*RXi**2*B0(p2,m12,m22*RXi) - 2*m12*m22**2*p2*RXi**2*B0(p2,m12,m22*RXi) +  &
     &         m22**2*p2**2*RXi**2*B0(p2,m12,m22*RXi) + m22**4*B0(p2,m22,m12*RXi) + 8*m22**3*p2*B0(p2,m22,m12*RXi) - 18*m22**2*p2**2*B0(p2,m22,m12*RXi) + 8*m22*p2**3*B0(p2,m22,m12*RXi) +  &
     &         p2**4*B0(p2,m22,m12*RXi) - 2*m12*m22**3*RXi*B0(p2,m22,m12*RXi) + 2*m12*m22**2*p2*RXi*B0(p2,m22,m12*RXi) + 2*m12*m22*p2**2*RXi*B0(p2,m22,m12*RXi) - 2*m12*p2**3*RXi*B0(p2,m22,m12*RXi) +  &
     &         m12**2*m22**2*RXi**2*B0(p2,m22,m12*RXi) - 2*m12**2*m22*p2*RXi**2*B0(p2,m22,m12*RXi) + m12**2*p2**2*RXi**2*B0(p2,m22,m12*RXi) -  &
     &         p2**2*(p2**2 - 2*(m12 + m22)*p2*RXi + (m12 - m22)**2*RXi**2)*B0(p2,m12*RXi,m22*RXi))))/(72.*m12*m22*p2) -2._dp*(rMS-1._dp)*(m12 + m22 - p2/3._dp)
  Else ! to be added
     Write(*,*) "Warning from VVVloop", p2,m12,m22
     VVVloop= 0._dp
   End if
! End if
End if
End Function VVVloop

 Complex(dp) Function SA_Gloop(p2,m12,m22)
 !-----------------------------------------------------------------------
 ! calculates the function G as defined in J. Bagger at al, Nucl.Phys.B
 ! written by Werner Porod, 4.8.1999
 ! 18.05.2001: porting to f90
 !-----------------------------------------------------------------------
 Implicit None

  Real(dp), Intent(in) :: p2,m12,m22

  If ((m12.eq.0._dp).and.(m22.eq.0._dp)) then
   If (p2.eq.0._dp) Then 
    SA_Gloop = 0._dp
   Else 
    SA_Gloop = p2 * SA_B0(p2,m12,m22)
   End if
  Else If (m12.eq.0._dp) then
   SA_Gloop = - SA_A0(m22) + (p2 - m22) * SA_B0(p2,m12,m22)

  Else If (m22.eq.0._dp) then
   SA_Gloop = - SA_A0(m12) + (p2 - m12) * SA_B0(p2,m12,m22)

  Else If (m12.eq.m22) then
   SA_Gloop =  - 2._dp * SA_A0(m12) + (p2 - m12 - m22) * SA_B0(p2,m12,m22)

  Else 
   SA_Gloop =  - SA_A0(m12) - SA_A0(m22) + (p2 - m12 - m22) * SA_B0(p2,m12,m22)

  End If

 End Function SA_Gloop


 Complex(dp) Function SA_Hloop(p2,m12,m22)
 !-----------------------------------------------------------------------
 ! calculates the function H as defined in J. Bagger at al, Nucl.Phys.B
 ! written by Werner Porod, 4.8.1999
 ! 18.05.2001: porting to f90
 !-----------------------------------------------------------------------
 Implicit None

  Real(dp), Intent(in) :: p2,m12,m22
  
  If ((p2.eq.0._dp).and.(m12.eq.0._dp).and.(m22.eq.0._dp)) Then
  SA_Hloop = 0._dp
  else 
  SA_Hloop = 4._dp * SA_B00(p2,m12,m22) + SA_GLoop(p2,m12,m22) 
  end if
 End Function SA_Hloop


Complex(dp) Function VGGloop(p2,m12,m22) 
Implicit None 
Real(dp),Intent(in)::p2,m12,m22 

If (RXi.eq.1._dp) Then 
  VGGloop=  SA_B00(p2,m12,m22) 
Else
  VGGloop=  SA_B00(p2,m12*RXi,m22*RXi) 

End if
End Function VGGloop


!definition of A00, B001, B111

 Complex(dp) Function A00(xm)
 Implicit None
  Real(dp), Intent(in) :: xm

  If (divonly.Eq.1) Then
   A00 = 0.25_dp * divergence * xm * xm
   Return 
  End If

  A00 = (1._dp/4._dp)*A0(xm)*xm + (1._dp/8._dp)*xm*xm

 End Function A00

 Complex(dp) Function B001(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Real(dp) :: cf1
  Complex(dp) :: ca0i(2)

  If (divonly.Eq.1) Then
   B001 = divergence * (-2._dp * xm1 - 4._dp * xm2 + xp) / 24._dp
   Return 
  End If

  cf1 = xp - xm2 + xm1

  ca0i(1) = A0(xm1)
  ca0i(2) = A0(xm2)

  B001 = 2._dp * xm1 * B1(xp,xm1,xm2) &
    & - ca0i(2) + cf1 * B11(xp,xm1,xm2) & 
    & - (1._dp)/(6._dp) &
    & * (2._dp * xm1 + 4._dp * xm2 - xp)

  B001 = (1._dp/8._dp) * B001

 End Function B001

 Complex(dp) Function B111(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Real(dp) :: cf1
  Complex(dp) :: ca0i(2)

  If (divonly.Eq.1) Then
   B111 = - 0.25_dp * divergence
   Return 
  End If

  cf1 = xp - xm2 + xm1

  ca0i(1) = A0(xm1)
  ca0i(2) = A0(xm2)

  B111 = ca0i(2) + 3._dp * cf1 * B11(xp,xm1,xm2) &
    & + 2._dp * xm1 * B1(xp,xm1,xm2) &
    & - (1._dp)/(6._dp) &
    & * (2._dp * xm1 + 4._dp * xm2 - xp)

  B111 = - (1._dp/4._dp) * B111
  B111 = B111/xp

 End Function B111

!derivative of B0
 Complex(dp) Function SA_DerB0(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  
  If ((xm1.eq.0._dp).and.(xm2.eq.0._dp)) Then 
    SA_DerB0=0._dp
    Return
  End if

  If (divonly.Eq.1) Then
   SA_DerB0 = ZeroC
   Return 
  End If

  If (IRdivonly) Then
!    If ((xm1.eq.Mass_Regulator_PhotonGluon**2).and.(xp.eq.xm2)) Then
   If ((EqualMasses(xm1,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(xm2,xp))) Then
    SA_DerB0 = 1._dp/(2._dp*xm2)*(0._dp - log(Mass_Regulator_PhotonGluon**2/xm2))
!    Else If ((xm2.eq.Mass_Regulator_PhotonGluon**2).and.(xp.eq.xm1)) Then
    Else If ((EqualMasses(xm2,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(xm1,xp))) Then
    SA_DerB0 = 1._dp/(2._dp*xm1)*(0._dp - log(Mass_Regulator_PhotonGluon**2/xm1))
   Else 
    SA_DerB0 = 0._dp
   End if

  Else

  SA_DerB0 = DB0(xp,xm1,xm2)
  
  End If
  


 End Function SA_DerB0
 
 !derivative of B0
 Complex(dp) Function SA_DerB1(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  
! 
   If ((xm1.eq.0._dp).and.(xm2.eq.0._dp)) Then 
    SA_DerB1=0._dp
    Return
  End if


    If (divonly.Eq.1) Then
     SA_DerB1 = ZeroC
     Return 
    End If
   
  If (IRdivonly) Then
!    If (xm1.eq.Mass_Regulator_PhotonGluon**2) Then
   If (EqualMasses(xm1,Mass_Regulator_PhotonGluon**2)) Then
    SA_DerB1 = ZeroC
   Else If ((EqualMasses(xm2,Mass_Regulator_PhotonGluon**2)).and.(EqualMasses(xm1,xp))) Then
!    Else If ((xm2.eq.Mass_Regulator_PhotonGluon**2).and.(xm1.eq.xp)) Then
    SA_DerB1 = -1._dp/(2._dp*xm1)*(0._dp - log(Mass_Regulator_PhotonGluon**2/xm1))
   Else 
    SA_DerB1 = 0._dp
   End if

  Else 
  SA_DerB1 = DerB1(xp,xm1,xm2)
  End if
 End Function SA_DerB1


!derivatives of other loop functions
Complex(dp) Function SA_DerA0(m1)
Implicit None
Real(dp), Intent(in) :: m1
SA_DerA0 = 0._dp
End Function SA_DerA0 

Complex(dp) Function DerB22(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerB22 = SA_DerB00(p2,m12,m22)
End Function DerB22


Complex(dp) Function SA_DerHloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
SA_DerHloop =   4._dp * SA_DerB00(p2,m12,m22) + SA_DerGLoop(p2,m12,m22) 
End Function SA_DerHloop 

Complex(dp) Function SA_DerGloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
! SA_DerGloop =  - 2._dp*(m12* SA_DerB0(p2,m12,m22) + p2*SA_DerB1(p2,m12,m22) + SA_B1(p2,m12,m22))
SA_DerGloop =  + (p2 - m12 - m22) * SA_DerB0(p2,m12,m22) + SA_B0(p2,m12,m22)
End Function SA_DerGloop 

Complex(dp) Function DerFloopRXi(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerFloopRXi = (-(2._dp*p2 + 2._dp*m12-m22)*SA_DerB0(p2,m12,m22)-2._dp*SA_B0(p2,m12,m22))
End Function DerFloopRXi

Complex(dp) Function DerVSSloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVSSloop = -4._dp*SA_DerB00(p2,m12,m22) 
End Function DerVSSloop

Complex(dp) Function DerVVSloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVVSloop = SA_DerB0(p2,m12,m22)
End Function DerVVSloop

Complex(dp) Function DerSVVloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerSVVloop = 4._dp*Real(SA_DerB0(p2,m12,m22),dp)
End Function DerSVVloop

Complex(dp) Function  DerVGGloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVGGloop = SA_DerB00(p2,m12,m22)
End Function  DerVGGloop

Complex(dp) Function DerVVVloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVVVloop = 10._dp*SA_DerB00(p2,m12,m22) &
     & + (m12+m22+4._dp*p2)*SA_DerB0(p2,m12,m22)+ 4._dp*SA_B0(p2,m12,m22)

End Function DerVVVloop




!derivatives of B1, B00, B11, B001, B111

 Complex(dp) Function DerB1(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE, sxm2, sxp
  Real(dp) :: mdiff
  
  If (divonly.Eq.1) Then
   DerB1 = ZeroC
   Return 
  End If

!   If (xp.Eq.0._dp) Then
!     If (xm1.Ne.0._dp) Then
!     mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
!     Else If (xm2.Ne.0._dp) Then
!     mdiff = Abs((xm1-xm2)/xm2)
!     Else
!     mdiff = 0._dp
!     End If
!    If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
!     write(ErrCan,*) "DerB1(0,0,0) diverges!"
  If (xp.Eq.0._dp) Then
    If (xm1.ge.controlmdiff) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.ge.controlmdiff) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.le.controlmdiff)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB1(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    DerB1 = - 1._dp / (12._dp * xm1)
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    DerB1 = - 1._dp / (6._dp * xm2)
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    DerB1 = 1._dp / (3._dp * xm1)
   Else !xp=0
    
    mudim2=GetRenormalizationScale()
   
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB1 = LogA * xm1**3 - 3._dp * LogA * xm1**2 * xm2 &
    & + 3._dp * LogA * xm1 * xm2**2 - LogA * xm2**3 &
    & + 8._dp * LogB * xm1**2 * xm2 + 8._dp * LogB * xm1 * xm2**2 &
    & - 4._dp * LogB * xm2**3 - 2._dp * LogC * xm1**3 &
    & + 6._dp * LogC * xm1**2 * xm2 - 6._dp * LogC * xm1 * xm2**2 &
    & + 2._dp * LogC * xm2**3 - 2._dp * LogD * xm1**3 &
    & + 4._dp * LogD * xm1**2 * xm2 - 2._dp * LogD * xm1 * xm2**2 &
    & + 2._dp * LogE * xm1**2 * xm2 - 4._dp * LogE * xm1 * xm2**2 &
    & + 2._dp * LogE * xm2**3 - 2._dp * xm1**3 - 3._dp * xm1**2 * xm2 &
    & + 6._dp * xm1 * xm2**2 - xm2**3
    DerB1 = DerB1 / (6._dp * (xm1 - xm2)**4)
   End If

  Else If (EqualMasses(xp,xm1).And.(Abs(xm2/xp).Le.(0.0001_dp))) Then
  !relevant in particular for IR divergent cases with small regulator mass xm2
  !Taylor Series of DerB1(xp,xp,xm2) up to xm2^4

   sxm2 = dsqrt(xm2)
   sxp = dsqrt(xp)

   DerB1 = 768._dp * xm2**4 + 7168._dp * xm2**3 * xp &
   & - 10584._dp * Pi * sxm2**5 * sxp**3 - 89600._dp * xm2**2 * xp**2 &
   & + 94080._dp * Pi * sxm2**3 * sxp**5 + 21504._dp * xm2 * xp**3 &
   & - 21._dp * (-6144._dp * xp**4 + 33._dp * Pi * sxm2**7 * sxp &
   & + 5120._dp * Pi * sxm2 * sxp**7) &
   & + 43008._dp * xp**2 * (xm2**2 - 3._dp * xm2 * xp + xp**2) * DLog(xm2/xp)

   DerB1 = DerB1 /(86016._dp * xp**5)

   !up to xm2^6 - makes essentially no difference
!   DerB1 = DerB1 + (131072._dp * xm2**6 - 96525._dp * Pi * sxm2**11 * sxp & 
!   & + 720896._dp * xm2**5 * xp - 566280._dp * Pi * sxm2**9 * sxp**3 &
!   & - 4181760._dp * Pi * sxm2**7 * sxp**5 &
!   & - 648806400._dp * Pi * sxm2 * sxp**11 &
!   & + 126720._dp * Pi * xp**2 * (33._dp * sxm2**7 * sxp &
!   & + 5120._dp * sxm2 * sxp**7))/(519045120._dp * xp**7)

  Else !generell case

  DerB1 = (xm1 - xm2) * B0(xp,xm1,xm2) &
   & + (xm2 - xm1) * B0(0._dp,xm1,xm2) &
   & - xp * (xm1 - xm2 + xp) * SA_DerB0(xp,xm1,xm2)
  DerB1 = DerB1 / (2._dp * xp * xp)

  End If

 End Function DerB1

 Complex(dp) Function SA_DerB00(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: VB0, VDerB0
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff
  
  mudim2=GetRenormalizationScale()
  


  If (divonly.Eq.1) Then
   If (IRdivonly) Then 
    SA_DerB00 = 0._dp
   Else
    SA_DerB00 = - divergence / 12._dp
    End if
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB00(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    LogD = Log(mudim2/xm1)
    SA_DerB00 = -(divergence + LogD) / 12._dp
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    LogE = Log(mudim2/xm2)
    SA_DerB00 = - (6._dp * divergence + 6._dp * LogE + 5._dp) / 72._dp
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    LogD = Log(mudim2/xm1)
    SA_DerB00 = - (6._dp * divergence + 6._dp * LogD + 5._dp) / 72._dp
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    SA_DerB00 = - 6._dp * divergence * xm1**3 + 18._dp * divergence * xm1**2 * xm2 &
    & -18._dp * divergence * xm1 * xm2**2 + 6._dp * divergence * xm2**3 &
    & + 6._dp * LogB * xm1**3 - 18._dp * LogB * xm1**2 * xm2 &
    & - 18._dp * LogB * xm1 * xm2**2 + 6._dp * LogB * xm2**3 &
    & + 6._dp * LogC * xm1**3 - 18._dp * LogC * xm1**2 * xm2 &
    & + 18._dp * LogC * xm1 * xm2**2 - 6._dp * LogC * xm2**3 &
    & - 5._dp * xm1**3 + 27._dp * xm1**2 * xm2 - 27._dp * xm1 * xm2**2 &
    & + 5._dp * xm2**3
    SA_DerB00 = SA_DerB00 / (72._dp * (xm1 - xm2)**3)
   End If

  Else !generell case

  VB0 = B0(xp,xm1,xm2)
  VDerB0 = SA_DerB0(xp,xm1,xm2)

  SA_DerB00 = 3._dp * (xm1 * xm1 - 2._dp * xm1 * xm2 &
   & + xm2 * xm2 - xp * xp) * VB0 &
   & - 3._dp * (xm1 - xm2) * (xm1 - xm2) * B0(0._dp,xm1,xm2) &
   & - 3._dp * xp * (xm1 * xm1 + xm2 * xm2 + xp * xp)* VDerB0 &
   & + 6._dp * (xm1 + xm2) * xp * xp * VDerB0 &
   & + 6._dp * xm1 * xm2 * xp * VDerB0 - 2._dp * xp * xp
  SA_DerB00 = SA_DerB00 / (36._dp * xp * xp)

  End If

 End Function SA_DerB00

 Complex(dp) Function DerB11(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: VB0, VDerB0
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff
  
  mudim2=GetRenormalizationScale()

  If (divonly.Eq.1) Then
   DerB11 = ZeroC
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB11(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    DerB11 = 1._dp / (20._dp * xm1)
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    DerB11 = 1._dp / (12._dp * xm2)
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    DerB11 = 1._dp / (4._dp * xm1)
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB11 = -3._dp * LogA * xm1**4 + 12._dp * LogA * xm1**3 * xm2 &
    & - 18._dp * LogA * xm1**2 * xm2**2 + 12._dp * LogA * xm1 * xm2**3 &
    & - 3._dp * LogA * xm2**4 - 30._dp * LogB * xm1**3 * xm2 &
    & - 54._dp * LogB * xm1**2 * xm2**2 + 54._dp * LogB * xm1 * xm2**3 &
    & - 18._dp * LogB * xm2**4 + 6._dp * LogC * xm1**4 &
    & - 30._dp * LogC * xm1**3 * xm2 + 54._dp * LogC * xm1**2 * xm2**2 &
    & - 42._dp * LogC * xm1 * xm2**3 + 12._dp * LogC * xm2**4 &
    & + 6._dp * LogD * xm1**4 - 18._dp * LogD * xm1**3 * xm2 &
    & + 18._dp * LogD * xm1**2 * xm2**2 - 6._dp * LogD * xm1 * xm2**3 &
    & - 12._dp * LogE * xm1**3 * xm2 + 36._dp * LogE * xm1**2 * xm2**2 &
    & - 36._dp * LogE * xm1 * xm2**3 + 12._dp * LogE * xm2**4 &
    & + 6._dp * xm1**4 + 20._dp * xm1**3 * xm2 - 36._dp * xm1**2 * xm2**2 &
    & + 12._dp * xm1 * xm2**3 - 2._dp * xm2**4
    DerB11 = DerB11 / (24._dp * (xm1 - xm2)**5)
   End If

  Else !generell case

  VB0 = B0(xp,xm1,xm2)
  VDerB0 = SA_DerB0(xp,xm1,xm2)

   DerB11 = 4._dp * xm1**2 * SA_B0(0._dp,xm1,xm2) &
    & + 4._dp * xm2**2 * B0(0._dp,xm1,xm2) + 2._dp * xm1 * xp * B0(0._dp,xm1,xm2) &
    & - 2._dp * xm2 * xp * B0(0._dp,xm1,xm2) - 8._dp * xm1 * xm2 * B0(0._dp,xm1,xm2) &
    & - 2._dp * xp * A0(xm2) - 4._dp * VB0 * xm1**2 + 8._dp * VB0 * xm1 * xm2 &
    & - 2._dp * VB0 * xm1 * xp - 4._dp * VB0 * xm2**2 + 4._dp * VB0 * xm2 * xp &
    & + 2._dp * VDerB0 * xm1**2 * xp - 4._dp * VDerB0 * xm1 * xm2 * xp &
    & + 2._dp * VDerB0 * xm1 * xp**2 + 2._dp * VDerB0 * xm2**2 * xp &
    & - 4._dp * VDerB0 * xm2 * xp**2 + 2._dp * VDerB0 * xp**3 + xm1 * xp + xm2 * xp
   DerB11 = DerB11 / (6._dp * xp * xp * xp)

  End If

 End Function DerB11
! 
!  Complex(dp) Function DerB001(xp, xm1, xm2)
!  Implicit None
!   Real(dp), Intent(in) :: xp, xm1, xm2
!   Complex(dp) :: VB0, VDerB0
!   Complex(dp) :: LogA, LogB, LogC, LogD, LogE
!   Real(dp) :: mdiff
! 
!   If (divonly.Eq.1) Then
!    DerB001 = divergence / 24._dp
!    Return 
!   End If
!   
!   mudim2=GetRenormalizationScale()
! 
!   If (xp.Eq.0._dp) Then
!     If (xm1.Ne.0._dp) Then
!     mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
!     Else If (xm2.Ne.0._dp) Then
!     mdiff = Abs((xm1-xm2)/xm2)
!     Else
!     mdiff = 0._dp
!     End If
!    If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
!     write(ErrCan,*) "DerB001(0,0,0) diverges!"
!    Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
!     LogD = Log(mudim2/xm1)
!     DerB001 = (divergence + LogD)/ 24._dp
!    Else If (xm1.Eq.0._dp) Then !xp=xm1=0
!     LogE = Log(mudim2/xm2)
!     DerB001 = (12._dp * divergence + 12._dp * LogE + 7._dp) / 288._dp
!    Else If (xm2.Eq.0._dp) Then !xp=xm2=0
!     LogD = Log(mudim2/xm1)
!     DerB001 = (12._dp * divergence + 12._dp * LogD + 13._dp) / 288._dp
!    Else !xp=0
!     LogA = Log(xm2/xm1)
!     LogB = Log(Sqrt(xm1/xm2))
!     LogC = Log(Sqrt(xm1*xm2)/mudim2)
!     LogD = Log(mudim2/xm1)
!     LogE = Log(mudim2/xm2)
! 
!     DerB001 = 12._dp * divergence * xm1**4 - 48._dp * divergence * xm1**3 * xm2 &
!     & + 72._dp * divergence * xm1**2 * xm2**2 - 48._dp * divergence * xm1 * xm2**3 &
!     & + 12._dp * divergence * xm2**4 + 2._dp * LogA * xm1**4 - 12._dp * LogA * xm1**2 * xm2**2 &
!     & + 16._dp * LogA * xm1 * xm2**3 - 6._dp * LogA * xm2**4 - 12._dp * LogB * xm1**4 &
!     & + 48._dp * LogB * xm1**3 * xm2 + 48._dp * LogB * xm1**2 * xm2**2 &
!     & - 12._dp * LogB * xm2**4 - 16._dp * LogC * xm1**4 + 48._dp * LogC * xm1**3 * xm2 &
!     & - 48._dp * LogC * xm1**2 * xm2**2 + 16._dp * LogC * xm1 * xm2**3 &
!     & - 4._dp * LogD * xm1**4 + 12._dp * LogD * xm1**2 * xm2**2 &
!     & - 8._dp * LogD * xm1 * xm2**3 + 12._dp * LogE * xm1**2 * xm2**2 &
!     & - 24._dp * LogE * xm1 * xm2**3 + 12._dp * LogE * xm2**4 &
!     & + 13._dp * xm1**4 - 88._dp * xm1**3 * xm2 + 108._dp * xm1**2 * xm2**2 &
!     & - 40._dp * xm1 * xm2**3 + 7._dp * xm2**4
!     DerB001 = DerB001 / (288._dp * (xm1 - xm2)**4)
!    End If
! 
!   Else !generell case
! 
!   VB0 = B0(xp,xm1,xm2)
!   VDerB0 = DerB0(xp,xm1,xm2)
! 
!   DerB001 = 6._dp * (xm1 - xm2) * (2._dp * xm1**2 - xm1 * (4._dp * xm2 + xp) &
!    &         + 2._dp * xm2 * (xm2-xp)) * B0(0._dp,xm1,xm2) &
!    & + 6._dp * xp * (xm2 - xm1) * A0(xm2) - 12._dp * VB0 * xm1**3 &
!    & + 36._dp * VB0 * xm1**2 * xm2 + 6._dp * VB0 * xm1**2 * xp &
!    & - 36._dp * VB0 * xm1 * xm2**2 + 12._dp * VB0 * xm1 * xm2 * xp &
!    & + 12._dp * VB0 * xm2**3 - 18._dp * VB0 * xm2**2 * xp &
!    & + 6._dp * VB0 * xp**3 + 6._dp * VDerB0 * xm1**3 * xp &
!    & - 18._dp * VDerB0 * xm1**2 * xm2 * xp - 6._dp * VDerB0 * xm1**2 * xp**2 &
!    & + 18._dp * VDerB0 * xm1 * xm2**2 * xp - 12._dp * VDerB0 * xm1 * xm2 * xp**2 &
!    & - 6._dp * VDerB0 * xm1 * xp**3 - 6._dp * VDerB0 * xm2**3 * xp &
!    & + 18._dp * VDerB0 * xm2**2 * xp**2 - 18._dp * VDerB0 * xm2 * xp**3 &
!    & + 6._dp * VDerB0 * xp**4 + 3._dp * xm1**2 * xp - 3._dp * xm2**2 * xp + 4._dp * xp**3
!   DerB001 = DerB001 / (144._dp * xp * xp * xp)
! 
!   End If
! 
!  End Function DerB001
! 
!  Complex(dp) Function DerB111(xp, xm1, xm2)
!  Implicit None
!   Real(dp), Intent(in) :: xp, xm1, xm2
!   Complex(dp) :: VB0, VDerB0
!   Complex(dp) :: LogA, LogB, LogC, LogD, LogE
!   Real(dp) :: mdiff
! 
!   If (divonly.Eq.1) Then
!    DerB111 = ZeroC
!    Return 
!   End If
! 
!   If (xp.Eq.0._dp) Then
!     If (xm1.Ne.0._dp) Then
!     mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
!     Else If (xm2.Ne.0._dp) Then
!     mdiff = Abs((xm1-xm2)/xm2)
!     Else
!     mdiff = 0._dp
!     End If
!    If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
!     write(ErrCan,*) "DerB111(0,0,0) diverges!"
!    Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
!     DerB111 = - 1._dp / (30._dp * xm1)
!    Else If (xm1.Eq.0._dp) Then !xp=xm1=0
!     DerB111 = - 1._dp / (20._dp * xm2)
!    Else If (xm2.Eq.0._dp) Then !xp=xm2=0
!     DerB111 = - 1._dp / (5._dp * xm1)
!    Else !xp=0
!     LogA = Log(xm2/xm1)
!     LogB = Log(Sqrt(xm1/xm2))
!     LogC = Log(Sqrt(xm1*xm2)/mudim2)
!     LogD = Log(mudim2/xm1)
!     LogE = Log(mudim2/xm2)
! 
!     DerB111 = 15._dp * LogA  * xm1**5 + 21._dp * LogA * xm1**4 * xm2 &
!     & - 9._dp * LogA * xm1**3 * xm2**2 - 249._dp * LogA * xm1**2 * xm2**3 &
!     & + 366._dp * LogA * xm1 * xm2**4 - 144._dp * LogA * xm2**5 &
!     & + 120._dp * LogB * xm1**4 * xm2 - 360._dp * LogB * xm1**2 * xm2**3 &
!     & + 1200._dp * LogB * xm1 * xm2**4 - 720._dp * LogB * xm2**5 &
!     & - 30._dp * LogC * xm1**5 + 102._dp * LogC * xm1**4 * xm2 &
!     & - 138._dp * LogC * xm1**3 * xm2**2 + 522._dp * LogC * xm1**2 * xm2**3 &
!     & - 888._dp * LogC * xm1 * xm2**4 + 432._dp * LogC * xm2**5 &
!     & - 30._dp * LogD * xm1**5 - 30._dp * LogD * xm1**4 * xm2 &
!     & - 60._dp * LogD * xm1**3 * xm2**2 + 330._dp * LogD * xm1**2 * xm2**3 &
!     & - 210._dp * LogD * xm1 * xm2**4 + 132._dp * LogE * xm1**4 * xm2 &
!     & - 78._dp * LogE * xm1**3 * xm2**2 + 192._dp * LogE * xm1**2 * xm2**3 &
!     & - 678._dp * LogE * xm1 * xm2**4 + 432._dp * LogE * xm2**5 &
!     & - 24._dp * xm1**5 - 130._dp * xm1**4 * xm2 + 240._dp * xm1**3 * xm2**2 &
!     & - 120._dp * xm1**2 * xm2**3 + 40._dp * xm1 * xm2**4 - 6._dp * xm2**5
!     DerB111 = DerB111 / (120._dp * (xm1 - xm2)**6)
!    End If
! 
!   Else !generell case
! 
!   VB0 = B0(xp,xm1,xm2)
!   VDerB0 = DerB0(xp,xm1,xm2)
! 
!   DerB111 =3._dp * (xm1-xm2) * (3._dp * xm1**2 - 6._dp * xm1 * xm2 + 2._dp * xm1 * xp &
!    & + 3._dp * xm2**2 - 4._dp * xm2 * xp + xp**2)*B0(0._dp,xm1,xm2) &
!    & - 6._dp * xp *A0(xm2)*(xm1-xm2+xp) - 9._dp * VB0 * xm1**3 &
!    & + 27._dp * VB0 * xm1**2 * xm2 - 6._dp * VB0 * xm1**2 * xp &
!    & - 27._dp * VB0 * xm1 * xm2**2 + 24._dp * VB0 * xm1 * xm2 * xp &
!    & - 3._dp * VB0 * xm1 * xp**2 + 9._dp * VB0 * xm2**3 &
!    & - 18._dp * VB0 * xm2**2 * xp + 9._dp * VB0 * xm2 * xp**2 &
!    & + 3._dp * VDerB0 * xm1**3 * xp - 9._dp * VDerB0 * xm1**2 * xm2 * xp &
!    & + 3._dp * VDerB0 * xm1**2 * xp**2 + 9._dp * VDerB0 * xm1 * xm2**2 * xp &
!    & - 12._dp * VDerB0 * xm1 * xm2 * xp**2 + 3._dp * VDerB0 * xm1 * xp**3 &
!    & - 3._dp * VDerB0 * xm2**3 * xp + 9._dp * VDerB0 * xm2**2 * xp**2 &
!    & - 9._dp * VDerB0 * xm2 * xp**3 + 3._dp * VDerB0 * xp**4 &
!    & + 3._dp * xm1**2 * xp + 2._dp * xm1 * xp**2 - 3._dp * xm2**2 * xp &
!    & + 4._dp * xm2 * xp**2
!   DerB111 = - DerB111 / (12._dp * xp * xp * xp * xp)
! 
!   End If
! 
!  End Function DerB111

!special passarino veltman integrals with zero masses:
!IR145 = argument 1,4 and 5 are zero
!example: C0_IR145(xp1,xp2,xm) = C0(0,xp1,xp2,0,0,xm)
!notation equivalent to looptools = ff package

 Complex(dp) Function C0_IR145(xp1, xp2, xm)
 Implicit None
  Real(dp), Intent(in) :: xp1, xp2, xm
!  Real(dp) :: s1
  Complex(dp) :: logspecial
  
  If (xp1.Eq.xp2) Then !xp1 = xp2

   If (xp1.Eq.xm) Then !xp1 = xp2 = xm
    
    !Call WriteLFerror(3) !divergent
    write(ErrCan,*) "Divergent Passarino Veltman, C0_IR145!"
    C0_IR145 = Huge(1._dp)

   Else !xp1 = xp2 unequal xm

!    calculating log(1-xp2/xm)
!     s1 = 1._dp - xm/xp2
!    If ( Abs(s1) .Lt. xloss ) Then
!     logspecial = Log1minusX(s1)
!    Else
    logspecial = Log(Abs(1._dp - xm/xp2)) + (xm/xp2) * Log(Abs(1._dp/(xp2/xm - 1._dp)))
    If (xp2.Gt.xm) logspecial = logspecial + 2._dp * Cmplx(0._dp,pi,dp) * (1._dp - xm/xp2)

    C0_IR145 = logspecial / (xp2 - xm)

   End If

  Else !the two momenta are not equal

  C0_IR145 = Cget("C0  ",0._dp,xp1,xp2,0._dp,0._dp,xm)

  End If

 End Function C0_IR145

 Complex(dp) Function C2_IR145(xp1, xp2, xm)
 Implicit None
  Real(dp), Intent(in) :: xp1, xp2, xm
  Real(dp) :: s1
  Complex(dp) :: logspecial
  
  If (xp1.Eq.xp2) Then !xp1 = xp2

   If (xp1.Eq.xm) Then !xp1 = xp2 = xm
    
    !Call WriteLFerror(3) !divergent
    write(ErrCan,*) "Divergent Passarino Veltman, C2_IR145!"
    C2_IR145 = Huge(1._dp)

   Else !xp1 = xp2 unequal xm

    !calculating log(1-xp2/xm)
     s1 = xp2/xm
    If ( Abs(s1) .Lt. xloss ) Then
     logspecial = Log1minusX(s1)
    Else
     logspecial = Log(Abs(1._dp - s1))
    End If
    If (xp2.Gt.xm) logspecial = logspecial + Cmplx(0._dp,pi,dp)

    C2_IR145 = - xm * logspecial - xp2
    C2_IR145 = C2_IR145 / (xp2 * xp2)

   End If

  Else !the two momenta are not equal

  C2_IR145 = B0(xp1,0._dp,xm) - B0(xp2,0._dp,xm)
  C2_IR145 = C2_IR145 / (xp1 - xp2)

  End If

 End Function C2_IR145


 Real(dp) Function SetRenormalizationScaleAdd(mu2_in)
 Implicit None
  Real(dp), Intent(in) :: mu2_in

  SetRenormalizationScaleAdd = mudim2
  mudim2 = mu2_in

 End Function SetRenormalizationScaleAdd

 Real(dp) Function SetDivergenceAdd(diver_in)
 !-----------------------------------------------------------------------
 ! resets divergence
 !-----------------------------------------------------------------------
 Implicit None
  Real(dp), Intent(in) :: diver_in

  SetDivergenceAdd = divergence
  divergence = diver_in

 End Function SetDivergenceAdd

 Integer Function SetDivonlyAdd(div_in)
 !-----------------------------------------------------------------------
 ! take only divergent parts
 !-----------------------------------------------------------------------
 Implicit None
  Integer, Intent(in) :: div_in

  SetDivonlyAdd = divonly
  divonly = div_in
  
  If (divonly.eq.1) rMS=0._dp ! remove constant parts in MS scheme

 End Function SetDivonlyAdd
 
!  
!---------------------------------------
! Loop functions for g-2 with vectors
! based on 1402.7065
!---------------------------------------


 Real(dp) Function fFFV(x)
 Implicit None
  Real(dp), Intent(in) :: x 
  If (x.Eq.0._dp) Then
   fFFV = -4._dp/3._dp
  Else If (x.Eq.1._dp) Then
   fFFV =-13._dp/12._dp
   Else
   fFFV = (-8._dp + 38._dp*x - 39._dp*x**2 + 14._dp*x**3 - &
   & 5._dp*x**4 + 18._dp*x**2*Log(x))/(6._dp*(-1._dp + x)**4)
  End If
End Function fFFV

 Real(dp) Function gFFV(x)
 Implicit None
  Real(dp), Intent(in) :: x 
  If (x.Eq.0._dp) Then
   gFFV = 4._dp
  Else If (x.Eq.1._dp) Then
   gFFV =2._dp
   Else
   gFFV =(-4._dp + 3._dp*x + x**3 - 6._dp*x*Log(x))/(-1._dp + x)**3
  End If
End Function gFFV

 Real(dp) Function fVVF(x)
 Implicit None
  Real(dp), Intent(in) :: x 
  If (x.Eq.0._dp) Then
   fVVF = 5._dp/3._dp
  Else If (x.Eq.1._dp) Then
   fVVF =17._dp/12._dp
   Else
   fVVF =(10._dp - 43._dp*x + 78._dp*x**2 - 49._dp*x**3 +  &
    & 4._dp*x**4 + 18._dp*x**3*Log(x))/(6._dp*(-1._dp + x)**4)
  End If
End Function fVVF


 Real(dp) Function gVVF(x)
 Implicit None
  Real(dp), Intent(in) :: x 
  If (x.Eq.0._dp) Then
   gVVF = -4._dp
  Else If (x.Eq.1._dp) Then
   gVVF =-3._dp
   Else
   gVVF =(4._dp - 15._dp*x + 12._dp*x**2 - x**3 - 6._dp*x**2*Log(x))/(-1._dp + x)**3
  End If
End Function gVVF


!-----------------------------------
! IR Save Loop Functions
!-----------------------------------


Complex(dp) Function A0_IR(m1)
Implicit None
Real(dp), Intent(in) :: m1

If (divonly.Eq.1) Then
    A0_IR = m1*divergence
    Return
End if

If ((m1/UVscaleQ).le.IRmass) Then
 A0_IR = 0._dp
Else 
 A0_IR = m1*(1+Log(UVscaleQ/m1))
End If

End Function A0_IR


Complex(dp) Function B0_IR(m1,m2)
Implicit None
Real(dp), Intent(in) :: m1,m2
Real(dp) :: m1s, m2s


If (divonly.Eq.1) Then
    B0_IR = divergence
    Return
End if    

! Sort masses
If (m1.ge.m2) Then 
 m1s=m2
 m2s=m1
Else 
 m1s=m1
 m2s=m2
End if

If  ((m2s/UVscaleQ).le.IRmass) Then ! B0(0,0)
 B0_IR=0._dp
Else if ((m1s/UVscaleQ).le.IRmass) Then ! B0(0,m2)
 B0_IR=1._dp + Log(UVscaleQ/m2s)
Else if (Abs((m1s-m2s)/UVscaleQ).le.IRmass) Then ! B0(m1,m1) 
 B0_IR=log(UVscaleQ/m1s)
Else 
 B0_IR=1._dp + log(UVscaleQ/m2s) + m1s/(m1s-m2s)*log(m2s/m1s)
End if

End Function B0_IR

Complex(dp) Function B1_IR(m1,m2)
Implicit None
Real(dp), Intent(in) :: m1,m2
Real(dp) :: t0


If (divonly.Eq.1) Then
    B1_IR = -0.5_dp*divergence
    Return
End if 

If  (((m2/UVscaleQ).le.IRmass).and.((m1/UVscaleQ).le.IRmass)) Then ! B1(0,0)
 B1_IR=0._dp
Else if ((m1/UVscaleQ).le.IRmass) Then ! B1(0,m2)
 B1_IR=-0.25_dp + 0.5_dp*Log(m2/UVscaleQ)
Else if ((m2/UVscaleQ).le.IRmass) Then ! B1(m1,0)
 B1_IR=0.25_dp*(-3._dp + 2._dp*Log(m1/UVscaleQ)) 
Else if (Abs((m1-m2)/UVscaleQ).le.IRmass) Then ! B1(m1,m1) 
 B1_IR=0.5_dp*log(m1/UVscaleQ)
Else 
 t0 = m2/m1
 B1_IR=0.5_dp*Log(m1/UVscaleQ)+ (-3._dp+4._dp*t0 - t0**2 - 4._dp*t0*Log(t0)+2._dp*t0**2*Log(t0))/(4._dp*(-1._dp+t0)**2)
End if

End Function B1_IR


Complex(dp) Function C0eft_IR(m1,m2,m3)
Implicit None
Real(dp), Intent(in) :: m1,m2,m3
Real(dp) :: xpi1,xpi2,xpi3, m_j, t1, t2

If (divonly.Eq.1) Then
    C0eft_IR = 0._dp
    Return
End if 

! Sort masses
xpi1 = m1
xpi2 = m2
xpi3 = m3

 If (xpi1 .Lt. xpi2) Then
    m_j = xpi2
    xpi2 = xpi1
    xpi1 = m_j
Endif
If (xpi2 .Lt. xpi3) Then
    m_j = xpi3
    xpi3 = xpi2
    xpi2 = m_j
Endif
If (xpi1 .Lt. xpi2) Then
    m_j = xpi2
    xpi2 = xpi1
    xpi1 = m_j
Endif

If  ((xpi1/UVscaleQ).le.IRmass) Then ! C0(0,0,0)
 C0eft_IR=0._dp
Else if ((xpi2/UVscaleQ).le.IRmass) Then ! C0(m1,0,0)
 C0eft_IR=1/xpi1 - log(xpi1/UVscaleQ)/xpi1 
Else if ((xpi3/UVscaleQ).le.IRmass) Then ! C0(m1,m2,0) 
   If (Abs((xpi1-xpi2)/UVscaleQ).le.IRmass) Then ! C0(m1,m1,0)
     C0eft_IR = -1/xpi1 
   Else ! C0(m1,m2,0)
     C0eft_IR = -(log(xpi1/xpi2)/(xpi1-xpi2))
   End if
Else if ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass).and.(Abs((xpi1-xpi3)/UVscaleQ).le.IRmass)) Then ! C0(m1,m1,m1) 
 C0eft_IR=-1._dp/(2._dp*xpi1)
Else if ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass)) Then ! C0(m1,m1,m3) 
 C0eft_IR = (-xpi1 + xpi3 + xpi3*log(xpi1/xpi3))/(xpi1-xpi3)**2
Else if ((Abs((xpi2-xpi3)/UVscaleQ).le.IRmass)) Then ! C0(m1,m2,m2) 
 C0eft_IR = (-xpi3 + xpi1 + xpi1*log(xpi3/xpi1))/(xpi3-xpi1)**2 
Else 
t1 = xpi2/xpi1
t2 = xpi3/xpi1
 C0eft_IR=(-1._dp/xpi1)*(-t1*Log(t1)+t1*t2*Log(t1)+t2*Log(t2)-t1*t2*Log(t2))/((-1._dp+t1)*(t1-t2)*(-1._dp+t2))
End if

End Function C0eft_IR


Complex(dp) Function D0_IR(m1,m2,m3,m4)
Implicit None
Real(dp), Intent(in) :: m1,m2,m3,m4
Real(dp) :: xpi1,xpi2,xpi3,xpi4, m_j, t1, t2, t3

Integer :: slot


If (divonly.Eq.1) Then
    D0_IR = 0._dp
    Return
End if

! Sort masses
xpi1 = m1
xpi2 = m2
xpi3 = m3
xpi4 = m4

! enforece m4 to be the smallest
If (xpi1 .Lt. xpi2) Then
    m_j = xpi2
    xpi2 = xpi1
    xpi1 = m_j
Endif
If (xpi2 .Lt. xpi3) Then
    m_j = xpi3
    xpi3 = xpi2
    xpi2 = m_j
Endif
If (xpi3 .Lt. xpi4) Then
    m_j = xpi4
    xpi4 = xpi3
    xpi3 = m_j
Endif

! sort the first three again
If (xpi1 .Lt. xpi2) Then
    m_j = xpi2
    xpi2 = xpi1
    xpi1 = m_j
Endif
If (xpi2 .Lt. xpi3) Then
    m_j = xpi3
    xpi3 = xpi2
    xpi2 = m_j
Endif
If (xpi1 .Lt. xpi2) Then
    m_j = xpi2
    xpi2 = xpi1
    xpi1 = m_j
Endif

If  ((xpi1/UVscaleQ).le.IRmass) Then ! D0(0,0,0,0)
 D0_IR=0._dp
 slot=1
Else if ((xpi2/UVscaleQ).le.IRmass) Then ! D0(m1,0,0,0)
 D0_IR= -Log(xpi1/UVscaleQ)/xpi1**2 + 1._dp/xpi1**2 
 slot=2
Else if ((xpi3/UVscaleQ).le.IRmass) Then ! D0(m1,m2,0,0) 
   If (Abs((xpi1-xpi2)/UVscaleQ).le.IRmass) Then ! D0(m1,m1,0,0)
     D0_IR = -2._dp/xpi1**2 + Log(xpi1/UvscaleQ)/xpi1**2 
     slot=3
   Else ! D0(m1,m2,0,0)
     D0_IR = Log(xpi2/xpi1)/(xpi1*(xpi1 - xpi2)) +  Log(xpi2/UVscaleQ)/(xpi1*xpi2)
     slot=4
   End if
Else if ((xpi4/UVscaleQ).le.IRmass) Then ! D0(m1,m2,m3,0) 
   If ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass).and.(Abs((xpi1-xpi3)/UVscaleQ).le.IRmass)) Then ! D0(m1,m1,m1,0)
     D0_IR = 1._dp/(2._dp*xpi1**2)
     slot=5
   Else if (Abs((xpi1-xpi2)/UVscaleQ).le.IRmass) Then ! D0(m1,m1,m3,0)
    D0_IR = (xpi3-xpi1+xpi1*Log(xpi1/xpi3))/((xpi3-xpi1)**2*xpi1)
    slot=6
   Else if (Abs((xpi2-xpi3)/UVscaleQ).le.IRmass) Then ! D0(m1,m1,m3,0)
     D0_IR = (xpi1-xpi3+xpi3*Log(xpi3/xpi1))/((xpi1-xpi3)**2*xpi3)
     slot=7
   Else ! D0(m1,m2,m3,0) 
     D0_IR = ((xpi2-xpi3)*Log(xpi3/xpi1)+(-xpi1+xpi3)*Log(xpi3/xpi2))/((xpi1-xpi2)*(xpi1-xpi3)*(xpi2-xpi3))
     slot=8
   End if     
Else if ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass).and.(Abs((xpi2-xpi3)/UVscaleQ).le.IRmass).and.(Abs((xpi3-xpi4)/UVscaleQ).le.IRmass)) Then ! D0(m1,m1,m1,m1) 
     D0_IR=1._dp/(6._dp*xpi1**2)
     slot=9
Else if ((Abs((xpi2-xpi3)/UVscaleQ).le.IRmass).and.(Abs((xpi3-xpi4)/UVscaleQ).le.IRmass)) Then ! D0(m1,m2,m2,m2)
     D0_IR = (xpi1**2-xpi2**2+2._dp*xpi1*xpi2*Log(xpi2/xpi1))/(2._dp*(xpi1-xpi2)**3*xpi2)
     slot=10
Else if ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass).and.(Abs((xpi1-xpi3)/UVscaleQ).le.IRmass)) Then ! D0(m1,m1,m1,m4)
      xpi2=xpi1
      xpi1=xpi4
      D0_IR = (xpi1**2-xpi2**2+2._dp*xpi1*xpi2*Log(xpi2/xpi1))/(2._dp*(xpi1-xpi2)**3*xpi2)     
      slot=11
Else if ((Abs((xpi2-xpi3)/UVscaleQ).le.IRmass).and.(Abs((xpi3-xpi4)/UVscaleQ).le.IRmass)) Then ! D0(m1,m2,m2,m2)     
     D0_IR = (xpi1**2-xpi2**2+2._dp*xpi1*xpi2*Log(xpi2/xpi1))/(2._dp*(xpi1-xpi2)**2*xpi2)
     slot=12
Else if ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass).and.(Abs((xpi3-xpi4)/UVscaleQ).le.IRmass)) Then ! D0(m1,m1,m3,m3)          
     D0_IR = (-2._dp*xpi1+2._dp*xpi3 + (xpi1+xpi3)*Log(xpi1/xpi3))/(xpi1-xpi3)**3
     slot=13
Else if ((Abs((xpi1-xpi2)/UVscaleQ).le.IRmass)) Then ! D0(m1,m1,m3,m4)     
     xpi1=xpi3
     xpi3=xpi2     
     xpi2=xpi4
     D0_IR = ((xpi1-xpi3+xpi2*Log(xpi3/xpi1))/(xpi1-xpi3)**2+(-xpi2+xpi3-xpi2*Log(xpi3/xpi2))/(xpi2-xpi3)**2)/(xpi1-xpi2)    
     slot=14
Else if ((Abs((xpi2-xpi3)/UVscaleQ).le.IRmass)) Then ! D0(m1,m2,m2,m4)
     xpi2=xpi4
     xpi4=xpi3  
     D0_IR = ((xpi1-xpi3+xpi2*Log(xpi3/xpi1))/(xpi1-xpi3)**2+(-xpi2+xpi3-xpi2*Log(xpi3/xpi2))/(xpi2-xpi3)**2)/(xpi1-xpi2)
     slot=15
Else if ((Abs((xpi3-xpi4)/UVscaleQ).le.IRmass)) Then ! D0(m1,m2,m3,m3)     
     D0_IR = ((xpi1-xpi3+xpi2*Log(xpi3/xpi1))/(xpi1-xpi3)**2+(-xpi2+xpi3-xpi2*Log(xpi3/xpi2))/(xpi2-xpi3)**2)/(xpi1-xpi2) 
     slot=16
! Else 
!  D0_IR=1._dp*(xpi1-xpi2)*(C0eft_IR(xpi1,xpi3,xpi4)-C0eft_IR(xpi2,xpi3,xpi4))
Else 
D0_IR=D0_bagger(m1,m2,m3,m4)
slot=17
End if

If (Abs(D0_IR).ne.Abs(D0_IR)) Then
Write(*,*) "NaN",m1,m2,m3,m4, slot, xpi1,xpi2,xpi3,xpi4
End if



! If (Abs(D0_IR).gt.1.0E-10) Then 
!  Write(*,*) xpi1,xpi2,xpi3,xpi4,D0_IR
!  Write(*,*) "D0B", D0_bagger(m1,m2,m3,m4)
!  D0_IR=0.
! Else  
! Write(*,*) "save", D0_bagger(m1,m2,m3,m4), D0_IR
! End if

End Function D0_IR


Complex(dp) Function DB0_IR(m1,m2)
Implicit None
Real(dp), Intent(in) :: m1,m2
Real(dp) :: m1s, m2s

If (divonly.Eq.1) Then
    DB0_IR = 0._dp
    Return
End if 

! Sort masses
If (m1.ge.m2) Then 
 m1s=m2
 m2s=m1
Else 
 m1s=m1
 m2s=m2
End if

If  ((m2s/UVscaleQ).le.IRmass) Then ! B0(0,0)
 DB0_IR=0._dp
Else if ((m1s/UVscaleQ).le.IRmass) Then ! B0(0,m2)
 DB0_IR=1._dp/(2._dp*m2s)
Else if (Abs((m1s-m2s)/UVscaleQ).le.IRmass) Then ! B0(m1,m1) 
 DB0_IR=1._dp/(6._dp*m1s)
Else 
 DB0_IR=1._dp/(2._dp*(m1s-m2s)**2)*(m1s+m2s+2._dp*m1s*m2s/(m1s-m2s)*Log(m2s/m1s))
End if
End Function DB0_IR


Complex(dp) Function DB1_IR(m1,m2)
Implicit None
Real(dp), Intent(in) :: m1,m2
Real(dp) :: t0

If (divonly.Eq.1) Then
    DB1_IR = 0._dp
    Return
End if 

If  (((m2/UVscaleQ).le.IRmass).and.((m1/UVscaleQ).le.IRmass)) Then ! B1(0,0)
 DB1_IR=0._dp
Else if ((m1/UVscaleQ).le.IRmass) Then ! B1(0,m2)
 DB1_IR=-1._dp/(6._dp*m2)
Else if ((m2/UVscaleQ).le.IRmass) Then ! B1(m1,0)
 DB1_IR=1._dp/(3._dp*m1)
Else if (Abs((m1-m2)/UVscaleQ).le.IRmass) Then ! B1(m1,m1) 
 DB1_IR=-1._dp/(12._dp*m1)
Else 
 DB1_IR=1._dp/(6._dp*(m1-m2)**4)*(-3._dp*m1**2*m2*(2._dp*Log(m2/m1)+1._dp)-2._dp*m1**3+6._dp*m1*m2**2-m2**3)
End if
End Function DB1_IR


 
End Module AddLoopFunctions
