! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:47 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module RGEs_Inert2 
 
Use Control 
Use Settings 
Use Model_Data_Inert2 
Use Mathematics 
 
Logical,Private,Save::OnlyDiagonal

Real(dp),Parameter::id3R(3,3)=& 
   & Reshape(Source=(/& 
   & 1,0,0,& 
 &0,1,0,& 
 &0,0,1& 
 &/),shape=(/3,3/)) 
Contains 


Subroutine GToParameters69(g,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,              & 
& MHD2,MHU2)

Implicit None 
Real(dp), Intent(in) :: g(69) 
Real(dp),Intent(out) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(out) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters69' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
lam5= Cmplx(g(4),g(5),dp) 
lam1= Cmplx(g(6),g(7),dp) 
lam4= Cmplx(g(8),g(9),dp) 
lam3= Cmplx(g(10),g(11),dp) 
lam2= Cmplx(g(12),g(13),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Ye(i1,i2) = Cmplx( g(SumI+14), g(SumI+15), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yd(i1,i2) = Cmplx( g(SumI+32), g(SumI+33), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yu(i1,i2) = Cmplx( g(SumI+50), g(SumI+51), dp) 
End Do 
 End Do 
 
MHD2= g(68) 
MHU2= g(69) 
Do i1=1,69 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters69

Subroutine ParametersToG69(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,g)

Implicit None 
Real(dp), Intent(out) :: g(69) 
Real(dp), Intent(in) :: g1,g2,g3,MHD2,MHU2

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG69' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
g(4) = Real(lam5,dp)  
g(5) = Aimag(lam5)  
g(6) = Real(lam1,dp)  
g(7) = Aimag(lam1)  
g(8) = Real(lam4,dp)  
g(9) = Aimag(lam4)  
g(10) = Real(lam3,dp)  
g(11) = Aimag(lam3)  
g(12) = Real(lam2,dp)  
g(13) = Aimag(lam2)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+14) = Real(Ye(i1,i2), dp) 
g(SumI+15) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+32) = Real(Yd(i1,i2), dp) 
g(SumI+33) = Aimag(Yd(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+50) = Real(Yu(i1,i2), dp) 
g(SumI+51) = Aimag(Yu(i1,i2)) 
End Do 
End Do 

g(68) = MHD2  
g(69) = MHU2  
Iname = Iname - 1 
 
End Subroutine ParametersToG69

Subroutine rge69(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,         & 
& Dg3,MHD2,betaMHD21,betaMHD22,DMHD2,MHU2,betaMHU21,betaMHU22,DMHU2
Complex(dp) :: lam5,betalam51,betalam52,Dlam5,lam1,betalam11,betalam12,               & 
& Dlam1,lam4,betalam41,betalam42,Dlam4,lam3,betalam31,betalam32,Dlam3,lam2,              & 
& betalam21,betalam22,Dlam2,Ye(3,3),betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3)        & 
& ,Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Yu(3,3),betaYu1(3,3)            & 
& ,betaYu2(3,3),DYu(3,3),adjYu(3,3)
Real(dp) :: Abslam5
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYdYu(3,3),adjYeYe(3,3),        & 
& adjYuYd(3,3),adjYuYu(3,3),YdadjYdYd(3,3),YdadjYdYu(3,3),YeadjYeYe(3,3),YuadjYuYd(3,3), & 
& YuadjYuYu(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYu(3,3),YdadjYdYdadjYd(3,3),& 
& YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYeadjYeYeadjYe,TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: lam1p2,lam2p2,lam3p2,lam4p2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge69' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters69(gy,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2)

Abslam5 = Conjg(lam5)*lam5
Call Adjungate(Ye,adjYe)
Call Adjungate(Yd,adjYd)
Call Adjungate(Yu,adjYu)
 YdadjYd = Matmul(Yd,adjYd) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 YeadjYe = Matmul(Ye,adjYe) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 YuadjYu = Matmul(Yu,adjYu) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdYd = Matmul(adjYd,Yd) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYdYu = Matmul(adjYd,Yu) 
 adjYeYe = Matmul(adjYe,Ye) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYuYd = Matmul(adjYu,Yd) 
 adjYuYu = Matmul(adjYu,Yu) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 YdadjYdYd = Matmul(Yd,adjYdYd) 
 YdadjYdYu = Matmul(Yd,adjYdYu) 
 YeadjYeYe = Matmul(Ye,adjYeYe) 
 YuadjYuYd = Matmul(Yu,adjYuYd) 
 YuadjYuYu = Matmul(Yu,adjYuYu) 
 adjYdYdadjYd = Matmul(adjYd,YdadjYd) 
 adjYeYeadjYe = Matmul(adjYe,YeadjYe) 
 adjYuYuadjYu = Matmul(adjYu,YuadjYu) 
 YdadjYdYdadjYd = Matmul(Yd,adjYdYdadjYd) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YeadjYeYeadjYe = Matmul(Ye,adjYeYeadjYe) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YuadjYuYuadjYu = Matmul(Yu,adjYuYuadjYu) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 TrYdadjYdYdadjYd = Real(cTrace(YdadjYdYdadjYd),dp) 
 TrYeadjYeYeadjYe = Real(cTrace(YeadjYeYeadjYe),dp) 
 TrYuadjYuYuadjYu = Real(cTrace(YuadjYuYuadjYu),dp) 
 g1p2 =g1**2 
 g1p3 =g1**3 
 g1p4 =g1**4 
 g2p2 =g2**2 
 g2p3 =g2**3 
 g2p4 =g2**4 
 g3p2 =g3**2 
 g3p3 =g3**3 
 lam1p2 =lam1**2 
 lam2p2 =lam2**2 
 lam3p2 =lam3**2 
 lam4p2 =lam4**2 


If (TwoLoopRGE) Then 
End If 
 
 
!-------------------- 
! g1 
!-------------------- 
 
betag11  = 21._dp*(g1p3)/5._dp

 
 
If (TwoLoopRGE) Then 
betag12 = 0

 
Dg1 = oo16pi2*( betag11 + oo16pi2 * betag12 ) 

 
Else 
Dg1 = oo16pi2* betag11 
End If 
 
 
!-------------------- 
! g2 
!-------------------- 
 
betag21  = -3._dp*(g2p3)

 
 
If (TwoLoopRGE) Then 
betag22 = 0

 
Dg2 = oo16pi2*( betag21 + oo16pi2 * betag22 ) 

 
Else 
Dg2 = oo16pi2* betag21 
End If 
 
 
!-------------------- 
! g3 
!-------------------- 
 
betag31  = -7._dp*(g3p3)

 
 
If (TwoLoopRGE) Then 
betag32 = 0

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 ) 

 
Else 
Dg3 = oo16pi2* betag31 
End If 
 
 
!-------------------- 
! lam5 
!-------------------- 
 
betalam51  = (-9*g1p2*lam5)/5._dp - 9*g2p2*lam5 + 2*lam1*lam5 + 2*lam2*lam5 +         & 
&  8*lam3*lam5 - 4*lam4*lam5 + 6*lam5*TrYdadjYd + 2*lam5*TrYeadjYe + 6*lam5*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betalam52 = 0

 
Dlam5 = oo16pi2*( betalam51 + oo16pi2 * betalam52 ) 

 
Else 
Dlam5 = oo16pi2* betalam51 
End If 
 
 
Call Chop(Dlam5) 

!-------------------- 
! lam1 
!-------------------- 
 
betalam11  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +         & 
&  9._dp*(g2p4)/4._dp + 12._dp*(lam1p2) + 4._dp*(lam3p2) + 2._dp*(lam4p2) -              & 
&  (9*g1p2*lam1)/5._dp - 9*g2p2*lam1 + 4*lam3*lam4 + 12*lam1*TrYdadjYd - 12._dp*(TrYdadjYdYdadjYd)& 
&  + 4*lam1*TrYeadjYe - 4._dp*(TrYeadjYeYeadjYe) + 12*lam1*TrYuadjYu - 12._dp*(TrYuadjYuYuadjYu)

 
 
If (TwoLoopRGE) Then 
betalam12 = 0

 
Dlam1 = oo16pi2*( betalam11 + oo16pi2 * betalam12 ) 

 
Else 
Dlam1 = oo16pi2* betalam11 
End If 
 
 
Call Chop(Dlam1) 

!-------------------- 
! lam4 
!-------------------- 
 
betalam41  = -8._dp*(Abslam5) - (9*g1p2*g2p2)/5._dp + 4._dp*(lam4p2) - (9*g1p2*lam4)  & 
& /5._dp - 9*g2p2*lam4 + 2*lam1*lam4 + 2*lam2*lam4 + 8*lam3*lam4 + 6*lam4*TrYdadjYd +    & 
&  2*lam4*TrYeadjYe + 6*lam4*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betalam42 = 0

 
Dlam4 = oo16pi2*( betalam41 + oo16pi2 * betalam42 ) 

 
Else 
Dlam4 = oo16pi2* betalam41 
End If 
 
 
Call Chop(Dlam4) 

!-------------------- 
! lam3 
!-------------------- 
 
betalam31  = 10._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +        & 
&  9._dp*(g2p4)/4._dp + 4._dp*(lam3p2) + 2._dp*(lam4p2) - (9*g1p2*lam3)/5._dp -          & 
&  9*g2p2*lam3 + 6*lam1*lam3 + 6*lam2*lam3 + 2*lam1*lam4 + 2*lam2*lam4 + 6*lam3*TrYdadjYd +& 
&  2*lam3*TrYeadjYe + 6*lam3*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betalam32 = 0

 
Dlam3 = oo16pi2*( betalam31 + oo16pi2 * betalam32 ) 

 
Else 
Dlam3 = oo16pi2* betalam31 
End If 
 
 
Call Chop(Dlam3) 

!-------------------- 
! lam2 
!-------------------- 
 
betalam21  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + 9._dp*(g2p4)/4._dp +           & 
&  12._dp*(lam2p2) + 4._dp*(lam3p2) + 2._dp*(lam4p2) + (9*g1p2*(g2p2 - 2._dp*(lam2)))    & 
& /10._dp - 9*g2p2*lam2 + 4*lam3*lam4

 
 
If (TwoLoopRGE) Then 
betalam22 = 0

 
Dlam2 = oo16pi2*( betalam21 + oo16pi2 * betalam22 ) 

 
Else 
Dlam2 = oo16pi2* betalam21 
End If 
 
 
Call Chop(Dlam2) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = (-9._dp*(g1p2)/4._dp - 9._dp*(g2p2)/4._dp + 3._dp*(TrYdadjYd)              & 
&  + TrYeadjYe + 3._dp*(TrYuadjYu))*Ye + 3._dp*(YeadjYeYe)/2._dp

 
 
If (TwoLoopRGE) Then 
betaYe2 = 0

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-((g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2) - 12._dp*(TrYdadjYd)               & 
&  - 4._dp*(TrYeadjYe) - 12._dp*(TrYuadjYu))*Yd) + 6*(YdadjYdYd - YuadjYuYd))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYd2 = 0

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = (-17._dp*(g1p2)/20._dp - 9._dp*(g2p2)/4._dp - 8._dp*(g3p2) +               & 
&  3._dp*(TrYdadjYd) + TrYeadjYe + 3._dp*(TrYuadjYu))*Yu - (3*(YdadjYdYu -               & 
&  YuadjYuYu))/2._dp

 
 
If (TwoLoopRGE) Then 
betaYu2 = 0

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! MHD2 
!-------------------- 
 
betaMHD21  = (-9*g1p2*MHD2)/10._dp - (9*g2p2*MHD2)/2._dp + 6*lam1*MHD2 +              & 
&  4*lam3*MHU2 + 2*lam4*MHU2 + 6*MHD2*TrYdadjYd + 2*MHD2*TrYeadjYe + 6*MHD2*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaMHD22 = 0

 
DMHD2 = oo16pi2*( betaMHD21 + oo16pi2 * betaMHD22 ) 

 
Else 
DMHD2 = oo16pi2* betaMHD21 
End If 
 
 
!-------------------- 
! MHU2 
!-------------------- 
 
betaMHU21  = 4*lam3*MHD2 + 2*lam4*MHD2 - (9*g1p2*MHU2)/10._dp - (9*g2p2*MHU2)         & 
& /2._dp + 6*lam2*MHU2

 
 
If (TwoLoopRGE) Then 
betaMHU22 = 0

 
DMHU2 = oo16pi2*( betaMHU21 + oo16pi2 * betaMHU22 ) 

 
Else 
DMHU2 = oo16pi2* betaMHU21 
End If 
 
 
Call ParametersToG69(Dg1,Dg2,Dg3,Dlam5,Dlam1,Dlam4,Dlam3,Dlam2,DYe,DYd,               & 
& DYu,DMHD2,DMHU2,f)

Iname = Iname - 1 
 
End Subroutine rge69  

Subroutine GToParameters70(g,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,              & 
& MHD2,MHU2,v)

Implicit None 
Real(dp), Intent(in) :: g(70) 
Real(dp),Intent(out) :: g1,g2,g3,MHD2,MHU2,v

Complex(dp),Intent(out) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters70' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
lam5= Cmplx(g(4),g(5),dp) 
lam1= Cmplx(g(6),g(7),dp) 
lam4= Cmplx(g(8),g(9),dp) 
lam3= Cmplx(g(10),g(11),dp) 
lam2= Cmplx(g(12),g(13),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Ye(i1,i2) = Cmplx( g(SumI+14), g(SumI+15), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yd(i1,i2) = Cmplx( g(SumI+32), g(SumI+33), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yu(i1,i2) = Cmplx( g(SumI+50), g(SumI+51), dp) 
End Do 
 End Do 
 
MHD2= g(68) 
MHU2= g(69) 
v= g(70) 
Do i1=1,70 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters70

Subroutine ParametersToG70(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,g)

Implicit None 
Real(dp), Intent(out) :: g(70) 
Real(dp), Intent(in) :: g1,g2,g3,MHD2,MHU2,v

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG70' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
g(4) = Real(lam5,dp)  
g(5) = Aimag(lam5)  
g(6) = Real(lam1,dp)  
g(7) = Aimag(lam1)  
g(8) = Real(lam4,dp)  
g(9) = Aimag(lam4)  
g(10) = Real(lam3,dp)  
g(11) = Aimag(lam3)  
g(12) = Real(lam2,dp)  
g(13) = Aimag(lam2)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+14) = Real(Ye(i1,i2), dp) 
g(SumI+15) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+32) = Real(Yd(i1,i2), dp) 
g(SumI+33) = Aimag(Yd(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+50) = Real(Yu(i1,i2), dp) 
g(SumI+51) = Aimag(Yu(i1,i2)) 
End Do 
End Do 

g(68) = MHD2  
g(69) = MHU2  
g(70) = v  
Iname = Iname - 1 
 
End Subroutine ParametersToG70

Subroutine rge70(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,         & 
& Dg3,MHD2,betaMHD21,betaMHD22,DMHD2,MHU2,betaMHU21,betaMHU22,DMHU2,v,betav1,betav2,Dv
Complex(dp) :: lam5,betalam51,betalam52,Dlam5,lam1,betalam11,betalam12,               & 
& Dlam1,lam4,betalam41,betalam42,Dlam4,lam3,betalam31,betalam32,Dlam3,lam2,              & 
& betalam21,betalam22,Dlam2,Ye(3,3),betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3)        & 
& ,Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Yu(3,3),betaYu1(3,3)            & 
& ,betaYu2(3,3),DYu(3,3),adjYu(3,3)
Real(dp) :: Abslam5
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYdYu(3,3),adjYeYe(3,3),        & 
& adjYuYd(3,3),adjYuYu(3,3),YdadjYdYd(3,3),YdadjYdYu(3,3),YeadjYeYe(3,3),YuadjYuYd(3,3), & 
& YuadjYuYu(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYu(3,3),YdadjYdYdadjYd(3,3),& 
& YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYeadjYeYeadjYe,TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: lam1p2,lam2p2,lam3p2,lam4p2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge70' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters70(gy,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v)

Abslam5 = Conjg(lam5)*lam5
Call Adjungate(Ye,adjYe)
Call Adjungate(Yd,adjYd)
Call Adjungate(Yu,adjYu)
 YdadjYd = Matmul(Yd,adjYd) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 YeadjYe = Matmul(Ye,adjYe) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 YuadjYu = Matmul(Yu,adjYu) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdYd = Matmul(adjYd,Yd) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYdYu = Matmul(adjYd,Yu) 
 adjYeYe = Matmul(adjYe,Ye) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYuYd = Matmul(adjYu,Yd) 
 adjYuYu = Matmul(adjYu,Yu) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 YdadjYdYd = Matmul(Yd,adjYdYd) 
 YdadjYdYu = Matmul(Yd,adjYdYu) 
 YeadjYeYe = Matmul(Ye,adjYeYe) 
 YuadjYuYd = Matmul(Yu,adjYuYd) 
 YuadjYuYu = Matmul(Yu,adjYuYu) 
 adjYdYdadjYd = Matmul(adjYd,YdadjYd) 
 adjYeYeadjYe = Matmul(adjYe,YeadjYe) 
 adjYuYuadjYu = Matmul(adjYu,YuadjYu) 
 YdadjYdYdadjYd = Matmul(Yd,adjYdYdadjYd) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YeadjYeYeadjYe = Matmul(Ye,adjYeYeadjYe) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YuadjYuYuadjYu = Matmul(Yu,adjYuYuadjYu) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 TrYdadjYdYdadjYd = Real(cTrace(YdadjYdYdadjYd),dp) 
 TrYeadjYeYeadjYe = Real(cTrace(YeadjYeYeadjYe),dp) 
 TrYuadjYuYuadjYu = Real(cTrace(YuadjYuYuadjYu),dp) 
 g1p2 =g1**2 
 g1p3 =g1**3 
 g1p4 =g1**4 
 g2p2 =g2**2 
 g2p3 =g2**3 
 g2p4 =g2**4 
 g3p2 =g3**2 
 g3p3 =g3**3 
 lam1p2 =lam1**2 
 lam2p2 =lam2**2 
 lam3p2 =lam3**2 
 lam4p2 =lam4**2 


If (TwoLoopRGE) Then 
End If 
 
 
!-------------------- 
! g1 
!-------------------- 
 
betag11  = 21._dp*(g1p3)/5._dp

 
 
If (TwoLoopRGE) Then 
betag12 = 0

 
Dg1 = oo16pi2*( betag11 + oo16pi2 * betag12 ) 

 
Else 
Dg1 = oo16pi2* betag11 
End If 
 
 
!-------------------- 
! g2 
!-------------------- 
 
betag21  = -3._dp*(g2p3)

 
 
If (TwoLoopRGE) Then 
betag22 = 0

 
Dg2 = oo16pi2*( betag21 + oo16pi2 * betag22 ) 

 
Else 
Dg2 = oo16pi2* betag21 
End If 
 
 
!-------------------- 
! g3 
!-------------------- 
 
betag31  = -7._dp*(g3p3)

 
 
If (TwoLoopRGE) Then 
betag32 = 0

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 ) 

 
Else 
Dg3 = oo16pi2* betag31 
End If 
 
 
!-------------------- 
! lam5 
!-------------------- 
 
betalam51  = (-9*g1p2*lam5)/5._dp - 9*g2p2*lam5 + 2*lam1*lam5 + 2*lam2*lam5 +         & 
&  8*lam3*lam5 - 4*lam4*lam5 + 6*lam5*TrYdadjYd + 2*lam5*TrYeadjYe + 6*lam5*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betalam52 = 0

 
Dlam5 = oo16pi2*( betalam51 + oo16pi2 * betalam52 ) 

 
Else 
Dlam5 = oo16pi2* betalam51 
End If 
 
 
Call Chop(Dlam5) 

!-------------------- 
! lam1 
!-------------------- 
 
betalam11  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +         & 
&  9._dp*(g2p4)/4._dp + 12._dp*(lam1p2) + 4._dp*(lam3p2) + 2._dp*(lam4p2) -              & 
&  (9*g1p2*lam1)/5._dp - 9*g2p2*lam1 + 4*lam3*lam4 + 12*lam1*TrYdadjYd - 12._dp*(TrYdadjYdYdadjYd)& 
&  + 4*lam1*TrYeadjYe - 4._dp*(TrYeadjYeYeadjYe) + 12*lam1*TrYuadjYu - 12._dp*(TrYuadjYuYuadjYu)

 
 
If (TwoLoopRGE) Then 
betalam12 = 0

 
Dlam1 = oo16pi2*( betalam11 + oo16pi2 * betalam12 ) 

 
Else 
Dlam1 = oo16pi2* betalam11 
End If 
 
 
Call Chop(Dlam1) 

!-------------------- 
! lam4 
!-------------------- 
 
betalam41  = -8._dp*(Abslam5) - (9*g1p2*g2p2)/5._dp + 4._dp*(lam4p2) - (9*g1p2*lam4)  & 
& /5._dp - 9*g2p2*lam4 + 2*lam1*lam4 + 2*lam2*lam4 + 8*lam3*lam4 + 6*lam4*TrYdadjYd +    & 
&  2*lam4*TrYeadjYe + 6*lam4*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betalam42 = 0

 
Dlam4 = oo16pi2*( betalam41 + oo16pi2 * betalam42 ) 

 
Else 
Dlam4 = oo16pi2* betalam41 
End If 
 
 
Call Chop(Dlam4) 

!-------------------- 
! lam3 
!-------------------- 
 
betalam31  = 10._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +        & 
&  9._dp*(g2p4)/4._dp + 4._dp*(lam3p2) + 2._dp*(lam4p2) - (9*g1p2*lam3)/5._dp -          & 
&  9*g2p2*lam3 + 6*lam1*lam3 + 6*lam2*lam3 + 2*lam1*lam4 + 2*lam2*lam4 + 6*lam3*TrYdadjYd +& 
&  2*lam3*TrYeadjYe + 6*lam3*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betalam32 = 0

 
Dlam3 = oo16pi2*( betalam31 + oo16pi2 * betalam32 ) 

 
Else 
Dlam3 = oo16pi2* betalam31 
End If 
 
 
Call Chop(Dlam3) 

!-------------------- 
! lam2 
!-------------------- 
 
betalam21  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + 9._dp*(g2p4)/4._dp +           & 
&  12._dp*(lam2p2) + 4._dp*(lam3p2) + 2._dp*(lam4p2) + (9*g1p2*(g2p2 - 2._dp*(lam2)))    & 
& /10._dp - 9*g2p2*lam2 + 4*lam3*lam4

 
 
If (TwoLoopRGE) Then 
betalam22 = 0

 
Dlam2 = oo16pi2*( betalam21 + oo16pi2 * betalam22 ) 

 
Else 
Dlam2 = oo16pi2* betalam21 
End If 
 
 
Call Chop(Dlam2) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = (-9._dp*(g1p2)/4._dp - 9._dp*(g2p2)/4._dp + 3._dp*(TrYdadjYd)              & 
&  + TrYeadjYe + 3._dp*(TrYuadjYu))*Ye + 3._dp*(YeadjYeYe)/2._dp

 
 
If (TwoLoopRGE) Then 
betaYe2 = 0

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-((g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2) - 12._dp*(TrYdadjYd)               & 
&  - 4._dp*(TrYeadjYe) - 12._dp*(TrYuadjYu))*Yd) + 6*(YdadjYdYd - YuadjYuYd))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYd2 = 0

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = (-17._dp*(g1p2)/20._dp - 9._dp*(g2p2)/4._dp - 8._dp*(g3p2) +               & 
&  3._dp*(TrYdadjYd) + TrYeadjYe + 3._dp*(TrYuadjYu))*Yu - (3*(YdadjYdYu -               & 
&  YuadjYuYu))/2._dp

 
 
If (TwoLoopRGE) Then 
betaYu2 = 0

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! MHD2 
!-------------------- 
 
betaMHD21  = (-9*g1p2*MHD2)/10._dp - (9*g2p2*MHD2)/2._dp + 6*lam1*MHD2 +              & 
&  4*lam3*MHU2 + 2*lam4*MHU2 + 6*MHD2*TrYdadjYd + 2*MHD2*TrYeadjYe + 6*MHD2*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaMHD22 = 0

 
DMHD2 = oo16pi2*( betaMHD21 + oo16pi2 * betaMHD22 ) 

 
Else 
DMHD2 = oo16pi2* betaMHD21 
End If 
 
 
!-------------------- 
! MHU2 
!-------------------- 
 
betaMHU21  = 4*lam3*MHD2 + 2*lam4*MHD2 - (9*g1p2*MHU2)/10._dp - (9*g2p2*MHU2)         & 
& /2._dp + 6*lam2*MHU2

 
 
If (TwoLoopRGE) Then 
betaMHU22 = 0

 
DMHU2 = oo16pi2*( betaMHU21 + oo16pi2 * betaMHU22 ) 

 
Else 
DMHU2 = oo16pi2* betaMHU21 
End If 
 
 
!-------------------- 
! v 
!-------------------- 
 
betav1  = (v*(9._dp*(g1p2) + 45._dp*(g2p2) - 60._dp*(TrYdadjYd) - 20._dp*(TrYeadjYe)  & 
&  - 60._dp*(TrYuadjYu) + 3*g1p2*Xi + 15*g2p2*Xi))/20._dp

 
 
If (TwoLoopRGE) Then 
betav2 = 0

 
Dv = oo16pi2*( betav1 + oo16pi2 * betav2 ) 

 
Else 
Dv = oo16pi2* betav1 
End If 
 
 
Call ParametersToG70(Dg1,Dg2,Dg3,Dlam5,Dlam1,Dlam4,Dlam3,Dlam2,DYe,DYd,               & 
& DYu,DMHD2,DMHU2,Dv,f)

Iname = Iname - 1 
 
End Subroutine rge70  

End Module RGEs_Inert2 
 
