! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:22 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module RGEs_gumTHDMII 
 
Use Control 
Use Settings 
Use Model_Data_gumTHDMII 
Use Mathematics 
 
Logical,Private,Save::OnlyDiagonal

Real(dp),Parameter::id3R(3,3)=& 
   & Reshape(Source=(/& 
   & 1,0,0,& 
 &0,1,0,& 
 &0,0,1& 
 &/),shape=(/3,3/)) 
Contains 


Subroutine GToParameters73(g,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,              & 
& m122,m112,m222)

Implicit None 
Real(dp), Intent(in) :: g(73) 
Real(dp),Intent(out) :: g1,g2,g3

Complex(dp),Intent(out) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters73' 
 
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
Yu(i1,i2) = Cmplx( g(SumI+14), g(SumI+15), dp) 
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
Ye(i1,i2) = Cmplx( g(SumI+50), g(SumI+51), dp) 
End Do 
 End Do 
 
m122= Cmplx(g(68),g(69),dp) 
m112= Cmplx(g(70),g(71),dp) 
m222= Cmplx(g(72),g(73),dp) 
Do i1=1,73 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters73

Subroutine ParametersToG73(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,           & 
& m112,m222,g)

Implicit None 
Real(dp), Intent(out) :: g(73) 
Real(dp), Intent(in) :: g1,g2,g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG73' 
 
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
g(SumI+14) = Real(Yu(i1,i2), dp) 
g(SumI+15) = Aimag(Yu(i1,i2)) 
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
g(SumI+50) = Real(Ye(i1,i2), dp) 
g(SumI+51) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

g(68) = Real(m122,dp)  
g(69) = Aimag(m122)  
g(70) = Real(m112,dp)  
g(71) = Aimag(m112)  
g(72) = Real(m222,dp)  
g(73) = Aimag(m222)  
Iname = Iname - 1 
 
End Subroutine ParametersToG73

Subroutine rge73(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,Dg3
Complex(dp) :: lam5,betalam51,betalam52,Dlam5,lam1,betalam11,betalam12,               & 
& Dlam1,lam4,betalam41,betalam42,Dlam4,lam3,betalam31,betalam32,Dlam3,lam2,              & 
& betalam21,betalam22,Dlam2,Yu(3,3),betaYu1(3,3),betaYu2(3,3),DYu(3,3),adjYu(3,3)        & 
& ,Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Ye(3,3),betaYe1(3,3)            & 
& ,betaYe2(3,3),DYe(3,3),adjYe(3,3),m122,betam1221,betam1222,Dm122,m112,betam1121,       & 
& betam1122,Dm112,m222,betam2221,betam2222,Dm222
Real(dp) :: Abslam5
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYd(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYeYe(3,3),        & 
& adjYuYu(3,3),YdadjYdYd(3,3),YdadjYuYu(3,3),YeadjYeYe(3,3),YuadjYdYd(3,3),              & 
& YuadjYuYu(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYd(3,3),adjYuYuadjYu(3,3),& 
& YdadjYdYdadjYd(3,3),YdadjYuYuadjYd(3,3),YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYdadjYuYuadjYd,TrYeadjYeYeadjYe,     & 
& TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: lam1p2,lam2p2,lam3p2,lam4p2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge73' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters73(gy,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,              & 
& m112,m222)

Abslam5 = Conjg(lam5)*lam5
Call Adjungate(Yu,adjYu)
Call Adjungate(Yd,adjYd)
Call Adjungate(Ye,adjYe)
 YdadjYd = Matmul(Yd,adjYd) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 YeadjYe = Matmul(Ye,adjYe) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 YuadjYd = Matmul(Yu,adjYd) 
 YuadjYu = Matmul(Yu,adjYu) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdYd = Matmul(adjYd,Yd) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYeYe = Matmul(adjYe,Ye) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYuYu = Matmul(adjYu,Yu) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 YdadjYdYd = Matmul(Yd,adjYdYd) 
 YdadjYuYu = Matmul(Yd,adjYuYu) 
 YeadjYeYe = Matmul(Ye,adjYeYe) 
 YuadjYdYd = Matmul(Yu,adjYdYd) 
 YuadjYuYu = Matmul(Yu,adjYuYu) 
 adjYdYdadjYd = Matmul(adjYd,YdadjYd) 
 adjYeYeadjYe = Matmul(adjYe,YeadjYe) 
 adjYuYuadjYd = Matmul(adjYu,YuadjYd) 
 adjYuYuadjYu = Matmul(adjYu,YuadjYu) 
 YdadjYdYdadjYd = Matmul(Yd,adjYdYdadjYd) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YdadjYuYuadjYd = Matmul(Yd,adjYuYuadjYd) 
Forall(i2=1:3)  YdadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYd(i2,i2),dp) 
 YeadjYeYeadjYe = Matmul(Ye,adjYeYeadjYe) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YuadjYuYuadjYu = Matmul(Yu,adjYuYuadjYu) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 TrYdadjYdYdadjYd = Real(cTrace(YdadjYdYdadjYd),dp) 
 TrYdadjYuYuadjYd = Real(cTrace(YdadjYuYuadjYd),dp) 
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
&  8*lam3*lam5 + 12*lam4*lam5 + 6*lam5*TrYdadjYd + 2*lam5*TrYeadjYe + 6*lam5*TrYuadjYu

 
 
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
&  + 4*lam1*TrYeadjYe - 4._dp*(TrYeadjYeYeadjYe)

 
 
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
 
betalam41  = 8._dp*(Abslam5) + (9*g1p2*g2p2)/5._dp + 4._dp*(lam4p2) - (9*g1p2*lam4)   & 
& /5._dp - 9*g2p2*lam4 + 2*lam1*lam4 + 2*lam2*lam4 + 8*lam3*lam4 + 6*lam4*TrYdadjYd +    & 
&  12._dp*(TrYdadjYuYuadjYd) + 2*lam4*TrYeadjYe + 6*lam4*TrYuadjYu

 
 
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
 
betalam31  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp - (9*g1p2*g2p2)/10._dp +         & 
&  9._dp*(g2p4)/4._dp + 4._dp*(lam3p2) + 2._dp*(lam4p2) - (9*g1p2*lam3)/5._dp -          & 
&  9*g2p2*lam3 + 6*lam1*lam3 + 6*lam2*lam3 + 2*lam1*lam4 + 2*lam2*lam4 + 6*lam3*TrYdadjYd -& 
&  12._dp*(TrYdadjYuYuadjYd) + 2*lam3*TrYeadjYe + 6*lam3*TrYuadjYu

 
 
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
 
betalam21  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +         & 
&  9._dp*(g2p4)/4._dp + 12._dp*(lam2p2) + 4._dp*(lam3p2) + 2._dp*(lam4p2) -              & 
&  (9*g1p2*lam2)/5._dp - 9*g2p2*lam2 + 4*lam3*lam4 + 12*lam2*TrYuadjYu - 12._dp*(TrYuadjYuYuadjYu)

 
 
If (TwoLoopRGE) Then 
betalam22 = 0

 
Dlam2 = oo16pi2*( betalam21 + oo16pi2 * betalam22 ) 

 
Else 
Dlam2 = oo16pi2* betalam21 
End If 
 
 
Call Chop(Dlam2) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = (-17._dp*(g1p2)/20._dp - 9._dp*(g2p2)/4._dp - 8._dp*(g3p2) +               & 
&  3._dp*(TrYuadjYu))*Yu + (YuadjYdYd + 3._dp*(YuadjYuYu))/2._dp

 
 
If (TwoLoopRGE) Then 
betaYu2 = 0

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-((g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2) - 12._dp*(TrYdadjYd)               & 
&  - 4._dp*(TrYeadjYe))*Yd) + 2*(3._dp*(YdadjYdYd) + YdadjYuYu))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYd2 = 0

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = ((-9*(g1p2 + g2p2) + 12._dp*(TrYdadjYd) + 4._dp*(TrYeadjYe))               & 
& *Ye + 6._dp*(YeadjYeYe))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYe2 = 0

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! m122 
!-------------------- 
 
betam1221  = (-9*g1p2*m122)/10._dp - (9*g2p2*m122)/2._dp + 2*lam3*m122 +              & 
&  4*lam4*m122 + 3*m122*TrYdadjYd + m122*TrYeadjYe + 3*m122*TrYuadjYu + 6*Conjg(lam5)    & 
& *Conjg(m122)

 
 
If (TwoLoopRGE) Then 
betam1222 = 0

 
Dm122 = oo16pi2*( betam1221 + oo16pi2 * betam1222 ) 

 
Else 
Dm122 = oo16pi2* betam1221 
End If 
 
 
Call Chop(Dm122) 

!-------------------- 
! m112 
!-------------------- 
 
betam1121  = (-9*g1p2*m112)/10._dp - (9*g2p2*m112)/2._dp + 6*lam1*m112 +              & 
&  4*lam3*m222 + 2*lam4*m222 + 6*m112*TrYdadjYd + 2*m112*TrYeadjYe

 
 
If (TwoLoopRGE) Then 
betam1122 = 0

 
Dm112 = oo16pi2*( betam1121 + oo16pi2 * betam1122 ) 

 
Else 
Dm112 = oo16pi2* betam1121 
End If 
 
 
Call Chop(Dm112) 

!-------------------- 
! m222 
!-------------------- 
 
betam2221  = 4*lam3*m112 + 2*lam4*m112 - (9*g1p2*m222)/10._dp - (9*g2p2*m222)         & 
& /2._dp + 6*lam2*m222 + 6*m222*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betam2222 = 0

 
Dm222 = oo16pi2*( betam2221 + oo16pi2 * betam2222 ) 

 
Else 
Dm222 = oo16pi2* betam2221 
End If 
 
 
Call Chop(Dm222) 

Call ParametersToG73(Dg1,Dg2,Dg3,Dlam5,Dlam1,Dlam4,Dlam3,Dlam2,DYu,DYd,               & 
& DYe,Dm122,Dm112,Dm222,f)

Iname = Iname - 1 
 
End Subroutine rge73  

Subroutine GToParameters75(g,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,              & 
& m122,m112,m222,vd,vu)

Implicit None 
Real(dp), Intent(in) :: g(75) 
Real(dp),Intent(out) :: g1,g2,g3,vd,vu

Complex(dp),Intent(out) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters75' 
 
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
Yu(i1,i2) = Cmplx( g(SumI+14), g(SumI+15), dp) 
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
Ye(i1,i2) = Cmplx( g(SumI+50), g(SumI+51), dp) 
End Do 
 End Do 
 
m122= Cmplx(g(68),g(69),dp) 
m112= Cmplx(g(70),g(71),dp) 
m222= Cmplx(g(72),g(73),dp) 
vd= g(74) 
vu= g(75) 
Do i1=1,75 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters75

Subroutine ParametersToG75(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,           & 
& m112,m222,vd,vu,g)

Implicit None 
Real(dp), Intent(out) :: g(75) 
Real(dp), Intent(in) :: g1,g2,g3,vd,vu

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG75' 
 
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
g(SumI+14) = Real(Yu(i1,i2), dp) 
g(SumI+15) = Aimag(Yu(i1,i2)) 
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
g(SumI+50) = Real(Ye(i1,i2), dp) 
g(SumI+51) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

g(68) = Real(m122,dp)  
g(69) = Aimag(m122)  
g(70) = Real(m112,dp)  
g(71) = Aimag(m112)  
g(72) = Real(m222,dp)  
g(73) = Aimag(m222)  
g(74) = vd  
g(75) = vu  
Iname = Iname - 1 
 
End Subroutine ParametersToG75

Subroutine rge75(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,         & 
& Dg3,vd,betavd1,betavd2,Dvd,vu,betavu1,betavu2,Dvu
Complex(dp) :: lam5,betalam51,betalam52,Dlam5,lam1,betalam11,betalam12,               & 
& Dlam1,lam4,betalam41,betalam42,Dlam4,lam3,betalam31,betalam32,Dlam3,lam2,              & 
& betalam21,betalam22,Dlam2,Yu(3,3),betaYu1(3,3),betaYu2(3,3),DYu(3,3),adjYu(3,3)        & 
& ,Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Ye(3,3),betaYe1(3,3)            & 
& ,betaYe2(3,3),DYe(3,3),adjYe(3,3),m122,betam1221,betam1222,Dm122,m112,betam1121,       & 
& betam1122,Dm112,m222,betam2221,betam2222,Dm222
Real(dp) :: Abslam5
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYd(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYeYe(3,3),        & 
& adjYuYu(3,3),YdadjYdYd(3,3),YdadjYuYu(3,3),YeadjYeYe(3,3),YuadjYdYd(3,3),              & 
& YuadjYuYu(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYd(3,3),adjYuYuadjYu(3,3),& 
& YdadjYdYdadjYd(3,3),YdadjYuYuadjYd(3,3),YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYdadjYuYuadjYd,TrYeadjYeYeadjYe,     & 
& TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: lam1p2,lam2p2,lam3p2,lam4p2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge75' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters75(gy,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,              & 
& m112,m222,vd,vu)

Abslam5 = Conjg(lam5)*lam5
Call Adjungate(Yu,adjYu)
Call Adjungate(Yd,adjYd)
Call Adjungate(Ye,adjYe)
 YdadjYd = Matmul(Yd,adjYd) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 YeadjYe = Matmul(Ye,adjYe) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 YuadjYd = Matmul(Yu,adjYd) 
 YuadjYu = Matmul(Yu,adjYu) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdYd = Matmul(adjYd,Yd) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYeYe = Matmul(adjYe,Ye) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYuYu = Matmul(adjYu,Yu) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 YdadjYdYd = Matmul(Yd,adjYdYd) 
 YdadjYuYu = Matmul(Yd,adjYuYu) 
 YeadjYeYe = Matmul(Ye,adjYeYe) 
 YuadjYdYd = Matmul(Yu,adjYdYd) 
 YuadjYuYu = Matmul(Yu,adjYuYu) 
 adjYdYdadjYd = Matmul(adjYd,YdadjYd) 
 adjYeYeadjYe = Matmul(adjYe,YeadjYe) 
 adjYuYuadjYd = Matmul(adjYu,YuadjYd) 
 adjYuYuadjYu = Matmul(adjYu,YuadjYu) 
 YdadjYdYdadjYd = Matmul(Yd,adjYdYdadjYd) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YdadjYuYuadjYd = Matmul(Yd,adjYuYuadjYd) 
Forall(i2=1:3)  YdadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYd(i2,i2),dp) 
 YeadjYeYeadjYe = Matmul(Ye,adjYeYeadjYe) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YuadjYuYuadjYu = Matmul(Yu,adjYuYuadjYu) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 TrYdadjYdYdadjYd = Real(cTrace(YdadjYdYdadjYd),dp) 
 TrYdadjYuYuadjYd = Real(cTrace(YdadjYuYuadjYd),dp) 
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
&  8*lam3*lam5 + 12*lam4*lam5 + 6*lam5*TrYdadjYd + 2*lam5*TrYeadjYe + 6*lam5*TrYuadjYu

 
 
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
&  + 4*lam1*TrYeadjYe - 4._dp*(TrYeadjYeYeadjYe)

 
 
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
 
betalam41  = 8._dp*(Abslam5) + (9*g1p2*g2p2)/5._dp + 4._dp*(lam4p2) - (9*g1p2*lam4)   & 
& /5._dp - 9*g2p2*lam4 + 2*lam1*lam4 + 2*lam2*lam4 + 8*lam3*lam4 + 6*lam4*TrYdadjYd +    & 
&  12._dp*(TrYdadjYuYuadjYd) + 2*lam4*TrYeadjYe + 6*lam4*TrYuadjYu

 
 
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
 
betalam31  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp - (9*g1p2*g2p2)/10._dp +         & 
&  9._dp*(g2p4)/4._dp + 4._dp*(lam3p2) + 2._dp*(lam4p2) - (9*g1p2*lam3)/5._dp -          & 
&  9*g2p2*lam3 + 6*lam1*lam3 + 6*lam2*lam3 + 2*lam1*lam4 + 2*lam2*lam4 + 6*lam3*TrYdadjYd -& 
&  12._dp*(TrYdadjYuYuadjYd) + 2*lam3*TrYeadjYe + 6*lam3*TrYuadjYu

 
 
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
 
betalam21  = 2._dp*(Abslam5) + 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp +         & 
&  9._dp*(g2p4)/4._dp + 12._dp*(lam2p2) + 4._dp*(lam3p2) + 2._dp*(lam4p2) -              & 
&  (9*g1p2*lam2)/5._dp - 9*g2p2*lam2 + 4*lam3*lam4 + 12*lam2*TrYuadjYu - 12._dp*(TrYuadjYuYuadjYu)

 
 
If (TwoLoopRGE) Then 
betalam22 = 0

 
Dlam2 = oo16pi2*( betalam21 + oo16pi2 * betalam22 ) 

 
Else 
Dlam2 = oo16pi2* betalam21 
End If 
 
 
Call Chop(Dlam2) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = (-17._dp*(g1p2)/20._dp - 9._dp*(g2p2)/4._dp - 8._dp*(g3p2) +               & 
&  3._dp*(TrYuadjYu))*Yu + (YuadjYdYd + 3._dp*(YuadjYuYu))/2._dp

 
 
If (TwoLoopRGE) Then 
betaYu2 = 0

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-((g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2) - 12._dp*(TrYdadjYd)               & 
&  - 4._dp*(TrYeadjYe))*Yd) + 2*(3._dp*(YdadjYdYd) + YdadjYuYu))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYd2 = 0

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = ((-9*(g1p2 + g2p2) + 12._dp*(TrYdadjYd) + 4._dp*(TrYeadjYe))               & 
& *Ye + 6._dp*(YeadjYeYe))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYe2 = 0

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! m122 
!-------------------- 
 
betam1221  = (-9*g1p2*m122)/10._dp - (9*g2p2*m122)/2._dp + 2*lam3*m122 +              & 
&  4*lam4*m122 + 3*m122*TrYdadjYd + m122*TrYeadjYe + 3*m122*TrYuadjYu + 6*Conjg(lam5)    & 
& *Conjg(m122)

 
 
If (TwoLoopRGE) Then 
betam1222 = 0

 
Dm122 = oo16pi2*( betam1221 + oo16pi2 * betam1222 ) 

 
Else 
Dm122 = oo16pi2* betam1221 
End If 
 
 
Call Chop(Dm122) 

!-------------------- 
! m112 
!-------------------- 
 
betam1121  = (-9*g1p2*m112)/10._dp - (9*g2p2*m112)/2._dp + 6*lam1*m112 +              & 
&  4*lam3*m222 + 2*lam4*m222 + 6*m112*TrYdadjYd + 2*m112*TrYeadjYe

 
 
If (TwoLoopRGE) Then 
betam1122 = 0

 
Dm112 = oo16pi2*( betam1121 + oo16pi2 * betam1122 ) 

 
Else 
Dm112 = oo16pi2* betam1121 
End If 
 
 
Call Chop(Dm112) 

!-------------------- 
! m222 
!-------------------- 
 
betam2221  = 4*lam3*m112 + 2*lam4*m112 - (9*g1p2*m222)/10._dp - (9*g2p2*m222)         & 
& /2._dp + 6*lam2*m222 + 6*m222*TrYuadjYu

 
 
If (TwoLoopRGE) Then 
betam2222 = 0

 
Dm222 = oo16pi2*( betam2221 + oo16pi2 * betam2222 ) 

 
Else 
Dm222 = oo16pi2* betam2221 
End If 
 
 
Call Chop(Dm222) 

!-------------------- 
! vd 
!-------------------- 
 
betavd1  = (vd*(-60._dp*(TrYdadjYd) - 20._dp*(TrYeadjYe) + 3*(g1p2 + 5._dp*(g2p2))    & 
& *(3 + Xi)))/20._dp

 
 
If (TwoLoopRGE) Then 
betavd2 = 0

 
Dvd = oo16pi2*( betavd1 + oo16pi2 * betavd2 ) 

 
Else 
Dvd = oo16pi2* betavd1 
End If 
 
 
!-------------------- 
! vu 
!-------------------- 
 
betavu1  = (3*vu*(-20._dp*(TrYuadjYu) + (g1p2 + 5._dp*(g2p2))*(3 + Xi)))/20._dp

 
 
If (TwoLoopRGE) Then 
betavu2 = 0

 
Dvu = oo16pi2*( betavu1 + oo16pi2 * betavu2 ) 

 
Else 
Dvu = oo16pi2* betavu1 
End If 
 
 
Call ParametersToG75(Dg1,Dg2,Dg3,Dlam5,Dlam1,Dlam4,Dlam3,Dlam2,DYu,DYd,               & 
& DYe,Dm122,Dm112,Dm222,Dvd,Dvu,f)

Iname = Iname - 1 
 
End Subroutine rge75  

End Module RGEs_gumTHDMII 
 
