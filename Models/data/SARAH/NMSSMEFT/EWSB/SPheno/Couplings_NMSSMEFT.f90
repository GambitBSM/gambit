! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.12.3 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 17:27 on 22.10.2018   
! ----------------------------------------------------------------------  
 
 
Module Couplings_NMSSMEFT
 
Use Control 
Use Settings 
Use Model_Data_NMSSMEFT 
Use Mathematics, Only: CompareMatrices, Adjungate 
 
Contains 
 
 Subroutine AllCouplingsReallyAll(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,             & 
& TW,g3,UM,UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,         & 
& cplAhHpmcHpm,cplhhhhhh,cplhhHpmcHpm,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,               & 
& cplAhAhHpmcHpm,cplAhhhhhhh,cplAhhhHpmcHpm,cplhhhhhhhh,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm,& 
& cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,            & 
& cplHpmcHpmVZ,cplhhcVWmVWm,cplhhVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,            & 
& cplcHpmVWmVZ,cplAhAhcVWmVWm,cplAhAhVZVZ,cplAhHpmcVWmVP,cplAhHpmcVWmVZ,cplAhcHpmVPVWm,  & 
& cplAhcHpmVWmVZ,cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWmVP,cplhhHpmcVWmVZ,               & 
& cplhhcHpmVPVWm,cplhhcHpmVWmVZ,cplHpmcHpmVPVP,cplHpmcHpmVPVZ,cplHpmcHpmcVWmVWm,         & 
& cplHpmcHpmVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL,cplcChaChaAhR,        & 
& cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,             & 
& cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,     & 
& cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,       & 
& cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,               & 
& cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,cplcFdFdVGL,     & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,           & 
& cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,            & 
& cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,            & 
& cplcFvFvVZR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,    & 
& cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,    & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3, & 
& cplcgGgGVG,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,        & 
& cplcgZgWmcVWm,cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,               & 
& cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHpm,       & 
& cplcgWpCgAcHpm,cplcgWmgWmhh,cplcgZgWmcHpm,cplcgWpCgWpChh,cplcgZgWpCHpm,cplcgZgZhh,     & 
& cplcgWmgZHpm,cplcgWpCgZcHpm)

Implicit None 
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),g1,g2,ZH(3,3),ZP(2,2),TW,g3

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,UM(2,2),UP(2,2),ZN(5,5),Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),            & 
& ZEL(3,3),ZER(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplAhAhAhAh(3,3,3,3),cplAhAhAhhh(3,3,3,3),        & 
& cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhhhhhhh(3,3,3,3),cplAhhhHpmcHpm(3,3,2,2),& 
& cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),cplHpmHpmcHpmcHpm(2,2,2,2),               & 
& cplAhhhVZ(3,3),cplAhHpmcVWm(3,2),cplAhcHpmVWm(3,2),cplhhHpmcVWm(3,2),cplhhcHpmVWm(3,2),& 
& cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),cplhhcVWmVWm(3),cplhhVZVZ(3),cplHpmcVWmVP(2),      & 
& cplHpmcVWmVZ(2),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplAhAhcVWmVWm(3,3),cplAhAhVZVZ(3,3),  & 
& cplAhHpmcVWmVP(3,2),cplAhHpmcVWmVZ(3,2),cplAhcHpmVPVWm(3,2),cplAhcHpmVWmVZ(3,2),       & 
& cplhhhhcVWmVWm(3,3),cplhhhhVZVZ(3,3),cplhhHpmcVWmVP(3,2),cplhhHpmcVWmVZ(3,2),          & 
& cplhhcHpmVPVWm(3,2),cplhhcHpmVWmVZ(3,2),cplHpmcHpmVPVP(2,2),cplHpmcHpmVPVZ(2,2),       & 
& cplHpmcHpmcVWmVWm(2,2),cplHpmcHpmVZVZ(2,2),cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,        & 
& cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),     & 
& cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),           & 
& cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),     & 
& cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),     & 
& cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),     & 
& cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),       & 
& cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),       & 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),       & 
& cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),         & 
& cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),             & 
& cplcChaChiVWmL(2,5),cplcChaChiVWmR(2,5),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),             & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),& 
& cplcFuFdcVWmR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),& 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),& 
& cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),& 
& cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,& 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2, & 
& cplcVWmcVWmVWmVWm3,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,         & 
& cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgWpCgWpCVP,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm, & 
& cplcgWmgWmAh(3),cplcgWpCgWpCAh(3),cplcgZgAhh(3),cplcgWmgAHpm(2),cplcgWpCgAcHpm(2),     & 
& cplcgWmgWmhh(3),cplcgZgWmcHpm(2),cplcgWpCgWpChh(3),cplcgZgWpCHpm(2),cplcgZgZhh(3),     & 
& cplcgWmgZHpm(2),cplcgWpCgZcHpm(2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'AllCouplingsReallyAll'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhAhT(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhhhhhT(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpmT(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplinghhhhhhT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpmT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhAhT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhhhT(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhAhAhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhhhhhT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZA,cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHpmcHpmT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,ZP,cplAhAhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhhhhhhhT(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHpmcHpmT(gt1,gt2,gt3,gt4,g2,lam,kap,ZH,ZA,ZP,cplAhhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplinghhhhhhhhT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHpmcHpmT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZP,cplhhhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHpmHpmcHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpmHpmcHpmcHpmT(gt1,gt2,gt3,gt4,g1,g2,lam,ZP,cplHpmHpmcHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmT(gt1,gt2,g2,ZA,ZP,cplAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplAhcHpmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcHpmVWmT(gt1,gt2,g2,ZA,ZP,cplAhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmT(gt1,gt2,g2,ZH,ZP,cplhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcHpmVWmT(gt1,gt2,g2,ZH,ZP,cplhhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVP(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZ(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplhhVZVZ = 0._dp 
Do gt1 = 1, 3
Call CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHpmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVPT(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVP(gt1))

End Do 


cplHpmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVZ(gt1))

End Do 


cplcHpmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVPVWmT(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVPVWm(gt1))

End Do 


cplcHpmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVWmVZ(gt1))

End Do 


cplAhAhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhcVWmVWmT(gt1,gt2,g2,ZA,cplAhAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplAhAhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhVZVZT(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWmVP = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmVPT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHpmcVWmVP(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWmVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHpmcVWmVZ(gt1,gt2))

 End Do 
End Do 


cplAhcHpmVPVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcHpmVPVWmT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHpmVPVWm(gt1,gt2))

 End Do 
End Do 


cplAhcHpmVWmVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcHpmVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHpmVWmVZ(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhcVWmVWmT(gt1,gt2,g2,ZH,cplhhhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhVZVZT(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWmVP = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmVPT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHpmcVWmVP(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWmVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHpmcVWmVZ(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVPVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcHpmVPVWmT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHpmVPVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVWmVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcHpmVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHpmVWmVZ(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVPT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVP(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVZT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVZ(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmcVWmVWmT(gt1,gt2,g2,ZP,cplHpmcHpmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZVZT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZVZ(gt1,gt2))

 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVGT(g3,cplVGVGVG)



cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmT(g2,TW,cplcVWmVPVWm)



cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZT(g2,TW,cplcVWmVWmVZ)



cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,lam,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)        & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,lam,kap,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)      & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)& 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,lam,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)        & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,lam,kap,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)      & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)& 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3) & 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3),               & 
& cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVPL = 0._dp 
cplcChaChaVPR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVPT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVPL(gt1,gt2),cplcChaChaVPR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVGL = 0._dp 
cplcFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVGT(gt1,gt2,g3,cplcFdFdVGL(gt1,gt2),cplcFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVPL = 0._dp 
cplcFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVPT(gt1,gt2,g1,g2,TW,cplcFdFdVPL(gt1,gt2),cplcFdFdVPR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVPL = 0._dp 
cplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVPT(gt1,gt2,g1,g2,TW,cplcFeFeVPL(gt1,gt2),cplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmT(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVGL = 0._dp 
cplcFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVGT(gt1,gt2,g3,cplcFuFuVGL(gt1,gt2),cplcFuFuVGR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVPL = 0._dp 
cplcFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVPT(gt1,gt2,g1,g2,TW,cplcFuFuVPL(gt1,gt2),cplcFuFuVPR(gt1,gt2))

 End Do 
End Do 


cplcFdFuVWmL = 0._dp 
cplcFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFuVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFdFuVWmL(gt1,gt2),cplcFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvVWmL = 0._dp 
cplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,cplcFeFvVWmL(gt1,gt2),cplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplVGVGVGVG1 = 0._dp 
cplVGVGVGVG2 = 0._dp 
cplVGVGVGVG3 = 0._dp 
Call CouplingVGVGVGVGT(g3,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3)



cplcVWmVPVPVWm1 = 0._dp 
cplcVWmVPVPVWm2 = 0._dp 
cplcVWmVPVPVWm3 = 0._dp 
Call CouplingcVWmVPVPVWmT(g2,TW,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3)



cplcVWmVPVWmVZ1 = 0._dp 
cplcVWmVPVWmVZ2 = 0._dp 
cplcVWmVPVWmVZ3 = 0._dp 
Call CouplingcVWmVPVWmVZT(g2,TW,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)



cplcVWmcVWmVWmVWm1 = 0._dp 
cplcVWmcVWmVWmVWm2 = 0._dp 
cplcVWmcVWmVWmVWm3 = 0._dp 
Call CouplingcVWmcVWmVWmVWmT(g2,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)



cplcVWmVWmVZVZ1 = 0._dp 
cplcVWmVWmVZVZ2 = 0._dp 
cplcVWmVWmVZVZ3 = 0._dp 
Call CouplingcVWmVWmVZVZT(g2,TW,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3)



cplcgGgGVG = 0._dp 
Call CouplingcgGgGVGT(g3,cplcgGgGVG)



cplcgWmgAVWm = 0._dp 
Call CouplingcgWmgAVWmT(g2,TW,cplcgWmgAVWm)



cplcgWpCgAcVWm = 0._dp 
Call CouplingcgWpCgAcVWmT(g2,TW,cplcgWpCgAcVWm)



cplcgWmgWmVP = 0._dp 
Call CouplingcgWmgWmVPT(g2,TW,cplcgWmgWmVP)



cplcgWmgWmVZ = 0._dp 
Call CouplingcgWmgWmVZT(g2,TW,cplcgWmgWmVZ)



cplcgAgWmcVWm = 0._dp 
Call CouplingcgAgWmcVWmT(g2,TW,cplcgAgWmcVWm)



cplcgZgWmcVWm = 0._dp 
Call CouplingcgZgWmcVWmT(g2,TW,cplcgZgWmcVWm)



cplcgWpCgWpCVP = 0._dp 
Call CouplingcgWpCgWpCVPT(g2,TW,cplcgWpCgWpCVP)



cplcgAgWpCVWm = 0._dp 
Call CouplingcgAgWpCVWmT(g2,TW,cplcgAgWpCVWm)



cplcgZgWpCVWm = 0._dp 
Call CouplingcgZgWpCVWmT(g2,TW,cplcgZgWpCVWm)



cplcgWpCgWpCVZ = 0._dp 
Call CouplingcgWpCgWpCVZT(g2,TW,cplcgWpCgWpCVZ)



cplcgWmgZVWm = 0._dp 
Call CouplingcgWmgZVWmT(g2,TW,cplcgWmgZVWm)



cplcgWpCgZcVWm = 0._dp 
Call CouplingcgWpCgZcVWmT(g2,TW,cplcgWpCgZcVWm)



cplcgWmgWmAh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWmgWmAhT(gt3,g2,vd,vu,ZA,cplcgWmgWmAh(gt3))

End Do 


cplcgWpCgWpCAh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWpCgWpCAhT(gt3,g2,vd,vu,ZA,cplcgWpCgWpCAh(gt3))

End Do 


cplcgZgAhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgZgAhhT(gt3,g1,g2,vd,vu,ZH,TW,cplcgZgAhh(gt3))

End Do 


cplcgWmgAHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgAHpmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWmgAHpm(gt3))

End Do 


cplcgWpCgAcHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgAcHpmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWpCgAcHpm(gt3))

End Do 


cplcgWmgWmhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWmgWmhhT(gt3,g2,vd,vu,ZH,cplcgWmgWmhh(gt3))

End Do 


cplcgZgWmcHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWmcHpmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgZgWmcHpm(gt3))

End Do 


cplcgWpCgWpChh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWpCgWpChhT(gt3,g2,vd,vu,ZH,cplcgWpCgWpChh(gt3))

End Do 


cplcgZgWpCHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWpCHpmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgZgWpCHpm(gt3))

End Do 


cplcgZgZhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgZgZhhT(gt3,g1,g2,vd,vu,ZH,TW,cplcgZgZhh(gt3))

End Do 


cplcgWmgZHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgZHpmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWmgZHpm(gt3))

End Do 


cplcgWpCgZcHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgZcHpmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWpCgZcHpm(gt3))

End Do 


Iname = Iname - 1 
End Subroutine AllCouplingsReallyAll

Subroutine AllCouplings(lam,Tlam,kap,Tk,vd,vu,vS,ZA,g1,g2,ZH,ZP,TW,g3,UM,             & 
& UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,     & 
& cplhhhhhh,cplhhHpmcHpm,cplAhhhVZ,cplAhHpmcVWm,cplAhcHpmVWm,cplhhHpmcVWm,               & 
& cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplhhcVWmVWm,cplhhVZVZ,cplHpmcVWmVP,            & 
& cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,            & 
& cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,         & 
& cplcChaChahhL,cplcChaChahhR,cplChiChihhL,cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,   & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,           & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,         & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,   & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,   & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,           & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFvFvVZL,cplcFvFvVZR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),g1,g2,ZH(3,3),ZP(2,2),TW,g3

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,UM(2,2),UP(2,2),ZN(5,5),Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),            & 
& ZEL(3,3),ZER(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplAhhhVZ(3,3),cplAhHpmcVWm(3,2),cplAhcHpmVWm(3,2),& 
& cplhhHpmcVWm(3,2),cplhhcHpmVWm(3,2),cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),               & 
& cplhhcVWmVWm(3),cplhhVZVZ(3),cplHpmcVWmVP(2),cplHpmcVWmVZ(2),cplcHpmVPVWm(2),          & 
& cplcHpmVWmVZ(2),cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcChaChaAhL(2,2,3),              & 
& cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),       & 
& cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),           & 
& cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplcChaChahhL(2,2,3),   & 
& cplcChaChahhR(2,2,3),cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplcChaChiHpmL(2,5,2),    & 
& cplcChaChiHpmR(2,5,2),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcFuFdcHpmL(3,3,2),      & 
& cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),cplcFvFecHpmL(3,3,2),       & 
& cplcFvFecHpmR(3,3,2),cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),        & 
& cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplChiChacVWmL(5,2),       & 
& cplChiChacVWmR(5,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),          & 
& cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplcChaChiVWmL(2,5),            & 
& cplcChaChiVWmR(2,5),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecVWmL(3,3),& 
& cplcFvFecVWmR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),& 
& cplcFeFvVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'AllCouplings'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhAhT(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhhhhhT(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpmT(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplinghhhhhhT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpmT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmT(gt1,gt2,g2,ZA,ZP,cplAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplAhcHpmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcHpmVWmT(gt1,gt2,g2,ZA,ZP,cplAhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmT(gt1,gt2,g2,ZH,ZP,cplhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcHpmVWmT(gt1,gt2,g2,ZH,ZP,cplhhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVP(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZT(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZ(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplhhVZVZ = 0._dp 
Do gt1 = 1, 3
Call CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHpmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVPT(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVP(gt1))

End Do 


cplHpmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVZ(gt1))

End Do 


cplcHpmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVPVWmT(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVPVWm(gt1))

End Do 


cplcHpmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVWmVZ(gt1))

End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVGT(g3,cplVGVGVG)



cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmT(g2,TW,cplcVWmVPVWm)



cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZT(g2,TW,cplcVWmVWmVZ)



cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaAhT(gt1,gt2,gt3,g2,lam,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)        & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,lam,kap,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)      & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)& 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChahhT(gt1,gt2,gt3,g2,lam,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)        & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChihhT(gt1,gt2,gt3,g1,g2,lam,kap,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)      & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
  Do gt3 = 1, 2
Call CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)& 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3) & 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3),               & 
& cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
Call CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVPL = 0._dp 
cplcChaChaVPR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVPT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVPL(gt1,gt2),cplcChaChaVPR(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
Call CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVGL = 0._dp 
cplcFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVGT(gt1,gt2,g3,cplcFdFdVGL(gt1,gt2),cplcFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVPL = 0._dp 
cplcFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVPT(gt1,gt2,g1,g2,TW,cplcFdFdVPL(gt1,gt2),cplcFdFdVPR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVPL = 0._dp 
cplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVPT(gt1,gt2,g1,g2,TW,cplcFeFeVPL(gt1,gt2),cplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmT(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVGL = 0._dp 
cplcFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVGT(gt1,gt2,g3,cplcFuFuVGL(gt1,gt2),cplcFuFuVGR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVPL = 0._dp 
cplcFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVPT(gt1,gt2,g1,g2,TW,cplcFuFuVPL(gt1,gt2),cplcFuFuVPR(gt1,gt2))

 End Do 
End Do 


cplcFdFuVWmL = 0._dp 
cplcFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFuVWmT(gt1,gt2,g2,ZDL,ZUL,cplcFdFuVWmL(gt1,gt2),cplcFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvVWmL = 0._dp 
cplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,cplcFeFvVWmL(gt1,gt2),cplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine AllCouplings

Subroutine CouplingAhAhAhT(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp)
res = res-((Tk*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp))
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhT  
 
 
Subroutine CouplingAhAhhhT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1**2*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))/4._dp
res = res-(g2**2*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))/4._dp
res = res+(g1**2*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/4._dp
res = res+(g2**2*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/4._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))
res = res+(g1**2*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/4._dp
res = res+(g2**2*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/4._dp
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(g1**2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))/4._dp
res = res-(g2**2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))/4._dp
res = res+(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vu*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res-2*vS*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
res = res+(Tk*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhT  
 
 
Subroutine CouplingAhhhhhT(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-((Conjg(Tk)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
res = res+(Tk*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhT  
 
 
Subroutine CouplingAhHpmcHpmT(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,vd,vu,vS,ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/4._dp
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(g2**2*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/4._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+vS*kap*Conjg(lam)*ZA(gt1,3)*ZP(gt2,2)*ZP(gt3,1)
res = res-((Conjg(Tlam)*ZA(gt1,3)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
res = res-(g2**2*vu*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/4._dp
res = res+(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(g2**2*vd*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/4._dp
res = res+(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZP(gt2,1)*ZP(gt3,2))
res = res+(Tlam*ZA(gt1,3)*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp)
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcHpmT  
 
 
Subroutine CouplinghhhhhhT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZH(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(-3*g1**2*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1))/4._dp
res = res+(-3*g2**2*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1))/4._dp
res = res+(g1**2*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/4._dp
res = res+(g2**2*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/4._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1))
res = res+(g1**2*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/4._dp
res = res+(g2**2*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/4._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res+(g1**2*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/4._dp
res = res+(g2**2*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/4._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))
res = res+(g1**2*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/4._dp
res = res+(g2**2*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/4._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res+(g1**2*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/4._dp
res = res+(g2**2*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/4._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(g1**2*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/4._dp
res = res+(g2**2*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/4._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res+(-3*g1**2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2))/4._dp
res = res+(-3*g2**2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2))/4._dp
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))
res = res-6*vS*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)
res = res-((Conjg(Tk)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
res = res-((Tk*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhT  
 
 
Subroutine CouplinghhHpmcHpmT(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1**2*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))/4._dp
res = res-(g2**2*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))/4._dp
res = res+(g1**2*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))/4._dp
res = res-(g2**2*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))/4._dp
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,1))
res = res-(g2**2*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/4._dp
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(g2**2*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/4._dp
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(vS*kap*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,1))
res = res-((Conjg(Tlam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
res = res-(g2**2*vu*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/4._dp
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(g2**2*vd*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/4._dp
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,2))
res = res-((Tlam*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp))
res = res+(g1**2*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))/4._dp
res = res-(g2**2*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))/4._dp
res = res-(g1**2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))/4._dp
res = res-(g2**2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))/4._dp
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcHpmT  
 
 
Subroutine CouplingAhAhAhAhT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(-3*g1**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res = res+(-3*g2**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,1))
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,1))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res = res+(-3*g1**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res = res+(-3*g2**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))
res = res-6*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,3)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAhT  
 
 
Subroutine CouplingAhAhAhhhT(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhhT  
 
 
Subroutine CouplingAhAhhhhhT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res-(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res-(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
res = res-2*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,3)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhhT  
 
 
Subroutine CouplingAhAhHpmcHpmT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res-(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res-(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,2)
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHpmcHpmT  
 
 
Subroutine CouplingAhhhhhhhT(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhhT  
 
 
Subroutine CouplingAhhhHpmcHpmT(gt1,gt2,gt3,gt4,g2,lam,kap,ZH,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g2,ZH(3,3),ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(g2**2*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
res = res-(g2**2*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res+(lam*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(g2**2*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res+(lam*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHpmcHpmT  
 
 
Subroutine CouplinghhhhhhhhT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(-3*g1**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res+(-3*g2**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res+(g1**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res+(g2**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
res = res+(g1**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res = res+(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res = res+(g1**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res = res+(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,1))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(g1**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res = res+(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res = res+(g1**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res = res+(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(g1**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res+(g2**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res+(-3*g1**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res+(-3*g2**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
res = res-6*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,3)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhT  
 
 
Subroutine CouplinghhhhHpmcHpmT(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res+(g1**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1))
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
res = res+(g1**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(g1**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpmcHpmT  
 
 
Subroutine CouplingHpmHpmcHpmcHpmT(gt1,gt2,gt3,gt4,g1,g2,lam,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmHpmcHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1**2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/2._dp
res = res-(g2**2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/2._dp
res = res+(g1**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res+(g2**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res+(g1**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res+(g2**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res = res-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res+(g1**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res+(g2**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res+(g1**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res+(g2**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res = res-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-(g1**2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/2._dp
res = res-(g2**2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmHpmcHpmcHpmT  
 
 
Subroutine CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZA(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*Cos(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res-(g1*Sin(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2*Cos(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(g1*Sin(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhVZT  
 
 
Subroutine CouplingAhHpmcVWmT(gt1,gt2,g2,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcVWmT  
 
 
Subroutine CouplingAhcHpmVWmT(gt1,gt2,g2,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHpmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHpmVWmT  
 
 
Subroutine CouplinghhHpmcVWmT(gt1,gt2,g2,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcVWmT  
 
 
Subroutine CouplinghhcHpmVWmT(gt1,gt2,g2,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpmVWmT  
 
 
Subroutine CouplingHpmcHpmVPT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g2*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPT  
 
 
Subroutine CouplingHpmcHpmVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(g1*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVZT  
 
 
Subroutine CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*ZH(gt1,1))/2._dp
res = res+(g2**2*vu*ZH(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcVWmVWmT  
 
 
Subroutine CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*Cos(TW)**2*ZH(gt1,1))/2._dp
res = res+g1*g2*vd*Cos(TW)*Sin(TW)*ZH(gt1,1)
res = res+(g1**2*vd*Sin(TW)**2*ZH(gt1,1))/2._dp
res = res+(g2**2*vu*Cos(TW)**2*ZH(gt1,2))/2._dp
res = res+g1*g2*vu*Cos(TW)*Sin(TW)*ZH(gt1,2)
res = res+(g1**2*vu*Sin(TW)**2*ZH(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhVZVZT  
 
 
Subroutine CouplingHpmcVWmVPT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcVWmVPT  
 
 
Subroutine CouplingHpmcVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcVWmVZT  
 
 
Subroutine CouplingcHpmVPVWmT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpmVPVWmT  
 
 
Subroutine CouplingcHpmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpmVWmVZT  
 
 
Subroutine CouplingAhAhcVWmVWmT(gt1,gt2,g2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhcVWmVWmT  
 
 
Subroutine CouplingAhAhVZVZT(gt1,gt2,g1,g2,ZA,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*Cos(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,1)*ZA(gt2,1)
res = res+(g1**2*Sin(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+(g2**2*Cos(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,2)*ZA(gt2,2)
res = res+(g1**2*Sin(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhVZVZT  
 
 
Subroutine CouplingAhHpmcVWmVPT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcVWmVPT  
 
 
Subroutine CouplingAhHpmcVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcVWmVZT  
 
 
Subroutine CouplingAhcHpmVPVWmT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHpmVPVWmT  
 
 
Subroutine CouplingAhcHpmVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHpmVWmVZT  
 
 
Subroutine CouplinghhhhcVWmVWmT(gt1,gt2,g2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWmVWmT  
 
 
Subroutine CouplinghhhhVZVZT(gt1,gt2,g1,g2,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*Cos(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,1)*ZH(gt2,1)
res = res+(g1**2*Sin(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2**2*Cos(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,2)*ZH(gt2,2)
res = res+(g1**2*Sin(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZT  
 
 
Subroutine CouplinghhHpmcVWmVPT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcVWmVPT  
 
 
Subroutine CouplinghhHpmcVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcVWmVZT  
 
 
Subroutine CouplinghhcHpmVPVWmT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpmVPVWmT  
 
 
Subroutine CouplinghhcHpmVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpmVWmVZT  
 
 
Subroutine CouplingHpmcHpmVPVPT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVPVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1**2*Cos(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,1)*ZP(gt2,1)
res = res+(g2**2*Sin(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1**2*Cos(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,2)*ZP(gt2,2)
res = res+(g2**2*Sin(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPVPT  
 
 
Subroutine CouplingHpmcHpmVPVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVPVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1**2*Sin(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/4._dp
res = res+(g2**2*Sin(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/4._dp
res = res+(g1*g2*Cos(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1**2*Sin(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/4._dp
res = res+(g2**2*Sin(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPVZT  
 
 
Subroutine CouplingHpmcHpmcVWmVWmT(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmcVWmVWmT  
 
 
Subroutine CouplingHpmcHpmVZVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*Cos(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))
res = res+(g1**2*Sin(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2**2*Cos(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))
res = res+(g1**2*Sin(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVZVZT  
 
 
Subroutine CouplingVGVGVGT(g3,res)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVG' 
 
res = 0._dp 
res = res+g3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVGT  
 
 
Subroutine CouplingcVWmVPVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVWm' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVWmT  
 
 
Subroutine CouplingcVWmVWmVZT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVWmVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVWmVZT  
 
 
Subroutine CouplingcChaChaAhT(gt1,gt2,gt3,g2,lam,ZA,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-((g2*Conjg(UM(gt2,2))*Conjg(UP(gt1,1))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-((g2*Conjg(UM(gt2,1))*Conjg(UP(gt1,2))*ZA(gt3,2))/sqrt(2._dp))
resL = resL+(lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2))*ZA(gt3,3))/sqrt(2._dp)
resR = 0._dp 
resR = resR+(g2*UM(gt1,2)*UP(gt2,1)*ZA(gt3,1))/sqrt(2._dp)
resR = resR+(g2*UM(gt1,1)*UP(gt2,2)*ZA(gt3,2))/sqrt(2._dp)
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2)*ZA(gt3,3))/sqrt(2._dp))
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaAhT  
 
 
Subroutine CouplingChiChiAhT(gt1,gt2,gt3,g1,g2,lam,kap,ZA,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(g1*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,1))*ZA(gt3,1))/2._dp
resL = resL-(g2*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,2))*ZA(gt3,1))/2._dp
resL = resL+(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,3))*ZA(gt3,1))/2._dp
resL = resL-(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,3))*ZA(gt3,1))/2._dp
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-(g1*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,1))*ZA(gt3,2))/2._dp
resL = resL+(g2*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,2))*ZA(gt3,2))/2._dp
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3))*ZA(gt3,2))/sqrt(2._dp))
resL = resL-(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,4))*ZA(gt3,2))/2._dp
resL = resL+(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,4))*ZA(gt3,2))/2._dp
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5))*ZA(gt3,2))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3))*ZA(gt3,3))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4))*ZA(gt3,3))/sqrt(2._dp))
resL = resL+sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))*ZA(gt3,3)
resR = 0._dp 
resR = resR-(g1*ZA(gt3,1)*ZN(gt1,3)*ZN(gt2,1))/2._dp
resR = resR+(g1*ZA(gt3,2)*ZN(gt1,4)*ZN(gt2,1))/2._dp
resR = resR+(g2*ZA(gt3,1)*ZN(gt1,3)*ZN(gt2,2))/2._dp
resR = resR-(g2*ZA(gt3,2)*ZN(gt1,4)*ZN(gt2,2))/2._dp
resR = resR-(g1*ZA(gt3,1)*ZN(gt1,1)*ZN(gt2,3))/2._dp
resR = resR+(g2*ZA(gt3,1)*ZN(gt1,2)*ZN(gt2,3))/2._dp
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(g1*ZA(gt3,2)*ZN(gt1,1)*ZN(gt2,4))/2._dp
resR = resR-(g2*ZA(gt3,2)*ZN(gt1,2)*ZN(gt2,4))/2._dp
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZA(gt3,3)*ZN(gt1,5)*ZN(gt2,5))
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiAhT  
 
 
Subroutine CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZA(gt3,1)*ZDL(gt1,j2)*ZDR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdAhT  
 
 
Subroutine CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZA(gt3,1)*ZEL(gt1,j2)*ZER(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeAhT  
 
 
Subroutine CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZA(gt3,2)*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuAhT  
 
 
Subroutine CouplingChiChacHpmT(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChacHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(g1*Conjg(UM(gt2,2))*Conjg(ZN(gt1,1))*ZP(gt3,1))/sqrt(2._dp)
resL = resL+(g2*Conjg(UM(gt2,2))*Conjg(ZN(gt1,2))*ZP(gt3,1))/sqrt(2._dp)
resL = resL-(g2*Conjg(UM(gt2,1))*Conjg(ZN(gt1,3))*ZP(gt3,1))
resL = resL-(lam*Conjg(UM(gt2,2))*Conjg(ZN(gt1,5))*ZP(gt3,2))
resR = 0._dp 
resR = resR-(Conjg(lam)*UP(gt2,2)*ZN(gt1,5)*ZP(gt3,1))
resR = resR-((g1*UP(gt2,2)*ZN(gt1,1)*ZP(gt3,2))/sqrt(2._dp))
resR = resR-((g2*UP(gt2,2)*ZN(gt1,2)*ZP(gt3,2))/sqrt(2._dp))
resR = resR-(g2*UP(gt2,1)*ZN(gt1,4)*ZP(gt3,2))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChacHpmT  
 
 
Subroutine CouplingcChaChahhT(gt1,gt2,gt3,g2,lam,ZH,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChahh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-((g2*Conjg(UM(gt2,2))*Conjg(UP(gt1,1))*ZH(gt3,1))/sqrt(2._dp))
resL = resL-((g2*Conjg(UM(gt2,1))*Conjg(UP(gt1,2))*ZH(gt3,2))/sqrt(2._dp))
resL = resL-((lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2))*ZH(gt3,3))/sqrt(2._dp))
resR = 0._dp 
resR = resR-((g2*UM(gt1,2)*UP(gt2,1)*ZH(gt3,1))/sqrt(2._dp))
resR = resR-((g2*UM(gt1,1)*UP(gt2,2)*ZH(gt3,2))/sqrt(2._dp))
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2)*ZH(gt3,3))/sqrt(2._dp))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChahhT  
 
 
Subroutine CouplingChiChihhT(gt1,gt2,gt3,g1,g2,lam,kap,ZH,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChihh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(g1*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,1))*ZH(gt3,1))/2._dp
resL = resL-(g2*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,2))*ZH(gt3,1))/2._dp
resL = resL+(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,3))*ZH(gt3,1))/2._dp
resL = resL-(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,3))*ZH(gt3,1))/2._dp
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4))*ZH(gt3,1))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5))*ZH(gt3,1))/sqrt(2._dp)
resL = resL-(g1*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,1))*ZH(gt3,2))/2._dp
resL = resL+(g2*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,2))*ZH(gt3,2))/2._dp
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3))*ZH(gt3,2))/sqrt(2._dp)
resL = resL-(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,4))*ZH(gt3,2))/2._dp
resL = resL+(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,4))*ZH(gt3,2))/2._dp
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5))*ZH(gt3,2))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3))*ZH(gt3,3))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4))*ZH(gt3,3))/sqrt(2._dp)
resL = resL-(sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))*ZH(gt3,3))
resR = 0._dp 
resR = resR+(g1*ZH(gt3,1)*ZN(gt1,3)*ZN(gt2,1))/2._dp
resR = resR-(g1*ZH(gt3,2)*ZN(gt1,4)*ZN(gt2,1))/2._dp
resR = resR-(g2*ZH(gt3,1)*ZN(gt1,3)*ZN(gt2,2))/2._dp
resR = resR+(g2*ZH(gt3,2)*ZN(gt1,4)*ZN(gt2,2))/2._dp
resR = resR+(g1*ZH(gt3,1)*ZN(gt1,1)*ZN(gt2,3))/2._dp
resR = resR-(g2*ZH(gt3,1)*ZN(gt1,2)*ZN(gt2,3))/2._dp
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
resR = resR-(g1*ZH(gt3,2)*ZN(gt1,1)*ZN(gt2,4))/2._dp
resR = resR+(g2*ZH(gt3,2)*ZN(gt1,2)*ZN(gt2,4))/2._dp
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZH(gt3,3)*ZN(gt1,5)*ZN(gt2,5))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChihhT  
 
 
Subroutine CouplingcChaChiHpmT(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChiHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(lam*Conjg(UP(gt1,2))*Conjg(ZN(gt2,5))*ZP(gt3,1))
resL = resL-((g1*Conjg(UP(gt1,2))*Conjg(ZN(gt2,1))*ZP(gt3,2))/sqrt(2._dp))
resL = resL-((g2*Conjg(UP(gt1,2))*Conjg(ZN(gt2,2))*ZP(gt3,2))/sqrt(2._dp))
resL = resL-(g2*Conjg(UP(gt1,1))*Conjg(ZN(gt2,4))*ZP(gt3,2))
resR = 0._dp 
resR = resR+(g1*UM(gt1,2)*ZN(gt2,1)*ZP(gt3,1))/sqrt(2._dp)
resR = resR+(g2*UM(gt1,2)*ZN(gt2,2)*ZP(gt3,1))/sqrt(2._dp)
resR = resR-(g2*UM(gt1,1)*ZN(gt2,3)*ZP(gt3,1))
resR = resR-(Conjg(lam)*UM(gt1,2)*ZN(gt2,5)*ZP(gt3,2))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChiHpmT  
 
 
Subroutine CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j2)*ZDR(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhhT  
 
 
Subroutine CouplingcFuFdcHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZP(gt3,1)*ZUL(gt1,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcHpmT  
 
 
Subroutine CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFehh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j2)*ZER(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehhT  
 
 
Subroutine CouplingcFvFecHpmT(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resR = 0._dp 
Do j1 = 1,3
resR = resR+Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecHpmT  
 
 
Subroutine CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZH(gt3,2)*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhhT  
 
 
Subroutine CouplingcFdFuHpmT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j2)*ZP(gt3,2)*ZUR(gt2,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuHpmT  
 
 
Subroutine CouplingcFeFvHpmT(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j1 = 1,3
resL = resL+Conjg(ZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvHpmT  
 
 
Subroutine CouplingChiChacVWmT(gt1,gt2,g2,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChacVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(g2*Conjg(UM(gt2,1))*ZN(gt1,2))
resL = resL-((g2*Conjg(UM(gt2,2))*ZN(gt1,3))/sqrt(2._dp))
resR = 0._dp 
resR = resR-(g2*Conjg(ZN(gt1,2))*UP(gt2,1))
resR = resR+(g2*Conjg(ZN(gt1,4))*UP(gt2,2))/sqrt(2._dp)
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChacVWmT  
 
 
Subroutine CouplingcChaChaVPT(gt1,gt2,g1,g2,UM,UP,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+g2*Conjg(UM(gt2,1))*Sin(TW)*UM(gt1,1)
resL = resL+(g1*Conjg(UM(gt2,2))*Cos(TW)*UM(gt1,2))/2._dp
resL = resL+(g2*Conjg(UM(gt2,2))*Sin(TW)*UM(gt1,2))/2._dp
resR = 0._dp 
resR = resR+g2*Conjg(UP(gt1,1))*Sin(TW)*UP(gt2,1)
resR = resR+(g1*Conjg(UP(gt1,2))*Cos(TW)*UP(gt2,2))/2._dp
resR = resR+(g2*Conjg(UP(gt1,2))*Sin(TW)*UP(gt2,2))/2._dp
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaVPT  
 
 
Subroutine CouplingcChaChaVZT(gt1,gt2,g1,g2,UM,UP,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+g2*Conjg(UM(gt2,1))*Cos(TW)*UM(gt1,1)
resL = resL+(g2*Conjg(UM(gt2,2))*Cos(TW)*UM(gt1,2))/2._dp
resL = resL-(g1*Conjg(UM(gt2,2))*Sin(TW)*UM(gt1,2))/2._dp
resR = 0._dp 
resR = resR+g2*Conjg(UP(gt1,1))*Cos(TW)*UP(gt2,1)
resR = resR+(g2*Conjg(UP(gt1,2))*Cos(TW)*UP(gt2,2))/2._dp
resR = resR-(g1*Conjg(UP(gt1,2))*Sin(TW)*UP(gt2,2))/2._dp
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaVZT  
 
 
Subroutine CouplingChiChiVZT(gt1,gt2,g1,g2,ZN,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(g2*Conjg(ZN(gt2,3))*Cos(TW)*ZN(gt1,3))/2._dp
resL = resL-(g1*Conjg(ZN(gt2,3))*Sin(TW)*ZN(gt1,3))/2._dp
resL = resL+(g2*Conjg(ZN(gt2,4))*Cos(TW)*ZN(gt1,4))/2._dp
resL = resL+(g1*Conjg(ZN(gt2,4))*Sin(TW)*ZN(gt1,4))/2._dp
resR = 0._dp 
resR = resR+(g2*Conjg(ZN(gt1,3))*Cos(TW)*ZN(gt2,3))/2._dp
resR = resR+(g1*Conjg(ZN(gt1,3))*Sin(TW)*ZN(gt2,3))/2._dp
resR = resR-(g2*Conjg(ZN(gt1,4))*Cos(TW)*ZN(gt2,4))/2._dp
resR = resR-(g1*Conjg(ZN(gt1,4))*Sin(TW)*ZN(gt2,4))/2._dp
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiVZT  
 
 
Subroutine CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChiVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(g2*Conjg(ZN(gt2,2))*UM(gt1,1))
resL = resL-((g2*Conjg(ZN(gt2,3))*UM(gt1,2))/sqrt(2._dp))
resR = 0._dp 
resR = resR-(g2*Conjg(UP(gt1,1))*ZN(gt2,2))
resR = resR+(g2*Conjg(UP(gt1,2))*ZN(gt2,4))/sqrt(2._dp)
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChiVWmT  
 
 
Subroutine CouplingcFdFdVGT(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVGT  
 
 
Subroutine CouplingcFdFdVPT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Cos(TW))/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(g1*Cos(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVPT  
 
 
Subroutine CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g1*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-(g1*Sin(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVZT  
 
 
Subroutine CouplingcFuFdcVWmT(gt1,gt2,g2,ZDL,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j1 = 1,3
resL = resL-((g2*Conjg(ZDL(gt2,j1))*ZUL(gt1,j1))/sqrt(2._dp))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcVWmT  
 
 
Subroutine CouplingcFeFeVPT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL+(g1*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+g1*Cos(TW)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeVPT  
 
 
Subroutine CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-(g1*Sin(TW))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeVZT  
 
 
Subroutine CouplingcFvFecVWmT(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-((g2*Conjg(ZEL(gt2,gt1)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecVWmT  
 
 
Subroutine CouplingcFuFuVGT(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVGT  
 
 
Subroutine CouplingcFuFuVPT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Cos(TW))/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(-2*g1*Cos(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVPT  
 
 
Subroutine CouplingcFdFuVWmT(gt1,gt2,g2,ZDL,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j1 = 1,3
resL = resL-((g2*Conjg(ZUL(gt2,j1))*ZDL(gt1,j1))/sqrt(2._dp))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuVWmT  
 
 
Subroutine CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g1*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(2*g1*Sin(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVZT  
 
 
Subroutine CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt2.le.3).And.(gt2.ge.1)) Then 
resL = resL-((g2*ZEL(gt1,gt2))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvVWmT  
 
 
Subroutine CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFvVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFvVZT  
 
 
Subroutine CouplingVGVGVGVGT(g3,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVGVG' 
 
res1 = 0._dp 
res1 = res1-16*g3**2
res2 = 0._dp 
res3 = 0._dp 
res3 = res3+16*g3**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVGVGT  
 
 
Subroutine CouplingcVWmVPVPVWmT(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVPVWm' 
 
res1 = 0._dp 
res1 = res1+g2**2*Sin(TW)**2
res2 = 0._dp 
res2 = res2+g2**2*Sin(TW)**2
res3 = 0._dp 
res3 = res3-2*g2**2*Sin(TW)**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVPVWmT  
 
 
Subroutine CouplingcVWmVPVWmVZT(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVWmVZ' 
 
res1 = 0._dp 
res1 = res1+g2**2*Cos(TW)*Sin(TW)
res2 = 0._dp 
res2 = res2-(g2**2*Sin(2._dp*(TW)))
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)*Sin(TW)
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVWmVZT  
 
 
Subroutine CouplingcVWmcVWmVWmVWmT(g2,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmcVWmVWmVWm' 
 
res1 = 0._dp 
res1 = res1+2*g2**2
res2 = 0._dp 
res2 = res2-g2**2
res3 = 0._dp 
res3 = res3-g2**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmcVWmVWmVWmT  
 
 
Subroutine CouplingcVWmVWmVZVZT(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVWmVZVZ' 
 
res1 = 0._dp 
res1 = res1-2*g2**2*Cos(TW)**2
res2 = 0._dp 
res2 = res2+g2**2*Cos(TW)**2
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVWmVZVZT  
 
 
Subroutine CouplingcgGgGVGT(g3,res)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgGgGVG' 
 
res = 0._dp 
res = res+g3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgGgGVGT  
 
 
Subroutine CouplingcgWmgAVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgAVWm' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgAVWmT  
 
 
Subroutine CouplingcgWpCgAcVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgAcVWm' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgAcVWmT  
 
 
Subroutine CouplingcgWmgWmVPT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmVP' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmVPT  
 
 
Subroutine CouplingcgWmgWmVZT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmVZT  
 
 
Subroutine CouplingcgAgWmcVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgAgWmcVWm' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgAgWmcVWmT  
 
 
Subroutine CouplingcgZgWmcVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWmcVWm' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWmcVWmT  
 
 
Subroutine CouplingcgWpCgWpCVPT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCVP' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCVPT  
 
 
Subroutine CouplingcgAgWpCVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgAgWpCVWm' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgAgWpCVWmT  
 
 
Subroutine CouplingcgZgWpCVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpCVWm' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpCVWmT  
 
 
Subroutine CouplingcgWpCgWpCVZT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCVZ' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCVZT  
 
 
Subroutine CouplingcgWmgZVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgZVWm' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgZVWmT  
 
 
Subroutine CouplingcgWpCgZcVWmT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgZcVWm' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgZcVWmT  
 
 
Subroutine CouplingcgWmgWmAhT(gt3,g2,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu,ZA(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmAh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*RXiWm*ZA(gt3,1))/4._dp
res = res-(g2**2*vu*RXiWm*ZA(gt3,2))/4._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmAhT  
 
 
Subroutine CouplingcgWpCgWpCAhT(gt3,g2,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu,ZA(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCAh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*RXiWm*ZA(gt3,1))/4._dp
res = res+(g2**2*vu*RXiWm*ZA(gt3,2))/4._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCAhT  
 
 
Subroutine CouplingcgZgAhhT(gt3,g1,g2,vd,vu,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgAhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(2._dp*(TW))*RXiZ*ZH(gt3,1))/4._dp
res = res+(g1**2*vd*RXiZ*Sin(2._dp*(TW))*ZH(gt3,1))/8._dp
res = res-(g2**2*vd*RXiZ*Sin(2._dp*(TW))*ZH(gt3,1))/8._dp
res = res+(g1*g2*vu*Cos(2._dp*(TW))*RXiZ*ZH(gt3,2))/4._dp
res = res+(g1**2*vu*RXiZ*Sin(2._dp*(TW))*ZH(gt3,2))/8._dp
res = res-(g2**2*vu*RXiZ*Sin(2._dp*(TW))*ZH(gt3,2))/8._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgAhhT  
 
 
Subroutine CouplingcgWmgAHpmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgAHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res+(g2**2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g1*g2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res-(g2**2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgAHpmT  
 
 
Subroutine CouplingcgWpCgAcHpmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgAcHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res+(g2**2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g1*g2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res-(g2**2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgAcHpmT  
 
 
Subroutine CouplingcgWmgWmhhT(gt3,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*RXiWm*ZH(gt3,1))/4._dp
res = res-(g2**2*vu*RXiWm*ZH(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmhhT  
 
 
Subroutine CouplingcgZgWmcHpmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWmcHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*Cos(TW)*RXiZ*ZP(gt3,1))/4._dp
res = res-(g1*g2*vd*RXiZ*Sin(TW)*ZP(gt3,1))/4._dp
res = res+(g2**2*vu*Cos(TW)*RXiZ*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiZ*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWmcHpmT  
 
 
Subroutine CouplingcgWpCgWpChhT(gt3,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpChh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*RXiWm*ZH(gt3,1))/4._dp
res = res-(g2**2*vu*RXiWm*ZH(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpChhT  
 
 
Subroutine CouplingcgZgWpCHpmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpCHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*Cos(TW)*RXiZ*ZP(gt3,1))/4._dp
res = res-(g1*g2*vd*RXiZ*Sin(TW)*ZP(gt3,1))/4._dp
res = res+(g2**2*vu*Cos(TW)*RXiZ*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiZ*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpCHpmT  
 
 
Subroutine CouplingcgZgZhhT(gt3,g1,g2,vd,vu,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgZhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*Cos(TW)**2*RXiZ*ZH(gt3,1))/4._dp
res = res-(g1*g2*vd*Cos(TW)*RXiZ*Sin(TW)*ZH(gt3,1))/2._dp
res = res-(g1**2*vd*RXiZ*Sin(TW)**2*ZH(gt3,1))/4._dp
res = res-(g2**2*vu*Cos(TW)**2*RXiZ*ZH(gt3,2))/4._dp
res = res-(g1*g2*vu*Cos(TW)*RXiZ*Sin(TW)*ZH(gt3,2))/2._dp
res = res-(g1**2*vu*RXiZ*Sin(TW)**2*ZH(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgZhhT  
 
 
Subroutine CouplingcgWmgZHpmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgZHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res-(g1*g2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g2**2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgZHpmT  
 
 
Subroutine CouplingcgWpCgZcHpmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgZcHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res-(g1*g2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g2**2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgZcHpmT  
 
 
Subroutine CouplingsForEffPot4(lam,kap,ZA,ZH,ZP,cplAhAhAhAh,cplAhAhhhhh,              & 
& cplAhAhHpmcHpm,cplhhhhhhhh,cplhhhhHpmcHpm,cplHpmHpmcHpmcHpm)

Implicit None 
Real(dp), Intent(in) :: ZA(3,3),ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplhhhhhhhh(3,3,3,3),& 
& cplhhhhHpmcHpm(3,3,2,2),cplHpmHpmcHpmcHpm(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForEffPot4'
 
cplAhAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhAh2L(gt1,gt2,gt3,gt4,lam,kap,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhhhhh2L(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHpmcHpm2L(gt1,gt2,gt3,gt4,lam,kap,ZA,ZP,cplAhAhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call Couplinghhhhhhhh2L(gt1,gt2,gt3,gt4,lam,kap,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHpmcHpm2L(gt1,gt2,gt3,gt4,lam,kap,ZH,ZP,cplhhhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHpmHpmcHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpmHpmcHpmcHpm2L(gt1,gt2,gt3,gt4,lam,ZP,cplHpmHpmcHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForEffPot4

Subroutine CouplingsForEffPot3(lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,ZP,g3,UM,               & 
& UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,     & 
& cplhhhhhh,cplhhHpmcHpm,cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,             & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,    & 
& cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,      & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdFdVGL,           & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),ZH(3,3),ZP(2,2),g3

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,UM(2,2),UP(2,2),ZN(5,5),Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),            & 
& ZEL(3,3),ZER(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),& 
& cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),         & 
& cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),           & 
& cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3), & 
& cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),   & 
& cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),       & 
& cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),       & 
& cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),         & 
& cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),             & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForEffPot3'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhAh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhhh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhhhhh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpm2L(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call Couplinghhhhhh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpm2L(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVG2L(g3,cplVGVGVG)



cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaAh2L(gt1,gt2,gt3,lam,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)          & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiAh2L(gt1,gt2,gt3,lam,kap,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)           & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdAh2L(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)             & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeAh2L(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)             & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuAh2L(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)             & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpm2L(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)     & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChahh2L(gt1,gt2,gt3,lam,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)          & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChihh2L(gt1,gt2,gt3,lam,kap,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)           & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
  Do gt3 = 1, 2
Call CouplingcChaChiHpm2L(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)     & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdhh2L(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)             & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpm2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFehh2L(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)             & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpm2L(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)             & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuhh2L(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)             & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpm2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3)& 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpm2L(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3)               & 
& ,cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdVGL = 0._dp 
cplcFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVG2L(gt1,gt2,g3,cplcFdFdVGL(gt1,gt2),cplcFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVGL = 0._dp 
cplcFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVG2L(gt1,gt2,g3,cplcFuFuVGL(gt1,gt2),cplcFuFuVGR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForEffPot3

Subroutine CouplingAhAhAhAh2L(gt1,gt2,gt3,gt4,lam,kap,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-6*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAh2L  
 
 
Subroutine CouplingAhAhhhhh2L(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-2*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhh2L  
 
 
Subroutine CouplingAhAhHpmcHpm2L(gt1,gt2,gt3,gt4,lam,kap,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,2)
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHpmcHpm2L  
 
 
Subroutine Couplinghhhhhhhh2L(gt1,gt2,gt3,gt4,lam,kap,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-6*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhhhh2L  
 
 
Subroutine CouplinghhhhHpmcHpm2L(gt1,gt2,gt3,gt4,lam,kap,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpmcHpm2L  
 
 
Subroutine CouplingHpmHpmcHpmcHpm2L(gt1,gt2,gt3,gt4,lam,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmHpmcHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmHpmcHpmcHpm2L  
 
 
Subroutine CouplingAhAhAh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp)
res = res-((Tk*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp))
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAh2L  
 
 
Subroutine CouplingAhAhhh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vu*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res-2*vS*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
res = res+(Tk*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhh2L  
 
 
Subroutine CouplingAhhhhh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-((Conjg(Tk)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
res = res+(Tk*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhh2L  
 
 
Subroutine CouplingAhHpmcHpm2L(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+vS*kap*Conjg(lam)*ZA(gt1,3)*ZP(gt2,2)*ZP(gt3,1)
res = res-((Conjg(Tlam)*ZA(gt1,3)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
res = res+(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZP(gt2,1)*ZP(gt3,2))
res = res+(Tlam*ZA(gt1,3)*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp)
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcHpm2L  
 
 
Subroutine Couplinghhhhhh2L(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vu*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1))
res = res-(vu*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(vd*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))
res = res-(vu*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(vd*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vd*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))
res = res-6*vS*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)
res = res-((Conjg(Tk)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
res = res-((Tk*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhh2L  
 
 
Subroutine CouplinghhHpmcHpm2L(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,1))
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(vS*kap*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,1))
res = res-((Conjg(Tlam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,2))
res = res-((Tlam*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcHpm2L  
 
 
Subroutine CouplingVGVGVG2L(g3,res)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVG' 
 
res = 0._dp 
res = res+g3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVG2L  
 
 
Subroutine CouplingcChaChaAh2L(gt1,gt2,gt3,lam,ZA,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2))*ZA(gt3,3))/sqrt(2._dp)
resR = 0._dp 
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2)*ZA(gt3,3))/sqrt(2._dp))
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaAh2L  
 
 
Subroutine CouplingChiChiAh2L(gt1,gt2,gt3,lam,kap,ZA,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3))*ZA(gt3,2))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5))*ZA(gt3,2))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3))*ZA(gt3,3))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4))*ZA(gt3,3))/sqrt(2._dp))
resL = resL+sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))*ZA(gt3,3)
resR = 0._dp 
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZA(gt3,3)*ZN(gt1,5)*ZN(gt2,5))
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiAh2L  
 
 
Subroutine CouplingcFdFdAh2L(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZA(gt3,1)*ZDL(gt1,j2)*ZDR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdAh2L  
 
 
Subroutine CouplingcFeFeAh2L(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZA(gt3,1)*ZEL(gt1,j2)*ZER(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeAh2L  
 
 
Subroutine CouplingcFuFuAh2L(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZA(gt3,2)*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuAh2L  
 
 
Subroutine CouplingChiChacHpm2L(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChacHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(lam*Conjg(UM(gt2,2))*Conjg(ZN(gt1,5))*ZP(gt3,2))
resR = 0._dp 
resR = resR-(Conjg(lam)*UP(gt2,2)*ZN(gt1,5)*ZP(gt3,1))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChacHpm2L  
 
 
Subroutine CouplingcChaChahh2L(gt1,gt2,gt3,lam,ZH,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChahh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-((lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2))*ZH(gt3,3))/sqrt(2._dp))
resR = 0._dp 
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2)*ZH(gt3,3))/sqrt(2._dp))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChahh2L  
 
 
Subroutine CouplingChiChihh2L(gt1,gt2,gt3,lam,kap,ZH,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChihh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4))*ZH(gt3,1))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5))*ZH(gt3,1))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3))*ZH(gt3,2))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5))*ZH(gt3,2))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3))*ZH(gt3,3))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4))*ZH(gt3,3))/sqrt(2._dp)
resL = resL-(sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))*ZH(gt3,3))
resR = 0._dp 
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZH(gt3,3)*ZN(gt1,5)*ZN(gt2,5))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChihh2L  
 
 
Subroutine CouplingcChaChiHpm2L(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChiHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(lam*Conjg(UP(gt1,2))*Conjg(ZN(gt2,5))*ZP(gt3,1))
resR = 0._dp 
resR = resR-(Conjg(lam)*UM(gt1,2)*ZN(gt2,5)*ZP(gt3,2))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChiHpm2L  
 
 
Subroutine CouplingcFdFdhh2L(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j2)*ZDR(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhh2L  
 
 
Subroutine CouplingcFuFdcHpm2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZP(gt3,1)*ZUL(gt1,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcHpm2L  
 
 
Subroutine CouplingcFeFehh2L(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFehh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j2)*ZER(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehh2L  
 
 
Subroutine CouplingcFvFecHpm2L(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resR = 0._dp 
Do j1 = 1,3
resR = resR+Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecHpm2L  
 
 
Subroutine CouplingcFuFuhh2L(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZH(gt3,2)*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhh2L  
 
 
Subroutine CouplingcFdFuHpm2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j2)*ZP(gt3,2)*ZUR(gt2,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuHpm2L  
 
 
Subroutine CouplingcFeFvHpm2L(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j1 = 1,3
resL = resL+Conjg(ZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvHpm2L  
 
 
Subroutine CouplingcFdFdVG2L(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVG2L  
 
 
Subroutine CouplingcFuFuVG2L(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVG2L  
 
 
Subroutine CouplingsFor2LPole3(lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,ZP,g3,UM,               & 
& UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,     & 
& cplhhhhhh,cplhhHpmcHpm,cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,             & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplcChaChahhL,cplcChaChahhR,cplChiChihhL,    & 
& cplChiChihhR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHpmL,      & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdFdVGL,           & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),ZH(3,3),ZP(2,2),g3

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,UM(2,2),UP(2,2),ZN(5,5),Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),            & 
& ZEL(3,3),ZER(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),& 
& cplChiChiAhL(5,5,3),cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),         & 
& cplcFeFeAhL(3,3,3),cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),           & 
& cplChiChacHpmL(5,2,2),cplChiChacHpmR(5,2,2),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3), & 
& cplChiChihhL(5,5,3),cplChiChihhR(5,5,3),cplcChaChiHpmL(2,5,2),cplcChaChiHpmR(2,5,2),   & 
& cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),       & 
& cplcFeFehhL(3,3,3),cplcFeFehhR(3,3,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),       & 
& cplcFuFuhhL(3,3,3),cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),         & 
& cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),             & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsFor2LPole3'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhAh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhhh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhhhhh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcHpm2LP(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZA,ZP,cplAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call Couplinghhhhhh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcHpm2LP(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZH,ZP,cplhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVG2LP(g3,cplVGVGVG)



cplcChaChaAhL = 0._dp 
cplcChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaAh2LP(gt1,gt2,gt3,lam,ZA,UM,UP,cplcChaChaAhL(gt1,gt2,gt3)         & 
& ,cplcChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiAhL = 0._dp 
cplChiChiAhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiAh2LP(gt1,gt2,gt3,lam,kap,ZA,ZN,cplChiChiAhL(gt1,gt2,gt3)          & 
& ,cplChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdAh2LP(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)            & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeAh2LP(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)            & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuAh2LP(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)            & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChacHpmL = 0._dp 
cplChiChacHpmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacHpm2LP(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,cplChiChacHpmL(gt1,gt2,gt3)    & 
& ,cplChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChahhL = 0._dp 
cplcChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChahh2LP(gt1,gt2,gt3,lam,ZH,UM,UP,cplcChaChahhL(gt1,gt2,gt3)         & 
& ,cplcChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChihhL = 0._dp 
cplChiChihhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChihh2LP(gt1,gt2,gt3,lam,kap,ZH,ZN,cplChiChihhL(gt1,gt2,gt3)          & 
& ,cplChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiHpmL = 0._dp 
cplcChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
  Do gt3 = 1, 2
Call CouplingcChaChiHpm2LP(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,cplcChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdhh2LP(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)            & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHpmL = 0._dp 
cplcFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHpm2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFehh2LP(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)            & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHpmL = 0._dp 
cplcFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHpm2LP(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHpmL(gt1,gt2,gt3)            & 
& ,cplcFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuhh2LP(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)            & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHpmL = 0._dp 
cplcFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHpm2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHpmL(gt1,gt2,gt3)& 
& ,cplcFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHpmL = 0._dp 
cplcFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHpm2LP(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHpmL(gt1,gt2,gt3)              & 
& ,cplcFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdVGL = 0._dp 
cplcFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVG2LP(gt1,gt2,g3,cplcFdFdVGL(gt1,gt2),cplcFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVGL = 0._dp 
cplcFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVG2LP(gt1,gt2,g3,cplcFuFuVGL(gt1,gt2),cplcFuFuVGR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsFor2LPole3

Subroutine CouplingAhAhAh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3))/2._dp
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3))/2._dp
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp)
res = res-((Tk*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp))
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAh2LP  
 
 
Subroutine CouplingAhAhhh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1))
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vu*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3))/2._dp
res = res-2*vS*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
res = res+(Tk*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhh2LP  
 
 
Subroutine CouplingAhhhhh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(Tlam*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-((Conjg(Tk)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
res = res+(Tk*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhh2LP  
 
 
Subroutine CouplingAhHpmcHpm2LP(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+vS*kap*Conjg(lam)*ZA(gt1,3)*ZP(gt2,2)*ZP(gt3,1)
res = res-((Conjg(Tlam)*ZA(gt1,3)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
res = res+(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZP(gt2,1)*ZP(gt3,2))
res = res+(Tlam*ZA(gt1,3)*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp)
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcHpm2LP  
 
 
Subroutine Couplinghhhhhh2LP(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vu*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1))
res = res-(vu*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(vd*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1))
res = res-(vu*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(vd*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vd*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3))
res = res+(vS*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vS*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(Conjg(Tlam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res+(Tlam*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3))
res = res+(vu*lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vu*kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vd*lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3))
res = res+(vd*lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res+(vd*kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))/2._dp
res = res-(vu*lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3))
res = res-6*vS*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)
res = res-((Conjg(Tk)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
res = res-((Tk*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhh2LP  
 
 
Subroutine CouplinghhHpmcHpm2LP(gt1,gt2,gt3,lam,Tlam,kap,vd,vu,vS,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,1))
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(vS*kap*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,1))
res = res-((Conjg(Tlam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vS*lam*Conjg(kap)*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,2))
res = res-((Tlam*ZH(gt1,3)*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp))
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcHpm2LP  
 
 
Subroutine CouplingVGVGVG2LP(g3,res)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVG' 
 
res = 0._dp 
res = res+g3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVG2LP  
 
 
Subroutine CouplingcChaChaAh2LP(gt1,gt2,gt3,lam,ZA,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2))*ZA(gt3,3))/sqrt(2._dp)
resR = 0._dp 
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2)*ZA(gt3,3))/sqrt(2._dp))
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaAh2LP  
 
 
Subroutine CouplingChiChiAh2LP(gt1,gt2,gt3,lam,kap,ZA,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5))*ZA(gt3,1))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3))*ZA(gt3,2))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5))*ZA(gt3,2))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3))*ZA(gt3,3))/sqrt(2._dp))
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4))*ZA(gt3,3))/sqrt(2._dp))
resL = resL+sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))*ZA(gt3,3)
resR = 0._dp 
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZA(gt3,3)*ZN(gt1,5)*ZN(gt2,5))
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiAh2LP  
 
 
Subroutine CouplingcFdFdAh2LP(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZA(gt3,1)*ZDL(gt1,j2)*ZDR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdAh2LP  
 
 
Subroutine CouplingcFeFeAh2LP(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZA(gt3,1)*ZEL(gt1,j2)*ZER(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeAh2LP  
 
 
Subroutine CouplingcFuFuAh2LP(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZA(gt3,2)*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuAh2LP  
 
 
Subroutine CouplingChiChacHpm2LP(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChacHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(lam*Conjg(UM(gt2,2))*Conjg(ZN(gt1,5))*ZP(gt3,2))
resR = 0._dp 
resR = resR-(Conjg(lam)*UP(gt2,2)*ZN(gt1,5)*ZP(gt3,1))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChacHpm2LP  
 
 
Subroutine CouplingcChaChahh2LP(gt1,gt2,gt3,lam,ZH,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChahh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-((lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2))*ZH(gt3,3))/sqrt(2._dp))
resR = 0._dp 
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2)*ZH(gt3,3))/sqrt(2._dp))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChahh2LP  
 
 
Subroutine CouplingChiChihh2LP(gt1,gt2,gt3,lam,kap,ZH,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChihh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4))*ZH(gt3,1))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5))*ZH(gt3,1))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3))*ZH(gt3,2))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5))*ZH(gt3,2))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3))*ZH(gt3,3))/sqrt(2._dp)
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4))*ZH(gt3,3))/sqrt(2._dp)
resL = resL-(sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))*ZH(gt3,3))
resR = 0._dp 
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZH(gt3,3)*ZN(gt1,5)*ZN(gt2,5))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChihh2LP  
 
 
Subroutine CouplingcChaChiHpm2LP(gt1,gt2,gt3,lam,ZP,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChiHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(lam*Conjg(UP(gt1,2))*Conjg(ZN(gt2,5))*ZP(gt3,1))
resR = 0._dp 
resR = resR-(Conjg(lam)*UM(gt1,2)*ZN(gt2,5)*ZP(gt3,2))
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChiHpm2LP  
 
 
Subroutine CouplingcFdFdhh2LP(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j2)*ZDR(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhh2LP  
 
 
Subroutine CouplingcFuFdcHpm2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZP(gt3,1)*ZUL(gt1,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcHpm2LP  
 
 
Subroutine CouplingcFeFehh2LP(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFehh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j2)*ZER(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehh2LP  
 
 
Subroutine CouplingcFvFecHpm2LP(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resR = 0._dp 
Do j1 = 1,3
resR = resR+Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecHpm2LP  
 
 
Subroutine CouplingcFuFuhh2LP(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZH(gt3,2)*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhh2LP  
 
 
Subroutine CouplingcFdFuHpm2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j2)*ZP(gt3,2)*ZUR(gt2,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuHpm2LP  
 
 
Subroutine CouplingcFeFvHpm2LP(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j1 = 1,3
resL = resL+Conjg(ZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvHpm2LP  
 
 
Subroutine CouplingcFdFdVG2LP(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVG2LP  
 
 
Subroutine CouplingcFuFuVG2LP(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVG2LP  
 
 
Subroutine CouplingsFor2LPole4(lam,kap,ZA,ZH,ZP,cplAhAhAhAh,cplAhAhAhhh,              & 
& cplAhAhhhhh,cplAhAhHpmcHpm,cplAhhhhhhh,cplAhhhHpmcHpm,cplhhhhhhhh,cplhhhhHpmcHpm,      & 
& cplHpmHpmcHpmcHpm)

Implicit None 
Real(dp), Intent(in) :: ZA(3,3),ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: cplAhAhAhAh(3,3,3,3),cplAhAhAhhh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),& 
& cplAhhhhhhh(3,3,3,3),cplAhhhHpmcHpm(3,3,2,2),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplHpmHpmcHpmcHpm(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsFor2LPole4'
 
cplAhAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhAh2LP(gt1,gt2,gt3,gt4,lam,kap,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhAhAhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhhhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,kap,ZA,ZP,cplAhAhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhhhhhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,ZP,cplAhhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call Couplinghhhhhhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZP,cplhhhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHpmHpmcHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpmHpmcHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,ZP,cplHpmHpmcHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsFor2LPole4

Subroutine CouplingAhAhAhAh2LP(gt1,gt2,gt3,gt4,lam,kap,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,1))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))
res = res-6*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,3)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAh2LP  
 
 
Subroutine CouplingAhAhAhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhh2LP  
 
 
Subroutine CouplingAhAhhhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
res = res-2*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,3)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhh2LP  
 
 
Subroutine CouplingAhAhHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,kap,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,2)
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHpmcHpm2LP  
 
 
Subroutine CouplingAhhhhhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhh2LP  
 
 
Subroutine CouplingAhhhHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
res = res+(lam*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(lam*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHpmcHpm2LP  
 
 
Subroutine Couplinghhhhhhhh2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,1))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,2))
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))
res = res-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
res = res+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res = res-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
res = res-6*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,3)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhhhh2LP  
 
 
Subroutine CouplinghhhhHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,kap,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1))
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpmcHpm2LP  
 
 
Subroutine CouplingHpmHpmcHpmcHpm2LP(gt1,gt2,gt3,gt4,lam,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmHpmcHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmHpmcHpmcHpm2LP  
 
 
Subroutine CouplingsForLoopMasses(g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,               & 
& TW,UM,UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,ZP,g3,cplAhAhUhh,cplAhUhhhh,              & 
& cplAhUhhVZ,cplcChaChaUhhL,cplcChaChaUhhR,cplChiChiUhhL,cplChiChiUhhR,cplcFdFdUhhL,     & 
& cplcFdFdUhhR,cplcFeFeUhhL,cplcFeFeUhhR,cplcFuFuUhhL,cplcFuFuUhhR,cplcgWmgWmUhh,        & 
& cplcgWpCgWpCUhh,cplcgZgZUhh,cplUhhhhhh,cplUhhHpmcHpm,cplUhhHpmcVWm,cplUhhcVWmVWm,      & 
& cplUhhVZVZ,cplAhAhUhhUhh,cplUhhUhhhhhh,cplUhhUhhHpmcHpm,cplUhhUhhcVWmVWm,              & 
& cplUhhUhhVZVZ,cplUAhAhAh,cplUAhAhhh,cplcChaChaUAhL,cplcChaChaUAhR,cplChiChiUAhL,       & 
& cplChiChiUAhR,cplcFdFdUAhL,cplcFdFdUAhR,cplcFeFeUAhL,cplcFeFeUAhR,cplcFuFuUAhL,        & 
& cplcFuFuUAhR,cplcgWmgWmUAh,cplcgWpCgWpCUAh,cplUAhhhhh,cplUAhhhVZ,cplUAhHpmcHpm,        & 
& cplUAhHpmcVWm,cplUAhUAhAhAh,cplUAhUAhhhhh,cplUAhUAhHpmcHpm,cplUAhUAhcVWmVWm,           & 
& cplUAhUAhVZVZ,cplAhHpmcUHpm,cplAhcUHpmVWm,cplChiChacUHpmL,cplChiChacUHpmR,             & 
& cplcFuFdcUHpmL,cplcFuFdcUHpmR,cplcFvFecUHpmL,cplcFvFecUHpmR,cplcgZgWmcUHpm,            & 
& cplcgWmgZUHpm,cplcgWpCgZcUHpm,cplcgZgWpCUHpm,cplhhHpmcUHpm,cplhhcUHpmVWm,              & 
& cplHpmcUHpmVP,cplHpmcUHpmVZ,cplcUHpmVPVWm,cplcUHpmVWmVZ,cplAhAhUHpmcUHpm,              & 
& cplhhhhUHpmcUHpm,cplUHpmHpmcUHpmcHpm,cplUHpmcUHpmVPVP,cplUHpmcUHpmcVWmVWm,             & 
& cplUHpmcUHpmVZVZ,cplUChiChiAhL,cplUChiChiAhR,cplUChiChacHpmL,cplUChiChacHpmR,          & 
& cplUChiChacVWmL,cplUChiChacVWmR,cplUChiChihhL,cplUChiChihhR,cplUChiChiVZL,             & 
& cplUChiChiVZR,cplcChaUChiHpmL,cplcChaUChiHpmR,cplcChaUChiVWmL,cplcChaUChiVWmR,         & 
& cplcUChaChaAhL,cplcUChaChaAhR,cplcUChaChahhL,cplcUChaChahhR,cplcUChaChaVPL,            & 
& cplcUChaChaVPR,cplcUChaChaVZL,cplcUChaChaVZR,cplcUChaChiHpmL,cplcUChaChiHpmR,          & 
& cplcUChaChiVWmL,cplcUChaChiVWmR,cplcUFeFeAhL,cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,   & 
& cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvHpmL,cplcUFeFvHpmR,       & 
& cplcUFeFvVWmL,cplcUFeFvVWmR,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,       & 
& cplcUFdFdVGL,cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,         & 
& cplcUFdFuHpmL,cplcUFdFuHpmR,cplcUFdFuVWmL,cplcUFdFuVWmR,cplcUFuFuAhL,cplcUFuFuAhR,     & 
& cplcUFuFdcHpmL,cplcUFuFdcHpmR,cplcUFuFdcVWmL,cplcUFuFdcVWmR,cplcUFuFuhhL,              & 
& cplcUFuFuhhR,cplcUFuFuVGL,cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,         & 
& cplcUFuFuVZR,cplcUFvFecHpmL,cplcUFvFecHpmR,cplcUFvFecVWmL,cplcUFvFecVWmR,              & 
& cplcUFvFvVZL,cplcUFvFvVZR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcChaChaVPL,             & 
& cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP,cplHpmcVWmVP,cplcVWmVPVWm,        & 
& cplHpmcHpmVPVP,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ,              & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcFdFdVZL,cplcFdFdVZR,         & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplcVWmVWmVZ,          & 
& cplAhAhVZVZ,cplhhhhVZVZ,cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,& 
& cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,  & 
& cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,               & 
& cplhhHpmcVWm,cplhhcVWmVWm,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,             & 
& cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcHpmVWmVZ,cplcHpmVPVWm,    & 
& cplHpmcHpmVPVZ,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)

Implicit None 
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZA(3,3),ZH(3,3),TW,ZP(2,2),g3

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,UM(2,2),UP(2,2),ZN(5,5),Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),            & 
& ZEL(3,3),ZER(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhUhh(3,3,3),cplAhUhhhh(3,3,3),cplAhUhhVZ(3,3),cplcChaChaUhhL(2,2,3),            & 
& cplcChaChaUhhR(2,2,3),cplChiChiUhhL(5,5,3),cplChiChiUhhR(5,5,3),cplcFdFdUhhL(3,3,3),   & 
& cplcFdFdUhhR(3,3,3),cplcFeFeUhhL(3,3,3),cplcFeFeUhhR(3,3,3),cplcFuFuUhhL(3,3,3),       & 
& cplcFuFuUhhR(3,3,3),cplcgWmgWmUhh(3),cplcgWpCgWpCUhh(3),cplcgZgZUhh(3),cplUhhhhhh(3,3,3),& 
& cplUhhHpmcHpm(3,2,2),cplUhhHpmcVWm(3,2),cplUhhcVWmVWm(3),cplUhhVZVZ(3),cplAhAhUhhUhh(3,3,3,3),& 
& cplUhhUhhhhhh(3,3,3,3),cplUhhUhhHpmcHpm(3,3,2,2),cplUhhUhhcVWmVWm(3,3),cplUhhUhhVZVZ(3,3),& 
& cplUAhAhAh(3,3,3),cplUAhAhhh(3,3,3),cplcChaChaUAhL(2,2,3),cplcChaChaUAhR(2,2,3),       & 
& cplChiChiUAhL(5,5,3),cplChiChiUAhR(5,5,3),cplcFdFdUAhL(3,3,3),cplcFdFdUAhR(3,3,3),     & 
& cplcFeFeUAhL(3,3,3),cplcFeFeUAhR(3,3,3),cplcFuFuUAhL(3,3,3),cplcFuFuUAhR(3,3,3),       & 
& cplcgWmgWmUAh(3),cplcgWpCgWpCUAh(3),cplUAhhhhh(3,3,3),cplUAhhhVZ(3,3),cplUAhHpmcHpm(3,2,2),& 
& cplUAhHpmcVWm(3,2),cplUAhUAhAhAh(3,3,3,3),cplUAhUAhhhhh(3,3,3,3),cplUAhUAhHpmcHpm(3,3,2,2),& 
& cplUAhUAhcVWmVWm(3,3),cplUAhUAhVZVZ(3,3),cplAhHpmcUHpm(3,2,2),cplAhcUHpmVWm(3,2),      & 
& cplChiChacUHpmL(5,2,2),cplChiChacUHpmR(5,2,2),cplcFuFdcUHpmL(3,3,2),cplcFuFdcUHpmR(3,3,2),& 
& cplcFvFecUHpmL(3,3,2),cplcFvFecUHpmR(3,3,2),cplcgZgWmcUHpm(2),cplcgWmgZUHpm(2),        & 
& cplcgWpCgZcUHpm(2),cplcgZgWpCUHpm(2),cplhhHpmcUHpm(3,2,2),cplhhcUHpmVWm(3,2),          & 
& cplHpmcUHpmVP(2,2),cplHpmcUHpmVZ(2,2),cplcUHpmVPVWm(2),cplcUHpmVWmVZ(2),               & 
& cplAhAhUHpmcUHpm(3,3,2,2),cplhhhhUHpmcUHpm(3,3,2,2),cplUHpmHpmcUHpmcHpm(2,2,2,2),      & 
& cplUHpmcUHpmVPVP(2,2),cplUHpmcUHpmcVWmVWm(2,2),cplUHpmcUHpmVZVZ(2,2),cplUChiChiAhL(5,5,3),& 
& cplUChiChiAhR(5,5,3),cplUChiChacHpmL(5,2,2),cplUChiChacHpmR(5,2,2),cplUChiChacVWmL(5,2),& 
& cplUChiChacVWmR(5,2),cplUChiChihhL(5,5,3),cplUChiChihhR(5,5,3),cplUChiChiVZL(5,5),     & 
& cplUChiChiVZR(5,5),cplcChaUChiHpmL(2,5,2),cplcChaUChiHpmR(2,5,2),cplcChaUChiVWmL(2,5), & 
& cplcChaUChiVWmR(2,5),cplcUChaChaAhL(2,2,3),cplcUChaChaAhR(2,2,3),cplcUChaChahhL(2,2,3),& 
& cplcUChaChahhR(2,2,3),cplcUChaChaVPL(2,2),cplcUChaChaVPR(2,2),cplcUChaChaVZL(2,2),     & 
& cplcUChaChaVZR(2,2),cplcUChaChiHpmL(2,5,2),cplcUChaChiHpmR(2,5,2),cplcUChaChiVWmL(2,5),& 
& cplcUChaChiVWmR(2,5),cplcUFeFeAhL(3,3,3),cplcUFeFeAhR(3,3,3),cplcUFeFehhL(3,3,3),      & 
& cplcUFeFehhR(3,3,3),cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),             & 
& cplcUFeFeVZR(3,3),cplcUFeFvHpmL(3,3,2),cplcUFeFvHpmR(3,3,2),cplcUFeFvVWmL(3,3),        & 
& cplcUFeFvVWmR(3,3),cplcUFdFdAhL(3,3,3),cplcUFdFdAhR(3,3,3),cplcUFdFdhhL(3,3,3),        & 
& cplcUFdFdhhR(3,3,3),cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),             & 
& cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFuHpmL(3,3,2),            & 
& cplcUFdFuHpmR(3,3,2),cplcUFdFuVWmL(3,3),cplcUFdFuVWmR(3,3),cplcUFuFuAhL(3,3,3),        & 
& cplcUFuFuAhR(3,3,3),cplcUFuFdcHpmL(3,3,2),cplcUFuFdcHpmR(3,3,2),cplcUFuFdcVWmL(3,3),   & 
& cplcUFuFdcVWmR(3,3),cplcUFuFuhhL(3,3,3),cplcUFuFuhhR(3,3,3),cplcUFuFuVGL(3,3),         & 
& cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),               & 
& cplcUFuFuVZR(3,3),cplcUFvFecHpmL(3,3,2),cplcUFvFecHpmR(3,3,2),cplcUFvFecVWmL(3,3),     & 
& cplcUFvFecVWmR(3,3),cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3),cplcFdFdVGL(3,3),              & 
& cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcgGgGVG,cplVGVGVG

Complex(dp), Intent(out) :: cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),          & 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),  & 
& cplcFuFuVPR(3,3),cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP(2,2),cplHpmcVWmVP(2),        & 
& cplcVWmVPVWm,cplHpmcHpmVPVP(2,2),cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,      & 
& cplAhhhVZ(3,3),cplcChaChaVZL(2,2),cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,        & 
& cplhhVZVZ(3),cplHpmcHpmVZ(2,2),cplHpmcVWmVZ(2),cplcVWmVWmVZ,cplAhAhVZVZ(3,3),          & 
& cplhhhhVZVZ(3,3),cplHpmcHpmVZVZ(2,2),cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,  & 
& cplAhHpmcVWm(3,2),cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),cplcFuFdcVWmL(3,3),          & 
& cplcFuFdcVWmR(3,3),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcgWpCgAcVWm,               & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm(3,2),cplhhcVWmVWm(3),          & 
& cplAhAhcVWmVWm(3,3),cplhhhhcVWmVWm(3,3),cplHpmcHpmcVWmVWm(2,2),cplcVWmcVWmVWmVWm1,     & 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcHpmVWmVZ(2),cplcHpmVPVWm(2),cplHpmcHpmVPVZ(2,2),& 
& cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForLoopMasses'
 
cplAhAhUhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhUhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplAhAhUhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhUhhhhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhUhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhUhhVZL(gt1,gt2,g1,g2,ZA,TW,cplAhUhhVZ(gt1,gt2))

 End Do 
End Do 


cplcChaChaUhhL = 0._dp 
cplcChaChaUhhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaUhhL(gt1,gt2,gt3,g2,lam,UM,UP,cplcChaChaUhhL(gt1,gt2,gt3)         & 
& ,cplcChaChaUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiUhhL = 0._dp 
cplChiChiUhhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiUhhL(gt1,gt2,gt3,g1,g2,lam,kap,ZN,cplChiChiUhhL(gt1,gt2,gt3)       & 
& ,cplChiChiUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdUhhL = 0._dp 
cplcFdFdUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdUhhL(gt1,gt2,gt3,Yd,ZDL,ZDR,cplcFdFdUhhL(gt1,gt2,gt3)               & 
& ,cplcFdFdUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeUhhL = 0._dp 
cplcFeFeUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeUhhL(gt1,gt2,gt3,Ye,ZEL,ZER,cplcFeFeUhhL(gt1,gt2,gt3)               & 
& ,cplcFeFeUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuUhhL = 0._dp 
cplcFuFuUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuUhhL(gt1,gt2,gt3,Yu,ZUL,ZUR,cplcFuFuUhhL(gt1,gt2,gt3)               & 
& ,cplcFuFuUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgWmgWmUhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWmgWmUhhL(gt3,g2,vd,vu,cplcgWmgWmUhh(gt3))

End Do 


cplcgWpCgWpCUhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWpCgWpCUhhL(gt3,g2,vd,vu,cplcgWpCgWpCUhh(gt3))

End Do 


cplcgZgZUhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgZgZUhhL(gt3,g1,g2,vd,vu,TW,cplcgZgZUhh(gt3))

End Do 


cplUhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingUhhhhhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplUhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUhhHpmcHpmL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZP,cplUhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingUhhHpmcVWmL(gt1,gt2,g2,ZP,cplUhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplUhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
Call CouplingUhhcVWmVWmL(gt1,g2,vd,vu,cplUhhcVWmVWm(gt1))

End Do 


cplUhhVZVZ = 0._dp 
Do gt1 = 1, 3
Call CouplingUhhVZVZL(gt1,g1,g2,vd,vu,TW,cplUhhVZVZ(gt1))

End Do 


cplAhAhUhhUhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhUhhUhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,cplAhAhUhhUhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingUhhUhhhhhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,cplUhhUhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUhhUhhHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZP,cplUhhUhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUhhUhhcVWmVWmL(gt1,gt2,g2,cplUhhUhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUhhUhhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUhhUhhVZVZL(gt1,gt2,g1,g2,TW,cplUhhUhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplUAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingUAhAhAhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplUAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUAhAhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingUAhAhhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,               & 
& cplUAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChaUAhL = 0._dp 
cplcChaChaUAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaUAhL(gt1,gt2,gt3,g2,lam,UM,UP,cplcChaChaUAhL(gt1,gt2,gt3)         & 
& ,cplcChaChaUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiUAhL = 0._dp 
cplChiChiUAhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiUAhL(gt1,gt2,gt3,g1,g2,lam,kap,ZN,cplChiChiUAhL(gt1,gt2,gt3)       & 
& ,cplChiChiUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdUAhL = 0._dp 
cplcFdFdUAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdUAhL(gt1,gt2,gt3,Yd,ZDL,ZDR,cplcFdFdUAhL(gt1,gt2,gt3)               & 
& ,cplcFdFdUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeUAhL = 0._dp 
cplcFeFeUAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeUAhL(gt1,gt2,gt3,Ye,ZEL,ZER,cplcFeFeUAhL(gt1,gt2,gt3)               & 
& ,cplcFeFeUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuUAhL = 0._dp 
cplcFuFuUAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuUAhL(gt1,gt2,gt3,Yu,ZUL,ZUR,cplcFuFuUAhL(gt1,gt2,gt3)               & 
& ,cplcFuFuUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgWmgWmUAh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWmgWmUAhL(gt3,g2,vd,vu,cplcgWmgWmUAh(gt3))

End Do 


cplcgWpCgWpCUAh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWpCgWpCUAhL(gt3,g2,vd,vu,cplcgWpCgWpCUAh(gt3))

End Do 


cplUAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingUAhhhhhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplUAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUAhhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUAhhhVZL(gt1,gt2,g1,g2,ZH,TW,cplUAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplUAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUAhHpmcHpmL(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZP,cplUAhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUAhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingUAhHpmcVWmL(gt1,gt2,g2,ZP,cplUAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplUAhUAhAhAh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingUAhUAhAhAhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,cplUAhUAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUAhUAhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingUAhUAhhhhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,cplUAhUAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUAhUAhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUAhUAhHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZP,cplUAhUAhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUAhUAhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUAhUAhcVWmVWmL(gt1,gt2,g2,cplUAhUAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUAhUAhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUAhUAhVZVZL(gt1,gt2,g1,g2,TW,cplUAhUAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplAhHpmcUHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHpmcUHpmL(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZA,ZP,cplAhHpmcUHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhcUHpmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcUHpmVWmL(gt1,gt2,g2,ZA,cplAhcUHpmVWm(gt1,gt2))

 End Do 
End Do 


cplChiChacUHpmL = 0._dp 
cplChiChacUHpmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingChiChacUHpmL(gt1,gt2,gt3,g1,g2,lam,ZN,UM,UP,cplChiChacUHpmL(gt1,gt2,gt3) & 
& ,cplChiChacUHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcUHpmL = 0._dp 
cplcFuFdcUHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcUHpmL(gt1,gt2,gt3,Yd,Yu,ZDL,ZDR,ZUL,ZUR,cplcFuFdcUHpmL(gt1,gt2,gt3)& 
& ,cplcFuFdcUHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecUHpmL = 0._dp 
cplcFvFecUHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecUHpmL(gt1,gt2,gt3,Ye,ZER,cplcFvFecUHpmL(gt1,gt2,gt3)               & 
& ,cplcFvFecUHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgZgWmcUHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWmcUHpmL(gt3,g1,g2,vd,vu,TW,cplcgZgWmcUHpm(gt3))

End Do 


cplcgWmgZUHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgZUHpmL(gt3,g1,g2,vd,vu,TW,cplcgWmgZUHpm(gt3))

End Do 


cplcgWpCgZcUHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgZcUHpmL(gt3,g1,g2,vd,vu,TW,cplcgWpCgZcUHpm(gt3))

End Do 


cplcgZgWpCUHpm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWpCUHpmL(gt3,g1,g2,vd,vu,TW,cplcgZgWpCUHpm(gt3))

End Do 


cplhhHpmcUHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHpmcUHpmL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZH,ZP,               & 
& cplhhHpmcUHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhcUHpmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcUHpmVWmL(gt1,gt2,g2,ZH,cplhhcUHpmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcUHpmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcUHpmVPL(gt1,gt2,g1,g2,ZP,TW,cplHpmcUHpmVP(gt1,gt2))

 End Do 
End Do 


cplHpmcUHpmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcUHpmVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcUHpmVZ(gt1,gt2))

 End Do 
End Do 


cplcUHpmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcUHpmVPVWmL(gt1,g1,g2,vd,vu,TW,cplcUHpmVPVWm(gt1))

End Do 


cplcUHpmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcUHpmVWmVZL(gt1,g1,g2,vd,vu,TW,cplcUHpmVWmVZ(gt1))

End Do 


cplAhAhUHpmcUHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhUHpmcUHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,cplAhAhUHpmcUHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhUHpmcUHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhUHpmcUHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,cplhhhhUHpmcUHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUHpmHpmcUHpmcHpm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUHpmHpmcUHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,ZP,cplUHpmHpmcUHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUHpmcUHpmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHpmcUHpmVPVPL(gt1,gt2,g1,g2,TW,cplUHpmcUHpmVPVP(gt1,gt2))

 End Do 
End Do 


cplUHpmcUHpmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHpmcUHpmcVWmVWmL(gt1,gt2,g2,cplUHpmcUHpmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUHpmcUHpmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHpmcUHpmVZVZL(gt1,gt2,g1,g2,TW,cplUHpmcUHpmVZVZ(gt1,gt2))

 End Do 
End Do 


cplUChiChiAhL = 0._dp 
cplUChiChiAhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingUChiChiAhL(gt1,gt2,gt3,g1,g2,lam,kap,ZA,ZN,cplUChiChiAhL(gt1,gt2,gt3)    & 
& ,cplUChiChiAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUChiChacHpmL = 0._dp 
cplUChiChacHpmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUChiChacHpmL(gt1,gt2,gt3,g1,g2,lam,ZP,UM,UP,cplUChiChacHpmL(gt1,gt2,gt3) & 
& ,cplUChiChacHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUChiChacVWmL = 0._dp 
cplUChiChacVWmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
Call CouplingUChiChacVWmL(gt1,gt2,g2,UM,UP,cplUChiChacVWmL(gt1,gt2),cplUChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplUChiChihhL = 0._dp 
cplUChiChihhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingUChiChihhL(gt1,gt2,gt3,g1,g2,lam,kap,ZH,ZN,cplUChiChihhL(gt1,gt2,gt3)    & 
& ,cplUChiChihhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUChiChiVZL = 0._dp 
cplUChiChiVZR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
Call CouplingUChiChiVZL(gt1,gt2,g1,g2,ZN,TW,cplUChiChiVZL(gt1,gt2),cplUChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcChaUChiHpmL = 0._dp 
cplcChaUChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
  Do gt3 = 1, 2
Call CouplingcChaUChiHpmL(gt1,gt2,gt3,g1,g2,lam,ZP,UM,UP,cplcChaUChiHpmL(gt1,gt2,gt3) & 
& ,cplcChaUChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaUChiVWmL = 0._dp 
cplcChaUChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
Call CouplingcChaUChiVWmL(gt1,gt2,g2,UM,UP,cplcChaUChiVWmL(gt1,gt2),cplcChaUChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcUChaChaAhL = 0._dp 
cplcUChaChaAhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcUChaChaAhL(gt1,gt2,gt3,g2,lam,ZA,UM,UP,cplcUChaChaAhL(gt1,gt2,gt3)      & 
& ,cplcUChaChaAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUChaChahhL = 0._dp 
cplcUChaChahhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcUChaChahhL(gt1,gt2,gt3,g2,lam,ZH,UM,UP,cplcUChaChahhL(gt1,gt2,gt3)      & 
& ,cplcUChaChahhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUChaChaVPL = 0._dp 
cplcUChaChaVPR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcUChaChaVPL(gt1,gt2,g1,g2,UM,UP,TW,cplcUChaChaVPL(gt1,gt2)               & 
& ,cplcUChaChaVPR(gt1,gt2))

 End Do 
End Do 


cplcUChaChaVZL = 0._dp 
cplcUChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcUChaChaVZL(gt1,gt2,g1,g2,UM,UP,TW,cplcUChaChaVZL(gt1,gt2)               & 
& ,cplcUChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplcUChaChiHpmL = 0._dp 
cplcUChaChiHpmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
  Do gt3 = 1, 2
Call CouplingcUChaChiHpmL(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,cplcUChaChiHpmL(gt1,gt2,gt3)    & 
& ,cplcUChaChiHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUChaChiVWmL = 0._dp 
cplcUChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 5
Call CouplingcUChaChiVWmL(gt1,gt2,g2,ZN,cplcUChaChiVWmL(gt1,gt2),cplcUChaChiVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFeFeAhL = 0._dp 
cplcUFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFeFeAhL(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcUFeFeAhL(gt1,gt2,gt3)            & 
& ,cplcUFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFeFehhL(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcUFeFehhL(gt1,gt2,gt3)            & 
& ,cplcUFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFeVPL = 0._dp 
cplcUFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFeVPL(gt1,gt2,g1,g2,ZEL,ZER,TW,cplcUFeFeVPL(gt1,gt2),cplcUFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcUFeFeVZL = 0._dp 
cplcUFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFeVZL(gt1,gt2,g1,g2,ZEL,ZER,TW,cplcUFeFeVZL(gt1,gt2),cplcUFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcUFeFvHpmL = 0._dp 
cplcUFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFvHpmL(gt1,gt2,gt3,Ye,ZP,cplcUFeFvHpmL(gt1,gt2,gt3),cplcUFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFvVWmL = 0._dp 
cplcUFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFvVWmL(gt1,gt2,g2,cplcUFeFvVWmL(gt1,gt2),cplcUFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFdFdAhL = 0._dp 
cplcUFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFdFdAhL(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcUFdFdAhL(gt1,gt2,gt3)            & 
& ,cplcUFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFdFdhhL(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcUFdFdhhL(gt1,gt2,gt3)            & 
& ,cplcUFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFdVGL = 0._dp 
cplcUFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdVGL(gt1,gt2,g3,ZDL,ZDR,cplcUFdFdVGL(gt1,gt2),cplcUFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcUFdFdVPL = 0._dp 
cplcUFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdVPL(gt1,gt2,g1,g2,ZDL,ZDR,TW,cplcUFdFdVPL(gt1,gt2),cplcUFdFdVPR(gt1,gt2))

 End Do 
End Do 


cplcUFdFdVZL = 0._dp 
cplcUFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdVZL(gt1,gt2,g1,g2,ZDL,ZDR,TW,cplcUFdFdVZL(gt1,gt2),cplcUFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcUFdFuHpmL = 0._dp 
cplcUFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFuHpmL(gt1,gt2,gt3,Yd,Yu,ZP,ZUL,ZUR,cplcUFdFuHpmL(gt1,gt2,gt3)       & 
& ,cplcUFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFuVWmL = 0._dp 
cplcUFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFuVWmL(gt1,gt2,g2,ZUL,cplcUFdFuVWmL(gt1,gt2),cplcUFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuAhL = 0._dp 
cplcUFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFuFuAhL(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcUFuFuAhL(gt1,gt2,gt3)            & 
& ,cplcUFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdcHpmL = 0._dp 
cplcUFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFuFdcHpmL(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,cplcUFuFdcHpmL(gt1,gt2,gt3)     & 
& ,cplcUFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdcVWmL = 0._dp 
cplcUFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFdcVWmL(gt1,gt2,g2,ZDL,cplcUFuFdcVWmL(gt1,gt2),cplcUFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuhhL = 0._dp 
cplcUFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFuFuhhL(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcUFuFuhhL(gt1,gt2,gt3)            & 
& ,cplcUFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFuVGL = 0._dp 
cplcUFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuVGL(gt1,gt2,g3,ZUL,ZUR,cplcUFuFuVGL(gt1,gt2),cplcUFuFuVGR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuVPL = 0._dp 
cplcUFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuVPL(gt1,gt2,g1,g2,ZUL,ZUR,TW,cplcUFuFuVPL(gt1,gt2),cplcUFuFuVPR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuVZL = 0._dp 
cplcUFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuVZL(gt1,gt2,g1,g2,ZUL,ZUR,TW,cplcUFuFuVZL(gt1,gt2),cplcUFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcUFvFecHpmL = 0._dp 
cplcUFvFecHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFvFecHpmL(gt1,gt2,gt3,Ye,ZP,ZER,cplcUFvFecHpmL(gt1,gt2,gt3)            & 
& ,cplcUFvFecHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFvFecVWmL = 0._dp 
cplcUFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFvFecVWmL(gt1,gt2,g2,ZEL,cplcUFvFecVWmL(gt1,gt2),cplcUFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFvFvVZL = 0._dp 
cplcUFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFvFvVZL(gt1,gt2,g1,g2,TW,cplcUFvFvVZL(gt1,gt2),cplcUFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVGL = 0._dp 
cplcFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVGL(gt1,gt2,g3,cplcFdFdVGL(gt1,gt2),cplcFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVGL = 0._dp 
cplcFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVGL(gt1,gt2,g3,cplcFuFuVGL(gt1,gt2),cplcFuFuVGR(gt1,gt2))

 End Do 
End Do 


cplcgGgGVG = 0._dp 
Call CouplingcgGgGVGL(g3,cplcgGgGVG)



cplVGVGVG = 0._dp 
Call CouplingVGVGVGL(g3,cplVGVGVG)



cplVGVGVGVG1 = 0._dp 
cplVGVGVGVG2 = 0._dp 
cplVGVGVGVG3 = 0._dp 
Call CouplingVGVGVGVGL(g3,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3)



cplcChaChaVPL = 0._dp 
cplcChaChaVPR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVPL(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVPL(gt1,gt2),cplcChaChaVPR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVPL = 0._dp 
cplcFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVPL(gt1,gt2,g1,g2,TW,cplcFdFdVPL(gt1,gt2),cplcFdFdVPR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVPL = 0._dp 
cplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVPL(gt1,gt2,g1,g2,TW,cplcFeFeVPL(gt1,gt2),cplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVPL = 0._dp 
cplcFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVPL(gt1,gt2,g1,g2,TW,cplcFuFuVPL(gt1,gt2),cplcFuFuVPR(gt1,gt2))

 End Do 
End Do 


cplcgWmgWmVP = 0._dp 
Call CouplingcgWmgWmVPL(g2,TW,cplcgWmgWmVP)



cplcgWpCgWpCVP = 0._dp 
Call CouplingcgWpCgWpCVPL(g2,TW,cplcgWpCgWpCVP)



cplHpmcHpmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVP(gt1,gt2))

 End Do 
End Do 


cplHpmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVPL(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVP(gt1))

End Do 


cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmL(g2,TW,cplcVWmVPVWm)



cplHpmcHpmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVPL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVP(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVPVWm1 = 0._dp 
cplcVWmVPVPVWm2 = 0._dp 
cplcVWmVPVPVWm3 = 0._dp 
Call CouplingcVWmVPVPVWmL(g2,TW,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3)



cplAhhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhhhVZL(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZL(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
Call CouplingChiChiVZL(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZL(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZL(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZL(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZL(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplcgWmgWmVZ = 0._dp 
Call CouplingcgWmgWmVZL(g2,TW,cplcgWmgWmVZ)



cplcgWpCgWpCVZ = 0._dp 
Call CouplingcgWpCgWpCVZL(g2,TW,cplcgWpCgWpCVZ)



cplhhVZVZ = 0._dp 
Do gt1 = 1, 3
Call CouplinghhVZVZL(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHpmcHpmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZ(gt1,gt2))

 End Do 
End Do 


cplHpmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVZ(gt1))

End Do 


cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZL(g2,TW,cplcVWmVWmVZ)



cplAhAhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhVZVZL(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhVZVZL(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVWmVZVZ1 = 0._dp 
cplcVWmVWmVZVZ2 = 0._dp 
cplcVWmVWmVZVZ3 = 0._dp 
Call CouplingcVWmVWmVZVZL(g2,TW,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3)



cplAhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmL(gt1,gt2,g2,ZA,ZP,cplAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
Call CouplingChiChacVWmL(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmL(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmL(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcgWpCgAcVWm = 0._dp 
Call CouplingcgWpCgAcVWmL(g2,TW,cplcgWpCgAcVWm)



cplcgAgWmcVWm = 0._dp 
Call CouplingcgAgWmcVWmL(g2,TW,cplcgAgWmcVWm)



cplcgZgWmcVWm = 0._dp 
Call CouplingcgZgWmcVWmL(g2,TW,cplcgZgWmcVWm)



cplcgWpCgZcVWm = 0._dp 
Call CouplingcgWpCgZcVWmL(g2,TW,cplcgWpCgZcVWm)



cplhhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmL(gt1,gt2,g2,ZH,ZP,cplhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
Call CouplinghhcVWmVWmL(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplAhAhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhcVWmVWmL(gt1,gt2,g2,ZA,cplAhAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhcVWmVWmL(gt1,gt2,g2,ZH,cplhhhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmcVWmVWmL(gt1,gt2,g2,ZP,cplHpmcHpmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplcVWmcVWmVWmVWm1 = 0._dp 
cplcVWmcVWmVWmVWm2 = 0._dp 
cplcVWmcVWmVWmVWm3 = 0._dp 
Call CouplingcVWmcVWmVWmVWmL(g2,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)



cplcHpmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVWmVZ(gt1))

End Do 


cplcHpmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVPVWmL(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVPVWm(gt1))

End Do 


cplHpmcHpmVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVWmVZ1 = 0._dp 
cplcVWmVPVWmVZ2 = 0._dp 
cplcVWmVPVWmVZ3 = 0._dp 
Call CouplingcVWmVPVWmVZL(g2,TW,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)



Iname = Iname - 1 
End Subroutine CouplingsForLoopMasses

Subroutine CouplingAhAhUhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g1**2*vd*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1**2*vu*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g2**2*vu*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((3.eq.gt3)) Then 
res = res-(vS*lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((3.eq.gt3)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res-(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,1))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res+(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res-(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt3)) Then 
res = res+(g1**2*vd*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((2.eq.gt3)) Then 
res = res-(g1**2*vu*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((3.eq.gt3)) Then 
res = res-(vS*lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((1.eq.gt3)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(Conjg(Tlam)*ZA(gt1,3)*ZA(gt2,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res+(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(Tlam*ZA(gt1,3)*ZA(gt2,2))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(Conjg(Tlam)*ZA(gt1,1)*ZA(gt2,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(Tlam*ZA(gt1,1)*ZA(gt2,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt3)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(Conjg(Tlam)*ZA(gt1,2)*ZA(gt2,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((3.eq.gt3)) Then 
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(Tlam*ZA(gt1,2)*ZA(gt2,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt3)) Then 
res = res-(vu*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vd*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))
End If 
If ((2.eq.gt3)) Then 
res = res-(vd*lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vu*lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))
End If 
If ((3.eq.gt3)) Then 
res = res-2*vS*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)
End If 
If ((3.eq.gt3)) Then 
res = res+(Conjg(Tk)*ZA(gt1,3)*ZA(gt2,3))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
res = res+(Tk*ZA(gt1,3)*ZA(gt2,3))/sqrt(2._dp)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhUhhL  
 
 
Subroutine CouplingAhUhhhhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhUhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((3.eq.gt2)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res-(Tlam*ZA(gt1,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt2)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(Tlam*ZA(gt1,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res-(Tlam*ZA(gt1,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt2)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(vS*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(Conjg(Tlam)*ZA(gt1,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(Tlam*ZA(gt1,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt2)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(Conjg(Tlam)*ZA(gt1,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res-(vu*lam*Conjg(kap)*ZA(gt1,1)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res+(vu*kap*Conjg(lam)*ZA(gt1,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(Tlam*ZA(gt1,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt2)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(Conjg(Tlam)*ZA(gt1,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res-(vd*lam*Conjg(kap)*ZA(gt1,2)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res+(vd*kap*Conjg(lam)*ZA(gt1,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(Tlam*ZA(gt1,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt2)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt1,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt1,3)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt2)) Then 
res = res-((Conjg(Tk)*ZA(gt1,3)*ZH(gt3,3))/sqrt(2._dp))
End If 
If ((3.eq.gt2)) Then 
res = res+(Tk*ZA(gt1,3)*ZH(gt3,3))/sqrt(2._dp)
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhUhhhhL  
 
 
Subroutine CouplingAhUhhVZL(gt1,gt2,g1,g2,ZA,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhUhhVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res-(g2*Cos(TW)*ZA(gt1,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(g1*Sin(TW)*ZA(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(g2*Cos(TW)*ZA(gt1,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(g1*Sin(TW)*ZA(gt1,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhUhhVZL  
 
 
Subroutine CouplingcChaChaUhhL(gt1,gt2,gt3,g2,lam,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
resL = resL-((g2*Conjg(UM(gt2,2))*Conjg(UP(gt1,1)))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resL = resL-((g2*Conjg(UM(gt2,1))*Conjg(UP(gt1,2)))/sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
resL = resL-((lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
resR = resR-((g2*UM(gt1,2)*UP(gt2,1))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resR = resR-((g2*UM(gt1,1)*UP(gt2,2))/sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2))/sqrt(2._dp))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaUhhL  
 
 
Subroutine CouplingChiChiUhhL(gt1,gt2,gt3,g1,g2,lam,kap,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
resL = resL+(g1*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,1)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL-(g2*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,2)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL+(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,3)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL-(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,3)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4)))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5)))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resL = resL-(g1*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,1)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL+(g2*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,2)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL+(lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3)))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resL = resL-(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,4)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL+(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,4)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5)))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
resL = resL+(lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3)))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
resL = resL+(lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4)))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
resL = resL-(sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5)))
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
resR = resR+(g1*ZN(gt1,3)*ZN(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
resR = resR-(g1*ZN(gt1,4)*ZN(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
resR = resR-(g2*ZN(gt1,3)*ZN(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
resR = resR+(g2*ZN(gt1,4)*ZN(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
resR = resR+(g1*ZN(gt1,1)*ZN(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
resR = resR-(g2*ZN(gt1,2)*ZN(gt2,3))/2._dp
End If 
If ((3.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR-(g1*ZN(gt1,1)*ZN(gt2,4))/2._dp
End If 
If ((2.eq.gt3)) Then 
resR = resR+(g2*ZN(gt1,2)*ZN(gt2,4))/2._dp
End If 
If ((3.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZN(gt1,5)*ZN(gt2,5))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiUhhL  
 
 
Subroutine CouplingcFdFdUhhL(gt1,gt2,gt3,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j2)*ZDR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdUhhL  
 
 
Subroutine CouplingcFeFeUhhL(gt1,gt2,gt3,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j2)*ZER(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeUhhL  
 
 
Subroutine CouplingcFuFuUhhL(gt1,gt2,gt3,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuUhhL  
 
 
Subroutine CouplingcgWmgWmUhhL(gt3,g2,vd,vu,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmUhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*RXiWm)/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmUhhL  
 
 
Subroutine CouplingcgWpCgWpCUhhL(gt3,g2,vd,vu,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCUhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*RXiWm)/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCUhhL  
 
 
Subroutine CouplingcgZgZUhhL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgZUhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*Cos(TW)**2*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*Cos(TW)**2*RXiZ)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g1*g2*vd*Cos(TW)*RXiZ*Sin(TW))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1*g2*vu*Cos(TW)*RXiZ*Sin(TW))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g1**2*vd*RXiZ*Sin(TW)**2)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1**2*vu*RXiZ*Sin(TW)**2)/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgZUhhL  
 
 
Subroutine CouplingUhhhhhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZH(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res+(-3*g1**2*vd*ZH(gt2,1)*ZH(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(-3*g2**2*vd*ZH(gt2,1)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1**2*vu*ZH(gt2,1)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vu*ZH(gt2,1)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZH(gt2,1)*ZH(gt3,1))
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt2,1)*ZH(gt3,1))
End If 
If ((1.eq.gt1)) Then 
res = res+(g1**2*vu*ZH(gt2,2)*ZH(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vu*ZH(gt2,2)*ZH(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZH(gt2,2)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res+(g1**2*vd*ZH(gt2,2)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vd*ZH(gt2,2)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZH(gt2,2)*ZH(gt3,1))
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(Tlam*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt2,3)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZH(gt2,3)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res+(Tlam*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(g1**2*vu*ZH(gt2,1)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vu*ZH(gt2,1)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZH(gt2,1)*ZH(gt3,2))
End If 
If ((2.eq.gt1)) Then 
res = res+(g1**2*vd*ZH(gt2,1)*ZH(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vd*ZH(gt2,1)*ZH(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZH(gt2,1)*ZH(gt3,2))
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(Tlam*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(g1**2*vd*ZH(gt2,2)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vd*ZH(gt2,2)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZH(gt2,2)*ZH(gt3,2))
End If 
If ((2.eq.gt1)) Then 
res = res+(-3*g1**2*vu*ZH(gt2,2)*ZH(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(-3*g2**2*vu*ZH(gt2,2)*ZH(gt3,2))/4._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt2,2)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt2,3)*ZH(gt3,2))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZH(gt2,3)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res+(Tlam*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt2,1)*ZH(gt3,3))
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*kap*Conjg(lam)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZH(gt2,1)*ZH(gt3,3))
End If 
If ((2.eq.gt1)) Then 
res = res+(Tlam*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt2,2)*ZH(gt3,3))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*kap*Conjg(lam)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZH(gt2,2)*ZH(gt3,3))
End If 
If ((1.eq.gt1)) Then 
res = res+(Tlam*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZH(gt2,3)*ZH(gt3,3))
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZH(gt2,3)*ZH(gt3,3))
End If 
If ((3.eq.gt1)) Then 
res = res-6*vS*kap*Conjg(kap)*ZH(gt2,3)*ZH(gt3,3)
End If 
If ((3.eq.gt1)) Then 
res = res-((Conjg(Tk)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-((Tk*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhhhhhL  
 
 
Subroutine CouplingUhhHpmcHpmL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g1**2*vd*ZP(gt2,1)*ZP(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(g2**2*vd*ZP(gt2,1)*ZP(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1**2*vu*ZP(gt2,1)*ZP(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2**2*vu*ZP(gt2,1)*ZP(gt3,1))/4._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZP(gt2,1)*ZP(gt3,1))
End If 
If ((1.eq.gt1)) Then 
res = res-(g2**2*vu*ZP(gt2,2)*ZP(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*lam*Conjg(lam)*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2**2*vd*ZP(gt2,2)*ZP(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*lam*Conjg(lam)*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*kap*Conjg(lam)*ZP(gt2,2)*ZP(gt3,1))
End If 
If ((3.eq.gt1)) Then 
res = res-((Conjg(Tlam)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(g2**2*vu*ZP(gt2,1)*ZP(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*lam*Conjg(lam)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2**2*vd*ZP(gt2,1)*ZP(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*lam*Conjg(lam)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZP(gt2,1)*ZP(gt3,2))
End If 
If ((3.eq.gt1)) Then 
res = res-((Tlam*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(g1**2*vd*ZP(gt2,2)*ZP(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(g2**2*vd*ZP(gt2,2)*ZP(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g1**2*vu*ZP(gt2,2)*ZP(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2**2*vu*ZP(gt2,2)*ZP(gt3,2))/4._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZP(gt2,2)*ZP(gt3,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhHpmcHpmL  
 
 
Subroutine CouplingUhhHpmcVWmL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhHpmcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g2*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2*ZP(gt2,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhHpmcVWmL  
 
 
Subroutine CouplingUhhcVWmVWmL(gt1,g2,vd,vu,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vd)/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vu)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhcVWmVWmL  
 
 
Subroutine CouplingUhhVZVZL(gt1,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vd*Cos(TW)**2)/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vu*Cos(TW)**2)/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+g1*g2*vd*Cos(TW)*Sin(TW)
End If 
If ((2.eq.gt1)) Then 
res = res+g1*g2*vu*Cos(TW)*Sin(TW)
End If 
If ((1.eq.gt1)) Then 
res = res+(g1**2*vd*Sin(TW)**2)/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1**2*vu*Sin(TW)**2)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhVZVZL  
 
 
Subroutine CouplingAhAhUhhUhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhUhhUhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g1**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g2**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1))/2._dp
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g1**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((1.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2))/2._dp
End If 
If ((2.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt4).And.(3.eq.gt3)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3).And.(3.eq.gt4)) Then 
res = res+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))/2._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))
End If 
If ((3.eq.gt3).And.(3.eq.gt4)) Then 
res = res-2*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhUhhUhhL  
 
 
Subroutine CouplingUhhUhhhhhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(-3*g1**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(-3*g2**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g1**2*ZH(gt3,2)*ZH(gt4,1))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZH(gt3,2)*ZH(gt4,1))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZH(gt3,2)*ZH(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZH(gt3,2)*ZH(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,1))
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,1))
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g1**2*ZH(gt3,1)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZH(gt3,1)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZH(gt3,1)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZH(gt3,1)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(-3*g1**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(-3*g2**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,2))
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,3))
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,3))
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,3))
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,3))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-6*kap*Conjg(kap)*ZH(gt3,3)*ZH(gt4,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhUhhhhhhL  
 
 
Subroutine CouplingUhhUhhHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g1**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(g2**2*ZP(gt3,2)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(lam*Conjg(lam)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,2)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(lam*Conjg(lam)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(kap*Conjg(lam)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(g2**2*ZP(gt3,1)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(lam*Conjg(lam)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,1)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(lam*Conjg(lam)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(kap)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g1**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhUhhHpmcHpmL  
 
 
Subroutine CouplingUhhUhhcVWmVWmL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+g2**2/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+g2**2/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhUhhcVWmVWmL  
 
 
Subroutine CouplingUhhUhhVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*Cos(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*Cos(TW)**2)/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+g1*g2*Cos(TW)*Sin(TW)
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+g1*g2*Cos(TW)*Sin(TW)
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*Sin(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*Sin(TW)**2)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhUhhVZVZL  
 
 
Subroutine CouplingUAhAhAhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,2)*ZA(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,2)*ZA(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(Tlam*ZA(gt2,2)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,3)*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,3)*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt2,3)*ZA(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt2,3)*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(Tlam*ZA(gt2,3)*ZA(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,1)*ZA(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,1)*ZA(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(Tlam*ZA(gt2,1)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,3)*ZA(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,3)*ZA(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt2,3)*ZA(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt2,3)*ZA(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(Tlam*ZA(gt2,3)*ZA(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,1)*ZA(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,1)*ZA(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt2,1)*ZA(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt2,1)*ZA(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(Tlam*ZA(gt2,1)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,2)*ZA(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,2)*ZA(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt2,2)*ZA(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt2,2)*ZA(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(Tlam*ZA(gt2,2)*ZA(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt2,3)*ZA(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt2,3)*ZA(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt2,3)*ZA(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt2,3)*ZA(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(Conjg(Tk)*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp)
End If 
If ((3.eq.gt1)) Then 
res = res-((Tk*ZA(gt2,3)*ZA(gt3,3))/sqrt(2._dp))
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhAhAhL  
 
 
Subroutine CouplingUAhAhhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,               & 
& ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g1**2*vd*ZA(gt2,1)*ZH(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(g2**2*vd*ZA(gt2,1)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1**2*vd*ZA(gt2,2)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vd*ZA(gt2,2)*ZH(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZA(gt2,2)*ZH(gt3,1))
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(Tlam*ZA(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*lam*Conjg(kap)*ZA(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*kap*Conjg(lam)*ZA(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZA(gt2,3)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(Tlam*ZA(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(g1**2*vu*ZA(gt2,1)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vu*ZA(gt2,1)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZA(gt2,1)*ZH(gt3,2))
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(Tlam*ZA(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(g1**2*vu*ZA(gt2,2)*ZH(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2**2*vu*ZA(gt2,2)*ZH(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZA(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZA(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*lam*Conjg(kap)*ZA(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*kap*Conjg(lam)*ZA(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZA(gt2,3)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res-(Tlam*ZA(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZA(gt2,1)*ZH(gt3,3))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*kap*Conjg(lam)*ZA(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*kap*Conjg(lam)*ZA(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Tlam*ZA(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*kap*Conjg(lam)*ZA(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Conjg(Tlam)*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(lam)*ZA(gt2,2)*ZH(gt3,3))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*kap*Conjg(lam)*ZA(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Tlam*ZA(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZA(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*kap*Conjg(lam)*ZA(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZA(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*kap*Conjg(lam)*ZA(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-2*vS*kap*Conjg(kap)*ZA(gt2,3)*ZH(gt3,3)
End If 
If ((3.eq.gt1)) Then 
res = res+(Conjg(Tk)*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
End If 
If ((3.eq.gt1)) Then 
res = res+(Tk*ZA(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhAhhhL  
 
 
Subroutine CouplingcChaChaUAhL(gt1,gt2,gt3,g2,lam,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaUAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
resL = resL-((g2*Conjg(UM(gt2,2))*Conjg(UP(gt1,1)))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resL = resL-((g2*Conjg(UM(gt2,1))*Conjg(UP(gt1,2)))/sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
resL = resL+(lam*Conjg(UM(gt2,2))*Conjg(UP(gt1,2)))/sqrt(2._dp)
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
resR = resR+(g2*UM(gt1,2)*UP(gt2,1))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR+(g2*UM(gt1,1)*UP(gt2,2))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
resR = resR-((Conjg(lam)*UM(gt1,2)*UP(gt2,2))/sqrt(2._dp))
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaUAhL  
 
 
Subroutine CouplingChiChiUAhL(gt1,gt2,gt3,g1,g2,lam,kap,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiUAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
resL = resL+(g1*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,1)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL-(g2*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,2)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL+(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,3)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL-(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,3)))/2._dp
End If 
If ((1.eq.gt3)) Then 
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,4)))/sqrt(2._dp))
End If 
If ((1.eq.gt3)) Then 
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,5)))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resL = resL-(g1*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,1)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL+(g2*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,2)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL-((lam*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,3)))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resL = resL-(g1*Conjg(ZN(gt1,1))*Conjg(ZN(gt2,4)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL+(g2*Conjg(ZN(gt1,2))*Conjg(ZN(gt2,4)))/2._dp
End If 
If ((2.eq.gt3)) Then 
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,5)))/sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
resL = resL-((lam*Conjg(ZN(gt1,4))*Conjg(ZN(gt2,3)))/sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
resL = resL-((lam*Conjg(ZN(gt1,3))*Conjg(ZN(gt2,4)))/sqrt(2._dp))
End If 
If ((3.eq.gt3)) Then 
resL = resL+sqrt(2._dp)*kap*Conjg(ZN(gt1,5))*Conjg(ZN(gt2,5))
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
resR = resR-(g1*ZN(gt1,3)*ZN(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
resR = resR+(g1*ZN(gt1,4)*ZN(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
resR = resR+(g2*ZN(gt1,3)*ZN(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
resR = resR-(g2*ZN(gt1,4)*ZN(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
resR = resR-(g1*ZN(gt1,1)*ZN(gt2,3))/2._dp
End If 
If ((1.eq.gt3)) Then 
resR = resR+(g2*ZN(gt1,2)*ZN(gt2,3))/2._dp
End If 
If ((3.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,4)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,5)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR+(g1*ZN(gt1,1)*ZN(gt2,4))/2._dp
End If 
If ((2.eq.gt3)) Then 
resR = resR-(g2*ZN(gt1,2)*ZN(gt2,4))/2._dp
End If 
If ((3.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,3)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,5)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((2.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,3)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resR = resR+(Conjg(lam)*ZN(gt1,4)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((3.eq.gt3)) Then 
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZN(gt1,5)*ZN(gt2,5))
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiUAhL  
 
 
Subroutine CouplingcFdFdUAhL(gt1,gt2,gt3,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdUAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j2)*ZDR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdUAhL  
 
 
Subroutine CouplingcFeFeUAhL(gt1,gt2,gt3,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeUAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j2)*ZER(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeUAhL  
 
 
Subroutine CouplingcFuFuUAhL(gt1,gt2,gt3,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuUAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
End If 
resR = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUL(gt1,j2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuUAhL  
 
 
Subroutine CouplingcgWmgWmUAhL(gt3,g2,vd,vu,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmUAh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*RXiWm)/4._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmUAhL  
 
 
Subroutine CouplingcgWpCgWpCUAhL(gt3,g2,vd,vu,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCUAh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g2**2*vu*RXiWm)/4._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCUAhL  
 
 
Subroutine CouplingUAhhhhhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,vS,ZH(3,3)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((3.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*kap*Conjg(lam)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(Tlam*ZH(gt2,2)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Tlam*ZH(gt2,3)*ZH(gt3,1))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vS*lam*Conjg(kap)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*kap*Conjg(lam)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res-(Tlam*ZH(gt2,1)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Tlam*ZH(gt2,3)*ZH(gt3,2))/(2._dp*sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vu*lam*Conjg(kap)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vu*kap*Conjg(lam)*ZH(gt2,1)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(Tlam*ZH(gt2,1)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vS*kap*Conjg(lam)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(Conjg(Tlam)*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(vd*lam*Conjg(kap)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vd*kap*Conjg(lam)*ZH(gt2,2)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(Tlam*ZH(gt2,2)*ZH(gt3,3))/(2._dp*sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*lam*Conjg(kap)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*kap*Conjg(lam)*ZH(gt2,3)*ZH(gt3,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-((Conjg(Tk)*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
res = res+(Tk*ZH(gt2,3)*ZH(gt3,3))/sqrt(2._dp)
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhhhhhL  
 
 
Subroutine CouplingUAhhhVZL(gt1,gt2,g1,g2,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhhhVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g2*Cos(TW)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(g1*Sin(TW)*ZH(gt2,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2*Cos(TW)*ZH(gt2,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1*Sin(TW)*ZH(gt2,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhhhVZL  
 
 
Subroutine CouplingUAhHpmcHpmL(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,vd,vu,vS,ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res+(g2**2*vu*ZP(gt2,2)*ZP(gt3,1))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*lam*Conjg(lam)*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2**2*vd*ZP(gt2,2)*ZP(gt3,1))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*lam*Conjg(lam)*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res+vS*kap*Conjg(lam)*ZP(gt2,2)*ZP(gt3,1)
End If 
If ((3.eq.gt1)) Then 
res = res-((Conjg(Tlam)*ZP(gt2,2)*ZP(gt3,1))/sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
res = res-(g2**2*vu*ZP(gt2,1)*ZP(gt3,2))/4._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*lam*Conjg(lam)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2**2*vd*ZP(gt2,1)*ZP(gt3,2))/4._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*lam*Conjg(lam)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
res = res-(vS*lam*Conjg(kap)*ZP(gt2,1)*ZP(gt3,2))
End If 
If ((3.eq.gt1)) Then 
res = res+(Tlam*ZP(gt2,1)*ZP(gt3,2))/sqrt(2._dp)
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhHpmcHpmL  
 
 
Subroutine CouplingUAhHpmcVWmL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhHpmcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g2*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g2*ZP(gt2,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhHpmcVWmL  
 
 
Subroutine CouplingUAhUAhAhAhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(-3*g1**2*ZA(gt3,1)*ZA(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(-3*g2**2*ZA(gt3,1)*ZA(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZA(gt3,1)*ZA(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZA(gt3,1)*ZA(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g1**2*ZA(gt3,2)*ZA(gt4,1))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZA(gt3,2)*ZA(gt4,1))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZA(gt3,2)*ZA(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZA(gt3,2)*ZA(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,3)*ZA(gt4,1))
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,3)*ZA(gt4,1))
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,3)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g1**2*ZA(gt3,1)*ZA(gt4,2))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZA(gt3,1)*ZA(gt4,2))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZA(gt3,1)*ZA(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZA(gt3,1)*ZA(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*ZA(gt3,2)*ZA(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*ZA(gt3,2)*ZA(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(-3*g1**2*ZA(gt3,2)*ZA(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(-3*g2**2*ZA(gt3,2)*ZA(gt4,2))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,3)*ZA(gt4,2))
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,3)*ZA(gt4,2))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,3)*ZA(gt4,2))
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,1)*ZA(gt4,3))
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,1)*ZA(gt4,3))
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,1)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,2)*ZA(gt4,3))
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,2)*ZA(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,2)*ZA(gt4,3))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,3)*ZA(gt4,3))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZA(gt3,3)*ZA(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZA(gt3,3)*ZA(gt4,3))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-6*kap*Conjg(kap)*ZA(gt3,3)*ZA(gt4,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhAhAhL  
 
 
Subroutine CouplingUAhUAhhhhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g1**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g2**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZH(gt3,1)*ZH(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(kap)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(kap*Conjg(lam)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,1))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(kap)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(kap*Conjg(lam)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g1**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZH(gt3,2)*ZH(gt4,2))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,2))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,1)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(3.eq.gt1)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(lam*Conjg(kap)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(3.eq.gt2)) Then 
res = res+(kap*Conjg(lam)*ZH(gt3,2)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(kap)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(kap*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZH(gt3,3)*ZH(gt4,3))
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-2*kap*Conjg(kap)*ZH(gt3,3)*ZH(gt4,3)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhhhhhL  
 
 
Subroutine CouplingUAhUAhHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g1**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,1)*ZP(gt4,1))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZP(gt3,2)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZP(gt3,2)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+kap*Conjg(lam)*ZP(gt3,2)*ZP(gt4,1)
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZP(gt3,1)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*ZP(gt3,1)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res+lam*Conjg(kap)*ZP(gt3,1)*ZP(gt4,2)
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g1**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g2**2*ZP(gt3,2)*ZP(gt4,2))/4._dp
End If 
If ((3.eq.gt1).And.(3.eq.gt2)) Then 
res = res-(lam*Conjg(lam)*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhHpmcHpmL  
 
 
Subroutine CouplingUAhUAhcVWmVWmL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+g2**2/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+g2**2/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhcVWmVWmL  
 
 
Subroutine CouplingUAhUAhVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*Cos(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*Cos(TW)**2)/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+g1*g2*Cos(TW)*Sin(TW)
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+g1*g2*Cos(TW)*Sin(TW)
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*Sin(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*Sin(TW)**2)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhVZVZL  
 
 
Subroutine CouplingAhHpmcUHpmL(gt1,gt2,gt3,g2,lam,Tlam,kap,vd,vu,vS,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,vd,vu,vS,ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*ZA(gt1,1)*ZP(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vd*ZA(gt1,2)*ZP(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vS*lam*Conjg(kap)*ZA(gt1,3)*ZP(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res+(Tlam*ZA(gt1,3)*ZP(gt2,1))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vu*ZA(gt1,1)*ZP(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vu*lam*Conjg(lam)*ZA(gt1,1)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*ZA(gt1,2)*ZP(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vd*lam*Conjg(lam)*ZA(gt1,2)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+vS*kap*Conjg(lam)*ZA(gt1,3)*ZP(gt2,2)
End If 
If ((1.eq.gt3)) Then 
res = res-((Conjg(Tlam)*ZA(gt1,3)*ZP(gt2,2))/sqrt(2._dp))
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcUHpmL  
 
 
Subroutine CouplingAhcUHpmVWmL(gt1,gt2,g2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcUHpmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res-(g2*ZA(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g2*ZA(gt1,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcUHpmVWmL  
 
 
Subroutine CouplingChiChacUHpmL(gt1,gt2,gt3,g1,g2,lam,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2

Complex(dp), Intent(in) :: lam,ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChacUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt3)) Then 
resL = resL+(g1*Conjg(UM(gt2,2))*Conjg(ZN(gt1,1)))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resL = resL+(g2*Conjg(UM(gt2,2))*Conjg(ZN(gt1,2)))/sqrt(2._dp)
End If 
If ((1.eq.gt3)) Then 
resL = resL-(g2*Conjg(UM(gt2,1))*Conjg(ZN(gt1,3)))
End If 
If ((2.eq.gt3)) Then 
resL = resL-(lam*Conjg(UM(gt2,2))*Conjg(ZN(gt1,5)))
End If 
resR = 0._dp 
If ((2.eq.gt3)) Then 
resR = resR-((g1*UP(gt2,2)*ZN(gt1,1))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resR = resR-((g2*UP(gt2,2)*ZN(gt1,2))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
resR = resR-(g2*UP(gt2,1)*ZN(gt1,4))
End If 
If ((1.eq.gt3)) Then 
resR = resR-(Conjg(lam)*UP(gt2,2)*ZN(gt1,5))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChacUHpmL  
 
 
Subroutine CouplingcFuFdcUHpmL(gt1,gt2,gt3,Yd,Yu,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZUL(gt1,j2)
End Do 
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcUHpmL  
 
 
Subroutine CouplingcFvFecUHpmL(gt1,gt2,gt3,Ye,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j1 = 1,3
resR = resR+Conjg(Ye(j1,gt1))*ZER(gt2,j1)
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecUHpmL  
 
 
Subroutine CouplingcgZgWmcUHpmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWmcUHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*Cos(TW)*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g2**2*vu*Cos(TW)*RXiZ)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g1*g2*vd*RXiZ*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiZ*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWmcUHpmL  
 
 
Subroutine CouplingcgWmgZUHpmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgZUHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*Cos(TW)*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*Cos(TW)*RXiWm)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g1*g2*vd*RXiWm*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiWm*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgZUHpmL  
 
 
Subroutine CouplingcgWpCgZcUHpmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgZcUHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*Cos(TW)*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*Cos(TW)*RXiWm)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g1*g2*vd*RXiWm*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiWm*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgZcUHpmL  
 
 
Subroutine CouplingcgZgWpCUHpmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpCUHpm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*Cos(TW)*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g2**2*vu*Cos(TW)*RXiZ)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g1*g2*vd*RXiZ*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiZ*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpCUHpmL  
 
 
Subroutine CouplinghhHpmcUHpmL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,               & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g1**2*vd*ZH(gt1,1)*ZP(gt2,1))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*ZH(gt1,1)*ZP(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*ZH(gt1,1)*ZP(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g1**2*vu*ZH(gt1,2)*ZP(gt2,1))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vu*ZH(gt1,2)*ZP(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vd*ZH(gt1,2)*ZP(gt2,1))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-(vS*lam*Conjg(kap)*ZH(gt1,3)*ZP(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-((Tlam*ZH(gt1,3)*ZP(gt2,1))/sqrt(2._dp))
End If 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vu*ZH(gt1,1)*ZP(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(vu*lam*Conjg(lam)*ZH(gt1,1)*ZP(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1**2*vd*ZH(gt1,1)*ZP(gt2,2))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vd*ZH(gt1,1)*ZP(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*ZH(gt1,2)*ZP(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(vd*lam*Conjg(lam)*ZH(gt1,2)*ZP(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1**2*vu*ZH(gt1,2)*ZP(gt2,2))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*ZH(gt1,2)*ZP(gt2,2))/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vS*kap*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2))
End If 
If ((1.eq.gt3)) Then 
res = res-((Conjg(Tlam)*ZH(gt1,3)*ZP(gt2,2))/sqrt(2._dp))
End If 
If ((2.eq.gt3)) Then 
res = res-(vS*lam*Conjg(lam)*ZH(gt1,3)*ZP(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcUHpmL  
 
 
Subroutine CouplinghhcUHpmVWmL(gt1,gt2,g2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcUHpmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res+(g2*ZH(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g2*ZH(gt1,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcUHpmVWmL  
 
 
Subroutine CouplingHpmcUHpmVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcUHpmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res-(g1*Cos(TW)*ZP(gt1,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(g2*Sin(TW)*ZP(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g1*Cos(TW)*ZP(gt1,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g2*Sin(TW)*ZP(gt1,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcUHpmVPL  
 
 
Subroutine CouplingHpmcUHpmVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcUHpmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res-(g2*Cos(TW)*ZP(gt1,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(g1*Sin(TW)*ZP(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g2*Cos(TW)*ZP(gt1,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(g1*Sin(TW)*ZP(gt1,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcUHpmVZL  
 
 
Subroutine CouplingcUHpmVPVWmL(gt1,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g1*g2*vd*Cos(TW))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1*g2*vu*Cos(TW))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUHpmVPVWmL  
 
 
Subroutine CouplingcUHpmVWmVZL(gt1,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res+(g1*g2*vd*Sin(TW))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g1*g2*vu*Sin(TW))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUHpmVWmVZL  
 
 
Subroutine CouplingAhAhUHpmcUHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhUHpmcUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g1**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g2**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(g1**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZA(gt1,1)*ZA(gt2,1))/4._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,1))/4._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,1))/4._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res+(g1**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g2**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g1**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZA(gt1,2)*ZA(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res+kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res+lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhUHpmcUHpmL  
 
 
Subroutine CouplinghhhhUHpmcUHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhUHpmcUHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g1**2*ZH(gt1,1)*ZH(gt2,1))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(g1**2*ZH(gt1,1)*ZH(gt2,1))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,1))/4._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,1))/4._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,1))/4._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,2))/4._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZH(gt1,1)*ZH(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res+(g1**2*ZH(gt1,2)*ZH(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,2))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g1**2*ZH(gt1,2)*ZH(gt2,2))/4._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(g2**2*ZH(gt1,2)*ZH(gt2,2))/4._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3))
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3))
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhUHpmcUHpmL  
 
 
Subroutine CouplingUHpmHpmcUHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpmHpmcUHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res-(g1**2*ZP(gt2,1)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res-(g2**2*ZP(gt2,1)*ZP(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res+(g1**2*ZP(gt2,1)*ZP(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res+(g2**2*ZP(gt2,1)*ZP(gt4,1))/4._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam*Conjg(lam)*ZP(gt2,1)*ZP(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res+(g1**2*ZP(gt2,2)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res+(g2**2*ZP(gt2,2)*ZP(gt4,1))/4._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam*Conjg(lam)*ZP(gt2,2)*ZP(gt4,1))
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res+(g1**2*ZP(gt2,1)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res+(g2**2*ZP(gt2,1)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res-(lam*Conjg(lam)*ZP(gt2,1)*ZP(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res+(g1**2*ZP(gt2,2)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res+(g2**2*ZP(gt2,2)*ZP(gt4,2))/4._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res-(lam*Conjg(lam)*ZP(gt2,2)*ZP(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(g1**2*ZP(gt2,2)*ZP(gt4,2))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(g2**2*ZP(gt2,2)*ZP(gt4,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUHpmHpmcUHpmcHpmL  
 
 
Subroutine CouplingUHpmcUHpmVPVPL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpmcUHpmVPVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*Cos(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*Cos(TW)**2)/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+g1*g2*Cos(TW)*Sin(TW)
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+g1*g2*Cos(TW)*Sin(TW)
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*Sin(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*Sin(TW)**2)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUHpmcUHpmVPVPL  
 
 
Subroutine CouplingUHpmcUHpmcVWmVWmL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpmcUHpmcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+g2**2/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+g2**2/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUHpmcUHpmcVWmVWmL  
 
 
Subroutine CouplingUHpmcUHpmVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpmcUHpmVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g2**2*Cos(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g2**2*Cos(TW)**2)/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(g1*g2*Cos(TW)*Sin(TW))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(g1*g2*Cos(TW)*Sin(TW))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(g1**2*Sin(TW)**2)/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(g1**2*Sin(TW)**2)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUHpmcUHpmVZVZL  
 
 
Subroutine CouplingUChiChiAhL(gt1,gt2,gt3,g1,g2,lam,kap,ZA,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUChiChiAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL+(g1*Conjg(ZN(gt2,3))*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,3))*ZA(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL+(g1*Conjg(ZN(gt2,1))*ZA(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,2))*ZA(gt3,1))/2._dp
End If 
If ((4.eq.gt1)) Then 
resL = resL-((lam*Conjg(ZN(gt2,5))*ZA(gt3,1))/sqrt(2._dp))
End If 
If ((5.eq.gt1)) Then 
resL = resL-((lam*Conjg(ZN(gt2,4))*ZA(gt3,1))/sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
resL = resL-(g1*Conjg(ZN(gt2,4))*ZA(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
resL = resL+(g2*Conjg(ZN(gt2,4))*ZA(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL-((lam*Conjg(ZN(gt2,5))*ZA(gt3,2))/sqrt(2._dp))
End If 
If ((4.eq.gt1)) Then 
resL = resL-(g1*Conjg(ZN(gt2,1))*ZA(gt3,2))/2._dp
End If 
If ((4.eq.gt1)) Then 
resL = resL+(g2*Conjg(ZN(gt2,2))*ZA(gt3,2))/2._dp
End If 
If ((5.eq.gt1)) Then 
resL = resL-((lam*Conjg(ZN(gt2,3))*ZA(gt3,2))/sqrt(2._dp))
End If 
If ((3.eq.gt1)) Then 
resL = resL-((lam*Conjg(ZN(gt2,4))*ZA(gt3,3))/sqrt(2._dp))
End If 
If ((4.eq.gt1)) Then 
resL = resL-((lam*Conjg(ZN(gt2,3))*ZA(gt3,3))/sqrt(2._dp))
End If 
If ((5.eq.gt1)) Then 
resL = resL+sqrt(2._dp)*kap*Conjg(ZN(gt2,5))*ZA(gt3,3)
End If 
resR = 0._dp 
If ((3.eq.gt1)) Then 
resR = resR-(g1*ZA(gt3,1)*ZN(gt2,1))/2._dp
End If 
If ((4.eq.gt1)) Then 
resR = resR+(g1*ZA(gt3,2)*ZN(gt2,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
resR = resR+(g2*ZA(gt3,1)*ZN(gt2,2))/2._dp
End If 
If ((4.eq.gt1)) Then 
resR = resR-(g2*ZA(gt3,2)*ZN(gt2,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
resR = resR-(g1*ZA(gt3,1)*ZN(gt2,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g2*ZA(gt3,1)*ZN(gt2,3))/2._dp
End If 
If ((5.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((4.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((5.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((1.eq.gt1)) Then 
resR = resR+(g1*ZA(gt3,2)*ZN(gt2,4))/2._dp
End If 
If ((2.eq.gt1)) Then 
resR = resR-(g2*ZA(gt3,2)*ZN(gt2,4))/2._dp
End If 
If ((3.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZA(gt3,3)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((4.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZA(gt3,1)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((3.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZA(gt3,2)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((5.eq.gt1)) Then 
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZA(gt3,3)*ZN(gt2,5))
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUChiChiAhL  
 
 
Subroutine CouplingUChiChacHpmL(gt1,gt2,gt3,g1,g2,lam,ZP,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUChiChacHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL+(g1*Conjg(UM(gt2,2))*ZP(gt3,1))/sqrt(2._dp)
End If 
If ((2.eq.gt1)) Then 
resL = resL+(g2*Conjg(UM(gt2,2))*ZP(gt3,1))/sqrt(2._dp)
End If 
If ((3.eq.gt1)) Then 
resL = resL-(g2*Conjg(UM(gt2,1))*ZP(gt3,1))
End If 
If ((5.eq.gt1)) Then 
resL = resL-(lam*Conjg(UM(gt2,2))*ZP(gt3,2))
End If 
resR = 0._dp 
If ((5.eq.gt1)) Then 
resR = resR-(Conjg(lam)*UP(gt2,2)*ZP(gt3,1))
End If 
If ((4.eq.gt1)) Then 
resR = resR-(g2*UP(gt2,1)*ZP(gt3,2))
End If 
If ((1.eq.gt1)) Then 
resR = resR-((g1*UP(gt2,2)*ZP(gt3,2))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resR = resR-((g2*UP(gt2,2)*ZP(gt3,2))/sqrt(2._dp))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUChiChacHpmL  
 
 
Subroutine CouplingUChiChacVWmL(gt1,gt2,g2,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUChiChacVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt1)) Then 
resL = resL-(g2*Conjg(UM(gt2,1)))
End If 
If ((3.eq.gt1)) Then 
resL = resL-((g2*Conjg(UM(gt2,2)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((2.eq.gt1)) Then 
resR = resR-(g2*UP(gt2,1))
End If 
If ((4.eq.gt1)) Then 
resR = resR+(g2*UP(gt2,2))/sqrt(2._dp)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUChiChacVWmL  
 
 
Subroutine CouplingUChiChihhL(gt1,gt2,gt3,g1,g2,lam,kap,ZH,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUChiChihh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL+(g1*Conjg(ZN(gt2,3))*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,3))*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL+(g1*Conjg(ZN(gt2,1))*ZH(gt3,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,2))*ZH(gt3,1))/2._dp
End If 
If ((4.eq.gt1)) Then 
resL = resL+(lam*Conjg(ZN(gt2,5))*ZH(gt3,1))/sqrt(2._dp)
End If 
If ((5.eq.gt1)) Then 
resL = resL+(lam*Conjg(ZN(gt2,4))*ZH(gt3,1))/sqrt(2._dp)
End If 
If ((1.eq.gt1)) Then 
resL = resL-(g1*Conjg(ZN(gt2,4))*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
resL = resL+(g2*Conjg(ZN(gt2,4))*ZH(gt3,2))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL+(lam*Conjg(ZN(gt2,5))*ZH(gt3,2))/sqrt(2._dp)
End If 
If ((4.eq.gt1)) Then 
resL = resL-(g1*Conjg(ZN(gt2,1))*ZH(gt3,2))/2._dp
End If 
If ((4.eq.gt1)) Then 
resL = resL+(g2*Conjg(ZN(gt2,2))*ZH(gt3,2))/2._dp
End If 
If ((5.eq.gt1)) Then 
resL = resL+(lam*Conjg(ZN(gt2,3))*ZH(gt3,2))/sqrt(2._dp)
End If 
If ((3.eq.gt1)) Then 
resL = resL+(lam*Conjg(ZN(gt2,4))*ZH(gt3,3))/sqrt(2._dp)
End If 
If ((4.eq.gt1)) Then 
resL = resL+(lam*Conjg(ZN(gt2,3))*ZH(gt3,3))/sqrt(2._dp)
End If 
If ((5.eq.gt1)) Then 
resL = resL-(sqrt(2._dp)*kap*Conjg(ZN(gt2,5))*ZH(gt3,3))
End If 
resR = 0._dp 
If ((3.eq.gt1)) Then 
resR = resR+(g1*ZH(gt3,1)*ZN(gt2,1))/2._dp
End If 
If ((4.eq.gt1)) Then 
resR = resR-(g1*ZH(gt3,2)*ZN(gt2,1))/2._dp
End If 
If ((3.eq.gt1)) Then 
resR = resR-(g2*ZH(gt3,1)*ZN(gt2,2))/2._dp
End If 
If ((4.eq.gt1)) Then 
resR = resR+(g2*ZH(gt3,2)*ZN(gt2,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
resR = resR+(g1*ZH(gt3,1)*ZN(gt2,3))/2._dp
End If 
If ((2.eq.gt1)) Then 
resR = resR-(g2*ZH(gt3,1)*ZN(gt2,3))/2._dp
End If 
If ((5.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((4.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt2,3))/sqrt(2._dp)
End If 
If ((5.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((1.eq.gt1)) Then 
resR = resR-(g1*ZH(gt3,2)*ZN(gt2,4))/2._dp
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g2*ZH(gt3,2)*ZN(gt2,4))/2._dp
End If 
If ((3.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZH(gt3,3)*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((4.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZH(gt3,1)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((3.eq.gt1)) Then 
resR = resR+(Conjg(lam)*ZH(gt3,2)*ZN(gt2,5))/sqrt(2._dp)
End If 
If ((5.eq.gt1)) Then 
resR = resR-(sqrt(2._dp)*Conjg(kap)*ZH(gt3,3)*ZN(gt2,5))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUChiChihhL  
 
 
Subroutine CouplingUChiChiVZL(gt1,gt2,g1,g2,ZN,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUChiChiVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((3.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,3))*Cos(TW))/2._dp
End If 
If ((4.eq.gt1)) Then 
resL = resL+(g2*Conjg(ZN(gt2,4))*Cos(TW))/2._dp
End If 
If ((3.eq.gt1)) Then 
resL = resL-(g1*Conjg(ZN(gt2,3))*Sin(TW))/2._dp
End If 
If ((4.eq.gt1)) Then 
resL = resL+(g1*Conjg(ZN(gt2,4))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((3.eq.gt1)) Then 
resR = resR+(g2*Cos(TW)*ZN(gt2,3))/2._dp
End If 
If ((3.eq.gt1)) Then 
resR = resR+(g1*Sin(TW)*ZN(gt2,3))/2._dp
End If 
If ((4.eq.gt1)) Then 
resR = resR-(g2*Cos(TW)*ZN(gt2,4))/2._dp
End If 
If ((4.eq.gt1)) Then 
resR = resR-(g1*Sin(TW)*ZN(gt2,4))/2._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUChiChiVZL  
 
 
Subroutine CouplingcChaUChiHpmL(gt1,gt2,gt3,g1,g2,lam,ZP,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaUChiHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((5.eq.gt2)) Then 
resL = resL-(lam*Conjg(UP(gt1,2))*ZP(gt3,1))
End If 
If ((1.eq.gt2)) Then 
resL = resL-((g1*Conjg(UP(gt1,2))*ZP(gt3,2))/sqrt(2._dp))
End If 
If ((2.eq.gt2)) Then 
resL = resL-((g2*Conjg(UP(gt1,2))*ZP(gt3,2))/sqrt(2._dp))
End If 
If ((4.eq.gt2)) Then 
resL = resL-(g2*Conjg(UP(gt1,1))*ZP(gt3,2))
End If 
resR = 0._dp 
If ((3.eq.gt2)) Then 
resR = resR-(g2*UM(gt1,1)*ZP(gt3,1))
End If 
If ((1.eq.gt2)) Then 
resR = resR+(g1*UM(gt1,2)*ZP(gt3,1))/sqrt(2._dp)
End If 
If ((2.eq.gt2)) Then 
resR = resR+(g2*UM(gt1,2)*ZP(gt3,1))/sqrt(2._dp)
End If 
If ((5.eq.gt2)) Then 
resR = resR-(Conjg(lam)*UM(gt1,2)*ZP(gt3,2))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaUChiHpmL  
 
 
Subroutine CouplingcChaUChiVWmL(gt1,gt2,g2,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaUChiVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt2)) Then 
resL = resL-(g2*UM(gt1,1))
End If 
If ((3.eq.gt2)) Then 
resL = resL-((g2*UM(gt1,2))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((2.eq.gt2)) Then 
resR = resR-(g2*Conjg(UP(gt1,1)))
End If 
If ((4.eq.gt2)) Then 
resR = resR+(g2*Conjg(UP(gt1,2)))/sqrt(2._dp)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaUChiVWmL  
 
 
Subroutine CouplingcUChaChaAhL(gt1,gt2,gt3,g2,lam,ZA,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUChaChaAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL-((g2*Conjg(UM(gt2,2))*ZA(gt3,1))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resL = resL-((g2*Conjg(UM(gt2,1))*ZA(gt3,2))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resL = resL+(lam*Conjg(UM(gt2,2))*ZA(gt3,3))/sqrt(2._dp)
End If 
resR = 0._dp 
If ((2.eq.gt1)) Then 
resR = resR+(g2*UP(gt2,1)*ZA(gt3,1))/sqrt(2._dp)
End If 
If ((1.eq.gt1)) Then 
resR = resR+(g2*UP(gt2,2)*ZA(gt3,2))/sqrt(2._dp)
End If 
If ((2.eq.gt1)) Then 
resR = resR-((Conjg(lam)*UP(gt2,2)*ZA(gt3,3))/sqrt(2._dp))
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUChaChaAhL  
 
 
Subroutine CouplingcUChaChahhL(gt1,gt2,gt3,g2,lam,ZH,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUChaChahh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL-((g2*Conjg(UM(gt2,2))*ZH(gt3,1))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resL = resL-((g2*Conjg(UM(gt2,1))*ZH(gt3,2))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resL = resL-((lam*Conjg(UM(gt2,2))*ZH(gt3,3))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((2.eq.gt1)) Then 
resR = resR-((g2*UP(gt2,1)*ZH(gt3,1))/sqrt(2._dp))
End If 
If ((1.eq.gt1)) Then 
resR = resR-((g2*UP(gt2,2)*ZH(gt3,2))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resR = resR-((Conjg(lam)*UP(gt2,2)*ZH(gt3,3))/sqrt(2._dp))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUChaChahhL  
 
 
Subroutine CouplingcUChaChaVPL(gt1,gt2,g1,g2,UM,UP,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUChaChaVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt1)) Then 
resL = resL+(g1*Conjg(UM(gt2,2))*Cos(TW))/2._dp
End If 
If ((1.eq.gt1)) Then 
resL = resL+g2*Conjg(UM(gt2,1))*Sin(TW)
End If 
If ((2.eq.gt1)) Then 
resL = resL+(g2*Conjg(UM(gt2,2))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((1.eq.gt1)) Then 
resR = resR+g2*Sin(TW)*UP(gt2,1)
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g1*Cos(TW)*UP(gt2,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g2*Sin(TW)*UP(gt2,2))/2._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUChaChaVPL  
 
 
Subroutine CouplingcUChaChaVZL(gt1,gt2,g1,g2,UM,UP,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUChaChaVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL+g2*Conjg(UM(gt2,1))*Cos(TW)
End If 
If ((2.eq.gt1)) Then 
resL = resL+(g2*Conjg(UM(gt2,2))*Cos(TW))/2._dp
End If 
If ((2.eq.gt1)) Then 
resL = resL-(g1*Conjg(UM(gt2,2))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((1.eq.gt1)) Then 
resR = resR+g2*Cos(TW)*UP(gt2,1)
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g2*Cos(TW)*UP(gt2,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
resR = resR-(g1*Sin(TW)*UP(gt2,2))/2._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUChaChaVZL  
 
 
Subroutine CouplingcUChaChiHpmL(gt1,gt2,gt3,g1,g2,lam,ZP,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam,ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUChaChiHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((2.eq.gt1)) Then 
resL = resL-(lam*Conjg(ZN(gt2,5))*ZP(gt3,1))
End If 
If ((1.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,4))*ZP(gt3,2))
End If 
If ((2.eq.gt1)) Then 
resL = resL-((g1*Conjg(ZN(gt2,1))*ZP(gt3,2))/sqrt(2._dp))
End If 
If ((2.eq.gt1)) Then 
resL = resL-((g2*Conjg(ZN(gt2,2))*ZP(gt3,2))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((2.eq.gt1)) Then 
resR = resR+(g1*ZN(gt2,1)*ZP(gt3,1))/sqrt(2._dp)
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g2*ZN(gt2,2)*ZP(gt3,1))/sqrt(2._dp)
End If 
If ((1.eq.gt1)) Then 
resR = resR-(g2*ZN(gt2,3)*ZP(gt3,1))
End If 
If ((2.eq.gt1)) Then 
resR = resR-(Conjg(lam)*ZN(gt2,5)*ZP(gt3,2))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUChaChiHpmL  
 
 
Subroutine CouplingcUChaChiVWmL(gt1,gt2,g2,ZN,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUChaChiVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((1.eq.gt1)) Then 
resL = resL-(g2*Conjg(ZN(gt2,2)))
End If 
If ((2.eq.gt1)) Then 
resL = resL-((g2*Conjg(ZN(gt2,3)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((1.eq.gt1)) Then 
resR = resR-(g2*ZN(gt2,2))
End If 
If ((2.eq.gt1)) Then 
resR = resR+(g2*ZN(gt2,4))/sqrt(2._dp)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUChaChiVWmL  
 
 
Subroutine CouplingcUFeFeAhL(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFeAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL+(Conjg(ZEL(gt2,j2))*Ye(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,gt1))*ZA(gt3,1)*ZER(gt2,j1))/sqrt(2._dp))
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFeAhL  
 
 
Subroutine CouplingcUFeFehhL(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFehh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL-((Conjg(ZEL(gt2,j2))*Ye(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFehhL  
 
 
Subroutine CouplingcUFeFeVPL(gt1,gt2,g1,g2,ZEL,ZER,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFeVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g1*Conjg(ZEL(gt2,gt1))*Cos(TW))/2._dp
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g2*Conjg(ZEL(gt2,gt1))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR+g1*Cos(TW)*ZER(gt2,gt1)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFeVPL  
 
 
Subroutine CouplingcUFeFeVZL(gt1,gt2,g1,g2,ZEL,ZER,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFeVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g2*Conjg(ZEL(gt2,gt1))*Cos(TW))/2._dp
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g1*Conjg(ZEL(gt2,gt1))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR-(g1*Sin(TW)*ZER(gt2,gt1))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFeVZL  
 
 
Subroutine CouplingcUFeFvHpmL(gt1,gt2,gt3,Ye,ZP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFvHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+Ye(gt1,gt2)*ZP(gt3,1)
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFvHpmL  
 
 
Subroutine CouplingcUFeFvVWmL(gt1,gt2,g2,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFvVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2).And.(gt2.le.3).And.(gt2.ge.1)) Then 
resL = resL-(g2/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFvVWmL  
 
 
Subroutine CouplingcUFdFdAhL(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFdAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL+(Conjg(ZDL(gt2,j2))*Yd(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,gt1))*ZA(gt3,1)*ZDR(gt2,j1))/sqrt(2._dp))
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFdAhL  
 
 
Subroutine CouplingcUFdFdhhL(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFdhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL-((Conjg(ZDL(gt2,j2))*Yd(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,gt1))*ZDR(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFdhhL  
 
 
Subroutine CouplingcUFdFdVGL(gt1,gt2,g3,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(in) :: ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFdVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g3*Conjg(ZDL(gt2,gt1)))
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR-(g3*ZDR(gt2,gt1))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFdVGL  
 
 
Subroutine CouplingcUFdFdVPL(gt1,gt2,g1,g2,ZDL,ZDR,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFdVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g1*Conjg(ZDL(gt2,gt1))*Cos(TW))/6._dp
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g2*Conjg(ZDL(gt2,gt1))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR+(g1*Cos(TW)*ZDR(gt2,gt1))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFdVPL  
 
 
Subroutine CouplingcUFdFdVZL(gt1,gt2,g1,g2,ZDL,ZDR,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFdVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g2*Conjg(ZDL(gt2,gt1))*Cos(TW))/2._dp
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g1*Conjg(ZDL(gt2,gt1))*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR-(g1*Sin(TW)*ZDR(gt2,gt1))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFdVZL  
 
 
Subroutine CouplingcUFdFuHpmL(gt1,gt2,gt3,Yd,Yu,ZP,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFuHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL+Conjg(ZUL(gt2,j2))*Yd(gt1,j2)*ZP(gt3,1)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,gt1))*ZP(gt3,2)*ZUR(gt2,j1)
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFuHpmL  
 
 
Subroutine CouplingcUFdFuVWmL(gt1,gt2,g2,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFuVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-((g2*Conjg(ZUL(gt2,gt1)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFuVWmL  
 
 
Subroutine CouplingcUFuFuAhL(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFuAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL+(Conjg(ZUL(gt2,j2))*Yu(gt1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,gt1))*ZA(gt3,2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFuAhL  
 
 
Subroutine CouplingcUFuFdcHpmL(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFdcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL+Conjg(ZDL(gt2,j2))*Yu(gt1,j2)*ZP(gt3,2)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,gt1))*ZDR(gt2,j1)*ZP(gt3,1)
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFdcHpmL  
 
 
Subroutine CouplingcUFuFdcVWmL(gt1,gt2,g2,ZDL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFdcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-((g2*Conjg(ZDL(gt2,gt1)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFdcVWmL  
 
 
Subroutine CouplingcUFuFuhhL(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(3,3)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFuhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resL = resL-((Conjg(ZUL(gt2,j2))*Yu(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,gt1))*ZH(gt3,2)*ZUR(gt2,j1))/sqrt(2._dp))
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFuhhL  
 
 
Subroutine CouplingcUFuFuVGL(gt1,gt2,g3,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(in) :: ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFuVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g3*Conjg(ZUL(gt2,gt1)))
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR-(g3*ZUR(gt2,gt1))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFuVGL  
 
 
Subroutine CouplingcUFuFuVPL(gt1,gt2,g1,g2,ZUL,ZUR,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFuVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g1*Conjg(ZUL(gt2,gt1))*Cos(TW))/6._dp
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g2*Conjg(ZUL(gt2,gt1))*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR+(-2*g1*Cos(TW)*ZUR(gt2,gt1))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFuVPL  
 
 
Subroutine CouplingcUFuFuVZL(gt1,gt2,g1,g2,ZUL,ZUR,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFuVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-(g2*Conjg(ZUL(gt2,gt1))*Cos(TW))/2._dp
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL+(g1*Conjg(ZUL(gt2,gt1))*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resR = resR+(2*g1*Sin(TW)*ZUR(gt2,gt1))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFuVZL  
 
 
Subroutine CouplingcUFvFecHpmL(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFvFecHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

resL = 0._dp 
resR = 0._dp 
Do j1 = 1,3
resR = resR+Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFvFecHpmL  
 
 
Subroutine CouplingcUFvFecVWmL(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFvFecVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-((g2*Conjg(ZEL(gt2,gt1)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFvFecVWmL  
 
 
Subroutine CouplingcUFvFvVZL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFvFvVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFvFvVZL  
 
 
Subroutine CouplingcFdFdVGL(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVGL  
 
 
Subroutine CouplingcFuFuVGL(gt1,gt2,g3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVG' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-1._dp*(g3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(g3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVGL  
 
 
Subroutine CouplingcgGgGVGL(g3,res)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgGgGVG' 
 
res = 0._dp 
res = res+g3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgGgGVGL  
 
 
Subroutine CouplingVGVGVGL(g3,res)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVG' 
 
res = 0._dp 
res = res+g3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVGL  
 
 
Subroutine CouplingVGVGVGVGL(g3,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVGVG' 
 
res1 = 0._dp 
res1 = res1-16*g3**2
res2 = 0._dp 
res3 = 0._dp 
res3 = res3+16*g3**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVGVGL  
 
 
Subroutine CouplingcChaChaVPL(gt1,gt2,g1,g2,UM,UP,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+g2*Conjg(UM(gt2,1))*Sin(TW)*UM(gt1,1)
resL = resL+(g1*Conjg(UM(gt2,2))*Cos(TW)*UM(gt1,2))/2._dp
resL = resL+(g2*Conjg(UM(gt2,2))*Sin(TW)*UM(gt1,2))/2._dp
resR = 0._dp 
resR = resR+g2*Conjg(UP(gt1,1))*Sin(TW)*UP(gt2,1)
resR = resR+(g1*Conjg(UP(gt1,2))*Cos(TW)*UP(gt2,2))/2._dp
resR = resR+(g2*Conjg(UP(gt1,2))*Sin(TW)*UP(gt2,2))/2._dp
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaVPL  
 
 
Subroutine CouplingcFdFdVPL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Cos(TW))/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(g1*Cos(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVPL  
 
 
Subroutine CouplingcFeFeVPL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL+(g1*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+g1*Cos(TW)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeVPL  
 
 
Subroutine CouplingcFuFuVPL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Cos(TW))/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(-2*g1*Cos(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVPL  
 
 
Subroutine CouplingcgWmgWmVPL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmVP' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmVPL  
 
 
Subroutine CouplingcgWpCgWpCVPL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCVP' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCVPL  
 
 
Subroutine CouplingHpmcHpmVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g2*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPL  
 
 
Subroutine CouplingHpmcVWmVPL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcVWmVPL  
 
 
Subroutine CouplingcVWmVPVWmL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVWm' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVWmL  
 
 
Subroutine CouplingHpmcHpmVPVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVPVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1**2*Cos(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,1)*ZP(gt2,1)
res = res+(g2**2*Sin(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1**2*Cos(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,2)*ZP(gt2,2)
res = res+(g2**2*Sin(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPVPL  
 
 
Subroutine CouplingcVWmVPVPVWmL(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVPVWm' 
 
res1 = 0._dp 
res1 = res1+g2**2*Sin(TW)**2
res2 = 0._dp 
res2 = res2+g2**2*Sin(TW)**2
res3 = 0._dp 
res3 = res3-2*g2**2*Sin(TW)**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVPVWmL  
 
 
Subroutine CouplingAhhhVZL(gt1,gt2,g1,g2,ZH,ZA,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZA(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*Cos(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res-(g1*Sin(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2*Cos(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(g1*Sin(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhVZL  
 
 
Subroutine CouplingcChaChaVZL(gt1,gt2,g1,g2,UM,UP,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcChaChaVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL+g2*Conjg(UM(gt2,1))*Cos(TW)*UM(gt1,1)
resL = resL+(g2*Conjg(UM(gt2,2))*Cos(TW)*UM(gt1,2))/2._dp
resL = resL-(g1*Conjg(UM(gt2,2))*Sin(TW)*UM(gt1,2))/2._dp
resR = 0._dp 
resR = resR+g2*Conjg(UP(gt1,1))*Cos(TW)*UP(gt2,1)
resR = resR+(g2*Conjg(UP(gt1,2))*Cos(TW)*UP(gt2,2))/2._dp
resR = resR-(g1*Conjg(UP(gt1,2))*Sin(TW)*UP(gt2,2))/2._dp
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcChaChaVZL  
 
 
Subroutine CouplingChiChiVZL(gt1,gt2,g1,g2,ZN,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(in) :: ZN(5,5)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChiVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(g2*Conjg(ZN(gt2,3))*Cos(TW)*ZN(gt1,3))/2._dp
resL = resL-(g1*Conjg(ZN(gt2,3))*Sin(TW)*ZN(gt1,3))/2._dp
resL = resL+(g2*Conjg(ZN(gt2,4))*Cos(TW)*ZN(gt1,4))/2._dp
resL = resL+(g1*Conjg(ZN(gt2,4))*Sin(TW)*ZN(gt1,4))/2._dp
resR = 0._dp 
resR = resR+(g2*Conjg(ZN(gt1,3))*Cos(TW)*ZN(gt2,3))/2._dp
resR = resR+(g1*Conjg(ZN(gt1,3))*Sin(TW)*ZN(gt2,3))/2._dp
resR = resR-(g2*Conjg(ZN(gt1,4))*Cos(TW)*ZN(gt2,4))/2._dp
resR = resR-(g1*Conjg(ZN(gt1,4))*Sin(TW)*ZN(gt2,4))/2._dp
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChiVZL  
 
 
Subroutine CouplingcFdFdVZL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g1*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-(g1*Sin(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdVZL  
 
 
Subroutine CouplingcFeFeVZL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL+(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-(g1*Sin(TW))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeVZL  
 
 
Subroutine CouplingcFuFuVZL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(g1*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(2*g1*Sin(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuVZL  
 
 
Subroutine CouplingcFvFvVZL(gt1,gt2,g1,g2,TW,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFvVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.eq.gt2)) Then 
resL = resL-(g2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(g1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFvVZL  
 
 
Subroutine CouplingcgWmgWmVZL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgWmVZL  
 
 
Subroutine CouplingcgWpCgWpCVZL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCVZ' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCVZL  
 
 
Subroutine CouplinghhVZVZL(gt1,g1,g2,vd,vu,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*Cos(TW)**2*ZH(gt1,1))/2._dp
res = res+g1*g2*vd*Cos(TW)*Sin(TW)*ZH(gt1,1)
res = res+(g1**2*vd*Sin(TW)**2*ZH(gt1,1))/2._dp
res = res+(g2**2*vu*Cos(TW)**2*ZH(gt1,2))/2._dp
res = res+g1*g2*vu*Cos(TW)*Sin(TW)*ZH(gt1,2)
res = res+(g1**2*vu*Sin(TW)**2*ZH(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhVZVZL  
 
 
Subroutine CouplingHpmcHpmVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(g1*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVZL  
 
 
Subroutine CouplingHpmcVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcVWmVZL  
 
 
Subroutine CouplingcVWmVWmVZL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVWmVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVWmVZL  
 
 
Subroutine CouplingAhAhVZVZL(gt1,gt2,g1,g2,ZA,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*Cos(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,1)*ZA(gt2,1)
res = res+(g1**2*Sin(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+(g2**2*Cos(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,2)*ZA(gt2,2)
res = res+(g1**2*Sin(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhVZVZL  
 
 
Subroutine CouplinghhhhVZVZL(gt1,gt2,g1,g2,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*Cos(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,1)*ZH(gt2,1)
res = res+(g1**2*Sin(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2**2*Cos(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,2)*ZH(gt2,2)
res = res+(g1**2*Sin(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZL  
 
 
Subroutine CouplingHpmcHpmVZVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*Cos(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))
res = res+(g1**2*Sin(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2**2*Cos(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))
res = res+(g1**2*Sin(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVZVZL  
 
 
Subroutine CouplingcVWmVWmVZVZL(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVWmVZVZ' 
 
res1 = 0._dp 
res1 = res1-2*g2**2*Cos(TW)**2
res2 = 0._dp 
res2 = res2+g2**2*Cos(TW)**2
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVWmVZVZL  
 
 
Subroutine CouplingAhHpmcVWmL(gt1,gt2,g2,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcVWmL  
 
 
Subroutine CouplingChiChacVWmL(gt1,gt2,g2,ZN,UM,UP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZN(5,5),UM(2,2),UP(2,2)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingChiChacVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.5)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
resL = resL-(g2*Conjg(UM(gt2,1))*ZN(gt1,2))
resL = resL-((g2*Conjg(UM(gt2,2))*ZN(gt1,3))/sqrt(2._dp))
resR = 0._dp 
resR = resR-(g2*Conjg(ZN(gt1,2))*UP(gt2,1))
resR = resR+(g2*Conjg(ZN(gt1,4))*UP(gt2,2))/sqrt(2._dp)
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingChiChacVWmL  
 
 
Subroutine CouplingcFuFdcVWmL(gt1,gt2,g2,ZDL,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
Do j1 = 1,3
resL = resL-((g2*Conjg(ZDL(gt2,j1))*ZUL(gt1,j1))/sqrt(2._dp))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcVWmL  
 
 
Subroutine CouplingcFvFecVWmL(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-((g2*Conjg(ZEL(gt2,gt1)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecVWmL  
 
 
Subroutine CouplingcgWpCgAcVWmL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgAcVWm' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgAcVWmL  
 
 
Subroutine CouplingcgAgWmcVWmL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgAgWmcVWm' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgAgWmcVWmL  
 
 
Subroutine CouplingcgZgWmcVWmL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWmcVWm' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWmcVWmL  
 
 
Subroutine CouplingcgWpCgZcVWmL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgZcVWm' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgZcVWmL  
 
 
Subroutine CouplinghhHpmcVWmL(gt1,gt2,g2,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcVWmL  
 
 
Subroutine CouplinghhcVWmVWmL(gt1,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*ZH(gt1,1))/2._dp
res = res+(g2**2*vu*ZH(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcVWmVWmL  
 
 
Subroutine CouplingAhAhcVWmVWmL(gt1,gt2,g2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+(g2**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhcVWmVWmL  
 
 
Subroutine CouplinghhhhcVWmVWmL(gt1,gt2,g2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWmVWmL  
 
 
Subroutine CouplingHpmcHpmcVWmVWmL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmcVWmVWmL  
 
 
Subroutine CouplingcVWmcVWmVWmVWmL(g2,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmcVWmVWmVWm' 
 
res1 = 0._dp 
res1 = res1+2*g2**2
res2 = 0._dp 
res2 = res2-g2**2
res3 = 0._dp 
res3 = res3-g2**2
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmcVWmVWmVWmL  
 
 
Subroutine CouplingcHpmVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpmVWmVZL  
 
 
Subroutine CouplingcHpmVPVWmL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpmVPVWmL  
 
 
Subroutine CouplingHpmcHpmVPVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVPVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1**2*Sin(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/4._dp
res = res+(g2**2*Sin(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/4._dp
res = res+(g1*g2*Cos(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1**2*Sin(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/4._dp
res = res+(g2**2*Sin(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPVZL  
 
 
Subroutine CouplingcVWmVPVWmVZL(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVWmVZ' 
 
res1 = 0._dp 
res1 = res1+(g2**2*Sin(2._dp*(TW)))/2._dp
res2 = 0._dp 
res2 = res2-(g2**2*Sin(2._dp*(TW)))
res3 = 0._dp 
res3 = res3+(g2**2*Sin(2._dp*(TW)))/2._dp
If ((Real(res1,dp).ne.Real(res1,dp)).or.(Real(res2,dp).ne.Real(res2,dp)).or.(Real(res3,dp).ne.Real(res3,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVWmVZL  
 
 
Subroutine CouplingsForVectorBosons(g1,g2,UM,UP,TW,ZP,vd,vu,ZH,ZA,ZN,ZDL,             & 
& ZUL,ZEL,cplcChaChaVPL,cplcChaChaVPR,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,               & 
& cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHpmcHpmVP,          & 
& cplHpmcVWmVP,cplcVWmVPVWm,cplHpmcHpmVPVP,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,              & 
& cplcVWmVPVPVWm3,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,       & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHpmcHpmVZVZ,cplcVWmVWmVZVZ1,      & 
& cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,cplChiChacVWmR,            & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,cplcgAgWmcVWm,  & 
& cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplAhAhcVWmVWm,cplhhhhcVWmVWm,  & 
& cplHpmcHpmcVWmVWm,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,            & 
& cplcHpmVWmVZ,cplcHpmVPVWm,cplHpmcHpmVPVZ,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,              & 
& cplcVWmVPVWmVZ3)

Implicit None 
Real(dp), Intent(in) :: g1,g2,TW,ZP(2,2),vd,vu,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: UM(2,2),UP(2,2),ZN(5,5),ZDL(3,3),ZUL(3,3),ZEL(3,3)

Complex(dp), Intent(out) :: cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),              & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmVP,      & 
& cplcgWpCgWpCVP,cplHpmcHpmVP(2,2),cplHpmcVWmVP(2),cplcVWmVPVWm,cplHpmcHpmVPVP(2,2),     & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ(3,3),cplcChaChaVZL(2,2),     & 
& cplcChaChaVZR(2,2),cplChiChiVZL(5,5),cplChiChiVZR(5,5),cplcFdFdVZL(3,3),               & 
& cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ(3),            & 
& cplHpmcHpmVZ(2,2),cplHpmcVWmVZ(2),cplcVWmVWmVZ,cplAhAhVZVZ(3,3),cplhhhhVZVZ(3,3),      & 
& cplHpmcHpmVZVZ(2,2),cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplAhHpmcVWm(3,2), & 
& cplChiChacVWmL(5,2),cplChiChacVWmR(5,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,      & 
& cplcgWpCgZcVWm,cplhhHpmcVWm(3,2),cplhhcVWmVWm(3),cplAhAhcVWmVWm(3,3),cplhhhhcVWmVWm(3,3),& 
& cplHpmcHpmcVWmVWm(2,2),cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,       & 
& cplcHpmVWmVZ(2),cplcHpmVPVWm(2),cplHpmcHpmVPVZ(2,2),cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,   & 
& cplcVWmVPVWmVZ3

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForVectorBosons'
 
cplcChaChaVPL = 0._dp 
cplcChaChaVPR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVPL(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVPL(gt1,gt2),cplcChaChaVPR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVPL = 0._dp 
cplcFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVPL(gt1,gt2,g1,g2,TW,cplcFdFdVPL(gt1,gt2),cplcFdFdVPR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVPL = 0._dp 
cplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVPL(gt1,gt2,g1,g2,TW,cplcFeFeVPL(gt1,gt2),cplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVPL = 0._dp 
cplcFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVPL(gt1,gt2,g1,g2,TW,cplcFuFuVPL(gt1,gt2),cplcFuFuVPR(gt1,gt2))

 End Do 
End Do 


cplcgWmgWmVP = 0._dp 
Call CouplingcgWmgWmVPL(g2,TW,cplcgWmgWmVP)



cplcgWpCgWpCVP = 0._dp 
Call CouplingcgWpCgWpCVPL(g2,TW,cplcgWpCgWpCVP)



cplHpmcHpmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVP(gt1,gt2))

 End Do 
End Do 


cplHpmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVPL(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVP(gt1))

End Do 


cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmL(g2,TW,cplcVWmVPVWm)



cplHpmcHpmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVPL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVP(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVPVWm1 = 0._dp 
cplcVWmVPVPVWm2 = 0._dp 
cplcVWmVPVPVWm3 = 0._dp 
Call CouplingcVWmVPVPVWmL(g2,TW,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3)



cplAhhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhhhVZL(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplcChaChaVZL = 0._dp 
cplcChaChaVZR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingcChaChaVZL(gt1,gt2,g1,g2,UM,UP,TW,cplcChaChaVZL(gt1,gt2),cplcChaChaVZR(gt1,gt2))

 End Do 
End Do 


cplChiChiVZL = 0._dp 
cplChiChiVZR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
Call CouplingChiChiVZL(gt1,gt2,g1,g2,ZN,TW,cplChiChiVZL(gt1,gt2),cplChiChiVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZL(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZL(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZL(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZL(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplcgWmgWmVZ = 0._dp 
Call CouplingcgWmgWmVZL(g2,TW,cplcgWmgWmVZ)



cplcgWpCgWpCVZ = 0._dp 
Call CouplingcgWpCgWpCVZL(g2,TW,cplcgWpCgWpCVZ)



cplhhVZVZ = 0._dp 
Do gt1 = 1, 3
Call CouplinghhVZVZL(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHpmcHpmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZ(gt1,gt2))

 End Do 
End Do 


cplHpmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpmcVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplHpmcVWmVZ(gt1))

End Do 


cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZL(g2,TW,cplcVWmVWmVZ)



cplAhAhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhVZVZL(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhVZVZL(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVWmVZVZ1 = 0._dp 
cplcVWmVWmVZVZ2 = 0._dp 
cplcVWmVWmVZVZ3 = 0._dp 
Call CouplingcVWmVWmVZVZL(g2,TW,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3)



cplAhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmL(gt1,gt2,g2,ZA,ZP,cplAhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplChiChacVWmL = 0._dp 
cplChiChacVWmR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 2
Call CouplingChiChacVWmL(gt1,gt2,g2,ZN,UM,UP,cplChiChacVWmL(gt1,gt2),cplChiChacVWmR(gt1,gt2))

 End Do 
End Do 


cplcFuFdcVWmL = 0._dp 
cplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdcVWmL(gt1,gt2,g2,ZDL,ZUL,cplcFuFdcVWmL(gt1,gt2),cplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcFvFecVWmL = 0._dp 
cplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFecVWmL(gt1,gt2,g2,ZEL,cplcFvFecVWmL(gt1,gt2),cplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


cplcgWpCgAcVWm = 0._dp 
Call CouplingcgWpCgAcVWmL(g2,TW,cplcgWpCgAcVWm)



cplcgAgWmcVWm = 0._dp 
Call CouplingcgAgWmcVWmL(g2,TW,cplcgAgWmcVWm)



cplcgZgWmcVWm = 0._dp 
Call CouplingcgZgWmcVWmL(g2,TW,cplcgZgWmcVWm)



cplcgWpCgZcVWm = 0._dp 
Call CouplingcgWpCgZcVWmL(g2,TW,cplcgWpCgZcVWm)



cplhhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmL(gt1,gt2,g2,ZH,ZP,cplhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
Call CouplinghhcVWmVWmL(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplAhAhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhcVWmVWmL(gt1,gt2,g2,ZA,cplAhAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhcVWmVWmL(gt1,gt2,g2,ZH,cplhhhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmcVWmVWmL(gt1,gt2,g2,ZP,cplHpmcHpmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplcVWmcVWmVWmVWm1 = 0._dp 
cplcVWmcVWmVWmVWm2 = 0._dp 
cplcVWmcVWmVWmVWm3 = 0._dp 
Call CouplingcVWmcVWmVWmVWmL(g2,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)



cplcHpmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVWmVZ(gt1))

End Do 


cplcHpmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpmVPVWmL(gt1,g1,g2,vd,vu,ZP,TW,cplcHpmVPVWm(gt1))

End Do 


cplHpmcHpmVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVZL(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVWmVZ1 = 0._dp 
cplcVWmVPVWmVZ2 = 0._dp 
cplcVWmVPVWmVZ3 = 0._dp 
Call CouplingcVWmVPVWmVZL(g2,TW,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)



Iname = Iname - 1 
End Subroutine CouplingsForVectorBosons

Subroutine CouplingsForSMfermions(Ye,ZA,ZEL,ZER,ZH,g1,g2,TW,ZP,Yd,ZDL,ZDR,            & 
& g3,Yu,ZUL,ZUR,cplcUFeFeAhL,cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,        & 
& cplcUFeFeVPR,cplcUFeFeVZL,cplcUFeFeVZR,cplcUFeFvHpmL,cplcUFeFvHpmR,cplcUFeFvVWmL,      & 
& cplcUFeFvVWmR,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,        & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFuHpmL,        & 
& cplcUFdFuHpmR,cplcUFdFuVWmL,cplcUFdFuVWmR,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdcHpmL,    & 
& cplcUFuFdcHpmR,cplcUFuFdcVWmL,cplcUFuFdcVWmR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,   & 
& cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR)

Implicit None 
Real(dp), Intent(in) :: ZA(3,3),ZH(3,3),g1,g2,TW,ZP(2,2),g3

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplcUFeFeAhL(3,3,3),cplcUFeFeAhR(3,3,3),cplcUFeFehhL(3,3,3),cplcUFeFehhR(3,3,3),      & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvHpmL(3,3,2),cplcUFeFvHpmR(3,3,2),cplcUFeFvVWmL(3,3),cplcUFeFvVWmR(3,3),       & 
& cplcUFdFdAhL(3,3,3),cplcUFdFdAhR(3,3,3),cplcUFdFdhhL(3,3,3),cplcUFdFdhhR(3,3,3),       & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFuHpmL(3,3,2),cplcUFdFuHpmR(3,3,2),         & 
& cplcUFdFuVWmL(3,3),cplcUFdFuVWmR(3,3),cplcUFuFuAhL(3,3,3),cplcUFuFuAhR(3,3,3),         & 
& cplcUFuFdcHpmL(3,3,2),cplcUFuFdcHpmR(3,3,2),cplcUFuFdcVWmL(3,3),cplcUFuFdcVWmR(3,3),   & 
& cplcUFuFuhhL(3,3,3),cplcUFuFuhhR(3,3,3),cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),           & 
& cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForSMfermions'
 
cplcUFeFeAhL = 0._dp 
cplcUFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFeFeAhL(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcUFeFeAhL(gt1,gt2,gt3)            & 
& ,cplcUFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFeFehhL(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcUFeFehhL(gt1,gt2,gt3)            & 
& ,cplcUFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFeVPL = 0._dp 
cplcUFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFeVPL(gt1,gt2,g1,g2,ZEL,ZER,TW,cplcUFeFeVPL(gt1,gt2),cplcUFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcUFeFeVZL = 0._dp 
cplcUFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFeVZL(gt1,gt2,g1,g2,ZEL,ZER,TW,cplcUFeFeVZL(gt1,gt2),cplcUFeFeVZR(gt1,gt2))

 End Do 
End Do 


cplcUFeFvHpmL = 0._dp 
cplcUFeFvHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFvHpmL(gt1,gt2,gt3,Ye,ZP,cplcUFeFvHpmL(gt1,gt2,gt3),cplcUFeFvHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFvVWmL = 0._dp 
cplcUFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFvVWmL(gt1,gt2,g2,cplcUFeFvVWmL(gt1,gt2),cplcUFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFdFdAhL = 0._dp 
cplcUFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFdFdAhL(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcUFdFdAhL(gt1,gt2,gt3)            & 
& ,cplcUFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFdFdhhL(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcUFdFdhhL(gt1,gt2,gt3)            & 
& ,cplcUFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFdVGL = 0._dp 
cplcUFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdVGL(gt1,gt2,g3,ZDL,ZDR,cplcUFdFdVGL(gt1,gt2),cplcUFdFdVGR(gt1,gt2))

 End Do 
End Do 


cplcUFdFdVPL = 0._dp 
cplcUFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdVPL(gt1,gt2,g1,g2,ZDL,ZDR,TW,cplcUFdFdVPL(gt1,gt2),cplcUFdFdVPR(gt1,gt2))

 End Do 
End Do 


cplcUFdFdVZL = 0._dp 
cplcUFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdVZL(gt1,gt2,g1,g2,ZDL,ZDR,TW,cplcUFdFdVZL(gt1,gt2),cplcUFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcUFdFuHpmL = 0._dp 
cplcUFdFuHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFuHpmL(gt1,gt2,gt3,Yd,Yu,ZP,ZUL,ZUR,cplcUFdFuHpmL(gt1,gt2,gt3)       & 
& ,cplcUFdFuHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFuVWmL = 0._dp 
cplcUFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFuVWmL(gt1,gt2,g2,ZUL,cplcUFdFuVWmL(gt1,gt2),cplcUFdFuVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuAhL = 0._dp 
cplcUFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFuFuAhL(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcUFuFuAhL(gt1,gt2,gt3)            & 
& ,cplcUFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdcHpmL = 0._dp 
cplcUFuFdcHpmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFuFdcHpmL(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,cplcUFuFdcHpmL(gt1,gt2,gt3)     & 
& ,cplcUFuFdcHpmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdcVWmL = 0._dp 
cplcUFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFdcVWmL(gt1,gt2,g2,ZDL,cplcUFuFdcVWmL(gt1,gt2),cplcUFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuhhL = 0._dp 
cplcUFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcUFuFuhhL(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcUFuFuhhL(gt1,gt2,gt3)            & 
& ,cplcUFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFuVGL = 0._dp 
cplcUFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuVGL(gt1,gt2,g3,ZUL,ZUR,cplcUFuFuVGL(gt1,gt2),cplcUFuFuVGR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuVPL = 0._dp 
cplcUFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuVPL(gt1,gt2,g1,g2,ZUL,ZUR,TW,cplcUFuFuVPL(gt1,gt2),cplcUFuFuVPR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuVZL = 0._dp 
cplcUFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuVZL(gt1,gt2,g1,g2,ZUL,ZUR,TW,cplcUFuFuVZL(gt1,gt2),cplcUFuFuVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForSMfermions

Subroutine CouplingsForTadpoles(g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,TW,              & 
& UM,UP,ZN,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,ZP,cplAhAhUhh,cplAhUhhhh,cplAhUhhVZ,         & 
& cplcChaChaUhhL,cplcChaChaUhhR,cplChiChiUhhL,cplChiChiUhhR,cplcFdFdUhhL,cplcFdFdUhhR,   & 
& cplcFeFeUhhL,cplcFeFeUhhR,cplcFuFuUhhL,cplcFuFuUhhR,cplcgWmgWmUhh,cplcgWpCgWpCUhh,     & 
& cplcgZgZUhh,cplUhhhhhh,cplUhhHpmcHpm,cplUhhHpmcVWm,cplUhhcVWmVWm,cplUhhVZVZ,           & 
& cplAhAhUhhUhh,cplUhhUhhhhhh,cplUhhUhhHpmcHpm,cplUhhUhhcVWmVWm,cplUhhUhhVZVZ)

Implicit None 
Real(dp), Intent(in) :: g1,g2,vd,vu,vS,ZA(3,3),ZH(3,3),TW,ZP(2,2)

Complex(dp), Intent(in) :: lam,Tlam,kap,Tk,UM(2,2),UP(2,2),ZN(5,5),Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),            & 
& ZEL(3,3),ZER(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhUhh(3,3,3),cplAhUhhhh(3,3,3),cplAhUhhVZ(3,3),cplcChaChaUhhL(2,2,3),            & 
& cplcChaChaUhhR(2,2,3),cplChiChiUhhL(5,5,3),cplChiChiUhhR(5,5,3),cplcFdFdUhhL(3,3,3),   & 
& cplcFdFdUhhR(3,3,3),cplcFeFeUhhL(3,3,3),cplcFeFeUhhR(3,3,3),cplcFuFuUhhL(3,3,3),       & 
& cplcFuFuUhhR(3,3,3),cplcgWmgWmUhh(3),cplcgWpCgWpCUhh(3),cplcgZgZUhh(3),cplUhhhhhh(3,3,3),& 
& cplUhhHpmcHpm(3,2,2),cplUhhHpmcVWm(3,2),cplUhhcVWmVWm(3),cplUhhVZVZ(3),cplAhAhUhhUhh(3,3,3,3),& 
& cplUhhUhhhhhh(3,3,3,3),cplUhhUhhHpmcHpm(3,3,2,2),cplUhhUhhcVWmVWm(3,3),cplUhhUhhVZVZ(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForTadpoles'
 
cplAhAhUhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhAhUhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZA,cplAhAhUhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingAhUhhhhL(gt1,gt2,gt3,lam,Tlam,kap,Tk,vd,vu,vS,ZH,ZA,cplAhUhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhUhhVZL(gt1,gt2,g1,g2,ZA,TW,cplAhUhhVZ(gt1,gt2))

 End Do 
End Do 


cplcChaChaUhhL = 0._dp 
cplcChaChaUhhR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcChaChaUhhL(gt1,gt2,gt3,g2,lam,UM,UP,cplcChaChaUhhL(gt1,gt2,gt3)         & 
& ,cplcChaChaUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiChiUhhL = 0._dp 
cplChiChiUhhR = 0._dp 
Do gt1 = 1, 5
 Do gt2 = 1, 5
  Do gt3 = 1, 3
Call CouplingChiChiUhhL(gt1,gt2,gt3,g1,g2,lam,kap,ZN,cplChiChiUhhL(gt1,gt2,gt3)       & 
& ,cplChiChiUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdUhhL = 0._dp 
cplcFdFdUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFdFdUhhL(gt1,gt2,gt3,Yd,ZDL,ZDR,cplcFdFdUhhL(gt1,gt2,gt3)               & 
& ,cplcFdFdUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeUhhL = 0._dp 
cplcFeFeUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFeFeUhhL(gt1,gt2,gt3,Ye,ZEL,ZER,cplcFeFeUhhL(gt1,gt2,gt3)               & 
& ,cplcFeFeUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuUhhL = 0._dp 
cplcFuFuUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcFuFuUhhL(gt1,gt2,gt3,Yu,ZUL,ZUR,cplcFuFuUhhL(gt1,gt2,gt3)               & 
& ,cplcFuFuUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgWmgWmUhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWmgWmUhhL(gt3,g2,vd,vu,cplcgWmgWmUhh(gt3))

End Do 


cplcgWpCgWpCUhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgWpCgWpCUhhL(gt3,g2,vd,vu,cplcgWpCgWpCUhh(gt3))

End Do 


cplcgZgZUhh = 0._dp 
Do gt3 = 1, 3
Call CouplingcgZgZUhhL(gt3,g1,g2,vd,vu,TW,cplcgZgZUhh(gt3))

End Do 


cplUhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingUhhhhhhL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,Tk,vd,vu,vS,ZH,cplUhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUhhHpmcHpmL(gt1,gt2,gt3,g1,g2,lam,Tlam,kap,vd,vu,vS,ZP,cplUhhHpmcHpm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHpmcVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingUhhHpmcVWmL(gt1,gt2,g2,ZP,cplUhhHpmcVWm(gt1,gt2))

 End Do 
End Do 


cplUhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
Call CouplingUhhcVWmVWmL(gt1,g2,vd,vu,cplUhhcVWmVWm(gt1))

End Do 


cplUhhVZVZ = 0._dp 
Do gt1 = 1, 3
Call CouplingUhhVZVZL(gt1,g1,g2,vd,vu,TW,cplUhhVZVZ(gt1))

End Do 


cplAhAhUhhUhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhUhhUhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,cplAhAhUhhUhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhhhhh = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingUhhUhhhhhhL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,cplUhhUhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhHpmcHpm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUhhUhhHpmcHpmL(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZP,cplUhhUhhHpmcHpm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhcVWmVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUhhUhhcVWmVWmL(gt1,gt2,g2,cplUhhUhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUhhUhhVZVZ = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingUhhUhhVZVZL(gt1,gt2,g1,g2,TW,cplUhhUhhVZVZ(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForTadpoles

Subroutine CouplingsColoredQuartics(g1,g2,lam,kap,ZA,ZH,ZP,TW,g3,cplAhAhAhAh1,        & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHpmcHpm1,cplAhhhhhhh1,cplAhhhHpmcHpm1,cplhhhhhhhh1,   & 
& cplhhhhHpmcHpm1,cplHpmHpmcHpmcHpm1,cplAhAhcVWmVWm1,cplAhAhVZVZ1,cplAhHpmcVWmVP1,       & 
& cplAhHpmcVWmVZ1,cplAhcHpmVPVWm1,cplAhcHpmVWmVZ1,cplhhhhcVWmVWm1,cplhhhhVZVZ1,          & 
& cplhhHpmcVWmVP1,cplhhHpmcVWmVZ1,cplhhcHpmVPVWm1,cplhhcHpmVWmVZ1,cplHpmcHpmVPVP1,       & 
& cplHpmcHpmVPVZ1,cplHpmcHpmcVWmVWm1,cplHpmcHpmVZVZ1,cplVGVGVGVG1Q,cplVGVGVGVG2Q,        & 
& cplVGVGVGVG3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWmVZ1Q,     & 
& cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,             & 
& cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q)

Implicit None 
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZH(3,3),ZP(2,2),TW,g3

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: cplAhAhAhAh1(3,3,3,3),cplAhAhAhhh1(3,3,3,3),cplAhAhhhhh1(3,3,3,3),cplAhAhHpmcHpm1(3,3,2,2),& 
& cplAhhhhhhh1(3,3,3,3),cplAhhhHpmcHpm1(3,3,2,2),cplhhhhhhhh1(3,3,3,3),cplhhhhHpmcHpm1(3,3,2,2),& 
& cplHpmHpmcHpmcHpm1(2,2,2,2),cplAhAhcVWmVWm1(3,3),cplAhAhVZVZ1(3,3),cplAhHpmcVWmVP1(3,2),& 
& cplAhHpmcVWmVZ1(3,2),cplAhcHpmVPVWm1(3,2),cplAhcHpmVWmVZ1(3,2),cplhhhhcVWmVWm1(3,3),   & 
& cplhhhhVZVZ1(3,3),cplhhHpmcVWmVP1(3,2),cplhhHpmcVWmVZ1(3,2),cplhhcHpmVPVWm1(3,2),      & 
& cplhhcHpmVWmVZ1(3,2),cplHpmcHpmVPVP1(2,2),cplHpmcHpmVPVZ1(2,2),cplHpmcHpmcVWmVWm1(2,2),& 
& cplHpmcHpmVZVZ1(2,2),cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWmVPVPVWm1Q,       & 
& cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,  & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ1Q,          & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsColoredQuartics'
 
cplAhAhAhAh1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhAhQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,cplAhAhAhAh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhAhhhQ(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhAhAhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhAhhhhhQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZA,cplAhAhhhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHpmcHpm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHpmcHpmQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,ZP,cplAhAhHpmcHpm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplingAhhhhhhhQ(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,cplAhhhhhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHpmcHpm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHpmcHpmQ(gt1,gt2,gt3,gt4,g2,lam,kap,ZH,ZA,ZP,cplAhhhHpmcHpm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 3
   Do gt4 = 1, 3
Call CouplinghhhhhhhhQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,cplhhhhhhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHpmcHpm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHpmcHpmQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZP,cplhhhhHpmcHpm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHpmHpmcHpmcHpm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpmHpmcHpmcHpmQ(gt1,gt2,gt3,gt4,g1,g2,lam,ZP,cplHpmHpmcHpmcHpm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhcVWmVWm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhcVWmVWmQ(gt1,gt2,g2,ZA,cplAhAhcVWmVWm1(gt1,gt2))

 End Do 
End Do 


cplAhAhVZVZ1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingAhAhVZVZQ(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ1(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWmVP1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmVPQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHpmcVWmVP1(gt1,gt2))

 End Do 
End Do 


cplAhHpmcVWmVZ1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhHpmcVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHpmcVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplAhcHpmVPVWm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcHpmVPVWmQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHpmVPVWm1(gt1,gt2))

 End Do 
End Do 


cplAhcHpmVWmVZ1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplingAhcHpmVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHpmVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhcVWmVWmQ(gt1,gt2,g2,ZH,cplhhhhcVWmVWm1(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplinghhhhVZVZQ(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ1(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWmVP1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmVPQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHpmcVWmVP1(gt1,gt2))

 End Do 
End Do 


cplhhHpmcVWmVZ1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhHpmcVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHpmcVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVPVWm1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcHpmVPVWmQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHpmVPVWm1(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVWmVZ1 = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
Call CouplinghhcHpmVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHpmVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVPVP1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVPQ(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVP1(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVPVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVPVZQ(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVPVZ1(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmcVWmVWm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmcVWmVWmQ(gt1,gt2,g2,ZP,cplHpmcHpmcVWmVWm1(gt1,gt2))

 End Do 
End Do 


cplHpmcHpmVZVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpmcHpmVZVZQ(gt1,gt2,g1,g2,ZP,TW,cplHpmcHpmVZVZ1(gt1,gt2))

 End Do 
End Do 


cplVGVGVGVG1Q = 0._dp 
cplVGVGVGVG2Q = 0._dp 
cplVGVGVGVG3Q = 0._dp 
Call CouplingVGVGVGVGQ(g3,cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q)



cplcVWmVPVPVWm1Q = 0._dp 
cplcVWmVPVPVWm2Q = 0._dp 
cplcVWmVPVPVWm3Q = 0._dp 
Call CouplingcVWmVPVPVWmQ(g2,TW,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q)



cplcVWmVPVWmVZ1Q = 0._dp 
cplcVWmVPVWmVZ2Q = 0._dp 
cplcVWmVPVWmVZ3Q = 0._dp 
Call CouplingcVWmVPVWmVZQ(g2,TW,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q)



cplcVWmcVWmVWmVWm1Q = 0._dp 
cplcVWmcVWmVWmVWm2Q = 0._dp 
cplcVWmcVWmVWmVWm3Q = 0._dp 
Call CouplingcVWmcVWmVWmVWmQ(g2,cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,              & 
& cplcVWmcVWmVWmVWm3Q)



cplcVWmVWmVZVZ1Q = 0._dp 
cplcVWmVWmVZVZ2Q = 0._dp 
cplcVWmVWmVZVZ3Q = 0._dp 
Call CouplingcVWmVWmVZVZQ(g2,TW,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q)



Iname = Iname - 1 
End Subroutine CouplingsColoredQuartics

Subroutine CouplingAhAhAhAhQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(-3*g1**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res1 = res1+(-3*g2**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res1 = res1+(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,1))
res1 = res1+(g1**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1+(g1**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,1))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,1))/2._dp
res1 = res1+(g1**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1+(g1**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1+(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res1 = res1+(-3*g1**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res1 = res1+(-3*g2**2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,2))
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZA(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,2)*ZA(gt4,3))
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,3)*ZA(gt4,3))
res1 = res1-6*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,3)*ZA(gt4,3)

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAhQ  
 
 
Subroutine CouplingAhAhAhhhQ(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZA(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZA(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,3)*ZH(gt4,3))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhhQ  
 
 
Subroutine CouplingAhAhhhhhQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1-(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1+(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1-(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
res1 = res1-(lam*Conjg(kap)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
res1 = res1-2*kap*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZH(gt3,3)*ZH(gt4,3)

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhhQ  
 
 
Subroutine CouplingAhAhHpmcHpmQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1-(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1+(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1-(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+kap*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+lam*Conjg(kap)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,1)*ZP(gt4,2)
res1 = res1+(g1**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(g2**2*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(g1**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(g2**2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,3)*ZA(gt2,3)*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHpmcHpmQ  
 
 
Subroutine CouplingAhhhhhhhQ(gt1,gt2,gt3,gt4,lam,kap,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(3,3),ZA(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhhQ  
 
 
Subroutine CouplingAhhhHpmcHpmQ(gt1,gt2,gt3,gt4,g2,lam,kap,ZH,ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g2,ZH(3,3),ZA(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(g2**2*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+kap*Conjg(lam)*ZA(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1)
res1 = res1-(g2**2*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1+(lam*Conjg(lam)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(g2**2*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1+(lam*Conjg(lam)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam*Conjg(kap)*ZA(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHpmcHpmQ  
 
 
Subroutine CouplinghhhhhhhhQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(-3*g1**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1+(-3*g2**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1+(g1**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1+(g2**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1+(g1**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res1 = res1+(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1+(g1**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res1 = res1+(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,1))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,1))/2._dp
res1 = res1+(g1**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res1 = res1+(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1+(g1**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res1 = res1+(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(g1**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1+(g2**2*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1+(-3*g1**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1+(-3*g2**2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,2))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,2))
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,1)*ZH(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,3)*ZH(gt3,2)*ZH(gt4,3))
res1 = res1-(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))
res1 = res1+(lam*Conjg(kap)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(lam*Conjg(kap)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1+(kap*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))/2._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,3)*ZH(gt4,3))
res1 = res1-6*kap*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZH(gt3,3)*ZH(gt4,3)

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhQ  
 
 
Subroutine CouplinghhhhHpmcHpmQ(gt1,gt2,gt3,gt4,g1,g2,lam,kap,ZH,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2)

Complex(dp), Intent(in) :: lam,kap

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1-(g2**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1+(g1**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1-(g2**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(kap*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(g2**2*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1+(lam*Conjg(lam)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(g2**2*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1+(lam*Conjg(lam)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam*Conjg(kap)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1+(g1**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(g2**2*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(g1**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(g2**2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZH(gt1,3)*ZH(gt2,3)*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpmcHpmQ  
 
 
Subroutine CouplingHpmHpmcHpmcHpmQ(gt1,gt2,gt3,gt4,g1,g2,lam,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: g1,g2,ZP(2,2)

Complex(dp), Intent(in) :: lam

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmHpmcHpmcHpm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

If ((gt4.Lt.1).Or.(gt4.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt4 out of range', gt4 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt4 out of range', gt4 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1**2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/2._dp
res1 = res1-(g2**2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1))/2._dp
res1 = res1+(g1**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1+(g2**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1+(g1**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1+(g2**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/4._dp
res1 = res1-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1+(g1**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1+(g2**2*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1+(g1**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1+(g2**2*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/4._dp
res1 = res1-(lam*Conjg(lam)*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(g1**2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/2._dp
res1 = res1-(g2**2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingHpmHpmcHpmcHpmQ  
 
 
Subroutine CouplingAhAhcVWmVWmQ(gt1,gt2,g2,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(3,3)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhcVWmVWmQ  
 
 
Subroutine CouplingAhAhVZVZQ(gt1,gt2,g1,g2,ZA,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,1)*ZA(gt2,1)
res1 = res1+(g1**2*Sin(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res1 = res1+(g2**2*Cos(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,2)*ZA(gt2,2)
res1 = res1+(g1**2*Sin(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhVZVZQ  
 
 
Subroutine CouplingAhHpmcVWmVPQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcVWmVPQ  
 
 
Subroutine CouplingAhHpmcVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHpmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhHpmcVWmVZQ  
 
 
Subroutine CouplingAhcHpmVPVWmQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHpmVPVWmQ  
 
 
Subroutine CouplingAhcHpmVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHpmVWmVZQ  
 
 
Subroutine CouplinghhhhcVWmVWmQ(gt1,gt2,g2,ZH,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(3,3)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res1 = res1+(g2**2*ZH(gt1,2)*ZH(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWmVWmQ  
 
 
Subroutine CouplinghhhhVZVZQ(gt1,gt2,g1,g2,ZH,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,1)*ZH(gt2,1)
res1 = res1+(g1**2*Sin(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res1 = res1+(g2**2*Cos(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,2)*ZH(gt2,2)
res1 = res1+(g1**2*Sin(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZQ  
 
 
Subroutine CouplinghhHpmcVWmVPQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcVWmVPQ  
 
 
Subroutine CouplinghhHpmcVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpmcVWmVZQ  
 
 
Subroutine CouplinghhcHpmVPVWmQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpmVPVWmQ  
 
 
Subroutine CouplinghhcHpmVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(3,3),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpmVWmVZQ  
 
 
Subroutine CouplingHpmcHpmVPVPQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVPVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1**2*Cos(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,1)*ZP(gt2,1)
res1 = res1+(g2**2*Sin(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1**2*Cos(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,2)*ZP(gt2,2)
res1 = res1+(g2**2*Sin(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPVPQ  
 
 
Subroutine CouplingHpmcHpmVPVZQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVPVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Cos(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1**2*Sin(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/4._dp
res1 = res1+(g2**2*Sin(2._dp*(TW))*ZP(gt1,1)*ZP(gt2,1))/4._dp
res1 = res1+(g1*g2*Cos(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/2._dp
res1 = res1-(g1**2*Sin(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/4._dp
res1 = res1+(g2**2*Sin(2._dp*(TW))*ZP(gt1,2)*ZP(gt2,2))/4._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVPVZQ  
 
 
Subroutine CouplingHpmcHpmcVWmVWmQ(gt1,gt2,g2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g2**2*ZP(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmcVWmVWmQ  
 
 
Subroutine CouplingHpmcHpmVZVZQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpmcHpmVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))
res1 = res1+(g1**2*Sin(TW)**2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g2**2*Cos(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res1 = res1-(g1*g2*Cos(TW)*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))
res1 = res1+(g1**2*Sin(TW)**2*ZP(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingHpmcHpmVZVZQ  
 
 
Subroutine CouplingVGVGVGVGQ(g3,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g3

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingVGVGVGVG' 
 
res1 = 0._dp 
res1 = res1-16*g3**2

 
res2 = 0._dp 
res2 = -(0.,1.)*res2 
 
res3 = 0._dp 
res3 = res3+16*g3**2

 


Iname = Iname - 1 
 
End Subroutine CouplingVGVGVGVGQ  
 
 
Subroutine CouplingcVWmVPVPVWmQ(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVPVWm' 
 
res1 = 0._dp 
res1 = res1+g2**2*Sin(TW)**2

 
res2 = 0._dp 
res2 = res2+g2**2*Sin(TW)**2

 
res3 = 0._dp 
res3 = res3-2*g2**2*Sin(TW)**2

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVPVWmQ  
 
 
Subroutine CouplingcVWmVPVWmVZQ(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVPVWmVZ' 
 
res1 = 0._dp 
res1 = res1+g2**2*Cos(TW)*Sin(TW)

 
res2 = 0._dp 
res2 = res2-(g2**2*Sin(2._dp*(TW)))

 
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)*Sin(TW)

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVPVWmVZQ  
 
 
Subroutine CouplingcVWmcVWmVWmVWmQ(g2,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmcVWmVWmVWm' 
 
res1 = 0._dp 
res1 = res1+2*g2**2

 
res2 = 0._dp 
res2 = res2-g2**2

 
res3 = 0._dp 
res3 = res3-g2**2

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmcVWmVWmVWmQ  
 
 
Subroutine CouplingcVWmVWmVZVZQ(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWmVWmVZVZ' 
 
res1 = 0._dp 
res1 = res1-2*g2**2*Cos(TW)**2

 
res2 = 0._dp 
res2 = res2+g2**2*Cos(TW)**2

 
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)**2

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWmVWmVZVZQ  
 
 
End Module Couplings_NMSSMEFT 
