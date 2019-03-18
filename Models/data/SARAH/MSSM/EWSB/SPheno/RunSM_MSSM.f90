! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:03 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module RunSM_MSSM 
 
Use Control 
Use LoopFunctions 
Use Mathematics 
Use StandardModel 
Use RGEs_MSSM 
Use Model_Data_MSSM 

Logical,Private,Save::OnlyDiagonal 
Contains 
 
 Subroutine RunSM_and_SUSY_RGEs(Qout,g1input,g2input,g3input,Ydinput,Yeinput,          & 
& Yuinput,Muinput,Tdinput,Teinput,Tuinput,Bmuinput,mq2input,ml2input,mHd2input,          & 
& mHu2input,md2input,mu2input,me2input,M1input,M2input,M3input,vdinput,vuinput,          & 
& g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,              & 
& vd,vu,CKMout,sinW2_out,Alpha_out,AlphaS_out,realCKM)

Implicit None 
Real(dp),Intent(in) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(in) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp),Intent(out) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp),Intent(out) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp), Intent(in) :: Qout 
Complex(dp), Intent(out) :: CKMout(3,3) 
Real(dp), Intent(out) :: sinW2_out, Alpha_out, AlphaS_out 
Complex(dp) :: YdSM(3,3), YuSM(3,3), YeSM(3,3) 
Real(dp) :: g1SM, g2SM, g3SM, vevSM 
Complex(dp) :: lambdaSM, muSM, dummy(3,3) 
Integer :: kont 
Logical :: OnlyDiagonal 
Logical :: realCKM 
Real(dp) :: deltaM = 0.000001_dp, test(3)  
Complex(dp) :: Yd_ckm(3,3), Yu_ckm(3,3), Tu_ckm(3,3), Td_ckm(3,3), mq2_ckm(3,3), mu2_ckm(3,3), md2_ckm(3,3) 
Complex(dp) :: Yd_out(3,3), Yu_out(3,3), Tu_out(3,3), Td_out(3,3), mq2_out(3,3), mu2_out(3,3), md2_out(3,3) 
Real(dp) :: scale_save, Qin, tz, dt, g1D(215), g62_SM(62) 
 
 
! Run SUSY RGEs from M_SUSY to Qin 
Qin=sqrt(getRenormalizationScale()) 
scale_save = Qin 
Call ParametersToG215(g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,Muinput,        & 
& Tdinput,Teinput,Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,md2input,       & 
& mu2input,me2input,M1input,M2input,M3input,vdinput,vuinput,g1D)

If (RunningSUSYparametersLowEnergy) Then 
tz=Log(Qout/Qin) 
dt=tz/100._dp 
Call odeint(g1D,215,0._dp,tz,deltaM,dt,0._dp,rge215,kont)

End if 

Call GToParameters215(g1D,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,             & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu)

g1 = Sqrt(3._dp/5._dp)*g1 


If (GenerationMixing) Then 
Call Switch_to_superCKM(Yd(1:3,1:3),Yu(1:3,1:3),Td(1:3,1:3),Tu(1:3,1:3),md2(1:3,1:3),mq2(1:3,1:3),mu2(1:3,1:3) &
&,Td_ckm, Tu_ckm,md2_ckm,mq2_ckm,mu2_ckm, .False., Yd_ckm, Yu_ckm)
Else 
Td_ckm = Td(1:3,1:3) 
Tu_ckm = Tu(1:3,1:3) 
Yd_ckm = Yd(1:3,1:3) 
Yu_ckm = Yu(1:3,1:3) 
mq2_ckm = mq2(1:3,1:3) 
md2_ckm = md2(1:3,1:3) 
mu2_ckm = mu2(1:3,1:3) 
End If 
! Run SM RGEs from MZ to Qin 
If (RunningSMparametersLowEnergy) Then 
! Run SM RGEs separately 
 
! Get values of gauge and Yukawa couplings at M_Z 
Call GetRunningSMparametersMZ(YdSM,YeSM,YuSM,g1SM,g2SM,g3SM,lambdaSM,muSM,            & 
& vevSM,realCKM)

Call ParametersToG62_SM(g1SM, g2SM, g3SM, lambdaSM, YuSM, YdSM, YeSM, muSM, vevSM, g62_SM) 
! Run to output scale 
tz=Log(sqrt(MZ2)/Qout) 
dt=tz/100._dp 
Call odeint(g62_SM,62,tz,0._dp,deltaM,dt,0._dp,rge62_SM,kont)

Call GtoParameters62_SM(g62_SM, g1SM, g2SM, g3SM, lambdaSM, YuSM, YdSM, YeSM, muSM, vevSM) 
 
! Overwrite values obtained from SUSY running 
g1 = g1SM 
g2 = g2SM 
g3 = g3SM 
vd=vevSM/Sqrt(1._dp+TanBeta**2) 
vu=TanBeta*vd 
Yu = YuSM*Sqrt(1._dp+TanBeta**2)/TanBeta 
Yd = YdSM*Sqrt(1._dp+TanBeta**2) 
Ye = YeSM*Sqrt(1._dp+TanBeta**2) 
! Calculate running CKM matrix 
Call FermionMass(YuSM,1._dp,test,dummy,CKMout,kont) 
 
! Rotating from SCKM to EW basis 
Call Switch_from_superCKM(YdSM, YuSM, Td_ckm, Tu_ckm, md2_ckm, mq2_ckm, mu2_ckm& 
&, Td,Tu,md2,mq2,mu2,.True.) 

 
 ! Output values for running SM constants 
sinW2_out = g1SM**2/(g1SM**2+g2SM**2) 
Alpha_out = sinW2_out*g2SM**2/(4._dp*Pi) 
AlphaS_out = g3SM**2/(4._dp*Pi) 
 
Else 

! Don't run SM RGEs separately 
Call FermionMass(Yu,1._dp,test,dummy,CKMout,kont) 
sinW2_out = g1**2/(g1**2+g2**2) 
Alpha_out = sinW2_out*g2**2/(4._dp*Pi) 
AlphaS_out = g3**2/(4._dp*Pi) 
End if 

Qin = SetRenormalizationScale(Qout**2) 

 Contains 

Subroutine Switch_to_superCKM(Y_d, Y_u, Ad_in, Au_in, MD_in, MQ_in, MU_in &
                      &, Ad_out, Au_out, MD_out, MQ_out, MU_out, tr        &
                      &,  Yd_out, Yu_out )
 !---------------------------------------------------------------------------
 ! shifts the parameter from the electroweak basis to the super CKM basis
 ! written by werner Porod, 12.03.08
 !---------------------------------------------------------------------------
 Implicit None
  Complex(dp), Intent(in), Dimension(3,3) :: Y_d, Y_u, Au_in, Ad_in, MD_in &
        & , MQ_in, MU_in
!   Complex(dp), Optional, Intent(in), Dimension(6,6) :: RSu_in, RSd_in
  Logical, Intent(in) :: tr  ! if true, then the matrices are transposed 
                             ! compared to low energy definition
  Complex(dp), Intent(out), Dimension(3,3) :: Au_out, Ad_out, MD_out, MQ_out &
        & , MU_out, Yd_out, Yu_out
!   Complex(dp), Optional, Intent(out), Dimension(6,6) :: RSu_out, RSd_out
!   Complex(dp), Optional, Intent(out) :: CKM_out(3,3)

  Complex(dp), Dimension(3,3) :: uU_L, uU_R, uD_L, uD_R, CKM_Q
  Complex(dp) :: rot(6,6), Ephi

  Real(dp) :: mf(3), s12, s23, aR, aI, s13, c13
  Integer :: ierr

  !------------------------------------------
  ! diagonalizing d- and u-Yukawa couplings
  ! I am only interested in the mixing matrices
  !------------------------------------------

   Call FermionMass(Y_u, 1._dp, mf, uU_L, uU_R, ierr)
   Call FermionMass(Y_d, 1._dp, mf, uD_L, uD_R, ierr)
   Yu_out = MatMul(MatMul(conjg(uU_L),Y_u),Transpose(conjg(uU_R)))
   Yd_out = MatMul(MatMul(conjg(uD_L),Y_d),Transpose(conjg(uD_R)))

  !---------------------------------------------------------
  ! CKM matrix at Q, shifting phases according to PDG form
  !---------------------------------------------------------
  CKM_Q =  Matmul(uU_R, Transpose(Conjg(ud_R)) )
  uD_L(1,:) = uD_L(1,:) / Conjg(CKM_Q(1,1)) * Abs(CKM_Q(1,1))
  uD_L(2,:) = uD_L(2,:) / Conjg(CKM_Q(1,2)) * Abs(CKM_Q(1,2))
  uU_L(2,:) = uU_L(2,:) / CKM_Q(2,3) * Abs(CKM_Q(2,3))
  uU_L(3,:) = uU_L(3,:) / CKM_Q(3,3) * Abs(CKM_Q(3,3))
  !-------------------------------------------------------------------
  ! also the right quark must be multiplied with the conjugate phase
  ! as otherwise the masses get complex
  !-------------------------------------------------------------------
  uD_R(1,:) = uD_R(1,:) / CKM_Q(1,1) * Abs(CKM_Q(1,1))
  uD_R(2,:) = uD_R(2,:) / CKM_Q(1,2) * Abs(CKM_Q(1,2))
  uU_R(2,:) = uU_R(2,:) * Abs(CKM_Q(2,3)) / Conjg(CKM_Q(2,3))
  uU_R(3,:) = uU_R(3,:) * Abs(CKM_Q(3,3)) / Conjg(CKM_Q(3,3))
  CKM_Q =  Matmul(uU_L, Transpose(Conjg(ud_L)) )

  !--------------------------------------------------------------
  ! one more freedom left
  !--------------------------------------------------------------
  s13 = Abs(CKM_Q(1,3))
  c13 = sqrt(1._dp - s13**2)
  s23 = Abs(CKM_Q(2,3))/c13
  s12 = Abs(CKM_Q(1,2))/c13

  aR = Real(CKM_Q(2,2),dp) + s12 * s23 * Real(CKM_Q(1,3),dp)
  aI =  s12 * s23 * Aimag(CKM_Q(1,3)) - Aimag(CKM_Q(2,2))
  Ephi = Cmplx(aR/Sqrt(aR**2+aI**2),aI/Sqrt(aR**2+aI**2),dp)

  uU_L(2:3,:) = Ephi * uU_L(2:3,:)
  uD_L(3,:) = Ephi * uD_L(3,:)
  Ephi = Conjg(Ephi)
  uU_R(2:3,:) = Ephi * uU_R(2:3,:)
  uD_R(3,:) = Ephi * uD_R(3,:)


  CKM_Q =  Matmul(uU_R, Transpose(Conjg(ud_R)) )

!   If (Present(CKM_out)) CKM_out = CKM_Q
  !-------------------------------------------------------------------
  ! shifting the parameters to the super CKM basis
  !-------------------------------------------------------------------

   Au_out = Matmul( Matmul(Conjg(uU_L), Au_in), Conjg(Transpose(uU_R)))

   Ad_out = Matmul( Matmul(Conjg(uD_L), Ad_in), Conjg(Transpose(uD_R)))


  MD_out = Matmul( Matmul( Conjg(uD_L), Transpose(MD_in)), Transpose(uD_L))
  MU_out = Matmul( Matmul( Conjg(uU_L), Transpose( MU_in)), Transpose(uU_L))
  MQ_out = Matmul( Matmul( uD_R, MQ_in), Transpose(Conjg(uD_R)) )

!    If (Present(RSu_in).And.Present(RSu_out)) Then
!     rot = 0._dp
!     rot(1:3,1:3) = Conjg(uU_L)
!     rot(4:6,4:6) = uU_R
!     RSu_out = Matmul(RSu_in,Transpose(rot))
!    End If
!    If (Present(RSd_in).And.Present(RSd_out)) Then
!     rot = 0._dp
!     rot(1:3,1:3) = Conjg(uD_L)
!     rot(4:6,4:6) = uD_R
!     RSd_out = Matmul(RSd_in,Transpose(rot))
!    End If

 End Subroutine Switch_to_superCKM



Subroutine Switch_from_superCKM(Y_d, Y_u, Ad_in, Au_in, MD_in, MQ_in, MU_in &
                      &, Ad_out, Au_out, MD_out, MQ_out, MU_out, tr      )
 !---------------------------------------------------------------------------
 ! shifts the parameter from the  super CKM basis to the electroweak basis
 ! written by werner Porod, 12.03.08
 !---------------------------------------------------------------------------
 Implicit None
  Complex(dp), Intent(in), Dimension(3,3) :: Y_d, Y_u, Au_in, Ad_in, MD_in &
        & , MQ_in, MU_in
  Logical, Intent(in) :: tr  ! if true, then the matrices are transposed 
                             ! compared to low energy definition
  Complex(dp), Intent(out), Dimension(3,3) :: Au_out, Ad_out, MD_out, MQ_out &
        & , MU_out

  Complex(dp), Dimension(3,3) :: uU_L, uU_R, uD_L, uD_R, CKM_Q
  Complex(dp) :: rot(6,6), Ephi

  Real(dp) :: mf(3), s12, s23, aR, aI, s13, c13
  Integer :: ierr

  !------------------------------------------
  ! diagonalizing d- and u-Yukawa couplings
  ! I am only interested in the mixing matrices
  !------------------------------------------
  If (tr) Then
   Call FermionMass(Transpose(Y_u), 1._dp, mf, uU_L, uU_R, ierr)
!    If (Present(Yu)) Yu = sqrt2 * mf
   Call FermionMass(Transpose(Y_d), 1._dp, mf, uD_L, uD_R, ierr)
!    If (Present(Yd)) Yd = sqrt2 * mf
  Else
   Call FermionMass(Y_u, 1._dp, mf, uU_L, uU_R, ierr)
!    If (Present(Yu)) Yu = sqrt2 * mf
   Call FermionMass(Y_d, 1._dp, mf, uD_L, uD_R, ierr)
!    If (Present(Yd)) Yd = sqrt2 * mf
  End If
  !---------------------------------------------------------
  ! CKM matrix at Q, shifting phases according to PDG form
  !---------------------------------------------------------
  CKM_Q =  Matmul(uU_L, Transpose(Conjg(ud_L)) )
  uD_L(1,:) = uD_L(1,:) / Conjg(CKM_Q(1,1)) * Abs(CKM_Q(1,1))
  uD_L(2,:) = uD_L(2,:) / Conjg(CKM_Q(1,2)) * Abs(CKM_Q(1,2))
  uU_L(2,:) = uU_L(2,:) / CKM_Q(2,3) * Abs(CKM_Q(2,3))
  uU_L(3,:) = uU_L(3,:) / CKM_Q(3,3) * Abs(CKM_Q(3,3))
  !-------------------------------------------------------------------
  ! also the right quark must be multiplied with the conjugate phase
  ! as otherwise the masses get complex
  !-------------------------------------------------------------------
  uD_R(1,:) = uD_R(1,:) / CKM_Q(1,1) * Abs(CKM_Q(1,1))
  uD_R(2,:) = uD_R(2,:) / CKM_Q(1,2) * Abs(CKM_Q(1,2))
  uU_R(2,:) = uU_R(2,:) / Conjg(CKM_Q(2,3)) * Abs(CKM_Q(2,3))
  uU_R(3,:) = uU_R(3,:) / Conjg(CKM_Q(3,3)) * Abs(CKM_Q(3,3))
  CKM_Q =  Matmul(uU_L, Transpose(Conjg(ud_L)) )

  !--------------------------------------------------------------
  ! one more freedom left
  !--------------------------------------------------------------
  s13 = Abs(CKM_Q(1,3))
  c13 = sqrt(1._dp - s13**2)
  s23 = Abs(CKM_Q(2,3))/c13
  s12 = Abs(CKM_Q(1,2))/c13

  aR = Real(CKM_Q(2,2),dp) + s12 * s23 * Real(CKM_Q(1,3),dp)
  aI =  s12 * s23 * Aimag(CKM_Q(1,3)) - Aimag(CKM_Q(2,2))
  Ephi = Cmplx(aR/Sqrt(aR**2+aI**2),aI/Sqrt(aR**2+aI**2),dp)

  uU_L(2:3,:) = Ephi * uU_L(2:3,:)
  uD_L(3,:) = Ephi * uD_L(3,:)
  Ephi = Conjg(Ephi)
  uU_R(2:3,:) = Ephi * uU_R(2:3,:)
  uD_R(3,:) = Ephi * uD_R(3,:)

  CKM_Q =  Matmul(uU_L, Transpose(Conjg(ud_L)) )

    !-------------------------------------------------------------------
  ! shifting the parameters from the super CKM basis
  !-------------------------------------------------------------------
  If (tr) Then
   Au_out = Matmul( Matmul(Transpose(uU_R), Au_in), uU_L)
   Ad_out = Matmul( Matmul(Transpose(uD_R), Ad_in), uD_L)

   MD_out = Matmul( Matmul( Transpose(Conjg(uD_R)), MD_in), uD_R)
   MU_out = Matmul( Matmul( Transpose(Conjg(uU_R)), MU_in), uU_R)
   MQ_out = Matmul( Matmul( Transpose(uD_L), MQ_in), Conjg(uD_L) )

  Else
   Au_out = Matmul( Matmul(Transpose(uU_L), Au_in), uU_R)
   Ad_out = Matmul( Matmul(Transpose(uD_L), Ad_in), uD_R)

   MD_out = Matmul( Matmul( Transpose(uD_R), MD_in), Conjg(uD_R))
   MU_out = Matmul( Matmul( Transpose(uU_R), MU_in), Conjg(uU_R))
   MQ_out = Matmul( Matmul( Transpose(Conjg(uD_L)), MQ_in), uD_L )

  End If
  !------------------------------------------------------------------
  ! to avoid numerical problems ensure that matrices are hermitian
  !-----------------------------------------------------------------
  MD_out = 0.5_dp * ( MD_out + Conjg(Transpose(MD_out)) )
  MU_out = 0.5_dp * ( MU_out + Conjg(Transpose(MU_out)) )
  MQ_out = 0.5_dp * ( MQ_out + Conjg(Transpose(MQ_out)) )

 End Subroutine Switch_from_superCKM

End Subroutine RunSM_and_SUSY_RGEs 
 
 
Subroutine GetRunningSMparametersMZ(YdSM,YeSM,YuSM,g1SM,g2SM,g3SM,lambdaSM,           & 
& muSM,vevSM,realCKM)

Implicit None 
Complex(dp), Intent(out) :: YdSM(3,3), YuSM(3,3), YeSM(3,3) 
Real(dp), Intent(out) :: g1SM, g2SM, g3SM, vevSM 
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
vevSM = sqrt(vev2) 
 
YdSM = 0._dp 
YeSM = 0._dp 
YuSM = 0._dp 
 
Do i1=1,3 
YdSM(i1,i1) = sqrt2*mf_d_mz(i1)/vevSM 
YeSM(i1,i1) = sqrt2*mf_l_mz(i1)/vevSM 
YuSM(i1,i1) = sqrt2*mf_u_mz(i1)/vevSM 
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
YuSM(3,3) = sqrt2*mtopMS_MZ/vevSM 
 

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
& Dg3,v,betav1,betav2,Dv
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
 TrYdadjYuYuadjYd = cTrace(YdadjYuYuadjYd) 
 TrYdadjYdYdadjYdYdadjYd = cTrace(YdadjYdYdadjYdYdadjYd) 
 TrYdadjYdYdadjYuYuadjYd = cTrace(YdadjYdYdadjYuYuadjYd) 
 TrYdadjYuYuadjYdYdadjYd = cTrace(YdadjYuYuadjYdYdadjYd) 
 TrYdadjYuYuadjYuYuadjYd = cTrace(YdadjYuYuadjYuYuadjYd) 
 TrYeadjYeYeadjYeYeadjYe = cTrace(YeadjYeYeadjYeYeadjYe) 
 TrYuadjYuYuadjYuYuadjYu = cTrace(YuadjYuYuadjYuYuadjYu) 
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

 
Dg3 = oo16pi2*( betag31 + oo16pi2 * betag32 ) 

 
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
&  (8*g1p2*TrYdadjYdYdadjYd)/5._dp - 64*g3p2*TrYdadjYdYdadjYd + 60._dp*(TrYdadjYdYdadjYdYdadjYd) +& 
&  12._dp*(TrYdadjYdYdadjYuYuadjYd) - 24._dp*(TrYdadjYuYuadjYdYdadjYd) - 12._dp*(TrYdadjYuYuadjYuYuadjYd) -& 
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

 
DLam = oo16pi2*( betaLam1 + oo16pi2 * betaLam2 ) 

 
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

 
DYu = oo16pi2*( betaYu1 + oo16pi2 * betaYu2 ) 

 
Else 
DYu = oo16pi2* betaYu1 
End If 
 
 
Call Chop(DYu) 

!-------------------- 
! Yd 
!-------------------- 
 
betaYd1  = (-((g1p2 + 9._dp*(g2p2) + 32._dp*(g3p2) - 12._dp*(TrYdadjYd)               & 
&  - 4._dp*(TrYeadjYe) - 12._dp*(TrYuadjYu))*Yd) + 6._dp*(YdadjYdYd) - 6._dp*(YdadjYuYu))/4._dp

 
 
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
 
betav1  = -(v*(-9._dp*(g1p2) - 45._dp*(g2p2) + 60._dp*(TrYdadjYd) + 20._dp*(TrYeadjYe)& 
&  + 60._dp*(TrYuadjYu) + 9*g1p2*Xi + 45*g2p2*Xi))/20._dp

 
 
If (TwoLoopRGE) Then 
betav2 = (v*(-1275._dp*(g1p4) - 90*g1p2*g2p2 + 11425._dp*(g2p4) - 1200._dp*(Lamp2) +           & 
&  5400._dp*(TrYdadjYdYdadjYd) - 1200._dp*(TrYdadjYuYuadjYd) + 1800._dp*(TrYeadjYeYeadjYe) -& 
&  1700*g1p2*TrYuadjYu - 4500*g2p2*TrYuadjYu - 16000*g3p2*TrYuadjYu + 5400._dp*(TrYuadjYuYuadjYu) +& 
&  18*g1p4*Xi + 180*g1p2*g2p2*Xi - 2550*g2p4*Xi - 360*g1p2*TrYuadjYu*Xi - 1800*g2p2*TrYuadjYu*Xi -& 
&  60*TrYeadjYe*(5*g2p2*(5 + 2._dp*(Xi)) + g1p2*(25 + 2._dp*(Xi))) - 20*TrYdadjYd*(800._dp*(g3p2) +& 
&  45*g2p2*(5 + 2._dp*(Xi)) + g1p2*(25 + 18._dp*(Xi))) - 300*g2p4*Xip2))/800._dp

 
Dv = oo16pi2*( betav1 + oo16pi2 * betav2 ) 

 
Else 
Dv = oo16pi2* betav1 
End If 
 
 
Call ParametersToG62_SM(Dg1,Dg2,Dg3,DLam,DYu,DYd,DYe,DMu,Dv,f)

Iname = Iname - 1 
 
End Subroutine rge62_SM  
End Module RunSM_MSSM 
