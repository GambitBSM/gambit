! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:48 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module CouplingsCT_Inert2
 
Use Control 
Use Settings 
Use Model_Data_Inert2 
Use Mathematics, Only: CompareMatrices, Adjungate 
 
Contains 
 
 Subroutine CalculateCouplingCT(lam5,v,lam3,lam4,ZP,lam1,g1,g2,TW,g3,Yd,               & 
& ZDL,ZDR,Yu,ZUL,ZUR,Ye,ZEL,ZER,dlam5,dv,dlam3,dlam4,dZP,dlam1,dg1,dg2,dSinTW,           & 
& dCosTW,dTanTW,dg3,dYd,dZDL,dZDR,dYu,dZUL,dZUR,dYe,dZEL,dZER,ctcplA0A0G0,               & 
& ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp,ctcplG0G0hh,ctcplG0H0H0,              & 
& ctcplH0H0hh,ctcplH0HpcHp,ctcplhhhhhh,ctcplhhHpcHp,ctcplA0H0VZ,ctcplA0HpcVWp,           & 
& ctcplA0cHpVWp,ctcplG0hhVZ,ctcplG0HpcVWp,ctcplG0cHpVWp,ctcplH0HpcVWp,ctcplH0cHpVWp,     & 
& ctcplhhHpcVWp,ctcplhhcHpVWp,ctcplHpcHpVP,ctcplHpcHpVZ,ctcplhhcVWpVWp,ctcplhhVZVZ,      & 
& ctcplHpcVWpVP,ctcplHpcVWpVZ,ctcplcHpVPVWp,ctcplcHpVWpVZ,ctcplVGVGVG,ctcplcVWpVPVWp,    & 
& ctcplcVWpVWpVZ,ctcplcFdFdG0L,ctcplcFdFdG0R,ctcplcFdFdhhL,ctcplcFdFdhhR,ctcplcFuFdHpL,  & 
& ctcplcFuFdHpR,ctcplcFeFeG0L,ctcplcFeFeG0R,ctcplcFeFehhL,ctcplcFeFehhR,ctcplcFvFeHpL,   & 
& ctcplcFvFeHpR,ctcplcFuFuG0L,ctcplcFuFuG0R,ctcplcFuFuhhL,ctcplcFuFuhhR,ctcplcFdFucHpL,  & 
& ctcplcFdFucHpR,ctcplcFeFvcHpL,ctcplcFeFvcHpR,ctcplcFdFdVGL,ctcplcFdFdVGR,              & 
& ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFuFdVWpL,ctcplcFuFdVWpR,ctcplcFdFdVZL,               & 
& ctcplcFdFdVZR,ctcplcFeFeVPL,ctcplcFeFeVPR,ctcplcFvFeVWpL,ctcplcFvFeVWpR,               & 
& ctcplcFeFeVZL,ctcplcFeFeVZR,ctcplcFuFuVGL,ctcplcFuFuVGR,ctcplcFuFuVPL,ctcplcFuFuVPR,   & 
& ctcplcFuFuVZL,ctcplcFuFuVZR,ctcplcFdFucVWpL,ctcplcFdFucVWpR,ctcplcFvFvVZL,             & 
& ctcplcFvFvVZR,ctcplcFeFvcVWpL,ctcplcFeFvcVWpR)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g1,g2,TW,g3,dv,dZP(2,2),dg1,dg2,dSinTW,dCosTW,dTanTW,dg3

Complex(dp), Intent(in) :: lam5,lam3,lam4,lam1,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),              & 
& Ye(3,3),ZEL(3,3),ZER(3,3),dlam5,dlam3,dlam4,dlam1,dYd(3,3),dZDL(3,3),dZDR(3,3),        & 
& dYu(3,3),dZUL(3,3),dZUR(3,3),dYe(3,3),dZEL(3,3),dZER(3,3)

Complex(dp), Intent(out) :: ctcplA0A0G0,ctcplA0A0hh,ctcplA0G0H0,ctcplA0H0hh,ctcplA0HpcHp(2,2),ctcplG0G0hh,        & 
& ctcplG0H0H0,ctcplH0H0hh,ctcplH0HpcHp(2,2),ctcplhhhhhh,ctcplhhHpcHp(2,2),               & 
& ctcplA0H0VZ,ctcplA0HpcVWp(2),ctcplA0cHpVWp(2),ctcplG0hhVZ,ctcplG0HpcVWp(2),            & 
& ctcplG0cHpVWp(2),ctcplH0HpcVWp(2),ctcplH0cHpVWp(2),ctcplhhHpcVWp(2),ctcplhhcHpVWp(2),  & 
& ctcplHpcHpVP(2,2),ctcplHpcHpVZ(2,2),ctcplhhcVWpVWp,ctcplhhVZVZ,ctcplHpcVWpVP(2),       & 
& ctcplHpcVWpVZ(2),ctcplcHpVPVWp(2),ctcplcHpVWpVZ(2),ctcplVGVGVG,ctcplcVWpVPVWp,         & 
& ctcplcVWpVWpVZ,ctcplcFdFdG0L(3,3),ctcplcFdFdG0R(3,3),ctcplcFdFdhhL(3,3),               & 
& ctcplcFdFdhhR(3,3),ctcplcFuFdHpL(3,3,2),ctcplcFuFdHpR(3,3,2),ctcplcFeFeG0L(3,3),       & 
& ctcplcFeFeG0R(3,3),ctcplcFeFehhL(3,3),ctcplcFeFehhR(3,3),ctcplcFvFeHpL(3,3,2),         & 
& ctcplcFvFeHpR(3,3,2),ctcplcFuFuG0L(3,3),ctcplcFuFuG0R(3,3),ctcplcFuFuhhL(3,3),         & 
& ctcplcFuFuhhR(3,3),ctcplcFdFucHpL(3,3,2),ctcplcFdFucHpR(3,3,2),ctcplcFeFvcHpL(3,3,2),  & 
& ctcplcFeFvcHpR(3,3,2),ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3),ctcplcFdFdVPL(3,3),        & 
& ctcplcFdFdVPR(3,3),ctcplcFuFdVWpL(3,3),ctcplcFuFdVWpR(3,3),ctcplcFdFdVZL(3,3),         & 
& ctcplcFdFdVZR(3,3),ctcplcFeFeVPL(3,3),ctcplcFeFeVPR(3,3),ctcplcFvFeVWpL(3,3),          & 
& ctcplcFvFeVWpR(3,3),ctcplcFeFeVZL(3,3),ctcplcFeFeVZR(3,3),ctcplcFuFuVGL(3,3),          & 
& ctcplcFuFuVGR(3,3),ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),           & 
& ctcplcFuFuVZR(3,3),ctcplcFdFucVWpL(3,3),ctcplcFdFucVWpR(3,3),ctcplcFvFvVZL(3,3),       & 
& ctcplcFvFvVZR(3,3),ctcplcFeFvcVWpL(3,3),ctcplcFeFvcVWpR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CalculateCouplingCT'
 
ctcplA0A0G0 = 0._dp 
Call CT_CouplingA0A0G0(lam5,v,dlam5,dv,ctcplA0A0G0)



ctcplA0A0hh = 0._dp 
Call CT_CouplingA0A0hh(lam5,lam3,v,dlam5,dlam3,dv,ctcplA0A0hh)



ctcplA0G0H0 = 0._dp 
Call CT_CouplingA0G0H0(lam5,v,dlam5,dv,ctcplA0G0H0)



ctcplA0H0hh = 0._dp 
Call CT_CouplingA0H0hh(lam5,v,dlam5,dv,ctcplA0H0hh)



ctcplA0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CT_CouplingA0HpcHp(gt2,gt3,lam5,lam4,v,ZP,dlam5,dlam4,dv,dZP,ctcplA0HpcHp(gt2,gt3))

 End Do 
End Do 


ctcplG0G0hh = 0._dp 
Call CT_CouplingG0G0hh(lam1,v,dlam1,dv,ctcplG0G0hh)



ctcplG0H0H0 = 0._dp 
Call CT_CouplingG0H0H0(lam5,v,dlam5,dv,ctcplG0H0H0)



ctcplH0H0hh = 0._dp 
Call CT_CouplingH0H0hh(lam5,lam3,v,dlam5,dlam3,dv,ctcplH0H0hh)



ctcplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CT_CouplingH0HpcHp(gt2,gt3,lam5,lam4,v,ZP,dlam5,dlam4,dv,dZP,ctcplH0HpcHp(gt2,gt3))

 End Do 
End Do 


ctcplhhhhhh = 0._dp 
Call CT_Couplinghhhhhh(lam1,v,dlam1,dv,ctcplhhhhhh)



ctcplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CT_CouplinghhHpcHp(gt2,gt3,lam1,lam4,lam3,v,ZP,dlam1,dlam4,dlam3,dv,             & 
& dZP,ctcplhhHpcHp(gt2,gt3))

 End Do 
End Do 


ctcplA0H0VZ = 0._dp 
Call CT_CouplingA0H0VZ(g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplA0H0VZ)



ctcplA0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplingA0HpcVWp(gt2,g2,ZP,dg2,dZP,ctcplA0HpcVWp(gt2))

End Do 


ctcplA0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplingA0cHpVWp(gt2,g2,ZP,dg2,dZP,ctcplA0cHpVWp(gt2))

End Do 


ctcplG0hhVZ = 0._dp 
Call CT_CouplingG0hhVZ(g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplG0hhVZ)



ctcplG0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplingG0HpcVWp(gt2,g2,ZP,dg2,dZP,ctcplG0HpcVWp(gt2))

End Do 


ctcplG0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplingG0cHpVWp(gt2,g2,ZP,dg2,dZP,ctcplG0cHpVWp(gt2))

End Do 


ctcplH0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplingH0HpcVWp(gt2,g2,ZP,dg2,dZP,ctcplH0HpcVWp(gt2))

End Do 


ctcplH0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplingH0cHpVWp(gt2,g2,ZP,dg2,dZP,ctcplH0cHpVWp(gt2))

End Do 


ctcplhhHpcVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplinghhHpcVWp(gt2,g2,ZP,dg2,dZP,ctcplhhHpcVWp(gt2))

End Do 


ctcplhhcHpVWp = 0._dp 
Do gt2 = 1, 2
Call CT_CouplinghhcHpVWp(gt2,g2,ZP,dg2,dZP,ctcplhhcHpVWp(gt2))

End Do 


ctcplHpcHpVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingHpcHpVP(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,dTanTW,         & 
& ctcplHpcHpVP(gt1,gt2))

 End Do 
End Do 


ctcplHpcHpVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CT_CouplingHpcHpVZ(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,dTanTW,         & 
& ctcplHpcHpVZ(gt1,gt2))

 End Do 
End Do 


ctcplhhcVWpVWp = 0._dp 
Call CT_CouplinghhcVWpVWp(g2,v,dg2,dv,ctcplhhcVWpVWp)



ctcplhhVZVZ = 0._dp 
Call CT_CouplinghhVZVZ(g1,g2,v,TW,dg1,dg2,dv,dSinTW,dCosTW,dTanTW,ctcplhhVZVZ)



ctcplHpcVWpVP = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingHpcVWpVP(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,dCosTW,              & 
& dTanTW,ctcplHpcVWpVP(gt1))

End Do 


ctcplHpcVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingHpcVWpVZ(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,dCosTW,              & 
& dTanTW,ctcplHpcVWpVZ(gt1))

End Do 


ctcplcHpVPVWp = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingcHpVPVWp(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,dCosTW,              & 
& dTanTW,ctcplcHpVPVWp(gt1))

End Do 


ctcplcHpVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CT_CouplingcHpVWpVZ(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,dCosTW,              & 
& dTanTW,ctcplcHpVWpVZ(gt1))

End Do 


ctcplVGVGVG = 0._dp 
Call CT_CouplingVGVGVG(g3,dg3,ctcplVGVGVG)



ctcplcVWpVPVWp = 0._dp 
Call CT_CouplingcVWpVPVWp(g2,TW,dg2,dSinTW,dCosTW,dTanTW,ctcplcVWpVPVWp)



ctcplcVWpVWpVZ = 0._dp 
Call CT_CouplingcVWpVWpVZ(g2,TW,dg2,dSinTW,dCosTW,dTanTW,ctcplcVWpVWpVZ)



ctcplcFdFdG0L = 0._dp 
ctcplcFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFdG0(gt1,gt2,Yd,ZDL,ZDR,dYd,dZDL,dZDR,ctcplcFdFdG0L(gt1,gt2)       & 
& ,ctcplcFdFdG0R(gt1,gt2))

 End Do 
End Do 


ctcplcFdFdhhL = 0._dp 
ctcplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFdhh(gt1,gt2,Yd,ZDL,ZDR,dYd,dZDL,dZDR,ctcplcFdFdhhL(gt1,gt2)       & 
& ,ctcplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


ctcplcFuFdHpL = 0._dp 
ctcplcFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFuFdHp(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,dYd,dYu,dZP,             & 
& dZDL,dZDR,dZUL,dZUR,ctcplcFuFdHpL(gt1,gt2,gt3),ctcplcFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFeFeG0L = 0._dp 
ctcplcFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFeG0(gt1,gt2,Ye,ZEL,ZER,dYe,dZEL,dZER,ctcplcFeFeG0L(gt1,gt2)       & 
& ,ctcplcFeFeG0R(gt1,gt2))

 End Do 
End Do 


ctcplcFeFehhL = 0._dp 
ctcplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFehh(gt1,gt2,Ye,ZEL,ZER,dYe,dZEL,dZER,ctcplcFeFehhL(gt1,gt2)       & 
& ,ctcplcFeFehhR(gt1,gt2))

 End Do 
End Do 


ctcplcFvFeHpL = 0._dp 
ctcplcFvFeHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFvFeHp(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,ctcplcFvFeHpL(gt1,gt2,gt3) & 
& ,ctcplcFvFeHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFuFuG0L = 0._dp 
ctcplcFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFuG0(gt1,gt2,Yu,ZUL,ZUR,dYu,dZUL,dZUR,ctcplcFuFuG0L(gt1,gt2)       & 
& ,ctcplcFuFuG0R(gt1,gt2))

 End Do 
End Do 


ctcplcFuFuhhL = 0._dp 
ctcplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFuhh(gt1,gt2,Yu,ZUL,ZUR,dYu,dZUL,dZUR,ctcplcFuFuhhL(gt1,gt2)       & 
& ,ctcplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


ctcplcFdFucHpL = 0._dp 
ctcplcFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFdFucHp(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,dYd,dYu,dZP,            & 
& dZDL,dZDR,dZUL,dZUR,ctcplcFdFucHpL(gt1,gt2,gt3),ctcplcFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


ctcplcFeFvcHpL = 0._dp 
ctcplcFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CT_CouplingcFeFvcHp(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,ctcplcFeFvcHpL(gt1,gt2,gt3)& 
& ,ctcplcFeFvcHpR(gt1,gt2,gt3))

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


ctcplcFuFdVWpL = 0._dp 
ctcplcFuFdVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFdVWp(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,ctcplcFuFdVWpL(gt1,gt2)     & 
& ,ctcplcFuFdVWpR(gt1,gt2))

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


ctcplcFeFeVPL = 0._dp 
ctcplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFeVP(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFeFeVPL(gt1,gt2)& 
& ,ctcplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


ctcplcFvFeVWpL = 0._dp 
ctcplcFvFeVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFvFeVWp(gt1,gt2,g2,ZEL,dg2,dZEL,ctcplcFvFeVWpL(gt1,gt2)              & 
& ,ctcplcFvFeVWpR(gt1,gt2))

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


ctcplcFuFuVZL = 0._dp 
ctcplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFuFuVZ(gt1,gt2,g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,ctcplcFuFuVZL(gt1,gt2)& 
& ,ctcplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


ctcplcFdFucVWpL = 0._dp 
ctcplcFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFdFucVWp(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,ctcplcFdFucVWpL(gt1,gt2)   & 
& ,ctcplcFdFucVWpR(gt1,gt2))

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


ctcplcFeFvcVWpL = 0._dp 
ctcplcFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CT_CouplingcFeFvcVWp(gt1,gt2,g2,ZEL,dg2,dZEL,ctcplcFeFvcVWpL(gt1,gt2)            & 
& ,ctcplcFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CalculateCouplingCT

Subroutine CT_CouplingA0A0G0(lam5,v,dlam5,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam5,dlam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0A0G0' 
 
res = 0._dp 
res = res-(dv*lam5)/2._dp
res = res-(dlam5*v)/2._dp
res = res+(v*Conjg(dlam5))/2._dp
res = res+(dv*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0A0G0  
 
 
Subroutine CT_CouplingA0A0hh(lam5,lam3,v,dlam5,dlam3,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam5,lam3,dlam5,dlam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0A0hh' 
 
res = 0._dp 
res = res-(dv*lam3)
res = res+(dv*lam5)/2._dp
res = res-(dlam3*v)
res = res+(dlam5*v)/2._dp
res = res+(v*Conjg(dlam5))/2._dp
res = res+(dv*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0A0hh  
 
 
Subroutine CT_CouplingA0G0H0(lam5,v,dlam5,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam5,dlam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0G0H0' 
 
res = 0._dp 
res = res+(dv*lam5)/2._dp
res = res+(dlam5*v)/2._dp
res = res+(v*Conjg(dlam5))/2._dp
res = res+(dv*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0G0H0  
 
 
Subroutine CT_CouplingA0H0hh(lam5,v,dlam5,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam5,dlam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0H0hh' 
 
res = 0._dp 
res = res+(dv*lam5)/2._dp
res = res+(dlam5*v)/2._dp
res = res-(v*Conjg(dlam5))/2._dp
res = res-(dv*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0H0hh  
 
 
Subroutine CT_CouplingA0HpcHp(gt2,gt3,lam5,lam4,v,ZP,dlam5,dlam4,dv,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2),dv,dZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4,dlam5,dlam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0HpcHp' 
 
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
res = res-(lam4*v*dZP(gt3,2)*ZP(gt2,1))/2._dp
res = res-(lam5*v*dZP(gt3,2)*ZP(gt2,1))/2._dp
res = res+(lam4*v*dZP(gt3,1)*ZP(gt2,2))/2._dp
res = res+(v*Conjg(lam5)*dZP(gt3,1)*ZP(gt2,2))/2._dp
res = res+(lam4*v*dZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*dZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dv*lam4*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dlam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(dlam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dv*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*dZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam5*v*dZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dv*lam4*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dv*lam5*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dlam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dlam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0HpcHp  
 
 
Subroutine CT_CouplingG0G0hh(lam1,v,dlam1,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam1,dlam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingG0G0hh' 
 
res = 0._dp 
res = res-(dv*lam1)
res = res-(dlam1*v)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingG0G0hh  
 
 
Subroutine CT_CouplingG0H0H0(lam5,v,dlam5,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam5,dlam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingG0H0H0' 
 
res = 0._dp 
res = res+(dv*lam5)/2._dp
res = res+(dlam5*v)/2._dp
res = res-(v*Conjg(dlam5))/2._dp
res = res-(dv*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingG0H0H0  
 
 
Subroutine CT_CouplingH0H0hh(lam5,lam3,v,dlam5,dlam3,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam5,lam3,dlam5,dlam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingH0H0hh' 
 
res = 0._dp 
res = res-(dv*lam3)
res = res-(dv*lam5)/2._dp
res = res-(dlam3*v)
res = res-(dlam5*v)/2._dp
res = res-(v*Conjg(dlam5))/2._dp
res = res-(dv*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingH0H0hh  
 
 
Subroutine CT_CouplingH0HpcHp(gt2,gt3,lam5,lam4,v,ZP,dlam5,dlam4,dv,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2),dv,dZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4,dlam5,dlam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingH0HpcHp' 
 
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
res = res-(lam4*v*dZP(gt3,2)*ZP(gt2,1))/2._dp
res = res+(lam5*v*dZP(gt3,2)*ZP(gt2,1))/2._dp
res = res-(lam4*v*dZP(gt3,1)*ZP(gt2,2))/2._dp
res = res+(v*Conjg(lam5)*dZP(gt3,1)*ZP(gt2,2))/2._dp
res = res-(lam4*v*dZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*dZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dv*lam4*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(dlam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(dlam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(dv*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*dZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(lam5*v*dZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dv*lam4*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(dv*lam5*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(dlam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(dlam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingH0HpcHp  
 
 
Subroutine CT_Couplinghhhhhh(lam1,v,dlam1,dv,res)

Implicit None 

Real(dp), Intent(in) :: v,dv

Complex(dp), Intent(in) :: lam1,dlam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_Couplinghhhhhh' 
 
res = 0._dp 
res = res-3*dv*lam1
res = res-3*dlam1*v
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_Couplinghhhhhh  
 
 
Subroutine CT_CouplinghhHpcHp(gt2,gt3,lam1,lam4,lam3,v,ZP,dlam1,dlam4,dlam3,          & 
& dv,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2),dv,dZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3,dlam1,dlam4,dlam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhHpcHp' 
 
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
res = res-(lam3*v*dZP(gt3,1)*ZP(gt2,1))
res = res-(lam4*v*dZP(gt3,1)*ZP(gt2,1))
res = res-(lam1*v*dZP(gt3,2)*ZP(gt2,2))
res = res-(lam3*v*dZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*v*dZP(gt2,1)*ZP(gt3,1))
res = res-(dv*lam3*ZP(gt2,1)*ZP(gt3,1))
res = res-(dv*lam4*ZP(gt2,1)*ZP(gt3,1))
res = res-(dlam3*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(dlam4*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam1*v*dZP(gt2,2)*ZP(gt3,2))
res = res-(dv*lam1*ZP(gt2,2)*ZP(gt3,2))
res = res-(dlam1*v*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhHpcHp  
 
 
Subroutine CT_CouplingA0H0VZ(g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0H0VZ' 
 
res = 0._dp 
res = res+(dSinTW*g1)/2._dp
res = res+(dCosTW*g2)/2._dp
res = res+(dg2*Cos(TW))/2._dp
res = res+(dg1*Sin(TW))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0H0VZ  
 
 
Subroutine CT_CouplingA0HpcVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*dZP(gt2,1))/2._dp
res = res-(dg2*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0HpcVWp  
 
 
Subroutine CT_CouplingA0cHpVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingA0cHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*dZP(gt2,1))/2._dp
res = res-(dg2*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingA0cHpVWp  
 
 
Subroutine CT_CouplingG0hhVZ(g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW,dg1,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingG0hhVZ' 
 
res = 0._dp 
res = res-(dSinTW*g1)/2._dp
res = res-(dCosTW*g2)/2._dp
res = res-(dg2*Cos(TW))/2._dp
res = res-(dg1*Sin(TW))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingG0hhVZ  
 
 
Subroutine CT_CouplingG0HpcVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingG0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*dZP(gt2,2))/2._dp
res = res-(dg2*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingG0HpcVWp  
 
 
Subroutine CT_CouplingG0cHpVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingG0cHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*dZP(gt2,2))/2._dp
res = res-(dg2*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingG0cHpVWp  
 
 
Subroutine CT_CouplingH0HpcVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingH0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*dZP(gt2,1))/2._dp
res = res-(dg2*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingH0HpcVWp  
 
 
Subroutine CT_CouplingH0cHpVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingH0cHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2*dZP(gt2,1))/2._dp
res = res+(dg2*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingH0cHpVWp  
 
 
Subroutine CT_CouplinghhHpcVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhHpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2*dZP(gt2,2))/2._dp
res = res+(dg2*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhHpcVWp  
 
 
Subroutine CT_CouplinghhcHpVWp(gt2,g2,ZP,dg2,dZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2),dg2,dZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhcHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*dZP(gt2,2))/2._dp
res = res-(dg2*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhcHpVWp  
 
 
Subroutine CT_CouplingHpcHpVP(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,          & 
& dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW,dg1,dg2,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHpcHpVP' 
 
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
res = res+(g1*Cos(TW)*dZP(gt2,1)*ZP(gt1,1))/2._dp
res = res+(g2*dZP(gt2,1)*Sin(TW)*ZP(gt1,1))/2._dp
res = res+(g1*Cos(TW)*dZP(gt2,2)*ZP(gt1,2))/2._dp
res = res+(g2*dZP(gt2,2)*Sin(TW)*ZP(gt1,2))/2._dp
res = res+(g1*Cos(TW)*dZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*dZP(gt1,1)*Sin(TW)*ZP(gt2,1))/2._dp
res = res+(dCosTW*g1*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dSinTW*g2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dg1*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dg2*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*Cos(TW)*dZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(g2*dZP(gt1,2)*Sin(TW)*ZP(gt2,2))/2._dp
res = res+(dCosTW*g1*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dSinTW*g2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dg1*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dg2*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHpcHpVP  
 
 
Subroutine CT_CouplingHpcHpVZ(gt1,gt2,g1,g2,ZP,TW,dg1,dg2,dZP,dSinTW,dCosTW,          & 
& dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW,dg1,dg2,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHpcHpVZ' 
 
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
res = res+(g2*Cos(TW)*dZP(gt2,1)*ZP(gt1,1))/2._dp
res = res-(g1*dZP(gt2,1)*Sin(TW)*ZP(gt1,1))/2._dp
res = res+(g2*Cos(TW)*dZP(gt2,2)*ZP(gt1,2))/2._dp
res = res-(g1*dZP(gt2,2)*Sin(TW)*ZP(gt1,2))/2._dp
res = res+(g2*Cos(TW)*dZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*dZP(gt1,1)*Sin(TW)*ZP(gt2,1))/2._dp
res = res-(dSinTW*g1*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dCosTW*g2*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(dg2*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(dg1*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*Cos(TW)*dZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1*dZP(gt1,2)*Sin(TW)*ZP(gt2,2))/2._dp
res = res-(dSinTW*g1*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dCosTW*g2*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(dg2*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(dg1*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHpcHpVZ  
 
 
Subroutine CT_CouplinghhcVWpVWp(g2,v,dg2,dv,res)

Implicit None 

Real(dp), Intent(in) :: g2,v,dg2,dv

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhcVWpVWp' 
 
res = 0._dp 
res = res+(dv*g2**2)/2._dp
res = res+dg2*g2*v
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhcVWpVWp  
 
 
Subroutine CT_CouplinghhVZVZ(g1,g2,v,TW,dg1,dg2,dv,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,v,TW,dg1,dg2,dv,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplinghhVZVZ' 
 
res = 0._dp 
res = res+(dv*g1**2)/4._dp
res = res+(dv*g2**2)/4._dp
res = res+(dg1*g1*v)/2._dp
res = res+(dg2*g2*v)/2._dp
res = res-(dCosTW*g1**2*v*Cos(TW))/2._dp
res = res+dSinTW*g1*g2*v*Cos(TW)
res = res+(dCosTW*g2**2*v*Cos(TW))/2._dp
res = res-(dv*g1**2*Cos(TW)**2)/4._dp
res = res+(dv*g2**2*Cos(TW)**2)/4._dp
res = res-(dg1*g1*v*Cos(TW)**2)/2._dp
res = res+(dg2*g2*v*Cos(TW)**2)/2._dp
res = res+(dSinTW*g1**2*v*Sin(TW))/2._dp
res = res+dCosTW*g1*g2*v*Sin(TW)
res = res-(dSinTW*g2**2*v*Sin(TW))/2._dp
res = res+dv*g1*g2*Cos(TW)*Sin(TW)
res = res+dg2*g1*v*Cos(TW)*Sin(TW)
res = res+dg1*g2*v*Cos(TW)*Sin(TW)
res = res+(dv*g1**2*Sin(TW)**2)/4._dp
res = res-(dv*g2**2*Sin(TW)**2)/4._dp
res = res+(dg1*g1*v*Sin(TW)**2)/2._dp
res = res-(dg2*g2*v*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplinghhVZVZ  
 
 
Subroutine CT_CouplingHpcVWpVP(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,               & 
& dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW,dg1,dg2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHpcVWpVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*v*Cos(TW)*dZP(gt1,2))/2._dp
res = res-(dCosTW*g1*g2*v*ZP(gt1,2))/2._dp
res = res-(dv*g1*g2*Cos(TW)*ZP(gt1,2))/2._dp
res = res-(dg2*g1*v*Cos(TW)*ZP(gt1,2))/2._dp
res = res-(dg1*g2*v*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHpcVWpVP  
 
 
Subroutine CT_CouplingHpcVWpVZ(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,               & 
& dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW,dg1,dg2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingHpcVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*dZP(gt1,2)*Sin(TW))/2._dp
res = res+(dSinTW*g1*g2*v*ZP(gt1,2))/2._dp
res = res+(dv*g1*g2*Sin(TW)*ZP(gt1,2))/2._dp
res = res+(dg2*g1*v*Sin(TW)*ZP(gt1,2))/2._dp
res = res+(dg1*g2*v*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingHpcVWpVZ  
 
 
Subroutine CT_CouplingcHpVPVWp(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,               & 
& dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW,dg1,dg2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcHpVPVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*v*Cos(TW)*dZP(gt1,2))/2._dp
res = res-(dCosTW*g1*g2*v*ZP(gt1,2))/2._dp
res = res-(dv*g1*g2*Cos(TW)*ZP(gt1,2))/2._dp
res = res-(dg2*g1*v*Cos(TW)*ZP(gt1,2))/2._dp
res = res-(dg1*g2*v*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcHpVPVWp  
 
 
Subroutine CT_CouplingcHpVWpVZ(gt1,g1,g2,v,ZP,TW,dg1,dg2,dv,dZP,dSinTW,               & 
& dCosTW,dTanTW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW,dg1,dg2,dv,dZP(2,2),dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcHpVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*dZP(gt1,2)*Sin(TW))/2._dp
res = res+(dSinTW*g1*g2*v*ZP(gt1,2))/2._dp
res = res+(dv*g1*g2*Sin(TW)*ZP(gt1,2))/2._dp
res = res+(dg2*g1*v*Sin(TW)*ZP(gt1,2))/2._dp
res = res+(dg1*g2*v*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcHpVWpVZ  
 
 
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
 
 
Subroutine CT_CouplingcVWpVPVWp(g2,TW,dg2,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcVWpVPVWp' 
 
res = 0._dp 
res = res-(dSinTW*g2)
res = res-(dg2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcVWpVPVWp  
 
 
Subroutine CT_CouplingcVWpVWpVZ(g2,TW,dg2,dSinTW,dCosTW,dTanTW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW,dg2,dSinTW,dCosTW,dTanTW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcVWpVWpVZ' 
 
res = 0._dp 
res = res+dCosTW*g2
res = res+dg2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcVWpVWpVZ  
 
 
Subroutine CT_CouplingcFdFdG0(gt1,gt2,Yd,ZDL,ZDR,dYd,dZDL,dZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3),dYd(3,3),dZDL(3,3),dZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFdG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*dYd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZDR(gt1,j2))*Conjg(ZDL(gt2,j1))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZDR(gt2,j2)*ZDL(gt1,j1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdG0  
 
 
Subroutine CT_CouplingcFdFdhh(gt1,gt2,Yd,ZDL,ZDR,dYd,dZDL,dZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*dYd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZDR(gt1,j2))*Conjg(ZDL(gt2,j1))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZDR(gt2,j2)*ZDL(gt1,j1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*dZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFdhh  
 
 
Subroutine CT_CouplingcFuFdHp(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,dYd,               & 
& dYu,dZP,dZDL,dZDR,dZUL,dZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3),dYd(3,3),dYu(3,3),dZDL(3,3),      & 
& dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFdHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDL(gt2,j1))*Conjg(ZUR(gt1,j2))*dZP(gt3,2)*Yu(j1,j2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDL(gt2,j1))*Conjg(ZUR(gt1,j2))*dYu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(dZUR(gt1,j2))*Conjg(ZDL(gt2,j1))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(dZDL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*dZUL(gt1,j1)*ZDR(gt2,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*dZP(gt3,2)*ZDR(gt2,j2)*ZUL(gt1,j1)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*dZDR(gt2,j2)*ZP(gt3,2)*ZUL(gt1,j1)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(dYd(j1,j2))*ZDR(gt2,j2)*ZP(gt3,2)*ZUL(gt1,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFdHp  
 
 
Subroutine CT_CouplingcFeFeG0(gt1,gt2,Ye,ZEL,ZER,dYe,dZEL,dZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3),dYe(3,3),dZEL(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFeG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*dYe(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZER(gt1,j2))*Conjg(ZEL(gt2,j1))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZER(gt2,j2)*ZEL(gt1,j1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYe(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFeG0  
 
 
Subroutine CT_CouplingcFeFehh(gt1,gt2,Ye,ZEL,ZER,dYe,dZEL,dZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*dYe(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZER(gt1,j2))*Conjg(ZEL(gt2,j1))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(dZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZER(gt2,j2)*ZEL(gt1,j1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*dZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYe(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFehh  
 
 
Subroutine CT_CouplingcFvFeHp(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3),dYe(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFvFeHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resR = resR+Conjg(Ye(gt1,j1))*dZP(gt3,2)*ZER(gt2,j1)
End Do 
Do j1 = 1,3
resR = resR+Conjg(Ye(gt1,j1))*dZER(gt2,j1)*ZP(gt3,2)
End Do 
Do j1 = 1,3
resR = resR+Conjg(dYe(gt1,j1))*ZER(gt2,j1)*ZP(gt3,2)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFvFeHp  
 
 
Subroutine CT_CouplingcFuFuG0(gt1,gt2,Yu,ZUL,ZUR,dYu,dZUL,dZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3),dYu(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFuG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*dYu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZUR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZUR(gt2,j2)*ZUL(gt1,j1))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*dZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(dYu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuG0  
 
 
Subroutine CT_CouplingcFuFuhh(gt1,gt2,Yu,ZUL,ZUR,dYu,dZUL,dZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*dYu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZUR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(dZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yu(j1,j2))*dZUR(gt2,j2)*ZUL(gt1,j1))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yu(j1,j2))*dZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(dYu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFuFuhh  
 
 
Subroutine CT_CouplingcFdFucHp(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,dYd,              & 
& dYu,dZP,dZDL,dZDR,dZUL,dZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3),dYd(3,3),dYu(3,3),dZDL(3,3),      & 
& dZDR(3,3),dZUL(3,3),dZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFucHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*dZP(gt3,2)*Yd(j1,j2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(ZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*dYd(j1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(dZUL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+Conjg(dZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yd(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*dZUR(gt2,j2)*ZDL(gt1,j1)*ZP(gt3,2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*dZP(gt3,2)*ZDL(gt1,j1)*ZUR(gt2,j2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*dZDL(gt1,j1)*ZP(gt3,2)*ZUR(gt2,j2)
End Do 
End Do 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(dYu(j1,j2))*ZDL(gt1,j1)*ZP(gt3,2)*ZUR(gt2,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFdFucHp  
 
 
Subroutine CT_CouplingcFeFvcHp(gt1,gt2,gt3,Ye,ZP,ZER,dYe,dZP,dZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2),dZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3),dYe(3,3),dZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFvcHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZER(gt1,j1))*dZP(gt3,2)*Ye(gt2,j1)
End Do 
Do j1 = 1,3
resL = resL+Conjg(ZER(gt1,j1))*dYe(gt2,j1)*ZP(gt3,2)
End Do 
Do j1 = 1,3
resL = resL+Conjg(dZER(gt1,j1))*Ye(gt2,j1)*ZP(gt3,2)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CT_CouplingcFeFvcHp  
 
 
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
 
 
Subroutine CT_CouplingcFuFdVWp(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3),dZDL(3,3),dZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFuFdVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CT_CouplingcFuFdVWp  
 
 
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
 
 
Subroutine CT_CouplingcFvFeVWp(gt1,gt2,g2,ZEL,dg2,dZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZEL(3,3),dZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFvFeVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CT_CouplingcFvFeVWp  
 
 
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
 
 
Subroutine CT_CouplingcFdFucVWp(gt1,gt2,g2,ZDL,ZUL,dg2,dZDL,dZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3),dZDL(3,3),dZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFdFucVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CT_CouplingcFdFucVWp  
 
 
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
 
 
Subroutine CT_CouplingcFeFvcVWp(gt1,gt2,g2,ZEL,dg2,dZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,dg2

Complex(dp), Intent(in) :: ZEL(3,3),dZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CT_CouplingcFeFvcVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CT_CouplingcFeFvcVWp  
 
 
End Module CouplingsCT_Inert2 
