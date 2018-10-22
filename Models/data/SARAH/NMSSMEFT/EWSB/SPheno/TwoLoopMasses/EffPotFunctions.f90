Module EffPotFunctions

Use Control
Use Mathematics
! Use Model_Data_MSSM

! squared masses lesser than MIN_MASS are set to zero
Real(dp), parameter :: MIN_MASS = 1.0_dp
! for squared masses lesser than SMALL_MASS expansions are made
Real(dp), parameter :: SMALL_MASS = 1.0_dp
Real(dp) :: hstep_pn=0.1_dp, hstep_sa=0.001_dp

 Real(dp) :: epsD = 1E-8_dp, epsM = 1.0E-8_dp, epsMnull = 1.0E-10_dp

 Interface SmallD
  Module Procedure SmallDR, SmallDC
 End Interface

 Interface SmallM
  Module Procedure SmallMR, SmallMC, SmallMR2, SmallMC2
 End Interface
 
  Interface VerySmallM
  Module Procedure VerySmallMR, VerySmallMC, VerySmallMR2, VerySmallMC2
 End Interface

Contains


! Function h(x,Q) for 1-loop effective potential
! following S.P. Martin, arXiv:hep-ph/0111209v2
! "Two-loop effective potential for a general renormalizable theory
! and softly broken supersymmetry"

Logical Function VerySmallMR(x,y,z,Q) 
Implicit None
Real(dp), Intent(in) :: x,y,z
Real(dp), Intent(in) :: Q
If (Max(Max(Abs(x),Abs(y)),Abs(z)).le.epsMnull) Then
 VerySmallMR = .True.
Else If ((Abs(x)/Max(Q,Max(Abs(y),Abs(z)))).le.epsMnull) Then
 VerySmallMR = .True.
Else
 VerySmallMR = .False.
End if
End Function VerySmallMR

Logical Function VerySmallMC(x,y,z,Q) 
Implicit None
Complex(dp), Intent(in) :: x,y,z
Real(dp), Intent(in) :: Q
If (Max(Max(Abs(x),Abs(y)),Abs(z)).le.epsMnull) Then
 VerySmallMC = .True.
Else If ((Abs(x)/Max(Q,Max(Abs(y),Abs(z)))).lt.epsMnull) Then
 VerySmallMC = .True.
Else
 VerySmallMC = .False.
End if
End Function VerySmallMC

Logical Function VerySmallMR2(x,y) 
Implicit None
Real(dp), Intent(in) :: x,y
If (Max(Abs(x),Abs(y)).le.epsMnull) Then
 VerySmallMR2 = .True.
Else If (Abs(x/y).le.epsMnull) Then
 VerySmallMR2 = .True.
Else
 VerySmallMR2 = .False.
End if
End Function VerySmallMR2

Logical Function VerySmallMC2(x,y) 
Implicit None
Complex(dp), Intent(in) :: x,y
If (Max(Abs(x),Abs(y)).le.epsMnull) Then
 VerySmallMC2 = .True.
Else If (Abs(x/y).le.epsMnull) Then
 VerySmallMC2 = .True.
Else
 VerySmallMC2 = .False.
End if
End Function VerySmallMC2

recursive Complex(dp) Function I_SMartin_ex(x_in,y_in,z_in,Q2) result(res)
Implicit None
! x_in,y_in,z_in are supposed to be squared masses
! symmetric under interchange of any two of these
Real(dp),Intent(in) :: x_in,y_in,z_in,Q2
Integer :: ncontrol 
Complex(dp) :: x,y,z,tempI
x = x_in
y = y_in
z = z_in
res = Cmplx(0._dp,0._dp)
ncontrol = 0

If (Q2.le.0._dp) Then 
  write(*,*) 'invalid renormalization scale!'
  return
end if

Call SortArguments3C(x,y,z) ! sort x<=y<=z

If (VerySmallM(x,y,z,Q2)) Then ! x=0
!  Write(*,*) x
  If (VerySmallM(y,z,z,Q2)) Then ! y=0 (z >= y holds)
    If (VerySmallM(z,z,z,Q2)) then ! z=0
      res = ZeroC ! I(0,0,0)
      ncontrol = ncontrol +1
    Else ! z!=0
         ! I(0,0,z)
         res = -0.5_dp*z*(log(z/Q2))**2 &
         & + 2*z*log(z/Q2)-2.5_dp*z-pi**2*z/6._dp
         ncontrol = ncontrol +1
!       res = 0._dp
    End If
  Else ! y != 0
    If (VerySmallM(Abs(y-z),Abs(z))) Then ! y=z
	 ! I(0,y,y)
         res = -y*(zlog(y/Q2))**2+4._dp*y*zlog(y/Q2)-5._dp*y 
         ncontrol = ncontrol +1
! res = 0._dp
    Else ! z != y
          ! I(0,y,z)
	res = (z-y)*(CLi2_mod(y/z)-log(z/y)*log((z-y)/Q2) &
	& +0.5_dp*(log(z/Q2))**2-pi**2/6._dp)  &
	& -2.5_dp*(z+y)+2*y*log(y/Q2)+2*z*log(z/Q2) & 
	& -z*log(z/Q2)*log(y/Q2)
	ncontrol = ncontrol +1
! res = 0._dp
    End If
  End If
Else If (SmallM(x,y,z,Q2)) then ! x small
  If (SmallM(y,z,z,Q2)) then ! y small (z >= y holds)

      ! I(eps1,eps2,z)
      tempI = I_SMartin_ex(0._dp,0._dp,Real(z,dp),Q2) 
      res = tempI + x/z*(-z-tempI + J_SMartin_1x(Real(z,dp),Q2)*(3._dp-zlog(x/Q2))) &  !! SWITCH 2
      & + y/z*(-z-tempI + J_SMartin_1x(Real(z,dp),Q2)*(3._dp-log(y/Q2))) &
      & + x*y/z**2*(-2._dp*tempI+4._dp*J_SMartin_1x(Real(z,dp),Q2) - 2.*z & 
      & - (z+J_SMartin_1x(Real(z,dp),Q2))*(log(x/Q2)+log(y/Q2))+z*log(x/Q2)*log(y/Q2))
      ncontrol = ncontrol +1     

  else ! y large (implies z also large)
    If (SmallD(y,z)) then ! y=z (large)
      ! I(eps,y,y)
      res = 2._dp
      res = 2._dp*J_SMartin_1x(Real(y,dp),Q2) - 2._dp*y &
      & - J_SMartin_2x(Real(y,dp),Real(y,dp),Q2)/y &
      & + x*(4._dp+J_SMartin_2x(Real(y,dp),Real(y,dp),Q2)/(2._dp*y**2) &  !! SWITCH 1
      & + 3._dp/y*J_SMartin_1x(Real(y,dp),Q2) &
      & -(1._dp+J_SMartin_1x(Real(y,dp),Q2)/y)*log(x/Q2))
      ncontrol = ncontrol +1
     
    else ! y != z
      ! I(eps,y,z)
      tempI = I_SMartin_ex(0._dp,Real(y,dp),Real(z,dp),Q2)
      res = tempI + x*(-(y+z)*tempI-2.*J_SMartin_2x(Real(y,dp),Real(z,dp),Q2) &  !! SWITCH 3
      & +3._dp*y*J_SMartin_1x(Real(y,dp),Q2) + 3.*z*J_SMartin_1x(Real(z,dp),Q2) & 
      & -z*J_SMartin_1x(Real(y,dp),Q2)-y*J_SMartin_1x(Real(z,dp),Q2) - (y+z)**2 &
      & + (y-z)*(J_SMartin_1x(Real(z,dp),Q2)-J_SMartin_1x(Real(y,dp),Q2))*log(x))/(y-z)**2
      ncontrol = ncontrol +1
    end if
  end if

else ! x large
 
  ! most general case
  ! I(x,y,z)
  res = Cmplx(0._dp,0._dp)
  res=res + 0.5_dp*(x-y-z)*log(y/Q2)*log(z/Q2)
  res=res + 0.5_dp*(y-x-z)*log(x/Q2)*log(z/Q2)
  res=res + 0.5_dp*(z-x-y)*log(x/Q2)*log(y/Q2)
  res=res + 2._dp*x*log(x/Q2)
  res=res + 2._dp*y*log(y/Q2)
  res=res + 2._dp*z*log(z/Q2)
  res=res - 2.5_dp*(x+y+z)
  res=res - 0.5*XiFunction(x,y,z)
  ncontrol = ncontrol +1


end if

! end of all ifs

! control variable against sloppy programming
if (ncontrol.gt.1) then
  write(*,*) 'in I_SMartin_ex more than one case applies. sloppy programming!'
end if
End Function I_SMartin_ex



Complex(dp) Function I_SMartinC(x,y,z,Q2)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Real(dp), Intent(in) :: Q2
I_SMartinC = I_SMartin(Real(x,dp),Real(y,dp),Real(z,dp),Q2)
End Function

Complex(dp) Function h_SMartin(m2,Q2)
Implicit None
Complex(dp) :: z
Real(dp),Intent(in) :: m2,Q2
! input: squared mass m2, squared renormalization scale Q2. 
If (Q2.le.0._dp) Then 
  write(*,*) 'invalid renormalization scale!'
  return
end if
z = CMPLX(m2,0._dp)
If (abs(m2).le.MIN_MASS) Then
   h_SMartin = 0._dp
Else
   h_SMartin = 0.25_dp * (m2**2) * (log(z/Q2)-1.5_dp)
End If
End Function h_SMartin

Real(dp) Function DumbDiff2(func,x,k1,k2,h)
! finite difference method
Implicit None
Real(dp),external :: func
Integer,intent(in) :: k1,k2
Real(dp), Intent(in) :: x(2),h
Real(dp) :: res
if (k1.eq.k2) then
 DumbDiff2 = (func1D(x(k1)-h)-2._dp*func1D(x(k1))+func1D(x(k1)+h))/(h**2.)
else
 res = func((/x(1)+h,x(2)+h/))
 res = res-func((/x(1)+h,x(2)-h/))
 res = res-func((/x(1)-h,x(2)+h/))
 res = res+func((/x(1)-h,x(2)-h/))
 res = res/(4._dp*h**2)
 DumbDiff2=res
end if
Contains
Real(dp) function func1D(y)
Real(dp),Intent(in) :: y
Real(dp) :: ytemp(2)
ytemp=x
ytemp(k1)=y
func1D = func(ytemp)
end function
End function

Real(dp) function partialDiff(func,x,k,n,h)
! wrapper function to calculate the partial derivative of func w.r.t. to k-th variable
! evaluated at the n-dim. point x, with stepsize h. 
Implicit None
Integer,Intent(in) :: n,k
Real(dp),External :: func
Real(dp),Intent(in) :: x(n),h
Real(dp) :: xtemp(n)
partialDiff=DumbDiff(func_k,x(k),h)
  Contains 
  Real(dp) function func_k(y)
  Implicit None
  Real(dp) :: y
  xtemp = x
  xtemp(k)=y
  func_k = func(xtemp)
  End function
End function


Real(dp) Function DumbDiff(f,x,h)
implicit none
Real(dp),intent(in) :: x,h
real(dp),external :: f
DumbDiff = (-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12.*h)
end function

Real(dp) Function dfridr(func,x,h,err,iout)
! algorithm based on
! Ridders, C.J.F. 1982,
! Advances in Engineering Software
! vol. 4, no. 2, pp. 75–76. 

! Returns the derivative of a function func at a point x
! by Ridders' method of polynomial extrapolation. 
! The value h is input as an estimated initial stepsize; it need not be small, but rather should 
! be an increment in x over which func changes substantially. 
! An estimate of the error in the derivative is returned as err.
! Parameters: Stepsize is decreased by CON at each iteration. Max size of tableau is set by NTAB. Return when error is SAFE worse than the best so far.
Implicit None
INTEGER, parameter :: NTAB=40
! original: CON=1.4
Real(dp), parameter :: CON=1.4_dp,CON2=CON*CON,BIG=1.D30,safe=20.0_dp
REAL(dp),Intent(in) :: h,x
Real(dp) :: err_int
Real(dp),Intent(out) :: err
Real(dp), EXTERNAL :: func
INTEGER i,j
INTEGER,Intent(out) :: iout
REAL(dp) :: errt,fac,hh,a(NTAB,NTAB)
if (h.eq.0.) write(*,*) 'h must be nonzero in dfridr'
hh=h
a(1,1)=(func(x+hh)-func(x-hh))/(2._dp*hh)
dfridr = a(1,1) ! the zero-th order solution
err_int=BIG
iout=2
do i=2,NTAB
! Successive columns in the Neville tableau will go to smaller
! stepsizes and higher orders of extrapolation.
  hh=hh/CON
  a(1,i)=(func(x+hh)-func(x-hh))/(2._dp*hh)
  ! Try new, smaller stepsize.
  fac=CON2
  do j=2,i
    ! Compute extrapolations of various orders, requiring no new
    ! function evaluations.
    a(j,i)=(a(j-1,i)*fac-a(j-1,i-1))/(fac-1._dp)
    fac=CON2*fac
    errt=max(abs(a(j,i)-a(j-1,i)),abs(a(j,i)-a(j-1,i-1)))
    ! The error strategy is to compare each new extrapolation to one order lower, both at
    ! the present stepsize and the previous one.
    if (errt.le.err_int) then
    ! If error is decreased, save the improved answer.
       err_int=errt
      dfridr=a(j,i)
    endif
  enddo
  if(abs(a(i,i)-a(i-1,i-1)).ge.SAFE*err_int) then
  iout=2*i
  exit
  end if
  ! If higher order is worse by a signicant factor SAFE, then quit early.
enddo
err=err_int
END function 

! Subroutine dfridrMulDimDummy(dfunc,d,x,h,err,der)
! EXTERNAL :: dfunc
! Integer, Intent(in) :: d
! Real(dp), Intent(out) :: der(d), err
! REAL(dp),Intent(in) :: h,x
! INTEGER, parameter :: NTAB=40
! Real(dp), parameter :: CON=1.4_dp,CON2=CON*CON,BIG=1.D30,SAFE=20.0_dp
! Real(dp) :: err_int, fm(d),  fp(d)
! INTEGER :: i,j
! Real(dp), Allocatable :: a(:,:,:)
! REAL(dp) :: errt,fac,hh
! 
! Allocate( a(d,NTAB,NTAB) ) 
! 
! 
! Write(*,*) "a"
! der = 0._dp
! End subroutine dfridrMulDimDummy

Subroutine dfridrMulDim(dfunc,d,x,h,err,der)
! algorithm based on
! Ridders, C.J.F. 1982,
! Advances in Engineering Software
! vol. 4, no. 2, pp. 75–76. 

! Returns the derivative of a function func at a point x
! by Ridders' method of polynomial extrapolation. 
! The value h is input as an estimated initial stepsize; it need not be small, but rather should 
! be an increment in x over which func changes substantially. 
! An estimate of the error in the derivative is returned as err.
! Parameters: Stepsize is decreased by CON at each iteration. Max size of tableau is set by NTAB. Return when error is SAFE worse than the best so far.
Implicit None
EXTERNAL :: dfunc
INTEGER, parameter :: NTAB=40
! original: CON=1.4
Integer, Intent(in) :: d
Real(dp), Intent(out) :: der(d)
Real(dp), parameter :: CON=1.4_dp,CON2=CON*CON,BIG=1.D30,safe=20.0_dp
REAL(dp),Intent(in) :: h,x
Real(dp) :: err_int, fm(d),  fp(d)
Real(dp),Intent(out) :: err
INTEGER :: i,j
Real(dp), Allocatable :: a(:,:,:)
REAL(dp) :: errt,fac,hh

Allocate( a(d,NTAB,NTAB) ) 

if (h.eq.0.) write(*,*) 'h must be nonzero in dfridr'
hh=h
Call dfunc(x+hh,fp)
Call dfunc(x-hh,fm)
a(:,1,1)=(fp-fm)/(2._dp*hh)
der = a(:,1,1) ! the zero-th order solution
err_int=BIG
do i=2,NTAB
! Successive columns in the Neville tableau will go to smaller
! stepsizes and higher orders of extrapolation.
  hh=hh/CON
Call dfunc(x+hh,fp)
Call dfunc(x-hh,fm)
  a(:,1,i)=(fp-fm)/(2._dp*hh)
  ! Try new, smaller stepsize.
  fac=CON2
  do j=2,i
    ! Compute extrapolations of various orders, requiring no new
    ! function evaluations.
    a(:,j,i)=(a(:,j-1,i)*fac-a(:,j-1,i-1))/(fac-1._dp)
    fac=CON2*fac
    errt=max(maxval(abs(a(:,j,i)-a(:,j-1,i))),maxval(abs(a(:,j,i)-a(:,j-1,i-1))))
    ! The error strategy is to compare each new extrapolation to one order lower, both at
    ! the present stepsize and the previous one.
    if (errt.le.err_int) then
    ! If error is decreased, save the improved answer.
       err_int=errt
      der=a(:,j,i)
    endif
  enddo
  if(maxval(abs(a(:,i,i)-a(:,i-1,i-1))).ge.SAFE*err_int) then
  exit
  end if
  ! If higher order is worse by a signicant factor SAFE, then quit early.
enddo
err=err_int
Deallocate(a)
END Subroutine 


Real(dp) FUNCTION D2FRIDRMIXED(FUNC,X,Y,HX,HY,ERR)
IMPLICIT NONE
INTEGER NTAB
Real(dp) :: ERR,HX,HY,X,Y,FUNC,CON,CON2,BIG,SAFE
PARAMETER(CON=1.4_dp,CON2=CON*CON,BIG=1.0E+30_dp,NTAB=40,safe=20.0_dp)
EXTERNAL FUNC
INTEGER I,J
Real(dp) :: ERRT,FAC,HHX,HHY,A(NTAB,NTAB)
! IF(HX.EQ.0.0_dp) PAUSE 'HX MUST BE NONZERO IN DFRIDR'
! IF(HY.EQ.0.0_dp) PAUSE 'HY MUST BE NONZERO IN DFRIDR'
HHX=HX
HHY=HY
A(1,1)=(FUNC(X+HHX,Y+HHY)-FUNC(X+HHX,Y-HHY) &
& -FUNC(X-HHX,Y+HHY)+FUNC(X-HHX,Y-HHY))/(4*HHX*HHY)
ERR=BIG
DO I=2,NTAB
HHX=HHX/CON
HHY=HHY/CON
A(1,I)=(FUNC(X+HHX,Y+HHY)-FUNC(X+HHX,Y-HHY) &
& -FUNC(X-HHX,Y+HHY)+FUNC(X-HHX,Y-HHY))/(4.0_dp*HHX*HHY)
FAC=CON2
DO J=2,I
A(J,I)=(A(J-1,I)*FAC-A(J-1,I-1))/(FAC-1.0_dp)
FAC=CON2*FAC
ERRT=MAX1(ABS(A(J,I)-A(J-1,I)),ABS(A(J,I)-A(J-1,I-1)))
IF (ERRT.LE.ERR) THEN
ERR=ERRT
D2FRIDRMIXED=A(J,I)
ENDIF
ENDDO
IF(ABS(A(I,I)-A(I-1,I-1)).GE.SAFE*ERR) RETURN
ENDDO
RETURN
END function

Real(dp) FUNCTION D2FRIDR(FUNC,X,H,ERR)
IMPLICIT NONE
INTEGER NTAB
Real(dp) :: ERR,H,X,FUNC,CON,CON2,BIG,SAFE
PARAMETER(CON=1.4_dp,CON2=CON*CON,BIG=1.0E+30_dp,NTAB=40,safe=20.0_dp)
EXTERNAL FUNC
INTEGER I,J
Real(dp) :: ERRT,FAC,HH,A(NTAB,NTAB)

! Write(*,*) "X", X, H

! IF(H.EQ.0.0_dp) PAUSE 'H MUST BE NONZERO IN DFRIDR'
HH=H
A(1,1)=(FUNC(X+HH)-2.0_dp*FUNC(X)+FUNC(X-HH))/(HH**2.0_dp)
ERR=BIG
DO I=2,NTAB
HH=HH/CON
! Write(*,*) "X", X, HH
A(1,I)=(FUNC(X+HH)-2.0_dp*FUNC(X)+FUNC(X-HH))/(HH**2.0_dp)
! Write(*,*) "end"
FAC=CON2
DO J=2,I
A(J,I)=(A(J-1,I)*FAC-A(J-1,I-1))/(FAC-1.0_dp)
FAC=CON2*FAC
ERRT=MAX1(ABS(A(J,I)-A(J-1,I)),ABS(A(J,I)-A(J-1,I-1)))
IF (ERRT.LE.ERR) THEN
ERR=ERRT
D2FRIDR=A(J,I)
ENDIF
ENDDO
IF(ABS(A(I,I)-A(I-1,I-1)).GE.SAFE*ERR) RETURN
ENDDO
RETURN
END function


Subroutine D2FRIDRMIXEDmuldim(dFUNC,D,X,Y,HX,HY,ERR,der)
IMPLICIT NONE
EXTERNAL dFUNC
Integer, Intent(in) :: d
Real(dp), Intent(out) :: der(d)
Real(dp) :: ERR,HX,HY,X,Y,FUNC,CON,CON2,BIG,SAFE
Real(dp) :: fxpyp(d), fxpym(d), fxmyp(d), fxmym(d)
INTEGER, Parameter :: NTAB=40
PARAMETER(CON=1.4_dp,CON2=CON*CON,BIG=1.0E+30_dp,safe=20.0_dp)
Integer :: I,J
Real(dp) :: ERRT,FAC,HHX,HHY
Real(dp), Allocatable :: a(:,:,:)

Allocate( a(d,NTAB,NTAB) ) 


! IF(HX.EQ.0.0_dp) PAUSE 'HX MUST BE NONZERO IN DFRIDR'
! IF(HY.EQ.0.0_dp) PAUSE 'HY MUST BE NONZERO IN DFRIDR'
HHX=HX
HHY=HY

Call dFUNC(X+HHX,Y+HHY,fxpyp)
Call dFUNC(X+HHX,Y-HHY,fxpym)
Call dFUNC(X-HHX,Y+HHY,fxmyp)
Call dFUNC(X-HHX,Y-HHY,fxmym)

A(:,1,1)=(fxpyp-fxpym -fxmyp+fxmym)/(4*HHX*HHY)
ERR=BIG
DO I=2,NTAB
HHX=HHX/CON
HHY=HHY/CON

Call dFUNC(X+HHX,Y+HHY,fxpyp)
Call dFUNC(X+HHX,Y-HHY,fxpym)
Call dFUNC(X-HHX,Y+HHY,fxmyp)
Call dFUNC(X-HHX,Y-HHY,fxmym)

A(:,1,I)=(fxpyp-fxpym -fxmyp+fxmym)/(4.0_dp*HHX*HHY)
FAC=CON2
DO J=2,I
A(:,J,I)=(A(:,J-1,I)*FAC-A(:,J-1,I-1))/(FAC-1.0_dp)
FAC=CON2*FAC
ERRT=MAX1(MaxVal(ABS(A(:,J,I)-A(:,J-1,I))),MaxVal(ABS(A(:,J,I)-A(:,J-1,I-1))))
IF (ERRT.LE.ERR) THEN
ERR=ERRT
der=A(:,J,I)
ENDIF
ENDDO
IF(MaxVal(ABS(A(:,I,I)-A(:,I-1,I-1))).GE.SAFE*ERR) Exit
ENDDO

Deallocate(a)

END Subroutine

Subroutine D2FRIDRmuldim(dFUNC,d,X,H,ERR,der)
IMPLICIT NONE
EXTERNAL dFUNC
INTEGER, Parameter :: NTAB=40
Integer, Intent(in) :: d
Real(dp), Intent(out) :: der(d)
Real(dp) :: ERR,H,X,FUNC,CON,CON2,BIG,SAFE
PARAMETER(CON=1.4_dp,CON2=CON*CON,BIG=1.0E+30_dp,safe=20.0_dp)
INTEGER I,J
Real(dp) :: ERRT,FAC,HH, fn(d), f(d),fp(d)
Real(dp), Allocatable :: a(:,:,:)

Allocate( a(d,NTAB,NTAB) ) 
! Write(*,*) "X", X, H

! IF(H.EQ.0.0_dp) PAUSE 'H MUST BE NONZERO IN DFRIDR'
HH=H

Call dFunc(x+hh,fp)
Call dFunc(x,f)
Call dFunc(x-hh,fn)

A(:,1,1)=(fp-2.0_dp*f+fn)/(HH**2.0_dp)
ERR=BIG
DO I=2,NTAB
HH=HH/CON

Call dFunc(x+hh,fp)
Call dFunc(x,f)
Call dFunc(x-hh,fn)

A(:,1,I)=(fp-2.0_dp*f+fn)/(HH**2.0_dp)
! Write(*,*) "end"
FAC=CON2
DO J=2,I
A(:,J,I)=(A(:,J-1,I)*FAC-A(:,J-1,I-1))/(FAC-1.0_dp)
FAC=CON2*FAC
ERRT=MAX1(MaxVal(ABS(A(:,J,I)-A(:,J-1,I))),MaxVal(ABS(A(:,J,I)-A(:,J-1,I-1))))
IF (ERRT.LE.ERR) THEN
ERR=ERRT
der=A(:,J,I)
ENDIF
ENDDO
IF(MaxVal(ABS(A(:,I,I)-A(:,I-1,I-1))).GE.SAFE*ERR) RETURN
ENDDO
Deallocate(a)
END Subroutine


Real(dp) function partialDiff_Ridders(func,x,k,n,err,h,iout)
! wrapper function to calculate the partial derivative of func w.r.t. to k-th variable
! evaluated at the n-dim. point x, starting with stepsize h. 
! returns error estimate err 
Implicit None
Integer,Intent(in) :: n,k
Integer :: iout
Real(dp),External :: func
Real(dp),Intent(in) :: x(n), h
Real(dp),Intent(out) :: err
Real(dp) :: xtemp(n)

partialDiff_Ridders=dfridr(func_k,x(k),Min(1._dp,hstep_pn*x(k)),err,iout)
! partialDiff_Ridders=dfridr(func_k,x(k),hstep_pn*x(k),err,iout)
  Contains 
  Real(dp) function func_k(y)
  ! projects out other components
  Implicit None
  Real(dp) :: y
  xtemp = x
  xtemp(k)=y
  func_k = func(xtemp)
  End function
End function

function partialDiff_RiddersMulDim(func,d,x,k,n,err)
! wrapper function to calculate the partial derivative of func w.r.t. to k-th variable
! evaluated at the n-dim. point x, starting with stepsize h. 
! returns error estimate err 
Implicit None
External :: func
Integer,Intent(in) :: n,k,d
Integer :: iout
Real(dp) :: partialDiff_RiddersMulDim(d)
Real(dp) :: test(d)
Real(dp),Intent(in) :: x(n)
Real(dp),Intent(out) :: err
Real(dp) :: xtemp(n),hrel(n)


! hrel(1) = hstep_sa_vd
! hrel(2) = hstep_sa_vu

! Write(*,*) x
Call dfridrMulDim(func_k,d,x(k),Min(1._dp,hstep_sa*x(k)),err,test)
! Call dfridrMulDim(func_k,d,x(k),hstep_sa*x(k),err,test)
partialDiff_RiddersMulDim = test
! dfridrMulDim(dfunc,d,x,h,err,der)

  Contains 

  subroutine func_k(y,out)
  ! projects out other components
  Implicit None
  Real(dp),Intent(in) :: y
  Real(dp),Intent(out) :: out(d)
  xtemp = x
  xtemp(k)=y
  Call func(xtemp,out)
!   func_k1 = func(xtemp)
  End subroutine

End function

function partialDiffXY_RiddersMulDim(func,d,x,k1,k2,n,err)
! wrapper function to calculate second partial derivative w.r.t. k1-th variable, then k2-th
! evaluated at n-dim. point x
! applies partialDiff_Ridders twice
Implicit None
External :: func
Integer,Intent(in) :: n,k1,k2,d
Real(dp) :: partialDiffXY_RiddersMulDim(d)
Integer :: itemp=0,i1
Real(dp),Intent(in) :: x(n)
Real(dp),Intent(out) :: err
Real(dp) :: xtemp(n), hrel(n)

! hrel(1) = hstep_sa_vd
! hrel(2) = hstep_sa_vu

If (k1.eq.k2) Then
!  Call D2FRIDRmuldim(func_k1,d,x(k1),hstep_sa*x(k1),err,partialDiffXY_RiddersMulDim)
!  Call D2FRIDRmuldim(func_k1,d,x(k1),hstep_sa,err,partialDiffXY_RiddersMulDim)
 Call D2FRIDRmuldim(func_k1,d,x(k1),Min(1._dp,x(k1)*hstep_sa),err,partialDiffXY_RiddersMulDim)
Else 
!  Call D2FRIDRMIXEDmuldim(func_k1k2,d,x(k2),x(k1),hstep_sa*x(k2), hstep_sa*x(k1),err,partialDiffXY_RiddersMulDim)
!  Call D2FRIDRMIXEDmuldim(func_k1k2,d,x(k2),x(k1),hstep_sa, hstep_sa,err,partialDiffXY_RiddersMulDim)
Call D2FRIDRMIXEDmuldim(func_k1k2,d,x(k2),x(k1),Min(1._dp,hstep_sa*x(k2)), Min(1._dp, hstep_sa*x(k1)),err,partialDiffXY_RiddersMulDim)
end if

Contains 


  subroutine func_k1(y,out)
  ! projects out other components
  Implicit None
  Real(dp),Intent(in) :: y
  Real(dp),Intent(out) :: out(d)
  xtemp = x
  xtemp(k1)=y
  Call func(xtemp,out)
!   func_k1 = func(xtemp)
  End subroutine

  subroutine func_k1k2(y1,y2,out)
  ! projects out other components
  Implicit None
  Real(dp),Intent(in) :: y1,y2
  Real(dp),Intent(out) :: out(d)
  xtemp = x
  xtemp(k2)=y1
  xtemp(k1)=y2
  Call func(xtemp,out)
!   func_k1k2 = func(xtemp)
  End subroutine

End function


Subroutine ScanEffPot(func,func2,x0,y0,hx,hy,N)
Implicit none
Real(dp),External :: func,func2
Real(dp),Intent(in) :: x0,y0,hx,hy
Integer,intent(in) :: N
Real(dp) :: x,y,dx,dy
Integer :: i,j
open(394729,file="scaneffpot.out",status="replace")
open(394728,file="scaneffpot2L.out",status="replace")
write(394729,*) x0,y0,func((/x0,y0/))
write(394728,*) x0,y0,func2((/x0,y0/))
dx=(hx)/(N-1)
dy=(hy)/(N-1)
do i=-N+2,N
 do j=-N+2,N
  x=x0+(i-1)*dx
  y=y0+(j-1)*dy
  write(394729,*) x,y,func((/x,y/))
  write(394728,*) x,y,func2((/x,y/))
 end do
end do
close(394729)
close(394728)
End subroutine


Real(dp) function partialDiffXY_Ridders(func,x,k1,k2,n,err,h,iout)
! wrapper function to calculate second partial derivative w.r.t. k1-th variable, then k2-th
! evaluated at n-dim. point x
! applies partialDiff_Ridders twice
Implicit None
Integer,Intent(in) :: n,k1,k2
Integer :: itemp=0,i1,iout
Real(dp),External :: func
Real(dp),Intent(in) :: x(n),h
Real(dp),Intent(out) :: err
Real(dp) :: xtemp(n),hrel(n)
iout=0

! hrel(1) = hstep_sa_vd
! hrel(2) = hstep_sa_vu

! ! partialDiffXY_Ridders = partialDiff_Ridders(funcD1p,x,k2,n,err,h,i1)
If (k1.eq.k2) Then
!  write(*,*) k1,k2
! partialDiffXY_Ridders = D2FRIDR(func_k1,x(k1),hstep_pn*x(k1),err)
! partialDiffXY_Ridders = D2FRIDR(func_k1,x(k1),hstep_pn,err)
partialDiffXY_Ridders = D2FRIDR(func_k1,x(k1),Min(1._dp,hstep_pn*x(k1)),err)
Else 
partialDiffXY_Ridders = D2FRIDRMIXED(func_k1k2,x(k2),x(k1),Min(1._dp,hstep_pn*x(k2)), Min(1._dp,hstep_pn*x(k1)),err)
! partialDiffXY_Ridders = D2FRIDRMIXED(func_k1k2,x(k2),x(k1),hstep_pn, hstep_pn,err)
! partialDiffXY_Ridders = D2FRIDRMIXED(func_k1k2,x(k2),x(k1),hstep_pn*x(k2), hstep_pn*x(k1),err)
end if

Contains 
  Real(dp) function funcD1p(x)
  Implicit None
  Real(dp) :: x(n)
  funcD1p = partialDiff_Ridders(func,x,k1,n,err,h,itemp)
  iout = iout + itemp
  End function

  Real(dp) function func_k1(y)
  ! projects out other components
  Implicit None
  Real(dp) :: y
  xtemp = x
  xtemp(k1)=y
  func_k1 = func(xtemp)
  End function

  Real(dp) function func_k1k2(y1,y2)
  ! projects out other components
  Implicit None
  Real(dp) :: y1,y2
  xtemp = x
  xtemp(k2)=y1
  xtemp(k1)=y2
  func_k1k2 = func(xtemp)
  End function

End function

Real(dp) function partialDiffXY_Ridders2(func,x,k1,k2,n,err,h,iout)
! wrapper function to calculate second partial derivative w.r.t. k1-th variable, then k2-th
! evaluated at n-dim. point x
! applies partialDiff_Ridders twice
Implicit None
Integer,Intent(in) :: n,k1,k2
Integer :: itemp=0,i1,iout
Real(dp),External :: func
Real(dp),Intent(in) :: x(n),h(2)
Real(dp),Intent(out) :: err
iout=0
partialDiffXY_Ridders2 = partialDiff_Ridders(funcD1p,x,k2,n,err,h(k2),i1)
Contains 
  Real(dp) function funcD1p(x)
  Implicit None
  Real(dp) :: x(n)
  funcD1p = partialDiff_Ridders(func,x,k1,n,err,h(k1),itemp)
  iout = iout + itemp
  End function
End function

!! These two-loop integral functions J(x),J(x,y),I(x,y,z) are taken from
!! Stephen P. Martin, arXiv:hep-ph/111209v2, 29 Mar 2002
!! FERMILAB-Pub-01/348-T



Real(dp) Function J_SMartin_1x(x,Q2)
Implicit None
! x is supposed to be a squared mass
Real(dp),Intent(in) :: x,Q2
If (Q2.le.0._dp) Then 
  write(*,*) 'invalid renormalization scale!'
  return
end if
If (VerySmallM(x,Q2)) Then
   J_SMartin_1x = 0._dp
Else
   J_SMartin_1x = (x)*(zlog(Cmplx(x/Q2,0._dp,dp))-1._dp)
End If

! J_SMartin_1x = 0._dp
 
End Function J_SMartin_1x



Real(dp) Function J_SMartin_2x(x,y,Q2)
Implicit None
! x,y are supposed to be squared masses
! symmetric x <-> y
Real(dp),Intent(in) :: x,y,Q2
If (Q2.le.0._dp) Then 
  write(*,*) 'invalid renormalization scale!'
  return
end if
If (VerySmallM(x,y,y,Q2).or.(VerySmallM(y,x,x,Q2))) Then
 J_SMartin_2x = 0
Else
 J_SMartin_2x = J_SMartin_1x(x,Q2)*J_SMartin_1x(y,Q2)
End if

! J_SMartin_2x = 0._dp

End Function J_SMartin_2x



Complex(dp) Function RFunction(x,y,z)
Implicit None
Complex(dp), Intent(in) :: x,y,z
Complex(dp) :: temp
temp = x**2+y**2+z**2-2._dp*x*y-2._dp*x*z-2._dp*y*z
RFunction = sqrt(temp)
! If (temp.lt.0._dp) Then
!   RFunction = Cmplx(0.,+sqrt(-temp),dp)
! Else
!   RFunction = Cmplx(sqrt(temp),0.,dp)
! End If
End Function RFunction






Complex(dp) Function I_SMartin(x_in,y_in,z_in,Q2)
Implicit None
! x_in,y_in,z_in are supposed to be squared masses
! symmetric under interchange of any two of these
Real(dp),Intent(in) :: x_in,y_in,z_in,Q2
Complex(dp) :: res,x,y,z
x = x_in
y = y_in
z = z_in
If (Q2.le.0._dp) Then 
  write(*,*) 'invalid renormalization scale!'
  return
end if
Call SortArguments3C(x,y,z) ! sort x<=y<=z


If (SmallM(x,y,z,Q2)) Then
 I_SMartin = I_SMartin_ex(x_in,y_in,z_in,Q2)

! !  ! I(0,y,z)
! !  If (SmallM(y,x,z,Q2)) Then
! !   If (SmallM(z,y,x,Q2)) Then 
! !    I_SMartin = ZeroC ! I(0,0,0)=0
! !   Else
! !    I_SMartin = -0.5_dp*z*(log(z/Q2))**2 &
! !       & + 2*z*log(z/Q2)-2.5_dp*z-pi**2*z/6._dp
! !    ! I(0,0,z)
! !   End If
! !  Else If (SmallD(z,y)) Then
! !   ! I(0,y,y)
! ! !   Write(*,*) Real(x,dp),Real(y,dp),Real(z,dp)
! !   I_SMartin = -y*(zlog(y/Q2))**2+4._dp*y*zlog(y/Q2)-5._dp*y
! ! ! I_SMartin = 0.
! !  Else
! ! !   Write(*,*) Real(x,dp),Real(y,dp),Real(z,dp)
! !   ! I(0,y,z), z>y
! !   I_SMartin = (z-y)*(CLi2_mod(y/z)-log(z/y)*log((z-y)/Q2) &
! !   & +0.5_dp*(log(z/Q2))**2-pi**2/6._dp)  &
! !   & -2.5_dp*(z+y)+2*y*log(y/Q2)+2*z*log(z/Q2) & 
! !   & -z*log(z/Q2)*log(y/Q2)
! ! ! I_SMartin =0
! !  End If

! I_SMartin = 0._dp

Else ! I(x,y,z) general case


res = Cmplx(0._dp,0._dp)
res=res + 0.5_dp*(x-y-z)*zlog(y/Q2)*zlog(z/Q2)
res=res + 0.5_dp*(y-x-z)*zlog(x/Q2)*zlog(z/Q2)
res=res + 0.5_dp*(z-x-y)*zlog(x/Q2)*zlog(y/Q2)
res=res + 2._dp*x*zlog(x/Q2)
res=res + 2._dp*y*zlog(y/Q2)
res=res + 2._dp*z*zlog(z/Q2)
res=res - 2.5_dp*(x+y+z)
res=res - 0.5_dp*XiFunction(x,y,z)

! res = 0._dp

I_SMartin = res


End If

! I_SMartin = 0._dp


End Function I_SMartin

Complex(dp) Function XiFunction(x0,y0,z0)
Implicit None
Complex(dp), Intent(in) :: x0,y0,z0
Complex(dp) :: x,y,z
Complex(dp) :: res,R
x=x0
y=y0
z=z0
Call SortArguments3C(x,y,z)
R=Rfunction(x,y,z)
res = Cmplx(0.,0.,dp)
res = res + 2._dp*log((z+x-y-R)/(2._dp*z))*log((z+y-x-R)/(2._dp*z))
res = res - log(x/z)*log(y/z)
res = res - 2._dp*CLi2_mod((z+x-y-R)/(2._dp*z))
res = res - 2._dp*CLi2_mod((z+y-x-R)/(2._dp*z))
res = res + (pi**2)/3._dp
res = R*res
XiFunction = res
End Function XiFunction

!! sorts three real arguments a,b,c from small to large
!! and returns them
Subroutine SortArguments3(a,b,c)
Implicit None
Real(dp), Intent(inout) :: a,b,c
Real(dp) :: x,y,z
x=a ! assume a is smallest
y=b
z=c
If (b.le.a) Then
 x=b
 y=a
 z=c
End If
If (c.le.x) Then
 x=c
 y=a
 z=b
End If
! compare last two elements
If (z.le.y) Then
 a=x ! output
 b=z
 c=y
Else
 a=x !output
 b=y
 c=z
End If
End Subroutine SortArguments3


!! sorts three complex arguments a,b,c from small to large
!! and returns them
Subroutine SortArguments3C(a,b,c)
Implicit None
Complex(dp), Intent(inout) :: a,b,c
Complex(dp) :: x,y,z
x=a ! assume a is smallest
y=b
z=c
If (Abs(b).le.Abs(a)) Then
 x=b
 y=a
 z=c
End If
If (Abs(c).le.Abs(x)) Then
 x=c
 y=a
 z=b
End If
! compare last two elements
If (Abs(z).le.Abs(y)) Then
 a=x ! output
 b=z
 c=y
Else
 a=x !output
 b=y
 c=z
End If
End Subroutine SortArguments3C

 Complex(DP) Function CLI2_mod(Z)
 !--------------------------------------------------------------
 !     routine for the complex dilogarithm function
 !--------------------------------------------------------------
 Implicit None      
  !-------
  ! input
  !-------
  Complex(DP), Intent(in) :: Z

  !-----------------
  ! local variables
  !-----------------
  Complex(DP) :: sumC, cy, cz, cz2, CLI2
  Real(dp) :: rz, iz, az
  Integer :: i1, jsgn, ipi12
  !---------------------------------------------
  ! Bernulli numbers / (2 n + 1)!
  !---------------------------------------------
  Real(dp), Parameter :: bf(20) = (/ - 1._dp/4._dp, + 1._dp/36._dp        &
       & , - 1._dp/36.e2_dp, + 1._dp/21168.e1_dp,  - 1._dp/108864.e2_dp   &
       & , + 1._dp/52690176.e1_dp,  - 691._dp/16999766784.e3_dp           &
       & , + 1._dp/1120863744.e3_dp,  - 3617._dp/18140058832896.e4_dp     &
       & , + 43867._dp/97072790126247936.e3_dp                            &
       & , - 174611._dp/168600109166641152.e5_dp                          &
       & , + 77683._dp/32432530090601152512.e4_dp                         &
       & , - 236364091._dp/4234560341829359173632.e7_dp                   &
       & , + 657931._dp/5025632054039239458816.e6_dp                      &
       & , - 3392780147._dp/109890470493622010006470656.e7_dp             &
       & , +172.3168255201_dp/2355349904102724211909.3102313472e6_dp      &
       & , -770.9321041217_dp/4428491985594062112714.2791446528e8_dp      &
       & ,  4.1576356446138997196178996207752266734882541595116e-29_dp    &
       & , -9.9621484882846221031940067024558388498548600173945e-31_dp    &
       & ,  2.3940344248961653005211679878937495629342791569329e-32_dp    &
       & /)

  rz = Real(z,dp)
  iz = Aimag(z)
  az = Sqrt(rz**2 + iz**2)
  !------------------
  ! special cases
  !------------------
  If (iz.Eq.0._dp) Then
    If (rz.gt.1._dp) Then
    CLi2_mod = Cmplx( Li2(rz), -pi*log(rz),dp)
    Else
    CLi2_mod = Cmplx( Li2(rz), 0.,dp)
    End If
   Return
  Else If (az.Lt.Epsilon(1._dp)) Then
   CLi2_mod = z
   Return
  End If
  !-----------------------------------------------------
  ! transformation to |z|<1, Re(z)<=0.5
  !-----------------------------------------------------
  If (rz.Le.0.5_dp) Then
   If (az.Gt.1._dp) Then
    cy = -0.5_dp * Log(-z)**2
    cz = - Log(1._dp - 1._dp / z)
    jsgn = -1
    ipi12 = -2
   Else !  (az.le.1._dp)
    cy = 0
    cz = - Log(1._dp - z)
    jsgn = 1
    ipi12 = 0
   End If
  Else ! rz.gt.0.5_dp
   If (az.Le.Sqrt(2*rz)) Then
    cz = - Log(z)
    cy = cz * Log(1._dp - z)
    jsgn = -1
    ipi12 = 2
   Else ! (az.gt.Sqrt(2*rz))
    cy = -0.5_dp * Log(-z)**2
    cz = - Log(1._dp - 1._dp / z)
    jsgn = -1
    ipi12 = -2
   End If
  End If
  !--------------------------------------------
  ! the dilogarithm
  !--------------------------------------------
  cz2 = cz**2
  sumC = cz2 * bf(20)
  Do i1=3,19
   sumC = cz2 * ( sumC + bf(22-i1) )
  End Do
  ! watch the powers of z
  sumC = cz + cz2 * (bf(1) + cz * (bf(2) + sumC))
  If (jsgn.Eq.1) Then
   CLi2 = sumC + cy
  Else
   CLi2 = - sumC + cy
  End If
  If (ipi12.Ne.0) Cli2 = Cli2 + ipi12 * pi2o12
  
  CLI2_mod = CLI2
 End Function CLI2_mod


!--------------------------------------------
! 2-Loop functions for different contributions
! 
!--------------------------------------------

  !--------------------------------------------
  ! three scalars, two cubic couplings
  !--------------------------------------------
Complex(dp) Function Fep_SSS(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
 Fep_SSS = -I_SMartin(x,y,z,Q2)
End Function Fep_SSS

  !--------------------------------------------
  ! two scalars, one quartic couplings
  !--------------------------------------------
Complex(dp) Function Fep_SS(x,y,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,Q2
 Fep_SS = J_SMartin_2x(x,y,Q2)
End Function Fep_SS

  !--------------------------------------------
  ! one scalar, two fermions, two cubic couplings
  !--------------------------------------------
Complex(dp) Function Fep_FFS(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
Complex(dp) :: res
res=Cmplx(0.,0.,dp)
res=res+J_SMartin_2x(x,y,Q2)-J_SMartin_2x(x,z,Q2)-J_SMartin_2x(y,z,Q2)
res=res+(x+y-z)*I_SMartin(x,y,z,Q2)
Fep_FFS=res
End Function Fep_FFS

  !--------------------------------------------
  ! like FFS, with mass insertion
  !--------------------------------------------
Complex(dp) Function Fep_FFSbar(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
Fep_FFSbar=2*I_SMartin(x,y,z,Q2)
End Function Fep_FFSbar

  !--------------------------------------------
  ! two scalars, one vector, two cubic couplings
  !--------------------------------------------
Complex(dp) Function Fep_SSV(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
Complex(dp) :: res
res=Cmplx(0.,0.,dp)

If (SmallM(z,x,y,Q2)) Then
  ! f_SSV(x,y,0) special case
 res=res+(x+y)**2+3._dp*(x+y)*I_SMartin(x,y,0._dp,Q2)
 res=res+3._dp*J_SMartin_2x(x,y,Q2)
 res=res-2._dp*x*J_SMartin_1x(x,Q2)
 res=res-2._dp*y*J_SMartin_1x(y,Q2)
Else
  ! f_SSV(x,y,z) general case
res = (-x**2-y**2-z**2+2._dp*(x*y+x*z+y*z))*I_SMartin(x,y,z,Q2)
res = res+I_SMartin(0._dp,x,y,Q2)*((x-y)**2)
res = res+(y-x-z)*J_SMartin_2x(x,z,Q2)+(x-y-z)*J_SMartin_2x(y,z,Q2)
res = res + z*J_SMartin_2x(x,y,Q2)
res = res/z
res = res+2._dp*(x+y-z/3._dp)*J_SMartin_1x(z,Q2)
End If

Fep_SSV = res
End Function Fep_SSV

  !--------------------------------------------
  ! one scalar, one vector, one quartic coupling
  !--------------------------------------------
Complex(dp) Function Fep_VS(x,y,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,Q2
 Fep_VS = 3._dp*J_SMartin_2x(x,y,Q2)
End Function Fep_VS

  !--------------------------------------------
  ! one scalar, two vectors, two cubic couplings
  !--------------------------------------------
Complex(dp) Function Fep_VVS(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
Real(dp) :: xt
Complex(dp) :: res
res=Cmplx(0.,0.,dp)
If (SmallM(x,y,z,Q2)) Then
 If (SmallM(y,x,z,Q2)) Then
  ! f_VSS(0,0,z)
  res=-3._dp*I_SMartin(0._dp,0._dp,z,Q2)
  res=res+1.5_dp*J_SMartin_1x(z,Q2)-0.25_dp*z
  Fep_VVS=res
  return
 Else
  xt=y
 End If
Else ! x>0
 If (SmallM(y,x,z,Q2)) Then
  xt=x
 Else ! x>0 and y>0 general case
   ! f_VSS(x,y,z)
 res=(-x**2-y**2-z**2)
 res=res-10._dp*x*y+2._dp*x*z+2._dp*y*z
 res=res*I_SMartin(x,y,z,Q2)
 res=res+(x-z)**2*I_SMartin(0._dp,x,z,Q2)
 res=res+(y-z)**2*I_SMartin( 0._dp,y,z,Q2)
 res=res-z**2*I_SMartin(0._dp,0._dp,z,Q2)
 res=res+(z-x-y)*J_SMartin_2x(x,y,Q2)
 res=res+y*J_SMartin_2x(x,z,Q2)
 res=res+z*J_SMartin_2x(y,z,Q2)
 res=res/(4._dp*x*y)
 res=res+0.5_dp*J_SMartin_1x(x,Q2)
 res=res+0.5_dp*J_SMartin_1x(y,Q2)
 Fep_VVS=res
 Return
 End If
End If
! case f_VSS(xt,0,z) with xt=x or y
res=xt/4._dp+0.5_dp*z
res=res-0.75_dp*z/xt*I_SMartin(0._dp,0._dp,z,Q2)
res=res+(0.75_dp*z/xt-9._dp/4._dp)*I_SMartin(0._dp,xt,z,Q2)
res=res+0.75_dp/xt*J_SMartin_2x(xt,z,Q2)
Fep_VVS=res
End Function Fep_VVS

  !--------------------------------------------
  ! two fermions, one vector, two cubic couplings
  !--------------------------------------------
Complex(dp) Function Fep_FFV(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
Complex(dp) :: res
res=Cmplx(0.,0.,dp)
If (SmallM(z,x,y,Q2)) Then
 ! f_FFV(x,y,0)
 res=-(x+y)**2
 res=res+2._dp*x*J_SMartin_1x(x,Q2)
 res=res+2._dp*y*J_SMartin_1x(y,Q2)
 Fep_FFV=res
 Return
Else
 ! f_FFV(x,y,z) general case
 res=x**2+y**2-2._dp*z**2
 res=res-2._dp*x*y+x*z+y*z
 res=res*I_SMartin(x,y,z,Q2)
 res=res-(x-y)**2*I_SMartin(0._dp,x,y,Q2)
 res=res+(x-y-2._dp*z)*J_SMartin_2x(x,z,Q2)
 res=res+(y-x-2._dp*z)*J_SMartin_2x(y,z,Q2)
 res=res+2._dp*z*J_SMartin_2x(x,y,Q2)
 res=res/z
 res=res+2._dp*(-x-y+z/3._dp)*J_SMartin_1x(z,Q2)
 Fep_FFV=res
 Return
End If
End Function Fep_FFV

  !--------------------------------------------
  ! like FFV with mass insertion
  !--------------------------------------------
Complex(dp) Function Fep_FFVbar(x,y,z,Q2)
Implicit None
Real(dp), Intent(in) :: x,y,z,Q2
 Fep_FFVbar=6._dp*I_SMartin(x,y,z,Q2)
End Function Fep_FFVbar

  !--------------------------------------------
  ! sum of three diagrams:
  ! two vectors, one quartic coupling
  ! + three vectors, two cubic couplings
  ! + one vector, two ghosts, two cubic couplings
  !--------------------------------------------
Complex(dp) Function Fep_gauge(a,b,c,Q2)
Implicit None
Real(dp), Intent(in) :: a,b,c,Q2
Real(dp) :: x,y,z
 Complex(dp) :: res
 res=Cmplx(0.,0.,dp)
x=a
y=b
z=c
Call SortArguments3(x,y,z)
If (SmallM(x,y,z,Q2)) Then
 If (SmallM(y,x,z,Q2)) Then
  If (SmallM(z,y,x,Q2)) Then
   res=0._dp
  Else
  ! f_gauge(0,0,z)
  res=13*z*I_SMartin(0._dp,0._dp,z,Q2)
  res=res-71._dp/6._dp*z*J_SMartin_1x(z,Q2)
  res=res+19._dp/4._dp*z**2
  End If
 Else
 ! f_gauge(0,y,z)
 res=43._dp*z**2*y+43._dp*z*y**2-7._dp*z**3-7._dp*y**3
 res=res*I_SMartin(0._dp,z,y,Q2)
 res=res+(2._dp*y+7._dp*z)*z**2*I_SMartin(0._dp,0._dp,z,Q2)
 res=res+(2._dp*z+7._dp*y)*y**2*I_SMartin(0._dp,0._dp,y,Q2)
 res=res+(34*z*y-7*z**2-7*y**2)*J_SMartin_2x(z,y,Q2)
 res=res/(4._dp*z*y)
 res=res+3*z**2+3*y**2+5.5_dp*z*y
 res=res-25._dp/3._dp*z*J_SMartin_1x(z,Q2)
 res=res-25._dp/3._dp*y*J_SMartin_1x(y,Q2)
 res=res+5*y*J_SMartin_1x(z,Q2)
 res=res+5*z*J_SMartin_1x(y,Q2)
 End If
Else 
! f_gauge(x,y,z) general case
 res=fgauge_aux(x,y,z,Q2)
 res=res+fgauge_aux(y,x,z,Q2)
 res=res+fgauge_aux(z,y,x,Q2)
End If

Fep_gauge=res
End Function Fep_gauge

Complex(dp) Function fgauge_aux(x,y,z,Q2)
 Real(dp), Intent(in) :: x,y,z,Q2
 Complex(dp) :: res
 res=Cmplx(0.,0.,dp)
 res=-x**4-8*x**3*(y+z)+32*x**2*y*z+18*y**2*z**2
 res=res*I_SMartin(x,y,z,Q2)
 res=res+(y-z)**2*(y**2+10*y*z+z**2)*I_SMartin(0._dp,y,z,Q2)
 res=res+x**2*(2*y*z-x**2)*I_SMartin(0._dp,0._dp,x,Q2)
 res=res+(x**2-9*(y**2+z**2-x*y-x*z)+14*y*z)*x*J_SMartin_2x(y,z,Q2)
 res=res+(22*(y+z)-40*x/3._dp)*x*y*z*J_SMartin_1x(x,Q2)
 res=res/(4._dp*x*y*z)
 fgauge_aux=res
End Function fgauge_aux


Logical Function SmallDC(x,y) 
Implicit None
Complex(dp), Intent(in) :: x,y
If (Max(Abs(x),Abs(y)).lt.epsD) Then
 SmallDC = .True.
Else If ((Abs(x-y)/Max(Abs(x),Abs(y))).le.epsD) Then
 SmallDC = .True.
Else
 SmallDC = .False.
End if
End Function SmallDC


Logical Function SmallDR(x,y) 
Implicit None
Real(dp), Intent(in) :: x,y
If (Max(Abs(x),Abs(y)).lt.epsD) Then
 SmallDR = .True.
Else If ((Abs(x-y)/Max(Abs(x),Abs(y))).le.epsD) Then
 SmallDR = .True.
Else
 SmallDR = .False.
End if
End Function SmallDR


Logical Function SmallMR(x,y,z,Q) 
Implicit None
Real(dp), Intent(in) :: x,y,z
Real(dp), Intent(in) :: Q
If (Max(Max(Abs(x),Abs(y)),Abs(z)).le.epsM) Then
 SmallMR = .True.
Else If ((Abs(x)/Max(Q,Max(Abs(y),Abs(z)))).le.epsM) Then
 SmallMR = .True.
Else
 SmallMR = .False.
End if
End Function SmallMR

Logical Function SmallMC(x,y,z,Q) 
Implicit None
Complex(dp), Intent(in) :: x,y,z
Real(dp), Intent(in) :: Q
If (Max(Max(Abs(x),Abs(y)),Abs(z)).le.epsM) Then
 SmallMC = .True.
Else If ((Abs(x)/Max(Q,Max(Abs(y),Abs(z)))).lt.epsM) Then
 SmallMC = .True.
Else
 SmallMC = .False.
End if
End Function SmallMC

Logical Function SmallMR2(x,y) 
Implicit None
Real(dp), Intent(in) :: x,y
If (Max(Abs(x),Abs(y)).le.epsM) Then
 SmallMR2 = .True.
Else If (Abs(x/y).le.epsM) Then
 SmallMR2 = .True.
Else
 SmallMR2 = .False.
End if
End Function SmallMR2

Logical Function SmallMC2(x,y) 
Implicit None
Complex(dp), Intent(in) :: x,y
If (Max(Abs(x),Abs(y)).le.epsM) Then
 SmallMC2 = .True.
Else If (Abs(x/y).le.epsM) Then
 SmallMC2 = .True.
Else
 SmallMC2 = .False.
End if
End Function SmallMC2




End Module EffPotFunctions
