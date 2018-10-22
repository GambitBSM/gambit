Module AddLoopFunctions
Use Control
!Use Mathematics, Only: Li2, CLi2, Delt
!Use LoopFunctions
Use LoopFunctions, Only: DB0, A0, B0, B1, B00, B11, Cget, Log1minusX

! private variables
Real(dp), Private :: mudim2 = 0._dp, divergence = 0._dp
Real(dp), Private :: xloss = 0.125_dp
Integer, Private :: divonly = 0 !when set to 1, only UV divergent parts are taken
                                !not for special C routines
Real(dp), Private :: controlmdiff = 1.0e-15_dp !controls the mass difference
                                               !when comparing two masses
Real(dp) :: CCut = 10.e-15_dp

! written by Stefan Liebler, Feb.-April 2010

Contains

!definition of A00, B001, B111

 Complex(dp) Function A00(xm)
 Implicit None
  Real(dp), Intent(in) :: xm

  If (divonly.Eq.1) Then
   A00 = 0.25_dp * divergence * xm * xm
   Return 
  End If

  A00 = (1._dp/4._dp)*A0(xm)*xm + (1._dp/8._dp)*xm*xm

 End Function A00

 Complex(dp) Function B001(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Real(dp) :: cf1
  Complex(dp) :: ca0i(2)

  If (divonly.Eq.1) Then
   B001 = divergence * (-2._dp * xm1 - 4._dp * xm2 + xp) / 24._dp
   Return 
  End If

  cf1 = xp - xm2 + xm1

  ca0i(1) = A0(xm1)
  ca0i(2) = A0(xm2)

  B001 = 2._dp * xm1 * B1(xp,xm1,xm2) &
    & - ca0i(2) + cf1 * B11(xp,xm1,xm2) & 
    & - (1._dp)/(6._dp) &
    & * (2._dp * xm1 + 4._dp * xm2 - xp)

  B001 = (1._dp/8._dp) * B001

 End Function B001

 Complex(dp) Function B111(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Real(dp) :: cf1
  Complex(dp) :: ca0i(2)

  If (divonly.Eq.1) Then
   B111 = - 0.25_dp * divergence
   Return 
  End If

  cf1 = xp - xm2 + xm1

  ca0i(1) = A0(xm1)
  ca0i(2) = A0(xm2)

  B111 = ca0i(2) + 3._dp * cf1 * B11(xp,xm1,xm2) &
    & + 2._dp * xm1 * B1(xp,xm1,xm2) &
    & - (1._dp)/(6._dp) &
    & * (2._dp * xm1 + 4._dp * xm2 - xp)

  B111 = - (1._dp/4._dp) * B111
  B111 = B111/xp

 End Function B111

!derivative of B0
 Complex(dp) Function DerB0(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2

  If (divonly.Eq.1) Then
   DerB0 = ZeroC
   Return 
  End If

  DerB0 = DB0(xp,xm1,xm2)

 End Function DerB0


!derivatives of other loop functions
Complex(dp) Function DerA0(m1)
Implicit None
Real(dp), Intent(in) :: m1
DerA0 = 0._dp
End Function DerA0 

Complex(dp) Function DerB22(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerB22 = DerB00(p2,m12,m22)
End Function DerB22


Complex(dp) Function DerHloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerHloop =   4._dp * DerB00(p2,m12,m22) + DerGLoop(p2,m12,m22) 
End Function DerHloop 

Complex(dp) Function DerGloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerGloop =  (p2 - m12 - m22) * DerB0(p2,m12,m22) + B0(p2,m12,m22)
End Function DerGloop 

Complex(dp) Function DerFloopRXi(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerFloopRXi = -(2._dp*p2 + 2._dp*m12-m22)*DerB0(p2,m12,m22)-2._dp*DerB0(p2,m12,m22)
End Function DerFloopRXi

Complex(dp) Function DerVSSloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVSSloop = -4._dp*DerB00(p2,m12,m22) 
End Function DerVSSloop

Complex(dp) Function DerVVSloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVVSloop = DerB0(p2,m12,m22)
End Function DerVVSloop

Complex(dp) Function DerSVVloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerSVVloop = 4._dp*Real(DerB0(p2,m12,m22),dp)
End Function DerSVVloop

Complex(dp) Function  DerVGGloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
DerVGGloop = DerB00(p2,m12,m22)
End Function  DerVGGloop

Complex(dp) Function DerVVVloop(p2,m12,m22)
Implicit None
Real(dp), Intent(in) :: p2,m12,m22
! DerVVVloop = 2._dp/3._dp*rMS + 10._dp*DerB00(p2,m12,m22) &
!      & + (m12+m22+4._dp*p2)*DerB0(p2,m12,m22)+ 4._dp*B0(p2,m12,m22)
DerVVVloop =  10._dp*DerB00(p2,m12,m22) &
     & + (m12+m22+4._dp*p2)*DerB0(p2,m12,m22)+ 4._dp*B0(p2,m12,m22)

End Function DerVVVloop




!derivatives of B1, B00, B11, B001, B111

 Complex(dp) Function DerB1(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff

  If (divonly.Eq.1) Then
   DerB1 = ZeroC
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB1(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    DerB1 = - 1._dp / (12._dp * xm1)
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    DerB1 = - 1._dp / (6._dp * xm2)
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    DerB1 = 1._dp / (3._dp * xm1)
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB1 = LogA * xm1**3 - 3._dp * LogA * xm1**2 * xm2 &
    & + 3._dp * LogA * xm1 * xm2**2 - LogA * xm2**3 &
    & + 8._dp * LogB * xm1**2 * xm2 + 8._dp * LogB * xm1 * xm2**2 &
    & - 4._dp * LogB * xm2**3 - 2._dp * LogC * xm1**3 &
    & + 6._dp * LogC * xm1**2 * xm2 - 6._dp * LogC * xm1 * xm2**2 &
    & + 2._dp * LogC * xm2**3 - 2._dp * LogD * xm1**3 &
    & + 4._dp * LogD * xm1**2 * xm2 - 2._dp * LogD * xm1 * xm2**2 &
    & + 2._dp * LogE * xm1**2 * xm2 - 4._dp * LogE * xm1 * xm2**2 &
    & + 2._dp * LogE * xm2**3 - 2._dp * xm1**3 - 3._dp * xm1**2 * xm2 &
    & + 6._dp * xm1 * xm2**2 - xm2**3
    DerB1 = DerB1 / (6._dp * (xm1 - xm2)**4)
   End If

  Else !generell case

  DerB1 = (xm1 - xm2) * B0(xp,xm1,xm2) &
   & + (xm2 - xm1) * B0(0._dp,xm1,xm2) &
   & - xp * (xm1 - xm2 + xp) * DerB0(xp,xm1,xm2)
  DerB1 = DerB1 / (2._dp * xp * xp)

  End If

 End Function DerB1

 Complex(dp) Function DerB00(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: VB0, VDerB0
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff

  If (divonly.Eq.1) Then
   DerB00 = - divergence / 12._dp
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB00(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    LogD = Log(mudim2/xm1)
    DerB00 = -(divergence + LogD) / 12._dp
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    LogE = Log(mudim2/xm2)
    DerB00 = - (6._dp * divergence + 6._dp * LogE + 5._dp) / 72._dp
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    LogD = Log(mudim2/xm1)
    DerB00 = - (6._dp * divergence + 6._dp * LogD + 5._dp) / 72._dp
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB00 = - 6._dp * divergence * xm1**3 + 18._dp * divergence * xm1**2 * xm2 &
    & -18._dp * divergence * xm1 * xm2**2 + 6._dp * divergence * xm2**3 &
    & + 6._dp * LogB * xm1**3 - 18._dp * LogB * xm1**2 * xm2 &
    & - 18._dp * LogB * xm1 * xm2**2 + 6._dp * LogB * xm2**3 &
    & + 6._dp * LogC * xm1**3 - 18._dp * LogC * xm1**2 * xm2 &
    & + 18._dp * LogC * xm1 * xm2**2 - 6._dp * LogC * xm2**3 &
    & - 5._dp * xm1**3 + 27._dp * xm1**2 * xm2 - 27._dp * xm1 * xm2**2 &
    & + 5._dp * xm2**3
    DerB00 = DerB00 / (72._dp * (xm1 - xm2)**3)
   End If

  Else !generell case

  VB0 = B0(xp,xm1,xm2)
  VDerB0 = DerB0(xp,xm1,xm2)

  DerB00 = 3._dp * (xm1 * xm1 - 2._dp * xm1 * xm2 &
   & + xm2 * xm2 - xp * xp) * VB0 &
   & - 3._dp * (xm1 - xm2) * (xm1 - xm2) * B0(0._dp,xm1,xm2) &
   & - 3._dp * xp * (xm1 * xm1 + xm2 * xm2 + xp * xp)* VDerB0 &
   & + 6._dp * (xm1 + xm2) * xp * xp * VDerB0 &
   & + 6._dp * xm1 * xm2 * xp * VDerB0 - 2._dp * xp * xp
  DerB00 = DerB00 / (36._dp * xp * xp)

  End If

 End Function DerB00

 Complex(dp) Function DerB11(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: VB0, VDerB0
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff

  If (divonly.Eq.1) Then
   DerB11 = ZeroC
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB11(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    DerB11 = 1._dp / (20._dp * xm1)
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    DerB11 = 1._dp / (12._dp * xm2)
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    DerB11 = 1._dp / (4._dp * xm1)
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB11 = -3._dp * LogA * xm1**4 + 12._dp * LogA * xm1**3 * xm2 &
    & - 18._dp * LogA * xm1**2 * xm2**2 + 12._dp * LogA * xm1 * xm2**3 &
    & - 3._dp * LogA * xm2**4 - 30._dp * LogB * xm1**3 * xm2 &
    & - 54._dp * LogB * xm1**2 * xm2**2 + 54._dp * LogB * xm1 * xm2**3 &
    & - 18._dp * LogB * xm2**4 + 6._dp * LogC * xm1**4 &
    & - 30._dp * LogC * xm1**3 * xm2 + 54._dp * LogC * xm1**2 * xm2**2 &
    & - 42._dp * LogC * xm1 * xm2**3 + 12._dp * LogC * xm2**4 &
    & + 6._dp * LogD * xm1**4 - 18._dp * LogD * xm1**3 * xm2 &
    & + 18._dp * LogD * xm1**2 * xm2**2 - 6._dp * LogD * xm1 * xm2**3 &
    & - 12._dp * LogE * xm1**3 * xm2 + 36._dp * LogE * xm1**2 * xm2**2 &
    & - 36._dp * LogE * xm1 * xm2**3 + 12._dp * LogE * xm2**4 &
    & + 6._dp * xm1**4 + 20._dp * xm1**3 * xm2 - 36._dp * xm1**2 * xm2**2 &
    & + 12._dp * xm1 * xm2**3 - 2._dp * xm2**4
    DerB11 = DerB11 / (24._dp * (xm1 - xm2)**5)
   End If

  Else !generell case

  VB0 = B0(xp,xm1,xm2)
  VDerB0 = DerB0(xp,xm1,xm2)

   DerB11 = 4._dp * xm1**2 * B0(0._dp,xm1,xm2) &
    & + 4._dp * xm2**2 * B0(0._dp,xm1,xm2) + 2._dp * xm1 * xp * B0(0._dp,xm1,xm2) &
    & - 2._dp * xm2 * xp * B0(0._dp,xm1,xm2) - 8._dp * xm1 * xm2 * B0(0._dp,xm1,xm2) &
    & - 2._dp * xp * A0(xm2) - 4._dp * VB0 * xm1**2 + 8._dp * VB0 * xm1 * xm2 &
    & - 2._dp * VB0 * xm1 * xp - 4._dp * VB0 * xm2**2 + 4._dp * VB0 * xm2 * xp &
    & + 2._dp * VDerB0 * xm1**2 * xp - 4._dp * VDerB0 * xm1 * xm2 * xp &
    & + 2._dp * VDerB0 * xm1 * xp**2 + 2._dp * VDerB0 * xm2**2 * xp &
    & - 4._dp * VDerB0 * xm2 * xp**2 + 2._dp * VDerB0 * xp**3 + xm1 * xp + xm2 * xp
   DerB11 = DerB11 / (6._dp * xp * xp * xp)

  End If

 End Function DerB11

 Complex(dp) Function DerB001(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: VB0, VDerB0
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff

  If (divonly.Eq.1) Then
   DerB001 = divergence / 24._dp
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB001(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    LogD = Log(mudim2/xm1)
    DerB001 = (divergence + LogD)/ 24._dp
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    LogE = Log(mudim2/xm2)
    DerB001 = (12._dp * divergence + 12._dp * LogE + 7._dp) / 288._dp
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    LogD = Log(mudim2/xm1)
    DerB001 = (12._dp * divergence + 12._dp * LogD + 13._dp) / 288._dp
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB001 = 12._dp * divergence * xm1**4 - 48._dp * divergence * xm1**3 * xm2 &
    & + 72._dp * divergence * xm1**2 * xm2**2 - 48._dp * divergence * xm1 * xm2**3 &
    & + 12._dp * divergence * xm2**4 + 2._dp * LogA * xm1**4 - 12._dp * LogA * xm1**2 * xm2**2 &
    & + 16._dp * LogA * xm1 * xm2**3 - 6._dp * LogA * xm2**4 - 12._dp * LogB * xm1**4 &
    & + 48._dp * LogB * xm1**3 * xm2 + 48._dp * LogB * xm1**2 * xm2**2 &
    & - 12._dp * LogB * xm2**4 - 16._dp * LogC * xm1**4 + 48._dp * LogC * xm1**3 * xm2 &
    & - 48._dp * LogC * xm1**2 * xm2**2 + 16._dp * LogC * xm1 * xm2**3 &
    & - 4._dp * LogD * xm1**4 + 12._dp * LogD * xm1**2 * xm2**2 &
    & - 8._dp * LogD * xm1 * xm2**3 + 12._dp * LogE * xm1**2 * xm2**2 &
    & - 24._dp * LogE * xm1 * xm2**3 + 12._dp * LogE * xm2**4 &
    & + 13._dp * xm1**4 - 88._dp * xm1**3 * xm2 + 108._dp * xm1**2 * xm2**2 &
    & - 40._dp * xm1 * xm2**3 + 7._dp * xm2**4
    DerB001 = DerB001 / (288._dp * (xm1 - xm2)**4)
   End If

  Else !generell case

  VB0 = B0(xp,xm1,xm2)
  VDerB0 = DerB0(xp,xm1,xm2)

  DerB001 = 6._dp * (xm1 - xm2) * (2._dp * xm1**2 - xm1 * (4._dp * xm2 + xp) &
   &         + 2._dp * xm2 * (xm2-xp)) * B0(0._dp,xm1,xm2) &
   & + 6._dp * xp * (xm2 - xm1) * A0(xm2) - 12._dp * VB0 * xm1**3 &
   & + 36._dp * VB0 * xm1**2 * xm2 + 6._dp * VB0 * xm1**2 * xp &
   & - 36._dp * VB0 * xm1 * xm2**2 + 12._dp * VB0 * xm1 * xm2 * xp &
   & + 12._dp * VB0 * xm2**3 - 18._dp * VB0 * xm2**2 * xp &
   & + 6._dp * VB0 * xp**3 + 6._dp * VDerB0 * xm1**3 * xp &
   & - 18._dp * VDerB0 * xm1**2 * xm2 * xp - 6._dp * VDerB0 * xm1**2 * xp**2 &
   & + 18._dp * VDerB0 * xm1 * xm2**2 * xp - 12._dp * VDerB0 * xm1 * xm2 * xp**2 &
   & - 6._dp * VDerB0 * xm1 * xp**3 - 6._dp * VDerB0 * xm2**3 * xp &
   & + 18._dp * VDerB0 * xm2**2 * xp**2 - 18._dp * VDerB0 * xm2 * xp**3 &
   & + 6._dp * VDerB0 * xp**4 + 3._dp * xm1**2 * xp - 3._dp * xm2**2 * xp + 4._dp * xp**3
  DerB001 = DerB001 / (144._dp * xp * xp * xp)

  End If

 End Function DerB001

 Complex(dp) Function DerB111(xp, xm1, xm2)
 Implicit None
  Real(dp), Intent(in) :: xp, xm1, xm2
  Complex(dp) :: VB0, VDerB0
  Complex(dp) :: LogA, LogB, LogC, LogD, LogE
  Real(dp) :: mdiff

  If (divonly.Eq.1) Then
   DerB111 = ZeroC
   Return 
  End If

  If (xp.Eq.0._dp) Then
    If (xm1.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm1) !to avoid problems when comparing xm1 with xm2
    Else If (xm2.Ne.0._dp) Then
    mdiff = Abs((xm1-xm2)/xm2)
    Else
    mdiff = 0._dp
    End If
   If ((mdiff.Le.controlmdiff).And.(xm1.Eq.0._dp)) Then !xp=xm1=xm2=0
    write(ErrCan,*) "DerB111(0,0,0) diverges!"
   Else If (mdiff.Le.controlmdiff) Then !xp=0, xm1=xm2
    DerB111 = - 1._dp / (30._dp * xm1)
   Else If (xm1.Eq.0._dp) Then !xp=xm1=0
    DerB111 = - 1._dp / (20._dp * xm2)
   Else If (xm2.Eq.0._dp) Then !xp=xm2=0
    DerB111 = - 1._dp / (5._dp * xm1)
   Else !xp=0
    LogA = Log(xm2/xm1)
    LogB = Log(Sqrt(xm1/xm2))
    LogC = Log(Sqrt(xm1*xm2)/mudim2)
    LogD = Log(mudim2/xm1)
    LogE = Log(mudim2/xm2)

    DerB111 = 15._dp * LogA  * xm1**5 + 21._dp * LogA * xm1**4 * xm2 &
    & - 9._dp * LogA * xm1**3 * xm2**2 - 249._dp * LogA * xm1**2 * xm2**3 &
    & + 366._dp * LogA * xm1 * xm2**4 - 144._dp * LogA * xm2**5 &
    & + 120._dp * LogB * xm1**4 * xm2 - 360._dp * LogB * xm1**2 * xm2**3 &
    & + 1200._dp * LogB * xm1 * xm2**4 - 720._dp * LogB * xm2**5 &
    & - 30._dp * LogC * xm1**5 + 102._dp * LogC * xm1**4 * xm2 &
    & - 138._dp * LogC * xm1**3 * xm2**2 + 522._dp * LogC * xm1**2 * xm2**3 &
    & - 888._dp * LogC * xm1 * xm2**4 + 432._dp * LogC * xm2**5 &
    & - 30._dp * LogD * xm1**5 - 30._dp * LogD * xm1**4 * xm2 &
    & - 60._dp * LogD * xm1**3 * xm2**2 + 330._dp * LogD * xm1**2 * xm2**3 &
    & - 210._dp * LogD * xm1 * xm2**4 + 132._dp * LogE * xm1**4 * xm2 &
    & - 78._dp * LogE * xm1**3 * xm2**2 + 192._dp * LogE * xm1**2 * xm2**3 &
    & - 678._dp * LogE * xm1 * xm2**4 + 432._dp * LogE * xm2**5 &
    & - 24._dp * xm1**5 - 130._dp * xm1**4 * xm2 + 240._dp * xm1**3 * xm2**2 &
    & - 120._dp * xm1**2 * xm2**3 + 40._dp * xm1 * xm2**4 - 6._dp * xm2**5
    DerB111 = DerB111 / (120._dp * (xm1 - xm2)**6)
   End If

  Else !generell case

  VB0 = B0(xp,xm1,xm2)
  VDerB0 = DerB0(xp,xm1,xm2)

  DerB111 =3._dp * (xm1-xm2) * (3._dp * xm1**2 - 6._dp * xm1 * xm2 + 2._dp * xm1 * xp &
   & + 3._dp * xm2**2 - 4._dp * xm2 * xp + xp**2)*B0(0._dp,xm1,xm2) &
   & - 6._dp * xp *A0(xm2)*(xm1-xm2+xp) - 9._dp * VB0 * xm1**3 &
   & + 27._dp * VB0 * xm1**2 * xm2 - 6._dp * VB0 * xm1**2 * xp &
   & - 27._dp * VB0 * xm1 * xm2**2 + 24._dp * VB0 * xm1 * xm2 * xp &
   & - 3._dp * VB0 * xm1 * xp**2 + 9._dp * VB0 * xm2**3 &
   & - 18._dp * VB0 * xm2**2 * xp + 9._dp * VB0 * xm2 * xp**2 &
   & + 3._dp * VDerB0 * xm1**3 * xp - 9._dp * VDerB0 * xm1**2 * xm2 * xp &
   & + 3._dp * VDerB0 * xm1**2 * xp**2 + 9._dp * VDerB0 * xm1 * xm2**2 * xp &
   & - 12._dp * VDerB0 * xm1 * xm2 * xp**2 + 3._dp * VDerB0 * xm1 * xp**3 &
   & - 3._dp * VDerB0 * xm2**3 * xp + 9._dp * VDerB0 * xm2**2 * xp**2 &
   & - 9._dp * VDerB0 * xm2 * xp**3 + 3._dp * VDerB0 * xp**4 &
   & + 3._dp * xm1**2 * xp + 2._dp * xm1 * xp**2 - 3._dp * xm2**2 * xp &
   & + 4._dp * xm2 * xp**2
  DerB111 = - DerB111 / (12._dp * xp * xp * xp * xp)

  End If

 End Function DerB111

!special passarino veltman integrals with zero masses:
!IR145 = argument 1,4 and 5 are zero
!example: C0_IR145(xp1,xp2,xm) = C0(0,xp1,xp2,0,0,xm)
!notation equivalent to looptools = ff package

 Complex(dp) Function C0_IR145(xp1, xp2, xm)
 Implicit None
  Real(dp), Intent(in) :: xp1, xp2, xm
!  Real(dp) :: s1
  Complex(dp) :: logspecial
  
  If (xp1.Eq.xp2) Then !xp1 = xp2

   If (xp1.Eq.xm) Then !xp1 = xp2 = xm
    
    !Call WriteLFerror(3) !divergent
    write(ErrCan,*) "Divergent Passarino Veltman, C0_IR145!"
    C0_IR145 = Huge(1._dp)

   Else !xp1 = xp2 unequal xm

!    calculating log(1-xp2/xm)
!     s1 = 1._dp - xm/xp2
!    If ( Abs(s1) .Lt. xloss ) Then
!     logspecial = Log1minusX(s1)
!    Else
    logspecial = Log(Abs(1._dp - xm/xp2)) + (xm/xp2) * Log(Abs(1._dp/(xp2/xm - 1._dp)))
    If (xp2.Gt.xm) logspecial = logspecial + 2._dp * Cmplx(0._dp,pi,dp) * (1._dp - xm/xp2)

    C0_IR145 = logspecial / (xp2 - xm)

   End If

  Else !the two momenta are not equal

  C0_IR145 = Cget("C0  ",0._dp,xp1,xp2,0._dp,0._dp,xm)

  End If

 End Function C0_IR145

 Complex(dp) Function C2_IR145(xp1, xp2, xm)
 Implicit None
  Real(dp), Intent(in) :: xp1, xp2, xm
  Real(dp) :: s1
  Complex(dp) :: logspecial
  
  If (xp1.Eq.xp2) Then !xp1 = xp2

   If (xp1.Eq.xm) Then !xp1 = xp2 = xm
    
    !Call WriteLFerror(3) !divergent
    write(ErrCan,*) "Divergent Passarino Veltman, C2_IR145!"
    C2_IR145 = Huge(1._dp)

   Else !xp1 = xp2 unequal xm

    !calculating log(1-xp2/xm)
     s1 = xp2/xm
    If ( Abs(s1) .Lt. xloss ) Then
     logspecial = Log1minusX(s1)
    Else
     logspecial = Log(Abs(1._dp - s1))
    End If
    If (xp2.Gt.xm) logspecial = logspecial + Cmplx(0._dp,pi,dp)

    C2_IR145 = - xm * logspecial - xp2
    C2_IR145 = C2_IR145 / (xp2 * xp2)

   End If

  Else !the two momenta are not equal

  C2_IR145 = B0(xp1,0._dp,xm) - B0(xp2,0._dp,xm)
  C2_IR145 = C2_IR145 / (xp1 - xp2)

  End If

 End Function C2_IR145


 Real(dp) Function SetRenormalizationScaleAdd(mu2_in)
 Implicit None
  Real(dp), Intent(in) :: mu2_in

  SetRenormalizationScaleAdd = mudim2
  mudim2 = mu2_in

 End Function SetRenormalizationScaleAdd

 Real(dp) Function SetDivergenceAdd(diver_in)
 !-----------------------------------------------------------------------
 ! resets divergence
 !-----------------------------------------------------------------------
 Implicit None
  Real(dp), Intent(in) :: diver_in

  SetDivergenceAdd = divergence
  divergence = diver_in

 End Function SetDivergenceAdd

 Integer Function SetDivonlyAdd(div_in)
 !-----------------------------------------------------------------------
 ! take only divergent parts
 !-----------------------------------------------------------------------
 Implicit None
  Integer, Intent(in) :: div_in

  SetDivonlyAdd = divonly
  divonly = div_in

 End Function SetDivonlyAdd
 
 
End Module AddLoopFunctions
