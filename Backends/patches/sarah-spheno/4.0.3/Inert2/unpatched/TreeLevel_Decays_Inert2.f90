! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:47 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module TreeLevelDecays_Inert2
 
Use Control 
Use DecayFunctions 
Use Settings 
Use LoopCouplings_Inert2 
Use CouplingsForDecays_Inert2 
Use Model_Data_Inert2 
Use Mathematics, Only: Li2 
 
 Contains 
 
  
Subroutine FuTwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),            & 
& cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT(:) 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Iname = Iname + 1 
NameOfUnit(Iname) = 'FuTwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 1 
  i_end = 3
  gT = 0._dp 
  gPartial = 0._dp 
Else If ( (i_in.Ge.1).And.(i_in.Le.3) ) Then 
  i_start = i_in 
  i_end = i_in 
  gT(i_in) = 0._dp 
  gPartial(i_in,:) = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,3

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,3

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
Do i1=i_start,i_end 
m_in = MFu(i1) 
If (m_in.Eq.0._dp) Cycle 
Call CouplingsFor_Fu_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVZL,cplcFuFuVZR,deltaM)

i_count = 1 

 
! ----------------------------------------------
! Fd, Hp
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=2, 2
m1out = MFd(gt1)
m2out = MHp(gt2)
coupL = cplcFuFdHpL(i1,gt1,gt2)
coupR = cplcFuFdHpR(i1,gt1,gt2)
Call FermionToFermionScalar(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
If (gt1.eq.3) Then 
  BR_tHb = gPartial(i1,i_count) 
End if 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fd, VWp
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = MVWp
coupL = cplcFuFdVWpL(i1,gt1)
coupR = cplcFuFdVWpR(i1,gt1)
Call FermionToFermionVectorBoson(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
If (gt1.eq.3) Then 
  BR_tWb = gPartial(i1,i_count) 
End if 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, hh
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = Mhh
coupL = cplcFuFuhhL(i1,gt1)
coupR = cplcFuFuhhR(i1,gt1)
Call FermionToFermionScalar(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, VZ
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = MVZ
coupL = cplcFuFuVZL(i1,gt1)
coupR = cplcFuFuVZR(i1,gt1)
Call FermionToFermionVectorBoson(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, A0
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = MA0
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, H0
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = MH0
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, VG
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, VP
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 
If ((Present(BR)).And.(gT(i1).Eq.0)) Then 
  BR(i1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(i1,:) = gPartial(i1,:)/gT(i1) 
End if 
 
End Do 
 
Iname = Iname - 1 
 
End Subroutine FuTwoBodyDecay
 
 
Subroutine FeTwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),& 
& cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3)

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT(:) 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Iname = Iname + 1 
NameOfUnit(Iname) = 'FeTwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 1 
  i_end = 3
  gT = 0._dp 
  gPartial = 0._dp 
Else If ( (i_in.Ge.1).And.(i_in.Le.3) ) Then 
  i_start = i_in 
  i_end = i_in 
  gT(i_in) = 0._dp 
  gPartial(i_in,:) = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,3

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,3

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
Do i1=i_start,i_end 
m_in = MFe(i1) 
If (m_in.Eq.0._dp) Cycle 
Call CouplingsFor_Fe_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,deltaM)

i_count = 1 

 
! ----------------------------------------------
! Fe, hh
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFe(gt1)
m2out = Mhh
coupL = cplcFeFehhL(i1,gt1)
coupR = cplcFeFehhR(i1,gt1)
Call FermionToFermionScalar(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fe, VZ
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFe(gt1)
m2out = MVZ
coupL = cplcFeFeVZL(i1,gt1)
coupR = cplcFeFeVZR(i1,gt1)
Call FermionToFermionVectorBoson(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fv, conj[Hp]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=2, 2
m1out = 0._dp
m2out = MHp(gt2)
coupL = cplcFeFvcHpL(i1,gt1,gt2)
coupR = cplcFeFvcHpR(i1,gt1,gt2)
Call FermionToFermionScalar(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fv, conj[VWp]
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = 0._dp
m2out = MVWp
coupL = cplcFeFvcVWpL(i1,gt1)
coupR = cplcFeFvcVWpR(i1,gt1)
Call FermionToFermionVectorBoson(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fe, A0
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFe(gt1)
m2out = MA0
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fe, H0
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFe(gt1)
m2out = MH0
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fe, VP
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFe(gt1)
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 
If ((Present(BR)).And.(gT(i1).Eq.0)) Then 
  BR(i1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(i1,:) = gPartial(i1,:)/gT(i1) 
End if 
 
End Do 
 
Iname = Iname - 1 
 
End Subroutine FeTwoBodyDecay
 
 
Subroutine FdTwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3,2),& 
& cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3)

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT(:) 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Iname = Iname + 1 
NameOfUnit(Iname) = 'FdTwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 1 
  i_end = 3
  gT = 0._dp 
  gPartial = 0._dp 
Else If ( (i_in.Ge.1).And.(i_in.Le.3) ) Then 
  i_start = i_in 
  i_end = i_in 
  gT(i_in) = 0._dp 
  gPartial(i_in,:) = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,3

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,3

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
Do i1=i_start,i_end 
m_in = MFd(i1) 
If (m_in.Eq.0._dp) Cycle 
Call CouplingsFor_Fd_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFucHpL,cplcFdFucHpR,           & 
& cplcFdFucVWpL,cplcFdFucVWpR,deltaM)

i_count = 1 

 
! ----------------------------------------------
! Fd, hh
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = Mhh
coupL = cplcFdFdhhL(i1,gt1)
coupR = cplcFdFdhhR(i1,gt1)
Call FermionToFermionScalar(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fd, VZ
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = MVZ
coupL = cplcFdFdVZL(i1,gt1)
coupR = cplcFdFdVZR(i1,gt1)
Call FermionToFermionVectorBoson(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fu, conj[Hp]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=2, 2
m1out = MFu(gt1)
m2out = MHp(gt2)
coupL = cplcFdFucHpL(i1,gt1,gt2)
coupR = cplcFdFucHpR(i1,gt1,gt2)
Call FermionToFermionScalar(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fu, conj[VWp]
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFu(gt1)
m2out = MVWp
coupL = cplcFdFucVWpL(i1,gt1)
coupR = cplcFdFucVWpR(i1,gt1)
Call FermionToFermionVectorBoson(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fd, A0
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = MA0
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fd, H0
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = MH0
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fd, VG
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! Fd, VP
! ----------------------------------------------

 
Do gt1= 1, 3
m1out = MFd(gt1)
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 
If ((Present(BR)).And.(gT(i1).Eq.0)) Then 
  BR(i1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(i1,:) = gPartial(i1,:)/gT(i1) 
End if 
 
End Do 
 
Iname = Iname - 1 
 
End Subroutine FdTwoBodyDecay
 
 
Subroutine hhTwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplHiggsPP,cplHiggsGG,cplHiggsZZvirt,cplHiggsWWvirt,cplA0A0hh,cplA0H0hh,              & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFuFuhhL(3,3),  & 
& cplcFuFuhhR(3,3),cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhcVWpVWp,cplhhVZVZ

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Real(dp) :: alpha3 
Iname = Iname + 1 
NameOfUnit(Iname) = 'hhTwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 1 
  i_end = 1 
  gT = 0._dp 
  gPartial = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,1

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,1

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
i1=1 
m_in = Mhh 
Call CouplingsFor_hh_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplHiggsPP,cplHiggsGG,cplHiggsZZvirt,cplHiggsWWvirt,cplA0A0hh,cplA0H0hh,             & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplH0H0hh,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,deltaM)

!alpha3 = AlphaSDR(m_in,MFd,MFu) 
alpha3 = g3running**2/(4._dp*Pi) 
i_count = 1 

 
! ----------------------------------------------
! VP, VP
! ----------------------------------------------

 
m1out = 0._dp
m2out = 0._dp
gam = G_F * m_in**3 * oosqrt2 * oo128pi3 * Abs(cplHiggsPP)**2 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VG, VG
! ----------------------------------------------

 
m1out = 0._dp
m2out = 0._dp
gam = G_F * m_in**3 * oosqrt2 * oo36pi3 * Abs(cplHiggsGG)**2 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VZ
! ----------------------------------------------

 
m1out = MVZ
m2out = MVZ
If (m_in.le.2._dp*m1out) Then 
coupReal = cplHiggsZZvirt
Call ScalarToVectorBosonsVR(m_in,m1out,coupReal,gam) 
Else 
gam = 0._dp 
End if 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VWp, VWp
! ----------------------------------------------

 
m1out = MVWp
m2out = MVWp
If (m_in.le.2._dp*m1out) Then 
coupReal = cplHiggsWWvirt
Call ScalarToVectorBosonsVR(m_in,m1out,coupReal,gam) 
Else 
gam = 0._dp 
End if 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, A0
! ----------------------------------------------

 
m1out = MA0
m2out = MA0
coup = cplA0A0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1._dp/2._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, A0
! ----------------------------------------------

 
m1out = MH0
m2out = MA0
coup = cplA0H0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! bar[Fd], Fd
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFd(gt1)
m2out = MFd(gt2)
coupL = cplcFdFdhhL(gt1,gt2)
coupR = cplcFdFdhhR(gt1,gt2)
Call ScalarToTwoFermions(m_in,m1out,m2out,coupL,coupR,gam) 
gam = gam * FFqcd(m1out,m_in,alpha3) 
gPartial(1,i_count) = 3*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! bar[Fe], Fe
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFe(gt1)
m2out = MFe(gt2)
coupL = cplcFeFehhL(gt1,gt2)
coupR = cplcFeFehhR(gt1,gt2)
Call ScalarToTwoFermions(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! bar[Fu], Fu
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFu(gt1)
m2out = MFu(gt2)
coupL = cplcFuFuhhL(gt1,gt2)
coupR = cplcFuFuhhR(gt1,gt2)
Call ScalarToTwoFermions(m_in,m1out,m2out,coupL,coupR,gam) 
gam = gam * FFqcd(m1out,m_in,alpha3) 
gPartial(1,i_count) = 3*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! H0, H0
! ----------------------------------------------

 
m1out = MH0
m2out = MH0
coup = cplH0H0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1._dp/2._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, hh
! ----------------------------------------------

 
m1out = Mhh
m2out = Mhh
coup = cplhhhhhh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1._dp/2._dp*gam 
gT = gT + gPartial(1,i_count) 
  BRHHH(1,1) = gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! conj[Hp], Hp
! ----------------------------------------------

 
Do gt1= 2, 2
  Do gt2=2, 2
m1out = MHp(gt1)
m2out = MHp(gt2)
coup = cplhhHpcHp(gt2,gt1)
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Hp, conj[VWp]
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = MVWp
coup = cplhhHpcVWp(gt1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 2*gam 
gT = gT + gPartial(1,i_count) 
  BRHHpW(i1,gt2) = gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! VWp, conj[VWp]
! ----------------------------------------------

 
m1out = MVWp
m2out = MVWp
coup = cplhhcVWpVWp
Call ScalarToTwoVectorBosons(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VZ
! ----------------------------------------------

 
m1out = MVZ
m2out = MVZ
coup = cplhhVZVZ
Call ScalarToTwoVectorBosons(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1._dp/2._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, hh
! ----------------------------------------------

 
m1out = MA0
m2out = Mhh
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, VP
! ----------------------------------------------

 
m1out = MA0
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, VZ
! ----------------------------------------------

 
m1out = MA0
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! Fv, bar[Fv]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! H0, hh
! ----------------------------------------------

 
m1out = MH0
m2out = Mhh
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, VP
! ----------------------------------------------

 
m1out = MH0
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, VZ
! ----------------------------------------------

 
m1out = MH0
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, VP
! ----------------------------------------------

 
m1out = Mhh
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, VZ
! ----------------------------------------------

 
m1out = Mhh
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
  BRHHZ(i1,gt1) = gPartial(i1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VG, VG
! ----------------------------------------------

 
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VP, VP
! ----------------------------------------------

 
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VP
! ----------------------------------------------

 
m1out = MVZ
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
If ((Present(BR)).And.(gT.Eq.0)) Then 
  BR(1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(1,:) = gPartial(1,:)/gT 
End if 
 
Iname = Iname - 1 
 
Contains 
 
  Real(dp) Function FFqcd(mf, mA, alpha_s)
  Implicit None
   Real(dp) , Intent(in) :: mf, mA, alpha_s
   Real(dp) :: fac, beta, beta2, ratio, R_beta_1, Ln_R_beta_1, Ln_beta

   FFqcd = 0._dp
   ratio = mf / mA
   If (ratio.Ge.0.5_dp) Return ! decay is kinematically forbitten

   If (ratio.Ge.0.495_dp) Return ! Coloumb singularity

    beta2 = 1._dp - 4._dp * ratio**2
    beta = Sqrt(beta2)
    
    R_beta_1 = (1. - beta) / (1._dp + beta)
    Ln_beta = Log(beta)
    Ln_R_beta_1 = Log(R_beta_1)

    fac = (3._dp + 34._dp * beta2 - 13._dp * beta**4) / (16._dp * beta**3)  &
      &     * (-Ln_R_beta_1)                                                &
      & + 0.375_dp * (7._dp - beta2) - 3._dp * Log(4._dp/(1._dp - beta**2)) &
      & - 4._dp * Ln_beta                                                   &
      & + (1._dp + beta**2)                                                 &
      &       * ( 4._dp * Li2(R_beta_1) + 2._dp * Li2(- R_beta_1)           &
      &         + Ln_R_beta_1 * ( 3._dp * Log(2._dp/(1._dp + beta))         &
      &                         + 2._dp * Ln_beta )  ) / beta

    fac = fac - 3._dp * Log(ratio)  ! absorb large logarithms in mass

    FFqcd = 1._dp + 5._dp * alpha_s * fac * oo3pi 

  End  Function FFqcd
End Subroutine hhTwoBodyDecay
 
 
Subroutine H0TwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplA0H0hh,cplA0H0VZ,cplH0H0hh,cplH0HpcHp(2,2),cplH0HpcVWp(2)

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Iname = Iname + 1 
NameOfUnit(Iname) = 'H0TwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 1 
  i_end = 1 
  gT = 0._dp 
  gPartial = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,1

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,1

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
i1=1 
m_in = MH0 
Call CouplingsFor_H0_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplA0H0hh,cplA0H0VZ,cplH0H0hh,cplH0HpcHp,cplH0HpcVWp,deltaM)

i_count = 1 

 
! ----------------------------------------------
! hh, A0
! ----------------------------------------------

 
m1out = Mhh
m2out = MA0
coup = cplA0H0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, VZ
! ----------------------------------------------

 
m1out = MA0
m2out = MVZ
coup = cplA0H0VZ
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, H0
! ----------------------------------------------

 
m1out = Mhh
m2out = MH0
coup = cplH0H0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! conj[Hp], Hp
! ----------------------------------------------

 
Do gt1= 2, 2
  Do gt2=2, 2
m1out = MHp(gt1)
m2out = MHp(gt2)
coup = cplH0HpcHp(gt2,gt1)
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Hp, conj[VWp]
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = MVWp
coup = cplH0HpcVWp(gt1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 2*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! A0, A0
! ----------------------------------------------

 
m1out = MA0
m2out = MA0
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, H0
! ----------------------------------------------

 
m1out = MA0
m2out = MH0
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, VP
! ----------------------------------------------

 
m1out = MA0
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! Fd, bar[Fd]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFd(gt1)
m2out = MFd(gt2)
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fe, bar[Fe]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFe(gt1)
m2out = MFe(gt2)
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fu, bar[Fu]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFu(gt1)
m2out = MFu(gt2)
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fv, bar[Fv]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! H0, H0
! ----------------------------------------------

 
m1out = MH0
m2out = MH0
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, VP
! ----------------------------------------------

 
m1out = MH0
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, VZ
! ----------------------------------------------

 
m1out = MH0
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, hh
! ----------------------------------------------

 
m1out = Mhh
m2out = Mhh
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, VP
! ----------------------------------------------

 
m1out = Mhh
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, VZ
! ----------------------------------------------

 
m1out = Mhh
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VP, VP
! ----------------------------------------------

 
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VP
! ----------------------------------------------

 
m1out = MVZ
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! conj[VWp], VWp
! ----------------------------------------------

 
m1out = MVWp
m2out = MVWp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VZ
! ----------------------------------------------

 
m1out = MVZ
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
If ((Present(BR)).And.(gT.Eq.0)) Then 
  BR(1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(1,:) = gPartial(1,:)/gT 
End if 
 
Iname = Iname - 1 
 
End Subroutine H0TwoBodyDecay
 
 
Subroutine A0TwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplA0A0hh,cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2)

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Iname = Iname + 1 
NameOfUnit(Iname) = 'A0TwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 1 
  i_end = 1 
  gT = 0._dp 
  gPartial = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,1

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,1

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
i1=1 
m_in = MA0 
Call CouplingsFor_A0_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplA0A0hh,cplA0H0hh,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,deltaM)

i_count = 1 

 
! ----------------------------------------------
! hh, A0
! ----------------------------------------------

 
m1out = Mhh
m2out = MA0
coup = cplA0A0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, H0
! ----------------------------------------------

 
m1out = Mhh
m2out = MH0
coup = cplA0H0hh
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, VZ
! ----------------------------------------------

 
m1out = MH0
m2out = MVZ
coup = cplA0H0VZ
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! conj[Hp], Hp
! ----------------------------------------------

 
Do gt1= 2, 2
  Do gt2=2, 2
m1out = MHp(gt1)
m2out = MHp(gt2)
coup = cplA0HpcHp(gt2,gt1)
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 1*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Hp, conj[VWp]
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = MVWp
coup = cplA0HpcVWp(gt1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(1,i_count) = 2*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! A0, A0
! ----------------------------------------------

 
m1out = MA0
m2out = MA0
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, H0
! ----------------------------------------------

 
m1out = MA0
m2out = MH0
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, VP
! ----------------------------------------------

 
m1out = MA0
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! A0, VZ
! ----------------------------------------------

 
m1out = MA0
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! Fd, bar[Fd]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFd(gt1)
m2out = MFd(gt2)
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fe, bar[Fe]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFe(gt1)
m2out = MFe(gt2)
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fu, bar[Fu]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFu(gt1)
m2out = MFu(gt2)
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Fv, bar[Fv]
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! H0, H0
! ----------------------------------------------

 
m1out = MH0
m2out = MH0
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! H0, VP
! ----------------------------------------------

 
m1out = MH0
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, hh
! ----------------------------------------------

 
m1out = Mhh
m2out = Mhh
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, VP
! ----------------------------------------------

 
m1out = Mhh
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! hh, VZ
! ----------------------------------------------

 
m1out = Mhh
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VP, VP
! ----------------------------------------------

 
m1out = 0._dp
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VP
! ----------------------------------------------

 
m1out = MVZ
m2out = 0._dp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! conj[VWp], VWp
! ----------------------------------------------

 
m1out = MVWp
m2out = MVWp
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! VZ, VZ
! ----------------------------------------------

 
m1out = MVZ
m2out = MVZ
gam = 0._dp 
gPartial(1,i_count) = 0._dp*gam 
gT = gT + gPartial(1,i_count) 
i_count = i_count +1 
If ((Present(BR)).And.(gT.Eq.0)) Then 
  BR(1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(1,:) = gPartial(1,:)/gT 
End if 
 
Iname = Iname - 1 
 
End Subroutine A0TwoBodyDecay
 
 
Subroutine HpTwoBodyDecay(i_in,deltaM,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,gPartial,gT,BR)

Implicit None 
 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2,v,MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),              & 
& ZZ(2,2),betaH

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZEL(3,3),          & 
& ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplA0HpcHp(2,2),cplA0cHpVWp(2),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),               & 
& cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplH0HpcHp(2,2),cplH0cHpVWp(2),cplhhHpcHp(2,2),& 
& cplhhcHpVWp(2),cplHpcHpVZ(2,2),cplcHpVWpVZ(2)

Integer, Intent(in) :: i_in 
Real(dp), Intent(inout) :: gPartial(:,:), gT(:) 
Real(dp), Intent(in) :: deltaM 
Real(dp), Optional, Intent(inout) :: BR(:,:) 
Integer :: i1, i2, i3, i4, i_start, i_end, i_count, gt1, gt2, gt3, gt4 
Real(dp) :: gam, m_in, m1out, m2out, coupReal 
Complex(dp) :: coupC, coupR, coupL, coup 
 
Iname = Iname + 1 
NameOfUnit(Iname) = 'HpTwoBodyDecay'
 
If (i_in.Lt.0) Then 
  i_start = 2 
  i_end = 2
  gT = 0._dp 
  gPartial = 0._dp 
Else If ( (i_in.Ge.1).And.(i_in.Le.2) ) Then 
  i_start = i_in 
  i_end = i_in 
  gT(i_in) = 0._dp 
  gPartial(i_in,:) = 0._dp 
Else 
  If (ErrorLevel.Ge.-1) Then 
     Write(ErrCan,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(ErrCan,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,2

     Write(*,*) 'Problem in subroutine '//NameOfUnit(Iname) 
     Write(*,*) 'Value of i_in out of range, (i_in,i_max) = ', i_in,2

  End If 
  If (ErrorLevel.Gt.0) Call TerminateProgram 
  If (Present(BR)) BR = 0._dp 
  Iname = Iname -1 
  Return 
End If 
 
Do i1=i_start,i_end 
m_in = MHp(i1) 
If (m_in.Eq.0._dp) Cycle 
Call CouplingsFor_Hp_decays_2B(m_in,i1,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,            & 
& ZP,ZUL,ZUR,ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,           & 
& v,cplA0HpcHp,cplA0cHpVWp,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,          & 
& cplH0HpcHp,cplH0cHpVWp,cplhhHpcHp,cplhhcHpVWp,cplHpcHpVZ,cplcHpVWpVZ,deltaM)

i_count = 1 

 
! ----------------------------------------------
! Hp, A0
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = MA0
coup = cplA0HpcHp(gt1,i1)
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! A0, VWp
! ----------------------------------------------

 
m1out = MA0
m2out = MVWp
coup = cplA0cHpVWp(i1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! bar[Fd], Fu
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFd(gt1)
m2out = MFu(gt2)
coupL = cplcFdFucHpL(gt1,gt2,i1)
coupR = cplcFdFucHpR(gt1,gt2,i1)
Call ScalarToTwoFermions(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 3*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
If ((gt1.eq.3).and.(gt2.eq.2)) Then 
  BR_Hcb(i1) = gPartial(i1,i_count) 
End if 
If ((gt1.eq.2).and.(gt2.eq.2)) Then 
  BR_Hcs(i1) = gPartial(i1,i_count) 
End if 
If ((gt1.eq.3).and.(gt2.eq.3)) Then 
  BR_HpTB(i1) = gPartial(i1,i_count) 
End if 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! bar[Fe], Fv
! ----------------------------------------------

 
Do gt1= 1, 3
  Do gt2=1, 3
m1out = MFe(gt1)
m2out = 0._dp
coupL = cplcFeFvcHpL(gt1,gt2,i1)
coupR = cplcFeFvcHpR(gt1,gt2,i1)
Call ScalarToTwoFermions(m_in,m1out,m2out,coupL,coupR,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 
End Do 
 

 
! ----------------------------------------------
! Hp, H0
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = MH0
coup = cplH0HpcHp(gt1,i1)
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! H0, VWp
! ----------------------------------------------

 
m1out = MH0
m2out = MVWp
coup = cplH0cHpVWp(i1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! Hp, hh
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = Mhh
coup = cplhhHpcHp(gt1,i1)
Call ScalarToTwoScalars(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! hh, VWp
! ----------------------------------------------

 
m1out = Mhh
m2out = MVWp
coup = cplhhcHpVWp(i1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
  BR_HpHW(i1,gt1) = gPartial(i1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! Hp, VZ
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = MVZ
coup = cplHpcHpVZ(gt1,i1)
Call ScalarToScalarVectorBoson(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! VWp, VZ
! ----------------------------------------------

 
m1out = MVWp
m2out = MVZ
coup = cplcHpVWpVZ(i1)
Call ScalarToTwoVectorBosons(m_in,m1out,m2out,coup,gam) 
gPartial(i1,i_count) = 1*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
  BR_HpWZ(i1) = gPartial(i1,i_count) 
i_count = i_count +1 

 
! ----------------------------------------------
! Hp, VP
! ----------------------------------------------

 
Do gt1= 2, 2
m1out = MHp(gt1)
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
  End Do 

 
! ----------------------------------------------
! VWp, VP
! ----------------------------------------------

 
m1out = MVWp
m2out = 0._dp
gam = 0._dp 
gPartial(i1,i_count) = 0._dp*gam 
gT(i1) = gT(i1) + gPartial(i1,i_count) 
i_count = i_count +1 
If ((Present(BR)).And.(gT(i1).Eq.0)) Then 
  BR(i1,:) = 0._dp 
Else If (Present(BR)) Then 
  BR(i1,:) = gPartial(i1,:)/gT(i1) 
End if 
 
End Do 
 
Iname = Iname - 1 
 
End Subroutine HpTwoBodyDecay
 
 
Subroutine ScalarToTwoVectorbosonsNew(mS,mV1,mV2,coup,width)
  implicit none
   real(dp), intent(in) :: mS,mV1,mV2
   real(dp), intent(out) :: width
   complex(dp), intent(in) :: coup

   real(dp) :: mSsq,mV1sq, mV2sq,kappa

   if ( abs(mS).le.( abs(mV1)+abs(mV2) ) ) then
    width = 0._dp

   elseif (mV1.eq.0._dp) then
    write(ErrCan,*) 'Server warning, in subroutine ScalarToTwoVectorbosons'
    write(ErrCan,*) 'm_V1 = 0, setting width to 0'
    width = 0._dp

   elseif (mV2.eq.0._dp) then
    write(ErrCan,*) 'Server warning, in subroutine ScalarToTwoVectorbosons'
    write(ErrCan,*) 'm_V2 = 0, setting width to 0'
    width = 0._dp


   elseif (Abs(coup).eq.0._dp) then
    width = 0._dp

   else
    mSsq = mS * mS
    mV1sq = mV1**2
    mV2sq = mV2**2
    kappa = Sqrt( (mSsq-mV1sq-mV2sq)**2 - 4._dp * mV1sq*mV2sq )/(mS**3)
    width = coup**2/(4._dp*mV1sq*mV2sq)*(mV1sq**2 + 10._dp*mV1sq*mV2sq - &
             & 2._dp*(mV1sq+mV2sq)*mSsq + mV2sq**2 +mSsq**2)
    width = oo16Pi*width*kappa

   endif

  End Subroutine ScalarToTwoVectorbosonsNew

Subroutine FermionToFermionVectorBosonMassless(mFin,mFout,mV,coupL,coupR,width)
  implicit none
   real(dp), intent(in) :: mFin,mFout,mV
   real(dp), intent(out) :: width
   complex(dp), intent(in) :: coupL, coupR


   if ( abs(mFin).le.( abs(mFout)+abs(mV) ) ) then
    width = 0._dp

   else

    width = 0.5_dp*oo16Pi*(Abs(coupL)**2 + Abs(coupR)**2)*mFin**3


   endif

  End Subroutine FermionToFermionVectorBosonMassless

End Module TreeLevelDecays_Inert2 
 
