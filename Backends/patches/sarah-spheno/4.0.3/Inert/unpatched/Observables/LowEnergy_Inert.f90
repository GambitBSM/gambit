! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:33 on 18.2.2026   
! ----------------------------------------------------------------------  
 
 
Module LowEnergy_Inert 
Use Control 
Use Settings 
Use Couplings_Inert 
Use LoopCouplings_Inert 
Use LoopMasses_SM_HC 
Use LoopFunctions 
Use LoopMasses_Inert 
Use StandardModel 
Use RunSM_Inert
Private::F1,F2,F3,F4,F3Gamma
!private variables
 

Contains


Subroutine Gminus2(Ifermion,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,cplcFeFeG0L,          & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFeFvcHpL,cplcFeFvcHpR,cplHpcHpVP,a_mu)

Real(dp),Intent(in)  :: MFe(3),MFe2(3),MG0,MG02,Mhh,Mhh2,MHp(2),MHp2(2)

Complex(dp),Intent(in)  :: cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFvcHpL(3,3,2),              & 
& cplcFeFvcHpR(3,3,2),cplHpcHpVP(2,2)

Real(dp), Intent(out) :: a_mu 
Integer, Intent(in) :: Ifermion 
Real(dp) :: ratio, chargefactor 
Integer :: i1, i2, i3, gt1, gt2 
Complex(dp) :: coup1L,coup1R,coup2L,coup2R 
 
Iname = Iname + 1 
NameOfUnit(Iname) = "Gminus2" 
 
 
a_mu = 0._dp 
gt1 = Ifermion 
gt2 = Ifermion 
 
chargefactor = 1 
Do i1= 1,3
  Do i2= 2,2
   i3 = i2
  If ((0._dp.gt.mz2).Or.(MHp2(i2).gt.mz2).Or.(MHp2(i3).gt.mz2)) Then
coup1L = cplcFeFvcHpL(gt1,i1,i2)
coup1R = cplcFeFvcHpR(gt1,i1,i2)
coup2L = cplcFvFeHpL(i1,gt2,i3)
coup2R = cplcFvFeHpR(i1,gt2,i3)
ratio = MHp2(i2)/0._dp
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
a_mu = a_mu - chargefactor*(2._dp*Real(coup1L*Conjg(coup1R),dp)*F4(ratio)/0._dp& 
      & +2._dp*MFe(Ifermion)*(Abs(coup1L)**2 + Abs(coup1R)**2)*F1(ratio)/0._dp) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
Do i1= 2,1
  Do i2= 1,3
   i3 = i2
  If ((MG02.gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFeG0L(gt1,i2)
coup1R = cplcFeFeG0R(gt1,i2)
coup2L = cplcFeFeG0L(i3,gt2)
coup2R = cplcFeFeG0R(i3,gt2)
ratio = MG02/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
a_mu = a_mu - chargefactor*(Real(coup1L*Conjg(coup1R),dp)*F3gamma(ratio)/MFe(i2)& 
      & - 2._dp*MFe(Ifermion)*(Abs(coup1L)**2 + Abs(coup1R)**2)*F2(ratio)/MFe2(i2)) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
  Do i2= 1,3
   i3 = i2
  If ((Mhh2.gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFehhL(gt1,i2)
coup1R = cplcFeFehhR(gt1,i2)
coup2L = cplcFeFehhL(i3,gt2)
coup2R = cplcFeFehhR(i3,gt2)
ratio = Mhh2/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
a_mu = a_mu - chargefactor*(Real(coup1L*Conjg(coup1R),dp)*F3gamma(ratio)/MFe(i2)& 
      & - 2._dp*MFe(Ifermion)*(Abs(coup1L)**2 + Abs(coup1R)**2)*F2(ratio)/MFe2(i2)) 
End if 
 
End if 
  End Do


a_mu = a_mu*MFe(Ifermion)*oo16pi2 
Iname = Iname -1 
 
End Subroutine Gminus2 
 
 
Subroutine LeptonEDM(Ifermion,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,MVWp,               & 
& MVWp2,MVZ,MVZ2,cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,            & 
& cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,             & 
& cplcFeFeVZR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplHpcHpVP,          & 
& cplcVWpVPVWp,EDM)

Implicit None
Real(dp),Intent(in)  :: MFe(3),MFe2(3),MG0,MG02,Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp),Intent(in)  :: cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),& 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),             & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplHpcHpVP(2,2),cplcVWpVPVWp

Real(dp), Intent(out) :: EDM 
Real(dp) :: ratio, chargefactor 
Integer, Intent(in) :: Ifermion 
Integer :: i1, i2, i3, gt1, gt2 
Complex(dp) :: coup1L,coup1R,coup2L,coup2R 
 
Iname = Iname + 1 
NameOfUnit(Iname) = "Gminus2" 
 
 
EDM = 0._dp 
gt1 = Ifermion 
gt2 = Ifermion 
 
chargefactor = 1 
Do i1= 1,3
  Do i2= 2,2
   i3 = i2
  If ((0._dp.gt.mz2).Or.(MHp2(i2).gt.mz2).Or.(MHp2(i3).gt.mz2)) Then
coup1L = cplcFeFvcHpL(gt1,i1,i2)
coup1R = cplcFeFvcHpR(gt1,i1,i2)
coup2L = cplcFvFeHpL(i1,gt2,i3)
coup2R = cplcFvFeHpR(i1,gt2,i3)
!ratio = 0._dp/MHp2(i2)
 !If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
!EDM = EDM +(1)* chargefactor*Aimag(coup1L*Conjg(coup1R))*FeynFunctionB(ratio)*0._dp/MHp2(i2) 
!End if 
 
ratio = MHp2(i2)/0._dp
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - chargefactor*(Aimag(coup1L*Conjg(coup1R))*F4(ratio)/0._dp) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
Do i1= 1,3
  If ((0._dp.gt.mz2).Or.(MVWp2.gt.mz2).Or.(MVWp2.gt.mz2)) Then
coup1L = cplcFeFvcVWpL(gt1,i1)
coup1R = cplcFeFvcVWpR(gt1,i1)
coup2L = cplcFvFeVWpL(i1,gt2)
coup2R = cplcFvFeVWpR(i1,gt2)
ratio = MVWp2/0._dp
 chargefactor = chargefactor*(1._dp)
 ratio = 1._dp/ratio ! conventions in 1402.7065 are different 
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 2._dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*gVVF(ratio)/0._dp) 
End if 
 
End if 
   End Do


chargefactor = 1 
Do i1= 2,1
  Do i2= 1,3
   i3 = i2
  If ((MG02.gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFeG0L(gt1,i2)
coup1R = cplcFeFeG0R(gt1,i2)
coup2L = cplcFeFeG0L(i3,gt2)
coup2R = cplcFeFeG0R(i3,gt2)
!ratio = MFe2(i2)/MG02
 !If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
!EDM = EDM -(-1)* chargefactor*Aimag(coup1R*Conjg(coup1L))*FeynFunctionA(ratio)*MFe(i2)/MG02 
!End if 
 
ratio = MG02/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 0.5_dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*F3gamma(ratio)/MFe(i2)) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
  Do i2= 1,3
   i3 = i2
  If ((Mhh2.gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFehhL(gt1,i2)
coup1R = cplcFeFehhR(gt1,i2)
coup2L = cplcFeFehhL(i3,gt2)
coup2R = cplcFeFehhR(i3,gt2)
!ratio = MFe2(i2)/Mhh2
 !If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
!EDM = EDM -(-1)* chargefactor*Aimag(coup1R*Conjg(coup1L))*FeynFunctionA(ratio)*MFe(i2)/Mhh2 
!End if 
 
ratio = Mhh2/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 0.5_dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*F3gamma(ratio)/MFe(i2)) 
End if 
 
End if 
  End Do


chargefactor = 1 
  Do i2= 1,3
   i3 = i2
  If ((0._dp.gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFeVPL(gt1,i2)
coup1R = cplcFeFeVPR(gt1,i2)
coup2L = cplcFeFeVPL(i3,gt2)
coup2R = cplcFeFeVPR(i3,gt2)
ratio = 0._dp/MFe2(i2)
 ratio = 1._dp/ratio ! conventions in 1402.7065 are different 
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 4._dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*gFFV(ratio)/MFe(i2)) 
End if 
 
End if 
  End Do


chargefactor = 1 
  Do i2= 1,3
   i3 = i2
  If ((MVZ2.gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFeVZL(gt1,i2)
coup1R = cplcFeFeVZR(gt1,i2)
coup2L = cplcFeFeVZL(i3,gt2)
coup2R = cplcFeFeVZR(i3,gt2)
ratio = MVZ2/MFe2(i2)
 ratio = 1._dp/ratio ! conventions in 1402.7065 are different 
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 4._dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*gFFV(ratio)/MFe(i2)) 
End if 
 
End if 
  End Do


EDM = ecmfactor*EDM*oo16pi2 
Iname = Iname -1 
 
End Subroutine LeptonEDM 
 
 
Subroutine DeltaRho(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,            & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0H0VZ,            & 
& cplA0HpcVWp,cplcFdFdVZL,cplcFdFdVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFeVZL,           & 
& cplcFeFeVZR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,           & 
& cplcFvFvVZR,cplcgAgWpcVWp,cplcgWCgAcVWp,cplcgWCgWCVZ,cplcgWCgZcVWp,cplcgWpgWpVZ,       & 
& cplcgZgWpcVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,& 
& cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWp,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,             & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplG0G0cVWpVWp,cplG0G0VZVZ,cplG0hhVZ,cplG0HpcVWp,      & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWp,cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhVZVZ,        & 
& cplhhHpcVWp,cplhhVZVZ,cplHpcHpcVWpVWp,cplHpcHpVZ,cplHpcHpVZVZ,cplHpcVWpVP,             & 
& cplHpcVWpVZ,rho)

Implicit None
Real(dp),Intent(in)  :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp),Intent(in)  :: cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0H0VZ,cplA0HpcVWp(2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),& 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),               & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),               & 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgWCgAcVWp,cplcgWCgWCVZ,            & 
& cplcgWCgZcVWp,cplcgWpgWpVZ,cplcgZgWpcVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,        & 
& cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWp,       & 
& cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplG0G0cVWpVWp,           & 
& cplG0G0VZVZ,cplG0hhVZ,cplG0HpcVWp(2),cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWp(2),        & 
& cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWp(2),cplhhVZVZ,cplHpcHpcVWpVWp(2,2), & 
& cplHpcHpVZ(2,2),cplHpcHpVZVZ(2,2),cplHpcVWpVP(2),cplHpcVWpVZ(2)

Real(dp), Intent(out) :: rho 
Integer :: i1, i2, i3, kont 
Real(dp) ::  delta_rho, delta_rho0, Drho_top, mu_old 
Complex(dp) ::  dmW2, dmz2 
mu_old = SetRenormalizationScale(mZ2) 
 
Call Pi1LoopVZ(0._dp,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,dmZ2)

Call Pi1LoopVWp(0._dp,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,               & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,dmW2)

Drho_top = 3*G_F*mf_u(3)**2*oosqrt2*oo8pi2 
 
mu_old = SetRenormalizationScale(mu_old) 
 
! Tree Level 
delta_rho0 =  0 
 
! 1-Loop Level 
delta_rho =  dmZ2/mz2 - dMW2/mW2 - drho_top 
 Rho= delta_rho + delta_rho0
End subroutine DeltaRho 
 
 
Subroutine STUparameter(vSM,g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,MA0,MA02,MFd,               & 
& MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,             & 
& MVZ2,cplG0hhVZ,cplG0HpcVWp,cplG0G0cVWpVWp,cplG0G0VZVZ,cplhhHpcVWp,cplhhcVWpVWp,        & 
& cplhhVZVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0HpcVWp,cplA0A0cVWpVWp,             & 
& cplA0A0VZVZ,cplH0HpcVWp,cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVPL,cplcFdFdVPR,            & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,cplcgWCgWCVP,             & 
& cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,      & 
& cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ,              & 
& cplHpcVWpVZ,cplcVWpVWpVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,   & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplHpcHpcVWpVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,     & 
& cplcVWpcVWpVWpVWp3,cplcHpVWpVZ,cplcHpVPVWp,cplHpcHpVPVZ,cplcVWpVPVWpVZ1,               & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,Spar,Tpar,Upar)

Implicit None
Real(dp),Intent(in)  :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2

Complex(dp),Intent(in)  :: cplG0hhVZ,cplG0HpcVWp(2),cplG0G0cVWpVWp,cplG0G0VZVZ,cplhhHpcVWp(2),cplhhcVWpVWp,      & 
& cplhhVZVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0HpcVWp(2),cplA0A0cVWpVWp,          & 
& cplA0A0VZVZ,cplH0HpcVWp(2),cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWpVP,      & 
& cplcgWCgWCVP,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcVWpVPVWp,cplHpcHpVPVP(2,2),            & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),     & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
& cplcFvFvVZR(3,3),cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),             & 
& cplcVWpVWpVZ,cplHpcHpVZVZ(2,2),cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,        & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),           & 
& cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplHpcHpcVWpVWp(2,2),          & 
& cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcHpVWpVZ(2),               & 
& cplcHpVPVWp(2),cplHpcHpVPVZ(2,2),cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3

Real(dp), Intent(out) :: Spar,Tpar,Upar 
Integer :: i1, i2, i3, kont 
Real(dp) ::  mu_old, cw2, sw2, rMS_SM_save 
Real(dp) ::  delta_T_SM, delta_S_SM, delta_U_SM 
Complex(dp) :: PiZZ, PiZZ_mz2, PiWW,PiWW_mw2,PiZg_mz2, Pigg_mz2 
Complex(dp) :: PiZZ_SM, PiZZ_mz2_SM, PiWW_SM,PiWW_mw2_SM,PiZg_mz2_SM, Pigg_mz2_SM 
Complex(dp) :: LamSM 
Complex(dp), Intent(in) :: YdSM(3,3), YuSM(3,3), YeSM(3,3) 
Real(dp), Intent(in) :: g1SM,g2SM,g3SM,vSM 
mu_old = SetRenormalizationScale(mZ2) 
 
LamSM = Mhh2/vSM**2
 
Call OneLoop_Z_W_Gamma_SM(vSM,g1SM,g2SM,g3SM,LamSM,YuSM,YdSM,YeSM,kont, & 
 & PiZZ_SM,PiZZ_mz2_SM,PiWW_SM,PiWW_mw2_SM,PiZg_mz2_SM,Pigg_mz2_SM) 
Call Pi1LoopVZ(0._dp,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,           & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiZZ)

Call Pi1LoopVZ(MVZ2,MH0,MH02,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,            & 
& MG0,MG02,MVZ,MVZ2,MHp,MHp2,MVWp,MVWp2,cplA0H0VZ,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplG0hhVZ,cplcgWpgWpVZ,cplcgWCgWCVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,     & 
& cplA0A0VZVZ,cplG0G0VZVZ,cplH0H0VZVZ,cplhhhhVZVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,          & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,kont,PiZZ_mz2)

Call Pi1LoopVWp(0._dp,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,               & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,PiWW)

Call Pi1LoopVWp(MVWp2,MHp,MHp2,MA0,MA02,MFd,MFd2,MFu,MFu2,MFe,MFe2,MG0,               & 
& MG02,MH0,MH02,Mhh,Mhh2,MVWp,MVWp2,MVZ,MVZ2,cplA0HpcVWp,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplG0HpcVWp,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,     & 
& cplcgWCgZcVWp,cplH0HpcVWp,cplhhHpcVWp,cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,            & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplA0A0cVWpVWp,cplG0G0cVWpVWp,cplH0H0cVWpVWp,cplhhhhcVWpVWp, & 
& cplHpcHpcVWpVWp,cplcVWpVPVPVWp3,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpcVWpVWpVWp2,    & 
& cplcVWpcVWpVWpVWp3,cplcVWpcVWpVWpVWp1,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3, & 
& kont,PiWW_mw2)

Call Pi1LoopVPVZ(MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,     & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWCgWCVP,              & 
& cplcgWCgWCVZ,cplcgWpgWpVP,cplcgWpgWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplcVWpVPVWp,           & 
& cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplHpcHpVP,               & 
& cplHpcHpVPVZ,cplHpcHpVZ,cplHpcVWpVP,cplHpcVWpVZ,kont,PiZg_mz2)

Call Pi1LoopVP(MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHp,MHp2,MVWp,MVWp2,cplcFdFdVPL,       & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,              & 
& cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp3,         & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,kont,Pigg_mz2)

PiZZ = PiZZ - PiZZ_SM 
PiZZ_mz2 = PiZZ_mz2 - PiZZ_mz2_SM 
PiWW = PiWW - PiWW_SM 
PiWW_mw2 = PiWW_mw2 - PiWW_mw2_SM 
PiZg_mz2 = PiZg_mz2 - PiZg_mz2_SM 
Pigg_mz2 = Pigg_mz2 - Pigg_mz2_SM 
sw2 = 0.22290_dp 
cw2 = 1._dp - sw2 
 
mu_old = SetRenormalizationScale(mu_old) 
 
! T-parameter 
Tpar= PiZZ/mz2 - PiWW/mW2  
 Tpar= -Tpar/alpha 


! S-parameter 
Spar= (PiZZ_mz2-PiZZ)/mz2 - (cw2-sw2)/(sqrt(cw2*sw2))*PiZg_mz2/mz2 - Pigg_mz2/mz2
Spar= 4._dp*sw2*cw2/alpha*Spar 


! U-parameter 
Upar= (PiWW_mw2-PiWW)/mw2 -cw2*(PiZZ_mz2-PiZZ)/mz2 - 2._dp*(sqrt(cw2*sw2))*PiZg_mz2/mz2 - sw2*Pigg_mz2/mz2
Upar= 4._dp*sw2/alpha*Upar 


End subroutine STUparameter 
 
 
Subroutine CalculateLowEnergyConstraints(g1input,g2input,g3input,Lam5input,           & 
& Lam1input,Lam4input,Lam3input,Lam2input,Yeinput,Ydinput,Yuinput,mHd2input,             & 
& mHu2input,vinput,Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho)

Real(dp),Intent(inout) :: g1input,g2input,g3input,mHd2input,mHu2input,vinput

Complex(dp),Intent(inout) :: Lam5input,Lam1input,Lam4input,Lam3input,Lam2input,Yeinput(3,3),Ydinput(3,3),          & 
& Yuinput(3,3)

Real(dp) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,v

Complex(dp) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Complex(dp) :: cplA0A0cVWpVWp,cplA0A0G0,cplA0A0hh,cplA0A0VZVZ,cplA0cHpVWp(2),cplA0G0H0,              & 
& cplA0H0hh,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),  & 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),  & 
& cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),& 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),               & 
& cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),  & 
& cplcFeFeVZR(3,3),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFeFvcVWpL(3,3),           & 
& cplcFeFvcVWpR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),            & 
& cplcFuFdVWpR(3,3),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3), & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),cplcFvFeVWpL(3,3),              & 
& cplcFvFeVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWpcVWp,cplcgWCgAcVWp,       & 
& cplcgWCgWCVP,cplcgWCgWCVZ,cplcgWCgZcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgZgWpcVWp,       & 
& cplcHpVPVWp(2),cplcHpVWpVZ(2),cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,& 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWp,cplcVWpVPVWpVZ1,          & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,          & 
& cplcVWpVWpVZVZ3,cplG0cHpVWp(2),cplG0G0cVWpVWp,cplG0G0hh,cplG0G0VZVZ,cplG0H0H0,         & 
& cplG0hhVZ,cplG0HpcVWp(2),cplH0cHpVWp(2),cplH0H0cVWpVWp,cplH0H0hh,cplH0H0VZVZ,          & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplhhcHpVWp(2),cplhhcVWpVWp,cplhhhhcVWpVWp,             & 
& cplhhhhhh,cplhhhhVZVZ,cplhhHpcHp(2,2),cplhhHpcVWp(2),cplhhVZVZ,cplHpcHpcVWpVWp(2,2),   & 
& cplHpcHpVP(2,2),cplHpcHpVPVP(2,2),cplHpcHpVPVZ(2,2),cplHpcHpVZ(2,2),cplHpcHpVZVZ(2,2), & 
& cplHpcVWpVP(2),cplHpcVWpVZ(2),cplVGVGVG

Real(dp),Intent(out) :: Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho

Complex(dp) :: c7,c7p,c8,c8p 
Real(dp) :: ResultMuE(6), ResultTauMeson(3), ResultTemp(99) 
Real(dp) :: epsTree=1.0E-20_dp 
Complex(dp), Dimension(3,3) :: Yu_save, Yd_save, Ye_save, CKMsave 
Complex(dp) :: YuSM(3,3),YeSM(3,3),YdSM(3,3) 
Real(dp)::g1SM, g2SM, g3SM, vSM 
Real(dp) ::Qin,vev2,sinw2, mzsave, scalein, scale_save, gSM(11),Qinsave, maxdiff =0._dp 
Integer :: i1, i2, i3, gt1, gt2, gt3, gt4,iQTEST, iQFinal 
Integer :: IndexArray4(99,4), IndexArray3(99,3), IndexArray2(99,2)   
Write(*,*) "Calculating low energy constraints" 
If (MatchingOrder.gt.-1) Then 


End if 
!-------------------------------------
! running to 160 GeV for b -> so gamma
!-------------------------------------

Qin=sqrt(getRenormalizationScale()) 
scale_save = Qin 
Call RunSM_and_SUSY_RGEs(160._dp,g1input,g2input,g3input,Lam5input,Lam1input,         & 
& Lam4input,Lam3input,Lam2input,Yeinput,Ydinput,Yuinput,mHd2input,mHu2input,             & 
& vinput,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,v,CKM_160,sinW2_160,       & 
& Alpha_160,AlphaS_160,.false.)

If (MatchingOrder.eq.-1) Then 
g1=g1input 
g2=g2input 
g3=g3input 
Lam5=Lam5input 
Lam1=Lam1input 
Lam4=Lam4input 
Lam3=Lam3input 
Lam2=Lam2input 
Ye=Yeinput 
Yd=Ydinput 
Yu=Yuinput 
mHd2=mHd2input 
mHu2=mHu2input 
v=vinput 
End if 

! ## All contributions ## 

Call SolveTadpoleEquations(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,           & 
& mHu2,v,(/ ZeroC, ZeroC /))

Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,GenerationMixing,kont)

 mf_d_160 = MFd(1:3) 
 mf_d2_160 = MFd(1:3)**2 
 mf_u_160 = MFu(1:3) 
 mf_u2_160 = MFu(1:3)**2 
 mf_l_160 = MFe(1:3) 
 mf_l2_160 = MFe(1:3)**2 
If (WriteParametersAtQ) Then 
! Write running parameters at Q=160 GeV in output file 
g1input = g1
g2input = g2
g3input = g3
Lam5input = Lam5
Lam1input = Lam1
Lam4input = Lam4
Lam3input = Lam3
Lam2input = Lam2
Yeinput = Ye
Ydinput = Yd
Yuinput = Yu
mHd2input = mHd2
mHu2input = mHu2
vinput = v
End If 
 
Mhh= MhhL 
Mhh2 = Mhh2L 
MG0= MAhL 
MG02 = MAh2L 
MG0=MVZ
MG02=MVZ2
MHp(1)=MVWp
MHp2(1)=MVWp2
Call AllCouplings(Lam5,v,Lam3,Lam4,ZP,Lam1,g1,g2,TW,g3,Yd,ZDL,ZDR,Yu,ZUL,             & 
& ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,cplG0G0hh,           & 
& cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0H0VZ,cplA0HpcVWp,             & 
& cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,     & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,cplHpcVWpVZ,      & 
& cplcHpVPVWp,cplcHpVWpVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,               & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,             & 
& cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,             & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFvFvVZL,           & 
& cplcFvFvVZR,cplcFeFvcVWpL,cplcFeFvcVWpR)


! ## SM only ##

CKM = CKMsave 
!-------------------------------------
! running to M_Z 
!-------------------------------------

scalein=SetRenormalizationScale(scale_save**2) 
If (MatchingOrder.gt.-1) Then 
Call RunSM_and_SUSY_RGEs(mz,g1input,g2input,g3input,Lam5input,Lam1input,              & 
& Lam4input,Lam3input,Lam2input,Yeinput,Ydinput,Yuinput,mHd2input,mHu2input,             & 
& vinput,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,v,CKM_MZ,sinW2_MZ,         & 
& Alpha_MZ,AlphaS_MZ,.true.)

Else 
g1=g1input 
g2=g2input 
g3=g3input 
Lam5=Lam5input 
Lam1=Lam1input 
Lam4=Lam4input 
Lam3=Lam3input 
Lam2=Lam2input 
Ye=Yeinput 
Yd=Ydinput 
Yu=Yuinput 
mHd2=mHd2input 
mHu2=mHu2input 
v=vinput 
End if 
Call SolveTadpoleEquations(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,           & 
& mHu2,v,(/ ZeroC, ZeroC /))

Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,GenerationMixing,kont)

mzsave  = sqrt(mz2) 
 mf_d_mz = MFd(1:3) 
 mf_d2_mz = MFd(1:3)**2 
 mf_u_mz = MFu(1:3) 
 mf_u2_mz = MFu(1:3)**2 
 mf_l_MZ = MFe(1:3) 
 mf_l2_MZ = MFe(1:3)**2 
Call AllCouplings(Lam5,v,Lam3,Lam4,ZP,Lam1,g1,g2,TW,g3,Yd,ZDL,ZDR,Yu,ZUL,             & 
& ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,cplG0G0hh,           & 
& cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0H0VZ,cplA0HpcVWp,             & 
& cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,cplhhHpcVWp,     & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,cplHpcVWpVZ,      & 
& cplcHpVPVWp,cplcHpVWpVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,               & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,             & 
& cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,             & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFvFvVZL,           & 
& cplcFvFvVZR,cplcFeFvcVWpL,cplcFeFvcVWpR)

Mhh_s = Mhh 
Mhh2_s  = Mhh2   
MAh_s = MG0 
MAh2_s  = MG02   
Mhh= MhhL 
Mhh2 = Mhh2L 
MG0= MAhL 
MG02 = MAh2L 
Mhh= Mhh_s 
Mhh2 = Mhh2_s 
MG0= MAh_s 
MG02 = MAh2_s 

! *****  G minus 2 ***** 

Call Gminus2(1,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,cplcFeFeG0L,cplcFeFeG0R,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplHpcHpVP,ae)

Call Gminus2(2,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,cplcFeFeG0L,cplcFeFeG0R,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplHpcHpVP,amu)

Call Gminus2(3,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,cplcFeFeG0L,cplcFeFeG0R,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplHpcHpVP,atau)


! *****  Lepton EDM ***** 

Call LeptonEDM(1,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,             & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplHpcHpVP,cplcVWpVPVWp,EDMe)

Call LeptonEDM(2,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,             & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplHpcHpVP,cplcVWpVPVWp,EDMmu)

Call LeptonEDM(3,MFe,MFe2,MG0,MG02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,             & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplHpcHpVP,cplcVWpVPVWp,EDMtau)


! *****  delta Rho ***** 

sinW2=0.22290_dp 
TW = asin(sqrt(sinW2)) 
mW2=(1._dp-sinW2)*mz2 + 0
g2SM=2._dp*Sqrt(alpha*pi/sinW2) 
g1SM=g2SM*Sqrt(sinW2/(1._dp-sinW2)) 
If (MatchingOrder.gt.-1) Then 
   vSM = Sqrt(mZ2*(1._dp-sinW2)*SinW2/(pi*alpha)) 
 Else
   vSM=1/Sqrt((G_F*Sqrt(2._dp)))
End if
YuSM=0._dp
YdSM=0._dp
YeSM=0._dp
   Do i1=1,3 
      YuSM(i1,i1)=sqrt(2._dp)*mf_u(i1)/vSM 
      YeSM(i1,i1)=sqrt(2._dp)*mf_l(i1)/vSM 
      YdSM(i1,i1)=sqrt(2._dp)*mf_d(i1)/vSM 
    End Do 
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,v,g1,g2,g3,              & 
& Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,.False.)

Call SolveTadpoleEquations(g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,           & 
& mHu2,v,(/ ZeroC, ZeroC /))

Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,GenerationMixing,kont)

Call CouplingsForVectorBosons(g1,g2,TW,ZP,v,ZDL,ZUL,ZEL,cplG0hhVZ,cplG0HpcVWp,        & 
& cplG0G0cVWpVWp,cplG0G0VZVZ,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplhhhhcVWpVWp,          & 
& cplhhhhVZVZ,cplA0H0VZ,cplA0HpcVWp,cplA0A0cVWpVWp,cplA0A0VZVZ,cplH0HpcVWp,              & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,            & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,              & 
& cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcVWpVWpVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,   & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplHpcHpcVWpVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,     & 
& cplcVWpcVWpVWpVWp3,cplcHpVWpVZ,cplcHpVPVWp,cplHpcHpVPVZ,cplcVWpVPVWpVZ1,               & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)

Call DeltaRho(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,              & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplA0A0cVWpVWp,cplA0A0VZVZ,cplA0H0VZ,cplA0HpcVWp,    & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFeVZL,cplcFeFeVZR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,           & 
& cplcgAgWpcVWp,cplcgWCgAcVWp,cplcgWCgWCVZ,cplcgWCgZcVWp,cplcgWpgWpVZ,cplcgZgWpcVWp,     & 
& cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcVWpVPVPVWp1,              & 
& cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWp,cplcVWpVWpVZ,cplcVWpVWpVZVZ1,             & 
& cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplG0G0cVWpVWp,cplG0G0VZVZ,cplG0hhVZ,cplG0HpcVWp,      & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWp,cplhhcVWpVWp,cplhhhhcVWpVWp,cplhhhhVZVZ,        & 
& cplhhHpcVWp,cplhhVZVZ,cplHpcHpcVWpVWp,cplHpcHpVZ,cplHpcHpVZVZ,cplHpcVWpVP,             & 
& cplHpcVWpVZ,dRho)

Call STUparameter(vSM,g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,MA0,MA02,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,cplG0hhVZ,       & 
& cplG0HpcVWp,cplG0G0cVWpVWp,cplG0G0VZVZ,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,             & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0HpcVWp,cplA0A0cVWpVWp,cplA0A0VZVZ,           & 
& cplH0HpcVWp,cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,            & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,              & 
& cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3, & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ,cplHpcVWpVZ,              & 
& cplcVWpVWpVZ,cplHpcHpVZVZ,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,             & 
& cplcFdFucVWpL,cplcFdFucVWpR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,   & 
& cplcgZgWpcVWp,cplcgWCgZcVWp,cplHpcHpcVWpVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,     & 
& cplcVWpcVWpVWpVWp3,cplcHpVWpVZ,cplcHpVPVWp,cplHpcHpVPVZ,cplcVWpVPVWpVZ1,               & 
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3,Spar,Tpar,Upar)

If (WriteParametersAtQ) Then 
scalein = SetRenormalizationScale(160._dp**2) 
Else 
scalein = SetRenormalizationScale(scale_save**2) 
End if 
mz2 = mzsave**2 
mz = mzsave 
End subroutine CalculateLowEnergyConstraints 
 
 
End Module LowEnergy_Inert 
