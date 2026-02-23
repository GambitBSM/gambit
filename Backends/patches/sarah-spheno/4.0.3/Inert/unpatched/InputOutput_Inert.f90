! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:33 on 18.2.2026   
! ----------------------------------------------------------------------  
 
 
Module InputOutput_Inert 
 
Use Control 
Use Settings 
!Use Experiment 
Use Model_Data_Inert 
Use LoopFunctions 
Use AddLoopFunctions 
Use StandardModel 
Use LoopCouplings_Inert 
 
Logical,Save::LesHouches_Format
Character(len=8),Save,Private::versionSARAH="4.14.0"
Integer,Private::i_cpv=0
Integer,Save,Private::in_kont(2)
Logical,Save::Add_Rparity= .False. 
Logical,Save::Write_HiggsBounds= .False. 
Logical,Save::Write_HiggsBounds5= .False. 
Character(len=40),Private::sp_info

Logical,Private::l_RP_Pythia= .False. 
Logical,Save,Private::Use_Flavour_States= .False. 
Real(dp),Save,Private::BrMin=1.e-4_dp 
Real(dp),Save,Private::SigMin=1.e-4_dp 
Character(len=120)::inputFileName,outputFileName 
Contains 
 
Subroutine LesHouches_Input(kont, Ecms, Pm, Pp, l_ISR, Fgmsb) 
 
Implicit None 
Integer, Intent(out) :: kont
Real(dp), Intent(out) :: Fgmsb, Ecms(:), Pm(:), Pp(:)
Logical, Intent(out) :: l_ISR(:)
Character(len=80) :: read_line
Integer :: i_mod=-1, i_sm=-1, i_par=-1, set_mod_par(25)=-1 &
& , i1, p_max, p_act, i_sp, i_model=-1, i_particles=-1
Real(dp) :: wert, Abs_Mu2, cosb2, cos2b, sinb2, RG0(3,3) &
 & , mat_D(3,3), R2(2,2), s12,s13,s23,c12,c13,c23
Logical :: check, calc_ferm, check_alpha(2)
Complex(dp) :: lam_vS
Logical, Save :: l_open = .True. 
 
Iname = Iname + 1
NameOfUnit(Iname) = "LesHouches_Input" 

check_alpha = .False. ! used to check consistency of alpha(mZ) calculation
in_kont = 0

Call InitializeStandardModel 
Call InitializeLoopFunctions 
 
i_mod = -1
i_sm = -1
i_par = -1
set_mod_par = -1 

ErrorLevel = -1
GenerationMixing=.False.
If (l_open) Then
   Open(ErrCan,file="Messages.out",status="unknown")
   Open(11,file="SPheno.out",status="unknown")
   l_open = .False.
End If 

Call Set_All_Parameters_0()

lam_vs = 0._dp
sp_info = " "
HighScaleModel="SARAH_Generated_Model" 
TwoLoopRGE = .True.
Fgmsb = 1.e12_dp
m32 = 1.e20_dp 
 
kont = 0
Open(99,file=inputFileName,status="old",err=200)
 
Do 
  Read(99,"(a80)",End=200,err=200) read_line 
  If (read_line(1:1).Eq."#") Cycle 
  If (read_line.Eq." ") Cycle 
  Call PutUpperCase(read_line) 
  If (read_line(1:5).Eq."BLOCK") Then  
    If (read_line(7:12).Eq."MODSEL") Then  
      kont = 0  
     Call Read_MODSEL(99,i_particles,i_model,i_cpv,kont)  
 CKMcomplex = CKM 
 If (i_cpv.Eq.0) Then 
 s12=lam_wolf 
 s23=s12**2*A_wolf 
 s13=s23*lam_wolf*Sqrt(eta_wolf**2+rho_wolf**2) 
 c12=Sqrt(1._dp-s12*s12) 
 c23=Sqrt(1._dp-s23*s23) 
 c13=Sqrt(1._dp-s13*s13) 
 CKM(1,1)=c12*c13 
 CKM(1,2)=s12*c13 
 CKM(1,3)=s13 
 CKM(2,1)=-s12*c23-c12*s23*s13 
 CKM(2,2)=c12*c23-s12*s23*s13 
 CKM(2,3)=s23*c13 
 CKM(3,1)=s12*s23-c12*c23*s13 
 CKM(3,2)=-c12*s23-s12*c23*s13 
 CKM(3,3)=c23*c13 
 End If 
    Else If (read_line(7:14).Eq."SMINPUTS") Then  
     Call Read_SMinput(99)  
    Else If (read_line(7:12).Eq."VCKMIN") Then  
     Call Read_CKM(99,i_cpv)  
    Else If (read_line(7:12).Eq."FCONST") Then  
     Call Read_FCONST(99)  
    Else If (read_line(7:11).Eq."FMASS") Then  
     Call Read_FMASS(99)  
    Else If (read_line(7:11).Eq."FLIFE") Then  
     Call Read_FLIFE(99)  
    Else If (read_line(7:17).Eq."SPHENOINPUT") Then  
     Call Read_SPhenoInput(99)  
    Else If (read_line(7:18).Eq."DECAYOPTIONS") Then  
     Call Read_DecayOptions(99)  
    Else If (read_line(7:12).Eq."MINPAR") Then  
     Call Read_MINPAR(99,0,i_model,set_mod_par,kont)  
    Else If (read_line(7:14).Eq."IMMINPAR") Then  
       If (i_cpv.Lt.2) Then 
       Call Warn_CPV(i_cpv,"IMMINPAR") 
       End If 
    Call Read_MINPAR(99,1,i_model,set_mod_par,kont)  
    Else If (read_line(7:12).Eq."EXTPAR") Then  
     Call Read_EXTPAR(99,0,i_model,set_mod_par,kont)  
    Else If (read_line(7:14).Eq."IMEXTPAR") Then  
       If (i_cpv.Lt.2) Then 
       Call Warn_CPV(i_cpv,"IMEXTPAR") 
       End If 
    Call Read_EXTPAR(99,1,i_model,set_mod_par,kont)  
   Else If (read_line(7:10).Eq."YEIN") Then 
InputValueforYe= .True. 
    Call ReadMatrixC(99,3,3,YeIN,0, "YeIN",kont)

 
   Else If (read_line(7:12).Eq."IMYEIN") Then 
     If (i_cpv.Lt.2) Then  
       Call Warn_CPV(i_cpv,"IMYe") 
       Cycle 
     End If 
    Call ReadMatrixC(99,3,3,YeIN,1, "YeIN",kont)

 
   Else If (read_line(7:10).Eq."YDIN") Then 
InputValueforYd= .True. 
    Call ReadMatrixC(99,3,3,YdIN,0, "YdIN",kont)

 
   Else If (read_line(7:12).Eq."IMYDIN") Then 
     If (i_cpv.Lt.2) Then  
       Call Warn_CPV(i_cpv,"IMYd") 
       Cycle 
     End If 
    Call ReadMatrixC(99,3,3,YdIN,1, "YdIN",kont)

 
   Else If (read_line(7:10).Eq."YUIN") Then 
InputValueforYu= .True. 
    Call ReadMatrixC(99,3,3,YuIN,0, "YuIN",kont)

 
   Else If (read_line(7:12).Eq."IMYUIN") Then 
     If (i_cpv.Lt.2) Then  
       Call Warn_CPV(i_cpv,"IMYu") 
       Cycle 
     End If 
    Call ReadMatrixC(99,3,3,YuIN,1, "YuIN",kont)

 
   Else If (read_line(7:13).Eq."GAUGEIN") Then 
    Call Read_GAUGEIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:15).Eq."IMGAUGEIN") Then 
    Call Read_GAUGEIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:11).Eq."HDMIN") Then 
    Call Read_HDMIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:13).Eq."IMHDMIN") Then 
    Call Read_HDMIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:13).Eq."MSOFTIN") Then 
    Call Read_MSOFTIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:15).Eq."IMMSOFTIN") Then 
    Call Read_MSOFTIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:12).Eq."HMIXIN") Then 
    Call Read_HMIXIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:14).Eq."IMHMIXIN") Then 
    Call Read_HMIXIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:13).Eq."GAUGEIN") Then 
    Call Read_GAUGEIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:15).Eq."IMGAUGEIN") Then 
    Call Read_GAUGEIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:11).Eq."HDMIN") Then 
    Call Read_HDMIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:13).Eq."IMHDMIN") Then 
    Call Read_HDMIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:13).Eq."MSOFTIN") Then 
    Call Read_MSOFTIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:15).Eq."IMMSOFTIN") Then 
    Call Read_MSOFTIN(99,1,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:12).Eq."HMIXIN") Then 
    Call Read_HMIXIN(99,0,i_model,set_mod_par,kont) 
 
   Else If (read_line(7:14).Eq."IMHMIXIN") Then 
    Call Read_HMIXIN(99,1,i_model,set_mod_par,kont) 
 
End if 
End If 
End Do 
200 Close(99) 
gmZ = gamZ * mZ
gmZ2 = gmZ**2
mW2 = mZ2 * (0.5_dp + Sqrt(0.25_dp-Alpha_Mz*pi / (sqrt2*G_F*mZ2))) / 0.987_dp
mW = Sqrt(mW2) 
mW_SM = MW 
gamW = 2.06_dp 
gamW2 = gamW**2
gmW = gamW * mW
gmW2 = gmW**2
Alpha_mZ = Alpha_MSbar(mZ, mW)
If (calc_ferm) Call CalculateRunningMasses(mf_l,mf_d,mf_u&
&,Q_light_quarks,alpha_mZ,alphas_mZ,mZ&
&,mf_l_mZ,mf_d_mZ,mf_u_mZ,kont)


Iname=Iname-1
Contains
Subroutine Read_MINPAR(io,i_c,i_model,set_mod_par,kont) 
Implicit None 
Integer,Intent(in)::io,i_c,i_model 
Integer,Intent(inout)::kont,set_mod_par(:) 
Integer::i_par 
Real(dp)::wert 
Character(len=80)::read_line 
Do 
Read(io,*,End=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*) i_par,wert!,read_line 
If (i_par.Eq.1) Then 
If (i_c.Eq.0) Lambda1IN= Cmplx(wert,Aimag(Lambda1IN),dp) 
If (i_c.Eq.1) Lambda1IN= Cmplx(Real(Lambda1IN,dp),wert,dp) 
Else If (i_par.Eq.2) Then 
If (i_c.Eq.0) Lambda2IN= Cmplx(wert,Aimag(Lambda2IN),dp) 
If (i_c.Eq.1) Lambda2IN= Cmplx(Real(Lambda2IN,dp),wert,dp) 
Else If (i_par.Eq.3) Then 
If (i_c.Eq.0) Lambda3IN= Cmplx(wert,Aimag(Lambda3IN),dp) 
If (i_c.Eq.1) Lambda3IN= Cmplx(Real(Lambda3IN,dp),wert,dp) 
Else If (i_par.Eq.4) Then 
If (i_c.Eq.0) Lambda4IN= Cmplx(wert,Aimag(Lambda4IN),dp) 
If (i_c.Eq.1) Lambda4IN= Cmplx(Real(Lambda4IN,dp),wert,dp) 
Else If (i_par.Eq.5) Then 
If (i_c.Eq.0) Lambda5IN= Cmplx(wert,Aimag(Lambda5IN),dp) 
If (i_c.Eq.1) Lambda5IN= Cmplx(Real(Lambda5IN,dp),wert,dp) 
Else
Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
If (i_c.Eq.0) Write(ErrCan,*) "Unknown entry for Block MINPAR ",i_par
If (i_c.Eq.1) Write(ErrCan,*) "Unknown entry for Block IMMINPAR ",i_par
If (i_c.Eq.0) Write(*,*) "Unknown entry for Block MINPAR ",i_par
If (i_c.Eq.1) Write(*,*) "Unknown entry for Block IMMINPAR ",i_par
Call AddError(304)
If (ErrorLevel.Eq.2) Call TerminateProgram
End If
End Do! i_par
200 Return
End Subroutine Read_MINPAR 
 
 
Subroutine Read_EXTPAR(io,i_c,i_model,set_mod_par,kont) 
Implicit None 
Integer,Intent(in)::io,i_c,i_model 
Integer,Intent(inout)::kont,set_mod_par(:) 
Integer::i_par 
Real(dp)::wert 
Character(len=80)::read_line 
Do 
Read(io,*,End=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*) i_par,wert!,read_line 
End Do! i_par
200 Return
End Subroutine Read_EXTPAR 
 
 
 Subroutine Read_MODSEL(io, i_particles, i_model, i_cpv, kont)
  Implicit None
   Integer, Intent(in) :: io
   Integer, Intent(out) :: i_particles, i_model, i_cpv
   Integer, Intent(inout) :: kont
    Real(dp) :: r_mod

   Integer :: i_mod, i_test, i_rp
   Character(len=80) :: read_line

   i_cpv = 0
   i_rp = 0

    Do 
     Read(io,*) read_line
     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop

     Read(io,*) i_test,r_mod ! ,read_line
     If (i_test.Ne.12) Then
      Backspace(io)
      Read(io,*) i_test,i_mod ! ,read_line
     End If

!      Read(io,*) i_test,i_mod,read_line
     If (i_test.Eq.1) Then
      i_particles = i_test
      i_model = i_mod
      If ((i_mod.Lt.0).Or.(i_mod.Gt.99)) Then
       Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
       Write(ErrCan,*) "MSSM, Unknown entry for Block MODSEL ",i_mod
       kont = -302
       Call AddError(-kont)
       Return
      Else If (i_mod.Eq.1) Then
       HighScaleModel = "GUT"
      Else If (i_mod.Eq.0) Then
       HighScaleModel = "LOW"
      End If

     Else If (i_test.Eq.2) Then
      BoundaryCondition = i_mod
     Else If (i_test.Eq.4) Then
      If (i_mod.Eq.1) Then
       i_rp = 1

      Else If (i_mod.Ne.0) Then
       Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
       Write(ErrCan,*) "Unknown entry for Block MODSEL ",i_test,i_mod
       kont = -302
       Call AddError(-kont)
       Return
      End If

     Else If (i_test.Eq.5) Then
      i_cpv = i_mod
      If ((i_mod.Lt.0).Or.(i_mod.Gt.2)) Then
       Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
       Write(ErrCan,*) "Unknown entry for Block MODSEL ",i_test,i_mod
       kont = -302
       Call AddError(-kont)
       Return
      End If

     Else If (i_test.Eq.6) Then
      If (i_mod.Eq.0) Then
       GenerationMixing = .False.
      Else If ((i_mod.Ge.1).And.(i_mod.Le.3)) Then
       GenerationMixing = .True.
      Else
       Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
       Write(ErrCan,*) "GenerationMixing, Unknown entry for Block MODSEL ",i_mod
       kont = -302
       Call AddError(-kont)
       Return
      End If

    Else If (i_test.Eq.12) Then
      Call SetRGEScale(r_mod**2)  ! set Q_EWSB

     End If
    End Do ! i_mod

  End Subroutine Read_MODSEL

  Subroutine Read_SMinput(io)
  Implicit None
   Integer, Intent(in) :: io
   
   Integer :: i_sm
   Real(dp) :: wert
   Character(len=80) :: read_line

    Do 
     Read(io,*) read_line
     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop

     Read(io,*) i_sm,wert,read_line

     Select Case(i_sm)
     Case(1)
      check_alpha(1) = .True.
      MZ_input = .True.
      Alpha_MZ_MS = 1._dp / wert

     Case(2) ! G_F
      G_F = wert

     Case(3) ! alpha_s(m_Z)
      alphaS_mZ = wert

     Case(4) ! m_Z
      mZ = wert
      mZ2 = mZ**2
      calc_ferm = .True.

     Case(5) ! m_b(m_b)^MSbar
      mf_d(3) = wert
      mf_d2(3) = mf_d(3)**2
      calc_ferm = .True.

     Case(6) ! m_t^pole
      mf_u(3) = wert
      mf_u2(3) = mf_u(3)**2

     Case(7) ! m_tau^pole
      mf_l(3) = wert
      mf_l2(3) = mf_l(3)**2
      calc_ferm = .True.

     Case(8) ! m_nu_3, input is in GeV
      Mf_nu(3) = wert

     Case(11) ! electron mass
      mf_l(1) = wert
      mf_l2(1) = wert**2
      calc_ferm = .True.

     Case(12) ! m_nu_1, input is in GeV
      Mf_nu(1) = wert 

     Case(13) ! muon mass
      mf_l(2) = wert
      mf_l2(2) = wert**2
      calc_ferm = .True.

     Case(14) ! m_nu_2, input is in eV, transform to GeV
      Mf_nu(2) = wert 

     Case(21) ! d-quark mass at 2 GeV
      mf_d(1) = wert
      mf_d2(1) = wert**2
      calc_ferm = .True.

     Case(22) ! u-quark mass at 2 GeV
      mf_u(1) = wert
      mf_u2(1) = wert**2
      calc_ferm = .True.

     Case(23) ! s-quark mass at 2 GeV
      mf_d(2) = wert
      mf_d2(2) = wert**2
      calc_ferm = .True.

     Case(24) ! c-quark mass at Q=m_c
      mf_u(2) = wert
      mf_u2(2) = wert**2
      calc_ferm = .True.

     Case Default
      If (output_screen) &
           & Write(*,*) "Ignoring unknown entry for Block SMINPUTS ",i_sm 
      Write(ErrCan,*) "Ignoring unknown entry for Block SMINPUTS ",i_sm 
     End Select

    End Do ! i_sm

  End Subroutine Read_SMinput

 Subroutine Read_CKM(io, i_cpv)
  Implicit None
   Integer, Intent(in) :: io, i_cpv

   Real(dp) :: s12, s13, s23, c12, c13, c23, phase
    
    Do 
     Read(io,*,End=200) read_line
!     Write(*,*) read_line
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."#").Or.(read_line(1:1).Eq."B")  &
                                .Or.(read_line(1:1).Eq."b") ) Exit ! this loop
     Read(io,*) i1, wert, read_line
     Select Case(i1)     
     Case(1)
      lam_wolf = wert
     Case(2)
      A_wolf = wert
     Case(3)
      rho_wolf = wert
     Case(4)
      eta_wolf = wert
     Case default
     End Select

    End Do

 200   s12 = lam_wolf
    s23 = s12**2 * A_wolf
    s13 = s23 * lam_wolf * Sqrt(eta_wolf**2+rho_wolf**2)
    If (i_cpv.Eq.0) Then
     Write(ErrCan,*) "Warning: CP violation is switched of, ignoring CKM phase."
     phase = 0._dp
    Else
     phase = Atan(eta_wolf/rho_wolf)
    End If


    c12 = Sqrt(1._dp-s12*s12)
    c23 = Sqrt(1._dp-s23*s23)
    c13 = Sqrt(1._dp-s13*s13)

    CKM(1,1) = c12 * c13
    CKM(1,2) = s12 * c13
    CKM(2,3) = s23 * c13
    CKM(3,3) = c23 * c13
    If (phase.Ne.0._dp) Then
     CKM(1,3) = s13 * Exp( (0._dp,-1._dp) * phase )
     CKM(2,1) = -s12*c23 -c12*s23*s13 * Exp( (0._dp,1._dp) * phase )
     CKM(2,2) = c12*c23 -s12*s23*s13 * Exp( (0._dp,1._dp) * phase )
     CKM(3,1) = s12*s23 -c12*c23*s13 * Exp( (0._dp,1._dp) * phase )
     CKM(3,2) = -c12*s23 - s12*c23*s13 * Exp( (0._dp,1._dp) * phase )
    Else
     CKM(1,3) = s13
     CKM(2,1) = -s12*c23 -c12*s23*s13
     CKM(2,2) = c12*c23 -s12*s23*s13
     CKM(3,1) = s12*s23 -c12*c23*s13
     CKM(3,2) = -c12*s23 - s12*c23*s13
    End If

  End Subroutine Read_CKM

 Subroutine Read_SPINFO(io, kont)
  Implicit None
   Integer, Intent(in) :: io
   Integer, Intent(inout) :: kont

    Do 
     Read(io,*,End=200) read_line
!     Write(*,*) read_line

     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop

     Read(io,*) i_sp, read_line

     If (i_sp.Eq.1) Then
      sp_info = Trim(read_line)//" "//Trim(sp_info)
     Else If (i_sp.Eq.2) Then
      sp_info = Trim(sp_info)//" "//Trim(read_line)
     Else If (i_sp.Eq.4) Then ! there is some inconsistency, exit
      kont = -306
      Call AddError(306)
      Iname = Iname - 1
      Return
     Else
      Write(ErrCan,*) "Unknown entry in BLOCK SPINFO, is ignored:"
      Write(ErrCan,*) i_sp, read_line
     End If
    End Do

   200 Return

  End Subroutine Read_SPINFO

  Subroutine Read_SPhenoInput(io)
  Implicit None
   Integer, Intent(in) :: io

   Integer :: i_par
   Real(dp) :: wert
   Character(len=80) :: read_line

    ! This initialization is necessary for the arrar of production infos
    p_max = Size(Ecms)
    p_act = 0
    Ecms = 0._dp
    Pm = 0._dp
    Pp = 0._dp
    l_ISR = .False.
    Do 
     Read(io,*,End=200,err=200) read_line
!     Write(*,*) trim(read_line)
     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop

     Read(io,*,End=200) i_par,wert,read_line
!     write(*,*) i_par,wert,trim(read_line)
     Select Case(i_par)
     Case(1)
      ErrorLevel = Int(wert)

     Case(2)
      If (Int(wert).Ne.0) Then
       SPA_convention = .True.
       Call SetRGEScale(1.e3_dp**2)
      End If

     Case(3)
      If (Int(wert).Ne.0) Then 
       External_Spectrum = .True.
       External_Higgs = .True.
      End If

     Case(4)
      If (Int(wert).Ne.0) Use_Flavour_States = .True.

     Case(5)
      If (Int(wert).Ne.0) FermionMassResummation = .False.
      
     Case(6)
       RXiNew = wert      

     Case(7)
       If (wert.eq.1) then
         CalculateTwoLoopHiggsMasses=.False.
!          TwoLoopMatching = .false.
!          OneLoopMatching = .false.         
       Else
         CalculateTwoLoopHiggsMasses=.True.
       End if

     Case(8)
        SELECT CASE (int(WERT))
        CASE ( 1 )
           PurelyNumericalEffPot = .true.
           CalculateMSSM2Loop = .false.
           TwoLoopMethod=1
        CASE ( 2 )
           PurelyNumericalEffPot = .false.
           CalculateMSSM2Loop = .false.
           TwoLoopMethod=2
        CASE ( 3 )
           CalculateMSSM2Loop = .false.
           TwoLoopMethod=3
        CASE ( 8 )
           CalculateMSSM2Loop = .True.
           TwoLoopMethod=8
        CASE ( 9 )
           CalculateMSSM2Loop = .True.
           TwoLoopMethod=9
        CASE DEFAULT 
           Write(*,*) "Unknown option for two-loop mass calculation"
           CalculateTwoLoopHiggsMasses=.False.
        END SELECT


 
     Case(9)
       If (wert.Ne.0) Then
        GaugelessLimit=.true.
       Else
        GaugelessLimit=.false.
       End If

     Case(400)
       hstep_pn = wert
     Case(401)
       hstep_sa = wert
       
     Case(410)
       TwoLoopRegulatorMass = wert       

     Case(10)
       If (wert.Ne.1) Then
        TwoLoopSafeMode=.false.
       Else
        TwoLoopSafeMode=.true.
       End If

     Case(11)  ! whether to calculate  branching ratios or not
      If (Int(wert).Eq.1) L_BR = .True.
      If (Int(wert).Eq.0) L_BR = .False.

     Case(12) ! minimal value such that a branching ratio is written out
      Call SetWriteMinBR(wert)

     Case(13) ! minimal value such that a branching ratio is written out
      If (wert.Eq.0) Then
           Enable3BDecaysF = .False.
           Enable3BDecaysS = .False.        
      Elseif (wert.Eq.1) Then
           Enable3BDecaysF = .True.
           Enable3BDecaysS = .False.        
      Elseif (wert.Eq.2) Then
           Enable3BDecaysS = .True.
           Enable3BDecaysF = .False.        
      Elseif (wert.Eq.3) Then
           Enable3BDecaysF = .True.
           Enable3BDecaysS = .True.        
      Else 
          Write(*,*) "Unknown option for flag 13 (three-body decays): ",wert
      End if


     Case(14) ! run SUSY couplings to scale of decaying particle
      If (wert.Eq.0) RunningCouplingsDecays = .False.    

     Case(15) ! run SUSY couplings to scale of decaying particle
      MinWidth = wert    
      
     Case(16) ! run SUSY couplings to scale of decaying particle
       If (wert.Ne.0) Then
        OneLoopDecays=.true.
       Else
        OneLoopDecays=.false.
       End If
!      Case(21)  ! whether to calculate cross sections or not
!       If (Int(wert).Eq.1) L_CS = .True.
!       If (Int(wert).Eq.0) L_CS = .False.
! 
!      Case(22) ! cms energy
!       p_act = p_act + 1
!       ! this test is necessary to avoid a memory violation
!       If (p_act.Le.p_max) Then
!        Ecms(p_act) = wert
!       Else
!        If (output_screen) &
!            & Write(*,*) "The number of required points for the calculation"// &
!            &  " of cross sections exceeds",p_max
!        If (output_screen) &
!            & Write(*,*) "Ignoring this information"
!        If (output_screen) &
!      &  Write(*,*) "Please enlarge the corresponding arrays in the main program."
!        Write(ErrCan,*) "The number of required points for the calculation"// &
!                &   " of cross sections exceeds",p_max
!        Write(ErrCan,*) "Ignoring this information"
!        Write(ErrCan,*) &
!          &"Please enlarge the corresponding arrays in the main program."
!       End If

!      Case (23) ! polarisation of incoming e- beam
!       If (Abs(wert).Gt.1._dp) Then
!        If (output_screen) Write(*,*) &
!            & "e- beam polarisation has to between -1 and 1 and not",wert
!        If (output_screen) &
!            & Write(*,*) "using now unpolarised e- beam"
!        Write(ErrCan,*) &
!           & "e- beam polarisation has to between -1 and 1 and not",wert
!        Write(ErrCan,*) "using now unpolarised e- beam"
!        If (p_act.Le.p_max) Pm(p_act) = 0
!       Else
!        If (p_act.Le.p_max) Pm(p_act) = wert
!       End If
! 
!      Case (24) ! polarisation of incoming e+ beam
!       If (Abs(wert).Gt.1._dp) Then
!        If (output_screen) Write(*,*) &
!            & "e+ beam polarisation has to between -1 and 1 and not",wert
!        If (output_screen) &
!            & Write(*,*) "using now unpolarised e+ beam"
!        Write(ErrCan,*) &
!           & "e+ beam polarisation has to between -1 and 1 and not",wert
!        Write(ErrCan,*) "using now unpolarised e+ beam"
!        If (p_act.Le.p_max) Pp(p_act) = 0
!       Else
!        If (p_act.Le.p_max) Pp(p_act) = wert
!       End If

!      Case(25)
!       If ((wert.Eq.1._dp).And.(p_act.Le.p_max)) L_ISR(p_act) = .True.
! 
!      Case(26) ! minimal value such that a cross section is written out
!       Call SetWriteMinSig(wert)

     Case(19) ! maximal number of iterations
      MatchingOrder = Int(wert)

     Case(20) 
      If (wert.eq.1._dp) GetMassUncertainty=.True.

     Case(31) ! setting a fixed GUT scale if wert > 0
      If (wert.Gt.0._dp) Call SetGUTScale(wert)

     Case(32) ! requires strict unification
      If (Int(wert).Ne.0) check = SetStrictUnification(.True.)

     Case(33) ! setting a fixed renormalization scale if wert > 0
      If (wert.Gt.0._dp) Call SetRGEScale(wert**2)

     Case(34) ! precision of mass calculation
      delta_mass = wert

     Case(35) ! maximal number of iterations
      n_run = Int(wert)

     Case(36) ! minimal number of iterations
      MinimalNumberIterations = Int(wert)

!      Case(36) ! write out debug information
!       If (wert.Eq.0) Then
!        WriteOut = .False.
!       Else
!        WriteOut = .True.
!       End If

     Case(37) ! if =1 -> CKM thourgh V_u, if =2 CKM through V_d 
      If ((wert.Eq.1._dp).Or.(wert.Eq.2._dp)) i1 =  SetYukawaScheme(Int(wert))

     Case(38) ! set looplevel of RGEs
      If (wert.Ne.2._dp) Then
       TwoLoopRGE=.False.
      Else
       TwoLoopRGE=.True.
      End If

     Case(39) ! write out debug information
      If (wert.Eq.0) Then
       WriteSLHA1 = .False.
      Else
       WriteSLHA1 = .True.
      End If


     Case(40) ! alpha(0)
      check_alpha(2) = .True.
      Alpha = 1._dp / wert

     Case(41) ! Z-boson width
      gamZ = wert

     Case(42) ! W-boson width
      gamW = wert

     Case(50) ! W-boson width
      If (wert.Ne.1._dp) Then
       RotateNegativeFermionMasses=.False.
      Else
       RotateNegativeFermionMasses=.True.
      End If

     Case(51)
      If (wert.Ne.1._dp) Then
       SwitchToSCKM=.False.
      Else
       SwitchToSCKM=.True.
      End If

     Case(52)
      If (wert.Ne.1._dp) Then
       IgnoreNegativeMasses=.False.
      Else
       IgnoreNegativeMasses=.True.
      End If

     Case(53)
      If (wert.Ne.1._dp) Then
       IgnoreNegativeMassesMZ=.False.
      Else
       IgnoreNegativeMassesMZ=.True.
      End If

     Case(54)
      If (wert.Ne.1._dp) Then
       WriteOutputForNonConvergence=.False.
      Else
       WriteOutputForNonConvergence=.True.
      End If

     Case(55)
      If (wert.Ne.0._dp) Then
       CalculateOneLoopMasses=.True.
      Else
       CalculateOneLoopMasses=.False.
!        TwoLoopMatching = .false.
!        OneLoopMatching = .false.
      End If

!      Case(56)
!       If (wert.Ne.0._dp) Then
!        CalculateTwoLoopHiggsMasses=.True.
!       Else
!        CalculateTwoLoopHiggsMasses=.False.
!       End If

     Case(57)
      If (wert.Ne.0._dp) Then
       CalculateLowEnergy=.True.
      Else
       CalculateLowEnergy=.False.
      End If

     Case(58)
      If (wert.Ne.0._dp) Then
        IncludeDeltaVB=.True.
        If (wert.Ne.2._dp) Then
         IncludeBSMdeltaVB=.True.
        Else
         IncludeBSMdeltaVB=.False.
        End If
      Else
       IncludeDeltaVB=.False.
      End If

     Case(60)
      If (wert.Ne.0._dp) Then
       KineticMixing=.True.
      Else
       KineticMixing=.False.
      End If

!      Case(61)
!       If (wert.Ne.0._dp) Then
!        SMrunningLowScaleInput=.True.
!       Else
!        SMrunningLowScaleInput=.False.
!       End If

     Case(62)
      If (wert.Ne.0._dp) Then
       RunningSUSYparametersLowEnergy=.True.
      Else
       RunningSUSYparametersLowEnergy=.False.
      End If

     Case(63)
      If (wert.Ne.0._dp) Then
       RunningSMparametersLowEnergy=.True.
      Else
       RunningSMparametersLowEnergy=.False.
      End If

     Case(64)
      If (wert.Ne.0._dp) Then
       WriteParametersAtQ=.True.
      Else
       WriteParametersAtQ=.False.
      End If
      
     Case(66)
      If (wert.Ne.1._dp) Then
       DecoupleAtRenScale=.False.
      Else
       DecoupleAtRenScale=.True.
      End If      
      
     Case(67)
      If (wert.Eq.0._dp) Then
       Calculate_mh_within_SM=.False.
      Else
       Calculate_mh_within_SM=.True.
        If (wert.Eq.2._dp) Then 
           Force_mh_within_SM = .true. 
        End if
      End If   
      
     Case(68)
      If (wert.Ne.1._dp) Then
       MatchZWpoleMasses=.False.
      Else
       MatchZWpoleMasses=.True.
      End If      

!      Case(70)
!       If (wert.Ne.0._dp) Then
!        SUSYrunningFromMZ=.True.
!       Else
!        SUSYrunningFromMZ=.False.
!       End If

     Case(65)
      If (wert.gt.0) SolutionTadpoleNr = wert 


     Case(75) ! Writes the parameter file for WHIZARD
      If (wert.Eq.1) Write_WHIZARD = .True.     

     Case(76) ! Writes input files for HiggsBounfs
      If (wert.Eq.1) Write_HiggsBounds = .True.
      If (wert.Eq.2) Write_HiggsBounds5 = .True.  
      
     Case(77) ! Use conventions for MO
      If (wert.Eq.1) Then 
        OutputForMO = .True.  
        RotateNegativeFermionMasses = .false.
      End if
      
     Case(78) ! Use conventions for MG
      If (wert.Eq.1) Then 
        OutputForMG = .True.  
      End if  
      
     Case(79) ! Writes Wilson coefficients in WCXF format
      If (wert.Eq.1) Write_WCXF = .True.         


     Case(80) ! exit for sure with non-zero value if a problem occurs
      If (wert.Eq.1) Non_Zero_Exit = .True.      

     Case(86) ! width to be counted as inivisble in HiggsBounds output
      WidthToBeInvisible = wert   

     Case(88) ! maximal mass allowed in loops
      MaxMassLoop = wert**2
   
     Case(89) ! maximal mass counted as numerical zero
      MaxMassNumericalZero = wert

     Case(95) ! Force mass matrices at 1-loop to be real
      If (wert.Eq.1) ForceRealMatrices  = .True.


!      Case(90) ! add R-parity at low energies
!       If (wert.Eq.1) Add_Rparity = .True.      
! 
!      Case(91) ! fit RP parameters such, that neutrino data are o.k.
!       If (wert.Eq.1) l_fit_RP_parameters = .True.      
! 
!      Case(92) ! for Pythia input
!       If (wert.Eq.1) l_RP_Pythia = .True.      
! 
!      Case(97) ! for Pythia input
!       If (wert.Eq.1) PrintPartialContributions = .True. 

      case(150) ! use 1l2lshifts
       if (wert.ne.1._dp) then
         include1l2lshift=.false.
       else
         include1l2lshift=.true.
       end if    

      case(151)
        if (wert.ne.1._dp) Then
         NewGBC=.false.
        else
         NewGBC=.true.
       end if
       
      case(201)
        if (wert.ne.1._dp) Then
         One_Loop_Matching =.false.
        else
         One_Loop_Matching =.true.
       end if       
       
      case(202)
        if (wert.ne.1._dp) Then
         Offdiaognal_WaveFunction_Matching =.false.
        else
         Offdiaognal_WaveFunction_Matching  =.true.
       end if        
       
     Case(440)
      If (wert.Ne.1._dp) Then
       TreeLevelUnitarityLimits=.False.
      Else
       TreeLevelUnitarityLimits=.True.
      End If    
      
     Case(441)
      If (wert.Ne.1._dp) Then
       TrilinearUnitarity=.False.
      Else
       TrilinearUnitarity=.True.
      End If   
      
     Case(442)
       unitarity_s_min = wert       

     Case(443)
       unitarity_s_max = wert       
       
     Case(444)
       unitarity_steps = wert           
       
     Case(445)
      If (wert.Ne.1._dp) Then
       RunRGEs_unitarity=.False.
      Else
       RunRGEs_unitarity=.True.
      End If 
       
     Case(446)
       TUcutLevel = wert          
       
     Case(447)
       CutSpole = wert              
       
       
     Case(510)
      If (wert.Ne.1._dp) Then
       WriteTreeLevelTadpoleSolutions=.False.
      Else
       WriteTreeLevelTadpoleSolutions=.True.
      End If

     Case(515)
      If (wert.Ne.0._dp) Then
       WriteGUTvalues=.True.
      Else
       WriteGUTvalues=.False.
      End If

     Case(520)
      If (wert.Ne.1._dp) Then
       WriteEffHiggsCouplingRatios=.False.
      Else
        WriteEffHiggsCouplingRatios=.True.
      End If
      If (OutputForMG) WriteEffHiggsCouplingRatios=.false.

     Case(521)
      If (wert.Ne.1._dp) Then
       HigherOrderDiboson=.False.
      Else
       HigherOrderDiboson=.True.
      End If    
      
     Case(522)
      If (wert.Ne.1._dp) Then
       PoleMassesInLoops=.False.
      Else
       PoleMassesInLoops=.True.
      End If      
      

     Case(525)
      If (wert.Ne.1._dp) Then
       WriteHiggsDiphotonLoopContributions=.False.
      Else
       WriteHiggsDiphotonLoopContributions=.True.
      End If

     Case(530)
      If (wert.Ne.1._dp) Then
       WriteTreeLevelTadpoleParameters=.False.
      Else
       WriteTreeLevelTadpoleParameters=.True.
      End If

     Case(550)
      If (wert.Ne.1._dp) Then
       CalcFT=.False.
      Else
       CalcFT=.True.
      End If

     Case(551)
      If (wert.Ne.1._dp) Then
       OneLoopFT=.False.
      Else
       OneLoopFT=.True.
      End If
! 
!      Case(600)  
!       Mass_Regulator_PhotonGluon = wert
!       
!      Case(610)  
!       If (wert.Ne.1._dp) Then
!        SquareFullAmplitudeDecays=.False.
!       Else
!        SquareFullAmplitudeDecays=.True.
!       End If      

     Case(990)
      If (wert.Ne.1._dp) Then
       MakeQTEST=.False.
      Else
       MakeQTEST=.True.
      End If
      

     Case(999)
      If (wert.Ne.1._dp) Then
       PrintDebugInformation=.False.
      Else
       PrintDebugInformation=.True.
      End If
 

    Case Default
      If (output_screen) Write(*,*) &
           & "Problem while reading SPhenoInput, ignoring unknown entry" &
           & ,i_par,wert
      Write(Errcan,*) &
          & "Problem while reading  SPhenoInput, ignoring unknown entry" &
               & ,i_par,wert
     End Select ! i_par

    End Do  ! i_par 

   200 Return

  End Subroutine Read_SPhenoInput
Subroutine Read_DecayOptions(io) 
Implicit None 
Integer,Intent(in) :: io 
Integer :: i_par, divset 
Real(dp) :: wert, divvalue 
Character(len=80) :: read_line 
Do 
Read(io,*,End=200,err=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*,End=200) i_par,wert ,read_line 
Select Case(i_par) 
Case(1) 
  If (wert.ne.1) Calc3BodyDecay_Fu= .False. 
Case(2) 
  If (wert.ne.1) Calc3BodyDecay_Fe= .False. 
Case(3) 
  If (wert.ne.1) Calc3BodyDecay_Fd= .False. 
Case(1000) 
  If (wert.eq.1) CalcLoopDecay_LoopInducedOnly = .True. 
Case(1001) 
  If (wert.ne.1) CalcLoopDecay_Fu= .False. 
Case(1002) 
  If (wert.ne.1) CalcLoopDecay_Fe= .False. 
Case(1003) 
  If (wert.ne.1) CalcLoopDecay_Fd= .False. 
Case(1004) 
  If (wert.ne.1) CalcLoopDecay_hh= .False. 
Case(1005) 
  If (wert.ne.1) CalcLoopDecay_H0= .False. 
Case(1006) 
  If (wert.ne.1) CalcLoopDecay_A0= .False. 
Case(1007) 
  If (wert.ne.1) CalcLoopDecay_Hp= .False. 
Case(1101) 
  divonly_save = wert ! divset = SetDivonlyAdd(INT(wert)) 
Case(1102) 
  divergence_save = wert ! divvalue = SetDivergenceAdd(wert) 
Case(1110) 
If (wert.Ne.1._dp) Then
  SimplisticLoopDecays=.False. 
Else
  SimplisticLoopDecays=.True.
End If 
Case(1111) 
If (wert.Ne.1._dp) Then
  ShiftIRdiv=.False. 
Else
  ShiftIRdiv=.True.
End If 
Case(1103) 
If (wert.Ne.1._dp) Then
  DebugLoopDecays=.False. 
Else
  DebugLoopDecays=.True.
End If 
Case(1104) 
If (wert.Ne.1._dp) Then
  OnlyTreeLevelContributions=.False. 
Else
  OnlyTreeLevelContributions=.True.
End If 
Case(1114) 
If (wert.Ne.0._dp) Then
  ExternalZfactors=.True. 
    If (wert.eq.1._dp) Then
     UseZeroRotationMatrices=.False.
     UseP2Matrices=.True.
    Else if (wert.eq.2._dp) Then  
     UseZeroRotationMatrices=.True.
     UseP2Matrices=.False.
    Else  
     UseZeroRotationMatrices=.False.
     UseP2Matrices=.False.
    End if  
Else
  ExternalZfactors=.False.
End If 
Case(1115) 
If (wert.Ne.1._dp) Then
  OSkinematics=.False. 
Else
  OSkinematics=.True.
End If 
Case(1116) 
If (wert.Ne.0._dp) Then
    If (wert.eq.1._dp) Then
     ewOSinDecays=.True.
     yukOSinDecays=.False.
    Else if (wert.eq.2._dp) Then  
     ewOSinDecays=.True.
     yukOSinDecays=.True.
    Else  
     ewOSinDecays=.False.
     yukOSinDecays=.False.
    End if  
Else
  yukOSinDecays=.False.
  ewOSinDecays=.False.
End If 
Case(1117) 
If (wert.Ne.1._dp) Then
  CTinLoopDecays=.False. 
Else
  CTinLoopDecays=.True.
End If 
Case(1118) 
If (wert.Ne.1._dp) Then
  LoopInducedDecaysOS=.False. 
Else
  LoopInducedDecaysOS=.True.
End If 
Case(1201) 
  Mass_Regulator_PhotonGluon=wert 
Case(1205) 
  Extra_scale_loopDecays = .true. 
  scale_loopdecays = wert 
Case Default 
 If (output_screen) Write(*,*)&
   & "Problem while reading DecayOptions, ignoring unknown entry"&
   &,i_par,wert
 Write(Errcan,*)&
   & "Problem while reading  DecayOptions, ignoring unknown entry"&
   &,i_par,wert 
End Select 
End Do! i_par 

200 Return 
End Subroutine Read_DecayOptions 


End Subroutine LesHouches_Input 
 
 
 
Subroutine LesHouches_Out(io_L,io,kont,M_GUT,Tpar,Spar,Upar,ae,amu,atau,              & 
& EDMe,EDMmu,EDMtau,dRho,GenerationMixing,f_name)

Implicit None 
Integer, Intent(in) :: io_L, io, kont
Real(dp),Intent(in) :: Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho

Real(dp), Intent(in) :: M_GUT
Character(len=8)::Datum 
Character(len=10)::Zeit 
Logical,Intent(in)::GenerationMixing 
Logical,Save::l_open= .True. 
Integer,Parameter::n_max=500 
Integer :: i1, i2 
Logical :: WriteNextBlock 
Character(len=30),Dimension(n_max)::Fnames,Lnames 
Character(len=*),Intent(in),Optional::f_name
Real(dp) :: Q, MassLSP(2), facPP, facGG, facPZ 
Integer :: CurrentPDG2(2), CurrentPDG3(3), PDGlsp(2) 
Integer::ierr,i_errors(1100),gt1,gt2,gt3,icount
Complex(dp) :: PDGhh,PDGG0,PDGH0,PDGA0,PDGHp(2),PDGVP,PDGVZ,PDGVG,PDGVWp,PDGgP,PDGgWp,               & 
& PDGgWpC,PDGgZ,PDGgG,PDGFd(3),PDGFu(3),PDGFe(3),PDGFv(3)

Character(len=30) :: NameParticlehh
Character(len=30) :: NameParticleG0
Character(len=30) :: NameParticleH0
Character(len=30) :: NameParticleA0
Character(len=30),Dimension(2):: NameParticleHp
Character(len=30) :: NameParticleVP
Character(len=30) :: NameParticleVZ
Character(len=30) :: NameParticleVG
Character(len=30) :: NameParticleVWp
Character(len=30) :: NameParticlegP
Character(len=30) :: NameParticlegWp
Character(len=30) :: NameParticlegWpC
Character(len=30) :: NameParticlegZ
Character(len=30) :: NameParticlegG
Character(len=30),Dimension(3):: NameParticleFd
Character(len=30),Dimension(3):: NameParticleFu
Character(len=30),Dimension(3):: NameParticleFe
Character(len=30),Dimension(3):: NameParticleFv
Complex(dp) :: Zbottom(2,2), Ztop(2,2), Ztau(2,2) 

 
 
 ! ----------- Set names and PDGs -------- 
 
PDGhh=25
NameParticlehh="hh"
PDGG0=0
NameParticleG0="G0"
PDGH0=35
NameParticleH0="H0"
PDGA0=36
NameParticleA0="A0"
PDGHp(1)=0
NameParticleHp(1)="Hp_1"
PDGHp(2)=37
NameParticleHp(2)="Hp_2"
PDGVP=22
NameParticleVP="VP"
PDGVZ=23
NameParticleVZ="VZ"
PDGVG=21
NameParticleVG="VG"
PDGVWp=24
NameParticleVWp="VWp"
PDGgP=0
NameParticlegP="gP"
PDGgWp=0
NameParticlegWp="gWp"
PDGgWpC=0
NameParticlegWpC="gWpC"
PDGgZ=0
NameParticlegZ="gZ"
PDGgG=0
NameParticlegG="gG"
PDGFd(1)=1
NameParticleFd(1)="Fd_1"
PDGFd(2)=3
NameParticleFd(2)="Fd_2"
PDGFd(3)=5
NameParticleFd(3)="Fd_3"
PDGFu(1)=2
NameParticleFu(1)="Fu_1"
PDGFu(2)=4
NameParticleFu(2)="Fu_2"
PDGFu(3)=6
NameParticleFu(3)="Fu_3"
PDGFe(1)=11
NameParticleFe(1)="Fe_1"
PDGFe(2)=13
NameParticleFe(2)="Fe_2"
PDGFe(3)=15
NameParticleFe(3)="Fe_3"
PDGFv(1)=12
NameParticleFv(1)="Fv_1"
PDGFv(2)=14
NameParticleFv(2)="Fv_2"
PDGFv(3)=16
NameParticleFv(3)="Fv_3"

 
 
 ! ----------- Use SLHA 1 conventions if demanded -------- 
 
If(WriteSLHA1) Write(*,*) "SLHA 1 output for given model not possible" 
Q=Sqrt(GetRenormalizationScale())
Call Date_and_time(datum,zeit)
If (l_open) Then
If (Present(f_name)) Then
Open(io_L,file=Trim(f_name),status="unknown")
Else
Open(io_L,file=outputFileName,status="unknown")
End If
l_open= .False.
End If
Write(io_L,100) "# SUSY Les Houches Accord 2 - Inert Spectrum + Decays + Flavor Observables"
Write(io_L,100) "# SPheno module generated by SARAH" 
Write(io_L,100) "# ----------------------------------------------------------------------" 
Write(io_L,100) "# SPheno "//version 
Write(io_L,100) "#   W. Porod, Comput. Phys. Commun. 153 (2003) 275-315, hep-ph/0301101"
Write(io_L,100) "#   W. Porod, F.Staub, Comput.Phys.Commun.183 (2012) 2458-2469, arXiv:1104.1573"
Write(io_L,100) "# SARAH: "//versionSARAH 
Write(io_L,100) "#   F. Staub; arXiv:0806.0538 (online manual)"
Write(io_L,100) "#   F. Staub; Comput. Phys. Commun. 181 (2010) 1077-1086; arXiv:0909.2863"
Write(io_L,100) "#   F. Staub; Comput. Phys. Commun. 182 (2011)  808-833; arXiv:1002.0840"
Write(io_L,100) "#   F. Staub; Comput. Phys. Commun. 184 (2013)  1792-1809; arXiv:1207.0906"
Write(io_L,100) "#   F. Staub; Comput. Phys. Commun. 185 (2014)  1773-1790; arXiv:1309.7223 "
Write(io_L,100) "# Including the calculation of flavor observables based on the FlavorKit "
Write(io_L,100) "#   W. Porod, F. Staub, A. Vicente; Eur.Phys.J. C74 (2014) 8, 2992; arXiv:1405.1434 "
Write(io_L,100) "# Two-loop masss corrections to Higgs fields based on "
Write(io_L,100) "#   M. D. Goodsell, K. Nickel, F. Staub; Eur.Phys.J. C75 (2015) no.6, 290; arXiv:1411.0675 "
Write(io_L,100) "#   M. D. Goodsell, K. Nickel, F. Staub; Eur.Phys.J. C75 (2015) no.1, 32; arXiv:1503.03098"
Write(io_L,100) "#   M. D. Goodsell, F. Staub; arXiv:1511.01904"
Write(io_L,100) "#  "
Write(io_L,100) "# in case of problems send email to florian.staub@kit.edu and goodsell@lpthe.jussieu.fr "
Write(io_L,100) "# ----------------------------------------------------------------------" 
Write(io_L,100) "# Created: "//Datum(7:8)//"."//Datum(5:6)//"."//Datum(1:4)&
&//",  "//Zeit(1:2)//":"//Zeit(3:4)
Write(io_L,100) "Block SPINFO         # Program information"
Write(io_L,100) "     1   SPhenoSARAH      # spectrum calculator"
Write(io_L,100) "     2   "//version//"    # version number of SPheno"
Write(io_L,100) "     9   "//versionSARAH//"    # version number of SARAH"
Write(io_L,100) "Block MODSEL  # Input parameters"
Write(io_L,110)  1, 1, " GUT scale input"
Write(io_L,110) 2, BoundaryCondition, " Boundary conditions "
If (i_cpv.Gt.0) Write(io_L,110) 5,i_cpv," switching on CP violation"
If (GenerationMixing) Write(io_L,110) &
&     6,1, " switching on flavour violation" 
Write(io_L,100) "Block MINPAR  # Input parameters"
Write(io_L,101) 1, Real(Lambda1IN,dp) ,"# Lambda1IN"
Write(io_L,101) 2, Real(Lambda2IN,dp) ,"# Lambda2IN"
Write(io_L,101) 3, Real(Lambda3IN,dp) ,"# Lambda3IN"
Write(io_L,101) 4, Real(Lambda4IN,dp) ,"# Lambda4IN"
Write(io_L,101) 5, Real(Lambda5IN,dp) ,"# Lambda5IN"
WriteNextBlock = .False. 
If (Abs(Aimag(Lambda1IN)).gt.0._dp) WriteNextBlock = .True. 
If (Abs(Aimag(Lambda2IN)).gt.0._dp) WriteNextBlock = .True. 
If (Abs(Aimag(Lambda3IN)).gt.0._dp) WriteNextBlock = .True. 
If (Abs(Aimag(Lambda4IN)).gt.0._dp) WriteNextBlock = .True. 
If (Abs(Aimag(Lambda5IN)).gt.0._dp) WriteNextBlock = .True. 
If(WriteNextBlock) Then 
Write(io_L,100) "Block IMMINPAR  # Input parameters"
If (Abs(Aimag(Lambda1IN)).gt.0._dp) Then 
Write(io_L,101) 1, Aimag(Lambda1IN) ,"# Lambda1IN"
End if 
If (Abs(Aimag(Lambda2IN)).gt.0._dp) Then 
Write(io_L,101) 2, Aimag(Lambda2IN) ,"# Lambda2IN"
End if 
If (Abs(Aimag(Lambda3IN)).gt.0._dp) Then 
Write(io_L,101) 3, Aimag(Lambda3IN) ,"# Lambda3IN"
End if 
If (Abs(Aimag(Lambda4IN)).gt.0._dp) Then 
Write(io_L,101) 4, Aimag(Lambda4IN) ,"# Lambda4IN"
End if 
If (Abs(Aimag(Lambda5IN)).gt.0._dp) Then 
Write(io_L,101) 5, Aimag(Lambda5IN) ,"# Lambda5IN"
End if 
End if 
Write(io_L,106) "Block gaugeGUT Q=",m_GUT,"# (GUT scale)" 
Write(io_L,104) 1,g1GUT, "# g1(Q)" 
Write(io_L,104) 2,g2GUT, "# g2(Q)" 
Write(io_L,104) 3,g3GUT, "# g3(Q)" 
Write(io_L,100) "Block SMINPUTS  # SM parameters"
Write(io_L,102) 1,1._dp/alpha_MZ,"# alpha_em^-1(MZ)^MSbar"
Write(io_L,102) 2,G_F,"# G_mu [GeV^-2]"
Write(io_L,102) 3,alphaS_MZ,"# alpha_s(MZ)^MSbar"
Write(io_L,102) 4,mZ,"# m_Z(pole)"
Write(io_L,102) 5,mf_d(3),"# m_b(m_b), MSbar"
Write(io_L,102) 6,mf_u(3),"# m_t(pole)"
Write(io_L,102) 7,mf_l(3),"# m_tau(pole)"
 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block GAUGE Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 1,Real(g1,dp), "# g1" 
Write(io_L,104) 2,Real(g2,dp), "# g2" 
Write(io_L,104) 3,Real(g3,dp), "# g3" 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block HDM Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 5,Real(Lam5,dp), "# Lam5" 
If (Abs(Aimag(Lam5)).gt.0._dp) WriteNextBlock = .True. 
Write(io_L,104) 1,Real(Lam1,dp), "# Lam1" 
If (Abs(Aimag(Lam1)).gt.0._dp) WriteNextBlock = .True. 
Write(io_L,104) 4,Real(Lam4,dp), "# Lam4" 
If (Abs(Aimag(Lam4)).gt.0._dp) WriteNextBlock = .True. 
Write(io_L,104) 3,Real(Lam3,dp), "# Lam3" 
If (Abs(Aimag(Lam3)).gt.0._dp) WriteNextBlock = .True. 
Write(io_L,104) 2,Real(Lam2,dp), "# Lam2" 
If (Abs(Aimag(Lam2)).gt.0._dp) WriteNextBlock = .True. 
If(WriteNextBlock) Then 
Write(io_L,106) "Block IMHDM Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 5,Aimag(Lam5), "# Lam5" 
Write(io_L,104) 1,Aimag(Lam1), "# Lam1" 
Write(io_L,104) 4,Aimag(Lam4), "# Lam4" 
Write(io_L,104) 3,Aimag(Lam3), "# Lam3" 
Write(io_L,104) 2,Aimag(Lam2), "# Lam2" 
End if 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block MSOFT Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 21,Real(mHd2,dp), "# mHd2" 
Write(io_L,104) 22,Real(mHu2,dp), "# mHu2" 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block HMIX Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 3,Real(v,dp), "# v" 
Write(io_L,104) 10,Real(ASin(Abs(ZP(1,2))),dp), "# betaH" 
If (WriteTreeLevelTadpoleParameters) Then 
If (HighScaleModel.Eq."LOW") Then 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block TREEMSOFT Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 21,Real(mHd2Tree,dp), "# mHd2" 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block LOOPMSOFT Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 21,Real(mHd21L,dp), "# mHd2" 
Else 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block TREEMSOFT Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 21,Real(mHd2Tree,dp), "# mHd2" 
WriteNextBlock = .false. 
If (OutputForMG) WriteNextBlock = .True. 
Write(io_L,106) "Block LOOPMSOFT Q=",Q,"# (Renormalization Scale)" 
Write(io_L,104) 21,Real(mHd21L,dp), "# mHd2" 
End if 
End if 
Write(io_L,106) "Block Ye Q=",Q,"# (Renormalization Scale)" 
Write(io_L,107)1,1,Real(Ye(1,1),dp), "# Real(Ye(1,1),dp)" 
Write(io_L,107)1,2,Real(Ye(1,2),dp), "# Real(Ye(1,2),dp)" 
Write(io_L,107)1,3,Real(Ye(1,3),dp), "# Real(Ye(1,3),dp)" 
Write(io_L,107)2,1,Real(Ye(2,1),dp), "# Real(Ye(2,1),dp)" 
Write(io_L,107)2,2,Real(Ye(2,2),dp), "# Real(Ye(2,2),dp)" 
Write(io_L,107)2,3,Real(Ye(2,3),dp), "# Real(Ye(2,3),dp)" 
Write(io_L,107)3,1,Real(Ye(3,1),dp), "# Real(Ye(3,1),dp)" 
Write(io_L,107)3,2,Real(Ye(3,2),dp), "# Real(Ye(3,2),dp)" 
Write(io_L,107)3,3,Real(Ye(3,3),dp), "# Real(Ye(3,3),dp)" 
If ((MaxVal(Abs(AImag(Ye))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMYe Q=",Q,"# (Renormalization Scale)" 
Write(io_L,107)1,1,Aimag(Ye(1,1)), "# Aimag(Ye(1,1))" 
Write(io_L,107)1,2,Aimag(Ye(1,2)), "# Aimag(Ye(1,2))" 
Write(io_L,107)1,3,Aimag(Ye(1,3)), "# Aimag(Ye(1,3))" 
Write(io_L,107)2,1,Aimag(Ye(2,1)), "# Aimag(Ye(2,1))" 
Write(io_L,107)2,2,Aimag(Ye(2,2)), "# Aimag(Ye(2,2))" 
Write(io_L,107)2,3,Aimag(Ye(2,3)), "# Aimag(Ye(2,3))" 
Write(io_L,107)3,1,Aimag(Ye(3,1)), "# Aimag(Ye(3,1))" 
Write(io_L,107)3,2,Aimag(Ye(3,2)), "# Aimag(Ye(3,2))" 
Write(io_L,107)3,3,Aimag(Ye(3,3)), "# Aimag(Ye(3,3))" 
End If 

Write(io_L,106) "Block Yd Q=",Q,"# (Renormalization Scale)" 
Write(io_L,107)1,1,Real(Yd(1,1),dp), "# Real(Yd(1,1),dp)" 
Write(io_L,107)1,2,Real(Yd(1,2),dp), "# Real(Yd(1,2),dp)" 
Write(io_L,107)1,3,Real(Yd(1,3),dp), "# Real(Yd(1,3),dp)" 
Write(io_L,107)2,1,Real(Yd(2,1),dp), "# Real(Yd(2,1),dp)" 
Write(io_L,107)2,2,Real(Yd(2,2),dp), "# Real(Yd(2,2),dp)" 
Write(io_L,107)2,3,Real(Yd(2,3),dp), "# Real(Yd(2,3),dp)" 
Write(io_L,107)3,1,Real(Yd(3,1),dp), "# Real(Yd(3,1),dp)" 
Write(io_L,107)3,2,Real(Yd(3,2),dp), "# Real(Yd(3,2),dp)" 
Write(io_L,107)3,3,Real(Yd(3,3),dp), "# Real(Yd(3,3),dp)" 
If ((MaxVal(Abs(AImag(Yd))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMYd Q=",Q,"# (Renormalization Scale)" 
Write(io_L,107)1,1,Aimag(Yd(1,1)), "# Aimag(Yd(1,1))" 
Write(io_L,107)1,2,Aimag(Yd(1,2)), "# Aimag(Yd(1,2))" 
Write(io_L,107)1,3,Aimag(Yd(1,3)), "# Aimag(Yd(1,3))" 
Write(io_L,107)2,1,Aimag(Yd(2,1)), "# Aimag(Yd(2,1))" 
Write(io_L,107)2,2,Aimag(Yd(2,2)), "# Aimag(Yd(2,2))" 
Write(io_L,107)2,3,Aimag(Yd(2,3)), "# Aimag(Yd(2,3))" 
Write(io_L,107)3,1,Aimag(Yd(3,1)), "# Aimag(Yd(3,1))" 
Write(io_L,107)3,2,Aimag(Yd(3,2)), "# Aimag(Yd(3,2))" 
Write(io_L,107)3,3,Aimag(Yd(3,3)), "# Aimag(Yd(3,3))" 
End If 

Write(io_L,106) "Block Yu Q=",Q,"# (Renormalization Scale)" 
Write(io_L,107)1,1,Real(Yu(1,1),dp), "# Real(Yu(1,1),dp)" 
Write(io_L,107)1,2,Real(Yu(1,2),dp), "# Real(Yu(1,2),dp)" 
Write(io_L,107)1,3,Real(Yu(1,3),dp), "# Real(Yu(1,3),dp)" 
Write(io_L,107)2,1,Real(Yu(2,1),dp), "# Real(Yu(2,1),dp)" 
Write(io_L,107)2,2,Real(Yu(2,2),dp), "# Real(Yu(2,2),dp)" 
Write(io_L,107)2,3,Real(Yu(2,3),dp), "# Real(Yu(2,3),dp)" 
Write(io_L,107)3,1,Real(Yu(3,1),dp), "# Real(Yu(3,1),dp)" 
Write(io_L,107)3,2,Real(Yu(3,2),dp), "# Real(Yu(3,2),dp)" 
Write(io_L,107)3,3,Real(Yu(3,3),dp), "# Real(Yu(3,3),dp)" 
If ((MaxVal(Abs(AImag(Yu))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMYu Q=",Q,"# (Renormalization Scale)" 
Write(io_L,107)1,1,Aimag(Yu(1,1)), "# Aimag(Yu(1,1))" 
Write(io_L,107)1,2,Aimag(Yu(1,2)), "# Aimag(Yu(1,2))" 
Write(io_L,107)1,3,Aimag(Yu(1,3)), "# Aimag(Yu(1,3))" 
Write(io_L,107)2,1,Aimag(Yu(2,1)), "# Aimag(Yu(2,1))" 
Write(io_L,107)2,2,Aimag(Yu(2,2)), "# Aimag(Yu(2,2))" 
Write(io_L,107)2,3,Aimag(Yu(2,3)), "# Aimag(Yu(2,3))" 
Write(io_L,107)3,1,Aimag(Yu(3,1)), "# Aimag(Yu(3,1))" 
Write(io_L,107)3,2,Aimag(Yu(3,2)), "# Aimag(Yu(3,2))" 
Write(io_L,107)3,3,Aimag(Yu(3,3)), "# Aimag(Yu(3,3))" 
End If 

If (WriteGUTvalues) Then 
Write(io_L,106) "Block GAUGEGUT Q=",M_GUT,"# (GUT scale)" 
Write(io_L,104) 1,Real(g1GUT,dp), "# g1" 
Write(io_L,104) 2,Real(g2GUT,dp), "# g2" 
Write(io_L,104) 3,Real(g3GUT,dp), "# g3" 
Write(io_L,106) "Block HDMGUT Q=",M_GUT,"# (GUT scale)" 
Write(io_L,104) 5,Real(Lam5GUT,dp), "# Lam5" 
Write(io_L,104) 1,Real(Lam1GUT,dp), "# Lam1" 
Write(io_L,104) 4,Real(Lam4GUT,dp), "# Lam4" 
Write(io_L,104) 3,Real(Lam3GUT,dp), "# Lam3" 
Write(io_L,104) 2,Real(Lam2GUT,dp), "# Lam2" 
Write(io_L,106) "Block MSOFTGUT Q=",M_GUT,"# (GUT scale)" 
Write(io_L,104) 21,Real(mHd2GUT,dp), "# mHd2" 
Write(io_L,104) 22,Real(mHu2GUT,dp), "# mHu2" 
Write(io_L,106) "Block YeGUT Q=",M_GUT,"# (GUT Scale)" 
Write(io_L,107)1,1,Real(YeGUT(1,1),dp), "# Real(YeGUT(1,1),dp)" 
Write(io_L,107)1,2,Real(YeGUT(1,2),dp), "# Real(YeGUT(1,2),dp)" 
Write(io_L,107)1,3,Real(YeGUT(1,3),dp), "# Real(YeGUT(1,3),dp)" 
Write(io_L,107)2,1,Real(YeGUT(2,1),dp), "# Real(YeGUT(2,1),dp)" 
Write(io_L,107)2,2,Real(YeGUT(2,2),dp), "# Real(YeGUT(2,2),dp)" 
Write(io_L,107)2,3,Real(YeGUT(2,3),dp), "# Real(YeGUT(2,3),dp)" 
Write(io_L,107)3,1,Real(YeGUT(3,1),dp), "# Real(YeGUT(3,1),dp)" 
Write(io_L,107)3,2,Real(YeGUT(3,2),dp), "# Real(YeGUT(3,2),dp)" 
Write(io_L,107)3,3,Real(YeGUT(3,3),dp), "# Real(YeGUT(3,3),dp)" 
If ((MaxVal(Abs(AImag(YeGUT))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMYeGUT Q=",M_GUT,"# (GUT Scale)" 
Write(io_L,107)1,1,Aimag(YeGUT(1,1)), "# Aimag(YeGUT(1,1))" 
Write(io_L,107)1,2,Aimag(YeGUT(1,2)), "# Aimag(YeGUT(1,2))" 
Write(io_L,107)1,3,Aimag(YeGUT(1,3)), "# Aimag(YeGUT(1,3))" 
Write(io_L,107)2,1,Aimag(YeGUT(2,1)), "# Aimag(YeGUT(2,1))" 
Write(io_L,107)2,2,Aimag(YeGUT(2,2)), "# Aimag(YeGUT(2,2))" 
Write(io_L,107)2,3,Aimag(YeGUT(2,3)), "# Aimag(YeGUT(2,3))" 
Write(io_L,107)3,1,Aimag(YeGUT(3,1)), "# Aimag(YeGUT(3,1))" 
Write(io_L,107)3,2,Aimag(YeGUT(3,2)), "# Aimag(YeGUT(3,2))" 
Write(io_L,107)3,3,Aimag(YeGUT(3,3)), "# Aimag(YeGUT(3,3))" 
End If 

Write(io_L,106) "Block YdGUT Q=",M_GUT,"# (GUT Scale)" 
Write(io_L,107)1,1,Real(YdGUT(1,1),dp), "# Real(YdGUT(1,1),dp)" 
Write(io_L,107)1,2,Real(YdGUT(1,2),dp), "# Real(YdGUT(1,2),dp)" 
Write(io_L,107)1,3,Real(YdGUT(1,3),dp), "# Real(YdGUT(1,3),dp)" 
Write(io_L,107)2,1,Real(YdGUT(2,1),dp), "# Real(YdGUT(2,1),dp)" 
Write(io_L,107)2,2,Real(YdGUT(2,2),dp), "# Real(YdGUT(2,2),dp)" 
Write(io_L,107)2,3,Real(YdGUT(2,3),dp), "# Real(YdGUT(2,3),dp)" 
Write(io_L,107)3,1,Real(YdGUT(3,1),dp), "# Real(YdGUT(3,1),dp)" 
Write(io_L,107)3,2,Real(YdGUT(3,2),dp), "# Real(YdGUT(3,2),dp)" 
Write(io_L,107)3,3,Real(YdGUT(3,3),dp), "# Real(YdGUT(3,3),dp)" 
If ((MaxVal(Abs(AImag(YdGUT))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMYdGUT Q=",M_GUT,"# (GUT Scale)" 
Write(io_L,107)1,1,Aimag(YdGUT(1,1)), "# Aimag(YdGUT(1,1))" 
Write(io_L,107)1,2,Aimag(YdGUT(1,2)), "# Aimag(YdGUT(1,2))" 
Write(io_L,107)1,3,Aimag(YdGUT(1,3)), "# Aimag(YdGUT(1,3))" 
Write(io_L,107)2,1,Aimag(YdGUT(2,1)), "# Aimag(YdGUT(2,1))" 
Write(io_L,107)2,2,Aimag(YdGUT(2,2)), "# Aimag(YdGUT(2,2))" 
Write(io_L,107)2,3,Aimag(YdGUT(2,3)), "# Aimag(YdGUT(2,3))" 
Write(io_L,107)3,1,Aimag(YdGUT(3,1)), "# Aimag(YdGUT(3,1))" 
Write(io_L,107)3,2,Aimag(YdGUT(3,2)), "# Aimag(YdGUT(3,2))" 
Write(io_L,107)3,3,Aimag(YdGUT(3,3)), "# Aimag(YdGUT(3,3))" 
End If 

Write(io_L,106) "Block YuGUT Q=",M_GUT,"# (GUT Scale)" 
Write(io_L,107)1,1,Real(YuGUT(1,1),dp), "# Real(YuGUT(1,1),dp)" 
Write(io_L,107)1,2,Real(YuGUT(1,2),dp), "# Real(YuGUT(1,2),dp)" 
Write(io_L,107)1,3,Real(YuGUT(1,3),dp), "# Real(YuGUT(1,3),dp)" 
Write(io_L,107)2,1,Real(YuGUT(2,1),dp), "# Real(YuGUT(2,1),dp)" 
Write(io_L,107)2,2,Real(YuGUT(2,2),dp), "# Real(YuGUT(2,2),dp)" 
Write(io_L,107)2,3,Real(YuGUT(2,3),dp), "# Real(YuGUT(2,3),dp)" 
Write(io_L,107)3,1,Real(YuGUT(3,1),dp), "# Real(YuGUT(3,1),dp)" 
Write(io_L,107)3,2,Real(YuGUT(3,2),dp), "# Real(YuGUT(3,2),dp)" 
Write(io_L,107)3,3,Real(YuGUT(3,3),dp), "# Real(YuGUT(3,3),dp)" 
If ((MaxVal(Abs(AImag(YuGUT))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMYuGUT Q=",M_GUT,"# (GUT Scale)" 
Write(io_L,107)1,1,Aimag(YuGUT(1,1)), "# Aimag(YuGUT(1,1))" 
Write(io_L,107)1,2,Aimag(YuGUT(1,2)), "# Aimag(YuGUT(1,2))" 
Write(io_L,107)1,3,Aimag(YuGUT(1,3)), "# Aimag(YuGUT(1,3))" 
Write(io_L,107)2,1,Aimag(YuGUT(2,1)), "# Aimag(YuGUT(2,1))" 
Write(io_L,107)2,2,Aimag(YuGUT(2,2)), "# Aimag(YuGUT(2,2))" 
Write(io_L,107)2,3,Aimag(YuGUT(2,3)), "# Aimag(YuGUT(2,3))" 
Write(io_L,107)3,1,Aimag(YuGUT(3,1)), "# Aimag(YuGUT(3,1))" 
Write(io_L,107)3,2,Aimag(YuGUT(3,2)), "# Aimag(YuGUT(3,2))" 
Write(io_L,107)3,3,Aimag(YuGUT(3,3)), "# Aimag(YuGUT(3,3))" 
End If 

End if 
 
MassLSP = 100000._dp 
Write(io_L,100) "Block MASS  # Mass spectrum"
Write(io_L,100) "#   PDG code      mass          particle" 
 Write(io_L,102) 25,Mhh,"# hh" 
 Write(io_L,102) 35,MH0,"# H0" 
If (MassLSP(1).gt.Abs(MH0)) Then 
PDGLSP(2) = PDGLSP(1) 
PDGLSP(1) = 35 
MassLSP(2) = MassLSP(1) 
MassLSP(1) = Abs(MH0)
Else 
If (MassLSP(2).gt.Abs(MH0)) Then 
PDGLSP(2) = 35 
MassLSP(2) = Abs(MH0)
End if 
End if 
 Write(io_L,102) 36,MA0,"# A0" 
If (MassLSP(1).gt.Abs(MA0)) Then 
PDGLSP(2) = PDGLSP(1) 
PDGLSP(1) = 36 
MassLSP(2) = MassLSP(1) 
MassLSP(1) = Abs(MA0)
Else 
If (MassLSP(2).gt.Abs(MA0)) Then 
PDGLSP(2) = 36 
MassLSP(2) = Abs(MA0)
End if 
End if 
 Write(io_L,102) INT(Abs(PDGHp(2))),MHp(2),"# "//Trim(NameParticleHp(2))// "" 
If (OutputForMG)  Write(io_L,102) 22,0._dp,"# VP" 
 Write(io_L,102) 23,MVZ,"# VZ" 
If (OutputForMG)  Write(io_L,102) 21,0._dp,"# VG" 
 Write(io_L,102) 24,MVWp,"# VWp" 
 Write(io_L,102) INT(Abs(PDGFd(1))),MFd(1),"# "//Trim(NameParticleFd(1))// "" 
 Write(io_L,102) INT(Abs(PDGFd(2))),MFd(2),"# "//Trim(NameParticleFd(2))// "" 
 Write(io_L,102) INT(Abs(PDGFd(3))),MFd(3),"# "//Trim(NameParticleFd(3))// "" 
 Write(io_L,102) INT(Abs(PDGFu(1))),MFu(1),"# "//Trim(NameParticleFu(1))// "" 
 Write(io_L,102) INT(Abs(PDGFu(2))),MFu(2),"# "//Trim(NameParticleFu(2))// "" 
 Write(io_L,102) INT(Abs(PDGFu(3))),MFu(3),"# "//Trim(NameParticleFu(3))// "" 
 Write(io_L,102) INT(Abs(PDGFe(1))),MFe(1),"# "//Trim(NameParticleFe(1))// "" 
 Write(io_L,102) INT(Abs(PDGFe(2))),MFe(2),"# "//Trim(NameParticleFe(2))// "" 
 Write(io_L,102) INT(Abs(PDGFe(3))),MFe(3),"# "//Trim(NameParticleFe(3))// "" 
If (OutputForMG) Write(io_L,102) INT(Abs(PDGFv(1))),0._dp,"# "//Trim(NameParticleFv(1))// "" 
If (OutputForMG) Write(io_L,102) INT(Abs(PDGFv(2))),0._dp,"# "//Trim(NameParticleFv(2))// "" 
If (OutputForMG) Write(io_L,102) INT(Abs(PDGFv(3))),0._dp,"# "//Trim(NameParticleFv(3))// "" 

 
If (GetMassUncertainty) Then
Write(io_L,100) "Block DMASS  # Overall uncertainty"
 Write(io_L,102) INT(Abs(37)), Sqrt(mass_uncertainty_Q(2)**2+mass_uncertainty_Yt(2)**2),"# MHp(2) " 
 Write(io_L,102) INT(Abs(25)), Sqrt(mass_uncertainty_Q(4)**2+mass_uncertainty_Yt(4)**2),"# Mhh(1) " 
 Write(io_L,102) INT(Abs(36)), Sqrt(mass_uncertainty_Q(5)**2+mass_uncertainty_Yt(5)**2),"# MA0(1) " 
 Write(io_L,102) INT(Abs(35)), Sqrt(mass_uncertainty_Q(6)**2+mass_uncertainty_Yt(6)**2),"# MH0(1) " 
Write(io_L,100) "Block DMASSQ  # Scale uncertainty"
 Write(io_L,102) INT(Abs(37)), mass_uncertainty_Q(2),"# MHp(2) " 
 Write(io_L,102) INT(Abs(25)), mass_uncertainty_Q(4),"# Mhh(1) " 
 Write(io_L,102) INT(Abs(36)), mass_uncertainty_Q(5),"# MA0(1) " 
 Write(io_L,102) INT(Abs(35)), mass_uncertainty_Q(6),"# MH0(1) " 
Write(io_L,100) "Block DMASST  # Top Matching uncertainty"
 Write(io_L,102) INT(Abs(37)), mass_uncertainty_Yt(2),"# MHp(2) " 
 Write(io_L,102) INT(Abs(25)), mass_uncertainty_Yt(4),"# Mhh(1) " 
 Write(io_L,102) INT(Abs(36)), mass_uncertainty_Yt(5),"# MA0(1) " 
 Write(io_L,102) INT(Abs(35)), mass_uncertainty_Yt(6),"# MH0(1) " 
End if
Write(io_L,106) "Block CHARGEMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,ZP(1,1), "# ZP(1,1)" 
Write(io_L,107)1,2,ZP(1,2), "# ZP(1,2)" 
Write(io_L,107)2,1,ZP(2,1), "# ZP(2,1)" 
Write(io_L,107)2,2,ZP(2,2), "# ZP(2,2)" 
Write(io_L,106) "Block UDLMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Real(ZDL(1,1),dp), "# Real(ZDL(1,1),dp)" 
Write(io_L,107)1,2,Real(ZDL(1,2),dp), "# Real(ZDL(1,2),dp)" 
Write(io_L,107)1,3,Real(ZDL(1,3),dp), "# Real(ZDL(1,3),dp)" 
Write(io_L,107)2,1,Real(ZDL(2,1),dp), "# Real(ZDL(2,1),dp)" 
Write(io_L,107)2,2,Real(ZDL(2,2),dp), "# Real(ZDL(2,2),dp)" 
Write(io_L,107)2,3,Real(ZDL(2,3),dp), "# Real(ZDL(2,3),dp)" 
Write(io_L,107)3,1,Real(ZDL(3,1),dp), "# Real(ZDL(3,1),dp)" 
Write(io_L,107)3,2,Real(ZDL(3,2),dp), "# Real(ZDL(3,2),dp)" 
Write(io_L,107)3,3,Real(ZDL(3,3),dp), "# Real(ZDL(3,3),dp)" 
If ((MaxVal(Abs(AImag(ZDL))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMUDLMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Aimag(ZDL(1,1)), "# Aimag(ZDL(1,1))" 
Write(io_L,107)1,2,Aimag(ZDL(1,2)), "# Aimag(ZDL(1,2))" 
Write(io_L,107)1,3,Aimag(ZDL(1,3)), "# Aimag(ZDL(1,3))" 
Write(io_L,107)2,1,Aimag(ZDL(2,1)), "# Aimag(ZDL(2,1))" 
Write(io_L,107)2,2,Aimag(ZDL(2,2)), "# Aimag(ZDL(2,2))" 
Write(io_L,107)2,3,Aimag(ZDL(2,3)), "# Aimag(ZDL(2,3))" 
Write(io_L,107)3,1,Aimag(ZDL(3,1)), "# Aimag(ZDL(3,1))" 
Write(io_L,107)3,2,Aimag(ZDL(3,2)), "# Aimag(ZDL(3,2))" 
Write(io_L,107)3,3,Aimag(ZDL(3,3)), "# Aimag(ZDL(3,3))" 
End If 

Write(io_L,106) "Block UDRMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Real(ZDR(1,1),dp), "# Real(ZDR(1,1),dp)" 
Write(io_L,107)1,2,Real(ZDR(1,2),dp), "# Real(ZDR(1,2),dp)" 
Write(io_L,107)1,3,Real(ZDR(1,3),dp), "# Real(ZDR(1,3),dp)" 
Write(io_L,107)2,1,Real(ZDR(2,1),dp), "# Real(ZDR(2,1),dp)" 
Write(io_L,107)2,2,Real(ZDR(2,2),dp), "# Real(ZDR(2,2),dp)" 
Write(io_L,107)2,3,Real(ZDR(2,3),dp), "# Real(ZDR(2,3),dp)" 
Write(io_L,107)3,1,Real(ZDR(3,1),dp), "# Real(ZDR(3,1),dp)" 
Write(io_L,107)3,2,Real(ZDR(3,2),dp), "# Real(ZDR(3,2),dp)" 
Write(io_L,107)3,3,Real(ZDR(3,3),dp), "# Real(ZDR(3,3),dp)" 
If ((MaxVal(Abs(AImag(ZDR))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMUDRMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Aimag(ZDR(1,1)), "# Aimag(ZDR(1,1))" 
Write(io_L,107)1,2,Aimag(ZDR(1,2)), "# Aimag(ZDR(1,2))" 
Write(io_L,107)1,3,Aimag(ZDR(1,3)), "# Aimag(ZDR(1,3))" 
Write(io_L,107)2,1,Aimag(ZDR(2,1)), "# Aimag(ZDR(2,1))" 
Write(io_L,107)2,2,Aimag(ZDR(2,2)), "# Aimag(ZDR(2,2))" 
Write(io_L,107)2,3,Aimag(ZDR(2,3)), "# Aimag(ZDR(2,3))" 
Write(io_L,107)3,1,Aimag(ZDR(3,1)), "# Aimag(ZDR(3,1))" 
Write(io_L,107)3,2,Aimag(ZDR(3,2)), "# Aimag(ZDR(3,2))" 
Write(io_L,107)3,3,Aimag(ZDR(3,3)), "# Aimag(ZDR(3,3))" 
End If 

Write(io_L,106) "Block UULMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Real(ZUL(1,1),dp), "# Real(ZUL(1,1),dp)" 
Write(io_L,107)1,2,Real(ZUL(1,2),dp), "# Real(ZUL(1,2),dp)" 
Write(io_L,107)1,3,Real(ZUL(1,3),dp), "# Real(ZUL(1,3),dp)" 
Write(io_L,107)2,1,Real(ZUL(2,1),dp), "# Real(ZUL(2,1),dp)" 
Write(io_L,107)2,2,Real(ZUL(2,2),dp), "# Real(ZUL(2,2),dp)" 
Write(io_L,107)2,3,Real(ZUL(2,3),dp), "# Real(ZUL(2,3),dp)" 
Write(io_L,107)3,1,Real(ZUL(3,1),dp), "# Real(ZUL(3,1),dp)" 
Write(io_L,107)3,2,Real(ZUL(3,2),dp), "# Real(ZUL(3,2),dp)" 
Write(io_L,107)3,3,Real(ZUL(3,3),dp), "# Real(ZUL(3,3),dp)" 
If ((MaxVal(Abs(AImag(ZUL))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMUULMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Aimag(ZUL(1,1)), "# Aimag(ZUL(1,1))" 
Write(io_L,107)1,2,Aimag(ZUL(1,2)), "# Aimag(ZUL(1,2))" 
Write(io_L,107)1,3,Aimag(ZUL(1,3)), "# Aimag(ZUL(1,3))" 
Write(io_L,107)2,1,Aimag(ZUL(2,1)), "# Aimag(ZUL(2,1))" 
Write(io_L,107)2,2,Aimag(ZUL(2,2)), "# Aimag(ZUL(2,2))" 
Write(io_L,107)2,3,Aimag(ZUL(2,3)), "# Aimag(ZUL(2,3))" 
Write(io_L,107)3,1,Aimag(ZUL(3,1)), "# Aimag(ZUL(3,1))" 
Write(io_L,107)3,2,Aimag(ZUL(3,2)), "# Aimag(ZUL(3,2))" 
Write(io_L,107)3,3,Aimag(ZUL(3,3)), "# Aimag(ZUL(3,3))" 
End If 

Write(io_L,106) "Block UURMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Real(ZUR(1,1),dp), "# Real(ZUR(1,1),dp)" 
Write(io_L,107)1,2,Real(ZUR(1,2),dp), "# Real(ZUR(1,2),dp)" 
Write(io_L,107)1,3,Real(ZUR(1,3),dp), "# Real(ZUR(1,3),dp)" 
Write(io_L,107)2,1,Real(ZUR(2,1),dp), "# Real(ZUR(2,1),dp)" 
Write(io_L,107)2,2,Real(ZUR(2,2),dp), "# Real(ZUR(2,2),dp)" 
Write(io_L,107)2,3,Real(ZUR(2,3),dp), "# Real(ZUR(2,3),dp)" 
Write(io_L,107)3,1,Real(ZUR(3,1),dp), "# Real(ZUR(3,1),dp)" 
Write(io_L,107)3,2,Real(ZUR(3,2),dp), "# Real(ZUR(3,2),dp)" 
Write(io_L,107)3,3,Real(ZUR(3,3),dp), "# Real(ZUR(3,3),dp)" 
If ((MaxVal(Abs(AImag(ZUR))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMUURMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Aimag(ZUR(1,1)), "# Aimag(ZUR(1,1))" 
Write(io_L,107)1,2,Aimag(ZUR(1,2)), "# Aimag(ZUR(1,2))" 
Write(io_L,107)1,3,Aimag(ZUR(1,3)), "# Aimag(ZUR(1,3))" 
Write(io_L,107)2,1,Aimag(ZUR(2,1)), "# Aimag(ZUR(2,1))" 
Write(io_L,107)2,2,Aimag(ZUR(2,2)), "# Aimag(ZUR(2,2))" 
Write(io_L,107)2,3,Aimag(ZUR(2,3)), "# Aimag(ZUR(2,3))" 
Write(io_L,107)3,1,Aimag(ZUR(3,1)), "# Aimag(ZUR(3,1))" 
Write(io_L,107)3,2,Aimag(ZUR(3,2)), "# Aimag(ZUR(3,2))" 
Write(io_L,107)3,3,Aimag(ZUR(3,3)), "# Aimag(ZUR(3,3))" 
End If 

Write(io_L,106) "Block UELMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Real(ZEL(1,1),dp), "# Real(ZEL(1,1),dp)" 
Write(io_L,107)1,2,Real(ZEL(1,2),dp), "# Real(ZEL(1,2),dp)" 
Write(io_L,107)1,3,Real(ZEL(1,3),dp), "# Real(ZEL(1,3),dp)" 
Write(io_L,107)2,1,Real(ZEL(2,1),dp), "# Real(ZEL(2,1),dp)" 
Write(io_L,107)2,2,Real(ZEL(2,2),dp), "# Real(ZEL(2,2),dp)" 
Write(io_L,107)2,3,Real(ZEL(2,3),dp), "# Real(ZEL(2,3),dp)" 
Write(io_L,107)3,1,Real(ZEL(3,1),dp), "# Real(ZEL(3,1),dp)" 
Write(io_L,107)3,2,Real(ZEL(3,2),dp), "# Real(ZEL(3,2),dp)" 
Write(io_L,107)3,3,Real(ZEL(3,3),dp), "# Real(ZEL(3,3),dp)" 
If ((MaxVal(Abs(AImag(ZEL))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMUELMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Aimag(ZEL(1,1)), "# Aimag(ZEL(1,1))" 
Write(io_L,107)1,2,Aimag(ZEL(1,2)), "# Aimag(ZEL(1,2))" 
Write(io_L,107)1,3,Aimag(ZEL(1,3)), "# Aimag(ZEL(1,3))" 
Write(io_L,107)2,1,Aimag(ZEL(2,1)), "# Aimag(ZEL(2,1))" 
Write(io_L,107)2,2,Aimag(ZEL(2,2)), "# Aimag(ZEL(2,2))" 
Write(io_L,107)2,3,Aimag(ZEL(2,3)), "# Aimag(ZEL(2,3))" 
Write(io_L,107)3,1,Aimag(ZEL(3,1)), "# Aimag(ZEL(3,1))" 
Write(io_L,107)3,2,Aimag(ZEL(3,2)), "# Aimag(ZEL(3,2))" 
Write(io_L,107)3,3,Aimag(ZEL(3,3)), "# Aimag(ZEL(3,3))" 
End If 

Write(io_L,106) "Block UERMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Real(ZER(1,1),dp), "# Real(ZER(1,1),dp)" 
Write(io_L,107)1,2,Real(ZER(1,2),dp), "# Real(ZER(1,2),dp)" 
Write(io_L,107)1,3,Real(ZER(1,3),dp), "# Real(ZER(1,3),dp)" 
Write(io_L,107)2,1,Real(ZER(2,1),dp), "# Real(ZER(2,1),dp)" 
Write(io_L,107)2,2,Real(ZER(2,2),dp), "# Real(ZER(2,2),dp)" 
Write(io_L,107)2,3,Real(ZER(2,3),dp), "# Real(ZER(2,3),dp)" 
Write(io_L,107)3,1,Real(ZER(3,1),dp), "# Real(ZER(3,1),dp)" 
Write(io_L,107)3,2,Real(ZER(3,2),dp), "# Real(ZER(3,2),dp)" 
Write(io_L,107)3,3,Real(ZER(3,3),dp), "# Real(ZER(3,3),dp)" 
If ((MaxVal(Abs(AImag(ZER))).gt.0._dp).OR.(OutputForMG)) Then 
Write(io_L,106) "Block IMUERMIX Q=",Q,"# ()" 
Write(io_L,107)1,1,Aimag(ZER(1,1)), "# Aimag(ZER(1,1))" 
Write(io_L,107)1,2,Aimag(ZER(1,2)), "# Aimag(ZER(1,2))" 
Write(io_L,107)1,3,Aimag(ZER(1,3)), "# Aimag(ZER(1,3))" 
Write(io_L,107)2,1,Aimag(ZER(2,1)), "# Aimag(ZER(2,1))" 
Write(io_L,107)2,2,Aimag(ZER(2,2)), "# Aimag(ZER(2,2))" 
Write(io_L,107)2,3,Aimag(ZER(2,3)), "# Aimag(ZER(2,3))" 
Write(io_L,107)3,1,Aimag(ZER(3,1)), "# Aimag(ZER(3,1))" 
Write(io_L,107)3,2,Aimag(ZER(3,2)), "# Aimag(ZER(3,2))" 
Write(io_L,107)3,3,Aimag(ZER(3,3)), "# Aimag(ZER(3,3))" 
End If 

Write(io_L,100) "Block SPheno # SPheno internal parameters " 
Write(io_L,102) 1,1.*ErrorLevel,"# ErrorLevel"

If (SPA_convention) Then
Write(io_L,102) 2,1.,"# SPA_conventions"
Else
Write(io_L,102) 2,0.,"# SPA_conventions"
End if

If (L_BR) Then
Write(io_L,102) 11,1.,"# Branching ratios"
Else
Write(io_L,102) 11,0.,"# Branching ratios"
End if


If (Enable3BDecays) Then
Write(io_L,102) 13,1.,"# 3 Body decays"
Else
Write(io_L,102) 13,0.,"# 3 Body decays"
End if


Write(io_L,102) 31,m_GUT,"# GUT scale"

Write(io_L,102) 33,Q,"# Renormalization scale"

Write(io_L,102) 34,delta_mass,"# Precision"

Write(io_L,102) 35,1.*n_run,"# Iterations"


If (TwoLoopRGE) Then
Write(io_L,102) 38,2.,"# RGE level"
Else
Write(io_L,102) 38,1.,"# RGE level"
End if

Write(io_L,102) 40,Alpha,"# Alpha"

Write(io_L,102) 41,gamZ,"# Gamma_Z"

Write(io_L,102) 42,gamW,"# Gamma_W"

If (RotateNegativeFermionMasses) Then
Write(io_L,102) 50,1.,"# Rotate negative fermion masses"
Else
Write(io_L,102) 50,0.,"# Rotate negative fermion masses"
End if


If (SwitchToSCKM) Then
Write(io_L,102) 51,1.,"# Switch to SCKM matrix"
Else
Write(io_L,102) 51,0.,"# Switch to SCKM matrix"
End if


If (IgnoreNegativeMasses) Then
Write(io_L,102) 52,1.,"# Ignore negative masses"
Else
Write(io_L,102) 52,0.,"# Ignore negative masses"
End if


If (IgnoreNegativeMassesMZ) Then
Write(io_L,102) 53,1.,"# Ignore negative masses at MZ"
Else
Write(io_L,102) 53,0.,"# Ignore negative masses at MZ"
End if


If (CalculateOneLoopMasses) Then
Write(io_L,102) 55,1.,"# Calculate one loop masses"
Else
Write(io_L,102) 55,0.,"# Calculate one loop masses"
End if


If (CalculateTwoLoopHiggsMasses) Then
Write(io_L,102) 56,1.,"# Calculate two-loop Higgs masses"
Else
Write(io_L,102) 56,0.,"# Calculate two-loop Higgs masses"
End if

If (CalculateLowEnergy) Then
Write(io_L,102) 57,1.,"# Calculate low energy"
Else
Write(io_L,102) 57,0.,"# Calculate low energy"
End if

If (KineticMixing) Then
Write(io_L,102) 60,1.,"# Include kinetic mixing"
Else
Write(io_L,102) 60,0.,"# Include kinetic mixing"
End if

Write(io_L,102) 65,1.*SolutionTadpoleNr,"# Solution of tadpole equation"
 


 
If(Write_WHIZARD) Call WriteWHIZARD 
 
If(Write_HiggsBounds) Call WriteHiggsBounds 
 
If(Write_HiggsBounds5) Call WriteHiggsBounds5 
 

 
If (L_BR) Then 
If (WriteEffHiggsCouplingRatios) Then 
Write(io_L,100) "Block HiggsBoundsInputHiggsCouplingsFermions # " 
Write(io_L,1101) rHB_S_S_Fd(1,3),rHB_S_P_Fd(1,3), 3 ,25,5,5, " # h_1 b b coupling " 
Write(io_L,1101) rHB_S_S_Fd(1,2),rHB_S_P_Fd(1,2), 3 ,25,3,3, " # h_1 s s coupling " 
Write(io_L,1101) rHB_S_S_Fu(1,3),rHB_S_P_Fu(1,3), 3 ,25,6,6, " # h_1 t t coupling  " 
Write(io_L,1101) rHB_S_S_Fu(1,2),rHB_S_P_Fu(1,2),3 ,25,4,4, " # h_1 c c coupling " 
Write(io_L,1101) rHB_S_S_Fe(1,3),rHB_S_P_Fe(1,3), 3 ,25,15,15, " # h_1 tau tau coupling " 
Write(io_L,1101) rHB_S_S_Fe(1,2),rHB_S_P_Fe(1,2), 3 ,25,13,13, " # h_1 mu mu coupling  " 
Write(io_L,100) "Block HiggsBoundsInputHiggsCouplingsBosons # " 
Write(io_L,1102) rHB_S_VWp(1),3 ,25,24,24, " # h_1 W W coupling " 
Write(io_L,1102) rHB_S_VZ(1),3 ,25,23,23, " # h_1 Z Z coupling  " 
Write(io_L,1102) 0._dp ,3 ,25,23,22, " # h_1 Z gamma coupling " 
Write(io_L,1102) Real(ratioPP,dp),3 ,25,22,22, " # h_1 gamma gamma coupling " 
Write(io_L,1102) Real(ratioGG,dp),3 ,25,21,21, " # h_1 g g coupling " 
Write(io_L,1103) 0._dp,4 ,25,21,21,23, " # h_1 g g Z coupling " 
Write(io_L,1102) Real(CPL_H_H_Z(1,1), dp),3 ,25,25,23, " # h_1 h_1 Z coupling  "
End If 

 
If (WriteHiggsDiphotonLoopContributions) Then 
Write(io_L,100) "Block HPPloops # Loop contributions to H-Photon-Photon coupling " 
Do i1=1,1
CurrentPDG2(1) = Abs(PDGhh) 
Do i2=1,1
CurrentPDG2(2) = Abs(PDGVWp) 
Write(io_L,122) CurrentPDG2(1), CurrentPDG2(2), HPPloopVWp, " # h(",i1,")-VWp(",i2,")-loop " 
End do 
Do i2=2,2
CurrentPDG2(2) = Abs(PDGHp(i2)) 
Write(io_L,122) CurrentPDG2(1), CurrentPDG2(2), HPPloopHp(i2), " # h(",i1,")-Hp(",i2,")-loop " 
End do 
Do i2=1,3
CurrentPDG2(2) = Abs(PDGFd(i2)) 
Write(io_L,122) CurrentPDG2(1), CurrentPDG2(2), HPPloopFd(i2), " # h(",i1,")-Fd(",i2,")-loop " 
End do 
Do i2=1,3
CurrentPDG2(2) = Abs(PDGFu(i2)) 
Write(io_L,122) CurrentPDG2(1), CurrentPDG2(2), HPPloopFu(i2), " # h(",i1,")-Fu(",i2,")-loop " 
End do 
Do i2=1,3
CurrentPDG2(2) = Abs(PDGFe(i2)) 
Write(io_L,122) CurrentPDG2(1), CurrentPDG2(2), HPPloopFe(i2), " # h(",i1,")-Fe(",i2,")-loop " 
End do 
End Do 
End if 

 
Write(io_L,100) "Block EFFHIGGSCOUPLINGS # values of loop-induced couplings " 
facPP = Alpha*Sqrt(2._dp*G_F/sqrt(2._dp))/(2._dp*Pi) 
facGG = Sqrt(2._dp*G_F/sqrt(2._dp))/(Sqrt(2._dp)*2._dp*Pi)*sqrt(8._dp/9._dp)
facPZ = 0._dp 
Do i1=1,1
CurrentPDG3(1) = Abs(PDGhh) 
CurrentPDG3(2) = Abs(PDGVP) 
CurrentPDG3(3) = Abs(PDGVP) 
Write(io_L,121) CurrentPDG3(1), CurrentPDG3(2), CurrentPDG3(3), Abs(CoupHPP)*facPP, " # H-Photon-Photon " 
CurrentPDG3(2) = Abs(PDGVG) 
CurrentPDG3(3) = Abs(PDGVG) 
Write(io_L,121) CurrentPDG3(1), CurrentPDG3(2), CurrentPDG3(3), Abs(CoupHGG)*facGG, " # H-Gluon-Gluon " 
CurrentPDG3(2) = Abs(PDGVP) 
CurrentPDG3(3) = Abs(PDGVZ) 
Write(io_L,121) CurrentPDG3(1), CurrentPDG3(2), CurrentPDG3(3), 0._dp, " # H-Photon-Z (not yet calculated by SPheno) " 
End Do 
Do i1=2,1
CurrentPDG3(1) = Abs(PDGG0) 
CurrentPDG3(2) = Abs(PDGVP) 
CurrentPDG3(3) = Abs(PDGVP) 
Write(io_L,121) CurrentPDG3(1), CurrentPDG3(2), CurrentPDG3(3), Abs(CoupAPP)*facPP, " # A-Photon-Photon " 
CurrentPDG3(2) = Abs(PDGVG) 
CurrentPDG3(3) = Abs(PDGVG) 
Write(io_L,121) CurrentPDG3(1), CurrentPDG3(2), CurrentPDG3(3), Abs(CoupAGG)*facGG, " # A-Gluon-Gluon " 
CurrentPDG3(2) = Abs(PDGVP) 
CurrentPDG3(3) = Abs(PDGVZ) 
Write(io_L,121) CurrentPDG3(1), CurrentPDG3(2), CurrentPDG3(3), 0._dp, " # A-Photon-Z (not yet calculated by SPheno) " 
End Do 
End If 

 
Write(io_L,100) "Block SPhenoLowEnergy # low energy observables " 
Write(io_L,1010) 1,Tpar,  "# T-parameter (1-loop BSM)" 
Write(io_L,1010) 2,Spar,  "# S-parameter (1-loop BSM)" 
Write(io_L,1010) 3,Upar,  "# U-parameter (1-loop BSM)" 
Write(io_L,1010) 20,ae,  "# (g-2)_e" 
Write(io_L,1010) 21,amu,  "# (g-2)_mu" 
Write(io_L,1010) 22,atau,  "# (g-2)_tau" 
Write(io_L,1010) 23,EDMe,  "# EDM(e)" 
Write(io_L,1010) 24,EDMmu,  "# EDM(mu)" 
Write(io_L,1010) 25,EDMtau,  "# EDM(tau)" 
Write(io_L,1010) 39,dRho,  "# delta(rho)" 
Write(io_L,100) "Block FlavorKitQFV # quark flavor violating observables " 
Write(io_L,100) "Block FlavorKitLFV # lepton flavor violating observables " 

 
Write(io_L,100) "Block FWCOEF Q=  1.60000000E+02  # Wilson coefficients at scale Q " 
Write(io_L,100) "Block IMFWCOEF Q=  1.60000000E+02  # Im(Wilson coefficients) at scale Q " 
Write(io_L,100) "Block TREELEVELUNITARITY #  " 
Write(io_L,1010) 0, TreeUnitarity,  "# Tree-level unitarity limits fulfilled or not "  
Write(io_L,1010) 1, max_scattering_eigenvalue,  "# Maximal scattering eigenvalue "  
If (TrilinearUnitarity) Then  
Write(io_L,100) "Block TREELEVELUNITARITYwTRILINEARS #  " 
Write(io_L,1010) 0, TreeUnitarityTrilinear,  "# Tree-level unitarity limits fulfilled or not "  
Write(io_L,1010) 1, max_scattering_eigenvalue_trilinears,  "# Maximal scattering eigenvalue "  
Write(io_L,1010) 2, unitarity_s_best,  "# best scattering energy "  
Write(io_L,1010) 11, unitarity_s_min,  "# min scattering energy "  
Write(io_L,1010) 12, unitarity_s_max,  "# max scattering energy "  
Write(io_L,1010) 13, 1._dp*unitarity_steps,  "# steps "  
End If 

 

 
 !-------------------------------
!Fu
!-------------------------------
 
If ((gTFu(1).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFu(1)),gTFu(1),Trim(NameParticleFu(1)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFu(1,25:159)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFu(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFu(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFu(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFu(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFu(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 
If ((gTFu(2).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFu(2)),gTFu(2),Trim(NameParticleFu(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFu(2,25:159)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFu(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFu(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFu(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFu(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFu(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 
If ((gTFu(3).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFu(3)),gTFu(3),Trim(NameParticleFu(3)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFu(3,25:159)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFu(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFu(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFu(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFu(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFu(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFu(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 

 
 !-------------------------------
!Fe
!-------------------------------
 
If ((gTFe(1).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFe(1)),gTFe(1),Trim(NameParticleFe(1)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFe(1,22:156)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFe(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFe(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFe(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFe(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFv(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFe(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 
If ((gTFe(2).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFe(2)),gTFe(2),Trim(NameParticleFe(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFe(2,22:156)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFe(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFe(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFe(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFe(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFv(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFe(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 
If ((gTFe(3).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFe(3)),gTFe(3),Trim(NameParticleFe(3)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFe(3,22:156)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFe(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFe(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFe(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFe(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFe(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFe(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFv(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFe(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 

 
 !-------------------------------
!Fd
!-------------------------------
 
If ((gTFd(1).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFd(1)),gTFd(1),Trim(NameParticleFd(1)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFd(1,25:159)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFd(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFd(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFd(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFd(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(1,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFd(1,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 
If ((gTFd(2).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFd(2)),gTFd(2),Trim(NameParticleFd(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFd(2,25:159)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFd(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFd(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFd(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFd(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(2,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFd(2,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 
If ((gTFd(3).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGFd(3)),gTFd(3),Trim(NameParticleFd(3)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (Maxval(BRFd(3,25:159)).Gt.BRmin) Then 
Write(io_L,100) "#    BR                NDA      ID1      ID2       ID3" 
End If 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFd(gt2) 
CurrentPDG3(3) = PDGFd(gt3) 
Write(io_L,202) BRFd(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//Trim(NameParticleFd(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFe(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFd(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFu(gt2) 
CurrentPDG3(3) = PDGFu(gt3) 
Write(io_L,202) BRFd(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//Trim(NameParticleFu(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFd(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFv(gt3) 
Write(io_L,202) BRFd(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFv(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
If (BRFd(3,icount).Gt.BrMin) Then 
CurrentPDG3(1) = PDGFu(gt1) 
CurrentPDG3(2) = -PDGFv(gt2) 
CurrentPDG3(3) = PDGFe(gt3) 
Write(io_L,202) BRFd(3,icount),3,CurrentPDG3, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//Trim(NameParticleFe(gt3))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
End Do 
 
End if 

 
 !-------------------------------
!hh
!-------------------------------
 
If ((gThh.gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGhh),gThh,Trim(NameParticlehh) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVG 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVG)//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGVWp 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVWp)//"^* "//Trim(NameParticleVWp)//"_virt "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleA0)//" "//")"
If (((gTA0.le.WidthToBeInvisible).and.(gTA0.le.WidthToBeInvisible)).OR. & 
 & ((WidthToBeInvisible.le.-1._dp).And.(CurrentPDG2(1).eq.PDGLSP(1)).And.(CurrentPDG2(2).eq.PDGLSP(1)))) Then 
  BRinvH(1) = BRinvH(1)+BRhh(1,icount) 
End if 
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleA0)//" "//")"
If (((gTH0.le.WidthToBeInvisible).and.(gTA0.le.WidthToBeInvisible)).OR. & 
 & ((WidthToBeInvisible.le.-1._dp).And.(CurrentPDG2(1).eq.PDGLSP(1)).And.(CurrentPDG2(2).eq.PDGLSP(1)))) Then 
  BRinvH(1) = BRinvH(1)+BRhh(1,icount) 
End if 
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFd(gt1) 
CurrentPDG2(2) = PDGFd(gt2) 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFd(gt1))//"^* "//Trim(NameParticleFd(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFe(gt1) 
CurrentPDG2(2) = PDGFe(gt2) 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFe(gt1))//"^* "//Trim(NameParticleFe(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFu(gt1) 
CurrentPDG2(2) = PDGFu(gt2) 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFu(gt1))//"^* "//Trim(NameParticleFu(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleH0)//" "//")"
If (((gTH0.le.WidthToBeInvisible).and.(gTH0.le.WidthToBeInvisible)).OR. & 
 & ((WidthToBeInvisible.le.-1._dp).And.(CurrentPDG2(1).eq.PDGLSP(1)).And.(CurrentPDG2(2).eq.PDGLSP(1)))) Then 
  BRinvH(1) = BRinvH(1)+BRhh(1,icount) 
End if 
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
  Do gt2=2, 2
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGHp(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRhh(1,icount)/2._dp,2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
Write(io_L,201) BRhh(1,icount)/2._dp,2,-CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVWp 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVWp)//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticlehh)//" "//")"
If (((gTA0.le.WidthToBeInvisible).and.(gThh.le.WidthToBeInvisible)).OR. & 
 & ((WidthToBeInvisible.le.-1._dp).And.(CurrentPDG2(1).eq.PDGLSP(1)).And.(CurrentPDG2(2).eq.PDGLSP(1)))) Then 
  BRinvH(1) = BRinvH(1)+BRhh(1,icount) 
End if 
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGFv(gt2) 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticlehh)//" "//")"
If (((gTH0.le.WidthToBeInvisible).and.(gThh.le.WidthToBeInvisible)).OR. & 
 & ((WidthToBeInvisible.le.-1._dp).And.(CurrentPDG2(1).eq.PDGLSP(1)).And.(CurrentPDG2(2).eq.PDGLSP(1)))) Then 
  BRinvH(1) = BRinvH(1)+BRhh(1,icount) 
End if 
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVG 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVG)//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
End if 

 
 !-------------------------------
!H0
!-------------------------------
 
If ((gTH0.gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGH0),gTH0,Trim(NameParticleH0) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
  Do gt2=2, 2
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGHp(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRH0(1,icount)/2._dp,2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
Write(io_L,201) BRH0(1,icount)/2._dp,2,-CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = -PDGFd(gt2) 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = -PDGFe(gt2) 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGFu(gt2) 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGFv(gt2) 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGVWp 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVWp)//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
If (BRH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
End if 

 
 !-------------------------------
!A0
!-------------------------------
 
If ((gTA0.gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGA0),gTA0,Trim(NameParticleA0) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
  Do gt2=2, 2
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGHp(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BRA0(1,icount)/2._dp,2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
Write(io_L,201) BRA0(1,icount)/2._dp,2,-CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = -PDGFd(gt2) 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = -PDGFe(gt2) 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGFu(gt2) 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGFv(gt2) 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGVWp 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVWp)//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
If (BRA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
End if 

 
 !-------------------------------
!Hp
!-------------------------------
 
If ((gTHp(2).gt.MinWidth).or.(OutputForMG)) Then 
Write(io_L,200) INT(PDGHp(2)),gTHp(2),Trim(NameParticleHp(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 2, 2
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFd(gt1) 
CurrentPDG2(2) = PDGFu(gt2) 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleFd(gt1))//"^* "//Trim(NameParticleFu(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFe(gt1) 
CurrentPDG2(2) = PDGFv(gt2) 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleFe(gt1))//"^* "//Trim(NameParticleFv(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVWp 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleVWp)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BRHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVWp 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BRHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleVWp)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
End if 
! Information needed by MadGraph 
If (OutputForMG) Then 
Write(io_L,200) INT(Abs(PDGVG)),0._dp, "VG" 
Write(io_L,200) INT(Abs(PDGVP)),0._dp, "VP" 
Write(io_L,200) INT(Abs(PDGVZ)),2.4952_dp, "VZ" 
Write(io_L,200) INT(Abs(PDGVWp)),2.141_dp, "VWp" 
Write(io_L,200) INT(Abs(PDGFv(1))),0._dp, "Fv_1" 
Write(io_L,200) INT(Abs(PDGFv(2))),0._dp, "Fv_2" 
Write(io_L,200) INT(Abs(PDGFv(3))),0._dp, "Fv_3" 
Write(io_L,200) INT(Abs(PDGG0)),0._dp, "G0_1" 
End if 

 
 !-------------------------------
!Fu
!-------------------------------
 
If(gT1LFu(1).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFu(1)),gT1LFu(1),Trim(NameParticleFu(1)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFu(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 
If(gT1LFu(2).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFu(2)),gT1LFu(2),Trim(NameParticleFu(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFu(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 
If(gT1LFu(3).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFu(3)),gT1LFu(3),Trim(NameParticleFu(3)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFu(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFu(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFu(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 

 
 !-------------------------------
!Fe
!-------------------------------
 
If(gT1LFe(1).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFe(1)),gT1LFe(1),Trim(NameParticleFe(1)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFe(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(1))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 
If(gT1LFe(2).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFe(2)),gT1LFe(2),Trim(NameParticleFe(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFe(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(2))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 
If(gT1LFe(3).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFe(3)),gT1LFe(3),Trim(NameParticleFe(3)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFe(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFe(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFe(3))//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 

 
 !-------------------------------
!Fd
!-------------------------------
 
If(gT1LFd(1).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFd(1)),gT1LFd(1),Trim(NameParticleFd(1)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFd(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(1))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 
If(gT1LFd(2).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFd(2)),gT1LFd(2),Trim(NameParticleFd(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFd(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(2))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 
If(gT1LFd(3).gt.MinWidth) Then 
Write(io_L,210) INT(PDGFd(3)),gT1LFd(3),Trim(NameParticleFd(3)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
  Do gt2=2, 2
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGHp(gt2) 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleHp(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
  End Do 
Do gt1= 1, 3
If (BR1LFd(3,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LFd(3,icount),2,CurrentPDG2, & 
 & Trim(NameParticleFd(3))//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
End if 

 
 !-------------------------------
!hh
!-------------------------------
 
If(gT1Lhh.gt.MinWidth) Then 
Write(io_L,210) INT(PDGhh),gT1Lhh,Trim(NameParticlehh) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVG 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVG)//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGVWp 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVWp)//"^* "//Trim(NameParticleVWp)//"_virt "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFd(gt1) 
CurrentPDG2(2) = PDGFd(gt2) 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFd(gt1))//"^* "//Trim(NameParticleFd(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFe(gt1) 
CurrentPDG2(2) = PDGFe(gt2) 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFe(gt1))//"^* "//Trim(NameParticleFe(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFu(gt1) 
CurrentPDG2(2) = PDGFu(gt2) 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFu(gt1))//"^* "//Trim(NameParticleFu(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
  Do gt2=2, 2
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGHp(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1Lhh(1,icount)/2._dp,2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
Write(io_L,201) BR1Lhh(1,icount)/2._dp,2,-CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVWp 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVWp)//" "//Trim(NameParticleVWp)//"^* "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGFv(gt2) 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVG 
CurrentPDG2(2) = PDGVG 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVG)//" "//Trim(NameParticleVG)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1Lhh(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1Lhh(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticlehh)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
End if 

 
 !-------------------------------
!H0
!-------------------------------
 
If(gT1LH0.gt.MinWidth) Then 
Write(io_L,210) INT(PDGH0),gT1LH0,Trim(NameParticleH0) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
  Do gt2=2, 2
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGHp(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LH0(1,icount)/2._dp,2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
Write(io_L,201) BR1LH0(1,icount)/2._dp,2,-CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = -PDGFd(gt2) 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = -PDGFe(gt2) 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGFu(gt2) 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGFv(gt2) 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGVWp 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVWp)//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
If (BR1LH0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LH0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleH0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
End if 

 
 !-------------------------------
!A0
!-------------------------------
 
If(gT1LA0.gt.MinWidth) Then 
Write(io_L,210) INT(PDGA0),gT1LA0,Trim(NameParticleA0) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
  Do gt2=2, 2
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGHp(gt1) 
CurrentPDG2(2) = PDGHp(gt2) 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleHp(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = -PDGVWp 
Write(io_L,201) BR1LA0(1,icount)/2._dp,2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVWp)//"^* "//")"
Write(io_L,201) BR1LA0(1,icount)/2._dp,2,-CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleHp(gt1))//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFd(gt1) 
CurrentPDG2(2) = -PDGFd(gt2) 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFd(gt1))//" "//Trim(NameParticleFd(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFe(gt1) 
CurrentPDG2(2) = -PDGFe(gt2) 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFe(gt1))//" "//Trim(NameParticleFe(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFu(gt1) 
CurrentPDG2(2) = -PDGFu(gt2) 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFu(gt1))//" "//Trim(NameParticleFu(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGFv(gt1) 
CurrentPDG2(2) = -PDGFv(gt2) 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleFv(gt1))//" "//Trim(NameParticleFv(gt2))//"^* "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVP 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVP)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGVWp 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVWp)//"^* "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
If (BR1LA0(1,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVZ 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LA0(1,icount),2,CurrentPDG2, & 
 & Trim(NameParticleA0)//" -> "//Trim(NameParticleVZ)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
End if 

 
 !-------------------------------
!Hp
!-------------------------------
 
If(gT1LHp(2).gt.MinWidth) Then 
Write(io_L,210) INT(PDGHp(2)),gT1LHp(2),Trim(NameParticleHp(2)) 
Write(io_L,100) "#    BR                NDA      ID1      ID2" 
icount = 1 
Do gt1= 2, 2
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGA0 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleA0)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGA0 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleA0)//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFd(gt1) 
CurrentPDG2(2) = PDGFu(gt2) 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleFd(gt1))//"^* "//Trim(NameParticleFu(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 1, 3
  Do gt2=1, 3
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = -PDGFe(gt1) 
CurrentPDG2(2) = PDGFv(gt2) 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleFe(gt1))//"^* "//Trim(NameParticleFv(gt2))//" "//")"
End if 
icount = icount +1 
  End Do 
End Do 
 
Do gt1= 2, 2
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGH0 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleH0)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGH0 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleH0)//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGhh 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticlehh)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGhh 
CurrentPDG2(2) = PDGVWp 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticlehh)//" "//Trim(NameParticleVWp)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVWp 
CurrentPDG2(2) = PDGVZ 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleVWp)//" "//Trim(NameParticleVZ)//" "//")"
End if 
icount = icount +1 
Do gt1= 2, 2
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGHp(gt1) 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleHp(gt1))//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
  End Do 
If (BR1LHp(2,icount).Gt.BrMin) Then 
CurrentPDG2(1) = PDGVWp 
CurrentPDG2(2) = PDGVP 
Write(io_L,201) BR1LHp(2,icount),2,CurrentPDG2, & 
 & Trim(NameParticleHp(2))//" -> "//Trim(NameParticleVWp)//" "//Trim(NameParticleVP)//" "//")"
End if 
icount = icount +1 
End if 
99 Format(1x,i5,3x,a) 
100 Format(a) 
101 Format(2x,i3,2x,1P,e16.8,2x,a) 
1010 Format(2x,i6,2x,1P,e16.8,2x,a) 
102 Format(1x,i9,3x,1P,e16.8,2x,a) 
103 Format(a13,1P,e16.8,2x,a) 
104 Format(i4,2x,1P,e16.8,2x,a) 
105 Format(1x,2i3,3x,1P,e16.8,3x,a) 
106 Format(a,1P,e16.8,2x,a) 
107 Format(2i3,3x,1P,e16.8,3x,a) 
127 Format(3i3,3x,1P,e16.8,3x,a) 
117 Format(i3,i8,3x,1P,e16.8,3x,a) 
118 Format(i3,i10,3x,1P,a) 
119 Format(i3,i10,3x,1P,3x,e16.8,a) 
120 Format(i3,i10,3x,1P,3x,e16.8,a,i2,a,i2,a) 
121 Format(i10,3x,i10,3x,i10,3x,e16.8,a) 
122 Format(i10,i10,3x,1P,3x,e16.8,a,i2,a,i2,a) 
108 Format(9x,1P,E16.8,0P,3x,a) 
109 Format(1x,3i3,3x,1P,e16.8,3x,a) 
110 Format(3x,2i3,3x,"# ",a) 
200 Format("DECAY",1x,I9,3x,1P,E16.8,0P,3x,"# ",a) 
210 Format("DECAY1L",1x,I9,3x,1P,E16.8,0P,3x,"# ",a) 
201 Format(3x,1P,e16.8,0p,3x,I2,3x,2(i10,1x),2x,"# BR(",a) 
202 Format(3x,1P,e16.8,0p,3x,I2,3x,3(i10,1x),2x,"# BR(",a) 
222 Format(1x,a8,1x,a4,3x,a2,3x,a1,3x,E16.8,3x,a) 
4711 Format(3x,1P,e16.8,0p,3x,I2,3x,2(i10,1x),2x," # ",A)
4712 Format("XS 11 -11 ",F7.1," ",F5.2," ",F5.2," ",A)

5410 Format(a25,1p,e16.7) 
5411 Format(a25,1p,"(",e16.7,",",e16.7,")") 
1101 Format(1P,2x,e16.8,2x,e16.8,0P,5x,i4,5x,3i10,a) 
1102 Format(1P,2x,e16.8,0P,5x,i4,5x,3i10,a) 
1103 Format(1P,2x,e16.8,0P,5x,i4,5x,4i10,a) 
End Subroutine LesHouches_Out 
 
 
Subroutine WriteWHIZARD 
   Open(123,file="WHIZARD.par.Inert",status="unknown")
Write(123,*) "# Couplings and VEVs" 
 
Write(123,*) "" 
Write(123,*) "Lam5_r = ",Real(Lam5,dp) 
Write(123,*) "Lam5_i = ",AImag(Lam5) 
Write(123,*) "Lam1_r = ",Real(Lam1,dp) 
Write(123,*) "Lam1_i = ",AImag(Lam1) 
Write(123,*) "Lam4_r = ",Real(Lam4,dp) 
Write(123,*) "Lam4_i = ",AImag(Lam4) 
Write(123,*) "Lam3_r = ",Real(Lam3,dp) 
Write(123,*) "Lam3_i = ",AImag(Lam3) 
Write(123,*) "Lam2_r = ",Real(Lam2,dp) 
Write(123,*) "Lam2_i = ",AImag(Lam2) 
Write(123,*) "Ye11_r= ",Real(Ye(1,1),dp)
Write(123,*) "Ye12_r= ",Real(Ye(1,2),dp)
Write(123,*) "Ye13_r= ",Real(Ye(1,3),dp)
Write(123,*) "Ye21_r= ",Real(Ye(2,1),dp)
Write(123,*) "Ye22_r= ",Real(Ye(2,2),dp)
Write(123,*) "Ye23_r= ",Real(Ye(2,3),dp)
Write(123,*) "Ye31_r= ",Real(Ye(3,1),dp)
Write(123,*) "Ye32_r= ",Real(Ye(3,2),dp)
Write(123,*) "Ye33_r= ",Real(Ye(3,3),dp)
Write(123,*) "Ye11_i= ",AImag(Ye(1,1))
Write(123,*) "Ye12_i= ",AImag(Ye(1,2))
Write(123,*) "Ye13_i= ",AImag(Ye(1,3))
Write(123,*) "Ye21_i= ",AImag(Ye(2,1))
Write(123,*) "Ye22_i= ",AImag(Ye(2,2))
Write(123,*) "Ye23_i= ",AImag(Ye(2,3))
Write(123,*) "Ye31_i= ",AImag(Ye(3,1))
Write(123,*) "Ye32_i= ",AImag(Ye(3,2))
Write(123,*) "Ye33_i= ",AImag(Ye(3,3))
Write(123,*) "Yd11_r= ",Real(Yd(1,1),dp)
Write(123,*) "Yd12_r= ",Real(Yd(1,2),dp)
Write(123,*) "Yd13_r= ",Real(Yd(1,3),dp)
Write(123,*) "Yd21_r= ",Real(Yd(2,1),dp)
Write(123,*) "Yd22_r= ",Real(Yd(2,2),dp)
Write(123,*) "Yd23_r= ",Real(Yd(2,3),dp)
Write(123,*) "Yd31_r= ",Real(Yd(3,1),dp)
Write(123,*) "Yd32_r= ",Real(Yd(3,2),dp)
Write(123,*) "Yd33_r= ",Real(Yd(3,3),dp)
Write(123,*) "Yd11_i= ",AImag(Yd(1,1))
Write(123,*) "Yd12_i= ",AImag(Yd(1,2))
Write(123,*) "Yd13_i= ",AImag(Yd(1,3))
Write(123,*) "Yd21_i= ",AImag(Yd(2,1))
Write(123,*) "Yd22_i= ",AImag(Yd(2,2))
Write(123,*) "Yd23_i= ",AImag(Yd(2,3))
Write(123,*) "Yd31_i= ",AImag(Yd(3,1))
Write(123,*) "Yd32_i= ",AImag(Yd(3,2))
Write(123,*) "Yd33_i= ",AImag(Yd(3,3))
Write(123,*) "Yu11_r= ",Real(Yu(1,1),dp)
Write(123,*) "Yu12_r= ",Real(Yu(1,2),dp)
Write(123,*) "Yu13_r= ",Real(Yu(1,3),dp)
Write(123,*) "Yu21_r= ",Real(Yu(2,1),dp)
Write(123,*) "Yu22_r= ",Real(Yu(2,2),dp)
Write(123,*) "Yu23_r= ",Real(Yu(2,3),dp)
Write(123,*) "Yu31_r= ",Real(Yu(3,1),dp)
Write(123,*) "Yu32_r= ",Real(Yu(3,2),dp)
Write(123,*) "Yu33_r= ",Real(Yu(3,3),dp)
Write(123,*) "Yu11_i= ",AImag(Yu(1,1))
Write(123,*) "Yu12_i= ",AImag(Yu(1,2))
Write(123,*) "Yu13_i= ",AImag(Yu(1,3))
Write(123,*) "Yu21_i= ",AImag(Yu(2,1))
Write(123,*) "Yu22_i= ",AImag(Yu(2,2))
Write(123,*) "Yu23_i= ",AImag(Yu(2,3))
Write(123,*) "Yu31_i= ",AImag(Yu(3,1))
Write(123,*) "Yu32_i= ",AImag(Yu(3,2))
Write(123,*) "Yu33_i= ",AImag(Yu(3,3))
Write(123,*) "" 
Write(123,*) "" 

 
 
 Write(123,*) "# Dependent parameters " 
 
Write(123,*) "" 
Write(123,*) "betaH= ",ASin(Abs(ZP(1,2)))
Write(123,*) "" 
Write(123,*) "" 

 
 
 Write(123,*) "# Necessary MINPAR parameters " 
 
Write(123,*) "" 
Write(123,*) "" 
Write(123,*) "" 

 
 
 Write(123,*) "# Masses of particles" 
 
Write(123,*) "" 
Write(123,*) "Mh= ", Abs(Mhh) 
Write(123,*) "MH0= ", Abs(MH0) 
Write(123,*) "MA0= ", Abs(MA0) 
Write(123,*) "MHp2= ", Abs(MHp(2)) 
Write(123,*) "MZ= ", Abs(MVZ) 
Write(123,*) "Md1= ", Abs(MFd(1)) 
Write(123,*) "Md2= ", Abs(MFd(2)) 
Write(123,*) "Md3= ", Abs(MFd(3)) 
Write(123,*) "Mu1= ", Abs(MFu(1)) 
Write(123,*) "Mu2= ", Abs(MFu(2)) 
Write(123,*) "Mu3= ", Abs(MFu(3)) 
Write(123,*) "Me1= ", Abs(MFe(1)) 
Write(123,*) "Me2= ", Abs(MFe(2)) 
Write(123,*) "Me3= ", Abs(MFe(3)) 
Write(123,*) "" 
Write(123,*) "" 

 
 
 Write(123,*) "# Widths of particles" 
 
Write(123,*) "" 
Write(123,*) "Wu3 = ",gTFu(3)
Write(123,*) "Wh = ",gThh
Write(123,*) "WH0 = ",gTH0
Write(123,*) "WA0 = ",gTA0
Write(123,*) "WHp2 = ",gTHp(2)
Write(123,*) "" 
Write(123,*) "" 

 
 
 Write(123,*) "# Mixing matrices" 
 
Write(123,*) "" 
If (MFd(1).Gt.0._dp) Then 
Write(123,*) "ZDL11_r = ", Real(ZDL(1,1),dp)
Write(123,*) "ZDL11_i = ", AImag(ZDL(1,1))
Write(123,*) "ZDL12_r = ", Real(ZDL(1,2),dp)
Write(123,*) "ZDL12_i = ", AImag(ZDL(1,2))
Write(123,*) "ZDL13_r = ", Real(ZDL(1,3),dp)
Write(123,*) "ZDL13_i = ", AImag(ZDL(1,3))
Else 
Write(123,*) "ZDL11_i = ", Real(ZDL(1,1),dp)
Write(123,*) "ZDL11_r = ", -AImag(ZDL(1,1))
Write(123,*) "ZDL12_i = ", Real(ZDL(1,2),dp)
Write(123,*) "ZDL12_r = ", -AImag(ZDL(1,2))
Write(123,*) "ZDL13_i = ", Real(ZDL(1,3),dp)
Write(123,*) "ZDL13_r = ", -AImag(ZDL(1,3))
End if 
If (MFd(2).Gt.0._dp) Then 
Write(123,*) "ZDL21_r = ", Real(ZDL(2,1),dp)
Write(123,*) "ZDL21_i = ", AImag(ZDL(2,1))
Write(123,*) "ZDL22_r = ", Real(ZDL(2,2),dp)
Write(123,*) "ZDL22_i = ", AImag(ZDL(2,2))
Write(123,*) "ZDL23_r = ", Real(ZDL(2,3),dp)
Write(123,*) "ZDL23_i = ", AImag(ZDL(2,3))
Else 
Write(123,*) "ZDL21_i = ", Real(ZDL(2,1),dp)
Write(123,*) "ZDL21_r = ", -AImag(ZDL(2,1))
Write(123,*) "ZDL22_i = ", Real(ZDL(2,2),dp)
Write(123,*) "ZDL22_r = ", -AImag(ZDL(2,2))
Write(123,*) "ZDL23_i = ", Real(ZDL(2,3),dp)
Write(123,*) "ZDL23_r = ", -AImag(ZDL(2,3))
End if 
If (MFd(3).Gt.0._dp) Then 
Write(123,*) "ZDL31_r = ", Real(ZDL(3,1),dp)
Write(123,*) "ZDL31_i = ", AImag(ZDL(3,1))
Write(123,*) "ZDL32_r = ", Real(ZDL(3,2),dp)
Write(123,*) "ZDL32_i = ", AImag(ZDL(3,2))
Write(123,*) "ZDL33_r = ", Real(ZDL(3,3),dp)
Write(123,*) "ZDL33_i = ", AImag(ZDL(3,3))
Else 
Write(123,*) "ZDL31_i = ", Real(ZDL(3,1),dp)
Write(123,*) "ZDL31_r = ", -AImag(ZDL(3,1))
Write(123,*) "ZDL32_i = ", Real(ZDL(3,2),dp)
Write(123,*) "ZDL32_r = ", -AImag(ZDL(3,2))
Write(123,*) "ZDL33_i = ", Real(ZDL(3,3),dp)
Write(123,*) "ZDL33_r = ", -AImag(ZDL(3,3))
End if 
If (MFd(1).Gt.0._dp) Then 
Write(123,*) "ZDR11_r = ", Real(ZDR(1,1),dp)
Write(123,*) "ZDR11_i = ", AImag(ZDR(1,1))
Write(123,*) "ZDR12_r = ", Real(ZDR(1,2),dp)
Write(123,*) "ZDR12_i = ", AImag(ZDR(1,2))
Write(123,*) "ZDR13_r = ", Real(ZDR(1,3),dp)
Write(123,*) "ZDR13_i = ", AImag(ZDR(1,3))
Else 
Write(123,*) "ZDR11_i = ", Real(ZDR(1,1),dp)
Write(123,*) "ZDR11_r = ", -AImag(ZDR(1,1))
Write(123,*) "ZDR12_i = ", Real(ZDR(1,2),dp)
Write(123,*) "ZDR12_r = ", -AImag(ZDR(1,2))
Write(123,*) "ZDR13_i = ", Real(ZDR(1,3),dp)
Write(123,*) "ZDR13_r = ", -AImag(ZDR(1,3))
End if 
If (MFd(2).Gt.0._dp) Then 
Write(123,*) "ZDR21_r = ", Real(ZDR(2,1),dp)
Write(123,*) "ZDR21_i = ", AImag(ZDR(2,1))
Write(123,*) "ZDR22_r = ", Real(ZDR(2,2),dp)
Write(123,*) "ZDR22_i = ", AImag(ZDR(2,2))
Write(123,*) "ZDR23_r = ", Real(ZDR(2,3),dp)
Write(123,*) "ZDR23_i = ", AImag(ZDR(2,3))
Else 
Write(123,*) "ZDR21_i = ", Real(ZDR(2,1),dp)
Write(123,*) "ZDR21_r = ", -AImag(ZDR(2,1))
Write(123,*) "ZDR22_i = ", Real(ZDR(2,2),dp)
Write(123,*) "ZDR22_r = ", -AImag(ZDR(2,2))
Write(123,*) "ZDR23_i = ", Real(ZDR(2,3),dp)
Write(123,*) "ZDR23_r = ", -AImag(ZDR(2,3))
End if 
If (MFd(3).Gt.0._dp) Then 
Write(123,*) "ZDR31_r = ", Real(ZDR(3,1),dp)
Write(123,*) "ZDR31_i = ", AImag(ZDR(3,1))
Write(123,*) "ZDR32_r = ", Real(ZDR(3,2),dp)
Write(123,*) "ZDR32_i = ", AImag(ZDR(3,2))
Write(123,*) "ZDR33_r = ", Real(ZDR(3,3),dp)
Write(123,*) "ZDR33_i = ", AImag(ZDR(3,3))
Else 
Write(123,*) "ZDR31_i = ", Real(ZDR(3,1),dp)
Write(123,*) "ZDR31_r = ", -AImag(ZDR(3,1))
Write(123,*) "ZDR32_i = ", Real(ZDR(3,2),dp)
Write(123,*) "ZDR32_r = ", -AImag(ZDR(3,2))
Write(123,*) "ZDR33_i = ", Real(ZDR(3,3),dp)
Write(123,*) "ZDR33_r = ", -AImag(ZDR(3,3))
End if 
If (MFu(1).Gt.0._dp) Then 
Write(123,*) "ZUL11_r = ", Real(ZUL(1,1),dp)
Write(123,*) "ZUL11_i = ", AImag(ZUL(1,1))
Write(123,*) "ZUL12_r = ", Real(ZUL(1,2),dp)
Write(123,*) "ZUL12_i = ", AImag(ZUL(1,2))
Write(123,*) "ZUL13_r = ", Real(ZUL(1,3),dp)
Write(123,*) "ZUL13_i = ", AImag(ZUL(1,3))
Else 
Write(123,*) "ZUL11_i = ", Real(ZUL(1,1),dp)
Write(123,*) "ZUL11_r = ", -AImag(ZUL(1,1))
Write(123,*) "ZUL12_i = ", Real(ZUL(1,2),dp)
Write(123,*) "ZUL12_r = ", -AImag(ZUL(1,2))
Write(123,*) "ZUL13_i = ", Real(ZUL(1,3),dp)
Write(123,*) "ZUL13_r = ", -AImag(ZUL(1,3))
End if 
If (MFu(2).Gt.0._dp) Then 
Write(123,*) "ZUL21_r = ", Real(ZUL(2,1),dp)
Write(123,*) "ZUL21_i = ", AImag(ZUL(2,1))
Write(123,*) "ZUL22_r = ", Real(ZUL(2,2),dp)
Write(123,*) "ZUL22_i = ", AImag(ZUL(2,2))
Write(123,*) "ZUL23_r = ", Real(ZUL(2,3),dp)
Write(123,*) "ZUL23_i = ", AImag(ZUL(2,3))
Else 
Write(123,*) "ZUL21_i = ", Real(ZUL(2,1),dp)
Write(123,*) "ZUL21_r = ", -AImag(ZUL(2,1))
Write(123,*) "ZUL22_i = ", Real(ZUL(2,2),dp)
Write(123,*) "ZUL22_r = ", -AImag(ZUL(2,2))
Write(123,*) "ZUL23_i = ", Real(ZUL(2,3),dp)
Write(123,*) "ZUL23_r = ", -AImag(ZUL(2,3))
End if 
If (MFu(3).Gt.0._dp) Then 
Write(123,*) "ZUL31_r = ", Real(ZUL(3,1),dp)
Write(123,*) "ZUL31_i = ", AImag(ZUL(3,1))
Write(123,*) "ZUL32_r = ", Real(ZUL(3,2),dp)
Write(123,*) "ZUL32_i = ", AImag(ZUL(3,2))
Write(123,*) "ZUL33_r = ", Real(ZUL(3,3),dp)
Write(123,*) "ZUL33_i = ", AImag(ZUL(3,3))
Else 
Write(123,*) "ZUL31_i = ", Real(ZUL(3,1),dp)
Write(123,*) "ZUL31_r = ", -AImag(ZUL(3,1))
Write(123,*) "ZUL32_i = ", Real(ZUL(3,2),dp)
Write(123,*) "ZUL32_r = ", -AImag(ZUL(3,2))
Write(123,*) "ZUL33_i = ", Real(ZUL(3,3),dp)
Write(123,*) "ZUL33_r = ", -AImag(ZUL(3,3))
End if 
If (MFu(1).Gt.0._dp) Then 
Write(123,*) "ZUR11_r = ", Real(ZUR(1,1),dp)
Write(123,*) "ZUR11_i = ", AImag(ZUR(1,1))
Write(123,*) "ZUR12_r = ", Real(ZUR(1,2),dp)
Write(123,*) "ZUR12_i = ", AImag(ZUR(1,2))
Write(123,*) "ZUR13_r = ", Real(ZUR(1,3),dp)
Write(123,*) "ZUR13_i = ", AImag(ZUR(1,3))
Else 
Write(123,*) "ZUR11_i = ", Real(ZUR(1,1),dp)
Write(123,*) "ZUR11_r = ", -AImag(ZUR(1,1))
Write(123,*) "ZUR12_i = ", Real(ZUR(1,2),dp)
Write(123,*) "ZUR12_r = ", -AImag(ZUR(1,2))
Write(123,*) "ZUR13_i = ", Real(ZUR(1,3),dp)
Write(123,*) "ZUR13_r = ", -AImag(ZUR(1,3))
End if 
If (MFu(2).Gt.0._dp) Then 
Write(123,*) "ZUR21_r = ", Real(ZUR(2,1),dp)
Write(123,*) "ZUR21_i = ", AImag(ZUR(2,1))
Write(123,*) "ZUR22_r = ", Real(ZUR(2,2),dp)
Write(123,*) "ZUR22_i = ", AImag(ZUR(2,2))
Write(123,*) "ZUR23_r = ", Real(ZUR(2,3),dp)
Write(123,*) "ZUR23_i = ", AImag(ZUR(2,3))
Else 
Write(123,*) "ZUR21_i = ", Real(ZUR(2,1),dp)
Write(123,*) "ZUR21_r = ", -AImag(ZUR(2,1))
Write(123,*) "ZUR22_i = ", Real(ZUR(2,2),dp)
Write(123,*) "ZUR22_r = ", -AImag(ZUR(2,2))
Write(123,*) "ZUR23_i = ", Real(ZUR(2,3),dp)
Write(123,*) "ZUR23_r = ", -AImag(ZUR(2,3))
End if 
If (MFu(3).Gt.0._dp) Then 
Write(123,*) "ZUR31_r = ", Real(ZUR(3,1),dp)
Write(123,*) "ZUR31_i = ", AImag(ZUR(3,1))
Write(123,*) "ZUR32_r = ", Real(ZUR(3,2),dp)
Write(123,*) "ZUR32_i = ", AImag(ZUR(3,2))
Write(123,*) "ZUR33_r = ", Real(ZUR(3,3),dp)
Write(123,*) "ZUR33_i = ", AImag(ZUR(3,3))
Else 
Write(123,*) "ZUR31_i = ", Real(ZUR(3,1),dp)
Write(123,*) "ZUR31_r = ", -AImag(ZUR(3,1))
Write(123,*) "ZUR32_i = ", Real(ZUR(3,2),dp)
Write(123,*) "ZUR32_r = ", -AImag(ZUR(3,2))
Write(123,*) "ZUR33_i = ", Real(ZUR(3,3),dp)
Write(123,*) "ZUR33_r = ", -AImag(ZUR(3,3))
End if 
If (MFe(1).Gt.0._dp) Then 
Write(123,*) "ZEL11_r = ", Real(ZEL(1,1),dp)
Write(123,*) "ZEL11_i = ", AImag(ZEL(1,1))
Write(123,*) "ZEL12_r = ", Real(ZEL(1,2),dp)
Write(123,*) "ZEL12_i = ", AImag(ZEL(1,2))
Write(123,*) "ZEL13_r = ", Real(ZEL(1,3),dp)
Write(123,*) "ZEL13_i = ", AImag(ZEL(1,3))
Else 
Write(123,*) "ZEL11_i = ", Real(ZEL(1,1),dp)
Write(123,*) "ZEL11_r = ", -AImag(ZEL(1,1))
Write(123,*) "ZEL12_i = ", Real(ZEL(1,2),dp)
Write(123,*) "ZEL12_r = ", -AImag(ZEL(1,2))
Write(123,*) "ZEL13_i = ", Real(ZEL(1,3),dp)
Write(123,*) "ZEL13_r = ", -AImag(ZEL(1,3))
End if 
If (MFe(2).Gt.0._dp) Then 
Write(123,*) "ZEL21_r = ", Real(ZEL(2,1),dp)
Write(123,*) "ZEL21_i = ", AImag(ZEL(2,1))
Write(123,*) "ZEL22_r = ", Real(ZEL(2,2),dp)
Write(123,*) "ZEL22_i = ", AImag(ZEL(2,2))
Write(123,*) "ZEL23_r = ", Real(ZEL(2,3),dp)
Write(123,*) "ZEL23_i = ", AImag(ZEL(2,3))
Else 
Write(123,*) "ZEL21_i = ", Real(ZEL(2,1),dp)
Write(123,*) "ZEL21_r = ", -AImag(ZEL(2,1))
Write(123,*) "ZEL22_i = ", Real(ZEL(2,2),dp)
Write(123,*) "ZEL22_r = ", -AImag(ZEL(2,2))
Write(123,*) "ZEL23_i = ", Real(ZEL(2,3),dp)
Write(123,*) "ZEL23_r = ", -AImag(ZEL(2,3))
End if 
If (MFe(3).Gt.0._dp) Then 
Write(123,*) "ZEL31_r = ", Real(ZEL(3,1),dp)
Write(123,*) "ZEL31_i = ", AImag(ZEL(3,1))
Write(123,*) "ZEL32_r = ", Real(ZEL(3,2),dp)
Write(123,*) "ZEL32_i = ", AImag(ZEL(3,2))
Write(123,*) "ZEL33_r = ", Real(ZEL(3,3),dp)
Write(123,*) "ZEL33_i = ", AImag(ZEL(3,3))
Else 
Write(123,*) "ZEL31_i = ", Real(ZEL(3,1),dp)
Write(123,*) "ZEL31_r = ", -AImag(ZEL(3,1))
Write(123,*) "ZEL32_i = ", Real(ZEL(3,2),dp)
Write(123,*) "ZEL32_r = ", -AImag(ZEL(3,2))
Write(123,*) "ZEL33_i = ", Real(ZEL(3,3),dp)
Write(123,*) "ZEL33_r = ", -AImag(ZEL(3,3))
End if 
If (MFe(1).Gt.0._dp) Then 
Write(123,*) "ZER11_r = ", Real(ZER(1,1),dp)
Write(123,*) "ZER11_i = ", AImag(ZER(1,1))
Write(123,*) "ZER12_r = ", Real(ZER(1,2),dp)
Write(123,*) "ZER12_i = ", AImag(ZER(1,2))
Write(123,*) "ZER13_r = ", Real(ZER(1,3),dp)
Write(123,*) "ZER13_i = ", AImag(ZER(1,3))
Else 
Write(123,*) "ZER11_i = ", Real(ZER(1,1),dp)
Write(123,*) "ZER11_r = ", -AImag(ZER(1,1))
Write(123,*) "ZER12_i = ", Real(ZER(1,2),dp)
Write(123,*) "ZER12_r = ", -AImag(ZER(1,2))
Write(123,*) "ZER13_i = ", Real(ZER(1,3),dp)
Write(123,*) "ZER13_r = ", -AImag(ZER(1,3))
End if 
If (MFe(2).Gt.0._dp) Then 
Write(123,*) "ZER21_r = ", Real(ZER(2,1),dp)
Write(123,*) "ZER21_i = ", AImag(ZER(2,1))
Write(123,*) "ZER22_r = ", Real(ZER(2,2),dp)
Write(123,*) "ZER22_i = ", AImag(ZER(2,2))
Write(123,*) "ZER23_r = ", Real(ZER(2,3),dp)
Write(123,*) "ZER23_i = ", AImag(ZER(2,3))
Else 
Write(123,*) "ZER21_i = ", Real(ZER(2,1),dp)
Write(123,*) "ZER21_r = ", -AImag(ZER(2,1))
Write(123,*) "ZER22_i = ", Real(ZER(2,2),dp)
Write(123,*) "ZER22_r = ", -AImag(ZER(2,2))
Write(123,*) "ZER23_i = ", Real(ZER(2,3),dp)
Write(123,*) "ZER23_r = ", -AImag(ZER(2,3))
End if 
If (MFe(3).Gt.0._dp) Then 
Write(123,*) "ZER31_r = ", Real(ZER(3,1),dp)
Write(123,*) "ZER31_i = ", AImag(ZER(3,1))
Write(123,*) "ZER32_r = ", Real(ZER(3,2),dp)
Write(123,*) "ZER32_i = ", AImag(ZER(3,2))
Write(123,*) "ZER33_r = ", Real(ZER(3,3),dp)
Write(123,*) "ZER33_i = ", AImag(ZER(3,3))
Else 
Write(123,*) "ZER31_i = ", Real(ZER(3,1),dp)
Write(123,*) "ZER31_r = ", -AImag(ZER(3,1))
Write(123,*) "ZER32_i = ", Real(ZER(3,2),dp)
Write(123,*) "ZER32_r = ", -AImag(ZER(3,2))
Write(123,*) "ZER33_i = ", Real(ZER(3,3),dp)
Write(123,*) "ZER33_r = ", -AImag(ZER(3,3))
End if 
    Close(123) 
End Subroutine WriteWHIZARD 

 
 Subroutine WriteHiggsBounds 
Implicit None 
Open(87,file="MH_GammaTot.dat",status="unknown") 
Open(88,file="MHplus_GammaTot.dat",status="unknown") 
Open(89,file="effC.dat",status="unknown") 
Open(90,file="BR_H_NP.dat",status="unknown") 
Open(91,file="BR_Hplus.dat",status="unknown") 
Open(92,file="BR_t.dat",status="unknown") 
Open(93,file="LEP_HpHm_CS_ratios.dat",status="unknown") 
Write(87,"(I1)",advance="No") 1 
Write(88,"(I1)",advance="No") 1 
Write(87,"(2e16.8)",advance="No") Mhh
Write(88,"(2e16.8)",advance="No") MHp(2)
Write(87,"(2e16.8)",advance="No") gThh
Write(88,"(2e16.8)",advance="No") gTHp(2)
Write(90,"(I1)",advance="No") 1 
Write(90,"(e16.8)",advance="No") BRinvH(1)/gThh 

 
 
Write(92,"(I1)",advance="No") 1
Write(92,"(e16.8)",advance="No") BR_tWb 
Write(92,"(e16.8)",advance="No") BR_tHb(2) 
Write(91,"(I1)",advance="No") 1 
Write(91,"(3e16.8)",advance="No") BR_Hcs(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No") BR_Hcb(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No") BR_Htaunu(2)/gTHp(2) 
Write(89,"(I1)",advance="No") 1 
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fd(1,2)**2
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fd(1,2)**2
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fu(1,2)**2
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fu(1,2)**2
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fd(1,3)**2
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fd(1,3)**2
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fu(1,3)**2
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fu(1,3)**2
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fe(1,2)**2
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fe(1,2)**2
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fe(1,3)**2
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fe(1,3)**2
Write(89,"(3e16.8)",advance="No") rHB_S_VWp(1)**2
Write(89,"(3e16.8)",advance="No") rHB_S_VZ(1)**2
Write(89,"(3e16.8)",advance="No") 0._dp 
Write(89,"(3e16.8)",advance="No")  Real(ratioPP,dp)**2 
Write(89,"(3e16.8)",advance="No")  Real(ratioGG,dp)**2 
Write(89,"(3e16.8)",advance="No") 0._dp 
Write(89,"(e16.8)",advance="No") Real(CPL_H_H_Z(1,1), dp) 
 
 
 
Write(93,"(I1)",advance="No") 1 
Write(93,"(e16.8)",advance="No") 0.0000 
Close(87) 
Close(88) 
Close(90) 
Close(91) 
Close(92) 
Close(93) 
End Subroutine WriteHiggsBounds 
 
 

 
 Subroutine WriteHiggsBounds5 
Implicit None 
Open(87,file="MH_GammaTot.dat",status="unknown") 
Open(88,file="MHplus_GammaTot.dat",status="unknown") 
Open(89,file="effC.dat",status="unknown") 
Open(90,file="BR_H_NP.dat",status="unknown") 
Open(91,file="BR_Hplus.dat",status="unknown") 
Open(92,file="BR_t.dat",status="unknown") 
Open(93,file="LEP_HpHm_CS_ratios.dat",status="unknown") 
Write(87,"(I1)",advance="No") 1 
Write(88,"(I1)",advance="No") 1 
Write(87,"(2e16.8)",advance="No") Mhh
Write(88,"(2e16.8)",advance="No") MHp(2)
Write(87,"(2e16.8)",advance="No") gThh
Write(88,"(2e16.8)",advance="No") gTHp(2)
Write(90,"(I1)",advance="No") 1 
Write(90,"(e16.8)",advance="No") BRinvH(1)/gThh 
Write(90,"(e16.8)",advance="No") BRHll(1,1,2)/gThh 
Write(90,"(e16.8)",advance="No") BRHll(1,1,3)/gThh 
Write(90,"(e16.8)",advance="No") BRHll(1,2,3)/gThh 
Write(90,"(e16.8)",advance="No") BRHHpW(1,2)/gThh  

 
 
Write(92,"(I1)",advance="No") 1
Write(92,"(e16.8)",advance="No") BR_tWb 
Write(92,"(e16.8)",advance="No") BR_tHb(2) 
Write(91,"(I1)",advance="No") 1 
Write(91,"(3e16.8)",advance="No") BR_Hcs(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No") BR_Hcb(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No") BR_Htaunu(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No") BR_HpTB(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No") BR_HpWZ(2)/gTHp(2) 
Write(91,"(3e16.8)",advance="No")BR_HpHW(2,1)/gTHp(2) 
Write(89,"(I1)",advance="No") 1 
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fd(1,2)
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fd(1,2)
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fu(1,2)
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fu(1,2)
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fd(1,3)
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fd(1,3)
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fu(1,3)
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fu(1,3)
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fe(1,2)
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fe(1,2)
Write(89,"(3e16.8)",advance="No") rHB_S_S_Fe(1,3)
Write(89,"(3e16.8)",advance="No") rHB_S_P_Fe(1,3)
Write(89,"(3e16.8)",advance="No") rHB_S_VWp(1)
Write(89,"(3e16.8)",advance="No") rHB_S_VZ(1)
Write(89,"(3e16.8)",advance="No") 0._dp 
Write(89,"(3e16.8)",advance="No")  Real(ratioPP,dp) 
Write(89,"(3e16.8)",advance="No")  Real(ratioGG,dp) 
Write(89,"(e16.8)",advance="No") Sqrt(Real(CPL_H_H_Z(1,1), dp)) 
 
 
 
Write(93,"(I1)",advance="No") 1 
Write(93,"(e16.8)",advance="No") 0.0000 
Close(87) 
Close(88) 
Close(90) 
Close(91) 
Close(92) 
Close(93) 
End Subroutine WriteHiggsBounds5 
 
 
 Subroutine ReadMatrixC(io, nmax1, nmax2, mat, ic, mat_name, kont, fill)
  Implicit None
   Character(len=*) :: mat_name
   Integer, Intent(in) :: nmax1, nmax2, io, ic
   Integer, Intent(in), Optional :: fill
   Complex(dp), Intent(inout) :: mat(nmax1, nmax2)
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1, i2
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadMatrixC"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) i1, i2, wert, read_line

    If ((i1.Lt.1).Or.(i1.Gt.nmax1)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i1=",i1
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If
    If ((i2.Lt.1).Or.(i2.Gt.nmax2)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i2=",i2
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If

    If (ic.Eq.0) Then
     mat(i1,i2) = Cmplx(0._dp,Aimag(mat(i1,i2)),dp) + wert
     If (Present(fill).And.(i1.Ne.i2)) &
       &  mat(i2,i1) = Cmplx(0._dp, Aimag(mat(i2,i1)), dp) + wert
    Else If (ic.Eq.1) Then
     mat(i1,i2) = Real(mat(i1,i2),dp) + Cmplx(0._dp, wert, dp)
     !-------------------------------------------------------------
     ! if fill==1 -> matrix is hermitian
     ! if fill==2 -> matrix is complex symmetric
     !-------------------------------------------------------------
     If (Present(fill).And.(i1.Ne.i2)) Then
      If (fill.Eq.1) mat(i2,i1) = Real(mat(i2,i1),dp) - Cmplx(0._dp, wert, dp)
      If (fill.Eq.2) mat(i2,i1) = Real(mat(i2,i1),dp) + Cmplx(0._dp, wert, dp)
     End If
    End If

   End Do

   200 Return

  End Subroutine ReadMatrixC

 
  Subroutine ReadMatrixR(io, nmax1, nmax2, mat, mat_name, kont)
  Implicit None
   Character(len=*) :: mat_name
   Integer, Intent(in) :: nmax1, nmax2, io
   Real(dp), Intent(inout) :: mat(nmax1, nmax2)
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1, i2
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadMatrixR"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) i1, i2, wert, read_line

    If ((i1.Lt.1).Or.(i1.Gt.nmax1)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i1=",i1
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If
    If ((i2.Lt.1).Or.(i2.Gt.nmax2)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i2=",i2
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If

    mat(i1,i2) = wert

   End Do

   200 Return

  End Subroutine ReadMatrixR

  
  Subroutine ReadVectorC(io, nmax, vec, ic, vec_name, kont)
  Implicit None
   Character(len=*) :: vec_name
   Integer, Intent(in) :: nmax, io, ic
   Complex(dp), Intent(inout) :: vec(nmax)
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadVectorC"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) i1, wert, read_line

    If ((i1.Lt.1).Or.(i1.Gt.nmax)) Then
     Write(ErrCan,*) "Problem while reading "//vec_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i1=",i1
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If

    If (ic.Eq.0) vec(i1) = Cmplx(0._dp, Aimag(vec(i1)), dp) + wert
    If (ic.Eq.1) vec(i1) = Real(vec(i1),dp) + Cmplx(0._dp, wert, dp)

   End Do

   200 Return

  End Subroutine ReadVectorC


Subroutine ReadScalarC(io, vec, ic, vec_name, kont)
  Implicit None
   Character(len=*) :: vec_name
   Integer, Intent(in) :: io, ic
   Complex(dp), Intent(inout) :: vec
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadVectorC"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) wert, read_line

!     If ((i1.Lt.1).Or.(i1.Gt.nmax)) Then
!      Write(ErrCan,*) "Problem while reading "//vec_name//" in routine"// &
!         & Trim(NameOfUnit(Iname))//", index i1=",i1
!      Iname = Iname - 2
!      kont = -305 
!      Call TerminateProgram()
!     End If

    If (ic.Eq.0) vec = Cmplx(0._dp, Aimag(vec), dp) + wert
    If (ic.Eq.1) vec = Real(vec,dp) + Cmplx(0._dp, wert, dp)

   End Do

   200 Return

  End Subroutine ReadScalarC

  
  Subroutine ReadVectorR(io, nmax, vec, vec_name, kont)
  Implicit None
   Character(len=*) :: vec_name
   Integer, Intent(in) :: nmax, io
   Real(dp), Intent(inout) :: vec(nmax)
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadVectorR"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) i1, wert, read_line

    If ((i1.Lt.1).Or.(i1.Gt.nmax)) Then
     Write(ErrCan,*) "Problem while reading "//vec_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i1=",i1
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If

    vec(i1) = wert

   End Do

   200 Return

  End Subroutine ReadVectorR

Subroutine ReadScalarR(io, vec, vec_name, kont)
  Implicit None
   Character(len=*) :: vec_name
   Integer, Intent(in) :: io
   Real(dp), Intent(inout) :: vec
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadVectorR"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) wert, read_line

!     If ((i1.Lt.1).Or.(i1.Gt.nmax)) Then
!      Write(ErrCan,*) "Problem while reading "//vec_name//" in routine"// &
!         & Trim(NameOfUnit(Iname))//", index i1=",i1
!      Iname = Iname - 2
!      kont = -305 
!      Call TerminateProgram()
!     End If

    vec = wert

   End Do

   200 Return

  End Subroutine ReadScalarR

  
  Subroutine ReadTensorC(io, nmax1, nmax2, nmax3, mat, ic, mat_name, kont)
  Implicit None
   Character(len=*) :: mat_name
   Integer, Intent(in) :: nmax1, nmax2, nmax3, io, ic
   Complex(dp), Intent(inout) :: mat(nmax1, nmax2, nmax3)
   Integer, Intent(out) :: kont

   Character(len=80) :: read_line
   Integer :: i1, i2, i3
   Real(dp) :: wert

   kont = 0

   Iname = Iname + 1
   NameOfUnit(Iname) = "ReadTensorC"
   Do 
    Read(io,*,End=200) read_line
!     Write(*,*) read_line
    If (read_line(1:1).Eq."#") Cycle ! ignore comments
    Backspace(io)                    ! resetting to the beginning of the line
    If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Then
     Iname = Iname - 1
     Return ! new block
    End If

    Read(io,*) i1, i2, i3, wert, read_line

    If ((i1.Lt.1).Or.(i1.Gt.nmax1)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i1=",i1
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If
    If ((i2.Lt.1).Or.(i2.Gt.nmax2)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i2=",i2
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If
    If ((i3.Lt.1).Or.(i3.Gt.nmax3)) Then
     Write(ErrCan,*) "Problem while reading "//mat_name//" in routine"// &
        & Trim(NameOfUnit(Iname))//", index i3=",i3
     Iname = Iname - 2
     kont = -305 
     Call TerminateProgram()
    End If

    If (ic.Eq.0) mat(i1,i2,i3) = Cmplx(0._dp, Aimag(mat(i1,i2,i3)), dp) + wert
    If (ic.Eq.1) mat(i1,i2,i3) = mat(i1,i2,i3) + Cmplx(0._dp, wert, dp)

   End Do

   200 Return

  End Subroutine ReadTensorC

 Subroutine SetWriteMinBR(wert)
 !-------------------------------------------------------------------
 ! sets the minimal branching ratio (=wert) appearing in the output
 !-------------------------------------------------------------------
 Implicit None
  Real(dp), Intent(in) :: wert
  BrMin = wert
 End Subroutine SetWriteMinBR


 Subroutine SetWriteMinSig(wert)
 !-------------------------------------------------------------------
 ! sets the minimal cross section (=wert) appearing in the output
 !-------------------------------------------------------------------
 Implicit None
  Real(dp), Intent(in) :: wert
  SigMin = wert
 End Subroutine SetWriteMinSig

 Subroutine Warn_CPV(i_cpv, name)
  Implicit None 
   Integer, Intent(in) :: i_cpv
   Character(len=*), Intent(in) :: name
   If (i_cpv.Eq.0) Write(ErrCan,*) "CP violation is switched off"
   If (i_cpv.Eq.1) Write(ErrCan,*) "CP violation beyond CKM is switched off"
   Write(ErrCan,*) "Ignoring block "//Trim(name)
   If (ErrorLevel.Eq.2) Call TerminateProgram
  End Subroutine Warn_CPV

Subroutine PutUpperCase(name)
 Implicit None
  Character(len=80), Intent(inout) :: name
  Integer :: len=80, i1
  Do i1=1,len
   If (name(i1:i1).Eq."a") name(i1:i1) = "A"
   If (name(i1:i1).Eq."b") name(i1:i1) = "B"
   If (name(i1:i1).Eq."c") name(i1:i1) = "C"
   If (name(i1:i1).Eq."d") name(i1:i1) = "D"
   If (name(i1:i1).Eq."e") name(i1:i1) = "E"
   If (name(i1:i1).Eq."f") name(i1:i1) = "F"
   If (name(i1:i1).Eq."g") name(i1:i1) = "G"
   If (name(i1:i1).Eq."h") name(i1:i1) = "H"
   If (name(i1:i1).Eq."i") name(i1:i1) = "I"
   If (name(i1:i1).Eq."j") name(i1:i1) = "J"
   If (name(i1:i1).Eq."k") name(i1:i1) = "K"
   If (name(i1:i1).Eq."l") name(i1:i1) = "L"
   If (name(i1:i1).Eq."m") name(i1:i1) = "M"
   If (name(i1:i1).Eq."n") name(i1:i1) = "N"
   If (name(i1:i1).Eq."o") name(i1:i1) = "O"
   If (name(i1:i1).Eq."p") name(i1:i1) = "P"
   If (name(i1:i1).Eq."q") name(i1:i1) = "Q"
   If (name(i1:i1).Eq."r") name(i1:i1) = "R"
   If (name(i1:i1).Eq."s") name(i1:i1) = "S"
   If (name(i1:i1).Eq."t") name(i1:i1) = "T"
   If (name(i1:i1).Eq."u") name(i1:i1) = "U"
   If (name(i1:i1).Eq."v") name(i1:i1) = "V"
   If (name(i1:i1).Eq."w") name(i1:i1) = "W"
   If (name(i1:i1).Eq."x") name(i1:i1) = "X"
   If (name(i1:i1).Eq."y") name(i1:i1) = "Y"
   If (name(i1:i1).Eq."z") name(i1:i1) = "Z"
  End Do
 End Subroutine PutUpperCase

 Subroutine Read_FCONST(io)
  Implicit None
   Integer, Intent(in) :: io
      Real(dp) :: r_mod, wert
   Integer :: i_mod, i_test, i_rp
   Character(len=80) :: read_line
    Do 
     Read(io,*) read_line
     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop
     Read(io,*) i_test,i_mod,wert ! ,read_line
     If (i_test.Eq.321) Then
      If (i_mod.Eq.1) Then
       f_k_CONST = wert
      Else If (i_mod.Eq.11) Then
       h_k_CONST = wert
      End If
     Else If (i_test.Eq.511) Then
      If (i_mod.Eq.1) Then
       f_B0d_CONST = wert
      End If
     Else If (i_test.Eq.531) Then
      If (i_mod.Eq.1) Then
       f_B0s_CONST = wert
      End If
     Else If (i_test.Eq.221) Then
      If (i_mod.Eq.1) Then
       f_eta_q_CONST = wert
      Else If (i_mod.Eq.2) Then
       f_eta_s_CONST = wert
      Else If (i_mod.Eq.11) Then
       h_eta_q_CONST = wert
      Else If (i_mod.Eq.12) Then
       h_eta_s_CONST = wert
      End If
     Else If (i_test.Eq.213) Then
      If (i_mod.Eq.1) Then
       f_rho_CONST = wert
      Else If (i_mod.Eq.11) Then
       h_rho_CONST = wert
      End If
     Else If (i_test.Eq.223) Then
      If (i_mod.Eq.1) Then
       f_omega_q_CONST = wert
      Else If (i_mod.Eq.2) Then
       f_omega_s_CONST = wert
      Else If (i_mod.Eq.11) Then
       h_omega_q_CONST = wert
      Else If (i_mod.Eq.12) Then
       h_omega_s_CONST = wert
      End If
     End If
    End Do ! i_mod
  End Subroutine Read_FCONST


 
Subroutine Read_FLIFE(io)
  Implicit None
   Integer, Intent(in) :: io
   Real(dp) :: r_mod, wert
   Integer :: i_mod, i_test, i_rp
   Character(len=80) :: read_line
    Do 
     Read(io,*) read_line
     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop
     Read(io,*) i_test,wert ! ,read_line
     If (i_test.Eq.111) Then
      tau_pi0 = wert
     Else if (i_test.Eq.211) Then
      tau_pip = wert
     Else if (i_test.Eq.113) Then
      tau_rho0 = wert
     Else if (i_test.Eq.213) Then
      tau_rhop = wert
     Else if (i_test.Eq.411) Then
      tau_Dp = wert
     Else if (i_test.Eq.421) Then
      tau_D0 = wert
     Else if (i_test.Eq.431) Then
      tau_DSp = wert
     Else if (i_test.Eq.433) Then
      tau_DSsp = wert
     Else if (i_test.Eq.221) Then
      tau_eta = wert
     Else if (i_test.Eq.331) Then
      tau_etap = wert
     Else if (i_test.Eq.223) Then
      tau_omega = wert
     Else if (i_test.Eq.333) Then
      tau_phi = wert
     Else if (i_test.Eq.130) Then
      tau_KL0 = wert
     Else if (i_test.Eq.310) Then
      tau_KS0 = wert
     Else if (i_test.Eq.311) Then
      tau_K0 = wert
     Else if (i_test.Eq.321) Then
      tau_Kp = wert
     Else if (i_test.Eq.511) Then
      tau_B0d = wert
     Else if (i_test.Eq.531) Then
      tau_B0s = wert
     Else if (i_test.Eq.521) Then
      tau_B0p = wert
     Else if (i_test.Eq.513) Then
      tau_B0c = wert
     Else if (i_test.Eq.523) Then
      tau_Bpc = wert
     Else if (i_test.Eq.533) Then
      tau_Bs0c = wert
     Else if (i_test.Eq.541) Then
      tau_Bcp = wert
     Else if (i_test.Eq.543) Then
      tau_Bcpc = wert
     Else if (i_test.Eq.313) Then
      tau_K0c = wert
     Else if (i_test.Eq.323) Then
      tau_Kpc = wert
     Else if (i_test.Eq.441) Then
      tau_etac = wert
     Else if (i_test.Eq.443) Then
      tau_JPsi = wert
     Else if (i_test.Eq.553) Then
      tau_Ups = wert
     Else if (i_test.Eq.551) Then
      tau_etab = wert
     End If
    End Do ! i_mod
  End Subroutine Read_FLIFE

Subroutine Read_FMASS(io)
  Implicit None
   Integer, Intent(in) :: io
   Real(dp) :: r_mod, wert
   Integer :: i_mod, i_test, i_rp
   Character(len=80) :: read_line
    Do 
     Read(io,*) read_line
     If (read_line(1:1).Eq."#") Cycle ! this loop
     Backspace(io) ! resetting to the beginning of the line
     If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b") ) Exit ! this loop
     Read(io,*) i_test,wert ! ,read_line
     If (i_test.Eq.111) Then
      mass_pi0 = wert
     Else if (i_test.Eq.211) Then
      mass_pip = wert
     Else if (i_test.Eq.113) Then
      mass_rho0 = wert
     Else if (i_test.Eq.213) Then
      mass_rhop = wert
     Else if (i_test.Eq.411) Then
      mass_Dp = wert
     Else if (i_test.Eq.421) Then
      mass_D0 = wert
     Else if (i_test.Eq.431) Then
      mass_DSp = wert
     Else if (i_test.Eq.433) Then
      mass_DSsp = wert
     Else if (i_test.Eq.221) Then
      mass_eta = wert
     Else if (i_test.Eq.331) Then
      mass_etap = wert
     Else if (i_test.Eq.223) Then
      mass_omega = wert
     Else if (i_test.Eq.333) Then
      mass_phi = wert
     Else if (i_test.Eq.130) Then
      mass_KL0 = wert
     Else if (i_test.Eq.310) Then
      mass_KS0 = wert
     Else if (i_test.Eq.311) Then
      mass_K0 = wert
     Else if (i_test.Eq.321) Then
      mass_Kp = wert
     Else if (i_test.Eq.511) Then
      mass_B0d = wert
     Else if (i_test.Eq.531) Then
      mass_B0s = wert
     Else if (i_test.Eq.521) Then
      mass_B0p = wert
     Else if (i_test.Eq.513) Then
      mass_B0c = wert
     Else if (i_test.Eq.523) Then
      mass_Bpc = wert
     Else if (i_test.Eq.533) Then
      mass_Bs0c = wert
     Else if (i_test.Eq.541) Then
      mass_Bcp = wert
     Else if (i_test.Eq.543) Then
      mass_Bcpc = wert
     Else if (i_test.Eq.313) Then
      mass_K0c = wert
     Else if (i_test.Eq.323) Then
      mass_Kpc = wert
     Else if (i_test.Eq.441) Then
      mass_etac = wert
     Else if (i_test.Eq.443) Then
      mass_JPsi = wert
     Else if (i_test.Eq.553) Then
      mass_Ups = wert
     Else if (i_test.Eq.551) Then
      mass_etab = wert
     End If
    End Do ! i_mod
  End Subroutine Read_FMASS
Subroutine Read_GAUGEIN(io,i_c,i_model,set_mod_par,kont) 
Implicit None 
Integer,Intent(in)::io,i_c,i_model 
Integer,Intent(inout)::kont,set_mod_par(:) 
Integer::i_par 
Real(dp)::wert 
Character(len=80)::read_line 
Do 
Read(io,*,End=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*) i_par,wert!,read_line 
If (i_par.Eq.1) Then 
g1IN= wert 
InputValueforg1= .True. 
Else If (i_par.Eq.2) Then 
g2IN= wert 
InputValueforg2= .True. 
Else If (i_par.Eq.3) Then 
g3IN= wert 
InputValueforg3= .True. 
Else
Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
If (i_c.Eq.0) Write(ErrCan,*) "Unknown entry for Block GAUGEIN ",i_par
If (i_c.Eq.1) Write(ErrCan,*) "Unknown entry for Block IMGAUGEIN ",i_par
If (i_c.Eq.0) Write(*,*) "Unknown entry for Block GAUGEIN ",i_par
If (i_c.Eq.1) Write(*,*) "Unknown entry for Block IMGAUGEIN ",i_par
Call AddError(304)
If (ErrorLevel.Eq.2) Call TerminateProgram
End If
End Do! i_par
200 Return
End Subroutine Read_GAUGEIN 
 
 
Subroutine Read_HDMIN(io,i_c,i_model,set_mod_par,kont) 
Implicit None 
Integer,Intent(in)::io,i_c,i_model 
Integer,Intent(inout)::kont,set_mod_par(:) 
Integer::i_par 
Real(dp)::wert 
Character(len=80)::read_line 
Do 
Read(io,*,End=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*) i_par,wert!,read_line 
If (i_par.Eq.5) Then 
If (i_c.Eq.0) Lam5IN= Cmplx(wert,Aimag(Lam5IN),dp) 
If (i_c.Eq.1) Lam5IN= Cmplx(Real(Lam5IN,dp),wert,dp) 
InputValueforLam5= .True. 
Else If (i_par.Eq.1) Then 
If (i_c.Eq.0) Lam1IN= Cmplx(wert,Aimag(Lam1IN),dp) 
If (i_c.Eq.1) Lam1IN= Cmplx(Real(Lam1IN,dp),wert,dp) 
InputValueforLam1= .True. 
Else If (i_par.Eq.4) Then 
If (i_c.Eq.0) Lam4IN= Cmplx(wert,Aimag(Lam4IN),dp) 
If (i_c.Eq.1) Lam4IN= Cmplx(Real(Lam4IN,dp),wert,dp) 
InputValueforLam4= .True. 
Else If (i_par.Eq.3) Then 
If (i_c.Eq.0) Lam3IN= Cmplx(wert,Aimag(Lam3IN),dp) 
If (i_c.Eq.1) Lam3IN= Cmplx(Real(Lam3IN,dp),wert,dp) 
InputValueforLam3= .True. 
Else If (i_par.Eq.2) Then 
If (i_c.Eq.0) Lam2IN= Cmplx(wert,Aimag(Lam2IN),dp) 
If (i_c.Eq.1) Lam2IN= Cmplx(Real(Lam2IN,dp),wert,dp) 
InputValueforLam2= .True. 
Else
Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
If (i_c.Eq.0) Write(ErrCan,*) "Unknown entry for Block HDMIN ",i_par
If (i_c.Eq.1) Write(ErrCan,*) "Unknown entry for Block IMHDMIN ",i_par
If (i_c.Eq.0) Write(*,*) "Unknown entry for Block HDMIN ",i_par
If (i_c.Eq.1) Write(*,*) "Unknown entry for Block IMHDMIN ",i_par
Call AddError(304)
If (ErrorLevel.Eq.2) Call TerminateProgram
End If
End Do! i_par
200 Return
End Subroutine Read_HDMIN 
 
 
Subroutine Read_MSOFTIN(io,i_c,i_model,set_mod_par,kont) 
Implicit None 
Integer,Intent(in)::io,i_c,i_model 
Integer,Intent(inout)::kont,set_mod_par(:) 
Integer::i_par 
Real(dp)::wert 
Character(len=80)::read_line 
Do 
Read(io,*,End=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*) i_par,wert!,read_line 
If (i_par.Eq.21) Then 
mHd2IN= wert 
InputValueformHd2= .True. 
Else If (i_par.Eq.22) Then 
mHu2IN= wert 
InputValueformHu2= .True. 
Else
Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
If (i_c.Eq.0) Write(ErrCan,*) "Unknown entry for Block MSOFTIN ",i_par
If (i_c.Eq.1) Write(ErrCan,*) "Unknown entry for Block IMMSOFTIN ",i_par
If (i_c.Eq.0) Write(*,*) "Unknown entry for Block MSOFTIN ",i_par
If (i_c.Eq.1) Write(*,*) "Unknown entry for Block IMMSOFTIN ",i_par
Call AddError(304)
If (ErrorLevel.Eq.2) Call TerminateProgram
End If
End Do! i_par
200 Return
End Subroutine Read_MSOFTIN 
 
 
Subroutine Read_HMIXIN(io,i_c,i_model,set_mod_par,kont) 
Implicit None 
Integer,Intent(in)::io,i_c,i_model 
Integer,Intent(inout)::kont,set_mod_par(:) 
Integer::i_par 
Real(dp)::wert 
Character(len=80)::read_line 
Do 
Read(io,*,End=200) read_line 
If (read_line(1:1).Eq."#") Cycle! this loop 
Backspace(io)! resetting to the beginning of the line 
If ((read_line(1:1).Eq."B").Or.(read_line(1:1).Eq."b")) Exit! this loop 
Read(io,*) i_par,wert!,read_line 
If (i_par.Eq.3) Then 
vIN= wert 
Else
Write(ErrCan,*) "Error in routine "//NameOfUnit(Iname)
If (i_c.Eq.0) Write(ErrCan,*) "Unknown entry for Block HMIXIN ",i_par
If (i_c.Eq.1) Write(ErrCan,*) "Unknown entry for Block IMHMIXIN ",i_par
If (i_c.Eq.0) Write(*,*) "Unknown entry for Block HMIXIN ",i_par
If (i_c.Eq.1) Write(*,*) "Unknown entry for Block IMHMIXIN ",i_par
Call AddError(304)
If (ErrorLevel.Eq.2) Call TerminateProgram
End If
End Do! i_par
200 Return
End Subroutine Read_HMIXIN 
 
 
Subroutine Switch_to_superCKM(Y_d, Y_u, Ad_in, Au_in, MD_in, MQ_in, MU_in &
                      &, Ad_out, Au_out, MD_out, MQ_out, MU_out, tr        &
                      &, RSd_in, RSu_in, RSd_out, RSu_out, CKM_out, Yd_out, Yu_out )
 !---------------------------------------------------------------------------
 ! shifts the parameter from the electroweak basis to the super CKM basis
 ! written by werner Porod, 12.03.08
 !---------------------------------------------------------------------------
 Implicit None
  Complex(dp), Intent(in), Dimension(3,3) :: Y_d, Y_u, Au_in, Ad_in, MD_in &
        & , MQ_in, MU_in
  Complex(dp), Optional, Intent(in), Dimension(6,6) :: RSu_in, RSd_in
  Logical, Intent(in) :: tr  ! if true, then the matrices are transposed 
                             ! compared to low energy definition
  Complex(dp), Intent(out), Dimension(3,3) :: Au_out, Ad_out, MD_out, MQ_out &
        & , MU_out, Yd_out, Yu_out
  Complex(dp), Optional, Intent(out), Dimension(6,6) :: RSu_out, RSd_out
  Complex(dp), Optional, Intent(out) :: CKM_out(3,3)

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

  If (Present(CKM_out)) CKM_out = CKM_Q
  !-------------------------------------------------------------------
  ! shifting the parameters to the super CKM basis
  !-------------------------------------------------------------------

   Au_out = Matmul( Matmul(Conjg(uU_L), Au_in), Conjg(Transpose(uU_R)))

   Ad_out = Matmul( Matmul(Conjg(uD_L), Ad_in), Conjg(Transpose(uD_R)))


  MD_out = Matmul( Matmul( Conjg(uD_L), Transpose(MD_in)), Transpose(uD_L))
  MU_out = Matmul( Matmul( Conjg(uU_L), Transpose( MU_in)), Transpose(uU_L))
  MQ_out = Matmul( Matmul( uD_R, MQ_in), Transpose(Conjg(uD_R)) )

   If (Present(RSu_in).And.Present(RSu_out)) Then
    rot = 0._dp
    rot(1:3,1:3) = Conjg(uU_L)
    rot(4:6,4:6) = uU_R
    RSu_out = Matmul(RSu_in,Transpose(rot))
   End If
   If (Present(RSd_in).And.Present(RSd_out)) Then
    rot = 0._dp
    rot(1:3,1:3) = Conjg(uD_L)
    rot(4:6,4:6) = uD_R
    RSd_out = Matmul(RSd_in,Transpose(rot))
   End If

 End Subroutine Switch_to_superCKM




 Subroutine Switch_to_superPMNS(Y_l, uN_L, Al_in, ME_in, ML_in &
                      &, Al_out, ME_out, ML_out, tr            &
                      &, RSl_in, RSn_in, RSl_out, RSn_out, PMNS_out, Yl )
 !---------------------------------------------------------------------------
 ! shifts the parameter from the electroweak basis to the super PMNS basis
 ! written by werner Porod, 12.03.08
 !---------------------------------------------------------------------------
 Implicit None
  Complex(dp), Intent(in), Dimension(3,3) :: Y_l, uN_L, Al_in, ME_in, ML_in
  Complex(dp), Optional, Intent(in) :: RSl_in(6,6), RSn_in(3,3)
  Logical, Intent(in) :: tr  ! if true, then the matrices are transposed 
                             ! compared to low energy definition
  Complex(dp), Intent(out), Dimension(3,3) :: Al_out, ME_out, ML_out
  Complex(dp), Optional, Intent(out), Dimension(6,6) :: RSl_out(6,6)
  Complex(dp), Optional, Intent(out) :: PMNS_out(3,3), RSn_out(3,3)
  Complex(dp), Optional, Intent(out) :: Yl(3,3)

  Complex(dp), Dimension(3,3) :: uL_L, uL_R, PMNS_Q
  Complex(dp) :: rot(6,6)

  Real(dp) :: mf(3)
  Integer :: ierr

  !------------------------------------------
  ! diagonalizing d- and u-Yukawa couplings
  ! I am only interested in the mixing matrices
  !------------------------------------------



   If (tr) Then
   Call FermionMass(Transpose(Y_l), 1._dp, mf, uL_L, uL_R, ierr)
  Else
   Call FermionMass(Y_l, 1._dp, mf, uL_L, uL_R, ierr)
  End If

  If (Present(Yl)) Then 
    Yl = 0._dp
    Yl(1,1) = sqrt2 * mf(1)
    Yl(2,2) = sqrt2 * mf(2)
    Yl(3,3) = sqrt2 * mf(3)
  End if

  !---------------------------------------------------------
  ! PMNS matrix at Q, shifting phases according to PDG form
  !---------------------------------------------------------
  PMNS_Q =  Matmul(uL_L, uN_L)

  If (Present(PMNS_out)) PMNS_out = PMNS_Q
  !-------------------------------------------------------------------
  ! shifting the parameters to the super PMNS basis
  !-------------------------------------------------------------------
  If (tr) Then
   Al_out = Matmul( Matmul(uL_R, Al_in), Transpose(Conjg(uL_L)))

   ME_out = Matmul( Matmul( uL_R, ME_in), Transpose(Conjg(uL_R)))
   ML_out = Matmul( Matmul( Transpose(uL_L), ML_in), Conjg(uL_L) )

  Else
   Al_out = Matmul( Matmul(Conjg(uL_L), Al_in), Transpose(uL_R))

   ME_out = Matmul( Matmul( Conjg(uL_R), ME_in), Transpose(uL_R))
   ML_out = Matmul( Matmul( uL_L, ML_in), Transpose(Conjg(uL_L)) )

  End If
  !------------------------------------------------------------------
  ! to avoid numerical problems ensure that matrices are hermitian
  !-----------------------------------------------------------------
  ME_out = 0.5_dp * ( ME_out + Conjg(Transpose(ME_out)) )
  ML_out = 0.5_dp * ( ML_out + Conjg(Transpose(ML_out)) )

   If (Present(RSn_in).And.Present(RSn_out)) Then
    RSn_out = Matmul(RSn_in, Conjg(uN_L) )
   End If
   If (Present(RSl_in).And.Present(RSl_out)) Then
    rot = 0._dp
    rot(1:3,1:3) = Transpose(uL_L)
    rot(4:6,4:6) = Transpose(Conjg(uL_R))
    RSl_out = Matmul(RSl_in, rot)
   End If

 End Subroutine Switch_to_superPMNS

Subroutine SLHA1converter(MSd,MSd2, MSu,MSu2, MSe, MSe2, MSv, MSv2, &
   & ZD,ZU,ZE,ZV,Ztop,Zbottom,Ztau,  &
   & PDGd, PDGu, PDGe, PDGv, NamesD, NamesU, NamesE, NamesV)
Implicit None
Real(dp), Intent(inout) :: MSd(6), MSu(6), MSe(6), MSv(3), MSd2(6), MSu2(6), MSe2(6), MSv2(3)
Character(len=30),Dimension(6), Intent(inout) :: NamesD, NamesU, NamesE
Character(len=30),Dimension(3), Intent(inout) :: NamesV
Complex(dp), Intent(inout) :: PDGd(6), PDGu(6), PDGe(6), PDGv(3)
Complex(dp), Intent(in) :: ZU(6,6), ZD(6,6), ZE(6,6), ZV(3,3)
Complex(dp), Intent(out) :: Ztop(2,2), Zbottom(2,2), Ztau(2,2)
Real(dp) :: MSdt(6), MSut(6), MSet(6), MSvt(3)
Character(len=30),Dimension(6) :: NamesDt, NamesUt, NamesEt
Character(len=30),Dimension(3) :: NamesVt
Complex(dp) :: PDGdt(6), PDGut(6), PDGet(6), PDGvt(3)


Integer :: i1, i2, i3, ii, jj, i_zaehl


! Down-Squark

Call CheckMixingMatrix6(ZD, Zbottom,MSd,MSdt, PDGd, PDGdt, NamesD, NamesDt, 1)
!GammaD = GammaDt
!BrD = BrDt
PDGd = PDGdt
NamesD = NamesDt
! MSd = MSdt
! MSd2 = MSdt**2
   

! Up-Squark

Call CheckMixingMatrix6(ZU, Ztop,MSu,MSut, PDGu, PDGut, NamesU, NamesUt,2)
!GammaU = GammaUt
!BrU = BrUt
PDGu = PDGut
NamesU = NamesUt
! MSu = MSut
! MSu2 = MSut**2


! Selectron

Call CheckMixingMatrix6(ZE, Ztau,MSe,MSet, PDGe, PDGet, NamesE, NamesEt,3)
!GammaE = GammaEt
PDGe = PDGet
NamesE = NamesEt
!BrE = BrEt
! MSe = MSet
! MSe2 = MSet**2

! Sneutrino

Call CheckMixingMatrix3(ZV, MSv,MSvt, PDGv, PDGvt, NamesV, NamesVt)
!GammaV = GammaVt
PDGv = PDGvt
NamesV = NamesVt
!BrV = BrVt
! MSv = MSvt
! MSv2 = MSvt**2

Contains 

Subroutine CheckMixingMatrix6(Z,Z_out,m_in,m_out, PDG_in, PDG_out, Names_in, Names_out,particle)
Implicit None
Complex(dp), Intent(in) :: Z(6,6)
Complex(dp), Intent(out) :: Z_out(2,2)
Character(len=30),Dimension(6), Intent(in) :: Names_in
Character(len=30),Dimension(6), Intent(out) :: Names_out
Character(len=30) :: Names_temp, Names_save(6)
Complex(dp), Intent(in) :: PDG_in(6)
Complex(dp), Intent(out) :: PDG_out(6)
Complex(dp) :: PDG_temp, PDG_save(6)
Real(dp), Intent(in) :: m_in(6)
Real(dp) :: mat6R(6,6), mtemp, Maxcont, Z_temp(2)
Integer, Intent(in) ::particle
Real(dp), Intent(out) :: m_out(6)
Integer :: i1, ii, jj, PDG3, PDG6

      Select Case(particle)
       Case(1)  ! d-squark
          Names_save(1) = "SdL"
          Names_save(2) = "SsL"
          Names_save(3) = "Sb1" 
          Names_save(4) = "SdR"
          Names_save(5) = "SsR"
          Names_save(6) = "Sb2" 
          PDG_save(1) = 1000001
          PDG_save(2) = 1000003
          PDG_save(3) = 1000005
          PDG_save(4) = 2000001
          PDG_save(5) = 2000003
          PDG_save(6) = 2000005
       Case(2)  ! u-squark
          Names_save(1) = "SuL"
          Names_save(2) = "ScL"
          Names_save(3) = "St1" 
          Names_save(4) = "SuR"
          Names_save(5) = "ScR"
          Names_save(6) = "St2"
          PDG_save(1) = 1000002
          PDG_save(2) = 1000004
          PDG_save(3) = 1000006
          PDG_save(4) = 2000002
          PDG_save(5) = 2000004
          PDG_save(6) = 2000006 
       Case(3)  ! selectron
          Names_save(1) = "SeL"
          Names_save(2) = "SmuL"
          Names_save(3) = "Stau1" 
          Names_save(4) = "SeR"
          Names_save(5) = "SmuR"
          Names_save(6) = "Stau2"
          PDG_save(1) = 1000011
          PDG_save(2) = 1000013
          PDG_save(3) = 1000015
          PDG_save(4) = 2000011
          PDG_save(5) = 2000013
          PDG_save(6) = 2000015 
      End Select


     mat6R = Abs(Z)
     Do i1=1,6
      jj = Maxloc(mat6R(i1,:),1)
      m_out(jj) = m_in(i1)
      PDG_out(i1) = PDG_save(jj)
      Names_out(i1) = Names_save(jj)
      If (jj.eq.3) Then
         Z_out(1,1) = MaxVal(mat6R(i1,:))
         PDG3 = i1
      End if
      If (jj.eq.6) Then
          Z_out(2,2) = MaxVal(mat6R(i1,:)) 
          PDG6 = i1
      End if
!       mat6R(ii,:) = 0._dp
!       mat6R(:,jj) = 0._dp
     End Do
      Z_out(1,2) = sqrt(1._dp - Z_out(1,1)**2)
      Z_out(2,1) = -Z_out(1,2)
     If (M_out(3).gt.M_out(6)) Then

      Names_out(PDG3) = Names_save(6)
      Names_out(PDG6) = Names_save(3) 

      PDG_out(PDG3) = PDG_save(6)
      PDG_out(PDG6) = PDG_save(3) 

      Z_temp = Z_out(1,:)
      Z_out(1,:) = Z_out(2,:)
      Z_out(2,:) = Z_temp
     End if






End Subroutine CheckMixingMatrix6


Subroutine CheckMixingMatrix3(Z,m_in,m_out, PDG_in, PDG_out, Names_in, Names_out)
Implicit None
Complex(dp), Intent(in) :: Z(3,3)
Real(dp), Intent(in) :: m_in(3)
Character(len=30),Dimension(3), Intent(in) :: Names_in
Character(len=30),Dimension(3), Intent(out) :: Names_out
Character(len=30),Dimension(3) :: Names_save
Complex(dp), Intent(in) :: PDG_in(3)
Complex(dp), Intent(out) :: PDG_out(3)
Complex(dp) :: PDG_save(3)
Real(dp), Intent(out) :: m_out(3)
Real(dp) :: mat6R(3,3), mtemp, Maxcont
Integer :: i1, ii, jj

          PDG_save(1) = 1000012
          PDG_save(2) = 1000014
          PDG_save(3) = 1000016
          Names_save(1) = "Snu_e"
          Names_save(2) = "Snu_mu"
          Names_save(3) = "Snu_tau" 

     mat6R = Abs(Z)
     Do i1=1,3
      jj = Maxloc(mat6R(i1,:),1)
      m_out(jj) = m_in(i1)
      PDG_out(i1) = PDG_save(jj)
      Names_out(i1) = Names_save(jj)
!       mat6R(ii,:) = 0._dp
!       mat6R(:,jj) = 0._dp
     End Do

End Subroutine CheckMixingMatrix3


End Subroutine SLHA1converter
End Module InputOutput_Inert 
 
