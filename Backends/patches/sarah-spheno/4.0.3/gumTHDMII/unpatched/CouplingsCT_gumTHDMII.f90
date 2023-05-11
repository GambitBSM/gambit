! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:23 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module CouplingsCT_gumTHDMII
 
Use Control 
Use Settings 
Use Model_Data_gumTHDMII 
Use Mathematics, Only: CompareMatrices, Adjungate 
 
Contains 
 
 Subroutine CalculateCouplingCT(lam5,vd,vu,ZA,lam1,lam4,lam3,lam2,ZH,ZP,               & 
& g1,g2,TW,g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,dlam5,dvd,dvu,dZA,dlam1,dlam4,            & 
& dlam3,dlam2,dZH,dZP,dg1,dg2,dSinTW,dCosTW,dTanTW,dg3,dYd,dZDL,dZDR,dYe,dZEL,           & 
& dZER,dYu,dZUL,dZUR,ctcplAhAhAh,ctcplAhAhhh,ctcplAhhhhh,ctcplAhHmcHm,ctcplhhhhhh,       & 
& ctcplhhHmcHm,ctcplAhhhVZ,ctcplAhHmcVWm,ctcplAhcHmVWm,ctcplhhHmcVWm,ctcplhhcHmVWm,      & 
& ctcplHmcHmVP,ctcplHmcHmVZ,ctcplhhcVWmVWm,ctcplhhVZVZ,ctcplHmcVWmVP,ctcplHmcVWmVZ,      & 
& ctcplcHmVPVWm,ctcplcHmVWmVZ,ctcplVGVGVG,ctcplcVWmVPVWm,ctcplcVWmVWmVZ,ctcplcFdFdAhL,   & 
& ctcplcFdFdAhR,ctcplcFeFeAhL,ctcplcFeFeAhR,ctcplcFuFuAhL,ctcplcFuFuAhR,ctcplcFdFdhhL,   & 
& ctcplcFdFdhhR,ctcplcFuFdcHmL,ctcplcFuFdcHmR,ctcplcFeFehhL,ctcplcFeFehhR,               & 
& ctcplcFvFecHmL,ctcplcFvFecHmR,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFuHmL,               & 
& ctcplcFdFuHmR,ctcplcFeFvHmL,ctcplcFeFvHmR,ctcplcFdFdVGL,ctcplcFdFdVGR,ctcplcFdFdVPL,   & 
& ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,ctcplcFuFdcVWmL,ctcplcFuFdcVWmR,             & 
& ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFvFecVWmL,               & 
& ctcplcFvFecVWmR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,               & 
& ctcplcFdFuVWmL,ctcplcFdFuVWmR,ctcplcFuFuVZL,ctcplcFuFuVZR,ctcplcFeFvVWmL,              & 
& ctcplcFeFvVWmR,ctcplcFvFvVZL,ctcplcFvFvVZR)

Implicit None 
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZH(2,2),ZP(2,2),g1,g2,TW,g3,dvd,dvu,dZA(2,2),dZH(2,2),dZP(2,2),         & 
& dg1,dg2,dSinTW,dCosTW,dTanTW,dg3

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3),         & 
& Yu(3,3),ZUL(3,3),ZUR(3,3),dlam5,dlam1,dlam4,dlam3,dlam2,dYd(3,3),dZDL(3,3),            & 
& dZDR(3,3),dYe(3,3),dZEL(3,3),dZER(3,3),dYu(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: ctcplAhAhAh(2,2,2),ctcplAhAhhh(2,2,2),ctcplAhhhhh(2,2,2),ctcplAhHmcHm(2,2,2),         & 
& ctcplhhhhhh(2,2,2),ctcplhhHmcHm(2,2,2),ctcplAhhhVZ(2,2),ctcplAhHmcVWm(2,2),            & 
& ctcplAhcHmVWm(2,2),ctcplhhHmcVWm(2,2),ctcplhhcHmVWm(2,2),ctcplHmcHmVP(2,2),            & 
& ctcplHmcHmVZ(2,2),ctcplhhcVWmVWm(2),ctcplhhVZVZ(2),ctcplHmcVWmVP(2),ctcplHmcVWmVZ(2),  & 
& ctcplcHmVPVWm(2),ctcplcHmVWmVZ(2),ctcplVGVGVG,ctcplcVWmVPVWm,ctcplcVWmVWmVZ,           & 
& ctcplcFdFdAhL(3,3,2),ctcplcFdFdAhR(3,3,2),ctcplcFeFeAhL(3,3,2),ctcplcFeFeAhR(3,3,2),   & 
& ctcplcFuFuAhL(3,3,2),ctcplcFuFuAhR(3,3,2),ctcplcFdFdhhL(3,3,2),ctcplcFdFdhhR(3,3,2),   & 
& ctcplcFuFdcHmL(3,3,2),ctcplcFuFdcHmR(3,3,2),ctcplcFeFehhL(3,3,2),ctcplcFeFehhR(3,3,2), & 
& ctcplcFvFecHmL(3,3,2),ctcplcFvFecHmR(3,3,2),ctcplcFuFuhhL(3,3,2),ctcplcFuFuhhR(3,3,2), & 
& ctcplcFdFuHmL(3,3,2),ctcplcFdFuHmR(3,3,2),ctcplcFeFvHmL(3,3,2),ctcplcFeFvHmR(3,3,2),   & 
& ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),ctcplcFdFdVPL(3,3),ctcplcFdFdVPR(3,3),           & 
& ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3),ctcplcFuFdcVWmL(3,3),ctcplcFuFdcVWmR(3,3),       & 
& ctcplcFeFeVPL(3,3),ctcplcFeFeVPR(3,3),ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),           & 
& ctcplcFvFecVWmL(3,3),ctcplcFvFecVWmR(3,3),ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3),       & 
& ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFdFuVWmL(3,3),ctcplcFdFuVWmR(3,3),         & 
& ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3),ctcplcFeFvVWmL(3,3),ctcplcFeFvVWmR(3,3),         & 
& ctcplcFvFvVZL(3,3),ctcplcFvFvVZR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateCouplingCT'
 
ctcplAhAhAh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CT_CouplingAhAhAh(gt1,gt2,gt3,lam5,vd,vu,ZA,dlam5,dvd,dvu,dZA,ctcplAhAhAh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplAhAhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CT_CouplingAhAhhh(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZA,              & 
& dlam5,dlam1,dlam4,dlam3,dlam2,dvd,dvu,dZH,dZA,ctcplAhAhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplAhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CT_CouplingAhhhhh(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,dlam5,dvd,dvu,dZH,dZA,            & 
& ctcplAhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplAhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CT_CouplingAhHmcHm(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,dlam5,dlam4,dvd,            & 
& dvu,dZA,dZP,ctcplAhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplhhhhhh = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CT_Couplinghhhhhh(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,dlam5,           & 
& dlam1,dlam4,dlam3,dlam2,dvd,dvu,dZH,ctcplhhhhhh(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplhhHmcHm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
Call CT_CouplinghhHmcHm(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,ZH,ZP,             & 
& dlam5,dlam1,dlam4,dlam3,dlam2,dvd,dvu,dZH,dZP,ctcplhhHmcHm(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplAhhhVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingAhhhVZ(gt1,gt2,g1,g2,ZH,ZA,TW,dg1,dg2,dZH,dZA,dSinTW,dCosTW,          & 
& dTanTW,ctcplAhhhVZ(gt1,gt2))

 End Do 
End Do 


ctcplAhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingAhHmcVWm(gt1,gt2,g2,ZA,ZP,dg2,dZA,dZP,ctcplAhHmcVWm(gt1,gt2))

 End Do 
End Do 


ctcplAhcHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingAhcHmVWm(gt1,gt2,g2,ZA,ZP,dg2,dZA,dZP,ctcplAhcHmVWm(gt1,gt2))

 End Do 
End Do 


ctcplhhHmcVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplinghhHmcVWm(gt1,gt2,g2,ZH,ZP,dg2,dZH,dZP,ctcplhhHmcVWm(gt1,gt2))

 End Do 
End Do 


ctcplhhcHmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplinghhcHmVWm(gt1,gt2,g2,ZH,ZP,dg2,dZH,dZP,ctcplhhcHmVWm(gt1,gt2))

 End Do 
End Do 


ctcplHmcHmVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingHmcHmVP(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,dTanTW,         & 
& ctcplHmcHmVP(gt1,gt2))

 End Do 
End Do 


ctcplHmcHmVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingHmcHmVZ(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,dTanTW,         & 
& ctcplHmcHmVZ(gt1,gt2))

 End Do 
End Do 


ctcplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CT_CouplinghhcVWmVWm(gt1,g2,vd,vu,ZH,dg2,dvd,dvu,dZH,ctcplhhcVWmVWm(gt1))

End Do 


ctcplhhVZVZ = 0._dp 
Do gt1 = 1, 2
Call CT_CouplinghhVZVZ(gt1,g1,g2,vd,vu,ZH,TW,dg1,dg2,dvd,dvu,dZH,dSinTW,              & 
& dCosTW,dTanTW,ctcplhhVZVZ(gt1))

End Do 


ctcplHmcVWmVP = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingHmcVWmVP(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,dSinTW,            & 
& dCosTW,dTanTW,ctcplHmcVWmVP(gt1))

End Do 


ctcplHmcVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingHmcVWmVZ(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,dSinTW,            & 
& dCosTW,dTanTW,ctcplHmcVWmVZ(gt1))

End Do 


ctcplcHmVPVWm = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingcHmVPVWm(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,dSinTW,            & 
& dCosTW,dTanTW,ctcplcHmVPVWm(gt1))

End Do 


ctcplcHmVWmVZ = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingcHmVWmVZ(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,dSinTW,            & 
& dCosTW,dTanTW,ctcplcHmVWmVZ(gt1))

End Do 


ctcplVGVGVG = 0._dp 
Call CT_CouplingVGVGVG(g3,dg3,ctcplVGVGVG)



ctcplcVWmVPVWm = 0._dp 
Call CT_CouplingcVWmVPVWm(g2,TW,dg2,dSinTW,dCosTW,dTanTW,ctcplcVWmVPVWm)



ctcplcVWmVWmVZ = 0._dp 
Call CT_CouplingcVWmVWmVZ(g2,TW,dg2,dSinTW,dCosTW,dTanTW,ctcplcVWmVWmVZ)



ctcplcFdFdAhL = 0._dp 
ctcplcFdFdAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFdFdAh(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,dYd,dZA,dZDL,dZDR,ctcplcFdFdAhL(gt1,gt2,gt3)& 
& ,ctcplcFdFdAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFeFeAhL = 0._dp 
ctcplcFeFeAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFeFeAh(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,dYe,dZA,dZEL,dZER,ctcplcFeFeAhL(gt1,gt2,gt3)& 
& ,ctcplcFeFeAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFuFuAhL = 0._dp 
ctcplcFuFuAhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFuFuAh(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,dYu,dZA,dZUL,dZUR,ctcplcFuFuAhL(gt1,gt2,gt3)& 
& ,ctcplcFuFuAhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFdFdhhL = 0._dp 
ctcplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFdFdhh(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,dYd,dZH,dZDL,dZDR,ctcplcFdFdhhL(gt1,gt2,gt3)& 
& ,ctcplcFdFdhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFuFdcHmL = 0._dp 
ctcplcFuFdcHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFuFdcHm(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,dYu,dYd,dZP,            & 
& dZDL,dZDR,dZUL,dZUR,ctcplcFuFdcHmL(gt1,gt2,gt3),ctcplcFuFdcHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFeFehhL = 0._dp 
ctcplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFeFehh(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,dYe,dZH,dZEL,dZER,ctcplcFeFehhL(gt1,gt2,gt3)& 
& ,ctcplcFeFehhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFvFecHmL = 0._dp 
ctcplcFvFecHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFvFecHm(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,ctcplcFvFecHmL(gt1,gt2,gt3)& 
& ,ctcplcFvFecHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFuFuhhL = 0._dp 
ctcplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFuFuhh(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,dYu,dZH,dZUL,dZUR,ctcplcFuFuhhL(gt1,gt2,gt3)& 
& ,ctcplcFuFuhhR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFdFuHmL = 0._dp 
ctcplcFdFuHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFdFuHm(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,dYu,dYd,dZP,             & 
& dZDL,dZDR,dZUL,dZUR,ctcplcFdFuHmL(gt1,gt2,gt3),ctcplcFdFuHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFeFvHmL = 0._dp 
ctcplcFeFvHmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFeFvHm(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,ctcplcFeFvHmL(gt1,gt2,gt3) & 
& ,ctcplcFeFvHmR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFdFdVGL = 0._dp 
ctcplcFdFdVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFdVG(gt1,gt2,g3,dg3,ctcplcFdFdVGL(gt1,gt2),ctcplcFdFdVGR(gt1,gt2))

 End Do 
End Do 


ctcplcFdFdVPL = 0._dp 
ctcplcFdFdVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFdVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFdFdVPL(gt1,gt2)& 
& ,ctcplcFdFdVPR(gt1,gt2))

 End Do 
End Do 


ctcplcFdFdVZL = 0._dp 
ctcplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFdVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFdFdVZL(gt1,gt2)& 
& ,ctcplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


ctcplcFuFdcVWmL = 0._dp 
ctcplcFuFdcVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFdcVWm(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,ctcplcFuFdcVWmL(gt1,gt2)   & 
& ,ctcplcFuFdcVWmR(gt1,gt2))

 End Do 
End Do 


ctcplcFeFeVPL = 0._dp 
ctcplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFeVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFeFeVPL(gt1,gt2)& 
& ,ctcplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


ctcplcFeFeVZL = 0._dp 
ctcplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFeVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFeFeVZL(gt1,gt2)& 
& ,ctcplcFeFeVZR(gt1,gt2))

 End Do 
End Do 


ctcplcFvFecVWmL = 0._dp 
ctcplcFvFecVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFvFecVWm(gt1,gt2,g2,ZEL,dg2,dZEL,ctcplcFvFecVWmL(gt1,gt2)            & 
& ,ctcplcFvFecVWmR(gt1,gt2))

 End Do 
End Do 


ctcplcFuFuVGL = 0._dp 
ctcplcFuFuVGR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFuVG(gt1,gt2,g3,dg3,ctcplcFuFuVGL(gt1,gt2),ctcplcFuFuVGR(gt1,gt2))

 End Do 
End Do 


ctcplcFuFuVPL = 0._dp 
ctcplcFuFuVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFuVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFuFuVPL(gt1,gt2)& 
& ,ctcplcFuFuVPR(gt1,gt2))

 End Do 
End Do 


ctcplcFdFuVWmL = 0._dp 
ctcplcFdFuVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFuVWm(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,ctcplcFdFuVWmL(gt1,gt2)     & 
& ,ctcplcFdFuVWmR(gt1,gt2))

 End Do 
End Do 


ctcplcFuFuVZL = 0._dp 
ctcplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFuVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFuFuVZL(gt1,gt2)& 
& ,ctcplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


ctcplcFeFvVWmL = 0._dp 
ctcplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFvVWm(gt1,gt2,g2,ZEL,dg2,dZEL,ctcplcFeFvVWmL(gt1,gt2)              & 
& ,ctcplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


ctcplcFvFvVZL = 0._dp 
ctcplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFvFvVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFvFvVZL(gt1,gt2)& 
& ,ctcplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CalculateCouplingCT

Subroutine CT_CouplingAhAhAh(gt1,gt2,gt3,lam5,vd,vu,ZA,dlam5,dvd,dvu,dZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),dvd,dvu,dZA(2,2)

Complex(dp), Intent(in) :: lam5,dlam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhAhAh' 
 
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
res = res+(lam5*vu*dZA(gt3,2)*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt3,2)*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+(lam5*vu*dZA(gt3,1)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt3,1)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res-(lam5*vd*dZA(gt3,2)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt3,2)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res+(lam5*vu*dZA(gt3,1)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt3,1)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(lam5*vd*dZA(gt3,2)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt3,2)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(lam5*vd*dZA(gt3,1)*ZA(gt1,2)*ZA(gt2,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt3,1)*ZA(gt1,2)*ZA(gt2,2))/2._dp
res = res+(lam5*vu*dZA(gt2,2)*ZA(gt1,1)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt2,2)*ZA(gt1,1)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*dZA(gt2,1)*ZA(gt1,2)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt2,1)*ZA(gt1,2)*ZA(gt3,1))/2._dp
res = res-(lam5*vd*dZA(gt2,2)*ZA(gt1,2)*ZA(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt2,2)*ZA(gt1,2)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*dZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res+(dvu*lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res+(dlam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*dZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(lam5*vd*dZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(dvu*lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(dlam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(dvd*lam5*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res-(dlam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZA(gt3,1))/2._dp
res = res+(lam5*vu*dZA(gt2,1)*ZA(gt1,1)*ZA(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt2,1)*ZA(gt1,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt2,2)*ZA(gt1,1)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt2,2)*ZA(gt1,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt2,1)*ZA(gt1,2)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt2,1)*ZA(gt1,2)*ZA(gt3,2))/2._dp
res = res+(lam5*vu*dZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(dvu*lam5*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(dlam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(dvd*lam5*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(dlam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZA(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res-(dvd*lam5*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res-(dlam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZA(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhAhAh  
 
 
Subroutine CT_CouplingAhAhhh(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,              & 
& ZH,ZA,dlam5,dlam1,dlam4,dlam3,dlam2,dvd,dvu,dZH,dZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2),dvd,dvu,dZH(2,2),dZA(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,dlam5,dlam1,dlam4,dlam3,dlam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhAhhh' 
 
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
res = res-(lam1*vd*dZH(gt3,1)*ZA(gt1,1)*ZA(gt2,1))
res = res-(lam3*vu*dZH(gt3,2)*ZA(gt1,1)*ZA(gt2,1))
res = res-(lam4*vu*dZH(gt3,2)*ZA(gt1,1)*ZA(gt2,1))
res = res+(lam5*vu*dZH(gt3,2)*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res+(vu*Conjg(lam5)*dZH(gt3,2)*ZA(gt1,1)*ZA(gt2,1))/2._dp
res = res-(lam5*vu*dZH(gt3,1)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,1)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res-(lam5*vd*dZH(gt3,2)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt3,2)*ZA(gt1,2)*ZA(gt2,1))/2._dp
res = res-(lam5*vu*dZH(gt3,1)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,1)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(lam5*vd*dZH(gt3,2)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt3,2)*ZA(gt1,1)*ZA(gt2,2))/2._dp
res = res-(lam3*vd*dZH(gt3,1)*ZA(gt1,2)*ZA(gt2,2))
res = res-(lam4*vd*dZH(gt3,1)*ZA(gt1,2)*ZA(gt2,2))
res = res+(lam5*vd*dZH(gt3,1)*ZA(gt1,2)*ZA(gt2,2))/2._dp
res = res+(vd*Conjg(lam5)*dZH(gt3,1)*ZA(gt1,2)*ZA(gt2,2))/2._dp
res = res-(lam2*vu*dZH(gt3,2)*ZA(gt1,2)*ZA(gt2,2))
res = res-(lam1*vd*dZA(gt2,1)*ZA(gt1,1)*ZH(gt3,1))
res = res-(lam5*vu*dZA(gt2,2)*ZA(gt1,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt2,2)*ZA(gt1,1)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*dZA(gt2,1)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt2,1)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*dZA(gt2,2)*ZA(gt1,2)*ZH(gt3,1))
res = res-(lam4*vd*dZA(gt2,2)*ZA(gt1,2)*ZH(gt3,1))
res = res+(lam5*vd*dZA(gt2,2)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt2,2)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res-(lam1*vd*dZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*dZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dvd*lam1*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res = res-(dlam1*vd*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,1))
res = res-(dvu*lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dlam5*vu*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*dZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*dZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*dZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(lam5*vd*dZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvu*lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dlam5*vu*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvd*lam3*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res-(dvd*lam4*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(dvd*lam5*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dlam3*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res-(dlam4*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))
res = res+(dlam5*vd*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*dZA(gt2,1)*ZA(gt1,1)*ZH(gt3,2))
res = res-(lam4*vu*dZA(gt2,1)*ZA(gt1,1)*ZH(gt3,2))
res = res+(lam5*vu*dZA(gt2,1)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res+(vu*Conjg(lam5)*dZA(gt2,1)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt2,2)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZA(gt2,2)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt2,1)*ZA(gt1,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZA(gt2,1)*ZA(gt1,2)*ZH(gt3,2))/2._dp
res = res-(lam2*vu*dZA(gt2,2)*ZA(gt1,2)*ZH(gt3,2))
res = res-(lam3*vu*dZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*dZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(lam5*vu*dZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vu*Conjg(lam5)*dZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvu*lam3*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res-(dvu*lam4*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(dvu*lam5*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dlam3*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res-(dlam4*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))
res = res+(dlam5*vu*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vu*Conjg(dlam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res+(dvu*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvd*lam5*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dlam5*vd*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(dlam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvd*Conjg(lam5)*ZA(gt1,2)*ZA(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(lam2*vu*dZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))
res = res-(dvd*lam5*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(dlam5*vd*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(dlam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(dvd*Conjg(lam5)*ZA(gt1,1)*ZA(gt2,2)*ZH(gt3,2))/2._dp
res = res-(dvu*lam2*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))
res = res-(dlam2*vu*ZA(gt1,2)*ZA(gt2,2)*ZH(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhAhhh  
 
 
Subroutine CT_CouplingAhhhhh(gt1,gt2,gt3,lam5,vd,vu,ZH,ZA,dlam5,dvd,dvu,              & 
& dZH,dZA,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZA(2,2),dvd,dvu,dZH(2,2),dZA(2,2)

Complex(dp), Intent(in) :: lam5,dlam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhhhhh' 
 
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
res = res+(lam5*vu*dZH(gt3,2)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,2)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res-(lam5*vu*dZH(gt3,1)*ZA(gt1,2)*ZH(gt2,1))/2._dp
res = res+(vu*Conjg(lam5)*dZH(gt3,1)*ZA(gt1,2)*ZH(gt2,1))/2._dp
res = res-(lam5*vd*dZH(gt3,2)*ZA(gt1,2)*ZH(gt2,1))/2._dp
res = res+(vd*Conjg(lam5)*dZH(gt3,2)*ZA(gt1,2)*ZH(gt2,1))/2._dp
res = res+(lam5*vu*dZH(gt3,1)*ZA(gt1,1)*ZH(gt2,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,1)*ZA(gt1,1)*ZH(gt2,2))/2._dp
res = res+(lam5*vd*dZH(gt3,2)*ZA(gt1,1)*ZH(gt2,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt3,2)*ZA(gt1,1)*ZH(gt2,2))/2._dp
res = res-(lam5*vd*dZH(gt3,1)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(vd*Conjg(lam5)*dZH(gt3,1)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(lam5*vu*dZH(gt2,2)*ZA(gt1,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt2,2)*ZA(gt1,1)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*dZH(gt2,1)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res+(vu*Conjg(lam5)*dZH(gt2,1)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res-(lam5*vd*dZH(gt2,2)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*dZH(gt2,2)*ZA(gt1,2)*ZH(gt3,1))/2._dp
res = res-(lam5*vu*dZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(vu*Conjg(lam5)*dZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dvu*lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dlam5*vu*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(vu*Conjg(dlam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(dvu*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*dZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam5*vd*dZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(dvu*lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(dlam5*vu*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvd*lam5*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dlam5*vd*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res+(lam5*vu*dZH(gt2,1)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt2,1)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res+(lam5*vd*dZH(gt2,2)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt2,2)*ZA(gt1,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*dZH(gt2,1)*ZA(gt1,2)*ZH(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZH(gt2,1)*ZA(gt1,2)*ZH(gt3,2))/2._dp
res = res+(lam5*vu*dZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam5*vd*dZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(dvu*lam5*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(dlam5*vu*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvd*lam5*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dlam5*vd*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res+(lam5*vd*dZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res+(dvd*lam5*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res+(dlam5*vd*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(dlam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(dvd*Conjg(lam5)*ZA(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhhhhh  
 
 
Subroutine CT_CouplingAhHmcHm(gt1,gt2,gt3,lam5,lam4,vd,vu,ZA,ZP,dlam5,dlam4,          & 
& dvd,dvu,dZA,dZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZA(2,2),ZP(2,2),dvd,dvu,dZA(2,2),dZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4,dlam5,dlam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhHmcHm' 
 
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
res = res+(lam4*vu*dZP(gt3,2)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZP(gt3,2)*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(lam4*vd*dZP(gt3,2)*ZA(gt1,2)*ZP(gt2,1))/2._dp
res = res+(vd*Conjg(lam5)*dZP(gt3,2)*ZA(gt1,2)*ZP(gt2,1))/2._dp
res = res-(lam4*vu*dZP(gt3,1)*ZA(gt1,1)*ZP(gt2,2))/2._dp
res = res+(lam5*vu*dZP(gt3,1)*ZA(gt1,1)*ZP(gt2,2))/2._dp
res = res+(lam4*vd*dZP(gt3,1)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = res-(lam5*vd*dZP(gt3,1)*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = res-(lam4*vu*dZP(gt2,2)*ZA(gt1,1)*ZP(gt3,1))/2._dp
res = res+(lam5*vu*dZP(gt2,2)*ZA(gt1,1)*ZP(gt3,1))/2._dp
res = res+(lam4*vd*dZP(gt2,2)*ZA(gt1,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*dZP(gt2,2)*ZA(gt1,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vu*dZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam5*vu*dZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vd*dZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*dZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dvu*lam4*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dvu*lam5*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam4*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dlam5*vu*ZA(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dvd*lam4*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dvd*lam5*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dlam4*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam5*vd*ZA(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(lam4*vu*dZP(gt2,1)*ZA(gt1,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZP(gt2,1)*ZA(gt1,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*dZP(gt2,1)*ZA(gt1,2)*ZP(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZP(gt2,1)*ZA(gt1,2)*ZP(gt3,2))/2._dp
res = res+(lam4*vu*dZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*dZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*Conjg(lam5)*dZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(dvu*lam4*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(dlam4*vu*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(dlam5)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dvu*Conjg(lam5)*ZA(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dvd*lam4*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dlam4*vd*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(vd*Conjg(dlam5)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(dvd*Conjg(lam5)*ZA(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhHmcHm  
 
 
Subroutine CT_Couplinghhhhhh(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,              & 
& ZH,dlam5,dlam1,dlam4,dlam3,dlam2,dvd,dvu,dZH,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),dvd,dvu,dZH(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,dlam5,dlam1,dlam4,dlam3,dlam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_Couplinghhhhhh' 
 
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
res = res-3*lam1*vd*dZH(gt3,1)*ZH(gt1,1)*ZH(gt2,1)
res = res-(lam3*vu*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,1))
res = res-(lam4*vu*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,1))
res = res-(lam5*vu*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,1))/2._dp
res = res-(lam3*vu*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,1))
res = res-(lam4*vu*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,1))
res = res-(lam5*vu*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,1))/2._dp
res = res-(lam3*vd*dZH(gt3,2)*ZH(gt1,2)*ZH(gt2,1))
res = res-(lam4*vd*dZH(gt3,2)*ZH(gt1,2)*ZH(gt2,1))
res = res-(lam5*vd*dZH(gt3,2)*ZH(gt1,2)*ZH(gt2,1))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt3,2)*ZH(gt1,2)*ZH(gt2,1))/2._dp
res = res-(lam3*vu*dZH(gt3,1)*ZH(gt1,1)*ZH(gt2,2))
res = res-(lam4*vu*dZH(gt3,1)*ZH(gt1,1)*ZH(gt2,2))
res = res-(lam5*vu*dZH(gt3,1)*ZH(gt1,1)*ZH(gt2,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt3,1)*ZH(gt1,1)*ZH(gt2,2))/2._dp
res = res-(lam3*vd*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,2))
res = res-(lam4*vd*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,2))
res = res-(lam5*vd*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt3,2)*ZH(gt1,1)*ZH(gt2,2))/2._dp
res = res-(lam3*vd*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,2))
res = res-(lam4*vd*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,2))
res = res-(lam5*vd*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt3,1)*ZH(gt1,2)*ZH(gt2,2))/2._dp
res = res-3*lam2*vu*dZH(gt3,2)*ZH(gt1,2)*ZH(gt2,2)
res = res-3*lam1*vd*dZH(gt2,1)*ZH(gt1,1)*ZH(gt3,1)
res = res-(lam3*vu*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,1))
res = res-(lam4*vu*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,1))
res = res-(lam5*vu*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,1))
res = res-(lam4*vu*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,1))
res = res-(lam5*vu*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*dZH(gt2,2)*ZH(gt1,2)*ZH(gt3,1))
res = res-(lam4*vd*dZH(gt2,2)*ZH(gt1,2)*ZH(gt3,1))
res = res-(lam5*vd*dZH(gt2,2)*ZH(gt1,2)*ZH(gt3,1))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt2,2)*ZH(gt1,2)*ZH(gt3,1))/2._dp
res = res-3*lam1*vd*dZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res = res-(lam3*vu*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam4*vu*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(lam5*vu*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-3*dvd*lam1*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res = res-3*dlam1*vd*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,1)
res = res-(dvu*lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(dvu*lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(dvu*lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dlam3*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(dlam4*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))
res = res-(dlam5*vu*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vu*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vu*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vd*dZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam4*vd*dZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(lam5*vd*dZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvu*lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dvu*lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dvu*lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dlam3*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dlam4*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dlam5*vu*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vu*Conjg(dlam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvd*lam3*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dvd*lam4*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dvd*lam5*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dlam3*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dlam4*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))
res = res-(dlam5*vd*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(vd*Conjg(dlam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(dvd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,1))/2._dp
res = res-(lam3*vu*dZH(gt2,1)*ZH(gt1,1)*ZH(gt3,2))
res = res-(lam4*vu*dZH(gt2,1)*ZH(gt1,1)*ZH(gt3,2))
res = res-(lam5*vu*dZH(gt2,1)*ZH(gt1,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt2,1)*ZH(gt1,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,2))
res = res-(lam4*vd*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,2))
res = res-(lam5*vd*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt2,2)*ZH(gt1,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,2))
res = res-(lam4*vd*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,2))
res = res-(lam5*vd*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt2,1)*ZH(gt1,2)*ZH(gt3,2))/2._dp
res = res-3*lam2*vu*dZH(gt2,2)*ZH(gt1,2)*ZH(gt3,2)
res = res-(lam3*vu*dZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vu*dZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vu*dZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam4*vd*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(lam5*vd*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvu*lam3*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dvu*lam4*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dvu*lam5*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dlam3*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dlam4*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dlam5*vu*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vu*Conjg(dlam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvu*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvd*lam3*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dvd*lam4*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dvd*lam5*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dlam3*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dlam4*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))
res = res-(dlam5*vd*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(dlam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(dvd*Conjg(lam5)*ZH(gt1,2)*ZH(gt2,1)*ZH(gt3,2))/2._dp
res = res-(lam3*vd*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam4*vd*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(lam5*vd*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-3*lam2*vu*dZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)
res = res-(dvd*lam3*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(dvd*lam4*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(dvd*lam5*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(dlam3*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(dlam4*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))
res = res-(dlam5*vd*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(vd*Conjg(dlam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-(dvd*Conjg(lam5)*ZH(gt1,1)*ZH(gt2,2)*ZH(gt3,2))/2._dp
res = res-3*dvu*lam2*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)
res = res-3*dlam2*vu*ZH(gt1,2)*ZH(gt2,2)*ZH(gt3,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_Couplinghhhhhh  
 
 
Subroutine CT_CouplinghhHmcHm(gt1,gt2,gt3,lam5,lam1,lam4,lam3,lam2,vd,vu,             & 
& ZH,ZP,dlam5,dlam1,dlam4,dlam3,dlam2,dvd,dvu,dZH,dZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: vd,vu,ZH(2,2),ZP(2,2),dvd,dvu,dZH(2,2),dZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam4,lam3,lam2,dlam5,dlam1,dlam4,dlam3,dlam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhHmcHm' 
 
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
res = res-(lam1*vd*dZP(gt3,1)*ZH(gt1,1)*ZP(gt2,1))
res = res-(lam4*vu*dZP(gt3,2)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(vu*Conjg(lam5)*dZP(gt3,2)*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(lam3*vu*dZP(gt3,1)*ZH(gt1,2)*ZP(gt2,1))
res = res-(lam4*vd*dZP(gt3,2)*ZH(gt1,2)*ZP(gt2,1))/2._dp
res = res-(vd*Conjg(lam5)*dZP(gt3,2)*ZH(gt1,2)*ZP(gt2,1))/2._dp
res = res-(lam4*vu*dZP(gt3,1)*ZH(gt1,1)*ZP(gt2,2))/2._dp
res = res-(lam5*vu*dZP(gt3,1)*ZH(gt1,1)*ZP(gt2,2))/2._dp
res = res-(lam3*vd*dZP(gt3,2)*ZH(gt1,1)*ZP(gt2,2))
res = res-(lam4*vd*dZP(gt3,1)*ZH(gt1,2)*ZP(gt2,2))/2._dp
res = res-(lam5*vd*dZP(gt3,1)*ZH(gt1,2)*ZP(gt2,2))/2._dp
res = res-(lam2*vu*dZP(gt3,2)*ZH(gt1,2)*ZP(gt2,2))
res = res-(lam1*vd*dZP(gt2,1)*ZH(gt1,1)*ZP(gt3,1))
res = res-(lam4*vu*dZP(gt2,2)*ZH(gt1,1)*ZP(gt3,1))/2._dp
res = res-(lam5*vu*dZP(gt2,2)*ZH(gt1,1)*ZP(gt3,1))/2._dp
res = res-(lam3*vu*dZP(gt2,1)*ZH(gt1,2)*ZP(gt3,1))
res = res-(lam4*vd*dZP(gt2,2)*ZH(gt1,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*dZP(gt2,2)*ZH(gt1,2)*ZP(gt3,1))/2._dp
res = res-(lam1*vd*dZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam3*vu*dZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res = res-(dvd*lam1*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res = res-(dlam1*vd*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,1))
res = res-(dvu*lam3*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res = res-(dlam3*vu*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*vu*dZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vu*dZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vd*dZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam5*vd*dZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dvu*lam4*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dvu*lam5*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam4*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam5*vu*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dvd*lam4*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dvd*lam5*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam4*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam5*vd*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*vu*dZP(gt2,1)*ZH(gt1,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZP(gt2,1)*ZH(gt1,1)*ZP(gt3,2))/2._dp
res = res-(lam3*vd*dZP(gt2,2)*ZH(gt1,1)*ZP(gt3,2))
res = res-(lam4*vd*dZP(gt2,1)*ZH(gt1,2)*ZP(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZP(gt2,1)*ZH(gt1,2)*ZP(gt3,2))/2._dp
res = res-(lam2*vu*dZP(gt2,2)*ZH(gt1,2)*ZP(gt3,2))
res = res-(lam4*vu*dZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(lam5)*dZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam4*vd*dZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vd*Conjg(lam5)*dZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dvu*lam4*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dlam4*vu*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vu*Conjg(dlam5)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dvu*Conjg(lam5)*ZH(gt1,1)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dvd*lam4*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dlam4*vd*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(vd*Conjg(dlam5)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dvd*Conjg(lam5)*ZH(gt1,2)*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam3*vd*dZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res = res-(lam2*vu*dZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))
res = res-(dvd*lam3*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res = res-(dlam3*vd*ZH(gt1,1)*ZP(gt2,2)*ZP(gt3,2))
res = res-(dvu*lam2*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))
res = res-(dlam2*vu*ZH(gt1,2)*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhHmcHm  
 
 
Subroutine CT_CouplingAhhhVZ(gt1,gt2,g1,g2,ZH,ZA,TW,dg1,dg2,dZH,dZA,dSinTW,           & 
& dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZH(2,2),ZA(2,2),TW,dg1,dg2,dZH(2,2),dZA(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhhhVZ' 
 
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
res = res+(g2*Cos(TW)*dZH(gt2,1)*ZA(gt1,1))/2._dp
res = res+(g1*dZH(gt2,1)*Sin(TW)*ZA(gt1,1))/2._dp
res = res+(g2*Cos(TW)*dZH(gt2,2)*ZA(gt1,2))/2._dp
res = res+(g1*dZH(gt2,2)*Sin(TW)*ZA(gt1,2))/2._dp
res = res+(g2*Cos(TW)*dZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g1*dZA(gt1,1)*Sin(TW)*ZH(gt2,1))/2._dp
res = res+(dSinTW*g1*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(dCosTW*g2*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(dg2*Cos(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(dg1*Sin(TW)*ZA(gt1,1)*ZH(gt2,1))/2._dp
res = res+(g2*Cos(TW)*dZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(g1*dZA(gt1,2)*Sin(TW)*ZH(gt2,2))/2._dp
res = res+(dSinTW*g1*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(dCosTW*g2*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(dg2*Cos(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = res+(dg1*Sin(TW)*ZA(gt1,2)*ZH(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhhhVZ  
 
 
Subroutine CT_CouplingAhHmcVWm(gt1,gt2,g2,ZA,ZP,dg2,dZA,dZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2),ZP(2,2),dg2,dZA(2,2),dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhHmcVWm' 
 
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
res = res-(g2*dZP(gt2,1)*ZA(gt1,1))/2._dp
res = res-(g2*dZP(gt2,2)*ZA(gt1,2))/2._dp
res = res-(g2*dZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*dZA(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhHmcVWm  
 
 
Subroutine CT_CouplingAhcHmVWm(gt1,gt2,g2,ZA,ZP,dg2,dZA,dZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZA(2,2),ZP(2,2),dg2,dZA(2,2),dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingAhcHmVWm' 
 
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
res = res-(g2*dZP(gt2,1)*ZA(gt1,1))/2._dp
res = res-(g2*dZP(gt2,2)*ZA(gt1,2))/2._dp
res = res-(g2*dZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg2*ZA(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*dZA(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg2*ZA(gt1,2)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingAhcHmVWm  
 
 
Subroutine CT_CouplinghhHmcVWm(gt1,gt2,g2,ZH,ZP,dg2,dZH,dZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2),ZP(2,2),dg2,dZH(2,2),dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhHmcVWm' 
 
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
res = res+(g2*dZP(gt2,1)*ZH(gt1,1))/2._dp
res = res+(g2*dZP(gt2,2)*ZH(gt1,2))/2._dp
res = res+(g2*dZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dg2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*dZH(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dg2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhHmcVWm  
 
 
Subroutine CT_CouplinghhcHmVWm(gt1,gt2,g2,ZH,ZP,dg2,dZH,dZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZH(2,2),ZP(2,2),dg2,dZH(2,2),dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhcHmVWm' 
 
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
res = res-(g2*dZP(gt2,1)*ZH(gt1,1))/2._dp
res = res-(g2*dZP(gt2,2)*ZH(gt1,2))/2._dp
res = res-(g2*dZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg2*ZH(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*dZH(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg2*ZH(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhcHmVWm  
 
 
Subroutine CT_CouplingHmcHmVP(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,          & 
& dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW,dg1,dg2,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHmcHmVP' 
 
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
res = res-(g1*Cos(TW)*dZP(gt2,1)*ZP(gt1,1))/2._dp
res = res-(g2*dZP(gt2,1)*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g1*Cos(TW)*dZP(gt2,2)*ZP(gt1,2))/2._dp
res = res-(g2*dZP(gt2,2)*Sin(TW)*ZP(gt1,2))/2._dp
res = res-(g1*Cos(TW)*dZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*dZP(gt1,1)*Sin(TW)*ZP(gt2,1))/2._dp
res = res-(dCosTW*g1*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dSinTW*g2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg1*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg2*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*Cos(TW)*dZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g2*dZP(gt1,2)*Sin(TW)*ZP(gt2,2))/2._dp
res = res-(dCosTW*g1*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dSinTW*g2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg1*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg2*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHmcHmVP  
 
 
Subroutine CT_CouplingHmcHmVZ(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,          & 
& dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW,dg1,dg2,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHmcHmVZ' 
 
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
res = res-(g2*Cos(TW)*dZP(gt2,1)*ZP(gt1,1))/2._dp
res = res+(g1*dZP(gt2,1)*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(g2*Cos(TW)*dZP(gt2,2)*ZP(gt1,2))/2._dp
res = res+(g1*dZP(gt2,2)*Sin(TW)*ZP(gt1,2))/2._dp
res = res-(g2*Cos(TW)*dZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*dZP(gt1,1)*Sin(TW)*ZP(gt2,1))/2._dp
res = res+(dSinTW*g1*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dCosTW*g2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg2*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dg1*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g2*Cos(TW)*dZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(g1*dZP(gt1,2)*Sin(TW)*ZP(gt2,2))/2._dp
res = res+(dSinTW*g1*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dCosTW*g2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg2*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dg1*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHmcHmVZ  
 
 
Subroutine CT_CouplinghhcVWmVWm(gt1,g2,vd,vu,ZH,dg2,dvd,dvu,dZH,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g2,vd,vu,ZH(2,2),dg2,dvd,dvu,dZH(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhcVWmVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*vd*dZH(gt1,1))/2._dp
res = res+(g2**2*vu*dZH(gt1,2))/2._dp
res = res+(dvd*g2**2*ZH(gt1,1))/2._dp
res = res+dg2*g2*vd*ZH(gt1,1)
res = res+(dvu*g2**2*ZH(gt1,2))/2._dp
res = res+dg2*g2*vu*ZH(gt1,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhcVWmVWm  
 
 
Subroutine CT_CouplinghhVZVZ(gt1,g1,g2,vd,vu,ZH,TW,dg1,dg2,dvd,dvu,dZH,               & 
& dSinTW,dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZH(2,2),TW,dg1,dg2,dvd,dvu,dZH(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhVZVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1**2*vd*dZH(gt1,1))/4._dp
res = res+(g2**2*vd*dZH(gt1,1))/4._dp
res = res-(g1**2*vd*Cos(TW)**2*dZH(gt1,1))/4._dp
res = res+(g2**2*vd*Cos(TW)**2*dZH(gt1,1))/4._dp
res = res+(g1**2*vu*dZH(gt1,2))/4._dp
res = res+(g2**2*vu*dZH(gt1,2))/4._dp
res = res-(g1**2*vu*Cos(TW)**2*dZH(gt1,2))/4._dp
res = res+(g2**2*vu*Cos(TW)**2*dZH(gt1,2))/4._dp
res = res+g1*g2*vd*Cos(TW)*dZH(gt1,1)*Sin(TW)
res = res+g1*g2*vu*Cos(TW)*dZH(gt1,2)*Sin(TW)
res = res+(g1**2*vd*dZH(gt1,1)*Sin(TW)**2)/4._dp
res = res-(g2**2*vd*dZH(gt1,1)*Sin(TW)**2)/4._dp
res = res+(g1**2*vu*dZH(gt1,2)*Sin(TW)**2)/4._dp
res = res-(g2**2*vu*dZH(gt1,2)*Sin(TW)**2)/4._dp
res = res+(dvd*g1**2*ZH(gt1,1))/4._dp
res = res+(dvd*g2**2*ZH(gt1,1))/4._dp
res = res+(dg1*g1*vd*ZH(gt1,1))/2._dp
res = res+(dg2*g2*vd*ZH(gt1,1))/2._dp
res = res-(dCosTW*g1**2*vd*Cos(TW)*ZH(gt1,1))/2._dp
res = res+dSinTW*g1*g2*vd*Cos(TW)*ZH(gt1,1)
res = res+(dCosTW*g2**2*vd*Cos(TW)*ZH(gt1,1))/2._dp
res = res-(dvd*g1**2*Cos(TW)**2*ZH(gt1,1))/4._dp
res = res+(dvd*g2**2*Cos(TW)**2*ZH(gt1,1))/4._dp
res = res-(dg1*g1*vd*Cos(TW)**2*ZH(gt1,1))/2._dp
res = res+(dg2*g2*vd*Cos(TW)**2*ZH(gt1,1))/2._dp
res = res+(dSinTW*g1**2*vd*Sin(TW)*ZH(gt1,1))/2._dp
res = res+dCosTW*g1*g2*vd*Sin(TW)*ZH(gt1,1)
res = res-(dSinTW*g2**2*vd*Sin(TW)*ZH(gt1,1))/2._dp
res = res+dvd*g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,1)
res = res+dg2*g1*vd*Cos(TW)*Sin(TW)*ZH(gt1,1)
res = res+dg1*g2*vd*Cos(TW)*Sin(TW)*ZH(gt1,1)
res = res+(dvd*g1**2*Sin(TW)**2*ZH(gt1,1))/4._dp
res = res-(dvd*g2**2*Sin(TW)**2*ZH(gt1,1))/4._dp
res = res+(dg1*g1*vd*Sin(TW)**2*ZH(gt1,1))/2._dp
res = res-(dg2*g2*vd*Sin(TW)**2*ZH(gt1,1))/2._dp
res = res+(dvu*g1**2*ZH(gt1,2))/4._dp
res = res+(dvu*g2**2*ZH(gt1,2))/4._dp
res = res+(dg1*g1*vu*ZH(gt1,2))/2._dp
res = res+(dg2*g2*vu*ZH(gt1,2))/2._dp
res = res-(dCosTW*g1**2*vu*Cos(TW)*ZH(gt1,2))/2._dp
res = res+dSinTW*g1*g2*vu*Cos(TW)*ZH(gt1,2)
res = res+(dCosTW*g2**2*vu*Cos(TW)*ZH(gt1,2))/2._dp
res = res-(dvu*g1**2*Cos(TW)**2*ZH(gt1,2))/4._dp
res = res+(dvu*g2**2*Cos(TW)**2*ZH(gt1,2))/4._dp
res = res-(dg1*g1*vu*Cos(TW)**2*ZH(gt1,2))/2._dp
res = res+(dg2*g2*vu*Cos(TW)**2*ZH(gt1,2))/2._dp
res = res+(dSinTW*g1**2*vu*Sin(TW)*ZH(gt1,2))/2._dp
res = res+dCosTW*g1*g2*vu*Sin(TW)*ZH(gt1,2)
res = res-(dSinTW*g2**2*vu*Sin(TW)*ZH(gt1,2))/2._dp
res = res+dvu*g1*g2*Cos(TW)*Sin(TW)*ZH(gt1,2)
res = res+dg2*g1*vu*Cos(TW)*Sin(TW)*ZH(gt1,2)
res = res+dg1*g2*vu*Cos(TW)*Sin(TW)*ZH(gt1,2)
res = res+(dvu*g1**2*Sin(TW)**2*ZH(gt1,2))/4._dp
res = res-(dvu*g2**2*Sin(TW)**2*ZH(gt1,2))/4._dp
res = res+(dg1*g1*vu*Sin(TW)**2*ZH(gt1,2))/2._dp
res = res-(dg2*g2*vu*Sin(TW)**2*ZH(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhVZVZ  
 
 
Subroutine CT_CouplingHmcVWmVP(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,             & 
& dSinTW,dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW,dg1,dg2,dvd,dvu,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHmcVWmVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*dZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*dZP(gt1,2))/2._dp
res = res+(dCosTW*g1*g2*vd*ZP(gt1,1))/2._dp
res = res+(dvd*g1*g2*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(dg2*g1*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(dg1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(dCosTW*g1*g2*vu*ZP(gt1,2))/2._dp
res = res+(dvu*g1*g2*Cos(TW)*ZP(gt1,2))/2._dp
res = res+(dg2*g1*vu*Cos(TW)*ZP(gt1,2))/2._dp
res = res+(dg1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHmcVWmVP  
 
 
Subroutine CT_CouplingHmcVWmVZ(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,             & 
& dSinTW,dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW,dg1,dg2,dvd,dvu,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHmcVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*dZP(gt1,1)*Sin(TW))/2._dp
res = res-(g1*g2*vu*dZP(gt1,2)*Sin(TW))/2._dp
res = res-(dSinTW*g1*g2*vd*ZP(gt1,1))/2._dp
res = res-(dvd*g1*g2*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(dg2*g1*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(dg1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(dSinTW*g1*g2*vu*ZP(gt1,2))/2._dp
res = res-(dvu*g1*g2*Sin(TW)*ZP(gt1,2))/2._dp
res = res-(dg2*g1*vu*Sin(TW)*ZP(gt1,2))/2._dp
res = res-(dg1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHmcVWmVZ  
 
 
Subroutine CT_CouplingcHmVPVWm(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,             & 
& dSinTW,dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW,dg1,dg2,dvd,dvu,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcHmVPVWm' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*vd*Cos(TW)*dZP(gt1,1))/2._dp
res = res+(g1*g2*vu*Cos(TW)*dZP(gt1,2))/2._dp
res = res+(dCosTW*g1*g2*vd*ZP(gt1,1))/2._dp
res = res+(dvd*g1*g2*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(dg2*g1*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(dg1*g2*vd*Cos(TW)*ZP(gt1,1))/2._dp
res = res+(dCosTW*g1*g2*vu*ZP(gt1,2))/2._dp
res = res+(dvu*g1*g2*Cos(TW)*ZP(gt1,2))/2._dp
res = res+(dg2*g1*vu*Cos(TW)*ZP(gt1,2))/2._dp
res = res+(dg1*g2*vu*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcHmVPVWm  
 
 
Subroutine CT_CouplingcHmVWmVZ(gt1,g1,g2,vd,vu,ZP,TW,dg1,dg2,dvd,dvu,dZP,             & 
& dSinTW,dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,vd,vu,ZP(2,2),TW,dg1,dg2,dvd,dvu,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcHmVWmVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*vd*dZP(gt1,1)*Sin(TW))/2._dp
res = res-(g1*g2*vu*dZP(gt1,2)*Sin(TW))/2._dp
res = res-(dSinTW*g1*g2*vd*ZP(gt1,1))/2._dp
res = res-(dvd*g1*g2*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(dg2*g1*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(dg1*g2*vd*Sin(TW)*ZP(gt1,1))/2._dp
res = res-(dSinTW*g1*g2*vu*ZP(gt1,2))/2._dp
res = res-(dvu*g1*g2*Sin(TW)*ZP(gt1,2))/2._dp
res = res-(dg2*g1*vu*Sin(TW)*ZP(gt1,2))/2._dp
res = res-(dg1*g2*vu*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcHmVWmVZ  
 
 
Subroutine CT_CouplingVGVGVG(g3,dg3,res)

Implicit None 

Real(dp), Intent(in) :: g3,dg3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingVGVGVG' 
 
res = 0._dp 
res = res+dg3
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingVGVGVG  
 
 
Subroutine CT_CouplingcVWmVPVWm(g2,TW,dg2,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcVWmVPVWm' 
 
res = 0._dp 
res = res+dSinTW*g2
res = res+dg2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcVWmVPVWm  
 
 
Subroutine CT_CouplingcVWmVWmVZ(g2,TW,dg2,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcVWmVWmVZ' 
 
res = 0._dp 
res = res-(dCosTW*g2)
res = res-(dg2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcVWmVWmVZ  
 
 
Subroutine CT_CouplingcFdFdAh(gt1,gt2,gt3,Yd,ZA,ZDL,ZDR,dYd,dZA,dZDL,dZDR,            & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2),dZA(2,2)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3),dYd(3,3),dZDL(3,3),dZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFdAh' 
 
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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*dZA(gt3,1)*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*dYd(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*dZA(gt3,1)*ZDR(gt2,j1)*ZDL(gt1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*dZDL(gt1,j2)*ZDR(gt2,j1)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yd(j1,j2))*dZDR(gt2,j1)*ZDL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(dYd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdAh  
 
 
Subroutine CT_CouplingcFeFeAh(gt1,gt2,gt3,Ye,ZA,ZEL,ZER,dYe,dZA,dZEL,dZER,            & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2),dZA(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3),dYe(3,3),dZEL(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFeAh' 
 
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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*dZA(gt3,1)*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*dYe(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZA(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*dZA(gt3,1)*ZER(gt2,j1)*ZEL(gt1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*dZEL(gt1,j2)*ZER(gt2,j1)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Ye(j1,j2))*dZER(gt2,j1)*ZEL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(dYe(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZA(gt3,1))/sqrt(2._dp)
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFeAh  
 
 
Subroutine CT_CouplingcFuFuAh(gt1,gt2,gt3,Yu,ZA,ZUL,ZUR,dYu,dZA,dZUL,dZUR,            & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZA(2,2),dZA(2,2)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3),dYu(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFuAh' 
 
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
resL = resL+(Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*dZA(gt3,2)*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*dYu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZA(gt3,2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZA(gt3,2)*ZUR(gt2,j1)*ZUL(gt1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZUL(gt1,j2)*ZUR(gt2,j1)*ZA(gt3,2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZUR(gt2,j1)*ZUL(gt1,j2)*ZA(gt3,2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZA(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuAh  
 
 
Subroutine CT_CouplingcFdFdhh(gt1,gt2,gt3,Yd,ZH,ZDL,ZDR,dYd,dZH,dZDL,dZDR,            & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2),dZH(2,2)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3),dYd(3,3),dZDL(3,3),dZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFdhh' 
 
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
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*dZH(gt3,1)*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*dYd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZDL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZDR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yd(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZH(gt3,1)*ZDR(gt2,j1)*ZDL(gt1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZDL(gt1,j2)*ZDR(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZDR(gt2,j1)*ZDL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYd(j1,j2))*ZDR(gt2,j1)*ZDL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdhh  
 
 
Subroutine CT_CouplingcFuFdcHm(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,dYu,              & 
& dYd,dZP,dZDL,dZDR,dZUL,dZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3),dYu(3,3),dYd(3,3),dZDL(3,3),      & 
& dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFdcHm' 
 
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
resL = resL+Conjg(ZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*dZP(gt3,2)*Yu(j1,j2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*dYu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(dZDL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(dZUR(gt1,j1))*Conjg(ZDL(gt2,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*dZP(gt3,1)*ZDR(gt2,j1)*ZUL(gt1,j2))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*dZUL(gt1,j2)*ZDR(gt2,j1)*ZP(gt3,1))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(Yd(j1,j2))*dZDR(gt2,j1)*ZUL(gt1,j2)*ZP(gt3,1))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-(Conjg(dYd(j1,j2))*ZDR(gt2,j1)*ZUL(gt1,j2)*ZP(gt3,1))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFdcHm  
 
 
Subroutine CT_CouplingcFeFehh(gt1,gt2,gt3,Ye,ZH,ZEL,ZER,dYe,dZH,dZEL,dZER,            & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2),dZH(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3),dYe(3,3),dZEL(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFehh' 
 
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
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*dZH(gt3,1)*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZER(gt1,j1))*Conjg(ZEL(gt2,j2))*dYe(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZEL(gt2,j2))*Conjg(ZER(gt1,j1))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZER(gt1,j1))*Conjg(ZEL(gt2,j2))*Ye(j1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZH(gt3,1)*ZER(gt2,j1)*ZEL(gt1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZEL(gt1,j2)*ZER(gt2,j1)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZER(gt2,j1)*ZEL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYe(j1,j2))*ZER(gt2,j1)*ZEL(gt1,j2)*ZH(gt3,1))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFehh  
 
 
Subroutine CT_CouplingcFvFecHm(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3),dYe(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFvFecHm' 
 
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
resR = resR-(Conjg(Ye(j1,gt1))*dZP(gt3,1)*ZER(gt2,j1))
End Do 
Do j1 = 1,3
resR = resR-(Conjg(Ye(j1,gt1))*dZER(gt2,j1)*ZP(gt3,1))
End Do 
Do j1 = 1,3
resR = resR-(Conjg(dYe(j1,gt1))*ZER(gt2,j1)*ZP(gt3,1))
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFvFecHm  
 
 
Subroutine CT_CouplingcFuFuhh(gt1,gt2,gt3,Yu,ZH,ZUL,ZUR,dYu,dZH,dZUL,dZUR,            & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZH(2,2),dZH(2,2)

Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3),dYu(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFuhh' 
 
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
resL = resL-((Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*dZH(gt3,2)*Yu(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*dYu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZUL(gt2,j2))*Conjg(ZUR(gt1,j1))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZUR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yu(j1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZH(gt3,2)*ZUR(gt2,j1)*ZUL(gt1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZUL(gt1,j2)*ZUR(gt2,j1)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZUR(gt2,j1)*ZUL(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYu(j1,j2))*ZUR(gt2,j1)*ZUL(gt1,j2)*ZH(gt3,2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuhh  
 
 
Subroutine CT_CouplingcFdFuHm(gt1,gt2,gt3,Yu,Yd,ZP,ZDL,ZDR,ZUL,ZUR,dYu,               & 
& dYd,dZP,dZDL,dZDR,dZUL,dZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Yu(3,3),Yd(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3),dYu(3,3),dYd(3,3),dZDL(3,3),      & 
& dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFuHm' 
 
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
resL = resL-(Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*dZP(gt3,1)*Yd(j1,j2))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-(Conjg(ZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*dYd(j1,j2)*ZP(gt3,1))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-(Conjg(dZUL(gt2,j2))*Conjg(ZDR(gt1,j1))*Yd(j1,j2)*ZP(gt3,1))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-(Conjg(dZDR(gt1,j1))*Conjg(ZUL(gt2,j2))*Yd(j1,j2)*ZP(gt3,1))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*dZP(gt3,2)*ZUR(gt2,j1)*ZDL(gt1,j2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*dZDL(gt1,j2)*ZUR(gt2,j1)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*dZUR(gt2,j1)*ZDL(gt1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(dYu(j1,j2))*ZUR(gt2,j1)*ZDL(gt1,j2)*ZP(gt3,2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFuHm  
 
 
Subroutine CT_CouplingcFeFvHm(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3),dYe(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFvHm' 
 
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
resL = resL-(Conjg(ZER(gt1,j1))*dZP(gt3,1)*Ye(j1,gt2))
End Do 
Do j1 = 1,3
resL = resL-(Conjg(ZER(gt1,j1))*dYe(j1,gt2)*ZP(gt3,1))
End Do 
Do j1 = 1,3
resL = resL-(Conjg(dZER(gt1,j1))*Ye(j1,gt2)*ZP(gt3,1))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFvHm  
 
 
Subroutine CT_CouplingcFdFdVG(gt1,gt2,g3,dg3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3,dg3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFdVG' 
 
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
resL = resL-1._dp*(dg3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(dg3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdVG  
 
 
Subroutine CT_CouplingcFdFdVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFdVP' 
 
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
resL = resL-(dCosTW*g1)/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dSinTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg1*Cos(TW))/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(dCosTW*g1)/3._dp
End If 
If ((gt1.eq.gt2)) Then 
resR = resR+(dg1*Cos(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdVP  
 
 
Subroutine CT_CouplingcFdFdVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFdVZ' 
 
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
resL = resL+(dSinTW*g1)/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dCosTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg1*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-(dSinTW*g1)/3._dp
End If 
If ((gt1.eq.gt2)) Then 
resR = resR-(dg1*Sin(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdVZ  
 
 
Subroutine CT_CouplingcFuFdcVWm(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3),dZDL(3,3),dZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFdcVWm' 
 
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
resL = resL-((g2*Conjg(ZDL(gt2,j1))*dZUL(gt1,j1))/sqrt(2._dp))
End Do 
Do j1 = 1,3
resL = resL-((g2*Conjg(dZDL(gt2,j1))*ZUL(gt1,j1))/sqrt(2._dp))
End Do 
Do j1 = 1,3
resL = resL-((dg2*Conjg(ZDL(gt2,j1))*ZUL(gt1,j1))/sqrt(2._dp))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFdcVWm  
 
 
Subroutine CT_CouplingcFeFeVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFeVP' 
 
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
resL = resL+(dCosTW*g1)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dSinTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg1*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+dCosTW*g1
End If 
If ((gt1.eq.gt2)) Then 
resR = resR+dg1*Cos(TW)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFeVP  
 
 
Subroutine CT_CouplingcFeFeVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFeVZ' 
 
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
resL = resL-(dSinTW*g1)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dCosTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-(dSinTW*g1)
End If 
If ((gt1.eq.gt2)) Then 
resR = resR-(dg1*Sin(TW))
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFeVZ  
 
 
Subroutine CT_CouplingcFvFecVWm(gt1,gt2,g2,ZEL,dg2,dZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZEL(3,3),dZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFvFecVWm' 
 
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
resL = resL-((g2*Conjg(dZEL(gt2,gt1)))/sqrt(2._dp))
End If 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
resL = resL-((dg2*Conjg(ZEL(gt2,gt1)))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFvFecVWm  
 
 
Subroutine CT_CouplingcFuFuVG(gt1,gt2,g3,dg3,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g3,dg3

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFuVG' 
 
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
resL = resL-1._dp*(dg3)
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR-1._dp*(dg3)
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuVG  
 
 
Subroutine CT_CouplingcFuFuVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFuVP' 
 
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
resL = resL-(dCosTW*g1)/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dSinTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg1*Cos(TW))/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg2*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(-2*dCosTW*g1)/3._dp
End If 
If ((gt1.eq.gt2)) Then 
resR = resR+(-2*dg1*Cos(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuVP  
 
 
Subroutine CT_CouplingcFdFuVWm(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3),dZDL(3,3),dZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFuVWm' 
 
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
resL = resL-((g2*Conjg(ZUL(gt2,j1))*dZDL(gt1,j1))/sqrt(2._dp))
End Do 
Do j1 = 1,3
resL = resL-((g2*Conjg(dZUL(gt2,j1))*ZDL(gt1,j1))/sqrt(2._dp))
End Do 
Do j1 = 1,3
resL = resL-((dg2*Conjg(ZUL(gt2,j1))*ZDL(gt1,j1))/sqrt(2._dp))
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFuVWm  
 
 
Subroutine CT_CouplingcFuFuVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFuVZ' 
 
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
resL = resL+(dSinTW*g1)/6._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dCosTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL+(dg1*Sin(TW))/6._dp
End If 
resR = 0._dp 
If ((gt1.eq.gt2)) Then 
resR = resR+(2*dSinTW*g1)/3._dp
End If 
If ((gt1.eq.gt2)) Then 
resR = resR+(2*dg1*Sin(TW))/3._dp
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuVZ  
 
 
Subroutine CT_CouplingcFeFvVWm(gt1,gt2,g2,ZEL,dg2,dZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZEL(3,3),dZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFvVWm' 
 
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
resL = resL-((g2*dZEL(gt1,gt2))/sqrt(2._dp))
End If 
If ((gt2.le.3).And.(gt2.ge.1)) Then 
resL = resL-((dg2*ZEL(gt1,gt2))/sqrt(2._dp))
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFvVWm  
 
 
Subroutine CT_CouplingcFvFvVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,          & 
& resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFvFvVZ' 
 
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
resL = resL-(dSinTW*g1)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dCosTW*g2)/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg2*Cos(TW))/2._dp
End If 
If ((gt1.eq.gt2)) Then 
resL = resL-(dg1*Sin(TW))/2._dp
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFvFvVZ  
 
 
End Module CouplingsCT_gumTHDMII 
