 Module DerivativesEffPotFunctions
 ! ###############################
 ! derivatives of EffPot Functions
 ! ###############################
 Use Control
 Use Mathematics
 Use EffPotFunctions

 Real(dp), parameter :: MIN_MASS_REL = 0.001

 
 ! totally symmetric functions:
 ! SSS
 ! FFSbar = 2I(x,y,z)
 ! FFVbar = 6I(x,y,z)
 ! VS = 3J(x,y)
 ! SS = J(x,y)
 ! gauge
 
 ! symmetric in first two arguments
 ! FFS
 ! FFV
 ! SSV
 ! VVS
 
Contains 

Complex(dp) Function deltaPS(x,y,z) 
Implicit None
Complex(dp), Intent(in) :: x,y,z
! Real(dp), Intent(in) :: Q2
deltaPS = (x**2 + y**2 + z**2 - 2*x*y - 2*x*z - 2*y*z)
End Function deltaPS

Complex(dp) Function  phiPS(x,y,z) 
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: temp1,temp2

If ((Abs(x).le.Abs(y)).and.(Abs(y).le.Abs(z))) Then
 phiPS =  phiNN(y,x,z) 
Else if  ((Abs(y).lt.Abs(x)).and.(Abs(x).lt.Abs(z))) Then
 phiPS =  phiNN(x,y,z)  
Else if  ((Abs(z).le.Abs(y)).and.(Abs(y).le.Abs(x))) Then
 phiPS =  z/x*phiNN(z,y,x) 
Else if  ((Abs(y).le.Abs(z)).and.(Abs(z).le.Abs(x))) Then
 phiPS = phiNN(x,y,z)
Else if ((Abs(x).le.Abs(z)).and.(Abs(z).le.Abs(y))) Then
 phiPS =  y/z*phiNN(x,z,y) 
 phiPS = phiNN(x,y,z)
Else if ((Abs(z).le.Abs(x)).and.(Abs(x).le.Abs(y))) Then
 phiPS =  y/z*phiNN(z,x,y) 
 phiPS = phiNN(x,y,z)
Else 
 Write(*,*) "unknown order",x,y,z
End if


End Function phiPS

Complex(dp) Function  phiNN(x,y,z) 
Implicit None
Complex(dp), Intent(in) :: x,y,z

phiNN = (Pi**2 - 6._dp*PolyLog(2,(x - y + z - &
     & z*ZSqrt(((x - y)**2 - &
     & 2._dp*(x + y)*z + z**2)/z**2))/(2._dp*z)) - &
     &    6._dp*PolyLog(2,(-x + y + z - z*ZSqrt((x**2 + (y - z)**2 &
     &- 2._dp*x*(y + z))/z**2))/(2._dp*z)) - 3._dp*ZLog(x/z)*ZLog(y/z) + &
     &    6._dp*ZLog((x - y + z - z*ZSqrt((x**2 + (y - z)**2 &
     & - 2._dp*x*(y + z))/z**2))/(2._dp*z))*&
     &     ZLog((-x + y + z - z*ZSqrt((x**2 + (y - z)**2 &
     & - 2._dp*x*(y + z))/z**2))/(2._dp*z)))/(3._dp*Sqrt((x**2 + &
     & (y - z)**2 - 2._dp*x*(y + z))/z**2))

End Function phiNN

! if function is totally symmetric
Subroutine CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(func,m1in,m2in,m3in,Q2,dfunc)
Implicit None
Complex(dp), External :: func
Real(dp), Intent(in) :: m1in,m2in,m3in,Q2
Complex(dp), Intent(out) :: dfunc(3)
Complex(dp) :: m1,m2,m3
m1 = Cmplx(m1in,0.,dp)
m2 = Cmplx(m2in,0.,dp)
m3 = Cmplx(m3in,0.,dp)
dfunc(1) = func(m1,m2,m3,Q2)
dfunc(2) = func(m2,m3,m1,Q2)
dfunc(3) = func(m3,m1,m2,Q2)
End Subroutine CalcLoopFunctionFirstDerivativesArrays_sunrise_sym

! if function is symmetric in first two arguments only
Subroutine CalcLoopFunctionFirstDerivativesArrays_sunrise(func1,func3,m1in,m2in,m3in,Q2,dfunc)
Implicit None
Complex(dp), External :: func1, func3
Real(dp), Intent(in) :: m1in,m2in,m3in,Q2
Complex(dp), Intent(out) :: dfunc(3)
Complex(dp) :: m1,m2,m3
m1 = Cmplx(m1in,0.,dp)
m2 = Cmplx(m2in,0.,dp)
m3 = Cmplx(m3in,0.,dp)
dfunc(1) = func1(m1,m2,m3,Q2)
dfunc(2) = func1(m2,m1,m3,Q2)
dfunc(3) = func3(m1,m2,m3,Q2)
End Subroutine CalcLoopFunctionFirstDerivativesArrays_sunrise

! if function is only symmetric in m1,m2
Subroutine CalcLoopFunctionSecondDerivativesArrays_sunrise(func11,func33,func12,func13,m1in,m2in,m3in,Q2,ddfunc)
Implicit None
Complex(dp), External :: func11, func33, func12, func13
Real(dp), Intent(in) :: m1in,m2in,m3in,Q2
Complex(dp), Intent(out) :: ddfunc(3,3)
Complex(dp) :: m1,m2,m3
m1 = Cmplx(m1in,0.,dp)
m2 = Cmplx(m2in,0.,dp)
m3 = Cmplx(m3in,0.,dp)
ddfunc(1,1) = func11(m1,m2,m3,Q2)
ddfunc(2,2) = func11(m2,m1,m3,Q2)
ddfunc(3,3) = func33(m1,m2,m3,Q2)
ddfunc(1,2) = func12(m1,m2,m3,Q2)
ddfunc(1,3) = func13(m1,m2,m3,Q2)
ddfunc(2,3) = func13(m2,m1,m3,Q2)
ddfunc(2,1) = ddfunc(1,2)
ddfunc(3,1) = ddfunc(1,3)
ddfunc(3,2) = ddfunc(2,3)
End Subroutine CalcLoopFunctionSecondDerivativesArrays_sunrise

Subroutine CalcLoopFunctionSecondDerivativesArrays_sunrise_sym(func11,func12,m1in,m2in,m3in,Q2,ddfunc)
Implicit None
Complex(dp), External :: func11, func12
Real(dp), Intent(in) :: m1in,m2in,m3in,Q2
Complex(dp), Intent(out) :: ddfunc(3,3)
Complex(dp) :: m1,m2,m3
m1 = Cmplx(m1in,0.,dp)
m2 = Cmplx(m2in,0.,dp)
m3 = Cmplx(m3in,0.,dp)
ddfunc(1,1) = func11(m1,m2,m3,Q2)
ddfunc(2,2) = func11(m2,m1,m3,Q2)
ddfunc(3,3) = func11(m3,m2,m1,Q2)
ddfunc(1,2) = func12(m1,m2,m3,Q2)
ddfunc(1,3) = func12(m1,m3,m2,Q2)
ddfunc(2,3) = func12(m2,m3,m1,Q2)
ddfunc(2,1) = ddfunc(1,2)
ddfunc(3,1) = ddfunc(1,3)
ddfunc(3,2) = ddfunc(2,3)
End Subroutine CalcLoopFunctionSecondDerivativesArrays_sunrise_sym


! if function is totally symmetric (always the case for balls topology)
Subroutine CalcLoopFunctionFirstDerivativesArrays_balls(func,m1in,m2in,Q2,dfunc)
Implicit None
Complex(dp), External :: func
Real(dp), Intent(in) :: m1in,m2in,Q2
Complex(dp), Intent(out) :: dfunc(2)
Complex(dp) :: m1,m2
m1 = Cmplx(m1in,0.,dp)
m2 = Cmplx(m2in,0.,dp)
dfunc(1) = func(m1,m2,Q2)
dfunc(2) = func(m2,m1,Q2)
End Subroutine CalcLoopFunctionFirstDerivativesArrays_balls

! if function is totally symmetric
Subroutine CalcLoopFunctionSecondDerivativesArrays_balls(func11,func12,m1in,m2in,Q2,ddfunc)
Implicit None
Complex(dp), External :: func11, func12
Real(dp), Intent(in) :: m1in,m2in,Q2
Complex(dp), Intent(out) :: ddfunc(2,2)
Complex(dp) :: m1,m2
m1 = Cmplx(m1in,0.,dp)
m2 = Cmplx(m2in,0.,dp)
ddfunc(1,1) = func11(m1,m2,Q2)
ddfunc(2,2) = func11(m2,m1,Q2)
ddfunc(1,2) = func12(m1,m2,Q2)
ddfunc(2,1) = ddfunc(1,2)
End Subroutine CalcLoopFunctionSecondDerivativesArrays_balls



! calculates First and Second derivatives of sunrise diagram contribution
Subroutine SecondDerivativeVeff_sunrise(m1,m2,m3,dm1_i,dm2_i,dm3_i,dm1_j,dm2_j,dm3_j,ddm1,ddm2,ddm3,coup,dcoup_i,dcoup_j,& 
&ddcoup,functype,Q2,ddVeff,dVeff_i,dVeff_j)
Implicit None
Real(dp), Intent(in) :: m1,m2,m3,Q2
Complex(dp), Intent(in) :: dm1_i,dm2_i,dm3_i,dm1_j,dm2_j,dm3_j,ddm1,ddm2,ddm3
Complex(dp), Intent(in) :: coup,dcoup_i,dcoup_j,ddcoup
Complex(dp), Intent(out) :: dVeff_i,dVeff_j,ddVeff
Character (Len=6), Intent(in) :: functype
Complex(dp) :: dfunc(3),ddfunc(3,3),Floop
Complex(dp) :: dfunc_vev_i,dfunc_vev_j,ddfunc_vev_ij !  derivatives of floop w.r.t. vevs vi,vj
Integer :: k,l
Complex(dp) :: dm_i(3),dm_j(3),ddm(3),mass1,mass2,dmass1_i,dmass1_j,dmass2_i,dmass2_j,massx,dmassx_i,dmassx_j,ddmassx
Complex(dp) :: ddmass1,ddmass2
dfunc = ZeroC
ddfunc = ZeroC
ddVeff = ZeroC
dVeff_i = ZeroC
dVeff_j = ZeroC
mass1 = sqrt(m1)
mass2 = sqrt(m2)
dm_i = (/dm1_i,dm2_i,dm3_i/)
dm_j = (/dm1_j,dm2_j,dm3_j/)
ddm  = (/ddm1,ddm2,ddm3/)
Select case (functype) 
  case('FFS   ')
    Floop = Fep_FFS(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dFFS_1,dFFS_3,m1,m2,m3,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_sunrise(ddFFS_11,ddFFS_33,ddFFS_12,ddFFS_13,m1,m2,m3,Q2,ddfunc)
!   Write(*,*) "dd", ddfunc(3,3)
  case('FFSbar')
    Floop = Fep_FFSbar(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFSbar_1,m1,m2,m3,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_sunrise_sym(ddFFSbar_11,ddFFSbar_12,m1,m2,m3,Q2,ddfunc)
!   Write(*,*) "ddb", ddfunc(3,3)
  case('SSS   ')
    Floop = Fep_SSS(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dSSS_1,m1,m2,m3,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_sunrise_sym(ddSSS_11,ddSSS_12,m1,m2,m3,Q2,ddfunc) 
  case('FFV   ')
    Floop = Fep_FFV(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dFFV_1,dFFV_3,m1,m2,m3,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_sunrise(ddFFV_11,ddFFV_33,ddFFV_12,ddFFV_13,m1,m2,m3,Q2,ddfunc)
  case('FFVbar')
    Floop = Fep_FFVbar(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFVbar_1,m1,m2,m3,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_sunrise_sym(ddFFVbar_11,ddFFVbar_12,m1,m2,m3,Q2,ddfunc)
  case('SSV   ')
    Floop = Fep_SSV(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dSSV_1,dSSV_3,m1,m2,m3,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_sunrise(ddSSV_11,ddSSV_33,ddSSV_12,ddSSV_13,m1,m2,m3,Q2,ddfunc)
  case('VVS   ')
    Floop = Fep_VVS(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dVVS_1,dVVS_3,m1,m2,m3,Q2,dfunc)
!     Call CalcLoopFunctionSecondDerivativesArrays_sunrise(ddVVS_11,ddVVS_33,ddVVS_12,ddVVS_13,m1,m2,m3,Q2,ddfunc)
  case('gauge ')
    Floop = Fep_gauge(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFSbar_1,m1,m2,m3,Q2,dfunc)
!     Call CalcLoopFunctionSecondDerivativesArrays_sunrise_sym(ddfgauge_11,ddfgauge_12,m1,m2,m3,Q2,ddfunc)
  case default
    write(*,*) "unspecified diagram type"
end select


dfunc_vev_i = (dfunc(1)*dm1_i + dfunc(2)*dm2_i + dfunc(3)*dm3_i)
dfunc_vev_j = (dfunc(1)*dm1_j + dfunc(2)*dm2_j + dfunc(3)*dm3_j)
ddfunc_vev_ij = ZeroC
Do k=1,3
  Do l=1,3
    ddfunc_vev_ij = ddfunc_vev_ij + ddfunc(k,l)*dm_i(k)*dm_j(l)
  End Do
  ddfunc_vev_ij = ddfunc_vev_ij + dfunc(k)*ddm(k)
End Do


! in case of FFS/FFSbar/FFV/FFVbar/SSV the case m1=m2 m3=0 can occur  
!! NO LONGER NECESSARY AND DISABLED
If (SmallD(m1,m2).and.VerySmallM(m3,m1,m2,Q2).and.(.false.)) then
  ! assuming dm1=dm2, ddm1=ddm2
   Select case (functype)
     case('FFS   ')
       dfunc(1) = dFFS_equalzero(Cmplx(m1,0.,dp),Q2)
       ddfunc(1,1) = ddFFS_equalzero(Cmplx(m1,0.,dp),Q2)
       dfunc_vev_i = dfunc(1)*dm1_i + dfunc(3)*dm3_i 
       dfunc_vev_j = dfunc(1)*dm1_j + dfunc(3)*dm3_j
       ddfunc_vev_ij = ddfunc(1,1)*dm1_i*dm1_j + dfunc(1)*ddm1 
     case('FFSbar')
       dfunc(1) = dFFSbar_equalzero(Cmplx(m1,0.,dp),Q2)
       ddfunc(1,1) = ddFFSbar_equalzero(Cmplx(m1,0.,dp),Q2)
       dfunc_vev_i = dfunc(1)*dm1_i
       dfunc_vev_j = dfunc(1)*dm1_j
       ddfunc_vev_ij = ddfunc(1,1)*dm1_i*dm1_j + dfunc(1)*ddm1
     case('FFV   ')
       dfunc(1) = dFFV_equalzero(Cmplx(m1,0.,dp),Q2)
       ddfunc(1,1) = ddFFV_equalzero(Cmplx(m1,0.,dp),Q2)
       dfunc_vev_i = dfunc(1)*dm1_i
       dfunc_vev_j = dfunc(1)*dm1_j
       ddfunc_vev_ij = ddfunc(1,1)*dm1_i*dm1_j !+ dfunc(1)*ddm1
     case('FFVbar')
       dfunc(1) = dFFVbar_equalzero(Cmplx(m1,0.,dp),Q2)
       ddfunc(1,1) = ddFFVbar_equalzero(Cmplx(m1,0.,dp),Q2)
       dfunc_vev_i = dfunc(1)*dm1_i
       dfunc_vev_j = dfunc(1)*dm1_j
       ddfunc_vev_ij = ddfunc(1,1)*dm1_i*dm1_j !+ dfunc(1)*ddm1
     case('SSV   ')
       dfunc(1) = dSSV_equalzero(Cmplx(m1,0.,dp),Q2)
       ddfunc(1,1) = ddSSV_equalzero(Cmplx(m1,0.,dp),Q2)
       dfunc_vev_i = dfunc(1)*dm1_i
       dfunc_vev_j = dfunc(1)*dm1_j
       ddfunc_vev_ij = ddfunc(1,1)*dm1_i*dm1_j + dfunc(1)*ddm1
   end select
   
end if   


! derivatives of mass product
! V = coup * mass1 * mass2 * fLoop
If ((functype.eq."FFSbar").or.(functype.eq."FFVbar")) Then


 mass1 = sqrt(m1) ! not-squared masses
 mass2 = sqrt(m2)
 If (mass1.ne.ZeroC) Then
  dmass1_i = dm1_i/(2*mass1) ! derivatives of not-squared masses
  dmass1_j = dm1_j/(2*mass1)
  ddmass1 = - dm1_j*dm1_i/(4._dp*mass1**3) + ddm1/(2._dp*mass1)
 Else
  dmass1_i = 0._dp
  dmass1_j = 0._dp
  ddmass1 = 0._dp
 End If
 If (mass2.ne.ZeroC) Then
  dmass2_i = dm2_i/(2*mass2)
  dmass2_j = dm2_j/(2*mass2)
  ddmass2 = - dm2_j*dm2_i/(4._dp*mass2**3) + ddm2/(2._dp*mass2)
 Else
  dmass2_i = 0._dp
  dmass2_j = 0._dp
  ddmass2 = 0._dp
 End If
 massx = mass1*mass2
 dmassx_i = dmass1_i*mass2 + mass1*dmass2_i ! first derivative
 dmassx_j = dmass1_j*mass2 + mass1*dmass2_j
 ddmassx = ddmass1*mass2 + mass1*ddmass2 + dmass1_i*dmass2_j + dmass1_j*dmass2_i ! second der.
 
 dVeff_i = dcoup_i*massx*Floop &
 & + coup*dmassx_i*Floop &
 & + coup*massx*dfunc_vev_i
 
 dVeff_j = dcoup_j*massx*Floop &
 & + coup*dmassx_j*Floop &
 & + coup*massx*dfunc_vev_j
 
 ddVeff = ddcoup*massx*Floop &
 & + coup*ddmassx*Floop &
 & + coup*massx*ddfunc_vev_ij &
 & + (dcoup_i*dmassx_j + dcoup_j*dmassx_i)*Floop &
 & + (dcoup_i*massx + coup*dmassx_i)*dfunc_vev_j &
 & + (dcoup_j*massx + coup*dmassx_j)*dfunc_vev_i
 
Else

! V = coup * Floop 
 dVeff_i = dcoup_i*Floop + coup*dfunc_vev_i
 
 dVeff_j = dcoup_j*Floop + coup*dfunc_vev_j
 
 ddVeff = ddcoup*Floop + coup*ddfunc_vev_ij &
 & + dcoup_i*dfunc_vev_j + dcoup_j*dfunc_vev_i
End If


End Subroutine SecondDerivativeVeff_sunrise

Subroutine SecondDerivativeVeff_balls(m1,m2,dm1_i,dm2_i,dm1_j,dm2_j,ddm1,ddm2,coup,dcoup_i,dcoup_j,ddcoup,functype,Q2,&
&ddVeff,dVeff_i,dVeff_j)
Implicit None
Real(dp), Intent(in) :: m1,m2, Q2
Complex(dp), Intent(in) :: coup,dcoup_i,dcoup_j,ddcoup,dm1_i,dm2_i,dm1_j,dm2_j,ddm1,ddm2
Complex(dp), Intent(out) :: ddVeff,dVeff_i,dVeff_j
Character (Len=2), Intent(in) :: functype
Complex(dp) :: dfunc(2),ddfunc(2,2),Floop
Complex(dp) :: dfunc_vev_i,dfunc_vev_j,ddfunc_vev_ij
Integer :: k,l
Complex(dp) :: dm_i(2),dm_j(2),ddm(2)
dfunc = ZeroC
ddVeff = ZeroC
dVeff_i = ZeroC
dVeff_j = ZeroC
dm_i = (/dm1_i,dm2_i/)
dm_j = (/dm1_j,dm2_j/)
ddm  = (/ddm1,ddm2/)
Select case (functype) 
  case('SS')
    Floop = Fep_SS(m1,m2,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_balls(dSS_1,m1,m2,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_balls(ddSS_11,ddSS_12,m1,m2,Q2,ddfunc)
  case('VS')
    Floop = Fep_VS(m1,m2,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_balls(dVS_1,m1,m2,Q2,dfunc)
    Call CalcLoopFunctionSecondDerivativesArrays_balls(ddVS_11,ddVS_12,m1,m2,Q2,ddfunc)
  case default
    write(*,*) "unspecified diagram type"
end select

dfunc_vev_i = (dfunc(1)*dm1_i + dfunc(2)*dm2_i)
dfunc_vev_j = (dfunc(1)*dm1_j + dfunc(2)*dm2_j)
ddfunc_vev_ij = ZeroC
Do k=1,2
  Do l=1,2
    ddfunc_vev_ij = ddfunc_vev_ij + ddfunc(k,l)*dm_i(k)*dm_j(l)
  End Do
  ddfunc_vev_ij = ddfunc_vev_ij + dfunc(k)*ddm(k)
End Do

ddVeff = ddcoup * Floop + coup * ddfunc_vev_ij &
& + dcoup_i * dfunc_vev_j + dcoup_j * dfunc_vev_i

! calculate dVeff too, because all the parts are already there
dVeff_i = (dcoup_i*Floop + coup*dfunc_vev_i)
dVeff_j = (dcoup_j*Floop + coup*dfunc_vev_j)
End Subroutine SecondDerivativeVeff_balls
 
Subroutine FirstDerivativeVeff_sunrise(m1,m2,m3,dm1,dm2,dm3,coup,dcoup,functype,Q2,dVeff)
Implicit None
Real(dp), Intent(in) :: m1,m2,m3, Q2
Complex(dp), Intent(in) :: coup,dcoup,dm1,dm2,dm3
Complex(dp), Intent(out) :: dVeff
Character (Len=6), Intent(in) :: functype
Complex(dp) :: dfunc(3),Floop,dFloop,dmass1,dmass2,mass1,mass2
dVeff = ZeroC
dfunc = ZeroC
mass1 = ZeroC
mass2 = ZeroC
Select case (functype) 
  case('FFS   ')
    Floop = Fep_FFS(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dFFS_1,dFFS_3,m1,m2,m3,Q2,dfunc)
  case('FFSbar')
    Floop = Fep_FFSbar(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFSbar_1,m1,m2,m3,Q2,dfunc)
  case('SSS   ')
    Floop = Fep_SSS(m1,m2,m3,Q2)
    Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFSbar_1,m1,m2,m3,Q2,dfunc)
  case('FFV   ')
    Floop = Fep_FFV(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dFFV_1,dFFV_3,m1,m2,m3,Q2,dfunc)
  case('FFVbar')
    Floop = Fep_FFVbar(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFSbar_1,m1,m2,m3,Q2,dfunc)
  case('SSV   ')
    Floop = Fep_SSV(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dSSV_1,dSSV_3,m1,m2,m3,Q2,dfunc)
  case('VVS   ')
    Floop = Fep_VVS(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise(dVVS_1,dVVS_3,m1,m2,m3,Q2,dfunc)
  case('gauge ')
    Floop = Fep_gauge(m1,m2,m3,Q2)
!     Call CalcLoopFunctionFirstDerivativesArrays_sunrise_sym(dFFSbar_1,m1,m2,m3,Q2,dfunc)
  case default
    write(*,*) "unspecified diagram type"
end select

dFloop = (dfunc(1)*dm1+dfunc(2)*dm2+dfunc(3)*dm3)
dVeff = dcoup * Floop + coup * dFloop ! product rule

! V = coup * mass1 * mass2 * fLoop
If ((functype.eq."FFSbar").or.(functype.eq."FFVbar")) Then
 If (mass1.ne.ZeroC) Then
  mass1 = sqrt(m1)
  dmass1 = dm1/(2*mass1)
 End If
 If (mass2.ne.ZeroC) Then
  mass2 = sqrt(m2)
  dmass2 = dm2/(2*mass2)
 End If
 dVeff = dcoup* mass1*mass2*Floop &
 & + coup * (dmass1*mass2+mass1*dmass2) * Floop &
 & + coup * mass1*mass2 * dFloop
End If

End Subroutine FirstDerivativeVeff_sunrise

Subroutine FirstDerivativeVeff_balls(m1,m2,dm1,dm2,coup,dcoup,functype,Q2,dVeff)
Implicit None
Real(dp), Intent(in) :: m1,m2,Q2
Complex(dp), Intent(in) :: coup,dcoup,dm1,dm2
Complex(dp), Intent(out) :: dVeff
Character (Len=2), Intent(in) :: functype
Complex(dp) :: dfunc(2),Floop
dfunc = ZeroC
dVeff = ZeroC
Select case (functype) 
  case('SS')
    Floop = Fep_SS(m1,m2,Q2)
    dfunc(1) = dSS_1(m1,m2,Q2)
    dfunc(2) = dSS_1(m2,m1,Q2) ! symmetric in m1,m2
  case('VS')
    Floop = Fep_VS(m1,m2,Q2)
    dfunc(1) = dVS_1(m1,m2,Q2)
    dfunc(2) = dVS_1(m2,m1,Q2) ! symmetric in m1,m2
  case default
    write(*,*) "unspecified diagram type"
end select

dVeff = dcoup * Floop + &
& coup * (dfunc(1)*dm1+dfunc(2)*dm2)
End Subroutine FirstDerivativeVeff_balls


 
Complex(dp) Function PolyLog(n,z)
Implicit None
Integer, Intent(in) :: n
Complex(dp), Intent(in) :: z
If (n.eq.2) Then
PolyLog = CLI2_mod(z)
Else
PolyLog = ZeroC
write(*,*) 'PolyLog(n,z) for n>2 not implemented!'
End If
End Function PolyLog


! #######################
! ####### FFS
! #######################

! derivatives created by Wolfram Mathematica 9

! 1st derivative, 1st argument (x)
Complex(dp) Function dFFS_1(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

dFFS_1 = dJ2x_1(x,y,Q2) - dJ2x_1(x,z,Q2) + I_SMartinC(x,y,z,Q2) &
& + (x+y-z)*dI_1(x,y,z,Q2)
If (dFFS_1.ne.dFFS_1) then
  write(*,*) "NaN appearing in dFFS_1"
End if
End Function

! 1st derivative, 3rd argument (z)
Complex(dp) Function dFFS_3(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

dFFS_3 = -dJ2x_1(z,x,Q2) - dJ2x_1(z,y,Q2) - I_SMartinC(x,y,z,Q2) &
& + (x+y-z)*dI_1(z,x,y,Q2)
If (dFFS_3.ne.dFFS_3) then
!   write(*,*) "NaN appearing in dFFS_3"
End if

End Function dFFS_3

! 2nd derivative, arguments (x,x)
Complex(dp) Function ddFFS_11(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

ddFFS_11 = ddJ2x_11(x,y,Q2)-ddJ2x_11(x,z,Q2)+2*dI_1(x,y,z,Q2)+(x+y-z)*ddI_11(x,y,z,Q2)
If (ddFFS_11.ne.ddFFS_11) then
!   write(*,*) "NaN appearing in ddFFS_11"
End if

End Function ddFFS_11

! 2nd derivative, arguments (z,z)
Complex(dp) Function ddFFS_33(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

ddFFS_33 = -ddJ2x_11(z,x,Q2)-ddJ2x_11(z,y,Q2)-2*dI_1(z,x,y,Q2)+(x+y-z)*ddI_11(z,x,y,Q2)
! If (abs(ddFFS_33).gt.100000._dp) Write(*,*) "33", ddFFS_33, (x+y-z)*ddI_11(z,x,y,Q2)
If (ddFFS_33.ne.ddFFS_33) then
!   write(*,*) "NaN appearing in ddFFS_33"
End if

End Function ddFFS_33

! 2nd derivative, arguments (x,y)
Complex(dp) Function ddFFS_12(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

ddFFS_12 = ddJ2x_12(x,y,Q2) + dI_1(y,x,z,Q2) + dI_1(x,y,z,Q2) + (x+y-z)*ddI_12(x,y,z,Q2)
If (ddFFS_12.ne.ddFFS_12) then
!   write(*,*) "NaN appearing in ddFFS_12"
End if
End Function ddFFS_12

! 2nd derivative, arguments (x,z)
Complex(dp) Function ddFFS_13(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

ddFFS_13 = -ddJ2x_12(x,z,Q2)+dI_1(z,x,y,Q2)-dI_1(x,y,z,Q2)+(x+y-z)*ddI_12(x,z,y,Q2)
If (ddFFS_13.ne.ddFFS_13) then
!   write(*,*) "NaN appearing in ddFFS_13"
End if
End Function ddFFS_13

! #######################
! ####### FFV
! #######################


! for special case m1=m2 and m3=0 only !!!
Complex(dp) function dFFV_equalzero(xin,Q2)
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res,x
x = xin
If (VerySmallM(Real(xin,dp),Q2)) then
  dFFV_equalzero = ZeroC
else 
  dFFV_equalzero = -4._dp*x+8._dp*x*(-1._dp+ZLOG(x/Q2))
end if
end function dFFV_equalzero

! for special case m1=m2 and m3=0 only !!!
Complex(dp) function ddFFV_equalzero(xin,Q2)
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res,x
x = xin
If (VerySmallM(Real(xin,dp),Q2)) then
  ddFFV_equalzero = ZeroC
else 
  ddFFV_equalzero = 4._dp+8._dp*(-1._dp+ZLOG(x/Q2))
end if
end function ddFFV_equalzero



Complex(dp) Function dFFV_1(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) Then ! f_x(x,y,0)
  If (VerySmallM(x,y,z,Q2)) Then ! f_x(0,y,0)
    res = ZeroC
  Else ! f_x(x,y,0)
    res = 2._dp*x-2._dp*(x+y)+4._dp*x*(-1._dp+ZLog(x/Q2))
  end if
Else ! z!=0
  If (SmallD(x,y)) then ! f_x(x,x,0)
    res = (z*I_SMartinC(x,x,z,Q2)+z*(-((2*z+x*ZLOG(x/Q2))*(-1+ZLOG(z/Q2)))+ZLOG(x/Q2)*(-&
    &3*x+2*z+2*x*ZLOG(x/Q2)+(x-2*z)*ZLOG(z/Q2)))+(2*x*z-2*z**2)*dI_1(x,x,z,Q2))/z
  else 
    ! f_x(x,y,0)
    res = (2*(-x+y)*I_SMartinC(x,y,ZeroC,Q2)+(2*x-2*y+z)*I_SMartinC(x,y,&
    &z,Q2)+z*(-((x-y+2*z+&
    &y*ZLOG(y/Q2))*(-1+ZLOG(z/Q2)))+ZLOG(x/Q2)*(-2*x-y+2*z+2*y*ZLOG(y/Q2)&
    &+(2*x-y-2*z)*ZLOG(z/Q2)))-(x-y)**2*dI_1(x,y,ZeroC,Q2)&
    &+((x-y)**2+(x+y)*z-2*z**2)*dI_1(x,y,z,Q2))/z
  end if
End if
If (res.ne.res) write(*,*) "NaN appearing in dFFV_1 for input ",Real(x),Real(y),Real(z)
dFFV_1 = res
End Function dFFV_1

Complex(dp) Function dFFV_3(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin
Call SortTwoArgumentsC(x,y)
If (VerySmallM(zin,xin,yin,Q2)) Then ! f_z(x,y,0)
  If (VerySmallM(x,y,z,Q2)) Then ! f_z(0,y,0)
    res = ZeroC
  Else ! f_z(x,y,0)
    res = ZeroC
  end if
Else ! z!=0
  If (SmallD(x,y)) then ! f_x(x,x,z)
    res = (z*I_SMartinC(x,x,z,Q2)+z*(-((2*z+x*ZLOG(x/Q2))*(-1+ZLOG(z/Q2)))+ZLOG(x/Q2)*(-&
    &3*x+2*z+2*x*ZLOG(x/Q2)+(x-2*z)*ZLOG(z/Q2)))+(2*x*z-2*z**2)*dI_1(x,x,z,Q2))/z
  else 
    ! f_z(x,y,z)
    res = (3*(x-y)**2*I_SMartinC(x,y,ZeroC,Q2)-3*((x-y)**2+2*z**2)*I_SMartinC(x,y,z,Q2)+z*(-3*(x-&
    &y)**2-2*z**2+4*z**2*ZLOG(z/Q2)+3*x*ZLOG(x/Q2)*(x-y-2*z*ZLOG(z/Q2))&
    &+3*y*ZLOG(y/Q2)*(-x+y-2*z*ZLOG(z/Q2))+3*((x-y)**2+(x+y)*z-2*z**2)&
    &*dI_1(z,x,y,Q2)))/(3.*z**2)
  end if
End if
If (res.ne.res) write(*,*) "NaN appearing in dFFV_3 for input ",Real(x),Real(y),Real(z)
dFFV_3 = res
End Function dFFV_3

Complex(dp) Function ddFFV_11(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(zin,x,y,Q2)) Then ! f_xx(x,y,0)
  If (VerySmallM(x,y,z,Q2)) Then ! f_xx(0,y,0)
    res = ZeroC
  Else ! f_xx(x,y,0)
    res = 4._dp*ZLOG(x/Q2)
  end if
Else
    ! f_xx(x,y,z)
    res = (-2*x*I_SMartinC(x,y,ZeroC,Q2)+2*x*I_SMartinC(x,y,z,Q2)+z*(-x-y+2*z+2*y*&
    &ZLOG(y/Q2)+2*x*ZLOG(x/Q2)&
    &*(-1+ZLOG(z/Q2))+(x-y-2*z)*ZLOG(z/Q2))+x*(4*(-x+y)*I_SMartinC(x,y,ZeroC,Q2)&
    &+2*(2*x-2*y+z)*I_SMartinC(x,y,z,Q2)-(x-y)&
    &**2*ddI_11(x,y,ZeroC,Q2)+((x-y)**2+(x+y)*z-2*z**2)*ddI_11(x,y,z,Q2)))/(x*z)
End if
If (res.ne.res) write(*,*) "NaN appearing in ddFFV_11 for input ",Real(x),Real(y),Real(z)
ddFFV_11 = res
End Function ddFFV_11

Complex(dp) Function ddFFV_33(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin
Call SortTwoArgumentsC(y,z)
If (VerySmallM(y,x,z,Q2)) Then ! f_zz(x,y,0)
  If (VerySmallM(x,y,z,Q2)) Then ! f_zz(0,y,0)
!  Write(*,*) 1
    res = ZeroC
  Else ! f_zz(x,y,0)
    res = ZeroC
  end if
Else ! z!=0
  If (SmallD(x,y)) then ! f_zz(x,x,z)
      res = (2*(z-6*x*ZLOG(x/Q2)+2*z*ZLOG(z/Q2)-6*z*dI_1(z,x,x,Q2)&
      &+3*(x-z)*z*ddI_11(z,x,x,Q2)))/(3.*z)
  else 
      ! f_zz(x,y,z)
      res = (-6*(x-y)**2*I_SMartinC(x,y,ZeroC,Q2)+6*(x-y)**2*I_SMartinC(x,y,z,Q2)+z*(3*(x-y)**2+2*z**2-&
      &3*x*(x-y+2*z)*ZLOG(x/Q2)-3*y*(-x+y+2*z)*ZLOG(y/Q2)+4*z**2*ZLOG(z/Q2)&
      &-6*((x-y)**2+2*z**2)*dI_1(z,x,y,Q2)+3*z*((x-y)**2+&
      &(x+y)*z-2*z**2)*ddI_11(z,x,y,Q2)))/(3.*z**3)
  end if
End if
If (res.ne.res) write(*,*) "NaN appearing in ddFFV_33 for input ",Real(x),Real(y),Real(z)
ddFFV_33 = res
End Function ddFFV_33

Complex(dp) Function ddFFV_12(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in):: xin,yin,zin 
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin
Call SortTwoArgumentsC(x,y)
If (VerySmallM(zin,x,y,Q2)) Then ! f_xy(x,y,0)
    res = -2._dp
Else ! z!=0
  If (SmallD(x,y)) then ! f_xy(x,x,z)
    res = (2*z+2*I_SMartinC(x,x,ZeroC,Q2)-2*I_SMartinC(x,x,z,Q2)+4*z*(-1+ZLOG(x/Q2))+2*z*(-1+ZLOG(x/Q2))&
    &**2-2*z*(-1+ZLOG(z/Q2))-2*z*(-1+ZLOG(x/Q2))*(-1+ZLOG(z/Q2))+z*&
    &dI_1(x,x,z,Q2)+z*dI_1(x,x,z,Q2)+(2*x**2+x*z-2*z**2+&
    &x*(-2*x+z))*ddI_12(x,x,z,Q2))/z
  else 
    ! f_xy(x,y,z)
    res = (2*I_SMartinC(x,y,ZeroC,Q2)-2*I_SMartinC(x,y,z,Q2)+z*(ZLOG(x/Q2)*(1+2*ZLOG(y/Q2)-ZLOG(z/Q2))&
    &-ZLOG(y/Q2)*(-1+ZLOG(z/Q2)))+2*(-x+y)*dI_1(y,x,ZeroC,Q2)&
    &+(2*x-2*y+z)*dI_1(y,x,z,Q2)+2*x*dI_1&
    &(x,y,ZeroC,Q2)-2*y*dI_1(x,y,ZeroC,Q2)-2*x*dI_1(x,&
    &y,z,Q2)+2*y*dI_1(x,y,z,Q2)+z*dI_1(x,y,z,Q2)&
    &-x**2*ddI_12(x,y,ZeroC,Q2)+2*x*y*ddI_12(x,y,zeroC,Q2)&
    &-y**2*ddI_12(x,y,ZeroC,Q2)+((x-y)**2+(x+y)*z-2*z**2)&
    &*ddI_12(x,y,z,Q2))/z
  end if
End if
If (res.ne.res) write(*,*) "NaN appearing in ddFFV_12 for input ",Real(x),Real(y),Real(z)
ddFFV_12 = res
End Function ddFFV_12

Complex(dp) Function ddFFV_13(x,y,z,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in):: x,y,z 
Complex(dp) :: res
If (VerySmallM(z,x,y,Q2)) Then 
    res = ZeroC
Else ! z!=0
  If (VerySmallM(x,y,z,Q2)) then
    res = ZeroC
  else
    If (VerySmallM(y,x,z,Q2)) then
      res = ZeroC
    else
      ! f_xz(x,y,z)
    res = (2*(x-y)*I_SMartinC(x,y,ZeroC,Q2)+2*(-x+y)*I_SMartinC(x,y,z,Q2)+z*(-x+y-y*ZLOG(y/Q2)-&
    &2*z*ZLOG(z/Q2)+ZLOG(x/Q2)*(2*x-y-2*z*ZLOG(z/Q2)))+2*x*z*&
    &dI_1(z,x,y,Q2)-2*y*z*dI_1(z,x,y,Q2)+z**2*&
    &dI_1(z,x,y,Q2)+x**2*dI_1(x,y,ZeroC,Q2)-2*x*y*&
    &dI_1(x,y,ZeroC,Q2)+y**2*dI_1(x,y,ZeroC,Q2)-x**2*&
    &dI_1(x,y,z,Q2)+2*x*y*dI_1(x,y,z,Q2)-y**2*&
    &dI_1(x,y,z,Q2)-2*z**2*dI_1(x,y,z,Q2)+z*((x-y)**2+(x+&
    &y)*z-2*z**2)*ddI_12(x,z,y,Q2))/z**2
    end if
  end if
End if
If (res.ne.res) write(*,*) "NaN appearing in ddFFV_13 for input ",Real(x),Real(y),Real(z)
ddFFV_13 = res
End Function ddFFV_13

! #######################
! ####### SSV
! #######################

Complex(dp) Function dSSV_equalzero(xin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin
Complex(dp) :: res,x
x = xin


res = 6*I_SMartinC(x,x,ZeroC,Q2)+3*dJ2x_1(x,x,Q2)+3*dJ2x_1(x,x,Q2)+&
&2*x*(6-4*ZLOG(x/Q2)+3*dI_1(x,x,ZeroC,Q2)+3*&
&dI_1(x,x,ZeroC,Q2))


dSSV_equalzero = res
end function dSSV_equalzero


Complex(dp) Function ddSSV_equalzero(xin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin
Complex(dp) :: res,x
x = xin

res = 4._dp-8._dp*ZLOG(x/Q2)+3*(ddJ2x_11(x,x,Q2)+2*ddJ2x_12(x,x,Q2)&
 &+ddJ2x_11(x,x,Q2))+12*(dI_1(x,x,ZeroC,Q2)+&
&dI_1(x,x,ZeroC,Q2))+6*x*(ddI_11(x,x,ZeroC,Q2)+2*&
&ddI_12(x,x,ZeroC,Q2)+ddI_11(x,x,ZeroC,Q2))

res = 8 + 12*dI_equalzero(x,Q2) + 6*x*ddI_equalzero(x,Q2) &
    & + 6*dJ(x,Q2)**2 + 6*J_SMartinC(x,Q2)*ddJ(x,Q2) - 8*dJ(x,Q2) - 4*x*ddJ(x,Q2)



ddSSV_equalzero = res
end function ddSSV_equalzero




Complex(dp) Function dSSV_1(xin,yin,zin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) then ! z=0
    res = 4*x+2*y+3*I_SMartinC(x,y,ZeroC,Q2)-4*x*ZLOG(x/Q2)+3*dJ2x_1(x,y,Q2)+3*(x+&
    &y)*dI_1(x,y,ZeroC,Q2)

else ! z not 0
  res = ZeroC
  write(*,*) 'derivative of SSV w. massive vector not implemented!'
end if

dSSV_1 = res
end function dSSV_1


Complex(dp) Function dSSV_3(xin,yin,zin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) then ! z=0
    res = ZeroC

else ! z not 0
  res = ZeroC
  write(*,*) 'derivative of SSV w. massive vector not implemented!'
end if

dSSV_3 = res
end function dSSV_3


Complex(dp) Function ddSSV_11(xin,yin,zin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) then ! z=0
    res = -4*ZLOG(x/Q2)+3*ddJ2x_11(x,y,Q2)+6*dI_1(x,y,&
&ZeroC,Q2)+3*(x+y)*ddI_11(x,y,ZeroC,Q2)

else ! z not 0
  res = ZeroC
  write(*,*) 'derivative of SSV w. massive vector not implemented!'
end if

ddSSV_11 = res
end function ddSSV_11


Complex(dp) Function ddSSV_33(xin,yin,zin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) then ! z=0
    res = ZeroC
else ! z not 0
  res = ZeroC
  write(*,*) 'derivative of SSV w. massive vector not implemented!'
end if

ddSSV_33 = res
end function ddSSV_33

Complex(dp) Function ddSSV_12(xin,yin,zin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) then ! z=0
    res = 2+3*ddJ2x_12(x,y,Q2)+3*dI_1(y,x,ZeroC,Q2)+3*&
&dI_1(x,y,ZeroC,Q2)+3*(x+y)*ddI_12(x,y,ZeroC,Q2)

else ! z not 0
  res = ZeroC
  write(*,*) 'derivative of SSV w. massive vector not implemented!'
end if

ddSSV_12 = res
end function ddSSV_12

Complex(dp) Function ddSSV_13(xin,yin,zin,Q2)
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: xin,yin,zin
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

If (VerySmallM(z,x,y,Q2)) then ! z=0
    res = ZeroC

else ! z not 0
  res = ZeroC
  write(*,*) 'derivative of SSV w. massive vector not implemented!'
end if

ddSSV_13 = res
end function ddSSV_13

! #######################
! ####### VVS
! #######################

! #######################
! ####### gauge / VVV
! #######################

! #######################
! ####### I(x,y,z) derivatives, J(x,y) and J(x)
! #######################

!! symmetric in y,z variables
Complex(dp) Function dI_1(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

Call SortTwoArgumentsC(y,z) 
! now y < z (real part)

res = ZeroC
If (VerySmallM(x,y,z,Q2)) Then ! x = 0
 If (SmallD(y,z)) Then  ! 
   res = 0._dp  
 Else If (SmallM(y,x,z,Q2)) Then ! f_x(x,0,a) | x->0
  res = -0.5_dp + Pi**2/6._dp + ZLog(z/Q2)**2/2._dp
 Else ! f_x(x,a,b) | x->0
   res = -((3 + Pi**2)*y + (-3 + Pi**2)*z + 3*(y - z)*(2*Log(1 - y/z) - & 
    & Log(y/Q2)*(-1 + Log(z/Q2)) + Log(z/Q2)) - 6*(y + z)*PolyLog(2,y/z))/(6.*(y - z))  
! Using II function
  res = -(3._dp*y + Pi**2*y - 3._dp*z + Pi**2*z - 3._dp*(y - z)*zLog(y/Q2)*(-1._dp + zLog(z/Q2)) &
   & + 3._dp*y*zLog(z/Q2) - 3._dp*z*zLog(z/Q2) - 6._dp*(y + z)*PolyLog(2,y/z))/(6._dp*(y - z))
 End If


Else if (SmallM(x,y,z,Q2)) Then ! x small 
 If (SmallM(z,x,y,Q2)) Then
  res = 0._dp
 Else If (SmallM(y,x,z,Q2)) Then 
  res = (-3._dp + Pi**2 - 6._dp*Log(x/Q2)*(-1._dp + Log(z/Q2)) + 3._dp*Log(z/Q2)**2)/6._dp
 Else
  If (SmallD(y,z)) Then 
   res = (3._dp + ZLog(y/Q2)*(2 - 2._dp*ZLog(x/Q2) + ZLog(y/Q2)))/2._dp
  Else
   res = ((-3._dp + Pi**2)*y + (3._dp + Pi**2)*z - 6._dp*(y + z)*PolyLog(2,z/y) &
    &  - 6._dp*ZLog(x)*(-y + z + y*ZLog(y/Q2)) - &
    &  3._dp*(y + z)*(ZLog(y/Q2)**2 - 2._dp*ZLog((y - z)/Q2)*ZLog(y/z)) + &
    & 6._dp*(z*ZLog(x) + y*ZLog(y/Q2))*ZLog(z/Q2))/(6._dp*(y - z))
  End if
 End if



Else  ! x large
  If (SmallM(y,x,z,Q2)) Then
    If (SmallM(z,x,y,Q2)) Then
      ! f_x(x,0,0)
      res = -0.5_dp-Pi**2/6._dp+ZLog(x/Q2)-ZLog(x/Q2)**2/2._dp
    Else If (SmallD(x,z)) then       ! f_1(x,0,x)
        res = -(-1._dp + zLog(x/Q2))**2/2._dp
    else  ! f_x(x,0,z))
        res=-(x - 2*(x + z)*zLog(x/q2) + x*zLog(x/q2)**2 + 2*z*zLog(z/q2) &
           & - 2*z*zLog(z/x) + 2*x*PolyLog(2,1 - z/x))/(2._dp*x)
    End If
  Else
      ! f_x(x,y,z)
      !res = -(x+(x+y-z)*ZLOG(y/Q2)+(x-y+z-x*ZLOG(y/Q2))*ZLOG(z/Q2)+x*ZLOG(x/Q2)&
     ! &*(-4._dp+ZLOG(y/Q2)+ZLOG(z/Q2))+x*dXi_1(x,y,z))/(2._dp*x)

!! NEW FUNCTION BY FS

res = (x*(-x + y + z)*phiPS(x,y,z) - z*(x + x*log(x/y) + &
&x*log(y/Q2) + y*log(y/Q2) - z*log(y/Q2) + x*log(x/z) + &
&x*log(z/Q2) - y*log(z/Q2) + &
&    z*log(z/Q2) - x*log(y/Q2)*log(z/Q2) +&
& x*log(x/Q2)*(-4._dp + log(y/Q2) + log(z/Q2)) + (y - z)*log(z/y)))/(2._dp*x*z)

! If (writeoutscreen) Write(*,*) real(x,dp),Real(y,dp),Real(z,dp), Abs(x/y), Abs(x/z), Abs(y/z)
 End if
End If

If (res.ne.res) write(*,*) "NaN appearing in dI_1 for input ",Real(x),Real(y),Real(z)
dI_1 = res
End Function dI_1





Complex(dp) function ddI_equalzero(xin,Q2)
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res,x
x = xin

If (VerySmallM(Real(xin,dp),Q2)) then
  res = ZeroC
else 
   res = (2._dp - 2._dp*ZLOG(x/Q2))/x
end if

ddI_equalzero = res
End function ddI_equalzero

Complex(dp) function dI_equalzero(xin,Q2)
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res,x
x = xin

If (VerySmallM(Real(xin,dp),Q2)) then
  res = ZeroC
else 
  res = -1+2*ZLOG(x/Q2)-ZLOG(x/Q2)**2
end if

dI_equalzero = res
End function dI_equalzero

Complex(dp) Function ddI_11(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res,x,y,z
x = xin
y = yin
z = zin

Call SortTwoArgumentsC(y,z)

res = ZeroC
If (VerySmallM(x,y,z,Q2)) Then ! x=0
 If (SmallD(z,y)) Then  ! y=z
  If (SmallM(z,x,y,Q2)) Then ! f_xx(x,0,0) | x->0
    res = 0._dp
  Else ! f_xx(x,a,a) | x->0
    res = 0._dp
  End if
 Else
  If (SmallM(y,x,z,Q2)) Then ! f_xx(x,0,a) | x->0
   res = -2/z + (3*ZLog(z/Q2))/(2._dp*z)
  Else ! f_xx(x,a,b) | x->0
   res=  (-12*y**2 - 4*Pi**2*y*z + 12*z**2 + 24*y*z*PolyLog(2,y/z) + (9*y**2 - &
& 6*y*z - 3*z**2)*ZLog(y/Q2) + 3*y**2*ZLog(z/Q2) + 6*y*z*ZLog(z/Q2) - &
& 9*z**2*ZLog(z/Q2))/(6._dp*(y - z)**3)
  End if
 End if
Else if (SmallM(x,y,z,Q2)) Then ! x small
 If (SmallD(y,z)) then ! y=z
  If (VerySmallM(y,z,z,Q2)) Then ! y=z=0
   res = (1-zlog(x/Q2))/x ! derived from I(0,0,x) (2.28 in hep-ph/0111209)
  else ! y=z not zeroC
   res = -zlog(y/Q2)/x ! derived from (*)
  end if
 else If (VerySmallM(y,z,x,Q2)) Then ! y=0
  res = (1 - zLog(z/Q2))/x ! also derived from (*)
 else ! y != z, both large
  res = (y - z - y*ZLog(y/Q2) + z*ZLog(z/Q2))/(x*(y - z)) ! eq. (*)
 end if
Else
  If (SmallM(y,x,z,Q2)) Then
    If (SmallM(z,x,y,Q2)) Then
      ! f_xx(x,0,0)
      res = (1-zLog(x/Q2))/x
    Else
      If (SmallD(x,z)) then
           res =-(zLog(x/Q2)/x)
      else
	! f_xx (x,0,z)
	res = (1.*x**2-1.*x*z+(1.*x**2-1.*z**2)*Log(x/Q2)+(-1.*x**2+1.*z**2)&
	&*Log((x-1.*z)/Q2)-1.*x**2*Log(x/z)-1.*x**2*Log(z/Q2)+1.*x*z*Log(z/Q2)&
	&+1.*x**2*Log(1.-(1.*z)/x)-1.*z**2*Log(1.-(1.*z)/x))/(x**2*(x-1.*z))
      end if
    End If
  Else
!    res = -(-4._dp*x+(x-y+z)*ZLOG(y/Q2)+(x+y-z)*ZLOG(z/Q2)+x**2._dp*&
!    & ddXi_11(x,y,z))/(2._dp*x**2._dp)

!! NEW FUNCTION BY FS
 res = (x*(x - y - z)*(x*(x - y - z)*phiPS(x,y,z) - x*z*(Zlog(x/y) &
  &  + Zlog(x/z)) + z*(-y + z)*Zlog(z/y)) &
  &   -  deltaPS(x,y,z)*(x**2*phiPS(x,y,z) + &
  & z*(-2._dp*x + (x - y + z)*Zlog(y/Q2) + (x + y - z)*Zlog(z/Q2) + &
 & (-y + z)*Zlog(z/y))))/(2._dp*x**2*z*deltaPS(x,y,z))
  End If
End If
If (res.ne.res) write(*,*) "NaN appearing in ddI_11 for input",Real(x),Real(y),Real(z)
ddI_11 = res
End Function ddI_11

Complex Function ddI_12_0(x,z,Q2) 
Complex(dp), Intent(in) :: x,z
Real(dp), Intent(in) :: Q2

If (((Real(x,dp).gt.Real(z,dp)).And.(Real(z,dp).gt.0._dp)).or.((Real(x,dp).lt.Real(z,dp)).And.(Real(z,dp).lt.0._dp))) Then 
 ddI_12_0 = (4*x*z*PolyLog(2,1 - x/z) + 2*x*(x + z)*ZLog(x/Q2) - x**2*ZLog(z/Q2) &
- 4*x*z*ZLog(z/Q2) + z**2*ZLog(z/Q2) + x**2*ZLog(z/x) - x*z*ZLog(z/x))/(2._dp*x*(x - z)**2)
Else 
  ddI_12_0 =  (2*Pi**2*x*z - 12*x*z*PolyLog(2,x/z) + 6*x*(x + z)*ZLog(x/Q2) - &
&3*x**2*ZLog(z/Q2) - 12*x*z*ZLog(z/Q2) + 3*z**2*ZLog(z/Q2) + &
&3*x**2*ZLog(z/x) - 3*x*z*ZLog(z/x))/(6._dp*x*(x - z)**2)
End if

End Function ddI_12_0

Complex(dp) Function ddI_12(x,y,z,Q2) 
Implicit None
Complex(dp), Intent(in) :: x,y,z
Real(dp), Intent(in) :: Q2
Complex(dp) :: res

res = ZeroC
If (SmallM(y,x,z,Q2).or.(SmallM(x,y,z,Q2))) Then
 If (SmallM(x,y,z,Q2)) Then
  If (SmallM(y,x,z,Q2)) Then 
   If (SmallM(z,x,y,Q2)) Then
    res = ZeroC
   Else
    res = Pi**2/(3._dp*z) - (2*ZLog(z/Q2))/z
   End If
  Else  ! y > 0
   If (SmallM(z,y,x,Q2)) Then 
    res = ZLog(y/Q2)/y
   Else
    If (SmallD(y,z)) Then 
     res= 0._dp
    Else
     res= ddI_12_0(y,z,Q2)
    End if
   End if
  End if
 Else !  x > 0
   If (SmallD(x,z)) Then 
    res= 0._dp
   Else
   If (SmallM(z,x,y,Q2)) Then
    res =  ZLog(x/Q2)/x
   Else
    res= ddI_12_0(x,z,Q2)
   End if
   End if
 End if
Else
  If (SmallM(z,x,y,Q2)) Then ! z=0
    If (SmallD(x,y)) then  !x=y
           res = 1._dp/x
    else
      ! f_xy(x,y,0)
      res = ((-1.*x**2+1.*y**2)*Log(x/Q2)+(1.*x**2-1.*y**2)*Log((x-1.*y)/Q2)&
      &+1.*x*y*Log(x/y)-1.*x**2*Log(1.-(1.*y)/x)+1.*y**2*Log(1.-(1.*y)&
      &/x))/(x*(x-1.*y)*y)
    end if
  Else ! z > 0
!      res = -(x+y-z+x*ZLOG(x/Q2)+y*ZLOG(y/Q2)-x*ZLOG(z/Q2)-y*ZLOG(z/Q2)+x*y*&
!      &ddXi_12(x,y,z))/(2._dp*x*y)
! !NEW FUNCTION BY FS
      res =  (-(x*(x - y - z)*(y*(x - y + z)*phiPS(x,y,z) &
     & + y*z*(Zlog(y/x) + Zlog(y/z)) + (x - z)*z*Zlog(z/x))) + &
     &    deltaPS(x,y,z)*(x*y*phiPS(x,y,z) &
     & - z*(x*Zlog(x/Q2) + y*Zlog(y/Q2) - (x + y)*Zlog(z/Q2) + y*Zlog(z/y))))/(2._dp*x*y*z*deltaPS(x,y,z))
  End If
End If
  
  If (res.ne.res) write(*,*) "NaN appearing in ddI_12 for input",Real(x),Real(y),Real(z)
ddI_12 = res
End Function ddI_12

! some functions that only depend on I(x,y,z)
! SSS, FFSbar, FFVbar

Complex(dp) Function dSSS_1(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fSSS(x,y,z) = -I(x,y,z)
res = -dI_1(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in dSSS_1"
dSSS_1 = res
End Function dSSS_1

Complex(dp) Function ddSSS_11(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fSSS(x,y,z) = -I(x,y,z)
res = -ddI_11(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddSSS_11"
ddSSS_11 = res
End Function ddSSS_11

Complex(dp) Function ddSSS_12(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fSSS(x,y,z) = -I(x,y,z)
res = -ddI_12(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddSSS_12"
ddSSS_12 = res
End Function ddSSS_12

Complex(dp) Function dFFSbar_1(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFSbar(x,y,z) = 2I(x,y,z)
res = 2*dI_1(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in dFFSbar_1"
dFFSbar_1 = res
End Function dFFSbar_1

Complex(dp) Function ddFFSbar_11(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2

Complex(dp) :: res
! fFFSbar(x,y,z) = 2I(x,y,z)
res = 2*ddI_11(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddFFSbar_11"
ddFFSbar_11 = res
End Function ddFFSbar_11

Complex(dp) Function ddFFSbar_12(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFSbar(x,y,z) = 2I(x,y,z)
res = 2*ddI_12(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddFFSbar_12"
ddFFSbar_12 = res
End Function ddFFSbar_12

Complex(dp) Function dFFVbar_1(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFVbar(x,y,z) = 6I(x,y,z)
res = 6*dI_1(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in dFFVbar_1"
dFFVbar_1 = res
End Function dFFVbar_1

Complex(dp) Function ddFFVbar_11(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFVbar(x,y,z) = 6I(x,y,z)
res = 6*ddI_11(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddFFVbar_11"
ddFFVbar_11 = res
End Function ddFFVbar_11

Complex(dp) Function ddFFVbar_equalzero(xin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFVbar(x,y,z) = 6I(x,y,z) 
res = 6*ddI_equalzero(xin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddFFVbar_11"
ddFFVbar_equalzero = res
End Function ddFFVbar_equalzero

Complex(dp) Function dFFVbar_equalzero(xin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFVbar(x,y,z) = 6I(x,y,z)
res = 6*dI_equalzero(xin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddFFVbar_11"
dFFVbar_equalzero = res
End Function dFFVbar_equalzero


Complex(dp) Function ddFFSbar_equalzero(xin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFSbar(x,y,z) = 2I(x,y,z) 
res = 2*ddI_equalzero(xin,Q2)
ddFFSbar_equalzero = res
End Function ddFFSbar_equalzero

Complex(dp) Function dFFSbar_equalzero(xin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFSbar(x,y,z) = J(x,x) + 2x*I(x,x,0)
res = 2*dI_equalzero(xin,Q2)
dFFSbar_equalzero = res
End Function dFFSbar_equalzero

Complex(dp) Function ddFFS_equalzero(xin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFSbar(x,y,z) = J(x,x) + 2x*I(x,x,0)
If (VerySmallM(Abs(xin),q2,q2,q2)) Then
 res = 0._dp
Else 
 res = -2._dp*(1._dp + (-3._dp + ZLog(xin/Q2))*zLog(xin/Q2))
End if
ddFFS_equalzero = res
End Function ddFFS_equalzero

Complex(dp) Function dFFS_equalzero(xin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFSbar(x,y,z) = J(x,x) + 2x*I(x,x,0)
If (VerySmallM(Abs(xin),q2,q2,q2)) Then
 res = 0
Else 
 res = -2._dp*xin*(-3._dp + ZLog(xin/Q2))*(-2._dp + ZLOG(xin/Q2))
End if
dFFS_equalzero = res
End Function dFFS_equalzero

Complex(dp) Function ddFFVbar_12(xin,yin,zin,Q2) 
Implicit None
Complex(dp), Intent(in) :: xin,yin,zin
Real(dp), Intent(in) :: Q2
Complex(dp) :: res
! fFFVbar(x,y,z) = 6I(x,y,z)
res = 6*ddI_12(xin,yin,zin,Q2)
! If (res.ne.res) write(*,*) "NaN appearing in ddFFVbar_12"
ddFFVbar_12 = res
End Function ddFFVbar_12

Complex(dp) Function J_SMartinC(x,Q2)
Implicit None
Complex(dp), Intent(in) :: x
Real(dp), Intent(in) :: Q2
If (VerySmallM(Real(x,dp),Q2)) then
  J_SMartinC = ZeroC
Else
  J_SMartinC = x*(log(x/Q2)-1._dp)
End If
End Function J_SMartinC

Complex(dp) Function dJ2x_1(x,y,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: x,y
Complex(dp) :: res
If (VerySmallM(Real(x,dp),Max(Real(y,dp),Q2)).or.VerySmallM(Real(y,dp),Max(Real(x,dp),Q2))) then
  res = ZeroC
else If (SmallM(Real(x,dp),Max(Real(y,dp),Q2))) then
 If (SmallM(Real(y,dp),Q2)) Then 
  res = y*Log(x/Q2)*(-1._dp + Log(y/q2))
 Else 
  res = y*Log(x/Q2)*(-1._dp + Log(y/Q2))
 End if
Else
  res = log(x/Q2)*J_SMartinC(y,Q2)
End if
If (res.ne.res) write(*,*) "NaN appearing in dJ2x_1", Real(x,dp), Real(y,dp)
dJ2x_1 = res
End Function dJ2x_1

Complex(dp) Function ddJ2x_11(x,y,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: x,y
Complex(dp) :: res
If (VerySmallM(Real(x,dp),Max(Real(y,dp),Q2))) then
  res =  ZeroC
Else
  res = J_SMartinC(y,Q2)*1._dp/x
End If
If (res.ne.res) write(*,*) "NaN appearing in ddJ2x_11"
ddJ2x_11 = res
End Function ddJ2x_11

Complex(dp) Function ddJ2x_12(x,y,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: x,y
Complex(dp) :: res
If ((VerySmallM(Real(x,dp),Max(Real(y,dp),Q2))).or.(VerySmallM(Real(y),Max(Real(x),Q2)))) then
  res = ZeroC
Else
  res = log(x/Q2)*log(y/Q2)
End if

If (res.ne.res) write(*,*) "NaN appearing in ddJ2x_12"
ddJ2x_12 = res
End Function ddJ2x_12

Complex(dp) Function dJ(x,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: x
Complex(dp) :: res
If (VerySmallM(Real(x,dp),Q2)) then
  res = ZeroC
Else
  res = log(x/Q2)
End if
If (res.ne.res) write(*,*) "NaN appearing in dJ"
dJ = res
End Function dJ

Complex(dp) Function ddJ(x,Q2) 
Implicit None
Real(dp), Intent(in) :: Q2
Complex(dp), Intent(in) :: x
Complex(dp) :: res
If (VerySmallM(Real(x,dp),Q2)) then
  res = ZeroC
Else
  res = 1._dp/x
End if

If (res.ne.res) write(*,*) "NaN appearing in ddJ"
ddJ = res
End Function ddJ





! balls topology functions SS, VS


Complex(dp) Function dSS_1(xin,yin,Q2)
Implicit None
Real(dp), Intent(in) :: xin,yin,Q2
Complex(dp) :: res,x,y
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
! fSS(x,y) = J(x,y)
res = dJ2x_1(x,y,Q2)
dSS_1 = res
If (res.ne.res) write(*,*) "NaN appearing in dSS_1"
End Function dSS_1

Complex(dp) Function ddSS_11(xin,yin,Q2)
Implicit None
Real(dp), Intent(in) :: xin,yin,Q2
Complex(dp) :: res,x,y
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
! fSS(x,y) = J(x,y)
res = ddJ2x_11(x,y,Q2)
ddSS_11 = res
! If (res.ne.res) write(*,*) "NaN appearing in ddSS_11"
End Function ddSS_11

Complex(dp) Function ddSS_12(xin,yin,Q2)
Implicit None
Real(dp), Intent(in) :: xin,yin,Q2
Complex(dp) :: res,x,y
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
! fSS(x,y) = J(x,y)
res = ddJ2x_12(x,y,Q2)
ddSS_12 = res
! If (res.ne.res) write(*,*) "NaN appearing in ddSS_12"
End Function ddSS_12

Complex(dp) Function dVS_1(xin,yin,Q2)
Implicit None
Real(dp), Intent(in) :: xin,yin,Q2
Complex(dp) :: res,x,y
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
! fVS(x,y) = 3J(x,y)
res = 3._dp*dJ2x_1(x,y,Q2)
dVS_1 = res
! If (res.ne.res) write(*,*) "NaN appearing in dVS_1"
End Function dVS_1

Complex(dp) Function ddVS_11(xin,yin,Q2)
Implicit None
Real(dp), Intent(in) :: xin,yin,Q2
Complex(dp) :: res,x,y
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
! fVS(x,y) = 3J(x,y)
res = 3._dp*ddJ2x_11(x,y,Q2)
ddVS_11 = res
! If (res.ne.res) write(*,*) "NaN appearing in ddVS_11"
End Function ddVS_11

Complex(dp) Function ddVS_12(xin,yin,Q2)
Implicit None
Real(dp), Intent(in) :: xin,yin,Q2
Complex(dp) :: res,x,y
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
! fVS(x,y) = 3J(x,y)
res = 3._dp*ddJ2x_12(x,y,Q2)
ddVS_12 = res
! If (res.ne.res) write(*,*) "NaN appearing in ddVS_12"
End Function ddVS_12

! sort two complex arguments by real part a<b
Subroutine SortTwoArgumentsC(a,b)
Implicit None
Complex(dp), Intent(inout) :: a,b
Complex(dp) :: x
If (Abs(b).le.Abs(a)) Then
  x = b
  b = a
  a = x
End If
End Subroutine SortTwoArgumentsC





!! DO NOT DELETE !!! FUNCTION BODY for copy paste
Complex(dp) Function newfunc(xin,yin,zin,Q2) 
Implicit None
Real(dp), Intent(in) :: xin,yin,zin,Q2
Complex(dp) :: x,y,z ! complexify input values
Complex(dp) :: res
x = Cmplx(xin,0.,dp)
y = Cmplx(yin,0.,dp)
z = Cmplx(zin,0.,dp)


If (res.ne.res) write(*,*) "NaN appearing in newfunc"
newfunc = res
End Function newfunc


Complex(dp) Function dXi_1(x,y,z)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: R,Rx,Xi,dtemp
R=Rfunction(x,y,z)
Xi=XiFunction(x,y,z)
Rx=dR_1(x,y,z)
dtemp = -(ZLOG(y/z)/x)+(2._dp*(ZLOG((-R+x-y+z)/(4._dp*z))+ZLOG((R+x-y+z)/z)))&
&/(R+x-y-z)+(LOG(16._dp)-2._dp*ZLOG((-R-x+y+z)/z)-2._dp*ZLOG((R-x+&
&y+z)/z))/(R-x+y-z)
dXi_1 = Rx*(Xi/R) + R*dtemp
! doesn't work that well!

dXi_1 = ZSQRT(x**2+(y-z)**2-2*x*(y+z))*(-(ZLOG(y/z)/x)+(2*ZLOG((x-y+z-&
&ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/ZSQRT(x**2+(y-z)**2-&
&2*x*(y+z))+(2*(1+(-x+y+z)/ZSQRT(x**2+(y-z)**2-2*x*(y+z)))&
&*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/(x-y+&
&z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))+(2*ZLOG((x-y+z+ZSQRT(x**2+&
&(y-z)**2-2*x*(y+z)))/(2.*z)))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))&
&-(2*(-x+y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))*ZLOG((-x+y+&
&z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/(ZSQRT(x**2+(y-z)&
&**2-2*x*(y+z))*(-x+y-z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))))&
&+((x-y-z)*(Pi**2-3*ZLOG(x/z)*ZLOG(y/z)+6*ZLOG((x-y+z-ZSQRT(x**2+&
&(y-z)**2-2*x*(y+z)))/(2.*z))*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)&
&**2-2*x*(y+z)))/(2.*z))-6*PolyLog(2,(x-y+z-ZSQRT(x**2+(y-z)&
&**2-2*x*(y+z)))/(2.*z))-6*PolyLog(2,(-x+y+z-ZSQRT(x**2+(y-&
&z)**2-2*x*(y+z)))/(2.*z))))/(3.*ZSQRT(x**2+(y-z)**2-2*x*(y+z)))

End Function dXi_1

Complex(dp) Function ddXi_11(x,y,z)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: R,Rx,Rxx,Xi,dtempx,ddtempxx

If (.false.) then

  R=Rfunction(x,y,z)
  Xi=XiFunction(x,y,z)
  Rx=dR_1(x,y,z)
  Rxx=ddR_11(x,y,z)
  dtempx = -(ZLOG(y/z)/x)+(2._dp*(ZLOG((-R+x-y+z)/(4._dp*z))+ZLOG((R+x-y+z)/z)))&
  &/(R+x-y-z)+(dlog(16._dp)-2._dp*ZLOG((-R-x+y+z)/z)-2._dp*ZLOG((R-x+&
  &y+z)/z))/(R-x+y-z)
  ddtempxx = -4._dp/((R+x-y-z)*(R-x+y-z))+2._dp/((R+x-y-z)*(R+x-y+z))&
  &+2._dp/((R-x+y-z)*(R-x+y+z))+ZLOG(y/z)/x**2-(2*ZLOG((-R+x-&
  &y+z)/(2._dp*z)))/(R+x-y-z)**2+(DLog(4._dp)-2._dp*ZLOG((R+x-y+z)/z))&
  &/(R+x-y-z)**2-(2._dp*ZLOG((-R-x+y+z)/(2._dp*z)))/(R-x+y-z)**2+&
  &(DLOG(4._dp)-2._dp*ZLOG((R-x+y+z)/z))/(R-x+y-z)**2
  ddXi_11 = Rxx*Xi/R+2._dp*Rx*dtempx+R*ddtempxx

else

  ddXi_11 = ((2*x-2*(y+z))*(-(ZLOG(y/z)/x)+(2*ZLOG((x-y+z-ZSQRT(x**2+(y-&
  &z)**2-2*x*(y+z)))/(2.*z)))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))+(2*(1+&
  &(-x+y+z)/ZSQRT(x**2+(y-z)**2-2*x*(y+z)))*ZLOG((-x+y+z-ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))/(2.*z)))/(x-y+z-ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))+(2*ZLOG((x-y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))&
  &/(2.*z)))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))-(2*(-x+y+z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))*ZLOG((-x+y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+&
  &z)))/(2.*z)))/(ZSQRT(x**2+(y-z)**2-2*x*(y+z))*(-x+y-z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z))))))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z))*((-4*(-x+y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+&
  &z))))/((x**2+(y-z)**2-2*x*(y+z))*(-x+y-z+ZSQRT(x**2+(y-&
  &z)**2-2*x*(y+z))))+ZLOG(y/z)/x**2-(2*(x-y-z)*ZLOG((x-y+z-&
  &ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/(x**2+(y-z)**2-2*x*(y+&
  &z))**1.5+2*(-((1+(-x+y+z)/ZSQRT(x**2+(y-z)**2-2*x*(y+z)))&
  &**2/(x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))**2)-(4*y*z)/((x**2+&
  &(y-z)**2-2*x*(y+z))**1.5*(-x+y-z+ZSQRT(x**2+(y-z)**2-2*x*(y+&
  &z)))))*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))&
  &+(2*(x**2-2*x*y+y**2-2*x*z-2*y*z+z**2+x*ZSQRT(x**2+(y-z)&
  &**2-2*x*(y+z))-y*ZSQRT(x**2+(y-z)**2-2*x*(y+z))-z*ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z))-(x-y-z)*(x-y+z+ZSQRT(x**2+(y-z)&
  &**2-2*x*(y+z)))*ZLOG((x-y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))&
  &/(2.*z))))/((x**2+(y-z)**2-2*x*(y+z))**1.5*(x-y+z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z))))-2*(-((-x+y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/((x**2+(y-z)**2-2*x*(y+z))*(-x+y-z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))))+(4*y*z*ZLOG((-x+y+z+ZSQRT(x**2+(y-&
  &z)**2-2*x*(y+z)))/(2.*z)))/((x**2+(y-z)**2-2*x*(y+z))**1.5*(-&
  &x+y-z+ZSQRT(x**2+(y-z)**2-2*x*(y+z))))+((-x+y+z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))**2*ZLOG((-x+y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z)))/((x**2+(y-z)**2-2*x*(y+z))*(x-y+z-ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))**2)))-(4*y*z*(Pi**2-3*ZLOG(x/z)*ZLOG(y/z)+&
  &6*ZLOG((x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))*ZLOG((-&
  &x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))-6*POLYLOG(2,&
  &(x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))-6*POLYLOG(2,&
  &(-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))))/(3.*(x**2+&
  &(y-z)**2-2*x*(y+z))**1.5)

end if

End Function ddXi_11

Complex(dp) Function ddXi_12(x,y,z)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: R,Rx,Ry,Rxy,Xi,dtempx,dtempy,ddtempxy

if (.false.) then 
  R=Rfunction(x,y,z)
  Xi=XiFunction(x,y,z)
  Rx=dR_1(x,y,z)
  Ry=dR_1(y,x,z)
  Rxy=ddR_11(x,y,z)
  dtempx = -(ZLOG(y/z)/x)+(2*(ZLOG((-R+x-y+z)/(4.*z))+ZLOG((R+x-y+z)/z)))&
  &/(R+x-y-z)+(dlog(16._dp)-2*ZLOG((-R-x+y+z)/z)-2*ZLOG((R-x+&
  &y+z)/z))/(R-x+y-z)
  dtempy = DLOG(4._dp)/(R+x-y-z)-ZLOG(x/z)/y+(2._dp*ZLOG((-R+x-y+z)/(2._dp*z)))/(-&
  &R-x+y+z)-(2._dp*ZLOG((R+x-y+z)/z))/(R+x-y-z)+(2._dp*(ZLOG((-&
  &R-x+y+z)/(4._dp*z))+ZLOG((R-x+y+z)/z)))/(R-x+y-z)
  ddtempxy = -(1._dp/(x*y))+4._dp/((R+x-y-z)*(R-x+y-z))-2._dp/((R+x-y-z)*(R+&
  &x-y+z))-2._dp/((R-x+y-z)*(R-x+y+z))+(2._dp*ZLOG((-R+x-y+&
  &z)/(2._dp*z)))/(R+x-y-z)**2+(2._dp*ZLOG((R+x-y+z)/(2._dp*z)))/(R+x-&
  &y-z)**2+(2._dp*ZLOG((-R-x+y+z)/(2._dp*z)))/(R-x+y-z)**2+(2._dp*ZLOG((R-&
  &x+y+z)/(2._dp*z)))/(R-x+y-z)**2
  ddXi_12 = Rxy*Xi/R+Rx*dtempy+Ry*dtempx+R*ddtempxy
else

  ddXi_12 = (-2*z*(-x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))*(-x**3+x**2*y+&
  &x*y**2-y**3+3*x**2*z+2*x*y*z+3*y**2*z-3*x*z**2-3*y*z**2+z**3+&
  &2*x*y*(x-y+z)*ZLOG((x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))&
  &/(2.*z))+2*x*y*(-x+y+z)*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))+2*x**2*y*ZLOG((x-y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))-2*x*y**2*ZLOG((x-y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))+2*x*y*z*ZLOG((x-y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))-2*x**2*y*ZLOG((-x+y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))+2*x*y**2*ZLOG((-x+y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))+2*x*y*z*ZLOG((-x+y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z))))/(x*y*(x**2+(y-z)**2-2*x*(y+z))*(x-y+&
  &z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))*(x-y-z+ZSQRT(x**2+(y-&
  &z)**2-2*x*(y+z))))+((2*x-2*(y+z))*(-(ZLOG(x/z)/y)+(2*(1+(x-&
  &y+z)/ZSQRT(x**2+(y-z)**2-2*x*(y+z)))*ZLOG((x-y+z-ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))/(2.*z)))/(-x+y+z-ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))+(2*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))&
  &/(2.*z)))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))-(2*(x-y+z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))*ZLOG((x-y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+&
  &z)))/(2.*z)))/(ZSQRT(x**2+(y-z)**2-2*x*(y+z))*(x-y-z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z))))+(2*ZLOG((-x+y+z+ZSQRT(x**2+(y-z)**2-&
  &2*x*(y+z)))/(2.*z)))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))))/(2.*ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))+((2*y-2*(x+z))*(-(ZLOG(y/z)/x)+(2*ZLOG((x-&
  &y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/ZSQRT(x**2+(y-&
  &z)**2-2*x*(y+z))+(2*(1+(-x+y+z)/ZSQRT(x**2+(y-z)**2-2*x*(y+&
  &z)))*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/(x-&
  &y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))+(2*ZLOG((x-y+z+ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))/(2.*z)))/ZSQRT(x**2+(y-z)**2-2*x*(y+z))&
  &-(2*(-x+y+z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))*ZLOG((-x+y+&
  &z+ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/(ZSQRT(x**2+(y-z)&
  &**2-2*x*(y+z))*(-x+y-z+ZSQRT(x**2+(y-z)**2-2*x*(y+z))))))&
  &/(2.*ZSQRT(x**2+(y-z)**2-2*x*(y+z)))+((x-y-z)*(x-y+z)*(Pi**2-&
  &3*ZLOG(x/z)*ZLOG(y/z)+6*ZLOG((x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+&
  &z)))/(2.*z))*ZLOG((-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))&
  &-6*PolyLog(2,(x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))&
  &-6*PolyLog(2,(-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))))&
  &/(3.*(x**2+(y-z)**2-2*x*(y+z))**1.5)+(-Pi**2+3*ZLOG(x/z)*ZLOG(y/z)&
  &-6*ZLOG((x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))*ZLOG((-&
  &x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))+6*PolyLog(2,&
  &(x-y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z))+6*PolyLog(2,&
  &(-x+y+z-ZSQRT(x**2+(y-z)**2-2*x*(y+z)))/(2.*z)))/(3.*ZSQRT(x**2+&
  &(y-z)**2-2*x*(y+z)))
end if
End Function ddXi_12	


Complex(dp) Function dR_1(x,yin,zin)
Implicit None
Complex(dp), Intent(in) :: x,yin,zin
Complex(dp) :: R,y,z
y = yin
z = zin
Call SortTwoArgumentsC(y,z)
R=Rfunction(x,y,z)
If (VerySmallM(x,y,z,0._dp)) then
  If (VerySmallM(y,x,z,0._dp)) then
    ! R_x(0,0,z) 
    dR_1 = -1._dp
  Else
    ! R_x(0,y,z)
    dR_1 = -(y+z)/ZSQRT((y-z)**2.)
  end if
else
  If (VerySmallM(y,x,z,0._dp)) then
    ! R_x(x,0,z)
    dR_1 = (x-z)/ZSQRT((x-z)**2.)
  else
    ! R_x(x,y,z)
    dR_1 = (x-y-z)/R
  end if
end if
End Function dR_1

Complex(dp) Function ddR_11(x,y,z)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: R
R=Rfunction(x,y,z)
ddR_11 = -4._dp*y*z/(R**3)
End Function ddR_11

Complex(dp) Function ddR_12(x,y,z)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: R
R=Rfunction(x,y,z)
ddR_12 = 2._dp*(x+y-z)*z/(R**3)
End Function ddR_12




End Module DerivativesEffPotFunctions
 
 
 
 
 