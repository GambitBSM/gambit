! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 14:58 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module RGEs_MSSM 
 
Use Control 
Use Model_Data_MSSM 
Use Mathematics 
 
Logical,Private,Save::OnlyDiagonal

Real(dp),Parameter::id3R(3,3)=& 
   & Reshape(Source=(/& 
   & 1,0,0,& 
 &0,1,0,& 
 &0,0,1& 
 &/),shape=(/3,3/)) 
Contains 


Subroutine GToParameters57(g,g1,g2,g3,Yd,Ye,Yu)

Implicit None 
Real(dp), Intent(in) :: g(57) 
Real(dp),Intent(out) :: g1,g2,g3

Complex(dp),Intent(out) :: Yd(3,3),Ye(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters57' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yd(i1,i2) = Cmplx( g(SumI+4), g(SumI+5), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Ye(i1,i2) = Cmplx( g(SumI+22), g(SumI+23), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yu(i1,i2) = Cmplx( g(SumI+40), g(SumI+41), dp) 
End Do 
 End Do 
 
Do i1=1,57 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters57

Subroutine ParametersToG57(g1,g2,g3,Yd,Ye,Yu,g)

Implicit None 
Real(dp), Intent(out) :: g(57) 
Real(dp), Intent(in) :: g1,g2,g3

Complex(dp), Intent(in) :: Yd(3,3),Ye(3,3),Yu(3,3)

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG57' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+4) = Real(Yd(i1,i2), dp) 
g(SumI+5) = Aimag(Yd(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+22) = Real(Ye(i1,i2), dp) 
g(SumI+23) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+40) = Real(Yu(i1,i2), dp) 
g(SumI+41) = Aimag(Yu(i1,i2)) 
End Do 
End Do 

Iname = Iname - 1 
 
End Subroutine ParametersToG57

Subroutine rge57(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,Dg3
Complex(dp) :: Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Ye(3,3)          & 
& ,betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3),Yu(3,3),betaYu1(3,3),betaYu2(3,3)       & 
& ,DYu(3,3),adjYu(3,3)
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYeYe(3,3),adjYuYu(3,3),        & 
& YdadjYdYd(3,3),YdadjYuYu(3,3),YeadjYeYe(3,3),YuadjYdYd(3,3),YuadjYuYu(3,3)

Complex(dp) :: YuadjYd(3,3),adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYd(3,3),adjYuYuadjYu(3,3), & 
& YdadjYdYdadjYd(3,3),YdadjYuYuadjYd(3,3),YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3),       & 
& adjYdYdadjYdYd(3,3),adjYdYdadjYuYu(3,3),adjYeYeadjYeYe(3,3),adjYuYuadjYdYd(3,3),       & 
& adjYuYuadjYuYu(3,3),YdadjYdYdadjYdYd(3,3),YdadjYuYuadjYdYd(3,3),YdadjYuYuadjYuYu(3,3), & 
& YeadjYeYeadjYeYe(3,3),YuadjYdYdadjYdYd(3,3),YuadjYdYdadjYuYu(3,3),YuadjYuYuadjYuYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu

Complex(dp) :: TrYdadjYdYdadjYd,TrYdadjYuYuadjYd,TrYeadjYeYeadjYe,TrYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g2p2,g2p3,g3p2,g3p3

Real(dp) :: g1p4,g2p4,g3p4

Iname = Iname +1 
NameOfUnit(Iname) = 'rge57' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters57(gy,g1,g2,g3,Yd,Ye,Yu)

Call Adjungate(Yd,adjYd)
Call Adjungate(Ye,adjYe)
Call Adjungate(Yu,adjYu)
 YdadjYd = Matmul2(Yd,adjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 YeadjYe = Matmul2(Ye,adjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 YuadjYu = Matmul2(Yu,adjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdYd = Matmul2(adjYd,Yd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYeYe = Matmul2(adjYe,Ye,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYuYu = Matmul2(adjYu,Yu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 YdadjYdYd = Matmul2(Yd,adjYdYd,OnlyDiagonal) 
 YdadjYuYu = Matmul2(Yd,adjYuYu,OnlyDiagonal) 
 YeadjYeYe = Matmul2(Ye,adjYeYe,OnlyDiagonal) 
 YuadjYdYd = Matmul2(Yu,adjYdYd,OnlyDiagonal) 
 YuadjYuYu = Matmul2(Yu,adjYuYu,OnlyDiagonal) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 g1p2 =g1**2 
 g1p3 =g1**3 
 g2p2 =g2**2 
 g2p3 =g2**3 
 g3p2 =g3**2 
 g3p3 =g3**3 
 g1p4 =g1**4 
 g2p4 =g2**4 
 g3p4 =g3**4 


If (TwoLoopRGE) Then 
 YuadjYd = Matmul2(Yu,adjYd,OnlyDiagonal) 
 adjYdYdadjYd = Matmul2(adjYd,YdadjYd,OnlyDiagonal) 
 adjYeYeadjYe = Matmul2(adjYe,YeadjYe,OnlyDiagonal) 
 adjYuYuadjYd = Matmul2(adjYu,YuadjYd,OnlyDiagonal) 
 adjYuYuadjYu = Matmul2(adjYu,YuadjYu,OnlyDiagonal) 
 YdadjYdYdadjYd = Matmul2(Yd,adjYdYdadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YdadjYuYuadjYd = Matmul2(Yd,adjYuYuadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYd(i2,i2),dp) 
 YeadjYeYeadjYe = Matmul2(Ye,adjYeYeadjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YuadjYuYuadjYu = Matmul2(Yu,adjYuYuadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 adjYdYdadjYdYd = Matmul2(adjYd,YdadjYdYd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYdadjYdYd(i2,i2) =  Real(adjYdYdadjYdYd(i2,i2),dp) 
 adjYdYdadjYuYu = Matmul2(adjYd,YdadjYuYu,OnlyDiagonal) 
 adjYeYeadjYeYe = Matmul2(adjYe,YeadjYeYe,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYeadjYeYe(i2,i2) =  Real(adjYeYeadjYeYe(i2,i2),dp) 
 adjYuYuadjYdYd = Matmul2(adjYu,YuadjYdYd,OnlyDiagonal) 
 adjYuYuadjYuYu = Matmul2(adjYu,YuadjYuYu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYuadjYuYu(i2,i2) =  Real(adjYuYuadjYuYu(i2,i2),dp) 
 YdadjYdYdadjYdYd = Matmul2(Yd,adjYdYdadjYdYd,OnlyDiagonal) 
 YdadjYuYuadjYdYd = Matmul2(Yd,adjYuYuadjYdYd,OnlyDiagonal) 
 YdadjYuYuadjYuYu = Matmul2(Yd,adjYuYuadjYuYu,OnlyDiagonal) 
 YeadjYeYeadjYeYe = Matmul2(Ye,adjYeYeadjYeYe,OnlyDiagonal) 
 YuadjYdYdadjYdYd = Matmul2(Yu,adjYdYdadjYdYd,OnlyDiagonal) 
 YuadjYdYdadjYuYu = Matmul2(Yu,adjYdYdadjYuYu,OnlyDiagonal) 
 YuadjYuYuadjYuYu = Matmul2(Yu,adjYuYuadjYuYu,OnlyDiagonal) 
 TrYdadjYdYdadjYd = cTrace(YdadjYdYdadjYd) 
 TrYdadjYuYuadjYd = cTrace(YdadjYuYuadjYd) 
 TrYeadjYeYeadjYe = cTrace(YeadjYeYeadjYe) 
 TrYuadjYuYuadjYu = cTrace(YuadjYuYuadjYu) 
 g1p4 =g1**4 
 g2p4 =g2**4 
 g3p4 =g3**4 
End If 
 
 
!-------------------- 
! g1 
!-------------------- 
 
betag11  = 33._dp*(g1p3)/5._dp

 
 
If (TwoLoopRGE) Then 
betag12 = (g1p3*(199._dp*(g1p2) + 135._dp*(g2p2) + 440._dp*(g3p2) - 70._dp*(TrYdadjYd) -        & 
&  90._dp*(TrYeadjYe) - 130._dp*(TrYuadjYu)))/25._dp

 
Dg1 = oo16pi2*( betag11 + oo16pi2 * betag12 ) 

 
Else 
Dg1 = oo16pi2* betag11 
End If 
 
 
!-------------------- 
! g2 
!-------------------- 
 
betag21  = g2p3

 
 
If (TwoLoopRGE) Then 
betag22 = (g2p3*(9._dp*(g1p2) + 125._dp*(g2p2) + 120._dp*(g3p2) - 30._dp*(TrYdadjYd) -          & 
&  10._dp*(TrYeadjYe) - 30._dp*(TrYuadjYu)))/5._dp

 
Dg2 = oo16pi2*( betag21 + oo16pi2 * betag22 ) 

 
Else 
Dg2 = oo16pi2* betag21 
End If 
 
 
!-------------------- 
! g3 
!-------------------- 
 
betag31  = -3._dp*(g3p3)

 
 
If (TwoLoopRGE) Then 
betag32 = (g3p3*(11._dp*(g1p2) + 45._dp*(g2p2) + 70._dp*(g3p2) - 20._dp*(TrYdadjYd) -           & 
&  20._dp*(TrYuadjYu)))/5._dp

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 ) 

 
Else 
Dg3 = oo16pi2* betag31 
End If 
 
 
!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-7._dp*(g1p2)/15._dp - 3._dp*(g2p2) - 16._dp*(g3p2)/3._dp +               & 
&  3._dp*(TrYdadjYd) + TrYeadjYe)*Yd + 3._dp*(YdadjYdYd) + YdadjYuYu

 
 
If (TwoLoopRGE) Then 
betaYd2 = (287._dp*(g1p4)/90._dp + g1p2*g2p2 + 15._dp*(g2p4)/2._dp + (8*g1p2*g3p2)/9._dp +      & 
&  8*g2p2*g3p2 - 16._dp*(g3p4)/9._dp - (2*(g1p2 - 40._dp*(g3p2))*TrYdadjYd)/5._dp -      & 
&  9._dp*(TrYdadjYdYdadjYd) - 3._dp*(TrYdadjYuYuadjYd) + (6*g1p2*TrYeadjYe)/5._dp -      & 
&  3._dp*(TrYeadjYeYeadjYe))*Yd + (4._dp*(g1p2)/5._dp + 6._dp*(g2p2) - 9._dp*(TrYdadjYd) -& 
&  3._dp*(TrYeadjYe))*YdadjYdYd - 4._dp*(YdadjYdYdadjYdYd) + (4*g1p2*YdadjYuYu)/5._dp -  & 
&  3*TrYuadjYu*YdadjYuYu - 2._dp*(YdadjYuYuadjYdYd) - 2._dp*(YdadjYuYuadjYuYu)

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = (-9._dp*(g1p2)/5._dp - 3._dp*(g2p2) + 3._dp*(TrYdadjYd) + TrYeadjYe)       & 
& *Ye + 3._dp*(YeadjYeYe)

 
 
If (TwoLoopRGE) Then 
betaYe2 = ((-4*(g1p2 - 40._dp*(g3p2))*TrYdadjYd + 3*(45._dp*(g1p4) + 6*g1p2*g2p2 +              & 
&  25._dp*(g2p4) - 30._dp*(TrYdadjYdYdadjYd) - 10._dp*(TrYdadjYuYuadjYd) +               & 
&  4*g1p2*TrYeadjYe - 10._dp*(TrYeadjYeYeadjYe)))*Ye)/10._dp + (6._dp*(g2p2) -           & 
&  9._dp*(TrYdadjYd) - 3._dp*(TrYeadjYe))*YeadjYeYe - 4._dp*(YeadjYeYeadjYeYe)

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = -((13._dp*(g1p2) + 45._dp*(g2p2) + 80._dp*(g3p2) - 45._dp*(TrYuadjYu))     & 
& *Yu)/15._dp + YuadjYdYd + 3._dp*(YuadjYuYu)

 
 
If (TwoLoopRGE) Then 
betaYu2 = (2743._dp*(g1p4)/450._dp + g1p2*g2p2 + 15._dp*(g2p4)/2._dp + (136*g1p2*g3p2)/45._dp + & 
&  8*g2p2*g3p2 - 16._dp*(g3p4)/9._dp - 3._dp*(TrYdadjYuYuadjYd) + (4*(g1p2 +             & 
&  20._dp*(g3p2))*TrYuadjYu)/5._dp - 9._dp*(TrYuadjYuYuadjYu))*Yu + (2._dp*(g1p2)/5._dp -& 
&  3._dp*(TrYdadjYd) - TrYeadjYe)*YuadjYdYd - 2._dp*(YuadjYdYdadjYdYd) - 2._dp*(YuadjYdYdadjYuYu) +& 
&  (2*g1p2*YuadjYuYu)/5._dp + 6*g2p2*YuadjYuYu - 9*TrYuadjYu*YuadjYuYu - 4._dp*(YuadjYuYuadjYuYu)

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

Call ParametersToG57(Dg1,Dg2,Dg3,DYd,DYe,DYu,f)

Iname = Iname - 1 
 
End Subroutine rge57  

Subroutine GToParameters213(g,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,              & 
& mHd2,mHu2,md2,mu2,me2,M1,M2,M3)

Implicit None 
Real(dp), Intent(in) :: g(213) 
Real(dp),Intent(out) :: g1,g2,g3,mHd2,mHu2

Complex(dp),Intent(out) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters213' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yd(i1,i2) = Cmplx( g(SumI+4), g(SumI+5), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Ye(i1,i2) = Cmplx( g(SumI+22), g(SumI+23), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yu(i1,i2) = Cmplx( g(SumI+40), g(SumI+41), dp) 
End Do 
 End Do 
 
Mu= Cmplx(g(58),g(59),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Td(i1,i2) = Cmplx( g(SumI+60), g(SumI+61), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Te(i1,i2) = Cmplx( g(SumI+78), g(SumI+79), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Tu(i1,i2) = Cmplx( g(SumI+96), g(SumI+97), dp) 
End Do 
 End Do 
 
Bmu= Cmplx(g(114),g(115),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
mq2(i1,i2) = Cmplx( g(SumI+116), g(SumI+117), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
ml2(i1,i2) = Cmplx( g(SumI+134), g(SumI+135), dp) 
End Do 
 End Do 
 
mHd2= g(152) 
mHu2= g(153) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
md2(i1,i2) = Cmplx( g(SumI+154), g(SumI+155), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
mu2(i1,i2) = Cmplx( g(SumI+172), g(SumI+173), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
me2(i1,i2) = Cmplx( g(SumI+190), g(SumI+191), dp) 
End Do 
 End Do 
 
M1= Cmplx(g(208),g(209),dp) 
M2= Cmplx(g(210),g(211),dp) 
M3= Cmplx(g(212),g(213),dp) 
Do i1=1,213 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters213

Subroutine ParametersToG213(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,           & 
& mHu2,md2,mu2,me2,M1,M2,M3,g)

Implicit None 
Real(dp), Intent(out) :: g(213) 
Real(dp), Intent(in) :: g1,g2,g3,mHd2,mHu2

Complex(dp), Intent(in) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG213' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+4) = Real(Yd(i1,i2), dp) 
g(SumI+5) = Aimag(Yd(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+22) = Real(Ye(i1,i2), dp) 
g(SumI+23) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+40) = Real(Yu(i1,i2), dp) 
g(SumI+41) = Aimag(Yu(i1,i2)) 
End Do 
End Do 

g(58) = Real(Mu,dp)  
g(59) = Aimag(Mu)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+60) = Real(Td(i1,i2), dp) 
g(SumI+61) = Aimag(Td(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+78) = Real(Te(i1,i2), dp) 
g(SumI+79) = Aimag(Te(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+96) = Real(Tu(i1,i2), dp) 
g(SumI+97) = Aimag(Tu(i1,i2)) 
End Do 
End Do 

g(114) = Real(Bmu,dp)  
g(115) = Aimag(Bmu)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+116) = Real(mq2(i1,i2), dp) 
g(SumI+117) = Aimag(mq2(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+134) = Real(ml2(i1,i2), dp) 
g(SumI+135) = Aimag(ml2(i1,i2)) 
End Do 
End Do 

g(152) = mHd2  
g(153) = mHu2  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+154) = Real(md2(i1,i2), dp) 
g(SumI+155) = Aimag(md2(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+172) = Real(mu2(i1,i2), dp) 
g(SumI+173) = Aimag(mu2(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+190) = Real(me2(i1,i2), dp) 
g(SumI+191) = Aimag(me2(i1,i2)) 
End Do 
End Do 

g(208) = Real(M1,dp)  
g(209) = Aimag(M1)  
g(210) = Real(M2,dp)  
g(211) = Aimag(M2)  
g(212) = Real(M3,dp)  
g(213) = Aimag(M3)  
Iname = Iname - 1 
 
End Subroutine ParametersToG213

Subroutine rge213(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,         & 
& Dg3,mHd2,betamHd21,betamHd22,DmHd2,mHu2,betamHu21,betamHu22,DmHu2
Complex(dp) :: Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Ye(3,3)          & 
& ,betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3),Yu(3,3),betaYu1(3,3),betaYu2(3,3)       & 
& ,DYu(3,3),adjYu(3,3),Mu,betaMu1,betaMu2,DMu,Td(3,3),betaTd1(3,3),betaTd2(3,3)          & 
& ,DTd(3,3),adjTd(3,3),Te(3,3),betaTe1(3,3),betaTe2(3,3),DTe(3,3),adjTe(3,3)             & 
& ,Tu(3,3),betaTu1(3,3),betaTu2(3,3),DTu(3,3),adjTu(3,3),Bmu,betaBmu1,betaBmu2,          & 
& DBmu,mq2(3,3),betamq21(3,3),betamq22(3,3),Dmq2(3,3),ml2(3,3),betaml21(3,3)             & 
& ,betaml22(3,3),Dml2(3,3),md2(3,3),betamd21(3,3),betamd22(3,3),Dmd2(3,3),               & 
& mu2(3,3),betamu21(3,3),betamu22(3,3),Dmu2(3,3),me2(3,3),betame21(3,3),betame22(3,3)    & 
& ,Dme2(3,3),M1,betaM11,betaM12,DM1,M2,betaM21,betaM22,DM2,M3,betaM31,betaM32,DM3
Real(dp) :: Tr1(3),Tr2(3),Tr3(3) 
Real(dp) :: Tr2U1(3,3) 
Real(dp) :: AbsM1,AbsM2,AbsM3
Complex(dp) :: md2Yd(3,3),me2Ye(3,3),ml2adjYe(3,3),mq2adjYd(3,3),mq2adjYu(3,3),mu2Yu(3,3),           & 
& Ydmq2(3,3),YdadjYd(3,3),Yeml2(3,3),YeadjYe(3,3),Yumq2(3,3),YuadjYu(3,3),               & 
& adjYdmd2(3,3),adjYdYd(3,3),adjYdTd(3,3),adjYeme2(3,3),adjYeYe(3,3),adjYeTe(3,3),       & 
& adjYumu2(3,3),adjYuYu(3,3),adjYuTu(3,3),adjTdTd(3,3),adjTeTe(3,3),adjTuTu(3,3),        & 
& CTdTpTd(3,3),CTeTpTe(3,3),CTuTpTu(3,3),TdadjTd(3,3),TeadjTe(3,3),TuadjTu(3,3),         & 
& md2YdadjYd(3,3),me2YeadjYe(3,3),ml2adjYeYe(3,3),mq2adjYdYd(3,3),mq2adjYuYu(3,3),       & 
& mu2YuadjYu(3,3),Ydmq2adjYd(3,3),YdadjYdmd2(3,3),YdadjYdYd(3,3),YdadjYdTd(3,3),         & 
& YdadjYuYu(3,3),YdadjYuTu(3,3),Yeml2adjYe(3,3),YeadjYeme2(3,3),YeadjYeYe(3,3),          & 
& YeadjYeTe(3,3),Yumq2adjYu(3,3),YuadjYdYd(3,3),YuadjYdTd(3,3),YuadjYumu2(3,3),          & 
& YuadjYuYu(3,3),YuadjYuTu(3,3),adjYdmd2Yd(3,3),adjYdYdmq2(3,3),adjYeme2Ye(3,3),         & 
& adjYeYeml2(3,3),adjYumu2Yu(3,3),adjYuYumq2(3,3),TdadjYdYd(3,3),TdadjYuYu(3,3),         & 
& TeadjYeYe(3,3),TuadjYdYd(3,3),TuadjYuYu(3,3)

Complex(dp) :: YdadjYu(3,3),YdadjTd(3,3),YdadjTu(3,3),YeadjTe(3,3),YuadjYd(3,3),YuadjTd(3,3),        & 
& YuadjTu(3,3),adjYdCmd2(3,3),adjYeCme2(3,3),adjYuCmu2(3,3),adjTdYd(3,3),adjTeYe(3,3),   & 
& adjTuYu(3,3),Cml2adjYe(3,3),Cmq2adjYd(3,3),Cmq2adjYu(3,3),CTdTpYd(3,3),CTeTpYe(3,3),   & 
& CTuTpYu(3,3),TdadjYd(3,3),TdadjYu(3,3),TdadjTu(3,3),TeadjYe(3,3),TuadjYd(3,3),         & 
& TuadjYu(3,3),TuadjTd(3,3),md2YdadjYu(3,3),mu2YuadjYd(3,3),Ydmq2adjYu(3,3),             & 
& YdadjYdCmd2(3,3),YdadjYumu2(3,3),YdadjTdTd(3,3),YdCmq2adjYd(3,3),YeadjYeCme2(3,3),     & 
& YeadjTeTe(3,3),YeCml2adjYe(3,3),Yumq2adjYd(3,3),YuadjYdmd2(3,3),YuadjYuCmu2(3,3),      & 
& YuadjTuTu(3,3),YuCmq2adjYu(3,3),adjYdYdadjYd(3,3),adjYdYdadjYu(3,3),adjYdYdadjTd(3,3), & 
& adjYdYdadjTu(3,3),adjYdTdadjYd(3,3),adjYdTdadjYu(3,3),adjYdTdadjTd(3,3),               & 
& adjYdTdadjTu(3,3),adjYeYeadjYe(3,3),adjYeYeadjTe(3,3),adjYeTeadjYe(3,3),               & 
& adjYeTeadjTe(3,3),adjYuYuadjYd(3,3),adjYuYuadjYu(3,3),adjYuYuadjTd(3,3),               & 
& adjYuYuadjTu(3,3),adjYuTuadjYd(3,3),adjYuTuadjYu(3,3),adjYuTuadjTd(3,3),               & 
& adjYuTuadjTu(3,3),adjTdYdadjYd(3,3),adjTdYdadjYu(3,3),adjTdTdadjYd(3,3),               & 
& adjTdTdadjYu(3,3),adjTeYeadjYe(3,3),adjTeTeadjYe(3,3),adjTuYuadjYd(3,3),               & 
& adjTuYuadjYu(3,3),adjTuTuadjYd(3,3),adjTuTuadjYu(3,3),TdadjTdYd(3,3),TeadjTeYe(3,3),   & 
& TuadjTuYu(3,3),md2YdadjYdYd(3,3),me2YeadjYeYe(3,3),ml2adjYeYeadjYe(3,3),               & 
& mq2adjYdYdadjYd(3,3),mq2adjYdYdadjYu(3,3),mq2adjYuYuadjYd(3,3),mq2adjYuYuadjYu(3,3),   & 
& mu2YuadjYuYu(3,3),Ydmq2adjYdYd(3,3),YdadjYdmd2Yd(3,3),YdadjYdYdmq2(3,3),               & 
& YdadjYdYdadjYd(3,3),YdadjYdTdadjYd(3,3),YdadjYdTdadjTd(3,3),YdadjYuYuadjYd(3,3),       & 
& YdadjYuTuadjYd(3,3),YdadjYuTuadjTd(3,3),YdadjTdTdadjYd(3,3),YdadjTuTuadjYd(3,3),       & 
& Yeml2adjYeYe(3,3),YeadjYeme2Ye(3,3),YeadjYeYeml2(3,3),YeadjYeYeadjYe(3,3),             & 
& YeadjYeTeadjYe(3,3),YeadjYeTeadjTe(3,3),YeadjTeTeadjYe(3,3),Yumq2adjYuYu(3,3),         & 
& YuadjYdYdadjYu(3,3),YuadjYdTdadjYu(3,3),YuadjYdTdadjTu(3,3),YuadjYumu2Yu(3,3),         & 
& YuadjYuYumq2(3,3),YuadjYuYuadjYu(3,3),YuadjYuTuadjYu(3,3),YuadjYuTuadjTu(3,3),         & 
& YuadjTdTdadjYu(3,3),YuadjTuTuadjYu(3,3),adjYdmd2YdadjYd(3,3),adjYdmd2YdadjYu(3,3),     & 
& adjYdYdmq2adjYd(3,3),adjYdYdmq2adjYu(3,3),adjYdYdadjYdmd2(3,3),adjYdYdadjYdYd(3,3),    & 
& adjYdYdadjYdTd(3,3),adjYdYdadjYumu2(3,3),adjYdYdadjYuYu(3,3),adjYdYdadjYuTu(3,3),      & 
& adjYdYdadjTdTd(3,3),adjYdTdadjYdYd(3,3),adjYdTdadjYuYu(3,3),adjYdTdadjTdYd(3,3),       & 
& adjYeme2YeadjYe(3,3),adjYeYeml2adjYe(3,3),adjYeYeadjYeme2(3,3),adjYeYeadjYeYe(3,3),    & 
& adjYeYeadjYeTe(3,3),adjYeYeadjTeTe(3,3),adjYeTeadjYeYe(3,3),adjYeTeadjTeYe(3,3),       & 
& adjYumu2YuadjYd(3,3),adjYumu2YuadjYu(3,3),adjYuYumq2adjYd(3,3),adjYuYumq2adjYu(3,3),   & 
& adjYuYuadjYdmd2(3,3),adjYuYuadjYdYd(3,3),adjYuYuadjYdTd(3,3),adjYuYuadjYumu2(3,3),     & 
& adjYuYuadjYuYu(3,3),adjYuYuadjYuTu(3,3),adjYuYuadjTuTu(3,3),adjYuTuadjYdYd(3,3),       & 
& adjYuTuadjYuYu(3,3),adjYuTuadjTuYu(3,3),adjTdYdadjYdTd(3,3),adjTdTdadjYdYd(3,3),       & 
& adjTeYeadjYeTe(3,3),adjTeTeadjYeYe(3,3),adjTuYuadjYuTu(3,3),adjTuTuadjYuYu(3,3),       & 
& TdadjYdYdadjTd(3,3),TdadjYuYuadjTd(3,3),TdadjTdYdadjYd(3,3),TdadjTuYuadjYd(3,3),       & 
& TeadjYeYeadjTe(3,3),TeadjTeYeadjYe(3,3),TuadjYdYdadjTu(3,3),TuadjYuYuadjTu(3,3)

Complex(dp) :: TuadjTdYdadjYu(3,3),TuadjTuYuadjYu(3,3),md2YdadjYdYdadjYd(3,3),md2YdadjYuYuadjYd(3,3), & 
& me2YeadjYeYeadjYe(3,3),ml2adjYeYeadjYeYe(3,3),mq2adjYdYdadjYdYd(3,3),mq2adjYdYdadjYuYu(3,3),& 
& mq2adjYuYuadjYdYd(3,3),mq2adjYuYuadjYuYu(3,3),mu2YuadjYdYdadjYu(3,3),mu2YuadjYuYuadjYu(3,3),& 
& Ydmq2adjYdYdadjYd(3,3),Ydmq2adjYuYuadjYd(3,3),YdadjYdmd2YdadjYd(3,3),YdadjYdYdmq2adjYd(3,3),& 
& YdadjYdYdadjYdmd2(3,3),YdadjYdYdadjYdYd(3,3),YdadjYdYdadjYdTd(3,3),YdadjYdTdadjYdYd(3,3),& 
& YdadjYumu2YuadjYd(3,3),YdadjYuYumq2adjYd(3,3),YdadjYuYuadjYdmd2(3,3),YdadjYuYuadjYdYd(3,3),& 
& YdadjYuYuadjYdTd(3,3),YdadjYuYuadjYuYu(3,3),YdadjYuYuadjYuTu(3,3),YdadjYuTuadjYdYd(3,3),& 
& YdadjYuTuadjYuYu(3,3),Yeml2adjYeYeadjYe(3,3),YeadjYeme2YeadjYe(3,3),YeadjYeYeml2adjYe(3,3),& 
& YeadjYeYeadjYeme2(3,3),YeadjYeYeadjYeYe(3,3),YeadjYeYeadjYeTe(3,3),YeadjYeTeadjYeYe(3,3),& 
& Yumq2adjYdYdadjYu(3,3),Yumq2adjYuYuadjYu(3,3),YuadjYdmd2YdadjYu(3,3),YuadjYdYdmq2adjYu(3,3),& 
& YuadjYdYdadjYdYd(3,3),YuadjYdYdadjYdTd(3,3),YuadjYdYdadjYumu2(3,3),YuadjYdYdadjYuYu(3,3),& 
& YuadjYdYdadjYuTu(3,3),YuadjYdTdadjYdYd(3,3),YuadjYdTdadjYuYu(3,3),YuadjYumu2YuadjYu(3,3),& 
& YuadjYuYumq2adjYu(3,3),YuadjYuYuadjYumu2(3,3),YuadjYuYuadjYuYu(3,3),YuadjYuYuadjYuTu(3,3),& 
& YuadjYuTuadjYuYu(3,3),adjYdmd2YdadjYdYd(3,3),adjYdYdmq2adjYdYd(3,3),adjYdYdadjYdmd2Yd(3,3),& 
& adjYdYdadjYdYdmq2(3,3),adjYeme2YeadjYeYe(3,3),adjYeYeml2adjYeYe(3,3),adjYeYeadjYeme2Ye(3,3),& 
& adjYeYeadjYeYeml2(3,3),adjYumu2YuadjYuYu(3,3),adjYuYumq2adjYuYu(3,3),adjYuYuadjYumu2Yu(3,3),& 
& adjYuYuadjYuYumq2(3,3),TdadjYdYdadjYdYd(3,3),TdadjYuYuadjYdYd(3,3),TdadjYuYuadjYuYu(3,3),& 
& TeadjYeYeadjYeYe(3,3),TuadjYdYdadjYdYd(3,3),TuadjYdYdadjYuYu(3,3),TuadjYuYuadjYuYu(3,3)

Complex(dp) :: Trmd2,Trme2,Trml2,Trmq2,Trmu2,TrYdadjYd,TrYeadjYe,TrYuadjYu,TradjYdTd,TradjYeTe,      & 
& TradjYuTu,TrCTdTpTd,TrCTeTpTe,TrCTuTpTu,Trmd2YdadjYd,Trme2YeadjYe,Trml2adjYeYe,        & 
& Trmq2adjYdYd,Trmq2adjYuYu,Trmu2YuadjYu

Complex(dp) :: TrCTdTpYd,TrCTeTpYe,TrCTuTpYu,TrYdadjYdCmd2,TrYdCmq2adjYd,TrYeadjYeCme2,              & 
& TrYeCml2adjYe,TrYuadjYuCmu2,TrYuCmq2adjYu,TrYdadjYdYdadjYd,TrYdadjYdTdadjYd,           & 
& TrYdadjYdTdadjTd,TrYdadjYuYuadjYd,TrYdadjYuTuadjYd,TrYdadjYuTuadjTd,TrYdadjTdTdadjYd,  & 
& TrYdadjTuTuadjYd,TrYeadjYeYeadjYe,TrYeadjYeTeadjYe,TrYeadjYeTeadjTe,TrYeadjTeTeadjYe,  & 
& TrYuadjYdTdadjYu,TrYuadjYdTdadjTu,TrYuadjYuYuadjYu,TrYuadjYuTuadjYu,TrYuadjYuTuadjTu,  & 
& TrYuadjTdTdadjYu,TrYuadjTuTuadjYu,Trmd2YdadjYdYdadjYd,Trmd2YdadjYuYuadjYd,             & 
& Trme2YeadjYeYeadjYe,Trml2adjYeYeadjYeYe,Trmq2adjYdYdadjYdYd,Trmq2adjYdYdadjYuYu,       & 
& Trmq2adjYuYuadjYdYd,Trmq2adjYuYuadjYuYu,Trmu2YuadjYdYdadjYu,Trmu2YuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g2p2,g2p3,g3p2,g3p3

Complex(dp) :: sqrt3ov5,ooSqrt15

Real(dp) :: g1p4,g2p4,g3p4

Complex(dp) :: sqrt15

Iname = Iname +1 
NameOfUnit(Iname) = 'rge213' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters213(gy,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3)

AbsM1 = Conjg(M1)*M1
AbsM2 = Conjg(M2)*M2
AbsM3 = Conjg(M3)*M3
Call Adjungate(Yd,adjYd)
Call Adjungate(Ye,adjYe)
Call Adjungate(Yu,adjYu)
Call Adjungate(Td,adjTd)
Call Adjungate(Te,adjTe)
Call Adjungate(Tu,adjTu)
 md2Yd = Matmul2(md2,Yd,OnlyDiagonal) 
 me2Ye = Matmul2(me2,Ye,OnlyDiagonal) 
 ml2adjYe = Matmul2(ml2,adjYe,OnlyDiagonal) 
 mq2adjYd = Matmul2(mq2,adjYd,OnlyDiagonal) 
 mq2adjYu = Matmul2(mq2,adjYu,OnlyDiagonal) 
 mu2Yu = Matmul2(mu2,Yu,OnlyDiagonal) 
 Ydmq2 = Matmul2(Yd,mq2,OnlyDiagonal) 
 YdadjYd = Matmul2(Yd,adjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 Yeml2 = Matmul2(Ye,ml2,OnlyDiagonal) 
 YeadjYe = Matmul2(Ye,adjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 Yumq2 = Matmul2(Yu,mq2,OnlyDiagonal) 
 YuadjYu = Matmul2(Yu,adjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdmd2 = Matmul2(adjYd,md2,OnlyDiagonal) 
 adjYdYd = Matmul2(adjYd,Yd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYdTd = Matmul2(adjYd,Td,OnlyDiagonal) 
 adjYeme2 = Matmul2(adjYe,me2,OnlyDiagonal) 
 adjYeYe = Matmul2(adjYe,Ye,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYeTe = Matmul2(adjYe,Te,OnlyDiagonal) 
 adjYumu2 = Matmul2(adjYu,mu2,OnlyDiagonal) 
 adjYuYu = Matmul2(adjYu,Yu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 adjYuTu = Matmul2(adjYu,Tu,OnlyDiagonal) 
 adjTdTd = Matmul2(adjTd,Td,OnlyDiagonal) 
 adjTeTe = Matmul2(adjTe,Te,OnlyDiagonal) 
 adjTuTu = Matmul2(adjTu,Tu,OnlyDiagonal) 
 CTdTpTd = Matmul2(Conjg(Td),Transpose(Td),OnlyDiagonal) 
Forall(i2=1:3)  CTdTpTd(i2,i2) =  Real(CTdTpTd(i2,i2),dp) 
 CTeTpTe = Matmul2(Conjg(Te),Transpose(Te),OnlyDiagonal) 
Forall(i2=1:3)  CTeTpTe(i2,i2) =  Real(CTeTpTe(i2,i2),dp) 
 CTuTpTu = Matmul2(Conjg(Tu),Transpose(Tu),OnlyDiagonal) 
Forall(i2=1:3)  CTuTpTu(i2,i2) =  Real(CTuTpTu(i2,i2),dp) 
 TdadjTd = Matmul2(Td,adjTd,OnlyDiagonal) 
 TeadjTe = Matmul2(Te,adjTe,OnlyDiagonal) 
 TuadjTu = Matmul2(Tu,adjTu,OnlyDiagonal) 
 md2YdadjYd = Matmul2(md2,YdadjYd,OnlyDiagonal) 
 me2YeadjYe = Matmul2(me2,YeadjYe,OnlyDiagonal) 
 ml2adjYeYe = Matmul2(ml2,adjYeYe,OnlyDiagonal) 
 mq2adjYdYd = Matmul2(mq2,adjYdYd,OnlyDiagonal) 
 mq2adjYuYu = Matmul2(mq2,adjYuYu,OnlyDiagonal) 
 mu2YuadjYu = Matmul2(mu2,YuadjYu,OnlyDiagonal) 
 Ydmq2adjYd = Matmul2(Yd,mq2adjYd,OnlyDiagonal) 
Forall(i2=1:3)  Ydmq2adjYd(i2,i2) =  Real(Ydmq2adjYd(i2,i2),dp) 
 YdadjYdmd2 = Matmul2(Yd,adjYdmd2,OnlyDiagonal) 
 YdadjYdYd = Matmul2(Yd,adjYdYd,OnlyDiagonal) 
 YdadjYdTd = Matmul2(Yd,adjYdTd,OnlyDiagonal) 
 YdadjYuYu = Matmul2(Yd,adjYuYu,OnlyDiagonal) 
 YdadjYuTu = Matmul2(Yd,adjYuTu,OnlyDiagonal) 
 Yeml2adjYe = Matmul2(Ye,ml2adjYe,OnlyDiagonal) 
Forall(i2=1:3)  Yeml2adjYe(i2,i2) =  Real(Yeml2adjYe(i2,i2),dp) 
 YeadjYeme2 = Matmul2(Ye,adjYeme2,OnlyDiagonal) 
 YeadjYeYe = Matmul2(Ye,adjYeYe,OnlyDiagonal) 
 YeadjYeTe = Matmul2(Ye,adjYeTe,OnlyDiagonal) 
 Yumq2adjYu = Matmul2(Yu,mq2adjYu,OnlyDiagonal) 
Forall(i2=1:3)  Yumq2adjYu(i2,i2) =  Real(Yumq2adjYu(i2,i2),dp) 
 YuadjYdYd = Matmul2(Yu,adjYdYd,OnlyDiagonal) 
 YuadjYdTd = Matmul2(Yu,adjYdTd,OnlyDiagonal) 
 YuadjYumu2 = Matmul2(Yu,adjYumu2,OnlyDiagonal) 
 YuadjYuYu = Matmul2(Yu,adjYuYu,OnlyDiagonal) 
 YuadjYuTu = Matmul2(Yu,adjYuTu,OnlyDiagonal) 
 adjYdmd2Yd = Matmul2(adjYd,md2Yd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdmd2Yd(i2,i2) =  Real(adjYdmd2Yd(i2,i2),dp) 
 adjYdYdmq2 = Matmul2(adjYd,Ydmq2,OnlyDiagonal) 
 adjYeme2Ye = Matmul2(adjYe,me2Ye,OnlyDiagonal) 
Forall(i2=1:3)  adjYeme2Ye(i2,i2) =  Real(adjYeme2Ye(i2,i2),dp) 
 adjYeYeml2 = Matmul2(adjYe,Yeml2,OnlyDiagonal) 
 adjYumu2Yu = Matmul2(adjYu,mu2Yu,OnlyDiagonal) 
Forall(i2=1:3)  adjYumu2Yu(i2,i2) =  Real(adjYumu2Yu(i2,i2),dp) 
 adjYuYumq2 = Matmul2(adjYu,Yumq2,OnlyDiagonal) 
 TdadjYdYd = Matmul2(Td,adjYdYd,OnlyDiagonal) 
 TdadjYuYu = Matmul2(Td,adjYuYu,OnlyDiagonal) 
 TeadjYeYe = Matmul2(Te,adjYeYe,OnlyDiagonal) 
 TuadjYdYd = Matmul2(Tu,adjYdYd,OnlyDiagonal) 
 TuadjYuYu = Matmul2(Tu,adjYuYu,OnlyDiagonal) 
 Trmd2 = Real(cTrace(md2),dp) 
 Trme2 = Real(cTrace(me2),dp) 
 Trml2 = Real(cTrace(ml2),dp) 
 Trmq2 = Real(cTrace(mq2),dp) 
 Trmu2 = Real(cTrace(mu2),dp) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 TradjYdTd = Real(cTrace(adjYdTd),dp) 
 TradjYeTe = Real(cTrace(adjYeTe),dp) 
 TradjYuTu = Real(cTrace(adjYuTu),dp) 
 TrCTdTpTd = Real(cTrace(CTdTpTd),dp) 
 TrCTeTpTe = Real(cTrace(CTeTpTe),dp) 
 TrCTuTpTu = Real(cTrace(CTuTpTu),dp) 
 Trmd2YdadjYd = Real(cTrace(md2YdadjYd),dp) 
 Trme2YeadjYe = Real(cTrace(me2YeadjYe),dp) 
 Trml2adjYeYe = Real(cTrace(ml2adjYeYe),dp) 
 Trmq2adjYdYd = Real(cTrace(mq2adjYdYd),dp) 
 Trmq2adjYuYu = Real(cTrace(mq2adjYuYu),dp) 
 Trmu2YuadjYu = Real(cTrace(mu2YuadjYu),dp) 
 sqrt3ov5 =Sqrt(3._dp/5._dp) 
 ooSqrt15 =1._dp/sqrt(15._dp) 
 g1p2 =g1**2 
 g1p3 =g1**3 
 g2p2 =g2**2 
 g2p3 =g2**3 
 g3p2 =g3**2 
 g3p3 =g3**3 
 sqrt15 =sqrt(15._dp) 
 g1p4 =g1**4 
 g2p4 =g2**4 
 g3p4 =g3**4 


If (TwoLoopRGE) Then 
 YdadjYu = Matmul2(Yd,adjYu,OnlyDiagonal) 
 YdadjTd = Matmul2(Yd,adjTd,OnlyDiagonal) 
 YdadjTu = Matmul2(Yd,adjTu,OnlyDiagonal) 
 YeadjTe = Matmul2(Ye,adjTe,OnlyDiagonal) 
 YuadjYd = Matmul2(Yu,adjYd,OnlyDiagonal) 
 YuadjTd = Matmul2(Yu,adjTd,OnlyDiagonal) 
 YuadjTu = Matmul2(Yu,adjTu,OnlyDiagonal) 
 adjYdCmd2 = Matmul2(adjYd,Conjg(md2),OnlyDiagonal) 
 adjYeCme2 = Matmul2(adjYe,Conjg(me2),OnlyDiagonal) 
 adjYuCmu2 = Matmul2(adjYu,Conjg(mu2),OnlyDiagonal) 
 adjTdYd = Matmul2(adjTd,Yd,OnlyDiagonal) 
 adjTeYe = Matmul2(adjTe,Ye,OnlyDiagonal) 
 adjTuYu = Matmul2(adjTu,Yu,OnlyDiagonal) 
 Cml2adjYe = Matmul2(Conjg(ml2),adjYe,OnlyDiagonal) 
 Cmq2adjYd = Matmul2(Conjg(mq2),adjYd,OnlyDiagonal) 
 Cmq2adjYu = Matmul2(Conjg(mq2),adjYu,OnlyDiagonal) 
 CTdTpYd = Matmul2(Conjg(Td),Transpose(Yd),OnlyDiagonal) 
 CTeTpYe = Matmul2(Conjg(Te),Transpose(Ye),OnlyDiagonal) 
 CTuTpYu = Matmul2(Conjg(Tu),Transpose(Yu),OnlyDiagonal) 
 TdadjYd = Matmul2(Td,adjYd,OnlyDiagonal) 
 TdadjYu = Matmul2(Td,adjYu,OnlyDiagonal) 
 TdadjTu = Matmul2(Td,adjTu,OnlyDiagonal) 
 TeadjYe = Matmul2(Te,adjYe,OnlyDiagonal) 
 TuadjYd = Matmul2(Tu,adjYd,OnlyDiagonal) 
 TuadjYu = Matmul2(Tu,adjYu,OnlyDiagonal) 
 TuadjTd = Matmul2(Tu,adjTd,OnlyDiagonal) 
 md2YdadjYu = Matmul2(md2,YdadjYu,OnlyDiagonal) 
 mu2YuadjYd = Matmul2(mu2,YuadjYd,OnlyDiagonal) 
 Ydmq2adjYu = Matmul2(Yd,mq2adjYu,OnlyDiagonal) 
 YdadjYdCmd2 = Matmul2(Yd,adjYdCmd2,OnlyDiagonal) 
 YdadjYumu2 = Matmul2(Yd,adjYumu2,OnlyDiagonal) 
 YdadjTdTd = Matmul2(Yd,adjTdTd,OnlyDiagonal) 
 YdCmq2adjYd = Matmul2(Yd,Cmq2adjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdCmq2adjYd(i2,i2) =  Real(YdCmq2adjYd(i2,i2),dp) 
 YeadjYeCme2 = Matmul2(Ye,adjYeCme2,OnlyDiagonal) 
 YeadjTeTe = Matmul2(Ye,adjTeTe,OnlyDiagonal) 
 YeCml2adjYe = Matmul2(Ye,Cml2adjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeCml2adjYe(i2,i2) =  Real(YeCml2adjYe(i2,i2),dp) 
 Yumq2adjYd = Matmul2(Yu,mq2adjYd,OnlyDiagonal) 
 YuadjYdmd2 = Matmul2(Yu,adjYdmd2,OnlyDiagonal) 
 YuadjYuCmu2 = Matmul2(Yu,adjYuCmu2,OnlyDiagonal) 
 YuadjTuTu = Matmul2(Yu,adjTuTu,OnlyDiagonal) 
 YuCmq2adjYu = Matmul2(Yu,Cmq2adjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuCmq2adjYu(i2,i2) =  Real(YuCmq2adjYu(i2,i2),dp) 
 adjYdYdadjYd = Matmul2(adjYd,YdadjYd,OnlyDiagonal) 
 adjYdYdadjYu = Matmul2(adjYd,YdadjYu,OnlyDiagonal) 
 adjYdYdadjTd = Matmul2(adjYd,YdadjTd,OnlyDiagonal) 
 adjYdYdadjTu = Matmul2(adjYd,YdadjTu,OnlyDiagonal) 
 adjYdTdadjYd = Matmul2(adjYd,TdadjYd,OnlyDiagonal) 
 adjYdTdadjYu = Matmul2(adjYd,TdadjYu,OnlyDiagonal) 
 adjYdTdadjTd = Matmul2(adjYd,TdadjTd,OnlyDiagonal) 
 adjYdTdadjTu = Matmul2(adjYd,TdadjTu,OnlyDiagonal) 
 adjYeYeadjYe = Matmul2(adjYe,YeadjYe,OnlyDiagonal) 
 adjYeYeadjTe = Matmul2(adjYe,YeadjTe,OnlyDiagonal) 
 adjYeTeadjYe = Matmul2(adjYe,TeadjYe,OnlyDiagonal) 
 adjYeTeadjTe = Matmul2(adjYe,TeadjTe,OnlyDiagonal) 
 adjYuYuadjYd = Matmul2(adjYu,YuadjYd,OnlyDiagonal) 
 adjYuYuadjYu = Matmul2(adjYu,YuadjYu,OnlyDiagonal) 
 adjYuYuadjTd = Matmul2(adjYu,YuadjTd,OnlyDiagonal) 
 adjYuYuadjTu = Matmul2(adjYu,YuadjTu,OnlyDiagonal) 
 adjYuTuadjYd = Matmul2(adjYu,TuadjYd,OnlyDiagonal) 
 adjYuTuadjYu = Matmul2(adjYu,TuadjYu,OnlyDiagonal) 
 adjYuTuadjTd = Matmul2(adjYu,TuadjTd,OnlyDiagonal) 
 adjYuTuadjTu = Matmul2(adjYu,TuadjTu,OnlyDiagonal) 
 adjTdYdadjYd = Matmul2(adjTd,YdadjYd,OnlyDiagonal) 
 adjTdYdadjYu = Matmul2(adjTd,YdadjYu,OnlyDiagonal) 
 adjTdTdadjYd = Matmul2(adjTd,TdadjYd,OnlyDiagonal) 
 adjTdTdadjYu = Matmul2(adjTd,TdadjYu,OnlyDiagonal) 
 adjTeYeadjYe = Matmul2(adjTe,YeadjYe,OnlyDiagonal) 
 adjTeTeadjYe = Matmul2(adjTe,TeadjYe,OnlyDiagonal) 
 adjTuYuadjYd = Matmul2(adjTu,YuadjYd,OnlyDiagonal) 
 adjTuYuadjYu = Matmul2(adjTu,YuadjYu,OnlyDiagonal) 
 adjTuTuadjYd = Matmul2(adjTu,TuadjYd,OnlyDiagonal) 
 adjTuTuadjYu = Matmul2(adjTu,TuadjYu,OnlyDiagonal) 
 TdadjTdYd = Matmul2(Td,adjTdYd,OnlyDiagonal) 
 TeadjTeYe = Matmul2(Te,adjTeYe,OnlyDiagonal) 
 TuadjTuYu = Matmul2(Tu,adjTuYu,OnlyDiagonal) 
 md2YdadjYdYd = Matmul2(md2,YdadjYdYd,OnlyDiagonal) 
 me2YeadjYeYe = Matmul2(me2,YeadjYeYe,OnlyDiagonal) 
 ml2adjYeYeadjYe = Matmul2(ml2,adjYeYeadjYe,OnlyDiagonal) 
 mq2adjYdYdadjYd = Matmul2(mq2,adjYdYdadjYd,OnlyDiagonal) 
 mq2adjYdYdadjYu = Matmul2(mq2,adjYdYdadjYu,OnlyDiagonal) 
 mq2adjYuYuadjYd = Matmul2(mq2,adjYuYuadjYd,OnlyDiagonal) 
 mq2adjYuYuadjYu = Matmul2(mq2,adjYuYuadjYu,OnlyDiagonal) 
 mu2YuadjYuYu = Matmul2(mu2,YuadjYuYu,OnlyDiagonal) 
 Ydmq2adjYdYd = Matmul2(Yd,mq2adjYdYd,OnlyDiagonal) 
 YdadjYdmd2Yd = Matmul2(Yd,adjYdmd2Yd,OnlyDiagonal) 
 YdadjYdYdmq2 = Matmul2(Yd,adjYdYdmq2,OnlyDiagonal) 
 YdadjYdYdadjYd = Matmul2(Yd,adjYdYdadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YdadjYdTdadjYd = Matmul2(Yd,adjYdTdadjYd,OnlyDiagonal) 
 YdadjYdTdadjTd = Matmul2(Yd,adjYdTdadjTd,OnlyDiagonal) 
 YdadjYuYuadjYd = Matmul2(Yd,adjYuYuadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYd(i2,i2),dp) 
 YdadjYuTuadjYd = Matmul2(Yd,adjYuTuadjYd,OnlyDiagonal) 
 YdadjYuTuadjTd = Matmul2(Yd,adjYuTuadjTd,OnlyDiagonal) 
 YdadjTdTdadjYd = Matmul2(Yd,adjTdTdadjYd,OnlyDiagonal) 
 YdadjTuTuadjYd = Matmul2(Yd,adjTuTuadjYd,OnlyDiagonal) 
 Yeml2adjYeYe = Matmul2(Ye,ml2adjYeYe,OnlyDiagonal) 
 YeadjYeme2Ye = Matmul2(Ye,adjYeme2Ye,OnlyDiagonal) 
 YeadjYeYeml2 = Matmul2(Ye,adjYeYeml2,OnlyDiagonal) 
 YeadjYeYeadjYe = Matmul2(Ye,adjYeYeadjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YeadjYeTeadjYe = Matmul2(Ye,adjYeTeadjYe,OnlyDiagonal) 
 YeadjYeTeadjTe = Matmul2(Ye,adjYeTeadjTe,OnlyDiagonal) 
 YeadjTeTeadjYe = Matmul2(Ye,adjTeTeadjYe,OnlyDiagonal) 
 Yumq2adjYuYu = Matmul2(Yu,mq2adjYuYu,OnlyDiagonal) 
 YuadjYdYdadjYu = Matmul2(Yu,adjYdYdadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYdYdadjYu(i2,i2) =  Real(YuadjYdYdadjYu(i2,i2),dp) 
 YuadjYdTdadjYu = Matmul2(Yu,adjYdTdadjYu,OnlyDiagonal) 
 YuadjYdTdadjTu = Matmul2(Yu,adjYdTdadjTu,OnlyDiagonal) 
 YuadjYumu2Yu = Matmul2(Yu,adjYumu2Yu,OnlyDiagonal) 
 YuadjYuYumq2 = Matmul2(Yu,adjYuYumq2,OnlyDiagonal) 
 YuadjYuYuadjYu = Matmul2(Yu,adjYuYuadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 YuadjYuTuadjYu = Matmul2(Yu,adjYuTuadjYu,OnlyDiagonal) 
 YuadjYuTuadjTu = Matmul2(Yu,adjYuTuadjTu,OnlyDiagonal) 
 YuadjTdTdadjYu = Matmul2(Yu,adjTdTdadjYu,OnlyDiagonal) 
 YuadjTuTuadjYu = Matmul2(Yu,adjTuTuadjYu,OnlyDiagonal) 
 adjYdmd2YdadjYd = Matmul2(adjYd,md2YdadjYd,OnlyDiagonal) 
 adjYdmd2YdadjYu = Matmul2(adjYd,md2YdadjYu,OnlyDiagonal) 
 adjYdYdmq2adjYd = Matmul2(adjYd,Ydmq2adjYd,OnlyDiagonal) 
 adjYdYdmq2adjYu = Matmul2(adjYd,Ydmq2adjYu,OnlyDiagonal) 
 adjYdYdadjYdmd2 = Matmul2(adjYd,YdadjYdmd2,OnlyDiagonal) 
 adjYdYdadjYdYd = Matmul2(adjYd,YdadjYdYd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYdadjYdYd(i2,i2) =  Real(adjYdYdadjYdYd(i2,i2),dp) 
 adjYdYdadjYdTd = Matmul2(adjYd,YdadjYdTd,OnlyDiagonal) 
 adjYdYdadjYumu2 = Matmul2(adjYd,YdadjYumu2,OnlyDiagonal) 
 adjYdYdadjYuYu = Matmul2(adjYd,YdadjYuYu,OnlyDiagonal) 
 adjYdYdadjYuTu = Matmul2(adjYd,YdadjYuTu,OnlyDiagonal) 
 adjYdYdadjTdTd = Matmul2(adjYd,YdadjTdTd,OnlyDiagonal) 
 adjYdTdadjYdYd = Matmul2(adjYd,TdadjYdYd,OnlyDiagonal) 
 adjYdTdadjYuYu = Matmul2(adjYd,TdadjYuYu,OnlyDiagonal) 
 adjYdTdadjTdYd = Matmul2(adjYd,TdadjTdYd,OnlyDiagonal) 
 adjYeme2YeadjYe = Matmul2(adjYe,me2YeadjYe,OnlyDiagonal) 
 adjYeYeml2adjYe = Matmul2(adjYe,Yeml2adjYe,OnlyDiagonal) 
 adjYeYeadjYeme2 = Matmul2(adjYe,YeadjYeme2,OnlyDiagonal) 
 adjYeYeadjYeYe = Matmul2(adjYe,YeadjYeYe,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYeadjYeYe(i2,i2) =  Real(adjYeYeadjYeYe(i2,i2),dp) 
 adjYeYeadjYeTe = Matmul2(adjYe,YeadjYeTe,OnlyDiagonal) 
 adjYeYeadjTeTe = Matmul2(adjYe,YeadjTeTe,OnlyDiagonal) 
 adjYeTeadjYeYe = Matmul2(adjYe,TeadjYeYe,OnlyDiagonal) 
 adjYeTeadjTeYe = Matmul2(adjYe,TeadjTeYe,OnlyDiagonal) 
 adjYumu2YuadjYd = Matmul2(adjYu,mu2YuadjYd,OnlyDiagonal) 
 adjYumu2YuadjYu = Matmul2(adjYu,mu2YuadjYu,OnlyDiagonal) 
 adjYuYumq2adjYd = Matmul2(adjYu,Yumq2adjYd,OnlyDiagonal) 
 adjYuYumq2adjYu = Matmul2(adjYu,Yumq2adjYu,OnlyDiagonal) 
 adjYuYuadjYdmd2 = Matmul2(adjYu,YuadjYdmd2,OnlyDiagonal) 
 adjYuYuadjYdYd = Matmul2(adjYu,YuadjYdYd,OnlyDiagonal) 
 adjYuYuadjYdTd = Matmul2(adjYu,YuadjYdTd,OnlyDiagonal) 
 adjYuYuadjYumu2 = Matmul2(adjYu,YuadjYumu2,OnlyDiagonal) 
 adjYuYuadjYuYu = Matmul2(adjYu,YuadjYuYu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYuadjYuYu(i2,i2) =  Real(adjYuYuadjYuYu(i2,i2),dp) 
 adjYuYuadjYuTu = Matmul2(adjYu,YuadjYuTu,OnlyDiagonal) 
 adjYuYuadjTuTu = Matmul2(adjYu,YuadjTuTu,OnlyDiagonal) 
 adjYuTuadjYdYd = Matmul2(adjYu,TuadjYdYd,OnlyDiagonal) 
 adjYuTuadjYuYu = Matmul2(adjYu,TuadjYuYu,OnlyDiagonal) 
 adjYuTuadjTuYu = Matmul2(adjYu,TuadjTuYu,OnlyDiagonal) 
 adjTdYdadjYdTd = Matmul2(adjTd,YdadjYdTd,OnlyDiagonal) 
 adjTdTdadjYdYd = Matmul2(adjTd,TdadjYdYd,OnlyDiagonal) 
 adjTeYeadjYeTe = Matmul2(adjTe,YeadjYeTe,OnlyDiagonal) 
 adjTeTeadjYeYe = Matmul2(adjTe,TeadjYeYe,OnlyDiagonal) 
 adjTuYuadjYuTu = Matmul2(adjTu,YuadjYuTu,OnlyDiagonal) 
 adjTuTuadjYuYu = Matmul2(adjTu,TuadjYuYu,OnlyDiagonal) 
 TdadjYdYdadjTd = Matmul2(Td,adjYdYdadjTd,OnlyDiagonal) 
 TdadjYuYuadjTd = Matmul2(Td,adjYuYuadjTd,OnlyDiagonal) 
 TdadjTdYdadjYd = Matmul2(Td,adjTdYdadjYd,OnlyDiagonal) 
 TdadjTuYuadjYd = Matmul2(Td,adjTuYuadjYd,OnlyDiagonal) 
 TeadjYeYeadjTe = Matmul2(Te,adjYeYeadjTe,OnlyDiagonal) 
 TeadjTeYeadjYe = Matmul2(Te,adjTeYeadjYe,OnlyDiagonal) 
 TuadjYdYdadjTu = Matmul2(Tu,adjYdYdadjTu,OnlyDiagonal) 
 TuadjYuYuadjTu = Matmul2(Tu,adjYuYuadjTu,OnlyDiagonal) 
 TuadjTdYdadjYu = Matmul2(Tu,adjTdYdadjYu,OnlyDiagonal) 
 TuadjTuYuadjYu = Matmul2(Tu,adjTuYuadjYu,OnlyDiagonal) 
 md2YdadjYdYdadjYd = Matmul2(md2,YdadjYdYdadjYd,OnlyDiagonal) 
 md2YdadjYuYuadjYd = Matmul2(md2,YdadjYuYuadjYd,OnlyDiagonal) 
 me2YeadjYeYeadjYe = Matmul2(me2,YeadjYeYeadjYe,OnlyDiagonal) 
 ml2adjYeYeadjYeYe = Matmul2(ml2,adjYeYeadjYeYe,OnlyDiagonal) 
 mq2adjYdYdadjYdYd = Matmul2(mq2,adjYdYdadjYdYd,OnlyDiagonal) 
 mq2adjYdYdadjYuYu = Matmul2(mq2,adjYdYdadjYuYu,OnlyDiagonal) 
 mq2adjYuYuadjYdYd = Matmul2(mq2,adjYuYuadjYdYd,OnlyDiagonal) 
 mq2adjYuYuadjYuYu = Matmul2(mq2,adjYuYuadjYuYu,OnlyDiagonal) 
 mu2YuadjYdYdadjYu = Matmul2(mu2,YuadjYdYdadjYu,OnlyDiagonal) 
 mu2YuadjYuYuadjYu = Matmul2(mu2,YuadjYuYuadjYu,OnlyDiagonal) 
 Ydmq2adjYdYdadjYd = Matmul2(Yd,mq2adjYdYdadjYd,OnlyDiagonal) 
 Ydmq2adjYuYuadjYd = Matmul2(Yd,mq2adjYuYuadjYd,OnlyDiagonal) 
 YdadjYdmd2YdadjYd = Matmul2(Yd,adjYdmd2YdadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYdmd2YdadjYd(i2,i2) =  Real(YdadjYdmd2YdadjYd(i2,i2),dp) 
 YdadjYdYdmq2adjYd = Matmul2(Yd,adjYdYdmq2adjYd,OnlyDiagonal) 
 YdadjYdYdadjYdmd2 = Matmul2(Yd,adjYdYdadjYdmd2,OnlyDiagonal) 
 YdadjYdYdadjYdYd = Matmul2(Yd,adjYdYdadjYdYd,OnlyDiagonal) 
 YdadjYdYdadjYdTd = Matmul2(Yd,adjYdYdadjYdTd,OnlyDiagonal) 
 YdadjYdTdadjYdYd = Matmul2(Yd,adjYdTdadjYdYd,OnlyDiagonal) 
 YdadjYumu2YuadjYd = Matmul2(Yd,adjYumu2YuadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYumu2YuadjYd(i2,i2) =  Real(YdadjYumu2YuadjYd(i2,i2),dp) 
 YdadjYuYumq2adjYd = Matmul2(Yd,adjYuYumq2adjYd,OnlyDiagonal) 
 YdadjYuYuadjYdmd2 = Matmul2(Yd,adjYuYuadjYdmd2,OnlyDiagonal) 
 YdadjYuYuadjYdYd = Matmul2(Yd,adjYuYuadjYdYd,OnlyDiagonal) 
 YdadjYuYuadjYdTd = Matmul2(Yd,adjYuYuadjYdTd,OnlyDiagonal) 
 YdadjYuYuadjYuYu = Matmul2(Yd,adjYuYuadjYuYu,OnlyDiagonal) 
 YdadjYuYuadjYuTu = Matmul2(Yd,adjYuYuadjYuTu,OnlyDiagonal) 
 YdadjYuTuadjYdYd = Matmul2(Yd,adjYuTuadjYdYd,OnlyDiagonal) 
 YdadjYuTuadjYuYu = Matmul2(Yd,adjYuTuadjYuYu,OnlyDiagonal) 
 Yeml2adjYeYeadjYe = Matmul2(Ye,ml2adjYeYeadjYe,OnlyDiagonal) 
 YeadjYeme2YeadjYe = Matmul2(Ye,adjYeme2YeadjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYeme2YeadjYe(i2,i2) =  Real(YeadjYeme2YeadjYe(i2,i2),dp) 
 YeadjYeYeml2adjYe = Matmul2(Ye,adjYeYeml2adjYe,OnlyDiagonal) 
 YeadjYeYeadjYeme2 = Matmul2(Ye,adjYeYeadjYeme2,OnlyDiagonal) 
 YeadjYeYeadjYeYe = Matmul2(Ye,adjYeYeadjYeYe,OnlyDiagonal) 
 YeadjYeYeadjYeTe = Matmul2(Ye,adjYeYeadjYeTe,OnlyDiagonal) 
 YeadjYeTeadjYeYe = Matmul2(Ye,adjYeTeadjYeYe,OnlyDiagonal) 
 Yumq2adjYdYdadjYu = Matmul2(Yu,mq2adjYdYdadjYu,OnlyDiagonal) 
 Yumq2adjYuYuadjYu = Matmul2(Yu,mq2adjYuYuadjYu,OnlyDiagonal) 
 YuadjYdmd2YdadjYu = Matmul2(Yu,adjYdmd2YdadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYdmd2YdadjYu(i2,i2) =  Real(YuadjYdmd2YdadjYu(i2,i2),dp) 
 YuadjYdYdmq2adjYu = Matmul2(Yu,adjYdYdmq2adjYu,OnlyDiagonal) 
 YuadjYdYdadjYdYd = Matmul2(Yu,adjYdYdadjYdYd,OnlyDiagonal) 
 YuadjYdYdadjYdTd = Matmul2(Yu,adjYdYdadjYdTd,OnlyDiagonal) 
 YuadjYdYdadjYumu2 = Matmul2(Yu,adjYdYdadjYumu2,OnlyDiagonal) 
 YuadjYdYdadjYuYu = Matmul2(Yu,adjYdYdadjYuYu,OnlyDiagonal) 
 YuadjYdYdadjYuTu = Matmul2(Yu,adjYdYdadjYuTu,OnlyDiagonal) 
 YuadjYdTdadjYdYd = Matmul2(Yu,adjYdTdadjYdYd,OnlyDiagonal) 
 YuadjYdTdadjYuYu = Matmul2(Yu,adjYdTdadjYuYu,OnlyDiagonal) 
 YuadjYumu2YuadjYu = Matmul2(Yu,adjYumu2YuadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYumu2YuadjYu(i2,i2) =  Real(YuadjYumu2YuadjYu(i2,i2),dp) 
 YuadjYuYumq2adjYu = Matmul2(Yu,adjYuYumq2adjYu,OnlyDiagonal) 
 YuadjYuYuadjYumu2 = Matmul2(Yu,adjYuYuadjYumu2,OnlyDiagonal) 
 YuadjYuYuadjYuYu = Matmul2(Yu,adjYuYuadjYuYu,OnlyDiagonal) 
 YuadjYuYuadjYuTu = Matmul2(Yu,adjYuYuadjYuTu,OnlyDiagonal) 
 YuadjYuTuadjYuYu = Matmul2(Yu,adjYuTuadjYuYu,OnlyDiagonal) 
 adjYdmd2YdadjYdYd = Matmul2(adjYd,md2YdadjYdYd,OnlyDiagonal) 
 adjYdYdmq2adjYdYd = Matmul2(adjYd,Ydmq2adjYdYd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYdmq2adjYdYd(i2,i2) =  Real(adjYdYdmq2adjYdYd(i2,i2),dp) 
 adjYdYdadjYdmd2Yd = Matmul2(adjYd,YdadjYdmd2Yd,OnlyDiagonal) 
 adjYdYdadjYdYdmq2 = Matmul2(adjYd,YdadjYdYdmq2,OnlyDiagonal) 
 adjYeme2YeadjYeYe = Matmul2(adjYe,me2YeadjYeYe,OnlyDiagonal) 
 adjYeYeml2adjYeYe = Matmul2(adjYe,Yeml2adjYeYe,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYeml2adjYeYe(i2,i2) =  Real(adjYeYeml2adjYeYe(i2,i2),dp) 
 adjYeYeadjYeme2Ye = Matmul2(adjYe,YeadjYeme2Ye,OnlyDiagonal) 
 adjYeYeadjYeYeml2 = Matmul2(adjYe,YeadjYeYeml2,OnlyDiagonal) 
 adjYumu2YuadjYuYu = Matmul2(adjYu,mu2YuadjYuYu,OnlyDiagonal) 
 adjYuYumq2adjYuYu = Matmul2(adjYu,Yumq2adjYuYu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYumq2adjYuYu(i2,i2) =  Real(adjYuYumq2adjYuYu(i2,i2),dp) 
 adjYuYuadjYumu2Yu = Matmul2(adjYu,YuadjYumu2Yu,OnlyDiagonal) 
 adjYuYuadjYuYumq2 = Matmul2(adjYu,YuadjYuYumq2,OnlyDiagonal) 
 TdadjYdYdadjYdYd = Matmul2(Td,adjYdYdadjYdYd,OnlyDiagonal) 
 TdadjYuYuadjYdYd = Matmul2(Td,adjYuYuadjYdYd,OnlyDiagonal) 
 TdadjYuYuadjYuYu = Matmul2(Td,adjYuYuadjYuYu,OnlyDiagonal) 
 TeadjYeYeadjYeYe = Matmul2(Te,adjYeYeadjYeYe,OnlyDiagonal) 
 TuadjYdYdadjYdYd = Matmul2(Tu,adjYdYdadjYdYd,OnlyDiagonal) 
 TuadjYdYdadjYuYu = Matmul2(Tu,adjYdYdadjYuYu,OnlyDiagonal) 
 TuadjYuYuadjYuYu = Matmul2(Tu,adjYuYuadjYuYu,OnlyDiagonal) 
 TrCTdTpYd = cTrace(CTdTpYd) 
 TrCTeTpYe = cTrace(CTeTpYe) 
 TrCTuTpYu = cTrace(CTuTpYu) 
 TrYdadjYdCmd2 = cTrace(YdadjYdCmd2) 
 TrYdCmq2adjYd = cTrace(YdCmq2adjYd) 
 TrYeadjYeCme2 = cTrace(YeadjYeCme2) 
 TrYeCml2adjYe = cTrace(YeCml2adjYe) 
 TrYuadjYuCmu2 = cTrace(YuadjYuCmu2) 
 TrYuCmq2adjYu = cTrace(YuCmq2adjYu) 
 TrYdadjYdYdadjYd = cTrace(YdadjYdYdadjYd) 
 TrYdadjYdTdadjYd = cTrace(YdadjYdTdadjYd) 
 TrYdadjYdTdadjTd = cTrace(YdadjYdTdadjTd) 
 TrYdadjYuYuadjYd = cTrace(YdadjYuYuadjYd) 
 TrYdadjYuTuadjYd = cTrace(YdadjYuTuadjYd) 
 TrYdadjYuTuadjTd = cTrace(YdadjYuTuadjTd) 
 TrYdadjTdTdadjYd = cTrace(YdadjTdTdadjYd) 
 TrYdadjTuTuadjYd = cTrace(YdadjTuTuadjYd) 
 TrYeadjYeYeadjYe = cTrace(YeadjYeYeadjYe) 
 TrYeadjYeTeadjYe = cTrace(YeadjYeTeadjYe) 
 TrYeadjYeTeadjTe = cTrace(YeadjYeTeadjTe) 
 TrYeadjTeTeadjYe = cTrace(YeadjTeTeadjYe) 
 TrYuadjYdTdadjYu = cTrace(YuadjYdTdadjYu) 
 TrYuadjYdTdadjTu = cTrace(YuadjYdTdadjTu) 
 TrYuadjYuYuadjYu = cTrace(YuadjYuYuadjYu) 
 TrYuadjYuTuadjYu = cTrace(YuadjYuTuadjYu) 
 TrYuadjYuTuadjTu = cTrace(YuadjYuTuadjTu) 
 TrYuadjTdTdadjYu = cTrace(YuadjTdTdadjYu) 
 TrYuadjTuTuadjYu = cTrace(YuadjTuTuadjYu) 
 Trmd2YdadjYdYdadjYd = cTrace(md2YdadjYdYdadjYd) 
 Trmd2YdadjYuYuadjYd = cTrace(md2YdadjYuYuadjYd) 
 Trme2YeadjYeYeadjYe = cTrace(me2YeadjYeYeadjYe) 
 Trml2adjYeYeadjYeYe = cTrace(ml2adjYeYeadjYeYe) 
 Trmq2adjYdYdadjYdYd = cTrace(mq2adjYdYdadjYdYd) 
 Trmq2adjYdYdadjYuYu = cTrace(mq2adjYdYdadjYuYu) 
 Trmq2adjYuYuadjYdYd = cTrace(mq2adjYuYuadjYdYd) 
 Trmq2adjYuYuadjYuYu = cTrace(mq2adjYuYuadjYuYu) 
 Trmu2YuadjYdYdadjYu = cTrace(mu2YuadjYdYdadjYu) 
 Trmu2YuadjYuYuadjYu = cTrace(mu2YuadjYuYuadjYu) 
 sqrt15 =sqrt(15._dp) 
 g1p4 =g1**4 
 g2p4 =g2**4 
 g3p4 =g3**4 
End If 
 
 
Tr1(1) = g1*sqrt3ov5*(-1._dp*(mHd2) + mHu2 + Trmd2 + Trme2 - Trml2 + Trmq2 -          & 
&  2._dp*(Trmu2))

If (TwoLoopRGE) Then 
Tr2U1(1, 1) = (g1p2*(3._dp*(mHd2) + 3._dp*(mHu2) + 2._dp*(Trmd2) + 6._dp*(Trme2)      & 
&  + 3._dp*(Trml2) + Trmq2 + 8._dp*(Trmu2)))/10._dp

Tr3(1) = (g1*ooSqrt15*(-9*g1p2*mHd2 - 45*g2p2*mHd2 + 9*g1p2*mHu2 + 45*g2p2*mHu2 +     & 
&  4*(g1p2 + 20._dp*(g3p2))*Trmd2 + 36*g1p2*Trme2 - 9*g1p2*Trml2 - 45*g2p2*Trml2 +       & 
&  g1p2*Trmq2 + 45*g2p2*Trmq2 + 80*g3p2*Trmq2 - 32*g1p2*Trmu2 - 160*g3p2*Trmu2 +         & 
&  90*mHd2*TrYdadjYd - 60._dp*(TrYdadjYdCmd2) - 30._dp*(TrYdCmq2adjYd) + 30*mHd2*TrYeadjYe -& 
&  60._dp*(TrYeadjYeCme2) + 30._dp*(TrYeCml2adjYe) - 90*mHu2*TrYuadjYu + 120._dp*(TrYuadjYuCmu2)& 
&  - 30._dp*(TrYuCmq2adjYu)))/20._dp

Tr2(2) = (mHd2 + mHu2 + Trml2 + 3._dp*(Trmq2))/2._dp

Tr2(3) = (Trmd2 + 2._dp*(Trmq2) + Trmu2)/2._dp

End If 
 
 
!-------------------- 
! g1 
!-------------------- 
 
betag11  = 33._dp*(g1p3)/5._dp

 
 
If (TwoLoopRGE) Then 
betag12 = (g1p3*(199._dp*(g1p2) + 135._dp*(g2p2) + 440._dp*(g3p2) - 70._dp*(TrYdadjYd) -        & 
&  90._dp*(TrYeadjYe) - 130._dp*(TrYuadjYu)))/25._dp

 
Dg1 = oo16pi2*( betag11 + oo16pi2 * betag12 ) 

 
Else 
Dg1 = oo16pi2* betag11 
End If 
 
 
!-------------------- 
! g2 
!-------------------- 
 
betag21  = g2p3

 
 
If (TwoLoopRGE) Then 
betag22 = (g2p3*(9._dp*(g1p2) + 125._dp*(g2p2) + 120._dp*(g3p2) - 30._dp*(TrYdadjYd) -          & 
&  10._dp*(TrYeadjYe) - 30._dp*(TrYuadjYu)))/5._dp

 
Dg2 = oo16pi2*( betag21 + oo16pi2 * betag22 ) 

 
Else 
Dg2 = oo16pi2* betag21 
End If 
 
 
!-------------------- 
! g3 
!-------------------- 
 
betag31  = -3._dp*(g3p3)

 
 
If (TwoLoopRGE) Then 
betag32 = (g3p3*(11._dp*(g1p2) + 45._dp*(g2p2) + 70._dp*(g3p2) - 20._dp*(TrYdadjYd) -           & 
&  20._dp*(TrYuadjYu)))/5._dp

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 ) 

 
Else 
Dg3 = oo16pi2* betag31 
End If 
 
 
!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-7._dp*(g1p2)/15._dp - 3._dp*(g2p2) - 16._dp*(g3p2)/3._dp +               & 
&  3._dp*(TrYdadjYd) + TrYeadjYe)*Yd + 3._dp*(YdadjYdYd) + YdadjYuYu

 
 
If (TwoLoopRGE) Then 
betaYd2 = (287._dp*(g1p4)/90._dp + g1p2*g2p2 + 15._dp*(g2p4)/2._dp + (8*g1p2*g3p2)/9._dp +      & 
&  8*g2p2*g3p2 - 16._dp*(g3p4)/9._dp - (2*(g1p2 - 40._dp*(g3p2))*TrYdadjYd)/5._dp -      & 
&  9._dp*(TrYdadjYdYdadjYd) - 3._dp*(TrYdadjYuYuadjYd) + (6*g1p2*TrYeadjYe)/5._dp -      & 
&  3._dp*(TrYeadjYeYeadjYe))*Yd + (4._dp*(g1p2)/5._dp + 6._dp*(g2p2) - 9._dp*(TrYdadjYd) -& 
&  3._dp*(TrYeadjYe))*YdadjYdYd - 4._dp*(YdadjYdYdadjYdYd) + (4*g1p2*YdadjYuYu)/5._dp -  & 
&  3*TrYuadjYu*YdadjYuYu - 2._dp*(YdadjYuYuadjYdYd) - 2._dp*(YdadjYuYuadjYuYu)

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = (-9._dp*(g1p2)/5._dp - 3._dp*(g2p2) + 3._dp*(TrYdadjYd) + TrYeadjYe)       & 
& *Ye + 3._dp*(YeadjYeYe)

 
 
If (TwoLoopRGE) Then 
betaYe2 = ((-4*(g1p2 - 40._dp*(g3p2))*TrYdadjYd + 3*(45._dp*(g1p4) + 6*g1p2*g2p2 +              & 
&  25._dp*(g2p4) - 30._dp*(TrYdadjYdYdadjYd) - 10._dp*(TrYdadjYuYuadjYd) +               & 
&  4*g1p2*TrYeadjYe - 10._dp*(TrYeadjYeYeadjYe)))*Ye)/10._dp + (6._dp*(g2p2) -           & 
&  9._dp*(TrYdadjYd) - 3._dp*(TrYeadjYe))*YeadjYeYe - 4._dp*(YeadjYeYeadjYeYe)

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = -((13._dp*(g1p2) + 45._dp*(g2p2) + 80._dp*(g3p2) - 45._dp*(TrYuadjYu))     & 
& *Yu)/15._dp + YuadjYdYd + 3._dp*(YuadjYuYu)

 
 
If (TwoLoopRGE) Then 
betaYu2 = (2743._dp*(g1p4)/450._dp + g1p2*g2p2 + 15._dp*(g2p4)/2._dp + (136*g1p2*g3p2)/45._dp + & 
&  8*g2p2*g3p2 - 16._dp*(g3p4)/9._dp - 3._dp*(TrYdadjYuYuadjYd) + (4*(g1p2 +             & 
&  20._dp*(g3p2))*TrYuadjYu)/5._dp - 9._dp*(TrYuadjYuYuadjYu))*Yu + (2._dp*(g1p2)/5._dp -& 
&  3._dp*(TrYdadjYd) - TrYeadjYe)*YuadjYdYd - 2._dp*(YuadjYdYdadjYdYd) - 2._dp*(YuadjYdYdadjYuYu) +& 
&  (2*g1p2*YuadjYuYu)/5._dp + 6*g2p2*YuadjYuYu - 9*TrYuadjYu*YuadjYuYu - 4._dp*(YuadjYuYuadjYuYu)

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! Mu 
!-------------------- 
 
betaMu1  = 3*TrYdadjYd*Mu + TrYeadjYe*Mu - (3*(g1p2 + 5._dp*(g2p2) - 5._dp*(TrYuadjYu))& 
& *Mu)/5._dp

 
 
If (TwoLoopRGE) Then 
betaMu2 = ((207._dp*(g1p4) + 90*g1p2*g2p2 + 375._dp*(g2p4) - 20*(g1p2 - 40._dp*(g3p2))*TrYdadjYd -& 
&  450._dp*(TrYdadjYdYdadjYd) - 300._dp*(TrYdadjYuYuadjYd) + 60*g1p2*TrYeadjYe -         & 
&  150._dp*(TrYeadjYeYeadjYe) + 40*g1p2*TrYuadjYu + 800*g3p2*TrYuadjYu - 450._dp*(TrYuadjYuYuadjYu))*Mu)/50._dp

 
DMu = oo16pi2*( betaMu1 + oo16pi2 * betaMu2 ) 

 
Else 
DMu = oo16pi2* betaMu1 
End If 
 
 
Call Chop(DMu) 

!-------------------- 
! Td 
!-------------------- 
 
betaTd1  = 5._dp*(TdadjYdYd) + TdadjYuYu + ((14*g1p2*M1)/15._dp + (32*g3p2*M3)        & 
& /3._dp + 6*g2p2*M2 + 6._dp*(TradjYdTd) + 2._dp*(TradjYeTe))*Yd + 4._dp*(YdadjYdTd)     & 
&  + 2._dp*(YdadjYuTu) - (7*g1p2*Td)/15._dp - 3*g2p2*Td - (16*g3p2*Td)/3._dp +           & 
&  3*TrYdadjYd*Td + TrYeadjYe*Td

 
 
If (TwoLoopRGE) Then 
betaTd2 = (6*g1p2*TdadjYdYd)/5._dp + 12*g2p2*TdadjYdYd - 6._dp*(TdadjYdYdadjYdYd) +             & 
&  (4*g1p2*TdadjYuYu)/5._dp - 4._dp*(TdadjYuYuadjYdYd) - 2._dp*(TdadjYuYuadjYuYu) -      & 
&  15*TdadjYdYd*TrYdadjYd - 5*TdadjYdYd*TrYeadjYe - 3*TdadjYuYu*TrYuadjYu -              & 
&  (2*(287*g1p4*M1 + 45*g1p2*g2p2*M1 + 40*g1p2*g3p2*M1 + 40*g1p2*g3p2*M3 +               & 
&  360*g2p2*g3p2*M3 - 160*g3p4*M3 + 45*g1p2*g2p2*M2 + 675*g2p4*M2 + 360*g2p2*g3p2*M2 +   & 
&  18*g1p2*TradjYdTd - 720*g3p2*TradjYdTd - 54*g1p2*TradjYeTe - 18*(g1p2*M1 -            & 
&  40*g3p2*M3)*TrYdadjYd + 810._dp*(TrYdadjYdTdadjYd) + 135._dp*(TrYdadjYuTuadjYd) +     & 
&  54*g1p2*M1*TrYeadjYe + 270._dp*(TrYeadjYeTeadjYe) + 135._dp*(TrYuadjYdTdadjYu))*Yd)/45._dp +& 
&  (6*g1p2*YdadjYdTd)/5._dp + 6*g2p2*YdadjYdTd - 12*TrYdadjYd*YdadjYdTd - 4*TrYeadjYe*YdadjYdTd -& 
&  8._dp*(YdadjYdTdadjYdYd) - (2*(4*g1p2*M1 + 30*g2p2*M2 + 45._dp*(TradjYdTd) +          & 
&  15._dp*(TradjYeTe))*YdadjYdYd)/5._dp - 6._dp*(YdadjYdYdadjYdTd) + (8*g1p2*YdadjYuTu)/5._dp -& 
&  6*TrYuadjYu*YdadjYuTu - 4._dp*(YdadjYuTuadjYdYd) - 4._dp*(YdadjYuTuadjYuYu) -         & 
&  (8*g1p2*M1*YdadjYuYu)/5._dp - 6*TradjYuTu*YdadjYuYu - 2._dp*(YdadjYuYuadjYdTd) -      & 
&  4._dp*(YdadjYuYuadjYuTu) + (287*g1p4*Td)/90._dp + g1p2*g2p2*Td + (15*g2p4*Td)/2._dp + & 
&  (8*g1p2*g3p2*Td)/9._dp + 8*g2p2*g3p2*Td - (16*g3p4*Td)/9._dp - (2*g1p2*TrYdadjYd*Td)/5._dp +& 
&  16*g3p2*TrYdadjYd*Td - 9*TrYdadjYdYdadjYd*Td - 3*TrYdadjYuYuadjYd*Td + (6*g1p2*TrYeadjYe*Td)/5._dp -& 
&  3*TrYeadjYeYeadjYe*Td

 
DTd = oo16pi2*( betaTd1 + oo16pi2 * betaTd2 ) 

 
Else 
DTd = oo16pi2* betaTd1 
End If 
 
 
Call Chop(DTd) 

!-------------------- 
! Te 
!-------------------- 
 
betaTe1  = 5._dp*(TeadjYeYe) + ((18*g1p2*M1)/5._dp + 6*g2p2*M2 + 6._dp*(TradjYdTd)    & 
&  + 2._dp*(TradjYeTe))*Ye + 4._dp*(YeadjYeTe) - (9*g1p2*Te)/5._dp - 3*g2p2*Te +         & 
&  3*TrYdadjYd*Te + TrYeadjYe*Te

 
 
If (TwoLoopRGE) Then 
betaTe2 = (-6*g1p2*TeadjYeYe)/5._dp + 12*g2p2*TeadjYeYe - 6._dp*(TeadjYeYeadjYeYe) -            & 
&  15*TeadjYeYe*TrYdadjYd - 5*TeadjYeYe*TrYeadjYe - (2*(135*g1p4*M1 + 9*g1p2*g2p2*M1 +   & 
&  9*g1p2*g2p2*M2 + 75*g2p4*M2 + 2*g1p2*TradjYdTd - 80*g3p2*TradjYdTd - 6*g1p2*TradjYeTe +& 
&  (-2*g1p2*M1 + 80*g3p2*M3)*TrYdadjYd + 90._dp*(TrYdadjYdTdadjYd) + 15._dp*(TrYdadjYuTuadjYd) +& 
&  6*g1p2*M1*TrYeadjYe + 30._dp*(TrYeadjYeTeadjYe) + 15._dp*(TrYuadjYdTdadjYu))*Ye)/5._dp +& 
&  (6*g1p2*YeadjYeTe)/5._dp + 6*g2p2*YeadjYeTe - 12*TrYdadjYd*YeadjYeTe - 4*TrYeadjYe*YeadjYeTe -& 
&  8._dp*(YeadjYeTeadjYeYe) - 6*(2*g2p2*M2 + 3._dp*(TradjYdTd) + TradjYeTe)*YeadjYeYe -  & 
&  6._dp*(YeadjYeYeadjYeTe) + (27*g1p4*Te)/2._dp + (9*g1p2*g2p2*Te)/5._dp +              & 
&  (15*g2p4*Te)/2._dp - (2*g1p2*TrYdadjYd*Te)/5._dp + 16*g3p2*TrYdadjYd*Te -             & 
&  9*TrYdadjYdYdadjYd*Te - 3*TrYdadjYuYuadjYd*Te + (6*g1p2*TrYeadjYe*Te)/5._dp -         & 
&  3*TrYeadjYeYeadjYe*Te

 
DTe = oo16pi2*( betaTe1 + oo16pi2 * betaTe2 ) 

 
Else 
DTe = oo16pi2* betaTe1 
End If 
 
 
Call Chop(DTe) 

!-------------------- 
! Tu 
!-------------------- 
 
betaTu1  = TuadjYdYd + 5._dp*(TuadjYuYu) + ((26*g1p2*M1)/15._dp + (32*g3p2*M3)        & 
& /3._dp + 6*g2p2*M2 + 6._dp*(TradjYuTu))*Yu + 2._dp*(YuadjYdTd) + 4._dp*(YuadjYuTu)     & 
&  - (13*g1p2*Tu)/15._dp - 3*g2p2*Tu - (16*g3p2*Tu)/3._dp + 3*TrYuadjYu*Tu

 
 
If (TwoLoopRGE) Then 
betaTu2 = (2*g1p2*TuadjYdYd)/5._dp - 3*TrYdadjYd*TuadjYdYd - TrYeadjYe*TuadjYdYd -              & 
&  2._dp*(TuadjYdYdadjYdYd) - 4._dp*(TuadjYdYdadjYuYu) + 12*g2p2*TuadjYuYu -             & 
&  15*TrYuadjYu*TuadjYuYu - 6._dp*(TuadjYuYuadjYuYu) - (2*(2743*g1p4*M1 + 225*g1p2*g2p2*M1 +& 
&  680*g1p2*g3p2*M1 + 680*g1p2*g3p2*M3 + 1800*g2p2*g3p2*M3 - 800*g3p4*M3 +               & 
&  225*g1p2*g2p2*M2 + 3375*g2p4*M2 + 1800*g2p2*g3p2*M2 - 180*(g1p2 + 20._dp*(g3p2))*TradjYuTu +& 
&  675._dp*(TrYdadjYuTuadjYd) + 675._dp*(TrYuadjYdTdadjYu) + 180*(g1p2*M1 +              & 
&  20*g3p2*M3)*TrYuadjYu + 4050._dp*(TrYuadjYuTuadjYu))*Yu)/225._dp + (4*g1p2*YuadjYdTd)/5._dp -& 
&  6*TrYdadjYd*YuadjYdTd - 2*TrYeadjYe*YuadjYdTd - 4._dp*(YuadjYdTdadjYdYd) -            & 
&  4._dp*(YuadjYdTdadjYuYu) - (2*(2*g1p2*M1 + 15._dp*(TradjYdTd) + 5._dp*(TradjYeTe))*YuadjYdYd)/5._dp -& 
&  4._dp*(YuadjYdYdadjYdTd) - 2._dp*(YuadjYdYdadjYuTu) + (6*g1p2*YuadjYuTu)/5._dp +      & 
&  6*g2p2*YuadjYuTu - 12*TrYuadjYu*YuadjYuTu - 8._dp*(YuadjYuTuadjYuYu) - (4*g1p2*M1*YuadjYuYu)/5._dp -& 
&  12*g2p2*M2*YuadjYuYu - 18*TradjYuTu*YuadjYuYu - 6._dp*(YuadjYuYuadjYuTu) +            & 
&  (2743*g1p4*Tu)/450._dp + g1p2*g2p2*Tu + (15*g2p4*Tu)/2._dp + (136*g1p2*g3p2*Tu)/45._dp +& 
&  8*g2p2*g3p2*Tu - (16*g3p4*Tu)/9._dp - 3*TrYdadjYuYuadjYd*Tu + (4*g1p2*TrYuadjYu*Tu)/5._dp +& 
&  16*g3p2*TrYuadjYu*Tu - 9*TrYuadjYuYuadjYu*Tu

 
DTu = oo16pi2*( betaTu1 + oo16pi2 * betaTu2 ) 

 
Else 
DTu = oo16pi2* betaTu1 
End If 
 
 
Call Chop(DTu) 

!-------------------- 
! Bmu 
!-------------------- 
 
betaBmu1  = (6*g1p2*M1*Mu)/5._dp + 6*g2p2*M2*Mu + 6*TradjYdTd*Mu + 2*TradjYeTe*Mu +   & 
&  6*TradjYuTu*Mu + (-3._dp*(g1p2)/5._dp - 3._dp*(g2p2) + 3._dp*(TrYdadjYd)              & 
&  + TrYeadjYe + 3._dp*(TrYuadjYu))*Bmu

 
 
If (TwoLoopRGE) Then 
betaBmu2 = (-2*(207*g1p4*M1 + 45*g1p2*g2p2*M1 + 45*g1p2*g2p2*M2 + 375*g2p4*M2 + 10*g1p2*TradjYdTd -& 
&  400*g3p2*TradjYdTd - 30*g1p2*TradjYeTe - 20*g1p2*TradjYuTu - 400*g3p2*TradjYuTu -     & 
&  10*(g1p2*M1 - 40*g3p2*M3)*TrYdadjYd + 450._dp*(TrYdadjYdTdadjYd) + 150._dp*(TrYdadjYuTuadjYd) +& 
&  30*g1p2*M1*TrYeadjYe + 150._dp*(TrYeadjYeTeadjYe) + 150._dp*(TrYuadjYdTdadjYu) +      & 
&  20*g1p2*M1*TrYuadjYu + 400*g3p2*M3*TrYuadjYu + 450._dp*(TrYuadjYuTuadjYu))*Mu)/25._dp +& 
&  (207._dp*(g1p4)/50._dp + (9*g1p2*g2p2)/5._dp + 15._dp*(g2p4)/2._dp - (2*(g1p2 -       & 
&  40._dp*(g3p2))*TrYdadjYd)/5._dp - 9._dp*(TrYdadjYdYdadjYd) - 6._dp*(TrYdadjYuYuadjYd) +& 
&  (6*g1p2*TrYeadjYe)/5._dp - 3._dp*(TrYeadjYeYeadjYe) + (4*g1p2*TrYuadjYu)/5._dp +      & 
&  16*g3p2*TrYuadjYu - 9._dp*(TrYuadjYuYuadjYu))*Bmu

 
DBmu = oo16pi2*( betaBmu1 + oo16pi2 * betaBmu2 ) 

 
Else 
DBmu = oo16pi2* betaBmu1 
End If 
 
 
Call Chop(DBmu) 

!-------------------- 
! mq2 
!-------------------- 
 
betamq21  = 2._dp*(adjTdTd) + 2._dp*(adjTuTu) + 2._dp*(adjYdmd2Yd) + adjYdYdmq2 +     & 
&  2._dp*(adjYumu2Yu) + adjYuYumq2 - (2*AbsM1*g1p2*id3R)/15._dp - 6*AbsM2*g2p2*id3R -    & 
&  (32*AbsM3*g3p2*id3R)/3._dp + 2*adjYdYd*mHd2 + 2*adjYuYu*mHu2 + mq2adjYdYd +           & 
&  mq2adjYuYu + g1*id3R*ooSqrt15*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamq22 = -4._dp*(adjTdTdadjYdYd) - 4._dp*(adjTdYdadjYdTd) - 4._dp*(adjTuTuadjYuYu) -           & 
&  4._dp*(adjTuYuadjYuTu) - 4._dp*(adjYdmd2YdadjYdYd) - 4._dp*(adjYdTdadjTdYd) -         & 
&  4._dp*(adjYdYdadjTdTd) - 4._dp*(adjYdYdadjYdmd2Yd) - 2._dp*(adjYdYdadjYdYdmq2) -      & 
&  4._dp*(adjYdYdmq2adjYdYd) - 4._dp*(adjYumu2YuadjYuYu) - 4._dp*(adjYuTuadjTuYu) -      & 
&  4._dp*(adjYuYuadjTuTu) - 4._dp*(adjYuYuadjYumu2Yu) - 2._dp*(adjYuYuadjYuYumq2) -      & 
&  4._dp*(adjYuYumq2adjYuYu) + (4*adjTdTd*g1p2)/5._dp + (8*adjTuTu*g1p2)/5._dp +         & 
&  (4*adjYdmd2Yd*g1p2)/5._dp + (2*adjYdYdmq2*g1p2)/5._dp + (8*adjYumu2Yu*g1p2)/5._dp +   & 
&  (4*adjYuYumq2*g1p2)/5._dp + (2*AbsM2*g1p2*g2p2*id3R)/5._dp + 33*AbsM2*g2p4*id3R +     & 
&  32*AbsM2*g2p2*g3p2*id3R - (4*adjTdYd*g1p2*M1)/5._dp - (8*adjTuYu*g1p2*M1)/5._dp -     & 
&  8*adjYdYdadjYdYd*mHd2 + (4*adjYdYd*g1p2*mHd2)/5._dp - 8*adjYuYuadjYuYu*mHu2 +         & 
&  (8*adjYuYu*g1p2*mHu2)/5._dp + (2*g1p2*mq2adjYdYd)/5._dp - 2._dp*(mq2adjYdYdadjYdYd) + & 
&  (4*g1p2*mq2adjYuYu)/5._dp - 2._dp*(mq2adjYuYuadjYuYu) - 6*adjTdYd*TradjYdTd -         & 
&  2*adjTdYd*TradjYeTe - 6*adjTuYu*TradjYuTu - 6*adjYdYd*TrCTdTpTd - 6*adjYdTd*TrCTdTpYd -& 
&  2*adjYdYd*TrCTeTpTe - 2*adjYdTd*TrCTeTpYe - 6*adjYuYu*TrCTuTpTu - 6*adjYuTu*TrCTuTpYu -& 
&  6*adjYdYd*Trmd2YdadjYd - 2*adjYdYd*Trme2YeadjYe - 2*adjYdYd*Trml2adjYeYe -            & 
&  6*adjYdYd*Trmq2adjYdYd - 6*adjYuYu*Trmq2adjYuYu - 6*adjYuYu*Trmu2YuadjYu -            & 
&  6*adjTdTd*TrYdadjYd - 6*adjYdmd2Yd*TrYdadjYd - 3*adjYdYdmq2*TrYdadjYd -               & 
&  12*adjYdYd*mHd2*TrYdadjYd - 3*mq2adjYdYd*TrYdadjYd - 2*adjTdTd*TrYeadjYe -            & 
&  2*adjYdmd2Yd*TrYeadjYe - adjYdYdmq2*TrYeadjYe - 4*adjYdYd*mHd2*TrYeadjYe -            & 
&  mq2adjYdYd*TrYeadjYe - 6*adjTuTu*TrYuadjYu - 6*adjYumu2Yu*TrYuadjYu - 3*adjYuYumq2*TrYuadjYu -& 
&  12*adjYuYu*mHu2*TrYuadjYu - 3*mq2adjYuYu*TrYuadjYu + (g1p2*(180*(-1._dp*(adjYdTd) -   & 
&  2._dp*(adjYuTu) + 2*adjYdYd*M1 + 4*adjYuYu*M1) + id3R*(597*g1p2*M1 + 5*(16*g3p2*(2._dp*(M1) +& 
&  M3) + 9*g2p2*(2._dp*(M1) + M2))))*Conjg(M1))/225._dp + (16*g3p2*id3R*(g1p2*(M1 +      & 
&  2._dp*(M3)) + 15*(-8*g3p2*M3 + 3*g2p2*(2._dp*(M3) + M2)))*Conjg(M3))/45._dp  
betamq22 =  betamq22+ (g1p2*g2p2*id3R*M1*Conjg(M2))/5._dp + 16*g2p2*g3p2*id3R*M3*Conjg(M2) + 6*g2p4*id3R*Tr2(2) +& 
&  (32*g3p4*id3R*Tr2(3))/3._dp + (2*g1p2*id3R*Tr2U1(1,1))/15._dp + 4*g1*id3R*ooSqrt15*Tr3(1)

 
Dmq2 = oo16pi2*( betamq21 + oo16pi2 * betamq22 ) 

 
Else 
Dmq2 = oo16pi2* betamq21 
End If 
 
 
Call Chop(Dmq2) 

Forall(i1=1:3) Dmq2(i1,i1) =  Real(Dmq2(i1,i1),dp) 
Dmq2 = 0.5_dp*(Dmq2+ Conjg(Transpose(Dmq2)) ) 
!-------------------- 
! ml2 
!-------------------- 
 
betaml21  = 2._dp*(adjTeTe) + 2._dp*(adjYeme2Ye) + adjYeYeml2 - (6*AbsM1*g1p2*id3R)   & 
& /5._dp - 6*AbsM2*g2p2*id3R + 2*adjYeYe*mHd2 + ml2adjYeYe - g1*id3R*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betaml22 = -4._dp*(adjTeTeadjYeYe) - 4._dp*(adjTeYeadjYeTe) - 4._dp*(adjYeme2YeadjYeYe) -        & 
&  4._dp*(adjYeTeadjTeYe) - 4._dp*(adjYeYeadjTeTe) - 4._dp*(adjYeYeadjYeme2Ye) -         & 
&  2._dp*(adjYeYeadjYeYeml2) - 4._dp*(adjYeYeml2adjYeYe) + (12*adjTeTe*g1p2)/5._dp +     & 
&  (12*adjYeme2Ye*g1p2)/5._dp + (6*adjYeYeml2*g1p2)/5._dp - (12*adjTeYe*g1p2*M1)/5._dp - & 
&  8*adjYeYeadjYeYe*mHd2 + (12*adjYeYe*g1p2*mHd2)/5._dp + (6*g1p2*ml2adjYeYe)/5._dp -    & 
&  2._dp*(ml2adjYeYeadjYeYe) - 6*adjTeYe*TradjYdTd - 2*adjTeYe*TradjYeTe -               & 
&  6*adjYeYe*TrCTdTpTd - 6*adjYeTe*TrCTdTpYd - 2*adjYeYe*TrCTeTpTe - 2*adjYeTe*TrCTeTpYe -& 
&  6*adjYeYe*Trmd2YdadjYd - 2*adjYeYe*Trme2YeadjYe - 2*adjYeYe*Trml2adjYeYe -            & 
&  6*adjYeYe*Trmq2adjYdYd - 6*adjTeTe*TrYdadjYd - 6*adjYeme2Ye*TrYdadjYd -               & 
&  3*adjYeYeml2*TrYdadjYd - 12*adjYeYe*mHd2*TrYdadjYd - 3*ml2adjYeYe*TrYdadjYd -         & 
&  2*adjTeTe*TrYeadjYe - 2*adjYeme2Ye*TrYeadjYe - adjYeYeml2*TrYeadjYe - 4*adjYeYe*mHd2*TrYeadjYe -& 
&  ml2adjYeYe*TrYeadjYe + (3*g1p2*(-20._dp*(adjYeTe) + 40*adjYeYe*M1 + 3*id3R*(69*g1p2*M1 +& 
&  5*g2p2*(2._dp*(M1) + M2)))*Conjg(M1))/25._dp + (3*g2p2*id3R*(55*g2p2*M2 +             & 
&  3*g1p2*(M1 + 2._dp*(M2)))*Conjg(M2))/5._dp + 6*g2p4*id3R*Tr2(2) + (6*g1p2*id3R*Tr2U1(1,& 
& 1))/5._dp - 4*g1*id3R*sqrt3ov5*Tr3(1)

 
Dml2 = oo16pi2*( betaml21 + oo16pi2 * betaml22 ) 

 
Else 
Dml2 = oo16pi2* betaml21 
End If 
 
 
Call Chop(Dml2) 

Forall(i1=1:3) Dml2(i1,i1) =  Real(Dml2(i1,i1),dp) 
Dml2 = 0.5_dp*(Dml2+ Conjg(Transpose(Dml2)) ) 
!-------------------- 
! mHd2 
!-------------------- 
 
betamHd21  = (-6*AbsM1*g1p2)/5._dp - 6*AbsM2*g2p2 + 6._dp*(TrCTdTpTd) +               & 
&  2._dp*(TrCTeTpTe) + 6._dp*(Trmd2YdadjYd) + 2._dp*(Trme2YeadjYe) + 2._dp*(Trml2adjYeYe)& 
&  + 6._dp*(Trmq2adjYdYd) + 6*mHd2*TrYdadjYd + 2*mHd2*TrYeadjYe - g1*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamHd22 = (g1p2*(621*g1p2*M1 + 90*g2p2*M1 + 45*g2p2*M2 + 20._dp*(TradjYdTd) - 60._dp*(TradjYeTe) -& 
&  40*M1*TrYdadjYd + 120*M1*TrYeadjYe)*Conjg(M1) + 15*g2p2*(55*g2p2*M2 + 3*g1p2*(M1 +    & 
&  2._dp*(M2)))*Conjg(M2) + 10*(-2*g1p2*TrCTdTpTd + 80*g3p2*TrCTdTpTd + 2*g1p2*M1*TrCTdTpYd -& 
&  80*g3p2*M3*TrCTdTpYd + 6*g1p2*TrCTeTpTe - 6*g1p2*M1*TrCTeTpYe - 2*g1p2*Trmd2YdadjYd + & 
&  80*g3p2*Trmd2YdadjYd - 90._dp*(Trmd2YdadjYdYdadjYd) - 15._dp*(Trmd2YdadjYuYuadjYd) +  & 
&  6*g1p2*Trme2YeadjYe - 30._dp*(Trme2YeadjYeYeadjYe) + 6*g1p2*Trml2adjYeYe -            & 
&  30._dp*(Trml2adjYeYeadjYeYe) - 2*g1p2*Trmq2adjYdYd + 80*g3p2*Trmq2adjYdYd -           & 
&  90._dp*(Trmq2adjYdYdadjYdYd) - 15._dp*(Trmq2adjYdYdadjYuYu) - 15._dp*(Trmq2adjYuYuadjYdYd) -& 
&  15._dp*(Trmu2YuadjYdYdadjYu) - 90._dp*(TrYdadjTdTdadjYd) - 15._dp*(TrYdadjTuTuadjYd) +& 
&  (160*AbsM3*g3p2 - 2*g1p2*mHd2 + 80*g3p2*mHd2)*TrYdadjYd - 90._dp*(TrYdadjYdTdadjTd) - & 
&  90*mHd2*TrYdadjYdYdadjYd - 15._dp*(TrYdadjYuTuadjTd) - 15*mHd2*TrYdadjYuYuadjYd -     & 
&  15*mHu2*TrYdadjYuYuadjYd - 30._dp*(TrYeadjTeTeadjYe) + 6*g1p2*mHd2*TrYeadjYe -        & 
&  30._dp*(TrYeadjYeTeadjTe) - 30*mHd2*TrYeadjYeYeadjYe - 15._dp*(TrYuadjTdTdadjYu) -    & 
&  15._dp*(TrYuadjYdTdadjTu) - 80*g3p2*TradjYdTd*Conjg(M3) + 15*g2p4*Tr2(2) +            & 
&  3*g1p2*Tr2U1(1,1) - 2*g1*sqrt15*Tr3(1)))/25._dp

 
DmHd2 = oo16pi2*( betamHd21 + oo16pi2 * betamHd22 ) 

 
Else 
DmHd2 = oo16pi2* betamHd21 
End If 
 
 
!-------------------- 
! mHu2 
!-------------------- 
 
betamHu21  = (-6*AbsM1*g1p2)/5._dp - 6*AbsM2*g2p2 + 6._dp*(TrCTuTpTu) +               & 
&  6._dp*(Trmq2adjYuYu) + 6._dp*(Trmu2YuadjYu) + 6*mHu2*TrYuadjYu + g1*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamHu22 = (8*g1p2*TrCTuTpTu)/5._dp + 32*g3p2*TrCTuTpTu - (8*g1p2*M1*TrCTuTpYu)/5._dp -          & 
&  32*g3p2*M3*TrCTuTpYu - 6._dp*(Trmd2YdadjYuYuadjYd) - 6._dp*(Trmq2adjYdYdadjYuYu) +    & 
&  (8*g1p2*Trmq2adjYuYu)/5._dp + 32*g3p2*Trmq2adjYuYu - 6._dp*(Trmq2adjYuYuadjYdYd) -    & 
&  36._dp*(Trmq2adjYuYuadjYuYu) - 6._dp*(Trmu2YuadjYdYdadjYu) + (8*g1p2*Trmu2YuadjYu)/5._dp +& 
&  32*g3p2*Trmu2YuadjYu - 36._dp*(Trmu2YuadjYuYuadjYu) - 6._dp*(TrYdadjTuTuadjYd) -      & 
&  6._dp*(TrYdadjYuTuadjTd) - 6*mHd2*TrYdadjYuYuadjYd - 6*mHu2*TrYdadjYuYuadjYd -        & 
&  6._dp*(TrYuadjTdTdadjYu) - 36._dp*(TrYuadjTuTuadjYu) - 6._dp*(TrYuadjYdTdadjTu) +     & 
&  64*AbsM3*g3p2*TrYuadjYu + (8*g1p2*mHu2*TrYuadjYu)/5._dp + 32*g3p2*mHu2*TrYuadjYu -    & 
&  36._dp*(TrYuadjYuTuadjTu) - 36*mHu2*TrYuadjYuYuadjYu + (g1p2*(621*g1p2*M1 +           & 
&  90*g2p2*M1 + 45*g2p2*M2 - 40._dp*(TradjYuTu) + 80*M1*TrYuadjYu)*Conjg(M1))/25._dp -   & 
&  32*g3p2*TradjYuTu*Conjg(M3) + (3*g2p2*(55*g2p2*M2 + 3*g1p2*(M1 + 2._dp*(M2)))*Conjg(M2))/5._dp +& 
&  6*g2p4*Tr2(2) + (6*g1p2*Tr2U1(1,1))/5._dp + 4*g1*sqrt3ov5*Tr3(1)

 
DmHu2 = oo16pi2*( betamHu21 + oo16pi2 * betamHu22 ) 

 
Else 
DmHu2 = oo16pi2* betamHu21 
End If 
 
 
!-------------------- 
! md2 
!-------------------- 
 
betamd21  = (-8*AbsM1*g1p2*id3R)/15._dp - (32*AbsM3*g3p2*id3R)/3._dp + 2._dp*(md2YdadjYd)& 
&  + 4._dp*(TdadjTd) + 4*mHd2*YdadjYd + 2._dp*(YdadjYdmd2) + 4._dp*(Ydmq2adjYd)          & 
&  + 2*g1*id3R*ooSqrt15*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamd22 = (2*g1p2*md2YdadjYd)/5._dp + 6*g2p2*md2YdadjYd - 2._dp*(md2YdadjYdYdadjYd) -           & 
&  2._dp*(md2YdadjYuYuadjYd) + (4*g1p2*TdadjTd)/5._dp + 12*g2p2*TdadjTd - 4._dp*(TdadjTdYdadjYd) -& 
&  4._dp*(TdadjTuYuadjYd) - 4._dp*(TdadjYdYdadjTd) - 4._dp*(TdadjYuYuadjTd) -            & 
&  12*TdadjYd*TrCTdTpYd - 4*TdadjYd*TrCTeTpYe - 6*md2YdadjYd*TrYdadjYd - 12*TdadjTd*TrYdadjYd -& 
&  2*md2YdadjYd*TrYeadjYe - 4*TdadjTd*TrYeadjYe - (4*g1p2*M1*YdadjTd)/5._dp -            & 
&  12*g2p2*M2*YdadjTd - 12*TradjYdTd*YdadjTd - 4*TradjYeTe*YdadjTd - 4._dp*(YdadjTdTdadjYd) -& 
&  4._dp*(YdadjTuTuadjYd) + 24*AbsM2*g2p2*YdadjYd + (4*g1p2*mHd2*YdadjYd)/5._dp +        & 
&  12*g2p2*mHd2*YdadjYd - 12*TrCTdTpTd*YdadjYd - 4*TrCTeTpTe*YdadjYd - 12*Trmd2YdadjYd*YdadjYd -& 
&  4*Trme2YeadjYe*YdadjYd - 4*Trml2adjYeYe*YdadjYd - 12*Trmq2adjYdYd*YdadjYd -           & 
&  24*mHd2*TrYdadjYd*YdadjYd - 8*mHd2*TrYeadjYe*YdadjYd + (2*g1p2*YdadjYdmd2)/5._dp +    & 
&  6*g2p2*YdadjYdmd2 - 6*TrYdadjYd*YdadjYdmd2 - 2*TrYeadjYe*YdadjYdmd2 - 4._dp*(YdadjYdmd2YdadjYd) -& 
&  4._dp*(YdadjYdTdadjTd) - 8*mHd2*YdadjYdYdadjYd - 2._dp*(YdadjYdYdadjYdmd2) -          & 
&  4._dp*(YdadjYdYdmq2adjYd) - 4._dp*(YdadjYumu2YuadjYd) - 4._dp*(YdadjYuTuadjTd) -      & 
&  4*mHd2*YdadjYuYuadjYd - 4*mHu2*YdadjYuYuadjYd - 2._dp*(YdadjYuYuadjYdmd2) -           & 
&  4._dp*(YdadjYuYumq2adjYd) + (4*g1p2*Ydmq2adjYd)/5._dp + 12*g2p2*Ydmq2adjYd -          & 
&  12*TrYdadjYd*Ydmq2adjYd - 4*TrYeadjYe*Ydmq2adjYd - 4._dp*(Ydmq2adjYdYdadjYd) -        & 
&  4._dp*(Ydmq2adjYuYuadjYd) + (4*g1p2*(2*id3R*(303*g1p2*M1 + 40*g3p2*(2._dp*(M1) +      & 
&  M3)) - 45._dp*(TdadjYd) + 90*M1*YdadjYd)*Conjg(M1))/225._dp + (64*g3p2*id3R*(-        & 
& 30*g3p2*M3 + g1p2*(M1 + 2._dp*(M3)))*Conjg(M3))/45._dp - 12*g2p2*TdadjYd*Conjg(M2) +   & 
&  (32*g3p4*id3R*Tr2(3))/3._dp + (8*g1p2*id3R*Tr2U1(1,1))/15._dp + 8*g1*id3R*ooSqrt15*Tr3(1)

 
Dmd2 = oo16pi2*( betamd21 + oo16pi2 * betamd22 ) 

 
Else 
Dmd2 = oo16pi2* betamd21 
End If 
 
 
Call Chop(Dmd2) 

Forall(i1=1:3) Dmd2(i1,i1) =  Real(Dmd2(i1,i1),dp) 
Dmd2 = 0.5_dp*(Dmd2+ Conjg(Transpose(Dmd2)) ) 
!-------------------- 
! mu2 
!-------------------- 
 
betamu21  = (-32*AbsM1*g1p2*id3R)/15._dp - (32*AbsM3*g3p2*id3R)/3._dp +               & 
&  2._dp*(mu2YuadjYu) + 4._dp*(TuadjTu) + 4*mHu2*YuadjYu + 2._dp*(YuadjYumu2)            & 
&  + 4._dp*(Yumq2adjYu) - 4*g1*id3R*ooSqrt15*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamu22 = -2._dp*(mu2YuadjYdYdadjYu) - (2*g1p2*mu2YuadjYu)/5._dp + 6*g2p2*mu2YuadjYu -          & 
&  2._dp*(mu2YuadjYuYuadjYu) - 6*mu2YuadjYu*TrYuadjYu - 4._dp*(TuadjTdYdadjYu) -         & 
&  (4*g1p2*TuadjTu)/5._dp + 12*g2p2*TuadjTu - 12*TrYuadjYu*TuadjTu - 4._dp*(TuadjTuYuadjYu) -& 
&  4._dp*(TuadjYdYdadjTu) - 12*TrCTuTpYu*TuadjYu - 4._dp*(TuadjYuYuadjTu) -              & 
&  4._dp*(YuadjTdTdadjYu) + (4*g1p2*M1*YuadjTu)/5._dp - 12*g2p2*M2*YuadjTu -             & 
&  12*TradjYuTu*YuadjTu - 4._dp*(YuadjTuTuadjYu) - 4._dp*(YuadjYdmd2YdadjYu) -           & 
&  4._dp*(YuadjYdTdadjTu) - 4*mHd2*YuadjYdYdadjYu - 4*mHu2*YuadjYdYdadjYu -              & 
&  2._dp*(YuadjYdYdadjYumu2) - 4._dp*(YuadjYdYdmq2adjYu) + 24*AbsM2*g2p2*YuadjYu -       & 
&  (4*g1p2*mHu2*YuadjYu)/5._dp + 12*g2p2*mHu2*YuadjYu - 12*TrCTuTpTu*YuadjYu -           & 
&  12*Trmq2adjYuYu*YuadjYu - 12*Trmu2YuadjYu*YuadjYu - 24*mHu2*TrYuadjYu*YuadjYu -       & 
&  (2*g1p2*YuadjYumu2)/5._dp + 6*g2p2*YuadjYumu2 - 6*TrYuadjYu*YuadjYumu2 -              & 
&  4._dp*(YuadjYumu2YuadjYu) - 4._dp*(YuadjYuTuadjTu) - 8*mHu2*YuadjYuYuadjYu -          & 
&  2._dp*(YuadjYuYuadjYumu2) - 4._dp*(YuadjYuYumq2adjYu) - 4._dp*(Yumq2adjYdYdadjYu) -   & 
&  (4*g1p2*Yumq2adjYu)/5._dp + 12*g2p2*Yumq2adjYu - 12*TrYuadjYu*Yumq2adjYu -            & 
&  4._dp*(Yumq2adjYuYuadjYu) + (4*g1p2*(8*id3R*(321*g1p2*M1 + 40*g3p2*(2._dp*(M1) +      & 
&  M3)) + 45*(TuadjYu - 2*M1*YuadjYu))*Conjg(M1))/225._dp - (128*g3p2*id3R*(15*g3p2*M3 - & 
&  2*g1p2*(M1 + 2._dp*(M3)))*Conjg(M3))/45._dp - 12*g2p2*TuadjYu*Conjg(M2) +             & 
&  (32*g3p4*id3R*Tr2(3))/3._dp + (32*g1p2*id3R*Tr2U1(1,1))/15._dp - 16*g1*id3R*ooSqrt15*Tr3(1)

 
Dmu2 = oo16pi2*( betamu21 + oo16pi2 * betamu22 ) 

 
Else 
Dmu2 = oo16pi2* betamu21 
End If 
 
 
Call Chop(Dmu2) 

Forall(i1=1:3) Dmu2(i1,i1) =  Real(Dmu2(i1,i1),dp) 
Dmu2 = 0.5_dp*(Dmu2+ Conjg(Transpose(Dmu2)) ) 
!-------------------- 
! me2 
!-------------------- 
 
betame21  = (-24*AbsM1*g1p2*id3R)/5._dp + 2*(me2YeadjYe + 2._dp*(TeadjTe)             & 
&  + 2*mHd2*YeadjYe + YeadjYeme2 + 2._dp*(Yeml2adjYe)) + 2*g1*id3R*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betame22 = (2*(6*g1p2*(234*g1p2*id3R*M1 + 5*(TeadjYe - 2*M1*YeadjYe))*Conjg(M1) - 5*(3*g1p2*me2YeadjYe -& 
&  15*g2p2*me2YeadjYe + 5._dp*(me2YeadjYeYeadjYe) + 6*g1p2*TeadjTe - 30*g2p2*TeadjTe +   & 
&  10._dp*(TeadjTeYeadjYe) + 10._dp*(TeadjYeYeadjTe) + 30*TeadjYe*TrCTdTpYd +            & 
&  10*TeadjYe*TrCTeTpYe + 15*me2YeadjYe*TrYdadjYd + 30*TeadjTe*TrYdadjYd +               & 
&  5*me2YeadjYe*TrYeadjYe + 10*TeadjTe*TrYeadjYe + (-6*g1p2*M1 + 30*g2p2*M2 +            & 
&  30._dp*(TradjYdTd) + 10._dp*(TradjYeTe))*YeadjTe + 10._dp*(YeadjTeTeadjYe) +          & 
&  2*(-30*AbsM2*g2p2 + 3*g1p2*mHd2 - 15*g2p2*mHd2 + 15._dp*(TrCTdTpTd) + 5._dp*(TrCTeTpTe) +& 
&  15._dp*(Trmd2YdadjYd) + 5._dp*(Trme2YeadjYe) + 5._dp*(Trml2adjYeYe) + 15._dp*(Trmq2adjYdYd) +& 
&  30*mHd2*TrYdadjYd + 10*mHd2*TrYeadjYe)*YeadjYe + 3*g1p2*YeadjYeme2 - 15*g2p2*YeadjYeme2 +& 
&  15*TrYdadjYd*YeadjYeme2 + 5*TrYeadjYe*YeadjYeme2 + 10._dp*(YeadjYeme2YeadjYe) +       & 
&  10._dp*(YeadjYeTeadjTe) + 20*mHd2*YeadjYeYeadjYe + 5._dp*(YeadjYeYeadjYeme2) +        & 
&  10._dp*(YeadjYeYeml2adjYe) + 6*g1p2*Yeml2adjYe - 30*g2p2*Yeml2adjYe + 30*TrYdadjYd*Yeml2adjYe +& 
&  10*TrYeadjYe*Yeml2adjYe + 10._dp*(Yeml2adjYeYeadjYe) + 30*g2p2*TeadjYe*Conjg(M2)) +   & 
&  20*g1*id3R*(3*g1*Tr2U1(1,1) + sqrt15*Tr3(1))))/25._dp

 
Dme2 = oo16pi2*( betame21 + oo16pi2 * betame22 ) 

 
Else 
Dme2 = oo16pi2* betame21 
End If 
 
 
Call Chop(Dme2) 

Forall(i1=1:3) Dme2(i1,i1) =  Real(Dme2(i1,i1),dp) 
Dme2 = 0.5_dp*(Dme2+ Conjg(Transpose(Dme2)) ) 
!-------------------- 
! M1 
!-------------------- 
 
betaM11  = (66*g1p2*M1)/5._dp

 
 
If (TwoLoopRGE) Then 
betaM12 = (2*g1p2*(398*g1p2*M1 + 135*g2p2*M1 + 440*g3p2*M1 + 440*g3p2*M3 + 135*g2p2*M2 +        & 
&  70._dp*(TradjYdTd) + 90._dp*(TradjYeTe) + 130._dp*(TradjYuTu) - 70*M1*TrYdadjYd -     & 
&  90*M1*TrYeadjYe - 130*M1*TrYuadjYu))/25._dp

 
DM1 = oo16pi2*( betaM11 + oo16pi2 * betaM12 ) 

 
Else 
DM1 = oo16pi2* betaM11 
End If 
 
 
Call Chop(DM1) 

!-------------------- 
! M2 
!-------------------- 
 
betaM21  = 2*g2p2*M2

 
 
If (TwoLoopRGE) Then 
betaM22 = (2*g2p2*(9*g1p2*M1 + 120*g3p2*M3 + 9*g1p2*M2 + 250*g2p2*M2 + 120*g3p2*M2 +            & 
&  30._dp*(TradjYdTd) + 10._dp*(TradjYeTe) + 30._dp*(TradjYuTu) - 30*M2*TrYdadjYd -      & 
&  10*M2*TrYeadjYe - 30*M2*TrYuadjYu))/5._dp

 
DM2 = oo16pi2*( betaM21 + oo16pi2 * betaM22 ) 

 
Else 
DM2 = oo16pi2* betaM21 
End If 
 
 
Call Chop(DM2) 

!-------------------- 
! M3 
!-------------------- 
 
betaM31  = -6*g3p2*M3

 
 
If (TwoLoopRGE) Then 
betaM32 = (2*g3p2*(11*g1p2*M1 + 11*g1p2*M3 + 45*g2p2*M3 + 140*g3p2*M3 + 45*g2p2*M2 +            & 
&  20._dp*(TradjYdTd) + 20._dp*(TradjYuTu) - 20*M3*TrYdadjYd - 20*M3*TrYuadjYu))/5._dp

 
DM3 = oo16pi2*( betaM31 + oo16pi2 * betaM32 ) 

 
Else 
DM3 = oo16pi2* betaM31 
End If 
 
 
Call Chop(DM3) 

Call ParametersToG213(Dg1,Dg2,Dg3,DYd,DYe,DYu,DMu,DTd,DTe,DTu,DBmu,Dmq2,              & 
& Dml2,DmHd2,DmHu2,Dmd2,Dmu2,Dme2,DM1,DM2,DM3,f)

Iname = Iname - 1 
 
End Subroutine rge213  

Subroutine GToParameters215(g,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,              & 
& mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)

Implicit None 
Real(dp), Intent(in) :: g(215) 
Real(dp),Intent(out) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp),Intent(out) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters215' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yd(i1,i2) = Cmplx( g(SumI+4), g(SumI+5), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Ye(i1,i2) = Cmplx( g(SumI+22), g(SumI+23), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yu(i1,i2) = Cmplx( g(SumI+40), g(SumI+41), dp) 
End Do 
 End Do 
 
Mu= Cmplx(g(58),g(59),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Td(i1,i2) = Cmplx( g(SumI+60), g(SumI+61), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Te(i1,i2) = Cmplx( g(SumI+78), g(SumI+79), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Tu(i1,i2) = Cmplx( g(SumI+96), g(SumI+97), dp) 
End Do 
 End Do 
 
Bmu= Cmplx(g(114),g(115),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
mq2(i1,i2) = Cmplx( g(SumI+116), g(SumI+117), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
ml2(i1,i2) = Cmplx( g(SumI+134), g(SumI+135), dp) 
End Do 
 End Do 
 
mHd2= g(152) 
mHu2= g(153) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
md2(i1,i2) = Cmplx( g(SumI+154), g(SumI+155), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
mu2(i1,i2) = Cmplx( g(SumI+172), g(SumI+173), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
me2(i1,i2) = Cmplx( g(SumI+190), g(SumI+191), dp) 
End Do 
 End Do 
 
M1= Cmplx(g(208),g(209),dp) 
M2= Cmplx(g(210),g(211),dp) 
M3= Cmplx(g(212),g(213),dp) 
vd= g(214) 
vu= g(215) 
Do i1=1,215 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters215

Subroutine ParametersToG215(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,           & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,g)

Implicit None 
Real(dp), Intent(out) :: g(215) 
Real(dp), Intent(in) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp), Intent(in) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG215' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+4) = Real(Yd(i1,i2), dp) 
g(SumI+5) = Aimag(Yd(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+22) = Real(Ye(i1,i2), dp) 
g(SumI+23) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+40) = Real(Yu(i1,i2), dp) 
g(SumI+41) = Aimag(Yu(i1,i2)) 
End Do 
End Do 

g(58) = Real(Mu,dp)  
g(59) = Aimag(Mu)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+60) = Real(Td(i1,i2), dp) 
g(SumI+61) = Aimag(Td(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+78) = Real(Te(i1,i2), dp) 
g(SumI+79) = Aimag(Te(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+96) = Real(Tu(i1,i2), dp) 
g(SumI+97) = Aimag(Tu(i1,i2)) 
End Do 
End Do 

g(114) = Real(Bmu,dp)  
g(115) = Aimag(Bmu)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+116) = Real(mq2(i1,i2), dp) 
g(SumI+117) = Aimag(mq2(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+134) = Real(ml2(i1,i2), dp) 
g(SumI+135) = Aimag(ml2(i1,i2)) 
End Do 
End Do 

g(152) = mHd2  
g(153) = mHu2  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+154) = Real(md2(i1,i2), dp) 
g(SumI+155) = Aimag(md2(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+172) = Real(mu2(i1,i2), dp) 
g(SumI+173) = Aimag(mu2(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+190) = Real(me2(i1,i2), dp) 
g(SumI+191) = Aimag(me2(i1,i2)) 
End Do 
End Do 

g(208) = Real(M1,dp)  
g(209) = Aimag(M1)  
g(210) = Real(M2,dp)  
g(211) = Aimag(M2)  
g(212) = Real(M3,dp)  
g(213) = Aimag(M3)  
g(214) = vd  
g(215) = vu  
Iname = Iname - 1 
 
End Subroutine ParametersToG215

Subroutine rge215(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,         & 
& Dg3,mHd2,betamHd21,betamHd22,DmHd2,mHu2,betamHu21,betamHu22,DmHu2,vd,betavd1,          & 
& betavd2,Dvd,vu,betavu1,betavu2,Dvu
Complex(dp) :: Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3),Ye(3,3)          & 
& ,betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3),Yu(3,3),betaYu1(3,3),betaYu2(3,3)       & 
& ,DYu(3,3),adjYu(3,3),Mu,betaMu1,betaMu2,DMu,Td(3,3),betaTd1(3,3),betaTd2(3,3)          & 
& ,DTd(3,3),adjTd(3,3),Te(3,3),betaTe1(3,3),betaTe2(3,3),DTe(3,3),adjTe(3,3)             & 
& ,Tu(3,3),betaTu1(3,3),betaTu2(3,3),DTu(3,3),adjTu(3,3),Bmu,betaBmu1,betaBmu2,          & 
& DBmu,mq2(3,3),betamq21(3,3),betamq22(3,3),Dmq2(3,3),ml2(3,3),betaml21(3,3)             & 
& ,betaml22(3,3),Dml2(3,3),md2(3,3),betamd21(3,3),betamd22(3,3),Dmd2(3,3),               & 
& mu2(3,3),betamu21(3,3),betamu22(3,3),Dmu2(3,3),me2(3,3),betame21(3,3),betame22(3,3)    & 
& ,Dme2(3,3),M1,betaM11,betaM12,DM1,M2,betaM21,betaM22,DM2,M3,betaM31,betaM32,DM3
Real(dp) :: Tr1(3),Tr2(3),Tr3(3) 
Real(dp) :: Tr2U1(3,3) 
Real(dp) :: AbsM1,AbsM2,AbsM3
Complex(dp) :: md2Yd(3,3),me2Ye(3,3),ml2adjYe(3,3),mq2adjYd(3,3),mq2adjYu(3,3),mu2Yu(3,3),           & 
& Ydmq2(3,3),YdadjYd(3,3),Yeml2(3,3),YeadjYe(3,3),Yumq2(3,3),YuadjYu(3,3),               & 
& adjYdmd2(3,3),adjYdYd(3,3),adjYdTd(3,3),adjYeme2(3,3),adjYeYe(3,3),adjYeTe(3,3),       & 
& adjYumu2(3,3),adjYuYu(3,3),adjYuTu(3,3),adjTdTd(3,3),adjTeTe(3,3),adjTuTu(3,3),        & 
& CTdTpTd(3,3),CTeTpTe(3,3),CTuTpTu(3,3),TdadjTd(3,3),TeadjTe(3,3),TuadjTu(3,3),         & 
& md2YdadjYd(3,3),me2YeadjYe(3,3),ml2adjYeYe(3,3),mq2adjYdYd(3,3),mq2adjYuYu(3,3),       & 
& mu2YuadjYu(3,3),Ydmq2adjYd(3,3),YdadjYdmd2(3,3),YdadjYdYd(3,3),YdadjYdTd(3,3),         & 
& YdadjYuYu(3,3),YdadjYuTu(3,3),Yeml2adjYe(3,3),YeadjYeme2(3,3),YeadjYeYe(3,3),          & 
& YeadjYeTe(3,3),Yumq2adjYu(3,3),YuadjYdYd(3,3),YuadjYdTd(3,3),YuadjYumu2(3,3),          & 
& YuadjYuYu(3,3),YuadjYuTu(3,3),adjYdmd2Yd(3,3),adjYdYdmq2(3,3),adjYeme2Ye(3,3),         & 
& adjYeYeml2(3,3),adjYumu2Yu(3,3),adjYuYumq2(3,3),TdadjYdYd(3,3),TdadjYuYu(3,3),         & 
& TeadjYeYe(3,3),TuadjYdYd(3,3),TuadjYuYu(3,3)

Complex(dp) :: YdadjYu(3,3),YdadjTd(3,3),YdadjTu(3,3),YeadjTe(3,3),YuadjYd(3,3),YuadjTd(3,3),        & 
& YuadjTu(3,3),adjYdCmd2(3,3),adjYeCme2(3,3),adjYuCmu2(3,3),adjTdYd(3,3),adjTeYe(3,3),   & 
& adjTuYu(3,3),Cml2adjYe(3,3),Cmq2adjYd(3,3),Cmq2adjYu(3,3),CTdTpYd(3,3),CTeTpYe(3,3),   & 
& CTuTpYu(3,3),TdadjYd(3,3),TdadjYu(3,3),TdadjTu(3,3),TeadjYe(3,3),TuadjYd(3,3),         & 
& TuadjYu(3,3),TuadjTd(3,3),md2YdadjYu(3,3),mu2YuadjYd(3,3),Ydmq2adjYu(3,3),             & 
& YdadjYdCmd2(3,3),YdadjYumu2(3,3),YdadjTdTd(3,3),YdCmq2adjYd(3,3),YeadjYeCme2(3,3),     & 
& YeadjTeTe(3,3),YeCml2adjYe(3,3),Yumq2adjYd(3,3),YuadjYdmd2(3,3),YuadjYuCmu2(3,3),      & 
& YuadjTuTu(3,3),YuCmq2adjYu(3,3),adjYdYdadjYd(3,3),adjYdYdadjYu(3,3),adjYdYdadjTd(3,3), & 
& adjYdYdadjTu(3,3),adjYdTdadjYd(3,3),adjYdTdadjYu(3,3),adjYdTdadjTd(3,3),               & 
& adjYdTdadjTu(3,3),adjYeYeadjYe(3,3),adjYeYeadjTe(3,3),adjYeTeadjYe(3,3),               & 
& adjYeTeadjTe(3,3),adjYuYuadjYd(3,3),adjYuYuadjYu(3,3),adjYuYuadjTd(3,3),               & 
& adjYuYuadjTu(3,3),adjYuTuadjYd(3,3),adjYuTuadjYu(3,3),adjYuTuadjTd(3,3),               & 
& adjYuTuadjTu(3,3),adjTdYdadjYd(3,3),adjTdYdadjYu(3,3),adjTdTdadjYd(3,3),               & 
& adjTdTdadjYu(3,3),adjTeYeadjYe(3,3),adjTeTeadjYe(3,3),adjTuYuadjYd(3,3),               & 
& adjTuYuadjYu(3,3),adjTuTuadjYd(3,3),adjTuTuadjYu(3,3),TdadjTdYd(3,3),TeadjTeYe(3,3),   & 
& TuadjTuYu(3,3),md2YdadjYdYd(3,3),me2YeadjYeYe(3,3),ml2adjYeYeadjYe(3,3),               & 
& mq2adjYdYdadjYd(3,3),mq2adjYdYdadjYu(3,3),mq2adjYuYuadjYd(3,3),mq2adjYuYuadjYu(3,3),   & 
& mu2YuadjYuYu(3,3),Ydmq2adjYdYd(3,3),YdadjYdmd2Yd(3,3),YdadjYdYdmq2(3,3),               & 
& YdadjYdYdadjYd(3,3),YdadjYdTdadjYd(3,3),YdadjYdTdadjTd(3,3),YdadjYuYuadjYd(3,3),       & 
& YdadjYuTuadjYd(3,3),YdadjYuTuadjTd(3,3),YdadjTdTdadjYd(3,3),YdadjTuTuadjYd(3,3),       & 
& Yeml2adjYeYe(3,3),YeadjYeme2Ye(3,3),YeadjYeYeml2(3,3),YeadjYeYeadjYe(3,3),             & 
& YeadjYeTeadjYe(3,3),YeadjYeTeadjTe(3,3),YeadjTeTeadjYe(3,3),Yumq2adjYuYu(3,3),         & 
& YuadjYdYdadjYu(3,3),YuadjYdTdadjYu(3,3),YuadjYdTdadjTu(3,3),YuadjYumu2Yu(3,3),         & 
& YuadjYuYumq2(3,3),YuadjYuYuadjYu(3,3),YuadjYuTuadjYu(3,3),YuadjYuTuadjTu(3,3),         & 
& YuadjTdTdadjYu(3,3),YuadjTuTuadjYu(3,3),adjYdmd2YdadjYd(3,3),adjYdmd2YdadjYu(3,3),     & 
& adjYdYdmq2adjYd(3,3),adjYdYdmq2adjYu(3,3),adjYdYdadjYdmd2(3,3),adjYdYdadjYdYd(3,3),    & 
& adjYdYdadjYdTd(3,3),adjYdYdadjYumu2(3,3),adjYdYdadjYuYu(3,3),adjYdYdadjYuTu(3,3),      & 
& adjYdYdadjTdTd(3,3),adjYdTdadjYdYd(3,3),adjYdTdadjYuYu(3,3),adjYdTdadjTdYd(3,3),       & 
& adjYeme2YeadjYe(3,3),adjYeYeml2adjYe(3,3),adjYeYeadjYeme2(3,3),adjYeYeadjYeYe(3,3),    & 
& adjYeYeadjYeTe(3,3),adjYeYeadjTeTe(3,3),adjYeTeadjYeYe(3,3),adjYeTeadjTeYe(3,3),       & 
& adjYumu2YuadjYd(3,3),adjYumu2YuadjYu(3,3),adjYuYumq2adjYd(3,3),adjYuYumq2adjYu(3,3),   & 
& adjYuYuadjYdmd2(3,3),adjYuYuadjYdYd(3,3),adjYuYuadjYdTd(3,3),adjYuYuadjYumu2(3,3),     & 
& adjYuYuadjYuYu(3,3),adjYuYuadjYuTu(3,3),adjYuYuadjTuTu(3,3),adjYuTuadjYdYd(3,3),       & 
& adjYuTuadjYuYu(3,3),adjYuTuadjTuYu(3,3),adjTdYdadjYdTd(3,3),adjTdTdadjYdYd(3,3),       & 
& adjTeYeadjYeTe(3,3),adjTeTeadjYeYe(3,3),adjTuYuadjYuTu(3,3),adjTuTuadjYuYu(3,3),       & 
& TdadjYdYdadjTd(3,3),TdadjYuYuadjTd(3,3),TdadjTdYdadjYd(3,3),TdadjTuYuadjYd(3,3),       & 
& TeadjYeYeadjTe(3,3),TeadjTeYeadjYe(3,3),TuadjYdYdadjTu(3,3),TuadjYuYuadjTu(3,3)

Complex(dp) :: TuadjTdYdadjYu(3,3),TuadjTuYuadjYu(3,3),md2YdadjYdYdadjYd(3,3),md2YdadjYuYuadjYd(3,3), & 
& me2YeadjYeYeadjYe(3,3),ml2adjYeYeadjYeYe(3,3),mq2adjYdYdadjYdYd(3,3),mq2adjYdYdadjYuYu(3,3),& 
& mq2adjYuYuadjYdYd(3,3),mq2adjYuYuadjYuYu(3,3),mu2YuadjYdYdadjYu(3,3),mu2YuadjYuYuadjYu(3,3),& 
& Ydmq2adjYdYdadjYd(3,3),Ydmq2adjYuYuadjYd(3,3),YdadjYdmd2YdadjYd(3,3),YdadjYdYdmq2adjYd(3,3),& 
& YdadjYdYdadjYdmd2(3,3),YdadjYdYdadjYdYd(3,3),YdadjYdYdadjYdTd(3,3),YdadjYdTdadjYdYd(3,3),& 
& YdadjYumu2YuadjYd(3,3),YdadjYuYumq2adjYd(3,3),YdadjYuYuadjYdmd2(3,3),YdadjYuYuadjYdYd(3,3),& 
& YdadjYuYuadjYdTd(3,3),YdadjYuYuadjYuYu(3,3),YdadjYuYuadjYuTu(3,3),YdadjYuTuadjYdYd(3,3),& 
& YdadjYuTuadjYuYu(3,3),Yeml2adjYeYeadjYe(3,3),YeadjYeme2YeadjYe(3,3),YeadjYeYeml2adjYe(3,3),& 
& YeadjYeYeadjYeme2(3,3),YeadjYeYeadjYeYe(3,3),YeadjYeYeadjYeTe(3,3),YeadjYeTeadjYeYe(3,3),& 
& Yumq2adjYdYdadjYu(3,3),Yumq2adjYuYuadjYu(3,3),YuadjYdmd2YdadjYu(3,3),YuadjYdYdmq2adjYu(3,3),& 
& YuadjYdYdadjYdYd(3,3),YuadjYdYdadjYdTd(3,3),YuadjYdYdadjYumu2(3,3),YuadjYdYdadjYuYu(3,3),& 
& YuadjYdYdadjYuTu(3,3),YuadjYdTdadjYdYd(3,3),YuadjYdTdadjYuYu(3,3),YuadjYumu2YuadjYu(3,3),& 
& YuadjYuYumq2adjYu(3,3),YuadjYuYuadjYumu2(3,3),YuadjYuYuadjYuYu(3,3),YuadjYuYuadjYuTu(3,3),& 
& YuadjYuTuadjYuYu(3,3),adjYdmd2YdadjYdYd(3,3),adjYdYdmq2adjYdYd(3,3),adjYdYdadjYdmd2Yd(3,3),& 
& adjYdYdadjYdYdmq2(3,3),adjYeme2YeadjYeYe(3,3),adjYeYeml2adjYeYe(3,3),adjYeYeadjYeme2Ye(3,3),& 
& adjYeYeadjYeYeml2(3,3),adjYumu2YuadjYuYu(3,3),adjYuYumq2adjYuYu(3,3),adjYuYuadjYumu2Yu(3,3),& 
& adjYuYuadjYuYumq2(3,3),TdadjYdYdadjYdYd(3,3),TdadjYuYuadjYdYd(3,3),TdadjYuYuadjYuYu(3,3),& 
& TeadjYeYeadjYeYe(3,3),TuadjYdYdadjYdYd(3,3),TuadjYdYdadjYuYu(3,3),TuadjYuYuadjYuYu(3,3)

Complex(dp) :: Trmd2,Trme2,Trml2,Trmq2,Trmu2,TrYdadjYd,TrYeadjYe,TrYuadjYu,TradjYdTd,TradjYeTe,      & 
& TradjYuTu,TrCTdTpTd,TrCTeTpTe,TrCTuTpTu,Trmd2YdadjYd,Trme2YeadjYe,Trml2adjYeYe,        & 
& Trmq2adjYdYd,Trmq2adjYuYu,Trmu2YuadjYu

Complex(dp) :: TrCTdTpYd,TrCTeTpYe,TrCTuTpYu,TrYdadjYdCmd2,TrYdCmq2adjYd,TrYeadjYeCme2,              & 
& TrYeCml2adjYe,TrYuadjYuCmu2,TrYuCmq2adjYu,TrYdadjYdYdadjYd,TrYdadjYdTdadjYd,           & 
& TrYdadjYdTdadjTd,TrYdadjYuYuadjYd,TrYdadjYuTuadjYd,TrYdadjYuTuadjTd,TrYdadjTdTdadjYd,  & 
& TrYdadjTuTuadjYd,TrYeadjYeYeadjYe,TrYeadjYeTeadjYe,TrYeadjYeTeadjTe,TrYeadjTeTeadjYe,  & 
& TrYuadjYdTdadjYu,TrYuadjYdTdadjTu,TrYuadjYuYuadjYu,TrYuadjYuTuadjYu,TrYuadjYuTuadjTu,  & 
& TrYuadjTdTdadjYu,TrYuadjTuTuadjYu,Trmd2YdadjYdYdadjYd,Trmd2YdadjYuYuadjYd,             & 
& Trme2YeadjYeYeadjYe,Trml2adjYeYeadjYeYe,Trmq2adjYdYdadjYdYd,Trmq2adjYdYdadjYuYu,       & 
& Trmq2adjYuYuadjYdYd,Trmq2adjYuYuadjYuYu,Trmu2YuadjYdYdadjYu,Trmu2YuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g2p2,g2p3,g3p2,g3p3

Complex(dp) :: sqrt3ov5,ooSqrt15

Real(dp) :: g1p4,g2p4,g3p4

Complex(dp) :: sqrt15,Xip2

Iname = Iname +1 
NameOfUnit(Iname) = 'rge215' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters215(gy,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,              & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)

AbsM1 = Conjg(M1)*M1
AbsM2 = Conjg(M2)*M2
AbsM3 = Conjg(M3)*M3
Call Adjungate(Yd,adjYd)
Call Adjungate(Ye,adjYe)
Call Adjungate(Yu,adjYu)
Call Adjungate(Td,adjTd)
Call Adjungate(Te,adjTe)
Call Adjungate(Tu,adjTu)
 md2Yd = Matmul2(md2,Yd,OnlyDiagonal) 
 me2Ye = Matmul2(me2,Ye,OnlyDiagonal) 
 ml2adjYe = Matmul2(ml2,adjYe,OnlyDiagonal) 
 mq2adjYd = Matmul2(mq2,adjYd,OnlyDiagonal) 
 mq2adjYu = Matmul2(mq2,adjYu,OnlyDiagonal) 
 mu2Yu = Matmul2(mu2,Yu,OnlyDiagonal) 
 Ydmq2 = Matmul2(Yd,mq2,OnlyDiagonal) 
 YdadjYd = Matmul2(Yd,adjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 Yeml2 = Matmul2(Ye,ml2,OnlyDiagonal) 
 YeadjYe = Matmul2(Ye,adjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
 Yumq2 = Matmul2(Yu,mq2,OnlyDiagonal) 
 YuadjYu = Matmul2(Yu,adjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYu(i2,i2) =  Real(YuadjYu(i2,i2),dp) 
 adjYdmd2 = Matmul2(adjYd,md2,OnlyDiagonal) 
 adjYdYd = Matmul2(adjYd,Yd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYd(i2,i2) =  Real(adjYdYd(i2,i2),dp) 
 adjYdTd = Matmul2(adjYd,Td,OnlyDiagonal) 
 adjYeme2 = Matmul2(adjYe,me2,OnlyDiagonal) 
 adjYeYe = Matmul2(adjYe,Ye,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYe(i2,i2) =  Real(adjYeYe(i2,i2),dp) 
 adjYeTe = Matmul2(adjYe,Te,OnlyDiagonal) 
 adjYumu2 = Matmul2(adjYu,mu2,OnlyDiagonal) 
 adjYuYu = Matmul2(adjYu,Yu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYu(i2,i2) =  Real(adjYuYu(i2,i2),dp) 
 adjYuTu = Matmul2(adjYu,Tu,OnlyDiagonal) 
 adjTdTd = Matmul2(adjTd,Td,OnlyDiagonal) 
 adjTeTe = Matmul2(adjTe,Te,OnlyDiagonal) 
 adjTuTu = Matmul2(adjTu,Tu,OnlyDiagonal) 
 CTdTpTd = Matmul2(Conjg(Td),Transpose(Td),OnlyDiagonal) 
Forall(i2=1:3)  CTdTpTd(i2,i2) =  Real(CTdTpTd(i2,i2),dp) 
 CTeTpTe = Matmul2(Conjg(Te),Transpose(Te),OnlyDiagonal) 
Forall(i2=1:3)  CTeTpTe(i2,i2) =  Real(CTeTpTe(i2,i2),dp) 
 CTuTpTu = Matmul2(Conjg(Tu),Transpose(Tu),OnlyDiagonal) 
Forall(i2=1:3)  CTuTpTu(i2,i2) =  Real(CTuTpTu(i2,i2),dp) 
 TdadjTd = Matmul2(Td,adjTd,OnlyDiagonal) 
 TeadjTe = Matmul2(Te,adjTe,OnlyDiagonal) 
 TuadjTu = Matmul2(Tu,adjTu,OnlyDiagonal) 
 md2YdadjYd = Matmul2(md2,YdadjYd,OnlyDiagonal) 
 me2YeadjYe = Matmul2(me2,YeadjYe,OnlyDiagonal) 
 ml2adjYeYe = Matmul2(ml2,adjYeYe,OnlyDiagonal) 
 mq2adjYdYd = Matmul2(mq2,adjYdYd,OnlyDiagonal) 
 mq2adjYuYu = Matmul2(mq2,adjYuYu,OnlyDiagonal) 
 mu2YuadjYu = Matmul2(mu2,YuadjYu,OnlyDiagonal) 
 Ydmq2adjYd = Matmul2(Yd,mq2adjYd,OnlyDiagonal) 
Forall(i2=1:3)  Ydmq2adjYd(i2,i2) =  Real(Ydmq2adjYd(i2,i2),dp) 
 YdadjYdmd2 = Matmul2(Yd,adjYdmd2,OnlyDiagonal) 
 YdadjYdYd = Matmul2(Yd,adjYdYd,OnlyDiagonal) 
 YdadjYdTd = Matmul2(Yd,adjYdTd,OnlyDiagonal) 
 YdadjYuYu = Matmul2(Yd,adjYuYu,OnlyDiagonal) 
 YdadjYuTu = Matmul2(Yd,adjYuTu,OnlyDiagonal) 
 Yeml2adjYe = Matmul2(Ye,ml2adjYe,OnlyDiagonal) 
Forall(i2=1:3)  Yeml2adjYe(i2,i2) =  Real(Yeml2adjYe(i2,i2),dp) 
 YeadjYeme2 = Matmul2(Ye,adjYeme2,OnlyDiagonal) 
 YeadjYeYe = Matmul2(Ye,adjYeYe,OnlyDiagonal) 
 YeadjYeTe = Matmul2(Ye,adjYeTe,OnlyDiagonal) 
 Yumq2adjYu = Matmul2(Yu,mq2adjYu,OnlyDiagonal) 
Forall(i2=1:3)  Yumq2adjYu(i2,i2) =  Real(Yumq2adjYu(i2,i2),dp) 
 YuadjYdYd = Matmul2(Yu,adjYdYd,OnlyDiagonal) 
 YuadjYdTd = Matmul2(Yu,adjYdTd,OnlyDiagonal) 
 YuadjYumu2 = Matmul2(Yu,adjYumu2,OnlyDiagonal) 
 YuadjYuYu = Matmul2(Yu,adjYuYu,OnlyDiagonal) 
 YuadjYuTu = Matmul2(Yu,adjYuTu,OnlyDiagonal) 
 adjYdmd2Yd = Matmul2(adjYd,md2Yd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdmd2Yd(i2,i2) =  Real(adjYdmd2Yd(i2,i2),dp) 
 adjYdYdmq2 = Matmul2(adjYd,Ydmq2,OnlyDiagonal) 
 adjYeme2Ye = Matmul2(adjYe,me2Ye,OnlyDiagonal) 
Forall(i2=1:3)  adjYeme2Ye(i2,i2) =  Real(adjYeme2Ye(i2,i2),dp) 
 adjYeYeml2 = Matmul2(adjYe,Yeml2,OnlyDiagonal) 
 adjYumu2Yu = Matmul2(adjYu,mu2Yu,OnlyDiagonal) 
Forall(i2=1:3)  adjYumu2Yu(i2,i2) =  Real(adjYumu2Yu(i2,i2),dp) 
 adjYuYumq2 = Matmul2(adjYu,Yumq2,OnlyDiagonal) 
 TdadjYdYd = Matmul2(Td,adjYdYd,OnlyDiagonal) 
 TdadjYuYu = Matmul2(Td,adjYuYu,OnlyDiagonal) 
 TeadjYeYe = Matmul2(Te,adjYeYe,OnlyDiagonal) 
 TuadjYdYd = Matmul2(Tu,adjYdYd,OnlyDiagonal) 
 TuadjYuYu = Matmul2(Tu,adjYuYu,OnlyDiagonal) 
 Trmd2 = Real(cTrace(md2),dp) 
 Trme2 = Real(cTrace(me2),dp) 
 Trml2 = Real(cTrace(ml2),dp) 
 Trmq2 = Real(cTrace(mq2),dp) 
 Trmu2 = Real(cTrace(mu2),dp) 
 TrYdadjYd = Real(cTrace(YdadjYd),dp) 
 TrYeadjYe = Real(cTrace(YeadjYe),dp) 
 TrYuadjYu = Real(cTrace(YuadjYu),dp) 
 TradjYdTd = Real(cTrace(adjYdTd),dp) 
 TradjYeTe = Real(cTrace(adjYeTe),dp) 
 TradjYuTu = Real(cTrace(adjYuTu),dp) 
 TrCTdTpTd = Real(cTrace(CTdTpTd),dp) 
 TrCTeTpTe = Real(cTrace(CTeTpTe),dp) 
 TrCTuTpTu = Real(cTrace(CTuTpTu),dp) 
 Trmd2YdadjYd = Real(cTrace(md2YdadjYd),dp) 
 Trme2YeadjYe = Real(cTrace(me2YeadjYe),dp) 
 Trml2adjYeYe = Real(cTrace(ml2adjYeYe),dp) 
 Trmq2adjYdYd = Real(cTrace(mq2adjYdYd),dp) 
 Trmq2adjYuYu = Real(cTrace(mq2adjYuYu),dp) 
 Trmu2YuadjYu = Real(cTrace(mu2YuadjYu),dp) 
 sqrt3ov5 =Sqrt(3._dp/5._dp) 
 ooSqrt15 =1._dp/sqrt(15._dp) 
 g1p2 =g1**2 
 g1p3 =g1**3 
 g2p2 =g2**2 
 g2p3 =g2**3 
 g3p2 =g3**2 
 g3p3 =g3**3 
 sqrt15 =sqrt(15._dp) 
 g1p4 =g1**4 
 g2p4 =g2**4 
 g3p4 =g3**4 
 Xip2 =Xi**2 


If (TwoLoopRGE) Then 
 YdadjYu = Matmul2(Yd,adjYu,OnlyDiagonal) 
 YdadjTd = Matmul2(Yd,adjTd,OnlyDiagonal) 
 YdadjTu = Matmul2(Yd,adjTu,OnlyDiagonal) 
 YeadjTe = Matmul2(Ye,adjTe,OnlyDiagonal) 
 YuadjYd = Matmul2(Yu,adjYd,OnlyDiagonal) 
 YuadjTd = Matmul2(Yu,adjTd,OnlyDiagonal) 
 YuadjTu = Matmul2(Yu,adjTu,OnlyDiagonal) 
 adjYdCmd2 = Matmul2(adjYd,Conjg(md2),OnlyDiagonal) 
 adjYeCme2 = Matmul2(adjYe,Conjg(me2),OnlyDiagonal) 
 adjYuCmu2 = Matmul2(adjYu,Conjg(mu2),OnlyDiagonal) 
 adjTdYd = Matmul2(adjTd,Yd,OnlyDiagonal) 
 adjTeYe = Matmul2(adjTe,Ye,OnlyDiagonal) 
 adjTuYu = Matmul2(adjTu,Yu,OnlyDiagonal) 
 Cml2adjYe = Matmul2(Conjg(ml2),adjYe,OnlyDiagonal) 
 Cmq2adjYd = Matmul2(Conjg(mq2),adjYd,OnlyDiagonal) 
 Cmq2adjYu = Matmul2(Conjg(mq2),adjYu,OnlyDiagonal) 
 CTdTpYd = Matmul2(Conjg(Td),Transpose(Yd),OnlyDiagonal) 
 CTeTpYe = Matmul2(Conjg(Te),Transpose(Ye),OnlyDiagonal) 
 CTuTpYu = Matmul2(Conjg(Tu),Transpose(Yu),OnlyDiagonal) 
 TdadjYd = Matmul2(Td,adjYd,OnlyDiagonal) 
 TdadjYu = Matmul2(Td,adjYu,OnlyDiagonal) 
 TdadjTu = Matmul2(Td,adjTu,OnlyDiagonal) 
 TeadjYe = Matmul2(Te,adjYe,OnlyDiagonal) 
 TuadjYd = Matmul2(Tu,adjYd,OnlyDiagonal) 
 TuadjYu = Matmul2(Tu,adjYu,OnlyDiagonal) 
 TuadjTd = Matmul2(Tu,adjTd,OnlyDiagonal) 
 md2YdadjYu = Matmul2(md2,YdadjYu,OnlyDiagonal) 
 mu2YuadjYd = Matmul2(mu2,YuadjYd,OnlyDiagonal) 
 Ydmq2adjYu = Matmul2(Yd,mq2adjYu,OnlyDiagonal) 
 YdadjYdCmd2 = Matmul2(Yd,adjYdCmd2,OnlyDiagonal) 
 YdadjYumu2 = Matmul2(Yd,adjYumu2,OnlyDiagonal) 
 YdadjTdTd = Matmul2(Yd,adjTdTd,OnlyDiagonal) 
 YdCmq2adjYd = Matmul2(Yd,Cmq2adjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdCmq2adjYd(i2,i2) =  Real(YdCmq2adjYd(i2,i2),dp) 
 YeadjYeCme2 = Matmul2(Ye,adjYeCme2,OnlyDiagonal) 
 YeadjTeTe = Matmul2(Ye,adjTeTe,OnlyDiagonal) 
 YeCml2adjYe = Matmul2(Ye,Cml2adjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeCml2adjYe(i2,i2) =  Real(YeCml2adjYe(i2,i2),dp) 
 Yumq2adjYd = Matmul2(Yu,mq2adjYd,OnlyDiagonal) 
 YuadjYdmd2 = Matmul2(Yu,adjYdmd2,OnlyDiagonal) 
 YuadjYuCmu2 = Matmul2(Yu,adjYuCmu2,OnlyDiagonal) 
 YuadjTuTu = Matmul2(Yu,adjTuTu,OnlyDiagonal) 
 YuCmq2adjYu = Matmul2(Yu,Cmq2adjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuCmq2adjYu(i2,i2) =  Real(YuCmq2adjYu(i2,i2),dp) 
 adjYdYdadjYd = Matmul2(adjYd,YdadjYd,OnlyDiagonal) 
 adjYdYdadjYu = Matmul2(adjYd,YdadjYu,OnlyDiagonal) 
 adjYdYdadjTd = Matmul2(adjYd,YdadjTd,OnlyDiagonal) 
 adjYdYdadjTu = Matmul2(adjYd,YdadjTu,OnlyDiagonal) 
 adjYdTdadjYd = Matmul2(adjYd,TdadjYd,OnlyDiagonal) 
 adjYdTdadjYu = Matmul2(adjYd,TdadjYu,OnlyDiagonal) 
 adjYdTdadjTd = Matmul2(adjYd,TdadjTd,OnlyDiagonal) 
 adjYdTdadjTu = Matmul2(adjYd,TdadjTu,OnlyDiagonal) 
 adjYeYeadjYe = Matmul2(adjYe,YeadjYe,OnlyDiagonal) 
 adjYeYeadjTe = Matmul2(adjYe,YeadjTe,OnlyDiagonal) 
 adjYeTeadjYe = Matmul2(adjYe,TeadjYe,OnlyDiagonal) 
 adjYeTeadjTe = Matmul2(adjYe,TeadjTe,OnlyDiagonal) 
 adjYuYuadjYd = Matmul2(adjYu,YuadjYd,OnlyDiagonal) 
 adjYuYuadjYu = Matmul2(adjYu,YuadjYu,OnlyDiagonal) 
 adjYuYuadjTd = Matmul2(adjYu,YuadjTd,OnlyDiagonal) 
 adjYuYuadjTu = Matmul2(adjYu,YuadjTu,OnlyDiagonal) 
 adjYuTuadjYd = Matmul2(adjYu,TuadjYd,OnlyDiagonal) 
 adjYuTuadjYu = Matmul2(adjYu,TuadjYu,OnlyDiagonal) 
 adjYuTuadjTd = Matmul2(adjYu,TuadjTd,OnlyDiagonal) 
 adjYuTuadjTu = Matmul2(adjYu,TuadjTu,OnlyDiagonal) 
 adjTdYdadjYd = Matmul2(adjTd,YdadjYd,OnlyDiagonal) 
 adjTdYdadjYu = Matmul2(adjTd,YdadjYu,OnlyDiagonal) 
 adjTdTdadjYd = Matmul2(adjTd,TdadjYd,OnlyDiagonal) 
 adjTdTdadjYu = Matmul2(adjTd,TdadjYu,OnlyDiagonal) 
 adjTeYeadjYe = Matmul2(adjTe,YeadjYe,OnlyDiagonal) 
 adjTeTeadjYe = Matmul2(adjTe,TeadjYe,OnlyDiagonal) 
 adjTuYuadjYd = Matmul2(adjTu,YuadjYd,OnlyDiagonal) 
 adjTuYuadjYu = Matmul2(adjTu,YuadjYu,OnlyDiagonal) 
 adjTuTuadjYd = Matmul2(adjTu,TuadjYd,OnlyDiagonal) 
 adjTuTuadjYu = Matmul2(adjTu,TuadjYu,OnlyDiagonal) 
 TdadjTdYd = Matmul2(Td,adjTdYd,OnlyDiagonal) 
 TeadjTeYe = Matmul2(Te,adjTeYe,OnlyDiagonal) 
 TuadjTuYu = Matmul2(Tu,adjTuYu,OnlyDiagonal) 
 md2YdadjYdYd = Matmul2(md2,YdadjYdYd,OnlyDiagonal) 
 me2YeadjYeYe = Matmul2(me2,YeadjYeYe,OnlyDiagonal) 
 ml2adjYeYeadjYe = Matmul2(ml2,adjYeYeadjYe,OnlyDiagonal) 
 mq2adjYdYdadjYd = Matmul2(mq2,adjYdYdadjYd,OnlyDiagonal) 
 mq2adjYdYdadjYu = Matmul2(mq2,adjYdYdadjYu,OnlyDiagonal) 
 mq2adjYuYuadjYd = Matmul2(mq2,adjYuYuadjYd,OnlyDiagonal) 
 mq2adjYuYuadjYu = Matmul2(mq2,adjYuYuadjYu,OnlyDiagonal) 
 mu2YuadjYuYu = Matmul2(mu2,YuadjYuYu,OnlyDiagonal) 
 Ydmq2adjYdYd = Matmul2(Yd,mq2adjYdYd,OnlyDiagonal) 
 YdadjYdmd2Yd = Matmul2(Yd,adjYdmd2Yd,OnlyDiagonal) 
 YdadjYdYdmq2 = Matmul2(Yd,adjYdYdmq2,OnlyDiagonal) 
 YdadjYdYdadjYd = Matmul2(Yd,adjYdYdadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYd(i2,i2),dp) 
 YdadjYdTdadjYd = Matmul2(Yd,adjYdTdadjYd,OnlyDiagonal) 
 YdadjYdTdadjTd = Matmul2(Yd,adjYdTdadjTd,OnlyDiagonal) 
 YdadjYuYuadjYd = Matmul2(Yd,adjYuYuadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYd(i2,i2),dp) 
 YdadjYuTuadjYd = Matmul2(Yd,adjYuTuadjYd,OnlyDiagonal) 
 YdadjYuTuadjTd = Matmul2(Yd,adjYuTuadjTd,OnlyDiagonal) 
 YdadjTdTdadjYd = Matmul2(Yd,adjTdTdadjYd,OnlyDiagonal) 
 YdadjTuTuadjYd = Matmul2(Yd,adjTuTuadjYd,OnlyDiagonal) 
 Yeml2adjYeYe = Matmul2(Ye,ml2adjYeYe,OnlyDiagonal) 
 YeadjYeme2Ye = Matmul2(Ye,adjYeme2Ye,OnlyDiagonal) 
 YeadjYeYeml2 = Matmul2(Ye,adjYeYeml2,OnlyDiagonal) 
 YeadjYeYeadjYe = Matmul2(Ye,adjYeYeadjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYe(i2,i2),dp) 
 YeadjYeTeadjYe = Matmul2(Ye,adjYeTeadjYe,OnlyDiagonal) 
 YeadjYeTeadjTe = Matmul2(Ye,adjYeTeadjTe,OnlyDiagonal) 
 YeadjTeTeadjYe = Matmul2(Ye,adjTeTeadjYe,OnlyDiagonal) 
 Yumq2adjYuYu = Matmul2(Yu,mq2adjYuYu,OnlyDiagonal) 
 YuadjYdYdadjYu = Matmul2(Yu,adjYdYdadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYdYdadjYu(i2,i2) =  Real(YuadjYdYdadjYu(i2,i2),dp) 
 YuadjYdTdadjYu = Matmul2(Yu,adjYdTdadjYu,OnlyDiagonal) 
 YuadjYdTdadjTu = Matmul2(Yu,adjYdTdadjTu,OnlyDiagonal) 
 YuadjYumu2Yu = Matmul2(Yu,adjYumu2Yu,OnlyDiagonal) 
 YuadjYuYumq2 = Matmul2(Yu,adjYuYumq2,OnlyDiagonal) 
 YuadjYuYuadjYu = Matmul2(Yu,adjYuYuadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYu(i2,i2),dp) 
 YuadjYuTuadjYu = Matmul2(Yu,adjYuTuadjYu,OnlyDiagonal) 
 YuadjYuTuadjTu = Matmul2(Yu,adjYuTuadjTu,OnlyDiagonal) 
 YuadjTdTdadjYu = Matmul2(Yu,adjTdTdadjYu,OnlyDiagonal) 
 YuadjTuTuadjYu = Matmul2(Yu,adjTuTuadjYu,OnlyDiagonal) 
 adjYdmd2YdadjYd = Matmul2(adjYd,md2YdadjYd,OnlyDiagonal) 
 adjYdmd2YdadjYu = Matmul2(adjYd,md2YdadjYu,OnlyDiagonal) 
 adjYdYdmq2adjYd = Matmul2(adjYd,Ydmq2adjYd,OnlyDiagonal) 
 adjYdYdmq2adjYu = Matmul2(adjYd,Ydmq2adjYu,OnlyDiagonal) 
 adjYdYdadjYdmd2 = Matmul2(adjYd,YdadjYdmd2,OnlyDiagonal) 
 adjYdYdadjYdYd = Matmul2(adjYd,YdadjYdYd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYdadjYdYd(i2,i2) =  Real(adjYdYdadjYdYd(i2,i2),dp) 
 adjYdYdadjYdTd = Matmul2(adjYd,YdadjYdTd,OnlyDiagonal) 
 adjYdYdadjYumu2 = Matmul2(adjYd,YdadjYumu2,OnlyDiagonal) 
 adjYdYdadjYuYu = Matmul2(adjYd,YdadjYuYu,OnlyDiagonal) 
 adjYdYdadjYuTu = Matmul2(adjYd,YdadjYuTu,OnlyDiagonal) 
 adjYdYdadjTdTd = Matmul2(adjYd,YdadjTdTd,OnlyDiagonal) 
 adjYdTdadjYdYd = Matmul2(adjYd,TdadjYdYd,OnlyDiagonal) 
 adjYdTdadjYuYu = Matmul2(adjYd,TdadjYuYu,OnlyDiagonal) 
 adjYdTdadjTdYd = Matmul2(adjYd,TdadjTdYd,OnlyDiagonal) 
 adjYeme2YeadjYe = Matmul2(adjYe,me2YeadjYe,OnlyDiagonal) 
 adjYeYeml2adjYe = Matmul2(adjYe,Yeml2adjYe,OnlyDiagonal) 
 adjYeYeadjYeme2 = Matmul2(adjYe,YeadjYeme2,OnlyDiagonal) 
 adjYeYeadjYeYe = Matmul2(adjYe,YeadjYeYe,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYeadjYeYe(i2,i2) =  Real(adjYeYeadjYeYe(i2,i2),dp) 
 adjYeYeadjYeTe = Matmul2(adjYe,YeadjYeTe,OnlyDiagonal) 
 adjYeYeadjTeTe = Matmul2(adjYe,YeadjTeTe,OnlyDiagonal) 
 adjYeTeadjYeYe = Matmul2(adjYe,TeadjYeYe,OnlyDiagonal) 
 adjYeTeadjTeYe = Matmul2(adjYe,TeadjTeYe,OnlyDiagonal) 
 adjYumu2YuadjYd = Matmul2(adjYu,mu2YuadjYd,OnlyDiagonal) 
 adjYumu2YuadjYu = Matmul2(adjYu,mu2YuadjYu,OnlyDiagonal) 
 adjYuYumq2adjYd = Matmul2(adjYu,Yumq2adjYd,OnlyDiagonal) 
 adjYuYumq2adjYu = Matmul2(adjYu,Yumq2adjYu,OnlyDiagonal) 
 adjYuYuadjYdmd2 = Matmul2(adjYu,YuadjYdmd2,OnlyDiagonal) 
 adjYuYuadjYdYd = Matmul2(adjYu,YuadjYdYd,OnlyDiagonal) 
 adjYuYuadjYdTd = Matmul2(adjYu,YuadjYdTd,OnlyDiagonal) 
 adjYuYuadjYumu2 = Matmul2(adjYu,YuadjYumu2,OnlyDiagonal) 
 adjYuYuadjYuYu = Matmul2(adjYu,YuadjYuYu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYuadjYuYu(i2,i2) =  Real(adjYuYuadjYuYu(i2,i2),dp) 
 adjYuYuadjYuTu = Matmul2(adjYu,YuadjYuTu,OnlyDiagonal) 
 adjYuYuadjTuTu = Matmul2(adjYu,YuadjTuTu,OnlyDiagonal) 
 adjYuTuadjYdYd = Matmul2(adjYu,TuadjYdYd,OnlyDiagonal) 
 adjYuTuadjYuYu = Matmul2(adjYu,TuadjYuYu,OnlyDiagonal) 
 adjYuTuadjTuYu = Matmul2(adjYu,TuadjTuYu,OnlyDiagonal) 
 adjTdYdadjYdTd = Matmul2(adjTd,YdadjYdTd,OnlyDiagonal) 
 adjTdTdadjYdYd = Matmul2(adjTd,TdadjYdYd,OnlyDiagonal) 
 adjTeYeadjYeTe = Matmul2(adjTe,YeadjYeTe,OnlyDiagonal) 
 adjTeTeadjYeYe = Matmul2(adjTe,TeadjYeYe,OnlyDiagonal) 
 adjTuYuadjYuTu = Matmul2(adjTu,YuadjYuTu,OnlyDiagonal) 
 adjTuTuadjYuYu = Matmul2(adjTu,TuadjYuYu,OnlyDiagonal) 
 TdadjYdYdadjTd = Matmul2(Td,adjYdYdadjTd,OnlyDiagonal) 
 TdadjYuYuadjTd = Matmul2(Td,adjYuYuadjTd,OnlyDiagonal) 
 TdadjTdYdadjYd = Matmul2(Td,adjTdYdadjYd,OnlyDiagonal) 
 TdadjTuYuadjYd = Matmul2(Td,adjTuYuadjYd,OnlyDiagonal) 
 TeadjYeYeadjTe = Matmul2(Te,adjYeYeadjTe,OnlyDiagonal) 
 TeadjTeYeadjYe = Matmul2(Te,adjTeYeadjYe,OnlyDiagonal) 
 TuadjYdYdadjTu = Matmul2(Tu,adjYdYdadjTu,OnlyDiagonal) 
 TuadjYuYuadjTu = Matmul2(Tu,adjYuYuadjTu,OnlyDiagonal) 
 TuadjTdYdadjYu = Matmul2(Tu,adjTdYdadjYu,OnlyDiagonal) 
 TuadjTuYuadjYu = Matmul2(Tu,adjTuYuadjYu,OnlyDiagonal) 
 md2YdadjYdYdadjYd = Matmul2(md2,YdadjYdYdadjYd,OnlyDiagonal) 
 md2YdadjYuYuadjYd = Matmul2(md2,YdadjYuYuadjYd,OnlyDiagonal) 
 me2YeadjYeYeadjYe = Matmul2(me2,YeadjYeYeadjYe,OnlyDiagonal) 
 ml2adjYeYeadjYeYe = Matmul2(ml2,adjYeYeadjYeYe,OnlyDiagonal) 
 mq2adjYdYdadjYdYd = Matmul2(mq2,adjYdYdadjYdYd,OnlyDiagonal) 
 mq2adjYdYdadjYuYu = Matmul2(mq2,adjYdYdadjYuYu,OnlyDiagonal) 
 mq2adjYuYuadjYdYd = Matmul2(mq2,adjYuYuadjYdYd,OnlyDiagonal) 
 mq2adjYuYuadjYuYu = Matmul2(mq2,adjYuYuadjYuYu,OnlyDiagonal) 
 mu2YuadjYdYdadjYu = Matmul2(mu2,YuadjYdYdadjYu,OnlyDiagonal) 
 mu2YuadjYuYuadjYu = Matmul2(mu2,YuadjYuYuadjYu,OnlyDiagonal) 
 Ydmq2adjYdYdadjYd = Matmul2(Yd,mq2adjYdYdadjYd,OnlyDiagonal) 
 Ydmq2adjYuYuadjYd = Matmul2(Yd,mq2adjYuYuadjYd,OnlyDiagonal) 
 YdadjYdmd2YdadjYd = Matmul2(Yd,adjYdmd2YdadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYdmd2YdadjYd(i2,i2) =  Real(YdadjYdmd2YdadjYd(i2,i2),dp) 
 YdadjYdYdmq2adjYd = Matmul2(Yd,adjYdYdmq2adjYd,OnlyDiagonal) 
 YdadjYdYdadjYdmd2 = Matmul2(Yd,adjYdYdadjYdmd2,OnlyDiagonal) 
 YdadjYdYdadjYdYd = Matmul2(Yd,adjYdYdadjYdYd,OnlyDiagonal) 
 YdadjYdYdadjYdTd = Matmul2(Yd,adjYdYdadjYdTd,OnlyDiagonal) 
 YdadjYdTdadjYdYd = Matmul2(Yd,adjYdTdadjYdYd,OnlyDiagonal) 
 YdadjYumu2YuadjYd = Matmul2(Yd,adjYumu2YuadjYd,OnlyDiagonal) 
Forall(i2=1:3)  YdadjYumu2YuadjYd(i2,i2) =  Real(YdadjYumu2YuadjYd(i2,i2),dp) 
 YdadjYuYumq2adjYd = Matmul2(Yd,adjYuYumq2adjYd,OnlyDiagonal) 
 YdadjYuYuadjYdmd2 = Matmul2(Yd,adjYuYuadjYdmd2,OnlyDiagonal) 
 YdadjYuYuadjYdYd = Matmul2(Yd,adjYuYuadjYdYd,OnlyDiagonal) 
 YdadjYuYuadjYdTd = Matmul2(Yd,adjYuYuadjYdTd,OnlyDiagonal) 
 YdadjYuYuadjYuYu = Matmul2(Yd,adjYuYuadjYuYu,OnlyDiagonal) 
 YdadjYuYuadjYuTu = Matmul2(Yd,adjYuYuadjYuTu,OnlyDiagonal) 
 YdadjYuTuadjYdYd = Matmul2(Yd,adjYuTuadjYdYd,OnlyDiagonal) 
 YdadjYuTuadjYuYu = Matmul2(Yd,adjYuTuadjYuYu,OnlyDiagonal) 
 Yeml2adjYeYeadjYe = Matmul2(Ye,ml2adjYeYeadjYe,OnlyDiagonal) 
 YeadjYeme2YeadjYe = Matmul2(Ye,adjYeme2YeadjYe,OnlyDiagonal) 
Forall(i2=1:3)  YeadjYeme2YeadjYe(i2,i2) =  Real(YeadjYeme2YeadjYe(i2,i2),dp) 
 YeadjYeYeml2adjYe = Matmul2(Ye,adjYeYeml2adjYe,OnlyDiagonal) 
 YeadjYeYeadjYeme2 = Matmul2(Ye,adjYeYeadjYeme2,OnlyDiagonal) 
 YeadjYeYeadjYeYe = Matmul2(Ye,adjYeYeadjYeYe,OnlyDiagonal) 
 YeadjYeYeadjYeTe = Matmul2(Ye,adjYeYeadjYeTe,OnlyDiagonal) 
 YeadjYeTeadjYeYe = Matmul2(Ye,adjYeTeadjYeYe,OnlyDiagonal) 
 Yumq2adjYdYdadjYu = Matmul2(Yu,mq2adjYdYdadjYu,OnlyDiagonal) 
 Yumq2adjYuYuadjYu = Matmul2(Yu,mq2adjYuYuadjYu,OnlyDiagonal) 
 YuadjYdmd2YdadjYu = Matmul2(Yu,adjYdmd2YdadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYdmd2YdadjYu(i2,i2) =  Real(YuadjYdmd2YdadjYu(i2,i2),dp) 
 YuadjYdYdmq2adjYu = Matmul2(Yu,adjYdYdmq2adjYu,OnlyDiagonal) 
 YuadjYdYdadjYdYd = Matmul2(Yu,adjYdYdadjYdYd,OnlyDiagonal) 
 YuadjYdYdadjYdTd = Matmul2(Yu,adjYdYdadjYdTd,OnlyDiagonal) 
 YuadjYdYdadjYumu2 = Matmul2(Yu,adjYdYdadjYumu2,OnlyDiagonal) 
 YuadjYdYdadjYuYu = Matmul2(Yu,adjYdYdadjYuYu,OnlyDiagonal) 
 YuadjYdYdadjYuTu = Matmul2(Yu,adjYdYdadjYuTu,OnlyDiagonal) 
 YuadjYdTdadjYdYd = Matmul2(Yu,adjYdTdadjYdYd,OnlyDiagonal) 
 YuadjYdTdadjYuYu = Matmul2(Yu,adjYdTdadjYuYu,OnlyDiagonal) 
 YuadjYumu2YuadjYu = Matmul2(Yu,adjYumu2YuadjYu,OnlyDiagonal) 
Forall(i2=1:3)  YuadjYumu2YuadjYu(i2,i2) =  Real(YuadjYumu2YuadjYu(i2,i2),dp) 
 YuadjYuYumq2adjYu = Matmul2(Yu,adjYuYumq2adjYu,OnlyDiagonal) 
 YuadjYuYuadjYumu2 = Matmul2(Yu,adjYuYuadjYumu2,OnlyDiagonal) 
 YuadjYuYuadjYuYu = Matmul2(Yu,adjYuYuadjYuYu,OnlyDiagonal) 
 YuadjYuYuadjYuTu = Matmul2(Yu,adjYuYuadjYuTu,OnlyDiagonal) 
 YuadjYuTuadjYuYu = Matmul2(Yu,adjYuTuadjYuYu,OnlyDiagonal) 
 adjYdmd2YdadjYdYd = Matmul2(adjYd,md2YdadjYdYd,OnlyDiagonal) 
 adjYdYdmq2adjYdYd = Matmul2(adjYd,Ydmq2adjYdYd,OnlyDiagonal) 
Forall(i2=1:3)  adjYdYdmq2adjYdYd(i2,i2) =  Real(adjYdYdmq2adjYdYd(i2,i2),dp) 
 adjYdYdadjYdmd2Yd = Matmul2(adjYd,YdadjYdmd2Yd,OnlyDiagonal) 
 adjYdYdadjYdYdmq2 = Matmul2(adjYd,YdadjYdYdmq2,OnlyDiagonal) 
 adjYeme2YeadjYeYe = Matmul2(adjYe,me2YeadjYeYe,OnlyDiagonal) 
 adjYeYeml2adjYeYe = Matmul2(adjYe,Yeml2adjYeYe,OnlyDiagonal) 
Forall(i2=1:3)  adjYeYeml2adjYeYe(i2,i2) =  Real(adjYeYeml2adjYeYe(i2,i2),dp) 
 adjYeYeadjYeme2Ye = Matmul2(adjYe,YeadjYeme2Ye,OnlyDiagonal) 
 adjYeYeadjYeYeml2 = Matmul2(adjYe,YeadjYeYeml2,OnlyDiagonal) 
 adjYumu2YuadjYuYu = Matmul2(adjYu,mu2YuadjYuYu,OnlyDiagonal) 
 adjYuYumq2adjYuYu = Matmul2(adjYu,Yumq2adjYuYu,OnlyDiagonal) 
Forall(i2=1:3)  adjYuYumq2adjYuYu(i2,i2) =  Real(adjYuYumq2adjYuYu(i2,i2),dp) 
 adjYuYuadjYumu2Yu = Matmul2(adjYu,YuadjYumu2Yu,OnlyDiagonal) 
 adjYuYuadjYuYumq2 = Matmul2(adjYu,YuadjYuYumq2,OnlyDiagonal) 
 TdadjYdYdadjYdYd = Matmul2(Td,adjYdYdadjYdYd,OnlyDiagonal) 
 TdadjYuYuadjYdYd = Matmul2(Td,adjYuYuadjYdYd,OnlyDiagonal) 
 TdadjYuYuadjYuYu = Matmul2(Td,adjYuYuadjYuYu,OnlyDiagonal) 
 TeadjYeYeadjYeYe = Matmul2(Te,adjYeYeadjYeYe,OnlyDiagonal) 
 TuadjYdYdadjYdYd = Matmul2(Tu,adjYdYdadjYdYd,OnlyDiagonal) 
 TuadjYdYdadjYuYu = Matmul2(Tu,adjYdYdadjYuYu,OnlyDiagonal) 
 TuadjYuYuadjYuYu = Matmul2(Tu,adjYuYuadjYuYu,OnlyDiagonal) 
 TrCTdTpYd = cTrace(CTdTpYd) 
 TrCTeTpYe = cTrace(CTeTpYe) 
 TrCTuTpYu = cTrace(CTuTpYu) 
 TrYdadjYdCmd2 = cTrace(YdadjYdCmd2) 
 TrYdCmq2adjYd = cTrace(YdCmq2adjYd) 
 TrYeadjYeCme2 = cTrace(YeadjYeCme2) 
 TrYeCml2adjYe = cTrace(YeCml2adjYe) 
 TrYuadjYuCmu2 = cTrace(YuadjYuCmu2) 
 TrYuCmq2adjYu = cTrace(YuCmq2adjYu) 
 TrYdadjYdYdadjYd = cTrace(YdadjYdYdadjYd) 
 TrYdadjYdTdadjYd = cTrace(YdadjYdTdadjYd) 
 TrYdadjYdTdadjTd = cTrace(YdadjYdTdadjTd) 
 TrYdadjYuYuadjYd = cTrace(YdadjYuYuadjYd) 
 TrYdadjYuTuadjYd = cTrace(YdadjYuTuadjYd) 
 TrYdadjYuTuadjTd = cTrace(YdadjYuTuadjTd) 
 TrYdadjTdTdadjYd = cTrace(YdadjTdTdadjYd) 
 TrYdadjTuTuadjYd = cTrace(YdadjTuTuadjYd) 
 TrYeadjYeYeadjYe = cTrace(YeadjYeYeadjYe) 
 TrYeadjYeTeadjYe = cTrace(YeadjYeTeadjYe) 
 TrYeadjYeTeadjTe = cTrace(YeadjYeTeadjTe) 
 TrYeadjTeTeadjYe = cTrace(YeadjTeTeadjYe) 
 TrYuadjYdTdadjYu = cTrace(YuadjYdTdadjYu) 
 TrYuadjYdTdadjTu = cTrace(YuadjYdTdadjTu) 
 TrYuadjYuYuadjYu = cTrace(YuadjYuYuadjYu) 
 TrYuadjYuTuadjYu = cTrace(YuadjYuTuadjYu) 
 TrYuadjYuTuadjTu = cTrace(YuadjYuTuadjTu) 
 TrYuadjTdTdadjYu = cTrace(YuadjTdTdadjYu) 
 TrYuadjTuTuadjYu = cTrace(YuadjTuTuadjYu) 
 Trmd2YdadjYdYdadjYd = cTrace(md2YdadjYdYdadjYd) 
 Trmd2YdadjYuYuadjYd = cTrace(md2YdadjYuYuadjYd) 
 Trme2YeadjYeYeadjYe = cTrace(me2YeadjYeYeadjYe) 
 Trml2adjYeYeadjYeYe = cTrace(ml2adjYeYeadjYeYe) 
 Trmq2adjYdYdadjYdYd = cTrace(mq2adjYdYdadjYdYd) 
 Trmq2adjYdYdadjYuYu = cTrace(mq2adjYdYdadjYuYu) 
 Trmq2adjYuYuadjYdYd = cTrace(mq2adjYuYuadjYdYd) 
 Trmq2adjYuYuadjYuYu = cTrace(mq2adjYuYuadjYuYu) 
 Trmu2YuadjYdYdadjYu = cTrace(mu2YuadjYdYdadjYu) 
 Trmu2YuadjYuYuadjYu = cTrace(mu2YuadjYuYuadjYu) 
 sqrt15 =sqrt(15._dp) 
 g1p4 =g1**4 
 g2p4 =g2**4 
 g3p4 =g3**4 
 Xip2 =Xi**2 
End If 
 
 
Tr1(1) = g1*sqrt3ov5*(-1._dp*(mHd2) + mHu2 + Trmd2 + Trme2 - Trml2 + Trmq2 -          & 
&  2._dp*(Trmu2))

If (TwoLoopRGE) Then 
Tr2U1(1, 1) = (g1p2*(3._dp*(mHd2) + 3._dp*(mHu2) + 2._dp*(Trmd2) + 6._dp*(Trme2)      & 
&  + 3._dp*(Trml2) + Trmq2 + 8._dp*(Trmu2)))/10._dp

Tr3(1) = (g1*ooSqrt15*(-9*g1p2*mHd2 - 45*g2p2*mHd2 + 9*g1p2*mHu2 + 45*g2p2*mHu2 +     & 
&  4*(g1p2 + 20._dp*(g3p2))*Trmd2 + 36*g1p2*Trme2 - 9*g1p2*Trml2 - 45*g2p2*Trml2 +       & 
&  g1p2*Trmq2 + 45*g2p2*Trmq2 + 80*g3p2*Trmq2 - 32*g1p2*Trmu2 - 160*g3p2*Trmu2 +         & 
&  90*mHd2*TrYdadjYd - 60._dp*(TrYdadjYdCmd2) - 30._dp*(TrYdCmq2adjYd) + 30*mHd2*TrYeadjYe -& 
&  60._dp*(TrYeadjYeCme2) + 30._dp*(TrYeCml2adjYe) - 90*mHu2*TrYuadjYu + 120._dp*(TrYuadjYuCmu2)& 
&  - 30._dp*(TrYuCmq2adjYu)))/20._dp

Tr2(2) = (mHd2 + mHu2 + Trml2 + 3._dp*(Trmq2))/2._dp

Tr2(3) = (Trmd2 + 2._dp*(Trmq2) + Trmu2)/2._dp

End If 
 
 
!-------------------- 
! g1 
!-------------------- 
 
betag11  = 33._dp*(g1p3)/5._dp

 
 
If (TwoLoopRGE) Then 
betag12 = (g1p3*(199._dp*(g1p2) + 135._dp*(g2p2) + 440._dp*(g3p2) - 70._dp*(TrYdadjYd) -        & 
&  90._dp*(TrYeadjYe) - 130._dp*(TrYuadjYu)))/25._dp

 
Dg1 = oo16pi2*( betag11 + oo16pi2 * betag12 ) 

 
Else 
Dg1 = oo16pi2* betag11 
End If 
 
 
!-------------------- 
! g2 
!-------------------- 
 
betag21  = g2p3

 
 
If (TwoLoopRGE) Then 
betag22 = (g2p3*(9._dp*(g1p2) + 125._dp*(g2p2) + 120._dp*(g3p2) - 30._dp*(TrYdadjYd) -          & 
&  10._dp*(TrYeadjYe) - 30._dp*(TrYuadjYu)))/5._dp

 
Dg2 = oo16pi2*( betag21 + oo16pi2 * betag22 ) 

 
Else 
Dg2 = oo16pi2* betag21 
End If 
 
 
!-------------------- 
! g3 
!-------------------- 
 
betag31  = -3._dp*(g3p3)

 
 
If (TwoLoopRGE) Then 
betag32 = (g3p3*(11._dp*(g1p2) + 45._dp*(g2p2) + 70._dp*(g3p2) - 20._dp*(TrYdadjYd) -           & 
&  20._dp*(TrYuadjYu)))/5._dp

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 ) 

 
Else 
Dg3 = oo16pi2* betag31 
End If 
 
 
!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-7._dp*(g1p2)/15._dp - 3._dp*(g2p2) - 16._dp*(g3p2)/3._dp +               & 
&  3._dp*(TrYdadjYd) + TrYeadjYe)*Yd + 3._dp*(YdadjYdYd) + YdadjYuYu

 
 
If (TwoLoopRGE) Then 
betaYd2 = (287._dp*(g1p4)/90._dp + g1p2*g2p2 + 15._dp*(g2p4)/2._dp + (8*g1p2*g3p2)/9._dp +      & 
&  8*g2p2*g3p2 - 16._dp*(g3p4)/9._dp - (2*(g1p2 - 40._dp*(g3p2))*TrYdadjYd)/5._dp -      & 
&  9._dp*(TrYdadjYdYdadjYd) - 3._dp*(TrYdadjYuYuadjYd) + (6*g1p2*TrYeadjYe)/5._dp -      & 
&  3._dp*(TrYeadjYeYeadjYe))*Yd + (4._dp*(g1p2)/5._dp + 6._dp*(g2p2) - 9._dp*(TrYdadjYd) -& 
&  3._dp*(TrYeadjYe))*YdadjYdYd - 4._dp*(YdadjYdYdadjYdYd) + (4*g1p2*YdadjYuYu)/5._dp -  & 
&  3*TrYuadjYu*YdadjYuYu - 2._dp*(YdadjYuYuadjYdYd) - 2._dp*(YdadjYuYuadjYuYu)

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = (-9._dp*(g1p2)/5._dp - 3._dp*(g2p2) + 3._dp*(TrYdadjYd) + TrYeadjYe)       & 
& *Ye + 3._dp*(YeadjYeYe)

 
 
If (TwoLoopRGE) Then 
betaYe2 = ((-4*(g1p2 - 40._dp*(g3p2))*TrYdadjYd + 3*(45._dp*(g1p4) + 6*g1p2*g2p2 +              & 
&  25._dp*(g2p4) - 30._dp*(TrYdadjYdYdadjYd) - 10._dp*(TrYdadjYuYuadjYd) +               & 
&  4*g1p2*TrYeadjYe - 10._dp*(TrYeadjYeYeadjYe)))*Ye)/10._dp + (6._dp*(g2p2) -           & 
&  9._dp*(TrYdadjYd) - 3._dp*(TrYeadjYe))*YeadjYeYe - 4._dp*(YeadjYeYeadjYeYe)

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = -((13._dp*(g1p2) + 45._dp*(g2p2) + 80._dp*(g3p2) - 45._dp*(TrYuadjYu))     & 
& *Yu)/15._dp + YuadjYdYd + 3._dp*(YuadjYuYu)

 
 
If (TwoLoopRGE) Then 
betaYu2 = (2743._dp*(g1p4)/450._dp + g1p2*g2p2 + 15._dp*(g2p4)/2._dp + (136*g1p2*g3p2)/45._dp + & 
&  8*g2p2*g3p2 - 16._dp*(g3p4)/9._dp - 3._dp*(TrYdadjYuYuadjYd) + (4*(g1p2 +             & 
&  20._dp*(g3p2))*TrYuadjYu)/5._dp - 9._dp*(TrYuadjYuYuadjYu))*Yu + (2._dp*(g1p2)/5._dp -& 
&  3._dp*(TrYdadjYd) - TrYeadjYe)*YuadjYdYd - 2._dp*(YuadjYdYdadjYdYd) - 2._dp*(YuadjYdYdadjYuYu) +& 
&  (2*g1p2*YuadjYuYu)/5._dp + 6*g2p2*YuadjYuYu - 9*TrYuadjYu*YuadjYuYu - 4._dp*(YuadjYuYuadjYuYu)

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! Mu 
!-------------------- 
 
betaMu1  = 3*TrYdadjYd*Mu + TrYeadjYe*Mu - (3*(g1p2 + 5._dp*(g2p2) - 5._dp*(TrYuadjYu))& 
& *Mu)/5._dp

 
 
If (TwoLoopRGE) Then 
betaMu2 = ((207._dp*(g1p4) + 90*g1p2*g2p2 + 375._dp*(g2p4) - 20*(g1p2 - 40._dp*(g3p2))*TrYdadjYd -& 
&  450._dp*(TrYdadjYdYdadjYd) - 300._dp*(TrYdadjYuYuadjYd) + 60*g1p2*TrYeadjYe -         & 
&  150._dp*(TrYeadjYeYeadjYe) + 40*g1p2*TrYuadjYu + 800*g3p2*TrYuadjYu - 450._dp*(TrYuadjYuYuadjYu))*Mu)/50._dp

 
DMu = oo16pi2*( betaMu1 + oo16pi2 * betaMu2 ) 

 
Else 
DMu = oo16pi2* betaMu1 
End If 
 
 
Call Chop(DMu) 

!-------------------- 
! Td 
!-------------------- 
 
betaTd1  = 5._dp*(TdadjYdYd) + TdadjYuYu + ((14*g1p2*M1)/15._dp + (32*g3p2*M3)        & 
& /3._dp + 6*g2p2*M2 + 6._dp*(TradjYdTd) + 2._dp*(TradjYeTe))*Yd + 4._dp*(YdadjYdTd)     & 
&  + 2._dp*(YdadjYuTu) - (7*g1p2*Td)/15._dp - 3*g2p2*Td - (16*g3p2*Td)/3._dp +           & 
&  3*TrYdadjYd*Td + TrYeadjYe*Td

 
 
If (TwoLoopRGE) Then 
betaTd2 = (6*g1p2*TdadjYdYd)/5._dp + 12*g2p2*TdadjYdYd - 6._dp*(TdadjYdYdadjYdYd) +             & 
&  (4*g1p2*TdadjYuYu)/5._dp - 4._dp*(TdadjYuYuadjYdYd) - 2._dp*(TdadjYuYuadjYuYu) -      & 
&  15*TdadjYdYd*TrYdadjYd - 5*TdadjYdYd*TrYeadjYe - 3*TdadjYuYu*TrYuadjYu -              & 
&  (2*(287*g1p4*M1 + 45*g1p2*g2p2*M1 + 40*g1p2*g3p2*M1 + 40*g1p2*g3p2*M3 +               & 
&  360*g2p2*g3p2*M3 - 160*g3p4*M3 + 45*g1p2*g2p2*M2 + 675*g2p4*M2 + 360*g2p2*g3p2*M2 +   & 
&  18*g1p2*TradjYdTd - 720*g3p2*TradjYdTd - 54*g1p2*TradjYeTe - 18*(g1p2*M1 -            & 
&  40*g3p2*M3)*TrYdadjYd + 810._dp*(TrYdadjYdTdadjYd) + 135._dp*(TrYdadjYuTuadjYd) +     & 
&  54*g1p2*M1*TrYeadjYe + 270._dp*(TrYeadjYeTeadjYe) + 135._dp*(TrYuadjYdTdadjYu))*Yd)/45._dp +& 
&  (6*g1p2*YdadjYdTd)/5._dp + 6*g2p2*YdadjYdTd - 12*TrYdadjYd*YdadjYdTd - 4*TrYeadjYe*YdadjYdTd -& 
&  8._dp*(YdadjYdTdadjYdYd) - (2*(4*g1p2*M1 + 30*g2p2*M2 + 45._dp*(TradjYdTd) +          & 
&  15._dp*(TradjYeTe))*YdadjYdYd)/5._dp - 6._dp*(YdadjYdYdadjYdTd) + (8*g1p2*YdadjYuTu)/5._dp -& 
&  6*TrYuadjYu*YdadjYuTu - 4._dp*(YdadjYuTuadjYdYd) - 4._dp*(YdadjYuTuadjYuYu) -         & 
&  (8*g1p2*M1*YdadjYuYu)/5._dp - 6*TradjYuTu*YdadjYuYu - 2._dp*(YdadjYuYuadjYdTd) -      & 
&  4._dp*(YdadjYuYuadjYuTu) + (287*g1p4*Td)/90._dp + g1p2*g2p2*Td + (15*g2p4*Td)/2._dp + & 
&  (8*g1p2*g3p2*Td)/9._dp + 8*g2p2*g3p2*Td - (16*g3p4*Td)/9._dp - (2*g1p2*TrYdadjYd*Td)/5._dp +& 
&  16*g3p2*TrYdadjYd*Td - 9*TrYdadjYdYdadjYd*Td - 3*TrYdadjYuYuadjYd*Td + (6*g1p2*TrYeadjYe*Td)/5._dp -& 
&  3*TrYeadjYeYeadjYe*Td

 
DTd = oo16pi2*( betaTd1 + oo16pi2 * betaTd2 ) 

 
Else 
DTd = oo16pi2* betaTd1 
End If 
 
 
Call Chop(DTd) 

!-------------------- 
! Te 
!-------------------- 
 
betaTe1  = 5._dp*(TeadjYeYe) + ((18*g1p2*M1)/5._dp + 6*g2p2*M2 + 6._dp*(TradjYdTd)    & 
&  + 2._dp*(TradjYeTe))*Ye + 4._dp*(YeadjYeTe) - (9*g1p2*Te)/5._dp - 3*g2p2*Te +         & 
&  3*TrYdadjYd*Te + TrYeadjYe*Te

 
 
If (TwoLoopRGE) Then 
betaTe2 = (-6*g1p2*TeadjYeYe)/5._dp + 12*g2p2*TeadjYeYe - 6._dp*(TeadjYeYeadjYeYe) -            & 
&  15*TeadjYeYe*TrYdadjYd - 5*TeadjYeYe*TrYeadjYe - (2*(135*g1p4*M1 + 9*g1p2*g2p2*M1 +   & 
&  9*g1p2*g2p2*M2 + 75*g2p4*M2 + 2*g1p2*TradjYdTd - 80*g3p2*TradjYdTd - 6*g1p2*TradjYeTe +& 
&  (-2*g1p2*M1 + 80*g3p2*M3)*TrYdadjYd + 90._dp*(TrYdadjYdTdadjYd) + 15._dp*(TrYdadjYuTuadjYd) +& 
&  6*g1p2*M1*TrYeadjYe + 30._dp*(TrYeadjYeTeadjYe) + 15._dp*(TrYuadjYdTdadjYu))*Ye)/5._dp +& 
&  (6*g1p2*YeadjYeTe)/5._dp + 6*g2p2*YeadjYeTe - 12*TrYdadjYd*YeadjYeTe - 4*TrYeadjYe*YeadjYeTe -& 
&  8._dp*(YeadjYeTeadjYeYe) - 6*(2*g2p2*M2 + 3._dp*(TradjYdTd) + TradjYeTe)*YeadjYeYe -  & 
&  6._dp*(YeadjYeYeadjYeTe) + (27*g1p4*Te)/2._dp + (9*g1p2*g2p2*Te)/5._dp +              & 
&  (15*g2p4*Te)/2._dp - (2*g1p2*TrYdadjYd*Te)/5._dp + 16*g3p2*TrYdadjYd*Te -             & 
&  9*TrYdadjYdYdadjYd*Te - 3*TrYdadjYuYuadjYd*Te + (6*g1p2*TrYeadjYe*Te)/5._dp -         & 
&  3*TrYeadjYeYeadjYe*Te

 
DTe = oo16pi2*( betaTe1 + oo16pi2 * betaTe2 ) 

 
Else 
DTe = oo16pi2* betaTe1 
End If 
 
 
Call Chop(DTe) 

!-------------------- 
! Tu 
!-------------------- 
 
betaTu1  = TuadjYdYd + 5._dp*(TuadjYuYu) + ((26*g1p2*M1)/15._dp + (32*g3p2*M3)        & 
& /3._dp + 6*g2p2*M2 + 6._dp*(TradjYuTu))*Yu + 2._dp*(YuadjYdTd) + 4._dp*(YuadjYuTu)     & 
&  - (13*g1p2*Tu)/15._dp - 3*g2p2*Tu - (16*g3p2*Tu)/3._dp + 3*TrYuadjYu*Tu

 
 
If (TwoLoopRGE) Then 
betaTu2 = (2*g1p2*TuadjYdYd)/5._dp - 3*TrYdadjYd*TuadjYdYd - TrYeadjYe*TuadjYdYd -              & 
&  2._dp*(TuadjYdYdadjYdYd) - 4._dp*(TuadjYdYdadjYuYu) + 12*g2p2*TuadjYuYu -             & 
&  15*TrYuadjYu*TuadjYuYu - 6._dp*(TuadjYuYuadjYuYu) - (2*(2743*g1p4*M1 + 225*g1p2*g2p2*M1 +& 
&  680*g1p2*g3p2*M1 + 680*g1p2*g3p2*M3 + 1800*g2p2*g3p2*M3 - 800*g3p4*M3 +               & 
&  225*g1p2*g2p2*M2 + 3375*g2p4*M2 + 1800*g2p2*g3p2*M2 - 180*(g1p2 + 20._dp*(g3p2))*TradjYuTu +& 
&  675._dp*(TrYdadjYuTuadjYd) + 675._dp*(TrYuadjYdTdadjYu) + 180*(g1p2*M1 +              & 
&  20*g3p2*M3)*TrYuadjYu + 4050._dp*(TrYuadjYuTuadjYu))*Yu)/225._dp + (4*g1p2*YuadjYdTd)/5._dp -& 
&  6*TrYdadjYd*YuadjYdTd - 2*TrYeadjYe*YuadjYdTd - 4._dp*(YuadjYdTdadjYdYd) -            & 
&  4._dp*(YuadjYdTdadjYuYu) - (2*(2*g1p2*M1 + 15._dp*(TradjYdTd) + 5._dp*(TradjYeTe))*YuadjYdYd)/5._dp -& 
&  4._dp*(YuadjYdYdadjYdTd) - 2._dp*(YuadjYdYdadjYuTu) + (6*g1p2*YuadjYuTu)/5._dp +      & 
&  6*g2p2*YuadjYuTu - 12*TrYuadjYu*YuadjYuTu - 8._dp*(YuadjYuTuadjYuYu) - (4*g1p2*M1*YuadjYuYu)/5._dp -& 
&  12*g2p2*M2*YuadjYuYu - 18*TradjYuTu*YuadjYuYu - 6._dp*(YuadjYuYuadjYuTu) +            & 
&  (2743*g1p4*Tu)/450._dp + g1p2*g2p2*Tu + (15*g2p4*Tu)/2._dp + (136*g1p2*g3p2*Tu)/45._dp +& 
&  8*g2p2*g3p2*Tu - (16*g3p4*Tu)/9._dp - 3*TrYdadjYuYuadjYd*Tu + (4*g1p2*TrYuadjYu*Tu)/5._dp +& 
&  16*g3p2*TrYuadjYu*Tu - 9*TrYuadjYuYuadjYu*Tu

 
DTu = oo16pi2*( betaTu1 + oo16pi2 * betaTu2 ) 

 
Else 
DTu = oo16pi2* betaTu1 
End If 
 
 
Call Chop(DTu) 

!-------------------- 
! Bmu 
!-------------------- 
 
betaBmu1  = (6*g1p2*M1*Mu)/5._dp + 6*g2p2*M2*Mu + 6*TradjYdTd*Mu + 2*TradjYeTe*Mu +   & 
&  6*TradjYuTu*Mu + (-3._dp*(g1p2)/5._dp - 3._dp*(g2p2) + 3._dp*(TrYdadjYd)              & 
&  + TrYeadjYe + 3._dp*(TrYuadjYu))*Bmu

 
 
If (TwoLoopRGE) Then 
betaBmu2 = (-2*(207*g1p4*M1 + 45*g1p2*g2p2*M1 + 45*g1p2*g2p2*M2 + 375*g2p4*M2 + 10*g1p2*TradjYdTd -& 
&  400*g3p2*TradjYdTd - 30*g1p2*TradjYeTe - 20*g1p2*TradjYuTu - 400*g3p2*TradjYuTu -     & 
&  10*(g1p2*M1 - 40*g3p2*M3)*TrYdadjYd + 450._dp*(TrYdadjYdTdadjYd) + 150._dp*(TrYdadjYuTuadjYd) +& 
&  30*g1p2*M1*TrYeadjYe + 150._dp*(TrYeadjYeTeadjYe) + 150._dp*(TrYuadjYdTdadjYu) +      & 
&  20*g1p2*M1*TrYuadjYu + 400*g3p2*M3*TrYuadjYu + 450._dp*(TrYuadjYuTuadjYu))*Mu)/25._dp +& 
&  (207._dp*(g1p4)/50._dp + (9*g1p2*g2p2)/5._dp + 15._dp*(g2p4)/2._dp - (2*(g1p2 -       & 
&  40._dp*(g3p2))*TrYdadjYd)/5._dp - 9._dp*(TrYdadjYdYdadjYd) - 6._dp*(TrYdadjYuYuadjYd) +& 
&  (6*g1p2*TrYeadjYe)/5._dp - 3._dp*(TrYeadjYeYeadjYe) + (4*g1p2*TrYuadjYu)/5._dp +      & 
&  16*g3p2*TrYuadjYu - 9._dp*(TrYuadjYuYuadjYu))*Bmu

 
DBmu = oo16pi2*( betaBmu1 + oo16pi2 * betaBmu2 ) 

 
Else 
DBmu = oo16pi2* betaBmu1 
End If 
 
 
Call Chop(DBmu) 

!-------------------- 
! mq2 
!-------------------- 
 
betamq21  = 2._dp*(adjTdTd) + 2._dp*(adjTuTu) + 2._dp*(adjYdmd2Yd) + adjYdYdmq2 +     & 
&  2._dp*(adjYumu2Yu) + adjYuYumq2 - (2*AbsM1*g1p2*id3R)/15._dp - 6*AbsM2*g2p2*id3R -    & 
&  (32*AbsM3*g3p2*id3R)/3._dp + 2*adjYdYd*mHd2 + 2*adjYuYu*mHu2 + mq2adjYdYd +           & 
&  mq2adjYuYu + g1*id3R*ooSqrt15*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamq22 = -4._dp*(adjTdTdadjYdYd) - 4._dp*(adjTdYdadjYdTd) - 4._dp*(adjTuTuadjYuYu) -           & 
&  4._dp*(adjTuYuadjYuTu) - 4._dp*(adjYdmd2YdadjYdYd) - 4._dp*(adjYdTdadjTdYd) -         & 
&  4._dp*(adjYdYdadjTdTd) - 4._dp*(adjYdYdadjYdmd2Yd) - 2._dp*(adjYdYdadjYdYdmq2) -      & 
&  4._dp*(adjYdYdmq2adjYdYd) - 4._dp*(adjYumu2YuadjYuYu) - 4._dp*(adjYuTuadjTuYu) -      & 
&  4._dp*(adjYuYuadjTuTu) - 4._dp*(adjYuYuadjYumu2Yu) - 2._dp*(adjYuYuadjYuYumq2) -      & 
&  4._dp*(adjYuYumq2adjYuYu) + (4*adjTdTd*g1p2)/5._dp + (8*adjTuTu*g1p2)/5._dp +         & 
&  (4*adjYdmd2Yd*g1p2)/5._dp + (2*adjYdYdmq2*g1p2)/5._dp + (8*adjYumu2Yu*g1p2)/5._dp +   & 
&  (4*adjYuYumq2*g1p2)/5._dp + (2*AbsM2*g1p2*g2p2*id3R)/5._dp + 33*AbsM2*g2p4*id3R +     & 
&  32*AbsM2*g2p2*g3p2*id3R - (4*adjTdYd*g1p2*M1)/5._dp - (8*adjTuYu*g1p2*M1)/5._dp -     & 
&  8*adjYdYdadjYdYd*mHd2 + (4*adjYdYd*g1p2*mHd2)/5._dp - 8*adjYuYuadjYuYu*mHu2 +         & 
&  (8*adjYuYu*g1p2*mHu2)/5._dp + (2*g1p2*mq2adjYdYd)/5._dp - 2._dp*(mq2adjYdYdadjYdYd) + & 
&  (4*g1p2*mq2adjYuYu)/5._dp - 2._dp*(mq2adjYuYuadjYuYu) - 6*adjTdYd*TradjYdTd -         & 
&  2*adjTdYd*TradjYeTe - 6*adjTuYu*TradjYuTu - 6*adjYdYd*TrCTdTpTd - 6*adjYdTd*TrCTdTpYd -& 
&  2*adjYdYd*TrCTeTpTe - 2*adjYdTd*TrCTeTpYe - 6*adjYuYu*TrCTuTpTu - 6*adjYuTu*TrCTuTpYu -& 
&  6*adjYdYd*Trmd2YdadjYd - 2*adjYdYd*Trme2YeadjYe - 2*adjYdYd*Trml2adjYeYe -            & 
&  6*adjYdYd*Trmq2adjYdYd - 6*adjYuYu*Trmq2adjYuYu - 6*adjYuYu*Trmu2YuadjYu -            & 
&  6*adjTdTd*TrYdadjYd - 6*adjYdmd2Yd*TrYdadjYd - 3*adjYdYdmq2*TrYdadjYd -               & 
&  12*adjYdYd*mHd2*TrYdadjYd - 3*mq2adjYdYd*TrYdadjYd - 2*adjTdTd*TrYeadjYe -            & 
&  2*adjYdmd2Yd*TrYeadjYe - adjYdYdmq2*TrYeadjYe - 4*adjYdYd*mHd2*TrYeadjYe -            & 
&  mq2adjYdYd*TrYeadjYe - 6*adjTuTu*TrYuadjYu - 6*adjYumu2Yu*TrYuadjYu - 3*adjYuYumq2*TrYuadjYu -& 
&  12*adjYuYu*mHu2*TrYuadjYu - 3*mq2adjYuYu*TrYuadjYu + (g1p2*(180*(-1._dp*(adjYdTd) -   & 
&  2._dp*(adjYuTu) + 2*adjYdYd*M1 + 4*adjYuYu*M1) + id3R*(597*g1p2*M1 + 5*(16*g3p2*(2._dp*(M1) +& 
&  M3) + 9*g2p2*(2._dp*(M1) + M2))))*Conjg(M1))/225._dp + (16*g3p2*id3R*(g1p2*(M1 +      & 
&  2._dp*(M3)) + 15*(-8*g3p2*M3 + 3*g2p2*(2._dp*(M3) + M2)))*Conjg(M3))/45._dp  
betamq22 =  betamq22+ (g1p2*g2p2*id3R*M1*Conjg(M2))/5._dp + 16*g2p2*g3p2*id3R*M3*Conjg(M2) + 6*g2p4*id3R*Tr2(2) +& 
&  (32*g3p4*id3R*Tr2(3))/3._dp + (2*g1p2*id3R*Tr2U1(1,1))/15._dp + 4*g1*id3R*ooSqrt15*Tr3(1)

 
Dmq2 = oo16pi2*( betamq21 + oo16pi2 * betamq22 ) 

 
Else 
Dmq2 = oo16pi2* betamq21 
End If 
 
 
Call Chop(Dmq2) 

Forall(i1=1:3) Dmq2(i1,i1) =  Real(Dmq2(i1,i1),dp) 
Dmq2 = 0.5_dp*(Dmq2+ Conjg(Transpose(Dmq2)) ) 
!-------------------- 
! ml2 
!-------------------- 
 
betaml21  = 2._dp*(adjTeTe) + 2._dp*(adjYeme2Ye) + adjYeYeml2 - (6*AbsM1*g1p2*id3R)   & 
& /5._dp - 6*AbsM2*g2p2*id3R + 2*adjYeYe*mHd2 + ml2adjYeYe - g1*id3R*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betaml22 = -4._dp*(adjTeTeadjYeYe) - 4._dp*(adjTeYeadjYeTe) - 4._dp*(adjYeme2YeadjYeYe) -        & 
&  4._dp*(adjYeTeadjTeYe) - 4._dp*(adjYeYeadjTeTe) - 4._dp*(adjYeYeadjYeme2Ye) -         & 
&  2._dp*(adjYeYeadjYeYeml2) - 4._dp*(adjYeYeml2adjYeYe) + (12*adjTeTe*g1p2)/5._dp +     & 
&  (12*adjYeme2Ye*g1p2)/5._dp + (6*adjYeYeml2*g1p2)/5._dp - (12*adjTeYe*g1p2*M1)/5._dp - & 
&  8*adjYeYeadjYeYe*mHd2 + (12*adjYeYe*g1p2*mHd2)/5._dp + (6*g1p2*ml2adjYeYe)/5._dp -    & 
&  2._dp*(ml2adjYeYeadjYeYe) - 6*adjTeYe*TradjYdTd - 2*adjTeYe*TradjYeTe -               & 
&  6*adjYeYe*TrCTdTpTd - 6*adjYeTe*TrCTdTpYd - 2*adjYeYe*TrCTeTpTe - 2*adjYeTe*TrCTeTpYe -& 
&  6*adjYeYe*Trmd2YdadjYd - 2*adjYeYe*Trme2YeadjYe - 2*adjYeYe*Trml2adjYeYe -            & 
&  6*adjYeYe*Trmq2adjYdYd - 6*adjTeTe*TrYdadjYd - 6*adjYeme2Ye*TrYdadjYd -               & 
&  3*adjYeYeml2*TrYdadjYd - 12*adjYeYe*mHd2*TrYdadjYd - 3*ml2adjYeYe*TrYdadjYd -         & 
&  2*adjTeTe*TrYeadjYe - 2*adjYeme2Ye*TrYeadjYe - adjYeYeml2*TrYeadjYe - 4*adjYeYe*mHd2*TrYeadjYe -& 
&  ml2adjYeYe*TrYeadjYe + (3*g1p2*(-20._dp*(adjYeTe) + 40*adjYeYe*M1 + 3*id3R*(69*g1p2*M1 +& 
&  5*g2p2*(2._dp*(M1) + M2)))*Conjg(M1))/25._dp + (3*g2p2*id3R*(55*g2p2*M2 +             & 
&  3*g1p2*(M1 + 2._dp*(M2)))*Conjg(M2))/5._dp + 6*g2p4*id3R*Tr2(2) + (6*g1p2*id3R*Tr2U1(1,& 
& 1))/5._dp - 4*g1*id3R*sqrt3ov5*Tr3(1)

 
Dml2 = oo16pi2*( betaml21 + oo16pi2 * betaml22 ) 

 
Else 
Dml2 = oo16pi2* betaml21 
End If 
 
 
Call Chop(Dml2) 

Forall(i1=1:3) Dml2(i1,i1) =  Real(Dml2(i1,i1),dp) 
Dml2 = 0.5_dp*(Dml2+ Conjg(Transpose(Dml2)) ) 
!-------------------- 
! mHd2 
!-------------------- 
 
betamHd21  = (-6*AbsM1*g1p2)/5._dp - 6*AbsM2*g2p2 + 6._dp*(TrCTdTpTd) +               & 
&  2._dp*(TrCTeTpTe) + 6._dp*(Trmd2YdadjYd) + 2._dp*(Trme2YeadjYe) + 2._dp*(Trml2adjYeYe)& 
&  + 6._dp*(Trmq2adjYdYd) + 6*mHd2*TrYdadjYd + 2*mHd2*TrYeadjYe - g1*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamHd22 = (g1p2*(621*g1p2*M1 + 90*g2p2*M1 + 45*g2p2*M2 + 20._dp*(TradjYdTd) - 60._dp*(TradjYeTe) -& 
&  40*M1*TrYdadjYd + 120*M1*TrYeadjYe)*Conjg(M1) + 15*g2p2*(55*g2p2*M2 + 3*g1p2*(M1 +    & 
&  2._dp*(M2)))*Conjg(M2) + 10*(-2*g1p2*TrCTdTpTd + 80*g3p2*TrCTdTpTd + 2*g1p2*M1*TrCTdTpYd -& 
&  80*g3p2*M3*TrCTdTpYd + 6*g1p2*TrCTeTpTe - 6*g1p2*M1*TrCTeTpYe - 2*g1p2*Trmd2YdadjYd + & 
&  80*g3p2*Trmd2YdadjYd - 90._dp*(Trmd2YdadjYdYdadjYd) - 15._dp*(Trmd2YdadjYuYuadjYd) +  & 
&  6*g1p2*Trme2YeadjYe - 30._dp*(Trme2YeadjYeYeadjYe) + 6*g1p2*Trml2adjYeYe -            & 
&  30._dp*(Trml2adjYeYeadjYeYe) - 2*g1p2*Trmq2adjYdYd + 80*g3p2*Trmq2adjYdYd -           & 
&  90._dp*(Trmq2adjYdYdadjYdYd) - 15._dp*(Trmq2adjYdYdadjYuYu) - 15._dp*(Trmq2adjYuYuadjYdYd) -& 
&  15._dp*(Trmu2YuadjYdYdadjYu) - 90._dp*(TrYdadjTdTdadjYd) - 15._dp*(TrYdadjTuTuadjYd) +& 
&  (160*AbsM3*g3p2 - 2*g1p2*mHd2 + 80*g3p2*mHd2)*TrYdadjYd - 90._dp*(TrYdadjYdTdadjTd) - & 
&  90*mHd2*TrYdadjYdYdadjYd - 15._dp*(TrYdadjYuTuadjTd) - 15*mHd2*TrYdadjYuYuadjYd -     & 
&  15*mHu2*TrYdadjYuYuadjYd - 30._dp*(TrYeadjTeTeadjYe) + 6*g1p2*mHd2*TrYeadjYe -        & 
&  30._dp*(TrYeadjYeTeadjTe) - 30*mHd2*TrYeadjYeYeadjYe - 15._dp*(TrYuadjTdTdadjYu) -    & 
&  15._dp*(TrYuadjYdTdadjTu) - 80*g3p2*TradjYdTd*Conjg(M3) + 15*g2p4*Tr2(2) +            & 
&  3*g1p2*Tr2U1(1,1) - 2*g1*sqrt15*Tr3(1)))/25._dp

 
DmHd2 = oo16pi2*( betamHd21 + oo16pi2 * betamHd22 ) 

 
Else 
DmHd2 = oo16pi2* betamHd21 
End If 
 
 
!-------------------- 
! mHu2 
!-------------------- 
 
betamHu21  = (-6*AbsM1*g1p2)/5._dp - 6*AbsM2*g2p2 + 6._dp*(TrCTuTpTu) +               & 
&  6._dp*(Trmq2adjYuYu) + 6._dp*(Trmu2YuadjYu) + 6*mHu2*TrYuadjYu + g1*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamHu22 = (8*g1p2*TrCTuTpTu)/5._dp + 32*g3p2*TrCTuTpTu - (8*g1p2*M1*TrCTuTpYu)/5._dp -          & 
&  32*g3p2*M3*TrCTuTpYu - 6._dp*(Trmd2YdadjYuYuadjYd) - 6._dp*(Trmq2adjYdYdadjYuYu) +    & 
&  (8*g1p2*Trmq2adjYuYu)/5._dp + 32*g3p2*Trmq2adjYuYu - 6._dp*(Trmq2adjYuYuadjYdYd) -    & 
&  36._dp*(Trmq2adjYuYuadjYuYu) - 6._dp*(Trmu2YuadjYdYdadjYu) + (8*g1p2*Trmu2YuadjYu)/5._dp +& 
&  32*g3p2*Trmu2YuadjYu - 36._dp*(Trmu2YuadjYuYuadjYu) - 6._dp*(TrYdadjTuTuadjYd) -      & 
&  6._dp*(TrYdadjYuTuadjTd) - 6*mHd2*TrYdadjYuYuadjYd - 6*mHu2*TrYdadjYuYuadjYd -        & 
&  6._dp*(TrYuadjTdTdadjYu) - 36._dp*(TrYuadjTuTuadjYu) - 6._dp*(TrYuadjYdTdadjTu) +     & 
&  64*AbsM3*g3p2*TrYuadjYu + (8*g1p2*mHu2*TrYuadjYu)/5._dp + 32*g3p2*mHu2*TrYuadjYu -    & 
&  36._dp*(TrYuadjYuTuadjTu) - 36*mHu2*TrYuadjYuYuadjYu + (g1p2*(621*g1p2*M1 +           & 
&  90*g2p2*M1 + 45*g2p2*M2 - 40._dp*(TradjYuTu) + 80*M1*TrYuadjYu)*Conjg(M1))/25._dp -   & 
&  32*g3p2*TradjYuTu*Conjg(M3) + (3*g2p2*(55*g2p2*M2 + 3*g1p2*(M1 + 2._dp*(M2)))*Conjg(M2))/5._dp +& 
&  6*g2p4*Tr2(2) + (6*g1p2*Tr2U1(1,1))/5._dp + 4*g1*sqrt3ov5*Tr3(1)

 
DmHu2 = oo16pi2*( betamHu21 + oo16pi2 * betamHu22 ) 

 
Else 
DmHu2 = oo16pi2* betamHu21 
End If 
 
 
!-------------------- 
! md2 
!-------------------- 
 
betamd21  = (-8*AbsM1*g1p2*id3R)/15._dp - (32*AbsM3*g3p2*id3R)/3._dp + 2._dp*(md2YdadjYd)& 
&  + 4._dp*(TdadjTd) + 4*mHd2*YdadjYd + 2._dp*(YdadjYdmd2) + 4._dp*(Ydmq2adjYd)          & 
&  + 2*g1*id3R*ooSqrt15*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamd22 = (2*g1p2*md2YdadjYd)/5._dp + 6*g2p2*md2YdadjYd - 2._dp*(md2YdadjYdYdadjYd) -           & 
&  2._dp*(md2YdadjYuYuadjYd) + (4*g1p2*TdadjTd)/5._dp + 12*g2p2*TdadjTd - 4._dp*(TdadjTdYdadjYd) -& 
&  4._dp*(TdadjTuYuadjYd) - 4._dp*(TdadjYdYdadjTd) - 4._dp*(TdadjYuYuadjTd) -            & 
&  12*TdadjYd*TrCTdTpYd - 4*TdadjYd*TrCTeTpYe - 6*md2YdadjYd*TrYdadjYd - 12*TdadjTd*TrYdadjYd -& 
&  2*md2YdadjYd*TrYeadjYe - 4*TdadjTd*TrYeadjYe - (4*g1p2*M1*YdadjTd)/5._dp -            & 
&  12*g2p2*M2*YdadjTd - 12*TradjYdTd*YdadjTd - 4*TradjYeTe*YdadjTd - 4._dp*(YdadjTdTdadjYd) -& 
&  4._dp*(YdadjTuTuadjYd) + 24*AbsM2*g2p2*YdadjYd + (4*g1p2*mHd2*YdadjYd)/5._dp +        & 
&  12*g2p2*mHd2*YdadjYd - 12*TrCTdTpTd*YdadjYd - 4*TrCTeTpTe*YdadjYd - 12*Trmd2YdadjYd*YdadjYd -& 
&  4*Trme2YeadjYe*YdadjYd - 4*Trml2adjYeYe*YdadjYd - 12*Trmq2adjYdYd*YdadjYd -           & 
&  24*mHd2*TrYdadjYd*YdadjYd - 8*mHd2*TrYeadjYe*YdadjYd + (2*g1p2*YdadjYdmd2)/5._dp +    & 
&  6*g2p2*YdadjYdmd2 - 6*TrYdadjYd*YdadjYdmd2 - 2*TrYeadjYe*YdadjYdmd2 - 4._dp*(YdadjYdmd2YdadjYd) -& 
&  4._dp*(YdadjYdTdadjTd) - 8*mHd2*YdadjYdYdadjYd - 2._dp*(YdadjYdYdadjYdmd2) -          & 
&  4._dp*(YdadjYdYdmq2adjYd) - 4._dp*(YdadjYumu2YuadjYd) - 4._dp*(YdadjYuTuadjTd) -      & 
&  4*mHd2*YdadjYuYuadjYd - 4*mHu2*YdadjYuYuadjYd - 2._dp*(YdadjYuYuadjYdmd2) -           & 
&  4._dp*(YdadjYuYumq2adjYd) + (4*g1p2*Ydmq2adjYd)/5._dp + 12*g2p2*Ydmq2adjYd -          & 
&  12*TrYdadjYd*Ydmq2adjYd - 4*TrYeadjYe*Ydmq2adjYd - 4._dp*(Ydmq2adjYdYdadjYd) -        & 
&  4._dp*(Ydmq2adjYuYuadjYd) + (4*g1p2*(2*id3R*(303*g1p2*M1 + 40*g3p2*(2._dp*(M1) +      & 
&  M3)) - 45._dp*(TdadjYd) + 90*M1*YdadjYd)*Conjg(M1))/225._dp + (64*g3p2*id3R*(-        & 
& 30*g3p2*M3 + g1p2*(M1 + 2._dp*(M3)))*Conjg(M3))/45._dp - 12*g2p2*TdadjYd*Conjg(M2) +   & 
&  (32*g3p4*id3R*Tr2(3))/3._dp + (8*g1p2*id3R*Tr2U1(1,1))/15._dp + 8*g1*id3R*ooSqrt15*Tr3(1)

 
Dmd2 = oo16pi2*( betamd21 + oo16pi2 * betamd22 ) 

 
Else 
Dmd2 = oo16pi2* betamd21 
End If 
 
 
Call Chop(Dmd2) 

Forall(i1=1:3) Dmd2(i1,i1) =  Real(Dmd2(i1,i1),dp) 
Dmd2 = 0.5_dp*(Dmd2+ Conjg(Transpose(Dmd2)) ) 
!-------------------- 
! mu2 
!-------------------- 
 
betamu21  = (-32*AbsM1*g1p2*id3R)/15._dp - (32*AbsM3*g3p2*id3R)/3._dp +               & 
&  2._dp*(mu2YuadjYu) + 4._dp*(TuadjTu) + 4*mHu2*YuadjYu + 2._dp*(YuadjYumu2)            & 
&  + 4._dp*(Yumq2adjYu) - 4*g1*id3R*ooSqrt15*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betamu22 = -2._dp*(mu2YuadjYdYdadjYu) - (2*g1p2*mu2YuadjYu)/5._dp + 6*g2p2*mu2YuadjYu -          & 
&  2._dp*(mu2YuadjYuYuadjYu) - 6*mu2YuadjYu*TrYuadjYu - 4._dp*(TuadjTdYdadjYu) -         & 
&  (4*g1p2*TuadjTu)/5._dp + 12*g2p2*TuadjTu - 12*TrYuadjYu*TuadjTu - 4._dp*(TuadjTuYuadjYu) -& 
&  4._dp*(TuadjYdYdadjTu) - 12*TrCTuTpYu*TuadjYu - 4._dp*(TuadjYuYuadjTu) -              & 
&  4._dp*(YuadjTdTdadjYu) + (4*g1p2*M1*YuadjTu)/5._dp - 12*g2p2*M2*YuadjTu -             & 
&  12*TradjYuTu*YuadjTu - 4._dp*(YuadjTuTuadjYu) - 4._dp*(YuadjYdmd2YdadjYu) -           & 
&  4._dp*(YuadjYdTdadjTu) - 4*mHd2*YuadjYdYdadjYu - 4*mHu2*YuadjYdYdadjYu -              & 
&  2._dp*(YuadjYdYdadjYumu2) - 4._dp*(YuadjYdYdmq2adjYu) + 24*AbsM2*g2p2*YuadjYu -       & 
&  (4*g1p2*mHu2*YuadjYu)/5._dp + 12*g2p2*mHu2*YuadjYu - 12*TrCTuTpTu*YuadjYu -           & 
&  12*Trmq2adjYuYu*YuadjYu - 12*Trmu2YuadjYu*YuadjYu - 24*mHu2*TrYuadjYu*YuadjYu -       & 
&  (2*g1p2*YuadjYumu2)/5._dp + 6*g2p2*YuadjYumu2 - 6*TrYuadjYu*YuadjYumu2 -              & 
&  4._dp*(YuadjYumu2YuadjYu) - 4._dp*(YuadjYuTuadjTu) - 8*mHu2*YuadjYuYuadjYu -          & 
&  2._dp*(YuadjYuYuadjYumu2) - 4._dp*(YuadjYuYumq2adjYu) - 4._dp*(Yumq2adjYdYdadjYu) -   & 
&  (4*g1p2*Yumq2adjYu)/5._dp + 12*g2p2*Yumq2adjYu - 12*TrYuadjYu*Yumq2adjYu -            & 
&  4._dp*(Yumq2adjYuYuadjYu) + (4*g1p2*(8*id3R*(321*g1p2*M1 + 40*g3p2*(2._dp*(M1) +      & 
&  M3)) + 45*(TuadjYu - 2*M1*YuadjYu))*Conjg(M1))/225._dp - (128*g3p2*id3R*(15*g3p2*M3 - & 
&  2*g1p2*(M1 + 2._dp*(M3)))*Conjg(M3))/45._dp - 12*g2p2*TuadjYu*Conjg(M2) +             & 
&  (32*g3p4*id3R*Tr2(3))/3._dp + (32*g1p2*id3R*Tr2U1(1,1))/15._dp - 16*g1*id3R*ooSqrt15*Tr3(1)

 
Dmu2 = oo16pi2*( betamu21 + oo16pi2 * betamu22 ) 

 
Else 
Dmu2 = oo16pi2* betamu21 
End If 
 
 
Call Chop(Dmu2) 

Forall(i1=1:3) Dmu2(i1,i1) =  Real(Dmu2(i1,i1),dp) 
Dmu2 = 0.5_dp*(Dmu2+ Conjg(Transpose(Dmu2)) ) 
!-------------------- 
! me2 
!-------------------- 
 
betame21  = (-24*AbsM1*g1p2*id3R)/5._dp + 2*(me2YeadjYe + 2._dp*(TeadjTe)             & 
&  + 2*mHd2*YeadjYe + YeadjYeme2 + 2._dp*(Yeml2adjYe)) + 2*g1*id3R*sqrt3ov5*Tr1(1)

 
 
If (TwoLoopRGE) Then 
betame22 = (2*(6*g1p2*(234*g1p2*id3R*M1 + 5*(TeadjYe - 2*M1*YeadjYe))*Conjg(M1) - 5*(3*g1p2*me2YeadjYe -& 
&  15*g2p2*me2YeadjYe + 5._dp*(me2YeadjYeYeadjYe) + 6*g1p2*TeadjTe - 30*g2p2*TeadjTe +   & 
&  10._dp*(TeadjTeYeadjYe) + 10._dp*(TeadjYeYeadjTe) + 30*TeadjYe*TrCTdTpYd +            & 
&  10*TeadjYe*TrCTeTpYe + 15*me2YeadjYe*TrYdadjYd + 30*TeadjTe*TrYdadjYd +               & 
&  5*me2YeadjYe*TrYeadjYe + 10*TeadjTe*TrYeadjYe + (-6*g1p2*M1 + 30*g2p2*M2 +            & 
&  30._dp*(TradjYdTd) + 10._dp*(TradjYeTe))*YeadjTe + 10._dp*(YeadjTeTeadjYe) +          & 
&  2*(-30*AbsM2*g2p2 + 3*g1p2*mHd2 - 15*g2p2*mHd2 + 15._dp*(TrCTdTpTd) + 5._dp*(TrCTeTpTe) +& 
&  15._dp*(Trmd2YdadjYd) + 5._dp*(Trme2YeadjYe) + 5._dp*(Trml2adjYeYe) + 15._dp*(Trmq2adjYdYd) +& 
&  30*mHd2*TrYdadjYd + 10*mHd2*TrYeadjYe)*YeadjYe + 3*g1p2*YeadjYeme2 - 15*g2p2*YeadjYeme2 +& 
&  15*TrYdadjYd*YeadjYeme2 + 5*TrYeadjYe*YeadjYeme2 + 10._dp*(YeadjYeme2YeadjYe) +       & 
&  10._dp*(YeadjYeTeadjTe) + 20*mHd2*YeadjYeYeadjYe + 5._dp*(YeadjYeYeadjYeme2) +        & 
&  10._dp*(YeadjYeYeml2adjYe) + 6*g1p2*Yeml2adjYe - 30*g2p2*Yeml2adjYe + 30*TrYdadjYd*Yeml2adjYe +& 
&  10*TrYeadjYe*Yeml2adjYe + 10._dp*(Yeml2adjYeYeadjYe) + 30*g2p2*TeadjYe*Conjg(M2)) +   & 
&  20*g1*id3R*(3*g1*Tr2U1(1,1) + sqrt15*Tr3(1))))/25._dp

 
Dme2 = oo16pi2*( betame21 + oo16pi2 * betame22 ) 

 
Else 
Dme2 = oo16pi2* betame21 
End If 
 
 
Call Chop(Dme2) 

Forall(i1=1:3) Dme2(i1,i1) =  Real(Dme2(i1,i1),dp) 
Dme2 = 0.5_dp*(Dme2+ Conjg(Transpose(Dme2)) ) 
!-------------------- 
! M1 
!-------------------- 
 
betaM11  = (66*g1p2*M1)/5._dp

 
 
If (TwoLoopRGE) Then 
betaM12 = (2*g1p2*(398*g1p2*M1 + 135*g2p2*M1 + 440*g3p2*M1 + 440*g3p2*M3 + 135*g2p2*M2 +        & 
&  70._dp*(TradjYdTd) + 90._dp*(TradjYeTe) + 130._dp*(TradjYuTu) - 70*M1*TrYdadjYd -     & 
&  90*M1*TrYeadjYe - 130*M1*TrYuadjYu))/25._dp

 
DM1 = oo16pi2*( betaM11 + oo16pi2 * betaM12 ) 

 
Else 
DM1 = oo16pi2* betaM11 
End If 
 
 
Call Chop(DM1) 

!-------------------- 
! M2 
!-------------------- 
 
betaM21  = 2*g2p2*M2

 
 
If (TwoLoopRGE) Then 
betaM22 = (2*g2p2*(9*g1p2*M1 + 120*g3p2*M3 + 9*g1p2*M2 + 250*g2p2*M2 + 120*g3p2*M2 +            & 
&  30._dp*(TradjYdTd) + 10._dp*(TradjYeTe) + 30._dp*(TradjYuTu) - 30*M2*TrYdadjYd -      & 
&  10*M2*TrYeadjYe - 30*M2*TrYuadjYu))/5._dp

 
DM2 = oo16pi2*( betaM21 + oo16pi2 * betaM22 ) 

 
Else 
DM2 = oo16pi2* betaM21 
End If 
 
 
Call Chop(DM2) 

!-------------------- 
! M3 
!-------------------- 
 
betaM31  = -6*g3p2*M3

 
 
If (TwoLoopRGE) Then 
betaM32 = (2*g3p2*(11*g1p2*M1 + 11*g1p2*M3 + 45*g2p2*M3 + 140*g3p2*M3 + 45*g2p2*M2 +            & 
&  20._dp*(TradjYdTd) + 20._dp*(TradjYuTu) - 20*M3*TrYdadjYd - 20*M3*TrYuadjYu))/5._dp

 
DM3 = oo16pi2*( betaM31 + oo16pi2 * betaM32 ) 

 
Else 
DM3 = oo16pi2* betaM31 
End If 
 
 
Call Chop(DM3) 

!-------------------- 
! vd 
!-------------------- 
 
betavd1  = (vd*(-60._dp*(TrYdadjYd) - 20._dp*(TrYeadjYe) + 3*(g1p2 + 5._dp*(g2p2))    & 
& *(1 + Xi)))/20._dp

 
 
If (TwoLoopRGE) Then 
betavd2 = (vd*(-414._dp*(g1p4) - 180*g1p2*g2p2 - 1200._dp*(g2p4) + 3600._dp*(TrYdadjYdYdadjYd) +& 
&  1200._dp*(TrYdadjYuYuadjYd) + 1200._dp*(TrYeadjYeYeadjYe) - 9*g1p4*Xi -               & 
&  90*g1p2*g2p2*Xi + 875*g2p4*Xi - 120*TrYeadjYe*(5*g2p2*Xi + g1p2*(4 + Xi)) -           & 
&  40*TrYdadjYd*(g1p2*(-4 + 9._dp*(Xi)) + 5*(32._dp*(g3p2) + 9*g2p2*Xi)) +               & 
&  9*g1p4*Xip2 + 90*g1p2*g2p2*Xip2 - 225*g2p4*Xip2))/400._dp

 
Dvd = oo16pi2*( betavd1 + oo16pi2 * betavd2 ) 

 
Else 
Dvd = oo16pi2* betavd1 
End If 
 
 
!-------------------- 
! vu 
!-------------------- 
 
betavu1  = (3*vu*(-20._dp*(TrYuadjYu) + (g1p2 + 5._dp*(g2p2))*(1 + Xi)))/20._dp

 
 
If (TwoLoopRGE) Then 
betavu2 = (vu*(-414._dp*(g1p4) - 180*g1p2*g2p2 - 1200._dp*(g2p4) + 1200._dp*(TrYdadjYuYuadjYd) +& 
&  3600._dp*(TrYuadjYuYuadjYu) - 9*g1p4*Xi - 90*g1p2*g2p2*Xi + 875*g2p4*Xi -             & 
&  40*TrYuadjYu*(g1p2*(8 + 9._dp*(Xi)) + 5*(32._dp*(g3p2) + 9*g2p2*Xi)) + 9*g1p4*Xip2 +  & 
&  90*g1p2*g2p2*Xip2 - 225*g2p4*Xip2))/400._dp

 
Dvu = oo16pi2*( betavu1 + oo16pi2 * betavu2 ) 

 
Else 
Dvu = oo16pi2* betavu1 
End If 
 
 
Call ParametersToG215(Dg1,Dg2,Dg3,DYd,DYe,DYu,DMu,DTd,DTe,DTu,DBmu,Dmq2,              & 
& Dml2,DmHd2,DmHu2,Dmd2,Dmu2,Dme2,DM1,DM2,DM3,Dvd,Dvu,f)

Iname = Iname - 1 
 
End Subroutine rge215  

End Module RGEs_MSSM 
 
