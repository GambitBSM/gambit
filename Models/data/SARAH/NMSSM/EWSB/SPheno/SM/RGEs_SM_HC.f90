! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version SARAHVERSION 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 13:23 on 7.1.2017   
! ----------------------------------------------------------------------  
 
 
Module RGEs_SM_HC
 
Use Control 
Use Settings 
Use Mathematics 
 
Logical,Private,Save::OnlyDiagonal

Real(dp),Parameter::id3R(3,3)=& 
   & Reshape(Source=(/& 
   & 1,0,0,& 
 &0,1,0,& 
 &0,0,1& 
 &/),shape=(/3,3/)) 
Contains 


Subroutine GToParameters62_SM(g,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v)

Implicit None 
Real(dp), Intent(in) :: g(62) 
Real(dp),Intent(out) :: g1,g2,g3,v

Complex(dp),Intent(out) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3),Mu

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'GToParameters62' 
 
g1= g(1) 
g2= g(2) 
g3= g(3) 
Lam= Cmplx(g(4),g(5),dp) 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yu(i1,i2) = Cmplx( g(SumI+6), g(SumI+7), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Yd(i1,i2) = Cmplx( g(SumI+24), g(SumI+25), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
Ye(i1,i2) = Cmplx( g(SumI+42), g(SumI+43), dp) 
End Do 
 End Do 
 
Mu= Cmplx(g(60),g(61),dp) 
v= g(62) 
Do i1=1,62 
If (g(i1).ne.g(i1)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Write(*,*) "At position ", i1 
 Call TerminateProgram 
End if 
End do 
Iname = Iname - 1 
 
End Subroutine GToParameters62_SM

Subroutine ParametersToG62_SM(g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v,g)

Implicit None 
Real(dp), Intent(out) :: g(62) 
Real(dp), Intent(in) :: g1,g2,g3,v

Complex(dp), Intent(in) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3),Mu

Integer i1, i2, i3, i4, SumI 
 
Iname = Iname +1 
NameOfUnit(Iname) = 'ParametersToG62' 
 
g(1) = g1  
g(2) = g2  
g(3) = g3  
g(4) = Real(Lam,dp)  
g(5) = Aimag(Lam)  
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+6) = Real(Yu(i1,i2), dp) 
g(SumI+7) = Aimag(Yu(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+24) = Real(Yd(i1,i2), dp) 
g(SumI+25) = Aimag(Yd(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+42) = Real(Ye(i1,i2), dp) 
g(SumI+43) = Aimag(Ye(i1,i2)) 
End Do 
End Do 

g(60) = Real(Mu,dp)  
g(61) = Aimag(Mu)  
g(62) = v  
Iname = Iname - 1 
 
End Subroutine ParametersToG62_SM

Subroutine rge62_SM(len, T, GY, F) 
Implicit None 
Integer, Intent(in) :: len 
Real(dp), Intent(in) :: T, GY(len) 
Real(dp), Intent(out) :: F(len) 
Integer :: i1,i2,i3,i4 
Integer :: j1,j2,j3,j4,j5,j6,j7 
Real(dp) :: q 
Real(dp) :: g1,betag11,betag12,Dg1,g2,betag21,betag22,Dg2,g3,betag31,betag32,         & 
& Dg3,v,betav1,betav2,Dv, betag33, betaLam3, BetaYu3, Yt, Z3
Complex(dp) :: Lam,betaLam1,betaLam2,DLam,Yu(3,3),betaYu1(3,3),betaYu2(3,3)           & 
& ,DYu(3,3),adjYu(3,3),Yd(3,3),betaYd1(3,3),betaYd2(3,3),DYd(3,3),adjYd(3,3)             & 
& ,Ye(3,3),betaYe1(3,3),betaYe2(3,3),DYe(3,3),adjYe(3,3),Mu,betaMu1,betaMu2,DMu
Complex(dp) :: YdadjYd(3,3),YeadjYe(3,3),YuadjYu(3,3),adjYdYd(3,3),adjYeYe(3,3),adjYuYu(3,3),        & 
& YdadjYdYd(3,3),YdadjYuYu(3,3),YeadjYeYe(3,3),YuadjYdYd(3,3),YuadjYuYu(3,3),            & 
& adjYdYdadjYd(3,3),adjYeYeadjYe(3,3),adjYuYuadjYu(3,3),YdadjYdYdadjYd(3,3),             & 
& YeadjYeYeadjYe(3,3),YuadjYuYuadjYu(3,3)

Complex(dp) :: YuadjYd(3,3),adjYuYuadjYd(3,3),YdadjYuYuadjYd(3,3),YuadjYdYdadjYd(3,3),               & 
& YuadjYuYuadjYd(3,3),adjYdYdadjYdYd(3,3),adjYdYdadjYuYu(3,3),adjYeYeadjYeYe(3,3),       & 
& adjYuYuadjYdYd(3,3),adjYuYuadjYuYu(3,3),YdadjYdYdadjYdYd(3,3),YdadjYdYdadjYuYu(3,3),   & 
& YdadjYuYuadjYdYd(3,3),YdadjYuYuadjYuYu(3,3),YeadjYeYeadjYeYe(3,3),YuadjYdYdadjYdYd(3,3),& 
& YuadjYdYdadjYuYu(3,3),YuadjYuYuadjYdYd(3,3),YuadjYuYuadjYuYu(3,3),adjYdYdadjYdYdadjYd(3,3),& 
& adjYdYdadjYuYuadjYd(3,3),adjYeYeadjYeYeadjYe(3,3),adjYuYuadjYdYdadjYd(3,3),            & 
& adjYuYuadjYuYuadjYd(3,3),adjYuYuadjYuYuadjYu(3,3),YdadjYdYdadjYdYdadjYd(3,3),          & 
& YdadjYdYdadjYuYuadjYd(3,3),YdadjYuYuadjYdYdadjYd(3,3),YdadjYuYuadjYuYuadjYd(3,3),      & 
& YeadjYeYeadjYeYeadjYe(3,3),YuadjYuYuadjYuYuadjYu(3,3)

Complex(dp) :: TrYdadjYd,TrYeadjYe,TrYuadjYu,TrYdadjYdYdadjYd,TrYeadjYeYeadjYe,TrYuadjYuYuadjYu

Complex(dp) :: TrYdadjYuYuadjYd,TrYdadjYdYdadjYdYdadjYd,TrYdadjYdYdadjYuYuadjYd,TrYdadjYuYuadjYdYdadjYd,& 
& TrYdadjYuYuadjYuYuadjYd,TrYeadjYeYeadjYeYeadjYe,TrYuadjYuYuadjYuYuadjYu

Real(dp) :: g1p2,g1p3,g1p4,g2p2,g2p3,g2p4,g3p2,g3p3

Complex(dp) :: Lamp2

Real(dp) :: g1p6,g2p6,g3p4

Complex(dp) :: Xip2,Lamp3

Iname = Iname +1 
NameOfUnit(Iname) = 'rge62' 
 
OnlyDiagonal = .Not.GenerationMixing 
q = t 
 
Call GToParameters62_SM(gy,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,v)

Yt= Yu(3,3)
Z3=1.2020569031595942366_dp

Call Adjungate(Yu,adjYu)
Call Adjungate(Yd,adjYd)
Call Adjungate(Ye,adjYe)
 YdadjYd = Matmul(Yd,adjYd) 
Forall(i2=1:3)  YdadjYd(i2,i2) =  Real(YdadjYd(i2,i2),dp) 
 YeadjYe = Matmul(Ye,adjYe) 
Forall(i2=1:3)  YeadjYe(i2,i2) =  Real(YeadjYe(i2,i2),dp) 
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
 Lamp2 =Lam**2 
 g1p6 =g1**6 
 g2p6 =g2**6 
 g3p4 =g3**4 
 Xip2 =Xi**2 
 Lamp3 =Lam**3 
 
!  TwoLoopRGE=.false.


If (TwoLoopRGE) Then 
 YuadjYd = Matmul(Yu,adjYd) 
 adjYuYuadjYd = Matmul(adjYu,YuadjYd) 
 YdadjYuYuadjYd = Matmul(Yd,adjYuYuadjYd) 
Forall(i2=1:3)  YdadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYd(i2,i2),dp) 
 YuadjYdYdadjYd = Matmul(Yu,adjYdYdadjYd) 
 YuadjYuYuadjYd = Matmul(Yu,adjYuYuadjYd) 
 adjYdYdadjYdYd = Matmul(adjYd,YdadjYdYd) 
Forall(i2=1:3)  adjYdYdadjYdYd(i2,i2) =  Real(adjYdYdadjYdYd(i2,i2),dp) 
 adjYdYdadjYuYu = Matmul(adjYd,YdadjYuYu) 
 adjYeYeadjYeYe = Matmul(adjYe,YeadjYeYe) 
Forall(i2=1:3)  adjYeYeadjYeYe(i2,i2) =  Real(adjYeYeadjYeYe(i2,i2),dp) 
 adjYuYuadjYdYd = Matmul(adjYu,YuadjYdYd) 
 adjYuYuadjYuYu = Matmul(adjYu,YuadjYuYu) 
Forall(i2=1:3)  adjYuYuadjYuYu(i2,i2) =  Real(adjYuYuadjYuYu(i2,i2),dp) 
 YdadjYdYdadjYdYd = Matmul(Yd,adjYdYdadjYdYd) 
 YdadjYdYdadjYuYu = Matmul(Yd,adjYdYdadjYuYu) 
 YdadjYuYuadjYdYd = Matmul(Yd,adjYuYuadjYdYd) 
 YdadjYuYuadjYuYu = Matmul(Yd,adjYuYuadjYuYu) 
 YeadjYeYeadjYeYe = Matmul(Ye,adjYeYeadjYeYe) 
 YuadjYdYdadjYdYd = Matmul(Yu,adjYdYdadjYdYd) 
 YuadjYdYdadjYuYu = Matmul(Yu,adjYdYdadjYuYu) 
 YuadjYuYuadjYdYd = Matmul(Yu,adjYuYuadjYdYd) 
 YuadjYuYuadjYuYu = Matmul(Yu,adjYuYuadjYuYu) 
 adjYdYdadjYdYdadjYd = Matmul(adjYd,YdadjYdYdadjYd) 
 adjYdYdadjYuYuadjYd = Matmul(adjYd,YdadjYuYuadjYd) 
 adjYeYeadjYeYeadjYe = Matmul(adjYe,YeadjYeYeadjYe) 
 adjYuYuadjYdYdadjYd = Matmul(adjYu,YuadjYdYdadjYd) 
 adjYuYuadjYuYuadjYd = Matmul(adjYu,YuadjYuYuadjYd) 
 adjYuYuadjYuYuadjYu = Matmul(adjYu,YuadjYuYuadjYu) 
 YdadjYdYdadjYdYdadjYd = Matmul(Yd,adjYdYdadjYdYdadjYd) 
Forall(i2=1:3)  YdadjYdYdadjYdYdadjYd(i2,i2) =  Real(YdadjYdYdadjYdYdadjYd(i2,i2),dp) 
 YdadjYdYdadjYuYuadjYd = Matmul(Yd,adjYdYdadjYuYuadjYd) 
 YdadjYuYuadjYdYdadjYd = Matmul(Yd,adjYuYuadjYdYdadjYd) 
 YdadjYuYuadjYuYuadjYd = Matmul(Yd,adjYuYuadjYuYuadjYd) 
Forall(i2=1:3)  YdadjYuYuadjYuYuadjYd(i2,i2) =  Real(YdadjYuYuadjYuYuadjYd(i2,i2),dp) 
 YeadjYeYeadjYeYeadjYe = Matmul(Ye,adjYeYeadjYeYeadjYe) 
Forall(i2=1:3)  YeadjYeYeadjYeYeadjYe(i2,i2) =  Real(YeadjYeYeadjYeYeadjYe(i2,i2),dp) 
 YuadjYuYuadjYuYuadjYu = Matmul(Yu,adjYuYuadjYuYuadjYu) 
Forall(i2=1:3)  YuadjYuYuadjYuYuadjYu(i2,i2) =  Real(YuadjYuYuadjYuYuadjYu(i2,i2),dp) 
 TrYdadjYuYuadjYd = Real(cTrace(YdadjYuYuadjYd),dp)  
 TrYdadjYdYdadjYdYdadjYd = Real(cTrace(YdadjYdYdadjYdYdadjYd),dp)  
 TrYdadjYdYdadjYuYuadjYd = cTrace(YdadjYdYdadjYuYuadjYd)
 TrYdadjYuYuadjYdYdadjYd = cTrace(YdadjYuYuadjYdYdadjYd)
 TrYdadjYuYuadjYuYuadjYd = Real(cTrace(YdadjYuYuadjYuYuadjYd),dp)  
 TrYeadjYeYeadjYeYeadjYe = Real(cTrace(YeadjYeYeadjYeYeadjYe),dp)  
 TrYuadjYuYuadjYuYuadjYu = Real(cTrace(YuadjYuYuadjYuYuadjYu),dp)  
 g1p6 =g1**6 
 g2p6 =g2**6 
 g3p4 =g3**4 
 Xip2 =Xi**2 
 Lamp3 =Lam**3 
End If 
 
 
!-------------------- 
! g1 
!-------------------- 
 
betag11  = 41._dp*(g1p3)/10._dp

 
 
If (TwoLoopRGE) Then 
betag12 = (g1p3*(199._dp*(g1p2) + 135._dp*(g2p2) + 440._dp*(g3p2) - 25._dp*(TrYdadjYd) -        & 
&  75._dp*(TrYeadjYe) - 85._dp*(TrYuadjYu)))/50._dp

 
Dg1 = oo16pi2*( betag11 + oo16pi2 * betag12 ) 

 
Else 
Dg1 = oo16pi2* betag11 
End If 
 
 
!-------------------- 
! g2 
!-------------------- 
 
betag21  = -19._dp*(g2p3)/6._dp

 
 
If (TwoLoopRGE) Then 
betag22 = (g2p3*(27._dp*(g1p2) + 175._dp*(g2p2) + 360._dp*(g3p2) - 45._dp*(TrYdadjYd) -         & 
&  15._dp*(TrYeadjYe) - 45._dp*(TrYuadjYu)))/30._dp

 
Dg2 = oo16pi2*( betag21 + oo16pi2 * betag22 ) 

 
Else 
Dg2 = oo16pi2* betag21 
End If 
 
 
!-------------------- 
! g3 
!-------------------- 
 
betag31  = -7._dp*(g3p3)

 
 
If (TwoLoopRGE) Then 
betag32 = -(g3p3*(-11._dp*(g1p2) - 45._dp*(g2p2) + 260._dp*(g3p2) + 20._dp*(TrYdadjYd) +        & 
&  20._dp*(TrYuadjYu)))/10._dp

betag33 = (65._dp*g3**7)/2._dp - 40*g3**5*Yt**2 + 15*g3**3*Yt**4

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 + oo16pi2**2*betag33 ) 

 
Else 
Dg3 = oo16pi2* betag31 
End If 
 
 
!-------------------- 
! Lam 
!-------------------- 
 
betaLam1  = 27._dp*(g1p4)/100._dp + (9*g1p2*g2p2)/10._dp + 9._dp*(g2p4)               & 
& /4._dp + 12._dp*(Lamp2) - 12._dp*(TrYdadjYdYdadjYd) - 4._dp*(TrYeadjYeYeadjYe)         & 
&  - 12._dp*(TrYuadjYuYuadjYu) - (9*g1p2*Lam)/5._dp - 9*g2p2*Lam + 12*TrYdadjYd*Lam +    & 
&  4*TrYeadjYe*Lam + 12*TrYuadjYu*Lam

 
 
If (TwoLoopRGE) Then 
betaLam2 = -3411._dp*(g1p6)/1000._dp - (1677*g1p4*g2p2)/200._dp - (289*g1p2*g2p4)/40._dp +       & 
&  305._dp*(g2p6)/8._dp + (54*g1p2*Lamp2)/5._dp + 54*g2p2*Lamp2 - 78._dp*(Lamp3) +       & 
&  (8*g1p2*TrYdadjYdYdadjYd)/5._dp - 64*g3p2*TrYdadjYdYdadjYd + 60._dp*(TrYdadjYdYdadjYdYdadjYd) -& 
&  24._dp*(TrYdadjYdYdadjYuYuadjYd) + 12._dp*(TrYdadjYuYuadjYdYdadjYd) - 12._dp*(TrYdadjYuYuadjYuYuadjYd) -& 
&  (24*g1p2*TrYeadjYeYeadjYe)/5._dp + 20._dp*(TrYeadjYeYeadjYeYeadjYe) - (171*g1p4*TrYuadjYu)/50._dp +& 
&  (63*g1p2*g2p2*TrYuadjYu)/5._dp - (9*g2p4*TrYuadjYu)/2._dp - 72*Lamp2*TrYuadjYu -      & 
&  (16*g1p2*TrYuadjYuYuadjYu)/5._dp - 64*g3p2*TrYuadjYuYuadjYu + 60._dp*(TrYuadjYuYuadjYuYuadjYu) +& 
&  (1887*g1p4*Lam)/200._dp + (117*g1p2*g2p2*Lam)/20._dp - (73*g2p4*Lam)/8._dp -          & 
&  3*TrYdadjYdYdadjYd*Lam - 42*TrYdadjYuYuadjYd*Lam - TrYeadjYeYeadjYe*Lam +             & 
&  (17*g1p2*TrYuadjYu*Lam)/2._dp + (45*g2p2*TrYuadjYu*Lam)/2._dp + 80*g3p2*TrYuadjYu*Lam -& 
&  3*TrYuadjYuYuadjYu*Lam + (TrYdadjYd*(9._dp*(g1p4) - 45._dp*(g2p4) + 225*g2p2*Lam +    & 
&  80*(10._dp*(g3p2) - 9._dp*(Lam))*Lam + g1p2*(54._dp*(g2p2) + 25._dp*(Lam))))/10._dp - & 
&  (3*TrYeadjYe*(15._dp*(g1p4) - g1p2*(22._dp*(g2p2) + 25._dp*(Lam)) + 5*(g2p4 +         & 
&  16._dp*(Lamp2) - 5*g2p2*Lam)))/10._dp


betaLam3 =   (5238*Lam**3*Yt**2 + Lam*Yt**2*(24*g3**2*Yt**2*(895 - 1296*Z3) + 27*Yt**4*(13 - 176*Z3) &
& + 32*g3**4*(311 - 36*Z3)) + 36*Lam**4*(299 + 168*Z3) + &
& 2*Yt**4*(16*g3**4*(-133 + 48*Z3) - 9*Yt**4*(533 + 96*Z3) + 48*g3**2*Yt**2*(-19 + 120*Z3)) + &
& 54*Lam**2*Yt**2*(16*g3**2*(-17 + 16*Z3) + Yt**2*(191 + 168*Z3)))/48._dp
 
DLam = oo16pi2*( betaLam1 + oo16pi2 * betaLam2 + oo16pi2**2*betaLam3 ) 

 
Else 
DLam = oo16pi2* betaLam1 
End If 
 
 
Call Chop(DLam) 

!-------------------- 
! Yu 
!-------------------- 
 
betaYu1  = (-17._dp*(g1p2)/20._dp - 9._dp*(g2p2)/4._dp - 8._dp*(g3p2) +               & 
&  3._dp*(TrYdadjYd) + TrYeadjYe + 3._dp*(TrYuadjYu))*Yu - (3*(YuadjYdYd -               & 
&  YuadjYuYu))/2._dp

 
 
If (TwoLoopRGE) Then 
betaYu2 = ((1187._dp*(g1p4) - 270*g1p2*g2p2 - 3450._dp*(g2p4) + 760*g1p2*g3p2 + 5400*g2p2*g3p2 -& 
&  64800._dp*(g3p4) + 900._dp*(Lamp2) + 375*(g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2))*TrYdadjYd -& 
&  4050._dp*(TrYdadjYdYdadjYd) + 900._dp*(TrYdadjYuYuadjYd) + 1125*(g1p2 +               & 
&  g2p2)*TrYeadjYe - 1350._dp*(TrYeadjYeYeadjYe) + 1275*g1p2*TrYuadjYu + 3375*g2p2*TrYuadjYu +& 
&  12000*g3p2*TrYuadjYu - 4050._dp*(TrYuadjYuYuadjYu))*Yu)/600._dp + ((-43._dp*(g1p2) +  & 
&  45._dp*(g2p2) - 1280._dp*(g3p2) + 300._dp*(TrYdadjYd) + 100._dp*(TrYeadjYe) +         & 
&  300._dp*(TrYuadjYu))*YuadjYdYd + 20*(11._dp*(YuadjYdYdadjYdYd) - YuadjYdYdadjYuYu -   & 
&  4._dp*(YuadjYuYuadjYdYd) + 6._dp*(YuadjYuYuadjYuYu)) + YuadjYuYu*(223._dp*(g1p2) +    & 
&  675._dp*(g2p2) + 1280._dp*(g3p2) - 540._dp*(TrYdadjYd) - 180._dp*(TrYeadjYe) -        & 
&  540._dp*(TrYuadjYu) - 480._dp*(Lam)))/80._dp

betaYu3 =  (Yt*(48*g3**2*(8*Lam*Yt**2 - 157*Yt**4) + 8*g3**4*Yt**2*(3827 - 1368*Z3) + &
& 32*g3**6*(-2083 + 960*Z3) + 9*(-24*Lam**3 + 5*Lam**2*Yt**2 + 528*Lam*Yt**4 + &
& 2*Yt**6*(113 + 36*Z3))))/48._dp

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 
DYu(3,3) = DYu(3,3) +  oo16pi2**3*betaYu3 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-((g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2) - 12._dp*(TrYdadjYd)               & 
&  - 4._dp*(TrYeadjYe) - 12._dp*(TrYuadjYu))*Yd) + 6*(YdadjYdYd - YdadjYuYu))/4._dp

 
 
If (TwoLoopRGE) Then 
betaYd2 = (-127._dp*(g1p4)/600._dp - (27*g1p2*g2p2)/20._dp - 23._dp*(g2p4)/4._dp +              & 
&  (31*g1p2*g3p2)/15._dp + 9*g2p2*g3p2 - 108._dp*(g3p4) + 3._dp*(Lamp2)/2._dp +          & 
&  (5*(g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2))*TrYdadjYd)/8._dp - 27._dp*(TrYdadjYdYdadjYd)/4._dp +& 
&  3._dp*(TrYdadjYuYuadjYd)/2._dp + (15*(g1p2 + g2p2)*TrYeadjYe)/8._dp - 9._dp*(TrYeadjYeYeadjYe)/4._dp +& 
&  (17*g1p2*TrYuadjYu)/8._dp + (45*g2p2*TrYuadjYu)/8._dp + 20*g3p2*TrYuadjYu -           & 
&  27._dp*(TrYuadjYuYuadjYu)/4._dp)*Yd + ((-79._dp*(g1p2) + 45._dp*(g2p2) -              & 
&  1280._dp*(g3p2) + 300._dp*(TrYdadjYd) + 100._dp*(TrYeadjYe) + 300._dp*(TrYuadjYu))*YdadjYuYu +& 
&  20*(6._dp*(YdadjYdYdadjYdYd) - 4._dp*(YdadjYdYdadjYuYu) - YdadjYuYuadjYdYd +          & 
&  11._dp*(YdadjYuYuadjYuYu)) + YdadjYdYd*(187._dp*(g1p2) + 675._dp*(g2p2) +             & 
&  1280._dp*(g3p2) - 540._dp*(TrYdadjYd) - 180._dp*(TrYeadjYe) - 540._dp*(TrYuadjYu) -   & 
&  480._dp*(Lam)))/80._dp

 
DYd = oo16pi2*( betaYd1 + oo16pi2 * betaYd2 ) 

 
Else 
DYd = oo16pi2* betaYd1 
End If 
 
 
Call Chop(DYd) 

!-------------------- 
! Ye 
!-------------------- 
 
betaYe1  = (-9._dp*(g1p2)/4._dp - 9._dp*(g2p2)/4._dp + 3._dp*(TrYdadjYd)              & 
&  + TrYeadjYe + 3._dp*(TrYuadjYu))*Ye + 3._dp*(YeadjYeYe)/2._dp

 
 
If (TwoLoopRGE) Then 
betaYe2 = ((2742._dp*(g1p4) + 540*g1p2*g2p2 - 2300._dp*(g2p4) + 600._dp*(Lamp2) +               & 
&  250*(g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2))*TrYdadjYd - 2700._dp*(TrYdadjYdYdadjYd) +   & 
&  600._dp*(TrYdadjYuYuadjYd) + 750*(g1p2 + g2p2)*TrYeadjYe - 900._dp*(TrYeadjYeYeadjYe) +& 
&  850*g1p2*TrYuadjYu + 2250*g2p2*TrYuadjYu + 8000*g3p2*TrYuadjYu - 2700._dp*(TrYuadjYuYuadjYu))*Ye +& 
&  15*(40._dp*(YeadjYeYeadjYeYe) + YeadjYeYe*(129._dp*(g1p2) + 225._dp*(g2p2) -          & 
&  180._dp*(TrYdadjYd) - 60._dp*(TrYeadjYe) - 180._dp*(TrYuadjYu) - 160._dp*(Lam))))/400._dp

 
DYe = oo16pi2*( betaYe1 + oo16pi2 * betaYe2 ) 

 
Else 
DYe = oo16pi2* betaYe1 
End If 
 
 
Call Chop(DYe) 

!-------------------- 
! Mu 
!-------------------- 
 
betaMu1  = (-9*g1p2*Mu)/10._dp - (9*g2p2*Mu)/2._dp + 6*Mu*TrYdadjYd + 2*Mu*TrYeadjYe +& 
&  6*Mu*TrYuadjYu + 6*Mu*Lam

 
 
If (TwoLoopRGE) Then 
betaMu2 = (Mu*(1671._dp*(g1p4) + 450*g1p2*g2p2 - 3625._dp*(g2p4) - 6000._dp*(Lamp2) -           & 
&  5400._dp*(TrYdadjYdYdadjYd) - 8400._dp*(TrYdadjYuYuadjYd) - 1800._dp*(TrYeadjYeYeadjYe) +& 
&  1700*g1p2*TrYuadjYu + 4500*g2p2*TrYuadjYu + 16000*g3p2*TrYuadjYu - 5400._dp*(TrYuadjYuYuadjYu) +& 
&  100*TrYdadjYd*(5._dp*(g1p2) + 45._dp*(g2p2) + 160._dp*(g3p2) - 144._dp*(Lam)) +       & 
&  300*TrYeadjYe*(5._dp*(g1p2) + 5._dp*(g2p2) - 16._dp*(Lam)) + 2880*g1p2*Lam +          & 
&  14400*g2p2*Lam - 14400*TrYuadjYu*Lam))/400._dp

 
DMu = oo16pi2*( betaMu1 + oo16pi2 * betaMu2 ) 

 
Else 
DMu = oo16pi2* betaMu1 
End If 
 
 
Call Chop(DMu) 

!-------------------- 
! v 
!-------------------- 
 
betav1  = (v*(9._dp*(g1p2) + 45._dp*(g2p2) - 60._dp*(TrYdadjYd) - 20._dp*(TrYeadjYe)  & 
&  - 60._dp*(TrYuadjYu) + 3*g1p2*Xi + 15*g2p2*Xi))/20._dp

 
 
If (TwoLoopRGE) Then 
betav2 = (v*(-1293._dp*(g1p4) - 270*g1p2*g2p2 + 6775._dp*(g2p4) - 1200._dp*(Lamp2) +           & 
&  5400._dp*(TrYdadjYdYdadjYd) - 1200._dp*(TrYdadjYuYuadjYd) + 1800._dp*(TrYeadjYeYeadjYe) -& 
&  1700*g1p2*TrYuadjYu - 4500*g2p2*TrYuadjYu - 16000*g3p2*TrYuadjYu + 5400._dp*(TrYuadjYuYuadjYu) +& 
&  18*g1p4*Xi + 180*g1p2*g2p2*Xi + 2250*g2p4*Xi - 360*g1p2*TrYuadjYu*Xi - 1800*g2p2*TrYuadjYu*Xi -& 
&  60*TrYeadjYe*(5*g2p2*(5 + 2._dp*(Xi)) + g1p2*(25 + 2._dp*(Xi))) - 20*TrYdadjYd*(800._dp*(g3p2) +& 
&  45*g2p2*(5 + 2._dp*(Xi)) + g1p2*(25 + 18._dp*(Xi))) + 18*g1p4*Xip2 + 180*g1p2*g2p2*Xip2 -& 
&  450*g2p4*Xip2))/800._dp

 
Dv = oo16pi2*( betav1 + oo16pi2 * betav2 ) 

 
Else 
Dv = oo16pi2* betav1 
End If 
 
 
Call ParametersToG62_SM(Dg1,Dg2,Dg3,DLam,DYu,DYd,DYe,DMu,Dv,f)

Iname = Iname - 1 
 
End Subroutine rge62_SM 

End Module RGEs_SM_HC
 
