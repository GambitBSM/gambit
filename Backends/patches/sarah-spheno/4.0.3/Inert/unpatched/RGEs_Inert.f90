! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:31 on 18.2.2026   
! ----------------------------------------------------------------------  
 
 
Module RGEs_Inert 
 
Use Control 
Use Settings 
Use Model_Data_Inert 
Use Mathematics 
 
Logical,Private,Save::OnlyDiagonal

Real(dp),Parameter::id3R(3,3)=& 
   & Reshape(Source=(/& 
   & 1,0,0,& 
 &0,1,0,& 
 &0,0,1& 
 &/),shape=(/3,3/)) 
Contains 


Subroutine GToParameters69(g,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,              & 
& mHd2,mHu2)

Implicit None 
Real(dp), Intent(in) :: g(69) 
Real(dp),Intent(out) :: g1,g2,g3,mHd2,mHu2

Complex(dp),Intent(out) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters69' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
Lam5= Cmplx(g(4),g(5),dp) 
Lam1= Cmplx(g(6),g(7),dp) 
Lam4= Cmplx(g(8),g(9),dp) 
Lam3= Cmplx(g(10),g(11),dp) 
Lam2= Cmplx(g(12),g(13),dp) 
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
 
mHd2= g(68) 
mHu2= g(69) 
Do i1=1,69 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters69

Subroutine ParametersToG69(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,g)

Implicit None 
Real(dp), Intent(out) :: g(69) 
Real(dp), Intent(in) :: g1,g2,g3,mHd2,mHu2

Complex(dp), Intent(in) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG69' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
g(4) = Real(Lam5,dp)  
g(5) = Aimag(Lam5)  
g(6) = Real(Lam1,dp)  
g(7) = Aimag(Lam1)  
g(8) = Real(Lam4,dp)  
g(9) = Aimag(Lam4)  
g(10) = Real(Lam3,dp)  
g(11) = Aimag(Lam3)  
g(12) = Real(Lam2,dp)  
g(13) = Aimag(Lam2)  
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

g(68) = mHd2  
g(69) = mHu2  
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
& Dg3,mHd2,betamHd21,betamHd22,DmHd2,mHu2,betamHu21,betamHu22,DmHu2
Complex(dp) :: Lam5,betaLam51,betaLam52,DLam5,Lam1,betaLam11,betaLam12,               & 
& DLam1,Lam4,betaLam41,betaLam42,DLam4,Lam3,betaLam31,betaLam32,DLam3,Lam2,              & 
& betaLam21,betaLam22,DLam2,Ye(3,3),betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3)        & 
& ,Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Yu(3,3),betaYu1(3,3)            & 
& ,betaYu2(3,3),DYu(3,3),adjYu(3,3)
Real(dp) :: AbsLam5
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYdYu(3,3),adjYeYe(3,3),        & 
& adjYuYd(3,3),adjYuYu(3,3),YdadjYdYd(3,3),YdadjYdYu(3,3),YeadjYeYe(3,3),YuadjYuYd(3,3), & 
& YuadjYuYu(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYu(3,3),YdadjYdYdadjYd(3,3),& 
& YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYeadjYeYeadjYe,TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: Lam1p2,Lam2p2,Lam3p2,Lam4p2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge69' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters69(gy,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2)

AbsLam5 = Conjg(Lam5)*Lam5
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
 Lam1p2 =Lam1**2 
 Lam2p2 =Lam2**2 
 Lam3p2 =Lam3**2 
 Lam4p2 =Lam4**2 


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
! Lam5 
!-------------------- 
 
betaLam51  = (-9*g1p2*Lam5)/5._dp - 9*g2p2*Lam5 + 4*Lam1*Lam5 + 4*Lam2*Lam5 +         & 
&  8*Lam3*Lam5 - 4*Lam4*Lam5 + 6*Lam5*TrYdadjYd + 2*Lam5*TrYeadjYe + 6*Lam5*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaLam52 = 0

 
DLam5 = oo16pi2*( betaLam51 + oo16pi2 * betaLam52 ) 

 
Else 
DLam5 = oo16pi2* betaLam51 
End If 
 
 
Call Chop(DLam5) 

!-------------------- 
! Lam1 
!-------------------- 
 
betaLam11  = AbsLam5 + 27._dp*(g1p4)/200._dp + (9*g1p2*g2p2)/20._dp + 9._dp*(g2p4)    & 
& /8._dp + 24._dp*(Lam1p2) + 2._dp*(Lam3p2) + Lam4p2 - (9*g1p2*Lam1)/5._dp -             & 
&  9*g2p2*Lam1 + 2*Lam3*Lam4 + 12*Lam1*TrYdadjYd - 6._dp*(TrYdadjYdYdadjYd)              & 
&  + 4*Lam1*TrYeadjYe - 2._dp*(TrYeadjYeYeadjYe) + 12*Lam1*TrYuadjYu - 6._dp*(TrYuadjYuYuadjYu)

 
 
If (TwoLoopRGE) Then 
betaLam12 = 0

 
DLam1 = oo16pi2*( betaLam11 + oo16pi2 * betaLam12 ) 

 
Else 
DLam1 = oo16pi2* betaLam11 
End If 
 
 
Call Chop(DLam1) 

!-------------------- 
! Lam4 
!-------------------- 
 
betaLam41  = -8._dp*(AbsLam5) - (9*g1p2*g2p2)/5._dp + 4._dp*(Lam4p2) - (9*g1p2*Lam4)  & 
& /5._dp - 9*g2p2*Lam4 + 4*Lam1*Lam4 + 4*Lam2*Lam4 + 8*Lam3*Lam4 + 6*Lam4*TrYdadjYd +    & 
&  2*Lam4*TrYeadjYe + 6*Lam4*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaLam42 = 0

 
DLam4 = oo16pi2*( betaLam41 + oo16pi2 * betaLam42 ) 

 
Else 
DLam4 = oo16pi2* betaLam41 
End If 
 
 
Call Chop(DLam4) 

!-------------------- 
! Lam3 
!-------------------- 
 
betaLam31  = 10._dp*(AbsLam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +        & 
&  9._dp*(g2p4)/4._dp + 4._dp*(Lam3p2) + 2._dp*(Lam4p2) - (9*g1p2*Lam3)/5._dp -          & 
&  9*g2p2*Lam3 + 12*Lam1*Lam3 + 12*Lam2*Lam3 + 4*Lam1*Lam4 + 4*Lam2*Lam4 +               & 
&  6*Lam3*TrYdadjYd + 2*Lam3*TrYeadjYe + 6*Lam3*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaLam32 = 0

 
DLam3 = oo16pi2*( betaLam31 + oo16pi2 * betaLam32 ) 

 
Else 
DLam3 = oo16pi2* betaLam31 
End If 
 
 
Call Chop(DLam3) 

!-------------------- 
! Lam2 
!-------------------- 
 
betaLam21  = AbsLam5 + 27._dp*(g1p4)/200._dp + 9._dp*(g2p4)/8._dp + 24._dp*(Lam2p2)   & 
&  + 2._dp*(Lam3p2) + Lam4p2 + (9*g1p2*(g2p2 - 4._dp*(Lam2)))/20._dp - 9*g2p2*Lam2 +     & 
&  2*Lam3*Lam4

 
 
If (TwoLoopRGE) Then 
betaLam22 = 0

 
DLam2 = oo16pi2*( betaLam21 + oo16pi2 * betaLam22 ) 

 
Else 
DLam2 = oo16pi2* betaLam21 
End If 
 
 
Call Chop(DLam2) 

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
! mHd2 
!-------------------- 
 
betamHd21  = (-9*g1p2*mHd2)/10._dp - (9*g2p2*mHd2)/2._dp + 12*Lam1*mHd2 +             & 
&  4*Lam3*mHu2 + 2*Lam4*mHu2 + 6*mHd2*TrYdadjYd + 2*mHd2*TrYeadjYe + 6*mHd2*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betamHd22 = 0

 
DmHd2 = oo16pi2*( betamHd21 + oo16pi2 * betamHd22 ) 

 
Else 
DmHd2 = oo16pi2* betamHd21 
End If 
 
 
!-------------------- 
! mHu2 
!-------------------- 
 
betamHu21  = 4*Lam3*mHd2 + 2*Lam4*mHd2 - (3*(3._dp*(g1p2) + 15._dp*(g2p2)             & 
&  - 40._dp*(Lam2))*mHu2)/10._dp

 
 
If (TwoLoopRGE) Then 
betamHu22 = 0

 
DmHu2 = oo16pi2*( betamHu21 + oo16pi2 * betamHu22 ) 

 
Else 
DmHu2 = oo16pi2* betamHu21 
End If 
 
 
Call ParametersToG69(Dg1,Dg2,Dg3,DLam5,DLam1,DLam4,DLam3,DLam2,DYe,DYd,               & 
& DYu,DmHd2,DmHu2,f)

Iname = Iname - 1 
 
End Subroutine rge69  

Subroutine GToParameters70(g,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,              & 
& mHd2,mHu2,v)

Implicit None 
Real(dp), Intent(in) :: g(70) 
Real(dp),Intent(out) :: g1,g2,g3,mHd2,mHu2,v

Complex(dp),Intent(out) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters70' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
Lam5= Cmplx(g(4),g(5),dp) 
Lam1= Cmplx(g(6),g(7),dp) 
Lam4= Cmplx(g(8),g(9),dp) 
Lam3= Cmplx(g(10),g(11),dp) 
Lam2= Cmplx(g(12),g(13),dp) 
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
 
mHd2= g(68) 
mHu2= g(69) 
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

Subroutine ParametersToG70(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,v,g)

Implicit None 
Real(dp), Intent(out) :: g(70) 
Real(dp), Intent(in) :: g1,g2,g3,mHd2,mHu2,v

Complex(dp), Intent(in) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG70' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
g(4) = Real(Lam5,dp)  
g(5) = Aimag(Lam5)  
g(6) = Real(Lam1,dp)  
g(7) = Aimag(Lam1)  
g(8) = Real(Lam4,dp)  
g(9) = Aimag(Lam4)  
g(10) = Real(Lam3,dp)  
g(11) = Aimag(Lam3)  
g(12) = Real(Lam2,dp)  
g(13) = Aimag(Lam2)  
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

g(68) = mHd2  
g(69) = mHu2  
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
& Dg3,mHd2,betamHd21,betamHd22,DmHd2,mHu2,betamHu21,betamHu22,DmHu2,v,betav1,betav2,Dv
Complex(dp) :: Lam5,betaLam51,betaLam52,DLam5,Lam1,betaLam11,betaLam12,               & 
& DLam1,Lam4,betaLam41,betaLam42,DLam4,Lam3,betaLam31,betaLam32,DLam3,Lam2,              & 
& betaLam21,betaLam22,DLam2,Ye(3,3),betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3)        & 
& ,Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Yu(3,3),betaYu1(3,3)            & 
& ,betaYu2(3,3),DYu(3,3),adjYu(3,3)
Real(dp) :: AbsLam5
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYdYu(3,3),adjYeYe(3,3),        & 
& adjYuYd(3,3),adjYuYu(3,3),YdadjYdYd(3,3),YdadjYdYu(3,3),YeadjYeYe(3,3),YuadjYuYd(3,3), & 
& YuadjYuYu(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYu(3,3),YdadjYdYdadjYd(3,3),& 
& YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYeadjYeYeadjYe,TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: Lam1p2,Lam2p2,Lam3p2,Lam4p2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge70' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters70(gy,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,v)

AbsLam5 = Conjg(Lam5)*Lam5
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
 Lam1p2 =Lam1**2 
 Lam2p2 =Lam2**2 
 Lam3p2 =Lam3**2 
 Lam4p2 =Lam4**2 


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
! Lam5 
!-------------------- 
 
betaLam51  = (-9*g1p2*Lam5)/5._dp - 9*g2p2*Lam5 + 4*Lam1*Lam5 + 4*Lam2*Lam5 +         & 
&  8*Lam3*Lam5 - 4*Lam4*Lam5 + 6*Lam5*TrYdadjYd + 2*Lam5*TrYeadjYe + 6*Lam5*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaLam52 = 0

 
DLam5 = oo16pi2*( betaLam51 + oo16pi2 * betaLam52 ) 

 
Else 
DLam5 = oo16pi2* betaLam51 
End If 
 
 
Call Chop(DLam5) 

!-------------------- 
! Lam1 
!-------------------- 
 
betaLam11  = AbsLam5 + 27._dp*(g1p4)/200._dp + (9*g1p2*g2p2)/20._dp + 9._dp*(g2p4)    & 
& /8._dp + 24._dp*(Lam1p2) + 2._dp*(Lam3p2) + Lam4p2 - (9*g1p2*Lam1)/5._dp -             & 
&  9*g2p2*Lam1 + 2*Lam3*Lam4 + 12*Lam1*TrYdadjYd - 6._dp*(TrYdadjYdYdadjYd)              & 
&  + 4*Lam1*TrYeadjYe - 2._dp*(TrYeadjYeYeadjYe) + 12*Lam1*TrYuadjYu - 6._dp*(TrYuadjYuYuadjYu)

 
 
If (TwoLoopRGE) Then 
betaLam12 = 0

 
DLam1 = oo16pi2*( betaLam11 + oo16pi2 * betaLam12 ) 

 
Else 
DLam1 = oo16pi2* betaLam11 
End If 
 
 
Call Chop(DLam1) 

!-------------------- 
! Lam4 
!-------------------- 
 
betaLam41  = -8._dp*(AbsLam5) - (9*g1p2*g2p2)/5._dp + 4._dp*(Lam4p2) - (9*g1p2*Lam4)  & 
& /5._dp - 9*g2p2*Lam4 + 4*Lam1*Lam4 + 4*Lam2*Lam4 + 8*Lam3*Lam4 + 6*Lam4*TrYdadjYd +    & 
&  2*Lam4*TrYeadjYe + 6*Lam4*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaLam42 = 0

 
DLam4 = oo16pi2*( betaLam41 + oo16pi2 * betaLam42 ) 

 
Else 
DLam4 = oo16pi2* betaLam41 
End If 
 
 
Call Chop(DLam4) 

!-------------------- 
! Lam3 
!-------------------- 
 
betaLam31  = 10._dp*(AbsLam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +        & 
&  9._dp*(g2p4)/4._dp + 4._dp*(Lam3p2) + 2._dp*(Lam4p2) - (9*g1p2*Lam3)/5._dp -          & 
&  9*g2p2*Lam3 + 12*Lam1*Lam3 + 12*Lam2*Lam3 + 4*Lam1*Lam4 + 4*Lam2*Lam4 +               & 
&  6*Lam3*TrYdadjYd + 2*Lam3*TrYeadjYe + 6*Lam3*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betaLam32 = 0

 
DLam3 = oo16pi2*( betaLam31 + oo16pi2 * betaLam32 ) 

 
Else 
DLam3 = oo16pi2* betaLam31 
End If 
 
 
Call Chop(DLam3) 

!-------------------- 
! Lam2 
!-------------------- 
 
betaLam21  = AbsLam5 + 27._dp*(g1p4)/200._dp + 9._dp*(g2p4)/8._dp + 24._dp*(Lam2p2)   & 
&  + 2._dp*(Lam3p2) + Lam4p2 + (9*g1p2*(g2p2 - 4._dp*(Lam2)))/20._dp - 9*g2p2*Lam2 +     & 
&  2*Lam3*Lam4

 
 
If (TwoLoopRGE) Then 
betaLam22 = 0

 
DLam2 = oo16pi2*( betaLam21 + oo16pi2 * betaLam22 ) 

 
Else 
DLam2 = oo16pi2* betaLam21 
End If 
 
 
Call Chop(DLam2) 

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
! mHd2 
!-------------------- 
 
betamHd21  = (-9*g1p2*mHd2)/10._dp - (9*g2p2*mHd2)/2._dp + 12*Lam1*mHd2 +             & 
&  4*Lam3*mHu2 + 2*Lam4*mHu2 + 6*mHd2*TrYdadjYd + 2*mHd2*TrYeadjYe + 6*mHd2*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betamHd22 = 0

 
DmHd2 = oo16pi2*( betamHd21 + oo16pi2 * betamHd22 ) 

 
Else 
DmHd2 = oo16pi2* betamHd21 
End If 
 
 
!-------------------- 
! mHu2 
!-------------------- 
 
betamHu21  = 4*Lam3*mHd2 + 2*Lam4*mHd2 - (3*(3._dp*(g1p2) + 15._dp*(g2p2)             & 
&  - 40._dp*(Lam2))*mHu2)/10._dp

 
 
If (TwoLoopRGE) Then 
betamHu22 = 0

 
DmHu2 = oo16pi2*( betamHu21 + oo16pi2 * betamHu22 ) 

 
Else 
DmHu2 = oo16pi2* betamHu21 
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
 
 
Call ParametersToG70(Dg1,Dg2,Dg3,DLam5,DLam1,DLam4,DLam3,DLam2,DYe,DYd,               & 
& DYu,DmHd2,DmHu2,Dv,f)

Iname = Iname - 1 
 
End Subroutine rge70  

End Module RGEs_Inert 
 
