! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:54 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module RunSM_Inert2 
 
Use Control 
Use Settings 
Use LoopFunctions 
Use Mathematics 
Use StandardModel 
Use RGEs_Inert2 
Use RGEs_SM_HC 
Use Model_Data_Inert2 

Logical,Private,Save::OnlyDiagonal 
Contains 
 
 Subroutine RunSM_and_SUSY_RGEs(Qout,g1input,g2input,g3input,lam5input,lam1input,      & 
& lam4input,lam3input,lam2input,Yeinput,Ydinput,Yuinput,MHD2input,MHU2input,             & 
& vinput,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,CKMout,sinW2_out,        & 
& Alpha_out,AlphaS_out,realCKM)

Implicit None 
Real(dp),Intent(in) :: g1input,g2input,g3input,MHD2input,MHU2input,vinput

Complex(dp),Intent(in) :: lam5input,lam1input,lam4input,lam3input,lam2input,Yeinput(3,3),Ydinput(3,3),          & 
& Yuinput(3,3)

Real(dp),Intent(out) :: g1,g2,g3,MHD2,MHU2,v

Complex(dp),Intent(out) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp), Intent(in) :: Qout 
Complex(dp), Intent(out) :: CKMout(3,3) 
Real(dp), Intent(out) :: sinW2_out, Alpha_out, AlphaS_out 
Complex(dp) :: YdSM(3,3), YuSM(3,3), YeSM(3,3) 
Real(dp) :: g1SM, g2SM, g3SM, vSM 
Complex(dp) :: lambdaSM, muSM, dummy(3,3) 
Integer :: kont 
Logical :: OnlyDiagonal 
Logical :: realCKM 
Real(dp) :: deltaM = 0.000001_dp, test(3)  
Real(dp) :: scale_save, Qin, tz, dt, g1D(70), g62_SM(62) 
 
 
! Run SUSY RGEs from M_SUSY to Qin 
Qin=sqrt(getRenormalizationScale()) 
scale_save = Qin 
Call ParametersToG70(g1input,g2input,g3input,lam5input,lam1input,lam4input,           & 
& lam3input,lam2input,Yeinput,Ydinput,Yuinput,MHD2input,MHU2input,vinput,g1D)

Call GToParameters70(g1D,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v)

g1 = Sqrt(3._dp/5._dp)*g1 


! Run SM RGEs from MZ to Qin 
If (RunningSMparametersLowEnergy) Then 
! Run SM RGEs separately 
 
! Get values of gauge and Yukawa couplings at M_Z 
Call GetRunningSMparametersMZ(YdSM,YeSM,YuSM,g1SM,g2SM,g3SM,lambdaSM,muSM,            & 
& vSM,realCKM)

Call ParametersToG62_SM(g1SM, g2SM, g3SM, lambdaSM, YuSM, YdSM, YeSM, muSM, vSM, g62_SM) 
! Run to output scale 
tz=Log(sqrt(MZ2)/Qout) 
dt=tz/100._dp 
Call odeint(g62_SM,62,tz,0._dp,deltaM,dt,0._dp,rge62_SM,kont)

Call GtoParameters62_SM(g62_SM, g1SM, g2SM, g3SM, lambdaSM, YuSM, YdSM, YeSM, muSM, vSM) 
 
! Overwrite values obtained from SUSY running 
g1 = g1SM 
g2 = g2SM 
g3 = g3SM 
v=vSM 
Yu = YuSM 
Yd = YdSM 
Ye = YeSM 
! Calculate running CKM matrix 
Call FermionMass(YuSM,1._dp,test,dummy,CKMout,kont) 
 

 
 ! Output values for running SM constants 
sinW2_out = g1SM**2/(g1SM**2+g2SM**2) 
Alpha_out = sinW2_out*g2SM**2/(4._dp*Pi) 
AlphaS_out = g3SM**2/(4._dp*Pi) 
 
Else 

! Don't run SM RGEs separately 
If (YukawaScheme.Eq.1) Then 
  Call FermionMass(Yu,1._dp,test,dummy,CKMout,kont) 
Else 
  Call FermionMass(Yd,1._dp,test,dummy,CKMout,kont) 
  CKMout=Conjg(Transpose(CKMout)) 
End if 
sinW2_out = g1**2/(g1**2+g2**2) 
Alpha_out = sinW2_out*g2**2/(4._dp*Pi) 
AlphaS_out = g3**2/(4._dp*Pi) 
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,v,g1,g2,g3,              & 
& lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,.False.)

End if 

Qin = SetRenormalizationScale(Qout**2) 
End Subroutine RunSM_and_SUSY_RGEs 
 
 
Subroutine GetRunningSMparametersMZ(YdSM,YeSM,YuSM,g1SM,g2SM,g3SM,lambdaSM,           & 
& muSM,vSM,realCKM)

Implicit None 
Complex(dp), Intent(out) :: YdSM(3,3), YuSM(3,3), YeSM(3,3) 
Real(dp), Intent(out) :: g1SM, g2SM, g3SM, vSM 
Complex(dp), Intent(out) :: lambdaSM, muSM 
Real(dp) :: vev2, sinW2, CosW2SinW2 
Real(dp) :: gSM2(2), gSM3(3), mtopMS, mtopMS_MZ 
Real(dp) :: dt, tz
Real(dp) :: deltaM = 0.000001_dp, test(3)  
Logical :: realCKM 
Integer :: i1,kont 
 
 
SinW2=0.22290_dp 
CosW2SinW2=(1._dp-sinW2)*sinW2 
vev2=mZ2*CosW2SinW2/(pi*Alpha_mZ) -0 
vSM = sqrt(vev2) 
 
YdSM = 0._dp 
YeSM = 0._dp 
YuSM = 0._dp 
 
Do i1=1,3 
YdSM(i1,i1) = sqrt2*mf_d_mz(i1)/vSM 
YeSM(i1,i1) = sqrt2*mf_l_mz(i1)/vSM 
YuSM(i1,i1) = sqrt2*mf_u_mz(i1)/vSM 
End do 
 

! Calculating m_top(M_Z) 
gSM2(1)=sqrt(Alpha_mZ*4*Pi) 
gSM2(2)=sqrt(AlphaS_mZ*4*Pi) 
tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM2,2,tz,0._dp,deltaM,dt,0._dp,RGEAlphaS,kont) 
 
!m_top^pole to m_top^MS(m_top) 
mtopMS=mf_u(3)*(1._dp-4._dp/3._dp*(gSM2(2)**2/4._dp/Pi )/Pi) 

!Running m_top^MS(m_top) to M_Z 
gSM3(1)=gSM2(1) 
gSM3(2)=gSM2(2) 
gSM3(3)=mtopMS 
tz=Log(sqrt(mz2)/mf_u(3)) 
dt=tz/50._dp 
Call odeint(gSM3,3,0._dp,tz,deltaM,dt,0._dp,RGEtop,kont) 
mtopMS_MZ=gSM3(3) 
YuSM(3,3) = sqrt2*mtopMS_MZ/vSM 
 

If (realCKM) Then 
 YuSM = Transpose(Matmul(Transpose(Real(CKMcomplex,dp)),Transpose(YuSM))) 
Else 
 YuSM = Transpose(Matmul(Transpose(CKMcomplex),Transpose(YuSM))) 
End if 
g1SM=sqrt(Alpha_MZ/(1-sinW2)*4._dp*Pi) 
g2SM=sqrt(Alpha_MZ/sinW2*4._dp*Pi) 
g3SM=sqrt(AlphaS_MZ*4._dp*Pi) 
 
lambdaSM = 0._dp 
muSM = 0._dp 
 
End Subroutine GetRunningSMparametersMZ 

End Module RunSM_Inert2 
