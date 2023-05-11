! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:25 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module LowEnergy_gumTHDMII 
Use Control 
Use Settings 
Use Couplings_gumTHDMII 
Use LoopCouplings_gumTHDMII 
Use LoopMasses_SM_HC 
Use LoopFunctions 
Use LoopMasses_gumTHDMII 
Use StandardModel 
Use RunSM_gumTHDMII
Use FlavorKit_LFV_gumTHDMII
Use FlavorKit_QFV_gumTHDMII
Use FlavorKit_Observables_gumTHDMII
Private::F1,F2,F3,F4,F3Gamma
!private variables
 

Contains


Subroutine Gminus2(Ifermion,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFeFvHmL,cplcFeFvHmR,cplHmcHmVP,a_mu)

Real(dp),Intent(in)  :: MAh(2),MAh2(2),MFe(3),MFe2(3),Mhh(2),Mhh2(2),MHm(2),MHm2(2)

Complex(dp),Intent(in)  :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),          & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),             & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplHmcHmVP(2,2)

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
Do i1= 2,2
  Do i2= 1,3
   i3 = i2
  If ((MAh2(i1).gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFeAhL(gt1,i2,i1)
coup1R = cplcFeFeAhR(gt1,i2,i1)
coup2L = cplcFeFeAhL(i3,gt2,i1)
coup2R = cplcFeFeAhR(i3,gt2,i1)
ratio = MAh2(i1)/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
a_mu = a_mu - chargefactor*(Real(coup1L*Conjg(coup1R),dp)*F3gamma(ratio)/MFe(i2)& 
      & - 2._dp*MFe(Ifermion)*(Abs(coup1L)**2 + Abs(coup1R)**2)*F2(ratio)/MFe2(i2)) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
Do i1= 1,3
  Do i2= 2,2
   i3 = i2
  If ((0._dp.gt.mz2).Or.(MHm2(i2).gt.mz2).Or.(MHm2(i3).gt.mz2)) Then
coup1L = cplcFeFvHmL(gt1,i1,i2)
coup1R = cplcFeFvHmR(gt1,i1,i2)
coup2L = cplcFvFecHmL(i1,gt2,i3)
coup2R = cplcFvFecHmR(i1,gt2,i3)
ratio = MHm2(i2)/0._dp
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
a_mu = a_mu - chargefactor*(2._dp*Real(coup1L*Conjg(coup1R),dp)*F4(ratio)/0._dp& 
      & +2._dp*MFe(Ifermion)*(Abs(coup1L)**2 + Abs(coup1R)**2)*F1(ratio)/0._dp) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
Do i1= 1,2
  Do i2= 1,3
   i3 = i2
  If ((Mhh2(i1).gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFehhL(gt1,i2,i1)
coup1R = cplcFeFehhR(gt1,i2,i1)
coup2L = cplcFeFehhL(i3,gt2,i1)
coup2R = cplcFeFehhR(i3,gt2,i1)
ratio = Mhh2(i1)/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
a_mu = a_mu - chargefactor*(Real(coup1L*Conjg(coup1R),dp)*F3gamma(ratio)/MFe(i2)& 
      & - 2._dp*MFe(Ifermion)*(Abs(coup1L)**2 + Abs(coup1R)**2)*F2(ratio)/MFe2(i2)) 
End if 
 
End if 
   End Do
  End Do


a_mu = a_mu*MFe(Ifermion)*oo16pi2 
Iname = Iname -1 
 
End Subroutine Gminus2 
 
 
Subroutine LeptonEDM(Ifermion,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,            & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHmcHmVP,            & 
& cplcVWmVPVWm,EDM)

Implicit None
Real(dp),Intent(in)  :: MAh(2),MAh2(2),MFe(3),MFe2(3),Mhh(2),Mhh2(2),MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2

Complex(dp),Intent(in)  :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),          & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecHmL(3,3,2),& 
& cplcFvFecHmR(3,3,2),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFeFvHmL(3,3,2),          & 
& cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplHmcHmVP(2,2),cplcVWmVPVWm

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
Do i1= 2,2
  Do i2= 1,3
   i3 = i2
  If ((MAh2(i1).gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFeAhL(gt1,i2,i1)
coup1R = cplcFeFeAhR(gt1,i2,i1)
coup2L = cplcFeFeAhL(i3,gt2,i1)
coup2R = cplcFeFeAhR(i3,gt2,i1)
!ratio = MFe2(i2)/MAh2(i1)
 !If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
!EDM = EDM -(-1)* chargefactor*Aimag(coup1R*Conjg(coup1L))*FeynFunctionA(ratio)*MFe(i2)/MAh2(i1) 
!End if 
 
ratio = MAh2(i1)/MFe2(i2)
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 0.5_dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*F3gamma(ratio)/MFe(i2)) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
Do i1= 1,3
  Do i2= 2,2
   i3 = i2
  If ((0._dp.gt.mz2).Or.(MHm2(i2).gt.mz2).Or.(MHm2(i3).gt.mz2)) Then
coup1L = cplcFeFvHmL(gt1,i1,i2)
coup1R = cplcFeFvHmR(gt1,i1,i2)
coup2L = cplcFvFecHmL(i1,gt2,i3)
coup2R = cplcFvFecHmR(i1,gt2,i3)
!ratio = 0._dp/MHm2(i2)
 !If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
!EDM = EDM +(-1)* chargefactor*Aimag(coup1L*Conjg(coup1R))*FeynFunctionB(ratio)*0._dp/MHm2(i2) 
!End if 
 
ratio = MHm2(i2)/0._dp
 chargefactor = chargefactor*(1._dp)
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - chargefactor*(Aimag(coup1L*Conjg(coup1R))*F4(ratio)/0._dp) 
End if 
 
End if 
   End Do
  End Do


chargefactor = 1 
Do i1= 1,3
  If ((0._dp.gt.mz2).Or.(MVWm2.gt.mz2).Or.(MVWm2.gt.mz2)) Then
coup1L = cplcFeFvVWmL(gt1,i1)
coup1R = cplcFeFvVWmR(gt1,i1)
coup2L = cplcFvFecVWmL(i1,gt2)
coup2R = cplcFvFecVWmR(i1,gt2)
ratio = MVWm2/0._dp
 chargefactor = chargefactor*(1._dp)
 ratio = 1._dp/ratio ! conventions in 1402.7065 are different 
 If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
EDM = EDM - 2._dp*chargefactor*(Aimag(coup1L*Conjg(coup1R))*gVVF(ratio)/0._dp) 
End if 
 
End if 
   End Do


chargefactor = 1 
Do i1= 1,2
  Do i2= 1,3
   i3 = i2
  If ((Mhh2(i1).gt.mz2).Or.(MFe2(i2).gt.mz2).Or.(MFe2(i3).gt.mz2)) Then
coup1L = cplcFeFehhL(gt1,i2,i1)
coup1R = cplcFeFehhR(gt1,i2,i1)
coup2L = cplcFeFehhL(i3,gt2,i1)
coup2R = cplcFeFehhR(i3,gt2,i1)
!ratio = MFe2(i2)/Mhh2(i1)
 !If ((ratio.eq.ratio).and.(ratio.lt.1.0E+30_dp).and.(ratio.gt.1.0E-30_dp)) Then 
!EDM = EDM -(-1)* chargefactor*Aimag(coup1R*Conjg(coup1L))*FeynFunctionA(ratio)*MFe(i2)/Mhh2(i1) 
!End if 
 
ratio = Mhh2(i1)/MFe2(i2)
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
 
 
Subroutine DeltaRho(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,            & 
& MVWm,MVWm2,MVZ,MVZ2,cplAhAhcVWmVWm,cplAhAhVZVZ,cplAhhhVZ,cplAhHmcVWm,cplcFdFdVZL,      & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgAgWmcVWm,         & 
& cplcgWmgWmVZ,cplcgWpCgAcVWm,cplcgWpCgWpCVZ,cplcgWpCgZcVWm,cplcgZgWmcVWm,               & 
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVPVPVWm1,              & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWm,cplcVWmVWmVZ,cplcVWmVWmVZVZ1,             & 
& cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplhhcVWmVWm,cplhhhhcVWmVWm,cplhhhhVZVZ,               & 
& cplhhHmcVWm,cplhhVZVZ,cplHmcHmcVWmVWm,cplHmcHmVZ,cplHmcHmVZVZ,cplHmcVWmVP,             & 
& cplHmcVWmVZ,rho)

Implicit None
Real(dp),Intent(in)  :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2

Complex(dp),Intent(in)  :: cplAhAhcVWmVWm(2,2),cplAhAhVZVZ(2,2),cplAhhhVZ(2,2),cplAhHmcVWm(2,2),cplcFdFdVZL(3,3),& 
& cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),& 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),               & 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWmcVWm,cplcgWmgWmVZ,cplcgWpCgAcVWm,           & 
& cplcgWpCgWpCVZ,cplcgWpCgZcVWm,cplcgZgWmcVWm,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,     & 
& cplcVWmcVWmVWmVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWm,       & 
& cplcVWmVWmVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplhhcVWmVWm(2),          & 
& cplhhhhcVWmVWm(2,2),cplhhhhVZVZ(2,2),cplhhHmcVWm(2,2),cplhhVZVZ(2),cplHmcHmcVWmVWm(2,2),& 
& cplHmcHmVZ(2,2),cplHmcHmVZVZ(2,2),cplHmcVWmVP(2),cplHmcVWmVZ(2)

Real(dp), Intent(out) :: rho 
Integer :: i1, i2, i3, kont 
Real(dp) ::  delta_rho, delta_rho0, Drho_top, mu_old 
Complex(dp) ::  dmW2, dmz2 
mu_old = SetRenormalizationScale(mZ2) 
 
Call Pi1LoopVZ(0._dp,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,           & 
& MHm,MHm2,MVWm,MVWm2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHmcHmVZVZ,    & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmZ2)

Call Pi1LoopVWm(0._dp,MHm,MHm2,MAh,MAh2,MFu,MFu2,MFd,MFd2,MFe,MFe2,Mhh,               & 
& Mhh2,MVWm,MVWm2,MVZ,MVZ2,cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,        & 
& cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,               & 
& cplhhHmcVWm,cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,            & 
& cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmVPVPVWm3,cplcVWmVPVPVWm1,         & 
& cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,              & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,dmW2)

Drho_top = 3*G_F*mf_u(3)**2*oosqrt2*oo8pi2 
 
mu_old = SetRenormalizationScale(mu_old) 
 
! Tree Level 
delta_rho0 =  0 
 
! 1-Loop Level 
delta_rho =  dmZ2/mz2 - dMW2/mW2 - drho_top 
 Rho= delta_rho + delta_rho0
End subroutine DeltaRho 
 
 
Subroutine STUparameter(vSM,g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,MAh,MAh2,MFd,               & 
& MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFdFdVPL,              & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcVWmVPVWm,cplHmcHmVPVP,cplcVWmVPVPVWm1,       & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,         & 
& cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,              & 
& cplhhhhVZVZ,cplHmcHmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,              & 
& cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,    & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcVWmVWm,cplAhAhcVWmVWm,    & 
& cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,& 
& cplcHmVWmVZ,cplcHmVPVWm,cplHmcHmVPVZ,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,  & 
& Spar,Tpar,Upar)

Implicit None
Real(dp),Intent(in)  :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2

Complex(dp),Intent(in)  :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3), & 
& cplcFuFuVPR(3,3),cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP(2,2),cplHmcVWmVP(2),           & 
& cplcVWmVPVWm,cplHmcHmVPVP(2,2),cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,        & 
& cplAhhhVZ(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),    & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgWmgWmVZ,      & 
& cplcgWpCgWpCVZ,cplhhVZVZ(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcVWmVWmVZ,               & 
& cplAhAhVZVZ(2,2),cplhhhhVZVZ(2,2),cplHmcHmVZVZ(2,2),cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,   & 
& cplcVWmVWmVZVZ3,cplAhHmcVWm(2,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFvFecVWmL(3,3),& 
& cplcFvFecVWmR(3,3),cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,          & 
& cplhhHmcVWm(2,2),cplhhcVWmVWm(2),cplAhAhcVWmVWm(2,2),cplhhhhcVWmVWm(2,2),              & 
& cplHmcHmcVWmVWm(2,2),cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,         & 
& cplcHmVWmVZ(2),cplcHmVPVWm(2),cplHmcHmVPVZ(2,2),cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,       & 
& cplcVWmVPVWmVZ3

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
 
LamSM = Mhh2(1)/vSM**2
 
Call OneLoop_Z_W_Gamma_SM(vSM,g1SM,g2SM,g3SM,LamSM,YuSM,YdSM,YeSM,kont, & 
 & PiZZ_SM,PiZZ_mz2_SM,PiWW_SM,PiWW_mw2_SM,PiZg_mz2_SM,Pigg_mz2_SM) 
Call Pi1LoopVZ(0._dp,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,           & 
& MHm,MHm2,MVWm,MVWm2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHmcHmVZVZ,    & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,PiZZ)

Call Pi1LoopVZ(MVZ2,Mhh,Mhh2,MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MVZ,MVZ2,            & 
& MHm,MHm2,MVWm,MVWm2,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,         & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHmcHmVZVZ,    & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,PiZZ_mz2)

Call Pi1LoopVWm(0._dp,MHm,MHm2,MAh,MAh2,MFu,MFu2,MFd,MFd2,MFe,MFe2,Mhh,               & 
& Mhh2,MVWm,MVWm2,MVZ,MVZ2,cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,        & 
& cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,               & 
& cplhhHmcVWm,cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,            & 
& cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmVPVPVWm3,cplcVWmVPVPVWm1,         & 
& cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,              & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,PiWW)

Call Pi1LoopVWm(MVWm2,MHm,MHm2,MAh,MAh2,MFu,MFu2,MFd,MFd2,MFe,MFe2,Mhh,               & 
& Mhh2,MVWm,MVWm2,MVZ,MVZ2,cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,        & 
& cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,               & 
& cplhhHmcVWm,cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,            & 
& cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmVPVPVWm3,cplcVWmVPVPVWm1,         & 
& cplcVWmVPVPVWm2,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmcVWmVWmVWm1,              & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,kont,PiWW_mw2)

Call Pi1LoopVPVZ(MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHm,MHm2,MVWm,MVWm2,cplcFdFdVPL,     & 
& cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,              & 
& cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,       & 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmVWmVZ,cplHmcHmVP,               & 
& cplHmcHmVPVZ,cplHmcHmVZ,cplHmcVWmVP,cplHmcVWmVZ,kont,PiZg_mz2)

Call Pi1LoopVP(MVZ2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MHm,MHm2,MVWm,MVWm2,cplcFdFdVPL,       & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcVWmVPVWm,cplHmcHmVPVP,cplcVWmVPVPVWm3,       & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,kont,Pigg_mz2)

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
 
 
Subroutine CalculateLowEnergyConstraints(g1input,g2input,g3input,lam5input,           & 
& lam1input,lam4input,lam3input,lam2input,Yuinput,Ydinput,Yeinput,m122input,             & 
& m112input,m222input,vdinput,vuinput,Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,             & 
& EDMtau,dRho,BrBsGamma,ratioBsGamma,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,            & 
& BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,     & 
& RK,RKSM,muEgamma,tauEgamma,tauMuGamma,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,         & 
& CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,BRtauToemumu,BRtauTomuee,BRtauToemumu2,          & 
& BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,BrhtoTauE,BrhtoTauMu,              & 
& DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,BrTautoEPi,BrTautoEEta,BrTautoEEtap,     & 
& BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,          & 
& BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,              & 
& BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu,              & 
& BrBtoKee,ratioBtoKee,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,     & 
& ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,             & 
& BrK0eMu,ratioK0eMu,DelMK,ratioDelMK,epsK,ratioepsK)

Real(dp),Intent(inout) :: g1input,g2input,g3input,vdinput,vuinput

Complex(dp),Intent(inout) :: lam5input,lam1input,lam4input,lam3input,lam2input,Yuinput(3,3),Ydinput(3,3),          & 
& Yeinput(3,3),m122input,m112input,m222input

Real(dp) :: MAh(2),MAh2(2),MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh(2),Mhh2(2),           & 
& MHm(2),MHm2(2),MVWm,MVWm2,MVZ,MVZ2,TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),               & 
& alphaH,betaH

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Real(dp) :: g1,g2,g3,vd,vu

Complex(dp) :: lam5,lam1,lam4,lam3,lam2,Yu(3,3),Yd(3,3),Ye(3,3),m122,m112,m222

Complex(dp) :: cplAhAhAh(2,2,2),cplAhAhcVWmVWm(2,2),cplAhAhhh(2,2,2),cplAhAhVZVZ(2,2),               & 
& cplAhcHmVWm(2,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),   & 
& cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),           & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFdFuVWmL(3,3),              & 
& cplcFdFuVWmR(3,3),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),            & 
& cplcFeFehhR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),& 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),             & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFvFecVWmL(3,3),           & 
& cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWmcVWm,cplcgWmgWmVP,       & 
& cplcgWmgWmVZ,cplcgWpCgAcVWm,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplcgWpCgZcVWm,              & 
& cplcgZgWmcVWm,cplcHmVPVWm(2),cplcHmVWmVZ(2),cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,     & 
& cplcVWmcVWmVWmVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWm,       & 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmVWmVZ,cplcVWmVWmVZVZ1,          & 
& cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplhhhhcVWmVWm(2,2),  & 
& cplhhhhhh(2,2,2),cplhhhhVZVZ(2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhVZVZ(2),     & 
& cplHmcHmcVWmVWm(2,2),cplHmcHmVP(2,2),cplHmcHmVPVP(2,2),cplHmcHmVPVZ(2,2),              & 
& cplHmcHmVZ(2,2),cplHmcHmVZVZ(2,2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplVGVGVG

Real(dp),Intent(out) :: Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,BrBsGamma,ratioBsGamma,             & 
& BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,     & 
& BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM,muEgamma,tauEgamma,tauMuGamma,         & 
& CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,         & 
& BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,     & 
& BrhtoMuE,BrhtoTauE,BrhtoTauMu,DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,           & 
& BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,            & 
& BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,   & 
& BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,            & 
& BrBtoSMuMu,ratioBtoSMuMu,BrBtoKee,ratioBtoKee,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,     & 
& ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,    & 
& ratioKltoPinunu,BrK0eMu,ratioK0eMu,DelMK,ratioDelMK,epsK,ratioepsK

Complex(dp) :: c7,c7p,c8,c8p 
Real(dp) :: ResultMuE(6), ResultTauMeson(3), ResultTemp(99) 
Real(dp) :: epsTree=1.0E-20_dp 
Complex(dp), Dimension(3,3) :: Yu_save, Yd_save, Ye_save, CKMsave 
Complex(dp) :: YuSM(3,3),YeSM(3,3),YdSM(3,3) 
Real(dp)::g1SM, g2SM, g3SM, vSM 
Real(dp) ::Qin,vev2,sinw2, mzsave, scalein, scale_save, gSM(11),Qinsave, maxdiff =0._dp 
Integer :: i1, i2, i3, gt1, gt2, gt3, gt4,iQTEST, iQFinal 
Integer :: IndexArray4(99,4), IndexArray3(99,3), IndexArray2(99,2)   
Complex(dp) :: TSOllddSLL(3,3,3,3),TSOllddSRR(3,3,3,3),TSOllddSRL(3,3,3,3),TSOllddSLR(3,3,3,3),      & 
& TSOllddVRR(3,3,3,3),TSOllddVLL(3,3,3,3),TSOllddVRL(3,3,3,3),TSOllddVLR(3,3,3,3),       & 
& TSOllddTLL(3,3,3,3),TSOllddTLR(3,3,3,3),TSOllddTRL(3,3,3,3),TSOllddTRR(3,3,3,3),       & 
& TVOllddSLL(3,3,3,3),TVOllddSRR(3,3,3,3),TVOllddSRL(3,3,3,3),TVOllddSLR(3,3,3,3),       & 
& TVOllddVRR(3,3,3,3),TVOllddVLL(3,3,3,3),TVOllddVRL(3,3,3,3),TVOllddVLR(3,3,3,3),       & 
& TVOllddTLL(3,3,3,3),TVOllddTLR(3,3,3,3),TVOllddTRL(3,3,3,3),TVOllddTRR(3,3,3,3),       & 
& TSOlluuSLL(3,3,3,3),TSOlluuSRR(3,3,3,3),TSOlluuSRL(3,3,3,3),TSOlluuSLR(3,3,3,3),       & 
& TSOlluuVRR(3,3,3,3),TSOlluuVLL(3,3,3,3),TSOlluuVRL(3,3,3,3),TSOlluuVLR(3,3,3,3),       & 
& TSOlluuTLL(3,3,3,3),TSOlluuTLR(3,3,3,3),TSOlluuTRL(3,3,3,3),TSOlluuTRR(3,3,3,3),       & 
& TVOlluuSLL(3,3,3,3),TVOlluuSRR(3,3,3,3),TVOlluuSRL(3,3,3,3),TVOlluuSLR(3,3,3,3),       & 
& TVOlluuVRR(3,3,3,3),TVOlluuVLL(3,3,3,3),TVOlluuVRL(3,3,3,3),TVOlluuVLR(3,3,3,3),       & 
& TVOlluuTLL(3,3,3,3),TVOlluuTLR(3,3,3,3),TVOlluuTRL(3,3,3,3),TVOlluuTRR(3,3,3,3),       & 
& TSO4lSLL(3,3,3,3),TSO4lSRR(3,3,3,3),TSO4lSRL(3,3,3,3),TSO4lSLR(3,3,3,3),               & 
& TSO4lVRR(3,3,3,3),TSO4lVLL(3,3,3,3),TSO4lVRL(3,3,3,3),TSO4lVLR(3,3,3,3),               & 
& TSO4lTLL(3,3,3,3),TSO4lTLR(3,3,3,3),TSO4lTRL(3,3,3,3),TSO4lTRR(3,3,3,3),               & 
& TVO4lSLL(3,3,3,3),TVO4lSRR(3,3,3,3),TVO4lSRL(3,3,3,3),TVO4lSLR(3,3,3,3),               & 
& TVO4lVRR(3,3,3,3),TVO4lVLL(3,3,3,3),TVO4lVRL(3,3,3,3),TVO4lVLR(3,3,3,3),               & 
& TVO4lTLL(3,3,3,3),TVO4lTLR(3,3,3,3),TVO4lTRL(3,3,3,3),TVO4lTRR(3,3,3,3),               & 
& TSO4lSLLcross(3,3,3,3),TSO4lSRRcross(3,3,3,3),TSO4lSRLcross(3,3,3,3),TSO4lSLRcross(3,3,3,3),& 
& TSO4lVRRcross(3,3,3,3),TSO4lVLLcross(3,3,3,3),TSO4lVRLcross(3,3,3,3),TSO4lVLRcross(3,3,3,3),& 
& TSO4lTLLcross(3,3,3,3),TSO4lTLRcross(3,3,3,3),TSO4lTRLcross(3,3,3,3),TSO4lTRRcross(3,3,3,3),& 
& TVO4lSLLcross(3,3,3,3),TVO4lSRRcross(3,3,3,3),TVO4lSRLcross(3,3,3,3),TVO4lSLRcross(3,3,3,3),& 
& TVO4lVRRcross(3,3,3,3),TVO4lVLLcross(3,3,3,3),TVO4lVRLcross(3,3,3,3),TVO4lVLRcross(3,3,3,3),& 
& TVO4lTLLcross(3,3,3,3),TVO4lTLRcross(3,3,3,3),TVO4lTRLcross(3,3,3,3),TVO4lTRRcross(3,3,3,3),& 
& BOllddSLL(3,3,3,3),BOllddSRR(3,3,3,3),BOllddSRL(3,3,3,3),BOllddSLR(3,3,3,3),           & 
& BOllddVRR(3,3,3,3),BOllddVLL(3,3,3,3),BOllddVRL(3,3,3,3),BOllddVLR(3,3,3,3),           & 
& BOllddTLL(3,3,3,3),BOllddTLR(3,3,3,3),BOllddTRL(3,3,3,3),BOllddTRR(3,3,3,3),           & 
& PSOllddSLL(3,3,3,3),PSOllddSRR(3,3,3,3),PSOllddSRL(3,3,3,3),PSOllddSLR(3,3,3,3),       & 
& PSOllddVRR(3,3,3,3),PSOllddVLL(3,3,3,3),PSOllddVRL(3,3,3,3),PSOllddVLR(3,3,3,3),       & 
& PSOllddTLL(3,3,3,3),PSOllddTLR(3,3,3,3),PSOllddTRL(3,3,3,3),PSOllddTRR(3,3,3,3),       & 
& PVOllddSLL(3,3,3,3),PVOllddSRR(3,3,3,3),PVOllddSRL(3,3,3,3),PVOllddSLR(3,3,3,3),       & 
& PVOllddVRR(3,3,3,3),PVOllddVLL(3,3,3,3),PVOllddVRL(3,3,3,3),PVOllddVLR(3,3,3,3),       & 
& PVOllddTLL(3,3,3,3),PVOllddTLR(3,3,3,3),PVOllddTRL(3,3,3,3),PVOllddTRR(3,3,3,3),       & 
& BOlluuSLL(3,3,3,3),BOlluuSRR(3,3,3,3),BOlluuSRL(3,3,3,3),BOlluuSLR(3,3,3,3),           & 
& BOlluuVRR(3,3,3,3),BOlluuVLL(3,3,3,3),BOlluuVRL(3,3,3,3),BOlluuVLR(3,3,3,3),           & 
& BOlluuTLL(3,3,3,3),BOlluuTLR(3,3,3,3),BOlluuTRL(3,3,3,3),BOlluuTRR(3,3,3,3),           & 
& PSOlluuSLL(3,3,3,3),PSOlluuSRR(3,3,3,3),PSOlluuSRL(3,3,3,3),PSOlluuSLR(3,3,3,3)

Complex(dp) :: PSOlluuVRR(3,3,3,3),PSOlluuVLL(3,3,3,3),PSOlluuVRL(3,3,3,3),PSOlluuVLR(3,3,3,3),       & 
& PSOlluuTLL(3,3,3,3),PSOlluuTLR(3,3,3,3),PSOlluuTRL(3,3,3,3),PSOlluuTRR(3,3,3,3),       & 
& PVOlluuSLL(3,3,3,3),PVOlluuSRR(3,3,3,3),PVOlluuSRL(3,3,3,3),PVOlluuSLR(3,3,3,3),       & 
& PVOlluuVRR(3,3,3,3),PVOlluuVLL(3,3,3,3),PVOlluuVRL(3,3,3,3),PVOlluuVLR(3,3,3,3),       & 
& PVOlluuTLL(3,3,3,3),PVOlluuTLR(3,3,3,3),PVOlluuTRL(3,3,3,3),PVOlluuTRR(3,3,3,3),       & 
& BO4lSLL(3,3,3,3),BO4lSRR(3,3,3,3),BO4lSRL(3,3,3,3),BO4lSLR(3,3,3,3),BO4lVRR(3,3,3,3),  & 
& BO4lVLL(3,3,3,3),BO4lVRL(3,3,3,3),BO4lVLR(3,3,3,3),BO4lTLL(3,3,3,3),BO4lTLR(3,3,3,3),  & 
& BO4lTRL(3,3,3,3),BO4lTRR(3,3,3,3),PSO4lSLL(3,3,3,3),PSO4lSRR(3,3,3,3),PSO4lSRL(3,3,3,3),& 
& PSO4lSLR(3,3,3,3),PSO4lVRR(3,3,3,3),PSO4lVLL(3,3,3,3),PSO4lVRL(3,3,3,3),               & 
& PSO4lVLR(3,3,3,3),PSO4lTLL(3,3,3,3),PSO4lTLR(3,3,3,3),PSO4lTRL(3,3,3,3),               & 
& PSO4lTRR(3,3,3,3),PVO4lSLL(3,3,3,3),PVO4lSRR(3,3,3,3),PVO4lSRL(3,3,3,3),               & 
& PVO4lSLR(3,3,3,3),PVO4lVRR(3,3,3,3),PVO4lVLL(3,3,3,3),PVO4lVRL(3,3,3,3),               & 
& PVO4lVLR(3,3,3,3),PVO4lTLL(3,3,3,3),PVO4lTLR(3,3,3,3),PVO4lTRL(3,3,3,3),               & 
& PVO4lTRR(3,3,3,3),BO4lSLLcross(3,3,3,3),BO4lSRRcross(3,3,3,3),BO4lSRLcross(3,3,3,3),   & 
& BO4lSLRcross(3,3,3,3),BO4lVRRcross(3,3,3,3),BO4lVLLcross(3,3,3,3),BO4lVRLcross(3,3,3,3),& 
& BO4lVLRcross(3,3,3,3),BO4lTLLcross(3,3,3,3),BO4lTLRcross(3,3,3,3),BO4lTRLcross(3,3,3,3),& 
& BO4lTRRcross(3,3,3,3),PSO4lSLLcross(3,3,3,3),PSO4lSRRcross(3,3,3,3),PSO4lSRLcross(3,3,3,3),& 
& PSO4lSLRcross(3,3,3,3),PSO4lVRRcross(3,3,3,3),PSO4lVLLcross(3,3,3,3),PSO4lVRLcross(3,3,3,3),& 
& PSO4lVLRcross(3,3,3,3),PSO4lTLLcross(3,3,3,3),PSO4lTLRcross(3,3,3,3),PSO4lTRLcross(3,3,3,3),& 
& PSO4lTRRcross(3,3,3,3),PVO4lSLLcross(3,3,3,3),PVO4lSRRcross(3,3,3,3),PVO4lSRLcross(3,3,3,3),& 
& PVO4lSLRcross(3,3,3,3),PVO4lVRRcross(3,3,3,3),PVO4lVLLcross(3,3,3,3),PVO4lVRLcross(3,3,3,3),& 
& PVO4lVLRcross(3,3,3,3),PVO4lTLLcross(3,3,3,3),PVO4lTLRcross(3,3,3,3),PVO4lTRLcross(3,3,3,3),& 
& PVO4lTRRcross(3,3,3,3),OA2lSL(3,3),OA2lSR(3,3),OA1L(3,3),OA1R(3,3),OH2lSL(3,3,2),      & 
& OH2lSR(3,3,2),OZ2lSL(3,3),OZ2lSR(3,3),OZ2lVL(3,3),OZ2lVR(3,3)

Complex(dp) :: TSOddllSLLSM(3,3,3,3),TSOddllSRRSM(3,3,3,3),TSOddllSRLSM(3,3,3,3),TSOddllSLRSM(3,3,3,3),& 
& TSOddllVRRSM(3,3,3,3),TSOddllVLLSM(3,3,3,3),TSOddllVRLSM(3,3,3,3),TSOddllVLRSM(3,3,3,3),& 
& TSOddllTLLSM(3,3,3,3),TSOddllTLRSM(3,3,3,3),TSOddllTRLSM(3,3,3,3),TSOddllTRRSM(3,3,3,3),& 
& TVOddllSLLSM(3,3,3,3),TVOddllSRRSM(3,3,3,3),TVOddllSRLSM(3,3,3,3),TVOddllSLRSM(3,3,3,3),& 
& TVOddllVRRSM(3,3,3,3),TVOddllVLLSM(3,3,3,3),TVOddllVRLSM(3,3,3,3),TVOddllVLRSM(3,3,3,3),& 
& TVOddllTLLSM(3,3,3,3),TVOddllTLRSM(3,3,3,3),TVOddllTRLSM(3,3,3,3),TVOddllTRRSM(3,3,3,3),& 
& TSOddvvVRRSM(3,3,3,3),TSOddvvVLLSM(3,3,3,3),TSOddvvVRLSM(3,3,3,3),TSOddvvVLRSM(3,3,3,3),& 
& TVOddvvVRRSM(3,3,3,3),TVOddvvVLLSM(3,3,3,3),TVOddvvVRLSM(3,3,3,3),TVOddvvVLRSM(3,3,3,3),& 
& TSO4dSLLSM(3,3,3,3),TSO4dSRRSM(3,3,3,3),TSO4dSRLSM(3,3,3,3),TSO4dSLRSM(3,3,3,3),       & 
& TSO4dVRRSM(3,3,3,3),TSO4dVLLSM(3,3,3,3),TSO4dVRLSM(3,3,3,3),TSO4dVLRSM(3,3,3,3),       & 
& TSO4dTLLSM(3,3,3,3),TSO4dTLRSM(3,3,3,3),TSO4dTRLSM(3,3,3,3),TSO4dTRRSM(3,3,3,3),       & 
& TVO4dSLLSM(3,3,3,3),TVO4dSRRSM(3,3,3,3),TVO4dSRLSM(3,3,3,3),TVO4dSLRSM(3,3,3,3),       & 
& TVO4dVRRSM(3,3,3,3),TVO4dVLLSM(3,3,3,3),TVO4dVRLSM(3,3,3,3),TVO4dVLRSM(3,3,3,3),       & 
& TVO4dTLLSM(3,3,3,3),TVO4dTLRSM(3,3,3,3),TVO4dTRLSM(3,3,3,3),TVO4dTRRSM(3,3,3,3),       & 
& TSOdulvSLLSM(3,3,3,3),TSOdulvSRRSM(3,3,3,3),TSOdulvSRLSM(3,3,3,3),TSOdulvSLRSM(3,3,3,3),& 
& TSOdulvVRRSM(3,3,3,3),TSOdulvVLLSM(3,3,3,3),TSOdulvVRLSM(3,3,3,3),TSOdulvVLRSM(3,3,3,3),& 
& TVOdulvSLLSM(3,3,3,3),TVOdulvSRRSM(3,3,3,3),TVOdulvSRLSM(3,3,3,3),TVOdulvSLRSM(3,3,3,3),& 
& TVOdulvVRRSM(3,3,3,3),TVOdulvVLLSM(3,3,3,3),TVOdulvVRLSM(3,3,3,3),TVOdulvVLRSM(3,3,3,3),& 
& BOddllSLLSM(3,3,3,3),BOddllSRRSM(3,3,3,3),BOddllSRLSM(3,3,3,3),BOddllSLRSM(3,3,3,3),   & 
& BOddllVRRSM(3,3,3,3),BOddllVLLSM(3,3,3,3),BOddllVRLSM(3,3,3,3),BOddllVLRSM(3,3,3,3),   & 
& BOddllTLLSM(3,3,3,3),BOddllTLRSM(3,3,3,3),BOddllTRLSM(3,3,3,3),BOddllTRRSM(3,3,3,3),   & 
& PSOddllSLLSM(3,3,3,3),PSOddllSRRSM(3,3,3,3),PSOddllSRLSM(3,3,3,3),PSOddllSLRSM(3,3,3,3),& 
& PSOddllVRRSM(3,3,3,3),PSOddllVLLSM(3,3,3,3),PSOddllVRLSM(3,3,3,3),PSOddllVLRSM(3,3,3,3),& 
& PSOddllTLLSM(3,3,3,3),PSOddllTLRSM(3,3,3,3),PSOddllTRLSM(3,3,3,3),PSOddllTRRSM(3,3,3,3),& 
& PVOddllSLLSM(3,3,3,3),PVOddllSRRSM(3,3,3,3),PVOddllSRLSM(3,3,3,3),PVOddllSLRSM(3,3,3,3),& 
& PVOddllVRRSM(3,3,3,3),PVOddllVLLSM(3,3,3,3),PVOddllVRLSM(3,3,3,3),PVOddllVLRSM(3,3,3,3),& 
& PVOddllTLLSM(3,3,3,3),PVOddllTLRSM(3,3,3,3),PVOddllTRLSM(3,3,3,3),PVOddllTRRSM(3,3,3,3),& 
& BOddvvVRRSM(3,3,3,3),BOddvvVLLSM(3,3,3,3),BOddvvVRLSM(3,3,3,3),BOddvvVLRSM(3,3,3,3),   & 
& PSOddvvVRRSM(3,3,3,3),PSOddvvVLLSM(3,3,3,3),PSOddvvVRLSM(3,3,3,3),PSOddvvVLRSM(3,3,3,3),& 
& PVOddvvVRRSM(3,3,3,3),PVOddvvVLLSM(3,3,3,3),PVOddvvVRLSM(3,3,3,3),PVOddvvVLRSM(3,3,3,3),& 
& BO4dSLLSM(3,3,3,3),BO4dSRRSM(3,3,3,3),BO4dSRLSM(3,3,3,3),BO4dSLRSM(3,3,3,3),           & 
& BO4dVRRSM(3,3,3,3),BO4dVLLSM(3,3,3,3),BO4dVRLSM(3,3,3,3),BO4dVLRSM(3,3,3,3),           & 
& BO4dTLLSM(3,3,3,3),BO4dTLRSM(3,3,3,3),BO4dTRLSM(3,3,3,3),BO4dTRRSM(3,3,3,3),           & 
& OAh2qSLSM(3,3,2),OAh2qSRSM(3,3,2),OA2qSLSM(3,3),OA2qSRSM(3,3),OA2qVLSM(3,3),           & 
& OA2qVRSM(3,3),OG2qSLSM(3,3),OG2qSRSM(3,3),OH2qSLSM(3,3,2),OH2qSRSM(3,3,2)

Complex(dp) :: TSOddllSLL(3,3,3,3),TSOddllSRR(3,3,3,3),TSOddllSRL(3,3,3,3),TSOddllSLR(3,3,3,3),      & 
& TSOddllVRR(3,3,3,3),TSOddllVLL(3,3,3,3),TSOddllVRL(3,3,3,3),TSOddllVLR(3,3,3,3),       & 
& TSOddllTLL(3,3,3,3),TSOddllTLR(3,3,3,3),TSOddllTRL(3,3,3,3),TSOddllTRR(3,3,3,3),       & 
& TVOddllSLL(3,3,3,3),TVOddllSRR(3,3,3,3),TVOddllSRL(3,3,3,3),TVOddllSLR(3,3,3,3),       & 
& TVOddllVRR(3,3,3,3),TVOddllVLL(3,3,3,3),TVOddllVRL(3,3,3,3),TVOddllVLR(3,3,3,3),       & 
& TVOddllTLL(3,3,3,3),TVOddllTLR(3,3,3,3),TVOddllTRL(3,3,3,3),TVOddllTRR(3,3,3,3),       & 
& TSOddvvVRR(3,3,3,3),TSOddvvVLL(3,3,3,3),TSOddvvVRL(3,3,3,3),TSOddvvVLR(3,3,3,3),       & 
& TVOddvvVRR(3,3,3,3),TVOddvvVLL(3,3,3,3),TVOddvvVRL(3,3,3,3),TVOddvvVLR(3,3,3,3),       & 
& TSO4dSLL(3,3,3,3),TSO4dSRR(3,3,3,3),TSO4dSRL(3,3,3,3),TSO4dSLR(3,3,3,3),               & 
& TSO4dVRR(3,3,3,3),TSO4dVLL(3,3,3,3),TSO4dVRL(3,3,3,3),TSO4dVLR(3,3,3,3),               & 
& TSO4dTLL(3,3,3,3),TSO4dTLR(3,3,3,3),TSO4dTRL(3,3,3,3),TSO4dTRR(3,3,3,3),               & 
& TVO4dSLL(3,3,3,3),TVO4dSRR(3,3,3,3),TVO4dSRL(3,3,3,3),TVO4dSLR(3,3,3,3),               & 
& TVO4dVRR(3,3,3,3),TVO4dVLL(3,3,3,3),TVO4dVRL(3,3,3,3),TVO4dVLR(3,3,3,3),               & 
& TVO4dTLL(3,3,3,3),TVO4dTLR(3,3,3,3),TVO4dTRL(3,3,3,3),TVO4dTRR(3,3,3,3),               & 
& TSOdulvSLL(3,3,3,3),TSOdulvSRR(3,3,3,3),TSOdulvSRL(3,3,3,3),TSOdulvSLR(3,3,3,3),       & 
& TSOdulvVRR(3,3,3,3),TSOdulvVLL(3,3,3,3),TSOdulvVRL(3,3,3,3),TSOdulvVLR(3,3,3,3),       & 
& TVOdulvSLL(3,3,3,3),TVOdulvSRR(3,3,3,3),TVOdulvSRL(3,3,3,3),TVOdulvSLR(3,3,3,3),       & 
& TVOdulvVRR(3,3,3,3),TVOdulvVLL(3,3,3,3),TVOdulvVRL(3,3,3,3),TVOdulvVLR(3,3,3,3),       & 
& BOddllSLL(3,3,3,3),BOddllSRR(3,3,3,3),BOddllSRL(3,3,3,3),BOddllSLR(3,3,3,3),           & 
& BOddllVRR(3,3,3,3),BOddllVLL(3,3,3,3),BOddllVRL(3,3,3,3),BOddllVLR(3,3,3,3),           & 
& BOddllTLL(3,3,3,3),BOddllTLR(3,3,3,3),BOddllTRL(3,3,3,3),BOddllTRR(3,3,3,3),           & 
& PSOddllSLL(3,3,3,3),PSOddllSRR(3,3,3,3),PSOddllSRL(3,3,3,3),PSOddllSLR(3,3,3,3),       & 
& PSOddllVRR(3,3,3,3),PSOddllVLL(3,3,3,3),PSOddllVRL(3,3,3,3),PSOddllVLR(3,3,3,3),       & 
& PSOddllTLL(3,3,3,3),PSOddllTLR(3,3,3,3),PSOddllTRL(3,3,3,3),PSOddllTRR(3,3,3,3),       & 
& PVOddllSLL(3,3,3,3),PVOddllSRR(3,3,3,3),PVOddllSRL(3,3,3,3),PVOddllSLR(3,3,3,3),       & 
& PVOddllVRR(3,3,3,3),PVOddllVLL(3,3,3,3),PVOddllVRL(3,3,3,3),PVOddllVLR(3,3,3,3),       & 
& PVOddllTLL(3,3,3,3),PVOddllTLR(3,3,3,3),PVOddllTRL(3,3,3,3),PVOddllTRR(3,3,3,3),       & 
& BOddvvVRR(3,3,3,3),BOddvvVLL(3,3,3,3),BOddvvVRL(3,3,3,3),BOddvvVLR(3,3,3,3),           & 
& PSOddvvVRR(3,3,3,3),PSOddvvVLL(3,3,3,3),PSOddvvVRL(3,3,3,3),PSOddvvVLR(3,3,3,3),       & 
& PVOddvvVRR(3,3,3,3),PVOddvvVLL(3,3,3,3),PVOddvvVRL(3,3,3,3),PVOddvvVLR(3,3,3,3),       & 
& BO4dSLL(3,3,3,3),BO4dSRR(3,3,3,3),BO4dSRL(3,3,3,3),BO4dSLR(3,3,3,3),BO4dVRR(3,3,3,3),  & 
& BO4dVLL(3,3,3,3),BO4dVRL(3,3,3,3),BO4dVLR(3,3,3,3),BO4dTLL(3,3,3,3),BO4dTLR(3,3,3,3),  & 
& BO4dTRL(3,3,3,3),BO4dTRR(3,3,3,3),OAh2qSL(3,3,2),OAh2qSR(3,3,2),OA2qSL(3,3),           & 
& OA2qSR(3,3),OA2qVL(3,3),OA2qVR(3,3),OG2qSL(3,3),OG2qSR(3,3),OH2qSL(3,3,2),             & 
& OH2qSR(3,3,2)

Complex(dp) :: TSOllddSLLcheck(3,3,3,3),TSOllddSRRcheck(3,3,3,3),TSOllddSRLcheck(3,3,3,3),           & 
& TSOllddSLRcheck(3,3,3,3),TSOllddVRRcheck(3,3,3,3),TSOllddVLLcheck(3,3,3,3),            & 
& TSOllddVRLcheck(3,3,3,3),TSOllddVLRcheck(3,3,3,3),TSOllddTLLcheck(3,3,3,3),            & 
& TSOllddTLRcheck(3,3,3,3),TSOllddTRLcheck(3,3,3,3),TSOllddTRRcheck(3,3,3,3),            & 
& TVOllddSLLcheck(3,3,3,3),TVOllddSRRcheck(3,3,3,3),TVOllddSRLcheck(3,3,3,3),            & 
& TVOllddSLRcheck(3,3,3,3),TVOllddVRRcheck(3,3,3,3),TVOllddVLLcheck(3,3,3,3),            & 
& TVOllddVRLcheck(3,3,3,3),TVOllddVLRcheck(3,3,3,3),TVOllddTLLcheck(3,3,3,3),            & 
& TVOllddTLRcheck(3,3,3,3),TVOllddTRLcheck(3,3,3,3),TVOllddTRRcheck(3,3,3,3),            & 
& TSOlluuSLLcheck(3,3,3,3),TSOlluuSRRcheck(3,3,3,3),TSOlluuSRLcheck(3,3,3,3),            & 
& TSOlluuSLRcheck(3,3,3,3),TSOlluuVRRcheck(3,3,3,3),TSOlluuVLLcheck(3,3,3,3),            & 
& TSOlluuVRLcheck(3,3,3,3),TSOlluuVLRcheck(3,3,3,3),TSOlluuTLLcheck(3,3,3,3),            & 
& TSOlluuTLRcheck(3,3,3,3),TSOlluuTRLcheck(3,3,3,3),TSOlluuTRRcheck(3,3,3,3),            & 
& TVOlluuSLLcheck(3,3,3,3),TVOlluuSRRcheck(3,3,3,3),TVOlluuSRLcheck(3,3,3,3),            & 
& TVOlluuSLRcheck(3,3,3,3),TVOlluuVRRcheck(3,3,3,3),TVOlluuVLLcheck(3,3,3,3),            & 
& TVOlluuVRLcheck(3,3,3,3),TVOlluuVLRcheck(3,3,3,3),TVOlluuTLLcheck(3,3,3,3),            & 
& TVOlluuTLRcheck(3,3,3,3),TVOlluuTRLcheck(3,3,3,3),TVOlluuTRRcheck(3,3,3,3),            & 
& TSO4lSLLcheck(3,3,3,3),TSO4lSRRcheck(3,3,3,3),TSO4lSRLcheck(3,3,3,3),TSO4lSLRcheck(3,3,3,3),& 
& TSO4lVRRcheck(3,3,3,3),TSO4lVLLcheck(3,3,3,3),TSO4lVRLcheck(3,3,3,3),TSO4lVLRcheck(3,3,3,3),& 
& TSO4lTLLcheck(3,3,3,3),TSO4lTLRcheck(3,3,3,3),TSO4lTRLcheck(3,3,3,3),TSO4lTRRcheck(3,3,3,3),& 
& TVO4lSLLcheck(3,3,3,3),TVO4lSRRcheck(3,3,3,3),TVO4lSRLcheck(3,3,3,3),TVO4lSLRcheck(3,3,3,3),& 
& TVO4lVRRcheck(3,3,3,3),TVO4lVLLcheck(3,3,3,3),TVO4lVRLcheck(3,3,3,3),TVO4lVLRcheck(3,3,3,3),& 
& TVO4lTLLcheck(3,3,3,3),TVO4lTLRcheck(3,3,3,3),TVO4lTRLcheck(3,3,3,3),TVO4lTRRcheck(3,3,3,3),& 
& TSO4lSLLcrosscheck(3,3,3,3),TSO4lSRRcrosscheck(3,3,3,3),TSO4lSRLcrosscheck(3,3,3,3),   & 
& TSO4lSLRcrosscheck(3,3,3,3),TSO4lVRRcrosscheck(3,3,3,3),TSO4lVLLcrosscheck(3,3,3,3),   & 
& TSO4lVRLcrosscheck(3,3,3,3),TSO4lVLRcrosscheck(3,3,3,3),TSO4lTLLcrosscheck(3,3,3,3),   & 
& TSO4lTLRcrosscheck(3,3,3,3),TSO4lTRLcrosscheck(3,3,3,3),TSO4lTRRcrosscheck(3,3,3,3),   & 
& TVO4lSLLcrosscheck(3,3,3,3),TVO4lSRRcrosscheck(3,3,3,3),TVO4lSRLcrosscheck(3,3,3,3),   & 
& TVO4lSLRcrosscheck(3,3,3,3),TVO4lVRRcrosscheck(3,3,3,3),TVO4lVLLcrosscheck(3,3,3,3),   & 
& TVO4lVRLcrosscheck(3,3,3,3),TVO4lVLRcrosscheck(3,3,3,3),TVO4lTLLcrosscheck(3,3,3,3),   & 
& TVO4lTLRcrosscheck(3,3,3,3),TVO4lTRLcrosscheck(3,3,3,3),TVO4lTRRcrosscheck(3,3,3,3),   & 
& BOllddSLLcheck(3,3,3,3),BOllddSRRcheck(3,3,3,3),BOllddSRLcheck(3,3,3,3),               & 
& BOllddSLRcheck(3,3,3,3),BOllddVRRcheck(3,3,3,3),BOllddVLLcheck(3,3,3,3),               & 
& BOllddVRLcheck(3,3,3,3),BOllddVLRcheck(3,3,3,3),BOllddTLLcheck(3,3,3,3),               & 
& BOllddTLRcheck(3,3,3,3),BOllddTRLcheck(3,3,3,3),BOllddTRRcheck(3,3,3,3),               & 
& PSOllddSLLcheck(3,3,3,3),PSOllddSRRcheck(3,3,3,3),PSOllddSRLcheck(3,3,3,3),            & 
& PSOllddSLRcheck(3,3,3,3),PSOllddVRRcheck(3,3,3,3),PSOllddVLLcheck(3,3,3,3),            & 
& PSOllddVRLcheck(3,3,3,3),PSOllddVLRcheck(3,3,3,3),PSOllddTLLcheck(3,3,3,3)

Complex(dp) :: PSOllddTLRcheck(3,3,3,3),PSOllddTRLcheck(3,3,3,3),PSOllddTRRcheck(3,3,3,3),            & 
& PVOllddSLLcheck(3,3,3,3),PVOllddSRRcheck(3,3,3,3),PVOllddSRLcheck(3,3,3,3),            & 
& PVOllddSLRcheck(3,3,3,3),PVOllddVRRcheck(3,3,3,3),PVOllddVLLcheck(3,3,3,3),            & 
& PVOllddVRLcheck(3,3,3,3),PVOllddVLRcheck(3,3,3,3),PVOllddTLLcheck(3,3,3,3),            & 
& PVOllddTLRcheck(3,3,3,3),PVOllddTRLcheck(3,3,3,3),PVOllddTRRcheck(3,3,3,3),            & 
& BOlluuSLLcheck(3,3,3,3),BOlluuSRRcheck(3,3,3,3),BOlluuSRLcheck(3,3,3,3),               & 
& BOlluuSLRcheck(3,3,3,3),BOlluuVRRcheck(3,3,3,3),BOlluuVLLcheck(3,3,3,3),               & 
& BOlluuVRLcheck(3,3,3,3),BOlluuVLRcheck(3,3,3,3),BOlluuTLLcheck(3,3,3,3),               & 
& BOlluuTLRcheck(3,3,3,3),BOlluuTRLcheck(3,3,3,3),BOlluuTRRcheck(3,3,3,3),               & 
& PSOlluuSLLcheck(3,3,3,3),PSOlluuSRRcheck(3,3,3,3),PSOlluuSRLcheck(3,3,3,3),            & 
& PSOlluuSLRcheck(3,3,3,3),PSOlluuVRRcheck(3,3,3,3),PSOlluuVLLcheck(3,3,3,3),            & 
& PSOlluuVRLcheck(3,3,3,3),PSOlluuVLRcheck(3,3,3,3),PSOlluuTLLcheck(3,3,3,3),            & 
& PSOlluuTLRcheck(3,3,3,3),PSOlluuTRLcheck(3,3,3,3),PSOlluuTRRcheck(3,3,3,3),            & 
& PVOlluuSLLcheck(3,3,3,3),PVOlluuSRRcheck(3,3,3,3),PVOlluuSRLcheck(3,3,3,3),            & 
& PVOlluuSLRcheck(3,3,3,3),PVOlluuVRRcheck(3,3,3,3),PVOlluuVLLcheck(3,3,3,3),            & 
& PVOlluuVRLcheck(3,3,3,3),PVOlluuVLRcheck(3,3,3,3),PVOlluuTLLcheck(3,3,3,3),            & 
& PVOlluuTLRcheck(3,3,3,3),PVOlluuTRLcheck(3,3,3,3),PVOlluuTRRcheck(3,3,3,3),            & 
& BO4lSLLcheck(3,3,3,3),BO4lSRRcheck(3,3,3,3),BO4lSRLcheck(3,3,3,3),BO4lSLRcheck(3,3,3,3),& 
& BO4lVRRcheck(3,3,3,3),BO4lVLLcheck(3,3,3,3),BO4lVRLcheck(3,3,3,3),BO4lVLRcheck(3,3,3,3),& 
& BO4lTLLcheck(3,3,3,3),BO4lTLRcheck(3,3,3,3),BO4lTRLcheck(3,3,3,3),BO4lTRRcheck(3,3,3,3),& 
& PSO4lSLLcheck(3,3,3,3),PSO4lSRRcheck(3,3,3,3),PSO4lSRLcheck(3,3,3,3),PSO4lSLRcheck(3,3,3,3),& 
& PSO4lVRRcheck(3,3,3,3),PSO4lVLLcheck(3,3,3,3),PSO4lVRLcheck(3,3,3,3),PSO4lVLRcheck(3,3,3,3),& 
& PSO4lTLLcheck(3,3,3,3),PSO4lTLRcheck(3,3,3,3),PSO4lTRLcheck(3,3,3,3),PSO4lTRRcheck(3,3,3,3),& 
& PVO4lSLLcheck(3,3,3,3),PVO4lSRRcheck(3,3,3,3),PVO4lSRLcheck(3,3,3,3),PVO4lSLRcheck(3,3,3,3),& 
& PVO4lVRRcheck(3,3,3,3),PVO4lVLLcheck(3,3,3,3),PVO4lVRLcheck(3,3,3,3),PVO4lVLRcheck(3,3,3,3),& 
& PVO4lTLLcheck(3,3,3,3),PVO4lTLRcheck(3,3,3,3),PVO4lTRLcheck(3,3,3,3),PVO4lTRRcheck(3,3,3,3),& 
& BO4lSLLcrosscheck(3,3,3,3),BO4lSRRcrosscheck(3,3,3,3),BO4lSRLcrosscheck(3,3,3,3),      & 
& BO4lSLRcrosscheck(3,3,3,3),BO4lVRRcrosscheck(3,3,3,3),BO4lVLLcrosscheck(3,3,3,3),      & 
& BO4lVRLcrosscheck(3,3,3,3),BO4lVLRcrosscheck(3,3,3,3),BO4lTLLcrosscheck(3,3,3,3),      & 
& BO4lTLRcrosscheck(3,3,3,3),BO4lTRLcrosscheck(3,3,3,3),BO4lTRRcrosscheck(3,3,3,3),      & 
& PSO4lSLLcrosscheck(3,3,3,3),PSO4lSRRcrosscheck(3,3,3,3),PSO4lSRLcrosscheck(3,3,3,3),   & 
& PSO4lSLRcrosscheck(3,3,3,3),PSO4lVRRcrosscheck(3,3,3,3),PSO4lVLLcrosscheck(3,3,3,3),   & 
& PSO4lVRLcrosscheck(3,3,3,3),PSO4lVLRcrosscheck(3,3,3,3),PSO4lTLLcrosscheck(3,3,3,3),   & 
& PSO4lTLRcrosscheck(3,3,3,3),PSO4lTRLcrosscheck(3,3,3,3),PSO4lTRRcrosscheck(3,3,3,3),   & 
& PVO4lSLLcrosscheck(3,3,3,3),PVO4lSRRcrosscheck(3,3,3,3),PVO4lSRLcrosscheck(3,3,3,3),   & 
& PVO4lSLRcrosscheck(3,3,3,3),PVO4lVRRcrosscheck(3,3,3,3),PVO4lVLLcrosscheck(3,3,3,3),   & 
& PVO4lVRLcrosscheck(3,3,3,3),PVO4lVLRcrosscheck(3,3,3,3),PVO4lTLLcrosscheck(3,3,3,3)

Complex(dp) :: PVO4lTLRcrosscheck(3,3,3,3),PVO4lTRLcrosscheck(3,3,3,3),PVO4lTRRcrosscheck(3,3,3,3),   & 
& OA2lSLcheck(3,3),OA2lSRcheck(3,3),OA1Lcheck(3,3),OA1Rcheck(3,3),OH2lSLcheck(3,3,2),    & 
& OH2lSRcheck(3,3,2),OZ2lSLcheck(3,3),OZ2lSRcheck(3,3),OZ2lVLcheck(3,3),OZ2lVRcheck(3,3)

Complex(dp) :: TSOddllSLLcheck(3,3,3,3),TSOddllSRRcheck(3,3,3,3),TSOddllSRLcheck(3,3,3,3),           & 
& TSOddllSLRcheck(3,3,3,3),TSOddllVRRcheck(3,3,3,3),TSOddllVLLcheck(3,3,3,3),            & 
& TSOddllVRLcheck(3,3,3,3),TSOddllVLRcheck(3,3,3,3),TSOddllTLLcheck(3,3,3,3),            & 
& TSOddllTLRcheck(3,3,3,3),TSOddllTRLcheck(3,3,3,3),TSOddllTRRcheck(3,3,3,3),            & 
& TVOddllSLLcheck(3,3,3,3),TVOddllSRRcheck(3,3,3,3),TVOddllSRLcheck(3,3,3,3),            & 
& TVOddllSLRcheck(3,3,3,3),TVOddllVRRcheck(3,3,3,3),TVOddllVLLcheck(3,3,3,3),            & 
& TVOddllVRLcheck(3,3,3,3),TVOddllVLRcheck(3,3,3,3),TVOddllTLLcheck(3,3,3,3),            & 
& TVOddllTLRcheck(3,3,3,3),TVOddllTRLcheck(3,3,3,3),TVOddllTRRcheck(3,3,3,3),            & 
& TSOddvvVRRcheck(3,3,3,3),TSOddvvVLLcheck(3,3,3,3),TSOddvvVRLcheck(3,3,3,3),            & 
& TSOddvvVLRcheck(3,3,3,3),TVOddvvVRRcheck(3,3,3,3),TVOddvvVLLcheck(3,3,3,3),            & 
& TVOddvvVRLcheck(3,3,3,3),TVOddvvVLRcheck(3,3,3,3),TSO4dSLLcheck(3,3,3,3),              & 
& TSO4dSRRcheck(3,3,3,3),TSO4dSRLcheck(3,3,3,3),TSO4dSLRcheck(3,3,3,3),TSO4dVRRcheck(3,3,3,3),& 
& TSO4dVLLcheck(3,3,3,3),TSO4dVRLcheck(3,3,3,3),TSO4dVLRcheck(3,3,3,3),TSO4dTLLcheck(3,3,3,3),& 
& TSO4dTLRcheck(3,3,3,3),TSO4dTRLcheck(3,3,3,3),TSO4dTRRcheck(3,3,3,3),TVO4dSLLcheck(3,3,3,3),& 
& TVO4dSRRcheck(3,3,3,3),TVO4dSRLcheck(3,3,3,3),TVO4dSLRcheck(3,3,3,3),TVO4dVRRcheck(3,3,3,3),& 
& TVO4dVLLcheck(3,3,3,3),TVO4dVRLcheck(3,3,3,3),TVO4dVLRcheck(3,3,3,3),TVO4dTLLcheck(3,3,3,3),& 
& TVO4dTLRcheck(3,3,3,3),TVO4dTRLcheck(3,3,3,3),TVO4dTRRcheck(3,3,3,3),TSOdulvSLLcheck(3,3,3,3),& 
& TSOdulvSRRcheck(3,3,3,3),TSOdulvSRLcheck(3,3,3,3),TSOdulvSLRcheck(3,3,3,3),            & 
& TSOdulvVRRcheck(3,3,3,3),TSOdulvVLLcheck(3,3,3,3),TSOdulvVRLcheck(3,3,3,3),            & 
& TSOdulvVLRcheck(3,3,3,3),TVOdulvSLLcheck(3,3,3,3),TVOdulvSRRcheck(3,3,3,3),            & 
& TVOdulvSRLcheck(3,3,3,3),TVOdulvSLRcheck(3,3,3,3),TVOdulvVRRcheck(3,3,3,3),            & 
& TVOdulvVLLcheck(3,3,3,3),TVOdulvVRLcheck(3,3,3,3),TVOdulvVLRcheck(3,3,3,3),            & 
& BOddllSLLcheck(3,3,3,3),BOddllSRRcheck(3,3,3,3),BOddllSRLcheck(3,3,3,3),               & 
& BOddllSLRcheck(3,3,3,3),BOddllVRRcheck(3,3,3,3),BOddllVLLcheck(3,3,3,3),               & 
& BOddllVRLcheck(3,3,3,3),BOddllVLRcheck(3,3,3,3),BOddllTLLcheck(3,3,3,3),               & 
& BOddllTLRcheck(3,3,3,3),BOddllTRLcheck(3,3,3,3),BOddllTRRcheck(3,3,3,3),               & 
& PSOddllSLLcheck(3,3,3,3),PSOddllSRRcheck(3,3,3,3),PSOddllSRLcheck(3,3,3,3),            & 
& PSOddllSLRcheck(3,3,3,3),PSOddllVRRcheck(3,3,3,3),PSOddllVLLcheck(3,3,3,3),            & 
& PSOddllVRLcheck(3,3,3,3),PSOddllVLRcheck(3,3,3,3),PSOddllTLLcheck(3,3,3,3),            & 
& PSOddllTLRcheck(3,3,3,3),PSOddllTRLcheck(3,3,3,3),PSOddllTRRcheck(3,3,3,3),            & 
& PVOddllSLLcheck(3,3,3,3),PVOddllSRRcheck(3,3,3,3),PVOddllSRLcheck(3,3,3,3),            & 
& PVOddllSLRcheck(3,3,3,3),PVOddllVRRcheck(3,3,3,3),PVOddllVLLcheck(3,3,3,3),            & 
& PVOddllVRLcheck(3,3,3,3),PVOddllVLRcheck(3,3,3,3),PVOddllTLLcheck(3,3,3,3),            & 
& PVOddllTLRcheck(3,3,3,3),PVOddllTRLcheck(3,3,3,3),PVOddllTRRcheck(3,3,3,3),            & 
& BOddvvVRRcheck(3,3,3,3),BOddvvVLLcheck(3,3,3,3),BOddvvVRLcheck(3,3,3,3),               & 
& BOddvvVLRcheck(3,3,3,3),PSOddvvVRRcheck(3,3,3,3),PSOddvvVLLcheck(3,3,3,3),             & 
& PSOddvvVRLcheck(3,3,3,3),PSOddvvVLRcheck(3,3,3,3),PVOddvvVRRcheck(3,3,3,3)

Complex(dp) :: PVOddvvVLLcheck(3,3,3,3),PVOddvvVRLcheck(3,3,3,3),PVOddvvVLRcheck(3,3,3,3),            & 
& BO4dSLLcheck(3,3,3,3),BO4dSRRcheck(3,3,3,3),BO4dSRLcheck(3,3,3,3),BO4dSLRcheck(3,3,3,3),& 
& BO4dVRRcheck(3,3,3,3),BO4dVLLcheck(3,3,3,3),BO4dVRLcheck(3,3,3,3),BO4dVLRcheck(3,3,3,3),& 
& BO4dTLLcheck(3,3,3,3),BO4dTLRcheck(3,3,3,3),BO4dTRLcheck(3,3,3,3),BO4dTRRcheck(3,3,3,3),& 
& OAh2qSLcheck(3,3,2),OAh2qSRcheck(3,3,2),OA2qSLcheck(3,3),OA2qSRcheck(3,3),             & 
& OA2qVLcheck(3,3),OA2qVRcheck(3,3),OG2qSLcheck(3,3),OG2qSRcheck(3,3),OH2qSLcheck(3,3,2),& 
& OH2qSRcheck(3,3,2)

Complex(dp) :: OllddSLL(3,3,3,3),OllddSRR(3,3,3,3),OllddSRL(3,3,3,3),OllddSLR(3,3,3,3),              & 
& OllddVRR(3,3,3,3),OllddVLL(3,3,3,3),OllddVRL(3,3,3,3),OllddVLR(3,3,3,3),               & 
& OllddTLL(3,3,3,3),OllddTLR(3,3,3,3),OllddTRL(3,3,3,3),OllddTRR(3,3,3,3),               & 
& OlluuSLL(3,3,3,3),OlluuSRR(3,3,3,3),OlluuSRL(3,3,3,3),OlluuSLR(3,3,3,3),               & 
& OlluuVRR(3,3,3,3),OlluuVLL(3,3,3,3),OlluuVRL(3,3,3,3),OlluuVLR(3,3,3,3),               & 
& OlluuTLL(3,3,3,3),OlluuTLR(3,3,3,3),OlluuTRL(3,3,3,3),OlluuTRR(3,3,3,3),               & 
& O4lSLL(3,3,3,3),O4lSRR(3,3,3,3),O4lSRL(3,3,3,3),O4lSLR(3,3,3,3),O4lVRR(3,3,3,3),       & 
& O4lVLL(3,3,3,3),O4lVRL(3,3,3,3),O4lVLR(3,3,3,3),O4lTLL(3,3,3,3),O4lTLR(3,3,3,3),       & 
& O4lTRL(3,3,3,3),O4lTRR(3,3,3,3),O4lSLLcross(3,3,3,3),O4lSRRcross(3,3,3,3),             & 
& O4lSRLcross(3,3,3,3),O4lSLRcross(3,3,3,3),O4lVRRcross(3,3,3,3),O4lVLLcross(3,3,3,3),   & 
& O4lVRLcross(3,3,3,3),O4lVLRcross(3,3,3,3),O4lTLLcross(3,3,3,3),O4lTLRcross(3,3,3,3),   & 
& O4lTRLcross(3,3,3,3),O4lTRRcross(3,3,3,3),K1L(3,3),K1R(3,3),K2L(3,3),K2R(3,3)

Complex(dp) :: OddllSLLSM(3,3,3,3),OddllSRRSM(3,3,3,3),OddllSRLSM(3,3,3,3),OddllSLRSM(3,3,3,3),      & 
& OddllVRRSM(3,3,3,3),OddllVLLSM(3,3,3,3),OddllVRLSM(3,3,3,3),OddllVLRSM(3,3,3,3),       & 
& OddllTLLSM(3,3,3,3),OddllTLRSM(3,3,3,3),OddllTRLSM(3,3,3,3),OddllTRRSM(3,3,3,3),       & 
& OddvvVRRSM(3,3,3,3),OddvvVLLSM(3,3,3,3),OddvvVRLSM(3,3,3,3),OddvvVLRSM(3,3,3,3),       & 
& O4dSLLSM(3,3,3,3),O4dSRRSM(3,3,3,3),O4dSRLSM(3,3,3,3),O4dSLRSM(3,3,3,3),               & 
& O4dVRRSM(3,3,3,3),O4dVLLSM(3,3,3,3),O4dVRLSM(3,3,3,3),O4dVLRSM(3,3,3,3),               & 
& O4dTLLSM(3,3,3,3),O4dTLRSM(3,3,3,3),O4dTRLSM(3,3,3,3),O4dTRRSM(3,3,3,3),               & 
& OdulvSLLSM(3,3,3,3),OdulvSRRSM(3,3,3,3),OdulvSRLSM(3,3,3,3),OdulvSLRSM(3,3,3,3),       & 
& OdulvVRRSM(3,3,3,3),OdulvVLLSM(3,3,3,3),OdulvVRLSM(3,3,3,3),OdulvVLRSM(3,3,3,3),       & 
& CC8SM(3,3),CC8pSM(3,3),CC7SM(3,3),CC7pSM(3,3)

Complex(dp) :: OddllSLL(3,3,3,3),OddllSRR(3,3,3,3),OddllSRL(3,3,3,3),OddllSLR(3,3,3,3),              & 
& OddllVRR(3,3,3,3),OddllVLL(3,3,3,3),OddllVRL(3,3,3,3),OddllVLR(3,3,3,3),               & 
& OddllTLL(3,3,3,3),OddllTLR(3,3,3,3),OddllTRL(3,3,3,3),OddllTRR(3,3,3,3),               & 
& OddvvVRR(3,3,3,3),OddvvVLL(3,3,3,3),OddvvVRL(3,3,3,3),OddvvVLR(3,3,3,3),               & 
& O4dSLL(3,3,3,3),O4dSRR(3,3,3,3),O4dSRL(3,3,3,3),O4dSLR(3,3,3,3),O4dVRR(3,3,3,3),       & 
& O4dVLL(3,3,3,3),O4dVRL(3,3,3,3),O4dVLR(3,3,3,3),O4dTLL(3,3,3,3),O4dTLR(3,3,3,3),       & 
& O4dTRL(3,3,3,3),O4dTRR(3,3,3,3),OdulvSLL(3,3,3,3),OdulvSRR(3,3,3,3),OdulvSRL(3,3,3,3), & 
& OdulvSLR(3,3,3,3),OdulvVRR(3,3,3,3),OdulvVLL(3,3,3,3),OdulvVRL(3,3,3,3),               & 
& OdulvVLR(3,3,3,3),CC8(3,3),CC8p(3,3),CC7(3,3),CC7p(3,3)

Write(*,*) "Calculating low energy constraints" 
TSOllddSLL = 0._dp 
TSOllddSRR = 0._dp 
TSOllddSRL = 0._dp 
TSOllddSLR = 0._dp 
TSOllddVRR = 0._dp 
TSOllddVLL = 0._dp 
TSOllddVRL = 0._dp 
TSOllddVLR = 0._dp 
TSOllddTLL = 0._dp 
TSOllddTLR = 0._dp 
TSOllddTRL = 0._dp 
TSOllddTRR = 0._dp 
TVOllddSLL = 0._dp 
TVOllddSRR = 0._dp 
TVOllddSRL = 0._dp 
TVOllddSLR = 0._dp 
TVOllddVRR = 0._dp 
TVOllddVLL = 0._dp 
TVOllddVRL = 0._dp 
TVOllddVLR = 0._dp 
TVOllddTLL = 0._dp 
TVOllddTLR = 0._dp 
TVOllddTRL = 0._dp 
TVOllddTRR = 0._dp 
TSOlluuSLL = 0._dp 
TSOlluuSRR = 0._dp 
TSOlluuSRL = 0._dp 
TSOlluuSLR = 0._dp 
TSOlluuVRR = 0._dp 
TSOlluuVLL = 0._dp 
TSOlluuVRL = 0._dp 
TSOlluuVLR = 0._dp 
TSOlluuTLL = 0._dp 
TSOlluuTLR = 0._dp 
TSOlluuTRL = 0._dp 
TSOlluuTRR = 0._dp 
TVOlluuSLL = 0._dp 
TVOlluuSRR = 0._dp 
TVOlluuSRL = 0._dp 
TVOlluuSLR = 0._dp 
TVOlluuVRR = 0._dp 
TVOlluuVLL = 0._dp 
TVOlluuVRL = 0._dp 
TVOlluuVLR = 0._dp 
TVOlluuTLL = 0._dp 
TVOlluuTLR = 0._dp 
TVOlluuTRL = 0._dp 
TVOlluuTRR = 0._dp 
TSO4lSLL = 0._dp 
TSO4lSRR = 0._dp 
TSO4lSRL = 0._dp 
TSO4lSLR = 0._dp 
TSO4lVRR = 0._dp 
TSO4lVLL = 0._dp 
TSO4lVRL = 0._dp 
TSO4lVLR = 0._dp 
TSO4lTLL = 0._dp 
TSO4lTLR = 0._dp 
TSO4lTRL = 0._dp 
TSO4lTRR = 0._dp 
TVO4lSLL = 0._dp 
TVO4lSRR = 0._dp 
TVO4lSRL = 0._dp 
TVO4lSLR = 0._dp 
TVO4lVRR = 0._dp 
TVO4lVLL = 0._dp 
TVO4lVRL = 0._dp 
TVO4lVLR = 0._dp 
TVO4lTLL = 0._dp 
TVO4lTLR = 0._dp 
TVO4lTRL = 0._dp 
TVO4lTRR = 0._dp 
TSO4lSLLcross = 0._dp 
TSO4lSRRcross = 0._dp 
TSO4lSRLcross = 0._dp 
TSO4lSLRcross = 0._dp 
TSO4lVRRcross = 0._dp 
TSO4lVLLcross = 0._dp 
TSO4lVRLcross = 0._dp 
TSO4lVLRcross = 0._dp 
TSO4lTLLcross = 0._dp 
TSO4lTLRcross = 0._dp 
TSO4lTRLcross = 0._dp 
TSO4lTRRcross = 0._dp 
TVO4lSLLcross = 0._dp 
TVO4lSRRcross = 0._dp 
TVO4lSRLcross = 0._dp 
TVO4lSLRcross = 0._dp 
TVO4lVRRcross = 0._dp 
TVO4lVLLcross = 0._dp 
TVO4lVRLcross = 0._dp 
TVO4lVLRcross = 0._dp 
TVO4lTLLcross = 0._dp 
TVO4lTLRcross = 0._dp 
TVO4lTRLcross = 0._dp 
TVO4lTRRcross = 0._dp 
BOllddSLL = 0._dp 
BOllddSRR = 0._dp 
BOllddSRL = 0._dp 
BOllddSLR = 0._dp 
BOllddVRR = 0._dp 
BOllddVLL = 0._dp 
BOllddVRL = 0._dp 
BOllddVLR = 0._dp 
BOllddTLL = 0._dp 
BOllddTLR = 0._dp 
BOllddTRL = 0._dp 
BOllddTRR = 0._dp 
PSOllddSLL = 0._dp 
PSOllddSRR = 0._dp 
PSOllddSRL = 0._dp 
PSOllddSLR = 0._dp 
PSOllddVRR = 0._dp 
PSOllddVLL = 0._dp 
PSOllddVRL = 0._dp 
PSOllddVLR = 0._dp 
PSOllddTLL = 0._dp 
PSOllddTLR = 0._dp 
PSOllddTRL = 0._dp 
PSOllddTRR = 0._dp 
PVOllddSLL = 0._dp 
PVOllddSRR = 0._dp 
PVOllddSRL = 0._dp 
PVOllddSLR = 0._dp 
PVOllddVRR = 0._dp 
PVOllddVLL = 0._dp 
PVOllddVRL = 0._dp 
PVOllddVLR = 0._dp 
PVOllddTLL = 0._dp 
PVOllddTLR = 0._dp 
PVOllddTRL = 0._dp 
PVOllddTRR = 0._dp 
BOlluuSLL = 0._dp 
BOlluuSRR = 0._dp 
BOlluuSRL = 0._dp 
BOlluuSLR = 0._dp 
BOlluuVRR = 0._dp 
BOlluuVLL = 0._dp 
BOlluuVRL = 0._dp 
BOlluuVLR = 0._dp 
BOlluuTLL = 0._dp 
BOlluuTLR = 0._dp 
BOlluuTRL = 0._dp 
BOlluuTRR = 0._dp 
PSOlluuSLL = 0._dp 
PSOlluuSRR = 0._dp 
PSOlluuSRL = 0._dp 
PSOlluuSLR = 0._dp 
PSOlluuVRR = 0._dp 
PSOlluuVLL = 0._dp 
PSOlluuVRL = 0._dp 
PSOlluuVLR = 0._dp 
PSOlluuTLL = 0._dp 
PSOlluuTLR = 0._dp 
PSOlluuTRL = 0._dp 
PSOlluuTRR = 0._dp 
PVOlluuSLL = 0._dp 
PVOlluuSRR = 0._dp 
PVOlluuSRL = 0._dp 
PVOlluuSLR = 0._dp 
PVOlluuVRR = 0._dp 
PVOlluuVLL = 0._dp 
PVOlluuVRL = 0._dp 
PVOlluuVLR = 0._dp 
PVOlluuTLL = 0._dp 
PVOlluuTLR = 0._dp 
PVOlluuTRL = 0._dp 
PVOlluuTRR = 0._dp 
BO4lSLL = 0._dp 
BO4lSRR = 0._dp 
BO4lSRL = 0._dp 
BO4lSLR = 0._dp 
BO4lVRR = 0._dp 
BO4lVLL = 0._dp 
BO4lVRL = 0._dp 
BO4lVLR = 0._dp 
BO4lTLL = 0._dp 
BO4lTLR = 0._dp 
BO4lTRL = 0._dp 
BO4lTRR = 0._dp 
PSO4lSLL = 0._dp 
PSO4lSRR = 0._dp 
PSO4lSRL = 0._dp 
PSO4lSLR = 0._dp 
PSO4lVRR = 0._dp 
PSO4lVLL = 0._dp 
PSO4lVRL = 0._dp 
PSO4lVLR = 0._dp 
PSO4lTLL = 0._dp 
PSO4lTLR = 0._dp 
PSO4lTRL = 0._dp 
PSO4lTRR = 0._dp 
PVO4lSLL = 0._dp 
PVO4lSRR = 0._dp 
PVO4lSRL = 0._dp 
PVO4lSLR = 0._dp 
PVO4lVRR = 0._dp 
PVO4lVLL = 0._dp 
PVO4lVRL = 0._dp 
PVO4lVLR = 0._dp 
PVO4lTLL = 0._dp 
PVO4lTLR = 0._dp 
PVO4lTRL = 0._dp 
PVO4lTRR = 0._dp 
BO4lSLLcross = 0._dp 
BO4lSRRcross = 0._dp 
BO4lSRLcross = 0._dp 
BO4lSLRcross = 0._dp 
BO4lVRRcross = 0._dp 
BO4lVLLcross = 0._dp 
BO4lVRLcross = 0._dp 
BO4lVLRcross = 0._dp 
BO4lTLLcross = 0._dp 
BO4lTLRcross = 0._dp 
BO4lTRLcross = 0._dp 
BO4lTRRcross = 0._dp 
PSO4lSLLcross = 0._dp 
PSO4lSRRcross = 0._dp 
PSO4lSRLcross = 0._dp 
PSO4lSLRcross = 0._dp 
PSO4lVRRcross = 0._dp 
PSO4lVLLcross = 0._dp 
PSO4lVRLcross = 0._dp 
PSO4lVLRcross = 0._dp 
PSO4lTLLcross = 0._dp 
PSO4lTLRcross = 0._dp 
PSO4lTRLcross = 0._dp 
PSO4lTRRcross = 0._dp 
PVO4lSLLcross = 0._dp 
PVO4lSRRcross = 0._dp 
PVO4lSRLcross = 0._dp 
PVO4lSLRcross = 0._dp 
PVO4lVRRcross = 0._dp 
PVO4lVLLcross = 0._dp 
PVO4lVRLcross = 0._dp 
PVO4lVLRcross = 0._dp 
PVO4lTLLcross = 0._dp 
PVO4lTLRcross = 0._dp 
PVO4lTRLcross = 0._dp 
PVO4lTRRcross = 0._dp 
OA2lSL = 0._dp 
OA2lSR = 0._dp 
OA1L = 0._dp 
OA1R = 0._dp 
OH2lSL = 0._dp 
OH2lSR = 0._dp 
OZ2lSL = 0._dp 
OZ2lSR = 0._dp 
OZ2lVL = 0._dp 
OZ2lVR = 0._dp 
TSOddllSLL = 0._dp 
TSOddllSLLSM = 0._dp 
TSOddllSRR = 0._dp 
TSOddllSRRSM = 0._dp 
TSOddllSRL = 0._dp 
TSOddllSRLSM = 0._dp 
TSOddllSLR = 0._dp 
TSOddllSLRSM = 0._dp 
TSOddllVRR = 0._dp 
TSOddllVRRSM = 0._dp 
TSOddllVLL = 0._dp 
TSOddllVLLSM = 0._dp 
TSOddllVRL = 0._dp 
TSOddllVRLSM = 0._dp 
TSOddllVLR = 0._dp 
TSOddllVLRSM = 0._dp 
TSOddllTLL = 0._dp 
TSOddllTLLSM = 0._dp 
TSOddllTLR = 0._dp 
TSOddllTLRSM = 0._dp 
TSOddllTRL = 0._dp 
TSOddllTRLSM = 0._dp 
TSOddllTRR = 0._dp 
TSOddllTRRSM = 0._dp 
TVOddllSLL = 0._dp 
TVOddllSLLSM = 0._dp 
TVOddllSRR = 0._dp 
TVOddllSRRSM = 0._dp 
TVOddllSRL = 0._dp 
TVOddllSRLSM = 0._dp 
TVOddllSLR = 0._dp 
TVOddllSLRSM = 0._dp 
TVOddllVRR = 0._dp 
TVOddllVRRSM = 0._dp 
TVOddllVLL = 0._dp 
TVOddllVLLSM = 0._dp 
TVOddllVRL = 0._dp 
TVOddllVRLSM = 0._dp 
TVOddllVLR = 0._dp 
TVOddllVLRSM = 0._dp 
TVOddllTLL = 0._dp 
TVOddllTLLSM = 0._dp 
TVOddllTLR = 0._dp 
TVOddllTLRSM = 0._dp 
TVOddllTRL = 0._dp 
TVOddllTRLSM = 0._dp 
TVOddllTRR = 0._dp 
TVOddllTRRSM = 0._dp 
TSOddvvVRR = 0._dp 
TSOddvvVRRSM = 0._dp 
TSOddvvVLL = 0._dp 
TSOddvvVLLSM = 0._dp 
TSOddvvVRL = 0._dp 
TSOddvvVRLSM = 0._dp 
TSOddvvVLR = 0._dp 
TSOddvvVLRSM = 0._dp 
TVOddvvVRR = 0._dp 
TVOddvvVRRSM = 0._dp 
TVOddvvVLL = 0._dp 
TVOddvvVLLSM = 0._dp 
TVOddvvVRL = 0._dp 
TVOddvvVRLSM = 0._dp 
TVOddvvVLR = 0._dp 
TVOddvvVLRSM = 0._dp 
TSO4dSLL = 0._dp 
TSO4dSLLSM = 0._dp 
TSO4dSRR = 0._dp 
TSO4dSRRSM = 0._dp 
TSO4dSRL = 0._dp 
TSO4dSRLSM = 0._dp 
TSO4dSLR = 0._dp 
TSO4dSLRSM = 0._dp 
TSO4dVRR = 0._dp 
TSO4dVRRSM = 0._dp 
TSO4dVLL = 0._dp 
TSO4dVLLSM = 0._dp 
TSO4dVRL = 0._dp 
TSO4dVRLSM = 0._dp 
TSO4dVLR = 0._dp 
TSO4dVLRSM = 0._dp 
TSO4dTLL = 0._dp 
TSO4dTLLSM = 0._dp 
TSO4dTLR = 0._dp 
TSO4dTLRSM = 0._dp 
TSO4dTRL = 0._dp 
TSO4dTRLSM = 0._dp 
TSO4dTRR = 0._dp 
TSO4dTRRSM = 0._dp 
TVO4dSLL = 0._dp 
TVO4dSLLSM = 0._dp 
TVO4dSRR = 0._dp 
TVO4dSRRSM = 0._dp 
TVO4dSRL = 0._dp 
TVO4dSRLSM = 0._dp 
TVO4dSLR = 0._dp 
TVO4dSLRSM = 0._dp 
TVO4dVRR = 0._dp 
TVO4dVRRSM = 0._dp 
TVO4dVLL = 0._dp 
TVO4dVLLSM = 0._dp 
TVO4dVRL = 0._dp 
TVO4dVRLSM = 0._dp 
TVO4dVLR = 0._dp 
TVO4dVLRSM = 0._dp 
TVO4dTLL = 0._dp 
TVO4dTLLSM = 0._dp 
TVO4dTLR = 0._dp 
TVO4dTLRSM = 0._dp 
TVO4dTRL = 0._dp 
TVO4dTRLSM = 0._dp 
TVO4dTRR = 0._dp 
TVO4dTRRSM = 0._dp 
TSOdulvSLL = 0._dp 
TSOdulvSLLSM = 0._dp 
TSOdulvSRR = 0._dp 
TSOdulvSRRSM = 0._dp 
TSOdulvSRL = 0._dp 
TSOdulvSRLSM = 0._dp 
TSOdulvSLR = 0._dp 
TSOdulvSLRSM = 0._dp 
TSOdulvVRR = 0._dp 
TSOdulvVRRSM = 0._dp 
TSOdulvVLL = 0._dp 
TSOdulvVLLSM = 0._dp 
TSOdulvVRL = 0._dp 
TSOdulvVRLSM = 0._dp 
TSOdulvVLR = 0._dp 
TSOdulvVLRSM = 0._dp 
TVOdulvSLL = 0._dp 
TVOdulvSLLSM = 0._dp 
TVOdulvSRR = 0._dp 
TVOdulvSRRSM = 0._dp 
TVOdulvSRL = 0._dp 
TVOdulvSRLSM = 0._dp 
TVOdulvSLR = 0._dp 
TVOdulvSLRSM = 0._dp 
TVOdulvVRR = 0._dp 
TVOdulvVRRSM = 0._dp 
TVOdulvVLL = 0._dp 
TVOdulvVLLSM = 0._dp 
TVOdulvVRL = 0._dp 
TVOdulvVRLSM = 0._dp 
TVOdulvVLR = 0._dp 
TVOdulvVLRSM = 0._dp 
BOddllSLL = 0._dp 
BOddllSLLSM = 0._dp 
BOddllSRR = 0._dp 
BOddllSRRSM = 0._dp 
BOddllSRL = 0._dp 
BOddllSRLSM = 0._dp 
BOddllSLR = 0._dp 
BOddllSLRSM = 0._dp 
BOddllVRR = 0._dp 
BOddllVRRSM = 0._dp 
BOddllVLL = 0._dp 
BOddllVLLSM = 0._dp 
BOddllVRL = 0._dp 
BOddllVRLSM = 0._dp 
BOddllVLR = 0._dp 
BOddllVLRSM = 0._dp 
BOddllTLL = 0._dp 
BOddllTLLSM = 0._dp 
BOddllTLR = 0._dp 
BOddllTLRSM = 0._dp 
BOddllTRL = 0._dp 
BOddllTRLSM = 0._dp 
BOddllTRR = 0._dp 
BOddllTRRSM = 0._dp 
PSOddllSLL = 0._dp 
PSOddllSLLSM = 0._dp 
PSOddllSRR = 0._dp 
PSOddllSRRSM = 0._dp 
PSOddllSRL = 0._dp 
PSOddllSRLSM = 0._dp 
PSOddllSLR = 0._dp 
PSOddllSLRSM = 0._dp 
PSOddllVRR = 0._dp 
PSOddllVRRSM = 0._dp 
PSOddllVLL = 0._dp 
PSOddllVLLSM = 0._dp 
PSOddllVRL = 0._dp 
PSOddllVRLSM = 0._dp 
PSOddllVLR = 0._dp 
PSOddllVLRSM = 0._dp 
PSOddllTLL = 0._dp 
PSOddllTLLSM = 0._dp 
PSOddllTLR = 0._dp 
PSOddllTLRSM = 0._dp 
PSOddllTRL = 0._dp 
PSOddllTRLSM = 0._dp 
PSOddllTRR = 0._dp 
PSOddllTRRSM = 0._dp 
PVOddllSLL = 0._dp 
PVOddllSLLSM = 0._dp 
PVOddllSRR = 0._dp 
PVOddllSRRSM = 0._dp 
PVOddllSRL = 0._dp 
PVOddllSRLSM = 0._dp 
PVOddllSLR = 0._dp 
PVOddllSLRSM = 0._dp 
PVOddllVRR = 0._dp 
PVOddllVRRSM = 0._dp 
PVOddllVLL = 0._dp 
PVOddllVLLSM = 0._dp 
PVOddllVRL = 0._dp 
PVOddllVRLSM = 0._dp 
PVOddllVLR = 0._dp 
PVOddllVLRSM = 0._dp 
PVOddllTLL = 0._dp 
PVOddllTLLSM = 0._dp 
PVOddllTLR = 0._dp 
PVOddllTLRSM = 0._dp 
PVOddllTRL = 0._dp 
PVOddllTRLSM = 0._dp 
PVOddllTRR = 0._dp 
PVOddllTRRSM = 0._dp 
BOddvvVRR = 0._dp 
BOddvvVRRSM = 0._dp 
BOddvvVLL = 0._dp 
BOddvvVLLSM = 0._dp 
BOddvvVRL = 0._dp 
BOddvvVRLSM = 0._dp 
BOddvvVLR = 0._dp 
BOddvvVLRSM = 0._dp 
PSOddvvVRR = 0._dp 
PSOddvvVRRSM = 0._dp 
PSOddvvVLL = 0._dp 
PSOddvvVLLSM = 0._dp 
PSOddvvVRL = 0._dp 
PSOddvvVRLSM = 0._dp 
PSOddvvVLR = 0._dp 
PSOddvvVLRSM = 0._dp 
PVOddvvVRR = 0._dp 
PVOddvvVRRSM = 0._dp 
PVOddvvVLL = 0._dp 
PVOddvvVLLSM = 0._dp 
PVOddvvVRL = 0._dp 
PVOddvvVRLSM = 0._dp 
PVOddvvVLR = 0._dp 
PVOddvvVLRSM = 0._dp 
BO4dSLL = 0._dp 
BO4dSLLSM = 0._dp 
BO4dSRR = 0._dp 
BO4dSRRSM = 0._dp 
BO4dSRL = 0._dp 
BO4dSRLSM = 0._dp 
BO4dSLR = 0._dp 
BO4dSLRSM = 0._dp 
BO4dVRR = 0._dp 
BO4dVRRSM = 0._dp 
BO4dVLL = 0._dp 
BO4dVLLSM = 0._dp 
BO4dVRL = 0._dp 
BO4dVRLSM = 0._dp 
BO4dVLR = 0._dp 
BO4dVLRSM = 0._dp 
BO4dTLL = 0._dp 
BO4dTLLSM = 0._dp 
BO4dTLR = 0._dp 
BO4dTLRSM = 0._dp 
BO4dTRL = 0._dp 
BO4dTRLSM = 0._dp 
BO4dTRR = 0._dp 
BO4dTRRSM = 0._dp 
OAh2qSL = 0._dp 
OAh2qSLSM = 0._dp 
OAh2qSR = 0._dp 
OAh2qSRSM = 0._dp 
OA2qSL = 0._dp 
OA2qSLSM = 0._dp 
OA2qSR = 0._dp 
OA2qSRSM = 0._dp 
OA2qVL = 0._dp 
OA2qVLSM = 0._dp 
OA2qVR = 0._dp 
OA2qVRSM = 0._dp 
OG2qSL = 0._dp 
OG2qSLSM = 0._dp 
OG2qSR = 0._dp 
OG2qSRSM = 0._dp 
OH2qSL = 0._dp 
OH2qSLSM = 0._dp 
OH2qSR = 0._dp 
OH2qSRSM = 0._dp 
If (MatchingOrder.gt.-1) Then 


End if 
!-------------------------------------
! running to 160 GeV for b -> so gamma
!-------------------------------------

Qin=sqrt(getRenormalizationScale()) 
scale_save = Qin 
Call RunSM_and_SUSY_RGEs(160._dp,g1input,g2input,g3input,lam5input,lam1input,         & 
& lam4input,lam3input,lam2input,Yuinput,Ydinput,Yeinput,m122input,m112input,             & 
& m222input,vdinput,vuinput,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,             & 
& m112,m222,vd,vu,CKM_160,sinW2_160,Alpha_160,AlphaS_160,.false.)

If (MatchingOrder.eq.-1) Then 
g1=g1input 
g2=g2input 
g3=g3input 
lam5=lam5input 
lam1=lam1input 
lam4=lam4input 
lam3=lam3input 
lam2=lam2input 
Yu=Yuinput 
Yd=Ydinput 
Ye=Yeinput 
m122=m122input 
m112=m112input 
m222=m222input 
vd=vdinput 
vu=vuinput 
End if 

! ## All contributions ## 

Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,           & 
& m112,m222,vd,vu,(/ ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,           & 
& MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,betaH,               & 
& vd,vu,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,GenerationMixing,kont)

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
lam5input = lam5
lam1input = lam1
lam4input = lam4
lam3input = lam3
lam2input = lam2
Yuinput = Yu
Ydinput = Yd
Yeinput = Ye
m122input = m122
m112input = m112
m222input = m222
vdinput = vd
vuinput = vu
End If 
 
Mhh= MhhL 
Mhh2 = Mhh2L 
MAh= MAhL 
MAh2 = MAh2L 
MAh(1)=MVZ
MAh2(1)=MVZ2
MHm(1)=MVWm
MHm2(1)=MVWm2
Call AllCouplings(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,g1,g2,TW,g3,Yd,             & 
& ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,cplhhhhhh,      & 
& cplhhHmcHm,cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,       & 
& cplHmcHmVZ,cplhhcVWmVWm,cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,     & 
& cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,               & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,            & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,            & 
& cplcFvFvVZR)


 ! **** TreeS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TSOddllSLL(gt1,gt2,gt3,gt4),TSOddllSRR(gt1,gt2,gt3,gt4)        & 
& ,TSOddllSRL(gt1,gt2,gt3,gt4),TSOddllSLR(gt1,gt2,gt3,gt4),TSOddllVRR(gt1,gt2,gt3,gt4)   & 
& ,TSOddllVLL(gt1,gt2,gt3,gt4),TSOddllVRL(gt1,gt2,gt3,gt4),TSOddllVLR(gt1,gt2,gt3,gt4)   & 
& ,TSOddllTLL(gt1,gt2,gt3,gt4),TSOddllTLR(gt1,gt2,gt3,gt4),TSOddllTRL(gt1,gt2,gt3,gt4)   & 
& ,TSOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TVOddllSLL(gt1,gt2,gt3,gt4),TVOddllSRR(gt1,gt2,gt3,gt4)        & 
& ,TVOddllSRL(gt1,gt2,gt3,gt4),TVOddllSLR(gt1,gt2,gt3,gt4),TVOddllVRR(gt1,gt2,gt3,gt4)   & 
& ,TVOddllVLL(gt1,gt2,gt3,gt4),TVOddllVRL(gt1,gt2,gt3,gt4),TVOddllVLR(gt1,gt2,gt3,gt4)   & 
& ,TVOddllTLL(gt1,gt2,gt3,gt4),TVOddllTLR(gt1,gt2,gt3,gt4),TVOddllTRL(gt1,gt2,gt3,gt4)   & 
& ,TVOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,               & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,             & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,              & 
& cplHmcHmVZ,cplHmcVWmVZ,TSOddvvVRR(gt1,gt2,gt3,gt4),TSOddvvVLL(gt1,gt2,gt3,gt4)         & 
& ,TSOddvvVRL(gt1,gt2,gt3,gt4),TSOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,               & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,             & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,              & 
& cplHmcHmVZ,cplHmcVWmVZ,TVOddvvVRR(gt1,gt2,gt3,gt4),TVOddvvVLL(gt1,gt2,gt3,gt4)         & 
& ,TVOddvvVRL(gt1,gt2,gt3,gt4),TVOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,             & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,       & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,TSO4dSLL(gt1,gt2,gt3,gt4),TSO4dSRR(gt1,gt2,gt3,gt4),TSO4dSRL(gt1,gt2,gt3,gt4)& 
& ,TSO4dSLR(gt1,gt2,gt3,gt4),TSO4dVRR(gt1,gt2,gt3,gt4),TSO4dVLL(gt1,gt2,gt3,gt4)         & 
& ,TSO4dVRL(gt1,gt2,gt3,gt4),TSO4dVLR(gt1,gt2,gt3,gt4),TSO4dTLL(gt1,gt2,gt3,gt4)         & 
& ,TSO4dTLR(gt1,gt2,gt3,gt4),TSO4dTRL(gt1,gt2,gt3,gt4),TSO4dTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,             & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,       & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,TVO4dSLL(gt1,gt2,gt3,gt4),TVO4dSRR(gt1,gt2,gt3,gt4),TVO4dSRL(gt1,gt2,gt3,gt4)& 
& ,TVO4dSLR(gt1,gt2,gt3,gt4),TVO4dVRR(gt1,gt2,gt3,gt4),TVO4dVLL(gt1,gt2,gt3,gt4)         & 
& ,TVO4dVRL(gt1,gt2,gt3,gt4),TVO4dVLR(gt1,gt2,gt3,gt4),TVO4dTLL(gt1,gt2,gt3,gt4)         & 
& ,TVO4dTLR(gt1,gt2,gt3,gt4),TVO4dTRL(gt1,gt2,gt3,gt4),TVO4dTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeSdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeSdulv(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHmVWm,cplAhHmcHm,cplAhHmcVWm,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,cplhhHmcHm,cplhhHmcVWm,              & 
& cplHmcHmVZ,cplHmcVWmVZ,TSOdulvSLL(gt1,gt2,gt3,gt4),TSOdulvSRR(gt1,gt2,gt3,gt4)         & 
& ,TSOdulvSRL(gt1,gt2,gt3,gt4),TSOdulvSLR(gt1,gt2,gt3,gt4),TSOdulvVRR(gt1,gt2,gt3,gt4)   & 
& ,TSOdulvVLL(gt1,gt2,gt3,gt4),TSOdulvVRL(gt1,gt2,gt3,gt4),TSOdulvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeVdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeVdulv(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHmVWm,cplAhHmcHm,cplAhHmcVWm,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,cplhhHmcHm,cplhhHmcVWm,              & 
& cplHmcHmVZ,cplHmcVWmVZ,TVOdulvSLL(gt1,gt2,gt3,gt4),TVOdulvSRR(gt1,gt2,gt3,gt4)         & 
& ,TVOdulvSRL(gt1,gt2,gt3,gt4),TVOdulvSLR(gt1,gt2,gt3,gt4),TVOdulvVRR(gt1,gt2,gt3,gt4)   & 
& ,TVOdulvVLL(gt1,gt2,gt3,gt4),TVOdulvVRL(gt1,gt2,gt3,gt4),TVOdulvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** Box2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSOddllSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVOddllSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculateBox2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,             & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,BOddllSLL(gt1,gt2,gt3,gt4),BOddllSRR(gt1,gt2,gt3,gt4)          & 
& ,BOddllSRL(gt1,gt2,gt3,gt4),BOddllSLR(gt1,gt2,gt3,gt4),BOddllVRR(gt1,gt2,gt3,gt4)      & 
& ,BOddllVLL(gt1,gt2,gt3,gt4),BOddllVRL(gt1,gt2,gt3,gt4),BOddllVLR(gt1,gt2,gt3,gt4)      & 
& ,BOddllTLL(gt1,gt2,gt3,gt4),BOddllTLR(gt1,gt2,gt3,gt4),BOddllTRL(gt1,gt2,gt3,gt4)      & 
& ,BOddllTRR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** PengS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSOddllSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVOddllSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculatePengS2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PSOddllSLL(gt1,gt2,gt3,gt4),PSOddllSRR(gt1,gt2,gt3,gt4)        & 
& ,PSOddllSRL(gt1,gt2,gt3,gt4),PSOddllSLR(gt1,gt2,gt3,gt4),PSOddllVRR(gt1,gt2,gt3,gt4)   & 
& ,PSOddllVLL(gt1,gt2,gt3,gt4),PSOddllVRL(gt1,gt2,gt3,gt4),PSOddllVLR(gt1,gt2,gt3,gt4)   & 
& ,PSOddllTLL(gt1,gt2,gt3,gt4),PSOddllTLR(gt1,gt2,gt3,gt4),PSOddllTRL(gt1,gt2,gt3,gt4)   & 
& ,PSOddllTRR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** PengV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSOddllSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddllTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVOddllSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddllTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculatePengV2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PVOddllSLL(gt1,gt2,gt3,gt4),PVOddllSRR(gt1,gt2,gt3,gt4)        & 
& ,PVOddllSRL(gt1,gt2,gt3,gt4),PVOddllSLR(gt1,gt2,gt3,gt4),PVOddllVRR(gt1,gt2,gt3,gt4)   & 
& ,PVOddllVLL(gt1,gt2,gt3,gt4),PVOddllVRL(gt1,gt2,gt3,gt4),PVOddllVLR(gt1,gt2,gt3,gt4)   & 
& ,PVOddllTLL(gt1,gt2,gt3,gt4),PVOddllTLR(gt1,gt2,gt3,gt4),PVOddllTRL(gt1,gt2,gt3,gt4)   & 
& ,PVOddllTRR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** Box2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSOddvvVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVLR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVOddvvVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVLR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculateBox2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& BOddvvVRR(gt1,gt2,gt3,gt4),BOddvvVLL(gt1,gt2,gt3,gt4),BOddvvVRL(gt1,gt2,gt3,gt4)       & 
& ,BOddvvVLR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** PengS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSOddvvVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVLR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVOddvvVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVLR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculatePengS2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,               & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,             & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,              & 
& cplHmcHmVZ,cplHmcVWmVZ,PSOddvvVRR(gt1,gt2,gt3,gt4),PSOddvvVLL(gt1,gt2,gt3,gt4)         & 
& ,PSOddvvVRL(gt1,gt2,gt3,gt4),PSOddvvVLR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** PengV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSOddvvVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSOddvvVLR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVOddvvVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVOddvvVLR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculatePengV2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,               & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,             & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,             & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,              & 
& cplHmcHmVZ,cplHmcVWmVZ,PVOddvvVRR(gt1,gt2,gt3,gt4),PVOddvvVLL(gt1,gt2,gt3,gt4)         & 
& ,PVOddvvVRL(gt1,gt2,gt3,gt4),PVOddvvVLR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** Box4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
If ((Abs(TSO4dSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TSO4dTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
  If ((Abs(TVO4dSLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dSRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dSRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dSLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dVRR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dVLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dVRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dVLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dTLL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dTLR(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dTRL(gt1,gt2,gt3,gt4)).lt.epsTree).and. & 
 & (Abs(TVO4dTRR(gt1,gt2,gt3,gt4)).lt.epsTree)) Then 
Call CalculateBox4d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,               & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,       & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,BO4dSLL(gt1,gt2,gt3,gt4),BO4dSRR(gt1,gt2,gt3,gt4),BO4dSRL(gt1,gt2,gt3,gt4) & 
& ,BO4dSLR(gt1,gt2,gt3,gt4),BO4dVRR(gt1,gt2,gt3,gt4),BO4dVLL(gt1,gt2,gt3,gt4)            & 
& ,BO4dVRL(gt1,gt2,gt3,gt4),BO4dVLR(gt1,gt2,gt3,gt4),BO4dTLL(gt1,gt2,gt3,gt4)            & 
& ,BO4dTLR(gt1,gt2,gt3,gt4),BO4dTRL(gt1,gt2,gt3,gt4),BO4dTRR(gt1,gt2,gt3,gt4))

  End if 
End if 
End do 



 ! **** A2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateA2q(gt1,gt2,gt3,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,Mhh2,            & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,    & 
& cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,            & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,OAh2qSL(gt1,gt2,gt3)  & 
& ,OAh2qSR(gt1,gt2,gt3))

 End Do  
End do 



 ! **** Gamma2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGamma2Q(gt1,gt2,gt3,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVPL,cplcFuFuVPR,cplcHmVPVWm,cplcVWmVPVWm,cplHmcHmVP,cplHmcVWmVP,               & 
& OA2qSL(gt1,gt2),OA2qSR(gt1,gt2),OA2qVL(gt1,gt2),OA2qVR(gt1,gt2))

End do 



 ! **** Gluon2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGluon2Q(gt1,gt2,gt3,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVGL,cplcFuFuVGR,OG2qSL(gt1,gt2),OG2qSR(gt1,gt2))

End do 



 ! **** H2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateH2q(gt1,gt2,gt3,.False.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,Mhh2,            & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplhhcHmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,     & 
& cplhhVZVZ,OH2qSL(gt1,gt2,gt3),OH2qSR(gt1,gt2,gt3))

 End Do  
End do 



! ## SM only ##


 ! **** TreeS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TSOddllSLLSM(gt1,gt2,gt3,gt4),TSOddllSRRSM(gt1,gt2,gt3,gt4)    & 
& ,TSOddllSRLSM(gt1,gt2,gt3,gt4),TSOddllSLRSM(gt1,gt2,gt3,gt4),TSOddllVRRSM(gt1,gt2,gt3,gt4)& 
& ,TSOddllVLLSM(gt1,gt2,gt3,gt4),TSOddllVRLSM(gt1,gt2,gt3,gt4),TSOddllVLRSM(gt1,gt2,gt3,gt4)& 
& ,TSOddllTLLSM(gt1,gt2,gt3,gt4),TSOddllTLRSM(gt1,gt2,gt3,gt4),TSOddllTRLSM(gt1,gt2,gt3,gt4)& 
& ,TSOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TVOddllSLLSM(gt1,gt2,gt3,gt4),TVOddllSRRSM(gt1,gt2,gt3,gt4)    & 
& ,TVOddllSRLSM(gt1,gt2,gt3,gt4),TVOddllSLRSM(gt1,gt2,gt3,gt4),TVOddllVRRSM(gt1,gt2,gt3,gt4)& 
& ,TVOddllVLLSM(gt1,gt2,gt3,gt4),TVOddllVRLSM(gt1,gt2,gt3,gt4),TVOddllVLRSM(gt1,gt2,gt3,gt4)& 
& ,TVOddllTLLSM(gt1,gt2,gt3,gt4),TVOddllTLRSM(gt1,gt2,gt3,gt4),TVOddllTRLSM(gt1,gt2,gt3,gt4)& 
& ,TVOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& TSOddvvVRRSM(gt1,gt2,gt3,gt4),TSOddvvVLLSM(gt1,gt2,gt3,gt4),TSOddvvVRLSM(gt1,gt2,gt3,gt4)& 
& ,TSOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& TVOddvvVRRSM(gt1,gt2,gt3,gt4),TVOddvvVLLSM(gt1,gt2,gt3,gt4),TVOddvvVRLSM(gt1,gt2,gt3,gt4)& 
& ,TVOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4d(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,              & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,       & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,TSO4dSLLSM(gt1,gt2,gt3,gt4),TSO4dSRRSM(gt1,gt2,gt3,gt4),TSO4dSRLSM(gt1,gt2,gt3,gt4)& 
& ,TSO4dSLRSM(gt1,gt2,gt3,gt4),TSO4dVRRSM(gt1,gt2,gt3,gt4),TSO4dVLLSM(gt1,gt2,gt3,gt4)   & 
& ,TSO4dVRLSM(gt1,gt2,gt3,gt4),TSO4dVLRSM(gt1,gt2,gt3,gt4),TSO4dTLLSM(gt1,gt2,gt3,gt4)   & 
& ,TSO4dTLRSM(gt1,gt2,gt3,gt4),TSO4dTRLSM(gt1,gt2,gt3,gt4),TSO4dTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4d(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,              & 
& Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,       & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,TVO4dSLLSM(gt1,gt2,gt3,gt4),TVO4dSRRSM(gt1,gt2,gt3,gt4),TVO4dSRLSM(gt1,gt2,gt3,gt4)& 
& ,TVO4dSLRSM(gt1,gt2,gt3,gt4),TVO4dVRRSM(gt1,gt2,gt3,gt4),TVO4dVLLSM(gt1,gt2,gt3,gt4)   & 
& ,TVO4dVRLSM(gt1,gt2,gt3,gt4),TVO4dVLRSM(gt1,gt2,gt3,gt4),TVO4dTLLSM(gt1,gt2,gt3,gt4)   & 
& ,TVO4dTLRSM(gt1,gt2,gt3,gt4),TVO4dTRLSM(gt1,gt2,gt3,gt4),TVO4dTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeSdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeSdulv(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHmVWm,cplAhHmcHm,cplAhHmcVWm,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,cplhhHmcHm,cplhhHmcVWm,              & 
& cplHmcHmVZ,cplHmcVWmVZ,TSOdulvSLLSM(gt1,gt2,gt3,gt4),TSOdulvSRRSM(gt1,gt2,gt3,gt4)     & 
& ,TSOdulvSRLSM(gt1,gt2,gt3,gt4),TSOdulvSLRSM(gt1,gt2,gt3,gt4),TSOdulvVRRSM(gt1,gt2,gt3,gt4)& 
& ,TSOdulvVLLSM(gt1,gt2,gt3,gt4),TSOdulvVRLSM(gt1,gt2,gt3,gt4),TSOdulvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeVdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeVdulv(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHmVWm,cplAhHmcHm,cplAhHmcVWm,     & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,cplhhHmcHm,cplhhHmcVWm,              & 
& cplHmcHmVZ,cplHmcVWmVZ,TVOdulvSLLSM(gt1,gt2,gt3,gt4),TVOdulvSRRSM(gt1,gt2,gt3,gt4)     & 
& ,TVOdulvSRLSM(gt1,gt2,gt3,gt4),TVOdulvSLRSM(gt1,gt2,gt3,gt4),TVOdulvVRRSM(gt1,gt2,gt3,gt4)& 
& ,TVOdulvVLLSM(gt1,gt2,gt3,gt4),TVOdulvVRLSM(gt1,gt2,gt3,gt4),TVOdulvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** Box2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,              & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,BOddllSLLSM(gt1,gt2,gt3,gt4),BOddllSRRSM(gt1,gt2,gt3,gt4)      & 
& ,BOddllSRLSM(gt1,gt2,gt3,gt4),BOddllSLRSM(gt1,gt2,gt3,gt4),BOddllVRRSM(gt1,gt2,gt3,gt4)& 
& ,BOddllVLLSM(gt1,gt2,gt3,gt4),BOddllVRLSM(gt1,gt2,gt3,gt4),BOddllVLRSM(gt1,gt2,gt3,gt4)& 
& ,BOddllTLLSM(gt1,gt2,gt3,gt4),BOddllTLRSM(gt1,gt2,gt3,gt4),BOddllTRLSM(gt1,gt2,gt3,gt4)& 
& ,BOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PSOddllSLLSM(gt1,gt2,gt3,gt4),PSOddllSRRSM(gt1,gt2,gt3,gt4)    & 
& ,PSOddllSRLSM(gt1,gt2,gt3,gt4),PSOddllSLRSM(gt1,gt2,gt3,gt4),PSOddllVRRSM(gt1,gt2,gt3,gt4)& 
& ,PSOddllVLLSM(gt1,gt2,gt3,gt4),PSOddllVRLSM(gt1,gt2,gt3,gt4),PSOddllVLRSM(gt1,gt2,gt3,gt4)& 
& ,PSOddllTLLSM(gt1,gt2,gt3,gt4),PSOddllTLRSM(gt1,gt2,gt3,gt4),PSOddllTRLSM(gt1,gt2,gt3,gt4)& 
& ,PSOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,            & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PVOddllSLLSM(gt1,gt2,gt3,gt4),PVOddllSRRSM(gt1,gt2,gt3,gt4)    & 
& ,PVOddllSRLSM(gt1,gt2,gt3,gt4),PVOddllSLRSM(gt1,gt2,gt3,gt4),PVOddllVRRSM(gt1,gt2,gt3,gt4)& 
& ,PVOddllVLLSM(gt1,gt2,gt3,gt4),PVOddllVRLSM(gt1,gt2,gt3,gt4),PVOddllVLRSM(gt1,gt2,gt3,gt4)& 
& ,PVOddllTLLSM(gt1,gt2,gt3,gt4),PVOddllTLRSM(gt1,gt2,gt3,gt4),PVOddllTRLSM(gt1,gt2,gt3,gt4)& 
& ,PVOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** Box2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,             & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& BOddvvVRRSM(gt1,gt2,gt3,gt4),BOddvvVLLSM(gt1,gt2,gt3,gt4),BOddvvVRLSM(gt1,gt2,gt3,gt4) & 
& ,BOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& PSOddvvVRRSM(gt1,gt2,gt3,gt4),PSOddvvVLLSM(gt1,gt2,gt3,gt4),PSOddvvVRLSM(gt1,gt2,gt3,gt4)& 
& ,PSOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,      & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFvFvVZL,cplcFvFvVZR,cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,     & 
& PVOddvvVRRSM(gt1,gt2,gt3,gt4),PVOddvvVLLSM(gt1,gt2,gt3,gt4),PVOddvvVRLSM(gt1,gt2,gt3,gt4)& 
& ,PVOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** Box4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4d(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,            & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,           & 
& cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,      & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,           & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,cplhhcVWmVWm,            & 
& cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,cplHmcVWmVP,          & 
& cplHmcVWmVZ,BO4dSLLSM(gt1,gt2,gt3,gt4),BO4dSRRSM(gt1,gt2,gt3,gt4),BO4dSRLSM(gt1,gt2,gt3,gt4)& 
& ,BO4dSLRSM(gt1,gt2,gt3,gt4),BO4dVRRSM(gt1,gt2,gt3,gt4),BO4dVLLSM(gt1,gt2,gt3,gt4)      & 
& ,BO4dVRLSM(gt1,gt2,gt3,gt4),BO4dVLRSM(gt1,gt2,gt3,gt4),BO4dTLLSM(gt1,gt2,gt3,gt4)      & 
& ,BO4dTLRSM(gt1,gt2,gt3,gt4),BO4dTRLSM(gt1,gt2,gt3,gt4),BO4dTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** A2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateA2q(gt1,gt2,gt3,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,Mhh2,             & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,cplAhhhhh,cplAhhhVZ,      & 
& cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,    & 
& cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,            & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,OAh2qSLSM(gt1,gt2,gt3)& 
& ,OAh2qSRSM(gt1,gt2,gt3))

 End Do  
End do 



 ! **** Gamma2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGamma2Q(gt1,gt2,gt3,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,              & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVPL,cplcFuFuVPR,cplcHmVPVWm,cplcVWmVPVWm,cplHmcHmVP,cplHmcVWmVP,               & 
& OA2qSLSM(gt1,gt2),OA2qSRSM(gt1,gt2),OA2qVLSM(gt1,gt2),OA2qVRSM(gt1,gt2))

End do 



 ! **** Gluon2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGluon2Q(gt1,gt2,gt3,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,              & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,     & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuVGL,cplcFuFuVGR,OG2qSLSM(gt1,gt2),OG2qSRSM(gt1,gt2))

End do 



 ! **** H2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateH2q(gt1,gt2,gt3,.true.,MAh,MAh2,MFd,MFd2,MFu,MFu2,Mhh,Mhh2,             & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,cplcFdFuHmR,               & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplhhcHmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,     & 
& cplhhVZVZ,OH2qSLSM(gt1,gt2,gt3),OH2qSRSM(gt1,gt2,gt3))

 End Do  
End do 



 ! ***** Combine operators for 2d2L
OddllSLL = BOddllSLL + PSOddllSLL + PVOddllSLL + TSOddllSLL + TVOddllSLL
OddllSLLSM = BOddllSLLSM + PSOddllSLLSM + PVOddllSLLSM + TSOddllSLLSM + TVOddllSLLSM
OddllSRR = BOddllSRR + PSOddllSRR + PVOddllSRR + TSOddllSRR + TVOddllSRR
OddllSRRSM = BOddllSRRSM + PSOddllSRRSM + PVOddllSRRSM + TSOddllSRRSM + TVOddllSRRSM
OddllSRL = BOddllSRL + PSOddllSRL + PVOddllSRL + TSOddllSRL + TVOddllSRL
OddllSRLSM = BOddllSRLSM + PSOddllSRLSM + PVOddllSRLSM + TSOddllSRLSM + TVOddllSRLSM
OddllSLR = BOddllSLR + PSOddllSLR + PVOddllSLR + TSOddllSLR + TVOddllSLR
OddllSLRSM = BOddllSLRSM + PSOddllSLRSM + PVOddllSLRSM + TSOddllSLRSM + TVOddllSLRSM
OddllVRR = BOddllVRR + PSOddllVRR + PVOddllVRR + TSOddllVRR + TVOddllVRR
OddllVRRSM = BOddllVRRSM + PSOddllVRRSM + PVOddllVRRSM + TSOddllVRRSM + TVOddllVRRSM
OddllVLL = BOddllVLL + PSOddllVLL + PVOddllVLL + TSOddllVLL + TVOddllVLL
OddllVLLSM = BOddllVLLSM + PSOddllVLLSM + PVOddllVLLSM + TSOddllVLLSM + TVOddllVLLSM
OddllVRL = BOddllVRL + PSOddllVRL + PVOddllVRL + TSOddllVRL + TVOddllVRL
OddllVRLSM = BOddllVRLSM + PSOddllVRLSM + PVOddllVRLSM + TSOddllVRLSM + TVOddllVRLSM
OddllVLR = BOddllVLR + PSOddllVLR + PVOddllVLR + TSOddllVLR + TVOddllVLR
OddllVLRSM = BOddllVLRSM + PSOddllVLRSM + PVOddllVLRSM + TSOddllVLRSM + TVOddllVLRSM
OddllTLL = BOddllTLL + PSOddllTLL + PVOddllTLL + TSOddllTLL + TVOddllTLL
OddllTLLSM = BOddllTLLSM + PSOddllTLLSM + PVOddllTLLSM + TSOddllTLLSM + TVOddllTLLSM
OddllTLR = BOddllTLR + PSOddllTLR + PVOddllTLR + TSOddllTLR + TVOddllTLR
OddllTLRSM = BOddllTLRSM + PSOddllTLRSM + PVOddllTLRSM + TSOddllTLRSM + TVOddllTLRSM
OddllTRL = BOddllTRL + PSOddllTRL + PVOddllTRL + TSOddllTRL + TVOddllTRL
OddllTRLSM = BOddllTRLSM + PSOddllTRLSM + PVOddllTRLSM + TSOddllTRLSM + TVOddllTRLSM
OddllTRR = BOddllTRR + PSOddllTRR + PVOddllTRR + TSOddllTRR + TVOddllTRR
OddllTRRSM = BOddllTRRSM + PSOddllTRRSM + PVOddllTRRSM + TSOddllTRRSM + TVOddllTRRSM

 ! ***** Combine operators for 2d2nu
OddvvVRR = BOddvvVRR + PSOddvvVRR + PVOddvvVRR + TSOddvvVRR + TVOddvvVRR
OddvvVRRSM = BOddvvVRRSM + PSOddvvVRRSM + PVOddvvVRRSM + TSOddvvVRRSM + TVOddvvVRRSM
OddvvVLL = BOddvvVLL + PSOddvvVLL + PVOddvvVLL + TSOddvvVLL + TVOddvvVLL
OddvvVLLSM = BOddvvVLLSM + PSOddvvVLLSM + PVOddvvVLLSM + TSOddvvVLLSM + TVOddvvVLLSM
OddvvVRL = BOddvvVRL + PSOddvvVRL + PVOddvvVRL + TSOddvvVRL + TVOddvvVRL
OddvvVRLSM = BOddvvVRLSM + PSOddvvVRLSM + PVOddvvVRLSM + TSOddvvVRLSM + TVOddvvVRLSM
OddvvVLR = BOddvvVLR + PSOddvvVLR + PVOddvvVLR + TSOddvvVLR + TVOddvvVLR
OddvvVLRSM = BOddvvVLRSM + PSOddvvVLRSM + PVOddvvVLRSM + TSOddvvVLRSM + TVOddvvVLRSM

 ! ***** Combine operators for 4d
O4dSLL = BO4dSLL + TSO4dSLL + TVO4dSLL
O4dSLLSM = BO4dSLLSM + TSO4dSLLSM + TVO4dSLLSM
O4dSRR = BO4dSRR + TSO4dSRR + TVO4dSRR
O4dSRRSM = BO4dSRRSM + TSO4dSRRSM + TVO4dSRRSM
O4dSRL = BO4dSRL + TSO4dSRL + TVO4dSRL
O4dSRLSM = BO4dSRLSM + TSO4dSRLSM + TVO4dSRLSM
O4dSLR = BO4dSLR + TSO4dSLR + TVO4dSLR
O4dSLRSM = BO4dSLRSM + TSO4dSLRSM + TVO4dSLRSM
O4dVRR = BO4dVRR + TSO4dVRR + TVO4dVRR
O4dVRRSM = BO4dVRRSM + TSO4dVRRSM + TVO4dVRRSM
O4dVLL = BO4dVLL + TSO4dVLL + TVO4dVLL
O4dVLLSM = BO4dVLLSM + TSO4dVLLSM + TVO4dVLLSM
O4dVRL = BO4dVRL + TSO4dVRL + TVO4dVRL
O4dVRLSM = BO4dVRLSM + TSO4dVRLSM + TVO4dVRLSM
O4dVLR = BO4dVLR + TSO4dVLR + TVO4dVLR
O4dVLRSM = BO4dVLRSM + TSO4dVLRSM + TVO4dVLRSM
O4dTLL = BO4dTLL + TSO4dTLL + TVO4dTLL
O4dTLLSM = BO4dTLLSM + TSO4dTLLSM + TVO4dTLLSM
O4dTLR = BO4dTLR + TSO4dTLR + TVO4dTLR
O4dTLRSM = BO4dTLRSM + TSO4dTLRSM + TVO4dTLRSM
O4dTRL = BO4dTRL + TSO4dTRL + TVO4dTRL
O4dTRLSM = BO4dTRLSM + TSO4dTRLSM + TVO4dTRLSM
O4dTRR = BO4dTRR + TSO4dTRR + TVO4dTRR
O4dTRRSM = BO4dTRRSM + TSO4dTRRSM + TVO4dTRRSM

 ! ***** Combine operators for dulv
OdulvSLL = TSOdulvSLL + TVOdulvSLL
OdulvSLLSM = TSOdulvSLLSM + TVOdulvSLLSM
OdulvSRR = TSOdulvSRR + TVOdulvSRR
OdulvSRRSM = TSOdulvSRRSM + TVOdulvSRRSM
OdulvSRL = TSOdulvSRL + TVOdulvSRL
OdulvSRLSM = TSOdulvSRLSM + TVOdulvSRLSM
OdulvSLR = TSOdulvSLR + TVOdulvSLR
OdulvSLRSM = TSOdulvSLRSM + TVOdulvSLRSM
OdulvVRR = TSOdulvVRR + TVOdulvVRR
OdulvVRRSM = TSOdulvVRRSM + TVOdulvVRRSM
OdulvVLL = TSOdulvVLL + TVOdulvVLL
OdulvVLLSM = TSOdulvVLLSM + TVOdulvVLLSM
OdulvVRL = TSOdulvVRL + TVOdulvVRL
OdulvVRLSM = TSOdulvVRLSM + TVOdulvVRLSM
OdulvVLR = TSOdulvVLR + TVOdulvVLR
OdulvVLRSM = TSOdulvVLRSM + TVOdulvVLRSM

 ! ***** Combine operators for Gluon2Q
CC8 = OG2qSL
CC8SM = OG2qSLSM 
CC8p = OG2qSR
CC8pSM = OG2qSRSM 
CC8(2,:) = -0.25_dp*CC8(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8(3,:) = -0.25_dp*CC8(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)
CC8p(2,:) = -0.25_dp*CC8p(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8p(3,:) = -0.25_dp*CC8p(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)
CC8SM(2,:) = -0.25_dp*CC8SM(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8SM(3,:) = -0.25_dp*CC8SM(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)
CC8pSM(2,:) = -0.25_dp*CC8pSM(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8pSM(3,:) = -0.25_dp*CC8pSM(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)

 ! ***** Combine operators for Gamma2Q
CC7 = OA2qSL
CC7SM = OA2qSLSM 
CC7p = OA2qSR
CC7pSM = OA2qSRSM 
CC7(2,:) = -0.25_dp*CC7(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7(3,:) = -0.25_dp*CC7(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)
CC7p(2,:) = -0.25_dp*CC7p(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7p(3,:) = -0.25_dp*CC7p(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)
CC7SM(2,:) = -0.25_dp*CC7SM(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7SM(3,:) = -0.25_dp*CC7SM(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)
CC7pSM(2,:) = -0.25_dp*CC7pSM(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7pSM(3,:) = -0.25_dp*CC7pSM(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)

 ! **** B0toLL **** 
 
Call Calculate_B0toLL(OddllSLL,OddllSRR,OddllSRL,OddllSLR,OddllVRR,OddllVLL,          & 
& OddllVRL,OddllVLR,OddllSLLSM,OddllSRRSM,OddllSRLSM,OddllSLRSM,OddllVRRSM,              & 
& OddllVLLSM,OddllVRLSM,OddllVLRSM,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,      & 
& ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,            & 
& ratioB0sTauTau)

If(BrB0dEE.ne.BrB0dEE) BrB0dEE = 0._dp 
If(ratioB0dEE.ne.ratioB0dEE) ratioB0dEE = 0._dp 
If(BrB0sEE.ne.BrB0sEE) BrB0sEE = 0._dp 
If(ratioB0sEE.ne.ratioB0sEE) ratioB0sEE = 0._dp 
If(BrB0dMuMu.ne.BrB0dMuMu) BrB0dMuMu = 0._dp 
If(ratioB0dMuMu.ne.ratioB0dMuMu) ratioB0dMuMu = 0._dp 
If(BrB0sMuMu.ne.BrB0sMuMu) BrB0sMuMu = 0._dp 
If(ratioB0sMuMu.ne.ratioB0sMuMu) ratioB0sMuMu = 0._dp 
If(BrB0dTauTau.ne.BrB0dTauTau) BrB0dTauTau = 0._dp 
If(ratioB0dTauTau.ne.ratioB0dTauTau) ratioB0dTauTau = 0._dp 
If(BrB0sTauTau.ne.BrB0sTauTau) BrB0sTauTau = 0._dp 
If(ratioB0sTauTau.ne.ratioB0sTauTau) ratioB0sTauTau = 0._dp 

 ! **** bsGamma **** 
 
Call Calculate_bsGamma(CC7,CC7p,CC8,CC8p,CC7SM,CC7pSM,CC8SM,CC8pSM,BrBsGamma,         & 
& ratioBsGamma)

If(BrBsGamma.ne.BrBsGamma) BrBsGamma = 0._dp 
If(ratioBsGamma.ne.ratioBsGamma) ratioBsGamma = 0._dp 

 ! **** BtoKLL **** 
 
Call Calculate_BtoKLL(OddllVRR,OddllVLL,OddllVRL,OddllVLR,CC7,CC7p,OddllVRRSM,        & 
& OddllVLLSM,OddllVRLSM,OddllVLRSM,CC7SM,CC7pSM,BrBtoKee,ratioBtoKee,BrBtoKmumu,         & 
& ratioBtoKmumu)

If(BrBtoKee.ne.BrBtoKee) BrBtoKee = 0._dp 
If(ratioBtoKee.ne.ratioBtoKee) ratioBtoKee = 0._dp 
If(BrBtoKmumu.ne.BrBtoKmumu) BrBtoKmumu = 0._dp 
If(ratioBtoKmumu.ne.ratioBtoKmumu) ratioBtoKmumu = 0._dp 

 ! **** BtoQnunu **** 
 
Call Calculate_BtoQnunu(OddvvVRR,OddvvVLL,OddvvVRL,OddvvVLR,OddvvVRRSM,               & 
& OddvvVLLSM,OddvvVRLSM,OddvvVLRSM,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu)

If(BrBtoSnunu.ne.BrBtoSnunu) BrBtoSnunu = 0._dp 
If(ratioBtoSnunu.ne.ratioBtoSnunu) ratioBtoSnunu = 0._dp 
If(BrBtoDnunu.ne.BrBtoDnunu) BrBtoDnunu = 0._dp 
If(ratioBtoDnunu.ne.ratioBtoDnunu) ratioBtoDnunu = 0._dp 

 ! **** BtoSLL **** 
 
Call Calculate_BtoSLL(OddllVRR,OddllVLL,OddllVRL,OddllVLR,CC7,CC7p,CC8,               & 
& CC8p,OddllVRRSM,OddllVLLSM,OddllVRLSM,OddllVLRSM,CC7SM,CC7pSM,CC8SM,CC8pSM,            & 
& BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu)

If(BrBtoSEE.ne.BrBtoSEE) BrBtoSEE = 0._dp 
If(ratioBtoSEE.ne.ratioBtoSEE) ratioBtoSEE = 0._dp 
If(BrBtoSMuMu.ne.BrBtoSMuMu) BrBtoSMuMu = 0._dp 
If(ratioBtoSMuMu.ne.ratioBtoSMuMu) ratioBtoSMuMu = 0._dp 

 ! **** DeltaMBq **** 
 
Call Calculate_DeltaMBq(O4dSLL,O4dSRR,O4dSRL,O4dSLR,O4dVRR,O4dVLL,O4dVLLSM,           & 
& O4dVRL,O4dVLR,O4dTLL,O4dTLR,O4dTRL,O4dTRR,OH2qSL,OH2qSR,OAh2qSL,OAh2qSR,               & 
& DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq)

If(DeltaMBs.ne.DeltaMBs) DeltaMBs = 0._dp 
If(ratioDeltaMBs.ne.ratioDeltaMBs) ratioDeltaMBs = 0._dp 
If(DeltaMBq.ne.DeltaMBq) DeltaMBq = 0._dp 
If(ratioDeltaMBq.ne.ratioDeltaMBq) ratioDeltaMBq = 0._dp 

 ! **** K0toEmu **** 
 
Call Calculate_K0toEmu(OddllSLL,OddllSLR,OddllSRR,OddllSRL,OddllVRR,OddllVLR,         & 
& OddllVRL,OddllVLL,OddllSLLSM,OddllSLRSM,OddllSRRSM,OddllSRLSM,OddllVRRSM,              & 
& OddllVLRSM,OddllVRLSM,OddllVLLSM,BrK0eMu,ratioK0eMu)

If(BrK0eMu.ne.BrK0eMu) BrK0eMu = 0._dp 
If(ratioK0eMu.ne.ratioK0eMu) ratioK0eMu = 0._dp 

 ! **** KKmix **** 
 
Call Calculate_KKmix(O4dSLL,O4dSRR,O4dSRL,O4dSLR,O4dVRR,O4dVLL,O4dVRL,O4dVLR,         & 
& O4dTLL,O4dTLR,O4dTRL,O4dTRR,O4dSLLSM,O4dSRRSM,O4dSRLSM,O4dSLRSM,O4dVRRSM,              & 
& O4dVLLSM,O4dVRLSM,O4dVLRSM,O4dTLLSM,O4dTLRSM,O4dTRLSM,O4dTRRSM,DelMK,ratioDelMK,       & 
& epsK,ratioepsK)

If(DelMK.ne.DelMK) DelMK = 0._dp 
If(ratioDelMK.ne.ratioDelMK) ratioDelMK = 0._dp 
If(epsK.ne.epsK) epsK = 0._dp 
If(ratioepsK.ne.ratioepsK) ratioepsK = 0._dp 

 ! **** KtoPInunu **** 
 
Call Calculate_KtoPInunu(OddvvVRR,OddvvVLL,OddvvVRL,OddvvVLR,OddvvVRRSM,              & 
& OddvvVLLSM,OddvvVRLSM,OddvvVLRSM,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,          & 
& ratioKltoPinunu)

If(BrKptoPipnunu.ne.BrKptoPipnunu) BrKptoPipnunu = 0._dp 
If(ratioKptoPipnunu.ne.ratioKptoPipnunu) ratioKptoPipnunu = 0._dp 
If(BrKltoPinunu.ne.BrKltoPinunu) BrKltoPinunu = 0._dp 
If(ratioKltoPinunu.ne.ratioKltoPinunu) ratioKltoPinunu = 0._dp 

 ! **** Plnu **** 
 
Call Calculate_Plnu(OdulvSLL,OdulvSRR,OdulvSRL,OdulvSLR,OdulvVRR,OdulvVLL,            & 
& OdulvVRL,OdulvVLR,OdulvSLLSM,OdulvSRRSM,OdulvSRLSM,OdulvSLRSM,OdulvVRRSM,              & 
& OdulvVLLSM,OdulvVRLSM,OdulvVLRSM,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,              & 
& BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM)

If(BrDmunu.ne.BrDmunu) BrDmunu = 0._dp 
If(ratioDmunu.ne.ratioDmunu) ratioDmunu = 0._dp 
If(BrDsmunu.ne.BrDsmunu) BrDsmunu = 0._dp 
If(ratioDsmunu.ne.ratioDsmunu) ratioDsmunu = 0._dp 
If(BrDstaunu.ne.BrDstaunu) BrDstaunu = 0._dp 
If(ratioDstaunu.ne.ratioDstaunu) ratioDstaunu = 0._dp 
If(BrBmunu.ne.BrBmunu) BrBmunu = 0._dp 
If(ratioBmunu.ne.ratioBmunu) ratioBmunu = 0._dp 
If(BrBtaunu.ne.BrBtaunu) BrBtaunu = 0._dp 
If(ratioBtaunu.ne.ratioBtaunu) ratioBtaunu = 0._dp 
If(BrKmunu.ne.BrKmunu) BrKmunu = 0._dp 
If(ratioKmunu.ne.ratioKmunu) ratioKmunu = 0._dp 
If(RK.ne.RK) RK = 0._dp 
If(RKSM.ne.RKSM) RKSM = 0._dp 
coeffC7sm = CC7SM(3,2)
coeffC7 = CC7(3,2)
coeffC7p = CC7p(3,2)
coeffC7NP = CC7(3,2) - CC7SM(3,2)
coeffC7pNP = CC7p(3,2)
coeffC8sm = CC8SM(3,2)
coeffC8 = CC8(3,2)
coeffC8p = CC8p(3,2)
coeffC8NP = CC8(3,2) - CC8SM(3,2)
coeffC8pNP = CC8p(3,2)
coeffC9eeSM = (OddllVLLSM(3,2,1,1) + OddllVLRSM(3,2,1,1))/2._dp
coeffC9ee = (OddllVLL(3,2,1,1) + OddllVLR(3,2,1,1))/2._dp
coeffC9Pee = (OddllVRL(3,2,1,1) + OddllVRR(3,2,1,1))/2._dp
coeffC9eeNP = (OddllVLL(3,2,1,1) - OddllVLLSM(3,2,1,1) + OddllVLR(3,2,1,1) - OddllVLRSM(3,2,1,1))/2._dp
coeffC9PeeNP = (OddllVRL(3,2,1,1) + OddllVRR(3,2,1,1))/2._dp
coeffC10eeSM = (-OddllVLLSM(3,2,1,1) + OddllVLRSM(3,2,1,1))/2._dp
coeffC10ee = (-OddllVLL(3,2,1,1) + OddllVLR(3,2,1,1))/2._dp
coeffC10Pee = (OddllVRL(3,2,1,1) - OddllVRR(3,2,1,1))/2._dp
coeffC10eeNP = (-OddllVLL(3,2,1,1) + OddllVLLSM(3,2,1,1) + OddllVLR(3,2,1,1) - OddllVLRSM(3,2,1,1))/2._dp
coeffC10PeeNP = (-OddllVRL(3,2,1,1) + OddllVRR(3,2,1,1))/2._dp
coeffC9mumuSM = (OddllVLLSM(3,2,2,2) + OddllVLRSM(3,2,2,2))/2._dp
coeffC9mumu = (OddllVLL(3,2,2,2) + OddllVLR(3,2,2,2))/2._dp
coeffC9Pmumu = (OddllVRL(3,2,2,2) + OddllVRR(3,2,2,2))/2._dp
coeffC9mumuNP = (OddllVLL(3,2,2,2) - OddllVLLSM(3,2,2,2) + OddllVLR(3,2,2,2) - OddllVLRSM(3,2,2,2))/2._dp
coeffC9PmumuNP = (OddllVRL(3,2,2,2) + OddllVRR(3,2,2,2))/2._dp
coeffC10mumuSM = (-OddllVLLSM(3,2,2,2) + OddllVLRSM(3,2,2,2))/2._dp
coeffC10mumu = (-OddllVLL(3,2,2,2) + OddllVLR(3,2,2,2))/2._dp
coeffC10Pmumu = (OddllVRL(3,2,2,2) - OddllVRR(3,2,2,2))/2._dp
coeffC10mumuNP = (-OddllVLL(3,2,2,2) + OddllVLLSM(3,2,2,2) + OddllVLR(3,2,2,2) - OddllVLRSM(3,2,2,2))/2._dp
coeffC10PmumuNP = (OddllVRL(3,2,2,2) - OddllVRR(3,2,2,2))/2._dp
coeffCLnu1nu1SM = OddvvVLLSM(3,2,1,1)
coeffCLnu1nu1 = OddvvVLL(3,2,1,1)
coeffCLPnu1nu1 = OddvvVRL(3,2,1,1)
coeffCLnu1nu1NP = OddvvVLL(3,2,1,1) - OddvvVLLSM(3,2,1,1)
coeffCLPnu1nu1NP = OddvvVRL(3,2,1,1)
coeffCLnu2nu2SM = OddvvVLLSM(3,2,2,2)
coeffCLnu2nu2 = OddvvVLL(3,2,2,2)
coeffCLPnu2nu2 = OddvvVRL(3,2,2,2)
coeffCLnu2nu2NP = OddvvVLL(3,2,2,2) - OddvvVLLSM(3,2,2,2)
coeffCLPnu2nu2NP = OddvvVRL(3,2,2,2)
coeffCLnu3nu3SM = OddvvVLLSM(3,2,3,3)
coeffCLnu3nu3 = OddvvVLL(3,2,3,3)
coeffCLPnu3nu3 = OddvvVRL(3,2,3,3)
coeffCLnu3nu3NP = OddvvVLL(3,2,3,3) - OddvvVLLSM(3,2,3,3)
coeffCLPnu3nu3NP = OddvvVRL(3,2,3,3)
coeffCRnu1nu1SM = 0
coeffCRnu1nu1 = OddvvVLR(3,2,1,1)
coeffCRPnu1nu1 = OddvvVRR(3,2,1,1)
coeffCRnu1nu1NP = OddvvVLR(3,2,1,1)
coeffCRPnu1nu1NP = OddvvVRR(3,2,1,1)
coeffCRnu2nu2SM = 0
coeffCRnu2nu2 = OddvvVLR(3,2,2,2)
coeffCRPnu2nu2 = OddvvVRR(3,2,2,2)
coeffCRnu2nu2NP = OddvvVLR(3,2,2,2)
coeffCRPnu2nu2NP = OddvvVRR(3,2,2,2)
coeffCRnu3nu3SM = 0
coeffCRnu3nu3 = OddvvVLR(3,2,3,3)
coeffCRPnu3nu3 = OddvvVRR(3,2,3,3)
coeffCRnu3nu3NP = OddvvVLR(3,2,3,3)
coeffCRPnu3nu3NP = OddvvVRR(3,2,3,3)
coeffKK_SLL = O4dSLL(2,1,2,1)/2._dp
coeffKK_SRR = O4dSRR(2,1,2,1)/2._dp
coeffKK_SLR = O4dSLR(2,1,2,1) + O4dSRL(2,1,2,1)
coeffKK_VLL = O4dVLL(2,1,2,1)/2._dp
coeffKK_VRR = O4dVRR(2,1,2,1)/2._dp
coeffKK_VLR = O4dVLR(2,1,2,1) + O4dVRL(2,1,2,1)
coeffKK_TLL = O4dTLL(2,1,2,1)/2._dp
coeffKK_TRR = O4dTRR(2,1,2,1)/2._dp
coeffBB_SLL = O4dSLL(3,1,3,1)/2._dp
coeffBB_SRR = O4dSRR(3,1,3,1)/2._dp
coeffBB_SLR = O4dSLR(3,1,3,1) + O4dSRL(3,1,3,1)
coeffBB_VLL = O4dVLL(3,1,3,1)/2._dp
coeffBB_VRR = O4dVRR(3,1,3,1)/2._dp
coeffBB_VLR = O4dVLR(3,1,3,1) + O4dVRL(3,1,3,1)
coeffBB_TLL = O4dTLL(3,1,3,1)/2._dp
coeffBB_TRR = O4dTRR(3,1,3,1)/2._dp
coeffBsBs_SLL = O4dSLL(3,2,3,2)/2._dp
coeffBsBs_SRR = O4dSRR(3,2,3,2)/2._dp
coeffBsBs_SLR = O4dSLR(3,2,3,2) + O4dSRL(3,2,3,2)
coeffBsBs_VLL = O4dVLL(3,2,3,2)/2._dp
coeffBsBs_VRR = O4dVRR(3,2,3,2)/2._dp
coeffBsBs_VLR = O4dVLR(3,2,3,2) + O4dVRL(3,2,3,2)
coeffBsBs_TLL = O4dTLL(3,2,3,2)/2._dp
coeffBsBs_TRR = O4dTRR(3,2,3,2)/2._dp
coeffKK_SLLNP = O4dSLL(2,1,2,1)/2._dp - O4dSLLSM(2,1,2,1)/2._dp
coeffKK_SRRNP = O4dSRR(2,1,2,1)/2._dp - O4dSRRSM(2,1,2,1)/2._dp
coeffKK_SLRNP = O4dSLR(2,1,2,1) - O4dSLRSM(2,1,2,1) + O4dSRL(2,1,2,1) - O4dSRLSM(2,1,2,1)
coeffKK_VLLNP = O4dVLL(2,1,2,1)/2._dp - O4dVLLSM(2,1,2,1)/2._dp
coeffKK_VRRNP = O4dVRR(2,1,2,1)/2._dp - O4dVRRSM(2,1,2,1)/2._dp
coeffKK_VLRNP = O4dVLR(2,1,2,1) - O4dVLRSM(2,1,2,1) + O4dVRL(2,1,2,1) - O4dVRLSM(2,1,2,1)
coeffKK_TLLNP = O4dTLL(2,1,2,1)/2._dp - O4dTLLSM(2,1,2,1)/2._dp
coeffKK_TRRNP = O4dTRR(2,1,2,1)/2._dp - O4dTRRSM(2,1,2,1)/2._dp
coeffBB_SLLNP = O4dSLL(3,1,3,1)/2._dp - O4dSLLSM(3,1,3,1)/2._dp
coeffBB_SRRNP = O4dSRR(3,1,3,1)/2._dp - O4dSRRSM(3,1,3,1)/2._dp
coeffBB_SLRNP = O4dSLR(3,1,3,1) - O4dSLRSM(3,1,3,1) + O4dSRL(3,1,3,1) - O4dSRLSM(3,1,3,1)
coeffBB_VLLNP = O4dVLL(3,1,3,1)/2._dp - O4dVLLSM(3,1,3,1)/2._dp
coeffBB_VRRNP = O4dVRR(3,1,3,1)/2._dp - O4dVRRSM(3,1,3,1)/2._dp
coeffBB_VLRNP = O4dVLR(3,1,3,1) - O4dVLRSM(3,1,3,1) + O4dVRL(3,1,3,1) - O4dVRLSM(3,1,3,1)
coeffBB_TLLNP = O4dTLL(3,1,3,1)/2._dp - O4dTLLSM(3,1,3,1)/2._dp
coeffBB_TRRNP = O4dTRR(3,1,3,1)/2._dp - O4dTRRSM(3,1,3,1)/2._dp
coeffBsBs_SLLNP = O4dSLL(3,2,3,2)/2._dp - O4dSLLSM(3,2,3,2)/2._dp
coeffBsBs_SRRNP = O4dSRR(3,2,3,2)/2._dp - O4dSRRSM(3,2,3,2)/2._dp
coeffBsBs_SLRNP = O4dSLR(3,2,3,2) - O4dSLRSM(3,2,3,2) + O4dSRL(3,2,3,2) - O4dSRLSM(3,2,3,2)
coeffBsBs_VLLNP = O4dVLL(3,2,3,2)/2._dp - O4dVLLSM(3,2,3,2)/2._dp
coeffBsBs_VRRNP = O4dVRR(3,2,3,2)/2._dp - O4dVRRSM(3,2,3,2)/2._dp
coeffBsBs_VLRNP = O4dVLR(3,2,3,2) - O4dVLRSM(3,2,3,2) + O4dVRL(3,2,3,2) - O4dVRLSM(3,2,3,2)
coeffBsBs_TLLNP = O4dTLL(3,2,3,2)/2._dp - O4dTLLSM(3,2,3,2)/2._dp
coeffBsBs_TRRNP = O4dTRR(3,2,3,2)/2._dp - O4dTRRSM(3,2,3,2)/2._dp
coeffKK_SLLSM = O4dSLLSM(2,1,2,1)/2._dp
coeffKK_SRRSM = O4dSRRSM(2,1,2,1)/2._dp
coeffKK_SLRSM = O4dSLRSM(2,1,2,1) + O4dSRLSM(2,1,2,1)
coeffKK_VLLSM = O4dVLLSM(2,1,2,1)/2._dp
coeffKK_VRRSM = O4dVRRSM(2,1,2,1)/2._dp
coeffKK_VLRSM = O4dVLRSM(2,1,2,1) + O4dVRLSM(2,1,2,1)
coeffKK_TLLSM = O4dTLLSM(2,1,2,1)/2._dp
coeffKK_TRRSM = O4dTRRSM(2,1,2,1)/2._dp
coeffBB_SLLSM = O4dSLLSM(3,1,3,1)/2._dp
coeffBB_SRRSM = O4dSRRSM(3,1,3,1)/2._dp
coeffBB_SLRSM = O4dSLRSM(3,1,3,1) + O4dSRLSM(3,1,3,1)
coeffBB_VLLSM = O4dVLLSM(3,1,3,1)/2._dp
coeffBB_VRRSM = O4dVRRSM(3,1,3,1)/2._dp
coeffBB_VLRSM = O4dVLRSM(3,1,3,1) + O4dVRLSM(3,1,3,1)
coeffBB_TLLSM = O4dTLLSM(3,1,3,1)/2._dp
coeffBB_TRRSM = O4dTRRSM(3,1,3,1)/2._dp
coeffBsBs_SLLSM = O4dSLLSM(3,2,3,2)/2._dp
coeffBsBs_SRRSM = O4dSRRSM(3,2,3,2)/2._dp
coeffBsBs_SLRSM = O4dSLRSM(3,2,3,2) + O4dSRLSM(3,2,3,2)
coeffBsBs_VLLSM = O4dVLLSM(3,2,3,2)/2._dp
coeffBsBs_VRRSM = O4dVRRSM(3,2,3,2)/2._dp
coeffBsBs_VLRSM = O4dVLRSM(3,2,3,2) + O4dVRLSM(3,2,3,2)
coeffBsBs_TLLSM = O4dTLLSM(3,2,3,2)/2._dp
coeffBsBs_TRRSM = O4dTRRSM(3,2,3,2)/2._dp
DVLL_2323 = O4dVLL(2,3,2,3) - O4dVLLSM(2,3,2,3)
DVRR_2323 = O4dVRR(2,3,2,3) - O4dVRRSM(2,3,2,3)
DVLR_2323 = O4dVLR(2,3,2,3) - O4dVLRSM(2,3,2,3)
DSRR_2323 = O4dSRR(2,3,2,3) - O4dSRRSM(2,3,2,3)
DSRR_3232 = O4dSRR(3,2,3,2) - O4dSRRSM(3,2,3,2)
DVLL_1313 = O4dVLL(1,3,1,3) - O4dVLLSM(1,3,1,3)
DVRR_1313 = O4dVRR(1,3,1,3) - O4dVRRSM(1,3,1,3)
DVLR_1313 = O4dVLR(1,3,1,3) - O4dVLRSM(1,3,1,3)
DSRR_1313 = O4dSRR(1,3,1,3) - O4dSRRSM(1,3,1,3)
DSRR_3131 = O4dSRR(3,1,3,1) - O4dSRRSM(3,1,3,1)
DVLL_1212 = O4dVLL(1,2,1,2) - O4dVLLSM(1,2,1,2)
DVRR_1212 = O4dVRR(1,2,1,2) - O4dVRRSM(1,2,1,2)
DVLR_1212 = O4dVLR(1,2,1,2) - O4dVLRSM(1,2,1,2)
DSRR_1212 = O4dSRR(1,2,1,2) - O4dSRRSM(1,2,1,2)
DSRR_2121 = O4dSRR(2,1,2,1) - O4dSRRSM(2,1,2,1)
DVLL_1323 = O4dVLL(1,3,2,3) - O4dVLLSM(1,3,2,3)
DVRR_1323 = O4dVRR(1,3,2,3) - O4dVRRSM(1,3,2,3)
DVLR_1323 = O4dVLR(1,3,2,3) - O4dVLRSM(1,3,2,3)
DVLR_2313 = O4dVLR(2,3,1,3) - O4dVLRSM(2,3,1,3)
DSRR_1323 = O4dSRR(1,3,2,3) - O4dSRRSM(1,3,2,3)
DSRR_3132 = O4dSRR(3,1,3,2) - O4dSRRSM(3,1,3,2)
DVLL_1232 = O4dVLL(1,2,3,2) - O4dVLLSM(1,2,3,2)
DVRR_1232 = O4dVRR(1,2,3,2) - O4dVRRSM(1,2,3,2)
DVLR_1232 = O4dVLR(1,2,3,2) - O4dVLRSM(1,2,3,2)
DVLR_2321 = O4dVLR(2,3,2,1) - O4dVLRSM(2,3,2,1)
DSRR_1232 = O4dSRR(1,2,3,2) - O4dSRRSM(1,2,3,2)
DSRR_2123 = O4dSRR(2,1,2,3) - O4dSRRSM(2,1,2,3)
DVLL_1213 = O4dVLL(1,2,1,3) - O4dVLLSM(1,2,1,3)
DVRR_1213 = O4dVRR(1,2,1,3) - O4dVRRSM(1,2,1,3)
DVLR_1213 = O4dVLR(1,2,1,3) - O4dVLRSM(1,2,1,3)
DVLR_1312 = O4dVLR(1,3,1,2) - O4dVLRSM(1,3,1,2)
DSRR_1213 = O4dSRR(1,2,1,3) - O4dSRRSM(1,2,1,3)
DSRR_2131 = O4dSRR(2,1,3,1) - O4dSRRSM(2,1,3,1)
GVLL_3111 = OdulvVLL(3,1,1,1) - OdulvVLLSM(3,1,1,1)
GVLL_3121 = OdulvVLL(3,1,2,1) - OdulvVLLSM(3,1,2,1)
GVLL_3131 = OdulvVLL(3,1,3,1) - OdulvVLLSM(3,1,3,1)
GVRL_3111 = OdulvVRL(3,1,1,1) - OdulvVRLSM(3,1,1,1)
GVRL_3121 = OdulvVRL(3,1,2,1) - OdulvVRLSM(3,1,2,1)
GVRL_3131 = OdulvVRL(3,1,3,1) - OdulvVRLSM(3,1,3,1)
GSLL_3111 = OdulvSLL(3,1,1,1) - OdulvSLLSM(3,1,1,1)
GSLL_3121 = OdulvSLL(3,1,2,1) - OdulvSLLSM(3,1,2,1)
GSLL_3131 = OdulvSLL(3,1,3,1) - OdulvSLLSM(3,1,3,1)
GSRL_3111 = OdulvSRL(3,1,1,1) - OdulvSRLSM(3,1,1,1)
GSRL_3121 = OdulvSRL(3,1,2,1) - OdulvSRLSM(3,1,2,1)
GSRL_3131 = OdulvSRL(3,1,3,1) - OdulvSRLSM(3,1,3,1)
GVLL_3211 = OdulvVLL(3,2,1,1) - OdulvVLLSM(3,2,1,1)
GVLL_3221 = OdulvVLL(3,2,2,1) - OdulvVLLSM(3,2,2,1)
GVLL_3231 = OdulvVLL(3,2,3,1) - OdulvVLLSM(3,2,3,1)
GVRL_3211 = OdulvVRL(3,2,1,1) - OdulvVRLSM(3,2,1,1)
GVRL_3221 = OdulvVRL(3,2,2,1) - OdulvVRLSM(3,2,2,1)
GVRL_3231 = OdulvVRL(3,2,3,1) - OdulvVRLSM(3,2,3,1)
GSLL_3211 = OdulvSLL(3,2,1,1) - OdulvSLLSM(3,2,1,1)
GSLL_3221 = OdulvSLL(3,2,2,1) - OdulvSLLSM(3,2,2,1)
GSLL_3231 = OdulvSLL(3,2,3,1) - OdulvSLLSM(3,2,3,1)
GSRL_3211 = OdulvSRL(3,2,1,1) - OdulvSRLSM(3,2,1,1)
GSRL_3221 = OdulvSRL(3,2,2,1) - OdulvSRLSM(3,2,2,1)
GSRL_3231 = OdulvSRL(3,2,3,1) - OdulvSRLSM(3,2,3,1)
GVLL_2111 = OdulvVLL(2,1,1,1) - OdulvVLLSM(2,1,1,1)
GVLL_2121 = OdulvVLL(2,1,2,1) - OdulvVLLSM(2,1,2,1)
GVLL_2131 = OdulvVLL(2,1,3,1) - OdulvVLLSM(2,1,3,1)
GVRL_2111 = OdulvVRL(2,1,1,1) - OdulvVRLSM(2,1,1,1)
GVRL_2121 = OdulvVRL(2,1,2,1) - OdulvVRLSM(2,1,2,1)
GVRL_2131 = OdulvVRL(2,1,3,1) - OdulvVRLSM(2,1,3,1)
GSLL_2111 = OdulvSLL(2,1,1,1) - OdulvSLLSM(2,1,1,1)
GSLL_2121 = OdulvSLL(2,1,2,1) - OdulvSLLSM(2,1,2,1)
GSLL_2131 = OdulvSLL(2,1,3,1) - OdulvSLLSM(2,1,3,1)
GSRL_2111 = OdulvSRL(2,1,1,1) - OdulvSRLSM(2,1,1,1)
GSRL_2121 = OdulvSRL(2,1,2,1) - OdulvSRLSM(2,1,2,1)
GSRL_2131 = OdulvSRL(2,1,3,1) - OdulvSRLSM(2,1,3,1)
GVLL_2211 = OdulvVLL(2,2,1,1) - OdulvVLLSM(2,2,1,1)
GVLL_2221 = OdulvVLL(2,2,2,1) - OdulvVLLSM(2,2,2,1)
GVLL_2231 = OdulvVLL(2,2,3,1) - OdulvVLLSM(2,2,3,1)
GVRL_2211 = OdulvVRL(2,2,1,1) - OdulvVRLSM(2,2,1,1)
GVRL_2221 = OdulvVRL(2,2,2,1) - OdulvVRLSM(2,2,2,1)
GVRL_2231 = OdulvVRL(2,2,3,1) - OdulvVRLSM(2,2,3,1)
GSLL_2211 = OdulvSLL(2,2,1,1) - OdulvSLLSM(2,2,1,1)
GSLL_2221 = OdulvSLL(2,2,2,1) - OdulvSLLSM(2,2,2,1)
GSLL_2231 = OdulvSLL(2,2,3,1) - OdulvSLLSM(2,2,3,1)
GSRL_2211 = OdulvSRL(2,2,1,1) - OdulvSRLSM(2,2,1,1)
GSRL_2221 = OdulvSRL(2,2,2,1) - OdulvSRLSM(2,2,2,1)
GSRL_2231 = OdulvSRL(2,2,3,1) - OdulvSRLSM(2,2,3,1)
GVLL_1111 = OdulvVLL(1,1,1,1) - OdulvVLLSM(1,1,1,1)
GVLL_1121 = OdulvVLL(1,1,2,1) - OdulvVLLSM(1,1,2,1)
GVLL_1131 = OdulvVLL(1,1,3,1) - OdulvVLLSM(1,1,3,1)
GVRL_1111 = OdulvVRL(1,1,1,1) - OdulvVRLSM(1,1,1,1)
GVRL_1121 = OdulvVRL(1,1,2,1) - OdulvVRLSM(1,1,2,1)
GVRL_1131 = OdulvVRL(1,1,3,1) - OdulvVRLSM(1,1,3,1)
GSLL_1111 = OdulvSLL(1,1,1,1) - OdulvSLLSM(1,1,1,1)
GSLL_1121 = OdulvSLL(1,1,2,1) - OdulvSLLSM(1,1,2,1)
GSLL_1131 = OdulvSLL(1,1,3,1) - OdulvSLLSM(1,1,3,1)
GSRL_1111 = OdulvSRL(1,1,1,1) - OdulvSRLSM(1,1,1,1)
GSRL_1121 = OdulvSRL(1,1,2,1) - OdulvSRLSM(1,1,2,1)
GSRL_1131 = OdulvSRL(1,1,3,1) - OdulvSRLSM(1,1,3,1)
GVLL_1211 = OdulvVLL(1,2,1,1) - OdulvVLLSM(1,2,1,1)
GVLL_1221 = OdulvVLL(1,2,2,1) - OdulvVLLSM(1,2,2,1)
GVLL_1231 = OdulvVLL(1,2,3,1) - OdulvVLLSM(1,2,3,1)
GVRL_1211 = OdulvVRL(1,2,1,1) - OdulvVRLSM(1,2,1,1)
GVRL_1221 = OdulvVRL(1,2,2,1) - OdulvVRLSM(1,2,2,1)
GVRL_1231 = OdulvVRL(1,2,3,1) - OdulvVRLSM(1,2,3,1)
GSLL_1211 = OdulvSLL(1,2,1,1) - OdulvSLLSM(1,2,1,1)
GSLL_1221 = OdulvSLL(1,2,2,1) - OdulvSLLSM(1,2,2,1)
GSLL_1231 = OdulvSLL(1,2,3,1) - OdulvSLLSM(1,2,3,1)
GSRL_1211 = OdulvSRL(1,2,1,1) - OdulvSRLSM(1,2,1,1)
GSRL_1221 = OdulvSRL(1,2,2,1) - OdulvSRLSM(1,2,2,1)
GSRL_1231 = OdulvSRL(1,2,3,1) - OdulvSRLSM(1,2,3,1)
GVLL_3112 = OdulvVLL(3,1,1,2) - OdulvVLLSM(3,1,1,2)
GVLL_3122 = OdulvVLL(3,1,2,2) - OdulvVLLSM(3,1,2,2)
GVLL_3132 = OdulvVLL(3,1,3,2) - OdulvVLLSM(3,1,3,2)
GVRL_3112 = OdulvVRL(3,1,1,2) - OdulvVRLSM(3,1,1,2)
GVRL_3122 = OdulvVRL(3,1,2,2) - OdulvVRLSM(3,1,2,2)
GVRL_3132 = OdulvVRL(3,1,3,2) - OdulvVRLSM(3,1,3,2)
GSLL_3112 = OdulvSLL(3,1,1,2) - OdulvSLLSM(3,1,1,2)
GSLL_3122 = OdulvSLL(3,1,2,2) - OdulvSLLSM(3,1,2,2)
GSLL_3132 = OdulvSLL(3,1,3,2) - OdulvSLLSM(3,1,3,2)
GSRL_3112 = OdulvSRL(3,1,1,2) - OdulvSRLSM(3,1,1,2)
GSRL_3122 = OdulvSRL(3,1,2,2) - OdulvSRLSM(3,1,2,2)
GSRL_3132 = OdulvSRL(3,1,3,2) - OdulvSRLSM(3,1,3,2)
GVLL_3212 = OdulvVLL(3,2,1,2) - OdulvVLLSM(3,2,1,2)
GVLL_3222 = OdulvVLL(3,2,2,2) - OdulvVLLSM(3,2,2,2)
GVLL_3232 = OdulvVLL(3,2,3,2) - OdulvVLLSM(3,2,3,2)
GVRL_3212 = OdulvVRL(3,2,1,2) - OdulvVRLSM(3,2,1,2)
GVRL_3222 = OdulvVRL(3,2,2,2) - OdulvVRLSM(3,2,2,2)
GVRL_3232 = OdulvVRL(3,2,3,2) - OdulvVRLSM(3,2,3,2)
GSLL_3212 = OdulvSLL(3,2,1,2) - OdulvSLLSM(3,2,1,2)
GSLL_3222 = OdulvSLL(3,2,2,2) - OdulvSLLSM(3,2,2,2)
GSLL_3232 = OdulvSLL(3,2,3,2) - OdulvSLLSM(3,2,3,2)
GSRL_3212 = OdulvSRL(3,2,1,2) - OdulvSRLSM(3,2,1,2)
GSRL_3222 = OdulvSRL(3,2,2,2) - OdulvSRLSM(3,2,2,2)
GSRL_3232 = OdulvSRL(3,2,3,2) - OdulvSRLSM(3,2,3,2)
GVLL_2112 = OdulvVLL(2,1,1,2) - OdulvVLLSM(2,1,1,2)
GVLL_2122 = OdulvVLL(2,1,2,2) - OdulvVLLSM(2,1,2,2)
GVLL_2132 = OdulvVLL(2,1,3,2) - OdulvVLLSM(2,1,3,2)
GVRL_2112 = OdulvVRL(2,1,1,2) - OdulvVRLSM(2,1,1,2)
GVRL_2122 = OdulvVRL(2,1,2,2) - OdulvVRLSM(2,1,2,2)
GVRL_2132 = OdulvVRL(2,1,3,2) - OdulvVRLSM(2,1,3,2)
GSLL_2112 = OdulvSLL(2,1,1,2) - OdulvSLLSM(2,1,1,2)
GSLL_2122 = OdulvSLL(2,1,2,2) - OdulvSLLSM(2,1,2,2)
GSLL_2132 = OdulvSLL(2,1,3,2) - OdulvSLLSM(2,1,3,2)
GSRL_2112 = OdulvSRL(2,1,1,2) - OdulvSRLSM(2,1,1,2)
GSRL_2122 = OdulvSRL(2,1,2,2) - OdulvSRLSM(2,1,2,2)
GSRL_2132 = OdulvSRL(2,1,3,2) - OdulvSRLSM(2,1,3,2)
GVLL_2212 = OdulvVLL(2,2,1,2) - OdulvVLLSM(2,2,1,2)
GVLL_2222 = OdulvVLL(2,2,2,2) - OdulvVLLSM(2,2,2,2)
GVLL_2232 = OdulvVLL(2,2,3,2) - OdulvVLLSM(2,2,3,2)
GVRL_2212 = OdulvVRL(2,2,1,2) - OdulvVRLSM(2,2,1,2)
GVRL_2222 = OdulvVRL(2,2,2,2) - OdulvVRLSM(2,2,2,2)
GVRL_2232 = OdulvVRL(2,2,3,2) - OdulvVRLSM(2,2,3,2)
GSLL_2212 = OdulvSLL(2,2,1,2) - OdulvSLLSM(2,2,1,2)
GSLL_2222 = OdulvSLL(2,2,2,2) - OdulvSLLSM(2,2,2,2)
GSLL_2232 = OdulvSLL(2,2,3,2) - OdulvSLLSM(2,2,3,2)
GSRL_2212 = OdulvSRL(2,2,1,2) - OdulvSRLSM(2,2,1,2)
GSRL_2222 = OdulvSRL(2,2,2,2) - OdulvSRLSM(2,2,2,2)
GSRL_2232 = OdulvSRL(2,2,3,2) - OdulvSRLSM(2,2,3,2)
GVLL_1112 = OdulvVLL(1,1,1,2) - OdulvVLLSM(1,1,1,2)
GVLL_1122 = OdulvVLL(1,1,2,2) - OdulvVLLSM(1,1,2,2)
GVLL_1132 = OdulvVLL(1,1,3,2) - OdulvVLLSM(1,1,3,2)
GVRL_1112 = OdulvVRL(1,1,1,2) - OdulvVRLSM(1,1,1,2)
GVRL_1122 = OdulvVRL(1,1,2,2) - OdulvVRLSM(1,1,2,2)
GVRL_1132 = OdulvVRL(1,1,3,2) - OdulvVRLSM(1,1,3,2)
GSLL_1112 = OdulvSLL(1,1,1,2) - OdulvSLLSM(1,1,1,2)
GSLL_1122 = OdulvSLL(1,1,2,2) - OdulvSLLSM(1,1,2,2)
GSLL_1132 = OdulvSLL(1,1,3,2) - OdulvSLLSM(1,1,3,2)
GSRL_1112 = OdulvSRL(1,1,1,2) - OdulvSRLSM(1,1,1,2)
GSRL_1122 = OdulvSRL(1,1,2,2) - OdulvSRLSM(1,1,2,2)
GSRL_1132 = OdulvSRL(1,1,3,2) - OdulvSRLSM(1,1,3,2)
GVLL_1212 = OdulvVLL(1,2,1,2) - OdulvVLLSM(1,2,1,2)
GVLL_1222 = OdulvVLL(1,2,2,2) - OdulvVLLSM(1,2,2,2)
GVLL_1232 = OdulvVLL(1,2,3,2) - OdulvVLLSM(1,2,3,2)
GVRL_1212 = OdulvVRL(1,2,1,2) - OdulvVRLSM(1,2,1,2)
GVRL_1222 = OdulvVRL(1,2,2,2) - OdulvVRLSM(1,2,2,2)
GVRL_1232 = OdulvVRL(1,2,3,2) - OdulvVRLSM(1,2,3,2)
GSLL_1212 = OdulvSLL(1,2,1,2) - OdulvSLLSM(1,2,1,2)
GSLL_1222 = OdulvSLL(1,2,2,2) - OdulvSLLSM(1,2,2,2)
GSLL_1232 = OdulvSLL(1,2,3,2) - OdulvSLLSM(1,2,3,2)
GSRL_1212 = OdulvSRL(1,2,1,2) - OdulvSRLSM(1,2,1,2)
GSRL_1222 = OdulvSRL(1,2,2,2) - OdulvSRLSM(1,2,2,2)
GSRL_1232 = OdulvSRL(1,2,3,2) - OdulvSRLSM(1,2,3,2)
GVLL_3113 = OdulvVLL(3,1,1,3) - OdulvVLLSM(3,1,1,3)
GVLL_3123 = OdulvVLL(3,1,2,3) - OdulvVLLSM(3,1,2,3)
GVLL_3133 = OdulvVLL(3,1,3,3) - OdulvVLLSM(3,1,3,3)
GVRL_3113 = OdulvVRL(3,1,1,3) - OdulvVRLSM(3,1,1,3)
GVRL_3123 = OdulvVRL(3,1,2,3) - OdulvVRLSM(3,1,2,3)
GVRL_3133 = OdulvVRL(3,1,3,3) - OdulvVRLSM(3,1,3,3)
GSLL_3113 = OdulvSLL(3,1,1,3) - OdulvSLLSM(3,1,1,3)
GSLL_3123 = OdulvSLL(3,1,2,3) - OdulvSLLSM(3,1,2,3)
GSLL_3133 = OdulvSLL(3,1,3,3) - OdulvSLLSM(3,1,3,3)
GSRL_3113 = OdulvSRL(3,1,1,3) - OdulvSRLSM(3,1,1,3)
GSRL_3123 = OdulvSRL(3,1,2,3) - OdulvSRLSM(3,1,2,3)
GSRL_3133 = OdulvSRL(3,1,3,3) - OdulvSRLSM(3,1,3,3)
GVLL_3213 = OdulvVLL(3,2,1,3) - OdulvVLLSM(3,2,1,3)
GVLL_3223 = OdulvVLL(3,2,2,3) - OdulvVLLSM(3,2,2,3)
GVLL_3233 = OdulvVLL(3,2,3,3) - OdulvVLLSM(3,2,3,3)
GVRL_3213 = OdulvVRL(3,2,1,3) - OdulvVRLSM(3,2,1,3)
GVRL_3223 = OdulvVRL(3,2,2,3) - OdulvVRLSM(3,2,2,3)
GVRL_3233 = OdulvVRL(3,2,3,3) - OdulvVRLSM(3,2,3,3)
GSLL_3213 = OdulvSLL(3,2,1,3) - OdulvSLLSM(3,2,1,3)
GSLL_3223 = OdulvSLL(3,2,2,3) - OdulvSLLSM(3,2,2,3)
GSLL_3233 = OdulvSLL(3,2,3,3) - OdulvSLLSM(3,2,3,3)
GSRL_3213 = OdulvSRL(3,2,1,3) - OdulvSRLSM(3,2,1,3)
GSRL_3223 = OdulvSRL(3,2,2,3) - OdulvSRLSM(3,2,2,3)
GSRL_3233 = OdulvSRL(3,2,3,3) - OdulvSRLSM(3,2,3,3)
GVLL_2113 = OdulvVLL(2,1,1,3) - OdulvVLLSM(2,1,1,3)
GVLL_2123 = OdulvVLL(2,1,2,3) - OdulvVLLSM(2,1,2,3)
GVLL_2133 = OdulvVLL(2,1,3,3) - OdulvVLLSM(2,1,3,3)
GVRL_2113 = OdulvVRL(2,1,1,3) - OdulvVRLSM(2,1,1,3)
GVRL_2123 = OdulvVRL(2,1,2,3) - OdulvVRLSM(2,1,2,3)
GVRL_2133 = OdulvVRL(2,1,3,3) - OdulvVRLSM(2,1,3,3)
GSLL_2113 = OdulvSLL(2,1,1,3) - OdulvSLLSM(2,1,1,3)
GSLL_2123 = OdulvSLL(2,1,2,3) - OdulvSLLSM(2,1,2,3)
GSLL_2133 = OdulvSLL(2,1,3,3) - OdulvSLLSM(2,1,3,3)
GSRL_2113 = OdulvSRL(2,1,1,3) - OdulvSRLSM(2,1,1,3)
GSRL_2123 = OdulvSRL(2,1,2,3) - OdulvSRLSM(2,1,2,3)
GSRL_2133 = OdulvSRL(2,1,3,3) - OdulvSRLSM(2,1,3,3)
GVLL_2213 = OdulvVLL(2,2,1,3) - OdulvVLLSM(2,2,1,3)
GVLL_2223 = OdulvVLL(2,2,2,3) - OdulvVLLSM(2,2,2,3)
GVLL_2233 = OdulvVLL(2,2,3,3) - OdulvVLLSM(2,2,3,3)
GVRL_2213 = OdulvVRL(2,2,1,3) - OdulvVRLSM(2,2,1,3)
GVRL_2223 = OdulvVRL(2,2,2,3) - OdulvVRLSM(2,2,2,3)
GVRL_2233 = OdulvVRL(2,2,3,3) - OdulvVRLSM(2,2,3,3)
GSLL_2213 = OdulvSLL(2,2,1,3) - OdulvSLLSM(2,2,1,3)
GSLL_2223 = OdulvSLL(2,2,2,3) - OdulvSLLSM(2,2,2,3)
GSLL_2233 = OdulvSLL(2,2,3,3) - OdulvSLLSM(2,2,3,3)
GSRL_2213 = OdulvSRL(2,2,1,3) - OdulvSRLSM(2,2,1,3)
GSRL_2223 = OdulvSRL(2,2,2,3) - OdulvSRLSM(2,2,2,3)
GSRL_2233 = OdulvSRL(2,2,3,3) - OdulvSRLSM(2,2,3,3)
GVLL_1113 = OdulvVLL(1,1,1,3) - OdulvVLLSM(1,1,1,3)
GVLL_1123 = OdulvVLL(1,1,2,3) - OdulvVLLSM(1,1,2,3)
GVLL_1133 = OdulvVLL(1,1,3,3) - OdulvVLLSM(1,1,3,3)
GVRL_1113 = OdulvVRL(1,1,1,3) - OdulvVRLSM(1,1,1,3)
GVRL_1123 = OdulvVRL(1,1,2,3) - OdulvVRLSM(1,1,2,3)
GVRL_1133 = OdulvVRL(1,1,3,3) - OdulvVRLSM(1,1,3,3)
GSLL_1113 = OdulvSLL(1,1,1,3) - OdulvSLLSM(1,1,1,3)
GSLL_1123 = OdulvSLL(1,1,2,3) - OdulvSLLSM(1,1,2,3)
GSLL_1133 = OdulvSLL(1,1,3,3) - OdulvSLLSM(1,1,3,3)
GSRL_1113 = OdulvSRL(1,1,1,3) - OdulvSRLSM(1,1,1,3)
GSRL_1123 = OdulvSRL(1,1,2,3) - OdulvSRLSM(1,1,2,3)
GSRL_1133 = OdulvSRL(1,1,3,3) - OdulvSRLSM(1,1,3,3)
GVLL_1213 = OdulvVLL(1,2,1,3) - OdulvVLLSM(1,2,1,3)
GVLL_1223 = OdulvVLL(1,2,2,3) - OdulvVLLSM(1,2,2,3)
GVLL_1233 = OdulvVLL(1,2,3,3) - OdulvVLLSM(1,2,3,3)
GVRL_1213 = OdulvVRL(1,2,1,3) - OdulvVRLSM(1,2,1,3)
GVRL_1223 = OdulvVRL(1,2,2,3) - OdulvVRLSM(1,2,2,3)
GVRL_1233 = OdulvVRL(1,2,3,3) - OdulvVRLSM(1,2,3,3)
GSLL_1213 = OdulvSLL(1,2,1,3) - OdulvSLLSM(1,2,1,3)
GSLL_1223 = OdulvSLL(1,2,2,3) - OdulvSLLSM(1,2,2,3)
GSLL_1233 = OdulvSLL(1,2,3,3) - OdulvSLLSM(1,2,3,3)
GSRL_1213 = OdulvSRL(1,2,1,3) - OdulvSRLSM(1,2,1,3)
GSRL_1223 = OdulvSRL(1,2,2,3) - OdulvSRLSM(1,2,2,3)
GSRL_1233 = OdulvSRL(1,2,3,3) - OdulvSRLSM(1,2,3,3)
FVLL_2311 = OddvvVLL(2,3,1,1) - OddvvVLLSM(2,3,1,1)
FVLL_2322 = OddvvVLL(2,3,2,2) - OddvvVLLSM(2,3,2,2)
FVLL_2333 = OddvvVLL(2,3,3,3) - OddvvVLLSM(2,3,3,3)
FVLL_2312 = OddvvVLL(2,3,1,2) - OddvvVLLSM(2,3,1,2)
FVLL_2313 = OddvvVLL(2,3,1,3) - OddvvVLLSM(2,3,1,3)
FVLL_2323 = OddvvVLL(2,3,2,3) - OddvvVLLSM(2,3,2,3)
FVLL_3212 = OddvvVLL(3,2,1,2) - OddvvVLLSM(3,2,1,2)
FVLL_3213 = OddvvVLL(3,2,1,3) - OddvvVLLSM(3,2,1,3)
FVLL_3223 = OddvvVLL(3,2,2,3) - OddvvVLLSM(3,2,2,3)
FVRL_2311 = OddvvVRL(2,3,1,1) - OddvvVRLSM(2,3,1,1)
FVRL_2322 = OddvvVRL(2,3,2,2) - OddvvVRLSM(2,3,2,2)
FVRL_2333 = OddvvVRL(2,3,3,3) - OddvvVRLSM(2,3,3,3)
FVRL_2312 = OddvvVRL(2,3,1,2) - OddvvVRLSM(2,3,1,2)
FVRL_2313 = OddvvVRL(2,3,1,3) - OddvvVRLSM(2,3,1,3)
FVRL_2323 = OddvvVRL(2,3,2,3) - OddvvVRLSM(2,3,2,3)
FVRL_3212 = OddvvVRL(3,2,1,2) - OddvvVRLSM(3,2,1,2)
FVRL_3213 = OddvvVRL(3,2,1,3) - OddvvVRLSM(3,2,1,3)
FVRL_3223 = OddvvVRL(3,2,2,3) - OddvvVRLSM(3,2,2,3)
FVLL_1311 = OddvvVLL(1,3,1,1) - OddvvVLLSM(1,3,1,1)
FVLL_1322 = OddvvVLL(1,3,2,2) - OddvvVLLSM(1,3,2,2)
FVLL_1333 = OddvvVLL(1,3,3,3) - OddvvVLLSM(1,3,3,3)
FVLL_1312 = OddvvVLL(1,3,1,2) - OddvvVLLSM(1,3,1,2)
FVLL_1313 = OddvvVLL(1,3,1,3) - OddvvVLLSM(1,3,1,3)
FVLL_1323 = OddvvVLL(1,3,2,3) - OddvvVLLSM(1,3,2,3)
FVLL_3112 = OddvvVLL(3,1,1,2) - OddvvVLLSM(3,1,1,2)
FVLL_3113 = OddvvVLL(3,1,1,3) - OddvvVLLSM(3,1,1,3)
FVLL_3123 = OddvvVLL(3,1,2,3) - OddvvVLLSM(3,1,2,3)
FVRL_1311 = OddvvVRL(1,3,1,1) - OddvvVRLSM(1,3,1,1)
FVRL_1322 = OddvvVRL(1,3,2,2) - OddvvVRLSM(1,3,2,2)
FVRL_1333 = OddvvVRL(1,3,3,3) - OddvvVRLSM(1,3,3,3)
FVRL_1312 = OddvvVRL(1,3,1,2) - OddvvVRLSM(1,3,1,2)
FVRL_1313 = OddvvVRL(1,3,1,3) - OddvvVRLSM(1,3,1,3)
FVRL_1323 = OddvvVRL(1,3,2,3) - OddvvVRLSM(1,3,2,3)
FVRL_3112 = OddvvVRL(3,1,1,2) - OddvvVRLSM(3,1,1,2)
FVRL_3113 = OddvvVRL(3,1,1,3) - OddvvVRLSM(3,1,1,3)
FVRL_3123 = OddvvVRL(3,1,2,3) - OddvvVRLSM(3,1,2,3)
FVLL_2111 = OddvvVLL(2,1,1,1) - OddvvVLLSM(2,1,1,1)
FVLL_2122 = OddvvVLL(2,1,2,2) - OddvvVLLSM(2,1,2,2)
FVLL_2133 = OddvvVLL(2,1,3,3) - OddvvVLLSM(2,1,3,3)
FVLL_2112 = OddvvVLL(2,1,1,2) - OddvvVLLSM(2,1,1,2)
FVLL_2113 = OddvvVLL(2,1,1,3) - OddvvVLLSM(2,1,1,3)
FVLL_2123 = OddvvVLL(2,1,2,3) - OddvvVLLSM(2,1,2,3)
FVLL_1212 = OddvvVLL(1,2,1,2) - OddvvVLLSM(1,2,1,2)
FVLL_1213 = OddvvVLL(1,2,1,3) - OddvvVLLSM(1,2,1,3)
FVLL_1223 = OddvvVLL(1,2,2,3) - OddvvVLLSM(1,2,2,3)
FVRL_2111 = OddvvVRL(2,1,1,1) - OddvvVRLSM(2,1,1,1)
FVRL_2122 = OddvvVRL(2,1,2,2) - OddvvVRLSM(2,1,2,2)
FVRL_2133 = OddvvVRL(2,1,3,3) - OddvvVRLSM(2,1,3,3)
FVRL_2112 = OddvvVRL(2,1,1,2) - OddvvVRLSM(2,1,1,2)
FVRL_2113 = OddvvVRL(2,1,1,3) - OddvvVRLSM(2,1,1,3)
FVRL_2123 = OddvvVRL(2,1,2,3) - OddvvVRLSM(2,1,2,3)
FVRL_1212 = OddvvVRL(1,2,1,2) - OddvvVRLSM(1,2,1,2)
FVRL_1213 = OddvvVRL(1,2,1,3) - OddvvVRLSM(1,2,1,3)
FVRL_1223 = OddvvVRL(1,2,2,3) - OddvvVRLSM(1,2,2,3)
Q1R_23 = CC7p(2,3) - CC7pSM(2,3)
Q1R_32 = CC7p(3,2) - CC7pSM(3,2)
Q2R_23 = CC8p(2,3) - CC8pSM(2,3)
Q2R_32 = CC8p(3,2) - CC8pSM(3,2)
DVLL_2311 = O4dVLL(2,3,1,1) - O4dVLLSM(2,3,1,1)
DVLL_2322 = O4dVLL(2,3,2,2) - O4dVLLSM(2,3,2,2)
DVLL_2333 = O4dVLL(2,3,3,3) - O4dVLLSM(2,3,3,3)
DVLL_1231 = O4dVLL(1,2,3,1) - O4dVLLSM(1,2,3,1)
DVRR_2311 = O4dVRR(2,3,1,1) - O4dVRRSM(2,3,1,1)
DVRR_2322 = O4dVRR(2,3,2,2) - O4dVRRSM(2,3,2,2)
DVRR_2333 = O4dVRR(2,3,3,3) - O4dVRRSM(2,3,3,3)
DVRR_1231 = O4dVRR(1,2,3,1) - O4dVRRSM(1,2,3,1)
DVLR_2311 = O4dVLR(2,3,1,1) - O4dVLRSM(2,3,1,1)
DVLR_2322 = O4dVLR(2,3,2,2) - O4dVLRSM(2,3,2,2)
DVLR_2333 = O4dVLR(2,3,3,3) - O4dVLRSM(2,3,3,3)
DVRL_2311 = O4dVRL(2,3,1,1) - O4dVRLSM(2,3,1,1)
DVRL_2322 = O4dVRL(2,3,2,2) - O4dVRLSM(2,3,2,2)
DVRL_2333 = O4dVRL(2,3,3,3) - O4dVRLSM(2,3,3,3)
DVLR_1231 = O4dVLR(1,2,3,1) - O4dVLRSM(1,2,3,1)
DVLR_1321 = O4dVLR(1,3,2,1) - O4dVLRSM(1,3,2,1)
DSRR_2311 = O4dSRR(2,3,1,1) - O4dSRRSM(2,3,1,1)
DSRR_2322 = O4dSRR(2,3,2,2) - O4dSRRSM(2,3,2,2)
DSRR_2333 = O4dSRR(2,3,3,3) - O4dSRRSM(2,3,3,3)
DSRR_3211 = O4dSRR(3,2,1,1) - O4dSRRSM(3,2,1,1)
DSRR_3222 = O4dSRR(3,2,2,2) - O4dSRRSM(3,2,2,2)
DSRR_3233 = O4dSRR(3,2,3,3) - O4dSRRSM(3,2,3,3)
DSRR_1231 = O4dSRR(1,2,3,1) - O4dSRRSM(1,2,3,1)
DSRR_1321 = O4dSRR(1,3,2,1) - O4dSRRSM(1,3,2,1)
EVLL_2311 = OddllVLL(2,3,1,1) - OddllVLLSM(2,3,1,1)
EVLL_2322 = OddllVLL(2,3,2,2) - OddllVLLSM(2,3,2,2)
EVLL_2333 = OddllVLL(2,3,3,3) - OddllVLLSM(2,3,3,3)
EVRR_2311 = OddllVRR(2,3,1,1) - OddllVRRSM(2,3,1,1)
EVRR_2322 = OddllVRR(2,3,2,2) - OddllVRRSM(2,3,2,2)
EVRR_2333 = OddllVRR(2,3,3,3) - OddllVRRSM(2,3,3,3)
EVLR_2311 = OddllVLR(2,3,1,1) - OddllVLRSM(2,3,1,1)
EVLR_2322 = OddllVLR(2,3,2,2) - OddllVLRSM(2,3,2,2)
EVLR_2333 = OddllVLR(2,3,3,3) - OddllVLRSM(2,3,3,3)
EVRL_2311 = OddllVRL(2,3,1,1) - OddllVRLSM(2,3,1,1)
EVRL_2322 = OddllVRL(2,3,2,2) - OddllVRLSM(2,3,2,2)
EVRL_2333 = OddllVRL(2,3,3,3) - OddllVRLSM(2,3,3,3)
ESRR_2311 = OddllSRR(2,3,1,1) - OddllSRRSM(2,3,1,1)
ESRR_2322 = OddllSRR(2,3,2,2) - OddllSRRSM(2,3,2,2)
ESRR_2333 = OddllSRR(2,3,3,3) - OddllSRRSM(2,3,3,3)
ESRR_3211 = OddllSRR(3,2,1,1) - OddllSRRSM(3,2,1,1)
ESRR_3222 = OddllSRR(3,2,2,2) - OddllSRRSM(3,2,2,2)
ESRR_3233 = OddllSRR(3,2,3,3) - OddllSRRSM(3,2,3,3)
ESLR_2311 = OddllSLR(2,3,1,1) - OddllSLRSM(2,3,1,1)
ESLR_2322 = OddllSLR(2,3,2,2) - OddllSLRSM(2,3,2,2)
ESLR_2333 = OddllSLR(2,3,3,3) - OddllSLRSM(2,3,3,3)
ESLR_3211 = OddllSLR(3,2,1,1) - OddllSLRSM(3,2,1,1)
ESLR_3222 = OddllSLR(3,2,2,2) - OddllSLRSM(3,2,2,2)
ESLR_3233 = OddllSLR(3,2,3,3) - OddllSLRSM(3,2,3,3)
ETRR_2311 = OddllTRR(2,3,1,1) - OddllTRRSM(2,3,1,1)
ETRR_2322 = OddllTRR(2,3,2,2) - OddllTRRSM(2,3,2,2)
ETRR_2333 = OddllTRR(2,3,3,3) - OddllTRRSM(2,3,3,3)
ETRR_3211 = OddllTRR(3,2,1,1) - OddllTRRSM(3,2,1,1)
ETRR_3222 = OddllTRR(3,2,2,2) - OddllTRRSM(3,2,2,2)
ETRR_3233 = OddllTRR(3,2,3,3) - OddllTRRSM(3,2,3,3)
Q1R_13 = CC7p(1,3) - CC7pSM(1,3)
Q1R_31 = CC7p(3,1) - CC7pSM(3,1)
Q2R_13 = CC8p(1,3) - CC8pSM(1,3)
Q2R_31 = CC8p(3,1) - CC8pSM(3,1)
DVLL_1311 = O4dVLL(1,3,1,1) - O4dVLLSM(1,3,1,1)
DVLL_1322 = O4dVLL(1,3,2,2) - O4dVLLSM(1,3,2,2)
DVLL_1333 = O4dVLL(1,3,3,3) - O4dVLLSM(1,3,3,3)
DVLL_2132 = O4dVLL(2,1,3,2) - O4dVLLSM(2,1,3,2)
DVRR_1311 = O4dVRR(1,3,1,1) - O4dVRRSM(1,3,1,1)
DVRR_1322 = O4dVRR(1,3,2,2) - O4dVRRSM(1,3,2,2)
DVRR_1333 = O4dVRR(1,3,3,3) - O4dVRRSM(1,3,3,3)
DVRR_2132 = O4dVRR(2,1,3,2) - O4dVRRSM(2,1,3,2)
DVLR_1311 = O4dVLR(1,3,1,1) - O4dVLRSM(1,3,1,1)
DVLR_1322 = O4dVLR(1,3,2,2) - O4dVLRSM(1,3,2,2)
DVLR_1333 = O4dVLR(1,3,3,3) - O4dVLRSM(1,3,3,3)
DVRL_1311 = O4dVRL(1,3,1,1) - O4dVRLSM(1,3,1,1)
DVRL_1322 = O4dVRL(1,3,2,2) - O4dVRLSM(1,3,2,2)
DVRL_1333 = O4dVRL(1,3,3,3) - O4dVRLSM(1,3,3,3)
DVLR_2132 = O4dVLR(2,1,3,2) - O4dVLRSM(2,1,3,2)
DVLR_2312 = O4dVLR(2,3,1,2) - O4dVLRSM(2,3,1,2)
DSRR_1311 = O4dSRR(1,3,1,1) - O4dSRRSM(1,3,1,1)
DSRR_1322 = O4dSRR(1,3,2,2) - O4dSRRSM(1,3,2,2)
DSRR_1333 = O4dSRR(1,3,3,3) - O4dSRRSM(1,3,3,3)
DSRR_3111 = O4dSRR(3,1,1,1) - O4dSRRSM(3,1,1,1)
DSRR_3122 = O4dSRR(3,1,2,2) - O4dSRRSM(3,1,2,2)
DSRR_3133 = O4dSRR(3,1,3,3) - O4dSRRSM(3,1,3,3)
DSRR_2132 = O4dSRR(2,1,3,2) - O4dSRRSM(2,1,3,2)
DSRR_2312 = O4dSRR(2,3,1,2) - O4dSRRSM(2,3,1,2)
EVLL_1311 = Conjg(OddllVLL(3,1,1,1)) - Conjg(OddllVLLSM(3,1,1,1))
EVLL_1322 = Conjg(OddllVLL(3,1,2,2)) - Conjg(OddllVLLSM(3,1,2,2))
EVLL_1333 = Conjg(OddllVLL(3,1,3,3)) - Conjg(OddllVLLSM(3,1,3,3))
EVRR_1311 = OddllVRR(1,3,1,1) - OddllVRRSM(1,3,1,1)
EVRR_1322 = OddllVRR(1,3,2,2) - OddllVRRSM(1,3,2,2)
EVRR_1333 = OddllVRR(1,3,3,3) - OddllVRRSM(1,3,3,3)
EVLR_1311 = OddllVLR(1,3,1,1) - OddllVLRSM(1,3,1,1)
EVLR_1322 = OddllVLR(1,3,2,2) - OddllVLRSM(1,3,2,2)
EVLR_1333 = OddllVLR(1,3,3,3) - OddllVLRSM(1,3,3,3)
EVRL_1311 = OddllVRL(1,3,1,1) - OddllVRLSM(1,3,1,1)
EVRL_1322 = OddllVRL(1,3,2,2) - OddllVRLSM(1,3,2,2)
EVRL_1333 = OddllVRL(1,3,3,3) - OddllVRLSM(1,3,3,3)
ESRR_1311 = OddllSRR(1,3,1,1) - OddllSRRSM(1,3,1,1)
ESRR_1322 = OddllSRR(1,3,2,2) - OddllSRRSM(1,3,2,2)
ESRR_1333 = OddllSRR(1,3,3,3) - OddllSRRSM(1,3,3,3)
ESRR_3111 = OddllSRR(3,1,1,1) - OddllSRRSM(3,1,1,1)
ESRR_3122 = OddllSRR(3,1,2,2) - OddllSRRSM(3,1,2,2)
ESRR_3133 = OddllSRR(3,1,3,3) - OddllSRRSM(3,1,3,3)
ESLR_1311 = OddllSLR(1,3,1,1) - OddllSLRSM(1,3,1,1)
ESLR_1322 = OddllSLR(1,3,2,2) - OddllSLRSM(1,3,2,2)
ESLR_1333 = OddllSLR(1,3,3,3) - OddllSLRSM(1,3,3,3)
ESLR_3111 = OddllSLR(3,1,1,1) - OddllSLRSM(3,1,1,1)
ESLR_3122 = OddllSLR(3,1,2,2) - OddllSLRSM(3,1,2,2)
ESLR_3133 = OddllSLR(3,1,3,3) - OddllSLRSM(3,1,3,3)
ETRR_1311 = OddllTRR(1,3,1,1) - OddllTRRSM(1,3,1,1)
ETRR_1322 = OddllTRR(1,3,2,2) - OddllTRRSM(1,3,2,2)
ETRR_1333 = OddllTRR(1,3,3,3) - OddllTRRSM(1,3,3,3)
ETRR_3111 = OddllTRR(3,1,1,1) - OddllTRRSM(3,1,1,1)
ETRR_3122 = OddllTRR(3,1,2,2) - OddllTRRSM(3,1,2,2)
ETRR_3133 = OddllTRR(3,1,3,3) - OddllTRRSM(3,1,3,3)
Q1R_12 = CC7p(1,2) - CC7pSM(1,2)
Q1R_21 = CC7p(2,1) - CC7pSM(2,1)
Q2R_12 = CC8p(1,2) - CC8pSM(1,2)
Q2R_21 = CC8p(2,1) - CC8pSM(2,1)
DVLL_1211 = O4dVLL(1,2,1,1) - O4dVLLSM(1,2,1,1)
DVLL_1222 = O4dVLL(1,2,2,2) - O4dVLLSM(1,2,2,2)
DVLL_1233 = O4dVLL(1,2,3,3) - O4dVLLSM(1,2,3,3)
DVLL_3123 = O4dVLL(3,1,2,3) - O4dVLLSM(3,1,2,3)
DVRR_1211 = O4dVRR(1,2,1,1) - O4dVRRSM(1,2,1,1)
DVRR_1222 = O4dVRR(1,2,2,2) - O4dVRRSM(1,2,2,2)
DVRR_1233 = O4dVRR(1,2,3,3) - O4dVRRSM(1,2,3,3)
DVRR_3123 = O4dVRR(3,1,2,3) - O4dVRRSM(3,1,2,3)
DVLR_1211 = O4dVLR(1,2,1,1) - O4dVLRSM(1,2,1,1)
DVLR_1222 = O4dVLR(1,2,2,2) - O4dVLRSM(1,2,2,2)
DVLR_1233 = O4dVLR(1,2,3,3) - O4dVLRSM(1,2,3,3)
DVRL_1211 = O4dVRL(1,2,1,1) - O4dVRLSM(1,2,1,1)
DVRL_1222 = O4dVRL(1,2,2,2) - O4dVRLSM(1,2,2,2)
DVRL_1233 = O4dVRL(1,2,3,3) - O4dVRLSM(1,2,3,3)
DVLR_3123 = O4dVLR(3,1,2,3) - O4dVLRSM(3,1,2,3)
DVLR_3213 = O4dVLR(3,2,1,3) - O4dVLRSM(3,2,1,3)
DSRR_1211 = O4dSRR(1,2,1,1) - O4dSRRSM(1,2,1,1)
DSRR_1222 = O4dSRR(1,2,2,2) - O4dSRRSM(1,2,2,2)
DSRR_1233 = O4dSRR(1,2,3,3) - O4dSRRSM(1,2,3,3)
DSRR_2111 = O4dSRR(2,1,1,1) - O4dSRRSM(2,1,1,1)
DSRR_2122 = O4dSRR(2,1,2,2) - O4dSRRSM(2,1,2,2)
DSRR_2133 = O4dSRR(2,1,3,3) - O4dSRRSM(2,1,3,3)
DSRR_3123 = O4dSRR(3,1,2,3) - O4dSRRSM(3,1,2,3)
DSRR_3213 = O4dSRR(3,2,1,3) - O4dSRRSM(3,2,1,3)
EVLL_1211 = OddllVLL(1,2,1,1) - OddllVLLSM(1,2,1,1)
EVLL_1222 = OddllVLL(1,2,2,2) - OddllVLLSM(1,2,2,2)
EVLL_1233 = OddllVLL(1,2,3,3) - OddllVLLSM(1,2,3,3)
EVRR_1211 = OddllVRR(1,2,1,1) - OddllVRRSM(1,2,1,1)
EVRR_1222 = OddllVRR(1,2,2,2) - OddllVRRSM(1,2,2,2)
EVRR_1233 = OddllVRR(1,2,3,3) - OddllVRRSM(1,2,3,3)
EVLR_1211 = OddllVLR(1,2,1,1) - OddllVLRSM(1,2,1,1)
EVLR_1222 = OddllVLR(1,2,2,2) - OddllVLRSM(1,2,2,2)
EVLR_1233 = OddllVLR(1,2,3,3) - OddllVLRSM(1,2,3,3)
EVRL_1211 = OddllVRL(1,2,1,1) - OddllVRLSM(1,2,1,1)
EVRL_1222 = OddllVRL(1,2,2,2) - OddllVRLSM(1,2,2,2)
EVRL_1233 = OddllVRL(1,2,3,3) - OddllVRLSM(1,2,3,3)
ESRR_1211 = OddllSRR(1,2,1,1) - OddllSRRSM(1,2,1,1)
ESRR_1222 = OddllSRR(1,2,2,2) - OddllSRRSM(1,2,2,2)
ESRR_1233 = OddllSRR(1,2,3,3) - OddllSRRSM(1,2,3,3)
ESRR_2111 = OddllSRR(2,1,1,1) - OddllSRRSM(2,1,1,1)
ESRR_2122 = OddllSRR(2,1,2,2) - OddllSRRSM(2,1,2,2)
ESRR_2133 = OddllSRR(2,1,3,3) - OddllSRRSM(2,1,3,3)
ESLR_1211 = OddllSLR(1,2,1,1) - OddllSLRSM(1,2,1,1)
ESLR_1222 = OddllSLR(1,2,2,2) - OddllSLRSM(1,2,2,2)
ESLR_1233 = OddllSLR(1,2,3,3) - OddllSLRSM(1,2,3,3)
ESLR_2111 = OddllSLR(2,1,1,1) - OddllSLRSM(2,1,1,1)
ESLR_2122 = OddllSLR(2,1,2,2) - OddllSLRSM(2,1,2,2)
ESLR_2133 = OddllSLR(2,1,3,3) - OddllSLRSM(2,1,3,3)
ETRR_1211 = OddllTRR(1,2,1,1) - OddllTRRSM(1,2,1,1)
ETRR_1222 = OddllTRR(1,2,2,2) - OddllTRRSM(1,2,2,2)
ETRR_1233 = OddllTRR(1,2,3,3) - OddllTRRSM(1,2,3,3)
ETRR_2111 = OddllTRR(2,1,1,1) - OddllTRRSM(2,1,1,1)
ETRR_2122 = OddllTRR(2,1,2,2) - OddllTRRSM(2,1,2,2)
ETRR_2133 = OddllTRR(2,1,3,3) - OddllTRRSM(2,1,3,3)
EVLL_2312 = OddllVLL(2,3,1,2) - OddllVLLSM(2,3,1,2)
EVRR_2312 = OddllVRR(2,3,1,2) - OddllVRRSM(2,3,1,2)
EVLR_2312 = OddllVLR(2,3,1,2) - OddllVLRSM(2,3,1,2)
EVRL_2312 = OddllVRL(2,3,1,2) - OddllVRLSM(2,3,1,2)
ESRR_2312 = OddllSRR(2,3,1,2) - OddllSRRSM(2,3,1,2)
ESRR_3221 = OddllSRR(3,2,2,1) - OddllSRRSM(3,2,2,1)
ESLR_2312 = OddllSLR(2,3,1,2) - OddllSLRSM(2,3,1,2)
ESLR_3221 = OddllSLR(3,2,2,1) - OddllSLRSM(3,2,2,1)
ETRR_2312 = OddllTRR(2,3,1,2) - OddllTRRSM(2,3,1,2)
ETRR_3221 = OddllTRR(3,2,2,1) - OddllTRRSM(3,2,2,1)
EVLL_3212 = OddllVLL(3,2,1,2) - OddllVLLSM(3,2,1,2)
EVRR_3212 = OddllVRR(3,2,1,2) - OddllVRRSM(3,2,1,2)
EVLR_3212 = OddllVLR(3,2,1,2) - OddllVLRSM(3,2,1,2)
EVRL_3212 = OddllVRL(3,2,1,2) - OddllVRLSM(3,2,1,2)
ESRR_3212 = OddllSRR(3,2,1,2) - OddllSRRSM(3,2,1,2)
ESRR_2321 = OddllSRR(2,3,2,1) - OddllSRRSM(2,3,2,1)
ESLR_3212 = OddllSLR(3,2,1,2) - OddllSLRSM(3,2,1,2)
ESLR_2321 = OddllSLR(2,3,2,1) - OddllSLRSM(2,3,2,1)
ETRR_3212 = OddllTRR(3,2,1,2) - OddllTRRSM(3,2,1,2)
ETRR_2321 = OddllTRR(2,3,2,1) - OddllTRRSM(2,3,2,1)
EVLL_2313 = OddllVLL(2,3,1,3) - OddllVLLSM(2,3,1,3)
EVRR_2313 = OddllVRR(2,3,1,3) - OddllVRRSM(2,3,1,3)
EVLR_2313 = OddllVLR(2,3,1,3) - OddllVLRSM(2,3,1,3)
EVRL_2313 = OddllVRL(2,3,1,3) - OddllVRLSM(2,3,1,3)
ESRR_2313 = OddllSRR(2,3,1,3) - OddllSRRSM(2,3,1,3)
ESRR_3231 = OddllSRR(3,2,3,1) - OddllSRRSM(3,2,3,1)
ESLR_2313 = OddllSLR(2,3,1,3) - OddllSLRSM(2,3,1,3)
ESLR_3231 = OddllSLR(3,2,3,1) - OddllSLRSM(3,2,3,1)
ETRR_2313 = OddllTRR(2,3,1,3) - OddllTRRSM(2,3,1,3)
ETRR_3231 = OddllTRR(3,2,3,1) - OddllTRRSM(3,2,3,1)
EVLL_3213 = OddllVLL(3,2,1,3) - OddllVLLSM(3,2,1,3)
EVRR_3213 = OddllVRR(3,2,1,3) - OddllVRRSM(3,2,1,3)
EVLR_3213 = OddllVLR(3,2,1,3) - OddllVLRSM(3,2,1,3)
EVRL_3213 = OddllVRL(3,2,1,3) - OddllVRLSM(3,2,1,3)
ESRR_3213 = OddllSRR(3,2,1,3) - OddllSRRSM(3,2,1,3)
ESRR_2331 = OddllSRR(2,3,3,1) - OddllSRRSM(2,3,3,1)
ESLR_3213 = OddllSLR(3,2,1,3) - OddllSLRSM(3,2,1,3)
ESLR_2331 = OddllSLR(2,3,3,1) - OddllSLRSM(2,3,3,1)
ETRR_3213 = OddllTRR(3,2,1,3) - OddllTRRSM(3,2,1,3)
ETRR_2331 = OddllTRR(2,3,3,1) - OddllTRRSM(2,3,3,1)
EVLL_2323 = OddllVLL(2,3,2,3) - OddllVLLSM(2,3,2,3)
EVRR_2323 = OddllVRR(2,3,2,3) - OddllVRRSM(2,3,2,3)
EVLR_2323 = OddllVLR(2,3,2,3) - OddllVLRSM(2,3,2,3)
EVRL_2323 = OddllVRL(2,3,2,3) - OddllVRLSM(2,3,2,3)
ESRR_2323 = OddllSRR(2,3,2,3) - OddllSRRSM(2,3,2,3)
ESRR_3232 = OddllSRR(3,2,3,2) - OddllSRRSM(3,2,3,2)
ESLR_2323 = OddllSLR(2,3,2,3) - OddllSLRSM(2,3,2,3)
ESLR_3232 = OddllSLR(3,2,3,2) - OddllSLRSM(3,2,3,2)
ETRR_2323 = OddllTRR(2,3,2,3) - OddllTRRSM(2,3,2,3)
ETRR_3232 = OddllTRR(3,2,3,2) - OddllTRRSM(3,2,3,2)
EVLL_3223 = OddllVLL(3,2,2,3) - OddllVLLSM(3,2,2,3)
EVRR_3223 = OddllVRR(3,2,2,3) - OddllVRRSM(3,2,2,3)
EVLR_3223 = OddllVLR(3,2,2,3) - OddllVLRSM(3,2,2,3)
EVRL_3223 = OddllVRL(3,2,2,3) - OddllVRLSM(3,2,2,3)
ESRR_3223 = OddllSRR(3,2,2,3) - OddllSRRSM(3,2,2,3)
ESRR_2332 = OddllSRR(2,3,3,2) - OddllSRRSM(2,3,3,2)
ESLR_3223 = OddllSLR(3,2,2,3) - OddllSLRSM(3,2,2,3)
ESLR_2332 = OddllSLR(2,3,3,2) - OddllSLRSM(2,3,3,2)
ETRR_3223 = OddllTRR(3,2,2,3) - OddllTRRSM(3,2,2,3)
ETRR_2332 = OddllTRR(2,3,3,2) - OddllTRRSM(2,3,3,2)
EVLL_1312 = OddllVLL(1,3,1,2) - OddllVLLSM(1,3,1,2)
EVRR_1312 = OddllVRR(1,3,1,2) - OddllVRRSM(1,3,1,2)
EVLR_1312 = OddllVLR(1,3,1,2) - OddllVLRSM(1,3,1,2)
EVRL_1312 = OddllVRL(1,3,1,2) - OddllVRLSM(1,3,1,2)
ESRR_1312 = OddllSRR(1,3,1,2) - OddllSRRSM(1,3,1,2)
ESRR_3121 = OddllSRR(3,1,2,1) - OddllSRRSM(3,1,2,1)
ESLR_1312 = OddllSLR(1,3,1,2) - OddllSLRSM(1,3,1,2)
ESLR_3121 = OddllSLR(3,1,2,1) - OddllSLRSM(3,1,2,1)
ETRR_1312 = OddllTRR(1,3,1,2) - OddllTRRSM(1,3,1,2)
ETRR_3121 = OddllTRR(3,1,2,1) - OddllTRRSM(3,1,2,1)
EVLL_3112 = OddllVLL(3,1,1,2) - OddllVLLSM(3,1,1,2)
EVRR_3112 = OddllVRR(3,1,1,2) - OddllVRRSM(3,1,1,2)
EVLR_3112 = OddllVLR(3,1,1,2) - OddllVLRSM(3,1,1,2)
EVRL_3112 = OddllVRL(3,1,1,2) - OddllVRLSM(3,1,1,2)
ESRR_3112 = OddllSRR(3,1,1,2) - OddllSRRSM(3,1,1,2)
ESRR_1321 = OddllSRR(1,3,2,1) - OddllSRRSM(1,3,2,1)
ESLR_3112 = OddllSLR(3,1,1,2) - OddllSLRSM(3,1,1,2)
ESLR_1321 = OddllSLR(1,3,2,1) - OddllSLRSM(1,3,2,1)
ETRR_3112 = OddllTRR(3,1,1,2) - OddllTRRSM(3,1,1,2)
ETRR_1321 = OddllTRR(1,3,2,1) - OddllTRRSM(1,3,2,1)
EVLL_1313 = OddllVLL(1,3,1,3) - OddllVLLSM(1,3,1,3)
EVRR_1313 = OddllVRR(1,3,1,3) - OddllVRRSM(1,3,1,3)
EVLR_1313 = OddllVLR(1,3,1,3) - OddllVLRSM(1,3,1,3)
EVRL_1313 = OddllVRL(1,3,1,3) - OddllVRLSM(1,3,1,3)
ESRR_1313 = OddllSRR(1,3,1,3) - OddllSRRSM(1,3,1,3)
ESRR_3131 = OddllSRR(3,1,3,1) - OddllSRRSM(3,1,3,1)
ESLR_1313 = OddllSLR(1,3,1,3) - OddllSLRSM(1,3,1,3)
ESLR_3131 = OddllSLR(3,1,3,1) - OddllSLRSM(3,1,3,1)
ETRR_1313 = OddllTRR(1,3,1,3) - OddllTRRSM(1,3,1,3)
ETRR_3131 = OddllTRR(3,1,3,1) - OddllTRRSM(3,1,3,1)
EVLL_3113 = OddllVLL(3,1,1,3) - OddllVLLSM(3,1,1,3)
EVRR_3113 = OddllVRR(3,1,1,3) - OddllVRRSM(3,1,1,3)
EVLR_3113 = OddllVLR(3,1,1,3) - OddllVLRSM(3,1,1,3)
EVRL_3113 = OddllVRL(3,1,1,3) - OddllVRLSM(3,1,1,3)
ESRR_3113 = OddllSRR(3,1,1,3) - OddllSRRSM(3,1,1,3)
ESRR_1331 = OddllSRR(1,3,3,1) - OddllSRRSM(1,3,3,1)
ESLR_3113 = OddllSLR(3,1,1,3) - OddllSLRSM(3,1,1,3)
ESLR_1331 = OddllSLR(1,3,3,1) - OddllSLRSM(1,3,3,1)
ETRR_3113 = OddllTRR(3,1,1,3) - OddllTRRSM(3,1,1,3)
ETRR_1331 = OddllTRR(1,3,3,1) - OddllTRRSM(1,3,3,1)
EVLL_1323 = OddllVLL(1,3,2,3) - OddllVLLSM(1,3,2,3)
EVRR_1323 = OddllVRR(1,3,2,3) - OddllVRRSM(1,3,2,3)
EVLR_1323 = OddllVLR(1,3,2,3) - OddllVLRSM(1,3,2,3)
EVRL_1323 = OddllVRL(1,3,2,3) - OddllVRLSM(1,3,2,3)
ESRR_1323 = OddllSRR(1,3,2,3) - OddllSRRSM(1,3,2,3)
ESRR_3132 = OddllSRR(3,1,3,2) - OddllSRRSM(3,1,3,2)
ESLR_1323 = OddllSLR(1,3,2,3) - OddllSLRSM(1,3,2,3)
ESLR_3132 = OddllSLR(3,1,3,2) - OddllSLRSM(3,1,3,2)
ETRR_1323 = OddllTRR(1,3,2,3) - OddllTRRSM(1,3,2,3)
ETRR_3132 = OddllTRR(3,1,3,2) - OddllTRRSM(3,1,3,2)
EVLL_3123 = OddllVLL(3,1,2,3) - OddllVLLSM(3,1,2,3)
EVRR_3123 = OddllVRR(3,1,2,3) - OddllVRRSM(3,1,2,3)
EVLR_3123 = OddllVLR(3,1,2,3) - OddllVLRSM(3,1,2,3)
EVRL_3123 = OddllVRL(3,1,2,3) - OddllVRLSM(3,1,2,3)
ESRR_3123 = OddllSRR(3,1,2,3) - OddllSRRSM(3,1,2,3)
ESRR_1332 = OddllSRR(1,3,3,2) - OddllSRRSM(1,3,3,2)
ESLR_3123 = OddllSLR(3,1,2,3) - OddllSLRSM(3,1,2,3)
ESLR_1332 = OddllSLR(1,3,3,2) - OddllSLRSM(1,3,3,2)
ETRR_3123 = OddllTRR(3,1,2,3) - OddllTRRSM(3,1,2,3)
ETRR_1332 = OddllTRR(1,3,3,2) - OddllTRRSM(1,3,3,2)
EVLL_2112 = OddllVLL(2,1,1,2) - OddllVLLSM(2,1,1,2)
EVRR_2112 = OddllVRR(2,1,1,2) - OddllVRRSM(2,1,1,2)
EVLR_2112 = OddllVLR(2,1,1,2) - OddllVLRSM(2,1,1,2)
EVRL_2112 = OddllVRL(2,1,1,2) - OddllVRLSM(2,1,1,2)
ESRR_2112 = OddllSRR(2,1,1,2) - OddllSRRSM(2,1,1,2)
ESRR_1221 = OddllSRR(1,2,2,1) - OddllSRRSM(1,2,2,1)
ESLR_2112 = OddllSLR(2,1,1,2) - OddllSLRSM(2,1,1,2)
ESLR_1221 = OddllSLR(1,2,2,1) - OddllSLRSM(1,2,2,1)
ETRR_2112 = OddllTRR(2,1,1,2) - OddllTRRSM(2,1,1,2)
ETRR_1221 = OddllTRR(1,2,2,1) - OddllTRRSM(1,2,2,1)
EVLL_1212 = OddllVLL(1,2,1,2) - OddllVLLSM(1,2,1,2)
EVRR_1212 = OddllVRR(1,2,1,2) - OddllVRRSM(1,2,1,2)
EVLR_1212 = OddllVLR(1,2,1,2) - OddllVLRSM(1,2,1,2)
EVRL_1212 = OddllVRL(1,2,1,2) - OddllVRLSM(1,2,1,2)
ESRR_1212 = OddllSRR(1,2,1,2) - OddllSRRSM(1,2,1,2)
ESRR_2121 = OddllSRR(2,1,2,1) - OddllSRRSM(2,1,2,1)
ESLR_1212 = OddllSLR(1,2,1,2) - OddllSLRSM(1,2,1,2)
ESLR_2121 = OddllSLR(2,1,2,1) - OddllSLRSM(2,1,2,1)
ETRR_1212 = OddllTRR(1,2,1,2) - OddllTRRSM(1,2,1,2)
ETRR_2121 = OddllTRR(2,1,2,1) - OddllTRRSM(2,1,2,1)
EVLL_2113 = OddllVLL(2,1,1,3) - OddllVLLSM(2,1,1,3)
EVRR_2113 = OddllVRR(2,1,1,3) - OddllVRRSM(2,1,1,3)
EVLR_2113 = OddllVLR(2,1,1,3) - OddllVLRSM(2,1,1,3)
EVRL_2113 = OddllVRL(2,1,1,3) - OddllVRLSM(2,1,1,3)
ESRR_2113 = OddllSRR(2,1,1,3) - OddllSRRSM(2,1,1,3)
ESRR_1231 = OddllSRR(1,2,3,1) - OddllSRRSM(1,2,3,1)
ESLR_2113 = OddllSLR(2,1,1,3) - OddllSLRSM(2,1,1,3)
ESLR_1231 = OddllSLR(1,2,3,1) - OddllSLRSM(1,2,3,1)
ETRR_2113 = OddllTRR(2,1,1,3) - OddllTRRSM(2,1,1,3)
ETRR_1231 = OddllTRR(1,2,3,1) - OddllTRRSM(1,2,3,1)
EVLL_1213 = OddllVLL(1,2,1,3) - OddllVLLSM(1,2,1,3)
EVRR_1213 = OddllVRR(1,2,1,3) - OddllVRRSM(1,2,1,3)
EVLR_1213 = OddllVLR(1,2,1,3) - OddllVLRSM(1,2,1,3)
EVRL_1213 = OddllVRL(1,2,1,3) - OddllVRLSM(1,2,1,3)
ESRR_1213 = OddllSRR(1,2,1,3) - OddllSRRSM(1,2,1,3)
ESRR_2131 = OddllSRR(2,1,3,1) - OddllSRRSM(2,1,3,1)
ESLR_1213 = OddllSLR(1,2,1,3) - OddllSLRSM(1,2,1,3)
ESLR_2131 = OddllSLR(2,1,3,1) - OddllSLRSM(2,1,3,1)
ETRR_1213 = OddllTRR(1,2,1,3) - OddllTRRSM(1,2,1,3)
ETRR_2131 = OddllTRR(2,1,3,1) - OddllTRRSM(2,1,3,1)
EVLL_2123 = OddllVLL(2,1,2,3) - OddllVLLSM(2,1,2,3)
EVRR_2123 = OddllVRR(2,1,2,3) - OddllVRRSM(2,1,2,3)
EVLR_2123 = OddllVLR(2,1,2,3) - OddllVLRSM(2,1,2,3)
EVRL_2123 = OddllVRL(2,1,2,3) - OddllVRLSM(2,1,2,3)
ESRR_2123 = OddllSRR(2,1,2,3) - OddllSRRSM(2,1,2,3)
ESRR_1232 = OddllSRR(1,2,3,2) - OddllSRRSM(1,2,3,2)
ESLR_2123 = OddllSLR(2,1,2,3) - OddllSLRSM(2,1,2,3)
ESLR_1232 = OddllSLR(1,2,3,2) - OddllSLRSM(1,2,3,2)
ETRR_2123 = OddllTRR(2,1,2,3) - OddllTRRSM(2,1,2,3)
ETRR_1232 = OddllTRR(1,2,3,2) - OddllTRRSM(1,2,3,2)
EVLL_1223 = OddllVLL(1,2,2,3) - OddllVLLSM(1,2,2,3)
EVRR_1223 = OddllVRR(1,2,2,3) - OddllVRRSM(1,2,2,3)
EVLR_1223 = OddllVLR(1,2,2,3) - OddllVLRSM(1,2,2,3)
EVRL_1223 = OddllVRL(1,2,2,3) - OddllVRLSM(1,2,2,3)
ESRR_1223 = OddllSRR(1,2,2,3) - OddllSRRSM(1,2,2,3)
ESRR_2132 = OddllSRR(2,1,3,2) - OddllSRRSM(2,1,3,2)
ESLR_1223 = OddllSLR(1,2,2,3) - OddllSLRSM(1,2,2,3)
ESLR_2132 = OddllSLR(2,1,3,2) - OddllSLRSM(2,1,3,2)
ETRR_1223 = OddllTRR(1,2,2,3) - OddllTRRSM(1,2,2,3)
ETRR_2132 = OddllTRR(2,1,3,2) - OddllTRRSM(2,1,3,2)
CKM = CKMsave 
!-------------------------------------
! running to M_Z 
!-------------------------------------

scalein=SetRenormalizationScale(scale_save**2) 
If (MatchingOrder.gt.-1) Then 
Call RunSM_and_SUSY_RGEs(mz,g1input,g2input,g3input,lam5input,lam1input,              & 
& lam4input,lam3input,lam2input,Yuinput,Ydinput,Yeinput,m122input,m112input,             & 
& m222input,vdinput,vuinput,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,             & 
& m112,m222,vd,vu,CKM_MZ,sinW2_MZ,Alpha_MZ,AlphaS_MZ,.true.)

Else 
g1=g1input 
g2=g2input 
g3=g3input 
lam5=lam5input 
lam1=lam1input 
lam4=lam4input 
lam3=lam3input 
lam2=lam2input 
Yu=Yuinput 
Yd=Ydinput 
Ye=Yeinput 
m122=m122input 
m112=m112input 
m222=m222input 
vd=vdinput 
vu=vuinput 
End if 
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,           & 
& m112,m222,vd,vu,(/ ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,           & 
& MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,betaH,               & 
& vd,vu,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,GenerationMixing,kont)

mzsave  = sqrt(mz2) 
 mf_d_mz = MFd(1:3) 
 mf_d2_mz = MFd(1:3)**2 
 mf_u_mz = MFu(1:3) 
 mf_u2_mz = MFu(1:3)**2 
 mf_l_MZ = MFe(1:3) 
 mf_l2_MZ = MFe(1:3)**2 
Call AllCouplings(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,g1,g2,TW,g3,Yd,             & 
& ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,cplhhhhhh,      & 
& cplhhHmcHm,cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,       & 
& cplHmcHmVZ,cplhhcVWmVWm,cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,     & 
& cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,               & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,            & 
& cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,            & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,            & 
& cplcFvFvVZR)

Mhh_s = Mhh 
Mhh2_s  = Mhh2   
MAh_s = MAh 
MAh2_s  = MAh2   
Mhh= MhhL 
Mhh2 = Mhh2L 
MAh= MAhL 
MAh2 = MAh2L 

 ! **** TreeS2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TSOllddSLL(gt1,gt2,gt3,gt4),TSOllddSRR(gt1,gt2,gt3,gt4)        & 
& ,TSOllddSRL(gt1,gt2,gt3,gt4),TSOllddSLR(gt1,gt2,gt3,gt4),TSOllddVRR(gt1,gt2,gt3,gt4)   & 
& ,TSOllddVLL(gt1,gt2,gt3,gt4),TSOllddVRL(gt1,gt2,gt3,gt4),TSOllddVLR(gt1,gt2,gt3,gt4)   & 
& ,TSOllddTLL(gt1,gt2,gt3,gt4),TSOllddTLR(gt1,gt2,gt3,gt4),TSOllddTRL(gt1,gt2,gt3,gt4)   & 
& ,TSOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TVOllddSLL(gt1,gt2,gt3,gt4),TVOllddSRR(gt1,gt2,gt3,gt4)        & 
& ,TVOllddSRL(gt1,gt2,gt3,gt4),TVOllddSLR(gt1,gt2,gt3,gt4),TVOllddVRR(gt1,gt2,gt3,gt4)   & 
& ,TVOllddVLL(gt1,gt2,gt3,gt4),TVOllddVRL(gt1,gt2,gt3,gt4),TVOllddVLR(gt1,gt2,gt3,gt4)   & 
& ,TVOllddTLL(gt1,gt2,gt3,gt4),TVOllddTLR(gt1,gt2,gt3,gt4),TVOllddTRL(gt1,gt2,gt3,gt4)   & 
& ,TVOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TSOlluuSLL(gt1,gt2,gt3,gt4),TSOlluuSRR(gt1,gt2,gt3,gt4)        & 
& ,TSOlluuSRL(gt1,gt2,gt3,gt4),TSOlluuSLR(gt1,gt2,gt3,gt4),TSOlluuVRR(gt1,gt2,gt3,gt4)   & 
& ,TSOlluuVLL(gt1,gt2,gt3,gt4),TSOlluuVRL(gt1,gt2,gt3,gt4),TSOlluuVLR(gt1,gt2,gt3,gt4)   & 
& ,TSOlluuTLL(gt1,gt2,gt3,gt4),TSOlluuTLR(gt1,gt2,gt3,gt4),TSOlluuTRL(gt1,gt2,gt3,gt4)   & 
& ,TSOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,TVOlluuSLL(gt1,gt2,gt3,gt4),TVOlluuSRR(gt1,gt2,gt3,gt4)        & 
& ,TVOlluuSRL(gt1,gt2,gt3,gt4),TVOlluuSLR(gt1,gt2,gt3,gt4),TVOlluuVRR(gt1,gt2,gt3,gt4)   & 
& ,TVOlluuVLL(gt1,gt2,gt3,gt4),TVOlluuVRL(gt1,gt2,gt3,gt4),TVOlluuVLR(gt1,gt2,gt3,gt4)   & 
& ,TVOlluuTLL(gt1,gt2,gt3,gt4),TVOlluuTLR(gt1,gt2,gt3,gt4),TVOlluuTRL(gt1,gt2,gt3,gt4)   & 
& ,TVOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,             & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFeFeAhL,      & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,TSO4lSLL(gt1,gt2,gt3,gt4) & 
& ,TSO4lSRR(gt1,gt2,gt3,gt4),TSO4lSRL(gt1,gt2,gt3,gt4),TSO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,TSO4lVRR(gt1,gt2,gt3,gt4),TSO4lVLL(gt1,gt2,gt3,gt4),TSO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,TSO4lVLR(gt1,gt2,gt3,gt4),TSO4lTLL(gt1,gt2,gt3,gt4),TSO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,TSO4lTRL(gt1,gt2,gt3,gt4),TSO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,             & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFeFeAhL,      & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,TVO4lSLL(gt1,gt2,gt3,gt4) & 
& ,TVO4lSRR(gt1,gt2,gt3,gt4),TVO4lSRL(gt1,gt2,gt3,gt4),TVO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,TVO4lVRR(gt1,gt2,gt3,gt4),TVO4lVLL(gt1,gt2,gt3,gt4),TVO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,TVO4lVLR(gt1,gt2,gt3,gt4),TVO4lTLL(gt1,gt2,gt3,gt4),TVO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,TVO4lTRL(gt1,gt2,gt3,gt4),TVO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,             & 
& TSO4lSLLcross(gt1,gt2,gt3,gt4),TSO4lSRRcross(gt1,gt2,gt3,gt4),TSO4lSRLcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lSLRcross(gt1,gt2,gt3,gt4),TSO4lVRRcross(gt1,gt2,gt3,gt4),TSO4lVLLcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lVRLcross(gt1,gt2,gt3,gt4),TSO4lVLRcross(gt1,gt2,gt3,gt4),TSO4lTLLcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lTLRcross(gt1,gt2,gt3,gt4),TSO4lTRLcross(gt1,gt2,gt3,gt4),TSO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,             & 
& TVO4lSLLcross(gt1,gt2,gt3,gt4),TVO4lSRRcross(gt1,gt2,gt3,gt4),TVO4lSRLcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lSLRcross(gt1,gt2,gt3,gt4),TVO4lVRRcross(gt1,gt2,gt3,gt4),TVO4lVLLcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lVRLcross(gt1,gt2,gt3,gt4),TVO4lVLRcross(gt1,gt2,gt3,gt4),TVO4lTLLcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lTLRcross(gt1,gt2,gt3,gt4),TVO4lTRLcross(gt1,gt2,gt3,gt4),TVO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,             & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,BOllddSLL(gt1,gt2,gt3,gt4),BOllddSRR(gt1,gt2,gt3,gt4)          & 
& ,BOllddSRL(gt1,gt2,gt3,gt4),BOllddSLR(gt1,gt2,gt3,gt4),BOllddVRR(gt1,gt2,gt3,gt4)      & 
& ,BOllddVLL(gt1,gt2,gt3,gt4),BOllddVRL(gt1,gt2,gt3,gt4),BOllddVLR(gt1,gt2,gt3,gt4)      & 
& ,BOllddTLL(gt1,gt2,gt3,gt4),BOllddTLR(gt1,gt2,gt3,gt4),BOllddTRL(gt1,gt2,gt3,gt4)      & 
& ,BOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PSOllddSLL(gt1,gt2,gt3,gt4),PSOllddSRR(gt1,gt2,gt3,gt4)        & 
& ,PSOllddSRL(gt1,gt2,gt3,gt4),PSOllddSLR(gt1,gt2,gt3,gt4),PSOllddVRR(gt1,gt2,gt3,gt4)   & 
& ,PSOllddVLL(gt1,gt2,gt3,gt4),PSOllddVRL(gt1,gt2,gt3,gt4),PSOllddVLR(gt1,gt2,gt3,gt4)   & 
& ,PSOllddTLL(gt1,gt2,gt3,gt4),PSOllddTLR(gt1,gt2,gt3,gt4),PSOllddTRL(gt1,gt2,gt3,gt4)   & 
& ,PSOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PVOllddSLL(gt1,gt2,gt3,gt4),PVOllddSRR(gt1,gt2,gt3,gt4)        & 
& ,PVOllddSRL(gt1,gt2,gt3,gt4),PVOllddSLR(gt1,gt2,gt3,gt4),PVOllddVRR(gt1,gt2,gt3,gt4)   & 
& ,PVOllddVLL(gt1,gt2,gt3,gt4),PVOllddVRL(gt1,gt2,gt3,gt4),PVOllddVLR(gt1,gt2,gt3,gt4)   & 
& ,PVOllddTLL(gt1,gt2,gt3,gt4),PVOllddTLR(gt1,gt2,gt3,gt4),PVOllddTRL(gt1,gt2,gt3,gt4)   & 
& ,PVOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,             & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,BOlluuSLL(gt1,gt2,gt3,gt4),BOlluuSRR(gt1,gt2,gt3,gt4)          & 
& ,BOlluuSRL(gt1,gt2,gt3,gt4),BOlluuSLR(gt1,gt2,gt3,gt4),BOlluuVRR(gt1,gt2,gt3,gt4)      & 
& ,BOlluuVLL(gt1,gt2,gt3,gt4),BOlluuVRL(gt1,gt2,gt3,gt4),BOlluuVLR(gt1,gt2,gt3,gt4)      & 
& ,BOlluuTLL(gt1,gt2,gt3,gt4),BOlluuTLR(gt1,gt2,gt3,gt4),BOlluuTRL(gt1,gt2,gt3,gt4)      & 
& ,BOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PSOlluuSLL(gt1,gt2,gt3,gt4),PSOlluuSRR(gt1,gt2,gt3,gt4)        & 
& ,PSOlluuSRL(gt1,gt2,gt3,gt4),PSOlluuSLR(gt1,gt2,gt3,gt4),PSOlluuVRR(gt1,gt2,gt3,gt4)   & 
& ,PSOlluuVLL(gt1,gt2,gt3,gt4),PSOlluuVRL(gt1,gt2,gt3,gt4),PSOlluuVLR(gt1,gt2,gt3,gt4)   & 
& ,PSOlluuTLL(gt1,gt2,gt3,gt4),PSOlluuTLR(gt1,gt2,gt3,gt4),PSOlluuTRL(gt1,gt2,gt3,gt4)   & 
& ,PSOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFd,MFd2,MFe,MFe2,           & 
& MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhcHmVWm,        & 
& cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,        & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHmL,               & 
& cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,             & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,               & 
& cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,         & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcHmVPVWm,cplcHmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplhhcHmVWm,           & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,cplHmcHmVP,cplHmcHmVZ,         & 
& cplHmcVWmVP,cplHmcVWmVZ,PVOlluuSLL(gt1,gt2,gt3,gt4),PVOlluuSRR(gt1,gt2,gt3,gt4)        & 
& ,PVOlluuSRL(gt1,gt2,gt3,gt4),PVOlluuSLR(gt1,gt2,gt3,gt4),PVOlluuVRR(gt1,gt2,gt3,gt4)   & 
& ,PVOlluuVLL(gt1,gt2,gt3,gt4),PVOlluuVRL(gt1,gt2,gt3,gt4),PVOlluuVLR(gt1,gt2,gt3,gt4)   & 
& ,PVOlluuTLL(gt1,gt2,gt3,gt4),PVOlluuTLR(gt1,gt2,gt3,gt4),PVOlluuTRL(gt1,gt2,gt3,gt4)   & 
& ,PVOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,               & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFeFeAhL,      & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,BO4lSLL(gt1,gt2,gt3,gt4)  & 
& ,BO4lSRR(gt1,gt2,gt3,gt4),BO4lSRL(gt1,gt2,gt3,gt4),BO4lSLR(gt1,gt2,gt3,gt4)            & 
& ,BO4lVRR(gt1,gt2,gt3,gt4),BO4lVLL(gt1,gt2,gt3,gt4),BO4lVRL(gt1,gt2,gt3,gt4)            & 
& ,BO4lVLR(gt1,gt2,gt3,gt4),BO4lTLL(gt1,gt2,gt3,gt4),BO4lTLR(gt1,gt2,gt3,gt4)            & 
& ,BO4lTRL(gt1,gt2,gt3,gt4),BO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,             & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFeFeAhL,      & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,PSO4lSLL(gt1,gt2,gt3,gt4) & 
& ,PSO4lSRR(gt1,gt2,gt3,gt4),PSO4lSRL(gt1,gt2,gt3,gt4),PSO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,PSO4lVRR(gt1,gt2,gt3,gt4),PSO4lVLL(gt1,gt2,gt3,gt4),PSO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,PSO4lVLR(gt1,gt2,gt3,gt4),PSO4lTLL(gt1,gt2,gt3,gt4),PSO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,PSO4lTRL(gt1,gt2,gt3,gt4),PSO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,             & 
& MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFeFeAhL,      & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,            & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,PVO4lSLL(gt1,gt2,gt3,gt4) & 
& ,PVO4lSRR(gt1,gt2,gt3,gt4),PVO4lSRL(gt1,gt2,gt3,gt4),PVO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,PVO4lVRR(gt1,gt2,gt3,gt4),PVO4lVLL(gt1,gt2,gt3,gt4),PVO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,PVO4lVLR(gt1,gt2,gt3,gt4),PVO4lTLL(gt1,gt2,gt3,gt4),PVO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,PVO4lTRL(gt1,gt2,gt3,gt4),PVO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,               & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,             & 
& BO4lSLLcross(gt1,gt2,gt3,gt4),BO4lSRRcross(gt1,gt2,gt3,gt4),BO4lSRLcross(gt1,gt2,gt3,gt4)& 
& ,BO4lSLRcross(gt1,gt2,gt3,gt4),BO4lVRRcross(gt1,gt2,gt3,gt4),BO4lVLLcross(gt1,gt2,gt3,gt4)& 
& ,BO4lVRLcross(gt1,gt2,gt3,gt4),BO4lVLRcross(gt1,gt2,gt3,gt4),BO4lTLLcross(gt1,gt2,gt3,gt4)& 
& ,BO4lTLRcross(gt1,gt2,gt3,gt4),BO4lTRLcross(gt1,gt2,gt3,gt4),BO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,             & 
& PSO4lSLLcross(gt1,gt2,gt3,gt4),PSO4lSRRcross(gt1,gt2,gt3,gt4),PSO4lSRLcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lSLRcross(gt1,gt2,gt3,gt4),PSO4lVRRcross(gt1,gt2,gt3,gt4),PSO4lVLLcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lVRLcross(gt1,gt2,gt3,gt4),PSO4lVLRcross(gt1,gt2,gt3,gt4),PSO4lTLLcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lTLRcross(gt1,gt2,gt3,gt4),PSO4lTRLcross(gt1,gt2,gt3,gt4),PSO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MFe,MFe2,Mhh,             & 
& Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhhhVZ,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplhhhhhh,cplhhVZVZ,             & 
& PVO4lSLLcross(gt1,gt2,gt3,gt4),PVO4lSRRcross(gt1,gt2,gt3,gt4),PVO4lSRLcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lSLRcross(gt1,gt2,gt3,gt4),PVO4lVRRcross(gt1,gt2,gt3,gt4),PVO4lVLLcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lVRLcross(gt1,gt2,gt3,gt4),PVO4lVLRcross(gt1,gt2,gt3,gt4),PVO4lTLLcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lTLRcross(gt1,gt2,gt3,gt4),PVO4lTRLcross(gt1,gt2,gt3,gt4),PVO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** Gamma2l **** 
 
IndexArray2(1,:) = (/2,1/) 
IndexArray2(2,:) = (/3,1/) 
IndexArray2(3,:) = (/3,2/) 
Do i1=1,3 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGamma2l(gt1,gt2,gt3,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,             & 
& MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,              & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplcHmVPVWm,cplcVWmVPVWm,cplHmcHmVP,cplHmcVWmVP,OA2lSL(gt1,gt2),OA2lSR(gt1,gt2)        & 
& ,OA1L(gt1,gt2),OA1R(gt1,gt2))

End Do 


 ! **** H2l **** 
 
IndexArray3(1,:) = (/1,2,1/) 
IndexArray3(2,:) = (/1,3,1/) 
IndexArray3(3,:) = (/2,3,1/) 
IndexArray3(4,:) = (/2,1,1/) 
IndexArray3(5,:) = (/3,1,1/) 
IndexArray3(6,:) = (/3,2,1/) 
Do i1=1,6 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateH2l(gt1,gt2,gt3,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,            & 
& MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhhhhh,cplAhhhVZ,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhVZVZ,OH2lSL(gt1,gt2,gt3)& 
& ,OH2lSR(gt1,gt2,gt3))

End Do 
 End Do 


 ! **** Z2l **** 
 
IndexArray2(1,:) = (/1,2/) 
IndexArray2(2,:) = (/1,3/) 
IndexArray2(3,:) = (/2,3/) 
Do i1=1,3 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateZ2l(gt1,gt2,gt3,.False.,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,            & 
& MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,         & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,         & 
& cplcHmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,OZ2lSL(gt1,gt2)              & 
& ,OZ2lSR(gt1,gt2),OZ2lVL(gt1,gt2),OZ2lVR(gt1,gt2))

End Do 


 ! ***** Combine operators for 2L2d
OllddSLL = BOllddSLL + PSOllddSLL + PVOllddSLL + TSOllddSLL + TVOllddSLL
OllddSRR = BOllddSRR + PSOllddSRR + PVOllddSRR + TSOllddSRR + TVOllddSRR
OllddSRL = BOllddSRL + PSOllddSRL + PVOllddSRL + TSOllddSRL + TVOllddSRL
OllddSLR = BOllddSLR + PSOllddSLR + PVOllddSLR + TSOllddSLR + TVOllddSLR
OllddVRR = BOllddVRR + PSOllddVRR + PVOllddVRR + TSOllddVRR + TVOllddVRR
OllddVLL = BOllddVLL + PSOllddVLL + PVOllddVLL + TSOllddVLL + TVOllddVLL
OllddVRL = BOllddVRL + PSOllddVRL + PVOllddVRL + TSOllddVRL + TVOllddVRL
OllddVLR = BOllddVLR + PSOllddVLR + PVOllddVLR + TSOllddVLR + TVOllddVLR
OllddTLL = BOllddTLL + PSOllddTLL + PVOllddTLL + TSOllddTLL + TVOllddTLL
OllddTLR = BOllddTLR + PSOllddTLR + PVOllddTLR + TSOllddTLR + TVOllddTLR
OllddTRL = BOllddTRL + PSOllddTRL + PVOllddTRL + TSOllddTRL + TVOllddTRL
OllddTRR = BOllddTRR + PSOllddTRR + PVOllddTRR + TSOllddTRR + TVOllddTRR

 ! ***** Combine operators for 2L2u
OlluuSLL = BOlluuSLL + PSOlluuSLL + PVOlluuSLL + TSOlluuSLL + TVOlluuSLL
OlluuSRR = BOlluuSRR + PSOlluuSRR + PVOlluuSRR + TSOlluuSRR + TVOlluuSRR
OlluuSRL = BOlluuSRL + PSOlluuSRL + PVOlluuSRL + TSOlluuSRL + TVOlluuSRL
OlluuSLR = BOlluuSLR + PSOlluuSLR + PVOlluuSLR + TSOlluuSLR + TVOlluuSLR
OlluuVRR = BOlluuVRR + PSOlluuVRR + PVOlluuVRR + TSOlluuVRR + TVOlluuVRR
OlluuVLL = BOlluuVLL + PSOlluuVLL + PVOlluuVLL + TSOlluuVLL + TVOlluuVLL
OlluuVRL = BOlluuVRL + PSOlluuVRL + PVOlluuVRL + TSOlluuVRL + TVOlluuVRL
OlluuVLR = BOlluuVLR + PSOlluuVLR + PVOlluuVLR + TSOlluuVLR + TVOlluuVLR
OlluuTLL = BOlluuTLL + PSOlluuTLL + PVOlluuTLL + TSOlluuTLL + TVOlluuTLL
OlluuTLR = BOlluuTLR + PSOlluuTLR + PVOlluuTLR + TSOlluuTLR + TVOlluuTLR
OlluuTRL = BOlluuTRL + PSOlluuTRL + PVOlluuTRL + TSOlluuTRL + TVOlluuTRL
OlluuTRR = BOlluuTRR + PSOlluuTRR + PVOlluuTRR + TSOlluuTRR + TVOlluuTRR

 ! ***** Combine operators for 4L
O4lSLL = BO4lSLL + PSO4lSLL + PVO4lSLL + TSO4lSLL + TVO4lSLL
O4lSRR = BO4lSRR + PSO4lSRR + PVO4lSRR + TSO4lSRR + TVO4lSRR
O4lSRL = BO4lSRL + PSO4lSRL + PVO4lSRL + TSO4lSRL + TVO4lSRL
O4lSLR = BO4lSLR + PSO4lSLR + PVO4lSLR + TSO4lSLR + TVO4lSLR
O4lVRR = BO4lVRR + PSO4lVRR + PVO4lVRR + TSO4lVRR + TVO4lVRR
O4lVLL = BO4lVLL + PSO4lVLL + PVO4lVLL + TSO4lVLL + TVO4lVLL
O4lVRL = BO4lVRL + PSO4lVRL + PVO4lVRL + TSO4lVRL + TVO4lVRL
O4lVLR = BO4lVLR + PSO4lVLR + PVO4lVLR + TSO4lVLR + TVO4lVLR
O4lTLL = BO4lTLL + PSO4lTLL + PVO4lTLL + TSO4lTLL + TVO4lTLL
O4lTLR = BO4lTLR + PSO4lTLR + PVO4lTLR + TSO4lTLR + TVO4lTLR
O4lTRL = BO4lTRL + PSO4lTRL + PVO4lTRL + TSO4lTRL + TVO4lTRL
O4lTRR = BO4lTRR + PSO4lTRR + PVO4lTRR + TSO4lTRR + TVO4lTRR

 ! ***** Combine operators for 4Lcross
O4lSLLcross = BO4lSLLcross + PSO4lSLLcross + PVO4lSLLcross + TSO4lSLLcross + TVO4lSLLcross
O4lSRRcross = BO4lSRRcross + PSO4lSRRcross + PVO4lSRRcross + TSO4lSRRcross + TVO4lSRRcross
O4lSRLcross = BO4lSRLcross + PSO4lSRLcross + PVO4lSRLcross + TSO4lSRLcross + TVO4lSRLcross
O4lSLRcross = BO4lSLRcross + PSO4lSLRcross + PVO4lSLRcross + TSO4lSLRcross + TVO4lSLRcross
O4lVRRcross = BO4lVRRcross + PSO4lVRRcross + PVO4lVRRcross + TSO4lVRRcross + TVO4lVRRcross
O4lVLLcross = BO4lVLLcross + PSO4lVLLcross + PVO4lVLLcross + TSO4lVLLcross + TVO4lVLLcross
O4lVRLcross = BO4lVRLcross + PSO4lVRLcross + PVO4lVRLcross + TSO4lVRLcross + TVO4lVRLcross
O4lVLRcross = BO4lVLRcross + PSO4lVLRcross + PVO4lVLRcross + TSO4lVLRcross + TVO4lVLRcross
O4lTLLcross = BO4lTLLcross + PSO4lTLLcross + PVO4lTLLcross + TSO4lTLLcross + TVO4lTLLcross
O4lTLRcross = BO4lTLRcross + PSO4lTLRcross + PVO4lTLRcross + TSO4lTLRcross + TVO4lTLRcross
O4lTRLcross = BO4lTRLcross + PSO4lTRLcross + PVO4lTRLcross + TSO4lTRLcross + TVO4lTRLcross
O4lTRRcross = BO4lTRRcross + PSO4lTRRcross + PVO4lTRRcross + TSO4lTRRcross + TVO4lTRRcross

 ! ***** Combine operators for Gamma2l
K1L = OA1L
K1R = OA1R
K2L = OA2lSL
K2R = OA2lSR
K1L = K1L/sqrt(Alpha_MZ*4*Pi)
K1R = K1R/sqrt(Alpha_MZ*4*Pi)
K2L(2,:) = -0.5_dp*K2L(2,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(2)
K2L(3,:) = -0.5_dp*K2L(3,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(3)
K2R(2,:) = -0.5_dp*K2R(2,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(2)
K2R(3,:) = -0.5_dp*K2R(3,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(3)
K2R_21 = K2R(2,1)
K2R_12 = K2R(1,2)
AVLL_1121 = 0.0982515_dp*K1L(2,1) + O4lVLL(1,1,2,1)
AVLL_2221 = 0.0982515_dp*K1L(2,1) + O4lVLL(2,2,2,1)
AVLL_3321 = 0.0982515_dp*K1L(2,1) + O4lVLL(3,3,2,1)
AVRR_1121 = 0.0982515_dp*K1R(2,1) + O4lVRR(1,1,2,1)
AVRR_2221 = 0.0982515_dp*K1R(2,1) + O4lVRR(2,2,2,1)
AVRR_3321 = 0.0982515_dp*K1R(2,1) + O4lVRR(3,3,2,1)
AVLR_1121 = 0.0982515_dp*K1R(2,1) + O4lVLR(1,1,2,1)
AVLR_2221 = 0.0982515_dp*K1R(2,1) + O4lVLR(2,2,2,1)
AVLR_3321 = 0.0982515_dp*K1R(2,1) + O4lVLR(3,3,2,1)
AVLR_2111 = 0.0982515_dp*K1L(2,1) + O4lVLR(2,1,1,1)
AVLR_2122 = 0.0982515_dp*K1L(2,1) + O4lVLR(2,1,2,2)
AVLR_2133 = 0.0982515_dp*K1L(2,1) + O4lVLR(2,1,3,3)
AVLR_3213 = O4lVLR(3,2,1,3)
AVLR_3123 = O4lVLR(3,1,2,3)
ASRR_1121 = O4lSRR(1,1,2,1)
ASRR_2221 = O4lSRR(2,2,2,1)
ASRR_3321 = O4lSRR(3,3,2,1)
ASRR_1112 = O4lSRR(1,1,1,2)
ASRR_2212 = O4lSRR(2,2,1,2)
ASRR_3312 = O4lSRR(3,3,1,2)
ASRR_3213 = O4lSRR(3,2,1,3)
ASRR_3123 = O4lSRR(3,1,2,3)
BVLL_2111 = OllddVLL(2,1,1,1)
BVLL_2122 = OllddVLL(2,1,2,2)
BVLL_2133 = OllddVLL(2,1,3,3)
BVRR_2111 = OllddVRR(2,1,1,1)
BVRR_2122 = OllddVRR(2,1,2,2)
BVRR_2133 = OllddVRR(2,1,3,3)
BVLR_2111 = OllddVLR(2,1,1,1)
BVLR_2122 = OllddVLR(2,1,2,2)
BVLR_2133 = OllddVLR(2,1,3,3)
BSRL_2111 = OllddSRL(2,1,1,1)
BSRL_2122 = OllddSRL(2,1,2,2)
BSRL_2133 = OllddSRL(2,1,3,3)
BSRL_1211 = OllddSRL(1,2,1,1)
BSRL_1222 = OllddSRL(1,2,2,2)
BSRL_1233 = OllddSRL(1,2,3,3)
BSRR_2111 = OllddSRR(2,1,1,1)
BSRR_2122 = OllddSRR(2,1,2,2)
BSRR_2133 = OllddSRR(2,1,3,3)
BSRR_1211 = OllddSRR(1,2,1,1)
BSRR_1222 = OllddSRR(1,2,2,2)
BSRR_1233 = OllddSRR(1,2,3,3)
BTRR_2111 = OllddTRR(2,1,1,1)
BTRR_2122 = OllddTRR(2,1,2,2)
BTRR_2133 = OllddTRR(2,1,3,3)
BTRR_1211 = OllddTRR(1,2,1,1)
BTRR_1222 = OllddTRR(1,2,2,2)
BTRR_1233 = OllddTRR(1,2,3,3)
EVLR_1121 = OddllVLR(1,1,2,1)
EVLR_2221 = OddllVLR(2,2,2,1)
EVLR_3321 = OddllVLR(3,3,2,1)
CVLL_2111 = OlluuVLL(2,1,1,1)
CVLL_2122 = OlluuVLL(2,1,2,2)
CVRR_2111 = OlluuVRR(2,1,1,1)
CVRR_2122 = OlluuVRR(2,1,2,2)
CVLR_2111 = OlluuVLR(2,1,1,1)
CVLR_2122 = OlluuVLR(2,1,2,2)
CSRL_2111 = OlluuSRL(2,1,1,1)
CSRL_2122 = OlluuSRL(2,1,2,2)
CSRL_1211 = OlluuSRL(1,2,1,1)
CSRL_1222 = OlluuSRL(1,2,2,2)
CSRR_2111 = OlluuSRR(2,1,1,1)
CSRR_2122 = OlluuSRR(2,1,2,2)
CSRR_1211 = OlluuSRR(1,2,1,1)
CSRR_1222 = OlluuSRR(1,2,2,2)
CTRR_2111 = OlluuTRR(2,1,1,1)
CTRR_2122 = OlluuTRR(2,1,2,2)
CTRR_1211 = OlluuTRR(1,2,1,1)
CTRR_1222 = OlluuTRR(1,2,2,2)
K2R_31 = K2R(3,1)
K2R_13 = K2R(1,3)
AVLL_1131 = 0.0982515_dp*K1L(3,1) + O4lVLL(1,1,3,1)
AVLL_2231 = 0.0982515_dp*K1L(3,1) + O4lVLL(2,2,3,1)
AVLL_3331 = 0.0982515_dp*K1L(3,1) + O4lVLL(3,3,3,1)
AVRR_1131 = 0.0982515_dp*K1R(3,1) + O4lVRR(1,1,3,1)
AVRR_2231 = 0.0982515_dp*K1R(3,1) + O4lVRR(2,2,3,1)
AVRR_3331 = 0.0982515_dp*K1R(3,1) + O4lVRR(3,3,3,1)
AVLR_1131 = 0.0982515_dp*K1R(3,1) + O4lVLR(1,1,3,1)
AVLR_2231 = 0.0982515_dp*K1R(3,1) + O4lVLR(2,2,3,1)
AVLR_3331 = 0.0982515_dp*K1R(3,1) + O4lVLR(3,3,3,1)
AVLR_3111 = 0.0982515_dp*K1L(3,1) + O4lVLR(3,1,1,1)
AVLR_3122 = 0.0982515_dp*K1L(3,1) + O4lVLR(3,1,2,2)
AVLR_3133 = 0.0982515_dp*K1L(3,1) + O4lVLR(3,1,3,3)
AVLR_2312 = O4lVLR(2,3,1,2)
AVLR_2132 = O4lVLR(2,1,3,2)
ASRR_1131 = O4lSRR(1,1,3,1)
ASRR_2231 = O4lSRR(2,2,3,1)
ASRR_3331 = O4lSRR(3,3,3,1)
ASRR_1113 = O4lSRR(1,1,1,3)
ASRR_2213 = O4lSRR(2,2,1,3)
ASRR_3313 = O4lSRR(3,3,1,3)
ASRR_2312 = O4lSRR(2,3,1,2)
ASRR_2132 = O4lSRR(2,1,3,2)
BVLL_3111 = OllddVLL(3,1,1,1)
BVLL_3122 = OllddVLL(3,1,2,2)
BVLL_3133 = OllddVLL(3,1,3,3)
BVRR_3111 = OllddVRR(3,1,1,1)
BVRR_3122 = OllddVRR(3,1,2,2)
BVRR_3133 = OllddVRR(3,1,3,3)
BVLR_3111 = OllddVLR(3,1,1,1)
BVLR_3122 = OllddVLR(3,1,2,2)
BVLR_3133 = OllddVLR(3,1,3,3)
BSRL_3111 = OllddSRL(3,1,1,1)
BSRL_3122 = OllddSRL(3,1,2,2)
BSRL_3133 = OllddSRL(3,1,3,3)
BSRL_1311 = OllddSRL(1,3,1,1)
BSRL_1322 = OllddSRL(1,3,2,2)
BSRL_1333 = OllddSRL(1,3,3,3)
BSRR_3111 = OllddSRR(3,1,1,1)
BSRR_3122 = OllddSRR(3,1,2,2)
BSRR_3133 = OllddSRR(3,1,3,3)
BSRR_1311 = OllddSRR(1,3,1,1)
BSRR_1322 = OllddSRR(1,3,2,2)
BSRR_1333 = OllddSRR(1,3,3,3)
BTRR_3111 = OllddTRR(3,1,1,1)
BTRR_3122 = OllddTRR(3,1,2,2)
BTRR_3133 = OllddTRR(3,1,3,3)
BTRR_1311 = OllddTRR(1,3,1,1)
BTRR_1322 = OllddTRR(1,3,2,2)
BTRR_1333 = OllddTRR(1,3,3,3)
EVLR_1131 = OddllVLR(1,1,3,1)
EVLR_2231 = OddllVLR(2,2,3,1)
EVLR_3331 = OddllVLR(3,3,3,1)
CVLL_3111 = OlluuVLL(3,1,1,1)
CVLL_3122 = OlluuVLL(3,1,2,2)
CVRR_3111 = OlluuVRR(3,1,1,1)
CVRR_3122 = OlluuVRR(3,1,2,2)
CVLR_3111 = OlluuVLR(3,1,1,1)
CVLR_3122 = OlluuVLR(3,1,2,2)
CSRL_3111 = OlluuSRL(3,1,1,1)
CSRL_3122 = OlluuSRL(3,1,2,2)
CSRL_1311 = OlluuSRL(1,3,1,1)
CSRL_1322 = OlluuSRL(1,3,2,2)
CSRR_3111 = OlluuSRR(3,1,1,1)
CSRR_3122 = OlluuSRR(3,1,2,2)
CSRR_1311 = OlluuSRR(1,3,1,1)
CSRR_1322 = OlluuSRR(1,3,2,2)
CTRR_3111 = OlluuTRR(3,1,1,1)
CTRR_3122 = OlluuTRR(3,1,2,2)
CTRR_1311 = OlluuTRR(1,3,1,1)
CTRR_1322 = OlluuTRR(1,3,2,2)
K2R_23 = K2R(2,3)
K2R_32 = K2R(3,2)
AVLL_1123 = 0.0982515_dp*K1L(2,3) + O4lVLL(1,1,2,3)
AVLL_2223 = 0.0982515_dp*K1L(2,3) + O4lVLL(2,2,2,3)
AVLL_3323 = 0.0982515_dp*K1L(2,3) + O4lVLL(3,3,2,3)
AVRR_1123 = 0.0982515_dp*K1R(2,3) + O4lVRR(1,1,2,3)
AVRR_2223 = 0.0982515_dp*K1R(2,3) + O4lVRR(2,2,2,3)
AVRR_3323 = 0.0982515_dp*K1R(2,3) + O4lVRR(3,3,2,3)
AVLR_1123 = 0.0982515_dp*K1R(2,3) + O4lVLR(1,1,2,3)
AVLR_2223 = 0.0982515_dp*K1R(2,3) + O4lVLR(2,2,2,3)
AVLR_3323 = 0.0982515_dp*K1R(2,3) + O4lVLR(3,3,2,3)
AVLR_2311 = 0.0982515_dp*K1L(2,3) + O4lVLR(2,3,1,1)
AVLR_2322 = 0.0982515_dp*K1L(2,3) + O4lVLR(2,3,2,2)
AVLR_2333 = 0.0982515_dp*K1L(2,3) + O4lVLR(2,3,3,3)
AVLR_1231 = O4lVLR(1,2,3,1)
AVLR_1321 = O4lVLR(1,3,2,1)
ASRR_1123 = O4lSRR(1,1,2,3)
ASRR_2223 = O4lSRR(2,2,2,3)
ASRR_3323 = O4lSRR(3,3,2,3)
ASRR_1132 = O4lSRR(1,1,3,2)
ASRR_2232 = O4lSRR(2,2,3,2)
ASRR_3332 = O4lSRR(3,3,3,2)
ASRR_1231 = O4lSRR(1,2,3,1)
ASRR_1321 = O4lSRR(1,3,2,1)
BVLL_2311 = OllddVLL(2,3,1,1)
BVLL_2322 = OllddVLL(2,3,2,2)
BVLL_2333 = OllddVLL(2,3,3,3)
BVRR_2311 = OllddVRR(2,3,1,1)
BVRR_2322 = OllddVRR(2,3,2,2)
BVRR_2333 = OllddVRR(2,3,3,3)
BVLR_2311 = OllddVLR(2,3,1,1)
BVLR_2322 = OllddVLR(2,3,2,2)
BVLR_2333 = OllddVLR(2,3,3,3)
BSRL_2311 = OllddSRL(2,3,1,1)
BSRL_2322 = OllddSRL(2,3,2,2)
BSRL_2333 = OllddSRL(2,3,3,3)
BSRL_3211 = OllddSRL(3,2,1,1)
BSRL_3222 = OllddSRL(3,2,2,2)
BSRL_3233 = OllddSRL(3,2,3,3)
BSRR_2311 = OllddSRR(2,3,1,1)
BSRR_2322 = OllddSRR(2,3,2,2)
BSRR_2333 = OllddSRR(2,3,3,3)
BSRR_3211 = OllddSRR(3,2,1,1)
BSRR_3222 = OllddSRR(3,2,2,2)
BSRR_3233 = OllddSRR(3,2,3,3)
BTRR_2311 = OllddTRR(2,3,1,1)
BTRR_2322 = OllddTRR(2,3,2,2)
BTRR_2333 = OllddTRR(2,3,3,3)
BTRR_3211 = OllddTRR(3,2,1,1)
BTRR_3222 = OllddTRR(3,2,2,2)
BTRR_3233 = OllddTRR(3,2,3,3)
EVLR_1123 = OddllVLR(1,1,2,3)
EVLR_2223 = OddllVLR(2,2,2,3)
EVLR_3323 = OddllVLR(3,3,2,3)
CVLL_2311 = OlluuVLL(2,3,1,1)
CVLL_2322 = OlluuVLL(2,3,2,2)
CVRR_2311 = OlluuVRR(2,3,1,1)
CVRR_2322 = OlluuVRR(2,3,2,2)
CVLR_2311 = OlluuVLR(2,3,1,1)
CVLR_2322 = OlluuVLR(2,3,2,2)
CSRL_2311 = OlluuSRL(2,3,1,1)
CSRL_2322 = OlluuSRL(2,3,2,2)
CSRL_3211 = OlluuSRL(3,2,1,1)
CSRL_3222 = OlluuSRL(3,2,2,2)
CSRR_2311 = OlluuSRR(2,3,1,1)
CSRR_2322 = OlluuSRR(2,3,2,2)
CSRR_3211 = OlluuSRR(3,2,1,1)
CSRR_3222 = OlluuSRR(3,2,2,2)
CTRR_2311 = OlluuTRR(2,3,1,1)
CTRR_2322 = OlluuTRR(2,3,2,2)
CTRR_3211 = OlluuTRR(3,2,1,1)
CTRR_3222 = OlluuTRR(3,2,2,2)
AVLL_1313 = O4lVLL(1,3,1,3)
AVRR_1313 = O4lVRR(1,3,1,3)
AVLR_1313 = O4lVLR(1,3,1,3)
ASRR_1313 = O4lSRR(1,3,1,3)
ASRR_3131 = O4lSRR(3,1,3,1)
AVLL_2323 = O4lVLL(2,3,2,3)
AVRR_2323 = O4lVRR(2,3,2,3)
AVLR_2323 = O4lVLR(2,3,2,3)
ASRR_2323 = O4lSRR(2,3,2,3)
ASRR_3232 = O4lSRR(3,2,3,2)
AVLL_1212 = O4lVLL(1,2,1,2)
AVRR_1212 = O4lVRR(1,2,1,2)
AVLR_1212 = O4lVLR(1,2,1,2)
ASRR_1212 = O4lSRR(1,2,1,2)
ASRR_2121 = O4lSRR(2,1,2,1)
AVLL_1232 = O4lVLL(1,2,3,2)
AVRR_1232 = O4lVRR(1,2,3,2)
AVLR_1232 = O4lVLR(1,2,3,2)
AVLR_2321 = O4lVLR(2,3,2,1)
ASRR_1232 = O4lSRR(1,2,3,2)
ASRR_2123 = O4lSRR(2,1,2,3)
AVLL_1213 = O4lVLL(1,2,1,3)
AVRR_1213 = O4lVRR(1,2,1,3)
AVLR_1213 = O4lVLR(1,2,1,3)
AVLR_1312 = O4lVLR(1,3,1,2)
ASRR_1213 = O4lSRR(1,2,1,3)
ASRR_2131 = O4lSRR(2,1,3,1)
AVLL_1323 = O4lVLL(1,3,2,3)
AVRR_1323 = O4lVRR(1,3,2,3)
AVLR_1323 = O4lVLR(1,3,2,3)
AVLR_2313 = O4lVLR(2,3,1,3)
ASRR_1323 = O4lSRR(1,3,2,3)
ASRR_3132 = O4lSRR(3,1,3,2)

 ! **** hLLp **** 
 
Call Calculate_hLLp(OH2lSL,OH2lSR,BrhtoMuE,BrhtoTauE,BrhtoTauMu)


 ! **** LLpGamma **** 
 
Call Calculate_LLpGamma(K2L,K2R,muEgamma,tauEgamma,tauMuGamma)


 ! **** Lto3Lp **** 
 
Call Calculate_Lto3Lp(K1L,K1R,K2L,K2R,O4lSLL,O4lSRR,O4lSRL,O4lSLR,O4lVRR,             & 
& O4lVLL,O4lVRL,O4lVLR,O4lTLL,O4lTRR,BRmuTo3e,BRtauTo3e,BRtauTo3mu)


 ! **** LtoL1L2L2 **** 
 
Call Calculate_LtoL1L2L2(K1L,K1R,K2L,K2R,O4lSLL,O4lSRR,O4lSRL,O4lSLR,O4lVRR,          & 
& O4lVLL,O4lVRL,O4lVLR,O4lTLL,O4lTRR,O4lSLLcross,O4lSRRcross,O4lSRLcross,O4lSLRcross,    & 
& O4lVRRcross,O4lVLLcross,O4lVRLcross,O4lVLRcross,O4lTLLcross,O4lTRRcross,               & 
& BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2)


 ! **** MuEconversion **** 
 
Call Calculate_MuEconversion(K1L,K1R,K2L,K2R,OllddSLL,OllddSRR,OllddSRL,              & 
& OllddSLR,OllddVRR,OllddVLL,OllddVRL,OllddVLR,OllddTLL,OllddTLR,OllddTRL,               & 
& OllddTRR,OlluuSLL,OlluuSRR,OlluuSRL,OlluuSLR,OlluuVRR,OlluuVLL,OlluuVRL,               & 
& OlluuVLR,OlluuTLL,OlluuTLR,OlluuTRL,OlluuTRR,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,          & 
& CRmuEAu,CRmuEPb)


 ! **** TauLMeson **** 
 
Call Calculate_TauLMeson(OllddSLL,OllddSRR,OllddSRL,OllddSLR,OllddVRR,OllddVLL,       & 
& OllddVRL,OllddVLR,OlluuSLL,OlluuSRR,OlluuSRL,OlluuSLR,OlluuVRR,OlluuVLL,               & 
& OlluuVRL,OlluuVLR,BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,        & 
& BrTautoMuEtap)


 ! **** ZLLp **** 
 
Call Calculate_ZLLp(OZ2lSL,OZ2lSR,OZ2lVL,OZ2lVR,BrZtoMuE,BrZtoTauE,BrZtoTauMu)

Mhh= Mhh_s 
Mhh2 = Mhh2_s 
MAh= MAh_s 
MAh2 = MAh2_s 

! *****  G minus 2 ***** 

Call Gminus2(1,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplHmcHmVP,ae)

Call Gminus2(2,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplHmcHmVP,amu)

Call Gminus2(3,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFecHmL,cplcFvFecHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplHmcHmVP,atau)


! *****  Lepton EDM ***** 

Call LeptonEDM(1,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHmcHmVP,cplcVWmVPVWm,EDMe)

Call LeptonEDM(2,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHmcHmVP,cplcVWmVPVWm,EDMmu)

Call LeptonEDM(3,MAh,MAh2,MFe,MFe2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,         & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHmcHmVP,cplcVWmVPVWm,EDMtau)


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
Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,vd,vu,g1,g2,             & 
& g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,.False.)

Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,           & 
& m112,m222,vd,vu,(/ ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,           & 
& MVWm2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,v,ZDL,ZEL,ZUL,ZA,ZH,ZP,ZW,ZZ,alphaH,betaH,               & 
& vd,vu,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Yu,Yd,Ye,m122,m112,m222,GenerationMixing,kont)

Call CouplingsForVectorBosons(g1,g2,TW,ZP,vd,vu,ZH,ZA,ZDL,ZUL,ZEL,cplcFdFdVPL,        & 
& cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,              & 
& cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcVWmVPVWm,cplHmcHmVPVP,cplcVWmVPVPVWm1,       & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,         & 
& cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,              & 
& cplhhhhVZVZ,cplHmcHmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,              & 
& cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,    & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcVWmVWm,cplAhAhcVWmVWm,    & 
& cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,& 
& cplcHmVWmVZ,cplcHmVPVWm,cplHmcHmVPVZ,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)

Call DeltaRho(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,             & 
& MVWm2,MVZ,MVZ2,cplAhAhcVWmVWm,cplAhAhVZVZ,cplAhhhVZ,cplAhHmcVWm,cplcFdFdVZL,           & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuVZL,           & 
& cplcFuFuVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplcgAgWmcVWm,         & 
& cplcgWmgWmVZ,cplcgWpCgAcVWm,cplcgWpCgWpCVZ,cplcgWpCgZcVWm,cplcgZgWmcVWm,               & 
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVPVPVWm1,              & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWm,cplcVWmVWmVZ,cplcVWmVWmVZVZ1,             & 
& cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplhhcVWmVWm,cplhhhhcVWmVWm,cplhhhhVZVZ,               & 
& cplhhHmcVWm,cplhhVZVZ,cplHmcHmcVWmVWm,cplHmcHmVZ,cplHmcHmVZVZ,cplHmcVWmVP,             & 
& cplHmcVWmVZ,dRho)

Call STUparameter(vSM,g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,MAh,MAh2,MFd,MFd2,MFe,            & 
& MFe2,MFu,MFu2,Mhh,Mhh2,MHm,MHm2,MVWm,MVWm2,MVZ,MVZ2,cplcFdFdVPL,cplcFdFdVPR,           & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,           & 
& cplHmcHmVP,cplHmcVWmVP,cplcVWmVPVWm,cplHmcHmVPVP,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,      & 
& cplcVWmVPVPVWm3,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,           & 
& cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHmcHmVZVZ,    & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplAhHmcVWm,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,  & 
& cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcVWmVWm,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHmcHmcVWmVWm, & 
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcHmVWmVZ,cplcHmVPVWm,      & 
& cplHmcHmVPVZ,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,Spar,Tpar,Upar)

If (WriteParametersAtQ) Then 
scalein = SetRenormalizationScale(160._dp**2) 
Else 
scalein = SetRenormalizationScale(scale_save**2) 
End if 
mz2 = mzsave**2 
mz = mzsave 
End subroutine CalculateLowEnergyConstraints 
 
 
End Module LowEnergy_gumTHDMII 
