Module Bremsstrahlung
Use Control
Use Mathematics, Only: Li2, CLi2
!Use LoopFunctions

! PhotonFFZ, PhotonFFW taken from CCNDecays by Stefan Liebler, March 2010
! GluonFFWZ adapted from these by Mark Goodsell, June 2016
! To add: SSS, SFF, SVV taken from sfold by ....

! FFS By Mark Goodsell, 2016 
! SVV By Mark Goodsell, 2016 (TO DO!)

Contains

! The following part is dedicaded to the real Bremsstrahlung
! integrals going from energy 0 to infinity not cut
! by an upper limit
! some basic functions:

 Real(dp) Function kasqrt(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0, m1, m2

  kasqrt = m0 * m0 * m0 * m0 + m1 * m1 * m1 * m1 + m2 * m2 * m2 * m2 &
    & - 2._dp * m0 * m0 * m1 * m1 - 2._dp * m0 * m0 * m2 *m2 - 2._dp * m1 * m1 * m2 * m2
  kasqrt = sqrt(kasqrt)

 End Function kasqrt

 Real(dp) Function beta0(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0, m1, m2

  beta0 = m0 * m0 - m1 * m1 - m2 * m2 + kasqrt(m0,m1,m2)
  beta0 = beta0 / (2._dp * m1 * m2)

 End Function beta0

 Real(dp) Function beta1(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0, m1, m2

  beta1 = m0 * m0 - m1 * m1 + m2 * m2 - kasqrt(m0,m1,m2)
  beta1 = beta1 / (2._dp * m0 * m2)

 End Function beta1

 Real(dp) Function beta2(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0, m1, m2

  beta2 = m0 * m0 + m1 * m1 - m2 * m2 - kasqrt(m0,m1,m2)
  beta2 = beta2 / (2._dp * m0 * m1)

 End Function beta2

 Real(dp) Function SpecialLog(lambda,m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m1,m2

  Speciallog = kasqrt(m0,m1,m2)*kasqrt(m0,m1,m2)
  Speciallog = Speciallog / (lambda*m0*m1*m2)
  !write(*,*) "kasqrt(m0,m1,m2)",kasqrt(m0,m1,m2)
  Speciallog = Log(Speciallog)
  !write(*,*) "Speciallog value",Speciallog
  !Speciallog = 0._dp

 End Function SpecialLog

! at first the IR-divergent Bremsstrahlung integrals:
! here lambda denotes the regulator mass of the photon

 Real(dp) Function IR_00(lambda,m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m1,m2

  IR_00 = kasqrt(m0,m1,m2) *Speciallog(lambda,m0,m1,m2) &
   & - kasqrt(m0,m1,m2) &
   & - (m1*m1 - m2*m2) * Log(beta1(m0,m1,m2)/beta2(m0,m1,m2)) &
   & - m0 * m0 * Log(beta0(m0,m1,m2))
  IR_00 = IR_00/(4._dp * m0 * m0 * m0 * m0)
  
 End Function IR_00

 Real(dp) Function IR_11(lambda,m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m1,m2

  IR_11 = kasqrt(m0,m1,m2) *Speciallog(lambda,m0,m1,m2) &
   & - kasqrt(m0,m1,m2) &
   & - (m0*m0 - m2*m2) * Log(beta0(m0,m1,m2)/beta2(m0,m1,m2)) &
   & - m1 * m1 * Log(beta1(m0,m1,m2))
  IR_11 = IR_11/(4._dp * m0 * m0 * m1 * m1)
  
End Function IR_11


Real(dp) Function IR_0safe(m0,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m2

  IR_0safe = (-m0**2 + m2**2 - 2._dp*m2**2*Log(m2/m0))/(4._dp*m0**2)
  
End Function IR_0safe


Real(dp) Function IR_2safe(m0,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m2

  IR_2safe = (-m0**2 + m2**2 - 2._dp*m0**2*Log(m2/m0))/(4._dp*m0**2)
  
End Function IR_2safe

Real(dp) Function IR_00safe(lambda,m0,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m2

  IR_00safe = (2._dp*m2**2*Log(m2/m0) + (m0**2 - m2**2)*(-1._dp + Log((m0**2 - m2**2)/(m0*lambda))))/(4._dp*m0**4)
  
End Function IR_00safe


Real(dp) Function IR_02safe(lambda,m0,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m2

  IR_02safe = (Log(m2/m0)**2 - 2*Log(m2/m0)*Log((m0*lambda)/(m0**2 - m2**2)) + 2*Real(Li2((m0**2 - m2**2)/m0**2),dp))/(4._dp*m0**2)
  
End Function IR_02safe

Real(dp) Function IR_22safe(lambda,m0,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m2

  IR_22safe = ((m0**2 + m2**2)*Log(m2/m0) + (m0**2 - m2**2)*(-1._dp + Log((m0**2 - m2**2)/(m0*lambda))))/(4._dp*m0**2*m2**2)
  
End Function IR_22safe

Real(dp) Function IR_2up1safe(m0,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m2

  IR_2up1safe = (-((m0**2 - m2**2)*(5._dp*m0**2 + m2**2))/4._dp - m0**2*(-m0**2 + 2._dp*m2**2)*Log(m2/m0))/(4._dp*m0**2)
  
End Function IR_2up1safe


Real(dp) Function IR_0up2safe(m0,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m2

  IR_0up2safe = (-0.25_dp*(m0**2-3._dp*m2**2)*(m0**2-m2**2) + m2**4*Log(m2/m0))/(4._dp*m0**2)
  
End Function IR_0up2safe



 Real(dp) Function IR_22(lambda,m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m1,m2

  IR_22 = kasqrt(m0,m1,m2) *Speciallog(lambda,m0,m1,m2) &
   & - kasqrt(m0,m1,m2) &
   & - (m0*m0 - m1*m1) * Log(beta0(m0,m1,m2)/beta1(m0,m1,m2)) &
   & - m2 * m2 * Log(beta2(m0,m1,m2))
  IR_22 = IR_22/(4._dp * m0 * m0 * m2 * m2)
  
 End Function IR_22

 Real(dp) Function IR_01(lambda,m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m1,m2

  IR_01 = 2._dp *Speciallog(lambda,m0,m1,m2) * Log(beta2(m0,m1,m2))&
   & + 2._dp * Log(beta2(m0,m1,m2)) * Log(beta2(m0,m1,m2)) &
   & - Log(beta0(m0,m1,m2)) * Log(beta0(m0,m1,m2)) &
   & - Log(beta1(m0,m1,m2)) * Log(beta1(m0,m1,m2)) &
   & + 2._dp * Real(Li2(1._dp - beta2(m0,m1,m2)*beta2(m0,m1,m2)),dp) &
   & - Real(Li2(1._dp - beta0(m0,m1,m2)*beta0(m0,m1,m2)),dp) &
   & - Real(Li2(1._dp - beta1(m0,m1,m2)*beta1(m0,m1,m2)),dp)
  IR_01 = IR_01/(4._dp * m0 * m0)
  
 End Function IR_01

 Real(dp) Function IR_12(lambda,m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: lambda,m0,m1,m2

  IR_12 = 2._dp *Speciallog(lambda,m0,m1,m2) * Log(beta0(m0,m1,m2))&
   & + 2._dp * Log(beta0(m0,m1,m2)) * Log(beta0(m0,m1,m2)) &
   & - Log(beta1(m0,m1,m2)) * Log(beta1(m0,m1,m2)) &
   & - Log(beta2(m0,m1,m2)) * Log(beta2(m0,m1,m2)) &
   & + 2._dp * Real(Li2(1._dp - beta0(m0,m1,m2)*beta0(m0,m1,m2)),dp) &
   & - Real(Li2(1._dp - beta1(m0,m1,m2)*beta1(m0,m1,m2)),dp) &
   & - Real(Li2(1._dp - beta2(m0,m1,m2)*beta2(m0,m1,m2)),dp)
  IR_12 = IR_12/(4._dp * m0 * m0)
  
 End Function IR_12

! now the IR-finite Bremsstrahlung integrals:

 Real(dp) Function IRwithout(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IRwithout = kasqrt(m0,m1,m2) * (m0*m0 + m1*m1 + m2*m2) / 2._dp &
   & + 2._dp * m0*m0*m1*m1*Log(beta2(m0,m1,m2)) &
   & + 2._dp * m0*m0*m2*m2*Log(beta1(m0,m1,m2)) &
   & + 2._dp * m1*m1*m2*m2*Log(beta0(m0,m1,m2))
  IRwithout = IRwithout/(4._dp * m0 * m0)
  
End Function IRwithout

Real(dp) Function IRsafe(m0,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m2

  IRsafe = 0.5_dp*(m0**4-m2**4)+2._dp*m0**2*m2**2*log(m2/m0)
  IRsafe = IRsafe/(4._dp * m0 * m0)
  
 End Function IRsafe


 Real(dp) Function IR_0(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_0 = - 2._dp * m1*m1*Log(beta2(m0,m1,m2)) &
   & - 2._dp * m2*m2*Log(beta1(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2)
  IR_0 = IR_0/(4._dp * m0 * m0)
  
 End Function IR_0

 Real(dp) Function IR_1(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_1 = - 2._dp * m0*m0*Log(beta2(m0,m1,m2)) &
   & - 2._dp * m2*m2*Log(beta0(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2)
  IR_1 = IR_1/(4._dp * m0 * m0)
  
 End Function IR_1

 Real(dp) Function IR_2(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_2 = - 2._dp * m0*m0*Log(beta1(m0,m1,m2)) &
   & - 2._dp * m1*m1*Log(beta0(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2)
  IR_2 = IR_2/(4._dp * m0 * m0)
  
 End Function IR_2

 Real(dp) Function IR_0up1(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_0up1 = m1 * m1 * m1 * m1 *Log(beta2(m0,m1,m2)) &
   & - m2 * m2 * (2._dp * m0 * m0 - 2._dp * m1 * m1 + m2 * m2) * Log(beta1(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2) * (m0 * m0 - 3._dp * m1 * m1 + 5._dp * m2 * m2) / 4._dp
  IR_0up1 = IR_0up1/(4._dp * m0 * m0)
  
 End Function IR_0up1

 Real(dp) Function IR_0up2(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_0up2 = m2 * m2 * m2 * m2 *Log(beta1(m0,m1,m2)) &
   & - m1 * m1 * (2._dp * m0 * m0 - 2._dp * m2 * m2 + m1 * m1) * Log(beta2(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2) * (m0 * m0 - 3._dp * m2 * m2 + 5._dp * m1 * m1) / 4._dp
  IR_0up2 = IR_0up2/(4._dp * m0 * m0)
  
 End Function IR_0up2

 Real(dp) Function IR_1up0(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_1up0 = m0 * m0 * m0 * m0 *Log(beta2(m0,m1,m2)) &
   & - m2 * m2 * (2._dp * m1 * m1 - 2._dp * m0 * m0 + m2 * m2) * Log(beta0(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2) * (m1 * m1 - 3._dp * m0 * m0 + 5._dp * m2 * m2) / 4._dp
  IR_1up0 = IR_1up0/(4._dp * m0 * m0)
  
 End Function IR_1up0

 Real(dp) Function IR_2up0(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_2up0 = m0 * m0 * m0 * m0 *Log(beta1(m0,m1,m2)) &
   & - m1 * m1 * (2._dp * m2 * m2 - 2._dp * m0 * m0 + m1 * m1) * Log(beta0(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2) * (m2 * m2 - 3._dp * m0 * m0 + 5._dp * m1 * m1) / 4._dp
  IR_2up0 = IR_2up0/(4._dp * m0 * m0)
  
 End Function IR_2up0

 Real(dp) Function IR_2up1(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_2up1 = m1 * m1 * m1 * m1 *Log(beta0(m0,m1,m2)) &
   & - m0 * m0 * (2._dp * m2 * m2 - 2._dp * m1 * m1 + m0 * m0) * Log(beta1(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2) * (m2 * m2 - 3._dp * m1 * m1 + 5._dp * m0 * m0) / 4._dp
  IR_2up1 = IR_2up1/(4._dp * m0 * m0)
  
 End Function IR_2up1

 Real(dp) Function IR_1up2(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_1up2 = m2 * m2 * m2 * m2 *Log(beta0(m0,m1,m2)) &
   & - m0 * m0 * (2._dp * m1 * m1 - 2._dp * m2 * m2 + m0 * m0) * Log(beta2(m0,m1,m2)) &
   & - kasqrt(m0,m1,m2) * (m1 * m1 - 3._dp * m2 * m2 + 5._dp * m0 * m0) / 4._dp
  IR_1up2 = IR_1up2/(4._dp * m0 * m0)
  
 End Function IR_1up2

 Real(dp) Function IR_00up12(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_00up12 = m1 * m1 * m1 * m1 *Log(beta2(m0,m1,m2)) &
   & + m2 * m2 * m2 * m2 *Log(beta1(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m0 * m0) &
   & + kasqrt(m0,m1,m2) * (3._dp * m1 * m1 + 3._dp * m2 * m2 - m0 * m0) / 4._dp
  IR_00up12 = - IR_00up12/(4._dp * m0 * m0)
  
 End Function IR_00up12

 Real(dp) Function IR_11up02(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_11up02 = m0 * m0 * m0 * m0 *Log(beta2(m0,m1,m2)) &
   & + m2 * m2 * m2 * m2 *Log(beta0(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m1 * m1) &
   & + kasqrt(m0,m1,m2) * (3._dp * m0 * m0 + 3._dp * m2 * m2 - m1 * m1) / 4._dp
  IR_11up02 = - IR_11up02/(4._dp * m0 * m0)
  
 End Function IR_11up02

 Real(dp) Function IR_22up01(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_22up01 = m0 * m0 * m0 * m0 *Log(beta1(m0,m1,m2)) &
   & + m1 * m1 * m1 * m1 *Log(beta0(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m2 * m2) &
   & + kasqrt(m0,m1,m2) * (3._dp * m0 * m0 + 3._dp * m1 * m1 - m2 * m2) / 4._dp
  IR_22up01 = - IR_22up01/(4._dp * m0 * m0)
  
 End Function IR_22up01

 Real(dp) Function IR_11up00(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_11up00 = 2._dp * m2 * m2 * (m1*m1+m2*m2-m0*m0) * Log(beta0(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m1 * m1) &
   & + 2._dp * kasqrt(m0,m1,m2) * m2 * m2
  IR_11up00 = IR_11up00/(4._dp * m0 * m0)
  
 End Function IR_11up00

 Real(dp) Function IR_22up00(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_22up00 = 2._dp * m1 * m1 * (m2*m2+m1*m1-m0*m0) * Log(beta0(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m2 * m2) &
   & + 2._dp * kasqrt(m0,m1,m2) * m1 * m1
  IR_22up00 = IR_22up00/(4._dp * m0 * m0)
  
 End Function IR_22up00

 Real(dp) Function IR_00up11(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_00up11 = 2._dp * m2 * m2 * (m0*m0+m2*m2-m1*m1) * Log(beta1(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m0 * m0) &
   & + 2._dp * kasqrt(m0,m1,m2) * m2 * m2
  IR_00up11 = IR_00up11/(4._dp * m0 * m0)
  
 End Function IR_00up11

 Real(dp) Function IR_11up22(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_11up22 = 2._dp * m0 * m0 * (m0*m0+m1*m1-m2*m2) * Log(beta2(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m1 * m1) &
   & + 2._dp * kasqrt(m0,m1,m2) * m0 * m0
  IR_11up22 = IR_11up22/(4._dp * m0 * m0)
  
 End Function IR_11up22

 Real(dp) Function IR_22up11(m0,m1,m2)
 Implicit None
 Real(dp), Intent(in) :: m0,m1,m2

  IR_22up11 = 2._dp * m0 * m0 * (m0*m0 + m2*m2 - m1*m1) * Log(beta1(m0,m1,m2)) &
   & + kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) * kasqrt(m0,m1,m2) / (6._dp * m2 * m2) &
   & + 2._dp * kasqrt(m0,m1,m2) * m0 * m0
  IR_22up11 = IR_22up11/(4._dp * m0 * m0)
  
 End Function IR_22up11

Subroutine hardphotonFFW(Mi,Mo,MW,MLambda,Qi,Qo,CL,CR,CWP,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard photon emission
 !for the process Fin -> Fout Wplmi
 !------------------------------------------------------------
 !Involved particles:
 !- Fermion F_in with mass Mi and charge Qi
 !- Fermion F_out with mass Mo and charge Qo
 !   of course it should be: |Qi-Qo|=1
 !- W boson with mass MW
 !- Photon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !- \bar{F_out} gamma_\mu (CL PL + CR PR) F_in W^\mu
 !- CWP = Coupling W-W-Photon, sign irrelevant!:
 !   in SM, MSSM, ....:\pm I*g(SU2)*Sin(theta_W) = \pm I * EL
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR, CWP
  Real(dp), Intent(in) :: Mi, Mo, MW, MLambda
  Real(dp), Intent(in) :: Qi, Qo

  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01



  Real(dp) :: AbbCLCLQiQi, AbbCLCLQoQo, AbbCLCLQiQo, AbbCLCRQiQi, AbbCLCRQoQo, AbbCLCRQiQo
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR, SCWP
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardphotonFFW'

  If (Abs(Abs(Qi-Qo)-1._dp).GE.(0.001_dp)) Then
   write(*,*) "|Qi-Qo| for the hard photon emission Fi -> Fo W Phot is not 1!"
   write(*,*) "Like that the result for hard photon emission cannot be correct!"
  End If

!   If ((Abs(Mi)-Abs(Mo)-Abs(MW)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard photon emission!"
!   End If

  AbbCLCLQiQi = 0._dp
  AbbCLCLQoQo = 0._dp
  AbbCLCLQiQo = 0._dp
  AbbCLCRQiQi = 0._dp
  AbbCLCRQoQo = 0._dp
  AbbCLCRQiQo = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
  SCWP = Conjg(CWP)  

  IRf = IRwithout(Mi,Mo,MW)
  IRf_0 = IR_0(Mi,Mo,MW)
  IRf_1 = IR_1(Mi,Mo,MW)
  IRf_2 = IR_2(Mi,Mo,MW)
  IRf_00 = IR_00(MLambda,Mi,Mo,MW)
  IRf_01 = IR_01(MLambda,Mi,Mo,MW)
  IRf_02 = - IR_01(MLambda,Mi,Mo,MW) - IR_12(MLambda,Mi,Mo,MW)
  IRf_11 = IR_11(MLambda,Mi,Mo,MW)
  IRf_22 = IR_22(MLambda,Mi,Mo,MW)
  IRf_0up1 = IR_0up1(Mi,Mo,MW)
  IRf_1up0 = IR_1up0(Mi,Mo,MW)
  IRf_0up2 = IR_0up2(Mi,Mo,MW)
  IRf_2up0 = IR_2up0(Mi,Mo,MW)
  IRf_1up2 = IR_1up2(Mi,Mo,MW)
  IRf_2up1 = IR_2up1(Mi,Mo,MW)
  IRf_22up01 = IR_22up01(Mi,Mo,MW)



!  write(*,*) "--------------Hard Photon------------------"
!  write(*,*) "1",IRf
!  write(*,*) "2",IRf_0
!  write(*,*) "3",IRf_1 
!  write(*,*) "4",IRf_2
!  write(*,*) "5",IRf_00 
!  write(*,*) "6",IRf_01 
!  write(*,*) "7",IRf_02 
!  write(*,*) "8",IRf_11
!  write(*,*) "9",IRf_22 
!  write(*,*) "10",IRf_0up1 
!  write(*,*) "11",IRf_1up0 
!  write(*,*) "12",IRf_0up2 
!  write(*,*) "13",IRf_2up0
!  write(*,*) "14",IRf_1up2 
!  write(*,*) "15",IRf_2up1
!  write(*,*) "16",IRf_22up01
!  write(*,*) "--------------Hard Photon------------------"

  AbbCLCLQiQi = 2._dp*IRf*Mi**2 + 2._dp*IRf_0up2*Mi**2 - 4._dp*IRf_0*Mi**4 - 4._dp*IRf_2*Mi**4 - &
     &  4._dp*IRf_00*Mi**6 - 4._dp*IRf_02*Mi**6 + 2._dp*IRf*Mo**2 + 2._dp*IRf_0up2*Mo**2 + &
     &  8._dp*IRf_0*Mi**2*Mo**2 + 8._dp*IRf_2*Mi**2*Mo**2 + 8._dp*IRf_00*Mi**4*Mo**2 + &
     &  12._dp*IRf_02*Mi**4*Mo**2 - 4._dp*IRf_0*Mo**4 - 4._dp*IRf_2*Mo**4 - 4._dp*IRf_00*Mi**2*Mo**4 - & 
     &  12._dp*IRf_02*Mi**2*Mo**4 + 4._dp*IRf_02*Mo**6 + 4._dp*IRf*MW**2 + 4._dp*IRf_0up2*MW**2 - &
     &  8._dp*IRf_22up01*MW**2 - 8._dp*IRf_2up1*MW**2 - 4._dp*IRf_0*Mi**2*MW**2 - 4._dp*IRf_2*Mi**2*MW**2 - &
     &  4._dp*IRf_00*Mi**4*MW**2 - 8._dp*IRf_02*Mi**4*MW**2 - 4._dp*IRf_22*Mi**4*MW**2 - &
     &  4._dp*IRf_0*Mo**2*MW**2 - 4._dp*IRf_2*Mo**2*MW**2 - 4._dp*IRf_00*Mi**2*Mo**2*MW**2 + &
     &  8._dp*IRf_02*Mi**2*Mo**2*MW**2 + 8._dp*IRf_22*Mi**2*Mo**2*MW**2 - 4._dp*IRf_22*Mo**4*MW**2 + &
     &  8._dp*IRf_0*MW**4 + 8._dp*IRf_2*MW**4 + 8._dp*IRf_00*Mi**2*MW**4 + & 
     &  4._dp*IRf_02*Mi**2*MW**4 - 4._dp*IRf_22*Mi**2*MW**4 - 12._dp*IRf_02*Mo**2*MW**4 - &
     &  4._dp*IRf_22*Mo**2*MW**4 + 8._dp*IRf_02*MW**6 + 8._dp*IRf_22*MW**6

  AbbCLCLQoQo = -2*IRf_1up0*Mi**2 - 4._dp*IRf_1*Mi**4 - 4._dp*IRf_2*Mi**4 - 4._dp*IRf_01*Mi**6 - &
     &  4._dp*IRf_02*Mi**6 - 2._dp*IRf_1up0*Mo**2 + 8._dp*IRf_1*Mi**2*Mo**2 + 8._dp*IRf_2*Mi**2*Mo**2 + &
     &  12._dp*IRf_01*Mi**4*Mo**2 + 12._dp*IRf_02*Mi**4*Mo**2 - 4._dp*IRf_11*Mi**4*Mo**2 - &
     &  4._dp*IRf_1*Mo**4 - 4._dp*IRf_2*Mo**4 - 12._dp*IRf_01*Mi**2*Mo**4 - &
     &  12._dp*IRf_02*Mi**2*Mo**4 + 8._dp*IRf_11*Mi**2*Mo**4 + 4._dp*IRf_01*Mo**6 + &
     &  4._dp*IRf_02*Mo**6 - 4._dp*IRf_11*Mo**6 - 8._dp*IRf*MW**2 - 4._dp*IRf_1up0*MW**2 - 8._dp*IRf_22up01*MW**2 - &
     &  16._dp*IRf_2up0*MW**2 - 8._dp*IRf_2up1*MW**2 - 4._dp*IRf_1*Mi**2*MW**2 - 4._dp*IRf_2*Mi**2*MW**2 - &
     &  4._dp*IRf_22*Mi**4*MW**2 - 4._dp*IRf_1*Mo**2*MW**2 - 4._dp*IRf_2*Mo**2*MW**2 - &
     &  8._dp*IRf_01*Mi**2*Mo**2*MW**2 - 8._dp*IRf_02*Mi**2*Mo**2*MW**2 - &
     &  4._dp*IRf_11*Mi**2*Mo**2*MW**2 + 8._dp*IRf_22*Mi**2*Mo**2*MW**2 + 8._dp*IRf_01*Mo**4*MW**2 + &
     &  8._dp*IRf_02*Mo**4*MW**2 - 4._dp*IRf_11*Mo**4*MW**2 - 4._dp*IRf_22*Mo**4*MW**2 + 8._dp*IRf_1*MW**4 + &
     &  8._dp*IRf_2*MW**4 + 12._dp*IRf_01*Mi**2*MW**4 + 12._dp*IRf_02*Mi**2*MW**4 - &
     &  4._dp*IRf_22*Mi**2*MW**4 - 4._dp*IRf_01*Mo**2*MW**4 - 4._dp*IRf_02*Mo**2*MW**4 + &
     &  8._dp*IRf_11*Mo**2*MW**4 - 4._dp*IRf_22*Mo**2*MW**4 - 8._dp*IRf_01*MW**6 - &
     &  8._dp*IRf_02*MW**6 + 8._dp*IRf_22*MW**6

  AbbCLCLQiQo = - 6._dp*IRf*Mi**2 - 2._dp*IRf_0up1*Mi**2 - 2._dp*IRf_0up2*Mi**2 + 8._dp*IRf_2*Mi**4 + &
     &  8._dp*IRf_02*Mi**6 - 6._dp*IRf*Mo**2 - 2._dp*IRf_0up1*Mo**2 - 2._dp*IRf_0up2*Mo**2 - &
     &  16._dp*IRf_2*Mi**2*Mo**2 - 8._dp*IRf_01*Mi**4*Mo**2 - 24._dp*IRf_02*Mi**4*Mo**2 + &
     &  8._dp*IRf_2*Mo**4 + 16._dp*IRf_01*Mi**2*Mo**4 + 24._dp*IRf_02*Mi**2*Mo**4 - &
     &  8._dp*IRf_01*Mo**6 - 8._dp*IRf_02*Mo**6 + 4._dp*IRf*MW**2 - 4._dp*IRf_0up1*MW**2 - &
     &  4._dp*IRf_0up2*MW**2 + 16._dp*IRf_22up01*MW**2 + 16._dp*IRf_2up0*MW**2 + 16._dp*IRf_2up1*MW**2 + &
     &  8._dp*IRf_2*Mi**2*MW**2 + 8._dp*IRf_02*Mi**4*MW**2 + 8._dp*IRf_22*Mi**4*MW**2 + &
     &  8._dp*IRf_2*Mo**2*MW**2 - 8._dp*IRf_01*Mi**2*Mo**2*MW**2 - &
     &  16._dp*IRf_22*Mi**2*Mo**2*MW**2 - 8._dp*IRf_01*Mo**4*MW**2 - 8._dp*IRf_02*Mo**4*MW**2 +  &
     &  8._dp*IRf_22*Mo**4*MW**2 - 16._dp*IRf_2*MW**4 - 16._dp*IRf_02*Mi**2*MW**4 + &
     &  8._dp*IRf_22*Mi**2*MW**4 + 16._dp*IRf_01*Mo**2*MW**4 + 16._dp*IRf_02*Mo**2*MW**4 + &
     &  8._dp*IRf_22*Mo**2*MW**4 - 16._dp*IRf_22*MW**6

  AbbCLCRQiQi = -4*IRf*Mi*Mo - 4._dp*IRf_0up2*Mi*Mo + 24._dp*IRf_0*Mi*Mo*MW**2 + &
     &  24._dp*IRf_2*Mi*Mo*MW**2 + 24._dp*IRf_00*Mi**3*Mo*MW**2 + 24._dp*IRf_02*Mi**3*Mo*MW**2 - &
     &  24._dp*IRf_02*Mi*Mo**3*MW**2 + 24._dp*IRf_02*Mi*Mo*MW**4 + 24._dp*IRf_22*Mi*Mo*MW**4

  AbbCLCRQoQo =   4._dp*IRf_1up0*Mi*Mo + 24._dp*IRf_1*Mi*Mo*MW**2 + 24._dp*IRf_2*Mi*Mo*MW**2 + &
     &  24._dp*IRf_01*Mi**3*Mo*MW**2 + 24._dp*IRf_02*Mi**3*Mo*MW**2 - 24._dp*IRf_01*Mi*Mo**3*MW**2 - &
     &  24._dp*IRf_02*Mi*Mo**3*MW**2 + 24._dp*IRf_11*Mi*Mo**3*MW**2 - 24._dp*IRf_01*Mi*Mo*MW**4 - &
     &  24._dp*IRf_02*Mi*Mo*MW**4 + 24._dp*IRf_22*Mi*Mo*MW**4

  AbbCLCRQiQo = 12._dp*IRf*Mi*Mo + 4._dp*IRf_0up1*Mi*Mo + 4._dp*IRf_0up2*Mi*Mo - 48._dp*IRf_2*Mi*Mo*MW**2 - &
     &  48._dp*IRf_02*Mi**3*Mo*MW**2 + 48._dp*IRf_01*Mi*Mo**3*MW**2 + 48._dp*IRf_02*Mi*Mo**3*MW**2 - &
     &  48._dp*IRf_22*Mi*Mo*MW**4


  AbbCLCL = Qi * Qi * AbbCLCLQiQi + Qo * Qo * AbbCLCLQoQo + Qi * Qo * AbbCLCLQiQo
  AbbCLCR = Qi * Qi * AbbCLCRQiQi + Qo * Qo * AbbCLCRQoQo + Qi * Qo * AbbCLCRQiQo

  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL + (CR * SCL + CL * SCR) * AbbCLCR 

  Gammatotc = Gammatotc * CWP * SCWP / (2._dp * MW**2)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 

!  write(*,*) "--------------Hard Photon------------------"
!  write(*,*) "Mi",Mi
!  write(*,*) "Mo",Mo
!  write(*,*) "MW",MW
!  write(*,*) "CL",CL
!  write(*,*) "CR",CR
!  write(*,*) "CWP",CWP
!  write(*,*) "CLCL", (CL * SCL) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CRCR", (CR * SCR) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CLCR", (CR * SCL + CL * SCR) * AbbCLCR / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "Gamma",Gammatotc
!  write(*,*) "--------------Hard Photon------------------"

  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardphotonFFW


Subroutine hardphotonFFZ(Mi,Mo,MZ,MLambda,Qi,Qo,CL,CR,CWP,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard photon emission
 !for the process Fin -> Fout Z
 !------------------------------------------------------------
 !Involved particles:
 !- Fermion F_in with mass Mi and charge Qi
 !- Fermion F_out with mass Mo and charge Qo
 !   of course it should be: |Qi-Qo|=1
 !- Z boson with mass MZ
 !- Photon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !- \bar{F_out} gamma_\mu (CL PL + CR PR) F_in W^\mu
 !- CWP = Coupling W-W-Photon, sign irrelevant!:
 !   in SM, MSSM, ....:\pm I*g(SU2)*Sin(theta_W) = \pm I * EL
 !   to parameterize the electric charge!
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR, CWP
  Real(dp), Intent(in) :: Mi, Mo, MZ, MLambda
  Real(dp), Intent(in) :: Qi, Qo

  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  Real(dp) :: AbbCLCLQiQi, AbbCLCLQoQo, AbbCLCLQiQo, AbbCLCRQiQi, AbbCLCRQoQo, AbbCLCRQiQo
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR, SCWP
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardphotonFFZ'

!   If ((Abs(Mi)-Abs(Mo)-Abs(MZ)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard photon emission!"
!   End If

  AbbCLCLQiQi = 0._dp
  AbbCLCLQoQo = 0._dp
  AbbCLCLQiQo = 0._dp
  AbbCLCRQiQi = 0._dp
  AbbCLCRQoQo = 0._dp
  AbbCLCRQiQo = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
  SCWP = Conjg(CWP)  

  IRf = IRwithout(Mi,Mo,MZ)
  IRf_0 = IR_0(Mi,Mo,MZ)
  IRf_1 = IR_1(Mi,Mo,MZ)
  IRf_2 = IR_2(Mi,Mo,MZ)
  IRf_00 = IR_00(MLambda,Mi,Mo,MZ)
  IRf_01 = IR_01(MLambda,Mi,Mo,MZ)
  IRf_02 = - IR_01(MLambda,Mi,Mo,MZ) - IR_12(MLambda,Mi,Mo,MZ)
  IRf_11 = IR_11(MLambda,Mi,Mo,MZ)
  IRf_22 = IR_22(MLambda,Mi,Mo,MZ)
  IRf_0up1 = IR_0up1(Mi,Mo,MZ)
  IRf_1up0 = IR_1up0(Mi,Mo,MZ)
  IRf_0up2 = IR_0up2(Mi,Mo,MZ)
  IRf_2up0 = IR_2up0(Mi,Mo,MZ)
  IRf_1up2 = IR_1up2(Mi,Mo,MZ)
  IRf_2up1 = IR_2up1(Mi,Mo,MZ)
  IRf_22up01 = IR_22up01(Mi,Mo,MZ)

!  write(*,*) "--------------Hard Photon------------------"
!  write(*,*) "1",IRf
!  write(*,*) "2",IRf_0
!  write(*,*) "3",IRf_1 
!  write(*,*) "4",IRf_2
!  write(*,*) "5",IRf_00 
!  write(*,*) "6",IRf_01 
!  write(*,*) "7",IRf_02 
!  write(*,*) "8",IRf_11
!  write(*,*) "9",IRf_22 
!  write(*,*) "10",IRf_0up1 
!  write(*,*) "11",IRf_1up0 
!  write(*,*) "12",IRf_0up2 
!  write(*,*) "13",IRf_2up0
!  write(*,*) "14",IRf_1up2 
!  write(*,*) "15",IRf_2up1
!  write(*,*) "16",IRf_22up01
!  write(*,*) "--------------Hard Photon------------------"

  AbbCLCLQiQi = - 2._dp*IRf*Mi**2 - 6._dp*IRf_0*Mi**4 - 4._dp*IRf_00*Mi**6 &
    & - 2._dp*IRf*Mo**2 + 4._dp*IRf_0*Mi**2*Mo**2 + 8._dp*IRf_00*Mi**4*Mo**2 &
    & + 2._dp*IRf_0*Mo**4 - 4._dp*IRf_00*Mi**2*Mo**4 + 4._dp*IRf*MZ**2  &
    & - 2._dp*IRf_0*Mi**2*MZ**2 - 4._dp*IRf_00*Mi**4*MZ**2 + 2._dp*IRf_0*Mo**2*MZ**2 &
    & - 4._dp*IRf_00*Mi**2*Mo**2*MZ**2 - 4._dp*IRf_0*MZ**4 + 8._dp*IRf_00*Mi**2*MZ**4

  AbbCLCLQoQo =  -2*IRf*Mi**2 + 2._dp*IRf_1*Mi**4 - 2._dp*IRf*Mo**2 &
    & + 4._dp*IRf_1*Mi**2*Mo**2 - 4._dp*IRf_11*Mi**4*Mo**2 - 6._dp*IRf_1*Mo**4 &
    & + 8._dp*IRf_11*Mi**2*Mo**4 - 4._dp*IRf_11*Mo**6 + 4._dp*IRf*MZ**2 &
    & + 2._dp*IRf_1*Mi**2*MZ**2 - 2._dp*IRf_1*Mo**2*MZ**2 &
    & - 4._dp*IRf_11*Mi**2*Mo**2*MZ**2 - 4._dp*IRf_11*Mo**4*MZ**2 &
    & - 4._dp*IRf_1*MZ**4 + 8._dp*IRf_11*Mo**2*MZ**4

  AbbCLCLQiQo = -2*IRf_0up1*Mi**2 - 2._dp*IRf_1up0*Mi**2 + 2._dp*IRf_0*Mi**4 &
    & - 6._dp*IRf_1*Mi**4 - 4._dp*IRf_01*Mi**6 - 2._dp*IRf_0up1*Mo**2 &
    & - 2._dp*IRf_1up0*Mo**2 + 4._dp*IRf_0*Mi**2*Mo**2 + 4._dp*IRf_1*Mi**2*Mo**2 &
    & + 4._dp*IRf_01*Mi**4*Mo**2 - 6._dp*IRf_0*Mo**4 + 2._dp*IRf_1*Mo**4 &
    &  + 4._dp*IRf_01*Mi**2*Mo**4 - 4._dp*IRf_01*Mo**6 - 8._dp*IRf*MZ**2 &
    & - 4._dp*IRf_0up1*MZ**2 - 4._dp*IRf_1up0*MZ**2 - 2._dp*IRf_0*Mi**2*MZ**2 &
    & - 6._dp*IRf_1*Mi**2*MZ**2 - 6._dp*IRf_0*Mo**2*MZ**2 - 2._dp*IRf_1*Mo**2*MZ**2 &
    & - 16._dp*IRf_01*Mi**2*Mo**2*MZ**2 + 12._dp*IRf_0*MZ**4 + 12._dp*IRf_1*MZ**4 &
    & + 12._dp*IRf_01*Mi**2*MZ**4 + 12._dp*IRf_01*Mo**2*MZ**4 - 8._dp*IRf_01*MZ**6

  AbbCLCRQiQi = 24._dp*IRf_00*Mi**3*Mo*MZ**2

  AbbCLCRQoQo =  24._dp*IRf_11*Mi*Mo**3*MZ**2 

  AbbCLCRQiQo = 8._dp*IRf*Mi*Mo + 4._dp*IRf_0up1*Mi*Mo + 4._dp*IRf_1up0*Mi*Mo &
    & + 24._dp*IRf_0*Mi*Mo*MZ**2 + 24._dp*IRf_1*Mi*Mo*MZ**2 + 24._dp*IRf_01*Mi**3*Mo*MZ**2 &
    & + 24._dp*IRf_01*Mi*Mo**3*MZ**2 - 24._dp*IRf_01*Mi*Mo*MZ**4

  AbbCLCL = Qi * Qi * AbbCLCLQiQi + Qo * Qo * AbbCLCLQoQo + Qi * Qo * AbbCLCLQiQo
  AbbCLCR = Qi * Qi * AbbCLCRQiQi + Qo * Qo * AbbCLCRQoQo + Qi * Qo * AbbCLCRQiQo

  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL + (CR * SCL + CL * SCR) * AbbCLCR 

  Gammatotc = Gammatotc * CWP * SCWP / (2._dp * MZ**2)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 

!  write(*,*) "--------------Hard Photon------------------"
!  write(*,*) "Mi",Mi
!  write(*,*) "Mo",Mo
!  write(*,*) "MW",MW
!  write(*,*) "CL",CL
!  write(*,*) "CR",CR
!  write(*,*) "CWP",CWP
!  write(*,*) "CLCL", (CL * SCL) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CRCR", (CR * SCR) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CLCR", (CR * SCL + CL * SCR) * AbbCLCR / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "Gamma",Gammatotc
!  write(*,*) "--------------Hard Photon------------------"

  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardphotonFFZ



Subroutine hardgluonFFZW(Mi,Mo,MZ,MLambda,CasR,GStrong,CL,CR,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard gluon emission
 !for the process Fin -> Fout Z
 !------------------------------------------------------------
 !Involved particles:
 !- Fermion F_in with mass Mi and Casimir CasR under strong interaction
 !- Fermion F_out with mass Mo and  Casimir CasR under strong interaction
 !   ... i.e. must be in the same rep!
 !- Z or W boson with mass MZ
 !- Photon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !- \bar{F_out} gamma_\mu (CL PL + CR PR) F_in V^\mu + h.c.
 !Here V is either Z or W
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !adapted from corrections written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR
  Real(dp), Intent(in) :: CasR, GStrong, Mi, Mo, MZ, MLambda


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  Real(dp) :: AbbCLCLQiQi, AbbCLCLQoQo, AbbCLCLQiQo, AbbCLCRQiQi, AbbCLCRQoQo, AbbCLCRQiQo
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR, SCWP
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardgluonFFZW'

!   If ((Abs(Mi)-Abs(Mo)-Abs(MZ)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard gluon emission!"
!   End If

  AbbCLCLQiQi = 0._dp
  AbbCLCLQoQo = 0._dp
  AbbCLCLQiQo = 0._dp
  AbbCLCRQiQi = 0._dp
  AbbCLCRQoQo = 0._dp
  AbbCLCRQiQo = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
!  SCWP = Conjg(CWP)  

  IRf = IRwithout(Mi,Mo,MZ)
  IRf_0 = IR_0(Mi,Mo,MZ)
  IRf_1 = IR_1(Mi,Mo,MZ)
  IRf_2 = IR_2(Mi,Mo,MZ)
  IRf_00 = IR_00(MLambda,Mi,Mo,MZ)
  IRf_01 = IR_01(MLambda,Mi,Mo,MZ)
  IRf_02 = - IR_01(MLambda,Mi,Mo,MZ) - IR_12(MLambda,Mi,Mo,MZ)
  IRf_11 = IR_11(MLambda,Mi,Mo,MZ)
  IRf_22 = IR_22(MLambda,Mi,Mo,MZ)
  IRf_0up1 = IR_0up1(Mi,Mo,MZ)
  IRf_1up0 = IR_1up0(Mi,Mo,MZ)
  IRf_0up2 = IR_0up2(Mi,Mo,MZ)
  IRf_2up0 = IR_2up0(Mi,Mo,MZ)
  IRf_1up2 = IR_1up2(Mi,Mo,MZ)
  IRf_2up1 = IR_2up1(Mi,Mo,MZ)
  IRf_22up01 = IR_22up01(Mi,Mo,MZ)

!  write(*,*) "--------------Hard Photon------------------"
!  write(*,*) "1",IRf
!  write(*,*) "2",IRf_0
!  write(*,*) "3",IRf_1 
!  write(*,*) "4",IRf_2
!  write(*,*) "5",IRf_00 
!  write(*,*) "6",IRf_01 
!  write(*,*) "7",IRf_02 
!  write(*,*) "8",IRf_11
!  write(*,*) "9",IRf_22 
!  write(*,*) "10",IRf_0up1 
!  write(*,*) "11",IRf_1up0 
!  write(*,*) "12",IRf_0up2 
!  write(*,*) "13",IRf_2up0
!  write(*,*) "14",IRf_1up2 
!  write(*,*) "15",IRf_2up1
!  write(*,*) "16",IRf_22up01
!  write(*,*) "--------------Hard Photon------------------"

  AbbCLCLQiQi = - 2._dp*IRf*Mi**2 - 6._dp*IRf_0*Mi**4 - 4._dp*IRf_00*Mi**6 &
    & - 2._dp*IRf*Mo**2 + 4._dp*IRf_0*Mi**2*Mo**2 + 8._dp*IRf_00*Mi**4*Mo**2 &
    & + 2._dp*IRf_0*Mo**4 - 4._dp*IRf_00*Mi**2*Mo**4 + 4._dp*IRf*MZ**2  &
    & - 2._dp*IRf_0*Mi**2*MZ**2 - 4._dp*IRf_00*Mi**4*MZ**2 + 2._dp*IRf_0*Mo**2*MZ**2 &
    & - 4._dp*IRf_00*Mi**2*Mo**2*MZ**2 - 4._dp*IRf_0*MZ**4 + 8._dp*IRf_00*Mi**2*MZ**4

  AbbCLCLQoQo =  -2*IRf*Mi**2 + 2._dp*IRf_1*Mi**4 - 2._dp*IRf*Mo**2 &
    & + 4._dp*IRf_1*Mi**2*Mo**2 - 4._dp*IRf_11*Mi**4*Mo**2 - 6._dp*IRf_1*Mo**4 &
    & + 8._dp*IRf_11*Mi**2*Mo**4 - 4._dp*IRf_11*Mo**6 + 4._dp*IRf*MZ**2 &
    & + 2._dp*IRf_1*Mi**2*MZ**2 - 2._dp*IRf_1*Mo**2*MZ**2 &
    & - 4._dp*IRf_11*Mi**2*Mo**2*MZ**2 - 4._dp*IRf_11*Mo**4*MZ**2 &
    & - 4._dp*IRf_1*MZ**4 + 8._dp*IRf_11*Mo**2*MZ**4

  AbbCLCLQiQo = -2*IRf_0up1*Mi**2 - 2._dp*IRf_1up0*Mi**2 + 2._dp*IRf_0*Mi**4 &
    & - 6._dp*IRf_1*Mi**4 - 4._dp*IRf_01*Mi**6 - 2._dp*IRf_0up1*Mo**2 &
    & - 2._dp*IRf_1up0*Mo**2 + 4._dp*IRf_0*Mi**2*Mo**2 + 4._dp*IRf_1*Mi**2*Mo**2 &
    & + 4._dp*IRf_01*Mi**4*Mo**2 - 6._dp*IRf_0*Mo**4 + 2._dp*IRf_1*Mo**4 &
    &  + 4._dp*IRf_01*Mi**2*Mo**4 - 4._dp*IRf_01*Mo**6 - 8._dp*IRf*MZ**2 &
    & - 4._dp*IRf_0up1*MZ**2 - 4._dp*IRf_1up0*MZ**2 - 2._dp*IRf_0*Mi**2*MZ**2 &
    & - 6._dp*IRf_1*Mi**2*MZ**2 - 6._dp*IRf_0*Mo**2*MZ**2 - 2._dp*IRf_1*Mo**2*MZ**2 &
    & - 16._dp*IRf_01*Mi**2*Mo**2*MZ**2 + 12._dp*IRf_0*MZ**4 + 12._dp*IRf_1*MZ**4 &
    & + 12._dp*IRf_01*Mi**2*MZ**4 + 12._dp*IRf_01*Mo**2*MZ**4 - 8._dp*IRf_01*MZ**6

  AbbCLCRQiQi = 24._dp*IRf_00*Mi**3*Mo*MZ**2

  AbbCLCRQoQo =  24._dp*IRf_11*Mi*Mo**3*MZ**2 

  AbbCLCRQiQo = 8._dp*IRf*Mi*Mo + 4._dp*IRf_0up1*Mi*Mo + 4._dp*IRf_1up0*Mi*Mo &
    & + 24._dp*IRf_0*Mi*Mo*MZ**2 + 24._dp*IRf_1*Mi*Mo*MZ**2 + 24._dp*IRf_01*Mi**3*Mo*MZ**2 &
    & + 24._dp*IRf_01*Mi*Mo**3*MZ**2 - 24._dp*IRf_01*Mi*Mo*MZ**4

  AbbCLCL = AbbCLCLQiQi + AbbCLCLQoQo + AbbCLCLQiQo
  AbbCLCR = AbbCLCRQiQi + AbbCLCRQoQo + AbbCLCRQiQo

  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL + (CR * SCL + CL * SCR) * AbbCLCR 

  Gammatotc = Gammatotc * CasR * GStrong**2/ (2._dp * MZ**2)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 

!  write(*,*) "--------------Hard gluon------------------"
!  write(*,*) "Mi",Mi
!  write(*,*) "Mo",Mo
!  write(*,*) "MW",MW
!  write(*,*) "CL",CL
!  write(*,*) "CR",CR
!  write(*,*) "CWP",CWP
!  write(*,*) "CLCL", (CL * SCL) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CRCR", (CR * SCR) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CLCR", (CR * SCL + CL * SCR) * AbbCLCR / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "Gamma",Gammatotc
!  write(*,*) "--------------Hard gluon------------------"

  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardgluonFFZW



Subroutine hardradiationFFS(Mi,Mo,Ms,MLambda,GC,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33,CL,CR,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard gluon or photon emission
 !for the process Fin -> Fout Scalar-bar
 !------------------------------------------------------------
 !Involved particles:
 !- Fermion F_in with mass Mi and Casimir CasR under strong interaction
 !- Fermion F_out with mass Mo and  Casimir CasR under strong interaction
 !   ... i.e. must be in the same rep!
 !- Scalar S_out with mas Ms
 !- Photon or gluon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !- \bar{F_out} (CL PL + CR PR) F_in S + h.c.
 ! GC is the gauge couplings
 ! Casij is the group factor for the combination where we attach 
 ! the gauge boson on leg i of the diagram to leg j of the conjugate
 ! Leg 1 -> Fermion in
 ! Leg 2 -> Fermion out
 ! Leg 3 -> Scalar
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !adapted from corrections written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR
  Real(dp), Intent(in) :: GC, Mi, Mo, Ms, MLambda,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  real(dp) :: IRf_02up1,IRf_02up11,irf_12,irf_12up0,irf_12up00,irf_22up0,irf_22up00,irf_22up1,irf_22up11


  Real(dp) :: AbbCLCL11, AbbCLCL12, AbbCLCL13,AbbCLCL22,AbbCLCL23,AbbCLCL33
  real(dp) :: AbbCLCR11, AbbCLCR12, AbbCLCR13,AbbCLCR22,AbbCLCR23,AbbCLCR33
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardradiationFFS'

!   If ((Abs(Mi)-Abs(Mo)-Abs(Ms)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard gluon emission!"
! End If

 if(abs(mo) .eq. 0._dp) then
     call hardradiationFFSmFzero(Mi,Ms,MLambda,GC,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33,CL,CR,Gammatotbrems,kont)
     Iname = Iname - 1
     return
  end if

  ! if(abs(mb) .eq. 0._dp) then
  !    call hardradiationFFSmSzero(Mi,Ma,MLambda,GC,Cas11,-Cas12,Cas22,CL,CR,Gammatotbrems,kont)
  !    Iname = Iname - 1
  !    return
  ! end if


  AbbCLCL11 = 0._dp
  AbbCLCL12 = 0._dp
  AbbCLCL13 = 0._dp
  AbbCLCL22 = 0._dp
  AbbCLCL23 = 0._dp
  AbbCLCL33 = 0._dp
  
  AbbCLCR11 = 0._dp
  AbbCLCR12 = 0._dp
  AbbCLCR13 = 0._dp
  AbbCLCR22 = 0._dp
  AbbCLCR23 = 0._dp
  AbbCLCR33 = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
!  SCWP = Conjg(CWP)  

  IRf = IRwithout(Mi,Mo,Ms)
  IRf_0 = IR_0(Mi,Mo,Ms)
  IRf_1 = IR_1(Mi,Mo,Ms)
  IRf_2 = IR_2(Mi,Mo,Ms)
  IRf_00 = IR_00(MLambda,Mi,Mo,Ms)
  IRf_01 = IR_01(MLambda,Mi,Mo,Ms)
  IRf_02 = - IR_01(MLambda,Mi,Mo,Ms) - IR_12(MLambda,Mi,Mo,Ms)
  IRf_11 = IR_11(MLambda,Mi,Mo,Ms)
  IRf_22 = IR_22(MLambda,Mi,Mo,Ms)
  IRf_0up1 = IR_0up1(Mi,Mo,Ms)
  IRf_1up0 = IR_1up0(Mi,Mo,Ms)
  IRf_0up2 = IR_0up2(Mi,Mo,Ms)
  IRf_2up0 = IR_2up0(Mi,Mo,Ms)
  IRf_1up2 = IR_1up2(Mi,Mo,Ms)
  IRf_2up1 = IR_2up1(Mi,Mo,Ms)
  IRf_22up01 = IR_22up01(Mi,Mo,Ms)


!!!!!! MARK'S DEFS:
  
!  IRf_02up1 = -IRf_1 - IRf_2
!  IRf_02up11 = -IRf - IRf_2up1
  IRf_12=-IRf_01 - IRf_02
!  IRf_12up0=-IRf_1 - IRf_2
!  IRf_12up00=-IRf_1up0 - IRf_2up0

!  IRf_22up00=IR_22up00(Mi,Mo,Ms)
!  IRf_22up11=IR_22up11(Mi,Mo,Ms)



!!!!!!! END MARK's DEFS



!  write(*,*) "--------------Hard Photon------------------"
!  write(*,*) "1",IRf
!  write(*,*) "2",IRf_0
!  write(*,*) "3",IRf_1 
!  write(*,*) "4",IRf_2
!  write(*,*) "5",IRf_00 
!  write(*,*) "6",IRf_01 
!  write(*,*) "7",IRf_02 
!  write(*,*) "8",IRf_11
!  write(*,*) "9",IRf_22 
!  write(*,*) "10",IRf_0up1 
!  write(*,*) "11",IRf_1up0 
!  write(*,*) "12",IRf_0up2 
!  write(*,*) "13",IRf_2up0
!  write(*,*) "14",IRf_1up2 
!  write(*,*) "15",IRf_2up1
!  write(*,*) "16",IRf_22up01
!  write(*,*) "--------------Hard Photon------------------"

AbbCLCR11 = -8._dp*Mi**3*Mo*IRf_00

AbbCLCR12 = (-8._dp*Mi**3*Mo - 8._dp*Mi*Mo**3 + 8._dp*Mi*Mo*Ms**2)*IRf_01-8._dp*Mi*Mo*IRf_0-8._dp*Mi*Mo*IRf_1

AbbCLCR13 = (8._dp*Mi**3*Mo - 8._dp*Mi*Mo**3 + 8._dp*Mi*Mo*Ms**2)*IRf_02+8._dp*Mi*Mo*IRf_0

AbbCLCR22 = -8._dp*Mi*Mo**3*IRf_11

AbbCLCR23 = (8._dp*Mi**3*Mo - 8._dp*Mi*Mo**3 - 8._dp*Mi*Mo*Ms**2)*IRf_12-8._dp*Mi*Mo*IRf_1

AbbCLCR33 = -8._dp*Mi*Mo*Ms**2*IRf_22-8._dp*Mi*Mo*IRf_2



AbbCLCL11 = (-4._dp*Mi**4 - 4._dp*Mi**2*Mo**2 + 4._dp*Mi**2*Ms**2)*IRf_00+(-2._dp*Mi**2 + 2._dp*Mo**2 - 2._dp*Ms**2)*IRf_0+2._dp*IRf

AbbCLCL12 = (-4._dp*Mi**4 - 8._dp*Mi**2*Mo**2 - 4._dp*Mo**4 + 8._dp*Mi**2*Ms**2 + 8._dp*Mo**2*Ms**2 - 4._dp*Ms**4)*IRf_01+(-2._dp*Mi**2 - 6._dp*Mo**2 + 6._dp*Ms**2)*IRf_0-2._dp*IRf_0up1+(-6._dp*Mi**2 - 2._dp*Mo**2 + 6._dp*Ms**2)*IRf_1-8._dp*IRf-2._dp*IRf_1up0

AbbCLCL13 = (4._dp*Mi**4 - 4._dp*Mo**4 + 8._dp*Mo**2*Ms**2 - 4._dp*Ms**4)*IRf_02+(2._dp*Mi**2 + 6._dp*Mo**2 - 6._dp*Ms**2)*IRf_0-2._dp*IRf_0up2+4._dp*Ms**2*IRf_2+4._dp*IRf

AbbCLCL22 = (-4._dp*Mi**2*Mo**2 - 4._dp*Mo**4 + 4._dp*Mo**2*Ms**2)*IRf_11+(2._dp*Mi**2 - 2._dp*Mo**2 - 2._dp*Ms**2)*IRf_1+2._dp*IRf

AbbCLCL23 = (4._dp*Mi**4 - 4._dp*Mo**4 - 8._dp*Mi**2*Ms**2 + 4._dp*Ms**4)*IRf_12+(-6._dp*Mi**2 - 2._dp*Mo**2 + 6._dp*Ms**2)*IRf_1+2._dp*IRf_1up2-4._dp*Ms**2*IRf_2-4._dp*IRf

AbbCLCL33 = (-4._dp*Mi**2*Ms**2 - 4._dp*Mo**2*Ms**2 + 4._dp*Ms**4)*IRf_22+(-4._dp*Mi**2 - 4._dp*Mo**2 + 8._dp*Ms**2)*IRf_2+4._dp*IRf


!!!!!!!!!!!
! Minus signs because we calculate the casimirs with T(Sbar) = - T(S)
!!!!!!!!!!!
  
AbbCLCR = Cas11*AbbCLCR11 + Cas12*AbbCLCR12 - Cas13*AbbCLCR13 + Cas22*AbbCLCR22 - Cas23*AbbCLCR23 + Cas33*AbbCLCR33
AbbCLCL = Cas11*AbbCLCL11 + Cas12*AbbCLCL12 - Cas13*AbbCLCL13 + Cas22*AbbCLCL22 - Cas23*AbbCLCL23 + Cas33*AbbCLCL33



!!!!!!!!


  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL + (CR * SCL + CL * SCR) * AbbCLCR 

  Gammatotc = Gammatotc * GC**2/ (2._dp)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 

!  write(*,*) "--------------Hard gluon------------------"
!  write(*,*) "Mi",Mi
!  write(*,*) "Mo",Mo
!  write(*,*) "MW",MW
!  write(*,*) "CL",CL
!  write(*,*) "CR",CR
!  write(*,*) "CWP",CWP
!  write(*,*) "CLCL", (CL * SCL) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CRCR", (CR * SCR) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CLCR", (CR * SCL + CL * SCR) * AbbCLCR / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "Gamma",Gammatotc
!  write(*,*) "--------------Hard gluon------------------"

  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardradiationFFS

Subroutine hardradiationFFSmFzero(Mi,Ms,MLambda,GC,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33,CL,CR,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard gluon or photon emission
 !for the process Fin -> Fout Scalar-bar
 !------------------------------------------------------------
 !Involved particles:
 !- Fermion F_in with mass Mi and Casimir CasR under strong interaction
 !- Fermion F_out with mass Mo and  Casimir CasR under strong interaction
 !   ... i.e. must be in the same rep!
 !- Scalar S_out with mas Ms
 !- Photon or gluon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !- \bar{F_out} (CL PL + CR PR) F_in S + h.c.
 ! GC is the gauge couplings
 ! Casij is the group factor for the combination where we attach 
 ! the gauge boson on leg i of the diagram to leg j of the conjugate
 ! Leg 1 -> Fermion in
 ! Leg 2 -> Fermion out
 ! Leg 3 -> Scalar
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !adapted from corrections written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR
  Real(dp), Intent(in) :: GC, Mi, Ms, MLambda,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  real(dp) :: IRf_02up1,IRf_02up11,irf_12,irf_12up0,irf_12up00,irf_22up0,irf_22up00,irf_22up1,irf_22up11


  Real(dp) :: AbbCLCL11, AbbCLCL12, AbbCLCL13,AbbCLCL22,AbbCLCL23,AbbCLCL33
  real(dp) :: AbbCLCR11, AbbCLCR12, AbbCLCR13,AbbCLCR22,AbbCLCR23,AbbCLCR33
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR

  real(dp) :: Mo
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardradiationFFS'

!   If ((Abs(Mi)-Abs(Mo)-Abs(Ms)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard gluon emission!"
! End If

 

  ! if(abs(mb) .eq. 0._dp) then
  !    call hardradiationFFSmSzero(Mi,Ma,MLambda,GC,Cas11,-Cas12,Cas22,CL,CR,Gammatotbrems,kont)
  !    Iname = Iname - 1
  !    return
  ! end if
  Mo=0._dp

  AbbCLCL11 = 0._dp
  AbbCLCL12 = 0._dp
  AbbCLCL13 = 0._dp
  AbbCLCL22 = 0._dp
  AbbCLCL23 = 0._dp
  AbbCLCL33 = 0._dp
  
  AbbCLCR11 = 0._dp
  AbbCLCR12 = 0._dp
  AbbCLCR13 = 0._dp
  AbbCLCR22 = 0._dp
  AbbCLCR23 = 0._dp
  AbbCLCR33 = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
!  SCWP = Conjg(CWP)  

  IRf = IRsafe(Mi,Ms)
!  IRf_0 = IR_0(Mi,Mo,Ms)
!  IRf_1 = IR_1(Mi,Mo,Ms)
!  IRf_2 = IR_2(Mi,Mo,Ms)

  IRf_0 = IR_0safe(Mi,Ms)
  
  IRf_2 = IR_2safe(Mi,Ms)
  IRf_00 = IR_00safe(MLambda,Mi,Ms)
  IRf_02 = IR_02safe(MLambda,Mi,Ms)
  IRf_22 = IR_22safe(MLambda,Mi,Ms)
  IRf_2up1 = IR_2up1safe(Mi,Ms)
  IRf_0up2 = IR_0up2safe(Mi,Ms)



  
AbbCLCL11 = (-4._dp*Mi**4  + 4._dp*Mi**2*Ms**2)*IRf_00+(-2._dp*Mi**2 - 2._dp*Ms**2)*IRf_0+2._dp*IRf

AbbCLCL13 = (4._dp*Mi**4 + 8._dp*Mo**2*Ms**2 - 4._dp*Ms**4)*IRf_02+(2._dp*Mi**2  - 6._dp*Ms**2)*IRf_0-2._dp*IRf_0up2+4._dp*Ms**2*IRf_2+4._dp*IRf

AbbCLCL33 = (-4._dp*Mi**2*Ms**2  + 4._dp*Ms**4)*IRf_22+(-4._dp*Mi**2 + 8._dp*Ms**2)*IRf_2+4._dp*IRf


!!!!!!!!!!!
! Minus signs because we calculate the casimirs with T(Sbar) = - T(S)
!!!!!!!!!!!
  
AbbCLCL = Cas11*AbbCLCL11  - Cas13*AbbCLCL13  + Cas33*AbbCLCL33



!!!!!!!!


  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL !+ (CR * SCL + CL * SCR) * AbbCLCR 

  Gammatotc = Gammatotc * GC**2/ (2._dp)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 


  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardradiationFFSmFzero





 

Subroutine hardradiationSFF(Mi,Ma,Mb,MLambda,GC,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33,CL,CR,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard gluon or photon emission
 !for the process S (mi) -> Fbar (ma) + F(mb)
 !------------------------------------------------------------
 !Involved particles:
 !- Scalar S_in with mass Mi 
 !- Anti-Fermion F_a with mass Ma 
 !- Fermion F_b with mass Mb
 !- Photon or gluon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !- \bar{F_b} (CL PL + CR PR) F_a S + h.c.
 ! GC is the gauge coupling
 ! Casij is the group factor for the combination where we attach 
 ! the gauge boson on leg i of the diagram to leg j of the conjugate
 ! Leg 1 -> Scalar in
 ! Leg 2 -> Anti-Fermion F_a out
 ! Leg 3 -> Fermion F_b out
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !adapted from corrections written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR
  Real(dp), Intent(in) :: GC, Mi, Ma, Mb, MLambda,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  real(dp) :: IRf_02up1,IRf_02up11,irf_12,irf_12up0,irf_12up00,irf_22up0,irf_22up00,irf_22up1,irf_22up11


  Real(dp) :: AbbCLCL11, AbbCLCL12, AbbCLCL13,AbbCLCL22,AbbCLCL23,AbbCLCL33
  real(dp) :: AbbCLCR11, AbbCLCR12, AbbCLCR13,AbbCLCR22,AbbCLCR23,AbbCLCR33
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardradiationFFS'

!   If ((Abs(Mi)-Abs(Ma)-Abs(Mb)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard gluon emission!"
!   End If

  if(abs(ma) .eq. 0._dp) then
     call hardradiationSFFmzero(Mi,Mb,MLambda,GC,Cas11,Cas13,Cas33,CL,CR,Gammatotbrems,kont)
     Iname = Iname - 1
     return
  end if

  if(abs(mb) .eq. 0._dp) then
     call hardradiationSFFmzero(Mi,Ma,MLambda,GC,Cas11,-Cas12,Cas22,CL,CR,Gammatotbrems,kont)
     Iname = Iname - 1
     return
  end if
  
  
  AbbCLCL11 = 0._dp
  AbbCLCL12 = 0._dp
  AbbCLCL13 = 0._dp
  AbbCLCL22 = 0._dp
  AbbCLCL23 = 0._dp
  AbbCLCL33 = 0._dp
  
  AbbCLCR11 = 0._dp
  AbbCLCR12 = 0._dp
  AbbCLCR13 = 0._dp
  AbbCLCR22 = 0._dp
  AbbCLCR23 = 0._dp
  AbbCLCR33 = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
!  SCWP = Conjg(CWP)  



  
  IRf = IRwithout(Mi,Ma,Mb)
  IRf_0 = IR_0(Mi,Ma,Mb)
  IRf_1 = IR_1(Mi,Ma,Mb)
  IRf_2 = IR_2(Mi,Ma,Mb)
  IRf_00 = IR_00(MLambda,Mi,Ma,Mb)
  IRf_01 = IR_01(MLambda,Mi,Ma,Mb)
  IRf_02 = - IR_01(MLambda,Mi,Ma,Mb) - IR_12(MLambda,Mi,Ma,Mb)
  IRf_11 = IR_11(MLambda,Mi,Ma,Mb)
  IRf_22 = IR_22(MLambda,Mi,Ma,Mb)
  IRf_0up1 = IR_0up1(Mi,Ma,Mb)
  IRf_1up0 = IR_1up0(Mi,Ma,Mb)
  IRf_0up2 = IR_0up2(Mi,Ma,Mb)
  IRf_2up0 = IR_2up0(Mi,Ma,Mb)
  IRf_1up2 = IR_1up2(Mi,Ma,Mb)
  IRf_2up1 = IR_2up1(Mi,Ma,Mb)
!  IRf_22up01 = IR_22up01(Mi,Mo,Ms)


!!!!!! MARK'S DEFS:
  
  IRf_02up1 = -IRf_1 - IRf_2
  IRf_02up11 = -IRf - IRf_2up1
  IRf_12=-IRf_01 - IRf_02
!  IRf_12up0=-IRf_1 - IRf_2
!  IRf_12up00=-IRf_1up0 - IRf_2up0

!  IRf_22up00=IR_22up00(Mi,Mo,Ms)
!  IRf_22up11=IR_22up11(Mi,Mo,Ms)



! ! !!!!!!! END MARK's DEFS


AbbCLCR11 = 16._dp*Ma*Mb*Mi**2*IRf_00

AbbCLCR12 = (-16._dp*Ma**3*Mb + 16._dp*Ma*Mb**3 - 16._dp*Ma*Mb*Mi**2)*IRf_01-16._dp*Ma*Mb*IRf_0-16._dp*Ma*Mb*IRf_1

AbbCLCR13 = (-16._dp*Ma**3*Mb + 16._dp*Ma*Mb**3 + 16._dp*Ma*Mb*Mi**2)*IRf_02+16._dp*Ma*Mb*IRf_0

AbbCLCR22 = 16._dp*Ma**3*Mb*IRf_11

AbbCLCR23 = (16._dp*Ma**3*Mb + 16._dp*Ma*Mb**3 - 16._dp*Ma*Mb*Mi**2)*IRf_12+16._dp*Ma*Mb*IRf_1

AbbCLCR33 = 16._dp*Ma*Mb**3*IRf_22+16._dp*Ma*Mb*IRf_2



AbbCLCL11 = (8._dp*Ma**2*Mi**2 + 8._dp*Mb**2*Mi**2 - 8._dp*Mi**4)*IRf_00-8._dp*Mi**2*IRf_0

AbbCLCL12 = (-8._dp*Ma**4 + 8._dp*Mb**4 - 16._dp*Mb**2*Mi**2 + 8._dp*Mi**4)*IRf_01+(-8._dp*Ma**2 - 8._dp*Mb**2)*IRf_0+(-4._dp*Ma**2 - 12._dp*Mb**2 + 12._dp*Mi**2)*IRf_1+4._dp*IRf+4._dp*IRf_1up0

AbbCLCL13 = (-8._dp*Ma**4 + 8._dp*Mb**4 + 16._dp*Ma**2*Mi**2 - 8._dp*Mi**4)*IRf_02+(8._dp*Ma**2 + 8._dp*Mb**2)*IRf_0+(12._dp*Ma**2 + 4._dp*Mb**2 - 12._dp*Mi**2)*IRf_2-4._dp*IRf-4._dp*IRf_2up0

AbbCLCL22 = (8._dp*Ma**4 + 8._dp*Ma**2*Mb**2 - 8._dp*Ma**2*Mi**2)*IRf_11+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*Mi**2)*IRf_1

AbbCLCL23 = (8._dp*Ma**4 + 16._dp*Ma**2*Mb**2 + 8._dp*Mb**4 - 16._dp*Ma**2*Mi**2 - 16._dp*Mb**2*Mi**2 + 8._dp*Mi**4)*IRf_12+(4._dp*Ma**2 + 12._dp*Mb**2 - 12._dp*Mi**2)*IRf_1+4._dp*IRf_1up2+(12._dp*Ma**2 + 4._dp*Mb**2 - 12._dp*Mi**2)*IRf_2+8._dp*IRf+4._dp*IRf_2up1

AbbCLCL33 = (8._dp*Ma**2*Mb**2 + 8._dp*Mb**4 - 8._dp*Mb**2*Mi**2)*IRf_22+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*Mi**2)*IRf_2


! !!!!!!!!!!!!!!!
! ! NB Cas13=Cas11-Cas12, Cas23=Cas21-Cas22, Cas33=Cas11-2._dp*Cas12+Cas22
! ! We just compute the whole lot before passing anyway -> easier to debug
! !!!!!!!!!!!!!!!

! !!!!!
! ! Nb minus signs here because the casimirs are calculated for T(bar(a)) = - (T(a))*
! !!!!!

AbbCLCR = Cas11*AbbCLCR11 - Cas12*AbbCLCR12 + Cas13*AbbCLCR13 + Cas22*AbbCLCR22 - Cas23*AbbCLCR23 + Cas33*AbbCLCR33
AbbCLCL = Cas11*AbbCLCL11 - Cas12*AbbCLCL12 + Cas13*AbbCLCL13 + Cas22*AbbCLCL22 - Cas23*AbbCLCL23 + Cas33*AbbCLCL33


! !!!! USE SFOLD:

! AbbCLCR11 = 16._dp*Ma*Mb*Mi**2*IRf_00+8._dp*Ma*Mb*IRf_0

! AbbCLCR12 = (16._dp*Ma**3*Mb - 16._dp*Ma*Mb**3 - 16._dp*Ma*Mb*Mi**2)*IRf_01-8._dp*Ma*Mb*IRf_0-8._dp*Ma*Mb*IRf_1

! AbbCLCR13 = (-16._dp*Ma**3*Mb + 16._dp*Ma*Mb**3 - 16._dp*Ma*Mb*Mi**2)*IRf_02-8._dp*Ma*Mb*IRf_0-8._dp*Ma*Mb*IRf_2

! AbbCLCR22 = 16._dp*Ma*Mb**3*IRf_11+8._dp*Ma*Mb*IRf_1

! AbbCLCR23 = (-16._dp*Ma**3*Mb - 16._dp*Ma*Mb**3 + 16._dp*Ma*Mb*Mi**2)*IRf_12-8._dp*Ma*Mb*IRf_1-8._dp*Ma*Mb*IRf_2

! AbbCLCR33 = 16._dp*Ma**3*Mb*IRf_22+8._dp*Ma*Mb*IRf_2



! AbbCLCL11 = (8._dp*Ma**2*Mi**2 + 8._dp*Mb**2*Mi**2 - 8._dp*Mi**4)*IRf_00+(4._dp*Ma**2 + 4._dp*Mb**2 - 12._dp*Mi**2)*IRf_0-4._dp*IRf

! AbbCLCL12 = (-8._dp*Ma**4 + 8._dp*Mb**4 - 16._dp*Mb**2*Mi**2 + 8._dp*Mi**4)*IRf_01+(-4._dp*Ma**2 - 4._dp*Mb**2 - 4._dp*Mi**2)*IRf_0+(-8._dp*Mb**2 + 8._dp*Mi**2)*IRf_1-4._dp*IRf

! AbbCLCL13 = (8._dp*Ma**4 - 8._dp*Mb**4 - 16._dp*Ma**2*Mi**2 + 8._dp*Mi**4)*IRf_02+(-4._dp*Ma**2 - 4._dp*Mb**2 - 4._dp*Mi**2)*IRf_0+(-8._dp*Ma**2 + 8._dp*Mi**2)*IRf_2-4._dp*IRf

! AbbCLCL22 = (8._dp*Ma**4 + 8._dp*Ma**2*Mb**2 - 8._dp*Ma**2*Mi**2)*IRf_11+8._dp*Ma**2*IRf_1+4._dp*IRf_1up2

! AbbCLCL23 = (-8._dp*Ma**4 - 16._dp*Ma**2*Mb**2 - 8._dp*Mb**4 + 16._dp*Ma**2*Mi**2 + 16._dp*Mb**2*Mi**2 - 8._dp*Mi**4)*IRf_12+(-8._dp*Mb**2 + 8._dp*Mi**2)*IRf_1+(-8._dp*Ma**2 + 8._dp*Mi**2)*IRf_2-8._dp*IRf

! AbbCLCL33 = (8._dp*Ma**2*Mb**2 + 8._dp*Mb**4 - 8._dp*Mb**2*Mi**2)*IRf_22+8._dp*Mb**2*IRf_2+4._dp*IRf_2up1



! AbbCLCR = Cas11*AbbCLCR11 - Cas12*AbbCLCR12 + Cas13*AbbCLCR13 + Cas22*AbbCLCR22 + Cas23*AbbCLCR23 + Cas33*AbbCLCR33
! AbbCLCL = Cas11*AbbCLCL11 - Cas12*AbbCLCL12 + Cas13*AbbCLCL13 + Cas22*AbbCLCL22 + Cas23*AbbCLCL23 + Cas33*AbbCLCL33

   

 

!!!!!!!!


  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL + (CR * SCL + CL * SCR) * AbbCLCR 
  Gammatotc = Gammatotc * GC**2/ (4._dp)
!  Gammatotc = Gammatotc * GC**2/ (2._dp)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 

!  write(*,*) "--------------Hard gluon------------------"
!  write(*,*) "Mi",Mi
!  write(*,*) "Mo",Mo
!  write(*,*) "MW",MW
!  write(*,*) "CL",CL
!  write(*,*) "CR",CR
!  write(*,*) "CWP",CWP
!  write(*,*) "CLCL", (CL * SCL) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CRCR", (CR * SCR) * AbbCLCL / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "CLCR", (CR * SCL + CL * SCR) * AbbCLCR / (2._dp *MW**2 * Mi * (4._dp * Pi)**3)
!  write(*,*) "Gamma",Gammatotc
!  write(*,*) "--------------Hard gluon------------------"

  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardradiationSFF


Subroutine hardradiationSFFmzero(Mi,Mb,MLambda,GC,Cas11,Cas13,Cas33,CL,CR,Gammatotbrems,kont)
 
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CL, CR
  Real(dp), Intent(in) :: GC, Mi, Mb, MLambda,Cas11,Cas13,Cas33


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  real(dp) :: IRf_02up1,IRf_02up11,irf_12,irf_12up0,irf_12up00,irf_22up0,irf_22up00,irf_22up1,irf_22up11


  Real(dp) :: AbbCLCL11, AbbCLCL12, AbbCLCL13,AbbCLCL22,AbbCLCL23,AbbCLCL33
  real(dp) :: AbbCLCR11, AbbCLCR12, AbbCLCR13,AbbCLCR22,AbbCLCR23,AbbCLCR33
  Real(dp) :: AbbCLCL, AbbCLCR
  Complex(dp) :: Gammatotc, SCL, SCR
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardradiationFFSmzero'

  
  
  
  AbbCLCL11 = 0._dp
  AbbCLCL12 = 0._dp
  AbbCLCL13 = 0._dp
  AbbCLCL22 = 0._dp
  AbbCLCL23 = 0._dp
  AbbCLCL33 = 0._dp
  
  AbbCLCR11 = 0._dp
  AbbCLCR12 = 0._dp
  AbbCLCR13 = 0._dp
  AbbCLCR22 = 0._dp
  AbbCLCR23 = 0._dp
  AbbCLCR33 = 0._dp
  AbbCLCL = 0._dp
  AbbCLCR = 0._dp
  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCL = Conjg(CL)
  SCR = Conjg(CR)
 

  if(abs(mb) .eq. 0._dp) then

     write(*,*) "Unsupported decay into two massless states!"
     kont=-11
     return
     
  else

  
!  IRf = IRsafe(Mi,Mb)
  IRf_0 = IR_0safe(Mi,Mb)
  
  IRf_2 = IR_2safe(Mi,Mb)
  IRf_00 = IR_00safe(MLambda,Mi,Mb)
  
  IRf_02 = IR_02safe(MLambda,Mi,Mb)

  IRf_22 = IR_22safe(MLambda,Mi,Mb)
  IRf_2up1 = IR_2up1safe(Mi,Mb)

  end if
  

AbbCLCL11 = (8._dp*Mb**2*Mi**2 - 8._dp*Mi**4)*IRf_00-8._dp*Mi**2*IRf_0

AbbCLCL13 = (8._dp*Mb**4 - 8._dp*Mi**4)*IRf_02+( 8._dp*Mb**2)*IRf_0+( 4._dp*Mb**2 - 12._dp*Mi**2)*IRf_2 +4._dp*IRf_2up1  !-4._dp*IRf-4._dp*IRf_2up0

AbbCLCL33 = (8._dp*Mb**4 - 8._dp*Mb**2*Mi**2)*IRf_22+( 4._dp*Mb**2 + 4._dp*Mi**2)*IRf_2


AbbCLCL = Cas11*AbbCLCL11 + Cas13*AbbCLCL13 + Cas33*AbbCLCL33




!!!!!!!!


  Gammatotc = (CL * SCL + CR * SCR) * AbbCLCL 

  Gammatotc = Gammatotc * GC**2/ (2._dp)
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 


  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardradiationSFFmzero
 

Subroutine hardradiationSSS(Mi,Ma,Mb,MLambda,GC,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33,CS,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard gluon or photon emission
 !for the process S (mi) -> S (ma) + S(mb)
 !------------------------------------------------------------
 !Involved particles:
 !- Scalar S_in with mass Mi 
 !- Scalar a out with mass Ma 
 !- Scalar b out with mass Mb
 !- Photon or gluon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !-CS bar(S_in) S_a S_b + h.c.
 ! GC is the gauge coupling
 ! Casij is the group factor for the combination where we attach 
 ! the gauge boson on leg i of the diagram to leg j of the conjugate
 ! Leg 1 -> Scalar in
 ! Leg 2 -> S_a out
 ! Leg 3 -> S_b out
 !------------------------------------------------------------
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !adapted from corrections written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CS
  Real(dp), Intent(in) :: GC, Mi, Ma, Mb, MLambda,Cas11,Cas12,Cas13,Cas22,Cas23,Cas33


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  real(dp) :: IRf_02up1,IRf_02up11,irf_12,irf_12up0,irf_12up00,irf_22up0,irf_22up00,irf_22up1,irf_22up11


  Real(dp) :: Abb11, Abb12, Abb13,Abb22,Abb23,Abb33
  Real(dp) :: Abb
  Complex(dp) :: Gammatotc, SCS
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardradiationSSS'

!   If ((Abs(Mi)-Abs(Ma)-Abs(Mb)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard gluon emission!"
!   End If

  Abb11 = 0._dp
  Abb12 = 0._dp
  Abb13 = 0._dp
  Abb22 = 0._dp
  Abb23 = 0._dp
  Abb33 = 0._dp
  
  Abb = 0._dp

  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCS = Conjg(CS)


!  IRf = IRwithout(Mi,Ma,Mb)
  IRf_0 = IR_0(Mi,Ma,Mb)
  IRf_1 = IR_1(Mi,Ma,Mb)
  IRf_2 = IR_2(Mi,Ma,Mb)
  IRf_00 = IR_00(MLambda,Mi,Ma,Mb)
  IRf_01 = IR_01(MLambda,Mi,Ma,Mb)
  IRf_02 = - IR_01(MLambda,Mi,Ma,Mb) - IR_12(MLambda,Mi,Ma,Mb)
  IRf_11 = IR_11(MLambda,Mi,Ma,Mb)
  IRf_22 = IR_22(MLambda,Mi,Ma,Mb)
  ! IRf_0up1 = IR_0up1(Mi,Ma,Mb)
  ! IRf_1up0 = IR_1up0(Mi,Ma,Mb)
  ! IRf_0up2 = IR_0up2(Mi,Ma,Mb)
  ! IRf_2up0 = IR_2up0(Mi,Ma,Mb)
  ! IRf_1up2 = IR_1up2(Mi,Ma,Mb)
  ! IRf_2up1 = IR_2up1(Mi,Ma,Mb)
!  IRf_22up01 = IR_22up01(Mi,Mo,Ms)


!!!!!! MARK'S DEFS:
  
!  IRf_02up1 = -IRf_1 - IRf_2
!  IRf_02up11 = -IRf - IRf_2up1
  IRf_12=-IRf_01 - IRf_02
!  IRf_12up0=-IRf_1 - IRf_2
!  IRf_12up00=-IRf_1up0 - IRf_2up0

!  IRf_22up00=IR_22up00(Mi,Mo,Ms)
!  IRf_22up11=IR_22up11(Mi,Mo,Ms)



!!!!!!! END MARK's DEFS

! Abb11 = -8._dp*Mi**2*IRf_00-4._dp*IRf_0

! Abb12 = (-4._dp*Mi**2 - 4._dp*ma**2 + 4._dp*mb**2)*IRf_01-2._dp*IRf_0-2._dp*IRf_1

! Abb13 = (-4._dp*Mi**2 + 4._dp*ma**2 - 4._dp*mb**2)*IRf_02-2._dp*IRf_0-2._dp*IRf_2

! Abb22 = -8._dp*ma**2*IRf_11-4._dp*IRf_1

! Abb23 = (-4._dp*Mi**2 + 4._dp*ma**2 + 4._dp*mb**2)*IRf_12+2._dp*IRf_2+2._dp*IRf_1

  ! Abb33 = -8._dp*mb**2*IRf_22-4._dp*IRf_2

Abb11 = -8._dp*Mi**2*IRf_00-4._dp*IRf_0

Abb12 = (-8._dp*Mi**2 - 8._dp*ma**2 + 8._dp*mb**2)*IRf_01-4._dp*IRf_0-4._dp*IRf_1

Abb13 = (-8._dp*Mi**2 + 8._dp*ma**2 - 8._dp*mb**2)*IRf_02-4._dp*IRf_0-4._dp*IRf_2

Abb22 = -8._dp*ma**2*IRf_11-4._dp*IRf_1

Abb23 = (-8._dp*Mi**2 + 8._dp*ma**2 + 8._dp*mb**2)*IRf_12+4._dp*IRf_1+4._dp*IRf_2

Abb33 = -8._dp*mb**2*IRf_22-4._dp*IRf_2

  


!!!!!!!!!!!!!!!
! NB Cas13=Cas11-Cas12, Cas23=Cas21-Cas22, Cas33=Cas11-2._dp*Cas12+Cas22
! We just compute the whole lot before passing anyway -> easier to debug
!!!!!!!!!!!!!!!

!!!!!
! Nb no minus signs here because Sfold used S -> S_1 S_2
!!!!!

Abb = Cas11*Abb11 + Cas12*Abb12 + Cas13*Abb13 + Cas22*Abb22 + Cas23*Abb23 + Cas33*Abb33




!!!!!!!!


  Gammatotc = CS * SCS * Abb

  Gammatotc = Gammatotc * GC**2
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 


  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardradiationSSS



Subroutine hardradiationSSV(Ma,Mb,MV,MLambda,GC,Qa,Qb,QV,CS,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard gluon or photon emission
 !for the process S (mi) -> S (ma) + V(MV)
 !------------------------------------------------------------
 !Involved particles:
 !- Scalar S_a with mass Ma 
 !- Scalar S_b out with mass Mb 
 !- Vector V out with mass MV
 !- Photon or gluon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !-CS 
 ! GC is the gauge coupling
 ! 
 ! Leg 1 -> S_a in
 ! Leg 2 -> S_b out
 ! Leg 3 -> V out
 !
 !------------------------------------------------------------
 ! Calculation done in UNITARY GAUGE as in SFOLD  
 !------------------------------------------------------------
 !Written by M. Goodsell July 2016
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !adapted from corrections written by Stefan Liebler, July 2010
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CS
  Real(dp), Intent(in) :: GC, Ma, Mb, MV, MLambda,Qa,Qb,QV


  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_0up1
  Real(dp) :: IRf_1up0, IRf_0up2, IRf_2up0, IRf_1up2, IRf_2up1, IRf_22up01

  real(dp) :: IRf_02up1,IRf_02up11,irf_12,irf_12up0,irf_12up00,irf_22up0,irf_22up00,irf_22up1,irf_22up11


  Real(dp) :: Abb11, Abb12, Abb13,Abb22,Abb23,Abb33,Abb14,Abb24,Abb34,Abb44
  Real(dp) :: Abb, MV2
  Complex(dp) :: Gammatotc, SCS
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardradiationSSS'

!   If ((Abs(Ma)-Abs(Mb)-Abs(MV)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by Hard gluon emission!"
!   End If

  MV2=MV**2
  
  Abb11 = 0._dp
  Abb12 = 0._dp
  Abb13 = 0._dp
  Abb14 = 0._dp
  Abb22 = 0._dp
  Abb23 = 0._dp
  Abb24 = 0._dp
  Abb33 = 0._dp
  Abb34 = 0._dp
  Abb44 = 0._dp
  
  
  Abb = 0._dp

  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCS = Conjg(CS)


!  IRf = IRwithout(Mi,Ma,Mb)
  IRf_0 = IR_0(Ma,Mb,MV)
  IRf_1 = IR_1(Ma,Mb,MV)
  IRf_2 = IR_2(Ma,Mb,MV)
  IRf_00 = IR_00(MLambda,Ma,Mb,MV)
  IRf_01 = IR_01(MLambda,Ma,Mb,MV)
  IRf_02 = - IR_01(MLambda,Ma,Mb,MV) - IR_12(MLambda,Ma,Mb,MV)
  IRf_11 = IR_11(MLambda,Ma,Mb,MV)
  IRf_22 = IR_22(MLambda,Ma,Mb,MV)
   IRf_0up1 = IR_0up1(Ma,Mb,MV)
  IRf_1up0 = IR_1up0(Ma,Mb,MV)
  IRf_0up2 = IR_0up2(Ma,Mb,MV)
  IRf_2up0 = IR_2up0(Ma,Mb,MV)
  IRf_1up2 = IR_1up2(Ma,Mb,MV)
  IRf_2up1 = IR_2up1(Ma,Mb,MV)
!  IRf_22up01 = IR_22up01(Mi,Mo,Ms)


!!!!!! MARK'S DEFS:
  
!  IRf_02up1 = -IRf_1 - IRf_2
!  IRf_02up11 = -IRf - IRf_2up1
  IRf_12=-IRf_01 - IRf_02
!  IRf_12up0=-IRf_1 - IRf_2
!  IRf_12up00=-IRf_1up0 - IRf_2up0

!  IRf_22up00=IR_22up00(Mi,Mo,Ms)
  IRf_22up11=IR_22up11(Ma,Mb,MV)




!!!!!!! END MARK's DEFS

! Abb11 = (-4._dp*Ma**6 + 8._dp*Ma**4*Mb**2 - 4._dp*Ma**2*Mb**4 + 8._dp*Ma**4*MV2 + 8._dp*Ma**2*Mb**2*MV2 - 4._dp*Ma**2*MV2**2)*IRf_00+(-8._dp*Ma**4 + 8._dp*Ma**2*Mb**2 + 8._dp*Ma**2*MV2)*IRf_0-4._dp*Ma**2*IRf

! Abb12 = (-4._dp*Ma**6 + 4._dp*Ma**4*Mb**2 + 4._dp*Ma**2*Mb**4 - 4._dp*Mb**6 + 12._dp*Ma**4*MV2 + 8._dp*Ma**2*Mb**2*MV2 + 12._dp*Mb**4*MV2 - 12._dp*Ma**2*MV2**2 - 12._dp*Mb**2*MV2**2 + 4._dp*MV2**3)*IRf_01+(8._dp*Ma**2*Mb**2 - 8._dp*Mb**4 + 8._dp*Ma**2*MV2 + 16._dp*Mb**2*MV2 - 8._dp*MV2**2)*IRf_0+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*MV2)*IRf_0up1+(-8._dp*Ma**4 + 8._dp*Ma**2*Mb**2 + 16._dp*Ma**2*MV2 + 8._dp*Mb**2*MV2 - 8._dp*MV2**2)*IRf_1+(4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf_1up0

! Abb14 = (4._dp*Ma**4 - 8._dp*Ma**2*Mb**2 + 4._dp*Mb**4 - 8._dp*Ma**2*MV2 - 8._dp*Mb**2*MV2 + 4._dp*MV2**2)*IRf_0+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*MV2)*IRf_0up2+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*MV2)*IRf

! Abb22 = (-4._dp*Ma**4*Mb**2 + 8._dp*Ma**2*Mb**4 - 4._dp*Mb**6 + 8._dp*Ma**2*Mb**2*MV2 + 8._dp*Mb**4*MV2 - 4._dp*Mb**2*MV2**2)*IRf_11+(8._dp*Ma**2*Mb**2 - 8._dp*Mb**4 + 8._dp*Mb**2*MV2)*IRf_1-4._dp*Mb**2*IRf

! Abb24 = (4._dp*Ma**4 - 8._dp*Ma**2*Mb**2 + 4._dp*Mb**4 - 8._dp*Ma**2*MV2 - 8._dp*Mb**2*MV2 + 4._dp*MV2**2)*IRf_1+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf_1up2+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf

  ! Abb44 = 4._dp*MV2*IRf

Abb11 = (-4._dp*Ma**6 + 8._dp*Ma**4*Mb**2 - 4._dp*Ma**2*Mb**4 + 8._dp*Ma**4*MV2 + 8._dp*Ma**2*Mb**2*MV2 - 4._dp*Ma**2*MV2**2)*IRf_00+(-8._dp*Ma**4 + 8._dp*Ma**2*Mb**2 + 8._dp*Ma**2*MV2)*IRf_0-4._dp*Ma**2*IRf

Abb12 = (-4._dp*Ma**6 + 4._dp*Ma**4*Mb**2 + 4._dp*Ma**2*Mb**4 - 4._dp*Mb**6 + 12._dp*Ma**4*MV2 + 8._dp*Ma**2*Mb**2*MV2 + 12._dp*Mb**4*MV2 - 12._dp*Ma**2*MV2**2 - 12._dp*Mb**2*MV2**2 + 4._dp*MV2**3)*IRf_01+(8._dp*Ma**2*Mb**2 - 8._dp*Mb**4 + 8._dp*Ma**2*MV2 + 16._dp*Mb**2*MV2 - 8._dp*MV2**2)*IRf_0+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*MV2)*IRf_0up1+(-8._dp*Ma**4 + 8._dp*Ma**2*Mb**2 + 16._dp*Ma**2*MV2 + 8._dp*Mb**2*MV2 - 8._dp*MV2**2)*IRf_1+(4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf_1up0

Abb14 = (4._dp*Ma**4 - 8._dp*Ma**2*Mb**2 + 4._dp*Mb**4 - 8._dp*Ma**2*MV2 - 8._dp*Mb**2*MV2 + 4._dp*MV2**2)*IRf_0+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*MV2)*IRf_0up2+(4._dp*Ma**2 - 4._dp*Mb**2 + 4._dp*MV2)*IRf

Abb22 = (-4._dp*Ma**4*Mb**2 + 8._dp*Ma**2*Mb**4 - 4._dp*Mb**6 + 8._dp*Ma**2*Mb**2*MV2 + 8._dp*Mb**4*MV2 - 4._dp*Mb**2*MV2**2)*IRf_11+(8._dp*Ma**2*Mb**2 - 8._dp*Mb**4 + 8._dp*Mb**2*MV2)*IRf_1-4._dp*Mb**2*IRf

Abb24 = (4._dp*Ma**4 - 8._dp*Ma**2*Mb**2 + 4._dp*Mb**4 - 8._dp*Ma**2*MV2 - 8._dp*Mb**2*MV2 + 4._dp*MV2**2)*IRf_1+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf_1up2+(-4._dp*Ma**2 + 4._dp*Mb**2 + 4._dp*MV2)*IRf

Abb44 = 4._dp*MV2*IRf

If(abs(QV) .gt. 0._dp) then

! Abb13 = (-2._dp*Ma**6 + 6._dp*Ma**4*Mb**2 - 6._dp*Ma**2*Mb**4 + 2._dp*Mb**6 + 8._dp*Ma**2*Mb**2*MV2 - 8._dp*Mb**4*MV2 + 6._dp*Ma**2*MV2**2 + 10._dp*Mb**2*MV2**2 - 4._dp*MV2**3)*IRf_02+(4._dp*Ma**4 - 4._dp*Mb**4 + 6._dp*Ma**2*MV2 + 10._dp*Mb**2*MV2 - 6._dp*MV2**2)*IRf_0+(-2._dp*Ma**2 + 2._dp*Mb**2 - 2._dp*MV2)*IRf_0up2+(-2._dp*Ma**4 + 4._dp*Ma**2*Mb**2 - 2._dp*Mb**4 + 2._dp*Ma**2*MV2 - 2._dp*Mb**2*MV2 + 4._dp*MV2**2)*IRf_2+(4._dp*Ma**2 + 4._dp*Mb**2 + 2._dp*MV2)*IRf

! Abb23 = (-2._dp*Ma**6 + 6._dp*Ma**4*Mb**2 - 6._dp*Ma**2*Mb**4 + 2._dp*Mb**6 + 8._dp*Ma**4*MV2 - 8._dp*Ma**2*Mb**2*MV2 - 10._dp*Ma**2*MV2**2 - 6._dp*Mb**2*MV2**2 + 4._dp*MV2**3)*IRf_12+(4._dp*Ma**4 - 4._dp*Mb**4 - 10._dp*Ma**2*MV2 - 6._dp*Mb**2*MV2 + 6._dp*MV2**2)*IRf_1+(-2._dp*Ma**2 + 2._dp*Mb**2 + 2._dp*MV2)*IRf_1up2+(2._dp*Ma**4 - 4._dp*Ma**2*Mb**2 + 2._dp*Mb**4 + 2._dp*Ma**2*MV2 - 2._dp*Mb**2*MV2 - 4._dp*MV2**2)*IRf_2+(-4._dp*Ma**2 - 4._dp*Mb**2 - 2._dp*MV2)*IRf

! Abb33 = (-3._dp*Ma**4*MV2 + 6._dp*Ma**2*Mb**2*MV2 - 3._dp*Mb**4*MV2 + 8._dp*Ma**2*MV2**2 + 8._dp*Mb**2*MV2**2 - 4._dp*MV2**3)*IRf_22+(Ma**4 - 2._dp*Ma**2*Mb**2 + Mb**4 + 4._dp*Ma**2*MV2 + 12._dp*Mb**2*MV2 - 8._dp*MV2**2)*IRf_2+(-2._dp*Ma**2 - 2._dp*Mb**2 - MV2)*IRf+(-8._dp*Ma**2*MV2 + 8._dp*Mb**2*MV2)*IRf_22up1+8._dp*MV2*IRf_2up1+8._dp*MV2*IRf_22up11

! Abb34 = (4._dp*Ma**2*MV2 - 4._dp*Mb**2*MV2)*IRf_2-8._dp*MV2*IRf-16._dp*MV2*IRf_2up1

   Abb13 = (-4._dp*Ma**6 + 12._dp*Ma**4*Mb**2 - 12._dp*Ma**2*Mb**4 + 4._dp*Mb**6 + 4._dp*Ma**4*MV2 + 8._dp*Ma**2*Mb**2*MV2 - 12._dp*Mb**4*MV2 + 4._dp*Ma**2*MV2**2 + 12._dp*Mb**2*MV2**2 - 4._dp*MV2**3)*IRf_02+(2._dp*Ma**4 + 4._dp*Ma**2*Mb**2 - 6._dp*Mb**4 + 4._dp*Ma**2*MV2 + 12._dp*Mb**2*MV2 - 6._dp*MV2**2)*IRf_0+(-2._dp*Ma**2 + 2._dp*Mb**2 - 2._dp*MV2)*IRf_0up2+(-4._dp*Ma**4 + 8._dp*Ma**2*Mb**2 - 4._dp*Mb**4 + 4._dp*MV2**2)*IRf_2+(2._dp*Ma**2 + 6._dp*Mb**2 + 2._dp*MV2)*IRf

   Abb23 = (-4._dp*Ma**6 + 12._dp*Ma**4*Mb**2 - 12._dp*Ma**2*Mb**4 + 4._dp*Mb**6 + 12._dp*Ma**4*MV2 - 8._dp*Ma**2*Mb**2*MV2 - 4._dp*Mb**4*MV2 - 12._dp*Ma**2*MV2**2 - 4._dp*Mb**2*MV2**2 + 4._dp*MV2**3)*IRf_12+(6._dp*Ma**4 - 4._dp*Ma**2*Mb**2 - 2._dp*Mb**4 - 12._dp*Ma**2*MV2 - 4._dp*Mb**2*MV2 + 6._dp*MV2**2)*IRf_1+(-2._dp*Ma**2 + 2._dp*Mb**2 + 2._dp*MV2)*IRf_1up2+(4._dp*Ma**4 - 8._dp*Ma**2*Mb**2 + 4._dp*Mb**4 - 4._dp*MV2**2)*IRf_2+(-6._dp*Ma**2 - 2._dp*Mb**2 - 2._dp*MV2)*IRf

   Abb33 = (-4._dp*Ma**4*MV2 + 8._dp*Ma**2*Mb**2*MV2 - 4._dp*Mb**4*MV2 + 8._dp*Ma**2*MV2**2 + 8._dp*Mb**2*MV2**2 - 4._dp*MV2**3)*IRf_22+(8._dp*Ma**2*MV2 + 8._dp*Mb**2*MV2 - 8._dp*MV2**2)*IRf_2+(-2._dp*Ma**2 - 2._dp*Mb**2 - MV2)*IRf+8._dp*MV2*IRf_2up1+8._dp*MV2*IRf_22up11

   Abb34 = (4._dp*Ma**2 - 4._dp*Mb**2 - 8._dp*MV2)*IRf-16._dp*MV2*IRf_2up1



   
end if


Abb=Qa**2*Abb11+Qa*Qb*Abb12+Qa*QV*Abb13+Qa*(Qa+Qb)*0.5_dp*Abb14
Abb=Abb+ Qb**2*Abb22+Qb*QV*Abb23+Qb*(Qa+Qb)*0.5_dp*Abb24
Abb=Abb+QV**2*Abb33+QV*(Qa+Qb)*0.5_dp*Abb34+(Qa+Qb)**2*0.25_dp*Abb44


!!!!!!!!


  Gammatotc = CS * SCS * Abb

  Gammatotc = Gammatotc * GC**2 /MV2
  Gammatotc = Gammatotc / (Ma * (4._dp * Pi)**3) 


  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardradiationSSV


 
Subroutine hardphotonSVV(Mi,M1,M2,MLambda,GC,Qi,Q1,Q2,CS,Gammatotbrems,kont)
 !------------------------------------------------------------
 !calculates the real corrections due to hard photon emission
 !for the process S (Mi) -> V1 (M1) + V2 (M2)
 !------------------------------------------------------------
 !Involved particles:
 !- Scalar S in with mass Mi, charge Qi = Q1+Q2
 !- Vector V1 out with mass M1, charge Q1
 !- Vector V2 out with mass M2, charge Q2
 !- Photon with Mass MLambda
 !------------------------------------------------------------
 !Necessary couplings:
 !-CS 
 !-GC is the gauge coupling = EL
 ! 
 ! Leg 1 -> S in
 ! Leg 2 -> V1 out
 ! Leg 3 -> V2 out
 !
 !------------------------------------------------------------
 !Written by S. Liebler January 2017
 !reproduces H->WW result of HFOLD for Qi=0,M1=M2,Q1=-Q2
 !needs Bremsstrahlung integrals IR_{ij}up{st}
 !------------------------------------------------------------
 Implicit None
  Integer, Intent(inout) :: kont
  Real(dp), Intent(out) :: Gammatotbrems
  Complex(dp), Intent(in) :: CS
  Real(dp), Intent(in) :: GC,Mi,M1,M2,MLambda,Qi,Q1,Q2

  Real(dp) :: IRf, IRf_0, IRf_1, IRf_2, IRf_00, IRf_01, IRf_02, IRf_11, IRf_22, IRf_12
  Real(dp) :: IRf_1up0, IRf_2up0, IRf_1up2, IRf_2up1, IRf_11up00, IRf_22up11

  Real(dp) :: Abbii,Abb1i,Abb2i,Abb12,Abb11,Abb22
  Real(dp) :: Abb
  Complex(dp) :: Gammatotc, SCS
  
  Iname = Iname + 1
  NameOfUnit(Iname) = 'hardphotonSVV'

!   If ((Abs(Mi)-Abs(M1)-Abs(M2)).LE.(0._dp)) Then
!    write(*,*) "Please have a look if the decay you are considering is kinematically"
!    write(*,*) "allowed. Error message by hard photon emission in S->VV!"
!   End If

  If ((Abs(Qi-Q1-Q2)).gt.(0.000001_dp)) Then
   write(*,*) "Please choose proper charge assignments in S->VV!"
  End If
  
  Abbii = 0._dp
  Abb1i = 0._dp
  Abb2i = 0._dp
  Abb12 = 0._dp
  Abb11 = 0._dp
  Abb22 = 0._dp
  
  Abb = 0._dp

  Gammatotbrems = 0._dp
  Gammatotc = ZeroC

  SCS = Conjg(CS)

  IRf = IRwithout(Mi,M1,M2)
  IRf_0 = IR_0(Mi,M1,M2)
  IRf_1 = IR_1(Mi,M1,M2)
  IRf_2 = IR_2(Mi,M1,M2)
  IRf_00 = IR_00(MLambda,Mi,M1,M2)
  IRf_01 = IR_01(MLambda,Mi,M1,M2)
  IRf_02 = - IR_01(MLambda,Mi,M1,M2) - IR_12(MLambda,Mi,M1,M2)
  IRf_11 = IR_11(MLambda,Mi,M1,M2)
  IRf_22 = IR_22(MLambda,Mi,M1,M2)
  IRf_1up0 = IR_1up0(Mi,M1,M2)
  IRf_2up0 = IR_2up0(Mi,M1,M2)
  IRf_1up2 = IR_1up2(Mi,M1,M2)
  IRf_2up1 = IR_2up1(Mi,M1,M2)
  IRf_11up00 = IR_11up00(Mi,M1,M2)
  IRf_22up11 = IR_22up11(Mi,M1,M2)

  IRf_12 = -IRf_01 - IRf_02

  Abb1i = -4._dp*IRf*M1**2 + 2._dp*IRf_1up0*M1**2 - 2._dp*IRf_01*M1**6 &
   & - 4._dp*IRf*M2**2 + 2._dp*IRf_1up0*M2**2 - 20._dp*IRf_1*M1**2*M2**2 &
   & - 18._dp*IRf_01*M1**4*M2**2 - 4._dp*IRf_1*M2**4 + 18._dp*IRf_01*M1**2*M2**4 &
   & + 2._dp*IRf_01*M2**6 + 8._dp*IRf*Mi**2 - 2._dp*IRf_1up0*Mi**2 &
   & - 4._dp*IRf_0*M1**2*Mi**2 + 4._dp*IRf_1*M1**2*Mi**2 + 2._dp*IRf_01*M1**4*Mi**2 &
   & - 4._dp*IRf_0*M2**2*Mi**2 + 8._dp*IRf_1*M2**2*Mi**2 - 20._dp*IRf_01*M1**2*M2**2*Mi**2 &
   & - 6._dp*IRf_01*M2**4*Mi**2 + 4._dp*IRf_0*Mi**4 - 4._dp*IRf_1*Mi**4 &
   & + 2._dp*IRf_01*M1**2*Mi**4 + 6._dp*IRf_01*M2**2*Mi**4 - 2._dp*IRf_01*Mi**6

  Abb2i = -4._dp*IRf*M1**2 + 2._dp*IRf_2up0*M1**2 - 4._dp*IRf_2*M1**4 &
   & + 2._dp*IRf_02*M1**6 - 4._dp*IRf*M2**2 + 2._dp*IRf_2up0*M2**2 &
   & - 20._dp*IRf_2*M1**2*M2**2 + 18._dp*IRf_02*M1**4*M2**2 &
   & - 18._dp*IRf_02*M1**2*M2**4 - 2._dp*IRf_02*M2**6 + 8._dp*IRf*Mi**2 &
   & - 2._dp*IRf_2up0*Mi**2 - 4._dp*IRf_0*M1**2*Mi**2 + 8._dp*IRf_2*M1**2*Mi**2 &
   & - 6._dp*IRf_02*M1**4*Mi**2 - 4._dp*IRf_0*M2**2*Mi**2 + 4._dp*IRf_2*M2**2*Mi**2 &
   & - 20._dp*IRf_02*M1**2*M2**2*Mi**2 + 2._dp*IRf_02*M2**4*Mi**2 &
   & + 4._dp*IRf_0*Mi**4 - 4._dp*IRf_2*Mi**4 + 6._dp*IRf_02*M1**2*Mi**4 &
   & + 2._dp*IRf_02*M2**2*Mi**4 - 2._dp*IRf_02*Mi**6

  Abb12 = 4._dp*IRf*M1**2 - 6._dp*IRf_1up2*M1**2 + 2._dp*IRf_2up1*M1**2 &
   & + 4._dp*IRf_2*M1**4 + 2._dp*IRf_12*M1**6 + 4._dp*IRf*M2**2 &
   & + 2._dp*IRf_1up2*M2**2 - 6._dp*IRf_2up1*M2**2 + 20._dp*IRf_1*M1**2*M2**2 &
   & + 20._dp*IRf_2*M1**2*M2**2 + 22._dp*IRf_12*M1**4*M2**2 + 4._dp*IRf_1*M2**4 &
   & + 22._dp*IRf_12*M1**2*M2**4 + 2._dp*IRf_12*M2**6 - 8._dp*IRf*Mi**2 &
   & - 2._dp*IRf_1up2*Mi**2 - 2._dp*IRf_2up1*Mi**2 - 4._dp*IRf_1*M1**2*Mi**2 &
   & - 8._dp*IRf_2*M1**2*Mi**2 - 6._dp*IRf_12*M1**4*Mi**2 - 8._dp*IRf_1*M2**2*Mi**2 &
   & - 4._dp*IRf_2*M2**2*Mi**2 -  28._dp*IRf_12*M1**2*M2**2*Mi**2 &
   & - 6._dp*IRf_12*M2**4*Mi**2 + 4._dp*IRf_1*Mi**4 + 4._dp*IRf_2*Mi**4 &
   & + 6._dp*IRf_12*M1**2*Mi**4 + 6._dp*IRf_12*M2**2*Mi**4 - 2._dp*IRf_12*Mi**6

  Abbii = 4._dp*IRf*M1**2 - 2._dp*IRf_0*M1**4 + 4._dp*IRf*M2**2 &
   & - 20._dp*IRf_0*M1**2*M2**2 - 2._dp*IRf_0*M2**4 - 6._dp*IRf*Mi**2 &
   & + 8._dp*IRf_0*M1**2*Mi**2 - 2._dp*IRf_00*M1**4*Mi**2 + 8._dp*IRf_0*M2**2*Mi**2 &
   & - 20._dp*IRf_00*M1**2*M2**2*Mi**2 - 2._dp*IRf_00*M2**4*Mi**2 &
   & - 6._dp*IRf_0*Mi**4 + 4._dp*IRf_00*M1**2*Mi**4 &
   & + 4._dp*IRf_00*M2**2*Mi**4 - 2._dp*IRf_00*Mi**6

  Abb11 = 4._dp*IRf*M1**2 + 4._dp*IRf_11up00*M1**2 + 6._dp*IRf_1up0*M1**2 &
   & - 2._dp*IRf_1*M1**4 - 2._dp*IRf_11*M1**6 + 4._dp*IRf*M2**2 - 2._dp*IRf_1up0*M2**2 &
   & - 20._dp*IRf_11*M1**4*M2**2 + 2._dp*IRf_1*M2**4 - 2._dp*IRf_11*M1**2*M2**4 &
   & - 2._dp*IRf*Mi**2 + 2._dp*IRf_1up0*Mi**2 + 4._dp*IRf_11*M1**4*Mi**2 &
   & - 4._dp*IRf_1*M2**2*Mi**2 + 4._dp*IRf_11*M1**2*M2**2*Mi**2 + 2._dp*IRf_1*Mi**4 &
   & - 2._dp*IRf_11*M1**2*Mi**4

  Abb22 = 6._dp*IRf*M1**2 + 2._dp*IRf_2up1*M1**2 + 2._dp*IRf_2*M1**4 + 2._dp*IRf*M2**2 &
   & + 4._dp*IRf_22up11*M2**2 + 2._dp*IRf_2up1*M2**2 - 2._dp*IRf_22*M1**4*M2**2 &
   & - 2._dp*IRf_2*M2**4 - 20._dp*IRf_22*M1**2*M2**4 - 2._dp*IRf_22*M2**6 &
   & - 4._dp*IRf*Mi**2 - 2._dp*IRf_2up1*Mi**2 - 4._dp*IRf_2*M1**2*Mi**2 &
   & + 4._dp*IRf_22*M1**2*M2**2*Mi**2 + 4._dp*IRf_22*M2**4*Mi**2 &
   & + 2._dp*IRf_2*Mi**4 - 2._dp*IRf_22*M2**2*Mi**4

  Abb = Qi**2*Abbii + Q1**2*Abb11 + Q2**2*Abb22
  Abb = Abb + Qi*Q1*Abb1i + Qi*Q2*Abb2i + Q1*Q2*Abb12 

  Gammatotc = CS * SCS * Abb

  Gammatotc = Gammatotc * GC**2 /2._dp/M1**2/M2**2
  Gammatotc = Gammatotc / (Mi * (4._dp * Pi)**3) 

  Gammatotbrems = Real(Gammatotc,dp)

  Iname = Iname - 1

 End Subroutine hardphotonSVV


 

End Module Bremsstrahlung

