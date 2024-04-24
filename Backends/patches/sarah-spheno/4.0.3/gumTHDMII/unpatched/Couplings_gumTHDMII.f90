! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:22 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Couplings_gumTHDMII
 
Use Control 
Use Settings 
Use Model_Data_gumTHDMII 
Use Mathematics, Only: CompareMatrices, Adjungate 
 
Contains 
 
 Subroutine AllCouplingsReallyAll(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,             & 
& g1,g2,TW,g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,            & 
& cplAhHmcHm,cplhhhhhh,cplhhHmcHm,cplAhAhAhAh,cplAhAhAhhh,cplAhAhhhhh,cplAhAhHmcHm,      & 
& cplAhhhhhhh,cplAhhhHmcHm,cplhhhhhhhh,cplhhhhHmcHm,cplHmHmcHmcHm,cplAhhhVZ,             & 
& cplAhHmcVWm,cplAhcHmVWm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplhhcVWmVWm,    & 
& cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcHmVWmVZ,cplAhAhcVWmVWm,              & 
& cplAhAhVZVZ,cplAhHmcVWmVP,cplAhHmcVWmVZ,cplAhcHmVPVWm,cplAhcHmVWmVZ,cplhhhhcVWmVWm,    & 
& cplhhhhVZVZ,cplhhHmcVWmVP,cplhhHmcVWmVZ,cplhhcHmVPVWm,cplhhcHmVWmVZ,cplHmcHmVPVP,      & 
& cplHmcHmVPVZ,cplHmcHmcVWmVWm,cplHmcHmVZVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,         & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,             & 
& cplcFeFvHmL,cplcFeFvHmR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,           & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,           & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFvVZL,cplcFvFvVZR,cplVGVGVGVG1,cplVGVGVGVG2,           & 
& cplVGVGVGVG3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWmVZ1,          & 
& cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,& 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplcgGgGVG,cplcgWmgAVWm,               & 
& cplcgWpCgAcVWm,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgWpCVP,   & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWpCgWpCVZ,cplcgWmgZVWm,cplcgWpCgZcVWm,cplcgWmgWmAh,   & 
& cplcgWpCgWpCAh,cplcgZgAhh,cplcgWmgAHm,cplcgWpCgAcHm,cplcgWmgWmhh,cplcgZgWmcHm,         & 
& cplcgWpCgWpChh,cplcgZgWpCHm,cplcgZgZhh,cplcgWmgZHm,cplcgWpCgZcHm)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),ZP(2,2),g1,g2,TW,g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhhhhh(2,2,2),cplAhHmcHm(2,2,2),cplhhhhhh(2,2,2),& 
& cplhhHmcHm(2,2,2),cplAhAhAhAh(2,2,2,2),cplAhAhAhhh(2,2,2,2),cplAhAhhhhh(2,2,2,2),      & 
& cplAhAhHmcHm(2,2,2,2),cplAhhhhhhh(2,2,2,2),cplAhhhHmcHm(2,2,2,2),cplhhhhhhhh(2,2,2,2), & 
& cplhhhhHmcHm(2,2,2,2),cplHmHmcHmcHm(2,2,2,2),cplAhhhVZ(2,2),cplAhHmcVWm(2,2),          & 
& cplAhcHmVWm(2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),cplHmcHmVP(2,2),cplHmcHmVZ(2,2),    & 
& cplhhcVWmVWm(2),cplhhVZVZ(2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplcHmVPVWm(2),             & 
& cplcHmVWmVZ(2),cplAhAhcVWmVWm(2,2),cplAhAhVZVZ(2,2),cplAhHmcVWmVP(2,2),cplAhHmcVWmVZ(2,2),& 
& cplAhcHmVPVWm(2,2),cplAhcHmVWmVZ(2,2),cplhhhhcVWmVWm(2,2),cplhhhhVZVZ(2,2),            & 
& cplhhHmcVWmVP(2,2),cplhhHmcVWmVZ(2,2),cplhhcHmVPVWm(2,2),cplhhcHmVWmVZ(2,2),           & 
& cplHmcHmVPVP(2,2),cplHmcHmVPVZ(2,2),cplHmcHmcVWmVWm(2,2),cplHmcHmVZVZ(2,2),            & 
& cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),             & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),         & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),               & 
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
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplcgZgAhh(2),cplcgWmgAHm(2),cplcgWpCgAcHm(2),       & 
& cplcgWmgWmhh(2),cplcgZgWmcHm(2),cplcgWpCgWpChh(2),cplcgZgWpCHm(2),cplcgZgZhh(2),       & 
& cplcgWmgZHm(2),cplcgWpCgZcHm(2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'AllCouplingsReallyAll'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhAhT(gt1,gt2,gt3,lam5,vd,vu,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhhhhhT(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHmcHmT(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,cplAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhhhhhT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHmcHmT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,               & 
& cplhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhAhT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhhhT(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhAhAhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhhhhhT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHmcHmT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,ZP,               & 
& cplAhAhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhhhhhT(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHmcHmT(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,cplAhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhhhhhT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHmcHmT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZP,               & 
& cplhhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHmHmcHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHmHmcHmcHmT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplHmHmcHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplAhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmT(gt1,gt2,g2,ZA,ZP,cplAhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplAhcHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHmVWmT(gt1,gt2,g2,ZA,ZP,cplAhcHmVWm(gt1,gt2))

 End Do 
End Do 


cplhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmT(gt1,gt2,g2,ZH,ZP,cplhhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHmVWmT(gt1,gt2,g2,ZH,ZP,cplhhcHmVWm(gt1,gt2))

 End Do 
End Do 


cplHmcHmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVP(gt1,gt2))

 End Do 
End Do 


cplHmcHmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZ(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVPT(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVP(gt1))

End Do 


cplHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVZ(gt1))

End Do 


cplcHmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVPVWmT(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVPVWm(gt1))

End Do 


cplcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVWmVZ(gt1))

End Do 


cplAhAhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhcVWmVWmT(gt1,gt2,g2,ZA,cplAhAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplAhAhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhVZVZT(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplAhHmcVWmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmVPT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHmcVWmVP(gt1,gt2))

 End Do 
End Do 


cplAhHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHmcVWmVZ(gt1,gt2))

 End Do 
End Do 


cplAhcHmVPVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHmVPVWmT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHmVPVWm(gt1,gt2))

 End Do 
End Do 


cplAhcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHmVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHmVWmVZ(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhcVWmVWmT(gt1,gt2,g2,ZH,cplhhhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhVZVZT(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplhhHmcVWmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmVPT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHmcVWmVP(gt1,gt2))

 End Do 
End Do 


cplhhHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHmcVWmVZ(gt1,gt2))

 End Do 
End Do 


cplhhcHmVPVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHmVPVWmT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHmVPVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHmVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHmVWmVZ(gt1,gt2))

 End Do 
End Do 


cplHmcHmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVPT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVP(gt1,gt2))

 End Do 
End Do 


cplHmcHmVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVZT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVZ(gt1,gt2))

 End Do 
End Do 


cplHmcHmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmcVWmVWmT(gt1,gt2,g2,ZP,cplHmcHmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplHmcHmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZVZT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZVZ(gt1,gt2))

 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVGT(g3,cplVGVGVG)



cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmT(g2,TW,cplcVWmVPVWm)



cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZT(g2,TW,cplcVWmVWmVZ)



cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHmL = 0._dp 
cplcFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHmT(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHmL(gt1,gt2,gt3) & 
& ,cplcFuFdcHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHmL = 0._dp 
cplcFvFecHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHmL(gt1,gt2,gt3),               & 
& cplcFvFecHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHmL = 0._dp 
cplcFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHmT(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHmL(gt1,gt2,gt3)   & 
& ,cplcFdFuHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHmL = 0._dp 
cplcFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHmL(gt1,gt2,gt3),cplcFeFvHmR(gt1,gt2,gt3))

  End Do 
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
Do gt3 = 1, 2
Call CouplingcgWmgWmAhT(gt3,g2,vd,vu,ZA,cplcgWmgWmAh(gt3))

End Do 


cplcgWpCgWpCAh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgWpCAhT(gt3,g2,vd,vu,ZA,cplcgWpCgWpCAh(gt3))

End Do 


cplcgZgAhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgAhhT(gt3,g1,g2,vd,vu,ZH,TW,cplcgZgAhh(gt3))

End Do 


cplcgWmgAHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgAHmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWmgAHm(gt3))

End Do 


cplcgWpCgAcHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgAcHmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWpCgAcHm(gt3))

End Do 


cplcgWmgWmhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgWmhhT(gt3,g2,vd,vu,ZH,cplcgWmgWmhh(gt3))

End Do 


cplcgZgWmcHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWmcHmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgZgWmcHm(gt3))

End Do 


cplcgWpCgWpChh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgWpChhT(gt3,g2,vd,vu,ZH,cplcgWpCgWpChh(gt3))

End Do 


cplcgZgWpCHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWpCHmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgZgWpCHm(gt3))

End Do 


cplcgZgZhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgZhhT(gt3,g1,g2,vd,vu,ZH,TW,cplcgZgZhh(gt3))

End Do 


cplcgWmgZHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgZHmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWmgZHm(gt3))

End Do 


cplcgWpCgZcHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgZcHmT(gt3,g1,g2,vd,vu,ZP,TW,cplcgWpCgZcHm(gt3))

End Do 


Iname = Iname - 1 
End Subroutine AllCouplingsReallyAll

Subroutine AllCouplings(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,g1,g2,TW,             & 
& g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,          & 
& cplhhhhhh,cplhhHmcHm,cplAhhhVZ,cplAhHmcVWm,cplAhcHmVWm,cplhhHmcVWm,cplhhcHmVWm,        & 
& cplHmcHmVP,cplHmcHmVZ,cplhhcVWmVWm,cplhhVZVZ,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,      & 
& cplcHmVWmVZ,cplVGVGVG,cplcVWmVPVWm,cplcVWmVWmVZ,cplcFdFdAhL,cplcFdFdAhR,               & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,           & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,               & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,           & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFvFvVZL,cplcFvFvVZR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),ZP(2,2),g1,g2,TW,g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhhhhh(2,2,2),cplAhHmcHm(2,2,2),cplhhhhhh(2,2,2),& 
& cplhhHmcHm(2,2,2),cplAhhhVZ(2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplhhHmcVWm(2,2),   & 
& cplhhcHmVWm(2,2),cplHmcHmVP(2,2),cplHmcHmVZ(2,2),cplhhcVWmVWm(2),cplhhVZVZ(2),         & 
& cplHmcVWmVP(2),cplHmcVWmVZ(2),cplcHmVPVWm(2),cplcHmVWmVZ(2),cplVGVGVG,cplcVWmVPVWm,    & 
& cplcVWmVWmVZ,cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),& 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),           & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),         & 
& cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),         & 
& cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),           & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFeFeVPL(3,3),               & 
& cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),& 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),& 
& cplcFvFvVZL(3,3),cplcFvFvVZR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'AllCouplings'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhAhT(gt1,gt2,gt3,lam5,vd,vu,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhhhhhT(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHmcHmT(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,cplAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhhhhhT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHmcHmT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,               & 
& cplhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplAhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmT(gt1,gt2,g2,ZA,ZP,cplAhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplAhcHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHmVWmT(gt1,gt2,g2,ZA,ZP,cplAhcHmVWm(gt1,gt2))

 End Do 
End Do 


cplhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmT(gt1,gt2,g2,ZH,ZP,cplhhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHmVWmT(gt1,gt2,g2,ZH,ZP,cplhhcHmVWm(gt1,gt2))

 End Do 
End Do 


cplHmcHmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVP(gt1,gt2))

 End Do 
End Do 


cplHmcHmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZT(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZ(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CouplinghhVZVZT(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVPT(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVP(gt1))

End Do 


cplHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVZ(gt1))

End Do 


cplcHmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVPVWmT(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVPVWm(gt1))

End Do 


cplcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVWmVZ(gt1))

End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVGT(g3,cplVGVGVG)



cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmT(g2,TW,cplcVWmVPVWm)



cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZT(g2,TW,cplcVWmVWmVZ)



cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)              & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAhT(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)              & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAhT(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)              & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)              & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHmL = 0._dp 
cplcFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHmT(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHmL(gt1,gt2,gt3) & 
& ,cplcFuFdcHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)              & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHmL = 0._dp 
cplcFvFecHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHmL(gt1,gt2,gt3),               & 
& cplcFvFecHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)              & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHmL = 0._dp 
cplcFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHmT(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHmL(gt1,gt2,gt3)   & 
& ,cplcFdFuHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHmL = 0._dp 
cplcFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHmT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHmL(gt1,gt2,gt3),cplcFeFvHmR(gt1,gt2,gt3))

  End Do 
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

Subroutine CouplingAhAhAhT(gt1,gt2,gt3,lam5,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
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

res = 0._dp 
res = res+(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhT  
 
 
Subroutine CouplingAhAhhhT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
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

res = 0._dp 
res = res-(lam1*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(lam2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhT  
 
 
Subroutine CouplingAhhhhhT(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
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

res = 0._dp 
res = res-(lam5*vu*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(vu*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(lam5*vd*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhT  
 
 
Subroutine CouplingAhHmcHmT(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcHm' 
 
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

res = 0._dp 
res = res-(lam4*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vu*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcHmT  
 
 
Subroutine CouplinghhhhhhT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
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

res = 0._dp 
res = res-3*lam1*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res = res-(lam3*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam4*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam4*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam5*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-3*lam2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhT  
 
 
Subroutine CouplinghhHmcHmT(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,               & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcHm' 
 
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

res = 0._dp 
res = res-(lam1*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam3*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res = res-(lam2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcHmT  
 
 
Subroutine CouplingAhAhAhAhT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
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
res = res-3*lam1*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1)
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res = res-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res = res-(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res = res-3*lam2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAhT  
 
 
Subroutine CouplingAhAhAhhhT(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
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
res = res-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhhT  
 
 
Subroutine CouplingAhAhhhhhT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
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
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res+(lam5*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhhT  
 
 
Subroutine CouplingAhAhHmcHmT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,               & 
& ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHmcHm' 
 
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
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHmcHmT  
 
 
Subroutine CouplingAhhhhhhhT(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
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
res = res-(lam5*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhhT  
 
 
Subroutine CouplingAhhhHmcHmT(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHmcHm' 
 
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
res = res+(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHmcHmT  
 
 
Subroutine CouplinghhhhhhhhT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
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
res = res-3*lam1*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1)
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam5*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam4*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam5*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-3*lam2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhT  
 
 
Subroutine CouplinghhhhHmcHmT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,               & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHmcHm' 
 
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
res = res-(lam1*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHmcHmT  
 
 
Subroutine CouplingHmHmcHmcHmT(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmHmcHmcHm' 
 
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
res = res-2*lam1*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res = res-2*lam5*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-2*Conjg(lam5)*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res = res-2*lam2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmHmcHmcHmT  
 
 
Subroutine CouplingAhhhVZT(gt1,gt2,g1,g2,ZH,ZA,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZA(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhVZ' 
 
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
res = res+(g2*Cos(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g1*Sin(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2*Cos(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(g1*Sin(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhVZT  
 
 
Subroutine CouplingAhHmcVWmT(gt1,gt2,g2,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcVWm' 
 
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
res = res-(g2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcVWmT  
 
 
Subroutine CouplingAhcHmVWmT(gt1,gt2,g2,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHmVWm' 
 
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
res = res-(g2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHmVWmT  
 
 
Subroutine CouplinghhHmcVWmT(gt1,gt2,g2,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcVWm' 
 
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
res = res+(g2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcVWmT  
 
 
Subroutine CouplinghhcHmVWmT(gt1,gt2,g2,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHmVWm' 
 
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
res = res-(g2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHmVWmT  
 
 
Subroutine CouplingHmcHmVPT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVP' 
 
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
 
End Subroutine CouplingHmcHmVPT  
 
 
Subroutine CouplingHmcHmVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVZ' 
 
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
 
End Subroutine CouplingHmcHmVZT  
 
 
Subroutine CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
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
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
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
 
 
Subroutine CouplingHmcVWmVPT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmcVWmVPT  
 
 
Subroutine CouplingHmcVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmcVWmVZT  
 
 
Subroutine CouplingcHmVPVWmT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHmVPVWmT  
 
 
Subroutine CouplingcHmVWmVZT(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHmVWmVZT  
 
 
Subroutine CouplingAhAhcVWmVWmT(gt1,gt2,g2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhcVWmVWm' 
 
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
Real(dp), Intent(in) :: g1,g2,ZA(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhVZVZ' 
 
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
 
 
Subroutine CouplingAhHmcVWmVPT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcVWmVP' 
 
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
res = res-(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcVWmVPT  
 
 
Subroutine CouplingAhHmcVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcVWmVZ' 
 
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
res = res+(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcVWmVZT  
 
 
Subroutine CouplingAhcHmVPVWmT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHmVPVWm' 
 
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
res = res+(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHmVPVWmT  
 
 
Subroutine CouplingAhcHmVWmVZT(gt1,gt2,g1,g2,ZA,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHmVWmVZ' 
 
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
res = res-(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHmVWmVZT  
 
 
Subroutine CouplinghhhhcVWmVWmT(gt1,gt2,g2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWmVWm' 
 
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
Real(dp), Intent(in) :: g1,g2,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
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
 
 
Subroutine CouplinghhHmcVWmVPT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcVWmVP' 
 
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
res = res+(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcVWmVPT  
 
 
Subroutine CouplinghhHmcVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcVWmVZ' 
 
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
res = res-(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcVWmVZT  
 
 
Subroutine CouplinghhcHmVPVWmT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHmVPVWm' 
 
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
res = res+(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHmVPVWmT  
 
 
Subroutine CouplinghhcHmVWmVZT(gt1,gt2,g1,g2,ZH,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHmVWmVZ' 
 
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
res = res-(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHmVWmVZT  
 
 
Subroutine CouplingHmcHmVPVPT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVPVP' 
 
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
 
End Subroutine CouplingHmcHmVPVPT  
 
 
Subroutine CouplingHmcHmVPVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVPVZ' 
 
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
 
End Subroutine CouplingHmcHmVPVZT  
 
 
Subroutine CouplingHmcHmcVWmVWmT(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmcVWmVWm' 
 
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
 
End Subroutine CouplingHmcHmcVWmVWmT  
 
 
Subroutine CouplingHmcHmVZVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVZVZ' 
 
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
 
End Subroutine CouplingHmcHmVZVZT  
 
 
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
 
 
Subroutine CouplingcFdFdAhT(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL+(Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZA(gt3,2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcFdFdhhT(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhhT  
 
 
Subroutine CouplingcFuFdcHmT(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcHm' 
 
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
resL = resL+Conjg(ZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZUL(gt1,j2)*ZP(gt3,1))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcHmT  
 
 
Subroutine CouplingcFeFehhT(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehhT  
 
 
Subroutine CouplingcFvFecHmT(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecHm' 
 
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
resR = resR-(Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1))
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecHmT  
 
 
Subroutine CouplingcFuFuhhT(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhhT  
 
 
Subroutine CouplingcFdFuHmT(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuHm' 
 
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
resL = resL-(Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZDL(gt1,j2)*ZP(gt3,2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuHmT  
 
 
Subroutine CouplingcFeFvHmT(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvHm' 
 
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
resL = resL-(Conjg(ZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvHmT  
 
 
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
Real(dp), Intent(in) :: g2,vd,vu,ZA(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmAh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*RXiWm*ZA(gt3,1))/4._dp
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
Real(dp), Intent(in) :: g2,vd,vu,ZA(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpCAh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*RXiWm*ZA(gt3,1))/4._dp
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
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgAhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
 
Subroutine CouplingcgWmgAHmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgAHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res-(g2**2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g1*g2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res-(g2**2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgAHmT  
 
 
Subroutine CouplingcgWpCgAcHmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgAcHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res-(g2**2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g1*g2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res-(g2**2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgAcHmT  
 
 
Subroutine CouplingcgWmgWmhhT(gt3,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgWmhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
 
Subroutine CouplingcgZgWmcHmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWmcHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*Cos(TW)*RXiZ*ZP(gt3,1))/4._dp
res = res+(g1*g2*vd*RXiZ*Sin(TW)*ZP(gt3,1))/4._dp
res = res+(g2**2*vu*Cos(TW)*RXiZ*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiZ*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWmcHmT  
 
 
Subroutine CouplingcgWpCgWpChhT(gt3,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g2,vd,vu,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgWpChh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
 
Subroutine CouplingcgZgWpCHmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpCHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*Cos(TW)*RXiZ*ZP(gt3,1))/4._dp
res = res+(g1*g2*vd*RXiZ*Sin(TW)*ZP(gt3,1))/4._dp
res = res+(g2**2*vu*Cos(TW)*RXiZ*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiZ*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpCHmT  
 
 
Subroutine CouplingcgZgZhhT(gt3,g1,g2,vd,vu,ZH,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgZhh' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
 
Subroutine CouplingcgWmgZHmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgZHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res+(g1*g2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g2**2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgZHmT  
 
 
Subroutine CouplingcgWpCgZcHmT(gt3,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgZcHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*vd*Cos(TW)*RXiWm*ZP(gt3,1))/4._dp
res = res+(g1*g2*vd*RXiWm*Sin(TW)*ZP(gt3,1))/4._dp
res = res-(g2**2*vu*Cos(TW)*RXiWm*ZP(gt3,2))/4._dp
res = res+(g1*g2*vu*RXiWm*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgZcHmT  
 
 
Subroutine CouplingsForEffPot4(lam5,lam1,lam4,lam3,lam2,ZA,ZH,ZP,cplAhAhAhAh,         & 
& cplAhAhhhhh,cplAhAhHmcHm,cplhhhhhhhh,cplhhhhHmcHm,cplHmHmcHmcHm)

Implicit None 
Real(dp), Intent(in) :: ZA(2,2),ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: cplAhAhAhAh(2,2,2,2),cplAhAhhhhh(2,2,2,2),cplAhAhHmcHm(2,2,2,2),cplhhhhhhhh(2,2,2,2), & 
& cplhhhhHmcHm(2,2,2,2),cplHmHmcHmcHm(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForEffPot4'
 
cplAhAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhAh2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhhhhh2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,               & 
& cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHmcHm2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,ZP,              & 
& cplAhAhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call Couplinghhhhhhhh2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHmcHm2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZP,              & 
& cplhhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHmHmcHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHmHmcHmcHm2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplHmHmcHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForEffPot4

Subroutine CouplingsForEffPot3(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,               & 
& g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,          & 
& cplhhhhhh,cplhhHmcHm,cplVGVGVG,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFuFuVGL,cplcFuFuVGR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),ZP(2,2),g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhhhhh(2,2,2),cplAhHmcHm(2,2,2),cplhhhhhh(2,2,2),& 
& cplhhHmcHm(2,2,2),cplVGVGVG,cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),  & 
& cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdhhL(3,3,2),           & 
& cplcFdFdhhR(3,3,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFeFehhL(3,3,2),         & 
& cplcFeFehhR(3,3,2),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFuFuhhL(3,3,2),         & 
& cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFeFvHmL(3,3,2),           & 
& cplcFeFvHmR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForEffPot3'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhAh2L(gt1,gt2,gt3,lam5,vd,vu,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhh2L(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,               & 
& cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhhhhh2L(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHmcHm2L(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,cplAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call Couplinghhhhhh2L(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHmcHm2L(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,              & 
& cplhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVG2L(g3,cplVGVGVG)



cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAh2L(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)             & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAh2L(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)             & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAh2L(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)             & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhh2L(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)             & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHmL = 0._dp 
cplcFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHm2L(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehh2L(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)             & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHmL = 0._dp 
cplcFvFecHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHm2L(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHmL(gt1,gt2,gt3)               & 
& ,cplcFvFecHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhh2L(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)             & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHmL = 0._dp 
cplcFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHm2L(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHmL(gt1,gt2,gt3)  & 
& ,cplcFdFuHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHmL = 0._dp 
cplcFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHm2L(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHmL(gt1,gt2,gt3),cplcFeFvHmR(gt1,gt2,gt3))

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

Subroutine CouplingAhAhAhAh2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
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
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-3*lam1*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1)
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-3*lam2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAh2L  
 
 
Subroutine CouplingAhAhhhhh2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,               & 
& ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
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
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam5*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhh2L  
 
 
Subroutine CouplingAhAhHmcHm2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,              & 
& ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHmcHm' 
 
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
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHmcHm2L  
 
 
Subroutine Couplinghhhhhhhh2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
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
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-3*lam1*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1)
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-3*lam2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhhhh2L  
 
 
Subroutine CouplinghhhhHmcHm2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,              & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHmcHm' 
 
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
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam1*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
End If 
If ((gt1.eq.gt2).And.(gt3.eq.gt4)) Then 
res = res-(lam2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHmcHm2L  
 
 
Subroutine CouplingHmHmcHmcHm2L(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmHmcHmcHm' 
 
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
res = res-2*lam1*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-2*lam5*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-2*Conjg(lam5)*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-2*lam2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmHmcHmcHm2L  
 
 
Subroutine CouplingAhAhAh2L(gt1,gt2,gt3,lam5,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
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

res = 0._dp 
res = res+(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAh2L  
 
 
Subroutine CouplingAhAhhh2L(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,               & 
& ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
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

res = 0._dp 
res = res-(lam1*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(lam2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhh2L  
 
 
Subroutine CouplingAhhhhh2L(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
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

res = 0._dp 
res = res-(lam5*vu*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(vu*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(lam5*vd*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhh2L  
 
 
Subroutine CouplingAhHmcHm2L(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcHm' 
 
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

res = 0._dp 
res = res-(lam4*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vu*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcHm2L  
 
 
Subroutine Couplinghhhhhh2L(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
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

res = 0._dp 
res = res-3*lam1*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res = res-(lam3*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam4*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam4*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam5*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-3*lam2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhh2L  
 
 
Subroutine CouplinghhHmcHm2L(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,              & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcHm' 
 
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

res = 0._dp 
res = res-(lam1*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam3*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res = res-(lam2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcHm2L  
 
 
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
 
 
Subroutine CouplingcFdFdAh2L(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL+(Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZA(gt3,2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcFdFdhh2L(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhh2L  
 
 
Subroutine CouplingcFuFdcHm2L(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcHm' 
 
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
resL = resL+Conjg(ZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZUL(gt1,j2)*ZP(gt3,1))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcHm2L  
 
 
Subroutine CouplingcFeFehh2L(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehh2L  
 
 
Subroutine CouplingcFvFecHm2L(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecHm' 
 
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
resR = resR-(Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1))
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecHm2L  
 
 
Subroutine CouplingcFuFuhh2L(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhh2L  
 
 
Subroutine CouplingcFdFuHm2L(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuHm' 
 
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
resL = resL-(Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZDL(gt1,j2)*ZP(gt3,2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuHm2L  
 
 
Subroutine CouplingcFeFvHm2L(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvHm' 
 
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
resL = resL-(Conjg(ZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvHm2L  
 
 
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
 
 
Subroutine CouplingsFor2LPole3(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,               & 
& g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,          & 
& cplhhhhhh,cplhhHmcHm,cplVGVGVG,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFecHmL,cplcFvFecHmR,cplcFuFuhhL,cplcFuFuhhR,             & 
& cplcFdFuHmL,cplcFdFuHmR,cplcFeFvHmL,cplcFeFvHmR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFuFuVGL,cplcFuFuVGR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),ZP(2,2),g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhhhhh(2,2,2),cplAhHmcHm(2,2,2),cplhhhhhh(2,2,2),& 
& cplhhHmcHm(2,2,2),cplVGVGVG,cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),  & 
& cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdhhL(3,3,2),           & 
& cplcFdFdhhR(3,3,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFeFehhL(3,3,2),         & 
& cplcFeFehhR(3,3,2),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFuFuhhL(3,3,2),         & 
& cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFeFvHmL(3,3,2),           & 
& cplcFeFvHmR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsFor2LPole3'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhAh2LP(gt1,gt2,gt3,lam5,vd,vu,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhh2LP(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,              & 
& cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhhhhh2LP(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHmcHm2LP(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,cplAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call Couplinghhhhhh2LP(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHmcHm2LP(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,             & 
& cplhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVG2LP(g3,cplVGVGVG)



cplcFdFdAhL = 0._dp 
cplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdAh2LP(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcFdFdAhL(gt1,gt2,gt3)            & 
& ,cplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeAhL = 0._dp 
cplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeAh2LP(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcFeFeAhL(gt1,gt2,gt3)            & 
& ,cplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuAhL = 0._dp 
cplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuAh2LP(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcFuFuAhL(gt1,gt2,gt3)            & 
& ,cplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdhh2LP(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,cplcFdFdhhL(gt1,gt2,gt3)            & 
& ,cplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFdcHmL = 0._dp 
cplcFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcHm2LP(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdcHmL(gt1,gt2,gt3)& 
& ,cplcFuFdcHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFehh2LP(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,cplcFeFehhL(gt1,gt2,gt3)            & 
& ,cplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecHmL = 0._dp 
cplcFvFecHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecHm2LP(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFecHmL(gt1,gt2,gt3)              & 
& ,cplcFvFecHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuhh2LP(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,cplcFuFuhhL(gt1,gt2,gt3)            & 
& ,cplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFuHmL = 0._dp 
cplcFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFuHm2LP(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFuHmL(gt1,gt2,gt3) & 
& ,cplcFdFuHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvHmL = 0._dp 
cplcFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvHm2LP(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvHmL(gt1,gt2,gt3),               & 
& cplcFeFvHmR(gt1,gt2,gt3))

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

Subroutine CouplingAhAhAh2LP(gt1,gt2,gt3,lam5,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
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

res = 0._dp 
res = res+(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAh2LP  
 
 
Subroutine CouplingAhAhhh2LP(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,              & 
& ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
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

res = 0._dp 
res = res-(lam1*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(lam2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhh2LP  
 
 
Subroutine CouplingAhhhhh2LP(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
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

res = 0._dp 
res = res-(lam5*vu*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(vu*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(lam5*vd*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhh2LP  
 
 
Subroutine CouplingAhHmcHm2LP(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcHm' 
 
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

res = 0._dp 
res = res-(lam4*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam5*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vu*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcHm2LP  
 
 
Subroutine Couplinghhhhhh2LP(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
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

res = 0._dp 
res = res-3*lam1*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res = res-(lam3*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam4*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam4*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam5*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-3*lam2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhh2LP  
 
 
Subroutine CouplinghhHmcHm2LP(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,             & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcHm' 
 
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

res = 0._dp 
res = res-(lam1*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam3*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam3*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res = res-(lam2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcHm2LP  
 
 
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
 
 
Subroutine CouplingcFdFdAh2LP(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL+(Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZA(gt3,2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcFdFdhh2LP(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhh2LP  
 
 
Subroutine CouplingcFuFdcHm2LP(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcHm' 
 
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
resL = resL+Conjg(ZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZUL(gt1,j2)*ZP(gt3,1))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcHm2LP  
 
 
Subroutine CouplingcFeFehh2LP(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehh2LP  
 
 
Subroutine CouplingcFvFecHm2LP(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecHm' 
 
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
resR = resR-(Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1))
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecHm2LP  
 
 
Subroutine CouplingcFuFuhh2LP(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhh2LP  
 
 
Subroutine CouplingcFdFuHm2LP(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFuHm' 
 
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
resL = resL-(Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZDL(gt1,j2)*ZP(gt3,2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFuHm2LP  
 
 
Subroutine CouplingcFeFvHm2LP(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvHm' 
 
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
resL = resL-(Conjg(ZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvHm2LP  
 
 
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
 
 
Subroutine CouplingsFor2LPole4(lam5,lam1,lam4,lam3,lam2,ZA,ZH,ZP,cplAhAhAhAh,         & 
& cplAhAhAhhh,cplAhAhhhhh,cplAhAhHmcHm,cplAhhhhhhh,cplAhhhHmcHm,cplhhhhhhhh,             & 
& cplhhhhHmcHm,cplHmHmcHmcHm)

Implicit None 
Real(dp), Intent(in) :: ZA(2,2),ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: cplAhAhAhAh(2,2,2,2),cplAhAhAhhh(2,2,2,2),cplAhAhhhhh(2,2,2,2),cplAhAhHmcHm(2,2,2,2), & 
& cplAhhhhhhh(2,2,2,2),cplAhhhHmcHm(2,2,2,2),cplhhhhhhhh(2,2,2,2),cplhhhhHmcHm(2,2,2,2), & 
& cplHmHmcHmcHm(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsFor2LPole4'
 
cplAhAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhAh2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhhh2LP(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhAhAhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhhhhh2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,              & 
& cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,ZP,             & 
& cplAhAhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhhhhh2LP(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,cplAhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call Couplinghhhhhhhh2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZP,             & 
& cplhhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHmHmcHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHmHmcHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,               & 
& cplHmHmcHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsFor2LPole4

Subroutine CouplingAhAhAhAh2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
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
res = res-3*lam1*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1)
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res = res-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res = res-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res = res-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res = res-(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res = res-3*lam2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAh2LP  
 
 
Subroutine CouplingAhAhAhhh2LP(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
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
res = res-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhh2LP  
 
 
Subroutine CouplingAhAhhhhh2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,              & 
& ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
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
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res+(lam5*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhh2LP  
 
 
Subroutine CouplingAhAhHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,             & 
& ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHmcHm' 
 
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
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHmcHm2LP  
 
 
Subroutine CouplingAhhhhhhh2LP(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
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
res = res-(lam5*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhh2LP  
 
 
Subroutine CouplingAhhhHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHmcHm' 
 
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
res = res+(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHmcHm2LP  
 
 
Subroutine Couplinghhhhhhhh2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
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
res = res-3*lam1*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1)
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res = res-(lam5*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res = res-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res = res-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam4*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res = res-(lam5*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res = res-3*lam2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhhhh2LP  
 
 
Subroutine CouplinghhhhHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,             & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHmcHm' 
 
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
res = res-(lam1*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHmcHm2LP  
 
 
Subroutine CouplingHmHmcHmcHm2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmHmcHmcHm' 
 
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
res = res-2*lam1*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res = res-2*lam5*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-2*Conjg(lam5)*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res = res-2*lam2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmHmcHmcHm2LP  
 
 
Subroutine CouplingsForLoopMasses(lam5,lam1,lam4,lam3,lam2,vd,vu,ZA,ZH,               & 
& g1,g2,TW,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,ZP,g3,cplAhAhUhh,cplAhUhhhh,cplAhUhhVZ,      & 
& cplcFdFdUhhL,cplcFdFdUhhR,cplcFeFeUhhL,cplcFeFeUhhR,cplcFuFuUhhL,cplcFuFuUhhR,         & 
& cplcgWmgWmUhh,cplcgWpCgWpCUhh,cplcgZgZUhh,cplUhhhhhh,cplUhhHmcHm,cplUhhHmcVWm,         & 
& cplUhhcVWmVWm,cplUhhVZVZ,cplAhAhUhhUhh,cplUhhUhhhhhh,cplUhhUhhHmcHm,cplUhhUhhcVWmVWm,  & 
& cplUhhUhhVZVZ,cplUAhAhAh,cplUAhAhhh,cplcFdFdUAhL,cplcFdFdUAhR,cplcFeFeUAhL,            & 
& cplcFeFeUAhR,cplcFuFuUAhL,cplcFuFuUAhR,cplcgWmgWmUAh,cplcgWpCgWpCUAh,cplUAhhhhh,       & 
& cplUAhhhVZ,cplUAhHmcHm,cplUAhHmcVWm,cplUAhUAhAhAh,cplUAhUAhhhhh,cplUAhUAhHmcHm,        & 
& cplUAhUAhcVWmVWm,cplUAhUAhVZVZ,cplAhHmcUHm,cplAhcUHmVWm,cplcFuFdcUHmL,cplcFuFdcUHmR,   & 
& cplcFvFecUHmL,cplcFvFecUHmR,cplcgZgWmcUHm,cplcgWmgZUHm,cplcgWpCgZcUHm,cplcgZgWpCUHm,   & 
& cplhhHmcUHm,cplhhcUHmVWm,cplHmcUHmVP,cplHmcUHmVZ,cplcUHmVPVWm,cplcUHmVWmVZ,            & 
& cplAhAhUHmcUHm,cplhhhhUHmcUHm,cplUHmHmcUHmcHm,cplUHmcUHmVPVP,cplUHmcUHmcVWmVWm,        & 
& cplUHmcUHmVZVZ,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,       & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFuHmL,         & 
& cplcUFdFuHmR,cplcUFdFuVWmL,cplcUFdFuVWmR,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdcHmL,      & 
& cplcUFuFdcHmR,cplcUFuFdcVWmL,cplcUFuFdcVWmR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,    & 
& cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeAhL,         & 
& cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,         & 
& cplcUFeFeVZR,cplcUFeFvHmL,cplcUFeFvHmR,cplcUFeFvVWmL,cplcUFeFvVWmR,cplcUFvFecHmL,      & 
& cplcUFvFecHmR,cplcUFvFecVWmL,cplcUFvFecVWmR,cplcUFvFvVZL,cplcUFvFvVZR,cplcFdFdVGL,     & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,    & 
& cplVGVGVGVG3,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcVWmVPVWm,           & 
& cplHmcHmVPVP,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ,cplcFdFdVZL,    & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,               & 
& cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,              & 
& cplcVWmVWmVZ,cplAhAhVZVZ,cplhhhhVZVZ,cplHmcHmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,     & 
& cplcVWmVWmVZVZ3,cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,   & 
& cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcVWmVWm,    & 
& cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,   & 
& cplcVWmcVWmVWmVWm3,cplcHmVWmVZ,cplcHmVPVWm,cplHmcHmVPVZ,cplcVWmVPVWmVZ1,               & 
& cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),g1,g2,TW,ZP(2,2),g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhUhh(2,2,2),cplAhUhhhh(2,2,2),cplAhUhhVZ(2,2),cplcFdFdUhhL(3,3,2),              & 
& cplcFdFdUhhR(3,3,2),cplcFeFeUhhL(3,3,2),cplcFeFeUhhR(3,3,2),cplcFuFuUhhL(3,3,2),       & 
& cplcFuFuUhhR(3,3,2),cplcgWmgWmUhh(2),cplcgWpCgWpCUhh(2),cplcgZgZUhh(2),cplUhhhhhh(2,2,2),& 
& cplUhhHmcHm(2,2,2),cplUhhHmcVWm(2,2),cplUhhcVWmVWm(2),cplUhhVZVZ(2),cplAhAhUhhUhh(2,2,2,2),& 
& cplUhhUhhhhhh(2,2,2,2),cplUhhUhhHmcHm(2,2,2,2),cplUhhUhhcVWmVWm(2,2),cplUhhUhhVZVZ(2,2),& 
& cplUAhAhAh(2,2,2),cplUAhAhhh(2,2,2),cplcFdFdUAhL(3,3,2),cplcFdFdUAhR(3,3,2),           & 
& cplcFeFeUAhL(3,3,2),cplcFeFeUAhR(3,3,2),cplcFuFuUAhL(3,3,2),cplcFuFuUAhR(3,3,2),       & 
& cplcgWmgWmUAh(2),cplcgWpCgWpCUAh(2),cplUAhhhhh(2,2,2),cplUAhhhVZ(2,2),cplUAhHmcHm(2,2,2),& 
& cplUAhHmcVWm(2,2),cplUAhUAhAhAh(2,2,2,2),cplUAhUAhhhhh(2,2,2,2),cplUAhUAhHmcHm(2,2,2,2),& 
& cplUAhUAhcVWmVWm(2,2),cplUAhUAhVZVZ(2,2),cplAhHmcUHm(2,2,2),cplAhcUHmVWm(2,2),         & 
& cplcFuFdcUHmL(3,3,2),cplcFuFdcUHmR(3,3,2),cplcFvFecUHmL(3,3,2),cplcFvFecUHmR(3,3,2),   & 
& cplcgZgWmcUHm(2),cplcgWmgZUHm(2),cplcgWpCgZcUHm(2),cplcgZgWpCUHm(2),cplhhHmcUHm(2,2,2),& 
& cplhhcUHmVWm(2,2),cplHmcUHmVP(2,2),cplHmcUHmVZ(2,2),cplcUHmVPVWm(2),cplcUHmVWmVZ(2),   & 
& cplAhAhUHmcUHm(2,2,2,2),cplhhhhUHmcUHm(2,2,2,2),cplUHmHmcUHmcHm(2,2,2,2),              & 
& cplUHmcUHmVPVP(2,2),cplUHmcUHmcVWmVWm(2,2),cplUHmcUHmVZVZ(2,2),cplcUFdFdAhL(3,3,2),    & 
& cplcUFdFdAhR(3,3,2),cplcUFdFdhhL(3,3,2),cplcUFdFdhhR(3,3,2),cplcUFdFdVGL(3,3),         & 
& cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),               & 
& cplcUFdFdVZR(3,3),cplcUFdFuHmL(3,3,2),cplcUFdFuHmR(3,3,2),cplcUFdFuVWmL(3,3),          & 
& cplcUFdFuVWmR(3,3),cplcUFuFuAhL(3,3,2),cplcUFuFuAhR(3,3,2),cplcUFuFdcHmL(3,3,2),       & 
& cplcUFuFdcHmR(3,3,2),cplcUFuFdcVWmL(3,3),cplcUFuFdcVWmR(3,3),cplcUFuFuhhL(3,3,2),      & 
& cplcUFuFuhhR(3,3,2),cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),             & 
& cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3),cplcUFeFeAhL(3,3,2),             & 
& cplcUFeFeAhR(3,3,2),cplcUFeFehhL(3,3,2),cplcUFeFehhR(3,3,2),cplcUFeFeVPL(3,3),         & 
& cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),cplcUFeFvHmL(3,3,2),             & 
& cplcUFeFvHmR(3,3,2),cplcUFeFvVWmL(3,3),cplcUFeFvVWmR(3,3),cplcUFvFecHmL(3,3,2),        & 
& cplcUFvFecHmR(3,3,2),cplcUFvFecVWmL(3,3),cplcUFvFecVWmR(3,3),cplcUFvFvVZL(3,3),        & 
& cplcUFvFvVZR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3), & 
& cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcFdFdVPL(3,3),          & 
& cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),  & 
& cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcVWmVPVWm,               & 
& cplHmcHmVPVP(2,2),cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ(2,2),      & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),  & 
& cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,        & 
& cplhhVZVZ(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcVWmVWmVZ,cplAhAhVZVZ(2,2),             & 
& cplhhhhVZVZ(2,2),cplHmcHmVZVZ(2,2),cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,    & 
& cplAhHmcVWm(2,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFvFecVWmL(3,3),             & 
& cplcFvFecVWmR(3,3),cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm

Complex(dp), Intent(out) :: cplhhHmcVWm(2,2),cplhhcVWmVWm(2),cplAhAhcVWmVWm(2,2),cplhhhhcVWmVWm(2,2),              & 
& cplHmcHmcVWmVWm(2,2),cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,         & 
& cplcHmVWmVZ(2),cplcHmVPVWm(2),cplHmcHmVPVZ(2,2),cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,       & 
& cplcVWmVPVWmVZ3

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForLoopMasses'
 
cplAhAhUhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhUhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZA,cplAhAhUhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhUhhhhL(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhUhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhUhhVZL(gt1,gt2,g1,g2,ZA,TW,cplAhUhhVZ(gt1,gt2))

 End Do 
End Do 


cplcFdFdUhhL = 0._dp 
cplcFdFdUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdUhhL(gt1,gt2,gt3,Yd,ZDL,ZDR,cplcFdFdUhhL(gt1,gt2,gt3)               & 
& ,cplcFdFdUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeUhhL = 0._dp 
cplcFeFeUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeUhhL(gt1,gt2,gt3,Ye,ZEL,ZER,cplcFeFeUhhL(gt1,gt2,gt3)               & 
& ,cplcFeFeUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuUhhL = 0._dp 
cplcFuFuUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuUhhL(gt1,gt2,gt3,Yu,ZUL,ZUR,cplcFuFuUhhL(gt1,gt2,gt3)               & 
& ,cplcFuFuUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgWmgWmUhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgWmUhhL(gt3,g2,vd,vu,cplcgWmgWmUhh(gt3))

End Do 


cplcgWpCgWpCUhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgWpCUhhL(gt3,g2,vd,vu,cplcgWpCgWpCUhh(gt3))

End Do 


cplcgZgZUhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgZUhhL(gt3,g1,g2,vd,vu,TW,cplcgZgZUhh(gt3))

End Do 


cplUhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUhhhhhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplUhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUhhHmcHmL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZP,cplUhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUhhHmcVWmL(gt1,gt2,g2,ZP,cplUhhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplUhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingUhhcVWmVWmL(gt1,g2,vd,vu,cplUhhcVWmVWm(gt1))

End Do 


cplUhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingUhhVZVZL(gt1,g1,g2,vd,vu,TW,cplUhhVZVZ(gt1))

End Do 


cplAhAhUhhUhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhUhhUhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhUhhUhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUhhUhhhhhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplUhhUhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUhhUhhHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplUhhUhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUhhUhhcVWmVWmL(gt1,gt2,g2,cplUhhUhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUhhUhhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUhhUhhVZVZL(gt1,gt2,g1,g2,TW,cplUhhUhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplUAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUAhAhAhL(gt1,gt2,gt3,lam5,vd,vu,ZA,cplUAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUAhAhhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,               & 
& cplUAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFdFdUAhL = 0._dp 
cplcFdFdUAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdUAhL(gt1,gt2,gt3,Yd,ZDL,ZDR,cplcFdFdUAhL(gt1,gt2,gt3)               & 
& ,cplcFdFdUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeUAhL = 0._dp 
cplcFeFeUAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeUAhL(gt1,gt2,gt3,Ye,ZEL,ZER,cplcFeFeUAhL(gt1,gt2,gt3)               & 
& ,cplcFeFeUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuUAhL = 0._dp 
cplcFuFuUAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuUAhL(gt1,gt2,gt3,Yu,ZUL,ZUR,cplcFuFuUAhL(gt1,gt2,gt3)               & 
& ,cplcFuFuUAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgWmgWmUAh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgWmUAhL(gt3,g2,vd,vu,cplcgWmgWmUAh(gt3))

End Do 


cplcgWpCgWpCUAh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgWpCUAhL(gt3,g2,vd,vu,cplcgWpCgWpCUAh(gt3))

End Do 


cplUAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUAhhhhhL(gt1,gt2,gt3,lam5,vd,vu,ZH,cplUAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUAhhhVZL(gt1,gt2,g1,g2,ZH,TW,cplUAhhhVZ(gt1,gt2))

 End Do 
End Do 


cplUAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUAhHmcHmL(gt1,gt2,gt3,lam5,lam4,vd,vu,ZP,cplUAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUAhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUAhHmcVWmL(gt1,gt2,g2,ZP,cplUAhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplUAhUAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUAhUAhAhAhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplUAhUAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUAhUAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUAhUAhhhhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplUAhUAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUAhUAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUAhUAhHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplUAhUAhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUAhUAhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUAhUAhcVWmVWmL(gt1,gt2,g2,cplUAhUAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUAhUAhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUAhUAhVZVZL(gt1,gt2,g1,g2,TW,cplUAhUAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplAhHmcUHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHmcUHmL(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,cplAhHmcUHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhcUHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcUHmVWmL(gt1,gt2,g2,ZA,cplAhcUHmVWm(gt1,gt2))

 End Do 
End Do 


cplcFuFdcUHmL = 0._dp 
cplcFuFdcUHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdcUHmL(gt1,gt2,gt3,Yu,Yd,ZDL,ZDR,ZUL,ZUR,cplcFuFdcUHmL(gt1,gt2,gt3)  & 
& ,cplcFuFdcUHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvFecUHmL = 0._dp 
cplcFvFecUHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFecUHmL(gt1,gt2,gt3,Ye,ZER,cplcFvFecUHmL(gt1,gt2,gt3),cplcFvFecUHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgZgWmcUHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWmcUHmL(gt3,g1,g2,vd,vu,TW,cplcgZgWmcUHm(gt3))

End Do 


cplcgWmgZUHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgZUHmL(gt3,g1,g2,vd,vu,TW,cplcgWmgZUHm(gt3))

End Do 


cplcgWpCgZcUHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgZcUHmL(gt3,g1,g2,vd,vu,TW,cplcgWpCgZcUHm(gt3))

End Do 


cplcgZgWpCUHm = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWpCUHmL(gt3,g1,g2,vd,vu,TW,cplcgZgWpCUHm(gt3))

End Do 


cplhhHmcUHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHmcUHmL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,              & 
& cplhhHmcUHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhcUHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcUHmVWmL(gt1,gt2,g2,ZH,cplhhcUHmVWm(gt1,gt2))

 End Do 
End Do 


cplHmcUHmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcUHmVPL(gt1,gt2,g1,g2,ZP,TW,cplHmcUHmVP(gt1,gt2))

 End Do 
End Do 


cplHmcUHmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcUHmVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcUHmVZ(gt1,gt2))

 End Do 
End Do 


cplcUHmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcUHmVPVWmL(gt1,g1,g2,vd,vu,TW,cplcUHmVPVWm(gt1))

End Do 


cplcUHmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcUHmVWmVZL(gt1,g1,g2,vd,vu,TW,cplcUHmVWmVZ(gt1))

End Do 


cplAhAhUHmcUHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhUHmcUHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhUHmcUHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhUHmcUHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhUHmcUHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplhhhhUHmcUHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUHmHmcUHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUHmHmcUHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,               & 
& cplUHmHmcUHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUHmcUHmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHmcUHmVPVPL(gt1,gt2,g1,g2,TW,cplUHmcUHmVPVP(gt1,gt2))

 End Do 
End Do 


cplUHmcUHmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHmcUHmcVWmVWmL(gt1,gt2,g2,cplUHmcUHmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUHmcUHmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHmcUHmVZVZL(gt1,gt2,g1,g2,TW,cplUHmcUHmVZVZ(gt1,gt2))

 End Do 
End Do 


cplcUFdFdAhL = 0._dp 
cplcUFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFdAhL(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcUFdFdAhL(gt1,gt2,gt3)            & 
& ,cplcUFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
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


cplcUFdFuHmL = 0._dp 
cplcUFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFuHmL(gt1,gt2,gt3,Yu,Yd,ZP,ZUL,ZUR,cplcUFdFuHmL(gt1,gt2,gt3)         & 
& ,cplcUFdFuHmR(gt1,gt2,gt3))

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
  Do gt3 = 1, 2
Call CouplingcUFuFuAhL(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcUFuFuAhL(gt1,gt2,gt3)            & 
& ,cplcUFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdcHmL = 0._dp 
cplcUFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFuFdcHmL(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,cplcUFuFdcHmL(gt1,gt2,gt3)       & 
& ,cplcUFuFdcHmR(gt1,gt2,gt3))

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
  Do gt3 = 1, 2
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


cplcUFeFeAhL = 0._dp 
cplcUFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFeAhL(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcUFeFeAhL(gt1,gt2,gt3)            & 
& ,cplcUFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
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


cplcUFeFvHmL = 0._dp 
cplcUFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFvHmL(gt1,gt2,gt3,Ye,ZP,cplcUFeFvHmL(gt1,gt2,gt3),cplcUFeFvHmR(gt1,gt2,gt3))

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


cplcUFvFecHmL = 0._dp 
cplcUFvFecHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFvFecHmL(gt1,gt2,gt3,Ye,ZP,ZER,cplcUFvFecHmL(gt1,gt2,gt3)              & 
& ,cplcUFvFecHmR(gt1,gt2,gt3))

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



cplHmcHmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVP(gt1,gt2))

 End Do 
End Do 


cplHmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVPL(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVP(gt1))

End Do 


cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmL(g2,TW,cplcVWmVPVWm)



cplHmcHmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVPL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVP(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVPVWm1 = 0._dp 
cplcVWmVPVPVWm2 = 0._dp 
cplcVWmVPVPVWm3 = 0._dp 
Call CouplingcVWmVPVPVWmL(g2,TW,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3)



cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZL(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

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
Do gt1 = 1, 2
Call CouplinghhVZVZL(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHmcHmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZ(gt1,gt2))

 End Do 
End Do 


cplHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVZ(gt1))

End Do 


cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZL(g2,TW,cplcVWmVWmVZ)



cplAhAhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhVZVZL(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhVZVZL(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplHmcHmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVWmVZVZ1 = 0._dp 
cplcVWmVWmVZVZ2 = 0._dp 
cplcVWmVWmVZVZ3 = 0._dp 
Call CouplingcVWmVWmVZVZL(g2,TW,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3)



cplAhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmL(gt1,gt2,g2,ZA,ZP,cplAhHmcVWm(gt1,gt2))

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



cplhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmL(gt1,gt2,g2,ZH,ZP,cplhhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmL(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplAhAhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhcVWmVWmL(gt1,gt2,g2,ZA,cplAhAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhcVWmVWmL(gt1,gt2,g2,ZH,cplhhhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplHmcHmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmcVWmVWmL(gt1,gt2,g2,ZP,cplHmcHmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplcVWmcVWmVWmVWm1 = 0._dp 
cplcVWmcVWmVWmVWm2 = 0._dp 
cplcVWmcVWmVWmVWm3 = 0._dp 
Call CouplingcVWmcVWmVWmVWmL(g2,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)



cplcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVWmVZ(gt1))

End Do 


cplcHmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVPVWmL(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVPVWm(gt1))

End Do 


cplHmcHmVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVWmVZ1 = 0._dp 
cplcVWmVPVWmVZ2 = 0._dp 
cplcVWmVPVWmVZ3 = 0._dp 
Call CouplingcVWmVPVWmVZL(g2,TW,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)



Iname = Iname - 1 
End Subroutine CouplingsForLoopMasses

Subroutine CouplingAhAhUhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhUhh' 
 
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

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(lam1*vd*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-(lam3*vu*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-(lam4*vu*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res+(lam5*vu*ZA(gt1,1)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam5*vu*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam5*vd*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam5*vu*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam5*vd*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam3*vd*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((1.eq.gt3)) Then 
res = res-(lam4*vd*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((1.eq.gt3)) Then 
res = res+(lam5*vd*ZA(gt1,2)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam2*vu*ZA(gt1,2)*ZA(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhUhhL  
 
 
Subroutine CouplingAhUhhhhL(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhUhhhh' 
 
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

res = 0._dp 
If ((2.eq.gt2)) Then 
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(lam5*vu*ZA(gt1,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(vu*Conjg(lam5)*ZA(gt1,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(lam5*vu*ZA(gt1,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(lam5*vd*ZA(gt1,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(vd*Conjg(lam5)*ZA(gt1,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(lam5*vd*ZA(gt1,2)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt3,2))/2._dp
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
Real(dp), Intent(in) :: g1,g2,ZA(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhUhhVZ' 
 
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
res = res+(g2*Cos(TW)*ZA(gt1,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(g1*Sin(TW)*ZA(gt1,1))/2._dp
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

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2))/sqrt(2._dp))
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

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2))/sqrt(2._dp))
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
resL = resL-((Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2))/sqrt(2._dp))
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
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
 
Subroutine CouplingUhhhhhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhhhhh' 
 
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

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-3*lam1*vd*ZH(gt2,1)*ZH(gt3,1)
End If 
If ((2.eq.gt1)) Then 
res = res-(lam3*vu*ZH(gt2,1)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vu*ZH(gt2,1)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vu*ZH(gt2,1)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZH(gt2,1)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam3*vu*ZH(gt2,2)*ZH(gt3,1))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam4*vu*ZH(gt2,2)*ZH(gt3,1))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vu*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam3*vd*ZH(gt2,2)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vd*ZH(gt2,2)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam3*vu*ZH(gt2,1)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam4*vu*ZH(gt2,1)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vu*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam3*vd*ZH(gt2,1)*ZH(gt3,2))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vd*ZH(gt2,1)*ZH(gt3,2))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam3*vd*ZH(gt2,2)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam4*vd*ZH(gt2,2)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vd*ZH(gt2,2)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZH(gt2,2)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-3*lam2*vu*ZH(gt2,2)*ZH(gt3,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhhhhhL  
 
 
Subroutine CouplingUhhHmcHmL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhHmcHm' 
 
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

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(lam1*vd*ZP(gt2,1)*ZP(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam3*vu*ZP(gt2,1)*ZP(gt3,1))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam4*vu*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vu*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vd*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam4*vu*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vd*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam3*vd*ZP(gt2,2)*ZP(gt3,2))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam2*vu*ZP(gt2,2)*ZP(gt3,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhHmcHmL  
 
 
Subroutine CouplingUhhHmcVWmL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhHmcVWm' 
 
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
If ((1.eq.gt1)) Then 
res = res+(g2*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g2*ZP(gt2,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhHmcVWmL  
 
 
Subroutine CouplingUhhcVWmVWmL(gt1,g2,vd,vu,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
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
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
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
 
 
Subroutine CouplingAhAhUhhUhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhUhhUhh' 
 
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
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(lam5*ZA(gt1,1)*ZA(gt2,1))/2._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res+(lam5*ZA(gt1,2)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2))/2._dp
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhUhhUhhL  
 
 
Subroutine CouplingUhhUhhhhhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhhhhh' 
 
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
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-3*lam1*ZH(gt3,1)*ZH(gt4,1)
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam3*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZH(gt3,2)*ZH(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam3*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZH(gt3,1)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam3*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam4*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam5*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-3*lam2*ZH(gt3,2)*ZH(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhUhhhhhhL  
 
 
Subroutine CouplingUhhUhhHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhHmcHm' 
 
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
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam1*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam2*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUhhUhhHmcHmL  
 
 
Subroutine CouplingUhhUhhcVWmVWmL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhcVWmVWm' 
 
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
 
End Subroutine CouplingUhhUhhcVWmVWmL  
 
 
Subroutine CouplingUhhUhhVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUhhUhhVZVZ' 
 
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
 
 
Subroutine CouplingUAhAhAhL(gt1,gt2,gt3,lam5,vd,vu,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhAhAh' 
 
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

res = 0._dp 
If ((2.eq.gt1)) Then 
res = res+(lam5*vu*ZA(gt2,1)*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt2,1)*ZA(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vu*ZA(gt2,2)*ZA(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt2,2)*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZA(gt2,2)*ZA(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt2,2)*ZA(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vu*ZA(gt2,1)*ZA(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt2,1)*ZA(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZA(gt2,1)*ZA(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt2,1)*ZA(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vd*ZA(gt2,2)*ZA(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt2,2)*ZA(gt3,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhAhAhL  
 
 
Subroutine CouplingUAhAhhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,               & 
& ZH,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhAhhh' 
 
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

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(lam1*vd*ZA(gt2,1)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vu*ZA(gt2,1)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt2,1)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vu*ZA(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam3*vd*ZA(gt2,2)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vd*ZA(gt2,2)*ZH(gt3,1))
End If 
If ((2.eq.gt1)) Then 
res = res+(lam5*vd*ZA(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam3*vu*ZA(gt2,1)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res-(lam4*vu*ZA(gt2,1)*ZH(gt3,2))
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vu*ZA(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(vu*Conjg(lam5)*ZA(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZA(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZA(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(lam5*vd*ZA(gt2,2)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZA(gt2,2)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam2*vu*ZA(gt2,2)*ZH(gt3,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhAhhhL  
 
 
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

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2))/sqrt(2._dp)
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

If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2))/sqrt(2._dp)
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
resL = resL+(Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
End If 
resR = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2))/sqrt(2._dp))
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
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
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
res = res+(g2**2*vu*RXiWm)/4._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgWpCUAhL  
 
 
Subroutine CouplingUAhhhhhL(gt1,gt2,gt3,lam5,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhhhhh' 
 
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

res = 0._dp 
If ((2.eq.gt1)) Then 
res = res-(lam5*vu*ZH(gt2,1)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vu*Conjg(lam5)*ZH(gt2,1)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vu*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZH(gt2,2)*ZH(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vu*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZH(gt2,1)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vd*ZH(gt2,2)*ZH(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vd*Conjg(lam5)*ZH(gt2,2)*ZH(gt3,2))/2._dp
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
Real(dp), Intent(in) :: g1,g2,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhhhVZ' 
 
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
If ((1.eq.gt1)) Then 
res = res+(g2*Cos(TW)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(g1*Sin(TW)*ZH(gt2,1))/2._dp
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
 
 
Subroutine CouplingUAhHmcHmL(gt1,gt2,gt3,lam5,lam4,vd,vu,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhHmcHm' 
 
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

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(lam4*vu*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam5*vu*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(lam4*vd*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam5*vd*ZP(gt2,2)*ZP(gt3,1))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res+(lam4*vu*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((1.eq.gt1)) Then 
res = res-(vu*Conjg(lam5)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(lam4*vd*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(vd*Conjg(lam5)*ZP(gt2,1)*ZP(gt3,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhHmcHmL  
 
 
Subroutine CouplingUAhHmcVWmL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhHmcVWm' 
 
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
 
End Subroutine CouplingUAhHmcVWmL  
 
 
Subroutine CouplingUAhUAhAhAhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhAhAh' 
 
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
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-3*lam1*ZA(gt3,1)*ZA(gt4,1)
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZA(gt3,1)*ZA(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZA(gt3,1)*ZA(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZA(gt3,1)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam3*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZA(gt3,2)*ZA(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZA(gt3,2)*ZA(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam3*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZA(gt3,1)*ZA(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZA(gt3,1)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam3*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam4*ZA(gt3,2)*ZA(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam5*ZA(gt3,2)*ZA(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZA(gt3,2)*ZA(gt4,2))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-3*lam2*ZA(gt3,2)*ZA(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhAhAhL  
 
 
Subroutine CouplingUAhUAhhhhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhhhhh' 
 
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
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam1*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZH(gt3,1)*ZH(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(lam5*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res+(Conjg(lam5)*ZH(gt3,1)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZH(gt3,2)*ZH(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZH(gt3,1)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam3*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam4*ZH(gt3,2)*ZH(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(lam5*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res+(Conjg(lam5)*ZH(gt3,2)*ZH(gt4,2))/2._dp
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam2*ZH(gt3,2)*ZH(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhhhhhL  
 
 
Subroutine CouplingUAhUAhHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhHmcHm' 
 
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
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam1*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam5*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam5*ZP(gt3,2)*ZP(gt4,1))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt2).And.(2.eq.gt1)) Then 
res = res-(Conjg(lam5)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(Conjg(lam5)*ZP(gt3,1)*ZP(gt4,2))/2._dp
End If 
If ((1.eq.gt1).And.(1.eq.gt2)) Then 
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt2)) Then 
res = res-(lam2*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUAhUAhHmcHmL  
 
 
Subroutine CouplingUAhUAhcVWmVWmL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhcVWmVWm' 
 
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
 
End Subroutine CouplingUAhUAhcVWmVWmL  
 
 
Subroutine CouplingUAhUAhVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUAhUAhVZVZ' 
 
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
 
 
Subroutine CouplingAhHmcUHmL(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcUHm' 
 
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

res = 0._dp 
If ((2.eq.gt3)) Then 
res = res+(lam4*vu*ZA(gt1,1)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vu*Conjg(lam5)*ZA(gt1,1)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam4*vd*ZA(gt1,2)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(vd*Conjg(lam5)*ZA(gt1,2)*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam4*vu*ZA(gt1,1)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(lam5*vu*ZA(gt1,1)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(lam4*vd*ZA(gt1,2)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam5*vd*ZA(gt1,2)*ZP(gt2,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcUHmL  
 
 
Subroutine CouplingAhcUHmVWmL(gt1,gt2,g2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcUHmVWm' 
 
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
 
End Subroutine CouplingAhcUHmVWmL  
 
 
Subroutine CouplingcFuFdcUHmL(gt1,gt2,gt3,Yu,Yd,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdcUHm' 
 
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
resL = resL+Conjg(ZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yu(j1,j2)
End Do 
End Do 
End If 
resR = 0._dp 
If ((1.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*ZDR(gt2,j1)*ZUL(gt1,j2))
End Do 
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdcUHmL  
 
 
Subroutine CouplingcFvFecUHmL(gt1,gt2,gt3,Ye,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFecUHm' 
 
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
resR = resR-(Conjg(Ye(j1,gt1))*ZER(gt2,j1))
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFecUHmL  
 
 
Subroutine CouplingcgZgWmcUHmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWmcUHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*Cos(TW)*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g2**2*vu*Cos(TW)*RXiZ)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g1*g2*vd*RXiZ*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiZ*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWmcUHmL  
 
 
Subroutine CouplingcgWmgZUHmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWmgZUHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*Cos(TW)*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*Cos(TW)*RXiWm)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g1*g2*vd*RXiWm*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiWm*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWmgZUHmL  
 
 
Subroutine CouplingcgWpCgZcUHmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpCgZcUHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(g2**2*vd*Cos(TW)*RXiWm)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g2**2*vu*Cos(TW)*RXiWm)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g1*g2*vd*RXiWm*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiWm*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpCgZcUHmL  
 
 
Subroutine CouplingcgZgWpCUHmL(gt3,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpCUHm' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res+(g2**2*vd*Cos(TW)*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g2**2*vu*Cos(TW)*RXiZ)/4._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(g1*g2*vd*RXiZ*Sin(TW))/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(g1*g2*vu*RXiZ*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpCUHmL  
 
 
Subroutine CouplinghhHmcUHmL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,              & 
& ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcUHm' 
 
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

res = 0._dp 
If ((1.eq.gt3)) Then 
res = res-(lam1*vd*ZH(gt1,1)*ZP(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vu*Conjg(lam5)*ZH(gt1,1)*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam3*vu*ZH(gt1,2)*ZP(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(vd*Conjg(lam5)*ZH(gt1,2)*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam4*vu*ZH(gt1,1)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam5*vu*ZH(gt1,1)*ZP(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam3*vd*ZH(gt1,1)*ZP(gt2,2))
End If 
If ((1.eq.gt3)) Then 
res = res-(lam4*vd*ZH(gt1,2)*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam5*vd*ZH(gt1,2)*ZP(gt2,2))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam2*vu*ZH(gt1,2)*ZP(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcUHmL  
 
 
Subroutine CouplinghhcUHmVWmL(gt1,gt2,g2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcUHmVWm' 
 
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
res = res-(g2*ZH(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g2*ZH(gt1,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcUHmVWmL  
 
 
Subroutine CouplingHmcUHmVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcUHmVP' 
 
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
 
End Subroutine CouplingHmcUHmVPL  
 
 
Subroutine CouplingHmcUHmVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcUHmVZ' 
 
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
 
End Subroutine CouplingHmcUHmVZL  
 
 
Subroutine CouplingcUHmVPVWmL(gt1,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUHmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res+(g1*g2*vd*Cos(TW))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res+(g1*g2*vu*Cos(TW))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUHmVPVWmL  
 
 
Subroutine CouplingcUHmVWmVZL(gt1,g1,g2,vd,vu,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUHmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt1)) Then 
res = res-(g1*g2*vd*Sin(TW))/2._dp
End If 
If ((2.eq.gt1)) Then 
res = res-(g1*g2*vu*Sin(TW))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUHmVWmVZL  
 
 
Subroutine CouplingAhAhUHmcUHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhUHmcUHm' 
 
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
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam1*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,1)*ZA(gt2,1))
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam5*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam5*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam4*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam3*ZA(gt1,2)*ZA(gt2,2))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam2*ZA(gt1,2)*ZA(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhUHmcUHmL  
 
 
Subroutine CouplinghhhhUHmcUHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhUHmcUHm' 
 
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
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam1*ZH(gt1,1)*ZH(gt2,1))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,1)*ZH(gt2,1))
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam5*ZH(gt1,2)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,2)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2))/2._dp
End If 
If ((1.eq.gt4).And.(2.eq.gt3)) Then 
res = res-(lam5*ZH(gt1,1)*ZH(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam4*ZH(gt1,1)*ZH(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2))/2._dp
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-(lam3*ZH(gt1,2)*ZH(gt2,2))
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-(lam2*ZH(gt1,2)*ZH(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhUHmcUHmL  
 
 
Subroutine CouplingUHmHmcUHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHmHmcUHmcHm' 
 
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
res = res-2*lam1*ZP(gt2,1)*ZP(gt4,1)
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam3*ZP(gt2,1)*ZP(gt4,1))
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam4*ZP(gt2,1)*ZP(gt4,1))
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res-2*lam5*ZP(gt2,2)*ZP(gt4,1)
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam3*ZP(gt2,2)*ZP(gt4,1))
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam4*ZP(gt2,2)*ZP(gt4,1))
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res-(lam3*ZP(gt2,1)*ZP(gt4,2))
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res-(lam4*ZP(gt2,1)*ZP(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res-2*Conjg(lam5)*ZP(gt2,1)*ZP(gt4,2)
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res-(lam3*ZP(gt2,2)*ZP(gt4,2))
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res-(lam4*ZP(gt2,2)*ZP(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-2*lam2*ZP(gt2,2)*ZP(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUHmHmcUHmcHmL  
 
 
Subroutine CouplingUHmcUHmVPVPL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHmcUHmVPVP' 
 
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
 
End Subroutine CouplingUHmcUHmVPVPL  
 
 
Subroutine CouplingUHmcUHmcVWmVWmL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHmcUHmcVWmVWm' 
 
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
 
End Subroutine CouplingUHmcUHmcVWmVWmL  
 
 
Subroutine CouplingUHmcUHmVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHmcUHmVZVZ' 
 
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
 
End Subroutine CouplingUHmcUHmVZVZL  
 
 
Subroutine CouplingcUFdFdAhL(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZDL(gt2,j2))*Yd(gt1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,gt1))*ZDR(gt2,j1)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZH(2,2)

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
 
 
Subroutine CouplingcUFdFuHmL(gt1,gt2,gt3,Yu,Yd,ZP,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFuHm' 
 
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
resL = resL-(Conjg(ZUL(gt2,j2))*Yd(gt1,j2)*ZP(gt3,1))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,gt1))*ZUR(gt2,j1)*ZP(gt3,2)
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFuHmL  
 
 
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
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL+(Conjg(ZUL(gt2,j2))*Yu(gt1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,gt1))*ZUR(gt2,j1)*ZA(gt3,2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcUFuFdcHmL(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFdcHm' 
 
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
resR = resR-(Conjg(Yd(j1,gt1))*ZDR(gt2,j1)*ZP(gt3,1))
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFdcHmL  
 
 
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
Real(dp), Intent(in) :: ZH(2,2)

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
resL = resL-((Conjg(ZUL(gt2,j2))*Yu(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,gt1))*ZUR(gt2,j1)*ZH(gt3,2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcUFeFeAhL(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2)

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
resL = resL-((Conjg(ZEL(gt2,j2))*Ye(gt1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZA(gt3,1))/sqrt(2._dp)
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
Real(dp), Intent(in) :: ZH(2,2)

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
 
 
Subroutine CouplingcUFeFvHmL(gt1,gt2,gt3,Ye,ZP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFvHm' 
 
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
resL = resL-(Ye(gt1,gt2)*ZP(gt3,1))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFvHmL  
 
 
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
 
 
Subroutine CouplingcUFvFecHmL(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFvFecHm' 
 
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
resR = resR-(Conjg(Ye(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1))
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFvFecHmL  
 
 
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
 
 
Subroutine CouplingHmcHmVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVP' 
 
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
 
End Subroutine CouplingHmcHmVPL  
 
 
Subroutine CouplingHmcVWmVPL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmcVWmVPL  
 
 
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
 
 
Subroutine CouplingHmcHmVPVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVPVP' 
 
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
 
End Subroutine CouplingHmcHmVPVPL  
 
 
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
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZA(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhVZ' 
 
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
res = res+(g2*Cos(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g1*Sin(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2*Cos(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(g1*Sin(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhVZL  
 
 
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
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
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
 
 
Subroutine CouplingHmcHmVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVZ' 
 
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
 
End Subroutine CouplingHmcHmVZL  
 
 
Subroutine CouplingHmcVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHmcVWmVZL  
 
 
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
Real(dp), Intent(in) :: g1,g2,ZA(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhVZVZ' 
 
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
Real(dp), Intent(in) :: g1,g2,ZH(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
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
 
 
Subroutine CouplingHmcHmVZVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVZVZ' 
 
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
 
End Subroutine CouplingHmcHmVZVZL  
 
 
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
 
 
Subroutine CouplingAhHmcVWmL(gt1,gt2,g2,ZA,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcVWm' 
 
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
res = res-(g2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcVWmL  
 
 
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
 
 
Subroutine CouplinghhHmcVWmL(gt1,gt2,g2,ZH,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2),ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcVWm' 
 
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
res = res+(g2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcVWmL  
 
 
Subroutine CouplinghhcVWmVWmL(gt1,g2,vd,vu,ZH,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
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
Real(dp), Intent(in) :: g2,ZA(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhcVWmVWm' 
 
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
Real(dp), Intent(in) :: g2,ZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWmVWm' 
 
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
res = res+(g2**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWmVWmL  
 
 
Subroutine CouplingHmcHmcVWmVWmL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmcVWmVWm' 
 
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
 
End Subroutine CouplingHmcHmcVWmVWmL  
 
 
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
 
 
Subroutine CouplingcHmVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHmVWmVZL  
 
 
Subroutine CouplingcHmVPVWmL(gt1,g1,g2,vd,vu,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHmVPVWmL  
 
 
Subroutine CouplingHmcHmVPVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVPVZ' 
 
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
 
End Subroutine CouplingHmcHmVPVZL  
 
 
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
 
 
Subroutine CouplingsForVectorBosons(g1,g2,TW,ZP,vd,vu,ZH,ZA,ZDL,ZUL,ZEL,              & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,cplcVWmVPVWm,cplHmcHmVPVP,          & 
& cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,     & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVWmVZ,             & 
& cplAhAhVZVZ,cplhhhhVZVZ,cplHmcHmVZVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,  & 
& cplAhHmcVWm,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm,    & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcVWmVWm,cplAhAhcVWmVWm,    & 
& cplhhhhcVWmVWm,cplHmcHmcVWmVWm,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,& 
& cplcHmVWmVZ,cplcHmVPVWm,cplHmcHmVPVZ,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)

Implicit None 
Real(dp), Intent(in) :: g1,g2,TW,ZP(2,2),vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3),ZEL(3,3)

Complex(dp), Intent(out) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3), & 
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

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForVectorBosons'
 
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



cplHmcHmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVP(gt1,gt2))

 End Do 
End Do 


cplHmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVPL(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVP(gt1))

End Do 


cplcVWmVPVWm = 0._dp 
Call CouplingcVWmVPVWmL(g2,TW,cplcVWmVPVWm)



cplHmcHmVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVPL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVP(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVPVWm1 = 0._dp 
cplcVWmVPVPVWm2 = 0._dp 
cplcVWmVPVPVWm3 = 0._dp 
Call CouplingcVWmVPVPVWmL(g2,TW,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3)



cplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhhhVZL(gt1,gt2,g1,g2,ZH,ZA,TW,cplAhhhVZ(gt1,gt2))

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
Do gt1 = 1, 2
Call CouplinghhVZVZL(gt1,g1,g2,vd,vu,ZH,TW,cplhhVZVZ(gt1))

End Do 


cplHmcHmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZ(gt1,gt2))

 End Do 
End Do 


cplHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHmcVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplHmcVWmVZ(gt1))

End Do 


cplcVWmVWmVZ = 0._dp 
Call CouplingcVWmVWmVZL(g2,TW,cplcVWmVWmVZ)



cplAhAhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhVZVZL(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhVZVZL(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ(gt1,gt2))

 End Do 
End Do 


cplHmcHmVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVWmVZVZ1 = 0._dp 
cplcVWmVWmVZVZ2 = 0._dp 
cplcVWmVWmVZVZ3 = 0._dp 
Call CouplingcVWmVWmVZVZL(g2,TW,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3)



cplAhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmL(gt1,gt2,g2,ZA,ZP,cplAhHmcVWm(gt1,gt2))

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



cplhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmL(gt1,gt2,g2,ZH,ZP,cplhhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmL(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplAhAhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhcVWmVWmL(gt1,gt2,g2,ZA,cplAhAhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhcVWmVWmL(gt1,gt2,g2,ZH,cplhhhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplHmcHmcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmcVWmVWmL(gt1,gt2,g2,ZP,cplHmcHmcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplcVWmcVWmVWmVWm1 = 0._dp 
cplcVWmcVWmVWmVWm2 = 0._dp 
cplcVWmcVWmVWmVWm3 = 0._dp 
Call CouplingcVWmcVWmVWmVWmL(g2,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)



cplcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVWmVZL(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVWmVZ(gt1))

End Do 


cplcHmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingcHmVPVWmL(gt1,g1,g2,vd,vu,ZP,TW,cplcHmVPVWm(gt1))

End Do 


cplHmcHmVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVZL(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVZ(gt1,gt2))

 End Do 
End Do 


cplcVWmVPVWmVZ1 = 0._dp 
cplcVWmVPVWmVZ2 = 0._dp 
cplcVWmVPVWmVZ3 = 0._dp 
Call CouplingcVWmVPVWmVZL(g2,TW,cplcVWmVPVWmVZ1,cplcVWmVPVWmVZ2,cplcVWmVPVWmVZ3)



Iname = Iname - 1 
End Subroutine CouplingsForVectorBosons

Subroutine CouplingsForSMfermions(Yd,ZA,ZDL,ZDR,ZH,g3,g1,g2,TW,Yu,ZP,ZUL,             & 
& ZUR,Ye,ZEL,ZER,cplcUFdFdAhL,cplcUFdFdAhR,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,       & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFuHmL,         & 
& cplcUFdFuHmR,cplcUFdFuVWmL,cplcUFdFuVWmR,cplcUFuFuAhL,cplcUFuFuAhR,cplcUFuFdcHmL,      & 
& cplcUFuFdcHmR,cplcUFuFdcVWmL,cplcUFuFdcVWmR,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,    & 
& cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeAhL,         & 
& cplcUFeFeAhR,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,         & 
& cplcUFeFeVZR,cplcUFeFvHmL,cplcUFeFvHmR,cplcUFeFvVWmL,cplcUFeFvVWmR)

Implicit None 
Real(dp), Intent(in) :: ZA(2,2),ZH(2,2),g3,g1,g2,TW,ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplcUFdFdAhL(3,3,2),cplcUFdFdAhR(3,3,2),cplcUFdFdhhL(3,3,2),cplcUFdFdhhR(3,3,2),      & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFuHmL(3,3,2),cplcUFdFuHmR(3,3,2),           & 
& cplcUFdFuVWmL(3,3),cplcUFdFuVWmR(3,3),cplcUFuFuAhL(3,3,2),cplcUFuFuAhR(3,3,2),         & 
& cplcUFuFdcHmL(3,3,2),cplcUFuFdcHmR(3,3,2),cplcUFuFdcVWmL(3,3),cplcUFuFdcVWmR(3,3),     & 
& cplcUFuFuhhL(3,3,2),cplcUFuFuhhR(3,3,2),cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),           & 
& cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3),               & 
& cplcUFeFeAhL(3,3,2),cplcUFeFeAhR(3,3,2),cplcUFeFehhL(3,3,2),cplcUFeFehhR(3,3,2),       & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvHmL(3,3,2),cplcUFeFvHmR(3,3,2),cplcUFeFvVWmL(3,3),cplcUFeFvVWmR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForSMfermions'
 
cplcUFdFdAhL = 0._dp 
cplcUFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFdAhL(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,cplcUFdFdAhL(gt1,gt2,gt3)            & 
& ,cplcUFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
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


cplcUFdFuHmL = 0._dp 
cplcUFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFuHmL(gt1,gt2,gt3,Yu,Yd,ZP,ZUL,ZUR,cplcUFdFuHmL(gt1,gt2,gt3)         & 
& ,cplcUFdFuHmR(gt1,gt2,gt3))

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
  Do gt3 = 1, 2
Call CouplingcUFuFuAhL(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,cplcUFuFuAhL(gt1,gt2,gt3)            & 
& ,cplcUFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdcHmL = 0._dp 
cplcUFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFuFdcHmL(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,cplcUFuFdcHmL(gt1,gt2,gt3)       & 
& ,cplcUFuFdcHmR(gt1,gt2,gt3))

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
  Do gt3 = 1, 2
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


cplcUFeFeAhL = 0._dp 
cplcUFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFeAhL(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,cplcUFeFeAhL(gt1,gt2,gt3)            & 
& ,cplcUFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
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


cplcUFeFvHmL = 0._dp 
cplcUFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFvHmL(gt1,gt2,gt3,Ye,ZP,cplcUFeFvHmL(gt1,gt2,gt3),cplcUFeFvHmR(gt1,gt2,gt3))

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


Iname = Iname - 1 
End Subroutine CouplingsForSMfermions

Subroutine CouplingsForTadpoles(lam5,lam1,lam4,lam3,lam2,vd,vu,ZA,ZH,g1,              & 
& g2,TW,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,ZP,cplAhAhUhh,cplAhUhhhh,cplAhUhhVZ,            & 
& cplcFdFdUhhL,cplcFdFdUhhR,cplcFeFeUhhL,cplcFeFeUhhR,cplcFuFuUhhL,cplcFuFuUhhR,         & 
& cplcgWmgWmUhh,cplcgWpCgWpCUhh,cplcgZgZUhh,cplUhhhhhh,cplUhhHmcHm,cplUhhHmcVWm,         & 
& cplUhhcVWmVWm,cplUhhVZVZ,cplAhAhUhhUhh,cplUhhUhhhhhh,cplUhhUhhHmcHm,cplUhhUhhcVWmVWm,  & 
& cplUhhUhhVZVZ)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),g1,g2,TW,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: cplAhAhUhh(2,2,2),cplAhUhhhh(2,2,2),cplAhUhhVZ(2,2),cplcFdFdUhhL(3,3,2),              & 
& cplcFdFdUhhR(3,3,2),cplcFeFeUhhL(3,3,2),cplcFeFeUhhR(3,3,2),cplcFuFuUhhL(3,3,2),       & 
& cplcFuFuUhhR(3,3,2),cplcgWmgWmUhh(2),cplcgWpCgWpCUhh(2),cplcgZgZUhh(2),cplUhhhhhh(2,2,2),& 
& cplUhhHmcHm(2,2,2),cplUhhHmcVWm(2,2),cplUhhcVWmVWm(2),cplUhhVZVZ(2),cplAhAhUhhUhh(2,2,2,2),& 
& cplUhhUhhhhhh(2,2,2,2),cplUhhUhhHmcHm(2,2,2,2),cplUhhUhhcVWmVWm(2,2),cplUhhUhhVZVZ(2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForTadpoles'
 
cplAhAhUhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhUhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZA,cplAhAhUhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhUhhhhL(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhUhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhUhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhUhhVZL(gt1,gt2,g1,g2,ZA,TW,cplAhUhhVZ(gt1,gt2))

 End Do 
End Do 


cplcFdFdUhhL = 0._dp 
cplcFdFdUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFdUhhL(gt1,gt2,gt3,Yd,ZDL,ZDR,cplcFdFdUhhL(gt1,gt2,gt3)               & 
& ,cplcFdFdUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeUhhL = 0._dp 
cplcFeFeUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFeUhhL(gt1,gt2,gt3,Ye,ZEL,ZER,cplcFeFeUhhL(gt1,gt2,gt3)               & 
& ,cplcFeFeUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuUhhL = 0._dp 
cplcFuFuUhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFuUhhL(gt1,gt2,gt3,Yu,ZUL,ZUR,cplcFuFuUhhL(gt1,gt2,gt3)               & 
& ,cplcFuFuUhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcgWmgWmUhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWmgWmUhhL(gt3,g2,vd,vu,cplcgWmgWmUhh(gt3))

End Do 


cplcgWpCgWpCUhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpCgWpCUhhL(gt3,g2,vd,vu,cplcgWpCgWpCUhh(gt3))

End Do 


cplcgZgZUhh = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgZUhhL(gt3,g1,g2,vd,vu,TW,cplcgZgZUhh(gt3))

End Do 


cplUhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUhhhhhhL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplUhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingUhhHmcHmL(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZP,cplUhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplUhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUhhHmcVWmL(gt1,gt2,g2,ZP,cplUhhHmcVWm(gt1,gt2))

 End Do 
End Do 


cplUhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplingUhhcVWmVWmL(gt1,g2,vd,vu,cplUhhcVWmVWm(gt1))

End Do 


cplUhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingUhhVZVZL(gt1,g1,g2,vd,vu,TW,cplUhhVZVZ(gt1))

End Do 


cplAhAhUhhUhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhUhhUhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhUhhUhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUhhUhhhhhhL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplUhhUhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUhhUhhHmcHmL(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplUhhUhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUhhUhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUhhUhhcVWmVWmL(gt1,gt2,g2,cplUhhUhhcVWmVWm(gt1,gt2))

 End Do 
End Do 


cplUhhUhhVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUhhUhhVZVZL(gt1,gt2,g1,g2,TW,cplUhhUhhVZVZ(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForTadpoles

Subroutine CouplingsColoredQuartics(lam5,lam1,lam4,lam3,lam2,ZA,ZH,ZP,g2,             & 
& g1,TW,g3,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhhhhhhh1,            & 
& cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,cplHmHmcHmcHm1,cplAhAhcVWmVWm1,               & 
& cplAhAhVZVZ1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,              & 
& cplhhhhcVWmVWm1,cplhhhhVZVZ1,cplhhHmcVWmVP1,cplhhHmcVWmVZ1,cplhhcHmVPVWm1,             & 
& cplhhcHmVWmVZ1,cplHmcHmVPVP1,cplHmcHmVPVZ1,cplHmcHmcVWmVWm1,cplHmcHmVZVZ1,             & 
& cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWmVPVPVWm1Q,cplcVWmVPVPVWm2Q,           & 
& cplcVWmVPVPVWm3Q,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,cplcVWmcVWmVWmVWm1Q,& 
& cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ1Q,cplcVWmVWmVZVZ2Q,             & 
& cplcVWmVWmVZVZ3Q)

Implicit None 
Real(dp), Intent(in) :: ZA(2,2),ZH(2,2),ZP(2,2),g2,g1,TW,g3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: cplAhAhAhAh1(2,2,2,2),cplAhAhAhhh1(2,2,2,2),cplAhAhhhhh1(2,2,2,2),cplAhAhHmcHm1(2,2,2,2),& 
& cplAhhhhhhh1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2),cplhhhhhhhh1(2,2,2,2),cplhhhhHmcHm1(2,2,2,2),& 
& cplHmHmcHmcHm1(2,2,2,2),cplAhAhcVWmVWm1(2,2),cplAhAhVZVZ1(2,2),cplAhHmcVWmVP1(2,2),    & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVPVWm1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhcVWmVWm1(2,2),      & 
& cplhhhhVZVZ1(2,2),cplhhHmcVWmVP1(2,2),cplhhHmcVWmVZ1(2,2),cplhhcHmVPVWm1(2,2),         & 
& cplhhcHmVWmVZ1(2,2),cplHmcHmVPVP1(2,2),cplHmcHmVPVZ1(2,2),cplHmcHmcVWmVWm1(2,2),       & 
& cplHmcHmVZVZ1(2,2),cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWmVPVPVWm1Q,         & 
& cplcVWmVPVPVWm2Q,cplcVWmVPVPVWm3Q,cplcVWmVPVWmVZ1Q,cplcVWmVPVWmVZ2Q,cplcVWmVPVWmVZ3Q,  & 
& cplcVWmcVWmVWmVWm1Q,cplcVWmcVWmVWmVWm2Q,cplcVWmcVWmVWmVWm3Q,cplcVWmVWmVZVZ1Q,          & 
& cplcVWmVWmVZVZ2Q,cplcVWmVWmVZVZ3Q

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsColoredQuartics'
 
cplAhAhAhAh1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhAhQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhAhAh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhhhQ(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhAhAhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhhhhhQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,cplAhAhhhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHmcHm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,ZP,               & 
& cplAhAhHmcHm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhhhhhQ(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhhhhhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHmcHm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,cplAhhhHmcHm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhhhhhQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplhhhhhhhh1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHmcHm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZP,               & 
& cplhhhhHmcHm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHmHmcHmcHm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHmHmcHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplHmHmcHmcHm1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhcVWmVWm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhcVWmVWmQ(gt1,gt2,g2,ZA,cplAhAhcVWmVWm1(gt1,gt2))

 End Do 
End Do 


cplAhAhVZVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhAhVZVZQ(gt1,gt2,g1,g2,ZA,TW,cplAhAhVZVZ1(gt1,gt2))

 End Do 
End Do 


cplAhHmcVWmVP1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmVPQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHmcVWmVP1(gt1,gt2))

 End Do 
End Do 


cplAhHmcVWmVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhHmcVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhHmcVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplAhcHmVPVWm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHmVPVWmQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHmVPVWm1(gt1,gt2))

 End Do 
End Do 


cplAhcHmVWmVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHmVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,cplAhcHmVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplhhhhcVWmVWm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhcVWmVWmQ(gt1,gt2,g2,ZH,cplhhhhcVWmVWm1(gt1,gt2))

 End Do 
End Do 


cplhhhhVZVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhhhVZVZQ(gt1,gt2,g1,g2,ZH,TW,cplhhhhVZVZ1(gt1,gt2))

 End Do 
End Do 


cplhhHmcVWmVP1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmVPQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHmcVWmVP1(gt1,gt2))

 End Do 
End Do 


cplhhHmcVWmVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhHmcVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhHmcVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplhhcHmVPVWm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHmVPVWmQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHmVPVWm1(gt1,gt2))

 End Do 
End Do 


cplhhcHmVWmVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHmVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,cplhhcHmVWmVZ1(gt1,gt2))

 End Do 
End Do 


cplHmcHmVPVP1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVPQ(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVP1(gt1,gt2))

 End Do 
End Do 


cplHmcHmVPVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVPVZQ(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVPVZ1(gt1,gt2))

 End Do 
End Do 


cplHmcHmcVWmVWm1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmcVWmVWmQ(gt1,gt2,g2,ZP,cplHmcHmcVWmVWm1(gt1,gt2))

 End Do 
End Do 


cplHmcHmVZVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHmcHmVZVZQ(gt1,gt2,g1,g2,ZP,TW,cplHmcHmVZVZ1(gt1,gt2))

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

Subroutine CouplingAhAhAhAhQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
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
res1 = res1-3*lam1*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1)
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res1 = res1-3*lam2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAhQ  
 
 
Subroutine CouplingAhAhAhhhQ(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
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
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhhQ  
 
 
Subroutine CouplingAhAhhhhhQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
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
res1 = res1-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1+(lam5*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhhQ  
 
 
Subroutine CouplingAhAhHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,               & 
& ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHmcHm' 
 
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
res1 = res1-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res1 = res1-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHmcHmQ  
 
 
Subroutine CouplingAhhhhhhhQ(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
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
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhhQ  
 
 
Subroutine CouplingAhhhHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHmcHm' 
 
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
res1 = res1+(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHmcHmQ  
 
 
Subroutine CouplinghhhhhhhhQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
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
res1 = res1-3*lam1*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1)
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-3*lam2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhQ  
 
 
Subroutine CouplinghhhhHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,               & 
& ZH,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHmcHm' 
 
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
res1 = res1-(lam1*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res1 = res1-(lam2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHmcHmQ  
 
 
Subroutine CouplingHmHmcHmcHmQ(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmHmcHmcHm' 
 
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
res1 = res1-2*lam1*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res1 = res1-2*lam5*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res1 = res1-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-2*Conjg(lam5)*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res1 = res1-2*lam2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplingHmHmcHmcHmQ  
 
 
Subroutine CouplingAhAhcVWmVWmQ(gt1,gt2,g2,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhcVWmVWm' 
 
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
res1 = res1+(g2**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res1 = res1+(g2**2*ZA(gt1,2)*ZA(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhcVWmVWmQ  
 
 
Subroutine CouplingAhAhVZVZQ(gt1,gt2,g1,g2,ZA,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhVZVZ' 
 
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
res1 = res1+(g2**2*Cos(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,1)*ZA(gt2,1)
res1 = res1+(g1**2*Sin(TW)**2*ZA(gt1,1)*ZA(gt2,1))/2._dp
res1 = res1+(g2**2*Cos(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZA(gt1,2)*ZA(gt2,2)
res1 = res1+(g1**2*Sin(TW)**2*ZA(gt1,2)*ZA(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhVZVZQ  
 
 
Subroutine CouplingAhHmcVWmVPQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcVWmVP' 
 
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
res1 = res1-(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcVWmVPQ  
 
 
Subroutine CouplingAhHmcVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcVWmVZ' 
 
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
res1 = res1+(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcVWmVZQ  
 
 
Subroutine CouplingAhcHmVPVWmQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHmVPVWm' 
 
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
res1 = res1+(g1*g2*Cos(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Cos(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHmVPVWmQ  
 
 
Subroutine CouplingAhcHmVWmVZQ(gt1,gt2,g1,g2,ZA,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZA(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhcHmVWmVZ' 
 
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
res1 = res1-(g1*g2*Sin(TW)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Sin(TW)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhcHmVWmVZQ  
 
 
Subroutine CouplinghhhhcVWmVWmQ(gt1,gt2,g2,ZH,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWmVWm' 
 
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
res1 = res1+(g2**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res1 = res1+(g2**2*ZH(gt1,2)*ZH(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWmVWmQ  
 
 
Subroutine CouplinghhhhVZVZQ(gt1,gt2,g1,g2,ZH,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
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
res1 = res1+(g2**2*Cos(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,1)*ZH(gt2,1)
res1 = res1+(g1**2*Sin(TW)**2*ZH(gt1,1)*ZH(gt2,1))/2._dp
res1 = res1+(g2**2*Cos(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,2)*ZH(gt2,2)
res1 = res1+(g1**2*Sin(TW)**2*ZH(gt1,2)*ZH(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZQ  
 
 
Subroutine CouplinghhHmcVWmVPQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcVWmVP' 
 
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
res1 = res1+(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcVWmVPQ  
 
 
Subroutine CouplinghhHmcVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcVWmVZ' 
 
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
res1 = res1-(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcVWmVZQ  
 
 
Subroutine CouplinghhcHmVPVWmQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHmVPVWm' 
 
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
res1 = res1+(g1*g2*Cos(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1+(g1*g2*Cos(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHmVPVWmQ  
 
 
Subroutine CouplinghhcHmVWmVZQ(gt1,gt2,g1,g2,ZH,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHmVWmVZ' 
 
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
res1 = res1-(g1*g2*Sin(TW)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res1 = res1-(g1*g2*Sin(TW)*ZH(gt1,2)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHmVWmVZQ  
 
 
Subroutine CouplingHmcHmVPVPQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVPVP' 
 
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
 
End Subroutine CouplingHmcHmVPVPQ  
 
 
Subroutine CouplingHmcHmVPVZQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVPVZ' 
 
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
 
End Subroutine CouplingHmcHmVPVZQ  
 
 
Subroutine CouplingHmcHmcVWmVWmQ(gt1,gt2,g2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmcVWmVWm' 
 
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
 
End Subroutine CouplingHmcHmcVWmVWmQ  
 
 
Subroutine CouplingHmcHmVZVZQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmcHmVZVZ' 
 
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
 
End Subroutine CouplingHmcHmVZVZQ  
 
 
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
 
 
Subroutine CouplingsColourStructures(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,               & 
& ZH,ZP,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHmcHm,cplhhhhhh,cplhhHmcHm,cplAhAhAhAh,       & 
& cplAhAhAhhh,cplAhAhhhhh,cplAhAhHmcHm,cplAhhhhhhh,cplAhhhHmcHm,cplhhhhhhhh,             & 
& cplhhhhHmcHm,cplHmHmcHmcHm)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplAhhhhh(2,2,2),cplAhHmcHm(2,2,2),cplhhhhhh(2,2,2),& 
& cplhhHmcHm(2,2,2),cplAhAhAhAh(2,2,2,2),cplAhAhAhhh(2,2,2,2),cplAhAhhhhh(2,2,2,2),      & 
& cplAhAhHmcHm(2,2,2,2),cplAhhhhhhh(2,2,2,2),cplAhhhHmcHm(2,2,2,2),cplhhhhhhhh(2,2,2,2), & 
& cplhhhhHmcHm(2,2,2,2),cplHmHmcHmcHm(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsColourStructures'
 
cplAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhAhCS(gt1,gt2,gt3,lam5,vd,vu,ZA,cplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhAhhhCS(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,               & 
& cplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhhhhhCS(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,cplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplingAhHmcHmCS(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,cplAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhhhhhCS(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,cplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CouplinghhHmcHmCS(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,              & 
& cplhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplAhAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhAhCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,cplAhAhAhAh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhAhhhCS(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhAhAhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhhhhhCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZA,               & 
& cplAhAhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhAhHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,ZP,              & 
& cplAhAhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhhhhhCS(gt1,gt2,gt3,gt4,lam5,ZH,ZA,cplAhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplAhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingAhhhHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,cplAhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhhhhhCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,cplhhhhhhhh(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplhhhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplinghhhhHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,ZP,              & 
& cplhhhhHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplHmHmcHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHmHmcHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,cplHmHmcHmcHm(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsColourStructures

Subroutine CouplingAhAhAhCS(gt1,gt2,gt3,lam5,vd,vu,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAh' 
 
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

res1 = 0._dp 
res1 = res1+(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res1 = res1+(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res1 = res1+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhCS  
 
 
Subroutine CouplingAhAhhhCS(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,               & 
& ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhh' 
 
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

res1 = 0._dp 
res1 = res1-(lam1*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res1 = res1-(lam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res1 = res1-(lam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(lam3*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res1 = res1-(lam4*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res1 = res1+(lam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(lam3*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res1 = res1-(lam4*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res1 = res1+(lam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1+(vu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res1 = res1-(lam2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhCS  
 
 
Subroutine CouplingAhhhhhCS(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhh' 
 
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

res1 = 0._dp 
res1 = res1-(lam5*vu*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res1 = res1+(vu*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res1 = res1+(lam5*vu*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1+(lam5*vu*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1+(lam5*vd*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhCS  
 
 
Subroutine CouplingAhHmcHmCS(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhHmcHm' 
 
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

res1 = 0._dp 
res1 = res1-(lam4*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1+(lam5*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1+(lam4*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1-(lam5*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1+(lam4*vu*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1-(lam4*vd*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1+(vd*Conjg(lam5)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhHmcHmCS  
 
 
Subroutine CouplinghhhhhhCS(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
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

res1 = 0._dp 
res1 = res1-3*lam1*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res1 = res1-(lam3*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res1 = res1-(lam4*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res1 = res1-(lam5*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res1 = res1-(lam3*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res1 = res1-(lam4*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res1 = res1-(lam5*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(lam3*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res1 = res1-(lam4*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res1 = res1-(lam5*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res1 = res1-(lam3*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res1 = res1-(lam4*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res1 = res1-(lam5*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(lam3*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res1 = res1-(lam4*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res1 = res1-(lam5*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res1 = res1-(lam3*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res1 = res1-(lam4*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res1 = res1-(lam5*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res1 = res1-3*lam2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhCS  
 
 
Subroutine CouplinghhHmcHmCS(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,              & 
& ZH,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHmcHm' 
 
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

res1 = 0._dp 
res1 = res1-(lam1*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res1 = res1-(lam3*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res1 = res1-(lam4*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1-(lam5*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1-(lam4*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1-(lam5*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res1 = res1-(lam4*vu*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1-(vu*Conjg(lam5)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1-(lam4*vd*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1-(vd*Conjg(lam5)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res1 = res1-(lam3*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res1 = res1-(lam2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHmcHmCS  
 
 
Subroutine CouplingAhAhAhAhCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhAh' 
 
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
res1 = res1-3*lam1*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,1)
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,1))/2._dp
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,1))/2._dp
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZA(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZA(gt4,2))/2._dp
res1 = res1-3*lam2*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,2)*ZA(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhAhCS  
 
 
Subroutine CouplingAhAhAhhhCS(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhAhhh' 
 
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
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2)*ZH(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhAhhhCS  
 
 
Subroutine CouplingAhAhhhhhCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,               & 
& ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhhhhh' 
 
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
res1 = res1-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1+(lam5*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1+(lam5*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2)*ZH(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhhhhhCS  
 
 
Subroutine CouplingAhAhHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,              & 
& ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhAhHmcHm' 
 
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
res1 = res1-(lam1*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam3*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam4*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam3*ZA(gt1,1)*ZA(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res1 = res1-(lam2*ZA(gt1,2)*ZA(gt2,2)*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingAhAhHmcHmCS  
 
 
Subroutine CouplingAhhhhhhhCS(gt1,gt2,gt3,gt4,lam5,ZH,ZA,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2)

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhhhhh' 
 
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
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhhhhhCS  
 
 
Subroutine CouplingAhhhHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam4,ZH,ZA,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZA(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingAhhhHmcHm' 
 
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
res1 = res1+(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(lam5*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+(Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+(lam4*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingAhhhHmcHmCS  
 
 
Subroutine CouplinghhhhhhhhCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZH,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
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
res1 = res1-3*lam1*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,1)
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,1))/2._dp
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,1))/2._dp
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1)*ZH(gt4,2))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2)*ZH(gt4,2))/2._dp
res1 = res1-3*lam2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)*ZH(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhCS  
 
 
Subroutine CouplinghhhhHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,              & 
& ZH,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZH(2,2),ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHmcHm' 
 
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
res1 = res1-(lam1*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam3*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam5*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam4*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam3*ZH(gt1,1)*ZH(gt2,1)*ZP(gt3,2)*ZP(gt4,2))
res1 = res1-(lam2*ZH(gt1,2)*ZH(gt2,2)*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHmcHmCS  
 
 
Subroutine CouplingHmHmcHmcHmCS(gt1,gt2,gt3,gt4,lam5,lam1,lam4,lam3,lam2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHmHmcHmcHm' 
 
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
res1 = res1-2*lam1*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res1 = res1-2*lam5*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res1 = res1-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam4*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam4*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-2*Conjg(lam5)*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res1 = res1-2*lam2*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplingHmHmcHmcHmCS  
 
 
End Module Couplings_gumTHDMII 
