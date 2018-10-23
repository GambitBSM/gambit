Module TwoLoopHiggsMass_SARAH
!---------------------------------------------------------------------------
! This module contains 2-loop self-energy contribution for the Higgs bosons
! as well as the 2-loop contributions to the tad-poles.
! The orginal routines have been provided by Pietro Slavich
!---------------------------------------------------------------------------
use Control
Use Loopfunctions
Use Mathematics


Interface SfermionMass
  Module Procedure SfermionMass1mssm, SfermionMass3MSSM 
 End Interface


Contains


Subroutine SfermionMass1mssm(M_L2, M_R2, Af, mu, vevs, Yuk, T3, Yl, Yr, &
   &  g, gp, kont, msf, msf2, Rsf)
 !----------------------------------------------------------------------
 ! calculates sfermion masses and mixing angles for complex parameters
 ! for 1 generation
 ! input:
 !  M_L2 ...... left sfermion mass squared
 !  M_R2 ...... right sfermion mass squared
 !  Af ........ trilinear A-parameter
 !  mu ........ mu-parameter
 !  vevs(i) ... i=1 v_d
 !              i=2 v_u
 !  Yuk ....... Yukawa coupling
 !  T3 ........ weak isospin of the left sfermion
 !  Yl ........ hypercharge of the left sfermion
 !  Yr ........ hypercharge of the right sfermion
 !  g ......... SU(2) gauge coupling
 !  gp ........ U(1) gauge coupling
 !  mf ........ fermion mass
 !  msf(i) .... sfermion mass i=1,2 msf(1) < msf(2)
 !  msf2(i) ... sfermion mass squared i=1,2
 !  Rsf(i,j) .. sfermion mixing matrix, i,j =1,2
 ! written by Werner Porod: 9.11.2000
 !----------------------------------------------------------------------
 Implicit None
  Real(Dp), Intent(in) :: M_L2, M_R2, T3, Yl, Yr, vevs(2), g, gp
  Real(Dp), Intent(out) :: msf(2), msf2(2)
  Complex(Dp), Intent(in) :: Af, Yuk, mu
  Complex(Dp), Intent(out) :: Rsf(2, 2)
  Integer, Intent(inout) :: kont
 
  Real(Dp) :: vev2, diag(2), abs_offdiag, trace, det2, det,     &
    &  nen2, nen, cost, sint
  Complex(Dp) :: offdiag, phase

  Iname = Iname + 1

  NameOfUnit(Iname) = 'SfermionMass1MSSM'

  kont = 0

  vev2 = 0.25_dp * (vevs(1)**2 - vevs(2)**2)
  If (T3.Gt.0) Then
   diag(1) = M_L2 + 0.5_dp * Abs(Yuk)**2 * vevs(2)**2        &
     &     + (T3 * g**2 - 0.5_dp * Yl * gp**2) * vev2
   diag(2) = M_R2 + 0.5_dp * Abs(Yuk)**2 * vevs(2)**2        &
     &     - 0.5_dp * Yr * gp**2 * vev2

   offdiag = (Conjg(Af) * vevs(2) - mu * vevs(1) * conjg(Yuk)) * oosqrt2

  Else
   diag(1) = M_L2 + 0.5_dp * Abs(Yuk)**2 * vevs(1)**2        &
     &     + (T3 * g**2 - 0.5_dp * YL * gp**2) * vev2
   diag(2) = M_R2 + 0.5_dp * Abs(Yuk)**2 * vevs(1)**2        &
     &     - 0.5_dp * Yr * gp**2 * vev2

   offdiag = (Conjg(Af) * vevs(1) - Conjg(Yuk) * mu * vevs(2) ) * oosqrt2
  End If
  !------------
  ! Masses
  !------------
  abs_offdiag = Abs(offdiag)
  trace = diag(1) + diag(2)
  det2 = (diag(1) - diag(2) )**2 + 4._dp * abs_offdiag**2

  det = Sqrt(det2)
  msf2(1) = 0.5_dp * (trace-det)
  msf2(2) = 0.5_dp * (trace+det)
  If (msf2(1) .Le.0.) Then
   Write(ErrCan, * ) 'Warning from routine SfermionMass1mssm!'
   Write(ErrCan, * ) 'in the calculation of the masses'
   Write(ErrCan, * ) 'occurred a negative mass squared!!!'
   Write(ErrCan, * ) 'msf2 ', msf2
   Write(ErrCan, * ) 'M_L2, M_R2, Af, mu, vevs, Yuk, T3, Yl, Yr, g, gp'
   Write(ErrCan, * ) M_L2, M_R2, Af, mu, vevs, Yuk, T3, Yl, Yr, g, gp

   kont = - 222
   Call AddError(222)
   msf = Sqrt( Abs(msf2) )

  Else
   msf = Sqrt(msf2 )
  End If

  !---------------
  ! mixing matrix
  !---------------
  If (offdiag.Eq. (0._dp, 0._dp) ) Then
   phase = (1._dp, 0._dp)
  Else If (Aimag(offdiag).eq.0._dp) Then
   If (Real(offdiag).gt.0._dp) Then
    phase = (1._dp, 0._dp)
   Else
    phase = (-1._dp, 0._dp)
   End If
  Else
   phase = (0._dp, 1._dp) * Arg(offdiag)
   Phase =  Exp(phase)
  End If

  nen2 = (diag(1) - msf2(1) )**2 + abs_offdiag**2

  nen = Sqrt(nen2)
  If (nen.Lt.1.e-9_dp) Then
   cost = 1._dp
   sint = 0._dp
  Else
   cost = - abs_offdiag / nen
   sint = (diag(1) - msf2(1) ) / nen
  End If

  Rsf(1, 1) = cost * phase
  Rsf(1, 2) = sint 
  Rsf(2, 1) = - sint
  Rsf(2, 2) = cost / phase

  Iname = Iname - 1

 End Subroutine SfermionMass1mssm

 Subroutine SfermionMass3mssm(M_L2, M_R2, Af, mu, vevs, Yuk, T3, Yl, Yr, &
   &  g, gp, kont, msf, msf2, Rsf)
 !----------------------------------------------------------------------
 ! calculates sfermion masses and mixing angles for complex parameters
 ! for 1 generation
 ! input:
 !  M_L2(i,j) . left sfermion squared mass matrix
 !  M_R2(i,j) . right sfermion squared mass matrix
 !  Af(i,j) ... trilinear A-parameter 
 !  mu ........ mu-parameter
 !  vevs(i) ... i=1 v_d
 !              i=2 v_u
 !  Yuk ....... Yukawa coupling
 !  T3 ........ weak isospin of the left sfermion
 !  Yl ........ hypercharge of the left sfermion
 !  Yr ........ hypercharge of the right sfermion
 !  g ......... SU(2) gauge coupling
 !  gp ........ U(1) gauge coupling
 !  mf ........ fermion mass
 !  msf(i) .... sfermion mass i=1,2 msf(1) < msf(2)
 !  msf2(i) ... sfermion mass squared i=1,2
 !  Rsf(i,j) .. sfermion mixing matrix, i,j =1,2
 ! written by Werner Porod: 9.11.2000
 ! 16.03.03: including a test, if there is really generation mixing
 !----------------------------------------------------------------------
 Implicit None
  Real(Dp), Intent(in) :: T3, Yl, Yr, vevs(2), g, gp
  Real(Dp), Intent(out) :: msf(6), msf2(6)
  Complex(Dp), Intent(in) :: M_L2(3,3), M_R2(3,3), Af(3,3), Yuk(3,3), mu
  Complex(Dp), Intent(out) :: Rsf(6, 6)
  Integer, Intent(inout) :: kont
 
  Integer :: i1, i2, ierr
  Real(Dp) :: vev2, test(2), Rsfa(6,6), m2(2), m22(2), Ml, Mr
  Complex(Dp) :: mat6(6,6), off(3,3), Rsf2(2,2), A, Y &
     & , vec(6), YukT(3,3), YukC(3,3), AfC(3,3)

  Iname = Iname + 1

  NameOfUnit(Iname) = 'SfermionMass3MSSM'

  kont = 0

  vev2 = 0.25_dp * (vevs(1)**2 - vevs(2)**2)

  !-----------------------------------------
  ! test for generation mixing
  !-----------------------------------------
  test(1) = 0._dp
  Do i1=1,2
   Do i2=i1+1,3
    test(1) = test(1) + Abs(M_L2(i1,i2))+Abs(M_r2(i1,i2))+Abs(af(i1,i2))  &
            &         + Abs(Af(i2,i1)) + Abs(Yuk(i1,i2)) + Abs(yuk(i2,i1))
   End Do
  End Do

  If (test(1).Eq.0._dp) Then
   Rsf = 0._dp
   msf2 = 10000._dp
   Do i1=1,3
    Ml = M_L2(i1,i1)
    Mr = M_R2(i1,i1)
    A = Af(i1,i1)
    Y = Yuk(i1,i1)
    Call SfermionMass(Ml, Mr, A, mu, vevs, Y, T3, Yl, Yr, g, gp, ierr &
                    &, m2, m22, Rsf2 )

    If ((ierr.Ne.0).And.(ErrorLevel.Ge.0)) Then
     Write(ErrCan,*) 'Diagonalization did not work in routine SfermionMass3mssm!'
     msf2(2*i1-1:2*i1) = m22
     Write(ErrCan, * ) 'msf2 ', msf2
     Write(ErrCan, * ) 'M_L2, ',M_L2
     Write(ErrCan, * ) 'M_R2, ',M_R2
     Write(ErrCan, * ) 'A_f, ',Af
     Write(ErrCan, * ) 'Y_f, ',Yuk
     Write(ErrCan, * ) 'mu, vevs, T3, Yl, Yr, g, gp'
     Write(ErrCan, * ) mu, vevs, T3, Yl, Yr, g, gp
     kont = ierr
     If (ErrorLevel.Eq.2) Call TerminateProgram
     Iname = Iname - 1
     Return
    End If
    msf(2*i1-1:2*i1) = m2
    Rsf(2*i1-1,i1) = Rsf2(1,1)
    Rsf(2*i1-1,i1+3) = Rsf2(1,2)
    Rsf(2*i1,i1) = Rsf2(2,1)
    Rsf(2*i1,i1+3) = Rsf2(2,2)
   End Do

   !----------------------
   ! reordering
   !----------------------
   Do i1=1,5
    Do i2=i1+1,6
     If (msf(i1).Gt.msf(i2)) Then
      test(1) = msf(i1)
      msf(i1) = msf(i2)
      msf(i2) = test(1)
      vec = Rsf(i1,:)
      Rsf(i1,:) = Rsf(i2,:)
      Rsf(i2,:) = vec
     End If
    End Do
   End Do
   msf2 = msf**2

  Else  ! there is really generation mixing
   test = 0._dp

   YukT = Transpose(Yuk)
   YukC = Conjg(Yuk)
   AfC = Conjg(Af)

   If (T3.Gt.0) Then
    mat6(1:3,1:3) = M_L2 + 0.5_dp * vevs(2)**2 * Matmul(YukC,YukT) &
        &         + (T3 * g**2 - 0.5_dp * Yl * gp**2) * vev2 * id3C
    mat6(4:6,4:6) = M_R2 + 0.5_dp * vevs(2)**2 * Matmul(YukT,YukC) &
       &         - 0.5_dp * Yr * gp**2 * vev2 * id3C
    off = (vevs(2) * AfC - Conjg(mu) * vevs(1) * YukC ) * oosqrt2
   Else
    mat6(1:3,1:3) = M_L2 + 0.5_dp * vevs(1)**2 * Matmul(YukC,YukT) &
        &         + (T3 * g**2 - 0.5_dp * Yl * gp**2) * vev2 * id3C
    mat6(4:6,4:6) = M_R2 + 0.5_dp * vevs(1)**2 * Matmul(YukT,YukC) &
       &         - 0.5_dp * Yr * gp**2 * vev2 * id3C
    off = (vevs(1) * AfC - mu * vevs(2) * YukC ) * oosqrt2
   End If
   mat6(1:3,4:6) = off
   Call Adjungate(off)
   mat6(4:6,1:3) = off      

   If (Maxval(Abs(Aimag(mat6))).Eq.0._dp) Then
    Call EigenSystem(Real(mat6,dp),msf2,Rsfa,ierr, test)
    Rsf = Rsfa
   Else
    Call EigenSystem(mat6,msf2,Rsf,ierr, test)
   End If
 
   If ((ierr.Eq.-14).Or.(ierr.Eq.-16)) Then
     Write(ErrCan,*) "Possible numerical problem in "//NameOfUnit(Iname)
     Write(ErrCan,*) "test =",test
     Write(ErrCan,*) "T_3, Y_l",T3,yl
     Write(ErrCan,*) "M_L2",M_L2(1,:)
     Write(errcan,*) "    ",M_L2(2,:) 
     Write(errcan,*) "    ",M_L2(3,:) 
     Write(ErrCan,*) "M_R2",M_R2(1,:)
     Write(errcan,*) "    ",M_r2(2,:) 
     Write(errcan,*) "    ",M_r2(3,:)
     off =  Matmul(YukC,YukT)
     Write(Errcan,*) "Y^* Y^T",off(1,:)
     Write(errcan,*) "     ",off(2,:)
     Write(errcan,*) "     ",off(3,:)
     off =  Matmul(YukT,YukC)
     Write(Errcan,*) "Y^T Y^*",off(1,:)
     Write(errcan,*) "     ",off(2,:)
     Write(errcan,*) "     ",off(3,:)
     Write(ErrCan,*) "mat 1",mat6(1,:)
     Write(ErrCan,*) "mat 2",mat6(2,:)
     Write(ErrCan,*) "mat 3",mat6(3,:)
     Write(ErrCan,*) "mat 4",mat6(4,:)
     Write(ErrCan,*) "mat 5",mat6(5,:)
     Write(ErrCan,*) "mat 6",mat6(6,:)
     Write(ErrCan,*) " "
     Write(ErrCan,*) "msf2",msf2
     Write(ErrCan,*) "Rsf 1",rsf(1,:)
     Write(ErrCan,*) "Rsf 2",rsf(2,:)
     Write(ErrCan,*) "Rsf 3",rsf(3,:)
     Write(ErrCan,*) "Rsf 4",rsf(4,:)
     Write(ErrCan,*) "Rsf 5",rsf(5,:)
     Write(ErrCan,*) "Rsf 6",rsf(6,:)
     Write(ErrCan,*) " "
     If (ErrorLevel.Eq.2) Call TerminateProgram
     ierr = 0
   End If
  

   If ((ierr.Ne.0).And.(ErrorLevel.Ge.0)) Then
     Write(ErrCan,*) 'Diagonalization did not work in routine SfermionMass3mssm!'
     Write(ErrCan, * ) 'msf2 ', msf2
     Write(ErrCan, * ) 'M_L2, ',M_L2
     Write(ErrCan, * ) 'M_R2, ',M_R2
     Write(ErrCan, * ) 'A_f, ',Af
     Write(ErrCan, * ) 'Y_f, ',Yuk
     Write(ErrCan, * ) 'mu, vevs, T3, Yl, Yr, g, gp'
     Write(ErrCan, * ) mu, vevs, T3, Yl, Yr, g, gp
     kont = ierr
     If (ErrorLevel.Eq.2) Call TerminateProgram
     Iname = Iname - 1
     Return
   End If

   Do i1=1,6
    If (mSf2(i1).Gt.0._dp) Then
     mSf(i1) = Sqrt( mSf2(i1) )
    Else
     kont = -223
     Call AddError(223)
     msf(i1) = 0._dp
     If (ErrorLevel.Ge.0) Then
      Write(ErrCan, * ) 'Warning from routine SfermionMass3mssm!'
      Write(ErrCan, * ) 'in the calculation of the masses'
      Write(ErrCan, * ) 'occurred a negative mass squared!!!'
      Write(ErrCan, * ) 'msf2 ', msf2
      Write(ErrCan, * ) 'M_L2, ',M_L2
      Write(ErrCan, * ) 'M_R2, ',M_R2
      Write(ErrCan, * ) 'A_f, ',Af
      Write(ErrCan, * ) 'Y_f, ',Yuk
      Write(ErrCan, * ) 'mu, vevs, T3, Yl, Yr, g, gp'
      Write(ErrCan, * ) mu, vevs, T3, Yl, Yr, g, gp

      If (ErrorLevel.Eq.2) Call TerminateProgram
     End If
    End If
   End Do
  End If ! test for generation mixing

  Iname = Iname - 1

 End Subroutine SfermionMass3mssm

 Subroutine CalculateStrongCorrections2L(Q2, gSU3, mglu, ZG, vevs, mD2, mU2, mQ2, ME2, ML2, A_b &
                    &, A_t, A_tau, Y_b, Y_t, Y_tau, mu, MDO,mo2,BO,MO,lam,LT,i_os, PiPS2, PiS2, tadpoles,kont)
 !-----------------------------------------------------------------------------
 ! in this routine the 2-loop contributions to the neutral scalar mass matrix
 !   Q2 .................. renormalization scale squared
 !   gSU3 ................ g_strong
 !   mglu ................ m_gluino
 !   mA2 ................. m_A0 squared
 !   vevs(i) ............. vacuum expactation values
 !   mD2 ................. M^2_(\tilde D)
 !   mU2 ................. M^2_(\tilde U)
 !   mQ2 ................. M^2_(\tilde Q)
 !   mE2 ................. M^2_(\tilde E)
 !   mL2 ................. M^2_(\tilde L)
 !   A_t ................. trilinear coupling A_top
 !   A_b ................. trilinear coupling A_bottom
 !   A_tau ............... trilinear coupling A_tau
 !   Y_t ................. top Yukawwa coupling
 !   Y_b ................. bottom Yukawwa coupling
 !   Y_tau ............... tau Yukawwa coupling
 !   mu .................. mu-parameter
 ! output:
 !  PiS2 ........ two-loop contribution to the scalar mass matrix
 !  kont ........ is 0 if everything is o.k., otherwise it gets a negative 
 !                value
 ! written by Werner Porod, 04.03.03
 !-----------------------------------------------------------------------------
 Implicit None
  Integer, intent(in) :: i_os
  Integer, Intent(inout) :: kont 
  Real(dp), Intent(in) :: Q2, gSU3, mglu(2), vevs(4), mQ2, mU2, mD2, ML2, ME2
  Complex(dp), Intent(in) :: A_b, A_t, Y_t, Y_b, mu, A_tau, Y_tau
  complex(dp), Intent(in) :: MDO,MO,BO,lam,LT,ZG(2,2)
  real(dp), intent(in) :: mo2
  Real(dp), Intent(out) :: PiPS2(4,4),PiS2(4,4),tadpoles(4)
  Real(dp) :: s2t, c2t, s2b, c2b, mt, tanb, mb, sb, cb, ht2, mSt(2)    &
    & , mSt2(2), mt2, mb2, mtau, mtau2, muR, mSb(2), mSb2(2), At, Ab   &
    & , hb2, vv, Atau, mStau(2), mStau2(2), s2tau, c2tau, htau2, mSneu2
  Real(dp) :: F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp, hthb       &
    & , F1, F2, F3, sF2, sF3 , F2_s, sF2_A, sF3_A, X, DF1, DF2, DF3, DsF2, DsF3 &
    & , Pi2Sa(2,2), htauhb, DdmuF2, DdmuF3, DM12, DM22, DdAtF2, DdAtF3, dmuF2   &
    & , dmuF3, dAtF2, dAtF3
  Complex(dp) :: RSt(2,2), RSb(2,2), Rstau(2,2)
  Real(dp), Parameter :: YL = 1._dp / 3._dp, YRu = -4._dp / 3._dp  &
       , YRd = 2._dp / 3._dp

  real(dp) :: astrong,st,ct,T1,T2,O1,O2,sO,cO,DMS(4,4),DMP(4,4),temptads(4)
  real(dp) :: sbsquark,cbsquark,PiS2a(2,2),fa_a,pia02
  complex(dp) :: octetBmass
  real(dp) :: octetmmass
  integer :: mi1,mi2,mi1hat,mi2hat
  real(dp) :: mA2

  real(dp) :: twovevs(2)
  complex(dp) :: mutilde

  Iname = Iname + 1
  NameOfUnit(Iname) = "CalculateStrongCorrections2L"
  PiS2 = 0._dp
  kont = 0

  twovevs(1) = vevs(1)
  twovevs(2) = vevs(2)

  mutilde=mu-vevs(3)*lam/sqrt(2._dp)+vevs(4)*LT/sqrt(2._dp)

 !------------------------------------------------------------------------
 ! first the (s)fermion, please note, that the papers by P.Slavich et al. 
 ! the ordering of the sfermions is reversed to compared to my odering
 !------------------------------------------------------------------------

  Call SfermionMass(MQ2, MU2, A_t, mutilde, twovevs, Y_t, 0.5_dp, YL, YRu,   &
  0._dp, 0._dp, kont, mSt, mSt2, RSt)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*)&
     "Stop masses squared for 2-loop calculation of pseudoscalar mass are negativ."
   kont = -604
   Call AddError(604)
   Iname = Iname - 1
   Return
  End If 
  mt2 = 0.5_dp * Abs(Y_t*vevs(2))**2
  Call SfermionMass(MQ2, MD2, A_b, mutilde, twovevs, Y_b, -0.5_dp, YL, YRd,   &
  0._dp, 0._dp, kont, mSb, mSb2, RSb)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
     "Sbottommasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -605
   Call AddError(605)
   Iname = Iname - 1
   Return
  End If 
  mb2 = 0.5_dp * Abs(Y_b*vevs(1))**2


 !------------------------------------------------------------
 ! different mass ordering leads to the following formulas
 !------------------------------------------------------------
  s2t = - 2._dp * Real( RSt(1,1) * RSt(1,2), dp)
  c2t = Abs(RSt(1,2))**2 -  Abs(RSt(1,1))**2
  s2b = - 2._dp * Real( RSb(1,1) * RSb(1,2), dp)
  c2b = Abs(RSb(1,2))**2 -  Abs(RSb(1,1))**2
  mt = Sqrt(mt2)
  mb = Sqrt(mb2)
  ht2 = Abs(Y_t)**2
  hb2 = Abs(Y_b)**2
  tanb = vevs(2) / vevs(1)

!  write(*,*) "Tan beta: ",tanb

  vv = vevs(1)**2 + vevs(2)**2

  cb = 1._dp / Sqrt(1._dp + tanb**2)
  sb = tanb * cb
 
  At = Real(A_t/Y_t, dp)
  Ab = Real(A_b/Y_b, dp)
  Atau = Real(A_tau/Y_tau, dp)
  muR = - Real(mu, dp) ! different sign convention
  X = At + muR * vevs(1) / vevs(2)

  astrong=gSU3**2/(4._dp*PI)


!---------------------------------
! alpha_s alpha_t
!---------------------------------

  T1=mst2(2)
  T2=mst2(1)



  st= real(RSt(2,2))
  ct= - real(RSt(1,2))


  sbsquark = - real(RSb(1,2))
  cbsquark = real(RSb(2,2))

  

  octetBmass=BO+2._dp*MDO**2
  octetMmass=mO2+MO*conjg(MO)+2._dp*MDO*conjg(MDO)


  if(abs(octetBmass) .gt. 1E-8) then
     cO=real(octetBmass/abs(octetBmass))
     sO=-aimag(octetBmass/abs(octetBmass))
  else
     cO=1._dp
     sO=0._dp
  end if


  O1=octetmmass+abs(octetbmass)
  O2=octetmmass-abs(octetbmass)



  DMS=0._dp
  DMP=0._dp
  
  ! In this basis, ZG*MGlu*ZG^T is diagonal, so we have gauge eigenstates = ZG^T. mass eigenstates, thus lambda = ZG(1,1) l1 + ZG(2,1) l2



call effpotasat(2,mt,mglu(1),mglu(2),real(ZG(1,1)**2),reaL(ZG(2,1)**2),MDO*conjg(MDO),T1,T2,st,ct,O1,O2,sO,cO,q2,tanb,sqrt(vv/2),-real(lam),real(LT),mu,vevs(3)/sqrt(2d0),vevs(4)/sqrt(2d0),astrong,DMS,DMP,tadpoles)



  do mi1=1,4
     do mi2=1,4
        PiS2(mi1,mi2) = DMS(mi1,mi2)
        PiPS2(mi1,mi2) = DMP(mi1,mi2)
!        
        end do
     end do


 !---------------------------------------------
 ! alpha_s alpha_b
 !---------------------------------------------
  X = Ab + muR * vevs(2) / vevs(1)
  
  DMS=0._dp
  DMP=0._dp
  call effpotasat(2,mb,mglu(1),mglu(2),real(ZG(1,1)**2),reaL(ZG(2,1)**2),MDO*conjg(MDO),msb2(2),msb2(1),sbsquark,cbsquark,O1,O2,sO,cO,q2,1d0/tanb,sqrt(vv/2),-real(lam),real(LT),mu,vevs(3)/sqrt(2d0),vevs(4)/sqrt(2d0),astrong,DMS,DMP,temptads) 


! write(*,*) "as ab: "
    do mi1=1,4
       
       if (mi1.lt.3) then
          mi1hat=3-mi1
       else
          mi1hat=mi1
       end if
       tadpoles(mi1) = tadpoles(mi1)+temptads(mi1hat)
    do mi2=1,4
        
        if(mi2.lt.3) then
           mi2hat=3-mi2
        else
           mi2hat=mi2
        end if

        PiS2(mi1,mi2) = PiS2(mi1,mi2) + DMS(mi1hat,mi2hat)
        PiPS2(mi1,mi2) = PiPS2(mi1,mi2) + DMP(mi1hat,mi2hat)

        end do
        write(*,*) 
     end do
    


  Iname = Iname - 1


 end subroutine CalculateStrongCorrections2L






 Subroutine makefuncs(t,b,A0,T1,T2,B1,B2,s2t,c2t,s2b,c2b, &
    q,mu,vv,tanb,F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6, Ft,Fb,Gt,Gb,FAp)
  !---------------------------------------------------------------------
  ! original code provided by Pietro Slavich
  ! Based on A. Dedes, G. Degrassi and P. Slavich, hep-ph/0305127
  !---------------------------------------------------------------------
  Implicit None
  Real(dp) :: t,b,A0,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,mu,vv,tanb, &
    F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp

  Real(dp) :: At, Ab, Xt, Xb

  Real(dp) :: D1t,DT1,DT2,Dc2t,DT1T1,DT2T2,Dtt,Dc2tc2t,DT1t,DT2t,DT1T2, &
    Dtc2t,DT1c2t,DT2c2t,Dtb,DT1b,DT2b,DB1t,DB2t,DT1B1,DT2B1, &
    DT1B2,DT2B2,Dbc2t,DB1c2t,DB2c2t,DT1c2b,DT2c2b,Dc2tc2b, &
    Dcptpb,Dcpttptb,Dcpbptt,Dcptptb,Dcptmptt,Dcpbmptb, &
    Dspbmptbspbptt,Dsptmpttsptptb,Dsptmpttspbmptb

  Call makederiv(t,b,A0,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,mu,vv,tanb)

  F1t = Dtt + DT1T1 + DT2T2 + 2._dp*(DT1t + DT2t + DT1T2) &
    & + (Dcptpb + Dcptmptt + Dcptptb - 2._dp*Dsptmpttsptptb) /4._dp/t**2

  F2t = DT1T1 - DT2T2 + DT1t - DT2t                    &
    & - 4._dp*c2t**2/(T1-T2)*(Dtc2t + DT1c2t + DT2c2t) &
    & - (Dcptmptt - Dsptmpttsptptb)/s2t**2/t/(T1-T2)

  F3t = DT1T1 + DT2T2 - 2._dp*DT1T2- 2._dp/(T1-T2)*(DT1-DT2) &
    & + 16._dp*c2t**2/(T1-T2)**2*(c2t**2*Dc2tc2t + 2._dp*Dc2t) &
    & - 8._dp*c2t**2/(T1-T2)*(DT1c2t-DT2c2t)                   &
    & + 4._dp/s2t**4/(T1-T2)**2*(Dcptmptt + Dcpbptt + Dcpttptb)

  F4t = DT1b + DT1B1 + DT1B2 - DT2b - DT2B1 - DT2B2          &
    & - 4._dp*c2t**2/(T1-T2)*(DB1c2t + DB2c2t + Dbc2t)         &
    & - (Dcpbptt + Dsptmpttspbmptb - Dspbmptbspbptt) /b/s2t**2/(T1-T2)

  F5 = DT1B1 - DT1B2 - DT2B1 + DT2B2                 &
   & + 16._dp*c2t**2*c2b**2/(T1-T2)/(B1-B2)*Dc2tc2b    &
   & - 4._dp*c2t**2/(T1-T2)*(DB1c2t-DB2c2t)            &
   & - 4._dp*c2b**2/(B1-B2)*(DT1c2b-DT2c2b)            &
   & - 4._dp/s2b**2/s2t**2/(T1-T2)/(B1-B2)             &
   &   * (Dcpttptb-Dsptmpttspbmptb + Dspbmptbspbptt + Dsptmpttsptptb)

  F6 = Dtb + DT1b + DT2b + DB1t + DB2t+ DT1B1 + DT1B2 + DT2B1 + DT2B2 &
   & - (Dcptpb - Dsptmpttspbmptb)/4._dp/b/t

  Ft = DT1 - DT2 - 4._dp*c2t**2/(T1-T2)*Dc2t
  Gt = D1t + DT1 + DT2

  Xt = (T1-T2)*s2t/2._dp/Sqrt(t)    
  Xb = (B1-B2)*s2b/2._dp/Sqrt(b)
  At = Xt - mu/tanb
  Ab = Xb - mu*tanb
  FAp = 0.25_dp * Dcptpb/Sqrt(b)/Sqrt(t)                                &
    & +4._dp*(At*Ab - mu**2)**2*Sqrt(t)*Sqrt(b)                         &
    &       /s2t**2/s2b**2/(T1-T2)**2/(B1-B2)**2*Dcpttptb               &
    & + Sqrt(t)/Sqrt(b)/s2t**2/(T1-T2)**2                               &
    &           * (At**2*Dcpbptt + mu**2/tanb**2*Dcptmptt)              &
    & + Sqrt(b)/Sqrt(t)/s2b**2/(B1-B2)**2                               &
    &           * (Ab**2*Dcptptb + mu**2*tanb**2*Dcpbmptb)              &
    & - 2._dp*mu/s2t/s2b/(T1-T2)/(B1-B2)                                &
    &   * (At*tanb*Dspbmptbspbptt + Ab/tanb*Dsptmpttsptptb+ mu*Dsptmpttspbmptb)

  Call makederiv(b,t,A0,B1,B2,T1,T2,s2b,c2b,s2t,c2t,q,mu,vv,1d0/tanb) 

  F1b = Dtt + DT1T1 + DT2T2 + 2._dp*(DT1t + DT2t + DT1T2) &
    & + (Dcptpb + Dcptmptt + Dcptptb - 2._dp*Dsptmpttsptptb) /4._dp/b**2

  F2b = DT1T1 - DT2T2 + DT1t - DT2t                  &
    & - 4._dp*c2b**2/(B1-B2)*(Dtc2t + DT1c2t + DT2c2t) &
    & - (Dcptmptt - Dsptmpttsptptb)/s2b**2/b/(B1-B2)

  F3b = DT1T1 + DT2T2 - 2._dp*DT1T2- 2._dp/(B1-B2)*(DT1-DT2) &
    & + 16._dp*c2b**2/(B1-B2)**2*(c2b**2*Dc2tc2t + 2._dp*Dc2t) &
    & - 8._dp*c2b**2/(B1-B2)*(DT1c2t-DT2c2t)                   &
    & + 4._dp/s2b**4/(B1-B2)**2*(Dcptmptt + Dcpbptt + Dcpttptb)

  F4b = DT1b + DT1B1 + DT1B2 - DT2b - DT2B1 - DT2B2          &
    & - 4._dp*c2b**2/(B1-B2)*(DB1c2t + DB2c2t + Dbc2t)         &
    & - (Dcpbptt + Dsptmpttspbmptb - Dspbmptbspbptt) /t/s2b**2/(B1-B2)
  
  Fb = DT1 - DT2 - 4._dp*c2b**2/(B1-B2)*Dc2t
  Gb = D1t + DT1 + DT2
  
  Contains

   Subroutine makederiv(t,b,A0,T1,T2,B1,B2,s2t,c2t,s2b,c2b, q,mu,vv,tanb)
   Implicit Real(dp) (t)
   Implicit Character (a-s,u-z)
   Real(dp) :: t,b,A0,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,mu,vv,tanb
   Real(dp) :: ht,hb,mt,mb,Xt,Xb,Yt,Yb,sbe,cbe,mu2

   Real(dp) :: Log_A0_q, Log_b_q, Log_t_q, Log_B1_q, Log_B2_q, Log_T1_q       &
     & , Log_T2_q, log_mu2_q, phi_A0_T1_B1, phi_A0_T1_B2, phi_A0_T2_B1        &
     & , phi_A0_T2_B2, phi_A0_t_b, phi_T1_t_mu2, phi_T2_t_mu2, phi_T1_b_mu2   &
     & , phi_T2_b_mu2, phi_B1_t_mu2, phi_B2_t_mu2, phi_A0_T1_T1, phi_A0_T1_T2 &
     & , phi_A0_T2_T2, phi_A0_t_t, delt_A0_T1_B1, delt_A0_T1_B2               &
     & , delt_A0_T2_B2, delt_A0_t_b, delt_T1_t_mu2, delt_T2_t_mu2             &
     & , delt_T2_b_mu2, delt_B1_t_mu2, delt_B2_t_mu2, delt_A0_T1_T2           &
     & , delt_A0_T2_T2, delt_A0_t_t, delt_A0_T2_B1, delt_T1_b_mu2             &
     & , delt_A0_T1_T1, abs_mu
   Real(dp), Parameter :: Nc=3._dp
   !      real(dp) Delt,phi,Li2
   
   mt = Sqrt(t)
   mb = Sqrt(b)
   sbe = Sin(Atan(tanb))
   cbe = Cos(Atan(tanb))
   
   ht = Sqrt(2._dp/vv)*mt/sbe
   hb = Sqrt(2._dp/vv)*mb/cbe
   
   Xt = (T1-T2)*s2t/2._dp/mt    
   Xb = (B1-B2)*s2b/2._dp/mb           
   Yt  = Xt - mu/sbe/cbe
   Yb  = Xb - mu/sbe/cbe
   
   mu2 = mu**2
   ! this was a bug in Pietro's file, where on several places Sqrt(mu**2)
   ! appeared instead of
   abs_mu = mu ! Abs(mu)

   Log_A0_q = Log(A0/q)
   Log_b_q = Log(b/q)
   Log_t_q = Log(t/q)
   Log_B1_q = Log(B1/q)
   Log_B2_q = Log(B2/q)
   Log_T1_q = Log(T1/q)
   Log_T2_q = Log(T2/q)
   Log_mu2_q = Log(mu2/q)

   phi_A0_t_b = phi(A0,t,b)
   phi_A0_t_t = phi(A0,t,t)
   phi_A0_T1_T1 = phi(A0,T1,T1)
   phi_A0_T1_T2 = phi(A0,T1,T2)
   phi_A0_T2_T2 = phi(A0,T2,T2)
   phi_A0_T1_B1 = phi(A0,T1,B1)
   phi_A0_T1_B2 = phi(A0,T1,B2)
   phi_A0_T2_B1 = phi(A0,T2,B1)
   phi_A0_T2_B2 = phi(A0,T2,B2)
   phi_T1_t_mu2 = phi(T1,t,mu2)
   phi_T2_t_mu2 = phi(T2,t,mu2)
   phi_T1_b_mu2 = phi(T1,b,mu2)
   phi_T2_b_mu2 = phi(T2,b,mu2)
   phi_B1_t_mu2 = phi(B1,t,mu2)
   phi_B2_t_mu2 = phi(B2,t,mu2)

   delt_A0_t_b = delt(A0,t,b)
   delt_A0_t_t = delt(A0,t,t)
   delt_A0_T1_T1 = delt(A0,T1,T1)
   delt_A0_T1_T2 = delt(A0,T1,T2)
   delt_A0_T2_T2 = delt(A0,T2,T2)
   delt_A0_T1_B1 = delt(A0,T1,B1)
   delt_A0_T1_B2 = delt(A0,T1,B2)
   delt_A0_T2_B1 = delt(A0,T2,B1)
   delt_A0_T2_B2 = delt(A0,T2,B2)
   delt_T1_t_mu2 = delt(T1,t,mu2)
   delt_T2_t_mu2 = delt(T2,t,mu2)
   delt_T1_b_mu2 = delt(T1,b,mu2)
   delt_T2_b_mu2 = delt(T2,b,mu2)
   delt_B1_t_mu2 = delt(B1,t,mu2)
   delt_B2_t_mu2 = delt(B2,t,mu2)

   tmp1 = 0.25_dp*hb**2/c2t - 0.25_dp*ht**2/c2t
   tmp2 = -(0.25_dp*hb**2/c2t) + 0.25_dp*ht**2/c2t
   tmp3 = c2t**2 - 0.5_dp*((-1 + Nc)*s2t**2)
   tmp4 = cbe**2*ht**2 + hb**2*sbe**2
   tmp5 = cbe**2*hb**2 + ht**2*sbe**2
   tmp6 = -(0.5_dp*(mb*cbe**2*ht**2*s2b*s2t*mt)  &
     &     +0.5_dp*(mb*hb**2*s2b*s2t*sbe**2*mt))
   tmp7 = 0.5_dp*(mb*cbe**2*ht**2*s2b*s2t*mt) + &
     &0.5_dp*(mb*hb**2*s2b*s2t*sbe**2*mt)
   tmp8 = -(0.5_dp*(mb*cbe**2*hb**2*s2b*s2t*mt)) - &
     &0.5_dp*(mb*ht**2*s2b*s2t*sbe**2*mt)
   tmp9 = 0.5_dp*(mb*cbe**2*hb**2*s2b*s2t*mt) + &
     &0.5_dp*(mb*ht**2*s2b*s2t*sbe**2*mt)
   tmp10 = 0.25_dp*((1 + c2b)*(1 + c2t)) + 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 + c2b)*s2t*Xb)/mt
   tmp11 = 0.0625_dp*b/(c2b*c2t) + &
     &0.125_dp*(mb*mt)/(s2b*s2t) + 0.0625_dp*t/(c2b*c2t) - &
     &0.125_dp*(mb*Xb)/(c2t*s2b) + &
     &0.125_dp*(mt*Xb)/(c2b*s2t) - 0.0625_dp*Xb**2/(c2b*c2t)
   tmp12 = -(0.0625_dp*b/(c2b*c2t)) - &
     &0.125_dp*(mb*mt)/(s2b*s2t) - 0.0625_dp*t/(c2b*c2t) + &
     &0.125_dp*(mb*Xb)/(c2t*s2b) - &
     &0.125_dp*(mt*Xb)/(c2b*s2t) + 0.0625_dp*Xb**2/(c2b*c2t)
   tmp13 = 0.25_dp*Xb/c2b - 0.25_dp*Xt/c2b
   tmp14 = -(0.25_dp*Xb/c2b) + 0.25_dp*Xt/c2b
   tmp15 = 0.125_dp*Xb/c2t**3 - 0.125_dp*Xt/c2t**3
   tmp16 = -(0.125_dp*Xb/c2t**3) + 0.125_dp*Xt/c2t**3
   tmp17 = 0.25_dp*Xb/c2t - 0.25_dp*Xt/c2t
   tmp18 = -(0.25_dp*Xb/c2t) + 0.25_dp*Xt/c2t
   tmp19 = 4 - (2*s2t*Xt)/mt
   tmp20 = 4 + (2*s2t*Xt)/mt
   tmp21 = 0.25_dp*((1 + c2b)*(1 + c2t)) + 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 + c2b)*s2t*Xt)/mt
   tmp22 = (-2*mt*Xt)/s2t - Xt**2
   tmp23 = (2*mt*Xt)/s2t - Xt**2
   tmp24 = 0.0625_dp*b/(c2b*c2t) + &
     &0.125_dp*(mb*mt)/(s2b*s2t) + 0.0625_dp*t/(c2b*c2t) + &
     &0.125_dp*(mb*Xt)/(c2t*s2b) - &
     &0.125_dp*(mt*Xt)/(c2b*s2t) - 0.0625_dp*Xt**2/(c2b*c2t)
   tmp25 = -(0.0625_dp*b/(c2b*c2t)) - &
     &0.125_dp*(mb*mt)/(s2b*s2t) - 0.0625_dp*t/(c2b*c2t) - &
     &0.125_dp*(mb*Xt)/(c2t*s2b) + &
     &0.125_dp*(mt*Xt)/(c2b*s2t) + 0.0625_dp*Xt**2/(c2b*c2t)
   tmp26 = 4*t - 4*s2t*mt*Xt + s2t**2*Xt**2
   tmp27 = 4*t + 4*s2t*mt*Xt + s2t**2*Xt**2
   tmp28 = 0.25_dp*((1 + c2b)*(1 + c2t)) + 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 + c2b)*s2t*Yb)/mt
   tmp29 = 0.0625_dp*b/(c2b*c2t) + &
     &0.125_dp*(mb*mt)/(s2b*s2t) + 0.0625_dp*t/(c2b*c2t) - &
     &0.125_dp*(mb*Yb)/(c2t*s2b) + &
     &0.125_dp*(mt*Yb)/(c2b*s2t) - 0.0625_dp*Yb**2/(c2b*c2t)
   tmp30 = -(0.0625_dp*b/(c2b*c2t)) - &
     &0.125_dp*(mb*mt)/(s2b*s2t) - 0.0625_dp*t/(c2b*c2t) + &
     &0.125_dp*(mb*Yb)/(c2t*s2b) - &
     &0.125_dp*(mt*Yb)/(c2b*s2t) + 0.0625_dp*Yb**2/(c2b*c2t)
   tmp31 = 0.25_dp*Yb/c2b - 0.25_dp*Yt/c2b
   tmp32 = -(0.25_dp*Yb/c2b) + 0.25_dp*Yt/c2b
   tmp33 = 0.125_dp*Yb/c2t**3 - 0.125_dp*Yt/c2t**3
   tmp34 = -(0.125_dp*Yb/c2t**3) + 0.125_dp*Yt/c2t**3
   tmp35 = 0.25_dp*Yb/c2t - 0.25_dp*Yt/c2t
   tmp36 = -(0.25_dp*Yb/c2t) + 0.25_dp*Yt/c2t
   tmp37 = 4 - (2*s2t*Yt)/mt
   tmp38 = 4 + (2*s2t*Yt)/mt
   tmp39 = 0.25_dp*((1 + c2b)*(1 + c2t)) + 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 + c2b)*s2t*Yt)/mt
   tmp40 = (-2*mt*Yt)/s2t - Yt**2
   tmp41 = (2*mt*Yt)/s2t - Yt**2
   tmp42 = 0.0625_dp*b/(c2b*c2t) + &
     &0.125_dp*(mb*mt)/(s2b*s2t) + 0.0625_dp*t/(c2b*c2t) + &
     &0.125_dp*(mb*Yt)/(c2t*s2b) - &
     &0.125_dp*(mt*Yt)/(c2b*s2t) - 0.0625_dp*Yt**2/(c2b*c2t)
   tmp43 = -(0.0625_dp*b/(c2b*c2t)) - &
     &0.125_dp*(mb*mt)/(s2b*s2t) - 0.0625_dp*t/(c2b*c2t) - &
     &0.125_dp*(mb*Yt)/(c2t*s2b) + &
     &0.125_dp*(mt*Yt)/(c2b*s2t) + 0.0625_dp*Yt**2/(c2b*c2t)
   tmp44 = 4*t - 4*s2t*mt*Yt + s2t**2*Yt**2
   tmp45 = 4*t + 4*s2t*mt*Yt + s2t**2*Yt**2
   tmp46 = 0.0625_dp*(1 - c2b)/c2t**3 - 0.0625_dp*(1 + c2b)/c2t**3
   tmp47 = -(0.0625_dp*(1 - c2b)/c2t**3) + 0.0625_dp*(1 + c2b)/c2t**3
   tmp48 = 0.125_dp*(1 - c2b)/c2t - 0.125_dp*(1 + c2b)/c2t
   tmp49 = -(0.125_dp*(1 - c2b)/c2t) + 0.125_dp*(1 + c2b)/c2t
   tmp50 = 0.25_dp*((1 + c2b)*(1 - c2t)) + 0.25_dp*((1 - c2b)*(1 + c2t))
   tmp51 = 0.125_dp*(1 - c2t)/c2b - 0.125_dp*(1 + c2t)/c2b
   tmp52 = -(0.125_dp*(1 - c2t)/c2b) + 0.125_dp*(1 + c2t)/c2b
   tmp53 = 0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*((1 + c2b)*(1 + c2t))
   tmp54 = 0.5_dp*((1 + c2b)*hb**2) + 0.5_dp*((1 - c2b)*ht**2)
   tmp55 = 0.5_dp*((1 - c2b)*hb**2) + 0.5_dp*((1 + c2b)*ht**2)
   tmp56 = 0.5_dp*((1 + c2t)*hb**2) + 0.5_dp*((1 - c2t)*ht**2)
   tmp57 = 0.5_dp*((1 - c2t)*hb**2) + 0.5_dp*((1 + c2t)*ht**2)
   tmp58 = 0.25_dp*((1 - c2b)*(1 + c2t)) - 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 - c2b)*s2t*Xb)/mt
   tmp59 = 0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 - c2b)*s2t*Xb)/mt
   tmp60 = 0.25_dp*((1 + c2b)*(1 - c2t)) - 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 + c2b)*s2t*Xb)/mt
   tmp61 = 0.25_dp*(b*(1 + c2b)*(1 - c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*t) + 0.5_dp*(mb*(1 - c2t)*s2b*Xb) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Xb) + 0.25_dp*((1 - c2b)*(1 - c2t)*Xb**2)
   tmp62 = 0.25_dp*(b*(1 - c2b)*(1 - c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*t) - 0.5_dp*(mb*(1 - c2t)*s2b*Xb) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Xb) + 0.25_dp*((1 + c2b)*(1 - c2t)*Xb**2)
   tmp63 = -(0.125_dp*(b*(1 + c2b))/c2t) + 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 - c2b)*t)/c2t - 0.25_dp*(mb*s2b*Xb)/c2t + &
     &0.25_dp*((1 - c2b)*mt*Xb)/s2t - 0.125_dp*((1 - c2b)*Xb**2)/c2t
   tmp64 = 0.125_dp*(b*(1 + c2b))/c2t - 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 - c2b)*t)/c2t + 0.25_dp*(mb*s2b*Xb)/c2t - &
     &0.25_dp*((1 - c2b)*mt*Xb)/s2t + 0.125_dp*((1 - c2b)*Xb**2)/c2t
   tmp65 = -(0.125_dp*(b*(1 - c2b))/c2t) - 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 + c2b)*t)/c2t + 0.25_dp*(mb*s2b*Xb)/c2t + &
     &0.25_dp*((1 + c2b)*mt*Xb)/s2t - 0.125_dp*((1 + c2b)*Xb**2)/c2t
   tmp66 = 0.125_dp*(b*(1 - c2b))/c2t + 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 + c2b)*t)/c2t - 0.25_dp*(mb*s2b*Xb)/c2t - &
     &0.25_dp*((1 + c2b)*mt*Xb)/s2t + 0.125_dp*((1 + c2b)*Xb**2)/c2t
   tmp67 = 0.25_dp*(b*(1 + c2b)*(1 + c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*t) + 0.5_dp*(mb*(1 + c2t)*s2b*Xb) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Xb) + 0.25_dp*((1 - c2b)*(1 + c2t)*Xb**2)
   tmp68 = 0.25_dp*(b*(1 - c2b)*(1 + c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*t) - 0.5_dp*(mb*(1 + c2t)*s2b*Xb) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Xb) + 0.25_dp*((1 + c2b)*(1 + c2t)*Xb**2)
   tmp69 = 0.5_dp*((1 + c2b)*Xb) + 0.5_dp*((1 - c2b)*Xt)
   tmp70 = 0.5_dp*((1 - c2b)*Xb) + 0.5_dp*((1 + c2b)*Xt)
   tmp71 = 0.5_dp*((1 + c2t)*Xb) + 0.5_dp*((1 - c2t)*Xt)
   tmp72 = 0.5_dp*((1 - c2t)*Xb) + 0.5_dp*((1 + c2t)*Xt)
   tmp73 = 0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 - c2b)*s2t*Xt)/mt
   tmp74 = 0.25_dp*((1 - c2b)*(1 + c2t)) - 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 - c2b)*s2t*Xt)/mt
   tmp75 = 0.25_dp*((1 + c2b)*(1 - c2t)) - 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 + c2b)*s2t*Xt)/mt
   tmp76 = 0.25_dp*(b*(1 + c2b)*(1 - c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*t) - 0.5_dp*(mb*(1 - c2t)*s2b*Xt) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Xt) + 0.25_dp*((1 - c2b)*(1 - c2t)*Xt**2)
   tmp77 = 0.25_dp*(b*(1 - c2b)*(1 - c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*t) + 0.5_dp*(mb*(1 - c2t)*s2b*Xt) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Xt) + 0.25_dp*((1 + c2b)*(1 - c2t)*Xt**2)
   tmp78 = -(0.125_dp*(b*(1 + c2b))/c2t) + 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 - c2b)*t)/c2t + 0.25_dp*(mb*s2b*Xt)/c2t - &
     &0.25_dp*((1 - c2b)*mt*Xt)/s2t - 0.125_dp*((1 - c2b)*Xt**2)/c2t
   tmp79 = 0.125_dp*(b*(1 + c2b))/c2t - 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 - c2b)*t)/c2t - 0.25_dp*(mb*s2b*Xt)/c2t + &
     &0.25_dp*((1 - c2b)*mt*Xt)/s2t + 0.125_dp*((1 - c2b)*Xt**2)/c2t
   tmp80 = -(0.125_dp*(b*(1 - c2b))/c2t) - 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 + c2b)*t)/c2t - 0.25_dp*(mb*s2b*Xt)/c2t - &
     &0.25_dp*((1 + c2b)*mt*Xt)/s2t - 0.125_dp*((1 + c2b)*Xt**2)/c2t
   tmp81 = 0.125_dp*(b*(1 - c2b))/c2t + 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 + c2b)*t)/c2t + 0.25_dp*(mb*s2b*Xt)/c2t + &
     &0.25_dp*((1 + c2b)*mt*Xt)/s2t + 0.125_dp*((1 + c2b)*Xt**2)/c2t
   tmp82 = 0.25_dp*(b*(1 + c2b)*(1 + c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*t) - 0.5_dp*(mb*(1 + c2t)*s2b*Xt) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Xt) + 0.25_dp*((1 - c2b)*(1 + c2t)*Xt**2)
   tmp83 = 0.25_dp*(b*(1 - c2b)*(1 + c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*t) + 0.5_dp*(mb*(1 + c2t)*s2b*Xt) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Xt) + 0.25_dp*((1 + c2b)*(1 + c2t)*Xt**2)
   tmp84 = 0.25_dp*((1 - c2b)*(1 + c2t)) - 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 - c2b)*s2t*Yb)/mt
   tmp85 = 0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 - c2b)*s2t*Yb)/mt
   tmp86 = 0.25_dp*((1 + c2b)*(1 - c2t)) - 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 + c2b)*s2t*Yb)/mt
   tmp87 = 0.25_dp*(b*(1 + c2b)*(1 - c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*t) + 0.5_dp*(mb*(1 - c2t)*s2b*Yb) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Yb) + 0.25_dp*((1 - c2b)*(1 - c2t)*Yb**2)
   tmp88 = 0.25_dp*(b*(1 - c2b)*(1 - c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*t) - 0.5_dp*(mb*(1 - c2t)*s2b*Yb) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Yb) + 0.25_dp*((1 + c2b)*(1 - c2t)*Yb**2)
   tmp89 = -(0.125_dp*(b*(1 + c2b))/c2t) + 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 - c2b)*t)/c2t - 0.25_dp*(mb*s2b*Yb)/c2t + &
     &0.25_dp*((1 - c2b)*mt*Yb)/s2t - 0.125_dp*((1 - c2b)*Yb**2)/c2t
   tmp90 = 0.125_dp*(b*(1 + c2b))/c2t - 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 - c2b)*t)/c2t + 0.25_dp*(mb*s2b*Yb)/c2t - &
     &0.25_dp*((1 - c2b)*mt*Yb)/s2t + 0.125_dp*((1 - c2b)*Yb**2)/c2t
   tmp91 = -(0.125_dp*(b*(1 - c2b))/c2t) - 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 + c2b)*t)/c2t + 0.25_dp*(mb*s2b*Yb)/c2t + &
     &0.25_dp*((1 + c2b)*mt*Yb)/s2t - 0.125_dp*((1 + c2b)*Yb**2)/c2t
   tmp92 = 0.125_dp*(b*(1 - c2b))/c2t + 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 + c2b)*t)/c2t - 0.25_dp*(mb*s2b*Yb)/c2t - &
     &0.25_dp*((1 + c2b)*mt*Yb)/s2t + 0.125_dp*((1 + c2b)*Yb**2)/c2t
   tmp93 = 0.25_dp*(b*(1 + c2b)*(1 + c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*t) + 0.5_dp*(mb*(1 + c2t)*s2b*Yb) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Yb) + 0.25_dp*((1 - c2b)*(1 + c2t)*Yb**2)
   tmp94 = 0.25_dp*(b*(1 - c2b)*(1 + c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*t) - 0.5_dp*(mb*(1 + c2t)*s2b*Yb) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Yb) + 0.25_dp*((1 + c2b)*(1 + c2t)*Yb**2)
   tmp95 = 0.5_dp*((1 + c2b)*Yb) + 0.5_dp*((1 - c2b)*Yt)
   tmp96 = 0.5_dp*((1 - c2b)*Yb) + 0.5_dp*((1 + c2b)*Yt)
   tmp97 = 0.5_dp*((1 + c2t)*Yb) + 0.5_dp*((1 - c2t)*Yt)
   tmp98 = 0.5_dp*((1 - c2t)*Yb) + 0.5_dp*((1 + c2t)*Yt)
   tmp99 = 0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 - c2b)*s2t*Yt)/mt
   tmp100 = 0.25_dp*((1 - c2b)*(1 + c2t)) - 0.25_dp*(mb*s2b*s2t)/mt + &
     &0.25_dp*((1 - c2b)*s2t*Yt)/mt
   tmp101 = 0.25_dp*((1 + c2b)*(1 - c2t)) - 0.25_dp*(mb*s2b*s2t)/mt - &
     &0.25_dp*((1 + c2b)*s2t*Yt)/mt
   tmp102 = 0.25_dp*(b*(1 + c2b)*(1 - c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*t) - 0.5_dp*(mb*(1 - c2t)*s2b*Yt) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Yt) + 0.25_dp*((1 - c2b)*(1 - c2t)*Yt**2)
   tmp103 = 0.25_dp*(b*(1 - c2b)*(1 - c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*t) + 0.5_dp*(mb*(1 - c2t)*s2b*Yt) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Yt) + 0.25_dp*((1 + c2b)*(1 - c2t)*Yt**2)
   tmp104 = -(0.125_dp*(b*(1 + c2b))/c2t) + 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 - c2b)*t)/c2t + 0.25_dp*(mb*s2b*Yt)/c2t - &
     &0.25_dp*((1 - c2b)*mt*Yt)/s2t - 0.125_dp*((1 - c2b)*Yt**2)/c2t
   tmp105 = 0.125_dp*(b*(1 + c2b))/c2t - 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 - c2b)*t)/c2t - 0.25_dp*(mb*s2b*Yt)/c2t + &
     &0.25_dp*((1 - c2b)*mt*Yt)/s2t + 0.125_dp*((1 - c2b)*Yt**2)/c2t
   tmp106 = -(0.125_dp*(b*(1 - c2b))/c2t) - 0.25_dp*(mb*s2b*mt)/s2t + &
     &0.125_dp*((1 + c2b)*t)/c2t - 0.25_dp*(mb*s2b*Yt)/c2t - &
     &0.25_dp*((1 + c2b)*mt*Yt)/s2t - 0.125_dp*((1 + c2b)*Yt**2)/c2t
   tmp107 = 0.125_dp*(b*(1 - c2b))/c2t + 0.25_dp*(mb*s2b*mt)/s2t - &
     &0.125_dp*((1 + c2b)*t)/c2t + 0.25_dp*(mb*s2b*Yt)/c2t + &
     &0.25_dp*((1 + c2b)*mt*Yt)/s2t + 0.125_dp*((1 + c2b)*Yt**2)/c2t
   tmp108 = 0.25_dp*(b*(1 + c2b)*(1 + c2t)) + 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*t) - 0.5_dp*(mb*(1 + c2t)*s2b*Yt) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Yt) + 0.25_dp*((1 - c2b)*(1 + c2t)*Yt**2)
   tmp109 = 0.25_dp*(b*(1 - c2b)*(1 + c2t)) - 0.5_dp*(mb*s2b*s2t*mt) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*t) + 0.5_dp*(mb*(1 + c2t)*s2b*Yt) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Yt) + 0.25_dp*((1 + c2b)*(1 + c2t)*Yt**2)
   tmp110 = -A0 + (A0 - t)**2/b - t
   tmp111 = -A0 + (A0 - t)**2/t - t
   tmp112 = -A0 + (A0 - T1)**2/B1 - T1
   tmp113 = -A0 + (A0 - T1)**2/B2 - T1
   tmp114 = -A0 + (A0 - T1)**2/T1 - T1
   tmp115 = -A0 - T1 + (A0 - T1)**2/T2
   tmp116 = -A0 + (A0 - T2)**2/B1 - T2
   tmp117 = -A0 + (A0 - T2)**2/B2 - T2
   tmp118 = -A0 + (A0 - T2)**2/T2 - T2
   tmp119 = cbe**2*hb**2*tmp66 + ht**2*sbe**2*tmp78 - &
     &cbe*hb*ht*sbe*(-(s2b*mt*tmp17) + &
     &2*mb*mt*tmp48 + 0.25_dp*(s2b*(b + t))/s2t - &
     &0.5_dp*(mb*tmp69)/s2t + 0.25_dp*(s2b*Xb*Xt)/s2t)
   tmp120 = cbe**2*hb**2*tmp64 + ht**2*sbe**2*tmp80 - &
     &cbe*hb*ht*sbe*(s2b*mt*tmp17 + &
     &2*mb*mt*tmp49 - 0.25_dp*(s2b*(b + t))/s2t - &
     &0.5_dp*(mb*tmp70)/s2t - 0.25_dp*(s2b*Xb*Xt)/s2t)
   tmp121 = cbe**2*hb**2*tmp65 + ht**2*sbe**2*tmp79 - &
     &cbe*hb*ht*sbe*(-(s2b*mt*tmp18) + &
     &2*mb*mt*tmp49 - 0.25_dp*(s2b*(b + t))/s2t + &
     &0.5_dp*(mb*tmp69)/s2t - 0.25_dp*(s2b*Xb*Xt)/s2t)
   tmp122 = cbe**2*hb**2*tmp63 + ht**2*sbe**2*tmp81 - &
     &cbe*hb*ht*sbe*(s2b*mt*tmp18 + &
     &2*mb*mt*tmp48 + 0.25_dp*(s2b*(b + t))/s2t + &
     &0.5_dp*(mb*tmp70)/s2t + 0.25_dp*(s2b*Xb*Xt)/s2t)
   tmp123 = cbe**2*ht**2*tmp104 + hb**2*sbe**2*tmp92 + &
     &cbe*hb*ht*sbe*(-(s2b*mt*tmp35) + &
     &2*mb*mt*tmp48 + 0.25_dp*(s2b*(b + t))/s2t - &
     &0.5_dp*(mb*tmp95)/s2t + 0.25_dp*(s2b*Yb*Yt)/s2t)
   tmp124 = cbe**2*ht**2*tmp106 + hb**2*sbe**2*tmp90 + &
     &cbe*hb*ht*sbe*(s2b*mt*tmp35 + &
     &2*mb*mt*tmp49 - 0.25_dp*(s2b*(b + t))/s2t - &
     &0.5_dp*(mb*tmp96)/s2t - 0.25_dp*(s2b*Yb*Yt)/s2t)
   tmp125 = cbe**2*ht**2*tmp105 + hb**2*sbe**2*tmp91 + &
     &cbe*hb*ht*sbe*(-(s2b*mt*tmp36) + &
     &2*mb*mt*tmp49 - 0.25_dp*(s2b*(b + t))/s2t + &
     &0.5_dp*(mb*tmp95)/s2t - 0.25_dp*(s2b*Yb*Yt)/s2t)
   tmp126 = cbe**2*ht**2*tmp107 + hb**2*sbe**2*tmp89 + &
     &cbe*hb*ht*sbe*(s2b*mt*tmp36 + &
     &2*mb*mt*tmp48 + 0.25_dp*(s2b*(b + t))/s2t + &
     &0.5_dp*(mb*tmp96)/s2t + 0.25_dp*(s2b*Yb*Yt)/s2t)
   tmp127 = cbe**2*hb**2*tmp60 + ht**2*sbe**2*tmp74 - &
     &cbe*hb*ht*sbe*((mb*tmp50)/mt - 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2b*tmp71)/mt)
   tmp128 = ht**2*sbe**2*tmp21 + cbe**2*hb**2*tmp59 - &
     &cbe*hb*ht*sbe*((mb*tmp53)/mt + 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2b*tmp71)/mt)
   tmp129 = cbe**2*hb**2*tmp68 + ht**2*sbe**2*tmp76 - &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp50 + &
     &mb*s2t*tmp69 - s2b*mt*tmp71 - &
     &0.5_dp*(s2b*s2t*(b + t)) - 0.5_dp*(s2b*s2t*Xb*Xt))
   tmp130 = cbe**2*hb**2*tmp67 + ht**2*sbe**2*tmp77 - &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp53 + &
     &mb*s2t*tmp70 + s2b*mt*tmp71 + &
     &0.5_dp*(s2b*s2t*(b + t)) + 0.5_dp*(s2b*s2t*Xb*Xt))
   tmp131 = cbe**2*hb**2*tmp10 + ht**2*sbe**2*tmp73 - &
     &cbe*hb*ht*sbe*((mb*tmp53)/mt + 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2b*tmp72)/mt)
   tmp132 = cbe**2*hb**2*tmp58 + ht**2*sbe**2*tmp75 - &
     &cbe*hb*ht*sbe*((mb*tmp50)/mt - 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2b*tmp72)/mt)
   tmp133 = cbe**2*hb**2*tmp62 + ht**2*sbe**2*tmp82 - &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp53 - &
     &mb*s2t*tmp69 - s2b*mt*tmp72 + &
     &0.5_dp*(s2b*s2t*(b + t)) + 0.5_dp*(s2b*s2t*Xb*Xt))
   tmp134 = cbe**2*hb**2*tmp61 + ht**2*sbe**2*tmp83 - &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp50 - &
     &mb*s2t*tmp70 + s2b*mt*tmp72 - &
     &0.5_dp*(s2b*s2t*(b + t)) - 0.5_dp*(s2b*s2t*Xb*Xt))
   tmp135 = cbe**2*ht**2*tmp100 + hb**2*sbe**2*tmp86 + &
     &cbe*hb*ht*sbe*((mb*tmp50)/mt - 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2b*tmp97)/mt)
   tmp136 = cbe**2*ht**2*tmp39 + hb**2*sbe**2*tmp85 + &
     &cbe*hb*ht*sbe*((mb*tmp53)/mt + 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2b*tmp97)/mt)
   tmp137 = cbe**2*ht**2*tmp102 + hb**2*sbe**2*tmp94 + &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp50 + &
     &mb*s2t*tmp95 - s2b*mt*tmp97 - &
     &0.5_dp*(s2b*s2t*(b + t)) - 0.5_dp*(s2b*s2t*Yb*Yt))
   tmp138 = cbe**2*ht**2*tmp103 + hb**2*sbe**2*tmp93 + &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp53 + &
     &mb*s2t*tmp96 + s2b*mt*tmp97 + &
     &0.5_dp*(s2b*s2t*(b + t)) + 0.5_dp*(s2b*s2t*Yb*Yt))
   tmp139 = hb**2*sbe**2*tmp28 + cbe**2*ht**2*tmp99 + &
     &cbe*hb*ht*sbe*((mb*tmp53)/mt + 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2b*tmp98)/mt)
   tmp140 = cbe**2*ht**2*tmp101 + hb**2*sbe**2*tmp84 + &
     &cbe*hb*ht*sbe*((mb*tmp50)/mt - 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2b*tmp98)/mt)
   tmp141 = cbe**2*ht**2*tmp108 + hb**2*sbe**2*tmp88 + &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp53 - &
     &mb*s2t*tmp95 - s2b*mt*tmp98 + &
     &0.5_dp*(s2b*s2t*(b + t)) + 0.5_dp*(s2b*s2t*Yb*Yt))
   tmp142 = cbe**2*ht**2*tmp109 + hb**2*sbe**2*tmp87 + &
     &cbe*hb*ht*sbe*(2*mb*mt*tmp50 - &
     &mb*s2t*tmp96 + s2b*mt*tmp98 - &
     &0.5_dp*(s2b*s2t*(b + t)) - 0.5_dp*(s2b*s2t*Yb*Yt))
   tmp143 = (A0 - b)/b - t/b + Log_A0_q - Log_b_q
   tmp144 = -Log_A0_q + Log_b_q
   tmp145 = 4*t - 2*b*Log_b_q
   tmp146 = -Log_A0_q + Log_B1_q
   tmp147 = 4*T1 - 2*B1*Log_B1_q
   tmp148 = 4*T2 - 2*B1*Log_B1_q
   tmp149 = -Log_A0_q + Log_B2_q
   tmp150 = 4*T1 - 2*B2*Log_B2_q
   tmp151 = 4*T2 - 2*B2*Log_B2_q
   tmp152 = -Log_b_q + Log_mu2_q
   tmp153 = -((b - mu2)/b) - T1/b - Log_b_q + Log_mu2_q
   tmp154 = -((b - mu2)/b) - T2/b - Log_b_q + Log_mu2_q
   tmp155 = -Log_B1_q + Log_mu2_q
   tmp156 = -Log_B2_q + Log_mu2_q
   tmp157 = Log_A0_q - Log_t_q
   tmp158 = Log_b_q - Log_t_q
   tmp159 = -Log_A0_q + 2*Log_b_q - Log_t_q
   tmp160 = 2*Log_B1_q - Log_mu2_q - Log_t_q
   tmp161 = 2*Log_B2_q - Log_mu2_q - Log_t_q
   tmp162 = Log_mu2_q - Log_t_q
   tmp163 = -(B1/t) - (-mu2 + t)/t + Log_mu2_q - Log_t_q
   tmp164 = -(B2/t) - (-mu2 + t)/t + Log_mu2_q - Log_t_q
   tmp165 = -Log_A0_q + Log_t_q
   tmp166 = -Log_A0_q - Log_b_q + 2*Log_t_q
   tmp167 = 2 - Log_A0_q - Log_b_q + 2*Log_t_q
   tmp168 = -Log_B1_q - Log_mu2_q + 2*Log_t_q
   tmp169 = 2 - Log_B1_q - Log_mu2_q + 2*Log_t_q
   tmp170 = -Log_B2_q - Log_mu2_q + 2*Log_t_q
   tmp171 = 2 - Log_B2_q - Log_mu2_q + 2*Log_t_q
   tmp172 = 2/t**2 - (2*Log_t_q)/t**2
   tmp173 = 4*t - 2*t*Log_t_q
   tmp174 = Log_A0_q - Log_T1_q
   tmp175 = Log_B1_q - Log_T1_q
   tmp176 = -Log_A0_q + 2*Log_B1_q - Log_T1_q
   tmp177 = Log_B2_q - Log_T1_q
   tmp178 = -Log_A0_q + 2*Log_B2_q - Log_T1_q
   tmp179 = 2*Log_b_q - Log_mu2_q - Log_T1_q
   tmp180 = Log_mu2_q - Log_T1_q
   tmp181 = -Log_mu2_q + 2*Log_t_q - Log_T1_q
   tmp182 = -Log_A0_q + Log_T1_q
   tmp183 = -Log_A0_q - Log_B1_q + 2*Log_T1_q
   tmp184 = -Log_A0_q - Log_B2_q + 2*Log_T1_q
   tmp185 = -Log_b_q - Log_mu2_q + 2*Log_T1_q
   tmp186 = 2 - Log_b_q - Log_mu2_q + 2*Log_T1_q
   tmp187 = -Log_mu2_q - Log_t_q + 2*Log_T1_q
   tmp188 = 2/T1**2 - (2*Log_T1_q)/T1**2
   tmp189 = 4*T1 - 2*T1*Log_T1_q
   tmp190 = Log_A0_q - Log_T2_q
   tmp191 = Log_B1_q - Log_T2_q
   tmp192 = -Log_A0_q + 2*Log_B1_q - Log_T2_q
   tmp193 = Log_B2_q - Log_T2_q
   tmp194 = -Log_A0_q + 2*Log_B2_q - Log_T2_q
   tmp195 = 2*Log_b_q - Log_mu2_q - Log_T2_q
   tmp196 = Log_mu2_q - Log_T2_q
   tmp197 = -Log_mu2_q + 2*Log_t_q - Log_T2_q
   tmp198 = -Log_A0_q + 2*Log_T1_q - Log_T2_q
   tmp199 = -Log_A0_q + Log_T2_q
   tmp200 = -Log_T1_q + Log_T2_q
   tmp201 = -Log_A0_q - Log_B1_q + 2*Log_T2_q
   tmp202 = -Log_A0_q - Log_B2_q + 2*Log_T2_q
   tmp203 = -Log_b_q - Log_mu2_q + 2*Log_T2_q
   tmp204 = 2 - Log_b_q - Log_mu2_q + 2*Log_T2_q
   tmp205 = -Log_mu2_q - Log_t_q + 2*Log_T2_q
   tmp206 = -Log_A0_q - Log_T1_q + 2*Log_T2_q
   tmp207 = 2/T2**2 - (2*Log_T2_q)/T2**2
   tmp208 = 4*T1 - 2*T2*Log_T2_q
   tmp209 = 4*T2 - 2*T2*Log_T2_q
   tmp210 = -(2.5_dp*(A0 + B1 + T1)) + &
     &0.5_dp*((-A0 - B1 + T1)*Log_A0_q*Log_B1_q) + &
     &0.5_dp*((-A0 + B1 - T1)*Log_A0_q*Log_T1_q) + &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q*Log_T1_q) - &
     &0.5_dp*(delt_A0_T1_B1*phi_A0_T1_B1)/B1 + 2*A0*Log_A0_q + &
     &2*B1*Log_B1_q + 2*T1*Log_T1_q
   tmp211 = -(2.5_dp*(A0 + B2 + T1)) + &
     &0.5_dp*((-A0 - B2 + T1)*Log_A0_q*Log_B2_q) + &
     &0.5_dp*((-A0 + B2 - T1)*Log_A0_q*Log_T1_q) + &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q*Log_T1_q) - &
     &0.5_dp*(delt_A0_T1_B2*phi_A0_T1_B2)/B2 + 2*A0*Log_A0_q + &
     &2*B2*Log_B2_q + 2*T1*Log_T1_q
   tmp212 = -(2.5_dp*(A0 + B1 + T2)) + &
     &0.5_dp*((-A0 - B1 + T2)*Log_A0_q*Log_B1_q) + &
     &0.5_dp*((-A0 + B1 - T2)*Log_A0_q*Log_T2_q) + &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q*Log_T2_q) - &
     &0.5_dp*(delt_A0_T2_B1*phi_A0_T2_B1)/B1 + 2*A0*Log_A0_q + &
     &2*B1*Log_B1_q + 2*T2*Log_T2_q
   tmp213 = -(2.5_dp*(A0 + B2 + T2)) + &
     &0.5_dp*((-A0 - B2 + T2)*Log_A0_q*Log_B2_q) + &
     &0.5_dp*((-A0 + B2 - T2)*Log_A0_q*Log_T2_q) + &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q*Log_T2_q) - &
     &0.5_dp*(delt_A0_T2_B2*phi_A0_T2_B2)/B2 + 2*A0*Log_A0_q + &
     &2*B2*Log_B2_q + 2*T2*Log_T2_q
   tmp214 = -(2.5_dp*(B1 + mu2 + t)) + 2.5_dp*(B2 + mu2 + t) + &
     &0.5_dp*((-B1 - mu2 + t)*Log_B1_q*Log_mu2_q) - &
     &0.5_dp*((-B2 - mu2 + t)*Log_B2_q*Log_mu2_q) + &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q*Log_t_q) - &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q*Log_t_q) + &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q*Log_t_q) - &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q*Log_t_q) - &
     &0.5_dp*(delt_B1_t_mu2*phi_B1_t_mu2)/mu2 + &
     &0.5_dp*(delt_B2_t_mu2*phi_B2_t_mu2)/mu2 + 2*B1*Log_B1_q - 2*B2*Log_B2_q
   tmp215 = -(2.5_dp*(b + mu2 + T1)) + &
     &0.5_dp*((-b - mu2 + T1)*Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q*Log_T1_q) + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q*Log_T1_q) - &
     &0.5_dp*(delt_T1_b_mu2*phi_T1_b_mu2)/mu2 + 2*b*Log_b_q + &
     &2*mu2*Log_mu2_q + 2*T1*Log_T1_q
   tmp216 = -(2.5_dp*(b + mu2 + T2)) + &
     &0.5_dp*((-b - mu2 + T2)*Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q*Log_T2_q) + &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q*Log_T2_q) - &
     &0.5_dp*(delt_T2_b_mu2*phi_T2_b_mu2)/mu2 + 2*b*Log_b_q + &
     &2*mu2*Log_mu2_q + 2*T2*Log_T2_q
   tmp217 = -(2.5_dp*(b + mu2 + T1)) + 2.5_dp*(b + mu2 + T2) + &
     &0.5_dp*((-b - mu2 + T1)*Log_b_q*Log_mu2_q) - &
     &0.5_dp*((-b - mu2 + T2)*Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q*Log_T1_q) + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q*Log_T1_q) - &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q*Log_T2_q) - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q*Log_T2_q) - &
     &0.5_dp*(delt_T1_b_mu2*phi_T1_b_mu2)/mu2 + &
     &0.5_dp*(delt_T2_b_mu2*phi_T2_b_mu2)/mu2 + 2*T1*Log_T1_q - 2*T2*Log_T2_q
   tmp218 = b/((1 - b/t)*t**3) +  (b**2*tmp158)/((1 - b/t)**2*t**4) +  &
     (2*b*tmp158)/((1 - b/t)*t**3)
   tmp219 = -5 + (2*(T1 - T2)*T2*tmp200)/ &
     (T1**2*(1 - T2/T1)) + tmp208/T1 - 2*Li2(1 - T2/T1) + &
     &4*Log_T1_q + (2*(-T1 + T2)*Log_T1_q)/T1 - Log_T1_q**2
   tmp220 = -((-b - mu2 + T1)*tmp215) + &
     &b*mu2*(-1 + Log_b_q)*(-1 + Log_mu2_q) - &
     &b*T1*(-1 + Log_b_q)*(-1 + Log_T1_q) - &
     &mu2*T1*(-1 + Log_mu2_q)*(-1 + Log_T1_q)
   tmp221 = -((-b - mu2 + T2)*tmp216) + &
     &b*mu2*(-1 + Log_b_q)*(-1 + Log_mu2_q) - &
     &b*T2*(-1 + Log_b_q)*(-1 + Log_T2_q) - &
     &mu2*T2*(-1 + Log_mu2_q)*(-1 + Log_T2_q)
   tmp222 = 2/t**2 - (2*(-1 + Log_t_q))/t**2
   tmp223 = -5 + tmp145/t +  &
     (2*b*(-b + t)*tmp158)/((1 - b/t)*t**2) - 2*Li2(1 - b/t) + &
     &4*Log_t_q + (2*(b - t)*Log_t_q)/t - Log_t_q**2
   tmp224 = -5*b - 5*t - 2*(-b + t)*Li2(1 - b/t) + &
     &4*b*Log_b_q + tmp145*Log_t_q + (b - t)*Log_t_q**2
   tmp225 = -5 + tmp147/T1 +  (2*B1*(-B1 + T1)*tmp175)/((1 - B1/T1)*T1**2) - &
     &2*Li2(1 - B1/T1) + 4*Log_T1_q +  (2*(B1 - T1)*Log_T1_q)/T1 - Log_T1_q**2
   tmp226 = -5 + tmp150/T1 +  (2*B2*(-B2 + T1)*tmp177)/((1 - B2/T1)*T1**2) - &
     &2*Li2(1 - B2/T1) + 4*Log_T1_q +  (2*(B2 - T1)*Log_T1_q)/T1 - Log_T1_q**2
   tmp227 = -5*B1 - 5*T1 - 2*(-B1 + T1)*Li2(1 - B1/T1) + &
     &4*B1*Log_B1_q + tmp147*Log_T1_q + (B1 - T1)*Log_T1_q**2
   tmp228 = -5*B2 - 5*T1 - 2*(-B2 + T1)*Li2(1 - B2/T1) + &
     &4*B2*Log_B2_q + tmp150*Log_T1_q + (B2 - T1)*Log_T1_q**2
   tmp229 = -(0.0625_dp* (B1*T1*(-1 + Log_B1_q)*(-1 + Log_T1_q))/(c2b*c2t)) + &
     &0.0625_dp*(B2*T1*(-1 + Log_B2_q)*(-1 + Log_T1_q))/ (c2b*c2t)+0.0625_dp* &
     (B1*T2*(-1 + Log_B1_q)*(-1 + Log_T2_q))/(c2b*c2t) - &
     &0.0625_dp*(B2*T2*(-1 + Log_B2_q)*(-1 + Log_T2_q))/(c2b*c2t)
   tmp230 = -5 + tmp148/T2 +  (2*B1*(-B1 + T2)*tmp191)/((1 - B1/T2)*T2**2) - &
     &2*Li2(1 - B1/T2) + 4*Log_T2_q +  (2*(B1 - T2)*Log_T2_q)/T2 - Log_T2_q**2
   tmp231 = -5 + tmp151/T2 +  (2*B2*(-B2 + T2)*tmp193)/((1 - B2/T2)*T2**2) - &
     &2*Li2(1 - B2/T2) + 4*Log_T2_q +  (2*(B2 - T2)*Log_T2_q)/T2 - Log_T2_q**2
   tmp232 = -5*B1 - 5*T2 - 2*(-B1 + T2)*Li2(1 - B1/T2) + &
     &4*B1*Log_B1_q + tmp148*Log_T2_q + (B1 - T2)*Log_T2_q**2
   tmp233 = -5*B2 - 5*T2 - 2*(-B2 + T2)*Li2(1 - B2/T2) + &
     &4*B2*Log_B2_q + tmp151*Log_T2_q + (B2 - T2)*Log_T2_q**2
   tmp234 = (b*((A0 - b)*tmp144 + t*tmp166))/ (t*delt_A0_t_b) +  &
     ((A0 + b - t)*phi_A0_t_b)/delt_A0_t_b
   tmp235 = ((-A0 + t)*tmp157 + b*tmp159)/delt_A0_t_b +  &
     (tmp110*phi_A0_t_b)/delt_A0_t_b
   tmp236 = ((-A0 + t)*tmp157 + t*tmp165)/delt_A0_t_t +  &
     ((A0 - t)*tmp165 + t*tmp165)/delt_A0_t_t + (A0*phi_A0_t_t)/delt_A0_t_t + &
     (tmp111*phi_A0_t_t)/delt_A0_t_t
   tmp237 = (B1*((A0 - B1)*tmp146 + T1*tmp183))/ (T1*delt_A0_T1_B1) +  &
     ((A0 + B1 - T1)*phi_A0_T1_B1)/delt_A0_T1_B1
   tmp238 = ((-A0 + T1)*tmp174 + B1*tmp176)/ &
     delt_A0_T1_B1 + (tmp112*phi_A0_T1_B1)/delt_A0_T1_B1
   tmp239 = (B2*((A0 - B2)*tmp149 + T1*tmp184))/ (T1*delt_A0_T1_B2) +  &
     ((A0 + B2 - T1)*phi_A0_T1_B2)/delt_A0_T1_B2
   tmp240 = ((-A0 + T1)*tmp174 + B2*tmp178)/ &
     delt_A0_T1_B2 + (tmp113*phi_A0_T1_B2)/delt_A0_T1_B2
   tmp241 = ((-A0 + T1)*tmp174 + T1*tmp182)/ delt_A0_T1_T1 +  &
     ((A0 - T1)*tmp182 + T1*tmp182)/delt_A0_T1_T1 +  &
     (A0*phi_A0_T1_T1)/delt_A0_T1_T1 +  (tmp114*phi_A0_T1_T1)/delt_A0_T1_T1
   tmp242 = -(2.5_dp*(A0 + 2*T1)) + 0.5_dp*((A0 - 2*T1)*Log_T1_q**2) - &
     &0.5_dp*(delt_A0_T1_T1*phi_A0_T1_T1)/T1 + 2*A0*Log_A0_q + &
     &4*T1*Log_T1_q - A0*Log_A0_q*Log_T1_q
   tmp243 = (T2*(T1*tmp198 + (A0 - T2)*tmp199))/ (T1*delt_A0_T1_T2) +  &
     ((A0 - T1 + T2)*phi_A0_T1_T2)/delt_A0_T1_T2
   tmp244 = ((-A0 + T1)*tmp174 + T2*tmp206)/ &
     delt_A0_T1_T2 + (tmp115*phi_A0_T1_T2)/delt_A0_T1_T2
   tmp245 = (B1*((A0 - B1)*tmp146 + T2*tmp201))/ (T2*delt_A0_T2_B1) +  &
     ((A0 + B1 - T2)*phi_A0_T2_B1)/delt_A0_T2_B1
   tmp246 = ((-A0 + T2)*tmp190 + B1*tmp192)/ &
     delt_A0_T2_B1 + (tmp116*phi_A0_T2_B1)/delt_A0_T2_B1
   tmp247 = (B2*((A0 - B2)*tmp149 + T2*tmp202))/ (T2*delt_A0_T2_B2) +  &
     ((A0 + B2 - T2)*phi_A0_T2_B2)/delt_A0_T2_B2
   tmp248 = ((-A0 + T2)*tmp190 + B2*tmp194)/ &
     delt_A0_T2_B2 + (tmp117*phi_A0_T2_B2)/delt_A0_T2_B2
   tmp249 = ((-A0 + T2)*tmp190 + T2*tmp199)/ delt_A0_T2_T2 +  &
     ((A0 - T2)*tmp199 + T2*tmp199)/delt_A0_T2_T2 +  &
     (A0*phi_A0_T2_T2)/delt_A0_T2_T2 +  (tmp118*phi_A0_T2_T2)/delt_A0_T2_T2
   tmp250 = -(2.5_dp*(A0 + 2*T2)) + 0.5_dp*((A0 - 2*T2)*Log_T2_q**2) - &
     &0.5_dp*(delt_A0_T2_T2*phi_A0_T2_T2)/T2 + 2*A0*Log_A0_q + &
     &4*T2*Log_T2_q - A0*Log_A0_q*Log_T2_q
   tmp251 = (mu2*((B1 - mu2)*tmp155 + t*tmp168))/ (t*delt_B1_t_mu2) +  &
     ((B1 + mu2 - t)*phi_B1_t_mu2)/delt_B1_t_mu2
   tmp252 = (mu2*(B1*tmp160 + (-mu2 + t)*tmp162))/ (B1*delt_B1_t_mu2) +  &
     ((-B1 + mu2 + t)*phi_B1_t_mu2)/delt_B1_t_mu2
   tmp253 = (mu2*((B2 - mu2)*tmp156 + t*tmp170))/ (t*delt_B2_t_mu2) +  &
     ((B2 + mu2 - t)*phi_B2_t_mu2)/delt_B2_t_mu2
   tmp254 = (mu2*(B2*tmp161 + (-mu2 + t)*tmp162))/ (B2*delt_B2_t_mu2) +  &
     ((-B2 + mu2 + t)*phi_B2_t_mu2)/delt_B2_t_mu2
   tmp255 = (mu2*((b - mu2)*tmp152 + T1*tmp185))/ (T1*delt_T1_b_mu2) +  &
     ((b + mu2 - T1)*phi_T1_b_mu2)/delt_T1_b_mu2
   tmp256 = (mu2*(b*tmp179 + (-mu2 + T1)*tmp180))/ (b*delt_T1_b_mu2) +  &
     ((-b + mu2 + T1)*phi_T1_b_mu2)/delt_T1_b_mu2
   tmp257 = (mu2*((-mu2 + t)*tmp162 + T1*tmp187))/ (T1*delt_T1_t_mu2) +  &
     ((mu2 + t - T1)*phi_T1_t_mu2)/delt_T1_t_mu2
   tmp258 = (mu2*((-mu2 + T1)*tmp180 + t*tmp181))/ (t*delt_T1_t_mu2) +  &
     ((mu2 - t + T1)*phi_T1_t_mu2)/delt_T1_t_mu2
   tmp259 = (mu2*((b - mu2)*tmp152 + T2*tmp203))/ (T2*delt_T2_b_mu2) +  &
     ((b + mu2 - T2)*phi_T2_b_mu2)/delt_T2_b_mu2
   tmp260 = (mu2*(b*tmp195 + (-mu2 + T2)*tmp196))/ (b*delt_T2_b_mu2) +  &
     ((-b + mu2 + T2)*phi_T2_b_mu2)/delt_T2_b_mu2
   tmp261 = (mu2*((-mu2 + t)*tmp162 + T2*tmp205))/ (T2*delt_T2_t_mu2) +  &
     ((mu2 + t - T2)*phi_T2_t_mu2)/delt_T2_t_mu2
   tmp262 = (mu2*((-mu2 + T2)*tmp196 + t*tmp197))/ (t*delt_T2_t_mu2) +  &
     ((mu2 - t + T2)*phi_T2_t_mu2)/delt_T2_t_mu2
   tmp263 = -6 + tmp173/t + 4*Log_t_q + (2 - 2*Log_t_q)*Log_t_q
   tmp264 = -6 + tmp189/T1 + 4*Log_T1_q +  (2 - 2*Log_T1_q)*Log_T1_q
   tmp265 = -1 - (2*(T1 - T2)*tmp200)/(T1*(1 - T2/T1)) + &
     &2*Li2(1 - T2/T1) + Log_T1_q**2 + Log_T1_q*(-2 - 2*Log_T2_q) + 4*Log_T2_q
   tmp266 = -6 + tmp209/T2 + 4*Log_T2_q +  (2 - 2*Log_T2_q)*Log_T2_q
   tmp267 = 2.5_dp*(b + mu2 + T1)-0.5_dp*((-b - mu2 + T1)*Log_b_q*Log_mu2_q)- &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q*Log_T1_q) - &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q*Log_T1_q) + &
     &0.5_dp*(delt_T1_b_mu2*phi_T1_b_mu2)/mu2 - &
     &b*(-1 + Log_b_q) - 2*b*Log_b_q - &
     &mu2*(-1 + Log_mu2_q) - 2*mu2*Log_mu2_q - &
     &b*(-1 + Log_b_q)*(-1 + Log_T1_q) - &
     &mu2*(-1 + Log_mu2_q)*(-1 + Log_T1_q) - 2*T1*Log_T1_q -  &
     (-b - mu2 + T1)*(-0.5_dp - 0.5_dp*(tmp255*delt_T1_b_mu2)/mu2 + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1 + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1 + &
     &0.5_dp*(Log_b_q*Log_mu2_q) - 0.5_dp*(Log_b_q*Log_T1_q) - &
     &0.5_dp*(Log_mu2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-b - mu2 + T1)*phi_T1_b_mu2)/mu2)
   tmp268 = 2.5_dp*(b + mu2 + T2)-0.5_dp*((-b - mu2 + T2)*Log_b_q*Log_mu2_q)- &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q*Log_T2_q) - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q*Log_T2_q) + &
     &0.5_dp*(delt_T2_b_mu2*phi_T2_b_mu2)/mu2 - &
     &b*(-1 + Log_b_q) - 2*b*Log_b_q - &
     &mu2*(-1 + Log_mu2_q) - 2*mu2*Log_mu2_q - &
     &b*(-1 + Log_b_q)*(-1 + Log_T2_q) - &
     &mu2*(-1 + Log_mu2_q)*(-1 + Log_T2_q) - 2*T2*Log_T2_q -  &
     (-b - mu2 + T2)*(-0.5_dp - 0.5_dp*(tmp259*delt_T2_b_mu2)/mu2 + &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2 + &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2 + &
     &0.5_dp*(Log_b_q*Log_mu2_q) - 0.5_dp*(Log_b_q*Log_T2_q) - &
     &0.5_dp*(Log_mu2_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-b - mu2 + T2)*phi_T2_b_mu2)/mu2)
   tmp269 = (2*(-b + t))/((1 - b/t)*t**2) -  (2*b*tmp158)/((1 - b/t)*t**2) -  &
     (2*tmp158)/((1 - b/t)*t) +  (2*b*(-b + t)*tmp158)/((1 - b/t)**2*t**3) +  &
     (2*(-b + t)*tmp158)/((1 - b/t)*t**2) +  (-2 - 2*Log_b_q)/t + (2*Log_t_q)/t
   tmp270 = -1 - (2*(-b + t)*tmp158)/((1 - b/t)*t) + &
     &2*Li2(1 - b/t) + 4*Log_b_q +  (-2 - 2*Log_b_q)*Log_t_q + Log_t_q**2
   tmp271 = 2*T1*(-1 + Log_T1_q) + 2*T1*(-1 + Log_T1_q)**2
   tmp272 = -1 - (2*(-B1 + T1)*tmp175)/((1 - B1/T1)*T1) + &
     &2*Li2(1 - B1/T1) + 4*Log_B1_q +  (-2 - 2*Log_B1_q)*Log_T1_q + Log_T1_q**2
   tmp273 = -1 - (2*(-B2 + T1)*tmp177)/((1 - B2/T1)*T1) + &
     &2*Li2(1 - B2/T1) + 4*Log_B2_q +  (-2 - 2*Log_B2_q)*Log_T1_q + Log_T1_q**2
   tmp274 = 2*T2*(-1 + Log_T2_q) + 2*T2*(-1 + Log_T2_q)**2
   tmp275 = -1 - (2*(-B1 + T2)*tmp191)/((1 - B1/T2)*T2) + &
     &2*Li2(1 - B1/T2) + 4*Log_B1_q +  (-2 - 2*Log_B1_q)*Log_T2_q + Log_T2_q**2
   tmp276 = -1 - (2*(-B2 + T2)*tmp193)/((1 - B2/T2)*T2) + &
     &2*Li2(1 - B2/T2) + 4*Log_B2_q +  (-2 - 2*Log_B2_q)*Log_T2_q + Log_T2_q**2
   tmp277 = 4*(-A0 - b + t)*tmp234 + 2*phi_A0_t_b + &
     &delt_A0_t_b*((-2*b*(-A0 - b + t)* &
     ((A0 - b)*tmp144 + t*tmp166))/(t*delt_A0_t_b**2) -  &
     (b*((A0 - b)*tmp144 + t*tmp166))/(t**2*delt_A0_t_b) +  &
     (b*tmp167)/(t*delt_A0_t_b) +  ((A0 + b - t)*tmp234)/delt_A0_t_b -  &
     (2*(A0 + b - t)*(-A0 - b + t)*phi_A0_t_b)/ &
     delt_A0_t_b**2 - phi_A0_t_b/delt_A0_t_b)
   tmp278 = 4*(-B1 - mu2 + t)*tmp251 + 2*phi_B1_t_mu2 + &
     &delt_B1_t_mu2*((-2*mu2*(-B1 - mu2 + t)* &
     ((B1 - mu2)*tmp155 + t*tmp168))/ (t*delt_B1_t_mu2**2) -  &
     (mu2*((B1 - mu2)*tmp155 + t*tmp168))/ (t**2*delt_B1_t_mu2) +  &
     (mu2*tmp169)/(t*delt_B1_t_mu2) + ((B1 + mu2 - t)*tmp251)/delt_B1_t_mu2 - &
     (2*(B1 + mu2 - t)*(-B1 - mu2 + t)*phi_B1_t_mu2)/ &
     delt_B1_t_mu2**2 - phi_B1_t_mu2/delt_B1_t_mu2)
   tmp279 = -(((B1 - mu2 - t)*tmp251)/mu2) -  ((-B1 - mu2 + t)*tmp252)/mu2 + &
     &0.5_dp*(-B1 + mu2 - t)/(B1*t) - 0.5_dp*Log_B1_q/t + &
     &0.5_dp*Log_mu2_q/B1 + 0.5_dp*Log_mu2_q/t           &
     &  - 0.5_dp*Log_t_q/B1 - 0.5_dp*(delt_B1_t_mu2*((-2*mu2*(-B1 - mu2 + t)* &
     (B1*tmp160 + (-mu2 + t)*tmp162))/ (B1*delt_B1_t_mu2**2) +  &
     (mu2*tmp163)/(B1*delt_B1_t_mu2) +  &
     ((-B1 + mu2 + t)*tmp251)/delt_B1_t_mu2 -  &
     (2*(-B1 - mu2 + t)*(-B1 + mu2 + t)*phi_B1_t_mu2)/ &
     delt_B1_t_mu2**2 + phi_B1_t_mu2/delt_B1_t_mu2))/ mu2 + phi_B1_t_mu2/mu2
   tmp280 = 4*(-B2 - mu2 + t)*tmp253 + 2*phi_B2_t_mu2 + &
     &delt_B2_t_mu2*((-2*mu2*(-B2 - mu2 + t)* &
     ((B2 - mu2)*tmp156 + t*tmp170))/ (t*delt_B2_t_mu2**2) -  &
     (mu2*((B2 - mu2)*tmp156 + t*tmp170))/ (t**2*delt_B2_t_mu2) +  &
     (mu2*tmp171)/(t*delt_B2_t_mu2) +((B2 + mu2 - t)*tmp253)/delt_B2_t_mu2 -  &
     (2*(B2 + mu2 - t)*(-B2 - mu2 + t)*phi_B2_t_mu2)/ &
     delt_B2_t_mu2**2 - phi_B2_t_mu2/delt_B2_t_mu2)
   tmp281 = 4*(-b - mu2 + T1)*tmp255 + 2*phi_T1_b_mu2 + &
     &delt_T1_b_mu2*((-2*mu2*(-b - mu2 + T1)* &
     ((b - mu2)*tmp152 + T1*tmp185))/ (T1*delt_T1_b_mu2**2) -  &
     (mu2*((b - mu2)*tmp152 + T1*tmp185))/ (T1**2*delt_T1_b_mu2) +  &
     (mu2*tmp186)/(T1*delt_T1_b_mu2) +  &
     ((b + mu2 - T1)*tmp255)/delt_T1_b_mu2 -  &
     (2*(b + mu2 - T1)*(-b - mu2 + T1)*phi_T1_b_mu2)/ &
     delt_T1_b_mu2**2 - phi_T1_b_mu2/delt_T1_b_mu2)
   tmp282 = -(((b - mu2 - T1)*tmp255)/mu2) -  ((-b - mu2 + T1)*tmp256)/mu2 + &
     &0.5_dp*(-b + mu2 - T1)/(b*T1) - 0.5_dp*Log_b_q/T1 + &
     &0.5_dp*Log_mu2_q/b + 0.5_dp*Log_mu2_q/T1           &
     &  - 0.5_dp*Log_T1_q/b - 0.5_dp*(delt_T1_b_mu2* ((-2*mu2*(b - mu2 - T1)* &
     ((b - mu2)*tmp152 + T1*tmp185))/ (T1*delt_T1_b_mu2**2) +  &
     (mu2*tmp153)/(T1*delt_T1_b_mu2) +  &
     ((b + mu2 - T1)*tmp256)/delt_T1_b_mu2 -  &
     (2*(b - mu2 - T1)*(b + mu2 - T1)*phi_T1_b_mu2)/ &
     delt_T1_b_mu2**2 + phi_T1_b_mu2/delt_T1_b_mu2))/ mu2 + phi_T1_b_mu2/mu2
   tmp283 = 4*(-b - mu2 + T2)*tmp259 + 2*phi_T2_b_mu2 + &
     &delt_T2_b_mu2*((-2*mu2*(-b - mu2 + T2)* &
     ((b - mu2)*tmp152 + T2*tmp203))/ (T2*delt_T2_b_mu2**2) -  &
     (mu2*((b - mu2)*tmp152 + T2*tmp203))/ (T2**2*delt_T2_b_mu2) +  &
     (mu2*tmp204)/(T2*delt_T2_b_mu2) +  &
     ((b + mu2 - T2)*tmp259)/delt_T2_b_mu2 -  &
     (2*(b + mu2 - T2)*(-b - mu2 + T2)*phi_T2_b_mu2)/ &
     delt_T2_b_mu2**2 - phi_T2_b_mu2/delt_T2_b_mu2)
   tmp284 = -(2.5_dp*(mu2 + t + T1)) - 2.5_dp*(mu2 + t + T2) + &
     &0.5_dp*((-mu2 - t + T1)*Log_mu2_q*Log_t_q) + &
     &0.5_dp*((-mu2 - t + T2)*Log_mu2_q*Log_t_q) + &
     &0.5_dp*((-mu2 + t - T1)*Log_mu2_q*Log_T1_q) + &
     &0.5_dp*((mu2 - t - T1)*Log_t_q*Log_T1_q) + &
     &0.5_dp*((-mu2 + t - T2)*Log_mu2_q*Log_T2_q) + &
     &0.5_dp*((mu2 - t - T2)*Log_t_q*Log_T2_q) - &
     &0.5_dp*(delt_T1_t_mu2*phi_T1_t_mu2)/mu2 + &
     &2*mu2*(-1 + Log_mu2_q) + 4*mu2*Log_mu2_q + &
     &2*mu2*(-1 + Log_mu2_q)*(-1 + Log_t_q) + 4*t*Log_t_q + &
     &sbe**2*(-10*t + t*tmp263 + 2*t*(-1 + Log_t_q) + &
     &2*t*(-1 + Log_t_q)**2 + 4*t*Log_t_q + tmp173*Log_t_q &
     ) - T1*(-1 + Log_T1_q) - &
     &T1*(-1 + Log_t_q)*(-1 + Log_T1_q)+ 2*T1*Log_T1_q - T2*(-1 + Log_T2_q) - &
     &T2*(-1 + Log_t_q)*(-1 + Log_T2_q) + 2*T2*Log_T2_q + &
     &cbe**2*(-2*A0*(-1 + Log_A0_q) + 2*t*(-1 + Log_t_q) - &
     &2*A0*(-1 + Log_A0_q)*(-1 + Log_t_q) + 2*t*(-1 + Log_t_q)**2 + &
     &2*(-(2.5_dp*(A0 + 2*t)) + 0.5_dp*((A0 - 2*t)*Log_t_q**2) - &
     &0.5_dp*(delt_A0_t_t*phi_A0_t_t)/t + 2*A0*Log_A0_q + &
     &4*t*Log_t_q - A0*Log_A0_q*Log_t_q) -  &
     (A0 - 2*t)*(-1 - 0.5_dp*(tmp236*delt_A0_t_t)/t + &
     &0.5_dp*(delt_A0_t_t*phi_A0_t_t)/t**2 -  &
     (A0*Log_A0_q)/t + 4*Log_t_q +  ((A0 - 2*t)*Log_t_q)/t - Log_t_q**2 +  &
     (2*A0*phi_A0_t_t)/t))
   tmp284 = tmp284 - 0.5_dp*(delt_T2_t_mu2*phi_T2_t_mu2)/mu2 -  &
     (-mu2 - t + T1)*(-0.5_dp - 0.5_dp*(tmp258*delt_T1_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 - t + T1)*Log_mu2_q)/t - 0.5_dp*(Log_mu2_q*Log_t_q) + &
     &0.5_dp*((mu2 - t - T1)*Log_T1_q)/t + 0.5_dp*(Log_mu2_q*Log_T1_q) - &
     &0.5_dp*(Log_t_q*Log_T1_q) + 2*Log_t_q -  &
     ((-mu2 + t - T1)*phi_T1_t_mu2)/mu2) -  &
     (-mu2 - t + T2)*(-0.5_dp - 0.5_dp*(tmp262*delt_T2_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 - t + T2)*Log_mu2_q)/t - 0.5_dp*(Log_mu2_q*Log_t_q) + &
     &0.5_dp*((mu2 - t - T2)*Log_T2_q)/t + 0.5_dp*(Log_mu2_q*Log_T2_q) - &
     &0.5_dp*(Log_t_q*Log_T2_q) + 2*Log_t_q -  &
     ((-mu2 + t - T2)*phi_T2_t_mu2)/mu2)
   D1t = -(tmp136*tmp210) - tmp135*tmp211 - tmp140*tmp212 - &
     &tmp139*tmp213 - (hb*ht*abs_mu*s2b*tmp214)/mt + &
     &ht**2*tmp284 - 0.5_dp*(tmp128*tmp227) - &
     &0.5_dp*(tmp127*tmp228)- 0.5_dp*(tmp132*tmp232)- 0.5_dp*(tmp131*tmp233)- &
     &0.25_dp*(ht**2*(cbe**2*tmp250*tmp37 + cbe**2*tmp242*tmp38 + &
     &0.5_dp*(sbe**2*tmp20* (-10*T1 + 4*T1*Log_T1_q + tmp189*Log_T1_q)) + &
     &0.5_dp*(sbe**2*tmp19* &
     (-10*T2 + 4*T2*Log_T2_q + tmp209*Log_T2_q)))) + &
     &tmp5*(0.5_dp*((b + t)*tmp223) + 0.5_dp*tmp224 + &
     &b*(-1 + Log_b_q) + b*(-1 + Log_b_q)*(-1 + Log_t_q))- &
     (2*mb*cbe*hb*ht*sbe* (2.5_dp*(A0 + b + t) + 0.5_dp*tmp224 - &
     &0.5_dp*((-A0 - b + t)*Log_A0_q*Log_b_q) - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q*Log_t_q) - &
     &0.5_dp*((A0 - b - t)*Log_b_q*Log_t_q) + &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b - 2*A0*Log_A0_q - &
     &2*b*Log_b_q - 2*t*Log_t_q))/mt - 4*mb*cbe*hb*ht*sbe*mt* &
     (0.5_dp + 0.5_dp*tmp223 + 0.5_dp*(tmp234*delt_A0_t_b)/b - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q)/t - 0.5_dp*((A0 - b - t)*Log_b_q)/t - &
     &0.5_dp*(Log_A0_q*Log_b_q) + 0.5_dp*(Log_A0_q*Log_t_q) + &
     &0.5_dp*(Log_b_q*Log_t_q) - 2*Log_t_q +  ((-A0 - b + t)*phi_A0_t_b)/b)
   D1t = D1t + tmp4* (-(2.5_dp*(A0 + b + t)) + &
     &0.5_dp*((-A0 - b + t)*Log_A0_q*Log_b_q) + &
     &0.5_dp*((-A0 + b - t)*Log_A0_q*Log_t_q) + &
     &0.5_dp*((A0 - b - t)*Log_b_q*Log_t_q) - &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b - &
     &A0*(-1 + Log_A0_q) + 2*A0*Log_A0_q + b*(-1 + Log_b_q) + 2*b*Log_b_q - &
     &A0*(-1 + Log_A0_q)*(-1 + Log_t_q) + &
     &b*(-1 + Log_b_q)*(-1 + Log_t_q) + 2*t*Log_t_q -  &
     (A0 - b - t)*(-0.5_dp - 0.5_dp*(tmp234*delt_A0_t_b)/b + &
     &0.5_dp*((-A0 + b - t)*Log_A0_q)/t + 0.5_dp*((A0 - b - t)*Log_b_q)/t + &
     &0.5_dp*(Log_A0_q*Log_b_q) - 0.5_dp*(Log_A0_q*Log_t_q) - &
     &0.5_dp*(Log_b_q*Log_t_q) + 2*Log_t_q -  &
     ((-A0 - b + t)*phi_A0_t_b)/b)) + tmp55*(-(2.5_dp*(B1 + mu2 + t)) + &
     &0.5_dp*((-B1 - mu2 + t)*Log_B1_q*Log_mu2_q) + &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q*Log_t_q) + &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q*Log_t_q) - &
     &0.5_dp*(delt_B1_t_mu2*phi_B1_t_mu2)/mu2 - &
     &B1*(-1 + Log_B1_q) + 2*B1*Log_B1_q + &
     &mu2*(-1 + Log_mu2_q) + 2*mu2*Log_mu2_q - &
     &B1*(-1 + Log_B1_q)*(-1 + Log_t_q) + &
     &mu2*(-1 + Log_mu2_q)*(-1 + Log_t_q) + 2*t*Log_t_q -  (B1 - mu2 - t)* &
     (-0.5_dp - 0.5_dp*(tmp251*delt_B1_t_mu2)/mu2 + &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t + &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t + 0.5_dp*(Log_B1_q*Log_mu2_q) - &
     &0.5_dp*(Log_B1_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_t_q) + 2*Log_t_q -  &
     ((-B1 - mu2 + t)*phi_B1_t_mu2)/mu2))
   D1t = D1t - 2*hb*ht*abs_mu*s2b*mt* &
     (-(0.5_dp*(tmp251*delt_B1_t_mu2)/mu2) + &
     &0.5_dp*(tmp253*delt_B2_t_mu2)/mu2+0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t - &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t + &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t - &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t + 0.5_dp*(Log_B1_q*Log_mu2_q) - &
     &0.5_dp*(Log_B2_q*Log_mu2_q) - &
     &0.5_dp*(Log_B1_q*Log_t_q) + 0.5_dp*(Log_B2_q*Log_t_q) -  &
     ((-B1 - mu2 + t)*phi_B1_t_mu2)/mu2 +  &
     ((-B2 - mu2 + t)*phi_B2_t_mu2)/mu2) + tmp54*(-(2.5_dp*(B2 + mu2 + t)) + &
     &0.5_dp*((-B2 - mu2 + t)*Log_B2_q*Log_mu2_q) + &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q*Log_t_q) + &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q*Log_t_q) - &
     &0.5_dp*(delt_B2_t_mu2*phi_B2_t_mu2)/mu2 - &
     &B2*(-1 + Log_B2_q) + 2*B2*Log_B2_q + &
     &mu2*(-1 + Log_mu2_q) + 2*mu2*Log_mu2_q - &
     &B2*(-1 + Log_B2_q)*(-1 + Log_t_q) + &
     &mu2*(-1 + Log_mu2_q)*(-1 + Log_t_q) + 2*t*Log_t_q -  (B2 - mu2 - t)* &
     (-0.5_dp - 0.5_dp*(tmp253*delt_B2_t_mu2)/mu2 + &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t + &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t + 0.5_dp*(Log_B2_q*Log_mu2_q) - &
     &0.5_dp*(Log_B2_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_t_q) + 2*Log_t_q -  &
     ((-B2 - mu2 + t)*phi_B2_t_mu2)/mu2))
   DT1 = tmp267*tmp56 - 0.5_dp*(tmp130*tmp225) - 0.5_dp*(tmp129*tmp226) + &
     &hb**2*(0.25_dp*(B1*(1 - c2b)*(1 + c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*(B2*(1 + c2b)*(1 + c2t)*(-1 + Log_B2_q)) + &
     &sbe**2*(0.5_dp*(A0*(1 + c2t)*(-1 + Log_A0_q)) + &
     &0.5_dp*(A0*(1 + c2t)*(-1 + Log_A0_q)*(-1 + Log_T1_q)) &
     ) + 0.25_dp*(B1*(1 - c2b)*(1 + c2t)*(-1 + Log_B1_q)* (-1 + Log_T1_q)) + &
     &0.25_dp*(B2*(1 + c2b)*(1 + c2t)*(-1 + Log_B2_q)* (-1 + Log_T1_q))) + &
     &ht**2*(0.25_dp*((1 + Nc)*s2t**2*tmp271) + &
     &0.25_dp*(B1*(1 + c2b)*(1 - c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*(B2*(1 - c2b)*(1 - c2t)*(-1 + Log_B2_q)) + &
     &0.25_dp*(B1*(1 + c2b)*(1 - c2t)*(-1 + Log_B1_q)* (-1 + Log_T1_q)) + &
     &0.25_dp*(B2*(1 - c2b)*(1 - c2t)*(-1 + Log_B2_q)* (-1 + Log_T1_q)) + &
     &cbe**2*(A0*(1 + 0.5_dp*(1 - c2t))*(-1 + Log_A0_q) + &
     &A0*(1 + 0.5_dp*(1 - c2t))*(-1 + Log_A0_q)* &
     (-1 + Log_T1_q)) + T2*tmp3*(-1 + Log_T2_q) + &
     &T2*tmp3*(-1 + Log_T1_q)*(-1 + Log_T2_q)) - &
     &tmp138*(-0.5_dp - 0.5_dp*(tmp237*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q)/T1 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B1_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B1 + T1)*phi_A0_T1_B1)/B1) - &
     &tmp137*(-0.5_dp - 0.5_dp*(tmp239*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q)/T1 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B2 + T1)*phi_A0_T1_B2)/B2)
   DT1 = DT1 - 0.25_dp* (ht**2*((1 + c2t**2)*sbe**2*tmp219*Xt**2 + &
     &0.5_dp*(sbe**2*tmp264*tmp27) + cbe**2*tmp45* &
     (-1 - 0.5_dp*(tmp241*delt_A0_T1_T1)/T1 + &
     &0.5_dp*(delt_A0_T1_T1*phi_A0_T1_T1)/T1**2 -  &
     (A0*Log_A0_q)/T1 + 4*Log_T1_q +  &
     ((A0 - 2*T1)*Log_T1_q)/T1 - Log_T1_q**2 +  &
     (2*A0*phi_A0_T1_T1)/T1) + 2*(1 + c2t**2)*cbe**2*Yt**2* &
     (-0.5_dp - 0.5_dp*(tmp243*delt_A0_T1_T2)/T2 + &
     &0.5_dp*((-A0 - T1 + T2)*Log_A0_q)/T1 - 0.5_dp*(Log_A0_q*Log_T1_q) + &
     &0.5_dp*((A0 - T1 - T2)*Log_T2_q)/T1 + 0.5_dp*(Log_A0_q*Log_T2_q) - &
     &0.5_dp*(Log_T1_q*Log_T2_q) + 2*Log_T1_q -  &
     ((-A0 + T1 - T2)*phi_A0_T1_T2)/T2))) - 2*mb*hb*ht*abs_mu*s2t* &
     (-0.5_dp - 0.5_dp*(tmp255*delt_T1_b_mu2)/mu2 + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1 + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1 + &
     &0.5_dp*(Log_b_q*Log_mu2_q) - 0.5_dp*(Log_b_q*Log_T1_q) - &
     &0.5_dp*(Log_mu2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-b - mu2 + T1)*phi_T1_b_mu2)/mu2)
   DT1 = DT1 + ht**2* (2.5_dp*(mu2 + t + T1) - &
     &0.5_dp*((-mu2 - t + T1)*Log_mu2_q*Log_t_q) - &
     &0.5_dp*((-mu2 + t - T1)*Log_mu2_q*Log_T1_q) - &
     &0.5_dp*((mu2 - t - T1)*Log_t_q*Log_T1_q) + &
     &0.5_dp*(delt_T1_t_mu2*phi_T1_t_mu2)/mu2 - &
     &mu2*(-1 + Log_mu2_q) - 2*mu2*Log_mu2_q - &
     &t*(-1 + Log_t_q) - 2*t*Log_t_q - &
     &mu2*(-1 + Log_mu2_q)*(-1 + Log_T1_q) - &
     &t*(-1 + Log_t_q)*(-1 + Log_T1_q) - 2*T1*Log_T1_q -  (-mu2 - t + T1)* &
     (-0.5_dp - 0.5_dp*(tmp257*delt_T1_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 + t - T1)*Log_mu2_q)/T1 + &
     &0.5_dp*((mu2 - t - T1)*Log_t_q)/T1 + 0.5_dp*(Log_mu2_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_T1_q) - &
     &0.5_dp*(Log_t_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-mu2 - t + T1)*phi_T1_t_mu2)/mu2))
   DT2 = tmp268*tmp57 - 0.5_dp*(tmp134*tmp230) - 0.5_dp*(tmp133*tmp231) + &
     &hb**2*(0.25_dp*(B1*(1 - c2b)*(1 - c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*(B2*(1 + c2b)*(1 - c2t)*(-1 + Log_B2_q)) + &
     &sbe**2*(0.5_dp*(A0*(1 - c2t)*(-1 + Log_A0_q)) + &
     &0.5_dp*(A0*(1 - c2t)*(-1 + Log_A0_q)*(-1 + Log_T2_q)) &
     ) + 0.25_dp*(B1*(1 - c2b)*(1 - c2t)*(-1 + Log_B1_q)* (-1 + Log_T2_q)) + &
     &0.25_dp*(B2*(1 + c2b)*(1 - c2t)*(-1 + Log_B2_q)* (-1 + Log_T2_q))) + &
     &ht**2*(0.25_dp*((1 + Nc)*s2t**2*tmp274) + &
     &0.25_dp*(B1*(1 + c2b)*(1 + c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*(B2*(1 - c2b)*(1 + c2t)*(-1 + Log_B2_q)) + &
     &0.25_dp*(B1*(1 + c2b)*(1 + c2t)*(-1 + Log_B1_q)* (-1 + Log_T2_q)) + &
     &0.25_dp*(B2*(1 - c2b)*(1 + c2t)*(-1 + Log_B2_q)* &
     (-1 + Log_T2_q)) + T1*tmp3*(-1 + Log_T1_q) + &
     &cbe**2*(A0*(1 + 0.5_dp*(1 + c2t))*(-1 + Log_A0_q) + &
     &A0*(1 + 0.5_dp*(1 + c2t))*(-1 + Log_A0_q)* (-1 + Log_T2_q)) + &
     &T1*tmp3*(-1 + Log_T1_q)*(-1 + Log_T2_q)) - &
     &tmp142*(-0.5_dp - 0.5_dp*(tmp245*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q)/T2 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B1_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B1 + T2)*phi_A0_T2_B1)/B1) - &
     &tmp141*(-0.5_dp - 0.5_dp*(tmp247*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q)/T2 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B2_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B2 + T2)*phi_A0_T2_B2)/B2)
   DT2 = DT2 - 0.25_dp* (ht**2*((1 + c2t**2)*sbe**2*tmp265*Xt**2 + &
     &0.5_dp*(sbe**2*tmp26*tmp266) + 2*(1 + c2t**2)*cbe**2*Yt**2* &
     (-0.5_dp - 0.5_dp*(tmp244*delt_A0_T1_T2)/T2 + &
     &0.5_dp*((-A0 + T1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - T1 - T2)*Log_T1_q)/T2 + 0.5_dp*(Log_A0_q*Log_T1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_T1_q*Log_T2_q) + &
     &0.5_dp*(delt_A0_T1_T2*phi_A0_T1_T2)/T2**2 + &
     &2*Log_T2_q - ((-A0 - T1 + T2)*phi_A0_T1_T2)/T2)+cbe**2*tmp44* &
     (-1 - 0.5_dp*(tmp249*delt_A0_T2_T2)/T2 + &
     &0.5_dp*(delt_A0_T2_T2*phi_A0_T2_T2)/T2**2 -  &
     (A0*Log_A0_q)/T2 + 4*Log_T2_q +  &
     ((A0 - 2*T2)*Log_T2_q)/T2 - Log_T2_q**2 +  &
     (2*A0*phi_A0_T2_T2)/T2))) - 2*mb*hb*ht*abs_mu*s2t* &
     (0.5_dp + 0.5_dp*(tmp259*delt_T2_b_mu2)/mu2 - &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2 - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2 - &
     &0.5_dp*(Log_b_q*Log_mu2_q) + 0.5_dp*(Log_b_q*Log_T2_q) + &
     &0.5_dp*(Log_mu2_q*Log_T2_q) - 2*Log_T2_q +  &
     ((-b - mu2 + T2)*phi_T2_b_mu2)/mu2)
   DT2 = DT2 + ht**2* (2.5_dp*(mu2 + t + T2) - &
     &0.5_dp*((-mu2 - t + T2)*Log_mu2_q*Log_t_q) - &
     &0.5_dp*((-mu2 + t - T2)*Log_mu2_q*Log_T2_q) - &
     &0.5_dp*((mu2 - t - T2)*Log_t_q*Log_T2_q) + &
     &0.5_dp*(delt_T2_t_mu2*phi_T2_t_mu2)/mu2 - &
     &mu2*(-1 + Log_mu2_q) - 2*mu2*Log_mu2_q - &
     &t*(-1 + Log_t_q) - 2*t*Log_t_q - &
     &mu2*(-1 + Log_mu2_q)*(-1 + Log_T2_q) - &
     &t*(-1 + Log_t_q)*(-1 + Log_T2_q) - 2*T2*Log_T2_q -  (-mu2 - t + T2)* &
     (-0.5_dp - 0.5_dp*(tmp261*delt_T2_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 + t - T2)*Log_mu2_q)/T2 + &
     &0.5_dp*((mu2 - t - T2)*Log_t_q)/T2 + 0.5_dp*(Log_mu2_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_T2_q) - &
     &0.5_dp*(Log_t_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-mu2 - t + T2)*phi_T2_t_mu2)/mu2))
   Dc2t = -(tmp124*tmp210) - tmp123*tmp211 - tmp126*tmp212 - tmp125*tmp213 +  &
     (mb*hb*ht*abs_mu*tmp217)/s2t + tmp1*tmp220 + &
     &tmp2*tmp221 - 0.5_dp*(tmp120*tmp227) - 0.5_dp*(tmp119*tmp228) - &
     &0.5_dp*(tmp122*tmp232) - 0.5_dp*(tmp121*tmp233) + &
     &hb**2*(0.125_dp*(B1*(1 - c2b)*T1*(-1 + Log_B1_q)* &
     (-1 + Log_T1_q))/c2t + 0.125_dp*(B2*(1 + c2b)*T1*(-1 + Log_B2_q)* &
     (-1 + Log_T1_q))/c2t + &
     &sbe**2*(0.25_dp*(A0*T1*(-1 + Log_A0_q)*(-1 + Log_T1_q))/ &
     c2t - 0.25_dp* (A0*T2*(-1 + Log_A0_q)*(-1 + Log_T2_q))/c2t) - &
     &0.125_dp*(B1*(1 - c2b)*T2*(-1 + Log_B1_q)* (-1 + Log_T2_q))/c2t - &
     &0.125_dp*(B2*(1 + c2b)*T2*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2t) + &
     &ht**2*(-(0.125_dp*(B1*(1 + c2b)*T1*(-1 + Log_B1_q)* &
     (-1 + Log_T1_q))/c2t) - 0.125_dp*(B2*(1 - c2b)*T1*(-1 + Log_B2_q)* &
     (-1 + Log_T1_q))/c2t - 0.25_dp*((1 + Nc)* (T1**2*(-1 + Log_T1_q)**2 + &
     &T2**2*(-1 + Log_T2_q)**2)) + cbe**2*(-(0.25_dp* &
     (A0*T1*(-1 + Log_A0_q)*(-1 + Log_T1_q))/c2t) + &
     &0.25_dp*(A0*T2*(-1 + Log_A0_q)*(-1 + Log_T2_q))/c2t)+&
     &0.125_dp*(B1*(1 + c2b)*T2*(-1 + Log_B1_q)* (-1 + Log_T2_q))/c2t + &
     &0.125_dp*(B2*(1 - c2b)*T2*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2t + &
     &T1*T2*(1 + 0.5_dp*(-1 + Nc))*(-1 + Log_T1_q)* (-1 + Log_T2_q))
   Dc2t = Dc2t - 0.25_dp* (ht**2*(cbe**2*tmp242*tmp40 + cbe**2*tmp250*tmp41 + &
     &0.5_dp*(sbe**2*tmp22* (-10*T1 + 4*T1*Log_T1_q + tmp189*Log_T1_q)) + &
     &0.5_dp*(sbe**2*tmp23* (-10*T2 + 4*T2*Log_T2_q + tmp209*Log_T2_q)) + &
     &2*cbe**2*Yt**2* (-(2.5_dp*(A0 + T1 + T2)) + &
     &0.5_dp*((-A0 - T1 + T2)*Log_A0_q*Log_T1_q) + &
     &0.5_dp*((-A0 + T1 - T2)*Log_A0_q*Log_T2_q) + &
     &0.5_dp*((A0 - T1 - T2)*Log_T1_q*Log_T2_q) - &
     &0.5_dp*(delt_A0_T1_T2*phi_A0_T1_T2)/T2 + &
     &2*A0*Log_A0_q + 2*T1*Log_T1_q + 2*T2*Log_T2_q) +sbe**2*Xt**2* &
     (-5*T1 - 5*T2 - 2*(T1 - T2)*Li2(1 - T2/T1) + &
     &tmp208*Log_T1_q + (-T1 + T2)*Log_T1_q**2 + 4*T2*Log_T2_q)))
   DT1T1 = hb**2*(0.5_dp* (A0*(1 + c2t)*sbe**2*(-1 + Log_A0_q))/T1 + &
     &0.25_dp*(B1*(1 - c2b)*(1 + c2t)*(-1 + Log_B1_q))/T1 + &
     &0.25_dp*(B2*(1 + c2b)*(1 + c2t)*(-1 + Log_B2_q))/T1) - &
     &0.5_dp*(tmp130*(8/T1 - tmp147/T1**2 +  &
     (4*B1*tmp175)/((1 - B1/T1)*T1**2) - 2*(-B1 + T1)* &
     (B1/((1 - B1/T1)*T1**3) +  (B1**2*tmp175)/((1 - B1/T1)**2*T1**4) +  &
     (2*B1*tmp175)/((1 - B1/T1)*T1**3)) +  &
     (B1 - T1)*tmp188 - (4*Log_T1_q)/T1))-0.5_dp*(tmp129*(8/T1-tmp150/T1**2+  &
     (4*B2*tmp177)/((1 - B2/T1)*T1**2) - 2*(-B2 + T1)* &
     (B2/((1 - B2/T1)*T1**3) +  (B2**2*tmp177)/((1 - B2/T1)**2*T1**4) +  &
     (2*B2*tmp177)/((1 - B2/T1)*T1**3)) +  &
     (B2 - T1)*tmp188 - (4*Log_T1_q)/T1)) - 2*mb*hb*ht*abs_mu*s2t* &
     (2/T1 - 0.5_dp*tmp281/mu2 - 0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1**2 - &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1**2 - Log_b_q/T1 - Log_mu2_q/T1) + &
     &ht**2*(0.25_dp*(B1*(1 + c2b)*(1 - c2t)*(-1 + Log_B1_q))/ &
     T1 + 0.25_dp*(B2*(1 - c2b)*(1 - c2t)*(-1 + Log_B2_q))/ &
     T1 + 0.25_dp*((1 + Nc)*s2t**2* &
     (T1**2*(2/T1**2 - (2*(-1 + Log_T1_q))/T1**2) + &
     &8*(-1 + Log_T1_q) + 2*(-1 + Log_T1_q)**2)) +  &
     (A0*cbe**2*(1 + 0.5_dp*(1 - c2t))*(-1 + Log_A0_q))/T1 +  &
     (T2*tmp3*(-1 + Log_T2_q))/T1)
   DT1T1 = DT1T1 - tmp138* (2/T1 - 0.5_dp*((-A0 + B1 - T1)*Log_A0_q)/T1**2 - &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q)/T1**2 - &
     &0.5_dp*(4*(-A0 - B1 + T1)*tmp237 + 2*phi_A0_T1_B1 + delt_A0_T1_B1* &
     ((-2*B1*(-A0 - B1 + T1)* ((A0 - B1)*tmp146 + T1*tmp183))/ &
     (T1*delt_A0_T1_B1**2) -  (B1*((A0 - B1)*tmp146 + T1*tmp183))/ &
     (T1**2*delt_A0_T1_B1) +  ((A0 + B1 - T1)*tmp237)/delt_A0_T1_B1 +  &
     (B1*(2 - Log_A0_q - Log_B1_q + 2*Log_T1_q))/ &
     (T1*delt_A0_T1_B1) -  (2*(A0 + B1 - T1)*(-A0 - B1 + T1)*&
     &phi_A0_T1_B1)/delt_A0_T1_B1**2 - &
     &phi_A0_T1_B1/delt_A0_T1_B1))/B1 - Log_A0_q/T1 - Log_B1_q/T1) - &
     &tmp137*(2/T1 - 0.5_dp*((-A0 + B2 - T1)*Log_A0_q)/T1**2 - &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q)/T1**2 - &
     &0.5_dp*(4*(-A0 - B2 + T1)*tmp239 + 2*phi_A0_T1_B2 + delt_A0_T1_B2* &
     ((-2*B2*(-A0 - B2 + T1)* ((A0 - B2)*tmp149 + T1*tmp184))/ &
     (T1*delt_A0_T1_B2**2) -  (B2*((A0 - B2)*tmp149 + T1*tmp184))/ &
     (T1**2*delt_A0_T1_B2) +  ((A0 + B2 - T1)*tmp239)/delt_A0_T1_B2 +  &
     (B2*(2 - Log_A0_q - Log_B2_q + 2*Log_T1_q))/ &
     (T1*delt_A0_T1_B2) -  (2*(A0 + B2 - T1)*(-A0 - B2 + T1)*&
     &phi_A0_T1_B2)/delt_A0_T1_B2**2 - &
     &phi_A0_T1_B2/delt_A0_T1_B2))/B2 - Log_A0_q/T1 - Log_B2_q/T1)
   DT1T1 = DT1T1 - 0.25_dp* (ht**2*(0.5_dp*(sbe**2*tmp27* &
     (4/T1 - tmp189/T1**2 + (2*(2 - 2*Log_T1_q))/T1 -  &
     (2*Log_T1_q)/T1)) +  (1 + c2t**2)*sbe**2*Xt**2* &
     (8/T1 + (-T1 + T2)*tmp188 +  (4*T2*tmp200)/(T1**2*(1 - T2/T1)) - &
     &2*(T1 - T2)* (T2/(T1**3*(1 - T2/T1)) +  &
     (T2**2*tmp200)/(T1**4*(1 - T2/T1)**2) +  &
     (2*T2*tmp200)/(T1**3*(1 - T2/T1))) - &
     &tmp208/T1**2 - (4*Log_T1_q)/T1) + 2*(1 + c2t**2)*cbe**2*Yt**2* &
     (2/T1 - 0.5_dp*((-A0 - T1 + T2)*Log_A0_q)/T1**2 - &
     &0.5_dp*((A0 - T1 - T2)*Log_T2_q)/T1**2 - &
     &0.5_dp*(4*(-A0 + T1 - T2)*tmp243 + 2*phi_A0_T1_T2 + &
     &delt_A0_T1_T2* ((-2*(-A0 + T1 - T2)*T2* &
     (T1*tmp198 + (A0 - T2)*tmp199))/ (T1*delt_A0_T1_T2**2) -  &
     (T2*(T1*tmp198 + (A0 - T2)*tmp199))/ (T1**2*delt_A0_T1_T2) +  &
     ((A0 - T1 + T2)*tmp243)/delt_A0_T1_T2 +  (T2* &
     (2 - Log_A0_q + 2*Log_T1_q - &
     &Log_T2_q))/(T1*delt_A0_T1_T2) -  &
     (2*(-A0 + T1 - T2)*(A0 - T1 + T2)*&
     &phi_A0_T1_T2)/delt_A0_T1_T2**2 - &
     &phi_A0_T1_T2/delt_A0_T1_T2))/T2 - Log_A0_q/T1 - Log_T2_q/T1) + &
     &cbe**2*tmp45* (4/T1 + 0.5_dp*((A0 - 2*T1)*tmp188) - &
     &0.5_dp*(-8*A0*tmp241 + delt_A0_T1_T1* &
     ((4*A0*((-A0 + T1)*tmp174 + T1*tmp182))/ delt_A0_T1_T1**2 +  &
     (4*A0*((A0 - T1)*tmp182 + T1*tmp182))/ delt_A0_T1_T1**2 +  &
     (1 + (A0 - T1)/T1)/delt_A0_T1_T1 +  &
     (1 - (-A0 + T1)/T1)/delt_A0_T1_T1 +  &
     (A0*tmp241)/delt_A0_T1_T1 +  (tmp114*tmp241)/delt_A0_T1_T1 +  &
     (4*A0**2*phi_A0_T1_T1)/ delt_A0_T1_T1**2 +  &
     (4*A0*tmp114*phi_A0_T1_T1)/ delt_A0_T1_T1**2 +  &
     ((-1 - (A0 - T1)**2/T1**2 -  &
     (2*(A0 - T1))/T1)*phi_A0_T1_T1)/ delt_A0_T1_T1))/T1 +  &
     (A0*Log_A0_q)/T1**2 - (4*Log_T1_q)/T1 -  &
     (delt_A0_T1_T1*phi_A0_T1_T1)/T1**3 +  &
     (tmp241*delt_A0_T1_T1 - 4*A0*phi_A0_T1_T1)/T1**2 )))
   DT1T1 = DT1T1 + tmp56* (-((b*(-1 + Log_b_q))/T1) -  &
     (mu2*(-1 + Log_mu2_q))/T1 - (-b - mu2 + T1)* (2/T1 - 0.5_dp*tmp281/mu2 - &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1**2 - &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1**2 - &
     &Log_b_q/T1 - Log_mu2_q/T1) + &
     &2*(0.5_dp + 0.5_dp*(tmp255*delt_T1_b_mu2)/mu2 - &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1 - &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1 - 0.5_dp*(Log_b_q*Log_mu2_q) + &
     &0.5_dp*(Log_b_q*Log_T1_q) + &
     &0.5_dp*(Log_mu2_q*Log_T1_q) - 2*Log_T1_q +  &
     ((-b - mu2 + T1)*phi_T1_b_mu2)/mu2)) + &
     &ht**2*(-((mu2*(-1 + Log_mu2_q))/T1) -  (t*(-1 + Log_t_q))/T1 -  &
     (-mu2 - t + T1)* (2/T1 - 0.5_dp*((-mu2 + t - T1)*Log_mu2_q)/T1**2 - &
     &0.5_dp*((mu2 - t - T1)*Log_t_q)/T1**2 - &
     &0.5_dp*(4*(-mu2 - t + T1)*tmp257 + 2*phi_T1_t_mu2 + delt_T1_t_mu2* &
     ((-2*mu2*(-mu2 - t + T1)* ((-mu2 + t)*tmp162 + T1*tmp187))/ &
     (T1*delt_T1_t_mu2**2) -  (mu2*((-mu2 + t)*tmp162 + T1*tmp187))/ &
     (T1**2*delt_T1_t_mu2) +  &
     ((mu2 + t - T1)*tmp257)/delt_T1_t_mu2 +  (mu2* &
     (2 - Log_mu2_q - Log_t_q + 2*Log_T1_q)) &
     /(T1*delt_T1_t_mu2) -  (2*(mu2 + t - T1)*(-mu2 - t + T1)*&
     &phi_T1_t_mu2)/delt_T1_t_mu2**2 - &
     &phi_T1_t_mu2/delt_T1_t_mu2))/mu2 - Log_mu2_q/T1 - Log_t_q/T1) + &
     &2*(0.5_dp + 0.5_dp*(tmp257*delt_T1_t_mu2)/mu2 - &
     &0.5_dp*((-mu2 + t - T1)*Log_mu2_q)/T1 - &
     &0.5_dp*((mu2 - t - T1)*Log_t_q)/T1 - 0.5_dp*(Log_mu2_q*Log_t_q) + &
     &0.5_dp*(Log_mu2_q*Log_T1_q) + &
     &0.5_dp*(Log_t_q*Log_T1_q) - 2*Log_T1_q +  &
     ((-mu2 - t + T1)*phi_T1_t_mu2)/mu2))
   DT2T2 = hb**2*(0.5_dp* (A0*(1 - c2t)*sbe**2*(-1 + Log_A0_q))/T2 + &
     &0.25_dp*(B1*(1 - c2b)*(1 - c2t)*(-1 + Log_B1_q))/T2 + &
     &0.25_dp*(B2*(1 + c2b)*(1 - c2t)*(-1 + Log_B2_q))/T2) - &
     &0.5_dp*(tmp134*(8/T2 - tmp148/T2**2 +  &
     (4*B1*tmp191)/((1 - B1/T2)*T2**2) - 2*(-B1 + T2)* &
     (B1/((1 - B1/T2)*T2**3) +  (B1**2*tmp191)/((1 - B1/T2)**2*T2**4) +  &
     (2*B1*tmp191)/((1 - B1/T2)*T2**3)) +  &
     (B1 - T2)*tmp207 -(4*Log_T2_q)/T2)) -0.5_dp*(tmp133*(8/T2-tmp151/T2**2 + &
     (4*B2*tmp193)/((1 - B2/T2)*T2**2) - 2*(-B2 + T2)* &
     (B2/((1 - B2/T2)*T2**3) +  (B2**2*tmp193)/((1 - B2/T2)**2*T2**4) +  &
     (2*B2*tmp193)/((1 - B2/T2)*T2**3)) +  &
     (B2 - T2)*tmp207 - (4*Log_T2_q)/T2)) - 2*mb*hb*ht*abs_mu*s2t* &
     (-2/T2 + 0.5_dp*tmp283/mu2 + 0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2**2 + &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2**2 + Log_b_q/T2 + Log_mu2_q/T2) + &
     &ht**2*(0.25_dp*(B1*(1 + c2b)*(1 + c2t)*(-1 + Log_B1_q))/ &
     T2 + 0.25_dp*(B2*(1 - c2b)*(1 + c2t)*(-1 + Log_B2_q))/ &
     T2 + 0.25_dp*((1 + Nc)*s2t**2* &
     (T2**2*(2/T2**2 - (2*(-1 + Log_T2_q))/T2**2) + &
     &8*(-1 + Log_T2_q) + 2*(-1 + Log_T2_q)**2)) +  &
     (A0*cbe**2*(1 + 0.5_dp*(1 + c2t))*(-1 + Log_A0_q))/T2 +  &
     (T1*tmp3*(-1 + Log_T1_q))/T2)
   DT2T2 = DT2T2 - tmp142* (2/T2 - 0.5_dp*((-A0 + B1 - T2)*Log_A0_q)/T2**2 - &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q)/T2**2 - &
     &0.5_dp*(4*(-A0 - B1 + T2)*tmp245 + 2*phi_A0_T2_B1 + delt_A0_T2_B1* &
     ((-2*B1*(-A0 - B1 + T2)* ((A0 - B1)*tmp146 + T2*tmp201))/ &
     (T2*delt_A0_T2_B1**2) -  (B1*((A0 - B1)*tmp146 + T2*tmp201))/ &
     (T2**2*delt_A0_T2_B1) +  ((A0 + B1 - T2)*tmp245)/delt_A0_T2_B1 +  &
     (B1*(2 - Log_A0_q - Log_B1_q + 2*Log_T2_q))/ &
     (T2*delt_A0_T2_B1) -  (2*(A0 + B1 - T2)*(-A0 - B1 + T2)*&
     &phi_A0_T2_B1)/delt_A0_T2_B1**2 - &
     &phi_A0_T2_B1/delt_A0_T2_B1))/B1 - Log_A0_q/T2 - Log_B1_q/T2) - &
     &tmp141*(2/T2 - 0.5_dp*((-A0 + B2 - T2)*Log_A0_q)/T2**2 - &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q)/T2**2 - &
     &0.5_dp*(4*(-A0 - B2 + T2)*tmp247 + 2*phi_A0_T2_B2 + delt_A0_T2_B2* &
     ((-2*B2*(-A0 - B2 + T2)* ((A0 - B2)*tmp149 + T2*tmp202))/ &
     (T2*delt_A0_T2_B2**2) -  (B2*((A0 - B2)*tmp149 + T2*tmp202))/ &
     (T2**2*delt_A0_T2_B2) +  ((A0 + B2 - T2)*tmp247)/delt_A0_T2_B2 +  &
     (B2*(2 - Log_A0_q - Log_B2_q + 2*Log_T2_q))/ &
     (T2*delt_A0_T2_B2) -  (2*(A0 + B2 - T2)*(-A0 - B2 + T2)*&
     &phi_A0_T2_B2)/delt_A0_T2_B2**2 - &
     &phi_A0_T2_B2/delt_A0_T2_B2))/B2 - Log_A0_q/T2 - Log_B2_q/T2)
   DT2T2 = DT2T2 - 0.25_dp* (ht**2*(0.5_dp*(sbe**2*tmp26* &
     (4/T2 - tmp209/T2**2 + (2*(2 - 2*Log_T2_q))/T2 -  &
     (2*Log_T2_q)/T2)) +  (1 + c2t**2)*sbe**2*Xt**2* &
     (4/T2 + (4*tmp200)/(T1*(1 - T2/T1)) - 2*(T1 - T2)* &
     (1/(T1*T2*(1 - T2/T1)) + tmp200/(T1**2*(1 - T2/T1)**2)) -  &
     (2*Log_T1_q)/T2) + 2*(1 + c2t**2)*cbe**2*Yt**2* &
     (2/T2 - 0.5_dp*((-A0 + T1 - T2)*Log_A0_q)/T2**2 - &
     &0.5_dp*((A0 - T1 - T2)*Log_T1_q)/T2**2 - &
     &0.5_dp*(4*(-A0 - T1 + T2)*tmp244 + 2*phi_A0_T1_T2 + &
     &delt_A0_T1_T2* ((-2*(-A0 - T1 + T2)* &
     ((-A0 + T1)*tmp174 + T2*tmp206))/ delt_A0_T1_T2**2 +  &
     (tmp115*tmp244)/delt_A0_T1_T2 +  &
     (2 - Log_A0_q - Log_T1_q + 2*Log_T2_q)/ delt_A0_T1_T2 -  &
     (2*(-A0 - T1 + T2)*tmp115*phi_A0_T1_T2)/ delt_A0_T1_T2**2 -  &
     ((A0 - T1)**2*phi_A0_T1_T2)/ (T2**2*delt_A0_T1_T2)))/T2 - &
     &Log_A0_q/T2 - Log_T1_q/T2 -  (delt_A0_T1_T2*phi_A0_T1_T2)/T2**3 +  &
     (tmp244*delt_A0_T1_T2 + 2*(-A0 - T1 + T2)*phi_A0_T1_T2)/T2**2) + &
     &cbe**2*tmp44* (4/T2 + 0.5_dp*((A0 - 2*T2)*tmp207) - &
     &0.5_dp*(-8*A0*tmp249 + delt_A0_T2_T2* &
     ((4*A0*((-A0 + T2)*tmp190 + T2*tmp199))/ delt_A0_T2_T2**2 +  &
     (4*A0*((A0 - T2)*tmp199 + T2*tmp199))/ delt_A0_T2_T2**2 +  &
     (1 + (A0 - T2)/T2)/delt_A0_T2_T2 +  &
     (1 - (-A0 + T2)/T2)/delt_A0_T2_T2 +  &
     (A0*tmp249)/delt_A0_T2_T2 +  (tmp118*tmp249)/delt_A0_T2_T2 +  &
     (4*A0**2*phi_A0_T2_T2)/ delt_A0_T2_T2**2 +  &
     (4*A0*tmp118*phi_A0_T2_T2)/ delt_A0_T2_T2**2 +  &
     ((-1 - (A0 - T2)**2/T2**2 -  &
     (2*(A0 - T2))/T2)*phi_A0_T2_T2)/ delt_A0_T2_T2))/T2 +  &
     (A0*Log_A0_q)/T2**2 - (4*Log_T2_q)/T2 -  &
     (delt_A0_T2_T2*phi_A0_T2_T2)/T2**3 +  &
     (tmp249*delt_A0_T2_T2 - 4*A0*phi_A0_T2_T2)/T2**2 )))
   DT2T2 = DT2T2 + tmp57* (-((b*(-1 + Log_b_q))/T2) -  &
     (mu2*(-1 + Log_mu2_q))/T2 - (-b - mu2 + T2)* (2/T2 - 0.5_dp*tmp283/mu2 - &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2**2 - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2**2 - &
     &Log_b_q/T2 - Log_mu2_q/T2) + &
     &2*(0.5_dp + 0.5_dp*(tmp259*delt_T2_b_mu2)/mu2 - &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2 - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2 - 0.5_dp*(Log_b_q*Log_mu2_q) + &
     &0.5_dp*(Log_b_q*Log_T2_q) + &
     &0.5_dp*(Log_mu2_q*Log_T2_q) - 2*Log_T2_q +  &
     ((-b - mu2 + T2)*phi_T2_b_mu2)/mu2)) + &
     &ht**2*(-((mu2*(-1 + Log_mu2_q))/T2) -  (t*(-1 + Log_t_q))/T2 -  &
     (-mu2 - t + T2)* (2/T2 - 0.5_dp*((-mu2 + t - T2)*Log_mu2_q)/T2**2 - &
     &0.5_dp*((mu2 - t - T2)*Log_t_q)/T2**2 - &
     &0.5_dp*(4*(-mu2 - t + T2)*tmp261 + 2*phi_T2_t_mu2 + delt_T2_t_mu2* &
     ((-2*mu2*(-mu2 - t + T2)* ((-mu2 + t)*tmp162 + T2*tmp205))/ &
     (T2*delt_T2_t_mu2**2) -  (mu2*((-mu2 + t)*tmp162 + T2*tmp205))/ &
     (T2**2*delt_T2_t_mu2) +  &
     ((mu2 + t - T2)*tmp261)/delt_T2_t_mu2 +  (mu2* &
     (2 - Log_mu2_q - Log_t_q + 2*Log_T2_q)) &
     /(T2*delt_T2_t_mu2) -  (2*(mu2 + t - T2)*(-mu2 - t + T2)*&
     &phi_T2_t_mu2)/delt_T2_t_mu2**2 - &
     &phi_T2_t_mu2/delt_T2_t_mu2))/mu2 - Log_mu2_q/T2 - Log_t_q/T2) + &
     &2*(0.5_dp + 0.5_dp*(tmp261*delt_T2_t_mu2)/mu2 - &
     &0.5_dp*((-mu2 + t - T2)*Log_mu2_q)/T2 - &
     &0.5_dp*((mu2 - t - T2)*Log_t_q)/T2 - 0.5_dp*(Log_mu2_q*Log_t_q) + &
     &0.5_dp*(Log_mu2_q*Log_T2_q) + &
     &0.5_dp*(Log_t_q*Log_T2_q) - 2*Log_T2_q +  &
     ((-mu2 - t + T2)*phi_T2_t_mu2)/mu2))
   tmp285 = (2*mu2*(-1 + Log_mu2_q))/t + &
     &sbe**2*(t**2*tmp222 + 2*tmp263 + 8*(-1 + Log_t_q) + &
     &2*(-1 + Log_t_q)**2 + t*(4/t - tmp173/t**2 + (2*(2 - 2*Log_t_q))/t -  &
     (2*Log_t_q)/t)) - (T1*(-1 + Log_T1_q))/t -  (T2*(-1 + Log_T2_q))/t + &
     &cbe**2*(t**2*tmp222 - (2*A0*(-1 + Log_A0_q))/t + &
     &8*(-1 + Log_t_q) + 2*(-1 + Log_t_q)**2 + &
     &4*(-1 - 0.5_dp*(tmp236*delt_A0_t_t)/t + &
     &0.5_dp*(delt_A0_t_t*phi_A0_t_t)/t**2 -  &
     (A0*Log_A0_q)/t + 4*Log_t_q +  ((A0 - 2*t)*Log_t_q)/t - Log_t_q**2 +  &
     (2*A0*phi_A0_t_t)/t) -  (A0 - 2*t)*(4/t + 0.5_dp*((A0 - 2*t)*tmp172) - &
     &0.5_dp*(-8*A0*tmp236 + delt_A0_t_t* &
     ((4*A0*((-A0 + t)*tmp157 + t*tmp165))/ delt_A0_t_t**2 +  &
     (4*A0*((A0 - t)*tmp165 + t*tmp165))/ delt_A0_t_t**2 +  &
     (1 + (A0 - t)/t)/delt_A0_t_t +  (1 - (-A0 + t)/t)/delt_A0_t_t +  &
     (A0*tmp236)/delt_A0_t_t +  (tmp111*tmp236)/delt_A0_t_t +  &
     (4*A0**2*phi_A0_t_t)/delt_A0_t_t**2 +  &
     (4*A0*tmp111*phi_A0_t_t)/delt_A0_t_t**2 +  &
     ((-1 - (A0 - t)**2/t**2 - (2*(A0 - t))/t)*&
     &phi_A0_t_t)/delt_A0_t_t))/t +  (A0*Log_A0_q)/t**2 - (4*Log_t_q)/t -  &
     (delt_A0_t_t*phi_A0_t_t)/t**3 +  &
     (tmp236*delt_A0_t_t - 4*A0*phi_A0_t_t)/t**2)) + &
     &2*(-0.5_dp - 0.5_dp*(tmp258*delt_T1_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 - t + T1)*Log_mu2_q)/t - 0.5_dp*(Log_mu2_q*Log_t_q) + &
     &0.5_dp*((mu2 - t - T1)*Log_T1_q)/t + 0.5_dp*(Log_mu2_q*Log_T1_q) - &
     &0.5_dp*(Log_t_q*Log_T1_q) + 2*Log_t_q -  &
     ((-mu2 + t - T1)*phi_T1_t_mu2)/mu2)
   tmp285 = tmp285 -  (-mu2 - t + T1)*(2/t - &
     &0.5_dp*((-mu2 - t + T1)*Log_mu2_q)/t**2 - &
     &0.5_dp*((mu2 - t - T1)*Log_T1_q)/t**2 - &
     &0.5_dp*(4*(-mu2 + t - T1)*tmp258 + 2*phi_T1_t_mu2 + delt_T1_t_mu2* &
     ((-2*mu2*(-mu2 + t - T1)* ((-mu2 + T1)*tmp180 + t*tmp181))/ &
     (t*delt_T1_t_mu2**2) -  (mu2*((-mu2 + T1)*tmp180 + t*tmp181))/ &
     (t**2*delt_T1_t_mu2) +  ((mu2 - t + T1)*tmp258)/delt_T1_t_mu2 +  &
     (mu2*(2 - Log_mu2_q + 2*Log_t_q - Log_T1_q))/ &
     (t*delt_T1_t_mu2) -  (2*(-mu2 + t - T1)*(mu2 - t + T1)*&
     &phi_T1_t_mu2)/delt_T1_t_mu2**2 - &
     &phi_T1_t_mu2/delt_T1_t_mu2))/mu2 - Log_mu2_q/t - Log_T1_q/t) -  &
     (-mu2 - t + T2)*(2/t - 0.5_dp*((-mu2 - t + T2)*Log_mu2_q)/t**2 - &
     &0.5_dp*((mu2 - t - T2)*Log_T2_q)/t**2 - &
     &0.5_dp*(4*(-mu2 + t - T2)*tmp262 + 2*phi_T2_t_mu2 + delt_T2_t_mu2* &
     ((-2*mu2*(-mu2 + t - T2)* ((-mu2 + T2)*tmp196 + t*tmp197))/ &
     (t*delt_T2_t_mu2**2) -  (mu2*((-mu2 + T2)*tmp196 + t*tmp197))/ &
     (t**2*delt_T2_t_mu2) +  ((mu2 - t + T2)*tmp262)/delt_T2_t_mu2 +  &
     (mu2*(2 - Log_mu2_q + 2*Log_t_q - Log_T2_q))/ &
     (t*delt_T2_t_mu2) -  (2*(-mu2 + t - T2)*(mu2 - t + T2)*&
     &phi_T2_t_mu2)/delt_T2_t_mu2**2 - &
     &phi_T2_t_mu2/delt_T2_t_mu2))/mu2 - Log_mu2_q/t - Log_T2_q/t) + &
     &2*(-0.5_dp - 0.5_dp*(tmp262*delt_T2_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 - t + T2)*Log_mu2_q)/t - 0.5_dp*(Log_mu2_q*Log_t_q) + &
     &0.5_dp*((mu2 - t - T2)*Log_T2_q)/t + 0.5_dp*(Log_mu2_q*Log_T2_q) - &
     &0.5_dp*(Log_t_q*Log_T2_q) + 2*Log_t_q -  &
     ((-mu2 + t - T2)*phi_T2_t_mu2)/mu2)
   Dtt = ht**2*tmp285 + tmp211*(-(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp50)/t**1.5_dp) + 0.25_dp*(s2b*tmp97)/t**1.5_dp)) - &
     &hb**2*sbe**2*(0.125_dp*(mb*s2b*s2t)/t**1.5_dp - &
     &0.125_dp*((1 + c2b)*s2t*Yb)/t**1.5_dp) - &
     &cbe**2*ht**2*(0.125_dp*(mb*s2b*s2t)/t**1.5_dp - &
     &0.125_dp*((1 - c2b)*s2t*Yt)/t**1.5_dp))+ 0.5_dp*(tmp228*(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp50)/t**1.5_dp) + 0.25_dp*(s2b*tmp71)/t**1.5_dp) - &
     &cbe**2*hb**2* (0.125_dp*(mb*s2b*s2t)/t**1.5_dp - &
     &0.125_dp*((1 + c2b)*s2t*Xb)/t**1.5_dp) - ht**2*sbe**2* &
     (0.125_dp*(mb*s2b*s2t)/t**1.5_dp - &
     &0.125_dp*((1 - c2b)*s2t*Xt)/t**1.5_dp)))+0.5_dp*(tmp233*(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp53)/t**1.5_dp) + 0.25_dp*(s2b*tmp72)/t**1.5_dp) - &
     &cbe**2*hb**2* (-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) + &
     &0.125_dp*((1 + c2b)*s2t*Xb)/t**1.5_dp) - ht**2*sbe**2* &
     (-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) + &
     &0.125_dp*((1 - c2b)*s2t*Xt)/t**1.5_dp)))+0.5_dp*(tmp227*(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp53)/t**1.5_dp) - 0.25_dp*(s2b*tmp71)/t**1.5_dp) - &
     &cbe**2*hb**2* (-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) - &
     &0.125_dp*((1 - c2b)*s2t*Xb)/t**1.5_dp) - ht**2*sbe**2* &
     (-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) - &
     &0.125_dp*((1 + c2b)*s2t*Xt)/t**1.5_dp)))+0.5_dp*(tmp232*(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp50)/t**1.5_dp) - 0.25_dp*(s2b*tmp72)/t**1.5_dp) - &
     &cbe**2*hb**2* (0.125_dp*(mb*s2b*s2t)/t**1.5_dp + &
     &0.125_dp*((1 - c2b)*s2t*Xb)/t**1.5_dp) - ht**2*sbe**2* &
     (0.125_dp*(mb*s2b*s2t)/t**1.5_dp + &
     &0.125_dp*((1 + c2b)*s2t*Xt)/t**1.5_dp)))
   Dtt = Dtt + tmp213* (-(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp53)/t**1.5_dp) + 0.25_dp*(s2b*tmp98)/t**1.5_dp)) - &
     &hb**2*sbe**2*(-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) + &
     &0.125_dp*((1 + c2b)*s2t*Yb)/t**1.5_dp) - &
     &cbe**2*ht**2*(-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) + &
     &0.125_dp*((1 - c2b)*s2t*Yt)/t**1.5_dp)) + tmp210*(-(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp53)/t**1.5_dp) - 0.25_dp*(s2b*tmp97)/t**1.5_dp)) - &
     &hb**2*sbe**2*(-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) - &
     &0.125_dp*((1 - c2b)*s2t*Yb)/t**1.5_dp) - &
     &cbe**2*ht**2*(-(0.125_dp*(mb*s2b*s2t)/t**1.5_dp) - &
     &0.125_dp*((1 + c2b)*s2t*Yt)/t**1.5_dp)) + tmp212*(-(cbe*hb*ht*sbe* &
     (-(0.5_dp*(mb*tmp50)/t**1.5_dp) - 0.25_dp*(s2b*tmp98)/t**1.5_dp)) - &
     &hb**2*sbe**2*(0.125_dp*(mb*s2b*s2t)/t**1.5_dp + &
     &0.125_dp*((1 - c2b)*s2t*Yb)/t**1.5_dp) - &
     &cbe**2*ht**2*(0.125_dp*(mb*s2b*s2t)/t**1.5_dp + &
     &0.125_dp*((1 + c2b)*s2t*Yt)/t**1.5_dp)) - &
     &0.25_dp*(ht**2*(-((cbe**2*s2t*tmp242*Yt)/t**1.5_dp) +  &
     (cbe**2*s2t*tmp250*Yt)/t**1.5_dp - 0.5_dp*(s2t*sbe**2*Xt* &
     (-10*T1 + 4*T1*Log_T1_q + tmp189*Log_T1_q))/ t**1.5_dp + 0.5_dp* &
     (s2t*sbe**2*Xt* (-10*T2 + 4*T2*Log_T2_q + tmp209*Log_T2_q))/ &
     t**1.5_dp)) + tmp5*(-5 + tmp145/t +  &
     (2*b*(-b + t)*tmp158)/((1 - b/t)*t**2) + &
     &0.5_dp*((b + t)*(8/t - tmp145/t**2 +  &
     (4*b*tmp158)/((1 - b/t)*t**2) + (b - t)*tmp172 - &
     &2*(-b + t)*tmp218 - (4*Log_t_q)/t)) - &
     &2*Li2(1 - b/t) + (b*(-1 + Log_b_q))/t + 4*Log_t_q +  &
     (2*(b - t)*Log_t_q)/t - Log_t_q**2)
   Dtt = Dtt + tmp4* (-((A0*(-1 + Log_A0_q))/t) + (b*(-1 + Log_b_q))/t -  &
     (A0 - b - t)*(2/t - 0.5_dp*tmp277/b - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q)/t**2 - &
     &0.5_dp*((A0 - b - t)*Log_b_q)/t**2 - Log_A0_q/t - Log_b_q/t) + &
     &2*(-0.5_dp - 0.5_dp*(tmp234*delt_A0_t_b)/b + &
     &0.5_dp*((-A0 + b - t)*Log_A0_q)/t + 0.5_dp*((A0 - b - t)*Log_b_q)/t + &
     &0.5_dp*(Log_A0_q*Log_b_q) - 0.5_dp*(Log_A0_q*Log_t_q) - &
     &0.5_dp*(Log_b_q*Log_t_q) + 2*Log_t_q -  &
     ((-A0 - b + t)*phi_A0_t_b)/b)) - 4*mb*cbe*hb*ht*sbe* &
     (-(0.25_dp*(2.5_dp*(A0 + b + t) + 0.5_dp*tmp224 - &
     &0.5_dp*((-A0 - b + t)*Log_A0_q*Log_b_q) - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q*Log_t_q) - &
     &0.5_dp*((A0 - b - t)*Log_b_q*Log_t_q) + &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b - &
     &2*A0*Log_A0_q - 2*b*Log_b_q - 2*t*Log_t_q)/ t**1.5_dp) + mt* &
     (-2/t + 0.5_dp*tmp277/b + 0.5_dp*((-A0 + b - t)*Log_A0_q)/t**2 + &
     &0.5_dp*((A0 - b - t)*Log_b_q)/t**2 + 0.5_dp*(8/t - tmp145/t**2 +  &
     (4*b*tmp158)/((1 - b/t)*t**2) + (b - t)*tmp172 - &
     &2*(-b + t)*tmp218 - (4*Log_t_q)/t) + Log_A0_q/t + Log_b_q/t) +  &
     (0.5_dp + 0.5_dp*tmp223 + 0.5_dp*(tmp234*delt_A0_t_b)/b - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q)/t - 0.5_dp*((A0 - b - t)*Log_b_q)/t - &
     &0.5_dp*(Log_A0_q*Log_b_q) + 0.5_dp*(Log_A0_q*Log_t_q) + &
     &0.5_dp*(Log_b_q*Log_t_q) - 2*Log_t_q +  &
     ((-A0 - b + t)*phi_A0_t_b)/b)/mt)
   Dtt = Dtt + tmp55* (-((B1*(-1 + Log_B1_q))/t) +  &
     (mu2*(-1 + Log_mu2_q))/t -  (B1 - mu2 - t)* (2/t - 0.5_dp*tmp278/mu2 - &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t**2 - &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t**2 - Log_B1_q/t - Log_mu2_q/t) + &
     &2*(-0.5_dp - 0.5_dp*(tmp251*delt_B1_t_mu2)/mu2 + &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t + &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t + 0.5_dp*(Log_B1_q*Log_mu2_q) - &
     &0.5_dp*(Log_B1_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_t_q) + 2*Log_t_q -  &
     ((-B1 - mu2 + t)*phi_B1_t_mu2)/mu2))+tmp54*(-((B2*(-1 + Log_B2_q))/t) +  &
     (mu2*(-1 + Log_mu2_q))/t -  (B2 - mu2 - t)* (2/t - 0.5_dp*tmp280/mu2 - &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t**2 - &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t**2 - Log_B2_q/t - Log_mu2_q/t) + &
     &2*(-0.5_dp - 0.5_dp*(tmp253*delt_B2_t_mu2)/mu2 + &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t + &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t + 0.5_dp*(Log_B2_q*Log_mu2_q) - &
     &0.5_dp*(Log_B2_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_t_q) + 2*Log_t_q -  &
     ((-B2 - mu2 + t)*phi_B2_t_mu2)/mu2))
   Dtt = Dtt - 2*hb*ht*abs_mu*s2b* (-(0.25_dp*tmp214/t**1.5_dp) + &
     &mt*(-(0.5_dp*tmp278/mu2) + 0.5_dp*tmp280/mu2 - &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t**2 + &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t**2 - &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t**2 + &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t**2 - Log_B1_q/t + Log_B2_q/t) +  &
     (-(0.5_dp*(tmp251*delt_B1_t_mu2)/mu2) + &
     &0.5_dp*(tmp253*delt_B2_t_mu2)/mu2 + &
     &0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t - &
     &0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t + &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t - &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t + 0.5_dp*(Log_B1_q*Log_mu2_q) - &
     &0.5_dp*(Log_B2_q*Log_mu2_q) - 0.5_dp*(Log_B1_q*Log_t_q) + &
     &0.5_dp*(Log_B2_q*Log_t_q) -  ((-B1 - mu2 + t)*phi_B1_t_mu2)/mu2 +  &
     ((-B2 - mu2 + t)*phi_B2_t_mu2)/mu2)/mt)
   Dc2tc2t = tmp221* (0.125_dp*hb**2/c2t**3 - 0.125_dp*ht**2/c2t**3) + &
     &tmp220*(-(0.125_dp*hb**2/c2t**3) + 0.125_dp*ht**2/c2t**3) + &
     &0.5_dp*(mb*hb*ht*abs_mu*tmp217)/s2t**3 + &
     &0.5_dp*(tmp233*(-(cbe**2*hb**2* (0.0625_dp*(b*(1 - c2b))/c2t**3 - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*t)/c2t**3 - 0.125_dp*(mb*s2b*Xb)/c2t**3 + &
     &0.125_dp*((1 + c2b)*mt*Xb)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*Xb**2)/c2t**3)) + cbe*hb*ht*sbe* &
     (-(s2b*mt*tmp15) + 2*mb*mt*tmp46 - &
     &0.125_dp*(s2b*(b + t))/s2t**3 + 0.25_dp*(mb*tmp69)/s2t**3 - &
     &0.125_dp*(s2b*Xb*Xt)/s2t**3) - ht**2*sbe**2* &
     (-(0.0625_dp*(b*(1 + c2b))/c2t**3) - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*t)/c2t**3 + 0.125_dp*(mb*s2b*Xt)/c2t**3 + &
     &0.125_dp*((1 - c2b)*mt*Xt)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*Xt**2)/c2t**3))) + 0.5_dp*(tmp228*(-(cbe**2*hb**2* &
     (-(0.0625_dp*(b*(1 - c2b))/c2t**3) + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*t)/c2t**3 + 0.125_dp*(mb*s2b*Xb)/c2t**3 - &
     &0.125_dp*((1 + c2b)*mt*Xb)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*Xb**2)/c2t**3)) + cbe*hb*ht*sbe* &
     (-(s2b*mt*tmp16) + 2*mb*mt*tmp47 + &
     &0.125_dp*(s2b*(b + t))/s2t**3 - 0.25_dp*(mb*tmp69)/s2t**3 + &
     &0.125_dp*(s2b*Xb*Xt)/s2t**3) - ht**2*sbe**2* &
     (0.0625_dp*(b*(1 + c2b))/c2t**3 + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*t)/c2t**3 - 0.125_dp*(mb*s2b*Xt)/c2t**3 - &
     &0.125_dp*((1 - c2b)*mt*Xt)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*Xt**2)/c2t**3)))
   Dc2tc2t = Dc2tc2t + 0.5_dp*(tmp232*(-(cbe**2*hb**2* &
     (0.0625_dp*(b*(1 + c2b))/c2t**3 + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*t)/c2t**3 + 0.125_dp*(mb*s2b*Xb)/c2t**3 + &
     &0.125_dp*((1 - c2b)*mt*Xb)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*Xb**2)/c2t**3)) + cbe*hb*ht*sbe* &
     (s2b*mt*tmp15 + 2*mb*mt*tmp47 + &
     &0.125_dp*(s2b*(b + t))/s2t**3 + 0.25_dp*(mb*tmp70)/s2t**3 + &
     &0.125_dp*(s2b*Xb*Xt)/s2t**3) - ht**2*sbe**2* &
     (-(0.0625_dp*(b*(1 - c2b))/c2t**3) + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*t)/c2t**3 - 0.125_dp*(mb*s2b*Xt)/c2t**3 + &
     &0.125_dp*((1 + c2b)*mt*Xt)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*Xt**2)/c2t**3))) + 0.5_dp*(tmp227*(-(cbe**2*hb**2* &
     (-(0.0625_dp*(b*(1 + c2b))/c2t**3) - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*t)/c2t**3 - 0.125_dp*(mb*s2b*Xb)/c2t**3 - &
     &0.125_dp*((1 - c2b)*mt*Xb)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*Xb**2)/c2t**3)) + cbe*hb*ht*sbe* &
     (s2b*mt*tmp16 + 2*mb*mt*tmp46 - &
     &0.125_dp*(s2b*(b + t))/s2t**3 - 0.25_dp*(mb*tmp70)/s2t**3 - &
     &0.125_dp*(s2b*Xb*Xt)/s2t**3) - ht**2*sbe**2* &
     (0.0625_dp*(b*(1 - c2b))/c2t**3 - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*t)/c2t**3 + 0.125_dp*(mb*s2b*Xt)/c2t**3 - &
     &0.125_dp*((1 + c2b)*mt*Xt)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*Xt**2)/c2t**3)))
   Dc2tc2t = Dc2tc2t + tmp213*(-(hb**2*sbe**2* &
     (0.0625_dp*(b*(1 - c2b))/c2t**3 - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*t)/c2t**3 - 0.125_dp*(mb*s2b*Yb)/c2t**3 + &
     &0.125_dp*((1 + c2b)*mt*Yb)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*Yb**2)/c2t**3)) - &
     &cbe*hb*ht*sbe*(-(s2b*mt*tmp33) + 2*mb*mt*tmp46 - &
     &0.125_dp*(s2b*(b + t))/s2t**3 + 0.25_dp*(mb*tmp95)/s2t**3 - &
     &0.125_dp*(s2b*Yb*Yt)/s2t**3) - &
     &cbe**2*ht**2*(-(0.0625_dp*(b*(1 + c2b))/c2t**3) - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + 0.0625_dp*((1 - c2b)*t)/c2t**3 + &
     &0.125_dp*(mb*s2b*Yt)/c2t**3 + &
     &0.125_dp*((1 - c2b)*mt*Yt)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*Yt**2)/c2t**3)) + tmp211*(-(hb**2*sbe**2* &
     (-(0.0625_dp*(b*(1 - c2b))/c2t**3) + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*t)/c2t**3 + 0.125_dp*(mb*s2b*Yb)/c2t**3 - &
     &0.125_dp*((1 + c2b)*mt*Yb)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*Yb**2)/c2t**3)) - &
     &cbe*hb*ht*sbe*(-(s2b*mt*tmp34) + 2*mb*mt*tmp47 + &
     &0.125_dp*(s2b*(b + t))/s2t**3 - 0.25_dp*(mb*tmp95)/s2t**3 + &
     &0.125_dp*(s2b*Yb*Yt)/s2t**3) - &
     &cbe**2*ht**2*(0.0625_dp*(b*(1 + c2b))/c2t**3 + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - 0.0625_dp*((1 - c2b)*t)/c2t**3 - &
     &0.125_dp*(mb*s2b*Yt)/c2t**3 - &
     &0.125_dp*((1 - c2b)*mt*Yt)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*Yt**2)/c2t**3))
   Dc2tc2t = Dc2tc2t + tmp212*(-(hb**2*sbe**2* &
     (0.0625_dp*(b*(1 + c2b))/c2t**3 + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*t)/c2t**3 + 0.125_dp*(mb*s2b*Yb)/c2t**3 + &
     &0.125_dp*((1 - c2b)*mt*Yb)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*Yb**2)/c2t**3)) - cbe*hb*ht*sbe*(s2b*mt*tmp33 + &
     &2*mb*mt*tmp47 + 0.125_dp*(s2b*(b + t))/s2t**3 + &
     &0.25_dp*(mb*tmp96)/s2t**3 + 0.125_dp*(s2b*Yb*Yt)/s2t**3) - &
     &cbe**2*ht**2*(-(0.0625_dp*(b*(1 - c2b))/c2t**3) + &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + 0.0625_dp*((1 + c2b)*t)/c2t**3 - &
     &0.125_dp*(mb*s2b*Yt)/c2t**3 + &
     &0.125_dp*((1 + c2b)*mt*Yt)/s2t**3 - &
     &0.0625_dp*((1 + c2b)*Yt**2)/c2t**3)) + tmp210*(-(hb**2*sbe**2* &
     (-(0.0625_dp*(b*(1 + c2b))/c2t**3) - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 + &
     &0.0625_dp*((1 - c2b)*t)/c2t**3 - 0.125_dp*(mb*s2b*Yb)/c2t**3 - &
     &0.125_dp*((1 - c2b)*mt*Yb)/s2t**3 - &
     &0.0625_dp*((1 - c2b)*Yb**2)/c2t**3)) - cbe*hb*ht*sbe*(s2b*mt*tmp34 + &
     &2*mb*mt*tmp46 - 0.125_dp*(s2b*(b + t))/s2t**3 - &
     &0.25_dp*(mb*tmp96)/s2t**3 - 0.125_dp*(s2b*Yb*Yt)/s2t**3) - &
     &cbe**2*ht**2*(0.0625_dp*(b*(1 - c2b))/c2t**3 - &
     &0.125_dp*(mb*s2b*mt)/s2t**3 - 0.0625_dp*((1 + c2b)*t)/c2t**3 + &
     &0.125_dp*(mb*s2b*Yt)/c2t**3 - &
     &0.125_dp*((1 + c2b)*mt*Yt)/s2t**3 + &
     &0.0625_dp*((1 + c2b)*Yt**2)/c2t**3)) + &
     &ht**2*(0.0625_dp*(B1*(1 + c2b)*T1*(-1 + Log_B1_q)* &
     (-1 + Log_T1_q))/c2t**3 + 0.0625_dp*(B2*(1 - c2b)*T1*(-1 + Log_B2_q)* &
     (-1 + Log_T1_q))/c2t**3 + cbe**2*(0.125_dp*(A0*T1*(-1 + Log_A0_q)* &
     (-1 + Log_T1_q))/c2t**3 - &
     &0.125_dp*(A0*T2*(-1 + Log_A0_q)*(-1 + Log_T2_q))/ c2t**3) - &
     &0.0625_dp*(B1*(1 + c2b)*T2*(-1 + Log_B1_q)* (-1 + Log_T2_q))/c2t**3 - &
     &0.0625_dp*(B2*(1 - c2b)*T2*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2t**3)
   Dc2tc2t = Dc2tc2t - 0.25_dp*(ht**2*(-((cbe**2*mt*tmp242*Yt)/s2t**3) +  &
     (cbe**2*mt*tmp250*Yt)/s2t**3 - 0.5_dp*(sbe**2*mt*Xt* &
     (-10*T1 + 4*T1*Log_T1_q + tmp189*Log_T1_q))/ s2t**3 + 0.5_dp* &
     (sbe**2*mt*Xt* (-10*T2 + 4*T2*Log_T2_q + tmp209*Log_T2_q))/ &
     s2t**3)) + hb**2*(-(0.0625_dp*(B1*(1 - c2b)*T1*(-1 + Log_B1_q)* &
     (-1 + Log_T1_q))/c2t**3) - 0.0625_dp*(B2*(1 + c2b)*T1*(-1 + Log_B2_q)* &
     (-1 + Log_T1_q))/c2t**3 + sbe**2*(-(0.125_dp* &
     (A0*T1*(-1 + Log_A0_q)*(-1 + Log_T1_q))/c2t**3) &
     + 0.125_dp*(A0*T2*(-1 + Log_A0_q)*(-1 + Log_T2_q))/ c2t**3) + &
     &0.0625_dp*(B1*(1 - c2b)*T2*(-1 + Log_B1_q)* (-1 + Log_T2_q))/c2t**3 + &
     &0.0625_dp*(B2*(1 + c2b)*T2*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2t**3)
   DT1t = -(0.5_dp*(tmp128*tmp225)) - 0.5_dp*(tmp127*tmp226) - &
     &0.25_dp*(ht**2*(0.5_dp*(sbe**2*tmp20*tmp264) + cbe**2*tmp38* &
     (-1 - 0.5_dp*(tmp241*delt_A0_T1_T1)/T1 + &
     &0.5_dp*(delt_A0_T1_T1*phi_A0_T1_T1)/T1**2 -  &
     (A0*Log_A0_q)/T1 + 4*Log_T1_q +  &
     ((A0 - 2*T1)*Log_T1_q)/T1 - Log_T1_q**2 +  &
     (2*A0*phi_A0_T1_T1)/T1))) - &
     &tmp136*(-0.5_dp - 0.5_dp*(tmp237*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q)/T1 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B1_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B1 + T1)*phi_A0_T1_B1)/B1) - &
     &tmp135*(-0.5_dp - 0.5_dp*(tmp239*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q)/T1 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B2 + T1)*phi_A0_T1_B2)/B2)
   DT1t = DT1t + ht**2* (1 - 0.5_dp*(tmp257*delt_T1_t_mu2)/mu2 + &
     &0.5_dp*(tmp258*delt_T1_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 + t - T1)*Log_mu2_q)/T1 - &
     &0.5_dp*((-mu2 - t + T1)*Log_mu2_q)/t + &
     &0.5_dp*((mu2 - t - T1)*Log_t_q)/T1 - &
     &0.5_dp*((mu2 - t - T1)*Log_T1_q)/t - 3*Log_t_q + Log_mu2_q*Log_t_q -  &
     (-1 + Log_t_q)*(-1 + Log_T1_q) + Log_T1_q - Log_mu2_q*Log_T1_q +  &
     ((-mu2 + t - T1)*phi_T1_t_mu2)/mu2 -  &
     ((-mu2 - t + T1)*phi_T1_t_mu2)/mu2 -  (-mu2 - t + T1)* &
     (-(((-mu2 + t - T1)*tmp257)/mu2) -  ((-mu2 - t + T1)*tmp258)/mu2 + &
     &0.5_dp*(mu2 - t - T1)/(t*T1) + 0.5_dp*Log_mu2_q/t + &
     &0.5_dp*Log_mu2_q/T1 - 0.5_dp*Log_t_q/T1 - 0.5_dp*Log_T1_q/t - &
     &0.5_dp*(delt_T1_t_mu2* ((-2*mu2*(-mu2 + t - T1)* &
     ((-mu2 + t)*tmp162 + T1*tmp187))/ (T1*delt_T1_t_mu2**2) +  &
     ((mu2 + t - T1)*tmp258)/delt_T1_t_mu2 +  &
     (mu2*(-((-mu2 + t)/t) - T1/t + Log_mu2_q - &
     &Log_t_q))/(T1*delt_T1_t_mu2) -  &
     (2*(-mu2 + t - T1)*(mu2 + t - T1)*&
     &phi_T1_t_mu2)/delt_T1_t_mu2**2 + &
     &phi_T1_t_mu2/delt_T1_t_mu2))/mu2 + phi_T1_t_mu2/mu2))
   DT2t = -(0.5_dp*(tmp132*tmp230)) - 0.5_dp*(tmp131*tmp231) - &
     &0.25_dp*(ht**2*(0.5_dp*(sbe**2*tmp19*tmp266) + cbe**2*tmp37* &
     (-1 - 0.5_dp*(tmp249*delt_A0_T2_T2)/T2 + &
     &0.5_dp*(delt_A0_T2_T2*phi_A0_T2_T2)/T2**2 -  &
     (A0*Log_A0_q)/T2 + 4*Log_T2_q +  &
     ((A0 - 2*T2)*Log_T2_q)/T2 - Log_T2_q**2 +  &
     (2*A0*phi_A0_T2_T2)/T2))) - &
     &tmp140*(-0.5_dp - 0.5_dp*(tmp245*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q)/T2 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B1_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B1 + T2)*phi_A0_T2_B1)/B1) - &
     &tmp139*(-0.5_dp - 0.5_dp*(tmp247*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q)/T2 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B2_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B2 + T2)*phi_A0_T2_B2)/B2)
   DT2t = DT2t + ht**2* (1 - 0.5_dp*(tmp261*delt_T2_t_mu2)/mu2 + &
     &0.5_dp*(tmp262*delt_T2_t_mu2)/mu2 + &
     &0.5_dp*((-mu2 + t - T2)*Log_mu2_q)/T2 - &
     &0.5_dp*((-mu2 - t + T2)*Log_mu2_q)/t + &
     &0.5_dp*((mu2 - t - T2)*Log_t_q)/T2 - &
     &0.5_dp*((mu2 - t - T2)*Log_T2_q)/t - 3*Log_t_q + Log_mu2_q*Log_t_q -  &
     (-1 + Log_t_q)*(-1 + Log_T2_q) + Log_T2_q - Log_mu2_q*Log_T2_q +  &
     ((-mu2 + t - T2)*phi_T2_t_mu2)/mu2 -  &
     ((-mu2 - t + T2)*phi_T2_t_mu2)/mu2 -  (-mu2 - t + T2)* &
     (-(((-mu2 + t - T2)*tmp261)/mu2) -  ((-mu2 - t + T2)*tmp262)/mu2 + &
     &0.5_dp*(mu2 - t - T2)/(t*T2) + 0.5_dp*Log_mu2_q/t + &
     &0.5_dp*Log_mu2_q/T2 - 0.5_dp*Log_t_q/T2 - 0.5_dp*Log_T2_q/t - &
     &0.5_dp*(delt_T2_t_mu2* ((-2*mu2*(-mu2 + t - T2)* &
     ((-mu2 + t)*tmp162 + T2*tmp205))/ (T2*delt_T2_t_mu2**2) +  &
     ((mu2 + t - T2)*tmp262)/delt_T2_t_mu2 +  &
     (mu2*(-((-mu2 + t)/t) - T2/t + Log_mu2_q - &
     &Log_t_q))/(T2*delt_T2_t_mu2) -  &
     (2*(-mu2 + t - T2)*(mu2 + t - T2)*&
     &phi_T2_t_mu2)/delt_T2_t_mu2**2 + &
     &phi_T2_t_mu2/delt_T2_t_mu2))/mu2 + phi_T2_t_mu2/mu2))
   DT1T2 = -(0.25_dp*(ht**2* ((1 + c2t**2)*sbe**2*Xt**2* &
     ((2*(T1 - T2))/(T1**2*(1 - T2/T1)) +  (2*(T1 - T2)*T2*tmp200)/ &
     (T1**3*(1 - T2/T1)**2) -  (2*tmp200)/(T1*(1 - T2/T1)) +  &
     (2*(T1 - T2)*tmp200)/(T1**2*(1 - T2/T1)) -  &
     (2*T2*tmp200)/(T1**2*(1 - T2/T1)) +  &
     (2*Log_T1_q)/T1 + (-2 - 2*Log_T2_q)/T1) + &
     &2*(1 + c2t**2)*cbe**2*Yt**2* (-(((-A0 - T1 + T2)*tmp243)/T2) -  &
     ((-A0 + T1 - T2)*tmp244)/T2 + 0.5_dp*(A0 - T1 - T2)/(T1*T2) + &
     &0.5_dp*(tmp243*delt_A0_T1_T2)/T2**2 + &
     &0.5_dp*Log_A0_q/T1 + 0.5_dp*Log_A0_q/T2 - &
     &0.5_dp*Log_T1_q/T2 - 0.5_dp*Log_T2_q/T1 - 0.5_dp*(delt_A0_T1_T2* &
     ((-2*T2*(-A0 - T1 + T2)* (T1*tmp198 + (A0 - T2)*tmp199))/ &
     (T1*delt_A0_T1_T2**2) +  (T1*tmp198 + (A0 - T2)*tmp199)/ &
     (T1*delt_A0_T1_T2) +  &
     ((A0 - T1 + T2)*tmp244)/delt_A0_T1_T2 +  (T2* &
     (-(T1/T2) + (A0 - T2)/T2 + Log_A0_q - &
     &Log_T2_q))/(T1*delt_A0_T1_T2) -  &
     (2*(-A0 - T1 + T2)*(A0 - T1 + T2)*&
     &phi_A0_T1_T2)/delt_A0_T1_T2**2 + &
     &phi_A0_T1_T2/delt_A0_T1_T2))/T2 +  &
     ((-A0 + T1 - T2)*phi_A0_T1_T2)/T2**2 + phi_A0_T1_T2/T2)))) + &
     &ht**2*(c2t**2 - 0.5_dp*((-1 + Nc)*s2t**2) + &
     &tmp3*(-1 + Log_T1_q) + tmp3*(-1 + Log_T2_q) + &
     &tmp3*(-1 + Log_T1_q)*(-1 + Log_T2_q))
   Dtc2t = -(0.5_dp*(tmp228* (-(cbe*hb*ht*sbe* &
     ((mb*tmp48)/mt + 0.25_dp*s2b/s2t - &
     &0.5_dp*(s2b*tmp17)/mt)) + cbe**2*hb**2* &
     (-(0.125_dp*(1 + c2b)/c2t) + 0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 + c2b)*Xb)/(s2t*mt)) + ht**2*sbe**2* &
     (0.125_dp*(1 - c2b)/c2t + 0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 - c2b)*Xt)/(s2t*mt))))) - 0.5_dp*(tmp233*(-(cbe*hb*ht*sbe* &
     ((mb*tmp49)/mt - 0.25_dp*s2b/s2t - &
     &0.5_dp*(s2b*tmp18)/mt)) + cbe**2*hb**2* (0.125_dp*(1 + c2b)/c2t - &
     &0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 + c2b)*Xb)/(s2t*mt)) + ht**2*sbe**2* &
     (-(0.125_dp*(1 - c2b)/c2t) - 0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 - c2b)*Xt)/(s2t*mt)))) - 0.5_dp*(tmp227*(-(cbe*hb*ht*sbe* &
     ((mb*tmp49)/mt - 0.25_dp*s2b/s2t + &
     &0.5_dp*(s2b*tmp17)/mt)) + cbe**2*hb**2* (-(0.125_dp*(1 - c2b)/c2t) - &
     &0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 - c2b)*Xb)/(s2t*mt)) + ht**2*sbe**2* &
     (0.125_dp*(1 + c2b)/c2t - 0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 + c2b)*Xt)/(s2t*mt)))) - 0.5_dp*(tmp232*(-(cbe*hb*ht*sbe* &
     ((mb*tmp48)/mt + 0.25_dp*s2b/s2t + &
     &0.5_dp*(s2b*tmp18)/mt)) + cbe**2*hb**2* (0.125_dp*(1 - c2b)/c2t + &
     &0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 - c2b)*Xb)/(s2t*mt)) + ht**2*sbe**2* &
     (-(0.125_dp*(1 + c2b)/c2t) + 0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 + c2b)*Xt)/(s2t*mt))))
   Dtc2t = Dtc2t - tmp211* &
     (cbe*hb*ht*sbe*((mb*tmp48)/mt + 0.25_dp*s2b/s2t - &
     &0.5_dp*(s2b*tmp35)/mt) + hb**2*sbe**2*(-(0.125_dp*(1 + c2b)/c2t) + &
     &0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 + c2b)*Yb)/(s2t*mt)) + &
     &cbe**2*ht**2*(0.125_dp*(1 - c2b)/c2t + &
     &0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 - c2b)*Yt)/(s2t*mt))) - tmp213*(cbe*hb*ht*sbe* &
     ((mb*tmp49)/mt - 0.25_dp*s2b/s2t - &
     &0.5_dp*(s2b*tmp36)/mt) + hb**2*sbe**2*(0.125_dp*(1 + c2b)/c2t - &
     &0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 + c2b)*Yb)/(s2t*mt)) + &
     &cbe**2*ht**2*(-(0.125_dp*(1 - c2b)/c2t) - &
     &0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 - c2b)*Yt)/(s2t*mt))) - tmp210*(cbe*hb*ht*sbe* &
     ((mb*tmp49)/mt - 0.25_dp*s2b/s2t + &
     &0.5_dp*(s2b*tmp35)/mt) + hb**2*sbe**2*(-(0.125_dp*(1 - c2b)/c2t) - &
     &0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 - c2b)*Yb)/(s2t*mt)) + &
     &cbe**2*ht**2*(0.125_dp*(1 + c2b)/c2t - &
     &0.125_dp*(mb*s2b)/(s2t*mt) - &
     &0.125_dp*((1 + c2b)*Yt)/(s2t*mt))) - tmp212*(cbe*hb*ht*sbe* &
     ((mb*tmp48)/mt + 0.25_dp*s2b/s2t + &
     &0.5_dp*(s2b*tmp36)/mt) + hb**2*sbe**2*(0.125_dp*(1 - c2b)/c2t + &
     &0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 - c2b)*Yb)/(s2t*mt)) + &
     &cbe**2*ht**2*(-(0.125_dp*(1 + c2b)/c2t) + &
     &0.125_dp*(mb*s2b)/(s2t*mt) + &
     &0.125_dp*((1 + c2b)*Yt)/(s2t*mt)))
   Dtc2t = Dtc2t - 0.25_dp* (ht**2*(-((cbe**2*tmp242*Yt)/(s2t*mt)) +  &
     (cbe**2*tmp250*Yt)/(s2t*mt) - 0.5_dp*(sbe**2*Xt* &
     (-10*T1 + 4*T1*Log_T1_q + tmp189*Log_T1_q))/ (s2t*mt) + &
     &0.5_dp*(sbe**2*Xt* (-10*T2 + 4*T2*Log_T2_q + tmp209*Log_T2_q))/ &
     (s2t*mt)))
   DT1c2t = tmp1*tmp267 - 0.5_dp*(tmp120*tmp225) - 0.5_dp*(tmp119*tmp226) + &
     &hb**2*(0.125_dp*(B1*(1 - c2b)*(-1 + Log_B1_q))/c2t + &
     &0.125_dp*(B2*(1 + c2b)*(-1 + Log_B2_q))/c2t + &
     &sbe**2*(0.25_dp*(A0*(-1 + Log_A0_q))/c2t + &
     &0.25_dp*(A0*(-1 + Log_A0_q)*(-1 + Log_T1_q))/c2t) + &
     &0.125_dp*(B1*(1 - c2b)*(-1 + Log_B1_q)*(-1 + Log_T1_q))/ &
     c2t + 0.125_dp*(B2*(1 + c2b)*(-1 + Log_B2_q)* (-1 + Log_T1_q))/c2t) + &
     &ht**2*(-(0.25_dp*((1 + Nc)*tmp271)) - &
     &0.125_dp*(B1*(1 + c2b)*(-1 + Log_B1_q))/c2t - &
     &0.125_dp*(B2*(1 - c2b)*(-1 + Log_B2_q))/c2t + &
     &cbe**2*(-(0.25_dp*(A0*(-1 + Log_A0_q))/c2t) - &
     &0.25_dp*(A0*(-1 + Log_A0_q)*(-1 + Log_T1_q))/c2t) - &
     &0.125_dp*(B1*(1 + c2b)*(-1 + Log_B1_q)*(-1 + Log_T1_q))/ &
     c2t - 0.125_dp*(B2*(1 - c2b)*(-1 + Log_B2_q)* (-1 + Log_T1_q))/c2t + &
     &T2*(1 + 0.5_dp*(-1 + Nc))*(-1 + Log_T2_q) + &
     &T2*(1 + 0.5_dp*(-1 + Nc))*(-1 + Log_T1_q)* (-1 + Log_T2_q)) - &
     &tmp124*(-0.5_dp - 0.5_dp*(tmp237*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q)/T1 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B1_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B1 + T1)*phi_A0_T1_B1)/B1) - &
     &tmp123*(-0.5_dp - 0.5_dp*(tmp239*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q)/T1 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B2 + T1)*phi_A0_T1_B2)/B2)
   DT1c2t = DT1c2t - 0.25_dp*(ht**2*(sbe**2*tmp219*Xt**2 + &
     &0.5_dp*(sbe**2*tmp22*tmp264) + cbe**2*tmp40* &
     (-1 - 0.5_dp*(tmp241*delt_A0_T1_T1)/T1 + &
     &0.5_dp*(delt_A0_T1_T1*phi_A0_T1_T1)/T1**2 -  &
     (A0*Log_A0_q)/T1 + 4*Log_T1_q +  &
     ((A0 - 2*T1)*Log_T1_q)/T1 - Log_T1_q**2 +  &
     (2*A0*phi_A0_T1_T1)/T1) + 2*cbe**2*Yt**2* &
     (-0.5_dp - 0.5_dp*(tmp243*delt_A0_T1_T2)/T2 + &
     &0.5_dp*((-A0 - T1 + T2)*Log_A0_q)/T1 - 0.5_dp*(Log_A0_q*Log_T1_q) + &
     &0.5_dp*((A0 - T1 - T2)*Log_T2_q)/T1 + 0.5_dp*(Log_A0_q*Log_T2_q) - &
     &0.5_dp*(Log_T1_q*Log_T2_q) + 2*Log_T1_q -  &
     ((-A0 + T1 - T2)*phi_A0_T1_T2)/T2))) +  (mb*hb*ht*abs_mu* &
     (-0.5_dp - 0.5_dp*(tmp255*delt_T1_b_mu2)/mu2 + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1 + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1 + 0.5_dp*(Log_b_q*Log_mu2_q) - &
     &0.5_dp*(Log_b_q*Log_T1_q) - &
     &0.5_dp*(Log_mu2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-b - mu2 + T1)*phi_T1_b_mu2)/mu2))/s2t
   DT2c2t = tmp2*tmp268 - 0.5_dp*(tmp122*tmp230) - 0.5_dp*(tmp121*tmp231) + &
     &hb**2*(-(0.125_dp*(B1*(1 - c2b)*(-1 + Log_B1_q))/c2t) - &
     &0.125_dp*(B2*(1 + c2b)*(-1 + Log_B2_q))/c2t + &
     &sbe**2*(-(0.25_dp*(A0*(-1 + Log_A0_q))/c2t) - &
     &0.25_dp*(A0*(-1 + Log_A0_q)*(-1 + Log_T2_q))/c2t) - &
     &0.125_dp*(B1*(1 - c2b)*(-1 + Log_B1_q)*(-1 + Log_T2_q))/ &
     c2t - 0.125_dp*(B2*(1 + c2b)*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2t) + &
     &ht**2*(-(0.25_dp*((1 + Nc)*tmp274)) + &
     &0.125_dp*(B1*(1 + c2b)*(-1 + Log_B1_q))/c2t + &
     &0.125_dp*(B2*(1 - c2b)*(-1 + Log_B2_q))/c2t + &
     &cbe**2*(0.25_dp*(A0*(-1 + Log_A0_q))/c2t + &
     &0.25_dp*(A0*(-1 + Log_A0_q)*(-1 + Log_T2_q))/c2t) + &
     &0.125_dp*(B1*(1 + c2b)*(-1 + Log_B1_q)*(-1 + Log_T2_q))/ &
     c2t + 0.125_dp*(B2*(1 - c2b)*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2t + &
     &T1*(1 + 0.5_dp*(-1 + Nc))*(-1 + Log_T1_q) + &
     &T1*(1 + 0.5_dp*(-1 + Nc))*(-1 + Log_T1_q)* (-1 + Log_T2_q)) - &
     &tmp126*(-0.5_dp - 0.5_dp*(tmp245*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q)/T2 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B1_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B1 + T2)*phi_A0_T2_B1)/B1) - &
     &tmp125*(-0.5_dp - 0.5_dp*(tmp247*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q)/T2 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B2_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B2 + T2)*phi_A0_T2_B2)/B2)
   DT2c2t = DT2c2t - 0.25_dp*(ht**2*(sbe**2*tmp265*Xt**2 + &
     &0.5_dp*(sbe**2*tmp23*tmp266) + 2*cbe**2*Yt**2* &
     (-0.5_dp - 0.5_dp*(tmp244*delt_A0_T1_T2)/T2 + &
     &0.5_dp*((-A0 + T1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - T1 - T2)*Log_T1_q)/T2 + 0.5_dp*(Log_A0_q*Log_T1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_T1_q*Log_T2_q) + &
     &0.5_dp*(delt_A0_T1_T2*phi_A0_T1_T2)/T2**2 + &
     &2*Log_T2_q - ((-A0 - T1 + T2)*phi_A0_T1_T2)/T2)+cbe**2*tmp41* &
     (-1 - 0.5_dp*(tmp249*delt_A0_T2_T2)/T2 + &
     &0.5_dp*(delt_A0_T2_T2*phi_A0_T2_T2)/T2**2 -  &
     (A0*Log_A0_q)/T2 + 4*Log_T2_q +  &
     ((A0 - 2*T2)*Log_T2_q)/T2 - Log_T2_q**2 +  &
     (2*A0*phi_A0_T2_T2)/T2))) +  (mb*hb*ht*abs_mu* &
     (0.5_dp + 0.5_dp*(tmp259*delt_T2_b_mu2)/mu2 - &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2 - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2 - 0.5_dp*(Log_b_q*Log_mu2_q) + &
     &0.5_dp*(Log_b_q*Log_T2_q) + &
     &0.5_dp*(Log_mu2_q*Log_T2_q) - 2*Log_T2_q +  &
     ((-b - mu2 + T2)*phi_T2_b_mu2)/mu2))/s2t
   Dtb = -(tmp211*(-(0.125_dp* (cbe**2*ht**2*s2b*s2t)/(mb*mt)) - &
     &0.125_dp*(hb**2*s2b*s2t*sbe**2)/(mb*mt) + &
     &0.5_dp*(cbe*hb*ht*sbe*tmp50)/(mb*mt))) - &
     &tmp212*(-(0.125_dp*(cbe**2*ht**2*s2b*s2t)/ (mb*mt)) - &
     &0.125_dp*(hb**2*s2b*s2t*sbe**2)/(mb*mt) + &
     &0.5_dp*(cbe*hb*ht*sbe*tmp50)/(mb*mt)) - &
     &tmp210*(0.125_dp*(cbe**2*ht**2*s2b*s2t)/(mb*mt) + &
     &0.125_dp*(hb**2*s2b*s2t*sbe**2)/(mb*mt) + &
     &0.5_dp*(cbe*hb*ht*sbe*tmp53)/(mb*mt)) - &
     &tmp213*(0.125_dp*(cbe**2*ht**2*s2b*s2t)/(mb*mt) + &
     &0.125_dp*(hb**2*s2b*s2t*sbe**2)/(mb*mt) + &
     &0.5_dp*(cbe*hb*ht*sbe*tmp53)/(mb*mt)) - 0.5_dp*(tmp228*(-(0.125_dp* &
     (cbe**2*hb**2*s2b*s2t)/(mb*mt)) - &
     &0.125_dp*(ht**2*s2b*s2t*sbe**2)/(mb*mt) - &
     &0.5_dp*(cbe*hb*ht*sbe*tmp50)/(mb*mt))) - 0.5_dp*(tmp232*(-(0.125_dp* &
     (cbe**2*hb**2*s2b*s2t)/(mb*mt)) - &
     &0.125_dp*(ht**2*s2b*s2t*sbe**2)/(mb*mt) - &
     &0.5_dp*(cbe*hb*ht*sbe*tmp50)/(mb*mt))) - 0.5_dp*(tmp227*(0.125_dp* &
     (cbe**2*hb**2*s2b*s2t)/(mb*mt) + &
     &0.125_dp*(ht**2*s2b*s2t*sbe**2)/(mb*mt) - &
     &0.5_dp*(cbe*hb*ht*sbe*tmp53)/(mb*mt))) - 0.5_dp*(tmp233*(0.125_dp* &
     (cbe**2*hb**2*s2b*s2t)/(mb*mt) + &
     &0.125_dp*(ht**2*s2b*s2t*sbe**2)/(mb*mt) - &
     &0.5_dp*(cbe*hb*ht*sbe*tmp53)/(mb*mt))) + &
     &tmp5*(-1 + 0.5_dp*tmp223 + 0.5_dp*((b + t)*tmp269) + &
     &0.5_dp*tmp270 + Log_b_q +  (-1 + Log_b_q)*(-1 + Log_t_q) + Log_t_q)
   Dtb = Dtb - (cbe*hb*ht*sbe* (2.5_dp*(A0 + b + t) + 0.5_dp*tmp224 - &
     &0.5_dp*((-A0 - b + t)*Log_A0_q*Log_b_q) - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q*Log_t_q) - &
     &0.5_dp*((A0 - b - t)*Log_b_q*Log_t_q) + &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b - 2*A0*Log_A0_q - &
     &2*b*Log_b_q - 2*t*Log_t_q))/(mb*mt) -  (2*mb*cbe*hb*ht*sbe* &
     (0.5_dp + 0.5_dp*tmp270 + 0.5_dp*(tmp235*delt_A0_t_b)/b - &
     &0.5_dp*((-A0 - b + t)*Log_A0_q)/b + 0.5_dp*(Log_A0_q*Log_b_q) - &
     &0.5_dp*((A0 - b - t)*Log_t_q)/b - &
     &0.5_dp*(Log_A0_q*Log_t_q) + 0.5_dp*(Log_b_q*Log_t_q) - &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b**2 - 2*Log_b_q +  &
     ((-A0 + b - t)*phi_A0_t_b)/b))/mt -  (2*cbe*hb*ht*sbe*mt* &
     (0.5_dp + 0.5_dp*tmp223 + 0.5_dp*(tmp234*delt_A0_t_b)/b - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q)/t - 0.5_dp*((A0 - b - t)*Log_b_q)/t - &
     &0.5_dp*(Log_A0_q*Log_b_q) + &
     &0.5_dp*(Log_A0_q*Log_t_q) + 0.5_dp*(Log_b_q*Log_t_q) - &
     &2*Log_t_q + ((-A0 - b + t)*phi_A0_t_b)/b))/mb
   Dtb = Dtb - 4*mb*cbe*hb*ht*sbe*mt* &
     (((-A0 + b - t)*tmp234)/b + ((-A0 - b + t)*tmp235)/b - &
     &0.5_dp*(A0 - b - t)/(b*t) + 0.5_dp*tmp269 - &
     &0.5_dp*(tmp234*delt_A0_t_b)/b**2 - 0.5_dp*Log_A0_q/b - &
     &0.5_dp*Log_A0_q/t + 0.5_dp*Log_b_q/t + 0.5_dp*Log_t_q/b + &
     &0.5_dp*(delt_A0_t_b* &
     ((-2*b*(-A0 + b - t)*((A0 - b)*tmp144 + t*tmp166))/ &
     (t*delt_A0_t_b**2) +  (b*tmp143)/(t*delt_A0_t_b) +  &
     ((A0 - b)*tmp144 + t*tmp166)/(t*delt_A0_t_b) +  &
     ((A0 + b - t)*tmp235)/delt_A0_t_b -  &
     (2*(-A0 + b - t)*(A0 + b - t)*phi_A0_t_b)/ &
     delt_A0_t_b**2 + phi_A0_t_b/delt_A0_t_b))/b-&
     &phi_A0_t_b/b - ((-A0 - b + t)*phi_A0_t_b)/b**2)
   Dtb = Dtb + tmp4* (-2 - 0.5_dp*(tmp234*delt_A0_t_b)/b - &
     &0.5_dp*(tmp235*delt_A0_t_b)/b + 0.5_dp*((-A0 + b - t)*Log_A0_q)/t + &
     &0.5_dp*((-A0 - b + t)*Log_A0_q)/b + 0.5_dp*((A0 - b - t)*Log_b_q)/t + &
     &0.5_dp*((A0 - b - t)*Log_t_q)/b + &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b**2 + 3*Log_b_q +  &
     (-1 + Log_b_q)*(-1 + Log_t_q) + 3*Log_t_q - &
     &Log_b_q*Log_t_q - ((-A0 + b - t)*phi_A0_t_b)/b -  &
     ((-A0 - b + t)*phi_A0_t_b)/b -  &
     (A0 - b - t)*(-(((-A0 + b - t)*tmp234)/b) -  &
     ((-A0 - b + t)*tmp235)/b + 0.5_dp*(A0 - b - t)/(b*t) + &
     &0.5_dp*(tmp234*delt_A0_t_b)/b**2 + 0.5_dp*Log_A0_q/b + &
     &0.5_dp*Log_A0_q/t - 0.5_dp*Log_b_q/t                   &
     &  - 0.5_dp*Log_t_q/b - 0.5_dp*(delt_A0_t_b* ((-2*b*(-A0 + b - t)* &
     ((A0 - b)*tmp144 + t*tmp166))/ (t*delt_A0_t_b**2) +  &
     (b*tmp143)/(t*delt_A0_t_b) +  ((A0 - b)*tmp144 + t*tmp166)/ &
     (t*delt_A0_t_b) +  ((A0 + b - t)*tmp235)/delt_A0_t_b -  &
     (2*(-A0 + b - t)*(A0 + b - t)*phi_A0_t_b)/ &
     delt_A0_t_b**2 + phi_A0_t_b/delt_A0_t_b))/ b + phi_A0_t_b/b +  &
     ((-A0 - b + t)*phi_A0_t_b)/b**2))
   DT1b = -2*mb*hb*ht*abs_mu*s2t*tmp282 - 0.5_dp*(tmp226*(-(cbe*hb*ht*sbe* &
     ((mt*tmp50)/mb - 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2t*tmp69)/mb)) + cbe**2*hb**2* &
     (0.25_dp*((1 - c2b)*(1 + c2t)) - 0.25_dp*(s2b*s2t*mt)/mb - &
     &0.25_dp*((1 + c2t)*s2b*Xb)/mb) + ht**2*sbe**2* &
     (0.25_dp*((1 + c2b)*(1 - c2t)) - 0.25_dp*(s2b*s2t*mt)/mb - &
     &0.25_dp*((1 - c2t)*s2b*Xt)/mb))) - 0.5_dp*(tmp225*(-(cbe*hb*ht*sbe* &
     ((mt*tmp53)/mb + 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2t*tmp70)/mb)) + cbe**2*hb**2* &
     (0.25_dp*((1 + c2b)*(1 + c2t)) + 0.25_dp*(s2b*s2t*mt)/mb + &
     &0.25_dp*((1 + c2t)*s2b*Xb)/mb) + ht**2*sbe**2* &
     (0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*(s2b*s2t*mt)/mb + &
     &0.25_dp*((1 - c2t)*s2b*Xt)/mb))) -  &
     (cbe*hb*ht*sbe*((mt*tmp53)/mb + 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2t*tmp96)/mb) + hb**2*sbe**2*(0.25_dp*((1 + c2b)*(1 + c2t)) + &
     &0.25_dp*(s2b*s2t*mt)/mb + &
     &0.25_dp*((1 + c2t)*s2b*Yb)/mb) + &
     &cbe**2*ht**2*(0.25_dp*((1 - c2b)*(1 - c2t)) + &
     &0.25_dp*(s2b*s2t*mt)/mb + 0.25_dp*((1 - c2t)*s2b*Yt)/mb))* &
     (-0.5_dp - 0.5_dp*(tmp237*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q)/T1 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B1_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B1 + T1)*phi_A0_T1_B1)/B1)
   DT1b = DT1b - (cbe*hb*ht*sbe* ((mt*tmp50)/mb - 0.5_dp*(s2b*s2t) + &
     &0.5_dp*(s2t*tmp95)/mb) + hb**2*sbe**2*(0.25_dp*((1 - c2b)*(1 + c2t)) - &
     &0.25_dp*(s2b*s2t*mt)/mb - &
     &0.25_dp*((1 + c2t)*s2b*Yb)/mb) + &
     &cbe**2*ht**2*(0.25_dp*((1 + c2b)*(1 - c2t)) - &
     &0.25_dp*(s2b*s2t*mt)/mb - 0.25_dp*((1 - c2t)*s2b*Yt)/mb))* &
     (-0.5_dp - 0.5_dp*(tmp239*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q)/T1 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B2 + T1)*phi_A0_T1_B2)/B2) -  (hb*ht*abs_mu*s2t* &
     (-0.5_dp - 0.5_dp*(tmp255*delt_T1_b_mu2)/mu2 + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1 + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1 + 0.5_dp*(Log_b_q*Log_mu2_q) - &
     &0.5_dp*(Log_b_q*Log_T1_q) - &
     &0.5_dp*(Log_mu2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-b - mu2 + T1)*phi_T1_b_mu2)/mu2))/mb + &
     &tmp56*(1 - (-b - mu2 + T1)*tmp282 - 0.5_dp*(tmp255*delt_T1_b_mu2)/mu2 + &
     &0.5_dp*(tmp256*delt_T1_b_mu2)/mu2 +0.5_dp*((-b + mu2 - T1)*Log_b_q)/T1 +&
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q)/T1 - &
     &0.5_dp*((-b - mu2 + T1)*Log_mu2_q)/b - &
     &0.5_dp*((-b + mu2 - T1)*Log_T1_q)/b - 3*Log_b_q + Log_b_q*Log_mu2_q -  &
     (-1 + Log_b_q)*(-1 + Log_T1_q) + Log_T1_q - Log_mu2_q*Log_T1_q +  &
     ((b - mu2 - T1)*phi_T1_b_mu2)/mu2 -  ((-b - mu2 + T1)*phi_T1_b_mu2)/mu2)
   DT2b = -(0.5_dp*(tmp231* (-(cbe*hb*ht*sbe* &
     ((mt*tmp53)/mb + 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2t*tmp69)/mb)) + cbe**2*hb**2* &
     (0.25_dp*((1 - c2b)*(1 - c2t)) + 0.25_dp*(s2b*s2t*mt)/mb - &
     &0.25_dp*((1 - c2t)*s2b*Xb)/mb) + ht**2*sbe**2* &
     (0.25_dp*((1 + c2b)*(1 + c2t)) + 0.25_dp*(s2b*s2t*mt)/mb - &
     &0.25_dp*((1 + c2t)*s2b*Xt)/mb)))) - 0.5_dp*(tmp230*(-(cbe*hb*ht*sbe* &
     ((mt*tmp50)/mb - 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2t*tmp70)/mb)) + cbe**2*hb**2* &
     (0.25_dp*((1 + c2b)*(1 - c2t)) - 0.25_dp*(s2b*s2t*mt)/mb + &
     &0.25_dp*((1 - c2t)*s2b*Xb)/mb) + ht**2*sbe**2* &
     (0.25_dp*((1 - c2b)*(1 + c2t)) - 0.25_dp*(s2b*s2t*mt)/mb + &
     &0.25_dp*((1 + c2t)*s2b*Xt)/mb))) -  &
     (cbe*hb*ht*sbe*((mt*tmp50)/mb - 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2t*tmp96)/mb) + hb**2*sbe**2*(0.25_dp*((1 + c2b)*(1 - c2t)) - &
     &0.25_dp*(s2b*s2t*mt)/mb + &
     &0.25_dp*((1 - c2t)*s2b*Yb)/mb) + &
     &cbe**2*ht**2*(0.25_dp*((1 - c2b)*(1 + c2t)) - &
     &0.25_dp*(s2b*s2t*mt)/mb + 0.25_dp*((1 + c2t)*s2b*Yt)/mb))* &
     (-0.5_dp - 0.5_dp*(tmp245*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q)/T2 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B1_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B1 + T2)*phi_A0_T2_B1)/B1)
   DT2b = DT2b - (cbe*hb*ht*sbe* ((mt*tmp53)/mb + 0.5_dp*(s2b*s2t) - &
     &0.5_dp*(s2t*tmp95)/mb) + hb**2*sbe**2*(0.25_dp*((1 - c2b)*(1 - c2t)) + &
     &0.25_dp*(s2b*s2t*mt)/mb - &
     &0.25_dp*((1 - c2t)*s2b*Yb)/mb) + &
     &cbe**2*ht**2*(0.25_dp*((1 + c2b)*(1 + c2t)) + &
     &0.25_dp*(s2b*s2t*mt)/mb - 0.25_dp*((1 + c2t)*s2b*Yt)/mb))* &
     (-0.5_dp - 0.5_dp*(tmp247*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q)/T2 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B2_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B2 + T2)*phi_A0_T2_B2)/B2) - 2*mb*hb*ht*abs_mu*s2t* &
     (((b - mu2 - T2)*tmp259)/mu2 +  ((-b - mu2 + T2)*tmp260)/mu2 - &
     &0.5_dp*(-b + mu2 - T2)/(b*T2) + 0.5_dp*Log_b_q/T2 - &
     &0.5_dp*Log_mu2_q/b - 0.5_dp*Log_mu2_q/T2 + 0.5_dp*Log_T2_q/b + &
     &0.5_dp*(delt_T2_b_mu2* ((-2*mu2*(b - mu2 - T2)* &
     ((b - mu2)*tmp152 + T2*tmp203))/ (T2*delt_T2_b_mu2**2) +  &
     (mu2*tmp154)/(T2*delt_T2_b_mu2) +  &
     ((b + mu2 - T2)*tmp260)/delt_T2_b_mu2 -  &
     (2*(b - mu2 - T2)*(b + mu2 - T2)*phi_T2_b_mu2)/ &
     delt_T2_b_mu2**2 + phi_T2_b_mu2/delt_T2_b_mu2 &
     ))/mu2 - phi_T2_b_mu2/mu2) -  (hb*ht*abs_mu*s2t* &
     (0.5_dp + 0.5_dp*(tmp259*delt_T2_b_mu2)/mu2 - &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2 - &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2 - 0.5_dp*(Log_b_q*Log_mu2_q) + &
     &0.5_dp*(Log_b_q*Log_T2_q) + &
     &0.5_dp*(Log_mu2_q*Log_T2_q) - 2*Log_T2_q +  &
     ((-b - mu2 + T2)*phi_T2_b_mu2)/mu2))/mb
   DT2b = DT2b + tmp57* (1 - 0.5_dp*(tmp259*delt_T2_b_mu2)/mu2 + &
     &0.5_dp*(tmp260*delt_T2_b_mu2)/mu2 + 0.5_dp*((-b + mu2 - T2)*Log_b_q)/T2 + &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q)/T2 - &
     &0.5_dp*((-b - mu2 + T2)*Log_mu2_q)/b - &
     &0.5_dp*((-b + mu2 - T2)*Log_T2_q)/b - 3*Log_b_q + Log_b_q*Log_mu2_q -  &
     (-1 + Log_b_q)*(-1 + Log_T2_q) + Log_T2_q - Log_mu2_q*Log_T2_q +  &
     ((b - mu2 - T2)*phi_T2_b_mu2)/mu2 -  ((-b - mu2 + T2)*phi_T2_b_mu2)/mu2 -  &
     (-b - mu2 + T2)* (-(((b - mu2 - T2)*tmp259)/mu2) -  &
     ((-b - mu2 + T2)*tmp260)/mu2 + &
     &0.5_dp*(-b + mu2 - T2)/(b*T2) - 0.5_dp*Log_b_q/T2 + &
     &0.5_dp*Log_mu2_q/b + 0.5_dp*Log_mu2_q/T2 - 0.5_dp*Log_T2_q/b - &
     &0.5_dp*(delt_T2_b_mu2* ((-2*mu2*(b - mu2 - T2)* &
     ((b - mu2)*tmp152 + T2*tmp203))/ (T2*delt_T2_b_mu2**2) +  &
     (mu2*tmp154)/(T2*delt_T2_b_mu2) +  &
     ((b + mu2 - T2)*tmp260)/delt_T2_b_mu2 -  &
     (2*(b - mu2 - T2)*(b + mu2 - T2)*&
     &phi_T2_b_mu2)/delt_T2_b_mu2**2 + &
     &phi_T2_b_mu2/delt_T2_b_mu2))/mu2 + phi_T2_b_mu2/mu2))
   DB1t = -2*hb*ht*abs_mu*s2b*mt*tmp279 - &
     &0.5_dp*(tmp128*tmp272) - 0.5_dp*(tmp132*tmp275) - &
     &tmp136*(-0.5_dp - 0.5_dp*(tmp238*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 - B1 + T1)*Log_A0_q)/B1 - 0.5_dp*(Log_A0_q*Log_B1_q) + &
     &0.5_dp*((A0 - B1 - T1)*Log_T1_q)/B1 + 0.5_dp*(Log_A0_q*Log_T1_q) - &
     &0.5_dp*(Log_B1_q*Log_T1_q) + &
     &0.5_dp*(delt_A0_T1_B1*phi_A0_T1_B1)/B1**2 + &
     &2*Log_B1_q - ((-A0 + B1 - T1)*phi_A0_T1_B1)/B1) - &
     &tmp140*(-0.5_dp - 0.5_dp*(tmp246*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 - B1 + T2)*Log_A0_q)/B1 - 0.5_dp*(Log_A0_q*Log_B1_q) + &
     &0.5_dp*((A0 - B1 - T2)*Log_T2_q)/B1 + 0.5_dp*(Log_A0_q*Log_T2_q) - &
     &0.5_dp*(Log_B1_q*Log_T2_q) + &
     &0.5_dp*(delt_A0_T2_B1*phi_A0_T2_B1)/B1**2 + &
     &2*Log_B1_q - ((-A0 + B1 - T2)*phi_A0_T2_B1)/B1) -  (hb*ht*abs_mu*s2b* &
     (-0.5_dp - 0.5_dp*(tmp252*delt_B1_t_mu2)/mu2 + &
     &0.5_dp*((-B1 - mu2 + t)*Log_mu2_q)/B1 - 0.5_dp*(Log_B1_q*Log_mu2_q) + &
     &0.5_dp*((-B1 + mu2 - t)*Log_t_q)/B1 - 0.5_dp*(Log_B1_q*Log_t_q) + &
     &0.5_dp*(Log_mu2_q*Log_t_q) + 2*Log_B1_q -  &
     ((B1 - mu2 - t)*phi_B1_t_mu2)/mu2))/mt + &
     &tmp55*(1 - (B1 - mu2 - t)*tmp279 + 0.5_dp*(tmp251*delt_B1_t_mu2)/mu2 - &
     &0.5_dp*(tmp252*delt_B1_t_mu2)/mu2-0.5_dp*((-B1 + mu2 - t)*Log_B1_q)/t - &
     &0.5_dp*((B1 - mu2 - t)*Log_mu2_q)/t + &
     &0.5_dp*((-B1 - mu2 + t)*Log_mu2_q)/B1 + &
     &0.5_dp*((-B1 + mu2 - t)*Log_t_q)/B1 + Log_B1_q - Log_B1_q*Log_mu2_q -  &
     (-1 + Log_B1_q)*(-1 + Log_t_q) - 3*Log_t_q + Log_mu2_q*Log_t_q -  &
     ((B1 - mu2 - t)*phi_B1_t_mu2)/mu2 +  ((-B1 - mu2 + t)*phi_B1_t_mu2)/mu2)
   DB2t = -(0.5_dp*(tmp127*tmp273)) - 0.5_dp*(tmp131*tmp276) - &
     &tmp135*(-0.5_dp - 0.5_dp*(tmp240*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 - B2 + T1)*Log_A0_q)/B2 - 0.5_dp*(Log_A0_q*Log_B2_q) + &
     &0.5_dp*((A0 - B2 - T1)*Log_T1_q)/B2 + 0.5_dp*(Log_A0_q*Log_T1_q) - &
     &0.5_dp*(Log_B2_q*Log_T1_q) + &
     &0.5_dp*(delt_A0_T1_B2*phi_A0_T1_B2)/B2**2 + &
     &2*Log_B2_q - ((-A0 + B2 - T1)*phi_A0_T1_B2)/B2) - &
     &tmp139*(-0.5_dp - 0.5_dp*(tmp248*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 - B2 + T2)*Log_A0_q)/B2 - 0.5_dp*(Log_A0_q*Log_B2_q) + &
     &0.5_dp*((A0 - B2 - T2)*Log_T2_q)/B2 + 0.5_dp*(Log_A0_q*Log_T2_q) - &
     &0.5_dp*(Log_B2_q*Log_T2_q) + &
     &0.5_dp*(delt_A0_T2_B2*phi_A0_T2_B2)/B2**2 + &
     &2*Log_B2_q - ((-A0 + B2 - T2)*phi_A0_T2_B2)/B2) - &
     &2*hb*ht*abs_mu*s2b*mt* (((B2 - mu2 - t)*tmp253)/mu2 +  &
     ((-B2 - mu2 + t)*tmp254)/mu2 - &
     &0.5_dp*(-B2 + mu2 - t)/(B2*t) + 0.5_dp*Log_B2_q/t - &
     &0.5_dp*Log_mu2_q/B2 - 0.5_dp*Log_mu2_q/t + 0.5_dp*Log_t_q/B2 + &
     &0.5_dp*(delt_B2_t_mu2* ((-2*mu2*(-B2 - mu2 + t)* &
     (B2*tmp161 + (-mu2 + t)*tmp162))/ (B2*delt_B2_t_mu2**2) +  &
     (mu2*tmp164)/(B2*delt_B2_t_mu2) +  &
     ((-B2 + mu2 + t)*tmp253)/delt_B2_t_mu2 -  &
     (2*(-B2 - mu2 + t)*(-B2 + mu2 + t)*&
     &phi_B2_t_mu2)/delt_B2_t_mu2**2 + &
     &phi_B2_t_mu2/delt_B2_t_mu2))/mu2 - phi_B2_t_mu2/mu2) -  &
     (hb*ht*abs_mu*s2b* (0.5_dp + 0.5_dp*(tmp254*delt_B2_t_mu2)/mu2 - &
     &0.5_dp*((-B2 - mu2 + t)*Log_mu2_q)/B2 + 0.5_dp*(Log_B2_q*Log_mu2_q) - &
     &0.5_dp*((-B2 + mu2 - t)*Log_t_q)/B2 + 0.5_dp*(Log_B2_q*Log_t_q) - &
     &0.5_dp*(Log_mu2_q*Log_t_q) - 2*Log_B2_q +  &
     ((B2 - mu2 - t)*phi_B2_t_mu2)/mu2))/mt
   DB2t = DB2t + tmp54* (1 + 0.5_dp*(tmp253*delt_B2_t_mu2)/mu2 - &
     &0.5_dp*(tmp254*delt_B2_t_mu2)/mu2-0.5_dp*((-B2 + mu2 - t)*Log_B2_q)/t - &
     &0.5_dp*((B2 - mu2 - t)*Log_mu2_q)/t + &
     &0.5_dp*((-B2 - mu2 + t)*Log_mu2_q)/B2 + &
     &0.5_dp*((-B2 + mu2 - t)*Log_t_q)/B2 + Log_B2_q - Log_B2_q*Log_mu2_q -  &
     (-1 + Log_B2_q)*(-1 + Log_t_q) - 3*Log_t_q + Log_mu2_q*Log_t_q -  &
     ((B2 - mu2 - t)*phi_B2_t_mu2)/mu2 +((-B2 - mu2 + t)*phi_B2_t_mu2)/mu2 -  &
     (B2 - mu2 - t)* (-(((B2 - mu2 - t)*tmp253)/mu2) -  &
     ((-B2 - mu2 + t)*tmp254)/mu2 + &
     &0.5_dp*(-B2 + mu2 - t)/(B2*t) - 0.5_dp*Log_B2_q/t + &
     &0.5_dp*Log_mu2_q/B2 + 0.5_dp*Log_mu2_q/t - 0.5_dp*Log_t_q/B2 - &
     &0.5_dp*(delt_B2_t_mu2* ((-2*mu2*(-B2 - mu2 + t)* &
     (B2*tmp161 + (-mu2 + t)*tmp162))/ (B2*delt_B2_t_mu2**2) +  &
     (mu2*tmp164)/(B2*delt_B2_t_mu2) +  &
     ((-B2 + mu2 + t)*tmp253)/delt_B2_t_mu2 -  &
     (2*(-B2 - mu2 + t)*(-B2 + mu2 + t)*&
     &phi_B2_t_mu2)/delt_B2_t_mu2**2 + &
     &phi_B2_t_mu2/delt_B2_t_mu2))/mu2 + phi_B2_t_mu2/mu2))
   DT1B1 = ht**2*(0.25_dp*((1 + c2b)*(1 - c2t)) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*(-1 + Log_T1_q)) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*(-1 + Log_B1_q)* (-1 + Log_T1_q))) + &
     &hb**2*(0.25_dp*((1 - c2b)*(1 + c2t)) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*(-1 + Log_T1_q)) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*(-1 + Log_B1_q)* (-1 + Log_T1_q))) - &
     &0.5_dp*(tmp130*((2*(-B1 + T1))/((1 - B1/T1)*T1**2) -  &
     (2*B1*tmp175)/((1 - B1/T1)*T1**2) -  (2*tmp175)/((1 - B1/T1)*T1) +  &
     (2*B1*(-B1 + T1)*tmp175)/((1 - B1/T1)**2*T1**3) +  &
     (2*(-B1 + T1)*tmp175)/((1 - B1/T1)*T1**2) +  &
     (-2 - 2*Log_B1_q)/T1 + (2*Log_T1_q)/T1)) - &
     &tmp138*(-(((-A0 + B1 - T1)*tmp237)/B1) -  ((-A0 - B1 + T1)*tmp238)/B1 + &
     &0.5_dp*(A0 - B1 - T1)/(B1*T1) + &
     &0.5_dp*(tmp237*delt_A0_T1_B1)/B1**2 + 0.5_dp*Log_A0_q/B1 + &
     &0.5_dp*Log_A0_q/T1 - 0.5_dp*Log_B1_q/T1 - 0.5_dp*Log_T1_q/B1 - &
     &0.5_dp*(delt_A0_T1_B1* ((-2*B1*(-A0 + B1 - T1)* &
     ((A0 - B1)*tmp146 + T1*tmp183))/ (T1*delt_A0_T1_B1**2) +  &
     ((A0 - B1)*tmp146 + T1*tmp183)/ (T1*delt_A0_T1_B1) +  &
     ((A0 + B1 - T1)*tmp238)/delt_A0_T1_B1 +  &
     (B1*((A0 - B1)/B1 - T1/B1 + Log_A0_q - &
     &Log_B1_q))/(T1*delt_A0_T1_B1) -  &
     (2*(-A0 + B1 - T1)*(A0 + B1 - T1)*phi_A0_T1_B1)/ &
     delt_A0_T1_B1**2 + phi_A0_T1_B1/delt_A0_T1_B1 &
     ))/B1 + phi_A0_T1_B1/B1 +  ((-A0 - B1 + T1)*phi_A0_T1_B1)/B1**2)
   DT2B1 = hb**2*(0.25_dp*((1 - c2b)*(1 - c2t)) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*(-1 + Log_T2_q)) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*(-1 + Log_B1_q)* (-1 + Log_T2_q))) + &
     &ht**2*(0.25_dp*((1 + c2b)*(1 + c2t)) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*(-1 + Log_B1_q)) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*(-1 + Log_T2_q)) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*(-1 + Log_B1_q)* (-1 + Log_T2_q))) - &
     &0.5_dp*(tmp134*((2*(-B1 + T2))/((1 - B1/T2)*T2**2) -  &
     (2*B1*tmp191)/((1 - B1/T2)*T2**2) -  (2*tmp191)/((1 - B1/T2)*T2) +  &
     (2*B1*(-B1 + T2)*tmp191)/((1 - B1/T2)**2*T2**3) +  &
     (2*(-B1 + T2)*tmp191)/((1 - B1/T2)*T2**2) +  &
     (-2 - 2*Log_B1_q)/T2 + (2*Log_T2_q)/T2)) - &
     &tmp142*(-(((-A0 + B1 - T2)*tmp245)/B1) -  ((-A0 - B1 + T2)*tmp246)/B1 + &
     &0.5_dp*(A0 - B1 - T2)/(B1*T2) + &
     &0.5_dp*(tmp245*delt_A0_T2_B1)/B1**2 + 0.5_dp*Log_A0_q/B1 + &
     &0.5_dp*Log_A0_q/T2 - 0.5_dp*Log_B1_q/T2 - 0.5_dp*Log_T2_q/B1 - &
     &0.5_dp*(delt_A0_T2_B1* ((-2*B1*(-A0 + B1 - T2)* &
     ((A0 - B1)*tmp146 + T2*tmp201))/ (T2*delt_A0_T2_B1**2) +  &
     ((A0 - B1)*tmp146 + T2*tmp201)/ (T2*delt_A0_T2_B1) +  &
     ((A0 + B1 - T2)*tmp246)/delt_A0_T2_B1 +  &
     (B1*((A0 - B1)/B1 - T2/B1 + Log_A0_q - &
     &Log_B1_q))/(T2*delt_A0_T2_B1) -  &
     (2*(-A0 + B1 - T2)*(A0 + B1 - T2)*phi_A0_T2_B1)/ &
     delt_A0_T2_B1**2 + phi_A0_T2_B1/delt_A0_T2_B1 &
     ))/B1 + phi_A0_T2_B1/B1 +  ((-A0 - B1 + T2)*phi_A0_T2_B1)/B1**2)
   DT1B2 = ht**2*(0.25_dp*((1 - c2b)*(1 - c2t)) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*(-1 + Log_B2_q)) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*(-1 + Log_T1_q)) + &
     &0.25_dp*((1 - c2b)*(1 - c2t)*(-1 + Log_B2_q)* (-1 + Log_T1_q))) + &
     &hb**2*(0.25_dp*((1 + c2b)*(1 + c2t)) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*(-1 + Log_B2_q)) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*(-1 + Log_T1_q)) + &
     &0.25_dp*((1 + c2b)*(1 + c2t)*(-1 + Log_B2_q)* (-1 + Log_T1_q))) - &
     &0.5_dp*(tmp129*((2*(-B2 + T1))/((1 - B2/T1)*T1**2) -  &
     (2*B2*tmp177)/((1 - B2/T1)*T1**2) -  (2*tmp177)/((1 - B2/T1)*T1) +  &
     (2*B2*(-B2 + T1)*tmp177)/((1 - B2/T1)**2*T1**3) +  &
     (2*(-B2 + T1)*tmp177)/((1 - B2/T1)*T1**2) +  &
     (-2 - 2*Log_B2_q)/T1 + (2*Log_T1_q)/T1)) - &
     &tmp137*(-(((-A0 + B2 - T1)*tmp239)/B2) -  ((-A0 - B2 + T1)*tmp240)/B2 + &
     &0.5_dp*(A0 - B2 - T1)/(B2*T1) + &
     &0.5_dp*(tmp239*delt_A0_T1_B2)/B2**2 + 0.5_dp*Log_A0_q/B2 + &
     &0.5_dp*Log_A0_q/T1 - 0.5_dp*Log_B2_q/T1 - 0.5_dp*Log_T1_q/B2 - &
     &0.5_dp*(delt_A0_T1_B2* ((-2*B2*(-A0 + B2 - T1)* &
     ((A0 - B2)*tmp149 + T1*tmp184))/ (T1*delt_A0_T1_B2**2) +  &
     ((A0 - B2)*tmp149 + T1*tmp184)/ (T1*delt_A0_T1_B2) +  &
     ((A0 + B2 - T1)*tmp240)/delt_A0_T1_B2 +  &
     (B2*((A0 - B2)/B2 - T1/B2 + Log_A0_q - &
     &Log_B2_q))/(T1*delt_A0_T1_B2) -  &
     (2*(-A0 + B2 - T1)*(A0 + B2 - T1)*phi_A0_T1_B2)/ &
     delt_A0_T1_B2**2 + phi_A0_T1_B2/delt_A0_T1_B2 &
     ))/B2 + phi_A0_T1_B2/B2 +  ((-A0 - B2 + T1)*phi_A0_T1_B2)/B2**2)
   DT2B2 = hb**2*(0.25_dp*((1 + c2b)*(1 - c2t)) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*(-1 + Log_B2_q)) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*(-1 + Log_T2_q)) + &
     &0.25_dp*((1 + c2b)*(1 - c2t)*(-1 + Log_B2_q)* (-1 + Log_T2_q))) + &
     &ht**2*(0.25_dp*((1 - c2b)*(1 + c2t)) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*(-1 + Log_B2_q)) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*(-1 + Log_T2_q)) + &
     &0.25_dp*((1 - c2b)*(1 + c2t)*(-1 + Log_B2_q)* (-1 + Log_T2_q))) - &
     &0.5_dp*(tmp133*((2*(-B2 + T2))/((1 - B2/T2)*T2**2) -  &
     (2*B2*tmp193)/((1 - B2/T2)*T2**2) -  (2*tmp193)/((1 - B2/T2)*T2) +  &
     (2*B2*(-B2 + T2)*tmp193)/((1 - B2/T2)**2*T2**3) +  &
     (2*(-B2 + T2)*tmp193)/((1 - B2/T2)*T2**2) +  &
     (-2 - 2*Log_B2_q)/T2 + (2*Log_T2_q)/T2)) - &
     &tmp141*(-(((-A0 + B2 - T2)*tmp247)/B2) -  ((-A0 - B2 + T2)*tmp248)/B2 + &
     &0.5_dp*(A0 - B2 - T2)/(B2*T2) + &
     &0.5_dp*(tmp247*delt_A0_T2_B2)/B2**2 + 0.5_dp*Log_A0_q/B2 + &
     &0.5_dp*Log_A0_q/T2 - 0.5_dp*Log_B2_q/T2 - 0.5_dp*Log_T2_q/B2 - &
     &0.5_dp*(delt_A0_T2_B2* ((-2*B2*(-A0 + B2 - T2)* &
     ((A0 - B2)*tmp149 + T2*tmp202))/ (T2*delt_A0_T2_B2**2) +  &
     ((A0 - B2)*tmp149 + T2*tmp202)/ (T2*delt_A0_T2_B2) +  &
     ((A0 + B2 - T2)*tmp248)/delt_A0_T2_B2 +  &
     (B2*((A0 - B2)/B2 - T2/B2 + Log_A0_q - &
     &Log_B2_q))/(T2*delt_A0_T2_B2) -  &
     (2*(-A0 + B2 - T2)*(A0 + B2 - T2)*phi_A0_T2_B2)/ &
     delt_A0_T2_B2**2 + phi_A0_T2_B2/delt_A0_T2_B2 &
     ))/B2 + phi_A0_T2_B2/B2 +  ((-A0 - B2 + T2)*phi_A0_T2_B2)/B2**2)
   Dbc2t = 0.5_dp*(hb*ht*abs_mu*tmp217)/(mb*s2t) - &
     &0.5_dp*(tmp227*(-(cbe*hb*ht*sbe* &
     ((mt*tmp49)/mb - 0.25_dp*s2b/s2t - &
     &0.25_dp*tmp70/(mb*s2t))) + cbe**2*hb**2* (0.125_dp*(1 + c2b)/c2t - &
     &0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Xb)/(mb*c2t)) + ht**2*sbe**2* &
     (-(0.125_dp*(1 - c2b)/c2t) - 0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Xt)/(mb*c2t)))) - 0.5_dp*(tmp233*(-(cbe*hb*ht*sbe* &
     ((mt*tmp49)/mb - 0.25_dp*s2b/s2t + &
     &0.25_dp*tmp69/(mb*s2t))) + cbe**2*hb**2* &
     (-(0.125_dp*(1 - c2b)/c2t) - 0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Xb)/(mb*c2t)) + ht**2*sbe**2* &
     (0.125_dp*(1 + c2b)/c2t - 0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Xt)/(mb*c2t)))) - 0.5_dp*(tmp232*(-(cbe*hb*ht*sbe* &
     ((mt*tmp48)/mb + 0.25_dp*s2b/s2t + &
     &0.25_dp*tmp70/(mb*s2t))) + cbe**2*hb**2* &
     (-(0.125_dp*(1 + c2b)/c2t) + 0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Xb)/(mb*c2t)) + ht**2*sbe**2* &
     (0.125_dp*(1 - c2b)/c2t + 0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Xt)/(mb*c2t)))) - 0.5_dp*(tmp228*(-(cbe*hb*ht*sbe* &
     ((mt*tmp48)/mb + 0.25_dp*s2b/s2t - &
     &0.25_dp*tmp69/(mb*s2t))) + cbe**2*hb**2* (0.125_dp*(1 - c2b)/c2t + &
     &0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Xb)/(mb*c2t)) + ht**2*sbe**2* &
     (-(0.125_dp*(1 + c2b)/c2t) + 0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Xt)/(mb*c2t))))
   Dbc2t = Dbc2t - tmp210* &
     (cbe*hb*ht*sbe*((mt*tmp49)/mb - 0.25_dp*s2b/s2t - &
     &0.25_dp*tmp96/(mb*s2t)) + hb**2*sbe**2*(0.125_dp*(1 + c2b)/c2t - &
     &0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Yb)/(mb*c2t)) + &
     &cbe**2*ht**2*(-(0.125_dp*(1 - c2b)/c2t) - &
     &0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Yt)/(mb*c2t))) - tmp213*(cbe*hb*ht*sbe* &
     ((mt*tmp49)/mb - 0.25_dp*s2b/s2t + &
     &0.25_dp*tmp95/(mb*s2t)) + hb**2*sbe**2*(-(0.125_dp*(1 - c2b)/c2t) - &
     &0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Yb)/(mb*c2t)) + cbe**2*ht**2*(0.125_dp*(1 + c2b)/c2t - &
     &0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Yt)/(mb*c2t))) - tmp212*(cbe*hb*ht*sbe* &
     ((mt*tmp48)/mb + 0.25_dp*s2b/s2t + &
     &0.25_dp*tmp96/(mb*s2t)) + hb**2*sbe**2*(-(0.125_dp*(1 + c2b)/c2t) + &
     &0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Yb)/(mb*c2t)) + cbe**2*ht**2*(0.125_dp*(1 - c2b)/c2t + &
     &0.125_dp*(s2b*mt)/(mb*s2t) + &
     &0.125_dp*(s2b*Yt)/(mb*c2t))) - tmp211*(cbe*hb*ht*sbe* &
     ((mt*tmp48)/mb + 0.25_dp*s2b/s2t - &
     &0.25_dp*tmp95/(mb*s2t)) + hb**2*sbe**2*(0.125_dp*(1 - c2b)/c2t + &
     &0.125_dp*(s2b*mt)/(mb*s2t) - &
     &0.125_dp*(s2b*Yb)/(mb*c2t)) + &
     &cbe**2*ht**2*(-(0.125_dp*(1 + c2b)/c2t) + &
     &0.125_dp*(s2b*mt)/(mb*s2t) + 0.125_dp*(s2b*Yt)/(mb*c2t)))
   Dbc2t = Dbc2t + tmp1* (-(2.5_dp*(b + mu2 + T1)) + &
     &0.5_dp*((-b - mu2 + T1)*Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T1)*Log_b_q*Log_T1_q) + &
     &0.5_dp*((b - mu2 - T1)*Log_mu2_q*Log_T1_q) - &
     &0.5_dp*(delt_T1_b_mu2*phi_T1_b_mu2)/mu2 + &
     &2*b*Log_b_q + mu2*(-1 + Log_mu2_q) + &
     &mu2*(-1 + Log_b_q)*(-1 + Log_mu2_q) + &
     &2*mu2*Log_mu2_q - T1*(-1 + Log_T1_q) - &
     &T1*(-1 + Log_b_q)*(-1 + Log_T1_q) + 2*T1*Log_T1_q -  (-b - mu2 + T1)* &
     (-0.5_dp - 0.5_dp*(tmp256*delt_T1_b_mu2)/mu2 + &
     &0.5_dp*((-b - mu2 + T1)*Log_mu2_q)/b - 0.5_dp*(Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T1)*Log_T1_q)/b - 0.5_dp*(Log_b_q*Log_T1_q) + &
     &0.5_dp*(Log_mu2_q*Log_T1_q) + 2*Log_b_q -  &
     ((b - mu2 - T1)*phi_T1_b_mu2)/mu2)) +  (mb*hb*ht*abs_mu* &
     (-(0.5_dp*(tmp256*delt_T1_b_mu2)/mu2) + &
     &0.5_dp*(tmp260*delt_T2_b_mu2)/mu2 + &
     &0.5_dp*((-b - mu2 + T1)*Log_mu2_q)/b - &
     &0.5_dp*((-b - mu2 + T2)*Log_mu2_q)/b + &
     &0.5_dp*((-b + mu2 - T1)*Log_T1_q)/b - 0.5_dp*(Log_b_q*Log_T1_q) + &
     &0.5_dp*(Log_mu2_q*Log_T1_q) - 0.5_dp*((-b + mu2 - T2)*Log_T2_q)/b + &
     &0.5_dp*(Log_b_q*Log_T2_q) - 0.5_dp*(Log_mu2_q*Log_T2_q) -  &
     ((b - mu2 - T1)*phi_T1_b_mu2)/mu2 +  &
     ((b - mu2 - T2)*phi_T2_b_mu2)/mu2))/s2t
   Dbc2t = Dbc2t + tmp2* (-(2.5_dp*(b + mu2 + T2)) + &
     &0.5_dp*((-b - mu2 + T2)*Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T2)*Log_b_q*Log_T2_q) + &
     &0.5_dp*((b - mu2 - T2)*Log_mu2_q*Log_T2_q) - &
     &0.5_dp*(delt_T2_b_mu2*phi_T2_b_mu2)/mu2 + &
     &2*b*Log_b_q + mu2*(-1 + Log_mu2_q) + &
     &mu2*(-1 + Log_b_q)*(-1 + Log_mu2_q) + &
     &2*mu2*Log_mu2_q - T2*(-1 + Log_T2_q) - &
     &T2*(-1 + Log_b_q)*(-1 + Log_T2_q) + 2*T2*Log_T2_q -  (-b - mu2 + T2)* &
     (-0.5_dp - 0.5_dp*(tmp260*delt_T2_b_mu2)/mu2 + &
     &0.5_dp*((-b - mu2 + T2)*Log_mu2_q)/b - 0.5_dp*(Log_b_q*Log_mu2_q) + &
     &0.5_dp*((-b + mu2 - T2)*Log_T2_q)/b - 0.5_dp*(Log_b_q*Log_T2_q) + &
     &0.5_dp*(Log_mu2_q*Log_T2_q) + 2*Log_b_q -  &
     ((b - mu2 - T2)*phi_T2_b_mu2)/mu2))
   DB1c2t = -(0.5_dp*(tmp120*tmp272)) - 0.5_dp*(tmp122*tmp275) + &
     &hb**2*(0.125_dp*((1 - c2b)*T1*(-1 + Log_T1_q))/c2t + &
     &0.125_dp*((1 - c2b)*T1*(-1 + Log_B1_q)*(-1 + Log_T1_q))/ &
     c2t - 0.125_dp*((1 - c2b)*T2*(-1 + Log_T2_q))/c2t - &
     &0.125_dp*((1 - c2b)*T2*(-1 + Log_B1_q)*(-1 + Log_T2_q))/ c2t) + ht**2* &
     (-(0.125_dp*((1 + c2b)*T1*(-1 + Log_T1_q))/c2t) - &
     &0.125_dp*((1 + c2b)*T1*(-1 + Log_B1_q)*(-1 + Log_T1_q))/ &
     c2t + 0.125_dp*((1 + c2b)*T2*(-1 + Log_T2_q))/c2t + &
     &0.125_dp*((1 + c2b)*T2*(-1 + Log_B1_q)*(-1 + Log_T2_q))/ c2t) - tmp124* &
     (-0.5_dp - 0.5_dp*(tmp238*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 - B1 + T1)*Log_A0_q)/B1 - 0.5_dp*(Log_A0_q*Log_B1_q) + &
     &0.5_dp*((A0 - B1 - T1)*Log_T1_q)/B1 + 0.5_dp*(Log_A0_q*Log_T1_q) - &
     &0.5_dp*(Log_B1_q*Log_T1_q) + &
     &0.5_dp*(delt_A0_T1_B1*phi_A0_T1_B1)/B1**2 + &
     &2*Log_B1_q - ((-A0 + B1 - T1)*phi_A0_T1_B1)/B1) - &
     &tmp126*(-0.5_dp - 0.5_dp*(tmp246*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 - B1 + T2)*Log_A0_q)/B1 - 0.5_dp*(Log_A0_q*Log_B1_q) + &
     &0.5_dp*((A0 - B1 - T2)*Log_T2_q)/B1 + 0.5_dp*(Log_A0_q*Log_T2_q) - &
     &0.5_dp*(Log_B1_q*Log_T2_q) + &
     &0.5_dp*(delt_A0_T2_B1*phi_A0_T2_B1)/B1**2 + &
     &2*Log_B1_q - ((-A0 + B1 - T2)*phi_A0_T2_B1)/B1)
   DB2c2t = -(0.5_dp*(tmp119*tmp273)) - 0.5_dp*(tmp121*tmp276) + &
     &ht**2*(-(0.125_dp*((1 - c2b)*T1*(-1 + Log_T1_q))/c2t) - &
     &0.125_dp*((1 - c2b)*T1*(-1 + Log_B2_q)*(-1 + Log_T1_q))/ &
     c2t + 0.125_dp*((1 - c2b)*T2*(-1 + Log_T2_q))/c2t + &
     &0.125_dp*((1 - c2b)*T2*(-1 + Log_B2_q)*(-1 + Log_T2_q))/ c2t) + hb**2* &
     (0.125_dp*((1 + c2b)*T1*(-1 + Log_T1_q))/c2t + &
     &0.125_dp*((1 + c2b)*T1*(-1 + Log_B2_q)*(-1 + Log_T1_q))/ &
     c2t - 0.125_dp*((1 + c2b)*T2*(-1 + Log_T2_q))/c2t - &
     &0.125_dp*((1 + c2b)*T2*(-1 + Log_B2_q)*(-1 + Log_T2_q))/ c2t) - tmp123* &
     (-0.5_dp - 0.5_dp*(tmp240*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 - B2 + T1)*Log_A0_q)/B2 - 0.5_dp*(Log_A0_q*Log_B2_q) + &
     &0.5_dp*((A0 - B2 - T1)*Log_T1_q)/B2 + 0.5_dp*(Log_A0_q*Log_T1_q) - &
     &0.5_dp*(Log_B2_q*Log_T1_q) + &
     &0.5_dp*(delt_A0_T1_B2*phi_A0_T1_B2)/B2**2 + &
     &2*Log_B2_q - ((-A0 + B2 - T1)*phi_A0_T1_B2)/B2) - &
     &tmp125*(-0.5_dp - 0.5_dp*(tmp248*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 - B2 + T2)*Log_A0_q)/B2 - 0.5_dp*(Log_A0_q*Log_B2_q) + &
     &0.5_dp*((A0 - B2 - T2)*Log_T2_q)/B2 + 0.5_dp*(Log_A0_q*Log_T2_q) - &
     &0.5_dp*(Log_B2_q*Log_T2_q) + &
     &0.5_dp*(delt_A0_T2_B2*phi_A0_T2_B2)/B2**2 + &
     &2*Log_B2_q - ((-A0 + B2 - T2)*phi_A0_T2_B2)/B2)
   DT1c2b = -(0.5_dp*(tmp226* (cbe**2*hb**2* &
     (-(0.125_dp*(b*(1 + c2t))/c2b) + 0.25_dp*(mb*s2t*mt)/s2b + &
     &0.125_dp*((1 - c2t)*t)/c2b + 0.25_dp*(mb*(1 + c2t)*Xb)/s2b + &
     &0.25_dp*(s2t*mt*Xb)/c2b + 0.125_dp*((1 + c2t)*Xb**2)/c2b) - &
     &cbe*hb*ht*sbe* (mb*s2t*tmp13 + 2*mb*mt*tmp51 + &
     &0.25_dp*(s2t*(b + t))/s2b + &
     &0.5_dp*(mt*tmp71)/s2b + 0.25_dp*(s2t*Xb*Xt)/s2b)+ht**2*sbe**2* &
     (0.125_dp*(b*(1 - c2t))/c2b + 0.25_dp*(mb*s2t*mt)/s2b - &
     &0.125_dp*((1 + c2t)*t)/c2b + 0.25_dp*(mb*(1 - c2t)*Xt)/s2b - &
     &0.25_dp*(s2t*mt*Xt)/c2b - 0.125_dp*((1 - c2t)*Xt**2)/c2b)))) - &
     &0.5_dp*(tmp225*(cbe**2*hb**2* (0.125_dp*(b*(1 + c2t))/c2b - &
     &0.25_dp*(mb*s2t*mt)/s2b - 0.125_dp*((1 - c2t)*t)/c2b - &
     &0.25_dp*(mb*(1 + c2t)*Xb)/s2b - 0.25_dp*(s2t*mt*Xb)/c2b - &
     &0.125_dp*((1 + c2t)*Xb**2)/c2b) - cbe*hb*ht*sbe* &
     (mb*s2t*tmp14 + 2*mb*mt*tmp52 - &
     &0.25_dp*(s2t*(b + t))/s2b - &
     &0.5_dp*(mt*tmp71)/s2b - 0.25_dp*(s2t*Xb*Xt)/s2b) + ht**2*sbe**2* &
     (-(0.125_dp*(b*(1 - c2t))/c2b) - 0.25_dp*(mb*s2t*mt)/s2b + &
     &0.125_dp*((1 + c2t)*t)/c2b - 0.25_dp*(mb*(1 - c2t)*Xt)/s2b + &
     &0.25_dp*(s2t*mt*Xt)/c2b + 0.125_dp*((1 - c2t)*Xt**2)/c2b))) + &
     &ht**2*(0.125_dp*(B1*(1 - c2t)*(-1 + Log_B1_q))/c2b - &
     &0.125_dp*(B2*(1 - c2t)*(-1 + Log_B2_q))/c2b + &
     &0.125_dp*(B1*(1 - c2t)*(-1 + Log_B1_q)*(-1 + Log_T1_q))/ &
     c2b - 0.125_dp*(B2*(1 - c2t)*(-1 + Log_B2_q)* (-1 + Log_T1_q))/c2b)
   DT1c2b = DT1c2b + hb**2*(-(0.125_dp*(B1*(1 + c2t)*(-1 + Log_B1_q))/c2b) + &
     &0.125_dp*(B2*(1 + c2t)*(-1 + Log_B2_q))/c2b - &
     &0.125_dp*(B1*(1 + c2t)*(-1 + Log_B1_q)*(-1 + Log_T1_q))/ &
     c2b + 0.125_dp*(B2*(1 + c2t)*(-1 + Log_B2_q)* (-1 + Log_T1_q))/c2b) -  &
     (hb**2*sbe**2*(0.125_dp*(b*(1 + c2t))/c2b - &
     &0.25_dp*(mb*s2t*mt)/s2b - 0.125_dp*((1 - c2t)*t)/c2b - &
     &0.25_dp*(mb*(1 + c2t)*Yb)/s2b - 0.25_dp*(s2t*mt*Yb)/c2b - &
     &0.125_dp*((1 + c2t)*Yb**2)/c2b) + cbe*hb*ht*sbe*(mb*s2t*tmp32 + &
     &2*mb*mt*tmp52 - 0.25_dp*(s2t*(b + t))/s2b - &
     &0.5_dp*(mt*tmp97)/s2b - 0.25_dp*(s2t*Yb*Yt)/s2b) + &
     &cbe**2*ht**2*(-(0.125_dp*(b*(1 - c2t))/c2b) - &
     &0.25_dp*(mb*s2t*mt)/s2b + 0.125_dp*((1 + c2t)*t)/c2b - &
     &0.25_dp*(mb*(1 - c2t)*Yt)/s2b + 0.25_dp*(s2t*mt*Yt)/c2b + &
     &0.125_dp*((1 - c2t)*Yt**2)/c2b))* &
     (-0.5_dp - 0.5_dp*(tmp237*delt_A0_T1_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B1 - T1)*Log_B1_q)/T1 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B1_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B1 + T1)*phi_A0_T1_B1)/B1)
   DT1c2b = DT1c2b -  (hb**2*sbe**2*(-(0.125_dp*(b*(1 + c2t))/c2b) + &
     &0.25_dp*(mb*s2t*mt)/s2b + 0.125_dp*((1 - c2t)*t)/c2b + &
     &0.25_dp*(mb*(1 + c2t)*Yb)/s2b + 0.25_dp*(s2t*mt*Yb)/c2b + &
     &0.125_dp*((1 + c2t)*Yb**2)/c2b) + cbe*hb*ht*sbe*(mb*s2t*tmp31 + &
     &2*mb*mt*tmp51 + 0.25_dp*(s2t*(b + t))/s2b + &
     &0.5_dp*(mt*tmp97)/s2b + 0.25_dp*(s2t*Yb*Yt)/s2b) + &
     &cbe**2*ht**2*(0.125_dp*(b*(1 - c2t))/c2b + &
     &0.25_dp*(mb*s2t*mt)/s2b - 0.125_dp*((1 + c2t)*t)/c2b + &
     &0.25_dp*(mb*(1 - c2t)*Yt)/s2b - 0.25_dp*(s2t*mt*Yt)/c2b - &
     &0.125_dp*((1 - c2t)*Yt**2)/c2b))* &
     (-0.5_dp - 0.5_dp*(tmp239*delt_A0_T1_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T1)*Log_A0_q)/T1 + &
     &0.5_dp*((A0 - B2 - T1)*Log_B2_q)/T1 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T1_q) - 0.5_dp*(Log_B2_q*Log_T1_q) + 2*Log_T1_q -  &
     ((-A0 - B2 + T1)*phi_A0_T1_B2)/B2)
   DT2c2b = -(0.5_dp*(tmp231* (cbe**2*hb**2* &
     (-(0.125_dp*(b*(1 - c2t))/c2b) - 0.25_dp*(mb*s2t*mt)/s2b + &
     &0.125_dp*((1 + c2t)*t)/c2b + 0.25_dp*(mb*(1 - c2t)*Xb)/s2b - &
     &0.25_dp*(s2t*mt*Xb)/c2b + 0.125_dp*((1 - c2t)*Xb**2)/c2b) - &
     &cbe*hb*ht*sbe* (-(mb*s2t*tmp13) + 2*mb*mt*tmp52 - &
     &0.25_dp*(s2t*(b + t))/s2b + &
     &0.5_dp*(mt*tmp72)/s2b - 0.25_dp*(s2t*Xb*Xt)/s2b)+ht**2*sbe**2* &
     (0.125_dp*(b*(1 + c2t))/c2b - 0.25_dp*(mb*s2t*mt)/s2b - &
     &0.125_dp*((1 - c2t)*t)/c2b + 0.25_dp*(mb*(1 + c2t)*Xt)/s2b + &
     &0.25_dp*(s2t*mt*Xt)/c2b - 0.125_dp*((1 + c2t)*Xt**2)/c2b)))) - &
     &0.5_dp*(tmp230*(cbe**2*hb**2* (0.125_dp*(b*(1 - c2t))/c2b + &
     &0.25_dp*(mb*s2t*mt)/s2b - 0.125_dp*((1 + c2t)*t)/c2b - &
     &0.25_dp*(mb*(1 - c2t)*Xb)/s2b + 0.25_dp*(s2t*mt*Xb)/c2b - &
     &0.125_dp*((1 - c2t)*Xb**2)/c2b) - cbe*hb*ht*sbe* &
     (-(mb*s2t*tmp14) + 2*mb*mt*tmp51 + &
     &0.25_dp*(s2t*(b + t))/s2b - &
     &0.5_dp*(mt*tmp72)/s2b + 0.25_dp*(s2t*Xb*Xt)/s2b) + ht**2*sbe**2* &
     (-(0.125_dp*(b*(1 + c2t))/c2b) + 0.25_dp*(mb*s2t*mt)/s2b + &
     &0.125_dp*((1 - c2t)*t)/c2b - 0.25_dp*(mb*(1 + c2t)*Xt)/s2b - &
     &0.25_dp*(s2t*mt*Xt)/c2b + 0.125_dp*((1 + c2t)*Xt**2)/c2b))) + &
     &hb**2*(-(0.125_dp*(B1*(1 - c2t)*(-1 + Log_B1_q))/c2b) + &
     &0.125_dp*(B2*(1 - c2t)*(-1 + Log_B2_q))/c2b - &
     &0.125_dp*(B1*(1 - c2t)*(-1 + Log_B1_q)*(-1 + Log_T2_q))/ &
     c2b + 0.125_dp*(B2*(1 - c2t)*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2b)
   DT2c2b = DT2c2b + ht**2*(0.125_dp*(B1*(1 + c2t)*(-1 + Log_B1_q))/c2b - &
     &0.125_dp*(B2*(1 + c2t)*(-1 + Log_B2_q))/c2b + &
     &0.125_dp*(B1*(1 + c2t)*(-1 + Log_B1_q)*(-1 + Log_T2_q))/ &
     c2b - 0.125_dp*(B2*(1 + c2t)*(-1 + Log_B2_q)* (-1 + Log_T2_q))/c2b) -  &
     (hb**2*sbe**2*(0.125_dp*(b*(1 - c2t))/c2b + &
     &0.25_dp*(mb*s2t*mt)/s2b - 0.125_dp*((1 + c2t)*t)/c2b - &
     &0.25_dp*(mb*(1 - c2t)*Yb)/s2b + 0.25_dp*(s2t*mt*Yb)/c2b - &
     &0.125_dp*((1 - c2t)*Yb**2)/c2b) + cbe*hb*ht*sbe*(-(mb*s2t*tmp32) + &
     &2*mb*mt*tmp51 + 0.25_dp*(s2t*(b + t))/s2b - &
     &0.5_dp*(mt*tmp98)/s2b + 0.25_dp*(s2t*Yb*Yt)/s2b) + &
     &cbe**2*ht**2*(-(0.125_dp*(b*(1 + c2t))/c2b) + &
     &0.25_dp*(mb*s2t*mt)/s2b + 0.125_dp*((1 - c2t)*t)/c2b - &
     &0.25_dp*(mb*(1 + c2t)*Yt)/s2b - 0.25_dp*(s2t*mt*Yt)/c2b + &
     &0.125_dp*((1 + c2t)*Yt**2)/c2b))* &
     (-0.5_dp - 0.5_dp*(tmp245*delt_A0_T2_B1)/B1 + &
     &0.5_dp*((-A0 + B1 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B1 - T2)*Log_B1_q)/T2 + 0.5_dp*(Log_A0_q*Log_B1_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B1_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B1 + T2)*phi_A0_T2_B1)/B1)
   DT2c2b = DT2c2b -  (hb**2*sbe**2*(-(0.125_dp*(b*(1 - c2t))/c2b) - &
     &0.25_dp*(mb*s2t*mt)/s2b + 0.125_dp*((1 + c2t)*t)/c2b + &
     &0.25_dp*(mb*(1 - c2t)*Yb)/s2b - 0.25_dp*(s2t*mt*Yb)/c2b + &
     &0.125_dp*((1 - c2t)*Yb**2)/c2b) + cbe*hb*ht*sbe*(-(mb*s2t*tmp31) + &
     &2*mb*mt*tmp52 - 0.25_dp*(s2t*(b + t))/s2b + &
     &0.5_dp*(mt*tmp98)/s2b - 0.25_dp*(s2t*Yb*Yt)/s2b) + &
     &cbe**2*ht**2*(0.125_dp*(b*(1 + c2t))/c2b - &
     &0.25_dp*(mb*s2t*mt)/s2b - 0.125_dp*((1 - c2t)*t)/c2b + &
     &0.25_dp*(mb*(1 + c2t)*Yt)/s2b + 0.25_dp*(s2t*mt*Yt)/c2b - &
     &0.125_dp*((1 + c2t)*Yt**2)/c2b))* &
     (-0.5_dp - 0.5_dp*(tmp247*delt_A0_T2_B2)/B2 + &
     &0.5_dp*((-A0 + B2 - T2)*Log_A0_q)/T2 + &
     &0.5_dp*((A0 - B2 - T2)*Log_B2_q)/T2 + 0.5_dp*(Log_A0_q*Log_B2_q) - &
     &0.5_dp*(Log_A0_q*Log_T2_q) - 0.5_dp*(Log_B2_q*Log_T2_q) + 2*Log_T2_q -  &
     ((-A0 - B2 + T2)*phi_A0_T2_B2)/B2)
   Dc2tc2b = hb**2*tmp229 + ht**2*tmp229 - &
     &tmp211*(hb**2*sbe**2*tmp30 + cbe**2*ht**2*tmp43 + &
     &cbe*hb*ht*sbe*(-(0.25_dp*(mb*mt)/(c2b*c2t)) - &
     &0.125_dp*(b + t)/(s2b*s2t) - 0.5_dp*(mb*tmp31)/s2t + &
     &0.5_dp*(mt*tmp35)/s2b - 0.125_dp*(Yb*Yt)/(s2b*s2t)))-&
     &tmp212*(hb**2*sbe**2*tmp30 + cbe**2*ht**2*tmp43 + &
     &cbe*hb*ht*sbe*(-(0.25_dp*(mb*mt)/(c2b*c2t)) - &
     &0.125_dp*(b + t)/(s2b*s2t) + 0.5_dp*(mb*tmp32)/s2t - &
     &0.5_dp*(mt*tmp36)/s2b - 0.125_dp*(Yb*Yt)/(s2b*s2t)))-&
     &0.5_dp*(tmp228*(cbe**2*hb**2*tmp12 +ht**2*sbe**2*tmp25 - cbe*hb*ht*sbe* &
     (-(0.25_dp*(mb*mt)/(c2b*c2t)) - 0.125_dp*(b + t)/(s2b*s2t) - &
     &0.5_dp*(mb*tmp13)/s2t + &
     &0.5_dp*(mt*tmp17)/s2b - 0.125_dp*(Xb*Xt)/(s2b*s2t)) &
     )) - 0.5_dp*(tmp232* (cbe**2*hb**2*tmp12 + ht**2*sbe**2*tmp25 - &
     &cbe*hb*ht*sbe* (-(0.25_dp*(mb*mt)/(c2b*c2t)) - &
     &0.125_dp*(b + t)/(s2b*s2t) + 0.5_dp*(mb*tmp14)/s2t - &
     &0.5_dp*(mt*tmp18)/s2b - 0.125_dp*(Xb*Xt)/(s2b*s2t)) &
     )) - 0.5_dp*(tmp227* (cbe**2*hb**2*tmp11 + ht**2*sbe**2*tmp24 - &
     &cbe*hb*ht*sbe* (0.25_dp*(mb*mt)/(c2b*c2t) + &
     &0.125_dp*(b + t)/(s2b*s2t) - 0.5_dp*(mb*tmp14)/s2t - &
     &0.5_dp*(mt*tmp17)/s2b + 0.125_dp*(Xb*Xt)/(s2b*s2t)) &
     )) - 0.5_dp*(tmp233* (cbe**2*hb**2*tmp11 + ht**2*sbe**2*tmp24 - &
     &cbe*hb*ht*sbe* (0.25_dp*(mb*mt)/(c2b*c2t) + &
     &0.125_dp*(b + t)/(s2b*s2t) + 0.5_dp*(mb*tmp13)/s2t + &
     &0.5_dp*(mt*tmp18)/s2b + 0.125_dp*(Xb*Xt)/(s2b*s2t)) ))
   Dc2tc2b = Dc2tc2b - tmp210*(hb**2*sbe**2*tmp29 + cbe**2*ht**2*tmp42 + &
     &cbe*hb*ht*sbe*(0.25_dp*(mb*mt)/(c2b*c2t) + &
     &0.125_dp*(b + t)/(s2b*s2t) - 0.5_dp*(mb*tmp32)/s2t - &
     &0.5_dp*(mt*tmp35)/s2b + 0.125_dp*(Yb*Yt)/(s2b*s2t)))-&
     &tmp213*(hb**2*sbe**2*tmp29 + cbe**2*ht**2*tmp42 + &
     &cbe*hb*ht*sbe*(0.25_dp*(mb*mt)/(c2b*c2t) + &
     &0.125_dp*(b + t)/(s2b*s2t) + 0.5_dp*(mb*tmp31)/s2t + &
     &0.5_dp*(mt*tmp36)/s2b + 0.125_dp*(Yb*Yt)/(s2b*s2t)))
   Dcptpb = -2*mb*cbe*hb*ht*sbe*mt*tmp211*tmp50 - &
     &2*mb*cbe*hb*ht*sbe*mt*tmp212*tmp50 + &
     &mb*cbe*hb*ht*sbe*mt*tmp228*tmp50 + &
     &mb*cbe*hb*ht*sbe*mt*tmp232*tmp50 - &
     &2*mb*cbe*hb*ht*sbe*mt*tmp210*tmp53 - &
     &2*mb*cbe*hb*ht*sbe*mt*tmp213*tmp53 + &
     &mb*cbe*hb*ht*sbe*mt*tmp227*tmp53 + &
     &mb*cbe*hb*ht*sbe*mt*tmp233*tmp53 - 4*mb*cbe*hb*ht*sbe*mt* &
     (2.5_dp*(A0 + b + t) + 0.5_dp*tmp224 - &
     &0.5_dp*((-A0 - b + t)*Log_A0_q*Log_b_q) - &
     &0.5_dp*((-A0 + b - t)*Log_A0_q*Log_t_q) - &
     &0.5_dp*((A0 - b - t)*Log_b_q*Log_t_q) + &
     &0.5_dp*(delt_A0_t_b*phi_A0_t_b)/b - 2*A0*Log_A0_q - &
     &2*b*Log_b_q - 2*t*Log_t_q)
   Dcpttptb = 0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp227*Xb*Xt) - &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp228*Xb*Xt) - &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp232*Xb*Xt) + &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp233*Xb*Xt) - &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp210*Yb*Yt) + &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp211*Yb*Yt) + &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp212*Yb*Yt) - &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*tmp213*Yb*Yt)
   Dcpbptt = -2*mb*hb*ht*abs_mu*s2t*tmp217 - cbe*hb*ht*sbe*tmp211* &
     (mb*s2t*tmp95 - 0.5_dp*(b*s2b*s2t)) - cbe*hb*ht*sbe*tmp212* &
     (-(mb*s2t*tmp96) - 0.5_dp*(b*s2b*s2t)) - cbe*hb*ht*sbe*tmp213* &
     (-(mb*s2t*tmp95) + 0.5_dp*(b*s2b*s2t)) - cbe*hb*ht*sbe*tmp210* &
     (mb*s2t*tmp96 + 0.5_dp*(b*s2b*s2t)) + 0.5_dp*(cbe*hb*ht*sbe*tmp228* &
     (mb*s2t*tmp69 - 0.5_dp*(b*s2b*s2t))) + 0.5_dp*(cbe*hb*ht*sbe*tmp232* &
     (-(mb*s2t*tmp70) - 0.5_dp*(b*s2b*s2t))) + 0.5_dp*(cbe*hb*ht*sbe*tmp233* &
     (-(mb*s2t*tmp69) + 0.5_dp*(b*s2b*s2t))) + 0.5_dp*(cbe*hb*ht*sbe*tmp227* &
     (mb*s2t*tmp70 + 0.5_dp*(b*s2b*s2t)))
   Dcptptb = -2*hb*ht*abs_mu*s2b*mt*tmp214 - cbe*hb*ht*sbe*tmp211* &
     (-(s2b*mt*tmp97) - 0.5_dp*(s2b*s2t*t)) - cbe*hb*ht*sbe*tmp212* &
     (s2b*mt*tmp98 - 0.5_dp*(s2b*s2t*t)) - cbe*hb*ht*sbe*tmp210* &
     (s2b*mt*tmp97 + 0.5_dp*(s2b*s2t*t)) - cbe*hb*ht*sbe*tmp213* &
     (-(s2b*mt*tmp98) + 0.5_dp*(s2b*s2t*t)) + 0.5_dp*(cbe*hb*ht*sbe*tmp228* &
     (-(s2b*mt*tmp71) - 0.5_dp*(s2b*s2t*t))) + 0.5_dp*(cbe*hb*ht*sbe*tmp232* &
     (s2b*mt*tmp72 - 0.5_dp*(s2b*s2t*t))) + 0.5_dp*(cbe*hb*ht*sbe*tmp227* &
     (s2b*mt*tmp71 + 0.5_dp*(s2b*s2t*t))) + 0.5_dp*(cbe*hb*ht*sbe*tmp233* &
     (-(s2b*mt*tmp72) + 0.5_dp*(s2b*s2t*t)))
   Dcptmptt = -(tmp213* (0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t) + hb**2*sbe**2* &
     (0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Yb)) + cbe**2*ht**2* &
     (0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Yt)))) - &
     &tmp211*(-(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t)) + &
     &hb**2*sbe**2*(-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Yb)) + &
     &cbe**2*ht**2*(-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Yt))) - &
     &tmp212*(-(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t)) + &
     &hb**2*sbe**2*(-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Yb)) + &
     &cbe**2*ht**2*(-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Yt))) - &
     &0.5_dp*(tmp233*(-(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t)) + cbe**2*hb**2* &
     (0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Xb)) + ht**2*sbe**2* &
     (0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Xt)))) - &
     &0.5_dp*(tmp228*(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t) + cbe**2*hb**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Xb)) + ht**2*sbe**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Xt)))) - &
     &0.5_dp*(tmp232*(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t) + cbe**2*hb**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*((1 - c2b)*s2t*mt*Xb)) + ht**2*sbe**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*((1 + c2b)*s2t*mt*Xt)))) - &
     &0.5_dp*(tmp227*(-(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t)) + cbe**2*hb**2* &
     (0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Xb)) + ht**2*sbe**2* &
     (0.5_dp*(mb*s2b*s2t*mt) + 0.5_dp*((1 + c2b)*s2t*mt*Xt))))
   Dcptmptt = Dcptmptt - tmp210*(0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t) + &
     &hb**2*sbe**2*(0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*((1 - c2b)*s2t*mt*Yb)) + &
     &cbe**2*ht**2*(0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*((1 + c2b)*s2t*mt*Yt))) - &
     &0.25_dp*(ht**2*(4*cbe**2*s2t*mt*tmp242*Yt - &
     &4*cbe**2*s2t*mt*tmp250*Yt + 2*s2t*sbe**2*mt*Xt* &
     (-10*T1 + 4*T1*Log_T1_q + tmp189*Log_T1_q) - 2*s2t*sbe**2*mt*Xt* &
     (-10*T2 + 4*T2*Log_T2_q + tmp209*Log_T2_q)))
   Dcpbmptb = -(tmp211* (-(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe)) + hb**2*sbe**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*(mb*(1 + c2t)*s2b*Yb)) + cbe**2*ht**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*(mb*(1 - c2t)*s2b*Yt)))) - &
     &tmp210*(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe) + &
     &hb**2*sbe**2*(0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*(mb*(1 + c2t)*s2b*Yb)) + &
     &cbe**2*ht**2*(0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*(mb*(1 - c2t)*s2b*Yt))) - &
     &tmp213*(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe) + &
     &hb**2*sbe**2*(0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*(mb*(1 - c2t)*s2b*Yb)) + &
     &cbe**2*ht**2*(0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*(mb*(1 + c2t)*s2b*Yt))) - &
     &0.5_dp*(tmp228*(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe) + cbe**2*hb**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*(mb*(1 + c2t)*s2b*Xb)) + ht**2*sbe**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) - &
     &0.5_dp*(mb*(1 - c2t)*s2b*Xt)))) - &
     &0.5_dp*(tmp227*(-(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe)) + cbe**2*hb**2* &
     (0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*(mb*(1 + c2t)*s2b*Xb)) + ht**2*sbe**2* &
     (0.5_dp*(mb*s2b*s2t*mt) + &
     &0.5_dp*(mb*(1 - c2t)*s2b*Xt)))) - &
     &0.5_dp*(tmp233*(-(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe)) + cbe**2*hb**2* &
     (0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*(mb*(1 - c2t)*s2b*Xb)) + ht**2*sbe**2* &
     (0.5_dp*(mb*s2b*s2t*mt) - &
     &0.5_dp*(mb*(1 + c2t)*s2b*Xt)))) - &
     &0.5_dp*(tmp232*(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe) + cbe**2*hb**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*(mb*(1 - c2t)*s2b*Xb)) + ht**2*sbe**2* &
     (-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*(mb*(1 + c2t)*s2b*Xt))))
   Dcpbmptb = Dcpbmptb - tmp212*(-(0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe)) + &
     &hb**2*sbe**2*(-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*(mb*(1 - c2t)*s2b*Yb)) + &
     &cbe**2*ht**2*(-(0.5_dp*(mb*s2b*s2t*mt)) + &
     &0.5_dp*(mb*(1 + c2t)*s2b*Yt))) - 0.25_dp*(hb**2*(4*mb*s2b*sbe**2*Yb* &
     (-(2.5_dp*(A0 + 2*B1)) + 0.5_dp*((A0 - 2*B1)*Log_B1_q**2) - &
     &0.5_dp*(delt(A0,B1,B1)*phi(A0,B1,B1))/B1 + &
     &2*A0*Log_A0_q + 4*B1*Log_B1_q - A0*Log_A0_q*Log_B1_q) + &
     &2*mb*cbe**2*s2b*Xb* (-10*B1 + 4*B1*Log_B1_q + &
     &Log_B1_q*(4*B1 - 2*B1*Log_B1_q)) - 4*mb*s2b*sbe**2*Yb* &
     (-(2.5_dp*(A0 + 2*B2)) + 0.5_dp*((A0 - 2*B2)*Log_B2_q**2) - &
     &0.5_dp*(delt(A0,B2,B2)*phi(A0,B2,B2))/B2 + &
     &2*A0*Log_A0_q + 4*B2*Log_B2_q - A0*Log_A0_q*Log_B2_q) - &
     &2*mb*cbe**2*s2b*Xb* (-10*B2 + 4*B2*Log_B2_q + &
     &Log_B2_q*(4*B2 - 2*B2*Log_B2_q))))
   Dspbmptbspbptt = 0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp210) - &
     &0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp211) - &
     &0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp212) + &
     &0.5_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp213) - &
     &0.25_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp227) + &
     &0.25_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp228) + &
     &0.25_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp232) - &
     &0.25_dp*(b*cbe*hb*ht*s2b*s2t*sbe*tmp233)
   Dsptmpttsptptb = 0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp210) - &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp211) - &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp212) + &
     &0.5_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp213) - &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp227) + &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp228) + &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp232) - &
     &0.25_dp*(cbe*hb*ht*s2b*s2t*sbe*t*tmp233)
   Dsptmpttspbmptb = -(tmp211*tmp6)-tmp212*tmp6 - tmp210*tmp7 - tmp213*tmp7 - &
     &0.5_dp*(tmp228*tmp8) - 0.5_dp*(tmp232*tmp8) - &
     &0.5_dp*(tmp227*tmp9) - 0.5_dp*(tmp233*tmp9)
   Return
   End Subroutine makederiv
   
 End Subroutine makefuncs


 Subroutine makefuncstau(t,b,T1,T2,B1,B2,s2t,c2t,s2b,c2b, &
    q,mu,vv,tanb,F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6, Ft,Fb,Gt,Gb,FAp)
  Implicit None
  Real(dp), intent(in) :: t,b,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,mu,vv,tanb
  Real(dp), intent(out) :: F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp
  
  Real(dp) :: pippob, pippot, ht, hb

  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  pippot = T1*(Log(T1/q)-1._dp) - T2*(Log(T2/q)-1._dp)
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))

  F1t = tauF1q(t,b,T1,T2,B1,B2,s2t,s2b,q,vv,tanb)
  F2t = tauF2q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  F3t = tauF3q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  F4t = tauF4q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)

  F1b = tauF1q(b,t,B1,B2,T1,T2,s2b,s2t,q,vv,tanb) 
  F2b = tauF2q(b,t,B1,B2,T1,T2,s2b,c2b,s2t,q,vv,tanb) 
  F3b = tauF3q(b,t,B1,B2,T1,T2,s2b,c2b,s2t,q,vv,tanb) 
  F4b = tauF4q(b,t,B1,B2,T1,T2,s2b,c2b,s2t,q,vv,tanb) 

  F5 = tauF5q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,vv,tanb)
  F6 = tauF6q(t,b,T1,T2,B1,B2,s2t,s2b,vv,tanb)

  Ft = tauFq(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  Gt = tauGq(t,b,T1,T2,B1,B2,s2t,s2b,q,vv,tanb)
  
  Fb = tauFq(b,t,B1,B2,T1,T2,s2b,c2b,s2t,q,vv,tanb)
  Gb = tauGq(b,t,B1,B2,T1,T2,s2b,s2t,q,vv,tanb)
  
  FAp = tauFAq(t,b,T1,T2,B1,B2,s2t,s2b,q,mu,vv,tanb)

 Contains

  Function tauF1q(t,b,T1,T2,B1,B2,s2t,s2b,q,vv,tanb)
  Implicit None
  
  Real(dp) :: tauF1q
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,s2b,q,vv,tanb
  Real(dp) :: ht,hb,pippob
  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  tauF1q = -0.5_dp*ht*hb*s2t*s2b*(T1-T2)/T1/T2*pippob

  End Function tauF1q
  
  
  Function tauF2q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  
  Implicit None
  
  Real(dp) :: tauF2q
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb
  Real(dp) :: ht,hb,pippob
  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  tauF2q =0.5_dp*ht*hb*s2b/s2t/T1/T2/(T1-T2)*pippob* &
      & (s2t**2*(T1**2-T2**2) + 2._dp*c2t**2*T1*T2*Log(T1/T2))
  
  End Function tauF2q
  
  
  Function tauF3q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  
  Implicit None
  Real(dp) :: tauF3q
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb
  Real(dp) :: ht,hb,pippob
  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  
  tauF3q = -0.5_dp*ht*hb*s2b/s2t/T1/T2/(T1-T2)**2*pippob* &
    ((T1-T2)*(s2t**2*(T1+T2)**2 - 8d0*c2t**2*T1*T2) &
    -2._dp*(3d0*s2t**2 - 2._dp)*T1*T2*(T1+T2)*Log(T1/T2))

  End Function tauF3q
  
  
  Function tauF4q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  
  Implicit None
  Real(dp) :: tauF4q
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb
  Real(dp) :: ht,hb,pippot
  pippot = T1*(Log(T1/q)-1._dp) - T2*(Log(T2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  
  tauF4q =0.5_dp*ht*hb*s2b/s2t/(T1-T2)*Log(B1/B2)* &
    (2._dp*c2t**2*pippot + s2t**2*(T1-T2)*Log(T1*T2/q**2))
  
  End Function tauF4q
  
  
  Function tauF5q(t,b,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,vv,tanb)
  
  Implicit None
  Real(dp) :: tauF5q
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,c2t,s2b,c2b,q,vv,tanb
  Real(dp) :: ht,hb,pippob,pippot
  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  pippot = T1*(Log(T1/q)-1._dp) - T2*(Log(T2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  
  tauF5q =0.5_dp*hb*ht/s2b/s2t*  &
    (-4._dp*pippob*pippot/(B1-B2)/(T1-T2)*(1._dp-c2b**2*c2t**2) &
    + 2._dp*pippot*s2b**2*c2t**2/(T1-T2)*Log(B1*B2/q**2) &
    + 2._dp*pippob*s2t**2*c2b**2/(B1-B2)*Log(T1*T2/q**2) &
    + s2t**2*s2b**2*(Log(B1/q)*Log(T1/q) + Log(B1/q)*Log(T2/q) &
    + Log(B2/q)*Log(T1/q) + Log(B2/q)*Log(T2/q)))
  
  End Function tauF5q
  
  
  Function tauF6q(t,b,T1,T2,B1,B2,s2t,s2b,vv,tanb)
  
  Implicit None
  Real(dp) :: tauF6q
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,s2b,vv,tanb
  Real(dp) :: ht,hb
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  
  tauF6q =0.5_dp*ht*hb*s2t*s2b*Log(B1/B2)*Log(T1/T2)
  
  Return
  End Function tauF6q
  
  
  Function tauFq(t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb)
  
  Implicit None
  Real(dp) :: tauFq
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,c2t,s2b,q,vv,tanb
  Real(dp) :: ht,hb,pippob,pippot
  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  pippot = T1*(Log(T1/q)-1._dp) - T2*(Log(T2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  
  tauFq =0.5_dp*ht*hb*s2b/s2t/(T1-T2)*pippob* &
    (2._dp*c2t**2*pippot + s2t**2*(T1-T2)*Log(T1*T2/q**2))
  
  End Function tauFq

  
  Function tauGq(t,b,T1,T2,B1,B2,s2t,s2b,q,vv,tanb)
  
  Implicit None
  Real(dp) :: tauGq
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,s2b,q,vv,tanb
  Real(dp) :: ht,hb,pippob
  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  
  tauGq =0.5_dp*hb*ht*s2b*s2t*pippob*Log(T1/T2)
  
  End Function tauGq
  
  
  Function tauFAq(t,b,T1,T2,B1,B2,s2t,s2b,q,mu,vv,tanb)
  
  Implicit None
  Real(dp) :: tauFAq
  Real(dp) :: t,b,T1,T2,B1,B2,s2t,s2b,q,mu,vv,tanb
  Real(dp) :: Xt,Xb,At,Ab
  Real(dp) :: ht,hb,pippob,pippot

  pippob = B1*(Log(B1/q)-1._dp) - B2*(Log(B2/q)-1._dp)
  pippot = T1*(Log(T1/q)-1._dp) - T2*(Log(T2/q)-1._dp)
  
  ht = Sqrt(2._dp*t/vv)/Cos(Atan(tanb))
  hb = Sqrt(2._dp*b/vv)/Cos(Atan(tanb))
  Xt = (T1-T2)*s2t/2._dp/Sqrt(t)    
  Xb = (B1-B2)*s2b/2._dp/Sqrt(b)
  At = Xt - mu*tanb
  Ab = Xb - mu*tanb
  
  tauFAq = 2._dp*ht*hb*Sqrt(t*b)*tanb*(Ab-At)**2    &
      &  * mu**2/s2b/s2t/(T1-T2)**2/(B1-B2)**2*pippot*pippob
  
  End Function tauFAq

 End Subroutine makefuncstau
  

 Subroutine Yukawa2L_PseudoScalar(mA2, vevs, mD2, mU2, mQ2, ME2, ML2, A_b &
             & , A_t, A_tau, Y_b, Y_t, Y_tau, mu, PiA02, kont)
 !------------------------------------------------------------------
 ! calulates the 2-loop contribution to the pseudoscalar Higgs mass
 ! in the effective potential approach. The program is based on the
 ! routines DSZodd and  BDSZodd which were provided by P. Slavich;
 ! The formulas are based on  hep-ph/0105096 and hep-ph/0112177
 ! input:
 !   gs .................. g_strong
 !   mg .................. m_gluino
 !   mA2 ................. m_A0 squared
 !   vevs(i) ............. vacuum expactation values
 !   mD2 ................. M^2_(\tilde D)
 !   mU2 ................. M^2_(\tilde U)
 !   mQ2 ................. M^2_(\tilde Q)
 !   mE2 ................. M^2_(\tilde E)
 !   mL2 ................. M^2_(\tilde L)
 !   A_t ................. trilinear coupling A_top
 !   A_b ................. trilinear coupling A_bottom
 !   A_tau ............... trilinear coupling A_tau
 !   Y_t ................. top Yukawwa coupling
 !   Y_b ................. bottom Yukawwa coupling
 !   Y_tau ............... tau Yukawwa coupling
 !   mu .................. mu-parameter
 ! output:
 !  PiA02 ....... two-loop contribution to pseudoscalar mass
 !  kont ........ is 0 if everything is o.k., otherwise it gets a negative 
 !                value
 ! written by Werner Porod, 13.12.02
 ! 11.06.03: implementing alpha_b alpha_t + alpha^2_b corrections
 !           based on A. Dedes, G. Degrassi and P. Slavich, hep-ph/0305127
 ! 04.03.04: - implementing alpha_b alpha_tau part
 !------------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont 
  Real(dp), Intent(in) ::  mA2, vevs(2), mQ2, mU2, mD2, ML2, ME2
  Complex(dp), Intent(in) :: A_b, A_t, Y_t, Y_b, mu, A_tau, Y_tau
  Real(dp), Intent(out) :: PiA02

  Real(dp) :: FA, FA_A, s2t, c2t, s2b, c2b, Q, mt, tanb, mb           &
       & , sb, cb, ht2, mStop(2), mStop2(2), mt2, mb2, mtau, mtau2    &
       & , muR, mSbottom(2), mSbottom2(2), At, Ab, hb2, vv, Atau      &
       & , mStau(2), mStau2(2), s2tau, c2tau, htau2, mSneu2
  Real(dp) :: F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp, DMA,FB_A, DMB
  Complex(dp) :: Rstop(2,2), RSbottom(2,2), Rstau(2,2)
  Real(dp), Parameter :: YL = 1._dp / 3._dp, YRu = -4._dp / 3._dp  &
         & , YRd = 2._dp / 3._dp

  Iname = Iname + 1
  NameOfUnit(Iname) = "Yukawa2L_PseudoScalar"

  PiA02 = 0._dp
  kont = 0
  !------------------------------------------------------------------------
  ! first the (s)fermion, please note, that the papers by P.Slavich et al. 
  ! the ordering of the sfermions is reversed to compared to my odering
  !------------------------------------------------------------------------
  Call SfermionMass(MQ2, MU2, A_t, mu, vevs, Y_t, 0.5_dp, YL, YRu,   &
               &  0._dp, 0._dp, kont, mStop, mStop2, Rstop)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*)&
 "Stop masses squared for 2-loop calculation of pseudoscalar mass are negativ."
   kont = -601
   Call AddError(601)
   Iname = Iname - 1
   Return
  End If 
  mt2 = 0.5_dp * Abs(Y_t*vevs(2))**2

  Call SfermionMass(MQ2, MD2, A_b, mu, vevs, Y_b, -0.5_dp, YL, YRd,   &
               &  0._dp, 0._dp, kont, mSbottom, mSbottom2, Rsbottom)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
         & "Sbottommasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -602
   Call AddError(602)
   Iname = Iname - 1
   Return
  End If 

  mb2 = 0.5_dp * Abs(Y_b*vevs(1))**2

  Call SfermionMass(ML2, ME2, A_tau, mu, vevs, Y_tau, -0.5_dp, 1._dp, 2._dp,   &
                  & 0._dp, 0._dp, kont, mStau, mStau2, RStau)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
     "Staumasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -603
   Call AddError(603)
   Iname = Iname - 1
   Return
  End If 

  mtau2 = 0.5_dp * Abs(Y_tau*vevs(1))**2
  mtau = Sqrt(mtau2)
  s2tau = - 2._dp * Real( Rstau(1,1) * Rstau(1,2), dp)
  c2tau = Abs(Rstau(1,2))**2 -  Abs(Rstau(1,1))**2
  htau2 = Abs(Y_tau)**2

  mSneu2 = ML2
  !------------------------------------------------------------
  ! different mass ordering leads to the following formulas
  !------------------------------------------------------------
  s2t = - 2._dp * Real( Rstop(1,1) * Rstop(1,2), dp)
  c2t = Abs(Rstop(1,2))**2 -  Abs(Rstop(1,1))**2
  s2b = - 2._dp * Real( Rsbottom(1,1) * Rsbottom(1,2), dp)
  c2b = Abs(Rsbottom(1,2))**2 -  Abs(Rsbottom(1,1))**2

  Q = GetRenormalizationScale() ! from LoopFunctions

  mt = Sqrt(mt2)
  mb = Sqrt(mb2)
  ht2 = Abs(Y_t)**2
  hb2 = Abs(Y_b)**2

  tanb = vevs(2) / vevs(1)
  cb = 1._dp / Sqrt(1._dp + tanb**2)
  sb = tanb * cb
 
  At = Real(A_t/Y_t, dp)
  Ab = Real(A_b/Y_b, dp)
  Atau = Real(A_tau/Y_tau, dp)
  muR = - Real(mu, dp) ! different sign convention

  PiA02 =0._dp
  FA=0._dp
  FA_A=0._dp
 !  !-----------------
 !  ! alpha_s alpha_t  
 !  !-----------------
 !  Call strfuncsodd(mt2, mg, mStop2(2), mStop2(1), s2t, Q, At, FA, FA_A)
 !  If (At.Eq.0._dp) Then
 ! !     the function FA has poles in A=0. 
 ! !     when necessary we consider the residues which is zero:
 !   PiA02 = ht2 * muR/ ((mStop2(2)-mStop2(1)) *sb *cb) * FA_A
 !  Else
 !   PiA02 = ht2 *At *muR / ((mStop2(2)-mStop2(1))*sb*cb) * FA
 !  End If
 !  !-----------------
 !  ! alpha_s alpha_b 
 !  !-----------------
 !  Call strfuncsodd(mb2, mg, mSbottom2(2), mSbottom2(1), s2b, Q, Ab, FA, FA_A)
 !  If (Ab.Eq.0._dp) Then
 ! !     the function FA has poles in A=0. 
 ! !     when necessary we consider the residues, which is zero
 !   PiA02 = PiA02 + hb2 * muR/ ((mSbottom2(2)-mSbottom2(1)) *sb *cb) * FA_A
 !  Else
 !   PiA02 = PiA02 +hb2 *Ab *muR / ((mSbottom2(2)-mSbottom2(1))*sb*cb) * FA
 !  End If

 !  PiA02 = 4._dp * gs**2 * PiA02 ! gs^2 CF Nc

  !-----------------------
  ! (alpha_t = alpha_b)^2  
  !-----------------------
  vv = vevs(1)**2 + vevs(2)**2

  Call makefuncs(mt2, mb2, mA2, mStop2(2), mStop2(1), mSbottom2(2) &
            & , mSbottom2(1), s2t, c2t, s2b, c2b, q, muR, vv, tanb &
            & , F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp)
  FA_A = -3._dp * ( ht2*muR*At/(mStop2(2) - mStop2(1)) * Ft         &
       &          + hb2*muR*Ab/(mSbottom2(2) - mSbottom2(1)) * Fb   &
       &          + 2._dp*Sqrt(ht2*hb2) * FAp) /( sb*cb)

 !-----------------------
 ! alpha_tau * alpha_b
 !-----------------------
  Call makefuncstau(mtau2,mb2,mStau2(2), mStau2(1), mSbottom2(2)    &
        & , mSbottom2(1), s2tau, c2tau, s2b, c2b, Q ,muR, vv, tanb  &
        & , F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp)
  DMA = -3._dp * ( htau2*muR*Atau/(mStau2(2)-mStau2(1)) * Ft   &
      &          + hb2*muR*Ab/(mSbottom2(2) - mSbottom2(1))*Fb &
      &          + 2._dp*Sqrt(htau2*hb2)*FAp)/ ( sb*cb)

 !-----------------------
 ! alpha_tau^2
 !-----------------------
  Call taufuncsodd(mtau2, mA2, mSneu2, mStau2(2), mStau2(1), s2tau, c2tau &
                 & , sb, cb, Q, muR, FB, FB_A)

  If(Atau/=0d0) Then
    DMB = htau2*muR*Atau/(mStau2(2) - mStau2(1))/(sb*cb) * FB
  Else
  !     the function FA has poles in A=0. 
  !     when necessary we consider the residues:
    DMB = htau2*muR/(mStau2(2) - mStau2(1))/(sb*cb) * FB_A
  Endif
  DMB = htau2 * DMB

  PiA02 = oo16Pi2**2 * (PiA02 + FA_A + DMA + DMB)

  Iname = Iname - 1

 Contains 

  ! Subroutine strfuncsodd(t,mg,T1,T2,s2t,q,A,FA,FA_A)
  ! Implicit None
  !  Real(dp), Intent(in) :: t,mg,T1,T2,s2t,q,A
  !  Real(dp), Intent(out) :: FA,FA_A

  !  If (A.eq.0._dp) Then
  !   FA_A = strresFAc(t,mg,T1,T2,q) - strresFAc(t,mg,T2,T1,q)
  !   FA = 0._dp
  !  Else
  !   FA_A = 0._dp
  !   FA = strFAab(T1,T2,s2t,q) + strFAc(t,mg,T1,T2,s2t,A,q) &
  !    & - strFAc(t,mg,T2,T1,-s2t,A,q)
  !  End If
   
  ! End Subroutine strfuncsodd

  Real(dp) Function strresFAc(t,mg,T1,T2,q)
  !     residue of FA for A=0
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,T2,q
   Real(dp) :: del, g

   g = mg**2
   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
   
   strresFAc = - mg*(T1+T2)*Pi**2/6._dp                                 &
    &   - 2._dp*mg*(T1*(6._dp- 5._dp*Log(T1/q))+ T2*(1._dp- Log(T2/q))) &
    &     - mg*(T1*Log(T1/q)**2 + T2*Log(T2/q)**2)                      &
    &     + 2._dp*mg*T1*Log(g/q)*Log(t/q)                               &
    &     - 2._dp*mg*((g-t)*Log(g/t)+ T1*Log(t*g/q**2))*Log(T1/q)       &
    &     - 2._dp*del/mg*phi(t, T1, g)
   
  End Function strresFAc

  Real(dp) Function strFAab(T1,T2,s2t,q)
  Implicit None
   Real(dp), Intent(in) :: T1,T2,s2t,q
  ! eq. (C4)
   strFAab = (8._dp - s2t**2*(2._dp - (T1+T2)/(T1-T2)*Log(T1/T2)))  &
    &     *(T1*(1._dp - Log(T1/q)) - T2*(1._dp - Log(T2/q)))        &
    &     + 2._dp*(T1*Log(T1/q)**2 - T2*Log(T2/q)**2)             &
    &     + 2._dp/(T1-T2)*(T1*Log(T1/q) - T2*Log(T2/q))**2
   
  End Function strFAab

  Real(dp) Function strFAc(t,mg,T1,T2,s2t,A,q)
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,T2,s2t,A,q
   Real(dp) :: del, g, mt

   g = mg**2
   mt = Sqrt(t)
   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
    ! eq. (C5)
   strFAc = 16._dp*T1/(T1-T2)*mg*mt*s2t                                  &
    &     -mg/A*(T1+T2)*Pi**2/6                                         &
    &     -4._dp*(g+t)*Log(T1/q)                                             &
    &     - 2._dp*mg/A*                                                 &
    &     (T1*(6._dp- 5._dp*Log(T1/q))+ T2*(1._dp- Log(T2/q)))               &
    &     - 4._dp* mg*mt*s2t*(3._dp* T1 + T2)/(T1-T2)*Log(T1/q)          &
    &     - mg/A*(T1*Log(T1/q)**2 + T2*Log(T2/q)**2)                    &
    &     + 2._dp*(g+t-T1)*Log(t*g/q**2)*Log(T1/q)                           &
    &     + 2._dp*T1*(1+mg/A)*Log(g/q)*Log(t/q)                         &
    &     - 2._dp*mg/A*((g-t)*Log(g/t)+ T1*Log(t*g/q**2))*Log(T1/q)     &
    &     + 2._dp*mg*mt*s2t/(T1-T2)*                                     &
    &     (2._dp*(g-t)*Log(g/t) + (T1+T2)*Log(t*g/q**2))*Log(T1/q)           &
    &     - (4._dp* t + 2._dp* del/g*(1._dp + mg/A)                     &
    &     - 2._dp*mt/mg*s2t/(T1-T2)*                                     &
    &     (2._dp*del + (g+t-T1)*(T1-T2)))*phi(t,T1,g)

  End Function strFAc

  
  Subroutine taufuncsodd(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu,FA,FA_A)
  Implicit None
  Real(dp) :: t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu
  Real(dp) :: FA,FA_A
  FA = tauFAab(T1,T2,Q) + tauFAc(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu) &
   & - tauFAc(t,A0,BL,T2,T1,-s2t,-c2t,cb,sb,q,mu)
  
  FA_A = tauresFAc(t,A0,BL,T1,T2,s2t,cb,sb,q,mu) &
     & - tauresFAc(t,A0,BL,T2,T1,-s2t,cb,sb,q,mu)
  
  End Subroutine taufuncsodd
  
  
  Function tauFAab(T1,T2,Q)
  Implicit None
  Real(dp) :: T1,T2,Q
  Real(dp) :: Nc=1._dp ! color factor !!!
  Real(dp) :: tauFAab
  tauFAab = (5.+2.*Nc)*(T1*(1.-Log(T1/q)+Log(T1/q)**2/2)-&
    &T2*(1.-Log(T2/q)+Log(T2/q)**2/2))

  End Function tauFAab
  

  Function tauFAc(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)
  Implicit None
  Real(dp) :: t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu
  Real(dp) :: Nc=1._dp ! color factor !!!
  Real(dp) :: mu2,Xt,Yt,At,st2,ct2, mt
  Real(dp) :: tauFAc
  mu2 = mu**2
  If(mu2==0._dp) mu2 = Epsilon(1._dp)
  mt = Sqrt(t)
  Xt = s2t*(T1-T2)/2._dp/mt
  Yt = Xt - mu/cb/sb
  At = sb**2*Xt+cb**2*Yt
  ct2 = (1._dp+c2t)/2._dp
  st2 = (1._dp-c2t)/2._dp

  tauFAc =  -(delt(mu2,t,T1)+2*t*mu2)/T1*phi(mu2,t,T1) &
    & + cb**2*Yt**2*(A0*c2t**2*(A0-2*(T1+T2))/2/(T1-T2)/T2 &
    &-s2t**2*(T1-T2)/4/T2)*phi(A0,T1,T2) +cb**2*(-A0*mt*Yt*(A0-4*T1) &
    *(1./2/At/T1/mt-s2t/T1/(T1-T2)) -A0*c2t**2*Yt**2*(A0-4*T1)/2/T1/(T1-T2) &
    & + A0*(2*mt+s2t*Yt)**2/4/T1)*phi(A0,T1,T1) +cb**2*(-mt*Yt*delt(A0,BL,T1)* &
    & ( 1./2/At/T1/mt-s2t/T1/(T1-T2)) +c2t*delt(A0,BL,T1)*(t-Yt**2)/2/T1/(T1-T2) &
    & + (A0+BL-T1)*(ct2*t+s2t*mt*Yt+st2*Yt**2)/2/T1)*phi(A0,BL,T1) &
    & - s2t**2*sb**2*Xt**2/2*Li2(1-T2/T1) &
    & + (mu2-T1)*(1-c2t*(1+(mu2-T1)/(T1-T2)))*Li2(1-mu2/T1) +(2*sb**2*mt*Xt*(BL-T1) &
    & *(1./2/At/mt-s2t/(T1-T2)) -c2t*sb**2*(t-Xt**2)*(BL-T1)/(T1-T2) &
    & - sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2))*Li2(1-BL/T1) &
    & - 21*mt*T1*(1./2/mt-s2t*At/(T1-T2)) &
    & - Nc*c2t**2*T1-9*s2t*mt*At/2+c2t/2*BL-c2t*T1/(T1-T2)*(A0*cb**2+2*BL-2*t&
    &-3*mu2+2*sb**2*Xt**2+2*cb**2*Yt**2) &
    & - T1/2-T1*(2*T1+5*T2)/2/(T1-T2)*c2t-T1*c2t**2-(3+Nc)*(T1-T2) &
    & + mu2*c2t*T2/(T1-T2)*Log(mu2/q) +BL*c2t*(3*T1+T2)/2/(T1-T2)*Log(BL/q) &
    & + A0*cb**2*c2t*(3*T1+T2)/2/(T1-T2)*Log(A0/q) &
    & + Log(T2/q)*(-3*s2t*mt*T2*At/(T1-T2) &
    & + c2t*T2/2/(T1-T2)*(BL+cb**2*A0-2*mu2-t+T1+sb**2*Xt**2+cb**2*Yt**2) &
    & + ((s2t**2-2)*T1+3*(3*s2t**2-4)*T2)/4/(T1-T2) *(sb**2*Xt**2+cb**2*Yt**2) &
    & + Nc*(T1+T2)/4/(T1-T2)*(s2t**2*(T1+2*T2)-4*T2) &
    & + s2t**2/4/(T1-T2)*(T1**2+3*T1*T2+2*T2**2) &
    & - (T1**2-3*T1*T2+9*T2**2)/2/(T1-T2)-(3+Nc)*T2&
    &-T2*(BL+3*A0*cb**2-6*mu2+t)/2/(T1-T2)) &
    & + Log(T1/q)*(18*mt*T1*(1./2/mt-s2t*At/(T1-T2)) &
    & + 3*s2t*mt*(2*T1-T2)/(T1-T2)*At&
    &+((9+8*c2t+9*c2t**2)*T1+(-5+2*c2t+c2t**2)*T2)/ &
    & 4/(T1-T2)*(sb**2*Xt**2+cb**2*Yt**2) +Nc*(4*(3-2*s2t**2)*T1**2&
    &+(-4+s2t**2)*T1*T2+s2t**2*T2**2)/4/(T1-T2) &
    & + c2t**2*(8*T1**2-T1*T2-T2**2)/4/(T1-T2) &
    & + cb**2*A0*(2*(3+c2t)*T1-(3-c2t)*T2)/2/(T1-T2) &
    & + BL*(2*(1+c2t)*T1-(1-c2t)*T2)/2/(T1-T2)      &
    & -mu2*(3*(2+c2t)*T1-(3-c2t)*T2)/(T1-T2) &
    & + t*(2*(1-2*c2t)*T1-(1+c2t)*T2)/2/(T1-T2) &
    &  +c2t*T1*(T1+4*T2)/2/(T1-T2)+(3+Nc)*T1&
    &+(20*T1**2-11*T1*T2-T2**2)/4/(T1-T2)) &
    & + T1*Log(mu2/q)*Log(t/q)+(mu2+t-T1)*Log(T1/q)*Log(t/q)
  tauFAc = tauFAc &
    & + (mu2+t-T1+c2t*mu2**2/(T1-T2))*Log(T1/q)*Log(mu2/q) +Log(BL/q)*Log(T1/q)* &
    & ( cb**2*(A0-BL-T1)*Yt/At/2-BL*sb**2*Xt/At+2*BL*mt*s2t*At/(T1-T2) &
    & - s2t*cb**2*mt*Yt*(A0+BL-T1)/(T1-T2) -cb**2*mt*Yt*s2t/2&
    &-c2t*cb**2*(A0+BL-T1)*(t-Yt**2)/2/(T1-T2) &
    & + c2t*BL*(t-T1-sb**2*Xt**2-cb**2*Yt**2)/(T1-T2) &
    & - (1-c2t)/2*BL-cb**2*((1+c2t)*t+(1-c2t)*Yt**2)/4) &
    &  +cb**2*Log(A0/q)*Log(T1/q)*( &
    & - mt*(3*A0-BL+T1)*Yt*(1./2/At/mt-s2t/(T1-T2)) &
    & - mt*Yt*s2t/2+c2t**2*Yt**2*(T1-T2-2*A0)/4/(T1-T2) &
    & - (6*A0+t+2*Yt**2)/4-c2t*(2*BL-2*A0-T1-T2)*(t-Yt**2)/4/(T1-T2) &
    & - c2t*A0*(T1+T2)/2/(T1-T2)) +cb**2*Log(A0/q)*Log(BL/q)* &
    & ( mt*T1*Yt*(1./2/At/mt-s2t/(T1-T2)) &
    & + s2t*mt*Yt/2-c2t*(t-Yt**2)*(T1+T2)/2/(T1-T2)) &
    & + cb**2*(A0*c2t**2*Yt**2/2/(T1-T2) +s2t**2*Yt**2/4)*Log(A0/q)*Log(T2/q) &
    & + Log(T2/q)**2*(3*s2t*mt*T2*At/2/(T1-T2)+ &
    & ( 2-c2t+c2t**2)*T2/4/(T1-T2)*(sb**2*Xt**2+cb**2*Yt**2) &
    & + Nc*(1+c2t**2)*T2**2/4/(T1-T2)-s2t**2*T2**2/4/(T1-T2) &
    & + BL*T2*(1-c2t)/4/(T1-T2)-(3-c2t)*mu2*T2/2/(T1-T2) &
    & + (3-c2t)*A0*T2*cb**2/4/(T1-T2)+(1+c2t)*t*T2/4/(T1-T2) &
    & + T2*(9*T2-(4+c2t)*T1)/4/(T1-T2)+(3+Nc)*T2/2) +Log(T1/q)*Log(T2/q)*( &
    & Nc*(4*T1*T2-s2t**2*(T1+T2)**2)/4/(T1-T2)+(1+c2t**2)/4*(T1-T2) &
    & + cb**2*c2t**2*Yt**2*(T1+T2-A0)/2/(T1-T2) &
    & +c2t**2*T2*(T1+sb**2*Xt**2)/(T1-T2)) &
    & + Log(T1/q)**2*( cb**2*mt*Yt*(A0-BL+T1)*(1./2/At/mt-s2t/(T1-T2)) &
    & + mt*(BL-6*T1)*(1./2/mt-s2t*At/(T1-T2)) &
    & + cb**2*s2t*mt*Yt/2-3*At*mt*(2*T1-T2)*s2t/2/(T1-T2) &
    & + Nc*T1*(3*(-2+s2t**2)*T1+2*s2t**2*T2)/4/(T1-T2) &
    & - sb**2*Xt**2/4/(T1-T2)*((5+2*c2t+3*c2t**2)*T1 &
    & + (-3+c2t+2*c2t**2)*T2-2*BL*c2t) &
    & - cb**2*Yt**2/4/(T1-T2)*((3+c2t+4*c2t**2)*T1-s2t**2*T2-2*A0*c2t**2) &
    & - (3+c2t)*cb**2*A0*T1/4/(T1-T2)-T1*BL*(1+c2t)/4/(T1-T2) &
    & -t*c2t*sb**2*BL/2/(T1-T2) &
    & + mu2/2/(T1-T2)*(2*(2+c2t)*T1-(1-c2t)*T2)-c2t*mu2**2/2/(T1-T2) &
    & + t/4/(T1-T2)*((-5+c2t-(1-c2t)*sb**2)*T1+(4+(1+c2t)*sb**2)*T2) &
    & - T1*((4+3*c2t**2)*T1+c2t*(3+2*c2t)*T2)/4/(T1-T2)-(3+Nc)*T1/2)

  End Function tauFAc
  

  Function tauresFAc(t,A0,BL,T1,T2,s2t,cb,sb,q,mu)
  Implicit None
  Real(dp) :: t,A0,BL,T1,T2,s2t,cb,sb,q,mu
  Real(dp) :: Xt,Yt
  Real(dp) :: tauresFAc
  Xt = s2t*(T1-T2)/2._dp/Sqrt(t)
  Yt = Xt - mu/cb/sb
  tauresFAc = -cb**2*A0*Yt*(A0-4*T1)/2/T1*phi(A0,T1,T1) &
    & - cb**2*Yt*delt(A0,BL,T1)/2/T1*phi(A0,BL,T1) +sb**2*Xt*(BL-T1)*Li2(1-BL/T1) &
    & + Log(BL/q)*Log(T1/q)*(cb**2*(A0-BL-T1)*Yt/2-BL*sb**2*Xt) &
    & - cb**2*Log(A0/q)*Log(T1/q)*(3*A0-BL+T1)*Yt/2&
    &+cb**2*Log(A0/q)*Log(BL/q)*T1*Yt/2+Log(T1/q)**2*cb**2*Yt*(A0-BL+T1)/2
  

  End Function tauresFAc
  
 End Subroutine Yukawa2L_PseudoScalar


 Subroutine Yukawa2L_Scalar(Q2, mA2, vevs, mD2, mU2, mQ2, ME2, ML2, A_b &
                    &, A_t, A_tau, Y_b, Y_t, Y_tau, mu, i_os, PiS2, kont)
 !-----------------------------------------------------------------------------
 ! in this routine the 2-loop contributions to the neutral scalar mass matrix
 !   Q2 .................. renormalization scale squared
 !   gSU3 ................ g_strong
 !   mglu ................ m_gluino
 !   mA2 ................. m_A0 squared
 !   vevs(i) ............. vacuum expactation values
 !   mD2 ................. M^2_(\tilde D)
 !   mU2 ................. M^2_(\tilde U)
 !   mQ2 ................. M^2_(\tilde Q)
 !   mE2 ................. M^2_(\tilde E)
 !   mL2 ................. M^2_(\tilde L)
 !   A_t ................. trilinear coupling A_top
 !   A_b ................. trilinear coupling A_bottom
 !   A_tau ............... trilinear coupling A_tau
 !   Y_t ................. top Yukawwa coupling
 !   Y_b ................. bottom Yukawwa coupling
 !   Y_tau ............... tau Yukawwa coupling
 !   mu .................. mu-parameter
 ! output:
 !  PiS2 ........ two-loop contribution to the scalar mass matrix
 !  kont ........ is 0 if everything is o.k., otherwise it gets a negative 
 !                value
 ! written by Werner Porod, 04.03.03
 !-----------------------------------------------------------------------------
 Implicit None
  Integer, intent(in) :: i_os
  Integer, Intent(inout) :: kont 
  Real(dp), Intent(in) :: Q2, mA2, vevs(2), mQ2, mU2, mD2, ML2, ME2
  Complex(dp), Intent(in) :: A_b, A_t, Y_t, Y_b, mu, A_tau, Y_tau
  Real(dp), Intent(out) :: PiS2(2,2)

  Real(dp) :: s2t, c2t, s2b, c2b, mt, tanb, mb, sb, cb, ht2, mSt(2)    &
    & , mSt2(2), mt2, mb2, mtau, mtau2, muR, mSb(2), mSb2(2), At, Ab   &
    & , hb2, vv, Atau, mStau(2), mStau2(2), s2tau, c2tau, htau2, mSneu2
  Real(dp) :: F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp, hthb       &
    & , F1, F2, F3, sF2, sF3 , F2_s, sF2_A, sF3_A, X, DF1, DF2, DF3, DsF2, DsF3 &
    & , Pi2Sa(2,2), htauhb, DdmuF2, DdmuF3, DM12, DM22, DdAtF2, DdAtF3, dmuF2   &
    & , dmuF3, dAtF2, dAtF3
  Complex(dp) :: RSt(2,2), RSb(2,2), Rstau(2,2)
  Real(dp), Parameter :: YL = 1._dp / 3._dp, YRu = -4._dp / 3._dp  &
       , YRd = 2._dp / 3._dp

  Iname = Iname + 1
  NameOfUnit(Iname) = "Yukawa2L_Scalar"

  PiS2 = 0._dp
  kont = 0

 !------------------------------------------------------------------------
 ! first the (s)fermion, please note, that the papers by P.Slavich et al. 
 ! the ordering of the sfermions is reversed to compared to my odering
 !------------------------------------------------------------------------
  Call SfermionMass(MQ2, MU2, A_t, mu, vevs, Y_t, 0.5_dp, YL, YRu,   &
  0._dp, 0._dp, kont, mSt, mSt2, RSt)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*)&
     "Stop masses squared for 2-loop calculation of pseudoscalar mass are negativ."
   kont = -604
   Call AddError(604)
   Iname = Iname - 1
   Return
  End If 
  mt2 = 0.5_dp * Abs(Y_t*vevs(2))**2

  Call SfermionMass(MQ2, MD2, A_b, mu, vevs, Y_b, -0.5_dp, YL, YRd,   &
  0._dp, 0._dp, kont, mSb, mSb2, RSb)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
     "Sbottommasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -605
   Call AddError(605)
   Iname = Iname - 1
   Return
  End If 

  mb2 = 0.5_dp * Abs(Y_b*vevs(1))**2

  Call SfermionMass(ML2, ME2, A_tau, mu, vevs, Y_tau, -0.5_dp, 1._dp, 2._dp,   &
                  & 0._dp, 0._dp, kont, mStau, mStau2, RStau)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
     "Staumasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -606
   Call AddError(606)
   Iname = Iname - 1
   Return
  End If 

  mtau2 = 0.5_dp * Abs(Y_tau*vevs(1))**2
  mtau = Sqrt(mtau2)
  s2tau = - 2._dp * Real( Rstau(1,1) * Rstau(1,2), dp)
  c2tau = Abs(Rstau(1,2))**2 -  Abs(Rstau(1,1))**2
  htau2 = Abs(Y_tau)**2

  mSneu2 = ML2
 !------------------------------------------------------------
 ! different mass ordering leads to the following formulas
 !------------------------------------------------------------
  s2t = - 2._dp * Real( RSt(1,1) * RSt(1,2), dp)
  c2t = Abs(RSt(1,2))**2 -  Abs(RSt(1,1))**2
  s2b = - 2._dp * Real( RSb(1,1) * RSb(1,2), dp)
  c2b = Abs(RSb(1,2))**2 -  Abs(RSb(1,1))**2

  mt = Sqrt(mt2)
  mb = Sqrt(mb2)
  ht2 = Abs(Y_t)**2
  hb2 = Abs(Y_b)**2

  tanb = vevs(2) / vevs(1)
  cb = 1._dp / Sqrt(1._dp + tanb**2)
  sb = tanb * cb
 
  At = Real(A_t/Y_t, dp)
  Ab = Real(A_b/Y_b, dp)
  Atau = Real(A_tau/Y_tau, dp)
  muR = - Real(mu, dp) ! different sign convention
  X = At + muR * vevs(1) / vevs(2)

!  !---------------------------------
!  ! alpha_s alpha_t
!  !---------------------------------
!   Call strfuncs(mt2, mglu, mst2(2), mst2(1), s2t, c2t, Q2, F1, F2, F3)
!   If (i_os.Ne.0) Then
!     Call strdfuncs(mt2, mglu, mst2(2), mst2(1), s2t, c2t, Q2   &
!       &  , At, X, DF1, DF2, DF3, DsF2, DsF3)
!   Else
!    DF1 = 0
!    DF2 = 0
!    DF3 = 0
!    DsF2 = 0
!    DsF3 = 0
!   End If

!   If ((s2t.Ne.0._dp).And.(At.Ne.0._dp)) Then
!    Call strsfuncs(mglu, mst2(2), mst2(1), Q2, At, sF2, sF3)
!    F1 = F1 + i_os * DF1
!    F2 = F2 + i_os * DF2
!    F3 = F3 + i_os * DF3
!    sF2 = sF2 + i_os * DsF2
!    sF3 = sF3 + i_os * DsF3
!    PiS2(1,1) = 0.5_dp * ht2 * muR**2 * s2t**2 * F3 ! eq. (25)
     
!    PiS2(1,2) = 0.5_dp * ht2 * muR * At * s2t**2 * (F3 + sF3)  &! eq. (26)
!            & + ht2 * mt * muR * s2t * F2
     
!    PiS2(2,2) = 0.5_dp * ht2 * At**2 * s2t**2 * (F3 + 2._dp*sF3)  &! eq. (27)
!            & + 2._dp * ht2 * ( mt * At * s2t * (F2 + sF2) + mt2 * F1 )

!   !     some of the functions have poles in s2t=0 or in A=0. 
!   !     when necessary we consider the residues:     
!   Else If ((s2t.Eq.0._dp).And.(At.Eq.0._dp)) Then
!    F1 = F1 + i_os * DF1
!    PiS2(1,1) = 0._dp
!    PiS2(1,2) = 0._dp
!    PiS2(2,2) = 2._dp * ht2 * mt2 * F1

!   Else If ((s2t.Eq.0._dp).And.(At.Ne.0._dp)) Then 
!    Call strresfuncs(mt2, mglu, mst2(2), mst2(1), q2, F2_s, sF2_A, sF3_A)     
!    F1 = F1 + i_os * DF1
!    F2_s = F2_s + i_os * DF2
!    PiS2(1,1) = 0._dp
!    PiS2(1,2) = ht2 * mt * muR * F2_s
!    PiS2(2,2) = 2._dp * ht2 * (mt2 * F1 + mt * At * F2_s)

!   Else If ((s2t.Ne.0._dp).And.(At.Eq.0._dp)) Then
!    Call strresfuncs(mt2, mglu, mst2(2), mst2(1), q2, F2_s, sF2_A, sF3_A)     
!    F1 = F1 + i_os * DF1
!    F2 = F2 + i_os * DF2
!    F3 = F3 + i_os * DF3
!    sF2_A = sF2_A + i_os * DsF2
!    sF3_A = sF3_A + i_os * DsF3
!    PiS2(1,1) = 0.5_dp * ht2 * muR**2 * s2t**2 * F3
!    PiS2(1,2) = 0.5_dp * ht2 * muR * s2t**2 * sF3_A + ht2 * mt * muR * s2t * F2
!    PiS2(2,2) = 2._dp * ht2 * (mt2 * F1 + mt * s2t * sF2_A)
 
!   End If

!   PiS2(2,1) = PiS2(1,2)
!   PiS2 = 4._dp * gSU3**2 * PiS2 ! gs^2 CF Nc

!  !---------------------------------------------
!  ! alpha_s alpha_b
!  !---------------------------------------------
!   X = Ab + muR * vevs(2) / vevs(1)

!   Call strfuncs(mb2, mglu, msb2(2), msb2(1), s2b, c2b, Q2, F1, F2, F3)
!   If (i_os.Eq.0) Then
!    DF1 = 0
!    DF2 = 0
!    DF3 = 0
!    DsF2 = 0
!    DsF3 = 0
!   Else
!    Call strdfuncs(mb2, mglu, msb2(2), msb2(1), s2b, c2b, Q2, Ab, X   &
!                 &, DF1, DF2, DF3, DsF2, DsF3)
!   End If

!   If ((s2b.Ne.0._dp).And.(Ab.Ne.0._dp)) Then
!    Call strsfuncs(mglu, msb2(2), msb2(1), Q2, Ab, sF2, sF3)
!    F1 = F1 + i_os * DF1
!    F2 = F2 + i_os * DF2
!    F3 = F3 + i_os * DF3
!    sF2 = sF2 + i_os * DsF2
!    sF3 = sF3 + i_os * DsF3
!    Pi2Sa(2,2) = 0.5_dp * hb2 * muR**2 * s2b**2 * F3 ! eq. (25)
     
!    Pi2Sa(1,2) = 0.5_dp * hb2 * muR * Ab * s2b**2 * (F3 + sF3)  &! eq. (26)
!             & + hb2 * mb * muR * s2b * F2
     
!    Pi2Sa(1,1) = 0.5_dp * hb2 * Ab**2 * s2b**2 * (F3 + 2._dp*sF3) &! eq. (27)
!             & + 2._dp * hb2 * ( mb * Ab * s2b * (F2 + sF2) + mb2 * F1 )

! !     some of the functions have poles in s2t=0 or in A=0. 
! !     when necessary we consider the residues:     
!   Else If ((s2b.Eq.0._dp).And.(Ab.Eq.0._dp)) Then
     
!    F1 = F1 + i_os * DF1
!    Pi2Sa(2,2) = 0._dp
!    Pi2Sa(1,2) = 0._dp
!    Pi2Sa(1,1) = 2._dp * hb2 * mb2 * F1

!   Else If ((s2b.Eq.0._dp).And.(Ab.Ne.0._dp)) Then 
!    Call strresfuncs(mb2, mglu, msb2(2), msb2(1), q2, F2_s, sF2_A, sF3_A)     
!    F1 = F1 + i_os * DF1
!    F2_s = F2_s + i_os * DF2
!    Pi2Sa(2,2) = 0._dp
!    Pi2Sa(1,2) = hb2 * mb * muR * F2_s
!    Pi2Sa(1,1) = 2._dp * hb2 * (mb2 * F1 + mb * Ab * F2_s)

!   Else If ((s2b.Ne.0._dp).And.(Ab.Eq.0._dp)) Then

!    Call strresfuncs(mb2, mglu, msb2(2), msb2(1), q2, F2_s, sF2_A, sF3_A)     
!    F1 = F1 + i_os * DF1
!    F2 = F2 + i_os * DF2
!    F3 = F3 + i_os * DF3
!    sF2_A = sF2_A + i_os * DsF2
!    sF3_A = sF3_A + i_os * DsF3

!    Pi2Sa(2,2) = 0.5_dp * hb2 * muR**2 * s2b**2 * F3
!    Pi2Sa(1,2) = 0.5_dp * hb2 * muR * s2b**2 * sF3_A + hb2 * mb * muR * s2b * F2
!    Pi2Sa(1,1) = 2._dp * hb2 * (mb2 * F1 + mb * s2b * sF2_A)
 
!   Endif
!   Pi2Sa(2,1) = Pi2Sa(1,2)
!   PiS2 = PiS2 + 4._dp * gSU3**2 * Pi2Sa ! gs^2 CF Nc

 !---------------------------------------------
 ! (alpha_t + alpha_b)^2
 !---------------------------------------------
  vv = vevs(1)**2 + vevs(2)**2 
  Call makefuncs(mt2, mb2, mA2, mst2(2), mst2(1), msb2(2), msb2(1) &
              & , s2t ,c2t, s2b, c2b, q2, muR, vv, tanb                &
              & , F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp)

  hthb = Sqrt(ht2*hb2)
  Pi2Sa(1,1) = 0.5_dp * ht2 * muR**2 * s2t**2 *F3t                           &
           & + 2._dp * hb2 * mb**2 * F1b + 2._dp * hb2 * Ab * mb * s2b *F2b &
           & + 0.5_dp * hb2 * Ab**2 * s2b**2 * F3b                          &
           & + 2._dp * hthb * mb * muR * s2t * F4t                           &
           & + hthb * muR* Ab *s2t * s2b * F5

  Pi2Sa(1,2) = ht2*muR*mt*s2t*F2t + 0.5_dp*ht2*At*muR*s2t**2*F3t       &
           & + hb2*muR*mb*s2b*F2b + 0.5_dp*hb2*Ab*muR*s2b**2*F3b       &
           & + hthb*mb*At*s2t*F4t + hthb*mt*Ab*s2b*F4b                &
           & + 0.5_dp*hthb*s2t*s2b*(At*Ab+muR**2)*F5+2._dp*hthb*mt*mb*F6
 
  Pi2Sa(2,2) = 0.5_dp*hb2*muR**2*s2b**2*F3b                         &
           & + 2._dp*ht2*mt**2*F1t + 2._dp*ht2*At*mt*s2t*F2t       &
           & + 0.5_dp*ht2*At**2*s2t**2*F3t                         &
           & + 2._dp*hthb*mt*muR*s2b*F4b + hthb*muR*At*s2b*s2t*F5

  Pi2Sa(2,1) = Pi2Sa(1,2)
  PiS2 = PiS2 + 3._dp * Pi2Sa
  
 !---------------------------------------------
 ! alpha_tau * alpha_b
 !---------------------------------------------
  htauhb = Sqrt(htau2*hb2)
  Call makefuncstau(mtau2,mb2,mStau2(2), mStau2(1), mSb2(2)    &
        & , mSb2(1), s2tau, c2tau, s2b, c2b, Q2 ,muR, vv, tanb  &
        & , F1t, F2t, F3t, F4t, F1b, F2b, F3b, F4b, F5, F6, Ft, Fb, Gt, Gb, FAp)

  Pi2Sa(1,1) = 2._dp*hb2*mb2*F1b + 2._dp*hb2*Ab*mb*s2b*F2b                 &
          & + 0.5_dp*hb2*Ab**2*s2b**2*F3b                                    &
          & + 2._dp*htau2*mtau2*F1t + 2._dp*htau2*Atau*mtau*s2tau*F2t          &
          & + 0.5_dp*htau2*Atau**2*s2tau**2*F3t                                &
          & + 2._dp*htauhb*mb*Atau*s2tau*F4t + 2._dp*htauhb*mtau*Ab*s2b*F4b  &
          & + htauhb*Atau*Ab*s2tau*s2b*F5 + 4._dp*htauhb*mtau*mb*F6

  Pi2Sa(1,2) = htau2*muR*mtau*s2tau*F2t + 0.5_dp*htau2*Atau*muR*s2tau**2*F3t   &
          & + hb2*muR*mb*s2b*F2b + 0.5_dp*hb2*Ab*muR*s2b**2*F3b    &
          & + htauhb*mb*muR*s2tau*F4t + htauhb*mtau*muR*s2b*F4b              &
          & + 0.5_dp*htauhb*s2tau*s2b*muR*(Atau+Ab)*F5

  Pi2Sa(2,2) =0.5_dp*hb2*muR**2*s2b**2*F3b+0.5_dp*htau2*muR**2*s2tau**2*F3t &
          & + htauhb*muR**2*s2b*s2tau*F5

  Pi2Sa(2,1) = Pi2Sa(1,2)

  PiS2 = PiS2 + 3._dp * Pi2Sa

 !-------------
 ! alpha_tau^2
 !-------------
  Call taufuncs(mtau2, mA2, mSneu2, mStau2(2), mStau2(1), s2tau, c2tau &
               & , sb, cb, Q2, muR, F1, F2, F3)
  Call tausfuncs(mtau2, mStau2(2), mStau2(1) ,s2tau, Q2, muR, Atau, sqrt(htau2) &
               & , dmuF2, dmuF3, dAtF2, dAtF3, DM12, DM22)
  If (i_os.ne.0) then
   Call taudfuncs(mtau2, mA2, mSneu2, mStau2(2), mStau2(1), s2tau, c2tau &
                & , sb, cb, Q2, muR, Atau, vv, DF1, DF2, DF3, DdmuF2, DdmuF3 &
                & , DdAtF2, DdAtF3)
  Else
   DF1 = 0._dp
   DF2 = 0._dp
   DF3 = 0._dp
   DdmuF2 = 0._dp
   DdmuF3 = 0._dp
   DdAtF2 = 0._dp
   DdAtF3 = 0._dp
  End If

  If(s2tau/=0._dp.And.Atau/=0._dp) Then
    Pi2Sa(1,1) = 0.5_dp * htau2 * muR**2 * s2tau**2 &
      & * (F3 + 2._dp*dmuF3 + i_os*(DF3 + 2._dp*DdmuF3))
    
    Pi2Sa(1,2) = 0.5_dp * htau2 * muR * Atau  * s2tau**2                            &
      &          * (F3 + dmuF3 + dAtF3 + i_os*(DF3 + DdmuF3 + DdAtF3)) &
      &  + htau2 * mtau * muR * s2tau * (F2 + dmuF2 + i_os*(DF2 + DdmuF2))
    
    Pi2Sa(2,2) = 0.5_dp * htau2 * Atau**2 * s2tau**2                          &
      &          * (F3 + 2._dp*dAtF3 + i_os*(DF3 + 2._dp*DdAtF3)) &
      & + 2._dp * htau2 * mtau * Atau * s2tau                            &
      &         * (F2 + dAtF2 + i_os*(DF2 + DdAtF2))              &
      & + 2._dp * htau2 * mtau2 * (F1 + i_os*DF1)
    
  !     some of the functions have poles in s2tau=0 or in Atau=0. 
  !     when necessary we consider the residues:
    
  Elseif(s2tau==0._dp.And.Atau==0._dp) Then
    
    Pi2Sa(1,1) = 0._dp
    Pi2Sa(1,2) = 0._dp
    Pi2Sa(2,2) = 2 * htau2 * mtau2 * (F1 + i_os*DF1)

  Elseif(s2tau==0._dp.And.Atau/=0._dp) Then 
    Call tauresfuncs(mtau2, mA2, mSneu2, mStau2(2), mStau2(1), s2tau, c2tau &
                   & , sb, cb, Q2, muR, F2_s)
    Pi2Sa(1,1) = 0._dp
    Pi2Sa(1,2) = htau2 * mtau * muR * (F2_s + i_os*DF2)
    Pi2Sa(2,2) = 2._dp * htau2 * mtau2 * (F1 + i_os*DF1) &
      & + 2._dp * htau2 * mtau * Atau * (F2_s + i_os*(DF2 + DdAtF2))
  Elseif(s2tau/=0._dp.And.Atau==0._dp) Then
    Pi2Sa(1,1) = 0.5_dp * htau2 * muR**2 * s2tau**2         &
      &          * (F3 + 2._dp*dmuF3 + i_os*(DF3 + 2._dp*DdmuF3))
    Pi2Sa(1,2) = 0.5_dp * htau2 * muR * s2tau**2 * i_os*DdAtF3 &
      & + htau2 * mtau * muR * s2tau * (F2 + dmuF2 +i_os*(DF2 + DdmuF2))
    Pi2Sa(2,2) = 2._dp * htau2 * mtau2 * (F1 + i_os*DF1) &
             & + 2._dp * htau2 * mtau * s2tau * i_os*DdAtF2
    
  Endif
  
  Pi2Sa(2,2) = Pi2Sa(1,1)
  Pi2Sa(1,2) = Pi2Sa(1,2) + DM12
  Pi2Sa(1,1) = Pi2Sa(2,2) + DM22

  Pi2Sa(2,1) = Pi2Sa(1,2)

  PiS2 = PiS2 + htau2 * Pi2Sa

  PiS2 = oo16Pi2**2 * PiS2

  Iname = Iname - 1

 Contains

 !----------------------------------------------------------------------
 ! the following functions and subroutines are taken from the routines
 ! provided by P.Slavich
 !----------------------------------------------------------------------
  Subroutine strfuncs(t,mg,T1,T2,s2t,c2t,q,F1,F2,F3)
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,T2,s2t,c2t,q
   Real(dp), Intent(out) :: F1,F2,F3

   F1 = strF1ab(t,T1,T2,s2t,c2t,q) + strF1c(t,mg,T1,s2t,q)   &
      & + strF1c(t,mg,T2,-s2t,q)
  
   F2 = strF2ab(T1,T2,s2t,c2t,q) + strF2c(t,mg,T1,T2,s2t,q)   &
      & - strF2c(t,mg,T2,T1,-s2t,q)

   F3 = strF3ab(T1,T2,s2t,c2t,q)  + strF3c(t,mg,T1,T2,s2t,q)  &
      & + strF3c(t,mg,T2,T1,-s2t,q)

  End Subroutine strfuncs

  Subroutine strdfuncs(t,mg,T1,T2,s2t,c2t,q,At,X,DF1,DF2,DF3,DsF2,DsF3) 
  !     shift of the parameters from DRbar to On-Shell scheme
  Implicit None      
   Real(dp), Intent(in) ::  t,mg,T1,T2,s2t,c2t,q,At,X
   Real(dp), Intent(out) ::  DF1,DF2,DF3,DsF2,DsF3
   Real(dp) :: F1o,F2o,F3o,dm1,dm2,dmt,dAt,dth,ds2t,mt, g
   Real(dp), Parameter :: msdr = -5._dp

   g = mg**2
   mt = Sqrt(t)

   F1o = Log(T1/q) + Log(T2/q) - 2._dp*Log(t/q) ! eq. (31)
   F2o = Log(T1/q) - Log(T2/q) 
   F3o = 2._dp - (T1+T2)/(T1-T2)*(Log(T1/q) - Log(T2/q))

   dmt = mt*(3*Log(t/q) + msdr + 1./2.*(2*g/t*(Log(g/q)-1)   & ! eq. (B2)
     & - T1/t*(Log(T1/q)-1) - T2/t*(Log(T2/q)-1)             &
     & + (g+t-T1 - 2*s2t*mg*mt)/t*B0(t,g,T1)             &
     & + (g+t-T2 + 2*s2t*mg*mt)/t*B0(t,g,T2)))

   dm1 = T1*(3*Log(T1/q) - 7 - c2t**2*(Log(T1/q)-1)          &  ! eq. (B3)
     & - s2t**2*T2/T1*(Log(T2/q)-1) + 2*(                    &
     &   g/T1*(Log(g/q)-1) + t/T1*(Log(t/q)-1)               &
     & + (T1-g-t + 2*s2t*mg*mt)/T1*B0(T1,t,g)))
  
   dm2 = T2*(3*Log(T2/q) - 7 - c2t**2*(Log(T2/q)-1)          & ! eq. (B4)
     & - s2t**2*T1/T2*(Log(T1/q)-1) + 2*(                    &
     &   g/T2*(Log(g/q)-1) + t/T2*(Log(t/q)-1)               &
     & + (T2-g-t - 2*s2t*mg*mt)/T2*B0(T2,t,g)))

   !     On-Shell theta-stop: eq. (B6)-(B7) of DSZ 
   dth = (4._dp*mg*mt*c2t*(B0(T1,t,g)+B0(T2,t,g)) +            &
     &     2._dp*c2t*s2t*(T2*(1._dp-Log(T2/q))-T1*(1._dp-Log(T1/q)))) &
     &   / 2._dp/(T1-T2)      

   ds2t = 2._dp*c2t*dth

   dAt = ((dm1-dm2)/(T1-T2) + ds2t/s2t - dmt/mt)*X ! eq. (B8)

   DF1 = dm1/T1 + dm2/T2 - 4._dp*dmt/mt + 4._dp*dmt/mt*F1o ! eq. (37)
   DF2 = dm1/T1 - dm2/T2 + (3._dp*dmt/mt + ds2t/s2t)*F2o ! eq. (38)
   DF3 = (2._dp*T1*T2/(T1-T2)**2*Log(T1/T2) - (T1+T2)/(T1-T2))    &
    &     *(dm1/T1-dm2/T2) + (2._dp*dmt/mt + 2._dp*ds2t/s2t)*F3o ! eq. (39)

   DsF2 = dAt/At * F2o       ! eq. (40)
   DsF3 = dAt/At * F3o       ! eq. (41)

  !     residues of some singular functions for s2t=0 and for A=0

   If(s2t.Eq.0._dp) Then
     DF2  = ds2t*F2o
     DsF2 = ds2t*X/At * F2o
   Endif

   If(At.Eq.0._dp) Then
     DsF2 = dAt * F2o
     DsF3 = dAt * F3o
   Endif

  End Subroutine strdfuncs

  Real(dp) Function strF1ab(t,T1,T2,s2t,c2t,q)
  Implicit None
   Real(dp), Intent(in) :: t,T1,T2,s2t,c2t,q

   strF1ab =                                                   & ! eq. (32) 
    &     -6*(1-Log(t/q))+5*Log(T1*T2/t**2)+Log(T1*T2/t**2)**2   &
    &     +8*Log(t/q)**2-4*Log(T1/q)**2-4*Log(T2/q)**2           &
    &     -c2t**2*(2-Log(T1/q)-Log(T2/q)-Log(T1/T2)**2)          &
    &     -s2t**2*(T1/T2*(1-Log(T1/q))+T2/T1*(1-Log(T2/q)))
  
  End Function strF1ab

  Real(dp) Function strF1c(t,mg,T1,s2t,q)
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,s2t,q
   Real(dp) :: del, g, mt

   g = mg**2
   mt = Sqrt(t)
   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
  
   strF1c =                                                      & ! eq. (A1)
    &     +4*(t+g-mg*mt*s2t)/T1*(1-Log(g/q))                   &
    &     +4*Log(t/g) - 2*Log(T1/g)                                &
    &     +2./del*(4*g**2*Log(T1/g)                                &
    &     +(g**2-T1**2+t*(10*g+3*t+2*t*g/T1-2*t**2/T1))*Log(t/g))  &
    &     +2*mg/mt*s2t*(Log(T1/q)**2+2*Log(t/q)*Log(T1/q))     &
    &     +4*mg/mt*s2t/del*(g*(T1-t-g)                         &
    &     *Log(T1/g)+t*(T1-3*g-2*t-(t*g-t**2)/T1)*Log(t/g))        &
    &     +(4*g*(t+g-T1-2*mg*mt*s2t)/del                       &
    &     -4*mg/mt*s2t)*phi(t,T1,g)

  End Function strF1c

  Real(dp) Function strF2ab(T1,T2,s2t,c2t,q)
  Implicit None
   Real(dp), Intent(in) :: T1,T2,s2t,c2t,q

   strF2ab =                                                  &  ! eq. (33)
    &     5*Log(T1/T2)-3*(Log(T1/q)**2-Log(T2/q)**2)            &
    &     +c2t**2*(5*Log(T1/T2)                                 &
    &     -(T1+T2)/(T1-T2)*Log(T1/T2)**2                        &
    &     -2/(T1-T2)*(T1*Log(T1/q)-T2*Log(T2/q))*Log(T1/T2))    &
    &     +s2t**2*(T1/T2*(1-Log(T1/q))-T2/T1*(1-Log(T2/q)))
  
  End Function strF2ab

  Real(dp) Function strF2c(t,mg,T1,T2,s2t,q)
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,T2,s2t,q
   Real(dp) :: del, g, mt

   g = mg**2
   mt = Sqrt(t)
   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
  
   strF2c =                                                      & ! eq. (A2)
    &     4*(t+g)/T1-4*mg/mt*s2t/(T1-T2)*(3*T1-t*T2/T1)        &
    &     +2*mg/mt*s2t/(T1-T2)*(                               &
    &     (4*t+5*T1+T2)*Log(T1/q)-2*t*T2/T1*Log(g/q))              &
    &     -4*(g+t)/T1*Log(g/q) - 2*Log(T1/g)                       &
    &     +2/del*(2*g*(g+t-T1)*Log(T1/g)                           &
    &     +2*t*(3*g+2*t-T1+(g*t-t**2)/T1)*Log(t/g))                &
    &     -4*mg*mt*s2t/del/T1*(2*g*T1*Log(T1/g)-               &
    &     ((t-T1)**2-g*(t+T1))*Log(t/g))                           &
    &     -8*mg*mt/s2t/(T1-T2)*(Log(T1/q)-Log(t/q)*Log(T1/q))  &
    &     -mg/mt*s2t/(T1-T2)*((T1+T2)*Log(T1/q)**2             &
    &     +(10*t-2*g+T1+T2)*Log(t/q)*Log(T1/q)                     &
    &     +(2*g-2*t+T1+T2)*Log(T1/q)*Log(g/q))                     &
    &     +(8*g*t/del-8*mg*mt/s2t/(T1-T2)                      &
    &     +2*s2t/mg/mt/(T1-T2)*(4*g*t-del)                     &
    &     +s2t/mg/mt/del*(T1-g-t)**3)*phi(t,T1,g)

  End Function strF2c

  Real(dp) Function strF3ab(T1,T2,s2t,c2t,q)
  Implicit None
   Real(dp), Intent(in) :: T1,T2,s2t,c2t,q

   strF3ab =                                                    & ! eq. (34)
    &     (3+9*c2t**2)*(2-(T1+T2)/(T1-T2)*Log(T1/T2))             &
    &     +4-(3+13*c2t**2)/(T1-T2)*(T1*Log(T1/q)-T2*Log(T2/q))    &
    &     +3*(T1+T2)/(T1-T2)*(Log(T1/q)**2-Log(T2/q)**2)          &
    &     -c2t**2*(4-((T1+T2)/(T1-T2))**2*Log(T1/T2)**2           &
    &     -6*(T1+T2)/(T1-T2)**2                                   &
    &     *(T1*Log(T1/q)-T2*Log(T2/q))*Log(T1/T2))                &
    &     -s2t**2*(T1/T2+T2/T1 + 2*Log(T1*T2/q**2)                &
    &     -T1**2/T2/(T1-T2)*Log(T1/q)                             &
    &     +T2**2/T1/(T1-T2)*Log(T2/q))

  End Function strF3ab

  Real(dp) Function strF3c(t,mg,T1,T2,s2t,q)
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,T2,s2t,q
   Real(dp) :: del, g, mt

   g = mg**2
   mt = Sqrt(t)
   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
  
   strF3c =                                                        & ! eq. (A3)
   &     -4*T2/T1/(T1-T2)*(g+t)                                     &
   &     +4*mg*mt*s2t/(T1-T2)**2*(21*T1-T2**2/T1)               &
   &     +4/(T1-T2)*(g*T2/T1*Log(g/q)-2*(t+g)*Log(T1/q))            &
   &     -24*mg*mt*s2t/(T1-T2)**2*(3*T1+T2)*Log(T1/q)           &
   &     +4*t/T1/del*(2*g*T1*Log(T1/q)-g*(g-t+T1)*Log(g/q)+         &
   &     (g*(T+T1)-(t-T1)**2)*Log(t/q))                             &
   &     -4*mg*mt*s2t/T1/del*(t*(g-t+T1)*Log(t/q)               &
   &     -g*(g-t-T1)*Log(g/q)+T1*(g+t-T1)*Log(T1/q))                &
   &     +2*(2*g+2*t-T1-T2)/(T1-T2)*Log(g*t/q**2)*Log(T1/q)         &
   &     +12*mg*mt*s2t/(T1-T2)**2*(2*(g-t)*Log(g/t)*Log(T1/q)   &
   &     +(T1+T2)*Log(t*g/q**2)*Log(T1/q))                          &
   &     +8*mg*mt/s2t/(T1-T2)**2*                               &
   &     (-8*T1+2*(3*T1+T2)*Log(T1/q)-2*(g-t)*Log(g/t)*Log(T1/q)    &
   &     -(T1+T2)*Log(t*g/q**2)*Log(T1/q))                          &
   &     -((8/s2t-12*s2t)*Sqrt(t/g)/(T1-T2)**2                      &
   &     *(2*del+(g+t-T1)*(T1-T2))                                  &
   &     +(4*del+8*g*t)/g/(T1-T2)+2*(g+t-T1)/g                      &
   &     -4*t*(g+t-T1- 2*mg*mt*s2t)/del)*phi(t,T1,g)

  End Function strF3c

  Subroutine strsfuncs(mg,T1,T2,q,A,sF2,sF3)
 !     shift to the Fi functions due to the renormalization of A
  Implicit None
   Real(dp), Intent(in) :: mg,T1,T2,q,A
   Real(dp), Intent(out) :: sF2,sF3

   sF2  = mg/A * 2._dp*(Log(T2/q)**2 - Log(T1/q)**2) ! eq. (35)
  
   sF3  = mg/A *                                              & ! eq. (36)
    &     (8._dp - 2._dp*(T1+T2)/(T1-T2)*(Log(T2/q)**2 - Log(T1/q)**2)  &
    &  + 8._dp/(T1-T2)*(T2*Log(T2/q) - T1*Log(T1/q)))
  
  End Subroutine strsfuncs

  Subroutine strresfuncs(t,mg,T1,T2,q,F2_s,sF2_A,sF3_A)
 !     residues of some singular functions for s2t=0 and for A=0
  Implicit None      
   Real(dp), Intent(in) :: t,mg,T1,T2,q
   Real(dp), Intent(out) :: sF2_A,sF3_A,F2_s
   Real(dp) :: g, mt

   g = mg**2
   mt = Sqrt(t)

   F2_s =  -8*mg*mt/(T1-T2)*(                           &
     &     (Log(T1/q)-Log(t/q)*Log(T1/q)+phi(t,T1,g))-     &
     &     (Log(T2/q)-Log(t/q)*Log(T2/q)+phi(t,T2,g)))
  
   sF2_A = mg * 2._dp*(Log(T2/q)**2 - Log(T1/q)**2)
  
   sF3_A = mg * (8._dp-2._dp*(T1+T2)/(T1-T2)*(Log(T2/q)**2-Log(T1/q)**2) &
      & + 8._dp/(T1-T2)*(T2*Log(T2/q) - T1*Log(T1/q)))

  End Subroutine strresfuncs


  Subroutine taufuncs(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu,F1,F2,F3)
  Implicit None
  Real(dp) :: t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu,F1,F2,F3

  F1 = tauF1ab(t,A0,BL,T1,T2,cb,sb,q,mu) &
   & + tauF1c(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)  &
   & + tauF1c(t,A0,BL,T2,T1,-s2t,-c2t,cb,sb,q,mu)
  
  F2 = tauF2ab(T1,T2,q)                          &
   & + tauF2c(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)  &
   & - tauF2c(t,A0,BL,T2,T1,-s2t,-c2t,cb,sb,q,mu)

  F3 = tauF3ab(T1,T2,q)                          &
   & + tauF3c(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)  &
   & + tauF3c(t,A0,BL,T2,T1,-s2t,-c2t,cb,sb,q,mu)

  End Subroutine taufuncs
  
  
  Function tauF1ab(t,A0,BL,T1,T2,cb,sb,q,mu)
  Implicit None
  Real(dp) :: tauF1ab
  Real(dp) :: t,mu2,A0,BL,T1,T2,cb,sb,q,mu
  Real(dp) :: d_BLmu2t, log_tq, log_t1q, log_t2q, log_BLq, log_mu2q
  mu2 = mu**2
  If(mu2==0._dp) mu2 = Epsilon(1._dp)

  d_BLmu2t = delt(BL,mu2,t)
  log_tq = Log(t/q)
  log_t1q = Log(T1/q)
  log_t2q = Log(T2/q)
  log_BLq = Log(BL/q)
  log_mu2q = Log(mu2/q)

  tauF1ab = (2._dp*BL*mu2/t*(mu2-BL+t)/d_BLmu2t                    &
    & + (BL+mu2-t)/t)*phi(BL,mu2,t)                                &
    & + 2._dp*A0*cb**2*(A0-6.*t)/(A0-4.*t)/t*phi(A0,t,t)           &
    & - 2._dp*cb**2*Li2(1.-A0/t) - 2._dp - (2._dp+sb**2)/3.*Pi**2  &
    & + log_tq*( (4._dp*(BL-mu2-10.*t)*t                           &
    &          + A0* (mu2-BL+(6.+4._dp*sb**2)*t))/(A0-4._dp*t)/t   &
    &          + 1._dp/d_BLmu2t*((BL-mu2)**3/t                     &
    &          + (2._dp*mu2**2+2._dp*BL*mu2+5.*BL*t+mu2*t          &
    &          -4._dp*BL**2-2._dp*t**2)))                          &
    & + Log(A0/q)*(4._dp*A0*cb**2/(A0-4._dp*t))                    &
    & + log_BLq*(-BL/t+BL*(-BL+mu2+t)**2/t/d_BLmu2t)               &
    & + log_mu2q*(mu2/t+mu2*(t**2-(BL-mu2)**2)/t/d_BLmu2t)         &
    & + (log_tq**2-log_t1q**2/2._dp-log_t2q**2/2._dp)              &
    & + log_BLq*log_mu2q-log_BLq*log_tq-log_mu2q*log_tq            &
    & - 3._dp*log_tq**2-2._dp*log_t1q**2-2._dp*log_t2q**2

  End Function tauF1ab
  
  
  Function tauF1c(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)
  Implicit None
  Real(dp) :: t,mu2,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu
  Real(dp) :: Xt,Yt,st2,ct2,mt
  Real(dp) :: tauF1c
  Real(dp) :: d_T1mu2t, log_tq, log_t1q, log_t2q, log_BLq, log_A0q, d_A0T1T2 &
     & , d_A0T1BL  

  mu2 = mu**2
  If(mu2==0._dp) mu2 = Epsilon(1._dp)
  mt = Sqrt(t)

  Xt  = s2t*(T1-T2)/2._dp/mt
  Yt  = s2t*(T1-T2)/2._dp/mt - mu/sb/cb
  ct2 = (1._dp+c2t)/2._dp
  st2 = (1._dp-c2t)/2._dp
  
  d_T1mu2t = delt(T1,mu2,t)
  d_A0T1T2 = delt(A0,T1,T2)
  d_A0T1BL = delt(A0,T1,BL)
  log_tq = Log(t/q)
  log_t1q = Log(T1/q)
  log_t2q = Log(T2/q)
  log_BLq = Log(BL/q)
  log_A0q = Log(A0/q)

  tauF1c = 2._dp*mu2**2*(mu2+t-T1)/T1/d_T1mu2t*phi(mu2,t,T1)                &
       & - A0**2*(1+c2t**2)*cb**2*Yt**2 /2./T2/d_A0T1T2*phi(A0,T1,T2)       &
       & - cb**2*A0/T1*((2._dp*mt+s2t*Yt)/mt                                &
       & + (2._dp*mt+s2t*Yt)**2/2._dp/(A0-4._dp*T1))*phi(A0,T1,T1)          &
       & - cb**2/T1*phi(A0,BL,T1)                                           &
       &           *(2._dp*A0*BL*(ct2*t+s2t*Yt*mt+st2*Yt**2)/d_A0T1BL       &
       &            +(A0+BL-T1)*((1.+c2t)*mt+s2t*Yt)/2._dp/mt)              &
       & + sb**2*(1+c2t+s2t*Xt/mt)*Li2(1-BL/T1) +(1-c2t)*Li2(1-mu2/T1)      &
       & + s2t**2*(T1-T2)**2/4._dp/T1/T2                                    &
       & + (1._dp/3._dp+s2t*(sb**2*(Xt-Yt)+Yt)/4._dp/mt)*pi2                &
       & - 3._dp*s2t*(sb**2*Xt+cb**2*Yt)*(2._dp*t-T1)/2._dp/mt/T1           &
       & - (sb**2*Xt**2+cb**2*Yt**2)/4._dp/T1/T2                            &
       &   * ((1.+c2t**2)*T1+(5.-2._dp*c2t-c2t**2)*T2)                      &
       & + (3._dp-c2t)*mu2/T1-(3._dp-c2t)*cb**2*A0/2._dp/T1                 &
       & - (1.+c2t)*t/2._dp/T1 - (1.-c2t)*BL/2._dp/T1                       &
       & - (1.+c2t**2)*(T1**2+T2**2)/4._dp/T1/T2+ 2.5_dp +c2t/2._dp         &
       & - s2t**2/2._dp+log_tq*(1.+mu2/t-t/T1-T1/t                          &
       & + (-(mu2-T1)**3/t + 4._dp*mu2**2 + 5.*mu2*t + 2._dp*t**2           &
       & + mu2**2*t/T1-t**3/T1-2._dp*mu2*T1-2._dp*T1**2)/d_T1mu2t)          &
       & + Log(mu2/q)*(mu2*((-2.+c2t)*t+T1)/t/T1                            &
       & -mu2*((T1-t)**3+2._dp*mu2*(t-T1)*T1+mu2**2*(t+T1)) /t/T1/d_T1mu2t) &
       & +log_BLq*((1-c2t)/2._dp*BL/T1-cb**2*BL*(A0-BL+T1)/T1/d_A0T1BL*     &
       &      (ct2*t+s2t*Yt*mt+st2*Yt**2)                                   &
       & + sb**2*BL*(ct2*t+s2t*Xt*mt+st2*Xt**2)/(BL-T1)/T1)                 &
       & + log_A0q*((3._dp-c2t)*A0*cb**2/2._dp/T1                           &
       & +A0*cb**2*(2._dp*mt+s2t*Yt)**2/2._dp/(A0-4._dp*T1)/T1              &
       & +A0*(1+c2t**2)*cb**2*(A0*(T1+T2)-(T1-T2)**2)                       &
       &      *Yt**2 /4._dp/T1/T2/d_A0T1T2                                  &
       & +A0*cb**2*(A0-BL-T1)/T1/d_A0T1BL* (ct2*t+s2t*Yt*mt+st2*Yt**2))     &
       & +log_t2q*((1+c2t**2)*T2/4._dp/T1-s2t**2*T2/4._dp/T1                &
       & -cb**2*(1+c2t**2)*Yt**2/4._dp/T2+sb**2*(1+c2t**2)*Xt**2/4._dp/T1   &
       & +cb**2*(1+c2t**2)*Yt**2/4._dp/T1/T2/d_A0T1T2*                      &
       & (A0**2*T1-A0*(2._dp*T1**2+5*T1*T2+T2**2)+(T1-T2)**2*(T1+T2)))
  tauF1c = tauF1c                                                           &
       & +log_t1q*(cb**2*(ct2*t+s2t*Yt*mt+st2*Yt**2)*                       &
       &     (1./T1-(A0+BL-T1)/d_A0T1BL)                                    &
       & + cb**2*(1+c2t**2)*Yt**2/4._dp/T1/T2/d_A0T1T2*                     &
       &       (A0**2*T2-A0*(T1**2+5*T1*T2+2._dp*T2**2)+(T1-T2)**2*(T1+T2)) &
       & + 1./d_T1mu2t*((mu2-T1)**2*T1/t-(mu2-t)**2*(mu2+t)/T1              &
       & + 6.*mu2**2+4._dp*mu2*t+2._dp*t**2-3._dp*mu2*T1-2._dp*T1**2)       &
       & + cb**2*(A0-8.*T1)/2._dp/T1/(A0-4._dp*T1)*(2*mt+s2t*Yt)**2         &
       & + sb**2*(BL-2._dp*T1)/T1/(BL-T1)* (ct2*t+s2t*Xt*mt+st2*Xt**2)      &
       & - (1-c2t)*(mu2-2._dp*T1)/2._dp/T1-s2t**2*(T1-2._dp*T2)/4._dp/T2    &
       & + sb**2*c2t*(1-c2t)*Xt**2/2._dp/T1+sb**2*(1+c2t**2)*Xt**2/4._dp/T2 &
       & + sb**2*s2t*(t-3._dp*T1)/mt/T1*Xt-3._dp*cb**2*s2t*(t+T1)/mt/T1*Yt  &
       & - cb**2*(5.-2._dp*c2t-c2t**2)*Yt**2/4._dp/T1-(3._dp+c2t-8.*sb**2)  &
       & *t/2._dp/T1 +(3._dp-c2t)/2._dp/T1*mu2+(1+c2t**2)*T1/4._dp/T2-T1/t  &
       & +(-14+c2t-c2t**2)/2._dp) +2._dp*s2t**2/4._dp*                      &
       &        (3._dp*log_t1q**2-2._dp*log_t1q*log_t2q-log_t2q**2)         &
       & +s2t*(6.*sb**2*Xt+5*cb**2*Yt)/2._dp/mt*log_t1q**2                  &
       & +(9.+sb**2-cb**2*c2t)/2._dp*log_t1q**2                             &
       & +log_t1q*log_t2q-2._dp*log_tq*log_t1q                              &
       & +cb**2*(1.+c2t+s2t*Yt/mt)/2._dp*(log_A0q*log_t1q                   &
       & +log_BLq*log_t1q-log_A0q*log_BLq)

  End Function tauF1c
  

  Function tauF2ab(T1,T2,q)
  
  Implicit None
  Real(dp) :: T1,T2,q
  Real(dp) :: tauF2ab
  
  tauF2ab = -0.5_dp*(Log(T1/q)**2-Log(T2/q)**2)

  End Function tauF2ab
  

  Function tauF2c(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)
  Implicit None
  Real(dp) :: t,mu2,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu
  Real(dp) :: ct2,st2,Xt,Yt,At, mt
  Real(dp) :: tauF2c
  Real(dp) :: d_T1mu2t, log_t1q, log_t2q, log_BLq, log_A0q, d_A0T1T2 &
     & , d_A0T1BL  

  mu2 = mu**2
  If(mu2==0._dp) mu2 = Epsilon(1._dp)
  mt = Sqrt(t)

  Xt = s2t*(T1-T2)/2._dp/mt
  Yt = Xt - mu/cb/sb
  At = sb**2*Xt+cb**2*Yt
  ct2 = (1._dp+c2t)/2._dp
  st2 = (1._dp-c2t)/2._dp

  d_T1mu2t = delt(T1,mu2,t)
  d_A0T1T2 = delt(A0,T1,T2)
  d_A0T1BL = delt(A0,T1,BL)
  log_t1q = Log(T1/q)
  log_t2q = Log(T2/q)
  log_BLq = Log(BL/q)
  log_A0q = Log(A0/q)

  tauF2c = 4*mu2**2*t/T1/d_T1mu2t*phi(mu2,t,T1) +(A0*c2t**2*Yt**2/(T1-T2)/T2  &
       & + (1+c2t**2)/2._dp*(T1/T2-1)*Yt**2*A0/d_A0T1T2) *cb**2*phi(A0,T1,T2) &
       & - (2*A0*c2t**2*mt*Yt/s2t/T1/(T1-T2) &
       & + s2t*(A0*Yt/2./mt/T1+Yt*A0*(A0-4*T1)/2./mt/T1/(T1-T2))                    &
       & + A0*(2*mt+s2t*Yt)**2/2./T1/(A0-4*T1)                                      &
       & + A0/T1+A0*c2t**2*Yt**2/T1/(T1-T2))*cb**2*phi(A0,T1,T1)                    &
       & - (2*A0*BL/T1*(ct2*t+s2t*mt*Yt+st2*Yt**2)/d_A0T1BL                         &
       & + c2t**2*(A0+BL-T1)*Yt*mt/s2t/T1/(T1-T2) +s2t*((A0+BL-T1)*Yt/4._dp/mt/T1   &
       & + d_A0T1BL*Yt/2./mt/T1/(T1-T2))                                            &
       & + ct2*(A0+BL-T1)/2./T1+c2t*Yt**2*(A0+BL-T1)/2./T1/(T1-T2)                  &
       & + c2t*d_A0T1BL/2./T1/(T1-T2)                                               &
       & - c2t*t*(A0+BL-T1)/2./T1/(T1-T2))*cb**2*phi(A0,BL,T1)                      &
       & + (s2t*(BL-T1)*Xt/mt/(T1-T2)+s2t*Xt/2./mt+ct2                              &
       & - c2t*(t+T1-BL)/(T1-T2)+c2t*Xt*(2*c2t*mt+s2t*Xt)                           &
       &      /s2t/(T1-T2))*sb**2*Li2(1-BL/T1)                                      &
       & + (1-c2t-2*c2t*(mu2-T1)/(T1-T2))*Li2(1-mu2/T1)                             &
       & - 21*s2t*T1*At/2./(T1-T2)/mt+c2t*T1/2./(T1-T2)                             &
       & + 3*s2t*At/4._dp/mt-3*s2t*mt*At/T1+c2t*(2*BL+2*A0*cb**2-4*mu2-2*t+T1       &
       & + 2*(sb**2*Xt**2+cb**2*Yt**2))/4._dp/T1                                    &
       & + (-5+c2t**2)/4._dp/T1*(sb**2*Xt**2+cb**2*Yt**2)                           &
       & - (2*BL+6*A0*cb**2-12*mu2+2*t+(1+c2t**2-s2t**2)*T2)/4._dp/T1               &
       & + ((1+c2t**2-s2t**2)*T1+(1+c2t**2)*(sb**2*Xt**2+cb**2*Yt**2))/4._dp/T2     &
       & - t/T1*Log(t/q)+(2*mu2*(t-T1)*T1+mu2**2*(t+T1)-(t-T1)**3)                  &
       &    /T1/d_T1mu2t*Log(t*T1/q**2)-Log(mu2/q)*(2-c2t)*mu2/T1                   &
       & + mu2*((t-T1)**2-mu2**2)/T1/d_T1mu2t*Log(mu2*T1/q**2)                      &
       & + log_BLq*(st2*BL/T1+sb**2*BL/T1/(BL-T1)* (ct2*t+s2t*mt*Xt+st2*Xt**2))     &
       & - cb**2*BL*(A0-BL+T1)*(ct2*t+s2t*mt*Yt+st2*Yt**2)                          &
       &      /T1/d_A0T1BL*Log(BL*T1/q**2) +log_A0q*((3-c2t)*cb**2*A0/2./T1         &
       & + A0*cb**2*(2*mt+s2t*Yt)**2/2./(A0-4*T1)/T1)                               &
       & - cb**2*A0*(1+c2t**2)*(A0-T1-T2)*(T1-T2)*Yt**2                             &
       &       /4._dp/T1/T2/d_A0T1T2*Log(A0*T1/q**2)                                &
       & + cb**2*A0*(A0-BL-T1)*(ct2*t+s2t*mt*Yt+st2*Yt**2)                          &
       &    /T1/d_A0T1BL*Log(A0*T1/q**2) +log_t2q*(c2t**2*2._dp*(T1+T2)/(T1-T2)     &
       & + c2t**2*(sb**2*Xt**2+cb**2*Yt**2)/(T1-T2)                                 &
       & - (1+c2t**2)*sb**2*(T1-T2)*Xt**2/4._dp/T1/T2+(1+c2t**2-s2t**2)*T2/4._dp/T1 &
       & + (1+c2t**2)*(sb**2*Xt**2+cb**2*Yt**2)/4._dp/T2)                           &
       & - (1+c2t**2)*cb**2*Yt**2*(A0**2*T1+(T1-T2)**3-A0*(2*T1**2+3*T1*T2-T2**2))  &
       &     /4._dp/T1/T2/d_A0T1T2*Log(T2*T1/q**2) 
   tauf2c = tauf2c                                                                 &
       & +log_t1q*(4*mu2*(mu2+t-T1)/d_T1mu2t                                       &
       & +2*(1+c2t**2)*cb**2*Yt**2*A0*(A0-T1-3*T2)/4._dp/T2/d_A0T1T2               &
       & -2*cb**2*(A0+BL-T1)*(ct2*t+s2t*mt*Yt+st2*Yt**2)                           &
       &              /d_A0T1BL+cb**2*(2*mt+s2t*Yt)**2/2./T1                       &
       & -2*cb**2*(2*mt+s2t*Yt)**2/(A0-4*T1)                                       &
       & +sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2)/T1                                     &
       & -sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2)/(BL-T1)                                &
       & -st2*mu2/T1+1-c2t-6*c2t**2*mt*At/s2t/(T1-T2) +9*s2t*T1*At/mt/(T1-T2)      &
       & -c2t*(1+c2t)*(sb**2*Xt**2+cb**2*Yt**2)/(T1-T2)                            &
       & -(1+c2t**2)*sb**2*(T1-T2)*Xt**2/4._dp/T1/T2                               &
       & -c2t*(BL+A0*cb**2-2*mu2-t+(1+3*c2t*2._dp)*T1-c2t*2._dp*T2)/(T1-T2)        &
       & -3*s2t*At/2./mt+s2t*mt*(sb**2*Xt-3*cb**2*Yt)/T1                           &
       & -(3-2*c2t+c2t**2)/4._dp/T1*(sb**2*Xt**2+cb**2*Yt**2)                      &
       & +s2t**2/2./T1*(sb**2*Xt**2-cb**2*Yt**2)                                   &
       & -6+c2t+2._dp*s2t**2/2.+((3-c2t)*mu2-(c2t+8*cb**2-5)*t)/2./T1              &
       & -(2*c2t**2)*T1/4._dp/T2)                                                  &
       & +log_t2q**2*(3*c2t**2*mt*At/2./s2t/(T1-T2)                                &
       & +c2t*(1-2*c2t)*(sb**2*Xt**2+cb**2*Yt**2)/4._dp/(T1-T2)+3._dp/8._dp        &
       & +c2t*(2*BL+2*A0*cb**2-4*mu2-2*t+(1-2*c2t*2._dp)*T1                        &
       & +(1-6*c2t*2._dp)*T2)/8./(T1-T2)) +log_t1q**2*(3*s2t/2./mt*At              &
       & +s2t*cb**2*A0*Yt/(T1-T2)/mt +s2t*(BL-6*T1)*At/2./(T1-T2)/mt               &
       & +9*c2t**2*mt/2./s2t*At/(T1-T2)                                            &
       & +3*c2t*(1+2*c2t)*(sb**2*Xt**2+cb**2*Yt**2)/4._dp/(T1-T2)                  &
       & +c2t*(6*BL+6*A0*cb**2-12*mu2-6*t+(7+26*c2t*2._dp)*T1                      &
       & -(1+2*c2t*2._dp)*T2)/8./(T1-T2)+25/8.-c2t/2.+s2t**2*2._dp)                &
       & -(s2t*(2*A0+2*BL-T1-T2)*Yt/4._dp/mt/(T1-T2)                               &
       & +(1+c2t)/4._dp+c2t**2*mt*Yt/s2t/(T1-T2)                                   &
       & +c2t*(A0+BL-t-T1+Yt**2)/2./(T1-T2))*cb**2*Log(A0/T1)*Log(BL/T1)           &
       & -cb**2*s2t*2*A0*Yt/(T1-T2)/mt*log_A0q*log_t1q                             &
       & -s2t*BL*At/(T1-T2)/mt*log_BLq*log_t1q -(c2t**2*2._dp*(T1+T2)/(T1-T2)      &
       & +c2t**2*(sb**2*Xt**2+cb**2*Yt**2)/(T1-T2))*log_t1q*log_t2q

  End Function tauF2c
  
  
  Function tauF3ab(T1,T2,q)
  Implicit None
  Real(dp) :: T1,T2,q
  Real(dp) :: tauF3ab
   tauF3ab = 1.5_dp*(2.-Log(T1/q)-Log(T2/q)) *(2.-(T1+T2)/(T1-T2)*Log(T1/T2))

  End Function tauF3ab
  
  
  Function tauF3c(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu)
  Implicit None
  Real(dp) :: t,mu2,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu
  Real(dp) :: Nc=1._dp ! color factor !!!
  Real(dp) :: ct2,st2,Xt,Yt,At, mt
  Real(dp) :: tauF3c

  mu2 = mu**2
  If(mu2==0._dp) mu2 = Epsilon(1._dp)

  Xt = s2t*(T1-T2)/2._dp/Sqrt(t)
  Yt = Xt - mu/cb/sb
  At = sb**2*Xt+cb**2*Yt
  ct2 = (1._dp+c2t)/2._dp
  st2 = (1._dp-c2t)/2._dp
  mt = Sqrt(t)

  tauF3c = (2*mu2*t*(mu2+t-T1)/T1/delt(T1,mu2,t) &
       & - (4*mu2*t+2*delt(T1,mu2,t))/T1/(T1-T2) -(mu2+t-T1)/T1)*phi(mu2,t,T1) &
       & + (A0*(1+c2t**2)*(A0-2*(T1+T2))*Yt**2/2./T2/delt(A0,T1,T2) &
       & + 4*A0*c2t**2*(A0-2*(T1+T2))*Yt**2/T2/(T1-T2)**2&
       & -(1-3*c2t**2)*Yt**2/2./T2)*cb**2*phi(A0,T1,T2) &
       & + (-A0*(2*mt+s2t*Yt)**2/2./T1/(A0-4*T1) &
       & + A0*(2*mt+s2t*Yt)**2/2./T1/(T1-T2) &
       & - 2*A0*c2t**2*Yt**2*(2*A0-7*T1-T2)/T1/(T1-T2)**2&
       & +2*A0*(1-3*c2t**2)*mt*(A0-4*T1)*Yt/s2t/T1/(T1-T2)**2&
       & -4*A0*c2t**2*mt*Yt/s2t/T1/(T1-T2))*cb**2*phi(A0,T1,T1) &
       & + (-2*A0*BL*(ct2*t+s2t*mt*Yt+st2*Yt**2)/T1/delt(A0,T1,BL) &
       & + 2*(1-3*c2t**2)*mt*Yt*delt(A0,T1,BL)/s2t/T1/(T1-T2)**2&
       & -2*c2t**2*mt*Yt*(A0+BL-T1)/s2t/T1/(T1-T2) &
       & + 3*c2t*delt(A0,T1,BL)*(t-Yt**2)/T1/(T1-T2)**2&
       & +(A0+BL-T1)*(c2t*(t-Yt**2)+(ct2*t+s2t*mt*Yt+st2*Yt**2)) &
       &      /T1/(T1-T2))*cb**2*phi(A0,BL,T1) &
       & -(1-3*c2t**2)*sb**2*Xt**2/(T1-T2)*Li2(1-T2/T1) &
       & + (1-c2t+2*(1-3*c2t)*(mu2-T1)/(T1-T2) &
       &  -6*c2t*(mu2-T1)**2/(T1-T2)**2)*Li2(1-mu2/T1) &
       & + (-4*(1-3*c2t**2)*sb**2*mt*(BL-T1)*Xt/s2t/(T1-T2)**2&
       & +4*c2t**2*sb**2*mt*Xt/s2t/(T1-T2) &
       & - 2*sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2)/(T1-T2) &
       & - 2*sb**2*c2t*(3*BL-2*T1-T2)*(t-Xt**2)/(T1-T2)**2)*Li2(1-BL/T1) &
       & + 2*mt*At*(3*(7-18*c2t**2)*T1-9*c2t**2*T2)/s2t/(T1-T2)**2&
       & -3*s2t*mt*At*(4*T1-T2)/T1/(T1-T2)+2*c2t*At**2/(T1-T2) &
       & - 21*c2t*T1*(sb**2*Xt**2+cb**2*Yt**2)/(T1-T2)**2&
       & +5*c2t/2./(T1-T2)*(sb**2*Xt**2+cb**2*Yt**2) &
       & - (6-2*c2t)/4._dp/T1*(sb**2*Xt**2+cb**2*Yt**2) &
       & + 3*mu2/T1+c2t*mu2*(T1+T2)/T1/(T1-T2)+18*c2t*mu2*T1/(T1-T2)**2&
       & +3*cb**2*A0*c2t/(T1-T2)-cb**2*A0*(3-c2t)/2./T1&
       & -12*(cb**2*A0+BL)*T1*c2t/(T1-T2)**2+3*c2t*BL/(T1-T2)-(1-c2t)*BL/2./T1&
       & +15*c2t*T1*t/(T1-T2)**2-3*c2t*t/2./(T1-T2)-(1+c2t)*t/2./T1&
       & -s2t**2/2._dp*2._dp-c2t**2*2._dp*(T1-T2)**2/4._dp/T1/T2&
       & -9*2._dp*T1*c2t**2/(T1-T2)-3*T1*(2*T1+3*T2)/(T1-T2)**2*c2t&
       & -(28+6)*T1/2./(T1-T2) +Log(t/q)*(-t/T1) &
       & - Log(t*T1/q**2)*t*((t-T1)**2-mu2**2)/T1/delt(T1,mu2,t) &
       & + Log(mu2/q)*(-6*mu2*(3*mu2-T2)*c2t/(T1-T2)**2-(2-c2t)*mu2/T1) 
   tauf3c = tauf3c &
       & - Log(mu2*T1/q**2)*mu2*(T1**2+mu2**2-t**2-2*mu2*T1) &
       &  /T1/delt(T1,mu2,t)+Log(BL/q)*(12*BL*c2t*T1/(T1-T2)**2&
       & +sb**2*BL*(ct2*t+s2t*mt*Xt+st2*Xt**2)/T1/(BL-T1) &
       & + (1-c2t)*BL/2./T1-3*c2t*BL/(T1-T2)) &
       & - Log(BL*T1/q**2)*cb**2*BL*(A0-BL+T1)/T1/delt(A0,T1,BL) &
       & * (ct2*t+s2t*mt*Yt+st2*Yt**2) &
       & + Log(A0/q)*A0*cb**2*((2*mt+s2t*Yt)**2/2./(A0-4*T1)/T1&
       & +12*c2t*T1/(T1-T2)**2+(3-c2t)/2./T1-3*c2t/(T1-T2)) &
       & - Log(A0*T1/q**2)*A0*cb**2*(Yt**2*(1+c2t**2)/4._dp/T1/T2/delt(A0,T1,T2) &
       & * ((T1+T2)**2-A0*(T1+T2)+4*T1*T2)-(A0-BL-T1)/T1/delt(A0,T1,BL) &
       & * (ct2*t+s2t*mt*Yt+st2*Yt**2)) &
       & + Log(T2/q)*(12*c2t**2*T2*mt*At/s2t/(T1-T2)**2&
       & -6*s2t*mt*T2*At/(T1-T2)**2&
       & -3*(1-c2t)*cb**2*A0*T2/(T1-T2)**2-(1-3*c2t)*T2*BL/(T1-T2)**2&
       & +6*(1-c2t)*T2*mu2/(T1-T2)**2-(1+3*c2t)*T2*t/(T1-T2)**2&
       & +(sb**2*Xt**2+cb**2*Yt**2)*(-(2-3*c2t+23*c2t**2)*T2/(T1-T2)**2&
       & -(1+5*c2t**2)/2./(T1-T2)-(1+c2t**2)/4._dp/T2) &
       & + (1+c2t**2)*sb**2*Xt**2*(T1**2-4*T1*T2-T2**2)/4._dp/T1/T2/(T1-T2) &
       & - 2._dp*c2t**2/4._dp/(T1-T2)**2*(9*T1**2+32*T1*T2+19*T2**2) &
       & - 2._dp*(T1-T2)/4._dp/T1*c2t**2+T2*(2*T1+T2)/(T1-T2)**2*c2t&
       & -T2*((7+3)*T1)/2./(T1-T2)**2 -(-(3-Nc)*T2)/2./(T1-T2)) &
       & + Log(T2*T1/q**2)*(1+c2t**2)*cb**2*Yt**2/4._dp/T1/T2/delt(A0,T1,T2) &
       & * (A0**2*T1+(T1-T2)**3-2*T2*(T1**2-T2**2) -A0*(2*T1**2+T1*T2+T2**2)) 
   tauf3c = tauf3c &
       & + Log(T1/q)*(2*(mu2+t-T1)**2/delt(T1,mu2,t) &
       & - cb**2*(1+c2t**2)*Yt**2/2./T2/delt(A0,T1,T2) &
       &         *(A0**2-4*T2*(T1-T2)-A0*(T1+3*T2)) &
       & - 2*cb**2*(A0+BL-T1)*(ct2*t+s2t*mt*Yt+st2*Yt**2) /delt(A0,T1,BL) &
       & + cb**2*(2*mt+s2t*Yt)**2/2./T1 &
       &    -2*cb**2*(2*mt+s2t*Yt)**2/(A0-4*T1) &
       & + sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2)/T1&
       & -sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2)/(BL-T1) -(1-c2t)/2._dp*mu2/T1+1-c2t&
       & +12*mt*At*((-3+7*c2t**2)*T1+c2t**2*T2)/s2t/(T1-T2)**2&
       & +6*mt*(2*T1-T2)*s2t*At/(T1-T2)**2+sb**2*s2t**2*Xt**2/T1&
       & +s2t*mt/T1*(sb**2*Xt-3*cb**2*Yt) &
       & + (1+c2t**2)*sb**2*Xt**2*(T1**2+4*T1*T2-T2**2)/4._dp/T1/T2/(T1-T2) &
       & + (sb**2*Xt**2+cb**2*Yt**2)*((2+15*c2t+23*c2t**2)*T1/(T1-T2)**2&
       & +(5-6*c2t-5*c2t**2)/2./(T1-T2)-(5-2*c2t-c2t**2)/4._dp/T1) &
       & + 3*A0*cb**2*(2*(1+c2t)*T1-(1-c2t)*T2)/(T1-T2)**2&
       & +BL*(2*(1+3*c2t)*T1-(1-3*c2t)*T2)/(T1-T2)**2&
       & +t*(2*(1-6*c2t)*T1-(1+3*c2t)*T2)/(T1-T2)**2&
       & +(5-c2t-8*cb**2)*t/2./T1+(3-c2t)*mu2/2./T1 &
       & -2*(3+12*c2t)*mu2*T1/(T1-T2)**2-6*(1-c2t)*mu2/(T1-T2) &
       & - 9/2.+s2t**2/2._dp*2._dp+3*c2t/2.+c2t*T1*(4*T1+11*T2)/(T1-T2)**2&
       & +2._dp*(65*T1**2+4*T1*T2-9*T2**2)*c2t**2/4._dp/(T1-T2)**2&
       & +2._dp*(T1-T2)*c2t**2/4._dp/T2 &
       & +T1*((7+3)*T1)/2./(T1-T2)**2+(5*(5+Nc)*T1)/2./(T1-T2)) &
       & + (2*Log(mu2/q)**2-Log(mu2/T1)**2)*3*c2t*mu2**2/(T1-T2)**2&
       & +(2*Log(BL/q)**2-Log(BL/T1)**2)* &
       &      (2*BL*(1-3*c2t**2)*mt*At/s2t/(T1-T2)**2-BL/2./(T1-T2) &
       & - 3*BL*c2t*(T1+T2-2*t+2*sb**2*Xt**2+2*cb**2*Yt**2)/2./(T1-T2)**2) &
       & + (2*Log(A0/q)**2-Log(A0/T1)**2)*cb**2* &
       &   (4*A0*(1-3*c2t**2)*mt*Yt/s2t/(T1-T2)**2-3*A0/2./(T1-T2) &
       & - 3*A0*c2t*(T1+T2-2*t+2*Yt**2)/2./(T1-T2)**2) &
       & + Log(t/T1)*Log(mu2/T1)*(T1+T2-2*t-2*mu2)/(T1-T2) &
       & + Log(T2/T1)*Log(A0/T1)*Yt**2*cb**2* &
       &   (8*A0*c2t**2+(1-3*c2t**2)*(T1-T2))/2./(T1-T2)**2&
       & + Log(BL/T1)*Log(A0/T1)*cb**2*(2*mt*Yt/(T1-T2)**2/s2t&
       &      *((A0+BL)*(1-3*c2t**2)-(1-2*c2t**2)*T1+c2t**2*T2) &
       & + s2t*mt*Yt/(T1-T2)+(t+Yt**2)/2./(T1-T2) &
       & + 3*c2t*(2*A0+2*BL-T1-T2)*(t-Yt**2)/2./(T1-T2)**2) 
   tauf3c = tauf3c &
       & + Log(T1/q)*Log(T2/q)*(2*c2t**2*2._dp*(T1+T2)**2/(T1-T2)**2 &
       & + ((1+5*c2t**2)*T1&
       & - (1-11*c2t**2)*T2)/2./(T1-T2)**2*(sb**2*Xt**2+cb**2*Yt**2)) &
       & + Log(T1/q)**2*(9*c2t**2*mt*At/s2t/(T1-T2) &
       & + 6*mt*T1*(2-5*c2t**2)*At/s2t/(T1-T2)**2&
       & -3*mt*s2t*(2*T1-T2)*At/(T1-T2)**2&
       & -((5+5*c2t+13*c2t**2)*T1-(3-4*c2t-10*c2t**2)*T2) &
       &           /2./(T1-T2)**2*(sb**2*Xt**2+cb**2*Yt**2) &
       & + mu2*((6+5*c2t)*T1-(3-4*c2t)*T2)/(T1-T2)**2+9/4._dp-c2t &
       &    +5/4._dp*s2t**2*2._dp &
       & + c2t*(t-BL-A0*cb**2)*(5*T1+4*T2)/2./(T1-T2)**2&
       & -(t+BL+3*A0*cb**2)*(2*T1-T2)/2./(T1-T2)**2+c2t/4._dp &
       &          -9*T1*T2*c2t/2./(T1-T2)**2&
       & -c2t**2*2._dp*(8*T1**2+16*T1*T2-T2**2)/2./(T1-T2)**2&
       & -T1*((14+5)*T1-(10+4)*T2)/2./(T1-T2)**2) &
       & + Log(T2/q)**2*(-3*c2t**2*mt*(T1+T2)*At/s2t/(T1-T2)**2&
       & +3*s2t*mt*T2*At/(T1-T2)**2+(2*T2-c2t*(T1+2*T2)+c2t**2*(2*T1+5*T2)) &
       &        /2./(T1-T2)**2*(sb**2*Xt**2+cb**2*Yt**2) &
       & + T2*(3*cb**2*A0+BL-6*mu2+t)/2./(T1-T2)**2&
       & -c2t*(cb**2*A0+BL-mu2-t)*(T1+2*T2)/2./(T1-T2)**2&
       & +c2t*mu2*(T1+2*T2)/2./(T1-T2)**2-3/4._dp+s2t**2/4._dp*2._dp &
       & + c2t**2*((T1+T2)**2+3*T2**2)/2./(T1-T2)**2*2._dp &
       & - c2t*((T1+T2)**2+2*T1*T2)/4._dp/(T1-T2)**2&
       & +T2*(2*2._dp*T1+(2-Nc)*T2)/2./(T1-T2)**2)

  End Function tauF3c
  

  Subroutine tauresfuncs(t,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu,F2_s)
  Implicit None
  Real(dp) :: t,mu2,A0,BL,T1,T2,s2t,c2t,cb,sb,q,mu
  Real(dp) :: ct2,st2,Xt,Yt,At, mt
  Real(dp) :: F2_s
  mu2 = mu**2
  mt = Sqrt(t)
  Xt = s2t*(T1-T2)/2._dp/mt
  Yt = Xt - mu/cb/sb
  At = sb**2*Xt+cb**2*Yt
  ct2 = (1._dp+c2t)/2._dp
  st2 = (1._dp-c2t)/2._dp
  
  F2_s = 2*c2t**2*sb**2*mt*Xt/(T1-T2)*Li2(1-BL/T1) &
      & - 2*c2t**2*sb**2*mt*Xt/(T1-T2)*Li2(1-BL/T2) &
      & - c2t**2*cb**2*mt*Yt/(T1-T2)*Log(A0/T1)*Log(BL/T1) &
      & + c2t**2*cb**2*mt*Yt/(T1-T2)*Log(A0/T2)*Log(BL/T2) &
      & - 6*At*c2t**2*mt/(T1-T2)*Log(T1/T2) &
      & + 3*c2t**2*At*mt/(T1-T2)*Log(T1/q)**2&
      & -3*c2t**2*At*mt/(T1-T2)*Log(T2/q)**2-c2t**2*cb**2*Yt*mt* &
      & (A0+BL-T1)/T1/(T1-T2)*phi(A0,BL,T1) +c2t**2*cb**2*Yt*mt* &
      & (A0+BL-T2)/T2/(T1-T2)*phi(A0,BL,T2) -2*A0*c2t**2*cb**2*Yt*mt &
      & /T1/(T1-T2)*phi(A0,T1,T1) +2*A0*c2t**2*cb**2*Yt*mt &
      & /T2/(T1-T2)*phi(A0,T2,T2)

  End Subroutine tauresfuncs
  

  Subroutine tausfuncs(t,T1,T2,s2t,q,mu,At,ht,          &
                     & dmuF2,dmuF3,dAtF2,dAtF3,DM12,DM22)
  
  Implicit None
  Real(dp) :: t,T1,T2,s2t,q,mu,At,ht
  Real(dp) :: Nc=1._dp ! color factor !!!
  Real(dp) :: dmuF2,dmuF3,dAtF2,dAtF3,DM12,DM22, mt
  mt = sqrt(t)
  dmuF2 = -Nc/4._dp*(Log(T1/q)**2-Log(T2/q)**2)
  dmuF3 = -Nc/4._dp*(Log(T1/q)+Log(T2/q)-2.) *(2.-(T1+T2)/(T1-T2)*Log(T1/T2))
  dAtF2 = -(3.+Nc)/2._dp*(Log(T1/q)**2-Log(T2/q)**2)
  dAtF3 = -(3.+Nc)/2._dp*(Log(T1/q)+Log(T2/q)-2.) *(2.-(T1+T2)/(T1-T2)*Log(T1/T2))
  DM12 = ht**2*s2t*mu*mt/4._dp*(Log(T1/q)**2-Log(T2/q)**2) &
     & +ht**2*s2t**2*mu*At/8.*(Log(T1/q)+Log(T2/q)-2.) &
     &  *(2.-(T1+T2)/(T1-T2)*Log(T1/T2))
  
  DM22 = ht**2*t*(Log(T1/q)**2+Log(T2/q)**2-2._dp*Log(t/q)**2) &
     & +ht**2*s2t*At*mt*(Log(T1/q)**2-Log(T2/q)**2) &
     & +ht**2*s2t**2*At**2/4._dp*(Log(T1/q)+Log(T2/q)-2.) &
     &   *(2.-(T1+T2)/(T1-T2)*Log(T1/T2))
  
  End Subroutine tausfuncs
  

  Subroutine taudfuncs(t,mA2,BL,T1,T2,s2t,c2t,cb,sb,q,mu,A,v2, &
    DF1,DF2,DF3,DdmuF2,DdmuF3,DdAtF2,DdAtF3)  
  !     shift of the parameters from DRbar to On-Shell scheme
  Implicit None      
  Real(dp) :: t,mu2,mA2,BL,T1,T2,s2t,c2t,cb,sb,q,A,mu,Xt,Yt
  Real(dp) :: DF1,DF2,DF3,DdmuF2,DdmuF3,DdAtF2,DdAtF3
  Real(dp) :: mt,ct2,st2,v2,v22,Nc=1._dp ! color factor !!!
  Real(dp) :: F1o,F2o,F3o,dm1,dm2,dmt,dAt,dth,ds2t,dv2,dv22,dmu,dcotb
  Real(dp) :: pi12_1,pi12_2, A0_t, A0_T1, A0_T2, A0_mu2, A0_BL, A0_mA2
  
  mu2 = mu**2
  Xt = A + mu*cb/sb
  Yt = A - mu*sb/cb
  ct2 = (1._dp+c2t)/2._dp
  st2 = (1._dp-c2t)/2._dp
  v22 = v2*sb**2
  
  mt = Sqrt(t)
  A0_t = A0(t)  
  A0_T1 = A0(T1)
  A0_T2 = A0(T2)
  A0_BL = A0(BL)
  A0_mu2 = A0(mu2)
  A0_mA2 = A0(mA2)

!  B0_T1_T1 = B0(T1,T1,0._dp)
!  B0_T1_T2 = B0(T1,T2,0._dp)
!  B0_T2_T1 = B0(T2,T1,0._dp)
!  B0_T2_T2 = B0(T2,T2,0._dp)
!  B0_T1_T1_A = B0(T1,T1,mA2)
!  B0_T1_T2_A = B0(T1,T2,mA2)
!  B0_T2_T2_A = B0(T2,T2,mA2)

  F1o = Log(T1/q) + Log(T2/q) - 2._dp*Log(t/q)
  F2o = Log(T1/q) - Log(T2/q) 
  F3o = 2._dp - (T1+T2)/(T1-T2)*(Log(T1/q) - Log(T2/q))
  !     counterterms:
  dv2 = v22 /2._dp* (2._dp *Log(t/q) - 1._dp - BL/t + &
    &T1/t * ct2 * (2._dp* BL/(BL-T1) * Log(BL/T1) - 1._dp)+&
    &T2/t * st2 * (2._dp* BL/(BL-T2) * Log(BL/T2) - 1._dp))
  dcotb = 0._dp               ! beta DRbar
  dv22 = v22/v2*dv2
  dmt = mt/2._dp*((1._dp-5d0/2._dp*sb**2)*Log(t/q) &
    +3d0*cb**2/2._dp*mA2/t*(1._dp-Log(mA2/q)) -3d0/2._dp*mu2/t*(1._dp-Log(mu2/q)) &
    +5d0*sb**2-1._dp+cb**2/2._dp*(1._dp-mA2/t)*B0(t,0._dp,mA2) &
    +cb**2*(2._dp-mA2/t)*B0(t,t,mA2) &
    +(T1/t*(1._dp-Log(T1/q))+(t-T1+mu2)/t*B0(t,mu2,T1) &
    +T2/t*(1._dp-Log(T2/q))+(t-T2+mu2)/t*B0(t,mu2,T2) &
    +BL/t*(1._dp-Log(BL/q))+(t-BL+mu2)/t*B0(t,mu2,BL))/2._dp)
  dmu = 0._dp                 ! mu DRbar
  
  dm1 = ((T1-t-mu2)*B0(T1,t,mu2) - A0_t &
    + st2*(T1-mu2)*B0(T1,0._dp,mu2) - (1._dp+st2)*A0_mu2 &
    + cb**2*(1._dp+st2)* A0_mA2 + st2* A0_BL + &
    (c2t**2-(Nc-1._dp)/2._dp*s2t**2)*A0_T2 &
    + (Nc+1._dp)/2._dp* s2t**2* A0_T1 + 1._dp/2._dp*   &
    (sb**2* (2._dp *mt+ s2t* Xt)**2* B0(T1,T1,0._dp) +&
    &cb**2*(2._dp* mt+ s2t* Yt)**2* B0(T1,T1,mA2) + &
    &sb**2*(1._dp+c2t**2)*Xt**2*B0(T1,T2,0._dp) + &
    &cb**2*(1._dp+c2t**2)*Yt**2*B0(T1,T2,mA2)) +&
    &sb**2*(ct2*t+s2t*mt*Xt+st2*Xt**2)*B0(T1,BL,0._dp) +&
    &cb**2*(ct2*t+s2t*mt*Yt+st2*Yt**2)*B0(T1,BL,mA2))
  
  dm2 = ((T2-t-mu2)*B0(T2,t,mu2) - A0_t &
    + ct2*(T2-mu2)*B0(T2,0._dp,mu2) - (1._dp+ct2)*A0_mu2 &
    + cb**2* (1._dp+ct2)*A0_mA2 + ct2* A0_BL + &
    (c2t**2 - (Nc-1._dp)/2._dp* s2t**2)*A0_T1 &
    +(Nc+1._dp)/2._dp* s2t**2* A0_T2 + 1._dp/2._dp*  &
    (sb**2* (2._dp* mt- s2t* Xt)**2* B0(T2,T2,0._dp) +&
    &cb**2*(2._dp*mt- s2t*Yt)**2*B0(T2,T2,mA2) + &
    &sb**2*(1._dp+c2t**2)* Xt**2* B0(T2,T1,0._dp) + &
    &cb**2*(1._dp+c2t**2)* Yt**2* B0(T2,T1,mA2)) +&
    &sb**2*(st2*t-s2t*mt*Xt+ct2*Xt**2)*B0(T2,BL,0._dp) +&
    &cb**2*(st2*t-s2t*mt*Yt+ct2*Yt**2)*B0(T2,BL,mA2))
  pi12_1 =1._dp/2._dp*(s2t*((T1-mu2)*B0(T1,0._dp,mu2)-A0_mu2) &
    + s2t* cb**2* A0_mA2 + s2t* A0_BL + &
    (Nc+1._dp)* c2t* s2t* (A0_T1 - A0_T2) +&
    &sb**2*c2t*Xt*(2._dp* mt + s2t* Xt)* B0(T1,T1,0._dp) +&
    &cb**2*c2t*Yt*(2._dp* mt + s2t* Yt)* B0(T1,T1,mA2) +&
    &sb**2*c2t*Xt*(2._dp* mt - s2t* Xt)* B0(T1,T2,0._dp) +&
    &cb**2*c2t*Yt*(2._dp* mt - s2t* Yt)* B0(T1,T2,mA2) -&
    &sb**2*(s2t*t-2._dp*c2t*mt*Xt-s2t*Xt**2) *B0(T1,BL,0._dp) -&
    &cb**2*(s2t*t-2._dp*c2t*mt*Yt-s2t*Yt**2) *B0(T1,BL,mA2))
  pi12_2 =1._dp/2._dp*(s2t*((T2-mu2)*B0(T2,0._dp,mu2)-A0_mu2) &
    + s2t* cb**2* A0_mA2 + s2t* A0_BL + &
    (Nc+1._dp)* c2t* s2t* (A0_T1 - A0_T2) +&
    &sb**2*c2t*Xt*(2._dp* mt + s2t* Xt)* B0(T2,T1,0._dp) +&
    &cb**2*c2t*Yt*(2._dp* mt + s2t* Yt)* B0(T2,T1,mA2) +&
    &sb**2*c2t*Xt*(2._dp* mt - s2t* Xt)* B0(T2,T2,0._dp) +&
    &cb**2*c2t*Yt*(2._dp* mt - s2t* Yt)* B0(T2,T2,mA2) -&
    &sb**2*(s2t*t-2._dp*c2t*mt*Xt-s2t*Xt**2) *B0(T2,BL,0._dp) -&
    &cb**2*(s2t*t-2._dp*c2t*mt*Yt-s2t*Yt**2) *B0(T2,BL,mA2))
  dth = (pi12_1 + pi12_2)/2._dp/(T1-T2)
  ds2t = 2._dp*c2t*dth
  dAt = ((dm1-dm2)/(T1-T2) + ds2t/s2t - dmt/mt)*Xt- mu * dcotb - dmu * cb/sb
  DF1 = dm1/T1 + dm2/T2 - 4d0*dmt/mt + (4d0*dmt/mt - dv22/v22)*F1o
  DF2 = dm1/T1 - dm2/T2 + (3d0*dmt/mt - dv22/v22 + ds2t/s2t)*F2o
  DF3 = (2._dp*T1*T2/(T1-T2)**2*Log(T1/T2) - (T1+T2)/(T1-T2)) &
    &*(dm1/T1-dm2/T2) + (2._dp*dmt/mt-dv22/v22+2._dp*ds2t/s2t)*F3o
  DdmuF2 = dmu/mu * F2o       
  DdmuF3 = dmu/mu * F3o       
  DdAtF2 = dAt/A * F2o       
  DdAtF3 = dAt/A * F3o       
  !     residues of some singular functions for s2t=0 and for A=0
  If(s2t==0._dp) Then         
    DF2 = ds2t*F2o
    DdAtF2 = ds2t*Xt/A
  Endif
  If(mu==0._dp) Then
    DdmuF2 = dmu * F2o       
    DdmuF3 = dmu * F3o       
  Endif
  If(A==0._dp) Then
    DdAtF2 = dAt * F2o       
    DdAtF3 = dAt * F3o       
  Endif
  
  End Subroutine taudfuncs

 End Subroutine Yukawa2L_Scalar

 Subroutine Yukawa2L_Tadpoles_MSSM(mA2, vevs, mD2, mU2, mQ2, ME2, ML2, A_b &
             & , A_t, A_tau, Y_b, Y_t, Y_tau, mu, tadpole, kont)
 !---------------------------------------------------------------------------
 ! Two-loop O(a_t a_s, a_b a_s, a_t^2) corrections to the Higgs tadpoles.
 ! Based on A. Dedes and P. Slavich, hep-ph/0212132, orignal routines
 ! provided by P. Slavich
 ! input:
 !   gs .................. g_strong
 !   mg .................. m_gluino
 !   mA2 ................. m_A0 squared
 !   vevs(i) ............. vacuum expactation values
 !   mD2 ................. M^2_(\tilde D)
 !   mU2 ................. M^2_(\tilde U)
 !   mQ2 ................. M^2_(\tilde Q)
 !   mE2 ................. M^2_(\tilde E)
 !   mL2 ................. M^2_(\tilde L)
 !   A_t ................. trilinear coupling A_top
 !   A_b ................. trilinear coupling A_bottom
 !   A_tau ............... trilinear coupling A_tau
 !   Y_t ................. top Yukawwa coupling
 !   Y_b ................. bottom Yukawwa coupling
 !   Y_tau ............... tau Yukawwa coupling
 !   mu .................. mu-parameter
 ! output:
 !  tadpole ..... 2-loop tadpole contributions
 !  kont ........ is 0 if everything is o.k., otherwise it gets a negative 
 !                value
 ! written by Werner Porod, 13.12.02
 ! 11.06.03: implementing alpha_b alpha_t + alpha^2_b corrections
 !           based on A. Dedes, G. Degrassi and P. Slavich, hep-ph/0305127
 ! 04.03.04: - implementing alpha_b alpha_tau part
 !---------------------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont 
  Real(dp), Intent(in) :: mA2, vevs(2), mQ2, mU2, mD2, ML2, ME2
  Complex(dp), Intent(in) :: A_b, A_t, Y_t, Y_b, mu, A_tau, Y_tau
  Real(dp), Intent(out) :: tadpole(2)
  
  Real(dp) :: parts(2,5), s2t, c2t, s2b, c2b, F2l, G2l, Q, mt, tanb, mb          &
       & , sb, cb, ht2, mStop(2), mStop2(2), mt2, mb2, muR                       &
       & , mSbottom(2), mSbottom2(2), At, Ab, gs2, vv, Atau, mStau(2), mStau2(2) &
       & , s2tau, c2tau, mtau, mtau2, mSneu2
  Real(dp) :: F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp
  Complex(dp) :: Rstop(2,2), RSbottom(2,2), RStau(2,2)
  Real(dp), Parameter :: YL = 1._dp / 3._dp, YRu = -4._dp / 3._dp  &
         & , YRd = 2._dp / 3._dp

  Iname = Iname + 1
  NameOfUnit(Iname) = "Yukawa2L_Tadpoles_MSSM"

  tadpole = 0._dp
  parts = 0._dp
  kont = 0
  !------------------------------------------------------------------------
  ! first the (s)fermion, please note, that the papers by P.Slavich et al. 
  ! the ordering of the sfermions is reversed to compared to my odering
  !------------------------------------------------------------------------
  Call SfermionMass(MQ2, MU2, A_t, mu, vevs, Y_t, 0.5_dp, YL, YRu,   &
               &  0._dp, 0._dp, kont, mStop, mStop2, Rstop)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
     & "Stop masses squared for 2-loop calculation of Tadpoles are negativ."
   kont = -607
   Call AddError(607)
   Iname = Iname - 1
   Return
  End If 
  mt2 = 0.5_dp * Abs(Y_t*vevs(2))**2
  mt = Sqrt(mt2)
  s2t = - 2._dp * Real( Rstop(1,1) * Rstop(1,2), dp)
  c2t = Abs(Rstop(1,2))**2 -  Abs(Rstop(1,1))**2

  Call SfermionMass(MQ2, MD2, A_b, mu, vevs, Y_b, -0.5_dp, YL, YRd,   &
               &  0._dp, 0._dp, kont, mSbottom, mSbottom2, Rsbottom)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
       & "Sbottommasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -608
   Call AddError(608)
   Iname = Iname - 1
   Return
  End If 

  mb2 = 0.5_dp * Abs(Y_b*vevs(1))**2
  mb = Sqrt(mb2)
  s2b = - 2._dp * Real( Rsbottom(1,1) * Rsbottom(1,2), dp)
  c2b = Abs(Rsbottom(1,2))**2 -  Abs(Rsbottom(1,1))**2

  Call SfermionMass(ML2, ME2, A_tau, mu, vevs, Y_tau, -0.5_dp, 1._dp, 2._dp,   &
                  & 0._dp, 0._dp, kont, mStau, mStau2, RStau)
  If (kont.Ne.0) Then
   Write(ErrCan,*) "Problem in "//NameOfUnit(Iname)
   Write(ErrCan,*) &
     "Staumasses for 2-loop calculation of  Tadpoles are negativ."
   kont = -609
   Call AddError(609)
   Iname = Iname - 1
   Return
  End If 

  mtau2 = 0.5_dp * Abs(Y_tau*vevs(1))**2
  mtau = Sqrt(mtau2)
  s2tau = - 2._dp * Real( Rstau(1,1) * Rstau(1,2), dp)
  c2tau = Abs(Rstau(1,2))**2 -  Abs(Rstau(1,1))**2

  mSneu2 = ML2
  !------------------------------------------------------------
  ! different mass ordering leads to the following formulas
  !------------------------------------------------------------

  Q = GetRenormalizationScale() ! from LoopFunctions

  ht2 = Abs(Y_t)**2

  tanb = vevs(2) / vevs(1)
  cb = 1._dp / Sqrt(1._dp + tanb**2)
  sb = tanb * cb
 
  At = Real(A_t/Y_t, dp)
  Ab = Real(A_b/Y_b, dp)
  Atau = Real(A_tau/Y_tau, dp)
  muR = - Real(mu, dp) ! different sign convention

  ! gs2 = gs**2
  ! !---------------------------------
  ! ! alpha_s alpha_t + alpha_t^2
  ! !---------------------------------
  ! Call strfuncs1(mt2, mg, mStop2(2), mStop2(1), s2t, c2t, Q, F2l, G2l)
  ! parts(1,1) = mt * muR/tanB * s2t * F2l / vevs(1)**2
  ! parts(2,1) = (mt * At * s2t * F2l + 2._dp * mt2 * G2l ) / vevs(2)**2
  ! parts(:,1) = parts(:,1) * 4._dp * gs2  ! gs^2 CF Nc

  ! !---------------------------------
  ! ! alpha_s alpha_b
  ! !---------------------------------
  ! Call strfuncs1(mb2,mg, mSbottom2(2),mSbottom2(1), s2b, c2b, Q, F2l, G2l)
  ! parts(1,2) = (mb * Ab * s2b * F2l + 2._dp * mb2 * G2l ) / vevs(1)**2
  ! parts(2,2) = mb * muR * tanB * s2b * F2l / vevs(2)**2
  ! parts(:,2) = parts(:,2) * 4._dp * gs2  ! gs^2 CF Nc

  !-----------------------------------------
  ! (alpha_t + alpha_b)^2
  !-----------------------------------------
  vv = vevs(1)**2 + vevs(2)**2
  call makefuncs(mt2, mb2, mA2, mStop2(2), mStop2(1), mSbottom2(2)    &
        & , mSbottom2(1), s2t, c2t, s2b, c2b, Q, muR, vv, tanb        &
        & , F1t,F2t,F3t,F4t,F1b,F2b,F3b,F4b,F5,F6,Ft,Fb,Gt,Gb,FAp     )

  parts(1,3) = mt*muR/tanb*s2t*Ft + mb*Ab*s2b*Fb + 2._dp * mb2 * Gb
  parts(2,3) = mb*muR*tanb*s2b*Fb + mt*At*s2t*Ft + 2._dp*mt2*Gt
  parts(:,3) = 3._dp * parts(:,3) / vevs**2

 !-----------------------------------------
 ! alpha_tau * alpha_b
 !-----------------------------------------
  Call makefuncstau(mtau2,mb2,mStau2(2), mStau2(1), mSbottom2(2)    &
        & , mSbottom2(1), s2tau, c2tau, s2b, c2b, Q ,muR, vv, tanb  &
        & , F1t, F2t, F3t, F4t, F1b, F2b, F3b, F4b, F5, F6, Ft, Fb, Gt, Gb, FAp)
  parts(1,4) = mtau*Atau*s2tau*Ft + mb*Ab*s2b*Fb + 2._dp*mtau2*Gt + 2._dp*mb2*Gb
  parts(2,4) = mtau*muR*tanb*s2tau*Ft + mb*muR*tanb*s2b*Fb
  parts(:,4) = 3._dp * parts(:,4) / vevs**2

 !--------------
 ! alpha_tau^2
 !--------------
  Call tautadfuncs(mtau2,mA2,mSneu2, mStau2(2), mStau2(1), s2tau, c2tau, Q, muR &
                 &, cb, sb, F2l, G2l)
  parts(1,5) = mtau * Atau * s2tau * F2l + 2._dp * mtau2 * G2l
  parts(2,5) = mtau * muR * tanb * s2tau * F2l 
  parts(:,5) = Abs(Y_tau)**2 * parts(:,5) / vevs**2

  tadpole(1) = oo16pi2**2 * Sum( parts(1,:) )
  tadpole(2) = oo16pi2**2 * Sum( parts(2,:) )

  Iname = Iname - 1

 Contains
  
  Subroutine tautadfuncs(t,A0,BL,T1,T2,s2t,c2t,q,mu,sb,cb,F2l,G2l)
  Implicit None
  real(dp) :: t,A0,BL,T1,T2,s2t,c2t,q,mu,mu2,sb,cb,sb2,cb2
  real(dp) :: F2l,G2l,Xt,Yt,At, mt
  real(dp) :: Nc=1._dp !color factor !!!

  mt = Sqrt(t)
  sb2 = sb**2
  cb2 = cb**2
  mu2 = mu**2
  If(mu2==0._dp) mu2 = Epsilon(1._dp)
  Xt = s2t*(T1-T2)/2._dp/mt
  Yt = Xt - mu/cb/sb
  At = sb2*Xt+cb2*Yt
  
  F2l = (delt(mu2,t,T1)+2*mu2*t)/T1*phi(mu2,t,T1) &
    & - (delt(mu2,t,T2)+2*mu2*t)/T2*phi(mu2,t,T2) &
    & + A0*cb2*(2*mt+s2t*Yt)/4/s2t/T1/(T1-T2)* &
    & ( -2*s2t*mt*(T1-T2)+2*(A0-4*T1)*Yt&
    &+s2t**2*(7*T1+T2-2*A0)*Yt)*phi(A0,T1,T1) &
    & - A0*cb2*(2*mt-s2t*Yt)/4/s2t/T2/(T1-T2)* &
    & ( -2*s2t*mt*(T1-T2)+2*(A0-4*T2)*Yt&
    &+s2t**2*(7*T2+T1-2*A0)*Yt)*phi(A0,T2,T2) &
    & + cb2*Yt**2/2/(T1-T2)/T2*(s2t**2*(T1-T2)**2-2*A0**2*c2t**2&
    &+A0*4*c2t**2*(T1+T2))*phi(A0,T1,T2) +(-cb2*delt(A0,BL,T1)/2/s2t/T1/(T1-T2) &
    & * (c2t*s2t*(t-Yt**2)-2*c2t**2*mt*Yt) &
    & - cb2/4/T1*(A0+BL-T1)*((1+c2t)*t+2*s2t*mt*Yt&
    &+Yt**2*(1-c2t)))*phi(A0,BL,T1) -(-cb2*delt(A0,BL,T2)/2/s2t/T2/(T1-T2) &
    & * (c2t*s2t*(t-Yt**2)-2*c2t**2*mt*Yt) &
    & - cb2/4/T2*(A0+BL-T2)*((1-c2t)*t-2*s2t*mt*Yt&
    &+Yt**2*(1+c2t)))*phi(A0,BL,T2) &
    & + (mu2-T1)*(T2-T1+c2t*(mu2-T2))/(T1-T2)*Li2(1-mu2/T1) &
    & + (mu2-T2)*(T1-T2-c2t*(mu2-T1))/(T1-T2)*Li2(1-mu2/T2) &
    & + (-sb2*(BL-T1)*(c2t*s2t*(t-Xt**2)-2*c2t**2*mt*Xt) /s2t/(T1-T2) &
    & - sb2/2*((1+c2t)*t+2*s2t*mt*Xt+(1-c2t)*Xt**2)) *Li2(1-T1/BL) &
    & - (-sb2*(BL-T2)*(c2t*s2t*(t-Xt**2)-2*c2t**2*mt*Xt) /s2t/(T1-T2) &
    & - sb2/2*((1-c2t)*t-2*s2t*mt*Xt+(1+c2t)*Xt**2)) *Li2(1-T2/BL) &
    & + s2t**2*sb2*Xt**2/2*(Li2(1-T2/T1)-Li2(1-T1/T2))	       &
    &+(-((-2+s2t**2)*T1+s2t**2*T2)/2/(T1-T2) &
    & * (sb2*Xt**2+cb2*Yt**2+2*mt*At/s2t) &
    & - (2*A0*c2t**2+(T1-T2)*s2t**2)/4/(T1-T2)*cb2*Yt**2&
    &-A0*cb2*c2t**2*mt*Yt/s2t/(T1-T2) &
    & - (Nc+1)*T1*((-3+s2t**2)*T1+(1+s2t**2)*T2)/2/(T1-T2)-Nc/2*T1&
    &+c2t*(mu2-T1)*(mu2-T2)/2/(T1-T2)-mu2/2+t)*Log(T1/q)**2&
    &-(((-2+s2t**2)*T2+s2t**2*T1)/2/(T1-T2) &
    & * (sb2*Xt**2+cb2*Yt**2-2*mt*At/s2t) &
    & + (2*A0*c2t**2-(T1-T2)*s2t**2)/4/(T1-T2)*cb2*Yt**2&
    &-A0*cb2*c2t**2*mt*Yt/s2t/(T1-T2) &
    & + (Nc+1)*T2*((-3+s2t**2)*T2+(1+s2t**2)*T1)/2/(T1-T2)-Nc/2*T2&
    &+c2t*(mu2-T1)*(mu2-T2)/2/(T1-T2)-mu2/2+t)*Log(T2/q)**2&
    &+(-c2t**2*(T1+T2)/(T1-T2)*(sb2*Xt**2+cb2*Yt**2) &
    & + c2t**2*cb2*A0*Yt**2/(T1-T2)-2*(1+Nc)*c2t**2*T1*T2/(T1-T2) &
    & + ((1+Nc)*s2t**2-2)/2*(T1-T2))*Log(T1/q)*Log(T2/q) &
    & + (T1-mu2-t)*Log(t/q)*Log(T1/q)-(T2-mu2-t)*Log(t/q)*Log(T2/q) 
  F2l = F2l &
    & + ((T1-mu2-t)-c2t*mu2**2/(T1-T2))*Log(mu2/q)*Log(T1/q) &
    & - ((T2-mu2-t)-c2t*mu2**2/(T1-T2))*Log(mu2/q)*Log(T2/q) &
    & - cb2*mt*Yt/s2t*Log(A0/q)*Log(BL/q) &
    & - (T1-T2)*Log(mu2/q)*Log(t/q)-sb2*mt*Xt/s2t*Log(BL/q)**2&
    &+(-cb2*mt*Yt/2/s2t/(T1-T2)* &
    & ( 2*BL*c2t**2-6*A0*c2t**2+(-2+s2t**2)*T1+s2t**2*T2) &
    & + c2t*cb2/4/(T1-T2)*((2*BL-T1-T2)*(t-Yt**2) +2*A0*(T1+T2+Yt**2-t)) &
    & + cb2/4*(6*A0+t+(1+2*s2t**2)*Yt**2))*Log(A0/q)*Log(T1/q) &
    & - (-cb2*mt*Yt/2/s2t/(T1-T2)* &
    & ( 2*BL*c2t**2-6*A0*c2t**2+(-2+s2t**2)*T2+s2t**2*T1) &
    & + c2t*cb2/4/(T1-T2)*((2*BL-T1-T2)*(t-Yt**2) +2*A0*(T1+T2+Yt**2-t)) &
    & + cb2/4*(6*A0+t+(1+2*s2t**2)*Yt**2))*Log(A0/q)*Log(T2/q) &
    & + (cb2*mt*Yt/2/s2t/(T1-T2)* &
    & ( 2*BL*c2t**2-2*A0*c2t**2+(-2+s2t**2)*T1+s2t**2*T2) &
    & - mt*At/s2t/(T1-T2)*((-2+s2t**2)*T1+s2t**2*T2) &
    & + c2t/4/(T1-T2)*(2*A0*cb2*(t-Yt**2)+(T1+T2)* &
    & ( t*(-2+cb2)+2*sb2*Xt**2+cb2*Yt**2) +2*BL*(T1+T2-cb2*(t-Yt**2))) &
    & + (2*BL-(-2+cb2)*t+2*sb2*Xt**2+cb2*Yt**2)/4) *Log(BL/q)*Log(T1/q) &
    & - (cb2*mt*Yt/2/s2t/(T1-T2)* &
    & ( 2*BL*c2t**2-2*A0*c2t**2+(-2+s2t**2)*T2+s2t**2*T1) &
    & - mt*At/s2t/(T1-T2)*((-2+s2t**2)*T2+s2t**2*T1) &
    & + c2t/4/(T1-T2)*(2*A0*cb2*(t-Yt**2)+(T1+T2)* &
    & ( t*(-2+cb2)+2*sb2*Xt**2+cb2*Yt**2) +2*BL*(T1+T2-cb2*(t-Yt**2))) &
    & + (2*BL-(-2+cb2)*t+2*sb2*Xt**2+cb2*Yt**2)/4) *Log(BL/q)*Log(T2/q) &
    & + (3*mt*At/s2t/(T1-T2)*((-4+3*s2t**2)*T1+s2t**2*T2) &
    & - (3*(1+c2t)*T1+(-3+c2t)*T2)/2/(T1-T2)*(sb2*Xt**2+cb2*Yt**2) &
    & - c2t/2/(T1-T2)*((T1+T2)*(BL+A0*cb2) -T1*(4*mu2+3*t-T1)-T2*(2*mu2+t-3*T1)) &
    & - BL/2-3./2.*A0*cb2+3*mu2-t/2+Nc/2*((-4+3*s2t**2)*T1+s2t**2*T2) &
    & + ((-13+3*s2t**2)*T1+(-2+s2t**2)*T2)/2)*Log(T1/q) &
    & - (3*mt*At/s2t/(T1-T2)*((-4+3*s2t**2)*T2+s2t**2*T1) &
    & + (3*(1-c2t)*T2+(-3-c2t)*T1)/2/(T1-T2)*(sb2*Xt**2+cb2*Yt**2) &
    & - c2t/2/(T1-T2)*((T1+T2)*(BL+A0*cb2) -T2*(4*mu2+3*t-T2)-T1*(2*mu2+t-3*T2)) &
    & - BL/2-3./2.*A0*cb2+3*mu2-t/2+Nc/2*((-4+3*s2t**2)*T2+s2t**2*T1) &
    & + ((-13+3*s2t**2)*T2+(-2+s2t**2)*T1)/2)*Log(T2/q) &
    & + c2t*(mu2*Log(mu2/q)-BL*Log(BL/q)-A0*cb2*Log(A0/q)) &
    & + 3*At*mt/s2t*(5-4*s2t**2) &
    & + 2*c2t*(sb2*Xt**2+cb2*Yt**2)+c2t*(BL+A0*cb2-3*mu2-2*t+T1+T2) &
    & - (2*Nc*(-1+s2t**2)-11+2*s2t**2)/2*(T1-T2)

  G2l = -2*A0*cb2*(A0-3*t)/t*phi(A0,t,t) &
    & + (2*BL+mu2-BL**2/t+BL*mu2/t-t)*phi(BL,mu2,t) &
    & +mu2/T1*(mu2+t-T1)*phi(mu2,t,T1) &
    & + mu2/T2*(mu2+t-T2)*phi(mu2,t,T2) &
    & + A0*cb2*(2*mt+s2t*Yt)*(A0-2*t-4*T1-s2t*mt*Yt) &
    & / 4/mt/T1*phi(A0,T1,T1) &
    & + A0*cb2*(2*mt-s2t*Yt)*(A0-2*t-4*T2+s2t*mt*Yt) &
    & / 4/mt/T2*phi(A0,T2,T2) +A0*cb2*(-2+s2t**2)*Yt**2/2/T2*phi(A0,T1,T2) &
    & + ((s2t*Yt/mt+1+c2t)*delt(A0,BL,T1) &
    & - (2*s2t*mt*Yt+(1-c2t)*Yt**2+(1+c2t)*t) &
    & * (A0+BL-T1))*cb2/4/T1*phi(A0,BL,T1) +((-s2t*Yt/mt+1-c2t)*delt(A0,BL,T2) &
    & - (-2*s2t*mt*Yt+(1+c2t)*Yt**2+(1-c2t)*t) &
    & * (A0+BL-T2))*cb2/4/T2*phi(A0,BL,T2) +2*cb2*(t-A0)*Li2(1-t/A0) &
    & + (-1+c2t)*(mu2-T1)*Li2(1-mu2/T1) +(-1-c2t)*(mu2-T2)*Li2(1-mu2/T2) &
    & + (-sb2*s2t*(2*t+T1-BL)*Xt/2/mt-sb2/2*(1-c2t)*Xt**2&
    &+sb2/2*(1+c2t)*(BL-t-T1))*Li2(1-T1/BL) &
    & + (sb2*s2t*(2*t+T2-BL)*Xt/2/mt-sb2/2*(1+c2t)*Xt**2&
    &+sb2/2*(1-c2t)*(BL-t-T2))*Li2(1-T2/BL) &
    & - sb2*(s2t**2-2)*Xt**2/2*(Li2(1-T1/T2)+Li2(1-T2/T1)) &
    & + cb2*(t-A0)*Log(A0/q)**2-2*cb2*(t+2*A0)*Log(A0/q)*Log(t/q) &
    & + (cb2*(t+2*A0)-3*t)*Log(t/q)**2-(BL-t)*Log(BL/q)*Log(mu2/q) &
    & + (BL+2*mu2-t)*Log(mu2/q)*Log(t/q)-(BL+t)*Log(BL/q)*Log(t/q) &
    & + (-sb2*s2t*(T1-T2)*Xt/4/mt-sb2/2*Xt**2&
    &+sb2/4*(2*BL-2*t-(1+c2t)*T1-(1-c2t)*T2))*Log(BL/q)**2&
    &+(-cb2*s2t*(T1-T2)*Yt/4/mt-cb2/2*(Yt**2-A0) &
    & + cb2/4*(2*BL-2*t-(1+c2t)*T1-(1-c2t)*T2))*Log(A0/q)*Log(BL/q) &
    & + (s2t*(2*t+T1)/2/mt*At-cb2*s2t*A0*Yt/4/mt &
    & + sb2/2*Xt**2+cb2*s2t**2/4*Yt**2-A0*cb2/2-mu2/2*(1-c2t) &
    & + t+(3-c2t+(1+Nc)*s2t**2)/2*T1)*Log(T1/q)**2&
    &+(-s2t*(2*t+T2)/2/mt*At+cb2*s2t*A0*Yt/4/mt &
    & + sb2/2*Xt**2+cb2*s2t**2/4*Yt**2-A0*cb2/2-mu2/2*(1+c2t) &
    & + t+(3+c2t+(1+Nc)*s2t**2)/2*T2)*Log(T2/q)**2&
    &+(cb2*(2-s2t**2)*Yt**2/2+(2-(1+Nc)*s2t**2)/2*(T1+T2)) *Log(T1/q)*Log(T2/q) &
    & - (mu2+2*t)*Log(t/q)*Log(T1/q)-mu2*Log(mu2/q)*Log(T1/q) &
    & - (mu2+2*t)*Log(t/q)*Log(T2/q)-mu2*Log(mu2/q)*Log(T2/q) &
    & + (cb2*s2t*(3*A0-BL+2*t+T1)*Yt/4/mt+cb2/4*(1-c2t)*Yt**2&
    &-cb2/4*((1+c2t)*(BL-t-T1)-(11-c2t)*A0))*Log(A0/q)*Log(T1/q) &
    & + (-cb2*s2t*(3*A0-BL+2*t+T2)*Yt/4/mt+cb2/4*(1+c2t)*Yt**2&
    &-cb2/4*((1-c2t)*(BL-t-T2)-(11+c2t)*A0))*Log(A0/q)*Log(T2/q) 
  G2l = G2l &
    & + (cb2*s2t*Yt/4/mt*(BL-A0+2*t+T1) &
    & + sb2*s2t*Xt/2/mt*(2*t+T1)+sb2/2*(1-c2t)*Xt**2&
    &+cb2/4*(1-c2t)*Yt**2-cb2/4*A0*(1+c2t) +BL/4*(2*(1-c2t)+cb2*(1+c2t)) &
    & - (1+c2t)*(-2+cb2)/4*(t+T1))*Log(BL/q)*Log(T1/q) &
    & + (-cb2*s2t*Yt/4/mt*(BL-A0+2*t+T2) &
    & - sb2*s2t*Xt/2/mt*(2*t+T2)+sb2/2*(1+c2t)*Xt**2&
    &+cb2/4*(1+c2t)*Yt**2-cb2/4*A0*(1-c2t) +BL/4*(2*(1+c2t)+cb2*(1-c2t)) &
    & - (1-c2t)*(-2+cb2)/4*(t+T2))*Log(BL/q)*Log(T2/q) +(-3*s2t*(t+T1)/mt*At&
    &-(3-c2t)/2*(sb2*Xt**2+cb2*Yt**2)-(1-c2t)/2*BL&
    &-(3-c2t)/2*cb2*A0+(3-c2t)*mu2-(1+c2t)/2*t+(c2t-15-(1+Nc)*s2t**2)/2*T1&
    &+(-2+(1+Nc)*s2t**2)/2*T2)*Log(T1/q) +(3*s2t*(t+T2)/mt*At&
    &-(3+c2t)/2*(sb2*Xt**2+cb2*Yt**2)-(1+c2t)/2*BL&
    &-(3+c2t)/2*cb2*A0+(3+c2t)*mu2-(1-c2t)/2*t+(-c2t-15-(1+Nc)*s2t**2)/2*T2&
    &+(-2+(1+Nc)*s2t**2)/2*T1)*Log(T2/q) -Pi**2*sb2*t/3&
    &+15*s2t*(T1-T2)/4/mt*At+3./2.*(sb2*Xt**2+cb2*Yt**2) &
    & + 18*t*Log(t/q)+BL/2+3./2.*A0*cb2-3*mu2+35./4.*(T1+T2-2*t)-c2t/4*(T1-T2)

  End Subroutine tautadfuncs
  
  ! Subroutine strfuncs1(t,mg,T1,T2,s2t,c2t,q,F2l,G2l)
  ! Implicit None
  !  Real(dp), Intent(in) :: t, mg, T1, T2, s2t, c2t, q
  !  Real(dp) :: g, mt

  !  Real(dp), Intent(out) :: F2l,G2l

  !  g = mg**2
  !  mt = Sqrt(t)

  !  F2l = 4._dp * mg*mt * (1._dp + 4._dp * c2t**2) / s2t                       &
  !    & - (2._dp * (T1-T2) + 4._dp * mg*mt / s2t) * Log(g/q) * Log(t/q)        &
  !    & - 2._dp * (4._dp-s2t**2) * (T1-T2)                                     &
  !    & + (4._dp * T1*T2 -s2t**2 * (T1+T2)**2) / (T1-T2) *Log(T1/q) *Log(T2/q) &
  !    & + strF2lc(t,mg,T1,T2,s2t,c2t,q) - strF2lc(t,mg,T2,T1,-s2t,c2t,q)

  !  G2l = 5._dp*mg/mt*s2t*(T1-T2)-10._dp* (T1+T2-2*t) - 4._dp*g      &
  !    & + 12._dp * t * (Log(t/q)**2 - 2._dp*Log(t/q) )               &
  !    & + (4._dp*g - s2t*mg/mt * (T1-T2)) * Log(g/q) * Log(t/q)      &
  !    & + s2t**2 * (T1+T2) * Log(T1/q) * Log(T2/q)                   &
  !    & + strG2lc(t,mg,T1,T2,s2t,q) + strG2lc(t,mg,T2,T1,-s2t,q)
  
  ! End Subroutine strfuncs1

  Real(dp) Function strF2lc(t,mg,T1,T2,s2t,c2t,q)
  Implicit None
   Real(dp), Intent(in) :: t, mg, T1, T2, s2t, c2t, q
   Real(dp) :: del, g, mt

   g = mg**2
   mt = Sqrt(t)

   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
  
   strF2lc = (4._dp*(g+t+2*T1)-s2t**2*(3._dp*T1+T2)-4._dp*s2t*mg*mt    &
         & -16._dp*mg*mt*T1*c2t**2/s2t/(T1-T2))*Log(T1/q)              &
         & +T1/(T1-T2)*(s2t**2*(T1+T2)-2*(2*T1-T2))*Log(T1/q)**2       &
         & +2._dp*(T1-g-t+mg*mt*s2t                                    &
         & +2._dp*c2t**2*mg*mt*T1/s2t/(T1-T2))*Log(g*t/q**2)*Log(T1/q) &
         & +4._dp*mg*mt*c2t**2*(t-g)/s2t/(T1-T2)*Log(t/g)*Log(T1/q)    &
         & +((2._dp*del+4._dp*g*t)/T1-2._dp*mg*mt*s2t/T1*(g+t-T1)      &
         & +4._dp*c2t**2*mg*mt/T1/(T1-T2)/s2t*del)*phi(g,t,T1)

  End Function strF2lc

  Real(dp) Function strG2lc(t,mg,T1,T2,s2t,q)
  Implicit None
   Real(dp), Intent(in) :: t,mg,T1,T2,s2t,q
   Real(dp) :: del, g, mt

   g = mg**2
   mt = Sqrt(t)

   del = g**2 + t**2 + T1**2 - 2*(g*t + g*T1 + t*T1)
  
   strG2lc = (4._dp*(g+t+2._dp*T1)+s2t**2*(T1-T2)                       &
         &     -4._dp*mg/mt*s2t*(t+T1))*Log(T1/q)                       &
         &     +(mg/mt*s2t*(5*t-g+T1)-2._dp*(g+2*t))*Log(t/q)*Log(T1/q) &
         &     +(mg/mt*s2t*(g-t+T1)-2._dp*g)*Log(g/q)*Log(T1/q)         &
         &     -(2._dp+s2t**2)*T1*Log(T1/q)**2                          &
         &     +(2._dp*g/T1*(g+t-T1-2*mg*mt*s2t)                        &
         &     +mg/mt*s2t*del/T1)*phi(g,t,T1)

  End Function strG2lc

 End Subroutine Yukawa2L_Tadpoles_MSSM
  

End Module TwoLoopHiggsMass_SARAH
