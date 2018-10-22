! -----------------------------------------------------------------------------
! This file was automatically created by SARAH version 4.9.3
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223
! (c) Florian Staub, 2013
! ------------------------------------------------------------------------------
! File created at 14:16 on 19.10.2018
! ----------------------------------------------------------------------


Module Boundaries_NMSSM

Use Control
Use LoopCouplings_NMSSM
Use LoopMasses_NMSSM
Use LoopFunctions
Use Mathematics
Use Model_Data_NMSSM
Use RGEs_NMSSM
Use RunSM_NMSSM

Use Tadpoles_NMSSM
 Use StandardModel

Integer, save :: YukScen
Real(dp), save :: Lambda, MlambdaS,F_GMSB
Real(dp),save::mGUT_save,sinW2_Q_mZ&
&,mf_l_Q_SM(3),mf_d_Q_SM(3),mf_u_Q_SM(3)
Complex(dp),save::Yl_mZ(3,3),Yu_mZ(3,3),Yd_mZ(3,3)
Real(dp),Save::vevs_DR_save(2), vSM_save
Contains

Subroutine BoundarySUSY(gA,gB)
Implicit None
Real(dp),Intent(in)::gA(:)
Real(dp),Intent(out)::gB(:)
Integer::i1,i2,i_count,kont
Complex(dp) :: Tad1Loop(3)
Real(dp) :: comp(3)
Complex(dp) :: cplAhAhUhh(3,3,3),cplAhUhhhh(3,3,3),cplAhUhhVZ(3,3),cplcChaChaUhhL(2,2,3),            &
& cplcChaChaUhhR(2,2,3),cplChiChiUhhL(5,5,3),cplChiChiUhhR(5,5,3),cplcFdFdUhhL(3,3,3),   &
& cplcFdFdUhhR(3,3,3),cplcFeFeUhhL(3,3,3),cplcFeFeUhhR(3,3,3),cplcFuFuUhhL(3,3,3),       &
& cplcFuFuUhhR(3,3,3),cplcgWmgWmUhh(3),cplcgWpCgWpCUhh(3),cplcgZgZUhh(3),cplUhhhhhh(3,3,3),&
& cplUhhHpmcHpm(3,2,2),cplUhhHpmcVWm(3,2),cplUhhcVWmVWm(3),cplUhhVZVZ(3),cplAhAhUhhUhh(3,3,3,3),&
& cplUhhUhhhhhh(3,3,3,3),cplUhhUhhHpmcHpm(3,3,2,2),cplUhhUhhcVWmVWm(3,3),cplUhhUhhVZVZ(3,3)

Real(dp) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             &
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp) :: vd,vu,vS

Iname=Iname+1
NameOfUnit(Iname)='BoundarySUSY'
Call GToParameters218(gA,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------



 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

If (.Not.FirstRun) Then
vd = vdSUSY
vu = vuSUSY
vS = vSSUSY


 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

End if


 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------

Call ParametersToG218(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gB)

Iname=Iname-1
End Subroutine BoundarySUSY

Subroutine BoundaryHS(gA,gB)
Implicit None
Real(dp),Intent(in)::gA(:)
Real(dp),Intent(out)::gB(:)
Integer::i1,i2
Real(dp) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             &
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp) :: Yd_ckm(3,3), Yu_ckm(3,3), Tu_ckm(3,3), Td_ckm(3,3), mq2_ckm(3,3), mu2_ckm(3,3), md2_ckm(3,3)
Complex(dp) :: Yd_out(3,3), Yu_out(3,3), Tu_out(3,3), Td_out(3,3), mq2_out(3,3), mu2_out(3,3), md2_out(3,3)
Iname=Iname+1
NameOfUnit(Iname)='BoundaryHS'
Call GToParameters218(gA,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)

If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
If (InputValueforTe) Then
Te = TeIN
Else
Te = Azero*Ye
End If
If (InputValueforTd) Then
Td = TdIN
Else
Td = Azero*Yd
End If
If (InputValueforTu) Then
Tu = TuIN
Else
Tu = Azero*Yu
End If
If (InputValueformq2) Then
mq2 = mq2IN
Else
mq2 = 0._dp
Do i1=1,3
mq2(i1,i1) = m0**2
End Do
End If
If (InputValueforml2) Then
ml2 = ml2IN
Else
ml2 = 0._dp
Do i1=1,3
ml2(i1,i1) = m0**2
End Do
End If
If (InputValueformd2) Then
md2 = md2IN
Else
md2 = 0._dp
Do i1=1,3
md2(i1,i1) = m0**2
End Do
End If
If (InputValueformu2) Then
mu2 = mu2IN
Else
mu2 = 0._dp
Do i1=1,3
mu2(i1,i1) = m0**2
End Do
End If
If (InputValueforme2) Then
me2 = me2IN
Else
me2 = 0._dp
Do i1=1,3
me2(i1,i1) = m0**2
End Do
End If
If (InputValueforTk) Then
Tk = TkIN
Else
Tk = AKappaInput*kap
End If
If (InputValueforTlam) Then
Tlam = TlamIN
Else
Tlam = ALambdaInput*lam
End If
If (InputValueforM1) Then
M1 = M1IN
Else
M1 = m12
End If
If (InputValueforM2) Then
M2 = M2IN
Else
M2 = m12
End If
If (InputValueforM3) Then
M3 = M3IN
Else
M3 = m12
End If
Case (2)
If (InputValueforTe) Then
Te = TeIN
Else
Te = Azero*Ye
End If
If (InputValueforTd) Then
Td = TdIN
Else
Td = Azero*Yd
End If
If (InputValueforTu) Then
Tu = TuIN
Else
Tu = Azero*Yu
End If
If (InputValueformq2) Then
mq2 = mq2IN
Else
mq2 = 0._dp
Do i1=1,3
mq2(i1,i1) = m0**2
End Do
End If
If (InputValueforml2) Then
ml2 = ml2IN
Else
ml2 = 0._dp
Do i1=1,3
ml2(i1,i1) = m0**2
End Do
End If
If (InputValueformd2) Then
md2 = md2IN
Else
md2 = 0._dp
Do i1=1,3
md2(i1,i1) = m0**2
End Do
End If
If (InputValueformu2) Then
mu2 = mu2IN
Else
mu2 = 0._dp
Do i1=1,3
mu2(i1,i1) = m0**2
End Do
End If
If (InputValueforme2) Then
me2 = me2IN
Else
me2 = 0._dp
Do i1=1,3
me2(i1,i1) = m0**2
End Do
End If
If (InputValueforkap) Then
kap = kapIN
Else
kap = KappaInput
End If
If (InputValueforlam) Then
lam = lamIN
Else
lam = LambdaInput
End If
If (InputValueforTk) Then
Tk = TkIN
Else
Tk = AKappaInput*KappaInput
End If
If (InputValueforTlam) Then
Tlam = TlamIN
Else
Tlam = ALambdaInput*LambdaInput
End If
If (InputValueforM1) Then
M1 = M1IN
Else
M1 = m12
End If
If (InputValueforM2) Then
M2 = M2IN
Else
M2 = m12
End If
If (InputValueforM3) Then
M3 = M3IN
Else
M3 = m12
End If
Case (3)
If (InputValueforTe) Then
Te = TeIN
Else
Te = Azero*Ye
End If
If (InputValueforTd) Then
Td = TdIN
Else
Td = Azero*Yd
End If
If (InputValueforTu) Then
Tu = TuIN
Else
Tu = Azero*Yu
End If
If (InputValueformq2) Then
mq2 = mq2IN
Else
mq2 = 0._dp
Do i1=1,3
mq2(i1,i1) = m0**2
End Do
End If
If (InputValueforml2) Then
ml2 = ml2IN
Else
ml2 = 0._dp
Do i1=1,3
ml2(i1,i1) = m0**2
End Do
End If
If (InputValueformd2) Then
md2 = md2IN
Else
md2 = 0._dp
Do i1=1,3
md2(i1,i1) = m0**2
End Do
End If
If (InputValueformu2) Then
mu2 = mu2IN
Else
mu2 = 0._dp
Do i1=1,3
mu2(i1,i1) = m0**2
End Do
End If
If (InputValueforme2) Then
me2 = me2IN
Else
me2 = 0._dp
Do i1=1,3
me2(i1,i1) = m0**2
End Do
End If
If (InputValueforM1) Then
M1 = M1IN
Else
M1 = m12
End If
If (InputValueforM2) Then
M2 = M2IN
Else
M2 = m12
End If
If (InputValueforM3) Then
M3 = M3IN
Else
M3 = m12
End If
End Select
else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 g1GUT =g1
g2GUT =g2
g3GUT =g3
YdGUT =Yd
YeGUT =Ye
lamGUT =lam
kapGUT =kap
YuGUT =Yu
TdGUT =Td
TeGUT =Te
TlamGUT =Tlam
TkGUT =Tk
TuGUT =Tu
mq2GUT =mq2
ml2GUT =ml2
mHd2GUT =mHd2
mHu2GUT =mHu2
md2GUT =md2
mu2GUT =mu2
me2GUT =me2
ms2GUT =ms2
M1GUT =M1
M2GUT =M2
M3GUT =M3
If (Maxval(Abs(Yd)).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale Yd"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Maxval(Abs(Ye)).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale Ye"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Abs(lam).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale lam"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Abs(kap).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale kap"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Maxval(Abs(Yu)).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale Yu"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Abs(g1).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale appearing for: g1"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Abs(g2).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale appearing for: g2"
If (ErrorLevel.gt.0) Call TerminateProgram
End if
If (Abs(g3).gt.3._dp) Then
Write(*,*) "Non pertubative coupling at GUT scale appearing for: g3"
If (ErrorLevel.gt.0) Call TerminateProgram
End if



! Translate input form SCKM to electroweak basis
If (SwitchToSCKM) Then
Yd_ckm = Yd(1:3,1:3)
Yu_ckm = Yu(1:3,1:3)
Td_ckm = Td(1:3,1:3)
Tu_ckm = Tu(1:3,1:3)
mq2_ckm = mq2(1:3,1:3)
md2_ckm = md2(1:3,1:3)
mu2_ckm = mu2(1:3,1:3)
Call Switch_from_superCKM(Yd_ckm, Yu_ckm, Td_ckm, Tu_ckm, md2_ckm, mq2_ckm, mu2_ckm&
&, Td_out, Tu_out, md2_out, mq2_out, mu2_out,.True.)
If (InputValueforTd) Td = Td_out
If (InputValueforTu) Tu = Tu_out
If (InputValueformq2) mq2 = mq2_out
If (InputValueformd2) md2 = md2_out
If (InputValueformu2) mu2 = mu2_out
End If



Call ParametersToG218(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gB)

Iname=Iname-1
Contains

Subroutine Switch_from_superCKM(Y_d, Y_u, Ad_in, Au_in, MD_in, MQ_in, MU_in &
                      &, Ad_out, Au_out, MD_out, MQ_out, MU_out, tr        &
                      &, RSd_in, RSu_in, RSd_out, RSu_out, CKM_out, Yd, Yu )
 !---------------------------------------------------------------------------
 ! shifts the parameter from the  super CKM basis to the electroweak basis
 ! written by werner Porod, 12.03.08
 !---------------------------------------------------------------------------
 Implicit None
  Complex(dp), Intent(in), Dimension(3,3) :: Y_d, Y_u, Au_in, Ad_in, MD_in &
        & , MQ_in, MU_in
  Complex(dp), Optional, Intent(in), Dimension(6,6) :: RSu_in, RSd_in
  Logical, Intent(in) :: tr  ! if true, then the matrices are transposed
                             ! compared to low energy definition
  Complex(dp), Intent(out), Dimension(3,3) :: Au_out, Ad_out, MD_out, MQ_out &
        & , MU_out
  Complex(dp), Optional, Intent(out), Dimension(6,6) :: RSu_out, RSd_out
  Complex(dp), Optional, Intent(out) :: CKM_out(3,3)
  Complex(dp), Optional, Intent(out) :: Yd(3), Yu(3)

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
   If (Present(Yu)) Yu = sqrt2 * mf
   Call FermionMass(Transpose(Y_d), 1._dp, mf, uD_L, uD_R, ierr)
   If (Present(Yd)) Yd = sqrt2 * mf
  Else
   Call FermionMass(Y_u, 1._dp, mf, uU_L, uU_R, ierr)
   If (Present(Yu)) Yu = sqrt2 * mf
   Call FermionMass(Y_d, 1._dp, mf, uD_L, uD_R, ierr)
   If (Present(Yd)) Yd = sqrt2 * mf
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

  If (Present(CKM_out)) CKM_out = CKM_Q
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

   If (Present(RSu_in).And.Present(RSu_out)) Then
    rot = 0._dp
    rot(1:3,1:3) = Conjg(uU_L)
    rot(4:6,4:6) = uU_R
    RSu_out = Matmul(RSu_in, rot)
   End If
   If (Present(RSd_in).And.Present(RSd_out)) Then
    rot = 0._dp
    rot(1:3,1:3) = Conjg(uD_L)
    rot(4:6,4:6) = uD_R
    RSd_out = Matmul(RSd_in, rot)
   End If

 End Subroutine Switch_from_superCKM
End Subroutine BoundaryHS

Subroutine BoundaryEW(i_run,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,              &
& MFe2,MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,            &
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             &
& ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,            &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,delta0,gMZ,kont)

Implicit None
Real(dp),Intent(out)::gMZ(:)
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             &
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(inout) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               &
& MFe2(3),MFu(3),MFu2(3),Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(1),MSd2(1),MSe(1),          &
& MSe2(1),MSu(1),MSu2(1),MSv(1),MSv2(1),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(3,3),ZH(3,3),        &
& ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(inout) :: pG,UM(2,2),UP(2,2),ZD(1,1),ZDL(3,3),ZDR(3,3),ZE(1,1),ZEL(3,3),ZER(3,3),               &
& ZN(5,5),ZU(1,1),ZUL(3,3),ZUR(3,3),ZV(1,1),ZW(2,2)

Real(dp),Intent(inout) :: vd,vu,vS

Complex(dp) :: cplAhhhVZ(3,3),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplChiChiVZL(5,5),               &
& cplChiChiVZR(5,5),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3), &
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgWmgWmVZ,      &
& cplcgWpCgWpCVZ,cplhhVZVZ(3),cplHpmcHpmVZ(2,2),cplHpmcVWmVZ(2),cplcVWmVWmVZ,            &
& cplAhAhVZVZ(3,3),cplhhhhVZVZ(3,3),cplHpmcHpmVZVZ(2,2),cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2, &
& cplcVWmVWmVZVZ3,cplAhHpmcVWm(3,2),cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),             &
& cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),           &
& cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm(3,2),           &
& cplhhcVWmVWm(3),cplHpmcVWmVP(2),cplcVWmVPVWm,cplAhAhcVWmVWm(3,3),cplhhhhcVWmVWm(3,3),  &
& cplHpmcHpmcVWmVWm(2,2),cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmcVWmVWmVWm1,&
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3

Complex(dp) :: cplcUFeFeAhL(3,3,3),cplcUFeFeAhR(3,3,3),cplcUFeFehhL(3,3,3),cplcUFeFehhR(3,3,3),      &
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               &
& cplcUFeFvHpmL(3,3,2),cplcUFeFvHpmR(3,3,2),cplcUFeFvVWmL(3,3),cplcUFeFvVWmR(3,3),       &
& cplcUFdFdAhL(3,3,3),cplcUFdFdAhR(3,3,3),cplcUFdFdhhL(3,3,3),cplcUFdFdhhR(3,3,3),       &
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               &
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFuHpmL(3,3,2),cplcUFdFuHpmR(3,3,2),         &
& cplcUFdFuVWmL(3,3),cplcUFdFuVWmR(3,3),cplcUFuFuAhL(3,3,3),cplcUFuFuAhR(3,3,3),         &
& cplcUFuFdcHpmL(3,3,2),cplcUFuFdcHpmR(3,3,2),cplcUFuFdcVWmL(3,3),cplcUFuFdcVWmR(3,3),   &
& cplcUFuFuhhL(3,3,3),cplcUFuFuhhR(3,3,3),cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),           &
& cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3)

Integer, Intent(in) :: i_run
Real(dp), Intent(in) :: delta0
Integer, Intent(inout) :: kont
Integer :: i1,i2,i3,i4
Complex(dp) ::uU_L(3,3),uU_R(3,3),uD_L(3,3),uD_R(3,3), NoMatrix(3,3) &
&,uL_L(3,3),uL_R(3,3)
Real(dp)::mW2_run,mZ2_run,test, D_mat(3,3)
Real(dp)::alphaMZ,alpha3,gSU2,rho,delta_rho,delta_rho0,sinW2_Q,vev2&
&,vevs_Q(2),mZ2_mZ,CosW2SinW2,gauge(3),delta,sinW2_old,delta_r&
&,p2,gSU3,tanb,xt2,fac(2),SigQCD,delta_rw,sinW2,cosW2,cosW
Real(dp),Dimension(3)::mf_d_Q,mf_l_Q,mf_u_Q
Real(dp) :: g1SM, g2SM, g3SM, vSM
Complex(dp) :: dmZ2,dmW2,dmW2_0,yuk_tau,yuk_t,yuk_b
Complex(dp) :: SigS_u(3,3),sigR_u(3,3),SigL_u(3,3)
Complex(dp) :: SigS_d(3,3),SigR_d(3,3),SigL_d(3,3)
Complex(dp) :: SigS_l(3,3),sigR_l(3,3),SigL_l(3,3)
Complex(dp) :: YuSM(3,3),YdSM(3,3),YeSM(3,3), adCKM(3,3),Y_l_old(3,3),Y_d_old(3,3),Y_u_old(3,3)
Complex(dp) :: uU_L_T(3,3),uU_R_T(3,3)&
&,uD_L_T(3,3),uD_R_T(3,3),uL_L_T(3,3),uL_R_T(3,3)
Logical::converge
Integer :: i_loop, i_loop_max
Real(dp),Parameter::&
& as2loop=1._dp/24._dp+2011._dp*oo32Pi2/12._dp&
&+Log2/12._dp-oo8Pi2*Zeta3&
&,log2loop_a=123._dp*oo32Pi2,log2loop_b=33._dp*oo32Pi2
Real(dp)::Q2,logQ


Complex(dp) ::MassFu(3,3),MassFd(3,3),MassFe(3,3)
Iname=Iname+1
NameOfUnit(Iname)='BoundaryEW'
tanb = tanbetaMZ
sinW2 = 1 - mW**2/mZ**2
test = SetRenormalizationScale(mZ2)
!-----------------
!sin(theta_W)^2
!-----------------
vSM = vSM_save
If (i_run.Eq.1) Then
   sinW2_Q=sinW2
   sinW2_old=sinW2_Q
   Y_l=0._dp
   Do i1=1,3
       y_l(i1,i1)=sqrt2*mf_l_mZ(i1)/vevSM(1)
   End Do
   mf_l2=mf_l_mZ**2
   mf_d2=mf_d_mZ**2
   mf_u2=mf_u_mZ**2
Else
   sinW2_Q=sinW2_Q_mZ
   sinW2_old=sinW2_Q
   Y_l=Yl_mZ
   Call FermionMass(Yd_mZ,vSM,mf_d2,uD_L_T,uD_R_T,kont)
   Call FermionMass(Yl_mZ,vSM,mf_l2,uL_L_T,uL_R_T,kont)
   Call FermionMass(Yu_mZ,vSM,mf_u2,uU_L_T,uU_R_T,kont)
   mf_l2=mf_l2**2
   mf_d2=mf_d2**2
   mf_u2=mf_u2**2
End If
MFe2(1:3) = mf_l**2
MFd2(1:3) = mf_d**2
MFu2(1:3) = mf_u**2
MFe = sqrt(MFe2)
MFd = sqrt(MFd2)
MFu = sqrt(MFu2)
alphaMZ = AlphaEwDR(mZ,MVWm,MHpm,MCha,MFe,MFd,MFu)

MFe2(1:3) = mf_l2
MFd2(1:3) = mf_d2
MFu2(1:3) = mf_u2
MFe = sqrt(MFe2)
MFd = sqrt(MFd2)
MFu = sqrt(MFu2)
alpha3 = AlphaSDR(mZ,Mhh,MAh,MHpm,MChi,MCha,MFe,MFd,MFu)
gSU3 = Sqrt(4._dp*pi*alpha3)
g3SM = Sqrt(4._dp*pi*alpha3)
!--------------------
!for 2-loop parts
!--------------------
xt2=3._dp*(G_F*mf_u2(3)*oo8pi2*oosqrt2)**2&
    &*Abs(ZH(1,2))**2*rho_2(Sqrt(Mhh2(1))/mf_U(3))&
    &*((1._dp+tanb**2)/tanb**2)
fac(1)=alphaMZ*alphaS_mZ*oo4pi&
      &*(2.145_dp*mf_u2(3)/mZ2+0.575*Log(mf_u(3)/mZ)-0.224_dp&
      &-0.144_dp*mZ2/mf_u2(3))/Pi
fac(2)=alphamZ*alphaS_mZ*oo4pi&
      &*(-2.145_dp*mf_u2(3)/mW2+1.262*Log(mf_u(3)/mZ)-2.24_dp&
      &-0.85_dp*mZ2/mf_u2(3))/Pi
Do i1=1,100
gSU2 = Sqrt( 4._dp*pi*alphamZ/sinW2_Q)
g1SM =gSU2*Sqrt(sinW2_Q/(1._dp-sinW2_Q))
g2SM =gSU2
YeSM=Yl_MZ
YdSM=Yd_MZ
YuSM=Yu_MZ
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

TW= Asin(Sqrt(sinw2_Q))


 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------

MVZ2 = mZ2
MVZ= Sqrt(MVZ2)
MVWm2 = mW2
MVWm= Sqrt(MVWm2)
MAh(1)=MVZ
MAh2(1)=MVZ2
MHpm(1)=MVWm
MHpm2(1)=MVWm2
Call CouplingsForVectorBosons(g1,g2,ZH,ZA,TW,UM,UP,ZN,vd,vu,ZP,ZDL,ZUL,               &
& ZEL,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,       &
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,               &
& cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,           &
& cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,   &
& cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,              &
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,  &
& cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,cplcVWmVPVWm,cplAhAhcVWmVWm,     &
& cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,      &
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)

Call Pi1LoopVZ(mZ2,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,              &
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,    &
& cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,             &
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           &
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,              &
& cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmZ2)

mZ2_mZ = Real(dmZ2 + mZ2,dp)
If (mZ2_mZ.Lt.0._dp) Then
    Iname=Iname-1
    kont=-402
    Call AddError(402)
    Write(*,*) " MZ  getting negative at EW scale"
    Call TerminateProgram
End If

mZ2_run=mZ2_mZ
mW2_run=mZ2_mZ*(1._dp-sinW2_Q) +0
MVZ2 = mZ2_run
MVZ= Sqrt(MVZ2)
MVWm2 = mW2_run
MVWm= Sqrt(MVWm2)
MAh(1)=MVZ
MAh2(1)=MVZ2
MHpm(1)=MVWm
MHpm2(1)=MVWm2
CosW2SinW2=(1._dp-sinW2_Q)*sinW2_Q
vev2=mZ2_mZ*CosW2SinW2/(pi*alphamZ) -0
vSM=Sqrt(vev2)
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

Call CouplingsForVectorBosons(g1,g2,ZH,ZA,TW,UM,UP,ZN,vd,vu,ZP,ZDL,ZUL,               &
& ZEL,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,       &
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,               &
& cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,           &
& cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,   &
& cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,              &
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,  &
& cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,cplcVWmVPVWm,cplAhAhcVWmVWm,     &
& cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,      &
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)

Call Pi1LoopVZ(mZ2,Mhh,Mhh2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,              &
& MFe2,MFu,MFu2,MVZ,MVZ2,MHpm,MHpm2,MVWm,MVWm2,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,    &
& cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,             &
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           &
& cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,              &
& cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmZ2)

mZ2_mZ = Real(dmZ2 + mZ2,dp)
If (mZ2_mZ.Lt.0._dp) Then
    Iname=Iname-1
    kont=-402
    Call AddError(402)
    Write(*,*) " MZ  getting negative at EW scale"
    Call TerminateProgram
End If

mZ2_run=mZ2_mZ
mW2_run=mZ2_mZ*(1._dp-sinW2_Q) +0
MVZ2 = mZ2_run
MVZ= Sqrt(MVZ2)
MVWm2 = mW2_run
MVWm= Sqrt(MVWm2)
MAh(1)=MVZ
MAh2(1)=MVZ2
MHpm(1)=MVWm
MHpm2(1)=MVWm2
CosW2SinW2=(1._dp-sinW2_Q)*sinW2_Q
vev2=mZ2_mZ *CosW2SinW2/(pi*alphamZ) -0
vSM=sqrt(vev2)
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

Call CouplingsForVectorBosons(g1,g2,ZH,ZA,TW,UM,UP,ZN,vd,vu,ZP,ZDL,ZUL,               &
& ZEL,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,       &
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,               &
& cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,           &
& cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,   &
& cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,              &
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,  &
& cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,cplcVWmVPVWm,cplAhAhcVWmVWm,     &
& cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,      &
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)

Call Pi1LoopVWm(mW2,MHpm,MHpm2,MAh,MAh2,MChi,MChi2,MCha,MCha2,MFu,MFu2,               &
& MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVWm,MVWm2,MVZ,MVZ2,cplAhHpmcVWm,cplChiChacVWmL,            &
& cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm, &
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,     &
& cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,&
& cplcVWmVPVPVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3, &
& cplcVWmcVWmVWmVWm1,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmW2)

Call Pi1LoopVWm(0._dp,MHpm,MHpm2,MAh,MAh2,MChi,MChi2,MCha,MCha2,MFu,MFu2,             &
& MFd,MFd2,MFe,MFe2,Mhh,Mhh2,MVWm,MVWm2,MVZ,MVZ2,cplAhHpmcVWm,cplChiChacVWmL,            &
& cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm, &
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,     &
& cplHpmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,&
& cplcVWmVPVPVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3, &
& cplcVWmcVWmVWmVWm1,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmW2_0)

rho=(1._dp+Real(dmZ2,dp)/mZ2)/(1._dp+Real(dmW2,dp)/mW2)
delta_rho=1._dp-1._dp/rho
delta_rho0=0
rho=1._dp/(1._dp-delta_rho-delta_rho0)
CosW2SinW2=(1._dp-sinW2_Q)*sinW2_Q
If (IncludeDeltaVB) Then
Call DeltaVB(sinW2,sinW2_Q,rho,MAh,MFe,Mhh,MHpm,MVWm,g2,vd,vu,Ye,ZA,ZEL,              &
& ZER,ZH,ZP,delta)

Else
delta = 0._dp
End if
delta_r=rho*Real(dmW2_0,dp)/mW2-Real(dmZ2,dp)/mZ2+delta
rho=1._dp/(1._dp-delta_rho-delta_rho0-fac(2)/sinW2_Q-xt2)
delta_r=rho*Real(dmW2_0,dp)/mW2-Real(dmZ2,dp)/mZ2+delta&
        &+fac(1)/CosW2SinW2-xt2*(1-delta_r)*rho
CosW2SinW2=pi*alphamZ/(sqrt2*mZ2*G_F*(1-delta_r))
sinW2_Q=0.5_dp-Sqrt(0.25_dp-CosW2SinW2)

If (sinW2_Q.Lt.0._dp) Then
    kont=-403
    Call AddError(403)
    Iname=Iname-1
    Write(*,*) " sinW2 getting negtive at EW scale "
    Call TerminateProgram
End If

If (Abs(sinW2_Q-sinW2_old).Lt.0.1_dp*delta0) Exit

sinW2_old=sinW2_Q
delta_rw=delta_rho*(1._dp-delta_r)+delta_r
If ((0.25_dp-alphamz*pi/(sqrt2*G_F*mz2*rho*(1._dp-delta_rw))).Lt.0._dp) Then
    kont=-404
    Call AddError(404)
    Iname=Iname-1
     Return
End If

mW2=mZ2*rho*(0.5_dp&
    &+Sqrt(0.25_dp-alphamz*pi/(sqrt2*G_F*mz2*rho*(1._dp-delta_rw))))
MAh(1)=MVZ
MAh2(1)=MVZ2
MHpm(1)=MVWm
MHpm2(1)=MVWm2
cosW2=mW2/mZ2
cosW=Sqrt(cosW2)
sinW2=1._dp-cosW2
End Do

MAh(1)=MVZ
MAh2(1)=MVZ2
MHpm(1)=MVWm
MHpm2(1)=MVWm2
delta_rw=delta_rho*(1._dp-delta_r)+delta_r
mW2=mZ2*rho*(0.5_dp&
   &+Sqrt(0.25_dp-alphamz*pi/(sqrt2*G_F*mz2*rho*(1._dp-delta_rw))))
mW=Sqrt(mW2)
cosW2=mW2/mZ2
cosW=Sqrt(cosW2)
sinW2=1._dp-cosW2
g1SM=Sqrt(4._dp*pi*alphamZ/(1._dp-sinW2_Q))
g2SM=Sqrt(4._dp*pi*alphamZ/sinW2_Q)
g3SM=Sqrt(4._dp*pi*alpha3)
vev2=mZ2_mZ*CosW2SinW2/(pi*alphamZ) -0
vSM=sqrt(vev2)
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.True.)



! -------------------------
!  Calculate Yukawas
! -------------------------
uU_L=id3C
uU_R=id3C
uD_L=id3C
uD_R=id3C
uL_L=id3C
uL_R=id3C
If (GenerationMixing) Then
    Call Adjungate(CKM,adCKM)
 If (YukawaScheme.Eq.1) Then
    uU_L(1:3,1:3)=CKM
 Else
    uD_L(1:3,1:3)=adCKM
 End If
End If
If (i_run.Eq.1) Then
If (rMS.gt.0.5_dp) Then ! shift to DR if necessary
   mf_l_Q_SM=&
            & mf_l_mZ*(1._dp-oo8pi2*3._dp*(g1SM**2-g2SM**2)/16._dp)
   mf_d_Q_SM=mf_d_mZ*(1._dp-alpha3/(3._dp*pi)&
           &-23._dp*alpha3**2/(72._dp*Pi2)&
           &+oo8pi2*3._dp*g2SM**2/16._dp&
           &-oo8pi2*13._dp*g1SM**2/144._dp)
   mf_u_Q_SM(1:2)=mf_u_mZ(1:2)*(1._dp-alpha3/(3._dp*pi)&
               &-23._dp*alpha3**2/(72._dp*Pi2)&
               &+oo8pi2*3._dp*g2SM**2/16._dp&
               &-oo8pi2*7._dp*g1SM**2/144._dp)
   mf_u_Q_SM(3)=mf_u(3)! QCD+QED shift will be added later
Else
   mf_l_Q_SM=mf_l_MZ
   mf_d_Q_SM=mf_d_MZ
   mf_u_Q_SM=mf_u_MZ
End if
mf_l_Q=mf_l_Q_SM
mf_d_Q=mf_d_Q_SM
mf_u_Q=mf_u_Q_SM
YdSM=0._dp
YuSM=0._dp
YeSM=0._dp
Do i1=1,3
    YuSM(i1,i1)=sqrt2*mf_u_Q_SM(i1)/vSM
    YeSM(i1,i1)=sqrt2*mf_l_Q_SM(i1)/vSM
    YdSM(i1,i1)=sqrt2*mf_d_Q_SM(i1)/vSM
End Do
If (GenerationMixing) Then
  If (YukawaScheme.Eq.1) Then
    YuSM=Matmul(Transpose(uU_L(1:3,1:3)),YuSM)
  Else
    YdSM=Matmul(Transpose(uD_L(1:3,1:3)),YdSM)
  End If
End If
Else
YeSM=Yl_MZ
YdSM=Yd_MZ
YuSM=Yu_MZ
End If! i_run.eq.1

converge= .False.
Y_l_old=YeSM
Y_d_old=YdSM
Y_u_old=YuSM
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)



! -------------------------
!  Main Loop
! -------------------------
if (FermionMassResummation) then
  i_loop_max=100! this should be sufficient
else
  i_loop_max=1
end if
Do i_loop=1,i_loop_max
p2=0._dp! for off-diagonal elements


 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------



! Full one-loop corrections
Call CouplingsForSMfermions(Ye,ZA,ZEL,ZER,ZH,g1,g2,TW,ZP,Yd,ZDL,ZDR,g3,               &
& Yu,ZUL,ZUR,cplcUFeFeAhL,cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,           &
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvHpmL,cplcUFeFvHpmR,cplcUFeFvVWmL,      &
& cplcUFeFvVWmR,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,        &
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFuHpmL,        &
& cplcUFdFuHpmR,cplcUFdFuVWmL,cplcUFdFuVWmR,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdcHpmL,    &
& cplcUFuFdcHpmR,cplcUFuFdcVWmL,cplcUFuFdcVWmR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,   &
& cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR)

Call Sigma1LoopFeMZ(p2,MFe,MFe2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MVWm,           &
& MVWm2,cplcUFeFeAhL,cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,   &
& cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvHpmL,cplcUFeFvHpmR,cplcUFeFvVWmL,cplcUFeFvVWmR,     &
& sigR_l,sigL_l,sigS_l)

Call Sigma1LoopFdMZ(p2,MFd,MFd2,MAh,MAh2,Mhh,Mhh2,MVZ,MVZ2,MHpm,MHpm2,MFu,            &
& MFu2,MVWm,MVWm2,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,      &
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFuHpmL,        &
& cplcUFdFuHpmR,cplcUFdFuVWmL,cplcUFdFuVWmR,sigR_d,sigL_d,sigS_d)

Call Sigma1LoopFuMZ(p2,MFu,MFu2,MAh,MAh2,MHpm,MHpm2,MFd,MFd2,MVWm,MVWm2,              &
& Mhh,Mhh2,MVZ,MVZ2,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdcHpmL,cplcUFuFdcHpmR,             &
& cplcUFuFdcVWmL,cplcUFuFdcVWmR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,     &
& cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,sigR_u,sigL_u,sigS_u)



! SM two-loop corrections
! Two-loop Non-SUSY from hep-ph/9803493
Q2=GetRenormalizationScale()
logQ=Log(Q2/MFu(3)**2)
SigQCD=-4._dp/3._dp*gSU3**2*MFu(3)*(5._dp-rMS+3._dp*LogQ&
&+(1._dp-rMS)*(as2loop+log2loop_a*logQ+log2loop_b*logQ**2)*gSU3**2&
&-oo16pi2*rMS*(174.452+112.667*LogQ+22._dp*LogQ**2)*gSU3**2)&
&-MFu(3)*(-2._dp/3._dp*gSU2)**2*sinW2_Q*(5._dp-rMS+3._dp*LogQ)
SigQCD=oo16pi2*SigQCD

mf_u_Q_SM(3)=mf_u(3)+SigQCD



! Construct tree-level masses
! Needed for models with additional states mixing with SM particles
Call CalculateMFe(Ye,vd,ZEL,ZER,MFe,kont)

MassFe=0._dp
Do i1 = 1,3
 MassFe(i1,i1)=MFe(i1)
End do
MassFe = MatMul(Transpose(ZEL),MatMul(MassFe,Conjg(ZER)))
MFe(1:3) =mf_l_Q_SM
Call CalculateMFu(Yu,vu,ZUL,ZUR,MFu,kont)

MassFu=0._dp
Do i1 = 1,3
 MassFu(i1,i1)=MFu(i1)
End do
MassFu = MatMul(Transpose(ZUL),MatMul(MassFu,Conjg(ZUR)))
MFu(1:3) =mf_u_Q_SM
Call CalculateMFd(Yd,vd,ZDL,ZDR,MFd,kont)

MassFd=0._dp
Do i1 = 1,3
 MassFd(i1,i1)=MFd(i1)
End do
MassFd = MatMul(Transpose(ZDL),MatMul(MassFd,Conjg(ZDR)))
MFd(1:3) =mf_d_Q_SM


! Obtain Yukawas
Call Yukawas3(MFu,vSM,uU_L,uU_R,SigS_u,SigL_u,SigR_u&
      &,massFu,YuSM, FermionMassResummation,kont)
If (kont.Ne.0) Then
    Iname=Iname-1
    Write(*,*) " Fit of Yukawa couplings at EW scale failed"
    Call TerminateProgram
End If
Call Yukawas3(MFd,vSM,uD_L,uD_R,SigS_d,SigL_d,SigR_d&
      &,massFd,YdSM,FermionMassResummation,kont)
If (kont.Ne.0) Then
    Iname=Iname-1
    Write(*,*) " Fit of Yukawa couplings at EW scale failed"
    Call TerminateProgram
End If
Call Yukawas3(MFe,vSM,uL_L,uL_R,SigS_l,SigL_l,SigR_l&
     &,massFe,YeSM,.False.,kont)
If (kont.Ne.0) Then
    Iname=Iname-1
    Write(*,*) " Fit of Yukawa couplings at EW scale failed"
    Call TerminateProgram
End If


! Transpose Yukawas to fit conventions
YuSM = Transpose(YuSM)
YdSM= Transpose(YdSM)
YeSM= Transpose(YeSM)
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)



! Re-calculate quarks with new Yukawas
Call CalculateMFe(Ye,vd,ZEL,ZER,MFe,kont)

MFe2 = MFe**2
Call CalculateMFu(Yu,vu,ZUL,ZUR,MFu,kont)

MFu2 = MFu**2
Call CalculateMFd(Yd,vd,ZDL,ZDR,MFd,kont)

MFd2 = MFd**2
mf_l_Q  = MFe(1:3)
mf_d_Q  = MFd(1:3)
mf_u_Q  = MFu(1:3)


! Re-calculate other masses which depend on Yukawas


! Check convergence
converge= .True.
D_mat=Abs(Abs(YeSM)-Abs(Y_l_old))
Where (Abs(YeSM).Ne.0._dp) D_mat=D_mat/Abs(YeSM)
Do i1=1,3
 If (D_mat(i1,i1).Gt.0.1_dp*delta0) converge= .False.
  Do i2=i1+1,3
   If (D_mat(i1,i2).Gt.delta0) converge= .False.
   If (D_mat(i2,i1).Gt.delta0) converge= .False.
 End Do
End Do
D_mat=Abs(Abs(YdSM)-Abs(Y_d_old))
Where (Abs(YdSM).Ne.0._dp) D_mat=D_mat/Abs(YdSM)
Do i1=1,3
 If (D_mat(i1,i1).Gt.0.1_dp*delta0) converge= .False.
   Do i2=i1+1,3
    If (D_mat(i1,i2).Gt.10._dp*delta0) converge= .False.
    If (D_mat(i2,i1).Gt.10._dp*delta0) converge= .False.
   End Do
End Do
D_mat=Abs(Abs(YuSM)-Abs(Y_u_old))
Where (Abs(YuSM).Ne.0._dp) D_mat=D_mat/Abs(YuSM)
Do i1=1,3
 If (D_mat(i1,i1).Gt.0.1_dp*delta0) converge= .False.
  Do i2=i1+1,3
   If (D_mat(i1,i2).Gt.10._dp*delta0) converge= .False.
   If (D_mat(i2,i1).Gt.10._dp*delta0) converge= .False.
  End Do
End Do
If (converge) Exit
  Y_l_old=YeSM
  Y_u_old=YuSM
  Y_d_old=YdSM
!--------------------------------------------------
!Either we have run into a numerical problem or
!perturbation theory breaks down
!--------------------------------------------------
If ((Minval(Abs(mf_l_Q/mf_l)).Lt.0.1_dp)&
&.Or.(Maxval(Abs(mf_l_Q/mf_l)).Gt.10._dp)) Then
Iname=Iname-1
kont=-405
Call AddError(405)
    Write(*,*) " Loop corrections to Yukawa couplings at EW scale too large!"
    Call TerminateProgram
Else If ((Minval(Abs(mf_d_Q/mf_d)).Lt.0.1_dp)&
&.Or.(Minval(Abs(mf_d_Q/mf_d)).Gt.10._dp)) Then
Iname=Iname-1
kont=-406
Call AddError(406)
    Write(*,*) " Loop corrections to Yukawa couplings at EW scale too large!"
    Call TerminateProgram
Else If ((Minval(Abs(mf_u_Q/mf_u)).Lt.0.1_dp)&
&.Or.(Minval(Abs(mf_u_Q/mf_u)).Gt.10._dp)) Then
Iname=Iname-1
kont=-407
Call AddError(407)
    Write(*,*) " Loop corrections to Yukawa couplings at EW scale too large!"
    Call TerminateProgram
End If
End Do! i_loop
If ((.Not.converge).and.FermionMassResummation) Then
Write (ErrCan,*)'Problem in subroutine BoundaryEW!!'
Write (ErrCan,*) "After-1 + (i_loop)iterations no convergence of Yukawas"
End If
Yl_MZ=YeSM
Yd_MZ=YdSM
Yu_MZ=YuSM
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

sinW2_Q_mZ=sinW2_Q
vSM_save=vSM
gauge_mZ=gauge


 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))



 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------

Call ParametersToG218(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gMZ)

test=SetRenormalizationScale(test)
Iname=Iname-1

Contains

Real(dp) Function rho_2(r)
Implicit None
Real(dp),Intent(in)::r
Real(dp)::r2,r3
r2=r*r
r3=r2*r
rho_2=19._dp-16.5_dp*r+43._dp*r2/12._dp&
&+7._dp*r3/120._dp&
&-Pi*Sqrt(r)*(4._dp-1.5_dp*r+3._dp*r2/32._dp&
&+r3/256._dp)&
&-Pi2*(2._dp-2._dp*r+0.5_dp*r2)&
&-Log(r)*(3._dp*r-0.5_dp*r2)
End Function rho_2


Subroutine Yukawas3(mf,vev,uL,uR,SigS,SigL,SigR,MassMatrix,Y,ReSum,kont)
Implicit None
Integer,Intent(inout)::kont
Real(dp),Intent(in)::mf(3),vev
Complex(dp),Dimension(3,3),Intent(in)::uL,uR,SigS,SigL,SigR
Logical,Intent(in)::ReSum
Complex(dp),Intent(inout)::MassMatrix(3,3)
Complex(dp),Intent(out)::Y(3,3)
Integer::i1
Complex(dp),Dimension(3,3)::mass,uLa,uRa,f,invf,invMass2,Ytemp
Call Adjungate(uL,uLa)
Call Adjungate(uR,uRa)
mass=ZeroC
Do i1=1,3
mass(i1,i1)=mf(i1)
End Do
mass=Matmul(Transpose(uL),Matmul(mass,uR))
If (ReSum) Then
kont=0
Call chop(MassMatrix)
invMass2=MassMatrix
Call gaussj(kont,invMass2,3,3)
If (kont.Ne.0) Return
f=id3C-Matmul(SigS,invMass2)-Transpose(SigL)-Matmul(MassMatrix,Matmul(SigR,invMass2))
invf=f
Call gaussj(kont,invf,3,3)
If (kont.Ne.0) Return
Ytemp=Matmul(invf,mass)
Else
Ytemp=mass+SigS+Matmul(Transpose(SigL),MassMatrix)+Matmul(MassMatrix,SigR)
End If
Y=sqrt2*Ytemp(1:3,1:3)/vev
Call chop(y)
End Subroutine Yukawas3

End Subroutine BoundaryEW

Subroutine Sugra(delta0,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,             &
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           &
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             &
& ZZ,betaH,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             &
& mu2,me2,ms2,M1,M2,M3,mGut,kont,WriteComment,niter)

Implicit None
Logical,Intent(in) :: WriteComment
Integer,Intent(inout) :: kont
Integer,Intent(in) :: niter
Real(dp) :: delta0,deltaG0, gA(218), gB(218)
Real(dp) :: gC(221),  gD(221)
Real(dp),Intent(out) :: mGUT
Complex(dp) :: Tad1Loop(3)
Real(dp) :: comp(3), tanbQ, vev2
Complex(dp) :: cplAhAhUhh(3,3,3),cplAhUhhhh(3,3,3),cplAhUhhVZ(3,3),cplcChaChaUhhL(2,2,3),            &
& cplcChaChaUhhR(2,2,3),cplChiChiUhhL(5,5,3),cplChiChiUhhR(5,5,3),cplcFdFdUhhL(3,3,3),   &
& cplcFdFdUhhR(3,3,3),cplcFeFeUhhL(3,3,3),cplcFeFeUhhR(3,3,3),cplcFuFuUhhL(3,3,3),       &
& cplcFuFuUhhR(3,3,3),cplcgWmgWmUhh(3),cplcgWpCgWpCUhh(3),cplcgZgZUhh(3),cplUhhhhhh(3,3,3),&
& cplUhhHpmcHpm(3,2,2),cplUhhHpmcVWm(3,2),cplUhhcVWmVWm(3),cplUhhVZVZ(3),cplAhAhUhhUhh(3,3,3,3),&
& cplUhhUhhhhhh(3,3,3,3),cplUhhUhhHpmcHpm(3,3,2,2),cplUhhUhhcVWmVWm(3,3),cplUhhUhhVZVZ(3,3)

Real(dp),Intent(inout) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               &
& MFe2(3),MFu(3),MFu2(3),Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(1),MSd2(1),MSe(1),          &
& MSe2(1),MSu(1),MSu2(1),MSv(1),MSv2(1),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(3,3),ZH(3,3),        &
& ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(inout) :: pG,UM(2,2),UP(2,2),ZD(1,1),ZDL(3,3),ZDR(3,3),ZE(1,1),ZEL(3,3),ZER(3,3),               &
& ZN(5,5),ZU(1,1),ZUL(3,3),ZUR(3,3),ZV(1,1),ZW(2,2)

Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             &
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp) ::mass_new(15),mass_old(15),diff_m(15)
Real(dp) :: tz,dt,q,q2,mudim,mudimNew, vev, sinW2
Logical::FoundResult, SignMassChangedSave
Integer::j,n_tot, i_count, i1, i2
Iname=Iname+1
NameOfUnit(Iname)='Sugra'
kont=0
FoundResult= .False.
n_tot =1
!mass_old(n_tot:n_tot+-1) = MSd
!n_tot = n_tot + 0
!mass_old(n_tot:n_tot+-1) = MSv
!n_tot = n_tot + 0
!mass_old(n_tot:n_tot+-1) = MSu
!n_tot = n_tot + 0
!mass_old(n_tot:n_tot+-1) = MSe
!n_tot = n_tot + 0
mass_old(n_tot:n_tot+2) = Mhh
n_tot = n_tot + 3
mass_old(n_tot:n_tot+2) = MAh
n_tot = n_tot + 3
mass_old(n_tot:n_tot+1) = MHpm
n_tot = n_tot + 2
mass_old(n_tot:n_tot+4) = MChi
n_tot = n_tot + 5
mass_old(n_tot:n_tot+1) = MCha
If (.Not.UseFixedScale) Then
mudim=Max(mZ**2,Abs(MSu(1)*MSu(6)))
Call SetRGEScale(mudim)
UseFixedScale= .False.
End If
Write(*,*) "Calculating mass spectrum"
CalculateOneLoopMassesSave = CalculateOneLoopMasses
CalculateOneLoopMasses = .false.
Do j=1,niter
Write(*,*) "  ", j,".-iteration"
Write(ErrCan,*) "sugra ", j,".-iteration"
Call BoundaryEW(j,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,               &
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,               &
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             &
& ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,             &
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,delta0,gB,kont)

If (kont.Ne.0) Then
Iname=Iname-1
    Write(*,*) " Problem with boundary conditions at EW scale"
    Call TerminateProgram
End If

Call RunRGE(kont,0.1_dp*delta0,gB,gA,mGUT)

Call GToParameters218(gA,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------

If (kont.Ne.0) Then
Iname=Iname-1
    Write(*,*) " RGE running not possible. Errorcode:", kont
    Call TerminateProgram
End If
mudim=GetRenormalizationScale()
Q=Sqrt(mudim)
Q2=mudim
tz=Log(Q/mZ)
dt=-tz/50._dp
vd=1._dp
vu=tanbeta


 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))



 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------

Call ParametersToG221(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gC)

Call odeint(gC,221,tz,0._dp,0.1_dp*delta0,dt,0._dp,rge221,kont)
Call GToParameters221(gC,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------

If(SPA_Convention) Then
  tanbetaMZ = vu/vd
Else
  tanbetaMZ = tanbeta
End If
vd = vdMZ
vu = vuMZ


 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

vSMZ = vS


 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------

Call ParametersToG221(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,gD)

tz=Log(mZ/Q)
dt=-tz/50._dp
Call odeint(gD,221,tz,0._dp,0.1_dp*delta0,dt,0._dp,rge221,kont)
Call GToParameters221(gD,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------



If(SPA_Convention) Then
  tanbQ = tanbeta
Else
  tanbQ = vu/vd
End If
vev2=4._dp*Real(mZ2,dp)/(g1**2+g2**2) -0._dp
vd=Sqrt(vev2/(1._dp+tanbQ**2))
vu=tanbQ*vd
vdSUSY = vd
vuSUSY = vu
vSSUSY = vS


 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

Call OneLoopMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,              &
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,               &
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             &
& ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,             &
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont)

 FirstRun = .False.
If (kont.Ne.0) Then
Iname=Iname-1
    Write(*,*) " Problem in RGE Running. Errorcode:", kont
    If (kont.eq.-12) Then
      Write(*,*) "Stepsize underflow in rkqs (most likely due to a Landau pole) "
    Else If ((kont.eq.-1).or.(kont.eq.-5).or.(kont.eq.-9)) Then
      Write(*,*) "Stepsize smaller than minimum."
    Else If ((kont.eq.-2).or.(kont.eq.-6).or.(kont.eq.-10)) Then
      Write(*,*) "Running values larger 10^36."
    Else If ((kont.eq.-3).or.(kont.eq.-7).or.(kont.eq.-11)) Then
      Write(*,*) "Too many steps: Running has not converged."
    Else If ((kont.eq.-4).or.(kont.eq.-8)) Then
      Write(*,*) "No GUT scale found."
End If
    Call TerminateProgram
End If
n_tot =1
!mass_new(n_tot:n_tot+-1) = MSd
!n_tot = n_tot + 0
!mass_new(n_tot:n_tot+-1) = MSv
!n_tot = n_tot + 0
!mass_new(n_tot:n_tot+-1) = MSu
!n_tot = n_tot + 0
!mass_new(n_tot:n_tot+-1) = MSe
!n_tot = n_tot + 0
mass_new(n_tot:n_tot+2) = Mhh
n_tot = n_tot + 3
mass_new(n_tot:n_tot+2) = MAh
n_tot = n_tot + 3
mass_new(n_tot:n_tot+1) = MHpm
n_tot = n_tot + 2
mass_new(n_tot:n_tot+4) = MChi
n_tot = n_tot + 5
mass_new(n_tot:n_tot+1) = MCha
Where (mass_new.lt.1E-10_dp) mass_new=0._dp
diff_m=Abs(mass_new-mass_old)
Where (Abs(mass_old).Gt.0._dp) diff_m=diff_m/Abs(mass_old)
deltag0=Maxval(diff_m)
Write(*,*) "  ... reached precision:", deltag0
If (WriteComment) Write(*,*) "Sugra,Comparing",deltag0
If ((deltag0.Lt.delta0).And.(j.Gt.1)) Then! require at least two iterations
   FoundResult= .True.
If (SignOfMassChanged) Then
  If (.Not.IgnoreNegativeMasses) Then
  Write(*,*) " Mass spectrum converged, but negative mass squared present."
   Call TerminateProgram
  Else
   SignOfMassChanged = .False.
   kont = 0
  End If
End If
If (SignOfMuChanged) Then
  If (.Not.IgnoreMuSignFlip) Then
  Write(*,*) " Mass spectrum converged, but negative |mu|^2 from tadpoles."
   Call TerminateProgram
  Else
   SignOfMuChanged = .False.
   kont = 0
  End If
End If
Exit
Else
If (SignOfMassChanged) Then
  If ((j.ge.MinimalNumberIterations).And.(.Not.IgnoreNegativeMasses)) Then
  Write(*,*) " Still a negative mass squared after ",MinimalNumberIterations," iterations. Stop calculation. "
   Call TerminateProgram
  Else
   SignOfMassChanged = .False.
   kont = 0
  End If
End If
If (SignOfMuChanged) Then
  If ((j.ge.MinimalNumberIterations).And.(.Not.IgnoreMuSignFlip)) Then
  Write(*,*) " Still a negative |mu|^2 after ",MinimalNumberIterations," iterations. Stop calculation. "
   Call TerminateProgram
  Else
   SignOfMuChanged = .False.
   kont = 0
  End If
End If
mass_old=mass_new
If (.Not.UseFixedScale) Then
mudimNew=Max(mZ**2,Abs(MSu(1)*MSu(6)))
If (HighScaleModel.eq."LOW") Call SetGUTscale(sqrt(mudimNew))
 UseFixedScale= .False.
End If
If (j.lt.niter) Then
Call GToParameters221(gC,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS)

vd = vdMZ
vu = vuMZ


 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------



 ! --- Boundary conditions at EW-scale when running down ---
! -----------------------



 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))



 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------

If (IgnoreNegativeMassesMZ) Then
  SignMassChangedSave = SignOfMassChanged
End if
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            &
& Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,           &
& pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,             &
& vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             &
& mu2,me2,ms2,M1,M2,M3,GenerationMixing,kont)

If (IgnoreNegativeMassesMZ) Then
  SignOfMassChanged = SignMassChangedSave
End if
If (.Not.UseFixedScale) Then
Call SetRGEScale(mudimNew)
UseFixedScale= .False.
End If
Else
  FoundIterativeSolution = .False.
End if
End If
End Do
If (CalculateOneLoopMassesSave) Then
CalculateOneLoopMasses =  CalculateOneLoopMassesSave
Write(*,*) "Calculate loop corrected masses "
Call OneLoopMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,              &
& MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,               &
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             &
& ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,             &
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont)

If (SignOfMassChanged) Then
  If (.Not.IgnoreNegativeMasses) Then
  Write(*,*) " Mass spectrum converged, but negative mass squared present."
   Call TerminateProgram
  Else
   SignOfMassChanged = .False.
   kont = 0
  End If
End If
If (SignOfMuChanged) Then
  If (.Not.IgnoreMuSignFlip) Then
  Write(*,*) " Mass spectrum converged, but negative |mu|^2 from tadpoles."
   Call TerminateProgram
  Else
   SignOfMuChanged = .False.
   kont = 0
  End If
End If
End if
Iname=Iname-1

End Subroutine Sugra

Subroutine RunRGE(kont, delta0, g1A, g1C, mGUT)
Implicit None
Integer,Intent(inout)::kont
Real(dp),Intent(in)::delta0
Integer :: i1, i2, i3, i4
Real(dp),Intent(inout)::g1A(218)
Real(dp),Intent(out)::g1C(218),mGUT
Real(dp)::tz,dt,t_out
Real(dp)::mudim,gGUT,gA_h(218),g1b(218),m_hi,m_lo
Real(dp)::g1S(218)
Logical :: FoundUnification, unified, greater

Iname=Iname+1
NameOfUnit(Iname)='runRGE'

If (.Not.UseFixedGUTScale) Then
m_lo=5.e12_dp
Else
m_lo=Min(5.e12_dp,GUT_Scale)
End If
mudim=GetRenormalizationScale()
mudim=Max(mudim,mZ2)
tz=0.5_dp*Log(mZ2/mudim)
dt=tz/100._dp
Call odeint(g1A,218,tz,0._dp,delta0,dt,0._dp,rge218,kont)

If (kont.Ne.0) Then
  Iname=Iname-1
  Write(*,*) " Problem with RGE running. Errorcode:", kont
  Call TerminateProgram
End If
Call BoundarySUSY(g1a,g1B)

FoundUnification= .False.
tz=Log(sqrt(mudim)/m_lo)
dt=-tz/50._dp

Call odeint(g1B,218,tz,0._dp,delta0,dt,0._dp,rge218,kont)

If (kont.Ne.0) Then
Iname=Iname-1
  Write(*,*) " Problem with RGE running. Errorcode:", kont
Call TerminateProgram
End If
If (.Not.UseFixedGUTScale) Then
tz=Log(m_lo/1.e20_dp)
dt=-tz/50._dp

Call odeintB2(g1B,218,tz,0._dp,delta0,dt,0._dp,rge218,checkGUT218,t_out,kont)

If (kont.Eq.0) Then
FoundUnification= .True.
mGUT=1.e20_dp*Exp(t_out)
gGUT=Sqrt(0.5_dp*(g1b(1)**2+g1b(2)**2))
If (StrictUnification) g1b(3)=gGUT
Else
Write(ErrCan,*) "kont",kont,delta0,tz,dt
Write (ErrCan,*) "t_out",t_out,1.e20_dp*Exp(t_out)
Write(ErrCan,*) " "
Iname=Iname-1
Return
End If
Else
  tz=Log(m_lo/GUT_scale)
  mGUT=GUT_scale
  dt=-tz/50._dp
Call odeint(g1B,218,tz,0._dp,delta0,dt,0._dp,rge218,kont)

If (kont.Ne.0) Then
Iname=Iname-1
  Write(*,*) " Problem with RGE running. Errorcode:", kont
Call TerminateProgram
End If
End If

mGUT_Save=mGUT
Call BoundaryHS(g1B,g1c)

mudim=GetRenormalizationScale()
mudim=Max(mudim,mZ2)
tz=0.5_dp*Log(mudim/mGUT_save**2)
dt=tz/100._dp
Call odeint(g1c,218,0._dp,tz,delta0,dt,0._dp,rge218,kont)
Iname=Iname-1
Contains

Function InverseMatrix(M) Result(Inv)
Implicit None
Complex(dp), Intent(in) :: M(:,:)
Complex(dp) :: Inv(Size(M,1),Size(M,2))

inv = M
Call gaussj(kont,inv,Size(M,1),Size(M,2))
End Function InverseMatrix

End Subroutine RunRGE

Subroutine checkGUT218(y,eps,unified,greater)
Implicit None
Real(dp), Intent(in) :: y(218), eps
Logical, Intent(out) :: unified, greater
Call GToParameters218(y,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,               &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)

If ((((g1)-(g2)).Gt.0._dp).And.(((g1)-(g2)).Lt.eps)) Then
  unified = .True.
Else
   unified = .False.
End If
If ((g1).Gt.(g2)) Then
  greater = .True.
Else
  greater = .False.
End If
End Subroutine checkGUT218

Subroutine FirstGuess(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               &
& MFu,MFu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,           &
& MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,             &
& ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,             &
& mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont)

Implicit None
Real(dp),Intent(out) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(out) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             &
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(out) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               &
& MFe2(3),MFu(3),MFu2(3),Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(1),MSd2(1),MSe(1),          &
& MSe2(1),MSu(1),MSu2(1),MSv(1),MSv2(1),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(3,3),ZH(3,3),        &
& ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(out) :: pG,UM(2,2),UP(2,2),ZD(1,1),ZDL(3,3),ZDR(3,3),ZE(1,1),ZEL(3,3),ZER(3,3),               &
& ZN(5,5),ZU(1,1),ZUL(3,3),ZUR(3,3),ZV(1,1),ZW(2,2)

Integer,Intent(inout)::kont
Integer :: i1, i2
Real(dp),Intent(inout) :: vd,vu,vS

Real(dp)::vev,vevs(2),vev2,mgut,mudim,mudimNew,sigma(2),mt,mb,cosW,cosW2,sinW2
Complex(dp):: YeSM(3,3), YdSM(3,3), YuSM(3,3)
Real(dp) :: k_fac, g1SM, g2SM, g3SM, vSM
Real(dp), Parameter :: oo2pi=1._dp/(2._dp*pi),oo6pi=oo2pi/3._dp
Real(dp):: gA(218), gB(218), Scale_Save
Logical::TwoLoopRGE_save, UseFixedScale_save
Iname=Iname+1
NameOfUnit(Iname)="FirstGuess"
If (HighScaleModel.eq."LOW") UseFixedGUTScale = .true.

If (tanbeta.gt.3._dp) Then
 tanb = tanbeta
 tanbetaMZ = tanbeta
Else
 tanb = 5._dp
 tanbetaMZ = 5._dp
End if
mW2=mZ2*(0.5_dp+Sqrt(0.25_dp-Alpha_Mz*pi/(sqrt2*G_F*mZ2)))
mW=Sqrt(mW2)
cosW2=mw2/mZ2
sinW2=1._dp-cosW2
cosW=Sqrt(cosW2)

If (tanbeta.gt.5._dp) Then
 k_fac=1._dp-alpha*(oo6pi &
  &-oo2pi*(57._dp*Log(10._dp)+16._dp*Log(mf_u(3)/mZ))/9._dp)
Else
 k_fac=1._dp
End if
g1SM=Sqrt(3._dp/5._dp)*Sqrt(20._dp*pi*alpha_mZ/(k_fac*3._dp*(1._dp-sinW2)))
g2SM=Sqrt(4._dp*pi*alpha_mZ/(k_fac*sinW2))
If (tanbeta.gt.5._dp) Then
 k_fac=1-AlphaS_mZ*oo2pi*(0.5_dp-4._dp*Log(10._dp) &
  &-2._dp*Log(mf_u(3)/mZ)/3._dp)
Else
 k_fac=1._dp
End if
g3SM=Sqrt(4._dp*pi*alphas_mZ)
g3SM=Sqrt(4._dp*pi*alphas_mZ/k_fac)

vSM=2._dp*mW/g2SM
YeSM=0._dp
YdSM=0._dp
YuSM=0._dp
Do i1=1,3
  YeSM(i1,i1)=sqrt2*mf_L_mZ(i1)/vSM
  If (i1.Eq.3) Then! top and bottom are special:
  ! TanBeta Aufsummierung fehlt bei Yd!!
  YuSM(i1,i1)=sqrt2*mf_U(i1)/vSM&
    &*(1._dp-oo3pi*alphas_mZ*(5._dp+3._dp*Log(mZ2/mf_u2(3))))
  YdSM(i1,i1)=sqrt2*mf_D_mZ(i1)/(vSM * (1._dp + 0.015*tanb))
Else
  YuSM(i1,i1)=sqrt2*mf_U_mZ(i1)/vSM
  YdSM(i1,i1)=sqrt2*mf_D_mZ(i1)/vSM
End If
End Do
If (GenerationMixing) Then
  If (YukawaScheme.Eq.1) Then
    YuSM=Matmul(Transpose(CKM),YuSM)
  Else
    YdSM=Matmul(Conjg(CKM),YdSM)
  End If
End If
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)

TwoLoopRGE_save=TwoLoopRGE
UseFixedScale_save = UseFixedScale
Scale_save=GetRenormalizationScale()
UseFixedScale = .True.
Call SetRGEScale(mZ2)
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)


 ! 1. Run



 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------



 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

mHd2 = 0._dp
mHu2 = 0._dp
ms2 = 0._dp


 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------



Call ParametersToG218(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gA)

If (.Not.UseFixedScale) Then
  If (HighScaleModel.eq."LOW") Then
     mudim=1000._dp**2
   Else
    mudim= Real(m0**2 + 4*m12**2, dp)
    mudim=Max(mf_u2(3),mudim)
  End if
   Call SetRGEScale(mudim)
   UseFixedScale= .False.
Else
  mudim=GetRenormalizationScale()
End If
If (HighScaleModel.eq."LOW") Call SetGUTscale(sqrt(mudim))
 TwoLoopRGE= .False.
kont=0
Call RunRGE(kont,0.001_dp,gA,gB,mGUT)
If (kont.Ne.0) Then
Iname=Iname-1
    Write(*,*) " Problem with RGE running. Errorcode:", kont
    Call TerminateProgram
End if
Call GToParameters218(gB,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------





 ! --- Boundary conditions at EW-scale when running down ---
! -----------------------

Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)


 ! 2. Run



 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------



 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))



 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------



Call ParametersToG218(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gA)

If (.Not.UseFixedScale) Then
  If (HighScaleModel.eq."LOW") Then
     mudim=1000._dp**2
   Else
    mudim= Real(m0**2 + 4*m12**2, dp)
    mudim=Max(mf_u2(3),mudim)
  End if
   Call SetRGEScale(mudim)
   UseFixedScale= .False.
Else
  mudim=GetRenormalizationScale()
End If
If (HighScaleModel.eq."LOW") Call SetGUTscale(sqrt(mudim))
 TwoLoopRGE= .False.
kont=0
Call RunRGE(kont,0.001_dp,gA,gB,mGUT)
If (kont.Ne.0) Then
Iname=Iname-1
    Write(*,*) " Problem with RGE running. Errorcode:", kont
    Call TerminateProgram
End if
Call GToParameters218(gB,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------





 ! --- Boundary conditions at EW-scale when running down ---
! -----------------------

Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,vS,g1,             &
& g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,             &
& M1,M2,M3,.False.)


 ! 3. Run



 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------



 ! --- Boundary conditions at SUSY-scale ---
If (HighScaleModel.ne."LOW") Then
 Select Case(BoundaryCondition)
Case (1)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Case (2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
Case (3)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
End Select

else If (HighScaleModel.Eq."LOW") Then
 ! Setting values
 vS = vSIN
 lam = lamIN
 kap = kapIN
 Td = TdIN
 Te = TeIN
 Tlam = TlamIN
 Tk = TkIN
 Tu = TuIN
 mq2 = mq2IN
 ml2 = ml2IN
 mHd2 = mHd2IN
 mHu2 = mHu2IN
 md2 = md2IN
 mu2 = mu2IN
 me2 = me2IN
 ms2 = ms2IN
 M1 = M1IN
 M2 = M2IN
 M3 = M3IN
 kap = KappaInput
lam = LambdaInput
Tk = AKappaInput*KappaInput
Tlam = ALambdaInput*LambdaInput
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
vS = (sqrt(2._dp)*MuEffinput)/LambdaInput
End if

 ! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))



 ! --- GUT normalize gauge couplings ---
g1 = Sqrt(5._dp/3._dp)*g1
! -----------------------



Call ParametersToG218(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,             &
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gA)

Call SetRGEScale(Scale_save)
UseFixedScale = UseFixedScale_save
If (.Not.UseFixedScale) Then
  If (HighScaleModel.eq."LOW") Then
     mudim=1000._dp**2
   Else
    mudim= Real(m0**2 + 4*m12**2, dp)
    mudim=Max(mf_u2(3),mudim)
  End if
   Call SetRGEScale(mudim)
   UseFixedScale= .False.
Else
  mudim=GetRenormalizationScale()
End If
If (HighScaleModel.eq."LOW") Call SetGUTscale(sqrt(mudim))
 TwoLoopRGE= .False.
kont=0
Call RunRGE(kont,0.001_dp,gA,gB,mGUT)
If (kont.Ne.0) Then
Iname=Iname-1
    Write(*,*) " Problem with RGE running. Errorcode:", kont
    Call TerminateProgram
End if
Call GToParameters218(gB,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,              &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3)



 ! --- Remove GUT-normalization of gauge couplings ---
g1 = Sqrt(3._dp/5._dp)*g1
! -----------------------





 ! --- Boundary conditions at EW-scale when running down ---
! -----------------------

TwoLoopRGE = TwoLoopRGE_save
vSM_save = vSM


 ! --- Boundary conditions at EW-scale ---
Select Case(BoundaryCondition)
Case (1)
Case (2)
Case (3)
End Select

! -----------------------

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            &
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,vd,vu,vS,(/ ZeroC, ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            &
& Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,           &
& pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,betaH,             &
& vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,             &
& mu2,me2,ms2,M1,M2,M3,GenerationMixing,kont)

tanb = tanbeta
tanbetaMZ = tanbeta
MVWm = mW
MVWm2 = mW2
MVZ = mZ
MVZ2 = mZ2
MFe(1:3) = mf_l
MFe2(1:3) = mf_l**2
MFu(1:3) = mf_u
MFu2(1:3) = mf_u**2
MFd(1:3) = mf_d
MFd2(1:3) = mf_d**2
Iname=Iname-1
End subroutine FirstGuess
End Module Boundaries_NMSSM
