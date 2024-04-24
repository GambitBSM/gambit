! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:23 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Fu3Decays_gumTHDMII 
 
Use Control 
Use Settings 
Use CouplingsForDecays_gumTHDMII 
Use ThreeBodyPhaseSpace 
 
Contains 
 
Subroutine FuThreeBodyDecay(n_in,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,               & 
& ZW,ZZ,alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,               & 
& m222,vd,vu,gTAh,gThh,gTHm,gTVWm,gTVZ,gFuFucFdFd,gFuFucFeFe,gFuFucFuFu,gFuFdcFeFv,      & 
& gFuFucFvFv,epsI,deltaM,CheckRealStates,gT,gPartial,BR)

Implicit None 
 
Real(dp),Intent(in) :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),               & 
& alphaH,betaH

Complex(dp),Intent(in) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Complex(dp) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),          & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),               & 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),             & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),               & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),             & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3)

Real(dp),Intent(in) :: g1,g2,g3,vd,vu

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Real(dp),Intent(inout) :: gFuFucFdFd(3,3,3,3),gFuFucFeFe(3,3,3,3),gFuFucFuFu(3,3,3,3),gFuFdcFeFv(3,3,3,3),      & 
& gFuFucFvFv(3,3,3,3)

Real(dp),Intent(in) :: gTAh(2),gThh(2),gTHm(2),gTVWm,gTVZ

Real(dp) :: gFuFucFdFdi(3,3,3),gFuFucFeFei(3,3,3),gFuFucFuFui(3,3,3),gFuFdcFeFvi(3,3,3),          & 
& gFuFucFvFvi(3,3,3)

Real(dp) :: gTAhtemp(2),gThhtemp(2),gTHmtemp(2),gTVWmtemp,gTVZtemp
Integer :: NVs,NVst,NSs,NVVst,NVVss,NVSss,NVSst,NSSss,NSSst
Complex(dp), Allocatable :: IntegralVVst(:,:),IntegralVSss(:,:),IntegralVSst(:,:),IntegralSSss(:,:)               & 
& ,IntegralSSst(:,:)
Real(dp), Allocatable :: IntegralVs(:,:),IntegralVst(:,:),IntegralSs(:,:),IntegralVVss(:,:)
Real(dp), Intent(inout), Optional :: BR(:,:), gPartial(:,:) 
Real(dp), Intent(inout) :: gT(:) 
Integer, Intent(in) :: n_in 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Intent(in) ::  CheckRealStates 
Integer :: i_start, i_end, i_run, n_out, n_length, gt1, gt2, gt3, i1 
Logical :: check 
Iname = Iname +1 
NameOfUnit(Iname) = 'FuThreeBodyDecay' 
 
Allocate( IntegralVs(25000,9) ) 
Allocate( IntegralVst(25000,12) ) 
Allocate( IntegralSs(500000,10) ) 
Allocate( IntegralVVst(25000,12) ) 
Allocate( IntegralVVss(500000,12) ) 
Allocate( IntegralVSss(500000,12) ) 
Allocate( IntegralVSst(500000,16) ) 
Allocate( IntegralSSss(500000,12) ) 
Allocate( IntegralSSst(500000,16) ) 

 
If (CheckRealStates) Then 
gTAhtemp = 0._dp 
gThhtemp = 0._dp 
gTHmtemp = 0._dp 
gTVWmtemp = 0._dp 
gTVZtemp = 0._dp 
Else 
gTAhtemp = gTAh 
gThhtemp = gThh 
gTHmtemp = gTHm 
gTVWmtemp = gTVWm 
gTVZtemp = gTVZ 
End If 
 
check=CheckRealStates 

 
If (n_in.Lt.0) Then 
 i_start = 1 
 i_end = 3 
 Else If ( (n_in.Ge.1).And.(n_in.Le. 3) ) Then 
 i_start = n_in 
 i_end = n_in 
Else 
 If (ErrorLevel.Ge.-1) Then 
   Write (ErrCan, *) 'Problem in subroutine'//NameOfUnit(Iname) 
   Write (ErrCan, *) 'Value of n_in out of range, (n_in,3) = ',n_in,3 
 End If 
 
 If (ErrorLevel.Gt.0) Call TerminateProgram 
 
 If (Present(BR)) BR = 0._dp 
 Iname = Iname - 1 
 Return 
End If 
 
Do i_run = i_start, i_end 
 
Call CouplingsFor_Fu_decays_3B(MFu(i_run),i_run,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,               & 
& ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,               & 
& Ye,m122,m112,m222,vd,vu,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,deltaM)

IntegralVs = 0._dp 
NVs = 0  
IntegralVst = 0._dp 
NVst = 0  
IntegralSs = 0._dp 
NSs = 0  
IntegralVVst = 0._dp 
NVVst = 0  
IntegralVVss = 0._dp 
NVVss = 0  
IntegralVSss = 0._dp 
NVSss = 0  
IntegralVSst = 0._dp 
NVSst = 0  
IntegralSSss = 0._dp 
NSSss = 0  
IntegralSSst = 0._dp 
NSSst = 0  

 
gFuFucFdFdi = 0._dp 
Call FuToFucFdFd(i_run,MFu,MFd,MVZ,MVWm,MHm,MAh,Mhh,cplcFdFdAhL,cplcFdFdAhR,          & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& IntegralSs,IntegralSSss,IntegralSSst,IntegralVs,IntegralVSss,IntegralVSst,             & 
& IntegralVVss,IntegralVVst,NSs,NSSss,NSSst,NVs,NVSss,NVSst,NVVss,NVVst,gTVZtemp,        & 
& gTVWmtemp,gTHmtemp,gTAhtemp,gThhtemp,deltaM,epsI,check,gFuFucFdFdi)

gFuFucFdFd(i_run,:,:,:) = gFuFucFdFdi 
gT(i_run) = gT(i_run) + Sum(gFuFucFdFdi) 
 
gFuFucFeFei = 0._dp 
Call FuToFucFeFe(i_run,MFu,MFe,MVZ,MAh,Mhh,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,               & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,IntegralSs,IntegralSSss,IntegralVs,IntegralVSss,   & 
& IntegralVVss,NSs,NSSss,NVs,NVSss,NVVss,gTVZtemp,gTAhtemp,gThhtemp,deltaM,              & 
& epsI,check,gFuFucFeFei)

gFuFucFeFe(i_run,:,:,:) = gFuFucFeFei 
gT(i_run) = gT(i_run) + Sum(gFuFucFeFei) 
 
gFuFucFuFui = 0._dp 
Call FuToFucFuFu(i_run,MFu,MVZ,MAh,Mhh,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,           & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,IntegralSs,IntegralSSss,IntegralSSst,              & 
& IntegralVs,IntegralVSss,IntegralVSst,IntegralVVss,IntegralVVst,NSs,NSSss,              & 
& NSSst,NVs,NVSss,NVSst,NVVss,NVVst,gTVZtemp,gTAhtemp,gThhtemp,deltaM,epsI,              & 
& check,gFuFucFuFui)

gFuFucFuFu(i_run,:,:,:) = gFuFucFuFui 
gT(i_run) = gT(i_run) + Sum(gFuFucFuFui) 
 
gFuFdcFeFvi = 0._dp 
Call FuToFdcFeFv(i_run,MFd,MFe,MVWm,MHm,MFu,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,     & 
& cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,IntegralSs,         & 
& IntegralSSss,IntegralVs,IntegralVSss,IntegralVVss,NSs,NSSss,NVs,NVSss,NVVss,           & 
& gTVWmtemp,gTHmtemp,deltaM,epsI,check,gFuFdcFeFvi)

gFuFdcFeFv(i_run,:,:,:) = gFuFdcFeFvi 
gT(i_run) = gT(i_run) + Sum(gFuFdcFeFvi) 
 
gFuFucFvFvi = 0._dp 
Call FuToFucFvFv(i_run,MFu,MVZ,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,       & 
& IntegralVs,IntegralVVss,NVs,NVVss,gTVZtemp,deltaM,epsI,check,gFuFucFvFvi)

gFuFucFvFv(i_run,:,:,:) = gFuFucFvFvi 
gT(i_run) = gT(i_run) + Sum(gFuFucFvFvi) 
 
End Do 
 

If (Present(gPartial)) Then
Do i1 = i_start, i_end 
 
n_length=1
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gFuFucFdFd(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gFuFucFeFe(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=gt1,3
gPartial(i1,n_length)= gFuFucFuFu(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gFuFdcFeFv(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,3
gPartial(i1,n_length)= gFuFucFvFv(i1,gt1,gt2,gt3)
n_length=n_length+1
     End Do 
  End Do 
End Do 
If (Present(BR).And.(gT(i1).Gt.0._dp)) Then 
BR(i1,:)=gPartial(i1,:)/gT(i1)
Else If (Present(BR)) Then
BR(i1,:)=0._dp
End If
 
End Do 
End if 
Deallocate( IntegralVs ) 
Deallocate( IntegralVst ) 
Deallocate( IntegralSs ) 
Deallocate( IntegralVVst ) 
Deallocate( IntegralVVss ) 
Deallocate( IntegralVSss ) 
Deallocate( IntegralVSst ) 
Deallocate( IntegralSSss ) 
Deallocate( IntegralSSst ) 
Iname = Iname - 1 
 
End Subroutine FuThreeBodyDecay
 
 
Subroutine FuToFucFdFd(iIN,MFu,MFd,MVZ,MVWm,MHm,MAh,Mhh,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& IntegralSs,IntegralSSss,IntegralSSst,IntegralVs,IntegralVSss,IntegralVSst,             & 
& IntegralVVss,IntegralVVst,NSs,NSSss,NSSst,NVs,NVSss,NVSst,NVVss,NVVst,gTVZ,            & 
& gTVWm,gTHm,gTAh,gThh,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MFd(3),MVZ,MVWm,MHm(2),MAh(2),Mhh(2)

Complex(dp),Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),          & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),               & 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),           & 
& cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Real(dp),Intent(inout) :: IntegralSs(500000,10),IntegralVs(25000,9),IntegralVVss(500000,12)

Complex(dp),Intent(inout) :: IntegralSSss(500000,12),IntegralSSst(500000,16),IntegralVSss(500000,12),              & 
& IntegralVSst(500000,16),IntegralVVst(25000,12)

Real(dp),Intent(inout) :: gTVZ,gTVWm,gTHm(2),gTAh(2),gThh(2)

Integer, Intent(inout) :: NSs,NSSss,NSSst,NVs,NVSss,NVSst,NVVss,NVVst
Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp) :: Boson2(2), mass(4),  Boson4(4) 
Complex(dp) :: coup(4), coup2(8),coupT 
mass(1) = MFu(iIN) 
 
Isum = 64 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
If(Abs(MFu(iIN)).gt.(Abs(MFd(gt3))+Abs(MFd(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
Boson2(1) = MVZ 
Boson2(2) =gTVZ 
 
Boson4(1) = MVZ 
Boson4(2) =gTVZ 
Boson4(3) = MVZ 
Boson4(4) =gTVZ 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup(2) = Conjg(cplcFuFuVZL(iIN,gt1)) 
coup(1) = Conjg(cplcFuFuVZR(iIN,gt1)) 
coup(4) = Conjg(cplcFdFdVZL(gt2,gt3)) 
coup(3) = Conjg(cplcFdFdVZR(gt2,gt3))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
resR= 3*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  conj[VWm] 
!-------------- 
Isum = Isum + 1 
Boson2(1) = MVWm 
Boson2(2) =gTVWm 
 
Boson4(1) = MVWm 
Boson4(2) =gTVWm 
Boson4(3) = MVWm 
Boson4(4) =gTVWm 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFd(gt3) 
mass(3) = -MFd(gt2) 
mass(4) = MFu(gt1) 
 
coup(2) = Conjg(cplcFuFdcVWmL(iIN,gt3)) 
coup(1) = Conjg(cplcFuFdcVWmR(iIN,gt3)) 
coup(4) = Conjg(cplcFdFuVWmL(gt2,gt1)) 
coup(3) = Conjg(cplcFdFuVWmR(gt2,gt1))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
resR= 3*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[VWm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm]'



!-------------- 
!  conj[Hm] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = MHm(i1) 
Boson2(2) =gTHm(i1) 
 
Boson4(1) = MHm(i1) 
Boson4(2) =gTHm(i1) 
Boson4(3) = MHm(i1) 
Boson4(4) =gTHm(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFd(gt3) 
mass(3) = -MFd(gt2) 
mass(4) = MFu(gt1) 
 
coup(2) = Conjg(cplcFuFdcHmL(iIN,gt3,i1)) 
coup(1) = Conjg(cplcFuFdcHmR(iIN,gt3,i1)) 
coup(4) = Conjg(cplcFdFuHmL(gt2,gt1,i1)) 
coup(3) = Conjg(cplcFdFuHmR(gt2,gt1,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
resR= 3*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hm]'
      End Do 



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = MAh(i1) 
Boson2(2) =gTAh(i1) 
 
Boson4(1) = MAh(i1) 
Boson4(2) =gTAh(i1) 
Boson4(3) = MAh(i1) 
Boson4(4) =gTAh(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup(2) = Conjg(cplcFuFuAhL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFuAhR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFdFdAhL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFdFdAhR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
resR= 3*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = Mhh(i1) 
Boson2(2) =gThh(i1) 
 
Boson4(1) = Mhh(i1) 
Boson4(2) =gThh(i1) 
Boson4(3) = Mhh(i1) 
Boson4(4) =gThh(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup(2) = Conjg(cplcFuFuhhL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFuhhR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFdFdhhL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFdFdhhR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
resR= 3*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  VZ, conj[VWm] 
!-------------- 
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = MVWm 
Boson4(4) = gTVWm 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFd(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFd(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = cplcFuFdcVWmL(iIN,gt3) 
coup2(3) = cplcFuFdcVWmR(iIN,gt3)  
coup2(5) = cplcFdFdVZL(gt2,gt3) 
coup2(6) = cplcFdFdVZR(gt2,gt3) 
coup2(8) = cplcFdFuVWmL(gt2,gt1) 
coup2(7) = cplcFdFuVWmR(gt2,gt1) 
Call IntegrateGaugeST(Boson4, mass, coup2, deltaM, epsI,IntegralVVst,NVVst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: VZ,conj[VWm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,conj[VWm]'



!-------------- 
!  VZ, conj[Hm] 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = MHm(i2) 
Boson4(4) = gTHm(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFd(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFd(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = cplcFuFdcHmL(iIN,gt3,i2) 
coup2(3) = cplcFuFdcHmR(iIN,gt3,i2)  
coup2(5) = cplcFdFdVZL(gt2,gt3) 
coup2(6) = cplcFdFdVZR(gt2,gt3) 
coup2(8) = cplcFdFuHmL(gt2,gt1,i2) 
coup2(7) = cplcFdFuHmR(gt2,gt1,i2) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: VZ,conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,conj[Hm]'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFdFdVZL(gt2,gt3) 
coup2(6) = cplcFdFdVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFdFdAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdAhR(gt3,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFdFdVZL(gt2,gt3) 
coup2(6) = cplcFdFdVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdhhR(gt3,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  conj[VWm], conj[Hm] 
!-------------- 
  Do i2=1,2
Boson4(1) = MVWm 
Boson4(2) = gTVWm 
Boson4(3) = MHm(i2) 
Boson4(4) = gTHm(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFd(gt3) 
mass(3) = -MFd(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFdcVWmL(iIN,gt3) 
coup2(2) = cplcFuFdcVWmR(iIN,gt3) 
coup2(4) = cplcFuFdcHmL(iIN,gt3,i2) 
coup2(3) = cplcFuFdcHmR(iIN,gt3,i2)  
coup2(5) = cplcFdFuVWmL(gt2,gt1) 
coup2(6) = cplcFdFuVWmR(gt2,gt1) 
coup2(8) = cplcFdFuHmL(gt2,gt1,i2) 
coup2(7) = cplcFdFuHmR(gt2,gt1,i2) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[VWm],conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],conj[Hm]'
      End Do 



!-------------- 
!  conj[VWm], Ah 
!-------------- 
  Do i2=1,2
Boson4(1) = MVWm 
Boson4(2) = gTVWm 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(4) = MFd(gt3) 
mass(3) = -MFd(gt2) 
 
coup2(1) = cplcFuFdcVWmL(iIN,gt3) 
coup2(2) = cplcFuFdcVWmR(iIN,gt3) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFdFuVWmL(gt2,gt1) 
coup2(6) = cplcFdFuVWmR(gt2,gt1) 
coup2(8) = Conjg(cplcFdFdAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdAhR(gt3,gt2,i2)) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[VWm],Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],Ah'
      End Do 



!-------------- 
!  conj[VWm], hh 
!-------------- 
  Do i2=1,2
Boson4(1) = MVWm 
Boson4(2) = gTVWm 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(4) = MFd(gt3) 
mass(3) = -MFd(gt2) 
 
coup2(1) = cplcFuFdcVWmL(iIN,gt3) 
coup2(2) = cplcFuFdcVWmR(iIN,gt3) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFdFuVWmL(gt2,gt1) 
coup2(6) = cplcFdFuVWmR(gt2,gt1) 
coup2(8) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdhhR(gt3,gt2,i2)) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[VWm],hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],hh'
      End Do 



!-------------- 
!  conj[Hm], conj[Hm] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = MHm(i1) 
Boson4(2) = gTHm(i1) 
Boson4(3) = MHm(i2) 
Boson4(4) = gTHm(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFd(gt3) 
mass(3) = -MFd(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFdcHmL(iIN,gt3,i1) 
coup2(2) = cplcFuFdcHmR(iIN,gt3,i1) 
coup2(4) = cplcFuFdcHmL(iIN,gt3,i2) 
coup2(3) = cplcFuFdcHmR(iIN,gt3,i2)  
coup2(5) = cplcFdFuHmL(gt2,gt1,i1) 
coup2(6) = cplcFdFuHmR(gt2,gt1,i1) 
coup2(8) = cplcFdFuHmL(gt2,gt1,i2) 
coup2(7) = cplcFdFuHmR(gt2,gt1,i2) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[Hm],conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hm],conj[Hm]'
        End Do 
      End Do 



!-------------- 
!  conj[Hm], Ah 
!-------------- 
Do i1=1,2
  Do i2=1,2
Boson4(1) = MHm(i1) 
Boson4(2) = gTHm(i1) 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(4) = MFd(gt3) 
mass(3) = -MFd(gt2) 
 
coup2(1) = cplcFuFdcHmL(iIN,gt3,i1) 
coup2(2) = cplcFuFdcHmR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFdFuHmL(gt2,gt1,i1) 
coup2(6) = cplcFdFuHmR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFdFdAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdAhR(gt3,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[Hm],Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hm],Ah'
        End Do 
      End Do 



!-------------- 
!  conj[Hm], hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Boson4(1) = MHm(i1) 
Boson4(2) = gTHm(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(4) = MFd(gt3) 
mass(3) = -MFd(gt2) 
 
coup2(1) = cplcFuFdcHmL(iIN,gt3,i1) 
coup2(2) = cplcFuFdcHmR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFdFuHmL(gt2,gt1,i1) 
coup2(6) = cplcFdFuHmR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdhhR(gt3,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: conj[Hm],hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hm],hh'
        End Do 
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = MAh(i1) 
Boson4(2) = gTAh(i1) 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFdFdAhL(gt2,gt3,i1) 
coup2(6) = cplcFdFdAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFdFdAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdAhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Boson4(1) = MAh(i1) 
Boson4(2) = gTAh(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFdFdAhL(gt2,gt3,i1) 
coup2(6) = cplcFdFdAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdhhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = Mhh(i1) 
Boson4(2) = gThh(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFd(gt2) 
mass(4) = MFd(gt3) 
 
coup2(1) = cplcFuFuhhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFdFdhhL(gt2,gt3,i1) 
coup2(6) = cplcFdFdhhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFdFdhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFdFdhhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFd Fd Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:64))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
  g = oo512pi3 / Abs(MFu(iIN))**3*g
End Subroutine FuToFucFdFd 
 
 
Subroutine FuToFucFeFe(iIN,MFu,MFe,MVZ,MAh,Mhh,cplcFeFeAhL,cplcFeFeAhR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,IntegralSs,IntegralSSss,               & 
& IntegralVs,IntegralVSss,IntegralVVss,NSs,NSSss,NVs,NVSss,NVVss,gTVZ,gTAh,              & 
& gThh,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MFe(3),MVZ,MAh(2),Mhh(2)

Complex(dp),Intent(in) :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),          & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),               & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Real(dp),Intent(inout) :: IntegralSs(500000,10),IntegralVs(25000,9),IntegralVVss(500000,12)

Complex(dp),Intent(inout) :: IntegralSSss(500000,12),IntegralVSss(500000,12)

Real(dp),Intent(inout) :: gTVZ,gTAh(2),gThh(2)

Integer, Intent(inout) :: NSs,NSSss,NVs,NVSss,NVVss
Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp) :: Boson2(2), mass(4),  Boson4(4) 
Complex(dp) :: coup(4), coup2(8),coupT 
mass(1) = MFu(iIN) 
 
Isum = 25 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
If(Abs(MFu(iIN)).gt.(Abs(MFe(gt3))+Abs(MFe(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
Boson2(1) = MVZ 
Boson2(2) =gTVZ 
 
Boson4(1) = MVZ 
Boson4(2) =gTVZ 
Boson4(3) = MVZ 
Boson4(4) =gTVZ 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup(2) = Conjg(cplcFuFuVZL(iIN,gt1)) 
coup(1) = Conjg(cplcFuFuVZR(iIN,gt1)) 
coup(4) = Conjg(cplcFeFeVZL(gt2,gt3)) 
coup(3) = Conjg(cplcFeFeVZR(gt2,gt3))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
resR= 1*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = MAh(i1) 
Boson2(2) =gTAh(i1) 
 
Boson4(1) = MAh(i1) 
Boson4(2) =gTAh(i1) 
Boson4(3) = MAh(i1) 
Boson4(4) =gTAh(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup(2) = Conjg(cplcFuFuAhL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFuAhR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFeFeAhL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFeFeAhR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
resR= 1*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = Mhh(i1) 
Boson2(2) =gThh(i1) 
 
Boson4(1) = Mhh(i1) 
Boson4(2) =gThh(i1) 
Boson4(3) = Mhh(i1) 
Boson4(4) =gThh(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup(2) = Conjg(cplcFuFuhhL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFuhhR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFeFehhL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFeFehhR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
resR= 1*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFeFeVZL(gt2,gt3) 
coup2(6) = cplcFeFeVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFeFeAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFeFeAhR(gt3,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFeFeVZL(gt2,gt3) 
coup2(6) = cplcFeFeVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFeFehhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFeFehhR(gt3,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = MAh(i1) 
Boson4(2) = gTAh(i1) 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFeFeAhL(gt2,gt3,i1) 
coup2(6) = cplcFeFeAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFeFeAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFeFeAhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Boson4(1) = MAh(i1) 
Boson4(2) = gTAh(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFeFeAhL(gt2,gt3,i1) 
coup2(6) = cplcFeFeAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFeFehhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFeFehhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = Mhh(i1) 
Boson4(2) = gThh(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = MFe(gt3) 
 
coup2(1) = cplcFuFuhhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFeFehhL(gt2,gt3,i1) 
coup2(6) = cplcFeFehhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFeFehhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFeFehhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFe Fe Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:25))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
  g = oo512pi3 / Abs(MFu(iIN))**3*g
End Subroutine FuToFucFeFe 
 
 
Subroutine FuToFucFuFu(iIN,MFu,MVZ,MAh,Mhh,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,IntegralSs,IntegralSSss,IntegralSSst,              & 
& IntegralVs,IntegralVSss,IntegralVSst,IntegralVVss,IntegralVVst,NSs,NSSss,              & 
& NSSst,NVs,NVSss,NVSst,NVVss,NVVst,gTVZ,gTAh,gThh,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MVZ,MAh(2),Mhh(2)

Complex(dp),Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),          & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Real(dp),Intent(inout) :: IntegralSs(500000,10),IntegralVs(25000,9),IntegralVVss(500000,12)

Complex(dp),Intent(inout) :: IntegralSSss(500000,12),IntegralSSst(500000,16),IntegralVSss(500000,12),              & 
& IntegralVSst(500000,16),IntegralVVst(25000,12)

Real(dp),Intent(inout) :: gTVZ,gTAh(2),gThh(2)

Integer, Intent(inout) :: NSs,NSSss,NSSst,NVs,NVSss,NVSst,NVVss,NVVst
Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp) :: Boson2(2), mass(4),  Boson4(4) 
Complex(dp) :: coup(4), coup2(8),coupT 
mass(1) = MFu(iIN) 
 
Isum = 25 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=gt1, iIN-1
Isum = 0 
 
If(Abs(MFu(iIN)).gt.(Abs(MFu(gt3))+Abs(MFu(gt2))+Abs(MFu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
Boson2(1) = MVZ 
Boson2(2) =gTVZ 
 
Boson4(1) = MVZ 
Boson4(2) =gTVZ 
Boson4(3) = MVZ 
Boson4(4) =gTVZ 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup(2) = Conjg(cplcFuFuVZL(iIN,gt1)) 
coup(1) = Conjg(cplcFuFuVZR(iIN,gt1)) 
coup(4) = Conjg(cplcFuFuVZL(gt2,gt3)) 
coup(3) = Conjg(cplcFuFuVZR(gt2,gt3))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
If (gt1.Eq.gt3) Then 
resR=resR/2._dp 
End If
resR= 3*resR ! color factor 
resS = resS + resR 
 
 mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup(2) = Conjg(cplcFuFuVZL(iIN,gt3)) 
coup(1) = Conjg(cplcFuFuVZR(iIN,gt3)) 
coup(4) = Conjg(cplcFuFuVZL(gt2,gt1)) 
coup(3) = Conjg(cplcFuFuVZR(gt2,gt1))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
If (gt1.Eq.gt3) Then 
resR=resR/2._dp 
End If
resR= 3*resR ! color factor 
resS = resS + resR 
 
 mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt3) 
coup2(2) = cplcFuFuVZR(iIN,gt3) 
coup2(3) = Conjg(cplcFuFuVZL(gt1,iIN)) 
coup2(4) = Conjg(cplcFuFuVZR(gt1,iIN))  
coup2(5) = cplcFuFuVZL(gt2,gt1) 
coup2(6) = cplcFuFuVZR(gt2,gt1) 
coup2(7) = Conjg(cplcFuFuVZL(gt3,gt2)) 
coup2(8) = Conjg(cplcFuFuVZR(gt3,gt2)) 
Call IntegrateGaugeST(Boson4, mass, coup2, deltaM, epsI,IntegralVVst,NVVst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



!-------------- 
!  Ah 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = MAh(i1) 
Boson2(2) =gTAh(i1) 
 
Boson4(1) = MAh(i1) 
Boson4(2) =gTAh(i1) 
Boson4(3) = MAh(i1) 
Boson4(4) =gTAh(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup(2) = Conjg(cplcFuFuAhL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFuAhR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFuFuAhL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFuFuAhR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
If (gt1.Eq.gt3) Then 
resR=resR/2._dp 
End If
resR= 3*resR ! color factor 
resS = resS + resR 
 
 mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup(2) = Conjg(cplcFuFuAhL(iIN,gt3,i1)) 
coup(1) = Conjg(cplcFuFuAhR(iIN,gt3,i1)) 
coup(4) = Conjg(cplcFuFuAhL(gt2,gt1,i1)) 
coup(3) = Conjg(cplcFuFuAhR(gt2,gt1,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
If (gt1.Eq.gt3) Then 
resR=resR/2._dp 
End If
resR= 3*resR ! color factor 
resS = resS + resR 
 
 mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuAhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i1)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i1))  
coup2(5) = cplcFuFuAhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuAhL(gt3,gt2,i1)) 
coup2(7) = Conjg(cplcFuFuAhR(gt3,gt2,i1)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah'
      End Do 



!-------------- 
!  hh 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = Mhh(i1) 
Boson2(2) =gThh(i1) 
 
Boson4(1) = Mhh(i1) 
Boson4(2) =gThh(i1) 
Boson4(3) = Mhh(i1) 
Boson4(4) =gThh(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup(2) = Conjg(cplcFuFuhhL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFuhhR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFuFuhhL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFuFuhhR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
If (gt1.Eq.gt3) Then 
resR=resR/2._dp 
End If
resR= 3*resR ! color factor 
resS = resS + resR 
 
 mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup(2) = Conjg(cplcFuFuhhL(iIN,gt3,i1)) 
coup(1) = Conjg(cplcFuFuhhR(iIN,gt3,i1)) 
coup(4) = Conjg(cplcFuFuhhL(gt2,gt1,i1)) 
coup(3) = Conjg(cplcFuFuhhR(gt2,gt1,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
If (gt1.Eq.gt3) Then 
resR=resR/2._dp 
End If
resR= 3*resR ! color factor 
resS = resS + resR 
 
 mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuhhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i1)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i1))  
coup2(5) = cplcFuFuhhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuhhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i1)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i1)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='hh'
      End Do 



!-------------- 
!  VZ, Ah 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt3) 
coup2(6) = cplcFuFuVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFuFuAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt3,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt3) 
coup2(2) = cplcFuFuVZR(iIN,gt3) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt1) 
coup2(6) = cplcFuFuVZR(gt2,gt1) 
coup2(8) = Conjg(cplcFuFuAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt3,gt2,i2)) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFuVZL(iIN,gt3) 
coup2(2) = cplcFuFuVZR(iIN,gt3) 
coup2(4) = Conjg(cplcFuFuAhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt1) 
coup2(6) = cplcFuFuVZR(gt2,gt1) 
coup2(8) = Conjg(cplcFuFuAhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt1,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuAhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt3) 
coup2(6) = cplcFuFuVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFuFuAhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt1,gt2,i2)) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: VZ,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,Ah'
      End Do 



!-------------- 
!  VZ, hh 
!-------------- 
  Do i2=1,2
Boson4(1) = MVZ 
Boson4(2) = gTVZ 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt3) 
coup2(6) = cplcFuFuVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt3) 
coup2(2) = cplcFuFuVZR(iIN,gt3) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt1) 
coup2(6) = cplcFuFuVZR(gt2,gt1) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i2)) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFuVZL(iIN,gt3) 
coup2(2) = cplcFuFuVZR(iIN,gt3) 
coup2(4) = Conjg(cplcFuFuhhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt1) 
coup2(6) = cplcFuFuVZR(gt2,gt1) 
coup2(8) = Conjg(cplcFuFuhhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt1,gt2,i2)) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuVZL(iIN,gt1) 
coup2(2) = cplcFuFuVZR(iIN,gt1) 
coup2(4) = Conjg(cplcFuFuhhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuVZL(gt2,gt3) 
coup2(6) = cplcFuFuVZR(gt2,gt3) 
coup2(8) = Conjg(cplcFuFuhhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt1,gt2,i2)) 
coupT = coup2(7) 
coup2(7) = coup2(8) 
coup2(8) = coupT 
Call IntegrateGaugeSscalarT(Boson4, mass, coup2, deltaM, epsI,IntegralVSst,NVSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: VZ,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ,hh'
      End Do 



!-------------- 
!  Ah, Ah 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = MAh(i1) 
Boson4(2) = gTAh(i1) 
Boson4(3) = MAh(i2) 
Boson4(4) = gTAh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt3,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFuFuAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuAhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuAhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt3,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFuAhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuAhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt1,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuAhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuAhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt3,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFuFuAhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuAhR(gt1,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: Ah,Ah" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,Ah'
        End Do 
      End Do 



!-------------- 
!  Ah, hh 
!-------------- 
Do i1=1,2
  Do i2=1,2
Boson4(1) = MAh(i1) 
Boson4(2) = gTAh(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt3,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuAhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFuAhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt1,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuAhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuAhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuAhL(gt2,gt3,i1) 
coup2(6) = cplcFuFuAhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt1,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: Ah,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='Ah,hh'
        End Do 
      End Do 



!-------------- 
!  hh, hh 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = Mhh(i1) 
Boson4(2) = gThh(i1) 
Boson4(3) = Mhh(i2) 
Boson4(4) = gThh(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFu(gt1) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt3) 
 
coup2(1) = cplcFuFuhhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuhhL(gt2,gt3,i1) 
coup2(6) = cplcFuFuhhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt1) 
mass(4) = MFu(gt3) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuhhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt1,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt1,iIN,i2))  
coup2(5) = cplcFuFuhhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuhhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt3,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt3,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(3) = -MFu(gt2) 
mass(4) = MFu(gt1) 
 
coup2(1) = cplcFuFuhhL(iIN,gt3,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt3,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuhhL(gt2,gt1,i1) 
coup2(6) = cplcFuFuhhR(gt2,gt1,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt1,gt2,i2)) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
mass(2) = MFu(gt3) 
mass(4) = MFu(gt1) 
mass(3) = -MFu(gt2) 
 
coup2(1) = cplcFuFuhhL(iIN,gt1,i1) 
coup2(2) = cplcFuFuhhR(iIN,gt1,i1) 
coup2(4) = Conjg(cplcFuFuhhL(gt3,iIN,i2)) 
coup2(3) = Conjg(cplcFuFuhhR(gt3,iIN,i2))  
coup2(5) = cplcFuFuhhL(gt2,gt3,i1) 
coup2(6) = cplcFuFuhhR(gt2,gt3,i1) 
coup2(8) = Conjg(cplcFuFuhhL(gt1,gt2,i2)) 
coup2(7) = Conjg(cplcFuFuhhR(gt1,gt2,i2)) 
Call IntegrateScalarST(Boson4, mass, coup2, deltaM, epsI,IntegralSSst,NSSst, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = -2._dp*resC 
resC= 3*resC ! color factor 
If (gt1.Eq.gt3) Then 
resC=resC/2._dp 
End If
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFu Fu Propagator: hh,hh" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='hh,hh'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=gt1, iIN-1
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:25))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
  g = oo512pi3 / Abs(MFu(iIN))**3*g
End Subroutine FuToFucFuFu 
 
 
Subroutine FuToFdcFeFv(iIN,MFd,MFe,MVWm,MHm,MFu,cplcFeFvHmL,cplcFeFvHmR,              & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& IntegralSs,IntegralSSss,IntegralVs,IntegralVSss,IntegralVVss,NSs,NSSss,NVs,            & 
& NVSss,NVVss,gTVWm,gTHm,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFd(3),MFe(3),MVWm,MHm(2),MFu(3)

Complex(dp),Intent(in) :: cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),            & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3)

Real(dp),Intent(inout) :: IntegralSs(500000,10),IntegralVs(25000,9),IntegralVVss(500000,12)

Complex(dp),Intent(inout) :: IntegralSSss(500000,12),IntegralVSss(500000,12)

Real(dp),Intent(inout) :: gTVWm,gTHm(2)

Integer, Intent(inout) :: NSs,NSSss,NVs,NVSss,NVVss
Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp) :: Boson2(2), mass(4),  Boson4(4) 
Complex(dp) :: coup(4), coup2(8),coupT 
mass(1) = MFu(iIN) 
 
Isum = 9 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
If(Abs(MFu(iIN)).gt.(Abs(0._dp)+Abs(MFe(gt2))+Abs(MFd(gt1)))) Then 
!-------------- 
!  conj[VWm] 
!-------------- 
Isum = Isum + 1 
Boson2(1) = MVWm 
Boson2(2) =gTVWm 
 
Boson4(1) = MVWm 
Boson4(2) =gTVWm 
Boson4(3) = MVWm 
Boson4(4) =gTVWm 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFd(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = 0._dp 
 
coup(2) = Conjg(cplcFuFdcVWmL(iIN,gt1)) 
coup(1) = Conjg(cplcFuFdcVWmR(iIN,gt1)) 
coup(4) = Conjg(cplcFeFvVWmL(gt2,gt3)) 
coup(3) = Conjg(cplcFeFvVWmR(gt2,gt3))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
resR= 1*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fd cFe Fv Propagator: conj[VWm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm]'



!-------------- 
!  conj[Hm] 
!-------------- 
Do i1=1,2
Isum = Isum + 1 
Boson2(1) = MHm(i1) 
Boson2(2) =gTHm(i1) 
 
Boson4(1) = MHm(i1) 
Boson4(2) =gTHm(i1) 
Boson4(3) = MHm(i1) 
Boson4(4) =gTHm(i1) 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFd(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = 0._dp 
 
coup(2) = Conjg(cplcFuFdcHmL(iIN,gt1,i1)) 
coup(1) = Conjg(cplcFuFdcHmR(iIN,gt1,i1)) 
coup(4) = Conjg(cplcFeFvHmL(gt2,gt3,i1)) 
coup(3) = Conjg(cplcFeFvHmR(gt2,gt3,i1))
Call IntegrateScalarSS(Boson2,mass,coup,deltaM,epsI,IntegralSs,NSs,resR, check) 
resR= 1*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fd cFe Fv Propagator: conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hm]'
      End Do 



!-------------- 
!  conj[VWm], conj[Hm] 
!-------------- 
  Do i2=1,2
Boson4(1) = MVWm 
Boson4(2) = gTVWm 
Boson4(3) = MHm(i2) 
Boson4(4) = gTHm(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFd(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = 0._dp 
 
coup2(1) = cplcFuFdcVWmL(iIN,gt1) 
coup2(2) = cplcFuFdcVWmR(iIN,gt1) 
coup2(4) = cplcFuFdcHmL(iIN,gt1,i2) 
coup2(3) = cplcFuFdcHmR(iIN,gt1,i2)  
coup2(5) = cplcFeFvVWmL(gt2,gt3) 
coup2(6) = cplcFeFvVWmR(gt2,gt3) 
coup2(8) = cplcFeFvHmL(gt2,gt3,i2) 
coup2(7) = cplcFeFvHmR(gt2,gt3,i2) 
Call IntegrateGaugeSscalarS(Boson4, mass, coup2, deltaM, epsI,IntegralVSss,NVSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fd cFe Fv Propagator: conj[VWm],conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[VWm],conj[Hm]'
      End Do 



!-------------- 
!  conj[Hm], conj[Hm] 
!-------------- 
Do i1=1,1
  Do i2=i1+1,2
Boson4(1) = MHm(i1) 
Boson4(2) = gTHm(i1) 
Boson4(3) = MHm(i2) 
Boson4(4) = gTHm(i2) 
Isum = Isum + 1 
 
resS = 0._dp 
mass(2) = MFd(gt1) 
mass(3) = -MFe(gt2) 
mass(4) = 0._dp 
 
coup2(1) = cplcFuFdcHmL(iIN,gt1,i1) 
coup2(2) = cplcFuFdcHmR(iIN,gt1,i1) 
coup2(4) = cplcFuFdcHmL(iIN,gt1,i2) 
coup2(3) = cplcFuFdcHmR(iIN,gt1,i2)  
coup2(5) = cplcFeFvHmL(gt2,gt3,i1) 
coup2(6) = cplcFeFvHmR(gt2,gt3,i1) 
coup2(8) = cplcFeFvHmL(gt2,gt3,i2) 
coup2(7) = cplcFeFvHmR(gt2,gt3,i2) 
Call IntegrateScalarS1S2(Boson4, mass, coup2, deltaM, epsI,IntegralSSss,NSSss, resC, check) 
If (resC.ne.resC) resC = 0._dp
resC = 2._dp*resC 
resC= 1*resC ! color factor 
resS = resS + resC 
If (resS.ne.resS) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fd cFe Fv Propagator: conj[Hm],conj[Hm]" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp  
Else 
gSum(gt1,gt2,gt3,Isum)= resS  
End If 
Contribution(gt1,gt2,gt3,Isum)='conj[Hm],conj[Hm]'
        End Do 
      End Do 



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1,3
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:9))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
  g = oo512pi3 / Abs(MFu(iIN))**3*g
End Subroutine FuToFdcFeFv 
 
 
Subroutine FuToFucFvFv(iIN,MFu,MVZ,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,IntegralVs,IntegralVVss,NVs,NVVss,gTVZ,deltaM,epsI,check,g,WriteContributions)

Implicit None 
 
Real(dp),Intent(in) :: MFu(3),MVZ

Complex(dp),Intent(in) :: cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3)

Real(dp),Intent(inout) :: IntegralVs(25000,9),IntegralVVss(500000,12)

Real(dp),Intent(inout) :: gTVZ

Integer, Intent(inout) :: NVs,NVVss
Real(dp),Intent(inout)::g(:,:,:) 
Logical, Intent(in) :: check 
Integer, Intent(in) :: iIN 
Real(dp), Intent(in) :: epsI, deltaM 
Logical, Optional :: WriteContributions 
Integer :: i1,i2,gt1,gt2,gt3, Isum 
Real(dp) :: resR,  res1, res2, resD, m_in 
Complex(dp) :: resC, resS 
Real(dp), Allocatable :: gSum(:,:,:,:) 
Character(len=20), Allocatable :: Contribution(:,:,:,:) 
Real(dp) :: Boson2(2), mass(4),  Boson4(4) 
Complex(dp) :: coup(4), coup2(8),coupT 
mass(1) = MFu(iIN) 
 
Isum = 1 
Allocate( gSum(3,3,3, Isum) ) 
Allocate( Contribution(3,3,3, Isum) ) 
gSum = 0._dp  
Contribution = ' ' 
 
Isum = 0 
 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
Isum = 0 
 
If(Abs(MFu(iIN)).gt.(Abs(0._dp)+Abs(0._dp)+Abs(MFu(gt1)))) Then 
!-------------- 
!  VZ 
!-------------- 
Isum = Isum + 1 
Boson2(1) = MVZ 
Boson2(2) =gTVZ 
 
Boson4(1) = MVZ 
Boson4(2) =gTVZ 
Boson4(3) = MVZ 
Boson4(4) =gTVZ 
 
resS=0._dp 
resD=0._dp 
 
mass(2) = MFu(gt1) 
mass(3) = -0._dp 
mass(4) = 0._dp 
 
coup(2) = Conjg(cplcFuFuVZL(iIN,gt1)) 
coup(1) = Conjg(cplcFuFuVZR(iIN,gt1)) 
coup(4) = Conjg(cplcFvFvVZL(gt2,gt3)) 
coup(3) = Conjg(cplcFvFvVZR(gt2,gt3))
Call IntegrateGaugeSS(Boson2,mass,coup,deltaM,epsI,IntegralVs,NVs,resR, check) 
resR= 1*resR ! color factor 
resS = resS + resR 
 
 resD = resD + resS 
If (resD.ne.resD) Then 
Write(*,*) "NaN appearing in the following diagrams: " 
Write(*,*) "Fu->Fu cFv Fv Propagator: VZ" 
Write(*,*)  "M_in: ",m_in 
Write(*,*)  "mass: ",mass 
Write(*,*)  "coup: ",coup 
gSum(gt1,gt2,gt3,Isum)= 0._dp
Else 
gSum(gt1,gt2,gt3,Isum)=resD
End If 
Contribution(gt1,gt2,gt3,Isum)='VZ'



Else 
gSum(gt1,gt2,gt3,:)= 0._dp  
End If 
       End Do 
     End Do 
   End Do 
!---------- 
!Summing 
!---------- 
g=0._dp 
    Do gt1=1, iIN-1
      Do gt2=1,3
        Do gt3=1,3
g(gt1,gt2,gt3)=Sum(gSum(gt1,gt2,gt3,1:1))
If (g(gt1,gt2,gt3).Lt.0._dp) Then
  Write (ErrCan,*)'Error in Subroutine'//NameOfUnit(Iname)
  g(gt1,gt2,gt3)=0._dp
End If
       End Do 
     End Do 
   End Do 
  g = oo512pi3 / Abs(MFu(iIN))**3*g
End Subroutine FuToFucFvFv 
 
 
End Module Fu3Decays_gumTHDMII 
 
